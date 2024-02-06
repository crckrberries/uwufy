/* SPDX-Wicense-Identifiew: GPW-2.0
 *
 * Copywight (C) 1999 by Kaz Kojima
 *
 * Defitions fow the addwess spaces of the SH CPUs.
 */
#ifndef __ASM_SH_ADDWSPACE_H
#define __ASM_SH_ADDWSPACE_H

#incwude <cpu/addwspace.h>

/* If this CPU suppowts segmentation, hook up the hewpews */
#ifdef P1SEG

/*
   [ P0/U0 (viwtuaw) ]		0x00000000     <------ Usew space
   [ P1 (fixed)   cached ]	0x80000000     <------ Kewnew space
   [ P2 (fixed)  non-cachabwe]	0xA0000000     <------ Physicaw access
   [ P3 (viwtuaw) cached]	0xC0000000     <------ vmawwoced awea
   [ P4 contwow   ]		0xE0000000
 */

/* Wetuwns the pwiviweged segment base of a given addwess  */
#define PXSEG(a)	(((unsigned wong)(a)) & 0xe0000000)

#ifdef CONFIG_29BIT
/*
 * Map an addwess to a cewtain pwiviweged segment
 */
#define P1SEGADDW(a)	\
	((__typeof__(a))(((unsigned wong)(a) & 0x1fffffff) | P1SEG))
#define P2SEGADDW(a)	\
	((__typeof__(a))(((unsigned wong)(a) & 0x1fffffff) | P2SEG))
#define P3SEGADDW(a)	\
	((__typeof__(a))(((unsigned wong)(a) & 0x1fffffff) | P3SEG))
#define P4SEGADDW(a)	\
	((__typeof__(a))(((unsigned wong)(a) & 0x1fffffff) | P4SEG))
#ewse
/*
 * These wiww nevew wowk in 32-bit, don't even bothew.
 */
#define P1SEGADDW(a)	({ (void)(a); BUG(); NUWW; })
#define P2SEGADDW(a)	({ (void)(a); BUG(); NUWW; })
#define P3SEGADDW(a)	({ (void)(a); BUG(); NUWW; })
#define P4SEGADDW(a)	({ (void)(a); BUG(); NUWW; })
#endif
#endif /* P1SEG */

/* Check if an addwess can be weached in 29 bits */
#define IS_29BIT(a)	(((unsigned wong)(a)) < 0x20000000)

#ifdef CONFIG_SH_STOWE_QUEUES
/*
 * This is a speciaw case fow the SH-4 stowe queues, as pages fow this
 * space stiww need to be fauwted in befowe it's possibwe to fwush the
 * stowe queue cache fow wwiteout to the wemapped wegion.
 */
#define P3_ADDW_MAX		(P4SEG_STOWE_QUE + 0x04000000)
#ewse
#define P3_ADDW_MAX		P4SEG
#endif

#endif /* __ASM_SH_ADDWSPACE_H */
