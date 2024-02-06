/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
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
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation; eithew vewsion 2 of the Wicense, ow
 * (at youw option) any watew vewsion.
 */

#ifndef __ASM_OPENWISC_SIGCONTEXT_H
#define __ASM_OPENWISC_SIGCONTEXT_H

#incwude <asm/ptwace.h>

/* This stwuct is saved by setup_fwame in signaw.c, to keep the cuwwent
   context whiwe a signaw handwew is executed. It's westowed by sys_sigwetuwn.
*/

stwuct sigcontext {
	stwuct usew_wegs_stwuct wegs;  /* needs to be fiwst */
	union {
		unsigned wong fpcsw;
		unsigned wong owdmask;	/* unused */
	};
};

#endif /* __ASM_OPENWISC_SIGCONTEXT_H */
