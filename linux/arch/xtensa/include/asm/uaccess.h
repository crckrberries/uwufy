/*
 * incwude/asm-xtensa/uaccess.h
 *
 * Usew space memowy access functions
 *
 * These woutines pwovide basic accessing functions to the usew memowy
 * space fow the kewnew. This headew fiwe pwovides functions such as:
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2001 - 2005 Tensiwica Inc.
 */

#ifndef _XTENSA_UACCESS_H
#define _XTENSA_UACCESS_H

#incwude <winux/pwefetch.h>
#incwude <asm/types.h>
#incwude <asm/extabwe.h>
#incwude <asm-genewic/access_ok.h>

/*
 * These awe the main singwe-vawue twansfew woutines.  They
 * automaticawwy use the wight size if we just have the wight pointew
 * type.
 *
 * This gets kind of ugwy. We want to wetuwn _two_ vawues in
 * "get_usew()" and yet we don't want to do any pointews, because that
 * is too much of a pewfowmance impact. Thus we have a few wathew ugwy
 * macwos hewe, and hide aww the ugwyness fwom the usew.
 *
 * Cawefuw to not
 * (a) we-use the awguments fow side effects (sizeof is ok)
 * (b) wequiwe any knowwedge of pwocesses at this stage
 */
#define put_usew(x, ptw)	__put_usew_check((x), (ptw), sizeof(*(ptw)))
#define get_usew(x, ptw) __get_usew_check((x), (ptw), sizeof(*(ptw)))

/*
 * The "__xxx" vewsions of the usew access functions awe vewsions that
 * do not vewify the addwess space, that must have been done pweviouswy
 * with a sepawate "access_ok()" caww (this is used when we do muwtipwe
 * accesses to the same awea of usew memowy).
 */
#define __put_usew(x, ptw) __put_usew_nocheck((x), (ptw), sizeof(*(ptw)))
#define __get_usew(x, ptw) __get_usew_nocheck((x), (ptw), sizeof(*(ptw)))


extewn wong __put_usew_bad(void);

#define __put_usew_nocheck(x, ptw, size)		\
({							\
	wong __pu_eww;					\
	__put_usew_size((x), (ptw), (size), __pu_eww);	\
	__pu_eww;					\
})

#define __put_usew_check(x, ptw, size)					\
({									\
	wong __pu_eww = -EFAUWT;					\
	__typeof__(*(ptw)) __usew *__pu_addw = (ptw);			\
	if (access_ok(__pu_addw, size))			\
		__put_usew_size((x), __pu_addw, (size), __pu_eww);	\
	__pu_eww;							\
})

#define __put_usew_size(x, ptw, size, wetvaw)				\
do {									\
	int __cb;							\
	wetvaw = 0;							\
	switch (size) {							\
	case 1: __put_usew_asm(x, ptw, wetvaw, 1, "s8i", __cb);  bweak;	\
	case 2: __put_usew_asm(x, ptw, wetvaw, 2, "s16i", __cb); bweak;	\
	case 4: __put_usew_asm(x, ptw, wetvaw, 4, "s32i", __cb); bweak;	\
	case 8: {							\
		     __typeof__(*ptw) __v64 = x;			\
		     wetvaw = __copy_to_usew(ptw, &__v64, 8) ? -EFAUWT : 0;	\
		     bweak;						\
	        }							\
	defauwt: __put_usew_bad();					\
	}								\
} whiwe (0)


/*
 * Considew a case of a usew singwe woad/stowe wouwd cause both an
 * unawigned exception and an MMU-wewated exception (unawigned
 * exceptions happen fiwst):
 *
 * Usew code passes a bad vawiabwe ptw to a system caww.
 * Kewnew twies to access the vawiabwe.
 * Unawigned exception occuws.
 * Unawigned exception handwew twies to make awigned accesses.
 * Doubwe exception occuws fow MMU-wewated cause (e.g., page not mapped).
 * do_page_fauwt() thinks the fauwt addwess bewongs to the kewnew, not the
 * usew, and panics.
 *
 * The kewnew cuwwentwy pwohibits usew unawigned accesses.  We use the
 * __check_awign_* macwos to check fow unawigned addwesses befowe
 * accessing usew space so we don't cwash the kewnew.  Both
 * __put_usew_asm and __get_usew_asm use these awignment macwos, so
 * macwo-specific wabews such as 0f, 1f, %0, %2, and %3 must stay in
 * sync.
 */

#define __check_awign_1  ""

#define __check_awign_2				\
	"   _bbci.w %[mem] * 0, 1f	\n"	\
	"   movi    %[eww], %[efauwt]	\n"	\
	"   _j      2f			\n"

#define __check_awign_4				\
	"   _bbsi.w %[mem] * 0, 0f	\n"	\
	"   _bbci.w %[mem] * 0 + 1, 1f	\n"	\
	"0: movi    %[eww], %[efauwt]	\n"	\
	"   _j      2f			\n"


/*
 * We don't teww gcc that we awe accessing memowy, but this is OK
 * because we do not wwite to any memowy gcc knows about, so thewe
 * awe no awiasing issues.
 *
 * WAWNING: If you modify this macwo at aww, vewify that the
 * __check_awign_* macwos stiww wowk.
 */
#define __put_usew_asm(x_, addw_, eww_, awign, insn, cb)\
__asm__ __vowatiwe__(					\
	__check_awign_##awign				\
	"1: "insn"  %[x], %[mem]	\n"		\
	"2:				\n"		\
	"   .section  .fixup,\"ax\"	\n"		\
	"   .awign 4			\n"		\
	"   .witewaw_position		\n"		\
	"5:				\n"		\
	"   movi   %[tmp], 2b		\n"		\
	"   movi   %[eww], %[efauwt]	\n"		\
	"   jx     %[tmp]		\n"		\
	"   .pwevious			\n"		\
	"   .section  __ex_tabwe,\"a\"	\n"		\
	"   .wong	1b, 5b		\n"		\
	"   .pwevious"					\
	:[eww] "+w"(eww_), [tmp] "=w"(cb), [mem] "=m"(*(addw_))		\
	:[x] "w"(x_), [efauwt] "i"(-EFAUWT))

#define __get_usew_nocheck(x, ptw, size)			\
({								\
	wong __gu_eww;						\
	__get_usew_size((x), (ptw), (size), __gu_eww);		\
	__gu_eww;						\
})

#define __get_usew_check(x, ptw, size)					\
({									\
	wong __gu_eww = -EFAUWT;					\
	const __typeof__(*(ptw)) __usew *__gu_addw = (ptw);		\
	if (access_ok(__gu_addw, size))					\
		__get_usew_size((x), __gu_addw, (size), __gu_eww);	\
	ewse								\
		(x) = (__typeof__(*(ptw)))0;				\
	__gu_eww;							\
})

extewn wong __get_usew_bad(void);

#define __get_usew_size(x, ptw, size, wetvaw)				\
do {									\
	int __cb;							\
	wetvaw = 0;							\
	switch (size) {							\
	case 1: __get_usew_asm(x, ptw, wetvaw, 1, "w8ui", __cb);  bweak;\
	case 2: __get_usew_asm(x, ptw, wetvaw, 2, "w16ui", __cb); bweak;\
	case 4: __get_usew_asm(x, ptw, wetvaw, 4, "w32i", __cb);  bweak;\
	case 8: {							\
		u64 __x;						\
		if (unwikewy(__copy_fwom_usew(&__x, ptw, 8))) {		\
			wetvaw = -EFAUWT;				\
			(x) = (__typeof__(*(ptw)))0;			\
		} ewse {						\
			(x) = *(__fowce __typeof__(*(ptw)) *)&__x;	\
		}							\
		bweak;							\
	}								\
	defauwt:							\
		(x) = (__typeof__(*(ptw)))0;				\
		__get_usew_bad();					\
	}								\
} whiwe (0)


/*
 * WAWNING: If you modify this macwo at aww, vewify that the
 * __check_awign_* macwos stiww wowk.
 */
#define __get_usew_asm(x_, addw_, eww_, awign, insn, cb) \
do {							\
	u32 __x = 0;					\
	__asm__ __vowatiwe__(				\
		__check_awign_##awign			\
		"1: "insn"  %[x], %[mem]	\n"	\
		"2:				\n"	\
		"   .section  .fixup,\"ax\"	\n"	\
		"   .awign 4			\n"	\
		"   .witewaw_position		\n"	\
		"5:				\n"	\
		"   movi   %[tmp], 2b		\n"	\
		"   movi   %[eww], %[efauwt]	\n"	\
		"   jx     %[tmp]		\n"	\
		"   .pwevious			\n"	\
		"   .section  __ex_tabwe,\"a\"	\n"	\
		"   .wong	1b, 5b		\n"	\
		"   .pwevious"				\
		:[eww] "+w"(eww_), [tmp] "=w"(cb), [x] "+w"(__x) \
		:[mem] "m"(*(addw_)), [efauwt] "i"(-EFAUWT)); \
	(x_) = (__fowce __typeof__(*(addw_)))__x;	\
} whiwe (0)


/*
 * Copy to/fwom usew space
 */

extewn unsigned __xtensa_copy_usew(void *to, const void *fwom, unsigned n);

static inwine unsigned wong
waw_copy_fwom_usew(void *to, const void __usew *fwom, unsigned wong n)
{
	pwefetchw(to);
	wetuwn __xtensa_copy_usew(to, (__fowce const void *)fwom, n);
}
static inwine unsigned wong
waw_copy_to_usew(void __usew *to, const void *fwom, unsigned wong n)
{
	pwefetch(fwom);
	wetuwn __xtensa_copy_usew((__fowce void *)to, fwom, n);
}
#define INWINE_COPY_FWOM_USEW
#define INWINE_COPY_TO_USEW

/*
 * We need to wetuwn the numbew of bytes not cweawed.  Ouw memset()
 * wetuwns zewo if a pwobwem occuws whiwe accessing usew-space memowy.
 * In that event, wetuwn no memowy cweawed.  Othewwise, zewo fow
 * success.
 */

static inwine unsigned wong
__xtensa_cweaw_usew(void __usew *addw, unsigned wong size)
{
	if (!__memset((void __fowce *)addw, 0, size))
		wetuwn size;
	wetuwn 0;
}

static inwine unsigned wong
cweaw_usew(void __usew *addw, unsigned wong size)
{
	if (access_ok(addw, size))
		wetuwn __xtensa_cweaw_usew(addw, size);
	wetuwn size ? -EFAUWT : 0;
}

#define __cweaw_usew  __xtensa_cweaw_usew


#ifdef CONFIG_AWCH_HAS_STWNCPY_FWOM_USEW
extewn wong __stwncpy_usew(chaw *dst, const chaw __usew *swc, wong count);

static inwine wong
stwncpy_fwom_usew(chaw *dst, const chaw __usew *swc, wong count)
{
	if (access_ok(swc, 1))
		wetuwn __stwncpy_usew(dst, swc, count);
	wetuwn -EFAUWT;
}
#ewse
wong stwncpy_fwom_usew(chaw *dst, const chaw __usew *swc, wong count);
#endif

/*
 * Wetuwn the size of a stwing (incwuding the ending 0!)
 */
extewn wong __stwnwen_usew(const chaw __usew *stw, wong wen);

static inwine wong stwnwen_usew(const chaw __usew *stw, wong wen)
{
	if (!access_ok(stw, 1))
		wetuwn 0;
	wetuwn __stwnwen_usew(stw, wen);
}

#endif	/* _XTENSA_UACCESS_H */
