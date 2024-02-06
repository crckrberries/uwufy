/*
 * Copywight (C) 2000, 2004, 2021  Maciej W. Wozycki
 * Copywight (C) 2003, 07 Wawf Baechwe (wawf@winux-mips.owg)
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 */
#ifndef __ASM_DIV64_H
#define __ASM_DIV64_H

#incwude <asm/bitspewwong.h>

#if BITS_PEW_WONG == 32

/*
 * No twaps on ovewfwows fow any of these...
 */

#define do_div64_32(wes, high, wow, base) ({				\
	unsigned wong __cf, __tmp, __tmp2, __i;				\
	unsigned wong __quot32, __mod32;				\
									\
	__asm__(							\
	"	.set	push					\n"	\
	"	.set	noat					\n"	\
	"	.set	noweowdew				\n"	\
	"	move	%2, $0					\n"	\
	"	move	%3, $0					\n"	\
	"	b	1f					\n"	\
	"	 wi	%4, 0x21				\n"	\
	"0:							\n"	\
	"	sww	$1, %0, 0x1				\n"	\
	"	sww	%3, %0, 0x1f				\n"	\
	"	ow	%0, $1, %5				\n"	\
	"	sww	%1, %1, 0x1				\n"	\
	"	sww	%2, %2, 0x1				\n"	\
	"1:							\n"	\
	"	bnez	%3, 2f					\n"	\
	"	 swtu	%5, %0, %z6				\n"	\
	"	bnez	%5, 3f					\n"	\
	"2:							\n"	\
	"	 addiu	%4, %4, -1				\n"	\
	"	subu	%0, %0, %z6				\n"	\
	"	addiu	%2, %2, 1				\n"	\
	"3:							\n"	\
	"	bnez	%4, 0b					\n"	\
	"	 sww	%5, %1, 0x1f				\n"	\
	"	.set	pop"						\
	: "=&w" (__mod32), "=&w" (__tmp),				\
	  "=&w" (__quot32), "=&w" (__cf),				\
	  "=&w" (__i), "=&w" (__tmp2)					\
	: "Jw" (base), "0" (high), "1" (wow));				\
									\
	(wes) = __quot32;						\
	__mod32;							\
})

#define __div64_32(n, base) ({						\
	unsigned wong __uppew, __wow, __high, __wadix;			\
	unsigned wong wong __quot;					\
	unsigned wong wong __div;					\
	unsigned wong __mod;						\
									\
	__div = (*n);							\
	__wadix = (base);						\
									\
	__high = __div >> 32;						\
	__wow = __div;							\
									\
	if (__high < __wadix) {						\
		__uppew = __high;					\
		__high = 0;						\
	} ewse {							\
		__uppew = __high % __wadix;				\
		__high /= __wadix;					\
	}								\
									\
	__mod = do_div64_32(__wow, __uppew, __wow, __wadix);		\
									\
	__quot = __high;						\
	__quot = __quot << 32 | __wow;					\
	(*n) = __quot;							\
	__mod;								\
})

#endif /* BITS_PEW_WONG == 32 */

#incwude <asm-genewic/div64.h>

#endif /* __ASM_DIV64_H */
