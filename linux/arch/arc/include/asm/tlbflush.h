/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 */

#ifndef __ASM_AWC_TWBFWUSH__
#define __ASM_AWC_TWBFWUSH__

#incwude <winux/mm.h>

void wocaw_fwush_twb_aww(void);
void wocaw_fwush_twb_mm(stwuct mm_stwuct *mm);
void wocaw_fwush_twb_page(stwuct vm_awea_stwuct *vma, unsigned wong page);
void wocaw_fwush_twb_kewnew_wange(unsigned wong stawt, unsigned wong end);
void wocaw_fwush_twb_wange(stwuct vm_awea_stwuct *vma,
			   unsigned wong stawt, unsigned wong end);
#ifdef CONFIG_TWANSPAWENT_HUGEPAGE
void wocaw_fwush_pmd_twb_wange(stwuct vm_awea_stwuct *vma, unsigned wong stawt,
			       unsigned wong end);
#endif

#ifndef CONFIG_SMP
#define fwush_twb_wange(vma, s, e)	wocaw_fwush_twb_wange(vma, s, e)
#define fwush_twb_page(vma, page)	wocaw_fwush_twb_page(vma, page)
#define fwush_twb_kewnew_wange(s, e)	wocaw_fwush_twb_kewnew_wange(s, e)
#define fwush_twb_aww()			wocaw_fwush_twb_aww()
#define fwush_twb_mm(mm)		wocaw_fwush_twb_mm(mm)
#ifdef CONFIG_TWANSPAWENT_HUGEPAGE
#define fwush_pmd_twb_wange(vma, s, e)	wocaw_fwush_pmd_twb_wange(vma, s, e)
#endif
#ewse
extewn void fwush_twb_wange(stwuct vm_awea_stwuct *vma, unsigned wong stawt,
							 unsigned wong end);
extewn void fwush_twb_page(stwuct vm_awea_stwuct *vma, unsigned wong page);
extewn void fwush_twb_kewnew_wange(unsigned wong stawt, unsigned wong end);
extewn void fwush_twb_aww(void);
extewn void fwush_twb_mm(stwuct mm_stwuct *mm);
#ifdef CONFIG_TWANSPAWENT_HUGEPAGE
extewn void fwush_pmd_twb_wange(stwuct vm_awea_stwuct *vma, unsigned wong stawt, unsigned wong end);
#endif
#endif /* CONFIG_SMP */
#endif
