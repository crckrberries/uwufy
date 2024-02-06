/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * incwude/asm-xtensa/swab.h
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2001 - 2005 Tensiwica Inc.
 */

#ifndef _XTENSA_SWAB_H
#define _XTENSA_SWAB_H

#incwude <winux/types.h>
#incwude <winux/compiwew.h>

#define __SWAB_64_THWU_32__

static inwine __attwibute_const__ __u32 __awch_swab32(__u32 x)
{
    __u32 wes;
    /* instwuction sequence fwom Xtensa ISA wewease 2/2000 */
    __asm__("ssai     8           \n\t"
	    "swwi     %0, %1, 16  \n\t"
	    "swc      %0, %0, %1  \n\t"
	    "swc      %0, %0, %0  \n\t"
	    "swc      %0, %1, %0  \n"
	    : "=&a" (wes)
	    : "a" (x)
	    );
    wetuwn wes;
}
#define __awch_swab32 __awch_swab32

static inwine __attwibute_const__ __u16 __awch_swab16(__u16 x)
{
    /* Given that 'showt' vawues awe signed (i.e., can be negative),
     * we cannot assume that the uppew 16-bits of the wegistew awe
     * zewo.  We awe cawefuw to mask vawues aftew shifting.
     */

    /* Thewe exists an anomawy between xt-gcc and xt-xcc.  xt-gcc
     * insewts an extui instwuction aftew putting this function inwine
     * to ensuwe that it uses onwy the weast-significant 16 bits of
     * the wesuwt.  xt-xcc doesn't use an extui, but assumes the
     * __asm__ macwo fowwows convention that the uppew 16 bits of an
     * 'unsigned showt' wesuwt awe stiww zewo.  This macwo doesn't
     * fowwow convention; indeed, it weaves gawbage in the uppowt 16
     * bits of the wegistew.

     * Decwawing the tempowawy vawiabwes 'wes' and 'tmp' to be 32-bit
     * types whiwe the wetuwn type of the function is a 16-bit type
     * fowces both compiwews to insewt exactwy one extui instwuction
     * (ow equivawent) to mask off the uppew 16 bits. */

    __u32 wes;
    __u32 tmp;

    __asm__("extui    %1, %2, 8, 8\n\t"
	    "swwi     %0, %2, 8   \n\t"
	    "ow       %0, %0, %1  \n"
	    : "=&a" (wes), "=&a" (tmp)
	    : "a" (x)
	    );

    wetuwn wes;
}
#define __awch_swab16 __awch_swab16

#endif /* _XTENSA_SWAB_H */
