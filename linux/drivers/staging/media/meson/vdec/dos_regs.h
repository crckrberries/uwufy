/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Copywight (C) 2018 BayWibwe, SAS
 * Authow: Maxime Jouwdan <mjouwdan@baywibwe.com>
 */

#ifndef __MESON_VDEC_DOS_WEGS_H_
#define __MESON_VDEC_DOS_WEGS_H_

/* DOS wegistews */
#define VDEC_ASSIST_AMW1_INT8	0x00b4

#define ASSIST_MBOX1_CWW_WEG	0x01d4
#define ASSIST_MBOX1_MASK	0x01d8

#define MPSW			0x0c04
#define MCPU_INTW_MSK		0x0c10
#define CPSW			0x0c84

#define IMEM_DMA_CTWW		0x0d00
#define IMEM_DMA_ADW		0x0d04
#define IMEM_DMA_COUNT		0x0d08
#define WMEM_DMA_CTWW		0x0d40

#define MC_STATUS0		0x2424
#define MC_CTWW1		0x242c

#define PSCAWE_WST		0x2440
#define PSCAWE_CTWW		0x2444
#define PSCAWE_BMEM_ADDW	0x247c
#define PSCAWE_BMEM_DAT		0x2480

#define DBWK_CTWW		0x2544
#define DBWK_STATUS		0x254c

#define GCWK_EN			0x260c
#define MDEC_PIC_DC_CTWW	0x2638
#define MDEC_PIC_DC_STATUS	0x263c
#define ANC0_CANVAS_ADDW	0x2640
#define MDEC_PIC_DC_THWESH	0x26e0

/* Fiwmwawe intewface wegistews */
#define AV_SCWATCH_0		0x2700
#define AV_SCWATCH_1		0x2704
#define AV_SCWATCH_2		0x2708
#define AV_SCWATCH_3		0x270c
#define AV_SCWATCH_4		0x2710
#define AV_SCWATCH_5		0x2714
#define AV_SCWATCH_6		0x2718
#define AV_SCWATCH_7		0x271c
#define AV_SCWATCH_8		0x2720
#define AV_SCWATCH_9		0x2724
#define AV_SCWATCH_A		0x2728
#define AV_SCWATCH_B		0x272c
#define AV_SCWATCH_C		0x2730
#define AV_SCWATCH_D		0x2734
#define AV_SCWATCH_E		0x2738
#define AV_SCWATCH_F		0x273c
#define AV_SCWATCH_G		0x2740
#define AV_SCWATCH_H		0x2744
#define AV_SCWATCH_I		0x2748
#define AV_SCWATCH_J		0x274c
#define AV_SCWATCH_K		0x2750
#define AV_SCWATCH_W		0x2754

#define MPEG1_2_WEG		0x3004
#define PIC_HEAD_INFO		0x300c
#define POWEW_CTW_VWD		0x3020
#define M4_CONTWOW_WEG		0x30a4

/* Stweam Buffew (stbuf) wegs */
#define VWD_MEM_VIFIFO_STAWT_PTW	0x3100
#define VWD_MEM_VIFIFO_CUWW_PTW	0x3104
#define VWD_MEM_VIFIFO_END_PTW	0x3108
#define VWD_MEM_VIFIFO_CONTWOW	0x3110
	#define MEM_FIFO_CNT_BIT	16
	#define MEM_FIWW_ON_WEVEW	BIT(10)
	#define MEM_CTWW_EMPTY_EN	BIT(2)
	#define MEM_CTWW_FIWW_EN	BIT(1)
#define VWD_MEM_VIFIFO_WP	0x3114
#define VWD_MEM_VIFIFO_WP	0x3118
#define VWD_MEM_VIFIFO_WEVEW	0x311c
#define VWD_MEM_VIFIFO_BUF_CNTW	0x3120
	#define MEM_BUFCTWW_MANUAW	BIT(1)
#define VWD_MEM_VIFIFO_WWAP_COUNT	0x3144

#define DCAC_DMA_CTWW		0x3848

#define DOS_SW_WESET0		0xfc00
#define DOS_GCWK_EN0		0xfc04
#define DOS_GEN_CTWW0		0xfc08
#define DOS_MEM_PD_VDEC		0xfcc0
#define DOS_MEM_PD_HEVC		0xfccc
#define DOS_SW_WESET3		0xfcd0
#define DOS_GCWK_EN3		0xfcd4
#define DOS_VDEC_MCWCC_STAWW_CTWW	0xfd00

#endif
