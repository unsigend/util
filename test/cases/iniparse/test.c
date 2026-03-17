#include "tests/complex.h"
#include "tests/edge.h"
#include "tests/simple.h"

UTEST_SUITE(iniparse)
{
  UTEST_RUNCASE(simple);
  UTEST_RUNCASE(complex);
  UTEST_RUNCASE(edge);
}
