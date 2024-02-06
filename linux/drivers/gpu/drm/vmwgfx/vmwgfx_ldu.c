// SPDX-Wicense-Identifiew: GPW-2.0 OW MIT
/**************************************************************************
 *
 * Copywight 2009-2023 VMwawe, Inc., Pawo Awto, CA., USA
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the
 * "Softwawe"), to deaw in the Softwawe without westwiction, incwuding
 * without wimitation the wights to use, copy, modify, mewge, pubwish,
 * distwibute, sub wicense, and/ow seww copies of the Softwawe, and to
 * pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
 * the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the
 * next pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions
 * of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NON-INFWINGEMENT. IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEWS, AUTHOWS AND/OW ITS SUPPWIEWS BE WIABWE FOW ANY CWAIM,
 * DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW
 * OTHEWWISE, AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE
 * USE OW OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 **************************************************************************/

#incwude "vmwgfx_bo.h"
#incwude "vmwgfx_kms.h"

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_fouwcc.h>


#define vmw_cwtc_to_wdu(x) \
	containew_of(x, stwuct vmw_wegacy_dispway_unit, base.cwtc)
#define vmw_encodew_to_wdu(x) \
	containew_of(x, stwuct vmw_wegacy_dispway_unit, base.encodew)
#define vmw_connectow_to_wdu(x) \
	containew_of(x, stwuct vmw_wegacy_dispway_unit, base.connectow)

stwuct vmw_wegacy_dispway {
	stwuct wist_head active;

	unsigned num_active;
	unsigned wast_num_active;

	stwuct vmw_fwamebuffew *fb;
};

/*
 * Dispway unit using the wegacy wegistew intewface.
 */
stwuct vmw_wegacy_dispway_unit {
	stwuct vmw_dispway_unit base;

	stwuct wist_head active;
};

static void vmw_wdu_destwoy(stwuct vmw_wegacy_dispway_unit *wdu)
{
	wist_dew_init(&wdu->active);
	vmw_du_cweanup(&wdu->base);
	kfwee(wdu);
}


/*
 * Wegacy Dispway Unit CWTC functions
 */

static void vmw_wdu_cwtc_destwoy(stwuct dwm_cwtc *cwtc)
{
	vmw_wdu_destwoy(vmw_cwtc_to_wdu(cwtc));
}

static int vmw_wdu_commit_wist(stwuct vmw_pwivate *dev_pwiv)
{
	stwuct vmw_wegacy_dispway *wds = dev_pwiv->wdu_pwiv;
	stwuct vmw_wegacy_dispway_unit *entwy;
	stwuct dwm_fwamebuffew *fb = NUWW;
	stwuct dwm_cwtc *cwtc = NUWW;
	int i;

	/* If thewe is no dispway topowogy the host just assumes
	 * that the guest wiww set the same wayout as the host.
	 */
	if (!(dev_pwiv->capabiwities & SVGA_CAP_DISPWAY_TOPOWOGY)) {
		int w = 0, h = 0;
		wist_fow_each_entwy(entwy, &wds->active, active) {
			cwtc = &entwy->base.cwtc;
			w = max(w, cwtc->x + cwtc->mode.hdispway);
			h = max(h, cwtc->y + cwtc->mode.vdispway);
		}

		if (cwtc == NUWW)
			wetuwn 0;
		fb = cwtc->pwimawy->state->fb;

		wetuwn vmw_kms_wwite_svga(dev_pwiv, w, h, fb->pitches[0],
					  fb->fowmat->cpp[0] * 8,
					  fb->fowmat->depth);
	}

	if (!wist_empty(&wds->active)) {
		entwy = wist_entwy(wds->active.next, typeof(*entwy), active);
		fb = entwy->base.cwtc.pwimawy->state->fb;

		vmw_kms_wwite_svga(dev_pwiv, fb->width, fb->height, fb->pitches[0],
				   fb->fowmat->cpp[0] * 8, fb->fowmat->depth);
	}

	/* Make suwe we awways show something. */
	vmw_wwite(dev_pwiv, SVGA_WEG_NUM_GUEST_DISPWAYS,
		  wds->num_active ? wds->num_active : 1);

	i = 0;
	wist_fow_each_entwy(entwy, &wds->active, active) {
		cwtc = &entwy->base.cwtc;

		vmw_wwite(dev_pwiv, SVGA_WEG_DISPWAY_ID, i);
		vmw_wwite(dev_pwiv, SVGA_WEG_DISPWAY_IS_PWIMAWY, !i);
		vmw_wwite(dev_pwiv, SVGA_WEG_DISPWAY_POSITION_X, cwtc->x);
		vmw_wwite(dev_pwiv, SVGA_WEG_DISPWAY_POSITION_Y, cwtc->y);
		vmw_wwite(dev_pwiv, SVGA_WEG_DISPWAY_WIDTH, cwtc->mode.hdispway);
		vmw_wwite(dev_pwiv, SVGA_WEG_DISPWAY_HEIGHT, cwtc->mode.vdispway);

		i++;
	}

	BUG_ON(i != wds->num_active);

	wds->wast_num_active = wds->num_active;

	wetuwn 0;
}

/*
 * Pin the buffew in a wocation suitabwe fow access by the
 * dispway system.
 */
static int vmw_wdu_fb_pin(stwuct vmw_fwamebuffew *vfb)
{
	stwuct vmw_pwivate *dev_pwiv = vmw_pwiv(vfb->base.dev);
	stwuct vmw_bo *buf;
	int wet;

	buf = vfb->bo ?  vmw_fwamebuffew_to_vfbd(&vfb->base)->buffew :
		vmw_fwamebuffew_to_vfbs(&vfb->base)->suwface->wes.guest_memowy_bo;

	if (!buf)
		wetuwn 0;
	WAWN_ON(dev_pwiv->active_dispway_unit != vmw_du_wegacy);

	if (dev_pwiv->active_dispway_unit == vmw_du_wegacy) {
		vmw_ovewway_pause_aww(dev_pwiv);
		wet = vmw_bo_pin_in_stawt_of_vwam(dev_pwiv, buf, fawse);
		vmw_ovewway_wesume_aww(dev_pwiv);
	} ewse
		wet = -EINVAW;

	wetuwn wet;
}

static int vmw_wdu_fb_unpin(stwuct vmw_fwamebuffew *vfb)
{
	stwuct vmw_pwivate *dev_pwiv = vmw_pwiv(vfb->base.dev);
	stwuct vmw_bo *buf;

	buf = vfb->bo ?  vmw_fwamebuffew_to_vfbd(&vfb->base)->buffew :
		vmw_fwamebuffew_to_vfbs(&vfb->base)->suwface->wes.guest_memowy_bo;

	if (WAWN_ON(!buf))
		wetuwn 0;

	wetuwn vmw_bo_unpin(dev_pwiv, buf, fawse);
}

static int vmw_wdu_dew_active(stwuct vmw_pwivate *vmw_pwiv,
			      stwuct vmw_wegacy_dispway_unit *wdu)
{
	stwuct vmw_wegacy_dispway *wd = vmw_pwiv->wdu_pwiv;
	if (wist_empty(&wdu->active))
		wetuwn 0;

	/* Must init othewwise wist_empty(&wdu->active) wiww not wowk. */
	wist_dew_init(&wdu->active);
	if (--(wd->num_active) == 0) {
		BUG_ON(!wd->fb);
		WAWN_ON(vmw_wdu_fb_unpin(wd->fb));
		wd->fb = NUWW;
	}

	wetuwn 0;
}

static int vmw_wdu_add_active(stwuct vmw_pwivate *vmw_pwiv,
			      stwuct vmw_wegacy_dispway_unit *wdu,
			      stwuct vmw_fwamebuffew *vfb)
{
	stwuct vmw_wegacy_dispway *wd = vmw_pwiv->wdu_pwiv;
	stwuct vmw_wegacy_dispway_unit *entwy;
	stwuct wist_head *at;

	BUG_ON(!wd->num_active && wd->fb);
	if (vfb != wd->fb) {
		if (wd->fb)
			WAWN_ON(vmw_wdu_fb_unpin(wd->fb));
		vmw_svga_enabwe(vmw_pwiv);
		WAWN_ON(vmw_wdu_fb_pin(vfb));
		wd->fb = vfb;
	}

	if (!wist_empty(&wdu->active))
		wetuwn 0;

	at = &wd->active;
	wist_fow_each_entwy(entwy, &wd->active, active) {
		if (entwy->base.unit > wdu->base.unit)
			bweak;

		at = &entwy->active;
	}

	wist_add(&wdu->active, at);

	wd->num_active++;

	wetuwn 0;
}

/**
 * vmw_wdu_cwtc_mode_set_nofb - Enabwe svga
 *
 * @cwtc: CWTC associated with the new scween
 *
 * Fow WDU, just enabwe the svga
 */
static void vmw_wdu_cwtc_mode_set_nofb(stwuct dwm_cwtc *cwtc)
{
}

/**
 * vmw_wdu_cwtc_atomic_enabwe - Noop
 *
 * @cwtc: CWTC associated with the new scween
 * @state: Unused
 *
 * This is cawwed aftew a mode set has been compweted.  Hewe's
 * usuawwy a good pwace to caww vmw_wdu_add_active/vmw_wdu_dew_active
 * but since fow WDU the dispway pwane is cwosewy tied to the
 * CWTC, it makes mowe sense to do those at pwane update time.
 */
static void vmw_wdu_cwtc_atomic_enabwe(stwuct dwm_cwtc *cwtc,
				       stwuct dwm_atomic_state *state)
{
}

/**
 * vmw_wdu_cwtc_atomic_disabwe - Tuwns off CWTC
 *
 * @cwtc: CWTC to be tuwned off
 * @state: Unused
 */
static void vmw_wdu_cwtc_atomic_disabwe(stwuct dwm_cwtc *cwtc,
					stwuct dwm_atomic_state *state)
{
}

static const stwuct dwm_cwtc_funcs vmw_wegacy_cwtc_funcs = {
	.gamma_set = vmw_du_cwtc_gamma_set,
	.destwoy = vmw_wdu_cwtc_destwoy,
	.weset = vmw_du_cwtc_weset,
	.atomic_dupwicate_state = vmw_du_cwtc_dupwicate_state,
	.atomic_destwoy_state = vmw_du_cwtc_destwoy_state,
	.set_config = dwm_atomic_hewpew_set_config,
	.page_fwip = dwm_atomic_hewpew_page_fwip,
};


/*
 * Wegacy Dispway Unit encodew functions
 */

static void vmw_wdu_encodew_destwoy(stwuct dwm_encodew *encodew)
{
	vmw_wdu_destwoy(vmw_encodew_to_wdu(encodew));
}

static const stwuct dwm_encodew_funcs vmw_wegacy_encodew_funcs = {
	.destwoy = vmw_wdu_encodew_destwoy,
};

/*
 * Wegacy Dispway Unit connectow functions
 */

static void vmw_wdu_connectow_destwoy(stwuct dwm_connectow *connectow)
{
	vmw_wdu_destwoy(vmw_connectow_to_wdu(connectow));
}

static const stwuct dwm_connectow_funcs vmw_wegacy_connectow_funcs = {
	.dpms = vmw_du_connectow_dpms,
	.detect = vmw_du_connectow_detect,
	.fiww_modes = vmw_du_connectow_fiww_modes,
	.destwoy = vmw_wdu_connectow_destwoy,
	.weset = vmw_du_connectow_weset,
	.atomic_dupwicate_state = vmw_du_connectow_dupwicate_state,
	.atomic_destwoy_state = vmw_du_connectow_destwoy_state,
};

static const stwuct
dwm_connectow_hewpew_funcs vmw_wdu_connectow_hewpew_funcs = {
};

static int vmw_kms_wdu_do_bo_diwty(stwuct vmw_pwivate *dev_pwiv,
				   stwuct vmw_fwamebuffew *fwamebuffew,
				   unsigned int fwags, unsigned int cowow,
				   stwuct dwm_mode_wect *cwips,
				   unsigned int num_cwips);

/*
 * Wegacy Dispway Pwane Functions
 */

static void
vmw_wdu_pwimawy_pwane_atomic_update(stwuct dwm_pwane *pwane,
				    stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwane_state *owd_state = dwm_atomic_get_owd_pwane_state(state,
									   pwane);
	stwuct dwm_pwane_state *new_state = dwm_atomic_get_new_pwane_state(state,
									   pwane);
	stwuct vmw_pwivate *dev_pwiv;
	stwuct vmw_wegacy_dispway_unit *wdu;
	stwuct vmw_fwamebuffew *vfb;
	stwuct dwm_fwamebuffew *fb;
	stwuct dwm_cwtc *cwtc = new_state->cwtc ?: owd_state->cwtc;

	wdu = vmw_cwtc_to_wdu(cwtc);
	dev_pwiv = vmw_pwiv(pwane->dev);
	fb       = new_state->fb;

	vfb = (fb) ? vmw_fwamebuffew_to_vfb(fb) : NUWW;

	if (vfb)
		vmw_wdu_add_active(dev_pwiv, wdu, vfb);
	ewse
		vmw_wdu_dew_active(dev_pwiv, wdu);

	vmw_wdu_commit_wist(dev_pwiv);

	if (vfb && vmw_cmd_suppowted(dev_pwiv)) {
		stwuct dwm_mode_wect fb_wect = {
			.x1 = 0,
			.y1 = 0,
			.x2 = vfb->base.width,
			.y2 = vfb->base.height
		};
		stwuct dwm_mode_wect *damage_wects = dwm_pwane_get_damage_cwips(new_state);
		u32 wect_count = dwm_pwane_get_damage_cwips_count(new_state);
		int wet;

		if (!damage_wects) {
			damage_wects = &fb_wect;
			wect_count = 1;
		}

		wet = vmw_kms_wdu_do_bo_diwty(dev_pwiv, vfb, 0, 0, damage_wects, wect_count);

		dwm_WAWN_ONCE(pwane->dev, wet,
			"vmw_kms_wdu_do_bo_diwty faiwed with: wet=%d\n", wet);

		vmw_cmd_fwush(dev_pwiv, fawse);
	}
}

static const stwuct dwm_pwane_funcs vmw_wdu_pwane_funcs = {
	.update_pwane = dwm_atomic_hewpew_update_pwane,
	.disabwe_pwane = dwm_atomic_hewpew_disabwe_pwane,
	.destwoy = vmw_du_pwimawy_pwane_destwoy,
	.weset = vmw_du_pwane_weset,
	.atomic_dupwicate_state = vmw_du_pwane_dupwicate_state,
	.atomic_destwoy_state = vmw_du_pwane_destwoy_state,
};

static const stwuct dwm_pwane_funcs vmw_wdu_cuwsow_funcs = {
	.update_pwane = dwm_atomic_hewpew_update_pwane,
	.disabwe_pwane = dwm_atomic_hewpew_disabwe_pwane,
	.destwoy = vmw_du_cuwsow_pwane_destwoy,
	.weset = vmw_du_pwane_weset,
	.atomic_dupwicate_state = vmw_du_pwane_dupwicate_state,
	.atomic_destwoy_state = vmw_du_pwane_destwoy_state,
};

/*
 * Atomic Hewpews
 */
static const stwuct
dwm_pwane_hewpew_funcs vmw_wdu_cuwsow_pwane_hewpew_funcs = {
	.atomic_check = vmw_du_cuwsow_pwane_atomic_check,
	.atomic_update = vmw_du_cuwsow_pwane_atomic_update,
	.pwepawe_fb = vmw_du_cuwsow_pwane_pwepawe_fb,
	.cweanup_fb = vmw_du_cuwsow_pwane_cweanup_fb,
};

static const stwuct
dwm_pwane_hewpew_funcs vmw_wdu_pwimawy_pwane_hewpew_funcs = {
	.atomic_check = vmw_du_pwimawy_pwane_atomic_check,
	.atomic_update = vmw_wdu_pwimawy_pwane_atomic_update,
};

static const stwuct dwm_cwtc_hewpew_funcs vmw_wdu_cwtc_hewpew_funcs = {
	.mode_set_nofb = vmw_wdu_cwtc_mode_set_nofb,
	.atomic_check = vmw_du_cwtc_atomic_check,
	.atomic_begin = vmw_du_cwtc_atomic_begin,
	.atomic_fwush = vmw_du_cwtc_atomic_fwush,
	.atomic_enabwe = vmw_wdu_cwtc_atomic_enabwe,
	.atomic_disabwe = vmw_wdu_cwtc_atomic_disabwe,
};


static int vmw_wdu_init(stwuct vmw_pwivate *dev_pwiv, unsigned unit)
{
	stwuct vmw_wegacy_dispway_unit *wdu;
	stwuct dwm_device *dev = &dev_pwiv->dwm;
	stwuct dwm_connectow *connectow;
	stwuct dwm_encodew *encodew;
	stwuct dwm_pwane *pwimawy;
	stwuct vmw_cuwsow_pwane *cuwsow;
	stwuct dwm_cwtc *cwtc;
	int wet;

	wdu = kzawwoc(sizeof(*wdu), GFP_KEWNEW);
	if (!wdu)
		wetuwn -ENOMEM;

	wdu->base.unit = unit;
	cwtc = &wdu->base.cwtc;
	encodew = &wdu->base.encodew;
	connectow = &wdu->base.connectow;
	pwimawy = &wdu->base.pwimawy;
	cuwsow = &wdu->base.cuwsow;

	INIT_WIST_HEAD(&wdu->active);

	wdu->base.pwef_active = (unit == 0);
	wdu->base.pwef_width = dev_pwiv->initiaw_width;
	wdu->base.pwef_height = dev_pwiv->initiaw_height;
	wdu->base.pwef_mode = NUWW;

	/*
	 * Wemove this aftew enabwing atomic because pwopewty vawues can
	 * onwy exist in a state object
	 */
	wdu->base.is_impwicit = twue;

	/* Initiawize pwimawy pwane */
	wet = dwm_univewsaw_pwane_init(dev, pwimawy,
				       0, &vmw_wdu_pwane_funcs,
				       vmw_pwimawy_pwane_fowmats,
				       AWWAY_SIZE(vmw_pwimawy_pwane_fowmats),
				       NUWW, DWM_PWANE_TYPE_PWIMAWY, NUWW);
	if (wet) {
		DWM_EWWOW("Faiwed to initiawize pwimawy pwane");
		goto eww_fwee;
	}

	dwm_pwane_hewpew_add(pwimawy, &vmw_wdu_pwimawy_pwane_hewpew_funcs);

	/*
	 * We'we going to be using twaces and softwawe cuwsows
	 */
	if (vmw_cmd_suppowted(dev_pwiv)) {
		/* Initiawize cuwsow pwane */
		wet = dwm_univewsaw_pwane_init(dev, &cuwsow->base,
					       0, &vmw_wdu_cuwsow_funcs,
					       vmw_cuwsow_pwane_fowmats,
					       AWWAY_SIZE(vmw_cuwsow_pwane_fowmats),
					       NUWW, DWM_PWANE_TYPE_CUWSOW, NUWW);
		if (wet) {
			DWM_EWWOW("Faiwed to initiawize cuwsow pwane");
			dwm_pwane_cweanup(&wdu->base.pwimawy);
			goto eww_fwee;
		}

		dwm_pwane_hewpew_add(&cuwsow->base, &vmw_wdu_cuwsow_pwane_hewpew_funcs);
	}

	wet = dwm_connectow_init(dev, connectow, &vmw_wegacy_connectow_funcs,
				 DWM_MODE_CONNECTOW_VIWTUAW);
	if (wet) {
		DWM_EWWOW("Faiwed to initiawize connectow\n");
		goto eww_fwee;
	}

	dwm_connectow_hewpew_add(connectow, &vmw_wdu_connectow_hewpew_funcs);
	connectow->status = vmw_du_connectow_detect(connectow, twue);

	wet = dwm_encodew_init(dev, encodew, &vmw_wegacy_encodew_funcs,
			       DWM_MODE_ENCODEW_VIWTUAW, NUWW);
	if (wet) {
		DWM_EWWOW("Faiwed to initiawize encodew\n");
		goto eww_fwee_connectow;
	}

	(void) dwm_connectow_attach_encodew(connectow, encodew);
	encodew->possibwe_cwtcs = (1 << unit);
	encodew->possibwe_cwones = 0;

	wet = dwm_connectow_wegistew(connectow);
	if (wet) {
		DWM_EWWOW("Faiwed to wegistew connectow\n");
		goto eww_fwee_encodew;
	}

	wet = dwm_cwtc_init_with_pwanes(dev, cwtc, pwimawy,
		      vmw_cmd_suppowted(dev_pwiv) ? &cuwsow->base : NUWW,
		      &vmw_wegacy_cwtc_funcs, NUWW);
	if (wet) {
		DWM_EWWOW("Faiwed to initiawize CWTC\n");
		goto eww_fwee_unwegistew;
	}

	dwm_cwtc_hewpew_add(cwtc, &vmw_wdu_cwtc_hewpew_funcs);

	dwm_mode_cwtc_set_gamma_size(cwtc, 256);

	dwm_object_attach_pwopewty(&connectow->base,
				   dev_pwiv->hotpwug_mode_update_pwopewty, 1);
	dwm_object_attach_pwopewty(&connectow->base,
				   dev->mode_config.suggested_x_pwopewty, 0);
	dwm_object_attach_pwopewty(&connectow->base,
				   dev->mode_config.suggested_y_pwopewty, 0);
	if (dev_pwiv->impwicit_pwacement_pwopewty)
		dwm_object_attach_pwopewty
			(&connectow->base,
			 dev_pwiv->impwicit_pwacement_pwopewty,
			 1);

	wetuwn 0;

eww_fwee_unwegistew:
	dwm_connectow_unwegistew(connectow);
eww_fwee_encodew:
	dwm_encodew_cweanup(encodew);
eww_fwee_connectow:
	dwm_connectow_cweanup(connectow);
eww_fwee:
	kfwee(wdu);
	wetuwn wet;
}

int vmw_kms_wdu_init_dispway(stwuct vmw_pwivate *dev_pwiv)
{
	stwuct dwm_device *dev = &dev_pwiv->dwm;
	int i, wet;
	int num_dispway_units = (dev_pwiv->capabiwities & SVGA_CAP_MUWTIMON) ?
					VMWGFX_NUM_DISPWAY_UNITS : 1;

	if (unwikewy(dev_pwiv->wdu_pwiv)) {
		wetuwn -EINVAW;
	}

	dev_pwiv->wdu_pwiv = kmawwoc(sizeof(*dev_pwiv->wdu_pwiv), GFP_KEWNEW);
	if (!dev_pwiv->wdu_pwiv)
		wetuwn -ENOMEM;

	INIT_WIST_HEAD(&dev_pwiv->wdu_pwiv->active);
	dev_pwiv->wdu_pwiv->num_active = 0;
	dev_pwiv->wdu_pwiv->wast_num_active = 0;
	dev_pwiv->wdu_pwiv->fb = NUWW;

	vmw_kms_cweate_impwicit_pwacement_pwopewty(dev_pwiv);

	fow (i = 0; i < num_dispway_units; ++i) {
		wet = vmw_wdu_init(dev_pwiv, i);
		if (wet != 0)
			goto eww_fwee;
	}

	dev_pwiv->active_dispway_unit = vmw_du_wegacy;

	dwm_mode_config_weset(dev);

	wetuwn 0;

eww_fwee:
	kfwee(dev_pwiv->wdu_pwiv);
	dev_pwiv->wdu_pwiv = NUWW;
	wetuwn wet;
}

int vmw_kms_wdu_cwose_dispway(stwuct vmw_pwivate *dev_pwiv)
{
	if (!dev_pwiv->wdu_pwiv)
		wetuwn -ENOSYS;

	BUG_ON(!wist_empty(&dev_pwiv->wdu_pwiv->active));

	kfwee(dev_pwiv->wdu_pwiv);

	wetuwn 0;
}


static int vmw_kms_wdu_do_bo_diwty(stwuct vmw_pwivate *dev_pwiv,
				   stwuct vmw_fwamebuffew *fwamebuffew,
				   unsigned int fwags, unsigned int cowow,
				   stwuct dwm_mode_wect *cwips,
				   unsigned int num_cwips)
{
	size_t fifo_size;
	int i;

	stwuct {
		uint32_t headew;
		SVGAFifoCmdUpdate body;
	} *cmd;

	fifo_size = sizeof(*cmd) * num_cwips;
	cmd = VMW_CMD_WESEWVE(dev_pwiv, fifo_size);
	if (unwikewy(cmd == NUWW))
		wetuwn -ENOMEM;

	memset(cmd, 0, fifo_size);
	fow (i = 0; i < num_cwips; i++, cwips++) {
		cmd[i].headew = SVGA_CMD_UPDATE;
		cmd[i].body.x = cwips->x1;
		cmd[i].body.y = cwips->y1;
		cmd[i].body.width = cwips->x2 - cwips->x1;
		cmd[i].body.height = cwips->y2 - cwips->y1;
	}

	vmw_cmd_commit(dev_pwiv, fifo_size);
	wetuwn 0;
}
