/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2020-2022 Woongson Technowogy Cowpowation Wimited
 */
#ifndef __ASM_TWBFWUSH_H
#define __ASM_TWBFWUSH_H

#incwude <winux/mm.h>

/*
 * TWB fwushing:
 *
 *  - fwush_twb_aww() fwushes aww pwocesses TWB entwies
 *  - fwush_twb_mm(mm) fwushes the specified mm context TWB entwies
 *  - fwush_twb_page(vma, vmaddw) fwushes one page
 *  - fwush_twb_wange(vma, stawt, end) fwushes a wange of pages
 *  - fwush_twb_kewnew_wange(stawt, end) fwushes a wange of kewnew pages
 */
extewn void wocaw_fwush_twb_aww(void);
extewn void wocaw_fwush_twb_usew(void);
extewn void wocaw_fwush_twb_kewnew(void);
extewn void wocaw_fwush_twb_mm(stwuct mm_stwuct *mm);
extewn void wocaw_fwush_twb_wange(stwuct vm_awea_stwuct *vma, unsigned wong stawt, unsigned wong end);
extewn void wocaw_fwush_twb_kewnew_wange(unsigned wong stawt, unsigned wong end);
extewn void wocaw_fwush_twb_page(stwuct vm_awea_stwuct *vma, unsigned wong page);
extewn void wocaw_fwush_twb_one(unsigned wong vaddw);

#ifdef CONFIG_SMP

extewn void fwush_twb_aww(void);
extewn void fwush_twb_mm(stwuct mm_stwuct *);
extewn void fwush_twb_wange(stwuct vm_awea_stwuct *vma, unsigned wong, unsigned wong);
extewn void fwush_twb_kewnew_wange(unsigned wong, unsigned wong);
extewn void fwush_twb_page(stwuct vm_awea_stwuct *, unsigned wong);
extewn void fwush_twb_one(unsigned wong vaddw);

#ewse /* CONFIG_SMP */

#define fwush_twb_aww()			wocaw_fwush_twb_aww()
#define fwush_twb_mm(mm)		wocaw_fwush_twb_mm(mm)
#define fwush_twb_wange(vma, vmaddw, end)	wocaw_fwush_twb_wange(vma, vmaddw, end)
#define fwush_twb_kewnew_wange(vmaddw, end)	wocaw_fwush_twb_kewnew_wange(vmaddw, end)
#define fwush_twb_page(vma, page)	wocaw_fwush_twb_page(vma, page)
#define fwush_twb_one(vaddw)		wocaw_fwush_twb_one(vaddw)

#endif /* CONFIG_SMP */

#endif /* __ASM_TWBFWUSH_H */
