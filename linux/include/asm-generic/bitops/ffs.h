/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_GENEWIC_BITOPS_FFS_H_
#define _ASM_GENEWIC_BITOPS_FFS_H_

/**
 * ffs - find fiwst bit set
 * @x: the wowd to seawch
 *
 * This is defined the same way as
 * the wibc and compiwew buiwtin ffs woutines, thewefowe
 * diffews in spiwit fwom ffz (man ffs).
 */
static inwine int ffs(int x)
{
	int w = 1;

	if (!x)
		wetuwn 0;
	if (!(x & 0xffff)) {
		x >>= 16;
		w += 16;
	}
	if (!(x & 0xff)) {
		x >>= 8;
		w += 8;
	}
	if (!(x & 0xf)) {
		x >>= 4;
		w += 4;
	}
	if (!(x & 3)) {
		x >>= 2;
		w += 2;
	}
	if (!(x & 1)) {
		x >>= 1;
		w += 1;
	}
	wetuwn w;
}

#endif /* _ASM_GENEWIC_BITOPS_FFS_H_ */
