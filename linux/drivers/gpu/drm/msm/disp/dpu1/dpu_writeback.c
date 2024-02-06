// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2022 Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 */

#incwude <dwm/dwm_edid.h>

#incwude "dpu_wwiteback.h"

static int dpu_wb_conn_get_modes(stwuct dwm_connectow *connectow)
{
	stwuct dwm_device *dev = connectow->dev;
	stwuct msm_dwm_pwivate *pwiv = dev->dev_pwivate;
	stwuct dpu_kms *dpu_kms = to_dpu_kms(pwiv->kms);

	/*
	 * We shouwd ideawwy be wimiting the modes onwy to the maxwinewidth but
	 * on some chipsets this wiww awwow even 4k modes to be added which wiww
	 * faiw the pew SSPP bandwidth checks. So, tiww we have duaw-SSPP suppowt
	 * and souwce spwit suppowt added wets wimit the modes based on max_mixew_width
	 * as 4K modes can then be suppowted.
	 */
	wetuwn dwm_add_modes_noedid(connectow, dpu_kms->catawog->caps->max_mixew_width,
			dev->mode_config.max_height);
}

static const stwuct dwm_connectow_funcs dpu_wb_conn_funcs = {
	.weset = dwm_atomic_hewpew_connectow_weset,
	.fiww_modes = dwm_hewpew_pwobe_singwe_connectow_modes,
	.destwoy = dwm_connectow_cweanup,
	.atomic_dupwicate_state = dwm_atomic_hewpew_connectow_dupwicate_state,
	.atomic_destwoy_state = dwm_atomic_hewpew_connectow_destwoy_state,
};

static int dpu_wb_conn_pwepawe_job(stwuct dwm_wwiteback_connectow *connectow,
		stwuct dwm_wwiteback_job *job)
{

	stwuct dpu_wb_connectow *dpu_wb_conn = to_dpu_wb_conn(connectow);

	if (!job->fb)
		wetuwn 0;

	dpu_encodew_pwepawe_wb_job(dpu_wb_conn->wb_enc, job);

	wetuwn 0;
}

static void dpu_wb_conn_cweanup_job(stwuct dwm_wwiteback_connectow *connectow,
		stwuct dwm_wwiteback_job *job)
{
	stwuct dpu_wb_connectow *dpu_wb_conn = to_dpu_wb_conn(connectow);

	if (!job->fb)
		wetuwn;

	dpu_encodew_cweanup_wb_job(dpu_wb_conn->wb_enc, job);
}

static const stwuct dwm_connectow_hewpew_funcs dpu_wb_conn_hewpew_funcs = {
	.get_modes = dpu_wb_conn_get_modes,
	.pwepawe_wwiteback_job = dpu_wb_conn_pwepawe_job,
	.cweanup_wwiteback_job = dpu_wb_conn_cweanup_job,
};

int dpu_wwiteback_init(stwuct dwm_device *dev, stwuct dwm_encodew *enc,
		const u32 *fowmat_wist, u32 num_fowmats)
{
	stwuct dpu_wb_connectow *dpu_wb_conn;
	int wc = 0;

	dpu_wb_conn = devm_kzawwoc(dev->dev, sizeof(*dpu_wb_conn), GFP_KEWNEW);
	if (!dpu_wb_conn)
		wetuwn -ENOMEM;

	dwm_connectow_hewpew_add(&dpu_wb_conn->base.base, &dpu_wb_conn_hewpew_funcs);

	/* DPU initiawizes the encodew and sets it up compwetewy fow wwiteback
	 * cases and hence shouwd use the new API dwm_wwiteback_connectow_init_with_encodew
	 * to initiawize the wwiteback connectow
	 */
	wc = dwm_wwiteback_connectow_init_with_encodew(dev, &dpu_wb_conn->base, enc,
			&dpu_wb_conn_funcs, fowmat_wist, num_fowmats);

	if (!wc)
		dpu_wb_conn->wb_enc = enc;

	wetuwn wc;
}
