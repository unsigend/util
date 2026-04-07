# iniparse

## Overview

`iniparse` is a minimal INI file parser and writer with a `FILE`-like interface. It supports reading, modifying, and writing INI files. The single header is `iniparse.h`.

An `iniFILE` handle is obtained via `iniparse_open` or `iniparse_create` and must be released with `iniparse_close`. All strings stored in the handle are heap-allocated and valid for the lifetime of the handle.

## Conventions

- Lines beginning with `;` or `#` are comments and are ignored
- Sections are declared as `[section name]`
- Entries have the form `key = value`
- Whitespace around section names, keys, and values is stripped
- Entries outside any section are not supported

## Structs

### `iniFILE`

Opaque handle representing an open INI file. Fields are managed internally and should not be modified directly.

### `ini_sec`

Represents a section. Contains the section name and its associated entries. Managed internally.

### `ini_entry`

Represents a single key/value pair within a section. Managed internally.

## Functions

### Lifecycle

#### `iniparse_open`

```c
struct iniFILE *iniparse_open(const char *filename);
```

Opens and memory-maps an existing INI file. Returns a heap-allocated handle on success, NULL on error. The file must exist and be non-empty. Call `iniparse_parse` before any get/set operations.

**Parameters**

- `filename` — path to the INI file to open

#### `iniparse_create`

```c
struct iniFILE *iniparse_create(const char *filename);
```

Creates an empty in-memory INI handle associated with the given filename. No file is opened or created on disk. Use `iniparse_set` to populate it, then `iniparse_write` to persist. Returns NULL on error.

**Parameters**

- `filename` — path that will be used when `iniparse_write` is called

#### `iniparse_parse`

```c
int iniparse_parse(struct iniFILE *fp);
```

Parses the file content into the in-memory structure. Must be called after `iniparse_open` before any get/set operations. On a handle from `iniparse_create` this is a no-op and returns 0. Returns 0 on success, -1 on error.

#### `iniparse_close`

```c
void iniparse_close(struct iniFILE *fp);
```

Releases all resources held by the handle including all heap-allocated strings. Must be called when the handle is no longer needed.

### Read / Write

#### `iniparse_get`

```c
const char *iniparse_get(struct iniFILE *fp, const char *sec, const char *key);
```

Returns the value for the given section and key, or NULL if not found. The returned pointer is valid for the lifetime of the handle.

**Parameters**

- `sec` — section name
- `key` — key name within that section

#### `iniparse_set`

```c
int iniparse_set(struct iniFILE *fp, const char *sec, const char *key,
                 const char *val);
```

Sets the value for a key. If the key exists it is updated in place. If the key or section does not exist they are created. `val` may be NULL to store a key with no value. Returns 0 on success, -1 on error.

#### `iniparse_unset`

```c
int iniparse_unset(struct iniFILE *fp, const char *sec, const char *key);
```

Removes a key/value pair from the section. The entry is omitted from all subsequent output. Returns 0 on success, -1 if the key is not found.

### Persist

#### `iniparse_write`

```c
int iniparse_write(struct iniFILE *fp);
```

Writes the in-memory state back to `fp->filename` atomically using a lockfile and rename. Returns the number of bytes written on success, -1 on error.

#### `iniparse_writeto`

```c
int iniparse_writeto(struct iniFILE *fp, const char *filename);
```

Writes the in-memory state to the given file atomically. The original `fp->filename` is not affected. Returns the number of bytes written on success, -1 on error.

### Print

#### `iniparse_fprint`

```c
int iniparse_fprint(struct iniFILE *fp, FILE *stream);
```

Writes all entries to `stream` in the format `section.key=value`. Returns the number of bytes written.

#### `iniparse_sprint`

```c
int iniparse_sprint(struct iniFILE *fp, char *buf);
```

Writes all entries to `buf` in the format `section.key=value`. No bounds checking. Returns the number of bytes written.

#### `iniparse_snprint`

```c
int iniparse_snprint(struct iniFILE *fp, char *buf, size_t bufsz);
```

Same as `iniparse_sprint` but writes at most `bufsz` bytes. Always returns the number of bytes that would have been written regardless of truncation, consistent with `snprintf` semantics.

## Example

```c
#include <iniparse.h>
#include <stdio.h>

int main(void)
{
    /* read and modify an existing file */
    struct iniFILE *fp = iniparse_open(".git/config");
    if (!fp)
        return 1;
    if (iniparse_parse(fp) == -1) {
        iniparse_close(fp);
        return 1;
    }

    const char *name = iniparse_get(fp, "user", "name");
    if (name)
        printf("user.name = %s\n", name);

    iniparse_set(fp, "core", "bare", "false");
    iniparse_unset(fp, "core", "ignoreCase");
    iniparse_write(fp);
    iniparse_close(fp);

    /* create a new file from scratch */
    struct iniFILE *cfg = iniparse_create(".qgit/config");
    if (!cfg)
        return 1;
    iniparse_set(cfg, "core", "repositoryFormat", "0");
    iniparse_set(cfg, "core", "bare", "false");
    iniparse_write(cfg);
    iniparse_close(cfg);

    return 0;
}
```
