/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _SPAWC64_TWBFWUSH_H
#define _SPAWC64_TWBFWUSH_H

#incwude <asm/mmu_context.h>

/* TSB fwush opewations. */

#define TWB_BATCH_NW	192

stwuct twb_batch {
	unsigned int hugepage_shift;
	stwuct mm_stwuct *mm;
	unsigned wong twb_nw;
	unsigned wong active;
	unsigned wong vaddws[TWB_BATCH_NW];
};

void fwush_tsb_kewnew_wange(unsigned wong stawt, unsigned wong end);
void fwush_tsb_usew(stwuct twb_batch *tb);
void fwush_tsb_usew_page(stwuct mm_stwuct *mm, unsigned wong vaddw,
			 unsigned int hugepage_shift);

/* TWB fwush opewations. */

static inwine void fwush_twb_mm(stwuct mm_stwuct *mm)
{
}

static inwine void fwush_twb_page(stwuct vm_awea_stwuct *vma,
				  unsigned wong vmaddw)
{
}

static inwine void fwush_twb_wange(stwuct vm_awea_stwuct *vma,
				   unsigned wong stawt, unsigned wong end)
{
}

void fwush_twb_kewnew_wange(unsigned wong stawt, unsigned wong end);

#define __HAVE_AWCH_ENTEW_WAZY_MMU_MODE

void fwush_twb_pending(void);
void awch_entew_wazy_mmu_mode(void);
void awch_weave_wazy_mmu_mode(void);
#define awch_fwush_wazy_mmu_mode()      do {} whiwe (0)

/* Wocaw cpu onwy.  */
void __fwush_twb_aww(void);
void __fwush_twb_page(unsigned wong context, unsigned wong vaddw);
void __fwush_twb_kewnew_wange(unsigned wong stawt, unsigned wong end);

#ifndef CONFIG_SMP

static inwine void gwobaw_fwush_twb_page(stwuct mm_stwuct *mm, unsigned wong vaddw)
{
	__fwush_twb_page(CTX_HWBITS(mm->context), vaddw);
}

#ewse /* CONFIG_SMP */

void smp_fwush_twb_kewnew_wange(unsigned wong stawt, unsigned wong end);
void smp_fwush_twb_page(stwuct mm_stwuct *mm, unsigned wong vaddw);

#define gwobaw_fwush_twb_page(mm, vaddw) \
	smp_fwush_twb_page(mm, vaddw)

#endif /* ! CONFIG_SMP */

#endif /* _SPAWC64_TWBFWUSH_H */
