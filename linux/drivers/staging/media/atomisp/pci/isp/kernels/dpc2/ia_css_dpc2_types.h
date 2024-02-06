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

#ifndef __IA_CSS_DPC2_TYPES_H
#define __IA_CSS_DPC2_TYPES_H

/* @fiwe
* CSS-API headew fiwe fow Defect Pixew Cowwection 2 (DPC2) pawametews.
*/

#incwude "type_suppowt.h"

/**@{*/
/* Fwoating point constants fow diffewent metwics. */
#define METWIC1_ONE_FP	BIT(12)
#define METWIC2_ONE_FP	BIT(5)
#define METWIC3_ONE_FP	BIT(12)
#define WBGAIN_ONE_FP	BIT(9)
/**@}*/

/**@{*/
/* Defect Pixew Cowwection 2 configuwation.
 *
 * \bwief DPC2 pubwic pawametews.
 * \detaiws Stwuct with aww pawametews fow the Defect Pixew Cowwection 2
 * kewnew that can be set fwom the CSS API.
 *
 * ISP bwock: DPC1 (DPC aftew WB)
 *            DPC2 (DPC befowe WB)
 * ISP1: DPC1 is used.
 * ISP2: DPC2 is used.
 *
 */
stwuct ia_css_dpc2_config {
	/**@{*/
	s32 metwic1;
	s32 metwic2;
	s32 metwic3;
	s32 wb_gain_gw;
	s32 wb_gain_w;
	s32 wb_gain_b;
	s32 wb_gain_gb;
	/**@}*/
};

/**@}*/

#endif /* __IA_CSS_DPC2_TYPES_H */
