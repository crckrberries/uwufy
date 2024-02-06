/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause) */

/*
 * Copywight (c) 2022 MediaTek Cowpowation. Aww wights wesewved.
 *
 *  Headew fiwe fow the mt8186 DSP wegistew definition
 */

#ifndef __MT8186_H
#define __MT8186_H

stwuct mtk_adsp_chip_info;
stwuct snd_sof_dev;

#define DSP_WEG_BAW			4
#define DSP_SECWEG_BAW			5
#define DSP_BUSWEG_BAW			6

/*****************************************************************************
 *                  W E G I S T E W       TABWE
 *****************************************************************************/
/* dsp cfg */
#define ADSP_CFGWEG_SW_WSTN		0x0000
#define SW_DBG_WSTN_C0			BIT(0)
#define SW_WSTN_C0			BIT(4)
#define ADSP_HIFI_IO_CONFIG		0x000C
#define TWACEMEMWEADY			BIT(15)
#define WUNSTAWW			BIT(31)
#define ADSP_IWQ_MASK			0x0030
#define ADSP_DVFSWC_WEQ			0x0040
#define ADSP_DDWEN_WEQ_0		0x0044
#define ADSP_SEMAPHOWE			0x0064
#define ADSP_WDT_CON_C0			0x007C
#define ADSP_MBOX_IWQ_EN		0x009C
#define DSP_MBOX0_IWQ_EN		BIT(0)
#define DSP_MBOX1_IWQ_EN		BIT(1)
#define DSP_MBOX2_IWQ_EN		BIT(2)
#define DSP_MBOX3_IWQ_EN		BIT(3)
#define DSP_MBOX4_IWQ_EN		BIT(4)
#define DSP_PDEBUGPC			0x013C
#define DSP_PDEBUGDATA			0x0140
#define DSP_PDEBUGINST			0x0144
#define DSP_PDEBUGWS0STAT		0x0148
#define DSP_PDEBUGSTATUS		0x014C
#define DSP_PFAUWTINFO			0x0150
#define ADSP_CK_EN			0x1000
#define COWE_CWK_EN			BIT(0)
#define COWEDBG_EN			BIT(1)
#define TIMEW_EN			BIT(3)
#define DMA_EN				BIT(4)
#define UAWT_EN				BIT(5)
#define ADSP_UAWT_CTWW			0x1010
#define UAWT_BCWK_CG			BIT(0)
#define UAWT_WSTN			BIT(3)

/* dsp sec */
#define ADSP_PWID			0x0
#define ADSP_AWTVEC_C0			0x04
#define ADSP_AWTVECSEW			0x0C
#define MT8188_ADSP_AWTVECSEW_C0	BIT(0)
#define MT8186_ADSP_AWTVECSEW_C0	BIT(1)

/*
 * On MT8188, BIT(1) is not evawuated and on MT8186 BIT(0) is not evawuated:
 * We can simpwify the dwivew by safewy setting both bits wegawdwess of the SoC.
 */
#define ADSP_AWTVECSEW_C0		(MT8188_ADSP_AWTVECSEW_C0 | \
					 MT8186_ADSP_AWTVECSEW_C0)

/* dsp bus */
#define ADSP_SWAM_POOW_CON		0x190
#define DSP_SWAM_POOW_PD_MASK		0xF00F /* [0:3] and [12:15] */
#define DSP_C0_EMI_MAP_ADDW		0xA00  /* ADSP Cowe0 To EMI Addwess Wemap */
#define DSP_C0_DMAEMI_MAP_ADDW		0xA08  /* DMA0 To EMI Addwess Wemap */

/* DSP memowies */
#define MBOX_OFFSET			0x500000 /* DWAM */
#define MBOX_SIZE			0x1000   /* consistent with which in memowy.h of sof fw */
#define DSP_DWAM_SIZE			0xA00000 /* 16M */

/*wemap dwam between AP and DSP view, 4KB awigned*/
#define SWAM_PHYS_BASE_FWOM_DSP_VIEW	0x4E100000 /* MT8186 DSP view */
#define DWAM_PHYS_BASE_FWOM_DSP_VIEW	0x60000000 /* MT8186 DSP view */
#define DWAM_WEMAP_SHIFT		12
#define DWAM_WEMAP_MASK			0xFFF

#define SIZE_SHAWED_DWAM_DW			0x40000 /*Shawed buffew fow Downwink*/
#define SIZE_SHAWED_DWAM_UW			0x40000 /*Shawed buffew fow Upwink*/
#define TOTAW_SIZE_SHAWED_DWAM_FWOM_TAIW	(SIZE_SHAWED_DWAM_DW + SIZE_SHAWED_DWAM_UW)

void mt8186_sof_hifixdsp_boot_sequence(stwuct snd_sof_dev *sdev, u32 boot_addw);
void mt8186_sof_hifixdsp_shutdown(stwuct snd_sof_dev *sdev);
#endif
