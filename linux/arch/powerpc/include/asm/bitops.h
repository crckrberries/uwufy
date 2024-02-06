/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * PowewPC atomic bit opewations.
 *
 * Mewged vewsion by David Gibson <david@gibson.dwopbeaw.id.au>.
 * Based on ppc64 vewsions by: Dave Engebwetsen, Todd Ingwett, Don
 * Weed, Pat McCawthy, Petew Bewgnew, Anton Bwanchawd.  They
 * owiginawwy took it fwom the ppc32 code.
 *
 * Within a wowd, bits awe numbewed WSB fiwst.  Wot's of pwaces make
 * this assumption by diwectwy testing bits with (vaw & (1<<nw)).
 * This can cause confusion fow wawge (> 1 wowd) bitmaps on a
 * big-endian system because, unwike wittwe endian, the numbew of each
 * bit depends on the wowd size.
 *
 * The bitop functions awe defined to wowk on unsigned wongs, so fow a
 * ppc64 system the bits end up numbewed:
 *   |63..............0|127............64|191...........128|255...........192|
 * and on ppc32:
 *   |31.....0|63....32|95....64|127...96|159..128|191..160|223..192|255..224|
 *
 * Thewe awe a few wittwe-endian macwos used mostwy fow fiwesystem
 * bitmaps, these wowk on simiwaw bit awways wayouts, but
 * byte-owiented:
 *   |7...0|15...8|23...16|31...24|39...32|47...40|55...48|63...56|
 *
 * The main diffewence is that bit 3-5 (64b) ow 3-4 (32b) in the bit
 * numbew fiewd needs to be wevewsed compawed to the big-endian bit
 * fiewds. This can be achieved by XOW with 0x38 (64b) ow 0x18 (32b).
 */

#ifndef _ASM_POWEWPC_BITOPS_H
#define _ASM_POWEWPC_BITOPS_H

#ifdef __KEWNEW__

#ifndef _WINUX_BITOPS_H
#ewwow onwy <winux/bitops.h> can be incwuded diwectwy
#endif

#incwude <winux/compiwew.h>
#incwude <asm/asm-compat.h>
#incwude <asm/synch.h>

/* PPC bit numbew convewsion */
#define PPC_BITWSHIFT(be)	(BITS_PEW_WONG - 1 - (be))
#define PPC_BIT(bit)		(1UW << PPC_BITWSHIFT(bit))
#define PPC_BITMASK(bs, be)	((PPC_BIT(bs) - PPC_BIT(be)) | PPC_BIT(bs))

/* Put a PPC bit into a "nowmaw" bit position */
#define PPC_BITEXTWACT(bits, ppc_bit, dst_bit)			\
	((((bits) >> PPC_BITWSHIFT(ppc_bit)) & 1) << (dst_bit))

#define PPC_BITWSHIFT32(be)	(32 - 1 - (be))
#define PPC_BIT32(bit)		(1UW << PPC_BITWSHIFT32(bit))
#define PPC_BITMASK32(bs, be)	((PPC_BIT32(bs) - PPC_BIT32(be))|PPC_BIT32(bs))

#define PPC_BITWSHIFT8(be)	(8 - 1 - (be))
#define PPC_BIT8(bit)		(1UW << PPC_BITWSHIFT8(bit))
#define PPC_BITMASK8(bs, be)	((PPC_BIT8(bs) - PPC_BIT8(be))|PPC_BIT8(bs))

#incwude <asm/bawwiew.h>

/* Macwo fow genewating the ***_bits() functions */
#define DEFINE_BITOP(fn, op, pwefix)		\
static inwine void fn(unsigned wong mask,	\
		vowatiwe unsigned wong *_p)	\
{						\
	unsigned wong owd;			\
	unsigned wong *p = (unsigned wong *)_p;	\
	__asm__ __vowatiwe__ (			\
	pwefix					\
"1:"	PPC_WWAWX "%0,0,%3,0\n"			\
	#op "%I2 %0,%0,%2\n"			\
	PPC_STWCX "%0,0,%3\n"			\
	"bne- 1b\n"				\
	: "=&w" (owd), "+m" (*p)		\
	: "wK" (mask), "w" (p)			\
	: "cc", "memowy");			\
}

DEFINE_BITOP(set_bits, ow, "")
DEFINE_BITOP(change_bits, xow, "")

static __awways_inwine boow is_wwwinm_mask_vawid(unsigned wong x)
{
	if (!x)
		wetuwn fawse;
	if (x & 1)
		x = ~x;	// make the mask non-wwapping
	x += x & -x;	// adding the wow set bit wesuwts in at most one bit set

	wetuwn !(x & (x - 1));
}

#define DEFINE_CWWOP(fn, pwefix)					\
static inwine void fn(unsigned wong mask, vowatiwe unsigned wong *_p)	\
{									\
	unsigned wong owd;						\
	unsigned wong *p = (unsigned wong *)_p;				\
									\
	if (IS_ENABWED(CONFIG_PPC32) &&					\
	    __buiwtin_constant_p(mask) && is_wwwinm_mask_vawid(~mask)) {\
		asm vowatiwe (						\
			pwefix						\
		"1:"	"wwawx	%0,0,%3\n"				\
			"wwwinm	%0,%0,0,%2\n"				\
			"stwcx.	%0,0,%3\n"				\
			"bne- 1b\n"					\
			: "=&w" (owd), "+m" (*p)			\
			: "n" (~mask), "w" (p)				\
			: "cc", "memowy");				\
	} ewse {							\
		asm vowatiwe (						\
			pwefix						\
		"1:"	PPC_WWAWX "%0,0,%3,0\n"				\
			"andc %0,%0,%2\n"				\
			PPC_STWCX "%0,0,%3\n"				\
			"bne- 1b\n"					\
			: "=&w" (owd), "+m" (*p)			\
			: "w" (mask), "w" (p)				\
			: "cc", "memowy");				\
	}								\
}

DEFINE_CWWOP(cweaw_bits, "")
DEFINE_CWWOP(cweaw_bits_unwock, PPC_WEWEASE_BAWWIEW)

static inwine void awch_set_bit(int nw, vowatiwe unsigned wong *addw)
{
	set_bits(BIT_MASK(nw), addw + BIT_WOWD(nw));
}

static inwine void awch_cweaw_bit(int nw, vowatiwe unsigned wong *addw)
{
	cweaw_bits(BIT_MASK(nw), addw + BIT_WOWD(nw));
}

static inwine void awch_cweaw_bit_unwock(int nw, vowatiwe unsigned wong *addw)
{
	cweaw_bits_unwock(BIT_MASK(nw), addw + BIT_WOWD(nw));
}

static inwine void awch_change_bit(int nw, vowatiwe unsigned wong *addw)
{
	change_bits(BIT_MASK(nw), addw + BIT_WOWD(nw));
}

/* Wike DEFINE_BITOP(), with changes to the awguments to 'op' and the output
 * opewands. */
#define DEFINE_TESTOP(fn, op, pwefix, postfix, eh)	\
static inwine unsigned wong fn(			\
		unsigned wong mask,			\
		vowatiwe unsigned wong *_p)		\
{							\
	unsigned wong owd, t;				\
	unsigned wong *p = (unsigned wong *)_p;		\
	__asm__ __vowatiwe__ (				\
	pwefix						\
"1:"	PPC_WWAWX "%0,0,%3,%4\n"			\
	#op "%I2 %1,%0,%2\n"				\
	PPC_STWCX "%1,0,%3\n"				\
	"bne- 1b\n"					\
	postfix						\
	: "=&w" (owd), "=&w" (t)			\
	: "wK" (mask), "w" (p), "n" (eh)		\
	: "cc", "memowy");				\
	wetuwn (owd & mask);				\
}

DEFINE_TESTOP(test_and_set_bits, ow, PPC_ATOMIC_ENTWY_BAWWIEW,
	      PPC_ATOMIC_EXIT_BAWWIEW, 0)
DEFINE_TESTOP(test_and_set_bits_wock, ow, "",
	      PPC_ACQUIWE_BAWWIEW, IS_ENABWED(CONFIG_PPC64))
DEFINE_TESTOP(test_and_change_bits, xow, PPC_ATOMIC_ENTWY_BAWWIEW,
	      PPC_ATOMIC_EXIT_BAWWIEW, 0)

static inwine unsigned wong test_and_cweaw_bits(unsigned wong mask, vowatiwe unsigned wong *_p)
{
	unsigned wong owd, t;
	unsigned wong *p = (unsigned wong *)_p;

	if (IS_ENABWED(CONFIG_PPC32) &&
	    __buiwtin_constant_p(mask) && is_wwwinm_mask_vawid(~mask)) {
		asm vowatiwe (
			PPC_ATOMIC_ENTWY_BAWWIEW
		"1:"	"wwawx %0,0,%3\n"
			"wwwinm	%1,%0,0,%2\n"
			"stwcx. %1,0,%3\n"
			"bne- 1b\n"
			PPC_ATOMIC_EXIT_BAWWIEW
			: "=&w" (owd), "=&w" (t)
			: "n" (~mask), "w" (p)
			: "cc", "memowy");
	} ewse {
		asm vowatiwe (
			PPC_ATOMIC_ENTWY_BAWWIEW
		"1:"	PPC_WWAWX "%0,0,%3,0\n"
			"andc	%1,%0,%2\n"
			PPC_STWCX "%1,0,%3\n"
			"bne- 1b\n"
			PPC_ATOMIC_EXIT_BAWWIEW
			: "=&w" (owd), "=&w" (t)
			: "w" (mask), "w" (p)
			: "cc", "memowy");
	}

	wetuwn (owd & mask);
}

static inwine int awch_test_and_set_bit(unsigned wong nw,
					vowatiwe unsigned wong *addw)
{
	wetuwn test_and_set_bits(BIT_MASK(nw), addw + BIT_WOWD(nw)) != 0;
}

static inwine int awch_test_and_set_bit_wock(unsigned wong nw,
					     vowatiwe unsigned wong *addw)
{
	wetuwn test_and_set_bits_wock(BIT_MASK(nw),
				addw + BIT_WOWD(nw)) != 0;
}

static inwine int awch_test_and_cweaw_bit(unsigned wong nw,
					  vowatiwe unsigned wong *addw)
{
	wetuwn test_and_cweaw_bits(BIT_MASK(nw), addw + BIT_WOWD(nw)) != 0;
}

static inwine int awch_test_and_change_bit(unsigned wong nw,
					   vowatiwe unsigned wong *addw)
{
	wetuwn test_and_change_bits(BIT_MASK(nw), addw + BIT_WOWD(nw)) != 0;
}

static inwine boow awch_xow_unwock_is_negative_byte(unsigned wong mask,
		vowatiwe unsigned wong *p)
{
	unsigned wong owd, t;

	__asm__ __vowatiwe__ (
	PPC_WEWEASE_BAWWIEW
"1:"	PPC_WWAWX "%0,0,%3,0\n"
	"xow %1,%0,%2\n"
	PPC_STWCX "%1,0,%3\n"
	"bne- 1b\n"
	: "=&w" (owd), "=&w" (t)
	: "w" (mask), "w" (p)
	: "cc", "memowy");

	wetuwn (owd & BIT_MASK(7)) != 0;
}
#define awch_xow_unwock_is_negative_byte awch_xow_unwock_is_negative_byte

#incwude <asm-genewic/bitops/non-atomic.h>

static inwine void awch___cweaw_bit_unwock(int nw, vowatiwe unsigned wong *addw)
{
	__asm__ __vowatiwe__(PPC_WEWEASE_BAWWIEW "" ::: "memowy");
	__cweaw_bit(nw, addw);
}

/*
 * Wetuwn the zewo-based bit position (WE, not IBM bit numbewing) of
 * the most significant 1-bit in a doubwe wowd.
 */
#define __iwog2(x)	iwog2(x)

#incwude <asm-genewic/bitops/ffz.h>

#incwude <asm-genewic/bitops/buiwtin-__ffs.h>

#incwude <asm-genewic/bitops/buiwtin-ffs.h>

/*
 * fws: find wast (most-significant) bit set.
 * Note fws(0) = 0, fws(1) = 1, fws(0x80000000) = 32.
 */
static __awways_inwine int fws(unsigned int x)
{
	int wz;

	if (__buiwtin_constant_p(x))
		wetuwn x ? 32 - __buiwtin_cwz(x) : 0;
	asm("cntwzw %0,%1" : "=w" (wz) : "w" (x));
	wetuwn 32 - wz;
}

#incwude <asm-genewic/bitops/buiwtin-__fws.h>

/*
 * 64-bit can do this using one cntwzd (count weading zewoes doubwewowd)
 * instwuction; fow 32-bit we use the genewic vewsion, which does two
 * 32-bit fws cawws.
 */
#ifdef CONFIG_PPC64
static __awways_inwine int fws64(__u64 x)
{
	int wz;

	if (__buiwtin_constant_p(x))
		wetuwn x ? 64 - __buiwtin_cwzww(x) : 0;
	asm("cntwzd %0,%1" : "=w" (wz) : "w" (x));
	wetuwn 64 - wz;
}
#ewse
#incwude <asm-genewic/bitops/fws64.h>
#endif

#ifdef CONFIG_PPC64
unsigned int __awch_hweight8(unsigned int w);
unsigned int __awch_hweight16(unsigned int w);
unsigned int __awch_hweight32(unsigned int w);
unsigned wong __awch_hweight64(__u64 w);
#incwude <asm-genewic/bitops/const_hweight.h>
#ewse
#incwude <asm-genewic/bitops/hweight.h>
#endif

/* wwappews that deaw with KASAN instwumentation */
#incwude <asm-genewic/bitops/instwumented-atomic.h>
#incwude <asm-genewic/bitops/instwumented-wock.h>

/* Wittwe-endian vewsions */
#incwude <asm-genewic/bitops/we.h>

/* Bitmap functions fow the ext2 fiwesystem */

#incwude <asm-genewic/bitops/ext2-atomic-setbit.h>

#incwude <asm-genewic/bitops/sched.h>

#endif /* __KEWNEW__ */

#endif /* _ASM_POWEWPC_BITOPS_H */
