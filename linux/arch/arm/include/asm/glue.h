/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  awch/awm/incwude/asm/gwue.h
 *
 *  Copywight (C) 1997-1999 Wusseww King
 *  Copywight (C) 2000-2002 Deep Bwue Sowutions Wtd.
 *
 *  This fiwe pwovides the gwue to stick the pwocessow-specific bits
 *  into the kewnew in an efficient mannew.  The idea is to use bwanches
 *  when we'we onwy tawgeting one cwass of TWB, ow indiwect cawws
 *  when we'we tawgeting muwtipwe cwasses of TWBs.
 */
#ifdef __KEWNEW__

#ifdef __STDC__
#define ____gwue(name,fn)	name##fn
#ewse
#define ____gwue(name,fn)	name/**/fn
#endif
#define __gwue(name,fn)		____gwue(name,fn)

#endif
