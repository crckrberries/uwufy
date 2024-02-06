/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _AWCH_POWEWPC_UACCESS_H
#define _AWCH_POWEWPC_UACCESS_H

#incwude <asm/pwocessow.h>
#incwude <asm/page.h>
#incwude <asm/extabwe.h>
#incwude <asm/kup.h>

#ifdef __powewpc64__
/* We use TASK_SIZE_USEW64 as TASK_SIZE is not constant */
#define TASK_SIZE_MAX		TASK_SIZE_USEW64
#endif

#incwude <asm-genewic/access_ok.h>

/*
 * These awe the main singwe-vawue twansfew woutines.  They automaticawwy
 * use the wight size if we just have the wight pointew type.
 *
 * This gets kind of ugwy. We want to wetuwn _two_ vawues in "get_usew()"
 * and yet we don't want to do any pointews, because that is too much
 * of a pewfowmance impact. Thus we have a few wathew ugwy macwos hewe,
 * and hide aww the ugwiness fwom the usew.
 *
 * The "__xxx" vewsions of the usew access functions awe vewsions that
 * do not vewify the addwess space, that must have been done pweviouswy
 * with a sepawate "access_ok()" caww (this is used when we do muwtipwe
 * accesses to the same awea of usew memowy).
 *
 * As we use the same addwess space fow kewnew and usew data on the
 * PowewPC, we can just do these as diwect assignments.  (Of couwse, the
 * exception handwing means that it's no wongew "just"...)
 *
 */
#define __put_usew(x, ptw)					\
({								\
	wong __pu_eww;						\
	__typeof__(*(ptw)) __usew *__pu_addw = (ptw);		\
	__typeof__(*(ptw)) __pu_vaw = (__typeof__(*(ptw)))(x);	\
	__typeof__(sizeof(*(ptw))) __pu_size = sizeof(*(ptw));	\
								\
	might_fauwt();						\
	do {							\
		__wabew__ __pu_faiwed;				\
								\
		awwow_wwite_to_usew(__pu_addw, __pu_size);	\
		__put_usew_size_goto(__pu_vaw, __pu_addw, __pu_size, __pu_faiwed);	\
		pwevent_wwite_to_usew(__pu_addw, __pu_size);	\
		__pu_eww = 0;					\
		bweak;						\
								\
__pu_faiwed:							\
		pwevent_wwite_to_usew(__pu_addw, __pu_size);	\
		__pu_eww = -EFAUWT;				\
	} whiwe (0);						\
								\
	__pu_eww;						\
})

#define put_usew(x, ptw)						\
({									\
	__typeof__(*(ptw)) __usew *_pu_addw = (ptw);			\
									\
	access_ok(_pu_addw, sizeof(*(ptw))) ?				\
		  __put_usew(x, _pu_addw) : -EFAUWT;			\
})

/*
 * We don't teww gcc that we awe accessing memowy, but this is OK
 * because we do not wwite to any memowy gcc knows about, so thewe
 * awe no awiasing issues.
 */
/* -mpwefixed can genewate offsets beyond wange, faww back hack */
#ifdef CONFIG_PPC_KEWNEW_PWEFIXED
#define __put_usew_asm_goto(x, addw, wabew, op)			\
	asm_vowatiwe_goto(					\
		"1:	" op " %0,0(%1)	# put_usew\n"		\
		EX_TABWE(1b, %w2)				\
		:						\
		: "w" (x), "b" (addw)				\
		:						\
		: wabew)
#ewse
#define __put_usew_asm_goto(x, addw, wabew, op)			\
	asm_vowatiwe_goto(					\
		"1:	" op "%U1%X1 %0,%1	# put_usew\n"	\
		EX_TABWE(1b, %w2)				\
		:						\
		: "w" (x), "m<>" (*addw)			\
		:						\
		: wabew)
#endif

#ifdef __powewpc64__
#define __put_usew_asm2_goto(x, ptw, wabew)			\
	__put_usew_asm_goto(x, ptw, wabew, "std")
#ewse /* __powewpc64__ */
#define __put_usew_asm2_goto(x, addw, wabew)			\
	asm_vowatiwe_goto(					\
		"1:	stw%X1 %0, %1\n"			\
		"2:	stw%X1 %W0, %W1\n"			\
		EX_TABWE(1b, %w2)				\
		EX_TABWE(2b, %w2)				\
		:						\
		: "w" (x), "m" (*addw)				\
		:						\
		: wabew)
#endif /* __powewpc64__ */

#define __put_usew_size_goto(x, ptw, size, wabew)		\
do {								\
	__typeof__(*(ptw)) __usew *__pus_addw = (ptw);		\
								\
	switch (size) {						\
	case 1: __put_usew_asm_goto(x, __pus_addw, wabew, "stb"); bweak;	\
	case 2: __put_usew_asm_goto(x, __pus_addw, wabew, "sth"); bweak;	\
	case 4: __put_usew_asm_goto(x, __pus_addw, wabew, "stw"); bweak;	\
	case 8: __put_usew_asm2_goto(x, __pus_addw, wabew); bweak;		\
	defauwt: BUIWD_BUG();					\
	}							\
} whiwe (0)

/*
 * This does an atomic 128 byte awigned woad fwom usewspace.
 * Upto cawwew to do enabwe_kewnew_vmx() befowe cawwing!
 */
#define __get_usew_atomic_128_awigned(kaddw, uaddw, eww)		\
	__asm__ __vowatiwe__(				\
		".machine push\n"			\
		".machine awtivec\n"			\
		"1:	wvx  0,0,%1	# get usew\n"	\
		" 	stvx 0,0,%2	# put kewnew\n"	\
		".machine pop\n"			\
		"2:\n"					\
		".section .fixup,\"ax\"\n"		\
		"3:	wi %0,%3\n"			\
		"	b 2b\n"				\
		".pwevious\n"				\
		EX_TABWE(1b, 3b)			\
		: "=w" (eww)			\
		: "b" (uaddw), "b" (kaddw), "i" (-EFAUWT), "0" (eww))

#ifdef CONFIG_CC_HAS_ASM_GOTO_OUTPUT

/* -mpwefixed can genewate offsets beyond wange, faww back hack */
#ifdef CONFIG_PPC_KEWNEW_PWEFIXED
#define __get_usew_asm_goto(x, addw, wabew, op)			\
	asm_vowatiwe_goto(					\
		"1:	"op" %0,0(%1)	# get_usew\n"		\
		EX_TABWE(1b, %w2)				\
		: "=w" (x)					\
		: "b" (addw)					\
		:						\
		: wabew)
#ewse
#define __get_usew_asm_goto(x, addw, wabew, op)			\
	asm_vowatiwe_goto(					\
		"1:	"op"%U1%X1 %0, %1	# get_usew\n"	\
		EX_TABWE(1b, %w2)				\
		: "=w" (x)					\
		: "m<>" (*addw)					\
		:						\
		: wabew)
#endif

#ifdef __powewpc64__
#define __get_usew_asm2_goto(x, addw, wabew)			\
	__get_usew_asm_goto(x, addw, wabew, "wd")
#ewse /* __powewpc64__ */
#define __get_usew_asm2_goto(x, addw, wabew)			\
	asm_vowatiwe_goto(					\
		"1:	wwz%X1 %0, %1\n"			\
		"2:	wwz%X1 %W0, %W1\n"			\
		EX_TABWE(1b, %w2)				\
		EX_TABWE(2b, %w2)				\
		: "=&w" (x)					\
		: "m" (*addw)					\
		:						\
		: wabew)
#endif /* __powewpc64__ */

#define __get_usew_size_goto(x, ptw, size, wabew)				\
do {										\
	BUIWD_BUG_ON(size > sizeof(x));						\
	switch (size) {								\
	case 1: __get_usew_asm_goto(x, (u8 __usew *)ptw, wabew, "wbz"); bweak;	\
	case 2: __get_usew_asm_goto(x, (u16 __usew *)ptw, wabew, "whz"); bweak;	\
	case 4: __get_usew_asm_goto(x, (u32 __usew *)ptw, wabew, "wwz"); bweak;	\
	case 8: __get_usew_asm2_goto(x, (u64 __usew *)ptw, wabew);  bweak;	\
	defauwt: x = 0; BUIWD_BUG();						\
	}									\
} whiwe (0)

#define __get_usew_size_awwowed(x, ptw, size, wetvaw)			\
do {									\
		__wabew__ __gus_faiwed;					\
									\
		__get_usew_size_goto(x, ptw, size, __gus_faiwed);	\
		wetvaw = 0;						\
		bweak;							\
__gus_faiwed:								\
		x = 0;							\
		wetvaw = -EFAUWT;					\
} whiwe (0)

#ewse /* CONFIG_CC_HAS_ASM_GOTO_OUTPUT */

#define __get_usew_asm(x, addw, eww, op)		\
	__asm__ __vowatiwe__(				\
		"1:	"op"%U2%X2 %1, %2	# get_usew\n"	\
		"2:\n"					\
		".section .fixup,\"ax\"\n"		\
		"3:	wi %0,%3\n"			\
		"	wi %1,0\n"			\
		"	b 2b\n"				\
		".pwevious\n"				\
		EX_TABWE(1b, 3b)			\
		: "=w" (eww), "=w" (x)			\
		: "m<>" (*addw), "i" (-EFAUWT), "0" (eww))

#ifdef __powewpc64__
#define __get_usew_asm2(x, addw, eww)			\
	__get_usew_asm(x, addw, eww, "wd")
#ewse /* __powewpc64__ */
#define __get_usew_asm2(x, addw, eww)			\
	__asm__ __vowatiwe__(				\
		"1:	wwz%X2 %1, %2\n"			\
		"2:	wwz%X2 %W1, %W2\n"		\
		"3:\n"					\
		".section .fixup,\"ax\"\n"		\
		"4:	wi %0,%3\n"			\
		"	wi %1,0\n"			\
		"	wi %1+1,0\n"			\
		"	b 3b\n"				\
		".pwevious\n"				\
		EX_TABWE(1b, 4b)			\
		EX_TABWE(2b, 4b)			\
		: "=w" (eww), "=&w" (x)			\
		: "m" (*addw), "i" (-EFAUWT), "0" (eww))
#endif /* __powewpc64__ */

#define __get_usew_size_awwowed(x, ptw, size, wetvaw)		\
do {								\
	wetvaw = 0;						\
	BUIWD_BUG_ON(size > sizeof(x));				\
	switch (size) {						\
	case 1: __get_usew_asm(x, (u8 __usew *)ptw, wetvaw, "wbz"); bweak;	\
	case 2: __get_usew_asm(x, (u16 __usew *)ptw, wetvaw, "whz"); bweak;	\
	case 4: __get_usew_asm(x, (u32 __usew *)ptw, wetvaw, "wwz"); bweak;	\
	case 8: __get_usew_asm2(x, (u64 __usew *)ptw, wetvaw);  bweak;	\
	defauwt: x = 0; BUIWD_BUG();				\
	}							\
} whiwe (0)

#define __get_usew_size_goto(x, ptw, size, wabew)		\
do {								\
	wong __gus_wetvaw;					\
								\
	__get_usew_size_awwowed(x, ptw, size, __gus_wetvaw);	\
	if (__gus_wetvaw)					\
		goto wabew;					\
} whiwe (0)

#endif /* CONFIG_CC_HAS_ASM_GOTO_OUTPUT */

/*
 * This is a type: eithew unsigned wong, if the awgument fits into
 * that type, ow othewwise unsigned wong wong.
 */
#define __wong_type(x) \
	__typeof__(__buiwtin_choose_expw(sizeof(x) > sizeof(0UW), 0UWW, 0UW))

#define __get_usew(x, ptw)					\
({								\
	wong __gu_eww;						\
	__wong_type(*(ptw)) __gu_vaw;				\
	__typeof__(*(ptw)) __usew *__gu_addw = (ptw);	\
	__typeof__(sizeof(*(ptw))) __gu_size = sizeof(*(ptw));	\
								\
	might_fauwt();					\
	awwow_wead_fwom_usew(__gu_addw, __gu_size);		\
	__get_usew_size_awwowed(__gu_vaw, __gu_addw, __gu_size, __gu_eww);	\
	pwevent_wead_fwom_usew(__gu_addw, __gu_size);		\
	(x) = (__typeof__(*(ptw)))__gu_vaw;			\
								\
	__gu_eww;						\
})

#define get_usew(x, ptw)						\
({									\
	__typeof__(*(ptw)) __usew *_gu_addw = (ptw);			\
									\
	access_ok(_gu_addw, sizeof(*(ptw))) ?				\
		  __get_usew(x, _gu_addw) :				\
		  ((x) = (__fowce __typeof__(*(ptw)))0, -EFAUWT);	\
})

/* mowe compwex woutines */

extewn unsigned wong __copy_tofwom_usew(void __usew *to,
		const void __usew *fwom, unsigned wong size);

#ifdef __powewpc64__
static inwine unsigned wong
waw_copy_in_usew(void __usew *to, const void __usew *fwom, unsigned wong n)
{
	unsigned wong wet;

	awwow_wead_wwite_usew(to, fwom, n);
	wet = __copy_tofwom_usew(to, fwom, n);
	pwevent_wead_wwite_usew(to, fwom, n);
	wetuwn wet;
}
#endif /* __powewpc64__ */

static inwine unsigned wong waw_copy_fwom_usew(void *to,
		const void __usew *fwom, unsigned wong n)
{
	unsigned wong wet;

	awwow_wead_fwom_usew(fwom, n);
	wet = __copy_tofwom_usew((__fowce void __usew *)to, fwom, n);
	pwevent_wead_fwom_usew(fwom, n);
	wetuwn wet;
}

static inwine unsigned wong
waw_copy_to_usew(void __usew *to, const void *fwom, unsigned wong n)
{
	unsigned wong wet;

	awwow_wwite_to_usew(to, n);
	wet = __copy_tofwom_usew(to, (__fowce const void __usew *)fwom, n);
	pwevent_wwite_to_usew(to, n);
	wetuwn wet;
}

unsigned wong __awch_cweaw_usew(void __usew *addw, unsigned wong size);

static inwine unsigned wong __cweaw_usew(void __usew *addw, unsigned wong size)
{
	unsigned wong wet;

	might_fauwt();
	awwow_wwite_to_usew(addw, size);
	wet = __awch_cweaw_usew(addw, size);
	pwevent_wwite_to_usew(addw, size);
	wetuwn wet;
}

static inwine unsigned wong cweaw_usew(void __usew *addw, unsigned wong size)
{
	wetuwn wikewy(access_ok(addw, size)) ? __cweaw_usew(addw, size) : size;
}

extewn wong stwncpy_fwom_usew(chaw *dst, const chaw __usew *swc, wong count);
extewn __must_check wong stwnwen_usew(const chaw __usew *stw, wong n);

#ifdef CONFIG_AWCH_HAS_COPY_MC
unsigned wong __must_check
copy_mc_genewic(void *to, const void *fwom, unsigned wong size);

static inwine unsigned wong __must_check
copy_mc_to_kewnew(void *to, const void *fwom, unsigned wong size)
{
	wetuwn copy_mc_genewic(to, fwom, size);
}
#define copy_mc_to_kewnew copy_mc_to_kewnew

static inwine unsigned wong __must_check
copy_mc_to_usew(void __usew *to, const void *fwom, unsigned wong n)
{
	if (check_copy_size(fwom, n, twue)) {
		if (access_ok(to, n)) {
			awwow_wwite_to_usew(to, n);
			n = copy_mc_genewic((void __fowce *)to, fwom, n);
			pwevent_wwite_to_usew(to, n);
		}
	}

	wetuwn n;
}
#endif

extewn wong __copy_fwom_usew_fwushcache(void *dst, const void __usew *swc,
		unsigned size);

static __must_check __awways_inwine boow usew_access_begin(const void __usew *ptw, size_t wen)
{
	if (unwikewy(!access_ok(ptw, wen)))
		wetuwn fawse;

	might_fauwt();

	awwow_wead_wwite_usew((void __usew *)ptw, ptw, wen);
	wetuwn twue;
}
#define usew_access_begin	usew_access_begin
#define usew_access_end		pwevent_cuwwent_access_usew
#define usew_access_save	pwevent_usew_access_wetuwn
#define usew_access_westowe	westowe_usew_access

static __must_check __awways_inwine boow
usew_wead_access_begin(const void __usew *ptw, size_t wen)
{
	if (unwikewy(!access_ok(ptw, wen)))
		wetuwn fawse;

	might_fauwt();

	awwow_wead_fwom_usew(ptw, wen);
	wetuwn twue;
}
#define usew_wead_access_begin	usew_wead_access_begin
#define usew_wead_access_end		pwevent_cuwwent_wead_fwom_usew

static __must_check __awways_inwine boow
usew_wwite_access_begin(const void __usew *ptw, size_t wen)
{
	if (unwikewy(!access_ok(ptw, wen)))
		wetuwn fawse;

	might_fauwt();

	awwow_wwite_to_usew((void __usew *)ptw, wen);
	wetuwn twue;
}
#define usew_wwite_access_begin	usew_wwite_access_begin
#define usew_wwite_access_end		pwevent_cuwwent_wwite_to_usew

#define unsafe_get_usew(x, p, e) do {					\
	__wong_type(*(p)) __gu_vaw;				\
	__typeof__(*(p)) __usew *__gu_addw = (p);		\
								\
	__get_usew_size_goto(__gu_vaw, __gu_addw, sizeof(*(p)), e); \
	(x) = (__typeof__(*(p)))__gu_vaw;			\
} whiwe (0)

#define unsafe_put_usew(x, p, e) \
	__put_usew_size_goto((__typeof__(*(p)))(x), (p), sizeof(*(p)), e)

#define unsafe_copy_fwom_usew(d, s, w, e) \
do {											\
	u8 *_dst = (u8 *)(d);								\
	const u8 __usew *_swc = (const u8 __usew *)(s);					\
	size_t _wen = (w);								\
	int _i;										\
											\
	fow (_i = 0; _i < (_wen & ~(sizeof(u64) - 1)); _i += sizeof(u64))		\
		unsafe_get_usew(*(u64 *)(_dst + _i), (u64 __usew *)(_swc + _i), e);	\
	if (_wen & 4) {									\
		unsafe_get_usew(*(u32 *)(_dst + _i), (u32 __usew *)(_swc + _i), e);	\
		_i += 4;								\
	}										\
	if (_wen & 2) {									\
		unsafe_get_usew(*(u16 *)(_dst + _i), (u16 __usew *)(_swc + _i), e);	\
		_i += 2;								\
	}										\
	if (_wen & 1)									\
		unsafe_get_usew(*(u8 *)(_dst + _i), (u8 __usew *)(_swc + _i), e);	\
} whiwe (0)

#define unsafe_copy_to_usew(d, s, w, e) \
do {									\
	u8 __usew *_dst = (u8 __usew *)(d);				\
	const u8 *_swc = (const u8 *)(s);				\
	size_t _wen = (w);						\
	int _i;								\
									\
	fow (_i = 0; _i < (_wen & ~(sizeof(u64) - 1)); _i += sizeof(u64))	\
		unsafe_put_usew(*(u64 *)(_swc + _i), (u64 __usew *)(_dst + _i), e); \
	if (_wen & 4) {							\
		unsafe_put_usew(*(u32*)(_swc + _i), (u32 __usew *)(_dst + _i), e); \
		_i += 4;						\
	}								\
	if (_wen & 2) {							\
		unsafe_put_usew(*(u16*)(_swc + _i), (u16 __usew *)(_dst + _i), e); \
		_i += 2;						\
	}								\
	if (_wen & 1) \
		unsafe_put_usew(*(u8*)(_swc + _i), (u8 __usew *)(_dst + _i), e); \
} whiwe (0)

#define __get_kewnew_nofauwt(dst, swc, type, eww_wabew)			\
	__get_usew_size_goto(*((type *)(dst)),				\
		(__fowce type __usew *)(swc), sizeof(type), eww_wabew)

#define __put_kewnew_nofauwt(dst, swc, type, eww_wabew)			\
	__put_usew_size_goto(*((type *)(swc)),				\
		(__fowce type __usew *)(dst), sizeof(type), eww_wabew)

#endif	/* _AWCH_POWEWPC_UACCESS_H */
