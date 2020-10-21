/* MIT License
 *
 * Copyright (c) 2020 Tyge Løvset, NORCE, www.norceresearch.no
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
#ifndef CFMT__H__
#define CFMT__H__

#include <stc/cstr.h>

// https://gist.github.com/alexameen/6550d892338626964a870e408d1e8912
// https://gist.github.com/alexameen/4440e4bcad557a464dcc9ff884763049

STC_API void
_cfmt_printf(int s, const char* fmt, ...);
STC_API char *
_cfmt_conv(const char *fmt, ...);

#ifndef __cplusplus
#define _cfmt_fn(x) _Generic ((x), \
    FILE*: fprintf, \
    char *: sprintf, \
    int: _cfmt_printf, \
    cstr_t *: cstr_fmt)

#define _cfmt(x) _Generic ((x), \
    char: "c", \
    unsigned char: "hhu", \
    short: "hd", \
    unsigned short: "hu", \
    int: "d", \
    unsigned: "u", \
    long: "ld", \
    unsigned long: "lu", \
    long long: "lld", \
    unsigned long long: "llu", \
    float: "g", \
    double: "g", \
    long double: "Lg", \
    char *: "s", \
    void *: "p")
#else
    inline auto _cfmt_fn(FILE*) {return fprintf;}
    inline auto _cfmt_fn(char*) {return sprintf;}
    inline auto _cfmt_fn(int s) {return _cfmt_printf;}
    inline auto _cfmt_fn(cstr_t*) {return cstr_fmt;}
    inline auto _cfmt(char x) {return "c";}
    inline auto _cfmt(unsigned char x) {return "hhu";}
    inline auto _cfmt(short x) {return "hd";}
    inline auto _cfmt(unsigned short x) {return "hu";}
    inline auto _cfmt(int x) {return "d";}
    inline auto _cfmt(unsigned x) {return "u";}
    inline auto _cfmt(long x) {return "ld";}
    inline auto _cfmt(unsigned long x) {return "lu";}
    inline auto _cfmt(long long x) {return "lld";}
    inline auto _cfmt(unsigned long long x) {return "llu";}
    inline auto _cfmt(float x) {return "g";}
    inline auto _cfmt(double x) {return "g";}
    inline auto _cfmt(long double x) {return "Lg";}
    inline auto _cfmt(const char *x) {return "s";}
    inline auto _cfmt(const void *x) {return "p";}
#endif

#define c_print(...) c_MACRO_OVERLOAD(c_print, __VA_ARGS__)
#define c_print_2(to, fmt) \
    do { char *_fm = _cfmt_conv(fmt); \
        _cfmt_fn(to)(to, _fm); free(_fm); } while (0)
#define c_print_3(to, fmt, c) \
    do { char *_fm = _cfmt_conv(fmt, _cfmt(c)); \
        _cfmt_fn(to)(to, _fm, c); free(_fm); } while (0)
#define c_print_4(to, fmt, c, d) \
    do { char *_fm = _cfmt_conv(fmt, _cfmt(c), _cfmt(d)); \
        _cfmt_fn(to)(to, _fm, c, d); free(_fm); } while (0)
#define c_print_5(to, fmt, c, d, e) \
    do { char *_fm = _cfmt_conv(fmt, _cfmt(c), _cfmt(d), _cfmt(e)); \
        _cfmt_fn(to)(to, _fm, c, d, e); free(_fm); } while (0)
#define c_print_6(to, fmt, c, d, e, f) \
    do { char *_fm = _cfmt_conv(fmt, _cfmt(c), _cfmt(d), _cfmt(e), _cfmt(f)); \
        _cfmt_fn(to)(to, _fm, c, d, e, f); free(_fm); } while (0)
#define c_print_7(to, fmt, c, d, e, f, g) \
    do { char *_fm = _cfmt_conv(fmt, _cfmt(c), _cfmt(d), _cfmt(e), _cfmt(f), _cfmt(g)); \
        _cfmt_fn(to)(to, _fm, c, d, e, f, g); free(_fm); } while (0)
#define c_print_8(to, fmt, c, d, e, f, g, h) \
    do { char *_fm = _cfmt_conv(fmt, _cfmt(c), _cfmt(d), _cfmt(e), _cfmt(f), _cfmt(g), _cfmt(h)); \
        _cfmt_fn(to)(to, _fm, c, d, e, f, g, h); free(_fm); } while (0)
#define c_print_9(to, fmt, c, d, e, f, g, h, i) \
    do { char *_fm = _cfmt_conv(fmt, _cfmt(c), _cfmt(d), _cfmt(e), _cfmt(f), _cfmt(g), _cfmt(h), _cfmt(i)); \
        _cfmt_fn(to)(to, _fm, c, d, e, f, g, h, i); free(_fm); } while (0)
#define c_print_10(to, fmt, c, d, e, f, g, h, i, j) \
    do { char *_fm = _cfmt_conv(fmt, _cfmt(c), _cfmt(d), _cfmt(e), _cfmt(f), _cfmt(g), _cfmt(h), _cfmt(i), _cfmt(j)); \
        _cfmt_fn(to)(to, _fm, c, d, e, f, g, h, i, j); free(_fm); } while (0)
#define c_print_11(to, fmt, c, d, e, f, g, h, i, j, k) \
    do { char *_fm = _cfmt_conv(fmt, _cfmt(c), _cfmt(d), _cfmt(e), _cfmt(f), _cfmt(g), _cfmt(h), _cfmt(i), _cfmt(j), _cfmt(k)); \
        _cfmt_fn(to)(to, _fm, c, d, e, f, g, h, i, j, k); free(_fm); } while (0)
#define c_print_12(to, fmt, c, d, e, f, g, h, i, j, k, m) \
    do { char *_fm = _cfmt_conv(fmt, _cfmt(c), _cfmt(d), _cfmt(e), _cfmt(f), _cfmt(g), _cfmt(h), _cfmt(i), _cfmt(j), _cfmt(k), _cfmt(m)); \
        _cfmt_fn(to)(to, _fm, c, d, e, f, g, h, i, j, k, m); free(_fm); } while (0)
#define c_print_13(to, fmt, c, d, e, f, g, h, i, j, k, m, n) \
    do { char *_fm = _cfmt_conv(fmt, _cfmt(c), _cfmt(d), _cfmt(e), _cfmt(f), _cfmt(g), _cfmt(h), _cfmt(i), _cfmt(j), _cfmt(k), _cfmt(m), _cfmt(n)); \
        _cfmt_fn(to)(to, _fm, c, d, e, f, g, h, i, j, k, m, n); free(_fm); } while (0)
#define c_print_14(to, fmt, c, d, e, f, g, h, i, j, k, m, n, o) \
    do { char *_fm = _cfmt_conv(fmt, _cfmt(c), _cfmt(d), _cfmt(e), _cfmt(f), _cfmt(g), _cfmt(h), _cfmt(i), _cfmt(j), _cfmt(k), _cfmt(m), _cfmt(n), _cfmt(o)); \
        _cfmt_fn(to)(to, _fm, c, d, e, f, g, h, i, j, k, m, n, o); free(_fm); } while (0)
#define c_print_15(to, fmt, c, d, e, f, g, h, i, j, k, m, n, o, p) \
    do { char *_fm = _cfmt_conv(fmt, _cfmt(c), _cfmt(d), _cfmt(e), _cfmt(f), _cfmt(g), _cfmt(h), _cfmt(i), _cfmt(j), _cfmt(k), _cfmt(m), _cfmt(n), _cfmt(o), _cfmt(p)); \
        _cfmt_fn(to)(to, _fm, c, d, e, f, g, h, i, j, k, m, n, o, p); free(_fm); } while (0)
#define c_print_16(to, fmt, c, d, e, f, g, h, i, j, k, m, n, o, p, q) \
    do { char *_fm = _cfmt_conv(fmt, _cfmt(c), _cfmt(d), _cfmt(e), _cfmt(f), _cfmt(g), _cfmt(h), _cfmt(i), _cfmt(j), _cfmt(k), _cfmt(m), _cfmt(n), _cfmt(o), _cfmt(p), _cfmt(p)); \
        _cfmt_fn(to)(to, _fm, c, d, e, f, g, h, i, j, k, m, n, o, p, q); free(_fm); } while (0)
#define c_print_17(to, fmt, c, d, e, f, g, h, i, j, k, m, n, o, p, q, r) \
    do { char *_fm = _cfmt_conv(fmt, _cfmt(c), _cfmt(d), _cfmt(e), _cfmt(f), _cfmt(g), _cfmt(h), _cfmt(i), _cfmt(j), _cfmt(k), _cfmt(m), _cfmt(n), _cfmt(o), _cfmt(p), _cfmt(p), _cfmt(r)); \
        _cfmt_fn(to)(to, _fm, c, d, e, f, g, h, i, j, k, m, n, o, p, q, r); free(_fm); } while (0)
#define c_print_18(to, fmt, c, d, e, f, g, h, i, j, k, m, n, o, p, q, r, s) \
    do { char *_fm = _cfmt_conv(fmt, _cfmt(c), _cfmt(d), _cfmt(e), _cfmt(f), _cfmt(g), _cfmt(h), _cfmt(i), _cfmt(j), _cfmt(k), _cfmt(m), _cfmt(n), _cfmt(o), _cfmt(p), _cfmt(p), _cfmt(r), _cfmt(s)); \
        _cfmt_fn(to)(to, _fm, c, d, e, f, g, h, i, j, k, m, n, o, p, q, r, s); free(_fm); } while (0)

#if !defined(STC_HEADER) || defined(STC_IMPLEMENTATION)

#include <stdarg.h>

STC_DEF void
_cfmt_printf(int s, const char* fmt, ...) {
    va_list args;
	va_start(args, fmt);
    vfprintf(s ? stderr : stdout, fmt, args);
    va_end(args);
}

STC_DEF char *
_cfmt_conv(const char *fmt, ...) {
    char *fmt2 = (char *) malloc(strlen(fmt)*2 + 1), *p = fmt2, *f, ch;
    va_list args;
    va_start(args, fmt);
    do {
        switch ((ch = *fmt)) {
        case '%':
            if (fmt[1] == '%') *p++ = *fmt++;
            else va_arg(args, char *);
            break;
        case '}':
            if (fmt[1] == '}') ++fmt;
            break;
        case '{':
            if (fmt[1] == '{') { ++fmt; break; }
            if (fmt[1] == ':' || fmt[1] == '}') {
                *p++ = '%';
                fmt += 1 + (fmt[1] == ':');
                while (*fmt != '}' && *fmt) *p++ = *fmt++;
                f = va_arg(args, char *);
                if (!strchr("csdioxXufFeEaAgGnp", fmt[-1]))
                    while (*f) *p++ = *f++;
                fmt += (*fmt == '}');
                continue;
            }
            break;
        }
        *p++ = *fmt++;
    } while (ch);
    va_end(args);
    return fmt2;
}

#endif

#endif