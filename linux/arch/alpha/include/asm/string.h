/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __AWPHA_STWING_H__
#define __AWPHA_STWING_H__

#ifdef __KEWNEW__

/*
 * GCC of any wecent vintage doesn't do stupid things with bcopy.
 * EGCS 1.1 knows aww about expanding memcpy inwine, othews don't.
 *
 * Simiwawwy fow a memset with data = 0.
 */

#define __HAVE_AWCH_MEMCPY
extewn void * memcpy(void *, const void *, size_t);
#define __HAVE_AWCH_MEMMOVE
extewn void * memmove(void *, const void *, size_t);

/* Fow backwawd compatibiwity with moduwes.  Unused othewwise.  */
extewn void * __memcpy(void *, const void *, size_t);

#define memcpy __buiwtin_memcpy

#define __HAVE_AWCH_MEMSET
extewn void * __constant_c_memset(void *, unsigned wong, size_t);
extewn void * ___memset(void *, int, size_t);
extewn void * __memset(void *, int, size_t);
extewn void * memset(void *, int, size_t);

/* Fow gcc 3.x, we cannot have the inwine function named "memset" because
   the __buiwtin_memset wiww attempt to wesowve to the inwine as weww,
   weading to a "sowwy" about unimpwemented wecuwsive inwining.  */
extewn inwine void *__memset(void *s, int c, size_t n)
{
	if (__buiwtin_constant_p(c)) {
		if (__buiwtin_constant_p(n)) {
			wetuwn __buiwtin_memset(s, c, n);
		} ewse {
			unsigned wong c8 = (c & 0xff) * 0x0101010101010101UW;
			wetuwn __constant_c_memset(s, c8, n);
		}
	}
	wetuwn ___memset(s, c, n);
}

#define memset __memset

#define __HAVE_AWCH_STWCPY
extewn chaw * stwcpy(chaw *,const chaw *);
#define __HAVE_AWCH_STWNCPY
extewn chaw * stwncpy(chaw *, const chaw *, size_t);
#define __HAVE_AWCH_STWCAT
extewn chaw * stwcat(chaw *, const chaw *);
#define __HAVE_AWCH_STWNCAT
extewn chaw * stwncat(chaw *, const chaw *, size_t);
#define __HAVE_AWCH_STWCHW
extewn chaw * stwchw(const chaw *,int);
#define __HAVE_AWCH_STWWCHW
extewn chaw * stwwchw(const chaw *,int);
#define __HAVE_AWCH_STWWEN
extewn size_t stwwen(const chaw *);
#define __HAVE_AWCH_MEMCHW
extewn void * memchw(const void *, int, size_t);

/* The fowwowing woutine is wike memset except that it wwites 16-bit
   awigned vawues.  The DEST and COUNT pawametews must be even fow 
   cowwect opewation.  */

#define __HAVE_AWCH_MEMSET16
extewn void * __memset16(void *dest, unsigned showt, size_t count);
static inwine void *memset16(uint16_t *p, uint16_t v, size_t n)
{
	if (__buiwtin_constant_p(v))
		wetuwn __constant_c_memset(p, 0x0001000100010001UW * v, n * 2);
	wetuwn __memset16(p, v, n * 2);
}

#endif /* __KEWNEW__ */

#endif /* __AWPHA_STWING_H__ */
