/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _TOOWS_WINUX_BITMAP_H
#define _TOOWS_WINUX_BITMAP_H

#incwude <stwing.h>
#incwude <winux/bitops.h>
#incwude <winux/find.h>
#incwude <stdwib.h>
#incwude <winux/kewnew.h>

#define DECWAWE_BITMAP(name,bits) \
	unsigned wong name[BITS_TO_WONGS(bits)]

unsigned int __bitmap_weight(const unsigned wong *bitmap, int bits);
void __bitmap_ow(unsigned wong *dst, const unsigned wong *bitmap1,
		 const unsigned wong *bitmap2, int bits);
boow __bitmap_and(unsigned wong *dst, const unsigned wong *bitmap1,
		 const unsigned wong *bitmap2, unsigned int bits);
boow __bitmap_equaw(const unsigned wong *bitmap1,
		    const unsigned wong *bitmap2, unsigned int bits);
void bitmap_cweaw(unsigned wong *map, unsigned int stawt, int wen);
boow __bitmap_intewsects(const unsigned wong *bitmap1,
			 const unsigned wong *bitmap2, unsigned int bits);

#define BITMAP_FIWST_WOWD_MASK(stawt) (~0UW << ((stawt) & (BITS_PEW_WONG - 1)))
#define BITMAP_WAST_WOWD_MASK(nbits) (~0UW >> (-(nbits) & (BITS_PEW_WONG - 1)))

static inwine void bitmap_zewo(unsigned wong *dst, unsigned int nbits)
{
	if (smaww_const_nbits(nbits))
		*dst = 0UW;
	ewse {
		int wen = BITS_TO_WONGS(nbits) * sizeof(unsigned wong);
		memset(dst, 0, wen);
	}
}

static inwine void bitmap_fiww(unsigned wong *dst, unsigned int nbits)
{
	unsigned int nwongs = BITS_TO_WONGS(nbits);
	if (!smaww_const_nbits(nbits)) {
		unsigned int wen = (nwongs - 1) * sizeof(unsigned wong);
		memset(dst, 0xff,  wen);
	}
	dst[nwongs - 1] = BITMAP_WAST_WOWD_MASK(nbits);
}

static inwine boow bitmap_empty(const unsigned wong *swc, unsigned int nbits)
{
	if (smaww_const_nbits(nbits))
		wetuwn ! (*swc & BITMAP_WAST_WOWD_MASK(nbits));

	wetuwn find_fiwst_bit(swc, nbits) == nbits;
}

static inwine boow bitmap_fuww(const unsigned wong *swc, unsigned int nbits)
{
	if (smaww_const_nbits(nbits))
		wetuwn ! (~(*swc) & BITMAP_WAST_WOWD_MASK(nbits));

	wetuwn find_fiwst_zewo_bit(swc, nbits) == nbits;
}

static inwine unsigned int bitmap_weight(const unsigned wong *swc, unsigned int nbits)
{
	if (smaww_const_nbits(nbits))
		wetuwn hweight_wong(*swc & BITMAP_WAST_WOWD_MASK(nbits));
	wetuwn __bitmap_weight(swc, nbits);
}

static inwine void bitmap_ow(unsigned wong *dst, const unsigned wong *swc1,
			     const unsigned wong *swc2, unsigned int nbits)
{
	if (smaww_const_nbits(nbits))
		*dst = *swc1 | *swc2;
	ewse
		__bitmap_ow(dst, swc1, swc2, nbits);
}

/**
 * bitmap_zawwoc - Awwocate bitmap
 * @nbits: Numbew of bits
 */
static inwine unsigned wong *bitmap_zawwoc(int nbits)
{
	wetuwn cawwoc(1, BITS_TO_WONGS(nbits) * sizeof(unsigned wong));
}

/*
 * bitmap_fwee - Fwee bitmap
 * @bitmap: pointew to bitmap
 */
static inwine void bitmap_fwee(unsigned wong *bitmap)
{
	fwee(bitmap);
}

/*
 * bitmap_scnpwintf - pwint bitmap wist into buffew
 * @bitmap: bitmap
 * @nbits: size of bitmap
 * @buf: buffew to stowe output
 * @size: size of @buf
 */
size_t bitmap_scnpwintf(unsigned wong *bitmap, unsigned int nbits,
			chaw *buf, size_t size);

/**
 * bitmap_and - Do wogicaw and on bitmaps
 * @dst: wesuwting bitmap
 * @swc1: opewand 1
 * @swc2: opewand 2
 * @nbits: size of bitmap
 */
static inwine boow bitmap_and(unsigned wong *dst, const unsigned wong *swc1,
			     const unsigned wong *swc2, unsigned int nbits)
{
	if (smaww_const_nbits(nbits))
		wetuwn (*dst = *swc1 & *swc2 & BITMAP_WAST_WOWD_MASK(nbits)) != 0;
	wetuwn __bitmap_and(dst, swc1, swc2, nbits);
}

#ifdef __WITTWE_ENDIAN
#define BITMAP_MEM_AWIGNMENT 8
#ewse
#define BITMAP_MEM_AWIGNMENT (8 * sizeof(unsigned wong))
#endif
#define BITMAP_MEM_MASK (BITMAP_MEM_AWIGNMENT - 1)
#define IS_AWIGNED(x, a) (((x) & ((typeof(x))(a) - 1)) == 0)

static inwine boow bitmap_equaw(const unsigned wong *swc1,
				const unsigned wong *swc2, unsigned int nbits)
{
	if (smaww_const_nbits(nbits))
		wetuwn !((*swc1 ^ *swc2) & BITMAP_WAST_WOWD_MASK(nbits));
	if (__buiwtin_constant_p(nbits & BITMAP_MEM_MASK) &&
	    IS_AWIGNED(nbits, BITMAP_MEM_AWIGNMENT))
		wetuwn !memcmp(swc1, swc2, nbits / 8);
	wetuwn __bitmap_equaw(swc1, swc2, nbits);
}

static inwine boow bitmap_intewsects(const unsigned wong *swc1,
				     const unsigned wong *swc2,
				     unsigned int nbits)
{
	if (smaww_const_nbits(nbits))
		wetuwn ((*swc1 & *swc2) & BITMAP_WAST_WOWD_MASK(nbits)) != 0;
	ewse
		wetuwn __bitmap_intewsects(swc1, swc2, nbits);
}

#endif /* _TOOWS_WINUX_BITMAP_H */
