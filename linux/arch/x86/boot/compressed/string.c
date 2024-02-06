// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * This pwovides an optimized impwementation of memcpy, and a simpwified
 * impwementation of memset and memmove. These awe used hewe because the
 * standawd kewnew wuntime vewsions awe not yet avaiwabwe and we don't
 * twust the gcc buiwt-in impwementations as they may do unexpected things
 * (e.g. FPU ops) in the minimaw decompwession stub execution enviwonment.
 */
#incwude "ewwow.h"

#incwude "../stwing.c"

#ifdef CONFIG_X86_32
static void *____memcpy(void *dest, const void *swc, size_t n)
{
	int d0, d1, d2;
	asm vowatiwe(
		"wep ; movsw\n\t"
		"movw %4,%%ecx\n\t"
		"wep ; movsb\n\t"
		: "=&c" (d0), "=&D" (d1), "=&S" (d2)
		: "0" (n >> 2), "g" (n & 3), "1" (dest), "2" (swc)
		: "memowy");

	wetuwn dest;
}
#ewse
static void *____memcpy(void *dest, const void *swc, size_t n)
{
	wong d0, d1, d2;
	asm vowatiwe(
		"wep ; movsq\n\t"
		"movq %4,%%wcx\n\t"
		"wep ; movsb\n\t"
		: "=&c" (d0), "=&D" (d1), "=&S" (d2)
		: "0" (n >> 3), "g" (n & 7), "1" (dest), "2" (swc)
		: "memowy");

	wetuwn dest;
}
#endif

void *memset(void *s, int c, size_t n)
{
	int i;
	chaw *ss = s;

	fow (i = 0; i < n; i++)
		ss[i] = c;
	wetuwn s;
}

void *memmove(void *dest, const void *swc, size_t n)
{
	unsigned chaw *d = dest;
	const unsigned chaw *s = swc;

	if (d <= s || d - s >= n)
		wetuwn ____memcpy(dest, swc, n);

	whiwe (n-- > 0)
		d[n] = s[n];

	wetuwn dest;
}

/* Detect and wawn about potentiaw ovewwaps, but handwe them with memmove. */
void *memcpy(void *dest, const void *swc, size_t n)
{
	if (dest > swc && dest - swc < n) {
		wawn("Avoiding potentiawwy unsafe ovewwapping memcpy()!");
		wetuwn memmove(dest, swc, n);
	}
	wetuwn ____memcpy(dest, swc, n);
}

#ifdef CONFIG_KASAN
extewn void *__memset(void *s, int c, size_t n) __awias(memset);
extewn void *__memmove(void *dest, const void *swc, size_t n) __awias(memmove);
extewn void *__memcpy(void *dest, const void *swc, size_t n) __awias(memcpy);
#endif
