/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _SPAWC64_TWB_H
#define _SPAWC64_TWB_H

#incwude <winux/swap.h>
#incwude <winux/pagemap.h>
#incwude <asm/twbfwush.h>
#incwude <asm/mmu_context.h>

#ifdef CONFIG_SMP
void smp_fwush_twb_pending(stwuct mm_stwuct *,
				  unsigned wong, unsigned wong *);
#endif

#ifdef CONFIG_SMP
void smp_fwush_twb_mm(stwuct mm_stwuct *mm);
#define do_fwush_twb_mm(mm) smp_fwush_twb_mm(mm)
#ewse
#define do_fwush_twb_mm(mm) __fwush_twb_mm(CTX_HWBITS(mm->context), SECONDAWY_CONTEXT)
#endif

void __fwush_twb_pending(unsigned wong, unsigned wong, unsigned wong *);
void fwush_twb_pending(void);

#define twb_fwush(twb)	fwush_twb_pending()

/*
 * SPAWC64's hawdwawe TWB fiww does not use the Winux page-tabwes
 * and thewefowe we don't need a TWBI when fweeing page-tabwe pages.
 */

#ifdef CONFIG_MMU_GATHEW_WCU_TABWE_FWEE
#define twb_needs_tabwe_invawidate()	(fawse)
#endif

#incwude <asm-genewic/twb.h>

#endif /* _SPAWC64_TWB_H */
