#include <math.h>
#include <stdio.h>

#include "include.h"

#define ERROR_CHECK(a) do                                \
    {                                                    \
      if ((a) != -1)                                     \
        {                                                \
          return 0.0;                                      \
        }                                                \
    } while (0)

float parse_item(struct token_s *tokens, int *index, int *error_index);
float parse_factor(struct token_s *tokens, int *index, int *error_index);
float parse_term(struct token_s *tokens, int *index, int *error_index);

float parse_item(struct token_s *tokens, int *index, int *error_index)
{
  float result;
  if (tokens[*index].type == NUMBER)
    {
      result = tokens[*index].value;
      (*index)++;
    }
  else if (tokens[*index].type == SYMBOL)
    {
      if (tokens[*index].symbol == '(')
        {
          (*index)++;
          result = parse_expression(tokens, index, error_index);
          if (tokens[*index].symbol != ')')
            {
              *error_index = *index;
              return 0.0;
            }

          (*index)++;
          ERROR_CHECK(*error_index);
        }
      else
        {
          *error_index = *index;
          return 0.0;
        }
    }

  return result;
}

float parse_factor(struct token_s *tokens, int *index, int *error_index)
{
  float result;

  if (tokens[*index].symbol == '-')
    {
      (*index)++;
      result = -1.0 * parse_item(tokens, index, error_index);
    }
  else
    {
      result = parse_item(tokens, index, error_index);
    }

  ERROR_CHECK(*error_index);

  while (tokens[*index].symbol == '^')
    {
      (*index)++;
      result = pow(result, parse_factor(tokens, index, error_index));
      ERROR_CHECK(*error_index);
    }

  return result;
}

float parse_term(struct token_s *tokens, int *index, int *error_index)
{
  float result = parse_factor(tokens, index, error_index);
  ERROR_CHECK(*error_index);

  while (tokens[*index].type == SYMBOL
         && (tokens[*index].symbol == '*'
             || tokens[*index].symbol == '/'))
    {
      if (tokens[*index].symbol == '*')
        {
          (*index)++;
          result *= parse_factor(tokens, index, error_index);
          ERROR_CHECK(*error_index);
        }
      else if (tokens[*index].symbol =='/')
        {
          (*index)++;
          result /= parse_factor(tokens, index, error_index);
          ERROR_CHECK(*error_index);
        }
    }

  return result;
}

float parse_expression(struct token_s *tokens, int *index, int *error_index)
{
  float result = parse_term(tokens, index, error_index);
  ERROR_CHECK(*error_index);

  while (tokens[*index].type == SYMBOL
         && (tokens[*index].symbol == '+'
             || tokens[*index].symbol == '-'))
    {
      if (tokens[*index].symbol == '+')
        {
          (*index)++;
          result += parse_term(tokens, index, error_index);
          ERROR_CHECK(*error_index);
        }
      else if (tokens[*index].symbol == '-')
        {
          (*index)++;
          result -= parse_term(tokens, index, error_index);
          ERROR_CHECK(*error_index);
        }
    }

  return result;
}
