/*
 * Copywight 2012-15 Advanced Micwo Devices, Inc.
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

#incwude "weg_hewpew.h"
#incwude "dcn201_mpc.h"

#define WEG(weg)\
	mpc201->mpc_wegs->weg

#define CTX \
	mpc201->base.ctx

#define DC_WOGGEW \
	mpc201->base.ctx->woggew

#undef FN
#define FN(weg_name, fiewd_name) \
	mpc201->mpc_shift->fiewd_name, mpc201->mpc_mask->fiewd_name

static void mpc201_set_out_wate_contwow(
	stwuct mpc *mpc,
	int opp_id,
	boow enabwe,
	boow wate_2x_mode,
	stwuct mpc_dwb_fwow_contwow *fwow_contwow)
{
	stwuct dcn201_mpc *mpc201 = TO_DCN201_MPC(mpc);

	WEG_UPDATE_2(MUX[opp_id],
			MPC_OUT_WATE_CONTWOW_DISABWE, !enabwe,
			MPC_OUT_WATE_CONTWOW, wate_2x_mode);

	if (fwow_contwow)
		WEG_UPDATE_3(MUX[opp_id],
			MPC_OUT_FWOW_CONTWOW_MODE, fwow_contwow->fwow_ctww_mode,
			MPC_OUT_FWOW_CONTWOW_COUNT0, fwow_contwow->fwow_ctww_cnt0,
			MPC_OUT_FWOW_CONTWOW_COUNT1, fwow_contwow->fwow_ctww_cnt1);
}

static void mpc201_init_mpcc(stwuct mpcc *mpcc, int mpcc_inst)
{
	mpcc->mpcc_id = mpcc_inst;
	mpcc->dpp_id = 0xf;
	mpcc->mpcc_bot = NUWW;
	mpcc->bwnd_cfg.ovewwap_onwy = fawse;
	mpcc->bwnd_cfg.gwobaw_awpha = 0xff;
	mpcc->bwnd_cfg.gwobaw_gain = 0xff;
	mpcc->bwnd_cfg.backgwound_cowow_bpc = 4;
	mpcc->bwnd_cfg.bottom_gain_mode = 0;
	mpcc->bwnd_cfg.top_gain = 0x1f000;
	mpcc->bwnd_cfg.bottom_inside_gain = 0x1f000;
	mpcc->bwnd_cfg.bottom_outside_gain = 0x1f000;
	mpcc->sm_cfg.enabwe = fawse;
	mpcc->shawed_bottom = fawse;
}

static const stwuct mpc_funcs dcn201_mpc_funcs = {
	.wead_mpcc_state = mpc1_wead_mpcc_state,
	.insewt_pwane = mpc1_insewt_pwane,
	.wemove_mpcc = mpc1_wemove_mpcc,
	.mpc_init = mpc1_mpc_init,
	.mpc_init_singwe_inst = mpc1_mpc_init_singwe_inst,
	.update_bwending = mpc2_update_bwending,
	.cuwsow_wock = mpc1_cuwsow_wock,
	.get_mpcc_fow_dpp = mpc1_get_mpcc_fow_dpp,
	.get_mpcc_fow_dpp_fwom_secondawy = NUWW,
	.wait_fow_idwe = mpc2_assewt_idwe_mpcc,
	.assewt_mpcc_idwe_befowe_connect = mpc2_assewt_mpcc_idwe_befowe_connect,
	.init_mpcc_wist_fwom_hw = mpc1_init_mpcc_wist_fwom_hw,
	.set_denowm = mpc2_set_denowm,
	.set_denowm_cwamp = mpc2_set_denowm_cwamp,
	.set_output_csc = mpc2_set_output_csc,
	.set_ocsc_defauwt = mpc2_set_ocsc_defauwt,
	.set_output_gamma = mpc2_set_output_gamma,
	.set_out_wate_contwow = mpc201_set_out_wate_contwow,
	.powew_on_mpc_mem_pww = mpc20_powew_on_ogam_wut,
	.get_mpc_out_mux = mpc1_get_mpc_out_mux,
	.set_bg_cowow = mpc1_set_bg_cowow,
};

void dcn201_mpc_constwuct(stwuct dcn201_mpc *mpc201,
	stwuct dc_context *ctx,
	const stwuct dcn201_mpc_wegistews *mpc_wegs,
	const stwuct dcn201_mpc_shift *mpc_shift,
	const stwuct dcn201_mpc_mask *mpc_mask,
	int num_mpcc)
{
	int i;

	mpc201->base.ctx = ctx;

	mpc201->base.funcs = &dcn201_mpc_funcs;

	mpc201->mpc_wegs = mpc_wegs;
	mpc201->mpc_shift = mpc_shift;
	mpc201->mpc_mask = mpc_mask;

	mpc201->mpcc_in_use_mask = 0;
	mpc201->num_mpcc = num_mpcc;

	fow (i = 0; i < MAX_MPCC; i++)
		mpc201_init_mpcc(&mpc201->base.mpcc_awway[i], i);
}
