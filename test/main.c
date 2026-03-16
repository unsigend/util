#include "utest/core.h"
#include <stdbool.h>
#include <stdlib.h>
#include <utest.h>

int always_true() { return 1; }
int always_false() { return 0; }
int random_int() { return rand() % 100; }

UTEST_CASE(pass1) { EXPECT_TRUE(1 == 1); }
UTEST_CASE(pass2) { EXPECT_TRUE(1 == 1); }
UTEST_CASE(pass3) { EXPECT_TRUE(1 == 1); }
UTEST_CASE(pass4) { EXPECT_TRUE(1 == 1); }
UTEST_CASE(pass5) { EXPECT_TRUE(1 == 1); }
UTEST_CASE(pass6) { EXPECT_TRUE(1 == 1); }
UTEST_CASE(pass7) { EXPECT_TRUE(1 == 1); }
UTEST_CASE(pass8) { EXPECT_TRUE(1 == 1); }

UTEST_CASE(fail1)
{
  EXPECT_NULL(0x80000000);
  EXPECT_EQ_INT(random_int(), 50);
  EXPECT_EQ_CHAR('a', 'b');
  const char *str = "hello";
  EXPECT_EQ_STR(str, "world");
  EXPECT_GT_INT(random_int(), 1000);
}

UTEST_CASE(fail2)
{
  EXPECT_FALSE(always_true());
  EXPECT_FALSE(1);
  EXPECT_FALSE(always_true());
  EXPECT_FALSE(always_true());
}

UTEST_SUITE(passsuite)
{
  UTEST_RUNCASE(pass1);
  UTEST_RUNCASE(pass2);
  UTEST_RUNCASE(pass3);
  UTEST_RUNCASE(pass4);
  UTEST_RUNCASE(pass5);
  UTEST_RUNCASE(pass6);
  UTEST_RUNCASE(pass7);
  UTEST_RUNCASE(pass8);
}

UTEST_SUITE(failsuite)
{
  UTEST_RUNCASE(fail1);
  UTEST_RUNCASE(fail2);
}

int main()
{
  UTEST_INIT(0);

  UTEST_ADDSUITE(passsuite);
  UTEST_ADDSUITE(failsuite);
  UTEST_RUNSUITES();

  UTEST_FINI();
  return 0;
}