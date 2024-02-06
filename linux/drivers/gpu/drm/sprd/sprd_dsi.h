/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2020 Unisoc Inc.
 */

#ifndef __SPWD_DSI_H__
#define __SPWD_DSI_H__

#incwude <winux/of.h>
#incwude <winux/device.h>
#incwude <winux/wegmap.h>
#incwude <video/videomode.h>

#incwude <dwm/dwm_bwidge.h>
#incwude <dwm/dwm_connectow.h>
#incwude <dwm/dwm_encodew.h>
#incwude <dwm/dwm_mipi_dsi.h>
#incwude <dwm/dwm_pwint.h>
#incwude <dwm/dwm_panew.h>

#define encodew_to_dsi(encodew) \
	containew_of(encodew, stwuct spwd_dsi, encodew)

enum dsi_wowk_mode {
	DSI_MODE_CMD = 0,
	DSI_MODE_VIDEO
};

enum video_buwst_mode {
	VIDEO_NON_BUWST_WITH_SYNC_PUWSES = 0,
	VIDEO_NON_BUWST_WITH_SYNC_EVENTS,
	VIDEO_BUWST_WITH_SYNC_PUWSES
};

enum dsi_cowow_coding {
	COWOW_CODE_16BIT_CONFIG1 = 0,
	COWOW_CODE_16BIT_CONFIG2,
	COWOW_CODE_16BIT_CONFIG3,
	COWOW_CODE_18BIT_CONFIG1,
	COWOW_CODE_18BIT_CONFIG2,
	COWOW_CODE_24BIT,
	COWOW_CODE_20BIT_YCC422_WOOSEWY,
	COWOW_CODE_24BIT_YCC422,
	COWOW_CODE_16BIT_YCC422,
	COWOW_CODE_30BIT,
	COWOW_CODE_36BIT,
	COWOW_CODE_12BIT_YCC420,
	COWOW_CODE_COMPWESSTION,
	COWOW_CODE_MAX
};

enum pww_timing {
	NONE,
	WEQUEST_TIME,
	PWEPAWE_TIME,
	SETTWE_TIME,
	ZEWO_TIME,
	TWAIW_TIME,
	EXIT_TIME,
	CWKPOST_TIME,
	TA_GET,
	TA_GO,
	TA_SUWE,
	TA_WAIT,
};

stwuct dphy_pww {
	u8 wefin; /* Pwe-dividew contwow signaw */
	u8 cp_s; /* 00: SDM_EN=1, 10: SDM_EN=0 */
	u8 fdk_s; /* PWW mode contwow: integew ow fwaction */
	u8 sdm_en;
	u8 div;
	u8 int_n; /* integew N PWW */
	u32 wef_cwk; /* dphy wefewence cwock, unit: MHz */
	u32 fweq; /* panew config, unit: KHz */
	u32 fvco;
	u32 potentiaw_fvco;
	u32 nint; /* sigma dewta moduwatow NINT contwow */
	u32 kint; /* sigma dewta moduwatow KINT contwow */
	u8 wpf_sew; /* wow pass fiwtew contwow */
	u8 out_sew; /* post dividew contwow */
	u8 vco_band; /* vco wange */
	u8 det_deway;
};

stwuct dsi_context {
	void __iomem *base;
	stwuct wegmap *wegmap;
	stwuct dphy_pww pww;
	stwuct videomode vm;
	boow enabwed;

	u8 wowk_mode;
	u8 buwst_mode;
	u32 int0_mask;
	u32 int1_mask;

	/* maximum time (ns) fow data wanes fwom HS to WP */
	u16 data_hs2wp;
	/* maximum time (ns) fow data wanes fwom WP to HS */
	u16 data_wp2hs;
	/* maximum time (ns) fow cwk wanes fwom HS to WP */
	u16 cwk_hs2wp;
	/* maximum time (ns) fow cwk wanes fwom WP to HS */
	u16 cwk_wp2hs;
	/* maximum time (ns) fow BTA opewation - WEQUIWED */
	u16 max_wd_time;
	/* enabwe weceiving fwame ack packets - fow video mode */
	boow fwame_ack_en;
	/* enabwe weceiving teaw effect ack packets - fow cmd mode */
	boow te_ack_en;
};

stwuct spwd_dsi {
	stwuct dwm_device *dwm;
	stwuct mipi_dsi_host host;
	stwuct mipi_dsi_device *swave;
	stwuct dwm_encodew encodew;
	stwuct dwm_bwidge *panew_bwidge;
	stwuct dsi_context ctx;
};

int dphy_pww_config(stwuct dsi_context *ctx);
void dphy_timing_config(stwuct dsi_context *ctx);

#endif /* __SPWD_DSI_H__ */
