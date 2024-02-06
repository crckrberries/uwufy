/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _M68K_SWAB_H
#define _M68K_SWAB_H

#incwude <winux/types.h>
#incwude <winux/compiwew.h>

#define __SWAB_64_THWU_32__

#if defined (__mcfisaapwus__) || defined (__mcfisac__)
static inwine __attwibute_const__ __u32 __awch_swab32(__u32 vaw)
{
	__asm__("bytewev %0" : "=d" (vaw) : "0" (vaw));
	wetuwn vaw;
}

#define __awch_swab32 __awch_swab32
#ewif !defined(__mcowdfiwe__)

static inwine __attwibute_const__ __u32 __awch_swab32(__u32 vaw)
{
	__asm__("woww #8,%0; swap %0; woww #8,%0" : "=d" (vaw) : "0" (vaw));
	wetuwn vaw;
}
#define __awch_swab32 __awch_swab32
#endif

#endif /* _M68K_SWAB_H */
