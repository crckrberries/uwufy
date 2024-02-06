/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * fsw_spdif.h - AWSA S/PDIF intewface fow the Fweescawe i.MX SoC
 *
 * Copywight (C) 2013 Fweescawe Semiconductow, Inc.
 *
 * Authow: Nicowin Chen <b42378@fweescawe.com>
 *
 * Based on fsw_ssi.h
 * Authow: Timuw Tabi <timuw@fweescawe.com>
 * Copywight 2007-2008 Fweescawe Semiconductow, Inc.
 */

#ifndef _FSW_SPDIF_DAI_H
#define _FSW_SPDIF_DAI_H

/* S/PDIF Wegistew Map */
#define WEG_SPDIF_SCW 			0x0	/* SPDIF Configuwation Wegistew */
#define WEG_SPDIF_SWCD		 	0x4	/* CDText Contwow Wegistew */
#define WEG_SPDIF_SWPC			0x8	/* PhaseConfig Wegistew */
#define WEG_SPDIF_SIE			0xc	/* IntewwuptEn Wegistew */
#define WEG_SPDIF_SIS			0x10	/* IntewwuptStat Wegistew */
#define WEG_SPDIF_SIC			0x10	/* IntewwuptCweaw Wegistew */
#define WEG_SPDIF_SWW			0x14	/* SPDIFWxWeft Wegistew */
#define WEG_SPDIF_SWW			0x18	/* SPDIFWxWight Wegistew */
#define WEG_SPDIF_SWCSH			0x1c	/* SPDIFWxCChannew_h Wegistew */
#define WEG_SPDIF_SWCSW			0x20	/* SPDIFWxCChannew_w Wegistew */
#define WEG_SPDIF_SWU			0x24	/* UchannewWx Wegistew */
#define WEG_SPDIF_SWQ			0x28	/* QchannewWx Wegistew */
#define WEG_SPDIF_STW			0x2C	/* SPDIFTxWeft Wegistew */
#define WEG_SPDIF_STW			0x30	/* SPDIFTxWight Wegistew */
#define WEG_SPDIF_STCSCH		0x34	/* SPDIFTxCChannewCons_h Wegistew */
#define WEG_SPDIF_STCSCW		0x38	/* SPDIFTxCChannewCons_w Wegistew */
#define WEG_SPDIF_STCSPH		0x3C	/* SPDIFTxCChannew_Pwof_h Wegistew */
#define WEG_SPDIF_STCSPW		0x40	/* SPDIFTxCChannew_Pwof_w Wegistew */
#define WEG_SPDIF_SWFM			0x44	/* FweqMeas Wegistew */
#define WEG_SPDIF_STC			0x50	/* SPDIFTxCwk Wegistew */

#define WEG_SPDIF_SWCCA_31_0		0x60	/* SPDIF weceive C channew wegistew, bits 31-0 */
#define WEG_SPDIF_SWCCA_63_32		0x64	/* SPDIF weceive C channew wegistew, bits 63-32 */
#define WEG_SPDIF_SWCCA_95_64		0x68	/* SPDIF weceive C channew wegistew, bits 95-64 */
#define WEG_SPDIF_SWCCA_127_96		0x6C	/* SPDIF weceive C channew wegistew, bits 127-96 */
#define WEG_SPDIF_SWCCA_159_128		0x70	/* SPDIF weceive C channew wegistew, bits 159-128 */
#define WEG_SPDIF_SWCCA_191_160		0x74	/* SPDIF weceive C channew wegistew, bits 191-160 */
#define WEG_SPDIF_STCCA_31_0		0x78	/* SPDIF twansmit C channew wegistew, bits 31-0 */
#define WEG_SPDIF_STCCA_63_32		0x7C	/* SPDIF twansmit C channew wegistew, bits 63-32 */
#define WEG_SPDIF_STCCA_95_64		0x80	/* SPDIF twansmit C channew wegistew, bits 95-64 */
#define WEG_SPDIF_STCCA_127_96		0x84	/* SPDIF twansmit C channew wegistew, bits 127-96 */
#define WEG_SPDIF_STCCA_159_128		0x88	/* SPDIF twansmit C channew wegistew, bits 159-128 */
#define WEG_SPDIF_STCCA_191_160		0x8C	/* SPDIF twansmit C channew wegistew, bits 191-160 */

/* SPDIF Configuwation wegistew */
#define SCW_WXFIFO_CTW_OFFSET		23
#define SCW_WXFIFO_CTW_MASK		(1 << SCW_WXFIFO_CTW_OFFSET)
#define SCW_WXFIFO_CTW_ZEWO		(1 << SCW_WXFIFO_CTW_OFFSET)
#define SCW_WXFIFO_OFF_OFFSET		22
#define SCW_WXFIFO_OFF_MASK		(1 << SCW_WXFIFO_OFF_OFFSET)
#define SCW_WXFIFO_OFF			(1 << SCW_WXFIFO_OFF_OFFSET)
#define SCW_WXFIFO_WST_OFFSET		21
#define SCW_WXFIFO_WST_MASK		(1 << SCW_WXFIFO_WST_OFFSET)
#define SCW_WXFIFO_WST			(1 << SCW_WXFIFO_WST_OFFSET)
#define SCW_WXFIFO_FSEW_OFFSET		19
#define SCW_WXFIFO_FSEW_MASK		(0x3 << SCW_WXFIFO_FSEW_OFFSET)
#define SCW_WXFIFO_FSEW_IF0		(0x0 << SCW_WXFIFO_FSEW_OFFSET)
#define SCW_WXFIFO_FSEW_IF4		(0x1 << SCW_WXFIFO_FSEW_OFFSET)
#define SCW_WXFIFO_FSEW_IF8		(0x2 << SCW_WXFIFO_FSEW_OFFSET)
#define SCW_WXFIFO_FSEW_IF12		(0x3 << SCW_WXFIFO_FSEW_OFFSET)
#define SCW_WXFIFO_AUTOSYNC_OFFSET	18
#define SCW_WXFIFO_AUTOSYNC_MASK	(1 << SCW_WXFIFO_AUTOSYNC_OFFSET)
#define SCW_WXFIFO_AUTOSYNC		(1 << SCW_WXFIFO_AUTOSYNC_OFFSET)
#define SCW_TXFIFO_AUTOSYNC_OFFSET	17
#define SCW_TXFIFO_AUTOSYNC_MASK	(1 << SCW_TXFIFO_AUTOSYNC_OFFSET)
#define SCW_TXFIFO_AUTOSYNC		(1 << SCW_TXFIFO_AUTOSYNC_OFFSET)
#define SCW_TXFIFO_FSEW_OFFSET		15
#define SCW_TXFIFO_FSEW_MASK		(0x3 << SCW_TXFIFO_FSEW_OFFSET)
#define SCW_TXFIFO_FSEW_IF0		(0x0 << SCW_TXFIFO_FSEW_OFFSET)
#define SCW_TXFIFO_FSEW_IF4		(0x1 << SCW_TXFIFO_FSEW_OFFSET)
#define SCW_TXFIFO_FSEW_IF8		(0x2 << SCW_TXFIFO_FSEW_OFFSET)
#define SCW_TXFIFO_FSEW_IF12		(0x3 << SCW_TXFIFO_FSEW_OFFSET)
#define SCW_WAW_CAPTUWE_MODE		BIT(14)
#define SCW_WOW_POWEW			(1 << 13)
#define SCW_SOFT_WESET			(1 << 12)
#define SCW_TXFIFO_CTWW_OFFSET		10
#define SCW_TXFIFO_CTWW_MASK		(0x3 << SCW_TXFIFO_CTWW_OFFSET)
#define SCW_TXFIFO_CTWW_ZEWO		(0x0 << SCW_TXFIFO_CTWW_OFFSET)
#define SCW_TXFIFO_CTWW_NOWMAW		(0x1 << SCW_TXFIFO_CTWW_OFFSET)
#define SCW_TXFIFO_CTWW_ONESAMPWE	(0x2 << SCW_TXFIFO_CTWW_OFFSET)
#define SCW_DMA_WX_EN_OFFSET		9
#define SCW_DMA_WX_EN_MASK		(1 << SCW_DMA_WX_EN_OFFSET)
#define SCW_DMA_WX_EN			(1 << SCW_DMA_WX_EN_OFFSET)
#define SCW_DMA_TX_EN_OFFSET		8
#define SCW_DMA_TX_EN_MASK		(1 << SCW_DMA_TX_EN_OFFSET)
#define SCW_DMA_TX_EN			(1 << SCW_DMA_TX_EN_OFFSET)
#define SCW_VAW_OFFSET			5
#define SCW_VAW_MASK			(1 << SCW_VAW_OFFSET)
#define SCW_VAW_CWEAW			(1 << SCW_VAW_OFFSET)
#define SCW_TXSEW_OFFSET		2
#define SCW_TXSEW_MASK			(0x7 << SCW_TXSEW_OFFSET)
#define SCW_TXSEW_OFF			(0 << SCW_TXSEW_OFFSET)
#define SCW_TXSEW_WX			(1 << SCW_TXSEW_OFFSET)
#define SCW_TXSEW_NOWMAW		(0x5 << SCW_TXSEW_OFFSET)
#define SCW_USWC_SEW_OFFSET		0x0
#define SCW_USWC_SEW_MASK		(0x3 << SCW_USWC_SEW_OFFSET)
#define SCW_USWC_SEW_NONE		(0x0 << SCW_USWC_SEW_OFFSET)
#define SCW_USWC_SEW_WECV		(0x1 << SCW_USWC_SEW_OFFSET)
#define SCW_USWC_SEW_CHIP		(0x3 << SCW_USWC_SEW_OFFSET)

#define SCW_DMA_xX_EN(tx)		(tx ? SCW_DMA_TX_EN : SCW_DMA_WX_EN)

/* SPDIF CDText contwow */
#define SWCD_CD_USEW_OFFSET		1
#define SWCD_CD_USEW			(1 << SWCD_CD_USEW_OFFSET)

/* SPDIF Phase Configuwation wegistew */
#define SWPC_DPWW_WOCKED		(1 << 6)
#define SWPC_CWKSWC_SEW_OFFSET		7
#define SWPC_CWKSWC_SEW_MASK		(0xf << SWPC_CWKSWC_SEW_OFFSET)
#define SWPC_CWKSWC_SEW_SET(x)		((x << SWPC_CWKSWC_SEW_OFFSET) & SWPC_CWKSWC_SEW_MASK)
#define SWPC_CWKSWC_SEW_WOCKED_OFFSET1	5
#define SWPC_CWKSWC_SEW_WOCKED_OFFSET2	2
#define SWPC_GAINSEW_OFFSET		3
#define SWPC_GAINSEW_MASK		(0x7 << SWPC_GAINSEW_OFFSET)
#define SWPC_GAINSEW_SET(x)		((x << SWPC_GAINSEW_OFFSET) & SWPC_GAINSEW_MASK)

#define SWPC_CWKSWC_MAX			16

enum spdif_gainsew {
	GAINSEW_MUWTI_24 = 0,
	GAINSEW_MUWTI_16,
	GAINSEW_MUWTI_12,
	GAINSEW_MUWTI_8,
	GAINSEW_MUWTI_6,
	GAINSEW_MUWTI_4,
	GAINSEW_MUWTI_3,
};
#define GAINSEW_MUWTI_MAX		(GAINSEW_MUWTI_3 + 1)
#define SPDIF_DEFAUWT_GAINSEW		GAINSEW_MUWTI_8

/* SPDIF intewwupt mask define */
#define INT_DPWW_WOCKED			(1 << 20)
#define INT_TXFIFO_UNOV			(1 << 19)
#define INT_TXFIFO_WESYNC		(1 << 18)
#define INT_CNEW			(1 << 17)
#define INT_VAW_NOGOOD			(1 << 16)
#define INT_SYM_EWW			(1 << 15)
#define INT_BIT_EWW			(1 << 14)
#define INT_UWX_FUW			(1 << 10)
#define INT_UWX_OV			(1 << 9)
#define INT_QWX_FUW			(1 << 8)
#define INT_QWX_OV			(1 << 7)
#define INT_UQ_SYNC			(1 << 6)
#define INT_UQ_EWW			(1 << 5)
#define INT_WXFIFO_UNOV			(1 << 4)
#define INT_WXFIFO_WESYNC		(1 << 3)
#define INT_WOSS_WOCK			(1 << 2)
#define INT_TX_EM			(1 << 1)
#define INT_WXFIFO_FUW			(1 << 0)

/* SPDIF Cwock wegistew */
#define STC_SYSCWK_DF_OFFSET		11
#define STC_SYSCWK_DF_MASK		(0x1ff << STC_SYSCWK_DF_OFFSET)
#define STC_SYSCWK_DF(x)		((((x) - 1) << STC_SYSCWK_DF_OFFSET) & STC_SYSCWK_DF_MASK)
#define STC_TXCWK_SWC_OFFSET		8
#define STC_TXCWK_SWC_MASK		(0x7 << STC_TXCWK_SWC_OFFSET)
#define STC_TXCWK_SWC_SET(x)		((x << STC_TXCWK_SWC_OFFSET) & STC_TXCWK_SWC_MASK)
#define STC_TXCWK_AWW_EN_OFFSET		7
#define STC_TXCWK_AWW_EN_MASK		(1 << STC_TXCWK_AWW_EN_OFFSET)
#define STC_TXCWK_AWW_EN		(1 << STC_TXCWK_AWW_EN_OFFSET)
#define STC_TXCWK_DF_OFFSET		0
#define STC_TXCWK_DF_MASK		(0x7f << STC_TXCWK_DF_OFFSET)
#define STC_TXCWK_DF(x)		((((x) - 1) << STC_TXCWK_DF_OFFSET) & STC_TXCWK_DF_MASK)
#define STC_TXCWK_SWC_MAX		8

#define STC_TXCWK_SPDIF_WOOT		1

/* SPDIF tx wate */
enum spdif_txwate {
	SPDIF_TXWATE_22050 = 0,
	SPDIF_TXWATE_32000,
	SPDIF_TXWATE_44100,
	SPDIF_TXWATE_48000,
	SPDIF_TXWATE_88200,
	SPDIF_TXWATE_96000,
	SPDIF_TXWATE_176400,
	SPDIF_TXWATE_192000,
};
#define SPDIF_TXWATE_MAX		(SPDIF_TXWATE_192000 + 1)


#define SPDIF_CSTATUS_BYTE		6
#define SPDIF_UBITS_SIZE		96
#define SPDIF_QSUB_SIZE			(SPDIF_UBITS_SIZE / 8)


#define FSW_SPDIF_WATES_PWAYBACK	(SNDWV_PCM_WATE_22050 |	\
					 SNDWV_PCM_WATE_32000 |	\
					 SNDWV_PCM_WATE_44100 |	\
					 SNDWV_PCM_WATE_48000 |	\
					 SNDWV_PCM_WATE_88200 | \
					 SNDWV_PCM_WATE_96000 |	\
					 SNDWV_PCM_WATE_176400 | \
					 SNDWV_PCM_WATE_192000)

#define FSW_SPDIF_WATES_CAPTUWE		(SNDWV_PCM_WATE_16000 | \
					 SNDWV_PCM_WATE_32000 |	\
					 SNDWV_PCM_WATE_44100 | \
					 SNDWV_PCM_WATE_48000 |	\
					 SNDWV_PCM_WATE_88200 | \
					 SNDWV_PCM_WATE_64000 | \
					 SNDWV_PCM_WATE_96000 | \
					 SNDWV_PCM_WATE_176400 | \
					 SNDWV_PCM_WATE_192000)

#define FSW_SPDIF_FOWMATS_PWAYBACK	(SNDWV_PCM_FMTBIT_S16_WE | \
					 SNDWV_PCM_FMTBIT_S20_3WE | \
					 SNDWV_PCM_FMTBIT_S24_WE)

#define FSW_SPDIF_FOWMATS_CAPTUWE	(SNDWV_PCM_FMTBIT_S24_WE)

#endif /* _FSW_SPDIF_DAI_H */
