# iniparse

## Overview

`iniparse` is a minimal INI file parser, it maps section/key pairs to their values and provides a simple lookup interface, the header is `iniparse.h`.

Two structs form the public surface: `iniparse_ctx` holds the parse state for a file, `iniparse_entry` represents a single key/value pair under a section. Both are stack-allocatable, and the context must be passed to every API call.

## Conventions

INI files follow standard conventions:

- Lines beginning with `;` or `#` are comments and are ignored
- Sections are declared as `[section_name]`
- Entries have the form `key = value`
- Whitespace around section names, keys, and values is stripped
- Entries outside any section are not supported, every key must belong to a section

## Structs

### `iniparse_ctx`

Holds all state associated with a parsed file. Fields are managed internally and should not be modified directly.

```c
struct iniparse_ctx {
    const char *filename;
    char       *buf;
    size_t      bufsz;
    size_t      nentries;
    size_t      nentriescap;
    struct iniparse_entry *entries;
};
```

### `iniparse_entry`

Represents a single parsed entry. Pointers point into the memory-mapped file buffer owned by the context, so they are valid only while the context is live.

```c
struct iniparse_entry {
    const char *sec;
    const char *key;
    const char *val;
};
```

## Functions

### `iniparse_init`

```c
int iniparse_init(struct iniparse_ctx *ctx, const char *filename);
```

Initializes a context and memory-maps the given file for parsing. Must be called before any other function. Returns 0 on success, -1 on error.

**Parameters**

- `ctx` — pointer to an uninitialized context struct
- `filename` — path to the INI file to open

### `iniparse_parse`

```c
int iniparse_parse(struct iniparse_ctx *ctx);
```

Parses the file associated with the context and populates its entry list. Must be called after `iniparse_init`. Returns 0 on success, -1 on error.

**Parameters**

- `ctx` — an initialized context

### `iniparse_fini`

```c
void iniparse_fini(struct iniparse_ctx *ctx);
```

Releases all resources held by the context, including the memory-mapped buffer and the entry list. Must be called when the context is no longer needed.

**Parameters**

- `ctx` — an initialized context

### `iniparse_getvalue`

```c
const char *iniparse_getvalue(struct iniparse_ctx *ctx, const char *sec, const char *key);
```

Looks up the value for a given section and key. Returns a pointer into the internal buffer on success, NULL if the section or key is not found. The returned pointer is valid only while the context is live and `iniparse_fini` has not been called.

**Parameters**

- `ctx` — a parsed context
- `sec` — section name to search
- `key` — key name to search within that section

## Example

```c
#include <iniparse.h>
#include <stdio.h>

int main(void)
{
    struct iniparse_ctx ctx;
    const char *val;

    /* initialize and parse */
    if (iniparse_init(&ctx, "config.ini") == -1)
        return 1;
    if (iniparse_parse(&ctx) == -1) {
        iniparse_fini(&ctx);
        return 1;
    }

    /* lookup a value */
    val = iniparse_getvalue(&ctx, "database", "host");
    if (val)
        printf("host = %s\n", val);

    /* release resources */
    iniparse_fini(&ctx);
    return 0;
}
```

Given a file `config.ini`:

```ini
[database]
host = localhost
port = 5432
```

The output would be:

```
host = localhost
```
