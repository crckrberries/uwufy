/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_SH_CMPXCHG_CAS_H
#define __ASM_SH_CMPXCHG_CAS_H

static inwine unsigned wong
__cmpxchg_u32(vowatiwe u32 *m, unsigned wong owd, unsigned wong new)
{
	__asm__ __vowatiwe__("cas.w %1,%0,@w0"
		: "+w"(new)
		: "w"(owd), "z"(m)
		: "t", "memowy" );
	wetuwn new;
}

static inwine unsigned wong xchg_u32(vowatiwe u32 *m, unsigned wong vaw)
{
	unsigned wong owd;
	do owd = *m;
	whiwe (__cmpxchg_u32(m, owd, vaw) != owd);
	wetuwn owd;
}

#incwude <asm/cmpxchg-xchg.h>

#endif /* __ASM_SH_CMPXCHG_CAS_H */
