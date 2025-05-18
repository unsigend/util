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
        OPTION_BOOLEAN('a', "flag1", NULL, &flag1, NULL),
        OPTION_BOOLEAN('b', "flag2", NULL, &flag2, NULL), 
        OPTION_BOOLEAN('c', "flag3", NULL, &flag3, NULL),
        OPTION_INT('n', "num1", NULL, &num1, NULL),
        OPTION_INT('m', "num2", NULL, &num2, NULL),
        OPTION_DOUBLE('d', "value", NULL, &value, NULL),
        OPTION_STRING('s', "text", NULL, &text, NULL),
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
        OPTION_BOOLEAN('f', "flag", NULL, &flag, NULL),
        OPTION_INT('c', "count", NULL, &count, NULL),
        OPTION_DOUBLE('r', "ratio", NULL, &ratio, NULL), 
        OPTION_STRING('n', "name", NULL, &name, NULL),
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
        OPTION_BOOLEAN('v', "verbose", NULL, &verbose, NULL),
        OPTION_BOOLEAN('d', "debug", NULL, &debug, NULL),
        OPTION_INT('l', "level", NULL, &level, NULL),
        OPTION_STRING('o', "output", NULL, &output, NULL),
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
        OPTION_BOOLEAN('e', "enable", NULL, &enable, NULL),
        OPTION_INT('w', "width", NULL, &width, NULL),
        OPTION_INT('h', "height", NULL, &height, NULL),
        OPTION_DOUBLE('s', "scale", NULL, &scale, NULL),
        OPTION_STRING('f', "format", NULL, &format, NULL),
        OPTION_END()
    };
    argparse_init(&argparse, options, NULL);

    // Test with very large/small numbers and special characters in strings
    argparse_parse(&argparse, 10, (char*[]){
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

UTEST_TEST_SUITE(test_mixed_types) {
    UTEST_RUN_TEST_CASE(test_mixed_type1);
    UTEST_RUN_TEST_CASE(test_mixed_type2);
    UTEST_RUN_TEST_CASE(test_mixed_type3);
    UTEST_RUN_TEST_CASE(test_mixed_type4);
}
