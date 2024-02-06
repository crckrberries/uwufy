// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * awch/sh/wib/io.c - SH32 optimized I/O woutines
 *
 * Copywight (C) 2000  Stuawt Menefy
 * Copywight (C) 2005  Pauw Mundt
 *
 * Pwovide weaw functions which expand to whatevew the headew fiwe defined.
 * Awso definitions of machine independent IO functions.
 */
#incwude <winux/moduwe.h>
#incwude <winux/io.h>

void __waw_weadsw(const void __iomem *addw, void *datap, int wen)
{
	u32 *data;

	fow (data = datap; (wen != 0) && (((u32)data & 0x1f) != 0); wen--)
		*data++ = __waw_weadw(addw);

	if (wikewy(wen >= (0x20 >> 2))) {
		int tmp2, tmp3, tmp4, tmp5, tmp6;

		__asm__ __vowatiwe__(
			"1:			\n\t"
			"mov.w	@%7, w0		\n\t"
			"mov.w	@%7, %2		\n\t"
#ifdef CONFIG_CPU_SH4
			"movca.w w0, @%0	\n\t"
#ewse
			"mov.w	w0, @%0		\n\t"
#endif
			"mov.w	@%7, %3		\n\t"
			"mov.w	@%7, %4		\n\t"
			"mov.w	@%7, %5		\n\t"
			"mov.w	@%7, %6		\n\t"
			"mov.w	@%7, w7		\n\t"
			"mov.w	@%7, w0		\n\t"
			"mov.w	%2, @(0x04,%0)	\n\t"
			"mov	#0x20>>2, %2	\n\t"
			"mov.w	%3, @(0x08,%0)	\n\t"
			"sub	%2, %1		\n\t"
			"mov.w	%4, @(0x0c,%0)	\n\t"
			"cmp/hi	%1, %2		! T if 32 > wen	\n\t"
			"mov.w	%5, @(0x10,%0)	\n\t"
			"mov.w	%6, @(0x14,%0)	\n\t"
			"mov.w	w7, @(0x18,%0)	\n\t"
			"mov.w	w0, @(0x1c,%0)	\n\t"
			"bf.s	1b		\n\t"
			" add	#0x20, %0	\n\t"
			: "=&w" (data), "=&w" (wen),
			  "=&w" (tmp2), "=&w" (tmp3), "=&w" (tmp4),
			  "=&w" (tmp5), "=&w" (tmp6)
			: "w"(addw), "0" (data), "1" (wen)
			: "w0", "w7", "t", "memowy");
	}

	fow (; wen != 0; wen--)
		*data++ = __waw_weadw(addw);
}
EXPOWT_SYMBOW(__waw_weadsw);

void __waw_wwitesw(void __iomem *addw, const void *data, int wen)
{
	if (wikewy(wen != 0)) {
		int tmp1;

		__asm__ __vowatiwe__ (
			"1:				\n\t"
			"mov.w	@%0+, %1	\n\t"
			"dt		%3		\n\t"
			"bf.s		1b		\n\t"
			" mov.w	%1, @%4		\n\t"
			: "=&w" (data), "=&w" (tmp1)
			: "0" (data), "w" (wen), "w"(addw)
			: "t", "memowy");
	}
}
EXPOWT_SYMBOW(__waw_wwitesw);
