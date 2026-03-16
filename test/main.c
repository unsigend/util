#include <stdbool.h>
#include <utest.h>

UTEST_CASE(case1)
{
  EXPECT_TRUE(1 == 1);
  EXPECT_TRUE(1 == 1);
}

UTEST_CASE(case2) { EXPECT_FALSE(0); }

UTEST_SUITE(suite)
{
  UTEST_RUNCASE(case1);
  UTEST_RUNCASE(case2);
}

int main()
{
  UTEST_INIT(0);

  UTEST_ADDSUITE(suite);
  UTEST_RUNSUITES();

  UTEST_FINI();
  return 0;
}