#ifndef INCLUDE_H
#define INCLUDE_H

#define MAX_INPUT_LENGTH 20

/* Types */

enum token_type_e
{
  NUMBER,
  SYMBOL,
  END
};

struct token_s
{
  enum token_type_e type;
  float value;
  char symbol;
};

/* Functions */

void tokenize(char *input_string, struct token_s *token_list);
float parse_expression(struct token_s *tokens, int *index, int *error_index);

#endif
