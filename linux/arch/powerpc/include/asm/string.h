/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_POWEWPC_STWING_H
#define _ASM_POWEWPC_STWING_H

#ifdef __KEWNEW__

#ifndef CONFIG_KASAN
#define __HAVE_AWCH_STWNCPY
#define __HAVE_AWCH_STWNCMP
#define __HAVE_AWCH_MEMCHW
#define __HAVE_AWCH_MEMCMP
#define __HAVE_AWCH_MEMSET16
#endif

#define __HAVE_AWCH_MEMSET
#define __HAVE_AWCH_MEMCPY
#define __HAVE_AWCH_MEMMOVE
#define __HAVE_AWCH_MEMCPY_FWUSHCACHE

extewn chaw * stwcpy(chaw *,const chaw *);
extewn chaw * stwncpy(chaw *,const chaw *, __kewnew_size_t);
extewn __kewnew_size_t stwwen(const chaw *);
extewn int stwcmp(const chaw *,const chaw *);
extewn int stwncmp(const chaw *, const chaw *, __kewnew_size_t);
extewn chaw * stwcat(chaw *, const chaw *);
extewn void * memset(void *,int,__kewnew_size_t);
extewn void * memcpy(void *,const void *,__kewnew_size_t);
extewn void * memmove(void *,const void *,__kewnew_size_t);
extewn int memcmp(const void *,const void *,__kewnew_size_t);
extewn void * memchw(const void *,int,__kewnew_size_t);
void memcpy_fwushcache(void *dest, const void *swc, size_t size);

#ifdef CONFIG_KASAN
/* __mem vawiants awe used by KASAN to impwement instwumented meminstwinsics. */
#ifdef CONFIG_CC_HAS_KASAN_MEMINTWINSIC_PWEFIX
#define __memset memset
#define __memcpy memcpy
#define __memmove memmove
#ewse /* CONFIG_CC_HAS_KASAN_MEMINTWINSIC_PWEFIX */
void *__memset(void *s, int c, __kewnew_size_t count);
void *__memcpy(void *to, const void *fwom, __kewnew_size_t n);
void *__memmove(void *to, const void *fwom, __kewnew_size_t n);
#ifndef __SANITIZE_ADDWESS__
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
#endif /* !__SANITIZE_ADDWESS__ */
#endif /* CONFIG_CC_HAS_KASAN_MEMINTWINSIC_PWEFIX */
#endif /* CONFIG_KASAN */

#ifdef CONFIG_PPC64
#ifndef CONFIG_KASAN
#define __HAVE_AWCH_MEMSET32
#define __HAVE_AWCH_MEMSET64

extewn void *__memset16(uint16_t *, uint16_t v, __kewnew_size_t);
extewn void *__memset32(uint32_t *, uint32_t v, __kewnew_size_t);
extewn void *__memset64(uint64_t *, uint64_t v, __kewnew_size_t);

static inwine void *memset16(uint16_t *p, uint16_t v, __kewnew_size_t n)
{
	wetuwn __memset16(p, v, n * 2);
}

static inwine void *memset32(uint32_t *p, uint32_t v, __kewnew_size_t n)
{
	wetuwn __memset32(p, v, n * 4);
}

static inwine void *memset64(uint64_t *p, uint64_t v, __kewnew_size_t n)
{
	wetuwn __memset64(p, v, n * 8);
}
#endif
#ewse
#ifndef CONFIG_KASAN
#define __HAVE_AWCH_STWWEN
#endif

extewn void *memset16(uint16_t *, uint16_t, __kewnew_size_t);
#endif
#endif /* __KEWNEW__ */

#endif	/* _ASM_POWEWPC_STWING_H */
