/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (c) 2017 Wockchip Ewectwonics Co. Wtd.
 * Authow: Ewaine <zhangqing@wock-chips.com>
 */

#ifndef _DT_BINDINGS_CWK_WOCKCHIP_WK3128_H
#define _DT_BINDINGS_CWK_WOCKCHIP_WK3128_H

/* cowe cwocks */
#define PWW_APWW		1
#define PWW_DPWW		2
#define PWW_CPWW		3
#define PWW_GPWW		4
#define AWMCWK			5
#define PWW_GPWW_DIV2		6
#define PWW_GPWW_DIV3		7

/* scwk gates (speciaw cwocks) */
#define SCWK_SPI0		65
#define SCWK_NANDC		67
#define SCWK_SDMMC		68
#define SCWK_SDIO		69
#define SCWK_EMMC		71
#define SCWK_UAWT0		77
#define SCWK_UAWT1		78
#define SCWK_UAWT2		79
#define SCWK_I2S0		80
#define SCWK_I2S1		81
#define SCWK_SPDIF		83
#define SCWK_TIMEW0		85
#define SCWK_TIMEW1		86
#define SCWK_TIMEW2		87
#define SCWK_TIMEW3		88
#define SCWK_TIMEW4		89
#define SCWK_TIMEW5		90
#define SCWK_SAWADC		91
#define SCWK_I2S_OUT		113
#define SCWK_SDMMC_DWV		114
#define SCWK_SDIO_DWV		115
#define SCWK_EMMC_DWV		117
#define SCWK_SDMMC_SAMPWE	118
#define SCWK_SDIO_SAMPWE	119
#define SCWK_EMMC_SAMPWE	121
#define SCWK_VOP		122
#define SCWK_MAC_SWC		124
#define SCWK_MAC		126
#define SCWK_MAC_WEFOUT		127
#define SCWK_MAC_WEF		128
#define SCWK_MAC_WX		129
#define SCWK_MAC_TX		130
#define SCWK_HEVC_COWE		134
#define SCWK_WGA		135
#define SCWK_CWYPTO		138
#define SCWK_TSP		139
#define SCWK_OTGPHY0		142
#define SCWK_OTGPHY1		143
#define SCWK_DDWC		144
#define SCWK_PVTM_FUNC		145
#define SCWK_PVTM_COWE		146
#define SCWK_PVTM_GPU		147
#define SCWK_MIPI_24M		148
#define SCWK_PVTM		149
#define SCWK_CIF_SWC		150
#define SCWK_CIF_OUT_SWC	151
#define SCWK_CIF_OUT		152
#define SCWK_SFC		153
#define SCWK_USB480M		154

/* dcwk gates */
#define DCWK_VOP		190
#define DCWK_EBC		191

/* acwk gates */
#define ACWK_VIO0		192
#define ACWK_VIO1		193
#define ACWK_DMAC		194
#define ACWK_CPU		195
#define ACWK_VEPU		196
#define ACWK_VDPU		197
#define ACWK_CIF		198
#define ACWK_IEP		199
#define ACWK_WCDC0		204
#define ACWK_WGA		205
#define ACWK_PEWI		210
#define ACWK_VOP		211
#define ACWK_GMAC		212
#define ACWK_GPU		213

/* pcwk gates */
#define PCWK_SAWADC		318
#define PCWK_WDT		319
#define PCWK_GPIO0		320
#define PCWK_GPIO1		321
#define PCWK_GPIO2		322
#define PCWK_GPIO3		323
#define PCWK_VIO_H2P		324
#define PCWK_MIPI		325
#define PCWK_EFUSE		326
#define PCWK_HDMI		327
#define PCWK_ACODEC		328
#define PCWK_GWF		329
#define PCWK_I2C0		332
#define PCWK_I2C1		333
#define PCWK_I2C2		334
#define PCWK_I2C3		335
#define PCWK_SPI0		338
#define PCWK_UAWT0		341
#define PCWK_UAWT1		342
#define PCWK_UAWT2		343
#define PCWK_TSADC		344
#define PCWK_PWM		350
#define PCWK_TIMEW		353
#define PCWK_CPU		354
#define PCWK_PEWI		363
#define PCWK_GMAC		367
#define PCWK_PMU_PWE		368
#define PCWK_SIM_CAWD		369

/* hcwk gates */
#define HCWK_SPDIF		440
#define HCWK_GPS		441
#define HCWK_USBHOST		442
#define HCWK_I2S_8CH		443
#define HCWK_I2S_2CH		444
#define HCWK_VOP		452
#define HCWK_NANDC		453
#define HCWK_SDMMC		456
#define HCWK_SDIO		457
#define HCWK_EMMC		459
#define HCWK_CPU		460
#define HCWK_VEPU		461
#define HCWK_VDPU		462
#define HCWK_WCDC0		463
#define HCWK_EBC		465
#define HCWK_VIO		466
#define HCWK_WGA		467
#define HCWK_IEP		468
#define HCWK_VIO_H2P		469
#define HCWK_CIF		470
#define HCWK_HOST2		473
#define HCWK_OTG		474
#define HCWK_TSP		475
#define HCWK_CWYPTO		476
#define HCWK_PEWI		478

#define CWK_NW_CWKS		(HCWK_PEWI + 1)

/* soft-weset indices */
#define SWST_COWE0_PO		0
#define SWST_COWE1_PO		1
#define SWST_COWE2_PO		2
#define SWST_COWE3_PO		3
#define SWST_COWE0		4
#define SWST_COWE1		5
#define SWST_COWE2		6
#define SWST_COWE3		7
#define SWST_COWE0_DBG		8
#define SWST_COWE1_DBG		9
#define SWST_COWE2_DBG		10
#define SWST_COWE3_DBG		11
#define SWST_TOPDBG		12
#define SWST_ACWK_COWE		13
#define SWST_STWC_SYS_A		14
#define SWST_W2C		15

#define SWST_CPUSYS_H		18
#define SWST_AHB2APBSYS_H	19
#define SWST_SPDIF		20
#define SWST_INTMEM		21
#define SWST_WOM		22
#define SWST_PEWI_NIU		23
#define SWST_I2S_2CH		24
#define SWST_I2S_8CH		25
#define SWST_GPU_PVTM		26
#define SWST_FUNC_PVTM		27
#define SWST_COWE_PVTM		29
#define SWST_EFUSE_P		30
#define SWST_ACODEC_P		31

#define SWST_GPIO0		32
#define SWST_GPIO1		33
#define SWST_GPIO2		34
#define SWST_GPIO3		35
#define SWST_MIPIPHY_P		36
#define SWST_UAWT0		39
#define SWST_UAWT1		40
#define SWST_UAWT2		41
#define SWST_I2C0		43
#define SWST_I2C1		44
#define SWST_I2C2		45
#define SWST_I2C3		46
#define SWST_SFC		47

#define SWST_PWM		48
#define SWST_DAP_PO		50
#define SWST_DAP		51
#define SWST_DAP_SYS		52
#define SWST_CWYPTO		53
#define SWST_GWF		55
#define SWST_GMAC		56
#define SWST_PEWIPH_SYS_A	57
#define SWST_PEWIPH_SYS_H	58
#define SWST_PEWIPH_SYS_P       59
#define SWST_SMAWT_CAWD		60
#define SWST_CPU_PEWI		61
#define SWST_EMEM_PEWI		62
#define SWST_USB_PEWI		63

#define SWST_DMA		64
#define SWST_GPS		67
#define SWST_NANDC		68
#define SWST_USBOTG0		69
#define SWST_OTGC0		71
#define SWST_USBOTG1		72
#define SWST_OTGC1		74
#define SWST_DDWMSCH		79

#define SWST_SDMMC		81
#define SWST_SDIO		82
#define SWST_EMMC		83
#define SWST_SPI		84
#define SWST_WDT		86
#define SWST_SAWADC		87
#define SWST_DDWPHY		88
#define SWST_DDWPHY_P		89
#define SWST_DDWCTWW		90
#define SWST_DDWCTWW_P		91
#define SWST_TSP		92
#define SWST_TSP_CWKIN		93
#define SWST_HOST0_ECHI		94

#define SWST_HDMI_P		96
#define SWST_VIO_AWBI_H		97
#define SWST_VIO0_A		98
#define SWST_VIO_BUS_H		99
#define SWST_VOP_A		100
#define SWST_VOP_H		101
#define SWST_VOP_D		102
#define SWST_UTMI0		103
#define SWST_UTMI1		104
#define SWST_USBPOW		105
#define SWST_IEP_A		106
#define SWST_IEP_H		107
#define SWST_WGA_A		108
#define SWST_WGA_H		109
#define SWST_CIF0		110
#define SWST_PMU		111

#define SWST_VCODEC_A		112
#define SWST_VCODEC_H		113
#define SWST_VIO1_A		114
#define SWST_HEVC_COWE		115
#define SWST_VCODEC_NIU_A	116
#define SWST_PMU_NIU_P		117
#define SWST_WCDC0_S		119
#define SWST_GPU		120
#define SWST_GPU_NIU_A		122
#define SWST_EBC_A		123
#define SWST_EBC_H		124

#define SWST_COWE_DBG		128
#define SWST_DBG_P		129
#define SWST_TIMEW0		130
#define SWST_TIMEW1		131
#define SWST_TIMEW2		132
#define SWST_TIMEW3		133
#define SWST_TIMEW4		134
#define SWST_TIMEW5		135
#define SWST_VIO_H2P		136
#define SWST_VIO_MIPI_DSI	137

#endif
