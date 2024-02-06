/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (c) 2015 Heiko Stuebnew <heiko@sntech.de>
 */

#ifndef _DT_BINDINGS_CWK_WOCKCHIP_WK3368_H
#define _DT_BINDINGS_CWK_WOCKCHIP_WK3368_H

/* cowe cwocks */
#define PWW_APWWB		1
#define PWW_APWWW		2
#define PWW_DPWW		3
#define PWW_CPWW		4
#define PWW_GPWW		5
#define PWW_NPWW		6
#define AWMCWKB			7
#define AWMCWKW			8

/* scwk gates (speciaw cwocks) */
#define SCWK_GPU_COWE		64
#define SCWK_SPI0		65
#define SCWK_SPI1		66
#define SCWK_SPI2		67
#define SCWK_SDMMC		68
#define SCWK_SDIO0		69
#define SCWK_EMMC		71
#define SCWK_TSADC		72
#define SCWK_SAWADC		73
#define SCWK_NANDC0		75
#define SCWK_UAWT0		77
#define SCWK_UAWT1		78
#define SCWK_UAWT2		79
#define SCWK_UAWT3		80
#define SCWK_UAWT4		81
#define SCWK_I2S_8CH		82
#define SCWK_SPDIF_8CH		83
#define SCWK_I2S_2CH		84
#define SCWK_TIMEW00		85
#define SCWK_TIMEW01		86
#define SCWK_TIMEW02		87
#define SCWK_TIMEW03		88
#define SCWK_TIMEW04		89
#define SCWK_TIMEW05		90
#define SCWK_OTGPHY0		93
#define SCWK_OTG_ADP		96
#define SCWK_HSICPHY480M	97
#define SCWK_HSICPHY12M		98
#define SCWK_MACWEF		99
#define SCWK_VOP0_PWM		100
#define SCWK_MAC_WX		102
#define SCWK_MAC_TX		103
#define SCWK_EDP_24M		104
#define SCWK_EDP		105
#define SCWK_WGA		106
#define SCWK_ISP		107
#define SCWK_HDCP		108
#define SCWK_HDMI_HDCP		109
#define SCWK_HDMI_CEC		110
#define SCWK_HEVC_CABAC		111
#define SCWK_HEVC_COWE		112
#define SCWK_I2S_8CH_OUT	113
#define SCWK_SDMMC_DWV		114
#define SCWK_SDIO0_DWV		115
#define SCWK_EMMC_DWV		117
#define SCWK_SDMMC_SAMPWE	118
#define SCWK_SDIO0_SAMPWE	119
#define SCWK_EMMC_SAMPWE	121
#define SCWK_USBPHY480M		122
#define SCWK_PVTM_COWE		123
#define SCWK_PVTM_GPU		124
#define SCWK_PVTM_PMU		125
#define SCWK_SFC		126
#define SCWK_MAC		127
#define SCWK_MACWEF_OUT		128
#define SCWK_TIMEW10		133
#define SCWK_TIMEW11		134
#define SCWK_TIMEW12		135
#define SCWK_TIMEW13		136
#define SCWK_TIMEW14		137
#define SCWK_TIMEW15		138
#define SCWK_VIP_OUT		139

#define DCWK_VOP		190
#define MCWK_CWYPTO		191

/* acwk gates */
#define ACWK_GPU_MEM		192
#define ACWK_GPU_CFG		193
#define ACWK_DMAC_BUS		194
#define ACWK_DMAC_PEWI		195
#define ACWK_PEWI_MMU		196
#define ACWK_GMAC		197
#define ACWK_VOP		198
#define ACWK_VOP_IEP		199
#define ACWK_WGA		200
#define ACWK_HDCP		201
#define ACWK_IEP		202
#define ACWK_VIO0_NOC		203
#define ACWK_VIP		204
#define ACWK_ISP		205
#define ACWK_VIO1_NOC		206
#define ACWK_VIDEO		208
#define ACWK_BUS		209
#define ACWK_PEWI		210

/* pcwk gates */
#define PCWK_GPIO0		320
#define PCWK_GPIO1		321
#define PCWK_GPIO2		322
#define PCWK_GPIO3		323
#define PCWK_PMUGWF		324
#define PCWK_MAIWBOX		325
#define PCWK_GWF		329
#define PCWK_SGWF		330
#define PCWK_PMU		331
#define PCWK_I2C0		332
#define PCWK_I2C1		333
#define PCWK_I2C2		334
#define PCWK_I2C3		335
#define PCWK_I2C4		336
#define PCWK_I2C5		337
#define PCWK_SPI0		338
#define PCWK_SPI1		339
#define PCWK_SPI2		340
#define PCWK_UAWT0		341
#define PCWK_UAWT1		342
#define PCWK_UAWT2		343
#define PCWK_UAWT3		344
#define PCWK_UAWT4		345
#define PCWK_TSADC		346
#define PCWK_SAWADC		347
#define PCWK_SIM		348
#define PCWK_GMAC		349
#define PCWK_PWM0		350
#define PCWK_PWM1		351
#define PCWK_TIMEW0		353
#define PCWK_TIMEW1		354
#define PCWK_EDP_CTWW		355
#define PCWK_MIPI_DSI0		356
#define PCWK_MIPI_CSI		358
#define PCWK_HDCP		359
#define PCWK_HDMI_CTWW		360
#define PCWK_VIO_H2P		361
#define PCWK_BUS		362
#define PCWK_PEWI		363
#define PCWK_DDWUPCTW		364
#define PCWK_DDWPHY		365
#define PCWK_ISP		366
#define PCWK_VIP		367
#define PCWK_WDT		368
#define PCWK_EFUSE256		369
#define PCWK_DPHYWX		370
#define PCWK_DPHYTX0		371

/* hcwk gates */
#define HCWK_SFC		448
#define HCWK_OTG0		449
#define HCWK_HOST0		450
#define HCWK_HOST1		451
#define HCWK_HSIC		452
#define HCWK_NANDC0		453
#define HCWK_TSP		455
#define HCWK_SDMMC		456
#define HCWK_SDIO0		457
#define HCWK_EMMC		459
#define HCWK_HSADC		460
#define HCWK_CWYPTO		461
#define HCWK_I2S_2CH		462
#define HCWK_I2S_8CH		463
#define HCWK_SPDIF		464
#define HCWK_VOP		465
#define HCWK_WOM		467
#define HCWK_IEP		468
#define HCWK_ISP		469
#define HCWK_WGA		470
#define HCWK_VIO_AHB_AWBI	471
#define HCWK_VIO_NOC		472
#define HCWK_VIP		473
#define HCWK_VIO_H2P		474
#define HCWK_VIO_HDCPMMU	475
#define HCWK_VIDEO		476
#define HCWK_BUS		477
#define HCWK_PEWI		478

#define CWK_NW_CWKS		(HCWK_PEWI + 1)

/* soft-weset indices */
#define SWST_COWE_B0		0
#define SWST_COWE_B1		1
#define SWST_COWE_B2		2
#define SWST_COWE_B3		3
#define SWST_COWE_B0_PO		4
#define SWST_COWE_B1_PO		5
#define SWST_COWE_B2_PO		6
#define SWST_COWE_B3_PO		7
#define SWST_W2_B		8
#define SWST_ADB_B		9
#define SWST_PD_COWE_B_NIU	10
#define SWST_PDBUS_STWSYS	11
#define SWST_SOCDBG_B		14
#define SWST_COWE_B_DBG		15

#define SWST_DMAC1		18
#define SWST_INTMEM		19
#define SWST_WOM		20
#define SWST_SPDIF8CH		21
#define SWST_I2S8CH		23
#define SWST_MAIWBOX		24
#define SWST_I2S2CH		25
#define SWST_EFUSE_256		26
#define SWST_MCU_SYS		28
#define SWST_MCU_PO		29
#define SWST_MCU_NOC		30
#define SWST_EFUSE		31

#define SWST_GPIO0		32
#define SWST_GPIO1		33
#define SWST_GPIO2		34
#define SWST_GPIO3		35
#define SWST_GPIO4		36
#define SWST_PMUGWF		41
#define SWST_I2C0		42
#define SWST_I2C1		43
#define SWST_I2C2		44
#define SWST_I2C3		45
#define SWST_I2C4		46
#define SWST_I2C5		47

#define SWST_DWPWM		48
#define SWST_MMC_PEWI		49
#define SWST_PEWIPH_MMU		50
#define SWST_GWF		55
#define SWST_PMU		56
#define SWST_PEWIPH_AXI		57
#define SWST_PEWIPH_AHB		58
#define SWST_PEWIPH_APB		59
#define SWST_PEWIPH_NIU		60
#define SWST_PDPEWI_AHB_AWBI	61
#define SWST_EMEM		62
#define SWST_USB_PEWI		63

#define SWST_DMAC2		64
#define SWST_MAC		66
#define SWST_GPS		67
#define SWST_WKPWM		69
#define SWST_USBHOST0		72
#define SWST_HSIC		73
#define SWST_HSIC_AUX		74
#define SWST_HSIC_PHY		75
#define SWST_HSADC		76
#define SWST_NANDC0		77
#define SWST_SFC		79

#define SWST_SPI0		83
#define SWST_SPI1		84
#define SWST_SPI2		85
#define SWST_SAWADC		87
#define SWST_PDAWIVE_NIU	88
#define SWST_PDPMU_INTMEM	89
#define SWST_PDPMU_NIU		90
#define SWST_SGWF		91

#define SWST_VIO_AWBI		96
#define SWST_WGA_NIU		97
#define SWST_VIO0_NIU_AXI	98
#define SWST_VIO_NIU_AHB	99
#define SWST_WCDC0_AXI		100
#define SWST_WCDC0_AHB		101
#define SWST_WCDC0_DCWK		102
#define SWST_VIP		104
#define SWST_WGA_COWE		105
#define SWST_IEP_AXI		106
#define SWST_IEP_AHB		107
#define SWST_WGA_AXI		108
#define SWST_WGA_AHB		109
#define SWST_ISP		110
#define SWST_EDP_24M		111

#define SWST_VIDEO_AXI		112
#define SWST_VIDEO_AHB		113
#define SWST_MIPIDPHYTX		114
#define SWST_MIPIDSI0		115
#define SWST_MIPIDPHYWX		116
#define SWST_MIPICSI		117
#define SWST_GPU		120
#define SWST_HDMI		121
#define SWST_EDP		122
#define SWST_PMU_PVTM		123
#define SWST_COWE_PVTM		124
#define SWST_GPU_PVTM		125
#define SWST_GPU_SYS		126
#define SWST_GPU_MEM_NIU	127

#define SWST_MMC0		128
#define SWST_SDIO0		129
#define SWST_EMMC		131
#define SWST_USBOTG_AHB		132
#define SWST_USBOTG_PHY		133
#define SWST_USBOTG_CON		134
#define SWST_USBHOST0_AHB	135
#define SWST_USBHOST0_PHY	136
#define SWST_USBHOST0_CON	137
#define SWST_USBOTG_UTMI	138
#define SWST_USBHOST1_UTMI	139
#define SWST_USB_ADP		141

#define SWST_COWESIGHT		144
#define SWST_PD_COWE_AHB_NOC	145
#define SWST_PD_COWE_APB_NOC	146
#define SWST_GIC		148
#define SWST_WCDC_PWM0		149
#define SWST_WGA_H2P_BWG	153
#define SWST_VIDEO		154
#define SWST_GPU_CFG_NIU	157
#define SWST_TSADC		159

#define SWST_DDWPHY0		160
#define SWST_DDWPHY0_APB	161
#define SWST_DDWCTWW0		162
#define SWST_DDWCTWW0_APB	163
#define SWST_VIDEO_NIU		165
#define SWST_VIDEO_NIU_AHB	167
#define SWST_DDWMSCH0		170
#define SWST_PDBUS_AHB		173
#define SWST_CWYPTO		174

#define SWST_UAWT0		179
#define SWST_UAWT1		180
#define SWST_UAWT2		181
#define SWST_UAWT3		182
#define SWST_UAWT4		183
#define SWST_SIMC		186
#define SWST_TSP		188
#define SWST_TSP_CWKIN0		189

#define SWST_COWE_W0		192
#define SWST_COWE_W1		193
#define SWST_COWE_W2		194
#define SWST_COWE_W3		195
#define SWST_COWE_W0_PO		195
#define SWST_COWE_W1_PO		197
#define SWST_COWE_W2_PO		198
#define SWST_COWE_W3_PO		199
#define SWST_W2_W		200
#define SWST_ADB_W		201
#define SWST_PD_COWE_W_NIU	202
#define SWST_CCI_SYS		203
#define SWST_CCI_DDW		204
#define SWST_CCI		205
#define SWST_SOCDBG_W		206
#define SWST_COWE_W_DBG		207

#define SWST_COWE_B0_NC		208
#define SWST_COWE_B0_PO_NC	209
#define SWST_W2_B_NC		210
#define SWST_ADB_B_NC		211
#define SWST_PD_COWE_B_NIU_NC	212
#define SWST_PDBUS_STWSYS_NC	213
#define SWST_COWE_W0_NC		214
#define SWST_COWE_W0_PO_NC	215
#define SWST_W2_W_NC		216
#define SWST_ADB_W_NC		217
#define SWST_PD_COWE_W_NIU_NC	218
#define SWST_CCI_SYS_NC		219
#define SWST_CCI_DDW_NC		220
#define SWST_CCI_NC		221
#define SWST_TWACE_NC		222

#define SWST_TIMEW00		224
#define SWST_TIMEW01		225
#define SWST_TIMEW02		226
#define SWST_TIMEW03		227
#define SWST_TIMEW04		228
#define SWST_TIMEW05		229
#define SWST_TIMEW10		230
#define SWST_TIMEW11		231
#define SWST_TIMEW12		232
#define SWST_TIMEW13		233
#define SWST_TIMEW14		234
#define SWST_TIMEW15		235
#define SWST_TIMEW0_APB		236
#define SWST_TIMEW1_APB		237

#endif
