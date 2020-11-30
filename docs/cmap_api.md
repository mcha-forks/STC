# Introduction

UNDER CONSTRUCTION!

This describes the API of circular singly linked list type **cmap**.

## Declaration

```c
#define using_cmap_str()

#define using_cmap_strkey(Mapped, mappedDestroy=c_default_del)

#define using_cmap_strval(T, Key, keyEquals=c_default_equals,
                                  keyHash=c_default_hash16,
                                  keyDestroy=c_default_del,
                                  RawKey=Key,
                                  keyToRaw=c_default_to_raw,
                                  keyFromRaw=c_default_from_raw)

#define using_cmap(T, Key, Mapped, mappedDestroy=c_default_del,
                                   keyEqualsRaw=c_default_equals,
                                   keyHashRaw=c_default_hash16,
                                   keyDestroy=c_default_del,
                                   RawKey=Key,
                                   keyToRaw=c_default_to_raw,
                                   keyFromRaw=c_default_from_raw,
                                   RawMapped=Mapped,
                                   mappedFromRaw=c_default_from_raw)
```
The macro `using_cmap()` can be instantiated with 3, 4, 6, 10, or 12 arguments in the global scope.
Default values are given above for args not specified. `T` is a type tag name and
will affect the names of all cmap types and methods. E.g. declaring `using_cmap(my, int);`, `T` should
be replaced by `my` in all of the following documentation.

`using_cmap_str()` is a predefined macro for `using_cmap(str, cstr_t, ...)`.

## Types

| Type name            | Type definition                       | Used to represent...               |
|:---------------------|:--------------------------------------|:-----------------------------------|
| `cmap_T`             | `struct {`                            | The cmap type                      |
|                      | `  cmap_T_value_t* table;             |                                    |
|                      | `  uint8_t* _hashx;`                  |                                    |
|                      | `  ...;`                              |                                    |
|                      | `}`                                   |                                    |
| `cmap_T_key_t`       | `Key`                                 | The cmap key type                  |
| `cmap_T_mapped_t`    | `Mapped`                              | cmap mapped type                   |
| `cmap_T_value_t`     | `struct {`                            | The cmap value type                |
|                      | `  cmap_T_key_t first;                |                                    |
|                      | `  cmap_T_mapped_t second;`           |                                    |
|                      | `}`                                   |                                    |
| `cmap_T_input_t`     | `cmap_T_value_t`                      | cmap input type                    |
| `cmap_T_rawvalue_t`  | `RawMapped`                           | cmap raw value type                |
| `cmap_T_iter_t`      | `struct {`                            | cmap iterator                      |
|                      | `  cmap_T_value_t* val;`              |                                    |
|                      | `  ...;`                              |                                    |
|                      | `}`                                   |                                    |

## Constants and macros

| Name                       | Value            |
|:---------------------------|:-----------------|
|  `cmap_inits`              | `{...}`          |
|  `cmap_empty(map)`         | `true` if empty  |
|  `cmap_size(map)`          |                  |
|  `cmap_capacity(map)`      |                  |


## Header file

All cmap definitions and prototypes may be included in your C source file by including a single header file.

```c
#include "stc/cmap.h"
```
## Methods

### Construction

The interfaces to create a cmap_T object:
```c
cmap_T              cmap_T_init(void);
cmap_T              cmap_T_with_capacity(size_t cap);
void                cmap_T_set_load_factors(cmap_T* self, float max, float shrink);

void                cmap_T_clear(cmap_T* self);
void                cmap_T_reserve(cmap_T* self, size_t size);
void                cmap_T_swap(cmap_T* a, cmap_T* b);

void                cmap_T_del(cmap_T* self);

bool                cmap_T_empty(cmap_T m);
size_t              cmap_T_size(cmap_T m);
size_t              cmap_T_bucket_count(cmap_T m);
size_t              cmap_T_capacity(cmap_T m);

void                cmap_T_push_n(cmap_T* self, const cmap_T_input_t in[], size_t size);

cmap_T_result_t     cmap_T_emplace(cmap_T* self, RawKey rawKey RawMapped rawVal);
cmap_T_result_t     cmap_T_insert(cmap_T* self, cmap_T_input_t in);
cmap_T_result_t     cmap_T_insert_or_assign(cmap_T* self, RawKey rawKey, RawMapped rawVal);
cmap_T_result_t     cmap_T_put(cmap_T* self, RawKey rawKey, RawMapped rawVal);
cmap_T_result_t     cmap_T_putv(cmap_T* self, RawKey rawKey, Mapped mapped);
cmap_T_mapped_t*    cmap_T_at(const cmap_T* self, RawKey rawKey);

size_t              cmap_T_erase(cmap_T* self, RawKey rawKey)
void                cmap_T_erase_entry(cmap_T* self, cmap_T_value_t* val);
cmap_T_iter_t       cmap_T_erase_at(cmap_T* self, cmap_T_iter_t pos);

cmap_T_value_t*     cmap_T_find(const cmap_T* self, RawKey rawKey);
bool                cmap_T_contains(const cmap_T* self, RawKey rawKey);

cmap_T_iter_t       cmap_T_begin(cmap_T* self);
cmap_T_iter_t       cmap_T_end(cmap_T* self)
void                cmap_T_next(cmap_T_iter_t* it);
cmap_T_mapped_t*    cmap_T_itval(cmap_T_iter_t it);

cmap_bucket_t       cmap_T_bucket(const cmap_T* self, const cmap_T_rawkey_t* rawKeyPtr);

uint32_t            c_default_hash16(const void *data, size_t len);
uint32_t            c_default_hash32(const void* data, size_t len);
```