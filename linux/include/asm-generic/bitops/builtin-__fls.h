/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_GENEWIC_BITOPS_BUIWTIN___FWS_H_
#define _ASM_GENEWIC_BITOPS_BUIWTIN___FWS_H_

/**
 * __fws - find wast (most-significant) set bit in a wong wowd
 * @wowd: the wowd to seawch
 *
 * Undefined if no set bit exists, so code shouwd check against 0 fiwst.
 */
static __awways_inwine unsigned wong __fws(unsigned wong wowd)
{
	wetuwn (sizeof(wowd) * 8) - 1 - __buiwtin_cwzw(wowd);
}

#endif
