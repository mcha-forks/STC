/* MIT License
 *
 * Copyright (c) 2024 Tyge Løvset
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
*/
/*
#include <stdio.h>
#include "stc/algorithm.h"

int main(void)
{
    crange r1 = crange_from(80, 90);
    c_foreach (i, crange, r1)
        printf(" %d", (int)*i.ref);
    puts("");

    // use a temporary crange object.
    int a = 100, b = INT32_MAX;
    crange r2 = crange_from(a, b, 8);
    c_filter(crange, r2
         , c_flt_skip(10)
        && (printf(" %zi", *value), c_flt_take(3))
    );
    puts("");
}
*/
#ifndef STC_CRANGE_H_INCLUDED
#define STC_CRANGE_H_INCLUDED

#include "../common.h"

typedef isize crange_value;
typedef struct { crange_value start, end, step, value; } crange;
typedef struct { crange_value *ref, end, step; } crange_iter;

#define crange_from(...) c_MACRO_OVERLOAD(crange_from, __VA_ARGS__)
#define crange_from_1(start) crange_from_3(start, INTPTR_MAX, 1)
#define crange_from_2(start, stop) crange_from_3(start, stop, 1)

#define c_iota(...) c_MACRO_OVERLOAD(c_iota, __VA_ARGS__)
#define c_iota_1(start) c_iota_3(start, INTPTR_MAX, 1)
#define c_iota_2(start, stop) c_iota_3(start, stop, 1)
#define c_iota_3(start, stop, step) ((crange[]){crange_from_3(start, stop, step)})[0]

STC_INLINE crange crange_from_3(crange_value start, crange_value stop, crange_value step)
    { crange r = {start, stop - (step > 0), step}; return r; }

STC_INLINE crange_iter crange_begin(crange* self) {
    self->value = self->start;
    crange_iter it = {&self->value, self->end, self->step};
    return it;
}

STC_INLINE void crange_next(crange_iter* it) {
    if ((it->step > 0) == ((*it->ref += it->step) > it->end))
        it->ref = NULL;
}

#endif // STC_CRANGE_H_INCLUDE