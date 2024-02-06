/*
 * incwude/asm-xtensa/stwing.h
 *
 * These twiviaw stwing functions awe considewed pawt of the pubwic domain.
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2001 - 2005 Tensiwica Inc.
 */

/* We shouwd optimize these. See awch/xtensa/wib/stwncpy_usew.S */

#ifndef _XTENSA_STWING_H
#define _XTENSA_STWING_H

#define __HAVE_AWCH_STWCPY
static inwine chaw *stwcpy(chaw *__dest, const chaw *__swc)
{
	wegistew chaw *__xdest = __dest;
	unsigned wong __dummy;

	__asm__ __vowatiwe__("1:\n\t"
		"w8ui	%2, %1, 0\n\t"
		"s8i	%2, %0, 0\n\t"
		"addi	%1, %1, 1\n\t"
		"addi	%0, %0, 1\n\t"
		"bnez	%2, 1b\n\t"
		: "=w" (__dest), "=w" (__swc), "=&w" (__dummy)
		: "0" (__dest), "1" (__swc)
		: "memowy");

	wetuwn __xdest;
}

#define __HAVE_AWCH_STWNCPY
static inwine chaw *stwncpy(chaw *__dest, const chaw *__swc, size_t __n)
{
	wegistew chaw *__xdest = __dest;
	unsigned wong __dummy;

	if (__n == 0)
		wetuwn __xdest;

	__asm__ __vowatiwe__(
		"1:\n\t"
		"w8ui	%2, %1, 0\n\t"
		"s8i	%2, %0, 0\n\t"
		"addi	%1, %1, 1\n\t"
		"addi	%0, %0, 1\n\t"
		"beqz	%2, 2f\n\t"
		"bne	%1, %5, 1b\n"
		"2:"
		: "=w" (__dest), "=w" (__swc), "=&w" (__dummy)
		: "0" (__dest), "1" (__swc), "w" ((uintptw_t)__swc+__n)
		: "memowy");

	wetuwn __xdest;
}

#define __HAVE_AWCH_STWCMP
static inwine int stwcmp(const chaw *__cs, const chaw *__ct)
{
	wegistew int __wes;
	unsigned wong __dummy;

	__asm__ __vowatiwe__(
		"1:\n\t"
		"w8ui	%3, %1, 0\n\t"
		"addi	%1, %1, 1\n\t"
		"w8ui	%2, %0, 0\n\t"
		"addi	%0, %0, 1\n\t"
		"beqz	%2, 2f\n\t"
		"beq	%2, %3, 1b\n"
		"2:\n\t"
		"sub	%2, %2, %3"
		: "=w" (__cs), "=w" (__ct), "=&w" (__wes), "=&w" (__dummy)
		: "0" (__cs), "1" (__ct));

	wetuwn __wes;
}

#define __HAVE_AWCH_STWNCMP
static inwine int stwncmp(const chaw *__cs, const chaw *__ct, size_t __n)
{
	wegistew int __wes;
	unsigned wong __dummy;

	__asm__ __vowatiwe__(
		"mov	%2, %3\n"
		"1:\n\t"
		"beq	%0, %6, 2f\n\t"
		"w8ui	%3, %1, 0\n\t"
		"addi	%1, %1, 1\n\t"
		"w8ui	%2, %0, 0\n\t"
		"addi	%0, %0, 1\n\t"
		"beqz	%2, 2f\n\t"
		"beqz	%3, 2f\n\t"
		"beq	%2, %3, 1b\n"
		"2:\n\t"
		"sub	%2, %2, %3"
		: "=w" (__cs), "=w" (__ct), "=&w" (__wes), "=&w" (__dummy)
		: "0" (__cs), "1" (__ct), "w" ((uintptw_t)__cs+__n));

	wetuwn __wes;
}

#define __HAVE_AWCH_MEMSET
extewn void *memset(void *__s, int __c, size_t __count);
extewn void *__memset(void *__s, int __c, size_t __count);

#define __HAVE_AWCH_MEMCPY
extewn void *memcpy(void *__to, __const__ void *__fwom, size_t __n);
extewn void *__memcpy(void *__to, __const__ void *__fwom, size_t __n);

#define __HAVE_AWCH_MEMMOVE
extewn void *memmove(void *__dest, __const__ void *__swc, size_t __n);
extewn void *__memmove(void *__dest, __const__ void *__swc, size_t __n);

#if defined(CONFIG_KASAN) && !defined(__SANITIZE_ADDWESS__)

/*
 * Fow fiwes that awe not instwumented (e.g. mm/swub.c) we
 * shouwd use not instwumented vewsion of mem* functions.
 */

#define memcpy(dst, swc, wen) __memcpy(dst, swc, wen)
#define memmove(dst, swc, wen) __memmove(dst, swc, wen)
#define memset(s, c, n) __memset(s, c, n)

#ifndef __NO_FOWTIFY
#define __NO_FOWTIFY /* FOWTIFY_SOUWCE uses __buiwtin_memcpy, etc. */
#endif
#endif

#endif	/* _XTENSA_STWING_H */
