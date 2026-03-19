#include <iniparse.h>
#include <string.h>
#include <utest.h>

UTEST_CASE(edge)
{
  struct iniparse_ctx ctx;
  EXPECT_EQ_INT(iniparse_init(&ctx, "cases/iniparse/INI/edge.ini"), 0);
  EXPECT_EQ_INT(iniparse_parse(&ctx), 0);

  EXPECT_EQ_STR(iniparse_getvalue(&ctx, "space in value", "key"),
                "value with spaces inside");
  EXPECT_EQ_STR(iniparse_getvalue(&ctx, "space in value", "trimmed"),
                "leading and trailing spaces");

  EXPECT_EQ_STR(iniparse_getvalue(&ctx, "section", "inside"),
                "section name has spaces in brackets");
  EXPECT_EQ_STR(iniparse_getvalue(&ctx, "section", "no_space"),
                "same section name without spaces in brackets");

  EXPECT_NOTNULL(iniparse_getvalue(&ctx, "empty", "empty_value"));
  EXPECT_EQ_STR(iniparse_getvalue(&ctx, "empty", "empty_value"), "");

  EXPECT_EQ_STR(iniparse_getvalue(&ctx, "extra", "pair"), "key=value");
  EXPECT_EQ_STR(iniparse_getvalue(&ctx, "extra", "with_hash"),
                "value#not_comment");
  EXPECT_EQ_STR(iniparse_getvalue(&ctx, "extra", "semicolon"),
                "value;not_comment");

  EXPECT_NULL(iniparse_getvalue(&ctx, "only_section", "any"));
  EXPECT_NULL(iniparse_getvalue(&ctx, "last_section_no_entry", "any"));

  EXPECT_EQ_STR(iniparse_getvalue(&ctx, "blank_lines", "first"), "one");
  EXPECT_EQ_STR(iniparse_getvalue(&ctx, "blank_lines", "second"), "two");
  EXPECT_EQ_STR(iniparse_getvalue(&ctx, "blank_lines", "third"), "three");

  EXPECT_EQ_STR(iniparse_getvalue(&ctx, "comments", "real"), "value");
  EXPECT_EQ_STR(iniparse_getvalue(&ctx, "comments", "another"), "here");

  EXPECT_EQ_STR(iniparse_getvalue(&ctx, "tab_key", "indented"),
                "tab before key");

  EXPECT_EQ_STR(iniparse_getvalue(&ctx, "subsection", "with_quotes"),
                "section \"has\" quotes");

  EXPECT_EQ_STR(iniparse_getvalue(&ctx, "spaces_after_value", "trailing"),
                "value");
  EXPECT_EQ_STR(iniparse_getvalue(&ctx, "spaces_after_value", "many_trailing"),
                "x");
  EXPECT_EQ_STR(iniparse_getvalue(&ctx, "spaces_after_value", "mixed"),
                "value");

  EXPECT_EQ_STR(iniparse_getvalue(&ctx, "spaces_around_equals", "loose"),
                "val");
  EXPECT_EQ_STR(iniparse_getvalue(&ctx, "spaces_around_equals", "wide"), "val");
  EXPECT_EQ_STR(
      iniparse_getvalue(&ctx, "spaces_around_equals", "tab_after_val"), "v");

  EXPECT_EQ_STR(iniparse_getvalue(&ctx, "leading_spaces_value", "normal"),
                "value");
  EXPECT_EQ_STR(iniparse_getvalue(&ctx, "leading_spaces_value", "spaced"),
                "value");

  EXPECT_NOTNULL(iniparse_getvalue(&ctx, "whitespace_only_value", "key"));
  EXPECT_EQ_STR(iniparse_getvalue(&ctx, "whitespace_only_value", "key"), "");
  EXPECT_NOTNULL(iniparse_getvalue(&ctx, "whitespace_only_value", "key2"));
  EXPECT_EQ_STR(iniparse_getvalue(&ctx, "whitespace_only_value", "key2"), "");

  EXPECT_NULL(iniparse_getvalue(&ctx, "nonexistent_section", "key"));
  EXPECT_NULL(iniparse_getvalue(&ctx, "section", "nonexistent_key"));

  EXPECT_NULL(iniparse_getvalue(&ctx, "NoSuchSection", "key"));
  EXPECT_NULL(iniparse_getvalue(&ctx, "space in value", "nonexistent_key"));
  EXPECT_NULL(iniparse_getvalue(&ctx, "extra", "missing"));
  EXPECT_NULL(iniparse_getvalue(&ctx, "blank_lines", "fourth"));
  EXPECT_NULL(iniparse_getvalue(&ctx, "comments", "absent"));
  EXPECT_NULL(iniparse_getvalue(&ctx, "tab_key", "other"));
  EXPECT_NULL(iniparse_getvalue(&ctx, "subsection", "other_key"));
  EXPECT_NULL(iniparse_getvalue(&ctx, "spaces_after_value", "absent"));
  EXPECT_NULL(iniparse_getvalue(&ctx, "spaces_around_equals", "missing"));
  EXPECT_NULL(iniparse_getvalue(&ctx, "leading_spaces_value", "other"));
  EXPECT_NULL(iniparse_getvalue(&ctx, "whitespace_only_value", "key3"));

  EXPECT_NULL(iniparse_getvalue(&ctx, "", "key"));
  EXPECT_NULL(iniparse_getvalue(&ctx, "section", ""));
  EXPECT_NULL(iniparse_getvalue(&ctx, "wrong_section", "inside"));
  EXPECT_NULL(iniparse_getvalue(&ctx, "section ", "no_space"));
  EXPECT_NULL(iniparse_getvalue(&ctx, " section", "inside"));

  iniparse_fini(&ctx);
}
