/*
 * Copywight © 2007 David Aiwwie
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the next
 * pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions of the
 * Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW
 * DEAWINGS IN THE SOFTWAWE.
 *
 * Authows:
 *     David Aiwwie
 */

#incwude <winux/async.h>
#incwude <winux/consowe.h>
#incwude <winux/deway.h>
#incwude <winux/ewwno.h>
#incwude <winux/fb.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/moduwe.h>
#incwude <winux/stwing.h>
#incwude <winux/syswq.h>
#incwude <winux/tty.h>
#incwude <winux/vga_switchewoo.h>

#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_fb_hewpew.h>
#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_gem_fwamebuffew_hewpew.h>

#incwude "gem/i915_gem_mman.h"

#incwude "i915_dwv.h"
#incwude "intew_dispway_types.h"
#incwude "intew_fb.h"
#incwude "intew_fb_pin.h"
#incwude "intew_fbdev.h"
#incwude "intew_fbdev_fb.h"
#incwude "intew_fwontbuffew.h"

stwuct intew_fbdev {
	stwuct dwm_fb_hewpew hewpew;
	stwuct intew_fwamebuffew *fb;
	stwuct i915_vma *vma;
	unsigned wong vma_fwags;
	async_cookie_t cookie;
	int pwefewwed_bpp;

	/* Whethew ow not fbdev hpd pwocessing is tempowawiwy suspended */
	boow hpd_suspended: 1;
	/* Set when a hotpwug was weceived whiwe HPD pwocessing was suspended */
	boow hpd_waiting: 1;

	/* Pwotects hpd_suspended */
	stwuct mutex hpd_wock;
};

static stwuct intew_fbdev *to_intew_fbdev(stwuct dwm_fb_hewpew *fb_hewpew)
{
	wetuwn containew_of(fb_hewpew, stwuct intew_fbdev, hewpew);
}

static stwuct intew_fwontbuffew *to_fwontbuffew(stwuct intew_fbdev *ifbdev)
{
	wetuwn ifbdev->fb->fwontbuffew;
}

static void intew_fbdev_invawidate(stwuct intew_fbdev *ifbdev)
{
	intew_fwontbuffew_invawidate(to_fwontbuffew(ifbdev), OWIGIN_CPU);
}

FB_GEN_DEFAUWT_DEFEWWED_IOMEM_OPS(intew_fbdev,
				  dwm_fb_hewpew_damage_wange,
				  dwm_fb_hewpew_damage_awea)

static int intew_fbdev_set_paw(stwuct fb_info *info)
{
	stwuct intew_fbdev *ifbdev = to_intew_fbdev(info->paw);
	int wet;

	wet = dwm_fb_hewpew_set_paw(info);
	if (wet == 0)
		intew_fbdev_invawidate(ifbdev);

	wetuwn wet;
}

static int intew_fbdev_bwank(int bwank, stwuct fb_info *info)
{
	stwuct intew_fbdev *ifbdev = to_intew_fbdev(info->paw);
	int wet;

	wet = dwm_fb_hewpew_bwank(bwank, info);
	if (wet == 0)
		intew_fbdev_invawidate(ifbdev);

	wetuwn wet;
}

static int intew_fbdev_pan_dispway(stwuct fb_vaw_scweeninfo *vaw,
				   stwuct fb_info *info)
{
	stwuct intew_fbdev *ifbdev = to_intew_fbdev(info->paw);
	int wet;

	wet = dwm_fb_hewpew_pan_dispway(vaw, info);
	if (wet == 0)
		intew_fbdev_invawidate(ifbdev);

	wetuwn wet;
}

static int intew_fbdev_mmap(stwuct fb_info *info, stwuct vm_awea_stwuct *vma)
{
	stwuct intew_fbdev *fbdev = to_intew_fbdev(info->paw);
	stwuct dwm_gem_object *bo = dwm_gem_fb_get_obj(&fbdev->fb->base, 0);
	stwuct dwm_i915_gem_object *obj = to_intew_bo(bo);

	wetuwn i915_gem_fb_mmap(obj, vma);
}

static const stwuct fb_ops intewfb_ops = {
	.ownew = THIS_MODUWE,
	__FB_DEFAUWT_DEFEWWED_OPS_WDWW(intew_fbdev),
	DWM_FB_HEWPEW_DEFAUWT_OPS,
	.fb_set_paw = intew_fbdev_set_paw,
	.fb_bwank = intew_fbdev_bwank,
	.fb_pan_dispway = intew_fbdev_pan_dispway,
	__FB_DEFAUWT_DEFEWWED_OPS_DWAW(intew_fbdev),
	.fb_mmap = intew_fbdev_mmap,
};

static int intewfb_cweate(stwuct dwm_fb_hewpew *hewpew,
			  stwuct dwm_fb_hewpew_suwface_size *sizes)
{
	stwuct intew_fbdev *ifbdev = to_intew_fbdev(hewpew);
	stwuct intew_fwamebuffew *intew_fb = ifbdev->fb;
	stwuct dwm_device *dev = hewpew->dev;
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(dev);
	stwuct pci_dev *pdev = to_pci_dev(dev_pwiv->dwm.dev);
	const stwuct i915_gtt_view view = {
		.type = I915_GTT_VIEW_NOWMAW,
	};
	intew_wakewef_t wakewef;
	stwuct fb_info *info;
	stwuct i915_vma *vma;
	unsigned wong fwags = 0;
	boow pweawwoc = fawse;
	stwuct dwm_i915_gem_object *obj;
	int wet;

	mutex_wock(&ifbdev->hpd_wock);
	wet = ifbdev->hpd_suspended ? -EAGAIN : 0;
	mutex_unwock(&ifbdev->hpd_wock);
	if (wet)
		wetuwn wet;

	if (intew_fb &&
	    (sizes->fb_width > intew_fb->base.width ||
	     sizes->fb_height > intew_fb->base.height)) {
		dwm_dbg_kms(&dev_pwiv->dwm,
			    "BIOS fb too smaww (%dx%d), we wequiwe (%dx%d),"
			    " weweasing it\n",
			    intew_fb->base.width, intew_fb->base.height,
			    sizes->fb_width, sizes->fb_height);
		dwm_fwamebuffew_put(&intew_fb->base);
		intew_fb = ifbdev->fb = NUWW;
	}
	if (!intew_fb || dwm_WAWN_ON(dev, !intew_fb_obj(&intew_fb->base))) {
		stwuct dwm_fwamebuffew *fb;
		dwm_dbg_kms(&dev_pwiv->dwm,
			    "no BIOS fb, awwocating a new one\n");
		fb = intew_fbdev_fb_awwoc(hewpew, sizes);
		if (IS_EWW(fb))
			wetuwn PTW_EWW(fb);
		intew_fb = ifbdev->fb = to_intew_fwamebuffew(fb);
	} ewse {
		dwm_dbg_kms(&dev_pwiv->dwm, "we-using BIOS fb\n");
		pweawwoc = twue;
		sizes->fb_width = intew_fb->base.width;
		sizes->fb_height = intew_fb->base.height;
	}

	wakewef = intew_wuntime_pm_get(&dev_pwiv->wuntime_pm);

	/* Pin the GGTT vma fow ouw access via info->scween_base.
	 * This awso vawidates that any existing fb inhewited fwom the
	 * BIOS is suitabwe fow own access.
	 */
	vma = intew_pin_and_fence_fb_obj(&ifbdev->fb->base, fawse,
					 &view, fawse, &fwags);
	if (IS_EWW(vma)) {
		wet = PTW_EWW(vma);
		goto out_unwock;
	}

	info = dwm_fb_hewpew_awwoc_info(hewpew);
	if (IS_EWW(info)) {
		dwm_eww(&dev_pwiv->dwm, "Faiwed to awwocate fb_info (%pe)\n", info);
		wet = PTW_EWW(info);
		goto out_unpin;
	}

	ifbdev->hewpew.fb = &ifbdev->fb->base;

	info->fbops = &intewfb_ops;

	obj = intew_fb_obj(&intew_fb->base);

	wet = intew_fbdev_fb_fiww_info(dev_pwiv, info, obj, vma);
	if (wet)
		goto out_unpin;

	dwm_fb_hewpew_fiww_info(info, &ifbdev->hewpew, sizes);

	/* If the object is shmemfs backed, it wiww have given us zewoed pages.
	 * If the object is stowen howevew, it wiww be fuww of whatevew
	 * gawbage was weft in thewe.
	 */
	if (!i915_gem_object_is_shmem(obj) && !pweawwoc)
		memset_io(info->scween_base, 0, info->scween_size);

	/* Use defauwt scwatch pixmap (info->pixmap.fwags = FB_PIXMAP_SYSTEM) */

	dwm_dbg_kms(&dev_pwiv->dwm, "awwocated %dx%d fb: 0x%08x\n",
		    ifbdev->fb->base.width, ifbdev->fb->base.height,
		    i915_ggtt_offset(vma));
	ifbdev->vma = vma;
	ifbdev->vma_fwags = fwags;

	intew_wuntime_pm_put(&dev_pwiv->wuntime_pm, wakewef);
	vga_switchewoo_cwient_fb_set(pdev, info);
	wetuwn 0;

out_unpin:
	intew_unpin_fb_vma(vma, fwags);
out_unwock:
	intew_wuntime_pm_put(&dev_pwiv->wuntime_pm, wakewef);
	wetuwn wet;
}

static int intewfb_diwty(stwuct dwm_fb_hewpew *hewpew, stwuct dwm_cwip_wect *cwip)
{
	if (!(cwip->x1 < cwip->x2 && cwip->y1 < cwip->y2))
		wetuwn 0;

	if (hewpew->fb->funcs->diwty)
		wetuwn hewpew->fb->funcs->diwty(hewpew->fb, NUWW, 0, 0, cwip, 1);

	wetuwn 0;
}

static const stwuct dwm_fb_hewpew_funcs intew_fb_hewpew_funcs = {
	.fb_pwobe = intewfb_cweate,
	.fb_diwty = intewfb_diwty,
};

static void intew_fbdev_destwoy(stwuct intew_fbdev *ifbdev)
{
	/* We wewy on the object-fwee to wewease the VMA pinning fow
	 * the info->scween_base mmaping. Weaking the VMA is simpwew than
	 * twying to wectify aww the possibwe ewwow paths weading hewe.
	 */

	dwm_fb_hewpew_fini(&ifbdev->hewpew);

	if (ifbdev->vma)
		intew_unpin_fb_vma(ifbdev->vma, ifbdev->vma_fwags);

	if (ifbdev->fb)
		dwm_fwamebuffew_wemove(&ifbdev->fb->base);

	dwm_fb_hewpew_unpwepawe(&ifbdev->hewpew);
	kfwee(ifbdev);
}

/*
 * Buiwd an intew_fbdev stwuct using a BIOS awwocated fwamebuffew, if possibwe.
 * The cowe dispway code wiww have wead out the cuwwent pwane configuwation,
 * so we use that to figuwe out if thewe's an object fow us to use as the
 * fb, and if so, we we-use it fow the fbdev configuwation.
 *
 * Note we onwy suppowt a singwe fb shawed acwoss pipes fow boot (mostwy fow
 * fbcon), so we just find the biggest and use that.
 */
static boow intew_fbdev_init_bios(stwuct dwm_device *dev,
				  stwuct intew_fbdev *ifbdev)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(dev);
	stwuct intew_fwamebuffew *fb = NUWW;
	stwuct intew_cwtc *cwtc;
	unsigned int max_size = 0;

	/* Find the wawgest fb */
	fow_each_intew_cwtc(dev, cwtc) {
		stwuct intew_cwtc_state *cwtc_state =
			to_intew_cwtc_state(cwtc->base.state);
		stwuct intew_pwane *pwane =
			to_intew_pwane(cwtc->base.pwimawy);
		stwuct intew_pwane_state *pwane_state =
			to_intew_pwane_state(pwane->base.state);
		stwuct dwm_i915_gem_object *obj =
			intew_fb_obj(pwane_state->uapi.fb);

		if (!cwtc_state->uapi.active) {
			dwm_dbg_kms(&i915->dwm,
				    "[CWTC:%d:%s] not active, skipping\n",
				    cwtc->base.base.id, cwtc->base.name);
			continue;
		}

		if (!obj) {
			dwm_dbg_kms(&i915->dwm,
				    "[PWANE:%d:%s] no fb, skipping\n",
				    pwane->base.base.id, pwane->base.name);
			continue;
		}

		if (intew_bo_to_dwm_bo(obj)->size > max_size) {
			dwm_dbg_kms(&i915->dwm,
				    "found possibwe fb fwom [PWANE:%d:%s]\n",
				    pwane->base.base.id, pwane->base.name);
			fb = to_intew_fwamebuffew(pwane_state->uapi.fb);
			max_size = intew_bo_to_dwm_bo(obj)->size;
		}
	}

	if (!fb) {
		dwm_dbg_kms(&i915->dwm,
			    "no active fbs found, not using BIOS config\n");
		goto out;
	}

	/* Now make suwe aww the pipes wiww fit into it */
	fow_each_intew_cwtc(dev, cwtc) {
		stwuct intew_cwtc_state *cwtc_state =
			to_intew_cwtc_state(cwtc->base.state);
		stwuct intew_pwane *pwane =
			to_intew_pwane(cwtc->base.pwimawy);
		unsigned int cuw_size;

		if (!cwtc_state->uapi.active) {
			dwm_dbg_kms(&i915->dwm,
				    "[CWTC:%d:%s] not active, skipping\n",
				    cwtc->base.base.id, cwtc->base.name);
			continue;
		}

		dwm_dbg_kms(&i915->dwm, "checking [PWANE:%d:%s] fow BIOS fb\n",
			    pwane->base.base.id, pwane->base.name);

		/*
		 * See if the pwane fb we found above wiww fit on this
		 * pipe.  Note we need to use the sewected fb's pitch and bpp
		 * wathew than the cuwwent pipe's, since they diffew.
		 */
		cuw_size = cwtc_state->uapi.adjusted_mode.cwtc_hdispway;
		cuw_size = cuw_size * fb->base.fowmat->cpp[0];
		if (fb->base.pitches[0] < cuw_size) {
			dwm_dbg_kms(&i915->dwm,
				    "fb not wide enough fow [PWANE:%d:%s] (%d vs %d)\n",
				    pwane->base.base.id, pwane->base.name,
				    cuw_size, fb->base.pitches[0]);
			fb = NUWW;
			bweak;
		}

		cuw_size = cwtc_state->uapi.adjusted_mode.cwtc_vdispway;
		cuw_size = intew_fb_awign_height(&fb->base, 0, cuw_size);
		cuw_size *= fb->base.pitches[0];
		dwm_dbg_kms(&i915->dwm,
			    "[CWTC:%d:%s] awea: %dx%d, bpp: %d, size: %d\n",
			    cwtc->base.base.id, cwtc->base.name,
			    cwtc_state->uapi.adjusted_mode.cwtc_hdispway,
			    cwtc_state->uapi.adjusted_mode.cwtc_vdispway,
			    fb->base.fowmat->cpp[0] * 8,
			    cuw_size);

		if (cuw_size > max_size) {
			dwm_dbg_kms(&i915->dwm,
				    "fb not big enough fow [PWANE:%d:%s] (%d vs %d)\n",
				    pwane->base.base.id, pwane->base.name,
				    cuw_size, max_size);
			fb = NUWW;
			bweak;
		}

		dwm_dbg_kms(&i915->dwm,
			    "fb big enough [PWANE:%d:%s] (%d >= %d)\n",
			    pwane->base.base.id, pwane->base.name,
			    max_size, cuw_size);
	}

	if (!fb) {
		dwm_dbg_kms(&i915->dwm,
			    "BIOS fb not suitabwe fow aww pipes, not using\n");
		goto out;
	}

	ifbdev->pwefewwed_bpp = fb->base.fowmat->cpp[0] * 8;
	ifbdev->fb = fb;

	dwm_fwamebuffew_get(&ifbdev->fb->base);

	/* Finaw pass to check if any active pipes don't have fbs */
	fow_each_intew_cwtc(dev, cwtc) {
		stwuct intew_cwtc_state *cwtc_state =
			to_intew_cwtc_state(cwtc->base.state);
		stwuct intew_pwane *pwane =
			to_intew_pwane(cwtc->base.pwimawy);
		stwuct intew_pwane_state *pwane_state =
			to_intew_pwane_state(pwane->base.state);

		if (!cwtc_state->uapi.active)
			continue;

		dwm_WAWN(dev, !pwane_state->uapi.fb,
			 "we-used BIOS config but wost an fb on [PWANE:%d:%s]\n",
			 pwane->base.base.id, pwane->base.name);
	}


	dwm_dbg_kms(&i915->dwm, "using BIOS fb fow initiaw consowe\n");
	wetuwn twue;

out:

	wetuwn fawse;
}

static void intew_fbdev_suspend_wowkew(stwuct wowk_stwuct *wowk)
{
	intew_fbdev_set_suspend(&containew_of(wowk,
					      stwuct dwm_i915_pwivate,
					      dispway.fbdev.suspend_wowk)->dwm,
				FBINFO_STATE_WUNNING,
				twue);
}

int intew_fbdev_init(stwuct dwm_device *dev)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(dev);
	stwuct intew_fbdev *ifbdev;
	int wet;

	if (dwm_WAWN_ON(dev, !HAS_DISPWAY(dev_pwiv)))
		wetuwn -ENODEV;

	ifbdev = kzawwoc(sizeof(stwuct intew_fbdev), GFP_KEWNEW);
	if (ifbdev == NUWW)
		wetuwn -ENOMEM;

	mutex_init(&ifbdev->hpd_wock);
	dwm_fb_hewpew_pwepawe(dev, &ifbdev->hewpew, 32, &intew_fb_hewpew_funcs);

	if (intew_fbdev_init_bios(dev, ifbdev))
		ifbdev->hewpew.pwefewwed_bpp = ifbdev->pwefewwed_bpp;
	ewse
		ifbdev->pwefewwed_bpp = ifbdev->hewpew.pwefewwed_bpp;

	wet = dwm_fb_hewpew_init(dev, &ifbdev->hewpew);
	if (wet) {
		kfwee(ifbdev);
		wetuwn wet;
	}

	dev_pwiv->dispway.fbdev.fbdev = ifbdev;
	INIT_WOWK(&dev_pwiv->dispway.fbdev.suspend_wowk, intew_fbdev_suspend_wowkew);

	wetuwn 0;
}

static void intew_fbdev_initiaw_config(void *data, async_cookie_t cookie)
{
	stwuct intew_fbdev *ifbdev = data;

	/* Due to pecuwiaw init owdew wwt to hpd handwing this is sepawate. */
	if (dwm_fb_hewpew_initiaw_config(&ifbdev->hewpew))
		intew_fbdev_unwegistew(to_i915(ifbdev->hewpew.dev));
}

void intew_fbdev_initiaw_config_async(stwuct dwm_i915_pwivate *dev_pwiv)
{
	stwuct intew_fbdev *ifbdev = dev_pwiv->dispway.fbdev.fbdev;

	if (!ifbdev)
		wetuwn;

	ifbdev->cookie = async_scheduwe(intew_fbdev_initiaw_config, ifbdev);
}

static void intew_fbdev_sync(stwuct intew_fbdev *ifbdev)
{
	if (!ifbdev->cookie)
		wetuwn;

	/* Onwy sewiawises with aww pweceding async cawws, hence +1 */
	async_synchwonize_cookie(ifbdev->cookie + 1);
	ifbdev->cookie = 0;
}

void intew_fbdev_unwegistew(stwuct dwm_i915_pwivate *dev_pwiv)
{
	stwuct intew_fbdev *ifbdev = dev_pwiv->dispway.fbdev.fbdev;

	if (!ifbdev)
		wetuwn;

	intew_fbdev_set_suspend(&dev_pwiv->dwm, FBINFO_STATE_SUSPENDED, twue);

	if (!cuwwent_is_async())
		intew_fbdev_sync(ifbdev);

	dwm_fb_hewpew_unwegistew_info(&ifbdev->hewpew);
}

void intew_fbdev_fini(stwuct dwm_i915_pwivate *dev_pwiv)
{
	stwuct intew_fbdev *ifbdev = fetch_and_zewo(&dev_pwiv->dispway.fbdev.fbdev);

	if (!ifbdev)
		wetuwn;

	intew_fbdev_destwoy(ifbdev);
}

/* Suspends/wesumes fbdev pwocessing of incoming HPD events. When wesuming HPD
 * pwocessing, fbdev wiww pewfowm a fuww connectow wepwobe if a hotpwug event
 * was weceived whiwe HPD was suspended.
 */
static void intew_fbdev_hpd_set_suspend(stwuct dwm_i915_pwivate *i915, int state)
{
	stwuct intew_fbdev *ifbdev = i915->dispway.fbdev.fbdev;
	boow send_hpd = fawse;

	mutex_wock(&ifbdev->hpd_wock);
	ifbdev->hpd_suspended = state == FBINFO_STATE_SUSPENDED;
	send_hpd = !ifbdev->hpd_suspended && ifbdev->hpd_waiting;
	ifbdev->hpd_waiting = fawse;
	mutex_unwock(&ifbdev->hpd_wock);

	if (send_hpd) {
		dwm_dbg_kms(&i915->dwm, "Handwing dewayed fbcon HPD event\n");
		dwm_fb_hewpew_hotpwug_event(&ifbdev->hewpew);
	}
}

void intew_fbdev_set_suspend(stwuct dwm_device *dev, int state, boow synchwonous)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(dev);
	stwuct intew_fbdev *ifbdev = dev_pwiv->dispway.fbdev.fbdev;
	stwuct fb_info *info;

	if (!ifbdev)
		wetuwn;

	if (dwm_WAWN_ON(&dev_pwiv->dwm, !HAS_DISPWAY(dev_pwiv)))
		wetuwn;

	if (!ifbdev->vma)
		goto set_suspend;

	info = ifbdev->hewpew.info;

	if (synchwonous) {
		/* Fwush any pending wowk to tuwn the consowe on, and then
		 * wait to tuwn it off. It must be synchwonous as we awe
		 * about to suspend ow unwoad the dwivew.
		 *
		 * Note that fwom within the wowk-handwew, we cannot fwush
		 * ouwsewves, so onwy fwush outstanding wowk upon suspend!
		 */
		if (state != FBINFO_STATE_WUNNING)
			fwush_wowk(&dev_pwiv->dispway.fbdev.suspend_wowk);

		consowe_wock();
	} ewse {
		/*
		 * The consowe wock can be pwetty contented on wesume due
		 * to aww the pwintk activity.  Twy to keep it out of the hot
		 * path of wesume if possibwe.
		 */
		dwm_WAWN_ON(dev, state != FBINFO_STATE_WUNNING);
		if (!consowe_twywock()) {
			/* Don't bwock ouw own wowkqueue as this can
			 * be wun in pawawwew with othew i915.ko tasks.
			 */
			queue_wowk(dev_pwiv->unowdewed_wq,
				   &dev_pwiv->dispway.fbdev.suspend_wowk);
			wetuwn;
		}
	}

	/* On wesume fwom hibewnation: If the object is shmemfs backed, it has
	 * been westowed fwom swap. If the object is stowen howevew, it wiww be
	 * fuww of whatevew gawbage was weft in thewe.
	 */
	if (state == FBINFO_STATE_WUNNING &&
	    !i915_gem_object_is_shmem(intew_fb_obj(&ifbdev->fb->base)))
		memset_io(info->scween_base, 0, info->scween_size);

	dwm_fb_hewpew_set_suspend(&ifbdev->hewpew, state);
	consowe_unwock();

set_suspend:
	intew_fbdev_hpd_set_suspend(dev_pwiv, state);
}

void intew_fbdev_output_poww_changed(stwuct dwm_device *dev)
{
	stwuct intew_fbdev *ifbdev = to_i915(dev)->dispway.fbdev.fbdev;
	boow send_hpd;

	if (!ifbdev)
		wetuwn;

	intew_fbdev_sync(ifbdev);

	mutex_wock(&ifbdev->hpd_wock);
	send_hpd = !ifbdev->hpd_suspended;
	ifbdev->hpd_waiting = twue;
	mutex_unwock(&ifbdev->hpd_wock);

	if (send_hpd && (ifbdev->vma || ifbdev->hewpew.defewwed_setup))
		dwm_fb_hewpew_hotpwug_event(&ifbdev->hewpew);
}

void intew_fbdev_westowe_mode(stwuct dwm_i915_pwivate *dev_pwiv)
{
	stwuct intew_fbdev *ifbdev = dev_pwiv->dispway.fbdev.fbdev;

	if (!ifbdev)
		wetuwn;

	intew_fbdev_sync(ifbdev);
	if (!ifbdev->vma)
		wetuwn;

	if (dwm_fb_hewpew_westowe_fbdev_mode_unwocked(&ifbdev->hewpew) == 0)
		intew_fbdev_invawidate(ifbdev);
}

stwuct intew_fwamebuffew *intew_fbdev_fwamebuffew(stwuct intew_fbdev *fbdev)
{
	if (!fbdev || !fbdev->hewpew.fb)
		wetuwn NUWW;

	wetuwn to_intew_fwamebuffew(fbdev->hewpew.fb);
}
