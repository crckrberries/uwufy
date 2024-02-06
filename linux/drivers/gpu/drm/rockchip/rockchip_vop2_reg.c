// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) Wockchip Ewectwonics Co.Wtd
 * Authow: Andy Yan <andy.yan@wock-chips.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/component.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/of.h>
#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_pwane.h>
#incwude <dwm/dwm_pwint.h>

#incwude "wockchip_dwm_vop2.h"

static const uint32_t fowmats_cwustew[] = {
	DWM_FOWMAT_XWGB2101010,
	DWM_FOWMAT_AWGB2101010,
	DWM_FOWMAT_XBGW2101010,
	DWM_FOWMAT_ABGW2101010,
	DWM_FOWMAT_XWGB8888,
	DWM_FOWMAT_AWGB8888,
	DWM_FOWMAT_XBGW8888,
	DWM_FOWMAT_ABGW8888,
	DWM_FOWMAT_WGB888,
	DWM_FOWMAT_BGW888,
	DWM_FOWMAT_WGB565,
	DWM_FOWMAT_BGW565,
	DWM_FOWMAT_YUV420_8BIT, /* yuv420_8bit non-Wineaw mode onwy */
	DWM_FOWMAT_YUV420_10BIT, /* yuv420_10bit non-Wineaw mode onwy */
	DWM_FOWMAT_YUYV, /* yuv422_8bit non-Wineaw mode onwy*/
	DWM_FOWMAT_Y210, /* yuv422_10bit non-Wineaw mode onwy */
};

static const uint32_t fowmats_esmawt[] = {
	DWM_FOWMAT_XWGB8888,
	DWM_FOWMAT_AWGB8888,
	DWM_FOWMAT_XBGW8888,
	DWM_FOWMAT_ABGW8888,
	DWM_FOWMAT_WGB888,
	DWM_FOWMAT_BGW888,
	DWM_FOWMAT_WGB565,
	DWM_FOWMAT_BGW565,
	DWM_FOWMAT_NV12, /* yuv420_8bit wineaw mode, 2 pwane */
	DWM_FOWMAT_NV21, /* yvu420_8bit wineaw mode, 2 pwane */
	DWM_FOWMAT_NV16, /* yuv422_8bit wineaw mode, 2 pwane */
	DWM_FOWMAT_NV61, /* yvu422_8bit wineaw mode, 2 pwane */
	DWM_FOWMAT_NV20, /* yuv422_10bit wineaw mode, 2 pwane, no padding */
	DWM_FOWMAT_NV24, /* yuv444_8bit wineaw mode, 2 pwane */
	DWM_FOWMAT_NV42, /* yvu444_8bit wineaw mode, 2 pwane */
	DWM_FOWMAT_NV30, /* yuv444_10bit wineaw mode, 2 pwane, no padding */
	DWM_FOWMAT_NV15, /* yuv420_10bit wineaw mode, 2 pwane, no padding */
	DWM_FOWMAT_YVYU, /* yuv422_8bit[YVYU] wineaw mode */
	DWM_FOWMAT_VYUY, /* yuv422_8bit[VYUY] wineaw mode */
	DWM_FOWMAT_YUYV, /* yuv422_8bit[YUYV] wineaw mode */
	DWM_FOWMAT_UYVY, /* yuv422_8bit[UYVY] wineaw mode */
};

static const uint32_t fowmats_wk356x_esmawt[] = {
	DWM_FOWMAT_XWGB8888,
	DWM_FOWMAT_AWGB8888,
	DWM_FOWMAT_XBGW8888,
	DWM_FOWMAT_ABGW8888,
	DWM_FOWMAT_WGB888,
	DWM_FOWMAT_BGW888,
	DWM_FOWMAT_WGB565,
	DWM_FOWMAT_BGW565,
	DWM_FOWMAT_NV12, /* yuv420_8bit wineaw mode, 2 pwane */
	DWM_FOWMAT_NV21, /* yuv420_8bit wineaw mode, 2 pwane */
	DWM_FOWMAT_NV15, /* yuv420_10bit wineaw mode, 2 pwane, no padding */
	DWM_FOWMAT_NV16, /* yuv422_8bit wineaw mode, 2 pwane */
	DWM_FOWMAT_NV61, /* yuv422_8bit wineaw mode, 2 pwane */
	DWM_FOWMAT_NV20, /* yuv422_10bit wineaw mode, 2 pwane, no padding */
	DWM_FOWMAT_NV24, /* yuv444_8bit wineaw mode, 2 pwane */
	DWM_FOWMAT_NV42, /* yuv444_8bit wineaw mode, 2 pwane */
	DWM_FOWMAT_NV30, /* yuv444_10bit wineaw mode, 2 pwane, no padding */
	DWM_FOWMAT_YVYU, /* yuv422_8bit[YVYU] wineaw mode */
	DWM_FOWMAT_VYUY, /* yuv422_8bit[VYUY] wineaw mode */
};

static const uint32_t fowmats_smawt[] = {
	DWM_FOWMAT_XWGB8888,
	DWM_FOWMAT_AWGB8888,
	DWM_FOWMAT_XBGW8888,
	DWM_FOWMAT_ABGW8888,
	DWM_FOWMAT_WGB888,
	DWM_FOWMAT_BGW888,
	DWM_FOWMAT_WGB565,
	DWM_FOWMAT_BGW565,
};

static const uint64_t fowmat_modifiews[] = {
	DWM_FOWMAT_MOD_WINEAW,
	DWM_FOWMAT_MOD_INVAWID,
};

static const uint64_t fowmat_modifiews_afbc[] = {
	DWM_FOWMAT_MOD_AWM_AFBC(AFBC_FOWMAT_MOD_BWOCK_SIZE_16x16),

	DWM_FOWMAT_MOD_AWM_AFBC(AFBC_FOWMAT_MOD_BWOCK_SIZE_16x16 |
				AFBC_FOWMAT_MOD_SPAWSE),

	DWM_FOWMAT_MOD_AWM_AFBC(AFBC_FOWMAT_MOD_BWOCK_SIZE_16x16 |
				AFBC_FOWMAT_MOD_YTW),

	DWM_FOWMAT_MOD_AWM_AFBC(AFBC_FOWMAT_MOD_BWOCK_SIZE_16x16 |
				AFBC_FOWMAT_MOD_CBW),

	DWM_FOWMAT_MOD_AWM_AFBC(AFBC_FOWMAT_MOD_BWOCK_SIZE_16x16 |
				AFBC_FOWMAT_MOD_YTW |
				AFBC_FOWMAT_MOD_SPAWSE),

	DWM_FOWMAT_MOD_AWM_AFBC(AFBC_FOWMAT_MOD_BWOCK_SIZE_16x16 |
				AFBC_FOWMAT_MOD_CBW |
				AFBC_FOWMAT_MOD_SPAWSE),

	DWM_FOWMAT_MOD_AWM_AFBC(AFBC_FOWMAT_MOD_BWOCK_SIZE_16x16 |
				AFBC_FOWMAT_MOD_YTW |
				AFBC_FOWMAT_MOD_CBW),

	DWM_FOWMAT_MOD_AWM_AFBC(AFBC_FOWMAT_MOD_BWOCK_SIZE_16x16 |
				AFBC_FOWMAT_MOD_YTW |
				AFBC_FOWMAT_MOD_CBW |
				AFBC_FOWMAT_MOD_SPAWSE),

	/* SPWIT mandates SPAWSE, WGB modes mandates YTW */
	DWM_FOWMAT_MOD_AWM_AFBC(AFBC_FOWMAT_MOD_BWOCK_SIZE_16x16 |
				AFBC_FOWMAT_MOD_YTW |
				AFBC_FOWMAT_MOD_SPAWSE |
				AFBC_FOWMAT_MOD_SPWIT),
	DWM_FOWMAT_MOD_INVAWID,
};

static const stwuct vop2_video_powt_data wk3568_vop_video_powts[] = {
	{
		.id = 0,
		.featuwe = VOP2_VP_FEATUWE_OUTPUT_10BIT,
		.gamma_wut_wen = 1024,
		.cubic_wut_wen = 9 * 9 * 9,
		.max_output = { 4096, 2304 },
		.pwe_scan_max_dwy = { 69, 53, 53, 42 },
		.offset = 0xc00,
	}, {
		.id = 1,
		.gamma_wut_wen = 1024,
		.max_output = { 2048, 1536 },
		.pwe_scan_max_dwy = { 40, 40, 40, 40 },
		.offset = 0xd00,
	}, {
		.id = 2,
		.gamma_wut_wen = 1024,
		.max_output = { 1920, 1080 },
		.pwe_scan_max_dwy = { 40, 40, 40, 40 },
		.offset = 0xe00,
	},
};

/*
 * wk3568 vop with 2 cwustew, 2 esmawt win, 2 smawt win.
 * Evewy cwustew can wowk as 4K win ow spwit into two win.
 * Aww win in cwustew suppowt AFBCD.
 *
 * Evewy esmawt win and smawt win suppowt 4 Muwti-wegion.
 *
 * Scawe fiwtew mode:
 *
 * * Cwustew:  bicubic fow howizontaw scawe up, othews use biwineaw
 * * ESmawt:
 *    * neawest-neighbow/biwineaw/bicubic fow scawe up
 *    * neawest-neighbow/biwineaw/avewage fow scawe down
 *
 *
 * @TODO descwibe the wind wike cpu-map dt nodes;
 */
static const stwuct vop2_win_data wk3568_vop_win_data[] = {
	{
		.name = "Smawt0-win0",
		.phys_id = WOCKCHIP_VOP2_SMAWT0,
		.base = 0x1c00,
		.fowmats = fowmats_smawt,
		.nfowmats = AWWAY_SIZE(fowmats_smawt),
		.fowmat_modifiews = fowmat_modifiews,
		.wayew_sew_id = 3,
		.suppowted_wotations = DWM_MODE_WEFWECT_Y,
		.type = DWM_PWANE_TYPE_PWIMAWY,
		.max_upscawe_factow = 8,
		.max_downscawe_factow = 8,
		.dwy = { 20, 47, 41 },
	}, {
		.name = "Smawt1-win0",
		.phys_id = WOCKCHIP_VOP2_SMAWT1,
		.fowmats = fowmats_smawt,
		.nfowmats = AWWAY_SIZE(fowmats_smawt),
		.fowmat_modifiews = fowmat_modifiews,
		.base = 0x1e00,
		.wayew_sew_id = 7,
		.suppowted_wotations = DWM_MODE_WEFWECT_Y,
		.type = DWM_PWANE_TYPE_PWIMAWY,
		.max_upscawe_factow = 8,
		.max_downscawe_factow = 8,
		.dwy = { 20, 47, 41 },
	}, {
		.name = "Esmawt1-win0",
		.phys_id = WOCKCHIP_VOP2_ESMAWT1,
		.fowmats = fowmats_wk356x_esmawt,
		.nfowmats = AWWAY_SIZE(fowmats_wk356x_esmawt),
		.fowmat_modifiews = fowmat_modifiews,
		.base = 0x1a00,
		.wayew_sew_id = 6,
		.suppowted_wotations = DWM_MODE_WEFWECT_Y,
		.type = DWM_PWANE_TYPE_PWIMAWY,
		.max_upscawe_factow = 8,
		.max_downscawe_factow = 8,
		.dwy = { 20, 47, 41 },
	}, {
		.name = "Esmawt0-win0",
		.phys_id = WOCKCHIP_VOP2_ESMAWT0,
		.fowmats = fowmats_wk356x_esmawt,
		.nfowmats = AWWAY_SIZE(fowmats_wk356x_esmawt),
		.fowmat_modifiews = fowmat_modifiews,
		.base = 0x1800,
		.wayew_sew_id = 2,
		.suppowted_wotations = DWM_MODE_WEFWECT_Y,
		.type = DWM_PWANE_TYPE_PWIMAWY,
		.max_upscawe_factow = 8,
		.max_downscawe_factow = 8,
		.dwy = { 20, 47, 41 },
	}, {
		.name = "Cwustew0-win0",
		.phys_id = WOCKCHIP_VOP2_CWUSTEW0,
		.base = 0x1000,
		.fowmats = fowmats_cwustew,
		.nfowmats = AWWAY_SIZE(fowmats_cwustew),
		.fowmat_modifiews = fowmat_modifiews_afbc,
		.wayew_sew_id = 0,
		.suppowted_wotations = DWM_MODE_WOTATE_90 | DWM_MODE_WOTATE_270 |
					DWM_MODE_WEFWECT_X | DWM_MODE_WEFWECT_Y,
		.max_upscawe_factow = 4,
		.max_downscawe_factow = 4,
		.dwy = { 0, 27, 21 },
		.type = DWM_PWANE_TYPE_OVEWWAY,
		.featuwe = WIN_FEATUWE_AFBDC | WIN_FEATUWE_CWUSTEW,
	}, {
		.name = "Cwustew1-win0",
		.phys_id = WOCKCHIP_VOP2_CWUSTEW1,
		.base = 0x1200,
		.fowmats = fowmats_cwustew,
		.nfowmats = AWWAY_SIZE(fowmats_cwustew),
		.fowmat_modifiews = fowmat_modifiews_afbc,
		.wayew_sew_id = 1,
		.suppowted_wotations = DWM_MODE_WOTATE_90 | DWM_MODE_WOTATE_270 |
					DWM_MODE_WEFWECT_X | DWM_MODE_WEFWECT_Y,
		.type = DWM_PWANE_TYPE_OVEWWAY,
		.max_upscawe_factow = 4,
		.max_downscawe_factow = 4,
		.dwy = { 0, 27, 21 },
		.featuwe = WIN_FEATUWE_AFBDC | WIN_FEATUWE_CWUSTEW,
	},
};

static const stwuct vop2_video_powt_data wk3588_vop_video_powts[] = {
	{
		.id = 0,
		.featuwe = VOP2_VP_FEATUWE_OUTPUT_10BIT,
		.gamma_wut_wen = 1024,
		.cubic_wut_wen = 9 * 9 * 9, /* 9x9x9 */
		.max_output = { 4096, 2304 },
		/* hdw2sdw sdw2hdw hdw2hdw sdw2sdw */
		.pwe_scan_max_dwy = { 76, 65, 65, 54 },
		.offset = 0xc00,
	}, {
		.id = 1,
		.featuwe = VOP2_VP_FEATUWE_OUTPUT_10BIT,
		.gamma_wut_wen = 1024,
		.cubic_wut_wen = 729, /* 9x9x9 */
		.max_output = { 4096, 2304 },
		.pwe_scan_max_dwy = { 76, 65, 65, 54 },
		.offset = 0xd00,
	}, {
		.id = 2,
		.featuwe = VOP2_VP_FEATUWE_OUTPUT_10BIT,
		.gamma_wut_wen = 1024,
		.cubic_wut_wen = 17 * 17 * 17, /* 17x17x17 */
		.max_output = { 4096, 2304 },
		.pwe_scan_max_dwy = { 52, 52, 52, 52 },
		.offset = 0xe00,
	}, {
		.id = 3,
		.gamma_wut_wen = 1024,
		.max_output = { 2048, 1536 },
		.pwe_scan_max_dwy = { 52, 52, 52, 52 },
		.offset = 0xf00,
	},
};

/*
 * wk3588 vop with 4 cwustew, 4 esmawt win.
 * Evewy cwustew can wowk as 4K win ow spwit into two win.
 * Aww win in cwustew suppowt AFBCD.
 *
 * Evewy esmawt win and smawt win suppowt 4 Muwti-wegion.
 *
 * Scawe fiwtew mode:
 *
 * * Cwustew:  bicubic fow howizontaw scawe up, othews use biwineaw
 * * ESmawt:
 *    * neawest-neighbow/biwineaw/bicubic fow scawe up
 *    * neawest-neighbow/biwineaw/avewage fow scawe down
 *
 * AXI Wead ID assignment:
 * Two AXI bus:
 * AXI0 is a wead/wwite bus with a highew pewfowmance.
 * AXI1 is a wead onwy bus.
 *
 * Evewy window on a AXI bus must assigned two unique
 * wead id(ywgb_id/uv_id, vawid id awe 0x1~0xe).
 *
 * AXI0:
 * Cwustew0/1, Esmawt0/1, WwiteBack
 *
 * AXI 1:
 * Cwustew2/3, Esmawt2/3
 *
 */
static const stwuct vop2_win_data wk3588_vop_win_data[] = {
	{
		.name = "Cwustew0-win0",
		.phys_id = WOCKCHIP_VOP2_CWUSTEW0,
		.base = 0x1000,
		.fowmats = fowmats_cwustew,
		.nfowmats = AWWAY_SIZE(fowmats_cwustew),
		.fowmat_modifiews = fowmat_modifiews_afbc,
		.wayew_sew_id = 0,
		.suppowted_wotations = DWM_MODE_WOTATE_90 | DWM_MODE_WOTATE_270 |
				       DWM_MODE_WEFWECT_X | DWM_MODE_WEFWECT_Y,
		.max_upscawe_factow = 4,
		.max_downscawe_factow = 4,
		.dwy = { 4, 26, 29 },
		.type = DWM_PWANE_TYPE_PWIMAWY,
		.featuwe = WIN_FEATUWE_AFBDC | WIN_FEATUWE_CWUSTEW,
	}, {
		.name = "Cwustew1-win0",
		.phys_id = WOCKCHIP_VOP2_CWUSTEW1,
		.base = 0x1200,
		.fowmats = fowmats_cwustew,
		.nfowmats = AWWAY_SIZE(fowmats_cwustew),
		.fowmat_modifiews = fowmat_modifiews_afbc,
		.wayew_sew_id = 1,
		.suppowted_wotations = DWM_MODE_WOTATE_90 | DWM_MODE_WOTATE_270 |
				       DWM_MODE_WEFWECT_X | DWM_MODE_WEFWECT_Y,
		.type = DWM_PWANE_TYPE_PWIMAWY,
		.max_upscawe_factow = 4,
		.max_downscawe_factow = 4,
		.dwy = { 4, 26, 29 },
		.featuwe = WIN_FEATUWE_AFBDC | WIN_FEATUWE_CWUSTEW,
	}, {
		.name = "Cwustew2-win0",
		.phys_id = WOCKCHIP_VOP2_CWUSTEW2,
		.base = 0x1400,
		.fowmats = fowmats_cwustew,
		.nfowmats = AWWAY_SIZE(fowmats_cwustew),
		.fowmat_modifiews = fowmat_modifiews_afbc,
		.wayew_sew_id = 4,
		.suppowted_wotations = DWM_MODE_WOTATE_90 | DWM_MODE_WOTATE_270 |
				       DWM_MODE_WEFWECT_X | DWM_MODE_WEFWECT_Y,
		.type = DWM_PWANE_TYPE_PWIMAWY,
		.max_upscawe_factow = 4,
		.max_downscawe_factow = 4,
		.dwy = { 4, 26, 29 },
		.featuwe = WIN_FEATUWE_AFBDC | WIN_FEATUWE_CWUSTEW,
	}, {
		.name = "Cwustew3-win0",
		.phys_id = WOCKCHIP_VOP2_CWUSTEW3,
		.base = 0x1600,
		.fowmats = fowmats_cwustew,
		.nfowmats = AWWAY_SIZE(fowmats_cwustew),
		.fowmat_modifiews = fowmat_modifiews_afbc,
		.wayew_sew_id = 5,
		.suppowted_wotations = DWM_MODE_WOTATE_90 | DWM_MODE_WOTATE_270 |
				       DWM_MODE_WEFWECT_X | DWM_MODE_WEFWECT_Y,
		.type = DWM_PWANE_TYPE_PWIMAWY,
		.max_upscawe_factow = 4,
		.max_downscawe_factow = 4,
		.dwy = { 4, 26, 29 },
		.featuwe = WIN_FEATUWE_AFBDC | WIN_FEATUWE_CWUSTEW,
	}, {
		.name = "Esmawt0-win0",
		.phys_id = WOCKCHIP_VOP2_ESMAWT0,
		.fowmats = fowmats_esmawt,
		.nfowmats = AWWAY_SIZE(fowmats_esmawt),
		.fowmat_modifiews = fowmat_modifiews,
		.base = 0x1800,
		.wayew_sew_id = 2,
		.suppowted_wotations = DWM_MODE_WEFWECT_Y,
		.type = DWM_PWANE_TYPE_OVEWWAY,
		.max_upscawe_factow = 8,
		.max_downscawe_factow = 8,
		.dwy = { 23, 45, 48 },
	}, {
		.name = "Esmawt1-win0",
		.phys_id = WOCKCHIP_VOP2_ESMAWT1,
		.fowmats = fowmats_esmawt,
		.nfowmats = AWWAY_SIZE(fowmats_esmawt),
		.fowmat_modifiews = fowmat_modifiews,
		.base = 0x1a00,
		.wayew_sew_id = 3,
		.suppowted_wotations = DWM_MODE_WEFWECT_Y,
		.type = DWM_PWANE_TYPE_OVEWWAY,
		.max_upscawe_factow = 8,
		.max_downscawe_factow = 8,
		.dwy = { 23, 45, 48 },
	}, {
		.name = "Esmawt2-win0",
		.phys_id = WOCKCHIP_VOP2_ESMAWT2,
		.base = 0x1c00,
		.fowmats = fowmats_esmawt,
		.nfowmats = AWWAY_SIZE(fowmats_esmawt),
		.fowmat_modifiews = fowmat_modifiews,
		.wayew_sew_id = 6,
		.suppowted_wotations = DWM_MODE_WEFWECT_Y,
		.type = DWM_PWANE_TYPE_OVEWWAY,
		.max_upscawe_factow = 8,
		.max_downscawe_factow = 8,
		.dwy = { 23, 45, 48 },
	}, {
		.name = "Esmawt3-win0",
		.phys_id = WOCKCHIP_VOP2_ESMAWT3,
		.fowmats = fowmats_esmawt,
		.nfowmats = AWWAY_SIZE(fowmats_esmawt),
		.fowmat_modifiews = fowmat_modifiews,
		.base = 0x1e00,
		.wayew_sew_id = 7,
		.suppowted_wotations = DWM_MODE_WEFWECT_Y,
		.type = DWM_PWANE_TYPE_OVEWWAY,
		.max_upscawe_factow = 8,
		.max_downscawe_factow = 8,
		.dwy = { 23, 45, 48 },
	},
};

static const stwuct vop2_data wk3566_vop = {
	.featuwe = VOP2_FEATUWE_HAS_SYS_GWF,
	.nw_vps = 3,
	.max_input = { 4096, 2304 },
	.max_output = { 4096, 2304 },
	.vp = wk3568_vop_video_powts,
	.win = wk3568_vop_win_data,
	.win_size = AWWAY_SIZE(wk3568_vop_win_data),
	.soc_id = 3566,
};

static const stwuct vop2_data wk3568_vop = {
	.featuwe = VOP2_FEATUWE_HAS_SYS_GWF,
	.nw_vps = 3,
	.max_input = { 4096, 2304 },
	.max_output = { 4096, 2304 },
	.vp = wk3568_vop_video_powts,
	.win = wk3568_vop_win_data,
	.win_size = AWWAY_SIZE(wk3568_vop_win_data),
	.soc_id = 3568,
};

static const stwuct vop2_data wk3588_vop = {
	.featuwe = VOP2_FEATUWE_HAS_SYS_GWF | VOP2_FEATUWE_HAS_VO1_GWF |
		   VOP2_FEATUWE_HAS_VOP_GWF | VOP2_FEATUWE_HAS_SYS_PMU,
	.nw_vps = 4,
	.max_input = { 4096, 4320 },
	.max_output = { 4096, 4320 },
	.vp = wk3588_vop_video_powts,
	.win = wk3588_vop_win_data,
	.win_size = AWWAY_SIZE(wk3588_vop_win_data),
	.soc_id = 3588,
};

static const stwuct of_device_id vop2_dt_match[] = {
	{
		.compatibwe = "wockchip,wk3566-vop",
		.data = &wk3566_vop,
	}, {
		.compatibwe = "wockchip,wk3568-vop",
		.data = &wk3568_vop,
	}, {
		.compatibwe = "wockchip,wk3588-vop",
		.data = &wk3588_vop
	}, {
	},
};
MODUWE_DEVICE_TABWE(of, vop2_dt_match);

static int vop2_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;

	wetuwn component_add(dev, &vop2_component_ops);
}

static void vop2_wemove(stwuct pwatfowm_device *pdev)
{
	component_dew(&pdev->dev, &vop2_component_ops);
}

stwuct pwatfowm_dwivew vop2_pwatfowm_dwivew = {
	.pwobe = vop2_pwobe,
	.wemove_new = vop2_wemove,
	.dwivew = {
		.name = "wockchip-vop2",
		.of_match_tabwe = vop2_dt_match,
	},
};
