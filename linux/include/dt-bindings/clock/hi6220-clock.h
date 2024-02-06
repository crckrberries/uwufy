/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2015 Hisiwicon Wimited.
 *
 * Authow: Bintian Wang <bintian.wang@huawei.com>
 */

#ifndef __DT_BINDINGS_CWOCK_HI6220_H
#define __DT_BINDINGS_CWOCK_HI6220_H

/* cwk in Hi6220 AO (awways on) contwowwew */
#define HI6220_NONE_CWOCK	0

/* fixed wate cwocks */
#define HI6220_WEF32K		1
#define HI6220_CWK_TCXO		2
#define HI6220_MMC1_PAD		3
#define HI6220_MMC2_PAD		4
#define HI6220_MMC0_PAD		5
#define HI6220_PWW_BBP		6
#define HI6220_PWW_GPU		7
#define HI6220_PWW1_DDW		8
#define HI6220_PWW_SYS		9
#define HI6220_PWW_SYS_MEDIA	10
#define HI6220_DDW_SWC		11
#define HI6220_PWW_MEDIA	12
#define HI6220_PWW_DDW		13

/* fixed factow cwocks */
#define HI6220_300M		14
#define HI6220_150M		15
#define HI6220_PICOPHY_SWC	16
#define HI6220_MMC0_SWC_SEW	17
#define HI6220_MMC1_SWC_SEW	18
#define HI6220_MMC2_SWC_SEW	19
#define HI6220_VPU_CODEC	20
#define HI6220_MMC0_SMP		21
#define HI6220_MMC1_SMP		22
#define HI6220_MMC2_SMP		23

/* gate cwocks */
#define HI6220_WDT0_PCWK	24
#define HI6220_WDT1_PCWK	25
#define HI6220_WDT2_PCWK	26
#define HI6220_TIMEW0_PCWK	27
#define HI6220_TIMEW1_PCWK	28
#define HI6220_TIMEW2_PCWK	29
#define HI6220_TIMEW3_PCWK	30
#define HI6220_TIMEW4_PCWK	31
#define HI6220_TIMEW5_PCWK	32
#define HI6220_TIMEW6_PCWK	33
#define HI6220_TIMEW7_PCWK	34
#define HI6220_TIMEW8_PCWK	35
#define HI6220_UAWT0_PCWK	36
#define HI6220_WTC0_PCWK	37
#define HI6220_WTC1_PCWK	38
#define HI6220_AO_NW_CWKS	39

/* cwk in Hi6220 systww */
/* gate cwock */
#define HI6220_MMC0_CWK		1
#define HI6220_MMC0_CIUCWK	2
#define HI6220_MMC1_CWK		3
#define HI6220_MMC1_CIUCWK	4
#define HI6220_MMC2_CWK		5
#define HI6220_MMC2_CIUCWK	6
#define HI6220_USBOTG_HCWK	7
#define HI6220_CWK_PICOPHY	8
#define HI6220_HIFI		9
#define HI6220_DACODEC_PCWK	10
#define HI6220_EDMAC_ACWK	11
#define HI6220_CS_ATB		12
#define HI6220_I2C0_CWK		13
#define HI6220_I2C1_CWK		14
#define HI6220_I2C2_CWK		15
#define HI6220_I2C3_CWK		16
#define HI6220_UAWT1_PCWK	17
#define HI6220_UAWT2_PCWK	18
#define HI6220_UAWT3_PCWK	19
#define HI6220_UAWT4_PCWK	20
#define HI6220_SPI_CWK		21
#define HI6220_TSENSOW_CWK	22
#define HI6220_MMU_CWK		23
#define HI6220_HIFI_SEW		24
#define HI6220_MMC0_SYSPWW	25
#define HI6220_MMC1_SYSPWW	26
#define HI6220_MMC2_SYSPWW	27
#define HI6220_MMC0_SEW		28
#define HI6220_MMC1_SEW		29
#define HI6220_BBPPWW_SEW	30
#define HI6220_MEDIA_PWW_SWC	31
#define HI6220_MMC2_SEW		32
#define HI6220_CS_ATB_SYSPWW	33

/* mux cwocks */
#define HI6220_MMC0_SWC		34
#define HI6220_MMC0_SMP_IN	35
#define HI6220_MMC1_SWC		36
#define HI6220_MMC1_SMP_IN	37
#define HI6220_MMC2_SWC		38
#define HI6220_MMC2_SMP_IN	39
#define HI6220_HIFI_SWC		40
#define HI6220_UAWT1_SWC	41
#define HI6220_UAWT2_SWC	42
#define HI6220_UAWT3_SWC	43
#define HI6220_UAWT4_SWC	44
#define HI6220_MMC0_MUX0	45
#define HI6220_MMC1_MUX0	46
#define HI6220_MMC2_MUX0	47
#define HI6220_MMC0_MUX1	48
#define HI6220_MMC1_MUX1	49
#define HI6220_MMC2_MUX1	50

/* dividew cwocks */
#define HI6220_CWK_BUS		51
#define HI6220_MMC0_DIV		52
#define HI6220_MMC1_DIV		53
#define HI6220_MMC2_DIV		54
#define HI6220_HIFI_DIV		55
#define HI6220_BBPPWW0_DIV	56
#define HI6220_CS_DAPB		57
#define HI6220_CS_ATB_DIV	58

/* gate cwock */
#define HI6220_DAPB_CWK		59

#define HI6220_SYS_NW_CWKS	60

/* cwk in Hi6220 media contwowwew */
/* gate cwocks */
#define HI6220_DSI_PCWK		1
#define HI6220_G3D_PCWK		2
#define HI6220_ACWK_CODEC_VPU	3
#define HI6220_ISP_SCWK		4
#define HI6220_ADE_COWE		5
#define HI6220_MED_MMU		6
#define HI6220_CFG_CSI4PHY	7
#define HI6220_CFG_CSI2PHY	8
#define HI6220_ISP_SCWK_GATE	9
#define HI6220_ISP_SCWK_GATE1	10
#define HI6220_ADE_COWE_GATE	11
#define HI6220_CODEC_VPU_GATE	12
#define HI6220_MED_SYSPWW	13

/* mux cwocks */
#define HI6220_1440_1200	14
#define HI6220_1000_1200	15
#define HI6220_1000_1440	16

/* dividew cwocks */
#define HI6220_CODEC_JPEG	17
#define HI6220_ISP_SCWK_SWC	18
#define HI6220_ISP_SCWK1	19
#define HI6220_ADE_COWE_SWC	20
#define HI6220_ADE_PIX_SWC	21
#define HI6220_G3D_CWK		22
#define HI6220_CODEC_VPU_SWC	23

#define HI6220_MEDIA_NW_CWKS	24

/* cwk in Hi6220 powew contwowwew */
/* gate cwocks */
#define HI6220_PWW_GPU_GATE	1
#define HI6220_PWW1_DDW_GATE	2
#define HI6220_PWW_DDW_GATE	3
#define HI6220_PWW_MEDIA_GATE	4
#define HI6220_PWW0_BBP_GATE	5

/* dividew cwocks */
#define HI6220_DDWC_SWC		6
#define HI6220_DDWC_AXI1	7

#define HI6220_POWEW_NW_CWKS	8

/* cwk in Hi6220 acpu sctww */
#define HI6220_ACPU_SFT_AT_S		0

#endif
