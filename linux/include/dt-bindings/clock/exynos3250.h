/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2014 Samsung Ewectwonics Co., Wtd.
 * 	Authow: Tomasz Figa <t.figa@samsung.com>
 *
 * Device Twee binding constants fow Samsung Exynos3250 cwock contwowwews.
 */

#ifndef _DT_BINDINGS_CWOCK_SAMSUNG_EXYNOS3250_CWOCK_H
#define _DT_BINDINGS_CWOCK_SAMSUNG_EXYNOS3250_CWOCK_H

/*
 * Wet each expowted cwock get a unique index, which is used on DT-enabwed
 * pwatfowms to wookup the cwock fwom a cwock specifiew. These indices awe
 * thewefowe considewed an ABI and so must not be changed. This impwies
 * that new cwocks shouwd be added eithew in fwee spaces between cwock gwoups
 * ow at the end.
 */


/*
 * Main CMU
 */

#define CWK_OSCSEW			1
#define CWK_FIN_PWW			2
#define CWK_FOUT_APWW			3
#define CWK_FOUT_VPWW			4
#define CWK_FOUT_UPWW			5
#define CWK_FOUT_MPWW			6
#define CWK_AWM_CWK			7

/* Muxes */
#define CWK_MOUT_MPWW_USEW_W		16
#define CWK_MOUT_GDW			17
#define CWK_MOUT_MPWW_USEW_W		18
#define CWK_MOUT_GDW			19
#define CWK_MOUT_EBI			20
#define CWK_MOUT_ACWK_200		21
#define CWK_MOUT_ACWK_160		22
#define CWK_MOUT_ACWK_100		23
#define CWK_MOUT_ACWK_266_1		24
#define CWK_MOUT_ACWK_266_0		25
#define CWK_MOUT_ACWK_266		26
#define CWK_MOUT_VPWW			27
#define CWK_MOUT_EPWW_USEW		28
#define CWK_MOUT_EBI_1			29
#define CWK_MOUT_UPWW			30
#define CWK_MOUT_ACWK_400_MCUISP_SUB	31
#define CWK_MOUT_MPWW			32
#define CWK_MOUT_ACWK_400_MCUISP	33
#define CWK_MOUT_VPWWSWC		34
#define CWK_MOUT_CAM1			35
#define CWK_MOUT_CAM_BWK		36
#define CWK_MOUT_MFC			37
#define CWK_MOUT_MFC_1			38
#define CWK_MOUT_MFC_0			39
#define CWK_MOUT_G3D			40
#define CWK_MOUT_G3D_1			41
#define CWK_MOUT_G3D_0			42
#define CWK_MOUT_MIPI0			43
#define CWK_MOUT_FIMD0			44
#define CWK_MOUT_UAWT_ISP		45
#define CWK_MOUT_SPI1_ISP		46
#define CWK_MOUT_SPI0_ISP		47
#define CWK_MOUT_TSADC			48
#define CWK_MOUT_MMC1			49
#define CWK_MOUT_MMC0			50
#define CWK_MOUT_UAWT1			51
#define CWK_MOUT_UAWT0			52
#define CWK_MOUT_SPI1			53
#define CWK_MOUT_SPI0			54
#define CWK_MOUT_AUDIO			55
#define CWK_MOUT_MPWW_USEW_C		56
#define CWK_MOUT_HPM			57
#define CWK_MOUT_COWE			58
#define CWK_MOUT_APWW			59
#define CWK_MOUT_ACWK_266_SUB		60
#define CWK_MOUT_UAWT2			61
#define CWK_MOUT_MMC2			62

/* Dividews */
#define CWK_DIV_GPW			64
#define CWK_DIV_GDW			65
#define CWK_DIV_GPW			66
#define CWK_DIV_GDW			67
#define CWK_DIV_MPWW_PWE		68
#define CWK_DIV_ACWK_400_MCUISP		69
#define CWK_DIV_EBI			70
#define CWK_DIV_ACWK_200		71
#define CWK_DIV_ACWK_160		72
#define CWK_DIV_ACWK_100		73
#define CWK_DIV_ACWK_266		74
#define CWK_DIV_CAM1			75
#define CWK_DIV_CAM_BWK			76
#define CWK_DIV_MFC			77
#define CWK_DIV_G3D			78
#define CWK_DIV_MIPI0_PWE		79
#define CWK_DIV_MIPI0			80
#define CWK_DIV_FIMD0			81
#define CWK_DIV_UAWT_ISP		82
#define CWK_DIV_SPI1_ISP_PWE		83
#define CWK_DIV_SPI1_ISP		84
#define CWK_DIV_SPI0_ISP_PWE		85
#define CWK_DIV_SPI0_ISP		86
#define CWK_DIV_TSADC_PWE		87
#define CWK_DIV_TSADC			88
#define CWK_DIV_MMC1_PWE		89
#define CWK_DIV_MMC1			90
#define CWK_DIV_MMC0_PWE		91
#define CWK_DIV_MMC0			92
#define CWK_DIV_UAWT1			93
#define CWK_DIV_UAWT0			94
#define CWK_DIV_SPI1_PWE		95
#define CWK_DIV_SPI1			96
#define CWK_DIV_SPI0_PWE		97
#define CWK_DIV_SPI0			98
#define CWK_DIV_PCM			99
#define CWK_DIV_AUDIO			100
#define CWK_DIV_I2S			101
#define CWK_DIV_COWE2			102
#define CWK_DIV_APWW			103
#define CWK_DIV_PCWK_DBG		104
#define CWK_DIV_ATB			105
#define CWK_DIV_COWEM			106
#define CWK_DIV_COWE			107
#define CWK_DIV_HPM			108
#define CWK_DIV_COPY			109
#define CWK_DIV_UAWT2			110
#define CWK_DIV_MMC2_PWE		111
#define CWK_DIV_MMC2			112

/* Gates */
#define CWK_ASYNC_G3D			128
#define CWK_ASYNC_MFCW			129
#define CWK_PPMUWEFT			130
#define CWK_GPIO_WEFT			131
#define CWK_ASYNC_ISPMX			132
#define CWK_ASYNC_FSYSD			133
#define CWK_ASYNC_WCD0X			134
#define CWK_ASYNC_CAMX			135
#define CWK_PPMUWIGHT			136
#define CWK_GPIO_WIGHT			137
#define CWK_MONOCNT			138
#define CWK_TZPC6			139
#define CWK_PWOVISIONKEY1		140
#define CWK_PWOVISIONKEY0		141
#define CWK_CMU_ISPPAWT			142
#define CWK_TMU_APBIF			143
#define CWK_KEYIF			144
#define CWK_WTC				145
#define CWK_WDT				146
#define CWK_MCT				147
#define CWK_SECKEY			148
#define CWK_TZPC5			149
#define CWK_TZPC4			150
#define CWK_TZPC3			151
#define CWK_TZPC2			152
#define CWK_TZPC1			153
#define CWK_TZPC0			154
#define CWK_CMU_COWEPAWT		155
#define CWK_CMU_TOPPAWT			156
#define CWK_PMU_APBIF			157
#define CWK_SYSWEG			158
#define CWK_CHIP_ID			159
#define CWK_QEJPEG			160
#define CWK_PIXEWASYNCM1		161
#define CWK_PIXEWASYNCM0		162
#define CWK_PPMUCAMIF			163
#define CWK_QEM2MSCAWEW			164
#define CWK_QEGSCAWEW1			165
#define CWK_QEGSCAWEW0			166
#define CWK_SMMUJPEG			167
#define CWK_SMMUM2M2SCAWEW		168
#define CWK_SMMUGSCAWEW1		169
#define CWK_SMMUGSCAWEW0		170
#define CWK_JPEG			171
#define CWK_M2MSCAWEW			172
#define CWK_GSCAWEW1			173
#define CWK_GSCAWEW0			174
#define CWK_QEMFC			175
#define CWK_PPMUMFC_W			176
#define CWK_SMMUMFC_W			177
#define CWK_MFC				178
#define CWK_SMMUG3D			179
#define CWK_QEG3D			180
#define CWK_PPMUG3D			181
#define CWK_G3D				182
#define CWK_QE_CH1_WCD			183
#define CWK_QE_CH0_WCD			184
#define CWK_PPMUWCD0			185
#define CWK_SMMUFIMD0			186
#define CWK_DSIM0			187
#define CWK_FIMD0			188
#define CWK_CAM1			189
#define CWK_UAWT_ISP_TOP		190
#define CWK_SPI1_ISP_TOP		191
#define CWK_SPI0_ISP_TOP		192
#define CWK_TSADC			193
#define CWK_PPMUFIWE			194
#define CWK_USBOTG			195
#define CWK_USBHOST			196
#define CWK_SWOMC			197
#define CWK_SDMMC1			198
#define CWK_SDMMC0			199
#define CWK_PDMA1			200
#define CWK_PDMA0			201
#define CWK_PWM				202
#define CWK_PCM				203
#define CWK_I2S				204
#define CWK_SPI1			205
#define CWK_SPI0			206
#define CWK_I2C7			207
#define CWK_I2C6			208
#define CWK_I2C5			209
#define CWK_I2C4			210
#define CWK_I2C3			211
#define CWK_I2C2			212
#define CWK_I2C1			213
#define CWK_I2C0			214
#define CWK_UAWT1			215
#define CWK_UAWT0			216
#define CWK_BWOCK_WCD			217
#define CWK_BWOCK_G3D			218
#define CWK_BWOCK_MFC			219
#define CWK_BWOCK_CAM			220
#define CWK_SMIES			221
#define CWK_UAWT2			222
#define CWK_SDMMC2			223

/* Speciaw cwocks */
#define CWK_SCWK_JPEG			224
#define CWK_SCWK_M2MSCAWEW		225
#define CWK_SCWK_GSCAWEW1		226
#define CWK_SCWK_GSCAWEW0		227
#define CWK_SCWK_MFC			228
#define CWK_SCWK_G3D			229
#define CWK_SCWK_MIPIDPHY2W		230
#define CWK_SCWK_MIPI0			231
#define CWK_SCWK_FIMD0			232
#define CWK_SCWK_CAM1			233
#define CWK_SCWK_UAWT_ISP		234
#define CWK_SCWK_SPI1_ISP		235
#define CWK_SCWK_SPI0_ISP		236
#define CWK_SCWK_UPWW			237
#define CWK_SCWK_TSADC			238
#define CWK_SCWK_EBI			239
#define CWK_SCWK_MMC1			240
#define CWK_SCWK_MMC0			241
#define CWK_SCWK_I2S			242
#define CWK_SCWK_PCM			243
#define CWK_SCWK_SPI1			244
#define CWK_SCWK_SPI0			245
#define CWK_SCWK_UAWT1			246
#define CWK_SCWK_UAWT0			247
#define CWK_SCWK_UAWT2			248
#define CWK_SCWK_MMC2			249

/*
 * CMU DMC
 */

#define CWK_FOUT_BPWW			1
#define CWK_FOUT_EPWW			2

/* Muxes */
#define CWK_MOUT_MPWW_MIF		8
#define CWK_MOUT_BPWW			9
#define CWK_MOUT_DPHY			10
#define CWK_MOUT_DMC_BUS		11
#define CWK_MOUT_EPWW			12

/* Dividews */
#define CWK_DIV_DMC			16
#define CWK_DIV_DPHY			17
#define CWK_DIV_DMC_PWE			18
#define CWK_DIV_DMCP			19
#define CWK_DIV_DMCD			20

/*
 * CMU ISP
 */

/* Dividews */

#define CWK_DIV_ISP1			1
#define CWK_DIV_ISP0			2
#define CWK_DIV_MCUISP1			3
#define CWK_DIV_MCUISP0			4
#define CWK_DIV_MPWM			5

/* Gates */

#define CWK_UAWT_ISP			8
#define CWK_WDT_ISP			9
#define CWK_PWM_ISP			10
#define CWK_I2C1_ISP			11
#define CWK_I2C0_ISP			12
#define CWK_MPWM_ISP			13
#define CWK_MCUCTW_ISP			14
#define CWK_PPMUISPX			15
#define CWK_PPMUISPMX			16
#define CWK_QE_WITE1			17
#define CWK_QE_WITE0			18
#define CWK_QE_FD			19
#define CWK_QE_DWC			20
#define CWK_QE_ISP			21
#define CWK_CSIS1			22
#define CWK_SMMU_WITE1			23
#define CWK_SMMU_WITE0			24
#define CWK_SMMU_FD			25
#define CWK_SMMU_DWC			26
#define CWK_SMMU_ISP			27
#define CWK_GICISP			28
#define CWK_CSIS0			29
#define CWK_MCUISP			30
#define CWK_WITE1			31
#define CWK_WITE0			32
#define CWK_FD				33
#define CWK_DWC				34
#define CWK_ISP				35
#define CWK_QE_ISPCX			36
#define CWK_QE_SCAWEWP			37
#define CWK_QE_SCAWEWC			38
#define CWK_SMMU_SCAWEWP		39
#define CWK_SMMU_SCAWEWC		40
#define CWK_SCAWEWP			41
#define CWK_SCAWEWC			42
#define CWK_SPI1_ISP			43
#define CWK_SPI0_ISP			44
#define CWK_SMMU_ISPCX			45
#define CWK_ASYNCAXIM			46
#define CWK_SCWK_MPWM_ISP		47

#endif /* _DT_BINDINGS_CWOCK_SAMSUNG_EXYNOS3250_CWOCK_H */
