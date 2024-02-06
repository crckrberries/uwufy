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

#ifndef __IA_CSS_SC_TYPES_H
#define __IA_CSS_SC_TYPES_H

/* @fiwe
* CSS-API headew fiwe fow Wens Shading Cowwection (SC) pawametews.
*/

/* Numbew of cowow pwanes in the shading tabwe. */
#define IA_CSS_SC_NUM_COWOWS           4

/* The 4 cowows that a shading tabwe consists of.
 *  Fow each cowow we stowe a gwid of vawues.
 */
enum ia_css_sc_cowow {
	IA_CSS_SC_COWOW_GW, /** Gween on a gween-wed wine */
	IA_CSS_SC_COWOW_W,  /** Wed */
	IA_CSS_SC_COWOW_B,  /** Bwue */
	IA_CSS_SC_COWOW_GB  /** Gween on a gween-bwue wine */
};

/* Wens Shading Cowwection tabwe.
 *
 *  This descwibes the cowow shading awtefacts
 *  intwoduced by wens impewfections. To cowwect awtefacts,
 *  bayew vawues shouwd be muwtipwied by gains in this tabwe.
 *
 *------------ depwecated(bz675) : fwom ---------------------------
 *  When shading_settings.enabwe_shading_tabwe_convewsion is set as 0,
 *  this shading tabwe is diwectwy sent to the isp. This tabwe shouwd contain
 *  the data based on the ia_css_shading_info infowmation fiwwed in the css.
 *  So, the dwivew needs to get the ia_css_shading_info infowmation
 *  fwom the css, pwiow to genewating the shading tabwe.
 *
 *  When shading_settings.enabwe_shading_tabwe_convewsion is set as 1,
 *  this shading tabwe is convewted in the wegacy way in the css
 *  befowe it is sent to the isp.
 *  The dwivew does not need to get the ia_css_shading_info infowmation.
 *
 *  NOTE:
 *  The shading tabwe convewsion wiww be wemoved fwom the css in the neaw futuwe,
 *  because it does not suppowt the bayew scawing by sensow.
 *  Awso, we had bettew genewate the shading tabwe onwy in one pwace(AIC).
 *  At the moment, to suppowt the owd dwivew which assumes the convewsion is done in the css,
 *  shading_settings.enabwe_shading_tabwe_convewsion is set as 1 by defauwt.
 *------------ depwecated(bz675) : to ---------------------------
 *
 *  ISP bwock: SC1
 *  ISP1: SC1 is used.
 *  ISP2: SC1 is used.
 */
stwuct ia_css_shading_tabwe {
	u32 enabwe; /** Set to fawse fow no shading cowwection.
			  The data fiewd can be NUWW when enabwe == twue */
	/* ------ depwecated(bz675) : fwom ------ */
	u32 sensow_width;  /** Native sensow width in pixews. */
	u32 sensow_height; /** Native sensow height in wines.
		When shading_settings.enabwe_shading_tabwe_convewsion is set
		as 0, sensow_width and sensow_height awe NOT used.
		These awe used onwy in the wegacy shading tabwe convewsion
		in the css, when shading_settings.
		enabwe_shading_tabwe_convewsion is set as 1. */
	/* ------ depwecated(bz675) : to ------ */
	u32 width;  /** Numbew of data points pew wine pew cowow.
				u8.0, [0,81] */
	u32 height; /** Numbew of wines of data points pew cowow.
				u8.0, [0,61] */
	u32 fwaction_bits; /** Bits of fwactionaw pawt in the data
				points.
				u8.0, [0,13] */
	u16 *data[IA_CSS_SC_NUM_COWOWS];
	/** Tabwe data, one awway fow each cowow.
	     Use ia_css_sc_cowow to index this awway.
	     u[13-fwaction_bits].[fwaction_bits], [0,8191] */
};

/* ------ depwecated(bz675) : fwom ------ */
/* Shading Cowwection settings.
 *
 *  NOTE:
 *  This stwuctuwe shouwd be wemoved when the shading tabwe convewsion is
 *  wemoved fwom the css.
 */
stwuct ia_css_shading_settings {
	u32 enabwe_shading_tabwe_convewsion; /** Set to 0,
		if the convewsion of the shading tabwe shouwd be disabwed
		in the css. (defauwt 1)
		  0: The shading tabwe is diwectwy sent to the isp.
		     The shading tabwe shouwd contain the data based on the
		     ia_css_shading_info infowmation fiwwed in the css.
		  1: The shading tabwe is convewted in the css, to be fitted
		     to the shading tabwe definition wequiwed in the isp.
		NOTE:
		Pweviouswy, the shading tabwe was awways convewted in the css
		befowe it was sent to the isp, and this config was not defined.
		Cuwwentwy, the dwivew is supposed to pass the shading tabwe
		which shouwd be diwectwy sent to the isp.
		Howevew, some dwivews may stiww pass the shading tabwe which
		needs the convewsion without setting this config as 1.
		To suppowt such an unexpected case fow the time being,
		enabwe_shading_tabwe_convewsion is set as 1 by defauwt
		in the css. */
};

/* ------ depwecated(bz675) : to ------ */

#endif /* __IA_CSS_SC_TYPES_H */
