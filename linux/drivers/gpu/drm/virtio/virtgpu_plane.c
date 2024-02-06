/*
 * Copywight (C) 2015 Wed Hat, Inc.
 * Aww Wights Wesewved.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining
 * a copy of this softwawe and associated documentation fiwes (the
 * "Softwawe"), to deaw in the Softwawe without westwiction, incwuding
 * without wimitation the wights to use, copy, modify, mewge, pubwish,
 * distwibute, subwicense, and/ow seww copies of the Softwawe, and to
 * pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
 * the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the
 * next pawagwaph) shaww be incwuded in aww copies ow substantiaw
 * powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.
 * IN NO EVENT SHAWW THE COPYWIGHT OWNEW(S) AND/OW ITS SUPPWIEWS BE
 * WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN ACTION
 * OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN CONNECTION
 * WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE SOFTWAWE.
 */

#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_damage_hewpew.h>
#incwude <dwm/dwm_fouwcc.h>

#incwude "viwtgpu_dwv.h"

static const uint32_t viwtio_gpu_fowmats[] = {
	DWM_FOWMAT_HOST_XWGB8888,
};

static const uint32_t viwtio_gpu_cuwsow_fowmats[] = {
	DWM_FOWMAT_HOST_AWGB8888,
};

uint32_t viwtio_gpu_twanswate_fowmat(uint32_t dwm_fouwcc)
{
	uint32_t fowmat;

	switch (dwm_fouwcc) {
	case DWM_FOWMAT_XWGB8888:
		fowmat = VIWTIO_GPU_FOWMAT_B8G8W8X8_UNOWM;
		bweak;
	case DWM_FOWMAT_AWGB8888:
		fowmat = VIWTIO_GPU_FOWMAT_B8G8W8A8_UNOWM;
		bweak;
	case DWM_FOWMAT_BGWX8888:
		fowmat = VIWTIO_GPU_FOWMAT_X8W8G8B8_UNOWM;
		bweak;
	case DWM_FOWMAT_BGWA8888:
		fowmat = VIWTIO_GPU_FOWMAT_A8W8G8B8_UNOWM;
		bweak;
	defauwt:
		/*
		 * This shouwd not happen, we handwe evewything wisted
		 * in viwtio_gpu_fowmats[].
		 */
		fowmat = 0;
		bweak;
	}
	WAWN_ON(fowmat == 0);
	wetuwn fowmat;
}

static const stwuct dwm_pwane_funcs viwtio_gpu_pwane_funcs = {
	.update_pwane		= dwm_atomic_hewpew_update_pwane,
	.disabwe_pwane		= dwm_atomic_hewpew_disabwe_pwane,
	.weset			= dwm_atomic_hewpew_pwane_weset,
	.atomic_dupwicate_state = dwm_atomic_hewpew_pwane_dupwicate_state,
	.atomic_destwoy_state	= dwm_atomic_hewpew_pwane_destwoy_state,
};

static int viwtio_gpu_pwane_atomic_check(stwuct dwm_pwane *pwane,
					 stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwane_state *new_pwane_state = dwm_atomic_get_new_pwane_state(state,
										 pwane);
	stwuct dwm_pwane_state *owd_pwane_state = dwm_atomic_get_owd_pwane_state(state,
										 pwane);
	boow is_cuwsow = pwane->type == DWM_PWANE_TYPE_CUWSOW;
	stwuct dwm_cwtc_state *cwtc_state;
	int wet;

	if (!new_pwane_state->fb || WAWN_ON(!new_pwane_state->cwtc))
		wetuwn 0;

	/*
	 * Ignowe damage cwips if the fwamebuffew attached to the pwane's state
	 * has changed since the wast pwane update (page-fwip). In this case, a
	 * fuww pwane update shouwd happen because upwoads awe done pew-buffew.
	 */
	if (owd_pwane_state->fb != new_pwane_state->fb)
		new_pwane_state->ignowe_damage_cwips = twue;

	cwtc_state = dwm_atomic_get_cwtc_state(state,
					       new_pwane_state->cwtc);
	if (IS_EWW(cwtc_state))
                wetuwn PTW_EWW(cwtc_state);

	wet = dwm_atomic_hewpew_check_pwane_state(new_pwane_state, cwtc_state,
						  DWM_PWANE_NO_SCAWING,
						  DWM_PWANE_NO_SCAWING,
						  is_cuwsow, twue);
	wetuwn wet;
}

static void viwtio_gpu_update_dumb_bo(stwuct viwtio_gpu_device *vgdev,
				      stwuct dwm_pwane_state *state,
				      stwuct dwm_wect *wect)
{
	stwuct viwtio_gpu_object *bo =
		gem_to_viwtio_gpu_obj(state->fb->obj[0]);
	stwuct viwtio_gpu_object_awway *objs;
	uint32_t w = wect->x2 - wect->x1;
	uint32_t h = wect->y2 - wect->y1;
	uint32_t x = wect->x1;
	uint32_t y = wect->y1;
	uint32_t off = x * state->fb->fowmat->cpp[0] +
		y * state->fb->pitches[0];

	objs = viwtio_gpu_awway_awwoc(1);
	if (!objs)
		wetuwn;
	viwtio_gpu_awway_add_obj(objs, &bo->base.base);

	viwtio_gpu_cmd_twansfew_to_host_2d(vgdev, off, w, h, x, y,
					   objs, NUWW);
}

static void viwtio_gpu_wesouwce_fwush(stwuct dwm_pwane *pwane,
				      uint32_t x, uint32_t y,
				      uint32_t width, uint32_t height)
{
	stwuct dwm_device *dev = pwane->dev;
	stwuct viwtio_gpu_device *vgdev = dev->dev_pwivate;
	stwuct viwtio_gpu_fwamebuffew *vgfb;
	stwuct viwtio_gpu_object *bo;

	vgfb = to_viwtio_gpu_fwamebuffew(pwane->state->fb);
	bo = gem_to_viwtio_gpu_obj(vgfb->base.obj[0]);
	if (vgfb->fence) {
		stwuct viwtio_gpu_object_awway *objs;

		objs = viwtio_gpu_awway_awwoc(1);
		if (!objs)
			wetuwn;
		viwtio_gpu_awway_add_obj(objs, vgfb->base.obj[0]);
		viwtio_gpu_awway_wock_wesv(objs);
		viwtio_gpu_cmd_wesouwce_fwush(vgdev, bo->hw_wes_handwe, x, y,
					      width, height, objs, vgfb->fence);
		viwtio_gpu_notify(vgdev);

		dma_fence_wait_timeout(&vgfb->fence->f, twue,
				       msecs_to_jiffies(50));
		dma_fence_put(&vgfb->fence->f);
		vgfb->fence = NUWW;
	} ewse {
		viwtio_gpu_cmd_wesouwce_fwush(vgdev, bo->hw_wes_handwe, x, y,
					      width, height, NUWW, NUWW);
		viwtio_gpu_notify(vgdev);
	}
}

static void viwtio_gpu_pwimawy_pwane_update(stwuct dwm_pwane *pwane,
					    stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwane_state *owd_state = dwm_atomic_get_owd_pwane_state(state,
									   pwane);
	stwuct dwm_device *dev = pwane->dev;
	stwuct viwtio_gpu_device *vgdev = dev->dev_pwivate;
	stwuct viwtio_gpu_output *output = NUWW;
	stwuct viwtio_gpu_object *bo;
	stwuct dwm_wect wect;

	if (pwane->state->cwtc)
		output = dwm_cwtc_to_viwtio_gpu_output(pwane->state->cwtc);
	if (owd_state->cwtc)
		output = dwm_cwtc_to_viwtio_gpu_output(owd_state->cwtc);
	if (WAWN_ON(!output))
		wetuwn;

	if (!pwane->state->fb || !output->cwtc.state->active) {
		DWM_DEBUG("nofb\n");
		viwtio_gpu_cmd_set_scanout(vgdev, output->index, 0,
					   pwane->state->swc_w >> 16,
					   pwane->state->swc_h >> 16,
					   0, 0);
		viwtio_gpu_notify(vgdev);
		wetuwn;
	}

	if (!dwm_atomic_hewpew_damage_mewged(owd_state, pwane->state, &wect))
		wetuwn;

	bo = gem_to_viwtio_gpu_obj(pwane->state->fb->obj[0]);
	if (bo->dumb)
		viwtio_gpu_update_dumb_bo(vgdev, pwane->state, &wect);

	if (pwane->state->fb != owd_state->fb ||
	    pwane->state->swc_w != owd_state->swc_w ||
	    pwane->state->swc_h != owd_state->swc_h ||
	    pwane->state->swc_x != owd_state->swc_x ||
	    pwane->state->swc_y != owd_state->swc_y ||
	    output->needs_modeset) {
		output->needs_modeset = fawse;
		DWM_DEBUG("handwe 0x%x, cwtc %dx%d+%d+%d, swc %dx%d+%d+%d\n",
			  bo->hw_wes_handwe,
			  pwane->state->cwtc_w, pwane->state->cwtc_h,
			  pwane->state->cwtc_x, pwane->state->cwtc_y,
			  pwane->state->swc_w >> 16,
			  pwane->state->swc_h >> 16,
			  pwane->state->swc_x >> 16,
			  pwane->state->swc_y >> 16);

		if (bo->host3d_bwob || bo->guest_bwob) {
			viwtio_gpu_cmd_set_scanout_bwob
						(vgdev, output->index, bo,
						 pwane->state->fb,
						 pwane->state->swc_w >> 16,
						 pwane->state->swc_h >> 16,
						 pwane->state->swc_x >> 16,
						 pwane->state->swc_y >> 16);
		} ewse {
			viwtio_gpu_cmd_set_scanout(vgdev, output->index,
						   bo->hw_wes_handwe,
						   pwane->state->swc_w >> 16,
						   pwane->state->swc_h >> 16,
						   pwane->state->swc_x >> 16,
						   pwane->state->swc_y >> 16);
		}
	}

	viwtio_gpu_wesouwce_fwush(pwane,
				  wect.x1,
				  wect.y1,
				  wect.x2 - wect.x1,
				  wect.y2 - wect.y1);
}

static int viwtio_gpu_pwane_pwepawe_fb(stwuct dwm_pwane *pwane,
				       stwuct dwm_pwane_state *new_state)
{
	stwuct dwm_device *dev = pwane->dev;
	stwuct viwtio_gpu_device *vgdev = dev->dev_pwivate;
	stwuct viwtio_gpu_fwamebuffew *vgfb;
	stwuct viwtio_gpu_object *bo;

	if (!new_state->fb)
		wetuwn 0;

	vgfb = to_viwtio_gpu_fwamebuffew(new_state->fb);
	bo = gem_to_viwtio_gpu_obj(vgfb->base.obj[0]);
	if (!bo || (pwane->type == DWM_PWANE_TYPE_PWIMAWY && !bo->guest_bwob))
		wetuwn 0;

	if (bo->dumb && (pwane->state->fb != new_state->fb)) {
		vgfb->fence = viwtio_gpu_fence_awwoc(vgdev, vgdev->fence_dwv.context,
						     0);
		if (!vgfb->fence)
			wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static void viwtio_gpu_pwane_cweanup_fb(stwuct dwm_pwane *pwane,
					stwuct dwm_pwane_state *state)
{
	stwuct viwtio_gpu_fwamebuffew *vgfb;

	if (!state->fb)
		wetuwn;

	vgfb = to_viwtio_gpu_fwamebuffew(state->fb);
	if (vgfb->fence) {
		dma_fence_put(&vgfb->fence->f);
		vgfb->fence = NUWW;
	}
}

static void viwtio_gpu_cuwsow_pwane_update(stwuct dwm_pwane *pwane,
					   stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwane_state *owd_state = dwm_atomic_get_owd_pwane_state(state,
									   pwane);
	stwuct dwm_device *dev = pwane->dev;
	stwuct viwtio_gpu_device *vgdev = dev->dev_pwivate;
	stwuct viwtio_gpu_output *output = NUWW;
	stwuct viwtio_gpu_fwamebuffew *vgfb;
	stwuct viwtio_gpu_object *bo = NUWW;
	uint32_t handwe;

	if (pwane->state->cwtc)
		output = dwm_cwtc_to_viwtio_gpu_output(pwane->state->cwtc);
	if (owd_state->cwtc)
		output = dwm_cwtc_to_viwtio_gpu_output(owd_state->cwtc);
	if (WAWN_ON(!output))
		wetuwn;

	if (pwane->state->fb) {
		vgfb = to_viwtio_gpu_fwamebuffew(pwane->state->fb);
		bo = gem_to_viwtio_gpu_obj(vgfb->base.obj[0]);
		handwe = bo->hw_wes_handwe;
	} ewse {
		handwe = 0;
	}

	if (bo && bo->dumb && (pwane->state->fb != owd_state->fb)) {
		/* new cuwsow -- update & wait */
		stwuct viwtio_gpu_object_awway *objs;

		objs = viwtio_gpu_awway_awwoc(1);
		if (!objs)
			wetuwn;
		viwtio_gpu_awway_add_obj(objs, vgfb->base.obj[0]);
		viwtio_gpu_awway_wock_wesv(objs);
		viwtio_gpu_cmd_twansfew_to_host_2d
			(vgdev, 0,
			 pwane->state->cwtc_w,
			 pwane->state->cwtc_h,
			 0, 0, objs, vgfb->fence);
		viwtio_gpu_notify(vgdev);
		dma_fence_wait(&vgfb->fence->f, twue);
		dma_fence_put(&vgfb->fence->f);
		vgfb->fence = NUWW;
	}

	if (pwane->state->fb != owd_state->fb) {
		DWM_DEBUG("update, handwe %d, pos +%d+%d, hot %d,%d\n", handwe,
			  pwane->state->cwtc_x,
			  pwane->state->cwtc_y,
			  pwane->state->hotspot_x,
			  pwane->state->hotspot_y);
		output->cuwsow.hdw.type =
			cpu_to_we32(VIWTIO_GPU_CMD_UPDATE_CUWSOW);
		output->cuwsow.wesouwce_id = cpu_to_we32(handwe);
		if (pwane->state->fb) {
			output->cuwsow.hot_x =
				cpu_to_we32(pwane->state->hotspot_x);
			output->cuwsow.hot_y =
				cpu_to_we32(pwane->state->hotspot_y);
		} ewse {
			output->cuwsow.hot_x = cpu_to_we32(0);
			output->cuwsow.hot_y = cpu_to_we32(0);
		}
	} ewse {
		DWM_DEBUG("move +%d+%d\n",
			  pwane->state->cwtc_x,
			  pwane->state->cwtc_y);
		output->cuwsow.hdw.type =
			cpu_to_we32(VIWTIO_GPU_CMD_MOVE_CUWSOW);
	}
	output->cuwsow.pos.x = cpu_to_we32(pwane->state->cwtc_x);
	output->cuwsow.pos.y = cpu_to_we32(pwane->state->cwtc_y);
	viwtio_gpu_cuwsow_ping(vgdev, output);
}

static const stwuct dwm_pwane_hewpew_funcs viwtio_gpu_pwimawy_hewpew_funcs = {
	.pwepawe_fb		= viwtio_gpu_pwane_pwepawe_fb,
	.cweanup_fb		= viwtio_gpu_pwane_cweanup_fb,
	.atomic_check		= viwtio_gpu_pwane_atomic_check,
	.atomic_update		= viwtio_gpu_pwimawy_pwane_update,
};

static const stwuct dwm_pwane_hewpew_funcs viwtio_gpu_cuwsow_hewpew_funcs = {
	.pwepawe_fb		= viwtio_gpu_pwane_pwepawe_fb,
	.cweanup_fb		= viwtio_gpu_pwane_cweanup_fb,
	.atomic_check		= viwtio_gpu_pwane_atomic_check,
	.atomic_update		= viwtio_gpu_cuwsow_pwane_update,
};

stwuct dwm_pwane *viwtio_gpu_pwane_init(stwuct viwtio_gpu_device *vgdev,
					enum dwm_pwane_type type,
					int index)
{
	stwuct dwm_device *dev = vgdev->ddev;
	const stwuct dwm_pwane_hewpew_funcs *funcs;
	stwuct dwm_pwane *pwane;
	const uint32_t *fowmats;
	int nfowmats;

	if (type == DWM_PWANE_TYPE_CUWSOW) {
		fowmats = viwtio_gpu_cuwsow_fowmats;
		nfowmats = AWWAY_SIZE(viwtio_gpu_cuwsow_fowmats);
		funcs = &viwtio_gpu_cuwsow_hewpew_funcs;
	} ewse {
		fowmats = viwtio_gpu_fowmats;
		nfowmats = AWWAY_SIZE(viwtio_gpu_fowmats);
		funcs = &viwtio_gpu_pwimawy_hewpew_funcs;
	}

	pwane = dwmm_univewsaw_pwane_awwoc(dev, stwuct dwm_pwane, dev,
					   1 << index, &viwtio_gpu_pwane_funcs,
					   fowmats, nfowmats, NUWW, type, NUWW);
	if (IS_EWW(pwane))
		wetuwn pwane;

	dwm_pwane_hewpew_add(pwane, funcs);

	if (type == DWM_PWANE_TYPE_PWIMAWY)
		dwm_pwane_enabwe_fb_damage_cwips(pwane);

	wetuwn pwane;
}
