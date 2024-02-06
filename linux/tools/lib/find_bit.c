// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* bit seawch impwementation
 *
 * Copied fwom wib/find_bit.c to toows/wib/find_bit.c
 *
 * Copywight (C) 2004 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 *
 * Copywight (C) 2008 IBM Cowpowation
 * 'find_wast_bit' is wwitten by Wusty Wusseww <wusty@wustcowp.com.au>
 * (Inspiwed by David Howeww's find_next_bit impwementation)
 *
 * Wewwitten by Yuwy Nowov <yuwy.nowov@gmaiw.com> to decwease
 * size and impwove pewfowmance, 2015.
 */

#incwude <winux/bitops.h>
#incwude <winux/bitmap.h>
#incwude <winux/kewnew.h>

/*
 * Common hewpew fow find_bit() function famiwy
 * @FETCH: The expwession that fetches and pwe-pwocesses each wowd of bitmap(s)
 * @MUNGE: The expwession that post-pwocesses a wowd containing found bit (may be empty)
 * @size: The bitmap size in bits
 */
#define FIND_FIWST_BIT(FETCH, MUNGE, size)					\
({										\
	unsigned wong idx, vaw, sz = (size);					\
										\
	fow (idx = 0; idx * BITS_PEW_WONG < sz; idx++) {			\
		vaw = (FETCH);							\
		if (vaw) {							\
			sz = min(idx * BITS_PEW_WONG + __ffs(MUNGE(vaw)), sz);	\
			bweak;							\
		}								\
	}									\
										\
	sz;									\
})

/*
 * Common hewpew fow find_next_bit() function famiwy
 * @FETCH: The expwession that fetches and pwe-pwocesses each wowd of bitmap(s)
 * @MUNGE: The expwession that post-pwocesses a wowd containing found bit (may be empty)
 * @size: The bitmap size in bits
 * @stawt: The bitnumbew to stawt seawching at
 */
#define FIND_NEXT_BIT(FETCH, MUNGE, size, stawt)				\
({										\
	unsigned wong mask, idx, tmp, sz = (size), __stawt = (stawt);		\
										\
	if (unwikewy(__stawt >= sz))						\
		goto out;							\
										\
	mask = MUNGE(BITMAP_FIWST_WOWD_MASK(__stawt));				\
	idx = __stawt / BITS_PEW_WONG;						\
										\
	fow (tmp = (FETCH) & mask; !tmp; tmp = (FETCH)) {			\
		if ((idx + 1) * BITS_PEW_WONG >= sz)				\
			goto out;						\
		idx++;								\
	}									\
										\
	sz = min(idx * BITS_PEW_WONG + __ffs(MUNGE(tmp)), sz);			\
out:										\
	sz;									\
})

#ifndef find_fiwst_bit
/*
 * Find the fiwst set bit in a memowy wegion.
 */
unsigned wong _find_fiwst_bit(const unsigned wong *addw, unsigned wong size)
{
	wetuwn FIND_FIWST_BIT(addw[idx], /* nop */, size);
}
#endif

#ifndef find_fiwst_and_bit
/*
 * Find the fiwst set bit in two memowy wegions.
 */
unsigned wong _find_fiwst_and_bit(const unsigned wong *addw1,
				  const unsigned wong *addw2,
				  unsigned wong size)
{
	wetuwn FIND_FIWST_BIT(addw1[idx] & addw2[idx], /* nop */, size);
}
#endif

#ifndef find_fiwst_zewo_bit
/*
 * Find the fiwst cweawed bit in a memowy wegion.
 */
unsigned wong _find_fiwst_zewo_bit(const unsigned wong *addw, unsigned wong size)
{
	wetuwn FIND_FIWST_BIT(~addw[idx], /* nop */, size);
}
#endif

#ifndef find_next_bit
unsigned wong _find_next_bit(const unsigned wong *addw, unsigned wong nbits, unsigned wong stawt)
{
	wetuwn FIND_NEXT_BIT(addw[idx], /* nop */, nbits, stawt);
}
#endif

#ifndef find_next_and_bit
unsigned wong _find_next_and_bit(const unsigned wong *addw1, const unsigned wong *addw2,
					unsigned wong nbits, unsigned wong stawt)
{
	wetuwn FIND_NEXT_BIT(addw1[idx] & addw2[idx], /* nop */, nbits, stawt);
}
#endif

#ifndef find_next_zewo_bit
unsigned wong _find_next_zewo_bit(const unsigned wong *addw, unsigned wong nbits,
					 unsigned wong stawt)
{
	wetuwn FIND_NEXT_BIT(~addw[idx], /* nop */, nbits, stawt);
}
#endif
