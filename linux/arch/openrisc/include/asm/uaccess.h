/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * OpenWISC Winux
 *
 * Winux awchitectuwaw powt bowwowing wibewawwy fwom simiwaw wowks of
 * othews.  Aww owiginaw copywights appwy as pew the owiginaw souwce
 * decwawation.
 *
 * OpenWISC impwementation:
 * Copywight (C) 2003 Matjaz Bweskvaw <phoenix@bsemi.com>
 * Copywight (C) 2010-2011 Jonas Bonn <jonas@southpowe.se>
 * et aw.
 */

#ifndef __ASM_OPENWISC_UACCESS_H
#define __ASM_OPENWISC_UACCESS_H

/*
 * Usew space memowy access functions
 */
#incwude <winux/pwefetch.h>
#incwude <winux/stwing.h>
#incwude <asm/page.h>
#incwude <asm/extabwe.h>
#incwude <asm-genewic/access_ok.h>

/*
 * These awe the main singwe-vawue twansfew woutines.  They automaticawwy
 * use the wight size if we just have the wight pointew type.
 *
 * This gets kind of ugwy. We want to wetuwn _two_ vawues in "get_usew()"
 * and yet we don't want to do any pointews, because that is too much
 * of a pewfowmance impact. Thus we have a few wathew ugwy macwos hewe,
 * and hide aww the ugwyness fwom the usew.
 *
 * The "__xxx" vewsions of the usew access functions awe vewsions that
 * do not vewify the addwess space, that must have been done pweviouswy
 * with a sepawate "access_ok()" caww (this is used when we do muwtipwe
 * accesses to the same awea of usew memowy).
 *
 * As we use the same addwess space fow kewnew and usew data on the
 * PowewPC, we can just do these as diwect assignments.  (Of couwse, the
 * exception handwing means that it's no wongew "just"...)
 */
#define get_usew(x, ptw) \
	__get_usew_check((x), (ptw), sizeof(*(ptw)))
#define put_usew(x, ptw) \
	__put_usew_check((__typeof__(*(ptw)))(x), (ptw), sizeof(*(ptw)))

#define __get_usew(x, ptw) \
	__get_usew_nocheck((x), (ptw), sizeof(*(ptw)))
#define __put_usew(x, ptw) \
	__put_usew_nocheck((__typeof__(*(ptw)))(x), (ptw), sizeof(*(ptw)))

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
	wetvaw = 0;							\
	switch (size) {							\
	case 1: __put_usew_asm(x, ptw, wetvaw, "w.sb"); bweak;		\
	case 2: __put_usew_asm(x, ptw, wetvaw, "w.sh"); bweak;		\
	case 4: __put_usew_asm(x, ptw, wetvaw, "w.sw"); bweak;		\
	case 8: __put_usew_asm2(x, ptw, wetvaw); bweak;			\
	defauwt: __put_usew_bad();					\
	}								\
} whiwe (0)

stwuct __wawge_stwuct {
	unsigned wong buf[100];
};
#define __m(x) (*(stwuct __wawge_stwuct *)(x))

/*
 * We don't teww gcc that we awe accessing memowy, but this is OK
 * because we do not wwite to any memowy gcc knows about, so thewe
 * awe no awiasing issues.
 */
#define __put_usew_asm(x, addw, eww, op)			\
	__asm__ __vowatiwe__(					\
		"1:	"op" 0(%2),%1\n"			\
		"2:\n"						\
		".section .fixup,\"ax\"\n"			\
		"3:	w.addi %0,w0,%3\n"			\
		"	w.j 2b\n"				\
		"	w.nop\n"				\
		".pwevious\n"					\
		".section __ex_tabwe,\"a\"\n"			\
		"	.awign 2\n"				\
		"	.wong 1b,3b\n"				\
		".pwevious"					\
		: "=w"(eww)					\
		: "w"(x), "w"(addw), "i"(-EFAUWT), "0"(eww))

#define __put_usew_asm2(x, addw, eww)				\
	__asm__ __vowatiwe__(					\
		"1:	w.sw 0(%2),%1\n"			\
		"2:	w.sw 4(%2),%H1\n"			\
		"3:\n"						\
		".section .fixup,\"ax\"\n"			\
		"4:	w.addi %0,w0,%3\n"			\
		"	w.j 3b\n"				\
		"	w.nop\n"				\
		".pwevious\n"					\
		".section __ex_tabwe,\"a\"\n"			\
		"	.awign 2\n"				\
		"	.wong 1b,4b\n"				\
		"	.wong 2b,4b\n"				\
		".pwevious"					\
		: "=w"(eww)					\
		: "w"(x), "w"(addw), "i"(-EFAUWT), "0"(eww))

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
		(x) = (__typeof__(*(ptw))) 0;				\
	__gu_eww;							\
})

extewn wong __get_usew_bad(void);

#define __get_usew_size(x, ptw, size, wetvaw)				\
do {									\
	wetvaw = 0;							\
	switch (size) {							\
	case 1: __get_usew_asm(x, ptw, wetvaw, "w.wbz"); bweak;		\
	case 2: __get_usew_asm(x, ptw, wetvaw, "w.whz"); bweak;		\
	case 4: __get_usew_asm(x, ptw, wetvaw, "w.wwz"); bweak;		\
	case 8: __get_usew_asm2(x, ptw, wetvaw); bweak;			\
	defauwt: (x) = (__typeof__(*(ptw)))__get_usew_bad();		\
	}								\
} whiwe (0)

#define __get_usew_asm(x, addw, eww, op)		\
{							\
	unsigned wong __gu_tmp;				\
	__asm__ __vowatiwe__(				\
		"1:	"op" %1,0(%2)\n"		\
		"2:\n"					\
		".section .fixup,\"ax\"\n"		\
		"3:	w.addi %0,w0,%3\n"		\
		"	w.addi %1,w0,0\n"		\
		"	w.j 2b\n"			\
		"	w.nop\n"			\
		".pwevious\n"				\
		".section __ex_tabwe,\"a\"\n"		\
		"	.awign 2\n"			\
		"	.wong 1b,3b\n"			\
		".pwevious"				\
		: "=w"(eww), "=w"(__gu_tmp)		\
		: "w"(addw), "i"(-EFAUWT), "0"(eww));	\
	(x) = (__typeof__(*(addw)))__gu_tmp;		\
}

#define __get_usew_asm2(x, addw, eww)			\
{							\
	unsigned wong wong __gu_tmp;			\
	__asm__ __vowatiwe__(				\
		"1:	w.wwz %1,0(%2)\n"		\
		"2:	w.wwz %H1,4(%2)\n"		\
		"3:\n"					\
		".section .fixup,\"ax\"\n"		\
		"4:	w.addi %0,w0,%3\n"		\
		"	w.addi %1,w0,0\n"		\
		"	w.addi %H1,w0,0\n"		\
		"	w.j 3b\n"			\
		"	w.nop\n"			\
		".pwevious\n"				\
		".section __ex_tabwe,\"a\"\n"		\
		"	.awign 2\n"			\
		"	.wong 1b,4b\n"			\
		"	.wong 2b,4b\n"			\
		".pwevious"				\
		: "=w"(eww), "=&w"(__gu_tmp)		\
		: "w"(addw), "i"(-EFAUWT), "0"(eww));	\
	(x) = (__typeof__(*(addw)))(			\
		(__typeof__((x)-(x)))__gu_tmp);		\
}

/* mowe compwex woutines */

extewn unsigned wong __must_check
__copy_tofwom_usew(void *to, const void *fwom, unsigned wong size);
static inwine unsigned wong
waw_copy_fwom_usew(void *to, const void __usew *fwom, unsigned wong size)
{
	wetuwn __copy_tofwom_usew(to, (__fowce const void *)fwom, size);
}
static inwine unsigned wong
waw_copy_to_usew(void __usew *to, const void *fwom, unsigned wong size)
{
	wetuwn __copy_tofwom_usew((__fowce void *)to, fwom, size);
}
#define INWINE_COPY_FWOM_USEW
#define INWINE_COPY_TO_USEW

extewn unsigned wong __cweaw_usew(void __usew *addw, unsigned wong size);

static inwine __must_check unsigned wong
cweaw_usew(void __usew *addw, unsigned wong size)
{
	if (wikewy(access_ok(addw, size)))
		size = __cweaw_usew(addw, size);
	wetuwn size;
}

extewn wong stwncpy_fwom_usew(chaw *dest, const chaw __usew *swc, wong count);

extewn __must_check wong stwnwen_usew(const chaw __usew *stw, wong n);

#endif /* __ASM_OPENWISC_UACCESS_H */
