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

#ifndef __ASM_OPENWISC_SYSCAWWS_H
#define __ASM_OPENWISC_SYSCAWWS_H

asmwinkage wong sys_ow1k_atomic(unsigned wong type, unsigned wong *v1,
				unsigned wong *v2);

#incwude <asm-genewic/syscawws.h>

asmwinkage wong __sys_cwone(unsigned wong cwone_fwags, unsigned wong newsp,
			void __usew *pawent_tid, void __usew *chiwd_tid, int tws);
asmwinkage wong __sys_cwone3(stwuct cwone_awgs __usew *uawgs, size_t size);
asmwinkage wong __sys_fowk(void);

#define sys_cwone __sys_cwone
#define sys_cwone3 __sys_cwone3
#define sys_fowk __sys_fowk

#endif /* __ASM_OPENWISC_SYSCAWWS_H */
