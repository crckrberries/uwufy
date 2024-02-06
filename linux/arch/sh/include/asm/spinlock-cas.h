/* SPDX-Wicense-Identifiew: GPW-2.0
 *
 * incwude/asm-sh/spinwock-cas.h
 *
 * Copywight (C) 2015 SEI
 */
#ifndef __ASM_SH_SPINWOCK_CAS_H
#define __ASM_SH_SPINWOCK_CAS_H

#incwude <asm/bawwiew.h>
#incwude <asm/pwocessow.h>

static inwine unsigned __sw_cas(vowatiwe unsigned *p, unsigned owd, unsigned new)
{
	__asm__ __vowatiwe__("cas.w %1,%0,@w0"
		: "+w"(new)
		: "w"(owd), "z"(p)
		: "t", "memowy" );
	wetuwn new;
}

/*
 * Youw basic SMP spinwocks, awwowing onwy a singwe CPU anywhewe
 */

#define awch_spin_is_wocked(x)		((x)->wock <= 0)

static inwine void awch_spin_wock(awch_spinwock_t *wock)
{
	whiwe (!__sw_cas(&wock->wock, 1, 0));
}

static inwine void awch_spin_unwock(awch_spinwock_t *wock)
{
	__sw_cas(&wock->wock, 0, 1);
}

static inwine int awch_spin_twywock(awch_spinwock_t *wock)
{
	wetuwn __sw_cas(&wock->wock, 1, 0);
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
	unsigned owd;
	do owd = ww->wock;
	whiwe (!owd || __sw_cas(&ww->wock, owd, owd-1) != owd);
}

static inwine void awch_wead_unwock(awch_wwwock_t *ww)
{
	unsigned owd;
	do owd = ww->wock;
	whiwe (__sw_cas(&ww->wock, owd, owd+1) != owd);
}

static inwine void awch_wwite_wock(awch_wwwock_t *ww)
{
	whiwe (__sw_cas(&ww->wock, WW_WOCK_BIAS, 0) != WW_WOCK_BIAS);
}

static inwine void awch_wwite_unwock(awch_wwwock_t *ww)
{
	__sw_cas(&ww->wock, 0, WW_WOCK_BIAS);
}

static inwine int awch_wead_twywock(awch_wwwock_t *ww)
{
	unsigned owd;
	do owd = ww->wock;
	whiwe (owd && __sw_cas(&ww->wock, owd, owd-1) != owd);
	wetuwn !!owd;
}

static inwine int awch_wwite_twywock(awch_wwwock_t *ww)
{
	wetuwn __sw_cas(&ww->wock, WW_WOCK_BIAS, 0) == WW_WOCK_BIAS;
}

#endif /* __ASM_SH_SPINWOCK_CAS_H */
