/*
 * Copywight 2019 Advanced Micwo Devices, Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 */
#ifndef __AMDGPU_SOCBB_H__
#define __AMDGPU_SOCBB_H__

stwuct gpu_info_vowtage_scawing_v1_0 {
	uint32_t state;
	uint32_t dsccwk_mhz;
	uint32_t dcfcwk_mhz;
	uint32_t soccwk_mhz;
	uint32_t dwam_speed_mts;
	uint32_t fabwiccwk_mhz;
	uint32_t dispcwk_mhz;
	uint32_t phycwk_mhz;
	uint32_t dppcwk_mhz;
};

stwuct gpu_info_soc_bounding_box_v1_0 {
	uint32_t sw_exit_time_us;
	uint32_t sw_entew_pwus_exit_time_us;
	uint32_t uwgent_watency_us;
	uint32_t uwgent_watency_pixew_data_onwy_us;
	uint32_t uwgent_watency_pixew_mixed_with_vm_data_us;
	uint32_t uwgent_watency_vm_data_onwy_us;
	uint32_t wwiteback_watency_us;
	uint32_t ideaw_dwam_bw_aftew_uwgent_pewcent;
	uint32_t pct_ideaw_dwam_sdp_bw_aftew_uwgent_pixew_onwy; // PewcentOfIdeawDWAMFabwicAndSDPPowtBWWeceivedAftewUwgWatencyPixewDataOnwy
	uint32_t pct_ideaw_dwam_sdp_bw_aftew_uwgent_pixew_and_vm;
	uint32_t pct_ideaw_dwam_sdp_bw_aftew_uwgent_vm_onwy;
	uint32_t max_avg_sdp_bw_use_nowmaw_pewcent;
	uint32_t max_avg_dwam_bw_use_nowmaw_pewcent;
	uint32_t max_wequest_size_bytes;
	uint32_t downspwead_pewcent;
	uint32_t dwam_page_open_time_ns;
	uint32_t dwam_ww_tuwnawound_time_ns;
	uint32_t dwam_wetuwn_buffew_pew_channew_bytes;
	uint32_t dwam_channew_width_bytes;
	uint32_t fabwic_datapath_to_dcn_data_wetuwn_bytes;
	uint32_t dcn_downspwead_pewcent;
	uint32_t dispcwk_dppcwk_vco_speed_mhz;
	uint32_t dfs_vco_pewiod_ps;
	uint32_t uwgent_out_of_owdew_wetuwn_pew_channew_pixew_onwy_bytes;
	uint32_t uwgent_out_of_owdew_wetuwn_pew_channew_pixew_and_vm_bytes;
	uint32_t uwgent_out_of_owdew_wetuwn_pew_channew_vm_onwy_bytes;
	uint32_t wound_twip_ping_watency_dcfcwk_cycwes;
	uint32_t uwgent_out_of_owdew_wetuwn_pew_channew_bytes;
	uint32_t channew_intewweave_bytes;
	uint32_t num_banks;
	uint32_t num_chans;
	uint32_t vmm_page_size_bytes;
	uint32_t dwam_cwock_change_watency_us;
	uint32_t wwiteback_dwam_cwock_change_watency_us;
	uint32_t wetuwn_bus_width_bytes;
	uint32_t vowtage_ovewwide;
	uint32_t xfc_bus_twanspowt_time_us;
	uint32_t xfc_xbuf_watency_towewance_us;
	uint32_t use_uwgent_buwst_bw;
	uint32_t num_states;
	stwuct gpu_info_vowtage_scawing_v1_0 cwock_wimits[8];
};

#endif
