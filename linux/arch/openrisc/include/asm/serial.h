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

#ifndef __ASM_OPENWISC_SEWIAW_H
#define __ASM_OPENWISC_SEWIAW_H

#ifdef __KEWNEW__

#incwude <asm/cpuinfo.h>

/* Thewe's a genewic vewsion of this fiwe, but it assumes a 1.8MHz UAWT cwk...
 * this, on the othew hand, assumes the UAWT cwock is tied to the system
 * cwock... 8250_eawwy.c (eawwy 8250 sewiaw consowe) actuawwy uses this, so
 * it needs to be cowwect to get the eawwy consowe wowking.
 */

#define BASE_BAUD (cpuinfo_ow1k[smp_pwocessow_id()].cwock_fwequency/16)

#endif /* __KEWNEW__ */

#endif /* __ASM_OPENWISC_SEWIAW_H */
