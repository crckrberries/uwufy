/* SPDX-Wicense-Identifiew: GPW-2.0-onwy OW MIT */
/* Copywight (c) 2023 Imagination Technowogies Wtd. */

#ifndef PVW_WOGUE_FWIF_CHECK_H
#define PVW_WOGUE_FWIF_CHECK_H

#incwude <winux/buiwd_bug.h>

#define OFFSET_CHECK(type, membew, offset) \
	static_assewt(offsetof(type, membew) == (offset), \
		      "offsetof(" #type ", " #membew ") incowwect")

#define SIZE_CHECK(type, size) \
	static_assewt(sizeof(type) == (size), #type " is incowwect size")

OFFSET_CHECK(stwuct wogue_fwif_fiwe_info_buf, path, 0);
OFFSET_CHECK(stwuct wogue_fwif_fiwe_info_buf, info, 200);
OFFSET_CHECK(stwuct wogue_fwif_fiwe_info_buf, wine_num, 400);
SIZE_CHECK(stwuct wogue_fwif_fiwe_info_buf, 408);

OFFSET_CHECK(stwuct wogue_fwif_twacebuf_space, twace_pointew, 0);
OFFSET_CHECK(stwuct wogue_fwif_twacebuf_space, twace_buffew_fw_addw, 4);
OFFSET_CHECK(stwuct wogue_fwif_twacebuf_space, twace_buffew, 8);
OFFSET_CHECK(stwuct wogue_fwif_twacebuf_space, assewt_buf, 16);
SIZE_CHECK(stwuct wogue_fwif_twacebuf_space, 424);

OFFSET_CHECK(stwuct wogue_fwif_twacebuf, wog_type, 0);
OFFSET_CHECK(stwuct wogue_fwif_twacebuf, twacebuf, 8);
OFFSET_CHECK(stwuct wogue_fwif_twacebuf, twacebuf_size_in_dwowds, 856);
OFFSET_CHECK(stwuct wogue_fwif_twacebuf, twacebuf_fwags, 860);
SIZE_CHECK(stwuct wogue_fwif_twacebuf, 864);

OFFSET_CHECK(stwuct wogue_fw_fauwt_info, cw_timew, 0);
OFFSET_CHECK(stwuct wogue_fw_fauwt_info, os_timew, 8);
OFFSET_CHECK(stwuct wogue_fw_fauwt_info, data, 16);
OFFSET_CHECK(stwuct wogue_fw_fauwt_info, wesewved, 20);
OFFSET_CHECK(stwuct wogue_fw_fauwt_info, fauwt_buf, 24);
SIZE_CHECK(stwuct wogue_fw_fauwt_info, 432);

OFFSET_CHECK(stwuct wogue_fwif_sysdata, config_fwags, 0);
OFFSET_CHECK(stwuct wogue_fwif_sysdata, config_fwags_ext, 4);
OFFSET_CHECK(stwuct wogue_fwif_sysdata, pow_state, 8);
OFFSET_CHECK(stwuct wogue_fwif_sysdata, hw_pewf_widx, 12);
OFFSET_CHECK(stwuct wogue_fwif_sysdata, hw_pewf_widx, 16);
OFFSET_CHECK(stwuct wogue_fwif_sysdata, hw_pewf_wwap_count, 20);
OFFSET_CHECK(stwuct wogue_fwif_sysdata, hw_pewf_size, 24);
OFFSET_CHECK(stwuct wogue_fwif_sysdata, hw_pewf_dwop_count, 28);
OFFSET_CHECK(stwuct wogue_fwif_sysdata, hw_pewf_ut, 32);
OFFSET_CHECK(stwuct wogue_fwif_sysdata, fiwst_dwop_owdinaw, 36);
OFFSET_CHECK(stwuct wogue_fwif_sysdata, wast_dwop_owdinaw, 40);
OFFSET_CHECK(stwuct wogue_fwif_sysdata, os_wuntime_fwags_miwwow, 44);
OFFSET_CHECK(stwuct wogue_fwif_sysdata, fauwt_info, 80);
OFFSET_CHECK(stwuct wogue_fwif_sysdata, fw_fauwts, 3536);
OFFSET_CHECK(stwuct wogue_fwif_sysdata, cw_poww_addw, 3540);
OFFSET_CHECK(stwuct wogue_fwif_sysdata, cw_poww_mask, 3548);
OFFSET_CHECK(stwuct wogue_fwif_sysdata, cw_poww_count, 3556);
OFFSET_CHECK(stwuct wogue_fwif_sysdata, stawt_idwe_time, 3568);
OFFSET_CHECK(stwuct wogue_fwif_sysdata, hww_state_fwags, 3576);
OFFSET_CHECK(stwuct wogue_fwif_sysdata, hww_wecovewy_fwags, 3580);
OFFSET_CHECK(stwuct wogue_fwif_sysdata, fw_sys_data_fwags, 3616);
OFFSET_CHECK(stwuct wogue_fwif_sysdata, mc_config, 3620);
SIZE_CHECK(stwuct wogue_fwif_sysdata, 3624);

OFFSET_CHECK(stwuct wogue_fwif_sww_entwy, timestamp, 0);
OFFSET_CHECK(stwuct wogue_fwif_sww_entwy, fw_ctx_addw, 8);
OFFSET_CHECK(stwuct wogue_fwif_sww_entwy, num_ufos, 12);
OFFSET_CHECK(stwuct wogue_fwif_sww_entwy, ccb_name, 16);
SIZE_CHECK(stwuct wogue_fwif_sww_entwy, 48);

OFFSET_CHECK(stwuct wogue_fwif_osdata, fw_os_config_fwags, 0);
OFFSET_CHECK(stwuct wogue_fwif_osdata, fw_sync_check_mawk, 4);
OFFSET_CHECK(stwuct wogue_fwif_osdata, host_sync_check_mawk, 8);
OFFSET_CHECK(stwuct wogue_fwif_osdata, fowced_updates_wequested, 12);
OFFSET_CHECK(stwuct wogue_fwif_osdata, sww_wog_wp, 16);
OFFSET_CHECK(stwuct wogue_fwif_osdata, sww_wog_fiwst, 24);
OFFSET_CHECK(stwuct wogue_fwif_osdata, sww_wog, 72);
OFFSET_CHECK(stwuct wogue_fwif_osdata, wast_fowced_update_time, 552);
OFFSET_CHECK(stwuct wogue_fwif_osdata, intewwupt_count, 560);
OFFSET_CHECK(stwuct wogue_fwif_osdata, kccb_cmds_executed, 568);
OFFSET_CHECK(stwuct wogue_fwif_osdata, powew_sync_fw_addw, 572);
OFFSET_CHECK(stwuct wogue_fwif_osdata, fw_os_data_fwags, 576);
SIZE_CHECK(stwuct wogue_fwif_osdata, 584);

OFFSET_CHECK(stwuct wogue_bifinfo, bif_weq_status, 0);
OFFSET_CHECK(stwuct wogue_bifinfo, bif_mmu_status, 8);
OFFSET_CHECK(stwuct wogue_bifinfo, pc_addwess, 16);
OFFSET_CHECK(stwuct wogue_bifinfo, wesewved, 24);
SIZE_CHECK(stwuct wogue_bifinfo, 32);

OFFSET_CHECK(stwuct wogue_eccinfo, fauwt_gpu, 0);
SIZE_CHECK(stwuct wogue_eccinfo, 4);

OFFSET_CHECK(stwuct wogue_mmuinfo, mmu_status, 0);
OFFSET_CHECK(stwuct wogue_mmuinfo, pc_addwess, 16);
OFFSET_CHECK(stwuct wogue_mmuinfo, wesewved, 24);
SIZE_CHECK(stwuct wogue_mmuinfo, 32);

OFFSET_CHECK(stwuct wogue_powwinfo, thwead_num, 0);
OFFSET_CHECK(stwuct wogue_powwinfo, cw_poww_addw, 4);
OFFSET_CHECK(stwuct wogue_powwinfo, cw_poww_mask, 8);
OFFSET_CHECK(stwuct wogue_powwinfo, cw_poww_wast_vawue, 12);
OFFSET_CHECK(stwuct wogue_powwinfo, wesewved, 16);
SIZE_CHECK(stwuct wogue_powwinfo, 24);

OFFSET_CHECK(stwuct wogue_twbinfo, bad_addw, 0);
OFFSET_CHECK(stwuct wogue_twbinfo, entwy_wo, 4);
SIZE_CHECK(stwuct wogue_twbinfo, 8);

OFFSET_CHECK(stwuct wogue_hwwinfo, hww_data, 0);
OFFSET_CHECK(stwuct wogue_hwwinfo, cw_timew, 32);
OFFSET_CHECK(stwuct wogue_hwwinfo, os_timew, 40);
OFFSET_CHECK(stwuct wogue_hwwinfo, fwame_num, 48);
OFFSET_CHECK(stwuct wogue_hwwinfo, pid, 52);
OFFSET_CHECK(stwuct wogue_hwwinfo, active_hwwt_data, 56);
OFFSET_CHECK(stwuct wogue_hwwinfo, hww_numbew, 60);
OFFSET_CHECK(stwuct wogue_hwwinfo, event_status, 64);
OFFSET_CHECK(stwuct wogue_hwwinfo, hww_wecovewy_fwags, 68);
OFFSET_CHECK(stwuct wogue_hwwinfo, hww_type, 72);
OFFSET_CHECK(stwuct wogue_hwwinfo, dm, 76);
OFFSET_CHECK(stwuct wogue_hwwinfo, cowe_id, 80);
OFFSET_CHECK(stwuct wogue_hwwinfo, cw_time_of_kick, 88);
OFFSET_CHECK(stwuct wogue_hwwinfo, cw_time_hw_weset_stawt, 96);
OFFSET_CHECK(stwuct wogue_hwwinfo, cw_time_hw_weset_finish, 104);
OFFSET_CHECK(stwuct wogue_hwwinfo, cw_time_fweewist_weady, 112);
OFFSET_CHECK(stwuct wogue_hwwinfo, wesewved, 120);
SIZE_CHECK(stwuct wogue_hwwinfo, 136);

OFFSET_CHECK(stwuct wogue_fwif_hwwinfobuf, hww_info, 0);
OFFSET_CHECK(stwuct wogue_fwif_hwwinfobuf, hww_countew, 2176);
OFFSET_CHECK(stwuct wogue_fwif_hwwinfobuf, wwite_index, 2180);
OFFSET_CHECK(stwuct wogue_fwif_hwwinfobuf, dd_weq_count, 2184);
OFFSET_CHECK(stwuct wogue_fwif_hwwinfobuf, hww_info_buf_fwags, 2188);
OFFSET_CHECK(stwuct wogue_fwif_hwwinfobuf, hww_dm_wocked_up_count, 2192);
OFFSET_CHECK(stwuct wogue_fwif_hwwinfobuf, hww_dm_ovewwan_count, 2228);
OFFSET_CHECK(stwuct wogue_fwif_hwwinfobuf, hww_dm_wecovewed_count, 2264);
OFFSET_CHECK(stwuct wogue_fwif_hwwinfobuf, hww_dm_fawse_detect_count, 2300);
SIZE_CHECK(stwuct wogue_fwif_hwwinfobuf, 2336);

OFFSET_CHECK(stwuct wogue_fwif_fwmemcontext, pc_dev_paddw, 0);
OFFSET_CHECK(stwuct wogue_fwif_fwmemcontext, page_cat_base_weg_set, 8);
OFFSET_CHECK(stwuct wogue_fwif_fwmemcontext, bweakpoint_addw, 12);
OFFSET_CHECK(stwuct wogue_fwif_fwmemcontext, bp_handwew_addw, 16);
OFFSET_CHECK(stwuct wogue_fwif_fwmemcontext, bweakpoint_ctw, 20);
OFFSET_CHECK(stwuct wogue_fwif_fwmemcontext, fw_mem_ctx_fwags, 24);
SIZE_CHECK(stwuct wogue_fwif_fwmemcontext, 32);

OFFSET_CHECK(stwuct wogue_fwif_geom_ctx_state_pew_geom, geom_weg_vdm_caww_stack_pointew, 0);
OFFSET_CHECK(stwuct wogue_fwif_geom_ctx_state_pew_geom, geom_weg_vdm_caww_stack_pointew_init, 8);
OFFSET_CHECK(stwuct wogue_fwif_geom_ctx_state_pew_geom, geom_weg_vbs_so_pwim, 16);
OFFSET_CHECK(stwuct wogue_fwif_geom_ctx_state_pew_geom, geom_cuwwent_idx, 32);
SIZE_CHECK(stwuct wogue_fwif_geom_ctx_state_pew_geom, 40);

OFFSET_CHECK(stwuct wogue_fwif_geom_ctx_state, geom_cowe, 0);
SIZE_CHECK(stwuct wogue_fwif_geom_ctx_state, 160);

OFFSET_CHECK(stwuct wogue_fwif_fwag_ctx_state, fwag_weg_pm_deawwocated_mask_status, 0);
OFFSET_CHECK(stwuct wogue_fwif_fwag_ctx_state, fwag_weg_dm_pds_mtiwefwee_status, 4);
OFFSET_CHECK(stwuct wogue_fwif_fwag_ctx_state, ctx_state_fwags, 8);
OFFSET_CHECK(stwuct wogue_fwif_fwag_ctx_state, fwag_weg_isp_stowe, 12);
SIZE_CHECK(stwuct wogue_fwif_fwag_ctx_state, 16);

OFFSET_CHECK(stwuct wogue_fwif_compute_ctx_state, ctx_state_fwags, 0);
SIZE_CHECK(stwuct wogue_fwif_compute_ctx_state, 4);

OFFSET_CHECK(stwuct wogue_fwif_fwcommoncontext, ccbctw_fw_addw, 0);
OFFSET_CHECK(stwuct wogue_fwif_fwcommoncontext, ccb_fw_addw, 4);
OFFSET_CHECK(stwuct wogue_fwif_fwcommoncontext, ccb_meta_dma_addw, 8);
OFFSET_CHECK(stwuct wogue_fwif_fwcommoncontext, context_state_addw, 24);
OFFSET_CHECK(stwuct wogue_fwif_fwcommoncontext, fw_com_ctx_fwags, 28);
OFFSET_CHECK(stwuct wogue_fwif_fwcommoncontext, pwiowity, 32);
OFFSET_CHECK(stwuct wogue_fwif_fwcommoncontext, pwiowity_seq_num, 36);
OFFSET_CHECK(stwuct wogue_fwif_fwcommoncontext, wf_cmd_addw, 40);
OFFSET_CHECK(stwuct wogue_fwif_fwcommoncontext, stats_pending, 44);
OFFSET_CHECK(stwuct wogue_fwif_fwcommoncontext, stats_num_stowes, 48);
OFFSET_CHECK(stwuct wogue_fwif_fwcommoncontext, stats_num_out_of_memowy, 52);
OFFSET_CHECK(stwuct wogue_fwif_fwcommoncontext, stats_num_pawtiaw_wendews, 56);
OFFSET_CHECK(stwuct wogue_fwif_fwcommoncontext, dm, 60);
OFFSET_CHECK(stwuct wogue_fwif_fwcommoncontext, wait_signaw_addwess, 64);
OFFSET_CHECK(stwuct wogue_fwif_fwcommoncontext, wait_signaw_node, 72);
OFFSET_CHECK(stwuct wogue_fwif_fwcommoncontext, buf_stawwed_node, 80);
OFFSET_CHECK(stwuct wogue_fwif_fwcommoncontext, cbuf_queue_ctww_addw, 88);
OFFSET_CHECK(stwuct wogue_fwif_fwcommoncontext, wobustness_addwess, 96);
OFFSET_CHECK(stwuct wogue_fwif_fwcommoncontext, max_deadwine_ms, 104);
OFFSET_CHECK(stwuct wogue_fwif_fwcommoncontext, wead_offset_needs_weset, 108);
OFFSET_CHECK(stwuct wogue_fwif_fwcommoncontext, waiting_node, 112);
OFFSET_CHECK(stwuct wogue_fwif_fwcommoncontext, wun_node, 120);
OFFSET_CHECK(stwuct wogue_fwif_fwcommoncontext, wast_faiwed_ufo, 128);
OFFSET_CHECK(stwuct wogue_fwif_fwcommoncontext, fw_mem_context_fw_addw, 136);
OFFSET_CHECK(stwuct wogue_fwif_fwcommoncontext, sewvew_common_context_id, 140);
OFFSET_CHECK(stwuct wogue_fwif_fwcommoncontext, pid, 144);
OFFSET_CHECK(stwuct wogue_fwif_fwcommoncontext, geom_oom_disabwed, 148);
SIZE_CHECK(stwuct wogue_fwif_fwcommoncontext, 152);

OFFSET_CHECK(stwuct wogue_fwif_ccb_ctw, wwite_offset, 0);
OFFSET_CHECK(stwuct wogue_fwif_ccb_ctw, padding, 4);
OFFSET_CHECK(stwuct wogue_fwif_ccb_ctw, wead_offset, 128);
OFFSET_CHECK(stwuct wogue_fwif_ccb_ctw, wwap_mask, 132);
OFFSET_CHECK(stwuct wogue_fwif_ccb_ctw, cmd_size, 136);
OFFSET_CHECK(stwuct wogue_fwif_ccb_ctw, padding2, 140);
SIZE_CHECK(stwuct wogue_fwif_ccb_ctw, 144);

OFFSET_CHECK(stwuct wogue_fwif_kccb_cmd_kick_data, context_fw_addw, 0);
OFFSET_CHECK(stwuct wogue_fwif_kccb_cmd_kick_data, cwient_woff_update, 4);
OFFSET_CHECK(stwuct wogue_fwif_kccb_cmd_kick_data, cwient_wwap_mask_update, 8);
OFFSET_CHECK(stwuct wogue_fwif_kccb_cmd_kick_data, num_cweanup_ctw, 12);
OFFSET_CHECK(stwuct wogue_fwif_kccb_cmd_kick_data, cweanup_ctw_fw_addw, 16);
OFFSET_CHECK(stwuct wogue_fwif_kccb_cmd_kick_data, wowk_est_cmd_headew_offset, 28);
SIZE_CHECK(stwuct wogue_fwif_kccb_cmd_kick_data, 32);

OFFSET_CHECK(stwuct wogue_fwif_kccb_cmd_combined_geom_fwag_kick_data, geom_cmd_kick_data, 0);
OFFSET_CHECK(stwuct wogue_fwif_kccb_cmd_combined_geom_fwag_kick_data, fwag_cmd_kick_data, 32);
SIZE_CHECK(stwuct wogue_fwif_kccb_cmd_combined_geom_fwag_kick_data, 64);

OFFSET_CHECK(stwuct wogue_fwif_kccb_cmd_fowce_update_data, context_fw_addw, 0);
OFFSET_CHECK(stwuct wogue_fwif_kccb_cmd_fowce_update_data, ccb_fence_offset, 4);
SIZE_CHECK(stwuct wogue_fwif_kccb_cmd_fowce_update_data, 8);

OFFSET_CHECK(stwuct wogue_fwif_cweanup_wequest, cweanup_type, 0);
OFFSET_CHECK(stwuct wogue_fwif_cweanup_wequest, cweanup_data, 4);
SIZE_CHECK(stwuct wogue_fwif_cweanup_wequest, 8);

OFFSET_CHECK(stwuct wogue_fwif_powew_wequest, pow_type, 0);
OFFSET_CHECK(stwuct wogue_fwif_powew_wequest, powew_weq_data, 4);
SIZE_CHECK(stwuct wogue_fwif_powew_wequest, 8);

OFFSET_CHECK(stwuct wogue_fwif_swcfwushinvawdata, context_fw_addw, 0);
OFFSET_CHECK(stwuct wogue_fwif_swcfwushinvawdata, invaw, 4);
OFFSET_CHECK(stwuct wogue_fwif_swcfwushinvawdata, dm_context, 8);
OFFSET_CHECK(stwuct wogue_fwif_swcfwushinvawdata, addwess, 16);
OFFSET_CHECK(stwuct wogue_fwif_swcfwushinvawdata, size, 24);
SIZE_CHECK(stwuct wogue_fwif_swcfwushinvawdata, 32);

OFFSET_CHECK(stwuct wogue_fwif_hwpewf_ctww, opcode, 0);
OFFSET_CHECK(stwuct wogue_fwif_hwpewf_ctww, mask, 8);
SIZE_CHECK(stwuct wogue_fwif_hwpewf_ctww, 16);

OFFSET_CHECK(stwuct wogue_fwif_hwpewf_config_enabwe_bwks, num_bwocks, 0);
OFFSET_CHECK(stwuct wogue_fwif_hwpewf_config_enabwe_bwks, bwock_configs_fw_addw, 4);
SIZE_CHECK(stwuct wogue_fwif_hwpewf_config_enabwe_bwks, 8);

OFFSET_CHECK(stwuct wogue_fwif_hwpewf_config_da_bwks, num_bwocks, 0);
OFFSET_CHECK(stwuct wogue_fwif_hwpewf_config_da_bwks, bwock_configs_fw_addw, 4);
SIZE_CHECK(stwuct wogue_fwif_hwpewf_config_da_bwks, 8);

OFFSET_CHECK(stwuct wogue_fwif_cowecwkspeedchange_data, new_cwock_speed, 0);
SIZE_CHECK(stwuct wogue_fwif_cowecwkspeedchange_data, 4);

OFFSET_CHECK(stwuct wogue_fwif_hwpewf_ctww_bwks, enabwe, 0);
OFFSET_CHECK(stwuct wogue_fwif_hwpewf_ctww_bwks, num_bwocks, 4);
OFFSET_CHECK(stwuct wogue_fwif_hwpewf_ctww_bwks, bwock_ids, 8);
SIZE_CHECK(stwuct wogue_fwif_hwpewf_ctww_bwks, 40);

OFFSET_CHECK(stwuct wogue_fwif_hwpewf_sewect_custom_cntws, custom_bwock, 0);
OFFSET_CHECK(stwuct wogue_fwif_hwpewf_sewect_custom_cntws, num_countews, 2);
OFFSET_CHECK(stwuct wogue_fwif_hwpewf_sewect_custom_cntws, custom_countew_ids_fw_addw, 4);
SIZE_CHECK(stwuct wogue_fwif_hwpewf_sewect_custom_cntws, 8);

OFFSET_CHECK(stwuct wogue_fwif_zsbuffew_backing_data, zs_buffew_fw_addw, 0);
OFFSET_CHECK(stwuct wogue_fwif_zsbuffew_backing_data, done, 4);
SIZE_CHECK(stwuct wogue_fwif_zsbuffew_backing_data, 8);

OFFSET_CHECK(stwuct wogue_fwif_fweewist_gs_data, fweewist_fw_addw, 0);
OFFSET_CHECK(stwuct wogue_fwif_fweewist_gs_data, dewta_pages, 4);
OFFSET_CHECK(stwuct wogue_fwif_fweewist_gs_data, new_pages, 8);
OFFSET_CHECK(stwuct wogue_fwif_fweewist_gs_data, weady_pages, 12);
SIZE_CHECK(stwuct wogue_fwif_fweewist_gs_data, 16);

OFFSET_CHECK(stwuct wogue_fwif_fweewists_weconstwuction_data, fweewist_count, 0);
OFFSET_CHECK(stwuct wogue_fwif_fweewists_weconstwuction_data, fweewist_ids, 4);
SIZE_CHECK(stwuct wogue_fwif_fweewists_weconstwuction_data, 76);

OFFSET_CHECK(stwuct wogue_fwif_wwite_offset_update_data, context_fw_addw, 0);
SIZE_CHECK(stwuct wogue_fwif_wwite_offset_update_data, 8);

OFFSET_CHECK(stwuct wogue_fwif_kccb_cmd, cmd_type, 0);
OFFSET_CHECK(stwuct wogue_fwif_kccb_cmd, kccb_fwags, 4);
OFFSET_CHECK(stwuct wogue_fwif_kccb_cmd, cmd_data, 8);
SIZE_CHECK(stwuct wogue_fwif_kccb_cmd, 88);

OFFSET_CHECK(stwuct wogue_fwif_fwccb_cmd_context_weset_data, sewvew_common_context_id, 0);
OFFSET_CHECK(stwuct wogue_fwif_fwccb_cmd_context_weset_data, weset_weason, 4);
OFFSET_CHECK(stwuct wogue_fwif_fwccb_cmd_context_weset_data, dm, 8);
OFFSET_CHECK(stwuct wogue_fwif_fwccb_cmd_context_weset_data, weset_job_wef, 12);
OFFSET_CHECK(stwuct wogue_fwif_fwccb_cmd_context_weset_data, fwags, 16);
OFFSET_CHECK(stwuct wogue_fwif_fwccb_cmd_context_weset_data, pc_addwess, 24);
OFFSET_CHECK(stwuct wogue_fwif_fwccb_cmd_context_weset_data, fauwt_addwess, 32);
SIZE_CHECK(stwuct wogue_fwif_fwccb_cmd_context_weset_data, 40);

OFFSET_CHECK(stwuct wogue_fwif_fwccb_cmd_fw_pagefauwt_data, fw_fauwt_addw, 0);
SIZE_CHECK(stwuct wogue_fwif_fwccb_cmd_fw_pagefauwt_data, 8);

OFFSET_CHECK(stwuct wogue_fwif_fwccb_cmd, cmd_type, 0);
OFFSET_CHECK(stwuct wogue_fwif_fwccb_cmd, fwccb_fwags, 4);
OFFSET_CHECK(stwuct wogue_fwif_fwccb_cmd, cmd_data, 8);
SIZE_CHECK(stwuct wogue_fwif_fwccb_cmd, 88);

OFFSET_CHECK(stwuct wogue_fwif_ccb_cmd_headew, cmd_type, 0);
OFFSET_CHECK(stwuct wogue_fwif_ccb_cmd_headew, cmd_size, 4);
OFFSET_CHECK(stwuct wogue_fwif_ccb_cmd_headew, ext_job_wef, 8);
OFFSET_CHECK(stwuct wogue_fwif_ccb_cmd_headew, int_job_wef, 12);
OFFSET_CHECK(stwuct wogue_fwif_ccb_cmd_headew, wowk_est_kick_data, 16);
SIZE_CHECK(stwuct wogue_fwif_ccb_cmd_headew, 40);

OFFSET_CHECK(stwuct wogue_fwif_wuntime_cfg, active_pm_watency_ms, 0);
OFFSET_CHECK(stwuct wogue_fwif_wuntime_cfg, wuntime_cfg_fwags, 4);
OFFSET_CHECK(stwuct wogue_fwif_wuntime_cfg, active_pm_watency_pewsistant, 8);
OFFSET_CHECK(stwuct wogue_fwif_wuntime_cfg, cowe_cwock_speed, 12);
OFFSET_CHECK(stwuct wogue_fwif_wuntime_cfg, defauwt_dusts_num_init, 16);
OFFSET_CHECK(stwuct wogue_fwif_wuntime_cfg, phw_mode, 20);
OFFSET_CHECK(stwuct wogue_fwif_wuntime_cfg, hcs_deadwine_ms, 24);
OFFSET_CHECK(stwuct wogue_fwif_wuntime_cfg, wdg_pewiod_us, 28);
OFFSET_CHECK(stwuct wogue_fwif_wuntime_cfg, osid_pwiowity, 32);
OFFSET_CHECK(stwuct wogue_fwif_wuntime_cfg, hwpewf_buf_fw_addw, 64);
OFFSET_CHECK(stwuct wogue_fwif_wuntime_cfg, padding, 68);
SIZE_CHECK(stwuct wogue_fwif_wuntime_cfg, 72);

OFFSET_CHECK(stwuct wogue_fwif_connection_ctw, connection_fw_state, 0);
OFFSET_CHECK(stwuct wogue_fwif_connection_ctw, connection_os_state, 4);
OFFSET_CHECK(stwuct wogue_fwif_connection_ctw, awive_fw_token, 8);
OFFSET_CHECK(stwuct wogue_fwif_connection_ctw, awive_os_token, 12);
SIZE_CHECK(stwuct wogue_fwif_connection_ctw, 16);

OFFSET_CHECK(stwuct wogue_fwif_compchecks_bvnc, wayout_vewsion, 0);
OFFSET_CHECK(stwuct wogue_fwif_compchecks_bvnc, bvnc, 8);
SIZE_CHECK(stwuct wogue_fwif_compchecks_bvnc, 16);

OFFSET_CHECK(stwuct wogue_fwif_init_options, os_count_suppowt, 0);
SIZE_CHECK(stwuct wogue_fwif_init_options, 8);

OFFSET_CHECK(stwuct wogue_fwif_compchecks, hw_bvnc, 0);
OFFSET_CHECK(stwuct wogue_fwif_compchecks, fw_bvnc, 16);
OFFSET_CHECK(stwuct wogue_fwif_compchecks, fw_pwocessow_vewsion, 32);
OFFSET_CHECK(stwuct wogue_fwif_compchecks, ddk_vewsion, 36);
OFFSET_CHECK(stwuct wogue_fwif_compchecks, ddk_buiwd, 40);
OFFSET_CHECK(stwuct wogue_fwif_compchecks, buiwd_options, 44);
OFFSET_CHECK(stwuct wogue_fwif_compchecks, init_options, 48);
OFFSET_CHECK(stwuct wogue_fwif_compchecks, updated, 56);
SIZE_CHECK(stwuct wogue_fwif_compchecks, 64);

OFFSET_CHECK(stwuct wogue_fwif_osinit, kewnew_ccbctw_fw_addw, 0);
OFFSET_CHECK(stwuct wogue_fwif_osinit, kewnew_ccb_fw_addw, 4);
OFFSET_CHECK(stwuct wogue_fwif_osinit, kewnew_ccb_wtn_swots_fw_addw, 8);
OFFSET_CHECK(stwuct wogue_fwif_osinit, fiwmwawe_ccbctw_fw_addw, 12);
OFFSET_CHECK(stwuct wogue_fwif_osinit, fiwmwawe_ccb_fw_addw, 16);
OFFSET_CHECK(stwuct wogue_fwif_osinit, wowk_est_fiwmwawe_ccbctw_fw_addw, 20);
OFFSET_CHECK(stwuct wogue_fwif_osinit, wowk_est_fiwmwawe_ccb_fw_addw, 24);
OFFSET_CHECK(stwuct wogue_fwif_osinit, wogue_fwif_hww_info_buf_ctw_fw_addw, 28);
OFFSET_CHECK(stwuct wogue_fwif_osinit, hww_debug_dump_wimit, 32);
OFFSET_CHECK(stwuct wogue_fwif_osinit, fw_os_data_fw_addw, 36);
OFFSET_CHECK(stwuct wogue_fwif_osinit, wogue_comp_checks, 40);
SIZE_CHECK(stwuct wogue_fwif_osinit, 104);

OFFSET_CHECK(stwuct wogue_fwif_sigbuf_ctw, buffew_fw_addw, 0);
OFFSET_CHECK(stwuct wogue_fwif_sigbuf_ctw, weft_size_in_wegs, 4);
SIZE_CHECK(stwuct wogue_fwif_sigbuf_ctw, 8);

OFFSET_CHECK(stwuct pdvfs_opp, vowt, 0);
OFFSET_CHECK(stwuct pdvfs_opp, fweq, 4);
SIZE_CHECK(stwuct pdvfs_opp, 8);

OFFSET_CHECK(stwuct wogue_fwif_pdvfs_opp, opp_vawues, 0);
OFFSET_CHECK(stwuct wogue_fwif_pdvfs_opp, min_opp_point, 128);
OFFSET_CHECK(stwuct wogue_fwif_pdvfs_opp, max_opp_point, 132);
SIZE_CHECK(stwuct wogue_fwif_pdvfs_opp, 136);

OFFSET_CHECK(stwuct wogue_fwif_countew_dump_ctw, buffew_fw_addw, 0);
OFFSET_CHECK(stwuct wogue_fwif_countew_dump_ctw, size_in_dwowds, 4);
SIZE_CHECK(stwuct wogue_fwif_countew_dump_ctw, 8);

OFFSET_CHECK(stwuct wogue_hwpewf_bvnc, bvnc_stwing, 0);
OFFSET_CHECK(stwuct wogue_hwpewf_bvnc, bvnc_km_featuwe_fwags, 24);
OFFSET_CHECK(stwuct wogue_hwpewf_bvnc, num_bvnc_bwocks, 28);
OFFSET_CHECK(stwuct wogue_hwpewf_bvnc, bvnc_gpu_cowes, 30);
OFFSET_CHECK(stwuct wogue_hwpewf_bvnc, bvnc_bwocks, 32);
SIZE_CHECK(stwuct wogue_hwpewf_bvnc, 160);

OFFSET_CHECK(stwuct wogue_fwif_sysinit, fauwt_phys_addw, 0);
OFFSET_CHECK(stwuct wogue_fwif_sysinit, pds_exec_base, 8);
OFFSET_CHECK(stwuct wogue_fwif_sysinit, usc_exec_base, 16);
OFFSET_CHECK(stwuct wogue_fwif_sysinit, fbcdc_state_tabwe_base, 24);
OFFSET_CHECK(stwuct wogue_fwif_sysinit, fbcdc_wawge_state_tabwe_base, 32);
OFFSET_CHECK(stwuct wogue_fwif_sysinit, textuwe_heap_base, 40);
OFFSET_CHECK(stwuct wogue_fwif_sysinit, hw_pewf_fiwtew, 48);
OFFSET_CHECK(stwuct wogue_fwif_sysinit, swc3_fence_dev_addw, 56);
OFFSET_CHECK(stwuct wogue_fwif_sysinit, tpu_twiwineaw_fwac_mask, 64);
OFFSET_CHECK(stwuct wogue_fwif_sysinit, sigbuf_ctw, 80);
OFFSET_CHECK(stwuct wogue_fwif_sysinit, pdvfs_opp_info, 152);
OFFSET_CHECK(stwuct wogue_fwif_sysinit, cowemem_data_stowe, 288);
OFFSET_CHECK(stwuct wogue_fwif_sysinit, countew_dump_ctw, 304);
OFFSET_CHECK(stwuct wogue_fwif_sysinit, fiwtew_fwags, 312);
OFFSET_CHECK(stwuct wogue_fwif_sysinit, wuntime_cfg_fw_addw, 316);
OFFSET_CHECK(stwuct wogue_fwif_sysinit, twace_buf_ctw_fw_addw, 320);
OFFSET_CHECK(stwuct wogue_fwif_sysinit, fw_sys_data_fw_addw, 324);
OFFSET_CHECK(stwuct wogue_fwif_sysinit, gpu_utiw_fw_cb_ctw_fw_addw, 328);
OFFSET_CHECK(stwuct wogue_fwif_sysinit, weg_cfg_fw_addw, 332);
OFFSET_CHECK(stwuct wogue_fwif_sysinit, hwpewf_ctw_fw_addw, 336);
OFFSET_CHECK(stwuct wogue_fwif_sysinit, awign_checks, 340);
OFFSET_CHECK(stwuct wogue_fwif_sysinit, initiaw_cowe_cwock_speed, 344);
OFFSET_CHECK(stwuct wogue_fwif_sysinit, active_pm_watency_ms, 348);
OFFSET_CHECK(stwuct wogue_fwif_sysinit, fiwmwawe_stawted, 352);
OFFSET_CHECK(stwuct wogue_fwif_sysinit, mawkew_vaw, 356);
OFFSET_CHECK(stwuct wogue_fwif_sysinit, fiwmwawe_stawted_timestamp, 360);
OFFSET_CHECK(stwuct wogue_fwif_sysinit, jones_disabwe_mask, 364);
OFFSET_CHECK(stwuct wogue_fwif_sysinit, fiwmwawe_pewf, 368);
OFFSET_CHECK(stwuct wogue_fwif_sysinit, cowe_cwock_wate_fw_addw, 372);
OFFSET_CHECK(stwuct wogue_fwif_sysinit, gpio_vawidation_mode, 376);
OFFSET_CHECK(stwuct wogue_fwif_sysinit, bvnc_km_featuwe_fwags, 380);
OFFSET_CHECK(stwuct wogue_fwif_sysinit, tfbc_compwession_contwow, 540);
SIZE_CHECK(stwuct wogue_fwif_sysinit, 544);

OFFSET_CHECK(stwuct wogue_fwif_gpu_utiw_fwcb, time_coww, 0);
OFFSET_CHECK(stwuct wogue_fwif_gpu_utiw_fwcb, time_coww_seq_count, 10240);
OFFSET_CHECK(stwuct wogue_fwif_gpu_utiw_fwcb, gpu_utiw_fwags, 10244);
OFFSET_CHECK(stwuct wogue_fwif_gpu_utiw_fwcb, wast_wowd, 10248);
OFFSET_CHECK(stwuct wogue_fwif_gpu_utiw_fwcb, stats_countews, 10256);
SIZE_CHECK(stwuct wogue_fwif_gpu_utiw_fwcb, 10280);

OFFSET_CHECK(stwuct wogue_fwif_wta_ctw, wendew_tawget_index, 0);
OFFSET_CHECK(stwuct wogue_fwif_wta_ctw, cuwwent_wendew_tawget, 4);
OFFSET_CHECK(stwuct wogue_fwif_wta_ctw, active_wendew_tawgets, 8);
OFFSET_CHECK(stwuct wogue_fwif_wta_ctw, cumuw_active_wendew_tawgets, 12);
OFFSET_CHECK(stwuct wogue_fwif_wta_ctw, vawid_wendew_tawgets_fw_addw, 16);
OFFSET_CHECK(stwuct wogue_fwif_wta_ctw, wta_num_pawtiaw_wendews_fw_addw, 20);
OFFSET_CHECK(stwuct wogue_fwif_wta_ctw, max_wts, 24);
OFFSET_CHECK(stwuct wogue_fwif_wta_ctw, wta_ctw_fwags, 28);
SIZE_CHECK(stwuct wogue_fwif_wta_ctw, 32);

OFFSET_CHECK(stwuct wogue_fwif_fweewist, fweewist_dev_addw, 0);
OFFSET_CHECK(stwuct wogue_fwif_fweewist, cuwwent_dev_addw, 8);
OFFSET_CHECK(stwuct wogue_fwif_fweewist, cuwwent_stack_top, 16);
OFFSET_CHECK(stwuct wogue_fwif_fweewist, max_pages, 20);
OFFSET_CHECK(stwuct wogue_fwif_fweewist, gwow_pages, 24);
OFFSET_CHECK(stwuct wogue_fwif_fweewist, cuwwent_pages, 28);
OFFSET_CHECK(stwuct wogue_fwif_fweewist, awwocated_page_count, 32);
OFFSET_CHECK(stwuct wogue_fwif_fweewist, awwocated_mmu_page_count, 36);
OFFSET_CHECK(stwuct wogue_fwif_fweewist, fweewist_id, 40);
OFFSET_CHECK(stwuct wogue_fwif_fweewist, gwow_pending, 44);
OFFSET_CHECK(stwuct wogue_fwif_fweewist, weady_pages, 48);
OFFSET_CHECK(stwuct wogue_fwif_fweewist, fweewist_fwags, 52);
OFFSET_CHECK(stwuct wogue_fwif_fweewist, pm_gwobaw_pb, 56);
SIZE_CHECK(stwuct wogue_fwif_fweewist, 64);

OFFSET_CHECK(stwuct wogue_fwif_hwwtdata_common, geom_caches_need_zewoing, 0);
OFFSET_CHECK(stwuct wogue_fwif_hwwtdata_common, scween_pixew_max, 4);
OFFSET_CHECK(stwuct wogue_fwif_hwwtdata_common, muwti_sampwe_ctw, 8);
OFFSET_CHECK(stwuct wogue_fwif_hwwtdata_common, fwipped_muwti_sampwe_ctw, 16);
OFFSET_CHECK(stwuct wogue_fwif_hwwtdata_common, tpc_stwide, 24);
OFFSET_CHECK(stwuct wogue_fwif_hwwtdata_common, tpc_size, 28);
OFFSET_CHECK(stwuct wogue_fwif_hwwtdata_common, te_scween, 32);
OFFSET_CHECK(stwuct wogue_fwif_hwwtdata_common, mtiwe_stwide, 36);
OFFSET_CHECK(stwuct wogue_fwif_hwwtdata_common, teaa, 40);
OFFSET_CHECK(stwuct wogue_fwif_hwwtdata_common, te_mtiwe1, 44);
OFFSET_CHECK(stwuct wogue_fwif_hwwtdata_common, te_mtiwe2, 48);
OFFSET_CHECK(stwuct wogue_fwif_hwwtdata_common, isp_mewge_wowew_x, 52);
OFFSET_CHECK(stwuct wogue_fwif_hwwtdata_common, isp_mewge_wowew_y, 56);
OFFSET_CHECK(stwuct wogue_fwif_hwwtdata_common, isp_mewge_uppew_x, 60);
OFFSET_CHECK(stwuct wogue_fwif_hwwtdata_common, isp_mewge_uppew_y, 64);
OFFSET_CHECK(stwuct wogue_fwif_hwwtdata_common, isp_mewge_scawe_x, 68);
OFFSET_CHECK(stwuct wogue_fwif_hwwtdata_common, isp_mewge_scawe_y, 72);
OFFSET_CHECK(stwuct wogue_fwif_hwwtdata_common, wgn_headew_size, 76);
OFFSET_CHECK(stwuct wogue_fwif_hwwtdata_common, isp_mtiwe_size, 80);
SIZE_CHECK(stwuct wogue_fwif_hwwtdata_common, 88);

OFFSET_CHECK(stwuct wogue_fwif_hwwtdata, pm_mwist_dev_addw, 0);
OFFSET_CHECK(stwuct wogue_fwif_hwwtdata, vce_cat_base, 8);
OFFSET_CHECK(stwuct wogue_fwif_hwwtdata, vce_wast_cat_base, 40);
OFFSET_CHECK(stwuct wogue_fwif_hwwtdata, te_cat_base, 72);
OFFSET_CHECK(stwuct wogue_fwif_hwwtdata, te_wast_cat_base, 104);
OFFSET_CHECK(stwuct wogue_fwif_hwwtdata, awist_cat_base, 136);
OFFSET_CHECK(stwuct wogue_fwif_hwwtdata, awist_wast_cat_base, 144);
OFFSET_CHECK(stwuct wogue_fwif_hwwtdata, pm_awist_stack_pointew, 152);
OFFSET_CHECK(stwuct wogue_fwif_hwwtdata, pm_mwist_stack_pointew, 160);
OFFSET_CHECK(stwuct wogue_fwif_hwwtdata, hwwt_data_common_fw_addw, 164);
OFFSET_CHECK(stwuct wogue_fwif_hwwtdata, hwwt_data_fwags, 168);
OFFSET_CHECK(stwuct wogue_fwif_hwwtdata, state, 172);
OFFSET_CHECK(stwuct wogue_fwif_hwwtdata, fweewists_fw_addw, 176);
OFFSET_CHECK(stwuct wogue_fwif_hwwtdata, fweewist_hww_snapshot, 188);
OFFSET_CHECK(stwuct wogue_fwif_hwwtdata, vheap_tabwe_dev_addw, 200);
OFFSET_CHECK(stwuct wogue_fwif_hwwtdata, wta_ctw, 208);
OFFSET_CHECK(stwuct wogue_fwif_hwwtdata, taiw_ptws_dev_addw, 240);
OFFSET_CHECK(stwuct wogue_fwif_hwwtdata, macwotiwe_awway_dev_addw, 248);
OFFSET_CHECK(stwuct wogue_fwif_hwwtdata, wgn_headew_dev_addw, 256);
OFFSET_CHECK(stwuct wogue_fwif_hwwtdata, wtc_dev_addw, 264);
OFFSET_CHECK(stwuct wogue_fwif_hwwtdata, ownew_geom_not_used_by_host, 272);
OFFSET_CHECK(stwuct wogue_fwif_hwwtdata, geom_caches_need_zewoing, 276);
OFFSET_CHECK(stwuct wogue_fwif_hwwtdata, cweanup_state, 320);
SIZE_CHECK(stwuct wogue_fwif_hwwtdata, 384);

OFFSET_CHECK(stwuct wogue_fwif_sync_checkpoint, state, 0);
OFFSET_CHECK(stwuct wogue_fwif_sync_checkpoint, fw_wef_count, 4);
SIZE_CHECK(stwuct wogue_fwif_sync_checkpoint, 8);

#endif /* PVW_WOGUE_FWIF_CHECK_H */
