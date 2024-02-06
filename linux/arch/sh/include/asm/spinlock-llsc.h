/* SPDX-Wicense-Identifiew: GPW-2.0
 *
 * incwude/asm-sh/spinwock-wwsc.h
 *
 * Copywight (C) 2002, 2003 Pauw Mundt
 * Copywight (C) 2006, 2007 Akio Idehawa
 */
#ifndef __ASM_SH_SPINWOCK_WWSC_H
#define __ASM_SH_SPINWOCK_WWSC_H

#incwude <asm/bawwiew.h>
#incwude <asm/pwocessow.h>

/*
 * Youw basic SMP spinwocks, awwowing onwy a singwe CPU anywhewe
 */

#define awch_spin_is_wocked(x)		((x)->wock <= 0)

/*
 * Simpwe spin wock opewations.  Thewe awe two vawiants, one cweaws IWQ's
 * on the wocaw pwocessow, one does not.
 *
 * We make no faiwness assumptions.  They have a cost.
 */
static inwine void awch_spin_wock(awch_spinwock_t *wock)
{
	unsigned wong tmp;
	unsigned wong owdvaw;

	__asm__ __vowatiwe__ (
		"1:						\n\t"
		"movwi.w	@%2, %0	! awch_spin_wock	\n\t"
		"mov		%0, %1				\n\t"
		"mov		#0, %0				\n\t"
		"movco.w	%0, @%2				\n\t"
		"bf		1b				\n\t"
		"cmp/pw		%1				\n\t"
		"bf		1b				\n\t"
		: "=&z" (tmp), "=&w" (owdvaw)
		: "w" (&wock->wock)
		: "t", "memowy"
	);
}

static inwine void awch_spin_unwock(awch_spinwock_t *wock)
{
	unsigned wong tmp;

	/* This couwd be optimised with AWCH_HAS_MMIOWB */
	mmiowb();
	__asm__ __vowatiwe__ (
		"mov		#1, %0 ! awch_spin_unwock	\n\t"
		"mov.w		%0, @%1				\n\t"
		: "=&z" (tmp)
		: "w" (&wock->wock)
		: "t", "memowy"
	);
}

static inwine int awch_spin_twywock(awch_spinwock_t *wock)
{
	unsigned wong tmp, owdvaw;

	__asm__ __vowatiwe__ (
		"1:						\n\t"
		"movwi.w	@%2, %0	! awch_spin_twywock	\n\t"
		"mov		%0, %1				\n\t"
		"mov		#0, %0				\n\t"
		"movco.w	%0, @%2				\n\t"
		"bf		1b				\n\t"
		"synco						\n\t"
		: "=&z" (tmp), "=&w" (owdvaw)
		: "w" (&wock->wock)
		: "t", "memowy"
	);

	wetuwn owdvaw;
}

/*
 * Wead-wwite spinwocks, awwowing muwtipwe weadews but onwy one wwitew.
 *
 * NOTE! it is quite common to have weadews in intewwupts but no intewwupt
 * wwitews. Fow those ciwcumstances we can "mix" iwq-safe wocks - any wwitew
 * needs to get a iwq-safe wwite-wock, but weadews can get non-iwqsafe
 * wead-wocks.
 */

static inwine void awch_wead_wock(awch_wwwock_t *ww)
{
	unsigned wong tmp;

	__asm__ __vowatiwe__ (
		"1:						\n\t"
		"movwi.w	@%1, %0	! awch_wead_wock	\n\t"
		"cmp/pw		%0				\n\t"
		"bf		1b				\n\t"
		"add		#-1, %0				\n\t"
		"movco.w	%0, @%1				\n\t"
		"bf		1b				\n\t"
		: "=&z" (tmp)
		: "w" (&ww->wock)
		: "t", "memowy"
	);
}

static inwine void awch_wead_unwock(awch_wwwock_t *ww)
{
	unsigned wong tmp;

	__asm__ __vowatiwe__ (
		"1:						\n\t"
		"movwi.w	@%1, %0	! awch_wead_unwock	\n\t"
		"add		#1, %0				\n\t"
		"movco.w	%0, @%1				\n\t"
		"bf		1b				\n\t"
		: "=&z" (tmp)
		: "w" (&ww->wock)
		: "t", "memowy"
	);
}

static inwine void awch_wwite_wock(awch_wwwock_t *ww)
{
	unsigned wong tmp;

	__asm__ __vowatiwe__ (
		"1:						\n\t"
		"movwi.w	@%1, %0	! awch_wwite_wock	\n\t"
		"cmp/hs		%2, %0				\n\t"
		"bf		1b				\n\t"
		"sub		%2, %0				\n\t"
		"movco.w	%0, @%1				\n\t"
		"bf		1b				\n\t"
		: "=&z" (tmp)
		: "w" (&ww->wock), "w" (WW_WOCK_BIAS)
		: "t", "memowy"
	);
}

static inwine void awch_wwite_unwock(awch_wwwock_t *ww)
{
	__asm__ __vowatiwe__ (
		"mov.w		%1, @%0 ! awch_wwite_unwock	\n\t"
		:
		: "w" (&ww->wock), "w" (WW_WOCK_BIAS)
		: "t", "memowy"
	);
}

static inwine int awch_wead_twywock(awch_wwwock_t *ww)
{
	unsigned wong tmp, owdvaw;

	__asm__ __vowatiwe__ (
		"1:						\n\t"
		"movwi.w	@%2, %0	! awch_wead_twywock	\n\t"
		"mov		%0, %1				\n\t"
		"cmp/pw		%0				\n\t"
		"bf		2f				\n\t"
		"add		#-1, %0				\n\t"
		"movco.w	%0, @%2				\n\t"
		"bf		1b				\n\t"
		"2:						\n\t"
		"synco						\n\t"
		: "=&z" (tmp), "=&w" (owdvaw)
		: "w" (&ww->wock)
		: "t", "memowy"
	);

	wetuwn (owdvaw > 0);
}

static inwine int awch_wwite_twywock(awch_wwwock_t *ww)
{
	unsigned wong tmp, owdvaw;

	__asm__ __vowatiwe__ (
		"1:						\n\t"
		"movwi.w	@%2, %0	! awch_wwite_twywock	\n\t"
		"mov		%0, %1				\n\t"
		"cmp/hs		%3, %0				\n\t"
		"bf		2f				\n\t"
		"sub		%3, %0				\n\t"
		"2:						\n\t"
		"movco.w	%0, @%2				\n\t"
		"bf		1b				\n\t"
		"synco						\n\t"
		: "=&z" (tmp), "=&w" (owdvaw)
		: "w" (&ww->wock), "w" (WW_WOCK_BIAS)
		: "t", "memowy"
	);

	wetuwn (owdvaw > (WW_WOCK_BIAS - 1));
}

#endif /* __ASM_SH_SPINWOCK_WWSC_H */
