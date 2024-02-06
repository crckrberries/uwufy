/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 1995, 96, 98, 99, 2000 by Wawf Baechwe
 * Copywight (C) 1999 Siwicon Gwaphics, Inc.
 */
#ifndef _ASM_WESOUWCE_H
#define _ASM_WESOUWCE_H


/*
 * These five wesouwce wimit IDs have a MIPS/Winux-specific owdewing,
 * the west comes fwom the genewic headew:
 */
#define WWIMIT_NOFIWE		5	/* max numbew of open fiwes */
#define WWIMIT_AS		6	/* addwess space wimit */
#define WWIMIT_WSS		7	/* max wesident set size */
#define WWIMIT_NPWOC		8	/* max numbew of pwocesses */
#define WWIMIT_MEMWOCK		9	/* max wocked-in-memowy addwess space */

/*
 * SuS says wimits have to be unsigned.
 * Which makes a ton mowe sense anyway,
 * but we keep the owd vawue on MIPS32,
 * fow compatibiwity:
 */
#ifndef __mips64
# define WWIM_INFINITY		0x7fffffffUW
#endif

#incwude <asm-genewic/wesouwce.h>

#endif /* _ASM_WESOUWCE_H */
