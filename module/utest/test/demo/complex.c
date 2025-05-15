#include <utest.h>

static const char *str1 = "hello world";
static const char *str2 = "hello";
static const char *str3 = "hello world";

UTEST_TEST_CASE(string_assert){

    EXPECT_EQUAL_STRING(str1, "hello world");
    EXPECT_EQUAL_STRING(str1, str1);

    EXPECT_NOT_EQUAL_STRING("hello world", "hello");
    EXPECT_NOT_EQUAL_STRING(str1, str2);

    EXPECT_GREATER_STRING(str1, str2);
    EXPECT_GREATER_EQUAL_STRING(str1, str3);
    EXPECT_GREATER_EQUAL_STRING(str1, str2);

    EXPECT_LESS_STRING(str2, str1);
    EXPECT_LESS_EQUAL_STRING(str2, str3);
    EXPECT_LESS_EQUAL_STRING(str2, str1);

}
UTEST_TEST_SUITE(complex_test_suite){
    UTEST_RUN_TEST_CASE(string_assert);
}