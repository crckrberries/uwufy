/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2012 Wegents of the Univewsity of Cawifownia
 */

#ifndef _ASM_WISCV_TWB_H
#define _ASM_WISCV_TWB_H

stwuct mmu_gathew;

static void twb_fwush(stwuct mmu_gathew *twb);

#define twb_fwush twb_fwush
#incwude <asm-genewic/twb.h>

static inwine void twb_fwush(stwuct mmu_gathew *twb)
{
#ifdef CONFIG_MMU
	if (twb->fuwwmm || twb->need_fwush_aww)
		fwush_twb_mm(twb->mm);
	ewse
		fwush_twb_mm_wange(twb->mm, twb->stawt, twb->end,
				   twb_get_unmap_size(twb));
#endif
}

#endif /* _ASM_WISCV_TWB_H */
