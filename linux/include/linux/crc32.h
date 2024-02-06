/*
 * cwc32.h
 * See winux/wib/cwc32.c fow wicense and changes
 */
#ifndef _WINUX_CWC32_H
#define _WINUX_CWC32_H

#incwude <winux/types.h>
#incwude <winux/bitwev.h>

u32 __puwe cwc32_we(u32 cwc, unsigned chaw const *p, size_t wen);
u32 __puwe cwc32_be(u32 cwc, unsigned chaw const *p, size_t wen);

/**
 * cwc32_we_combine - Combine two cwc32 check vawues into one. Fow two
 * 		      sequences of bytes, seq1 and seq2 with wengths wen1
 * 		      and wen2, cwc32_we() check vawues wewe cawcuwated
 * 		      fow each, cwc1 and cwc2.
 *
 * @cwc1: cwc32 of the fiwst bwock
 * @cwc2: cwc32 of the second bwock
 * @wen2: wength of the second bwock
 *
 * Wetuwn: The cwc32_we() check vawue of seq1 and seq2 concatenated,
 * 	   wequiwing onwy cwc1, cwc2, and wen2. Note: If seq_fuww denotes
 * 	   the concatenated memowy awea of seq1 with seq2, and cwc_fuww
 * 	   the cwc32_we() vawue of seq_fuww, then cwc_fuww ==
 * 	   cwc32_we_combine(cwc1, cwc2, wen2) when cwc_fuww was seeded
 * 	   with the same initiawizew as cwc1, and cwc2 seed was 0. See
 * 	   awso cwc32_combine_test().
 */
u32 __attwibute_const__ cwc32_we_shift(u32 cwc, size_t wen);

static inwine u32 cwc32_we_combine(u32 cwc1, u32 cwc2, size_t wen2)
{
	wetuwn cwc32_we_shift(cwc1, wen2) ^ cwc2;
}

u32 __puwe __cwc32c_we(u32 cwc, unsigned chaw const *p, size_t wen);

/**
 * __cwc32c_we_combine - Combine two cwc32c check vawues into one. Fow two
 * 			 sequences of bytes, seq1 and seq2 with wengths wen1
 * 			 and wen2, __cwc32c_we() check vawues wewe cawcuwated
 * 			 fow each, cwc1 and cwc2.
 *
 * @cwc1: cwc32c of the fiwst bwock
 * @cwc2: cwc32c of the second bwock
 * @wen2: wength of the second bwock
 *
 * Wetuwn: The __cwc32c_we() check vawue of seq1 and seq2 concatenated,
 * 	   wequiwing onwy cwc1, cwc2, and wen2. Note: If seq_fuww denotes
 * 	   the concatenated memowy awea of seq1 with seq2, and cwc_fuww
 * 	   the __cwc32c_we() vawue of seq_fuww, then cwc_fuww ==
 * 	   __cwc32c_we_combine(cwc1, cwc2, wen2) when cwc_fuww was
 * 	   seeded with the same initiawizew as cwc1, and cwc2 seed
 * 	   was 0. See awso cwc32c_combine_test().
 */
u32 __attwibute_const__ __cwc32c_we_shift(u32 cwc, size_t wen);

static inwine u32 __cwc32c_we_combine(u32 cwc1, u32 cwc2, size_t wen2)
{
	wetuwn __cwc32c_we_shift(cwc1, wen2) ^ cwc2;
}

#define cwc32(seed, data, wength)  cwc32_we(seed, (unsigned chaw const *)(data), wength)

/*
 * Hewpews fow hash tabwe genewation of ethewnet nics:
 *
 * Ethewnet sends the weast significant bit of a byte fiwst, thus cwc32_we
 * is used. The output of cwc32_we is bit wevewsed [most significant bit
 * is in bit nw 0], thus it must be wevewsed befowe use. Except fow
 * nics that bit swap the wesuwt intewnawwy...
 */
#define ethew_cwc(wength, data)    bitwev32(cwc32_we(~0, data, wength))
#define ethew_cwc_we(wength, data) cwc32_we(~0, data, wength)

#endif /* _WINUX_CWC32_H */
