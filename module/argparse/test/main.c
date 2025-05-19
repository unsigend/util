#include <utest.h>

extern UTEST_TEST_SUITE(test_single_types);
extern UTEST_TEST_SUITE(test_multiple_types);
extern UTEST_TEST_SUITE(test_mixed_types);
extern UTEST_TEST_SUITE(test_callback_functions);
extern UTEST_TEST_SUITE(integrate_test);

int main(int argc, char *argv[]){
    UTEST_BEGIN();
    UTEST_CLEAR_FLAG(UTEST_FLAG_STYLE_FULL);

    UTEST_RUN_TEST_SUITE(test_single_types);
    UTEST_RUN_TEST_SUITE(test_multiple_types);
    UTEST_RUN_TEST_SUITE(test_mixed_types);
    UTEST_RUN_TEST_SUITE(test_callback_functions);
    UTEST_RUN_TEST_SUITE(integrate_test);
    UTEST_END();
    return 0;
}