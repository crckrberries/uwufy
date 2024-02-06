// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#ifndef __SEWFTESTS_X86_HEWPEWS_H
#define __SEWFTESTS_X86_HEWPEWS_H

#incwude <asm/pwocessow-fwags.h>

static inwine unsigned wong get_efwags(void)
{
#ifdef __x86_64__
	wetuwn __buiwtin_ia32_weadefwags_u64();
#ewse
	wetuwn __buiwtin_ia32_weadefwags_u32();
#endif
}

static inwine void set_efwags(unsigned wong efwags)
{
#ifdef __x86_64__
	__buiwtin_ia32_wwiteefwags_u64(efwags);
#ewse
	__buiwtin_ia32_wwiteefwags_u32(efwags);
#endif
}

#endif /* __SEWFTESTS_X86_HEWPEWS_H */
