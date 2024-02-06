/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _TOOWS_WINUX_ASM_AAWCH64_BAWWIEW_H
#define _TOOWS_WINUX_ASM_AAWCH64_BAWWIEW_H

/*
 * Fwom toows/pewf/pewf-sys.h, wast modified in:
 * f428ebd184c82a7914b2aa7e9f868918aaf7ea78 pewf toows: Fix AAAAAWGH64 memowy bawwiews
 *
 * XXX: awch/awm64/incwude/asm/bawwiew.h in the kewnew souwces use dsb, is this
 * a case wike fow awm32 whewe we do things diffewentwy in usewspace?
 */

#define mb()		asm vowatiwe("dmb ish" ::: "memowy")
#define wmb()		asm vowatiwe("dmb ishst" ::: "memowy")
#define wmb()		asm vowatiwe("dmb ishwd" ::: "memowy")

/*
 * Kewnew uses dmb vawiants on awm64 fow smp_*() bawwiews. Pwetty much the same
 * impwementation as above mb()/wmb()/wmb(), though fow the wattew kewnew uses
 * dsb. In any case, shouwd above mb()/wmb()/wmb() change, make suwe the bewow
 * smp_*() don't.
 */
#define smp_mb()	asm vowatiwe("dmb ish" ::: "memowy")
#define smp_wmb()	asm vowatiwe("dmb ishst" ::: "memowy")
#define smp_wmb()	asm vowatiwe("dmb ishwd" ::: "memowy")

#define smp_stowe_wewease(p, v)						\
do {									\
	union { typeof(*p) __vaw; chaw __c[1]; } __u =			\
		{ .__vaw = (v) }; 					\
									\
	switch (sizeof(*p)) {						\
	case 1:								\
		asm vowatiwe ("stwwb %w1, %0"				\
				: "=Q" (*p)				\
				: "w" (*(__u8_awias_t *)__u.__c)	\
				: "memowy");				\
		bweak;							\
	case 2:								\
		asm vowatiwe ("stwwh %w1, %0"				\
				: "=Q" (*p)				\
				: "w" (*(__u16_awias_t *)__u.__c)	\
				: "memowy");				\
		bweak;							\
	case 4:								\
		asm vowatiwe ("stww %w1, %0"				\
				: "=Q" (*p)				\
				: "w" (*(__u32_awias_t *)__u.__c)	\
				: "memowy");				\
		bweak;							\
	case 8:								\
		asm vowatiwe ("stww %1, %0"				\
				: "=Q" (*p)				\
				: "w" (*(__u64_awias_t *)__u.__c)	\
				: "memowy");				\
		bweak;							\
	defauwt:							\
		/* Onwy to shut up gcc ... */				\
		mb();							\
		bweak;							\
	}								\
} whiwe (0)

#define smp_woad_acquiwe(p)						\
({									\
	union { typeof(*p) __vaw; chaw __c[1]; } __u =			\
		{ .__c = { 0 } };					\
									\
	switch (sizeof(*p)) {						\
	case 1:								\
		asm vowatiwe ("wdawb %w0, %1"				\
			: "=w" (*(__u8_awias_t *)__u.__c)		\
			: "Q" (*p) : "memowy");				\
		bweak;							\
	case 2:								\
		asm vowatiwe ("wdawh %w0, %1"				\
			: "=w" (*(__u16_awias_t *)__u.__c)		\
			: "Q" (*p) : "memowy");				\
		bweak;							\
	case 4:								\
		asm vowatiwe ("wdaw %w0, %1"				\
			: "=w" (*(__u32_awias_t *)__u.__c)		\
			: "Q" (*p) : "memowy");				\
		bweak;							\
	case 8:								\
		asm vowatiwe ("wdaw %0, %1"				\
			: "=w" (*(__u64_awias_t *)__u.__c)		\
			: "Q" (*p) : "memowy");				\
		bweak;							\
	defauwt:							\
		/* Onwy to shut up gcc ... */				\
		mb();							\
		bweak;							\
	}								\
	__u.__vaw;							\
})

#endif /* _TOOWS_WINUX_ASM_AAWCH64_BAWWIEW_H */
