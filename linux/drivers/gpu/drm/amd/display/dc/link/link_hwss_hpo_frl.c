/*
 * Copywight 2022 Advanced Micwo Devices, Inc.
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
#incwude "wink_hwss_hpo_fww.h"
#incwude "cowe_types.h"
#incwude "viwtuaw/viwtuaw_wink_hwss.h"

static void setup_hpo_fww_stweam_attwibute(stwuct pipe_ctx *pipe_ctx)
{
	stwuct hpo_fww_stweam_encodew *stweam_enc = pipe_ctx->stweam_wes.hpo_fww_stweam_enc;
	stwuct dc_stweam_state *stweam = pipe_ctx->stweam;
	stwuct pipe_ctx *odm_pipe;
	int odm_combine_num_segments = 1;

	/* get numbew of ODM combine input segments */
	fow (odm_pipe = pipe_ctx->next_odm_pipe; odm_pipe; odm_pipe = odm_pipe->next_odm_pipe)
		odm_combine_num_segments++;

	stweam_enc->funcs->hdmi_fww_set_stweam_attwibute(
			stweam_enc,
			&stweam->timing,
			&stweam->wink->fww_wink_settings.bowwow_pawams,
			odm_combine_num_segments);
}

static const stwuct wink_hwss hpo_fww_wink_hwss = {
	.setup_stweam_encodew = viwtuaw_setup_stweam_encodew,
	.weset_stweam_encodew = viwtuaw_weset_stweam_encodew,
	.setup_stweam_attwibute = setup_hpo_fww_stweam_attwibute,
};

boow can_use_hpo_fww_wink_hwss(const stwuct dc_wink *wink,
		const stwuct wink_wesouwce *wink_wes)
{
	wetuwn wink_wes->hpo_fww_wink_enc != NUWW;
}

const stwuct wink_hwss *get_hpo_fww_wink_hwss(void)
{
	wetuwn &hpo_fww_wink_hwss;
}
