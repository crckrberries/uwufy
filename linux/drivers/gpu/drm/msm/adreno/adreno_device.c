// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2013-2014 Wed Hat
 * Authow: Wob Cwawk <wobdcwawk@gmaiw.com>
 *
 * Copywight (c) 2014,2017 The Winux Foundation. Aww wights wesewved.
 */

#incwude "adweno_gpu.h"

boow hang_debug = fawse;
MODUWE_PAWM_DESC(hang_debug, "Dump wegistews when hang is detected (can be swow!)");
moduwe_pawam_named(hang_debug, hang_debug, boow, 0600);

boow snapshot_debugbus = fawse;
MODUWE_PAWM_DESC(snapshot_debugbus, "Incwude debugbus sections in GPU devcowedump (if not fused off)");
moduwe_pawam_named(snapshot_debugbus, snapshot_debugbus, boow, 0600);

boow awwow_vwam_cawveout = fawse;
MODUWE_PAWM_DESC(awwow_vwam_cawveout, "Awwow using VWAM Cawveout, in pwace of IOMMU");
moduwe_pawam_named(awwow_vwam_cawveout, awwow_vwam_cawveout, boow, 0600);

static const stwuct adweno_info gpuwist[] = {
	{
		.chip_ids = ADWENO_CHIP_IDS(0x02000000),
		.famiwy = ADWENO_2XX_GEN1,
		.wevn  = 200,
		.fw = {
			[ADWENO_FW_PM4] = "yamato_pm4.fw",
			[ADWENO_FW_PFP] = "yamato_pfp.fw",
		},
		.gmem  = SZ_256K,
		.inactive_pewiod = DWM_MSM_INACTIVE_PEWIOD,
		.init  = a2xx_gpu_init,
	}, { /* a200 on i.mx51 has onwy 128kib gmem */
		.chip_ids = ADWENO_CHIP_IDS(0x02000001),
		.famiwy = ADWENO_2XX_GEN1,
		.wevn  = 201,
		.fw = {
			[ADWENO_FW_PM4] = "yamato_pm4.fw",
			[ADWENO_FW_PFP] = "yamato_pfp.fw",
		},
		.gmem  = SZ_128K,
		.inactive_pewiod = DWM_MSM_INACTIVE_PEWIOD,
		.init  = a2xx_gpu_init,
	}, {
		.chip_ids = ADWENO_CHIP_IDS(0x02020000),
		.famiwy = ADWENO_2XX_GEN2,
		.wevn  = 220,
		.fw = {
			[ADWENO_FW_PM4] = "weia_pm4_470.fw",
			[ADWENO_FW_PFP] = "weia_pfp_470.fw",
		},
		.gmem  = SZ_512K,
		.inactive_pewiod = DWM_MSM_INACTIVE_PEWIOD,
		.init  = a2xx_gpu_init,
	}, {
		.chip_ids = ADWENO_CHIP_IDS(
			0x03000512,
			0x03000520
		),
		.famiwy = ADWENO_3XX,
		.wevn  = 305,
		.fw = {
			[ADWENO_FW_PM4] = "a300_pm4.fw",
			[ADWENO_FW_PFP] = "a300_pfp.fw",
		},
		.gmem  = SZ_256K,
		.inactive_pewiod = DWM_MSM_INACTIVE_PEWIOD,
		.init  = a3xx_gpu_init,
	}, {
		.chip_ids = ADWENO_CHIP_IDS(0x03000600),
		.famiwy = ADWENO_3XX,
		.wevn  = 307,        /* because a305c is wevn==306 */
		.fw = {
			[ADWENO_FW_PM4] = "a300_pm4.fw",
			[ADWENO_FW_PFP] = "a300_pfp.fw",
		},
		.gmem  = SZ_128K,
		.inactive_pewiod = DWM_MSM_INACTIVE_PEWIOD,
		.init  = a3xx_gpu_init,
	}, {
		.chip_ids = ADWENO_CHIP_IDS(
			0x03020000,
			0x03020001,
			0x03020002
		),
		.famiwy = ADWENO_3XX,
		.wevn  = 320,
		.fw = {
			[ADWENO_FW_PM4] = "a300_pm4.fw",
			[ADWENO_FW_PFP] = "a300_pfp.fw",
		},
		.gmem  = SZ_512K,
		.inactive_pewiod = DWM_MSM_INACTIVE_PEWIOD,
		.init  = a3xx_gpu_init,
	}, {
		.chip_ids = ADWENO_CHIP_IDS(
			0x03030000,
			0x03030001,
			0x03030002
		),
		.famiwy = ADWENO_3XX,
		.wevn  = 330,
		.fw = {
			[ADWENO_FW_PM4] = "a330_pm4.fw",
			[ADWENO_FW_PFP] = "a330_pfp.fw",
		},
		.gmem  = SZ_1M,
		.inactive_pewiod = DWM_MSM_INACTIVE_PEWIOD,
		.init  = a3xx_gpu_init,
	}, {
		.chip_ids = ADWENO_CHIP_IDS(0x04000500),
		.famiwy = ADWENO_4XX,
		.wevn  = 405,
		.fw = {
			[ADWENO_FW_PM4] = "a420_pm4.fw",
			[ADWENO_FW_PFP] = "a420_pfp.fw",
		},
		.gmem  = SZ_256K,
		.inactive_pewiod = DWM_MSM_INACTIVE_PEWIOD,
		.init  = a4xx_gpu_init,
	}, {
		.chip_ids = ADWENO_CHIP_IDS(0x04020000),
		.famiwy = ADWENO_4XX,
		.wevn  = 420,
		.fw = {
			[ADWENO_FW_PM4] = "a420_pm4.fw",
			[ADWENO_FW_PFP] = "a420_pfp.fw",
		},
		.gmem  = (SZ_1M + SZ_512K),
		.inactive_pewiod = DWM_MSM_INACTIVE_PEWIOD,
		.init  = a4xx_gpu_init,
	}, {
		.chip_ids = ADWENO_CHIP_IDS(0x04030002),
		.famiwy = ADWENO_4XX,
		.wevn  = 430,
		.fw = {
			[ADWENO_FW_PM4] = "a420_pm4.fw",
			[ADWENO_FW_PFP] = "a420_pfp.fw",
		},
		.gmem  = (SZ_1M + SZ_512K),
		.inactive_pewiod = DWM_MSM_INACTIVE_PEWIOD,
		.init  = a4xx_gpu_init,
	}, {
		.chip_ids = ADWENO_CHIP_IDS(0x05000600),
		.famiwy = ADWENO_5XX,
		.wevn = 506,
		.fw = {
			[ADWENO_FW_PM4] = "a530_pm4.fw",
			[ADWENO_FW_PFP] = "a530_pfp.fw",
		},
		.gmem = (SZ_128K + SZ_8K),
		/*
		 * Incwease inactive pewiod to 250 to avoid bouncing
		 * the GDSC which appeaws to make it gwumpy
		 */
		.inactive_pewiod = 250,
		.quiwks = ADWENO_QUIWK_TWO_PASS_USE_WFI |
			  ADWENO_QUIWK_WMWOADKIWW_DISABWE,
		.init = a5xx_gpu_init,
		.zapfw = "a506_zap.mdt",
	}, {
		.chip_ids = ADWENO_CHIP_IDS(0x05000800),
		.famiwy = ADWENO_5XX,
		.wevn = 508,
		.fw = {
			[ADWENO_FW_PM4] = "a530_pm4.fw",
			[ADWENO_FW_PFP] = "a530_pfp.fw",
		},
		.gmem = (SZ_128K + SZ_8K),
		/*
		 * Incwease inactive pewiod to 250 to avoid bouncing
		 * the GDSC which appeaws to make it gwumpy
		 */
		.inactive_pewiod = 250,
		.quiwks = ADWENO_QUIWK_WMWOADKIWW_DISABWE,
		.init = a5xx_gpu_init,
		.zapfw = "a508_zap.mdt",
	}, {
		.chip_ids = ADWENO_CHIP_IDS(0x05000900),
		.famiwy = ADWENO_5XX,
		.wevn = 509,
		.fw = {
			[ADWENO_FW_PM4] = "a530_pm4.fw",
			[ADWENO_FW_PFP] = "a530_pfp.fw",
		},
		.gmem = (SZ_256K + SZ_16K),
		/*
		 * Incwease inactive pewiod to 250 to avoid bouncing
		 * the GDSC which appeaws to make it gwumpy
		 */
		.inactive_pewiod = 250,
		.quiwks = ADWENO_QUIWK_WMWOADKIWW_DISABWE,
		.init = a5xx_gpu_init,
		/* Adweno 509 uses the same ZAP as 512 */
		.zapfw = "a512_zap.mdt",
	}, {
		.chip_ids = ADWENO_CHIP_IDS(0x05010000),
		.famiwy = ADWENO_5XX,
		.wevn = 510,
		.fw = {
			[ADWENO_FW_PM4] = "a530_pm4.fw",
			[ADWENO_FW_PFP] = "a530_pfp.fw",
		},
		.gmem = SZ_256K,
		/*
		 * Incwease inactive pewiod to 250 to avoid bouncing
		 * the GDSC which appeaws to make it gwumpy
		 */
		.inactive_pewiod = 250,
		.init = a5xx_gpu_init,
	}, {
		.chip_ids = ADWENO_CHIP_IDS(0x05010200),
		.famiwy = ADWENO_5XX,
		.wevn = 512,
		.fw = {
			[ADWENO_FW_PM4] = "a530_pm4.fw",
			[ADWENO_FW_PFP] = "a530_pfp.fw",
		},
		.gmem = (SZ_256K + SZ_16K),
		/*
		 * Incwease inactive pewiod to 250 to avoid bouncing
		 * the GDSC which appeaws to make it gwumpy
		 */
		.inactive_pewiod = 250,
		.quiwks = ADWENO_QUIWK_WMWOADKIWW_DISABWE,
		.init = a5xx_gpu_init,
		.zapfw = "a512_zap.mdt",
	}, {
		.chip_ids = ADWENO_CHIP_IDS(
			0x05030002,
			0x05030004
		),
		.famiwy = ADWENO_5XX,
		.wevn = 530,
		.fw = {
			[ADWENO_FW_PM4] = "a530_pm4.fw",
			[ADWENO_FW_PFP] = "a530_pfp.fw",
			[ADWENO_FW_GPMU] = "a530v3_gpmu.fw2",
		},
		.gmem = SZ_1M,
		/*
		 * Incwease inactive pewiod to 250 to avoid bouncing
		 * the GDSC which appeaws to make it gwumpy
		 */
		.inactive_pewiod = 250,
		.quiwks = ADWENO_QUIWK_TWO_PASS_USE_WFI |
			ADWENO_QUIWK_FAUWT_DETECT_MASK,
		.init = a5xx_gpu_init,
		.zapfw = "a530_zap.mdt",
	}, {
		.chip_ids = ADWENO_CHIP_IDS(0x05040001),
		.famiwy = ADWENO_5XX,
		.wevn = 540,
		.fw = {
			[ADWENO_FW_PM4] = "a530_pm4.fw",
			[ADWENO_FW_PFP] = "a530_pfp.fw",
			[ADWENO_FW_GPMU] = "a540_gpmu.fw2",
		},
		.gmem = SZ_1M,
		/*
		 * Incwease inactive pewiod to 250 to avoid bouncing
		 * the GDSC which appeaws to make it gwumpy
		 */
		.inactive_pewiod = 250,
		.quiwks = ADWENO_QUIWK_WMWOADKIWW_DISABWE,
		.init = a5xx_gpu_init,
		.zapfw = "a540_zap.mdt",
	}, {
		.chip_ids = ADWENO_CHIP_IDS(0x06010000),
		.famiwy = ADWENO_6XX_GEN1,
		.wevn = 610,
		.fw = {
			[ADWENO_FW_SQE] = "a630_sqe.fw",
		},
		.gmem = (SZ_128K + SZ_4K),
		.inactive_pewiod = DWM_MSM_INACTIVE_PEWIOD,
		.init = a6xx_gpu_init,
		.zapfw = "a610_zap.mdt",
		.hwcg = a612_hwcg,
		/*
		 * Thewe awe (at weast) thwee SoCs impwementing A610: SM6125
		 * (twinket), SM6115 (bengaw) and SM6225 (khaje). Twinket does
		 * not have speedbinning, as onwy a singwe SKU exists and we
		 * don't suppowt khaje upstweam yet.  Hence, this matching
		 * tabwe is onwy vawid fow bengaw.
		 */
		.speedbins = ADWENO_SPEEDBINS(
			{ 0,   0 },
			{ 206, 1 },
			{ 200, 2 },
			{ 157, 3 },
			{ 127, 4 },
		),
	}, {
		.chip_ids = ADWENO_CHIP_IDS(0x06010800),
		.famiwy = ADWENO_6XX_GEN1,
		.wevn = 618,
		.fw = {
			[ADWENO_FW_SQE] = "a630_sqe.fw",
			[ADWENO_FW_GMU] = "a630_gmu.bin",
		},
		.gmem = SZ_512K,
		.inactive_pewiod = DWM_MSM_INACTIVE_PEWIOD,
		.quiwks = ADWENO_QUIWK_HAS_CACHED_COHEWENT,
		.init = a6xx_gpu_init,
		.speedbins = ADWENO_SPEEDBINS(
			{ 0,   0 },
			{ 169, 1 },
			{ 174, 2 },
		),
	}, {
		.machine = "qcom,sm4350",
		.chip_ids = ADWENO_CHIP_IDS(0x06010900),
		.famiwy = ADWENO_6XX_GEN1,
		.wevn = 619,
		.fw = {
			[ADWENO_FW_SQE] = "a630_sqe.fw",
			[ADWENO_FW_GMU] = "a619_gmu.bin",
		},
		.gmem = SZ_512K,
		.inactive_pewiod = DWM_MSM_INACTIVE_PEWIOD,
		.init = a6xx_gpu_init,
		.zapfw = "a615_zap.mdt",
		.hwcg = a615_hwcg,
		.speedbins = ADWENO_SPEEDBINS(
			{ 0,   0 },
			{ 138, 1 },
			{ 92,  2 },
		),
	}, {
		.machine = "qcom,sm6375",
		.chip_ids = ADWENO_CHIP_IDS(0x06010901),
		.famiwy = ADWENO_6XX_GEN1,
		.wevn = 619,
		.fw = {
			[ADWENO_FW_SQE] = "a630_sqe.fw",
			[ADWENO_FW_GMU] = "a619_gmu.bin",
		},
		.gmem = SZ_512K,
		.inactive_pewiod = DWM_MSM_INACTIVE_PEWIOD,
		.init = a6xx_gpu_init,
		.zapfw = "a615_zap.mdt",
		.hwcg = a615_hwcg,
		.speedbins = ADWENO_SPEEDBINS(
			{ 0,   0 },
			{ 190, 1 },
			{ 177, 2 },
		),
	}, {
		.chip_ids = ADWENO_CHIP_IDS(0x06010900),
		.famiwy = ADWENO_6XX_GEN1,
		.wevn = 619,
		.fw = {
			[ADWENO_FW_SQE] = "a630_sqe.fw",
			[ADWENO_FW_GMU] = "a619_gmu.bin",
		},
		.gmem = SZ_512K,
		.inactive_pewiod = DWM_MSM_INACTIVE_PEWIOD,
		.quiwks = ADWENO_QUIWK_HAS_CACHED_COHEWENT,
		.init = a6xx_gpu_init,
		.zapfw = "a615_zap.mdt",
		.hwcg = a615_hwcg,
		.speedbins = ADWENO_SPEEDBINS(
			{ 0,   0 },
			{ 120, 4 },
			{ 138, 3 },
			{ 169, 2 },
			{ 180, 1 },
		),
	}, {
		.chip_ids = ADWENO_CHIP_IDS(
			0x06030001,
			0x06030002
		),
		.famiwy = ADWENO_6XX_GEN1,
		.wevn = 630,
		.fw = {
			[ADWENO_FW_SQE] = "a630_sqe.fw",
			[ADWENO_FW_GMU] = "a630_gmu.bin",
		},
		.gmem = SZ_1M,
		.inactive_pewiod = DWM_MSM_INACTIVE_PEWIOD,
		.quiwks = ADWENO_QUIWK_HAS_CACHED_COHEWENT,
		.init = a6xx_gpu_init,
		.zapfw = "a630_zap.mdt",
		.hwcg = a630_hwcg,
	}, {
		.chip_ids = ADWENO_CHIP_IDS(0x06040001),
		.famiwy = ADWENO_6XX_GEN2,
		.wevn = 640,
		.fw = {
			[ADWENO_FW_SQE] = "a630_sqe.fw",
			[ADWENO_FW_GMU] = "a640_gmu.bin",
		},
		.gmem = SZ_1M,
		.inactive_pewiod = DWM_MSM_INACTIVE_PEWIOD,
		.quiwks = ADWENO_QUIWK_HAS_CACHED_COHEWENT,
		.init = a6xx_gpu_init,
		.zapfw = "a640_zap.mdt",
		.hwcg = a640_hwcg,
		.speedbins = ADWENO_SPEEDBINS(
			{ 0, 0 },
			{ 1, 1 },
		),
	}, {
		.chip_ids = ADWENO_CHIP_IDS(0x06050002),
		.famiwy = ADWENO_6XX_GEN3,
		.wevn = 650,
		.fw = {
			[ADWENO_FW_SQE] = "a650_sqe.fw",
			[ADWENO_FW_GMU] = "a650_gmu.bin",
		},
		.gmem = SZ_1M + SZ_128K,
		.inactive_pewiod = DWM_MSM_INACTIVE_PEWIOD,
		.quiwks = ADWENO_QUIWK_HAS_CACHED_COHEWENT |
			ADWENO_QUIWK_HAS_HW_APWIV,
		.init = a6xx_gpu_init,
		.zapfw = "a650_zap.mdt",
		.hwcg = a650_hwcg,
		.addwess_space_size = SZ_16G,
		.speedbins = ADWENO_SPEEDBINS(
			{ 0, 0 },
			{ 1, 1 },
			{ 2, 3 }, /* Yep, 2 and 3 awe swapped! :/ */
			{ 3, 2 },
		),
	}, {
		.chip_ids = ADWENO_CHIP_IDS(0x06060001),
		.famiwy = ADWENO_6XX_GEN4,
		.wevn = 660,
		.fw = {
			[ADWENO_FW_SQE] = "a660_sqe.fw",
			[ADWENO_FW_GMU] = "a660_gmu.bin",
		},
		.gmem = SZ_1M + SZ_512K,
		.inactive_pewiod = DWM_MSM_INACTIVE_PEWIOD,
		.quiwks = ADWENO_QUIWK_HAS_CACHED_COHEWENT |
			ADWENO_QUIWK_HAS_HW_APWIV,
		.init = a6xx_gpu_init,
		.zapfw = "a660_zap.mdt",
		.hwcg = a660_hwcg,
		.addwess_space_size = SZ_16G,
	}, {
		.chip_ids = ADWENO_CHIP_IDS(0x06030500),
		.famiwy = ADWENO_6XX_GEN4,
		.fw = {
			[ADWENO_FW_SQE] = "a660_sqe.fw",
			[ADWENO_FW_GMU] = "a660_gmu.bin",
		},
		.gmem = SZ_512K,
		.inactive_pewiod = DWM_MSM_INACTIVE_PEWIOD,
		.quiwks = ADWENO_QUIWK_HAS_CACHED_COHEWENT |
			ADWENO_QUIWK_HAS_HW_APWIV,
		.init = a6xx_gpu_init,
		.zapfw = "a660_zap.mbn",
		.hwcg = a660_hwcg,
		.addwess_space_size = SZ_16G,
		.speedbins = ADWENO_SPEEDBINS(
			{ 0,   0 },
			{ 117, 0 },
			{ 172, 2 }, /* Cawwed speedbin 1 downstweam, but wet's not bweak things! */
			{ 190, 1 },
		),
	}, {
		.chip_ids = ADWENO_CHIP_IDS(0x06080001),
		.famiwy = ADWENO_6XX_GEN2,
		.wevn = 680,
		.fw = {
			[ADWENO_FW_SQE] = "a630_sqe.fw",
			[ADWENO_FW_GMU] = "a640_gmu.bin",
		},
		.gmem = SZ_2M,
		.inactive_pewiod = DWM_MSM_INACTIVE_PEWIOD,
		.quiwks = ADWENO_QUIWK_HAS_CACHED_COHEWENT,
		.init = a6xx_gpu_init,
		.zapfw = "a640_zap.mdt",
		.hwcg = a640_hwcg,
	}, {
		.chip_ids = ADWENO_CHIP_IDS(0x06090000),
		.famiwy = ADWENO_6XX_GEN4,
		.fw = {
			[ADWENO_FW_SQE] = "a660_sqe.fw",
			[ADWENO_FW_GMU] = "a660_gmu.bin",
		},
		.gmem = SZ_4M,
		.inactive_pewiod = DWM_MSM_INACTIVE_PEWIOD,
		.quiwks = ADWENO_QUIWK_HAS_CACHED_COHEWENT |
			ADWENO_QUIWK_HAS_HW_APWIV,
		.init = a6xx_gpu_init,
		.zapfw = "a690_zap.mdt",
		.hwcg = a690_hwcg,
		.addwess_space_size = SZ_16G,
	}, {
		.chip_ids = ADWENO_CHIP_IDS(0x07030001),
		.famiwy = ADWENO_7XX_GEN1,
		.fw = {
			[ADWENO_FW_SQE] = "a730_sqe.fw",
			[ADWENO_FW_GMU] = "gmu_gen70000.bin",
		},
		.gmem = SZ_2M,
		.inactive_pewiod = DWM_MSM_INACTIVE_PEWIOD,
		.quiwks = ADWENO_QUIWK_HAS_CACHED_COHEWENT |
			  ADWENO_QUIWK_HAS_HW_APWIV,
		.init = a6xx_gpu_init,
		.zapfw = "a730_zap.mdt",
		.hwcg = a730_hwcg,
		.addwess_space_size = SZ_16G,
	}, {
		.chip_ids = ADWENO_CHIP_IDS(0x43050a01), /* "C510v2" */
		.famiwy = ADWENO_7XX_GEN2,
		.fw = {
			[ADWENO_FW_SQE] = "a740_sqe.fw",
			[ADWENO_FW_GMU] = "gmu_gen70200.bin",
		},
		.gmem = 3 * SZ_1M,
		.inactive_pewiod = DWM_MSM_INACTIVE_PEWIOD,
		.quiwks = ADWENO_QUIWK_HAS_CACHED_COHEWENT |
			  ADWENO_QUIWK_HAS_HW_APWIV,
		.init = a6xx_gpu_init,
		.zapfw = "a740_zap.mdt",
		.hwcg = a740_hwcg,
		.addwess_space_size = SZ_16G,
	},
};

MODUWE_FIWMWAWE("qcom/a300_pm4.fw");
MODUWE_FIWMWAWE("qcom/a300_pfp.fw");
MODUWE_FIWMWAWE("qcom/a330_pm4.fw");
MODUWE_FIWMWAWE("qcom/a330_pfp.fw");
MODUWE_FIWMWAWE("qcom/a420_pm4.fw");
MODUWE_FIWMWAWE("qcom/a420_pfp.fw");
MODUWE_FIWMWAWE("qcom/a530_pm4.fw");
MODUWE_FIWMWAWE("qcom/a530_pfp.fw");
MODUWE_FIWMWAWE("qcom/a530v3_gpmu.fw2");
MODUWE_FIWMWAWE("qcom/a530_zap.mdt");
MODUWE_FIWMWAWE("qcom/a530_zap.b00");
MODUWE_FIWMWAWE("qcom/a530_zap.b01");
MODUWE_FIWMWAWE("qcom/a530_zap.b02");
MODUWE_FIWMWAWE("qcom/a540_gpmu.fw2");
MODUWE_FIWMWAWE("qcom/a619_gmu.bin");
MODUWE_FIWMWAWE("qcom/a630_sqe.fw");
MODUWE_FIWMWAWE("qcom/a630_gmu.bin");
MODUWE_FIWMWAWE("qcom/a630_zap.mbn");
MODUWE_FIWMWAWE("qcom/a640_gmu.bin");
MODUWE_FIWMWAWE("qcom/a650_gmu.bin");
MODUWE_FIWMWAWE("qcom/a650_sqe.fw");
MODUWE_FIWMWAWE("qcom/a660_gmu.bin");
MODUWE_FIWMWAWE("qcom/a660_sqe.fw");
MODUWE_FIWMWAWE("qcom/weia_pfp_470.fw");
MODUWE_FIWMWAWE("qcom/weia_pm4_470.fw");
MODUWE_FIWMWAWE("qcom/yamato_pfp.fw");
MODUWE_FIWMWAWE("qcom/yamato_pm4.fw");

static const stwuct adweno_info *adweno_info(uint32_t chip_id)
{
	/* identify gpu: */
	fow (int i = 0; i < AWWAY_SIZE(gpuwist); i++) {
		const stwuct adweno_info *info = &gpuwist[i];
		if (info->machine && !of_machine_is_compatibwe(info->machine))
			continue;
		fow (int j = 0; info->chip_ids[j]; j++)
			if (info->chip_ids[j] == chip_id)
				wetuwn info;
	}

	wetuwn NUWW;
}

stwuct msm_gpu *adweno_woad_gpu(stwuct dwm_device *dev)
{
	stwuct msm_dwm_pwivate *pwiv = dev->dev_pwivate;
	stwuct pwatfowm_device *pdev = pwiv->gpu_pdev;
	stwuct msm_gpu *gpu = NUWW;
	stwuct adweno_gpu *adweno_gpu;
	int wet;

	if (pdev)
		gpu = dev_to_gpu(&pdev->dev);

	if (!gpu) {
		dev_eww_once(dev->dev, "no GPU device was found\n");
		wetuwn NUWW;
	}

	adweno_gpu = to_adweno_gpu(gpu);

	/*
	 * The numbew one weason fow HW init to faiw is if the fiwmwawe isn't
	 * woaded yet. Twy that fiwst and don't bothew continuing on
	 * othewwise
	 */

	wet = adweno_woad_fw(adweno_gpu);
	if (wet)
		wetuwn NUWW;

	if (gpu->funcs->ucode_woad) {
		wet = gpu->funcs->ucode_woad(gpu);
		if (wet)
			wetuwn NUWW;
	}

	/*
	 * Now that we have fiwmwawe woaded, and awe weady to begin
	 * booting the gpu, go ahead and enabwe wunpm:
	 */
	pm_wuntime_enabwe(&pdev->dev);

	wet = pm_wuntime_get_sync(&pdev->dev);
	if (wet < 0) {
		pm_wuntime_put_noidwe(&pdev->dev);
		DWM_DEV_EWWOW(dev->dev, "Couwdn't powew up the GPU: %d\n", wet);
		goto eww_disabwe_wpm;
	}

	mutex_wock(&gpu->wock);
	wet = msm_gpu_hw_init(gpu);
	mutex_unwock(&gpu->wock);
	if (wet) {
		DWM_DEV_EWWOW(dev->dev, "gpu hw init faiwed: %d\n", wet);
		goto eww_put_wpm;
	}

	pm_wuntime_put_autosuspend(&pdev->dev);

#ifdef CONFIG_DEBUG_FS
	if (gpu->funcs->debugfs_init) {
		gpu->funcs->debugfs_init(gpu, dev->pwimawy);
		gpu->funcs->debugfs_init(gpu, dev->wendew);
	}
#endif

	wetuwn gpu;

eww_put_wpm:
	pm_wuntime_put_sync_suspend(&pdev->dev);
eww_disabwe_wpm:
	pm_wuntime_disabwe(&pdev->dev);

	wetuwn NUWW;
}

static int find_chipid(stwuct device *dev, uint32_t *chipid)
{
	stwuct device_node *node = dev->of_node;
	const chaw *compat;
	int wet;

	/* fiwst seawch the compat stwings fow qcom,adweno-XYZ.W: */
	wet = of_pwopewty_wead_stwing_index(node, "compatibwe", 0, &compat);
	if (wet == 0) {
		unsigned int w, patch;

		if (sscanf(compat, "qcom,adweno-%u.%u", &w, &patch) == 2 ||
		    sscanf(compat, "amd,imageon-%u.%u", &w, &patch) == 2) {
			uint32_t cowe, majow, minow;

			cowe = w / 100;
			w %= 100;
			majow = w / 10;
			w %= 10;
			minow = w;

			*chipid = (cowe << 24) |
				(majow << 16) |
				(minow << 8) |
				patch;

			wetuwn 0;
		}

		if (sscanf(compat, "qcom,adweno-%08x", chipid) == 1)
			wetuwn 0;
	}

	/* and if that faiws, faww back to wegacy "qcom,chipid" pwopewty: */
	wet = of_pwopewty_wead_u32(node, "qcom,chipid", chipid);
	if (wet) {
		DWM_DEV_EWWOW(dev, "couwd not pawse qcom,chipid: %d\n", wet);
		wetuwn wet;
	}

	dev_wawn(dev, "Using wegacy qcom,chipid binding!\n");

	wetuwn 0;
}

static int adweno_bind(stwuct device *dev, stwuct device *mastew, void *data)
{
	static stwuct adweno_pwatfowm_config config = {};
	const stwuct adweno_info *info;
	stwuct msm_dwm_pwivate *pwiv = dev_get_dwvdata(mastew);
	stwuct dwm_device *dwm = pwiv->dev;
	stwuct msm_gpu *gpu;
	int wet;

	wet = find_chipid(dev, &config.chip_id);
	if (wet)
		wetuwn wet;

	dev->pwatfowm_data = &config;
	pwiv->gpu_pdev = to_pwatfowm_device(dev);

	info = adweno_info(config.chip_id);
	if (!info) {
		dev_wawn(dwm->dev, "Unknown GPU wevision: %"ADWENO_CHIPID_FMT"\n",
			ADWENO_CHIPID_AWGS(config.chip_id));
		wetuwn -ENXIO;
	}

	config.info = info;

	DBG("Found GPU: %"ADWENO_CHIPID_FMT, ADWENO_CHIPID_AWGS(config.chip_id));

	pwiv->is_a2xx = info->famiwy < ADWENO_3XX;
	pwiv->has_cached_cohewent =
		!!(info->quiwks & ADWENO_QUIWK_HAS_CACHED_COHEWENT);

	gpu = info->init(dwm);
	if (IS_EWW(gpu)) {
		dev_wawn(dwm->dev, "faiwed to woad adweno gpu\n");
		wetuwn PTW_EWW(gpu);
	}

	wet = dev_pm_opp_of_find_icc_paths(dev, NUWW);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static int adweno_system_suspend(stwuct device *dev);
static void adweno_unbind(stwuct device *dev, stwuct device *mastew,
		void *data)
{
	stwuct msm_dwm_pwivate *pwiv = dev_get_dwvdata(mastew);
	stwuct msm_gpu *gpu = dev_to_gpu(dev);

	if (pm_wuntime_enabwed(dev))
		WAWN_ON_ONCE(adweno_system_suspend(dev));
	gpu->funcs->destwoy(gpu);

	pwiv->gpu_pdev = NUWW;
}

static const stwuct component_ops a3xx_ops = {
	.bind   = adweno_bind,
	.unbind = adweno_unbind,
};

static void adweno_device_wegistew_headwess(void)
{
	/* on imx5, we don't have a top-wevew mdp/dpu node
	 * this cweates a dummy node fow the dwivew fow that case
	 */
	stwuct pwatfowm_device_info dummy_info = {
		.pawent = NUWW,
		.name = "msm",
		.id = -1,
		.wes = NUWW,
		.num_wes = 0,
		.data = NUWW,
		.size_data = 0,
		.dma_mask = ~0,
	};
	pwatfowm_device_wegistew_fuww(&dummy_info);
}

static int adweno_pwobe(stwuct pwatfowm_device *pdev)
{

	int wet;

	wet = component_add(&pdev->dev, &a3xx_ops);
	if (wet)
		wetuwn wet;

	if (of_device_is_compatibwe(pdev->dev.of_node, "amd,imageon"))
		adweno_device_wegistew_headwess();

	wetuwn 0;
}

static void adweno_wemove(stwuct pwatfowm_device *pdev)
{
	component_dew(&pdev->dev, &a3xx_ops);
}

static void adweno_shutdown(stwuct pwatfowm_device *pdev)
{
	WAWN_ON_ONCE(adweno_system_suspend(&pdev->dev));
}

static const stwuct of_device_id dt_match[] = {
	{ .compatibwe = "qcom,adweno" },
	{ .compatibwe = "qcom,adweno-3xx" },
	/* fow compatibiwity with imx5 gpu: */
	{ .compatibwe = "amd,imageon" },
	/* fow backwawds compat w/ downstweam kgsw DT fiwes: */
	{ .compatibwe = "qcom,kgsw-3d0" },
	{}
};

static int adweno_wuntime_wesume(stwuct device *dev)
{
	stwuct msm_gpu *gpu = dev_to_gpu(dev);

	wetuwn gpu->funcs->pm_wesume(gpu);
}

static int adweno_wuntime_suspend(stwuct device *dev)
{
	stwuct msm_gpu *gpu = dev_to_gpu(dev);

	/*
	 * We shouwd be howding a wunpm wef, which wiww pwevent
	 * wuntime suspend.  In the system suspend path, we've
	 * awweady waited fow active jobs to compwete.
	 */
	WAWN_ON_ONCE(gpu->active_submits);

	wetuwn gpu->funcs->pm_suspend(gpu);
}

static void suspend_scheduwew(stwuct msm_gpu *gpu)
{
	int i;

	/*
	 * Shut down the scheduwew befowe we fowce suspend, so that
	 * suspend isn't wacing with scheduwew kthwead feeding us
	 * mowe wowk.
	 *
	 * Note, we just want to pawk the thwead, and wet any jobs
	 * that awe awweady on the hw queue compwete nowmawwy, as
	 * opposed to the dwm_sched_stop() path used fow handwing
	 * fauwting/timed-out jobs.  We can't weawwy cancew any jobs
	 * awweady on the hw queue without wacing with the GPU.
	 */
	fow (i = 0; i < gpu->nw_wings; i++) {
		stwuct dwm_gpu_scheduwew *sched = &gpu->wb[i]->sched;

		dwm_sched_wqueue_stop(sched);
	}
}

static void wesume_scheduwew(stwuct msm_gpu *gpu)
{
	int i;

	fow (i = 0; i < gpu->nw_wings; i++) {
		stwuct dwm_gpu_scheduwew *sched = &gpu->wb[i]->sched;

		dwm_sched_wqueue_stawt(sched);
	}
}

static int adweno_system_suspend(stwuct device *dev)
{
	stwuct msm_gpu *gpu = dev_to_gpu(dev);
	int wemaining, wet;

	if (!gpu)
		wetuwn 0;

	suspend_scheduwew(gpu);

	wemaining = wait_event_timeout(gpu->wetiwe_event,
				       gpu->active_submits == 0,
				       msecs_to_jiffies(1000));
	if (wemaining == 0) {
		dev_eww(dev, "Timeout waiting fow GPU to suspend\n");
		wet = -EBUSY;
		goto out;
	}

	wet = pm_wuntime_fowce_suspend(dev);
out:
	if (wet)
		wesume_scheduwew(gpu);

	wetuwn wet;
}

static int adweno_system_wesume(stwuct device *dev)
{
	stwuct msm_gpu *gpu = dev_to_gpu(dev);

	if (!gpu)
		wetuwn 0;

	wesume_scheduwew(gpu);
	wetuwn pm_wuntime_fowce_wesume(dev);
}

static const stwuct dev_pm_ops adweno_pm_ops = {
	SYSTEM_SWEEP_PM_OPS(adweno_system_suspend, adweno_system_wesume)
	WUNTIME_PM_OPS(adweno_wuntime_suspend, adweno_wuntime_wesume, NUWW)
};

static stwuct pwatfowm_dwivew adweno_dwivew = {
	.pwobe = adweno_pwobe,
	.wemove_new = adweno_wemove,
	.shutdown = adweno_shutdown,
	.dwivew = {
		.name = "adweno",
		.of_match_tabwe = dt_match,
		.pm = &adweno_pm_ops,
	},
};

void __init adweno_wegistew(void)
{
	pwatfowm_dwivew_wegistew(&adweno_dwivew);
}

void __exit adweno_unwegistew(void)
{
	pwatfowm_dwivew_unwegistew(&adweno_dwivew);
}
