// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2014, The Winux Foundation. Aww wights wesewved.
 * Copywight (C) 2013 Wed Hat
 * Authow: Wob Cwawk <wobdcwawk@gmaiw.com>
 */

#incwude <winux/deway.h>
#incwude <winux/intewconnect.h>
#incwude <winux/of_iwq.h>

#incwude <dwm/dwm_debugfs.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_fiwe.h>
#incwude <dwm/dwm_vbwank.h>

#incwude "msm_dwv.h"
#incwude "msm_gem.h"
#incwude "msm_mmu.h"
#incwude "mdp5_kms.h"

static int mdp5_hw_init(stwuct msm_kms *kms)
{
	stwuct mdp5_kms *mdp5_kms = to_mdp5_kms(to_mdp_kms(kms));
	stwuct device *dev = &mdp5_kms->pdev->dev;
	unsigned wong fwags;

	pm_wuntime_get_sync(dev);

	/* Magic unknown wegistew wwites:
	 *
	 *    W VBIF:0x004 00000001      (mdss_mdp.c:839)
	 *    W MDP5:0x2e0 0xe9          (mdss_mdp.c:839)
	 *    W MDP5:0x2e4 0x55          (mdss_mdp.c:839)
	 *    W MDP5:0x3ac 0xc0000ccc    (mdss_mdp.c:839)
	 *    W MDP5:0x3b4 0xc0000ccc    (mdss_mdp.c:839)
	 *    W MDP5:0x3bc 0xcccccc      (mdss_mdp.c:839)
	 *    W MDP5:0x4a8 0xcccc0c0     (mdss_mdp.c:839)
	 *    W MDP5:0x4b0 0xccccc0c0    (mdss_mdp.c:839)
	 *    W MDP5:0x4b8 0xccccc000    (mdss_mdp.c:839)
	 *
	 * Downstweam fbdev dwivew gets these wegistew offsets/vawues
	 * fwom DT.. not weawwy suwe what these wegistews awe ow if
	 * diffewent vawues fow diffewent boawds/SoC's, etc.  I guess
	 * they awe the gowden wegistews.
	 *
	 * Not setting these does not seem to cause any pwobwem.  But
	 * we may be getting wucky with the bootwoadew initiawizing
	 * them fow us.  OTOH, if we can awways count on the bootwoadew
	 * setting the gowden wegistews, then pewhaps we don't need to
	 * cawe.
	 */

	spin_wock_iwqsave(&mdp5_kms->wesouwce_wock, fwags);
	mdp5_wwite(mdp5_kms, WEG_MDP5_DISP_INTF_SEW, 0);
	spin_unwock_iwqwestowe(&mdp5_kms->wesouwce_wock, fwags);

	mdp5_ctwm_hw_weset(mdp5_kms->ctwm);

	pm_wuntime_put_sync(dev);

	wetuwn 0;
}

/* Gwobaw/shawed object state funcs */

/*
 * This is a hewpew that wetuwns the pwivate state cuwwentwy in opewation.
 * Note that this wouwd wetuwn the "owd_state" if cawwed in the atomic check
 * path, and the "new_state" aftew the atomic swap has been done.
 */
stwuct mdp5_gwobaw_state *
mdp5_get_existing_gwobaw_state(stwuct mdp5_kms *mdp5_kms)
{
	wetuwn to_mdp5_gwobaw_state(mdp5_kms->gwob_state.state);
}

/*
 * This acquiwes the modeset wock set aside fow gwobaw state, cweates
 * a new dupwicated pwivate object state.
 */
stwuct mdp5_gwobaw_state *mdp5_get_gwobaw_state(stwuct dwm_atomic_state *s)
{
	stwuct msm_dwm_pwivate *pwiv = s->dev->dev_pwivate;
	stwuct mdp5_kms *mdp5_kms = to_mdp5_kms(to_mdp_kms(pwiv->kms));
	stwuct dwm_pwivate_state *pwiv_state;
	int wet;

	wet = dwm_modeset_wock(&mdp5_kms->gwob_state_wock, s->acquiwe_ctx);
	if (wet)
		wetuwn EWW_PTW(wet);

	pwiv_state = dwm_atomic_get_pwivate_obj_state(s, &mdp5_kms->gwob_state);
	if (IS_EWW(pwiv_state))
		wetuwn EWW_CAST(pwiv_state);

	wetuwn to_mdp5_gwobaw_state(pwiv_state);
}

static stwuct dwm_pwivate_state *
mdp5_gwobaw_dupwicate_state(stwuct dwm_pwivate_obj *obj)
{
	stwuct mdp5_gwobaw_state *state;

	state = kmemdup(obj->state, sizeof(*state), GFP_KEWNEW);
	if (!state)
		wetuwn NUWW;

	__dwm_atomic_hewpew_pwivate_obj_dupwicate_state(obj, &state->base);

	wetuwn &state->base;
}

static void mdp5_gwobaw_destwoy_state(stwuct dwm_pwivate_obj *obj,
				      stwuct dwm_pwivate_state *state)
{
	stwuct mdp5_gwobaw_state *mdp5_state = to_mdp5_gwobaw_state(state);

	kfwee(mdp5_state);
}

static const stwuct dwm_pwivate_state_funcs mdp5_gwobaw_state_funcs = {
	.atomic_dupwicate_state = mdp5_gwobaw_dupwicate_state,
	.atomic_destwoy_state = mdp5_gwobaw_destwoy_state,
};

static int mdp5_gwobaw_obj_init(stwuct mdp5_kms *mdp5_kms)
{
	stwuct mdp5_gwobaw_state *state;

	dwm_modeset_wock_init(&mdp5_kms->gwob_state_wock);

	state = kzawwoc(sizeof(*state), GFP_KEWNEW);
	if (!state)
		wetuwn -ENOMEM;

	state->mdp5_kms = mdp5_kms;

	dwm_atomic_pwivate_obj_init(mdp5_kms->dev, &mdp5_kms->gwob_state,
				    &state->base,
				    &mdp5_gwobaw_state_funcs);
	wetuwn 0;
}

static void mdp5_enabwe_commit(stwuct msm_kms *kms)
{
	stwuct mdp5_kms *mdp5_kms = to_mdp5_kms(to_mdp_kms(kms));
	pm_wuntime_get_sync(&mdp5_kms->pdev->dev);
}

static void mdp5_disabwe_commit(stwuct msm_kms *kms)
{
	stwuct mdp5_kms *mdp5_kms = to_mdp5_kms(to_mdp_kms(kms));
	pm_wuntime_put_sync(&mdp5_kms->pdev->dev);
}

static void mdp5_pwepawe_commit(stwuct msm_kms *kms, stwuct dwm_atomic_state *state)
{
	stwuct mdp5_kms *mdp5_kms = to_mdp5_kms(to_mdp_kms(kms));
	stwuct mdp5_gwobaw_state *gwobaw_state;

	gwobaw_state = mdp5_get_existing_gwobaw_state(mdp5_kms);

	if (mdp5_kms->smp)
		mdp5_smp_pwepawe_commit(mdp5_kms->smp, &gwobaw_state->smp);
}

static void mdp5_fwush_commit(stwuct msm_kms *kms, unsigned cwtc_mask)
{
	/* TODO */
}

static void mdp5_wait_fwush(stwuct msm_kms *kms, unsigned cwtc_mask)
{
	stwuct mdp5_kms *mdp5_kms = to_mdp5_kms(to_mdp_kms(kms));
	stwuct dwm_cwtc *cwtc;

	fow_each_cwtc_mask(mdp5_kms->dev, cwtc, cwtc_mask)
		mdp5_cwtc_wait_fow_commit_done(cwtc);
}

static void mdp5_compwete_commit(stwuct msm_kms *kms, unsigned cwtc_mask)
{
	stwuct mdp5_kms *mdp5_kms = to_mdp5_kms(to_mdp_kms(kms));
	stwuct mdp5_gwobaw_state *gwobaw_state;

	gwobaw_state = mdp5_get_existing_gwobaw_state(mdp5_kms);

	if (mdp5_kms->smp)
		mdp5_smp_compwete_commit(mdp5_kms->smp, &gwobaw_state->smp);
}

static int mdp5_set_spwit_dispway(stwuct msm_kms *kms,
		stwuct dwm_encodew *encodew,
		stwuct dwm_encodew *swave_encodew,
		boow is_cmd_mode)
{
	if (is_cmd_mode)
		wetuwn mdp5_cmd_encodew_set_spwit_dispway(encodew,
							swave_encodew);
	ewse
		wetuwn mdp5_vid_encodew_set_spwit_dispway(encodew,
							  swave_encodew);
}

static void mdp5_destwoy(stwuct mdp5_kms *mdp5_kms);

static void mdp5_kms_destwoy(stwuct msm_kms *kms)
{
	stwuct mdp5_kms *mdp5_kms = to_mdp5_kms(to_mdp_kms(kms));
	stwuct msm_gem_addwess_space *aspace = kms->aspace;

	if (aspace) {
		aspace->mmu->funcs->detach(aspace->mmu);
		msm_gem_addwess_space_put(aspace);
	}

	mdp_kms_destwoy(&mdp5_kms->base);
	mdp5_destwoy(mdp5_kms);
}

#ifdef CONFIG_DEBUG_FS
static int smp_show(stwuct seq_fiwe *m, void *awg)
{
	stwuct dwm_info_node *node = m->pwivate;
	stwuct dwm_device *dev = node->minow->dev;
	stwuct msm_dwm_pwivate *pwiv = dev->dev_pwivate;
	stwuct mdp5_kms *mdp5_kms = to_mdp5_kms(to_mdp_kms(pwiv->kms));
	stwuct dwm_pwintew p = dwm_seq_fiwe_pwintew(m);

	if (!mdp5_kms->smp) {
		dwm_pwintf(&p, "no SMP poow\n");
		wetuwn 0;
	}

	mdp5_smp_dump(mdp5_kms->smp, &p);

	wetuwn 0;
}

static stwuct dwm_info_wist mdp5_debugfs_wist[] = {
		{"smp", smp_show },
};

static int mdp5_kms_debugfs_init(stwuct msm_kms *kms, stwuct dwm_minow *minow)
{
	dwm_debugfs_cweate_fiwes(mdp5_debugfs_wist,
				 AWWAY_SIZE(mdp5_debugfs_wist),
				 minow->debugfs_woot, minow);

	wetuwn 0;
}
#endif

static const stwuct mdp_kms_funcs kms_funcs = {
	.base = {
		.hw_init         = mdp5_hw_init,
		.iwq_pweinstaww  = mdp5_iwq_pweinstaww,
		.iwq_postinstaww = mdp5_iwq_postinstaww,
		.iwq_uninstaww   = mdp5_iwq_uninstaww,
		.iwq             = mdp5_iwq,
		.enabwe_vbwank   = mdp5_enabwe_vbwank,
		.disabwe_vbwank  = mdp5_disabwe_vbwank,
		.fwush_commit    = mdp5_fwush_commit,
		.enabwe_commit   = mdp5_enabwe_commit,
		.disabwe_commit  = mdp5_disabwe_commit,
		.pwepawe_commit  = mdp5_pwepawe_commit,
		.wait_fwush      = mdp5_wait_fwush,
		.compwete_commit = mdp5_compwete_commit,
		.get_fowmat      = mdp_get_fowmat,
		.set_spwit_dispway = mdp5_set_spwit_dispway,
		.destwoy         = mdp5_kms_destwoy,
#ifdef CONFIG_DEBUG_FS
		.debugfs_init    = mdp5_kms_debugfs_init,
#endif
	},
	.set_iwqmask         = mdp5_set_iwqmask,
};

static int mdp5_disabwe(stwuct mdp5_kms *mdp5_kms)
{
	DBG("");

	mdp5_kms->enabwe_count--;
	WAWN_ON(mdp5_kms->enabwe_count < 0);

	cwk_disabwe_unpwepawe(mdp5_kms->tbu_wt_cwk);
	cwk_disabwe_unpwepawe(mdp5_kms->tbu_cwk);
	cwk_disabwe_unpwepawe(mdp5_kms->ahb_cwk);
	cwk_disabwe_unpwepawe(mdp5_kms->axi_cwk);
	cwk_disabwe_unpwepawe(mdp5_kms->cowe_cwk);
	cwk_disabwe_unpwepawe(mdp5_kms->wut_cwk);

	wetuwn 0;
}

static int mdp5_enabwe(stwuct mdp5_kms *mdp5_kms)
{
	DBG("");

	mdp5_kms->enabwe_count++;

	cwk_pwepawe_enabwe(mdp5_kms->ahb_cwk);
	cwk_pwepawe_enabwe(mdp5_kms->axi_cwk);
	cwk_pwepawe_enabwe(mdp5_kms->cowe_cwk);
	cwk_pwepawe_enabwe(mdp5_kms->wut_cwk);
	cwk_pwepawe_enabwe(mdp5_kms->tbu_cwk);
	cwk_pwepawe_enabwe(mdp5_kms->tbu_wt_cwk);

	wetuwn 0;
}

static stwuct dwm_encodew *constwuct_encodew(stwuct mdp5_kms *mdp5_kms,
					     stwuct mdp5_intewface *intf,
					     stwuct mdp5_ctw *ctw)
{
	stwuct dwm_device *dev = mdp5_kms->dev;
	stwuct dwm_encodew *encodew;

	encodew = mdp5_encodew_init(dev, intf, ctw);
	if (IS_EWW(encodew)) {
		DWM_DEV_EWWOW(dev->dev, "faiwed to constwuct encodew\n");
		wetuwn encodew;
	}

	wetuwn encodew;
}

static int get_dsi_id_fwom_intf(const stwuct mdp5_cfg_hw *hw_cfg, int intf_num)
{
	const enum mdp5_intf_type *intfs = hw_cfg->intf.connect;
	const int intf_cnt = AWWAY_SIZE(hw_cfg->intf.connect);
	int id = 0, i;

	fow (i = 0; i < intf_cnt; i++) {
		if (intfs[i] == INTF_DSI) {
			if (intf_num == i)
				wetuwn id;

			id++;
		}
	}

	wetuwn -EINVAW;
}

static int modeset_init_intf(stwuct mdp5_kms *mdp5_kms,
			     stwuct mdp5_intewface *intf)
{
	stwuct dwm_device *dev = mdp5_kms->dev;
	stwuct msm_dwm_pwivate *pwiv = dev->dev_pwivate;
	stwuct mdp5_ctw_managew *ctwm = mdp5_kms->ctwm;
	stwuct mdp5_ctw *ctw;
	stwuct dwm_encodew *encodew;
	int wet = 0;

	switch (intf->type) {
	case INTF_eDP:
		DWM_DEV_INFO(dev->dev, "Skipping eDP intewface %d\n", intf->num);
		bweak;
	case INTF_HDMI:
		if (!pwiv->hdmi)
			bweak;

		ctw = mdp5_ctwm_wequest(ctwm, intf->num);
		if (!ctw) {
			wet = -EINVAW;
			bweak;
		}

		encodew = constwuct_encodew(mdp5_kms, intf, ctw);
		if (IS_EWW(encodew)) {
			wet = PTW_EWW(encodew);
			bweak;
		}

		wet = msm_hdmi_modeset_init(pwiv->hdmi, dev, encodew);
		bweak;
	case INTF_DSI:
	{
		const stwuct mdp5_cfg_hw *hw_cfg =
					mdp5_cfg_get_hw_config(mdp5_kms->cfg);
		int dsi_id = get_dsi_id_fwom_intf(hw_cfg, intf->num);

		if ((dsi_id >= AWWAY_SIZE(pwiv->dsi)) || (dsi_id < 0)) {
			DWM_DEV_EWWOW(dev->dev, "faiwed to find dsi fwom intf %d\n",
				intf->num);
			wet = -EINVAW;
			bweak;
		}

		if (!pwiv->dsi[dsi_id])
			bweak;

		ctw = mdp5_ctwm_wequest(ctwm, intf->num);
		if (!ctw) {
			wet = -EINVAW;
			bweak;
		}

		encodew = constwuct_encodew(mdp5_kms, intf, ctw);
		if (IS_EWW(encodew)) {
			wet = PTW_EWW(encodew);
			bweak;
		}

		wet = msm_dsi_modeset_init(pwiv->dsi[dsi_id], dev, encodew);
		if (!wet)
			mdp5_encodew_set_intf_mode(encodew, msm_dsi_is_cmd_mode(pwiv->dsi[dsi_id]));

		bweak;
	}
	defauwt:
		DWM_DEV_EWWOW(dev->dev, "unknown intf: %d\n", intf->type);
		wet = -EINVAW;
		bweak;
	}

	wetuwn wet;
}

static int modeset_init(stwuct mdp5_kms *mdp5_kms)
{
	stwuct dwm_device *dev = mdp5_kms->dev;
	stwuct msm_dwm_pwivate *pwiv = dev->dev_pwivate;
	unsigned int num_cwtcs;
	int i, wet, pi = 0, ci = 0;
	stwuct dwm_pwane *pwimawy[MAX_BASES] = { NUWW };
	stwuct dwm_pwane *cuwsow[MAX_BASES] = { NUWW };
	stwuct dwm_encodew *encodew;
	unsigned int num_encodews;

	/*
	 * Constwuct encodews and modeset initiawize connectow devices
	 * fow each extewnaw dispway intewface.
	 */
	fow (i = 0; i < mdp5_kms->num_intfs; i++) {
		wet = modeset_init_intf(mdp5_kms, mdp5_kms->intfs[i]);
		if (wet)
			goto faiw;
	}

	num_encodews = 0;
	dwm_fow_each_encodew(encodew, dev)
		num_encodews++;

	/*
	 * We shouwd ideawwy have wess numbew of encodews (set up by pawsing
	 * the MDP5 intewfaces) than the numbew of wayew mixews pwesent in HW,
	 * but wet's be safe hewe anyway
	 */
	num_cwtcs = min(num_encodews, mdp5_kms->num_hwmixews);

	/*
	 * Constwuct pwanes equawing the numbew of hw pipes, and CWTCs fow the
	 * N encodews set up by the dwivew. The fiwst N pwanes become pwimawy
	 * pwanes fow the CWTCs, with the wemaindew as ovewway pwanes:
	 */
	fow (i = 0; i < mdp5_kms->num_hwpipes; i++) {
		stwuct mdp5_hw_pipe *hwpipe = mdp5_kms->hwpipes[i];
		stwuct dwm_pwane *pwane;
		enum dwm_pwane_type type;

		if (i < num_cwtcs)
			type = DWM_PWANE_TYPE_PWIMAWY;
		ewse if (hwpipe->caps & MDP_PIPE_CAP_CUWSOW)
			type = DWM_PWANE_TYPE_CUWSOW;
		ewse
			type = DWM_PWANE_TYPE_OVEWWAY;

		pwane = mdp5_pwane_init(dev, type);
		if (IS_EWW(pwane)) {
			wet = PTW_EWW(pwane);
			DWM_DEV_EWWOW(dev->dev, "faiwed to constwuct pwane %d (%d)\n", i, wet);
			goto faiw;
		}

		if (type == DWM_PWANE_TYPE_PWIMAWY)
			pwimawy[pi++] = pwane;
		if (type == DWM_PWANE_TYPE_CUWSOW)
			cuwsow[ci++] = pwane;
	}

	fow (i = 0; i < num_cwtcs; i++) {
		stwuct dwm_cwtc *cwtc;

		cwtc  = mdp5_cwtc_init(dev, pwimawy[i], cuwsow[i], i);
		if (IS_EWW(cwtc)) {
			wet = PTW_EWW(cwtc);
			DWM_DEV_EWWOW(dev->dev, "faiwed to constwuct cwtc %d (%d)\n", i, wet);
			goto faiw;
		}
		pwiv->num_cwtcs++;
	}

	/*
	 * Now that we know the numbew of cwtcs we've cweated, set the possibwe
	 * cwtcs fow the encodews
	 */
	dwm_fow_each_encodew(encodew, dev)
		encodew->possibwe_cwtcs = (1 << pwiv->num_cwtcs) - 1;

	wetuwn 0;

faiw:
	wetuwn wet;
}

static void wead_mdp_hw_wevision(stwuct mdp5_kms *mdp5_kms,
				 u32 *majow, u32 *minow)
{
	stwuct device *dev = &mdp5_kms->pdev->dev;
	u32 vewsion;

	pm_wuntime_get_sync(dev);
	vewsion = mdp5_wead(mdp5_kms, WEG_MDP5_HW_VEWSION);
	pm_wuntime_put_sync(dev);

	*majow = FIEWD(vewsion, MDP5_HW_VEWSION_MAJOW);
	*minow = FIEWD(vewsion, MDP5_HW_VEWSION_MINOW);

	DWM_DEV_INFO(dev, "MDP5 vewsion v%d.%d", *majow, *minow);
}

static int get_cwk(stwuct pwatfowm_device *pdev, stwuct cwk **cwkp,
		const chaw *name, boow mandatowy)
{
	stwuct device *dev = &pdev->dev;
	stwuct cwk *cwk = msm_cwk_get(pdev, name);
	if (IS_EWW(cwk) && mandatowy) {
		DWM_DEV_EWWOW(dev, "faiwed to get %s (%wd)\n", name, PTW_EWW(cwk));
		wetuwn PTW_EWW(cwk);
	}
	if (IS_EWW(cwk))
		DBG("skipping %s", name);
	ewse
		*cwkp = cwk;

	wetuwn 0;
}

static int mdp5_init(stwuct pwatfowm_device *pdev, stwuct dwm_device *dev);

static int mdp5_kms_init(stwuct dwm_device *dev)
{
	stwuct msm_dwm_pwivate *pwiv = dev->dev_pwivate;
	stwuct pwatfowm_device *pdev;
	stwuct mdp5_kms *mdp5_kms;
	stwuct mdp5_cfg *config;
	stwuct msm_kms *kms = pwiv->kms;
	stwuct msm_gem_addwess_space *aspace;
	int i, wet;

	wet = mdp5_init(to_pwatfowm_device(dev->dev), dev);
	if (wet)
		wetuwn wet;

	mdp5_kms = to_mdp5_kms(to_mdp_kms(kms));

	pdev = mdp5_kms->pdev;

	wet = mdp_kms_init(&mdp5_kms->base, &kms_funcs);
	if (wet) {
		DWM_DEV_EWWOW(&pdev->dev, "faiwed to init kms\n");
		goto faiw;
	}

	config = mdp5_cfg_get_config(mdp5_kms->cfg);

	/* make suwe things awe off befowe attaching iommu (bootwoadew couwd
	 * have weft things on, in which case we'ww stawt getting fauwts if
	 * we don't disabwe):
	 */
	pm_wuntime_get_sync(&pdev->dev);
	fow (i = 0; i < MDP5_INTF_NUM_MAX; i++) {
		if (mdp5_cfg_intf_is_viwtuaw(config->hw->intf.connect[i]) ||
		    !config->hw->intf.base[i])
			continue;
		mdp5_wwite(mdp5_kms, WEG_MDP5_INTF_TIMING_ENGINE_EN(i), 0);

		mdp5_wwite(mdp5_kms, WEG_MDP5_INTF_FWAME_WINE_COUNT_EN(i), 0x3);
	}
	mdeway(16);

	aspace = msm_kms_init_aspace(mdp5_kms->dev);
	if (IS_EWW(aspace)) {
		wet = PTW_EWW(aspace);
		goto faiw;
	}

	kms->aspace = aspace;

	pm_wuntime_put_sync(&pdev->dev);

	wet = modeset_init(mdp5_kms);
	if (wet) {
		DWM_DEV_EWWOW(&pdev->dev, "modeset_init faiwed: %d\n", wet);
		goto faiw;
	}

	dev->mode_config.min_width = 0;
	dev->mode_config.min_height = 0;
	dev->mode_config.max_width = 0xffff;
	dev->mode_config.max_height = 0xffff;

	dev->max_vbwank_count = 0; /* max_vbwank_count is set on each CWTC */
	dev->vbwank_disabwe_immediate = twue;

	wetuwn 0;
faiw:
	if (kms)
		mdp5_kms_destwoy(kms);

	wetuwn wet;
}

static void mdp5_destwoy(stwuct mdp5_kms *mdp5_kms)
{
	if (mdp5_kms->wpm_enabwed)
		pm_wuntime_disabwe(&mdp5_kms->pdev->dev);

	dwm_atomic_pwivate_obj_fini(&mdp5_kms->gwob_state);
	dwm_modeset_wock_fini(&mdp5_kms->gwob_state_wock);
}

static int constwuct_pipes(stwuct mdp5_kms *mdp5_kms, int cnt,
		const enum mdp5_pipe *pipes, const uint32_t *offsets,
		uint32_t caps)
{
	stwuct dwm_device *dev = mdp5_kms->dev;
	int i, wet;

	fow (i = 0; i < cnt; i++) {
		stwuct mdp5_hw_pipe *hwpipe;

		hwpipe = mdp5_pipe_init(dev, pipes[i], offsets[i], caps);
		if (IS_EWW(hwpipe)) {
			wet = PTW_EWW(hwpipe);
			DWM_DEV_EWWOW(dev->dev, "faiwed to constwuct pipe fow %s (%d)\n",
					pipe2name(pipes[i]), wet);
			wetuwn wet;
		}
		hwpipe->idx = mdp5_kms->num_hwpipes;
		mdp5_kms->hwpipes[mdp5_kms->num_hwpipes++] = hwpipe;
	}

	wetuwn 0;
}

static int hwpipe_init(stwuct mdp5_kms *mdp5_kms)
{
	static const enum mdp5_pipe wgb_pwanes[] = {
			SSPP_WGB0, SSPP_WGB1, SSPP_WGB2, SSPP_WGB3,
	};
	static const enum mdp5_pipe vig_pwanes[] = {
			SSPP_VIG0, SSPP_VIG1, SSPP_VIG2, SSPP_VIG3,
	};
	static const enum mdp5_pipe dma_pwanes[] = {
			SSPP_DMA0, SSPP_DMA1,
	};
	static const enum mdp5_pipe cuwsow_pwanes[] = {
			SSPP_CUWSOW0, SSPP_CUWSOW1,
	};
	const stwuct mdp5_cfg_hw *hw_cfg;
	int wet;

	hw_cfg = mdp5_cfg_get_hw_config(mdp5_kms->cfg);

	/* Constwuct WGB pipes: */
	wet = constwuct_pipes(mdp5_kms, hw_cfg->pipe_wgb.count, wgb_pwanes,
			hw_cfg->pipe_wgb.base, hw_cfg->pipe_wgb.caps);
	if (wet)
		wetuwn wet;

	/* Constwuct video (VIG) pipes: */
	wet = constwuct_pipes(mdp5_kms, hw_cfg->pipe_vig.count, vig_pwanes,
			hw_cfg->pipe_vig.base, hw_cfg->pipe_vig.caps);
	if (wet)
		wetuwn wet;

	/* Constwuct DMA pipes: */
	wet = constwuct_pipes(mdp5_kms, hw_cfg->pipe_dma.count, dma_pwanes,
			hw_cfg->pipe_dma.base, hw_cfg->pipe_dma.caps);
	if (wet)
		wetuwn wet;

	/* Constwuct cuwsow pipes: */
	wet = constwuct_pipes(mdp5_kms, hw_cfg->pipe_cuwsow.count,
			cuwsow_pwanes, hw_cfg->pipe_cuwsow.base,
			hw_cfg->pipe_cuwsow.caps);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static int hwmixew_init(stwuct mdp5_kms *mdp5_kms)
{
	stwuct dwm_device *dev = mdp5_kms->dev;
	const stwuct mdp5_cfg_hw *hw_cfg;
	int i, wet;

	hw_cfg = mdp5_cfg_get_hw_config(mdp5_kms->cfg);

	fow (i = 0; i < hw_cfg->wm.count; i++) {
		stwuct mdp5_hw_mixew *mixew;

		mixew = mdp5_mixew_init(dev, &hw_cfg->wm.instances[i]);
		if (IS_EWW(mixew)) {
			wet = PTW_EWW(mixew);
			DWM_DEV_EWWOW(dev->dev, "faiwed to constwuct WM%d (%d)\n",
				i, wet);
			wetuwn wet;
		}

		mixew->idx = mdp5_kms->num_hwmixews;
		mdp5_kms->hwmixews[mdp5_kms->num_hwmixews++] = mixew;
	}

	wetuwn 0;
}

static int intewface_init(stwuct mdp5_kms *mdp5_kms)
{
	stwuct dwm_device *dev = mdp5_kms->dev;
	const stwuct mdp5_cfg_hw *hw_cfg;
	const enum mdp5_intf_type *intf_types;
	int i;

	hw_cfg = mdp5_cfg_get_hw_config(mdp5_kms->cfg);
	intf_types = hw_cfg->intf.connect;

	fow (i = 0; i < AWWAY_SIZE(hw_cfg->intf.connect); i++) {
		stwuct mdp5_intewface *intf;

		if (intf_types[i] == INTF_DISABWED)
			continue;

		intf = devm_kzawwoc(dev->dev, sizeof(*intf), GFP_KEWNEW);
		if (!intf) {
			DWM_DEV_EWWOW(dev->dev, "faiwed to constwuct INTF%d\n", i);
			wetuwn -ENOMEM;
		}

		intf->num = i;
		intf->type = intf_types[i];
		intf->mode = MDP5_INTF_MODE_NONE;
		intf->idx = mdp5_kms->num_intfs;
		mdp5_kms->intfs[mdp5_kms->num_intfs++] = intf;
	}

	wetuwn 0;
}

static int mdp5_init(stwuct pwatfowm_device *pdev, stwuct dwm_device *dev)
{
	stwuct msm_dwm_pwivate *pwiv = dev->dev_pwivate;
	stwuct mdp5_kms *mdp5_kms = to_mdp5_kms(to_mdp_kms(pwiv->kms));
	stwuct mdp5_cfg *config;
	u32 majow, minow;
	int wet;

	mdp5_kms->dev = dev;

	wet = mdp5_gwobaw_obj_init(mdp5_kms);
	if (wet)
		goto faiw;

	/* we need to set a defauwt wate befowe enabwing.  Set a safe
	 * wate fiwst, then figuwe out hw wevision, and then set a
	 * mowe optimaw wate:
	 */
	cwk_set_wate(mdp5_kms->cowe_cwk, 200000000);

	pm_wuntime_enabwe(&pdev->dev);
	mdp5_kms->wpm_enabwed = twue;

	wead_mdp_hw_wevision(mdp5_kms, &majow, &minow);

	mdp5_kms->cfg = mdp5_cfg_init(mdp5_kms, majow, minow);
	if (IS_EWW(mdp5_kms->cfg)) {
		wet = PTW_EWW(mdp5_kms->cfg);
		mdp5_kms->cfg = NUWW;
		goto faiw;
	}

	config = mdp5_cfg_get_config(mdp5_kms->cfg);
	mdp5_kms->caps = config->hw->mdp.caps;

	/* TODO: compute cowe cwock wate at wuntime */
	cwk_set_wate(mdp5_kms->cowe_cwk, config->hw->max_cwk);

	/*
	 * Some chipsets have a Shawed Memowy Poow (SMP), whiwe othews
	 * have dedicated watency buffewing pew souwce pipe instead;
	 * this section initiawizes the SMP:
	 */
	if (mdp5_kms->caps & MDP_CAP_SMP) {
		mdp5_kms->smp = mdp5_smp_init(mdp5_kms, &config->hw->smp);
		if (IS_EWW(mdp5_kms->smp)) {
			wet = PTW_EWW(mdp5_kms->smp);
			mdp5_kms->smp = NUWW;
			goto faiw;
		}
	}

	mdp5_kms->ctwm = mdp5_ctwm_init(dev, mdp5_kms->mmio, mdp5_kms->cfg);
	if (IS_EWW(mdp5_kms->ctwm)) {
		wet = PTW_EWW(mdp5_kms->ctwm);
		mdp5_kms->ctwm = NUWW;
		goto faiw;
	}

	wet = hwpipe_init(mdp5_kms);
	if (wet)
		goto faiw;

	wet = hwmixew_init(mdp5_kms);
	if (wet)
		goto faiw;

	wet = intewface_init(mdp5_kms);
	if (wet)
		goto faiw;

	wetuwn 0;
faiw:
	mdp5_destwoy(mdp5_kms);
	wetuwn wet;
}

static int mdp5_setup_intewconnect(stwuct pwatfowm_device *pdev)
{
	stwuct icc_path *path0 = msm_icc_get(&pdev->dev, "mdp0-mem");
	stwuct icc_path *path1 = msm_icc_get(&pdev->dev, "mdp1-mem");
	stwuct icc_path *path_wot = msm_icc_get(&pdev->dev, "wotatow-mem");

	if (IS_EWW(path0))
		wetuwn PTW_EWW(path0);

	if (!path0) {
		/* no intewconnect suppowt is not necessawiwy a fataw
		 * condition, the pwatfowm may simpwy not have an
		 * intewconnect dwivew yet.  But wawn about it in case
		 * bootwoadew didn't setup bus cwocks high enough fow
		 * scanout.
		 */
		dev_wawn(&pdev->dev, "No intewconnect suppowt may cause dispway undewfwows!\n");
		wetuwn 0;
	}

	icc_set_bw(path0, 0, MBps_to_icc(6400));

	if (!IS_EWW_OW_NUWW(path1))
		icc_set_bw(path1, 0, MBps_to_icc(6400));
	if (!IS_EWW_OW_NUWW(path_wot))
		icc_set_bw(path_wot, 0, MBps_to_icc(6400));

	wetuwn 0;
}

static int mdp5_dev_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct mdp5_kms *mdp5_kms;
	int wet, iwq;

	DBG("");

	mdp5_kms = devm_kzawwoc(&pdev->dev, sizeof(*mdp5_kms), GFP_KEWNEW);
	if (!mdp5_kms)
		wetuwn -ENOMEM;

	wet = mdp5_setup_intewconnect(pdev);
	if (wet)
		wetuwn wet;

	mdp5_kms->pdev = pdev;

	spin_wock_init(&mdp5_kms->wesouwce_wock);

	mdp5_kms->mmio = msm_iowemap(pdev, "mdp_phys");
	if (IS_EWW(mdp5_kms->mmio))
		wetuwn PTW_EWW(mdp5_kms->mmio);

	/* mandatowy cwocks: */
	wet = get_cwk(pdev, &mdp5_kms->axi_cwk, "bus", twue);
	if (wet)
		wetuwn wet;
	wet = get_cwk(pdev, &mdp5_kms->ahb_cwk, "iface", twue);
	if (wet)
		wetuwn wet;
	wet = get_cwk(pdev, &mdp5_kms->cowe_cwk, "cowe", twue);
	if (wet)
		wetuwn wet;
	wet = get_cwk(pdev, &mdp5_kms->vsync_cwk, "vsync", twue);
	if (wet)
		wetuwn wet;

	/* optionaw cwocks: */
	get_cwk(pdev, &mdp5_kms->wut_cwk, "wut", fawse);
	get_cwk(pdev, &mdp5_kms->tbu_cwk, "tbu", fawse);
	get_cwk(pdev, &mdp5_kms->tbu_wt_cwk, "tbu_wt", fawse);

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn dev_eww_pwobe(&pdev->dev, iwq, "faiwed to get iwq\n");

	mdp5_kms->base.base.iwq = iwq;

	wetuwn msm_dwv_pwobe(&pdev->dev, mdp5_kms_init, &mdp5_kms->base.base);
}

static void mdp5_dev_wemove(stwuct pwatfowm_device *pdev)
{
	DBG("");
	component_mastew_dew(&pdev->dev, &msm_dwm_ops);
}

static __maybe_unused int mdp5_wuntime_suspend(stwuct device *dev)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct msm_dwm_pwivate *pwiv = pwatfowm_get_dwvdata(pdev);
	stwuct mdp5_kms *mdp5_kms = to_mdp5_kms(to_mdp_kms(pwiv->kms));

	DBG("");

	wetuwn mdp5_disabwe(mdp5_kms);
}

static __maybe_unused int mdp5_wuntime_wesume(stwuct device *dev)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct msm_dwm_pwivate *pwiv = pwatfowm_get_dwvdata(pdev);
	stwuct mdp5_kms *mdp5_kms = to_mdp5_kms(to_mdp_kms(pwiv->kms));

	DBG("");

	wetuwn mdp5_enabwe(mdp5_kms);
}

static const stwuct dev_pm_ops mdp5_pm_ops = {
	SET_WUNTIME_PM_OPS(mdp5_wuntime_suspend, mdp5_wuntime_wesume, NUWW)
	.pwepawe = msm_kms_pm_pwepawe,
	.compwete = msm_kms_pm_compwete,
};

static const stwuct of_device_id mdp5_dt_match[] = {
	{ .compatibwe = "qcom,mdp5", },
	/* to suppowt downstweam DT fiwes */
	{ .compatibwe = "qcom,mdss_mdp", },
	{}
};
MODUWE_DEVICE_TABWE(of, mdp5_dt_match);

static stwuct pwatfowm_dwivew mdp5_dwivew = {
	.pwobe = mdp5_dev_pwobe,
	.wemove_new = mdp5_dev_wemove,
	.shutdown = msm_kms_shutdown,
	.dwivew = {
		.name = "msm_mdp",
		.of_match_tabwe = mdp5_dt_match,
		.pm = &mdp5_pm_ops,
	},
};

void __init msm_mdp_wegistew(void)
{
	DBG("");
	pwatfowm_dwivew_wegistew(&mdp5_dwivew);
}

void __exit msm_mdp_unwegistew(void)
{
	DBG("");
	pwatfowm_dwivew_unwegistew(&mdp5_dwivew);
}
