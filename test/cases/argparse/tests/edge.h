#include <argparse.h>
#include <stdbool.h>
#include <utest.h>

static int edge_cb_count = 0;
static int edge_cb_seen = 0;

static void edge_int_cb(struct argparse *ctx, struct argparse_opt *opt)
{
  (void)ctx;
  edge_cb_count++;
  if (opt && opt->dest)
    edge_cb_seen = *(int *)opt->dest;
}

UTEST_CASE(edge)
{
  {
    struct argparse ctx;
    int n = 7;
    int min = 0;
    struct argparse_opt opts[] = {
        OPT_INT('n', "num", "", &n, OPT_OPTIONAL),
        OPT_INT('m', "min", "", &min, OPT_REQUIRED),
        OPT_END(),
    };
    char *argv[] = {"-n", "--min", "3"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 3, argv), 0);
    EXPECT_EQ_INT(n, 7);
    EXPECT_EQ_INT(min, 3);
    EXPECT_EQ_UINT(argparse_getremargc(&ctx), 0);
    EXPECT_EQ_PTR(argparse_getremargv(&ctx), NULL);
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    int n = 7;
    struct argparse_opt opts[] = {
        OPT_INT('n', "num", "", &n, OPT_OPTIONAL),
        OPT_END(),
    };
    char empty[] = "";
    char *argv[] = {"-n", empty};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 2, argv), 0);
    EXPECT_EQ_INT(n, 7);
    EXPECT_EQ_UINT(argparse_getremargc(&ctx), 1);
    EXPECT_NOTNULL(argparse_getremargv(&ctx));
    EXPECT_EQ_STR(argparse_getremargv(&ctx)[0], "");
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    int n = 9;
    struct argparse_opt opts[] = {
        OPT_INT('n', "num", "", &n, OPT_REQUIRED),
        OPT_END(),
    };
    char *argv[] = {"-n", "abc"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    argparse_setflags(&ctx, ARG_IGNORE);
    EXPECT_EQ_INT(argparse_parse(&ctx, 2, argv), -1);
    EXPECT_EQ_INT(n, 9);
    EXPECT_NE_STR(argparse_strerror(&ctx), "");
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
    char *argv[] = {"-abz"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 1, argv), -1);
    EXPECT_TRUE(aflag);
    EXPECT_TRUE(bflag);
    EXPECT_NE_STR(argparse_strerror(&ctx), "");
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
    char *argv[] = {"-abz"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    argparse_setflags(&ctx, ARG_IGNORE);
    EXPECT_EQ_INT(argparse_parse(&ctx, 1, argv), 0);
    EXPECT_TRUE(aflag);
    EXPECT_TRUE(bflag);
    EXPECT_EQ_UINT(argparse_getremargc(&ctx), 0);
    EXPECT_EQ_PTR(argparse_getremargv(&ctx), NULL);
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    struct argparse_list *inc = NULL;
    struct argparse_opt opts[] = {
        OPT_LIST('I', "include", "", &inc),
        OPT_END(),
    };
    char *argv[] = {"-I", "-notanoption"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 2, argv), 0);
    EXPECT_NOTNULL(inc);
    EXPECT_EQ_UINT(argparse_getlistsz(inc), 1);
    EXPECT_NOTNULL(argparse_getlist(inc));
    EXPECT_EQ_STR(argparse_getlist(inc)[0], "-notanoption");
    EXPECT_EQ_UINT(argparse_getremargc(&ctx), 0);
    EXPECT_EQ_PTR(argparse_getremargv(&ctx), NULL);
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    struct argparse_list *inc = NULL;
    struct argparse_opt opts[] = {
        OPT_LIST('I', "include", "", &inc),
        OPT_END(),
    };
    char *argv[] = {"-I-notanoption"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 1, argv), 0);
    EXPECT_NOTNULL(inc);
    EXPECT_EQ_UINT(argparse_getlistsz(inc), 1);
    EXPECT_NOTNULL(argparse_getlist(inc));
    EXPECT_EQ_STR(argparse_getlist(inc)[0], "-notanoption");
    EXPECT_EQ_UINT(argparse_getremargc(&ctx), 0);
    EXPECT_EQ_PTR(argparse_getremargv(&ctx), NULL);
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    int min = 0;
    struct argparse_opt opts[] = {
        OPT_INT('m', "min", "", &min, OPT_REQUIRED),
        OPT_END(),
    };
    char *argv[] = {"--unknown=5", "--min", "3"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    argparse_setflags(&ctx, ARG_IGNORE);
    EXPECT_EQ_INT(argparse_parse(&ctx, 3, argv), 0);
    EXPECT_EQ_INT(min, 3);
    EXPECT_EQ_UINT(argparse_getremargc(&ctx), 0);
    EXPECT_EQ_PTR(argparse_getremargv(&ctx), NULL);
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    int n = 0;
    struct argparse_opt opts[] = {
        OPT_INT('n', "num", "", &n, OPT_REQUIRED),
        OPT_END(),
    };
    char *argv[] = {"-n", "-5"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 2, argv), 0);
    EXPECT_EQ_INT(n, -5);
    EXPECT_EQ_UINT(argparse_getremargc(&ctx), 0);
    EXPECT_EQ_PTR(argparse_getremargv(&ctx), NULL);
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    int n = 42;
    struct argparse_opt opts[] = {
        OPT_INT('n', "num", "", &n, OPT_REQUIRED),
        OPT_END(),
    };
    char *argv[] = {"--num="};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 1, argv), -1);
    EXPECT_EQ_INT(n, 42);
    EXPECT_NE_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    int n = 7;
    struct argparse_opt opts[] = {
        OPT_INT('n', "num", "", &n, OPT_OPTIONAL),
        OPT_END(),
    };
    char *argv[] = {"--num=", "pos1"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 2, argv), 0);
    EXPECT_EQ_INT(n, 7);
    EXPECT_EQ_UINT(argparse_getremargc(&ctx), 1);
    EXPECT_NOTNULL(argparse_getremargv(&ctx));
    EXPECT_EQ_STR(argparse_getremargv(&ctx)[0], "pos1");
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    int n = 0;
    bool aflag = false;
    struct argparse_opt opts[] = {
        OPT_INT('n', "num", "", &n, OPT_REQUIRED),
        OPT_BOOL('a', "all", "", &aflag),
        OPT_END(),
    };
    char *argv[] = {"-n", "1", "--", "-a", "-n", "2", "file"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 7, argv), 0);
    EXPECT_EQ_INT(n, 1);
    EXPECT_FALSE(aflag);
    EXPECT_EQ_UINT(argparse_getremargc(&ctx), 4);
    EXPECT_NOTNULL(argparse_getremargv(&ctx));
    EXPECT_EQ_STR(argparse_getremargv(&ctx)[0], "-a");
    EXPECT_EQ_STR(argparse_getremargv(&ctx)[1], "-n");
    EXPECT_EQ_STR(argparse_getremargv(&ctx)[2], "2");
    EXPECT_EQ_STR(argparse_getremargv(&ctx)[3], "file");
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    struct argparse_opt opts[] = {OPT_END()};
    char *argv[] = {"--unknown=5", "file1", "-x"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    argparse_setflags(&ctx, ARG_IGNORE);
    EXPECT_EQ_INT(argparse_parse(&ctx, 3, argv), 0);
    EXPECT_EQ_UINT(argparse_getremargc(&ctx), 1);
    EXPECT_NOTNULL(argparse_getremargv(&ctx));
    EXPECT_EQ_STR(argparse_getremargv(&ctx)[0], "file1");
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    int n = 7;
    int min = 0;
    struct argparse_opt opts[] = {
        OPT_DECL(_OPT_INT, 'n', "num", "", &n, OPT_OPTIONAL, edge_int_cb),
        OPT_INT('m', "min", "", &min, OPT_REQUIRED),
        OPT_END(),
    };

    edge_cb_count = 0;
    edge_cb_seen = 0;
    char *argv[] = {"-n", "--min", "3"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 3, argv), 0);
    EXPECT_EQ_INT(n, 7);
    EXPECT_EQ_INT(min, 3);
    EXPECT_EQ_INT(edge_cb_count, 1);
    EXPECT_EQ_INT(edge_cb_seen, 7);
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    int n = 9;
    struct argparse_opt opts[] = {
        OPT_DECL(_OPT_INT, 'n', "num", "", &n, OPT_REQUIRED, edge_int_cb),
        OPT_END(),
    };
    char *argv[] = {"-n", "abc"};

    edge_cb_count = 0;
    edge_cb_seen = 0;
    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 2, argv), -1);
    EXPECT_EQ_INT(n, 9);
    EXPECT_EQ_INT(edge_cb_count, 0);
    EXPECT_NE_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    int n = 5;
    struct argparse_opt opts[] = {
        OPT_INT('n', "num", "", &n, OPT_OPTIONAL),
        OPT_END(),
    };
    char *argv[] = {"-n", "-z"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 2, argv), -1);
    EXPECT_EQ_INT(n, 5);
    EXPECT_NE_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    int n = 5;
    struct argparse_opt opts[] = {
        OPT_INT('n', "num", "", &n, OPT_OPTIONAL),
        OPT_END(),
    };
    char *argv[] = {"-n", "-z"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    argparse_setflags(&ctx, ARG_IGNORE);
    EXPECT_EQ_INT(argparse_parse(&ctx, 2, argv), 0);
    EXPECT_EQ_INT(n, 5);
    EXPECT_EQ_UINT(argparse_getremargc(&ctx), 0);
    EXPECT_EQ_PTR(argparse_getremargv(&ctx), NULL);
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    bool a = false;
    bool b = false;
    int n = 0;
    struct argparse_opt opts[] = {
        OPT_BOOL('a', "all", "", &a),
        OPT_BOOL('b', "bin", "", &b),
        OPT_INT('n', "num", "", &n, OPT_REQUIRED),
        OPT_END(),
    };
    char *argv[] = {"-abn5"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 1, argv), 0);
    EXPECT_TRUE(a);
    EXPECT_TRUE(b);
    EXPECT_EQ_INT(n, 5);
    EXPECT_EQ_UINT(argparse_getremargc(&ctx), 0);
    EXPECT_EQ_PTR(argparse_getremargv(&ctx), NULL);
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    bool a = false;
    int n = 1;
    struct argparse_opt opts[] = {
        OPT_BOOL('a', "all", "", &a),
        OPT_INT('n', "num", "", &n, OPT_REQUIRED),
        OPT_END(),
    };
    char *argv[] = {"-an"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 1, argv), -1);
    EXPECT_TRUE(a);
    EXPECT_EQ_INT(n, 1);
    EXPECT_NE_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    bool a = false;
    bool b = false;
    bool c = false;
    struct argparse_opt opts[] = {
        OPT_BOOL('a', "all", "", &a),
        OPT_BOOL('b', "bin", "", &b),
        OPT_BOOL('c', "check", "", &c),
        OPT_END(),
    };
    char *argv[] = {"-abzc"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    argparse_setflags(&ctx, ARG_IGNORE);
    EXPECT_EQ_INT(argparse_parse(&ctx, 1, argv), 0);
    EXPECT_TRUE(a);
    EXPECT_TRUE(b);
    EXPECT_TRUE(c);
    EXPECT_EQ_UINT(argparse_getremargc(&ctx), 0);
    EXPECT_EQ_PTR(argparse_getremargv(&ctx), NULL);
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    int min = 0;
    struct argparse_opt opts[] = {
        OPT_INT('m', "min", "", &min, OPT_REQUIRED),
        OPT_END(),
    };
    char *argv[] = {"--unknown", "--min", "3"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    argparse_setflags(&ctx, ARG_IGNORE);
    EXPECT_EQ_INT(argparse_parse(&ctx, 3, argv), 0);
    EXPECT_EQ_INT(min, 3);
    EXPECT_EQ_UINT(argparse_getremargc(&ctx), 0);
    EXPECT_EQ_PTR(argparse_getremargv(&ctx), NULL);
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    struct argparse_list *inc = NULL;
    int n = 0;
    struct argparse_opt opts[] = {
        OPT_LIST('I', "include", "", &inc),
        OPT_INT('n', "num", "", &n, OPT_REQUIRED),
        OPT_END(),
    };
    char *argv[] = {"-I", "-n7", "file"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 3, argv), 0);
    EXPECT_EQ_UINT(argparse_getlistsz(inc), 1);
    EXPECT_EQ_STR(argparse_getlist(inc)[0], "-n7");
    EXPECT_EQ_INT(n, 0);
    EXPECT_EQ_UINT(argparse_getremargc(&ctx), 1);
    EXPECT_EQ_STR(argparse_getremargv(&ctx)[0], "file");
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    struct argparse_list *inc = NULL;
    int n = 0;
    struct argparse_opt opts[] = {
        OPT_LIST('I', "include", "", &inc),
        OPT_INT('n', "num", "", &n, OPT_REQUIRED),
        OPT_END(),
    };
    char *argv[] = {"--include=-n7", "--num", "3"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 3, argv), 0);
    EXPECT_EQ_UINT(argparse_getlistsz(inc), 1);
    EXPECT_EQ_STR(argparse_getlist(inc)[0], "-n7");
    EXPECT_EQ_INT(n, 3);
    EXPECT_EQ_UINT(argparse_getremargc(&ctx), 0);
    EXPECT_EQ_PTR(argparse_getremargv(&ctx), NULL);
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    struct argparse_opt opts[] = {OPT_END()};
    char *argv[] = {"-", "file"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 2, argv), 0);
    EXPECT_EQ_UINT(argparse_getremargc(&ctx), 1);
    EXPECT_EQ_STR(argparse_getremargv(&ctx)[0], "file");
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    int n = 2;
    struct argparse_opt opts[] = {
        OPT_INT('n', "num", "", &n, OPT_REQUIRED),
        OPT_END(),
    };
    char *argv[] = {"--", "-n", "5"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 3, argv), 0);
    EXPECT_EQ_INT(n, 2);
    EXPECT_EQ_UINT(argparse_getremargc(&ctx), 2);
    EXPECT_EQ_STR(argparse_getremargv(&ctx)[0], "-n");
    EXPECT_EQ_STR(argparse_getremargv(&ctx)[1], "5");
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    struct argparse_list *inc = NULL;
    struct argparse_opt opts[] = {
        OPT_LIST('I', "include", "", &inc),
        OPT_END(),
    };
    char *argv[] = {"-I", "--", "file"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 3, argv), 0);
    EXPECT_EQ_UINT(argparse_getlistsz(inc), 1);
    EXPECT_EQ_STR(argparse_getlist(inc)[0], "--");
    EXPECT_EQ_UINT(argparse_getremargc(&ctx), 1);
    EXPECT_EQ_STR(argparse_getremargv(&ctx)[0], "file");
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    bool dummy = false;
    struct argparse_opt opts[] = {
        OPT_BOOL('a', "all", "", &dummy),
        OPT_END(),
    };
    EXPECT_EQ_INT(argparse_init(NULL, opts, NULL), -1);
  }

  {
    struct argparse ctx;
    EXPECT_EQ_INT(argparse_init(&ctx, NULL, NULL), -1);
  }

  {
    argparse_fini(NULL);
  }

  {
    struct argparse ctx;
    bool aflag = false;
    struct argparse_opt opts[] = {
        OPT_BOOL('a', "all", "", &aflag),
        OPT_END(),
    };
    char *argv[] = {"-z", "-a"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    argparse_setflags(&ctx, ARG_IGNORE);
    argparse_clrflags(&ctx, ARG_IGNORE);
    EXPECT_EQ_INT(argparse_parse(&ctx, 2, argv), -1);
    EXPECT_FALSE(aflag);
    EXPECT_NE_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    bool aflag = false;
    struct argparse_opt opts[] = {
        OPT_GROUP("group"),
        OPT_BOOL('a', "all", "", &aflag),
        OPT_END(),
    };
    char *argv[] = {"-a"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 1, argv), 0);
    EXPECT_TRUE(aflag);
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    struct argparse_opt opts[] = {OPT_END()};
    char *argv1[] = {"--", "first"};
    char *argv2[] = {"second"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 2, argv1), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 1, argv2), 0);
    EXPECT_EQ_UINT(argparse_getremargc(&ctx), 2);
    EXPECT_EQ_STR(argparse_getremargv(&ctx)[0], "first");
    EXPECT_EQ_STR(argparse_getremargv(&ctx)[1], "second");
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    struct argparse_opt opts[] = {OPT_END()};
    char *argv[] = {"--"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 1, argv), 0);
    EXPECT_EQ_UINT(argparse_getremargc(&ctx), 0);
    EXPECT_EQ_PTR(argparse_getremargv(&ctx), NULL);
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }
}