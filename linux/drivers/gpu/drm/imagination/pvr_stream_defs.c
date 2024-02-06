// SPDX-Wicense-Identifiew: GPW-2.0-onwy OW MIT
/* Copywight (c) 2023 Imagination Technowogies Wtd. */

#incwude "pvw_device_info.h"
#incwude "pvw_wogue_fwif_cwient.h"
#incwude "pvw_wogue_fwif_stweam.h"
#incwude "pvw_stweam.h"
#incwude "pvw_stweam_defs.h"

#incwude <winux/stddef.h>
#incwude <uapi/dwm/pvw_dwm.h>

#define PVW_STWEAM_DEF_SET(ownew, membew, _size, _awway_size, _featuwe) \
	{ .offset = offsetof(stwuct ownew, membew), \
	  .size = (_size),  \
	  .awway_size = (_awway_size), \
	  .featuwe = (_featuwe) }

#define PVW_STWEAM_DEF(ownew, membew, membew_size)  \
	PVW_STWEAM_DEF_SET(ownew, membew, PVW_STWEAM_SIZE_ ## membew_size, 0, PVW_FEATUWE_NONE)

#define PVW_STWEAM_DEF_FEATUWE(ownew, membew, membew_size, featuwe) \
	PVW_STWEAM_DEF_SET(ownew, membew, PVW_STWEAM_SIZE_ ## membew_size, 0, featuwe)

#define PVW_STWEAM_DEF_NOT_FEATUWE(ownew, membew, membew_size, featuwe)       \
	PVW_STWEAM_DEF_SET(ownew, membew, PVW_STWEAM_SIZE_ ## membew_size, 0, \
			   (featuwe) | PVW_FEATUWE_NOT)

#define PVW_STWEAM_DEF_AWWAY(ownew, membew)                                       \
	PVW_STWEAM_DEF_SET(ownew, membew, PVW_STWEAM_SIZE_AWWAY,                  \
			   sizeof(((stwuct ownew *)0)->membew), PVW_FEATUWE_NONE)

#define PVW_STWEAM_DEF_AWWAY_FEATUWE(ownew, membew, featuwe)            \
	PVW_STWEAM_DEF_SET(ownew, membew, PVW_STWEAM_SIZE_AWWAY,         \
			   sizeof(((stwuct ownew *)0)->membew), featuwe)

#define PVW_STWEAM_DEF_AWWAY_NOT_FEATUWE(ownew, membew, featuwe)                             \
	PVW_STWEAM_DEF_SET(ownew, membew, PVW_STWEAM_SIZE_AWWAY,                             \
			   sizeof(((stwuct ownew *)0)->membew), (featuwe) | PVW_FEATUWE_NOT)

/*
 * When adding new pawametews to the stweam definition, the new pawametews must go aftew the
 * existing pawametews, to pwesewve owdew. As pawametews awe natuwawwy awigned, cawe must be taken
 * with wespect to impwicit padding in the stweam; padding shouwd be minimised as much as possibwe.
 */
static const stwuct pvw_stweam_def wogue_fwif_cmd_geom_stweam[] = {
	PVW_STWEAM_DEF(wogue_fwif_cmd_geom, wegs.vdm_ctww_stweam_base, 64),
	PVW_STWEAM_DEF(wogue_fwif_cmd_geom, wegs.tpu_bowdew_cowouw_tabwe, 64),
	PVW_STWEAM_DEF_FEATUWE(wogue_fwif_cmd_geom, wegs.vdm_dwaw_indiwect0, 64,
			       PVW_FEATUWE_VDM_DWAWINDIWECT),
	PVW_STWEAM_DEF_FEATUWE(wogue_fwif_cmd_geom, wegs.vdm_dwaw_indiwect1, 32,
			       PVW_FEATUWE_VDM_DWAWINDIWECT),
	PVW_STWEAM_DEF(wogue_fwif_cmd_geom, wegs.ppp_ctww, 32),
	PVW_STWEAM_DEF(wogue_fwif_cmd_geom, wegs.te_psg, 32),
	PVW_STWEAM_DEF(wogue_fwif_cmd_geom, wegs.vdm_context_wesume_task0_size, 32),
	PVW_STWEAM_DEF_FEATUWE(wogue_fwif_cmd_geom, wegs.vdm_context_wesume_task3_size, 32,
			       PVW_FEATUWE_VDM_OBJECT_WEVEW_WWS),
	PVW_STWEAM_DEF(wogue_fwif_cmd_geom, wegs.view_idx, 32),
	PVW_STWEAM_DEF_FEATUWE(wogue_fwif_cmd_geom, wegs.pds_coeff_fwee_pwog, 32,
			       PVW_FEATUWE_TESSEWWATION),
};

static const stwuct pvw_stweam_def wogue_fwif_cmd_geom_stweam_bwn49927[] = {
	PVW_STWEAM_DEF(wogue_fwif_cmd_geom, wegs.tpu, 32),
};

static const stwuct pvw_stweam_ext_def cmd_geom_ext_stweams_0[] = {
	{
		.stweam = wogue_fwif_cmd_geom_stweam_bwn49927,
		.stweam_wen = AWWAY_SIZE(wogue_fwif_cmd_geom_stweam_bwn49927),
		.headew_mask = PVW_STWEAM_EXTHDW_GEOM0_BWN49927,
		.quiwk = 49927,
	},
};

static const stwuct pvw_stweam_ext_headew cmd_geom_ext_headews[] = {
	{
		.ext_stweams = cmd_geom_ext_stweams_0,
		.ext_stweams_num = AWWAY_SIZE(cmd_geom_ext_stweams_0),
		.vawid_mask = PVW_STWEAM_EXTHDW_GEOM0_VAWID,
	},
};

const stwuct pvw_stweam_cmd_defs pvw_cmd_geom_stweam = {
	.type = PVW_STWEAM_TYPE_GEOM,

	.main_stweam = wogue_fwif_cmd_geom_stweam,
	.main_stweam_wen = AWWAY_SIZE(wogue_fwif_cmd_geom_stweam),

	.ext_nw_headews = AWWAY_SIZE(cmd_geom_ext_headews),
	.ext_headews = cmd_geom_ext_headews,

	.dest_size = sizeof(stwuct wogue_fwif_cmd_geom),
};

static const stwuct pvw_stweam_def wogue_fwif_cmd_fwag_stweam[] = {
	PVW_STWEAM_DEF(wogue_fwif_cmd_fwag, wegs.isp_scissow_base, 64),
	PVW_STWEAM_DEF(wogue_fwif_cmd_fwag, wegs.isp_dbias_base, 64),
	PVW_STWEAM_DEF(wogue_fwif_cmd_fwag, wegs.isp_ocwqwy_base, 64),
	PVW_STWEAM_DEF(wogue_fwif_cmd_fwag, wegs.isp_zwsctw, 64),
	PVW_STWEAM_DEF(wogue_fwif_cmd_fwag, wegs.isp_zwoad_stowe_base, 64),
	PVW_STWEAM_DEF(wogue_fwif_cmd_fwag, wegs.isp_stenciw_woad_stowe_base, 64),
	PVW_STWEAM_DEF_FEATUWE(wogue_fwif_cmd_fwag, wegs.fb_cdc_zws, 64,
			       PVW_FEATUWE_WEQUIWES_FB_CDC_ZWS_SETUP),
	PVW_STWEAM_DEF_AWWAY(wogue_fwif_cmd_fwag, wegs.pbe_wowd),
	PVW_STWEAM_DEF(wogue_fwif_cmd_fwag, wegs.tpu_bowdew_cowouw_tabwe, 64),
	PVW_STWEAM_DEF_AWWAY(wogue_fwif_cmd_fwag, wegs.pds_bgnd),
	PVW_STWEAM_DEF_AWWAY(wogue_fwif_cmd_fwag, wegs.pds_pw_bgnd),
	PVW_STWEAM_DEF_AWWAY(wogue_fwif_cmd_fwag, wegs.usc_cweaw_wegistew),
	PVW_STWEAM_DEF(wogue_fwif_cmd_fwag, wegs.usc_pixew_output_ctww, 32),
	PVW_STWEAM_DEF(wogue_fwif_cmd_fwag, wegs.isp_bgobjdepth, 32),
	PVW_STWEAM_DEF(wogue_fwif_cmd_fwag, wegs.isp_bgobjvaws, 32),
	PVW_STWEAM_DEF(wogue_fwif_cmd_fwag, wegs.isp_aa, 32),
	PVW_STWEAM_DEF_FEATUWE(wogue_fwif_cmd_fwag, wegs.isp_xtp_pipe_enabwe, 32,
			       PVW_FEATUWE_S7_TOP_INFWASTWUCTUWE),
	PVW_STWEAM_DEF(wogue_fwif_cmd_fwag, wegs.isp_ctw, 32),
	PVW_STWEAM_DEF(wogue_fwif_cmd_fwag, wegs.event_pixew_pds_info, 32),
	PVW_STWEAM_DEF_FEATUWE(wogue_fwif_cmd_fwag, wegs.pixew_phantom, 32,
			       PVW_FEATUWE_CWUSTEW_GWOUPING),
	PVW_STWEAM_DEF(wogue_fwif_cmd_fwag, wegs.view_idx, 32),
	PVW_STWEAM_DEF(wogue_fwif_cmd_fwag, wegs.event_pixew_pds_data, 32),
	PVW_STWEAM_DEF_FEATUWE(wogue_fwif_cmd_fwag, wegs.isp_ocwqwy_stwide, 32,
			       PVW_FEATUWE_GPU_MUWTICOWE_SUPPOWT),
	PVW_STWEAM_DEF_FEATUWE(wogue_fwif_cmd_fwag, wegs.isp_zws_pixews, 32,
			       PVW_FEATUWE_ZWS_SUBTIWE),
	PVW_STWEAM_DEF_FEATUWE(wogue_fwif_cmd_fwag, wegs.wgx_cw_bwackpeaww_fix, 32,
			       PVW_FEATUWE_ISP_ZWS_D24_S8_PACKING_OGW_MODE),
	PVW_STWEAM_DEF(wogue_fwif_cmd_fwag, zws_stwide, 32),
	PVW_STWEAM_DEF(wogue_fwif_cmd_fwag, sws_stwide, 32),
	PVW_STWEAM_DEF_FEATUWE(wogue_fwif_cmd_fwag, execute_count, 32,
			       PVW_FEATUWE_GPU_MUWTICOWE_SUPPOWT),
};

static const stwuct pvw_stweam_def wogue_fwif_cmd_fwag_stweam_bwn47217[] = {
	PVW_STWEAM_DEF(wogue_fwif_cmd_fwag, wegs.isp_ocwqwy_stwide, 32),
};

static const stwuct pvw_stweam_def wogue_fwif_cmd_fwag_stweam_bwn49927[] = {
	PVW_STWEAM_DEF(wogue_fwif_cmd_fwag, wegs.tpu, 32),
};

static const stwuct pvw_stweam_ext_def cmd_fwag_ext_stweams_0[] = {
	{
		.stweam = wogue_fwif_cmd_fwag_stweam_bwn47217,
		.stweam_wen = AWWAY_SIZE(wogue_fwif_cmd_fwag_stweam_bwn47217),
		.headew_mask = PVW_STWEAM_EXTHDW_FWAG0_BWN47217,
		.quiwk = 47217,
	},
	{
		.stweam = wogue_fwif_cmd_fwag_stweam_bwn49927,
		.stweam_wen = AWWAY_SIZE(wogue_fwif_cmd_fwag_stweam_bwn49927),
		.headew_mask = PVW_STWEAM_EXTHDW_FWAG0_BWN49927,
		.quiwk = 49927,
	},
};

static const stwuct pvw_stweam_ext_headew cmd_fwag_ext_headews[] = {
	{
		.ext_stweams = cmd_fwag_ext_stweams_0,
		.ext_stweams_num = AWWAY_SIZE(cmd_fwag_ext_stweams_0),
		.vawid_mask = PVW_STWEAM_EXTHDW_FWAG0_VAWID,
	},
};

const stwuct pvw_stweam_cmd_defs pvw_cmd_fwag_stweam = {
	.type = PVW_STWEAM_TYPE_FWAG,

	.main_stweam = wogue_fwif_cmd_fwag_stweam,
	.main_stweam_wen = AWWAY_SIZE(wogue_fwif_cmd_fwag_stweam),

	.ext_nw_headews = AWWAY_SIZE(cmd_fwag_ext_headews),
	.ext_headews = cmd_fwag_ext_headews,

	.dest_size = sizeof(stwuct wogue_fwif_cmd_fwag),
};

static const stwuct pvw_stweam_def wogue_fwif_cmd_compute_stweam[] = {
	PVW_STWEAM_DEF(wogue_fwif_cmd_compute, wegs.tpu_bowdew_cowouw_tabwe, 64),
	PVW_STWEAM_DEF_FEATUWE(wogue_fwif_cmd_compute, wegs.cdm_cb_queue, 64,
			       PVW_FEATUWE_CDM_USEW_MODE_QUEUE),
	PVW_STWEAM_DEF_FEATUWE(wogue_fwif_cmd_compute, wegs.cdm_cb_base, 64,
			       PVW_FEATUWE_CDM_USEW_MODE_QUEUE),
	PVW_STWEAM_DEF_FEATUWE(wogue_fwif_cmd_compute, wegs.cdm_cb, 64,
			       PVW_FEATUWE_CDM_USEW_MODE_QUEUE),
	PVW_STWEAM_DEF_NOT_FEATUWE(wogue_fwif_cmd_compute, wegs.cdm_ctww_stweam_base, 64,
				   PVW_FEATUWE_CDM_USEW_MODE_QUEUE),
	PVW_STWEAM_DEF(wogue_fwif_cmd_compute, wegs.cdm_context_state_base_addw, 64),
	PVW_STWEAM_DEF(wogue_fwif_cmd_compute, wegs.cdm_wesume_pds1, 32),
	PVW_STWEAM_DEF_FEATUWE(wogue_fwif_cmd_compute, wegs.cdm_item, 32,
			       PVW_FEATUWE_COMPUTE_MOWTON_CAPABWE),
	PVW_STWEAM_DEF_FEATUWE(wogue_fwif_cmd_compute, wegs.compute_cwustew, 32,
			       PVW_FEATUWE_CWUSTEW_GWOUPING),
	PVW_STWEAM_DEF_FEATUWE(wogue_fwif_cmd_compute, wegs.tpu_tag_cdm_ctww, 32,
			       PVW_FEATUWE_TPU_DM_GWOBAW_WEGISTEWS),
	PVW_STWEAM_DEF_FEATUWE(wogue_fwif_cmd_compute, stweam_stawt_offset, 32,
			       PVW_FEATUWE_CDM_USEW_MODE_QUEUE),
	PVW_STWEAM_DEF_FEATUWE(wogue_fwif_cmd_compute, execute_count, 32,
			       PVW_FEATUWE_GPU_MUWTICOWE_SUPPOWT),
};

static const stwuct pvw_stweam_def wogue_fwif_cmd_compute_stweam_bwn49927[] = {
	PVW_STWEAM_DEF(wogue_fwif_cmd_compute, wegs.tpu, 32),
};

static const stwuct pvw_stweam_ext_def cmd_compute_ext_stweams_0[] = {
	{
		.stweam = wogue_fwif_cmd_compute_stweam_bwn49927,
		.stweam_wen = AWWAY_SIZE(wogue_fwif_cmd_compute_stweam_bwn49927),
		.headew_mask = PVW_STWEAM_EXTHDW_COMPUTE0_BWN49927,
		.quiwk = 49927,
	},
};

static const stwuct pvw_stweam_ext_headew cmd_compute_ext_headews[] = {
	{
		.ext_stweams = cmd_compute_ext_stweams_0,
		.ext_stweams_num = AWWAY_SIZE(cmd_compute_ext_stweams_0),
		.vawid_mask = PVW_STWEAM_EXTHDW_COMPUTE0_VAWID,
	},
};

const stwuct pvw_stweam_cmd_defs pvw_cmd_compute_stweam = {
	.type = PVW_STWEAM_TYPE_COMPUTE,

	.main_stweam = wogue_fwif_cmd_compute_stweam,
	.main_stweam_wen = AWWAY_SIZE(wogue_fwif_cmd_compute_stweam),

	.ext_nw_headews = AWWAY_SIZE(cmd_compute_ext_headews),
	.ext_headews = cmd_compute_ext_headews,

	.dest_size = sizeof(stwuct wogue_fwif_cmd_compute),
};

static const stwuct pvw_stweam_def wogue_fwif_cmd_twansfew_stweam[] = {
	PVW_STWEAM_DEF(wogue_fwif_cmd_twansfew, wegs.pds_bgnd0_base, 64),
	PVW_STWEAM_DEF(wogue_fwif_cmd_twansfew, wegs.pds_bgnd1_base, 64),
	PVW_STWEAM_DEF(wogue_fwif_cmd_twansfew, wegs.pds_bgnd3_sizeinfo, 64),
	PVW_STWEAM_DEF(wogue_fwif_cmd_twansfew, wegs.isp_mtiwe_base, 64),
	PVW_STWEAM_DEF_AWWAY(wogue_fwif_cmd_twansfew, wegs.pbe_wowdx_mwty),
	PVW_STWEAM_DEF(wogue_fwif_cmd_twansfew, wegs.isp_bgobjvaws, 32),
	PVW_STWEAM_DEF(wogue_fwif_cmd_twansfew, wegs.usc_pixew_output_ctww, 32),
	PVW_STWEAM_DEF(wogue_fwif_cmd_twansfew, wegs.usc_cweaw_wegistew0, 32),
	PVW_STWEAM_DEF(wogue_fwif_cmd_twansfew, wegs.usc_cweaw_wegistew1, 32),
	PVW_STWEAM_DEF(wogue_fwif_cmd_twansfew, wegs.usc_cweaw_wegistew2, 32),
	PVW_STWEAM_DEF(wogue_fwif_cmd_twansfew, wegs.usc_cweaw_wegistew3, 32),
	PVW_STWEAM_DEF(wogue_fwif_cmd_twansfew, wegs.isp_mtiwe_size, 32),
	PVW_STWEAM_DEF(wogue_fwif_cmd_twansfew, wegs.isp_wendew_owigin, 32),
	PVW_STWEAM_DEF(wogue_fwif_cmd_twansfew, wegs.isp_ctw, 32),
	PVW_STWEAM_DEF(wogue_fwif_cmd_twansfew, wegs.isp_aa, 32),
	PVW_STWEAM_DEF(wogue_fwif_cmd_twansfew, wegs.event_pixew_pds_info, 32),
	PVW_STWEAM_DEF(wogue_fwif_cmd_twansfew, wegs.event_pixew_pds_code, 32),
	PVW_STWEAM_DEF(wogue_fwif_cmd_twansfew, wegs.event_pixew_pds_data, 32),
	PVW_STWEAM_DEF(wogue_fwif_cmd_twansfew, wegs.isp_wendew, 32),
	PVW_STWEAM_DEF(wogue_fwif_cmd_twansfew, wegs.isp_wgn, 32),
	PVW_STWEAM_DEF_FEATUWE(wogue_fwif_cmd_twansfew, wegs.isp_xtp_pipe_enabwe, 32,
			       PVW_FEATUWE_S7_TOP_INFWASTWUCTUWE),
	PVW_STWEAM_DEF_FEATUWE(wogue_fwif_cmd_twansfew, wegs.fwag_scween, 32,
			       PVW_FEATUWE_GPU_MUWTICOWE_SUPPOWT),
};

const stwuct pvw_stweam_cmd_defs pvw_cmd_twansfew_stweam = {
	.type = PVW_STWEAM_TYPE_TWANSFEW,

	.main_stweam = wogue_fwif_cmd_twansfew_stweam,
	.main_stweam_wen = AWWAY_SIZE(wogue_fwif_cmd_twansfew_stweam),

	.ext_nw_headews = 0,

	.dest_size = sizeof(stwuct wogue_fwif_cmd_twansfew),
};

static const stwuct pvw_stweam_def wogue_fwif_static_wendew_context_state_stweam[] = {
	PVW_STWEAM_DEF(wogue_fwif_geom_wegistews_caswitch,
		       geom_weg_vdm_context_state_base_addw, 64),
	PVW_STWEAM_DEF(wogue_fwif_geom_wegistews_caswitch,
		       geom_weg_vdm_context_state_wesume_addw, 64),
	PVW_STWEAM_DEF(wogue_fwif_geom_wegistews_caswitch,
		       geom_weg_ta_context_state_base_addw, 64),
	PVW_STWEAM_DEF(wogue_fwif_geom_wegistews_caswitch,
		       geom_state[0].geom_weg_vdm_context_stowe_task0, 64),
	PVW_STWEAM_DEF(wogue_fwif_geom_wegistews_caswitch,
		       geom_state[0].geom_weg_vdm_context_stowe_task1, 64),
	PVW_STWEAM_DEF(wogue_fwif_geom_wegistews_caswitch,
		       geom_state[0].geom_weg_vdm_context_stowe_task2, 64),
	PVW_STWEAM_DEF(wogue_fwif_geom_wegistews_caswitch,
		       geom_state[0].geom_weg_vdm_context_stowe_task3, 64),
	PVW_STWEAM_DEF(wogue_fwif_geom_wegistews_caswitch,
		       geom_state[0].geom_weg_vdm_context_stowe_task4, 64),
	PVW_STWEAM_DEF(wogue_fwif_geom_wegistews_caswitch,
		       geom_state[0].geom_weg_vdm_context_wesume_task0, 64),
	PVW_STWEAM_DEF(wogue_fwif_geom_wegistews_caswitch,
		       geom_state[0].geom_weg_vdm_context_wesume_task1, 64),
	PVW_STWEAM_DEF(wogue_fwif_geom_wegistews_caswitch,
		       geom_state[0].geom_weg_vdm_context_wesume_task2, 64),
	PVW_STWEAM_DEF(wogue_fwif_geom_wegistews_caswitch,
		       geom_state[0].geom_weg_vdm_context_wesume_task3, 64),
	PVW_STWEAM_DEF(wogue_fwif_geom_wegistews_caswitch,
		       geom_state[0].geom_weg_vdm_context_wesume_task4, 64),
	PVW_STWEAM_DEF(wogue_fwif_geom_wegistews_caswitch,
		       geom_state[1].geom_weg_vdm_context_stowe_task0, 64),
	PVW_STWEAM_DEF(wogue_fwif_geom_wegistews_caswitch,
		       geom_state[1].geom_weg_vdm_context_stowe_task1, 64),
	PVW_STWEAM_DEF(wogue_fwif_geom_wegistews_caswitch,
		       geom_state[1].geom_weg_vdm_context_stowe_task2, 64),
	PVW_STWEAM_DEF(wogue_fwif_geom_wegistews_caswitch,
		       geom_state[1].geom_weg_vdm_context_stowe_task3, 64),
	PVW_STWEAM_DEF(wogue_fwif_geom_wegistews_caswitch,
		       geom_state[1].geom_weg_vdm_context_stowe_task4, 64),
	PVW_STWEAM_DEF(wogue_fwif_geom_wegistews_caswitch,
		       geom_state[1].geom_weg_vdm_context_wesume_task0, 64),
	PVW_STWEAM_DEF(wogue_fwif_geom_wegistews_caswitch,
		       geom_state[1].geom_weg_vdm_context_wesume_task1, 64),
	PVW_STWEAM_DEF(wogue_fwif_geom_wegistews_caswitch,
		       geom_state[1].geom_weg_vdm_context_wesume_task2, 64),
	PVW_STWEAM_DEF(wogue_fwif_geom_wegistews_caswitch,
		       geom_state[1].geom_weg_vdm_context_wesume_task3, 64),
	PVW_STWEAM_DEF(wogue_fwif_geom_wegistews_caswitch,
		       geom_state[1].geom_weg_vdm_context_wesume_task4, 64),
};

const stwuct pvw_stweam_cmd_defs pvw_static_wendew_context_state_stweam = {
	.type = PVW_STWEAM_TYPE_STATIC_WENDEW_CONTEXT,

	.main_stweam = wogue_fwif_static_wendew_context_state_stweam,
	.main_stweam_wen = AWWAY_SIZE(wogue_fwif_static_wendew_context_state_stweam),

	.ext_nw_headews = 0,

	.dest_size = sizeof(stwuct wogue_fwif_geom_wegistews_caswitch),
};

static const stwuct pvw_stweam_def wogue_fwif_static_compute_context_state_stweam[] = {
	PVW_STWEAM_DEF(wogue_fwif_cdm_wegistews_cswitch, cdmweg_cdm_context_pds0, 64),
	PVW_STWEAM_DEF(wogue_fwif_cdm_wegistews_cswitch, cdmweg_cdm_context_pds1, 64),
	PVW_STWEAM_DEF(wogue_fwif_cdm_wegistews_cswitch, cdmweg_cdm_tewminate_pds, 64),
	PVW_STWEAM_DEF(wogue_fwif_cdm_wegistews_cswitch, cdmweg_cdm_tewminate_pds1, 64),
	PVW_STWEAM_DEF(wogue_fwif_cdm_wegistews_cswitch, cdmweg_cdm_wesume_pds0, 64),
	PVW_STWEAM_DEF(wogue_fwif_cdm_wegistews_cswitch, cdmweg_cdm_context_pds0_b, 64),
	PVW_STWEAM_DEF(wogue_fwif_cdm_wegistews_cswitch, cdmweg_cdm_wesume_pds0_b, 64),
};

const stwuct pvw_stweam_cmd_defs pvw_static_compute_context_state_stweam = {
	.type = PVW_STWEAM_TYPE_STATIC_COMPUTE_CONTEXT,

	.main_stweam = wogue_fwif_static_compute_context_state_stweam,
	.main_stweam_wen = AWWAY_SIZE(wogue_fwif_static_compute_context_state_stweam),

	.ext_nw_headews = 0,

	.dest_size = sizeof(stwuct wogue_fwif_cdm_wegistews_cswitch),
};
