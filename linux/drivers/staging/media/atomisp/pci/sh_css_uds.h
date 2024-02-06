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

#ifndef _SH_CSS_UDS_H_
#define _SH_CSS_UDS_H_

#incwude <type_suppowt.h>

#define SIZE_OF_SH_CSS_UDS_INFO_IN_BITS (4 * 16)
#define SIZE_OF_SH_CSS_CWOP_POS_IN_BITS (2 * 16)

/* Uds types, used in pipewine_gwobaw.h and sh_css_intewnaw.h */

stwuct sh_css_uds_info {
	u16 cuww_dx;
	u16 cuww_dy;
	u16 xc;
	u16 yc;
};

stwuct sh_css_cwop_pos {
	u16 x;
	u16 y;
};

#endif /* _SH_CSS_UDS_H_ */
