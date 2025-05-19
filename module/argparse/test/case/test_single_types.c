#include <utest.h>
#include <argparse.h>

#define NAMESPACE_BEGIN {
#define NAMESPACE_END   }

UTEST_TEST_CASE(parse_bool){
NAMESPACE_BEGIN
    bool force = false;
    struct argparse argparse;
    struct argparse_option option_list[] = {
        OPTION_BOOLEAN('f', "force", NULL, &force, NULL, 0),
        OPTION_END()
    };
    argparse_init(&argparse, option_list, NULL);
    argparse_parse(&argparse, 1, (char*[]){"-f"});
    EXPECT_TRUE(force);

    argparse_parse(&argparse, 1, (char*[]){"-f", "-f"});
    EXPECT_TRUE(force);

    argparse_parse(&argparse, 1, (char*[]){"-f", "-f", "-f"});
    EXPECT_TRUE(force);

    argparse_parse(&argparse, 1, (char*[]){"-f", "-f", "-f", "-f"});
    EXPECT_TRUE(force);
NAMESPACE_END
    bool verbose = false;
    bool quiet = false;
    struct argparse argparse_mixed;
    struct argparse_option mixed_options[] = {
        OPTION_BOOLEAN('v', "verbose", NULL, &verbose, NULL, 0),
        OPTION_BOOLEAN('q', "quiet", NULL, &quiet, NULL, 0), 
        OPTION_END()
    };

    argparse_init(&argparse_mixed, mixed_options, NULL);
    argparse_parse(&argparse_mixed, 2, (char*[]){"-v", "--quiet"});
    EXPECT_TRUE(verbose);
    EXPECT_TRUE(quiet);

    verbose = false;
    quiet = false;
    argparse_parse(&argparse_mixed, 2, (char*[]){ "--verbose", "-q"});
    EXPECT_TRUE(verbose);
    EXPECT_TRUE(quiet);

    verbose = false;
    quiet = false;
    argparse_parse(&argparse_mixed, 4, (char*[]){ "-v", "--quiet", "--verbose", "-q"});
    EXPECT_TRUE(verbose);
    EXPECT_TRUE(quiet);
}
UTEST_TEST_CASE(parse_int){
NAMESPACE_BEGIN
    int number = 0;
    struct argparse argparse;
    struct argparse_option option_list[] = {
        OPTION_INT('n', "number", NULL, &number, NULL, 0),
        OPTION_END()
    };
    argparse_init(&argparse, option_list, NULL);
    argparse_parse(&argparse, 2, (char*[]){"-n", "10"});
    EXPECT_EQUAL_INT(number, 10);

    argparse_parse(&argparse, 4, (char*[]){"-n", "10", "-n", "20"});
    EXPECT_EQUAL_INT(number, 20);
NAMESPACE_END
NAMESPACE_BEGIN
    int number = 0;
    struct argparse argparse_mixed;
    struct argparse_option mixed_options[] = {
        OPTION_INT('n', "number", NULL, &number, NULL, 0),
        OPTION_END()
    };
    argparse_init(&argparse_mixed, mixed_options, NULL);
    argparse_parse(&argparse_mixed, 2, (char*[]){"-n", "10"});
    EXPECT_EQUAL_INT(number, 10);

    argparse_parse(&argparse_mixed, 4, (char*[]){"-n", "10", "-n", "20"});
    EXPECT_EQUAL_INT(number, 20);
NAMESPACE_END
NAMESPACE_BEGIN
    int number = 0;
    struct argparse argparse_fixed;
    struct argparse_option fixed_options[] = {
        OPTION_INT('o', "one", NULL, &number, NULL, 0), 
        OPTION_END()
    };
    argparse_init(&argparse_fixed, fixed_options, NULL);
    argparse_parse(&argparse_fixed, 2, (char*[]){"-o", "10"});
    EXPECT_EQUAL_INT(number, 10);

    argparse_parse(&argparse_fixed, 2, (char*[]){"--one", "20"});
    EXPECT_EQUAL_INT(number, 20);

    argparse_parse(&argparse_fixed, 4, (char*[]){"-o", "30", "--one", "40"});
    EXPECT_EQUAL_INT(number, 40);
NAMESPACE_END
NAMESPACE_BEGIN
    int number = 0;
    struct argparse argparse_fixed;
    struct argparse_option fixed_options[] = {
        OPTION_INT('o', "one", NULL, &number, NULL, 0), 
        OPTION_INT('t', "two", NULL, &number, NULL, 0), 
        OPTION_END()
    };
    argparse_init(&argparse_fixed, fixed_options, NULL);
    argparse_parse(&argparse_fixed, 2, (char*[]){"-o", "10"});
    EXPECT_EQUAL_INT(number, 10);

    argparse_parse(&argparse_fixed, 2, (char*[]){"--one", "20"});
    EXPECT_EQUAL_INT(number, 20);

    argparse_parse(&argparse_fixed, 6, (char*[]){"-o", "30", "--one", "40", "-t", "50"});
    EXPECT_EQUAL_INT(number, 50);

    argparse_parse(&argparse_fixed, 4, (char*[]){"-o", "30", "--one", "40", "-t", "50", "--two", "60"});
    EXPECT_EQUAL_INT(number, 40);

    argparse_parse(&argparse_fixed, 6, (char*[]){"-o", "30", "--one", "40", "-t", "50", "--two", "60"});
    EXPECT_EQUAL_INT(number, 50);

    argparse_parse(&argparse_fixed, 8, (char*[]){"-o", "30", "--one", "40", "-t", "50", "--two", "60"});
    EXPECT_EQUAL_INT(number, 60);
NAMESPACE_END
}
UTEST_TEST_CASE(parse_double){
NAMESPACE_BEGIN
    double number = 0;
    struct argparse argparse;
    struct argparse_option option_list[] = {
        OPTION_DOUBLE('n', "number", NULL, &number, NULL, 0),
        OPTION_END()
    };
    argparse_init(&argparse, option_list, NULL);
    argparse_parse(&argparse, 2, (char*[]){"-n", "10.5"});
    EXPECT_EQUAL_DOUBLE(number, 10.5);

    argparse_parse(&argparse, 4, (char*[]){"-n", "10.5", "-n", "20.5"});
    EXPECT_EQUAL_DOUBLE(number, 20.5);
NAMESPACE_END
NAMESPACE_BEGIN
    double number = 0;
    struct argparse argparse_mixed;
    struct argparse_option mixed_options[] = {
        OPTION_DOUBLE('n', "number", NULL, &number, NULL, 0),
        OPTION_END()
    };
    argparse_init(&argparse_mixed, mixed_options, NULL);
    argparse_parse(&argparse_mixed, 2, (char*[]){"-n", "10.5"});
    EXPECT_EQUAL_DOUBLE(number, 10.5);

    argparse_parse(&argparse_mixed, 4, (char*[]){"-n", "10.5", "--number", "20.5"});
    EXPECT_EQUAL_DOUBLE(number, 20.5);
NAMESPACE_END
}
UTEST_TEST_CASE(parse_string){
NAMESPACE_BEGIN
    char* string = NULL;
    struct argparse argparse;
    struct argparse_option option_list[] = {
        OPTION_STRING('s', "string", NULL, &string, NULL, 0),
        OPTION_END()
    };
    argparse_init(&argparse, option_list, NULL);
    argparse_parse(&argparse, 2, (char*[]){"-s", "hello"});
    EXPECT_EQUAL_STRING(string, "hello");
NAMESPACE_END
NAMESPACE_BEGIN
    char* string = NULL;
    struct argparse argparse_mixed;
    struct argparse_option mixed_options[] = {
        OPTION_STRING('s', "string", NULL, &string, NULL, 0),
        OPTION_END()
    };
    argparse_init(&argparse_mixed, mixed_options, NULL);
    argparse_parse(&argparse_mixed, 2, (char*[]){"--string", "hello"});
    EXPECT_EQUAL_STRING(string, "hello");
NAMESPACE_END
NAMESPACE_BEGIN
    char* string = NULL;
    struct argparse argparse_mixed;
    struct argparse_option mixed_options[] = {
        OPTION_STRING('s', "string", NULL, &string, NULL, 0),
        OPTION_END()
    };
    argparse_init(&argparse_mixed, mixed_options, NULL);
    argparse_parse(&argparse_mixed, 2, (char*[]){"-s", "hello"});
    EXPECT_EQUAL_STRING(string, "hello");

    argparse_parse(&argparse_mixed, 4, (char*[]){"-s", "hello", "--string", "world"});
    EXPECT_EQUAL_STRING(string, "world");
NAMESPACE_END
}
UTEST_TEST_SUITE(test_single_types){
    UTEST_RUN_TEST_CASE(parse_bool);
    UTEST_RUN_TEST_CASE(parse_int);
    UTEST_RUN_TEST_CASE(parse_double);
    UTEST_RUN_TEST_CASE(parse_string);
}