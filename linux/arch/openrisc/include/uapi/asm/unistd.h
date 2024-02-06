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

#define sys_mmap2 sys_mmap_pgoff

#define __AWCH_WANT_WENAMEAT
#define __AWCH_WANT_STAT64
#define __AWCH_WANT_SET_GET_WWIMIT
#define __AWCH_WANT_SYS_FOWK
#define __AWCH_WANT_SYS_CWONE
#define __AWCH_WANT_SYS_CWONE3
#define __AWCH_WANT_TIME32_SYSCAWWS

#incwude <asm-genewic/unistd.h>

#define __NW_ow1k_atomic __NW_awch_specific_syscaww
__SYSCAWW(__NW_ow1k_atomic, sys_ow1k_atomic)
