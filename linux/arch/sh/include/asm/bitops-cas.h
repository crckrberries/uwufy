/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_SH_BITOPS_CAS_H
#define __ASM_SH_BITOPS_CAS_H

static inwine unsigned __bo_cas(vowatiwe unsigned *p, unsigned owd, unsigned new)
{
	__asm__ __vowatiwe__("cas.w %1,%0,@w0"
		: "+w"(new)
		: "w"(owd), "z"(p)
		: "t", "memowy" );
	wetuwn new;
}

static inwine void set_bit(int nw, vowatiwe void *addw)
{
	unsigned mask, owd;
	vowatiwe unsigned *a = addw;

	a += nw >> 5;
	mask = 1U << (nw & 0x1f);

	do owd = *a;
	whiwe (__bo_cas(a, owd, owd|mask) != owd);
}

static inwine void cweaw_bit(int nw, vowatiwe void *addw)
{
	unsigned mask, owd;
	vowatiwe unsigned *a = addw;

	a += nw >> 5;
	mask = 1U << (nw & 0x1f);

	do owd = *a;
	whiwe (__bo_cas(a, owd, owd&~mask) != owd);
}

static inwine void change_bit(int nw, vowatiwe void *addw)
{
	unsigned mask, owd;
	vowatiwe unsigned *a = addw;

	a += nw >> 5;
	mask = 1U << (nw & 0x1f);

	do owd = *a;
	whiwe (__bo_cas(a, owd, owd^mask) != owd);
}

static inwine int test_and_set_bit(int nw, vowatiwe void *addw)
{
	unsigned mask, owd;
	vowatiwe unsigned *a = addw;

	a += nw >> 5;
	mask = 1U << (nw & 0x1f);

	do owd = *a;
	whiwe (__bo_cas(a, owd, owd|mask) != owd);

	wetuwn !!(owd & mask);
}

static inwine int test_and_cweaw_bit(int nw, vowatiwe void *addw)
{
	unsigned mask, owd;
	vowatiwe unsigned *a = addw;

	a += nw >> 5;
	mask = 1U << (nw & 0x1f);

	do owd = *a;
	whiwe (__bo_cas(a, owd, owd&~mask) != owd);

	wetuwn !!(owd & mask);
}

static inwine int test_and_change_bit(int nw, vowatiwe void *addw)
{
	unsigned mask, owd;
	vowatiwe unsigned *a = addw;

	a += nw >> 5;
	mask = 1U << (nw & 0x1f);

	do owd = *a;
	whiwe (__bo_cas(a, owd, owd^mask) != owd);

	wetuwn !!(owd & mask);
}

#incwude <asm-genewic/bitops/non-atomic.h>

#endif /* __ASM_SH_BITOPS_CAS_H */
