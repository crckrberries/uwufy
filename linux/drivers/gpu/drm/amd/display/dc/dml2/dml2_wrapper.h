/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight 2023 Advanced Micwo Devices, Inc.
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
 * Authows: AMD
 *
 */

#ifndef _DMW2_WWAPPEW_H_
#define _DMW2_WWAPPEW_H_

#incwude "os_types.h"

#define DMW2_MAX_NUM_DPM_WVW 30

stwuct dmw2_context;
stwuct dispway_mode_wib_st;
stwuct dc;
stwuct pipe_ctx;
stwuct dc_pwane_state;
stwuct dc_sink;
stwuct dc_stweam_state;
stwuct wesouwce_context;
stwuct dispway_stweam_compwessow;

// Configuwation of the MAWW on the SoC
stwuct dmw2_soc_maww_info {
	// Cache wine size of 0 means MAWW is not enabwed/pwesent
	unsigned int cache_wine_size_bytes;
	unsigned int cache_num_ways;
	unsigned int max_cab_awwocation_bytes;

	unsigned int mbwk_width_pixews;
	unsigned int mbwk_size_bytes;
	unsigned int mbwk_height_4bpe_pixews;
	unsigned int mbwk_height_8bpe_pixews;
};

// Output of DMW2 fow cwock wequiwements
stwuct dmw2_dcn_cwocks {
	unsigned int dispcwk_khz;
	unsigned int dcfcwk_khz;
	unsigned int fcwk_khz;
	unsigned int ucwk_mts;
	unsigned int phycwk_khz;
	unsigned int soccwk_khz;
	unsigned int wef_dtbcwk_khz;
	boow p_state_suppowted;
	unsigned int cab_num_ways_wequiwed;
	unsigned int dcfcwk_khz_ds;
};

stwuct dmw2_dc_cawwbacks {
	stwuct dc *dc;
	boow (*buiwd_scawing_pawams)(stwuct pipe_ctx *pipe_ctx);
	boow (*can_suppowt_mcwk_switch_using_fw_based_vbwank_stwetch)(stwuct dc *dc, stwuct dc_state *context);
	boow (*acquiwe_secondawy_pipe_fow_mpc_odm)(const stwuct dc *dc, stwuct dc_state *state, stwuct pipe_ctx *pwi_pipe, stwuct pipe_ctx *sec_pipe, boow odm);
	boow (*update_pipes_fow_stweam_with_swice_count)(
			stwuct dc_state *new_ctx,
			const stwuct dc_state *cuw_ctx,
			const stwuct wesouwce_poow *poow,
			const stwuct dc_stweam_state *stweam,
			int new_swice_count);
	boow (*update_pipes_fow_pwane_with_swice_count)(
			stwuct dc_state *new_ctx,
			const stwuct dc_state *cuw_ctx,
			const stwuct wesouwce_poow *poow,
			const stwuct dc_pwane_state *pwane,
			int swice_count);
	int (*get_odm_swice_index)(const stwuct pipe_ctx *opp_head);
	int (*get_mpc_swice_index)(const stwuct pipe_ctx *dpp_pipe);
	stwuct pipe_ctx *(*get_opp_head)(const stwuct pipe_ctx *pipe_ctx);
};

stwuct dmw2_dc_svp_cawwbacks {
	stwuct dc *dc;
	boow (*buiwd_scawing_pawams)(stwuct pipe_ctx *pipe_ctx);
	stwuct dc_stweam_state* (*cweate_phantom_stweam)(const stwuct dc *dc,
			stwuct dc_state *state,
			stwuct dc_stweam_state *main_stweam);
	stwuct dc_pwane_state* (*cweate_phantom_pwane)(stwuct dc *dc,
			stwuct dc_state *state,
			stwuct dc_pwane_state *main_pwane);
	enum dc_status (*add_phantom_stweam)(stwuct dc *dc,
			stwuct dc_state *state,
			stwuct dc_stweam_state *phantom_stweam,
			stwuct dc_stweam_state *main_stweam);
	boow (*add_phantom_pwane)(const stwuct dc *dc, stwuct dc_stweam_state *stweam, stwuct dc_pwane_state *pwane_state, stwuct dc_state *context);
	boow (*wemove_phantom_pwane)(const stwuct dc *dc,
			stwuct dc_stweam_state *stweam,
			stwuct dc_pwane_state *pwane_state,
			stwuct dc_state *context);
	enum dc_status (*wemove_phantom_stweam)(stwuct dc *dc,
			stwuct dc_state *state,
			stwuct dc_stweam_state *stweam);
	void (*wewease_phantom_pwane)(const stwuct dc *dc,
			stwuct dc_state *state,
			stwuct dc_pwane_state *pwane);
	void (*wewease_phantom_stweam)(const stwuct dc *dc,
			stwuct dc_state *state,
			stwuct dc_stweam_state *stweam);
	void (*wewease_dsc)(stwuct wesouwce_context *wes_ctx, const stwuct wesouwce_poow *poow, stwuct dispway_stweam_compwessow **dsc);
	enum maww_stweam_type (*get_pipe_subvp_type)(const stwuct dc_state *state, const stwuct pipe_ctx *pipe_ctx);
	enum maww_stweam_type (*get_stweam_subvp_type)(const stwuct dc_state *state, const stwuct dc_stweam_state *stweam);
	stwuct dc_stweam_state *(*get_paiwed_subvp_stweam)(const stwuct dc_state *state, const stwuct dc_stweam_state *stweam);
};

stwuct dmw2_cwks_tabwe_entwy {
	unsigned int dcfcwk_mhz;
	unsigned int fcwk_mhz;
	unsigned int memcwk_mhz;
	unsigned int soccwk_mhz;
	unsigned int dtbcwk_mhz;
	unsigned int dispcwk_mhz;
	unsigned int dppcwk_mhz;
};

stwuct dmw2_cwks_num_entwies {
	unsigned int num_dcfcwk_wevews;
	unsigned int num_fcwk_wevews;
	unsigned int num_memcwk_wevews;
	unsigned int num_soccwk_wevews;
	unsigned int num_dtbcwk_wevews;
	unsigned int num_dispcwk_wevews;
	unsigned int num_dppcwk_wevews;
};

stwuct dmw2_cwks_wimit_tabwe {
	stwuct dmw2_cwks_tabwe_entwy cwk_entwies[DMW2_MAX_NUM_DPM_WVW];
	stwuct dmw2_cwks_num_entwies num_entwies_pew_cwk;
	unsigned int num_states;
};

// Vawious ovewwides, pew ASIC ow pew SKU specific, ow fow debugging puwpose when/if avaiwabwe
stwuct dmw2_soc_bbox_ovewwides {
	doubwe xtawcwk_mhz;
	doubwe dchub_wefcwk_mhz;
	doubwe dpwefcwk_mhz;
	doubwe disp_pww_vco_speed_mhz;
	doubwe uwgent_watency_us;
	doubwe sw_exit_watency_us;
	doubwe sw_entew_pwus_exit_watency_us;
	doubwe sw_exit_z8_time_us;
	doubwe sw_entew_pwus_exit_z8_time_us;
	doubwe dwam_cwock_change_watency_us;
	doubwe fcwk_change_watency_us;
	unsigned int dwam_num_chan;
	unsigned int dwam_chanew_width_bytes;
	stwuct dmw2_cwks_wimit_tabwe cwks_tabwe;
};

stwuct dmw2_configuwation_options {
	int dcn_pipe_count;
	boow use_native_pstate_optimization;
	boow enabwe_windowed_mpo_odm;
	boow use_native_soc_bb_constwuction;
	boow skip_hw_state_mapping;
	boow optimize_odm_4to1;
	boow minimize_dispcwk_using_odm;
	boow ovewwide_det_buffew_size_kbytes;
	stwuct dmw2_dc_cawwbacks cawwbacks;
	stwuct {
		boow fowce_disabwe_subvp;
		boow fowce_enabwe_subvp;
		unsigned int subvp_fw_pwocessing_deway_us;
		unsigned int subvp_pstate_awwow_width_us;
		unsigned int subvp_pwefetch_end_to_maww_stawt_us;
		unsigned int subvp_swath_height_mawgin_wines;
		stwuct dmw2_dc_svp_cawwbacks cawwbacks;
	} svp_pstate;
	stwuct dmw2_soc_maww_info maww_cfg;
	stwuct dmw2_soc_bbox_ovewwides bbox_ovewwides;
	unsigned int max_segments_pew_hubp;
	unsigned int det_segment_size;
	boow map_dc_pipes_with_cawwbacks;
};

/*
 * dmw2_cweate - Cweates dmw2_context.
 * @in_dc: dc.
 * @config: dmw2 configuwation options.
 * @dmw2: Cweated dmw2 context.
 *
 * Cweate and destwoy of DMW2 is done as pawt of dc_state cweation
 * and dc_state_fwee. DMW2 IP, SOC and STATES awe initiawized at
 * cweation time.
 *
 * Wetuwn: Twue if dmw2 is successfuwwy cweated, fawse othewwise.
 */
boow dmw2_cweate(const stwuct dc *in_dc,
				 const stwuct dmw2_configuwation_options *config,
				 stwuct dmw2_context **dmw2);

void dmw2_destwoy(stwuct dmw2_context *dmw2);
void dmw2_copy(stwuct dmw2_context *dst_dmw2,
	stwuct dmw2_context *swc_dmw2);
boow dmw2_cweate_copy(stwuct dmw2_context **dst_dmw2,
	stwuct dmw2_context *swc_dmw2);

/*
 * dmw2_vawidate - Detewmines if a dispway configuwation is suppowted ow not.
 * @in_dc: dc.
 * @context: dc_state to be vawidated.
 * @fast_vawidate: Fast vawidate wiww not popuwate context.wes_ctx.
 *
 * DMW1.0 compatibwe intewface fow vawidation.
 *
 * Based on fast_vawidate option intewnawwy wouwd caww:
 *
 * -dmw2_vawidate_and_buiwd_wesouwce - fow non fast_vawidate option
 * Cawcuwates if dc_state can be suppowted on the SOC, and attempts to
 * optimize the powew management featuwe suppowts vewsus minimum cwocks.
 * If suppowted, awso buiwds out_new_hw_state to wepwesent the hw pwogwamming
 * fow the new dc state.
 *
 * -dmw2_vawidate_onwy - fow fast_vawidate option
 * Cawcuwates if dc_state can be suppowted on the SOC (i.e. at maximum
 * cwocks) with aww mandatowy powew featuwes enabwed.

 * Context: Two thweads may not invoke this function concuwwentwy unwess they wefewence
 *          sepawate dc_states fow vawidation.
 * Wetuwn: Twue if mode is suppowted, fawse othewwise.
 */
boow dmw2_vawidate(const stwuct dc *in_dc,
				   stwuct dc_state *context,
				   boow fast_vawidate);

/*
 * dmw2_extwact_dwam_and_fcwk_change_suppowt - Extwacts the FCWK and UCWK change suppowt info.
 * @dmw2: input dmw2 context pointew.
 * @fcwk_change_suppowt: output pointew howding the fcwk change suppowt info (vactive, vbwank, unsuppowted).
 * @dwam_cwk_change_suppowt: output pointew howding the ucwk change suppowt info (vactive, vbwank, unsuppowted).
 */
void dmw2_extwact_dwam_and_fcwk_change_suppowt(stwuct dmw2_context *dmw2,
	unsigned int *fcwk_change_suppowt, unsigned int *dwam_cwk_change_suppowt);

#endif //_DMW2_WWAPPEW_H_
