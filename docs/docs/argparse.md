## Argparse

Lightweight **table-driven** CLI parser for C. Follows **POSIX Utility Syntax Guidelines**: short and long options, optional **`=`** values, **`--`** to end option scanning, and a **remainder** for operands.

Quick facts:

- **Header**: `#include <argparse.h>`
- **`argv`**: pass **only** user arguments, omit `argv[0]`
- **Model**: one option table, one **`argparse_parse`** per parse
- **API**: use documented **macros** and **functions**, keep the context opaque aside from **`init`**, **`parse`**, **`fini`**, and accessors

---

## 1. Conventions

- **Option table**: **`struct argparse_opt[]`** built with **`OPT_*`** (or **`OPT_DECL`**), terminated with **`OPT_END()`**.
- **Short names**: one dash and one letter, defined in each macro. **`-abc`** clustering is allowed **only** for **`OPT_BOOL`**.
- **Long names**: two dashes and a name, value as **`--opt=value`**, or **`--opt`** with the value in the next argv element.
- **Attached values**: a value may share the argv element with the flag or sit in the next one, depending on type and flags (e.g. **`-I./dir`** vs **`-I` `./dir`**).
- **Operands**: any argv token that is not an option or its value, **plus** every token after **`--`**. A lone **`-`** counts as an operand. Exposed as the **remainder** via **`argparse_getremargc`** / **`argparse_getremargv`**.
- **`OPT_LIST`**: each occurrence supplies **one** value, order matches the command line.
- **Parsing**: left to right over the **`argv`** you pass to **`argparse_parse`** (no program name in that slice).
- **Errors**: **`argparse_parse`** returns **`-1`**, use **`argparse_strerror`**, and set **`ARG_IGNORE`** via **`argparse_setflags`** to skip unknown options instead of failing.

---

## 2. Tokens and argv shapes

**Option vs operand** — An **option** starts with **`-`** and is parsed as short or long. Everything else in the scan (and all tokens after **`--`**) is an **operand** once options/values are resolved.

**Short** — **`-x`** (boolean **`x`** if registered as bool). **`-xyz`**: booleans only, same as **`-x -y -z`**. **`-xvalue`**: **`x`** with value in the same token. **`-x`** then **`value`**: next token is the value.

**Long** — **`--flag`** (boolean). **`--opt`** then **`value`**: separate token. **`--opt=value`**: value after **`=`**.

**`--`** — Ends option scanning, following tokens are operands even if they start with **`-`**.

**Scan order** — Options and values are consumed from **`argv`** in order, whatever is left, plus everything after **`--`**, forms the **remainder** list.

---

## 3. Functions

Signatures match **`argparse.h`**.

```c
int  argparse_init(struct argparse *ctx, struct argparse_opt *opts,
                   struct argparse_desc *desc);
int  argparse_parse(struct argparse *ctx, int argc, char **argv);
void argparse_fini(struct argparse *ctx);
```

- **`argparse_init`**: wire **`ctx`**, **`opts`** (must end with **`OPT_END()`**), optional **`desc`**. Returns **`0`** or **`-1`**.
- **`argparse_parse`**: parse **`argc` / `argv`** without the program name. **`0`** on success, **`-1`** on error.
- **`argparse_fini`**: free resources held by that **`ctx`**.

Help callback (library implementation, declared in the header, use **`OPT_HELP()`**):

```c
void argparse_cb_help(struct argparse *ctx, struct argparse_opt *opt);
```

---

## 4. Types

**Callback** — Runs after the value is bound, unless parsing stops on error.

```c
typedef void (*argparse_cb)(struct argparse *ctx, struct argparse_opt *opt);
```

**Program description** — Pass **`NULL`** for **`desc`** at **`argparse_init`** if unused.

```c
struct argparse_desc {
  const char *prog;
  const char *desc;
  const char *usage;
  const char *epilog;
};
```

**Option rows** — Normally built only with **`OPT_*`** / **`OPT_DECL`**. Each row has short name, long name, type, destination, help, flags **`OPT_NONE` / `OPT_REQUIRED` / `OPT_OPTIONAL`**, and optional callback.

**Lists** — After parse, use **`argparse_getlist`** and **`argparse_getlistsz`**. Set the `struct argparse_list *` for **`OPT_LIST`** to **`NULL`** before **`argparse_parse`**.

---

## 5. Macros

**Context flags**

- **`ARG_IGNORE`**: when set via **`argparse_setflags`**, unknown options are skipped instead of an error.
- **`argparse_setflags`**: OR bits into the context flags.
- **`argparse_clrflags`**: clear flag bits.

**Argument mode**

- **`OPT_NONE`**: no separate argument (booleans). Lists still take a value internally.
- **`OPT_REQUIRED`**: a value is required, string rules depend on type.
- **`OPT_OPTIONAL`**: value may be omitted or come from the next token, per type rules.

**Option builders** — Letters **`s`** (short or **`'\0'`**), **`l`** (long or **`NULL`**), **`h`** (help), **`d`** (destination), **`f`** (flags) where the macro shows **`f`**.

- **`OPT_BOOL`**: destination **`bool *`**, no **`f`**.
- **`OPT_INT`**: **`int *`**, **`f`** supported.
- **`OPT_LONG`**: **`long *`**, **`f`** supported.
- **`OPT_DOUBLE`**: **`double *`**, **`f`** supported.
- **`OPT_STR`**: destination `char *`, **`f`** supported.
- **`OPT_LIST`**: destination `struct argparse_list *`, no **`f`**.

**Special**

- **`OPT_GROUP`**: help section label only.
- **`OPT_END()`**: required table terminator.
- **`OPT_HELP()`**: **`-h` / `--help`**, uses **`argparse_cb_help`**.
- **`OPT_DECL`**: full control (**`_OPT_*`** type, callback or **`NULL`**).

---

## 6. After parse

**Accessors** (valid after **`argparse_parse`**, **`argparse_strerror`** also after failure)

- **`argparse_getremargc`**: operand count.
- **`argparse_getremargv`**: operand `char **` array (argv-style), or **`NULL`** if the count is zero.
- **`argparse_strerror`**: message string, empty if there is no error.
- **`argparse_getlist`**: list of `char *` items.
- **`argparse_getlistsz`**: list length.

**Behavior**

- **Failure**: return **`-1`**, read **`argparse_strerror`**. **`ARG_IGNORE`** affects **unknown** options only.
- **Callbacks** (**`OPT_DECL`**): invocation order follows **argv**.
- **Duplicate option**: last wins for scalars, **lists** append.

---

## 7. Example

```c
#include <argparse.h>
#include <stdbool.h>
#include <stdio.h>

int main(int argc, char **argv)
{
  bool verbose = false;
  int jobs = 1;
  char *out = NULL;
  struct argparse_list *includes = NULL;

  struct argparse_opt opts[] = {
      OPT_BOOL('v', "verbose", "verbose output", &verbose),
      OPT_INT('j', "jobs', "parallel jobs", &jobs, OPT_REQUIRED),
      OPT_STR('o', "output", "output file", &out, OPT_REQUIRED),
      OPT_LIST('I', "include", "include path", &includes),
      OPT_END(),
  };

  struct argparse ctx;
  if (argparse_init(&ctx, opts, NULL) != 0)
    return 1;

  int pn = argc - 1;
  char **pv = (pn > 0) ? argv + 1 : NULL;
  if (argparse_parse(&ctx, pn, pv) != 0) {
    fprintf(stderr, "%s\n", argparse_strerror(&ctx));
    argparse_fini(&ctx);
    return 1;
  }

  printf("jobs=%d operands=%zu\n", jobs,
         (size_t)argparse_getremargc(&ctx));
  argparse_fini(&ctx);
  return 0;
}
```

---

## 8. Summary

- **POSIX-shaped** argv: short, long, **`=`**, bool clusters where allowed, **`--`**, operands in the remainder.
- **Declarative** **`struct argparse_opt[]`** instead of hand-rolled parsing.
- **Extended** behavior with **`OPT_DECL`** and **`argparse_cb`**.
- **Remainder and lists** via accessors, **`argparse_fini`** releases parser-owned memory for **`ctx`**.
