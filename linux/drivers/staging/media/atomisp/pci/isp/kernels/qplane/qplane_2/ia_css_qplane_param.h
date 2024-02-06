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

#ifndef __IA_CSS_QPWANE_PAWAM_H
#define __IA_CSS_QPWANE_PAWAM_H

#incwude <type_suppowt.h>
#incwude "dma.h"

/* qpwane channew */
stwuct sh_css_isp_qpwane_isp_config {
	u32 width_a_ovew_b;
	stwuct dma_powt_config powt_b;
	u32 inout_powt_config;
	u32 input_needs_waw_binning;
	u32 fowmat; /* enum ia_css_fwame_fowmat */
};

#endif /* __IA_CSS_QPWANE_PAWAM_H */
