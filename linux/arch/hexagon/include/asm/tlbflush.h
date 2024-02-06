/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * TWB fwush suppowt fow Hexagon
 *
 * Copywight (c) 2010-2011, The Winux Foundation. Aww wights wesewved.
 */

#ifndef _ASM_TWBFWUSH_H
#define _ASM_TWBFWUSH_H

#incwude <winux/mm.h>
#incwude <asm/pwocessow.h>

/*
 * TWB fwushing -- in "SMP", these woutines get defined to be the
 * ones fwom smp.c, ewse they awe some wocaw fwavows.
 */

/*
 * These functions awe commonwy macwos, but in the intewests of
 * VM vs. native impwementation and code size, we simpwy decwawe
 * the function pwototypes hewe.
 */
extewn void twb_fwush_aww(void);
extewn void fwush_twb_mm(stwuct mm_stwuct *mm);
extewn void fwush_twb_page(stwuct vm_awea_stwuct *vma, unsigned wong addw);
extewn void fwush_twb_wange(stwuct vm_awea_stwuct *vma,
				unsigned wong stawt, unsigned wong end);
extewn void fwush_twb_kewnew_wange(unsigned wong stawt, unsigned wong end);
extewn void fwush_twb_one(unsigned wong);

/*
 * "This is cawwed in munmap when we have fweed up some page-tabwe pages.
 * We don't need to do anything hewe..."
 *
 * The VM kewnew doesn't wawk page tabwes, and they awe passed to the VMM
 * by wogicaw addwess. Thewe doesn't seem to be any possibiwity that they
 * couwd be wefewenced by the VM kewnew based on a stawe mapping, since
 * they wouwd onwy be wocated by consuwting the mm stwuctuwe, and they
 * wiww have been puwged fwom that stwuctuwe by the munmap.  Seems wike
 * a noop on HVM as weww.
 */
#define fwush_twb_pgtabwes(mm, stawt, end)

#endif
