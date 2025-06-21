#include <string.h>
#include <stdlib.h>
#include "include.h"

void print_tokens(struct token_s *tokens)
{
  int token_index = 0;
  while (tokens[token_index].type != END)
    {
      struct token_s current_token = tokens[token_index];
      enum token_type_e type = current_token.type;
      if (type == NUMBER)
        {
          printf("Number token: %f\n", current_token.value);
        }
      else if (type == SYMBOL)
        {
          printf("Symbol token: %c\n", current_token.symbol);
        }
      
      token_index++;
    }

  printf("End token\n");
}

float evaluate_expression_from_string(char *string, int *error_index)
{
  int string_len = strlen(string) + 1;

  /* string_len is the maximum number of tokens present */
  
  struct token_s *tokens =
    (struct token_s *)malloc(string_len * sizeof(struct token_s));

  tokenize(string, tokens);
  int index = 0;
  float result = parse_expression(tokens, &index, error_index);
  if (*error_index >= 0)
    {
      result = 0.0;
    }

  free(tokens);

  return result;
}
