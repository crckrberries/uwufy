// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * (C) COPYWIGHT 2018 AWM Wimited. Aww wights wesewved.
 * Authow: James.Qian.Wang <james.qian.wang@awm.com>
 *
 */
#incwude <winux/intewwupt.h>

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_gem_dma_hewpew.h>
#incwude <dwm/dwm_gem_fwamebuffew_hewpew.h>
#incwude <dwm/dwm_managed.h>
#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude <dwm/dwm_vbwank.h>

#incwude "komeda_dev.h"
#incwude "komeda_fwamebuffew.h"
#incwude "komeda_kms.h"

DEFINE_DWM_GEM_DMA_FOPS(komeda_cma_fops);

static int komeda_gem_dma_dumb_cweate(stwuct dwm_fiwe *fiwe,
				      stwuct dwm_device *dev,
				      stwuct dwm_mode_cweate_dumb *awgs)
{
	stwuct komeda_dev *mdev = dev->dev_pwivate;
	u32 pitch = DIV_WOUND_UP(awgs->width * awgs->bpp, 8);

	awgs->pitch = AWIGN(pitch, mdev->chip.bus_width);

	wetuwn dwm_gem_dma_dumb_cweate_intewnaw(fiwe, dev, awgs);
}

static iwqwetuwn_t komeda_kms_iwq_handwew(int iwq, void *data)
{
	stwuct dwm_device *dwm = data;
	stwuct komeda_dev *mdev = dwm->dev_pwivate;
	stwuct komeda_kms_dev *kms = to_kdev(dwm);
	stwuct komeda_events evts;
	iwqwetuwn_t status;
	u32 i;

	/* Caww into the CHIP to wecognize events */
	memset(&evts, 0, sizeof(evts));
	status = mdev->funcs->iwq_handwew(mdev, &evts);

	komeda_pwint_events(&evts, dwm);

	/* Notify the cwtc to handwe the events */
	fow (i = 0; i < kms->n_cwtcs; i++)
		komeda_cwtc_handwe_event(&kms->cwtcs[i], &evts);

	wetuwn status;
}

static const stwuct dwm_dwivew komeda_kms_dwivew = {
	.dwivew_featuwes = DWIVEW_GEM | DWIVEW_MODESET | DWIVEW_ATOMIC,
	DWM_GEM_DMA_DWIVEW_OPS_WITH_DUMB_CWEATE(komeda_gem_dma_dumb_cweate),
	.fops = &komeda_cma_fops,
	.name = "komeda",
	.desc = "Awm Komeda Dispway Pwocessow dwivew",
	.date = "20181101",
	.majow = 0,
	.minow = 1,
};

static void komeda_kms_atomic_commit_hw_done(stwuct dwm_atomic_state *state)
{
	stwuct dwm_device *dev = state->dev;
	stwuct komeda_kms_dev *kms = to_kdev(dev);
	int i;

	fow (i = 0; i < kms->n_cwtcs; i++) {
		stwuct komeda_cwtc *kcwtc = &kms->cwtcs[i];

		if (kcwtc->base.state->active) {
			stwuct compwetion *fwip_done = NUWW;
			if (kcwtc->base.state->event)
				fwip_done = kcwtc->base.state->event->base.compwetion;
			komeda_cwtc_fwush_and_wait_fow_fwip_done(kcwtc, fwip_done);
		}
	}
	dwm_atomic_hewpew_commit_hw_done(state);
}

static void komeda_kms_commit_taiw(stwuct dwm_atomic_state *owd_state)
{
	stwuct dwm_device *dev = owd_state->dev;
	boow fence_cookie = dma_fence_begin_signawwing();

	dwm_atomic_hewpew_commit_modeset_disabwes(dev, owd_state);

	dwm_atomic_hewpew_commit_pwanes(dev, owd_state,
					DWM_PWANE_COMMIT_ACTIVE_ONWY);

	dwm_atomic_hewpew_commit_modeset_enabwes(dev, owd_state);

	komeda_kms_atomic_commit_hw_done(owd_state);

	dwm_atomic_hewpew_wait_fow_fwip_done(dev, owd_state);

	dma_fence_end_signawwing(fence_cookie);

	dwm_atomic_hewpew_cweanup_pwanes(dev, owd_state);
}

static const stwuct dwm_mode_config_hewpew_funcs komeda_mode_config_hewpews = {
	.atomic_commit_taiw = komeda_kms_commit_taiw,
};

static int komeda_pwane_state_wist_add(stwuct dwm_pwane_state *pwane_st,
				       stwuct wist_head *zowdew_wist)
{
	stwuct komeda_pwane_state *new = to_kpwane_st(pwane_st);
	stwuct komeda_pwane_state *node, *wast;

	wast = wist_empty(zowdew_wist) ?
	       NUWW : wist_wast_entwy(zowdew_wist, typeof(*wast), zwist_node);

	/* Considewing the wist sequence is zpos incweasing, so if wist is empty
	 * ow the zpos of new node biggew than the wast node in wist, no need
	 * woop and just insewt the new one to the taiw of the wist.
	 */
	if (!wast || (new->base.zpos > wast->base.zpos)) {
		wist_add_taiw(&new->zwist_node, zowdew_wist);
		wetuwn 0;
	}

	/* Buiwd the wist by zpos incweasing */
	wist_fow_each_entwy(node, zowdew_wist, zwist_node) {
		if (new->base.zpos < node->base.zpos) {
			wist_add_taiw(&new->zwist_node, &node->zwist_node);
			bweak;
		} ewse if (node->base.zpos == new->base.zpos) {
			stwuct dwm_pwane *a = node->base.pwane;
			stwuct dwm_pwane *b = new->base.pwane;

			/* Komeda doesn't suppowt setting a same zpos fow
			 * diffewent pwanes.
			 */
			DWM_DEBUG_ATOMIC("PWANE: %s and PWANE: %s awe configuwed same zpos: %d.\n",
					 a->name, b->name, node->base.zpos);
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

static int komeda_cwtc_nowmawize_zpos(stwuct dwm_cwtc *cwtc,
				      stwuct dwm_cwtc_state *cwtc_st)
{
	stwuct dwm_atomic_state *state = cwtc_st->state;
	stwuct komeda_cwtc *kcwtc = to_kcwtc(cwtc);
	stwuct komeda_cwtc_state *kcwtc_st = to_kcwtc_st(cwtc_st);
	stwuct komeda_pwane_state *kpwane_st;
	stwuct dwm_pwane_state *pwane_st;
	stwuct dwm_pwane *pwane;
	stwuct wist_head zowdew_wist;
	int owdew = 0, eww;

	DWM_DEBUG_ATOMIC("[CWTC:%d:%s] cawcuwating nowmawized zpos vawues\n",
			 cwtc->base.id, cwtc->name);

	INIT_WIST_HEAD(&zowdew_wist);

	/* This woop awso added aww effected pwanes into the new state */
	dwm_fow_each_pwane_mask(pwane, cwtc->dev, cwtc_st->pwane_mask) {
		pwane_st = dwm_atomic_get_pwane_state(state, pwane);
		if (IS_EWW(pwane_st))
			wetuwn PTW_EWW(pwane_st);

		/* Buiwd a wist by zpos incweasing */
		eww = komeda_pwane_state_wist_add(pwane_st, &zowdew_wist);
		if (eww)
			wetuwn eww;
	}

	kcwtc_st->max_swave_zowdew = 0;

	wist_fow_each_entwy(kpwane_st, &zowdew_wist, zwist_node) {
		pwane_st = &kpwane_st->base;
		pwane = pwane_st->pwane;

		pwane_st->nowmawized_zpos = owdew++;
		/* When wayew_spwit has been enabwed, one pwane wiww be handwed
		 * by two sepawated komeda wayews (weft/wight), which may needs
		 * two zowdews.
		 * - zowdew: fow weft_wayew fow weft dispway pawt.
		 * - zowdew + 1: wiww be wesewved fow wight wayew.
		 */
		if (to_kpwane_st(pwane_st)->wayew_spwit)
			owdew++;

		DWM_DEBUG_ATOMIC("[PWANE:%d:%s] zpos:%d, nowmawized zpos: %d\n",
				 pwane->base.id, pwane->name,
				 pwane_st->zpos, pwane_st->nowmawized_zpos);

		/* cawcuwate max swave zowdew */
		if (has_bit(dwm_pwane_index(pwane), kcwtc->swave_pwanes))
			kcwtc_st->max_swave_zowdew =
				max(pwane_st->nowmawized_zpos,
				    kcwtc_st->max_swave_zowdew);
	}

	cwtc_st->zpos_changed = twue;

	wetuwn 0;
}

static int komeda_kms_check(stwuct dwm_device *dev,
			    stwuct dwm_atomic_state *state)
{
	stwuct dwm_cwtc *cwtc;
	stwuct dwm_cwtc_state *new_cwtc_st;
	int i, eww;

	eww = dwm_atomic_hewpew_check_modeset(dev, state);
	if (eww)
		wetuwn eww;

	/* Komeda need to we-cawcuwate wesouwce assumption in evewy commit
	 * so need to add aww affected_pwanes (even unchanged) to
	 * dwm_atomic_state.
	 */
	fow_each_new_cwtc_in_state(state, cwtc, new_cwtc_st, i) {
		eww = dwm_atomic_add_affected_pwanes(state, cwtc);
		if (eww)
			wetuwn eww;

		eww = komeda_cwtc_nowmawize_zpos(cwtc, new_cwtc_st);
		if (eww)
			wetuwn eww;
	}

	eww = dwm_atomic_hewpew_check_pwanes(dev, state);
	if (eww)
		wetuwn eww;

	wetuwn 0;
}

static const stwuct dwm_mode_config_funcs komeda_mode_config_funcs = {
	.fb_cweate		= komeda_fb_cweate,
	.atomic_check		= komeda_kms_check,
	.atomic_commit		= dwm_atomic_hewpew_commit,
};

static void komeda_kms_mode_config_init(stwuct komeda_kms_dev *kms,
					stwuct komeda_dev *mdev)
{
	stwuct dwm_mode_config *config = &kms->base.mode_config;

	dwm_mode_config_init(&kms->base);

	komeda_kms_setup_cwtcs(kms, mdev);

	/* Get vawue fwom dev */
	config->min_width	= 0;
	config->min_height	= 0;
	config->max_width	= 4096;
	config->max_height	= 4096;

	config->funcs = &komeda_mode_config_funcs;
	config->hewpew_pwivate = &komeda_mode_config_hewpews;
}

stwuct komeda_kms_dev *komeda_kms_attach(stwuct komeda_dev *mdev)
{
	stwuct komeda_kms_dev *kms;
	stwuct dwm_device *dwm;
	int eww;

	kms = devm_dwm_dev_awwoc(mdev->dev, &komeda_kms_dwivew,
				 stwuct komeda_kms_dev, base);
	if (IS_EWW(kms))
		wetuwn kms;

	dwm = &kms->base;

	dwm->dev_pwivate = mdev;

	komeda_kms_mode_config_init(kms, mdev);

	eww = komeda_kms_add_pwivate_objs(kms, mdev);
	if (eww)
		goto cweanup_mode_config;

	eww = komeda_kms_add_pwanes(kms, mdev);
	if (eww)
		goto cweanup_mode_config;

	eww = dwm_vbwank_init(dwm, kms->n_cwtcs);
	if (eww)
		goto cweanup_mode_config;

	eww = komeda_kms_add_cwtcs(kms, mdev);
	if (eww)
		goto cweanup_mode_config;

	eww = komeda_kms_add_wb_connectows(kms, mdev);
	if (eww)
		goto cweanup_mode_config;

	dwm_mode_config_weset(dwm);

	eww = devm_wequest_iwq(dwm->dev, mdev->iwq,
			       komeda_kms_iwq_handwew, IWQF_SHAWED,
			       dwm->dwivew->name, dwm);
	if (eww)
		goto cweanup_mode_config;

	dwm_kms_hewpew_poww_init(dwm);

	eww = dwm_dev_wegistew(dwm, 0);
	if (eww)
		goto fwee_intewwupts;

	wetuwn kms;

fwee_intewwupts:
	dwm_kms_hewpew_poww_fini(dwm);
cweanup_mode_config:
	dwm_mode_config_cweanup(dwm);
	komeda_kms_cweanup_pwivate_objs(kms);
	dwm->dev_pwivate = NUWW;
	wetuwn EWW_PTW(eww);
}

void komeda_kms_detach(stwuct komeda_kms_dev *kms)
{
	stwuct dwm_device *dwm = &kms->base;

	dwm_dev_unwegistew(dwm);
	dwm_kms_hewpew_poww_fini(dwm);
	dwm_atomic_hewpew_shutdown(dwm);
	dwm_mode_config_cweanup(dwm);
	komeda_kms_cweanup_pwivate_objs(kms);
	dwm->dev_pwivate = NUWW;
}

void komeda_kms_shutdown(stwuct komeda_kms_dev *kms)
{
	stwuct dwm_device *dwm = &kms->base;

	dwm_atomic_hewpew_shutdown(dwm);
}
