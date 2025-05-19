#include <utest.h>
#include <argparse.h>

#define NAMESPACE_BEGIN {
#define NAMESPACE_END   }

UTEST_TEST_CASE(parse_multiple_bool) {
NAMESPACE_BEGIN
    bool flag1 = false, flag2 = false, flag3 = false;
    struct argparse argparse;
    struct argparse_option options[] = {
        OPTION_BOOLEAN('x', "flag1", NULL, &flag1, NULL, 0),
        OPTION_BOOLEAN('y', "flag2", NULL, &flag2, NULL, 0),
        OPTION_BOOLEAN('z', "flag3", NULL, &flag3, NULL, 0),
        OPTION_END()
    };
    argparse_init(&argparse, options, NULL);
    
    argparse_parse(&argparse, 3, (char*[]){"-x", "-y", "-z"});
    EXPECT_TRUE(flag1);
    EXPECT_TRUE(flag2);
    EXPECT_TRUE(flag3);

    flag1 = flag2 = flag3 = false;
    argparse_parse(&argparse, 3, (char*[]){"--flag1", "--flag2", "--flag3"});
    EXPECT_TRUE(flag1);
    EXPECT_TRUE(flag2);
    EXPECT_TRUE(flag3);
NAMESPACE_END
}
UTEST_TEST_CASE(parse_multiple_int) {
NAMESPACE_BEGIN
    int num1 = 0, num2 = 0, num3 = 0;
    struct argparse argparse;
    struct argparse_option options[] = {
        OPTION_INT('a', "first", NULL, &num1, NULL, 0),
        OPTION_INT('b', "second", NULL, &num2, NULL, 0),
        OPTION_INT('c', "third", NULL, &num3, NULL, 0),
        OPTION_END()
    };
    argparse_init(&argparse, options, NULL);
    
    argparse_parse(&argparse, 6, (char*[]){"-a", "10", "-b", "20", "-c", "30"});
    EXPECT_EQUAL_INT(num1, 10);
    EXPECT_EQUAL_INT(num2, 20); 
    EXPECT_EQUAL_INT(num3, 30);

    argparse_parse(&argparse, 6, (char*[]){"--first", "100", "--second", "200", "--third", "300"});
    EXPECT_EQUAL_INT(num1, 100);
    EXPECT_EQUAL_INT(num2, 200);
    EXPECT_EQUAL_INT(num3, 300);
NAMESPACE_END
}

UTEST_TEST_CASE(parse_multiple_double) {
NAMESPACE_BEGIN
    double val1 = 0.0, val2 = 0.0, val3 = 0.0;
    struct argparse argparse;
    struct argparse_option options[] = {
        OPTION_DOUBLE('d', "double1", NULL, &val1, NULL, 0),
        OPTION_DOUBLE('e', "double2", NULL, &val2, NULL, 0),
        OPTION_DOUBLE('f', "double3", NULL, &val3, NULL, 0),
        OPTION_END()
    };
    argparse_init(&argparse, options, NULL);
    
    argparse_parse(&argparse, 6, (char*[]){"-d", "1.5", "-e", "2.5", "-f", "3.5"});
    EXPECT_EQUAL_DOUBLE(val1, 1.5);
    EXPECT_EQUAL_DOUBLE(val2, 2.5);
    EXPECT_EQUAL_DOUBLE(val3, 3.5);

    argparse_parse(&argparse, 6, (char*[]){"--double1", "10.5", "--double2", "20.5", "--double3", "30.5"});
    EXPECT_EQUAL_DOUBLE(val1, 10.5);
    EXPECT_EQUAL_DOUBLE(val2, 20.5);
    EXPECT_EQUAL_DOUBLE(val3, 30.5);
NAMESPACE_END
}

UTEST_TEST_CASE(parse_multiple_string) {
NAMESPACE_BEGIN
    char *str1 = NULL, *str2 = NULL, *str3 = NULL;
    struct argparse argparse;
    struct argparse_option options[] = {
        OPTION_STRING('p', "path", NULL, &str1, NULL, 0),
        OPTION_STRING('n', "name", NULL, &str2, NULL, 0),
        OPTION_STRING('v', "value", NULL, &str3, NULL, 0),
        OPTION_END()
    };
    argparse_init(&argparse, options, NULL);
    
    argparse_parse(&argparse, 6, (char*[]){"-p", "/tmp", "-n", "test", "-v", "data"});
    EXPECT_EQUAL_STRING(str1, "/tmp");
    EXPECT_EQUAL_STRING(str2, "test");
    EXPECT_EQUAL_STRING(str3, "data");

    argparse_parse(&argparse, 6, (char*[]){"--path", "/usr", "--name", "config", "--value", "settings"});
    EXPECT_EQUAL_STRING(str1, "/usr");
    EXPECT_EQUAL_STRING(str2, "config");
    EXPECT_EQUAL_STRING(str3, "settings");
NAMESPACE_END
}

UTEST_TEST_SUITE(test_multiple_types){
    UTEST_RUN_TEST_CASE(parse_multiple_bool);
    UTEST_RUN_TEST_CASE(parse_multiple_int);
    UTEST_RUN_TEST_CASE(parse_multiple_double);
    UTEST_RUN_TEST_CASE(parse_multiple_string);
}