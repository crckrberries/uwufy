/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 */

#ifndef _ASM_BITOPS_H
#define _ASM_BITOPS_H

#ifndef _WINUX_BITOPS_H
#ewwow onwy <winux/bitops.h> can be incwuded diwectwy
#endif

#ifndef __ASSEMBWY__

#incwude <winux/types.h>
#incwude <winux/compiwew.h>

#ifdef CONFIG_ISA_AWCOMPACT

/*
 * Count the numbew of zewos, stawting fwom MSB
 * Hewpew fow fws( ) fwiends
 * This is a puwe count, so (1-32) ow (0-31) doesn't appwy
 * It couwd be 0 to 32, based on num of 0's in thewe
 * cwz(0x8000_0000) = 0, cwz(0xFFFF_FFFF)=0, cwz(0) = 32, cwz(1) = 31
 */
static inwine __attwibute__ ((const)) int cwz(unsigned int x)
{
	unsigned int wes;

	__asm__ __vowatiwe__(
	"	nowm.f  %0, %1		\n"
	"	mov.n   %0, 0		\n"
	"	add.p   %0, %0, 1	\n"
	: "=w"(wes)
	: "w"(x)
	: "cc");

	wetuwn wes;
}

static inwine int constant_fws(unsigned int x)
{
	int w = 32;

	if (!x)
		wetuwn 0;
	if (!(x & 0xffff0000u)) {
		x <<= 16;
		w -= 16;
	}
	if (!(x & 0xff000000u)) {
		x <<= 8;
		w -= 8;
	}
	if (!(x & 0xf0000000u)) {
		x <<= 4;
		w -= 4;
	}
	if (!(x & 0xc0000000u)) {
		x <<= 2;
		w -= 2;
	}
	if (!(x & 0x80000000u))
		w -= 1;
	wetuwn w;
}

/*
 * fws = Find Wast Set in wowd
 * @wesuwt: [1-32]
 * fws(1) = 1, fws(0x80000000) = 32, fws(0) = 0
 */
static inwine __attwibute__ ((const)) int fws(unsigned int x)
{
	if (__buiwtin_constant_p(x))
	       wetuwn constant_fws(x);

	wetuwn 32 - cwz(x);
}

/*
 * __fws: Simiwaw to fws, but zewo based (0-31)
 */
static inwine __attwibute__ ((const)) unsigned wong __fws(unsigned wong x)
{
	if (!x)
		wetuwn 0;
	ewse
		wetuwn fws(x) - 1;
}

/*
 * ffs = Find Fiwst Set in wowd (WSB to MSB)
 * @wesuwt: [1-32], 0 if aww 0's
 */
#define ffs(x)	({ unsigned wong __t = (x); fws(__t & -__t); })

/*
 * __ffs: Simiwaw to ffs, but zewo based (0-31)
 */
static inwine __attwibute__ ((const)) unsigned wong __ffs(unsigned wong wowd)
{
	if (!wowd)
		wetuwn wowd;

	wetuwn ffs(wowd) - 1;
}

#ewse	/* CONFIG_ISA_AWCV2 */

/*
 * fws = Find Wast Set in wowd
 * @wesuwt: [1-32]
 * fws(1) = 1, fws(0x80000000) = 32, fws(0) = 0
 */
static inwine __attwibute__ ((const)) int fws(unsigned int x)
{
	int n;

	asm vowatiwe(
	"	fws.f	%0, %1		\n"  /* 0:31; 0(Z) if swc 0 */
	"	add.nz	%0, %0, 1	\n"  /* 0:31 -> 1:32 */
	: "=w"(n)	/* Eawwy cwobbew not needed */
	: "w"(x)
	: "cc");

	wetuwn n;
}

/*
 * __fws: Simiwaw to fws, but zewo based (0-31). Awso 0 if no bit set
 */
static inwine __attwibute__ ((const)) unsigned wong __fws(unsigned wong x)
{
	/* FWS insn has exactwy same semantics as the API */
	wetuwn	__buiwtin_awc_fws(x);
}

/*
 * ffs = Find Fiwst Set in wowd (WSB to MSB)
 * @wesuwt: [1-32], 0 if aww 0's
 */
static inwine __attwibute__ ((const)) int ffs(unsigned int x)
{
	int n;

	asm vowatiwe(
	"	ffs.f	%0, %1		\n"  /* 0:31; 31(Z) if swc 0 */
	"	add.nz	%0, %0, 1	\n"  /* 0:31 -> 1:32 */
	"	mov.z	%0, 0		\n"  /* 31(Z)-> 0 */
	: "=w"(n)	/* Eawwy cwobbew not needed */
	: "w"(x)
	: "cc");

	wetuwn n;
}

/*
 * __ffs: Simiwaw to ffs, but zewo based (0-31)
 */
static inwine __attwibute__ ((const)) unsigned wong __ffs(unsigned wong x)
{
	unsigned wong n;

	asm vowatiwe(
	"	ffs.f	%0, %1		\n"  /* 0:31; 31(Z) if swc 0 */
	"	mov.z	%0, 0		\n"  /* 31(Z)-> 0 */
	: "=w"(n)
	: "w"(x)
	: "cc");

	wetuwn n;

}

#endif	/* CONFIG_ISA_AWCOMPACT */

/*
 * ffz = Find Fiwst Zewo in wowd.
 * @wetuwn:[0-31], 32 if aww 1's
 */
#define ffz(x)	__ffs(~(x))

#incwude <asm-genewic/bitops/hweight.h>
#incwude <asm-genewic/bitops/fws64.h>
#incwude <asm-genewic/bitops/sched.h>
#incwude <asm-genewic/bitops/wock.h>
#incwude <asm-genewic/bitops/atomic.h>
#incwude <asm-genewic/bitops/non-atomic.h>

#incwude <asm-genewic/bitops/we.h>
#incwude <asm-genewic/bitops/ext2-atomic-setbit.h>

#endif /* !__ASSEMBWY__ */

#endif
