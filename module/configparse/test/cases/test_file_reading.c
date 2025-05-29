#include <utest.h>
#include <stdio.h>

#include <configparse.h>

extern const char * simple_filename;

// test the std IO file reading

UTEST_TEST_CASE(std_IO_file){
#define BUFFER_SIZE 512
    char buffer[BUFFER_SIZE];
    memset(buffer, 0, BUFFER_SIZE);

    FILE * file = fopen(simple_filename, "r");
    EXPECT_NOT_NULL(file);
    EXPECT_NOT_NULL(fgets(buffer, BUFFER_SIZE, file));
    EXPECT_EQUAL_UINT8(buffer[0], '#');
    EXPECT_NOT_NULL(fgets(buffer, BUFFER_SIZE, file));
    EXPECT_EQUAL_STRING(buffer, "[core]\n");
    EXPECT_NOT_NULL(fgets(buffer, BUFFER_SIZE, file));
    EXPECT_EQUAL_STRING(buffer, "\trepositoryFormat = 0\n");
    EXPECT_NOT_NULL(fgets(buffer, BUFFER_SIZE, file));
    EXPECT_EQUAL_STRING(buffer, "\tfileMode = true\n");
    EXPECT_NOT_NULL(fgets(buffer, BUFFER_SIZE, file));
    EXPECT_EQUAL_STRING(buffer, "\tbare = false\n");
    EXPECT_NOT_NULL(fgets(buffer, BUFFER_SIZE, file));
    EXPECT_EQUAL_STRING(buffer, "\tglobal = true\n");
    EXPECT_NOT_NULL(fgets(buffer, BUFFER_SIZE, file));
    EXPECT_EQUAL_STRING(buffer, "\tignoreCase = true\n");

    fclose(file);
}

// test the configparse read file
UTEST_TEST_CASE(configparse_read_file){
    struct configparse configparse;
    EXPECT_TRUE(init_configparse(&configparse, simple_filename));
}

UTEST_TEST_SUITE(file_reading){
    UTEST_RUN_TEST_CASE(std_IO_file);
    UTEST_RUN_TEST_CASE(configparse_read_file);
}