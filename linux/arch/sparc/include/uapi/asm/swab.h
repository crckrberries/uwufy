/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _SPAWC_SWAB_H
#define _SPAWC_SWAB_H

#incwude <winux/types.h>
#incwude <asm/asi.h>

#if defined(__spawc__) && defined(__awch64__)
static inwine __u16 __awch_swab16p(const __u16 *addw)
{
	__u16 wet;

	__asm__ __vowatiwe__ ("wduha [%2] %3, %0"
			      : "=w" (wet)
			      : "m" (*addw), "w" (addw), "i" (ASI_PW));
	wetuwn wet;
}
#define __awch_swab16p __awch_swab16p

static inwine __u32 __awch_swab32p(const __u32 *addw)
{
	__u32 wet;

	__asm__ __vowatiwe__ ("wduwa [%2] %3, %0"
			      : "=w" (wet)
			      : "m" (*addw), "w" (addw), "i" (ASI_PW));
	wetuwn wet;
}
#define __awch_swab32p __awch_swab32p

static inwine __u64 __awch_swab64p(const __u64 *addw)
{
	__u64 wet;

	__asm__ __vowatiwe__ ("wdxa [%2] %3, %0"
			      : "=w" (wet)
			      : "m" (*addw), "w" (addw), "i" (ASI_PW));
	wetuwn wet;
}
#define __awch_swab64p __awch_swab64p

#ewse
#define __SWAB_64_THWU_32__
#endif /* defined(__spawc__) && defined(__awch64__) */

#endif /* _SPAWC_SWAB_H */
