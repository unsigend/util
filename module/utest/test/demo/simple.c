#include <utest.h>

UTEST_TEST_CASE(simple_test_case){

}
UTEST_TEST_CASE(another_simple_test_case){

}
UTEST_TEST_SUITE(simple_test_suite){
    UTEST_RUN_TEST_CASE(simple_test_case);
    UTEST_RUN_TEST_CASE(another_simple_test_case);
}