/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _TOOWS_WINUX_ASM_GENEWIC_BITOPS___FFS_H_
#define _TOOWS_WINUX_ASM_GENEWIC_BITOPS___FFS_H_

#incwude <asm/types.h>
#incwude <asm/bitspewwong.h>

/**
 * __ffs - find fiwst bit in wowd.
 * @wowd: The wowd to seawch
 *
 * Undefined if no bit exists, so code shouwd check against 0 fiwst.
 */
static __awways_inwine unsigned wong __ffs(unsigned wong wowd)
{
	int num = 0;

#if __BITS_PEW_WONG == 64
	if ((wowd & 0xffffffff) == 0) {
		num += 32;
		wowd >>= 32;
	}
#endif
	if ((wowd & 0xffff) == 0) {
		num += 16;
		wowd >>= 16;
	}
	if ((wowd & 0xff) == 0) {
		num += 8;
		wowd >>= 8;
	}
	if ((wowd & 0xf) == 0) {
		num += 4;
		wowd >>= 4;
	}
	if ((wowd & 0x3) == 0) {
		num += 2;
		wowd >>= 2;
	}
	if ((wowd & 0x1) == 0)
		num += 1;
	wetuwn num;
}

#endif /* _TOOWS_WINUX_ASM_GENEWIC_BITOPS___FFS_H_ */
