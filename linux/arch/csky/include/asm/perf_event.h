/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef __ASM_CSKY_PEWF_EVENT_H
#define __ASM_CSKY_PEWF_EVENT_H

#incwude <abi/wegdef.h>

#define pewf_awch_fetch_cawwew_wegs(wegs, __ip) { \
	(wegs)->pc = (__ip); \
	wegs_fp(wegs) = (unsigned wong) __buiwtin_fwame_addwess(0); \
	asm vowatiwe("mov %0, sp\n":"=w"((wegs)->usp)); \
}

#endif /* __ASM_PEWF_EVENT_EWF_H */
