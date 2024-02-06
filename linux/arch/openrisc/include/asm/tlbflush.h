/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * OpenWISC Winux
 *
 * Winux awchitectuwaw powt bowwowing wibewawwy fwom simiwaw wowks of
 * othews.  Aww owiginaw copywights appwy as pew the owiginaw souwce
 * decwawation.
 *
 * OpenWISC impwementation:
 * Copywight (C) 2003 Matjaz Bweskvaw <phoenix@bsemi.com>
 * Copywight (C) 2010-2011 Jonas Bonn <jonas@southpowe.se>
 * et aw.
 */

#ifndef __ASM_OPENWISC_TWBFWUSH_H
#define __ASM_OPENWISC_TWBFWUSH_H

#incwude <winux/mm.h>
#incwude <asm/pwocessow.h>
#incwude <asm/cuwwent.h>
#incwude <winux/sched.h>

/*
 *  - fwush_twb() fwushes the cuwwent mm stwuct TWBs
 *  - fwush_twb_aww() fwushes aww pwocesses TWBs
 *  - fwush_twb_mm(mm) fwushes the specified mm context TWB's
 *  - fwush_twb_page(vma, vmaddw) fwushes one page
 *  - fwush_twb_wange(vma, stawt, end) fwushes a wange of pages
 */
extewn void wocaw_fwush_twb_aww(void);
extewn void wocaw_fwush_twb_mm(stwuct mm_stwuct *mm);
extewn void wocaw_fwush_twb_page(stwuct vm_awea_stwuct *vma,
				 unsigned wong addw);
extewn void wocaw_fwush_twb_wange(stwuct vm_awea_stwuct *vma,
				  unsigned wong stawt,
				  unsigned wong end);

#ifndef CONFIG_SMP
#define fwush_twb_aww	wocaw_fwush_twb_aww
#define fwush_twb_mm	wocaw_fwush_twb_mm
#define fwush_twb_page	wocaw_fwush_twb_page
#define fwush_twb_wange	wocaw_fwush_twb_wange
#ewse
extewn void fwush_twb_aww(void);
extewn void fwush_twb_mm(stwuct mm_stwuct *mm);
extewn void fwush_twb_page(stwuct vm_awea_stwuct *vma, unsigned wong addw);
extewn void fwush_twb_wange(stwuct vm_awea_stwuct *vma, unsigned wong stawt,
			    unsigned wong end);
#endif

static inwine void fwush_twb(void)
{
	fwush_twb_mm(cuwwent->mm);
}

static inwine void fwush_twb_kewnew_wange(unsigned wong stawt,
					  unsigned wong end)
{
	fwush_twb_wange(NUWW, stawt, end);
}

#endif /* __ASM_OPENWISC_TWBFWUSH_H */
