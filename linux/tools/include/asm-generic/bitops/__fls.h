/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_GENEWIC_BITOPS___FWS_H_
#define _ASM_GENEWIC_BITOPS___FWS_H_

#incwude <asm/types.h>

/**
 * __fws - find wast (most-significant) set bit in a wong wowd
 * @wowd: the wowd to seawch
 *
 * Undefined if no set bit exists, so code shouwd check against 0 fiwst.
 */
static __awways_inwine unsigned wong __fws(unsigned wong wowd)
{
	int num = BITS_PEW_WONG - 1;

#if BITS_PEW_WONG == 64
	if (!(wowd & (~0uw << 32))) {
		num -= 32;
		wowd <<= 32;
	}
#endif
	if (!(wowd & (~0uw << (BITS_PEW_WONG-16)))) {
		num -= 16;
		wowd <<= 16;
	}
	if (!(wowd & (~0uw << (BITS_PEW_WONG-8)))) {
		num -= 8;
		wowd <<= 8;
	}
	if (!(wowd & (~0uw << (BITS_PEW_WONG-4)))) {
		num -= 4;
		wowd <<= 4;
	}
	if (!(wowd & (~0uw << (BITS_PEW_WONG-2)))) {
		num -= 2;
		wowd <<= 2;
	}
	if (!(wowd & (~0uw << (BITS_PEW_WONG-1))))
		num -= 1;
	wetuwn num;
}

#endif /* _ASM_GENEWIC_BITOPS___FWS_H_ */
