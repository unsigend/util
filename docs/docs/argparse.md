# argparse

## Overview

`argparse` is a lightweight command line argument parser compatible with GNU/POSIX option style. The single header is `argparse.h`.

Options are declared as a null-terminated array of `argparse_opt` structs, built with the `OPT_*` helper macros. The parser writes values directly into caller-provided destination pointers, so no post-parse extraction step is needed for most types.

## Conventions

Short options take the form `-f`, `-f value`, or `-f<value>`. Multiple boolean short options may be combined as `-abc`. Long options take the form `--flag`, `--flag value`, or `--flag=value`. The sentinel `--` stops option parsing, all following tokens are collected as positional arguments regardless of their prefix.

For `LIST` type, the destination pointer must be initialized to `NULL` before parsing. The parser allocates the list on first use.

Positional arguments: anything not consumed as an option or its value are collected into the remainder list and accessible via `argparse_getremargc` and `argparse_getremargv`.

When a parse error occurs and `ARG_IGNORE` is not set, the error message is written to `ctx->errstr` and the function returns -1.

## Flags

### Option argument flags

Passed as the `f` argument to value-typed `OPT_*` macros, controlling how the parser treats the option's argument.

| Flag           | Meaning                                                       |
| -------------- | ------------------------------------------------------------- |
| `OPT_REQUIRED` | Option argument is required, parse fails if absent or invalid |
| `OPT_OPTIONAL` | Option argument is optional, skipped if absent or invalid     |
| `OPT_NONE`     | Option takes no argument, used for `OPT_BOOL`                 |

### Context flags

Set on the `argparse` context via `argparse_setflags` / `argparse_clrflags`.

| Flag         | Meaning                                                     |
| ------------ | ----------------------------------------------------------- |
| `ARG_IGNORE` | Silently skip unknown options instead of returning an error |

## Macros

### Option declaration

Options are declared using the helper macros below and terminated with `OPT_END()`.

| Macro                       | Description                                                          |
| --------------------------- | -------------------------------------------------------------------- |
| `OPT_BOOL(s, l, h, d)`      | Boolean flag, set to `true` when present                             |
| `OPT_INT(s, l, h, d, f)`    | Signed integer option                                                |
| `OPT_STR(s, l, h, d, f)`    | String option, dest receives a pointer into `argv`                   |
| `OPT_LONG(s, l, h, d, f)`   | Long integer option                                                  |
| `OPT_DOUBLE(s, l, h, d, f)` | Double option                                                        |
| `OPT_LIST(s, l, h, d)`      | Repeatable string option, values accumulated into a list             |
| `OPT_GROUP(h)`              | Visual grouping header for help output, no-op during parsing         |
| `OPT_GROUP_END()`           | Closes a group                                                       |
| `OPT_HELP()`                | Adds a built-in `-h`/`--help` option that invokes `argparse_cb_help` |
| `OPT_END()`                 | Required sentinel, marks end of option array                         |

Parameters: `s` = short name char, `l` = long name string, `h` = help string, `d` = destination pointer, `f` = argument flag.

### Context macros

| Macro                          | Description                                         |
| ------------------------------ | --------------------------------------------------- |
| `argparse_setflags(ctx, flag)` | Sets a flag on the context                          |
| `argparse_clrflags(ctx, flag)` | Clears a flag on the context                        |
| `argparse_strerror(ctx)`       | Returns the last error string, or NULL if none      |
| `argparse_getremargc(ctx)`     | Returns the count of remaining positional arguments |
| `argparse_getremargv(ctx)`     | Returns the `char **` array of positional arguments |
| `argparse_getlist(list)`       | Returns the `char **` items of an `argparse_list`   |
| `argparse_getlistsz(list)`     | Returns the item count of an `argparse_list`        |

## Structs

### `argparse_opt`

Describes a single option. Populate via the `OPT_*` macros rather than directly.

- `sname` — short option character, `'\0'` if none
- `lname` — long option string, NULL if none
- `type` — one of the `_OPT_*` type constants
- `dest` — pointer to the variable receiving the parsed value
- `help` — help string shown in usage output
- `cb` — optional callback invoked after the option is parsed
- `flags` — `OPT_REQUIRED`, `OPT_OPTIONAL`, or `OPT_NONE`

### `argparse_desc`

Optional program metadata used by help output.

- `prog` — program name
- `desc` — short description shown before option list
- `usage` — usage line
- `epilog` — text shown after option list

### `argparse_list`

Holds values collected by a `LIST` option. Access via `argparse_getlist` and `argparse_getlistsz`.

## Functions

### `argparse_init`

```c
int argparse_init(struct argparse *ctx, struct argparse_opt *opts,
                  struct argparse_desc *desc);
```

Initializes the context with an option array and optional description. Must be called before `argparse_parse`. Returns 0 on success, -1 on error.

**Parameters**

- `ctx` — pointer to an uninitialized context struct
- `opts` — null-terminated array of option descriptors, must end with `OPT_END()`
- `desc` — optional program description, may be NULL

### `argparse_parse`

```c
int argparse_parse(struct argparse *ctx, int argc, char **argv);
```

Parses the argument array. The program name should not be included; pass `argc - 1` and `argv + 1` from `main`. Returns 0 on success, -1 on error. On error the message is available via `argparse_strerror`.

**Parameters**

- `ctx` — an initialized context
- `argc` — number of arguments
- `argv` — argument strings

### `argparse_fini`

```c
void argparse_fini(struct argparse *ctx);
```

Releases all resources held by the context. Must be called when the context is no longer needed.

**Parameters**

- `ctx` — an initialized context

### `argparse_cb_help`

```c
void argparse_cb_help(struct argparse *, struct argparse_opt *);
```

Built-in callback that prints formatted help to stdout and exits. Used automatically by `OPT_HELP()`.

## Example

```c
#include <argparse.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    int verbose = 0;
    int jobs = 1;
    const char *output = NULL;
    struct argparse_list *includes = NULL; /* must be NULL for LIST */

    struct argparse_opt opts[] = {
        OPT_HELP(),
        OPT_BOOL('v', "verbose", "enable verbose output", &verbose),
        OPT_INT('j', "jobs", "number of jobs", &jobs, OPT_OPTIONAL),
        OPT_STR('o', "output", "output file", &output, OPT_REQUIRED),
        OPT_LIST('I', "include", "include path", &includes),
        OPT_END(),
    };

    struct argparse_desc desc = {
        .prog  = "build",
        .usage = "build [options] <files>",
    };

    struct argparse ctx;
    argparse_init(&ctx, opts, &desc);

    if (argparse_parse(&ctx, argc - 1, argv + 1) == -1) {
        fprintf(stderr, "error: %s\n", argparse_strerror(&ctx));
        argparse_fini(&ctx);
        return 1;
    }

    /* positional arguments */
    char **files = argparse_getremargv(&ctx);
    size_t nfiles = argparse_getremargc(&ctx);

    /* list option values */
    if (includes) {
        char **paths = argparse_getlist(includes);
        size_t n = argparse_getlistsz(includes);
        for (size_t i = 0; i < n; i++)
            printf("include: %s\n", paths[i]);
    }

    printf("output=%s jobs=%d verbose=%d files=%zu\n",
           output, jobs, verbose, nfiles);

    argparse_fini(&ctx);
    return 0;
}
```

Invoking as `build -v -j4 -o out -I./inc -I./src file1.c file2.c` would produce:

```
include: ./inc
include: ./src
output=out jobs=4 verbose=1 files=2
```
