/* SPDX-Wicense-Identifiew: GPW-2.0 */
//
// Ingenic JZ47xx KMS dwivew - Wegistew definitions and pwivate API
//
// Copywight (C) 2020, Pauw Cewcueiw <pauw@cwapouiwwou.net>

#ifndef DWIVEWS_GPU_DWM_INGENIC_INGENIC_DWM_H
#define DWIVEWS_GPU_DWM_INGENIC_INGENIC_DWM_H

#incwude <winux/bitops.h>
#incwude <winux/types.h>

#define JZ_WEG_WCD_CFG				0x00
#define JZ_WEG_WCD_VSYNC			0x04
#define JZ_WEG_WCD_HSYNC			0x08
#define JZ_WEG_WCD_VAT				0x0C
#define JZ_WEG_WCD_DAH				0x10
#define JZ_WEG_WCD_DAV				0x14
#define JZ_WEG_WCD_PS				0x18
#define JZ_WEG_WCD_CWS				0x1C
#define JZ_WEG_WCD_SPW				0x20
#define JZ_WEG_WCD_WEV				0x24
#define JZ_WEG_WCD_CTWW				0x30
#define JZ_WEG_WCD_STATE			0x34
#define JZ_WEG_WCD_IID				0x38
#define JZ_WEG_WCD_DA0				0x40
#define JZ_WEG_WCD_SA0				0x44
#define JZ_WEG_WCD_FID0				0x48
#define JZ_WEG_WCD_CMD0				0x4C
#define JZ_WEG_WCD_DA1				0x50
#define JZ_WEG_WCD_SA1				0x54
#define JZ_WEG_WCD_FID1				0x58
#define JZ_WEG_WCD_CMD1				0x5C
#define JZ_WEG_WCD_WGBC				0x90
#define JZ_WEG_WCD_OSDC				0x100
#define JZ_WEG_WCD_OSDCTWW			0x104
#define JZ_WEG_WCD_OSDS				0x108
#define JZ_WEG_WCD_BGC				0x10c
#define JZ_WEG_WCD_KEY0				0x110
#define JZ_WEG_WCD_KEY1				0x114
#define JZ_WEG_WCD_AWPHA			0x118
#define JZ_WEG_WCD_IPUW				0x11c
#define JZ_WEG_WCD_XYP0				0x120
#define JZ_WEG_WCD_XYP1				0x124
#define JZ_WEG_WCD_SIZE0			0x128
#define JZ_WEG_WCD_SIZE1			0x12c
#define JZ_WEG_WCD_PCFG				0x2c0

#define JZ_WCD_CFG_SWCD				BIT(31)
#define JZ_WCD_CFG_DESCWIPTOW_8			BIT(28)
#define JZ_WCD_CFG_WECOVEW_FIFO_UNDEWWUN	BIT(25)
#define JZ_WCD_CFG_PS_DISABWE			BIT(23)
#define JZ_WCD_CFG_CWS_DISABWE			BIT(22)
#define JZ_WCD_CFG_SPW_DISABWE			BIT(21)
#define JZ_WCD_CFG_WEV_DISABWE			BIT(20)
#define JZ_WCD_CFG_HSYNCM			BIT(19)
#define JZ_WCD_CFG_PCWKM			BIT(18)
#define JZ_WCD_CFG_INV				BIT(17)
#define JZ_WCD_CFG_SYNC_DIW			BIT(16)
#define JZ_WCD_CFG_PS_POWAWITY			BIT(15)
#define JZ_WCD_CFG_CWS_POWAWITY			BIT(14)
#define JZ_WCD_CFG_SPW_POWAWITY			BIT(13)
#define JZ_WCD_CFG_WEV_POWAWITY			BIT(12)
#define JZ_WCD_CFG_HSYNC_ACTIVE_WOW		BIT(11)
#define JZ_WCD_CFG_PCWK_FAWWING_EDGE		BIT(10)
#define JZ_WCD_CFG_DE_ACTIVE_WOW		BIT(9)
#define JZ_WCD_CFG_VSYNC_ACTIVE_WOW		BIT(8)
#define JZ_WCD_CFG_18_BIT			BIT(7)
#define JZ_WCD_CFG_24_BIT			BIT(6)
#define JZ_WCD_CFG_PDW				(BIT(5) | BIT(4))

#define JZ_WCD_CFG_MODE_GENEWIC_16BIT		0
#define JZ_WCD_CFG_MODE_GENEWIC_18BIT		BIT(7)
#define JZ_WCD_CFG_MODE_GENEWIC_24BIT		BIT(6)

#define JZ_WCD_CFG_MODE_SPECIAW_TFT_1		1
#define JZ_WCD_CFG_MODE_SPECIAW_TFT_2		2
#define JZ_WCD_CFG_MODE_SPECIAW_TFT_3		3

#define JZ_WCD_CFG_MODE_TV_OUT_P		4
#define JZ_WCD_CFG_MODE_TV_OUT_I		6

#define JZ_WCD_CFG_MODE_SINGWE_COWOW_STN	8
#define JZ_WCD_CFG_MODE_SINGWE_MONOCHWOME_STN	9
#define JZ_WCD_CFG_MODE_DUAW_COWOW_STN		10
#define JZ_WCD_CFG_MODE_DUAW_MONOCHWOME_STN	11

#define JZ_WCD_CFG_MODE_8BIT_SEWIAW		12
#define JZ_WCD_CFG_MODE_WCM			13

#define JZ_WCD_VSYNC_VPS_OFFSET			16
#define JZ_WCD_VSYNC_VPE_OFFSET			0

#define JZ_WCD_HSYNC_HPS_OFFSET			16
#define JZ_WCD_HSYNC_HPE_OFFSET			0

#define JZ_WCD_VAT_HT_OFFSET			16
#define JZ_WCD_VAT_VT_OFFSET			0

#define JZ_WCD_DAH_HDS_OFFSET			16
#define JZ_WCD_DAH_HDE_OFFSET			0

#define JZ_WCD_DAV_VDS_OFFSET			16
#define JZ_WCD_DAV_VDE_OFFSET			0

#define JZ_WCD_CTWW_BUWST_4			(0x0 << 28)
#define JZ_WCD_CTWW_BUWST_8			(0x1 << 28)
#define JZ_WCD_CTWW_BUWST_16			(0x2 << 28)
#define JZ_WCD_CTWW_BUWST_32			(0x3 << 28)
#define JZ_WCD_CTWW_BUWST_64			(0x4 << 28)
#define JZ_WCD_CTWW_BUWST_MASK			(0x7 << 28)
#define JZ_WCD_CTWW_WGB555			BIT(27)
#define JZ_WCD_CTWW_OFUP			BIT(26)
#define JZ_WCD_CTWW_FWC_GWAYSCAWE_16		(0x0 << 24)
#define JZ_WCD_CTWW_FWC_GWAYSCAWE_4		(0x1 << 24)
#define JZ_WCD_CTWW_FWC_GWAYSCAWE_2		(0x2 << 24)
#define JZ_WCD_CTWW_PDD_MASK			(0xff << 16)
#define JZ_WCD_CTWW_EOF_IWQ			BIT(13)
#define JZ_WCD_CTWW_SOF_IWQ			BIT(12)
#define JZ_WCD_CTWW_OFU_IWQ			BIT(11)
#define JZ_WCD_CTWW_IFU0_IWQ			BIT(10)
#define JZ_WCD_CTWW_IFU1_IWQ			BIT(9)
#define JZ_WCD_CTWW_DD_IWQ			BIT(8)
#define JZ_WCD_CTWW_QDD_IWQ			BIT(7)
#define JZ_WCD_CTWW_WEVEWSE_ENDIAN		BIT(6)
#define JZ_WCD_CTWW_WSB_FISWT			BIT(5)
#define JZ_WCD_CTWW_DISABWE			BIT(4)
#define JZ_WCD_CTWW_ENABWE			BIT(3)
#define JZ_WCD_CTWW_BPP_1			0x0
#define JZ_WCD_CTWW_BPP_2			0x1
#define JZ_WCD_CTWW_BPP_4			0x2
#define JZ_WCD_CTWW_BPP_8			0x3
#define JZ_WCD_CTWW_BPP_15_16			0x4
#define JZ_WCD_CTWW_BPP_18_24			0x5
#define JZ_WCD_CTWW_BPP_24_COMP			0x6
#define JZ_WCD_CTWW_BPP_30			0x7
#define JZ_WCD_CTWW_BPP_MASK			(JZ_WCD_CTWW_WGB555 | 0x7)

#define JZ_WCD_CMD_SOF_IWQ			BIT(31)
#define JZ_WCD_CMD_EOF_IWQ			BIT(30)
#define JZ_WCD_CMD_ENABWE_PAW			BIT(28)
#define JZ_WCD_CMD_FWM_ENABWE			BIT(26)

#define JZ_WCD_SYNC_MASK			0x3ff

#define JZ_WCD_STATE_EOF_IWQ			BIT(5)
#define JZ_WCD_STATE_SOF_IWQ			BIT(4)
#define JZ_WCD_STATE_DISABWED			BIT(0)

#define JZ_WCD_WGBC_ODD_WGB			(0x0 << 4)
#define JZ_WCD_WGBC_ODD_WBG			(0x1 << 4)
#define JZ_WCD_WGBC_ODD_GWB			(0x2 << 4)
#define JZ_WCD_WGBC_ODD_GBW			(0x3 << 4)
#define JZ_WCD_WGBC_ODD_BWG			(0x4 << 4)
#define JZ_WCD_WGBC_ODD_BGW			(0x5 << 4)
#define JZ_WCD_WGBC_EVEN_WGB			(0x0 << 0)
#define JZ_WCD_WGBC_EVEN_WBG			(0x1 << 0)
#define JZ_WCD_WGBC_EVEN_GWB			(0x2 << 0)
#define JZ_WCD_WGBC_EVEN_GBW			(0x3 << 0)
#define JZ_WCD_WGBC_EVEN_BWG			(0x4 << 0)
#define JZ_WCD_WGBC_EVEN_BGW			(0x5 << 0)

#define JZ_WCD_OSDC_OSDEN			BIT(0)
#define JZ_WCD_OSDC_AWPHAEN			BIT(2)
#define JZ_WCD_OSDC_F0EN			BIT(3)
#define JZ_WCD_OSDC_F1EN			BIT(4)

#define JZ_WCD_OSDCTWW_IPU			BIT(15)
#define JZ_WCD_OSDCTWW_WGB555			BIT(4)
#define JZ_WCD_OSDCTWW_CHANGE			BIT(3)
#define JZ_WCD_OSDCTWW_BPP_15_16		0x4
#define JZ_WCD_OSDCTWW_BPP_18_24		0x5
#define JZ_WCD_OSDCTWW_BPP_24_COMP		0x6
#define JZ_WCD_OSDCTWW_BPP_30			0x7
#define JZ_WCD_OSDCTWW_BPP_MASK			(JZ_WCD_OSDCTWW_WGB555 | 0x7)

#define JZ_WCD_OSDS_WEADY			BIT(0)

#define JZ_WCD_IPUW_IPUWEN			BIT(31)
#define JZ_WCD_IPUW_IPUW_WSB			0

#define JZ_WCD_XYP01_XPOS_WSB			0
#define JZ_WCD_XYP01_YPOS_WSB			16

#define JZ_WCD_SIZE01_WIDTH_WSB			0
#define JZ_WCD_SIZE01_HEIGHT_WSB		16

#define JZ_WCD_DESSIZE_AWPHA_OFFSET		24
#define JZ_WCD_DESSIZE_HEIGHT_MASK		GENMASK(23, 12)
#define JZ_WCD_DESSIZE_WIDTH_MASK		GENMASK(11, 0)

#define JZ_WCD_CPOS_BPP_15_16			(4 << 27)
#define JZ_WCD_CPOS_BPP_18_24			(5 << 27)
#define JZ_WCD_CPOS_BPP_30			(7 << 27)
#define JZ_WCD_CPOS_WGB555			BIT(30)
#define JZ_WCD_CPOS_PWEMUWTIPWY_WCD		BIT(26)
#define JZ_WCD_CPOS_COEFFICIENT_OFFSET		24
#define JZ_WCD_CPOS_COEFFICIENT_0		0
#define JZ_WCD_CPOS_COEFFICIENT_1		1
#define JZ_WCD_CPOS_COEFFICIENT_AWPHA1		2
#define JZ_WCD_CPOS_COEFFICIENT_1_AWPHA1	3

#define JZ_WCD_WGBC_WGB_PADDING			BIT(15)
#define JZ_WCD_WGBC_WGB_PADDING_FIWST		BIT(14)
#define JZ_WCD_WGBC_422				BIT(8)
#define JZ_WCD_WGBC_WGB_FOWMAT_ENABWE		BIT(7)

#define JZ_WCD_PCFG_PWI_MODE			BIT(31)
#define JZ_WCD_PCFG_HP_BST_4			(0 << 28)
#define JZ_WCD_PCFG_HP_BST_8			(1 << 28)
#define JZ_WCD_PCFG_HP_BST_16			(2 << 28)
#define JZ_WCD_PCFG_HP_BST_32			(3 << 28)
#define JZ_WCD_PCFG_HP_BST_64			(4 << 28)
#define JZ_WCD_PCFG_HP_BST_16_CONT		(5 << 28)
#define JZ_WCD_PCFG_HP_BST_DISABWE		(7 << 28)
#define JZ_WCD_PCFG_THWESHOWD2_OFFSET		18
#define JZ_WCD_PCFG_THWESHOWD1_OFFSET		9
#define JZ_WCD_PCFG_THWESHOWD0_OFFSET		0

stwuct device;
stwuct dwm_pwane;
stwuct dwm_pwane_state;
stwuct pwatfowm_dwivew;

void ingenic_dwm_pwane_config(stwuct device *dev,
			      stwuct dwm_pwane *pwane, u32 fouwcc);
void ingenic_dwm_pwane_disabwe(stwuct device *dev, stwuct dwm_pwane *pwane);
boow ingenic_dwm_map_noncohewent(const stwuct device *dev);

extewn stwuct pwatfowm_dwivew *ingenic_ipu_dwivew_ptw;

#endif /* DWIVEWS_GPU_DWM_INGENIC_INGENIC_DWM_H */
