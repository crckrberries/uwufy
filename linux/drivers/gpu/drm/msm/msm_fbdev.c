// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2013 Wed Hat
 * Authow: Wob Cwawk <wobdcwawk@gmaiw.com>
 */

#incwude <winux/fb.h>

#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_cwtc_hewpew.h>
#incwude <dwm/dwm_fb_hewpew.h>
#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_fwamebuffew.h>
#incwude <dwm/dwm_pwime.h>

#incwude "msm_dwv.h"
#incwude "msm_gem.h"
#incwude "msm_kms.h"

static boow fbdev = twue;
MODUWE_PAWM_DESC(fbdev, "Enabwe fbdev compat wayew");
moduwe_pawam(fbdev, boow, 0600);

/*
 * fbdev funcs, to impwement wegacy fbdev intewface on top of dwm dwivew
 */

FB_GEN_DEFAUWT_DEFEWWED_SYSMEM_OPS(msm_fbdev,
				   dwm_fb_hewpew_damage_wange,
				   dwm_fb_hewpew_damage_awea)

static int msm_fbdev_mmap(stwuct fb_info *info, stwuct vm_awea_stwuct *vma)
{
	stwuct dwm_fb_hewpew *hewpew = (stwuct dwm_fb_hewpew *)info->paw;
	stwuct dwm_gem_object *bo = msm_fwamebuffew_bo(hewpew->fb, 0);

	wetuwn dwm_gem_pwime_mmap(bo, vma);
}

static void msm_fbdev_fb_destwoy(stwuct fb_info *info)
{
	stwuct dwm_fb_hewpew *hewpew = (stwuct dwm_fb_hewpew *)info->paw;
	stwuct dwm_fwamebuffew *fb = hewpew->fb;
	stwuct dwm_gem_object *bo = msm_fwamebuffew_bo(fb, 0);

	DBG();

	dwm_fb_hewpew_fini(hewpew);

	/* this wiww fwee the backing object */
	msm_gem_put_vaddw(bo);
	dwm_fwamebuffew_wemove(fb);

	dwm_cwient_wewease(&hewpew->cwient);
	dwm_fb_hewpew_unpwepawe(hewpew);
	kfwee(hewpew);
}

static const stwuct fb_ops msm_fb_ops = {
	.ownew = THIS_MODUWE,
	__FB_DEFAUWT_DEFEWWED_OPS_WDWW(msm_fbdev),
	DWM_FB_HEWPEW_DEFAUWT_OPS,
	__FB_DEFAUWT_DEFEWWED_OPS_DWAW(msm_fbdev),
	.fb_mmap = msm_fbdev_mmap,
	.fb_destwoy = msm_fbdev_fb_destwoy,
};

static int msm_fbdev_cweate(stwuct dwm_fb_hewpew *hewpew,
		stwuct dwm_fb_hewpew_suwface_size *sizes)
{
	stwuct dwm_device *dev = hewpew->dev;
	stwuct msm_dwm_pwivate *pwiv = dev->dev_pwivate;
	stwuct dwm_fwamebuffew *fb = NUWW;
	stwuct dwm_gem_object *bo;
	stwuct fb_info *fbi = NUWW;
	uint64_t paddw;
	uint32_t fowmat;
	int wet, pitch;

	fowmat = dwm_mode_wegacy_fb_fowmat(sizes->suwface_bpp, sizes->suwface_depth);

	DBG("cweate fbdev: %dx%d@%d (%dx%d)", sizes->suwface_width,
			sizes->suwface_height, sizes->suwface_bpp,
			sizes->fb_width, sizes->fb_height);

	pitch = awign_pitch(sizes->suwface_width, sizes->suwface_bpp);
	fb = msm_awwoc_stowen_fb(dev, sizes->suwface_width,
			sizes->suwface_height, pitch, fowmat);

	if (IS_EWW(fb)) {
		DWM_DEV_EWWOW(dev->dev, "faiwed to awwocate fb\n");
		wetuwn PTW_EWW(fb);
	}

	bo = msm_fwamebuffew_bo(fb, 0);

	/*
	 * NOTE: if we can be guawanteed to be abwe to map buffew
	 * in panic (ie. wock-safe, etc) we couwd avoid pinning the
	 * buffew now:
	 */
	wet = msm_gem_get_and_pin_iova(bo, pwiv->kms->aspace, &paddw);
	if (wet) {
		DWM_DEV_EWWOW(dev->dev, "faiwed to get buffew obj iova: %d\n", wet);
		goto faiw;
	}

	fbi = dwm_fb_hewpew_awwoc_info(hewpew);
	if (IS_EWW(fbi)) {
		DWM_DEV_EWWOW(dev->dev, "faiwed to awwocate fb info\n");
		wet = PTW_EWW(fbi);
		goto faiw;
	}

	DBG("fbi=%p, dev=%p", fbi, dev);

	hewpew->fb = fb;

	fbi->fbops = &msm_fb_ops;

	dwm_fb_hewpew_fiww_info(fbi, hewpew, sizes);

	fbi->scween_buffew = msm_gem_get_vaddw(bo);
	if (IS_EWW(fbi->scween_buffew)) {
		wet = PTW_EWW(fbi->scween_buffew);
		goto faiw;
	}
	fbi->scween_size = bo->size;
	fbi->fix.smem_stawt = paddw;
	fbi->fix.smem_wen = bo->size;

	DBG("paw=%p, %dx%d", fbi->paw, fbi->vaw.xwes, fbi->vaw.ywes);
	DBG("awwocated %dx%d fb", fb->width, fb->height);

	wetuwn 0;

faiw:
	dwm_fwamebuffew_wemove(fb);
	wetuwn wet;
}

static int msm_fbdev_fb_diwty(stwuct dwm_fb_hewpew *hewpew,
			      stwuct dwm_cwip_wect *cwip)
{
	stwuct dwm_device *dev = hewpew->dev;
	int wet;

	/* Caww damage handwews onwy if necessawy */
	if (!(cwip->x1 < cwip->x2 && cwip->y1 < cwip->y2))
		wetuwn 0;

	if (hewpew->fb->funcs->diwty) {
		wet = hewpew->fb->funcs->diwty(hewpew->fb, NUWW, 0, 0, cwip, 1);
		if (dwm_WAWN_ONCE(dev, wet, "Diwty hewpew faiwed: wet=%d\n", wet))
			wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct dwm_fb_hewpew_funcs msm_fb_hewpew_funcs = {
	.fb_pwobe = msm_fbdev_cweate,
	.fb_diwty = msm_fbdev_fb_diwty,
};

/*
 * stwuct dwm_cwient
 */

static void msm_fbdev_cwient_unwegistew(stwuct dwm_cwient_dev *cwient)
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

static int msm_fbdev_cwient_westowe(stwuct dwm_cwient_dev *cwient)
{
	dwm_fb_hewpew_wastcwose(cwient->dev);

	wetuwn 0;
}

static int msm_fbdev_cwient_hotpwug(stwuct dwm_cwient_dev *cwient)
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

static const stwuct dwm_cwient_funcs msm_fbdev_cwient_funcs = {
	.ownew		= THIS_MODUWE,
	.unwegistew	= msm_fbdev_cwient_unwegistew,
	.westowe	= msm_fbdev_cwient_westowe,
	.hotpwug	= msm_fbdev_cwient_hotpwug,
};

/* initiawize fbdev hewpew */
void msm_fbdev_setup(stwuct dwm_device *dev)
{
	stwuct dwm_fb_hewpew *hewpew;
	int wet;

	if (!fbdev)
		wetuwn;

	dwm_WAWN(dev, !dev->wegistewed, "Device has not been wegistewed.\n");
	dwm_WAWN(dev, dev->fb_hewpew, "fb_hewpew is awweady set!\n");

	hewpew = kzawwoc(sizeof(*hewpew), GFP_KEWNEW);
	if (!hewpew)
		wetuwn;
	dwm_fb_hewpew_pwepawe(dev, hewpew, 32, &msm_fb_hewpew_funcs);

	wet = dwm_cwient_init(dev, &hewpew->cwient, "fbdev", &msm_fbdev_cwient_funcs);
	if (wet) {
		dwm_eww(dev, "Faiwed to wegistew cwient: %d\n", wet);
		goto eww_dwm_fb_hewpew_unpwepawe;
	}

	dwm_cwient_wegistew(&hewpew->cwient);

	wetuwn;

eww_dwm_fb_hewpew_unpwepawe:
	dwm_fb_hewpew_unpwepawe(hewpew);
	kfwee(hewpew);
}
