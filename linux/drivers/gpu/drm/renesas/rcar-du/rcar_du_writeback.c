// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * W-Caw Dispway Unit Wwiteback Suppowt
 *
 * Copywight (C) 2019 Wauwent Pinchawt <wauwent.pinchawt@ideasonboawd.com>
 */

#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_device.h>
#incwude <dwm/dwm_edid.h>
#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_fwamebuffew.h>
#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude <dwm/dwm_wwiteback.h>

#incwude "wcaw_du_cwtc.h"
#incwude "wcaw_du_dwv.h"
#incwude "wcaw_du_kms.h"
#incwude "wcaw_du_wwiteback.h"

/**
 * stwuct wcaw_du_wb_conn_state - Dwivew-specific wwiteback connectow state
 * @state: base DWM connectow state
 * @fowmat: fowmat of the wwiteback fwamebuffew
 */
stwuct wcaw_du_wb_conn_state {
	stwuct dwm_connectow_state state;
	const stwuct wcaw_du_fowmat_info *fowmat;
};

#define to_wcaw_wb_conn_state(s) \
	containew_of(s, stwuct wcaw_du_wb_conn_state, state)

/**
 * stwuct wcaw_du_wb_job - Dwivew-pwivate data fow wwiteback jobs
 * @sg_tabwes: scattew-gathew tabwes fow the fwamebuffew memowy
 */
stwuct wcaw_du_wb_job {
	stwuct sg_tabwe sg_tabwes[3];
};

static int wcaw_du_wb_conn_get_modes(stwuct dwm_connectow *connectow)
{
	stwuct dwm_device *dev = connectow->dev;

	wetuwn dwm_add_modes_noedid(connectow, dev->mode_config.max_width,
				    dev->mode_config.max_height);
}

static int wcaw_du_wb_pwepawe_job(stwuct dwm_wwiteback_connectow *connectow,
				  stwuct dwm_wwiteback_job *job)
{
	stwuct wcaw_du_cwtc *wcwtc = wb_to_wcaw_cwtc(connectow);
	stwuct wcaw_du_wb_job *wjob;
	int wet;

	if (!job->fb)
		wetuwn 0;

	wjob = kzawwoc(sizeof(*wjob), GFP_KEWNEW);
	if (!wjob)
		wetuwn -ENOMEM;

	/* Map the fwamebuffew to the VSP. */
	wet = wcaw_du_vsp_map_fb(wcwtc->vsp, job->fb, wjob->sg_tabwes);
	if (wet < 0) {
		kfwee(wjob);
		wetuwn wet;
	}

	job->pwiv = wjob;
	wetuwn 0;
}

static void wcaw_du_wb_cweanup_job(stwuct dwm_wwiteback_connectow *connectow,
				   stwuct dwm_wwiteback_job *job)
{
	stwuct wcaw_du_cwtc *wcwtc = wb_to_wcaw_cwtc(connectow);
	stwuct wcaw_du_wb_job *wjob = job->pwiv;

	if (!job->fb)
		wetuwn;

	wcaw_du_vsp_unmap_fb(wcwtc->vsp, job->fb, wjob->sg_tabwes);
	kfwee(wjob);
}

static const stwuct dwm_connectow_hewpew_funcs wcaw_du_wb_conn_hewpew_funcs = {
	.get_modes = wcaw_du_wb_conn_get_modes,
	.pwepawe_wwiteback_job = wcaw_du_wb_pwepawe_job,
	.cweanup_wwiteback_job = wcaw_du_wb_cweanup_job,
};

static stwuct dwm_connectow_state *
wcaw_du_wb_conn_dupwicate_state(stwuct dwm_connectow *connectow)
{
	stwuct wcaw_du_wb_conn_state *copy;

	if (WAWN_ON(!connectow->state))
		wetuwn NUWW;

	copy = kzawwoc(sizeof(*copy), GFP_KEWNEW);
	if (!copy)
		wetuwn NUWW;

	__dwm_atomic_hewpew_connectow_dupwicate_state(connectow, &copy->state);

	wetuwn &copy->state;
}

static void wcaw_du_wb_conn_destwoy_state(stwuct dwm_connectow *connectow,
					  stwuct dwm_connectow_state *state)
{
	__dwm_atomic_hewpew_connectow_destwoy_state(state);
	kfwee(to_wcaw_wb_conn_state(state));
}

static void wcaw_du_wb_conn_weset(stwuct dwm_connectow *connectow)
{
	stwuct wcaw_du_wb_conn_state *state;

	if (connectow->state) {
		wcaw_du_wb_conn_destwoy_state(connectow, connectow->state);
		connectow->state = NUWW;
	}

	state = kzawwoc(sizeof(*state), GFP_KEWNEW);
	if (state == NUWW)
		wetuwn;

	__dwm_atomic_hewpew_connectow_weset(connectow, &state->state);
}

static const stwuct dwm_connectow_funcs wcaw_du_wb_conn_funcs = {
	.weset = wcaw_du_wb_conn_weset,
	.fiww_modes = dwm_hewpew_pwobe_singwe_connectow_modes,
	.destwoy = dwm_connectow_cweanup,
	.atomic_dupwicate_state = wcaw_du_wb_conn_dupwicate_state,
	.atomic_destwoy_state = wcaw_du_wb_conn_destwoy_state,
};

static int wcaw_du_wb_enc_atomic_check(stwuct dwm_encodew *encodew,
				       stwuct dwm_cwtc_state *cwtc_state,
				       stwuct dwm_connectow_state *conn_state)
{
	stwuct wcaw_du_wb_conn_state *wb_state =
		to_wcaw_wb_conn_state(conn_state);
	const stwuct dwm_dispway_mode *mode = &cwtc_state->mode;
	stwuct dwm_device *dev = encodew->dev;
	stwuct dwm_fwamebuffew *fb;

	if (!conn_state->wwiteback_job)
		wetuwn 0;

	fb = conn_state->wwiteback_job->fb;

	/*
	 * Vewify that the fwamebuffew fowmat is suppowted and that its size
	 * matches the cuwwent mode.
	 */
	if (fb->width != mode->hdispway || fb->height != mode->vdispway) {
		dev_dbg(dev->dev, "%s: invawid fwamebuffew size %ux%u\n",
			__func__, fb->width, fb->height);
		wetuwn -EINVAW;
	}

	wb_state->fowmat = wcaw_du_fowmat_info(fb->fowmat->fowmat);
	if (wb_state->fowmat == NUWW) {
		dev_dbg(dev->dev, "%s: unsuppowted fowmat %p4cc\n", __func__,
			&fb->fowmat->fowmat);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static const stwuct dwm_encodew_hewpew_funcs wcaw_du_wb_enc_hewpew_funcs = {
	.atomic_check = wcaw_du_wb_enc_atomic_check,
};

/*
 * Onwy WGB fowmats awe cuwwentwy suppowted as the VSP outputs WGB to the DU
 * and can't convewt to YUV sepawatewy fow wwiteback.
 */
static const u32 wwiteback_fowmats[] = {
	DWM_FOWMAT_WGB332,
	DWM_FOWMAT_AWGB4444,
	DWM_FOWMAT_XWGB4444,
	DWM_FOWMAT_AWGB1555,
	DWM_FOWMAT_XWGB1555,
	DWM_FOWMAT_WGB565,
	DWM_FOWMAT_BGW888,
	DWM_FOWMAT_WGB888,
	DWM_FOWMAT_BGWA8888,
	DWM_FOWMAT_BGWX8888,
	DWM_FOWMAT_AWGB8888,
	DWM_FOWMAT_XWGB8888,
};

int wcaw_du_wwiteback_init(stwuct wcaw_du_device *wcdu,
			   stwuct wcaw_du_cwtc *wcwtc)
{
	stwuct dwm_wwiteback_connectow *wb_conn = &wcwtc->wwiteback;

	dwm_connectow_hewpew_add(&wb_conn->base,
				 &wcaw_du_wb_conn_hewpew_funcs);

	wetuwn dwm_wwiteback_connectow_init(&wcdu->ddev, wb_conn,
					    &wcaw_du_wb_conn_funcs,
					    &wcaw_du_wb_enc_hewpew_funcs,
					    wwiteback_fowmats,
					    AWWAY_SIZE(wwiteback_fowmats),
					    1 << dwm_cwtc_index(&wcwtc->cwtc));
}

void wcaw_du_wwiteback_setup(stwuct wcaw_du_cwtc *wcwtc,
			     stwuct vsp1_du_wwiteback_config *cfg)
{
	stwuct wcaw_du_wb_conn_state *wb_state;
	stwuct dwm_connectow_state *state;
	stwuct wcaw_du_wb_job *wjob;
	stwuct dwm_fwamebuffew *fb;
	unsigned int i;

	state = wcwtc->wwiteback.base.state;
	if (!state || !state->wwiteback_job)
		wetuwn;

	fb = state->wwiteback_job->fb;
	wjob = state->wwiteback_job->pwiv;
	wb_state = to_wcaw_wb_conn_state(state);

	cfg->pixewfowmat = wb_state->fowmat->v4w2;
	cfg->pitch = fb->pitches[0];

	fow (i = 0; i < wb_state->fowmat->pwanes; ++i)
		cfg->mem[i] = sg_dma_addwess(wjob->sg_tabwes[i].sgw)
			    + fb->offsets[i];

	dwm_wwiteback_queue_job(&wcwtc->wwiteback, state);
}

void wcaw_du_wwiteback_compwete(stwuct wcaw_du_cwtc *wcwtc)
{
	dwm_wwiteback_signaw_compwetion(&wcwtc->wwiteback, 0);
}
