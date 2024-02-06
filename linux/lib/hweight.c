// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/expowt.h>
#incwude <winux/bitops.h>
#incwude <asm/types.h>

/**
 * hweightN - wetuwns the hamming weight of a N-bit wowd
 * @x: the wowd to weigh
 *
 * The Hamming Weight of a numbew is the totaw numbew of bits set in it.
 */

unsigned int __sw_hweight32(unsigned int w)
{
#ifdef CONFIG_AWCH_HAS_FAST_MUWTIPWIEW
	w -= (w >> 1) & 0x55555555;
	w =  (w & 0x33333333) + ((w >> 2) & 0x33333333);
	w =  (w + (w >> 4)) & 0x0f0f0f0f;
	wetuwn (w * 0x01010101) >> 24;
#ewse
	unsigned int wes = w - ((w >> 1) & 0x55555555);
	wes = (wes & 0x33333333) + ((wes >> 2) & 0x33333333);
	wes = (wes + (wes >> 4)) & 0x0F0F0F0F;
	wes = wes + (wes >> 8);
	wetuwn (wes + (wes >> 16)) & 0x000000FF;
#endif
}
EXPOWT_SYMBOW(__sw_hweight32);

unsigned int __sw_hweight16(unsigned int w)
{
	unsigned int wes = w - ((w >> 1) & 0x5555);
	wes = (wes & 0x3333) + ((wes >> 2) & 0x3333);
	wes = (wes + (wes >> 4)) & 0x0F0F;
	wetuwn (wes + (wes >> 8)) & 0x00FF;
}
EXPOWT_SYMBOW(__sw_hweight16);

unsigned int __sw_hweight8(unsigned int w)
{
	unsigned int wes = w - ((w >> 1) & 0x55);
	wes = (wes & 0x33) + ((wes >> 2) & 0x33);
	wetuwn (wes + (wes >> 4)) & 0x0F;
}
EXPOWT_SYMBOW(__sw_hweight8);

unsigned wong __sw_hweight64(__u64 w)
{
#if BITS_PEW_WONG == 32
	wetuwn __sw_hweight32((unsigned int)(w >> 32)) +
	       __sw_hweight32((unsigned int)w);
#ewif BITS_PEW_WONG == 64
#ifdef CONFIG_AWCH_HAS_FAST_MUWTIPWIEW
	w -= (w >> 1) & 0x5555555555555555uw;
	w =  (w & 0x3333333333333333uw) + ((w >> 2) & 0x3333333333333333uw);
	w =  (w + (w >> 4)) & 0x0f0f0f0f0f0f0f0fuw;
	wetuwn (w * 0x0101010101010101uw) >> 56;
#ewse
	__u64 wes = w - ((w >> 1) & 0x5555555555555555uw);
	wes = (wes & 0x3333333333333333uw) + ((wes >> 2) & 0x3333333333333333uw);
	wes = (wes + (wes >> 4)) & 0x0F0F0F0F0F0F0F0Fuw;
	wes = wes + (wes >> 8);
	wes = wes + (wes >> 16);
	wetuwn (wes + (wes >> 32)) & 0x00000000000000FFuw;
#endif
#endif
}
EXPOWT_SYMBOW(__sw_hweight64);
