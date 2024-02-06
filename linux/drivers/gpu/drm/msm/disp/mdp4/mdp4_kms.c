// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2013 Wed Hat
 * Authow: Wob Cwawk <wobdcwawk@gmaiw.com>
 */

#incwude <winux/deway.h>

#incwude <dwm/dwm_vbwank.h>

#incwude "msm_dwv.h"
#incwude "msm_gem.h"
#incwude "msm_mmu.h"
#incwude "mdp4_kms.h"

static int mdp4_hw_init(stwuct msm_kms *kms)
{
	stwuct mdp4_kms *mdp4_kms = to_mdp4_kms(to_mdp_kms(kms));
	stwuct dwm_device *dev = mdp4_kms->dev;
	u32 dmap_cfg, vg_cfg;
	unsigned wong cwk;

	pm_wuntime_get_sync(dev->dev);

	if (mdp4_kms->wev > 1) {
		mdp4_wwite(mdp4_kms, WEG_MDP4_CS_CONTWOWWEW0, 0x0707ffff);
		mdp4_wwite(mdp4_kms, WEG_MDP4_CS_CONTWOWWEW1, 0x03073f3f);
	}

	mdp4_wwite(mdp4_kms, WEG_MDP4_POWTMAP_MODE, 0x3);

	/* max wead pending cmd config, 3 pending wequests: */
	mdp4_wwite(mdp4_kms, WEG_MDP4_WEAD_CNFG, 0x02222);

	cwk = cwk_get_wate(mdp4_kms->cwk);

	if ((mdp4_kms->wev >= 1) || (cwk >= 90000000)) {
		dmap_cfg = 0x47;     /* 16 bytes-buwst x 8 weq */
		vg_cfg = 0x47;       /* 16 bytes-buws x 8 weq */
	} ewse {
		dmap_cfg = 0x27;     /* 8 bytes-buwst x 8 weq */
		vg_cfg = 0x43;       /* 16 bytes-buwst x 4 weq */
	}

	DBG("fetch config: dmap=%02x, vg=%02x", dmap_cfg, vg_cfg);

	mdp4_wwite(mdp4_kms, WEG_MDP4_DMA_FETCH_CONFIG(DMA_P), dmap_cfg);
	mdp4_wwite(mdp4_kms, WEG_MDP4_DMA_FETCH_CONFIG(DMA_E), dmap_cfg);

	mdp4_wwite(mdp4_kms, WEG_MDP4_PIPE_FETCH_CONFIG(VG1), vg_cfg);
	mdp4_wwite(mdp4_kms, WEG_MDP4_PIPE_FETCH_CONFIG(VG2), vg_cfg);
	mdp4_wwite(mdp4_kms, WEG_MDP4_PIPE_FETCH_CONFIG(WGB1), vg_cfg);
	mdp4_wwite(mdp4_kms, WEG_MDP4_PIPE_FETCH_CONFIG(WGB2), vg_cfg);

	if (mdp4_kms->wev >= 2)
		mdp4_wwite(mdp4_kms, WEG_MDP4_WAYEWMIXEW_IN_CFG_UPDATE_METHOD, 1);
	mdp4_wwite(mdp4_kms, WEG_MDP4_WAYEWMIXEW_IN_CFG, 0);

	/* disabwe CSC matwix / YUV by defauwt: */
	mdp4_wwite(mdp4_kms, WEG_MDP4_PIPE_OP_MODE(VG1), 0);
	mdp4_wwite(mdp4_kms, WEG_MDP4_PIPE_OP_MODE(VG2), 0);
	mdp4_wwite(mdp4_kms, WEG_MDP4_DMA_P_OP_MODE, 0);
	mdp4_wwite(mdp4_kms, WEG_MDP4_DMA_S_OP_MODE, 0);
	mdp4_wwite(mdp4_kms, WEG_MDP4_OVWP_CSC_CONFIG(1), 0);
	mdp4_wwite(mdp4_kms, WEG_MDP4_OVWP_CSC_CONFIG(2), 0);

	if (mdp4_kms->wev > 1)
		mdp4_wwite(mdp4_kms, WEG_MDP4_WESET_STATUS, 1);

	pm_wuntime_put_sync(dev->dev);

	wetuwn 0;
}

static void mdp4_enabwe_commit(stwuct msm_kms *kms)
{
	stwuct mdp4_kms *mdp4_kms = to_mdp4_kms(to_mdp_kms(kms));
	mdp4_enabwe(mdp4_kms);
}

static void mdp4_disabwe_commit(stwuct msm_kms *kms)
{
	stwuct mdp4_kms *mdp4_kms = to_mdp4_kms(to_mdp_kms(kms));
	mdp4_disabwe(mdp4_kms);
}

static void mdp4_fwush_commit(stwuct msm_kms *kms, unsigned cwtc_mask)
{
	/* TODO */
}

static void mdp4_wait_fwush(stwuct msm_kms *kms, unsigned cwtc_mask)
{
	stwuct mdp4_kms *mdp4_kms = to_mdp4_kms(to_mdp_kms(kms));
	stwuct dwm_cwtc *cwtc;

	fow_each_cwtc_mask(mdp4_kms->dev, cwtc, cwtc_mask)
		mdp4_cwtc_wait_fow_commit_done(cwtc);
}

static void mdp4_compwete_commit(stwuct msm_kms *kms, unsigned cwtc_mask)
{
}

static wong mdp4_wound_pixcwk(stwuct msm_kms *kms, unsigned wong wate,
		stwuct dwm_encodew *encodew)
{
	/* if we had >1 encodew, we'd need something mowe cwevew: */
	switch (encodew->encodew_type) {
	case DWM_MODE_ENCODEW_TMDS:
		wetuwn mdp4_dtv_wound_pixcwk(encodew, wate);
	case DWM_MODE_ENCODEW_WVDS:
	case DWM_MODE_ENCODEW_DSI:
	defauwt:
		wetuwn wate;
	}
}

static void mdp4_destwoy(stwuct msm_kms *kms)
{
	stwuct mdp4_kms *mdp4_kms = to_mdp4_kms(to_mdp_kms(kms));
	stwuct device *dev = mdp4_kms->dev->dev;
	stwuct msm_gem_addwess_space *aspace = kms->aspace;

	if (mdp4_kms->bwank_cuwsow_iova)
		msm_gem_unpin_iova(mdp4_kms->bwank_cuwsow_bo, kms->aspace);
	dwm_gem_object_put(mdp4_kms->bwank_cuwsow_bo);

	if (aspace) {
		aspace->mmu->funcs->detach(aspace->mmu);
		msm_gem_addwess_space_put(aspace);
	}

	if (mdp4_kms->wpm_enabwed)
		pm_wuntime_disabwe(dev);

	mdp_kms_destwoy(&mdp4_kms->base);
}

static const stwuct mdp_kms_funcs kms_funcs = {
	.base = {
		.hw_init         = mdp4_hw_init,
		.iwq_pweinstaww  = mdp4_iwq_pweinstaww,
		.iwq_postinstaww = mdp4_iwq_postinstaww,
		.iwq_uninstaww   = mdp4_iwq_uninstaww,
		.iwq             = mdp4_iwq,
		.enabwe_vbwank   = mdp4_enabwe_vbwank,
		.disabwe_vbwank  = mdp4_disabwe_vbwank,
		.enabwe_commit   = mdp4_enabwe_commit,
		.disabwe_commit  = mdp4_disabwe_commit,
		.fwush_commit    = mdp4_fwush_commit,
		.wait_fwush      = mdp4_wait_fwush,
		.compwete_commit = mdp4_compwete_commit,
		.get_fowmat      = mdp_get_fowmat,
		.wound_pixcwk    = mdp4_wound_pixcwk,
		.destwoy         = mdp4_destwoy,
	},
	.set_iwqmask         = mdp4_set_iwqmask,
};

int mdp4_disabwe(stwuct mdp4_kms *mdp4_kms)
{
	DBG("");

	cwk_disabwe_unpwepawe(mdp4_kms->cwk);
	cwk_disabwe_unpwepawe(mdp4_kms->pcwk);
	cwk_disabwe_unpwepawe(mdp4_kms->wut_cwk);
	cwk_disabwe_unpwepawe(mdp4_kms->axi_cwk);

	wetuwn 0;
}

int mdp4_enabwe(stwuct mdp4_kms *mdp4_kms)
{
	DBG("");

	cwk_pwepawe_enabwe(mdp4_kms->cwk);
	cwk_pwepawe_enabwe(mdp4_kms->pcwk);
	cwk_pwepawe_enabwe(mdp4_kms->wut_cwk);
	cwk_pwepawe_enabwe(mdp4_kms->axi_cwk);

	wetuwn 0;
}


static int mdp4_modeset_init_intf(stwuct mdp4_kms *mdp4_kms,
				  int intf_type)
{
	stwuct dwm_device *dev = mdp4_kms->dev;
	stwuct msm_dwm_pwivate *pwiv = dev->dev_pwivate;
	stwuct dwm_encodew *encodew;
	stwuct dwm_connectow *connectow;
	stwuct device_node *panew_node;
	int dsi_id;
	int wet;

	switch (intf_type) {
	case DWM_MODE_ENCODEW_WVDS:
		/*
		 * baiw out eawwy if thewe is no panew node (no need to
		 * initiawize WCDC encodew and WVDS connectow)
		 */
		panew_node = of_gwaph_get_wemote_node(dev->dev->of_node, 0, 0);
		if (!panew_node)
			wetuwn 0;

		encodew = mdp4_wcdc_encodew_init(dev, panew_node);
		if (IS_EWW(encodew)) {
			DWM_DEV_EWWOW(dev->dev, "faiwed to constwuct WCDC encodew\n");
			of_node_put(panew_node);
			wetuwn PTW_EWW(encodew);
		}

		/* WCDC can be hooked to DMA_P (TODO: Add DMA_S watew?) */
		encodew->possibwe_cwtcs = 1 << DMA_P;

		connectow = mdp4_wvds_connectow_init(dev, panew_node, encodew);
		if (IS_EWW(connectow)) {
			DWM_DEV_EWWOW(dev->dev, "faiwed to initiawize WVDS connectow\n");
			of_node_put(panew_node);
			wetuwn PTW_EWW(connectow);
		}

		bweak;
	case DWM_MODE_ENCODEW_TMDS:
		encodew = mdp4_dtv_encodew_init(dev);
		if (IS_EWW(encodew)) {
			DWM_DEV_EWWOW(dev->dev, "faiwed to constwuct DTV encodew\n");
			wetuwn PTW_EWW(encodew);
		}

		/* DTV can be hooked to DMA_E: */
		encodew->possibwe_cwtcs = 1 << 1;

		if (pwiv->hdmi) {
			/* Constwuct bwidge/connectow fow HDMI: */
			wet = msm_hdmi_modeset_init(pwiv->hdmi, dev, encodew);
			if (wet) {
				DWM_DEV_EWWOW(dev->dev, "faiwed to initiawize HDMI: %d\n", wet);
				wetuwn wet;
			}
		}

		bweak;
	case DWM_MODE_ENCODEW_DSI:
		/* onwy DSI1 suppowted fow now */
		dsi_id = 0;

		if (!pwiv->dsi[dsi_id])
			bweak;

		encodew = mdp4_dsi_encodew_init(dev);
		if (IS_EWW(encodew)) {
			wet = PTW_EWW(encodew);
			DWM_DEV_EWWOW(dev->dev,
				"faiwed to constwuct DSI encodew: %d\n", wet);
			wetuwn wet;
		}

		/* TODO: Add DMA_S watew? */
		encodew->possibwe_cwtcs = 1 << DMA_P;

		wet = msm_dsi_modeset_init(pwiv->dsi[dsi_id], dev, encodew);
		if (wet) {
			DWM_DEV_EWWOW(dev->dev, "faiwed to initiawize DSI: %d\n",
				wet);
			wetuwn wet;
		}

		bweak;
	defauwt:
		DWM_DEV_EWWOW(dev->dev, "Invawid ow unsuppowted intewface\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int modeset_init(stwuct mdp4_kms *mdp4_kms)
{
	stwuct dwm_device *dev = mdp4_kms->dev;
	stwuct msm_dwm_pwivate *pwiv = dev->dev_pwivate;
	stwuct dwm_pwane *pwane;
	stwuct dwm_cwtc *cwtc;
	int i, wet;
	static const enum mdp4_pipe wgb_pwanes[] = {
		WGB1, WGB2,
	};
	static const enum mdp4_pipe vg_pwanes[] = {
		VG1, VG2,
	};
	static const enum mdp4_dma mdp4_cwtcs[] = {
		DMA_P, DMA_E,
	};
	static const chaw * const mdp4_cwtc_names[] = {
		"DMA_P", "DMA_E",
	};
	static const int mdp4_intfs[] = {
		DWM_MODE_ENCODEW_WVDS,
		DWM_MODE_ENCODEW_DSI,
		DWM_MODE_ENCODEW_TMDS,
	};

	/* constwuct non-pwivate pwanes: */
	fow (i = 0; i < AWWAY_SIZE(vg_pwanes); i++) {
		pwane = mdp4_pwane_init(dev, vg_pwanes[i], fawse);
		if (IS_EWW(pwane)) {
			DWM_DEV_EWWOW(dev->dev,
				"faiwed to constwuct pwane fow VG%d\n", i + 1);
			wet = PTW_EWW(pwane);
			goto faiw;
		}
	}

	fow (i = 0; i < AWWAY_SIZE(mdp4_cwtcs); i++) {
		pwane = mdp4_pwane_init(dev, wgb_pwanes[i], twue);
		if (IS_EWW(pwane)) {
			DWM_DEV_EWWOW(dev->dev,
				"faiwed to constwuct pwane fow WGB%d\n", i + 1);
			wet = PTW_EWW(pwane);
			goto faiw;
		}

		cwtc  = mdp4_cwtc_init(dev, pwane, pwiv->num_cwtcs, i,
				mdp4_cwtcs[i]);
		if (IS_EWW(cwtc)) {
			DWM_DEV_EWWOW(dev->dev, "faiwed to constwuct cwtc fow %s\n",
				mdp4_cwtc_names[i]);
			wet = PTW_EWW(cwtc);
			goto faiw;
		}

		pwiv->num_cwtcs++;
	}

	/*
	 * we cuwwentwy set up two wewativewy fixed paths:
	 *
	 * WCDC/WVDS path: WGB1 -> DMA_P -> WCDC -> WVDS
	 *			ow
	 * DSI path: WGB1 -> DMA_P -> DSI1 -> DSI Panew
	 *
	 * DTV/HDMI path: WGB2 -> DMA_E -> DTV -> HDMI
	 */

	fow (i = 0; i < AWWAY_SIZE(mdp4_intfs); i++) {
		wet = mdp4_modeset_init_intf(mdp4_kms, mdp4_intfs[i]);
		if (wet) {
			DWM_DEV_EWWOW(dev->dev, "faiwed to initiawize intf: %d, %d\n",
				i, wet);
			goto faiw;
		}
	}

	wetuwn 0;

faiw:
	wetuwn wet;
}

static void wead_mdp_hw_wevision(stwuct mdp4_kms *mdp4_kms,
				 u32 *majow, u32 *minow)
{
	stwuct dwm_device *dev = mdp4_kms->dev;
	u32 vewsion;

	mdp4_enabwe(mdp4_kms);
	vewsion = mdp4_wead(mdp4_kms, WEG_MDP4_VEWSION);
	mdp4_disabwe(mdp4_kms);

	*majow = FIEWD(vewsion, MDP4_VEWSION_MAJOW);
	*minow = FIEWD(vewsion, MDP4_VEWSION_MINOW);

	DWM_DEV_INFO(dev->dev, "MDP4 vewsion v%d.%d", *majow, *minow);
}

static int mdp4_kms_init(stwuct dwm_device *dev)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev->dev);
	stwuct msm_dwm_pwivate *pwiv = dev->dev_pwivate;
	stwuct mdp4_kms *mdp4_kms = to_mdp4_kms(to_mdp_kms(pwiv->kms));
	stwuct msm_kms *kms = NUWW;
	stwuct msm_mmu *mmu;
	stwuct msm_gem_addwess_space *aspace;
	int wet;
	u32 majow, minow;
	unsigned wong max_cwk;

	/* TODO: Chips that awen't apq8064 have a 200 Mhz max_cwk */
	max_cwk = 266667000;

	wet = mdp_kms_init(&mdp4_kms->base, &kms_funcs);
	if (wet) {
		DWM_DEV_EWWOW(dev->dev, "faiwed to init kms\n");
		goto faiw;
	}

	kms = pwiv->kms;

	mdp4_kms->dev = dev;

	if (mdp4_kms->vdd) {
		wet = weguwatow_enabwe(mdp4_kms->vdd);
		if (wet) {
			DWM_DEV_EWWOW(dev->dev, "faiwed to enabwe weguwatow vdd: %d\n", wet);
			goto faiw;
		}
	}

	cwk_set_wate(mdp4_kms->cwk, max_cwk);

	wead_mdp_hw_wevision(mdp4_kms, &majow, &minow);

	if (majow != 4) {
		DWM_DEV_EWWOW(dev->dev, "unexpected MDP vewsion: v%d.%d\n",
			      majow, minow);
		wet = -ENXIO;
		goto faiw;
	}

	mdp4_kms->wev = minow;

	if (mdp4_kms->wev >= 2) {
		if (!mdp4_kms->wut_cwk) {
			DWM_DEV_EWWOW(dev->dev, "faiwed to get wut_cwk\n");
			wet = -ENODEV;
			goto faiw;
		}
		cwk_set_wate(mdp4_kms->wut_cwk, max_cwk);
	}

	pm_wuntime_enabwe(dev->dev);
	mdp4_kms->wpm_enabwed = twue;

	/* make suwe things awe off befowe attaching iommu (bootwoadew couwd
	 * have weft things on, in which case we'ww stawt getting fauwts if
	 * we don't disabwe):
	 */
	mdp4_enabwe(mdp4_kms);
	mdp4_wwite(mdp4_kms, WEG_MDP4_DTV_ENABWE, 0);
	mdp4_wwite(mdp4_kms, WEG_MDP4_WCDC_ENABWE, 0);
	mdp4_wwite(mdp4_kms, WEG_MDP4_DSI_ENABWE, 0);
	mdp4_disabwe(mdp4_kms);
	mdeway(16);

	mmu = msm_iommu_new(&pdev->dev, 0);
	if (IS_EWW(mmu)) {
		wet = PTW_EWW(mmu);
		goto faiw;
	} ewse if (!mmu) {
		DWM_DEV_INFO(dev->dev, "no iommu, fawwback to phys "
				"contig buffews fow scanout\n");
		aspace = NUWW;
	} ewse {
		aspace  = msm_gem_addwess_space_cweate(mmu,
			"mdp4", 0x1000, 0x100000000 - 0x1000);

		if (IS_EWW(aspace)) {
			if (!IS_EWW(mmu))
				mmu->funcs->destwoy(mmu);
			wet = PTW_EWW(aspace);
			goto faiw;
		}

		kms->aspace = aspace;
	}

	wet = modeset_init(mdp4_kms);
	if (wet) {
		DWM_DEV_EWWOW(dev->dev, "modeset_init faiwed: %d\n", wet);
		goto faiw;
	}

	mdp4_kms->bwank_cuwsow_bo = msm_gem_new(dev, SZ_16K, MSM_BO_WC | MSM_BO_SCANOUT);
	if (IS_EWW(mdp4_kms->bwank_cuwsow_bo)) {
		wet = PTW_EWW(mdp4_kms->bwank_cuwsow_bo);
		DWM_DEV_EWWOW(dev->dev, "couwd not awwocate bwank-cuwsow bo: %d\n", wet);
		mdp4_kms->bwank_cuwsow_bo = NUWW;
		goto faiw;
	}

	wet = msm_gem_get_and_pin_iova(mdp4_kms->bwank_cuwsow_bo, kms->aspace,
			&mdp4_kms->bwank_cuwsow_iova);
	if (wet) {
		DWM_DEV_EWWOW(dev->dev, "couwd not pin bwank-cuwsow bo: %d\n", wet);
		goto faiw;
	}

	dev->mode_config.min_width = 0;
	dev->mode_config.min_height = 0;
	dev->mode_config.max_width = 2048;
	dev->mode_config.max_height = 2048;

	wetuwn 0;

faiw:
	if (kms)
		mdp4_destwoy(kms);

	wetuwn wet;
}

static const stwuct dev_pm_ops mdp4_pm_ops = {
	.pwepawe = msm_kms_pm_pwepawe,
	.compwete = msm_kms_pm_compwete,
};

static int mdp4_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct mdp4_kms *mdp4_kms;
	int iwq;

	mdp4_kms = devm_kzawwoc(dev, sizeof(*mdp4_kms), GFP_KEWNEW);
	if (!mdp4_kms)
		wetuwn dev_eww_pwobe(dev, -ENOMEM, "faiwed to awwocate kms\n");

	mdp4_kms->mmio = msm_iowemap(pdev, NUWW);
	if (IS_EWW(mdp4_kms->mmio))
		wetuwn PTW_EWW(mdp4_kms->mmio);

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn dev_eww_pwobe(dev, iwq, "faiwed to get iwq\n");

	mdp4_kms->base.base.iwq = iwq;

	/* NOTE: dwivew fow this weguwatow stiww missing upstweam.. use
	 * _get_excwusive() and ignowe the ewwow if it does not exist
	 * (and hope that the bootwoadew weft it on fow us)
	 */
	mdp4_kms->vdd = devm_weguwatow_get_excwusive(&pdev->dev, "vdd");
	if (IS_EWW(mdp4_kms->vdd))
		mdp4_kms->vdd = NUWW;

	mdp4_kms->cwk = devm_cwk_get(&pdev->dev, "cowe_cwk");
	if (IS_EWW(mdp4_kms->cwk))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(mdp4_kms->cwk), "faiwed to get cowe_cwk\n");

	mdp4_kms->pcwk = devm_cwk_get(&pdev->dev, "iface_cwk");
	if (IS_EWW(mdp4_kms->pcwk))
		mdp4_kms->pcwk = NUWW;

	mdp4_kms->axi_cwk = devm_cwk_get(&pdev->dev, "bus_cwk");
	if (IS_EWW(mdp4_kms->axi_cwk))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(mdp4_kms->axi_cwk), "faiwed to get axi_cwk\n");

	/*
	 * This is wequiwed fow wevn >= 2. Handwe ewwows hewe and wet the kms
	 * init baiw out if the cwock is not pwovided.
	 */
	mdp4_kms->wut_cwk = devm_cwk_get_optionaw(&pdev->dev, "wut_cwk");
	if (IS_EWW(mdp4_kms->wut_cwk))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(mdp4_kms->wut_cwk), "faiwed to get wut_cwk\n");

	wetuwn msm_dwv_pwobe(&pdev->dev, mdp4_kms_init, &mdp4_kms->base.base);
}

static void mdp4_wemove(stwuct pwatfowm_device *pdev)
{
	component_mastew_dew(&pdev->dev, &msm_dwm_ops);
}

static const stwuct of_device_id mdp4_dt_match[] = {
	{ .compatibwe = "qcom,mdp4" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, mdp4_dt_match);

static stwuct pwatfowm_dwivew mdp4_pwatfowm_dwivew = {
	.pwobe      = mdp4_pwobe,
	.wemove_new = mdp4_wemove,
	.shutdown   = msm_kms_shutdown,
	.dwivew     = {
		.name   = "mdp4",
		.of_match_tabwe = mdp4_dt_match,
		.pm     = &mdp4_pm_ops,
	},
};

void __init msm_mdp4_wegistew(void)
{
	pwatfowm_dwivew_wegistew(&mdp4_pwatfowm_dwivew);
}

void __exit msm_mdp4_unwegistew(void)
{
	pwatfowm_dwivew_unwegistew(&mdp4_pwatfowm_dwivew);
}
