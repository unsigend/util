#include <utest.h>
#include <argparse.h>

#define NAMESPACE_BEGIN {
#define NAMESPACE_END   }

UTEST_TEST_CASE(test_mixed_type1) {
NAMESPACE_BEGIN
    bool flag1 = false, flag2 = false, flag3 = false;
    int num1 = 0, num2 = 0;
    double value = 0.0;
    char *text = NULL;
    
    struct argparse argparse;
    struct argparse_option options[] = {
        OPTION_BOOLEAN('a', "flag1", NULL, &flag1, NULL, 0),
        OPTION_BOOLEAN('b', "flag2", NULL, &flag2, NULL, 0), 
        OPTION_BOOLEAN('c', "flag3", NULL, &flag3, NULL, 0),
        OPTION_INT('n', "num1", NULL, &num1, NULL, 0),
        OPTION_INT('m', "num2", NULL, &num2, NULL, 0),
        OPTION_DOUBLE('d', "value", NULL, &value, NULL, 0),
        OPTION_STRING('s', "text", NULL, &text, NULL, 0),
        OPTION_END()
    };
    argparse_init(&argparse, options, NULL);

    argparse_parse(&argparse, 11, (char*[]){
        "-a", "-n", "42", 
        "--text", "hello",
        "-b", "--num2", "100",
        "-d", "3.14",
        "--flag3", 
    });

    EXPECT_TRUE(flag1);
    EXPECT_TRUE(flag2);
    EXPECT_TRUE(flag3);
    EXPECT_EQUAL_INT(num1, 42);
    EXPECT_EQUAL_INT(num2, 100);
    EXPECT_EQUAL_DOUBLE(value, 3.14);
    EXPECT_EQUAL_STRING(text, "hello");
    flag1 = flag2 = flag3 = false;
    num1 = num2 = 0;
    value = 0.0;
    text = NULL;

    argparse_parse(&argparse, 11, (char*[]){
        "--flag2",
        "-s", "world",
        "--num1", "123",
        "-c",
        "--value", "2.718",
        "-m", "456",
        "--flag1"
    });

    EXPECT_TRUE(flag1);
    EXPECT_TRUE(flag2);
    EXPECT_TRUE(flag3);
    EXPECT_EQUAL_INT(num1, 123);
    EXPECT_EQUAL_INT(num2, 456);
    EXPECT_EQUAL_DOUBLE(value, 2.718);
    EXPECT_EQUAL_STRING(text, "world");
NAMESPACE_END
}
UTEST_TEST_CASE(test_mixed_type2) {
NAMESPACE_BEGIN
    bool flag = false;
    int count = 0;
    double ratio = 0.0;
    char* name = NULL;
    struct argparse argparse;
    struct argparse_option options[] = {
        OPTION_BOOLEAN('f', "flag", NULL, &flag, NULL, 0),
        OPTION_INT('c', "count", NULL, &count, NULL, 0),
        OPTION_DOUBLE('r', "ratio", NULL, &ratio, NULL, 0), 
        OPTION_STRING('n', "name", NULL, &name, NULL, 0),
        OPTION_END()
    };
    argparse_init(&argparse, options, NULL);

    // Test mixing short and long options with negative numbers
    argparse_parse(&argparse, 7, (char*[]){
        "-f",
        "--count", "-42",
        "-r", "-1.234",
        "--name", "test"
    });

    EXPECT_TRUE(flag);
    EXPECT_EQUAL_INT(count, -42);
    EXPECT_EQUAL_DOUBLE(ratio, -1.234);
    EXPECT_EQUAL_STRING(name, "test");
NAMESPACE_END
}

UTEST_TEST_CASE(test_mixed_type3) {
NAMESPACE_BEGIN
    bool verbose = false, debug = false;
    int level = 0;
    char* output = NULL;
    struct argparse argparse;
    struct argparse_option options[] = {
        OPTION_BOOLEAN('v', "verbose", NULL, &verbose, NULL, 0),
        OPTION_BOOLEAN('d', "debug", NULL, &debug, NULL, 0),
        OPTION_INT('l', "level", NULL, &level, NULL, 0),
        OPTION_STRING('o', "output", NULL, &output, NULL, 0),
        OPTION_END()
    };
    argparse_init(&argparse, options, NULL);

    // Test repeated options - last value should be used
    argparse_parse(&argparse, 9, (char*[]){
        "-v",
        "--level", "1",
        "-l", "2",
        "-o", "file1.txt",
        "--output", "file2.txt"
    });

    EXPECT_TRUE(verbose);
    EXPECT_FALSE(debug);
    EXPECT_EQUAL_INT(level, 2);
    EXPECT_EQUAL_STRING(output, "file2.txt");
NAMESPACE_END
}

UTEST_TEST_CASE(test_mixed_type4) {
NAMESPACE_BEGIN
    bool enable = false;
    int width = 0, height = 0;
    double scale = 1.0;
    char* format = NULL;
    struct argparse argparse;
    struct argparse_option options[] = {
        OPTION_BOOLEAN('e', "enable", NULL, &enable, NULL, 0),
        OPTION_INT('w', "width", NULL, &width, NULL, 0),
        OPTION_INT('h', "height", NULL, &height, NULL, 0),
        OPTION_DOUBLE('s', "scale", NULL, &scale, NULL, 0),
        OPTION_STRING('f', "format", NULL, &format, NULL, 0),
        OPTION_END()
    };
    argparse_init(&argparse, options, NULL);

    // Test with very large/small numbers and special characters in strings
    argparse_parse(&argparse, 9, (char*[]){
        "--enable",
        "-w", "999999",
        "-h", "0",
        "--scale", "0.000001",
        "-f", "test@#$%"
    });

    EXPECT_TRUE(enable);
    EXPECT_EQUAL_INT(width, 999999);
    EXPECT_EQUAL_INT(height, 0);
    EXPECT_EQUAL_DOUBLE(scale, 0.000001);
    EXPECT_EQUAL_STRING(format, "test@#$%");
NAMESPACE_END
}
UTEST_TEST_CASE(test_mixed_type5) {
NAMESPACE_BEGIN
    int value = 0;
    double ratio = 0.0;
    char* text = NULL;
    struct argparse argparse;
    struct argparse_option options[] = {
        OPTION_INT('v', "value", NULL, &value, NULL, 0),
        OPTION_DOUBLE('r', "ratio", NULL, &ratio, NULL, 0), 
        OPTION_STRING('t', "text", NULL, &text, NULL, 0),
        OPTION_END()
    };
    argparse_init(&argparse, options, NULL);

    // Test negative numbers
    argparse_parse(&argparse, 6, (char*[]){
        "-v", "-42",
        "-r", "-3.14159",
        "-t", ""
    });

    EXPECT_EQUAL_INT(value, -42);
    EXPECT_EQUAL_DOUBLE(ratio, -3.14159);
    EXPECT_EQUAL_STRING(text, "");

    // Test very large negative numbers and empty string
    argparse_parse(&argparse, 6, (char*[]){
        "--value", "-2147483648",
        "--ratio", "-1.7976931348623157e+308",
        "--text", ""
    });

    EXPECT_EQUAL_INT(value, -2147483648);
    EXPECT_EQUAL_DOUBLE(ratio, -1.7976931348623157e+308);
    EXPECT_EQUAL_STRING(text, "");
NAMESPACE_END
}

UTEST_TEST_CASE(test_mixed_type6) {
NAMESPACE_BEGIN
    bool flag1 = false, flag2 = false;
    int count = 0;
    double amount = 0.0;
    char* name = NULL;
    struct argparse argparse;
    struct argparse_option options[] = {
        OPTION_BOOLEAN('a', "flag1", NULL, &flag1, NULL, 0),
        OPTION_BOOLEAN('b', "flag2", NULL, &flag2, NULL, 0),
        OPTION_INT('c', "count", NULL, &count, NULL, 0),
        OPTION_DOUBLE('d', "amount", NULL, &amount, NULL, 0),
        OPTION_STRING('n', "name", NULL, &name, NULL, 0),
        OPTION_END()
    };
    argparse_init(&argparse, options, NULL);

    // Test mixing boolean flags with other types
    argparse_parse(&argparse, 7, (char*[]){
        "-a",
        "-c", "-0",
        "-d", "-0.0",
        "-n", ""
    });

    EXPECT_TRUE(flag1);
    EXPECT_FALSE(flag2);
    EXPECT_EQUAL_INT(count, 0);
    EXPECT_EQUAL_DOUBLE(amount, 0.0);
    EXPECT_EQUAL_STRING(name, "");

    // Test with minimum values and special characters
    argparse_parse(&argparse, 8, (char*[]){
        "--flag1",
        "--flag2", 
        "--count", "-2147483648",
        "--amount", "-2.2250738585072014e-308",
        "--name", "\t\n\r"
    });

    EXPECT_TRUE(flag1);
    EXPECT_TRUE(flag2);
    EXPECT_EQUAL_INT(count, -2147483648);
    EXPECT_EQUAL_DOUBLE(amount, -2.2250738585072014e-308);
    EXPECT_EQUAL_STRING(name, "\t\n\r");
NAMESPACE_END
}

UTEST_TEST_CASE(test_mixed_type7) {
NAMESPACE_BEGIN
    // Test maximum values and overflow handling
    bool flag = false;
    int num = 0;
    double dbl = 0.0;
    char* str = NULL;
    struct argparse argparse;
    struct argparse_option options[] = {
        OPTION_BOOLEAN('f', "flag", NULL, &flag, NULL, 0),
        OPTION_INT('i', "int", NULL, &num, NULL, 0), 
        OPTION_DOUBLE('d', "double", NULL, &dbl, NULL, 0),
        OPTION_STRING('s', "string", NULL, &str, NULL, 0),
        OPTION_END()
    };
    argparse_init(&argparse, options, NULL);

    // Test with maximum values
    argparse_parse(&argparse, 7, (char*[]){
        "-f",
        "-i", "2147483647", // INT_MAX
        "-d", "1.7976931348623157e+308", // DBL_MAX
        "-s", "test"
    });

    EXPECT_TRUE(flag);
    EXPECT_EQUAL_INT(num, 2147483647);
    EXPECT_EQUAL_DOUBLE(dbl, 1.7976931348623157e+308);
    EXPECT_EQUAL_STRING(str, "test");
NAMESPACE_END
}

UTEST_TEST_CASE(test_mixed_type8) {
NAMESPACE_BEGIN
    // Test mixing long and short options in different orders
    bool flag1 = false, flag2 = false;
    int num1 = 0, num2 = 0;
    char* str = NULL;
    struct argparse argparse;
    struct argparse_option options[] = {
        OPTION_BOOLEAN('x', "flag1", NULL, &flag1, NULL, 0),
        OPTION_BOOLEAN('y', "flag2", NULL, &flag2, NULL, 0),
        OPTION_INT('a', "num1", NULL, &num1, NULL, 0),
        OPTION_INT('b', "num2", NULL, &num2, NULL, 0),
        OPTION_STRING('s', "str", NULL, &str, NULL, 0),
        OPTION_END()
    };
    argparse_init(&argparse, options, NULL);

    // Mix short and long options
    argparse_parse(&argparse, 9, (char*[]){
        "-x",
        "--num1", "100",
        "-y",
        "--num2", "200",
        "-s", "short",
        "--flag1"
    });

    EXPECT_TRUE(flag1);
    EXPECT_TRUE(flag2);
    EXPECT_EQUAL_INT(num1, 100);
    EXPECT_EQUAL_INT(num2, 200);
    EXPECT_EQUAL_STRING(str, "short");
NAMESPACE_END
}

UTEST_TEST_CASE(test_mixed_type9) {
NAMESPACE_BEGIN
    // Test handling of special floating point values
    double dbl = 0.0;
    int num = 0;
    char* str = NULL;
    struct argparse argparse;
    struct argparse_option options[] = {
        OPTION_DOUBLE('d', "double", NULL, &dbl, NULL, 0),
        OPTION_INT('i', "int", NULL, &num, NULL, 0),
        OPTION_STRING('s', "string", NULL, &str, NULL, 0),
        OPTION_END()
    };
    argparse_init(&argparse, options, NULL);

    // Test with various number formats
    argparse_parse(&argparse, 6, (char*[]){
        "-d", "1e-10",
        "-i", "+100",
        "-s", "test"    
    });

    EXPECT_EQUAL_DOUBLE(dbl, 1e-10);
    EXPECT_EQUAL_INT(num, 100);
    EXPECT_EQUAL_STRING(str, "test");

    // Test with scientific notation
    argparse_parse(&argparse, 6, (char*[]){
        "--double", "1.23e+5",
        "--int", "-0100",
        "--string", "test2"
    });

    EXPECT_EQUAL_DOUBLE(dbl, 123000.0);
    EXPECT_EQUAL_INT(num, -100);
    EXPECT_EQUAL_STRING(str, "test2");
NAMESPACE_END
}

UTEST_TEST_CASE(test_mixed_type10) {
NAMESPACE_BEGIN
    // Test with empty strings and zero values
    bool flag = false;
    int num = -1;
    double dbl = -1.0;
    char* str = NULL;
    struct argparse argparse;
    struct argparse_option options[] = {
        OPTION_BOOLEAN('f', "flag", NULL, &flag, NULL, 0),
        OPTION_INT('i', "int", NULL, &num, NULL, 0),
        OPTION_DOUBLE('d', "double", NULL, &dbl, NULL, 0),
        OPTION_STRING('s', "string", NULL, &str, NULL, 0),
        OPTION_END()
    };
    argparse_init(&argparse, options, NULL);

    // Test with zero values and empty string
    argparse_parse(&argparse, 7, (char*[]){
        "-f",
        "-i", "0",
        "-d", "0.0",
        "-s", ""
    });

    EXPECT_TRUE(flag);
    EXPECT_EQUAL_INT(num, 0);
    EXPECT_EQUAL_DOUBLE(dbl, 0.0);
    EXPECT_EQUAL_STRING(str, "");
NAMESPACE_END
}

UTEST_TEST_SUITE(test_mixed_types) {
    UTEST_RUN_TEST_CASE(test_mixed_type1);
    UTEST_RUN_TEST_CASE(test_mixed_type2);
    UTEST_RUN_TEST_CASE(test_mixed_type3);
    UTEST_RUN_TEST_CASE(test_mixed_type4);
    UTEST_RUN_TEST_CASE(test_mixed_type5);
    UTEST_RUN_TEST_CASE(test_mixed_type6);
    UTEST_RUN_TEST_CASE(test_mixed_type7);
    UTEST_RUN_TEST_CASE(test_mixed_type8);
    UTEST_RUN_TEST_CASE(test_mixed_type9);
    UTEST_RUN_TEST_CASE(test_mixed_type10);
}
