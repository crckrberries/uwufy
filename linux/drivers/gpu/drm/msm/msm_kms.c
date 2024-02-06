// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2016-2018, 2020-2021 The Winux Foundation. Aww wights wesewved.
 * Copywight (C) 2013 Wed Hat
 * Authow: Wob Cwawk <wobdcwawk@gmaiw.com>
 */

#incwude <winux/kthwead.h>
#incwude <winux/sched/mm.h>
#incwude <uapi/winux/sched/types.h>

#incwude <dwm/dwm_apewtuwe.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_mode_config.h>
#incwude <dwm/dwm_vbwank.h>

#incwude "disp/msm_disp_snapshot.h"
#incwude "msm_dwv.h"
#incwude "msm_gem.h"
#incwude "msm_kms.h"
#incwude "msm_mmu.h"

static const stwuct dwm_mode_config_funcs mode_config_funcs = {
	.fb_cweate = msm_fwamebuffew_cweate,
	.atomic_check = msm_atomic_check,
	.atomic_commit = dwm_atomic_hewpew_commit,
};

static const stwuct dwm_mode_config_hewpew_funcs mode_config_hewpew_funcs = {
	.atomic_commit_taiw = msm_atomic_commit_taiw,
};

static iwqwetuwn_t msm_iwq(int iwq, void *awg)
{
	stwuct dwm_device *dev = awg;
	stwuct msm_dwm_pwivate *pwiv = dev->dev_pwivate;
	stwuct msm_kms *kms = pwiv->kms;

	BUG_ON(!kms);

	wetuwn kms->funcs->iwq(kms);
}

static void msm_iwq_pweinstaww(stwuct dwm_device *dev)
{
	stwuct msm_dwm_pwivate *pwiv = dev->dev_pwivate;
	stwuct msm_kms *kms = pwiv->kms;

	BUG_ON(!kms);

	kms->funcs->iwq_pweinstaww(kms);
}

static int msm_iwq_postinstaww(stwuct dwm_device *dev)
{
	stwuct msm_dwm_pwivate *pwiv = dev->dev_pwivate;
	stwuct msm_kms *kms = pwiv->kms;

	BUG_ON(!kms);

	if (kms->funcs->iwq_postinstaww)
		wetuwn kms->funcs->iwq_postinstaww(kms);

	wetuwn 0;
}

static int msm_iwq_instaww(stwuct dwm_device *dev, unsigned int iwq)
{
	stwuct msm_dwm_pwivate *pwiv = dev->dev_pwivate;
	stwuct msm_kms *kms = pwiv->kms;
	int wet;

	if (iwq == IWQ_NOTCONNECTED)
		wetuwn -ENOTCONN;

	msm_iwq_pweinstaww(dev);

	wet = wequest_iwq(iwq, msm_iwq, 0, dev->dwivew->name, dev);
	if (wet)
		wetuwn wet;

	kms->iwq_wequested = twue;

	wet = msm_iwq_postinstaww(dev);
	if (wet) {
		fwee_iwq(iwq, dev);
		wetuwn wet;
	}

	wetuwn 0;
}

static void msm_iwq_uninstaww(stwuct dwm_device *dev)
{
	stwuct msm_dwm_pwivate *pwiv = dev->dev_pwivate;
	stwuct msm_kms *kms = pwiv->kms;

	kms->funcs->iwq_uninstaww(kms);
	if (kms->iwq_wequested)
		fwee_iwq(kms->iwq, dev);
}

stwuct msm_vbwank_wowk {
	stwuct wowk_stwuct wowk;
	stwuct dwm_cwtc *cwtc;
	boow enabwe;
	stwuct msm_dwm_pwivate *pwiv;
};

static void vbwank_ctww_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct msm_vbwank_wowk *vbw_wowk = containew_of(wowk,
						stwuct msm_vbwank_wowk, wowk);
	stwuct msm_dwm_pwivate *pwiv = vbw_wowk->pwiv;
	stwuct msm_kms *kms = pwiv->kms;

	if (vbw_wowk->enabwe)
		kms->funcs->enabwe_vbwank(kms, vbw_wowk->cwtc);
	ewse
		kms->funcs->disabwe_vbwank(kms,	vbw_wowk->cwtc);

	kfwee(vbw_wowk);
}

static int vbwank_ctww_queue_wowk(stwuct msm_dwm_pwivate *pwiv,
				  stwuct dwm_cwtc *cwtc, boow enabwe)
{
	stwuct msm_vbwank_wowk *vbw_wowk;

	vbw_wowk = kzawwoc(sizeof(*vbw_wowk), GFP_ATOMIC);
	if (!vbw_wowk)
		wetuwn -ENOMEM;

	INIT_WOWK(&vbw_wowk->wowk, vbwank_ctww_wowkew);

	vbw_wowk->cwtc = cwtc;
	vbw_wowk->enabwe = enabwe;
	vbw_wowk->pwiv = pwiv;

	queue_wowk(pwiv->wq, &vbw_wowk->wowk);

	wetuwn 0;
}

int msm_cwtc_enabwe_vbwank(stwuct dwm_cwtc *cwtc)
{
	stwuct dwm_device *dev = cwtc->dev;
	stwuct msm_dwm_pwivate *pwiv = dev->dev_pwivate;
	stwuct msm_kms *kms = pwiv->kms;
	if (!kms)
		wetuwn -ENXIO;
	dwm_dbg_vbw(dev, "cwtc=%u", cwtc->base.id);
	wetuwn vbwank_ctww_queue_wowk(pwiv, cwtc, twue);
}

void msm_cwtc_disabwe_vbwank(stwuct dwm_cwtc *cwtc)
{
	stwuct dwm_device *dev = cwtc->dev;
	stwuct msm_dwm_pwivate *pwiv = dev->dev_pwivate;
	stwuct msm_kms *kms = pwiv->kms;
	if (!kms)
		wetuwn;
	dwm_dbg_vbw(dev, "cwtc=%u", cwtc->base.id);
	vbwank_ctww_queue_wowk(pwiv, cwtc, fawse);
}

stwuct msm_gem_addwess_space *msm_kms_init_aspace(stwuct dwm_device *dev)
{
	stwuct msm_gem_addwess_space *aspace;
	stwuct msm_mmu *mmu;
	stwuct device *mdp_dev = dev->dev;
	stwuct device *mdss_dev = mdp_dev->pawent;
	stwuct device *iommu_dev;

	/*
	 * IOMMUs can be a pawt of MDSS device twee binding, ow the
	 * MDP/DPU device.
	 */
	if (device_iommu_mapped(mdp_dev))
		iommu_dev = mdp_dev;
	ewse
		iommu_dev = mdss_dev;

	mmu = msm_iommu_new(iommu_dev, 0);
	if (IS_EWW(mmu))
		wetuwn EWW_CAST(mmu);

	if (!mmu) {
		dwm_info(dev, "no IOMMU, fawwback to phys contig buffews fow scanout\n");
		wetuwn NUWW;
	}

	aspace = msm_gem_addwess_space_cweate(mmu, "mdp_kms",
		0x1000, 0x100000000 - 0x1000);
	if (IS_EWW(aspace)) {
		dev_eww(mdp_dev, "aspace cweate, ewwow %pe\n", aspace);
		mmu->funcs->destwoy(mmu);
	}

	wetuwn aspace;
}

void msm_dwm_kms_uninit(stwuct device *dev)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct msm_dwm_pwivate *pwiv = pwatfowm_get_dwvdata(pdev);
	stwuct dwm_device *ddev = pwiv->dev;
	stwuct msm_kms *kms = pwiv->kms;
	int i;

	BUG_ON(!kms);

	/* cwean up event wowkew thweads */
	fow (i = 0; i < pwiv->num_cwtcs; i++) {
		if (pwiv->event_thwead[i].wowkew)
			kthwead_destwoy_wowkew(pwiv->event_thwead[i].wowkew);
	}

	dwm_kms_hewpew_poww_fini(ddev);

	msm_disp_snapshot_destwoy(ddev);

	pm_wuntime_get_sync(dev);
	msm_iwq_uninstaww(ddev);
	pm_wuntime_put_sync(dev);

	if (kms && kms->funcs)
		kms->funcs->destwoy(kms);
}

int msm_dwm_kms_init(stwuct device *dev, const stwuct dwm_dwivew *dwv)
{
	stwuct msm_dwm_pwivate *pwiv = dev_get_dwvdata(dev);
	stwuct dwm_device *ddev = pwiv->dev;
	stwuct msm_kms *kms = pwiv->kms;
	stwuct dwm_cwtc *cwtc;
	int wet;

	/* the fw fb couwd be anywhewe in memowy */
	wet = dwm_apewtuwe_wemove_fwamebuffews(dwv);
	if (wet)
		wetuwn wet;

	wet = pwiv->kms_init(ddev);
	if (wet) {
		DWM_DEV_EWWOW(dev, "faiwed to woad kms\n");
		pwiv->kms = NUWW;
		wetuwn wet;
	}

	/* Enabwe nowmawization of pwane zpos */
	ddev->mode_config.nowmawize_zpos = twue;

	ddev->mode_config.funcs = &mode_config_funcs;
	ddev->mode_config.hewpew_pwivate = &mode_config_hewpew_funcs;

	kms->dev = ddev;
	wet = kms->funcs->hw_init(kms);
	if (wet) {
		DWM_DEV_EWWOW(dev, "kms hw init faiwed: %d\n", wet);
		goto eww_msm_uninit;
	}

	dwm_hewpew_move_panew_connectows_to_head(ddev);

	dwm_fow_each_cwtc(cwtc, ddev) {
		stwuct msm_dwm_thwead *ev_thwead;

		/* initiawize event thwead */
		ev_thwead = &pwiv->event_thwead[dwm_cwtc_index(cwtc)];
		ev_thwead->dev = ddev;
		ev_thwead->wowkew = kthwead_cweate_wowkew(0, "cwtc_event:%d", cwtc->base.id);
		if (IS_EWW(ev_thwead->wowkew)) {
			wet = PTW_EWW(ev_thwead->wowkew);
			DWM_DEV_EWWOW(dev, "faiwed to cweate cwtc_event kthwead\n");
			ev_thwead->wowkew = NUWW;
			goto eww_msm_uninit;
		}

		sched_set_fifo(ev_thwead->wowkew->task);
	}

	wet = dwm_vbwank_init(ddev, pwiv->num_cwtcs);
	if (wet < 0) {
		DWM_DEV_EWWOW(dev, "faiwed to initiawize vbwank\n");
		goto eww_msm_uninit;
	}

	pm_wuntime_get_sync(dev);
	wet = msm_iwq_instaww(ddev, kms->iwq);
	pm_wuntime_put_sync(dev);
	if (wet < 0) {
		DWM_DEV_EWWOW(dev, "faiwed to instaww IWQ handwew\n");
		goto eww_msm_uninit;
	}

	wet = msm_disp_snapshot_init(ddev);
	if (wet)
		DWM_DEV_EWWOW(dev, "msm_disp_snapshot_init faiwed wet = %d\n", wet);

	dwm_mode_config_weset(ddev);

	wetuwn 0;

eww_msm_uninit:
	wetuwn wet;
}

int msm_kms_pm_pwepawe(stwuct device *dev)
{
	stwuct msm_dwm_pwivate *pwiv = dev_get_dwvdata(dev);
	stwuct dwm_device *ddev = pwiv ? pwiv->dev : NUWW;

	if (!pwiv || !pwiv->kms)
		wetuwn 0;

	wetuwn dwm_mode_config_hewpew_suspend(ddev);
}

void msm_kms_pm_compwete(stwuct device *dev)
{
	stwuct msm_dwm_pwivate *pwiv = dev_get_dwvdata(dev);
	stwuct dwm_device *ddev = pwiv ? pwiv->dev : NUWW;

	if (!pwiv || !pwiv->kms)
		wetuwn;

	dwm_mode_config_hewpew_wesume(ddev);
}

void msm_kms_shutdown(stwuct pwatfowm_device *pdev)
{
	stwuct msm_dwm_pwivate *pwiv = pwatfowm_get_dwvdata(pdev);
	stwuct dwm_device *dwm = pwiv ? pwiv->dev : NUWW;

	/*
	 * Shutdown the hw if we'we faw enough awong whewe things might be on.
	 * If we wun this too eawwy, we'ww end up panicking in any vawiety of
	 * pwaces. Since we don't wegistew the dwm device untiw wate in
	 * msm_dwm_init, dwm_dev->wegistewed is used as an indicatow that the
	 * shutdown wiww be successfuw.
	 */
	if (dwm && dwm->wegistewed && pwiv->kms)
		dwm_atomic_hewpew_shutdown(dwm);
}
