#include <argparse.h>
#include <stdbool.h>
#include <utest.h>

static int bool_cb_count = 0;
static bool bool_cb_seen_dest = false;

static void bool_cb(struct argparse *ctx, struct argparse_opt *opt)
{
  (void)ctx;
  bool_cb_count++;
  if (opt && opt->dest)
    bool_cb_seen_dest = *(bool *)opt->dest;
}

UTEST_CASE(bool)
{
  {
    struct argparse ctx;
    bool aflag = false;
    bool bflag = false;
    bool cflag = false;
    bool vflag = false;
    struct argparse_opt opts[] = {
        OPT_BOOL('a', "all", "", &aflag),
        OPT_BOOL('b', "binary", "", &bflag),
        OPT_BOOL('c', "check", "", &cflag),
        OPT_DECL(_OPT_BOOL, 'v', "verbose", "", &vflag, OPT_NONE, bool_cb),
        OPT_END(),
    };
    char *argv[] = {"-a", "--binary", "-cv"};

    bool_cb_count = 0;
    bool_cb_seen_dest = false;
    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 3, argv), 0);
    EXPECT_TRUE(aflag);
    EXPECT_TRUE(bflag);
    EXPECT_TRUE(cflag);
    EXPECT_TRUE(vflag);
    EXPECT_EQ_INT(bool_cb_count, 1);
    EXPECT_TRUE(bool_cb_seen_dest);
    EXPECT_EQ_UINT(argparse_getremargc(&ctx), 0);
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    bool aflag = false;
    bool bflag = false;
    bool cflag = false;
    struct argparse_opt opts[] = {
        OPT_BOOL('a', "all", "", &aflag),
        OPT_BOOL('b', "binary", "", &bflag),
        OPT_BOOL('c', "check", "", &cflag),
        OPT_END(),
    };
    char *argv[] = {"-abc"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 1, argv), 0);
    EXPECT_TRUE(aflag);
    EXPECT_TRUE(bflag);
    EXPECT_TRUE(cflag);
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    bool aflag = false;
    struct argparse_opt opts[] = {
        OPT_BOOL('a', "all", "", &aflag),
        OPT_END(),
    };
    char *argv[] = {"--all", "input.o", "--", "--unknown", "-a"};
    char **remv;

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 5, argv), 0);
    EXPECT_TRUE(aflag);
    EXPECT_EQ_UINT(argparse_getremargc(&ctx), 3);
    remv = argparse_getremargv(&ctx);
    EXPECT_NOTNULL(remv);
    EXPECT_EQ_STR(remv[0], "input.o");
    EXPECT_EQ_STR(remv[1], "--unknown");
    EXPECT_EQ_STR(remv[2], "-a");
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    bool aflag = false;
    struct argparse_opt opts[] = {
        OPT_BOOL('a', "all", "", &aflag),
        OPT_END(),
    };
    char *argv[] = {"-x", "-a"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 2, argv), -1);
    EXPECT_FALSE(aflag);
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    bool aflag = false;
    struct argparse_opt opts[] = {
        OPT_BOOL('a', "all", "", &aflag),
        OPT_END(),
    };
    char *argv[] = {"--unknown", "-a"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    argparse_setflags(&ctx, ARG_IGNORE);
    EXPECT_EQ_INT(argparse_parse(&ctx, 2, argv), 0);
    EXPECT_TRUE(aflag);
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    bool aflag = false;
    struct argparse_opt opts[] = {
        OPT_BOOL('a', "all", "", &aflag),
        OPT_END(),
    };
    char **argv0 = NULL;

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 0, NULL), 0);
    EXPECT_FALSE(aflag);
    argparse_fini(&ctx);

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 0, argv0), 0);
    EXPECT_FALSE(aflag);
    EXPECT_EQ_UINT(argparse_getremargc(&ctx), 0);
    EXPECT_EQ_PTR(argparse_getremargv(&ctx), NULL);
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    bool aflag = false;
    bool bflag = false;
    bool cflag = false;
    struct argparse_opt opts[] = {
        OPT_BOOL('a', "all", "", &aflag),
        OPT_BOOL('b', "binary", "", &bflag),
        OPT_BOOL('c', "check", "", &cflag),
        OPT_END(),
    };
    char *argv[] = {"--all", "--all", "-bb", "-c", "-a"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 5, argv), 0);
    EXPECT_TRUE(aflag);
    EXPECT_TRUE(bflag);
    EXPECT_TRUE(cflag);
    EXPECT_EQ_UINT(argparse_getremargc(&ctx), 0);
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    bool aflag = false;
    struct argparse_opt opts[] = {
        OPT_BOOL('a', "all", "", &aflag),
        OPT_END(),
    };
    char *argv[] = {"--", "-a", "--all", "file.o"};
    char **remv;

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 4, argv), 0);
    EXPECT_FALSE(aflag);
    EXPECT_EQ_UINT(argparse_getremargc(&ctx), 3);
    remv = argparse_getremargv(&ctx);
    EXPECT_NOTNULL(remv);
    EXPECT_EQ_STR(remv[0], "-a");
    EXPECT_EQ_STR(remv[1], "--all");
    EXPECT_EQ_STR(remv[2], "file.o");
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    bool aflag = false;
    bool bflag = false;
    struct argparse_opt opts[] = {
        OPT_BOOL('a', "all", "", &aflag),
        OPT_BOOL('b', "binary", "", &bflag),
        OPT_END(),
    };
    char *argv[] = {"-x", "--unknown", "-ab"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    argparse_setflags(&ctx, ARG_IGNORE);
    EXPECT_EQ_INT(argparse_parse(&ctx, 3, argv), 0);
    EXPECT_TRUE(aflag);
    EXPECT_TRUE(bflag);
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    bool aflag = false;
    struct argparse_opt opts[] = {
        OPT_BOOL('a', "all", "", &aflag),
        OPT_END(),
    };
    char *argv[] = {"--unknown", "input.o", "--", "-a"};
    char **remv;

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    argparse_setflags(&ctx, ARG_IGNORE);
    EXPECT_EQ_INT(argparse_parse(&ctx, 4, argv), 0);
    EXPECT_FALSE(aflag);
    EXPECT_EQ_UINT(argparse_getremargc(&ctx), 2);
    remv = argparse_getremargv(&ctx);
    EXPECT_NOTNULL(remv);
    EXPECT_EQ_STR(remv[0], "input.o");
    EXPECT_EQ_STR(remv[1], "-a");
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }
}