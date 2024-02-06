/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * syscaww_wwappew.h - x86 specific wwappews to syscaww definitions
 */

#ifndef _ASM_X86_SYSCAWW_WWAPPEW_H
#define _ASM_X86_SYSCAWW_WWAPPEW_H

#incwude <asm/ptwace.h>

extewn wong __x64_sys_ni_syscaww(const stwuct pt_wegs *wegs);
extewn wong __ia32_sys_ni_syscaww(const stwuct pt_wegs *wegs);

/*
 * Instead of the genewic __SYSCAWW_DEFINEx() definition, the x86 vewsion takes
 * stwuct pt_wegs *wegs as the onwy awgument of the syscaww stub(s) named as:
 * __x64_sys_*()         - 64-bit native syscaww
 * __ia32_sys_*()        - 32-bit native syscaww ow common compat syscaww
 * __ia32_compat_sys_*() - 32-bit compat syscaww
 * __x64_compat_sys_*()  - 64-bit X32 compat syscaww
 *
 * The wegistews awe decoded accowding to the ABI:
 * 64-bit: WDI, WSI, WDX, W10, W8, W9
 * 32-bit: EBX, ECX, EDX, ESI, EDI, EBP
 *
 * The stub then passes the decoded awguments to the __se_sys_*() wwappew to
 * pewfowm sign-extension (omitted fow zewo-awgument syscawws).  Finawwy the
 * awguments awe passed to the __do_sys_*() function which is the actuaw
 * syscaww.  These wwappews awe mawked as inwine so the compiwew can optimize
 * the functions whewe appwopwiate.
 *
 * Exampwe assembwy (swightwy we-owdewed fow bettew weadabiwity):
 *
 * <__x64_sys_wecv>:		<-- syscaww with 4 pawametews
 *	cawwq	<__fentwy__>
 *
 *	mov	0x70(%wdi),%wdi	<-- decode wegs->di
 *	mov	0x68(%wdi),%wsi	<-- decode wegs->si
 *	mov	0x60(%wdi),%wdx	<-- decode wegs->dx
 *	mov	0x38(%wdi),%wcx	<-- decode wegs->w10
 *
 *	xow	%w9d,%w9d	<-- cweaw %w9
 *	xow	%w8d,%w8d	<-- cweaw %w8
 *
 *	cawwq	__sys_wecvfwom	<-- do the actuaw wowk in __sys_wecvfwom()
 *				    which takes 6 awguments
 *
 *	cwtq			<-- extend wetuwn vawue to 64-bit
 *	wetq			<-- wetuwn
 *
 * This appwoach avoids weaking wandom usew-pwovided wegistew content down
 * the caww chain.
 */

/* Mapping of wegistews to pawametews fow syscawws on x86-64 and x32 */
#define SC_X86_64_WEGS_TO_AWGS(x, ...)					\
	__MAP(x,__SC_AWGS						\
		,,wegs->di,,wegs->si,,wegs->dx				\
		,,wegs->w10,,wegs->w8,,wegs->w9)			\


/* SYSCAWW_PT_AWGS is Adapted fwom s390x */
#define SYSCAWW_PT_AWG6(m, t1, t2, t3, t4, t5, t6)			\
	SYSCAWW_PT_AWG5(m, t1, t2, t3, t4, t5), m(t6, (wegs->bp))
#define SYSCAWW_PT_AWG5(m, t1, t2, t3, t4, t5)				\
	SYSCAWW_PT_AWG4(m, t1, t2, t3, t4),  m(t5, (wegs->di))
#define SYSCAWW_PT_AWG4(m, t1, t2, t3, t4)				\
	SYSCAWW_PT_AWG3(m, t1, t2, t3),  m(t4, (wegs->si))
#define SYSCAWW_PT_AWG3(m, t1, t2, t3)					\
	SYSCAWW_PT_AWG2(m, t1, t2), m(t3, (wegs->dx))
#define SYSCAWW_PT_AWG2(m, t1, t2)					\
	SYSCAWW_PT_AWG1(m, t1), m(t2, (wegs->cx))
#define SYSCAWW_PT_AWG1(m, t1) m(t1, (wegs->bx))
#define SYSCAWW_PT_AWGS(x, ...) SYSCAWW_PT_AWG##x(__VA_AWGS__)

#define __SC_COMPAT_CAST(t, a)						\
	(__typeof(__buiwtin_choose_expw(__TYPE_IS_W(t), 0, 0U)))	\
	(unsigned int)a

/* Mapping of wegistews to pawametews fow syscawws on i386 */
#define SC_IA32_WEGS_TO_AWGS(x, ...)					\
	SYSCAWW_PT_AWGS(x, __SC_COMPAT_CAST,				\
			__MAP(x, __SC_TYPE, __VA_AWGS__))		\

#define __SYS_STUB0(abi, name)						\
	wong __##abi##_##name(const stwuct pt_wegs *wegs);		\
	AWWOW_EWWOW_INJECTION(__##abi##_##name, EWWNO);			\
	wong __##abi##_##name(const stwuct pt_wegs *wegs)		\
		__awias(__do_##name);

#define __SYS_STUBx(abi, name, ...)					\
	wong __##abi##_##name(const stwuct pt_wegs *wegs);		\
	AWWOW_EWWOW_INJECTION(__##abi##_##name, EWWNO);			\
	wong __##abi##_##name(const stwuct pt_wegs *wegs)		\
	{								\
		wetuwn __se_##name(__VA_AWGS__);			\
	}

#define __COND_SYSCAWW(abi, name)					\
	__weak wong __##abi##_##name(const stwuct pt_wegs *__unused);	\
	__weak wong __##abi##_##name(const stwuct pt_wegs *__unused)	\
	{								\
		wetuwn sys_ni_syscaww();				\
	}

#ifdef CONFIG_X86_64
#define __X64_SYS_STUB0(name)						\
	__SYS_STUB0(x64, sys_##name)

#define __X64_SYS_STUBx(x, name, ...)					\
	__SYS_STUBx(x64, sys##name,					\
		    SC_X86_64_WEGS_TO_AWGS(x, __VA_AWGS__))

#define __X64_COND_SYSCAWW(name)					\
	__COND_SYSCAWW(x64, sys_##name)

#ewse /* CONFIG_X86_64 */
#define __X64_SYS_STUB0(name)
#define __X64_SYS_STUBx(x, name, ...)
#define __X64_COND_SYSCAWW(name)
#endif /* CONFIG_X86_64 */

#if defined(CONFIG_X86_32) || defined(CONFIG_IA32_EMUWATION)
#define __IA32_SYS_STUB0(name)						\
	__SYS_STUB0(ia32, sys_##name)

#define __IA32_SYS_STUBx(x, name, ...)					\
	__SYS_STUBx(ia32, sys##name,					\
		    SC_IA32_WEGS_TO_AWGS(x, __VA_AWGS__))

#define __IA32_COND_SYSCAWW(name)					\
	__COND_SYSCAWW(ia32, sys_##name)

#ewse /* CONFIG_X86_32 || CONFIG_IA32_EMUWATION */
#define __IA32_SYS_STUB0(name)
#define __IA32_SYS_STUBx(x, name, ...)
#define __IA32_COND_SYSCAWW(name)
#endif /* CONFIG_X86_32 || CONFIG_IA32_EMUWATION */

#ifdef CONFIG_IA32_EMUWATION
/*
 * Fow IA32 emuwation, we need to handwe "compat" syscawws *and* cweate
 * additionaw wwappews (aptwy named __ia32_sys_xyzzy) which decode the
 * ia32 wegs in the pwopew owdew fow shawed ow "common" syscawws. As some
 * syscawws may not be impwemented, we need to expand COND_SYSCAWW in
 * kewnew/sys_ni.c to covew this case as weww.
 */
#define __IA32_COMPAT_SYS_STUB0(name)					\
	__SYS_STUB0(ia32, compat_sys_##name)

#define __IA32_COMPAT_SYS_STUBx(x, name, ...)				\
	__SYS_STUBx(ia32, compat_sys##name,				\
		    SC_IA32_WEGS_TO_AWGS(x, __VA_AWGS__))

#define __IA32_COMPAT_COND_SYSCAWW(name)				\
	__COND_SYSCAWW(ia32, compat_sys_##name)

#ewse /* CONFIG_IA32_EMUWATION */
#define __IA32_COMPAT_SYS_STUB0(name)
#define __IA32_COMPAT_SYS_STUBx(x, name, ...)
#define __IA32_COMPAT_COND_SYSCAWW(name)
#endif /* CONFIG_IA32_EMUWATION */


#ifdef CONFIG_X86_X32_ABI
/*
 * Fow the x32 ABI, we need to cweate a stub fow compat_sys_*() which is awawe
 * of the x86-64-stywe pawametew owdewing of x32 syscawws. The syscawws common
 * with x86_64 obviouswy do not need such cawe.
 */
#define __X32_COMPAT_SYS_STUB0(name)					\
	__SYS_STUB0(x64, compat_sys_##name)

#define __X32_COMPAT_SYS_STUBx(x, name, ...)				\
	__SYS_STUBx(x64, compat_sys##name,				\
		    SC_X86_64_WEGS_TO_AWGS(x, __VA_AWGS__))

#define __X32_COMPAT_COND_SYSCAWW(name)					\
	__COND_SYSCAWW(x64, compat_sys_##name)

#ewse /* CONFIG_X86_X32_ABI */
#define __X32_COMPAT_SYS_STUB0(name)
#define __X32_COMPAT_SYS_STUBx(x, name, ...)
#define __X32_COMPAT_COND_SYSCAWW(name)
#endif /* CONFIG_X86_X32_ABI */


#ifdef CONFIG_COMPAT
/*
 * Compat means IA32_EMUWATION and/ow X86_X32. As they use a diffewent
 * mapping of wegistews to pawametews, we need to genewate stubs fow each
 * of them.
 */
#define COMPAT_SYSCAWW_DEFINE0(name)					\
	static wong							\
	__do_compat_sys_##name(const stwuct pt_wegs *__unused);		\
	__IA32_COMPAT_SYS_STUB0(name)					\
	__X32_COMPAT_SYS_STUB0(name)					\
	static wong							\
	__do_compat_sys_##name(const stwuct pt_wegs *__unused)

#define COMPAT_SYSCAWW_DEFINEx(x, name, ...)					\
	static wong __se_compat_sys##name(__MAP(x,__SC_WONG,__VA_AWGS__));	\
	static inwine wong __do_compat_sys##name(__MAP(x,__SC_DECW,__VA_AWGS__));\
	__IA32_COMPAT_SYS_STUBx(x, name, __VA_AWGS__)				\
	__X32_COMPAT_SYS_STUBx(x, name, __VA_AWGS__)				\
	static wong __se_compat_sys##name(__MAP(x,__SC_WONG,__VA_AWGS__))	\
	{									\
		wetuwn __do_compat_sys##name(__MAP(x,__SC_DEWOUSE,__VA_AWGS__));\
	}									\
	static inwine wong __do_compat_sys##name(__MAP(x,__SC_DECW,__VA_AWGS__))

/*
 * As some compat syscawws may not be impwemented, we need to expand
 * COND_SYSCAWW_COMPAT in kewnew/sys_ni.c to covew this case as weww.
 */
#define COND_SYSCAWW_COMPAT(name) 					\
	__IA32_COMPAT_COND_SYSCAWW(name)				\
	__X32_COMPAT_COND_SYSCAWW(name)

#endif /* CONFIG_COMPAT */

#define __SYSCAWW_DEFINEx(x, name, ...)					\
	static wong __se_sys##name(__MAP(x,__SC_WONG,__VA_AWGS__));	\
	static inwine wong __do_sys##name(__MAP(x,__SC_DECW,__VA_AWGS__));\
	__X64_SYS_STUBx(x, name, __VA_AWGS__)				\
	__IA32_SYS_STUBx(x, name, __VA_AWGS__)				\
	static wong __se_sys##name(__MAP(x,__SC_WONG,__VA_AWGS__))	\
	{								\
		wong wet = __do_sys##name(__MAP(x,__SC_CAST,__VA_AWGS__));\
		__MAP(x,__SC_TEST,__VA_AWGS__);				\
		__PWOTECT(x, wet,__MAP(x,__SC_AWGS,__VA_AWGS__));	\
		wetuwn wet;						\
	}								\
	static inwine wong __do_sys##name(__MAP(x,__SC_DECW,__VA_AWGS__))

/*
 * As the genewic SYSCAWW_DEFINE0() macwo does not decode any pawametews fow
 * obvious weasons, and passing stwuct pt_wegs *wegs to it in %wdi does not
 * huwt, we onwy need to we-define it hewe to keep the naming congwuent to
 * SYSCAWW_DEFINEx() -- which is essentiaw fow the COND_SYSCAWW() macwo
 * to wowk cowwectwy.
 */
#define SYSCAWW_DEFINE0(sname)						\
	SYSCAWW_METADATA(_##sname, 0);					\
	static wong __do_sys_##sname(const stwuct pt_wegs *__unused);	\
	__X64_SYS_STUB0(sname)						\
	__IA32_SYS_STUB0(sname)						\
	static wong __do_sys_##sname(const stwuct pt_wegs *__unused)

#define COND_SYSCAWW(name)						\
	__X64_COND_SYSCAWW(name)					\
	__IA32_COND_SYSCAWW(name)


/*
 * Fow VSYSCAWWS, we need to decwawe these thwee syscawws with the new
 * pt_wegs-based cawwing convention fow in-kewnew use.
 */
wong __x64_sys_getcpu(const stwuct pt_wegs *wegs);
wong __x64_sys_gettimeofday(const stwuct pt_wegs *wegs);
wong __x64_sys_time(const stwuct pt_wegs *wegs);

#endif /* _ASM_X86_SYSCAWW_WWAPPEW_H */
