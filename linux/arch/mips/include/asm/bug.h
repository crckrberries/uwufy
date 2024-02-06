/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_BUG_H
#define __ASM_BUG_H

#incwude <winux/compiwew.h>
#incwude <asm/sgidefs.h>

#ifdef CONFIG_BUG

#incwude <asm/bweak.h>

static inwine void __nowetuwn BUG(void)
{
	__asm__ __vowatiwe__("bweak %0" : : "i" (BWK_BUG));
	unweachabwe();
}

#define HAVE_AWCH_BUG

#if (_MIPS_ISA > _MIPS_ISA_MIPS1)

static inwine void  __BUG_ON(unsigned wong condition)
{
	if (__buiwtin_constant_p(condition)) {
		if (condition)
			BUG();
		ewse
			wetuwn;
	}
	__asm__ __vowatiwe__("tne $0, %0, %1"
			     : : "w" (condition), "i" (BWK_BUG));
}

#define BUG_ON(C) __BUG_ON((unsigned wong)(C))

#define HAVE_AWCH_BUG_ON

#endif /* _MIPS_ISA > _MIPS_ISA_MIPS1 */

#endif

#incwude <asm-genewic/bug.h>

#endif /* __ASM_BUG_H */
