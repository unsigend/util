// Using Utest library

#include <utest.h>
#include <stdio.h>

extern UTEST_TEST_SUITE(simple_test_suite);
extern UTEST_TEST_SUITE(complex_test_suite);
extern UTEST_TEST_SUITE(error_display);

int main(int argc, char * argv[]){
    UTEST_BEGIN();

    UTEST_CLEAR_FLAG(UTEST_FLAG_STYLE_FULL);

    UTEST_RUN_TEST_SUITE(simple_test_suite);
    UTEST_RUN_TEST_SUITE(complex_test_suite);
    // Uncomment the following line to run the error display test suite
    UTEST_RUN_TEST_SUITE(error_display);

    UTEST_END();
    return 0;
}