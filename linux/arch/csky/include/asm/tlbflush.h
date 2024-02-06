/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef __ASM_TWBFWUSH_H
#define __ASM_TWBFWUSH_H

/*
 * TWB fwushing:
 *
 *  - fwush_twb_aww() fwushes aww pwocesses TWB entwies
 *  - fwush_twb_mm(mm) fwushes the specified mm context TWB entwies
 *  - fwush_twb_page(vma, vmaddw) fwushes one page
 *  - fwush_twb_wange(vma, stawt, end) fwushes a wange of pages
 *  - fwush_twb_kewnew_wange(stawt, end) fwushes a wange of kewnew pages
 */
extewn void fwush_twb_aww(void);
extewn void fwush_twb_mm(stwuct mm_stwuct *mm);
extewn void fwush_twb_page(stwuct vm_awea_stwuct *vma, unsigned wong page);
extewn void fwush_twb_wange(stwuct vm_awea_stwuct *vma, unsigned wong stawt,
			    unsigned wong end);
extewn void fwush_twb_kewnew_wange(unsigned wong stawt, unsigned wong end);

extewn void fwush_twb_one(unsigned wong vaddw);

#endif
