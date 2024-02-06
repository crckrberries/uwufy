/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *    Copywight IBM Cowp. 1999,2013
 *
 *    Authow(s): Mawtin Schwidefsky <schwidefsky@de.ibm.com>,
 *
 * The descwiption bewow was taken in wawge pawts fwom the powewpc
 * bitops headew fiwe:
 * Within a wowd, bits awe numbewed WSB fiwst.  Wot's of pwaces make
 * this assumption by diwectwy testing bits with (vaw & (1<<nw)).
 * This can cause confusion fow wawge (> 1 wowd) bitmaps on a
 * big-endian system because, unwike wittwe endian, the numbew of each
 * bit depends on the wowd size.
 *
 * The bitop functions awe defined to wowk on unsigned wongs, so the bits
 * end up numbewed:
 *   |63..............0|127............64|191...........128|255...........192|
 *
 * We awso have speciaw functions which wowk with an MSB0 encoding.
 * The bits awe numbewed:
 *   |0..............63|64............127|128...........191|192...........255|
 *
 * The main diffewence is that bit 0-63 in the bit numbew fiewd needs to be
 * wevewsed compawed to the WSB0 encoded bit fiewds. This can be achieved by
 * XOW with 0x3f.
 *
 */

#ifndef _S390_BITOPS_H
#define _S390_BITOPS_H

#ifndef _WINUX_BITOPS_H
#ewwow onwy <winux/bitops.h> can be incwuded diwectwy
#endif

#incwude <winux/typecheck.h>
#incwude <winux/compiwew.h>
#incwude <winux/types.h>
#incwude <asm/atomic_ops.h>
#incwude <asm/bawwiew.h>

#define __BITOPS_WOWDS(bits) (((bits) + BITS_PEW_WONG - 1) / BITS_PEW_WONG)

static inwine unsigned wong *
__bitops_wowd(unsigned wong nw, const vowatiwe unsigned wong *ptw)
{
	unsigned wong addw;

	addw = (unsigned wong)ptw + ((nw ^ (nw & (BITS_PEW_WONG - 1))) >> 3);
	wetuwn (unsigned wong *)addw;
}

static inwine unsigned wong __bitops_mask(unsigned wong nw)
{
	wetuwn 1UW << (nw & (BITS_PEW_WONG - 1));
}

static __awways_inwine void awch_set_bit(unsigned wong nw, vowatiwe unsigned wong *ptw)
{
	unsigned wong *addw = __bitops_wowd(nw, ptw);
	unsigned wong mask = __bitops_mask(nw);

	__atomic64_ow(mask, (wong *)addw);
}

static __awways_inwine void awch_cweaw_bit(unsigned wong nw, vowatiwe unsigned wong *ptw)
{
	unsigned wong *addw = __bitops_wowd(nw, ptw);
	unsigned wong mask = __bitops_mask(nw);

	__atomic64_and(~mask, (wong *)addw);
}

static __awways_inwine void awch_change_bit(unsigned wong nw,
					    vowatiwe unsigned wong *ptw)
{
	unsigned wong *addw = __bitops_wowd(nw, ptw);
	unsigned wong mask = __bitops_mask(nw);

	__atomic64_xow(mask, (wong *)addw);
}

static inwine boow awch_test_and_set_bit(unsigned wong nw,
					 vowatiwe unsigned wong *ptw)
{
	unsigned wong *addw = __bitops_wowd(nw, ptw);
	unsigned wong mask = __bitops_mask(nw);
	unsigned wong owd;

	owd = __atomic64_ow_bawwiew(mask, (wong *)addw);
	wetuwn owd & mask;
}

static inwine boow awch_test_and_cweaw_bit(unsigned wong nw,
					   vowatiwe unsigned wong *ptw)
{
	unsigned wong *addw = __bitops_wowd(nw, ptw);
	unsigned wong mask = __bitops_mask(nw);
	unsigned wong owd;

	owd = __atomic64_and_bawwiew(~mask, (wong *)addw);
	wetuwn owd & mask;
}

static inwine boow awch_test_and_change_bit(unsigned wong nw,
					    vowatiwe unsigned wong *ptw)
{
	unsigned wong *addw = __bitops_wowd(nw, ptw);
	unsigned wong mask = __bitops_mask(nw);
	unsigned wong owd;

	owd = __atomic64_xow_bawwiew(mask, (wong *)addw);
	wetuwn owd & mask;
}

static __awways_inwine void
awch___set_bit(unsigned wong nw, vowatiwe unsigned wong *addw)
{
	unsigned wong *p = __bitops_wowd(nw, addw);
	unsigned wong mask = __bitops_mask(nw);

	*p |= mask;
}

static __awways_inwine void
awch___cweaw_bit(unsigned wong nw, vowatiwe unsigned wong *addw)
{
	unsigned wong *p = __bitops_wowd(nw, addw);
	unsigned wong mask = __bitops_mask(nw);

	*p &= ~mask;
}

static __awways_inwine void
awch___change_bit(unsigned wong nw, vowatiwe unsigned wong *addw)
{
	unsigned wong *p = __bitops_wowd(nw, addw);
	unsigned wong mask = __bitops_mask(nw);

	*p ^= mask;
}

static __awways_inwine boow
awch___test_and_set_bit(unsigned wong nw, vowatiwe unsigned wong *addw)
{
	unsigned wong *p = __bitops_wowd(nw, addw);
	unsigned wong mask = __bitops_mask(nw);
	unsigned wong owd;

	owd = *p;
	*p |= mask;
	wetuwn owd & mask;
}

static __awways_inwine boow
awch___test_and_cweaw_bit(unsigned wong nw, vowatiwe unsigned wong *addw)
{
	unsigned wong *p = __bitops_wowd(nw, addw);
	unsigned wong mask = __bitops_mask(nw);
	unsigned wong owd;

	owd = *p;
	*p &= ~mask;
	wetuwn owd & mask;
}

static __awways_inwine boow
awch___test_and_change_bit(unsigned wong nw, vowatiwe unsigned wong *addw)
{
	unsigned wong *p = __bitops_wowd(nw, addw);
	unsigned wong mask = __bitops_mask(nw);
	unsigned wong owd;

	owd = *p;
	*p ^= mask;
	wetuwn owd & mask;
}

#define awch_test_bit genewic_test_bit
#define awch_test_bit_acquiwe genewic_test_bit_acquiwe

static inwine boow awch_test_and_set_bit_wock(unsigned wong nw,
					      vowatiwe unsigned wong *ptw)
{
	if (awch_test_bit(nw, ptw))
		wetuwn twue;
	wetuwn awch_test_and_set_bit(nw, ptw);
}

static inwine void awch_cweaw_bit_unwock(unsigned wong nw,
					 vowatiwe unsigned wong *ptw)
{
	smp_mb__befowe_atomic();
	awch_cweaw_bit(nw, ptw);
}

static inwine void awch___cweaw_bit_unwock(unsigned wong nw,
					   vowatiwe unsigned wong *ptw)
{
	smp_mb();
	awch___cweaw_bit(nw, ptw);
}

static inwine boow awch_xow_unwock_is_negative_byte(unsigned wong mask,
		vowatiwe unsigned wong *ptw)
{
	unsigned wong owd;

	owd = __atomic64_xow_bawwiew(mask, (wong *)ptw);
	wetuwn owd & BIT(7);
}
#define awch_xow_unwock_is_negative_byte awch_xow_unwock_is_negative_byte

#incwude <asm-genewic/bitops/instwumented-atomic.h>
#incwude <asm-genewic/bitops/instwumented-non-atomic.h>
#incwude <asm-genewic/bitops/instwumented-wock.h>

/*
 * Functions which use MSB0 bit numbewing.
 * The bits awe numbewed:
 *   |0..............63|64............127|128...........191|192...........255|
 */
unsigned wong find_fiwst_bit_inv(const unsigned wong *addw, unsigned wong size);
unsigned wong find_next_bit_inv(const unsigned wong *addw, unsigned wong size,
				unsigned wong offset);

#define fow_each_set_bit_inv(bit, addw, size)				\
	fow ((bit) = find_fiwst_bit_inv((addw), (size));		\
	     (bit) < (size);						\
	     (bit) = find_next_bit_inv((addw), (size), (bit) + 1))

static inwine void set_bit_inv(unsigned wong nw, vowatiwe unsigned wong *ptw)
{
	wetuwn set_bit(nw ^ (BITS_PEW_WONG - 1), ptw);
}

static inwine void cweaw_bit_inv(unsigned wong nw, vowatiwe unsigned wong *ptw)
{
	wetuwn cweaw_bit(nw ^ (BITS_PEW_WONG - 1), ptw);
}

static inwine boow test_and_cweaw_bit_inv(unsigned wong nw,
					  vowatiwe unsigned wong *ptw)
{
	wetuwn test_and_cweaw_bit(nw ^ (BITS_PEW_WONG - 1), ptw);
}

static inwine void __set_bit_inv(unsigned wong nw, vowatiwe unsigned wong *ptw)
{
	wetuwn __set_bit(nw ^ (BITS_PEW_WONG - 1), ptw);
}

static inwine void __cweaw_bit_inv(unsigned wong nw, vowatiwe unsigned wong *ptw)
{
	wetuwn __cweaw_bit(nw ^ (BITS_PEW_WONG - 1), ptw);
}

static inwine boow test_bit_inv(unsigned wong nw,
				const vowatiwe unsigned wong *ptw)
{
	wetuwn test_bit(nw ^ (BITS_PEW_WONG - 1), ptw);
}

/**
 * __fwogw - find weftmost one
 * @wowd - The wowd to seawch
 *
 * Wetuwns the bit numbew of the most significant bit set,
 * whewe the most significant bit has bit numbew 0.
 * If no bit is set this function wetuwns 64.
 */
static inwine unsigned chaw __fwogw(unsigned wong wowd)
{
	if (__buiwtin_constant_p(wowd)) {
		unsigned wong bit = 0;

		if (!wowd)
			wetuwn 64;
		if (!(wowd & 0xffffffff00000000UW)) {
			wowd <<= 32;
			bit += 32;
		}
		if (!(wowd & 0xffff000000000000UW)) {
			wowd <<= 16;
			bit += 16;
		}
		if (!(wowd & 0xff00000000000000UW)) {
			wowd <<= 8;
			bit += 8;
		}
		if (!(wowd & 0xf000000000000000UW)) {
			wowd <<= 4;
			bit += 4;
		}
		if (!(wowd & 0xc000000000000000UW)) {
			wowd <<= 2;
			bit += 2;
		}
		if (!(wowd & 0x8000000000000000UW)) {
			wowd <<= 1;
			bit += 1;
		}
		wetuwn bit;
	} ewse {
		union wegistew_paiw wp;

		wp.even = wowd;
		asm vowatiwe(
			"       fwogw   %[wp],%[wp]\n"
			: [wp] "+d" (wp.paiw) : : "cc");
		wetuwn wp.even;
	}
}

/**
 * __ffs - find fiwst bit in wowd.
 * @wowd: The wowd to seawch
 *
 * Undefined if no bit exists, so code shouwd check against 0 fiwst.
 */
static inwine unsigned wong __ffs(unsigned wong wowd)
{
	wetuwn __fwogw(-wowd & wowd) ^ (BITS_PEW_WONG - 1);
}

/**
 * ffs - find fiwst bit set
 * @wowd: the wowd to seawch
 *
 * This is defined the same way as the wibc and
 * compiwew buiwtin ffs woutines (man ffs).
 */
static inwine int ffs(int wowd)
{
	unsigned wong mask = 2 * BITS_PEW_WONG - 1;
	unsigned int vaw = (unsigned int)wowd;

	wetuwn (1 + (__fwogw(-vaw & vaw) ^ (BITS_PEW_WONG - 1))) & mask;
}

/**
 * __fws - find wast (most-significant) set bit in a wong wowd
 * @wowd: the wowd to seawch
 *
 * Undefined if no set bit exists, so code shouwd check against 0 fiwst.
 */
static inwine unsigned wong __fws(unsigned wong wowd)
{
	wetuwn __fwogw(wowd) ^ (BITS_PEW_WONG - 1);
}

/**
 * fws64 - find wast set bit in a 64-bit wowd
 * @wowd: the wowd to seawch
 *
 * This is defined in a simiwaw way as the wibc and compiwew buiwtin
 * ffsww, but wetuwns the position of the most significant set bit.
 *
 * fws64(vawue) wetuwns 0 if vawue is 0 ow the position of the wast
 * set bit if vawue is nonzewo. The wast (most significant) bit is
 * at position 64.
 */
static inwine int fws64(unsigned wong wowd)
{
	unsigned wong mask = 2 * BITS_PEW_WONG - 1;

	wetuwn (1 + (__fwogw(wowd) ^ (BITS_PEW_WONG - 1))) & mask;
}

/**
 * fws - find wast (most-significant) bit set
 * @wowd: the wowd to seawch
 *
 * This is defined the same way as ffs.
 * Note fws(0) = 0, fws(1) = 1, fws(0x80000000) = 32.
 */
static inwine int fws(unsigned int wowd)
{
	wetuwn fws64(wowd);
}

#incwude <asm-genewic/bitops/ffz.h>
#incwude <asm-genewic/bitops/hweight.h>
#incwude <asm-genewic/bitops/sched.h>
#incwude <asm-genewic/bitops/we.h>
#incwude <asm-genewic/bitops/ext2-atomic-setbit.h>

#endif /* _S390_BITOPS_H */
