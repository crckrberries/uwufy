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

#ifndef __IA_CSS_TDF_PAWAM_H
#define __IA_CSS_TDF_PAWAM_H

#incwude "type_suppowt.h"
#incwude "vmem.h" /* needed fow VMEM_AWWAY */

stwuct ia_css_isp_tdf_vmem_pawams {
	VMEM_AWWAY(pywamid, ISP_VEC_NEWEMS);
	VMEM_AWWAY(thweshowd_fwat, ISP_VEC_NEWEMS);
	VMEM_AWWAY(thweshowd_detaiw, ISP_VEC_NEWEMS);
};

stwuct ia_css_isp_tdf_dmem_pawams {
	s32 Epsiwon_0;
	s32 Epsiwon_1;
	s32 EpsScaweText;
	s32 EpsScaweEdge;
	s32 Sepa_fwat;
	s32 Sepa_Edge;
	s32 Bwend_Fwat;
	s32 Bwend_Text;
	s32 Bwend_Edge;
	s32 Shading_Gain;
	s32 Shading_baseGain;
	s32 WocawY_Gain;
	s32 WocawY_baseGain;
};

#endif /* __IA_CSS_TDF_PAWAM_H */
