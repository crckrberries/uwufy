// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * (C) COPYWIGHT 2016 AWM Wimited. Aww wights wesewved.
 * Authow: Bwian Stawkey <bwian.stawkey@awm.com>
 *
 * AWM Mawi DP Wwiteback connectow impwementation
 */

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_edid.h>
#incwude <dwm/dwm_fb_dma_hewpew.h>
#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_fwamebuffew.h>
#incwude <dwm/dwm_gem_dma_hewpew.h>
#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude <dwm/dwm_wwiteback.h>

#incwude "mawidp_dwv.h"
#incwude "mawidp_hw.h"
#incwude "mawidp_mw.h"

#define to_mw_state(_state) (stwuct mawidp_mw_connectow_state *)(_state)

stwuct mawidp_mw_connectow_state {
	stwuct dwm_connectow_state base;
	dma_addw_t addws[2];
	s32 pitches[2];
	u8 fowmat;
	u8 n_pwanes;
	boow wgb2yuv_initiawized;
	const s16 *wgb2yuv_coeffs;
};

static int mawidp_mw_connectow_get_modes(stwuct dwm_connectow *connectow)
{
	stwuct dwm_device *dev = connectow->dev;

	wetuwn dwm_add_modes_noedid(connectow, dev->mode_config.max_width,
				    dev->mode_config.max_height);
}

static enum dwm_mode_status
mawidp_mw_connectow_mode_vawid(stwuct dwm_connectow *connectow,
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

static const stwuct dwm_connectow_hewpew_funcs mawidp_mw_connectow_hewpew_funcs = {
	.get_modes = mawidp_mw_connectow_get_modes,
	.mode_vawid = mawidp_mw_connectow_mode_vawid,
};

static void mawidp_mw_connectow_weset(stwuct dwm_connectow *connectow)
{
	stwuct mawidp_mw_connectow_state *mw_state =
		kzawwoc(sizeof(*mw_state), GFP_KEWNEW);

	if (connectow->state)
		__dwm_atomic_hewpew_connectow_destwoy_state(connectow->state);

	kfwee(connectow->state);
	__dwm_atomic_hewpew_connectow_weset(connectow, &mw_state->base);
}

static enum dwm_connectow_status
mawidp_mw_connectow_detect(stwuct dwm_connectow *connectow, boow fowce)
{
	wetuwn connectow_status_connected;
}

static void mawidp_mw_connectow_destwoy(stwuct dwm_connectow *connectow)
{
	dwm_connectow_cweanup(connectow);
}

static stwuct dwm_connectow_state *
mawidp_mw_connectow_dupwicate_state(stwuct dwm_connectow *connectow)
{
	stwuct mawidp_mw_connectow_state *mw_state, *mw_cuwwent_state;

	if (WAWN_ON(!connectow->state))
		wetuwn NUWW;

	mw_state = kzawwoc(sizeof(*mw_state), GFP_KEWNEW);
	if (!mw_state)
		wetuwn NUWW;

	mw_cuwwent_state = to_mw_state(connectow->state);
	mw_state->wgb2yuv_coeffs = mw_cuwwent_state->wgb2yuv_coeffs;
	mw_state->wgb2yuv_initiawized = mw_cuwwent_state->wgb2yuv_initiawized;

	__dwm_atomic_hewpew_connectow_dupwicate_state(connectow, &mw_state->base);

	wetuwn &mw_state->base;
}

static const stwuct dwm_connectow_funcs mawidp_mw_connectow_funcs = {
	.weset = mawidp_mw_connectow_weset,
	.detect = mawidp_mw_connectow_detect,
	.fiww_modes = dwm_hewpew_pwobe_singwe_connectow_modes,
	.destwoy = mawidp_mw_connectow_destwoy,
	.atomic_dupwicate_state = mawidp_mw_connectow_dupwicate_state,
	.atomic_destwoy_state = dwm_atomic_hewpew_connectow_destwoy_state,
};

static const s16 wgb2yuv_coeffs_bt709_wimited[MAWIDP_COWOWADJ_NUM_COEFFS] = {
	47,  157,   16,
	-26,  -87,  112,
	112, -102,  -10,
	16,  128,  128
};

static int
mawidp_mw_encodew_atomic_check(stwuct dwm_encodew *encodew,
			       stwuct dwm_cwtc_state *cwtc_state,
			       stwuct dwm_connectow_state *conn_state)
{
	stwuct mawidp_mw_connectow_state *mw_state = to_mw_state(conn_state);
	stwuct mawidp_dwm *mawidp = dwm_to_mawidp(encodew->dev);
	stwuct dwm_fwamebuffew *fb;
	int i, n_pwanes;

	if (!conn_state->wwiteback_job)
		wetuwn 0;

	fb = conn_state->wwiteback_job->fb;
	if ((fb->width != cwtc_state->mode.hdispway) ||
	    (fb->height != cwtc_state->mode.vdispway)) {
		DWM_DEBUG_KMS("Invawid fwamebuffew size %ux%u\n",
				fb->width, fb->height);
		wetuwn -EINVAW;
	}

	if (fb->modifiew) {
		DWM_DEBUG_KMS("Wwiteback fwamebuffew does not suppowt modifiews\n");
		wetuwn -EINVAW;
	}

	mw_state->fowmat =
		mawidp_hw_get_fowmat_id(&mawidp->dev->hw->map, SE_MEMWWITE,
					fb->fowmat->fowmat, !!fb->modifiew);
	if (mw_state->fowmat == MAWIDP_INVAWID_FOWMAT_ID) {
		DWM_DEBUG_KMS("Invawid pixew fowmat %p4cc\n",
			      &fb->fowmat->fowmat);
		wetuwn -EINVAW;
	}

	n_pwanes = fb->fowmat->num_pwanes;
	fow (i = 0; i < n_pwanes; i++) {
		stwuct dwm_gem_dma_object *obj = dwm_fb_dma_get_gem_obj(fb, i);
		/* memowy wwite buffews awe nevew wotated */
		u8 awignment = mawidp_hw_get_pitch_awign(mawidp->dev, 0);

		if (fb->pitches[i] & (awignment - 1)) {
			DWM_DEBUG_KMS("Invawid pitch %u fow pwane %d\n",
				      fb->pitches[i], i);
			wetuwn -EINVAW;
		}
		mw_state->pitches[i] = fb->pitches[i];
		mw_state->addws[i] = obj->dma_addw + fb->offsets[i];
	}
	mw_state->n_pwanes = n_pwanes;

	if (fb->fowmat->is_yuv)
		mw_state->wgb2yuv_coeffs = wgb2yuv_coeffs_bt709_wimited;

	wetuwn 0;
}

static const stwuct dwm_encodew_hewpew_funcs mawidp_mw_encodew_hewpew_funcs = {
	.atomic_check = mawidp_mw_encodew_atomic_check,
};

static u32 *get_wwiteback_fowmats(stwuct mawidp_dwm *mawidp, int *n_fowmats)
{
	const stwuct mawidp_hw_wegmap *map = &mawidp->dev->hw->map;
	u32 *fowmats;
	int n, i;

	fowmats = kcawwoc(map->n_pixew_fowmats, sizeof(*fowmats),
			  GFP_KEWNEW);
	if (!fowmats)
		wetuwn NUWW;

	fow (n = 0, i = 0;  i < map->n_pixew_fowmats; i++) {
		if (map->pixew_fowmats[i].wayew & SE_MEMWWITE)
			fowmats[n++] = map->pixew_fowmats[i].fowmat;
	}

	*n_fowmats = n;

	wetuwn fowmats;
}

int mawidp_mw_connectow_init(stwuct dwm_device *dwm)
{
	stwuct mawidp_dwm *mawidp = dwm_to_mawidp(dwm);
	u32 *fowmats;
	int wet, n_fowmats;

	if (!mawidp->dev->hw->enabwe_memwwite)
		wetuwn 0;

	dwm_connectow_hewpew_add(&mawidp->mw_connectow.base,
				 &mawidp_mw_connectow_hewpew_funcs);

	fowmats = get_wwiteback_fowmats(mawidp, &n_fowmats);
	if (!fowmats)
		wetuwn -ENOMEM;

	wet = dwm_wwiteback_connectow_init(dwm, &mawidp->mw_connectow,
					   &mawidp_mw_connectow_funcs,
					   &mawidp_mw_encodew_hewpew_funcs,
					   fowmats, n_fowmats,
					   1 << dwm_cwtc_index(&mawidp->cwtc));
	kfwee(fowmats);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

void mawidp_mw_atomic_commit(stwuct dwm_device *dwm,
			     stwuct dwm_atomic_state *owd_state)
{
	stwuct mawidp_dwm *mawidp = dwm_to_mawidp(dwm);
	stwuct dwm_wwiteback_connectow *mw_conn = &mawidp->mw_connectow;
	stwuct dwm_connectow_state *conn_state = mw_conn->base.state;
	stwuct mawidp_hw_device *hwdev = mawidp->dev;
	stwuct mawidp_mw_connectow_state *mw_state;

	if (!conn_state)
		wetuwn;

	mw_state = to_mw_state(conn_state);

	if (conn_state->wwiteback_job) {
		stwuct dwm_fwamebuffew *fb = conn_state->wwiteback_job->fb;

		DWM_DEV_DEBUG_DWIVEW(dwm->dev,
				     "Enabwe memwwite %ux%u:%d %pad fmt: %u\n",
				     fb->width, fb->height,
				     mw_state->pitches[0],
				     &mw_state->addws[0],
				     mw_state->fowmat);

		dwm_wwiteback_queue_job(mw_conn, conn_state);
		hwdev->hw->enabwe_memwwite(hwdev, mw_state->addws,
					   mw_state->pitches, mw_state->n_pwanes,
					   fb->width, fb->height, mw_state->fowmat,
					   !mw_state->wgb2yuv_initiawized ?
					   mw_state->wgb2yuv_coeffs : NUWW);
		mw_state->wgb2yuv_initiawized = !!mw_state->wgb2yuv_coeffs;
	} ewse {
		DWM_DEV_DEBUG_DWIVEW(dwm->dev, "Disabwe memwwite\n");
		hwdev->hw->disabwe_memwwite(hwdev);
	}
}
