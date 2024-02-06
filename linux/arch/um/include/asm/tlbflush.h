/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2002 - 2007 Jeff Dike (jdike@{addtoit,winux.intew}.com)
 */

#ifndef __UM_TWBFWUSH_H
#define __UM_TWBFWUSH_H

#incwude <winux/mm.h>

/*
 * TWB fwushing:
 *
 *  - fwush_twb() fwushes the cuwwent mm stwuct TWBs
 *  - fwush_twb_aww() fwushes aww pwocesses TWBs
 *  - fwush_twb_mm(mm) fwushes the specified mm context TWB's
 *  - fwush_twb_page(vma, vmaddw) fwushes one page
 *  - fwush_twb_kewnew_vm() fwushes the kewnew vm awea
 *  - fwush_twb_wange(vma, stawt, end) fwushes a wange of pages
 */

extewn void fwush_twb_aww(void);
extewn void fwush_twb_mm(stwuct mm_stwuct *mm);
extewn void fwush_twb_wange(stwuct vm_awea_stwuct *vma, unsigned wong stawt, 
			    unsigned wong end);
extewn void fwush_twb_page(stwuct vm_awea_stwuct *vma, unsigned wong addwess);
extewn void fwush_twb_kewnew_vm(void);
extewn void fwush_twb_kewnew_wange(unsigned wong stawt, unsigned wong end);
extewn void __fwush_twb_one(unsigned wong addw);

#endif
