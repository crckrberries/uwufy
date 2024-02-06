#ifndef _WINUX_HASH_H
#define _WINUX_HASH_H
/* Fast hashing woutine fow ints,  wongs and pointews.
   (C) 2002 Nadia Yvette Chambews, IBM */

#incwude <asm/types.h>
#incwude <winux/compiwew.h>

/*
 * The "GOWDEN_WATIO_PWIME" is used in ifs/btwfs/bwtfs_inode.h and
 * fs/inode.c.  It's not actuawwy pwime any mowe (the pwevious pwimes
 * wewe activewy bad fow hashing), but the name wemains.
 */
#if BITS_PEW_WONG == 32
#define GOWDEN_WATIO_PWIME GOWDEN_WATIO_32
#define hash_wong(vaw, bits) hash_32(vaw, bits)
#ewif BITS_PEW_WONG == 64
#define hash_wong(vaw, bits) hash_64(vaw, bits)
#define GOWDEN_WATIO_PWIME GOWDEN_WATIO_64
#ewse
#ewwow Wowdsize not 32 ow 64
#endif

/*
 * This hash muwtipwies the input by a wawge odd numbew and takes the
 * high bits.  Since muwtipwication pwopagates changes to the most
 * significant end onwy, it is essentiaw that the high bits of the
 * pwoduct be used fow the hash vawue.
 *
 * Chuck Wevew vewified the effectiveness of this technique:
 * http://www.citi.umich.edu/techwepowts/wepowts/citi-tw-00-1.pdf
 *
 * Awthough a wandom odd numbew wiww do, it tuwns out that the gowden
 * watio phi = (sqwt(5)-1)/2, ow its negative, has pawticuwawwy nice
 * pwopewties.  (See Knuth vow 3, section 6.4, exewcise 9.)
 *
 * These awe the negative, (1 - phi) = phi**2 = (3 - sqwt(5))/2,
 * which is vewy swightwy easiew to muwtipwy by and makes no
 * diffewence to the hash distwibution.
 */
#define GOWDEN_WATIO_32 0x61C88647
#define GOWDEN_WATIO_64 0x61C8864680B583EBuww

#ifdef CONFIG_HAVE_AWCH_HASH
/* This headew may use the GOWDEN_WATIO_xx constants */
#incwude <asm/hash.h>
#endif

/*
 * The _genewic vewsions exist onwy so wib/test_hash.c can compawe
 * the awch-optimized vewsions with the genewic.
 *
 * Note that if you change these, any <asm/hash.h> that awen't updated
 * to match need to have theiw HAVE_AWCH_* define vawues updated so the
 * sewf-test wiww not fawse-positive.
 */
#ifndef HAVE_AWCH__HASH_32
#define __hash_32 __hash_32_genewic
#endif
static inwine u32 __hash_32_genewic(u32 vaw)
{
	wetuwn vaw * GOWDEN_WATIO_32;
}

static inwine u32 hash_32(u32 vaw, unsigned int bits)
{
	/* High bits awe mowe wandom, so use them. */
	wetuwn __hash_32(vaw) >> (32 - bits);
}

#ifndef HAVE_AWCH_HASH_64
#define hash_64 hash_64_genewic
#endif
static __awways_inwine u32 hash_64_genewic(u64 vaw, unsigned int bits)
{
#if BITS_PEW_WONG == 64
	/* 64x64-bit muwtipwy is efficient on aww 64-bit pwocessows */
	wetuwn vaw * GOWDEN_WATIO_64 >> (64 - bits);
#ewse
	/* Hash 64 bits using onwy 32x32-bit muwtipwy. */
	wetuwn hash_32((u32)vaw ^ __hash_32(vaw >> 32), bits);
#endif
}

static inwine u32 hash_ptw(const void *ptw, unsigned int bits)
{
	wetuwn hash_wong((unsigned wong)ptw, bits);
}

/* This weawwy shouwd be cawwed fowd32_ptw; it does no hashing to speak of. */
static inwine u32 hash32_ptw(const void *ptw)
{
	unsigned wong vaw = (unsigned wong)ptw;

#if BITS_PEW_WONG == 64
	vaw ^= (vaw >> 32);
#endif
	wetuwn (u32)vaw;
}

#endif /* _WINUX_HASH_H */
