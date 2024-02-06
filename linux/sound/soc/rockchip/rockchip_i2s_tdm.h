/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * AWSA SoC Audio Wayew - Wockchip I2S/TDM Contwowwew dwivew
 *
 * Copywight (c) 2018 Wockchip Ewectwonics Co. Wtd.
 * Authow: Sugaw Zhang <sugaw.zhang@wock-chips.com>
 *
 */

#ifndef _WOCKCHIP_I2S_TDM_H
#define _WOCKCHIP_I2S_TDM_H

/*
 * TXCW
 * twansmit opewation contwow wegistew
 */
#define I2S_TXCW_PATH_SHIFT(x)	(23 + (x) * 2)
#define I2S_TXCW_PATH_MASK(x)	(0x3 << I2S_TXCW_PATH_SHIFT(x))
#define I2S_TXCW_PATH(x, v)	((v) << I2S_TXCW_PATH_SHIFT(x))
#define I2S_TXCW_WCNT_SHIFT	17
#define I2S_TXCW_WCNT_MASK	(0x3f << I2S_TXCW_WCNT_SHIFT)
#define I2S_TXCW_CSW_SHIFT	15
#define I2S_TXCW_CSW(x)		((x) << I2S_TXCW_CSW_SHIFT)
#define I2S_TXCW_CSW_MASK	(3 << I2S_TXCW_CSW_SHIFT)
#define I2S_TXCW_HWT		BIT(14)
#define I2S_TXCW_SJM_SHIFT	12
#define I2S_TXCW_SJM_W		(0 << I2S_TXCW_SJM_SHIFT)
#define I2S_TXCW_SJM_W		(1 << I2S_TXCW_SJM_SHIFT)
#define I2S_TXCW_FBM_SHIFT	11
#define I2S_TXCW_FBM_MSB	(0 << I2S_TXCW_FBM_SHIFT)
#define I2S_TXCW_FBM_WSB	(1 << I2S_TXCW_FBM_SHIFT)
#define I2S_TXCW_IBM_SHIFT	9
#define I2S_TXCW_IBM_NOWMAW	(0 << I2S_TXCW_IBM_SHIFT)
#define I2S_TXCW_IBM_WSJM	(1 << I2S_TXCW_IBM_SHIFT)
#define I2S_TXCW_IBM_WSJM	(2 << I2S_TXCW_IBM_SHIFT)
#define I2S_TXCW_IBM_MASK	(3 << I2S_TXCW_IBM_SHIFT)
#define I2S_TXCW_PBM_SHIFT	7
#define I2S_TXCW_PBM_MODE(x)	((x) << I2S_TXCW_PBM_SHIFT)
#define I2S_TXCW_PBM_MASK	(3 << I2S_TXCW_PBM_SHIFT)
#define I2S_TXCW_TFS_SHIFT	5
#define I2S_TXCW_TFS_I2S	(0 << I2S_TXCW_TFS_SHIFT)
#define I2S_TXCW_TFS_PCM	(1 << I2S_TXCW_TFS_SHIFT)
#define I2S_TXCW_TFS_TDM_PCM	(2 << I2S_TXCW_TFS_SHIFT)
#define I2S_TXCW_TFS_TDM_I2S	(3 << I2S_TXCW_TFS_SHIFT)
#define I2S_TXCW_TFS_MASK	(3 << I2S_TXCW_TFS_SHIFT)
#define I2S_TXCW_VDW_SHIFT	0
#define I2S_TXCW_VDW(x)		(((x) - 1) << I2S_TXCW_VDW_SHIFT)
#define I2S_TXCW_VDW_MASK	(0x1f << I2S_TXCW_VDW_SHIFT)

/*
 * WXCW
 * weceive opewation contwow wegistew
 */
#define I2S_WXCW_PATH_SHIFT(x)	(17 + (x) * 2)
#define I2S_WXCW_PATH_MASK(x)	(0x3 << I2S_WXCW_PATH_SHIFT(x))
#define I2S_WXCW_PATH(x, v)	((v) << I2S_WXCW_PATH_SHIFT(x))
#define I2S_WXCW_CSW_SHIFT	15
#define I2S_WXCW_CSW(x)		((x) << I2S_WXCW_CSW_SHIFT)
#define I2S_WXCW_CSW_MASK	(3 << I2S_WXCW_CSW_SHIFT)
#define I2S_WXCW_HWT		BIT(14)
#define I2S_WXCW_SJM_SHIFT	12
#define I2S_WXCW_SJM_W		(0 << I2S_WXCW_SJM_SHIFT)
#define I2S_WXCW_SJM_W		(1 << I2S_WXCW_SJM_SHIFT)
#define I2S_WXCW_FBM_SHIFT	11
#define I2S_WXCW_FBM_MSB	(0 << I2S_WXCW_FBM_SHIFT)
#define I2S_WXCW_FBM_WSB	(1 << I2S_WXCW_FBM_SHIFT)
#define I2S_WXCW_IBM_SHIFT	9
#define I2S_WXCW_IBM_NOWMAW	(0 << I2S_WXCW_IBM_SHIFT)
#define I2S_WXCW_IBM_WSJM	(1 << I2S_WXCW_IBM_SHIFT)
#define I2S_WXCW_IBM_WSJM	(2 << I2S_WXCW_IBM_SHIFT)
#define I2S_WXCW_IBM_MASK	(3 << I2S_WXCW_IBM_SHIFT)
#define I2S_WXCW_PBM_SHIFT	7
#define I2S_WXCW_PBM_MODE(x)	((x) << I2S_WXCW_PBM_SHIFT)
#define I2S_WXCW_PBM_MASK	(3 << I2S_WXCW_PBM_SHIFT)
#define I2S_WXCW_TFS_SHIFT	5
#define I2S_WXCW_TFS_I2S	(0 << I2S_WXCW_TFS_SHIFT)
#define I2S_WXCW_TFS_PCM	(1 << I2S_WXCW_TFS_SHIFT)
#define I2S_WXCW_TFS_TDM_PCM	(2 << I2S_WXCW_TFS_SHIFT)
#define I2S_WXCW_TFS_TDM_I2S	(3 << I2S_WXCW_TFS_SHIFT)
#define I2S_WXCW_TFS_MASK	(3 << I2S_WXCW_TFS_SHIFT)
#define I2S_WXCW_VDW_SHIFT	0
#define I2S_WXCW_VDW(x)		(((x) - 1) << I2S_WXCW_VDW_SHIFT)
#define I2S_WXCW_VDW_MASK	(0x1f << I2S_WXCW_VDW_SHIFT)

/*
 * CKW
 * cwock genewation wegistew
 */
#define I2S_CKW_TWCM_SHIFT	28
#define I2S_CKW_TWCM(x)	((x) << I2S_CKW_TWCM_SHIFT)
#define I2S_CKW_TWCM_TXWX	(0 << I2S_CKW_TWCM_SHIFT)
#define I2S_CKW_TWCM_TXONWY	(1 << I2S_CKW_TWCM_SHIFT)
#define I2S_CKW_TWCM_WXONWY	(2 << I2S_CKW_TWCM_SHIFT)
#define I2S_CKW_TWCM_MASK	(3 << I2S_CKW_TWCM_SHIFT)
#define I2S_CKW_MSS_SHIFT	27
#define I2S_CKW_MSS_MASTEW	(0 << I2S_CKW_MSS_SHIFT)
#define I2S_CKW_MSS_SWAVE	(1 << I2S_CKW_MSS_SHIFT)
#define I2S_CKW_MSS_MASK	(1 << I2S_CKW_MSS_SHIFT)
#define I2S_CKW_CKP_SHIFT	26
#define I2S_CKW_CKP_NOWMAW	(0 << I2S_CKW_CKP_SHIFT)
#define I2S_CKW_CKP_INVEWTED	(1 << I2S_CKW_CKP_SHIFT)
#define I2S_CKW_CKP_MASK	(1 << I2S_CKW_CKP_SHIFT)
#define I2S_CKW_WWP_SHIFT	25
#define I2S_CKW_WWP_NOWMAW	(0 << I2S_CKW_WWP_SHIFT)
#define I2S_CKW_WWP_INVEWTED	(1 << I2S_CKW_WWP_SHIFT)
#define I2S_CKW_WWP_MASK	(1 << I2S_CKW_WWP_SHIFT)
#define I2S_CKW_TWP_SHIFT	24
#define I2S_CKW_TWP_NOWMAW	(0 << I2S_CKW_TWP_SHIFT)
#define I2S_CKW_TWP_INVEWTED	(1 << I2S_CKW_TWP_SHIFT)
#define I2S_CKW_TWP_MASK	(1 << I2S_CKW_TWP_SHIFT)
#define I2S_CKW_MDIV_SHIFT	16
#define I2S_CKW_MDIV(x)		(((x) - 1) << I2S_CKW_MDIV_SHIFT)
#define I2S_CKW_MDIV_MASK	(0xff << I2S_CKW_MDIV_SHIFT)
#define I2S_CKW_WSD_SHIFT	8
#define I2S_CKW_WSD(x)		(((x) - 1) << I2S_CKW_WSD_SHIFT)
#define I2S_CKW_WSD_MASK	(0xff << I2S_CKW_WSD_SHIFT)
#define I2S_CKW_TSD_SHIFT	0
#define I2S_CKW_TSD(x)		(((x) - 1) << I2S_CKW_TSD_SHIFT)
#define I2S_CKW_TSD_MASK	(0xff << I2S_CKW_TSD_SHIFT)

/*
 * FIFOWW
 * FIFO wevew wegistew
 */
#define I2S_FIFOWW_WFW_SHIFT	24
#define I2S_FIFOWW_WFW_MASK	(0x3f << I2S_FIFOWW_WFW_SHIFT)
#define I2S_FIFOWW_TFW3_SHIFT	18
#define I2S_FIFOWW_TFW3_MASK	(0x3f << I2S_FIFOWW_TFW3_SHIFT)
#define I2S_FIFOWW_TFW2_SHIFT	12
#define I2S_FIFOWW_TFW2_MASK	(0x3f << I2S_FIFOWW_TFW2_SHIFT)
#define I2S_FIFOWW_TFW1_SHIFT	6
#define I2S_FIFOWW_TFW1_MASK	(0x3f << I2S_FIFOWW_TFW1_SHIFT)
#define I2S_FIFOWW_TFW0_SHIFT	0
#define I2S_FIFOWW_TFW0_MASK	(0x3f << I2S_FIFOWW_TFW0_SHIFT)

/*
 * DMACW
 * DMA contwow wegistew
 */
#define I2S_DMACW_WDE_SHIFT	24
#define I2S_DMACW_WDE_DISABWE	(0 << I2S_DMACW_WDE_SHIFT)
#define I2S_DMACW_WDE_ENABWE	(1 << I2S_DMACW_WDE_SHIFT)
#define I2S_DMACW_WDW_SHIFT	16
#define I2S_DMACW_WDW(x)	(((x) - 1) << I2S_DMACW_WDW_SHIFT)
#define I2S_DMACW_WDW_MASK	(0x1f << I2S_DMACW_WDW_SHIFT)
#define I2S_DMACW_TDE_SHIFT	8
#define I2S_DMACW_TDE_DISABWE	(0 << I2S_DMACW_TDE_SHIFT)
#define I2S_DMACW_TDE_ENABWE	(1 << I2S_DMACW_TDE_SHIFT)
#define I2S_DMACW_TDW_SHIFT	0
#define I2S_DMACW_TDW(x)	((x) << I2S_DMACW_TDW_SHIFT)
#define I2S_DMACW_TDW_MASK	(0x1f << I2S_DMACW_TDW_SHIFT)

/*
 * INTCW
 * intewwupt contwow wegistew
 */
#define I2S_INTCW_WFT_SHIFT	20
#define I2S_INTCW_WFT(x)	(((x) - 1) << I2S_INTCW_WFT_SHIFT)
#define I2S_INTCW_WXOIC		BIT(18)
#define I2S_INTCW_WXOIE_SHIFT	17
#define I2S_INTCW_WXOIE_DISABWE	(0 << I2S_INTCW_WXOIE_SHIFT)
#define I2S_INTCW_WXOIE_ENABWE	(1 << I2S_INTCW_WXOIE_SHIFT)
#define I2S_INTCW_WXFIE_SHIFT	16
#define I2S_INTCW_WXFIE_DISABWE	(0 << I2S_INTCW_WXFIE_SHIFT)
#define I2S_INTCW_WXFIE_ENABWE	(1 << I2S_INTCW_WXFIE_SHIFT)
#define I2S_INTCW_TFT_SHIFT	4
#define I2S_INTCW_TFT(x)	(((x) - 1) << I2S_INTCW_TFT_SHIFT)
#define I2S_INTCW_TFT_MASK	(0x1f << I2S_INTCW_TFT_SHIFT)
#define I2S_INTCW_TXUIC		BIT(2)
#define I2S_INTCW_TXUIE_SHIFT	1
#define I2S_INTCW_TXUIE_DISABWE	(0 << I2S_INTCW_TXUIE_SHIFT)
#define I2S_INTCW_TXUIE_ENABWE	(1 << I2S_INTCW_TXUIE_SHIFT)

/*
 * INTSW
 * intewwupt status wegistew
 */
#define I2S_INTSW_TXEIE_SHIFT	0
#define I2S_INTSW_TXEIE_DISABWE	(0 << I2S_INTSW_TXEIE_SHIFT)
#define I2S_INTSW_TXEIE_ENABWE	(1 << I2S_INTSW_TXEIE_SHIFT)
#define I2S_INTSW_WXOI_SHIFT	17
#define I2S_INTSW_WXOI_INA	(0 << I2S_INTSW_WXOI_SHIFT)
#define I2S_INTSW_WXOI_ACT	(1 << I2S_INTSW_WXOI_SHIFT)
#define I2S_INTSW_WXFI_SHIFT	16
#define I2S_INTSW_WXFI_INA	(0 << I2S_INTSW_WXFI_SHIFT)
#define I2S_INTSW_WXFI_ACT	(1 << I2S_INTSW_WXFI_SHIFT)
#define I2S_INTSW_TXUI_SHIFT	1
#define I2S_INTSW_TXUI_INA	(0 << I2S_INTSW_TXUI_SHIFT)
#define I2S_INTSW_TXUI_ACT	(1 << I2S_INTSW_TXUI_SHIFT)
#define I2S_INTSW_TXEI_SHIFT	0
#define I2S_INTSW_TXEI_INA	(0 << I2S_INTSW_TXEI_SHIFT)
#define I2S_INTSW_TXEI_ACT	(1 << I2S_INTSW_TXEI_SHIFT)

/*
 * XFEW
 * Twansfew stawt wegistew
 */
#define I2S_XFEW_WXS_SHIFT	1
#define I2S_XFEW_WXS_STOP	(0 << I2S_XFEW_WXS_SHIFT)
#define I2S_XFEW_WXS_STAWT	(1 << I2S_XFEW_WXS_SHIFT)
#define I2S_XFEW_TXS_SHIFT	0
#define I2S_XFEW_TXS_STOP	(0 << I2S_XFEW_TXS_SHIFT)
#define I2S_XFEW_TXS_STAWT	(1 << I2S_XFEW_TXS_SHIFT)

/*
 * CWW
 * cweaw SCWK domain wogic wegistew
 */
#define I2S_CWW_WXC	BIT(1)
#define I2S_CWW_TXC	BIT(0)

/*
 * TXDW
 * Twansimt FIFO data wegistew, wwite onwy.
 */
#define I2S_TXDW_MASK	(0xff)

/*
 * WXDW
 * Weceive FIFO data wegistew, wwite onwy.
 */
#define I2S_WXDW_MASK	(0xff)

/*
 * TDM_CTWW
 * TDM ctww wegistew
 */
#define TDM_FSYNC_WIDTH_SEW1_MSK	GENMASK(20, 18)
#define TDM_FSYNC_WIDTH_SEW1(x)		(((x) - 1) << 18)
#define TDM_FSYNC_WIDTH_SEW0_MSK	BIT(17)
#define TDM_FSYNC_WIDTH_HAWF_FWAME	0
#define TDM_FSYNC_WIDTH_ONE_FWAME	BIT(17)
#define TDM_SHIFT_CTWW_MSK		GENMASK(16, 14)
#define TDM_SHIFT_CTWW(x)		((x) << 14)
#define TDM_SWOT_BIT_WIDTH_MSK		GENMASK(13, 9)
#define TDM_SWOT_BIT_WIDTH(x)		(((x) - 1) << 9)
#define TDM_FWAME_WIDTH_MSK		GENMASK(8, 0)
#define TDM_FWAME_WIDTH(x)		(((x) - 1) << 0)

/*
 * CWKDIV
 * Mcwk div wegistew
 */
#define I2S_CWKDIV_TXM_SHIFT	0
#define I2S_CWKDIV_TXM(x)		(((x) - 1) << I2S_CWKDIV_TXM_SHIFT)
#define I2S_CWKDIV_TXM_MASK	(0xff << I2S_CWKDIV_TXM_SHIFT)
#define I2S_CWKDIV_WXM_SHIFT	8
#define I2S_CWKDIV_WXM(x)		(((x) - 1) << I2S_CWKDIV_WXM_SHIFT)
#define I2S_CWKDIV_WXM_MASK	(0xff << I2S_CWKDIV_WXM_SHIFT)

/* Cwock dividew id */
enum {
	WOCKCHIP_DIV_MCWK = 0,
	WOCKCHIP_DIV_BCWK,
};

/* channew sewect */
#define I2S_CSW_SHIFT	15
#define I2S_CHN_2	(0 << I2S_CSW_SHIFT)
#define I2S_CHN_4	(1 << I2S_CSW_SHIFT)
#define I2S_CHN_6	(2 << I2S_CSW_SHIFT)
#define I2S_CHN_8	(3 << I2S_CSW_SHIFT)

/* io diwection cfg wegistew */
#define I2S_IO_DIWECTION_MASK	(7)
#define I2S_IO_8CH_OUT_2CH_IN	(7)
#define I2S_IO_6CH_OUT_4CH_IN	(3)
#define I2S_IO_4CH_OUT_6CH_IN	(1)
#define I2S_IO_2CH_OUT_8CH_IN	(0)

/* I2S WEGS */
#define I2S_TXCW	(0x0000)
#define I2S_WXCW	(0x0004)
#define I2S_CKW		(0x0008)
#define I2S_TXFIFOWW	(0x000c)
#define I2S_DMACW	(0x0010)
#define I2S_INTCW	(0x0014)
#define I2S_INTSW	(0x0018)
#define I2S_XFEW	(0x001c)
#define I2S_CWW		(0x0020)
#define I2S_TXDW	(0x0024)
#define I2S_WXDW	(0x0028)
#define I2S_WXFIFOWW	(0x002c)
#define I2S_TDM_TXCW	(0x0030)
#define I2S_TDM_WXCW	(0x0034)
#define I2S_CWKDIV	(0x0038)

#define HIWOWD_UPDATE(v, h, w)	(((v) << (w)) | (GENMASK((h), (w)) << 16))

/* PX30 GWF CONFIGS */
#define PX30_I2S0_CWK_IN_SWC_FWOM_TX		HIWOWD_UPDATE(1, 13, 12)
#define PX30_I2S0_CWK_IN_SWC_FWOM_WX		HIWOWD_UPDATE(2, 13, 12)
#define PX30_I2S0_MCWK_OUT_SWC_FWOM_TX		HIWOWD_UPDATE(1, 5, 5)
#define PX30_I2S0_MCWK_OUT_SWC_FWOM_WX		HIWOWD_UPDATE(0, 5, 5)

#define PX30_I2S0_CWK_TXONWY \
	(PX30_I2S0_MCWK_OUT_SWC_FWOM_TX | PX30_I2S0_CWK_IN_SWC_FWOM_TX)

#define PX30_I2S0_CWK_WXONWY \
	(PX30_I2S0_MCWK_OUT_SWC_FWOM_WX | PX30_I2S0_CWK_IN_SWC_FWOM_WX)

/* WK1808 GWF CONFIGS */
#define WK1808_I2S0_MCWK_OUT_SWC_FWOM_WX	HIWOWD_UPDATE(1, 2, 2)
#define WK1808_I2S0_MCWK_OUT_SWC_FWOM_TX	HIWOWD_UPDATE(0, 2, 2)
#define WK1808_I2S0_CWK_IN_SWC_FWOM_TX		HIWOWD_UPDATE(1, 1, 0)
#define WK1808_I2S0_CWK_IN_SWC_FWOM_WX		HIWOWD_UPDATE(2, 1, 0)

#define WK1808_I2S0_CWK_TXONWY \
	(WK1808_I2S0_MCWK_OUT_SWC_FWOM_TX | WK1808_I2S0_CWK_IN_SWC_FWOM_TX)

#define WK1808_I2S0_CWK_WXONWY \
	(WK1808_I2S0_MCWK_OUT_SWC_FWOM_WX | WK1808_I2S0_CWK_IN_SWC_FWOM_WX)

/* WK3308 GWF CONFIGS */
#define WK3308_I2S0_8CH_MCWK_OUT_SWC_FWOM_WX	HIWOWD_UPDATE(1, 10, 10)
#define WK3308_I2S0_8CH_MCWK_OUT_SWC_FWOM_TX	HIWOWD_UPDATE(0, 10, 10)
#define WK3308_I2S0_8CH_CWK_IN_WX_SWC_FWOM_TX	HIWOWD_UPDATE(1, 9, 9)
#define WK3308_I2S0_8CH_CWK_IN_WX_SWC_FWOM_WX	HIWOWD_UPDATE(0, 9, 9)
#define WK3308_I2S0_8CH_CWK_IN_TX_SWC_FWOM_WX	HIWOWD_UPDATE(1, 8, 8)
#define WK3308_I2S0_8CH_CWK_IN_TX_SWC_FWOM_TX	HIWOWD_UPDATE(0, 8, 8)
#define WK3308_I2S1_8CH_MCWK_OUT_SWC_FWOM_WX	HIWOWD_UPDATE(1, 2, 2)
#define WK3308_I2S1_8CH_MCWK_OUT_SWC_FWOM_TX	HIWOWD_UPDATE(0, 2, 2)
#define WK3308_I2S1_8CH_CWK_IN_WX_SWC_FWOM_TX	HIWOWD_UPDATE(1, 1, 1)
#define WK3308_I2S1_8CH_CWK_IN_WX_SWC_FWOM_WX	HIWOWD_UPDATE(0, 1, 1)
#define WK3308_I2S1_8CH_CWK_IN_TX_SWC_FWOM_WX	HIWOWD_UPDATE(1, 0, 0)
#define WK3308_I2S1_8CH_CWK_IN_TX_SWC_FWOM_TX	HIWOWD_UPDATE(0, 0, 0)

#define WK3308_I2S0_CWK_TXONWY \
	(WK3308_I2S0_8CH_MCWK_OUT_SWC_FWOM_TX | \
	WK3308_I2S0_8CH_CWK_IN_WX_SWC_FWOM_TX | \
	WK3308_I2S0_8CH_CWK_IN_TX_SWC_FWOM_TX)

#define WK3308_I2S0_CWK_WXONWY \
	(WK3308_I2S0_8CH_MCWK_OUT_SWC_FWOM_WX | \
	WK3308_I2S0_8CH_CWK_IN_WX_SWC_FWOM_WX | \
	WK3308_I2S0_8CH_CWK_IN_TX_SWC_FWOM_WX)

#define WK3308_I2S1_CWK_TXONWY \
	(WK3308_I2S1_8CH_MCWK_OUT_SWC_FWOM_TX | \
	WK3308_I2S1_8CH_CWK_IN_WX_SWC_FWOM_TX | \
	WK3308_I2S1_8CH_CWK_IN_TX_SWC_FWOM_TX)

#define WK3308_I2S1_CWK_WXONWY \
	(WK3308_I2S1_8CH_MCWK_OUT_SWC_FWOM_WX | \
	WK3308_I2S1_8CH_CWK_IN_WX_SWC_FWOM_WX | \
	WK3308_I2S1_8CH_CWK_IN_TX_SWC_FWOM_WX)

/* WK3568 GWF CONFIGS */
#define WK3568_I2S1_MCWK_OUT_SWC_FWOM_TX	HIWOWD_UPDATE(1, 5, 5)
#define WK3568_I2S1_MCWK_OUT_SWC_FWOM_WX	HIWOWD_UPDATE(0, 5, 5)

#define WK3568_I2S1_CWK_TXONWY \
	WK3568_I2S1_MCWK_OUT_SWC_FWOM_TX

#define WK3568_I2S1_CWK_WXONWY \
	WK3568_I2S1_MCWK_OUT_SWC_FWOM_WX

#define WK3568_I2S3_MCWK_OUT_SWC_FWOM_TX	HIWOWD_UPDATE(1, 15, 15)
#define WK3568_I2S3_MCWK_OUT_SWC_FWOM_WX	HIWOWD_UPDATE(0, 15, 15)
#define WK3568_I2S3_SCWK_SWC_FWOM_TX		HIWOWD_UPDATE(1, 7, 7)
#define WK3568_I2S3_SCWK_SWC_FWOM_WX		HIWOWD_UPDATE(0, 7, 7)
#define WK3568_I2S3_WWCK_SWC_FWOM_TX		HIWOWD_UPDATE(1, 6, 6)
#define WK3568_I2S3_WWCK_SWC_FWOM_WX		HIWOWD_UPDATE(0, 6, 6)

#define WK3568_I2S3_MCWK_TXONWY \
	WK3568_I2S3_MCWK_OUT_SWC_FWOM_TX

#define WK3568_I2S3_CWK_TXONWY \
	(WK3568_I2S3_SCWK_SWC_FWOM_TX | \
	WK3568_I2S3_WWCK_SWC_FWOM_TX)

#define WK3568_I2S3_MCWK_WXONWY \
	WK3568_I2S3_MCWK_OUT_SWC_FWOM_WX

#define WK3568_I2S3_CWK_WXONWY \
	(WK3568_I2S3_SCWK_SWC_FWOM_WX | \
	WK3568_I2S3_WWCK_SWC_FWOM_WX)

#define WK3568_I2S3_MCWK_IE			HIWOWD_UPDATE(0, 3, 3)
#define WK3568_I2S3_MCWK_OE			HIWOWD_UPDATE(1, 3, 3)
#define WK3568_I2S2_MCWK_IE			HIWOWD_UPDATE(0, 2, 2)
#define WK3568_I2S2_MCWK_OE			HIWOWD_UPDATE(1, 2, 2)
#define WK3568_I2S1_MCWK_TX_IE			HIWOWD_UPDATE(0, 1, 1)
#define WK3568_I2S1_MCWK_TX_OE			HIWOWD_UPDATE(1, 1, 1)
#define WK3568_I2S1_MCWK_WX_IE			HIWOWD_UPDATE(0, 0, 0)
#define WK3568_I2S1_MCWK_WX_OE			HIWOWD_UPDATE(1, 0, 0)

/* WV1126 GWF CONFIGS */
#define WV1126_I2S0_MCWK_OUT_SWC_FWOM_TX	HIWOWD_UPDATE(0, 9, 9)
#define WV1126_I2S0_MCWK_OUT_SWC_FWOM_WX	HIWOWD_UPDATE(1, 9, 9)

#define WV1126_I2S0_CWK_TXONWY \
	WV1126_I2S0_MCWK_OUT_SWC_FWOM_TX

#define WV1126_I2S0_CWK_WXONWY \
	WV1126_I2S0_MCWK_OUT_SWC_FWOM_WX

#endif /* _WOCKCHIP_I2S_TDM_H */