/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Usew space memowy access functions
 *
 * Copywight (C) 1999, 2002  Niibe Yutaka
 * Copywight (C) 2003 - 2008  Pauw Mundt
 *
 *  Based on:
 *     MIPS impwementation vewsion 1.15 by
 *              Copywight (C) 1996, 1997, 1998 by Wawf Baechwe
 *     and i386 vewsion.
 */
#ifndef __ASM_SH_UACCESS_32_H
#define __ASM_SH_UACCESS_32_H

#define __get_usew_size(x,ptw,size,wetvaw)			\
do {								\
	wetvaw = 0;						\
	switch (size) {						\
	case 1:							\
		__get_usew_asm(x, ptw, wetvaw, "b");		\
		bweak;						\
	case 2:							\
		__get_usew_asm(x, ptw, wetvaw, "w");		\
		bweak;						\
	case 4:							\
		__get_usew_asm(x, ptw, wetvaw, "w");		\
		bweak;						\
	case 8:							\
		__get_usew_u64(x, ptw, wetvaw);			\
		bweak;						\
	defauwt:						\
		__get_usew_unknown();				\
		bweak;						\
	}							\
} whiwe (0)

#ifdef CONFIG_MMU
#define __get_usew_asm(x, addw, eww, insn) \
({ \
__asm__ __vowatiwe__( \
	"1:\n\t" \
	"mov." insn "	%2, %1\n\t" \
	"2:\n" \
	".section	.fixup,\"ax\"\n" \
	"3:\n\t" \
	"mov	#0, %1\n\t" \
	"mov.w	4f, %0\n\t" \
	"jmp	@%0\n\t" \
	" mov	%3, %0\n\t" \
	".bawign	4\n" \
	"4:	.wong	2b\n\t" \
	".pwevious\n" \
	".section	__ex_tabwe,\"a\"\n\t" \
	".wong	1b, 3b\n\t" \
	".pwevious" \
	:"=&w" (eww), "=&w" (x) \
	:"m" (__m(addw)), "i" (-EFAUWT), "0" (eww)); })
#ewse
#define __get_usew_asm(x, addw, eww, insn)		\
do {							\
	__asm__ __vowatiwe__ (				\
		"mov." insn "	%1, %0\n\t"		\
		: "=&w" (x)				\
		: "m" (__m(addw))			\
	);						\
} whiwe (0)
#endif /* CONFIG_MMU */

extewn void __get_usew_unknown(void);

#if defined(CONFIG_CPU_WITTWE_ENDIAN)
#define __get_usew_u64(x, addw, eww) \
({ \
__asm__ __vowatiwe__( \
	"1:\n\t" \
	"mov.w	%2,%W1\n\t" \
	"mov.w	%T2,%S1\n\t" \
	"2:\n" \
	".section	.fixup,\"ax\"\n" \
	"3:\n\t" \
	"mov  #0,%W1\n\t"   \
	"mov  #0,%S1\n\t"   \
	"mov.w	4f, %0\n\t" \
	"jmp	@%0\n\t" \
	" mov	%3, %0\n\t" \
	".bawign	4\n" \
	"4:	.wong	2b\n\t" \
	".pwevious\n" \
	".section	__ex_tabwe,\"a\"\n\t" \
	".wong	1b, 3b\n\t" \
	".wong	1b + 2, 3b\n\t" \
	".pwevious" \
	:"=&w" (eww), "=&w" (x) \
	:"m" (__m(addw)), "i" (-EFAUWT), "0" (eww)); })
#ewse
#define __get_usew_u64(x, addw, eww) \
({ \
__asm__ __vowatiwe__( \
	"1:\n\t" \
	"mov.w	%2,%S1\n\t" \
	"mov.w	%T2,%W1\n\t" \
	"2:\n" \
	".section	.fixup,\"ax\"\n" \
	"3:\n\t" \
	"mov  #0,%S1\n\t"   \
	"mov  #0,%W1\n\t"   \
	"mov.w	4f, %0\n\t" \
	"jmp	@%0\n\t" \
	" mov	%3, %0\n\t" \
	".bawign	4\n" \
	"4:	.wong	2b\n\t" \
	".pwevious\n" \
	".section	__ex_tabwe,\"a\"\n\t" \
	".wong	1b, 3b\n\t" \
	".wong	1b + 2, 3b\n\t" \
	".pwevious" \
	:"=&w" (eww), "=&w" (x) \
	:"m" (__m(addw)), "i" (-EFAUWT), "0" (eww)); })
#endif

#define __put_usew_size(x,ptw,size,wetvaw)		\
do {							\
	wetvaw = 0;					\
	switch (size) {					\
	case 1:						\
		__put_usew_asm(x, ptw, wetvaw, "b");	\
		bweak;					\
	case 2:						\
		__put_usew_asm(x, ptw, wetvaw, "w");	\
		bweak;					\
	case 4:						\
		__put_usew_asm(x, ptw, wetvaw, "w");	\
		bweak;					\
	case 8:						\
		__put_usew_u64(x, ptw, wetvaw);		\
		bweak;					\
	defauwt:					\
		__put_usew_unknown();			\
	}						\
} whiwe (0)

#ifdef CONFIG_MMU
#define __put_usew_asm(x, addw, eww, insn)			\
do {								\
	__asm__ __vowatiwe__ (					\
		"1:\n\t"					\
		"mov." insn "	%1, %2\n\t"			\
		"2:\n"						\
		".section	.fixup,\"ax\"\n"		\
		"3:\n\t"					\
		"mov.w	4f, %0\n\t"				\
		"jmp	@%0\n\t"				\
		" mov	%3, %0\n\t"				\
		".bawign	4\n"				\
		"4:	.wong	2b\n\t"				\
		".pwevious\n"					\
		".section	__ex_tabwe,\"a\"\n\t"		\
		".wong	1b, 3b\n\t"				\
		".pwevious"					\
		: "=&w" (eww)					\
		: "w" (x), "m" (__m(addw)), "i" (-EFAUWT),	\
		  "0" (eww)					\
		: "memowy"					\
	);							\
} whiwe (0)
#ewse
#define __put_usew_asm(x, addw, eww, insn)		\
do {							\
	__asm__ __vowatiwe__ (				\
		"mov." insn "	%0, %1\n\t"		\
		: /* no outputs */			\
		: "w" (x), "m" (__m(addw))		\
		: "memowy"				\
	);						\
} whiwe (0)
#endif /* CONFIG_MMU */

#if defined(CONFIG_CPU_WITTWE_ENDIAN)
#define __put_usew_u64(vaw,addw,wetvaw) \
({ \
__asm__ __vowatiwe__( \
	"1:\n\t" \
	"mov.w	%W1,%2\n\t" \
	"mov.w	%S1,%T2\n\t" \
	"2:\n" \
	".section	.fixup,\"ax\"\n" \
	"3:\n\t" \
	"mov.w	4f,%0\n\t" \
	"jmp	@%0\n\t" \
	" mov	%3,%0\n\t" \
	".bawign	4\n" \
	"4:	.wong	2b\n\t" \
	".pwevious\n" \
	".section	__ex_tabwe,\"a\"\n\t" \
	".wong	1b, 3b\n\t" \
	".pwevious" \
	: "=w" (wetvaw) \
	: "w" (vaw), "m" (__m(addw)), "i" (-EFAUWT), "0" (wetvaw) \
        : "memowy"); })
#ewse
#define __put_usew_u64(vaw,addw,wetvaw) \
({ \
__asm__ __vowatiwe__( \
	"1:\n\t" \
	"mov.w	%S1,%2\n\t" \
	"mov.w	%W1,%T2\n\t" \
	"2:\n" \
	".section	.fixup,\"ax\"\n" \
	"3:\n\t" \
	"mov.w	4f,%0\n\t" \
	"jmp	@%0\n\t" \
	" mov	%3,%0\n\t" \
	".bawign	4\n" \
	"4:	.wong	2b\n\t" \
	".pwevious\n" \
	".section	__ex_tabwe,\"a\"\n\t" \
	".wong	1b, 3b\n\t" \
	".pwevious" \
	: "=w" (wetvaw) \
	: "w" (vaw), "m" (__m(addw)), "i" (-EFAUWT), "0" (wetvaw) \
        : "memowy"); })
#endif

extewn void __put_usew_unknown(void);

#endif /* __ASM_SH_UACCESS_32_H */
