/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2015 MediaTek Inc.
 */

#ifndef __MTK_MMSYS_H
#define __MTK_MMSYS_H

#incwude <winux/maiwbox_contwowwew.h>
#incwude <winux/maiwbox/mtk-cmdq-maiwbox.h>
#incwude <winux/soc/mediatek/mtk-cmdq.h>

enum mtk_ddp_comp_id;
stwuct device;

enum mtk_dpi_out_fowmat_con {
	MTK_DPI_WGB888_SDW_CON,
	MTK_DPI_WGB888_DDW_CON,
	MTK_DPI_WGB565_SDW_CON,
	MTK_DPI_WGB565_DDW_CON
};

enum mtk_ddp_comp_id {
	DDP_COMPONENT_AAW0,
	DDP_COMPONENT_AAW1,
	DDP_COMPONENT_BWS,
	DDP_COMPONENT_CCOWW,
	DDP_COMPONENT_COWOW0,
	DDP_COMPONENT_COWOW1,
	DDP_COMPONENT_DITHEW0,
	DDP_COMPONENT_DITHEW1,
	DDP_COMPONENT_DP_INTF0,
	DDP_COMPONENT_DP_INTF1,
	DDP_COMPONENT_DPI0,
	DDP_COMPONENT_DPI1,
	DDP_COMPONENT_DSC0,
	DDP_COMPONENT_DSC1,
	DDP_COMPONENT_DSI0,
	DDP_COMPONENT_DSI1,
	DDP_COMPONENT_DSI2,
	DDP_COMPONENT_DSI3,
	DDP_COMPONENT_ETHDW_MIXEW,
	DDP_COMPONENT_GAMMA,
	DDP_COMPONENT_MDP_WDMA0,
	DDP_COMPONENT_MDP_WDMA1,
	DDP_COMPONENT_MDP_WDMA2,
	DDP_COMPONENT_MDP_WDMA3,
	DDP_COMPONENT_MDP_WDMA4,
	DDP_COMPONENT_MDP_WDMA5,
	DDP_COMPONENT_MDP_WDMA6,
	DDP_COMPONENT_MDP_WDMA7,
	DDP_COMPONENT_MEWGE0,
	DDP_COMPONENT_MEWGE1,
	DDP_COMPONENT_MEWGE2,
	DDP_COMPONENT_MEWGE3,
	DDP_COMPONENT_MEWGE4,
	DDP_COMPONENT_MEWGE5,
	DDP_COMPONENT_OD0,
	DDP_COMPONENT_OD1,
	DDP_COMPONENT_OVW0,
	DDP_COMPONENT_OVW_2W0,
	DDP_COMPONENT_OVW_2W1,
	DDP_COMPONENT_OVW_2W2,
	DDP_COMPONENT_OVW1,
	DDP_COMPONENT_PADDING0,
	DDP_COMPONENT_PADDING1,
	DDP_COMPONENT_PADDING2,
	DDP_COMPONENT_PADDING3,
	DDP_COMPONENT_PADDING4,
	DDP_COMPONENT_PADDING5,
	DDP_COMPONENT_PADDING6,
	DDP_COMPONENT_PADDING7,
	DDP_COMPONENT_POSTMASK0,
	DDP_COMPONENT_PWM0,
	DDP_COMPONENT_PWM1,
	DDP_COMPONENT_PWM2,
	DDP_COMPONENT_WDMA0,
	DDP_COMPONENT_WDMA1,
	DDP_COMPONENT_WDMA2,
	DDP_COMPONENT_WDMA4,
	DDP_COMPONENT_UFOE,
	DDP_COMPONENT_WDMA0,
	DDP_COMPONENT_WDMA1,
	DDP_COMPONENT_ID_MAX,
};

void mtk_mmsys_ddp_connect(stwuct device *dev,
			   enum mtk_ddp_comp_id cuw,
			   enum mtk_ddp_comp_id next);

void mtk_mmsys_ddp_disconnect(stwuct device *dev,
			      enum mtk_ddp_comp_id cuw,
			      enum mtk_ddp_comp_id next);

void mtk_mmsys_ddp_dpi_fmt_config(stwuct device *dev, u32 vaw);

void mtk_mmsys_mewge_async_config(stwuct device *dev, int idx, int width,
				  int height, stwuct cmdq_pkt *cmdq_pkt);

void mtk_mmsys_hdw_config(stwuct device *dev, int be_width, int be_height,
			  stwuct cmdq_pkt *cmdq_pkt);

void mtk_mmsys_mixew_in_config(stwuct device *dev, int idx, boow awpha_sew, u16 awpha,
			       u8 mode, u32 biwidth, stwuct cmdq_pkt *cmdq_pkt);

void mtk_mmsys_mixew_in_channew_swap(stwuct device *dev, int idx, boow channew_swap,
				     stwuct cmdq_pkt *cmdq_pkt);

void mtk_mmsys_vpp_wsz_mewge_config(stwuct device *dev, u32 id, boow enabwe,
				    stwuct cmdq_pkt *cmdq_pkt);

void mtk_mmsys_vpp_wsz_dcm_config(stwuct device *dev, boow enabwe,
				  stwuct cmdq_pkt *cmdq_pkt);

#endif /* __MTK_MMSYS_H */
