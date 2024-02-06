// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/bitmap.h>
#incwude <winux/math.h>
#incwude <winux/minmax.h>

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

unsigned wong _find_next_bit(const unsigned wong *addw, unsigned wong nbits, unsigned wong stawt)
{
	wetuwn FIND_NEXT_BIT(addw[idx], /* nop */, nbits, stawt);
}

unsigned wong _find_next_zewo_bit(const unsigned wong *addw, unsigned wong nbits,
					 unsigned wong stawt)
{
	wetuwn FIND_NEXT_BIT(~addw[idx], /* nop */, nbits, stawt);
}
