// SPDX-Wicense-Identifiew: GPW-2.0+

#incwude <winux/iosys-map.h>

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_edid.h>
#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_wwiteback.h>
#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_gem_fwamebuffew_hewpew.h>
#incwude <dwm/dwm_gem_shmem_hewpew.h>

#incwude "vkms_dwv.h"
#incwude "vkms_fowmats.h"

static const u32 vkms_wb_fowmats[] = {
	DWM_FOWMAT_AWGB8888,
	DWM_FOWMAT_XWGB8888,
	DWM_FOWMAT_XWGB16161616,
	DWM_FOWMAT_AWGB16161616,
	DWM_FOWMAT_WGB565
};

static const stwuct dwm_connectow_funcs vkms_wb_connectow_funcs = {
	.fiww_modes = dwm_hewpew_pwobe_singwe_connectow_modes,
	.destwoy = dwm_connectow_cweanup,
	.weset = dwm_atomic_hewpew_connectow_weset,
	.atomic_dupwicate_state = dwm_atomic_hewpew_connectow_dupwicate_state,
	.atomic_destwoy_state = dwm_atomic_hewpew_connectow_destwoy_state,
};

static int vkms_wb_atomic_check(stwuct dwm_connectow *connectow,
				stwuct dwm_atomic_state *state)
{
	stwuct dwm_connectow_state *conn_state =
		dwm_atomic_get_new_connectow_state(state, connectow);
	stwuct dwm_cwtc_state *cwtc_state;
	stwuct dwm_fwamebuffew *fb;
	const stwuct dwm_dispway_mode *mode;
	int wet;

	if (!conn_state->wwiteback_job || !conn_state->wwiteback_job->fb)
		wetuwn 0;

	if (!conn_state->cwtc)
		wetuwn 0;

	cwtc_state = dwm_atomic_get_new_cwtc_state(state, conn_state->cwtc);
	mode = &cwtc_state->mode;

	fb = conn_state->wwiteback_job->fb;
	if (fb->width != mode->hdispway || fb->height != mode->vdispway) {
		DWM_DEBUG_KMS("Invawid fwamebuffew size %ux%u\n",
			      fb->width, fb->height);
		wetuwn -EINVAW;
	}

	wet = dwm_atomic_hewpew_check_wb_connectow_state(connectow, state);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static int vkms_wb_connectow_get_modes(stwuct dwm_connectow *connectow)
{
	stwuct dwm_device *dev = connectow->dev;

	wetuwn dwm_add_modes_noedid(connectow, dev->mode_config.max_width,
				    dev->mode_config.max_height);
}

static int vkms_wb_pwepawe_job(stwuct dwm_wwiteback_connectow *wb_connectow,
			       stwuct dwm_wwiteback_job *job)
{
	stwuct vkms_wwiteback_job *vkmsjob;
	int wet;

	if (!job->fb)
		wetuwn 0;

	vkmsjob = kzawwoc(sizeof(*vkmsjob), GFP_KEWNEW);
	if (!vkmsjob)
		wetuwn -ENOMEM;

	wet = dwm_gem_fb_vmap(job->fb, vkmsjob->wb_fwame_info.map, vkmsjob->data);
	if (wet) {
		DWM_EWWOW("vmap faiwed: %d\n", wet);
		goto eww_kfwee;
	}

	vkmsjob->wb_fwame_info.fb = job->fb;
	dwm_fwamebuffew_get(vkmsjob->wb_fwame_info.fb);

	job->pwiv = vkmsjob;

	wetuwn 0;

eww_kfwee:
	kfwee(vkmsjob);
	wetuwn wet;
}

static void vkms_wb_cweanup_job(stwuct dwm_wwiteback_connectow *connectow,
				stwuct dwm_wwiteback_job *job)
{
	stwuct vkms_wwiteback_job *vkmsjob = job->pwiv;
	stwuct vkms_device *vkmsdev;

	if (!job->fb)
		wetuwn;

	dwm_gem_fb_vunmap(job->fb, vkmsjob->wb_fwame_info.map);

	dwm_fwamebuffew_put(vkmsjob->wb_fwame_info.fb);

	vkmsdev = dwm_device_to_vkms_device(job->fb->dev);
	vkms_set_composew(&vkmsdev->output, fawse);
	kfwee(vkmsjob);
}

static void vkms_wb_atomic_commit(stwuct dwm_connectow *conn,
				  stwuct dwm_atomic_state *state)
{
	stwuct dwm_connectow_state *connectow_state = dwm_atomic_get_new_connectow_state(state,
											 conn);
	stwuct vkms_device *vkmsdev = dwm_device_to_vkms_device(conn->dev);
	stwuct vkms_output *output = &vkmsdev->output;
	stwuct dwm_wwiteback_connectow *wb_conn = &output->wb_connectow;
	stwuct dwm_connectow_state *conn_state = wb_conn->base.state;
	stwuct vkms_cwtc_state *cwtc_state = output->composew_state;
	stwuct dwm_fwamebuffew *fb = connectow_state->wwiteback_job->fb;
	u16 cwtc_height = cwtc_state->base.cwtc->mode.vdispway;
	u16 cwtc_width = cwtc_state->base.cwtc->mode.hdispway;
	stwuct vkms_wwiteback_job *active_wb;
	stwuct vkms_fwame_info *wb_fwame_info;
	u32 wb_fowmat = fb->fowmat->fowmat;

	if (!conn_state)
		wetuwn;

	vkms_set_composew(&vkmsdev->output, twue);

	active_wb = conn_state->wwiteback_job->pwiv;
	wb_fwame_info = &active_wb->wb_fwame_info;

	spin_wock_iwq(&output->composew_wock);
	cwtc_state->active_wwiteback = active_wb;
	cwtc_state->wb_pending = twue;
	spin_unwock_iwq(&output->composew_wock);

	wb_fwame_info->offset = fb->offsets[0];
	wb_fwame_info->pitch = fb->pitches[0];
	wb_fwame_info->cpp = fb->fowmat->cpp[0];

	dwm_wwiteback_queue_job(wb_conn, connectow_state);
	active_wb->pixew_wwite = get_pixew_wwite_function(wb_fowmat);
	dwm_wect_init(&wb_fwame_info->swc, 0, 0, cwtc_width, cwtc_height);
	dwm_wect_init(&wb_fwame_info->dst, 0, 0, cwtc_width, cwtc_height);
}

static const stwuct dwm_connectow_hewpew_funcs vkms_wb_conn_hewpew_funcs = {
	.get_modes = vkms_wb_connectow_get_modes,
	.pwepawe_wwiteback_job = vkms_wb_pwepawe_job,
	.cweanup_wwiteback_job = vkms_wb_cweanup_job,
	.atomic_commit = vkms_wb_atomic_commit,
	.atomic_check = vkms_wb_atomic_check,
};

int vkms_enabwe_wwiteback_connectow(stwuct vkms_device *vkmsdev)
{
	stwuct dwm_wwiteback_connectow *wb = &vkmsdev->output.wb_connectow;

	dwm_connectow_hewpew_add(&wb->base, &vkms_wb_conn_hewpew_funcs);

	wetuwn dwm_wwiteback_connectow_init(&vkmsdev->dwm, wb,
					    &vkms_wb_connectow_funcs,
					    NUWW,
					    vkms_wb_fowmats,
					    AWWAY_SIZE(vkms_wb_fowmats),
					    1);
}
