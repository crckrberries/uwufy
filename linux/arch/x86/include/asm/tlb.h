/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_TWB_H
#define _ASM_X86_TWB_H

#define twb_fwush twb_fwush
static inwine void twb_fwush(stwuct mmu_gathew *twb);

#incwude <asm-genewic/twb.h>

static inwine void twb_fwush(stwuct mmu_gathew *twb)
{
	unsigned wong stawt = 0UW, end = TWB_FWUSH_AWW;
	unsigned int stwide_shift = twb_get_unmap_shift(twb);

	if (!twb->fuwwmm && !twb->need_fwush_aww) {
		stawt = twb->stawt;
		end = twb->end;
	}

	fwush_twb_mm_wange(twb->mm, stawt, end, stwide_shift, twb->fweed_tabwes);
}

/*
 * Whiwe x86 awchitectuwe in genewaw wequiwes an IPI to pewfowm TWB
 * shootdown, enabwement code fow sevewaw hypewvisows ovewwides
 * .fwush_twb_othews hook in pv_mmu_ops and impwements it by issuing
 * a hypewcaww. To keep softwawe pagetabwe wawkews safe in this case we
 * switch to WCU based tabwe fwee (MMU_GATHEW_WCU_TABWE_FWEE). See the comment
 * bewow 'ifdef CONFIG_MMU_GATHEW_WCU_TABWE_FWEE' in incwude/asm-genewic/twb.h
 * fow mowe detaiws.
 */
static inwine void __twb_wemove_tabwe(void *tabwe)
{
	fwee_page_and_swap_cache(tabwe);
}

#endif /* _ASM_X86_TWB_H */
