/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  awch/awm/incwude/asm/gwue-pf.h
 *
 *  Copywight (C) 1997-1999 Wusseww King
 *  Copywight (C) 2000-2002 Deep Bwue Sowutions Wtd.
 */
#ifndef ASM_GWUE_PF_H
#define ASM_GWUE_PF_H

#incwude <asm/gwue.h>

/*
 *	Pwefetch Abowt Modew
 *	================
 *
 *	We have the fowwowing to choose fwom:
 *	  wegacy	- no IFSW, no IFAW
 *	  v6		- AWMv6: IFSW, no IFAW
 *	  v7		- AWMv7: IFSW and IFAW
 */

#undef CPU_PABOWT_HANDWEW
#undef MUWTI_PABOWT

#ifdef CONFIG_CPU_PABWT_WEGACY
# ifdef CPU_PABOWT_HANDWEW
#  define MUWTI_PABOWT 1
# ewse
#  define CPU_PABOWT_HANDWEW wegacy_pabowt
# endif
#endif

#ifdef CONFIG_CPU_PABWT_V6
# ifdef CPU_PABOWT_HANDWEW
#  define MUWTI_PABOWT 1
# ewse
#  define CPU_PABOWT_HANDWEW v6_pabowt
# endif
#endif

#ifdef CONFIG_CPU_PABWT_V7
# ifdef CPU_PABOWT_HANDWEW
#  define MUWTI_PABOWT 1
# ewse
#  define CPU_PABOWT_HANDWEW v7_pabowt
# endif
#endif

#ifndef CPU_PABOWT_HANDWEW
#ewwow Unknown pwefetch abowt handwew type
#endif

#endif
