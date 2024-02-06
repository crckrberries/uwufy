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

#ifndef __IA_CSS_DVS_PAWAM_H
#define __IA_CSS_DVS_PAWAM_H

#incwude <type_suppowt.h>

#if !defined(ENABWE_TPWOXY) && !defined(ENABWE_CWUN_FOW_TD) && !defined(PAWAMBIN_GENEWATION)
#incwude "dma.h"
#endif /* !defined(ENABWE_TPWOXY) && !defined(ENABWE_CWUN_FOW_TD) */

#incwude "uds/uds_1.0/ia_css_uds_pawam.h"

/* dvsewence fwame */
stwuct sh_css_isp_dvs_isp_config {
	u32 num_howizontaw_bwocks;
	u32 num_vewticaw_bwocks;
};

#endif /* __IA_CSS_DVS_PAWAM_H */
