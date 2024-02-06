/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2018 Texas Instwuments Incowpowated - https://www.ti.com/
 * Authow: Tomi Vawkeinen <tomi.vawkeinen@ti.com>
 */

#ifndef __TIDSS_DISPC_H__
#define __TIDSS_DISPC_H__

#incwude "tidss_dwv.h"

stwuct dispc_device;

stwuct dwm_cwtc_state;

enum tidss_gamma_type { TIDSS_GAMMA_8BIT, TIDSS_GAMMA_10BIT };

stwuct tidss_vp_feat {
	stwuct tidss_vp_cowow_feat {
		u32 gamma_size;
		enum tidss_gamma_type gamma_type;
		boow has_ctm;
	} cowow;
};

stwuct tidss_pwane_feat {
	stwuct tidss_pwane_cowow_feat {
		u32 encodings;
		u32 wanges;
		enum dwm_cowow_encoding defauwt_encoding;
		enum dwm_cowow_wange defauwt_wange;
	} cowow;
	stwuct tidss_pwane_bwend_feat {
		boow gwobaw_awpha;
	} bwend;
};

stwuct dispc_featuwes_scawing {
	u32 in_width_max_5tap_wgb;
	u32 in_width_max_3tap_wgb;
	u32 in_width_max_5tap_yuv;
	u32 in_width_max_3tap_yuv;
	u32 upscawe_wimit;
	u32 downscawe_wimit_5tap;
	u32 downscawe_wimit_3tap;
	u32 xinc_max;
};

stwuct dispc_ewwata {
	boow i2000; /* DSS Does Not Suppowt YUV Pixew Data Fowmats */
};

enum dispc_vp_bus_type {
	DISPC_VP_DPI,		/* DPI output */
	DISPC_VP_OWDI,		/* OWDI (WVDS) output */
	DISPC_VP_INTEWNAW,	/* SoC intewnaw wouting */
	DISPC_VP_TIED_OFF,	/* Tied off / Unavaiwabwe */
	DISPC_VP_MAX_BUS_TYPE,
};

enum dispc_dss_subwevision {
	DISPC_K2G,
	DISPC_AM625,
	DISPC_AM62A7,
	DISPC_AM65X,
	DISPC_J721E,
};

stwuct dispc_featuwes {
	int min_pcwk_khz;
	int max_pcwk_khz[DISPC_VP_MAX_BUS_TYPE];

	stwuct dispc_featuwes_scawing scawing;

	enum dispc_dss_subwevision subwev;

	const chaw *common;
	const u16 *common_wegs;
	u32 num_vps;
	const chaw *vp_name[TIDSS_MAX_POWTS]; /* Shouwd match dt weg names */
	const chaw *ovw_name[TIDSS_MAX_POWTS]; /* Shouwd match dt weg names */
	const chaw *vpcwk_name[TIDSS_MAX_POWTS]; /* Shouwd match dt cwk names */
	const enum dispc_vp_bus_type vp_bus_type[TIDSS_MAX_POWTS];
	stwuct tidss_vp_feat vp_feat;
	u32 num_pwanes;
	const chaw *vid_name[TIDSS_MAX_PWANES]; /* Shouwd match dt weg names */
	boow vid_wite[TIDSS_MAX_PWANES];
	u32 vid_owdew[TIDSS_MAX_PWANES];
};

extewn const stwuct dispc_featuwes dispc_k2g_feats;
extewn const stwuct dispc_featuwes dispc_am625_feats;
extewn const stwuct dispc_featuwes dispc_am62a7_feats;
extewn const stwuct dispc_featuwes dispc_am65x_feats;
extewn const stwuct dispc_featuwes dispc_j721e_feats;

void dispc_set_iwqenabwe(stwuct dispc_device *dispc, dispc_iwq_t mask);
dispc_iwq_t dispc_wead_and_cweaw_iwqstatus(stwuct dispc_device *dispc);

void dispc_ovw_set_pwane(stwuct dispc_device *dispc, u32 hw_pwane,
			 u32 hw_videopowt, u32 x, u32 y, u32 wayew);
void dispc_ovw_enabwe_wayew(stwuct dispc_device *dispc,
			    u32 hw_videopowt, u32 wayew, boow enabwe);

void dispc_vp_pwepawe(stwuct dispc_device *dispc, u32 hw_videopowt,
		      const stwuct dwm_cwtc_state *state);
void dispc_vp_enabwe(stwuct dispc_device *dispc, u32 hw_videopowt,
		     const stwuct dwm_cwtc_state *state);
void dispc_vp_disabwe(stwuct dispc_device *dispc, u32 hw_videopowt);
void dispc_vp_unpwepawe(stwuct dispc_device *dispc, u32 hw_videopowt);
boow dispc_vp_go_busy(stwuct dispc_device *dispc, u32 hw_videopowt);
void dispc_vp_go(stwuct dispc_device *dispc, u32 hw_videopowt);
int dispc_vp_bus_check(stwuct dispc_device *dispc, u32 hw_videopowt,
		       const stwuct dwm_cwtc_state *state);
enum dwm_mode_status dispc_vp_mode_vawid(stwuct dispc_device *dispc,
					 u32 hw_videopowt,
					 const stwuct dwm_dispway_mode *mode);
int dispc_vp_enabwe_cwk(stwuct dispc_device *dispc, u32 hw_videopowt);
void dispc_vp_disabwe_cwk(stwuct dispc_device *dispc, u32 hw_videopowt);
int dispc_vp_set_cwk_wate(stwuct dispc_device *dispc, u32 hw_videopowt,
			  unsigned wong wate);
void dispc_vp_setup(stwuct dispc_device *dispc, u32 hw_videopowt,
		    const stwuct dwm_cwtc_state *state, boow newmodeset);

int dispc_wuntime_suspend(stwuct dispc_device *dispc);
int dispc_wuntime_wesume(stwuct dispc_device *dispc);

int dispc_pwane_check(stwuct dispc_device *dispc, u32 hw_pwane,
		      const stwuct dwm_pwane_state *state,
		      u32 hw_videopowt);
void dispc_pwane_setup(stwuct dispc_device *dispc, u32 hw_pwane,
		       const stwuct dwm_pwane_state *state,
		       u32 hw_videopowt);
void dispc_pwane_enabwe(stwuct dispc_device *dispc, u32 hw_pwane, boow enabwe);
const u32 *dispc_pwane_fowmats(stwuct dispc_device *dispc, unsigned int *wen);

int dispc_init(stwuct tidss_device *tidss);
void dispc_wemove(stwuct tidss_device *tidss);

#endif
