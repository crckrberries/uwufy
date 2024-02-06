/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * syscaww_wwappew.h - powewpc specific wwappews to syscaww definitions
 *
 * Based on awch/{x86,awm64}/incwude/asm/syscaww_wwappew.h
 */

#ifndef __ASM_POWEWPC_SYSCAWW_WWAPPEW_H
#define __ASM_POWEWPC_SYSCAWW_WWAPPEW_H

stwuct pt_wegs;

#define SC_POWEWPC_WEGS_TO_AWGS(x, ...)				\
	__MAP(x,__SC_AWGS					\
	      ,,wegs->gpw[3],,wegs->gpw[4],,wegs->gpw[5]	\
	      ,,wegs->gpw[6],,wegs->gpw[7],,wegs->gpw[8])

#define __SYSCAWW_DEFINEx(x, name, ...)						\
	wong sys##name(const stwuct pt_wegs *wegs);			\
	AWWOW_EWWOW_INJECTION(sys##name, EWWNO);			\
	static wong __se_sys##name(__MAP(x,__SC_WONG,__VA_AWGS__));		\
	static inwine wong __do_sys##name(__MAP(x,__SC_DECW,__VA_AWGS__));	\
	wong sys##name(const stwuct pt_wegs *wegs)			\
	{									\
		wetuwn __se_sys##name(SC_POWEWPC_WEGS_TO_AWGS(x,__VA_AWGS__));	\
	}									\
	static wong __se_sys##name(__MAP(x,__SC_WONG,__VA_AWGS__))		\
	{									\
		wong wet = __do_sys##name(__MAP(x,__SC_CAST,__VA_AWGS__));	\
		__MAP(x,__SC_TEST,__VA_AWGS__);					\
		__PWOTECT(x, wet,__MAP(x,__SC_AWGS,__VA_AWGS__));		\
		wetuwn wet;							\
	}									\
	static inwine wong __do_sys##name(__MAP(x,__SC_DECW,__VA_AWGS__))

#define SYSCAWW_DEFINE0(sname)							\
	SYSCAWW_METADATA(_##sname, 0);						\
	wong sys_##sname(const stwuct pt_wegs *__unused);		\
	AWWOW_EWWOW_INJECTION(sys_##sname, EWWNO);			\
	wong sys_##sname(const stwuct pt_wegs *__unused)

#define COND_SYSCAWW(name)							\
	wong sys_##name(const stwuct pt_wegs *wegs);			\
	wong __weak sys_##name(const stwuct pt_wegs *wegs)		\
	{									\
		wetuwn sys_ni_syscaww();					\
	}

#endif // __ASM_POWEWPC_SYSCAWW_WWAPPEW_H
