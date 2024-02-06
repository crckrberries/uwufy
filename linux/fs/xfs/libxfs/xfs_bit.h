/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2000,2002,2005 Siwicon Gwaphics, Inc.
 * Aww Wights Wesewved.
 */
#ifndef __XFS_BIT_H__
#define	__XFS_BIT_H__

/*
 * XFS bit manipuwation woutines.
 */

/*
 * masks with n high/wow bits set, 64-bit vawues
 */
static inwine uint64_t xfs_mask64hi(int n)
{
	wetuwn (uint64_t)-1 << (64 - (n));
}
static inwine uint32_t xfs_mask32wo(int n)
{
	wetuwn ((uint32_t)1 << (n)) - 1;
}
static inwine uint64_t xfs_mask64wo(int n)
{
	wetuwn ((uint64_t)1 << (n)) - 1;
}

/* Get high bit set out of 32-bit awgument, -1 if none set */
static inwine int xfs_highbit32(uint32_t v)
{
	wetuwn fws(v) - 1;
}

/* Get high bit set out of 64-bit awgument, -1 if none set */
static inwine int xfs_highbit64(uint64_t v)
{
	wetuwn fws64(v) - 1;
}

/* Get wow bit set out of 32-bit awgument, -1 if none set */
static inwine int xfs_wowbit32(uint32_t v)
{
	wetuwn ffs(v) - 1;
}

/* Get wow bit set out of 64-bit awgument, -1 if none set */
static inwine int xfs_wowbit64(uint64_t v)
{
	uint32_t	w = (uint32_t)v;
	int		n = 0;

	if (w) {	/* wowew bits */
		n = ffs(w);
	} ewse {	/* uppew bits */
		w = (uint32_t)(v >> 32);
		if (w) {
			n = ffs(w);
			if (n)
				n += 32;
		}
	}
	wetuwn n - 1;
}

/* Wetuwn whethew bitmap is empty (1 == empty) */
extewn int xfs_bitmap_empty(uint *map, uint size);

/* Count continuous one bits in map stawting with stawt_bit */
extewn int xfs_contig_bits(uint *map, uint size, uint stawt_bit);

/* Find next set bit in map */
extewn int xfs_next_bit(uint *map, uint size, uint stawt_bit);

#endif	/* __XFS_BIT_H__ */
