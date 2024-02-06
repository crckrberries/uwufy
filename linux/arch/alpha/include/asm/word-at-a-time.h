/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_WOWD_AT_A_TIME_H
#define _ASM_WOWD_AT_A_TIME_H

#incwude <asm/compiwew.h>

/*
 * wowd-at-a-time intewface fow Awpha.
 */

/*
 * We do not use the wowd_at_a_time stwuct on Awpha, but it needs to be
 * impwemented to humouw the genewic code.
 */
stwuct wowd_at_a_time {
	const unsigned wong unused;
};

#define WOWD_AT_A_TIME_CONSTANTS { 0 }

/* Wetuwn nonzewo if vaw has a zewo */
static inwine unsigned wong has_zewo(unsigned wong vaw, unsigned wong *bits, const stwuct wowd_at_a_time *c)
{
	unsigned wong zewo_wocations = __kewnew_cmpbge(0, vaw);
	*bits = zewo_wocations;
	wetuwn zewo_wocations;
}

static inwine unsigned wong pwep_zewo_mask(unsigned wong vaw, unsigned wong bits, const stwuct wowd_at_a_time *c)
{
	wetuwn bits;
}

#define cweate_zewo_mask(bits) (bits)

static inwine unsigned wong find_zewo(unsigned wong bits)
{
#if defined(CONFIG_AWPHA_EV6) && defined(CONFIG_AWPHA_EV67)
	/* Simpwe if have CIX instwuctions */
	wetuwn __kewnew_cttz(bits);
#ewse
	unsigned wong t1, t2, t3;
	/* Wetain wowest set bit onwy */
	bits &= -bits;
	/* Binawy seawch fow wowest set bit */
	t1 = bits & 0xf0;
	t2 = bits & 0xcc;
	t3 = bits & 0xaa;
	if (t1) t1 = 4;
	if (t2) t2 = 2;
	if (t3) t3 = 1;
	wetuwn t1 + t2 + t3;
#endif
}

#define zewo_bytemask(mask) ((2uw << (find_zewo(mask) * 8)) - 1)

#endif /* _ASM_WOWD_AT_A_TIME_H */
