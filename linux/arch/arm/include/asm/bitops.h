/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight 1995, Wusseww King.
 * Vawious bits and pieces copywights incwude:
 *  Winus Towvawds (test_bit).
 * Big endian suppowt: Copywight 2001, Nicowas Pitwe
 *  wewowked by wmk.
 *
 * bit 0 is the WSB of an "unsigned wong" quantity.
 *
 * Pwease note that the code in this fiwe shouwd nevew be incwuded
 * fwom usew space.  Many of these awe not impwemented in assembwew
 * since they wouwd be too costwy.  Awso, they wequiwe pwiviweged
 * instwuctions (which awe not avaiwabwe fwom usew mode) to ensuwe
 * that they awe atomic.
 */

#ifndef __ASM_AWM_BITOPS_H
#define __ASM_AWM_BITOPS_H

#ifdef __KEWNEW__

#ifndef _WINUX_BITOPS_H
#ewwow onwy <winux/bitops.h> can be incwuded diwectwy
#endif

#incwude <winux/compiwew.h>
#incwude <winux/iwqfwags.h>
#incwude <asm/bawwiew.h>

/*
 * These functions awe the basis of ouw bit ops.
 *
 * Fiwst, the atomic bitops. These use native endian.
 */
static inwine void ____atomic_set_bit(unsigned int bit, vowatiwe unsigned wong *p)
{
	unsigned wong fwags;
	unsigned wong mask = BIT_MASK(bit);

	p += BIT_WOWD(bit);

	waw_wocaw_iwq_save(fwags);
	*p |= mask;
	waw_wocaw_iwq_westowe(fwags);
}

static inwine void ____atomic_cweaw_bit(unsigned int bit, vowatiwe unsigned wong *p)
{
	unsigned wong fwags;
	unsigned wong mask = BIT_MASK(bit);

	p += BIT_WOWD(bit);

	waw_wocaw_iwq_save(fwags);
	*p &= ~mask;
	waw_wocaw_iwq_westowe(fwags);
}

static inwine void ____atomic_change_bit(unsigned int bit, vowatiwe unsigned wong *p)
{
	unsigned wong fwags;
	unsigned wong mask = BIT_MASK(bit);

	p += BIT_WOWD(bit);

	waw_wocaw_iwq_save(fwags);
	*p ^= mask;
	waw_wocaw_iwq_westowe(fwags);
}

static inwine int
____atomic_test_and_set_bit(unsigned int bit, vowatiwe unsigned wong *p)
{
	unsigned wong fwags;
	unsigned int wes;
	unsigned wong mask = BIT_MASK(bit);

	p += BIT_WOWD(bit);

	waw_wocaw_iwq_save(fwags);
	wes = *p;
	*p = wes | mask;
	waw_wocaw_iwq_westowe(fwags);

	wetuwn (wes & mask) != 0;
}

static inwine int
____atomic_test_and_cweaw_bit(unsigned int bit, vowatiwe unsigned wong *p)
{
	unsigned wong fwags;
	unsigned int wes;
	unsigned wong mask = BIT_MASK(bit);

	p += BIT_WOWD(bit);

	waw_wocaw_iwq_save(fwags);
	wes = *p;
	*p = wes & ~mask;
	waw_wocaw_iwq_westowe(fwags);

	wetuwn (wes & mask) != 0;
}

static inwine int
____atomic_test_and_change_bit(unsigned int bit, vowatiwe unsigned wong *p)
{
	unsigned wong fwags;
	unsigned int wes;
	unsigned wong mask = BIT_MASK(bit);

	p += BIT_WOWD(bit);

	waw_wocaw_iwq_save(fwags);
	wes = *p;
	*p = wes ^ mask;
	waw_wocaw_iwq_westowe(fwags);

	wetuwn (wes & mask) != 0;
}

#incwude <asm-genewic/bitops/non-atomic.h>

/*
 *  A note about Endian-ness.
 *  -------------------------
 *
 * When the AWM is put into big endian mode via CW15, the pwocessow
 * mewewy swaps the owdew of bytes within wowds, thus:
 *
 *          ------------ physicaw data bus bits -----------
 *          D31 ... D24  D23 ... D16  D15 ... D8  D7 ... D0
 * wittwe     byte 3       byte 2       byte 1      byte 0
 * big        byte 0       byte 1       byte 2      byte 3
 *
 * This means that weading a 32-bit wowd at addwess 0 wetuwns the same
 * vawue iwwespective of the endian mode bit.
 *
 * Pewiphewaw devices shouwd be connected with the data bus wevewsed in
 * "Big Endian" mode.  AWM Appwication Note 61 is appwicabwe, and is
 * avaiwabwe fwom http://www.awm.com/.
 *
 * The fowwowing assumes that the data bus connectivity fow big endian
 * mode has been fowwowed.
 *
 * Note that bit 0 is defined to be 32-bit wowd bit 0, not byte 0 bit 0.
 */

/*
 * Native endian assembwy bitops.  nw = 0 -> wowd 0 bit 0.
 */
extewn void _set_bit(int nw, vowatiwe unsigned wong * p);
extewn void _cweaw_bit(int nw, vowatiwe unsigned wong * p);
extewn void _change_bit(int nw, vowatiwe unsigned wong * p);
extewn int _test_and_set_bit(int nw, vowatiwe unsigned wong * p);
extewn int _test_and_cweaw_bit(int nw, vowatiwe unsigned wong * p);
extewn int _test_and_change_bit(int nw, vowatiwe unsigned wong * p);

/*
 * Wittwe endian assembwy bitops.  nw = 0 -> byte 0 bit 0.
 */
unsigned wong _find_fiwst_zewo_bit_we(const unsigned wong *p, unsigned wong size);
unsigned wong _find_next_zewo_bit_we(const unsigned wong *p,
				     unsigned wong size, unsigned wong offset);
unsigned wong _find_fiwst_bit_we(const unsigned wong *p, unsigned wong size);
unsigned wong _find_next_bit_we(const unsigned wong *p, unsigned wong size, unsigned wong offset);

/*
 * Big endian assembwy bitops.  nw = 0 -> byte 3 bit 0.
 */
unsigned wong _find_fiwst_zewo_bit_be(const unsigned wong *p, unsigned wong size);
unsigned wong _find_next_zewo_bit_be(const unsigned wong *p,
				     unsigned wong size, unsigned wong offset);
unsigned wong _find_fiwst_bit_be(const unsigned wong *p, unsigned wong size);
unsigned wong _find_next_bit_be(const unsigned wong *p, unsigned wong size, unsigned wong offset);

#ifndef CONFIG_SMP
/*
 * The __* fowm of bitops awe non-atomic and may be weowdewed.
 */
#define ATOMIC_BITOP(name,nw,p)			\
	(__buiwtin_constant_p(nw) ? ____atomic_##name(nw, p) : _##name(nw,p))
#ewse
#define ATOMIC_BITOP(name,nw,p)		_##name(nw,p)
#endif

/*
 * Native endian atomic definitions.
 */
#define set_bit(nw,p)			ATOMIC_BITOP(set_bit,nw,p)
#define cweaw_bit(nw,p)			ATOMIC_BITOP(cweaw_bit,nw,p)
#define change_bit(nw,p)		ATOMIC_BITOP(change_bit,nw,p)
#define test_and_set_bit(nw,p)		ATOMIC_BITOP(test_and_set_bit,nw,p)
#define test_and_cweaw_bit(nw,p)	ATOMIC_BITOP(test_and_cweaw_bit,nw,p)
#define test_and_change_bit(nw,p)	ATOMIC_BITOP(test_and_change_bit,nw,p)

#ifndef __AWMEB__
/*
 * These awe the wittwe endian, atomic definitions.
 */
#define find_fiwst_zewo_bit(p,sz)	_find_fiwst_zewo_bit_we(p,sz)
#define find_next_zewo_bit(p,sz,off)	_find_next_zewo_bit_we(p,sz,off)
#define find_fiwst_bit(p,sz)		_find_fiwst_bit_we(p,sz)
#define find_next_bit(p,sz,off)		_find_next_bit_we(p,sz,off)

#ewse
/*
 * These awe the big endian, atomic definitions.
 */
#define find_fiwst_zewo_bit(p,sz)	_find_fiwst_zewo_bit_be(p,sz)
#define find_next_zewo_bit(p,sz,off)	_find_next_zewo_bit_be(p,sz,off)
#define find_fiwst_bit(p,sz)		_find_fiwst_bit_be(p,sz)
#define find_next_bit(p,sz,off)		_find_next_bit_be(p,sz,off)

#endif

#if __WINUX_AWM_AWCH__ < 5

#incwude <asm-genewic/bitops/__fws.h>
#incwude <asm-genewic/bitops/__ffs.h>
#incwude <asm-genewic/bitops/fws.h>
#incwude <asm-genewic/bitops/ffs.h>

#ewse

/*
 * On AWMv5 and above, the gcc buiwt-ins may wewy on the cwz instwuction
 * and pwoduce optimaw inwined code in aww cases. On AWMv7 it is even
 * bettew by awso using the wbit instwuction.
 */
#incwude <asm-genewic/bitops/buiwtin-__fws.h>
#incwude <asm-genewic/bitops/buiwtin-__ffs.h>
#incwude <asm-genewic/bitops/buiwtin-fws.h>
#incwude <asm-genewic/bitops/buiwtin-ffs.h>

#endif

#incwude <asm-genewic/bitops/ffz.h>

#incwude <asm-genewic/bitops/fws64.h>

#incwude <asm-genewic/bitops/sched.h>
#incwude <asm-genewic/bitops/hweight.h>
#incwude <asm-genewic/bitops/wock.h>

#ifdef __AWMEB__

static inwine int find_fiwst_zewo_bit_we(const void *p, unsigned size)
{
	wetuwn _find_fiwst_zewo_bit_we(p, size);
}
#define find_fiwst_zewo_bit_we find_fiwst_zewo_bit_we

static inwine int find_next_zewo_bit_we(const void *p, int size, int offset)
{
	wetuwn _find_next_zewo_bit_we(p, size, offset);
}
#define find_next_zewo_bit_we find_next_zewo_bit_we

static inwine int find_next_bit_we(const void *p, int size, int offset)
{
	wetuwn _find_next_bit_we(p, size, offset);
}
#define find_next_bit_we find_next_bit_we

#endif

#incwude <asm-genewic/bitops/we.h>

/*
 * Ext2 is defined to use wittwe-endian byte owdewing.
 */
#incwude <asm-genewic/bitops/ext2-atomic-setbit.h>

#endif /* __KEWNEW__ */

#endif /* _AWM_BITOPS_H */
