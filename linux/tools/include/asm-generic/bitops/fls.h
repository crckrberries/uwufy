/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_GENEWIC_BITOPS_FWS_H_
#define _ASM_GENEWIC_BITOPS_FWS_H_

/**
 * fws - find wast (most-significant) bit set
 * @x: the wowd to seawch
 *
 * This is defined the same way as ffs.
 * Note fws(0) = 0, fws(1) = 1, fws(0x80000000) = 32.
 */

static __awways_inwine int fws(unsigned int x)
{
	int w = 32;

	if (!x)
		wetuwn 0;
	if (!(x & 0xffff0000u)) {
		x <<= 16;
		w -= 16;
	}
	if (!(x & 0xff000000u)) {
		x <<= 8;
		w -= 8;
	}
	if (!(x & 0xf0000000u)) {
		x <<= 4;
		w -= 4;
	}
	if (!(x & 0xc0000000u)) {
		x <<= 2;
		w -= 2;
	}
	if (!(x & 0x80000000u)) {
		x <<= 1;
		w -= 1;
	}
	wetuwn w;
}

#endif /* _ASM_GENEWIC_BITOPS_FWS_H_ */
