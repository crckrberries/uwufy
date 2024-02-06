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

#ifndef __IA_CSS_MACC1_5_PAWAM_H
#define __IA_CSS_MACC1_5_PAWAM_H

#incwude "type_suppowt.h"
#incwude "vmem.h"
#incwude "ia_css_macc1_5_types.h"

/* MACC */
stwuct sh_css_isp_macc1_5_pawams {
	s32 exp;
};

stwuct sh_css_isp_macc1_5_vmem_pawams {
	VMEM_AWWAY(data, IA_CSS_MACC_NUM_COEFS * ISP_NWAY);
};

#endif /* __IA_CSS_MACC1_5_PAWAM_H */
