#include <utest.h>

bool function_always_false(){
    return false;
}
int self_inject(int a){
    return a;
}

UTEST_TEST_CASE(simple_test_case){
    EXPECT_TRUE(!self_inject(0));
}
UTEST_TEST_CASE(another_simple_test_case){
    EXPECT_TRUE(!function_always_false());
}
UTEST_TEST_SUITE(simple_test_suite){
    UTEST_RUN_TEST_CASE(simple_test_case);
    UTEST_RUN_TEST_CASE(another_simple_test_case);
}