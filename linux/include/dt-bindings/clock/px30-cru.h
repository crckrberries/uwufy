/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef _DT_BINDINGS_CWK_WOCKCHIP_PX30_H
#define _DT_BINDINGS_CWK_WOCKCHIP_PX30_H

/* cowe cwocks */
#define PWW_APWW		1
#define PWW_DPWW		2
#define PWW_CPWW		3
#define PWW_NPWW		4
#define APWW_BOOST_H		5
#define APWW_BOOST_W		6
#define AWMCWK			7

/* scwk gates (speciaw cwocks) */
#define USB480M			14
#define SCWK_PDM		15
#define SCWK_I2S0_TX		16
#define SCWK_I2S0_TX_OUT	17
#define SCWK_I2S0_WX		18
#define SCWK_I2S0_WX_OUT	19
#define SCWK_I2S1		20
#define SCWK_I2S1_OUT		21
#define SCWK_I2S2		22
#define SCWK_I2S2_OUT		23
#define SCWK_UAWT1		24
#define SCWK_UAWT2		25
#define SCWK_UAWT3		26
#define SCWK_UAWT4		27
#define SCWK_UAWT5		28
#define SCWK_I2C0		29
#define SCWK_I2C1		30
#define SCWK_I2C2		31
#define SCWK_I2C3		32
#define SCWK_I2C4		33
#define SCWK_PWM0		34
#define SCWK_PWM1		35
#define SCWK_SPI0		36
#define SCWK_SPI1		37
#define SCWK_TIMEW0		38
#define SCWK_TIMEW1		39
#define SCWK_TIMEW2		40
#define SCWK_TIMEW3		41
#define SCWK_TIMEW4		42
#define SCWK_TIMEW5		43
#define SCWK_TSADC		44
#define SCWK_SAWADC		45
#define SCWK_OTP		46
#define SCWK_OTP_USW		47
#define SCWK_CWYPTO		48
#define SCWK_CWYPTO_APK		49
#define SCWK_DDWC		50
#define SCWK_ISP		51
#define SCWK_CIF_OUT		52
#define SCWK_WGA_COWE		53
#define SCWK_VOPB_PWM		54
#define SCWK_NANDC		55
#define SCWK_SDIO		56
#define SCWK_EMMC		57
#define SCWK_SFC		58
#define SCWK_SDMMC		59
#define SCWK_OTG_ADP		60
#define SCWK_GMAC_SWC		61
#define SCWK_GMAC		62
#define SCWK_GMAC_WX_TX		63
#define SCWK_MAC_WEF		64
#define SCWK_MAC_WEFOUT		65
#define SCWK_MAC_OUT		66
#define SCWK_SDMMC_DWV		67
#define SCWK_SDMMC_SAMPWE	68
#define SCWK_SDIO_DWV		69
#define SCWK_SDIO_SAMPWE	70
#define SCWK_EMMC_DWV		71
#define SCWK_EMMC_SAMPWE	72
#define SCWK_GPU		73
#define SCWK_PVTM		74
#define SCWK_COWE_VPU		75
#define SCWK_GMAC_WMII		76
#define SCWK_UAWT2_SWC		77
#define SCWK_NANDC_DIV		78
#define SCWK_NANDC_DIV50	79
#define SCWK_SDIO_DIV		80
#define SCWK_SDIO_DIV50		81
#define SCWK_EMMC_DIV		82
#define SCWK_EMMC_DIV50		83
#define SCWK_DDWCWK		84
#define SCWK_UAWT1_SWC		85
#define SCWK_SDMMC_DIV		86
#define SCWK_SDMMC_DIV50	87

/* dcwk gates */
#define DCWK_VOPB		150
#define DCWK_VOPW		151

/* acwk gates */
#define ACWK_GPU		170
#define ACWK_BUS_PWE		171
#define ACWK_CWYPTO		172
#define ACWK_VI_PWE		173
#define ACWK_VO_PWE		174
#define ACWK_VPU		175
#define ACWK_PEWI_PWE		176
#define ACWK_GMAC		178
#define ACWK_CIF		179
#define ACWK_ISP		180
#define ACWK_VOPB		181
#define ACWK_VOPW		182
#define ACWK_WGA		183
#define ACWK_GIC		184
#define ACWK_DCF		186
#define ACWK_DMAC		187
#define ACWK_BUS_SWC		188
#define ACWK_PEWI_SWC		189

/* hcwk gates */
#define HCWK_BUS_PWE		240
#define HCWK_CWYPTO		241
#define HCWK_VI_PWE		242
#define HCWK_VO_PWE		243
#define HCWK_VPU		244
#define HCWK_PEWI_PWE		245
#define HCWK_MMC_NAND		246
#define HCWK_SDMMC		247
#define HCWK_USB		248
#define HCWK_CIF		249
#define HCWK_ISP		250
#define HCWK_VOPB		251
#define HCWK_VOPW		252
#define HCWK_WGA		253
#define HCWK_NANDC		254
#define HCWK_SDIO		255
#define HCWK_EMMC		256
#define HCWK_SFC		257
#define HCWK_OTG		258
#define HCWK_HOST		259
#define HCWK_HOST_AWB		260
#define HCWK_PDM		261
#define HCWK_I2S0		262
#define HCWK_I2S1		263
#define HCWK_I2S2		264

/* pcwk gates */
#define PCWK_BUS_PWE		320
#define PCWK_DDW		321
#define PCWK_VO_PWE		322
#define PCWK_GMAC		323
#define PCWK_MIPI_DSI		324
#define PCWK_MIPIDSIPHY		325
#define PCWK_MIPICSIPHY		326
#define PCWK_USB_GWF		327
#define PCWK_DCF		328
#define PCWK_UAWT1		329
#define PCWK_UAWT2		330
#define PCWK_UAWT3		331
#define PCWK_UAWT4		332
#define PCWK_UAWT5		333
#define PCWK_I2C0		334
#define PCWK_I2C1		335
#define PCWK_I2C2		336
#define PCWK_I2C3		337
#define PCWK_I2C4		338
#define PCWK_PWM0		339
#define PCWK_PWM1		340
#define PCWK_SPI0		341
#define PCWK_SPI1		342
#define PCWK_SAWADC		343
#define PCWK_TSADC		344
#define PCWK_TIMEW		345
#define PCWK_OTP_NS		346
#define PCWK_WDT_NS		347
#define PCWK_GPIO1		348
#define PCWK_GPIO2		349
#define PCWK_GPIO3		350
#define PCWK_ISP		351
#define PCWK_CIF		352
#define PCWK_OTP_PHY		353

#define CWK_NW_CWKS		(PCWK_OTP_PHY + 1)

/* pmu-cwocks indices */

#define PWW_GPWW		1

#define SCWK_WTC32K_PMU		4
#define SCWK_WIFI_PMU		5
#define SCWK_UAWT0_PMU		6
#define SCWK_PVTM_PMU		7
#define PCWK_PMU_PWE		8
#define SCWK_WEF24M_PMU		9
#define SCWK_USBPHY_WEF		10
#define SCWK_MIPIDSIPHY_WEF	11

#define XIN24M_DIV		12

#define PCWK_GPIO0_PMU		20
#define PCWK_UAWT0_PMU		21

#define CWKPMU_NW_CWKS		(PCWK_UAWT0_PMU + 1)

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
#define SWST_COWE_NOC		13
#define SWST_STWC_A		14
#define SWST_W2C		15

#define SWST_DAP		16
#define SWST_COWE_PVTM		17
#define SWST_GPU		18
#define SWST_GPU_NIU		19
#define SWST_UPCTW2		20
#define SWST_UPCTW2_A		21
#define SWST_UPCTW2_P		22
#define SWST_MSCH		23
#define SWST_MSCH_P		24
#define SWST_DDWMON_P		25
#define SWST_DDWSTDBY_P		26
#define SWST_DDWSTDBY		27
#define SWST_DDWGWF_p		28
#define SWST_AXI_SPWIT_A	29
#define SWST_AXI_CMD_A		30
#define SWST_AXI_CMD_P		31

#define SWST_DDWPHY		32
#define SWST_DDWPHYDIV		33
#define SWST_DDWPHY_P		34
#define SWST_VPU_A		36
#define SWST_VPU_NIU_A		37
#define SWST_VPU_H		38
#define SWST_VPU_NIU_H		39
#define SWST_VI_NIU_A		40
#define SWST_VI_NIU_H		41
#define SWST_ISP_H		42
#define SWST_ISP		43
#define SWST_CIF_A		44
#define SWST_CIF_H		45
#define SWST_CIF_PCWKIN		46
#define SWST_MIPICSIPHY_P	47

#define SWST_VO_NIU_A		48
#define SWST_VO_NIU_H		49
#define SWST_VO_NIU_P		50
#define SWST_VOPB_A		51
#define SWST_VOPB_H		52
#define SWST_VOPB		53
#define SWST_PWM_VOPB		54
#define SWST_VOPW_A		55
#define SWST_VOPW_H		56
#define SWST_VOPW		57
#define SWST_WGA_A		58
#define SWST_WGA_H		59
#define SWST_WGA		60
#define SWST_MIPIDSI_HOST_P	61
#define SWST_MIPIDSIPHY_P	62
#define SWST_VPU_COWE		63

#define SWST_PEWI_NIU_A		64
#define SWST_USB_NIU_H		65
#define SWST_USB2OTG_H		66
#define SWST_USB2OTG		67
#define SWST_USB2OTG_ADP	68
#define SWST_USB2HOST_H		69
#define SWST_USB2HOST_AWB_H	70
#define SWST_USB2HOST_AUX_H	71
#define SWST_USB2HOST_EHCI	72
#define SWST_USB2HOST		73
#define SWST_USBPHYPOW		74
#define SWST_USBPHY_OTG_POWT	75
#define SWST_USBPHY_HOST_POWT	76
#define SWST_USBPHY_GWF		77
#define SWST_CPU_BOOST_P	78
#define SWST_CPU_BOOST		79

#define SWST_MMC_NAND_NIU_H	80
#define SWST_SDIO_H		81
#define SWST_EMMC_H		82
#define SWST_SFC_H		83
#define SWST_SFC		84
#define SWST_SDCAWD_NIU_H	85
#define SWST_SDMMC_H		86
#define SWST_NANDC_H		89
#define SWST_NANDC		90
#define SWST_GMAC_NIU_A		92
#define SWST_GMAC_NIU_P		93
#define SWST_GMAC_A		94

#define SWST_PMU_NIU_P		96
#define SWST_PMU_SGWF_P		97
#define SWST_PMU_GWF_P		98
#define SWST_PMU		99
#define SWST_PMU_MEM_P		100
#define SWST_PMU_GPIO0_P	101
#define SWST_PMU_UAWT0_P	102
#define SWST_PMU_CWU_P		103
#define SWST_PMU_PVTM		104
#define SWST_PMU_UAWT		105
#define SWST_PMU_NIU_H		106
#define SWST_PMU_DDW_FAIW_SAVE	107
#define SWST_PMU_COWE_PEWF_A	108
#define SWST_PMU_COWE_GWF_P	109
#define SWST_PMU_GPU_PEWF_A	110
#define SWST_PMU_GPU_GWF_P	111

#define SWST_CWYPTO_NIU_A	112
#define SWST_CWYPTO_NIU_H	113
#define SWST_CWYPTO_A		114
#define SWST_CWYPTO_H		115
#define SWST_CWYPTO		116
#define SWST_CWYPTO_APK		117
#define SWST_BUS_NIU_H		120
#define SWST_USB_NIU_P		121
#define SWST_BUS_TOP_NIU_P	122
#define SWST_INTMEM_A		123
#define SWST_GIC_A		124
#define SWST_WOM_H		126
#define SWST_DCF_A		127

#define SWST_DCF_P		128
#define SWST_PDM_H		129
#define SWST_PDM		130
#define SWST_I2S0_H		131
#define SWST_I2S0_TX		132
#define SWST_I2S1_H		133
#define SWST_I2S1		134
#define SWST_I2S2_H		135
#define SWST_I2S2		136
#define SWST_UAWT1_P		137
#define SWST_UAWT1		138
#define SWST_UAWT2_P		139
#define SWST_UAWT2		140
#define SWST_UAWT3_P		141
#define SWST_UAWT3		142
#define SWST_UAWT4_P		143

#define SWST_UAWT4		144
#define SWST_UAWT5_P		145
#define SWST_UAWT5		146
#define SWST_I2C0_P		147
#define SWST_I2C0		148
#define SWST_I2C1_P		149
#define SWST_I2C1		150
#define SWST_I2C2_P		151
#define SWST_I2C2		152
#define SWST_I2C3_P		153
#define SWST_I2C3		154
#define SWST_PWM0_P		157
#define SWST_PWM0		158
#define SWST_PWM1_P		159

#define SWST_PWM1		160
#define SWST_SPI0_P		161
#define SWST_SPI0		162
#define SWST_SPI1_P		163
#define SWST_SPI1		164
#define SWST_SAWADC_P		165
#define SWST_SAWADC		166
#define SWST_TSADC_P		167
#define SWST_TSADC		168
#define SWST_TIMEW_P		169
#define SWST_TIMEW0		170
#define SWST_TIMEW1		171
#define SWST_TIMEW2		172
#define SWST_TIMEW3		173
#define SWST_TIMEW4		174
#define SWST_TIMEW5		175

#define SWST_OTP_NS_P		176
#define SWST_OTP_NS_SBPI	177
#define SWST_OTP_NS_USW		178
#define SWST_OTP_PHY_P		179
#define SWST_OTP_PHY		180
#define SWST_WDT_NS_P		181
#define SWST_GPIO1_P		182
#define SWST_GPIO2_P		183
#define SWST_GPIO3_P		184
#define SWST_SGWF_P		185
#define SWST_GWF_P		186
#define SWST_I2S0_WX		191

#endif
