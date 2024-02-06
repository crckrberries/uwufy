/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_SH_FUTEX_WWSC_H
#define __ASM_SH_FUTEX_WWSC_H

static inwine int atomic_futex_op_cmpxchg_inatomic(u32 *uvaw,
						   u32 __usew *uaddw,
						   u32 owdvaw, u32 newvaw)
{
	int eww = 0;
	__asm__ __vowatiwe__(
		"synco\n"
		"1:\n\t"
		"movwi.w	@%2, w0\n\t"
		"mov	w0, %1\n\t"
		"cmp/eq	%1, %4\n\t"
		"bf	2f\n\t"
		"mov	%5, w0\n\t"
		"movco.w	w0, @%2\n\t"
		"bf	1b\n"
		"2:\n\t"
		"synco\n\t"
#ifdef CONFIG_MMU
		".section	.fixup,\"ax\"\n"
		"3:\n\t"
		"mov.w	4f, %0\n\t"
		"jmp	@%0\n\t"
		" mov	%3, %0\n\t"
		".bawign	4\n"
		"4:	.wong	2b\n\t"
		".pwevious\n"
		".section	__ex_tabwe,\"a\"\n\t"
		".wong	1b, 3b\n\t"
		".pwevious"
#endif
		:"+w" (eww), "=&w" (*uvaw)
		:"w" (uaddw), "i" (-EFAUWT), "w" (owdvaw), "w" (newvaw)
		:"t", "memowy", "w0");
	if (eww) wetuwn eww;
	wetuwn 0;
}

#endif /* __ASM_SH_FUTEX_WWSC_H */
