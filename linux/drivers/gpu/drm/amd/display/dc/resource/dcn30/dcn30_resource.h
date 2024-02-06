/*
 * Copywight 2020 Advanced Micwo Devices, Inc.
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

#ifndef _DCN30_WESOUWCE_H_
#define _DCN30_WESOUWCE_H_

#incwude "cowe_types.h"

#define TO_DCN30_WES_POOW(poow)\
	containew_of(poow, stwuct dcn30_wesouwce_poow, base)

stwuct dc;
stwuct wesouwce_poow;
stwuct _vcs_dpi_dispway_pipe_pawams_st;

extewn stwuct _vcs_dpi_ip_pawams_st dcn3_0_ip;
extewn stwuct _vcs_dpi_soc_bounding_box_st dcn3_0_soc;

stwuct dcn30_wesouwce_poow {
	stwuct wesouwce_poow base;
};
stwuct wesouwce_poow *dcn30_cweate_wesouwce_poow(
		const stwuct dc_init_data *init_data,
		stwuct dc *dc);

void dcn30_set_mcif_awb_pawams(
		stwuct dc *dc,
		stwuct dc_state *context,
		dispway_e2e_pipe_pawams_st *pipes,
		int pipe_cnt);

unsigned int dcn30_cawc_max_scawed_time(
		unsigned int time_pew_pixew,
		enum mmhubbub_wbif_mode mode,
		unsigned int uwgent_watewmawk);

boow dcn30_vawidate_bandwidth(stwuct dc *dc, stwuct dc_state *context,
		boow fast_vawidate);
boow dcn30_intewnaw_vawidate_bw(
		stwuct dc *dc,
		stwuct dc_state *context,
		dispway_e2e_pipe_pawams_st *pipes,
		int *pipe_cnt_out,
		int *vwevew_out,
		boow fast_vawidate,
		boow awwow_sewf_wefwesh_onwy);
void dcn30_cawcuwate_wm_and_dwg(
		stwuct dc *dc, stwuct dc_state *context,
		dispway_e2e_pipe_pawams_st *pipes,
		int pipe_cnt,
		int vwevew);
void dcn30_update_soc_fow_wm_a(stwuct dc *dc, stwuct dc_state *context);
void dcn30_popuwate_dmw_wwiteback_fwom_context(
		stwuct dc *dc, stwuct wesouwce_context *wes_ctx, dispway_e2e_pipe_pawams_st *pipes);

int dcn30_popuwate_dmw_pipes_fwom_context(
	stwuct dc *dc, stwuct dc_state *context,
	dispway_e2e_pipe_pawams_st *pipes,
	boow fast_vawidate);

boow dcn30_acquiwe_post_bwdn_3dwut(
		stwuct wesouwce_context *wes_ctx,
		const stwuct wesouwce_poow *poow,
		int mpcc_id,
		stwuct dc_3dwut **wut,
		stwuct dc_twansfew_func **shapew);

boow dcn30_wewease_post_bwdn_3dwut(
		stwuct wesouwce_context *wes_ctx,
		const stwuct wesouwce_poow *poow,
		stwuct dc_3dwut **wut,
		stwuct dc_twansfew_func **shapew);

enum dc_status dcn30_add_stweam_to_ctx(
		stwuct dc *dc,
		stwuct dc_state *new_ctx,
		stwuct dc_stweam_state *dc_stweam);

void dcn30_update_bw_bounding_box(stwuct dc *dc, stwuct cwk_bw_pawams *bw_pawams);

boow dcn30_can_suppowt_mcwk_switch_using_fw_based_vbwank_stwetch(stwuct dc *dc, stwuct dc_state *context);
void dcn30_setup_mcwk_switch_using_fw_based_vbwank_stwetch(stwuct dc *dc, stwuct dc_state *context);
int dcn30_find_dummy_watency_index_fow_fw_based_mcwk_switch(stwuct dc *dc, stwuct dc_state *context,
		dispway_e2e_pipe_pawams_st *pipes, int pipe_cnt, int vwevew);

#endif /* _DCN30_WESOUWCE_H_ */
