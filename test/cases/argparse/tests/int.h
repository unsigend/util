#include <argparse.h>
#include <limits.h>
#include <utest.h>

static int int_cb_count = 0;
static int int_cb_seen_dest = 0;

static void int_cb(struct argparse *ctx, struct argparse_opt *opt)
{
  (void)ctx;
  int_cb_count++;
  if (opt && opt->dest)
    int_cb_seen_dest = *(int *)opt->dest;
}

UTEST_CASE(int)
{
  {
    struct argparse ctx;
    int level = 0;
    struct argparse_opt opts[] = {
        OPT_INT('O', "opt-level", "", &level, OPT_REQUIRED),
        OPT_END(),
    };
    char *argv[] = {"-O", "2"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 2, argv), 0);
    EXPECT_EQ_INT(level, 2);
    EXPECT_EQ_UINT(argparse_getremargc(&ctx), 0);
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    int jobs = 0;
    struct argparse_opt opts[] = {
        OPT_INT('j', "jobs", "", &jobs, OPT_REQUIRED),
        OPT_END(),
    };
    char *argv[] = {"--jobs", "16"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 2, argv), 0);
    EXPECT_EQ_INT(jobs, 16);
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    int number = 0;
    struct argparse_opt opts[] = {
        OPT_INT('n', "number", "", &number, OPT_REQUIRED),
        OPT_END(),
    };
    char *argv[] = {"-n6"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 1, argv), 0);
    EXPECT_EQ_INT(number, 6);
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    int number = 0;
    struct argparse_opt opts[] = {
        OPT_INT('n', "number", "", &number, OPT_REQUIRED),
        OPT_END(),
    };
    char *argv[] = {"-n", "6"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 2, argv), 0);
    EXPECT_EQ_INT(number, 6);
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    int number = 0;
    struct argparse_opt opts[] = {
        OPT_INT('n', "number", "", &number, OPT_REQUIRED),
        OPT_END(),
    };
    char *argv[] = {"--number", "6"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 2, argv), 0);
    EXPECT_EQ_INT(number, 6);
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    int number = 0;
    struct argparse_opt opts[] = {
        OPT_INT('n', "number", "", &number, OPT_REQUIRED),
        OPT_END(),
    };
    char *argv[] = {"--number=6"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 1, argv), 0);
    EXPECT_EQ_INT(number, 6);
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    int level = -1;
    int jobs = -1;
    int warn = -1;
    struct argparse_opt opts[] = {
        OPT_INT('O', "opt-level", "", &level, OPT_REQUIRED),
        OPT_INT('j', "jobs", "", &jobs, OPT_REQUIRED),
        OPT_INT('W', "warn", "", &warn, OPT_OPTIONAL),
        OPT_END(),
    };
    char *argv[] = {"-O", "3", "--jobs", "4", "-W", "2", "file1.c", "file2.c"};
    char **remv;

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 8, argv), 0);
    EXPECT_EQ_INT(level, 3);
    EXPECT_EQ_INT(jobs, 4);
    EXPECT_EQ_INT(warn, 2);
    EXPECT_EQ_UINT(argparse_getremargc(&ctx), 2);
    remv = argparse_getremargv(&ctx);
    EXPECT_NOTNULL(remv);
    EXPECT_EQ_STR(remv[0], "file1.c");
    EXPECT_EQ_STR(remv[1], "file2.c");
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    int number = 7;
    struct argparse_opt opts[] = {
        OPT_INT('n', "number", "", &number, OPT_OPTIONAL),
        OPT_END(),
    };
    char *argv[] = {"-n6"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 1, argv), 0);
    EXPECT_EQ_INT(number, 6);
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    int number = 7;
    struct argparse_opt opts[] = {
        OPT_INT('n', "number", "", &number, OPT_OPTIONAL),
        OPT_END(),
    };
    char *argv[] = {"--number", "6"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 2, argv), 0);
    EXPECT_EQ_INT(number, 6);
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    int number = 7;
    struct argparse_opt opts[] = {
        OPT_INT('n', "number", "", &number, OPT_OPTIONAL),
        OPT_END(),
    };
    char *argv[] = {"--number=6"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 1, argv), 0);
    EXPECT_EQ_INT(number, 6);
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    int signedv = 0;
    int zerov = -1;
    int hexx = 0;
    struct argparse_opt opts[] = {
        OPT_INT('s', "signed", "", &signedv, OPT_REQUIRED),
        OPT_INT('z', "zero", "", &zerov, OPT_REQUIRED),
        OPT_INT('x', "hex", "", &hexx, OPT_REQUIRED),
        OPT_END(),
    };
    char *argv[] = {"--signed", "-12", "--zero", "0", "--hex", "0x10"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 6, argv), 0);
    EXPECT_EQ_INT(signedv, -12);
    EXPECT_EQ_INT(zerov, 0);
    EXPECT_EQ_INT(hexx, 16);
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    int hexx = 0;
    int octv = 0;
    int negv = 0;
    int plusv = 0;
    struct argparse_opt opts[] = {
        OPT_INT('x', "hex", "", &hexx, OPT_REQUIRED),
        OPT_INT('o', "oct", "", &octv, OPT_REQUIRED),
        OPT_INT('n', "neg", "", &negv, OPT_REQUIRED),
        OPT_INT('p', "plus", "", &plusv, OPT_REQUIRED),
        OPT_END(),
    };
    char *argv[] = {"-x0x20", "-o", "077", "--neg=-9", "--plus", "+12"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 5, argv), 0);
    EXPECT_EQ_INT(hexx, 32);
    EXPECT_EQ_INT(octv, 63);
    EXPECT_EQ_INT(negv, -9);
    EXPECT_EQ_INT(plusv, 12);
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    int value = 7;
    struct argparse_opt opts[] = {
        OPT_INT('n', "number", "", &value, OPT_OPTIONAL),
        OPT_END(),
    };
    char *argv[] = {"-n", "33"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 2, argv), 0);
    EXPECT_EQ_INT(value, 33);
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    int value = 7;
    struct argparse_opt opts[] = {
        OPT_INT('n', "number", "", &value, OPT_OPTIONAL),
        OPT_END(),
    };
    char *argv[] = {"-n", "input.c"};
    char **remv;

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 2, argv), 0);
    EXPECT_EQ_INT(value, 7);
    EXPECT_EQ_UINT(argparse_getremargc(&ctx), 1);
    remv = argparse_getremargv(&ctx);
    EXPECT_NOTNULL(remv);
    EXPECT_EQ_STR(remv[0], "input.c");
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    int level = 0;
    struct argparse_opt opts[] = {
        OPT_INT('O', "opt-level", "", &level, OPT_REQUIRED),
        OPT_END(),
    };
    char *argv[] = {"-O", "12abc"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 2, argv), -1);
    EXPECT_EQ_INT(level, 0);
    EXPECT_NE_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    int level = 0;
    struct argparse_opt opts[] = {
        OPT_INT('O', "opt-level", "", &level, OPT_REQUIRED),
        OPT_END(),
    };
    char *argv[] = {"--opt-level"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 1, argv), -1);
    EXPECT_EQ_INT(level, 0);
    EXPECT_NE_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    int level = 0;
    struct argparse_opt opts[] = {
        OPT_INT('O', "opt-level", "", &level, OPT_REQUIRED),
        OPT_END(),
    };
    char *argv[] = {"-O", "2147483648"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 2, argv), -1);
    EXPECT_EQ_INT(level, 0);
    EXPECT_NE_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    int level = 0;
    struct argparse_opt opts[] = {
        OPT_INT('O', "opt-level", "", &level, OPT_REQUIRED),
        OPT_END(),
    };
    char *argv[] = {"-X", "-O", "2"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 3, argv), -1);
    EXPECT_EQ_INT(level, 0);
    EXPECT_NE_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    int level = 0;
    struct argparse_opt opts[] = {
        OPT_INT('O', "opt-level", "", &level, OPT_REQUIRED),
        OPT_END(),
    };
    char *argv[] = {"--unknown", "-O", "2"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    argparse_setflags(&ctx, ARG_IGNORE);
    EXPECT_EQ_INT(argparse_parse(&ctx, 3, argv), 0);
    EXPECT_EQ_INT(level, 2);
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    int jobs = 3;
    struct argparse_opt opts[] = {
        OPT_INT('j', "jobs", "", &jobs, OPT_REQUIRED),
        OPT_END(),
    };
    char *argv[] = {"--", "-j", "9", "file.o"};
    char **remv;

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 4, argv), 0);
    EXPECT_EQ_INT(jobs, 3);
    EXPECT_EQ_UINT(argparse_getremargc(&ctx), 3);
    remv = argparse_getremargv(&ctx);
    EXPECT_NOTNULL(remv);
    EXPECT_EQ_STR(remv[0], "-j");
    EXPECT_EQ_STR(remv[1], "9");
    EXPECT_EQ_STR(remv[2], "file.o");
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    int threshold = 0;
    struct argparse_opt opts[] = {
        OPT_DECL(_OPT_INT, 't', "threshold", "", &threshold, OPT_REQUIRED,
                 int_cb),
        OPT_END(),
    };
    char *argv[] = {"--threshold", "42"};

    int_cb_count = 0;
    int_cb_seen_dest = 0;
    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 2, argv), 0);
    EXPECT_EQ_INT(threshold, 42);
    EXPECT_EQ_INT(int_cb_count, 1);
    EXPECT_EQ_INT(int_cb_seen_dest, 42);
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    int value = 5;
    struct argparse_opt opts[] = {
        OPT_INT('n', "number", "", &value, OPT_REQUIRED),
        OPT_END(),
    };

    EXPECT_EQ_INT(argparse_parse(NULL, 1, NULL), -1);

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 0, NULL), 0);
    EXPECT_EQ_INT(value, 5);
    EXPECT_EQ_UINT(argparse_getremargc(&ctx), 0);
    EXPECT_EQ_PTR(argparse_getremargv(&ctx), NULL);
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    int minv = 0;
    int maxv = 0;
    struct argparse_opt opts[] = {
        OPT_INT('m', "min", "", &minv, OPT_REQUIRED),
        OPT_INT('M', "max", "", &maxv, OPT_REQUIRED),
        OPT_END(),
    };
    char *argv[] = {"--min", "-2147483648", "--max", "2147483647"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 4, argv), 0);
    EXPECT_EQ_INT(minv, INT_MIN);
    EXPECT_EQ_INT(maxv, INT_MAX);
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }
}