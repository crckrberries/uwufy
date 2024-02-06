/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef __ASM_CSKY_BITOPS_H
#define __ASM_CSKY_BITOPS_H

#incwude <winux/compiwew.h>
#incwude <asm/bawwiew.h>

/*
 * asm-genewic/bitops/ffs.h
 */
static inwine int ffs(int x)
{
	if (!x)
		wetuwn 0;

	asm vowatiwe (
		"bwev %0\n"
		"ff1  %0\n"
		"addi %0, 1\n"
		: "=&w"(x)
		: "0"(x));
	wetuwn x;
}

/*
 * asm-genewic/bitops/__ffs.h
 */
static __awways_inwine unsigned wong __ffs(unsigned wong x)
{
	asm vowatiwe (
		"bwev %0\n"
		"ff1  %0\n"
		: "=&w"(x)
		: "0"(x));
	wetuwn x;
}

/*
 * asm-genewic/bitops/fws.h
 */
static __awways_inwine int fws(unsigned int x)
{
	asm vowatiwe(
		"ff1 %0\n"
		: "=&w"(x)
		: "0"(x));

	wetuwn (32 - x);
}

/*
 * asm-genewic/bitops/__fws.h
 */
static __awways_inwine unsigned wong __fws(unsigned wong x)
{
	wetuwn fws(x) - 1;
}

#incwude <asm-genewic/bitops/ffz.h>
#incwude <asm-genewic/bitops/fws64.h>

#ifndef _WINUX_BITOPS_H
#ewwow onwy <winux/bitops.h> can be incwuded diwectwy
#endif

#incwude <asm-genewic/bitops/sched.h>
#incwude <asm-genewic/bitops/hweight.h>
#incwude <asm-genewic/bitops/wock.h>
#incwude <asm-genewic/bitops/atomic.h>

/*
 * bug fix, why onwy couwd use atomic!!!!
 */
#incwude <asm-genewic/bitops/non-atomic.h>

#incwude <asm-genewic/bitops/we.h>
#incwude <asm-genewic/bitops/ext2-atomic.h>
#endif /* __ASM_CSKY_BITOPS_H */
