#include <utest.h>
#include <argparse.h>
#include <stdio.h>

UTEST_TEST_CASE(integrate_test1) {
    // Test basic types and multiple arguments
    const char *str = NULL;
    const char **str_array = NULL;
    int int_val = 0;
    bool flag = false;
    int array_size = 0;
    double float_val = 0.0;

    struct argparse argparse;
    struct argparse_option options[] = {
        OPTION_STRING('s', "string", "test string option", &str, NULL, 0),
        OPTION_INT('i', "int", "test integer option", &int_val, NULL, 0), 
        OPTION_DOUBLE('f', "float", "test float option", &float_val, NULL, 0),
        OPTION_BOOLEAN('b', "bool", "test boolean flag", &flag, NULL, 0),
        OPTION_STRING('m', "multi", "test multiple arguments", &str_array, argparse_callback_multiple_arguments, (intptr_t)&array_size),
        OPTION_END()
    };

    argparse_init(&argparse, options, NULL);
    argparse_parse(&argparse, 10, (char*[]){
        "--string", "hello",
        "--int", "42", 
        "--float", "3.14",
        "--bool",
        "--multi", "arg1", "arg2"
    });

    EXPECT_EQUAL_STRING(str, "hello");
    EXPECT_EQUAL_INT(int_val, 42);
    EXPECT_EQUAL_DOUBLE(float_val, 3.14);
    EXPECT_TRUE(flag);
    EXPECT_EQUAL_INT(array_size, 2);
    EXPECT_EQUAL_STRING(str_array[0], "arg1"); 
    EXPECT_EQUAL_STRING(str_array[1], "arg2");
}

UTEST_TEST_CASE(integrate_test2) {
    // Test overwriting options
    const char *str = NULL;
    int int_val = 0;
    
    struct argparse argparse;
    struct argparse_option options[] = {
        OPTION_STRING('s', "string", "string that will be overwritten", &str, NULL, 0),
        OPTION_INT('i', "int", "integer that will be overwritten", &int_val, NULL, 0),
        OPTION_END()
    };

    argparse_init(&argparse, options, NULL);
    argparse_parse(&argparse, 6, (char*[]){
        "--string", "first",
        "--string", "second",
        "--int", "123"
    });

    EXPECT_EQUAL_STRING(str, "second");
    EXPECT_EQUAL_INT(int_val, 123);
}

UTEST_TEST_CASE(integrate_test3) {
    // Test mixing short and long options
    const char *str1 = NULL;
    const char *str2 = NULL;
    const char **multi = NULL;
    int array_size = 0;
    bool flag = false;

    struct argparse argparse;
    struct argparse_option options[] = {
        OPTION_STRING('a', "str1", "first string", &str1, NULL, 0),
        OPTION_STRING('b', "str2", "second string", &str2, NULL, 0),
        OPTION_STRING('m', "multi", "multiple args", &multi, argparse_callback_multiple_arguments, (intptr_t)&array_size),
        OPTION_BOOLEAN('f', "flag", "boolean flag", &flag, NULL, 0),
        OPTION_END()
    };

    argparse_init(&argparse, options, NULL);
    argparse_parse(&argparse, 8, (char*[]){
        "-a", "short1",
        "--str2", "long2",
        "-m", "m1", "m2", "-f"
    });

    EXPECT_EQUAL_STRING(str1, "short1");
    EXPECT_EQUAL_STRING(str2, "long2");
    EXPECT_EQUAL_INT(array_size, 2);
    EXPECT_EQUAL_STRING(multi[0], "m1");
    EXPECT_EQUAL_STRING(multi[1], "m2");
    EXPECT_TRUE(flag);
}

UTEST_TEST_CASE(integrate_test4) {
    // Test empty strings and edge cases
    const char *str = NULL;
    const char **multi = NULL;
    int array_size = 0;

    struct argparse argparse;
    struct argparse_option options[] = {
        OPTION_STRING('s', "string", "string option", &str, NULL, 0),
        OPTION_STRING('m', "multi", "multiple args", &multi, argparse_callback_multiple_arguments, (intptr_t)&array_size),
        OPTION_END()
    };

    argparse_init(&argparse, options, NULL);
    argparse_parse(&argparse, 4, (char*[]){
        "--string", "",
        "-m", ""
    });

    EXPECT_EQUAL_STRING(str, "");
    EXPECT_EQUAL_INT(array_size, 1);
    EXPECT_EQUAL_STRING(multi[0], "");
}

UTEST_TEST_CASE(integrate_test5) {
    // Test multiple string arrays
    const char **array1 = NULL;
    const char **array2 = NULL;
    int size1 = 0;
    int size2 = 0;

    struct argparse argparse;
    struct argparse_option options[] = {
        OPTION_STRING('a', "array1", "first array", &array1, argparse_callback_multiple_arguments, (intptr_t)&size1),
        OPTION_STRING('b', "array2", "second array", &array2, argparse_callback_multiple_arguments, (intptr_t)&size2),
        OPTION_END()
    };

    argparse_init(&argparse, options, NULL);
    argparse_parse(&argparse, 7, (char*[]){
        "-a", "a1", "a2",
        "-b", "b1", "b2", "b3"
    });

    EXPECT_EQUAL_INT(size1, 2);
    EXPECT_EQUAL_INT(size2, 3);
    EXPECT_EQUAL_STRING(array1[0], "a1");
    EXPECT_EQUAL_STRING(array1[1], "a2");
    EXPECT_EQUAL_STRING(array2[0], "b1");
    EXPECT_EQUAL_STRING(array2[1], "b2");
    EXPECT_EQUAL_STRING(array2[2], "b3");
}

UTEST_TEST_CASE(integrate_test6) {
    // Test boolean flags
    bool flag1 = false;
    bool flag2 = false;
    bool flag3 = false;

    struct argparse argparse;
    struct argparse_option options[] = {
        OPTION_BOOLEAN('x', "flag1", "first flag", &flag1, NULL, 0),
        OPTION_BOOLEAN('y', "flag2", "second flag", &flag2, NULL, 0), 
        OPTION_BOOLEAN('z', "flag3", "third flag", &flag3, NULL, 0),
        OPTION_END()
    };

    argparse_init(&argparse, options, NULL);
    argparse_parse(&argparse, 3, (char*[]){
        "-x",
        "--flag2",
        "-z"
    });

    EXPECT_TRUE(flag1);
    EXPECT_TRUE(flag2);
    EXPECT_TRUE(flag3);
}

UTEST_TEST_CASE(integrate_test7) {
    // Test mixed types
    int number = 0;
    double decimal = 0.0;
    const char *text = NULL;
    bool flag = false;

    struct argparse argparse;
    struct argparse_option options[] = {
        OPTION_INT('n', "number", "integer value", &number, NULL, 0),
        OPTION_DOUBLE('d', "decimal", "decimal value", &decimal, NULL, 0),
        OPTION_STRING('t', "text", "string value", &text, NULL, 0),
        OPTION_BOOLEAN('f', "flag", "boolean flag", &flag, NULL, 0),
        OPTION_END()
    };

    argparse_init(&argparse, options, NULL);
    argparse_parse(&argparse, 7, (char*[]){
        "--number", "42",
        "-d", "3.14",
        "-t", "hello",
        "-f"
    });

    EXPECT_EQUAL_INT(number, 42);
    EXPECT_EQUAL_DOUBLE(decimal, 3.14);
    EXPECT_EQUAL_STRING(text, "hello");
    EXPECT_TRUE(flag);
}

UTEST_TEST_CASE(integrate_test8) {
    // Test ignore unknown options flag
    const char *value = NULL;
    
    struct argparse argparse;
    struct argparse_option options[] = {
        OPTION_STRING('v', "value", "test value", &value, NULL, 0),
        OPTION_END()
    };

    argparse_init(&argparse, options, NULL);
    argparse_set_flags(&argparse, ARGPARSE_FLAG_IGNORE_UNKNOWN_OPTION);
    argparse_parse(&argparse, 4, (char*[]){
        "-v", "test",
        "--value", "ggg"
    });

    EXPECT_EQUAL_STRING(value, "ggg");
}

UTEST_TEST_CASE(integrate_test9) {
    // Test multiple string arrays with empty values
    const char **array1 = NULL;
    const char **array2 = NULL;
    int size1 = 0;
    int size2 = 0;

    struct argparse argparse;
    struct argparse_option options[] = {
        OPTION_STRING('a', "array1", "first array", &array1, argparse_callback_multiple_arguments, (intptr_t)&size1),
        OPTION_STRING('b', "array2", "second array", &array2, argparse_callback_multiple_arguments, (intptr_t)&size2),
        OPTION_END()
    };

    argparse_init(&argparse, options, NULL);
    argparse_parse(&argparse, 6, (char*[]){
        "-a", "", "test",
        "-b", "", ""
    });

    EXPECT_EQUAL_INT(size1, 2);
    EXPECT_EQUAL_INT(size2, 2);
    EXPECT_EQUAL_STRING(array1[0], "");
    EXPECT_EQUAL_STRING(array1[1], "test");
    EXPECT_EQUAL_STRING(array2[0], "");
    EXPECT_EQUAL_STRING(array2[1], "");
}

UTEST_TEST_CASE(integrate_test10) {
    // Test description and help callback
    const char *value = NULL;
    struct argparse_description desc = {
        ._description = "Test Program",
        ._epilog = "Test Epilog",
        ._usage = "test [options]",
        ._program_name = "test"
    };
    struct argparse argparse;
    struct argparse_option options[] = {
        OPTION_STRING('v', "value", "test value", &value, NULL, 0),
        OPTION_HELP(),
        OPTION_END()
    };
    argparse_init(&argparse, options, &desc);
    // argparse_parse(&argparse, 2, (char*[]){
    //     "--help",
    // });
}
UTEST_TEST_CASE(integrate_test11) {
    bool force;
    int processor_count;
    int memory_size;
    bool debug;
    bool verbose;
    double cpu_frequency;
    bool freestanding;
    const char * arch;

    const char ** support_arch;
    int support_arch_size;

    const char ** path_list;
    int path_list_size;

    const char ** file_name_list;
    int file_name_list_size;

    struct argparse argparse;
    struct argparse_option options[] = {
        OPTION_BOOLEAN('f', "force", NULL, &force, NULL, 0),
        OPTION_INT(0, "processor", NULL, &processor_count, NULL, 0),
        OPTION_INT('m', "memory", NULL, &memory_size, NULL, 0),
        OPTION_DOUBLE('c', "cpu", NULL, &cpu_frequency, NULL, 0),
        OPTION_BOOLEAN(0, "freestanding", NULL, &freestanding, NULL, 0),
        OPTION_STRING('a', "arch", NULL, &arch, NULL, 0),
        OPTION_STRING('s', "support_arch", NULL, &support_arch, argparse_callback_multiple_arguments, (intptr_t)&support_arch_size),
        OPTION_STRING('p', "path", NULL, &path_list, argparse_callback_multiple_arguments, (intptr_t)&path_list_size),
        OPTION_STRING(0, "file", NULL, &file_name_list, argparse_callback_multiple_arguments, (intptr_t)&file_name_list_size),
        OPTION_BOOLEAN('d', "debug", NULL, &debug, NULL, 0),
        OPTION_BOOLEAN('v', "verbose", NULL, &verbose, NULL, 0),
        OPTION_END()
    };

    argparse_init(&argparse, options, NULL);
    argparse_parse(&argparse, 31, (char*[]){
        "-f",
        "--processor", "4",
        "-m", "1024",
        "-c", "2.50",
        "--freestanding",
        "-a", "x86",
        "-s", "x86_64", "i386", "arm64", "risc-v", "long-arch",
        "-m", "4096",
        "-p", "./", "../include", "../gnu/libc/includes", "/root/lib/bin/",
        "-d",
        "--file", "stdio.h", "stdlib.h", "string.h", "math.h", "time.h",
        "--verbose"
    });

    EXPECT_TRUE(force);
    EXPECT_TRUE(freestanding);
    EXPECT_TRUE(debug);
    EXPECT_TRUE(verbose);
    EXPECT_EQUAL_INT(processor_count, 4);
    EXPECT_EQUAL_INT(memory_size, 4096);
    EXPECT_EQUAL_DOUBLE(cpu_frequency, 2.50);
    EXPECT_NOT_NULL(arch);
    EXPECT_EQUAL_STRING(arch, "x86");
    EXPECT_EQUAL_INT(support_arch_size, 5);
    EXPECT_EQUAL_INT(path_list_size, 4);
    EXPECT_EQUAL_INT(file_name_list_size, 5);
    
    EXPECT_NOT_NULL(support_arch);
    EXPECT_EQUAL_STRING(support_arch[0], "x86_64");
    EXPECT_EQUAL_STRING(support_arch[1], "i386");
    EXPECT_EQUAL_STRING(support_arch[2], "arm64");
    EXPECT_EQUAL_STRING(support_arch[3], "risc-v");
    EXPECT_EQUAL_STRING(support_arch[4], "long-arch");

    EXPECT_NOT_NULL(path_list);
    EXPECT_EQUAL_STRING(path_list[0], "./");
    EXPECT_EQUAL_STRING(path_list[1], "../include");
    EXPECT_EQUAL_STRING(path_list[2], "../gnu/libc/includes");
    EXPECT_EQUAL_STRING(path_list[3], "/root/lib/bin/");

    EXPECT_NOT_NULL(file_name_list);
    EXPECT_EQUAL_STRING(file_name_list[0], "stdio.h");
    EXPECT_EQUAL_STRING(file_name_list[1], "stdlib.h");
    EXPECT_EQUAL_STRING(file_name_list[2], "string.h");
    EXPECT_EQUAL_STRING(file_name_list[3], "math.h");
    EXPECT_EQUAL_STRING(file_name_list[4], "time.h");
}
UTEST_TEST_SUITE(integrate_test){
    UTEST_RUN_TEST_CASE(integrate_test1);
    UTEST_RUN_TEST_CASE(integrate_test2);
    UTEST_RUN_TEST_CASE(integrate_test3);
    UTEST_RUN_TEST_CASE(integrate_test4);
    UTEST_RUN_TEST_CASE(integrate_test5);
    UTEST_RUN_TEST_CASE(integrate_test6);
    UTEST_RUN_TEST_CASE(integrate_test7);
    UTEST_RUN_TEST_CASE(integrate_test8);
    UTEST_RUN_TEST_CASE(integrate_test9);
    UTEST_RUN_TEST_CASE(integrate_test10);
    UTEST_RUN_TEST_CASE(integrate_test11);
}