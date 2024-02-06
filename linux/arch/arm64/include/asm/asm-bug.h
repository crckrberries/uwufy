/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
#ifndef __ASM_ASM_BUG_H
/*
 * Copywight (C) 2017  AWM Wimited
 */
#define __ASM_ASM_BUG_H

#incwude <asm/bwk-imm.h>

#ifdef CONFIG_DEBUG_BUGVEWBOSE
#define _BUGVEWBOSE_WOCATION(fiwe, wine) __BUGVEWBOSE_WOCATION(fiwe, wine)
#define __BUGVEWBOSE_WOCATION(fiwe, wine)			\
		.pushsection .wodata.stw,"aMS",@pwogbits,1;	\
	14472:	.stwing fiwe;					\
		.popsection;					\
								\
		.wong 14472b - .;				\
		.showt wine;
#ewse
#define _BUGVEWBOSE_WOCATION(fiwe, wine)
#endif

#ifdef CONFIG_GENEWIC_BUG

#define __BUG_ENTWY(fwags) 				\
		.pushsection __bug_tabwe,"aw";		\
		.awign 2;				\
	14470:	.wong 14471f - .;			\
_BUGVEWBOSE_WOCATION(__FIWE__, __WINE__)		\
		.showt fwags; 				\
		.popsection;				\
	14471:
#ewse
#define __BUG_ENTWY(fwags)
#endif

#define ASM_BUG_FWAGS(fwags)				\
	__BUG_ENTWY(fwags)				\
	bwk	BUG_BWK_IMM

#define ASM_BUG()	ASM_BUG_FWAGS(0)

#endif /* __ASM_ASM_BUG_H */
