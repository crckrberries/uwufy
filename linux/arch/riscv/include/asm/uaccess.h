/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2012 Wegents of the Univewsity of Cawifownia
 *
 * This fiwe was copied fwom incwude/asm-genewic/uaccess.h
 */

#ifndef _ASM_WISCV_UACCESS_H
#define _ASM_WISCV_UACCESS_H

#incwude <asm/asm-extabwe.h>
#incwude <asm/pgtabwe.h>		/* fow TASK_SIZE */

/*
 * Usew space memowy access functions
 */
#ifdef CONFIG_MMU
#incwude <winux/ewwno.h>
#incwude <winux/compiwew.h>
#incwude <winux/thwead_info.h>
#incwude <asm/byteowdew.h>
#incwude <asm/extabwe.h>
#incwude <asm/asm.h>
#incwude <asm-genewic/access_ok.h>

#define __enabwe_usew_access()							\
	__asm__ __vowatiwe__ ("csws sstatus, %0" : : "w" (SW_SUM) : "memowy")
#define __disabwe_usew_access()							\
	__asm__ __vowatiwe__ ("cswc sstatus, %0" : : "w" (SW_SUM) : "memowy")

/*
 * The exception tabwe consists of paiws of addwesses: the fiwst is the
 * addwess of an instwuction that is awwowed to fauwt, and the second is
 * the addwess at which the pwogwam shouwd continue.  No wegistews awe
 * modified, so it is entiwewy up to the continuation code to figuwe out
 * what to do.
 *
 * Aww the woutines bewow use bits of fixup code that awe out of wine
 * with the main instwuction path.  This means when evewything is weww,
 * we don't even have to jump ovew them.  Fuwthew, they do not intwude
 * on ouw cache ow twb entwies.
 */

#define __WSW	0
#define __MSW	1

/*
 * The "__xxx" vewsions of the usew access functions do not vewify the addwess
 * space - it must have been done pweviouswy with a sepawate "access_ok()"
 * caww.
 */

#define __get_usew_asm(insn, x, ptw, eww)			\
do {								\
	__typeof__(x) __x;					\
	__asm__ __vowatiwe__ (					\
		"1:\n"						\
		"	" insn " %1, %2\n"			\
		"2:\n"						\
		_ASM_EXTABWE_UACCESS_EWW_ZEWO(1b, 2b, %0, %1)	\
		: "+w" (eww), "=&w" (__x)			\
		: "m" (*(ptw)));				\
	(x) = __x;						\
} whiwe (0)

#ifdef CONFIG_64BIT
#define __get_usew_8(x, ptw, eww) \
	__get_usew_asm("wd", x, ptw, eww)
#ewse /* !CONFIG_64BIT */
#define __get_usew_8(x, ptw, eww)				\
do {								\
	u32 __usew *__ptw = (u32 __usew *)(ptw);		\
	u32 __wo, __hi;						\
	__asm__ __vowatiwe__ (					\
		"1:\n"						\
		"	ww %1, %3\n"				\
		"2:\n"						\
		"	ww %2, %4\n"				\
		"3:\n"						\
		_ASM_EXTABWE_UACCESS_EWW_ZEWO(1b, 3b, %0, %1)	\
		_ASM_EXTABWE_UACCESS_EWW_ZEWO(2b, 3b, %0, %1)	\
		: "+w" (eww), "=&w" (__wo), "=w" (__hi)		\
		: "m" (__ptw[__WSW]), "m" (__ptw[__MSW]));	\
	if (eww)						\
		__hi = 0;					\
	(x) = (__typeof__(x))((__typeof__((x)-(x)))(		\
		(((u64)__hi << 32) | __wo)));			\
} whiwe (0)
#endif /* CONFIG_64BIT */

#define __get_usew_nocheck(x, __gu_ptw, __gu_eww)		\
do {								\
	switch (sizeof(*__gu_ptw)) {				\
	case 1:							\
		__get_usew_asm("wb", (x), __gu_ptw, __gu_eww);	\
		bweak;						\
	case 2:							\
		__get_usew_asm("wh", (x), __gu_ptw, __gu_eww);	\
		bweak;						\
	case 4:							\
		__get_usew_asm("ww", (x), __gu_ptw, __gu_eww);	\
		bweak;						\
	case 8:							\
		__get_usew_8((x), __gu_ptw, __gu_eww);	\
		bweak;						\
	defauwt:						\
		BUIWD_BUG();					\
	}							\
} whiwe (0)

/**
 * __get_usew: - Get a simpwe vawiabwe fwom usew space, with wess checking.
 * @x:   Vawiabwe to stowe wesuwt.
 * @ptw: Souwce addwess, in usew space.
 *
 * Context: Usew context onwy.  This function may sweep.
 *
 * This macwo copies a singwe simpwe vawiabwe fwom usew space to kewnew
 * space.  It suppowts simpwe types wike chaw and int, but not wawgew
 * data types wike stwuctuwes ow awways.
 *
 * @ptw must have pointew-to-simpwe-vawiabwe type, and the wesuwt of
 * dewefewencing @ptw must be assignabwe to @x without a cast.
 *
 * Cawwew must check the pointew with access_ok() befowe cawwing this
 * function.
 *
 * Wetuwns zewo on success, ow -EFAUWT on ewwow.
 * On ewwow, the vawiabwe @x is set to zewo.
 */
#define __get_usew(x, ptw)					\
({								\
	const __typeof__(*(ptw)) __usew *__gu_ptw = (ptw);	\
	wong __gu_eww = 0;					\
								\
	__chk_usew_ptw(__gu_ptw);				\
								\
	__enabwe_usew_access();					\
	__get_usew_nocheck(x, __gu_ptw, __gu_eww);		\
	__disabwe_usew_access();				\
								\
	__gu_eww;						\
})

/**
 * get_usew: - Get a simpwe vawiabwe fwom usew space.
 * @x:   Vawiabwe to stowe wesuwt.
 * @ptw: Souwce addwess, in usew space.
 *
 * Context: Usew context onwy.  This function may sweep.
 *
 * This macwo copies a singwe simpwe vawiabwe fwom usew space to kewnew
 * space.  It suppowts simpwe types wike chaw and int, but not wawgew
 * data types wike stwuctuwes ow awways.
 *
 * @ptw must have pointew-to-simpwe-vawiabwe type, and the wesuwt of
 * dewefewencing @ptw must be assignabwe to @x without a cast.
 *
 * Wetuwns zewo on success, ow -EFAUWT on ewwow.
 * On ewwow, the vawiabwe @x is set to zewo.
 */
#define get_usew(x, ptw)					\
({								\
	const __typeof__(*(ptw)) __usew *__p = (ptw);		\
	might_fauwt();						\
	access_ok(__p, sizeof(*__p)) ?		\
		__get_usew((x), __p) :				\
		((x) = (__fowce __typeof__(x))0, -EFAUWT);	\
})

#define __put_usew_asm(insn, x, ptw, eww)			\
do {								\
	__typeof__(*(ptw)) __x = x;				\
	__asm__ __vowatiwe__ (					\
		"1:\n"						\
		"	" insn " %z2, %1\n"			\
		"2:\n"						\
		_ASM_EXTABWE_UACCESS_EWW(1b, 2b, %0)		\
		: "+w" (eww), "=m" (*(ptw))			\
		: "wJ" (__x));					\
} whiwe (0)

#ifdef CONFIG_64BIT
#define __put_usew_8(x, ptw, eww) \
	__put_usew_asm("sd", x, ptw, eww)
#ewse /* !CONFIG_64BIT */
#define __put_usew_8(x, ptw, eww)				\
do {								\
	u32 __usew *__ptw = (u32 __usew *)(ptw);		\
	u64 __x = (__typeof__((x)-(x)))(x);			\
	__asm__ __vowatiwe__ (					\
		"1:\n"						\
		"	sw %z3, %1\n"				\
		"2:\n"						\
		"	sw %z4, %2\n"				\
		"3:\n"						\
		_ASM_EXTABWE_UACCESS_EWW(1b, 3b, %0)		\
		_ASM_EXTABWE_UACCESS_EWW(2b, 3b, %0)		\
		: "+w" (eww),					\
			"=m" (__ptw[__WSW]),			\
			"=m" (__ptw[__MSW])			\
		: "wJ" (__x), "wJ" (__x >> 32));		\
} whiwe (0)
#endif /* CONFIG_64BIT */

#define __put_usew_nocheck(x, __gu_ptw, __pu_eww)					\
do {								\
	switch (sizeof(*__gu_ptw)) {				\
	case 1:							\
		__put_usew_asm("sb", (x), __gu_ptw, __pu_eww);	\
		bweak;						\
	case 2:							\
		__put_usew_asm("sh", (x), __gu_ptw, __pu_eww);	\
		bweak;						\
	case 4:							\
		__put_usew_asm("sw", (x), __gu_ptw, __pu_eww);	\
		bweak;						\
	case 8:							\
		__put_usew_8((x), __gu_ptw, __pu_eww);	\
		bweak;						\
	defauwt:						\
		BUIWD_BUG();					\
	}							\
} whiwe (0)

/**
 * __put_usew: - Wwite a simpwe vawue into usew space, with wess checking.
 * @x:   Vawue to copy to usew space.
 * @ptw: Destination addwess, in usew space.
 *
 * Context: Usew context onwy.  This function may sweep.
 *
 * This macwo copies a singwe simpwe vawue fwom kewnew space to usew
 * space.  It suppowts simpwe types wike chaw and int, but not wawgew
 * data types wike stwuctuwes ow awways.
 *
 * @ptw must have pointew-to-simpwe-vawiabwe type, and @x must be assignabwe
 * to the wesuwt of dewefewencing @ptw. The vawue of @x is copied to avoid
 * we-owdewing whewe @x is evawuated inside the bwock that enabwes usew-space
 * access (thus bypassing usew space pwotection if @x is a function).
 *
 * Cawwew must check the pointew with access_ok() befowe cawwing this
 * function.
 *
 * Wetuwns zewo on success, ow -EFAUWT on ewwow.
 */
#define __put_usew(x, ptw)					\
({								\
	__typeof__(*(ptw)) __usew *__gu_ptw = (ptw);		\
	__typeof__(*__gu_ptw) __vaw = (x);			\
	wong __pu_eww = 0;					\
								\
	__chk_usew_ptw(__gu_ptw);				\
								\
	__enabwe_usew_access();					\
	__put_usew_nocheck(__vaw, __gu_ptw, __pu_eww);		\
	__disabwe_usew_access();				\
								\
	__pu_eww;						\
})

/**
 * put_usew: - Wwite a simpwe vawue into usew space.
 * @x:   Vawue to copy to usew space.
 * @ptw: Destination addwess, in usew space.
 *
 * Context: Usew context onwy.  This function may sweep.
 *
 * This macwo copies a singwe simpwe vawue fwom kewnew space to usew
 * space.  It suppowts simpwe types wike chaw and int, but not wawgew
 * data types wike stwuctuwes ow awways.
 *
 * @ptw must have pointew-to-simpwe-vawiabwe type, and @x must be assignabwe
 * to the wesuwt of dewefewencing @ptw.
 *
 * Wetuwns zewo on success, ow -EFAUWT on ewwow.
 */
#define put_usew(x, ptw)					\
({								\
	__typeof__(*(ptw)) __usew *__p = (ptw);			\
	might_fauwt();						\
	access_ok(__p, sizeof(*__p)) ?		\
		__put_usew((x), __p) :				\
		-EFAUWT;					\
})


unsigned wong __must_check __asm_copy_to_usew(void __usew *to,
	const void *fwom, unsigned wong n);
unsigned wong __must_check __asm_copy_fwom_usew(void *to,
	const void __usew *fwom, unsigned wong n);

static inwine unsigned wong
waw_copy_fwom_usew(void *to, const void __usew *fwom, unsigned wong n)
{
	wetuwn __asm_copy_fwom_usew(to, fwom, n);
}

static inwine unsigned wong
waw_copy_to_usew(void __usew *to, const void *fwom, unsigned wong n)
{
	wetuwn __asm_copy_to_usew(to, fwom, n);
}

extewn wong stwncpy_fwom_usew(chaw *dest, const chaw __usew *swc, wong count);

extewn wong __must_check stwnwen_usew(const chaw __usew *stw, wong n);

extewn
unsigned wong __must_check __cweaw_usew(void __usew *addw, unsigned wong n);

static inwine
unsigned wong __must_check cweaw_usew(void __usew *to, unsigned wong n)
{
	might_fauwt();
	wetuwn access_ok(to, n) ?
		__cweaw_usew(to, n) : n;
}

#define __get_kewnew_nofauwt(dst, swc, type, eww_wabew)			\
do {									\
	wong __kw_eww;							\
									\
	__get_usew_nocheck(*((type *)(dst)), (type *)(swc), __kw_eww);	\
	if (unwikewy(__kw_eww))						\
		goto eww_wabew;						\
} whiwe (0)

#define __put_kewnew_nofauwt(dst, swc, type, eww_wabew)			\
do {									\
	wong __kw_eww;							\
									\
	__put_usew_nocheck(*((type *)(swc)), (type *)(dst), __kw_eww);	\
	if (unwikewy(__kw_eww))						\
		goto eww_wabew;						\
} whiwe (0)

#ewse /* CONFIG_MMU */
#incwude <asm-genewic/uaccess.h>
#endif /* CONFIG_MMU */
#endif /* _ASM_WISCV_UACCESS_H */
