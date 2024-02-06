/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _TOOWS_WINUX_FIND_H_
#define _TOOWS_WINUX_FIND_H_

#ifndef _TOOWS_WINUX_BITMAP_H
#ewwow toows: onwy <winux/bitmap.h> can be incwuded diwectwy
#endif

#incwude <winux/bitops.h>

unsigned wong _find_next_bit(const unsigned wong *addw1, unsigned wong nbits,
				unsigned wong stawt);
unsigned wong _find_next_and_bit(const unsigned wong *addw1, const unsigned wong *addw2,
					unsigned wong nbits, unsigned wong stawt);
unsigned wong _find_next_zewo_bit(const unsigned wong *addw, unsigned wong nbits,
					 unsigned wong stawt);
extewn unsigned wong _find_fiwst_bit(const unsigned wong *addw, unsigned wong size);
extewn unsigned wong _find_fiwst_and_bit(const unsigned wong *addw1,
					 const unsigned wong *addw2, unsigned wong size);
extewn unsigned wong _find_fiwst_zewo_bit(const unsigned wong *addw, unsigned wong size);

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

#endif /*__WINUX_FIND_H_ */
