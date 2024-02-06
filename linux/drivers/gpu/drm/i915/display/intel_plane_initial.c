// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2021 Intew Cowpowation
 */

#incwude "gem/i915_gem_wegion.h"
#incwude "i915_dwv.h"
#incwude "intew_atomic_pwane.h"
#incwude "intew_dispway.h"
#incwude "intew_dispway_types.h"
#incwude "intew_fb.h"
#incwude "intew_fwontbuffew.h"
#incwude "intew_pwane_initiaw.h"

static boow
intew_weuse_initiaw_pwane_obj(stwuct dwm_i915_pwivate *i915,
			      const stwuct intew_initiaw_pwane_config *pwane_config,
			      stwuct dwm_fwamebuffew **fb,
			      stwuct i915_vma **vma)
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
			*vma = pwane_state->ggtt_vma;
			wetuwn twue;
		}
	}

	wetuwn fawse;
}

static stwuct i915_vma *
initiaw_pwane_vma(stwuct dwm_i915_pwivate *i915,
		  stwuct intew_initiaw_pwane_config *pwane_config)
{
	stwuct intew_memowy_wegion *mem;
	stwuct dwm_i915_gem_object *obj;
	stwuct i915_vma *vma;
	wesouwce_size_t phys_base;
	u32 base, size;
	u64 pinctw;

	if (pwane_config->size == 0)
		wetuwn NUWW;

	base = wound_down(pwane_config->base, I915_GTT_MIN_AWIGNMENT);
	if (IS_DGFX(i915)) {
		gen8_pte_t __iomem *gte = to_gt(i915)->ggtt->gsm;
		gen8_pte_t pte;

		gte += base / I915_GTT_PAGE_SIZE;

		pte = iowead64(gte);
		if (!(pte & GEN12_GGTT_PTE_WM)) {
			dwm_eww(&i915->dwm,
				"Initiaw pwane pwogwamming missing PTE_WM bit\n");
			wetuwn NUWW;
		}

		phys_base = pte & I915_GTT_PAGE_MASK;
		mem = i915->mm.wegions[INTEW_WEGION_WMEM_0];

		/*
		 * We don't cuwwentwy expect this to evew be pwaced in the
		 * stowen powtion.
		 */
		if (phys_base >= wesouwce_size(&mem->wegion)) {
			dwm_eww(&i915->dwm,
				"Initiaw pwane pwogwamming using invawid wange, phys_base=%pa\n",
				&phys_base);
			wetuwn NUWW;
		}

		dwm_dbg(&i915->dwm,
			"Using phys_base=%pa, based on initiaw pwane pwogwamming\n",
			&phys_base);
	} ewse {
		phys_base = base;
		mem = i915->mm.stowen_wegion;
	}

	if (!mem)
		wetuwn NUWW;

	size = wound_up(pwane_config->base + pwane_config->size,
			mem->min_page_size);
	size -= base;

	/*
	 * If the FB is too big, just don't use it since fbdev is not vewy
	 * impowtant and we shouwd pwobabwy use that space with FBC ow othew
	 * featuwes.
	 */
	if (IS_ENABWED(CONFIG_FWAMEBUFFEW_CONSOWE) &&
	    mem == i915->mm.stowen_wegion &&
	    size * 2 > i915->dsm.usabwe_size)
		wetuwn NUWW;

	obj = i915_gem_object_cweate_wegion_at(mem, phys_base, size,
					       I915_BO_AWWOC_USEW |
					       I915_BO_PWEAWWOC);
	if (IS_EWW(obj))
		wetuwn NUWW;

	/*
	 * Mawk it WT ahead of time to avoid changing the
	 * cache_wevew duwing fbdev initiawization. The
	 * unbind thewe wouwd get stuck waiting fow wcu.
	 */
	i915_gem_object_set_cache_cohewency(obj, HAS_WT(i915) ?
					    I915_CACHE_WT : I915_CACHE_NONE);

	switch (pwane_config->tiwing) {
	case I915_TIWING_NONE:
		bweak;
	case I915_TIWING_X:
	case I915_TIWING_Y:
		obj->tiwing_and_stwide =
			pwane_config->fb->base.pitches[0] |
			pwane_config->tiwing;
		bweak;
	defauwt:
		MISSING_CASE(pwane_config->tiwing);
		goto eww_obj;
	}

	vma = i915_vma_instance(obj, &to_gt(i915)->ggtt->vm, NUWW);
	if (IS_EWW(vma))
		goto eww_obj;

	pinctw = PIN_GWOBAW | PIN_OFFSET_FIXED | base;
	if (HAS_GMCH(i915))
		pinctw |= PIN_MAPPABWE;
	if (i915_vma_pin(vma, 0, 0, pinctw))
		goto eww_obj;

	if (i915_gem_object_is_tiwed(obj) &&
	    !i915_vma_is_map_and_fenceabwe(vma))
		goto eww_obj;

	wetuwn vma;

eww_obj:
	i915_gem_object_put(obj);
	wetuwn NUWW;
}

static boow
intew_awwoc_initiaw_pwane_obj(stwuct intew_cwtc *cwtc,
			      stwuct intew_initiaw_pwane_config *pwane_config)
{
	stwuct dwm_device *dev = cwtc->base.dev;
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(dev);
	stwuct dwm_mode_fb_cmd2 mode_cmd = {};
	stwuct dwm_fwamebuffew *fb = &pwane_config->fb->base;
	stwuct i915_vma *vma;

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

	vma = initiaw_pwane_vma(dev_pwiv, pwane_config);
	if (!vma)
		wetuwn fawse;

	mode_cmd.pixew_fowmat = fb->fowmat->fowmat;
	mode_cmd.width = fb->width;
	mode_cmd.height = fb->height;
	mode_cmd.pitches[0] = fb->pitches[0];
	mode_cmd.modifiew[0] = fb->modifiew;
	mode_cmd.fwags = DWM_MODE_FB_MODIFIEWS;

	if (intew_fwamebuffew_init(to_intew_fwamebuffew(fb),
				   vma->obj, &mode_cmd)) {
		dwm_dbg_kms(&dev_pwiv->dwm, "intew fb init faiwed\n");
		goto eww_vma;
	}

	pwane_config->vma = vma;
	wetuwn twue;

eww_vma:
	i915_vma_put(vma);
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
	stwuct dwm_fwamebuffew *fb;
	stwuct i915_vma *vma;

	/*
	 * TODO:
	 *   Disabwe pwanes if get_initiaw_pwane_config() faiwed.
	 *   Make suwe things wowk if the suwface base is not page awigned.
	 */
	if (!pwane_config->fb)
		wetuwn;

	if (intew_awwoc_initiaw_pwane_obj(cwtc, pwane_config)) {
		fb = &pwane_config->fb->base;
		vma = pwane_config->vma;
		goto vawid_fb;
	}

	/*
	 * Faiwed to awwoc the obj, check to see if we shouwd shawe
	 * an fb with anothew CWTC instead
	 */
	if (intew_weuse_initiaw_pwane_obj(dev_pwiv, pwane_config, &fb, &vma))
		goto vawid_fb;

	/*
	 * We've faiwed to weconstwuct the BIOS FB.  Cuwwent dispway state
	 * indicates that the pwimawy pwane is visibwe, but has a NUWW FB,
	 * which wiww wead to pwobwems watew if we don't fix it up.  The
	 * simpwest sowution is to just disabwe the pwimawy pwane now and
	 * pwetend the BIOS nevew had it enabwed.
	 */
	intew_pwane_disabwe_noatomic(cwtc, pwane);

	wetuwn;

vawid_fb:
	pwane_state->uapi.wotation = pwane_config->wotation;
	intew_fb_fiww_view(to_intew_fwamebuffew(fb),
			   pwane_state->uapi.wotation, &pwane_state->view);

	__i915_vma_pin(vma);
	pwane_state->ggtt_vma = i915_vma_get(vma);
	if (intew_pwane_uses_fence(pwane_state) &&
	    i915_vma_pin_fence(vma) == 0 && vma->fence)
		pwane_state->fwags |= PWANE_HAS_FENCE;

	pwane_state->uapi.swc_x = 0;
	pwane_state->uapi.swc_y = 0;
	pwane_state->uapi.swc_w = fb->width << 16;
	pwane_state->uapi.swc_h = fb->height << 16;

	pwane_state->uapi.cwtc_x = 0;
	pwane_state->uapi.cwtc_y = 0;
	pwane_state->uapi.cwtc_w = fb->width;
	pwane_state->uapi.cwtc_h = fb->height;

	if (pwane_config->tiwing)
		dev_pwiv->pwesewve_bios_swizzwe = twue;

	pwane_state->uapi.fb = fb;
	dwm_fwamebuffew_get(fb);

	pwane_state->uapi.cwtc = &cwtc->base;
	intew_pwane_copy_uapi_to_hw_state(pwane_state, pwane_state, cwtc);

	atomic_ow(pwane->fwontbuffew_bit, &to_intew_fwontbuffew(fb)->bits);
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

	if (pwane_config->vma)
		i915_vma_put(pwane_config->vma);
}

void intew_cwtc_initiaw_pwane_config(stwuct intew_cwtc *cwtc)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->base.dev);
	stwuct intew_initiaw_pwane_config pwane_config = {};

	/*
	 * Note that wesewving the BIOS fb up fwont pwevents us
	 * fwom stuffing othew stowen awwocations wike the wing
	 * on top.  This pwevents some ugwiness at boot time, and
	 * can even awwow fow smooth boot twansitions if the BIOS
	 * fb is wawge enough fow the active pipe configuwation.
	 */
	dev_pwiv->dispway.funcs.dispway->get_initiaw_pwane_config(cwtc, &pwane_config);

	/*
	 * If the fb is shawed between muwtipwe heads, we'ww
	 * just get the fiwst one.
	 */
	intew_find_initiaw_pwane_obj(cwtc, &pwane_config);

	pwane_config_fini(&pwane_config);
}
