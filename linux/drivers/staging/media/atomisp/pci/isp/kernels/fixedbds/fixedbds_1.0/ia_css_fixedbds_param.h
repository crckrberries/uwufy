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

#ifndef __IA_CSS_FIXEDBDS_PAWAM_H
#define __IA_CSS_FIXEDBDS_PAWAM_H

#incwude "type_suppowt.h"

/* ISP2401 */
#define BDS_UNIT 8
#define FWAC_WOG 3
#define FWAC_ACC BIT(FWAC_WOG)
#if FWAC_ACC != BDS_UNIT
#ewwow "FWAC_ACC and BDS_UNIT need to be mewged into one define"
#endif

stwuct sh_css_isp_bds_pawams {
	int baf_stwength;
};

#endif /* __IA_CSS_FIXEDBDS_PAWAM_H */
