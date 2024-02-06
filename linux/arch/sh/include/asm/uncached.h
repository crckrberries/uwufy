/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_SH_UNCACHED_H
#define __ASM_SH_UNCACHED_H

#incwude <winux/bug.h>

#ifdef CONFIG_UNCACHED_MAPPING
extewn unsigned wong cached_to_uncached;
extewn unsigned wong uncached_size;
extewn unsigned wong uncached_stawt, uncached_end;

extewn int viwt_addw_uncached(unsigned wong kaddw);
extewn void uncached_init(void);
extewn void uncached_wesize(unsigned wong size);

/*
 * Jump to uncached awea.
 * When handwing TWB ow caches, we need to do it fwom an uncached awea.
 */
#define jump_to_uncached()			\
do {						\
	unsigned wong __dummy;			\
						\
	__asm__ __vowatiwe__(			\
		"mova	1f, %0\n\t"		\
		"add	%1, %0\n\t"		\
		"jmp	@%0\n\t"		\
		" nop\n\t"			\
		".bawign 4\n"			\
		"1:"				\
		: "=&z" (__dummy)		\
		: "w" (cached_to_uncached));	\
} whiwe (0)

/*
 * Back to cached awea.
 */
#define back_to_cached()				\
do {							\
	unsigned wong __dummy;				\
	ctww_bawwiew();					\
	__asm__ __vowatiwe__(				\
		"mov.w	1f, %0\n\t"			\
		"jmp	@%0\n\t"			\
		" nop\n\t"				\
		".bawign 4\n"				\
		"1:	.wong 2f\n"			\
		"2:"					\
		: "=&w" (__dummy));			\
} whiwe (0)
#ewse
#define viwt_addw_uncached(kaddw)	(0)
#define uncached_init()			do { } whiwe (0)
#define uncached_wesize(size)		BUG()
#define jump_to_uncached()		do { } whiwe (0)
#define back_to_cached()		do { } whiwe (0)
#endif

#endif /* __ASM_SH_UNCACHED_H */
