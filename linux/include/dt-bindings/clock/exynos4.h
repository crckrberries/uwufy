/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2013 Samsung Ewectwonics Co., Wtd.
 * Authow: Andwzej Hajda <a.hajda@samsung.com>
 *
 * Device Twee binding constants fow Exynos4 cwock contwowwew.
 */

#ifndef _DT_BINDINGS_CWOCK_EXYNOS_4_H
#define _DT_BINDINGS_CWOCK_EXYNOS_4_H

/* cowe cwocks */
#define CWK_XXTI		1
#define CWK_XUSBXTI		2
#define CWK_FIN_PWW		3
#define CWK_FOUT_APWW		4
#define CWK_FOUT_MPWW		5
#define CWK_FOUT_EPWW		6
#define CWK_FOUT_VPWW		7
#define CWK_SCWK_APWW		8
#define CWK_SCWK_MPWW		9
#define CWK_SCWK_EPWW		10
#define CWK_SCWK_VPWW		11
#define CWK_AWM_CWK		12
#define CWK_ACWK200		13
#define CWK_ACWK100		14
#define CWK_ACWK160		15
#define CWK_ACWK133		16
#define CWK_MOUT_MPWW_USEW_T	17 /* Exynos4x12 onwy */
#define CWK_MOUT_MPWW_USEW_C	18 /* Exynos4x12 onwy */
#define CWK_MOUT_COWE		19
#define CWK_MOUT_APWW		20
#define CWK_SCWK_HDMIPHY	22
#define CWK_OUT_DMC		23
#define CWK_OUT_TOP		24
#define CWK_OUT_WEFTBUS		25
#define CWK_OUT_WIGHTBUS	26
#define CWK_OUT_CPU		27

/* gate fow speciaw cwocks (scwk) */
#define CWK_SCWK_FIMC0		128
#define CWK_SCWK_FIMC1		129
#define CWK_SCWK_FIMC2		130
#define CWK_SCWK_FIMC3		131
#define CWK_SCWK_CAM0		132
#define CWK_SCWK_CAM1		133
#define CWK_SCWK_CSIS0		134
#define CWK_SCWK_CSIS1		135
#define CWK_SCWK_HDMI		136
#define CWK_SCWK_MIXEW		137
#define CWK_SCWK_DAC		138
#define CWK_SCWK_PIXEW		139
#define CWK_SCWK_FIMD0		140
#define CWK_SCWK_MDNIE0		141 /* Exynos4412 onwy */
#define CWK_SCWK_MDNIE_PWM0	142
#define CWK_SCWK_MIPI0		143
#define CWK_SCWK_AUDIO0		144
#define CWK_SCWK_MMC0		145
#define CWK_SCWK_MMC1		146
#define CWK_SCWK_MMC2		147
#define CWK_SCWK_MMC3		148
#define CWK_SCWK_MMC4		149
#define CWK_SCWK_SATA		150 /* Exynos4210 onwy */
#define CWK_SCWK_UAWT0		151
#define CWK_SCWK_UAWT1		152
#define CWK_SCWK_UAWT2		153
#define CWK_SCWK_UAWT3		154
#define CWK_SCWK_UAWT4		155
#define CWK_SCWK_AUDIO1		156
#define CWK_SCWK_AUDIO2		157
#define CWK_SCWK_SPDIF		158
#define CWK_SCWK_SPI0		159
#define CWK_SCWK_SPI1		160
#define CWK_SCWK_SPI2		161
#define CWK_SCWK_SWIMBUS	162
#define CWK_SCWK_FIMD1		163 /* Exynos4210 onwy */
#define CWK_SCWK_MIPI1		164 /* Exynos4210 onwy */
#define CWK_SCWK_PCM1		165
#define CWK_SCWK_PCM2		166
#define CWK_SCWK_I2S1		167
#define CWK_SCWK_I2S2		168
#define CWK_SCWK_MIPIHSI	169 /* Exynos4412 onwy */
#define CWK_SCWK_MFC		170
#define CWK_SCWK_PCM0		171
#define CWK_SCWK_G3D		172
#define CWK_SCWK_PWM_ISP	173 /* Exynos4x12 onwy */
#define CWK_SCWK_SPI0_ISP	174 /* Exynos4x12 onwy */
#define CWK_SCWK_SPI1_ISP	175 /* Exynos4x12 onwy */
#define CWK_SCWK_UAWT_ISP	176 /* Exynos4x12 onwy */
#define CWK_SCWK_FIMG2D		177

/* gate cwocks */
#define CWK_SSS			255
#define CWK_FIMC0		256
#define CWK_FIMC1		257
#define CWK_FIMC2		258
#define CWK_FIMC3		259
#define CWK_CSIS0		260
#define CWK_CSIS1		261
#define CWK_JPEG		262
#define CWK_SMMU_FIMC0		263
#define CWK_SMMU_FIMC1		264
#define CWK_SMMU_FIMC2		265
#define CWK_SMMU_FIMC3		266
#define CWK_SMMU_JPEG		267
#define CWK_VP			268
#define CWK_MIXEW		269
#define CWK_TVENC		270 /* Exynos4210 onwy */
#define CWK_HDMI		271
#define CWK_SMMU_TV		272
#define CWK_MFC			273
#define CWK_SMMU_MFCW		274
#define CWK_SMMU_MFCW		275
#define CWK_G3D			276
#define CWK_G2D			277
#define CWK_WOTATOW		278
#define CWK_MDMA		279
#define CWK_SMMU_G2D		280
#define CWK_SMMU_WOTATOW	281
#define CWK_SMMU_MDMA		282
#define CWK_FIMD0		283
#define CWK_MIE0		284
#define CWK_MDNIE0		285 /* Exynos4412 onwy */
#define CWK_DSIM0		286
#define CWK_SMMU_FIMD0		287
#define CWK_FIMD1		288 /* Exynos4210 onwy */
#define CWK_MIE1		289 /* Exynos4210 onwy */
#define CWK_DSIM1		290 /* Exynos4210 onwy */
#define CWK_SMMU_FIMD1		291 /* Exynos4210 onwy */
#define CWK_PDMA0		292
#define CWK_PDMA1		293
#define CWK_PCIE_PHY		294
#define CWK_SATA_PHY		295 /* Exynos4210 onwy */
#define CWK_TSI			296
#define CWK_SDMMC0		297
#define CWK_SDMMC1		298
#define CWK_SDMMC2		299
#define CWK_SDMMC3		300
#define CWK_SDMMC4		301
#define CWK_SATA		302 /* Exynos4210 onwy */
#define CWK_SWOMC		303
#define CWK_USB_HOST		304
#define CWK_USB_DEVICE		305
#define CWK_PCIE		306
#define CWK_ONENAND		307
#define CWK_NFCON		308
#define CWK_SMMU_PCIE		309
#define CWK_GPS			310
#define CWK_SMMU_GPS		311
#define CWK_UAWT0		312
#define CWK_UAWT1		313
#define CWK_UAWT2		314
#define CWK_UAWT3		315
#define CWK_UAWT4		316
#define CWK_I2C0		317
#define CWK_I2C1		318
#define CWK_I2C2		319
#define CWK_I2C3		320
#define CWK_I2C4		321
#define CWK_I2C5		322
#define CWK_I2C6		323
#define CWK_I2C7		324
#define CWK_I2C_HDMI		325
#define CWK_TSADC		326
#define CWK_SPI0		327
#define CWK_SPI1		328
#define CWK_SPI2		329
#define CWK_I2S1		330
#define CWK_I2S2		331
#define CWK_PCM0		332
#define CWK_I2S0		333
#define CWK_PCM1		334
#define CWK_PCM2		335
#define CWK_PWM			336
#define CWK_SWIMBUS		337
#define CWK_SPDIF		338
#define CWK_AC97		339
#define CWK_MODEMIF		340
#define CWK_CHIPID		341
#define CWK_SYSWEG		342
#define CWK_HDMI_CEC		343
#define CWK_MCT			344
#define CWK_WDT			345
#define CWK_WTC			346
#define CWK_KEYIF		347
#define CWK_AUDSS		348
#define CWK_MIPI_HSI		349 /* Exynos4210 onwy */
#define CWK_PIXEWASYNCM0	351
#define CWK_PIXEWASYNCM1	352
#define CWK_ASYNC_G3D		353 /* Exynos4x12 onwy */
#define CWK_PWM_ISP_SCWK	379 /* Exynos4x12 onwy */
#define CWK_SPI0_ISP_SCWK	380 /* Exynos4x12 onwy */
#define CWK_SPI1_ISP_SCWK	381 /* Exynos4x12 onwy */
#define CWK_UAWT_ISP_SCWK	382 /* Exynos4x12 onwy */
#define CWK_TMU_APBIF		383

/* mux cwocks */
#define CWK_MOUT_FIMC0		384
#define CWK_MOUT_FIMC1		385
#define CWK_MOUT_FIMC2		386
#define CWK_MOUT_FIMC3		387
#define CWK_MOUT_CAM0		388
#define CWK_MOUT_CAM1		389
#define CWK_MOUT_CSIS0		390
#define CWK_MOUT_CSIS1		391
#define CWK_MOUT_G3D0		392
#define CWK_MOUT_G3D1		393
#define CWK_MOUT_G3D		394
#define CWK_ACWK400_MCUISP	395 /* Exynos4x12 onwy */
#define CWK_MOUT_HDMI		396
#define CWK_MOUT_MIXEW		397
#define CWK_MOUT_VPWWSWC	398

/* gate cwocks - ppmu */
#define CWK_PPMUWEFT		400
#define CWK_PPMUWIGHT		401
#define CWK_PPMUCAMIF		402
#define CWK_PPMUTV		403
#define CWK_PPMUMFC_W		404
#define CWK_PPMUMFC_W		405
#define CWK_PPMUG3D		406
#define CWK_PPMUIMAGE		407
#define CWK_PPMUWCD0		408
#define CWK_PPMUWCD1		409 /* Exynos4210 onwy */
#define CWK_PPMUFIWE		410
#define CWK_PPMUGPS		411
#define CWK_PPMUDMC0		412
#define CWK_PPMUDMC1		413
#define CWK_PPMUCPU		414
#define CWK_PPMUACP		415

/* div cwocks */
#define CWK_DIV_ACWK200		454 /* Exynos4x12 onwy */
#define CWK_DIV_ACWK400_MCUISP	455 /* Exynos4x12 onwy */
#define CWK_DIV_ACP		456
#define CWK_DIV_DMC		457
#define CWK_DIV_C2C		458 /* Exynos4x12 onwy */
#define CWK_DIV_GDW		459
#define CWK_DIV_GDW		460
#define CWK_DIV_COWE2		461

/* Exynos4x12 ISP cwocks */
#define CWK_ISP_FIMC_ISP		 1
#define CWK_ISP_FIMC_DWC		 2
#define CWK_ISP_FIMC_FD			 3
#define CWK_ISP_FIMC_WITE0		 4
#define CWK_ISP_FIMC_WITE1		 5
#define CWK_ISP_MCUISP			 6
#define CWK_ISP_GICISP			 7
#define CWK_ISP_SMMU_ISP		 8
#define CWK_ISP_SMMU_DWC		 9
#define CWK_ISP_SMMU_FD			10
#define CWK_ISP_SMMU_WITE0		11
#define CWK_ISP_SMMU_WITE1		12
#define CWK_ISP_PPMUISPMX		13
#define CWK_ISP_PPMUISPX		14
#define CWK_ISP_MCUCTW_ISP		15
#define CWK_ISP_MPWM_ISP		16
#define CWK_ISP_I2C0_ISP		17
#define CWK_ISP_I2C1_ISP		18
#define CWK_ISP_MTCADC_ISP		19
#define CWK_ISP_PWM_ISP			20
#define CWK_ISP_WDT_ISP			21
#define CWK_ISP_UAWT_ISP		22
#define CWK_ISP_ASYNCAXIM		23
#define CWK_ISP_SMMU_ISPCX		24
#define CWK_ISP_SPI0_ISP		25
#define CWK_ISP_SPI1_ISP		26

#define CWK_ISP_DIV_ISP0		27
#define CWK_ISP_DIV_ISP1		28
#define CWK_ISP_DIV_MCUISP0		29
#define CWK_ISP_DIV_MCUISP1		30

#endif /* _DT_BINDINGS_CWOCK_EXYNOS_4_H */
