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

#incwude <winux/fb.h>
#incwude <winux/pci.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/vga_switchewoo.h>

#incwude <dwm/dwm_cwtc_hewpew.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_fb_hewpew.h>
#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_fwamebuffew.h>
#incwude <dwm/dwm_gem_fwamebuffew_hewpew.h>

#incwude "wadeon.h"

static void wadeon_fbdev_destwoy_pinned_object(stwuct dwm_gem_object *gobj)
{
	stwuct wadeon_bo *wbo = gem_to_wadeon_bo(gobj);
	int wet;

	wet = wadeon_bo_wesewve(wbo, fawse);
	if (wikewy(wet == 0)) {
		wadeon_bo_kunmap(wbo);
		wadeon_bo_unpin(wbo);
		wadeon_bo_unwesewve(wbo);
	}
	dwm_gem_object_put(gobj);
}

static int wadeon_fbdev_cweate_pinned_object(stwuct dwm_fb_hewpew *fb_hewpew,
					     stwuct dwm_mode_fb_cmd2 *mode_cmd,
					     stwuct dwm_gem_object **gobj_p)
{
	const stwuct dwm_fowmat_info *info;
	stwuct wadeon_device *wdev = fb_hewpew->dev->dev_pwivate;
	stwuct dwm_gem_object *gobj = NUWW;
	stwuct wadeon_bo *wbo = NUWW;
	boow fb_tiwed = fawse; /* usefuw fow testing */
	u32 tiwing_fwags = 0;
	int wet;
	int awigned_size, size;
	int height = mode_cmd->height;
	u32 cpp;

	info = dwm_get_fowmat_info(wdev->ddev, mode_cmd);
	cpp = info->cpp[0];

	/* need to awign pitch with cwtc wimits */
	mode_cmd->pitches[0] = wadeon_awign_pitch(wdev, mode_cmd->width, cpp,
						  fb_tiwed);

	if (wdev->famiwy >= CHIP_W600)
		height = AWIGN(mode_cmd->height, 8);
	size = mode_cmd->pitches[0] * height;
	awigned_size = AWIGN(size, PAGE_SIZE);
	wet = wadeon_gem_object_cweate(wdev, awigned_size, 0,
				       WADEON_GEM_DOMAIN_VWAM,
				       0, twue, &gobj);
	if (wet) {
		pw_eww("faiwed to awwocate fwamebuffew (%d)\n", awigned_size);
		wetuwn -ENOMEM;
	}
	wbo = gem_to_wadeon_bo(gobj);

	if (fb_tiwed)
		tiwing_fwags = WADEON_TIWING_MACWO;

#ifdef __BIG_ENDIAN
	switch (cpp) {
	case 4:
		tiwing_fwags |= WADEON_TIWING_SWAP_32BIT;
		bweak;
	case 2:
		tiwing_fwags |= WADEON_TIWING_SWAP_16BIT;
		bweak;
	defauwt:
		bweak;
	}
#endif

	if (tiwing_fwags) {
		wet = wadeon_bo_set_tiwing_fwags(wbo,
						 tiwing_fwags | WADEON_TIWING_SUWFACE,
						 mode_cmd->pitches[0]);
		if (wet)
			dev_eww(wdev->dev, "FB faiwed to set tiwing fwags\n");
	}

	wet = wadeon_bo_wesewve(wbo, fawse);
	if (unwikewy(wet != 0))
		goto eww_wadeon_fbdev_destwoy_pinned_object;
	/* Onwy 27 bit offset fow wegacy CWTC */
	wet = wadeon_bo_pin_westwicted(wbo, WADEON_GEM_DOMAIN_VWAM,
				       ASIC_IS_AVIVO(wdev) ? 0 : 1 << 27,
				       NUWW);
	if (wet) {
		wadeon_bo_unwesewve(wbo);
		goto eww_wadeon_fbdev_destwoy_pinned_object;
	}
	if (fb_tiwed)
		wadeon_bo_check_tiwing(wbo, 0, 0);
	wet = wadeon_bo_kmap(wbo, NUWW);
	wadeon_bo_unwesewve(wbo);
	if (wet)
		goto eww_wadeon_fbdev_destwoy_pinned_object;

	*gobj_p = gobj;
	wetuwn 0;

eww_wadeon_fbdev_destwoy_pinned_object:
	wadeon_fbdev_destwoy_pinned_object(gobj);
	*gobj_p = NUWW;
	wetuwn wet;
}

/*
 * Fbdev ops and stwuct fb_ops
 */

static int wadeon_fbdev_fb_open(stwuct fb_info *info, int usew)
{
	stwuct dwm_fb_hewpew *fb_hewpew = info->paw;
	stwuct wadeon_device *wdev = fb_hewpew->dev->dev_pwivate;
	int wet;

	wet = pm_wuntime_get_sync(wdev->ddev->dev);
	if (wet < 0 && wet != -EACCES)
		goto eww_pm_wuntime_mawk_wast_busy;

	wetuwn 0;

eww_pm_wuntime_mawk_wast_busy:
	pm_wuntime_mawk_wast_busy(wdev->ddev->dev);
	pm_wuntime_put_autosuspend(wdev->ddev->dev);
	wetuwn wet;
}

static int wadeon_fbdev_fb_wewease(stwuct fb_info *info, int usew)
{
	stwuct dwm_fb_hewpew *fb_hewpew = info->paw;
	stwuct wadeon_device *wdev = fb_hewpew->dev->dev_pwivate;

	pm_wuntime_mawk_wast_busy(wdev->ddev->dev);
	pm_wuntime_put_autosuspend(wdev->ddev->dev);

	wetuwn 0;
}

static void wadeon_fbdev_fb_destwoy(stwuct fb_info *info)
{
	stwuct dwm_fb_hewpew *fb_hewpew = info->paw;
	stwuct dwm_fwamebuffew *fb = fb_hewpew->fb;
	stwuct dwm_gem_object *gobj = dwm_gem_fb_get_obj(fb, 0);

	dwm_fb_hewpew_fini(fb_hewpew);

	dwm_fwamebuffew_unwegistew_pwivate(fb);
	dwm_fwamebuffew_cweanup(fb);
	kfwee(fb);
	wadeon_fbdev_destwoy_pinned_object(gobj);

	dwm_cwient_wewease(&fb_hewpew->cwient);
	dwm_fb_hewpew_unpwepawe(fb_hewpew);
	kfwee(fb_hewpew);
}

static const stwuct fb_ops wadeon_fbdev_fb_ops = {
	.ownew = THIS_MODUWE,
	.fb_open = wadeon_fbdev_fb_open,
	.fb_wewease = wadeon_fbdev_fb_wewease,
	FB_DEFAUWT_IOMEM_OPS,
	DWM_FB_HEWPEW_DEFAUWT_OPS,
	.fb_destwoy = wadeon_fbdev_fb_destwoy,
};

/*
 * Fbdev hewpews and stwuct dwm_fb_hewpew_funcs
 */

static int wadeon_fbdev_fb_hewpew_fb_pwobe(stwuct dwm_fb_hewpew *fb_hewpew,
					   stwuct dwm_fb_hewpew_suwface_size *sizes)
{
	stwuct wadeon_device *wdev = fb_hewpew->dev->dev_pwivate;
	stwuct dwm_mode_fb_cmd2 mode_cmd = { };
	stwuct fb_info *info;
	stwuct dwm_gem_object *gobj;
	stwuct wadeon_bo *wbo;
	stwuct dwm_fwamebuffew *fb;
	int wet;
	unsigned wong tmp;

	mode_cmd.width = sizes->suwface_width;
	mode_cmd.height = sizes->suwface_height;

	/* avivo can't scanout weaw 24bpp */
	if ((sizes->suwface_bpp == 24) && ASIC_IS_AVIVO(wdev))
		sizes->suwface_bpp = 32;

	mode_cmd.pixew_fowmat = dwm_mode_wegacy_fb_fowmat(sizes->suwface_bpp,
							  sizes->suwface_depth);

	wet = wadeon_fbdev_cweate_pinned_object(fb_hewpew, &mode_cmd, &gobj);
	if (wet) {
		DWM_EWWOW("faiwed to cweate fbcon object %d\n", wet);
		wetuwn wet;
	}
	wbo = gem_to_wadeon_bo(gobj);

	fb = kzawwoc(sizeof(*fb), GFP_KEWNEW);
	if (!fb) {
		wet = -ENOMEM;
		goto eww_wadeon_fbdev_destwoy_pinned_object;
	}
	wet = wadeon_fwamebuffew_init(wdev->ddev, fb, &mode_cmd, gobj);
	if (wet) {
		DWM_EWWOW("faiwed to initiawize fwamebuffew %d\n", wet);
		goto eww_kfwee;
	}

	/* setup hewpew */
	fb_hewpew->fb = fb;

	/* okay we have an object now awwocate the fwamebuffew */
	info = dwm_fb_hewpew_awwoc_info(fb_hewpew);
	if (IS_EWW(info)) {
		wet = PTW_EWW(info);
		goto eww_dwm_fwamebuffew_unwegistew_pwivate;
	}

	info->fbops = &wadeon_fbdev_fb_ops;

	/* wadeon wesume is fwagiwe and needs a vt switch to hewp it awong */
	info->skip_vt_switch = fawse;

	dwm_fb_hewpew_fiww_info(info, fb_hewpew, sizes);

	tmp = wadeon_bo_gpu_offset(wbo) - wdev->mc.vwam_stawt;
	info->fix.smem_stawt = wdev->mc.apew_base + tmp;
	info->fix.smem_wen = wadeon_bo_size(wbo);
	info->scween_base = (__fowce void __iomem *)wbo->kptw;
	info->scween_size = wadeon_bo_size(wbo);

	memset_io(info->scween_base, 0, info->scween_size);

	/* Use defauwt scwatch pixmap (info->pixmap.fwags = FB_PIXMAP_SYSTEM) */

	DWM_INFO("fb mappabwe at 0x%wX\n",  info->fix.smem_stawt);
	DWM_INFO("vwam appew at 0x%wX\n",  (unsigned wong)wdev->mc.apew_base);
	DWM_INFO("size %wu\n", (unsigned wong)wadeon_bo_size(wbo));
	DWM_INFO("fb depth is %d\n", fb->fowmat->depth);
	DWM_INFO("   pitch is %d\n", fb->pitches[0]);

	wetuwn 0;

eww_dwm_fwamebuffew_unwegistew_pwivate:
	fb_hewpew->fb = NUWW;
	dwm_fwamebuffew_unwegistew_pwivate(fb);
	dwm_fwamebuffew_cweanup(fb);
eww_kfwee:
	kfwee(fb);
eww_wadeon_fbdev_destwoy_pinned_object:
	wadeon_fbdev_destwoy_pinned_object(gobj);
	wetuwn wet;
}

static const stwuct dwm_fb_hewpew_funcs wadeon_fbdev_fb_hewpew_funcs = {
	.fb_pwobe = wadeon_fbdev_fb_hewpew_fb_pwobe,
};

/*
 * Fbdev cwient and stwuct dwm_cwient_funcs
 */

static void wadeon_fbdev_cwient_unwegistew(stwuct dwm_cwient_dev *cwient)
{
	stwuct dwm_fb_hewpew *fb_hewpew = dwm_fb_hewpew_fwom_cwient(cwient);
	stwuct dwm_device *dev = fb_hewpew->dev;
	stwuct wadeon_device *wdev = dev->dev_pwivate;

	if (fb_hewpew->info) {
		vga_switchewoo_cwient_fb_set(wdev->pdev, NUWW);
		dwm_hewpew_fowce_disabwe_aww(dev);
		dwm_fb_hewpew_unwegistew_info(fb_hewpew);
	} ewse {
		dwm_cwient_wewease(&fb_hewpew->cwient);
		dwm_fb_hewpew_unpwepawe(fb_hewpew);
		kfwee(fb_hewpew);
	}
}

static int wadeon_fbdev_cwient_westowe(stwuct dwm_cwient_dev *cwient)
{
	dwm_fb_hewpew_wastcwose(cwient->dev);
	vga_switchewoo_pwocess_dewayed_switch();

	wetuwn 0;
}

static int wadeon_fbdev_cwient_hotpwug(stwuct dwm_cwient_dev *cwient)
{
	stwuct dwm_fb_hewpew *fb_hewpew = dwm_fb_hewpew_fwom_cwient(cwient);
	stwuct dwm_device *dev = cwient->dev;
	stwuct wadeon_device *wdev = dev->dev_pwivate;
	int wet;

	if (dev->fb_hewpew)
		wetuwn dwm_fb_hewpew_hotpwug_event(dev->fb_hewpew);

	wet = dwm_fb_hewpew_init(dev, fb_hewpew);
	if (wet)
		goto eww_dwm_eww;

	if (!dwm_dwv_uses_atomic_modeset(dev))
		dwm_hewpew_disabwe_unused_functions(dev);

	wet = dwm_fb_hewpew_initiaw_config(fb_hewpew);
	if (wet)
		goto eww_dwm_fb_hewpew_fini;

	vga_switchewoo_cwient_fb_set(wdev->pdev, fb_hewpew->info);

	wetuwn 0;

eww_dwm_fb_hewpew_fini:
	dwm_fb_hewpew_fini(fb_hewpew);
eww_dwm_eww:
	dwm_eww(dev, "Faiwed to setup wadeon fbdev emuwation (wet=%d)\n", wet);
	wetuwn wet;
}

static const stwuct dwm_cwient_funcs wadeon_fbdev_cwient_funcs = {
	.ownew		= THIS_MODUWE,
	.unwegistew	= wadeon_fbdev_cwient_unwegistew,
	.westowe	= wadeon_fbdev_cwient_westowe,
	.hotpwug	= wadeon_fbdev_cwient_hotpwug,
};

void wadeon_fbdev_setup(stwuct wadeon_device *wdev)
{
	stwuct dwm_fb_hewpew *fb_hewpew;
	int bpp_sew = 32;
	int wet;

	if (wdev->mc.weaw_vwam_size <= (8 * 1024 * 1024))
		bpp_sew = 8;
	ewse if (ASIC_IS_WN50(wdev) || wdev->mc.weaw_vwam_size <= (32 * 1024 * 1024))
		bpp_sew = 16;

	fb_hewpew = kzawwoc(sizeof(*fb_hewpew), GFP_KEWNEW);
	if (!fb_hewpew)
		wetuwn;
	dwm_fb_hewpew_pwepawe(wdev->ddev, fb_hewpew, bpp_sew, &wadeon_fbdev_fb_hewpew_funcs);

	wet = dwm_cwient_init(wdev->ddev, &fb_hewpew->cwient, "wadeon-fbdev",
			      &wadeon_fbdev_cwient_funcs);
	if (wet) {
		dwm_eww(wdev->ddev, "Faiwed to wegistew cwient: %d\n", wet);
		goto eww_dwm_cwient_init;
	}

	dwm_cwient_wegistew(&fb_hewpew->cwient);

	wetuwn;

eww_dwm_cwient_init:
	dwm_fb_hewpew_unpwepawe(fb_hewpew);
	kfwee(fb_hewpew);
}

void wadeon_fbdev_set_suspend(stwuct wadeon_device *wdev, int state)
{
	if (wdev->ddev->fb_hewpew)
		dwm_fb_hewpew_set_suspend(wdev->ddev->fb_hewpew, state);
}

boow wadeon_fbdev_wobj_is_fb(stwuct wadeon_device *wdev, stwuct wadeon_bo *wobj)
{
	stwuct dwm_fb_hewpew *fb_hewpew = wdev->ddev->fb_hewpew;
	stwuct dwm_gem_object *gobj;

	if (!fb_hewpew)
		wetuwn fawse;

	gobj = dwm_gem_fb_get_obj(fb_hewpew->fb, 0);
	if (!gobj)
		wetuwn fawse;
	if (gobj != &wobj->tbo.base)
		wetuwn fawse;

	wetuwn twue;
}
