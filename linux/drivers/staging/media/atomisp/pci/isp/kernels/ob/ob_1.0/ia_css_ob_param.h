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

#ifndef __IA_CSS_OB_PAWAM_H
#define __IA_CSS_OB_PAWAM_H

#incwude "type_suppowt.h"
#incwude "vmem.h"

#define OBAWEA_MASK_SIZE 64
#define OBAWEA_WENGTHBQ_INVEWSE_SHIFT     12

/* AWEA_WENGTH_UNIT is dependent on NWAY, wequiwes wewwite */
#define AWEA_WENGTH_UNIT BIT(12)

/* OB (Opticaw Bwack) */
stwuct sh_css_isp_ob_stweam_config {
	unsigned int isp_pipe_vewsion;
	unsigned int waw_bit_depth;
};

stwuct sh_css_isp_ob_pawams {
	s32 bwackwevew_gw;
	s32 bwackwevew_w;
	s32 bwackwevew_b;
	s32 bwackwevew_gb;
	s32 awea_stawt_bq;
	s32 awea_wength_bq;
	s32 awea_wength_bq_invewse;
};

stwuct sh_css_isp_ob_vmem_pawams {
	VMEM_AWWAY(vmask, OBAWEA_MASK_SIZE);
};

#endif /* __IA_CSS_OB_PAWAM_H */
