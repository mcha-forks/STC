# Introduction

UNDER CONSTRUCTION!

This describes the API of the unordered set type **cset**.

## Declaration

```c
#define using_cset_str()

#define using_cset(X, Key, keyEqualsRaw=c_default_equals,
                           keyHashRaw=c_default_hash16,
                           keyDestroy=c_default_del,
                           RawKey=Key,
                           keyToRaw=c_default_to_raw,
                           keyFromRaw=c_default_from_raw)
```
The macro `using_cset()` can be instantiated with 2, 4, 5, or 8 arguments in the global scope.
Default values are given above for args not specified. `X` is a type tag name and
will affect the names of all cset types and methods. E.g. declaring `using_cset(my, int);`, `X` should
be replaced by `my` in all of the following documentation.

`using_cset_str()` is a predefined macro for `using_cset(str, cstr_t, ...)`.

## Types

| Type name            | Type definition                       | Used to represent...               |
|:---------------------|:--------------------------------------|:-----------------------------------|
| `cset_X`             | `struct {`                            | The cset type                      |
|                      | `  cset_X_value_t* table;`            |                                    |
|                      | `  uint8_t* _hashx;`                  |                                    |
|                      | `  ...;`                              |                                    |
|                      | `}`                                   |                                    |
| `cset_X_key_t`       | `Key`                                 | The cset key type                  |
| `cset_X_mapped_t`    | `Mapped`                              | cset mapped type                   |
| `cset_X_value_t`     | `Key`                                 | The cset value type                |
| `cset_X_result_t`    | `struct {`                            | Result of insert/emplace           |
|                      | `  cset_X_value_t* first;`            |                                    |
|                      | `  bool second; /* inserted */`       |                                    |
|                      | `}`                                   |                                    |
| `cset_X_input_t`     | `cset_X_value_t`                      | cset input type                    |
| `cset_X_iter_t`      | `struct {`                            | cset iterator                      |
|                      | `  cset_X_value_t* val;`              |                                    |
|                      | `  ...;`                              |                                    |
|                      | `}`                                   |                                    |

## Constants and macros

| Name                                            | Purpose                  |
|:------------------------------------------------|:-------------------------|
|  `cset_inits`                                   | Initializer const        |
|  `cset_empty(set)`                              | Test for empty set       |
|  `cset_size(set)`                               | Get set size             |
|  `cset_capacity(set)`                           | Get set capacity         |
|  `c_try_emplace(self, ctype, key, val)`         | Emplace if key exist     |
|  `c_insert_items(self, ctype, array)`           | Insert literals list     |

## Header file

All cset definitions and prototypes may be included in your C source file by including a single header file.

```c
#include "stc/cset.h" or "stc/cmap.h"
```
## Methods

### Construction

The interface for cset_X:
```c
cset_X              cset_X_init(void);
cset_X              cset_X_with_capacity(size_t cap);
void                cset_X_set_load_factors(cset_X* self, float max, float shrink);

void                cset_X_clear(cset_X* self);
void                cset_X_reserve(cset_X* self, size_t size);
void                cset_X_swap(cset_X* a, cset_X* b);

void                cset_X_del(cset_X* self);

bool                cset_X_empty(cset_X m);
size_t              cset_X_size(cset_X m);
size_t              cset_X_bucket_count(cset_X m);
size_t              cset_X_capacity(cset_X m);

void                cset_X_push_n(cset_X* self, const cset_X_input_t in[], size_t size);

cset_X_result_t     cset_X_emplace(cset_X* self, cset_X_rawkey_t rawKey);
cset_X_result_t     cset_X_insert(cset_X* self, cset_X_rawkey_t rawKey);

size_t              cset_X_erase(cset_X* self, cset_X_rawkey_t rawKey);
void                cset_X_erase_entry(cset_X* self, cset_X_key_t* key);
cset_X_iter_t       cset_X_erase_at(cset_X* self, cset_X_iter_t pos);

cset_X_value_t*     cset_X_find(const cset_X* self, cset_X_rawkey_t rawKey);
bool                cset_X_contains(const cset_X* self, cset_X_rawkey_t rawKey);

cset_X_iter_t       cset_X_begin(cset_X* self);
cset_X_iter_t       cset_X_end(cset_X* self);
void                cset_X_next(cset_X_iter_t* it);
cset_X_mapped_t*    cset_X_itval(cset_X_iter_t it);

cset_bucket_t       cset_X_bucket(const cset_X* self, const cset_X_rawkey_t* rawKeyPtr);

uint32_t            c_default_hash16(const void *data, size_t len);
uint32_t            c_default_hash32(const void* data, size_t len);
```

Example:
```c
#include <stc/cstr.h>
#include <stc/cmap.h>

using_cset_str();

int main() {
    cset_str words = cset_str_init();
    cset_str_emplace(&words, "Hello");
    cset_str_emplace(&words, "Crazy");
    cset_str_emplace(&words, "World");
    cset_str_erase(&words, "Crazy");

    // iterate the set of cstr_t values:
    c_foreach (i, cset_str, words)
        printf("%s ", i.val->str);
    cset_str_del(&words);
}
// Output:
Hello World
```