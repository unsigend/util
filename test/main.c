/* Test runner for util library
   Usage: ./test [module] [nthreads] */

#include <stdlib.h>
#include <utest.h>

#define NTHREADS 5

extern UTEST_SUITE(iniparse);

int main(int argc, char *argv[])
{
  int nthreads = NTHREADS;
  UTEST_INIT(UTF_STOPONASS | UTF_STOPONCASE | UTF_SHOWSUITE);

  UTEST_ADDSUITE(iniparse);

  if (argc > 1) {
    if (argc >= 3) {
      nthreads = atoi(argv[2]);
      if (nthreads <= 0) {
        fprintf(stderr, "invalid number of threads: %s\n", argv[2]);
        return EXIT_FAILURE;
      }
    }
    if (UTEST_RUNSUITE(argv[1]) == -1) {
      UTEST_SHOWSUITES();
      return EXIT_FAILURE;
    }
  } else
    UTEST_RUNSUITES_THREAD(nthreads);

  UTEST_FINI();
  return EXIT_SUCCESS;
}
