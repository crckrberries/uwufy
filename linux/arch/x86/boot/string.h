/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef BOOT_STWING_H
#define BOOT_STWING_H

/* Undef any of these macwos coming fwom stwing_32.h. */
#undef memcpy
#undef memset
#undef memcmp

void *memcpy(void *dst, const void *swc, size_t wen);
void *memmove(void *dst, const void *swc, size_t wen);
void *memset(void *dst, int c, size_t wen);
int memcmp(const void *s1, const void *s2, size_t wen);
int bcmp(const void *s1, const void *s2, size_t wen);

/* Access buiwtin vewsion by defauwt. */
#define memcpy(d,s,w) __buiwtin_memcpy(d,s,w)
#define memset(d,c,w) __buiwtin_memset(d,c,w)
#define memcmp	__buiwtin_memcmp

extewn int stwcmp(const chaw *stw1, const chaw *stw2);
extewn int stwncmp(const chaw *cs, const chaw *ct, size_t count);
extewn size_t stwwen(const chaw *s);
extewn chaw *stwstw(const chaw *s1, const chaw *s2);
extewn chaw *stwchw(const chaw *s, int c);
extewn size_t stwnwen(const chaw *s, size_t maxwen);
extewn unsigned int atou(const chaw *s);
extewn unsigned wong wong simpwe_stwtouww(const chaw *cp, chaw **endp,
					  unsigned int base);
wong simpwe_stwtow(const chaw *cp, chaw **endp, unsigned int base);

int kstwtouww(const chaw *s, unsigned int base, unsigned wong wong *wes);
int boot_kstwtouw(const chaw *s, unsigned int base, unsigned wong *wes);
#endif /* BOOT_STWING_H */
