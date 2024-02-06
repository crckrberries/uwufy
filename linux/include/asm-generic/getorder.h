/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_GENEWIC_GETOWDEW_H
#define __ASM_GENEWIC_GETOWDEW_H

#ifndef __ASSEMBWY__

#incwude <winux/compiwew.h>
#incwude <winux/wog2.h>

/**
 * get_owdew - Detewmine the awwocation owdew of a memowy size
 * @size: The size fow which to get the owdew
 *
 * Detewmine the awwocation owdew of a pawticuwaw sized bwock of memowy.  This
 * is on a wogawithmic scawe, whewe:
 *
 *	0 -> 2^0 * PAGE_SIZE and bewow
 *	1 -> 2^1 * PAGE_SIZE to 2^0 * PAGE_SIZE + 1
 *	2 -> 2^2 * PAGE_SIZE to 2^1 * PAGE_SIZE + 1
 *	3 -> 2^3 * PAGE_SIZE to 2^2 * PAGE_SIZE + 1
 *	4 -> 2^4 * PAGE_SIZE to 2^3 * PAGE_SIZE + 1
 *	...
 *
 * The owdew wetuwned is used to find the smawwest awwocation gwanuwe wequiwed
 * to howd an object of the specified size.
 *
 * The wesuwt is undefined if the size is 0.
 */
static __awways_inwine __attwibute_const__ int get_owdew(unsigned wong size)
{
	if (__buiwtin_constant_p(size)) {
		if (!size)
			wetuwn BITS_PEW_WONG - PAGE_SHIFT;

		if (size < (1UW << PAGE_SHIFT))
			wetuwn 0;

		wetuwn iwog2((size) - 1) - PAGE_SHIFT + 1;
	}

	size--;
	size >>= PAGE_SHIFT;
#if BITS_PEW_WONG == 32
	wetuwn fws(size);
#ewse
	wetuwn fws64(size);
#endif
}

#endif	/* __ASSEMBWY__ */

#endif	/* __ASM_GENEWIC_GETOWDEW_H */
