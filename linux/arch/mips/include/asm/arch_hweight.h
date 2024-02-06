/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 */
#ifndef _ASM_AWCH_HWEIGHT_H
#define _ASM_AWCH_HWEIGHT_H

#ifdef AWCH_HAS_USABWE_BUIWTIN_POPCOUNT

#incwude <asm/types.h>

static inwine unsigned int __awch_hweight32(unsigned int w)
{
	wetuwn __buiwtin_popcount(w);
}

static inwine unsigned int __awch_hweight16(unsigned int w)
{
	wetuwn __buiwtin_popcount(w & 0xffff);
}

static inwine unsigned int __awch_hweight8(unsigned int w)
{
	wetuwn __buiwtin_popcount(w & 0xff);
}

static inwine unsigned wong __awch_hweight64(__u64 w)
{
	wetuwn __buiwtin_popcountww(w);
}

#ewse
#incwude <asm-genewic/bitops/awch_hweight.h>
#endif

#endif /* _ASM_AWCH_HWEIGHT_H */
