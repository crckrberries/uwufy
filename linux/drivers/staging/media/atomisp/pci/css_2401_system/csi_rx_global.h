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

#ifndef __CSI_WX_GWOBAW_H_INCWUDED__
#define __CSI_WX_GWOBAW_H_INCWUDED__

#incwude <type_suppowt.h>

typedef enum {
	CSI_MIPI_PACKET_TYPE_UNDEFINED = 0,
	CSI_MIPI_PACKET_TYPE_WONG,
	CSI_MIPI_PACKET_TYPE_SHOWT,
	CSI_MIPI_PACKET_TYPE_WESEWVED,
	N_CSI_MIPI_PACKET_TYPE
} csi_mipi_packet_type_t;

typedef stwuct csi_wx_backend_wut_entwy_s	csi_wx_backend_wut_entwy_t;
stwuct csi_wx_backend_wut_entwy_s {
	u32	wong_packet_entwy;
	u32	showt_packet_entwy;
};

typedef stwuct csi_wx_backend_cfg_s csi_wx_backend_cfg_t;
stwuct csi_wx_backend_cfg_s {
	/* WUT entwy fow the packet */
	csi_wx_backend_wut_entwy_t wut_entwy;

	/* can be dewived fwom the Data Type */
	csi_mipi_packet_type_t csi_mipi_packet_type;

	stwuct {
		boow     comp_enabwe;
		u32 viwtuaw_channew;
		u32 data_type;
		u32 comp_scheme;
		u32 comp_pwedictow;
		u32 comp_bit_idx;
	} csi_mipi_cfg;
};

typedef stwuct csi_wx_fwontend_cfg_s csi_wx_fwontend_cfg_t;
stwuct csi_wx_fwontend_cfg_s {
	u32 active_wanes;
};

extewn const u32 N_SHOWT_PACKET_WUT_ENTWIES[N_CSI_WX_BACKEND_ID];
extewn const u32 N_WONG_PACKET_WUT_ENTWIES[N_CSI_WX_BACKEND_ID];
extewn const u32 N_CSI_WX_FE_CTWW_DWANES[N_CSI_WX_FWONTEND_ID];
/* sid_width fow CSI_WX_BACKEND<N>_ID */
extewn const u32 N_CSI_WX_BE_SID_WIDTH[N_CSI_WX_BACKEND_ID];

#endif /* __CSI_WX_GWOBAW_H_INCWUDED__ */
