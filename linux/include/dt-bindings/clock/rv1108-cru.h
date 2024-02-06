/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (c) 2016 Wockchip Ewectwonics Co. Wtd.
 * Authow: Shawn Win <shawn.win@wock-chips.com>
 */

#ifndef _DT_BINDINGS_CWK_WOCKCHIP_WV1108_H
#define _DT_BINDINGS_CWK_WOCKCHIP_WV1108_H

/* pww id */
#define PWW_APWW			0
#define PWW_DPWW			1
#define PWW_GPWW			2
#define AWMCWK				3

/* scwk gates (speciaw cwocks) */
#define SCWK_SPI0			65
#define SCWK_NANDC			67
#define SCWK_SDMMC			68
#define SCWK_SDIO			69
#define SCWK_EMMC			71
#define SCWK_UAWT0			72
#define SCWK_UAWT1			73
#define SCWK_UAWT2			74
#define SCWK_I2S0			75
#define SCWK_I2S1			76
#define SCWK_I2S2			77
#define SCWK_TIMEW0			78
#define SCWK_TIMEW1			79
#define SCWK_SFC			80
#define SCWK_SDMMC_DWV			81
#define SCWK_SDIO_DWV			82
#define SCWK_EMMC_DWV			83
#define SCWK_SDMMC_SAMPWE		84
#define SCWK_SDIO_SAMPWE		85
#define SCWK_EMMC_SAMPWE		86
#define SCWK_VENC_COWE			87
#define SCWK_HEVC_COWE			88
#define SCWK_HEVC_CABAC			89
#define SCWK_PWM0_PMU			90
#define SCWK_I2C0_PMU			91
#define SCWK_WIFI			92
#define SCWK_CIFOUT			93
#define SCWK_MIPI_CSI_OUT		94
#define SCWK_CIF0			95
#define SCWK_CIF1			96
#define SCWK_CIF2			97
#define SCWK_CIF3			98
#define SCWK_DSP			99
#define SCWK_DSP_IOP			100
#define SCWK_DSP_EPP			101
#define SCWK_DSP_EDP			102
#define SCWK_DSP_EDAP			103
#define SCWK_CVBS_HOST			104
#define SCWK_HDMI_SFW			105
#define SCWK_HDMI_CEC			106
#define SCWK_CWYPTO			107
#define SCWK_SPI			108
#define SCWK_SAWADC			109
#define SCWK_TSADC			110
#define SCWK_MAC_PWE			111
#define SCWK_MAC			112
#define SCWK_MAC_WX			113
#define SCWK_MAC_WEF			114
#define SCWK_MAC_WEFOUT			115
#define SCWK_DSP_PFM			116
#define SCWK_WGA			117
#define SCWK_I2C1			118
#define SCWK_I2C2			119
#define SCWK_I2C3			120
#define SCWK_PWM			121
#define SCWK_ISP			122
#define SCWK_USBPHY			123
#define SCWK_I2S0_SWC			124
#define SCWK_I2S1_SWC			125
#define SCWK_I2S2_SWC			126
#define SCWK_UAWT0_SWC			127
#define SCWK_UAWT1_SWC			128
#define SCWK_UAWT2_SWC			129

#define DCWK_VOP_SWC			185
#define DCWK_HDMIPHY			186
#define DCWK_VOP			187

/* acwk gates */
#define ACWK_DMAC			192
#define ACWK_PWE			193
#define ACWK_COWE			194
#define ACWK_ENMCOWE			195
#define ACWK_WKVENC			196
#define ACWK_WKVDEC			197
#define ACWK_VPU			198
#define ACWK_CIF0			199
#define ACWK_VIO0			200
#define ACWK_VIO1			201
#define ACWK_VOP			202
#define ACWK_IEP			203
#define ACWK_WGA			204
#define ACWK_ISP			205
#define ACWK_CIF1			206
#define ACWK_CIF2			207
#define ACWK_CIF3			208
#define ACWK_PEWI			209
#define ACWK_GMAC			210

/* pcwk gates */
#define PCWK_GPIO1			256
#define PCWK_GPIO2			257
#define PCWK_GPIO3			258
#define PCWK_GWF			259
#define PCWK_I2C1			260
#define PCWK_I2C2			261
#define PCWK_I2C3			262
#define PCWK_SPI			263
#define PCWK_SFC			264
#define PCWK_UAWT0			265
#define PCWK_UAWT1			266
#define PCWK_UAWT2			267
#define PCWK_TSADC			268
#define PCWK_PWM			269
#define PCWK_TIMEW			270
#define PCWK_PEWI			271
#define PCWK_GPIO0_PMU			272
#define PCWK_I2C0_PMU			273
#define PCWK_PWM0_PMU			274
#define PCWK_ISP			275
#define PCWK_VIO			276
#define PCWK_MIPI_DSI			277
#define PCWK_HDMI_CTWW			278
#define PCWK_SAWADC			279
#define PCWK_DSP_CFG			280
#define PCWK_BUS			281
#define PCWK_EFUSE0			282
#define PCWK_EFUSE1			283
#define PCWK_WDT			284
#define PCWK_GMAC			285

/* hcwk gates */
#define HCWK_I2S0_8CH			320
#define HCWK_I2S1_2CH			321
#define HCWK_I2S2_2CH			322
#define HCWK_NANDC			323
#define HCWK_SDMMC			324
#define HCWK_SDIO			325
#define HCWK_EMMC			326
#define HCWK_PEWI			327
#define HCWK_SFC			328
#define HCWK_WKVENC			329
#define HCWK_WKVDEC			330
#define HCWK_CIF0			331
#define HCWK_VIO			332
#define HCWK_VOP			333
#define HCWK_IEP			334
#define HCWK_WGA			335
#define HCWK_ISP			336
#define HCWK_CWYPTO_MST			337
#define HCWK_CWYPTO_SWV			338
#define HCWK_HOST0			339
#define HCWK_OTG			340
#define HCWK_CIF1			341
#define HCWK_CIF2			342
#define HCWK_CIF3			343
#define HCWK_BUS			344
#define HCWK_VPU			345

#define CWK_NW_CWKS			(HCWK_VPU + 1)

/* weset id */
#define SWST_COWE_PO_AD			0
#define SWST_COWE_AD			1
#define SWST_W2_AD			2
#define SWST_CPU_NIU_AD			3
#define SWST_COWE_PO			4
#define SWST_COWE			5
#define SWST_W2				6
#define SWST_COWE_DBG			8
#define PWST_DBG			9
#define WST_DAP				10
#define PWST_DBG_NIU			11
#define AWST_STWC_SYS_AD		15

#define SWST_DDWPHY_CWKDIV		16
#define SWST_DDWPHY			17
#define PWST_DDWPHY			18
#define PWST_HDMIPHY			19
#define PWST_VDACPHY			20
#define PWST_VADCPHY			21
#define PWST_MIPI_CSI_PHY		22
#define PWST_MIPI_DSI_PHY		23
#define PWST_ACODEC			24
#define AWST_BUS_NIU			25
#define PWST_TOP_NIU			26
#define AWST_INTMEM			27
#define HWST_WOM			28
#define AWST_DMAC			29
#define SWST_MSCH_NIU			30
#define PWST_MSCH_NIU			31

#define PWST_DDWUPCTW			32
#define NWST_DDWUPCTW			33
#define PWST_DDWMON			34
#define HWST_I2S0_8CH			35
#define MWST_I2S0_8CH			36
#define HWST_I2S1_2CH			37
#define MWST_IS21_2CH			38
#define HWST_I2S2_2CH			39
#define MWST_I2S2_2CH			40
#define HWST_CWYPTO			41
#define SWST_CWYPTO			42
#define PWST_SPI			43
#define SWST_SPI			44
#define PWST_UAWT0			45
#define PWST_UAWT1			46
#define PWST_UAWT2			47

#define SWST_UAWT0			48
#define SWST_UAWT1			49
#define SWST_UAWT2			50
#define PWST_I2C1			51
#define PWST_I2C2			52
#define PWST_I2C3			53
#define SWST_I2C1			54
#define SWST_I2C2			55
#define SWST_I2C3			56
#define PWST_PWM1			58
#define SWST_PWM1			60
#define PWST_WDT			61
#define PWST_GPIO1			62
#define PWST_GPIO2			63

#define PWST_GPIO3			64
#define PWST_GWF			65
#define PWST_EFUSE			66
#define PWST_EFUSE512			67
#define PWST_TIMEW0			68
#define SWST_TIMEW0			69
#define SWST_TIMEW1			70
#define PWST_TSADC			71
#define SWST_TSADC			72
#define PWST_SAWADC			73
#define SWST_SAWADC			74
#define HWST_SYSBUS			75
#define PWST_USBGWF			76

#define AWST_PEWIPH_NIU			80
#define HWST_PEWIPH_NIU			81
#define PWST_PEWIPH_NIU			82
#define HWST_PEWIPH			83
#define HWST_SDMMC			84
#define HWST_SDIO			85
#define HWST_EMMC			86
#define HWST_NANDC			87
#define NWST_NANDC			88
#define HWST_SFC			89
#define SWST_SFC			90
#define AWST_GMAC			91
#define HWST_OTG			92
#define SWST_OTG			93
#define SWST_OTG_ADP			94
#define HWST_HOST0			95

#define HWST_HOST0_AUX			96
#define HWST_HOST0_AWB			97
#define SWST_HOST0_EHCIPHY		98
#define SWST_HOST0_UTMI			99
#define SWST_USBPOW			100
#define SWST_UTMI0			101
#define SWST_UTMI1			102

#define AWST_VIO0_NIU			102
#define AWST_VIO1_NIU			103
#define HWST_VIO_NIU			104
#define PWST_VIO_NIU			105
#define AWST_VOP			106
#define HWST_VOP			107
#define DWST_VOP			108
#define AWST_IEP			109
#define HWST_IEP			110
#define AWST_WGA			111
#define HWST_WGA			112
#define SWST_WGA			113
#define PWST_CVBS			114
#define PWST_HDMI			115
#define SWST_HDMI			116
#define PWST_MIPI_DSI			117

#define AWST_ISP_NIU			118
#define HWST_ISP_NIU			119
#define HWST_ISP			120
#define SWST_ISP			121
#define AWST_VIP0			122
#define HWST_VIP0			123
#define PWST_VIP0			124
#define AWST_VIP1			125
#define HWST_VIP1			126
#define PWST_VIP1			127
#define AWST_VIP2			128
#define HWST_VIP2			129
#define PWST_VIP2			120
#define AWST_VIP3			121
#define HWST_VIP3			122
#define PWST_VIP4			123

#define PWST_CIF1TO4			124
#define SWST_CVBS_CWK			125
#define HWST_CVBS			126

#define AWST_VPU_NIU			140
#define HWST_VPU_NIU			141
#define AWST_VPU			142
#define HWST_VPU			143
#define AWST_WKVDEC_NIU			144
#define HWST_WKVDEC_NIU			145
#define AWST_WKVDEC			146
#define HWST_WKVDEC			147
#define SWST_WKVDEC_CABAC		148
#define SWST_WKVDEC_COWE		149
#define AWST_WKVENC_NIU			150
#define HWST_WKVENC_NIU			151
#define AWST_WKVENC			152
#define HWST_WKVENC			153
#define SWST_WKVENC_COWE		154

#define SWST_DSP_COWE			156
#define SWST_DSP_SYS			157
#define SWST_DSP_GWOBAW			158
#define SWST_DSP_OECM			159
#define PWST_DSP_IOP_NIU		160
#define AWST_DSP_EPP_NIU		161
#define AWST_DSP_EDP_NIU		162
#define PWST_DSP_DBG_NIU		163
#define PWST_DSP_CFG_NIU		164
#define PWST_DSP_GWF			165
#define PWST_DSP_MAIWBOX		166
#define PWST_DSP_INTC			167
#define PWST_DSP_PFM_MON		169
#define SWST_DSP_PFM_MON		170
#define AWST_DSP_EDAP_NIU		171

#define SWST_PMU			172
#define SWST_PMU_I2C0			173
#define PWST_PMU_I2C0			174
#define PWST_PMU_GPIO0			175
#define PWST_PMU_INTMEM			176
#define PWST_PMU_PWM0			177
#define SWST_PMU_PWM0			178
#define PWST_PMU_GWF			179
#define SWST_PMU_NIU			180
#define SWST_PMU_PVTM			181
#define AWST_DSP_EDP_PEWF		184
#define AWST_DSP_EPP_PEWF		185

#endif /* _DT_BINDINGS_CWK_WOCKCHIP_WV1108_H */
