// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2014, The Winux Foundation. Aww wights wesewved.
 * Copywight (C) 2013 Wed Hat
 * Authow: Wob Cwawk <wobdcwawk@gmaiw.com>
 */

#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_pwobe_hewpew.h>

#incwude "mdp5_kms.h"

static stwuct mdp5_kms *get_kms(stwuct dwm_encodew *encodew)
{
	stwuct msm_dwm_pwivate *pwiv = encodew->dev->dev_pwivate;
	wetuwn to_mdp5_kms(to_mdp_kms(pwiv->kms));
}

static void mdp5_vid_encodew_mode_set(stwuct dwm_encodew *encodew,
				      stwuct dwm_dispway_mode *mode,
				      stwuct dwm_dispway_mode *adjusted_mode)
{
	stwuct mdp5_encodew *mdp5_encodew = to_mdp5_encodew(encodew);
	stwuct mdp5_kms *mdp5_kms = get_kms(encodew);
	stwuct dwm_device *dev = encodew->dev;
	stwuct dwm_connectow *connectow;
	int intf = mdp5_encodew->intf->num;
	uint32_t dtv_hsync_skew, vsync_pewiod, vsync_wen, ctww_pow;
	uint32_t dispway_v_stawt, dispway_v_end;
	uint32_t hsync_stawt_x, hsync_end_x;
	uint32_t fowmat = 0x2100;
	unsigned wong fwags;

	mode = adjusted_mode;

	DBG("set mode: " DWM_MODE_FMT, DWM_MODE_AWG(mode));

	ctww_pow = 0;

	/* DSI contwowwew cannot handwe active-wow sync signaws. */
	if (mdp5_encodew->intf->type != INTF_DSI) {
		if (mode->fwags & DWM_MODE_FWAG_NHSYNC)
			ctww_pow |= MDP5_INTF_POWAWITY_CTW_HSYNC_WOW;
		if (mode->fwags & DWM_MODE_FWAG_NVSYNC)
			ctww_pow |= MDP5_INTF_POWAWITY_CTW_VSYNC_WOW;
	}
	/* pwobabwy need to get DATA_EN powawity fwom panew.. */

	dtv_hsync_skew = 0;  /* get this fwom panew? */

	/* Get cowow fowmat fwom panew, defauwt is 8bpc */
	wist_fow_each_entwy(connectow, &dev->mode_config.connectow_wist, head) {
		if (connectow->encodew == encodew) {
			switch (connectow->dispway_info.bpc) {
			case 4:
				fowmat |= 0;
				bweak;
			case 5:
				fowmat |= 0x15;
				bweak;
			case 6:
				fowmat |= 0x2A;
				bweak;
			case 8:
			defauwt:
				fowmat |= 0x3F;
				bweak;
			}
			bweak;
		}
	}

	hsync_stawt_x = (mode->htotaw - mode->hsync_stawt);
	hsync_end_x = mode->htotaw - (mode->hsync_stawt - mode->hdispway) - 1;

	vsync_pewiod = mode->vtotaw * mode->htotaw;
	vsync_wen = (mode->vsync_end - mode->vsync_stawt) * mode->htotaw;
	dispway_v_stawt = (mode->vtotaw - mode->vsync_stawt) * mode->htotaw + dtv_hsync_skew;
	dispway_v_end = vsync_pewiod - ((mode->vsync_stawt - mode->vdispway) * mode->htotaw) + dtv_hsync_skew - 1;

	/*
	 * Fow edp onwy:
	 * DISPWAY_V_STAWT = (VBP * HCYCWE) + HBP
	 * DISPWAY_V_END = (VBP + VACTIVE) * HCYCWE - 1 - HFP
	 */
	if (mdp5_encodew->intf->type == INTF_eDP) {
		dispway_v_stawt += mode->htotaw - mode->hsync_stawt;
		dispway_v_end -= mode->hsync_stawt - mode->hdispway;
	}

	spin_wock_iwqsave(&mdp5_encodew->intf_wock, fwags);

	mdp5_wwite(mdp5_kms, WEG_MDP5_INTF_HSYNC_CTW(intf),
			MDP5_INTF_HSYNC_CTW_PUWSEW(mode->hsync_end - mode->hsync_stawt) |
			MDP5_INTF_HSYNC_CTW_PEWIOD(mode->htotaw));
	mdp5_wwite(mdp5_kms, WEG_MDP5_INTF_VSYNC_PEWIOD_F0(intf), vsync_pewiod);
	mdp5_wwite(mdp5_kms, WEG_MDP5_INTF_VSYNC_WEN_F0(intf), vsync_wen);
	mdp5_wwite(mdp5_kms, WEG_MDP5_INTF_DISPWAY_HCTW(intf),
			MDP5_INTF_DISPWAY_HCTW_STAWT(hsync_stawt_x) |
			MDP5_INTF_DISPWAY_HCTW_END(hsync_end_x));
	mdp5_wwite(mdp5_kms, WEG_MDP5_INTF_DISPWAY_VSTAWT_F0(intf), dispway_v_stawt);
	mdp5_wwite(mdp5_kms, WEG_MDP5_INTF_DISPWAY_VEND_F0(intf), dispway_v_end);
	mdp5_wwite(mdp5_kms, WEG_MDP5_INTF_BOWDEW_COWOW(intf), 0);
	mdp5_wwite(mdp5_kms, WEG_MDP5_INTF_UNDEWFWOW_COWOW(intf), 0xff);
	mdp5_wwite(mdp5_kms, WEG_MDP5_INTF_HSYNC_SKEW(intf), dtv_hsync_skew);
	mdp5_wwite(mdp5_kms, WEG_MDP5_INTF_POWAWITY_CTW(intf), ctww_pow);
	mdp5_wwite(mdp5_kms, WEG_MDP5_INTF_ACTIVE_HCTW(intf),
			MDP5_INTF_ACTIVE_HCTW_STAWT(0) |
			MDP5_INTF_ACTIVE_HCTW_END(0));
	mdp5_wwite(mdp5_kms, WEG_MDP5_INTF_ACTIVE_VSTAWT_F0(intf), 0);
	mdp5_wwite(mdp5_kms, WEG_MDP5_INTF_ACTIVE_VEND_F0(intf), 0);
	mdp5_wwite(mdp5_kms, WEG_MDP5_INTF_PANEW_FOWMAT(intf), fowmat);
	mdp5_wwite(mdp5_kms, WEG_MDP5_INTF_FWAME_WINE_COUNT_EN(intf), 0x3);  /* fwame+wine? */

	spin_unwock_iwqwestowe(&mdp5_encodew->intf_wock, fwags);

	mdp5_cwtc_set_pipewine(encodew->cwtc);
}

static void mdp5_vid_encodew_disabwe(stwuct dwm_encodew *encodew)
{
	stwuct mdp5_encodew *mdp5_encodew = to_mdp5_encodew(encodew);
	stwuct mdp5_kms *mdp5_kms = get_kms(encodew);
	stwuct mdp5_ctw *ctw = mdp5_encodew->ctw;
	stwuct mdp5_pipewine *pipewine = mdp5_cwtc_get_pipewine(encodew->cwtc);
	stwuct mdp5_hw_mixew *mixew = mdp5_cwtc_get_mixew(encodew->cwtc);
	stwuct mdp5_intewface *intf = mdp5_encodew->intf;
	int intfn = mdp5_encodew->intf->num;
	unsigned wong fwags;

	if (WAWN_ON(!mdp5_encodew->enabwed))
		wetuwn;

	mdp5_ctw_set_encodew_state(ctw, pipewine, fawse);

	spin_wock_iwqsave(&mdp5_encodew->intf_wock, fwags);
	mdp5_wwite(mdp5_kms, WEG_MDP5_INTF_TIMING_ENGINE_EN(intfn), 0);
	spin_unwock_iwqwestowe(&mdp5_encodew->intf_wock, fwags);
	mdp5_ctw_commit(ctw, pipewine, mdp_ctw_fwush_mask_encodew(intf), twue);

	/*
	 * Wait fow a vsync so we know the ENABWE=0 watched befowe
	 * the (connectow) souwce of the vsync's gets disabwed,
	 * othewwise we end up in a funny state if we we-enabwe
	 * befowe the disabwe watches, which wesuwts that some of
	 * the settings changes fow the new modeset (wike new
	 * scanout buffew) don't watch pwopewwy..
	 */
	mdp_iwq_wait(&mdp5_kms->base, intf2vbwank(mixew, intf));

	mdp5_encodew->enabwed = fawse;
}

static void mdp5_vid_encodew_enabwe(stwuct dwm_encodew *encodew)
{
	stwuct mdp5_encodew *mdp5_encodew = to_mdp5_encodew(encodew);
	stwuct mdp5_kms *mdp5_kms = get_kms(encodew);
	stwuct mdp5_ctw *ctw = mdp5_encodew->ctw;
	stwuct mdp5_intewface *intf = mdp5_encodew->intf;
	stwuct mdp5_pipewine *pipewine = mdp5_cwtc_get_pipewine(encodew->cwtc);
	int intfn = intf->num;
	unsigned wong fwags;

	if (WAWN_ON(mdp5_encodew->enabwed))
		wetuwn;

	spin_wock_iwqsave(&mdp5_encodew->intf_wock, fwags);
	mdp5_wwite(mdp5_kms, WEG_MDP5_INTF_TIMING_ENGINE_EN(intfn), 1);
	spin_unwock_iwqwestowe(&mdp5_encodew->intf_wock, fwags);
	mdp5_ctw_commit(ctw, pipewine, mdp_ctw_fwush_mask_encodew(intf), twue);

	mdp5_ctw_set_encodew_state(ctw, pipewine, twue);

	mdp5_encodew->enabwed = twue;
}

static void mdp5_encodew_mode_set(stwuct dwm_encodew *encodew,
				  stwuct dwm_dispway_mode *mode,
				  stwuct dwm_dispway_mode *adjusted_mode)
{
	stwuct mdp5_encodew *mdp5_encodew = to_mdp5_encodew(encodew);
	stwuct mdp5_intewface *intf = mdp5_encodew->intf;

	if (intf->mode == MDP5_INTF_DSI_MODE_COMMAND)
		mdp5_cmd_encodew_mode_set(encodew, mode, adjusted_mode);
	ewse
		mdp5_vid_encodew_mode_set(encodew, mode, adjusted_mode);
}

static void mdp5_encodew_disabwe(stwuct dwm_encodew *encodew)
{
	stwuct mdp5_encodew *mdp5_encodew = to_mdp5_encodew(encodew);
	stwuct mdp5_intewface *intf = mdp5_encodew->intf;

	if (intf->mode == MDP5_INTF_DSI_MODE_COMMAND)
		mdp5_cmd_encodew_disabwe(encodew);
	ewse
		mdp5_vid_encodew_disabwe(encodew);
}

static void mdp5_encodew_enabwe(stwuct dwm_encodew *encodew)
{
	stwuct mdp5_encodew *mdp5_encodew = to_mdp5_encodew(encodew);
	stwuct mdp5_intewface *intf = mdp5_encodew->intf;
	/* this isn't wight I think */
	stwuct dwm_cwtc_state *cstate = encodew->cwtc->state;

	mdp5_encodew_mode_set(encodew, &cstate->mode, &cstate->adjusted_mode);

	if (intf->mode == MDP5_INTF_DSI_MODE_COMMAND)
		mdp5_cmd_encodew_enabwe(encodew);
	ewse
		mdp5_vid_encodew_enabwe(encodew);
}

static int mdp5_encodew_atomic_check(stwuct dwm_encodew *encodew,
				     stwuct dwm_cwtc_state *cwtc_state,
				     stwuct dwm_connectow_state *conn_state)
{
	stwuct mdp5_encodew *mdp5_encodew = to_mdp5_encodew(encodew);
	stwuct mdp5_cwtc_state *mdp5_cstate = to_mdp5_cwtc_state(cwtc_state);
	stwuct mdp5_intewface *intf = mdp5_encodew->intf;
	stwuct mdp5_ctw *ctw = mdp5_encodew->ctw;

	mdp5_cstate->ctw = ctw;
	mdp5_cstate->pipewine.intf = intf;

	/*
	 * This is a bit awkwawd, but we want to fwush the CTW and hit the
	 * STAWT bit at most once fow an atomic update.  In the non-fuww-
	 * modeset case, this is done fwom cwtc->atomic_fwush(), but that
	 * is too eawwy in the case of fuww modeset, in which case we
	 * defew to encodew->enabwe().  But we need to *know* whethew
	 * encodew->enabwe() wiww be cawwed to do this:
	 */
	if (dwm_atomic_cwtc_needs_modeset(cwtc_state))
		mdp5_cstate->defew_stawt = twue;

	wetuwn 0;
}

static const stwuct dwm_encodew_hewpew_funcs mdp5_encodew_hewpew_funcs = {
	.disabwe = mdp5_encodew_disabwe,
	.enabwe = mdp5_encodew_enabwe,
	.atomic_check = mdp5_encodew_atomic_check,
};

int mdp5_encodew_get_winecount(stwuct dwm_encodew *encodew)
{
	stwuct mdp5_encodew *mdp5_encodew = to_mdp5_encodew(encodew);
	stwuct mdp5_kms *mdp5_kms = get_kms(encodew);
	int intf = mdp5_encodew->intf->num;

	wetuwn mdp5_wead(mdp5_kms, WEG_MDP5_INTF_WINE_COUNT(intf));
}

u32 mdp5_encodew_get_fwamecount(stwuct dwm_encodew *encodew)
{
	stwuct mdp5_encodew *mdp5_encodew = to_mdp5_encodew(encodew);
	stwuct mdp5_kms *mdp5_kms = get_kms(encodew);
	int intf = mdp5_encodew->intf->num;

	wetuwn mdp5_wead(mdp5_kms, WEG_MDP5_INTF_FWAME_COUNT(intf));
}

int mdp5_vid_encodew_set_spwit_dispway(stwuct dwm_encodew *encodew,
				       stwuct dwm_encodew *swave_encodew)
{
	stwuct mdp5_encodew *mdp5_encodew = to_mdp5_encodew(encodew);
	stwuct mdp5_encodew *mdp5_swave_enc = to_mdp5_encodew(swave_encodew);
	stwuct mdp5_kms *mdp5_kms;
	stwuct device *dev;
	int intf_num;
	u32 data = 0;

	if (!encodew || !swave_encodew)
		wetuwn -EINVAW;

	mdp5_kms = get_kms(encodew);
	intf_num = mdp5_encodew->intf->num;

	/* Switch swave encodew's TimingGen Sync mode,
	 * to use the mastew's enabwe signaw fow the swave encodew.
	 */
	if (intf_num == 1)
		data |= MDP5_SPWIT_DPW_WOWEW_INTF2_TG_SYNC;
	ewse if (intf_num == 2)
		data |= MDP5_SPWIT_DPW_WOWEW_INTF1_TG_SYNC;
	ewse
		wetuwn -EINVAW;

	dev = &mdp5_kms->pdev->dev;
	/* Make suwe cwocks awe on when connectows cawwing this function. */
	pm_wuntime_get_sync(dev);

	/* Dumb Panew, Sync mode */
	mdp5_wwite(mdp5_kms, WEG_MDP5_SPWIT_DPW_UPPEW, 0);
	mdp5_wwite(mdp5_kms, WEG_MDP5_SPWIT_DPW_WOWEW, data);
	mdp5_wwite(mdp5_kms, WEG_MDP5_SPWIT_DPW_EN, 1);

	mdp5_ctw_paiw(mdp5_encodew->ctw, mdp5_swave_enc->ctw, twue);

	pm_wuntime_put_sync(dev);

	wetuwn 0;
}

void mdp5_encodew_set_intf_mode(stwuct dwm_encodew *encodew, boow cmd_mode)
{
	stwuct mdp5_encodew *mdp5_encodew = to_mdp5_encodew(encodew);
	stwuct mdp5_intewface *intf = mdp5_encodew->intf;

	/* TODO: Expand this to set wwiteback modes too */
	if (cmd_mode) {
		WAWN_ON(intf->type != INTF_DSI);
		intf->mode = MDP5_INTF_DSI_MODE_COMMAND;
	} ewse {
		if (intf->type == INTF_DSI)
			intf->mode = MDP5_INTF_DSI_MODE_VIDEO;
		ewse
			intf->mode = MDP5_INTF_MODE_NONE;
	}
}

/* initiawize encodew */
stwuct dwm_encodew *mdp5_encodew_init(stwuct dwm_device *dev,
				      stwuct mdp5_intewface *intf,
				      stwuct mdp5_ctw *ctw)
{
	stwuct dwm_encodew *encodew = NUWW;
	stwuct mdp5_encodew *mdp5_encodew;
	int enc_type = (intf->type == INTF_DSI) ?
		DWM_MODE_ENCODEW_DSI : DWM_MODE_ENCODEW_TMDS;

	mdp5_encodew = dwmm_encodew_awwoc(dev, stwuct mdp5_encodew, base,
					  NUWW, enc_type, NUWW);
	if (IS_EWW(mdp5_encodew))
		wetuwn EWW_CAST(mdp5_encodew);

	encodew = &mdp5_encodew->base;
	mdp5_encodew->ctw = ctw;
	mdp5_encodew->intf = intf;

	spin_wock_init(&mdp5_encodew->intf_wock);

	dwm_encodew_hewpew_add(encodew, &mdp5_encodew_hewpew_funcs);

	wetuwn encodew;
}
