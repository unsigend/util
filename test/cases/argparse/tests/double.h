#include <argparse.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <utest.h>

static int double_cb_count = 0;
static double double_cb_seen_dest = 0.0;

static void double_cb(struct argparse *ctx, struct argparse_opt *opt)
{
  (void)ctx;
  double_cb_count++;
  if (opt && opt->dest)
    double_cb_seen_dest = *(double *)opt->dest;
}

UTEST_CASE(double)
{
  {
    struct argparse ctx;
    double x = 0.0;
    struct argparse_opt opts[] = {
        OPT_DOUBLE('d', "depth", "", &x, OPT_REQUIRED),
        OPT_END(),
    };
    char *argv[] = {"-d", "2.5"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 2, argv), 0);
    EXPECT_EQ_DOUBLE(x, 2.5);
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }
  {
    struct argparse ctx;
    double x = 0.0;
    struct argparse_opt opts[] = {
        OPT_DOUBLE('d', "depth", "", &x, OPT_REQUIRED),
        OPT_END(),
    };
    char *argv[] = {"-d3.25"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 1, argv), 0);
    EXPECT_EQ_DOUBLE(x, 3.25);
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    double x = 0.0;
    struct argparse_opt opts[] = {
        OPT_DOUBLE('d', "depth", "", &x, OPT_REQUIRED),
        OPT_END(),
    };
    char *argv[] = {"--depth", "1.0"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 2, argv), 0);
    EXPECT_EQ_DOUBLE(x, 1.0);
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    double x = 0.0;
    struct argparse_opt opts[] = {
        OPT_DOUBLE('d', "depth", "", &x, OPT_REQUIRED),
        OPT_END(),
    };
    char *argv[] = {"--depth=-4.5"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 1, argv), 0);
    EXPECT_EQ_DOUBLE(x, -4.5);
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    double a = 0.0;
    double b = 0.0;
    double c = 0.0;
    struct argparse_opt opts[] = {
        OPT_DOUBLE('a', "alpha", "", &a, OPT_REQUIRED),
        OPT_DOUBLE('b', "beta", "", &b, OPT_REQUIRED),
        OPT_DOUBLE('c', "gamma", "", &c, OPT_OPTIONAL),
        OPT_END(),
    };
    char *argv[] = {"-a", "0.5", "--beta=1.25", "-c2", "out.bin"};
    char **remv;

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 5, argv), 0);
    EXPECT_EQ_DOUBLE(a, 0.5);
    EXPECT_EQ_DOUBLE(b, 1.25);
    EXPECT_EQ_DOUBLE(c, 2.0);
    EXPECT_EQ_UINT(argparse_getremargc(&ctx), 1);
    remv = argparse_getremargv(&ctx);
    EXPECT_NOTNULL(remv);
    EXPECT_EQ_STR(remv[0], "out.bin");
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    double sci = 0.0;
    double expv = 0.0;
    double plus = 0.0;
    struct argparse_opt opts[] = {
        OPT_DOUBLE('s', "sci", "", &sci, OPT_REQUIRED),
        OPT_DOUBLE('e', "exp", "", &expv, OPT_REQUIRED),
        OPT_DOUBLE('p', "plus", "", &plus, OPT_REQUIRED),
        OPT_END(),
    };
    char *argv[] = {"-s", "1e2", "--exp", "2.5e-1", "--plus", "+3.0"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 5, argv), 0);
    EXPECT_EQ_DOUBLE(sci, 100.0);
    EXPECT_EQ_DOUBLE(expv, 0.25);
    EXPECT_EQ_DOUBLE(plus, 3.0);
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    double x = 0.0;
    struct argparse_opt opts[] = {
        OPT_DOUBLE('x', "hexflt", "", &x, OPT_REQUIRED),
        OPT_END(),
    };
    char *argv[] = {"--hexflt=0x1p-1"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 1, argv), 0);
    EXPECT_EQ_DOUBLE(x, 0.5);
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    double x = 7.0;
    struct argparse_opt opts[] = {
        OPT_DOUBLE('n', "number", "", &x, OPT_OPTIONAL),
        OPT_END(),
    };
    char *argv[] = {"-n8.5"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 1, argv), 0);
    EXPECT_EQ_DOUBLE(x, 8.5);
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    double x = 7.0;
    struct argparse_opt opts[] = {
        OPT_DOUBLE('n', "number", "", &x, OPT_OPTIONAL),
        OPT_END(),
    };
    char *argv[] = {"-n", "9.0"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 2, argv), 0);
    EXPECT_EQ_DOUBLE(x, 9.0);
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    double x = 7.0;
    struct argparse_opt opts[] = {
        OPT_DOUBLE('n', "number", "", &x, OPT_OPTIONAL),
        OPT_END(),
    };
    char *argv[] = {"--number", "10.5"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 2, argv), 0);
    EXPECT_EQ_DOUBLE(x, 10.5);
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    double x = 7.0;
    struct argparse_opt opts[] = {
        OPT_DOUBLE('n', "number", "", &x, OPT_OPTIONAL),
        OPT_END(),
    };
    char *argv[] = {"--number=11.25"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 1, argv), 0);
    EXPECT_EQ_DOUBLE(x, 11.25);
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    double x = 7.0;
    struct argparse_opt opts[] = {
        OPT_DOUBLE('n', "number", "", &x, OPT_OPTIONAL),
        OPT_END(),
    };
    char *argv[] = {"-n", "not_a_float"};
    char **remv;

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 2, argv), 0);
    EXPECT_EQ_DOUBLE(x, 7.0);
    EXPECT_EQ_UINT(argparse_getremargc(&ctx), 1);
    remv = argparse_getremargv(&ctx);
    EXPECT_NOTNULL(remv);
    EXPECT_EQ_STR(remv[0], "not_a_float");
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    double x = 0.0;
    struct argparse_opt opts[] = {
        OPT_DOUBLE('d', "depth", "", &x, OPT_REQUIRED),
        OPT_END(),
    };
    char *argv[] = {"-d", "3.14x"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 2, argv), -1);
    EXPECT_EQ_DOUBLE(x, 0.0);
    EXPECT_NE_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    double x = 0.0;
    struct argparse_opt opts[] = {
        OPT_DOUBLE('d', "depth", "", &x, OPT_REQUIRED),
        OPT_END(),
    };
    char *argv[] = {"--depth"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 1, argv), -1);
    EXPECT_EQ_DOUBLE(x, 0.0);
    EXPECT_NE_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    double x = 0.0;
    struct argparse_opt opts[] = {
        OPT_DOUBLE('d', "depth", "", &x, OPT_REQUIRED),
        OPT_END(),
    };
    char *argv[] = {"--depth="};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 1, argv), -1);
    EXPECT_EQ_DOUBLE(x, 0.0);
    EXPECT_NE_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    double x = 0.0;
    struct argparse_opt opts[] = {
        OPT_DOUBLE('d', "depth", "", &x, OPT_REQUIRED),
        OPT_END(),
    };
    char *argv[] = {"-d", "1e9999"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 2, argv), -1);
    EXPECT_EQ_DOUBLE(x, 0.0);
    EXPECT_NE_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    double x = 0.0;
    struct argparse_opt opts[] = {
        OPT_DOUBLE('d', "depth", "", &x, OPT_REQUIRED),
        OPT_END(),
    };
    char *argv[] = {"-X", "-d", "1.0"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 3, argv), -1);
    EXPECT_EQ_DOUBLE(x, 0.0);
    EXPECT_NE_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    double x = 0.0;
    struct argparse_opt opts[] = {
        OPT_DOUBLE('d', "depth", "", &x, OPT_REQUIRED),
        OPT_END(),
    };
    char *argv[] = {"--unknown", "-d", "2.0"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    argparse_setflags(&ctx, ARG_IGNORE);
    EXPECT_EQ_INT(argparse_parse(&ctx, 3, argv), 0);
    EXPECT_EQ_DOUBLE(x, 2.0);
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }
  {
    struct argparse ctx;
    double x = 1.0;
    struct argparse_opt opts[] = {
        OPT_DOUBLE('d', "depth", "", &x, OPT_REQUIRED),
        OPT_END(),
    };
    char *argv[] = {"--", "-d", "9.0", "data.txt"};
    char **remv;

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 4, argv), 0);
    EXPECT_EQ_DOUBLE(x, 1.0);
    EXPECT_EQ_UINT(argparse_getremargc(&ctx), 3);
    remv = argparse_getremargv(&ctx);
    EXPECT_NOTNULL(remv);
    EXPECT_EQ_STR(remv[0], "-d");
    EXPECT_EQ_STR(remv[1], "9.0");
    EXPECT_EQ_STR(remv[2], "data.txt");
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    double t = 0.0;
    struct argparse_opt opts[] = {
        OPT_DECL(_OPT_DOUBLE, 't', "tol", "", &t, OPT_REQUIRED, double_cb),
        OPT_END(),
    };
    char *argv[] = {"--tol", "0.001"};

    double_cb_count = 0;
    double_cb_seen_dest = 0.0;
    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 2, argv), 0);
    EXPECT_EQ_DOUBLE(t, 0.001);
    EXPECT_EQ_INT(double_cb_count, 1);
    EXPECT_EQ_DOUBLE(double_cb_seen_dest, 0.001);
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    double a = 0.0;
    double b = 0.0;
    struct argparse_opt opts[] = {
        OPT_DECL(_OPT_DOUBLE, 'a', "aaa", "", &a, OPT_REQUIRED, double_cb),
        OPT_DECL(_OPT_DOUBLE, 'b', "bbb", "", &b, OPT_REQUIRED, double_cb),
        OPT_END(),
    };
    char *argv[] = {"-a0.5", "--bbb=1.5"};

    double_cb_count = 0;
    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 2, argv), 0);
    EXPECT_EQ_DOUBLE(a, 0.5);
    EXPECT_EQ_DOUBLE(b, 1.5);
    EXPECT_EQ_INT(double_cb_count, 2);
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    double x = 3.0;
    struct argparse_opt opts[] = {
        OPT_DOUBLE('d', "depth", "", &x, OPT_REQUIRED),
        OPT_END(),
    };

    EXPECT_EQ_INT(argparse_parse(NULL, 1, NULL), -1);

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 0, NULL), 0);
    EXPECT_EQ_DOUBLE(x, 3.0);
    EXPECT_EQ_UINT(argparse_getremargc(&ctx), 0);
    EXPECT_EQ_PTR(argparse_getremargv(&ctx), NULL);
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    double x = 0.0;
    struct argparse_opt opts[] = {
        OPT_DOUBLE('d', "depth", "", &x, OPT_REQUIRED),
        OPT_END(),
    };
    char *argv[] = {"-d", "  \t42"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 2, argv), 0);
    EXPECT_EQ_DOUBLE(x, 42.0);
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    double x = 0.0;
    struct argparse_opt opts[] = {
        OPT_DOUBLE('d', "depth", "", &x, OPT_REQUIRED),
        OPT_END(),
    };
    char *argv[] = {"-d", "inf"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 2, argv), 0);
    EXPECT_EQ_DOUBLE(x, HUGE_VAL);
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }
}
