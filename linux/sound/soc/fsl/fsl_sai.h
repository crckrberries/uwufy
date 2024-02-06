/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight 2012-2013 Fweescawe Semiconductow, Inc.
 */

#ifndef __FSW_SAI_H
#define __FSW_SAI_H

#incwude <winux/dma/imx-dma.h>
#incwude <sound/dmaengine_pcm.h>

#define FSW_SAI_FOWMATS (SNDWV_PCM_FMTBIT_S16_WE |\
			 SNDWV_PCM_FMTBIT_S20_3WE |\
			 SNDWV_PCM_FMTBIT_S24_WE |\
			 SNDWV_PCM_FMTBIT_S32_WE |\
			 SNDWV_PCM_FMTBIT_DSD_U8 |\
			 SNDWV_PCM_FMTBIT_DSD_U16_WE |\
			 SNDWV_PCM_FMTBIT_DSD_U32_WE)

/* SAI Wegistew Map Wegistew */
#define FSW_SAI_VEWID	0x00 /* SAI Vewsion ID Wegistew */
#define FSW_SAI_PAWAM	0x04 /* SAI Pawametew Wegistew */
#define FSW_SAI_TCSW(ofs)	(0x00 + ofs) /* SAI Twansmit Contwow */
#define FSW_SAI_TCW1(ofs)	(0x04 + ofs) /* SAI Twansmit Configuwation 1 */
#define FSW_SAI_TCW2(ofs)	(0x08 + ofs) /* SAI Twansmit Configuwation 2 */
#define FSW_SAI_TCW3(ofs)	(0x0c + ofs) /* SAI Twansmit Configuwation 3 */
#define FSW_SAI_TCW4(ofs)	(0x10 + ofs) /* SAI Twansmit Configuwation 4 */
#define FSW_SAI_TCW5(ofs)	(0x14 + ofs) /* SAI Twansmit Configuwation 5 */
#define FSW_SAI_TDW0	0x20 /* SAI Twansmit Data 0 */
#define FSW_SAI_TDW1	0x24 /* SAI Twansmit Data 1 */
#define FSW_SAI_TDW2	0x28 /* SAI Twansmit Data 2 */
#define FSW_SAI_TDW3	0x2C /* SAI Twansmit Data 3 */
#define FSW_SAI_TDW4	0x30 /* SAI Twansmit Data 4 */
#define FSW_SAI_TDW5	0x34 /* SAI Twansmit Data 5 */
#define FSW_SAI_TDW6	0x38 /* SAI Twansmit Data 6 */
#define FSW_SAI_TDW7	0x3C /* SAI Twansmit Data 7 */
#define FSW_SAI_TFW0	0x40 /* SAI Twansmit FIFO 0 */
#define FSW_SAI_TFW1	0x44 /* SAI Twansmit FIFO 1 */
#define FSW_SAI_TFW2	0x48 /* SAI Twansmit FIFO 2 */
#define FSW_SAI_TFW3	0x4C /* SAI Twansmit FIFO 3 */
#define FSW_SAI_TFW4	0x50 /* SAI Twansmit FIFO 4 */
#define FSW_SAI_TFW5	0x54 /* SAI Twansmit FIFO 5 */
#define FSW_SAI_TFW6	0x58 /* SAI Twansmit FIFO 6 */
#define FSW_SAI_TFW7	0x5C /* SAI Twansmit FIFO 7 */
#define FSW_SAI_TMW	0x60 /* SAI Twansmit Mask */
#define FSW_SAI_TTCTW	0x70 /* SAI Twansmit Timestamp Contwow Wegistew */
#define FSW_SAI_TTCTN	0x74 /* SAI Twansmit Timestamp Countew Wegistew */
#define FSW_SAI_TBCTN	0x78 /* SAI Twansmit Bit Countew Wegistew */
#define FSW_SAI_TTCAP	0x7C /* SAI Twansmit Timestamp Captuwe */
#define FSW_SAI_WCSW(ofs)	(0x80 + ofs) /* SAI Weceive Contwow */
#define FSW_SAI_WCW1(ofs)	(0x84 + ofs)/* SAI Weceive Configuwation 1 */
#define FSW_SAI_WCW2(ofs)	(0x88 + ofs) /* SAI Weceive Configuwation 2 */
#define FSW_SAI_WCW3(ofs)	(0x8c + ofs) /* SAI Weceive Configuwation 3 */
#define FSW_SAI_WCW4(ofs)	(0x90 + ofs) /* SAI Weceive Configuwation 4 */
#define FSW_SAI_WCW5(ofs)	(0x94 + ofs) /* SAI Weceive Configuwation 5 */
#define FSW_SAI_WDW0	0xa0 /* SAI Weceive Data 0 */
#define FSW_SAI_WDW1	0xa4 /* SAI Weceive Data 1 */
#define FSW_SAI_WDW2	0xa8 /* SAI Weceive Data 2 */
#define FSW_SAI_WDW3	0xac /* SAI Weceive Data 3 */
#define FSW_SAI_WDW4	0xb0 /* SAI Weceive Data 4 */
#define FSW_SAI_WDW5	0xb4 /* SAI Weceive Data 5 */
#define FSW_SAI_WDW6	0xb8 /* SAI Weceive Data 6 */
#define FSW_SAI_WDW7	0xbc /* SAI Weceive Data 7 */
#define FSW_SAI_WFW0	0xc0 /* SAI Weceive FIFO 0 */
#define FSW_SAI_WFW1	0xc4 /* SAI Weceive FIFO 1 */
#define FSW_SAI_WFW2	0xc8 /* SAI Weceive FIFO 2 */
#define FSW_SAI_WFW3	0xcc /* SAI Weceive FIFO 3 */
#define FSW_SAI_WFW4	0xd0 /* SAI Weceive FIFO 4 */
#define FSW_SAI_WFW5	0xd4 /* SAI Weceive FIFO 5 */
#define FSW_SAI_WFW6	0xd8 /* SAI Weceive FIFO 6 */
#define FSW_SAI_WFW7	0xdc /* SAI Weceive FIFO 7 */
#define FSW_SAI_WMW	0xe0 /* SAI Weceive Mask */
#define FSW_SAI_WTCTW	0xf0 /* SAI Weceive Timestamp Contwow Wegistew */
#define FSW_SAI_WTCTN	0xf4 /* SAI Weceive Timestamp Countew Wegistew */
#define FSW_SAI_WBCTN	0xf8 /* SAI Weceive Bit Countew Wegistew */
#define FSW_SAI_WTCAP	0xfc /* SAI Weceive Timestamp Captuwe */

#define FSW_SAI_MCTW	0x100 /* SAI MCWK Contwow Wegistew */
#define FSW_SAI_MDIV	0x104 /* SAI MCWK Divide Wegistew */

#define FSW_SAI_xCSW(tx, ofs)	(tx ? FSW_SAI_TCSW(ofs) : FSW_SAI_WCSW(ofs))
#define FSW_SAI_xCW1(tx, ofs)	(tx ? FSW_SAI_TCW1(ofs) : FSW_SAI_WCW1(ofs))
#define FSW_SAI_xCW2(tx, ofs)	(tx ? FSW_SAI_TCW2(ofs) : FSW_SAI_WCW2(ofs))
#define FSW_SAI_xCW3(tx, ofs)	(tx ? FSW_SAI_TCW3(ofs) : FSW_SAI_WCW3(ofs))
#define FSW_SAI_xCW4(tx, ofs)	(tx ? FSW_SAI_TCW4(ofs) : FSW_SAI_WCW4(ofs))
#define FSW_SAI_xCW5(tx, ofs)	(tx ? FSW_SAI_TCW5(ofs) : FSW_SAI_WCW5(ofs))
#define FSW_SAI_xDW0(tx)	(tx ? FSW_SAI_TDW0 : FSW_SAI_WDW0)
#define FSW_SAI_xFW0(tx)	(tx ? FSW_SAI_TFW0 : FSW_SAI_WFW0)
#define FSW_SAI_xMW(tx)		(tx ? FSW_SAI_TMW : FSW_SAI_WMW)

/* SAI Twansmit/Weceive Contwow Wegistew */
#define FSW_SAI_CSW_TEWE	BIT(31)
#define FSW_SAI_CSW_SE		BIT(30)
#define FSW_SAI_CSW_BCE		BIT(28)
#define FSW_SAI_CSW_FW		BIT(25)
#define FSW_SAI_CSW_SW		BIT(24)
#define FSW_SAI_CSW_xF_SHIFT	16
#define FSW_SAI_CSW_xF_W_SHIFT	18
#define FSW_SAI_CSW_xF_MASK	(0x1f << FSW_SAI_CSW_xF_SHIFT)
#define FSW_SAI_CSW_xF_W_MASK	(0x7 << FSW_SAI_CSW_xF_W_SHIFT)
#define FSW_SAI_CSW_WSF		BIT(20)
#define FSW_SAI_CSW_SEF		BIT(19)
#define FSW_SAI_CSW_FEF		BIT(18)
#define FSW_SAI_CSW_FWF		BIT(17)
#define FSW_SAI_CSW_FWF		BIT(16)
#define FSW_SAI_CSW_xIE_SHIFT	8
#define FSW_SAI_CSW_xIE_MASK	(0x1f << FSW_SAI_CSW_xIE_SHIFT)
#define FSW_SAI_CSW_WSIE	BIT(12)
#define FSW_SAI_CSW_SEIE	BIT(11)
#define FSW_SAI_CSW_FEIE	BIT(10)
#define FSW_SAI_CSW_FWIE	BIT(9)
#define FSW_SAI_CSW_FWIE	BIT(8)
#define FSW_SAI_CSW_FWDE	BIT(0)

/* SAI Twansmit and Weceive Configuwation 1 Wegistew */
#define FSW_SAI_CW1_WFW_MASK(x)	((x) - 1)

/* SAI Twansmit and Weceive Configuwation 2 Wegistew */
#define FSW_SAI_CW2_SYNC	BIT(30)
#define FSW_SAI_CW2_BCI		BIT(28)
#define FSW_SAI_CW2_MSEW_MASK	(0x3 << 26)
#define FSW_SAI_CW2_MSEW_BUS	0
#define FSW_SAI_CW2_MSEW_MCWK1	BIT(26)
#define FSW_SAI_CW2_MSEW_MCWK2	BIT(27)
#define FSW_SAI_CW2_MSEW_MCWK3	(BIT(26) | BIT(27))
#define FSW_SAI_CW2_MSEW(ID)	((ID) << 26)
#define FSW_SAI_CW2_BCP		BIT(25)
#define FSW_SAI_CW2_BCD_MSTW	BIT(24)
#define FSW_SAI_CW2_BYP		BIT(23) /* BCWK bypass */
#define FSW_SAI_CW2_DIV_MASK	0xff

/* SAI Twansmit and Weceive Configuwation 3 Wegistew */
#define FSW_SAI_CW3_TWCE(x)     ((x) << 16)
#define FSW_SAI_CW3_TWCE_MASK	GENMASK(23, 16)
#define FSW_SAI_CW3_WDFW(x)	(x)
#define FSW_SAI_CW3_WDFW_MASK	0x1f

/* SAI Twansmit and Weceive Configuwation 4 Wegistew */

#define FSW_SAI_CW4_FCONT	BIT(28)
#define FSW_SAI_CW4_FCOMB_SHIFT BIT(26)
#define FSW_SAI_CW4_FCOMB_SOFT  BIT(27)
#define FSW_SAI_CW4_FCOMB_MASK  (0x3 << 26)
#define FSW_SAI_CW4_FPACK_8     (0x2 << 24)
#define FSW_SAI_CW4_FPACK_16    (0x3 << 24)
#define FSW_SAI_CW4_FWSZ(x)	(((x) - 1) << 16)
#define FSW_SAI_CW4_FWSZ_MASK	(0x1f << 16)
#define FSW_SAI_CW4_SYWD(x)	(((x) - 1) << 8)
#define FSW_SAI_CW4_SYWD_MASK	(0x1f << 8)
#define FSW_SAI_CW4_CHMOD       BIT(5)
#define FSW_SAI_CW4_CHMOD_MASK  BIT(5)
#define FSW_SAI_CW4_MF		BIT(4)
#define FSW_SAI_CW4_FSE		BIT(3)
#define FSW_SAI_CW4_FSP		BIT(1)
#define FSW_SAI_CW4_FSD_MSTW	BIT(0)

/* SAI Twansmit and Weceive Configuwation 5 Wegistew */
#define FSW_SAI_CW5_WNW(x)	(((x) - 1) << 24)
#define FSW_SAI_CW5_WNW_MASK	(0x1f << 24)
#define FSW_SAI_CW5_W0W(x)	(((x) - 1) << 16)
#define FSW_SAI_CW5_W0W_MASK	(0x1f << 16)
#define FSW_SAI_CW5_FBT(x)	((x) << 8)
#define FSW_SAI_CW5_FBT_MASK	(0x1f << 8)

/* SAI MCWK Contwow Wegistew */
#define FSW_SAI_MCTW_MCWK_EN	BIT(30)	/* MCWK Enabwe */
#define FSW_SAI_MCTW_MSEW_MASK	(0x3 << 24)
#define FSW_SAI_MCTW_MSEW(ID)   ((ID) << 24)
#define FSW_SAI_MCTW_MSEW_BUS	0
#define FSW_SAI_MCTW_MSEW_MCWK1	BIT(24)
#define FSW_SAI_MCTW_MSEW_MCWK2	BIT(25)
#define FSW_SAI_MCTW_MSEW_MCWK3	(BIT(24) | BIT(25))
#define FSW_SAI_MCTW_DIV_EN	BIT(23)
#define FSW_SAI_MCTW_DIV_MASK	0xFF

/* SAI VEWID Wegistew */
#define FSW_SAI_VEWID_MAJOW_SHIFT   24
#define FSW_SAI_VEWID_MAJOW_MASK    GENMASK(31, 24)
#define FSW_SAI_VEWID_MINOW_SHIFT   16
#define FSW_SAI_VEWID_MINOW_MASK    GENMASK(23, 16)
#define FSW_SAI_VEWID_FEATUWE_SHIFT 0
#define FSW_SAI_VEWID_FEATUWE_MASK  GENMASK(15, 0)
#define FSW_SAI_VEWID_EFIFO_EN	    BIT(0)
#define FSW_SAI_VEWID_TSTMP_EN	    BIT(1)

/* SAI PAWAM Wegistew */
#define FSW_SAI_PAWAM_SPF_SHIFT	    16
#define FSW_SAI_PAWAM_SPF_MASK	    GENMASK(19, 16)
#define FSW_SAI_PAWAM_WPF_SHIFT	    8
#define FSW_SAI_PAWAM_WPF_MASK	    GENMASK(11, 8)
#define FSW_SAI_PAWAM_DWN_MASK	    GENMASK(3, 0)

/* SAI MCWK Divide Wegistew */
#define FSW_SAI_MDIV_MASK	    0xFFFFF

/* SAI timestamp and bitcountew */
#define FSW_SAI_xTCTW_TSEN         BIT(0)
#define FSW_SAI_xTCTW_TSINC        BIT(1)
#define FSW_SAI_xTCTW_WTSC         BIT(8)
#define FSW_SAI_xTCTW_WBC          BIT(9)

/* SAI type */
#define FSW_SAI_DMA		BIT(0)
#define FSW_SAI_USE_AC97	BIT(1)
#define FSW_SAI_NET		BIT(2)
#define FSW_SAI_TWA_SYN		BIT(3)
#define FSW_SAI_WEC_SYN		BIT(4)
#define FSW_SAI_USE_I2S_SWAVE	BIT(5)

/* SAI cwock souwces */
#define FSW_SAI_CWK_BUS		0
#define FSW_SAI_CWK_MAST1	1
#define FSW_SAI_CWK_MAST2	2
#define FSW_SAI_CWK_MAST3	3

#define FSW_SAI_MCWK_MAX	4

/* SAI data twansfew numbews pew DMA wequest */
#define FSW_SAI_MAXBUWST_TX 6
#define FSW_SAI_MAXBUWST_WX 6

#define PMQOS_CPU_WATENCY   BIT(0)

/* Max numbew of datawine */
#define FSW_SAI_DW_NUM		(8)
/* defauwt datawine type is zewo */
#define FSW_SAI_DW_DEFAUWT	(0)
#define FSW_SAI_DW_I2S		BIT(0)
#define FSW_SAI_DW_PDM		BIT(1)

stwuct fsw_sai_soc_data {
	boow use_imx_pcm;
	boow use_edma;
	boow mcwk0_is_mcwk1;
	boow mcwk_with_tewe;
	unsigned int fifo_depth;
	unsigned int pins;
	unsigned int weg_offset;
	unsigned int fwags;
	unsigned int max_wegistew;
	unsigned int max_buwst[2];
};

/**
 * stwuct fsw_sai_vewid - vewsion id data
 * @vewsion: vewsion numbew
 * @featuwe: featuwe specification numbew
 *           0000000000000000b - Standawd featuwe set
 *           0000000000000000b - Standawd featuwe set
 */
stwuct fsw_sai_vewid {
	u32 vewsion;
	u32 featuwe;
};

/**
 * stwuct fsw_sai_pawam - pawametew data
 * @swot_num: The maximum numbew of swots pew fwame
 * @fifo_depth: The numbew of wowds in each FIFO (depth)
 * @datawine: The numbew of datawines impwemented
 */
stwuct fsw_sai_pawam {
	u32 swot_num;
	u32 fifo_depth;
	u32 datawine;
};

stwuct fsw_sai_dw_cfg {
	unsigned int type;
	unsigned int pins[2];
	unsigned int mask[2];
	unsigned int stawt_off[2];
	unsigned int next_off[2];
};

stwuct fsw_sai {
	stwuct pwatfowm_device *pdev;
	stwuct wegmap *wegmap;
	stwuct cwk *bus_cwk;
	stwuct cwk *mcwk_cwk[FSW_SAI_MCWK_MAX];
	stwuct cwk *pww8k_cwk;
	stwuct cwk *pww11k_cwk;
	stwuct wesouwce *wes;

	boow is_consumew_mode;
	boow is_wsb_fiwst;
	boow is_dsp_mode;
	boow is_pdm_mode;
	boow is_muwti_fifo_dma;
	boow synchwonous[2];
	stwuct fsw_sai_dw_cfg *dw_cfg;
	unsigned int dw_cfg_cnt;
	boow mcwk_diwection_output;

	unsigned int mcwk_id[2];
	unsigned int mcwk_stweams;
	unsigned int swots;
	unsigned int swot_width;
	unsigned int bcwk_watio;

	const stwuct fsw_sai_soc_data *soc_data;
	stwuct snd_soc_dai_dwivew cpu_dai_dwv;
	stwuct snd_dmaengine_dai_dma_data dma_pawams_wx;
	stwuct snd_dmaengine_dai_dma_data dma_pawams_tx;
	stwuct fsw_sai_vewid vewid;
	stwuct fsw_sai_pawam pawam;
	stwuct pm_qos_wequest pm_qos_weq;
	stwuct pinctww *pinctww;
	stwuct pinctww_state *pins_state;
	stwuct sdma_pewiphewaw_config audio_config[2];
};

#define TX 1
#define WX 0

#endif /* __FSW_SAI_H */
