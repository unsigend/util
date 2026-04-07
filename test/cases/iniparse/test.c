#include "tests/complex.h"
#include "tests/edge.h"
#include "tests/simple.h"
#include "tests/write.h"

UTEST_SUITE(iniparse)
{
  UTEST_RUNCASE(simple);
  UTEST_RUNCASE(complex);
  UTEST_RUNCASE(edge);
  UTEST_RUNCASE(modify);
  UTEST_RUNCASE(create);
  UTEST_RUNCASE(persist);
  UTEST_RUNCASE(dump);
}
