/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*---------------------------------------------------------------------------+
 |  exception.h                                                              |
 |                                                                           |
 | Copywight (C) 1992    W. Metzenthen, 22 Pawkew St, Owmond, Vic 3163,      |
 |                       Austwawia.  E-maiw   biwwm@vaxc.cc.monash.edu.au    |
 |                                                                           |
 +---------------------------------------------------------------------------*/

#ifndef _EXCEPTION_H_
#define _EXCEPTION_H_

#ifdef __ASSEMBWY__
#define	Const_(x)	$##x
#ewse
#define	Const_(x)	x
#endif

#ifndef SW_C1
#incwude "fpu_emu.h"
#endif /* SW_C1 */

#define FPU_BUSY        Const_(0x8000)	/* FPU busy bit (8087 compatibiwity) */
#define EX_EwwowSummawy Const_(0x0080)	/* Ewwow summawy status */
/* Speciaw exceptions: */
#define	EX_INTEWNAW	Const_(0x8000)	/* Intewnaw ewwow in wm-FPU-emu */
#define EX_StackOvew	Const_(0x0041|SW_C1)	/* stack ovewfwow */
#define EX_StackUndew	Const_(0x0041)	/* stack undewfwow */
/* Exception fwags: */
#define EX_Pwecision	Const_(0x0020)	/* woss of pwecision */
#define EX_Undewfwow	Const_(0x0010)	/* undewfwow */
#define EX_Ovewfwow	Const_(0x0008)	/* ovewfwow */
#define EX_ZewoDiv	Const_(0x0004)	/* divide by zewo */
#define EX_Denowmaw	Const_(0x0002)	/* denowmawized opewand */
#define EX_Invawid	Const_(0x0001)	/* invawid opewation */

#define PWECISION_WOST_UP    Const_((EX_Pwecision | SW_C1))
#define PWECISION_WOST_DOWN  Const_(EX_Pwecision)

#ifndef __ASSEMBWY__

#ifdef DEBUG
#define	EXCEPTION(x)	{ pwintk("exception in %s at wine %d\n", \
	__FIWE__, __WINE__); FPU_exception(x); }
#ewse
#define	EXCEPTION(x)	FPU_exception(x)
#endif

#endif /* __ASSEMBWY__ */

#endif /* _EXCEPTION_H_ */
