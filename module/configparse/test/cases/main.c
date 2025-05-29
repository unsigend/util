#include <utest.h>

extern UTEST_TEST_SUITE(file_reading);
extern UTEST_TEST_SUITE(get_value);

// relative path to the util project
const char * simple_filename = "module/configparse/test/cases/INI/simple.ini";
const char * complex_filename = "module/configparse/test/cases/INI/complex.ini";

int main(int argc, char * argv[]){
    (void)argc;
    (void)argv;

    UTEST_BEGIN();
    UTEST_CLEAR_FLAG(UTEST_FLAG_STYLE_FULL);

    UTEST_RUN_TEST_SUITE(file_reading);
    UTEST_RUN_TEST_SUITE(get_value);

    UTEST_END();
    return 0;
}