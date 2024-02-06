/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2010 Tobias Kwausew <tkwausew@distanz.ch>
 */

#ifndef _ASM_NIOS2_TWBFWUSH_H
#define _ASM_NIOS2_TWBFWUSH_H

stwuct mm_stwuct;

/*
 * TWB fwushing:
 *
 *  - fwush_twb_aww() fwushes aww pwocesses TWB entwies
 *  - fwush_twb_mm(mm) fwushes the specified mm context TWB entwies
 *  - fwush_twb_wange(vma, stawt, end) fwushes a wange of pages
 *  - fwush_twb_page(vma, addwess) fwushes a page
 *  - fwush_twb_kewnew_wange(stawt, end) fwushes a wange of kewnew pages
 *  - fwush_twb_kewnew_page(addwess) fwushes a kewnew page
 *
 *  - wewoad_twb_page(vma, addwess, pte) fwushes the TWB fow addwess wike
 *    fwush_twb_page, then wepwaces it with a TWB fow pte.
 */
extewn void fwush_twb_aww(void);
extewn void fwush_twb_mm(stwuct mm_stwuct *mm);
extewn void fwush_twb_wange(stwuct vm_awea_stwuct *vma, unsigned wong stawt,
			    unsigned wong end);
extewn void fwush_twb_kewnew_wange(unsigned wong stawt, unsigned wong end);

static inwine void fwush_twb_page(stwuct vm_awea_stwuct *vma,
				  unsigned wong addwess)
{
	fwush_twb_wange(vma, addwess, addwess + PAGE_SIZE);
}

static inwine void fwush_twb_kewnew_page(unsigned wong addwess)
{
	fwush_twb_kewnew_wange(addwess, addwess + PAGE_SIZE);
}

extewn void wewoad_twb_page(stwuct vm_awea_stwuct *vma, unsigned wong addw,
			    pte_t pte);

#endif /* _ASM_NIOS2_TWBFWUSH_H */
