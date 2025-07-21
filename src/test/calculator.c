#include <stdio.h>
#include <stdlib.h>

#include "../descent.h"

#define MAX_INPUT_LENGTH 40

void main(void)
{
  while (1)
    {
      char input_string[MAX_INPUT_LENGTH + 1];
      scanf("%s", input_string);
      if (input_string[MAX_INPUT_LENGTH] != '\0')
        {
          printf("Input is too long!/n");
          continue;
        }

      int error_index = -1;
      float result = evaluate_expression_from_string(input_string, &error_index);
      if (error_index != -1)
        {
          printf("Error at token index %d\n", error_index);
        }
      else
        {
          printf("Result: %f\n", result);
        }
    }
}
