#include <stdlib.h>

#include "include.h"

void tokenize(char *input_string, struct token_s *token_list)
{
  int token_index = 0;
  struct token_s *current_token = &token_list[token_index];
  
  char working_string[MAX_INPUT_LENGTH + 1];
  int working_index = 0;
  
  for (int i = 0; input_string[i] != '\0'; i++)
    {
      char current_char = input_string[i];

      if (current_char == ' ')
        {
          continue;
        }
      else if (current_char == '+' || current_char == '-'
          || current_char == '*' || current_char == '/'
          || current_char == '^' || current_char == '('
          || current_char == ')')
        {
          if (working_index != 0)
            {
              working_string[working_index] = '\0';
              current_token->type = NUMBER;
              char *end = NULL;
              current_token->value = strtof(working_string, &end);
              current_token->symbol = '\0';

              working_index = 0;

              token_index++;
              current_token = &token_list[token_index];
            }
          
          current_token->type = SYMBOL;
          current_token->symbol = current_char;
          current_token->value = 0.0;
          
          token_index++;
          current_token = &token_list[token_index];
        }
      else
        {
          working_string[working_index] = current_char;
          working_index++;
        }
    }

  if (working_index != 0)
    {
      working_string[working_index] = '\0';
      current_token->type = NUMBER;
      char *end = NULL;
      current_token->value = strtof(working_string, &end);
      current_token->symbol = '\0';

      token_index++;
      current_token = &token_list[token_index];
    }
  
  current_token->type = END;
  current_token->symbol = '\0';
  current_token->value = 0.0;
}
