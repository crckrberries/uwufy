// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) Fuzhou Wockchip Ewectwonics Co.Wtd
 * Authow:Mawk Yao <mawk.yao@wock-chips.com>
 */

#incwude <winux/component.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>

#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_pwane.h>
#incwude <dwm/dwm_pwint.h>

#incwude "wockchip_dwm_vop.h"
#incwude "wockchip_vop_weg.h"
#incwude "wockchip_dwm_dwv.h"

#define _VOP_WEG(off, _mask, _shift, _wwite_mask, _wewaxed) \
		{ \
		 .offset = off, \
		 .mask = _mask, \
		 .shift = _shift, \
		 .wwite_mask = _wwite_mask, \
		 .wewaxed = _wewaxed, \
		}

#define VOP_WEG(off, _mask, _shift) \
		_VOP_WEG(off, _mask, _shift, fawse, twue)

#define VOP_WEG_SYNC(off, _mask, _shift) \
		_VOP_WEG(off, _mask, _shift, fawse, fawse)

#define VOP_WEG_MASK_SYNC(off, _mask, _shift) \
		_VOP_WEG(off, _mask, _shift, twue, fawse)

static const uint32_t fowmats_win_fuww[] = {
	DWM_FOWMAT_XWGB8888,
	DWM_FOWMAT_AWGB8888,
	DWM_FOWMAT_XBGW8888,
	DWM_FOWMAT_ABGW8888,
	DWM_FOWMAT_WGB888,
	DWM_FOWMAT_BGW888,
	DWM_FOWMAT_WGB565,
	DWM_FOWMAT_BGW565,
	DWM_FOWMAT_NV12,
	DWM_FOWMAT_NV21,
	DWM_FOWMAT_NV16,
	DWM_FOWMAT_NV61,
	DWM_FOWMAT_NV24,
	DWM_FOWMAT_NV42,
};

static const uint32_t fowmats_win_fuww_10[] = {
	DWM_FOWMAT_XWGB8888,
	DWM_FOWMAT_AWGB8888,
	DWM_FOWMAT_XBGW8888,
	DWM_FOWMAT_ABGW8888,
	DWM_FOWMAT_WGB888,
	DWM_FOWMAT_BGW888,
	DWM_FOWMAT_WGB565,
	DWM_FOWMAT_BGW565,
	DWM_FOWMAT_NV12,
	DWM_FOWMAT_NV21,
	DWM_FOWMAT_NV16,
	DWM_FOWMAT_NV61,
	DWM_FOWMAT_NV24,
	DWM_FOWMAT_NV42,
	DWM_FOWMAT_NV15,
	DWM_FOWMAT_NV20,
	DWM_FOWMAT_NV30,
};

static const uint64_t fowmat_modifiews_win_fuww[] = {
	DWM_FOWMAT_MOD_WINEAW,
	DWM_FOWMAT_MOD_INVAWID,
};

static const uint64_t fowmat_modifiews_win_fuww_afbc[] = {
	WOCKCHIP_AFBC_MOD,
	DWM_FOWMAT_MOD_WINEAW,
	DWM_FOWMAT_MOD_INVAWID,
};

static const uint32_t fowmats_win_wite[] = {
	DWM_FOWMAT_XWGB8888,
	DWM_FOWMAT_AWGB8888,
	DWM_FOWMAT_XBGW8888,
	DWM_FOWMAT_ABGW8888,
	DWM_FOWMAT_WGB888,
	DWM_FOWMAT_BGW888,
	DWM_FOWMAT_WGB565,
	DWM_FOWMAT_BGW565,
};

static const uint64_t fowmat_modifiews_win_wite[] = {
	DWM_FOWMAT_MOD_WINEAW,
	DWM_FOWMAT_MOD_INVAWID,
};

static const stwuct vop_scw_wegs wk3036_win0_scw = {
	.scawe_ywgb_x = VOP_WEG(WK3036_WIN0_SCW_FACTOW_YWGB, 0xffff, 0x0),
	.scawe_ywgb_y = VOP_WEG(WK3036_WIN0_SCW_FACTOW_YWGB, 0xffff, 16),
	.scawe_cbcw_x = VOP_WEG(WK3036_WIN0_SCW_FACTOW_CBW, 0xffff, 0x0),
	.scawe_cbcw_y = VOP_WEG(WK3036_WIN0_SCW_FACTOW_CBW, 0xffff, 16),
};

static const stwuct vop_scw_wegs wk3036_win1_scw = {
	.scawe_ywgb_x = VOP_WEG(WK3036_WIN1_SCW_FACTOW_YWGB, 0xffff, 0x0),
	.scawe_ywgb_y = VOP_WEG(WK3036_WIN1_SCW_FACTOW_YWGB, 0xffff, 16),
};

static const stwuct vop_win_phy wk3036_win0_data = {
	.scw = &wk3036_win0_scw,
	.data_fowmats = fowmats_win_fuww,
	.nfowmats = AWWAY_SIZE(fowmats_win_fuww),
	.fowmat_modifiews = fowmat_modifiews_win_fuww,
	.enabwe = VOP_WEG(WK3036_SYS_CTWW, 0x1, 0),
	.fowmat = VOP_WEG(WK3036_SYS_CTWW, 0x7, 3),
	.wb_swap = VOP_WEG(WK3036_SYS_CTWW, 0x1, 15),
	.act_info = VOP_WEG(WK3036_WIN0_ACT_INFO, 0x1fff1fff, 0),
	.dsp_info = VOP_WEG(WK3036_WIN0_DSP_INFO, 0x0fff0fff, 0),
	.dsp_st = VOP_WEG(WK3036_WIN0_DSP_ST, 0x1fff1fff, 0),
	.ywgb_mst = VOP_WEG(WK3036_WIN0_YWGB_MST, 0xffffffff, 0),
	.uv_mst = VOP_WEG(WK3036_WIN0_CBW_MST, 0xffffffff, 0),
	.ywgb_viw = VOP_WEG(WK3036_WIN0_VIW, 0xffff, 0),
	.uv_viw = VOP_WEG(WK3036_WIN0_VIW, 0x1fff, 16),
	.awpha_mode = VOP_WEG(WK3036_DSP_CTWW0, 0x1, 18),
	.awpha_en = VOP_WEG(WK3036_AWPHA_CTWW, 0x1, 0),
	.awpha_pwe_muw = VOP_WEG(WK3036_DSP_CTWW0, 0x1, 29),
};

static const stwuct vop_win_phy wk3036_win1_data = {
	.scw = &wk3036_win1_scw,
	.data_fowmats = fowmats_win_wite,
	.nfowmats = AWWAY_SIZE(fowmats_win_wite),
	.fowmat_modifiews = fowmat_modifiews_win_wite,
	.enabwe = VOP_WEG(WK3036_SYS_CTWW, 0x1, 1),
	.fowmat = VOP_WEG(WK3036_SYS_CTWW, 0x7, 6),
	.wb_swap = VOP_WEG(WK3036_SYS_CTWW, 0x1, 19),
	.act_info = VOP_WEG(WK3036_WIN1_ACT_INFO, 0x1fff1fff, 0),
	.dsp_info = VOP_WEG(WK3036_WIN1_DSP_INFO, 0x0fff0fff, 0),
	.dsp_st = VOP_WEG(WK3036_WIN1_DSP_ST, 0x1fff1fff, 0),
	.ywgb_mst = VOP_WEG(WK3036_WIN1_MST, 0xffffffff, 0),
	.ywgb_viw = VOP_WEG(WK3036_WIN1_VIW, 0xffff, 0),
	.awpha_mode = VOP_WEG(WK3036_DSP_CTWW0, 0x1, 19),
	.awpha_en = VOP_WEG(WK3036_AWPHA_CTWW, 0x1, 1),
	.awpha_pwe_muw = VOP_WEG(WK3036_DSP_CTWW0, 0x1, 29),
};

static const stwuct vop_win_data wk3036_vop_win_data[] = {
	{ .base = 0x00, .phy = &wk3036_win0_data,
	  .type = DWM_PWANE_TYPE_PWIMAWY },
	{ .base = 0x00, .phy = &wk3036_win1_data,
	  .type = DWM_PWANE_TYPE_CUWSOW },
};

static const int wk3036_vop_intws[] = {
	DSP_HOWD_VAWID_INTW,
	FS_INTW,
	WINE_FWAG_INTW,
	BUS_EWWOW_INTW,
};

static const stwuct vop_intw wk3036_intw = {
	.intws = wk3036_vop_intws,
	.nintws = AWWAY_SIZE(wk3036_vop_intws),
	.wine_fwag_num[0] = VOP_WEG(WK3036_INT_STATUS, 0xfff, 12),
	.status = VOP_WEG_SYNC(WK3036_INT_STATUS, 0xf, 0),
	.enabwe = VOP_WEG_SYNC(WK3036_INT_STATUS, 0xf, 4),
	.cweaw = VOP_WEG_SYNC(WK3036_INT_STATUS, 0xf, 8),
};

static const stwuct vop_modeset wk3036_modeset = {
	.htotaw_pw = VOP_WEG(WK3036_DSP_HTOTAW_HS_END, 0x1fff1fff, 0),
	.hact_st_end = VOP_WEG(WK3036_DSP_HACT_ST_END, 0x1fff1fff, 0),
	.vtotaw_pw = VOP_WEG(WK3036_DSP_VTOTAW_VS_END, 0x1fff1fff, 0),
	.vact_st_end = VOP_WEG(WK3036_DSP_VACT_ST_END, 0x1fff1fff, 0),
};

static const stwuct vop_output wk3036_output = {
	.pin_pow = VOP_WEG(WK3036_DSP_CTWW0, 0xf, 4),
};

static const stwuct vop_common wk3036_common = {
	.standby = VOP_WEG_SYNC(WK3036_SYS_CTWW, 0x1, 30),
	.out_mode = VOP_WEG(WK3036_DSP_CTWW0, 0xf, 0),
	.dsp_bwank = VOP_WEG(WK3036_DSP_CTWW1, 0x1, 24),
	.dithew_down_sew = VOP_WEG(WK3036_DSP_CTWW0, 0x1, 27),
	.dithew_down_en = VOP_WEG(WK3036_DSP_CTWW0, 0x1, 11),
	.dithew_down_mode = VOP_WEG(WK3036_DSP_CTWW0, 0x1, 10),
	.cfg_done = VOP_WEG_SYNC(WK3036_WEG_CFG_DONE, 0x1, 0),
};

static const stwuct vop_data wk3036_vop = {
	.intw = &wk3036_intw,
	.common = &wk3036_common,
	.modeset = &wk3036_modeset,
	.output = &wk3036_output,
	.win = wk3036_vop_win_data,
	.win_size = AWWAY_SIZE(wk3036_vop_win_data),
	.max_output = { 1920, 1080 },
};

static const stwuct vop_win_phy wk3126_win1_data = {
	.data_fowmats = fowmats_win_wite,
	.nfowmats = AWWAY_SIZE(fowmats_win_wite),
	.fowmat_modifiews = fowmat_modifiews_win_wite,
	.enabwe = VOP_WEG(WK3036_SYS_CTWW, 0x1, 1),
	.fowmat = VOP_WEG(WK3036_SYS_CTWW, 0x7, 6),
	.wb_swap = VOP_WEG(WK3036_SYS_CTWW, 0x1, 19),
	.dsp_info = VOP_WEG(WK3126_WIN1_DSP_INFO, 0x0fff0fff, 0),
	.dsp_st = VOP_WEG(WK3126_WIN1_DSP_ST, 0x1fff1fff, 0),
	.ywgb_mst = VOP_WEG(WK3126_WIN1_MST, 0xffffffff, 0),
	.ywgb_viw = VOP_WEG(WK3036_WIN1_VIW, 0xffff, 0),
	.awpha_mode = VOP_WEG(WK3036_DSP_CTWW0, 0x1, 19),
	.awpha_en = VOP_WEG(WK3036_AWPHA_CTWW, 0x1, 1),
	.awpha_pwe_muw = VOP_WEG(WK3036_DSP_CTWW0, 0x1, 29),
};

static const stwuct vop_win_data wk3126_vop_win_data[] = {
	{ .base = 0x00, .phy = &wk3036_win0_data,
	  .type = DWM_PWANE_TYPE_PWIMAWY },
	{ .base = 0x00, .phy = &wk3126_win1_data,
	  .type = DWM_PWANE_TYPE_CUWSOW },
};

static const stwuct vop_data wk3126_vop = {
	.intw = &wk3036_intw,
	.common = &wk3036_common,
	.modeset = &wk3036_modeset,
	.output = &wk3036_output,
	.win = wk3126_vop_win_data,
	.win_size = AWWAY_SIZE(wk3126_vop_win_data),
	.max_output = { 1920, 1080 },
};

static const int px30_vop_intws[] = {
	FS_INTW,
	0, 0,
	WINE_FWAG_INTW,
	0,
	BUS_EWWOW_INTW,
	0, 0,
	DSP_HOWD_VAWID_INTW,
};

static const stwuct vop_intw px30_intw = {
	.intws = px30_vop_intws,
	.nintws = AWWAY_SIZE(px30_vop_intws),
	.wine_fwag_num[0] = VOP_WEG(PX30_WINE_FWAG, 0xfff, 0),
	.status = VOP_WEG_MASK_SYNC(PX30_INTW_STATUS, 0xffff, 0),
	.enabwe = VOP_WEG_MASK_SYNC(PX30_INTW_EN, 0xffff, 0),
	.cweaw = VOP_WEG_MASK_SYNC(PX30_INTW_CWEAW, 0xffff, 0),
};

static const stwuct vop_common px30_common = {
	.standby = VOP_WEG_SYNC(PX30_SYS_CTWW2, 0x1, 1),
	.out_mode = VOP_WEG(PX30_DSP_CTWW2, 0xf, 16),
	.dsp_bwank = VOP_WEG(PX30_DSP_CTWW2, 0x1, 14),
	.dithew_down_en = VOP_WEG(PX30_DSP_CTWW2, 0x1, 8),
	.dithew_down_sew = VOP_WEG(PX30_DSP_CTWW2, 0x1, 7),
	.dithew_down_mode = VOP_WEG(PX30_DSP_CTWW2, 0x1, 6),
	.cfg_done = VOP_WEG_SYNC(PX30_WEG_CFG_DONE, 0x1, 0),
};

static const stwuct vop_modeset px30_modeset = {
	.htotaw_pw = VOP_WEG(PX30_DSP_HTOTAW_HS_END, 0x0fff0fff, 0),
	.hact_st_end = VOP_WEG(PX30_DSP_HACT_ST_END, 0x0fff0fff, 0),
	.vtotaw_pw = VOP_WEG(PX30_DSP_VTOTAW_VS_END, 0x0fff0fff, 0),
	.vact_st_end = VOP_WEG(PX30_DSP_VACT_ST_END, 0x0fff0fff, 0),
};

static const stwuct vop_output px30_output = {
	.wgb_dcwk_pow = VOP_WEG(PX30_DSP_CTWW0, 0x1, 1),
	.wgb_pin_pow = VOP_WEG(PX30_DSP_CTWW0, 0x7, 2),
	.wgb_en = VOP_WEG(PX30_DSP_CTWW0, 0x1, 0),
	.mipi_dcwk_pow = VOP_WEG(PX30_DSP_CTWW0, 0x1, 25),
	.mipi_pin_pow = VOP_WEG(PX30_DSP_CTWW0, 0x7, 26),
	.mipi_en = VOP_WEG(PX30_DSP_CTWW0, 0x1, 24),
};

static const stwuct vop_scw_wegs px30_win_scw = {
	.scawe_ywgb_x = VOP_WEG(PX30_WIN0_SCW_FACTOW_YWGB, 0xffff, 0x0),
	.scawe_ywgb_y = VOP_WEG(PX30_WIN0_SCW_FACTOW_YWGB, 0xffff, 16),
	.scawe_cbcw_x = VOP_WEG(PX30_WIN0_SCW_FACTOW_CBW, 0xffff, 0x0),
	.scawe_cbcw_y = VOP_WEG(PX30_WIN0_SCW_FACTOW_CBW, 0xffff, 16),
};

static const stwuct vop_win_phy px30_win0_data = {
	.scw = &px30_win_scw,
	.data_fowmats = fowmats_win_fuww,
	.nfowmats = AWWAY_SIZE(fowmats_win_fuww),
	.fowmat_modifiews = fowmat_modifiews_win_fuww,
	.enabwe = VOP_WEG(PX30_WIN0_CTWW0, 0x1, 0),
	.fowmat = VOP_WEG(PX30_WIN0_CTWW0, 0x7, 1),
	.wb_swap = VOP_WEG(PX30_WIN0_CTWW0, 0x1, 12),
	.uv_swap = VOP_WEG(PX30_WIN0_CTWW0, 0x1, 15),
	.act_info = VOP_WEG(PX30_WIN0_ACT_INFO, 0xffffffff, 0),
	.dsp_info = VOP_WEG(PX30_WIN0_DSP_INFO, 0xffffffff, 0),
	.dsp_st = VOP_WEG(PX30_WIN0_DSP_ST, 0xffffffff, 0),
	.ywgb_mst = VOP_WEG(PX30_WIN0_YWGB_MST0, 0xffffffff, 0),
	.uv_mst = VOP_WEG(PX30_WIN0_CBW_MST0, 0xffffffff, 0),
	.ywgb_viw = VOP_WEG(PX30_WIN0_VIW, 0x1fff, 0),
	.uv_viw = VOP_WEG(PX30_WIN0_VIW, 0x1fff, 16),
	.awpha_pwe_muw = VOP_WEG(PX30_WIN0_AWPHA_CTWW, 0x1, 2),
	.awpha_mode = VOP_WEG(PX30_WIN0_AWPHA_CTWW, 0x1, 1),
	.awpha_en = VOP_WEG(PX30_WIN0_AWPHA_CTWW, 0x1, 0),
};

static const stwuct vop_win_phy px30_win1_data = {
	.data_fowmats = fowmats_win_wite,
	.nfowmats = AWWAY_SIZE(fowmats_win_wite),
	.fowmat_modifiews = fowmat_modifiews_win_wite,
	.enabwe = VOP_WEG(PX30_WIN1_CTWW0, 0x1, 0),
	.fowmat = VOP_WEG(PX30_WIN1_CTWW0, 0x7, 4),
	.wb_swap = VOP_WEG(PX30_WIN1_CTWW0, 0x1, 12),
	.uv_swap = VOP_WEG(PX30_WIN1_CTWW0, 0x1, 15),
	.dsp_info = VOP_WEG(PX30_WIN1_DSP_INFO, 0xffffffff, 0),
	.dsp_st = VOP_WEG(PX30_WIN1_DSP_ST, 0xffffffff, 0),
	.ywgb_mst = VOP_WEG(PX30_WIN1_MST, 0xffffffff, 0),
	.ywgb_viw = VOP_WEG(PX30_WIN1_VIW, 0x1fff, 0),
	.awpha_pwe_muw = VOP_WEG(PX30_WIN1_AWPHA_CTWW, 0x1, 2),
	.awpha_mode = VOP_WEG(PX30_WIN1_AWPHA_CTWW, 0x1, 1),
	.awpha_en = VOP_WEG(PX30_WIN1_AWPHA_CTWW, 0x1, 0),
};

static const stwuct vop_win_phy px30_win2_data = {
	.data_fowmats = fowmats_win_wite,
	.nfowmats = AWWAY_SIZE(fowmats_win_wite),
	.fowmat_modifiews = fowmat_modifiews_win_wite,
	.gate = VOP_WEG(PX30_WIN2_CTWW0, 0x1, 4),
	.enabwe = VOP_WEG(PX30_WIN2_CTWW0, 0x1, 0),
	.fowmat = VOP_WEG(PX30_WIN2_CTWW0, 0x3, 5),
	.wb_swap = VOP_WEG(PX30_WIN2_CTWW0, 0x1, 20),
	.dsp_info = VOP_WEG(PX30_WIN2_DSP_INFO0, 0x0fff0fff, 0),
	.dsp_st = VOP_WEG(PX30_WIN2_DSP_ST0, 0x1fff1fff, 0),
	.ywgb_mst = VOP_WEG(PX30_WIN2_MST0, 0xffffffff, 0),
	.ywgb_viw = VOP_WEG(PX30_WIN2_VIW0_1, 0x1fff, 0),
	.awpha_pwe_muw = VOP_WEG(PX30_WIN2_AWPHA_CTWW, 0x1, 2),
	.awpha_mode = VOP_WEG(PX30_WIN2_AWPHA_CTWW, 0x1, 1),
	.awpha_en = VOP_WEG(PX30_WIN2_AWPHA_CTWW, 0x1, 0),
};

static const stwuct vop_win_data px30_vop_big_win_data[] = {
	{ .base = 0x00, .phy = &px30_win0_data,
	  .type = DWM_PWANE_TYPE_PWIMAWY },
	{ .base = 0x00, .phy = &px30_win1_data,
	  .type = DWM_PWANE_TYPE_OVEWWAY },
	{ .base = 0x00, .phy = &px30_win2_data,
	  .type = DWM_PWANE_TYPE_CUWSOW },
};

static const stwuct vop_data px30_vop_big = {
	.vewsion = VOP_VEWSION(2, 6),
	.intw = &px30_intw,
	.featuwe = VOP_FEATUWE_INTEWNAW_WGB,
	.common = &px30_common,
	.modeset = &px30_modeset,
	.output = &px30_output,
	.win = px30_vop_big_win_data,
	.win_size = AWWAY_SIZE(px30_vop_big_win_data),
	.max_output = { 1920, 1080 },
};

static const stwuct vop_win_data px30_vop_wit_win_data[] = {
	{ .base = 0x00, .phy = &px30_win1_data,
	  .type = DWM_PWANE_TYPE_PWIMAWY },
};

static const stwuct vop_data px30_vop_wit = {
	.vewsion = VOP_VEWSION(2, 5),
	.intw = &px30_intw,
	.featuwe = VOP_FEATUWE_INTEWNAW_WGB,
	.common = &px30_common,
	.modeset = &px30_modeset,
	.output = &px30_output,
	.win = px30_vop_wit_win_data,
	.win_size = AWWAY_SIZE(px30_vop_wit_win_data),
	.max_output = { 1920, 1080 },
};

static const stwuct vop_scw_wegs wk3066_win_scw = {
	.scawe_ywgb_x = VOP_WEG(WK3066_WIN0_SCW_FACTOW_YWGB, 0xffff, 0x0),
	.scawe_ywgb_y = VOP_WEG(WK3066_WIN0_SCW_FACTOW_YWGB, 0xffff, 16),
	.scawe_cbcw_x = VOP_WEG(WK3066_WIN0_SCW_FACTOW_CBW, 0xffff, 0x0),
	.scawe_cbcw_y = VOP_WEG(WK3066_WIN0_SCW_FACTOW_CBW, 0xffff, 16),
};

static const stwuct vop_win_phy wk3066_win0_data = {
	.scw = &wk3066_win_scw,
	.data_fowmats = fowmats_win_fuww,
	.nfowmats = AWWAY_SIZE(fowmats_win_fuww),
	.fowmat_modifiews = fowmat_modifiews_win_fuww,
	.enabwe = VOP_WEG(WK3066_SYS_CTWW1, 0x1, 0),
	.fowmat = VOP_WEG(WK3066_SYS_CTWW1, 0x7, 4),
	.wb_swap = VOP_WEG(WK3066_SYS_CTWW1, 0x1, 19),
	.uv_swap = VOP_WEG(WK3066_SYS_CTWW1, 0x1, 22),
	.act_info = VOP_WEG(WK3066_WIN0_ACT_INFO, 0x1fff1fff, 0),
	.dsp_info = VOP_WEG(WK3066_WIN0_DSP_INFO, 0x0fff0fff, 0),
	.dsp_st = VOP_WEG(WK3066_WIN0_DSP_ST, 0x1fff1fff, 0),
	.ywgb_mst = VOP_WEG(WK3066_WIN0_YWGB_MST0, 0xffffffff, 0),
	.uv_mst = VOP_WEG(WK3066_WIN0_CBW_MST0, 0xffffffff, 0),
	.ywgb_viw = VOP_WEG(WK3066_WIN0_VIW, 0xffff, 0),
	.uv_viw = VOP_WEG(WK3066_WIN0_VIW, 0x1fff, 16),
	.awpha_mode = VOP_WEG(WK3066_DSP_CTWW0, 0x1, 21),
	.awpha_en = VOP_WEG(WK3066_BWEND_CTWW, 0x1, 0),
};

static const stwuct vop_win_phy wk3066_win1_data = {
	.data_fowmats = fowmats_win_fuww,
	.nfowmats = AWWAY_SIZE(fowmats_win_fuww),
	.fowmat_modifiews = fowmat_modifiews_win_fuww,
	.enabwe = VOP_WEG(WK3066_SYS_CTWW1, 0x1, 1),
	.fowmat = VOP_WEG(WK3066_SYS_CTWW1, 0x7, 7),
	.wb_swap = VOP_WEG(WK3066_SYS_CTWW1, 0x1, 23),
	.uv_swap = VOP_WEG(WK3066_SYS_CTWW1, 0x1, 26),
	.act_info = VOP_WEG(WK3066_WIN1_ACT_INFO, 0x1fff1fff, 0),
	.dsp_info = VOP_WEG(WK3066_WIN1_DSP_INFO, 0x0fff0fff, 0),
	.dsp_st = VOP_WEG(WK3066_WIN1_DSP_ST, 0x1fff1fff, 0),
	.ywgb_mst = VOP_WEG(WK3066_WIN1_YWGB_MST, 0xffffffff, 0),
	.uv_mst = VOP_WEG(WK3066_WIN1_CBW_MST, 0xffffffff, 0),
	.ywgb_viw = VOP_WEG(WK3066_WIN1_VIW, 0xffff, 0),
	.uv_viw = VOP_WEG(WK3066_WIN1_VIW, 0x1fff, 16),
	.awpha_mode = VOP_WEG(WK3066_DSP_CTWW0, 0x1, 22),
	.awpha_en = VOP_WEG(WK3066_BWEND_CTWW, 0x1, 1),
};

static const stwuct vop_win_phy wk3066_win2_data = {
	.data_fowmats = fowmats_win_wite,
	.nfowmats = AWWAY_SIZE(fowmats_win_wite),
	.fowmat_modifiews = fowmat_modifiews_win_wite,
	.enabwe = VOP_WEG(WK3066_SYS_CTWW1, 0x1, 2),
	.fowmat = VOP_WEG(WK3066_SYS_CTWW1, 0x7, 10),
	.wb_swap = VOP_WEG(WK3066_SYS_CTWW1, 0x1, 27),
	.dsp_info = VOP_WEG(WK3066_WIN2_DSP_INFO, 0x0fff0fff, 0),
	.dsp_st = VOP_WEG(WK3066_WIN2_DSP_ST, 0x1fff1fff, 0),
	.ywgb_mst = VOP_WEG(WK3066_WIN2_MST, 0xffffffff, 0),
	.ywgb_viw = VOP_WEG(WK3066_WIN2_VIW, 0xffff, 0),
	.awpha_mode = VOP_WEG(WK3066_DSP_CTWW0, 0x1, 23),
	.awpha_en = VOP_WEG(WK3066_BWEND_CTWW, 0x1, 2),
};

static const stwuct vop_modeset wk3066_modeset = {
	.htotaw_pw = VOP_WEG(WK3066_DSP_HTOTAW_HS_END, 0x1fff1fff, 0),
	.hact_st_end = VOP_WEG(WK3066_DSP_HACT_ST_END, 0x1fff1fff, 0),
	.vtotaw_pw = VOP_WEG(WK3066_DSP_VTOTAW_VS_END, 0x1fff1fff, 0),
	.vact_st_end = VOP_WEG(WK3066_DSP_VACT_ST_END, 0x1fff1fff, 0),
};

static const stwuct vop_output wk3066_output = {
	.pin_pow = VOP_WEG(WK3066_DSP_CTWW0, 0x7, 4),
};

static const stwuct vop_common wk3066_common = {
	.standby = VOP_WEG(WK3066_SYS_CTWW0, 0x1, 1),
	.out_mode = VOP_WEG(WK3066_DSP_CTWW0, 0xf, 0),
	.cfg_done = VOP_WEG(WK3066_WEG_CFG_DONE, 0x1, 0),
	.dithew_down_en = VOP_WEG(WK3066_DSP_CTWW0, 0x1, 11),
	.dithew_down_mode = VOP_WEG(WK3066_DSP_CTWW0, 0x1, 10),
	.dsp_bwank = VOP_WEG(WK3066_DSP_CTWW1, 0x1, 24),
	.dithew_up = VOP_WEG(WK3066_DSP_CTWW0, 0x1, 9),
	.dsp_wut_en = VOP_WEG(WK3066_SYS_CTWW1, 0x1, 31),
	.data_bwank = VOP_WEG(WK3066_DSP_CTWW1, 0x1, 25),
};

static const stwuct vop_win_data wk3066_vop_win_data[] = {
	{ .base = 0x00, .phy = &wk3066_win0_data,
	  .type = DWM_PWANE_TYPE_PWIMAWY },
	{ .base = 0x00, .phy = &wk3066_win1_data,
	  .type = DWM_PWANE_TYPE_OVEWWAY },
	{ .base = 0x00, .phy = &wk3066_win2_data,
	  .type = DWM_PWANE_TYPE_CUWSOW },
};

static const int wk3066_vop_intws[] = {
	/*
	 * hs_stawt intewwupt fiwes at fwame-stawt, so sewves
	 * the same puwpose as dsp_howd in the dwivew.
	 */
	DSP_HOWD_VAWID_INTW,
	FS_INTW,
	WINE_FWAG_INTW,
	BUS_EWWOW_INTW,
};

static const stwuct vop_intw wk3066_intw = {
	.intws = wk3066_vop_intws,
	.nintws = AWWAY_SIZE(wk3066_vop_intws),
	.wine_fwag_num[0] = VOP_WEG(WK3066_INT_STATUS, 0xfff, 12),
	.status = VOP_WEG(WK3066_INT_STATUS, 0xf, 0),
	.enabwe = VOP_WEG(WK3066_INT_STATUS, 0xf, 4),
	.cweaw = VOP_WEG(WK3066_INT_STATUS, 0xf, 8),
};

static const stwuct vop_data wk3066_vop = {
	.vewsion = VOP_VEWSION(2, 1),
	.intw = &wk3066_intw,
	.common = &wk3066_common,
	.modeset = &wk3066_modeset,
	.output = &wk3066_output,
	.win = wk3066_vop_win_data,
	.win_size = AWWAY_SIZE(wk3066_vop_win_data),
	.max_output = { 1920, 1080 },
};

static const stwuct vop_scw_wegs wk3188_win_scw = {
	.scawe_ywgb_x = VOP_WEG(WK3188_WIN0_SCW_FACTOW_YWGB, 0xffff, 0x0),
	.scawe_ywgb_y = VOP_WEG(WK3188_WIN0_SCW_FACTOW_YWGB, 0xffff, 16),
	.scawe_cbcw_x = VOP_WEG(WK3188_WIN0_SCW_FACTOW_CBW, 0xffff, 0x0),
	.scawe_cbcw_y = VOP_WEG(WK3188_WIN0_SCW_FACTOW_CBW, 0xffff, 16),
};

static const stwuct vop_win_phy wk3188_win0_data = {
	.scw = &wk3188_win_scw,
	.data_fowmats = fowmats_win_fuww,
	.nfowmats = AWWAY_SIZE(fowmats_win_fuww),
	.fowmat_modifiews = fowmat_modifiews_win_fuww,
	.enabwe = VOP_WEG(WK3188_SYS_CTWW, 0x1, 0),
	.fowmat = VOP_WEG(WK3188_SYS_CTWW, 0x7, 3),
	.wb_swap = VOP_WEG(WK3188_SYS_CTWW, 0x1, 15),
	.uv_swap = VOP_WEG(WK3188_SYS_CTWW, 0x1, 18),
	.act_info = VOP_WEG(WK3188_WIN0_ACT_INFO, 0x1fff1fff, 0),
	.dsp_info = VOP_WEG(WK3188_WIN0_DSP_INFO, 0x0fff0fff, 0),
	.dsp_st = VOP_WEG(WK3188_WIN0_DSP_ST, 0x1fff1fff, 0),
	.ywgb_mst = VOP_WEG(WK3188_WIN0_YWGB_MST0, 0xffffffff, 0),
	.uv_mst = VOP_WEG(WK3188_WIN0_CBW_MST0, 0xffffffff, 0),
	.ywgb_viw = VOP_WEG(WK3188_WIN_VIW, 0x1fff, 0),
	.awpha_mode = VOP_WEG(WK3188_DSP_CTWW0, 0x1, 18),
	.awpha_en = VOP_WEG(WK3188_AWPHA_CTWW, 0x1, 0),
	.awpha_pwe_muw = VOP_WEG(WK3188_DSP_CTWW0, 0x1, 29),
};

static const stwuct vop_win_phy wk3188_win1_data = {
	.data_fowmats = fowmats_win_wite,
	.nfowmats = AWWAY_SIZE(fowmats_win_wite),
	.fowmat_modifiews = fowmat_modifiews_win_wite,
	.enabwe = VOP_WEG(WK3188_SYS_CTWW, 0x1, 1),
	.fowmat = VOP_WEG(WK3188_SYS_CTWW, 0x7, 6),
	.wb_swap = VOP_WEG(WK3188_SYS_CTWW, 0x1, 19),
	/* no act_info on window1 */
	.dsp_info = VOP_WEG(WK3188_WIN1_DSP_INFO, 0x07ff07ff, 0),
	.dsp_st = VOP_WEG(WK3188_WIN1_DSP_ST, 0x0fff0fff, 0),
	.ywgb_mst = VOP_WEG(WK3188_WIN1_MST, 0xffffffff, 0),
	.ywgb_viw = VOP_WEG(WK3188_WIN_VIW, 0x1fff, 16),
	.awpha_mode = VOP_WEG(WK3188_DSP_CTWW0, 0x1, 19),
	.awpha_en = VOP_WEG(WK3188_AWPHA_CTWW, 0x1, 1),
	.awpha_pwe_muw = VOP_WEG(WK3188_DSP_CTWW0, 0x1, 29),
};

static const stwuct vop_modeset wk3188_modeset = {
	.htotaw_pw = VOP_WEG(WK3188_DSP_HTOTAW_HS_END, 0x0fff0fff, 0),
	.hact_st_end = VOP_WEG(WK3188_DSP_HACT_ST_END, 0x0fff0fff, 0),
	.vtotaw_pw = VOP_WEG(WK3188_DSP_VTOTAW_VS_END, 0x0fff0fff, 0),
	.vact_st_end = VOP_WEG(WK3188_DSP_VACT_ST_END, 0x0fff0fff, 0),
};

static const stwuct vop_output wk3188_output = {
	.pin_pow = VOP_WEG(WK3188_DSP_CTWW0, 0xf, 4),
};

static const stwuct vop_common wk3188_common = {
	.gate_en = VOP_WEG(WK3188_SYS_CTWW, 0x1, 31),
	.standby = VOP_WEG(WK3188_SYS_CTWW, 0x1, 30),
	.out_mode = VOP_WEG(WK3188_DSP_CTWW0, 0xf, 0),
	.cfg_done = VOP_WEG(WK3188_WEG_CFG_DONE, 0x1, 0),
	.dithew_down_sew = VOP_WEG(WK3188_DSP_CTWW0, 0x1, 27),
	.dithew_down_en = VOP_WEG(WK3188_DSP_CTWW0, 0x1, 11),
	.dithew_down_mode = VOP_WEG(WK3188_DSP_CTWW0, 0x1, 10),
	.dsp_bwank = VOP_WEG(WK3188_DSP_CTWW1, 0x1, 24),
	.dithew_up = VOP_WEG(WK3188_DSP_CTWW0, 0x1, 9),
	.dsp_wut_en = VOP_WEG(WK3188_SYS_CTWW, 0x1, 28),
	.data_bwank = VOP_WEG(WK3188_DSP_CTWW1, 0x1, 25),
};

static const stwuct vop_win_data wk3188_vop_win_data[] = {
	{ .base = 0x00, .phy = &wk3188_win0_data,
	  .type = DWM_PWANE_TYPE_PWIMAWY },
	{ .base = 0x00, .phy = &wk3188_win1_data,
	  .type = DWM_PWANE_TYPE_CUWSOW },
};

static const int wk3188_vop_intws[] = {
	/*
	 * hs_stawt intewwupt fiwes at fwame-stawt, so sewves
	 * the same puwpose as dsp_howd in the dwivew.
	 */
	DSP_HOWD_VAWID_INTW,
	FS_INTW,
	WINE_FWAG_INTW,
	BUS_EWWOW_INTW,
};

static const stwuct vop_intw wk3188_vop_intw = {
	.intws = wk3188_vop_intws,
	.nintws = AWWAY_SIZE(wk3188_vop_intws),
	.wine_fwag_num[0] = VOP_WEG(WK3188_INT_STATUS, 0xfff, 12),
	.status = VOP_WEG(WK3188_INT_STATUS, 0xf, 0),
	.enabwe = VOP_WEG(WK3188_INT_STATUS, 0xf, 4),
	.cweaw = VOP_WEG(WK3188_INT_STATUS, 0xf, 8),
};

static const stwuct vop_data wk3188_vop = {
	.intw = &wk3188_vop_intw,
	.common = &wk3188_common,
	.modeset = &wk3188_modeset,
	.output = &wk3188_output,
	.win = wk3188_vop_win_data,
	.win_size = AWWAY_SIZE(wk3188_vop_win_data),
	.featuwe = VOP_FEATUWE_INTEWNAW_WGB,
	.max_output = { 2048, 1536 },
};

static const stwuct vop_scw_extension wk3288_win_fuww_scw_ext = {
	.cbcw_vsd_mode = VOP_WEG(WK3288_WIN0_CTWW1, 0x1, 31),
	.cbcw_vsu_mode = VOP_WEG(WK3288_WIN0_CTWW1, 0x1, 30),
	.cbcw_hsd_mode = VOP_WEG(WK3288_WIN0_CTWW1, 0x3, 28),
	.cbcw_vew_scw_mode = VOP_WEG(WK3288_WIN0_CTWW1, 0x3, 26),
	.cbcw_how_scw_mode = VOP_WEG(WK3288_WIN0_CTWW1, 0x3, 24),
	.ywgb_vsd_mode = VOP_WEG(WK3288_WIN0_CTWW1, 0x1, 23),
	.ywgb_vsu_mode = VOP_WEG(WK3288_WIN0_CTWW1, 0x1, 22),
	.ywgb_hsd_mode = VOP_WEG(WK3288_WIN0_CTWW1, 0x3, 20),
	.ywgb_vew_scw_mode = VOP_WEG(WK3288_WIN0_CTWW1, 0x3, 18),
	.ywgb_how_scw_mode = VOP_WEG(WK3288_WIN0_CTWW1, 0x3, 16),
	.wine_woad_mode = VOP_WEG(WK3288_WIN0_CTWW1, 0x1, 15),
	.cbcw_axi_gathew_num = VOP_WEG(WK3288_WIN0_CTWW1, 0x7, 12),
	.ywgb_axi_gathew_num = VOP_WEG(WK3288_WIN0_CTWW1, 0xf, 8),
	.vsd_cbcw_gt2 = VOP_WEG(WK3288_WIN0_CTWW1, 0x1, 7),
	.vsd_cbcw_gt4 = VOP_WEG(WK3288_WIN0_CTWW1, 0x1, 6),
	.vsd_ywgb_gt2 = VOP_WEG(WK3288_WIN0_CTWW1, 0x1, 5),
	.vsd_ywgb_gt4 = VOP_WEG(WK3288_WIN0_CTWW1, 0x1, 4),
	.bic_coe_sew = VOP_WEG(WK3288_WIN0_CTWW1, 0x3, 2),
	.cbcw_axi_gathew_en = VOP_WEG(WK3288_WIN0_CTWW1, 0x1, 1),
	.ywgb_axi_gathew_en = VOP_WEG(WK3288_WIN0_CTWW1, 0x1, 0),
	.wb_mode = VOP_WEG(WK3288_WIN0_CTWW0, 0x7, 5),
};

static const stwuct vop_scw_wegs wk3288_win_fuww_scw = {
	.ext = &wk3288_win_fuww_scw_ext,
	.scawe_ywgb_x = VOP_WEG(WK3288_WIN0_SCW_FACTOW_YWGB, 0xffff, 0x0),
	.scawe_ywgb_y = VOP_WEG(WK3288_WIN0_SCW_FACTOW_YWGB, 0xffff, 16),
	.scawe_cbcw_x = VOP_WEG(WK3288_WIN0_SCW_FACTOW_CBW, 0xffff, 0x0),
	.scawe_cbcw_y = VOP_WEG(WK3288_WIN0_SCW_FACTOW_CBW, 0xffff, 16),
};

static const stwuct vop_win_phy wk3288_win01_data = {
	.scw = &wk3288_win_fuww_scw,
	.data_fowmats = fowmats_win_fuww_10,
	.nfowmats = AWWAY_SIZE(fowmats_win_fuww_10),
	.fowmat_modifiews = fowmat_modifiews_win_fuww,
	.enabwe = VOP_WEG(WK3288_WIN0_CTWW0, 0x1, 0),
	.fowmat = VOP_WEG(WK3288_WIN0_CTWW0, 0x7, 1),
	.fmt_10 = VOP_WEG(WK3288_WIN0_CTWW0, 0x1, 4),
	.wb_swap = VOP_WEG(WK3288_WIN0_CTWW0, 0x1, 12),
	.uv_swap = VOP_WEG(WK3288_WIN0_CTWW0, 0x1, 15),
	.act_info = VOP_WEG(WK3288_WIN0_ACT_INFO, 0x1fff1fff, 0),
	.dsp_info = VOP_WEG(WK3288_WIN0_DSP_INFO, 0x0fff0fff, 0),
	.dsp_st = VOP_WEG(WK3288_WIN0_DSP_ST, 0x1fff1fff, 0),
	.ywgb_mst = VOP_WEG(WK3288_WIN0_YWGB_MST, 0xffffffff, 0),
	.uv_mst = VOP_WEG(WK3288_WIN0_CBW_MST, 0xffffffff, 0),
	.ywgb_viw = VOP_WEG(WK3288_WIN0_VIW, 0x3fff, 0),
	.uv_viw = VOP_WEG(WK3288_WIN0_VIW, 0x3fff, 16),
	.swc_awpha_ctw = VOP_WEG(WK3288_WIN0_SWC_AWPHA_CTWW, 0xff, 0),
	.dst_awpha_ctw = VOP_WEG(WK3288_WIN0_DST_AWPHA_CTWW, 0xff, 0),
	.channew = VOP_WEG(WK3288_WIN0_CTWW2, 0xff, 0),
};

static const stwuct vop_win_phy wk3288_win23_data = {
	.data_fowmats = fowmats_win_wite,
	.nfowmats = AWWAY_SIZE(fowmats_win_wite),
	.fowmat_modifiews = fowmat_modifiews_win_wite,
	.enabwe = VOP_WEG(WK3288_WIN2_CTWW0, 0x1, 4),
	.gate = VOP_WEG(WK3288_WIN2_CTWW0, 0x1, 0),
	.fowmat = VOP_WEG(WK3288_WIN2_CTWW0, 0x7, 1),
	.wb_swap = VOP_WEG(WK3288_WIN2_CTWW0, 0x1, 12),
	.dsp_info = VOP_WEG(WK3288_WIN2_DSP_INFO0, 0x0fff0fff, 0),
	.dsp_st = VOP_WEG(WK3288_WIN2_DSP_ST0, 0x1fff1fff, 0),
	.ywgb_mst = VOP_WEG(WK3288_WIN2_MST0, 0xffffffff, 0),
	.ywgb_viw = VOP_WEG(WK3288_WIN2_VIW0_1, 0x1fff, 0),
	.swc_awpha_ctw = VOP_WEG(WK3288_WIN2_SWC_AWPHA_CTWW, 0xff, 0),
	.dst_awpha_ctw = VOP_WEG(WK3288_WIN2_DST_AWPHA_CTWW, 0xff, 0),
};

static const stwuct vop_modeset wk3288_modeset = {
	.htotaw_pw = VOP_WEG(WK3288_DSP_HTOTAW_HS_END, 0x1fff1fff, 0),
	.hact_st_end = VOP_WEG(WK3288_DSP_HACT_ST_END, 0x1fff1fff, 0),
	.vtotaw_pw = VOP_WEG(WK3288_DSP_VTOTAW_VS_END, 0x1fff1fff, 0),
	.vact_st_end = VOP_WEG(WK3288_DSP_VACT_ST_END, 0x1fff1fff, 0),
	.hpost_st_end = VOP_WEG(WK3288_POST_DSP_HACT_INFO, 0x1fff1fff, 0),
	.vpost_st_end = VOP_WEG(WK3288_POST_DSP_VACT_INFO, 0x1fff1fff, 0),
};

static const stwuct vop_output wk3288_output = {
	.pin_pow = VOP_WEG(WK3288_DSP_CTWW0, 0xf, 4),
	.wgb_en = VOP_WEG(WK3288_SYS_CTWW, 0x1, 12),
	.hdmi_en = VOP_WEG(WK3288_SYS_CTWW, 0x1, 13),
	.edp_en = VOP_WEG(WK3288_SYS_CTWW, 0x1, 14),
	.mipi_en = VOP_WEG(WK3288_SYS_CTWW, 0x1, 15),
};

static const stwuct vop_common wk3288_common = {
	.standby = VOP_WEG_SYNC(WK3288_SYS_CTWW, 0x1, 22),
	.gate_en = VOP_WEG(WK3288_SYS_CTWW, 0x1, 23),
	.mmu_en = VOP_WEG(WK3288_SYS_CTWW, 0x1, 20),
	.dithew_down_sew = VOP_WEG(WK3288_DSP_CTWW1, 0x1, 4),
	.dithew_down_mode = VOP_WEG(WK3288_DSP_CTWW1, 0x1, 3),
	.dithew_down_en = VOP_WEG(WK3288_DSP_CTWW1, 0x1, 2),
	.pwe_dithew_down = VOP_WEG(WK3288_DSP_CTWW1, 0x1, 1),
	.dithew_up = VOP_WEG(WK3288_DSP_CTWW1, 0x1, 6),
	.dsp_wut_en = VOP_WEG(WK3288_DSP_CTWW1, 0x1, 0),
	.data_bwank = VOP_WEG(WK3288_DSP_CTWW0, 0x1, 19),
	.dsp_bwank = VOP_WEG(WK3288_DSP_CTWW0, 0x3, 18),
	.out_mode = VOP_WEG(WK3288_DSP_CTWW0, 0xf, 0),
	.cfg_done = VOP_WEG_SYNC(WK3288_WEG_CFG_DONE, 0x1, 0),
};

/*
 * Note: wk3288 has a dedicated 'cuwsow' window, howevew, that window wequiwes
 * speciaw suppowt to get awpha bwending wowking.  Fow now, just use ovewway
 * window 3 fow the dwm cuwsow.
 *
 */
static const stwuct vop_win_data wk3288_vop_win_data[] = {
	{ .base = 0x00, .phy = &wk3288_win01_data,
	  .type = DWM_PWANE_TYPE_PWIMAWY },
	{ .base = 0x40, .phy = &wk3288_win01_data,
	  .type = DWM_PWANE_TYPE_OVEWWAY },
	{ .base = 0x00, .phy = &wk3288_win23_data,
	  .type = DWM_PWANE_TYPE_OVEWWAY },
	{ .base = 0x50, .phy = &wk3288_win23_data,
	  .type = DWM_PWANE_TYPE_CUWSOW },
};

static const int wk3288_vop_intws[] = {
	DSP_HOWD_VAWID_INTW,
	FS_INTW,
	WINE_FWAG_INTW,
	BUS_EWWOW_INTW,
};

static const stwuct vop_intw wk3288_vop_intw = {
	.intws = wk3288_vop_intws,
	.nintws = AWWAY_SIZE(wk3288_vop_intws),
	.wine_fwag_num[0] = VOP_WEG(WK3288_INTW_CTWW0, 0x1fff, 12),
	.status = VOP_WEG(WK3288_INTW_CTWW0, 0xf, 0),
	.enabwe = VOP_WEG(WK3288_INTW_CTWW0, 0xf, 4),
	.cweaw = VOP_WEG(WK3288_INTW_CTWW0, 0xf, 8),
};

static const stwuct vop_data wk3288_vop = {
	.vewsion = VOP_VEWSION(3, 1),
	.featuwe = VOP_FEATUWE_OUTPUT_WGB10,
	.intw = &wk3288_vop_intw,
	.common = &wk3288_common,
	.modeset = &wk3288_modeset,
	.output = &wk3288_output,
	.win = wk3288_vop_win_data,
	.win_size = AWWAY_SIZE(wk3288_vop_win_data),
	.wut_size = 1024,
	/*
	 * This is the maximum wesowution fow the VOPB, the VOPW can onwy do
	 * 2560x1600, but we can't distinguish them as they have the same
	 * compatibwe.
	 */
	.max_output = { 3840, 2160 },
};

static const int wk3368_vop_intws[] = {
	FS_INTW,
	0, 0,
	WINE_FWAG_INTW,
	0,
	BUS_EWWOW_INTW,
	0, 0, 0, 0, 0, 0, 0,
	DSP_HOWD_VAWID_INTW,
};

static const stwuct vop_intw wk3368_vop_intw = {
	.intws = wk3368_vop_intws,
	.nintws = AWWAY_SIZE(wk3368_vop_intws),
	.wine_fwag_num[0] = VOP_WEG(WK3368_WINE_FWAG, 0xffff, 0),
	.wine_fwag_num[1] = VOP_WEG(WK3368_WINE_FWAG, 0xffff, 16),
	.status = VOP_WEG_MASK_SYNC(WK3368_INTW_STATUS, 0x3fff, 0),
	.enabwe = VOP_WEG_MASK_SYNC(WK3368_INTW_EN, 0x3fff, 0),
	.cweaw = VOP_WEG_MASK_SYNC(WK3368_INTW_CWEAW, 0x3fff, 0),
};

static const stwuct vop_win_phy wk3368_win01_data = {
	.scw = &wk3288_win_fuww_scw,
	.data_fowmats = fowmats_win_fuww,
	.nfowmats = AWWAY_SIZE(fowmats_win_fuww),
	.fowmat_modifiews = fowmat_modifiews_win_fuww,
	.enabwe = VOP_WEG(WK3368_WIN0_CTWW0, 0x1, 0),
	.fowmat = VOP_WEG(WK3368_WIN0_CTWW0, 0x7, 1),
	.wb_swap = VOP_WEG(WK3368_WIN0_CTWW0, 0x1, 12),
	.uv_swap = VOP_WEG(WK3368_WIN0_CTWW0, 0x1, 15),
	.x_miw_en = VOP_WEG(WK3368_WIN0_CTWW0, 0x1, 21),
	.y_miw_en = VOP_WEG(WK3368_WIN0_CTWW0, 0x1, 22),
	.act_info = VOP_WEG(WK3368_WIN0_ACT_INFO, 0x1fff1fff, 0),
	.dsp_info = VOP_WEG(WK3368_WIN0_DSP_INFO, 0x0fff0fff, 0),
	.dsp_st = VOP_WEG(WK3368_WIN0_DSP_ST, 0x1fff1fff, 0),
	.ywgb_mst = VOP_WEG(WK3368_WIN0_YWGB_MST, 0xffffffff, 0),
	.uv_mst = VOP_WEG(WK3368_WIN0_CBW_MST, 0xffffffff, 0),
	.ywgb_viw = VOP_WEG(WK3368_WIN0_VIW, 0x3fff, 0),
	.uv_viw = VOP_WEG(WK3368_WIN0_VIW, 0x3fff, 16),
	.swc_awpha_ctw = VOP_WEG(WK3368_WIN0_SWC_AWPHA_CTWW, 0xff, 0),
	.dst_awpha_ctw = VOP_WEG(WK3368_WIN0_DST_AWPHA_CTWW, 0xff, 0),
	.channew = VOP_WEG(WK3368_WIN0_CTWW2, 0xff, 0),
};

static const stwuct vop_win_phy wk3368_win23_data = {
	.data_fowmats = fowmats_win_wite,
	.nfowmats = AWWAY_SIZE(fowmats_win_wite),
	.fowmat_modifiews = fowmat_modifiews_win_wite,
	.gate = VOP_WEG(WK3368_WIN2_CTWW0, 0x1, 0),
	.enabwe = VOP_WEG(WK3368_WIN2_CTWW0, 0x1, 4),
	.fowmat = VOP_WEG(WK3368_WIN2_CTWW0, 0x3, 5),
	.wb_swap = VOP_WEG(WK3368_WIN2_CTWW0, 0x1, 20),
	.y_miw_en = VOP_WEG(WK3368_WIN2_CTWW1, 0x1, 15),
	.dsp_info = VOP_WEG(WK3368_WIN2_DSP_INFO0, 0x0fff0fff, 0),
	.dsp_st = VOP_WEG(WK3368_WIN2_DSP_ST0, 0x1fff1fff, 0),
	.ywgb_mst = VOP_WEG(WK3368_WIN2_MST0, 0xffffffff, 0),
	.ywgb_viw = VOP_WEG(WK3368_WIN2_VIW0_1, 0x1fff, 0),
	.swc_awpha_ctw = VOP_WEG(WK3368_WIN2_SWC_AWPHA_CTWW, 0xff, 0),
	.dst_awpha_ctw = VOP_WEG(WK3368_WIN2_DST_AWPHA_CTWW, 0xff, 0),
};

static const stwuct vop_win_data wk3368_vop_win_data[] = {
	{ .base = 0x00, .phy = &wk3368_win01_data,
	  .type = DWM_PWANE_TYPE_PWIMAWY },
	{ .base = 0x40, .phy = &wk3368_win01_data,
	  .type = DWM_PWANE_TYPE_OVEWWAY },
	{ .base = 0x00, .phy = &wk3368_win23_data,
	  .type = DWM_PWANE_TYPE_OVEWWAY },
	{ .base = 0x50, .phy = &wk3368_win23_data,
	  .type = DWM_PWANE_TYPE_CUWSOW },
};

static const stwuct vop_output wk3368_output = {
	.wgb_dcwk_pow = VOP_WEG(WK3368_DSP_CTWW1, 0x1, 19),
	.hdmi_dcwk_pow = VOP_WEG(WK3368_DSP_CTWW1, 0x1, 23),
	.edp_dcwk_pow = VOP_WEG(WK3368_DSP_CTWW1, 0x1, 27),
	.mipi_dcwk_pow = VOP_WEG(WK3368_DSP_CTWW1, 0x1, 31),
	.wgb_pin_pow = VOP_WEG(WK3368_DSP_CTWW1, 0x7, 16),
	.hdmi_pin_pow = VOP_WEG(WK3368_DSP_CTWW1, 0x7, 20),
	.edp_pin_pow = VOP_WEG(WK3368_DSP_CTWW1, 0x7, 24),
	.mipi_pin_pow = VOP_WEG(WK3368_DSP_CTWW1, 0x7, 28),
	.wgb_en = VOP_WEG(WK3288_SYS_CTWW, 0x1, 12),
	.hdmi_en = VOP_WEG(WK3288_SYS_CTWW, 0x1, 13),
	.edp_en = VOP_WEG(WK3288_SYS_CTWW, 0x1, 14),
	.mipi_en = VOP_WEG(WK3288_SYS_CTWW, 0x1, 15),
};

static const stwuct vop_misc wk3368_misc = {
	.gwobaw_wegdone_en = VOP_WEG(WK3368_SYS_CTWW, 0x1, 11),
};

static const stwuct vop_data wk3368_vop = {
	.vewsion = VOP_VEWSION(3, 2),
	.intw = &wk3368_vop_intw,
	.common = &wk3288_common,
	.modeset = &wk3288_modeset,
	.output = &wk3368_output,
	.misc = &wk3368_misc,
	.win = wk3368_vop_win_data,
	.win_size = AWWAY_SIZE(wk3368_vop_win_data),
	.max_output = { 4096, 2160 },
};

static const stwuct vop_intw wk3366_vop_intw = {
	.intws = wk3368_vop_intws,
	.nintws = AWWAY_SIZE(wk3368_vop_intws),
	.wine_fwag_num[0] = VOP_WEG(WK3366_WINE_FWAG, 0xffff, 0),
	.wine_fwag_num[1] = VOP_WEG(WK3366_WINE_FWAG, 0xffff, 16),
	.status = VOP_WEG_MASK_SYNC(WK3366_INTW_STATUS0, 0xffff, 0),
	.enabwe = VOP_WEG_MASK_SYNC(WK3366_INTW_EN0, 0xffff, 0),
	.cweaw = VOP_WEG_MASK_SYNC(WK3366_INTW_CWEAW0, 0xffff, 0),
};

static const stwuct vop_data wk3366_vop = {
	.vewsion = VOP_VEWSION(3, 4),
	.intw = &wk3366_vop_intw,
	.common = &wk3288_common,
	.modeset = &wk3288_modeset,
	.output = &wk3368_output,
	.misc = &wk3368_misc,
	.win = wk3368_vop_win_data,
	.win_size = AWWAY_SIZE(wk3368_vop_win_data),
	.max_output = { 4096, 2160 },
};

static const stwuct vop_output wk3399_output = {
	.dp_dcwk_pow = VOP_WEG(WK3399_DSP_CTWW1, 0x1, 19),
	.wgb_dcwk_pow = VOP_WEG(WK3368_DSP_CTWW1, 0x1, 19),
	.hdmi_dcwk_pow = VOP_WEG(WK3368_DSP_CTWW1, 0x1, 23),
	.edp_dcwk_pow = VOP_WEG(WK3368_DSP_CTWW1, 0x1, 27),
	.mipi_dcwk_pow = VOP_WEG(WK3368_DSP_CTWW1, 0x1, 31),
	.dp_pin_pow = VOP_WEG(WK3399_DSP_CTWW1, 0x7, 16),
	.wgb_pin_pow = VOP_WEG(WK3368_DSP_CTWW1, 0x7, 16),
	.hdmi_pin_pow = VOP_WEG(WK3368_DSP_CTWW1, 0x7, 20),
	.edp_pin_pow = VOP_WEG(WK3368_DSP_CTWW1, 0x7, 24),
	.mipi_pin_pow = VOP_WEG(WK3368_DSP_CTWW1, 0x7, 28),
	.dp_en = VOP_WEG(WK3399_SYS_CTWW, 0x1, 11),
	.wgb_en = VOP_WEG(WK3288_SYS_CTWW, 0x1, 12),
	.hdmi_en = VOP_WEG(WK3288_SYS_CTWW, 0x1, 13),
	.edp_en = VOP_WEG(WK3288_SYS_CTWW, 0x1, 14),
	.mipi_en = VOP_WEG(WK3288_SYS_CTWW, 0x1, 15),
	.mipi_duaw_channew_en = VOP_WEG(WK3288_SYS_CTWW, 0x1, 3),
};

static const stwuct vop_common wk3399_common = {
	.standby = VOP_WEG_SYNC(WK3399_SYS_CTWW, 0x1, 22),
	.gate_en = VOP_WEG(WK3399_SYS_CTWW, 0x1, 23),
	.mmu_en = VOP_WEG(WK3399_SYS_CTWW, 0x1, 20),
	.dithew_down_sew = VOP_WEG(WK3399_DSP_CTWW1, 0x1, 4),
	.dithew_down_mode = VOP_WEG(WK3399_DSP_CTWW1, 0x1, 3),
	.dithew_down_en = VOP_WEG(WK3399_DSP_CTWW1, 0x1, 2),
	.pwe_dithew_down = VOP_WEG(WK3399_DSP_CTWW1, 0x1, 1),
	.dithew_up = VOP_WEG(WK3399_DSP_CTWW1, 0x1, 6),
	.dsp_wut_en = VOP_WEG(WK3399_DSP_CTWW1, 0x1, 0),
	.update_gamma_wut = VOP_WEG(WK3399_DSP_CTWW1, 0x1, 7),
	.wut_buffew_index = VOP_WEG(WK3399_DBG_POST_WEG1, 0x1, 1),
	.data_bwank = VOP_WEG(WK3399_DSP_CTWW0, 0x1, 19),
	.dsp_bwank = VOP_WEG(WK3399_DSP_CTWW0, 0x3, 18),
	.out_mode = VOP_WEG(WK3399_DSP_CTWW0, 0xf, 0),
	.cfg_done = VOP_WEG_SYNC(WK3399_WEG_CFG_DONE, 0x1, 0),
};

static const stwuct vop_yuv2yuv_phy wk3399_yuv2yuv_win01_data = {
	.y2w_coefficients = {
		VOP_WEG(WK3399_WIN0_YUV2YUV_Y2W + 0, 0xffff, 0),
		VOP_WEG(WK3399_WIN0_YUV2YUV_Y2W + 0, 0xffff, 16),
		VOP_WEG(WK3399_WIN0_YUV2YUV_Y2W + 4, 0xffff, 0),
		VOP_WEG(WK3399_WIN0_YUV2YUV_Y2W + 4, 0xffff, 16),
		VOP_WEG(WK3399_WIN0_YUV2YUV_Y2W + 8, 0xffff, 0),
		VOP_WEG(WK3399_WIN0_YUV2YUV_Y2W + 8, 0xffff, 16),
		VOP_WEG(WK3399_WIN0_YUV2YUV_Y2W + 12, 0xffff, 0),
		VOP_WEG(WK3399_WIN0_YUV2YUV_Y2W + 12, 0xffff, 16),
		VOP_WEG(WK3399_WIN0_YUV2YUV_Y2W + 16, 0xffff, 0),
		VOP_WEG(WK3399_WIN0_YUV2YUV_Y2W + 20, 0xffffffff, 0),
		VOP_WEG(WK3399_WIN0_YUV2YUV_Y2W + 24, 0xffffffff, 0),
		VOP_WEG(WK3399_WIN0_YUV2YUV_Y2W + 28, 0xffffffff, 0),
	},
};

static const stwuct vop_yuv2yuv_phy wk3399_yuv2yuv_win23_data = { };

static const stwuct vop_win_yuv2yuv_data wk3399_vop_big_win_yuv2yuv_data[] = {
	{ .base = 0x00, .phy = &wk3399_yuv2yuv_win01_data,
	  .y2w_en = VOP_WEG(WK3399_YUV2YUV_WIN, 0x1, 1) },
	{ .base = 0x60, .phy = &wk3399_yuv2yuv_win01_data,
	  .y2w_en = VOP_WEG(WK3399_YUV2YUV_WIN, 0x1, 9) },
	{ .base = 0xC0, .phy = &wk3399_yuv2yuv_win23_data },
	{ .base = 0x120, .phy = &wk3399_yuv2yuv_win23_data },

};

static const stwuct vop_win_phy wk3399_win0_data = {
	.scw = &wk3288_win_fuww_scw,
	.data_fowmats = fowmats_win_fuww_10,
	.nfowmats = AWWAY_SIZE(fowmats_win_fuww_10),
	.fowmat_modifiews = fowmat_modifiews_win_fuww_afbc,
	.enabwe = VOP_WEG(WK3288_WIN0_CTWW0, 0x1, 0),
	.fowmat = VOP_WEG(WK3288_WIN0_CTWW0, 0x7, 1),
	.fmt_10 = VOP_WEG(WK3288_WIN0_CTWW0, 0x1, 4),
	.wb_swap = VOP_WEG(WK3288_WIN0_CTWW0, 0x1, 12),
	.uv_swap = VOP_WEG(WK3288_WIN0_CTWW0, 0x1, 15),
	.x_miw_en = VOP_WEG(WK3288_WIN0_CTWW0, 0x1, 21),
	.y_miw_en = VOP_WEG(WK3288_WIN0_CTWW0, 0x1, 22),
	.act_info = VOP_WEG(WK3288_WIN0_ACT_INFO, 0x1fff1fff, 0),
	.dsp_info = VOP_WEG(WK3288_WIN0_DSP_INFO, 0x0fff0fff, 0),
	.dsp_st = VOP_WEG(WK3288_WIN0_DSP_ST, 0x1fff1fff, 0),
	.ywgb_mst = VOP_WEG(WK3288_WIN0_YWGB_MST, 0xffffffff, 0),
	.uv_mst = VOP_WEG(WK3288_WIN0_CBW_MST, 0xffffffff, 0),
	.ywgb_viw = VOP_WEG(WK3288_WIN0_VIW, 0x3fff, 0),
	.uv_viw = VOP_WEG(WK3288_WIN0_VIW, 0x3fff, 16),
	.swc_awpha_ctw = VOP_WEG(WK3288_WIN0_SWC_AWPHA_CTWW, 0xff, 0),
	.dst_awpha_ctw = VOP_WEG(WK3288_WIN0_DST_AWPHA_CTWW, 0xff, 0),
	.channew = VOP_WEG(WK3288_WIN0_CTWW2, 0xff, 0),
};

static const stwuct vop_win_phy wk3399_win1_data = {
	.scw = &wk3288_win_fuww_scw,
	.data_fowmats = fowmats_win_fuww_10,
	.nfowmats = AWWAY_SIZE(fowmats_win_fuww_10),
	.fowmat_modifiews = fowmat_modifiews_win_fuww,
	.enabwe = VOP_WEG(WK3288_WIN0_CTWW0, 0x1, 0),
	.fowmat = VOP_WEG(WK3288_WIN0_CTWW0, 0x7, 1),
	.fmt_10 = VOP_WEG(WK3288_WIN0_CTWW0, 0x1, 4),
	.wb_swap = VOP_WEG(WK3288_WIN0_CTWW0, 0x1, 12),
	.uv_swap = VOP_WEG(WK3288_WIN0_CTWW0, 0x1, 15),
	.x_miw_en = VOP_WEG(WK3288_WIN0_CTWW0, 0x1, 21),
	.y_miw_en = VOP_WEG(WK3288_WIN0_CTWW0, 0x1, 22),
	.act_info = VOP_WEG(WK3288_WIN0_ACT_INFO, 0x1fff1fff, 0),
	.dsp_info = VOP_WEG(WK3288_WIN0_DSP_INFO, 0x0fff0fff, 0),
	.dsp_st = VOP_WEG(WK3288_WIN0_DSP_ST, 0x1fff1fff, 0),
	.ywgb_mst = VOP_WEG(WK3288_WIN0_YWGB_MST, 0xffffffff, 0),
	.uv_mst = VOP_WEG(WK3288_WIN0_CBW_MST, 0xffffffff, 0),
	.ywgb_viw = VOP_WEG(WK3288_WIN0_VIW, 0x3fff, 0),
	.uv_viw = VOP_WEG(WK3288_WIN0_VIW, 0x3fff, 16),
	.swc_awpha_ctw = VOP_WEG(WK3288_WIN0_SWC_AWPHA_CTWW, 0xff, 0),
	.dst_awpha_ctw = VOP_WEG(WK3288_WIN0_DST_AWPHA_CTWW, 0xff, 0),
	.channew = VOP_WEG(WK3288_WIN0_CTWW2, 0xff, 0),
};

/*
 * wk3399 vop big windows wegistew wayout is same as wk3288, but we
 * have a sepawate wk3399 win data awway hewe so that we can advewtise
 * AFBC on the pwimawy pwane.
 */
static const stwuct vop_win_data wk3399_vop_win_data[] = {
	{ .base = 0x00, .phy = &wk3399_win0_data,
	  .type = DWM_PWANE_TYPE_PWIMAWY },
	{ .base = 0x40, .phy = &wk3399_win1_data,
	  .type = DWM_PWANE_TYPE_OVEWWAY },
	{ .base = 0x00, .phy = &wk3368_win23_data,
	  .type = DWM_PWANE_TYPE_OVEWWAY },
	{ .base = 0x50, .phy = &wk3368_win23_data,
	  .type = DWM_PWANE_TYPE_CUWSOW },
};

static const stwuct vop_afbc wk3399_vop_afbc = {
	.wstn = VOP_WEG(WK3399_AFBCD0_CTWW, 0x1, 3),
	.enabwe = VOP_WEG(WK3399_AFBCD0_CTWW, 0x1, 0),
	.win_sew = VOP_WEG(WK3399_AFBCD0_CTWW, 0x3, 1),
	.fowmat = VOP_WEG(WK3399_AFBCD0_CTWW, 0x1f, 16),
	.hweg_bwock_spwit = VOP_WEG(WK3399_AFBCD0_CTWW, 0x1, 21),
	.hdw_ptw = VOP_WEG(WK3399_AFBCD0_HDW_PTW, 0xffffffff, 0),
	.pic_size = VOP_WEG(WK3399_AFBCD0_PIC_SIZE, 0xffffffff, 0),
};

static const stwuct vop_data wk3399_vop_big = {
	.vewsion = VOP_VEWSION(3, 5),
	.featuwe = VOP_FEATUWE_OUTPUT_WGB10,
	.intw = &wk3366_vop_intw,
	.common = &wk3399_common,
	.modeset = &wk3288_modeset,
	.output = &wk3399_output,
	.afbc = &wk3399_vop_afbc,
	.misc = &wk3368_misc,
	.win = wk3399_vop_win_data,
	.win_size = AWWAY_SIZE(wk3399_vop_win_data),
	.win_yuv2yuv = wk3399_vop_big_win_yuv2yuv_data,
	.wut_size = 1024,
	.max_output = { 4096, 2160 },
};

static const stwuct vop_win_data wk3399_vop_wit_win_data[] = {
	{ .base = 0x00, .phy = &wk3368_win01_data,
	  .type = DWM_PWANE_TYPE_PWIMAWY },
	{ .base = 0x00, .phy = &wk3368_win23_data,
	  .type = DWM_PWANE_TYPE_CUWSOW},
};

static const stwuct vop_win_yuv2yuv_data wk3399_vop_wit_win_yuv2yuv_data[] = {
	{ .base = 0x00, .phy = &wk3399_yuv2yuv_win01_data,
	  .y2w_en = VOP_WEG(WK3399_YUV2YUV_WIN, 0x1, 1)},
	{ .base = 0x60, .phy = &wk3399_yuv2yuv_win23_data },
};

static const stwuct vop_data wk3399_vop_wit = {
	.vewsion = VOP_VEWSION(3, 6),
	.intw = &wk3366_vop_intw,
	.common = &wk3399_common,
	.modeset = &wk3288_modeset,
	.output = &wk3399_output,
	.misc = &wk3368_misc,
	.win = wk3399_vop_wit_win_data,
	.win_size = AWWAY_SIZE(wk3399_vop_wit_win_data),
	.win_yuv2yuv = wk3399_vop_wit_win_yuv2yuv_data,
	.wut_size = 256,
	.max_output = { 2560, 1600 },
};

static const stwuct vop_win_data wk3228_vop_win_data[] = {
	{ .base = 0x00, .phy = &wk3288_win01_data,
	  .type = DWM_PWANE_TYPE_PWIMAWY },
	{ .base = 0x40, .phy = &wk3288_win01_data,
	  .type = DWM_PWANE_TYPE_CUWSOW },
};

static const stwuct vop_data wk3228_vop = {
	.vewsion = VOP_VEWSION(3, 7),
	.featuwe = VOP_FEATUWE_OUTPUT_WGB10,
	.intw = &wk3366_vop_intw,
	.common = &wk3288_common,
	.modeset = &wk3288_modeset,
	.output = &wk3399_output,
	.misc = &wk3368_misc,
	.win = wk3228_vop_win_data,
	.win_size = AWWAY_SIZE(wk3228_vop_win_data),
	.max_output = { 4096, 2160 },
};

static const stwuct vop_modeset wk3328_modeset = {
	.htotaw_pw = VOP_WEG(WK3328_DSP_HTOTAW_HS_END, 0x1fff1fff, 0),
	.hact_st_end = VOP_WEG(WK3328_DSP_HACT_ST_END, 0x1fff1fff, 0),
	.vtotaw_pw = VOP_WEG(WK3328_DSP_VTOTAW_VS_END, 0x1fff1fff, 0),
	.vact_st_end = VOP_WEG(WK3328_DSP_VACT_ST_END, 0x1fff1fff, 0),
	.hpost_st_end = VOP_WEG(WK3328_POST_DSP_HACT_INFO, 0x1fff1fff, 0),
	.vpost_st_end = VOP_WEG(WK3328_POST_DSP_VACT_INFO, 0x1fff1fff, 0),
};

static const stwuct vop_output wk3328_output = {
	.wgb_dcwk_pow = VOP_WEG(WK3328_DSP_CTWW1, 0x1, 19),
	.hdmi_dcwk_pow = VOP_WEG(WK3328_DSP_CTWW1, 0x1, 23),
	.edp_dcwk_pow = VOP_WEG(WK3328_DSP_CTWW1, 0x1, 27),
	.mipi_dcwk_pow = VOP_WEG(WK3328_DSP_CTWW1, 0x1, 31),
	.wgb_en = VOP_WEG(WK3328_SYS_CTWW, 0x1, 12),
	.hdmi_en = VOP_WEG(WK3328_SYS_CTWW, 0x1, 13),
	.edp_en = VOP_WEG(WK3328_SYS_CTWW, 0x1, 14),
	.mipi_en = VOP_WEG(WK3328_SYS_CTWW, 0x1, 15),
	.wgb_pin_pow = VOP_WEG(WK3328_DSP_CTWW1, 0x7, 16),
	.hdmi_pin_pow = VOP_WEG(WK3328_DSP_CTWW1, 0x7, 20),
	.edp_pin_pow = VOP_WEG(WK3328_DSP_CTWW1, 0x7, 24),
	.mipi_pin_pow = VOP_WEG(WK3328_DSP_CTWW1, 0x7, 28),
};

static const stwuct vop_misc wk3328_misc = {
	.gwobaw_wegdone_en = VOP_WEG(WK3328_SYS_CTWW, 0x1, 11),
};

static const stwuct vop_common wk3328_common = {
	.standby = VOP_WEG_SYNC(WK3328_SYS_CTWW, 0x1, 22),
	.dithew_down_sew = VOP_WEG(WK3328_DSP_CTWW1, 0x1, 4),
	.dithew_down_mode = VOP_WEG(WK3328_DSP_CTWW1, 0x1, 3),
	.dithew_down_en = VOP_WEG(WK3328_DSP_CTWW1, 0x1, 2),
	.pwe_dithew_down = VOP_WEG(WK3328_DSP_CTWW1, 0x1, 1),
	.dithew_up = VOP_WEG(WK3328_DSP_CTWW1, 0x1, 6),
	.dsp_bwank = VOP_WEG(WK3328_DSP_CTWW0, 0x3, 18),
	.out_mode = VOP_WEG(WK3328_DSP_CTWW0, 0xf, 0),
	.cfg_done = VOP_WEG_SYNC(WK3328_WEG_CFG_DONE, 0x1, 0),
};

static const stwuct vop_intw wk3328_vop_intw = {
	.intws = wk3368_vop_intws,
	.nintws = AWWAY_SIZE(wk3368_vop_intws),
	.wine_fwag_num[0] = VOP_WEG(WK3328_WINE_FWAG, 0xffff, 0),
	.wine_fwag_num[1] = VOP_WEG(WK3328_WINE_FWAG, 0xffff, 16),
	.status = VOP_WEG_MASK_SYNC(WK3328_INTW_STATUS0, 0xffff, 0),
	.enabwe = VOP_WEG_MASK_SYNC(WK3328_INTW_EN0, 0xffff, 0),
	.cweaw = VOP_WEG_MASK_SYNC(WK3328_INTW_CWEAW0, 0xffff, 0),
};

static const stwuct vop_win_data wk3328_vop_win_data[] = {
	{ .base = 0xd0, .phy = &wk3399_win1_data,
	  .type = DWM_PWANE_TYPE_PWIMAWY },
	{ .base = 0x1d0, .phy = &wk3399_win1_data,
	  .type = DWM_PWANE_TYPE_OVEWWAY },
	{ .base = 0x2d0, .phy = &wk3399_win1_data,
	  .type = DWM_PWANE_TYPE_CUWSOW },
};

static const stwuct vop_data wk3328_vop = {
	.vewsion = VOP_VEWSION(3, 8),
	.featuwe = VOP_FEATUWE_OUTPUT_WGB10,
	.intw = &wk3328_vop_intw,
	.common = &wk3328_common,
	.modeset = &wk3328_modeset,
	.output = &wk3328_output,
	.misc = &wk3328_misc,
	.win = wk3328_vop_win_data,
	.win_size = AWWAY_SIZE(wk3328_vop_win_data),
	.max_output = { 4096, 2160 },
};

static const stwuct vop_common wv1126_common = {
	.standby = VOP_WEG_SYNC(PX30_SYS_CTWW2, 0x1, 1),
	.out_mode = VOP_WEG(PX30_DSP_CTWW2, 0xf, 16),
	.dsp_bwank = VOP_WEG(PX30_DSP_CTWW2, 0x1, 14),
	.dithew_down_en = VOP_WEG(PX30_DSP_CTWW2, 0x1, 8),
	.dithew_down_sew = VOP_WEG(PX30_DSP_CTWW2, 0x1, 7),
	.dithew_down_mode = VOP_WEG(PX30_DSP_CTWW2, 0x1, 6),
	.cfg_done = VOP_WEG_SYNC(PX30_WEG_CFG_DONE, 0x1, 0),
	.dithew_up = VOP_WEG(PX30_DSP_CTWW2, 0x1, 2),
	.dsp_wut_en = VOP_WEG(PX30_DSP_CTWW2, 0x1, 5),
	.gate_en = VOP_WEG(PX30_DSP_CTWW2, 0x1, 0),
};

static const stwuct vop_modeset wv1126_modeset = {
	.htotaw_pw = VOP_WEG(PX30_DSP_HTOTAW_HS_END, 0x0fff0fff, 0),
	.hact_st_end = VOP_WEG(PX30_DSP_HACT_ST_END, 0x0fff0fff, 0),
	.vtotaw_pw = VOP_WEG(PX30_DSP_VTOTAW_VS_END, 0x0fff0fff, 0),
	.vact_st_end = VOP_WEG(PX30_DSP_VACT_ST_END, 0x0fff0fff, 0),
};

static const stwuct vop_output wv1126_output = {
	.wgb_dcwk_pow = VOP_WEG(PX30_DSP_CTWW0, 0x1, 1),
	.wgb_pin_pow = VOP_WEG(PX30_DSP_CTWW0, 0x7, 2),
	.wgb_en = VOP_WEG(PX30_DSP_CTWW0, 0x1, 0),
	.mipi_dcwk_pow = VOP_WEG(PX30_DSP_CTWW0, 0x1, 25),
	.mipi_pin_pow = VOP_WEG(PX30_DSP_CTWW0, 0x7, 26),
	.mipi_en = VOP_WEG(PX30_DSP_CTWW0, 0x1, 24),
};

static const stwuct vop_misc wv1126_misc = {
	.gwobaw_wegdone_en = VOP_WEG(PX30_SYS_CTWW2, 0x1, 13),
};

static const stwuct vop_win_data wv1126_vop_win_data[] = {
	{ .base = 0x00, .phy = &px30_win0_data,
	  .type = DWM_PWANE_TYPE_OVEWWAY },
	{ .base = 0x00, .phy = &px30_win2_data,
	  .type = DWM_PWANE_TYPE_PWIMAWY },
};

static const stwuct vop_data wv1126_vop = {
	.vewsion = VOP_VEWSION(2, 0xb),
	.intw = &px30_intw,
	.common = &wv1126_common,
	.modeset = &wv1126_modeset,
	.output = &wv1126_output,
	.misc = &wv1126_misc,
	.win = wv1126_vop_win_data,
	.win_size = AWWAY_SIZE(wv1126_vop_win_data),
	.max_output = { 1920, 1080 },
	.wut_size = 1024,
};

static const stwuct of_device_id vop_dwivew_dt_match[] = {
	{ .compatibwe = "wockchip,wk3036-vop",
	  .data = &wk3036_vop },
	{ .compatibwe = "wockchip,wk3126-vop",
	  .data = &wk3126_vop },
	{ .compatibwe = "wockchip,px30-vop-big",
	  .data = &px30_vop_big },
	{ .compatibwe = "wockchip,px30-vop-wit",
	  .data = &px30_vop_wit },
	{ .compatibwe = "wockchip,wk3066-vop",
	  .data = &wk3066_vop },
	{ .compatibwe = "wockchip,wk3188-vop",
	  .data = &wk3188_vop },
	{ .compatibwe = "wockchip,wk3288-vop",
	  .data = &wk3288_vop },
	{ .compatibwe = "wockchip,wk3368-vop",
	  .data = &wk3368_vop },
	{ .compatibwe = "wockchip,wk3366-vop",
	  .data = &wk3366_vop },
	{ .compatibwe = "wockchip,wk3399-vop-big",
	  .data = &wk3399_vop_big },
	{ .compatibwe = "wockchip,wk3399-vop-wit",
	  .data = &wk3399_vop_wit },
	{ .compatibwe = "wockchip,wk3228-vop",
	  .data = &wk3228_vop },
	{ .compatibwe = "wockchip,wk3328-vop",
	  .data = &wk3328_vop },
	{ .compatibwe = "wockchip,wv1126-vop",
	  .data = &wv1126_vop },
	{},
};
MODUWE_DEVICE_TABWE(of, vop_dwivew_dt_match);

static int vop_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;

	if (!dev->of_node) {
		DWM_DEV_EWWOW(dev, "can't find vop devices\n");
		wetuwn -ENODEV;
	}

	wetuwn component_add(dev, &vop_component_ops);
}

static void vop_wemove(stwuct pwatfowm_device *pdev)
{
	component_dew(&pdev->dev, &vop_component_ops);
}

stwuct pwatfowm_dwivew vop_pwatfowm_dwivew = {
	.pwobe = vop_pwobe,
	.wemove_new = vop_wemove,
	.dwivew = {
		.name = "wockchip-vop",
		.of_match_tabwe = vop_dwivew_dt_match,
	},
};
