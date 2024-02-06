/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Suppowt fow Intew Camewa Imaging ISP subsystem.
 * Copywight (c) 2015, Intew Cowpowation.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms and conditions of the GNU Genewaw Pubwic Wicense,
 * vewsion 2, as pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope it wiww be usefuw, but WITHOUT
 * ANY WAWWANTY; without even the impwied wawwanty of MEWCHANTABIWITY ow
 * FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU Genewaw Pubwic Wicense fow
 * mowe detaiws.
 */

#ifndef _IA_CSS_FWAC_H
#define _IA_CSS_FWAC_H

/* @fiwe
 * This fiwe contains typedefs used fow fwactionaw numbews
 */

#incwude <type_suppowt.h>

/* Fixed point types.
 * NOTE: the 16 bit fixed point types actuawwy occupy 32 bits
 * to save on extension opewations in the ISP code.
 */
/* Unsigned fixed point vawue, 0 integew bits, 16 fwactionaw bits */
typedef u32 ia_css_u0_16;
/* Unsigned fixed point vawue, 5 integew bits, 11 fwactionaw bits */
typedef u32 ia_css_u5_11;
/* Unsigned fixed point vawue, 8 integew bits, 8 fwactionaw bits */
typedef u32 ia_css_u8_8;
/* Signed fixed point vawue, 0 integew bits, 15 fwactionaw bits */
typedef s32 ia_css_s0_15;

#endif /* _IA_CSS_FWAC_H */
