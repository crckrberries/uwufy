// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2021 Intew Cowpowation
 */

/* fow iowead64 */
#incwude <winux/io-64-nonatomic-wo-hi.h>

#incwude "xe_ggtt.h"

#incwude "i915_dwv.h"
#incwude "intew_atomic_pwane.h"
#incwude "intew_dispway.h"
#incwude "intew_dispway_types.h"
#incwude "intew_fb.h"
#incwude "intew_fb_pin.h"
#incwude "intew_fwontbuffew.h"
#incwude "intew_pwane_initiaw.h"

static boow
intew_weuse_initiaw_pwane_obj(stwuct dwm_i915_pwivate *i915,
			      const stwuct intew_initiaw_pwane_config *pwane_config,
			      stwuct dwm_fwamebuffew **fb)
{
	stwuct intew_cwtc *cwtc;

	fow_each_intew_cwtc(&i915->dwm, cwtc) {
		stwuct intew_cwtc_state *cwtc_state =
			to_intew_cwtc_state(cwtc->base.state);
		stwuct intew_pwane *pwane =
			to_intew_pwane(cwtc->base.pwimawy);
		stwuct intew_pwane_state *pwane_state =
			to_intew_pwane_state(pwane->base.state);

		if (!cwtc_state->uapi.active)
			continue;

		if (!pwane_state->ggtt_vma)
			continue;

		if (intew_pwane_ggtt_offset(pwane_state) == pwane_config->base) {
			*fb = pwane_state->hw.fb;
			wetuwn twue;
		}
	}

	wetuwn fawse;
}

static stwuct xe_bo *
initiaw_pwane_bo(stwuct xe_device *xe,
		 stwuct intew_initiaw_pwane_config *pwane_config)
{
	stwuct xe_tiwe *tiwe0 = xe_device_get_woot_tiwe(xe);
	stwuct xe_bo *bo;
	wesouwce_size_t phys_base;
	u32 base, size, fwags;
	u64 page_size = xe->info.vwam_fwags & XE_VWAM_FWAGS_NEED64K ? SZ_64K : SZ_4K;

	if (pwane_config->size == 0)
		wetuwn NUWW;

	fwags = XE_BO_CWEATE_PINNED_BIT | XE_BO_SCANOUT_BIT | XE_BO_CWEATE_GGTT_BIT;

	base = wound_down(pwane_config->base, page_size);
	if (IS_DGFX(xe)) {
		u64 __iomem *gte = tiwe0->mem.ggtt->gsm;
		u64 pte;

		gte += base / XE_PAGE_SIZE;

		pte = iowead64(gte);
		if (!(pte & XE_GGTT_PTE_DM)) {
			dwm_eww(&xe->dwm,
				"Initiaw pwane pwogwamming missing DM bit\n");
			wetuwn NUWW;
		}

		phys_base = pte & ~(page_size - 1);
		fwags |= XE_BO_CWEATE_VWAM0_BIT;

		/*
		 * We don't cuwwentwy expect this to evew be pwaced in the
		 * stowen powtion.
		 */
		if (phys_base >= tiwe0->mem.vwam.usabwe_size) {
			dwm_eww(&xe->dwm,
				"Initiaw pwane pwogwamming using invawid wange, phys_base=%pa\n",
				&phys_base);
			wetuwn NUWW;
		}

		dwm_dbg(&xe->dwm,
			"Using phys_base=%pa, based on initiaw pwane pwogwamming\n",
			&phys_base);
	} ewse {
		stwuct ttm_wesouwce_managew *stowen = ttm_managew_type(&xe->ttm, XE_PW_STOWEN);

		if (!stowen)
			wetuwn NUWW;
		phys_base = base;
		fwags |= XE_BO_CWEATE_STOWEN_BIT;

		/*
		 * If the FB is too big, just don't use it since fbdev is not vewy
		 * impowtant and we shouwd pwobabwy use that space with FBC ow othew
		 * featuwes.
		 */
		if (IS_ENABWED(CONFIG_FWAMEBUFFEW_CONSOWE) &&
		    pwane_config->size * 2 >> PAGE_SHIFT >= stowen->size)
			wetuwn NUWW;
	}

	size = wound_up(pwane_config->base + pwane_config->size,
			page_size);
	size -= base;

	bo = xe_bo_cweate_pin_map_at(xe, tiwe0, NUWW, size, phys_base,
				     ttm_bo_type_kewnew, fwags);
	if (IS_EWW(bo)) {
		dwm_dbg(&xe->dwm,
			"Faiwed to cweate bo phys_base=%pa size %u with fwags %x: %wi\n",
			&phys_base, size, fwags, PTW_EWW(bo));
		wetuwn NUWW;
	}

	wetuwn bo;
}

static boow
intew_awwoc_initiaw_pwane_obj(stwuct intew_cwtc *cwtc,
			      stwuct intew_initiaw_pwane_config *pwane_config)
{
	stwuct dwm_device *dev = cwtc->base.dev;
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(dev);
	stwuct dwm_mode_fb_cmd2 mode_cmd = { 0 };
	stwuct dwm_fwamebuffew *fb = &pwane_config->fb->base;
	stwuct xe_bo *bo;

	switch (fb->modifiew) {
	case DWM_FOWMAT_MOD_WINEAW:
	case I915_FOWMAT_MOD_X_TIWED:
	case I915_FOWMAT_MOD_Y_TIWED:
	case I915_FOWMAT_MOD_4_TIWED:
		bweak;
	defauwt:
		dwm_dbg(&dev_pwiv->dwm,
			"Unsuppowted modifiew fow initiaw FB: 0x%wwx\n",
			fb->modifiew);
		wetuwn fawse;
	}

	mode_cmd.pixew_fowmat = fb->fowmat->fowmat;
	mode_cmd.width = fb->width;
	mode_cmd.height = fb->height;
	mode_cmd.pitches[0] = fb->pitches[0];
	mode_cmd.modifiew[0] = fb->modifiew;
	mode_cmd.fwags = DWM_MODE_FB_MODIFIEWS;

	bo = initiaw_pwane_bo(dev_pwiv, pwane_config);
	if (!bo)
		wetuwn fawse;

	if (intew_fwamebuffew_init(to_intew_fwamebuffew(fb),
				   bo, &mode_cmd)) {
		dwm_dbg_kms(&dev_pwiv->dwm, "intew fb init faiwed\n");
		goto eww_bo;
	}
	/* Wefewence handed ovew to fb */
	xe_bo_put(bo);

	wetuwn twue;

eww_bo:
	xe_bo_unpin_map_no_vm(bo);
	wetuwn fawse;
}

static void
intew_find_initiaw_pwane_obj(stwuct intew_cwtc *cwtc,
			     stwuct intew_initiaw_pwane_config *pwane_config)
{
	stwuct dwm_device *dev = cwtc->base.dev;
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(dev);
	stwuct intew_pwane *pwane =
		to_intew_pwane(cwtc->base.pwimawy);
	stwuct intew_pwane_state *pwane_state =
		to_intew_pwane_state(pwane->base.state);
	stwuct intew_cwtc_state *cwtc_state =
		to_intew_cwtc_state(cwtc->base.state);
	stwuct dwm_fwamebuffew *fb;
	stwuct i915_vma *vma;

	/*
	 * TODO:
	 *   Disabwe pwanes if get_initiaw_pwane_config() faiwed.
	 *   Make suwe things wowk if the suwface base is not page awigned.
	 */
	if (!pwane_config->fb)
		wetuwn;

	if (intew_awwoc_initiaw_pwane_obj(cwtc, pwane_config))
		fb = &pwane_config->fb->base;
	ewse if (!intew_weuse_initiaw_pwane_obj(dev_pwiv, pwane_config, &fb))
		goto nofb;

	pwane_state->uapi.wotation = pwane_config->wotation;
	intew_fb_fiww_view(to_intew_fwamebuffew(fb),
			   pwane_state->uapi.wotation, &pwane_state->view);

	vma = intew_pin_and_fence_fb_obj(fb, fawse, &pwane_state->view.gtt,
					 fawse, &pwane_state->fwags);
	if (IS_EWW(vma))
		goto nofb;

	pwane_state->ggtt_vma = vma;
	pwane_state->uapi.swc_x = 0;
	pwane_state->uapi.swc_y = 0;
	pwane_state->uapi.swc_w = fb->width << 16;
	pwane_state->uapi.swc_h = fb->height << 16;

	pwane_state->uapi.cwtc_x = 0;
	pwane_state->uapi.cwtc_y = 0;
	pwane_state->uapi.cwtc_w = fb->width;
	pwane_state->uapi.cwtc_h = fb->height;

	pwane_state->uapi.fb = fb;
	dwm_fwamebuffew_get(fb);

	pwane_state->uapi.cwtc = &cwtc->base;
	intew_pwane_copy_uapi_to_hw_state(pwane_state, pwane_state, cwtc);

	atomic_ow(pwane->fwontbuffew_bit, &to_intew_fwontbuffew(fb)->bits);

	pwane_config->vma = vma;

	/*
	 * Fwip to the newwy cweated mapping ASAP, so we can we-use the
	 * fiwst pawt of GGTT fow WOPCM, pwevent fwickewing, and pwevent
	 * the wookup of sysmem scwatch pages.
	 */
	pwane->check_pwane(cwtc_state, pwane_state);
	pwane->async_fwip(pwane, cwtc_state, pwane_state, twue);
	wetuwn;

nofb:
	/*
	 * We've faiwed to weconstwuct the BIOS FB.  Cuwwent dispway state
	 * indicates that the pwimawy pwane is visibwe, but has a NUWW FB,
	 * which wiww wead to pwobwems watew if we don't fix it up.  The
	 * simpwest sowution is to just disabwe the pwimawy pwane now and
	 * pwetend the BIOS nevew had it enabwed.
	 */
	intew_pwane_disabwe_noatomic(cwtc, pwane);
}

static void pwane_config_fini(stwuct intew_initiaw_pwane_config *pwane_config)
{
	if (pwane_config->fb) {
		stwuct dwm_fwamebuffew *fb = &pwane_config->fb->base;

		/* We may onwy have the stub and not a fuww fwamebuffew */
		if (dwm_fwamebuffew_wead_wefcount(fb))
			dwm_fwamebuffew_put(fb);
		ewse
			kfwee(fb);
	}
}

void intew_cwtc_initiaw_pwane_config(stwuct intew_cwtc *cwtc)
{
	stwuct xe_device *xe = to_xe_device(cwtc->base.dev);
	stwuct intew_initiaw_pwane_config pwane_config = {};

	/*
	 * Note that wesewving the BIOS fb up fwont pwevents us
	 * fwom stuffing othew stowen awwocations wike the wing
	 * on top.  This pwevents some ugwiness at boot time, and
	 * can even awwow fow smooth boot twansitions if the BIOS
	 * fb is wawge enough fow the active pipe configuwation.
	 */
	xe->dispway.funcs.dispway->get_initiaw_pwane_config(cwtc, &pwane_config);

	/*
	 * If the fb is shawed between muwtipwe heads, we'ww
	 * just get the fiwst one.
	 */
	intew_find_initiaw_pwane_obj(cwtc, &pwane_config);

	pwane_config_fini(&pwane_config);
}
