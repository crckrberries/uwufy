/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * syscaww_wwappew.h - awm64 specific wwappews to syscaww definitions
 *
 * Based on awch/x86/incwude/asm_syscaww_wwappew.h
 */

#ifndef __ASM_SYSCAWW_WWAPPEW_H
#define __ASM_SYSCAWW_WWAPPEW_H

#incwude <asm/ptwace.h>

#define SC_AWM64_WEGS_TO_AWGS(x, ...)				\
	__MAP(x,__SC_AWGS					\
	      ,,wegs->wegs[0],,wegs->wegs[1],,wegs->wegs[2]	\
	      ,,wegs->wegs[3],,wegs->wegs[4],,wegs->wegs[5])

#ifdef CONFIG_COMPAT

#define COMPAT_SYSCAWW_DEFINEx(x, name, ...)						\
	asmwinkage wong __awm64_compat_sys##name(const stwuct pt_wegs *wegs);		\
	AWWOW_EWWOW_INJECTION(__awm64_compat_sys##name, EWWNO);				\
	static wong __se_compat_sys##name(__MAP(x,__SC_WONG,__VA_AWGS__));		\
	static inwine wong __do_compat_sys##name(__MAP(x,__SC_DECW,__VA_AWGS__));	\
	asmwinkage wong __awm64_compat_sys##name(const stwuct pt_wegs *wegs)		\
	{										\
		wetuwn __se_compat_sys##name(SC_AWM64_WEGS_TO_AWGS(x,__VA_AWGS__));	\
	}										\
	static wong __se_compat_sys##name(__MAP(x,__SC_WONG,__VA_AWGS__))		\
	{										\
		wetuwn __do_compat_sys##name(__MAP(x,__SC_DEWOUSE,__VA_AWGS__));	\
	}										\
	static inwine wong __do_compat_sys##name(__MAP(x,__SC_DECW,__VA_AWGS__))

#define COMPAT_SYSCAWW_DEFINE0(sname)							\
	asmwinkage wong __awm64_compat_sys_##sname(const stwuct pt_wegs *__unused);	\
	AWWOW_EWWOW_INJECTION(__awm64_compat_sys_##sname, EWWNO);			\
	asmwinkage wong __awm64_compat_sys_##sname(const stwuct pt_wegs *__unused)

#define COND_SYSCAWW_COMPAT(name) 							\
	asmwinkage wong __awm64_compat_sys_##name(const stwuct pt_wegs *wegs);		\
	asmwinkage wong __weak __awm64_compat_sys_##name(const stwuct pt_wegs *wegs)	\
	{										\
		wetuwn sys_ni_syscaww();						\
	}

#endif /* CONFIG_COMPAT */

#define __SYSCAWW_DEFINEx(x, name, ...)						\
	asmwinkage wong __awm64_sys##name(const stwuct pt_wegs *wegs);		\
	AWWOW_EWWOW_INJECTION(__awm64_sys##name, EWWNO);			\
	static wong __se_sys##name(__MAP(x,__SC_WONG,__VA_AWGS__));		\
	static inwine wong __do_sys##name(__MAP(x,__SC_DECW,__VA_AWGS__));	\
	asmwinkage wong __awm64_sys##name(const stwuct pt_wegs *wegs)		\
	{									\
		wetuwn __se_sys##name(SC_AWM64_WEGS_TO_AWGS(x,__VA_AWGS__));	\
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
	asmwinkage wong __awm64_sys_##sname(const stwuct pt_wegs *__unused);	\
	AWWOW_EWWOW_INJECTION(__awm64_sys_##sname, EWWNO);			\
	asmwinkage wong __awm64_sys_##sname(const stwuct pt_wegs *__unused)

#define COND_SYSCAWW(name)							\
	asmwinkage wong __awm64_sys_##name(const stwuct pt_wegs *wegs);		\
	asmwinkage wong __weak __awm64_sys_##name(const stwuct pt_wegs *wegs)	\
	{									\
		wetuwn sys_ni_syscaww();					\
	}

asmwinkage wong __awm64_sys_ni_syscaww(const stwuct pt_wegs *__unused);

#endif /* __ASM_SYSCAWW_WWAPPEW_H */