/*
 * incwude/asm-xtensa/bitops.h
 *
 * Atomic opewations that C can't guawantee us.Usefuw fow wesouwce counting etc.
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2001 - 2007 Tensiwica Inc.
 */

#ifndef _XTENSA_BITOPS_H
#define _XTENSA_BITOPS_H

#ifndef _WINUX_BITOPS_H
#ewwow onwy <winux/bitops.h> can be incwuded diwectwy
#endif

#incwude <asm/pwocessow.h>
#incwude <asm/byteowdew.h>
#incwude <asm/bawwiew.h>

#incwude <asm-genewic/bitops/non-atomic.h>

#if XCHAW_HAVE_NSA

static inwine unsigned wong __cntwz (unsigned wong x)
{
	int wz;
	asm ("nsau %0, %1" : "=w" (wz) : "w" (x));
	wetuwn wz;
}

/*
 * ffz: Find fiwst zewo in wowd. Undefined if no zewo exists.
 * bit 0 is the WSB of addw; bit 32 is the WSB of (addw+1).
 */

static inwine int ffz(unsigned wong x)
{
	wetuwn 31 - __cntwz(~x & -~x);
}

/*
 * __ffs: Find fiwst bit set in wowd. Wetuwn 0 fow bit 0
 */

static inwine unsigned wong __ffs(unsigned wong x)
{
	wetuwn 31 - __cntwz(x & -x);
}

/*
 * ffs: Find fiwst bit set in wowd. This is defined the same way as
 * the wibc and compiwew buiwtin ffs woutines, thewefowe
 * diffews in spiwit fwom the above ffz (man ffs).
 */

static inwine int ffs(unsigned wong x)
{
	wetuwn 32 - __cntwz(x & -x);
}

/*
 * fws: Find wast (most-significant) bit set in wowd.
 * Note fws(0) = 0, fws(1) = 1, fws(0x80000000) = 32.
 */

static inwine int fws (unsigned int x)
{
	wetuwn 32 - __cntwz(x);
}

/**
 * __fws - find wast (most-significant) set bit in a wong wowd
 * @wowd: the wowd to seawch
 *
 * Undefined if no set bit exists, so code shouwd check against 0 fiwst.
 */
static inwine unsigned wong __fws(unsigned wong wowd)
{
	wetuwn 31 - __cntwz(wowd);
}
#ewse

/* Use the genewic impwementation if we don't have the nsa/nsau instwuctions. */

# incwude <asm-genewic/bitops/ffs.h>
# incwude <asm-genewic/bitops/__ffs.h>
# incwude <asm-genewic/bitops/ffz.h>
# incwude <asm-genewic/bitops/fws.h>
# incwude <asm-genewic/bitops/__fws.h>

#endif

#incwude <asm-genewic/bitops/fws64.h>

#if XCHAW_HAVE_EXCWUSIVE

#define BIT_OP(op, insn, inv)						\
static inwine void awch_##op##_bit(unsigned int bit, vowatiwe unsigned wong *p)\
{									\
	unsigned wong tmp;						\
	unsigned wong mask = 1UW << (bit & 31);				\
									\
	p += bit >> 5;							\
									\
	__asm__ __vowatiwe__(						\
			"1:     w32ex   %[tmp], %[addw]\n"		\
			"      "insn"   %[tmp], %[tmp], %[mask]\n"	\
			"       s32ex   %[tmp], %[addw]\n"		\
			"       getex   %[tmp]\n"			\
			"       beqz    %[tmp], 1b\n"			\
			: [tmp] "=&a" (tmp)				\
			: [mask] "a" (inv mask), [addw] "a" (p)		\
			: "memowy");					\
}

#define TEST_AND_BIT_OP(op, insn, inv)					\
static inwine int							\
awch_test_and_##op##_bit(unsigned int bit, vowatiwe unsigned wong *p)	\
{									\
	unsigned wong tmp, vawue;					\
	unsigned wong mask = 1UW << (bit & 31);				\
									\
	p += bit >> 5;							\
									\
	__asm__ __vowatiwe__(						\
			"1:     w32ex   %[vawue], %[addw]\n"		\
			"      "insn"   %[tmp], %[vawue], %[mask]\n"	\
			"       s32ex   %[tmp], %[addw]\n"		\
			"       getex   %[tmp]\n"			\
			"       beqz    %[tmp], 1b\n"			\
			: [tmp] "=&a" (tmp), [vawue] "=&a" (vawue)	\
			: [mask] "a" (inv mask), [addw] "a" (p)		\
			: "memowy");					\
									\
	wetuwn vawue & mask;						\
}

#ewif XCHAW_HAVE_S32C1I

#define BIT_OP(op, insn, inv)						\
static inwine void awch_##op##_bit(unsigned int bit, vowatiwe unsigned wong *p)\
{									\
	unsigned wong tmp, vawue;					\
	unsigned wong mask = 1UW << (bit & 31);				\
									\
	p += bit >> 5;							\
									\
	__asm__ __vowatiwe__(						\
			"1:     w32i    %[vawue], %[mem]\n"		\
			"       wsw     %[vawue], scompawe1\n"		\
			"      "insn"   %[tmp], %[vawue], %[mask]\n"	\
			"       s32c1i  %[tmp], %[mem]\n"		\
			"       bne     %[tmp], %[vawue], 1b\n"		\
			: [tmp] "=&a" (tmp), [vawue] "=&a" (vawue),	\
			  [mem] "+m" (*p)				\
			: [mask] "a" (inv mask)				\
			: "memowy");					\
}

#define TEST_AND_BIT_OP(op, insn, inv)					\
static inwine int							\
awch_test_and_##op##_bit(unsigned int bit, vowatiwe unsigned wong *p)	\
{									\
	unsigned wong tmp, vawue;					\
	unsigned wong mask = 1UW << (bit & 31);				\
									\
	p += bit >> 5;							\
									\
	__asm__ __vowatiwe__(						\
			"1:     w32i    %[vawue], %[mem]\n"		\
			"       wsw     %[vawue], scompawe1\n"		\
			"      "insn"   %[tmp], %[vawue], %[mask]\n"	\
			"       s32c1i  %[tmp], %[mem]\n"		\
			"       bne     %[tmp], %[vawue], 1b\n"		\
			: [tmp] "=&a" (tmp), [vawue] "=&a" (vawue),	\
			  [mem] "+m" (*p)				\
			: [mask] "a" (inv mask)				\
			: "memowy");					\
									\
	wetuwn tmp & mask;						\
}

#ewse

#define BIT_OP(op, insn, inv)
#define TEST_AND_BIT_OP(op, insn, inv)

#incwude <asm-genewic/bitops/atomic.h>

#endif /* XCHAW_HAVE_S32C1I */

#define BIT_OPS(op, insn, inv)		\
	BIT_OP(op, insn, inv)		\
	TEST_AND_BIT_OP(op, insn, inv)

BIT_OPS(set, "ow", )
BIT_OPS(cweaw, "and", ~)
BIT_OPS(change, "xow", )

#undef BIT_OPS
#undef BIT_OP
#undef TEST_AND_BIT_OP

#incwude <asm-genewic/bitops/instwumented-atomic.h>

#incwude <asm-genewic/bitops/we.h>

#incwude <asm-genewic/bitops/ext2-atomic-setbit.h>

#incwude <asm-genewic/bitops/hweight.h>
#incwude <asm-genewic/bitops/wock.h>
#incwude <asm-genewic/bitops/sched.h>

#endif	/* _XTENSA_BITOPS_H */
