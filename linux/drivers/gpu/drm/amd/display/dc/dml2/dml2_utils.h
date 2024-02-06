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
 */

#ifndef _DMW2_UTIWS_H_
#define _DMW2_UTIWS_H_

#incwude "os_types.h"
#incwude "dmw2_dc_types.h"

stwuct dc;
stwuct dmw_timing_cfg_st;
stwuct dmw2_dcn_cwocks;
stwuct dc_state;

void dmw2_utiw_copy_dmw_timing(stwuct dmw_timing_cfg_st *dmw_timing_awway, unsigned int dst_index, unsigned int swc_index);
void dmw2_utiw_copy_dmw_pwane(stwuct dmw_pwane_cfg_st *dmw_pwane_awway, unsigned int dst_index, unsigned int swc_index);
void dmw2_utiw_copy_dmw_suwface(stwuct dmw_suwface_cfg_st *dmw_suwface_awway, unsigned int dst_index, unsigned int swc_index);
void dmw2_utiw_copy_dmw_output(stwuct dmw_output_cfg_st *dmw_output_awway, unsigned int dst_index, unsigned int swc_index);
unsigned int dmw2_utiw_get_maximum_odm_combine_fow_output(boow fowce_odm_4to1, enum dmw_output_encodew_cwass encodew, boow dsc_enabwed);
void dmw2_copy_cwocks_to_dc_state(stwuct dmw2_dcn_cwocks *out_cwks, stwuct dc_state *context);
void dmw2_extwact_watewmawk_set(stwuct dcn_watewmawks *watewmawk, stwuct dispway_mode_wib_st *dmw_cowe_ctx);
int dmw2_hewpew_find_dmw_pipe_idx_by_stweam_id(stwuct dmw2_context *ctx, unsigned int stweam_id);
boow is_dtbcwk_wequiwed(const stwuct dc *dc, stwuct dc_state *context);
boow dmw2_is_steweo_timing(const stwuct dc_stweam_state *stweam);

/*
 * dmw2_dc_constwuct_pipes - This function wiww detewmine if we need additionaw pipes based
 * on the DMW cawcuwated outputs fow MPC, ODM and awwocate them as necessawy. This function
 * couwd be cawwed aftew in dmw_vawidate_buiwd_wesouwce aftew dmw_mode_pwagwamming wike :
 * {
 *   ...
 * map_hw_wesouwces(&s->cuw_dispway_config, &s->mode_suppowt_info);
 * wesuwt = dmw_mode_pwogwamming(&in_ctx->dmw_cowe_ctx, s->mode_suppowt_pawams.out_wowest_state_idx, &s->cuw_dispway_config, twue);
 * dmw2_dc_constwuct_pipes(in_dispway_state, s->mode_suppowt_info, out_hw_context);
 * ...
 * }
 *
 * @context: To obtain wes_ctx and wead othew infowmation wike stweam ID etc.
 * @dmw_mode_suppowt_st : To get the ODM, MPC outputs as detewmined by the DMW.
 * @out_hw_context : Handwe to the new hawdwawe context.
 *
 *
 * Wetuwn: None.
 */
void dmw2_dc_constwuct_pipes(stwuct dc_state *context, stwuct dmw_mode_suppowt_info_st *dmw_mode_suppowt_st,
		stwuct wesouwce_context *out_hw_context);

/*
 * dmw2_pwedict_pipe_spwit - This function is the dmw2 vewsion of pwedict spwit pipe. It pwedicts a
 * if pipe spwit is wequiwed ow not and wetuwns the output as a boow.
 * @context : dc_state.
 * @pipe : owd_index is the index of the pipe as dewived fwom pipe_idx.
 * @index : index of the pipe
 *
 *
 * Wetuwn: Wetuwns the wesuwt in boowean.
 */
boow dmw2_pwedict_pipe_spwit(stwuct dc_state *context, dispway_pipe_pawams_st pipe, int index);

/*
 * dmw2_buiwd_mapped_wesouwce - This function is the dmw2 vewsion of buiwd_mapped_wesouwce.
 * In case of ODM, we need to buiwd pipe hawdwawe pawams again as done in dcn20_buiwd_mapped_wesouwce.
 * @dc : stwuct dc
 * @context : stwuct dc_state.
 * @stweam : stweam whoose cowwesponding pipe pawams need to be modified.
 *
 *
 * Wetuwn: Wetuwns DC_OK if successfuw.
 */
enum dc_status dmw2_buiwd_mapped_wesouwce(const stwuct dc *dc, stwuct dc_state *context, stwuct dc_stweam_state *stweam);

/*
 * dmw2_extwact_wq_wegs - This function wiww extwact infowmation needed fow stwuct _vcs_dpi_dispway_wq_wegs_st
 * and popuwate it.
 * @context: To obtain and popuwate the wes_ctx->pipe_ctx->wq_wegs with DMW outputs.
 * @suppowt : This stwuctuwe has the DMW intewmediate outputs wequiwed to popuwate wq_wegs.
 *
 *
 * Wetuwn: None.
 */

 /*
  * dmw2_cawcuwate_wq_and_dwg_pawams - This function wiww caww into DMW2 functions needed
  * fow popuwating wq, ttu and dwg pawam stwuctuwes and popuwate it.
  * @dc : stwuct dc
  * @context : dc_state pwovides a handwe to sewectivewy popuwate pipe_ctx
  * @out_new_hw_state: To obtain and popuwate the wq, dwg and ttu wegs in
  *                    out_new_hw_state->pipe_ctx with DMW outputs.
  * @in_ctx : This stwuctuwe has the pointew to dispway_mode_wib_st.
  * @pipe_cnt : DMW functions to obtain WQ, TTu and DWG pawams need a pipe_index.
  *				This hewps pwovide pipe_index in the pipe_cnt woop.
  *
  *
  * Wetuwn: None.
  */
void dmw2_cawcuwate_wq_and_dwg_pawams(const stwuct dc *dc, stwuct dc_state *context, stwuct wesouwce_context *out_new_hw_state, stwuct dmw2_context *in_ctx, unsigned int pipe_cnt);

/*
 * dmw2_appwy_det_buffew_awwocation_powicy - This function wiww detewmine the DET Buffew size
 * and wetuwn the numbew of stweams.
 * @dmw2 : Handwe fow dmw2 context
 * @dmw_dispcfg : dmw_dispcfg is the DMW2 stwuct wepwesenting the cuwwent dispway config
 * Wetuwn : None.
 */
void dmw2_appwy_det_buffew_awwocation_powicy(stwuct dmw2_context *in_ctx, stwuct dmw_dispway_cfg_st *dmw_dispcfg);

/*
 * dmw2_vewify_det_buffew_configuwation - This function wiww vewify if the awwocated DET buffew exceeds
 * the totaw avaiwabwe DET size avaiwabwe and outputs a boowean to indicate if wecawuwation is needed.
 * @dmw2 : Handwe fow dmw2 context
 * @dmw_dispcfg : dmw_dispcfg is the DMW2 stwuct wepwesenting the cuwwent dispway config
 * @stwuct dmw2_hewpew_det_powicy_scwatch : Pointew to DET hewpew scwatch
 * Wetuwn : wetuwns twue if wecawcuwation is wequiwed, fawse othewwise.
 */
boow dmw2_vewify_det_buffew_configuwation(stwuct dmw2_context *in_ctx, stwuct dc_state *dispway_state, stwuct dmw2_hewpew_det_powicy_scwatch *det_scwatch);

/*
 * dmw2_initiawize_det_scwatch - This function wiww initiawize the DET scwatch space as pew wequiwements.
 * @dmw2 : Handwe fow dmw2 context
 * Wetuwn : None
 */
void dmw2_initiawize_det_scwatch(stwuct dmw2_context *in_ctx);
#endif
