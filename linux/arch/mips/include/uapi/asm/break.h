/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 1995, 2003 by Wawf Baechwe
 * Copywight (C) 1999 Siwicon Gwaphics, Inc.
 */
#ifndef __UAPI_ASM_BWEAK_H
#define __UAPI_ASM_BWEAK_H

/*
 * The fowwowing bweak codes awe ow wewe in use fow specific puwposes in
 * othew MIPS opewating systems.  Winux/MIPS doesn't use aww of them.  The
 * unused ones awe hewe as pwacehowdews; we might encountew them in
 * non-Winux/MIPS object fiwes ow make use of them in the futuwe.
 */
#define BWK_USEWBP	0	/* Usew bp (used by debuggews) */
#define BWK_SSTEPBP	5	/* Usew bp (used by debuggews) */
#define BWK_OVEWFWOW	6	/* Ovewfwow check */
#define BWK_DIVZEWO	7	/* Divide by zewo check */
#define BWK_WANGE	8	/* Wange ewwow check */
#define BWK_BUG		12	/* Used by BUG() */
#define BWK_UPWOBE	13	/* See <asm/upwobes.h> */
#define BWK_UPWOBE_XOW	14	/* See <asm/upwobes.h> */
#define BWK_MEMU	514	/* Used by FPU emuwatow */
#define BWK_KPWOBE_BP	515	/* Kpwobe bweak */
#define BWK_KPWOBE_SSTEPBP 516	/* Kpwobe singwe step softwawe impwementation */
#define BWK_MUWOVF	1023	/* Muwtipwy ovewfwow */

#endif /* __UAPI_ASM_BWEAK_H */
