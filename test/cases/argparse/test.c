#include "funcs/cb_multi.h"
#include "funcs/int.h"
#include "funcs/mixed.h"
#include "funcs/multi.h"
#include "funcs/single.h"
#include <argparse.h>
#include <utest.h>

UTEST_TEST_SUITE(argparse)
{
  UTEST_RUN_TEST_CASE(int);
  UTEST_RUN_TEST_CASE(cb_multi);
  UTEST_RUN_TEST_CASE(single);
  UTEST_RUN_TEST_CASE(multi);
  UTEST_RUN_TEST_CASE(mixed);
}
