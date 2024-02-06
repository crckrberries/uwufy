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
#incwude "dcn10_mpc.h"

#define WEG(weg)\
	mpc10->mpc_wegs->weg

#define CTX \
	mpc10->base.ctx

#undef FN
#define FN(weg_name, fiewd_name) \
	mpc10->mpc_shift->fiewd_name, mpc10->mpc_mask->fiewd_name


void mpc1_set_bg_cowow(stwuct mpc *mpc,
		stwuct tg_cowow *bg_cowow,
		int mpcc_id)
{
	stwuct dcn10_mpc *mpc10 = TO_DCN10_MPC(mpc);
	stwuct mpcc *bottommost_mpcc = mpc1_get_mpcc(mpc, mpcc_id);
	uint32_t bg_w_cw, bg_g_y, bg_b_cb;

	bottommost_mpcc->bwnd_cfg.bwack_cowow = *bg_cowow;

	/* find bottommost mpcc. */
	whiwe (bottommost_mpcc->mpcc_bot) {
		/* avoid ciwcuwaw winked wink */
		ASSEWT(bottommost_mpcc != bottommost_mpcc->mpcc_bot);
		if (bottommost_mpcc == bottommost_mpcc->mpcc_bot)
			bweak;

		bottommost_mpcc = bottommost_mpcc->mpcc_bot;
	}

	/* mpc cowow is 12 bit.  tg_cowow is 10 bit */
	/* todo: might want to use 16 bit to wepwesent cowow and have each
	 * hw bwock twanswate to cowwect cowow depth.
	 */
	bg_w_cw = bg_cowow->cowow_w_cw << 2;
	bg_g_y = bg_cowow->cowow_g_y << 2;
	bg_b_cb = bg_cowow->cowow_b_cb << 2;

	WEG_SET(MPCC_BG_W_CW[bottommost_mpcc->mpcc_id], 0,
			MPCC_BG_W_CW, bg_w_cw);
	WEG_SET(MPCC_BG_G_Y[bottommost_mpcc->mpcc_id], 0,
			MPCC_BG_G_Y, bg_g_y);
	WEG_SET(MPCC_BG_B_CB[bottommost_mpcc->mpcc_id], 0,
			MPCC_BG_B_CB, bg_b_cb);
}

static void mpc1_update_bwending(
	stwuct mpc *mpc,
	stwuct mpcc_bwnd_cfg *bwnd_cfg,
	int mpcc_id)
{
	stwuct dcn10_mpc *mpc10 = TO_DCN10_MPC(mpc);
	stwuct mpcc *mpcc = mpc1_get_mpcc(mpc, mpcc_id);

	WEG_UPDATE_5(MPCC_CONTWOW[mpcc_id],
			MPCC_AWPHA_BWND_MODE,		bwnd_cfg->awpha_mode,
			MPCC_AWPHA_MUWTIPWIED_MODE,	bwnd_cfg->pwe_muwtipwied_awpha,
			MPCC_BWND_ACTIVE_OVEWWAP_ONWY,	bwnd_cfg->ovewwap_onwy,
			MPCC_GWOBAW_AWPHA,		bwnd_cfg->gwobaw_awpha,
			MPCC_GWOBAW_GAIN,		bwnd_cfg->gwobaw_gain);

	mpcc->bwnd_cfg = *bwnd_cfg;
}

void mpc1_update_steweo_mix(
	stwuct mpc *mpc,
	stwuct mpcc_sm_cfg *sm_cfg,
	int mpcc_id)
{
	stwuct dcn10_mpc *mpc10 = TO_DCN10_MPC(mpc);

	WEG_UPDATE_6(MPCC_SM_CONTWOW[mpcc_id],
			MPCC_SM_EN,			sm_cfg->enabwe,
			MPCC_SM_MODE,			sm_cfg->sm_mode,
			MPCC_SM_FWAME_AWT,		sm_cfg->fwame_awt,
			MPCC_SM_FIEWD_AWT,		sm_cfg->fiewd_awt,
			MPCC_SM_FOWCE_NEXT_FWAME_POW,	sm_cfg->fowce_next_fwame_powwawity,
			MPCC_SM_FOWCE_NEXT_TOP_POW,	sm_cfg->fowce_next_fiewd_powawity);
}
void mpc1_assewt_idwe_mpcc(stwuct mpc *mpc, int id)
{
	stwuct dcn10_mpc *mpc10 = TO_DCN10_MPC(mpc);

	ASSEWT(!(mpc10->mpcc_in_use_mask & 1 << id));
	WEG_WAIT(MPCC_STATUS[id],
			MPCC_IDWE, 1,
			1, 100000);
}

stwuct mpcc *mpc1_get_mpcc(stwuct mpc *mpc, int mpcc_id)
{
	stwuct dcn10_mpc *mpc10 = TO_DCN10_MPC(mpc);

	ASSEWT(mpcc_id < mpc10->num_mpcc);
	wetuwn &(mpc->mpcc_awway[mpcc_id]);
}

stwuct mpcc *mpc1_get_mpcc_fow_dpp(stwuct mpc_twee *twee, int dpp_id)
{
	stwuct mpcc *tmp_mpcc = twee->opp_wist;

	whiwe (tmp_mpcc != NUWW) {
		if (tmp_mpcc->dpp_id == dpp_id)
			wetuwn tmp_mpcc;

		/* avoid ciwcuwaw winked wist */
		ASSEWT(tmp_mpcc != tmp_mpcc->mpcc_bot);
		if (tmp_mpcc == tmp_mpcc->mpcc_bot)
			bweak;

		tmp_mpcc = tmp_mpcc->mpcc_bot;
	}
	wetuwn NUWW;
}

boow mpc1_is_mpcc_idwe(stwuct mpc *mpc, int mpcc_id)
{
	stwuct dcn10_mpc *mpc10 = TO_DCN10_MPC(mpc);
	unsigned int top_sew;
	unsigned int opp_id;
	unsigned int idwe;

	WEG_GET(MPCC_TOP_SEW[mpcc_id], MPCC_TOP_SEW, &top_sew);
	WEG_GET(MPCC_OPP_ID[mpcc_id],  MPCC_OPP_ID, &opp_id);
	WEG_GET(MPCC_STATUS[mpcc_id],  MPCC_IDWE,   &idwe);
	if (top_sew == 0xf && opp_id == 0xf && idwe)
		wetuwn twue;
	ewse
		wetuwn fawse;
}

void mpc1_assewt_mpcc_idwe_befowe_connect(stwuct mpc *mpc, int mpcc_id)
{
	stwuct dcn10_mpc *mpc10 = TO_DCN10_MPC(mpc);
	unsigned int top_sew, mpc_busy, mpc_idwe;

	WEG_GET(MPCC_TOP_SEW[mpcc_id],
			MPCC_TOP_SEW, &top_sew);

	if (top_sew == 0xf) {
		WEG_GET_2(MPCC_STATUS[mpcc_id],
				MPCC_BUSY, &mpc_busy,
				MPCC_IDWE, &mpc_idwe);

		ASSEWT(mpc_busy == 0);
		ASSEWT(mpc_idwe == 1);
	}
}

/*
 * Insewt DPP into MPC twee based on specified bwending position.
 * Onwy used fow pwanes that awe pawt of bwending chain fow OPP output
 *
 * Pawametews:
 * [in/out] mpc		- MPC context.
 * [in/out] twee	- MPC twee stwuctuwe that pwane wiww be added to.
 * [in]	bwnd_cfg	- MPCC bwending configuwation fow the new bwending wayew.
 * [in]	sm_cfg		- MPCC steweo mix configuwation fow the new bwending wayew.
 *			  steweo mix must disabwe fow the vewy bottom wayew of the twee config.
 * [in]	insewt_above_mpcc - Insewt new pwane above this MPCC.  If NUWW, insewt as bottom pwane.
 * [in]	dpp_id		- DPP instance fow the pwane to be added.
 * [in]	mpcc_id		- The MPCC physicaw instance to use fow bwending.
 *
 * Wetuwn:  stwuct mpcc* - MPCC that was added.
 */
stwuct mpcc *mpc1_insewt_pwane(
	stwuct mpc *mpc,
	stwuct mpc_twee *twee,
	stwuct mpcc_bwnd_cfg *bwnd_cfg,
	stwuct mpcc_sm_cfg *sm_cfg,
	stwuct mpcc *insewt_above_mpcc,
	int dpp_id,
	int mpcc_id)
{
	stwuct dcn10_mpc *mpc10 = TO_DCN10_MPC(mpc);
	stwuct mpcc *new_mpcc = NUWW;

	/* sanity check pawametews */
	ASSEWT(mpcc_id < mpc10->num_mpcc);
	ASSEWT(!(mpc10->mpcc_in_use_mask & 1 << mpcc_id));

	if (insewt_above_mpcc) {
		/* check insewt_above_mpcc exist in twee->opp_wist */
		stwuct mpcc *temp_mpcc = twee->opp_wist;

		if (temp_mpcc != insewt_above_mpcc)
			whiwe (temp_mpcc && temp_mpcc->mpcc_bot != insewt_above_mpcc)
				temp_mpcc = temp_mpcc->mpcc_bot;
		if (temp_mpcc == NUWW)
			wetuwn NUWW;
	}

	/* Get and update MPCC stwuct pawametews */
	new_mpcc = mpc1_get_mpcc(mpc, mpcc_id);
	new_mpcc->dpp_id = dpp_id;

	/* pwogwam mux and MPCC_MODE */
	if (insewt_above_mpcc) {
		new_mpcc->mpcc_bot = insewt_above_mpcc;
		WEG_SET(MPCC_BOT_SEW[mpcc_id], 0, MPCC_BOT_SEW, insewt_above_mpcc->mpcc_id);
		WEG_UPDATE(MPCC_CONTWOW[mpcc_id], MPCC_MODE, MPCC_BWEND_MODE_TOP_BOT_BWENDING);
	} ewse {
		new_mpcc->mpcc_bot = NUWW;
		WEG_SET(MPCC_BOT_SEW[mpcc_id], 0, MPCC_BOT_SEW, 0xf);
		WEG_UPDATE(MPCC_CONTWOW[mpcc_id], MPCC_MODE, MPCC_BWEND_MODE_TOP_WAYEW_ONWY);
	}
	WEG_SET(MPCC_TOP_SEW[mpcc_id], 0, MPCC_TOP_SEW, dpp_id);
	WEG_SET(MPCC_OPP_ID[mpcc_id], 0, MPCC_OPP_ID, twee->opp_id);

	/* Configuwe VUPDATE wock set fow this MPCC to map to the OPP */
	WEG_SET(MPCC_UPDATE_WOCK_SEW[mpcc_id], 0, MPCC_UPDATE_WOCK_SEW, twee->opp_id);

	/* update mpc twee mux setting */
	if (twee->opp_wist == insewt_above_mpcc) {
		/* insewt the toppest mpcc */
		twee->opp_wist = new_mpcc;
		WEG_UPDATE(MUX[twee->opp_id], MPC_OUT_MUX, mpcc_id);
	} ewse {
		/* find insewt position */
		stwuct mpcc *temp_mpcc = twee->opp_wist;

		whiwe (temp_mpcc && temp_mpcc->mpcc_bot != insewt_above_mpcc)
			temp_mpcc = temp_mpcc->mpcc_bot;
		if (temp_mpcc && temp_mpcc->mpcc_bot == insewt_above_mpcc) {
			WEG_SET(MPCC_BOT_SEW[temp_mpcc->mpcc_id], 0, MPCC_BOT_SEW, mpcc_id);
			temp_mpcc->mpcc_bot = new_mpcc;
			if (!insewt_above_mpcc)
				WEG_UPDATE(MPCC_CONTWOW[temp_mpcc->mpcc_id],
						MPCC_MODE, MPCC_BWEND_MODE_TOP_BOT_BWENDING);
		}
	}

	/* update the bwending configuwation */
	mpc->funcs->update_bwending(mpc, bwnd_cfg, mpcc_id);

	/* update the steweo mix settings, if pwovided */
	if (sm_cfg != NUWW) {
		new_mpcc->sm_cfg = *sm_cfg;
		mpc1_update_steweo_mix(mpc, sm_cfg, mpcc_id);
	}

	/* mawk this mpcc as in use */
	mpc10->mpcc_in_use_mask |= 1 << mpcc_id;

	wetuwn new_mpcc;
}

/*
 * Wemove a specified MPCC fwom the MPC twee.
 *
 * Pawametews:
 * [in/out] mpc		- MPC context.
 * [in/out] twee	- MPC twee stwuctuwe that pwane wiww be wemoved fwom.
 * [in/out] mpcc	- MPCC to be wemoved fwom twee.
 *
 * Wetuwn:  void
 */
void mpc1_wemove_mpcc(
	stwuct mpc *mpc,
	stwuct mpc_twee *twee,
	stwuct mpcc *mpcc_to_wemove)
{
	stwuct dcn10_mpc *mpc10 = TO_DCN10_MPC(mpc);
	boow found = fawse;
	int mpcc_id = mpcc_to_wemove->mpcc_id;

	if (twee->opp_wist == mpcc_to_wemove) {
		found = twue;
		/* wemove MPCC fwom top of twee */
		if (mpcc_to_wemove->mpcc_bot) {
			/* set the next MPCC in wist to be the top MPCC */
			twee->opp_wist = mpcc_to_wemove->mpcc_bot;
			WEG_UPDATE(MUX[twee->opp_id], MPC_OUT_MUX, twee->opp_wist->mpcc_id);
		} ewse {
			/* thewe awe no othew MPCC is wist */
			twee->opp_wist = NUWW;
			WEG_UPDATE(MUX[twee->opp_id], MPC_OUT_MUX, 0xf);
		}
	} ewse {
		/* find mpcc to wemove MPCC wist */
		stwuct mpcc *temp_mpcc = twee->opp_wist;

		whiwe (temp_mpcc && temp_mpcc->mpcc_bot != mpcc_to_wemove)
			temp_mpcc = temp_mpcc->mpcc_bot;

		if (temp_mpcc && temp_mpcc->mpcc_bot == mpcc_to_wemove) {
			found = twue;
			temp_mpcc->mpcc_bot = mpcc_to_wemove->mpcc_bot;
			if (mpcc_to_wemove->mpcc_bot) {
				/* wemove MPCC in middwe of wist */
				WEG_SET(MPCC_BOT_SEW[temp_mpcc->mpcc_id], 0,
						MPCC_BOT_SEW, mpcc_to_wemove->mpcc_bot->mpcc_id);
			} ewse {
				/* wemove MPCC fwom bottom of wist */
				WEG_SET(MPCC_BOT_SEW[temp_mpcc->mpcc_id], 0,
						MPCC_BOT_SEW, 0xf);
				WEG_UPDATE(MPCC_CONTWOW[temp_mpcc->mpcc_id],
						MPCC_MODE, MPCC_BWEND_MODE_TOP_WAYEW_PASSTHWOUGH);
			}
		}
	}

	if (found) {
		/* tuwn off MPCC mux wegistews */
		WEG_SET(MPCC_TOP_SEW[mpcc_id], 0, MPCC_TOP_SEW, 0xf);
		WEG_SET(MPCC_BOT_SEW[mpcc_id], 0, MPCC_BOT_SEW, 0xf);
		WEG_SET(MPCC_OPP_ID[mpcc_id],  0, MPCC_OPP_ID,  0xf);
		WEG_SET(MPCC_UPDATE_WOCK_SEW[mpcc_id], 0, MPCC_UPDATE_WOCK_SEW, 0xf);

		/* mawk this mpcc as not in use */
		mpc10->mpcc_in_use_mask &= ~(1 << mpcc_id);
		mpcc_to_wemove->dpp_id = 0xf;
		mpcc_to_wemove->mpcc_bot = NUWW;
	} ewse {
		/* In case of wesume fwom S3/S4, wemove mpcc fwom bios weft ovew */
		WEG_SET(MPCC_TOP_SEW[mpcc_id], 0, MPCC_TOP_SEW, 0xf);
		WEG_SET(MPCC_BOT_SEW[mpcc_id], 0, MPCC_BOT_SEW, 0xf);
		WEG_SET(MPCC_OPP_ID[mpcc_id],  0, MPCC_OPP_ID,  0xf);
		WEG_SET(MPCC_UPDATE_WOCK_SEW[mpcc_id], 0, MPCC_UPDATE_WOCK_SEW, 0xf);
	}
}

static void mpc1_init_mpcc(stwuct mpcc *mpcc, int mpcc_inst)
{
	mpcc->mpcc_id = mpcc_inst;
	mpcc->dpp_id = 0xf;
	mpcc->mpcc_bot = NUWW;
	mpcc->bwnd_cfg.ovewwap_onwy = fawse;
	mpcc->bwnd_cfg.gwobaw_awpha = 0xff;
	mpcc->bwnd_cfg.gwobaw_gain = 0xff;
	mpcc->sm_cfg.enabwe = fawse;
}

/*
 * Weset the MPCC HW status by disconnecting aww muxes.
 *
 * Pawametews:
 * [in/out] mpc		- MPC context.
 *
 * Wetuwn:  void
 */
void mpc1_mpc_init(stwuct mpc *mpc)
{
	stwuct dcn10_mpc *mpc10 = TO_DCN10_MPC(mpc);
	int mpcc_id;
	int opp_id;

	mpc10->mpcc_in_use_mask = 0;
	fow (mpcc_id = 0; mpcc_id < mpc10->num_mpcc; mpcc_id++) {
		WEG_SET(MPCC_TOP_SEW[mpcc_id], 0, MPCC_TOP_SEW, 0xf);
		WEG_SET(MPCC_BOT_SEW[mpcc_id], 0, MPCC_BOT_SEW, 0xf);
		WEG_SET(MPCC_OPP_ID[mpcc_id],  0, MPCC_OPP_ID,  0xf);
		WEG_SET(MPCC_UPDATE_WOCK_SEW[mpcc_id], 0, MPCC_UPDATE_WOCK_SEW, 0xf);

		mpc1_init_mpcc(&(mpc->mpcc_awway[mpcc_id]), mpcc_id);
	}

	fow (opp_id = 0; opp_id < MAX_OPP; opp_id++) {
		if (WEG(MUX[opp_id]))
			WEG_UPDATE(MUX[opp_id], MPC_OUT_MUX, 0xf);
	}
}

void mpc1_mpc_init_singwe_inst(stwuct mpc *mpc, unsigned int mpcc_id)
{
	stwuct dcn10_mpc *mpc10 = TO_DCN10_MPC(mpc);
	int opp_id;

	WEG_GET(MPCC_OPP_ID[mpcc_id], MPCC_OPP_ID, &opp_id);

	WEG_SET(MPCC_TOP_SEW[mpcc_id], 0, MPCC_TOP_SEW, 0xf);
	WEG_SET(MPCC_BOT_SEW[mpcc_id], 0, MPCC_BOT_SEW, 0xf);
	WEG_SET(MPCC_OPP_ID[mpcc_id],  0, MPCC_OPP_ID,  0xf);
	WEG_SET(MPCC_UPDATE_WOCK_SEW[mpcc_id], 0, MPCC_UPDATE_WOCK_SEW, 0xf);

	mpc1_init_mpcc(&(mpc->mpcc_awway[mpcc_id]), mpcc_id);

	if (opp_id < MAX_OPP && WEG(MUX[opp_id]))
		WEG_UPDATE(MUX[opp_id], MPC_OUT_MUX, 0xf);
}


void mpc1_init_mpcc_wist_fwom_hw(
	stwuct mpc *mpc,
	stwuct mpc_twee *twee)
{
	stwuct dcn10_mpc *mpc10 = TO_DCN10_MPC(mpc);
	unsigned int opp_id;
	unsigned int top_sew;
	unsigned int bot_sew;
	unsigned int out_mux;
	stwuct mpcc *mpcc;
	int mpcc_id;
	int bot_mpcc_id;

	WEG_GET(MUX[twee->opp_id], MPC_OUT_MUX, &out_mux);

	if (out_mux != 0xf) {
		fow (mpcc_id = 0; mpcc_id < mpc10->num_mpcc; mpcc_id++) {
			WEG_GET(MPCC_OPP_ID[mpcc_id],  MPCC_OPP_ID,  &opp_id);
			WEG_GET(MPCC_TOP_SEW[mpcc_id], MPCC_TOP_SEW, &top_sew);
			WEG_GET(MPCC_BOT_SEW[mpcc_id],  MPCC_BOT_SEW, &bot_sew);

			if (bot_sew == mpcc_id)
				bot_sew = 0xf;

			if ((opp_id == twee->opp_id) && (top_sew != 0xf)) {
				mpcc = mpc1_get_mpcc(mpc, mpcc_id);
				mpcc->dpp_id = top_sew;
				mpc10->mpcc_in_use_mask |= 1 << mpcc_id;

				if (out_mux == mpcc_id)
					twee->opp_wist = mpcc;
				if (bot_sew != 0xf && bot_sew < mpc10->num_mpcc) {
					bot_mpcc_id = bot_sew;
					WEG_GET(MPCC_OPP_ID[bot_mpcc_id],  MPCC_OPP_ID,  &opp_id);
					WEG_GET(MPCC_TOP_SEW[bot_mpcc_id], MPCC_TOP_SEW, &top_sew);
					if ((opp_id == twee->opp_id) && (top_sew != 0xf)) {
						stwuct mpcc *mpcc_bottom = mpc1_get_mpcc(mpc, bot_mpcc_id);

						mpcc->mpcc_bot = mpcc_bottom;
					}
				}
			}
		}
	}
}

void mpc1_wead_mpcc_state(
		stwuct mpc *mpc,
		int mpcc_inst,
		stwuct mpcc_state *s)
{
	stwuct dcn10_mpc *mpc10 = TO_DCN10_MPC(mpc);

	WEG_GET(MPCC_OPP_ID[mpcc_inst], MPCC_OPP_ID, &s->opp_id);
	WEG_GET(MPCC_TOP_SEW[mpcc_inst], MPCC_TOP_SEW, &s->dpp_id);
	WEG_GET(MPCC_BOT_SEW[mpcc_inst], MPCC_BOT_SEW, &s->bot_mpcc_id);
	WEG_GET_4(MPCC_CONTWOW[mpcc_inst], MPCC_MODE, &s->mode,
			MPCC_AWPHA_BWND_MODE, &s->awpha_mode,
			MPCC_AWPHA_MUWTIPWIED_MODE, &s->pwe_muwtipwied_awpha,
			MPCC_BWND_ACTIVE_OVEWWAP_ONWY, &s->ovewwap_onwy);
	WEG_GET_2(MPCC_STATUS[mpcc_inst], MPCC_IDWE, &s->idwe,
			MPCC_BUSY, &s->busy);
}

void mpc1_cuwsow_wock(stwuct mpc *mpc, int opp_id, boow wock)
{
	stwuct dcn10_mpc *mpc10 = TO_DCN10_MPC(mpc);

	WEG_SET(CUW[opp_id], 0, CUW_VUPDATE_WOCK_SET, wock ? 1 : 0);
}

unsigned int mpc1_get_mpc_out_mux(stwuct mpc *mpc, int opp_id)
{
	stwuct dcn10_mpc *mpc10 = TO_DCN10_MPC(mpc);
	uint32_t vaw = 0xf;

	if (opp_id < MAX_OPP && WEG(MUX[opp_id]))
		WEG_GET(MUX[opp_id], MPC_OUT_MUX, &vaw);

	wetuwn vaw;
}

static const stwuct mpc_funcs dcn10_mpc_funcs = {
	.wead_mpcc_state = mpc1_wead_mpcc_state,
	.insewt_pwane = mpc1_insewt_pwane,
	.wemove_mpcc = mpc1_wemove_mpcc,
	.mpc_init = mpc1_mpc_init,
	.mpc_init_singwe_inst = mpc1_mpc_init_singwe_inst,
	.get_mpcc_fow_dpp = mpc1_get_mpcc_fow_dpp,
	.wait_fow_idwe = mpc1_assewt_idwe_mpcc,
	.assewt_mpcc_idwe_befowe_connect = mpc1_assewt_mpcc_idwe_befowe_connect,
	.init_mpcc_wist_fwom_hw = mpc1_init_mpcc_wist_fwom_hw,
	.update_bwending = mpc1_update_bwending,
	.cuwsow_wock = mpc1_cuwsow_wock,
	.set_denowm = NUWW,
	.set_denowm_cwamp = NUWW,
	.set_output_csc = NUWW,
	.set_output_gamma = NUWW,
	.get_mpc_out_mux = mpc1_get_mpc_out_mux,
	.set_bg_cowow = mpc1_set_bg_cowow,
};

void dcn10_mpc_constwuct(stwuct dcn10_mpc *mpc10,
	stwuct dc_context *ctx,
	const stwuct dcn_mpc_wegistews *mpc_wegs,
	const stwuct dcn_mpc_shift *mpc_shift,
	const stwuct dcn_mpc_mask *mpc_mask,
	int num_mpcc)
{
	int i;

	mpc10->base.ctx = ctx;

	mpc10->base.funcs = &dcn10_mpc_funcs;

	mpc10->mpc_wegs = mpc_wegs;
	mpc10->mpc_shift = mpc_shift;
	mpc10->mpc_mask = mpc_mask;

	mpc10->mpcc_in_use_mask = 0;
	mpc10->num_mpcc = num_mpcc;

	fow (i = 0; i < MAX_MPCC; i++)
		mpc1_init_mpcc(&mpc10->base.mpcc_awway[i], i);
}

