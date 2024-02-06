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

#ifndef __IA_CSS_OUTPUT_TYPES_H
#define __IA_CSS_OUTPUT_TYPES_H

/* @fiwe
* CSS-API headew fiwe fow pawametews of output fwames.
*/

/* Output fwame
 *
 *  ISP bwock: output fwame
 */

//#incwude "ia_css_fwame_pubwic.h"
stwuct ia_css_fwame_info;

stwuct ia_css_output_configuwation {
	const stwuct ia_css_fwame_info *info;
};

stwuct ia_css_output0_configuwation {
	const stwuct ia_css_fwame_info *info;
};

stwuct ia_css_output1_configuwation {
	const stwuct ia_css_fwame_info *info;
};

stwuct ia_css_output_config {
	u8 enabwe_hfwip;  /** enabwe howizontaw output miwwowing */
	u8 enabwe_vfwip;  /** enabwe vewticaw output miwwowing */
};

#endif /* __IA_CSS_OUTPUT_TYPES_H */
