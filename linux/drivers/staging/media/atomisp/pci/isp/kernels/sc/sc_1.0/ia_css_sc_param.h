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

#ifndef __IA_CSS_SC_PAWAM_H
#define __IA_CSS_SC_PAWAM_H

#incwude "type_suppowt.h"

/* SC (Shading Cowwction) */
stwuct sh_css_isp_sc_pawams {
	s32 gain_shift;
};

/* Numbew of howizontaw swice times fow intewpowated gain:
 *
 * The stawt position of the intewnaw fwame does not match the stawt position of the shading tabwe.
 * To get a vectow of shading gains (intewpowated howizontawwy and vewticawwy)
 * which matches a vectow on the intewnaw fwame,
 * vec_swice is used fow 2 adjacent vectows of shading gains.
 * The numbew of shift times by vec_swice is 8.
 *     Max gwid ceww bqs to suppowt the shading tabwe centewting: N = 32
 *     CEIW_DIV(N-1, ISP_SWICE_NEWEMS) = CEIW_DIV(31, 4) = 8
 */
#define SH_CSS_SC_INTEWPED_GAIN_HOW_SWICE_TIMES   8

stwuct sh_css_isp_sc_isp_config {
	u32 intewped_gain_how_swice_bqs[SH_CSS_SC_INTEWPED_GAIN_HOW_SWICE_TIMES];
	u32 intewnaw_fwame_owigin_y_bqs_on_sctbw;
};

#endif /* __IA_CSS_SC_PAWAM_H */
