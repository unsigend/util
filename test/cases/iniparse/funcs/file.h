#include <iniparse.h>
#include <stdio.h>
#include <string.h>
#include <utest.h>

extern const char *simple_filename;
#define BUFFSZ 512

UTEST_TEST_CASE(file)
{
  {
    char buffer[BUFFSZ];
    memset(buffer, 0, BUFFSZ);

    FILE *file = fopen(simple_filename, "r");
    EXPECT_NOT_NULL(file);
    EXPECT_NOT_NULL(fgets(buffer, BUFFSZ, file));
    EXPECT_EQUAL_UINT8(buffer[0], '#');
    EXPECT_NOT_NULL(fgets(buffer, BUFFSZ, file));
    EXPECT_EQUAL_STRING(buffer, "[core]\n");
    EXPECT_NOT_NULL(fgets(buffer, BUFFSZ, file));
    EXPECT_EQUAL_STRING(buffer, "\trepositoryFormat = 0\n");
    EXPECT_NOT_NULL(fgets(buffer, BUFFSZ, file));
    EXPECT_EQUAL_STRING(buffer, "\tfileMode = true\n");
    EXPECT_NOT_NULL(fgets(buffer, BUFFSZ, file));
    EXPECT_EQUAL_STRING(buffer, "\tbare = false\n");
    EXPECT_NOT_NULL(fgets(buffer, BUFFSZ, file));
    EXPECT_EQUAL_STRING(buffer, "\tglobal = true\n");
    EXPECT_NOT_NULL(fgets(buffer, BUFFSZ, file));
    EXPECT_EQUAL_STRING(buffer, "\tignoreCase = true\n");

    fclose(file);
  }
  {
    struct iniparse iniparse;
    EXPECT_TRUE(iniparse_init(&iniparse, simple_filename));
  }
}
