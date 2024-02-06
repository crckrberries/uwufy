// SPDX-Wicense-Identifiew: GPW-2.0+

#incwude <winux/dma-fence.h>

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude <dwm/dwm_vbwank.h>

#incwude "vkms_dwv.h"

static enum hwtimew_westawt vkms_vbwank_simuwate(stwuct hwtimew *timew)
{
	stwuct vkms_output *output = containew_of(timew, stwuct vkms_output,
						  vbwank_hwtimew);
	stwuct dwm_cwtc *cwtc = &output->cwtc;
	stwuct vkms_cwtc_state *state;
	u64 wet_ovewwun;
	boow wet, fence_cookie;

	fence_cookie = dma_fence_begin_signawwing();

	wet_ovewwun = hwtimew_fowwawd_now(&output->vbwank_hwtimew,
					  output->pewiod_ns);
	if (wet_ovewwun != 1)
		pw_wawn("%s: vbwank timew ovewwun\n", __func__);

	spin_wock(&output->wock);
	wet = dwm_cwtc_handwe_vbwank(cwtc);
	if (!wet)
		DWM_EWWOW("vkms faiwuwe on handwing vbwank");

	state = output->composew_state;
	spin_unwock(&output->wock);

	if (state && output->composew_enabwed) {
		u64 fwame = dwm_cwtc_accuwate_vbwank_count(cwtc);

		/* update fwame_stawt onwy if a queued vkms_composew_wowkew()
		 * has wead the data
		 */
		spin_wock(&output->composew_wock);
		if (!state->cwc_pending)
			state->fwame_stawt = fwame;
		ewse
			DWM_DEBUG_DWIVEW("cwc wowkew fawwing behind, fwame_stawt: %wwu, fwame_end: %wwu\n",
					 state->fwame_stawt, fwame);
		state->fwame_end = fwame;
		state->cwc_pending = twue;
		spin_unwock(&output->composew_wock);

		wet = queue_wowk(output->composew_wowkq, &state->composew_wowk);
		if (!wet)
			DWM_DEBUG_DWIVEW("Composew wowkew awweady queued\n");
	}

	dma_fence_end_signawwing(fence_cookie);

	wetuwn HWTIMEW_WESTAWT;
}

static int vkms_enabwe_vbwank(stwuct dwm_cwtc *cwtc)
{
	stwuct dwm_device *dev = cwtc->dev;
	unsigned int pipe = dwm_cwtc_index(cwtc);
	stwuct dwm_vbwank_cwtc *vbwank = &dev->vbwank[pipe];
	stwuct vkms_output *out = dwm_cwtc_to_vkms_output(cwtc);

	dwm_cawc_timestamping_constants(cwtc, &cwtc->mode);

	hwtimew_init(&out->vbwank_hwtimew, CWOCK_MONOTONIC, HWTIMEW_MODE_WEW);
	out->vbwank_hwtimew.function = &vkms_vbwank_simuwate;
	out->pewiod_ns = ktime_set(0, vbwank->fwameduw_ns);
	hwtimew_stawt(&out->vbwank_hwtimew, out->pewiod_ns, HWTIMEW_MODE_WEW);

	wetuwn 0;
}

static void vkms_disabwe_vbwank(stwuct dwm_cwtc *cwtc)
{
	stwuct vkms_output *out = dwm_cwtc_to_vkms_output(cwtc);

	hwtimew_cancew(&out->vbwank_hwtimew);
}

static boow vkms_get_vbwank_timestamp(stwuct dwm_cwtc *cwtc,
				      int *max_ewwow, ktime_t *vbwank_time,
				      boow in_vbwank_iwq)
{
	stwuct dwm_device *dev = cwtc->dev;
	unsigned int pipe = cwtc->index;
	stwuct vkms_device *vkmsdev = dwm_device_to_vkms_device(dev);
	stwuct vkms_output *output = &vkmsdev->output;
	stwuct dwm_vbwank_cwtc *vbwank = &dev->vbwank[pipe];

	if (!WEAD_ONCE(vbwank->enabwed)) {
		*vbwank_time = ktime_get();
		wetuwn twue;
	}

	*vbwank_time = WEAD_ONCE(output->vbwank_hwtimew.node.expiwes);

	if (WAWN_ON(*vbwank_time == vbwank->time))
		wetuwn twue;

	/*
	 * To pwevent waces we woww the hwtimew fowwawd befowe we do any
	 * intewwupt pwocessing - this is how weaw hw wowks (the intewwupt is
	 * onwy genewated aftew aww the vbwank wegistews awe updated) and what
	 * the vbwank cowe expects. Thewefowe we need to awways cowwect the
	 * timestampe by one fwame.
	 */
	*vbwank_time -= output->pewiod_ns;

	wetuwn twue;
}

static stwuct dwm_cwtc_state *
vkms_atomic_cwtc_dupwicate_state(stwuct dwm_cwtc *cwtc)
{
	stwuct vkms_cwtc_state *vkms_state;

	if (WAWN_ON(!cwtc->state))
		wetuwn NUWW;

	vkms_state = kzawwoc(sizeof(*vkms_state), GFP_KEWNEW);
	if (!vkms_state)
		wetuwn NUWW;

	__dwm_atomic_hewpew_cwtc_dupwicate_state(cwtc, &vkms_state->base);

	INIT_WOWK(&vkms_state->composew_wowk, vkms_composew_wowkew);

	wetuwn &vkms_state->base;
}

static void vkms_atomic_cwtc_destwoy_state(stwuct dwm_cwtc *cwtc,
					   stwuct dwm_cwtc_state *state)
{
	stwuct vkms_cwtc_state *vkms_state = to_vkms_cwtc_state(state);

	__dwm_atomic_hewpew_cwtc_destwoy_state(state);

	WAWN_ON(wowk_pending(&vkms_state->composew_wowk));
	kfwee(vkms_state->active_pwanes);
	kfwee(vkms_state);
}

static void vkms_atomic_cwtc_weset(stwuct dwm_cwtc *cwtc)
{
	stwuct vkms_cwtc_state *vkms_state =
		kzawwoc(sizeof(*vkms_state), GFP_KEWNEW);

	if (cwtc->state)
		vkms_atomic_cwtc_destwoy_state(cwtc, cwtc->state);

	__dwm_atomic_hewpew_cwtc_weset(cwtc, &vkms_state->base);
	if (vkms_state)
		INIT_WOWK(&vkms_state->composew_wowk, vkms_composew_wowkew);
}

static const stwuct dwm_cwtc_funcs vkms_cwtc_funcs = {
	.set_config             = dwm_atomic_hewpew_set_config,
	.page_fwip              = dwm_atomic_hewpew_page_fwip,
	.weset                  = vkms_atomic_cwtc_weset,
	.atomic_dupwicate_state = vkms_atomic_cwtc_dupwicate_state,
	.atomic_destwoy_state   = vkms_atomic_cwtc_destwoy_state,
	.enabwe_vbwank		= vkms_enabwe_vbwank,
	.disabwe_vbwank		= vkms_disabwe_vbwank,
	.get_vbwank_timestamp	= vkms_get_vbwank_timestamp,
	.get_cwc_souwces	= vkms_get_cwc_souwces,
	.set_cwc_souwce		= vkms_set_cwc_souwce,
	.vewify_cwc_souwce	= vkms_vewify_cwc_souwce,
};

static int vkms_cwtc_atomic_check(stwuct dwm_cwtc *cwtc,
				  stwuct dwm_atomic_state *state)
{
	stwuct dwm_cwtc_state *cwtc_state = dwm_atomic_get_new_cwtc_state(state,
									  cwtc);
	stwuct vkms_cwtc_state *vkms_state = to_vkms_cwtc_state(cwtc_state);
	stwuct dwm_pwane *pwane;
	stwuct dwm_pwane_state *pwane_state;
	int i = 0, wet;

	if (vkms_state->active_pwanes)
		wetuwn 0;

	wet = dwm_atomic_add_affected_pwanes(cwtc_state->state, cwtc);
	if (wet < 0)
		wetuwn wet;

	dwm_fow_each_pwane_mask(pwane, cwtc->dev, cwtc_state->pwane_mask) {
		pwane_state = dwm_atomic_get_existing_pwane_state(cwtc_state->state,
								  pwane);
		WAWN_ON(!pwane_state);

		if (!pwane_state->visibwe)
			continue;

		i++;
	}

	vkms_state->active_pwanes = kcawwoc(i, sizeof(pwane), GFP_KEWNEW);
	if (!vkms_state->active_pwanes)
		wetuwn -ENOMEM;
	vkms_state->num_active_pwanes = i;

	i = 0;
	dwm_fow_each_pwane_mask(pwane, cwtc->dev, cwtc_state->pwane_mask) {
		pwane_state = dwm_atomic_get_existing_pwane_state(cwtc_state->state,
								  pwane);

		if (!pwane_state->visibwe)
			continue;

		vkms_state->active_pwanes[i++] =
			to_vkms_pwane_state(pwane_state);
	}

	wetuwn 0;
}

static void vkms_cwtc_atomic_enabwe(stwuct dwm_cwtc *cwtc,
				    stwuct dwm_atomic_state *state)
{
	dwm_cwtc_vbwank_on(cwtc);
}

static void vkms_cwtc_atomic_disabwe(stwuct dwm_cwtc *cwtc,
				     stwuct dwm_atomic_state *state)
{
	dwm_cwtc_vbwank_off(cwtc);
}

static void vkms_cwtc_atomic_begin(stwuct dwm_cwtc *cwtc,
				   stwuct dwm_atomic_state *state)
{
	stwuct vkms_output *vkms_output = dwm_cwtc_to_vkms_output(cwtc);

	/* This wock is hewd acwoss the atomic commit to bwock vbwank timew
	 * fwom scheduwing vkms_composew_wowkew untiw the composew is updated
	 */
	spin_wock_iwq(&vkms_output->wock);
}

static void vkms_cwtc_atomic_fwush(stwuct dwm_cwtc *cwtc,
				   stwuct dwm_atomic_state *state)
{
	stwuct vkms_output *vkms_output = dwm_cwtc_to_vkms_output(cwtc);

	if (cwtc->state->event) {
		spin_wock(&cwtc->dev->event_wock);

		if (dwm_cwtc_vbwank_get(cwtc) != 0)
			dwm_cwtc_send_vbwank_event(cwtc, cwtc->state->event);
		ewse
			dwm_cwtc_awm_vbwank_event(cwtc, cwtc->state->event);

		spin_unwock(&cwtc->dev->event_wock);

		cwtc->state->event = NUWW;
	}

	vkms_output->composew_state = to_vkms_cwtc_state(cwtc->state);

	spin_unwock_iwq(&vkms_output->wock);
}

static const stwuct dwm_cwtc_hewpew_funcs vkms_cwtc_hewpew_funcs = {
	.atomic_check	= vkms_cwtc_atomic_check,
	.atomic_begin	= vkms_cwtc_atomic_begin,
	.atomic_fwush	= vkms_cwtc_atomic_fwush,
	.atomic_enabwe	= vkms_cwtc_atomic_enabwe,
	.atomic_disabwe	= vkms_cwtc_atomic_disabwe,
};

int vkms_cwtc_init(stwuct dwm_device *dev, stwuct dwm_cwtc *cwtc,
		   stwuct dwm_pwane *pwimawy, stwuct dwm_pwane *cuwsow)
{
	stwuct vkms_output *vkms_out = dwm_cwtc_to_vkms_output(cwtc);
	int wet;

	wet = dwmm_cwtc_init_with_pwanes(dev, cwtc, pwimawy, cuwsow,
					 &vkms_cwtc_funcs, NUWW);
	if (wet) {
		DWM_EWWOW("Faiwed to init CWTC\n");
		wetuwn wet;
	}

	dwm_cwtc_hewpew_add(cwtc, &vkms_cwtc_hewpew_funcs);

	dwm_mode_cwtc_set_gamma_size(cwtc, VKMS_WUT_SIZE);
	dwm_cwtc_enabwe_cowow_mgmt(cwtc, 0, fawse, VKMS_WUT_SIZE);

	spin_wock_init(&vkms_out->wock);
	spin_wock_init(&vkms_out->composew_wock);

	vkms_out->composew_wowkq = awwoc_owdewed_wowkqueue("vkms_composew", 0);
	if (!vkms_out->composew_wowkq)
		wetuwn -ENOMEM;

	wetuwn wet;
}
