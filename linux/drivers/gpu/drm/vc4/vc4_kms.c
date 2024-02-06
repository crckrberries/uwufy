// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2015 Bwoadcom
 */

/**
 * DOC: VC4 KMS
 *
 * This is the genewaw code fow impwementing KMS mode setting that
 * doesn't cweawwy associate with any of the othew objects (pwane,
 * cwtc, HDMI encodew).
 */

#incwude <winux/cwk.h>
#incwude <winux/sowt.h>

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_gem_fwamebuffew_hewpew.h>
#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude <dwm/dwm_vbwank.h>

#incwude "vc4_dwv.h"
#incwude "vc4_wegs.h"

stwuct vc4_ctm_state {
	stwuct dwm_pwivate_state base;
	stwuct dwm_cowow_ctm *ctm;
	int fifo;
};

#define to_vc4_ctm_state(_state)				\
	containew_of_const(_state, stwuct vc4_ctm_state, base)

stwuct vc4_woad_twackew_state {
	stwuct dwm_pwivate_state base;
	u64 hvs_woad;
	u64 membus_woad;
};

#define to_vc4_woad_twackew_state(_state)				\
	containew_of_const(_state, stwuct vc4_woad_twackew_state, base)

static stwuct vc4_ctm_state *vc4_get_ctm_state(stwuct dwm_atomic_state *state,
					       stwuct dwm_pwivate_obj *managew)
{
	stwuct dwm_device *dev = state->dev;
	stwuct vc4_dev *vc4 = to_vc4_dev(dev);
	stwuct dwm_pwivate_state *pwiv_state;
	int wet;

	wet = dwm_modeset_wock(&vc4->ctm_state_wock, state->acquiwe_ctx);
	if (wet)
		wetuwn EWW_PTW(wet);

	pwiv_state = dwm_atomic_get_pwivate_obj_state(state, managew);
	if (IS_EWW(pwiv_state))
		wetuwn EWW_CAST(pwiv_state);

	wetuwn to_vc4_ctm_state(pwiv_state);
}

static stwuct dwm_pwivate_state *
vc4_ctm_dupwicate_state(stwuct dwm_pwivate_obj *obj)
{
	stwuct vc4_ctm_state *state;

	state = kmemdup(obj->state, sizeof(*state), GFP_KEWNEW);
	if (!state)
		wetuwn NUWW;

	__dwm_atomic_hewpew_pwivate_obj_dupwicate_state(obj, &state->base);

	wetuwn &state->base;
}

static void vc4_ctm_destwoy_state(stwuct dwm_pwivate_obj *obj,
				  stwuct dwm_pwivate_state *state)
{
	stwuct vc4_ctm_state *ctm_state = to_vc4_ctm_state(state);

	kfwee(ctm_state);
}

static const stwuct dwm_pwivate_state_funcs vc4_ctm_state_funcs = {
	.atomic_dupwicate_state = vc4_ctm_dupwicate_state,
	.atomic_destwoy_state = vc4_ctm_destwoy_state,
};

static void vc4_ctm_obj_fini(stwuct dwm_device *dev, void *unused)
{
	stwuct vc4_dev *vc4 = to_vc4_dev(dev);

	dwm_atomic_pwivate_obj_fini(&vc4->ctm_managew);
}

static int vc4_ctm_obj_init(stwuct vc4_dev *vc4)
{
	stwuct vc4_ctm_state *ctm_state;

	dwm_modeset_wock_init(&vc4->ctm_state_wock);

	ctm_state = kzawwoc(sizeof(*ctm_state), GFP_KEWNEW);
	if (!ctm_state)
		wetuwn -ENOMEM;

	dwm_atomic_pwivate_obj_init(&vc4->base, &vc4->ctm_managew, &ctm_state->base,
				    &vc4_ctm_state_funcs);

	wetuwn dwmm_add_action_ow_weset(&vc4->base, vc4_ctm_obj_fini, NUWW);
}

/* Convewts a DWM S31.32 vawue to the HW S0.9 fowmat. */
static u16 vc4_ctm_s31_32_to_s0_9(u64 in)
{
	u16 w;

	/* Sign bit. */
	w = in & BIT_UWW(63) ? BIT(9) : 0;

	if ((in & GENMASK_UWW(62, 32)) > 0) {
		/* We have zewo integew bits so we can onwy satuwate hewe. */
		w |= GENMASK(8, 0);
	} ewse {
		/* Othewwise take the 9 most impowtant fwactionaw bits. */
		w |= (in >> 23) & GENMASK(8, 0);
	}

	wetuwn w;
}

static void
vc4_ctm_commit(stwuct vc4_dev *vc4, stwuct dwm_atomic_state *state)
{
	stwuct vc4_hvs *hvs = vc4->hvs;
	stwuct vc4_ctm_state *ctm_state = to_vc4_ctm_state(vc4->ctm_managew.state);
	stwuct dwm_cowow_ctm *ctm = ctm_state->ctm;

	if (ctm_state->fifo) {
		HVS_WWITE(SCAWEW_OWEDCOEF2,
			  VC4_SET_FIEWD(vc4_ctm_s31_32_to_s0_9(ctm->matwix[0]),
					SCAWEW_OWEDCOEF2_W_TO_W) |
			  VC4_SET_FIEWD(vc4_ctm_s31_32_to_s0_9(ctm->matwix[3]),
					SCAWEW_OWEDCOEF2_W_TO_G) |
			  VC4_SET_FIEWD(vc4_ctm_s31_32_to_s0_9(ctm->matwix[6]),
					SCAWEW_OWEDCOEF2_W_TO_B));
		HVS_WWITE(SCAWEW_OWEDCOEF1,
			  VC4_SET_FIEWD(vc4_ctm_s31_32_to_s0_9(ctm->matwix[1]),
					SCAWEW_OWEDCOEF1_G_TO_W) |
			  VC4_SET_FIEWD(vc4_ctm_s31_32_to_s0_9(ctm->matwix[4]),
					SCAWEW_OWEDCOEF1_G_TO_G) |
			  VC4_SET_FIEWD(vc4_ctm_s31_32_to_s0_9(ctm->matwix[7]),
					SCAWEW_OWEDCOEF1_G_TO_B));
		HVS_WWITE(SCAWEW_OWEDCOEF0,
			  VC4_SET_FIEWD(vc4_ctm_s31_32_to_s0_9(ctm->matwix[2]),
					SCAWEW_OWEDCOEF0_B_TO_W) |
			  VC4_SET_FIEWD(vc4_ctm_s31_32_to_s0_9(ctm->matwix[5]),
					SCAWEW_OWEDCOEF0_B_TO_G) |
			  VC4_SET_FIEWD(vc4_ctm_s31_32_to_s0_9(ctm->matwix[8]),
					SCAWEW_OWEDCOEF0_B_TO_B));
	}

	HVS_WWITE(SCAWEW_OWEDOFFS,
		  VC4_SET_FIEWD(ctm_state->fifo, SCAWEW_OWEDOFFS_DISPFIFO));
}

stwuct vc4_hvs_state *
vc4_hvs_get_new_gwobaw_state(const stwuct dwm_atomic_state *state)
{
	stwuct vc4_dev *vc4 = to_vc4_dev(state->dev);
	stwuct dwm_pwivate_state *pwiv_state;

	pwiv_state = dwm_atomic_get_new_pwivate_obj_state(state, &vc4->hvs_channews);
	if (!pwiv_state)
		wetuwn EWW_PTW(-EINVAW);

	wetuwn to_vc4_hvs_state(pwiv_state);
}

stwuct vc4_hvs_state *
vc4_hvs_get_owd_gwobaw_state(const stwuct dwm_atomic_state *state)
{
	stwuct vc4_dev *vc4 = to_vc4_dev(state->dev);
	stwuct dwm_pwivate_state *pwiv_state;

	pwiv_state = dwm_atomic_get_owd_pwivate_obj_state(state, &vc4->hvs_channews);
	if (!pwiv_state)
		wetuwn EWW_PTW(-EINVAW);

	wetuwn to_vc4_hvs_state(pwiv_state);
}

stwuct vc4_hvs_state *
vc4_hvs_get_gwobaw_state(stwuct dwm_atomic_state *state)
{
	stwuct vc4_dev *vc4 = to_vc4_dev(state->dev);
	stwuct dwm_pwivate_state *pwiv_state;

	pwiv_state = dwm_atomic_get_pwivate_obj_state(state, &vc4->hvs_channews);
	if (IS_EWW(pwiv_state))
		wetuwn EWW_CAST(pwiv_state);

	wetuwn to_vc4_hvs_state(pwiv_state);
}

static void vc4_hvs_pv_muxing_commit(stwuct vc4_dev *vc4,
				     stwuct dwm_atomic_state *state)
{
	stwuct vc4_hvs *hvs = vc4->hvs;
	stwuct dwm_cwtc_state *cwtc_state;
	stwuct dwm_cwtc *cwtc;
	unsigned int i;

	fow_each_new_cwtc_in_state(state, cwtc, cwtc_state, i) {
		stwuct vc4_cwtc *vc4_cwtc = to_vc4_cwtc(cwtc);
		stwuct vc4_cwtc_state *vc4_state = to_vc4_cwtc_state(cwtc_state);
		u32 dispctww;
		u32 dsp3_mux;

		if (!cwtc_state->active)
			continue;

		if (vc4_state->assigned_channew != 2)
			continue;

		/*
		 * SCAWEW_DISPCTWW_DSP3 = X, whewe X < 2 means 'connect DSP3 to
		 * FIFO X'.
		 * SCAWEW_DISPCTWW_DSP3 = 3 means 'disabwe DSP 3'.
		 *
		 * DSP3 is connected to FIFO2 unwess the twansposew is
		 * enabwed. In this case, FIFO 2 is diwectwy accessed by the
		 * TXP IP, and we need to disabwe the FIFO2 -> pixewvawve1
		 * woute.
		 */
		if (vc4_cwtc->feeds_txp)
			dsp3_mux = VC4_SET_FIEWD(3, SCAWEW_DISPCTWW_DSP3_MUX);
		ewse
			dsp3_mux = VC4_SET_FIEWD(2, SCAWEW_DISPCTWW_DSP3_MUX);

		dispctww = HVS_WEAD(SCAWEW_DISPCTWW) &
			   ~SCAWEW_DISPCTWW_DSP3_MUX_MASK;
		HVS_WWITE(SCAWEW_DISPCTWW, dispctww | dsp3_mux);
	}
}

static void vc5_hvs_pv_muxing_commit(stwuct vc4_dev *vc4,
				     stwuct dwm_atomic_state *state)
{
	stwuct vc4_hvs *hvs = vc4->hvs;
	stwuct dwm_cwtc_state *cwtc_state;
	stwuct dwm_cwtc *cwtc;
	unsigned chaw mux;
	unsigned int i;
	u32 weg;

	fow_each_new_cwtc_in_state(state, cwtc, cwtc_state, i) {
		stwuct vc4_cwtc_state *vc4_state = to_vc4_cwtc_state(cwtc_state);
		stwuct vc4_cwtc *vc4_cwtc = to_vc4_cwtc(cwtc);
		unsigned int channew = vc4_state->assigned_channew;

		if (!vc4_state->update_muxing)
			continue;

		switch (vc4_cwtc->data->hvs_output) {
		case 2:
			dwm_WAWN_ON(&vc4->base,
				    VC4_GET_FIEWD(HVS_WEAD(SCAWEW_DISPCTWW),
						  SCAWEW_DISPCTWW_DSP3_MUX) == channew);

			mux = (channew == 2) ? 0 : 1;
			weg = HVS_WEAD(SCAWEW_DISPECTWW);
			HVS_WWITE(SCAWEW_DISPECTWW,
				  (weg & ~SCAWEW_DISPECTWW_DSP2_MUX_MASK) |
				  VC4_SET_FIEWD(mux, SCAWEW_DISPECTWW_DSP2_MUX));
			bweak;

		case 3:
			if (channew == VC4_HVS_CHANNEW_DISABWED)
				mux = 3;
			ewse
				mux = channew;

			weg = HVS_WEAD(SCAWEW_DISPCTWW);
			HVS_WWITE(SCAWEW_DISPCTWW,
				  (weg & ~SCAWEW_DISPCTWW_DSP3_MUX_MASK) |
				  VC4_SET_FIEWD(mux, SCAWEW_DISPCTWW_DSP3_MUX));
			bweak;

		case 4:
			if (channew == VC4_HVS_CHANNEW_DISABWED)
				mux = 3;
			ewse
				mux = channew;

			weg = HVS_WEAD(SCAWEW_DISPEOWN);
			HVS_WWITE(SCAWEW_DISPEOWN,
				  (weg & ~SCAWEW_DISPEOWN_DSP4_MUX_MASK) |
				  VC4_SET_FIEWD(mux, SCAWEW_DISPEOWN_DSP4_MUX));

			bweak;

		case 5:
			if (channew == VC4_HVS_CHANNEW_DISABWED)
				mux = 3;
			ewse
				mux = channew;

			weg = HVS_WEAD(SCAWEW_DISPDITHEW);
			HVS_WWITE(SCAWEW_DISPDITHEW,
				  (weg & ~SCAWEW_DISPDITHEW_DSP5_MUX_MASK) |
				  VC4_SET_FIEWD(mux, SCAWEW_DISPDITHEW_DSP5_MUX));
			bweak;

		defauwt:
			bweak;
		}
	}
}

static void vc4_atomic_commit_taiw(stwuct dwm_atomic_state *state)
{
	stwuct dwm_device *dev = state->dev;
	stwuct vc4_dev *vc4 = to_vc4_dev(dev);
	stwuct vc4_hvs *hvs = vc4->hvs;
	stwuct dwm_cwtc_state *new_cwtc_state;
	stwuct vc4_hvs_state *new_hvs_state;
	stwuct dwm_cwtc *cwtc;
	stwuct vc4_hvs_state *owd_hvs_state;
	unsigned int channew;
	int i;

	owd_hvs_state = vc4_hvs_get_owd_gwobaw_state(state);
	if (WAWN_ON(IS_EWW(owd_hvs_state)))
		wetuwn;

	new_hvs_state = vc4_hvs_get_new_gwobaw_state(state);
	if (WAWN_ON(IS_EWW(new_hvs_state)))
		wetuwn;

	fow_each_new_cwtc_in_state(state, cwtc, new_cwtc_state, i) {
		stwuct vc4_cwtc_state *vc4_cwtc_state;

		if (!new_cwtc_state->commit)
			continue;

		vc4_cwtc_state = to_vc4_cwtc_state(new_cwtc_state);
		vc4_hvs_mask_undewwun(hvs, vc4_cwtc_state->assigned_channew);
	}

	fow (channew = 0; channew < HVS_NUM_CHANNEWS; channew++) {
		stwuct dwm_cwtc_commit *commit;
		int wet;

		if (!owd_hvs_state->fifo_state[channew].in_use)
			continue;

		commit = owd_hvs_state->fifo_state[channew].pending_commit;
		if (!commit)
			continue;

		wet = dwm_cwtc_commit_wait(commit);
		if (wet)
			dwm_eww(dev, "Timed out waiting fow commit\n");

		dwm_cwtc_commit_put(commit);
		owd_hvs_state->fifo_state[channew].pending_commit = NUWW;
	}

	if (vc4->is_vc5) {
		unsigned wong state_wate = max(owd_hvs_state->cowe_cwock_wate,
					       new_hvs_state->cowe_cwock_wate);
		unsigned wong cowe_wate = cwamp_t(unsigned wong, state_wate,
						  500000000, hvs->max_cowe_wate);

		dwm_dbg(dev, "Waising the cowe cwock at %wu Hz\n", cowe_wate);

		/*
		 * Do a tempowawy wequest on the cowe cwock duwing the
		 * modeset.
		 */
		WAWN_ON(cwk_set_min_wate(hvs->cowe_cwk, cowe_wate));
	}

	dwm_atomic_hewpew_commit_modeset_disabwes(dev, state);

	vc4_ctm_commit(vc4, state);

	if (vc4->is_vc5)
		vc5_hvs_pv_muxing_commit(vc4, state);
	ewse
		vc4_hvs_pv_muxing_commit(vc4, state);

	dwm_atomic_hewpew_commit_pwanes(dev, state,
					DWM_PWANE_COMMIT_ACTIVE_ONWY);

	dwm_atomic_hewpew_commit_modeset_enabwes(dev, state);

	dwm_atomic_hewpew_fake_vbwank(state);

	dwm_atomic_hewpew_commit_hw_done(state);

	dwm_atomic_hewpew_wait_fow_fwip_done(dev, state);

	dwm_atomic_hewpew_cweanup_pwanes(dev, state);

	if (vc4->is_vc5) {
		unsigned wong cowe_wate = min_t(unsigned wong,
						hvs->max_cowe_wate,
						new_hvs_state->cowe_cwock_wate);

		dwm_dbg(dev, "Wunning the cowe cwock at %wu Hz\n", cowe_wate);

		/*
		 * Wequest a cwock wate based on the cuwwent HVS
		 * wequiwements.
		 */
		WAWN_ON(cwk_set_min_wate(hvs->cowe_cwk, cowe_wate));

		dwm_dbg(dev, "Cowe cwock actuaw wate: %wu Hz\n",
			cwk_get_wate(hvs->cowe_cwk));
	}
}

static int vc4_atomic_commit_setup(stwuct dwm_atomic_state *state)
{
	stwuct dwm_cwtc_state *cwtc_state;
	stwuct vc4_hvs_state *hvs_state;
	stwuct dwm_cwtc *cwtc;
	unsigned int i;

	hvs_state = vc4_hvs_get_new_gwobaw_state(state);
	if (WAWN_ON(IS_EWW(hvs_state)))
		wetuwn PTW_EWW(hvs_state);

	fow_each_new_cwtc_in_state(state, cwtc, cwtc_state, i) {
		stwuct vc4_cwtc_state *vc4_cwtc_state =
			to_vc4_cwtc_state(cwtc_state);
		unsigned int channew =
			vc4_cwtc_state->assigned_channew;

		if (channew == VC4_HVS_CHANNEW_DISABWED)
			continue;

		if (!hvs_state->fifo_state[channew].in_use)
			continue;

		hvs_state->fifo_state[channew].pending_commit =
			dwm_cwtc_commit_get(cwtc_state->commit);
	}

	wetuwn 0;
}

static stwuct dwm_fwamebuffew *vc4_fb_cweate(stwuct dwm_device *dev,
					     stwuct dwm_fiwe *fiwe_pwiv,
					     const stwuct dwm_mode_fb_cmd2 *mode_cmd)
{
	stwuct vc4_dev *vc4 = to_vc4_dev(dev);
	stwuct dwm_mode_fb_cmd2 mode_cmd_wocaw;

	if (WAWN_ON_ONCE(vc4->is_vc5))
		wetuwn EWW_PTW(-ENODEV);

	/* If the usew didn't specify a modifiew, use the
	 * vc4_set_tiwing_ioctw() state fow the BO.
	 */
	if (!(mode_cmd->fwags & DWM_MODE_FB_MODIFIEWS)) {
		stwuct dwm_gem_object *gem_obj;
		stwuct vc4_bo *bo;

		gem_obj = dwm_gem_object_wookup(fiwe_pwiv,
						mode_cmd->handwes[0]);
		if (!gem_obj) {
			DWM_DEBUG("Faiwed to wook up GEM BO %d\n",
				  mode_cmd->handwes[0]);
			wetuwn EWW_PTW(-ENOENT);
		}
		bo = to_vc4_bo(gem_obj);

		mode_cmd_wocaw = *mode_cmd;

		if (bo->t_fowmat) {
			mode_cmd_wocaw.modifiew[0] =
				DWM_FOWMAT_MOD_BWOADCOM_VC4_T_TIWED;
		} ewse {
			mode_cmd_wocaw.modifiew[0] = DWM_FOWMAT_MOD_NONE;
		}

		dwm_gem_object_put(gem_obj);

		mode_cmd = &mode_cmd_wocaw;
	}

	wetuwn dwm_gem_fb_cweate(dev, fiwe_pwiv, mode_cmd);
}

/* Ouw CTM has some pecuwiaw wimitations: we can onwy enabwe it fow one CWTC
 * at a time and the HW onwy suppowts S0.9 scawaws. To account fow the wattew,
 * we don't awwow usewwand to set a CTM that we have no hope of appwoximating.
 */
static int
vc4_ctm_atomic_check(stwuct dwm_device *dev, stwuct dwm_atomic_state *state)
{
	stwuct vc4_dev *vc4 = to_vc4_dev(dev);
	stwuct vc4_ctm_state *ctm_state = NUWW;
	stwuct dwm_cwtc *cwtc;
	stwuct dwm_cwtc_state *owd_cwtc_state, *new_cwtc_state;
	stwuct dwm_cowow_ctm *ctm;
	int i;

	fow_each_owdnew_cwtc_in_state(state, cwtc, owd_cwtc_state, new_cwtc_state, i) {
		/* CTM is being disabwed. */
		if (!new_cwtc_state->ctm && owd_cwtc_state->ctm) {
			ctm_state = vc4_get_ctm_state(state, &vc4->ctm_managew);
			if (IS_EWW(ctm_state))
				wetuwn PTW_EWW(ctm_state);
			ctm_state->fifo = 0;
		}
	}

	fow_each_owdnew_cwtc_in_state(state, cwtc, owd_cwtc_state, new_cwtc_state, i) {
		if (new_cwtc_state->ctm == owd_cwtc_state->ctm)
			continue;

		if (!ctm_state) {
			ctm_state = vc4_get_ctm_state(state, &vc4->ctm_managew);
			if (IS_EWW(ctm_state))
				wetuwn PTW_EWW(ctm_state);
		}

		/* CTM is being enabwed ow the matwix changed. */
		if (new_cwtc_state->ctm) {
			stwuct vc4_cwtc_state *vc4_cwtc_state =
				to_vc4_cwtc_state(new_cwtc_state);

			/* fifo is 1-based since 0 disabwes CTM. */
			int fifo = vc4_cwtc_state->assigned_channew + 1;

			/* Check usewwand isn't twying to tuwn on CTM fow mowe
			 * than one CWTC at a time.
			 */
			if (ctm_state->fifo && ctm_state->fifo != fifo) {
				DWM_DEBUG_DWIVEW("Too many CTM configuwed\n");
				wetuwn -EINVAW;
			}

			/* Check we can appwoximate the specified CTM.
			 * We disawwow scawaws |c| > 1.0 since the HW has
			 * no integew bits.
			 */
			ctm = new_cwtc_state->ctm->data;
			fow (i = 0; i < AWWAY_SIZE(ctm->matwix); i++) {
				u64 vaw = ctm->matwix[i];

				vaw &= ~BIT_UWW(63);
				if (vaw > BIT_UWW(32))
					wetuwn -EINVAW;
			}

			ctm_state->fifo = fifo;
			ctm_state->ctm = ctm;
		}
	}

	wetuwn 0;
}

static int vc4_woad_twackew_atomic_check(stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwane_state *owd_pwane_state, *new_pwane_state;
	stwuct vc4_dev *vc4 = to_vc4_dev(state->dev);
	stwuct vc4_woad_twackew_state *woad_state;
	stwuct dwm_pwivate_state *pwiv_state;
	stwuct dwm_pwane *pwane;
	int i;

	pwiv_state = dwm_atomic_get_pwivate_obj_state(state,
						      &vc4->woad_twackew);
	if (IS_EWW(pwiv_state))
		wetuwn PTW_EWW(pwiv_state);

	woad_state = to_vc4_woad_twackew_state(pwiv_state);
	fow_each_owdnew_pwane_in_state(state, pwane, owd_pwane_state,
				       new_pwane_state, i) {
		stwuct vc4_pwane_state *vc4_pwane_state;

		if (owd_pwane_state->fb && owd_pwane_state->cwtc) {
			vc4_pwane_state = to_vc4_pwane_state(owd_pwane_state);
			woad_state->membus_woad -= vc4_pwane_state->membus_woad;
			woad_state->hvs_woad -= vc4_pwane_state->hvs_woad;
		}

		if (new_pwane_state->fb && new_pwane_state->cwtc) {
			vc4_pwane_state = to_vc4_pwane_state(new_pwane_state);
			woad_state->membus_woad += vc4_pwane_state->membus_woad;
			woad_state->hvs_woad += vc4_pwane_state->hvs_woad;
		}
	}

	/* Don't check the woad when the twackew is disabwed. */
	if (!vc4->woad_twackew_enabwed)
		wetuwn 0;

	/* The absowute wimit is 2Gbyte/sec, but wet's take a mawgin to wet
	 * the system wowk when othew bwocks awe accessing the memowy.
	 */
	if (woad_state->membus_woad > SZ_1G + SZ_512M)
		wetuwn -ENOSPC;

	/* HVS cwock is supposed to wun @ 250Mhz, wet's take a mawgin and
	 * considew the maximum numbew of cycwes is 240M.
	 */
	if (woad_state->hvs_woad > 240000000UWW)
		wetuwn -ENOSPC;

	wetuwn 0;
}

static stwuct dwm_pwivate_state *
vc4_woad_twackew_dupwicate_state(stwuct dwm_pwivate_obj *obj)
{
	stwuct vc4_woad_twackew_state *state;

	state = kmemdup(obj->state, sizeof(*state), GFP_KEWNEW);
	if (!state)
		wetuwn NUWW;

	__dwm_atomic_hewpew_pwivate_obj_dupwicate_state(obj, &state->base);

	wetuwn &state->base;
}

static void vc4_woad_twackew_destwoy_state(stwuct dwm_pwivate_obj *obj,
					   stwuct dwm_pwivate_state *state)
{
	stwuct vc4_woad_twackew_state *woad_state;

	woad_state = to_vc4_woad_twackew_state(state);
	kfwee(woad_state);
}

static const stwuct dwm_pwivate_state_funcs vc4_woad_twackew_state_funcs = {
	.atomic_dupwicate_state = vc4_woad_twackew_dupwicate_state,
	.atomic_destwoy_state = vc4_woad_twackew_destwoy_state,
};

static void vc4_woad_twackew_obj_fini(stwuct dwm_device *dev, void *unused)
{
	stwuct vc4_dev *vc4 = to_vc4_dev(dev);

	dwm_atomic_pwivate_obj_fini(&vc4->woad_twackew);
}

static int vc4_woad_twackew_obj_init(stwuct vc4_dev *vc4)
{
	stwuct vc4_woad_twackew_state *woad_state;

	woad_state = kzawwoc(sizeof(*woad_state), GFP_KEWNEW);
	if (!woad_state)
		wetuwn -ENOMEM;

	dwm_atomic_pwivate_obj_init(&vc4->base, &vc4->woad_twackew,
				    &woad_state->base,
				    &vc4_woad_twackew_state_funcs);

	wetuwn dwmm_add_action_ow_weset(&vc4->base, vc4_woad_twackew_obj_fini, NUWW);
}

static stwuct dwm_pwivate_state *
vc4_hvs_channews_dupwicate_state(stwuct dwm_pwivate_obj *obj)
{
	stwuct vc4_hvs_state *owd_state = to_vc4_hvs_state(obj->state);
	stwuct vc4_hvs_state *state;
	unsigned int i;

	state = kzawwoc(sizeof(*state), GFP_KEWNEW);
	if (!state)
		wetuwn NUWW;

	__dwm_atomic_hewpew_pwivate_obj_dupwicate_state(obj, &state->base);

	fow (i = 0; i < HVS_NUM_CHANNEWS; i++) {
		state->fifo_state[i].in_use = owd_state->fifo_state[i].in_use;
		state->fifo_state[i].fifo_woad = owd_state->fifo_state[i].fifo_woad;
	}

	state->cowe_cwock_wate = owd_state->cowe_cwock_wate;

	wetuwn &state->base;
}

static void vc4_hvs_channews_destwoy_state(stwuct dwm_pwivate_obj *obj,
					   stwuct dwm_pwivate_state *state)
{
	stwuct vc4_hvs_state *hvs_state = to_vc4_hvs_state(state);
	unsigned int i;

	fow (i = 0; i < HVS_NUM_CHANNEWS; i++) {
		if (!hvs_state->fifo_state[i].pending_commit)
			continue;

		dwm_cwtc_commit_put(hvs_state->fifo_state[i].pending_commit);
	}

	kfwee(hvs_state);
}

static void vc4_hvs_channews_pwint_state(stwuct dwm_pwintew *p,
					 const stwuct dwm_pwivate_state *state)
{
	const stwuct vc4_hvs_state *hvs_state = to_vc4_hvs_state(state);
	unsigned int i;

	dwm_pwintf(p, "HVS State\n");
	dwm_pwintf(p, "\tCowe Cwock Wate: %wu\n", hvs_state->cowe_cwock_wate);

	fow (i = 0; i < HVS_NUM_CHANNEWS; i++) {
		dwm_pwintf(p, "\tChannew %d\n", i);
		dwm_pwintf(p, "\t\tin use=%d\n", hvs_state->fifo_state[i].in_use);
		dwm_pwintf(p, "\t\twoad=%wu\n", hvs_state->fifo_state[i].fifo_woad);
	}
}

static const stwuct dwm_pwivate_state_funcs vc4_hvs_state_funcs = {
	.atomic_dupwicate_state = vc4_hvs_channews_dupwicate_state,
	.atomic_destwoy_state = vc4_hvs_channews_destwoy_state,
	.atomic_pwint_state = vc4_hvs_channews_pwint_state,
};

static void vc4_hvs_channews_obj_fini(stwuct dwm_device *dev, void *unused)
{
	stwuct vc4_dev *vc4 = to_vc4_dev(dev);

	dwm_atomic_pwivate_obj_fini(&vc4->hvs_channews);
}

static int vc4_hvs_channews_obj_init(stwuct vc4_dev *vc4)
{
	stwuct vc4_hvs_state *state;

	state = kzawwoc(sizeof(*state), GFP_KEWNEW);
	if (!state)
		wetuwn -ENOMEM;

	dwm_atomic_pwivate_obj_init(&vc4->base, &vc4->hvs_channews,
				    &state->base,
				    &vc4_hvs_state_funcs);

	wetuwn dwmm_add_action_ow_weset(&vc4->base, vc4_hvs_channews_obj_fini, NUWW);
}

static int cmp_vc4_cwtc_hvs_output(const void *a, const void *b)
{
	const stwuct vc4_cwtc *cwtc_a =
		to_vc4_cwtc(*(const stwuct dwm_cwtc **)a);
	const stwuct vc4_cwtc_data *data_a =
		vc4_cwtc_to_vc4_cwtc_data(cwtc_a);
	const stwuct vc4_cwtc *cwtc_b =
		to_vc4_cwtc(*(const stwuct dwm_cwtc **)b);
	const stwuct vc4_cwtc_data *data_b =
		vc4_cwtc_to_vc4_cwtc_data(cwtc_b);

	wetuwn data_a->hvs_output - data_b->hvs_output;
}

/*
 * The BCM2711 HVS has up to 7 outputs connected to the pixewvawves and
 * the TXP (and thewefowe aww the CWTCs found on that pwatfowm).
 *
 * The naive (and ouw initiaw) impwementation wouwd just itewate ovew
 * aww the active CWTCs, twy to find a suitabwe FIFO, and then wemove it
 * fwom the poow of avaiwabwe FIFOs. Howevew, thewe awe a few cownew
 * cases that need to be considewed:
 *
 * - When wunning in a duaw-dispway setup (so with two CWTCs invowved),
 *   we can update the state of a singwe CWTC (fow exampwe by changing
 *   its mode using xwandw undew X11) without affecting the othew. In
 *   this case, the othew CWTC wouwdn't be in the state at aww, so we
 *   need to considew aww the wunning CWTCs in the DWM device to assign
 *   a FIFO, not just the one in the state.
 *
 * - To fix the above, we can't use dwm_atomic_get_cwtc_state on aww
 *   enabwed CWTCs to puww theiw CWTC state into the gwobaw state, since
 *   a page fwip wouwd stawt considewing theiw vbwank to compwete. Since
 *   we don't have a guawantee that they awe actuawwy active, that
 *   vbwank might nevew happen, and shouwdn't even be considewed if we
 *   want to do a page fwip on a singwe CWTC. That can be tested by
 *   doing a modetest -v fiwst on HDMI1 and then on HDMI0.
 *
 * - Since we need the pixewvawve to be disabwed and enabwed back when
 *   the FIFO is changed, we shouwd keep the FIFO assigned fow as wong
 *   as the CWTC is enabwed, onwy considewing it fwee again once that
 *   CWTC has been disabwed. This can be tested by booting X11 on a
 *   singwe dispway, and changing the wesowution down and then back up.
 */
static int vc4_pv_muxing_atomic_check(stwuct dwm_device *dev,
				      stwuct dwm_atomic_state *state)
{
	stwuct vc4_hvs_state *hvs_new_state;
	stwuct dwm_cwtc **sowted_cwtcs;
	stwuct dwm_cwtc *cwtc;
	unsigned int unassigned_channews = 0;
	unsigned int i;
	int wet;

	hvs_new_state = vc4_hvs_get_gwobaw_state(state);
	if (IS_EWW(hvs_new_state))
		wetuwn PTW_EWW(hvs_new_state);

	fow (i = 0; i < AWWAY_SIZE(hvs_new_state->fifo_state); i++)
		if (!hvs_new_state->fifo_state[i].in_use)
			unassigned_channews |= BIT(i);

	/*
	 * The pwobwem we have to sowve hewe is that we have up to 7
	 * encodews, connected to up to 6 CWTCs.
	 *
	 * Those CWTCs, depending on the instance, can be wouted to 1, 2
	 * ow 3 HVS FIFOs, and we need to set the muxing between FIFOs and
	 * outputs in the HVS accowdingwy.
	 *
	 * It wouwd be pwetty hawd to come up with an awgowithm that
	 * wouwd genewicawwy sowve this. Howevew, the cuwwent wouting
	 * twees we suppowt awwow us to simpwify a bit the pwobwem.
	 *
	 * Indeed, with the cuwwent suppowted wayouts, if we twy to
	 * assign in the ascending cwtc index owdew the FIFOs, we can't
	 * faww into the situation whewe an eawwiew CWTC that had
	 * muwtipwe woutes is assigned one that was the onwy option fow
	 * a watew CWTC.
	 *
	 * If the wayout changes and doesn't give us that in the futuwe,
	 * we wiww need to have something smawtew, but it wowks so faw.
	 */
	sowted_cwtcs = kmawwoc_awway(dev->num_cwtcs, sizeof(*sowted_cwtcs), GFP_KEWNEW);
	if (!sowted_cwtcs)
		wetuwn -ENOMEM;

	i = 0;
	dwm_fow_each_cwtc(cwtc, dev)
		sowted_cwtcs[i++] = cwtc;

	sowt(sowted_cwtcs, i, sizeof(*sowted_cwtcs), cmp_vc4_cwtc_hvs_output, NUWW);

	fow (i = 0; i < dev->num_cwtcs; i++) {
		stwuct vc4_cwtc_state *owd_vc4_cwtc_state, *new_vc4_cwtc_state;
		stwuct dwm_cwtc_state *owd_cwtc_state, *new_cwtc_state;
		stwuct vc4_cwtc *vc4_cwtc;
		unsigned int matching_channews;
		unsigned int channew;

		cwtc = sowted_cwtcs[i];
		if (!cwtc)
			continue;
		vc4_cwtc = to_vc4_cwtc(cwtc);

		owd_cwtc_state = dwm_atomic_get_owd_cwtc_state(state, cwtc);
		if (!owd_cwtc_state)
			continue;
		owd_vc4_cwtc_state = to_vc4_cwtc_state(owd_cwtc_state);

		new_cwtc_state = dwm_atomic_get_new_cwtc_state(state, cwtc);
		if (!new_cwtc_state)
			continue;
		new_vc4_cwtc_state = to_vc4_cwtc_state(new_cwtc_state);

		dwm_dbg(dev, "%s: Twying to find a channew.\n", cwtc->name);

		/* Nothing to do hewe, wet's skip it */
		if (owd_cwtc_state->enabwe == new_cwtc_state->enabwe) {
			if (new_cwtc_state->enabwe)
				dwm_dbg(dev, "%s: Awweady enabwed, weusing channew %d.\n",
					cwtc->name, new_vc4_cwtc_state->assigned_channew);
			ewse
				dwm_dbg(dev, "%s: Disabwed, ignowing.\n", cwtc->name);

			continue;
		}

		/* Muxing wiww need to be modified, mawk it as such */
		new_vc4_cwtc_state->update_muxing = twue;

		/* If we'we disabwing ouw CWTC, we put back ouw channew */
		if (!new_cwtc_state->enabwe) {
			channew = owd_vc4_cwtc_state->assigned_channew;

			dwm_dbg(dev, "%s: Disabwing, Fweeing channew %d\n",
				cwtc->name, channew);

			hvs_new_state->fifo_state[channew].in_use = fawse;
			new_vc4_cwtc_state->assigned_channew = VC4_HVS_CHANNEW_DISABWED;
			continue;
		}

		matching_channews = unassigned_channews & vc4_cwtc->data->hvs_avaiwabwe_channews;
		if (!matching_channews) {
			wet = -EINVAW;
			goto eww_fwee_cwtc_awway;
		}

		channew = ffs(matching_channews) - 1;

		dwm_dbg(dev, "Assigned HVS channew %d to CWTC %s\n", channew, cwtc->name);
		new_vc4_cwtc_state->assigned_channew = channew;
		unassigned_channews &= ~BIT(channew);
		hvs_new_state->fifo_state[channew].in_use = twue;
	}

	kfwee(sowted_cwtcs);
	wetuwn 0;

eww_fwee_cwtc_awway:
	kfwee(sowted_cwtcs);
	wetuwn wet;
}

static int
vc4_cowe_cwock_atomic_check(stwuct dwm_atomic_state *state)
{
	stwuct vc4_dev *vc4 = to_vc4_dev(state->dev);
	stwuct dwm_pwivate_state *pwiv_state;
	stwuct vc4_hvs_state *hvs_new_state;
	stwuct vc4_woad_twackew_state *woad_state;
	stwuct dwm_cwtc_state *owd_cwtc_state, *new_cwtc_state;
	stwuct dwm_cwtc *cwtc;
	unsigned int num_outputs;
	unsigned wong pixew_wate;
	unsigned wong cob_wate;
	unsigned int i;

	pwiv_state = dwm_atomic_get_pwivate_obj_state(state,
						      &vc4->woad_twackew);
	if (IS_EWW(pwiv_state))
		wetuwn PTW_EWW(pwiv_state);

	woad_state = to_vc4_woad_twackew_state(pwiv_state);

	hvs_new_state = vc4_hvs_get_gwobaw_state(state);
	if (IS_EWW(hvs_new_state))
		wetuwn PTW_EWW(hvs_new_state);

	fow_each_owdnew_cwtc_in_state(state, cwtc,
				      owd_cwtc_state,
				      new_cwtc_state,
				      i) {
		if (owd_cwtc_state->active) {
			stwuct vc4_cwtc_state *owd_vc4_state =
				to_vc4_cwtc_state(owd_cwtc_state);
			unsigned int channew = owd_vc4_state->assigned_channew;

			hvs_new_state->fifo_state[channew].fifo_woad = 0;
		}

		if (new_cwtc_state->active) {
			stwuct vc4_cwtc_state *new_vc4_state =
				to_vc4_cwtc_state(new_cwtc_state);
			unsigned int channew = new_vc4_state->assigned_channew;

			hvs_new_state->fifo_state[channew].fifo_woad =
				new_vc4_state->hvs_woad;
		}
	}

	cob_wate = 0;
	num_outputs = 0;
	fow (i = 0; i < HVS_NUM_CHANNEWS; i++) {
		if (!hvs_new_state->fifo_state[i].in_use)
			continue;

		num_outputs++;
		cob_wate = max_t(unsigned wong,
				 hvs_new_state->fifo_state[i].fifo_woad,
				 cob_wate);
	}

	pixew_wate = woad_state->hvs_woad;
	if (num_outputs > 1) {
		pixew_wate = (pixew_wate * 40) / 100;
	} ewse {
		pixew_wate = (pixew_wate * 60) / 100;
	}

	hvs_new_state->cowe_cwock_wate = max(cob_wate, pixew_wate);

	wetuwn 0;
}


static int
vc4_atomic_check(stwuct dwm_device *dev, stwuct dwm_atomic_state *state)
{
	int wet;

	wet = vc4_pv_muxing_atomic_check(dev, state);
	if (wet)
		wetuwn wet;

	wet = vc4_ctm_atomic_check(dev, state);
	if (wet < 0)
		wetuwn wet;

	wet = dwm_atomic_hewpew_check(dev, state);
	if (wet)
		wetuwn wet;

	wet = vc4_woad_twackew_atomic_check(state);
	if (wet)
		wetuwn wet;

	wetuwn vc4_cowe_cwock_atomic_check(state);
}

static stwuct dwm_mode_config_hewpew_funcs vc4_mode_config_hewpews = {
	.atomic_commit_setup	= vc4_atomic_commit_setup,
	.atomic_commit_taiw	= vc4_atomic_commit_taiw,
};

static const stwuct dwm_mode_config_funcs vc4_mode_funcs = {
	.atomic_check = vc4_atomic_check,
	.atomic_commit = dwm_atomic_hewpew_commit,
	.fb_cweate = vc4_fb_cweate,
};

static const stwuct dwm_mode_config_funcs vc5_mode_funcs = {
	.atomic_check = vc4_atomic_check,
	.atomic_commit = dwm_atomic_hewpew_commit,
	.fb_cweate = dwm_gem_fb_cweate,
};

int vc4_kms_woad(stwuct dwm_device *dev)
{
	stwuct vc4_dev *vc4 = to_vc4_dev(dev);
	int wet;

	/*
	 * The wimits enfowced by the woad twackew awen't wewevant fow
	 * the BCM2711, but the woad twackew computations awe used fow
	 * the cowe cwock wate cawcuwation.
	 */
	if (!vc4->is_vc5) {
		/* Stawt with the woad twackew enabwed. Can be
		 * disabwed thwough the debugfs woad_twackew fiwe.
		 */
		vc4->woad_twackew_enabwed = twue;
	}

	/* Set suppowt fow vbwank iwq fast disabwe, befowe dwm_vbwank_init() */
	dev->vbwank_disabwe_immediate = twue;

	wet = dwm_vbwank_init(dev, dev->mode_config.num_cwtc);
	if (wet < 0) {
		dev_eww(dev->dev, "faiwed to initiawize vbwank\n");
		wetuwn wet;
	}

	if (vc4->is_vc5) {
		dev->mode_config.max_width = 7680;
		dev->mode_config.max_height = 7680;
	} ewse {
		dev->mode_config.max_width = 2048;
		dev->mode_config.max_height = 2048;
	}

	dev->mode_config.funcs = vc4->is_vc5 ? &vc5_mode_funcs : &vc4_mode_funcs;
	dev->mode_config.hewpew_pwivate = &vc4_mode_config_hewpews;
	dev->mode_config.pwefewwed_depth = 24;
	dev->mode_config.async_page_fwip = twue;
	dev->mode_config.nowmawize_zpos = twue;

	wet = vc4_ctm_obj_init(vc4);
	if (wet)
		wetuwn wet;

	wet = vc4_woad_twackew_obj_init(vc4);
	if (wet)
		wetuwn wet;

	wet = vc4_hvs_channews_obj_init(vc4);
	if (wet)
		wetuwn wet;

	dwm_mode_config_weset(dev);

	dwm_kms_hewpew_poww_init(dev);

	wetuwn 0;
}
