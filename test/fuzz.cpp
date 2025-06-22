#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
#include "../descent.h"
}

#define MAX_INPUT_SIZE 1000

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size)
{
  int count = (Size > MAX_INPUT_SIZE) ? MAX_INPUT_SIZE : Size;
  uint8_t *copy = (uint8_t *)malloc((count + 1) * sizeof(uint8_t));
  if (copy == NULL)
    {
      return 0;
    }
  memcpy(copy, Data, count);
  copy[count] = '\0';

  int error_index = -1;
  evaluate_expression_from_string((char *)copy, &error_index);
  free(copy);
  return 0;
}
    
