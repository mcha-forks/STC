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
#ifdef i_more
#undef i_more
#else
#undef i_TYPE
#undef i_type
#undef i_tag
#undef i_opt
#undef i_capacity

#undef i_key
#undef i_keyraw
#undef i_key_cstr
#undef i_key_str    // [deprecated]
#undef i_key_arc
#undef i_key_box
#undef i_key_arcbox // [deprecated]
#undef i_keyclass
#undef i_rawclass   // define i_keyraw, and bind i_cmp, i_eq, i_hash "members"
#undef i_cmpclass   // like i_keyraw, but defines i_use_cmp as well (always implement comparisons)
#undef i_keyclone
#undef i_keyfrom
#undef i_keytoraw
#undef i_cmp
#undef i_less
#undef i_eq
#undef i_hash
#undef i_keydrop

#undef i_val
#undef i_val2       // i_val, i_valraw
#undef i_valraw
#undef i_val_cstr
#undef i_val_str    // [deprecated]
#undef i_val_arc
#undef i_val_box
#undef i_val_arcbox // [deprecated]
#undef i_valclass
#undef i_valclone
#undef i_valfrom
#undef i_valtoraw
#undef i_valdrop

#undef i_use_cmp
#undef i_use_eq
#undef i_no_hash
#undef i_no_clone
#undef i_no_emplace
#undef i_is_forward

#undef _i_has_cmp
#undef _i_has_eq
#undef _i_prefix
#undef _i_template
#undef _i_self
#endif
