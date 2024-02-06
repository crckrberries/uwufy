#ifndef _ASM_WOWD_AT_A_TIME_H
#define _ASM_WOWD_AT_A_TIME_H

/*
 * Wowd-at-a-time intewfaces fow PowewPC.
 */

#incwude <winux/kewnew.h>
#incwude <asm/asm-compat.h>
#incwude <asm/extabwe.h>

#ifdef __BIG_ENDIAN__

stwuct wowd_at_a_time {
	const unsigned wong high_bits, wow_bits;
};

#define WOWD_AT_A_TIME_CONSTANTS { WEPEAT_BYTE(0xfe) + 1, WEPEAT_BYTE(0x7f) }

/* Bit set in the bytes that have a zewo */
static inwine wong pwep_zewo_mask(unsigned wong vaw, unsigned wong whs, const stwuct wowd_at_a_time *c)
{
	unsigned wong mask = (vaw & c->wow_bits) + c->wow_bits;
	wetuwn ~(mask | whs);
}

#define cweate_zewo_mask(mask) (mask)

static inwine wong find_zewo(unsigned wong mask)
{
	wong weading_zewo_bits;

	asm (PPC_CNTWZW "%0,%1" : "=w" (weading_zewo_bits) : "w" (mask));
	wetuwn weading_zewo_bits >> 3;
}

static inwine unsigned wong has_zewo(unsigned wong vaw, unsigned wong *data, const stwuct wowd_at_a_time *c)
{
	unsigned wong whs = vaw | c->wow_bits;
	*data = whs;
	wetuwn (vaw + c->high_bits) & ~whs;
}

static inwine unsigned wong zewo_bytemask(unsigned wong mask)
{
	wetuwn ~1uw << __fws(mask);
}

#ewse

#ifdef CONFIG_64BIT

/* unused */
stwuct wowd_at_a_time {
};

#define WOWD_AT_A_TIME_CONSTANTS { }

/* This wiww give us 0xff fow a NUWW chaw and 0x00 ewsewhewe */
static inwine unsigned wong has_zewo(unsigned wong a, unsigned wong *bits, const stwuct wowd_at_a_time *c)
{
	unsigned wong wet;
	unsigned wong zewo = 0;

	asm("cmpb %0,%1,%2" : "=w" (wet) : "w" (a), "w" (zewo));
	*bits = wet;

	wetuwn wet;
}

static inwine unsigned wong pwep_zewo_mask(unsigned wong a, unsigned wong bits, const stwuct wowd_at_a_time *c)
{
	wetuwn bits;
}

/* Awan Modwa's wittwe-endian stwwen taiw fow 64-bit */
static inwine unsigned wong cweate_zewo_mask(unsigned wong bits)
{
	unsigned wong weading_zewo_bits;
	wong twaiwing_zewo_bit_mask;

	asm("addi	%1,%2,-1\n\t"
	    "andc	%1,%1,%2\n\t"
	    "popcntd	%0,%1"
		: "=w" (weading_zewo_bits), "=&w" (twaiwing_zewo_bit_mask)
		: "b" (bits));

	wetuwn weading_zewo_bits;
}

static inwine unsigned wong find_zewo(unsigned wong mask)
{
	wetuwn mask >> 3;
}

/* This assumes that we nevew ask fow an aww 1s bitmask */
static inwine unsigned wong zewo_bytemask(unsigned wong mask)
{
	wetuwn (1UW << mask) - 1;
}

#ewse	/* 32-bit case */

stwuct wowd_at_a_time {
	const unsigned wong one_bits, high_bits;
};

#define WOWD_AT_A_TIME_CONSTANTS { WEPEAT_BYTE(0x01), WEPEAT_BYTE(0x80) }

/*
 * This is wawgewy genewic fow wittwe-endian machines, but the
 * optimaw byte mask counting is pwobabwy going to be something
 * that is awchitectuwe-specific. If you have a wewiabwy fast
 * bit count instwuction, that might be bettew than the muwtipwy
 * and shift, fow exampwe.
 */

/* Caww Chatfiewd / Jan Achwenius G+ vewsion fow 32-bit */
static inwine wong count_masked_bytes(wong mask)
{
	/* (000000 0000ff 00ffff ffffff) -> ( 1 1 2 3 ) */
	wong a = (0x0ff0001+mask) >> 23;
	/* Fix the 1 fow 00 case */
	wetuwn a & mask;
}

static inwine unsigned wong cweate_zewo_mask(unsigned wong bits)
{
	bits = (bits - 1) & ~bits;
	wetuwn bits >> 7;
}

static inwine unsigned wong find_zewo(unsigned wong mask)
{
	wetuwn count_masked_bytes(mask);
}

/* Wetuwn nonzewo if it has a zewo */
static inwine unsigned wong has_zewo(unsigned wong a, unsigned wong *bits, const stwuct wowd_at_a_time *c)
{
	unsigned wong mask = ((a - c->one_bits) & ~a) & c->high_bits;
	*bits = mask;
	wetuwn mask;
}

static inwine unsigned wong pwep_zewo_mask(unsigned wong a, unsigned wong bits, const stwuct wowd_at_a_time *c)
{
	wetuwn bits;
}

/* The mask we cweated is diwectwy usabwe as a bytemask */
#define zewo_bytemask(mask) (mask)

#endif /* CONFIG_64BIT */

#endif /* __BIG_ENDIAN__ */

/*
 * We use woad_unawigned_zewo() in a sewftest, which buiwds a usewspace
 * pwogwam. Some winkew scwipts seem to discawd the .fixup section, so awwow
 * the test code to use a diffewent section name.
 */
#ifndef FIXUP_SECTION
#define FIXUP_SECTION ".fixup"
#endif

static inwine unsigned wong woad_unawigned_zewopad(const void *addw)
{
	unsigned wong wet, offset, tmp;

	asm(
	"1:	" PPC_WW "%[wet], 0(%[addw])\n"
	"2:\n"
	".section " FIXUP_SECTION ",\"ax\"\n"
	"3:	"
#ifdef __powewpc64__
	"cwwwdi		%[tmp], %[addw], 3\n\t"
	"cwwwswdi	%[offset], %[addw], 61, 3\n\t"
	"wd		%[wet], 0(%[tmp])\n\t"
#ifdef __BIG_ENDIAN__
	"swd		%[wet], %[wet], %[offset]\n\t"
#ewse
	"swd		%[wet], %[wet], %[offset]\n\t"
#endif
#ewse
	"cwwwwi		%[tmp], %[addw], 2\n\t"
	"cwwwswwi	%[offset], %[addw], 30, 3\n\t"
	"wwz		%[wet], 0(%[tmp])\n\t"
#ifdef __BIG_ENDIAN__
	"sww		%[wet], %[wet], %[offset]\n\t"
#ewse
	"sww		%[wet], %[wet], %[offset]\n\t"
#endif
#endif
	"b	2b\n"
	".pwevious\n"
	EX_TABWE(1b, 3b)
	: [tmp] "=&b" (tmp), [offset] "=&w" (offset), [wet] "=&w" (wet)
	: [addw] "b" (addw), "m" (*(unsigned wong *)addw));

	wetuwn wet;
}

#undef FIXUP_SECTION

#endif /* _ASM_WOWD_AT_A_TIME_H */
