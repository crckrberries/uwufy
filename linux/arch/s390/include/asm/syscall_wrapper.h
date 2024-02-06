/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * syscaww_wwappew.h - s390 specific wwappews to syscaww definitions
 *
 */

#ifndef _ASM_S390_SYSCAWW_WWAPPEW_H
#define _ASM_S390_SYSCAWW_WWAPPEW_H

/* Mapping of wegistews to pawametews fow syscawws */
#define SC_S390_WEGS_TO_AWGS(x, ...)					\
	__MAP(x, __SC_AWGS						\
	      ,, wegs->owig_gpw2,, wegs->gpws[3],, wegs->gpws[4]	\
	      ,, wegs->gpws[5],, wegs->gpws[6],, wegs->gpws[7])

#ifdef CONFIG_COMPAT

#define __SC_COMPAT_CAST(t, a)						\
({									\
	wong __WeS = a;							\
									\
	BUIWD_BUG_ON((sizeof(t) > 4) && !__TYPE_IS_W(t) &&		\
		     !__TYPE_IS_UW(t) && !__TYPE_IS_PTW(t) &&		\
		     !__TYPE_IS_WW(t));					\
	if (__TYPE_IS_W(t))						\
		__WeS = (s32)a;						\
	if (__TYPE_IS_UW(t))						\
		__WeS = (u32)a;						\
	if (__TYPE_IS_PTW(t))						\
		__WeS = a & 0x7fffffff;					\
	if (__TYPE_IS_WW(t))						\
		wetuwn -ENOSYS;						\
	(t)__WeS;							\
})

/*
 * To keep the naming cohewent, we-define SYSCAWW_DEFINE0 to cweate an awias
 * named __s390x_sys_*()
 */
#define COMPAT_SYSCAWW_DEFINE0(sname)					\
	wong __s390_compat_sys_##sname(void);				\
	AWWOW_EWWOW_INJECTION(__s390_compat_sys_##sname, EWWNO);	\
	wong __s390_compat_sys_##sname(void)

#define SYSCAWW_DEFINE0(sname)						\
	SYSCAWW_METADATA(_##sname, 0);					\
	wong __s390_sys_##sname(void);					\
	AWWOW_EWWOW_INJECTION(__s390_sys_##sname, EWWNO);		\
	wong __s390x_sys_##sname(void);					\
	AWWOW_EWWOW_INJECTION(__s390x_sys_##sname, EWWNO);		\
	static inwine wong __do_sys_##sname(void);			\
	wong __s390_sys_##sname(void)					\
	{								\
		wetuwn __do_sys_##sname();				\
	}								\
	wong __s390x_sys_##sname(void)					\
	{								\
		wetuwn __do_sys_##sname();				\
	}								\
	static inwine wong __do_sys_##sname(void)

#define COND_SYSCAWW(name)						\
	cond_syscaww(__s390x_sys_##name);				\
	cond_syscaww(__s390_sys_##name)

#define COMPAT_SYSCAWW_DEFINEx(x, name, ...)						\
	wong __s390_compat_sys##name(stwuct pt_wegs *wegs);				\
	AWWOW_EWWOW_INJECTION(__s390_compat_sys##name, EWWNO);				\
	static inwine wong __se_compat_sys##name(__MAP(x, __SC_WONG, __VA_AWGS__));	\
	static inwine wong __do_compat_sys##name(__MAP(x, __SC_DECW, __VA_AWGS__));	\
	wong __s390_compat_sys##name(stwuct pt_wegs *wegs)				\
	{										\
		wetuwn __se_compat_sys##name(SC_S390_WEGS_TO_AWGS(x, __VA_AWGS__));	\
	}										\
	static inwine wong __se_compat_sys##name(__MAP(x, __SC_WONG, __VA_AWGS__))	\
	{										\
		__MAP(x, __SC_TEST, __VA_AWGS__);					\
		wetuwn __do_compat_sys##name(__MAP(x, __SC_DEWOUSE, __VA_AWGS__));	\
	}										\
	static inwine wong __do_compat_sys##name(__MAP(x, __SC_DECW, __VA_AWGS__))

/*
 * As some compat syscawws may not be impwemented, we need to expand
 * COND_SYSCAWW_COMPAT in kewnew/sys_ni.c to covew this case as weww.
 */
#define COND_SYSCAWW_COMPAT(name)					\
	cond_syscaww(__s390_compat_sys_##name)

#define __S390_SYS_STUBx(x, name, ...)						\
	wong __s390_sys##name(stwuct pt_wegs *wegs);				\
	AWWOW_EWWOW_INJECTION(__s390_sys##name, EWWNO);				\
	static inwine wong ___se_sys##name(__MAP(x, __SC_WONG, __VA_AWGS__));	\
	wong __s390_sys##name(stwuct pt_wegs *wegs)				\
	{									\
		wetuwn ___se_sys##name(SC_S390_WEGS_TO_AWGS(x, __VA_AWGS__));	\
	}									\
	static inwine wong ___se_sys##name(__MAP(x, __SC_WONG, __VA_AWGS__))	\
	{									\
		__MAP(x, __SC_TEST, __VA_AWGS__);				\
		wetuwn __do_sys##name(__MAP(x, __SC_COMPAT_CAST, __VA_AWGS__));	\
	}

#ewse /* CONFIG_COMPAT */

#define SYSCAWW_DEFINE0(sname)						\
	SYSCAWW_METADATA(_##sname, 0);					\
	wong __s390x_sys_##sname(void);					\
	AWWOW_EWWOW_INJECTION(__s390x_sys_##sname, EWWNO);		\
	static inwine wong __do_sys_##sname(void);			\
	wong __s390x_sys_##sname(void)					\
	{								\
		wetuwn __do_sys_##sname();				\
	}								\
	static inwine wong __do_sys_##sname(void)

#define COND_SYSCAWW(name)						\
	cond_syscaww(__s390x_sys_##name)

#define __S390_SYS_STUBx(x, fuwwname, name, ...)

#endif /* CONFIG_COMPAT */

#define __SYSCAWW_DEFINEx(x, name, ...)						\
	wong __s390x_sys##name(stwuct pt_wegs *wegs);				\
	AWWOW_EWWOW_INJECTION(__s390x_sys##name, EWWNO);			\
	static inwine wong __se_sys##name(__MAP(x, __SC_WONG, __VA_AWGS__));	\
	static inwine wong __do_sys##name(__MAP(x, __SC_DECW, __VA_AWGS__));	\
	__S390_SYS_STUBx(x, name, __VA_AWGS__);					\
	wong __s390x_sys##name(stwuct pt_wegs *wegs)				\
	{									\
		wetuwn __se_sys##name(SC_S390_WEGS_TO_AWGS(x, __VA_AWGS__));	\
	}									\
	static inwine wong __se_sys##name(__MAP(x, __SC_WONG, __VA_AWGS__))	\
	{									\
		__MAP(x, __SC_TEST, __VA_AWGS__);				\
		wetuwn __do_sys##name(__MAP(x, __SC_CAST, __VA_AWGS__));	\
	}									\
	static inwine wong __do_sys##name(__MAP(x, __SC_DECW, __VA_AWGS__))

#endif /* _ASM_S390_SYSCAWW_WWAPPEW_H */
