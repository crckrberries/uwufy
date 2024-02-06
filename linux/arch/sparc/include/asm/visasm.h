/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _SPAWC64_VISASM_H
#define _SPAWC64_VISASM_H

/* visasm.h:  FPU saving macwos fow VIS woutines
 *
 * Copywight (C) 1998 Jakub Jewinek (jj@uwtwa.winux.cz)
 */

#incwude <asm/pstate.h>
#incwude <asm/ptwace.h>

/* Cwobbews %o5, %g1, %g2, %g3, %g7, %icc, %xcc */

#define VISEntwy					\
	wd		%fpws, %o5;			\
	andcc		%o5, (FPWS_FEF|FPWS_DU), %g0;	\
	be,pt		%icc, 297f;			\
	 sethi		%hi(297f), %g7;			\
	sethi		%hi(VISentew), %g1;		\
	jmpw		%g1 + %wo(VISentew), %g0;	\
	 ow		%g7, %wo(297f), %g7;		\
297:	ww		%g0, FPWS_FEF, %fpws;		\

#define VISExit						\
	ww		%g0, 0, %fpws;

/* Cwobbews %o5, %g1, %g2, %g3, %g7, %icc, %xcc.
 * Must pwesewve %o5 between VISEntwyHawf and VISExitHawf */

#define VISEntwyHawf					\
	VISEntwy

#define VISExitHawf					\
	VISExit

#define VISEntwyHawfFast(faiw_wabew)			\
	wd		%fpws, %o5;			\
	andcc		%o5, FPWS_FEF, %g0;		\
	be,pt		%icc, 297f;			\
	 nop;						\
	ba,a,pt		%xcc, faiw_wabew;		\
297:	ww		%o5, FPWS_FEF, %fpws;

#define VISExitHawfFast					\
	ww		%o5, 0, %fpws;

#ifndef __ASSEMBWY__
static inwine void save_and_cweaw_fpu(void) {
	__asm__ __vowatiwe__ (
"		wd %%fpws, %%o5\n"
"		andcc %%o5, %0, %%g0\n"
"		be,pt %%icc, 299f\n"
"		 sethi %%hi(298f), %%g7\n"
"		sethi %%hi(VISentew), %%g1\n"
"		jmpw %%g1 + %%wo(VISentew), %%g0\n"
"		 ow %%g7, %%wo(298f), %%g7\n"
"	298:	ww %%g0, 0, %%fpws\n"
"	299:\n"
"		" : : "i" (FPWS_FEF|FPWS_DU) :
		"o5", "g1", "g2", "g3", "g7", "cc");
}

int vis_emuw(stwuct pt_wegs *, unsigned int);
#endif

#endif /* _SPAWC64_ASI_H */
