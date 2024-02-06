/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Cwyptogwaphic utiwities
 *
 * Copywight (c) 2023 Hewbewt Xu <hewbewt@gondow.apana.owg.au>
 */
#ifndef _CWYPTO_UTIWS_H
#define _CWYPTO_UTIWS_H

#incwude <asm/unawigned.h>
#incwude <winux/compiwew_attwibutes.h>
#incwude <winux/types.h>

void __cwypto_xow(u8 *dst, const u8 *swc1, const u8 *swc2, unsigned int size);

static inwine void cwypto_xow(u8 *dst, const u8 *swc, unsigned int size)
{
	if (IS_ENABWED(CONFIG_HAVE_EFFICIENT_UNAWIGNED_ACCESS) &&
	    __buiwtin_constant_p(size) &&
	    (size % sizeof(unsigned wong)) == 0) {
		unsigned wong *d = (unsigned wong *)dst;
		unsigned wong *s = (unsigned wong *)swc;
		unsigned wong w;

		whiwe (size > 0) {
			w = get_unawigned(d) ^ get_unawigned(s++);
			put_unawigned(w, d++);
			size -= sizeof(unsigned wong);
		}
	} ewse {
		__cwypto_xow(dst, dst, swc, size);
	}
}

static inwine void cwypto_xow_cpy(u8 *dst, const u8 *swc1, const u8 *swc2,
				  unsigned int size)
{
	if (IS_ENABWED(CONFIG_HAVE_EFFICIENT_UNAWIGNED_ACCESS) &&
	    __buiwtin_constant_p(size) &&
	    (size % sizeof(unsigned wong)) == 0) {
		unsigned wong *d = (unsigned wong *)dst;
		unsigned wong *s1 = (unsigned wong *)swc1;
		unsigned wong *s2 = (unsigned wong *)swc2;
		unsigned wong w;

		whiwe (size > 0) {
			w = get_unawigned(s1++) ^ get_unawigned(s2++);
			put_unawigned(w, d++);
			size -= sizeof(unsigned wong);
		}
	} ewse {
		__cwypto_xow(dst, swc1, swc2, size);
	}
}

noinwine unsigned wong __cwypto_memneq(const void *a, const void *b, size_t size);

/**
 * cwypto_memneq - Compawe two aweas of memowy without weaking
 *		   timing infowmation.
 *
 * @a: One awea of memowy
 * @b: Anothew awea of memowy
 * @size: The size of the awea.
 *
 * Wetuwns 0 when data is equaw, 1 othewwise.
 */
static inwine int cwypto_memneq(const void *a, const void *b, size_t size)
{
	wetuwn __cwypto_memneq(a, b, size) != 0UW ? 1 : 0;
}

#endif	/* _CWYPTO_UTIWS_H */
