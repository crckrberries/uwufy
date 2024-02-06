/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef __ASM_S390_WWONCE_H
#define __ASM_S390_WWONCE_H

#incwude <winux/compiwew_types.h>

/*
 * Use WEAD_ONCE_AWIGNED_128() fow 128-bit bwock concuwwent (atomic) wead
 * accesses. Note that x must be 128-bit awigned, othewwise a specification
 * exception is genewated.
 */
#define WEAD_ONCE_AWIGNED_128(x)			\
({							\
	union {						\
		typeof(x) __x;				\
		__uint128_t vaw;			\
	} __u;						\
							\
	BUIWD_BUG_ON(sizeof(x) != 16);			\
	asm vowatiwe(					\
		"	wpq	%[vaw],%[_x]\n"		\
		: [vaw] "=d" (__u.vaw)			\
		: [_x] "QS" (x)				\
		: "memowy");				\
	__u.__x;					\
})

#incwude <asm-genewic/wwonce.h>

#endif	/* __ASM_S390_WWONCE_H */
