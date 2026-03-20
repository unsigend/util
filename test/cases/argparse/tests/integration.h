#include <argparse.h>
#include <stdbool.h>
#include <utest.h>

UTEST_CASE(gcc)
{
  {
    struct argparse ctx;
    bool cflag = false;
    bool gflag = false;
    bool vflag = false;
    bool gcsec = false;
    int optlevel = -1;
    int num = -1;
    long longnum = -1;
    double ratio = 0.0;
    char *define = NULL;
    char *out = NULL;
    char *std = NULL;
    char *sysroot = NULL;
    struct argparse_list *inc = NULL;
    struct argparse_list *libpaths = NULL;
    struct argparse_list *libs = NULL;

    struct argparse_opt opts[] = {
        OPT_BOOL('c', "compile-only", "", &cflag),
        OPT_BOOL('g', "debug", "", &gflag),
        OPT_BOOL('v', "verbose", "", &vflag),
        OPT_BOOL('q', "gc-sections", "", &gcsec),
        OPT_INT('O', "opt-level", "", &optlevel, OPT_REQUIRED),
        OPT_INT('n', "num", "", &num, OPT_OPTIONAL),
        OPT_LONG('z', "long-num", "", &longnum, OPT_REQUIRED),
        OPT_DOUBLE('r', "ratio", "", &ratio, OPT_REQUIRED),
        OPT_STR('D', "define", "", &define, OPT_REQUIRED),
        OPT_STR('o', "output", "", &out, OPT_REQUIRED),
        OPT_STR('s', "std", "", &std, OPT_REQUIRED),
        OPT_STR('y', "sysroot", "", &sysroot, OPT_REQUIRED),
        OPT_LIST('I', "include", "", &inc),
        OPT_LIST('L', "libpath", "", &libpaths),
        OPT_LIST('l', "library", "", &libs),
        OPT_END(),
    };

    char *argv[100];
    const char *exprem[100];
    int argc = 0;
    int expc = 0;

    argv[argc++] = "-cXg";
    argv[argc++] = "-O2";
    argv[argc++] = "-v";
    argv[argc++] = "-Z";
    argv[argc++] = "--gc-sections";
    argv[argc++] = "-n7";
    argv[argc++] = "-DNAME=VALUE";
    argv[argc++] = "-o";
    argv[argc++] = "out.o";
    argv[argc++] = "-I./inc1";
    argv[argc++] = "-I";
    argv[argc++] = "./inc2";
    argv[argc++] = "-I";
    argv[argc++] = "-notaninclude";
    argv[argc++] = "--std=gnu11";
    argv[argc++] = "--sysroot";
    argv[argc++] = "/sysroot";
    argv[argc++] = "--ratio=0.75";
    argv[argc++] = "--long-num=123456789";
    argv[argc++] = "--unknown-long";
    argv[argc++] = "-L./lib1";
    argv[argc++] = "-L";
    argv[argc++] = "./lib2";
    argv[argc++] = "-lm";
    argv[argc++] = "-lstdc++";
    argv[argc++] = "main.c";
    exprem[expc++] = argv[argc - 1];
    argv[argc++] = "util.c";
    exprem[expc++] = argv[argc - 1];
    argv[argc++] = "extra.c";
    exprem[expc++] = argv[argc - 1];
    argv[argc++] = "--";
    argv[argc++] = "-Wunknown";
    exprem[expc++] = argv[argc - 1];
    argv[argc++] = "--fake-long";
    exprem[expc++] = argv[argc - 1];
    argv[argc++] = "after1.c";
    exprem[expc++] = argv[argc - 1];
    argv[argc++] = "-";
    exprem[expc++] = argv[argc - 1];

    while (argc < 70) {
      argv[argc++] = "pos.c";
      exprem[expc++] = argv[argc - 1];
    }

    EXPECT_EQ_INT(argc, 70);
    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    argparse_setflags(&ctx, ARG_IGNORE);
    EXPECT_EQ_INT(argparse_parse(&ctx, argc, argv), 0);
    EXPECT_TRUE(cflag);
    EXPECT_TRUE(gflag);
    EXPECT_TRUE(vflag);
    EXPECT_TRUE(gcsec);
    EXPECT_EQ_INT(optlevel, 2);
    EXPECT_EQ_INT(num, 7);
    EXPECT_EQ_INT(longnum, 123456789);
    EXPECT_EQ_DOUBLE(ratio, 0.75);
    EXPECT_NOTNULL(define);
    EXPECT_EQ_STR(define, "NAME=VALUE");
    EXPECT_NOTNULL(out);
    EXPECT_EQ_STR(out, "out.o");
    EXPECT_NOTNULL(std);
    EXPECT_EQ_STR(std, "gnu11");
    EXPECT_NOTNULL(sysroot);
    EXPECT_EQ_STR(sysroot, "/sysroot");

    EXPECT_NOTNULL(inc);
    EXPECT_EQ_UINT(argparse_getlistsz(inc), 3);
    {
      char **items = argparse_getlist(inc);
      EXPECT_EQ_STR(items[0], "./inc1");
      EXPECT_EQ_STR(items[1], "./inc2");
      EXPECT_EQ_STR(items[2], "-notaninclude");
    }

    EXPECT_NOTNULL(libpaths);
    EXPECT_EQ_UINT(argparse_getlistsz(libpaths), 2);
    {
      char **items = argparse_getlist(libpaths);
      EXPECT_EQ_STR(items[0], "./lib1");
      EXPECT_EQ_STR(items[1], "./lib2");
    }

    EXPECT_NOTNULL(libs);
    EXPECT_EQ_UINT(argparse_getlistsz(libs), 2);
    {
      char **items = argparse_getlist(libs);
      EXPECT_EQ_STR(items[0], "m");
      EXPECT_EQ_STR(items[1], "stdc++");
    }

    EXPECT_EQ_UINT(argparse_getremargc(&ctx), (unsigned)expc);
    char **remv = argparse_getremargv(&ctx);
    EXPECT_NOTNULL(remv);
    for (size_t i = 0; i < (size_t)expc; i++)
      EXPECT_EQ_STR(remv[i], exprem[i]);

    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    bool cflag = false;
    bool gflag = false;
    bool vflag = false;
    bool gcsec = false;
    int optlevel = -1;
    int num = -1;
    long longnum = -1;
    double ratio = 0.0;
    char *define = NULL;
    char *out = NULL;
    char *std = NULL;
    char *sysroot = NULL;
    struct argparse_list *inc = NULL;
    struct argparse_list *libpaths = NULL;
    struct argparse_list *libs = NULL;

    struct argparse_opt opts[] = {
        OPT_BOOL('c', "compile-only", "", &cflag),
        OPT_BOOL('g', "debug", "", &gflag),
        OPT_BOOL('v', "verbose", "", &vflag),
        OPT_BOOL('q', "gc-sections", "", &gcsec),
        OPT_INT('O', "opt-level", "", &optlevel, OPT_REQUIRED),
        OPT_INT('n', "num", "", &num, OPT_OPTIONAL),
        OPT_LONG('z', "long-num", "", &longnum, OPT_REQUIRED),
        OPT_DOUBLE('r', "ratio", "", &ratio, OPT_REQUIRED),
        OPT_STR('D', "define", "", &define, OPT_REQUIRED),
        OPT_STR('o', "output", "", &out, OPT_REQUIRED),
        OPT_STR('s', "std", "", &std, OPT_REQUIRED),
        OPT_STR('y', "sysroot", "", &sysroot, OPT_REQUIRED),
        OPT_LIST('I', "include", "", &inc),
        OPT_LIST('L', "libpath", "", &libpaths),
        OPT_LIST('l', "library", "", &libs),
        OPT_END(),
    };

    char *argv[120];
    const char *exprem[120];
    int argc = 0;
    int expc = 0;
    int target = 100;

    argv[argc++] = "-cg";
    argv[argc++] = "Xjunk";
    exprem[expc++] = argv[argc - 1];
    argv[argc++] = "-O3";
    argv[argc++] = "-n";
    argv[argc++] = "8";
    argv[argc++] = "-v";
    argv[argc++] = "--gc-sections";
    argv[argc++] = "-DDEBUG=1";
    argv[argc++] = "-o";
    argv[argc++] = "out2.o";
    argv[argc++] = "-I./inc1";
    argv[argc++] = "-I";
    argv[argc++] = "./inc2";
    argv[argc++] = "--include=./inc3";
    argv[argc++] = "--include";
    argv[argc++] = "./inc4";
    argv[argc++] = "-I";
    argv[argc++] = "-notaninclude2";
    argv[argc++] = "--std=gnu99";
    argv[argc++] = "--sysroot=/opt/sysroot";
    argv[argc++] = "--ratio=1.25";
    argv[argc++] = "--long-num=987654321";
    argv[argc++] = "-L./libA";
    argv[argc++] = "-L";
    argv[argc++] = "./libB";
    argv[argc++] = "-lm";
    argv[argc++] = "-lstdc++";
    argv[argc++] = "--unknown-long";
    argv[argc++] = "--unknown-long2";

    argv[argc++] = "main2.c";
    exprem[expc++] = argv[argc - 1];
    argv[argc++] = "util2.c";
    exprem[expc++] = argv[argc - 1];
    argv[argc++] = "extra2.c";
    exprem[expc++] = argv[argc - 1];

    argv[argc++] = "--";
    argv[argc++] = "-Wunknown2";
    exprem[expc++] = argv[argc - 1];
    argv[argc++] = "--fake-long2";
    exprem[expc++] = argv[argc - 1];
    argv[argc++] = "-n9";
    exprem[expc++] = argv[argc - 1];
    argv[argc++] = "after2.c";
    exprem[expc++] = argv[argc - 1];
    argv[argc++] = "-";
    exprem[expc++] = argv[argc - 1];

    while (argc < target) {
      argv[argc++] = "pos2.c";
      exprem[expc++] = argv[argc - 1];
    }

    EXPECT_EQ_INT(argc, target);
    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    argparse_setflags(&ctx, ARG_IGNORE);
    EXPECT_EQ_INT(argparse_parse(&ctx, argc, argv), 0);

    EXPECT_TRUE(cflag);
    EXPECT_TRUE(gflag);
    EXPECT_TRUE(vflag);
    EXPECT_TRUE(gcsec);
    EXPECT_EQ_INT(optlevel, 3);
    EXPECT_EQ_INT(num, 8);
    EXPECT_EQ_INT(longnum, 987654321);
    EXPECT_EQ_DOUBLE(ratio, 1.25);
    EXPECT_NOTNULL(define);
    EXPECT_EQ_STR(define, "DEBUG=1");
    EXPECT_NOTNULL(out);
    EXPECT_EQ_STR(out, "out2.o");
    EXPECT_NOTNULL(std);
    EXPECT_EQ_STR(std, "gnu99");
    EXPECT_NOTNULL(sysroot);
    EXPECT_EQ_STR(sysroot, "/opt/sysroot");

    EXPECT_NOTNULL(inc);
    EXPECT_EQ_UINT(argparse_getlistsz(inc), 5);
    {
      char **items = argparse_getlist(inc);
      EXPECT_EQ_STR(items[0], "./inc1");
      EXPECT_EQ_STR(items[1], "./inc2");
      EXPECT_EQ_STR(items[2], "./inc3");
      EXPECT_EQ_STR(items[3], "./inc4");
      EXPECT_EQ_STR(items[4], "-notaninclude2");
    }

    EXPECT_NOTNULL(libpaths);
    EXPECT_EQ_UINT(argparse_getlistsz(libpaths), 2);
    {
      char **items = argparse_getlist(libpaths);
      EXPECT_EQ_STR(items[0], "./libA");
      EXPECT_EQ_STR(items[1], "./libB");
    }

    EXPECT_NOTNULL(libs);
    EXPECT_EQ_UINT(argparse_getlistsz(libs), 2);
    {
      char **items = argparse_getlist(libs);
      EXPECT_EQ_STR(items[0], "m");
      EXPECT_EQ_STR(items[1], "stdc++");
    }

    EXPECT_EQ_UINT(argparse_getremargc(&ctx), (unsigned)expc);
    char **remv = argparse_getremargv(&ctx);
    EXPECT_NOTNULL(remv);
    for (size_t i = 0; i < (size_t)expc; i++)
      EXPECT_EQ_STR(remv[i], exprem[i]);

    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }
}

UTEST_CASE(as)
{
  {
    struct argparse ctx;
    bool gflag = false;
    bool xflag = false;
    int pass = -1;
    long longoff = -1;
    double scale = 0.0;
    char *out = NULL;
    char *target = NULL;
    struct argparse_list *inc = NULL;
    struct argparse_list *defines = NULL;
    struct argparse_list *sections = NULL;

    struct argparse_opt opts[] = {
        OPT_BOOL('g', "debug", "", &gflag),
        OPT_BOOL('x', "xray", "", &xflag),
        OPT_INT('p', "pass", "", &pass, OPT_REQUIRED),
        OPT_LONG('o', "offset", "", &longoff, OPT_REQUIRED),
        OPT_DOUBLE('s', "scale", "", &scale, OPT_REQUIRED),
        OPT_STR('O', "output", "", &out, OPT_REQUIRED),
        OPT_STR('t', "target", "", &target, OPT_REQUIRED),
        OPT_LIST('I', "include", "", &inc),
        OPT_LIST('D', "define", "", &defines),
        OPT_LIST('e', "section", "", &sections),
        OPT_END(),
    };

    char *argv[100];
    const char *exprem[100];
    int argc = 0;
    int expc = 0;

    argv[argc++] = "-g";
    argv[argc++] = "-x";
    argv[argc++] = "-p1";
    argv[argc++] = "-O";
    argv[argc++] = "asout.o";
    argv[argc++] = "--target=arm-linux-gnueabihf";
    argv[argc++] = "--offset=4096";
    argv[argc++] = "--scale=0.5";
    argv[argc++] = "-I./inc1";
    argv[argc++] = "-I";
    argv[argc++] = "./inc2";
    argv[argc++] = "-I";
    argv[argc++] = "-notaninclude";
    argv[argc++] = "-DFOO=1";
    argv[argc++] = "-DDEBUG=1";
    argv[argc++] = "--section=.text";
    argv[argc++] = "--section";
    argv[argc++] = ".data";
    argv[argc++] = "--unknown-as";

    argv[argc++] = "code1.s";
    exprem[expc++] = argv[argc - 1];
    argv[argc++] = "code2.s";
    exprem[expc++] = argv[argc - 1];

    argv[argc++] = "--";
    argv[argc++] = "-h";
    exprem[expc++] = argv[argc - 1];
    argv[argc++] = "--fake-as";
    exprem[expc++] = argv[argc - 1];
    argv[argc++] = "after1.s";
    exprem[expc++] = argv[argc - 1];
    argv[argc++] = "-";
    exprem[expc++] = argv[argc - 1];

    while (argc < 70) {
      argv[argc++] = "pos.s";
      exprem[expc++] = argv[argc - 1];
    }

    EXPECT_EQ_INT(argc, 70);
    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    argparse_setflags(&ctx, ARG_IGNORE);
    EXPECT_EQ_INT(argparse_parse(&ctx, argc, argv), 0);
    EXPECT_TRUE(gflag);
    EXPECT_TRUE(xflag);
    EXPECT_EQ_INT(pass, 1);
    EXPECT_EQ_INT(longoff, 4096);
    EXPECT_EQ_DOUBLE(scale, 0.5);
    EXPECT_NOTNULL(out);
    EXPECT_EQ_STR(out, "asout.o");
    EXPECT_NOTNULL(target);
    EXPECT_EQ_STR(target, "arm-linux-gnueabihf");

    EXPECT_NOTNULL(inc);
    EXPECT_EQ_UINT(argparse_getlistsz(inc), 3);
    {
      char **items = argparse_getlist(inc);
      EXPECT_EQ_STR(items[0], "./inc1");
      EXPECT_EQ_STR(items[1], "./inc2");
      EXPECT_EQ_STR(items[2], "-notaninclude");
    }

    EXPECT_NOTNULL(defines);
    EXPECT_EQ_UINT(argparse_getlistsz(defines), 2);
    {
      char **items = argparse_getlist(defines);
      EXPECT_EQ_STR(items[0], "FOO=1");
      EXPECT_EQ_STR(items[1], "DEBUG=1");
    }

    EXPECT_NOTNULL(sections);
    EXPECT_EQ_UINT(argparse_getlistsz(sections), 2);
    {
      char **items = argparse_getlist(sections);
      EXPECT_EQ_STR(items[0], ".text");
      EXPECT_EQ_STR(items[1], ".data");
    }

    EXPECT_EQ_UINT(argparse_getremargc(&ctx), (unsigned)expc);
    char **remv = argparse_getremargv(&ctx);
    EXPECT_NOTNULL(remv);
    for (size_t i = 0; i < (size_t)expc; i++)
      EXPECT_EQ_STR(remv[i], exprem[i]);

    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    bool gflag = false;
    bool xflag = false;
    int pass = -1;
    long longoff = -1;
    double scale = 0.0;
    char *out = NULL;
    char *target = NULL;
    struct argparse_list *inc = NULL;
    struct argparse_list *defines = NULL;
    struct argparse_list *sections = NULL;

    struct argparse_opt opts[] = {
        OPT_BOOL('g', "debug", "", &gflag),
        OPT_BOOL('x', "xray", "", &xflag),
        OPT_INT('p', "pass", "", &pass, OPT_REQUIRED),
        OPT_LONG('o', "offset", "", &longoff, OPT_REQUIRED),
        OPT_DOUBLE('s', "scale", "", &scale, OPT_REQUIRED),
        OPT_STR('O', "output", "", &out, OPT_REQUIRED),
        OPT_STR('t', "target", "", &target, OPT_REQUIRED),
        OPT_LIST('I', "include", "", &inc),
        OPT_LIST('D', "define", "", &defines),
        OPT_LIST('e', "section", "", &sections),
        OPT_END(),
    };

    char *argv[160];
    const char *exprem[160];
    int argc = 0;
    int expc = 0;
    int argc_target = 100;

    argv[argc++] = "-gx";
    argv[argc++] = "-p";
    argv[argc++] = "2";
    argv[argc++] = "-O";
    argv[argc++] = "asout2.o";
    argv[argc++] = "--target";
    argv[argc++] = "x86_64-linux-gnu";
    argv[argc++] = "--offset=8192";
    argv[argc++] = "--scale=1.25";
    argv[argc++] = "-I./inc1";
    argv[argc++] = "-I";
    argv[argc++] = "./inc2";
    argv[argc++] = "--include=./inc3";
    argv[argc++] = "-I";
    argv[argc++] = "-notaninclude2";
    argv[argc++] = "-DFLAG=ON";
    argv[argc++] = "-DLEVEL=3";
    argv[argc++] = "-DNAME=VALUE";
    argv[argc++] = "--section=.rodata";
    argv[argc++] = "--section";
    argv[argc++] = ".bss";
    argv[argc++] = "--unknown-as";
    argv[argc++] = "--unknown-as2";

    argv[argc++] = "code3.s";
    exprem[expc++] = argv[argc - 1];
    argv[argc++] = "code4.s";
    exprem[expc++] = argv[argc - 1];
    argv[argc++] = "code5.s";
    exprem[expc++] = argv[argc - 1];

    argv[argc++] = "--";
    argv[argc++] = "-p";
    exprem[expc++] = argv[argc - 1];
    argv[argc++] = "9";
    exprem[expc++] = argv[argc - 1];
    argv[argc++] = "--fake-as2";
    exprem[expc++] = argv[argc - 1];
    argv[argc++] = "after2.s";
    exprem[expc++] = argv[argc - 1];
    argv[argc++] = "-";
    exprem[expc++] = argv[argc - 1];

    while (argc < argc_target) {
      argv[argc++] = "pos2.s";
      exprem[expc++] = argv[argc - 1];
    }

    EXPECT_EQ_INT(argc, argc_target);
    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    argparse_setflags(&ctx, ARG_IGNORE);
    EXPECT_EQ_INT(argparse_parse(&ctx, argc, argv), 0);

    EXPECT_TRUE(gflag);
    EXPECT_TRUE(xflag);
    EXPECT_EQ_INT(pass, 2);
    EXPECT_EQ_INT(longoff, 8192);
    EXPECT_EQ_DOUBLE(scale, 1.25);
    EXPECT_NOTNULL(out);
    EXPECT_EQ_STR(out, "asout2.o");
    EXPECT_NOTNULL(target);
    EXPECT_EQ_STR(target, "x86_64-linux-gnu");

    EXPECT_NOTNULL(inc);
    EXPECT_EQ_UINT(argparse_getlistsz(inc), 4);
    {
      char **items = argparse_getlist(inc);
      EXPECT_EQ_STR(items[0], "./inc1");
      EXPECT_EQ_STR(items[1], "./inc2");
      EXPECT_EQ_STR(items[2], "./inc3");
      EXPECT_EQ_STR(items[3], "-notaninclude2");
    }

    EXPECT_NOTNULL(defines);
    EXPECT_EQ_UINT(argparse_getlistsz(defines), 3);
    {
      char **items = argparse_getlist(defines);
      EXPECT_EQ_STR(items[0], "FLAG=ON");
      EXPECT_EQ_STR(items[1], "LEVEL=3");
      EXPECT_EQ_STR(items[2], "NAME=VALUE");
    }

    EXPECT_NOTNULL(sections);
    EXPECT_EQ_UINT(argparse_getlistsz(sections), 2);
    {
      char **items = argparse_getlist(sections);
      EXPECT_EQ_STR(items[0], ".rodata");
      EXPECT_EQ_STR(items[1], ".bss");
    }

    EXPECT_EQ_UINT(argparse_getremargc(&ctx), (unsigned)expc);
    char **remv = argparse_getremargv(&ctx);
    EXPECT_NOTNULL(remv);
    for (size_t i = 0; i < (size_t)expc; i++)
      EXPECT_EQ_STR(remv[i], exprem[i]);

    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }
}

UTEST_CASE(ld)
{
  {
    struct argparse ctx;
    bool gcsec = false;
    bool verbose = false;
    char *out = NULL;
    char *script = NULL;
    long entry = -1;
    double ratio = 0.0;
    struct argparse_list *libpaths = NULL;
    struct argparse_list *libs = NULL;
    char *mapfile = NULL;

    struct argparse_opt opts[] = {
        OPT_BOOL('g', "gc-sections", "", &gcsec),
        OPT_BOOL('v', "verbose", "", &verbose),
        OPT_STR('o', "output", "", &out, OPT_REQUIRED),
        OPT_STR('T', "script", "", &script, OPT_REQUIRED),
        OPT_LONG('e', "entry", "", &entry, OPT_REQUIRED),
        OPT_DOUBLE('r', "ratio", "", &ratio, OPT_REQUIRED),
        OPT_LIST('L', "libpath", "", &libpaths),
        OPT_LIST('l', "library", "", &libs),
        OPT_STR('m', "mapfile", "", &mapfile, OPT_REQUIRED),
        OPT_END(),
    };

    char *argv[100];
    const char *exprem[100];
    int argc = 0;
    int expc = 0;

    argv[argc++] = "-v";
    argv[argc++] = "--gc-sections";
    argv[argc++] = "-o";
    argv[argc++] = "a.out";
    argv[argc++] = "-T";
    argv[argc++] = "link.ld";
    argv[argc++] = "--entry=0x401000";
    argv[argc++] = "--ratio=0.5";
    argv[argc++] = "--mapfile=out.map";
    argv[argc++] = "-L./libA";
    argv[argc++] = "-L";
    argv[argc++] = "./libB";
    argv[argc++] = "-lm";
    argv[argc++] = "-lstdc++";
    argv[argc++] = "--unknown-ld";

    argv[argc++] = "crt1.o";
    exprem[expc++] = argv[argc - 1];
    argv[argc++] = "main.o";
    exprem[expc++] = argv[argc - 1];
    argv[argc++] = "util.o";
    exprem[expc++] = argv[argc - 1];

    argv[argc++] = "--";
    argv[argc++] = "-Wl,unknown";
    exprem[expc++] = argv[argc - 1];
    argv[argc++] = "--fake-ld";
    exprem[expc++] = argv[argc - 1];
    argv[argc++] = "after.ld";
    exprem[expc++] = argv[argc - 1];
    argv[argc++] = "-";
    exprem[expc++] = argv[argc - 1];

    while (argc < 70) {
      argv[argc++] = "pos.o";
      exprem[expc++] = argv[argc - 1];
    }

    EXPECT_EQ_INT(argc, 70);
    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    argparse_setflags(&ctx, ARG_IGNORE);
    EXPECT_EQ_INT(argparse_parse(&ctx, argc, argv), 0);
    EXPECT_TRUE(gcsec);
    EXPECT_TRUE(verbose);
    EXPECT_NOTNULL(out);
    EXPECT_EQ_STR(out, "a.out");
    EXPECT_NOTNULL(script);
    EXPECT_EQ_STR(script, "link.ld");
    EXPECT_EQ_INT(entry, (long)0x401000);
    EXPECT_EQ_DOUBLE(ratio, 0.5);
    EXPECT_NOTNULL(mapfile);
    EXPECT_EQ_STR(mapfile, "out.map");

    EXPECT_NOTNULL(libpaths);
    EXPECT_EQ_UINT(argparse_getlistsz(libpaths), 2);
    {
      char **items = argparse_getlist(libpaths);
      EXPECT_EQ_STR(items[0], "./libA");
      EXPECT_EQ_STR(items[1], "./libB");
    }

    EXPECT_NOTNULL(libs);
    EXPECT_EQ_UINT(argparse_getlistsz(libs), 2);
    {
      char **items = argparse_getlist(libs);
      EXPECT_EQ_STR(items[0], "m");
      EXPECT_EQ_STR(items[1], "stdc++");
    }

    EXPECT_EQ_UINT(argparse_getremargc(&ctx), (unsigned)expc);
    char **remv = argparse_getremargv(&ctx);
    EXPECT_NOTNULL(remv);
    for (size_t i = 0; i < (size_t)expc; i++)
      EXPECT_EQ_STR(remv[i], exprem[i]);

    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    bool gcsec = false;
    bool verbose = false;
    char *out = NULL;
    char *script = NULL;
    long entry = -1;
    double ratio = 0.0;
    struct argparse_list *libpaths = NULL;
    struct argparse_list *libs = NULL;
    char *mapfile = NULL;

    struct argparse_opt opts[] = {
        OPT_BOOL('g', "gc-sections", "", &gcsec),
        OPT_BOOL('v', "verbose", "", &verbose),
        OPT_STR('o', "output", "", &out, OPT_REQUIRED),
        OPT_STR('T', "script", "", &script, OPT_REQUIRED),
        OPT_LONG('e', "entry", "", &entry, OPT_REQUIRED),
        OPT_DOUBLE('r', "ratio", "", &ratio, OPT_REQUIRED),
        OPT_LIST('L', "libpath", "", &libpaths),
        OPT_LIST('l', "library", "", &libs),
        OPT_STR('m', "mapfile", "", &mapfile, OPT_REQUIRED),
        OPT_END(),
    };

    char *argv[200];
    const char *exprem[200];
    int argc = 0;
    int expc = 0;
    int target = 100;

    argv[argc++] = "-vg";
    argv[argc++] = "-o";
    argv[argc++] = "link2";
    argv[argc++] = "--gc-sections";
    argv[argc++] = "-Tlink.ld";
    argv[argc++] = "--entry";
    argv[argc++] = "0x500000";
    argv[argc++] = "--ratio=1.25";
    argv[argc++] = "--mapfile";
    argv[argc++] = "out2.map";
    argv[argc++] = "-L./lib1";
    argv[argc++] = "-L";
    argv[argc++] = "./lib2";
    argv[argc++] = "-L";
    argv[argc++] = "-notalibpath";
    argv[argc++] = "-lm";
    argv[argc++] = "-lutil";
    argv[argc++] = "-lstdc++";
    argv[argc++] = "--unknown-ld";

    argv[argc++] = "crt2.o";
    exprem[expc++] = argv[argc - 1];
    argv[argc++] = "main2.o";
    exprem[expc++] = argv[argc - 1];

    argv[argc++] = "--";
    argv[argc++] = "-m";
    exprem[expc++] = argv[argc - 1];
    argv[argc++] = "999";
    exprem[expc++] = argv[argc - 1];
    argv[argc++] = "--fake-ld2";
    exprem[expc++] = argv[argc - 1];
    argv[argc++] = "-";
    exprem[expc++] = argv[argc - 1];

    while (argc < target) {
      argv[argc++] = "pos2.o";
      exprem[expc++] = argv[argc - 1];
    }

    EXPECT_EQ_INT(argc, target);
    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    argparse_setflags(&ctx, ARG_IGNORE);
    EXPECT_EQ_INT(argparse_parse(&ctx, argc, argv), 0);

    EXPECT_TRUE(gcsec);
    EXPECT_TRUE(verbose);
    EXPECT_NOTNULL(out);
    EXPECT_EQ_STR(out, "link2");
    EXPECT_NOTNULL(script);
    EXPECT_EQ_STR(script, "link.ld");
    EXPECT_EQ_INT(entry, (long)0x500000);
    EXPECT_EQ_DOUBLE(ratio, 1.25);
    EXPECT_NOTNULL(mapfile);
    EXPECT_EQ_STR(mapfile, "out2.map");

    EXPECT_NOTNULL(libpaths);
    EXPECT_EQ_UINT(argparse_getlistsz(libpaths), 3);
    {
      char **items = argparse_getlist(libpaths);
      EXPECT_EQ_STR(items[0], "./lib1");
      EXPECT_EQ_STR(items[1], "./lib2");
      EXPECT_EQ_STR(items[2], "-notalibpath");
    }

    EXPECT_NOTNULL(libs);
    EXPECT_EQ_UINT(argparse_getlistsz(libs), 3);
    {
      char **items = argparse_getlist(libs);
      EXPECT_EQ_STR(items[0], "m");
      EXPECT_EQ_STR(items[1], "util");
      EXPECT_EQ_STR(items[2], "stdc++");
    }

    EXPECT_EQ_UINT(argparse_getremargc(&ctx), (unsigned)expc);
    char **remv = argparse_getremargv(&ctx);
    EXPECT_NOTNULL(remv);
    for (size_t i = 0; i < (size_t)expc; i++)
      EXPECT_EQ_STR(remv[i], exprem[i]);

    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }
}

UTEST_CASE(readelf)
{
  {
    struct argparse ctx;
    bool hflag = false;
    bool sflag = false;
    bool rflag = false;
    bool wflag = false;
    int part = -1;
    long offset = -1;
    double scale = 0.0;
    char *out = NULL;
    struct argparse_list *sections = NULL;

    struct argparse_opt opts[] = {
        OPT_BOOL('h', "header", "", &hflag),
        OPT_BOOL('S', "sections", "", &sflag),
        OPT_BOOL('r', "relocations", "", &rflag),
        OPT_BOOL('W', "wide", "", &wflag),
        OPT_INT('p', "part", "", &part, OPT_REQUIRED),
        OPT_LONG('o', "offset", "", &offset, OPT_REQUIRED),
        OPT_DOUBLE('s', "scale", "", &scale, OPT_REQUIRED),
        OPT_STR('O', "output", "", &out, OPT_REQUIRED),
        OPT_LIST('e', "section", "", &sections),
        OPT_END(),
    };

    char *argv[100];
    const char *exprem[100];
    int argc = 0;
    int expc = 0;

    argv[argc++] = "-hSrW";
    argv[argc++] = "-p";
    argv[argc++] = "2";
    argv[argc++] = "--offset=64";
    argv[argc++] = "--scale=2.0";
    argv[argc++] = "-O";
    argv[argc++] = "readelf.out";
    argv[argc++] = "--section=.text";
    argv[argc++] = "--section";
    argv[argc++] = ".data";
    argv[argc++] = "--unknown-readelf";

    argv[argc++] = "a.out";
    exprem[expc++] = argv[argc - 1];

    argv[argc++] = "--";
    argv[argc++] = "-p";
    exprem[expc++] = argv[argc - 1];
    argv[argc++] = "9";
    exprem[expc++] = argv[argc - 1];
    argv[argc++] = "--fake-readelf";
    exprem[expc++] = argv[argc - 1];
    argv[argc++] = "-";
    exprem[expc++] = argv[argc - 1];

    while (argc < 70) {
      argv[argc++] = "pos.elf";
      exprem[expc++] = argv[argc - 1];
    }

    EXPECT_EQ_INT(argc, 70);
    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    argparse_setflags(&ctx, ARG_IGNORE);
    EXPECT_EQ_INT(argparse_parse(&ctx, argc, argv), 0);
    EXPECT_TRUE(hflag);
    EXPECT_TRUE(sflag);
    EXPECT_TRUE(rflag);
    EXPECT_TRUE(wflag);
    EXPECT_EQ_INT(part, 2);
    EXPECT_EQ_INT(offset, 64);
    EXPECT_EQ_DOUBLE(scale, 2.0);
    EXPECT_NOTNULL(out);
    EXPECT_EQ_STR(out, "readelf.out");

    EXPECT_NOTNULL(sections);
    EXPECT_EQ_UINT(argparse_getlistsz(sections), 2);
    {
      char **items = argparse_getlist(sections);
      EXPECT_EQ_STR(items[0], ".text");
      EXPECT_EQ_STR(items[1], ".data");
    }

    EXPECT_EQ_UINT(argparse_getremargc(&ctx), (unsigned)expc);
    char **remv = argparse_getremargv(&ctx);
    EXPECT_NOTNULL(remv);
    for (size_t i = 0; i < (size_t)expc; i++)
      EXPECT_EQ_STR(remv[i], exprem[i]);

    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }

  {
    struct argparse ctx;
    bool hflag = false;
    bool sflag = false;
    bool rflag = false;
    bool wflag = false;
    int part = -1;
    long offset = -1;
    double scale = 0.0;
    char *out = NULL;
    struct argparse_list *sections = NULL;

    struct argparse_opt opts[] = {
        OPT_BOOL('h', "header", "", &hflag),
        OPT_BOOL('S', "sections", "", &sflag),
        OPT_BOOL('r', "relocations", "", &rflag),
        OPT_BOOL('W', "wide", "", &wflag),
        OPT_INT('p', "part", "", &part, OPT_REQUIRED),
        OPT_LONG('o', "offset", "", &offset, OPT_REQUIRED),
        OPT_DOUBLE('s', "scale", "", &scale, OPT_REQUIRED),
        OPT_STR('O', "output", "", &out, OPT_REQUIRED),
        OPT_LIST('e', "section", "", &sections),
        OPT_END(),
    };

    char *argv[200];
    const char *exprem[200];
    int argc = 0;
    int expc = 0;
    int target = 100;

    argv[argc++] = "-hSrwW";
    argv[argc++] = "-p";
    argv[argc++] = "1";
    argv[argc++] = "--offset";
    argv[argc++] = "128";
    argv[argc++] = "--scale=1.25";
    argv[argc++] = "-O";
    argv[argc++] = "readelf.out2";
    argv[argc++] = "--section=.init";
    argv[argc++] = "--section=.plt";
    argv[argc++] = "--section";
    argv[argc++] = ".fini";
    argv[argc++] = "--unknown-readelf2";

    argv[argc++] = "prog.elf";
    exprem[expc++] = argv[argc - 1];

    argv[argc++] = "--";
    argv[argc++] = "--fake-readelf2";
    exprem[expc++] = argv[argc - 1];
    argv[argc++] = "-W";
    exprem[expc++] = argv[argc - 1];
    argv[argc++] = "-p";
    exprem[expc++] = argv[argc - 1];
    argv[argc++] = "4";
    exprem[expc++] = argv[argc - 1];
    argv[argc++] = "-";
    exprem[expc++] = argv[argc - 1];

    while (argc < target) {
      argv[argc++] = "pos2.elf";
      exprem[expc++] = argv[argc - 1];
    }

    EXPECT_EQ_INT(argc, target);
    EXPECT_EQ_INT(argparse_init(&ctx, opts, NULL), 0);
    argparse_setflags(&ctx, ARG_IGNORE);
    EXPECT_EQ_INT(argparse_parse(&ctx, argc, argv), 0);
    EXPECT_TRUE(hflag);
    EXPECT_TRUE(sflag);
    EXPECT_TRUE(rflag);
    EXPECT_TRUE(wflag);
    EXPECT_EQ_INT(part, 1);
    EXPECT_EQ_INT(offset, 128);
    EXPECT_EQ_DOUBLE(scale, 1.25);
    EXPECT_NOTNULL(out);
    EXPECT_EQ_STR(out, "readelf.out2");

    EXPECT_NOTNULL(sections);
    EXPECT_EQ_UINT(argparse_getlistsz(sections), 3);
    {
      char **items = argparse_getlist(sections);
      EXPECT_EQ_STR(items[0], ".init");
      EXPECT_EQ_STR(items[1], ".plt");
      EXPECT_EQ_STR(items[2], ".fini");
    }

    EXPECT_EQ_UINT(argparse_getremargc(&ctx), (unsigned)expc);
    char **remv = argparse_getremargv(&ctx);
    EXPECT_NOTNULL(remv);
    for (size_t i = 0; i < (size_t)expc; i++)
      EXPECT_EQ_STR(remv[i], exprem[i]);

    EXPECT_EQ_STR(argparse_strerror(&ctx), "");
    argparse_fini(&ctx);
  }
}