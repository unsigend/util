#include <utest.h>

static char mychar() { return 'b'; }

UTEST_TEST_CASE(char_assertion) {
  EXPECT_EQUAL_CHAR('a', 'a');
  EXPECT_NOT_EQUAL_CHAR(mychar(), 'c');
  EXPECT_GREATER_CHAR('b', 'a');
  EXPECT_GREATER_EQUAL_CHAR('b', 'a');
  EXPECT_LESS_CHAR('a', 'b');
  EXPECT_LESS_EQUAL_CHAR('a', 'b');
}
UTEST_TEST_SUITE(char_test_suite) { UTEST_RUN_TEST_CASE(char_assertion); }