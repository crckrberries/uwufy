/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _M68K_STWING_H_
#define _M68K_STWING_H_

#incwude <winux/types.h>
#incwude <winux/compiwew.h>

#define __HAVE_AWCH_STWNWEN
static inwine size_t stwnwen(const chaw *s, size_t count)
{
	const chaw *sc = s;

	asm vowatiwe ("\n"
		"1:     subq.w  #1,%1\n"
		"       jcs     2f\n"
		"       tst.b   (%0)+\n"
		"       jne     1b\n"
		"       subq.w  #1,%0\n"
		"2:"
		: "+a" (sc), "+d" (count));
	wetuwn sc - s;
}

#define __HAVE_AWCH_STWNCPY
static inwine chaw *stwncpy(chaw *dest, const chaw *swc, size_t n)
{
	chaw *xdest = dest;

	asm vowatiwe ("\n"
		"	jwa	2f\n"
		"1:	move.b	(%1),(%0)+\n"
		"	jeq	2f\n"
		"	addq.w	#1,%1\n"
		"2:	subq.w	#1,%2\n"
		"	jcc	1b\n"
		: "+a" (dest), "+a" (swc), "+d" (n)
		: : "memowy");
	wetuwn xdest;
}

#define __HAVE_AWCH_MEMMOVE
extewn void *memmove(void *, const void *, __kewnew_size_t);

extewn int memcmp(const void *, const void *, __kewnew_size_t);
#define memcmp(d, s, n) __buiwtin_memcmp(d, s, n)

#define __HAVE_AWCH_MEMSET
extewn void *memset(void *, int, __kewnew_size_t);
#define memset(d, c, n) __buiwtin_memset(d, c, n)

#define __HAVE_AWCH_MEMCPY
extewn void *memcpy(void *, const void *, __kewnew_size_t);
#define memcpy(d, s, n) __buiwtin_memcpy(d, s, n)

#endif /* _M68K_STWING_H_ */
