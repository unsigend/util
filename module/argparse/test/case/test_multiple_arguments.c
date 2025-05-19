#include <utest.h>
#include <argparse.h>
#define NAMESPACE_BEGIN {
#define NAMESPACE_END   }

UTEST_TEST_CASE(argparse_callback_multiple_arguments){
NAMESPACE_BEGIN
    const char ** string = NULL;
    int array_size = 0;
    struct argparse argparse;
    struct argparse_option options[] = {
        OPTION_STRING('s', "string", NULL, &string, argparse_callback_multiple_arguments, (intptr_t)&array_size),
        OPTION_END()
    };
    argparse_init(&argparse, options, NULL);
    argparse_parse(&argparse, 3, (char*[]){"-s", "hello", "world"});
    EXPECT_EQUAL_INT(array_size, 2);
    EXPECT_NOT_NULL(string);
    EXPECT_EQUAL_STRING(string[0], "hello");
    EXPECT_EQUAL_STRING(string[1], "world");
NAMESPACE_END
NAMESPACE_BEGIN
    const char ** string = NULL;
    bool flag = false;
    int array_size = 0;
    struct argparse argparse;
    struct argparse_option options[] = {
        OPTION_BOOLEAN('f', "flag", NULL, &flag, NULL, 0),
        OPTION_STRING('s', "string", NULL, &string, argparse_callback_multiple_arguments, (intptr_t)&array_size),
        OPTION_END()
    };
    argparse_init(&argparse, options, NULL);
    argparse_parse(&argparse, 4, (char*[]){"-s", "hello", "world", "-f"});
    EXPECT_EQUAL_INT(array_size, 2);
    EXPECT_NOT_NULL(string);
    EXPECT_EQUAL_STRING(string[0], "hello");
    EXPECT_EQUAL_STRING(string[1], "world");
    EXPECT_EQUAL_INT(flag, true);
NAMESPACE_END
NAMESPACE_BEGIN
    const char ** string1 = NULL;
    const char ** string2 = NULL;
    int array_size1 = 0;
    int array_size2 = 0;
    struct argparse argparse;
    struct argparse_option options[] = {
        OPTION_STRING('s', "string1", NULL, &string1, argparse_callback_multiple_arguments, (intptr_t)&array_size1),
        OPTION_STRING('t', "string2", NULL, &string2, argparse_callback_multiple_arguments, (intptr_t)&array_size2),
        OPTION_END()
    };
    argparse_init(&argparse, options, NULL);
    argparse_parse(&argparse, 7, (char*[]){"-s", "hello", "world", "-t", "foo", "bar", "baz"});
    EXPECT_EQUAL_INT(array_size1, 2);
    EXPECT_EQUAL_INT(array_size2, 3);
    EXPECT_NOT_NULL(string1);
    EXPECT_NOT_NULL(string2);
    EXPECT_EQUAL_STRING(string1[0], "hello");
    EXPECT_EQUAL_STRING(string1[1], "world");
    EXPECT_EQUAL_STRING(string2[0], "foo"); 
    EXPECT_EQUAL_STRING(string2[1], "bar");
    EXPECT_EQUAL_STRING(string2[2], "baz");
NAMESPACE_END
NAMESPACE_BEGIN
    const char ** string1 = NULL;
    const char ** string2 = NULL;
    int array_size1 = 0;
    int array_size2 = 0;
    struct argparse argparse;
    struct argparse_option options[] = {
        OPTION_STRING('s', "string1", NULL, &string1, argparse_callback_multiple_arguments, (intptr_t)&array_size1),
        OPTION_STRING('t', "string2", NULL, &string2, argparse_callback_multiple_arguments, (intptr_t)&array_size2),
        OPTION_END()
    };
    argparse_init(&argparse, options, NULL);
    argparse_parse(&argparse, 6, (char*[]){"--string1", "test1", "--string2", "test2", "test3", "test4"});
    EXPECT_EQUAL_INT(array_size1, 1);
    EXPECT_EQUAL_INT(array_size2, 3);
    EXPECT_NOT_NULL(string1);
    EXPECT_NOT_NULL(string2);
    EXPECT_EQUAL_STRING(string1[0], "test1");
    EXPECT_EQUAL_STRING(string2[0], "test2");
    EXPECT_EQUAL_STRING(string2[1], "test3");
    EXPECT_EQUAL_STRING(string2[2], "test4");
NAMESPACE_END
NAMESPACE_BEGIN
    const char ** string = NULL;
    int array_size = 0;
    struct argparse argparse;
    struct argparse_option options[] = {
        OPTION_STRING('s', "string", NULL, &string, argparse_callback_multiple_arguments, (intptr_t)&array_size),
        OPTION_END()
    };
    argparse_init(&argparse, options, NULL);
    argparse_parse(&argparse, 2, (char*[]){"--string", ""});
    EXPECT_EQUAL_INT(array_size, 1);
    EXPECT_NOT_NULL(string);
    EXPECT_EQUAL_STRING(string[0], "");
NAMESPACE_END

NAMESPACE_BEGIN
    const char ** string = NULL; 
    int array_size = 0;
    struct argparse argparse;
    struct argparse_option options[] = {
        OPTION_STRING('s', "string", NULL, &string, argparse_callback_multiple_arguments, (intptr_t)&array_size),
        OPTION_END()
    };
    argparse_init(&argparse, options, NULL);
    argparse_parse(&argparse, 4, (char*[]){"--string", "test", "-s", "another"});
    EXPECT_EQUAL_INT(array_size, 1);
    EXPECT_NOT_NULL(string);
    EXPECT_EQUAL_STRING(string[0], "another");

NAMESPACE_END

NAMESPACE_BEGIN
    const char ** string1 = NULL;
    const char ** string2 = NULL;
    int array_size1 = 0;
    int array_size2 = 0;
    struct argparse argparse;
    struct argparse_option options[] = {
        OPTION_STRING('s', "string1", NULL, &string1, argparse_callback_multiple_arguments, (intptr_t)&array_size1),
        OPTION_STRING('t', "string2", NULL, &string2, argparse_callback_multiple_arguments, (intptr_t)&array_size2),
        OPTION_END()
    };
    argparse_init(&argparse, options, NULL);
    argparse_parse(&argparse, 8, (char*[]){"--string1", "a1", "-t", "b1", "b2", "-s", "a2", "a3"});
    EXPECT_EQUAL_INT(array_size1, 2);
    EXPECT_EQUAL_INT(array_size2, 2);
    EXPECT_NOT_NULL(string1);
    EXPECT_NOT_NULL(string2);
    EXPECT_EQUAL_STRING(string1[0], "a2");
    EXPECT_EQUAL_STRING(string1[1], "a3");
    EXPECT_EQUAL_STRING(string2[0], "b1");
    EXPECT_EQUAL_STRING(string2[1], "b2");
NAMESPACE_END

}

UTEST_TEST_SUITE(test_callback_functions){
    UTEST_RUN_TEST_CASE(argparse_callback_multiple_arguments);
}