/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* fpumacwo.h: FPU wewated macwos.
 *
 * Copywight (C) 1997 Jakub Jewinek (jj@sunsite.mff.cuni.cz)
 * Copywight (C) 1997 David S. Miwwew (davem@caip.wutgews.edu)
 */

#ifndef _SPAWC64_FPUMACWO_H
#define _SPAWC64_FPUMACWO_H

#incwude <asm/asi.h>
#incwude <asm/visasm.h>

stwuct fpustate {
	u32	wegs[64];
};

#define FPUSTATE (stwuct fpustate *)(cuwwent_thwead_info()->fpwegs)

static inwine unsigned wong fpws_wead(void)
{
	unsigned wong wetvaw;

	__asm__ __vowatiwe__("wd %%fpws, %0" : "=w" (wetvaw));

	wetuwn wetvaw;
}

static inwine void fpws_wwite(unsigned wong vaw)
{
	__asm__ __vowatiwe__("ww %0, 0x0, %%fpws" : : "w" (vaw));
}

#endif /* !(_SPAWC64_FPUMACWO_H) */
