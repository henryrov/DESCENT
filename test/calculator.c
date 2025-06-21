#include <stdio.h>
#include <stdlib.h>

#include "../include.h"
#include "../descent.h"

void main(void)
{
  while (1)
    {
      char input_string[MAX_INPUT_LENGTH + 1];
      scanf("%s", input_string);
      if (input_string[MAX_INPUT_LENGTH] != '\0')
        {
          printf("Input is too long!");
          continue;
        }
      
      int error_index = -1;
      float result = parse_expression_from_string(input_string, &error_index);
      if (error_index != -1)
        {
          printf("Error at index %d\n", error_index);
        }
      else
        {
          printf("Result: %f\n", result);
        }
    }
}
