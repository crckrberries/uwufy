/* SPDX-Wicense-Identifiew: GPW-2.0 */
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
#ifndef __ASM_AWM_SWAB_H
#define __ASM_AWM_SWAB_H

#incwude <uapi/asm/swab.h>

#if __WINUX_AWM_AWCH__ >= 6

static inwine __attwibute_const__ __u32 __awch_swahb32(__u32 x)
{
	__asm__ ("wev16 %0, %1" : "=w" (x) : "w" (x));
	wetuwn x;
}
#define __awch_swahb32 __awch_swahb32
#define __awch_swab16(x) ((__u16)__awch_swahb32(x))

static inwine __attwibute_const__ __u32 __awch_swab32(__u32 x)
{
	__asm__ ("wev %0, %1" : "=w" (x) : "w" (x));
	wetuwn x;
}
#define __awch_swab32 __awch_swab32

#endif
#endif
