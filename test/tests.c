#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <string.h>
#include <stdlib.h>
#include "../include.h"
#include "../descent.h"

void test_tokenize(void)
{
  char input_string[] = "1+ 20 -300 * 4000/5000^ 60000* ( -1 ) ";
  int max_tokens = strlen(input_string) + 1;
  struct token_s *tokens =
    (struct token_s *)malloc(max_tokens * sizeof(struct token_s));
  tokenize(input_string, tokens);
  CU_ASSERT(tokens[0].value == 1.0);
  CU_ASSERT(tokens[1].symbol == '+');
  CU_ASSERT(tokens[2].value == 20.0);
  CU_ASSERT(tokens[3].symbol == '-');
  CU_ASSERT(tokens[4].value == 300.0);
  CU_ASSERT(tokens[5].symbol == '*');
  CU_ASSERT(tokens[6].value == 4000.0);
  CU_ASSERT(tokens[7].symbol == '/');
  CU_ASSERT(tokens[8].value == 5000.0);
  CU_ASSERT(tokens[9].symbol == '^');
  CU_ASSERT(tokens[10].value == 60000.0);
  CU_ASSERT(tokens[11].symbol == '*');
  CU_ASSERT(tokens[12].symbol == '(');
  CU_ASSERT(tokens[13].symbol == '-');
  CU_ASSERT(tokens[14].value == 1.0);
  CU_ASSERT(tokens[15].symbol == ')');
  free(tokens);
}

void test_evaluate(void)
{
  char input_string_1[] = "2+3*(-3-(-8))^2/10";
  int error_index_1 = -1;
  float result_1 = evaluate_expression_from_string(input_string_1, &error_index_1);
  CU_ASSERT(error_index_1 == -1);
  CU_ASSERT(result_1 == 9.5);

  char input_string_2[] = "-2+3*(-3-(-8))^2/10";
  int error_index_2 = -1;
  float result_2 = evaluate_expression_from_string(input_string_2, &error_index_2);
  CU_ASSERT(error_index_2 == -1);
  CU_ASSERT(result_2 == 5.5);

  char input_string_3[] = "(2+3)*(-3-(-8))^2/10";  
  int error_index_3 = -1;
  float result_3 = evaluate_expression_from_string(input_string_3, &error_index_3);
  CU_ASSERT(error_index_3 == -1);
  CU_ASSERT(result_3 == 12.5);
}

int main()
{
  CU_initialize_registry();
  CU_pSuite suite = CU_add_suite("descent_test_suite", 0, 0);
  CU_add_test(suite, "Test for tokenize()", test_tokenize);
  CU_add_test(suite, "Test for evaluation", test_evaluate);
  CU_basic_run_tests();
  CU_cleanup_registry();
  return 0;
}
