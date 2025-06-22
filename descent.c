#include <string.h>
#include <stdlib.h>
#include "include.h"

float evaluate_expression_from_string(char *string, int *error_index)
{
  int string_len = strlen(string) + 1;

  /* string_len + 1 is the maximum number of tokens present */
  
  struct token_s *tokens =
    (struct token_s *)malloc((string_len + 1) * sizeof(struct token_s));

  if (tokenize(string, string_len, tokens) < 0)
    {
      *error_index = 0;
      return 0.0;
    }
  
  int index = 0;
  float result = parse_expression(tokens, &index, error_index);
  if (*error_index >= 0)
    {
      result = 0.0;
    }

  free(tokens);

  return result;
}
