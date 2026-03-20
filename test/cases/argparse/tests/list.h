#include <argparse.h>
#include <utest.h>

static int list_cb_count = 0;

static void list_cb(struct argparse *ctx, struct argparse_opt *opt)
{
  (void)ctx;
  (void)opt;
  list_cb_count++;
}

UTEST_CASE(list)
{
  {
    struct argparse ctx;
    struct argparse_list *inc = NULL;
    struct argparse_opt opts[] = {
        OPT_LIST('I', "include", "", &inc),
        OPT_END(),
    };
    char *argv[] = {"-I./include", "-I./arch", "-I./src"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 3, argv), 0);
    EXPECT_NOTNULL(inc);
    EXPECT_EQ_UINT(argparse_getlistsz(inc), 3);
    EXPECT_NOTNULL(argparse_getlist(inc));
    {
      const char *exp[] = {"./include", "./arch", "./src"};
      char **items = argparse_getlist(inc);
      for (size_t i = 0; i < 3; i++)
        EXPECT_EQ_STR(items[i], exp[i]);
    }
    EXPECT_EQ_UINT(argparse_getremargc(&ctx), 0);
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
    char *argv[] = {"-I", "./include", "-I", "./arch"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 4, argv), 0);
    EXPECT_NOTNULL(inc);
    EXPECT_EQ_UINT(argparse_getlistsz(inc), 2);
    {
      const char *exp[] = {"./include", "./arch"};
      char **items = argparse_getlist(inc);
      for (size_t i = 0; i < 2; i++)
        EXPECT_EQ_STR(items[i], exp[i]);
    }
    EXPECT_EQ_UINT(argparse_getremargc(&ctx), 0);
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
    char *argv[] = {"--include=./a", "--include", "./b"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 3, argv), 0);
    EXPECT_NOTNULL(inc);
    EXPECT_EQ_UINT(argparse_getlistsz(inc), 2);
    {
      const char *exp[] = {"./a", "./b"};
      char **items = argparse_getlist(inc);
      for (size_t i = 0; i < 2; i++)
        EXPECT_EQ_STR(items[i], exp[i]);
    }
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
    char *argv[] = {"-I./first", "./positional", "-I./second"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 3, argv), 0);
    EXPECT_NOTNULL(inc);
    EXPECT_EQ_UINT(argparse_getlistsz(inc), 2);
    {
      const char *exp[] = {"./first", "./second"};
      char **items = argparse_getlist(inc);
      for (size_t i = 0; i < 2; i++)
        EXPECT_EQ_STR(items[i], exp[i]);
    }
    EXPECT_EQ_UINT(argparse_getremargc(&ctx), 1);
    EXPECT_NOTNULL(argparse_getremargv(&ctx));
    EXPECT_EQ_STR(argparse_getremargv(&ctx)[0], "./positional");
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
    char *argv[] = {"-I", "./include", "./not-listed"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 3, argv), 0);
    EXPECT_NOTNULL(inc);
    EXPECT_EQ_UINT(argparse_getlistsz(inc), 1);
    {
      const char *exp[] = {"./include"};
      char **items = argparse_getlist(inc);
      for (size_t i = 0; i < 1; i++)
        EXPECT_EQ_STR(items[i], exp[i]);
    }
    EXPECT_EQ_UINT(argparse_getremargc(&ctx), 1);
    EXPECT_EQ_STR(argparse_getremargv(&ctx)[0], "./not-listed");
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
    char *argv[] = {"-I./b", "-I./a", "-I./c"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 3, argv), 0);
    EXPECT_NOTNULL(inc);
    EXPECT_EQ_UINT(argparse_getlistsz(inc), 3);
    {
      const char *exp[] = {"./b", "./a", "./c"};
      char **items = argparse_getlist(inc);
      for (size_t i = 0; i < 3; i++)
        EXPECT_EQ_STR(items[i], exp[i]);
    }
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
    char *argv[] = {"-I./dup", "-I./other", "-I./dup"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 3, argv), 0);
    EXPECT_NOTNULL(inc);
    EXPECT_EQ_UINT(argparse_getlistsz(inc), 3);
    {
      const char *exp[] = {"./dup", "./other", "./dup"};
      char **items = argparse_getlist(inc);
      for (size_t i = 0; i < 3; i++)
        EXPECT_EQ_STR(items[i], exp[i]);
    }
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    struct argparse_list *inc = NULL;
    struct argparse_list *lib = NULL;
    struct argparse_opt opts[] = {
        OPT_LIST('I', "include", "", &inc),
        OPT_LIST('L', "library", "", &lib),
        OPT_END(),
    };
    char *argv[] = {"-I./inc", "-L./lib1", "-I./src", "-L./lib2"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 4, argv), 0);
    EXPECT_NOTNULL(inc);
    EXPECT_NOTNULL(lib);
    EXPECT_EQ_UINT(argparse_getlistsz(inc), 2);
    EXPECT_EQ_UINT(argparse_getlistsz(lib), 2);
    {
      const char *expi[] = {"./inc", "./src"};
      const char *expl[] = {"./lib1", "./lib2"};
      char **itemsi = argparse_getlist(inc);
      char **itemsl = argparse_getlist(lib);
      for (size_t i = 0; i < 2; i++) {
        EXPECT_EQ_STR(itemsi[i], expi[i]);
        EXPECT_EQ_STR(itemsl[i], expl[i]);
      }
    }
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
    char *argv[] = {"-I./here", "--", "-I./after", "pos"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 4, argv), 0);
    EXPECT_NOTNULL(inc);
    EXPECT_EQ_UINT(argparse_getlistsz(inc), 1);
    {
      const char *exp[] = {"./here"};
      char **items = argparse_getlist(inc);
      for (size_t i = 0; i < 1; i++)
        EXPECT_EQ_STR(items[i], exp[i]);
    }
    EXPECT_EQ_UINT(argparse_getremargc(&ctx), 2);
    EXPECT_EQ_STR(argparse_getremargv(&ctx)[0], "-I./after");
    EXPECT_EQ_STR(argparse_getremargv(&ctx)[1], "pos");
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    struct argparse_list *inc = NULL;
    struct argparse_opt opts[] = {
        OPT_DECL(_OPT_LIST, 'I', "include", "", &inc, OPT_REQUIRED, list_cb),
        OPT_END(),
    };
    char *argv[] = {"-I./a", "-I./b"};

    list_cb_count = 0;
    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 2, argv), 0);
    EXPECT_NOTNULL(inc);
    EXPECT_EQ_UINT(argparse_getlistsz(inc), 2);
    {
      const char *exp[] = {"./a", "./b"};
      char **items = argparse_getlist(inc);
      for (size_t i = 0; i < 2; i++)
        EXPECT_EQ_STR(items[i], exp[i]);
    }
    EXPECT_EQ_INT(list_cb_count, 2);
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
    char *argv[] = {"-I"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 1, argv), -1);
    EXPECT_NULL(inc);
    EXPECT_NE_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    struct argparse_list *inc = NULL;
    struct argparse_opt opts[] = {
        OPT_LIST('I', "include", "", &inc),
        OPT_END(),
    };
    char *argv[] = {"--include"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 1, argv), -1);
    EXPECT_NULL(inc);
    EXPECT_NE_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    struct argparse_list *inc = NULL;
    struct argparse_opt opts[] = {
        OPT_LIST('I', "include", "", &inc),
        OPT_END(),
    };
    char *argv[] = {"-X", "-I./x"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 2, argv), -1);
    EXPECT_NULL(inc);
    EXPECT_NE_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    struct argparse_list *inc = NULL;
    struct argparse_opt opts[] = {
        OPT_LIST('I', "include", "", &inc),
        OPT_END(),
    };
    char *argv[] = {"--unknown", "-I./ok"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    argparse_setflags(&ctx, ARG_IGNORE);
    EXPECT_EQ_INT(argparse_parse(&ctx, 2, argv), 0);
    EXPECT_NOTNULL(inc);
    EXPECT_EQ_UINT(argparse_getlistsz(inc), 1);
    {
      const char *exp[] = {"./ok"};
      char **items = argparse_getlist(inc);
      for (size_t i = 0; i < 1; i++)
        EXPECT_EQ_STR(items[i], exp[i]);
    }
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
    char *argv[] = {"pos1", "pos2"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 2, argv), 0);
    EXPECT_NULL(inc);
    EXPECT_EQ_UINT(argparse_getremargc(&ctx), 2);
    EXPECT_EQ_STR(argparse_getremargv(&ctx)[0], "pos1");
    EXPECT_EQ_STR(argparse_getremargv(&ctx)[1], "pos2");
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
    char *argv[] = {"-I./only"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 1, argv), 0);
    EXPECT_NOTNULL(inc);
    EXPECT_EQ_UINT(argparse_getlistsz(inc), 1);
    {
      const char *exp[] = {"./only"};
      char **items = argparse_getlist(inc);
      for (size_t i = 0; i < 1; i++)
        EXPECT_EQ_STR(items[i], exp[i]);
    }
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
    char *argv[] = {"-I./with space", "-I./tab\tok"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 2, argv), 0);
    EXPECT_NOTNULL(inc);
    EXPECT_EQ_UINT(argparse_getlistsz(inc), 2);
    {
      const char *exp[] = {"./with space", "./tab\tok"};
      char **items = argparse_getlist(inc);
      for (size_t i = 0; i < 2; i++)
        EXPECT_EQ_STR(items[i], exp[i]);
    }
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
    char empty[] = "";
    char *argv[] = {"-I", empty, "-I./x"};

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 3, argv), 0);
    EXPECT_NOTNULL(inc);
    EXPECT_EQ_UINT(argparse_getlistsz(inc), 2);
    {
      const char *exp[] = {"", "./x"};
      char **items = argparse_getlist(inc);
      for (size_t i = 0; i < 2; i++)
        EXPECT_EQ_STR(items[i], exp[i]);
    }
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

    EXPECT_EQ_INT(argparse_parse(NULL, 1, NULL), -1);

    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    EXPECT_EQ_INT(argparse_parse(&ctx, 0, NULL), 0);
    EXPECT_NULL(inc);
    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }
}
