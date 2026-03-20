#include <argparse.h>
#include <utest.h>

static int str_cb_count = 0;
static char *str_cb_seen_dest = NULL;

static void str_cb(struct argparse *ctx, struct argparse_opt *opt)
{
  (void)ctx;
  str_cb_count++;
  if (opt && opt->dest)
    str_cb_seen_dest = *(char **)opt->dest;
}

UTEST_CASE(string)
{
  {
    struct argparse ctx;
    char *out = NULL;
    struct argparse_opt opts[] = {
        OPT_STR('o', "output", "", &out, OPT_REQUIRED),
        OPT_END(),
    };
    char *argv[] = {"-o", "file.o"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 2, argv), 0);
    EXPECT_NOTNULL(out);
    EXPECT_EQ_STR(out, "file.o");
    EXPECT_EQ_PTR(out, argv[1]);
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    char *out = NULL;
    struct argparse_opt opts[] = {
        OPT_STR('o', "output", "", &out, OPT_REQUIRED),
        OPT_END(),
    };
    char *argv[] = {"-ofile.o"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 1, argv), 0);
    EXPECT_NOTNULL(out);
    EXPECT_EQ_STR(out, "file.o");
    EXPECT_EQ_PTR(out, argv[0] + 2);
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    char *out = NULL;
    struct argparse_opt opts[] = {
        OPT_STR('o', "output", "", &out, OPT_REQUIRED),
        OPT_END(),
    };
    char *argv[] = {"--output", "out.txt"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 2, argv), 0);
    EXPECT_NOTNULL(out);
    EXPECT_EQ_STR(out, "out.txt");
    EXPECT_EQ_PTR(out, argv[1]);
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    char *out = NULL;
    struct argparse_opt opts[] = {
        OPT_STR('o', "output", "", &out, OPT_REQUIRED),
        OPT_END(),
    };
    char *argv[] = {"--output=out.txt"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 1, argv), 0);
    EXPECT_NOTNULL(out);
    EXPECT_EQ_STR(out, "out.txt");
    EXPECT_EQ_PTR(out, argv[0] + 9);
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    char *a = NULL;
    char *b = NULL;
    char *c = NULL;
    struct argparse_opt opts[] = {
        OPT_STR('a', "aaa", "", &a, OPT_REQUIRED),
        OPT_STR('b', "bbb", "", &b, OPT_REQUIRED),
        OPT_STR('c', "ccc", "", &c, OPT_OPTIONAL),
        OPT_END(),
    };
    char *argv[] = {"-a", "one", "--bbb=two", "-cthree", "tail"};
    char **remv;

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 5, argv), 0);
    EXPECT_NOTNULL(a);
    EXPECT_NOTNULL(b);
    EXPECT_NOTNULL(c);
    EXPECT_EQ_STR(a, "one");
    EXPECT_EQ_STR(b, "two");
    EXPECT_EQ_STR(c, "three");
    EXPECT_EQ_UINT(argparse_getremargc(&ctx), 1);
    remv = argparse_getremargv(&ctx);
    EXPECT_NOTNULL(remv);
    EXPECT_EQ_STR(remv[0], "tail");
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    char *path = NULL;
    struct argparse_opt opts[] = {
        OPT_STR('I', "include", "", &path, OPT_REQUIRED),
        OPT_END(),
    };
    char *argv[] = {"-I", "./include/with spaces"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 2, argv), 0);
    EXPECT_NOTNULL(path);
    EXPECT_EQ_STR(path, "./include/with spaces");
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    char *flagish = NULL;
    struct argparse_opt opts[] = {
        OPT_STR('x', "extra", "", &flagish, OPT_REQUIRED),
        OPT_END(),
    };
    char *argv[] = {"-x", "-notanoption"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 2, argv), 0);
    EXPECT_NOTNULL(flagish);
    EXPECT_EQ_STR(flagish, "-notanoption");
    EXPECT_EQ_PTR(flagish, argv[1]);
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    char *tag = NULL;
    struct argparse_opt opts[] = {
        OPT_STR('t', "tag", "", &tag, OPT_OPTIONAL),
        OPT_END(),
    };
    char *argv[] = {"-t", "value"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 2, argv), 0);
    EXPECT_NOTNULL(tag);
    EXPECT_EQ_STR(tag, "value");
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    char *tag = NULL;
    struct argparse_opt opts[] = {
        OPT_STR('t', "tag", "", &tag, OPT_OPTIONAL),
        OPT_END(),
    };
    char *argv[] = {"-tglued"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 1, argv), 0);
    EXPECT_NOTNULL(tag);
    EXPECT_EQ_STR(tag, "glued");
    EXPECT_EQ_PTR(tag, argv[0] + 2);
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    char *tag = NULL;
    struct argparse_opt opts[] = {
        OPT_STR('t', "tag", "", &tag, OPT_OPTIONAL),
        OPT_END(),
    };
    char *argv[] = {"--tag", "opt"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 2, argv), 0);
    EXPECT_NOTNULL(tag);
    EXPECT_EQ_STR(tag, "opt");
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    char *tag = NULL;
    struct argparse_opt opts[] = {
        OPT_STR('t', "tag", "", &tag, OPT_OPTIONAL),
        OPT_END(),
    };
    char *argv[] = {"--tag=opt"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 1, argv), 0);
    EXPECT_NOTNULL(tag);
    EXPECT_EQ_STR(tag, "opt");
    EXPECT_EQ_PTR(tag, argv[0] + 6);
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    char *tag = (char *)"default";
    struct argparse_opt opts[] = {
        OPT_STR('t', "tag", "", &tag, OPT_OPTIONAL),
        OPT_END(),
    };
    char *argv[] = {"-t", "--looks-like-long"};
    char **remv;

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 2, argv), 0);
    EXPECT_NOTNULL(tag);
    EXPECT_EQ_STR(tag, "--looks-like-long");
    EXPECT_EQ_UINT(argparse_getremargc(&ctx), 0);
    remv = argparse_getremargv(&ctx);
    EXPECT_EQ_PTR(remv, NULL);
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    char *tag = (char *)"keep";
    struct argparse_opt opts[] = {
        OPT_STR('t', "tag", "", &tag, OPT_OPTIONAL),
        OPT_END(),
    };
    char empty[] = "";
    char *argv[] = {"-t", empty};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 2, argv), 0);
    EXPECT_NOTNULL(tag);
    EXPECT_EQ_STR(tag, "");
    EXPECT_EQ_PTR(tag, empty);
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    char *name = NULL;
    struct argparse_opt opts[] = {
        OPT_STR('n', "name", "", &name, OPT_REQUIRED),
        OPT_END(),
    };
    char *argv[] = {"-Z", "-n", "x"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 3, argv), -1);
    EXPECT_NULL(name);
    EXPECT_NE_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    char *name = NULL;
    struct argparse_opt opts[] = {
        OPT_STR('n', "name", "", &name, OPT_REQUIRED),
        OPT_END(),
    };
    char *argv[] = {"--badopt", "-n", "ok"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    argparse_setflags(&ctx, ARG_IGNORE);
    EXPECT_EQ_INT(argparse_parse(&ctx, 3, argv), 0);
    EXPECT_NOTNULL(name);
    EXPECT_EQ_STR(name, "ok");
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    char *name = NULL;
    struct argparse_opt opts[] = {
        OPT_STR('n', "name", "", &name, OPT_REQUIRED),
        OPT_END(),
    };
    char *argv[] = {"--", "-n", "v", "pos"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 4, argv), 0);
    EXPECT_NULL(name);
    EXPECT_EQ_UINT(argparse_getremargc(&ctx), 3);
    char **remv = argparse_getremargv(&ctx);
    EXPECT_NOTNULL(remv);
    EXPECT_EQ_STR(remv[0], "-n");
    EXPECT_EQ_STR(remv[1], "v");
    EXPECT_EQ_STR(remv[2], "pos");
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    char *path = NULL;
    struct argparse_opt opts[] = {
        OPT_DECL(_OPT_STR, 'p', "path", "", &path, OPT_REQUIRED, str_cb),
        OPT_END(),
    };
    char *argv[] = {"--path=/usr/local"};

    str_cb_count = 0;
    str_cb_seen_dest = NULL;
    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 1, argv), 0);
    EXPECT_NOTNULL(path);
    EXPECT_EQ_STR(path, "/usr/local");
    EXPECT_EQ_INT(str_cb_count, 1);
    EXPECT_NOTNULL(str_cb_seen_dest);
    EXPECT_EQ_STR(str_cb_seen_dest, "/usr/local");
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    char *u = NULL;
    char *v = NULL;
    struct argparse_opt opts[] = {
        OPT_DECL(_OPT_STR, 'u', "u", "", &u, OPT_REQUIRED, str_cb),
        OPT_DECL(_OPT_STR, 'v', "v", "", &v, OPT_REQUIRED, str_cb),
        OPT_END(),
    };
    char *argv[] = {"-ua", "--v=b"};

    str_cb_count = 0;
    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 2, argv), 0);
    EXPECT_EQ_STR(u, "a");
    EXPECT_EQ_STR(v, "b");
    EXPECT_EQ_INT(str_cb_count, 2);
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    char *s = (char *)"init";
    struct argparse_opt opts[] = {
        OPT_STR('s', "str", "", &s, OPT_REQUIRED),
        OPT_END(),
    };

    EXPECT_EQ_INT(argparse_parse(NULL, 1, NULL), -1);

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 0, NULL), 0);
    EXPECT_EQ_STR(s, "init");
    EXPECT_EQ_UINT(argparse_getremargc(&ctx), 0);
    EXPECT_EQ_PTR(argparse_getremargv(&ctx), NULL);
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    char *utf = NULL;
    struct argparse_opt opts[] = {
        OPT_STR('m', "msg", "", &utf, OPT_REQUIRED),
        OPT_END(),
    };
    char *argv[] = {"-m", "hello \xC3\xBC"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 2, argv), 0);
    EXPECT_NOTNULL(utf);
    EXPECT_EQ_STR(utf, "hello \xC3\xBC");
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    char *eq = NULL;
    struct argparse_opt opts[] = {
        OPT_STR('e', "eq", "", &eq, OPT_REQUIRED),
        OPT_END(),
    };
    char *argv[] = {"--eq=a=b=c"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 1, argv), 0);
    EXPECT_NOTNULL(eq);
    EXPECT_EQ_STR(eq, "a=b=c");
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }
}
