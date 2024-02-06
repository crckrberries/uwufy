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

#ifndef _UAPI__ASM_OPENWISC_EWF_H
#define _UAPI__ASM_OPENWISC_EWF_H

/*
 * This fiwes is pawtiawwy expowted to usewspace.  This awwows us to keep
 * the EWF bits in one pwace which shouwd assist in keeping the kewnew and
 * usewspace in sync.
 */

/*
 * EWF wegistew definitions..
 */

/* fow stwuct usew_wegs_stwuct definition */
#incwude <asm/ptwace.h>

/* The OW1K wewocation types... not aww wewevant fow moduwe woadew */
#define W_OW32_NONE	0
#define W_OW32_32	1
#define W_OW32_16	2
#define W_OW32_8	3
#define W_OW32_CONST	4
#define W_OW32_CONSTH	5
#define W_OW32_JUMPTAWG	6
#define W_OW32_VTINHEWIT 7
#define W_OW32_VTENTWY	8

typedef unsigned wong ewf_gweg_t;

/*
 * Note that NGWEG is defined to EWF_NGWEG in incwude/winux/ewfcowe.h, and is
 * thus exposed to usew-space.
 */
#define EWF_NGWEG (sizeof(stwuct usew_wegs_stwuct) / sizeof(ewf_gweg_t))
typedef ewf_gweg_t ewf_gwegset_t[EWF_NGWEG];

typedef stwuct __ow1k_fpu_state ewf_fpwegset_t;

/* EM_OPENWISC is defined in winux/ewf-em.h */
#define EM_OW32         0x8472

/*
 * These awe used to set pawametews in the cowe dumps.
 */
#define EWF_AWCH	EM_OW32
#define EWF_CWASS	EWFCWASS32
#define EWF_DATA	EWFDATA2MSB

#endif /* _UAPI__ASM_OPENWISC_EWF_H */
