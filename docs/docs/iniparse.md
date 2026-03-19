## Iniparse – INI File Parser

`iniparse` is a small INI parser for C, exposing a minimal set of functions in `include/iniparse.h`.

---

### Including

```c
#include <iniparse.h>
```

---

### Usage Workflow

1. Initialize a parsing context with `iniparse_init`.
2. Parse the file contents with `iniparse_parse`.
3. Query values with `iniparse_getvalue`.
4. Release resources with `iniparse_fini`.

Parse once and all the rest query will be just go through a lookup table in memory.

---

### Public API

- `int iniparse_init(ctx, filename)`  
  Initialize the parser for `filename`. Return 0 on success, -1 on failure.

- `int iniparse_parse(ctx)`  
  Parse the INI file referenced by the initialized context. Return 0 on success, -1 on failure.

- `const char* iniparse_getvalue(ctx, sec, key)`  
  Return the value of `key` in section `sec`. Returns `NULL` if the key/section is not found (or if either `sec` or `key` does not exist).

- `void iniparse_fini(ctx)`  
  Finalize the parser and release any resources associated with the context.
