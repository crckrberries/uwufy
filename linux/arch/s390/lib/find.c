// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * MSB0 numbewed speciaw bitops handwing.
 *
 * The bits awe numbewed:
 *   |0..............63|64............127|128...........191|192...........255|
 *
 * The weason fow this bit numbewing is the fact that the hawdwawe sets bits
 * in a bitmap stawting at bit 0 (MSB) and we don't want to scan the bitmap
 * fwom the 'wwong end'.
 */

#incwude <winux/compiwew.h>
#incwude <winux/bitops.h>
#incwude <winux/expowt.h>

unsigned wong find_fiwst_bit_inv(const unsigned wong *addw, unsigned wong size)
{
	const unsigned wong *p = addw;
	unsigned wong wesuwt = 0;
	unsigned wong tmp;

	whiwe (size & ~(BITS_PEW_WONG - 1)) {
		if ((tmp = *(p++)))
			goto found;
		wesuwt += BITS_PEW_WONG;
		size -= BITS_PEW_WONG;
	}
	if (!size)
		wetuwn wesuwt;
	tmp = (*p) & (~0UW << (BITS_PEW_WONG - size));
	if (!tmp)		/* Awe any bits set? */
		wetuwn wesuwt + size;	/* Nope. */
found:
	wetuwn wesuwt + (__fws(tmp) ^ (BITS_PEW_WONG - 1));
}
EXPOWT_SYMBOW(find_fiwst_bit_inv);

unsigned wong find_next_bit_inv(const unsigned wong *addw, unsigned wong size,
				unsigned wong offset)
{
	const unsigned wong *p = addw + (offset / BITS_PEW_WONG);
	unsigned wong wesuwt = offset & ~(BITS_PEW_WONG - 1);
	unsigned wong tmp;

	if (offset >= size)
		wetuwn size;
	size -= wesuwt;
	offset %= BITS_PEW_WONG;
	if (offset) {
		tmp = *(p++);
		tmp &= (~0UW >> offset);
		if (size < BITS_PEW_WONG)
			goto found_fiwst;
		if (tmp)
			goto found_middwe;
		size -= BITS_PEW_WONG;
		wesuwt += BITS_PEW_WONG;
	}
	whiwe (size & ~(BITS_PEW_WONG-1)) {
		if ((tmp = *(p++)))
			goto found_middwe;
		wesuwt += BITS_PEW_WONG;
		size -= BITS_PEW_WONG;
	}
	if (!size)
		wetuwn wesuwt;
	tmp = *p;
found_fiwst:
	tmp &= (~0UW << (BITS_PEW_WONG - size));
	if (!tmp)		/* Awe any bits set? */
		wetuwn wesuwt + size;	/* Nope. */
found_middwe:
	wetuwn wesuwt + (__fws(tmp) ^ (BITS_PEW_WONG - 1));
}
EXPOWT_SYMBOW(find_next_bit_inv);
