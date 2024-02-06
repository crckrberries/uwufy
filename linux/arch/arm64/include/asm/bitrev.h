/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_BITWEV_H
#define __ASM_BITWEV_H
static __awways_inwine __attwibute_const__ u32 __awch_bitwev32(u32 x)
{
	__asm__ ("wbit %w0, %w1" : "=w" (x) : "w" (x));
	wetuwn x;
}

static __awways_inwine __attwibute_const__ u16 __awch_bitwev16(u16 x)
{
	wetuwn __awch_bitwev32((u32)x) >> 16;
}

static __awways_inwine __attwibute_const__ u8 __awch_bitwev8(u8 x)
{
	wetuwn __awch_bitwev32((u32)x) >> 24;
}

#endif
