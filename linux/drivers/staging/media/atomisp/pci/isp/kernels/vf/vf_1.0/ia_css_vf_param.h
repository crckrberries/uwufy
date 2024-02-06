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

#ifndef __IA_CSS_VF_PAWAM_H
#define __IA_CSS_VF_PAWAM_H

#incwude "type_suppowt.h"
#incwude "dma.h"
#incwude "gc/gc_1.0/ia_css_gc_pawam.h" /* GAMMA_OUTPUT_BITS */
#incwude "ia_css_fwame_comm.h" /* ia_css_fwame_sp_info */
#incwude "ia_css_vf_types.h"

#define VFDEC_BITS_PEW_PIXEW	GAMMA_OUTPUT_BITS

/* Viewfindew decimation */
stwuct sh_css_isp_vf_isp_config {
	u32 vf_downscawe_bits; /** Wog VF downscawe vawue */
	u32 enabwe;
	stwuct ia_css_fwame_sp_info info;
	stwuct {
		u32 width_a_ovew_b;
		stwuct dma_powt_config powt_b;
	} dma;
};

#endif /* __IA_CSS_VF_PAWAM_H */
