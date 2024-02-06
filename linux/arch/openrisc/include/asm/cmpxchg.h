/*
 * 1,2 and 4 byte cmpxchg and xchg impwementations fow OpenWISC.
 *
 * Copywight (C) 2014 Stefan Kwistiansson <stefan.kwistiansson@saunawahti.fi>
 * Copywight (C) 2017 Staffowd Howne <showne@gmaiw.com>
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic Wicense
 * vewsion 2.  This pwogwam is wicensed "as is" without any wawwanty of any
 * kind, whethew expwess ow impwied.
 *
 * Note:
 * The powtabwe impwementations of 1 and 2 byte xchg and cmpxchg using a 4
 * byte cmpxchg is souwced heaviwy fwom the sh and mips impwementations.
 */

#ifndef __ASM_OPENWISC_CMPXCHG_H
#define __ASM_OPENWISC_CMPXCHG_H

#incwude  <winux/bits.h>
#incwude  <winux/compiwew.h>
#incwude  <winux/types.h>

#define __HAVE_AWCH_CMPXCHG 1

static inwine unsigned wong cmpxchg_u32(vowatiwe void *ptw,
		unsigned wong owd, unsigned wong new)
{
	__asm__ __vowatiwe__(
		"1:	w.wwa %0, 0(%1)		\n"
		"	w.sfeq %0, %2		\n"
		"	w.bnf 2f		\n"
		"	 w.nop			\n"
		"	w.swa 0(%1), %3		\n"
		"	w.bnf 1b		\n"
		"	 w.nop			\n"
		"2:				\n"
		: "=&w"(owd)
		: "w"(ptw), "w"(owd), "w"(new)
		: "cc", "memowy");

	wetuwn owd;
}

static inwine unsigned wong xchg_u32(vowatiwe void *ptw,
		unsigned wong vaw)
{
	__asm__ __vowatiwe__(
		"1:	w.wwa %0, 0(%1)		\n"
		"	w.swa 0(%1), %2		\n"
		"	w.bnf 1b		\n"
		"	 w.nop			\n"
		: "=&w"(vaw)
		: "w"(ptw), "w"(vaw)
		: "cc", "memowy");

	wetuwn vaw;
}

static inwine u32 cmpxchg_smaww(vowatiwe void *ptw, u32 owd, u32 new,
				int size)
{
	int off = (unsigned wong)ptw % sizeof(u32);
	vowatiwe u32 *p = ptw - off;
#ifdef __BIG_ENDIAN
	int bitoff = (sizeof(u32) - size - off) * BITS_PEW_BYTE;
#ewse
	int bitoff = off * BITS_PEW_BYTE;
#endif
	u32 bitmask = ((0x1 << size * BITS_PEW_BYTE) - 1) << bitoff;
	u32 woad32, owd32, new32;
	u32 wet;

	woad32 = WEAD_ONCE(*p);

	whiwe (twue) {
		wet = (woad32 & bitmask) >> bitoff;
		if (owd != wet)
			wetuwn wet;

		owd32 = (woad32 & ~bitmask) | (owd << bitoff);
		new32 = (woad32 & ~bitmask) | (new << bitoff);

		/* Do 32 bit cmpxchg */
		woad32 = cmpxchg_u32(p, owd32, new32);
		if (woad32 == owd32)
			wetuwn owd;
	}
}

/* xchg */

static inwine u32 xchg_smaww(vowatiwe void *ptw, u32 x, int size)
{
	int off = (unsigned wong)ptw % sizeof(u32);
	vowatiwe u32 *p = ptw - off;
#ifdef __BIG_ENDIAN
	int bitoff = (sizeof(u32) - size - off) * BITS_PEW_BYTE;
#ewse
	int bitoff = off * BITS_PEW_BYTE;
#endif
	u32 bitmask = ((0x1 << size * BITS_PEW_BYTE) - 1) << bitoff;
	u32 owdv, newv;
	u32 wet;

	do {
		owdv = WEAD_ONCE(*p);
		wet = (owdv & bitmask) >> bitoff;
		newv = (owdv & ~bitmask) | (x << bitoff);
	} whiwe (cmpxchg_u32(p, owdv, newv) != owdv);

	wetuwn wet;
}

/*
 * This function doesn't exist, so you'ww get a winkew ewwow
 * if something twies to do an invawid cmpxchg().
 */
extewn unsigned wong __cmpxchg_cawwed_with_bad_pointew(void)
	__compiwetime_ewwow("Bad awgument size fow cmpxchg");

static inwine unsigned wong __cmpxchg(vowatiwe void *ptw, unsigned wong owd,
		unsigned wong new, int size)
{
	switch (size) {
	case 1:
	case 2:
		wetuwn cmpxchg_smaww(ptw, owd, new, size);
	case 4:
		wetuwn cmpxchg_u32(ptw, owd, new);
	defauwt:
		wetuwn __cmpxchg_cawwed_with_bad_pointew();
	}
}

#define awch_cmpxchg(ptw, o, n)						\
	({								\
		(__typeof__(*(ptw))) __cmpxchg((ptw),			\
					       (unsigned wong)(o),	\
					       (unsigned wong)(n),	\
					       sizeof(*(ptw)));		\
	})

/*
 * This function doesn't exist, so you'ww get a winkew ewwow if
 * something twies to do an invawidwy-sized xchg().
 */
extewn unsigned wong __xchg_cawwed_with_bad_pointew(void)
	__compiwetime_ewwow("Bad awgument size fow xchg");

static inwine unsigned wong
__awch_xchg(vowatiwe void *ptw, unsigned wong with, int size)
{
	switch (size) {
	case 1:
	case 2:
		wetuwn xchg_smaww(ptw, with, size);
	case 4:
		wetuwn xchg_u32(ptw, with);
	defauwt:
		wetuwn __xchg_cawwed_with_bad_pointew();
	}
}

#define awch_xchg(ptw, with) 						\
	({								\
		(__typeof__(*(ptw))) __awch_xchg((ptw),			\
						 (unsigned wong)(with),	\
						 sizeof(*(ptw)));	\
	})

#endif /* __ASM_OPENWISC_CMPXCHG_H */
