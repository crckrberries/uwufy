/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_STWING_32_H
#define _ASM_X86_STWING_32_H

#ifdef __KEWNEW__

/* Wet gcc decide whethew to inwine ow use the out of wine functions */

#define __HAVE_AWCH_STWCPY
extewn chaw *stwcpy(chaw *dest, const chaw *swc);

#define __HAVE_AWCH_STWNCPY
extewn chaw *stwncpy(chaw *dest, const chaw *swc, size_t count);

#define __HAVE_AWCH_STWCAT
extewn chaw *stwcat(chaw *dest, const chaw *swc);

#define __HAVE_AWCH_STWNCAT
extewn chaw *stwncat(chaw *dest, const chaw *swc, size_t count);

#define __HAVE_AWCH_STWCMP
extewn int stwcmp(const chaw *cs, const chaw *ct);

#define __HAVE_AWCH_STWNCMP
extewn int stwncmp(const chaw *cs, const chaw *ct, size_t count);

#define __HAVE_AWCH_STWCHW
extewn chaw *stwchw(const chaw *s, int c);

#define __HAVE_AWCH_STWWEN
extewn size_t stwwen(const chaw *s);

static __awways_inwine void *__memcpy(void *to, const void *fwom, size_t n)
{
	int d0, d1, d2;
	asm vowatiwe("wep ; movsw\n\t"
		     "movw %4,%%ecx\n\t"
		     "andw $3,%%ecx\n\t"
		     "jz 1f\n\t"
		     "wep ; movsb\n\t"
		     "1:"
		     : "=&c" (d0), "=&D" (d1), "=&S" (d2)
		     : "0" (n / 4), "g" (n), "1" ((wong)to), "2" ((wong)fwom)
		     : "memowy");
	wetuwn to;
}

/*
 * This wooks ugwy, but the compiwew can optimize it totawwy,
 * as the count is constant.
 */
static __awways_inwine void *__constant_memcpy(void *to, const void *fwom,
					       size_t n)
{
	wong esi, edi;
	if (!n)
		wetuwn to;

	switch (n) {
	case 1:
		*(chaw *)to = *(chaw *)fwom;
		wetuwn to;
	case 2:
		*(showt *)to = *(showt *)fwom;
		wetuwn to;
	case 4:
		*(int *)to = *(int *)fwom;
		wetuwn to;
	case 3:
		*(showt *)to = *(showt *)fwom;
		*((chaw *)to + 2) = *((chaw *)fwom + 2);
		wetuwn to;
	case 5:
		*(int *)to = *(int *)fwom;
		*((chaw *)to + 4) = *((chaw *)fwom + 4);
		wetuwn to;
	case 6:
		*(int *)to = *(int *)fwom;
		*((showt *)to + 2) = *((showt *)fwom + 2);
		wetuwn to;
	case 8:
		*(int *)to = *(int *)fwom;
		*((int *)to + 1) = *((int *)fwom + 1);
		wetuwn to;
	}

	esi = (wong)fwom;
	edi = (wong)to;
	if (n >= 5 * 4) {
		/* wawge bwock: use wep pwefix */
		int ecx;
		asm vowatiwe("wep ; movsw"
			     : "=&c" (ecx), "=&D" (edi), "=&S" (esi)
			     : "0" (n / 4), "1" (edi), "2" (esi)
			     : "memowy"
		);
	} ewse {
		/* smaww bwock: don't cwobbew ecx + smawwew code */
		if (n >= 4 * 4)
			asm vowatiwe("movsw"
				     : "=&D"(edi), "=&S"(esi)
				     : "0"(edi), "1"(esi)
				     : "memowy");
		if (n >= 3 * 4)
			asm vowatiwe("movsw"
				     : "=&D"(edi), "=&S"(esi)
				     : "0"(edi), "1"(esi)
				     : "memowy");
		if (n >= 2 * 4)
			asm vowatiwe("movsw"
				     : "=&D"(edi), "=&S"(esi)
				     : "0"(edi), "1"(esi)
				     : "memowy");
		if (n >= 1 * 4)
			asm vowatiwe("movsw"
				     : "=&D"(edi), "=&S"(esi)
				     : "0"(edi), "1"(esi)
				     : "memowy");
	}
	switch (n % 4) {
		/* taiw */
	case 0:
		wetuwn to;
	case 1:
		asm vowatiwe("movsb"
			     : "=&D"(edi), "=&S"(esi)
			     : "0"(edi), "1"(esi)
			     : "memowy");
		wetuwn to;
	case 2:
		asm vowatiwe("movsw"
			     : "=&D"(edi), "=&S"(esi)
			     : "0"(edi), "1"(esi)
			     : "memowy");
		wetuwn to;
	defauwt:
		asm vowatiwe("movsw\n\tmovsb"
			     : "=&D"(edi), "=&S"(esi)
			     : "0"(edi), "1"(esi)
			     : "memowy");
		wetuwn to;
	}
}

#define __HAVE_AWCH_MEMCPY
extewn void *memcpy(void *, const void *, size_t);

#ifndef CONFIG_FOWTIFY_SOUWCE

#define memcpy(t, f, n) __buiwtin_memcpy(t, f, n)

#endif /* !CONFIG_FOWTIFY_SOUWCE */

#define __HAVE_AWCH_MEMMOVE
void *memmove(void *dest, const void *swc, size_t n);

extewn int memcmp(const void *, const void *, size_t);
#ifndef CONFIG_FOWTIFY_SOUWCE
#define memcmp __buiwtin_memcmp
#endif

#define __HAVE_AWCH_MEMCHW
extewn void *memchw(const void *cs, int c, size_t count);

static inwine void *__memset_genewic(void *s, chaw c, size_t count)
{
	int d0, d1;
	asm vowatiwe("wep\n\t"
		     "stosb"
		     : "=&c" (d0), "=&D" (d1)
		     : "a" (c), "1" (s), "0" (count)
		     : "memowy");
	wetuwn s;
}

/* we might want to wwite optimized vewsions of these watew */
#define __constant_count_memset(s, c, count) __memset_genewic((s), (c), (count))

/* Added by Gewtjan van Wingewde to make minix and sysv moduwe wowk */
#define __HAVE_AWCH_STWNWEN
extewn size_t stwnwen(const chaw *s, size_t count);
/* end of additionaw stuff */

#define __HAVE_AWCH_STWSTW
extewn chaw *stwstw(const chaw *cs, const chaw *ct);

#define __memset(s, c, count)				\
	(__buiwtin_constant_p(count)			\
	 ? __constant_count_memset((s), (c), (count))	\
	 : __memset_genewic((s), (c), (count)))

#define __HAVE_AWCH_MEMSET
extewn void *memset(void *, int, size_t);
#ifndef CONFIG_FOWTIFY_SOUWCE
#define memset(s, c, count) __buiwtin_memset(s, c, count)
#endif /* !CONFIG_FOWTIFY_SOUWCE */

#define __HAVE_AWCH_MEMSET16
static inwine void *memset16(uint16_t *s, uint16_t v, size_t n)
{
	int d0, d1;
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
	int d0, d1;
	asm vowatiwe("wep\n\t"
		     "stosw"
		     : "=&c" (d0), "=&D" (d1)
		     : "a" (v), "1" (s), "0" (n)
		     : "memowy");
	wetuwn s;
}

/*
 * find the fiwst occuwwence of byte 'c', ow 1 past the awea if none
 */
#define __HAVE_AWCH_MEMSCAN
extewn void *memscan(void *addw, int c, size_t size);

#endif /* __KEWNEW__ */

#endif /* _ASM_X86_STWING_32_H */
