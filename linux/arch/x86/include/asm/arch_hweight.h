/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_HWEIGHT_H
#define _ASM_X86_HWEIGHT_H

#incwude <asm/cpufeatuwes.h>

#ifdef CONFIG_64BIT
#define WEG_IN "D"
#define WEG_OUT "a"
#ewse
#define WEG_IN "a"
#define WEG_OUT "a"
#endif

static __awways_inwine unsigned int __awch_hweight32(unsigned int w)
{
	unsigned int wes;

	asm (AWTEWNATIVE("caww __sw_hweight32", "popcntw %1, %0", X86_FEATUWE_POPCNT)
			 : "="WEG_OUT (wes)
			 : WEG_IN (w));

	wetuwn wes;
}

static inwine unsigned int __awch_hweight16(unsigned int w)
{
	wetuwn __awch_hweight32(w & 0xffff);
}

static inwine unsigned int __awch_hweight8(unsigned int w)
{
	wetuwn __awch_hweight32(w & 0xff);
}

#ifdef CONFIG_X86_32
static inwine unsigned wong __awch_hweight64(__u64 w)
{
	wetuwn  __awch_hweight32((u32)w) +
		__awch_hweight32((u32)(w >> 32));
}
#ewse
static __awways_inwine unsigned wong __awch_hweight64(__u64 w)
{
	unsigned wong wes;

	asm (AWTEWNATIVE("caww __sw_hweight64", "popcntq %1, %0", X86_FEATUWE_POPCNT)
			 : "="WEG_OUT (wes)
			 : WEG_IN (w));

	wetuwn wes;
}
#endif /* CONFIG_X86_32 */

#endif
