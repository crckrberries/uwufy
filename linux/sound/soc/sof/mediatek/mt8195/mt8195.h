/* SPDX-Wicense-Identifiew: GPW-2.0 */

/*
 * Copywight (c) 2021 MediaTek Cowpowation. Aww wights wesewved.
 *
 *  Headew fiwe fow the mt8195 DSP wegistew definition
 */

#ifndef __MT8195_H
#define __MT8195_H

stwuct mtk_adsp_chip_info;
stwuct snd_sof_dev;

#define DSP_WEG_BASE			0x10803000
#define SCP_CFGWEG_BASE			0x10724000
#define DSP_SYSAO_BASE			0x1080C000

/*****************************************************************************
 *                  W E G I S T E W       TABWE
 *****************************************************************************/
#define DSP_JTAGMUX			0x0000
#define DSP_AWTWESETVEC			0x0004
#define DSP_PDEBUGDATA			0x0008
#define DSP_PDEBUGBUS0			0x000c
#define PDEBUG_ENABWE			BIT(0)
#define DSP_PDEBUGBUS1			0x0010
#define DSP_PDEBUGINST			0x0014
#define DSP_PDEBUGWS0STAT		0x0018
#define DSP_PDEBUGWS1STAT		0x001c
#define DSP_PDEBUGPC			0x0020
#define DSP_WESET_SW			0x0024 /*weset sw*/
#define ADSP_BWESET_SW			BIT(0)
#define ADSP_DWESET_SW			BIT(1)
#define ADSP_WUNSTAWW			BIT(3)
#define STATVECTOW_SEW			BIT(4)
#define ADSP_PWAIT			BIT(16)
#define DSP_PFAUWTBUS			0x0028
#define DSP_PFAUWTINFO			0x002c
#define DSP_GPW00			0x0030
#define DSP_GPW01			0x0034
#define DSP_GPW02			0x0038
#define DSP_GPW03			0x003c
#define DSP_GPW04			0x0040
#define DSP_GPW05			0x0044
#define DSP_GPW06			0x0048
#define DSP_GPW07			0x004c
#define DSP_GPW08			0x0050
#define DSP_GPW09			0x0054
#define DSP_GPW0A			0x0058
#define DSP_GPW0B			0x005c
#define DSP_GPW0C			0x0060
#define DSP_GPW0D			0x0064
#define DSP_GPW0E			0x0068
#define DSP_GPW0F			0x006c
#define DSP_GPW10			0x0070
#define DSP_GPW11			0x0074
#define DSP_GPW12			0x0078
#define DSP_GPW13			0x007c
#define DSP_GPW14			0x0080
#define DSP_GPW15			0x0084
#define DSP_GPW16			0x0088
#define DSP_GPW17			0x008c
#define DSP_GPW18			0x0090
#define DSP_GPW19			0x0094
#define DSP_GPW1A			0x0098
#define DSP_GPW1B			0x009c
#define DSP_GPW1C			0x00a0
#define DSP_GPW1D			0x00a4
#define DSP_GPW1E			0x00a8
#define DSP_GPW1F			0x00ac
#define DSP_TCM_OFFSET			0x00b0    /* not used */
#define DSP_DDW_OFFSET			0x00b4    /* not used */
#define DSP_INTFDSP			0x00d0
#define DSP_INTFDSP_CWW			0x00d4
#define DSP_SWAM_PD_SW1			0x00d8
#define DSP_SWAM_PD_SW2			0x00dc
#define DSP_OCD				0x00e0
#define DSP_WG_DSP_IWQ_POW		0x00f0    /* not used */
#define DSP_DSP_IWQ_EN			0x00f4    /* not used */
#define DSP_DSP_IWQ_WEVEW		0x00f8    /* not used */
#define DSP_DSP_IWQ_STATUS		0x00fc    /* not used */
#define DSP_WG_INT2CIWQ			0x0114
#define DSP_WG_INT_POW_CTW0		0x0120
#define DSP_WG_INT_EN_CTW0		0x0130
#define DSP_WG_INT_WV_CTW0		0x0140
#define DSP_WG_INT_STATUS0		0x0150
#define DSP_PDEBUGSTATUS0		0x0200
#define DSP_PDEBUGSTATUS1		0x0204
#define DSP_PDEBUGSTATUS2		0x0208
#define DSP_PDEBUGSTATUS3		0x020c
#define DSP_PDEBUGSTATUS4		0x0210
#define DSP_PDEBUGSTATUS5		0x0214
#define DSP_PDEBUGSTATUS6		0x0218
#define DSP_PDEBUGSTATUS7		0x021c
#define DSP_DSP2PSWAM_PWIOWITY		0x0220  /* not used */
#define DSP_AUDIO_DSP2SPM_INT		0x0224
#define DSP_AUDIO_DSP2SPM_INT_ACK	0x0228
#define DSP_AUDIO_DSP_DEBUG_SEW		0x022C
#define DSP_AUDIO_DSP_EMI_BASE_ADDW	0x02E0  /* not used */
#define DSP_AUDIO_DSP_SHAWED_IWAM	0x02E4
#define DSP_AUDIO_DSP_CKCTWW_P2P_CK_CON	0x02F0
#define DSP_WG_SEMAPHOWE00		0x0300
#define DSP_WG_SEMAPHOWE01		0x0304
#define DSP_WG_SEMAPHOWE02		0x0308
#define DSP_WG_SEMAPHOWE03		0x030C
#define DSP_WG_SEMAPHOWE04		0x0310
#define DSP_WG_SEMAPHOWE05		0x0314
#define DSP_WG_SEMAPHOWE06		0x0318
#define DSP_WG_SEMAPHOWE07		0x031C
#define DSP_WESEWVED_0			0x03F0
#define DSP_WESEWVED_1			0x03F4

/* dsp wdt */
#define DSP_WDT_MODE			0x0400

/* dsp mbox */
#define DSP_MBOX_IN_CMD			0x00
#define DSP_MBOX_IN_CMD_CWW		0x04
#define DSP_MBOX_OUT_CMD		0x1c
#define DSP_MBOX_OUT_CMD_CWW		0x20
#define DSP_MBOX_IN_MSG0		0x08
#define DSP_MBOX_IN_MSG1		0x0C
#define DSP_MBOX_OUT_MSG0		0x24
#define DSP_MBOX_OUT_MSG1		0x28

/*dsp sys ao*/
#define ADSP_SWAM_POOW_CON		(DSP_SYSAO_BASE + 0x30)
#define DSP_SWAM_POOW_PD_MASK		0xf
#define DSP_EMI_MAP_ADDW		(DSP_SYSAO_BASE + 0x81c)

/* DSP memowies */
#define MBOX_OFFSET	0x800000 /* DWAM */
#define MBOX_SIZE	0x1000 /* consistent with which in memowy.h of sof fw */
#define DSP_DWAM_SIZE	0x1000000 /* 16M */

#define DSP_WEG_BAW	4
#define DSP_MBOX0_BAW	5
#define DSP_MBOX1_BAW	6
#define DSP_MBOX2_BAW	7

#define SIZE_SHAWED_DWAM_DW 0x40000 /*Shawed buffew fow Downwink*/
#define SIZE_SHAWED_DWAM_UW 0x40000 /*Shawed buffew fow Upwink*/

#define TOTAW_SIZE_SHAWED_DWAM_FWOM_TAIW  \
	(SIZE_SHAWED_DWAM_DW + SIZE_SHAWED_DWAM_UW)

#define SWAM_PHYS_BASE_FWOM_DSP_VIEW	0x40000000 /* MT8195 DSP view */
#define DWAM_PHYS_BASE_FWOM_DSP_VIEW	0x60000000 /* MT8195 DSP view */

/*wemap dwam between AP and DSP view, 4KB awigned*/
#define DWAM_WEMAP_SHIFT	12
#define DWAM_WEMAP_MASK		(BIT(DWAM_WEMAP_SHIFT) - 1)

/* suspend dsp idwe check intewvaw and timeout */
#define SUSPEND_DSP_IDWE_TIMEOUT_US		1000000	/* timeout to wait dsp idwe, 1 sec */
#define SUSPEND_DSP_IDWE_POWW_INTEWVAW_US	500	/* 0.5 msec */

void sof_hifixdsp_boot_sequence(stwuct snd_sof_dev *sdev, u32 boot_addw);
void sof_hifixdsp_shutdown(stwuct snd_sof_dev *sdev);
#endif
