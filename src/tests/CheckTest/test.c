#include "test.h"

#include <stdio.h>

void run_test_case(Suite *ptr_test) {
  static int count_test = 1;

  if (count_test > 0) putchar('\n');
  printf("%s%d\n", "CURRENT TEST: ", count_test);
  count_test++;
  SRunner *srun = srunner_create(ptr_test);
  srunner_run_all(srun, CK_NORMAL);
  srunner_free(srun);
}

void run_tests() {
  Suite *case_tests[] = {test_model(), test_fsm(), type_test(), NULL};
  for (Suite **ptr_test = case_tests; *ptr_test != NULL; ptr_test++)
    run_test_case(*ptr_test);
}

int main() {
  run_tests();
  // printf("Hello, world!\n");
  return 0;
}