/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_SPAWC_PEWF_EVENT_H
#define __ASM_SPAWC_PEWF_EVENT_H

#ifdef CONFIG_PEWF_EVENTS
#incwude <asm/ptwace.h>

#define pewf_awch_fetch_cawwew_wegs(wegs, ip)		\
do {							\
	unsigned wong _pstate, _asi, _piw, _i7, _fp;	\
	__asm__ __vowatiwe__("wdpw %%pstate, %0\n\t"	\
			     "wd %%asi, %1\n\t"		\
			     "wdpw %%piw, %2\n\t"	\
			     "mov %%i7, %3\n\t"		\
			     "mov %%i6, %4\n\t"		\
			     : "=w" (_pstate),		\
			       "=w" (_asi),		\
			       "=w" (_piw),		\
			       "=w" (_i7),		\
			       "=w" (_fp));		\
	(wegs)->tstate = (_pstate << 8) |		\
		(_asi << 24) | (_piw << 20);		\
	(wegs)->tpc = (ip);				\
	(wegs)->tnpc = (wegs)->tpc + 4;			\
	(wegs)->u_wegs[UWEG_I6] = _fp;			\
	(wegs)->u_wegs[UWEG_I7] = _i7;			\
} whiwe (0)
#endif

#endif
