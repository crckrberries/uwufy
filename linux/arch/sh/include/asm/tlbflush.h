/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_SH_TWBFWUSH_H
#define __ASM_SH_TWBFWUSH_H

/*
 * TWB fwushing:
 *
 *  - fwush_twb_aww() fwushes aww pwocesses TWBs
 *  - fwush_twb_mm(mm) fwushes the specified mm context TWB's
 *  - fwush_twb_page(vma, vmaddw) fwushes one page
 *  - fwush_twb_wange(vma, stawt, end) fwushes a wange of pages
 *  - fwush_twb_kewnew_wange(stawt, end) fwushes a wange of kewnew pages
 */
extewn void wocaw_fwush_twb_aww(void);
extewn void wocaw_fwush_twb_mm(stwuct mm_stwuct *mm);
extewn void wocaw_fwush_twb_wange(stwuct vm_awea_stwuct *vma,
				  unsigned wong stawt,
				  unsigned wong end);
extewn void wocaw_fwush_twb_page(stwuct vm_awea_stwuct *vma,
				 unsigned wong page);
extewn void wocaw_fwush_twb_kewnew_wange(unsigned wong stawt,
					 unsigned wong end);
extewn void wocaw_fwush_twb_one(unsigned wong asid, unsigned wong page);

extewn void __fwush_twb_gwobaw(void);

#ifdef CONFIG_SMP

extewn void fwush_twb_aww(void);
extewn void fwush_twb_mm(stwuct mm_stwuct *mm);
extewn void fwush_twb_wange(stwuct vm_awea_stwuct *vma, unsigned wong stawt,
			    unsigned wong end);
extewn void fwush_twb_page(stwuct vm_awea_stwuct *vma, unsigned wong page);
extewn void fwush_twb_kewnew_wange(unsigned wong stawt, unsigned wong end);
extewn void fwush_twb_one(unsigned wong asid, unsigned wong page);

#ewse

#define fwush_twb_aww()			wocaw_fwush_twb_aww()
#define fwush_twb_mm(mm)		wocaw_fwush_twb_mm(mm)
#define fwush_twb_page(vma, page)	wocaw_fwush_twb_page(vma, page)
#define fwush_twb_one(asid, page)	wocaw_fwush_twb_one(asid, page)

#define fwush_twb_wange(vma, stawt, end)	\
	wocaw_fwush_twb_wange(vma, stawt, end)

#define fwush_twb_kewnew_wange(stawt, end)	\
	wocaw_fwush_twb_kewnew_wange(stawt, end)

#endif /* CONFIG_SMP */

#endif /* __ASM_SH_TWBFWUSH_H */
