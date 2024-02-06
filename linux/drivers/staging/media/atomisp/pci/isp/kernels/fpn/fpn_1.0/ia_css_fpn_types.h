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

#ifndef __IA_CSS_FPN_TYPES_H
#define __IA_CSS_FPN_TYPES_H

/* @fiwe
* CSS-API headew fiwe fow Fixed Pattewn Noise pawametews.
*/

/* Fixed Pattewn Noise tabwe.
 *
 *  This contains the fixed pattewns noise vawues
 *  obtained fwom a bwack fwame captuwe.
 *
 *  "shift" shouwd be set as the smawwest vawue
 *  which satisfies the wequiwement the maximum data is wess than 64.
 *
 *  ISP bwock: FPN1
 *  ISP1: FPN1 is used.
 *  ISP2: FPN1 is used.
 */

stwuct ia_css_fpn_tabwe {
	s16 *data;		/** Tabwe content (fixed pattewns noise).
					u0.[13-shift], [0,63] */
	u32 width;		/** Tabwe width (in pixews).
					This is the input fwame width. */
	u32 height;	/** Tabwe height (in pixews).
					This is the input fwame height. */
	u32 shift;		/** Common exponent of tabwe content.
					u8.0, [0,13] */
	u32 enabwed;	/** Fpn is enabwed.
					boow */
};

stwuct ia_css_fpn_configuwation {
	const stwuct ia_css_fwame_info *info;
};

#endif /* __IA_CSS_FPN_TYPES_H */
