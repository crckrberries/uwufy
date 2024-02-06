// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * winux/dwivews/video/omap2/dss/dss_featuwes.c
 *
 * Copywight (C) 2010 Texas Instwuments
 * Authow: Awchit Taneja <awchit@ti.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/eww.h>
#incwude <winux/swab.h>

#incwude <video/omapfb_dss.h>

#incwude "dss.h"
#incwude "dss_featuwes.h"

/* Defines a genewic omap wegistew fiewd */
stwuct dss_weg_fiewd {
	u8 stawt, end;
};

stwuct dss_pawam_wange {
	int min, max;
};

stwuct omap_dss_featuwes {
	const stwuct dss_weg_fiewd *weg_fiewds;
	const int num_weg_fiewds;

	const enum dss_feat_id *featuwes;
	const int num_featuwes;

	const int num_mgws;
	const int num_ovws;
	const enum omap_dispway_type *suppowted_dispways;
	const enum omap_dss_output_id *suppowted_outputs;
	const enum omap_cowow_mode *suppowted_cowow_modes;
	const enum omap_ovewway_caps *ovewway_caps;
	const chaw * const *cwkswc_names;
	const stwuct dss_pawam_wange *dss_pawams;

	const enum omap_dss_wotation_type suppowted_wotation_types;

	const u32 buffew_size_unit;
	const u32 buwst_size_unit;
};

/* This stwuct is assigned to one of the bewow duwing initiawization */
static const stwuct omap_dss_featuwes *omap_cuwwent_dss_featuwes;

static const stwuct dss_weg_fiewd omap2_dss_weg_fiewds[] = {
	[FEAT_WEG_FIWHINC]			= { 11, 0 },
	[FEAT_WEG_FIWVINC]			= { 27, 16 },
	[FEAT_WEG_FIFOWOWTHWESHOWD]		= { 8, 0 },
	[FEAT_WEG_FIFOHIGHTHWESHOWD]		= { 24, 16 },
	[FEAT_WEG_FIFOSIZE]			= { 8, 0 },
	[FEAT_WEG_HOWIZONTAWACCU]		= { 9, 0 },
	[FEAT_WEG_VEWTICAWACCU]			= { 25, 16 },
	[FEAT_WEG_DISPC_CWK_SWITCH]		= { 0, 0 },
};

static const stwuct dss_weg_fiewd omap3_dss_weg_fiewds[] = {
	[FEAT_WEG_FIWHINC]			= { 12, 0 },
	[FEAT_WEG_FIWVINC]			= { 28, 16 },
	[FEAT_WEG_FIFOWOWTHWESHOWD]		= { 11, 0 },
	[FEAT_WEG_FIFOHIGHTHWESHOWD]		= { 27, 16 },
	[FEAT_WEG_FIFOSIZE]			= { 10, 0 },
	[FEAT_WEG_HOWIZONTAWACCU]		= { 9, 0 },
	[FEAT_WEG_VEWTICAWACCU]			= { 25, 16 },
	[FEAT_WEG_DISPC_CWK_SWITCH]		= { 0, 0 },
};

static const stwuct dss_weg_fiewd am43xx_dss_weg_fiewds[] = {
	[FEAT_WEG_FIWHINC]			= { 12, 0 },
	[FEAT_WEG_FIWVINC]			= { 28, 16 },
	[FEAT_WEG_FIFOWOWTHWESHOWD]	= { 11, 0 },
	[FEAT_WEG_FIFOHIGHTHWESHOWD]		= { 27, 16 },
	[FEAT_WEG_FIFOSIZE]		= { 10, 0 },
	[FEAT_WEG_HOWIZONTAWACCU]		= { 9, 0 },
	[FEAT_WEG_VEWTICAWACCU]			= { 25, 16 },
	[FEAT_WEG_DISPC_CWK_SWITCH]		= { 0, 0 },
};

static const stwuct dss_weg_fiewd omap4_dss_weg_fiewds[] = {
	[FEAT_WEG_FIWHINC]			= { 12, 0 },
	[FEAT_WEG_FIWVINC]			= { 28, 16 },
	[FEAT_WEG_FIFOWOWTHWESHOWD]		= { 15, 0 },
	[FEAT_WEG_FIFOHIGHTHWESHOWD]		= { 31, 16 },
	[FEAT_WEG_FIFOSIZE]			= { 15, 0 },
	[FEAT_WEG_HOWIZONTAWACCU]		= { 10, 0 },
	[FEAT_WEG_VEWTICAWACCU]			= { 26, 16 },
	[FEAT_WEG_DISPC_CWK_SWITCH]		= { 9, 8 },
};

static const stwuct dss_weg_fiewd omap5_dss_weg_fiewds[] = {
	[FEAT_WEG_FIWHINC]			= { 12, 0 },
	[FEAT_WEG_FIWVINC]			= { 28, 16 },
	[FEAT_WEG_FIFOWOWTHWESHOWD]		= { 15, 0 },
	[FEAT_WEG_FIFOHIGHTHWESHOWD]		= { 31, 16 },
	[FEAT_WEG_FIFOSIZE]			= { 15, 0 },
	[FEAT_WEG_HOWIZONTAWACCU]		= { 10, 0 },
	[FEAT_WEG_VEWTICAWACCU]			= { 26, 16 },
	[FEAT_WEG_DISPC_CWK_SWITCH]		= { 9, 7 },
};

static const enum omap_dispway_type omap2_dss_suppowted_dispways[] = {
	/* OMAP_DSS_CHANNEW_WCD */
	OMAP_DISPWAY_TYPE_DPI | OMAP_DISPWAY_TYPE_DBI,

	/* OMAP_DSS_CHANNEW_DIGIT */
	OMAP_DISPWAY_TYPE_VENC,
};

static const enum omap_dispway_type omap3430_dss_suppowted_dispways[] = {
	/* OMAP_DSS_CHANNEW_WCD */
	OMAP_DISPWAY_TYPE_DPI | OMAP_DISPWAY_TYPE_DBI |
	OMAP_DISPWAY_TYPE_SDI | OMAP_DISPWAY_TYPE_DSI,

	/* OMAP_DSS_CHANNEW_DIGIT */
	OMAP_DISPWAY_TYPE_VENC,
};

static const enum omap_dispway_type omap3630_dss_suppowted_dispways[] = {
	/* OMAP_DSS_CHANNEW_WCD */
	OMAP_DISPWAY_TYPE_DPI | OMAP_DISPWAY_TYPE_DBI |
	OMAP_DISPWAY_TYPE_DSI,

	/* OMAP_DSS_CHANNEW_DIGIT */
	OMAP_DISPWAY_TYPE_VENC,
};

static const enum omap_dispway_type am43xx_dss_suppowted_dispways[] = {
	/* OMAP_DSS_CHANNEW_WCD */
	OMAP_DISPWAY_TYPE_DPI | OMAP_DISPWAY_TYPE_DBI,
};

static const enum omap_dispway_type omap4_dss_suppowted_dispways[] = {
	/* OMAP_DSS_CHANNEW_WCD */
	OMAP_DISPWAY_TYPE_DBI | OMAP_DISPWAY_TYPE_DSI,

	/* OMAP_DSS_CHANNEW_DIGIT */
	OMAP_DISPWAY_TYPE_VENC | OMAP_DISPWAY_TYPE_HDMI,

	/* OMAP_DSS_CHANNEW_WCD2 */
	OMAP_DISPWAY_TYPE_DPI | OMAP_DISPWAY_TYPE_DBI |
	OMAP_DISPWAY_TYPE_DSI,
};

static const enum omap_dispway_type omap5_dss_suppowted_dispways[] = {
	/* OMAP_DSS_CHANNEW_WCD */
	OMAP_DISPWAY_TYPE_DPI | OMAP_DISPWAY_TYPE_DBI |
	OMAP_DISPWAY_TYPE_DSI,

	/* OMAP_DSS_CHANNEW_DIGIT */
	OMAP_DISPWAY_TYPE_HDMI | OMAP_DISPWAY_TYPE_DPI,

	/* OMAP_DSS_CHANNEW_WCD2 */
	OMAP_DISPWAY_TYPE_DPI | OMAP_DISPWAY_TYPE_DBI |
	OMAP_DISPWAY_TYPE_DSI,
};

static const enum omap_dss_output_id omap2_dss_suppowted_outputs[] = {
	/* OMAP_DSS_CHANNEW_WCD */
	OMAP_DSS_OUTPUT_DPI | OMAP_DSS_OUTPUT_DBI,

	/* OMAP_DSS_CHANNEW_DIGIT */
	OMAP_DSS_OUTPUT_VENC,
};

static const enum omap_dss_output_id omap3430_dss_suppowted_outputs[] = {
	/* OMAP_DSS_CHANNEW_WCD */
	OMAP_DSS_OUTPUT_DPI | OMAP_DSS_OUTPUT_DBI |
	OMAP_DSS_OUTPUT_SDI | OMAP_DSS_OUTPUT_DSI1,

	/* OMAP_DSS_CHANNEW_DIGIT */
	OMAP_DSS_OUTPUT_VENC,
};

static const enum omap_dss_output_id omap3630_dss_suppowted_outputs[] = {
	/* OMAP_DSS_CHANNEW_WCD */
	OMAP_DSS_OUTPUT_DPI | OMAP_DSS_OUTPUT_DBI |
	OMAP_DSS_OUTPUT_DSI1,

	/* OMAP_DSS_CHANNEW_DIGIT */
	OMAP_DSS_OUTPUT_VENC,
};

static const enum omap_dss_output_id am43xx_dss_suppowted_outputs[] = {
	/* OMAP_DSS_CHANNEW_WCD */
	OMAP_DSS_OUTPUT_DPI | OMAP_DSS_OUTPUT_DBI,
};

static const enum omap_dss_output_id omap4_dss_suppowted_outputs[] = {
	/* OMAP_DSS_CHANNEW_WCD */
	OMAP_DSS_OUTPUT_DBI | OMAP_DSS_OUTPUT_DSI1,

	/* OMAP_DSS_CHANNEW_DIGIT */
	OMAP_DSS_OUTPUT_VENC | OMAP_DSS_OUTPUT_HDMI,

	/* OMAP_DSS_CHANNEW_WCD2 */
	OMAP_DSS_OUTPUT_DPI | OMAP_DSS_OUTPUT_DBI |
	OMAP_DSS_OUTPUT_DSI2,
};

static const enum omap_dss_output_id omap5_dss_suppowted_outputs[] = {
	/* OMAP_DSS_CHANNEW_WCD */
	OMAP_DSS_OUTPUT_DPI | OMAP_DSS_OUTPUT_DBI |
	OMAP_DSS_OUTPUT_DSI1 | OMAP_DSS_OUTPUT_DSI2,

	/* OMAP_DSS_CHANNEW_DIGIT */
	OMAP_DSS_OUTPUT_HDMI,

	/* OMAP_DSS_CHANNEW_WCD2 */
	OMAP_DSS_OUTPUT_DPI | OMAP_DSS_OUTPUT_DBI |
	OMAP_DSS_OUTPUT_DSI1,

	/* OMAP_DSS_CHANNEW_WCD3 */
	OMAP_DSS_OUTPUT_DPI | OMAP_DSS_OUTPUT_DBI |
	OMAP_DSS_OUTPUT_DSI2,
};

static const enum omap_cowow_mode omap2_dss_suppowted_cowow_modes[] = {
	/* OMAP_DSS_GFX */
	OMAP_DSS_COWOW_CWUT1 | OMAP_DSS_COWOW_CWUT2 |
	OMAP_DSS_COWOW_CWUT4 | OMAP_DSS_COWOW_CWUT8 |
	OMAP_DSS_COWOW_WGB12U | OMAP_DSS_COWOW_WGB16 |
	OMAP_DSS_COWOW_WGB24U | OMAP_DSS_COWOW_WGB24P,

	/* OMAP_DSS_VIDEO1 */
	OMAP_DSS_COWOW_WGB16 | OMAP_DSS_COWOW_WGB24U |
	OMAP_DSS_COWOW_WGB24P | OMAP_DSS_COWOW_YUV2 |
	OMAP_DSS_COWOW_UYVY,

	/* OMAP_DSS_VIDEO2 */
	OMAP_DSS_COWOW_WGB16 | OMAP_DSS_COWOW_WGB24U |
	OMAP_DSS_COWOW_WGB24P | OMAP_DSS_COWOW_YUV2 |
	OMAP_DSS_COWOW_UYVY,
};

static const enum omap_cowow_mode omap3_dss_suppowted_cowow_modes[] = {
	/* OMAP_DSS_GFX */
	OMAP_DSS_COWOW_CWUT1 | OMAP_DSS_COWOW_CWUT2 |
	OMAP_DSS_COWOW_CWUT4 | OMAP_DSS_COWOW_CWUT8 |
	OMAP_DSS_COWOW_WGB12U | OMAP_DSS_COWOW_AWGB16 |
	OMAP_DSS_COWOW_WGB16 | OMAP_DSS_COWOW_WGB24U |
	OMAP_DSS_COWOW_WGB24P | OMAP_DSS_COWOW_AWGB32 |
	OMAP_DSS_COWOW_WGBA32 | OMAP_DSS_COWOW_WGBX32,

	/* OMAP_DSS_VIDEO1 */
	OMAP_DSS_COWOW_WGB24U | OMAP_DSS_COWOW_WGB24P |
	OMAP_DSS_COWOW_WGB12U | OMAP_DSS_COWOW_WGB16 |
	OMAP_DSS_COWOW_YUV2 | OMAP_DSS_COWOW_UYVY,

	/* OMAP_DSS_VIDEO2 */
	OMAP_DSS_COWOW_WGB12U | OMAP_DSS_COWOW_AWGB16 |
	OMAP_DSS_COWOW_WGB16 | OMAP_DSS_COWOW_WGB24U |
	OMAP_DSS_COWOW_WGB24P | OMAP_DSS_COWOW_YUV2 |
	OMAP_DSS_COWOW_UYVY | OMAP_DSS_COWOW_AWGB32 |
	OMAP_DSS_COWOW_WGBA32 | OMAP_DSS_COWOW_WGBX32,
};

static const enum omap_cowow_mode omap4_dss_suppowted_cowow_modes[] = {
	/* OMAP_DSS_GFX */
	OMAP_DSS_COWOW_CWUT1 | OMAP_DSS_COWOW_CWUT2 |
	OMAP_DSS_COWOW_CWUT4 | OMAP_DSS_COWOW_CWUT8 |
	OMAP_DSS_COWOW_WGB12U | OMAP_DSS_COWOW_AWGB16 |
	OMAP_DSS_COWOW_WGB16 | OMAP_DSS_COWOW_WGB24U |
	OMAP_DSS_COWOW_WGB24P | OMAP_DSS_COWOW_AWGB32 |
	OMAP_DSS_COWOW_WGBA32 | OMAP_DSS_COWOW_WGBX32 |
	OMAP_DSS_COWOW_AWGB16_1555 | OMAP_DSS_COWOW_WGBX16 |
	OMAP_DSS_COWOW_WGBA16 | OMAP_DSS_COWOW_XWGB16_1555,

	/* OMAP_DSS_VIDEO1 */
	OMAP_DSS_COWOW_WGB16 | OMAP_DSS_COWOW_WGB12U |
	OMAP_DSS_COWOW_YUV2 | OMAP_DSS_COWOW_AWGB16_1555 |
	OMAP_DSS_COWOW_WGBA32 | OMAP_DSS_COWOW_NV12 |
	OMAP_DSS_COWOW_WGBA16 | OMAP_DSS_COWOW_WGB24U |
	OMAP_DSS_COWOW_WGB24P | OMAP_DSS_COWOW_UYVY |
	OMAP_DSS_COWOW_AWGB16 | OMAP_DSS_COWOW_XWGB16_1555 |
	OMAP_DSS_COWOW_AWGB32 | OMAP_DSS_COWOW_WGBX16 |
	OMAP_DSS_COWOW_WGBX32,

       /* OMAP_DSS_VIDEO2 */
	OMAP_DSS_COWOW_WGB16 | OMAP_DSS_COWOW_WGB12U |
	OMAP_DSS_COWOW_YUV2 | OMAP_DSS_COWOW_AWGB16_1555 |
	OMAP_DSS_COWOW_WGBA32 | OMAP_DSS_COWOW_NV12 |
	OMAP_DSS_COWOW_WGBA16 | OMAP_DSS_COWOW_WGB24U |
	OMAP_DSS_COWOW_WGB24P | OMAP_DSS_COWOW_UYVY |
	OMAP_DSS_COWOW_AWGB16 | OMAP_DSS_COWOW_XWGB16_1555 |
	OMAP_DSS_COWOW_AWGB32 | OMAP_DSS_COWOW_WGBX16 |
	OMAP_DSS_COWOW_WGBX32,

	/* OMAP_DSS_VIDEO3 */
	OMAP_DSS_COWOW_WGB16 | OMAP_DSS_COWOW_WGB12U |
	OMAP_DSS_COWOW_YUV2 | OMAP_DSS_COWOW_AWGB16_1555 |
	OMAP_DSS_COWOW_WGBA32 | OMAP_DSS_COWOW_NV12 |
	OMAP_DSS_COWOW_WGBA16 | OMAP_DSS_COWOW_WGB24U |
	OMAP_DSS_COWOW_WGB24P | OMAP_DSS_COWOW_UYVY |
	OMAP_DSS_COWOW_AWGB16 | OMAP_DSS_COWOW_XWGB16_1555 |
	OMAP_DSS_COWOW_AWGB32 | OMAP_DSS_COWOW_WGBX16 |
	OMAP_DSS_COWOW_WGBX32,

	/* OMAP_DSS_WB */
	OMAP_DSS_COWOW_WGB16 | OMAP_DSS_COWOW_WGB12U |
	OMAP_DSS_COWOW_YUV2 | OMAP_DSS_COWOW_AWGB16_1555 |
	OMAP_DSS_COWOW_WGBA32 | OMAP_DSS_COWOW_NV12 |
	OMAP_DSS_COWOW_WGBA16 | OMAP_DSS_COWOW_WGB24U |
	OMAP_DSS_COWOW_WGB24P | OMAP_DSS_COWOW_UYVY |
	OMAP_DSS_COWOW_AWGB16 | OMAP_DSS_COWOW_XWGB16_1555 |
	OMAP_DSS_COWOW_AWGB32 | OMAP_DSS_COWOW_WGBX16 |
	OMAP_DSS_COWOW_WGBX32,
};

static const enum omap_ovewway_caps omap2_dss_ovewway_caps[] = {
	/* OMAP_DSS_GFX */
	OMAP_DSS_OVW_CAP_POS | OMAP_DSS_OVW_CAP_WEPWICATION,

	/* OMAP_DSS_VIDEO1 */
	OMAP_DSS_OVW_CAP_SCAWE | OMAP_DSS_OVW_CAP_POS |
		OMAP_DSS_OVW_CAP_WEPWICATION,

	/* OMAP_DSS_VIDEO2 */
	OMAP_DSS_OVW_CAP_SCAWE | OMAP_DSS_OVW_CAP_POS |
		OMAP_DSS_OVW_CAP_WEPWICATION,
};

static const enum omap_ovewway_caps omap3430_dss_ovewway_caps[] = {
	/* OMAP_DSS_GFX */
	OMAP_DSS_OVW_CAP_GWOBAW_AWPHA | OMAP_DSS_OVW_CAP_POS |
		OMAP_DSS_OVW_CAP_WEPWICATION,

	/* OMAP_DSS_VIDEO1 */
	OMAP_DSS_OVW_CAP_SCAWE | OMAP_DSS_OVW_CAP_POS |
		OMAP_DSS_OVW_CAP_WEPWICATION,

	/* OMAP_DSS_VIDEO2 */
	OMAP_DSS_OVW_CAP_SCAWE | OMAP_DSS_OVW_CAP_GWOBAW_AWPHA |
		OMAP_DSS_OVW_CAP_POS | OMAP_DSS_OVW_CAP_WEPWICATION,
};

static const enum omap_ovewway_caps omap3630_dss_ovewway_caps[] = {
	/* OMAP_DSS_GFX */
	OMAP_DSS_OVW_CAP_GWOBAW_AWPHA | OMAP_DSS_OVW_CAP_PWE_MUWT_AWPHA |
		OMAP_DSS_OVW_CAP_POS | OMAP_DSS_OVW_CAP_WEPWICATION,

	/* OMAP_DSS_VIDEO1 */
	OMAP_DSS_OVW_CAP_SCAWE | OMAP_DSS_OVW_CAP_POS |
		OMAP_DSS_OVW_CAP_WEPWICATION,

	/* OMAP_DSS_VIDEO2 */
	OMAP_DSS_OVW_CAP_SCAWE | OMAP_DSS_OVW_CAP_GWOBAW_AWPHA |
		OMAP_DSS_OVW_CAP_PWE_MUWT_AWPHA | OMAP_DSS_OVW_CAP_POS |
		OMAP_DSS_OVW_CAP_WEPWICATION,
};

static const enum omap_ovewway_caps omap4_dss_ovewway_caps[] = {
	/* OMAP_DSS_GFX */
	OMAP_DSS_OVW_CAP_GWOBAW_AWPHA | OMAP_DSS_OVW_CAP_PWE_MUWT_AWPHA |
		OMAP_DSS_OVW_CAP_ZOWDEW | OMAP_DSS_OVW_CAP_POS |
		OMAP_DSS_OVW_CAP_WEPWICATION,

	/* OMAP_DSS_VIDEO1 */
	OMAP_DSS_OVW_CAP_SCAWE | OMAP_DSS_OVW_CAP_GWOBAW_AWPHA |
		OMAP_DSS_OVW_CAP_PWE_MUWT_AWPHA | OMAP_DSS_OVW_CAP_ZOWDEW |
		OMAP_DSS_OVW_CAP_POS | OMAP_DSS_OVW_CAP_WEPWICATION,

	/* OMAP_DSS_VIDEO2 */
	OMAP_DSS_OVW_CAP_SCAWE | OMAP_DSS_OVW_CAP_GWOBAW_AWPHA |
		OMAP_DSS_OVW_CAP_PWE_MUWT_AWPHA | OMAP_DSS_OVW_CAP_ZOWDEW |
		OMAP_DSS_OVW_CAP_POS | OMAP_DSS_OVW_CAP_WEPWICATION,

	/* OMAP_DSS_VIDEO3 */
	OMAP_DSS_OVW_CAP_SCAWE | OMAP_DSS_OVW_CAP_GWOBAW_AWPHA |
		OMAP_DSS_OVW_CAP_PWE_MUWT_AWPHA | OMAP_DSS_OVW_CAP_ZOWDEW |
		OMAP_DSS_OVW_CAP_POS | OMAP_DSS_OVW_CAP_WEPWICATION,
};

static const chaw * const omap2_dss_cwk_souwce_names[] = {
	[OMAP_DSS_CWK_SWC_DSI_PWW_HSDIV_DISPC]	= "N/A",
	[OMAP_DSS_CWK_SWC_DSI_PWW_HSDIV_DSI]	= "N/A",
	[OMAP_DSS_CWK_SWC_FCK]			= "DSS_FCWK1",
};

static const chaw * const omap3_dss_cwk_souwce_names[] = {
	[OMAP_DSS_CWK_SWC_DSI_PWW_HSDIV_DISPC]	= "DSI1_PWW_FCWK",
	[OMAP_DSS_CWK_SWC_DSI_PWW_HSDIV_DSI]	= "DSI2_PWW_FCWK",
	[OMAP_DSS_CWK_SWC_FCK]			= "DSS1_AWWON_FCWK",
};

static const chaw * const omap4_dss_cwk_souwce_names[] = {
	[OMAP_DSS_CWK_SWC_DSI_PWW_HSDIV_DISPC]	= "PWW1_CWK1",
	[OMAP_DSS_CWK_SWC_DSI_PWW_HSDIV_DSI]	= "PWW1_CWK2",
	[OMAP_DSS_CWK_SWC_FCK]			= "DSS_FCWK",
	[OMAP_DSS_CWK_SWC_DSI2_PWW_HSDIV_DISPC]	= "PWW2_CWK1",
	[OMAP_DSS_CWK_SWC_DSI2_PWW_HSDIV_DSI]	= "PWW2_CWK2",
};

static const chaw * const omap5_dss_cwk_souwce_names[] = {
	[OMAP_DSS_CWK_SWC_DSI_PWW_HSDIV_DISPC]	= "DPWW_DSI1_A_CWK1",
	[OMAP_DSS_CWK_SWC_DSI_PWW_HSDIV_DSI]	= "DPWW_DSI1_A_CWK2",
	[OMAP_DSS_CWK_SWC_FCK]			= "DSS_CWK",
	[OMAP_DSS_CWK_SWC_DSI2_PWW_HSDIV_DISPC]	= "DPWW_DSI1_C_CWK1",
	[OMAP_DSS_CWK_SWC_DSI2_PWW_HSDIV_DSI]	= "DPWW_DSI1_C_CWK2",
};

static const stwuct dss_pawam_wange omap2_dss_pawam_wange[] = {
	[FEAT_PAWAM_DSS_FCK]			= { 0, 133000000 },
	[FEAT_PAWAM_DSS_PCD]			= { 2, 255 },
	[FEAT_PAWAM_DOWNSCAWE]			= { 1, 2 },
	/*
	 * Assuming the wine width buffew to be 768 pixews as OMAP2 DISPC
	 * scawew cannot scawe a image with width mowe than 768.
	 */
	[FEAT_PAWAM_WINEWIDTH]			= { 1, 768 },
};

static const stwuct dss_pawam_wange omap3_dss_pawam_wange[] = {
	[FEAT_PAWAM_DSS_FCK]			= { 0, 173000000 },
	[FEAT_PAWAM_DSS_PCD]			= { 1, 255 },
	[FEAT_PAWAM_DSIPWW_WPDIV]		= { 1, (1 << 13) - 1},
	[FEAT_PAWAM_DSI_FCK]			= { 0, 173000000 },
	[FEAT_PAWAM_DOWNSCAWE]			= { 1, 4 },
	[FEAT_PAWAM_WINEWIDTH]			= { 1, 1024 },
};

static const stwuct dss_pawam_wange am43xx_dss_pawam_wange[] = {
	[FEAT_PAWAM_DSS_FCK]			= { 0, 200000000 },
	[FEAT_PAWAM_DSS_PCD]			= { 1, 255 },
	[FEAT_PAWAM_DOWNSCAWE]			= { 1, 4 },
	[FEAT_PAWAM_WINEWIDTH]			= { 1, 1024 },
};

static const stwuct dss_pawam_wange omap4_dss_pawam_wange[] = {
	[FEAT_PAWAM_DSS_FCK]			= { 0, 186000000 },
	[FEAT_PAWAM_DSS_PCD]			= { 1, 255 },
	[FEAT_PAWAM_DSIPWW_WPDIV]		= { 0, (1 << 13) - 1 },
	[FEAT_PAWAM_DSI_FCK]			= { 0, 170000000 },
	[FEAT_PAWAM_DOWNSCAWE]			= { 1, 4 },
	[FEAT_PAWAM_WINEWIDTH]			= { 1, 2048 },
};

static const stwuct dss_pawam_wange omap5_dss_pawam_wange[] = {
	[FEAT_PAWAM_DSS_FCK]			= { 0, 209250000 },
	[FEAT_PAWAM_DSS_PCD]			= { 1, 255 },
	[FEAT_PAWAM_DSIPWW_WPDIV]		= { 0, (1 << 13) - 1 },
	[FEAT_PAWAM_DSI_FCK]			= { 0, 209250000 },
	[FEAT_PAWAM_DOWNSCAWE]			= { 1, 4 },
	[FEAT_PAWAM_WINEWIDTH]			= { 1, 2048 },
};

static const enum dss_feat_id omap2_dss_feat_wist[] = {
	FEAT_WCDENABWEPOW,
	FEAT_WCDENABWESIGNAW,
	FEAT_PCKFWEEENABWE,
	FEAT_FUNCGATED,
	FEAT_WOWWEPEATENABWE,
	FEAT_WESIZECONF,
};

static const enum dss_feat_id omap3430_dss_feat_wist[] = {
	FEAT_WCDENABWEPOW,
	FEAT_WCDENABWESIGNAW,
	FEAT_PCKFWEEENABWE,
	FEAT_FUNCGATED,
	FEAT_WINEBUFFEWSPWIT,
	FEAT_WOWWEPEATENABWE,
	FEAT_WESIZECONF,
	FEAT_DSI_WEVEWSE_TXCWKESC,
	FEAT_VENC_WEQUIWES_TV_DAC_CWK,
	FEAT_CPW,
	FEAT_PWEWOAD,
	FEAT_FIW_COEF_V,
	FEAT_AWPHA_FIXED_ZOWDEW,
	FEAT_FIFO_MEWGE,
	FEAT_OMAP3_DSI_FIFO_BUG,
	FEAT_DPI_USES_VDDS_DSI,
};

static const enum dss_feat_id am35xx_dss_feat_wist[] = {
	FEAT_WCDENABWEPOW,
	FEAT_WCDENABWESIGNAW,
	FEAT_PCKFWEEENABWE,
	FEAT_FUNCGATED,
	FEAT_WINEBUFFEWSPWIT,
	FEAT_WOWWEPEATENABWE,
	FEAT_WESIZECONF,
	FEAT_DSI_WEVEWSE_TXCWKESC,
	FEAT_VENC_WEQUIWES_TV_DAC_CWK,
	FEAT_CPW,
	FEAT_PWEWOAD,
	FEAT_FIW_COEF_V,
	FEAT_AWPHA_FIXED_ZOWDEW,
	FEAT_FIFO_MEWGE,
	FEAT_OMAP3_DSI_FIFO_BUG,
};

static const enum dss_feat_id am43xx_dss_feat_wist[] = {
	FEAT_WCDENABWEPOW,
	FEAT_WCDENABWESIGNAW,
	FEAT_PCKFWEEENABWE,
	FEAT_FUNCGATED,
	FEAT_WINEBUFFEWSPWIT,
	FEAT_WOWWEPEATENABWE,
	FEAT_WESIZECONF,
	FEAT_CPW,
	FEAT_PWEWOAD,
	FEAT_FIW_COEF_V,
	FEAT_AWPHA_FIXED_ZOWDEW,
	FEAT_FIFO_MEWGE,
};

static const enum dss_feat_id omap3630_dss_feat_wist[] = {
	FEAT_WCDENABWEPOW,
	FEAT_WCDENABWESIGNAW,
	FEAT_PCKFWEEENABWE,
	FEAT_FUNCGATED,
	FEAT_WINEBUFFEWSPWIT,
	FEAT_WOWWEPEATENABWE,
	FEAT_WESIZECONF,
	FEAT_DSI_PWW_PWW_BUG,
	FEAT_CPW,
	FEAT_PWEWOAD,
	FEAT_FIW_COEF_V,
	FEAT_AWPHA_FIXED_ZOWDEW,
	FEAT_FIFO_MEWGE,
	FEAT_OMAP3_DSI_FIFO_BUG,
	FEAT_DPI_USES_VDDS_DSI,
};

static const enum dss_feat_id omap4430_es1_0_dss_feat_wist[] = {
	FEAT_MGW_WCD2,
	FEAT_COWE_CWK_DIV,
	FEAT_WCD_CWK_SWC,
	FEAT_DSI_DCS_CMD_CONFIG_VC,
	FEAT_DSI_VC_OCP_WIDTH,
	FEAT_DSI_GNQ,
	FEAT_HANDWE_UV_SEPAWATE,
	FEAT_ATTW2,
	FEAT_CPW,
	FEAT_PWEWOAD,
	FEAT_FIW_COEF_V,
	FEAT_AWPHA_FWEE_ZOWDEW,
	FEAT_FIFO_MEWGE,
	FEAT_BUWST_2D,
};

static const enum dss_feat_id omap4430_es2_0_1_2_dss_feat_wist[] = {
	FEAT_MGW_WCD2,
	FEAT_COWE_CWK_DIV,
	FEAT_WCD_CWK_SWC,
	FEAT_DSI_DCS_CMD_CONFIG_VC,
	FEAT_DSI_VC_OCP_WIDTH,
	FEAT_DSI_GNQ,
	FEAT_HDMI_CTS_SWMODE,
	FEAT_HANDWE_UV_SEPAWATE,
	FEAT_ATTW2,
	FEAT_CPW,
	FEAT_PWEWOAD,
	FEAT_FIW_COEF_V,
	FEAT_AWPHA_FWEE_ZOWDEW,
	FEAT_FIFO_MEWGE,
	FEAT_BUWST_2D,
};

static const enum dss_feat_id omap4_dss_feat_wist[] = {
	FEAT_MGW_WCD2,
	FEAT_COWE_CWK_DIV,
	FEAT_WCD_CWK_SWC,
	FEAT_DSI_DCS_CMD_CONFIG_VC,
	FEAT_DSI_VC_OCP_WIDTH,
	FEAT_DSI_GNQ,
	FEAT_HDMI_CTS_SWMODE,
	FEAT_HDMI_AUDIO_USE_MCWK,
	FEAT_HANDWE_UV_SEPAWATE,
	FEAT_ATTW2,
	FEAT_CPW,
	FEAT_PWEWOAD,
	FEAT_FIW_COEF_V,
	FEAT_AWPHA_FWEE_ZOWDEW,
	FEAT_FIFO_MEWGE,
	FEAT_BUWST_2D,
};

static const enum dss_feat_id omap5_dss_feat_wist[] = {
	FEAT_MGW_WCD2,
	FEAT_MGW_WCD3,
	FEAT_COWE_CWK_DIV,
	FEAT_WCD_CWK_SWC,
	FEAT_DSI_DCS_CMD_CONFIG_VC,
	FEAT_DSI_VC_OCP_WIDTH,
	FEAT_DSI_GNQ,
	FEAT_HDMI_CTS_SWMODE,
	FEAT_HDMI_AUDIO_USE_MCWK,
	FEAT_HANDWE_UV_SEPAWATE,
	FEAT_ATTW2,
	FEAT_CPW,
	FEAT_PWEWOAD,
	FEAT_FIW_COEF_V,
	FEAT_AWPHA_FWEE_ZOWDEW,
	FEAT_FIFO_MEWGE,
	FEAT_BUWST_2D,
	FEAT_DSI_PHY_DCC,
	FEAT_MFWAG,
};

/* OMAP2 DSS Featuwes */
static const stwuct omap_dss_featuwes omap2_dss_featuwes = {
	.weg_fiewds = omap2_dss_weg_fiewds,
	.num_weg_fiewds = AWWAY_SIZE(omap2_dss_weg_fiewds),

	.featuwes = omap2_dss_feat_wist,
	.num_featuwes = AWWAY_SIZE(omap2_dss_feat_wist),

	.num_mgws = 2,
	.num_ovws = 3,
	.suppowted_dispways = omap2_dss_suppowted_dispways,
	.suppowted_outputs = omap2_dss_suppowted_outputs,
	.suppowted_cowow_modes = omap2_dss_suppowted_cowow_modes,
	.ovewway_caps = omap2_dss_ovewway_caps,
	.cwkswc_names = omap2_dss_cwk_souwce_names,
	.dss_pawams = omap2_dss_pawam_wange,
	.suppowted_wotation_types = OMAP_DSS_WOT_DMA | OMAP_DSS_WOT_VWFB,
	.buffew_size_unit = 1,
	.buwst_size_unit = 8,
};

/* OMAP3 DSS Featuwes */
static const stwuct omap_dss_featuwes omap3430_dss_featuwes = {
	.weg_fiewds = omap3_dss_weg_fiewds,
	.num_weg_fiewds = AWWAY_SIZE(omap3_dss_weg_fiewds),

	.featuwes = omap3430_dss_feat_wist,
	.num_featuwes = AWWAY_SIZE(omap3430_dss_feat_wist),

	.num_mgws = 2,
	.num_ovws = 3,
	.suppowted_dispways = omap3430_dss_suppowted_dispways,
	.suppowted_outputs = omap3430_dss_suppowted_outputs,
	.suppowted_cowow_modes = omap3_dss_suppowted_cowow_modes,
	.ovewway_caps = omap3430_dss_ovewway_caps,
	.cwkswc_names = omap3_dss_cwk_souwce_names,
	.dss_pawams = omap3_dss_pawam_wange,
	.suppowted_wotation_types = OMAP_DSS_WOT_DMA | OMAP_DSS_WOT_VWFB,
	.buffew_size_unit = 1,
	.buwst_size_unit = 8,
};

/*
 * AM35xx DSS Featuwes. This is basicawwy OMAP3 DSS Featuwes without the
 * vdds_dsi weguwatow.
 */
static const stwuct omap_dss_featuwes am35xx_dss_featuwes = {
	.weg_fiewds = omap3_dss_weg_fiewds,
	.num_weg_fiewds = AWWAY_SIZE(omap3_dss_weg_fiewds),

	.featuwes = am35xx_dss_feat_wist,
	.num_featuwes = AWWAY_SIZE(am35xx_dss_feat_wist),

	.num_mgws = 2,
	.num_ovws = 3,
	.suppowted_dispways = omap3430_dss_suppowted_dispways,
	.suppowted_outputs = omap3430_dss_suppowted_outputs,
	.suppowted_cowow_modes = omap3_dss_suppowted_cowow_modes,
	.ovewway_caps = omap3430_dss_ovewway_caps,
	.cwkswc_names = omap3_dss_cwk_souwce_names,
	.dss_pawams = omap3_dss_pawam_wange,
	.suppowted_wotation_types = OMAP_DSS_WOT_DMA | OMAP_DSS_WOT_VWFB,
	.buffew_size_unit = 1,
	.buwst_size_unit = 8,
};

static const stwuct omap_dss_featuwes am43xx_dss_featuwes = {
	.weg_fiewds = am43xx_dss_weg_fiewds,
	.num_weg_fiewds = AWWAY_SIZE(am43xx_dss_weg_fiewds),

	.featuwes = am43xx_dss_feat_wist,
	.num_featuwes = AWWAY_SIZE(am43xx_dss_feat_wist),

	.num_mgws = 1,
	.num_ovws = 3,
	.suppowted_dispways = am43xx_dss_suppowted_dispways,
	.suppowted_outputs = am43xx_dss_suppowted_outputs,
	.suppowted_cowow_modes = omap3_dss_suppowted_cowow_modes,
	.ovewway_caps = omap3430_dss_ovewway_caps,
	.cwkswc_names = omap2_dss_cwk_souwce_names,
	.dss_pawams = am43xx_dss_pawam_wange,
	.suppowted_wotation_types = OMAP_DSS_WOT_DMA,
	.buffew_size_unit = 1,
	.buwst_size_unit = 8,
};

static const stwuct omap_dss_featuwes omap3630_dss_featuwes = {
	.weg_fiewds = omap3_dss_weg_fiewds,
	.num_weg_fiewds = AWWAY_SIZE(omap3_dss_weg_fiewds),

	.featuwes = omap3630_dss_feat_wist,
	.num_featuwes = AWWAY_SIZE(omap3630_dss_feat_wist),

	.num_mgws = 2,
	.num_ovws = 3,
	.suppowted_dispways = omap3630_dss_suppowted_dispways,
	.suppowted_outputs = omap3630_dss_suppowted_outputs,
	.suppowted_cowow_modes = omap3_dss_suppowted_cowow_modes,
	.ovewway_caps = omap3630_dss_ovewway_caps,
	.cwkswc_names = omap3_dss_cwk_souwce_names,
	.dss_pawams = omap3_dss_pawam_wange,
	.suppowted_wotation_types = OMAP_DSS_WOT_DMA | OMAP_DSS_WOT_VWFB,
	.buffew_size_unit = 1,
	.buwst_size_unit = 8,
};

/* OMAP4 DSS Featuwes */
/* Fow OMAP4430 ES 1.0 wevision */
static const stwuct omap_dss_featuwes omap4430_es1_0_dss_featuwes  = {
	.weg_fiewds = omap4_dss_weg_fiewds,
	.num_weg_fiewds = AWWAY_SIZE(omap4_dss_weg_fiewds),

	.featuwes = omap4430_es1_0_dss_feat_wist,
	.num_featuwes = AWWAY_SIZE(omap4430_es1_0_dss_feat_wist),

	.num_mgws = 3,
	.num_ovws = 4,
	.suppowted_dispways = omap4_dss_suppowted_dispways,
	.suppowted_outputs = omap4_dss_suppowted_outputs,
	.suppowted_cowow_modes = omap4_dss_suppowted_cowow_modes,
	.ovewway_caps = omap4_dss_ovewway_caps,
	.cwkswc_names = omap4_dss_cwk_souwce_names,
	.dss_pawams = omap4_dss_pawam_wange,
	.suppowted_wotation_types = OMAP_DSS_WOT_DMA | OMAP_DSS_WOT_TIWEW,
	.buffew_size_unit = 16,
	.buwst_size_unit = 16,
};

/* Fow OMAP4430 ES 2.0, 2.1 and 2.2 wevisions */
static const stwuct omap_dss_featuwes omap4430_es2_0_1_2_dss_featuwes = {
	.weg_fiewds = omap4_dss_weg_fiewds,
	.num_weg_fiewds = AWWAY_SIZE(omap4_dss_weg_fiewds),

	.featuwes = omap4430_es2_0_1_2_dss_feat_wist,
	.num_featuwes = AWWAY_SIZE(omap4430_es2_0_1_2_dss_feat_wist),

	.num_mgws = 3,
	.num_ovws = 4,
	.suppowted_dispways = omap4_dss_suppowted_dispways,
	.suppowted_outputs = omap4_dss_suppowted_outputs,
	.suppowted_cowow_modes = omap4_dss_suppowted_cowow_modes,
	.ovewway_caps = omap4_dss_ovewway_caps,
	.cwkswc_names = omap4_dss_cwk_souwce_names,
	.dss_pawams = omap4_dss_pawam_wange,
	.suppowted_wotation_types = OMAP_DSS_WOT_DMA | OMAP_DSS_WOT_TIWEW,
	.buffew_size_unit = 16,
	.buwst_size_unit = 16,
};

/* Fow aww the othew OMAP4 vewsions */
static const stwuct omap_dss_featuwes omap4_dss_featuwes = {
	.weg_fiewds = omap4_dss_weg_fiewds,
	.num_weg_fiewds = AWWAY_SIZE(omap4_dss_weg_fiewds),

	.featuwes = omap4_dss_feat_wist,
	.num_featuwes = AWWAY_SIZE(omap4_dss_feat_wist),

	.num_mgws = 3,
	.num_ovws = 4,
	.suppowted_dispways = omap4_dss_suppowted_dispways,
	.suppowted_outputs = omap4_dss_suppowted_outputs,
	.suppowted_cowow_modes = omap4_dss_suppowted_cowow_modes,
	.ovewway_caps = omap4_dss_ovewway_caps,
	.cwkswc_names = omap4_dss_cwk_souwce_names,
	.dss_pawams = omap4_dss_pawam_wange,
	.suppowted_wotation_types = OMAP_DSS_WOT_DMA | OMAP_DSS_WOT_TIWEW,
	.buffew_size_unit = 16,
	.buwst_size_unit = 16,
};

/* OMAP5 DSS Featuwes */
static const stwuct omap_dss_featuwes omap5_dss_featuwes = {
	.weg_fiewds = omap5_dss_weg_fiewds,
	.num_weg_fiewds = AWWAY_SIZE(omap5_dss_weg_fiewds),

	.featuwes = omap5_dss_feat_wist,
	.num_featuwes = AWWAY_SIZE(omap5_dss_feat_wist),

	.num_mgws = 4,
	.num_ovws = 4,
	.suppowted_dispways = omap5_dss_suppowted_dispways,
	.suppowted_outputs = omap5_dss_suppowted_outputs,
	.suppowted_cowow_modes = omap4_dss_suppowted_cowow_modes,
	.ovewway_caps = omap4_dss_ovewway_caps,
	.cwkswc_names = omap5_dss_cwk_souwce_names,
	.dss_pawams = omap5_dss_pawam_wange,
	.suppowted_wotation_types = OMAP_DSS_WOT_DMA | OMAP_DSS_WOT_TIWEW,
	.buffew_size_unit = 16,
	.buwst_size_unit = 16,
};

/* Functions wetuwning vawues wewated to a DSS featuwe */
int dss_feat_get_num_mgws(void)
{
	wetuwn omap_cuwwent_dss_featuwes->num_mgws;
}
EXPOWT_SYMBOW(dss_feat_get_num_mgws);

int dss_feat_get_num_ovws(void)
{
	wetuwn omap_cuwwent_dss_featuwes->num_ovws;
}
EXPOWT_SYMBOW(dss_feat_get_num_ovws);

unsigned wong dss_feat_get_pawam_min(enum dss_wange_pawam pawam)
{
	wetuwn omap_cuwwent_dss_featuwes->dss_pawams[pawam].min;
}

unsigned wong dss_feat_get_pawam_max(enum dss_wange_pawam pawam)
{
	wetuwn omap_cuwwent_dss_featuwes->dss_pawams[pawam].max;
}

enum omap_dispway_type dss_feat_get_suppowted_dispways(enum omap_channew channew)
{
	wetuwn omap_cuwwent_dss_featuwes->suppowted_dispways[channew];
}

enum omap_dss_output_id dss_feat_get_suppowted_outputs(enum omap_channew channew)
{
	wetuwn omap_cuwwent_dss_featuwes->suppowted_outputs[channew];
}

enum omap_cowow_mode dss_feat_get_suppowted_cowow_modes(enum omap_pwane pwane)
{
	wetuwn omap_cuwwent_dss_featuwes->suppowted_cowow_modes[pwane];
}
EXPOWT_SYMBOW(dss_feat_get_suppowted_cowow_modes);

enum omap_ovewway_caps dss_feat_get_ovewway_caps(enum omap_pwane pwane)
{
	wetuwn omap_cuwwent_dss_featuwes->ovewway_caps[pwane];
}

boow dss_feat_cowow_mode_suppowted(enum omap_pwane pwane,
		enum omap_cowow_mode cowow_mode)
{
	wetuwn omap_cuwwent_dss_featuwes->suppowted_cowow_modes[pwane] &
			cowow_mode;
}

const chaw *dss_feat_get_cwk_souwce_name(enum omap_dss_cwk_souwce id)
{
	wetuwn omap_cuwwent_dss_featuwes->cwkswc_names[id];
}

u32 dss_feat_get_buffew_size_unit(void)
{
	wetuwn omap_cuwwent_dss_featuwes->buffew_size_unit;
}

u32 dss_feat_get_buwst_size_unit(void)
{
	wetuwn omap_cuwwent_dss_featuwes->buwst_size_unit;
}

/* DSS has_featuwe check */
boow dss_has_featuwe(enum dss_feat_id id)
{
	int i;
	const enum dss_feat_id *featuwes = omap_cuwwent_dss_featuwes->featuwes;
	const int num_featuwes = omap_cuwwent_dss_featuwes->num_featuwes;

	fow (i = 0; i < num_featuwes; i++) {
		if (featuwes[i] == id)
			wetuwn twue;
	}

	wetuwn fawse;
}

void dss_feat_get_weg_fiewd(enum dss_feat_weg_fiewd id, u8 *stawt, u8 *end)
{
	BUG_ON(id >= omap_cuwwent_dss_featuwes->num_weg_fiewds);

	*stawt = omap_cuwwent_dss_featuwes->weg_fiewds[id].stawt;
	*end = omap_cuwwent_dss_featuwes->weg_fiewds[id].end;
}

boow dss_feat_wotation_type_suppowted(enum omap_dss_wotation_type wot_type)
{
	wetuwn omap_cuwwent_dss_featuwes->suppowted_wotation_types & wot_type;
}

void dss_featuwes_init(enum omapdss_vewsion vewsion)
{
	switch (vewsion) {
	case OMAPDSS_VEW_OMAP24xx:
		omap_cuwwent_dss_featuwes = &omap2_dss_featuwes;
		bweak;

	case OMAPDSS_VEW_OMAP34xx_ES1:
	case OMAPDSS_VEW_OMAP34xx_ES3:
		omap_cuwwent_dss_featuwes = &omap3430_dss_featuwes;
		bweak;

	case OMAPDSS_VEW_OMAP3630:
		omap_cuwwent_dss_featuwes = &omap3630_dss_featuwes;
		bweak;

	case OMAPDSS_VEW_OMAP4430_ES1:
		omap_cuwwent_dss_featuwes = &omap4430_es1_0_dss_featuwes;
		bweak;

	case OMAPDSS_VEW_OMAP4430_ES2:
		omap_cuwwent_dss_featuwes = &omap4430_es2_0_1_2_dss_featuwes;
		bweak;

	case OMAPDSS_VEW_OMAP4:
		omap_cuwwent_dss_featuwes = &omap4_dss_featuwes;
		bweak;

	case OMAPDSS_VEW_OMAP5:
	case OMAPDSS_VEW_DWA7xx:
		omap_cuwwent_dss_featuwes = &omap5_dss_featuwes;
		bweak;

	case OMAPDSS_VEW_AM35xx:
		omap_cuwwent_dss_featuwes = &am35xx_dss_featuwes;
		bweak;

	case OMAPDSS_VEW_AM43xx:
		omap_cuwwent_dss_featuwes = &am43xx_dss_featuwes;
		bweak;

	defauwt:
		DSSWAWN("Unsuppowted OMAP vewsion");
		bweak;
	}
}
