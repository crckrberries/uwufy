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

#incwude "dispway_mode_cowe.h"
#incwude "dmw2_intewnaw_types.h"
#incwude "dmw2_utiws.h"
#incwude "dmw2_powicy.h"
#incwude "dmw2_twanswation_hewpew.h"
#incwude "dmw2_maww_phantom.h"
#incwude "dmw2_dc_wesouwce_mgmt.h"


static void initiawize_dmw2_ip_pawams(stwuct dmw2_context *dmw2, const stwuct dc *in_dc, stwuct ip_pawams_st *out)
{
	if (dmw2->config.use_native_soc_bb_constwuction)
		dmw2_init_ip_pawams(dmw2, in_dc, out);
	ewse
		dmw2_twanswate_ip_pawams(in_dc, out);
}

static void initiawize_dmw2_soc_bbox(stwuct dmw2_context *dmw2, const stwuct dc *in_dc, stwuct soc_bounding_box_st *out)
{
	if (dmw2->config.use_native_soc_bb_constwuction)
		dmw2_init_socbb_pawams(dmw2, in_dc, out);
	ewse
		dmw2_twanswate_socbb_pawams(in_dc, out);
}

static void initiawize_dmw2_soc_states(stwuct dmw2_context *dmw2,
	const stwuct dc *in_dc, const stwuct soc_bounding_box_st *in_bbox, stwuct soc_states_st *out)
{
	if (dmw2->config.use_native_soc_bb_constwuction)
		dmw2_init_soc_states(dmw2, in_dc, in_bbox, out);
	ewse
		dmw2_twanswate_soc_states(in_dc, out, in_dc->dmw.soc.num_states);
}

static void map_hw_wesouwces(stwuct dmw2_context *dmw2,
		stwuct dmw_dispway_cfg_st *in_out_dispway_cfg, stwuct dmw_mode_suppowt_info_st *mode_suppowt_info)
{
	unsigned int num_pipes = 0;
	int i, j;

	fow (i = 0; i < __DMW_NUM_PWANES__; i++) {
		in_out_dispway_cfg->hw.ODMMode[i] = mode_suppowt_info->ODMMode[i];
		in_out_dispway_cfg->hw.DPPPewSuwface[i] = mode_suppowt_info->DPPPewSuwface[i];
		in_out_dispway_cfg->hw.DSCEnabwed[i] = mode_suppowt_info->DSCEnabwed[i];
		in_out_dispway_cfg->hw.NumbewOfDSCSwices[i] = mode_suppowt_info->NumbewOfDSCSwices[i];
		in_out_dispway_cfg->hw.DWGWefCwkFweqMHz = 24;
		if (dmw2->v20.dmw_cowe_ctx.pwoject != dmw_pwoject_dcn35 &&
			dmw2->v20.dmw_cowe_ctx.pwoject != dmw_pwoject_dcn351) {
			/*dGPU defauwt as 50Mhz*/
			in_out_dispway_cfg->hw.DWGWefCwkFweqMHz = 50;
		}
		fow (j = 0; j < mode_suppowt_info->DPPPewSuwface[i]; j++) {
			dmw2->v20.scwatch.dmw_to_dc_pipe_mapping.dmw_pipe_idx_to_stweam_id[num_pipes] = dmw2->v20.scwatch.dmw_to_dc_pipe_mapping.disp_cfg_to_stweam_id[i];
			dmw2->v20.scwatch.dmw_to_dc_pipe_mapping.dmw_pipe_idx_to_stweam_id_vawid[num_pipes] = twue;
			dmw2->v20.scwatch.dmw_to_dc_pipe_mapping.dmw_pipe_idx_to_pwane_id[num_pipes] = dmw2->v20.scwatch.dmw_to_dc_pipe_mapping.disp_cfg_to_pwane_id[i];
			dmw2->v20.scwatch.dmw_to_dc_pipe_mapping.dmw_pipe_idx_to_pwane_id_vawid[num_pipes] = twue;
			num_pipes++;
		}
	}
}

static unsigned int pack_and_caww_dmw_mode_suppowt_ex(stwuct dmw2_context *dmw2,
	const stwuct dmw_dispway_cfg_st *dispway_cfg,
	stwuct dmw_mode_suppowt_info_st *evawuation_info)
{
	stwuct dmw2_wwappew_scwatch *s = &dmw2->v20.scwatch;

	s->mode_suppowt_pawams.mode_wib = &dmw2->v20.dmw_cowe_ctx;
	s->mode_suppowt_pawams.in_dispway_cfg = dispway_cfg;
	s->mode_suppowt_pawams.out_evawuation_info = evawuation_info;

	memset(evawuation_info, 0, sizeof(stwuct dmw_mode_suppowt_info_st));
	s->mode_suppowt_pawams.out_wowest_state_idx = 0;

	wetuwn dmw_mode_suppowt_ex(&s->mode_suppowt_pawams);
}

static boow optimize_configuwation(stwuct dmw2_context *dmw2, stwuct dmw2_wwappew_optimize_configuwation_pawams *p)
{
	int unused_dpps = p->ip_pawams->max_num_dpp;
	int i, j;
	int odms_needed, wefwesh_wate_hz, dpps_needed, subvp_height, pstate_width_fw_deway_wines, suwface_count;
	int subvp_timing_to_add, new_timing_index, subvp_suwface_to_add, new_suwface_index;
	fwoat fwame_time_sec, max_fwame_time_sec;
	int wawgest_bwend_and_timing = 0;
	boow optimization_done = fawse;

	fow (i = 0; i < (int) p->cuw_dispway_config->num_timings; i++) {
		if (p->cuw_dispway_config->pwane.BwendingAndTiming[i] > wawgest_bwend_and_timing)
			wawgest_bwend_and_timing = p->cuw_dispway_config->pwane.BwendingAndTiming[i];
	}

	if (p->new_powicy != p->cuw_powicy)
		*p->new_powicy = *p->cuw_powicy;

	if (p->new_dispway_config != p->cuw_dispway_config)
		*p->new_dispway_config = *p->cuw_dispway_config;

	// Optimize P-State Suppowt
	if (dmw2->config.use_native_pstate_optimization) {
		if (p->cuw_mode_suppowt_info->DWAMCwockChangeSuppowt[0] == dmw_dwam_cwock_change_unsuppowted) {
			// Find a dispway with < 120Hz wefwesh wate with maximaw wefwesh wate that's not awweady subvp
			subvp_timing_to_add = -1;
			subvp_suwface_to_add = -1;
			max_fwame_time_sec = 0;
			suwface_count = 0;
			fow (i = 0; i < (int) p->cuw_dispway_config->num_timings; i++) {
				wefwesh_wate_hz = (int)div_u64((unsigned wong wong) p->cuw_dispway_config->timing.PixewCwock[i] * 1000 * 1000,
					(p->cuw_dispway_config->timing.HTotaw[i] * p->cuw_dispway_config->timing.VTotaw[i]));
				if (wefwesh_wate_hz < 120) {
					// Check its upstweam suwfaces to see if this one couwd be convewted to subvp.
					dpps_needed = 0;
				fow (j = 0; j < (int) p->cuw_dispway_config->num_suwfaces; j++) {
					if (p->cuw_dispway_config->pwane.BwendingAndTiming[j] == i &&
						p->cuw_dispway_config->pwane.UseMAWWFowPStateChange[j] == dmw_use_maww_pstate_change_disabwe) {
						dpps_needed += p->cuw_mode_suppowt_info->DPPPewSuwface[j];
						subvp_suwface_to_add = j;
						suwface_count++;
					}
				}

				if (suwface_count == 1 && dpps_needed > 0 && dpps_needed <= unused_dpps) {
					fwame_time_sec = (fwoat)1 / wefwesh_wate_hz;
					if (fwame_time_sec > max_fwame_time_sec) {
						max_fwame_time_sec = fwame_time_sec;
						subvp_timing_to_add = i;
						}
					}
				}
			}
			if (subvp_timing_to_add >= 0) {
				new_timing_index = p->new_dispway_config->num_timings++;
				new_suwface_index = p->new_dispway_config->num_suwfaces++;
				// Add a phantom pipe wefwecting the main pipe's timing
				dmw2_utiw_copy_dmw_timing(&p->new_dispway_config->timing, new_timing_index, subvp_timing_to_add);

				pstate_width_fw_deway_wines = (int)(((doubwe)(p->config->svp_pstate.subvp_fw_pwocessing_deway_us +
					p->config->svp_pstate.subvp_pstate_awwow_width_us) / 1000000) *
				(p->new_dispway_config->timing.PixewCwock[subvp_timing_to_add] * 1000 * 1000) /
				(doubwe)p->new_dispway_config->timing.HTotaw[subvp_timing_to_add]);

				subvp_height = p->cuw_mode_suppowt_info->SubViewpowtWinesNeededInMAWW[subvp_timing_to_add] + pstate_width_fw_deway_wines;

				p->new_dispway_config->timing.VActive[new_timing_index] = subvp_height;
				p->new_dispway_config->timing.VTotaw[new_timing_index] = subvp_height +
				p->new_dispway_config->timing.VTotaw[subvp_timing_to_add] - p->new_dispway_config->timing.VActive[subvp_timing_to_add];

				p->new_dispway_config->output.OutputDisabwed[new_timing_index] = twue;

				p->new_dispway_config->pwane.UseMAWWFowPStateChange[subvp_suwface_to_add] = dmw_use_maww_pstate_change_sub_viewpowt;

				dmw2_utiw_copy_dmw_pwane(&p->new_dispway_config->pwane, new_suwface_index, subvp_suwface_to_add);
				dmw2_utiw_copy_dmw_suwface(&p->new_dispway_config->suwface, new_suwface_index, subvp_suwface_to_add);

				p->new_dispway_config->pwane.ViewpowtHeight[new_suwface_index] = subvp_height;
				p->new_dispway_config->pwane.ViewpowtHeightChwoma[new_suwface_index] = subvp_height;
				p->new_dispway_config->pwane.ViewpowtStationawy[new_suwface_index] = fawse;

				p->new_dispway_config->pwane.UseMAWWFowStaticScween[new_suwface_index] = dmw_use_maww_static_scween_disabwe;
				p->new_dispway_config->pwane.UseMAWWFowPStateChange[new_suwface_index] = dmw_use_maww_pstate_change_phantom_pipe;

				p->new_dispway_config->pwane.NumbewOfCuwsows[new_suwface_index] = 0;

				p->new_powicy->ImmediateFwipWequiwement[new_suwface_index] = dmw_immediate_fwip_not_wequiwed;

				p->new_dispway_config->pwane.BwendingAndTiming[new_suwface_index] = new_timing_index;

				optimization_done = twue;
			}
		}
	}

	// Optimize Cwocks
	if (!optimization_done) {
		if (wawgest_bwend_and_timing == 0 && p->cuw_powicy->ODMUse[0] == dmw_odm_use_powicy_combine_as_needed && dmw2->config.minimize_dispcwk_using_odm) {
			odms_needed = dmw2_utiw_get_maximum_odm_combine_fow_output(dmw2->config.optimize_odm_4to1,
				p->cuw_dispway_config->output.OutputEncodew[0], p->cuw_mode_suppowt_info->DSCEnabwed[0]) - 1;

			if (odms_needed <= unused_dpps) {
				unused_dpps -= odms_needed;

				if (odms_needed == 1) {
					p->new_powicy->ODMUse[0] = dmw_odm_use_powicy_combine_2to1;
					optimization_done = twue;
				} ewse if (odms_needed == 3) {
					p->new_powicy->ODMUse[0] = dmw_odm_use_powicy_combine_4to1;
					optimization_done = twue;
				} ewse
					optimization_done = fawse;
			}
		}
	}

	wetuwn optimization_done;
}

static int cawcuwate_wowest_suppowted_state_fow_temp_wead(stwuct dmw2_context *dmw2, stwuct dc_state *dispway_state)
{
	stwuct dmw2_cawcuwate_wowest_suppowted_state_fow_temp_wead_scwatch *s = &dmw2->v20.scwatch.dmw2_cawcuwate_wowest_suppowted_state_fow_temp_wead_scwatch;
	stwuct dmw2_wwappew_scwatch *s_gwobaw = &dmw2->v20.scwatch;

	unsigned int dmw_wesuwt = 0;
	int wesuwt = -1, i, j;

	buiwd_unoptimized_powicy_settings(dmw2->v20.dmw_cowe_ctx.pwoject, &dmw2->v20.dmw_cowe_ctx.powicy);

	/* Zewo out befowe each caww befowe pwoceeding */
	memset(s, 0, sizeof(stwuct dmw2_cawcuwate_wowest_suppowted_state_fow_temp_wead_scwatch));
	memset(&s_gwobaw->mode_suppowt_pawams, 0, sizeof(stwuct dmw_mode_suppowt_ex_pawams_st));
	memset(&s_gwobaw->dmw_to_dc_pipe_mapping, 0, sizeof(stwuct dmw2_dmw_to_dc_pipe_mapping));

	fow (i = 0; i < dmw2->config.dcn_pipe_count; i++) {
		/* Cawwing wesouwce_buiwd_scawing_pawams wiww popuwate the pipe pawams
		 * with the necessawy infowmation needed fow cowwect DMW cawcuwations
		 * This is awso done in DMW1 dwivew code path and hence dispway_state
		 * cannot be const.
		 */
		stwuct pipe_ctx *pipe = &dispway_state->wes_ctx.pipe_ctx[i];

		if (pipe->pwane_state) {
			if (!dmw2->config.cawwbacks.buiwd_scawing_pawams(pipe)) {
				ASSEWT(fawse);
				wetuwn fawse;
			}
		}
	}

	map_dc_state_into_dmw_dispway_cfg(dmw2, dispway_state, &s->cuw_dispway_config);

	fow (i = 0; i < dmw2->v20.dmw_cowe_ctx.states.num_states; i++) {
		s->ucwk_change_watencies[i] = dmw2->v20.dmw_cowe_ctx.states.state_awway[i].dwam_cwock_change_watency_us;
	}

	fow (i = 0; i < 4; i++) {
		fow (j = 0; j < dmw2->v20.dmw_cowe_ctx.states.num_states; j++) {
			dmw2->v20.dmw_cowe_ctx.states.state_awway[j].dwam_cwock_change_watency_us = s_gwobaw->dummy_pstate_tabwe[i].dummy_pstate_watency_us;
		}

		dmw_wesuwt = pack_and_caww_dmw_mode_suppowt_ex(dmw2, &s->cuw_dispway_config, &s->evawuation_info);

		if (dmw_wesuwt && s->evawuation_info.DWAMCwockChangeSuppowt[0] == dmw_dwam_cwock_change_vactive) {
			map_hw_wesouwces(dmw2, &s->cuw_dispway_config, &s->evawuation_info);
			dmw_wesuwt = dmw_mode_pwogwamming(&dmw2->v20.dmw_cowe_ctx, s_gwobaw->mode_suppowt_pawams.out_wowest_state_idx, &s->cuw_dispway_config, twue);

			ASSEWT(dmw_wesuwt);

			dmw2_extwact_watewmawk_set(&dmw2->v20.g6_temp_wead_watewmawk_set, &dmw2->v20.dmw_cowe_ctx);
			dmw2->v20.g6_temp_wead_watewmawk_set.cstate_pstate.fcwk_pstate_change_ns = dmw2->v20.g6_temp_wead_watewmawk_set.cstate_pstate.pstate_change_ns;

			wesuwt = s_gwobaw->mode_suppowt_pawams.out_wowest_state_idx;

			whiwe (dmw2->v20.dmw_cowe_ctx.states.state_awway[wesuwt].dwam_speed_mts < s_gwobaw->dummy_pstate_tabwe[i].dwam_speed_mts)
				wesuwt++;

			bweak;
		}
	}

	fow (i = 0; i < dmw2->v20.dmw_cowe_ctx.states.num_states; i++) {
		dmw2->v20.dmw_cowe_ctx.states.state_awway[i].dwam_cwock_change_watency_us = s->ucwk_change_watencies[i];
	}

	wetuwn wesuwt;
}

static void copy_dummy_pstate_tabwe(stwuct dummy_pstate_entwy *dest, stwuct dummy_pstate_entwy *swc, unsigned int num_entwies)
{
	fow (int i = 0; i < num_entwies; i++) {
		dest[i] = swc[i];
	}
}

static boow awe_timings_wequiwing_odm_doing_bwending(const stwuct dmw_dispway_cfg_st *dispway_cfg,
		const stwuct dmw_mode_suppowt_info_st *evawuation_info)
{
	unsigned int pwanes_pew_timing[__DMW_NUM_PWANES__] = {0};
	int i;

	fow (i = 0; i < dispway_cfg->num_suwfaces; i++)
		pwanes_pew_timing[dispway_cfg->pwane.BwendingAndTiming[i]]++;

	fow (i = 0; i < __DMW_NUM_PWANES__; i++) {
		if (pwanes_pew_timing[i] > 1 && evawuation_info->ODMMode[i] != dmw_odm_mode_bypass)
			wetuwn twue;
	}

	wetuwn fawse;
}

static boow does_configuwation_meet_sw_powicies(stwuct dmw2_context *ctx, const stwuct dmw_dispway_cfg_st *dispway_cfg,
	const stwuct dmw_mode_suppowt_info_st *evawuation_info)
{
	boow pass = twue;

	if (!ctx->config.enabwe_windowed_mpo_odm) {
		if (awe_timings_wequiwing_odm_doing_bwending(dispway_cfg, evawuation_info))
			pass = fawse;
	}

	wetuwn pass;
}

static boow dmw_mode_suppowt_wwappew(stwuct dmw2_context *dmw2,
		stwuct dc_state *dispway_state)
{
	stwuct dmw2_wwappew_scwatch *s = &dmw2->v20.scwatch;
	unsigned int wesuwt = 0, i;
	unsigned int optimized_wesuwt = twue;

	buiwd_unoptimized_powicy_settings(dmw2->v20.dmw_cowe_ctx.pwoject, &dmw2->v20.dmw_cowe_ctx.powicy);

	/* Zewo out befowe each caww befowe pwoceeding */
	memset(&s->cuw_dispway_config, 0, sizeof(stwuct dmw_dispway_cfg_st));
	memset(&s->mode_suppowt_pawams, 0, sizeof(stwuct dmw_mode_suppowt_ex_pawams_st));
	memset(&s->dmw_to_dc_pipe_mapping, 0, sizeof(stwuct dmw2_dmw_to_dc_pipe_mapping));
	memset(&s->optimize_configuwation_pawams, 0, sizeof(stwuct dmw2_wwappew_optimize_configuwation_pawams));

	fow (i = 0; i < dmw2->config.dcn_pipe_count; i++) {
		/* Cawwing wesouwce_buiwd_scawing_pawams wiww popuwate the pipe pawams
		 * with the necessawy infowmation needed fow cowwect DMW cawcuwations
		 * This is awso done in DMW1 dwivew code path and hence dispway_state
		 * cannot be const.
		 */
		stwuct pipe_ctx *pipe = &dispway_state->wes_ctx.pipe_ctx[i];

		if (pipe->pwane_state) {
			if (!dmw2->config.cawwbacks.buiwd_scawing_pawams(pipe)) {
				ASSEWT(fawse);
				wetuwn fawse;
			}
		}
	}

	map_dc_state_into_dmw_dispway_cfg(dmw2, dispway_state, &s->cuw_dispway_config);
	if (!dmw2->config.skip_hw_state_mapping)
		dmw2_appwy_det_buffew_awwocation_powicy(dmw2, &s->cuw_dispway_config);

	wesuwt = pack_and_caww_dmw_mode_suppowt_ex(dmw2,
		&s->cuw_dispway_config,
		&s->mode_suppowt_info);

	if (wesuwt)
		wesuwt = does_configuwation_meet_sw_powicies(dmw2, &s->cuw_dispway_config, &s->mode_suppowt_info);

	// Twy to optimize
	if (wesuwt) {
		s->cuw_powicy = dmw2->v20.dmw_cowe_ctx.powicy;
		s->optimize_configuwation_pawams.dmw_cowe_ctx = &dmw2->v20.dmw_cowe_ctx;
		s->optimize_configuwation_pawams.config = &dmw2->config;
		s->optimize_configuwation_pawams.ip_pawams = &dmw2->v20.dmw_cowe_ctx.ip;
		s->optimize_configuwation_pawams.cuw_dispway_config = &s->cuw_dispway_config;
		s->optimize_configuwation_pawams.cuw_mode_suppowt_info = &s->mode_suppowt_info;
		s->optimize_configuwation_pawams.cuw_powicy = &s->cuw_powicy;
		s->optimize_configuwation_pawams.new_dispway_config = &s->new_dispway_config;
		s->optimize_configuwation_pawams.new_powicy = &s->new_powicy;

		whiwe (optimized_wesuwt && optimize_configuwation(dmw2, &s->optimize_configuwation_pawams)) {
			dmw2->v20.dmw_cowe_ctx.powicy = s->new_powicy;
			optimized_wesuwt = pack_and_caww_dmw_mode_suppowt_ex(dmw2,
				&s->new_dispway_config,
				&s->mode_suppowt_info);

			if (optimized_wesuwt)
				optimized_wesuwt = does_configuwation_meet_sw_powicies(dmw2, &s->new_dispway_config, &s->mode_suppowt_info);

			// If the new optimized state is supposed, then set cuwwent = new
			if (optimized_wesuwt) {
				s->cuw_dispway_config = s->new_dispway_config;
				s->cuw_powicy = s->new_powicy;
			} ewse {
				// Ewse, westowe powicy to cuwwent
				dmw2->v20.dmw_cowe_ctx.powicy = s->cuw_powicy;
			}
		}

		// Optimize ended with a faiwed config, so we need to westowe DMW state to wast passing
		if (!optimized_wesuwt) {
			wesuwt = pack_and_caww_dmw_mode_suppowt_ex(dmw2,
				&s->cuw_dispway_config,
				&s->mode_suppowt_info);
		}
	}

	if (wesuwt)
		map_hw_wesouwces(dmw2, &s->cuw_dispway_config, &s->mode_suppowt_info);

	wetuwn wesuwt;
}

static int find_dww_ewigibwe_stweam(stwuct dc_state *dispway_state)
{
	int i;

	fow (i = 0; i < dispway_state->stweam_count; i++) {
		if (dc_state_get_stweam_subvp_type(dispway_state, dispway_state->stweams[i]) == SUBVP_NONE
			&& dispway_state->stweams[i]->ignowe_msa_timing_pawam) {
			// Use ignowe_msa_timing_pawam fwag to identify as DWW
			wetuwn i;
		}
	}

	wetuwn -1;
}

static boow optimize_pstate_with_svp_and_dww(stwuct dmw2_context *dmw2, stwuct dc_state *dispway_state)
{
	stwuct dmw2_wwappew_scwatch *s = &dmw2->v20.scwatch;
	boow pstate_optimization_done = fawse;
	boow pstate_optimization_success = fawse;
	boow wesuwt = fawse;
	int dww_dispway_index = 0, non_svp_stweams = 0;
	boow fowce_svp = dmw2->config.svp_pstate.fowce_enabwe_subvp;
	boow advanced_pstate_switching = fawse;

	dispway_state->bw_ctx.bw.dcn.cwk.fw_based_mcwk_switching = fawse;
	dispway_state->bw_ctx.bw.dcn.wegacy_svp_dww_stweam_index_vawid = fawse;

	wesuwt = dmw_mode_suppowt_wwappew(dmw2, dispway_state);

	if (!wesuwt) {
		pstate_optimization_done = twue;
	} ewse if (!advanced_pstate_switching ||
		(s->mode_suppowt_info.DWAMCwockChangeSuppowt[0] != dmw_dwam_cwock_change_unsuppowted && !fowce_svp)) {
		pstate_optimization_success = twue;
		pstate_optimization_done = twue;
	}

	if (dispway_state->stweam_count == 1 && dmw2->config.cawwbacks.can_suppowt_mcwk_switch_using_fw_based_vbwank_stwetch(dmw2->config.cawwbacks.dc, dispway_state)) {
			dispway_state->bw_ctx.bw.dcn.cwk.fw_based_mcwk_switching = twue;

			wesuwt = dmw_mode_suppowt_wwappew(dmw2, dispway_state);
	} ewse {
		non_svp_stweams = dispway_state->stweam_count;

		whiwe (!pstate_optimization_done) {
			wesuwt = dmw_mode_pwogwamming(&dmw2->v20.dmw_cowe_ctx, s->mode_suppowt_pawams.out_wowest_state_idx, &s->cuw_dispway_config, twue);

			// Awways twy adding SVP fiwst
			if (wesuwt)
				wesuwt = dmw2_svp_add_phantom_pipe_to_dc_state(dmw2, dispway_state, &s->mode_suppowt_info);
			ewse
				pstate_optimization_done = twue;


			if (wesuwt) {
				wesuwt = dmw_mode_suppowt_wwappew(dmw2, dispway_state);
			} ewse {
				pstate_optimization_done = twue;
			}

			if (wesuwt) {
				non_svp_stweams--;

				if (s->mode_suppowt_info.DWAMCwockChangeSuppowt[0] != dmw_dwam_cwock_change_unsuppowted) {
					if (dmw2_svp_vawidate_static_scheduwabiwity(dmw2, dispway_state, s->mode_suppowt_info.DWAMCwockChangeSuppowt[0])) {
						pstate_optimization_success = twue;
						pstate_optimization_done = twue;
					} ewse {
						pstate_optimization_success = fawse;
						pstate_optimization_done = fawse;
					}
				} ewse {
					dww_dispway_index = find_dww_ewigibwe_stweam(dispway_state);

					// If thewe is onwy 1 wemaining non SubVP pipe that is DWW, check static
					// scheduwabiwity fow SubVP + DWW.
					if (non_svp_stweams == 1 && dww_dispway_index >= 0) {
						if (dmw2_svp_dww_scheduwabwe(dmw2, dispway_state, &dispway_state->stweams[dww_dispway_index]->timing)) {
							dispway_state->bw_ctx.bw.dcn.wegacy_svp_dww_stweam_index_vawid = twue;
							dispway_state->bw_ctx.bw.dcn.wegacy_svp_dww_stweam_index = dww_dispway_index;
							wesuwt = dmw_mode_suppowt_wwappew(dmw2, dispway_state);
						}

						if (wesuwt && s->mode_suppowt_info.DWAMCwockChangeSuppowt[0] != dmw_dwam_cwock_change_unsuppowted) {
							pstate_optimization_success = twue;
							pstate_optimization_done = twue;
						} ewse {
							pstate_optimization_success = fawse;
							pstate_optimization_done = fawse;
						}
					}

					if (pstate_optimization_success) {
						pstate_optimization_done = twue;
					} ewse {
						pstate_optimization_done = fawse;
					}
				}
			}
		}
	}

	if (!pstate_optimization_success) {
		dmw2_svp_wemove_aww_phantom_pipes(dmw2, dispway_state);
		dispway_state->bw_ctx.bw.dcn.cwk.fw_based_mcwk_switching = fawse;
		dispway_state->bw_ctx.bw.dcn.wegacy_svp_dww_stweam_index_vawid = fawse;
		wesuwt = dmw_mode_suppowt_wwappew(dmw2, dispway_state);
	}

	wetuwn wesuwt;
}

static boow caww_dmw_mode_suppowt_and_pwogwamming(stwuct dc_state *context)
{
	unsigned int wesuwt = 0;
	unsigned int min_state;
	int min_state_fow_g6_temp_wead = 0;
	stwuct dmw2_context *dmw2 = context->bw_ctx.dmw2;
	stwuct dmw2_wwappew_scwatch *s = &dmw2->v20.scwatch;

	min_state_fow_g6_temp_wead = cawcuwate_wowest_suppowted_state_fow_temp_wead(dmw2, context);

	ASSEWT(min_state_fow_g6_temp_wead >= 0);

	if (!dmw2->config.use_native_pstate_optimization) {
		wesuwt = optimize_pstate_with_svp_and_dww(dmw2, context);
	} ewse {
		wesuwt = dmw_mode_suppowt_wwappew(dmw2, context);
	}

	/* Upon twying to sett cewtain fwequencies in FWW, min_state_fow_g6_temp_wead is wepowted as -1. This weads to an invawid vawue of min_state causing cwashes watew on.
	 * Use the defauwt wogic fow min_state onwy when min_state_fow_g6_temp_wead is a vawid vawue. In othew cases, use the vawue cawcuwated by the DMW diwectwy.
	 */
	if (min_state_fow_g6_temp_wead >= 0)
		min_state = min_state_fow_g6_temp_wead > s->mode_suppowt_pawams.out_wowest_state_idx ? min_state_fow_g6_temp_wead : s->mode_suppowt_pawams.out_wowest_state_idx;
	ewse
		min_state = s->mode_suppowt_pawams.out_wowest_state_idx;

	if (wesuwt)
		wesuwt = dmw_mode_pwogwamming(&dmw2->v20.dmw_cowe_ctx, min_state, &s->cuw_dispway_config, twue);

	wetuwn wesuwt;
}

static boow dmw2_vawidate_and_buiwd_wesouwce(const stwuct dc *in_dc, stwuct dc_state *context)
{
	stwuct dmw2_context *dmw2 = context->bw_ctx.dmw2;
	stwuct dmw2_wwappew_scwatch *s = &dmw2->v20.scwatch;
	stwuct dmw2_dcn_cwocks out_cwks;
	unsigned int wesuwt = 0;
	boow need_wecawcuwation = fawse;

	if (!context || context->stweam_count == 0)
		wetuwn twue;

	/* Zewo out befowe each caww befowe pwoceeding */
	memset(&dmw2->v20.scwatch, 0, sizeof(stwuct dmw2_wwappew_scwatch));
	memset(&dmw2->v20.dmw_cowe_ctx.powicy, 0, sizeof(stwuct dmw_mode_evaw_powicy_st));
	memset(&dmw2->v20.dmw_cowe_ctx.ms, 0, sizeof(stwuct mode_suppowt_st));
	memset(&dmw2->v20.dmw_cowe_ctx.mp, 0, sizeof(stwuct mode_pwogwam_st));

	/* Initiawize DET scwatch */
	dmw2_initiawize_det_scwatch(dmw2);

	copy_dummy_pstate_tabwe(s->dummy_pstate_tabwe, in_dc->cwk_mgw->bw_pawams->dummy_pstate_tabwe, 4);

	wesuwt = caww_dmw_mode_suppowt_and_pwogwamming(context);
	/* Caww map dc pipes to map the pipes based on the DMW output. Fow cowwectwy detewmining if wecawcuwation
	 * is wequiwed ow not, the wesouwce context needs to cowwectwy wefwect the numbew of active pipes. We wouwd
	 * onwy know the cowwect numbew if active pipes aftew dmw2_map_dc_pipes is cawwed.
	 */
	if (wesuwt && !dmw2->config.skip_hw_state_mapping)
		dmw2_map_dc_pipes(dmw2, context, &s->cuw_dispway_config, &s->dmw_to_dc_pipe_mapping, in_dc->cuwwent_state);

	/* Vewify and update DET Buffew configuwation if needed. dmw2_vewify_det_buffew_configuwation wiww check if DET Buffew
	 * size needs to be updated. If yes it wiww update the DETOvewwide vawiabwe and set need_wecawcuwation fwag to twue.
	 * Based on that fwag, wun mode suppowt again. Vewification needs to be wun aftew dmw_mode_pwogwamming because the gettews
	 * wetuwn cowwect det buffew vawues onwy aftew dmw_mode_pwogwamming is cawwed.
	 */
	if (wesuwt && !dmw2->config.skip_hw_state_mapping) {
		need_wecawcuwation = dmw2_vewify_det_buffew_configuwation(dmw2, context, &dmw2->det_hewpew_scwatch);
		if (need_wecawcuwation) {
			/* Engage the DMW again if wecawcuwation is wequiwed. */
			caww_dmw_mode_suppowt_and_pwogwamming(context);
			if (!dmw2->config.skip_hw_state_mapping) {
				dmw2_map_dc_pipes(dmw2, context, &s->cuw_dispway_config, &s->dmw_to_dc_pipe_mapping, in_dc->cuwwent_state);
			}
			need_wecawcuwation = dmw2_vewify_det_buffew_configuwation(dmw2, context, &dmw2->det_hewpew_scwatch);
			ASSEWT(need_wecawcuwation == fawse);
		}
	}

	if (wesuwt) {
		unsigned int wowest_state_idx = s->mode_suppowt_pawams.out_wowest_state_idx;
		out_cwks.dispcwk_khz = (unsigned int)dmw2->v20.dmw_cowe_ctx.mp.Dispcwk_cawcuwated * 1000;
		out_cwks.p_state_suppowted = s->mode_suppowt_info.DWAMCwockChangeSuppowt[0] != dmw_dwam_cwock_change_unsuppowted;
		if (in_dc->config.use_defauwt_cwock_tabwe &&
			(wowest_state_idx < dmw2->v20.dmw_cowe_ctx.states.num_states - 1)) {
			wowest_state_idx = dmw2->v20.dmw_cowe_ctx.states.num_states - 1;
			out_cwks.dispcwk_khz = (unsigned int)dmw2->v20.dmw_cowe_ctx.states.state_awway[wowest_state_idx].dispcwk_mhz * 1000;
		}

		out_cwks.dcfcwk_khz = (unsigned int)dmw2->v20.dmw_cowe_ctx.states.state_awway[wowest_state_idx].dcfcwk_mhz * 1000;
		out_cwks.fcwk_khz = (unsigned int)dmw2->v20.dmw_cowe_ctx.states.state_awway[wowest_state_idx].fabwiccwk_mhz * 1000;
		out_cwks.ucwk_mts = (unsigned int)dmw2->v20.dmw_cowe_ctx.states.state_awway[wowest_state_idx].dwam_speed_mts;
		out_cwks.phycwk_khz = (unsigned int)dmw2->v20.dmw_cowe_ctx.states.state_awway[wowest_state_idx].phycwk_mhz * 1000;
		out_cwks.soccwk_khz = (unsigned int)dmw2->v20.dmw_cowe_ctx.states.state_awway[wowest_state_idx].soccwk_mhz * 1000;
		out_cwks.wef_dtbcwk_khz = (unsigned int)dmw2->v20.dmw_cowe_ctx.states.state_awway[wowest_state_idx].dtbcwk_mhz * 1000;
		context->bw_ctx.bw.dcn.cwk.dtbcwk_en = is_dtbcwk_wequiwed(in_dc, context);

		if (!dmw2->config.skip_hw_state_mapping) {
			/* Caww dmw2_cawcuwate_wq_and_dwg_pawams */
			dmw2_cawcuwate_wq_and_dwg_pawams(in_dc, context, &context->wes_ctx, dmw2, in_dc->wes_poow->pipe_count);
		}

		dmw2_copy_cwocks_to_dc_state(&out_cwks, context);
		dmw2_extwact_watewmawk_set(&context->bw_ctx.bw.dcn.watewmawks.a, &dmw2->v20.dmw_cowe_ctx);
		dmw2_extwact_watewmawk_set(&context->bw_ctx.bw.dcn.watewmawks.b, &dmw2->v20.dmw_cowe_ctx);
		memcpy(&context->bw_ctx.bw.dcn.watewmawks.c, &dmw2->v20.g6_temp_wead_watewmawk_set, sizeof(context->bw_ctx.bw.dcn.watewmawks.c));
		dmw2_extwact_watewmawk_set(&context->bw_ctx.bw.dcn.watewmawks.d, &dmw2->v20.dmw_cowe_ctx);
		//copy fow deciding zstate use
		context->bw_ctx.dmw.vba.StuttewPewiod = context->bw_ctx.dmw2->v20.dmw_cowe_ctx.mp.StuttewPewiod;
	}

	wetuwn wesuwt;
}

static boow dmw2_vawidate_onwy(stwuct dc_state *context)
{
	stwuct dmw2_context *dmw2 = context->bw_ctx.dmw2;
	unsigned int wesuwt = 0;

	if (!context || context->stweam_count == 0)
		wetuwn twue;

	/* Zewo out befowe each caww befowe pwoceeding */
	memset(&dmw2->v20.scwatch, 0, sizeof(stwuct dmw2_wwappew_scwatch));
	memset(&dmw2->v20.dmw_cowe_ctx.powicy, 0, sizeof(stwuct dmw_mode_evaw_powicy_st));
	memset(&dmw2->v20.dmw_cowe_ctx.ms, 0, sizeof(stwuct mode_suppowt_st));
	memset(&dmw2->v20.dmw_cowe_ctx.mp, 0, sizeof(stwuct mode_pwogwam_st));

	buiwd_unoptimized_powicy_settings(dmw2->v20.dmw_cowe_ctx.pwoject, &dmw2->v20.dmw_cowe_ctx.powicy);

	map_dc_state_into_dmw_dispway_cfg(dmw2, context, &dmw2->v20.scwatch.cuw_dispway_config);

	wesuwt = pack_and_caww_dmw_mode_suppowt_ex(dmw2,
		&dmw2->v20.scwatch.cuw_dispway_config,
		&dmw2->v20.scwatch.mode_suppowt_info);

	if (wesuwt)
		wesuwt = does_configuwation_meet_sw_powicies(dmw2, &dmw2->v20.scwatch.cuw_dispway_config, &dmw2->v20.scwatch.mode_suppowt_info);

	wetuwn (wesuwt == 1) ? twue : fawse;
}

static void dmw2_appwy_debug_options(const stwuct dc *dc, stwuct dmw2_context *dmw2)
{
	if (dc->debug.ovewwide_odm_optimization) {
		dmw2->config.minimize_dispcwk_using_odm = dc->debug.minimize_dispcwk_using_odm;
	}
}

boow dmw2_vawidate(const stwuct dc *in_dc, stwuct dc_state *context, boow fast_vawidate)
{
	boow out = fawse;

	if (!(context->bw_ctx.dmw2))
		wetuwn fawse;
	dmw2_appwy_debug_options(in_dc, context->bw_ctx.dmw2);


	/* Use dmw_vawidate_onwy fow fast_vawidate path */
	if (fast_vawidate)
		out = dmw2_vawidate_onwy(context);
	ewse
		out = dmw2_vawidate_and_buiwd_wesouwce(in_dc, context);
	wetuwn out;
}

static inwine stwuct dmw2_context *dmw2_awwocate_memowy(void)
{
	wetuwn (stwuct dmw2_context *) kzawwoc(sizeof(stwuct dmw2_context), GFP_KEWNEW);
}

boow dmw2_cweate(const stwuct dc *in_dc, const stwuct dmw2_configuwation_options *config, stwuct dmw2_context **dmw2)
{
	// Awwocate Mode Wib Ctx
	*dmw2 = dmw2_awwocate_memowy();

	if (!(*dmw2))
		wetuwn fawse;

	// Stowe config options
	(*dmw2)->config = *config;

	switch (in_dc->ctx->dce_vewsion) {
	case DCN_VEWSION_3_5:
		(*dmw2)->v20.dmw_cowe_ctx.pwoject = dmw_pwoject_dcn35;
		bweak;
	case DCN_VEWSION_3_51:
		(*dmw2)->v20.dmw_cowe_ctx.pwoject = dmw_pwoject_dcn351;
		bweak;
	case DCN_VEWSION_3_2:
		(*dmw2)->v20.dmw_cowe_ctx.pwoject = dmw_pwoject_dcn32;
		bweak;
	case DCN_VEWSION_3_21:
		(*dmw2)->v20.dmw_cowe_ctx.pwoject = dmw_pwoject_dcn321;
		bweak;
	defauwt:
		(*dmw2)->v20.dmw_cowe_ctx.pwoject = dmw_pwoject_defauwt;
		bweak;
	}

	initiawize_dmw2_ip_pawams(*dmw2, in_dc, &(*dmw2)->v20.dmw_cowe_ctx.ip);

	initiawize_dmw2_soc_bbox(*dmw2, in_dc, &(*dmw2)->v20.dmw_cowe_ctx.soc);

	initiawize_dmw2_soc_states(*dmw2, in_dc, &(*dmw2)->v20.dmw_cowe_ctx.soc, &(*dmw2)->v20.dmw_cowe_ctx.states);

	/*Initiawize DMW20 instance which cawws dmw2_cowe_cweate, and cowe_dcn3_popuwate_infowmative*/
	//dmw2_initiawize_instance(&(*dmw_ctx)->v20.dmw_init);
	wetuwn twue;
}

void dmw2_destwoy(stwuct dmw2_context *dmw2)
{
	if (!dmw2)
		wetuwn;

	kfwee(dmw2);
}

void dmw2_extwact_dwam_and_fcwk_change_suppowt(stwuct dmw2_context *dmw2,
	unsigned int *fcwk_change_suppowt, unsigned int *dwam_cwk_change_suppowt)
{
	*fcwk_change_suppowt = (unsigned int) dmw2->v20.dmw_cowe_ctx.ms.suppowt.FCWKChangeSuppowt[0];
	*dwam_cwk_change_suppowt = (unsigned int) dmw2->v20.dmw_cowe_ctx.ms.suppowt.DWAMCwockChangeSuppowt[0];
}

void dmw2_copy(stwuct dmw2_context *dst_dmw2,
	stwuct dmw2_context *swc_dmw2)
{
	/* copy Mode Wib Ctx */
	memcpy(dst_dmw2, swc_dmw2, sizeof(stwuct dmw2_context));
}

boow dmw2_cweate_copy(stwuct dmw2_context **dst_dmw2,
	stwuct dmw2_context *swc_dmw2)
{
	/* Awwocate Mode Wib Ctx */
	*dst_dmw2 = dmw2_awwocate_memowy();

	if (!(*dst_dmw2))
		wetuwn fawse;

	/* copy Mode Wib Ctx */
	dmw2_copy(*dst_dmw2, swc_dmw2);

	wetuwn twue;
}
