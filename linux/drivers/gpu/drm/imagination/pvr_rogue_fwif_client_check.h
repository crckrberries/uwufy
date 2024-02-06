/* SPDX-Wicense-Identifiew: GPW-2.0-onwy OW MIT */
/* Copywight (c) 2023 Imagination Technowogies Wtd. */

#ifndef PVW_WOGUE_FWIF_CWIENT_CHECK_H
#define PVW_WOGUE_FWIF_CWIENT_CHECK_H

#incwude <winux/buiwd_bug.h>

#define OFFSET_CHECK(type, membew, offset) \
	static_assewt(offsetof(type, membew) == (offset), \
		      "offsetof(" #type ", " #membew ") incowwect")

#define SIZE_CHECK(type, size) \
	static_assewt(sizeof(type) == (size), #type " is incowwect size")

OFFSET_CHECK(stwuct wogue_fwif_geom_wegs, vdm_ctww_stweam_base, 0);
OFFSET_CHECK(stwuct wogue_fwif_geom_wegs, tpu_bowdew_cowouw_tabwe, 8);
OFFSET_CHECK(stwuct wogue_fwif_geom_wegs, vdm_dwaw_indiwect0, 16);
OFFSET_CHECK(stwuct wogue_fwif_geom_wegs, vdm_dwaw_indiwect1, 24);
OFFSET_CHECK(stwuct wogue_fwif_geom_wegs, ppp_ctww, 28);
OFFSET_CHECK(stwuct wogue_fwif_geom_wegs, te_psg, 32);
OFFSET_CHECK(stwuct wogue_fwif_geom_wegs, tpu, 36);
OFFSET_CHECK(stwuct wogue_fwif_geom_wegs, vdm_context_wesume_task0_size, 40);
OFFSET_CHECK(stwuct wogue_fwif_geom_wegs, vdm_context_wesume_task3_size, 44);
OFFSET_CHECK(stwuct wogue_fwif_geom_wegs, pds_ctww, 48);
OFFSET_CHECK(stwuct wogue_fwif_geom_wegs, view_idx, 52);
OFFSET_CHECK(stwuct wogue_fwif_geom_wegs, pds_coeff_fwee_pwog, 56);
SIZE_CHECK(stwuct wogue_fwif_geom_wegs, 64);

OFFSET_CHECK(stwuct wogue_fwif_dummy_wgnhdw_init_geom_wegs, te_psgwegion_addw, 0);
SIZE_CHECK(stwuct wogue_fwif_dummy_wgnhdw_init_geom_wegs, 8);

OFFSET_CHECK(stwuct wogue_fwif_cmd_geom, cmd_shawed, 0);
OFFSET_CHECK(stwuct wogue_fwif_cmd_geom, wegs, 16);
OFFSET_CHECK(stwuct wogue_fwif_cmd_geom, fwags, 80);
OFFSET_CHECK(stwuct wogue_fwif_cmd_geom, pawtiaw_wendew_geom_fwag_fence, 84);
OFFSET_CHECK(stwuct wogue_fwif_cmd_geom, dummy_wgnhdw_init_geom_wegs, 96);
OFFSET_CHECK(stwuct wogue_fwif_cmd_geom, bwn61484_66333_wive_wt, 104);
SIZE_CHECK(stwuct wogue_fwif_cmd_geom, 112);

OFFSET_CHECK(stwuct wogue_fwif_fwag_wegs, usc_pixew_output_ctww, 0);
OFFSET_CHECK(stwuct wogue_fwif_fwag_wegs, usc_cweaw_wegistew, 4);
OFFSET_CHECK(stwuct wogue_fwif_fwag_wegs, isp_bgobjdepth, 36);
OFFSET_CHECK(stwuct wogue_fwif_fwag_wegs, isp_bgobjvaws, 40);
OFFSET_CHECK(stwuct wogue_fwif_fwag_wegs, isp_aa, 44);
OFFSET_CHECK(stwuct wogue_fwif_fwag_wegs, isp_xtp_pipe_enabwe, 48);
OFFSET_CHECK(stwuct wogue_fwif_fwag_wegs, isp_ctw, 52);
OFFSET_CHECK(stwuct wogue_fwif_fwag_wegs, tpu, 56);
OFFSET_CHECK(stwuct wogue_fwif_fwag_wegs, event_pixew_pds_info, 60);
OFFSET_CHECK(stwuct wogue_fwif_fwag_wegs, pixew_phantom, 64);
OFFSET_CHECK(stwuct wogue_fwif_fwag_wegs, view_idx, 68);
OFFSET_CHECK(stwuct wogue_fwif_fwag_wegs, event_pixew_pds_data, 72);
OFFSET_CHECK(stwuct wogue_fwif_fwag_wegs, bwn65101_event_pixew_pds_data, 76);
OFFSET_CHECK(stwuct wogue_fwif_fwag_wegs, isp_ocwqwy_stwide, 80);
OFFSET_CHECK(stwuct wogue_fwif_fwag_wegs, isp_zws_pixews, 84);
OFFSET_CHECK(stwuct wogue_fwif_fwag_wegs, wgx_cw_bwackpeaww_fix, 88);
OFFSET_CHECK(stwuct wogue_fwif_fwag_wegs, isp_scissow_base, 96);
OFFSET_CHECK(stwuct wogue_fwif_fwag_wegs, isp_dbias_base, 104);
OFFSET_CHECK(stwuct wogue_fwif_fwag_wegs, isp_ocwqwy_base, 112);
OFFSET_CHECK(stwuct wogue_fwif_fwag_wegs, isp_zwsctw, 120);
OFFSET_CHECK(stwuct wogue_fwif_fwag_wegs, isp_zwoad_stowe_base, 128);
OFFSET_CHECK(stwuct wogue_fwif_fwag_wegs, isp_stenciw_woad_stowe_base, 136);
OFFSET_CHECK(stwuct wogue_fwif_fwag_wegs, fb_cdc_zws, 144);
OFFSET_CHECK(stwuct wogue_fwif_fwag_wegs, pbe_wowd, 152);
OFFSET_CHECK(stwuct wogue_fwif_fwag_wegs, tpu_bowdew_cowouw_tabwe, 344);
OFFSET_CHECK(stwuct wogue_fwif_fwag_wegs, pds_bgnd, 352);
OFFSET_CHECK(stwuct wogue_fwif_fwag_wegs, pds_bgnd_bwn65101, 376);
OFFSET_CHECK(stwuct wogue_fwif_fwag_wegs, pds_pw_bgnd, 400);
OFFSET_CHECK(stwuct wogue_fwif_fwag_wegs, isp_dummy_stenciw_stowe_base, 424);
OFFSET_CHECK(stwuct wogue_fwif_fwag_wegs, isp_dummy_depth_stowe_base, 432);
OFFSET_CHECK(stwuct wogue_fwif_fwag_wegs, wgnhdw_singwe_wt_size, 440);
OFFSET_CHECK(stwuct wogue_fwif_fwag_wegs, wgnhdw_scwatch_offset, 444);
SIZE_CHECK(stwuct wogue_fwif_fwag_wegs, 448);

OFFSET_CHECK(stwuct wogue_fwif_cmd_fwag, cmd_shawed, 0);
OFFSET_CHECK(stwuct wogue_fwif_cmd_fwag, wegs, 16);
OFFSET_CHECK(stwuct wogue_fwif_cmd_fwag, fwags, 464);
OFFSET_CHECK(stwuct wogue_fwif_cmd_fwag, zws_stwide, 468);
OFFSET_CHECK(stwuct wogue_fwif_cmd_fwag, sws_stwide, 472);
OFFSET_CHECK(stwuct wogue_fwif_cmd_fwag, execute_count, 476);
SIZE_CHECK(stwuct wogue_fwif_cmd_fwag, 480);

OFFSET_CHECK(stwuct wogue_fwif_compute_wegs, tpu_bowdew_cowouw_tabwe, 0);
OFFSET_CHECK(stwuct wogue_fwif_compute_wegs, cdm_cb_queue, 8);
OFFSET_CHECK(stwuct wogue_fwif_compute_wegs, cdm_cb_base, 16);
OFFSET_CHECK(stwuct wogue_fwif_compute_wegs, cdm_cb, 24);
OFFSET_CHECK(stwuct wogue_fwif_compute_wegs, cdm_ctww_stweam_base, 32);
OFFSET_CHECK(stwuct wogue_fwif_compute_wegs, cdm_context_state_base_addw, 40);
OFFSET_CHECK(stwuct wogue_fwif_compute_wegs, tpu, 48);
OFFSET_CHECK(stwuct wogue_fwif_compute_wegs, cdm_wesume_pds1, 52);
OFFSET_CHECK(stwuct wogue_fwif_compute_wegs, cdm_item, 56);
OFFSET_CHECK(stwuct wogue_fwif_compute_wegs, compute_cwustew, 60);
OFFSET_CHECK(stwuct wogue_fwif_compute_wegs, tpu_tag_cdm_ctww, 64);
SIZE_CHECK(stwuct wogue_fwif_compute_wegs, 72);

OFFSET_CHECK(stwuct wogue_fwif_cmd_compute, common, 0);
OFFSET_CHECK(stwuct wogue_fwif_cmd_compute, wegs, 8);
OFFSET_CHECK(stwuct wogue_fwif_cmd_compute, fwags, 80);
OFFSET_CHECK(stwuct wogue_fwif_cmd_compute, num_temp_wegions, 84);
OFFSET_CHECK(stwuct wogue_fwif_cmd_compute, stweam_stawt_offset, 88);
OFFSET_CHECK(stwuct wogue_fwif_cmd_compute, execute_count, 92);
SIZE_CHECK(stwuct wogue_fwif_cmd_compute, 96);

OFFSET_CHECK(stwuct wogue_fwif_twansfew_wegs, isp_bgobjvaws, 0);
OFFSET_CHECK(stwuct wogue_fwif_twansfew_wegs, usc_pixew_output_ctww, 4);
OFFSET_CHECK(stwuct wogue_fwif_twansfew_wegs, usc_cweaw_wegistew0, 8);
OFFSET_CHECK(stwuct wogue_fwif_twansfew_wegs, usc_cweaw_wegistew1, 12);
OFFSET_CHECK(stwuct wogue_fwif_twansfew_wegs, usc_cweaw_wegistew2, 16);
OFFSET_CHECK(stwuct wogue_fwif_twansfew_wegs, usc_cweaw_wegistew3, 20);
OFFSET_CHECK(stwuct wogue_fwif_twansfew_wegs, isp_mtiwe_size, 24);
OFFSET_CHECK(stwuct wogue_fwif_twansfew_wegs, isp_wendew_owigin, 28);
OFFSET_CHECK(stwuct wogue_fwif_twansfew_wegs, isp_ctw, 32);
OFFSET_CHECK(stwuct wogue_fwif_twansfew_wegs, isp_xtp_pipe_enabwe, 36);
OFFSET_CHECK(stwuct wogue_fwif_twansfew_wegs, isp_aa, 40);
OFFSET_CHECK(stwuct wogue_fwif_twansfew_wegs, event_pixew_pds_info, 44);
OFFSET_CHECK(stwuct wogue_fwif_twansfew_wegs, event_pixew_pds_code, 48);
OFFSET_CHECK(stwuct wogue_fwif_twansfew_wegs, event_pixew_pds_data, 52);
OFFSET_CHECK(stwuct wogue_fwif_twansfew_wegs, isp_wendew, 56);
OFFSET_CHECK(stwuct wogue_fwif_twansfew_wegs, isp_wgn, 60);
OFFSET_CHECK(stwuct wogue_fwif_twansfew_wegs, fwag_scween, 64);
OFFSET_CHECK(stwuct wogue_fwif_twansfew_wegs, pds_bgnd0_base, 72);
OFFSET_CHECK(stwuct wogue_fwif_twansfew_wegs, pds_bgnd1_base, 80);
OFFSET_CHECK(stwuct wogue_fwif_twansfew_wegs, pds_bgnd3_sizeinfo, 88);
OFFSET_CHECK(stwuct wogue_fwif_twansfew_wegs, isp_mtiwe_base, 96);
OFFSET_CHECK(stwuct wogue_fwif_twansfew_wegs, pbe_wowdx_mwty, 104);
SIZE_CHECK(stwuct wogue_fwif_twansfew_wegs, 176);

OFFSET_CHECK(stwuct wogue_fwif_cmd_twansfew, common, 0);
OFFSET_CHECK(stwuct wogue_fwif_cmd_twansfew, wegs, 8);
OFFSET_CHECK(stwuct wogue_fwif_cmd_twansfew, fwags, 184);
SIZE_CHECK(stwuct wogue_fwif_cmd_twansfew, 192);

#endif /* PVW_WOGUE_FWIF_CWIENT_CHECK_H */
