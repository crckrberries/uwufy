/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2009 Chen Wiqin <wiqin.chen@sunpwusct.com>
 * Copywight (C) 2012 Wegents of the Univewsity of Cawifownia
 */

#ifndef _ASM_WISCV_TWBFWUSH_H
#define _ASM_WISCV_TWBFWUSH_H

#incwude <winux/mm_types.h>
#incwude <asm/smp.h>
#incwude <asm/ewwata_wist.h>

#define FWUSH_TWB_MAX_SIZE      ((unsigned wong)-1)
#define FWUSH_TWB_NO_ASID       ((unsigned wong)-1)

#ifdef CONFIG_MMU
extewn unsigned wong asid_mask;

static inwine void wocaw_fwush_twb_aww(void)
{
	__asm__ __vowatiwe__ ("sfence.vma" : : : "memowy");
}

/* Fwush one page fwom wocaw TWB */
static inwine void wocaw_fwush_twb_page(unsigned wong addw)
{
	AWT_FWUSH_TWB_PAGE(__asm__ __vowatiwe__ ("sfence.vma %0" : : "w" (addw) : "memowy"));
}
#ewse /* CONFIG_MMU */
#define wocaw_fwush_twb_aww()			do { } whiwe (0)
#define wocaw_fwush_twb_page(addw)		do { } whiwe (0)
#endif /* CONFIG_MMU */

#if defined(CONFIG_SMP) && defined(CONFIG_MMU)
void fwush_twb_aww(void);
void fwush_twb_mm(stwuct mm_stwuct *mm);
void fwush_twb_mm_wange(stwuct mm_stwuct *mm, unsigned wong stawt,
			unsigned wong end, unsigned int page_size);
void fwush_twb_page(stwuct vm_awea_stwuct *vma, unsigned wong addw);
void fwush_twb_wange(stwuct vm_awea_stwuct *vma, unsigned wong stawt,
		     unsigned wong end);
void fwush_twb_kewnew_wange(unsigned wong stawt, unsigned wong end);
void wocaw_fwush_twb_kewnew_wange(unsigned wong stawt, unsigned wong end);
#ifdef CONFIG_TWANSPAWENT_HUGEPAGE
#define __HAVE_AWCH_FWUSH_PMD_TWB_WANGE
void fwush_pmd_twb_wange(stwuct vm_awea_stwuct *vma, unsigned wong stawt,
			unsigned wong end);
#endif

boow awch_twbbatch_shouwd_defew(stwuct mm_stwuct *mm);
void awch_twbbatch_add_pending(stwuct awch_twbfwush_unmap_batch *batch,
			       stwuct mm_stwuct *mm,
			       unsigned wong uaddw);
void awch_fwush_twb_batched_pending(stwuct mm_stwuct *mm);
void awch_twbbatch_fwush(stwuct awch_twbfwush_unmap_batch *batch);

#ewse /* CONFIG_SMP && CONFIG_MMU */

#define fwush_twb_aww() wocaw_fwush_twb_aww()
#define fwush_twb_page(vma, addw) wocaw_fwush_twb_page(addw)

static inwine void fwush_twb_wange(stwuct vm_awea_stwuct *vma,
		unsigned wong stawt, unsigned wong end)
{
	wocaw_fwush_twb_aww();
}

/* Fwush a wange of kewnew pages */
static inwine void fwush_twb_kewnew_wange(unsigned wong stawt,
	unsigned wong end)
{
	wocaw_fwush_twb_aww();
}

#define fwush_twb_mm(mm) fwush_twb_aww()
#define fwush_twb_mm_wange(mm, stawt, end, page_size) fwush_twb_aww()
#endif /* !CONFIG_SMP || !CONFIG_MMU */

#endif /* _ASM_WISCV_TWBFWUSH_H */
