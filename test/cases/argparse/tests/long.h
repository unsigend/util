#include <argparse.h>
#include <limits.h>
#include <stdio.h>
#include <utest.h>

static int long_cb_count = 0;
static long long_cb_seen_dest = 0;

static void long_cb(struct argparse *ctx, struct argparse_opt *opt)
{
  (void)ctx;
  long_cb_count++;
  if (opt && opt->dest)
    long_cb_seen_dest = *(long *)opt->dest;
}

UTEST_CASE(long)
{
  {
    struct argparse ctx;
    long v = 0;
    struct argparse_opt opts[] = {
        OPT_LONG('l', "level", "", &v, OPT_REQUIRED),
        OPT_END(),
    };
    char *argv[] = {"-l", "42"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 2, argv), 0);
    EXPECT_TRUE(v == 42L);
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    long v = 0;
    struct argparse_opt opts[] = {
        OPT_LONG('l', "level", "", &v, OPT_REQUIRED),
        OPT_END(),
    };
    char *argv[] = {"-l99"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 1, argv), 0);
    EXPECT_TRUE(v == 99L);
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    long v = 0;
    struct argparse_opt opts[] = {
        OPT_LONG('l', "level", "", &v, OPT_REQUIRED),
        OPT_END(),
    };
    char *argv[] = {"--level", "100"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 2, argv), 0);
    EXPECT_TRUE(v == 100L);
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    long v = 0;
    struct argparse_opt opts[] = {
        OPT_LONG('l', "level", "", &v, OPT_REQUIRED),
        OPT_END(),
    };
    char *argv[] = {"--level=200"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 1, argv), 0);
    EXPECT_TRUE(v == 200L);
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    long a = 0;
    long b = 0;
    long c = 0;
    struct argparse_opt opts[] = {
        OPT_LONG('a', "alpha", "", &a, OPT_REQUIRED),
        OPT_LONG('b', "beta", "", &b, OPT_REQUIRED),
        OPT_LONG('c', "gamma", "", &c, OPT_OPTIONAL),
        OPT_END(),
    };
    char *argv[] = {"-a", "1", "--beta=2", "-c3", "rest.o"};
    char **remv;

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 5, argv), 0);
    EXPECT_TRUE(a == 1L && b == 2L && c == 3L);
    EXPECT_EQ_UINT(argparse_getremargc(&ctx), 1);
    remv = argparse_getremargv(&ctx);
    EXPECT_NOTNULL(remv);
    EXPECT_EQ_STR(remv[0], "rest.o");
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    long hexv = 0;
    long octv = 0;
    long negv = 0;
    long plusv = 0;
    struct argparse_opt opts[] = {
        OPT_LONG('x', "hex", "", &hexv, OPT_REQUIRED),
        OPT_LONG('o', "oct", "", &octv, OPT_REQUIRED),
        OPT_LONG('n', "neg", "", &negv, OPT_REQUIRED),
        OPT_LONG('p', "plus", "", &plusv, OPT_REQUIRED),
        OPT_END(),
    };
    char *argv[] = {"-x0x40", "-o", "0100", "--neg=-7", "--plus", "+15"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 6, argv), 0);
    EXPECT_TRUE(hexv == 64L && octv == 64L && negv == -7L && plusv == 15L);
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    long v = 7;
    struct argparse_opt opts[] = {
        OPT_LONG('n', "number", "", &v, OPT_OPTIONAL),
        OPT_END(),
    };
    char *argv[] = {"-n8"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 1, argv), 0);
    EXPECT_TRUE(v == 8L);
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    long v = 7;
    struct argparse_opt opts[] = {
        OPT_LONG('n', "number", "", &v, OPT_OPTIONAL),
        OPT_END(),
    };
    char *argv[] = {"-n", "9"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 2, argv), 0);
    EXPECT_TRUE(v == 9L);
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    long v = 7;
    struct argparse_opt opts[] = {
        OPT_LONG('n', "number", "", &v, OPT_OPTIONAL),
        OPT_END(),
    };
    char *argv[] = {"--number", "10"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 2, argv), 0);
    EXPECT_TRUE(v == 10L);
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    long v = 7;
    struct argparse_opt opts[] = {
        OPT_LONG('n', "number", "", &v, OPT_OPTIONAL),
        OPT_END(),
    };
    char *argv[] = {"--number=11"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 1, argv), 0);
    EXPECT_TRUE(v == 11L);
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    long v = 7;
    struct argparse_opt opts[] = {
        OPT_LONG('n', "number", "", &v, OPT_OPTIONAL),
        OPT_END(),
    };
    char *argv[] = {"-n", "notanumber"};
    char **remv;

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 2, argv), 0);
    EXPECT_TRUE(v == 7L);
    EXPECT_EQ_UINT(argparse_getremargc(&ctx), 1);
    remv = argparse_getremargv(&ctx);
    EXPECT_NOTNULL(remv);
    EXPECT_EQ_STR(remv[0], "notanumber");
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    long v = 13;
    struct argparse_opt opts[] = {
        OPT_LONG('z', "zzz", "", &v, OPT_OPTIONAL),
        OPT_END(),
    };
    char *argv[] = {"-z"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 1, argv), 0);
    EXPECT_TRUE(v == 13L);
    EXPECT_EQ_UINT(argparse_getremargc(&ctx), 0);
    EXPECT_EQ_PTR(argparse_getremargv(&ctx), NULL);
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    long v = 0;
    struct argparse_opt opts[] = {
        OPT_LONG('l', "level", "", &v, OPT_REQUIRED),
        OPT_END(),
    };
    char *argv[] = {"-l", "12xyz"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 2, argv), -1);
    EXPECT_TRUE(v == 0L);
    EXPECT_NE_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    long v = 0;
    struct argparse_opt opts[] = {
        OPT_LONG('l', "level", "", &v, OPT_REQUIRED),
        OPT_END(),
    };
    char *argv[] = {"--level"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 1, argv), -1);
    EXPECT_TRUE(v == 0L);
    EXPECT_NE_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    long v = 0;
    struct argparse_opt opts[] = {
        OPT_LONG('l', "level", "", &v, OPT_REQUIRED),
        OPT_END(),
    };
    char *argv[] = {"--level="};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 1, argv), -1);
    EXPECT_TRUE(v == 0L);
    EXPECT_NE_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    long lo = 0;
    long hi = 0;
    struct argparse_opt opts[] = {
        OPT_LONG('m', "min", "", &lo, OPT_REQUIRED),
        OPT_LONG('M', "max", "", &hi, OPT_REQUIRED),
        OPT_END(),
    };
    char minbuf[64];
    char maxbuf[64];
    snprintf(minbuf, sizeof(minbuf), "%ld", LONG_MIN);
    snprintf(maxbuf, sizeof(maxbuf), "%ld", LONG_MAX);
    char *argv[] = {"--min", minbuf, "--max", maxbuf};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 4, argv), 0);
    EXPECT_TRUE(lo == LONG_MIN && hi == LONG_MAX);
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    long v = 0;
    struct argparse_opt opts[] = {
        OPT_LONG('l', "level", "", &v, OPT_REQUIRED),
        OPT_END(),
    };
    char *argv[] = {"-l", "999999999999999999999999999999999999999999999"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 2, argv), -1);
    EXPECT_TRUE(v == 0L);
    EXPECT_NE_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    long v = 0;
    struct argparse_opt opts[] = {
        OPT_LONG('l', "level", "", &v, OPT_REQUIRED),
        OPT_END(),
    };
    char *argv[] = {"--level=-99999999999999999999999999999999999999999999"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 1, argv), -1);
    EXPECT_TRUE(v == 0L);
    EXPECT_NE_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    long v = 0;
    struct argparse_opt opts[] = {
        OPT_LONG('l', "level", "", &v, OPT_REQUIRED),
        OPT_END(),
    };
    char *argv[] = {"-X", "-l", "1"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 3, argv), -1);
    EXPECT_TRUE(v == 0L);
    EXPECT_NE_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    long v = 0;
    struct argparse_opt opts[] = {
        OPT_LONG('l', "level", "", &v, OPT_REQUIRED),
        OPT_END(),
    };
    char *argv[] = {"--lev", "9"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 2, argv), -1);
    EXPECT_TRUE(v == 0L);
    EXPECT_NE_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    long v = 0;
    struct argparse_opt opts[] = {
        OPT_LONG('l', "level", "", &v, OPT_REQUIRED),
        OPT_END(),
    };
    char *argv[] = {"--nosuch", "-l", "2"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    argparse_setflags(&ctx, ARG_IGNORE);
    EXPECT_EQ_INT(argparse_parse(&ctx, 3, argv), 0);
    EXPECT_TRUE(v == 2L);
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    long v = 5;
    struct argparse_opt opts[] = {
        OPT_LONG('l', "level", "", &v, OPT_REQUIRED),
        OPT_END(),
    };
    char *argv[] = {"--", "-l", "9", "file.o"};
    char **remv;

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 4, argv), 0);
    EXPECT_TRUE(v == 5L);
    EXPECT_EQ_UINT(argparse_getremargc(&ctx), 3);
    remv = argparse_getremargv(&ctx);
    EXPECT_NOTNULL(remv);
    EXPECT_EQ_STR(remv[0], "-l");
    EXPECT_EQ_STR(remv[1], "9");
    EXPECT_EQ_STR(remv[2], "file.o");
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    long threshold = 0;
    struct argparse_opt opts[] = {
        OPT_DECL(_OPT_LONG, 't', "threshold", "", &threshold, OPT_REQUIRED,
                 long_cb),
        OPT_END(),
    };
    char *argv[] = {"--threshold=-12345"};

    long_cb_count = 0;
    long_cb_seen_dest = 0;
    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 1, argv), 0);
    EXPECT_TRUE(threshold == -12345L);
    EXPECT_EQ_INT(long_cb_count, 1);
    EXPECT_TRUE(long_cb_seen_dest == -12345L);
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    long a = 0;
    long b = 0;
    struct argparse_opt opts[] = {
        OPT_DECL(_OPT_LONG, 'a', "aaa", "", &a, OPT_REQUIRED, long_cb),
        OPT_DECL(_OPT_LONG, 'b', "bbb", "", &b, OPT_REQUIRED, long_cb),
        OPT_END(),
    };
    char *argv[] = {"-a1", "--bbb=2"};

    long_cb_count = 0;
    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 2, argv), 0);
    EXPECT_TRUE(a == 1L && b == 2L);
    EXPECT_EQ_INT(long_cb_count, 2);
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    long v = 3;
    struct argparse_opt opts[] = {
        OPT_LONG('l', "level", "", &v, OPT_REQUIRED),
        OPT_END(),
    };

    EXPECT_EQ_INT(argparse_parse(NULL, 1, NULL), -1);

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 0, NULL), 0);
    EXPECT_TRUE(v == 3L);
    EXPECT_EQ_UINT(argparse_getremargc(&ctx), 0);
    EXPECT_EQ_PTR(argparse_getremargv(&ctx), NULL);
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

#if LONG_MAX > INT_MAX
  {
    struct argparse ctx;
    long big = 0;
    struct argparse_opt opts[] = {
        OPT_LONG('b', "big", "", &big, OPT_REQUIRED),
        OPT_END(),
    };
    char bigbuf[64];
    snprintf(bigbuf, sizeof(bigbuf), "%ld", (long)INT_MAX + 1L);
    char *argv[] = {"--big", bigbuf};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 2, argv), 0);
    EXPECT_TRUE(big == (long)INT_MAX + 1L);
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }
#endif

  {
    struct argparse ctx;
    long z = -1;
    struct argparse_opt opts[] = {
        OPT_LONG('z', "zero", "", &z, OPT_REQUIRED),
        OPT_END(),
    };
    char *argv[] = {"-z0"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 1, argv), 0);
    EXPECT_TRUE(z == 0L);
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }
}
