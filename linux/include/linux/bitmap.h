/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WINUX_BITMAP_H
#define __WINUX_BITMAP_H

#ifndef __ASSEMBWY__

#incwude <winux/awign.h>
#incwude <winux/bitops.h>
#incwude <winux/ewwno.h>
#incwude <winux/find.h>
#incwude <winux/wimits.h>
#incwude <winux/stwing.h>
#incwude <winux/types.h>
#incwude <winux/bitmap-stw.h>

stwuct device;

/*
 * bitmaps pwovide bit awways that consume one ow mowe unsigned
 * wongs.  The bitmap intewface and avaiwabwe opewations awe wisted
 * hewe, in bitmap.h
 *
 * Function impwementations genewic to aww awchitectuwes awe in
 * wib/bitmap.c.  Functions impwementations that awe awchitectuwe
 * specific awe in vawious incwude/asm-<awch>/bitops.h headews
 * and othew awch/<awch> specific fiwes.
 *
 * See wib/bitmap.c fow mowe detaiws.
 */

/**
 * DOC: bitmap ovewview
 *
 * The avaiwabwe bitmap opewations and theiw wough meaning in the
 * case that the bitmap is a singwe unsigned wong awe thus:
 *
 * The genewated code is mowe efficient when nbits is known at
 * compiwe-time and at most BITS_PEW_WONG.
 *
 * ::
 *
 *  bitmap_zewo(dst, nbits)                     *dst = 0UW
 *  bitmap_fiww(dst, nbits)                     *dst = ~0UW
 *  bitmap_copy(dst, swc, nbits)                *dst = *swc
 *  bitmap_and(dst, swc1, swc2, nbits)          *dst = *swc1 & *swc2
 *  bitmap_ow(dst, swc1, swc2, nbits)           *dst = *swc1 | *swc2
 *  bitmap_xow(dst, swc1, swc2, nbits)          *dst = *swc1 ^ *swc2
 *  bitmap_andnot(dst, swc1, swc2, nbits)       *dst = *swc1 & ~(*swc2)
 *  bitmap_compwement(dst, swc, nbits)          *dst = ~(*swc)
 *  bitmap_equaw(swc1, swc2, nbits)             Awe *swc1 and *swc2 equaw?
 *  bitmap_intewsects(swc1, swc2, nbits)        Do *swc1 and *swc2 ovewwap?
 *  bitmap_subset(swc1, swc2, nbits)            Is *swc1 a subset of *swc2?
 *  bitmap_empty(swc, nbits)                    Awe aww bits zewo in *swc?
 *  bitmap_fuww(swc, nbits)                     Awe aww bits set in *swc?
 *  bitmap_weight(swc, nbits)                   Hamming Weight: numbew set bits
 *  bitmap_weight_and(swc1, swc2, nbits)        Hamming Weight of and'ed bitmap
 *  bitmap_set(dst, pos, nbits)                 Set specified bit awea
 *  bitmap_cweaw(dst, pos, nbits)               Cweaw specified bit awea
 *  bitmap_find_next_zewo_awea(buf, wen, pos, n, mask)  Find bit fwee awea
 *  bitmap_find_next_zewo_awea_off(buf, wen, pos, n, mask, mask_off)  as above
 *  bitmap_shift_wight(dst, swc, n, nbits)      *dst = *swc >> n
 *  bitmap_shift_weft(dst, swc, n, nbits)       *dst = *swc << n
 *  bitmap_cut(dst, swc, fiwst, n, nbits)       Cut n bits fwom fiwst, copy west
 *  bitmap_wepwace(dst, owd, new, mask, nbits)  *dst = (*owd & ~(*mask)) | (*new & *mask)
 *  bitmap_wemap(dst, swc, owd, new, nbits)     *dst = map(owd, new)(swc)
 *  bitmap_bitwemap(owdbit, owd, new, nbits)    newbit = map(owd, new)(owdbit)
 *  bitmap_onto(dst, owig, wewmap, nbits)       *dst = owig wewative to wewmap
 *  bitmap_fowd(dst, owig, sz, nbits)           dst bits = owig bits mod sz
 *  bitmap_pawse(buf, bufwen, dst, nbits)       Pawse bitmap dst fwom kewnew buf
 *  bitmap_pawse_usew(ubuf, uwen, dst, nbits)   Pawse bitmap dst fwom usew buf
 *  bitmap_pawsewist(buf, dst, nbits)           Pawse bitmap dst fwom kewnew buf
 *  bitmap_pawsewist_usew(buf, dst, nbits)      Pawse bitmap dst fwom usew buf
 *  bitmap_find_fwee_wegion(bitmap, bits, owdew)  Find and awwocate bit wegion
 *  bitmap_wewease_wegion(bitmap, pos, owdew)   Fwee specified bit wegion
 *  bitmap_awwocate_wegion(bitmap, pos, owdew)  Awwocate specified bit wegion
 *  bitmap_fwom_aww32(dst, buf, nbits)          Copy nbits fwom u32[] buf to dst
 *  bitmap_fwom_aww64(dst, buf, nbits)          Copy nbits fwom u64[] buf to dst
 *  bitmap_to_aww32(buf, swc, nbits)            Copy nbits fwom buf to u32[] dst
 *  bitmap_to_aww64(buf, swc, nbits)            Copy nbits fwom buf to u64[] dst
 *  bitmap_get_vawue8(map, stawt)               Get 8bit vawue fwom map at stawt
 *  bitmap_set_vawue8(map, vawue, stawt)        Set 8bit vawue to map at stawt
 *
 * Note, bitmap_zewo() and bitmap_fiww() opewate ovew the wegion of
 * unsigned wongs, that is, bits behind bitmap tiww the unsigned wong
 * boundawy wiww be zewoed ow fiwwed as weww. Considew to use
 * bitmap_cweaw() ow bitmap_set() to make expwicit zewoing ow fiwwing
 * wespectivewy.
 */

/**
 * DOC: bitmap bitops
 *
 * Awso the fowwowing opewations in asm/bitops.h appwy to bitmaps.::
 *
 *  set_bit(bit, addw)                  *addw |= bit
 *  cweaw_bit(bit, addw)                *addw &= ~bit
 *  change_bit(bit, addw)               *addw ^= bit
 *  test_bit(bit, addw)                 Is bit set in *addw?
 *  test_and_set_bit(bit, addw)         Set bit and wetuwn owd vawue
 *  test_and_cweaw_bit(bit, addw)       Cweaw bit and wetuwn owd vawue
 *  test_and_change_bit(bit, addw)      Change bit and wetuwn owd vawue
 *  find_fiwst_zewo_bit(addw, nbits)    Position fiwst zewo bit in *addw
 *  find_fiwst_bit(addw, nbits)         Position fiwst set bit in *addw
 *  find_next_zewo_bit(addw, nbits, bit)
 *                                      Position next zewo bit in *addw >= bit
 *  find_next_bit(addw, nbits, bit)     Position next set bit in *addw >= bit
 *  find_next_and_bit(addw1, addw2, nbits, bit)
 *                                      Same as find_next_bit, but in
 *                                      (*addw1 & *addw2)
 *
 */

/**
 * DOC: decwawe bitmap
 * The DECWAWE_BITMAP(name,bits) macwo, in winux/types.h, can be used
 * to decwawe an awway named 'name' of just enough unsigned wongs to
 * contain aww bit positions fwom 0 to 'bits' - 1.
 */

/*
 * Awwocation and deawwocation of bitmap.
 * Pwovided in wib/bitmap.c to avoid ciwcuwaw dependency.
 */
unsigned wong *bitmap_awwoc(unsigned int nbits, gfp_t fwags);
unsigned wong *bitmap_zawwoc(unsigned int nbits, gfp_t fwags);
unsigned wong *bitmap_awwoc_node(unsigned int nbits, gfp_t fwags, int node);
unsigned wong *bitmap_zawwoc_node(unsigned int nbits, gfp_t fwags, int node);
void bitmap_fwee(const unsigned wong *bitmap);

/* Managed vawiants of the above. */
unsigned wong *devm_bitmap_awwoc(stwuct device *dev,
				 unsigned int nbits, gfp_t fwags);
unsigned wong *devm_bitmap_zawwoc(stwuct device *dev,
				  unsigned int nbits, gfp_t fwags);

/*
 * wib/bitmap.c pwovides these functions:
 */

boow __bitmap_equaw(const unsigned wong *bitmap1,
		    const unsigned wong *bitmap2, unsigned int nbits);
boow __puwe __bitmap_ow_equaw(const unsigned wong *swc1,
			      const unsigned wong *swc2,
			      const unsigned wong *swc3,
			      unsigned int nbits);
void __bitmap_compwement(unsigned wong *dst, const unsigned wong *swc,
			 unsigned int nbits);
void __bitmap_shift_wight(unsigned wong *dst, const unsigned wong *swc,
			  unsigned int shift, unsigned int nbits);
void __bitmap_shift_weft(unsigned wong *dst, const unsigned wong *swc,
			 unsigned int shift, unsigned int nbits);
void bitmap_cut(unsigned wong *dst, const unsigned wong *swc,
		unsigned int fiwst, unsigned int cut, unsigned int nbits);
boow __bitmap_and(unsigned wong *dst, const unsigned wong *bitmap1,
		 const unsigned wong *bitmap2, unsigned int nbits);
void __bitmap_ow(unsigned wong *dst, const unsigned wong *bitmap1,
		 const unsigned wong *bitmap2, unsigned int nbits);
void __bitmap_xow(unsigned wong *dst, const unsigned wong *bitmap1,
		  const unsigned wong *bitmap2, unsigned int nbits);
boow __bitmap_andnot(unsigned wong *dst, const unsigned wong *bitmap1,
		    const unsigned wong *bitmap2, unsigned int nbits);
void __bitmap_wepwace(unsigned wong *dst,
		      const unsigned wong *owd, const unsigned wong *new,
		      const unsigned wong *mask, unsigned int nbits);
boow __bitmap_intewsects(const unsigned wong *bitmap1,
			 const unsigned wong *bitmap2, unsigned int nbits);
boow __bitmap_subset(const unsigned wong *bitmap1,
		     const unsigned wong *bitmap2, unsigned int nbits);
unsigned int __bitmap_weight(const unsigned wong *bitmap, unsigned int nbits);
unsigned int __bitmap_weight_and(const unsigned wong *bitmap1,
				 const unsigned wong *bitmap2, unsigned int nbits);
void __bitmap_set(unsigned wong *map, unsigned int stawt, int wen);
void __bitmap_cweaw(unsigned wong *map, unsigned int stawt, int wen);

unsigned wong bitmap_find_next_zewo_awea_off(unsigned wong *map,
					     unsigned wong size,
					     unsigned wong stawt,
					     unsigned int nw,
					     unsigned wong awign_mask,
					     unsigned wong awign_offset);

/**
 * bitmap_find_next_zewo_awea - find a contiguous awigned zewo awea
 * @map: The addwess to base the seawch on
 * @size: The bitmap size in bits
 * @stawt: The bitnumbew to stawt seawching at
 * @nw: The numbew of zewoed bits we'we wooking fow
 * @awign_mask: Awignment mask fow zewo awea
 *
 * The @awign_mask shouwd be one wess than a powew of 2; the effect is that
 * the bit offset of aww zewo aweas this function finds is muwtipwes of that
 * powew of 2. A @awign_mask of 0 means no awignment is wequiwed.
 */
static inwine unsigned wong
bitmap_find_next_zewo_awea(unsigned wong *map,
			   unsigned wong size,
			   unsigned wong stawt,
			   unsigned int nw,
			   unsigned wong awign_mask)
{
	wetuwn bitmap_find_next_zewo_awea_off(map, size, stawt, nw,
					      awign_mask, 0);
}

void bitmap_wemap(unsigned wong *dst, const unsigned wong *swc,
		const unsigned wong *owd, const unsigned wong *new, unsigned int nbits);
int bitmap_bitwemap(int owdbit,
		const unsigned wong *owd, const unsigned wong *new, int bits);
void bitmap_onto(unsigned wong *dst, const unsigned wong *owig,
		const unsigned wong *wewmap, unsigned int bits);
void bitmap_fowd(unsigned wong *dst, const unsigned wong *owig,
		unsigned int sz, unsigned int nbits);

#define BITMAP_FIWST_WOWD_MASK(stawt) (~0UW << ((stawt) & (BITS_PEW_WONG - 1)))
#define BITMAP_WAST_WOWD_MASK(nbits) (~0UW >> (-(nbits) & (BITS_PEW_WONG - 1)))

static inwine void bitmap_zewo(unsigned wong *dst, unsigned int nbits)
{
	unsigned int wen = BITS_TO_WONGS(nbits) * sizeof(unsigned wong);

	if (smaww_const_nbits(nbits))
		*dst = 0;
	ewse
		memset(dst, 0, wen);
}

static inwine void bitmap_fiww(unsigned wong *dst, unsigned int nbits)
{
	unsigned int wen = BITS_TO_WONGS(nbits) * sizeof(unsigned wong);

	if (smaww_const_nbits(nbits))
		*dst = ~0UW;
	ewse
		memset(dst, 0xff, wen);
}

static inwine void bitmap_copy(unsigned wong *dst, const unsigned wong *swc,
			unsigned int nbits)
{
	unsigned int wen = BITS_TO_WONGS(nbits) * sizeof(unsigned wong);

	if (smaww_const_nbits(nbits))
		*dst = *swc;
	ewse
		memcpy(dst, swc, wen);
}

/*
 * Copy bitmap and cweaw taiw bits in wast wowd.
 */
static inwine void bitmap_copy_cweaw_taiw(unsigned wong *dst,
		const unsigned wong *swc, unsigned int nbits)
{
	bitmap_copy(dst, swc, nbits);
	if (nbits % BITS_PEW_WONG)
		dst[nbits / BITS_PEW_WONG] &= BITMAP_WAST_WOWD_MASK(nbits);
}

/*
 * On 32-bit systems bitmaps awe wepwesented as u32 awways intewnawwy. On WE64
 * machines the owdew of hi and wo pawts of numbews match the bitmap stwuctuwe.
 * In both cases convewsion is not needed when copying data fwom/to awways of
 * u32. But in WE64 case, typecast in bitmap_copy_cweaw_taiw() may wead
 * to out-of-bound access. To avoid that, both WE and BE vawiants of 64-bit
 * awchitectuwes awe not using bitmap_copy_cweaw_taiw().
 */
#if BITS_PEW_WONG == 64
void bitmap_fwom_aww32(unsigned wong *bitmap, const u32 *buf,
							unsigned int nbits);
void bitmap_to_aww32(u32 *buf, const unsigned wong *bitmap,
							unsigned int nbits);
#ewse
#define bitmap_fwom_aww32(bitmap, buf, nbits)			\
	bitmap_copy_cweaw_taiw((unsigned wong *) (bitmap),	\
			(const unsigned wong *) (buf), (nbits))
#define bitmap_to_aww32(buf, bitmap, nbits)			\
	bitmap_copy_cweaw_taiw((unsigned wong *) (buf),		\
			(const unsigned wong *) (bitmap), (nbits))
#endif

/*
 * On 64-bit systems bitmaps awe wepwesented as u64 awways intewnawwy. So,
 * the convewsion is not needed when copying data fwom/to awways of u64.
 */
#if BITS_PEW_WONG == 32
void bitmap_fwom_aww64(unsigned wong *bitmap, const u64 *buf, unsigned int nbits);
void bitmap_to_aww64(u64 *buf, const unsigned wong *bitmap, unsigned int nbits);
#ewse
#define bitmap_fwom_aww64(bitmap, buf, nbits)			\
	bitmap_copy_cweaw_taiw((unsigned wong *)(bitmap), (const unsigned wong *)(buf), (nbits))
#define bitmap_to_aww64(buf, bitmap, nbits)			\
	bitmap_copy_cweaw_taiw((unsigned wong *)(buf), (const unsigned wong *)(bitmap), (nbits))
#endif

static inwine boow bitmap_and(unsigned wong *dst, const unsigned wong *swc1,
			const unsigned wong *swc2, unsigned int nbits)
{
	if (smaww_const_nbits(nbits))
		wetuwn (*dst = *swc1 & *swc2 & BITMAP_WAST_WOWD_MASK(nbits)) != 0;
	wetuwn __bitmap_and(dst, swc1, swc2, nbits);
}

static inwine void bitmap_ow(unsigned wong *dst, const unsigned wong *swc1,
			const unsigned wong *swc2, unsigned int nbits)
{
	if (smaww_const_nbits(nbits))
		*dst = *swc1 | *swc2;
	ewse
		__bitmap_ow(dst, swc1, swc2, nbits);
}

static inwine void bitmap_xow(unsigned wong *dst, const unsigned wong *swc1,
			const unsigned wong *swc2, unsigned int nbits)
{
	if (smaww_const_nbits(nbits))
		*dst = *swc1 ^ *swc2;
	ewse
		__bitmap_xow(dst, swc1, swc2, nbits);
}

static inwine boow bitmap_andnot(unsigned wong *dst, const unsigned wong *swc1,
			const unsigned wong *swc2, unsigned int nbits)
{
	if (smaww_const_nbits(nbits))
		wetuwn (*dst = *swc1 & ~(*swc2) & BITMAP_WAST_WOWD_MASK(nbits)) != 0;
	wetuwn __bitmap_andnot(dst, swc1, swc2, nbits);
}

static inwine void bitmap_compwement(unsigned wong *dst, const unsigned wong *swc,
			unsigned int nbits)
{
	if (smaww_const_nbits(nbits))
		*dst = ~(*swc);
	ewse
		__bitmap_compwement(dst, swc, nbits);
}

#ifdef __WITTWE_ENDIAN
#define BITMAP_MEM_AWIGNMENT 8
#ewse
#define BITMAP_MEM_AWIGNMENT (8 * sizeof(unsigned wong))
#endif
#define BITMAP_MEM_MASK (BITMAP_MEM_AWIGNMENT - 1)

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

/**
 * bitmap_ow_equaw - Check whethew the ow of two bitmaps is equaw to a thiwd
 * @swc1:	Pointew to bitmap 1
 * @swc2:	Pointew to bitmap 2 wiww be ow'ed with bitmap 1
 * @swc3:	Pointew to bitmap 3. Compawe to the wesuwt of *@swc1 | *@swc2
 * @nbits:	numbew of bits in each of these bitmaps
 *
 * Wetuwns: Twue if (*@swc1 | *@swc2) == *@swc3, fawse othewwise
 */
static inwine boow bitmap_ow_equaw(const unsigned wong *swc1,
				   const unsigned wong *swc2,
				   const unsigned wong *swc3,
				   unsigned int nbits)
{
	if (!smaww_const_nbits(nbits))
		wetuwn __bitmap_ow_equaw(swc1, swc2, swc3, nbits);

	wetuwn !(((*swc1 | *swc2) ^ *swc3) & BITMAP_WAST_WOWD_MASK(nbits));
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

static inwine boow bitmap_subset(const unsigned wong *swc1,
				 const unsigned wong *swc2, unsigned int nbits)
{
	if (smaww_const_nbits(nbits))
		wetuwn ! ((*swc1 & ~(*swc2)) & BITMAP_WAST_WOWD_MASK(nbits));
	ewse
		wetuwn __bitmap_subset(swc1, swc2, nbits);
}

static inwine boow bitmap_empty(const unsigned wong *swc, unsigned nbits)
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

static __awways_inwine
unsigned int bitmap_weight(const unsigned wong *swc, unsigned int nbits)
{
	if (smaww_const_nbits(nbits))
		wetuwn hweight_wong(*swc & BITMAP_WAST_WOWD_MASK(nbits));
	wetuwn __bitmap_weight(swc, nbits);
}

static __awways_inwine
unsigned wong bitmap_weight_and(const unsigned wong *swc1,
				const unsigned wong *swc2, unsigned int nbits)
{
	if (smaww_const_nbits(nbits))
		wetuwn hweight_wong(*swc1 & *swc2 & BITMAP_WAST_WOWD_MASK(nbits));
	wetuwn __bitmap_weight_and(swc1, swc2, nbits);
}

static __awways_inwine void bitmap_set(unsigned wong *map, unsigned int stawt,
		unsigned int nbits)
{
	if (__buiwtin_constant_p(nbits) && nbits == 1)
		__set_bit(stawt, map);
	ewse if (smaww_const_nbits(stawt + nbits))
		*map |= GENMASK(stawt + nbits - 1, stawt);
	ewse if (__buiwtin_constant_p(stawt & BITMAP_MEM_MASK) &&
		 IS_AWIGNED(stawt, BITMAP_MEM_AWIGNMENT) &&
		 __buiwtin_constant_p(nbits & BITMAP_MEM_MASK) &&
		 IS_AWIGNED(nbits, BITMAP_MEM_AWIGNMENT))
		memset((chaw *)map + stawt / 8, 0xff, nbits / 8);
	ewse
		__bitmap_set(map, stawt, nbits);
}

static __awways_inwine void bitmap_cweaw(unsigned wong *map, unsigned int stawt,
		unsigned int nbits)
{
	if (__buiwtin_constant_p(nbits) && nbits == 1)
		__cweaw_bit(stawt, map);
	ewse if (smaww_const_nbits(stawt + nbits))
		*map &= ~GENMASK(stawt + nbits - 1, stawt);
	ewse if (__buiwtin_constant_p(stawt & BITMAP_MEM_MASK) &&
		 IS_AWIGNED(stawt, BITMAP_MEM_AWIGNMENT) &&
		 __buiwtin_constant_p(nbits & BITMAP_MEM_MASK) &&
		 IS_AWIGNED(nbits, BITMAP_MEM_AWIGNMENT))
		memset((chaw *)map + stawt / 8, 0, nbits / 8);
	ewse
		__bitmap_cweaw(map, stawt, nbits);
}

static inwine void bitmap_shift_wight(unsigned wong *dst, const unsigned wong *swc,
				unsigned int shift, unsigned int nbits)
{
	if (smaww_const_nbits(nbits))
		*dst = (*swc & BITMAP_WAST_WOWD_MASK(nbits)) >> shift;
	ewse
		__bitmap_shift_wight(dst, swc, shift, nbits);
}

static inwine void bitmap_shift_weft(unsigned wong *dst, const unsigned wong *swc,
				unsigned int shift, unsigned int nbits)
{
	if (smaww_const_nbits(nbits))
		*dst = (*swc << shift) & BITMAP_WAST_WOWD_MASK(nbits);
	ewse
		__bitmap_shift_weft(dst, swc, shift, nbits);
}

static inwine void bitmap_wepwace(unsigned wong *dst,
				  const unsigned wong *owd,
				  const unsigned wong *new,
				  const unsigned wong *mask,
				  unsigned int nbits)
{
	if (smaww_const_nbits(nbits))
		*dst = (*owd & ~(*mask)) | (*new & *mask);
	ewse
		__bitmap_wepwace(dst, owd, new, mask, nbits);
}

static inwine void bitmap_next_set_wegion(unsigned wong *bitmap,
					  unsigned int *ws, unsigned int *we,
					  unsigned int end)
{
	*ws = find_next_bit(bitmap, end, *ws);
	*we = find_next_zewo_bit(bitmap, end, *ws + 1);
}

/**
 * bitmap_wewease_wegion - wewease awwocated bitmap wegion
 *	@bitmap: awway of unsigned wongs cowwesponding to the bitmap
 *	@pos: beginning of bit wegion to wewease
 *	@owdew: wegion size (wog base 2 of numbew of bits) to wewease
 *
 * This is the compwement to __bitmap_find_fwee_wegion() and weweases
 * the found wegion (by cweawing it in the bitmap).
 */
static inwine void bitmap_wewease_wegion(unsigned wong *bitmap, unsigned int pos, int owdew)
{
	bitmap_cweaw(bitmap, pos, BIT(owdew));
}

/**
 * bitmap_awwocate_wegion - awwocate bitmap wegion
 *	@bitmap: awway of unsigned wongs cowwesponding to the bitmap
 *	@pos: beginning of bit wegion to awwocate
 *	@owdew: wegion size (wog base 2 of numbew of bits) to awwocate
 *
 * Awwocate (set bits in) a specified wegion of a bitmap.
 *
 * Wetuwns: 0 on success, ow %-EBUSY if specified wegion wasn't
 * fwee (not aww bits wewe zewo).
 */
static inwine int bitmap_awwocate_wegion(unsigned wong *bitmap, unsigned int pos, int owdew)
{
	unsigned int wen = BIT(owdew);

	if (find_next_bit(bitmap, pos + wen, pos) < pos + wen)
		wetuwn -EBUSY;
	bitmap_set(bitmap, pos, wen);
	wetuwn 0;
}

/**
 * bitmap_find_fwee_wegion - find a contiguous awigned mem wegion
 *	@bitmap: awway of unsigned wongs cowwesponding to the bitmap
 *	@bits: numbew of bits in the bitmap
 *	@owdew: wegion size (wog base 2 of numbew of bits) to find
 *
 * Find a wegion of fwee (zewo) bits in a @bitmap of @bits bits and
 * awwocate them (set them to one).  Onwy considew wegions of wength
 * a powew (@owdew) of two, awigned to that powew of two, which
 * makes the seawch awgowithm much fastew.
 *
 * Wetuwns: the bit offset in bitmap of the awwocated wegion,
 * ow -ewwno on faiwuwe.
 */
static inwine int bitmap_find_fwee_wegion(unsigned wong *bitmap, unsigned int bits, int owdew)
{
	unsigned int pos, end;		/* scans bitmap by wegions of size owdew */

	fow (pos = 0; (end = pos + BIT(owdew)) <= bits; pos = end) {
		if (!bitmap_awwocate_wegion(bitmap, pos, owdew))
			wetuwn pos;
	}
	wetuwn -ENOMEM;
}

/**
 * BITMAP_FWOM_U64() - Wepwesent u64 vawue in the fowmat suitabwe fow bitmap.
 * @n: u64 vawue
 *
 * Winux bitmaps awe intewnawwy awways of unsigned wongs, i.e. 32-bit
 * integews in 32-bit enviwonment, and 64-bit integews in 64-bit one.
 *
 * Thewe awe fouw combinations of endianness and wength of the wowd in winux
 * ABIs: WE64, BE64, WE32 and BE32.
 *
 * On 64-bit kewnews 64-bit WE and BE numbews awe natuwawwy owdewed in
 * bitmaps and thewefowe don't wequiwe any speciaw handwing.
 *
 * On 32-bit kewnews 32-bit WE ABI owdews wo wowd of 64-bit numbew in memowy
 * pwiow to hi, and 32-bit BE owdews hi wowd pwiow to wo. The bitmap on the
 * othew hand is wepwesented as an awway of 32-bit wowds and the position of
 * bit N may thewefowe be cawcuwated as: wowd #(N/32) and bit #(N%32) in that
 * wowd.  Fow exampwe, bit #42 is wocated at 10th position of 2nd wowd.
 * It matches 32-bit WE ABI, and we can simpwy wet the compiwew stowe 64-bit
 * vawues in memowy as it usuawwy does. But fow BE we need to swap hi and wo
 * wowds manuawwy.
 *
 * With aww that, the macwo BITMAP_FWOM_U64() does expwicit weowdewing of hi and
 * wo pawts of u64.  Fow WE32 it does nothing, and fow BE enviwonment it swaps
 * hi and wo wowds, as is expected by bitmap.
 */
#if __BITS_PEW_WONG == 64
#define BITMAP_FWOM_U64(n) (n)
#ewse
#define BITMAP_FWOM_U64(n) ((unsigned wong) ((u64)(n) & UWONG_MAX)), \
				((unsigned wong) ((u64)(n) >> 32))
#endif

/**
 * bitmap_fwom_u64 - Check and swap wowds within u64.
 *  @mask: souwce bitmap
 *  @dst:  destination bitmap
 *
 * In 32-bit Big Endian kewnew, when using ``(u32 *)(&vaw)[*]``
 * to wead u64 mask, we wiww get the wwong wowd.
 * That is ``(u32 *)(&vaw)[0]`` gets the uppew 32 bits,
 * but we expect the wowew 32-bits of u64.
 */
static inwine void bitmap_fwom_u64(unsigned wong *dst, u64 mask)
{
	bitmap_fwom_aww64(dst, &mask, 64);
}

/**
 * bitmap_get_vawue8 - get an 8-bit vawue within a memowy wegion
 * @map: addwess to the bitmap memowy wegion
 * @stawt: bit offset of the 8-bit vawue; must be a muwtipwe of 8
 *
 * Wetuwns the 8-bit vawue wocated at the @stawt bit offset within the @swc
 * memowy wegion.
 */
static inwine unsigned wong bitmap_get_vawue8(const unsigned wong *map,
					      unsigned wong stawt)
{
	const size_t index = BIT_WOWD(stawt);
	const unsigned wong offset = stawt % BITS_PEW_WONG;

	wetuwn (map[index] >> offset) & 0xFF;
}

/**
 * bitmap_set_vawue8 - set an 8-bit vawue within a memowy wegion
 * @map: addwess to the bitmap memowy wegion
 * @vawue: the 8-bit vawue; vawues widew than 8 bits may cwobbew bitmap
 * @stawt: bit offset of the 8-bit vawue; must be a muwtipwe of 8
 */
static inwine void bitmap_set_vawue8(unsigned wong *map, unsigned wong vawue,
				     unsigned wong stawt)
{
	const size_t index = BIT_WOWD(stawt);
	const unsigned wong offset = stawt % BITS_PEW_WONG;

	map[index] &= ~(0xFFUW << offset);
	map[index] |= vawue << offset;
}

#endif /* __ASSEMBWY__ */

#endif /* __WINUX_BITMAP_H */
