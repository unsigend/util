/* Main test program. Dispatch suites by argv. If no args, run all.
   Usage: ./test [suite_name] */

#include <stdio.h>
#include <string.h>
#include <utest.h>
#include <utest/core.h>

typedef struct {
  const char *name;
  utest_func_ptr func;
} suite_t;

extern UTEST_TEST_SUITE(argparse);
extern UTEST_TEST_SUITE(iniparse);

static const suite_t suites[] = {
    {"argparse", UTEST_CONCATENATE(UTEST_SUITENAME_PREFIX, argparse)},
    {"iniparse", UTEST_CONCATENATE(UTEST_SUITENAME_PREFIX, iniparse)},
};
static const size_t nsuites = sizeof(suites) / sizeof(suite_t);

int main(int argc, char *argv[])
{
  UTEST_BEGIN();
  UTEST_CLEAR_FLAG(UTEST_FLAG_STYLE_FULL);

  if (argc <= 1) {
    UTEST_CLEAR_FLAG(UTEST_FLAG_SHOW_CASE);
    for (size_t i = 0; i < nsuites; i++)
      UtestRunTestSuite(suites[i].func, suites[i].name);
  } else {
    bool found = false;
    for (size_t i = 0; i < nsuites; i++) {
      if (!strcmp(argv[1], suites[i].name)) {
        UtestRunTestSuite(suites[i].func, suites[i].name);
        found = true;
        break;
      }
    }
    if (!found) {
      int bound = 0;
      fprintf(stdout, "Unknown test suites: %s\n", argv[1]);
      fprintf(stdout, "Available test suites: \n\t");
      for (size_t i = 0; i < nsuites; i++) {
        if (bound == 8) {
          bound = 0;
          fprintf(stdout, "\n\t");
        }
        fprintf(stdout, "%s ", suites[i].name);
        bound++;
      }
      fprintf(stdout, "\n\n");
      return 1;
    }
  }
  UTEST_END();

  return 0;
}
