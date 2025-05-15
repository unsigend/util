#include <utest.h>
#include <stdbool.h>

// all of the assertions in this file are expected to fail
UTEST_TEST_CASE(pointer_assertion){
    int * ptr1 = NULL;
    int value = 0;
    int * ptr2 = &value;
    EXPECT_NULL(ptr2);
    EXPECT_NOT_NULL(ptr1);
}

UTEST_TEST_CASE(boolean_assertion){
    bool true_value = true;
    bool false_value = false;
    EXPECT_TRUE(false_value);
    EXPECT_FALSE(true_value);
}
UTEST_TEST_CASE(string_assertion){
    const char *str1 = "hello world";
    const char *str2 = "hello";
    const char *str3 = "hello world";
    EXPECT_EQUAL_STRING(str1, str2);
    EXPECT_NOT_EQUAL_STRING(str1, str3);
    EXPECT_GREATER_STRING(str2, str1);
    EXPECT_GREATER_EQUAL_STRING(str2, str1);
    EXPECT_LESS_STRING(str3, str2);
    EXPECT_LESS_EQUAL_STRING(str1, str2);
}
UTEST_TEST_SUITE(error_display){
    UTEST_CLEAR_FLAG(UTEST_FLAG_STOP_ON_FAILURE);
    //UTEST_RUN_TEST_CASE(pointer_assertion);
    //UTEST_RUN_TEST_CASE(boolean_assertion);
    // UTEST_RUN_TEST_CASE(string_assertion);
    UTEST_SET_FLAG(UTEST_FLAG_STOP_ON_FAILURE);
}