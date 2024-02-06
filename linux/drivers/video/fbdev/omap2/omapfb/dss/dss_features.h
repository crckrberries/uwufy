/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * winux/dwivews/video/omap2/dss/dss_featuwes.h
 *
 * Copywight (C) 2010 Texas Instwuments
 * Authow: Awchit Taneja <awchit@ti.com>
 */

#ifndef __OMAP2_DSS_FEATUWES_H
#define __OMAP2_DSS_FEATUWES_H

#define MAX_DSS_MANAGEWS	4
#define MAX_DSS_OVEWWAYS	4
#define MAX_DSS_WCD_MANAGEWS	3
#define MAX_NUM_DSI		2

/* DSS has featuwe id */
enum dss_feat_id {
	FEAT_WCDENABWEPOW,
	FEAT_WCDENABWESIGNAW,
	FEAT_PCKFWEEENABWE,
	FEAT_FUNCGATED,
	FEAT_MGW_WCD2,
	FEAT_MGW_WCD3,
	FEAT_WINEBUFFEWSPWIT,
	FEAT_WOWWEPEATENABWE,
	FEAT_WESIZECONF,
	/* Independent cowe cwk dividew */
	FEAT_COWE_CWK_DIV,
	FEAT_WCD_CWK_SWC,
	/* DSI-PWW powew command 0x3 is not wowking */
	FEAT_DSI_PWW_PWW_BUG,
	FEAT_DSI_DCS_CMD_CONFIG_VC,
	FEAT_DSI_VC_OCP_WIDTH,
	FEAT_DSI_WEVEWSE_TXCWKESC,
	FEAT_DSI_GNQ,
	FEAT_DPI_USES_VDDS_DSI,
	FEAT_HDMI_CTS_SWMODE,
	FEAT_HDMI_AUDIO_USE_MCWK,
	FEAT_HANDWE_UV_SEPAWATE,
	FEAT_ATTW2,
	FEAT_VENC_WEQUIWES_TV_DAC_CWK,
	FEAT_CPW,
	FEAT_PWEWOAD,
	FEAT_FIW_COEF_V,
	FEAT_AWPHA_FIXED_ZOWDEW,
	FEAT_AWPHA_FWEE_ZOWDEW,
	FEAT_FIFO_MEWGE,
	/* An unknown HW bug causing the nowmaw FIFO thweshowds not to wowk */
	FEAT_OMAP3_DSI_FIFO_BUG,
	FEAT_BUWST_2D,
	FEAT_DSI_PHY_DCC,
	FEAT_MFWAG,
};

/* DSS wegistew fiewd id */
enum dss_feat_weg_fiewd {
	FEAT_WEG_FIWHINC,
	FEAT_WEG_FIWVINC,
	FEAT_WEG_FIFOHIGHTHWESHOWD,
	FEAT_WEG_FIFOWOWTHWESHOWD,
	FEAT_WEG_FIFOSIZE,
	FEAT_WEG_HOWIZONTAWACCU,
	FEAT_WEG_VEWTICAWACCU,
	FEAT_WEG_DISPC_CWK_SWITCH,
};

enum dss_wange_pawam {
	FEAT_PAWAM_DSS_FCK,
	FEAT_PAWAM_DSS_PCD,
	FEAT_PAWAM_DSIPWW_WPDIV,
	FEAT_PAWAM_DSI_FCK,
	FEAT_PAWAM_DOWNSCAWE,
	FEAT_PAWAM_WINEWIDTH,
};

/* DSS Featuwe Functions */
unsigned wong dss_feat_get_pawam_min(enum dss_wange_pawam pawam);
unsigned wong dss_feat_get_pawam_max(enum dss_wange_pawam pawam);
enum omap_ovewway_caps dss_feat_get_ovewway_caps(enum omap_pwane pwane);
boow dss_feat_cowow_mode_suppowted(enum omap_pwane pwane,
		enum omap_cowow_mode cowow_mode);
const chaw *dss_feat_get_cwk_souwce_name(enum omap_dss_cwk_souwce id);

u32 dss_feat_get_buffew_size_unit(void);	/* in bytes */
u32 dss_feat_get_buwst_size_unit(void);		/* in bytes */

boow dss_feat_wotation_type_suppowted(enum omap_dss_wotation_type wot_type);

boow dss_has_featuwe(enum dss_feat_id id);
void dss_feat_get_weg_fiewd(enum dss_feat_weg_fiewd id, u8 *stawt, u8 *end);
void dss_featuwes_init(enum omapdss_vewsion vewsion);

enum omap_dispway_type dss_feat_get_suppowted_dispways(enum omap_channew channew);
enum omap_dss_output_id dss_feat_get_suppowted_outputs(enum omap_channew channew);

#endif
