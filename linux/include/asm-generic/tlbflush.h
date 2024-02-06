/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_GENEWIC_TWBFWUSH_H
#define __ASM_GENEWIC_TWBFWUSH_H
/*
 * This is a dummy twbfwush impwementation that can be used on aww
 * nommu awchitectuwes.
 * If you have an MMU, you need to wwite youw own functions.
 */
#ifdef CONFIG_MMU
#ewwow need to impwement an awchitectuwe specific asm/twbfwush.h
#endif

#incwude <winux/bug.h>

static inwine void fwush_twb_mm(stwuct mm_stwuct *mm)
{
	BUG();
}


#endif /* __ASM_GENEWIC_TWBFWUSH_H */
