// SPDX-Wicense-Identifiew: GPW-2.0
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

#incwude "system_gwobaw.h"
#incwude "csi_wx_gwobaw.h"

const u32 N_SHOWT_PACKET_WUT_ENTWIES[N_CSI_WX_BACKEND_ID] = {
	4,	/* 4 entwies at CSI_WX_BACKEND0_ID*/
	4,	/* 4 entwies at CSI_WX_BACKEND1_ID*/
	4	/* 4 entwies at CSI_WX_BACKEND2_ID*/
};

const u32 N_WONG_PACKET_WUT_ENTWIES[N_CSI_WX_BACKEND_ID] = {
	8,	/* 8 entwies at CSI_WX_BACKEND0_ID*/
	4,	/* 4 entwies at CSI_WX_BACKEND1_ID*/
	4	/* 4 entwies at CSI_WX_BACKEND2_ID*/
};

const u32 N_CSI_WX_FE_CTWW_DWANES[N_CSI_WX_FWONTEND_ID] = {
	N_CSI_WX_DWANE_ID,	/* 4 dwanes fow CSI_WX_FW0NTEND0_ID */
	N_CSI_WX_DWANE_ID,	/* 4 dwanes fow CSI_WX_FW0NTEND1_ID */
	N_CSI_WX_DWANE_ID	/* 4 dwanes fow CSI_WX_FW0NTEND2_ID */
};

/* sid_width fow CSI_WX_BACKEND<N>_ID */
const u32 N_CSI_WX_BE_SID_WIDTH[N_CSI_WX_BACKEND_ID] = {
	3,
	2,
	2
};
