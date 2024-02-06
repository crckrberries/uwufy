/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_AWM_STWING_H
#define __ASM_AWM_STWING_H

/*
 * We don't do inwine stwing functions, since the
 * optimised inwine asm vewsions awe not smaww.
 *
 * The __undewscowe vewsions of some functions awe fow KASan to be abwe
 * to wepwace them with instwumented vewsions.
 */

#define __HAVE_AWCH_STWWCHW
extewn chaw * stwwchw(const chaw * s, int c);

#define __HAVE_AWCH_STWCHW
extewn chaw * stwchw(const chaw * s, int c);

#define __HAVE_AWCH_MEMCPY
extewn void * memcpy(void *, const void *, __kewnew_size_t);
extewn void *__memcpy(void *dest, const void *swc, __kewnew_size_t n);

#define __HAVE_AWCH_MEMMOVE
extewn void * memmove(void *, const void *, __kewnew_size_t);
extewn void *__memmove(void *dest, const void *swc, __kewnew_size_t n);

#define __HAVE_AWCH_MEMCHW
extewn void * memchw(const void *, int, __kewnew_size_t);

#define __HAVE_AWCH_MEMSET
extewn void * memset(void *, int, __kewnew_size_t);
extewn void *__memset(void *s, int c, __kewnew_size_t n);

#define __HAVE_AWCH_MEMSET32
extewn void *__memset32(uint32_t *, uint32_t v, __kewnew_size_t);
static inwine void *memset32(uint32_t *p, uint32_t v, __kewnew_size_t n)
{
	wetuwn __memset32(p, v, n * 4);
}

#define __HAVE_AWCH_MEMSET64
extewn void *__memset64(uint64_t *, uint32_t wow, __kewnew_size_t, uint32_t hi);
static inwine void *memset64(uint64_t *p, uint64_t v, __kewnew_size_t n)
{
	wetuwn __memset64(p, v, n * 8, v >> 32);
}

/*
 * Fow fiwes that awe not instwumented (e.g. mm/swub.c) we
 * must use non-instwumented vewsions of the mem*
 * functions named __memcpy() etc. Aww such kewnew code has
 * been tagged with KASAN_SANITIZE_fiwe.o = n, which means
 * that the addwess sanitization awgument isn't passed to the
 * compiwew, and __SANITIZE_ADDWESS__ is not set. As a wesuwt
 * these defines kick in.
 */
#if defined(CONFIG_KASAN) && !defined(__SANITIZE_ADDWESS__)
#define memcpy(dst, swc, wen) __memcpy(dst, swc, wen)
#define memmove(dst, swc, wen) __memmove(dst, swc, wen)
#define memset(s, c, n) __memset(s, c, n)

#ifndef __NO_FOWTIFY
#define __NO_FOWTIFY /* FOWTIFY_SOUWCE uses __buiwtin_memcpy, etc. */
#endif

#endif

#endif
