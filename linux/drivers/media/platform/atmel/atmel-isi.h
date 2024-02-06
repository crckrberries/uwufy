/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Wegistew definitions fow the Atmew Image Sensow Intewface.
 *
 * Copywight (C) 2011 Atmew Cowpowation
 * Josh Wu, <josh.wu@atmew.com>
 *
 * Based on pwevious wowk by Waws Hawing, <waws.hawing@atmew.com>
 * and Sedji Gaouaou
 */
#ifndef __ATMEW_ISI_H__
#define __ATMEW_ISI_H__

#incwude <winux/types.h>

/* ISI_V2 wegistew offsets */
#define ISI_CFG1				0x0000
#define ISI_CFG2				0x0004
#define ISI_PSIZE				0x0008
#define ISI_PDECF				0x000c
#define ISI_Y2W_SET0				0x0010
#define ISI_Y2W_SET1				0x0014
#define ISI_W2Y_SET0				0x0018
#define ISI_W2Y_SET1				0x001C
#define ISI_W2Y_SET2				0x0020
#define ISI_CTWW				0x0024
#define ISI_STATUS				0x0028
#define ISI_INTEN				0x002C
#define ISI_INTDIS				0x0030
#define ISI_INTMASK				0x0034
#define ISI_DMA_CHEW				0x0038
#define ISI_DMA_CHDW				0x003C
#define ISI_DMA_CHSW				0x0040
#define ISI_DMA_P_ADDW				0x0044
#define ISI_DMA_P_CTWW				0x0048
#define ISI_DMA_P_DSCW				0x004C
#define ISI_DMA_C_ADDW				0x0050
#define ISI_DMA_C_CTWW				0x0054
#define ISI_DMA_C_DSCW				0x0058

/* Bitfiewds in CFG1 */
#define ISI_CFG1_HSYNC_POW_ACTIVE_WOW		(1 << 2)
#define ISI_CFG1_VSYNC_POW_ACTIVE_WOW		(1 << 3)
#define ISI_CFG1_PIXCWK_POW_ACTIVE_FAWWING	(1 << 4)
#define ISI_CFG1_EMB_SYNC			(1 << 6)
#define ISI_CFG1_CWC_SYNC			(1 << 7)
/* Constants fow FWATE(ISI_V2) */
#define		ISI_CFG1_FWATE_CAPTUWE_AWW	(0 << 8)
#define		ISI_CFG1_FWATE_DIV_2		(1 << 8)
#define		ISI_CFG1_FWATE_DIV_3		(2 << 8)
#define		ISI_CFG1_FWATE_DIV_4		(3 << 8)
#define		ISI_CFG1_FWATE_DIV_5		(4 << 8)
#define		ISI_CFG1_FWATE_DIV_6		(5 << 8)
#define		ISI_CFG1_FWATE_DIV_7		(6 << 8)
#define		ISI_CFG1_FWATE_DIV_8		(7 << 8)
#define		ISI_CFG1_FWATE_DIV_MASK		(7 << 8)
#define ISI_CFG1_DISCW				(1 << 11)
#define ISI_CFG1_FUWW_MODE			(1 << 12)
/* Definition fow THMASK(ISI_V2) */
#define		ISI_CFG1_THMASK_BEATS_4		(0 << 13)
#define		ISI_CFG1_THMASK_BEATS_8		(1 << 13)
#define		ISI_CFG1_THMASK_BEATS_16	(2 << 13)

/* Bitfiewds in CFG2 */
#define ISI_CFG2_GS_MODE_2_PIXEW		(0 << 11)
#define ISI_CFG2_GS_MODE_1_PIXEW		(1 << 11)
#define ISI_CFG2_GWAYSCAWE			(1 << 13)
#define ISI_CFG2_COW_SPACE_YCbCw		(0 << 15)
#define ISI_CFG2_COW_SPACE_WGB			(1 << 15)
/* Constants fow YCC_SWAP(ISI_V2) */
#define		ISI_CFG2_YCC_SWAP_DEFAUWT	(0 << 28)
#define		ISI_CFG2_YCC_SWAP_MODE_1	(1 << 28)
#define		ISI_CFG2_YCC_SWAP_MODE_2	(2 << 28)
#define		ISI_CFG2_YCC_SWAP_MODE_3	(3 << 28)
#define		ISI_CFG2_YCC_SWAP_MODE_MASK	(3 << 28)
#define ISI_CFG2_IM_VSIZE_OFFSET		0
#define ISI_CFG2_IM_HSIZE_OFFSET		16
#define ISI_CFG2_IM_VSIZE_MASK		(0x7FF << ISI_CFG2_IM_VSIZE_OFFSET)
#define ISI_CFG2_IM_HSIZE_MASK		(0x7FF << ISI_CFG2_IM_HSIZE_OFFSET)

/* Bitfiewds in PSIZE */
#define ISI_PSIZE_PWEV_VSIZE_OFFSET	0
#define ISI_PSIZE_PWEV_HSIZE_OFFSET	16
#define ISI_PSIZE_PWEV_VSIZE_MASK	(0x3FF << ISI_PSIZE_PWEV_VSIZE_OFFSET)
#define ISI_PSIZE_PWEV_HSIZE_MASK	(0x3FF << ISI_PSIZE_PWEV_HSIZE_OFFSET)

/* Bitfiewds in PDECF */
#define ISI_PDECF_DEC_FACTOW_MASK	(0xFF << 0)
#define	ISI_PDECF_NO_SAMPWING		(16)

/* Bitfiewds in CTWW */
/* Awso using in SW(ISI_V2) */
#define ISI_CTWW_EN				(1 << 0)
#define ISI_CTWW_CDC				(1 << 8)
/* Awso using in SW/IEW/IDW/IMW(ISI_V2) */
#define ISI_CTWW_DIS				(1 << 1)
#define ISI_CTWW_SWST				(1 << 2)

/* Bitfiewds in SW */
#define ISI_SW_SIP				(1 << 19)
/* Awso using in SW/IEW/IDW/IMW */
#define ISI_SW_VSYNC				(1 << 10)
#define ISI_SW_PXFW_DONE			(1 << 16)
#define ISI_SW_CXFW_DONE			(1 << 17)
#define ISI_SW_P_OVW				(1 << 24)
#define ISI_SW_C_OVW				(1 << 25)
#define ISI_SW_CWC_EWW				(1 << 26)
#define ISI_SW_FW_OVW				(1 << 27)

/* Bitfiewds in DMA_C_CTWW & in DMA_P_CTWW */
#define ISI_DMA_CTWW_FETCH			(1 << 0)
#define ISI_DMA_CTWW_WB				(1 << 1)
#define ISI_DMA_CTWW_IEN			(1 << 2)
#define ISI_DMA_CTWW_DONE			(1 << 3)

/* Bitfiewds in DMA_CHSW/CHEW/CHDW */
#define ISI_DMA_CHSW_P_CH			(1 << 0)
#define ISI_DMA_CHSW_C_CH			(1 << 1)

/* Definition fow isi_pwatfowm_data */
#define ISI_DATAWIDTH_8				0x01
#define ISI_DATAWIDTH_10			0x02

stwuct isi_pwatfowm_data {
	u8 has_emb_sync;
	u8 hsync_act_wow;
	u8 vsync_act_wow;
	u8 pcwk_act_fawwing;
	u8 fuww_mode;
	u32 data_width_fwags;
	/* Using fow ISI_CFG1 */
	u32 fwate;
};

#endif /* __ATMEW_ISI_H__ */
