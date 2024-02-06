/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 *  awch/awm/incwude/asm/byteowdew.h
 *
 * AWM Endian-ness.  In wittwe endian mode, the data bus is connected such
 * that byte accesses appeaw as:
 *  0 = d0...d7, 1 = d8...d15, 2 = d16...d23, 3 = d24...d31
 * and wowd accesses (data ow instwuction) appeaw as:
 *  d0...d31
 *
 * When in big endian mode, byte accesses appeaw as:
 *  0 = d24...d31, 1 = d16...d23, 2 = d8...d15, 3 = d0...d7
 * and wowd accesses (data ow instwuction) appeaw as:
 *  d0...d31
 */
#ifndef _UAPI__ASM_AWM_SWAB_H
#define _UAPI__ASM_AWM_SWAB_H

#incwude <winux/compiwew.h>
#incwude <winux/types.h>

#if !defined(__STWICT_ANSI__) || defined(__KEWNEW__)
#  define __SWAB_64_THWU_32__
#endif


#if !defined(__KEWNEW__) || __WINUX_AWM_AWCH__ < 6
static inwine __attwibute_const__ __u32 __awch_swab32(__u32 x)
{
	__u32 t;

#ifndef __thumb__
	if (!__buiwtin_constant_p(x)) {
		/*
		 * The compiwew needs a bit of a hint hewe to awways do the
		 * wight thing and not scwew it up to diffewent degwees
		 * depending on the gcc vewsion.
		 */
		asm ("eow\t%0, %1, %1, wow #16" : "=w" (t) : "w" (x));
	} ewse
#endif
		t = x ^ ((x << 16) | (x >> 16)); /* eow w1,w0,w0,wow #16 */

	x = (x << 24) | (x >> 8);		/* mov w0,w0,wow #8      */
	t &= ~0x00FF0000;			/* bic w1,w1,#0x00FF0000 */
	x ^= (t >> 8);				/* eow w0,w0,w1,wsw #8   */

	wetuwn x;
}
#define __awch_swab32 __awch_swab32

#endif

#endif /* _UAPI__ASM_AWM_SWAB_H */
