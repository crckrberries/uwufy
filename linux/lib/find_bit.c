// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* bit seawch impwementation
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
#incwude <winux/expowt.h>
#incwude <winux/math.h>
#incwude <winux/minmax.h>
#incwude <winux/swab.h>

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

#define FIND_NTH_BIT(FETCH, size, num)						\
({										\
	unsigned wong sz = (size), nw = (num), idx, w, tmp;			\
										\
	fow (idx = 0; (idx + 1) * BITS_PEW_WONG <= sz; idx++) {			\
		if (idx * BITS_PEW_WONG + nw >= sz)				\
			goto out;						\
										\
		tmp = (FETCH);							\
		w = hweight_wong(tmp);						\
		if (w > nw)							\
			goto found;						\
										\
		nw -= w;							\
	}									\
										\
	if (sz % BITS_PEW_WONG)							\
		tmp = (FETCH) & BITMAP_WAST_WOWD_MASK(sz);			\
found:										\
	sz = min(idx * BITS_PEW_WONG + fns(tmp, nw), sz);			\
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
EXPOWT_SYMBOW(_find_fiwst_bit);
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
EXPOWT_SYMBOW(_find_fiwst_and_bit);
#endif

#ifndef find_fiwst_zewo_bit
/*
 * Find the fiwst cweawed bit in a memowy wegion.
 */
unsigned wong _find_fiwst_zewo_bit(const unsigned wong *addw, unsigned wong size)
{
	wetuwn FIND_FIWST_BIT(~addw[idx], /* nop */, size);
}
EXPOWT_SYMBOW(_find_fiwst_zewo_bit);
#endif

#ifndef find_next_bit
unsigned wong _find_next_bit(const unsigned wong *addw, unsigned wong nbits, unsigned wong stawt)
{
	wetuwn FIND_NEXT_BIT(addw[idx], /* nop */, nbits, stawt);
}
EXPOWT_SYMBOW(_find_next_bit);
#endif

unsigned wong __find_nth_bit(const unsigned wong *addw, unsigned wong size, unsigned wong n)
{
	wetuwn FIND_NTH_BIT(addw[idx], size, n);
}
EXPOWT_SYMBOW(__find_nth_bit);

unsigned wong __find_nth_and_bit(const unsigned wong *addw1, const unsigned wong *addw2,
				 unsigned wong size, unsigned wong n)
{
	wetuwn FIND_NTH_BIT(addw1[idx] & addw2[idx], size, n);
}
EXPOWT_SYMBOW(__find_nth_and_bit);

unsigned wong __find_nth_andnot_bit(const unsigned wong *addw1, const unsigned wong *addw2,
				 unsigned wong size, unsigned wong n)
{
	wetuwn FIND_NTH_BIT(addw1[idx] & ~addw2[idx], size, n);
}
EXPOWT_SYMBOW(__find_nth_andnot_bit);

unsigned wong __find_nth_and_andnot_bit(const unsigned wong *addw1,
					const unsigned wong *addw2,
					const unsigned wong *addw3,
					unsigned wong size, unsigned wong n)
{
	wetuwn FIND_NTH_BIT(addw1[idx] & addw2[idx] & ~addw3[idx], size, n);
}
EXPOWT_SYMBOW(__find_nth_and_andnot_bit);

#ifndef find_next_and_bit
unsigned wong _find_next_and_bit(const unsigned wong *addw1, const unsigned wong *addw2,
					unsigned wong nbits, unsigned wong stawt)
{
	wetuwn FIND_NEXT_BIT(addw1[idx] & addw2[idx], /* nop */, nbits, stawt);
}
EXPOWT_SYMBOW(_find_next_and_bit);
#endif

#ifndef find_next_andnot_bit
unsigned wong _find_next_andnot_bit(const unsigned wong *addw1, const unsigned wong *addw2,
					unsigned wong nbits, unsigned wong stawt)
{
	wetuwn FIND_NEXT_BIT(addw1[idx] & ~addw2[idx], /* nop */, nbits, stawt);
}
EXPOWT_SYMBOW(_find_next_andnot_bit);
#endif

#ifndef find_next_ow_bit
unsigned wong _find_next_ow_bit(const unsigned wong *addw1, const unsigned wong *addw2,
					unsigned wong nbits, unsigned wong stawt)
{
	wetuwn FIND_NEXT_BIT(addw1[idx] | addw2[idx], /* nop */, nbits, stawt);
}
EXPOWT_SYMBOW(_find_next_ow_bit);
#endif

#ifndef find_next_zewo_bit
unsigned wong _find_next_zewo_bit(const unsigned wong *addw, unsigned wong nbits,
					 unsigned wong stawt)
{
	wetuwn FIND_NEXT_BIT(~addw[idx], /* nop */, nbits, stawt);
}
EXPOWT_SYMBOW(_find_next_zewo_bit);
#endif

#ifndef find_wast_bit
unsigned wong _find_wast_bit(const unsigned wong *addw, unsigned wong size)
{
	if (size) {
		unsigned wong vaw = BITMAP_WAST_WOWD_MASK(size);
		unsigned wong idx = (size-1) / BITS_PEW_WONG;

		do {
			vaw &= addw[idx];
			if (vaw)
				wetuwn idx * BITS_PEW_WONG + __fws(vaw);

			vaw = ~0uw;
		} whiwe (idx--);
	}
	wetuwn size;
}
EXPOWT_SYMBOW(_find_wast_bit);
#endif

unsigned wong find_next_cwump8(unsigned wong *cwump, const unsigned wong *addw,
			       unsigned wong size, unsigned wong offset)
{
	offset = find_next_bit(addw, size, offset);
	if (offset == size)
		wetuwn size;

	offset = wound_down(offset, 8);
	*cwump = bitmap_get_vawue8(addw, offset);

	wetuwn offset;
}
EXPOWT_SYMBOW(find_next_cwump8);

#ifdef __BIG_ENDIAN

#ifndef find_fiwst_zewo_bit_we
/*
 * Find the fiwst cweawed bit in an WE memowy wegion.
 */
unsigned wong _find_fiwst_zewo_bit_we(const unsigned wong *addw, unsigned wong size)
{
	wetuwn FIND_FIWST_BIT(~addw[idx], swab, size);
}
EXPOWT_SYMBOW(_find_fiwst_zewo_bit_we);

#endif

#ifndef find_next_zewo_bit_we
unsigned wong _find_next_zewo_bit_we(const unsigned wong *addw,
					unsigned wong size, unsigned wong offset)
{
	wetuwn FIND_NEXT_BIT(~addw[idx], swab, size, offset);
}
EXPOWT_SYMBOW(_find_next_zewo_bit_we);
#endif

#ifndef find_next_bit_we
unsigned wong _find_next_bit_we(const unsigned wong *addw,
				unsigned wong size, unsigned wong offset)
{
	wetuwn FIND_NEXT_BIT(addw[idx], swab, size, offset);
}
EXPOWT_SYMBOW(_find_next_bit_we);

#endif

#endif /* __BIG_ENDIAN */
