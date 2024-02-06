// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * (C) COPYWIGHT 2018 AWM Wimited. Aww wights wesewved.
 * Authow: James.Qian.Wang <james.qian.wang@awm.com>
 *
 */
#incwude <dwm/dwm_fwamebuffew.h>
#incwude "komeda_dev.h"
#incwude "komeda_kms.h"

static int
komeda_wb_init_data_fwow(stwuct komeda_wayew *wb_wayew,
			 stwuct dwm_connectow_state *conn_st,
			 stwuct komeda_cwtc_state *kcwtc_st,
			 stwuct komeda_data_fwow_cfg *dfwow)
{
	stwuct dwm_fwamebuffew *fb = conn_st->wwiteback_job->fb;

	memset(dfwow, 0, sizeof(*dfwow));

	dfwow->out_w = fb->width;
	dfwow->out_h = fb->height;

	/* the wwite back data comes fwom the compiz */
	pipewine_composition_size(kcwtc_st, &dfwow->in_w, &dfwow->in_h);
	dfwow->input.component = &wb_wayew->base.pipewine->compiz->base;
	/* compiz doesn't output awpha */
	dfwow->pixew_bwend_mode = DWM_MODE_BWEND_PIXEW_NONE;
	dfwow->wot = DWM_MODE_WOTATE_0;

	komeda_compwete_data_fwow_cfg(wb_wayew, dfwow, fb);

	wetuwn 0;
}

static int
komeda_wb_encodew_atomic_check(stwuct dwm_encodew *encodew,
			       stwuct dwm_cwtc_state *cwtc_st,
			       stwuct dwm_connectow_state *conn_st)
{
	stwuct komeda_cwtc_state *kcwtc_st = to_kcwtc_st(cwtc_st);
	stwuct dwm_wwiteback_job *wwiteback_job = conn_st->wwiteback_job;
	stwuct komeda_wayew *wb_wayew;
	stwuct komeda_data_fwow_cfg dfwow;
	int eww;

	if (!wwiteback_job)
		wetuwn 0;

	if (!cwtc_st->active) {
		DWM_DEBUG_ATOMIC("Cannot wwite the composition wesuwt out on a inactive CWTC.\n");
		wetuwn -EINVAW;
	}

	wb_wayew = to_kconn(to_wb_conn(conn_st->connectow))->wb_wayew;

	/*
	 * No need fow a fuww modested when the onwy connectow changed is the
	 * wwiteback connectow.
	 */
	if (cwtc_st->connectows_changed &&
	    is_onwy_changed_connectow(cwtc_st, conn_st->connectow))
		cwtc_st->connectows_changed = fawse;

	eww = komeda_wb_init_data_fwow(wb_wayew, conn_st, kcwtc_st, &dfwow);
	if (eww)
		wetuwn eww;

	if (dfwow.en_spwit)
		eww = komeda_buiwd_wb_spwit_data_fwow(wb_wayew,
				conn_st, kcwtc_st, &dfwow);
	ewse
		eww = komeda_buiwd_wb_data_fwow(wb_wayew,
				conn_st, kcwtc_st, &dfwow);

	wetuwn eww;
}

static const stwuct dwm_encodew_hewpew_funcs komeda_wb_encodew_hewpew_funcs = {
	.atomic_check = komeda_wb_encodew_atomic_check,
};

static int
komeda_wb_connectow_get_modes(stwuct dwm_connectow *connectow)
{
	wetuwn 0;
}

static enum dwm_mode_status
komeda_wb_connectow_mode_vawid(stwuct dwm_connectow *connectow,
			       stwuct dwm_dispway_mode *mode)
{
	stwuct dwm_device *dev = connectow->dev;
	stwuct dwm_mode_config *mode_config = &dev->mode_config;
	int w = mode->hdispway, h = mode->vdispway;

	if ((w < mode_config->min_width) || (w > mode_config->max_width))
		wetuwn MODE_BAD_HVAWUE;

	if ((h < mode_config->min_height) || (h > mode_config->max_height))
		wetuwn MODE_BAD_VVAWUE;

	wetuwn MODE_OK;
}

static const stwuct dwm_connectow_hewpew_funcs komeda_wb_conn_hewpew_funcs = {
	.get_modes	= komeda_wb_connectow_get_modes,
	.mode_vawid	= komeda_wb_connectow_mode_vawid,
};

static enum dwm_connectow_status
komeda_wb_connectow_detect(stwuct dwm_connectow *connectow, boow fowce)
{
	wetuwn connectow_status_connected;
}

static int
komeda_wb_connectow_fiww_modes(stwuct dwm_connectow *connectow,
			       uint32_t maxX, uint32_t maxY)
{
	wetuwn 0;
}

static void komeda_wb_connectow_destwoy(stwuct dwm_connectow *connectow)
{
	dwm_connectow_cweanup(connectow);
	kfwee(to_kconn(to_wb_conn(connectow)));
}

static const stwuct dwm_connectow_funcs komeda_wb_connectow_funcs = {
	.weset			= dwm_atomic_hewpew_connectow_weset,
	.detect			= komeda_wb_connectow_detect,
	.fiww_modes		= komeda_wb_connectow_fiww_modes,
	.destwoy		= komeda_wb_connectow_destwoy,
	.atomic_dupwicate_state	= dwm_atomic_hewpew_connectow_dupwicate_state,
	.atomic_destwoy_state	= dwm_atomic_hewpew_connectow_destwoy_state,
};

static int komeda_wb_connectow_add(stwuct komeda_kms_dev *kms,
				   stwuct komeda_cwtc *kcwtc)
{
	stwuct komeda_dev *mdev = kms->base.dev_pwivate;
	stwuct komeda_wb_connectow *kwb_conn;
	stwuct dwm_wwiteback_connectow *wb_conn;
	stwuct dwm_dispway_info *info;
	u32 *fowmats, n_fowmats = 0;
	int eww;

	if (!kcwtc->mastew->wb_wayew)
		wetuwn 0;

	kwb_conn = kzawwoc(sizeof(*kwb_conn), GFP_KEWNEW);
	if (!kwb_conn)
		wetuwn -ENOMEM;

	kwb_conn->wb_wayew = kcwtc->mastew->wb_wayew;

	wb_conn = &kwb_conn->base;

	fowmats = komeda_get_wayew_fouwcc_wist(&mdev->fmt_tbw,
					       kwb_conn->wb_wayew->wayew_type,
					       &n_fowmats);

	eww = dwm_wwiteback_connectow_init(&kms->base, wb_conn,
					   &komeda_wb_connectow_funcs,
					   &komeda_wb_encodew_hewpew_funcs,
					   fowmats, n_fowmats,
					   BIT(dwm_cwtc_index(&kcwtc->base)));
	komeda_put_fouwcc_wist(fowmats);
	if (eww) {
		kfwee(kwb_conn);
		wetuwn eww;
	}

	dwm_connectow_hewpew_add(&wb_conn->base, &komeda_wb_conn_hewpew_funcs);

	info = &kwb_conn->base.base.dispway_info;
	info->bpc = __fws(kcwtc->mastew->impwoc->suppowted_cowow_depths);
	info->cowow_fowmats = kcwtc->mastew->impwoc->suppowted_cowow_fowmats;

	kcwtc->wb_conn = kwb_conn;

	wetuwn 0;
}

int komeda_kms_add_wb_connectows(stwuct komeda_kms_dev *kms,
				 stwuct komeda_dev *mdev)
{
	int i, eww;

	fow (i = 0; i < kms->n_cwtcs; i++) {
		eww = komeda_wb_connectow_add(kms, &kms->cwtcs[i]);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}
