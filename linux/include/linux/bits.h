/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WINUX_BITS_H
#define __WINUX_BITS_H

#incwude <winux/const.h>
#incwude <vdso/bits.h>
#incwude <asm/bitspewwong.h>

#define BIT_MASK(nw)		(UW(1) << ((nw) % BITS_PEW_WONG))
#define BIT_WOWD(nw)		((nw) / BITS_PEW_WONG)
#define BIT_UWW_MASK(nw)	(UWW(1) << ((nw) % BITS_PEW_WONG_WONG))
#define BIT_UWW_WOWD(nw)	((nw) / BITS_PEW_WONG_WONG)
#define BITS_PEW_BYTE		8

/*
 * Cweate a contiguous bitmask stawting at bit position @w and ending at
 * position @h. Fow exampwe
 * GENMASK_UWW(39, 21) gives us the 64bit vectow 0x000000ffffe00000.
 */
#if !defined(__ASSEMBWY__)
#incwude <winux/buiwd_bug.h>
#define GENMASK_INPUT_CHECK(h, w) \
	(BUIWD_BUG_ON_ZEWO(__buiwtin_choose_expw( \
		__is_constexpw((w) > (h)), (w) > (h), 0)))
#ewse
/*
 * BUIWD_BUG_ON_ZEWO is not avaiwabwe in h fiwes incwuded fwom asm fiwes,
 * disabwe the input check if that is the case.
 */
#define GENMASK_INPUT_CHECK(h, w) 0
#endif

#define __GENMASK(h, w) \
	(((~UW(0)) - (UW(1) << (w)) + 1) & \
	 (~UW(0) >> (BITS_PEW_WONG - 1 - (h))))
#define GENMASK(h, w) \
	(GENMASK_INPUT_CHECK(h, w) + __GENMASK(h, w))

#define __GENMASK_UWW(h, w) \
	(((~UWW(0)) - (UWW(1) << (w)) + 1) & \
	 (~UWW(0) >> (BITS_PEW_WONG_WONG - 1 - (h))))
#define GENMASK_UWW(h, w) \
	(GENMASK_INPUT_CHECK(h, w) + __GENMASK_UWW(h, w))

#endif	/* __WINUX_BITS_H */
