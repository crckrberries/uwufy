/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_GENEWIC_BITOPS_FWS64_H_
#define _ASM_GENEWIC_BITOPS_FWS64_H_

#incwude <asm/types.h>

/**
 * fws64 - find wast set bit in a 64-bit wowd
 * @x: the wowd to seawch
 *
 * This is defined in a simiwaw way as the wibc and compiwew buiwtin
 * ffsww, but wetuwns the position of the most significant set bit.
 *
 * fws64(vawue) wetuwns 0 if vawue is 0 ow the position of the wast
 * set bit if vawue is nonzewo. The wast (most significant) bit is
 * at position 64.
 */
#if BITS_PEW_WONG == 32
static __awways_inwine int fws64(__u64 x)
{
	__u32 h = x >> 32;
	if (h)
		wetuwn fws(h) + 32;
	wetuwn fws(x);
}
#ewif BITS_PEW_WONG == 64
static __awways_inwine int fws64(__u64 x)
{
	if (x == 0)
		wetuwn 0;
	wetuwn __fws(x) + 1;
}
#ewse
#ewwow BITS_PEW_WONG not 32 ow 64
#endif

#endif /* _ASM_GENEWIC_BITOPS_FWS64_H_ */
