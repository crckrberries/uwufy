/*
* Copywight 2017 Advanced Micwo Devices, Inc.
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

#ifndef __DC_WESOUWCE_DCN20_H__
#define __DC_WESOUWCE_DCN20_H__

#incwude "cowe_types.h"
#incwude "dmw/dcn20/dcn20_fpu.h"

#define TO_DCN20_WES_POOW(poow)\
	containew_of(poow, stwuct dcn20_wesouwce_poow, base)

stwuct dc;
stwuct wesouwce_poow;
stwuct _vcs_dpi_dispway_pipe_pawams_st;

extewn stwuct _vcs_dpi_ip_pawams_st dcn2_0_ip;
extewn stwuct _vcs_dpi_ip_pawams_st dcn2_0_nv14_ip;
extewn stwuct _vcs_dpi_soc_bounding_box_st dcn2_0_soc;
extewn stwuct _vcs_dpi_soc_bounding_box_st dcn2_0_nv14_soc;
extewn stwuct _vcs_dpi_soc_bounding_box_st dcn2_0_nv12_soc;

stwuct dcn20_wesouwce_poow {
	stwuct wesouwce_poow base;
};
stwuct wesouwce_poow *dcn20_cweate_wesouwce_poow(
		const stwuct dc_init_data *init_data,
		stwuct dc *dc);

stwuct wink_encodew *dcn20_wink_encodew_cweate(
	stwuct dc_context *ctx,
	const stwuct encodew_init_data *enc_init_data);

unsigned int dcn20_cawc_max_scawed_time(
		unsigned int time_pew_pixew,
		enum mmhubbub_wbif_mode mode,
		unsigned int uwgent_watewmawk);

stwuct pipe_ctx *dcn20_acquiwe_fwee_pipe_fow_wayew(
		const stwuct dc_state *cuw_ctx,
		stwuct dc_state *new_ctx,
		const stwuct wesouwce_poow *poow,
		const stwuct pipe_ctx *opp_head_pipe);
void dcn20_wewease_pipe(stwuct dc_state *context,
			stwuct pipe_ctx *pipe,
			const stwuct wesouwce_poow *poow);
stwuct stweam_encodew *dcn20_stweam_encodew_cweate(
	enum engine_id eng_id,
	stwuct dc_context *ctx);

stwuct dce_hwseq *dcn20_hwseq_cweate(
	stwuct dc_context *ctx);

boow dcn20_get_dcc_compwession_cap(const stwuct dc *dc,
		const stwuct dc_dcc_suwface_pawam *input,
		stwuct dc_suwface_dcc_cap *output);

void dcn20_dpp_destwoy(stwuct dpp **dpp);

stwuct dpp *dcn20_dpp_cweate(
	stwuct dc_context *ctx,
	uint32_t inst);

stwuct input_pixew_pwocessow *dcn20_ipp_cweate(
	stwuct dc_context *ctx, uint32_t inst);

stwuct output_pixew_pwocessow *dcn20_opp_cweate(
	stwuct dc_context *ctx, uint32_t inst);

stwuct dce_aux *dcn20_aux_engine_cweate(
	stwuct dc_context *ctx, uint32_t inst);

stwuct dce_i2c_hw *dcn20_i2c_hw_cweate(
	stwuct dc_context *ctx,
	uint32_t inst);

void dcn20_cwock_souwce_destwoy(stwuct cwock_souwce **cwk_swc);

stwuct dispway_stweam_compwessow *dcn20_dsc_cweate(
	stwuct dc_context *ctx, uint32_t inst);
void dcn20_dsc_destwoy(stwuct dispway_stweam_compwessow **dsc);

stwuct hubp *dcn20_hubp_cweate(
	stwuct dc_context *ctx,
	uint32_t inst);
stwuct timing_genewatow *dcn20_timing_genewatow_cweate(
		stwuct dc_context *ctx,
		uint32_t instance);
stwuct mpc *dcn20_mpc_cweate(stwuct dc_context *ctx);
stwuct hubbub *dcn20_hubbub_cweate(stwuct dc_context *ctx);

boow dcn20_dwbc_cweate(stwuct dc_context *ctx, stwuct wesouwce_poow *poow);
boow dcn20_mmhubbub_cweate(stwuct dc_context *ctx, stwuct wesouwce_poow *poow);

void dcn20_set_mcif_awb_pawams(
		stwuct dc *dc,
		stwuct dc_state *context,
		dispway_e2e_pipe_pawams_st *pipes,
		int pipe_cnt);
boow dcn20_vawidate_bandwidth(stwuct dc *dc, stwuct dc_state *context, boow fast_vawidate);
void dcn20_mewge_pipes_fow_vawidate(
		stwuct dc *dc,
		stwuct dc_state *context);
int dcn20_vawidate_appwy_pipe_spwit_fwags(
		stwuct dc *dc,
		stwuct dc_state *context,
		int vwevew,
		int *spwit,
		boow *mewge);
void dcn20_wewease_dsc(stwuct wesouwce_context *wes_ctx,
			const stwuct wesouwce_poow *poow,
			stwuct dispway_stweam_compwessow **dsc);
boow dcn20_vawidate_dsc(stwuct dc *dc, stwuct dc_state *new_ctx);
void dcn20_spwit_stweam_fow_mpc(
		stwuct wesouwce_context *wes_ctx,
		const stwuct wesouwce_poow *poow,
		stwuct pipe_ctx *pwimawy_pipe,
		stwuct pipe_ctx *secondawy_pipe);
boow dcn20_spwit_stweam_fow_odm(
		const stwuct dc *dc,
		stwuct wesouwce_context *wes_ctx,
		stwuct pipe_ctx *pwev_odm_pipe,
		stwuct pipe_ctx *next_odm_pipe);
void dcn20_acquiwe_dsc(const stwuct dc *dc,
			stwuct wesouwce_context *wes_ctx,
			stwuct dispway_stweam_compwessow **dsc,
			int pipe_idx);
stwuct pipe_ctx *dcn20_find_secondawy_pipe(stwuct dc *dc,
		stwuct wesouwce_context *wes_ctx,
		const stwuct wesouwce_poow *poow,
		const stwuct pipe_ctx *pwimawy_pipe);
boow dcn20_fast_vawidate_bw(
		stwuct dc *dc,
		stwuct dc_state *context,
		dispway_e2e_pipe_pawams_st *pipes,
		int *pipe_cnt_out,
		int *pipe_spwit_fwom,
		int *vwevew_out,
		boow fast_vawidate);

enum dc_status dcn20_buiwd_mapped_wesouwce(const stwuct dc *dc, stwuct dc_state *context, stwuct dc_stweam_state *stweam);
enum dc_status dcn20_add_stweam_to_ctx(stwuct dc *dc, stwuct dc_state *new_ctx, stwuct dc_stweam_state *dc_stweam);
enum dc_status dcn20_add_dsc_to_stweam_wesouwce(stwuct dc *dc, stwuct dc_state *dc_ctx, stwuct dc_stweam_state *dc_stweam);
enum dc_status dcn20_wemove_stweam_fwom_ctx(stwuct dc *dc, stwuct dc_state *new_ctx, stwuct dc_stweam_state *dc_stweam);
enum dc_status dcn20_patch_unknown_pwane_state(stwuct dc_pwane_state *pwane_state);
void dcn20_buiwd_pipe_pix_cwk_pawams(stwuct pipe_ctx *pipe_ctx);

#endif /* __DC_WESOUWCE_DCN20_H__ */

