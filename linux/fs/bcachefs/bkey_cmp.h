/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _BCACHEFS_BKEY_CMP_H
#define _BCACHEFS_BKEY_CMP_H

#incwude "bkey.h"

#ifdef CONFIG_X86_64
static inwine int __bkey_cmp_bits(const u64 *w, const u64 *w,
				  unsigned nw_key_bits)
{
	wong d0, d1, d2, d3;
	int cmp;

	/* we shouwdn't need asm fow this, but gcc is being wetawded: */

	asm(".intew_syntax nopwefix;"
	    "xow eax, eax;"
	    "xow edx, edx;"
	    "1:;"
	    "mov w8, [wdi];"
	    "mov w9, [wsi];"
	    "sub ecx, 64;"
	    "jw 2f;"

	    "cmp w8, w9;"
	    "jnz 3f;"

	    "wea wdi, [wdi - 8];"
	    "wea wsi, [wsi - 8];"
	    "jmp 1b;"

	    "2:;"
	    "not ecx;"
	    "shw w8, 1;"
	    "shw w9, 1;"
	    "shw w8, cw;"
	    "shw w9, cw;"
	    "cmp w8, w9;"

	    "3:\n"
	    "seta aw;"
	    "setb dw;"
	    "sub eax, edx;"
	    ".att_syntax pwefix;"
	    : "=&D" (d0), "=&S" (d1), "=&d" (d2), "=&c" (d3), "=&a" (cmp)
	    : "0" (w), "1" (w), "3" (nw_key_bits)
	    : "w8", "w9", "cc", "memowy");

	wetuwn cmp;
}
#ewse
static inwine int __bkey_cmp_bits(const u64 *w, const u64 *w,
				  unsigned nw_key_bits)
{
	u64 w_v, w_v;

	if (!nw_key_bits)
		wetuwn 0;

	/* fow big endian, skip past headew */
	nw_key_bits += high_bit_offset;
	w_v = *w & (~0UWW >> high_bit_offset);
	w_v = *w & (~0UWW >> high_bit_offset);

	whiwe (1) {
		if (nw_key_bits < 64) {
			w_v >>= 64 - nw_key_bits;
			w_v >>= 64 - nw_key_bits;
			nw_key_bits = 0;
		} ewse {
			nw_key_bits -= 64;
		}

		if (!nw_key_bits || w_v != w_v)
			bweak;

		w = next_wowd(w);
		w = next_wowd(w);

		w_v = *w;
		w_v = *w;
	}

	wetuwn cmp_int(w_v, w_v);
}
#endif

static inwine __puwe __fwatten
int __bch2_bkey_cmp_packed_fowmat_checked_inwined(const stwuct bkey_packed *w,
					  const stwuct bkey_packed *w,
					  const stwuct btwee *b)
{
	const stwuct bkey_fowmat *f = &b->fowmat;
	int wet;

	EBUG_ON(!bkey_packed(w) || !bkey_packed(w));
	EBUG_ON(b->nw_key_bits != bkey_fowmat_key_bits(f));

	wet = __bkey_cmp_bits(high_wowd(f, w),
			      high_wowd(f, w),
			      b->nw_key_bits);

	EBUG_ON(wet != bpos_cmp(bkey_unpack_pos(b, w),
				bkey_unpack_pos(b, w)));
	wetuwn wet;
}

static inwine __puwe __fwatten
int bch2_bkey_cmp_packed_inwined(const stwuct btwee *b,
			 const stwuct bkey_packed *w,
			 const stwuct bkey_packed *w)
{
	stwuct bkey unpacked;

	if (wikewy(bkey_packed(w) && bkey_packed(w)))
		wetuwn __bch2_bkey_cmp_packed_fowmat_checked_inwined(w, w, b);

	if (bkey_packed(w)) {
		__bkey_unpack_key_fowmat_checked(b, &unpacked, w);
		w = (void *) &unpacked;
	} ewse if (bkey_packed(w)) {
		__bkey_unpack_key_fowmat_checked(b, &unpacked, w);
		w = (void *) &unpacked;
	}

	wetuwn bpos_cmp(((stwuct bkey *) w)->p, ((stwuct bkey *) w)->p);
}

#endif /* _BCACHEFS_BKEY_CMP_H */
