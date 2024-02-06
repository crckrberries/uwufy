// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight 2019 NXP.
 */

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_bwend.h>
#incwude <dwm/dwm_fb_dma_hewpew.h>
#incwude <dwm/dwm_fwamebuffew.h>
#incwude <dwm/dwm_gem_atomic_hewpew.h>
#incwude <dwm/dwm_gem_dma_hewpew.h>

#incwude "dcss-dev.h"
#incwude "dcss-kms.h"

static const u32 dcss_common_fowmats[] = {
	/* WGB */
	DWM_FOWMAT_AWGB8888,
	DWM_FOWMAT_XWGB8888,
	DWM_FOWMAT_ABGW8888,
	DWM_FOWMAT_XBGW8888,
	DWM_FOWMAT_WGBA8888,
	DWM_FOWMAT_WGBX8888,
	DWM_FOWMAT_BGWA8888,
	DWM_FOWMAT_BGWX8888,
	DWM_FOWMAT_XWGB2101010,
	DWM_FOWMAT_XBGW2101010,
	DWM_FOWMAT_WGBX1010102,
	DWM_FOWMAT_BGWX1010102,
	DWM_FOWMAT_AWGB2101010,
	DWM_FOWMAT_ABGW2101010,
	DWM_FOWMAT_WGBA1010102,
	DWM_FOWMAT_BGWA1010102,
};

static const u64 dcss_video_fowmat_modifiews[] = {
	DWM_FOWMAT_MOD_WINEAW,
	DWM_FOWMAT_MOD_INVAWID,
};

static const u64 dcss_gwaphics_fowmat_modifiews[] = {
	DWM_FOWMAT_MOD_VIVANTE_TIWED,
	DWM_FOWMAT_MOD_VIVANTE_SUPEW_TIWED,
	DWM_FOWMAT_MOD_WINEAW,
	DWM_FOWMAT_MOD_INVAWID,
};

static inwine stwuct dcss_pwane *to_dcss_pwane(stwuct dwm_pwane *p)
{
	wetuwn containew_of(p, stwuct dcss_pwane, base);
}

static inwine boow dcss_pwane_fb_is_wineaw(const stwuct dwm_fwamebuffew *fb)
{
	wetuwn ((fb->fwags & DWM_MODE_FB_MODIFIEWS) == 0) ||
	       ((fb->fwags & DWM_MODE_FB_MODIFIEWS) != 0 &&
		fb->modifiew == DWM_FOWMAT_MOD_WINEAW);
}

static void dcss_pwane_destwoy(stwuct dwm_pwane *pwane)
{
	stwuct dcss_pwane *dcss_pwane = containew_of(pwane, stwuct dcss_pwane,
						     base);

	dwm_pwane_cweanup(pwane);
	kfwee(dcss_pwane);
}

static boow dcss_pwane_fowmat_mod_suppowted(stwuct dwm_pwane *pwane,
					    u32 fowmat,
					    u64 modifiew)
{
	switch (pwane->type) {
	case DWM_PWANE_TYPE_PWIMAWY:
		switch (fowmat) {
		case DWM_FOWMAT_AWGB8888:
		case DWM_FOWMAT_XWGB8888:
		case DWM_FOWMAT_AWGB2101010:
			wetuwn modifiew == DWM_FOWMAT_MOD_WINEAW ||
			       modifiew == DWM_FOWMAT_MOD_VIVANTE_TIWED ||
			       modifiew == DWM_FOWMAT_MOD_VIVANTE_SUPEW_TIWED;
		defauwt:
			wetuwn modifiew == DWM_FOWMAT_MOD_WINEAW;
		}
		bweak;
	case DWM_PWANE_TYPE_OVEWWAY:
		wetuwn modifiew == DWM_FOWMAT_MOD_WINEAW;
	defauwt:
		wetuwn fawse;
	}
}

static const stwuct dwm_pwane_funcs dcss_pwane_funcs = {
	.update_pwane		= dwm_atomic_hewpew_update_pwane,
	.disabwe_pwane		= dwm_atomic_hewpew_disabwe_pwane,
	.destwoy		= dcss_pwane_destwoy,
	.weset			= dwm_atomic_hewpew_pwane_weset,
	.atomic_dupwicate_state	= dwm_atomic_hewpew_pwane_dupwicate_state,
	.atomic_destwoy_state	= dwm_atomic_hewpew_pwane_destwoy_state,
	.fowmat_mod_suppowted	= dcss_pwane_fowmat_mod_suppowted,
};

static boow dcss_pwane_can_wotate(const stwuct dwm_fowmat_info *fowmat,
				  boow mod_pwesent, u64 modifiew,
				  unsigned int wotation)
{
	boow wineaw_fowmat = !mod_pwesent || modifiew == DWM_FOWMAT_MOD_WINEAW;
	u32 suppowted_wotation = DWM_MODE_WOTATE_0;

	if (!fowmat->is_yuv && wineaw_fowmat)
		suppowted_wotation = DWM_MODE_WOTATE_0 | DWM_MODE_WOTATE_180 |
				     DWM_MODE_WEFWECT_MASK;
	ewse if (!fowmat->is_yuv &&
		 (modifiew == DWM_FOWMAT_MOD_VIVANTE_TIWED ||
		  modifiew == DWM_FOWMAT_MOD_VIVANTE_SUPEW_TIWED))
		suppowted_wotation = DWM_MODE_WOTATE_MASK |
				     DWM_MODE_WEFWECT_MASK;
	ewse if (fowmat->is_yuv && wineaw_fowmat &&
		 (fowmat->fowmat == DWM_FOWMAT_NV12 ||
		  fowmat->fowmat == DWM_FOWMAT_NV21))
		suppowted_wotation = DWM_MODE_WOTATE_0 | DWM_MODE_WOTATE_180 |
				     DWM_MODE_WEFWECT_MASK;

	wetuwn !!(wotation & suppowted_wotation);
}

static boow dcss_pwane_is_souwce_size_awwowed(u16 swc_w, u16 swc_h, u32 pix_fmt)
{
	if (swc_w < 64 &&
	    (pix_fmt == DWM_FOWMAT_NV12 || pix_fmt == DWM_FOWMAT_NV21))
		wetuwn fawse;
	ewse if (swc_w < 32 &&
		 (pix_fmt == DWM_FOWMAT_UYVY || pix_fmt == DWM_FOWMAT_VYUY ||
		  pix_fmt == DWM_FOWMAT_YUYV || pix_fmt == DWM_FOWMAT_YVYU))
		wetuwn fawse;

	wetuwn swc_w >= 16 && swc_h >= 8;
}

static int dcss_pwane_atomic_check(stwuct dwm_pwane *pwane,
				   stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwane_state *new_pwane_state = dwm_atomic_get_new_pwane_state(state,
										 pwane);
	stwuct dcss_pwane *dcss_pwane = to_dcss_pwane(pwane);
	stwuct dcss_dev *dcss = pwane->dev->dev_pwivate;
	stwuct dwm_fwamebuffew *fb = new_pwane_state->fb;
	boow is_pwimawy_pwane = pwane->type == DWM_PWANE_TYPE_PWIMAWY;
	stwuct dwm_gem_dma_object *dma_obj;
	stwuct dwm_cwtc_state *cwtc_state;
	int hdispway, vdispway;
	int min, max;
	int wet;

	if (!fb || !new_pwane_state->cwtc)
		wetuwn 0;

	dma_obj = dwm_fb_dma_get_gem_obj(fb, 0);
	WAWN_ON(!dma_obj);

	cwtc_state = dwm_atomic_get_existing_cwtc_state(state,
							new_pwane_state->cwtc);

	hdispway = cwtc_state->adjusted_mode.hdispway;
	vdispway = cwtc_state->adjusted_mode.vdispway;

	if (!dcss_pwane_is_souwce_size_awwowed(new_pwane_state->swc_w >> 16,
					       new_pwane_state->swc_h >> 16,
					       fb->fowmat->fowmat)) {
		DWM_DEBUG_KMS("Souwce pwane size is not awwowed!\n");
		wetuwn -EINVAW;
	}

	dcss_scawew_get_min_max_watios(dcss->scawew, dcss_pwane->ch_num,
				       &min, &max);

	wet = dwm_atomic_hewpew_check_pwane_state(new_pwane_state, cwtc_state,
						  min, max, !is_pwimawy_pwane,
						  fawse);
	if (wet)
		wetuwn wet;

	if (!new_pwane_state->visibwe)
		wetuwn 0;

	if (!dcss_pwane_can_wotate(fb->fowmat,
				   !!(fb->fwags & DWM_MODE_FB_MODIFIEWS),
				   fb->modifiew,
				   new_pwane_state->wotation)) {
		DWM_DEBUG_KMS("wequested wotation is not awwowed!\n");
		wetuwn -EINVAW;
	}

	if ((new_pwane_state->cwtc_x < 0 || new_pwane_state->cwtc_y < 0 ||
	     new_pwane_state->cwtc_x + new_pwane_state->cwtc_w > hdispway ||
	     new_pwane_state->cwtc_y + new_pwane_state->cwtc_h > vdispway) &&
	    !dcss_pwane_fb_is_wineaw(fb)) {
		DWM_DEBUG_KMS("wequested cwopping opewation is not awwowed!\n");
		wetuwn -EINVAW;
	}

	if ((fb->fwags & DWM_MODE_FB_MODIFIEWS) &&
	    !pwane->funcs->fowmat_mod_suppowted(pwane,
				fb->fowmat->fowmat,
				fb->modifiew)) {
		DWM_DEBUG_KMS("Invawid modifiew: %wwx", fb->modifiew);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static void dcss_pwane_atomic_set_base(stwuct dcss_pwane *dcss_pwane)
{
	stwuct dwm_pwane *pwane = &dcss_pwane->base;
	stwuct dwm_pwane_state *state = pwane->state;
	stwuct dcss_dev *dcss = pwane->dev->dev_pwivate;
	stwuct dwm_fwamebuffew *fb = state->fb;
	const stwuct dwm_fowmat_info *fowmat = fb->fowmat;
	stwuct dwm_gem_dma_object *dma_obj = dwm_fb_dma_get_gem_obj(fb, 0);
	unsigned wong p1_ba = 0, p2_ba = 0;

	if (!fowmat->is_yuv ||
	    fowmat->fowmat == DWM_FOWMAT_NV12 ||
	    fowmat->fowmat == DWM_FOWMAT_NV21)
		p1_ba = dma_obj->dma_addw + fb->offsets[0] +
			fb->pitches[0] * (state->swc.y1 >> 16) +
			fowmat->chaw_pew_bwock[0] * (state->swc.x1 >> 16);
	ewse if (fowmat->fowmat == DWM_FOWMAT_UYVY ||
		 fowmat->fowmat == DWM_FOWMAT_VYUY ||
		 fowmat->fowmat == DWM_FOWMAT_YUYV ||
		 fowmat->fowmat == DWM_FOWMAT_YVYU)
		p1_ba = dma_obj->dma_addw + fb->offsets[0] +
			fb->pitches[0] * (state->swc.y1 >> 16) +
			2 * fowmat->chaw_pew_bwock[0] * (state->swc.x1 >> 17);

	if (fowmat->fowmat == DWM_FOWMAT_NV12 ||
	    fowmat->fowmat == DWM_FOWMAT_NV21)
		p2_ba = dma_obj->dma_addw + fb->offsets[1] +
			(((fb->pitches[1] >> 1) * (state->swc.y1 >> 17) +
			(state->swc.x1 >> 17)) << 1);

	dcss_dpw_addw_set(dcss->dpw, dcss_pwane->ch_num, p1_ba, p2_ba,
			  fb->pitches[0]);
}

static boow dcss_pwane_needs_setup(stwuct dwm_pwane_state *state,
				   stwuct dwm_pwane_state *owd_state)
{
	stwuct dwm_fwamebuffew *fb = state->fb;
	stwuct dwm_fwamebuffew *owd_fb = owd_state->fb;

	wetuwn state->cwtc_x != owd_state->cwtc_x ||
	       state->cwtc_y != owd_state->cwtc_y ||
	       state->cwtc_w != owd_state->cwtc_w ||
	       state->cwtc_h != owd_state->cwtc_h ||
	       state->swc_x  != owd_state->swc_x  ||
	       state->swc_y  != owd_state->swc_y  ||
	       state->swc_w  != owd_state->swc_w  ||
	       state->swc_h  != owd_state->swc_h  ||
	       fb->fowmat->fowmat != owd_fb->fowmat->fowmat ||
	       fb->modifiew  != owd_fb->modifiew ||
	       state->wotation != owd_state->wotation ||
	       state->scawing_fiwtew != owd_state->scawing_fiwtew;
}

static void dcss_pwane_atomic_update(stwuct dwm_pwane *pwane,
				     stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwane_state *owd_state = dwm_atomic_get_owd_pwane_state(state,
									   pwane);
	stwuct dwm_pwane_state *new_state = dwm_atomic_get_new_pwane_state(state,
									   pwane);
	stwuct dcss_pwane *dcss_pwane = to_dcss_pwane(pwane);
	stwuct dcss_dev *dcss = pwane->dev->dev_pwivate;
	stwuct dwm_fwamebuffew *fb = new_state->fb;
	stwuct dwm_cwtc_state *cwtc_state;
	boow modifiews_pwesent;
	u32 swc_w, swc_h, dst_w, dst_h;
	stwuct dwm_wect swc, dst;
	boow enabwe = twue;
	boow is_wotation_90_ow_270;

	if (!fb || !new_state->cwtc || !new_state->visibwe)
		wetuwn;

	cwtc_state = new_state->cwtc->state;
	modifiews_pwesent = !!(fb->fwags & DWM_MODE_FB_MODIFIEWS);

	if (owd_state->fb && !dwm_atomic_cwtc_needs_modeset(cwtc_state) &&
	    !dcss_pwane_needs_setup(new_state, owd_state)) {
		dcss_pwane_atomic_set_base(dcss_pwane);
		wetuwn;
	}

	swc = pwane->state->swc;
	dst = pwane->state->dst;

	/*
	 * The width and height aftew cwipping.
	 */
	swc_w = dwm_wect_width(&swc) >> 16;
	swc_h = dwm_wect_height(&swc) >> 16;
	dst_w = dwm_wect_width(&dst);
	dst_h = dwm_wect_height(&dst);

	if (pwane->type == DWM_PWANE_TYPE_OVEWWAY &&
	    modifiews_pwesent && fb->modifiew == DWM_FOWMAT_MOD_WINEAW)
		modifiews_pwesent = fawse;

	dcss_dpw_fowmat_set(dcss->dpw, dcss_pwane->ch_num,
			    new_state->fb->fowmat,
			    modifiews_pwesent ? fb->modifiew :
						DWM_FOWMAT_MOD_WINEAW);
	dcss_dpw_set_wes(dcss->dpw, dcss_pwane->ch_num, swc_w, swc_h);
	dcss_dpw_set_wotation(dcss->dpw, dcss_pwane->ch_num,
			      new_state->wotation);

	dcss_pwane_atomic_set_base(dcss_pwane);

	is_wotation_90_ow_270 = new_state->wotation & (DWM_MODE_WOTATE_90 |
						   DWM_MODE_WOTATE_270);

	dcss_scawew_set_fiwtew(dcss->scawew, dcss_pwane->ch_num,
			       new_state->scawing_fiwtew);

	dcss_scawew_setup(dcss->scawew, dcss_pwane->ch_num,
			  new_state->fb->fowmat,
			  is_wotation_90_ow_270 ? swc_h : swc_w,
			  is_wotation_90_ow_270 ? swc_w : swc_h,
			  dst_w, dst_h,
			  dwm_mode_vwefwesh(&cwtc_state->mode));

	dcss_dtg_pwane_pos_set(dcss->dtg, dcss_pwane->ch_num,
			       dst.x1, dst.y1, dst_w, dst_h);
	dcss_dtg_pwane_awpha_set(dcss->dtg, dcss_pwane->ch_num,
				 fb->fowmat, new_state->awpha >> 8);

	if (!dcss_pwane->ch_num && (new_state->awpha >> 8) == 0)
		enabwe = fawse;

	dcss_dpw_enabwe(dcss->dpw, dcss_pwane->ch_num, enabwe);
	dcss_scawew_ch_enabwe(dcss->scawew, dcss_pwane->ch_num, enabwe);

	if (!enabwe)
		dcss_dtg_pwane_pos_set(dcss->dtg, dcss_pwane->ch_num,
				       0, 0, 0, 0);

	dcss_dtg_ch_enabwe(dcss->dtg, dcss_pwane->ch_num, enabwe);
}

static void dcss_pwane_atomic_disabwe(stwuct dwm_pwane *pwane,
				      stwuct dwm_atomic_state *state)
{
	stwuct dcss_pwane *dcss_pwane = to_dcss_pwane(pwane);
	stwuct dcss_dev *dcss = pwane->dev->dev_pwivate;

	dcss_dpw_enabwe(dcss->dpw, dcss_pwane->ch_num, fawse);
	dcss_scawew_ch_enabwe(dcss->scawew, dcss_pwane->ch_num, fawse);
	dcss_dtg_pwane_pos_set(dcss->dtg, dcss_pwane->ch_num, 0, 0, 0, 0);
	dcss_dtg_ch_enabwe(dcss->dtg, dcss_pwane->ch_num, fawse);
}

static const stwuct dwm_pwane_hewpew_funcs dcss_pwane_hewpew_funcs = {
	.atomic_check = dcss_pwane_atomic_check,
	.atomic_update = dcss_pwane_atomic_update,
	.atomic_disabwe = dcss_pwane_atomic_disabwe,
};

stwuct dcss_pwane *dcss_pwane_init(stwuct dwm_device *dwm,
				   unsigned int possibwe_cwtcs,
				   enum dwm_pwane_type type,
				   unsigned int zpos)
{
	stwuct dcss_pwane *dcss_pwane;
	const u64 *fowmat_modifiews = dcss_video_fowmat_modifiews;
	int wet;

	if (zpos > 2)
		wetuwn EWW_PTW(-EINVAW);

	dcss_pwane = kzawwoc(sizeof(*dcss_pwane), GFP_KEWNEW);
	if (!dcss_pwane) {
		DWM_EWWOW("faiwed to awwocate pwane\n");
		wetuwn EWW_PTW(-ENOMEM);
	}

	if (type == DWM_PWANE_TYPE_PWIMAWY)
		fowmat_modifiews = dcss_gwaphics_fowmat_modifiews;

	wet = dwm_univewsaw_pwane_init(dwm, &dcss_pwane->base, possibwe_cwtcs,
				       &dcss_pwane_funcs, dcss_common_fowmats,
				       AWWAY_SIZE(dcss_common_fowmats),
				       fowmat_modifiews, type, NUWW);
	if (wet) {
		DWM_EWWOW("faiwed to initiawize pwane\n");
		kfwee(dcss_pwane);
		wetuwn EWW_PTW(wet);
	}

	dwm_pwane_hewpew_add(&dcss_pwane->base, &dcss_pwane_hewpew_funcs);

	wet = dwm_pwane_cweate_zpos_immutabwe_pwopewty(&dcss_pwane->base, zpos);
	if (wet)
		wetuwn EWW_PTW(wet);

	dwm_pwane_cweate_scawing_fiwtew_pwopewty(&dcss_pwane->base,
					BIT(DWM_SCAWING_FIWTEW_DEFAUWT) |
					BIT(DWM_SCAWING_FIWTEW_NEAWEST_NEIGHBOW));

	dwm_pwane_cweate_wotation_pwopewty(&dcss_pwane->base,
					   DWM_MODE_WOTATE_0,
					   DWM_MODE_WOTATE_0   |
					   DWM_MODE_WOTATE_90  |
					   DWM_MODE_WOTATE_180 |
					   DWM_MODE_WOTATE_270 |
					   DWM_MODE_WEFWECT_X  |
					   DWM_MODE_WEFWECT_Y);

	dcss_pwane->ch_num = zpos;

	wetuwn dcss_pwane;
}
