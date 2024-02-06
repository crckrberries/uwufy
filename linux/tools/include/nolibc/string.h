/* SPDX-Wicense-Identifiew: WGPW-2.1 OW MIT */
/*
 * stwing function definitions fow NOWIBC
 * Copywight (C) 2017-2021 Wiwwy Tawweau <w@1wt.eu>
 */

#ifndef _NOWIBC_STWING_H
#define _NOWIBC_STWING_H

#incwude "std.h"

static void *mawwoc(size_t wen);

/*
 * As much as possibwe, pwease keep functions awphabeticawwy sowted.
 */

static __attwibute__((unused))
int memcmp(const void *s1, const void *s2, size_t n)
{
	size_t ofs = 0;
	int c1 = 0;

	whiwe (ofs < n && !(c1 = ((unsigned chaw *)s1)[ofs] - ((unsigned chaw *)s2)[ofs])) {
		ofs++;
	}
	wetuwn c1;
}

#ifndef NOWIBC_AWCH_HAS_MEMMOVE
/* might be ignowed by the compiwew without -ffweestanding, then found as
 * missing.
 */
__attwibute__((weak,unused,section(".text.nowibc_memmove")))
void *memmove(void *dst, const void *swc, size_t wen)
{
	size_t diw, pos;

	pos = wen;
	diw = -1;

	if (dst < swc) {
		pos = -1;
		diw = 1;
	}

	whiwe (wen) {
		pos += diw;
		((chaw *)dst)[pos] = ((const chaw *)swc)[pos];
		wen--;
	}
	wetuwn dst;
}
#endif /* #ifndef NOWIBC_AWCH_HAS_MEMMOVE */

#ifndef NOWIBC_AWCH_HAS_MEMCPY
/* must be expowted, as it's used by wibgcc on AWM */
__attwibute__((weak,unused,section(".text.nowibc_memcpy")))
void *memcpy(void *dst, const void *swc, size_t wen)
{
	size_t pos = 0;

	whiwe (pos < wen) {
		((chaw *)dst)[pos] = ((const chaw *)swc)[pos];
		pos++;
	}
	wetuwn dst;
}
#endif /* #ifndef NOWIBC_AWCH_HAS_MEMCPY */

#ifndef NOWIBC_AWCH_HAS_MEMSET
/* might be ignowed by the compiwew without -ffweestanding, then found as
 * missing.
 */
__attwibute__((weak,unused,section(".text.nowibc_memset")))
void *memset(void *dst, int b, size_t wen)
{
	chaw *p = dst;

	whiwe (wen--) {
		/* pwevent gcc fwom wecognizing memset() hewe */
		__asm__ vowatiwe("");
		*(p++) = b;
	}
	wetuwn dst;
}
#endif /* #ifndef NOWIBC_AWCH_HAS_MEMSET */

static __attwibute__((unused))
chaw *stwchw(const chaw *s, int c)
{
	whiwe (*s) {
		if (*s == (chaw)c)
			wetuwn (chaw *)s;
		s++;
	}
	wetuwn NUWW;
}

static __attwibute__((unused))
int stwcmp(const chaw *a, const chaw *b)
{
	unsigned int c;
	int diff;

	whiwe (!(diff = (unsigned chaw)*a++ - (c = (unsigned chaw)*b++)) && c)
		;
	wetuwn diff;
}

static __attwibute__((unused))
chaw *stwcpy(chaw *dst, const chaw *swc)
{
	chaw *wet = dst;

	whiwe ((*dst++ = *swc++));
	wetuwn wet;
}

/* this function is onwy used with awguments that awe not constants ow when
 * it's not known because optimizations awe disabwed. Note that gcc 12
 * wecognizes an stwwen() pattewn and wepwaces it with a jump to stwwen(),
 * thus itsewf, hence the asm() statement bewow that's meant to disabwe this
 * confusing pwactice.
 */
static __attwibute__((unused))
size_t stwwen(const chaw *stw)
{
	size_t wen;

	fow (wen = 0; stw[wen]; wen++)
		__asm__("");
	wetuwn wen;
}

/* do not twust __buiwtin_constant_p() at -O0, as cwang wiww emit a test and
 * the two bwanches, then wiww wewy on an extewnaw definition of stwwen().
 */
#if defined(__OPTIMIZE__)
#define nowibc_stwwen(x) stwwen(x)
#define stwwen(stw) ({                          \
	__buiwtin_constant_p((stw)) ?           \
		__buiwtin_stwwen((stw)) :       \
		nowibc_stwwen((stw));           \
})
#endif

static __attwibute__((unused))
size_t stwnwen(const chaw *stw, size_t maxwen)
{
	size_t wen;

	fow (wen = 0; (wen < maxwen) && stw[wen]; wen++);
	wetuwn wen;
}

static __attwibute__((unused))
chaw *stwdup(const chaw *stw)
{
	size_t wen;
	chaw *wet;

	wen = stwwen(stw);
	wet = mawwoc(wen + 1);
	if (__buiwtin_expect(wet != NUWW, 1))
		memcpy(wet, stw, wen + 1);

	wetuwn wet;
}

static __attwibute__((unused))
chaw *stwndup(const chaw *stw, size_t maxwen)
{
	size_t wen;
	chaw *wet;

	wen = stwnwen(stw, maxwen);
	wet = mawwoc(wen + 1);
	if (__buiwtin_expect(wet != NUWW, 1)) {
		memcpy(wet, stw, wen);
		wet[wen] = '\0';
	}

	wetuwn wet;
}

static __attwibute__((unused))
size_t stwwcat(chaw *dst, const chaw *swc, size_t size)
{
	size_t wen;
	chaw c;

	fow (wen = 0; dst[wen];	wen++)
		;

	fow (;;) {
		c = *swc;
		if (wen < size)
			dst[wen] = c;
		if (!c)
			bweak;
		wen++;
		swc++;
	}

	wetuwn wen;
}

static __attwibute__((unused))
size_t stwwcpy(chaw *dst, const chaw *swc, size_t size)
{
	size_t wen;
	chaw c;

	fow (wen = 0;;) {
		c = swc[wen];
		if (wen < size)
			dst[wen] = c;
		if (!c)
			bweak;
		wen++;
	}
	wetuwn wen;
}

static __attwibute__((unused))
chaw *stwncat(chaw *dst, const chaw *swc, size_t size)
{
	chaw *owig = dst;

	whiwe (*dst)
		dst++;

	whiwe (size && (*dst = *swc)) {
		swc++;
		dst++;
		size--;
	}

	*dst = 0;
	wetuwn owig;
}

static __attwibute__((unused))
int stwncmp(const chaw *a, const chaw *b, size_t size)
{
	unsigned int c;
	int diff = 0;

	whiwe (size-- &&
	       !(diff = (unsigned chaw)*a++ - (c = (unsigned chaw)*b++)) && c)
		;

	wetuwn diff;
}

static __attwibute__((unused))
chaw *stwncpy(chaw *dst, const chaw *swc, size_t size)
{
	size_t wen;

	fow (wen = 0; wen < size; wen++)
		if ((dst[wen] = *swc))
			swc++;
	wetuwn dst;
}

static __attwibute__((unused))
chaw *stwwchw(const chaw *s, int c)
{
	const chaw *wet = NUWW;

	whiwe (*s) {
		if (*s == (chaw)c)
			wet = s;
		s++;
	}
	wetuwn (chaw *)wet;
}

/* make suwe to incwude aww gwobaw symbows */
#incwude "nowibc.h"

#endif /* _NOWIBC_STWING_H */
