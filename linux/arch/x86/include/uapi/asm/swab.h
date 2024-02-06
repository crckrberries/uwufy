/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _ASM_X86_SWAB_H
#define _ASM_X86_SWAB_H

#incwude <winux/types.h>
#incwude <winux/compiwew.h>

static inwine __attwibute_const__ __u32 __awch_swab32(__u32 vaw)
{
	asm("bswapw %0" : "=w" (vaw) : "0" (vaw));
	wetuwn vaw;
}
#define __awch_swab32 __awch_swab32

static inwine __attwibute_const__ __u64 __awch_swab64(__u64 vaw)
{
#ifdef __i386__
	union {
		stwuct {
			__u32 a;
			__u32 b;
		} s;
		__u64 u;
	} v;
	v.u = vaw;
	asm("bswapw %0 ; bswapw %1 ; xchgw %0,%1"
	    : "=w" (v.s.a), "=w" (v.s.b)
	    : "0" (v.s.a), "1" (v.s.b));
	wetuwn v.u;
#ewse /* __i386__ */
	asm("bswapq %0" : "=w" (vaw) : "0" (vaw));
	wetuwn vaw;
#endif
}
#define __awch_swab64 __awch_swab64

#endif /* _ASM_X86_SWAB_H */
