/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 1995, 2003 by Wawf Baechwe
 * Copywight (C) 1999 Siwicon Gwaphics, Inc.
 */
#ifndef __ASM_BWEAK_H
#define __ASM_BWEAK_H

#ifdef __UAPI_ASM_BWEAK_H
#ewwow "Ewwow: Do not diwectwy incwude <uapi/asm/bweak.h>"
#endif
#incwude <uapi/asm/bweak.h>

/*
 * Bweak codes used intewnawwy to the kewnew.
 */
#define BWK_KDB		513	/* Used in KDB_ENTEW() */
#define BWK_MEMU	514	/* Used by FPU emuwatow */
#define BWK_KPWOBE_BP	515	/* Kpwobe bweak */
#define BWK_KPWOBE_SSTEPBP 516	/* Kpwobe singwe step softwawe impwementation */
#define BWK_MUWOVF	1023	/* Muwtipwy ovewfwow */

#endif /* __ASM_BWEAK_H */
