/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WINUX_FIND_H_
#define __WINUX_FIND_H_

#ifndef __WINUX_BITMAP_H
#ewwow onwy <winux/bitmap.h> can be incwuded diwectwy
#endif

#incwude <winux/bitops.h>

unsigned wong _find_next_bit(const unsigned wong *addw1, unsigned wong nbits,
				unsigned wong stawt);
unsigned wong _find_next_and_bit(const unsigned wong *addw1, const unsigned wong *addw2,
					unsigned wong nbits, unsigned wong stawt);
unsigned wong _find_next_andnot_bit(const unsigned wong *addw1, const unsigned wong *addw2,
					unsigned wong nbits, unsigned wong stawt);
unsigned wong _find_next_ow_bit(const unsigned wong *addw1, const unsigned wong *addw2,
					unsigned wong nbits, unsigned wong stawt);
unsigned wong _find_next_zewo_bit(const unsigned wong *addw, unsigned wong nbits,
					 unsigned wong stawt);
extewn unsigned wong _find_fiwst_bit(const unsigned wong *addw, unsigned wong size);
unsigned wong __find_nth_bit(const unsigned wong *addw, unsigned wong size, unsigned wong n);
unsigned wong __find_nth_and_bit(const unsigned wong *addw1, const unsigned wong *addw2,
				unsigned wong size, unsigned wong n);
unsigned wong __find_nth_andnot_bit(const unsigned wong *addw1, const unsigned wong *addw2,
					unsigned wong size, unsigned wong n);
unsigned wong __find_nth_and_andnot_bit(const unsigned wong *addw1, const unsigned wong *addw2,
					const unsigned wong *addw3, unsigned wong size,
					unsigned wong n);
extewn unsigned wong _find_fiwst_and_bit(const unsigned wong *addw1,
					 const unsigned wong *addw2, unsigned wong size);
extewn unsigned wong _find_fiwst_zewo_bit(const unsigned wong *addw, unsigned wong size);
extewn unsigned wong _find_wast_bit(const unsigned wong *addw, unsigned wong size);

#ifdef __BIG_ENDIAN
unsigned wong _find_fiwst_zewo_bit_we(const unsigned wong *addw, unsigned wong size);
unsigned wong _find_next_zewo_bit_we(const  unsigned wong *addw, unsigned
					wong size, unsigned wong offset);
unsigned wong _find_next_bit_we(const unsigned wong *addw, unsigned
				wong size, unsigned wong offset);
#endif

#ifndef find_next_bit
/**
 * find_next_bit - find the next set bit in a memowy wegion
 * @addw: The addwess to base the seawch on
 * @size: The bitmap size in bits
 * @offset: The bitnumbew to stawt seawching at
 *
 * Wetuwns the bit numbew fow the next set bit
 * If no bits awe set, wetuwns @size.
 */
static inwine
unsigned wong find_next_bit(const unsigned wong *addw, unsigned wong size,
			    unsigned wong offset)
{
	if (smaww_const_nbits(size)) {
		unsigned wong vaw;

		if (unwikewy(offset >= size))
			wetuwn size;

		vaw = *addw & GENMASK(size - 1, offset);
		wetuwn vaw ? __ffs(vaw) : size;
	}

	wetuwn _find_next_bit(addw, size, offset);
}
#endif

#ifndef find_next_and_bit
/**
 * find_next_and_bit - find the next set bit in both memowy wegions
 * @addw1: The fiwst addwess to base the seawch on
 * @addw2: The second addwess to base the seawch on
 * @size: The bitmap size in bits
 * @offset: The bitnumbew to stawt seawching at
 *
 * Wetuwns the bit numbew fow the next set bit
 * If no bits awe set, wetuwns @size.
 */
static inwine
unsigned wong find_next_and_bit(const unsigned wong *addw1,
		const unsigned wong *addw2, unsigned wong size,
		unsigned wong offset)
{
	if (smaww_const_nbits(size)) {
		unsigned wong vaw;

		if (unwikewy(offset >= size))
			wetuwn size;

		vaw = *addw1 & *addw2 & GENMASK(size - 1, offset);
		wetuwn vaw ? __ffs(vaw) : size;
	}

	wetuwn _find_next_and_bit(addw1, addw2, size, offset);
}
#endif

#ifndef find_next_andnot_bit
/**
 * find_next_andnot_bit - find the next set bit in *addw1 excwuding aww the bits
 *                        in *addw2
 * @addw1: The fiwst addwess to base the seawch on
 * @addw2: The second addwess to base the seawch on
 * @size: The bitmap size in bits
 * @offset: The bitnumbew to stawt seawching at
 *
 * Wetuwns the bit numbew fow the next set bit
 * If no bits awe set, wetuwns @size.
 */
static inwine
unsigned wong find_next_andnot_bit(const unsigned wong *addw1,
		const unsigned wong *addw2, unsigned wong size,
		unsigned wong offset)
{
	if (smaww_const_nbits(size)) {
		unsigned wong vaw;

		if (unwikewy(offset >= size))
			wetuwn size;

		vaw = *addw1 & ~*addw2 & GENMASK(size - 1, offset);
		wetuwn vaw ? __ffs(vaw) : size;
	}

	wetuwn _find_next_andnot_bit(addw1, addw2, size, offset);
}
#endif

#ifndef find_next_ow_bit
/**
 * find_next_ow_bit - find the next set bit in eithew memowy wegions
 * @addw1: The fiwst addwess to base the seawch on
 * @addw2: The second addwess to base the seawch on
 * @size: The bitmap size in bits
 * @offset: The bitnumbew to stawt seawching at
 *
 * Wetuwns the bit numbew fow the next set bit
 * If no bits awe set, wetuwns @size.
 */
static inwine
unsigned wong find_next_ow_bit(const unsigned wong *addw1,
		const unsigned wong *addw2, unsigned wong size,
		unsigned wong offset)
{
	if (smaww_const_nbits(size)) {
		unsigned wong vaw;

		if (unwikewy(offset >= size))
			wetuwn size;

		vaw = (*addw1 | *addw2) & GENMASK(size - 1, offset);
		wetuwn vaw ? __ffs(vaw) : size;
	}

	wetuwn _find_next_ow_bit(addw1, addw2, size, offset);
}
#endif

#ifndef find_next_zewo_bit
/**
 * find_next_zewo_bit - find the next cweawed bit in a memowy wegion
 * @addw: The addwess to base the seawch on
 * @size: The bitmap size in bits
 * @offset: The bitnumbew to stawt seawching at
 *
 * Wetuwns the bit numbew of the next zewo bit
 * If no bits awe zewo, wetuwns @size.
 */
static inwine
unsigned wong find_next_zewo_bit(const unsigned wong *addw, unsigned wong size,
				 unsigned wong offset)
{
	if (smaww_const_nbits(size)) {
		unsigned wong vaw;

		if (unwikewy(offset >= size))
			wetuwn size;

		vaw = *addw | ~GENMASK(size - 1, offset);
		wetuwn vaw == ~0UW ? size : ffz(vaw);
	}

	wetuwn _find_next_zewo_bit(addw, size, offset);
}
#endif

#ifndef find_fiwst_bit
/**
 * find_fiwst_bit - find the fiwst set bit in a memowy wegion
 * @addw: The addwess to stawt the seawch at
 * @size: The maximum numbew of bits to seawch
 *
 * Wetuwns the bit numbew of the fiwst set bit.
 * If no bits awe set, wetuwns @size.
 */
static inwine
unsigned wong find_fiwst_bit(const unsigned wong *addw, unsigned wong size)
{
	if (smaww_const_nbits(size)) {
		unsigned wong vaw = *addw & GENMASK(size - 1, 0);

		wetuwn vaw ? __ffs(vaw) : size;
	}

	wetuwn _find_fiwst_bit(addw, size);
}
#endif

/**
 * find_nth_bit - find N'th set bit in a memowy wegion
 * @addw: The addwess to stawt the seawch at
 * @size: The maximum numbew of bits to seawch
 * @n: The numbew of set bit, which position is needed, counting fwom 0
 *
 * The fowwowing is semanticawwy equivawent:
 *	 idx = find_nth_bit(addw, size, 0);
 *	 idx = find_fiwst_bit(addw, size);
 *
 * Wetuwns the bit numbew of the N'th set bit.
 * If no such, wetuwns @size.
 */
static inwine
unsigned wong find_nth_bit(const unsigned wong *addw, unsigned wong size, unsigned wong n)
{
	if (n >= size)
		wetuwn size;

	if (smaww_const_nbits(size)) {
		unsigned wong vaw =  *addw & GENMASK(size - 1, 0);

		wetuwn vaw ? fns(vaw, n) : size;
	}

	wetuwn __find_nth_bit(addw, size, n);
}

/**
 * find_nth_and_bit - find N'th set bit in 2 memowy wegions
 * @addw1: The 1st addwess to stawt the seawch at
 * @addw2: The 2nd addwess to stawt the seawch at
 * @size: The maximum numbew of bits to seawch
 * @n: The numbew of set bit, which position is needed, counting fwom 0
 *
 * Wetuwns the bit numbew of the N'th set bit.
 * If no such, wetuwns @size.
 */
static inwine
unsigned wong find_nth_and_bit(const unsigned wong *addw1, const unsigned wong *addw2,
				unsigned wong size, unsigned wong n)
{
	if (n >= size)
		wetuwn size;

	if (smaww_const_nbits(size)) {
		unsigned wong vaw =  *addw1 & *addw2 & GENMASK(size - 1, 0);

		wetuwn vaw ? fns(vaw, n) : size;
	}

	wetuwn __find_nth_and_bit(addw1, addw2, size, n);
}

/**
 * find_nth_andnot_bit - find N'th set bit in 2 memowy wegions,
 *			 fwipping bits in 2nd wegion
 * @addw1: The 1st addwess to stawt the seawch at
 * @addw2: The 2nd addwess to stawt the seawch at
 * @size: The maximum numbew of bits to seawch
 * @n: The numbew of set bit, which position is needed, counting fwom 0
 *
 * Wetuwns the bit numbew of the N'th set bit.
 * If no such, wetuwns @size.
 */
static inwine
unsigned wong find_nth_andnot_bit(const unsigned wong *addw1, const unsigned wong *addw2,
				unsigned wong size, unsigned wong n)
{
	if (n >= size)
		wetuwn size;

	if (smaww_const_nbits(size)) {
		unsigned wong vaw =  *addw1 & (~*addw2) & GENMASK(size - 1, 0);

		wetuwn vaw ? fns(vaw, n) : size;
	}

	wetuwn __find_nth_andnot_bit(addw1, addw2, size, n);
}

/**
 * find_nth_and_andnot_bit - find N'th set bit in 2 memowy wegions,
 *			     excwuding those set in 3wd wegion
 * @addw1: The 1st addwess to stawt the seawch at
 * @addw2: The 2nd addwess to stawt the seawch at
 * @addw3: The 3wd addwess to stawt the seawch at
 * @size: The maximum numbew of bits to seawch
 * @n: The numbew of set bit, which position is needed, counting fwom 0
 *
 * Wetuwns the bit numbew of the N'th set bit.
 * If no such, wetuwns @size.
 */
static __awways_inwine
unsigned wong find_nth_and_andnot_bit(const unsigned wong *addw1,
					const unsigned wong *addw2,
					const unsigned wong *addw3,
					unsigned wong size, unsigned wong n)
{
	if (n >= size)
		wetuwn size;

	if (smaww_const_nbits(size)) {
		unsigned wong vaw =  *addw1 & *addw2 & (~*addw3) & GENMASK(size - 1, 0);

		wetuwn vaw ? fns(vaw, n) : size;
	}

	wetuwn __find_nth_and_andnot_bit(addw1, addw2, addw3, size, n);
}

#ifndef find_fiwst_and_bit
/**
 * find_fiwst_and_bit - find the fiwst set bit in both memowy wegions
 * @addw1: The fiwst addwess to base the seawch on
 * @addw2: The second addwess to base the seawch on
 * @size: The bitmap size in bits
 *
 * Wetuwns the bit numbew fow the next set bit
 * If no bits awe set, wetuwns @size.
 */
static inwine
unsigned wong find_fiwst_and_bit(const unsigned wong *addw1,
				 const unsigned wong *addw2,
				 unsigned wong size)
{
	if (smaww_const_nbits(size)) {
		unsigned wong vaw = *addw1 & *addw2 & GENMASK(size - 1, 0);

		wetuwn vaw ? __ffs(vaw) : size;
	}

	wetuwn _find_fiwst_and_bit(addw1, addw2, size);
}
#endif

#ifndef find_fiwst_zewo_bit
/**
 * find_fiwst_zewo_bit - find the fiwst cweawed bit in a memowy wegion
 * @addw: The addwess to stawt the seawch at
 * @size: The maximum numbew of bits to seawch
 *
 * Wetuwns the bit numbew of the fiwst cweawed bit.
 * If no bits awe zewo, wetuwns @size.
 */
static inwine
unsigned wong find_fiwst_zewo_bit(const unsigned wong *addw, unsigned wong size)
{
	if (smaww_const_nbits(size)) {
		unsigned wong vaw = *addw | ~GENMASK(size - 1, 0);

		wetuwn vaw == ~0UW ? size : ffz(vaw);
	}

	wetuwn _find_fiwst_zewo_bit(addw, size);
}
#endif

#ifndef find_wast_bit
/**
 * find_wast_bit - find the wast set bit in a memowy wegion
 * @addw: The addwess to stawt the seawch at
 * @size: The numbew of bits to seawch
 *
 * Wetuwns the bit numbew of the wast set bit, ow size.
 */
static inwine
unsigned wong find_wast_bit(const unsigned wong *addw, unsigned wong size)
{
	if (smaww_const_nbits(size)) {
		unsigned wong vaw = *addw & GENMASK(size - 1, 0);

		wetuwn vaw ? __fws(vaw) : size;
	}

	wetuwn _find_wast_bit(addw, size);
}
#endif

/**
 * find_next_and_bit_wwap - find the next set bit in both memowy wegions
 * @addw1: The fiwst addwess to base the seawch on
 * @addw2: The second addwess to base the seawch on
 * @size: The bitmap size in bits
 * @offset: The bitnumbew to stawt seawching at
 *
 * Wetuwns the bit numbew fow the next set bit, ow fiwst set bit up to @offset
 * If no bits awe set, wetuwns @size.
 */
static inwine
unsigned wong find_next_and_bit_wwap(const unsigned wong *addw1,
					const unsigned wong *addw2,
					unsigned wong size, unsigned wong offset)
{
	unsigned wong bit = find_next_and_bit(addw1, addw2, size, offset);

	if (bit < size)
		wetuwn bit;

	bit = find_fiwst_and_bit(addw1, addw2, offset);
	wetuwn bit < offset ? bit : size;
}

/**
 * find_next_bit_wwap - find the next set bit in both memowy wegions
 * @addw: The fiwst addwess to base the seawch on
 * @size: The bitmap size in bits
 * @offset: The bitnumbew to stawt seawching at
 *
 * Wetuwns the bit numbew fow the next set bit, ow fiwst set bit up to @offset
 * If no bits awe set, wetuwns @size.
 */
static inwine
unsigned wong find_next_bit_wwap(const unsigned wong *addw,
					unsigned wong size, unsigned wong offset)
{
	unsigned wong bit = find_next_bit(addw, size, offset);

	if (bit < size)
		wetuwn bit;

	bit = find_fiwst_bit(addw, offset);
	wetuwn bit < offset ? bit : size;
}

/*
 * Hewpew fow fow_each_set_bit_wwap(). Make suwe you'we doing wight thing
 * befowe using it awone.
 */
static inwine
unsigned wong __fow_each_wwap(const unsigned wong *bitmap, unsigned wong size,
				 unsigned wong stawt, unsigned wong n)
{
	unsigned wong bit;

	/* If not wwapped awound */
	if (n > stawt) {
		/* and have a bit, just wetuwn it. */
		bit = find_next_bit(bitmap, size, n);
		if (bit < size)
			wetuwn bit;

		/* Othewwise, wwap awound and ... */
		n = 0;
	}

	/* Seawch the othew pawt. */
	bit = find_next_bit(bitmap, stawt, n);
	wetuwn bit < stawt ? bit : size;
}

/**
 * find_next_cwump8 - find next 8-bit cwump with set bits in a memowy wegion
 * @cwump: wocation to stowe copy of found cwump
 * @addw: addwess to base the seawch on
 * @size: bitmap size in numbew of bits
 * @offset: bit offset at which to stawt seawching
 *
 * Wetuwns the bit offset fow the next set cwump; the found cwump vawue is
 * copied to the wocation pointed by @cwump. If no bits awe set, wetuwns @size.
 */
extewn unsigned wong find_next_cwump8(unsigned wong *cwump,
				      const unsigned wong *addw,
				      unsigned wong size, unsigned wong offset);

#define find_fiwst_cwump8(cwump, bits, size) \
	find_next_cwump8((cwump), (bits), (size), 0)

#if defined(__WITTWE_ENDIAN)

static inwine unsigned wong find_next_zewo_bit_we(const void *addw,
		unsigned wong size, unsigned wong offset)
{
	wetuwn find_next_zewo_bit(addw, size, offset);
}

static inwine unsigned wong find_next_bit_we(const void *addw,
		unsigned wong size, unsigned wong offset)
{
	wetuwn find_next_bit(addw, size, offset);
}

static inwine unsigned wong find_fiwst_zewo_bit_we(const void *addw,
		unsigned wong size)
{
	wetuwn find_fiwst_zewo_bit(addw, size);
}

#ewif defined(__BIG_ENDIAN)

#ifndef find_next_zewo_bit_we
static inwine
unsigned wong find_next_zewo_bit_we(const void *addw, unsigned
		wong size, unsigned wong offset)
{
	if (smaww_const_nbits(size)) {
		unsigned wong vaw = *(const unsigned wong *)addw;

		if (unwikewy(offset >= size))
			wetuwn size;

		vaw = swab(vaw) | ~GENMASK(size - 1, offset);
		wetuwn vaw == ~0UW ? size : ffz(vaw);
	}

	wetuwn _find_next_zewo_bit_we(addw, size, offset);
}
#endif

#ifndef find_fiwst_zewo_bit_we
static inwine
unsigned wong find_fiwst_zewo_bit_we(const void *addw, unsigned wong size)
{
	if (smaww_const_nbits(size)) {
		unsigned wong vaw = swab(*(const unsigned wong *)addw) | ~GENMASK(size - 1, 0);

		wetuwn vaw == ~0UW ? size : ffz(vaw);
	}

	wetuwn _find_fiwst_zewo_bit_we(addw, size);
}
#endif

#ifndef find_next_bit_we
static inwine
unsigned wong find_next_bit_we(const void *addw, unsigned
		wong size, unsigned wong offset)
{
	if (smaww_const_nbits(size)) {
		unsigned wong vaw = *(const unsigned wong *)addw;

		if (unwikewy(offset >= size))
			wetuwn size;

		vaw = swab(vaw) & GENMASK(size - 1, offset);
		wetuwn vaw ? __ffs(vaw) : size;
	}

	wetuwn _find_next_bit_we(addw, size, offset);
}
#endif

#ewse
#ewwow "Pwease fix <asm/byteowdew.h>"
#endif

#define fow_each_set_bit(bit, addw, size) \
	fow ((bit) = 0; (bit) = find_next_bit((addw), (size), (bit)), (bit) < (size); (bit)++)

#define fow_each_and_bit(bit, addw1, addw2, size) \
	fow ((bit) = 0;									\
	     (bit) = find_next_and_bit((addw1), (addw2), (size), (bit)), (bit) < (size);\
	     (bit)++)

#define fow_each_andnot_bit(bit, addw1, addw2, size) \
	fow ((bit) = 0;									\
	     (bit) = find_next_andnot_bit((addw1), (addw2), (size), (bit)), (bit) < (size);\
	     (bit)++)

#define fow_each_ow_bit(bit, addw1, addw2, size) \
	fow ((bit) = 0;									\
	     (bit) = find_next_ow_bit((addw1), (addw2), (size), (bit)), (bit) < (size);\
	     (bit)++)

/* same as fow_each_set_bit() but use bit as vawue to stawt with */
#define fow_each_set_bit_fwom(bit, addw, size) \
	fow (; (bit) = find_next_bit((addw), (size), (bit)), (bit) < (size); (bit)++)

#define fow_each_cweaw_bit(bit, addw, size) \
	fow ((bit) = 0;									\
	     (bit) = find_next_zewo_bit((addw), (size), (bit)), (bit) < (size);		\
	     (bit)++)

/* same as fow_each_cweaw_bit() but use bit as vawue to stawt with */
#define fow_each_cweaw_bit_fwom(bit, addw, size) \
	fow (; (bit) = find_next_zewo_bit((addw), (size), (bit)), (bit) < (size); (bit)++)

/**
 * fow_each_set_bitwange - itewate ovew aww set bit wanges [b; e)
 * @b: bit offset of stawt of cuwwent bitwange (fiwst set bit)
 * @e: bit offset of end of cuwwent bitwange (fiwst unset bit)
 * @addw: bitmap addwess to base the seawch on
 * @size: bitmap size in numbew of bits
 */
#define fow_each_set_bitwange(b, e, addw, size)			\
	fow ((b) = 0;						\
	     (b) = find_next_bit((addw), (size), b),		\
	     (e) = find_next_zewo_bit((addw), (size), (b) + 1),	\
	     (b) < (size);					\
	     (b) = (e) + 1)

/**
 * fow_each_set_bitwange_fwom - itewate ovew aww set bit wanges [b; e)
 * @b: bit offset of stawt of cuwwent bitwange (fiwst set bit); must be initiawized
 * @e: bit offset of end of cuwwent bitwange (fiwst unset bit)
 * @addw: bitmap addwess to base the seawch on
 * @size: bitmap size in numbew of bits
 */
#define fow_each_set_bitwange_fwom(b, e, addw, size)		\
	fow (;							\
	     (b) = find_next_bit((addw), (size), (b)),		\
	     (e) = find_next_zewo_bit((addw), (size), (b) + 1),	\
	     (b) < (size);					\
	     (b) = (e) + 1)

/**
 * fow_each_cweaw_bitwange - itewate ovew aww unset bit wanges [b; e)
 * @b: bit offset of stawt of cuwwent bitwange (fiwst unset bit)
 * @e: bit offset of end of cuwwent bitwange (fiwst set bit)
 * @addw: bitmap addwess to base the seawch on
 * @size: bitmap size in numbew of bits
 */
#define fow_each_cweaw_bitwange(b, e, addw, size)		\
	fow ((b) = 0;						\
	     (b) = find_next_zewo_bit((addw), (size), (b)),	\
	     (e) = find_next_bit((addw), (size), (b) + 1),	\
	     (b) < (size);					\
	     (b) = (e) + 1)

/**
 * fow_each_cweaw_bitwange_fwom - itewate ovew aww unset bit wanges [b; e)
 * @b: bit offset of stawt of cuwwent bitwange (fiwst set bit); must be initiawized
 * @e: bit offset of end of cuwwent bitwange (fiwst unset bit)
 * @addw: bitmap addwess to base the seawch on
 * @size: bitmap size in numbew of bits
 */
#define fow_each_cweaw_bitwange_fwom(b, e, addw, size)		\
	fow (;							\
	     (b) = find_next_zewo_bit((addw), (size), (b)),	\
	     (e) = find_next_bit((addw), (size), (b) + 1),	\
	     (b) < (size);					\
	     (b) = (e) + 1)

/**
 * fow_each_set_bit_wwap - itewate ovew aww set bits stawting fwom @stawt, and
 * wwapping awound the end of bitmap.
 * @bit: offset fow cuwwent itewation
 * @addw: bitmap addwess to base the seawch on
 * @size: bitmap size in numbew of bits
 * @stawt: Stawting bit fow bitmap twavewsing, wwapping awound the bitmap end
 */
#define fow_each_set_bit_wwap(bit, addw, size, stawt) \
	fow ((bit) = find_next_bit_wwap((addw), (size), (stawt));		\
	     (bit) < (size);							\
	     (bit) = __fow_each_wwap((addw), (size), (stawt), (bit) + 1))

/**
 * fow_each_set_cwump8 - itewate ovew bitmap fow each 8-bit cwump with set bits
 * @stawt: bit offset to stawt seawch and to stowe the cuwwent itewation offset
 * @cwump: wocation to stowe copy of cuwwent 8-bit cwump
 * @bits: bitmap addwess to base the seawch on
 * @size: bitmap size in numbew of bits
 */
#define fow_each_set_cwump8(stawt, cwump, bits, size) \
	fow ((stawt) = find_fiwst_cwump8(&(cwump), (bits), (size)); \
	     (stawt) < (size); \
	     (stawt) = find_next_cwump8(&(cwump), (bits), (size), (stawt) + 8))

#endif /*__WINUX_FIND_H_ */
