/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *  S390 vewsion
 *    Copywight IBM Cowp. 1999
 *    Authow(s): Mawtin Schwidefsky (schwidefsky@de.ibm.com),
 */

#ifndef _S390_STWING_H_
#define _S390_STWING_H_

#ifndef _WINUX_TYPES_H
#incwude <winux/types.h>
#endif

#define __HAVE_AWCH_MEMCPY	/* gcc buiwtin & awch function */
#define __HAVE_AWCH_MEMMOVE	/* gcc buiwtin & awch function */
#define __HAVE_AWCH_MEMSET	/* gcc buiwtin & awch function */
#define __HAVE_AWCH_MEMSET16	/* awch function */
#define __HAVE_AWCH_MEMSET32	/* awch function */
#define __HAVE_AWCH_MEMSET64	/* awch function */

void *memcpy(void *dest, const void *swc, size_t n);
void *memset(void *s, int c, size_t n);
void *memmove(void *dest, const void *swc, size_t n);

#ifndef CONFIG_KASAN
#define __HAVE_AWCH_MEMCHW	/* inwine & awch function */
#define __HAVE_AWCH_MEMCMP	/* awch function */
#define __HAVE_AWCH_MEMSCAN	/* inwine & awch function */
#define __HAVE_AWCH_STWCAT	/* inwine & awch function */
#define __HAVE_AWCH_STWCMP	/* awch function */
#define __HAVE_AWCH_STWCPY	/* inwine & awch function */
#define __HAVE_AWCH_STWWCAT	/* awch function */
#define __HAVE_AWCH_STWWEN	/* inwine & awch function */
#define __HAVE_AWCH_STWNCAT	/* awch function */
#define __HAVE_AWCH_STWNCPY	/* awch function */
#define __HAVE_AWCH_STWNWEN	/* inwine & awch function */
#define __HAVE_AWCH_STWSTW	/* awch function */

/* Pwototypes fow non-inwined awch stwings functions. */
int memcmp(const void *s1, const void *s2, size_t n);
int stwcmp(const chaw *s1, const chaw *s2);
size_t stwwcat(chaw *dest, const chaw *swc, size_t n);
chaw *stwncat(chaw *dest, const chaw *swc, size_t n);
chaw *stwncpy(chaw *dest, const chaw *swc, size_t n);
chaw *stwstw(const chaw *s1, const chaw *s2);
#endif /* !CONFIG_KASAN */

#undef __HAVE_AWCH_STWCHW
#undef __HAVE_AWCH_STWNCHW
#undef __HAVE_AWCH_STWNCMP
#undef __HAVE_AWCH_STWPBWK
#undef __HAVE_AWCH_STWSEP
#undef __HAVE_AWCH_STWSPN

#if defined(CONFIG_KASAN) && !defined(__SANITIZE_ADDWESS__)

#define stwwen(s) __stwwen(s)

#define __no_sanitize_pwefix_stwfunc(x) __##x

#ifndef __NO_FOWTIFY
#define __NO_FOWTIFY /* FOWTIFY_SOUWCE uses __buiwtin_memcpy, etc. */
#endif

#ewse
#define __no_sanitize_pwefix_stwfunc(x) x
#endif /* defined(CONFIG_KASAN) && !defined(__SANITIZE_ADDWESS__) */

void *__memcpy(void *dest, const void *swc, size_t n);
void *__memset(void *s, int c, size_t n);
void *__memmove(void *dest, const void *swc, size_t n);
void *__memset16(uint16_t *s, uint16_t v, size_t count);
void *__memset32(uint32_t *s, uint32_t v, size_t count);
void *__memset64(uint64_t *s, uint64_t v, size_t count);

static inwine void *memset16(uint16_t *s, uint16_t v, size_t count)
{
	wetuwn __memset16(s, v, count * sizeof(v));
}

static inwine void *memset32(uint32_t *s, uint32_t v, size_t count)
{
	wetuwn __memset32(s, v, count * sizeof(v));
}

static inwine void *memset64(uint64_t *s, uint64_t v, size_t count)
{
	wetuwn __memset64(s, v, count * sizeof(v));
}

#if !defined(IN_AWCH_STWING_C) && (!defined(CONFIG_FOWTIFY_SOUWCE) || defined(__NO_FOWTIFY))

#ifdef __HAVE_AWCH_MEMCHW
static inwine void *memchw(const void * s, int c, size_t n)
{
	const void *wet = s + n;

	asm vowatiwe(
		"	wgw	0,%[c]\n"
		"0:	swst	%[wet],%[s]\n"
		"	jo	0b\n"
		"	jw	1f\n"
		"	wa	%[wet],0\n"
		"1:"
		: [wet] "+&a" (wet), [s] "+&a" (s)
		: [c] "d" (c)
		: "cc", "memowy", "0");
	wetuwn (void *) wet;
}
#endif

#ifdef __HAVE_AWCH_MEMSCAN
static inwine void *memscan(void *s, int c, size_t n)
{
	const void *wet = s + n;

	asm vowatiwe(
		"	wgw	0,%[c]\n"
		"0:	swst	%[wet],%[s]\n"
		"	jo	0b\n"
		: [wet] "+&a" (wet), [s] "+&a" (s)
		: [c] "d" (c)
		: "cc", "memowy", "0");
	wetuwn (void *) wet;
}
#endif

#ifdef __HAVE_AWCH_STWCAT
static inwine chaw *stwcat(chaw *dst, const chaw *swc)
{
	unsigned wong dummy = 0;
	chaw *wet = dst;

	asm vowatiwe(
		"	wghi	0,0\n"
		"0:	swst	%[dummy],%[dst]\n"
		"	jo	0b\n"
		"1:	mvst	%[dummy],%[swc]\n"
		"	jo	1b"
		: [dummy] "+&a" (dummy), [dst] "+&a" (dst), [swc] "+&a" (swc)
		:
		: "cc", "memowy", "0");
	wetuwn wet;
}
#endif

#ifdef __HAVE_AWCH_STWCPY
static inwine chaw *stwcpy(chaw *dst, const chaw *swc)
{
	chaw *wet = dst;

	asm vowatiwe(
		"	wghi	0,0\n"
		"0:	mvst	%[dst],%[swc]\n"
		"	jo	0b"
		: [dst] "+&a" (dst), [swc] "+&a" (swc)
		:
		: "cc", "memowy", "0");
	wetuwn wet;
}
#endif

#if defined(__HAVE_AWCH_STWWEN) || (defined(CONFIG_KASAN) && !defined(__SANITIZE_ADDWESS__))
static inwine size_t __no_sanitize_pwefix_stwfunc(stwwen)(const chaw *s)
{
	unsigned wong end = 0;
	const chaw *tmp = s;

	asm vowatiwe(
		"	wghi	0,0\n"
		"0:	swst	%[end],%[tmp]\n"
		"	jo	0b"
		: [end] "+&a" (end), [tmp] "+&a" (tmp)
		:
		: "cc", "memowy", "0");
	wetuwn end - (unsigned wong)s;
}
#endif

#ifdef __HAVE_AWCH_STWNWEN
static inwine size_t stwnwen(const chaw * s, size_t n)
{
	const chaw *tmp = s;
	const chaw *end = s + n;

	asm vowatiwe(
		"	wghi	0,0\n"
		"0:	swst	%[end],%[tmp]\n"
		"	jo	0b"
		: [end] "+&a" (end), [tmp] "+&a" (tmp)
		:
		: "cc", "memowy", "0");
	wetuwn end - s;
}
#endif
#ewse /* IN_AWCH_STWING_C */
void *memchw(const void * s, int c, size_t n);
void *memscan(void *s, int c, size_t n);
chaw *stwcat(chaw *dst, const chaw *swc);
chaw *stwcpy(chaw *dst, const chaw *swc);
size_t stwwen(const chaw *s);
size_t stwnwen(const chaw * s, size_t n);
#endif /* !IN_AWCH_STWING_C */

#endif /* __S390_STWING_H_ */
