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
#ifndef STC_RANDOM_H_INCLUDED
#define STC_RANDOM_H_INCLUDED

#include <math.h>
#include "stc/common.h"

// ===== crand64 ===================================

typedef struct { uint64_t data[4]; } crand64_state;

static inline void crand64_seed_r(crand64_state* rng, uint64_t seed) {
    uint64_t* s = rng->data;
    s[0] = seed*0x9e3779b97f4a7c15; s[0] ^= s[0] >> 30;
    s[1] = s[0]*0xbf58476d1ce4e5b9; s[1] ^= s[1] >> 27;
    s[2] = s[1]*0x94d049bb133111eb; s[2] ^= s[2] >> 31;
    s[3] = seed;
}

// Minimum period length 2^64 per stream. 2^63 streams (odd numbers only)
static inline uint64_t crand64_r(crand64_state* rng, uint64_t stream) {
    uint64_t* s = rng->data;
    const uint64_t result = (s[0] ^ (s[3] += stream)) + s[1];
    s[0] = s[1] ^ (s[1] >> 11);
    s[1] = s[2] + (s[2] << 3);
    s[2] = ((s[2] << 24) | (s[2] >> 40)) + result;
    return result;
}

static inline double crand64_real_r(crand64_state* rng, uint64_t stream)
    { return (double)(crand64_r(rng, stream) >> 11) * 0x1.0p-53; }

static inline crand64_state* _stc64(void) {
    static crand64_state s = {{0x9e3779bb07979af0,0x6f682616bae3641a,0xe220a8397b1dcdaf,0x1}};
    return &s;
}

static inline void crand64_seed(uint64_t seed)
    { crand64_seed_r(_stc64(), seed); }

static inline crand64_state crand64_make(uint64_t seed)
    { crand64_state s; crand64_seed_r(&s, seed); return s; }

static inline uint64_t crand64(void)
    { return crand64_r(_stc64(), 1); }

static inline double crand64_real(void)
    { return crand64_real_r(_stc64(), 1); }

// --- crand64_uniform ---

typedef struct {
    int64_t low;
    uint64_t range, threshold;
} crand64_uniform_dist;

static inline crand64_uniform_dist
crand64_uniform_lowhigh(int64_t low, int64_t high) {
    crand64_uniform_dist d = {low, (uint64_t)(high - low + 1)};
    d.threshold = (uint64_t)(0 - d.range) % d.range;
    return d;
}

static inline int64_t
crand64_uniform_r(crand64_state* rng, uint64_t stream, crand64_uniform_dist* d) {
    uint64_t lo, hi;
    #ifdef c_umul128
        do { c_umul128(crand64_r(rng, stream), d->range, &lo, &hi); } while (lo < d->threshold);
    #else
        do { lo = crand64_r(rng, stream); hi = lo % d->range; } while (lo - hi > -d->range);
    #endif
    return d->low + (int64_t)hi;
}

static inline int64_t crand64_uniform(crand64_uniform_dist* d)
    { return crand64_uniform_r(_stc64(), 1, d); }

// --- crand64_normal ---

typedef struct {
    double mean, stddev;
    double _next;
    int _has_next;
} crand64_normal_dist;

static inline double
crand64_normal_r(crand64_state* rng, uint64_t stream, crand64_normal_dist* d) {
    double v1, v2, sq, rt;
    if (d->_has_next++ & 1)
        return d->_next*d->stddev + d->mean;
    do {
        v1 = 2*crand64_real_r(rng, stream) - 1;
        v2 = 2*crand64_real_r(rng, stream) - 1;
        sq = v1*v1 + v2*v2;
    } while (sq >= 1 || sq == 0);
    rt = sqrt(-2*log(sq)/sq);
    d->_next = v2*rt;
    return (v1*rt)*d->stddev + d->mean;
}

static inline double crand64_normal(crand64_normal_dist* d)
    { return crand64_normal_r(_stc64(), 1, d); }

// ===== crand32 ===================================

typedef struct { uint32_t data[4]; } crand32_state;

static inline void crand32_seed_r(crand32_state* rng, uint32_t seed) {
    uint32_t* s = rng->data;
    s[0] = seed*0x9e3779b9; s[0] ^= s[0] >> 16;
    s[1] = s[0]*0x21f0aaad; s[1] ^= s[1] >> 15;
    s[2] = s[1]*0x735a2d97; s[2] ^= s[2] >> 15;
    s[3] = seed;
}

// Minimum period length 2^32 per stream. 2^31 streams (odd numbers only)
static inline uint32_t crand32_r(crand32_state* rng, uint32_t stream) {
    uint32_t* s = rng->data;
    const uint32_t result = (s[0] ^ (s[3] += stream)) + s[1];
    s[0] = s[1] ^ (s[1] >> 9);
    s[1] = s[2] + (s[2] << 3);
    s[2] = ((s[2] << 21) | (s[2] >> 11)) + result;
    return result;
}

static inline float crand32_real_r(crand32_state* rng, uint32_t stream)
    { return (float)(crand32_r(rng, stream) >> 9) * 0x1.0p-23f; }

static inline crand32_state* _stc32(void) {
    static crand32_state s = {{0x9e37e78e,0x6eab1ba1,0x64625032,0x1}};
    return &s;
}

static inline void crand32_seed(uint32_t seed)
    { crand32_seed_r(_stc32(), seed); }

static inline crand32_state crand32_make(uint32_t seed)
    { crand32_state s; crand32_seed_r(&s, seed); return s; }

static inline uint32_t crand32(void)
    { return crand32_r(_stc32(), 1); }

static inline float crand32_real(void)
    { return crand32_real_r(_stc32(), 1); }

// --- crand32_uniform ---

typedef struct {
    int32_t low;
    uint32_t range, threshold;
} crand32_uniform_dist;

static inline crand32_uniform_dist
crand32_uniform_lowhigh(int32_t low, int32_t high) {
    crand32_uniform_dist d = {low, (uint32_t)(high - low + 1)};
    d.threshold = (uint32_t)(0 - d.range) % d.range;
    return d;
}

static inline int32_t
crand32_uniform_r(crand32_state* rng, uint32_t stream, crand32_uniform_dist* d) {
    uint64_t r;
    do {
        r = crand32_r(rng, stream) * (uint64_t)d->range;
    } while ((uint32_t)r < d->threshold);
    return d->low + (int32_t)(r >> 32);
}

static inline int64_t crand32_uniform(crand32_uniform_dist* d)
    { return crand32_uniform_r(_stc32(), 1, d); }

// --- crand32_normal ---

typedef struct {
    float mean, stddev;
    float _next;
    int _has_next;
} crand32_normal_dist;

static inline float
crand32_normal_r(crand32_state* rng, uint32_t stream, crand32_normal_dist* d) {
    float v1, v2, sq, rt;
    if (d->_has_next++ & 1)
        return d->_next*d->stddev + d->mean;
    do {
        v1 = 2.0f*crand32_real_r(rng, stream) - 1.0f;
        v2 = 2.0f*crand32_real_r(rng, stream) - 1.0f;
        sq = v1*v1 + v2*v2;
    } while (sq >= 1.0f || sq == 0.0f);
    rt = sqrtf(-2.0f*logf(sq)/sq);
    d->_next = v2*rt;
    return (v1*rt)*d->stddev + d->mean;
}

static inline float
crand32_normal(crand32_normal_dist* d)
    { return crand32_normal_r(_stc32(), 1, d); }

#endif // STC_RANDOM_H_INCLUDED