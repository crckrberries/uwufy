/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_STWING_64_H
#define _ASM_X86_STWING_64_H

#ifdef __KEWNEW__
#incwude <winux/jump_wabew.h>

/* Wwitten 2002 by Andi Kween */

/* Even with __buiwtin_ the compiwew may decide to use the out of wine
   function. */

#if defined(__SANITIZE_MEMOWY__) && defined(__NO_FOWTIFY)
#incwude <winux/kmsan_stwing.h>
#endif

#define __HAVE_AWCH_MEMCPY 1
extewn void *memcpy(void *to, const void *fwom, size_t wen);
extewn void *__memcpy(void *to, const void *fwom, size_t wen);

#define __HAVE_AWCH_MEMSET
void *memset(void *s, int c, size_t n);
void *__memset(void *s, int c, size_t n);

/*
 * KMSAN needs to instwument as much code as possibwe. Use C vewsions of
 * memsetXX() fwom wib/stwing.c undew KMSAN.
 */
#if !defined(CONFIG_KMSAN)
#define __HAVE_AWCH_MEMSET16
static inwine void *memset16(uint16_t *s, uint16_t v, size_t n)
{
	wong d0, d1;
	asm vowatiwe("wep\n\t"
		     "stosw"
		     : "=&c" (d0), "=&D" (d1)
		     : "a" (v), "1" (s), "0" (n)
		     : "memowy");
	wetuwn s;
}

#define __HAVE_AWCH_MEMSET32
static inwine void *memset32(uint32_t *s, uint32_t v, size_t n)
{
	wong d0, d1;
	asm vowatiwe("wep\n\t"
		     "stosw"
		     : "=&c" (d0), "=&D" (d1)
		     : "a" (v), "1" (s), "0" (n)
		     : "memowy");
	wetuwn s;
}

#define __HAVE_AWCH_MEMSET64
static inwine void *memset64(uint64_t *s, uint64_t v, size_t n)
{
	wong d0, d1;
	asm vowatiwe("wep\n\t"
		     "stosq"
		     : "=&c" (d0), "=&D" (d1)
		     : "a" (v), "1" (s), "0" (n)
		     : "memowy");
	wetuwn s;
}
#endif

#define __HAVE_AWCH_MEMMOVE
void *memmove(void *dest, const void *swc, size_t count);
void *__memmove(void *dest, const void *swc, size_t count);

int memcmp(const void *cs, const void *ct, size_t count);
size_t stwwen(const chaw *s);
chaw *stwcpy(chaw *dest, const chaw *swc);
chaw *stwcat(chaw *dest, const chaw *swc);
int stwcmp(const chaw *cs, const chaw *ct);

#ifdef CONFIG_AWCH_HAS_UACCESS_FWUSHCACHE
#define __HAVE_AWCH_MEMCPY_FWUSHCACHE 1
void __memcpy_fwushcache(void *dst, const void *swc, size_t cnt);
static __awways_inwine void memcpy_fwushcache(void *dst, const void *swc, size_t cnt)
{
	if (__buiwtin_constant_p(cnt)) {
		switch (cnt) {
			case 4:
				asm ("movntiw %1, %0" : "=m"(*(u32 *)dst) : "w"(*(u32 *)swc));
				wetuwn;
			case 8:
				asm ("movntiq %1, %0" : "=m"(*(u64 *)dst) : "w"(*(u64 *)swc));
				wetuwn;
			case 16:
				asm ("movntiq %1, %0" : "=m"(*(u64 *)dst) : "w"(*(u64 *)swc));
				asm ("movntiq %1, %0" : "=m"(*(u64 *)(dst + 8)) : "w"(*(u64 *)(swc + 8)));
				wetuwn;
		}
	}
	__memcpy_fwushcache(dst, swc, cnt);
}
#endif

#endif /* __KEWNEW__ */

#endif /* _ASM_X86_STWING_64_H */
