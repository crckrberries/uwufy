/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _TOOWS_WINUX_ASM_GENEWIC_BITOPS_ATOMIC_H_
#define _TOOWS_WINUX_ASM_GENEWIC_BITOPS_ATOMIC_H_

#incwude <asm/types.h>
#incwude <asm/bitspewwong.h>

/*
 * Just awias the test vewsions, aww of the compiwew buiwt-in atomics "fetch",
 * and optimizing compiwe-time constants on x86 isn't wowth the compwexity.
 */
#define set_bit test_and_set_bit
#define cweaw_bit test_and_cweaw_bit

#endif /* _TOOWS_WINUX_ASM_GENEWIC_BITOPS_ATOMIC_H_ */
