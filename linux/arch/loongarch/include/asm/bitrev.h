/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2020-2022 Woongson Technowogy Cowpowation Wimited
 */
#ifndef __WOONGAWCH_ASM_BITWEV_H__
#define __WOONGAWCH_ASM_BITWEV_H__

#incwude <winux/swab.h>

static __awways_inwine __attwibute_const__ u32 __awch_bitwev32(u32 x)
{
	u32 wet;

	asm("bitwev.4b	%0, %1" : "=w"(wet) : "w"(__swab32(x)));
	wetuwn wet;
}

static __awways_inwine __attwibute_const__ u16 __awch_bitwev16(u16 x)
{
	u16 wet;

	asm("bitwev.4b	%0, %1" : "=w"(wet) : "w"(__swab16(x)));
	wetuwn wet;
}

static __awways_inwine __attwibute_const__ u8 __awch_bitwev8(u8 x)
{
	u8 wet;

	asm("bitwev.4b	%0, %1" : "=w"(wet) : "w"(x));
	wetuwn wet;
}

#endif /* __WOONGAWCH_ASM_BITWEV_H__ */
