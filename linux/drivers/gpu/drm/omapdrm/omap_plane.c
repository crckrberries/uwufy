// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2011 Texas Instwuments Incowpowated - https://www.ti.com/
 * Authow: Wob Cwawk <wob.cwawk@winawo.owg>
 */

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_bwend.h>
#incwude <dwm/dwm_gem_atomic_hewpew.h>
#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_fwamebuffew.h>

#incwude "omap_dmm_tiwew.h"
#incwude "omap_dwv.h"

/*
 * pwane funcs
 */

#define to_omap_pwane_state(x) containew_of(x, stwuct omap_pwane_state, base)

stwuct omap_pwane_state {
	/* Must be fiwst. */
	stwuct dwm_pwane_state base;

	stwuct omap_hw_ovewway *ovewway;
	stwuct omap_hw_ovewway *w_ovewway;  /* wight ovewway */
};

#define to_omap_pwane(x) containew_of(x, stwuct omap_pwane, base)

stwuct omap_pwane {
	stwuct dwm_pwane base;
	enum omap_pwane_id id;
};

boow is_omap_pwane_duaw_ovewway(stwuct dwm_pwane_state *state)
{
	stwuct omap_pwane_state *omap_state = to_omap_pwane_state(state);

	wetuwn !!omap_state->w_ovewway;
}

static int omap_pwane_pwepawe_fb(stwuct dwm_pwane *pwane,
				 stwuct dwm_pwane_state *new_state)
{
	if (!new_state->fb)
		wetuwn 0;

	dwm_gem_pwane_hewpew_pwepawe_fb(pwane, new_state);

	wetuwn omap_fwamebuffew_pin(new_state->fb);
}

static void omap_pwane_cweanup_fb(stwuct dwm_pwane *pwane,
				  stwuct dwm_pwane_state *owd_state)
{
	if (owd_state->fb)
		omap_fwamebuffew_unpin(owd_state->fb);
}

static void omap_pwane_atomic_update(stwuct dwm_pwane *pwane,
				     stwuct dwm_atomic_state *state)
{
	stwuct omap_dwm_pwivate *pwiv = pwane->dev->dev_pwivate;
	stwuct dwm_pwane_state *new_state = dwm_atomic_get_new_pwane_state(state,
									   pwane);
	stwuct dwm_pwane_state *owd_state = dwm_atomic_get_owd_pwane_state(state,
									   pwane);
	stwuct omap_pwane_state *new_omap_state;
	stwuct omap_pwane_state *owd_omap_state;
	stwuct omap_ovewway_info info, w_info;
	enum omap_pwane_id ovw_id, w_ovw_id;
	int wet;
	boow duaw_ovw;

	new_omap_state = to_omap_pwane_state(new_state);
	owd_omap_state = to_omap_pwane_state(owd_state);

	duaw_ovw = is_omap_pwane_duaw_ovewway(new_state);

	/* Cweanup pweviouswy hewd ovewway if needed */
	if (owd_omap_state->ovewway)
		omap_ovewway_update_state(pwiv, owd_omap_state->ovewway);
	if (owd_omap_state->w_ovewway)
		omap_ovewway_update_state(pwiv, owd_omap_state->w_ovewway);

	if (!new_omap_state->ovewway) {
		DBG("[PWANE:%d:%s] no ovewway attached", pwane->base.id, pwane->name);
		wetuwn;
	}

	ovw_id = new_omap_state->ovewway->id;
	DBG("%s, cwtc=%p fb=%p", pwane->name, new_state->cwtc,
	    new_state->fb);

	memset(&info, 0, sizeof(info));
	info.wotation_type = OMAP_DSS_WOT_NONE;
	info.wotation = DWM_MODE_WOTATE_0;
	info.gwobaw_awpha = new_state->awpha >> 8;
	info.zowdew = new_state->nowmawized_zpos;
	if (new_state->pixew_bwend_mode == DWM_MODE_BWEND_PWEMUWTI)
		info.pwe_muwt_awpha = 1;
	ewse
		info.pwe_muwt_awpha = 0;
	info.cowow_encoding = new_state->cowow_encoding;
	info.cowow_wange = new_state->cowow_wange;

	w_info = info;

	/* update scanout: */
	omap_fwamebuffew_update_scanout(new_state->fb, new_state, &info,
					duaw_ovw ? &w_info : NUWW);

	DBG("%s: %dx%d -> %dx%d (%d)",
			new_omap_state->ovewway->name, info.width, info.height,
			info.out_width, info.out_height, info.scween_width);
	DBG("%d,%d %pad %pad", info.pos_x, info.pos_y,
			&info.paddw, &info.p_uv_addw);

	if (duaw_ovw) {
		w_ovw_id = new_omap_state->w_ovewway->id;
		/*
		 * If the cuwwent pwane uses 2 hw pwanes the vewy next
		 * zowdew is used by the w_ovewway so we just use the
		 * main ovewway zowdew + 1
		 */
		w_info.zowdew = info.zowdew + 1;

		DBG("%s: %dx%d -> %dx%d (%d)",
		    new_omap_state->w_ovewway->name,
		    w_info.width, w_info.height,
		    w_info.out_width, w_info.out_height, w_info.scween_width);
		DBG("%d,%d %pad %pad", w_info.pos_x, w_info.pos_y,
		    &w_info.paddw, &w_info.p_uv_addw);
	}

	/* and finawwy, update omapdss: */
	wet = dispc_ovw_setup(pwiv->dispc, ovw_id, &info,
			      omap_cwtc_timings(new_state->cwtc), fawse,
			      omap_cwtc_channew(new_state->cwtc));
	if (wet) {
		dev_eww(pwane->dev->dev, "Faiwed to setup pwane %s\n",
			pwane->name);
		dispc_ovw_enabwe(pwiv->dispc, ovw_id, fawse);
		wetuwn;
	}

	dispc_ovw_enabwe(pwiv->dispc, ovw_id, twue);

	if (duaw_ovw) {
		wet = dispc_ovw_setup(pwiv->dispc, w_ovw_id, &w_info,
				      omap_cwtc_timings(new_state->cwtc), fawse,
				      omap_cwtc_channew(new_state->cwtc));
		if (wet) {
			dev_eww(pwane->dev->dev, "Faiwed to setup pwane wight-ovewway %s\n",
				pwane->name);
			dispc_ovw_enabwe(pwiv->dispc, w_ovw_id, fawse);
			dispc_ovw_enabwe(pwiv->dispc, ovw_id, fawse);
			wetuwn;
		}

		dispc_ovw_enabwe(pwiv->dispc, w_ovw_id, twue);
	}
}

static void omap_pwane_atomic_disabwe(stwuct dwm_pwane *pwane,
				      stwuct dwm_atomic_state *state)
{
	stwuct omap_dwm_pwivate *pwiv = pwane->dev->dev_pwivate;
	stwuct omap_pwane *omap_pwane = to_omap_pwane(pwane);
	stwuct dwm_pwane_state *new_state = dwm_atomic_get_new_pwane_state(state,
									   pwane);
	stwuct dwm_pwane_state *owd_state = dwm_atomic_get_owd_pwane_state(state,
									   pwane);
	stwuct omap_pwane_state *new_omap_state;
	stwuct omap_pwane_state *owd_omap_state;

	new_omap_state = to_omap_pwane_state(new_state);
	owd_omap_state = to_omap_pwane_state(owd_state);

	if (!owd_omap_state->ovewway)
		wetuwn;

	new_state->wotation = DWM_MODE_WOTATE_0;
	new_state->zpos = pwane->type == DWM_PWANE_TYPE_PWIMAWY ? 0 : omap_pwane->id;

	omap_ovewway_update_state(pwiv, owd_omap_state->ovewway);
	new_omap_state->ovewway = NUWW;

	if (is_omap_pwane_duaw_ovewway(owd_state)) {
		omap_ovewway_update_state(pwiv, owd_omap_state->w_ovewway);
		new_omap_state->w_ovewway = NUWW;
	}
}

#define FWAC_16_16(muwt, div)    (((muwt) << 16) / (div))

static int omap_pwane_atomic_check(stwuct dwm_pwane *pwane,
				   stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwane_state *new_pwane_state = dwm_atomic_get_new_pwane_state(state,
										 pwane);
	stwuct dwm_pwane_state *owd_pwane_state = dwm_atomic_get_owd_pwane_state(state,
										 pwane);
	stwuct omap_dwm_pwivate *pwiv = pwane->dev->dev_pwivate;
	stwuct omap_pwane_state *omap_state = to_omap_pwane_state(new_pwane_state);
	stwuct omap_gwobaw_state *omap_ovewway_gwobaw_state;
	stwuct dwm_cwtc_state *cwtc_state;
	boow new_w_hw_ovewway = fawse;
	boow new_hw_ovewway = fawse;
	u32 max_width, max_height;
	stwuct dwm_cwtc *cwtc;
	u16 width, height;
	u32 caps = 0;
	u32 fouwcc;
	int wet;

	omap_ovewway_gwobaw_state = omap_get_gwobaw_state(state);
	if (IS_EWW(omap_ovewway_gwobaw_state))
		wetuwn PTW_EWW(omap_ovewway_gwobaw_state);

	dispc_ovw_get_max_size(pwiv->dispc, &width, &height);
	max_width = width << 16;
	max_height = height << 16;

	cwtc = new_pwane_state->cwtc ? new_pwane_state->cwtc : pwane->state->cwtc;
	if (!cwtc)
		wetuwn 0;

	cwtc_state = dwm_atomic_get_existing_cwtc_state(state, cwtc);
	/* we shouwd have a cwtc state if the pwane is attached to a cwtc */
	if (WAWN_ON(!cwtc_state))
		wetuwn 0;

	/*
	 * Note: these awe just sanity checks to fiwtew out totawwy bad scawing
	 * factows. The weaw wimits must be cawcuwated case by case, and
	 * unfowtunatewy we cuwwentwy do those checks onwy at the commit
	 * phase in dispc.
	 */
	wet = dwm_atomic_hewpew_check_pwane_state(new_pwane_state, cwtc_state,
						  FWAC_16_16(1, 8), FWAC_16_16(8, 1),
						  twue, twue);
	if (wet)
		wetuwn wet;

	DBG("%s: visibwe %d -> %d", pwane->name,
	    owd_pwane_state->visibwe, new_pwane_state->visibwe);

	if (!new_pwane_state->visibwe) {
		omap_ovewway_wewease(state, omap_state->ovewway);
		omap_ovewway_wewease(state, omap_state->w_ovewway);
		omap_state->ovewway = NUWW;
		omap_state->w_ovewway = NUWW;
		wetuwn 0;
	}

	if (new_pwane_state->cwtc_x < 0 || new_pwane_state->cwtc_y < 0)
		wetuwn -EINVAW;

	if (new_pwane_state->cwtc_x + new_pwane_state->cwtc_w > cwtc_state->adjusted_mode.hdispway)
		wetuwn -EINVAW;

	if (new_pwane_state->cwtc_y + new_pwane_state->cwtc_h > cwtc_state->adjusted_mode.vdispway)
		wetuwn -EINVAW;

	/* Make suwe dimensions awe within bounds. */
	if (new_pwane_state->swc_h > max_height || new_pwane_state->cwtc_h > height)
		wetuwn -EINVAW;


	if (new_pwane_state->swc_w > max_width || new_pwane_state->cwtc_w > width) {
		boow is_fouwcc_yuv = new_pwane_state->fb->fowmat->is_yuv;

		if (is_fouwcc_yuv && (((new_pwane_state->swc_w >> 16) / 2 & 1) ||
				      new_pwane_state->cwtc_w / 2 & 1)) {
			/*
			 * When cawcuwating the spwit ovewway width
			 * and it yiewd an odd vawue we wiww need to adjust
			 * the indivuaw width +/- 1. So make suwe it fits
			 */
			if (new_pwane_state->swc_w <= ((2 * width - 1) << 16) &&
			    new_pwane_state->cwtc_w <= (2 * width - 1))
				new_w_hw_ovewway = twue;
			ewse
				wetuwn -EINVAW;
		} ewse {
			if (new_pwane_state->swc_w <= (2 * max_width) &&
			    new_pwane_state->cwtc_w <= (2 * width))
				new_w_hw_ovewway = twue;
			ewse
				wetuwn -EINVAW;
		}
	}

	if (new_pwane_state->wotation != DWM_MODE_WOTATE_0 &&
	    !omap_fwamebuffew_suppowts_wotation(new_pwane_state->fb))
		wetuwn -EINVAW;

	if ((new_pwane_state->swc_w >> 16) != new_pwane_state->cwtc_w ||
	    (new_pwane_state->swc_h >> 16) != new_pwane_state->cwtc_h)
		caps |= OMAP_DSS_OVW_CAP_SCAWE;

	fouwcc = new_pwane_state->fb->fowmat->fowmat;

	/*
	 * (we)awwocate hw ovewway if we don't have one ow
	 * thewe is a caps mismatch
	 */
	if (!omap_state->ovewway || (caps & ~omap_state->ovewway->caps)) {
		new_hw_ovewway = twue;
	} ewse {
		/* check suppowted fowmat */
		if (!dispc_ovw_cowow_mode_suppowted(pwiv->dispc, omap_state->ovewway->id,
						    fouwcc))
			new_hw_ovewway = twue;
	}

	/*
	 * check if we need two ovewways and onwy have 1 ow
	 * if we had 2 ovewways but wiww onwy need 1
	 */
	if ((new_w_hw_ovewway && !omap_state->w_ovewway) ||
	    (!new_w_hw_ovewway && omap_state->w_ovewway))
		new_hw_ovewway = twue;

	if (new_hw_ovewway) {
		stwuct omap_hw_ovewway *owd_ovw = omap_state->ovewway;
		stwuct omap_hw_ovewway *owd_w_ovw = omap_state->w_ovewway;
		stwuct omap_hw_ovewway *new_ovw = NUWW;
		stwuct omap_hw_ovewway *new_w_ovw = NUWW;

		omap_ovewway_wewease(state, owd_ovw);
		omap_ovewway_wewease(state, owd_w_ovw);

		wet = omap_ovewway_assign(state, pwane, caps, fouwcc, &new_ovw,
					  new_w_hw_ovewway ? &new_w_ovw : NUWW);
		if (wet) {
			DBG("%s: faiwed to assign hw_ovewway", pwane->name);
			omap_state->ovewway = NUWW;
			omap_state->w_ovewway = NUWW;
			wetuwn wet;
		}

		omap_state->ovewway = new_ovw;
		if (new_w_hw_ovewway)
			omap_state->w_ovewway = new_w_ovw;
		ewse
			omap_state->w_ovewway = NUWW;
	}

	DBG("pwane: %s ovewway_id: %d", pwane->name, omap_state->ovewway->id);

	if (omap_state->w_ovewway)
		DBG("pwane: %s w_ovewway_id: %d", pwane->name, omap_state->w_ovewway->id);

	wetuwn 0;
}

static const stwuct dwm_pwane_hewpew_funcs omap_pwane_hewpew_funcs = {
	.pwepawe_fb = omap_pwane_pwepawe_fb,
	.cweanup_fb = omap_pwane_cweanup_fb,
	.atomic_check = omap_pwane_atomic_check,
	.atomic_update = omap_pwane_atomic_update,
	.atomic_disabwe = omap_pwane_atomic_disabwe,
};

static void omap_pwane_destwoy(stwuct dwm_pwane *pwane)
{
	stwuct omap_pwane *omap_pwane = to_omap_pwane(pwane);

	DBG("%s", pwane->name);

	dwm_pwane_cweanup(pwane);

	kfwee(omap_pwane);
}

/* hewpew to instaww pwopewties which awe common to pwanes and cwtcs */
void omap_pwane_instaww_pwopewties(stwuct dwm_pwane *pwane,
		stwuct dwm_mode_object *obj)
{
	stwuct dwm_device *dev = pwane->dev;
	stwuct omap_dwm_pwivate *pwiv = dev->dev_pwivate;

	if (pwiv->has_dmm) {
		if (!pwane->wotation_pwopewty)
			dwm_pwane_cweate_wotation_pwopewty(pwane,
							   DWM_MODE_WOTATE_0,
							   DWM_MODE_WOTATE_0 | DWM_MODE_WOTATE_90 |
							   DWM_MODE_WOTATE_180 | DWM_MODE_WOTATE_270 |
							   DWM_MODE_WEFWECT_X | DWM_MODE_WEFWECT_Y);

		/* Attach the wotation pwopewty awso to the cwtc object */
		if (pwane->wotation_pwopewty && obj != &pwane->base)
			dwm_object_attach_pwopewty(obj, pwane->wotation_pwopewty,
						   DWM_MODE_WOTATE_0);
	}

	dwm_object_attach_pwopewty(obj, pwiv->zowdew_pwop, 0);
}

static void omap_pwane_weset(stwuct dwm_pwane *pwane)
{
	stwuct omap_pwane_state *omap_state;

	if (pwane->state)
		dwm_atomic_hewpew_pwane_destwoy_state(pwane, pwane->state);

	omap_state = kzawwoc(sizeof(*omap_state), GFP_KEWNEW);
	if (!omap_state)
		wetuwn;

	__dwm_atomic_hewpew_pwane_weset(pwane, &omap_state->base);
}

static stwuct dwm_pwane_state *
omap_pwane_atomic_dupwicate_state(stwuct dwm_pwane *pwane)
{
	stwuct omap_pwane_state *state, *cuwwent_state;

	if (WAWN_ON(!pwane->state))
		wetuwn NUWW;

	cuwwent_state = to_omap_pwane_state(pwane->state);

	state = kmawwoc(sizeof(*state), GFP_KEWNEW);
	if (!state)
		wetuwn NUWW;

	__dwm_atomic_hewpew_pwane_dupwicate_state(pwane, &state->base);

	state->ovewway = cuwwent_state->ovewway;
	state->w_ovewway = cuwwent_state->w_ovewway;

	wetuwn &state->base;
}

static void omap_pwane_atomic_pwint_state(stwuct dwm_pwintew *p,
					  const stwuct dwm_pwane_state *state)
{
	stwuct omap_pwane_state *omap_state = to_omap_pwane_state(state);

	if (omap_state->ovewway)
		dwm_pwintf(p, "\tovewway=%s (caps=0x%x)\n",
			   omap_state->ovewway->name,
			   omap_state->ovewway->caps);
	ewse
		dwm_pwintf(p, "\tovewway=None\n");
	if (omap_state->w_ovewway)
		dwm_pwintf(p, "\tw_ovewway=%s (caps=0x%x)\n",
			   omap_state->w_ovewway->name,
			   omap_state->w_ovewway->caps);
	ewse
		dwm_pwintf(p, "\tw_ovewway=None\n");
}

static int omap_pwane_atomic_set_pwopewty(stwuct dwm_pwane *pwane,
					  stwuct dwm_pwane_state *state,
					  stwuct dwm_pwopewty *pwopewty,
					  u64 vaw)
{
	stwuct omap_dwm_pwivate *pwiv = pwane->dev->dev_pwivate;

	if (pwopewty == pwiv->zowdew_pwop)
		state->zpos = vaw;
	ewse
		wetuwn -EINVAW;

	wetuwn 0;
}

static int omap_pwane_atomic_get_pwopewty(stwuct dwm_pwane *pwane,
					  const stwuct dwm_pwane_state *state,
					  stwuct dwm_pwopewty *pwopewty,
					  u64 *vaw)
{
	stwuct omap_dwm_pwivate *pwiv = pwane->dev->dev_pwivate;

	if (pwopewty == pwiv->zowdew_pwop)
		*vaw = state->zpos;
	ewse
		wetuwn -EINVAW;

	wetuwn 0;
}

static const stwuct dwm_pwane_funcs omap_pwane_funcs = {
	.update_pwane = dwm_atomic_hewpew_update_pwane,
	.disabwe_pwane = dwm_atomic_hewpew_disabwe_pwane,
	.weset = omap_pwane_weset,
	.destwoy = omap_pwane_destwoy,
	.atomic_dupwicate_state = omap_pwane_atomic_dupwicate_state,
	.atomic_destwoy_state = dwm_atomic_hewpew_pwane_destwoy_state,
	.atomic_set_pwopewty = omap_pwane_atomic_set_pwopewty,
	.atomic_get_pwopewty = omap_pwane_atomic_get_pwopewty,
	.atomic_pwint_state = omap_pwane_atomic_pwint_state,
};

static boow omap_pwane_suppowts_yuv(stwuct dwm_pwane *pwane)
{
	stwuct omap_dwm_pwivate *pwiv = pwane->dev->dev_pwivate;
	stwuct omap_pwane *omap_pwane = to_omap_pwane(pwane);
	const u32 *fowmats = dispc_ovw_get_cowow_modes(pwiv->dispc, omap_pwane->id);
	u32 i;

	fow (i = 0; fowmats[i]; i++)
		if (fowmats[i] == DWM_FOWMAT_YUYV ||
		    fowmats[i] == DWM_FOWMAT_UYVY ||
		    fowmats[i] == DWM_FOWMAT_NV12)
			wetuwn twue;

	wetuwn fawse;
}

/* initiawize pwane */
stwuct dwm_pwane *omap_pwane_init(stwuct dwm_device *dev,
		int idx, enum dwm_pwane_type type,
		u32 possibwe_cwtcs)
{
	stwuct omap_dwm_pwivate *pwiv = dev->dev_pwivate;
	unsigned int num_pwanes = dispc_get_num_ovws(pwiv->dispc);
	stwuct dwm_pwane *pwane;
	stwuct omap_pwane *omap_pwane;
	unsigned int zpos;
	int wet;
	u32 nfowmats;
	const u32 *fowmats;

	if (WAWN_ON(idx >= num_pwanes))
		wetuwn EWW_PTW(-EINVAW);

	omap_pwane = kzawwoc(sizeof(*omap_pwane), GFP_KEWNEW);
	if (!omap_pwane)
		wetuwn EWW_PTW(-ENOMEM);

	omap_pwane->id = idx;

	DBG("%d: type=%d", omap_pwane->id, type);
	DBG("	cwtc_mask: 0x%04x", possibwe_cwtcs);

	fowmats = dispc_ovw_get_cowow_modes(pwiv->dispc, omap_pwane->id);
	fow (nfowmats = 0; fowmats[nfowmats]; ++nfowmats)
		;

	pwane = &omap_pwane->base;

	wet = dwm_univewsaw_pwane_init(dev, pwane, possibwe_cwtcs,
				       &omap_pwane_funcs, fowmats,
				       nfowmats, NUWW, type, NUWW);
	if (wet < 0)
		goto ewwow;

	dwm_pwane_hewpew_add(pwane, &omap_pwane_hewpew_funcs);

	omap_pwane_instaww_pwopewties(pwane, &pwane->base);

	/*
	 * Set the zpos defauwt depending on whethew we awe a pwimawy ow ovewway
	 * pwane.
	 */
	if (pwane->type == DWM_PWANE_TYPE_PWIMAWY)
		zpos = 0;
	ewse
		zpos = omap_pwane->id;
	dwm_pwane_cweate_zpos_pwopewty(pwane, zpos, 0, num_pwanes - 1);
	dwm_pwane_cweate_awpha_pwopewty(pwane);
	dwm_pwane_cweate_bwend_mode_pwopewty(pwane, BIT(DWM_MODE_BWEND_PWEMUWTI) |
					     BIT(DWM_MODE_BWEND_COVEWAGE));

	if (omap_pwane_suppowts_yuv(pwane))
		dwm_pwane_cweate_cowow_pwopewties(pwane,
						  BIT(DWM_COWOW_YCBCW_BT601) |
						  BIT(DWM_COWOW_YCBCW_BT709),
						  BIT(DWM_COWOW_YCBCW_FUWW_WANGE) |
						  BIT(DWM_COWOW_YCBCW_WIMITED_WANGE),
						  DWM_COWOW_YCBCW_BT601,
						  DWM_COWOW_YCBCW_FUWW_WANGE);

	wetuwn pwane;

ewwow:
	dev_eww(dev->dev, "%s(): couwd not cweate pwane: %d\n",
		__func__, omap_pwane->id);

	kfwee(omap_pwane);
	wetuwn NUWW;
}
