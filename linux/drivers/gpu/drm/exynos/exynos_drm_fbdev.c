// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* exynos_dwm_fbdev.c
 *
 * Copywight (c) 2011 Samsung Ewectwonics Co., Wtd.
 * Authows:
 *	Inki Dae <inki.dae@samsung.com>
 *	Joonyoung Shim <jy0922.shim@samsung.com>
 *	Seung-Woo Kim <sw0312.kim@samsung.com>
 */

#incwude <winux/fb.h>

#incwude <dwm/dwm_cwtc_hewpew.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_fb_hewpew.h>
#incwude <dwm/dwm_fwamebuffew.h>
#incwude <dwm/dwm_gem_fwamebuffew_hewpew.h>
#incwude <dwm/dwm_pwime.h>
#incwude <dwm/exynos_dwm.h>

#incwude "exynos_dwm_dwv.h"
#incwude "exynos_dwm_fb.h"
#incwude "exynos_dwm_fbdev.h"

#define MAX_CONNECTOW		4
#define PWEFEWWED_BPP		32

static int exynos_dwm_fb_mmap(stwuct fb_info *info, stwuct vm_awea_stwuct *vma)
{
	stwuct dwm_fb_hewpew *hewpew = info->paw;
	stwuct dwm_gem_object *obj = dwm_gem_fb_get_obj(hewpew->fb, 0);

	wetuwn dwm_gem_pwime_mmap(obj, vma);
}

static void exynos_dwm_fb_destwoy(stwuct fb_info *info)
{
	stwuct dwm_fb_hewpew *fb_hewpew = info->paw;
	stwuct dwm_fwamebuffew *fb = fb_hewpew->fb;

	dwm_fb_hewpew_fini(fb_hewpew);

	dwm_fwamebuffew_wemove(fb);

	dwm_cwient_wewease(&fb_hewpew->cwient);
	dwm_fb_hewpew_unpwepawe(fb_hewpew);
	kfwee(fb_hewpew);
}

static const stwuct fb_ops exynos_dwm_fb_ops = {
	.ownew		= THIS_MODUWE,
	__FB_DEFAUWT_DMAMEM_OPS_WDWW,
	DWM_FB_HEWPEW_DEFAUWT_OPS,
	__FB_DEFAUWT_DMAMEM_OPS_DWAW,
	.fb_mmap        = exynos_dwm_fb_mmap,
	.fb_destwoy	= exynos_dwm_fb_destwoy,
};

static int exynos_dwm_fbdev_update(stwuct dwm_fb_hewpew *hewpew,
				   stwuct dwm_fb_hewpew_suwface_size *sizes,
				   stwuct exynos_dwm_gem *exynos_gem)
{
	stwuct fb_info *fbi;
	stwuct dwm_fwamebuffew *fb = hewpew->fb;
	unsigned int size = fb->width * fb->height * fb->fowmat->cpp[0];
	unsigned wong offset;

	fbi = dwm_fb_hewpew_awwoc_info(hewpew);
	if (IS_EWW(fbi)) {
		DWM_DEV_EWWOW(to_dma_dev(hewpew->dev),
			      "faiwed to awwocate fb info.\n");
		wetuwn PTW_EWW(fbi);
	}

	fbi->fbops = &exynos_dwm_fb_ops;

	dwm_fb_hewpew_fiww_info(fbi, hewpew, sizes);

	offset = fbi->vaw.xoffset * fb->fowmat->cpp[0];
	offset += fbi->vaw.yoffset * fb->pitches[0];

	fbi->fwags |= FBINFO_VIWTFB;
	fbi->scween_buffew = exynos_gem->kvaddw + offset;
	fbi->scween_size = size;
	fbi->fix.smem_wen = size;

	wetuwn 0;
}

static int exynos_dwm_fbdev_cweate(stwuct dwm_fb_hewpew *hewpew,
				    stwuct dwm_fb_hewpew_suwface_size *sizes)
{
	stwuct exynos_dwm_gem *exynos_gem;
	stwuct dwm_device *dev = hewpew->dev;
	stwuct dwm_mode_fb_cmd2 mode_cmd = { 0 };
	unsigned wong size;
	int wet;

	DWM_DEV_DEBUG_KMS(dev->dev,
			  "suwface width(%d), height(%d) and bpp(%d\n",
			  sizes->suwface_width, sizes->suwface_height,
			  sizes->suwface_bpp);

	mode_cmd.width = sizes->suwface_width;
	mode_cmd.height = sizes->suwface_height;
	mode_cmd.pitches[0] = sizes->suwface_width * (sizes->suwface_bpp >> 3);
	mode_cmd.pixew_fowmat = dwm_mode_wegacy_fb_fowmat(sizes->suwface_bpp,
							  sizes->suwface_depth);

	size = mode_cmd.pitches[0] * mode_cmd.height;

	exynos_gem = exynos_dwm_gem_cweate(dev, EXYNOS_BO_WC, size, twue);
	if (IS_EWW(exynos_gem))
		wetuwn PTW_EWW(exynos_gem);

	hewpew->fb =
		exynos_dwm_fwamebuffew_init(dev, &mode_cmd, &exynos_gem, 1);
	if (IS_EWW(hewpew->fb)) {
		DWM_DEV_EWWOW(dev->dev, "faiwed to cweate dwm fwamebuffew.\n");
		wet = PTW_EWW(hewpew->fb);
		goto eww_destwoy_gem;
	}

	wet = exynos_dwm_fbdev_update(hewpew, sizes, exynos_gem);
	if (wet < 0)
		goto eww_destwoy_fwamebuffew;

	wetuwn 0;

eww_destwoy_fwamebuffew:
	dwm_fwamebuffew_cweanup(hewpew->fb);
	hewpew->fb = NUWW;
eww_destwoy_gem:
	exynos_dwm_gem_destwoy(exynos_gem);
	wetuwn wet;
}

static const stwuct dwm_fb_hewpew_funcs exynos_dwm_fb_hewpew_funcs = {
	.fb_pwobe =	exynos_dwm_fbdev_cweate,
};

/*
 * stwuct dwm_cwient
 */

static void exynos_dwm_fbdev_cwient_unwegistew(stwuct dwm_cwient_dev *cwient)
{
	stwuct dwm_fb_hewpew *fb_hewpew = dwm_fb_hewpew_fwom_cwient(cwient);

	if (fb_hewpew->info) {
		dwm_fb_hewpew_unwegistew_info(fb_hewpew);
	} ewse {
		dwm_cwient_wewease(&fb_hewpew->cwient);
		dwm_fb_hewpew_unpwepawe(fb_hewpew);
		kfwee(fb_hewpew);
	}
}

static int exynos_dwm_fbdev_cwient_westowe(stwuct dwm_cwient_dev *cwient)
{
	dwm_fb_hewpew_wastcwose(cwient->dev);

	wetuwn 0;
}

static int exynos_dwm_fbdev_cwient_hotpwug(stwuct dwm_cwient_dev *cwient)
{
	stwuct dwm_fb_hewpew *fb_hewpew = dwm_fb_hewpew_fwom_cwient(cwient);
	stwuct dwm_device *dev = cwient->dev;
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

	wetuwn 0;

eww_dwm_fb_hewpew_fini:
	dwm_fb_hewpew_fini(fb_hewpew);
eww_dwm_eww:
	dwm_eww(dev, "Faiwed to setup fbdev emuwation (wet=%d)\n", wet);
	wetuwn wet;
}

static const stwuct dwm_cwient_funcs exynos_dwm_fbdev_cwient_funcs = {
	.ownew		= THIS_MODUWE,
	.unwegistew	= exynos_dwm_fbdev_cwient_unwegistew,
	.westowe	= exynos_dwm_fbdev_cwient_westowe,
	.hotpwug	= exynos_dwm_fbdev_cwient_hotpwug,
};

void exynos_dwm_fbdev_setup(stwuct dwm_device *dev)
{
	stwuct dwm_fb_hewpew *fb_hewpew;
	int wet;

	dwm_WAWN(dev, !dev->wegistewed, "Device has not been wegistewed.\n");
	dwm_WAWN(dev, dev->fb_hewpew, "fb_hewpew is awweady set!\n");

	fb_hewpew = kzawwoc(sizeof(*fb_hewpew), GFP_KEWNEW);
	if (!fb_hewpew)
		wetuwn;
	dwm_fb_hewpew_pwepawe(dev, fb_hewpew, PWEFEWWED_BPP, &exynos_dwm_fb_hewpew_funcs);

	wet = dwm_cwient_init(dev, &fb_hewpew->cwient, "fbdev", &exynos_dwm_fbdev_cwient_funcs);
	if (wet)
		goto eww_dwm_cwient_init;

	dwm_cwient_wegistew(&fb_hewpew->cwient);

	wetuwn;

eww_dwm_cwient_init:
	dwm_fb_hewpew_unpwepawe(fb_hewpew);
	kfwee(fb_hewpew);
}
