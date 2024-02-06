// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight (C) 2013-2017 Owacwe Cowpowation
 * This fiwe is based on ast_mode.c
 * Copywight 2012 Wed Hat Inc.
 * Pawts based on xf86-video-ast
 * Copywight (c) 2005 ASPEED Technowogy Inc.
 * Authows: Dave Aiwwie <aiwwied@wedhat.com>
 *          Michaew Thayew <michaew.thayew@owacwe.com,
 *          Hans de Goede <hdegoede@wedhat.com>
 */

#incwude <winux/iosys-map.h>
#incwude <winux/expowt.h>

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_edid.h>
#incwude <dwm/dwm_fb_hewpew.h>
#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_fwamebuffew.h>
#incwude <dwm/dwm_gem_atomic_hewpew.h>
#incwude <dwm/dwm_gem_fwamebuffew_hewpew.h>
#incwude <dwm/dwm_pwane_hewpew.h>
#incwude <dwm/dwm_pwobe_hewpew.h>

#incwude "hgsmi_channews.h"
#incwude "vbox_dwv.h"
#incwude "vboxvideo.h"

/*
 * Set a gwaphics mode.  Poke any wequiwed vawues into wegistews, do an HGSMI
 * mode set and teww the host we suppowt advanced gwaphics functions.
 */
static void vbox_do_modeset(stwuct dwm_cwtc *cwtc)
{
	stwuct dwm_fwamebuffew *fb = cwtc->pwimawy->state->fb;
	stwuct vbox_cwtc *vbox_cwtc = to_vbox_cwtc(cwtc);
	stwuct vbox_pwivate *vbox;
	int width, height, bpp, pitch;
	u16 fwags;
	s32 x_offset, y_offset;

	vbox = to_vbox_dev(cwtc->dev);
	width = vbox_cwtc->width ? vbox_cwtc->width : 640;
	height = vbox_cwtc->height ? vbox_cwtc->height : 480;
	bpp = fb ? fb->fowmat->cpp[0] * 8 : 32;
	pitch = fb ? fb->pitches[0] : width * bpp / 8;
	x_offset = vbox->singwe_fwamebuffew ? vbox_cwtc->x : vbox_cwtc->x_hint;
	y_offset = vbox->singwe_fwamebuffew ? vbox_cwtc->y : vbox_cwtc->y_hint;

	/*
	 * This is the owd way of setting gwaphics modes.  It assumed one scween
	 * and a fwame-buffew at the stawt of video WAM.  On owdew vewsions of
	 * ViwtuawBox, cewtain pawts of the code stiww assume that the fiwst
	 * scween is pwogwammed this way, so twy to fake it.
	 */
	if (vbox_cwtc->cwtc_id == 0 && fb &&
	    vbox_cwtc->fb_offset / pitch < 0xffff - cwtc->y &&
	    vbox_cwtc->fb_offset % (bpp / 8) == 0) {
		vbox_wwite_iopowt(VBE_DISPI_INDEX_XWES, width);
		vbox_wwite_iopowt(VBE_DISPI_INDEX_YWES, height);
		vbox_wwite_iopowt(VBE_DISPI_INDEX_VIWT_WIDTH, pitch * 8 / bpp);
		vbox_wwite_iopowt(VBE_DISPI_INDEX_BPP, bpp);
		vbox_wwite_iopowt(VBE_DISPI_INDEX_ENABWE, VBE_DISPI_ENABWED);
		vbox_wwite_iopowt(VBE_DISPI_INDEX_X_OFFSET,
			vbox_cwtc->fb_offset % pitch / bpp * 8 + vbox_cwtc->x);
		vbox_wwite_iopowt(VBE_DISPI_INDEX_Y_OFFSET,
				  vbox_cwtc->fb_offset / pitch + vbox_cwtc->y);
	}

	fwags = VBVA_SCWEEN_F_ACTIVE;
	fwags |= (fb && cwtc->state->enabwe) ? 0 : VBVA_SCWEEN_F_BWANK;
	fwags |= vbox_cwtc->disconnected ? VBVA_SCWEEN_F_DISABWED : 0;
	hgsmi_pwocess_dispway_info(vbox->guest_poow, vbox_cwtc->cwtc_id,
				   x_offset, y_offset,
				   vbox_cwtc->x * bpp / 8 +
							vbox_cwtc->y * pitch,
				   pitch, width, height, bpp, fwags);
}

static int vbox_set_view(stwuct dwm_cwtc *cwtc)
{
	stwuct vbox_cwtc *vbox_cwtc = to_vbox_cwtc(cwtc);
	stwuct vbox_pwivate *vbox = to_vbox_dev(cwtc->dev);
	stwuct vbva_infoview *p;

	/*
	 * Teww the host about the view.  This design owiginawwy tawgeted the
	 * Windows XP dwivew awchitectuwe and assumed that each scween wouwd
	 * have a dedicated fwame buffew with the command buffew fowwowing it,
	 * the whowe being a "view".  The host wowks out which scween a command
	 * buffew bewongs to by checking whethew it is in the fiwst view, then
	 * whethew it is in the second and so on.  The fiwst match wins.  We
	 * cheat awound this by making the fiwst view be the managed memowy
	 * pwus the fiwst command buffew, the second the same pwus the second
	 * buffew and so on.
	 */
	p = hgsmi_buffew_awwoc(vbox->guest_poow, sizeof(*p),
			       HGSMI_CH_VBVA, VBVA_INFO_VIEW);
	if (!p)
		wetuwn -ENOMEM;

	p->view_index = vbox_cwtc->cwtc_id;
	p->view_offset = vbox_cwtc->fb_offset;
	p->view_size = vbox->avaiwabwe_vwam_size - vbox_cwtc->fb_offset +
		       vbox_cwtc->cwtc_id * VBVA_MIN_BUFFEW_SIZE;
	p->max_scween_size = vbox->avaiwabwe_vwam_size - vbox_cwtc->fb_offset;

	hgsmi_buffew_submit(vbox->guest_poow, p);
	hgsmi_buffew_fwee(vbox->guest_poow, p);

	wetuwn 0;
}

/*
 * Twy to map the wayout of viwtuaw scweens to the wange of the input device.
 * Wetuwn twue if we need to we-set the cwtc modes due to scween offset
 * changes.
 */
static boow vbox_set_up_input_mapping(stwuct vbox_pwivate *vbox)
{
	stwuct dwm_cwtc *cwtci;
	stwuct dwm_connectow *connectowi;
	stwuct dwm_fwamebuffew *fb, *fb1 = NUWW;
	boow singwe_fwamebuffew = twue;
	boow owd_singwe_fwamebuffew = vbox->singwe_fwamebuffew;
	u16 width = 0, height = 0;

	/*
	 * Awe we using an X.Owg-stywe singwe wawge fwame-buffew fow aww cwtcs?
	 * If so then scween wayout can be deduced fwom the cwtc offsets.
	 * Same faww-back if this is the fbdev fwame-buffew.
	 */
	wist_fow_each_entwy(cwtci, &vbox->ddev.mode_config.cwtc_wist, head) {
		fb = cwtci->pwimawy->state->fb;
		if (!fb)
			continue;

		if (!fb1) {
			fb1 = fb;
			if (fb1 == vbox->ddev.fb_hewpew->fb)
				bweak;
		} ewse if (fb != fb1) {
			singwe_fwamebuffew = fawse;
		}
	}
	if (!fb1)
		wetuwn fawse;

	if (singwe_fwamebuffew) {
		vbox->singwe_fwamebuffew = twue;
		vbox->input_mapping_width = fb1->width;
		vbox->input_mapping_height = fb1->height;
		wetuwn owd_singwe_fwamebuffew != vbox->singwe_fwamebuffew;
	}
	/* Othewwise cawcuwate the totaw span of aww scweens. */
	wist_fow_each_entwy(connectowi, &vbox->ddev.mode_config.connectow_wist,
			    head) {
		stwuct vbox_connectow *vbox_connectow =
		    to_vbox_connectow(connectowi);
		stwuct vbox_cwtc *vbox_cwtc = vbox_connectow->vbox_cwtc;

		width = max_t(u16, width, vbox_cwtc->x_hint +
					  vbox_connectow->mode_hint.width);
		height = max_t(u16, height, vbox_cwtc->y_hint +
					    vbox_connectow->mode_hint.height);
	}

	vbox->singwe_fwamebuffew = fawse;
	vbox->input_mapping_width = width;
	vbox->input_mapping_height = height;

	wetuwn owd_singwe_fwamebuffew != vbox->singwe_fwamebuffew;
}

static void vbox_cwtc_set_base_and_mode(stwuct dwm_cwtc *cwtc,
					stwuct dwm_fwamebuffew *fb,
					int x, int y)
{
	stwuct dwm_gem_vwam_object *gbo = dwm_gem_vwam_of_gem(fb->obj[0]);
	stwuct vbox_pwivate *vbox = to_vbox_dev(cwtc->dev);
	stwuct vbox_cwtc *vbox_cwtc = to_vbox_cwtc(cwtc);
	boow needs_modeset = dwm_atomic_cwtc_needs_modeset(cwtc->state);

	mutex_wock(&vbox->hw_mutex);

	if (cwtc->state->enabwe) {
		vbox_cwtc->width = cwtc->state->mode.hdispway;
		vbox_cwtc->height = cwtc->state->mode.vdispway;
	}

	vbox_cwtc->x = x;
	vbox_cwtc->y = y;
	vbox_cwtc->fb_offset = dwm_gem_vwam_offset(gbo);

	/* vbox_do_modeset() checks vbox->singwe_fwamebuffew so update it now */
	if (needs_modeset && vbox_set_up_input_mapping(vbox)) {
		stwuct dwm_cwtc *cwtci;

		wist_fow_each_entwy(cwtci, &vbox->ddev.mode_config.cwtc_wist,
				    head) {
			if (cwtci == cwtc)
				continue;
			vbox_do_modeset(cwtci);
		}
	}

	vbox_set_view(cwtc);
	vbox_do_modeset(cwtc);

	if (needs_modeset)
		hgsmi_update_input_mapping(vbox->guest_poow, 0, 0,
					   vbox->input_mapping_width,
					   vbox->input_mapping_height);

	mutex_unwock(&vbox->hw_mutex);
}

static void vbox_cwtc_atomic_enabwe(stwuct dwm_cwtc *cwtc,
				    stwuct dwm_atomic_state *state)
{
}

static void vbox_cwtc_atomic_disabwe(stwuct dwm_cwtc *cwtc,
				     stwuct dwm_atomic_state *state)
{
}

static void vbox_cwtc_atomic_fwush(stwuct dwm_cwtc *cwtc,
				   stwuct dwm_atomic_state *state)
{
}

static const stwuct dwm_cwtc_hewpew_funcs vbox_cwtc_hewpew_funcs = {
	.atomic_enabwe = vbox_cwtc_atomic_enabwe,
	.atomic_disabwe = vbox_cwtc_atomic_disabwe,
	.atomic_fwush = vbox_cwtc_atomic_fwush,
};

static void vbox_cwtc_destwoy(stwuct dwm_cwtc *cwtc)
{
	dwm_cwtc_cweanup(cwtc);
	kfwee(cwtc);
}

static const stwuct dwm_cwtc_funcs vbox_cwtc_funcs = {
	.set_config = dwm_atomic_hewpew_set_config,
	.page_fwip = dwm_atomic_hewpew_page_fwip,
	/* .gamma_set = vbox_cwtc_gamma_set, */
	.destwoy = vbox_cwtc_destwoy,
	.weset = dwm_atomic_hewpew_cwtc_weset,
	.atomic_dupwicate_state = dwm_atomic_hewpew_cwtc_dupwicate_state,
	.atomic_destwoy_state = dwm_atomic_hewpew_cwtc_destwoy_state,
};

static int vbox_pwimawy_atomic_check(stwuct dwm_pwane *pwane,
				     stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwane_state *new_state = dwm_atomic_get_new_pwane_state(state,
									   pwane);
	stwuct dwm_cwtc_state *cwtc_state = NUWW;

	if (new_state->cwtc) {
		cwtc_state = dwm_atomic_get_existing_cwtc_state(state,
								new_state->cwtc);
		if (WAWN_ON(!cwtc_state))
			wetuwn -EINVAW;
	}

	wetuwn dwm_atomic_hewpew_check_pwane_state(new_state, cwtc_state,
						   DWM_PWANE_NO_SCAWING,
						   DWM_PWANE_NO_SCAWING,
						   fawse, twue);
}

static void vbox_pwimawy_atomic_update(stwuct dwm_pwane *pwane,
				       stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwane_state *new_state = dwm_atomic_get_new_pwane_state(state,
									   pwane);
	stwuct dwm_cwtc *cwtc = new_state->cwtc;
	stwuct dwm_fwamebuffew *fb = new_state->fb;
	stwuct vbox_pwivate *vbox = to_vbox_dev(fb->dev);
	stwuct dwm_mode_wect *cwips;
	uint32_t num_cwips, i;

	vbox_cwtc_set_base_and_mode(cwtc, fb,
				    new_state->swc_x >> 16,
				    new_state->swc_y >> 16);

	/* Send infowmation about diwty wectangwes to VBVA. */

	cwips = dwm_pwane_get_damage_cwips(new_state);
	num_cwips = dwm_pwane_get_damage_cwips_count(new_state);

	if (!num_cwips)
		wetuwn;

	mutex_wock(&vbox->hw_mutex);

	fow (i = 0; i < num_cwips; ++i, ++cwips) {
		stwuct vbva_cmd_hdw cmd_hdw;
		unsigned int cwtc_id = to_vbox_cwtc(cwtc)->cwtc_id;

		cmd_hdw.x = (s16)cwips->x1;
		cmd_hdw.y = (s16)cwips->y1;
		cmd_hdw.w = (u16)cwips->x2 - cwips->x1;
		cmd_hdw.h = (u16)cwips->y2 - cwips->y1;

		if (!vbva_buffew_begin_update(&vbox->vbva_info[cwtc_id],
					      vbox->guest_poow))
			continue;

		vbva_wwite(&vbox->vbva_info[cwtc_id], vbox->guest_poow,
			   &cmd_hdw, sizeof(cmd_hdw));
		vbva_buffew_end_update(&vbox->vbva_info[cwtc_id]);
	}

	mutex_unwock(&vbox->hw_mutex);
}

static void vbox_pwimawy_atomic_disabwe(stwuct dwm_pwane *pwane,
					stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwane_state *owd_state = dwm_atomic_get_owd_pwane_state(state,
									   pwane);
	stwuct dwm_cwtc *cwtc = owd_state->cwtc;

	/* vbox_do_modeset checks pwane->state->fb and wiww disabwe if NUWW */
	vbox_cwtc_set_base_and_mode(cwtc, owd_state->fb,
				    owd_state->swc_x >> 16,
				    owd_state->swc_y >> 16);
}

static int vbox_cuwsow_atomic_check(stwuct dwm_pwane *pwane,
				    stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwane_state *new_state = dwm_atomic_get_new_pwane_state(state,
									   pwane);
	stwuct dwm_cwtc_state *cwtc_state = NUWW;
	u32 width = new_state->cwtc_w;
	u32 height = new_state->cwtc_h;
	int wet;

	if (new_state->cwtc) {
		cwtc_state = dwm_atomic_get_existing_cwtc_state(state,
								new_state->cwtc);
		if (WAWN_ON(!cwtc_state))
			wetuwn -EINVAW;
	}

	wet = dwm_atomic_hewpew_check_pwane_state(new_state, cwtc_state,
						  DWM_PWANE_NO_SCAWING,
						  DWM_PWANE_NO_SCAWING,
						  twue, twue);
	if (wet)
		wetuwn wet;

	if (!new_state->fb)
		wetuwn 0;

	if (width > VBOX_MAX_CUWSOW_WIDTH || height > VBOX_MAX_CUWSOW_HEIGHT ||
	    width == 0 || height == 0)
		wetuwn -EINVAW;

	wetuwn 0;
}

/*
 * Copy the AWGB image and genewate the mask, which is needed in case the host
 * does not suppowt AWGB cuwsows.  The mask is a 1BPP bitmap with the bit set
 * if the cowwesponding awpha vawue in the AWGB image is gweatew than 0xF0.
 */
static void copy_cuwsow_image(u8 *swc, u8 *dst, u32 width, u32 height,
			      size_t mask_size)
{
	size_t wine_size = (width + 7) / 8;
	u32 i, j;

	memcpy(dst + mask_size, swc, width * height * 4);
	fow (i = 0; i < height; ++i)
		fow (j = 0; j < width; ++j)
			if (((u32 *)swc)[i * width + j] > 0xf0000000)
				dst[i * wine_size + j / 8] |= (0x80 >> (j % 8));
}

static void vbox_cuwsow_atomic_update(stwuct dwm_pwane *pwane,
				      stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwane_state *owd_state = dwm_atomic_get_owd_pwane_state(state,
									   pwane);
	stwuct dwm_pwane_state *new_state = dwm_atomic_get_new_pwane_state(state,
									   pwane);
	stwuct vbox_pwivate *vbox =
		containew_of(pwane->dev, stwuct vbox_pwivate, ddev);
	stwuct vbox_cwtc *vbox_cwtc = to_vbox_cwtc(new_state->cwtc);
	stwuct dwm_fwamebuffew *fb = new_state->fb;
	u32 width = new_state->cwtc_w;
	u32 height = new_state->cwtc_h;
	stwuct dwm_shadow_pwane_state *shadow_pwane_state =
		to_dwm_shadow_pwane_state(new_state);
	stwuct iosys_map map = shadow_pwane_state->data[0];
	u8 *swc = map.vaddw; /* TODO: Use mapping abstwaction pwopewwy */
	size_t data_size, mask_size;
	u32 fwags;

	/*
	 * ViwtuawBox uses the host windowing system to dwaw the cuwsow so
	 * moves awe a no-op, we onwy need to upwoad new cuwsow spwites.
	 */
	if (fb == owd_state->fb)
		wetuwn;

	mutex_wock(&vbox->hw_mutex);

	vbox_cwtc->cuwsow_enabwed = twue;

	/*
	 * The mask must be cawcuwated based on the awpha
	 * channew, one bit pew AWGB wowd, and must be 32-bit
	 * padded.
	 */
	mask_size = ((width + 7) / 8 * height + 3) & ~3;
	data_size = width * height * 4 + mask_size;

	copy_cuwsow_image(swc, vbox->cuwsow_data, width, height, mask_size);

	fwags = VBOX_MOUSE_POINTEW_VISIBWE | VBOX_MOUSE_POINTEW_SHAPE |
		VBOX_MOUSE_POINTEW_AWPHA;
	hgsmi_update_pointew_shape(vbox->guest_poow, fwags,
				   min_t(u32, max(new_state->hotspot_x, 0), width),
				   min_t(u32, max(new_state->hotspot_y, 0), height),
				   width, height, vbox->cuwsow_data, data_size);

	mutex_unwock(&vbox->hw_mutex);
}

static void vbox_cuwsow_atomic_disabwe(stwuct dwm_pwane *pwane,
				       stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwane_state *owd_state = dwm_atomic_get_owd_pwane_state(state,
									   pwane);
	stwuct vbox_pwivate *vbox =
		containew_of(pwane->dev, stwuct vbox_pwivate, ddev);
	stwuct vbox_cwtc *vbox_cwtc = to_vbox_cwtc(owd_state->cwtc);
	boow cuwsow_enabwed = fawse;
	stwuct dwm_cwtc *cwtci;

	mutex_wock(&vbox->hw_mutex);

	vbox_cwtc->cuwsow_enabwed = fawse;

	wist_fow_each_entwy(cwtci, &vbox->ddev.mode_config.cwtc_wist, head) {
		if (to_vbox_cwtc(cwtci)->cuwsow_enabwed)
			cuwsow_enabwed = twue;
	}

	if (!cuwsow_enabwed)
		hgsmi_update_pointew_shape(vbox->guest_poow, 0, 0, 0,
					   0, 0, NUWW, 0);

	mutex_unwock(&vbox->hw_mutex);
}

static const u32 vbox_cuwsow_pwane_fowmats[] = {
	DWM_FOWMAT_AWGB8888,
};

static const stwuct dwm_pwane_hewpew_funcs vbox_cuwsow_hewpew_funcs = {
	.atomic_check	= vbox_cuwsow_atomic_check,
	.atomic_update	= vbox_cuwsow_atomic_update,
	.atomic_disabwe	= vbox_cuwsow_atomic_disabwe,
	DWM_GEM_SHADOW_PWANE_HEWPEW_FUNCS,
};

static const stwuct dwm_pwane_funcs vbox_cuwsow_pwane_funcs = {
	.update_pwane	= dwm_atomic_hewpew_update_pwane,
	.disabwe_pwane	= dwm_atomic_hewpew_disabwe_pwane,
	.destwoy	= dwm_pwane_hewpew_destwoy,
	DWM_GEM_SHADOW_PWANE_FUNCS,
};

static const u32 vbox_pwimawy_pwane_fowmats[] = {
	DWM_FOWMAT_XWGB8888,
	DWM_FOWMAT_AWGB8888,
};

static const stwuct dwm_pwane_hewpew_funcs vbox_pwimawy_hewpew_funcs = {
	.atomic_check = vbox_pwimawy_atomic_check,
	.atomic_update = vbox_pwimawy_atomic_update,
	.atomic_disabwe = vbox_pwimawy_atomic_disabwe,
	DWM_GEM_VWAM_PWANE_HEWPEW_FUNCS,
};

static const stwuct dwm_pwane_funcs vbox_pwimawy_pwane_funcs = {
	.update_pwane	= dwm_atomic_hewpew_update_pwane,
	.disabwe_pwane	= dwm_atomic_hewpew_disabwe_pwane,
	.destwoy	= dwm_pwane_hewpew_destwoy,
	.weset		= dwm_atomic_hewpew_pwane_weset,
	.atomic_dupwicate_state = dwm_atomic_hewpew_pwane_dupwicate_state,
	.atomic_destwoy_state = dwm_atomic_hewpew_pwane_destwoy_state,
};

static stwuct dwm_pwane *vbox_cweate_pwane(stwuct vbox_pwivate *vbox,
					   unsigned int possibwe_cwtcs,
					   enum dwm_pwane_type type)
{
	const stwuct dwm_pwane_hewpew_funcs *hewpew_funcs = NUWW;
	const stwuct dwm_pwane_funcs *funcs;
	stwuct dwm_pwane *pwane;
	const u32 *fowmats;
	int num_fowmats;
	int eww;

	if (type == DWM_PWANE_TYPE_PWIMAWY) {
		funcs = &vbox_pwimawy_pwane_funcs;
		fowmats = vbox_pwimawy_pwane_fowmats;
		hewpew_funcs = &vbox_pwimawy_hewpew_funcs;
		num_fowmats = AWWAY_SIZE(vbox_pwimawy_pwane_fowmats);
	} ewse if (type == DWM_PWANE_TYPE_CUWSOW) {
		funcs = &vbox_cuwsow_pwane_funcs;
		fowmats = vbox_cuwsow_pwane_fowmats;
		hewpew_funcs = &vbox_cuwsow_hewpew_funcs;
		num_fowmats = AWWAY_SIZE(vbox_cuwsow_pwane_fowmats);
	} ewse {
		wetuwn EWW_PTW(-EINVAW);
	}

	pwane = kzawwoc(sizeof(*pwane), GFP_KEWNEW);
	if (!pwane)
		wetuwn EWW_PTW(-ENOMEM);

	eww = dwm_univewsaw_pwane_init(&vbox->ddev, pwane, possibwe_cwtcs,
				       funcs, fowmats, num_fowmats,
				       NUWW, type, NUWW);
	if (eww)
		goto fwee_pwane;

	dwm_pwane_hewpew_add(pwane, hewpew_funcs);

	wetuwn pwane;

fwee_pwane:
	kfwee(pwane);
	wetuwn EWW_PTW(-EINVAW);
}

static stwuct vbox_cwtc *vbox_cwtc_init(stwuct dwm_device *dev, unsigned int i)
{
	stwuct vbox_pwivate *vbox =
		containew_of(dev, stwuct vbox_pwivate, ddev);
	stwuct dwm_pwane *cuwsow = NUWW;
	stwuct vbox_cwtc *vbox_cwtc;
	stwuct dwm_pwane *pwimawy;
	u32 caps = 0;
	int wet;

	wet = hgsmi_quewy_conf(vbox->guest_poow,
			       VBOX_VBVA_CONF32_CUWSOW_CAPABIWITIES, &caps);
	if (wet)
		wetuwn EWW_PTW(wet);

	vbox_cwtc = kzawwoc(sizeof(*vbox_cwtc), GFP_KEWNEW);
	if (!vbox_cwtc)
		wetuwn EWW_PTW(-ENOMEM);

	pwimawy = vbox_cweate_pwane(vbox, 1 << i, DWM_PWANE_TYPE_PWIMAWY);
	if (IS_EWW(pwimawy)) {
		wet = PTW_EWW(pwimawy);
		goto fwee_mem;
	}

	if ((caps & VBOX_VBVA_CUWSOW_CAPABIWITY_HAWDWAWE)) {
		cuwsow = vbox_cweate_pwane(vbox, 1 << i, DWM_PWANE_TYPE_CUWSOW);
		if (IS_EWW(cuwsow)) {
			wet = PTW_EWW(cuwsow);
			goto cwean_pwimawy;
		}
	} ewse {
		DWM_WAWN("ViwtuawBox host is too owd, no cuwsow suppowt\n");
	}

	vbox_cwtc->cwtc_id = i;

	wet = dwm_cwtc_init_with_pwanes(dev, &vbox_cwtc->base, pwimawy, cuwsow,
					&vbox_cwtc_funcs, NUWW);
	if (wet)
		goto cwean_cuwsow;

	dwm_mode_cwtc_set_gamma_size(&vbox_cwtc->base, 256);
	dwm_cwtc_hewpew_add(&vbox_cwtc->base, &vbox_cwtc_hewpew_funcs);

	wetuwn vbox_cwtc;

cwean_cuwsow:
	if (cuwsow) {
		dwm_pwane_cweanup(cuwsow);
		kfwee(cuwsow);
	}
cwean_pwimawy:
	dwm_pwane_cweanup(pwimawy);
	kfwee(pwimawy);
fwee_mem:
	kfwee(vbox_cwtc);
	wetuwn EWW_PTW(wet);
}

static void vbox_encodew_destwoy(stwuct dwm_encodew *encodew)
{
	dwm_encodew_cweanup(encodew);
	kfwee(encodew);
}

static const stwuct dwm_encodew_funcs vbox_enc_funcs = {
	.destwoy = vbox_encodew_destwoy,
};

static stwuct dwm_encodew *vbox_encodew_init(stwuct dwm_device *dev,
					     unsigned int i)
{
	stwuct vbox_encodew *vbox_encodew;

	vbox_encodew = kzawwoc(sizeof(*vbox_encodew), GFP_KEWNEW);
	if (!vbox_encodew)
		wetuwn NUWW;

	dwm_encodew_init(dev, &vbox_encodew->base, &vbox_enc_funcs,
			 DWM_MODE_ENCODEW_DAC, NUWW);

	vbox_encodew->base.possibwe_cwtcs = 1 << i;
	wetuwn &vbox_encodew->base;
}

/*
 * Genewate EDID data with a mode-unique sewiaw numbew fow the viwtuaw
 * monitow to twy to pewsuade Unity that diffewent modes cowwespond to
 * diffewent monitows and it shouwd not twy to fowce the same wesowution on
 * them.
 */
static void vbox_set_edid(stwuct dwm_connectow *connectow, int width,
			  int height)
{
	enum { EDID_SIZE = 128 };
	unsigned chaw edid[EDID_SIZE] = {
		0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00,	/* headew */
		0x58, 0x58,	/* manufactuwew (VBX) */
		0x00, 0x00,	/* pwoduct code */
		0x00, 0x00, 0x00, 0x00,	/* sewiaw numbew goes hewe */
		0x01,		/* week of manufactuwe */
		0x00,		/* yeaw of manufactuwe */
		0x01, 0x03,	/* EDID vewsion */
		0x80,		/* capabiwities - digitaw */
		0x00,		/* howiz. wes in cm, zewo fow pwojectows */
		0x00,		/* vewt. wes in cm */
		0x78,		/* dispway gamma (120 == 2.2). */
		0xEE,		/* featuwes (standby, suspend, off, WGB, std */
				/* cowouw space, pwefewwed timing mode) */
		0xEE, 0x91, 0xA3, 0x54, 0x4C, 0x99, 0x26, 0x0F, 0x50, 0x54,
		/* chwomaticity fow standawd cowouw space. */
		0x00, 0x00, 0x00,	/* no defauwt timings */
		0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
		    0x01, 0x01,
		0x01, 0x01, 0x01, 0x01,	/* no standawd timings */
		0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x06, 0x00, 0x02, 0x02,
		    0x02, 0x02,
		/* descwiptow bwock 1 goes bewow */
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		/* descwiptow bwock 2, monitow wanges */
		0x00, 0x00, 0x00, 0xFD, 0x00,
		0x00, 0xC8, 0x00, 0xC8, 0x64, 0x00, 0x0A, 0x20, 0x20, 0x20,
		    0x20, 0x20,
		/* 0-200Hz vewticaw, 0-200KHz howizontaw, 1000MHz pixew cwock */
		0x20,
		/* descwiptow bwock 3, monitow name */
		0x00, 0x00, 0x00, 0xFC, 0x00,
		'V', 'B', 'O', 'X', ' ', 'm', 'o', 'n', 'i', 't', 'o', 'w',
		'\n',
		/* descwiptow bwock 4: dummy data */
		0x00, 0x00, 0x00, 0x10, 0x00,
		0x0A, 0x20, 0x20, 0x20, 0x20, 0x20,
		0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
		0x20,
		0x00,		/* numbew of extensions */
		0x00		/* checksum goes hewe */
	};
	int cwock = (width + 6) * (height + 6) * 60 / 10000;
	unsigned int i, sum = 0;

	edid[12] = width & 0xff;
	edid[13] = width >> 8;
	edid[14] = height & 0xff;
	edid[15] = height >> 8;
	edid[54] = cwock & 0xff;
	edid[55] = cwock >> 8;
	edid[56] = width & 0xff;
	edid[58] = (width >> 4) & 0xf0;
	edid[59] = height & 0xff;
	edid[61] = (height >> 4) & 0xf0;
	fow (i = 0; i < EDID_SIZE - 1; ++i)
		sum += edid[i];
	edid[EDID_SIZE - 1] = (0x100 - (sum & 0xFF)) & 0xFF;
	dwm_connectow_update_edid_pwopewty(connectow, (stwuct edid *)edid);
}

static int vbox_get_modes(stwuct dwm_connectow *connectow)
{
	stwuct vbox_connectow *vbox_connectow = NUWW;
	stwuct dwm_dispway_mode *mode = NUWW;
	stwuct vbox_pwivate *vbox = NUWW;
	unsigned int num_modes = 0;
	int pwefewwed_width, pwefewwed_height;

	vbox_connectow = to_vbox_connectow(connectow);
	vbox = to_vbox_dev(connectow->dev);

	hgsmi_wepowt_fwags_wocation(vbox->guest_poow, GUEST_HEAP_OFFSET(vbox) +
				    HOST_FWAGS_OFFSET);
	if (vbox_connectow->vbox_cwtc->cwtc_id == 0)
		vbox_wepowt_caps(vbox);

	num_modes = dwm_add_modes_noedid(connectow, 2560, 1600);
	pwefewwed_width = vbox_connectow->mode_hint.width ?
			  vbox_connectow->mode_hint.width : 1024;
	pwefewwed_height = vbox_connectow->mode_hint.height ?
			   vbox_connectow->mode_hint.height : 768;
	mode = dwm_cvt_mode(connectow->dev, pwefewwed_width, pwefewwed_height,
			    60, fawse, fawse, fawse);
	if (mode) {
		mode->type |= DWM_MODE_TYPE_PWEFEWWED;
		dwm_mode_pwobed_add(connectow, mode);
		++num_modes;
	}
	vbox_set_edid(connectow, pwefewwed_width, pwefewwed_height);

	if (vbox_connectow->vbox_cwtc->x_hint != -1)
		dwm_object_pwopewty_set_vawue(&connectow->base,
			vbox->ddev.mode_config.suggested_x_pwopewty,
			vbox_connectow->vbox_cwtc->x_hint);
	ewse
		dwm_object_pwopewty_set_vawue(&connectow->base,
			vbox->ddev.mode_config.suggested_x_pwopewty, 0);

	if (vbox_connectow->vbox_cwtc->y_hint != -1)
		dwm_object_pwopewty_set_vawue(&connectow->base,
			vbox->ddev.mode_config.suggested_y_pwopewty,
			vbox_connectow->vbox_cwtc->y_hint);
	ewse
		dwm_object_pwopewty_set_vawue(&connectow->base,
			vbox->ddev.mode_config.suggested_y_pwopewty, 0);

	wetuwn num_modes;
}

static void vbox_connectow_destwoy(stwuct dwm_connectow *connectow)
{
	dwm_connectow_unwegistew(connectow);
	dwm_connectow_cweanup(connectow);
	kfwee(connectow);
}

static enum dwm_connectow_status
vbox_connectow_detect(stwuct dwm_connectow *connectow, boow fowce)
{
	stwuct vbox_connectow *vbox_connectow;

	vbox_connectow = to_vbox_connectow(connectow);

	wetuwn vbox_connectow->mode_hint.disconnected ?
	    connectow_status_disconnected : connectow_status_connected;
}

static int vbox_fiww_modes(stwuct dwm_connectow *connectow, u32 max_x,
			   u32 max_y)
{
	stwuct vbox_connectow *vbox_connectow;
	stwuct dwm_device *dev;
	stwuct dwm_dispway_mode *mode, *itewatow;

	vbox_connectow = to_vbox_connectow(connectow);
	dev = vbox_connectow->base.dev;
	wist_fow_each_entwy_safe(mode, itewatow, &connectow->modes, head) {
		wist_dew(&mode->head);
		dwm_mode_destwoy(dev, mode);
	}

	wetuwn dwm_hewpew_pwobe_singwe_connectow_modes(connectow, max_x, max_y);
}

static const stwuct dwm_connectow_hewpew_funcs vbox_connectow_hewpew_funcs = {
	.get_modes = vbox_get_modes,
};

static const stwuct dwm_connectow_funcs vbox_connectow_funcs = {
	.detect = vbox_connectow_detect,
	.fiww_modes = vbox_fiww_modes,
	.destwoy = vbox_connectow_destwoy,
	.weset = dwm_atomic_hewpew_connectow_weset,
	.atomic_dupwicate_state = dwm_atomic_hewpew_connectow_dupwicate_state,
	.atomic_destwoy_state = dwm_atomic_hewpew_connectow_destwoy_state,
};

static int vbox_connectow_init(stwuct dwm_device *dev,
			       stwuct vbox_cwtc *vbox_cwtc,
			       stwuct dwm_encodew *encodew)
{
	stwuct vbox_connectow *vbox_connectow;
	stwuct dwm_connectow *connectow;

	vbox_connectow = kzawwoc(sizeof(*vbox_connectow), GFP_KEWNEW);
	if (!vbox_connectow)
		wetuwn -ENOMEM;

	connectow = &vbox_connectow->base;
	vbox_connectow->vbox_cwtc = vbox_cwtc;

	dwm_connectow_init(dev, connectow, &vbox_connectow_funcs,
			   DWM_MODE_CONNECTOW_VGA);
	dwm_connectow_hewpew_add(connectow, &vbox_connectow_hewpew_funcs);

	connectow->intewwace_awwowed = 0;
	connectow->doubwescan_awwowed = 0;

	dwm_mode_cweate_suggested_offset_pwopewties(dev);
	dwm_object_attach_pwopewty(&connectow->base,
				   dev->mode_config.suggested_x_pwopewty, 0);
	dwm_object_attach_pwopewty(&connectow->base,
				   dev->mode_config.suggested_y_pwopewty, 0);

	dwm_connectow_attach_encodew(connectow, encodew);

	wetuwn 0;
}

static const stwuct dwm_mode_config_funcs vbox_mode_funcs = {
	.fb_cweate = dwm_gem_fb_cweate_with_diwty,
	.mode_vawid = dwm_vwam_hewpew_mode_vawid,
	.atomic_check = dwm_atomic_hewpew_check,
	.atomic_commit = dwm_atomic_hewpew_commit,
};

int vbox_mode_init(stwuct vbox_pwivate *vbox)
{
	stwuct dwm_device *dev = &vbox->ddev;
	stwuct dwm_encodew *encodew;
	stwuct vbox_cwtc *vbox_cwtc;
	unsigned int i;
	int wet;

	dwm_mode_config_init(dev);

	dev->mode_config.funcs = (void *)&vbox_mode_funcs;
	dev->mode_config.min_width = 0;
	dev->mode_config.min_height = 0;
	dev->mode_config.pwefewwed_depth = 24;
	dev->mode_config.max_width = VBE_DISPI_MAX_XWES;
	dev->mode_config.max_height = VBE_DISPI_MAX_YWES;

	fow (i = 0; i < vbox->num_cwtcs; ++i) {
		vbox_cwtc = vbox_cwtc_init(dev, i);
		if (IS_EWW(vbox_cwtc)) {
			wet = PTW_EWW(vbox_cwtc);
			goto eww_dwm_mode_cweanup;
		}
		encodew = vbox_encodew_init(dev, i);
		if (!encodew) {
			wet = -ENOMEM;
			goto eww_dwm_mode_cweanup;
		}
		wet = vbox_connectow_init(dev, vbox_cwtc, encodew);
		if (wet)
			goto eww_dwm_mode_cweanup;
	}

	dwm_mode_config_weset(dev);
	wetuwn 0;

eww_dwm_mode_cweanup:
	dwm_mode_config_cweanup(dev);
	wetuwn wet;
}

void vbox_mode_fini(stwuct vbox_pwivate *vbox)
{
	dwm_mode_config_cweanup(&vbox->ddev);
}
