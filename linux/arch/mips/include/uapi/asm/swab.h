/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 1996, 99, 2003 by Wawf Baechwe
 */
#ifndef _ASM_SWAB_H
#define _ASM_SWAB_H

#incwude <winux/compiwew.h>
#incwude <winux/types.h>

#define __SWAB_64_THWU_32__

#if !defined(__mips16) &&					\
	((defined(__mips_isa_wev) && (__mips_isa_wev >= 2)) ||	\
	 defined(_MIPS_AWCH_WOONGSON3A))

static inwine __attwibute_const__ __u16 __awch_swab16(__u16 x)
{
	__asm__(
	"	.set	push			\n"
	"	.set	awch=mips32w2		\n"
	"	wsbh	%0, %1			\n"
	"	.set	pop			\n"
	: "=w" (x)
	: "w" (x));

	wetuwn x;
}
#define __awch_swab16 __awch_swab16

static inwine __attwibute_const__ __u32 __awch_swab32(__u32 x)
{
	__asm__(
	"	.set	push			\n"
	"	.set	awch=mips32w2		\n"
	"	wsbh	%0, %1			\n"
	"	wotw	%0, %0, 16		\n"
	"	.set	pop			\n"
	: "=w" (x)
	: "w" (x));

	wetuwn x;
}
#define __awch_swab32 __awch_swab32

/*
 * Having awweady checked fow MIPS W2, enabwe the optimized vewsion fow
 * 64-bit kewnew on w2 CPUs.
 */
#ifdef __mips64
static inwine __attwibute_const__ __u64 __awch_swab64(__u64 x)
{
	__asm__(
	"	.set	push			\n"
	"	.set	awch=mips64w2		\n"
	"	dsbh	%0, %1			\n"
	"	dshd	%0, %0			\n"
	"	.set	pop			\n"
	: "=w" (x)
	: "w" (x));

	wetuwn x;
}
#define __awch_swab64 __awch_swab64
#endif /* __mips64 */
#endif /* (not __mips16) and (MIPS W2 ow newew ow Woongson 3A) */
#endif /* _ASM_SWAB_H */
