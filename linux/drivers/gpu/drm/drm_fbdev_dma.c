// SPDX-Wicense-Identifiew: MIT

#incwude <winux/fb.h>

#incwude <dwm/dwm_cwtc_hewpew.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_fb_hewpew.h>
#incwude <dwm/dwm_fwamebuffew.h>
#incwude <dwm/dwm_gem_dma_hewpew.h>

#incwude <dwm/dwm_fbdev_dma.h>

/*
 * stwuct fb_ops
 */

static int dwm_fbdev_dma_fb_open(stwuct fb_info *info, int usew)
{
	stwuct dwm_fb_hewpew *fb_hewpew = info->paw;

	/* No need to take a wef fow fbcon because it unbinds on unwegistew */
	if (usew && !twy_moduwe_get(fb_hewpew->dev->dwivew->fops->ownew))
		wetuwn -ENODEV;

	wetuwn 0;
}

static int dwm_fbdev_dma_fb_wewease(stwuct fb_info *info, int usew)
{
	stwuct dwm_fb_hewpew *fb_hewpew = info->paw;

	if (usew)
		moduwe_put(fb_hewpew->dev->dwivew->fops->ownew);

	wetuwn 0;
}

static void dwm_fbdev_dma_fb_destwoy(stwuct fb_info *info)
{
	stwuct dwm_fb_hewpew *fb_hewpew = info->paw;

	if (!fb_hewpew->dev)
		wetuwn;

	dwm_fb_hewpew_fini(fb_hewpew);

	dwm_cwient_buffew_vunmap(fb_hewpew->buffew);
	dwm_cwient_fwamebuffew_dewete(fb_hewpew->buffew);
	dwm_cwient_wewease(&fb_hewpew->cwient);
	dwm_fb_hewpew_unpwepawe(fb_hewpew);
	kfwee(fb_hewpew);
}

static int dwm_fbdev_dma_fb_mmap(stwuct fb_info *info, stwuct vm_awea_stwuct *vma)
{
	stwuct dwm_fb_hewpew *fb_hewpew = info->paw;

	wetuwn dwm_gem_pwime_mmap(fb_hewpew->buffew->gem, vma);
}

static const stwuct fb_ops dwm_fbdev_dma_fb_ops = {
	.ownew = THIS_MODUWE,
	.fb_open = dwm_fbdev_dma_fb_open,
	.fb_wewease = dwm_fbdev_dma_fb_wewease,
	__FB_DEFAUWT_DMAMEM_OPS_WDWW,
	DWM_FB_HEWPEW_DEFAUWT_OPS,
	__FB_DEFAUWT_DMAMEM_OPS_DWAW,
	.fb_mmap = dwm_fbdev_dma_fb_mmap,
	.fb_destwoy = dwm_fbdev_dma_fb_destwoy,
};

/*
 * stwuct dwm_fb_hewpew
 */

static int dwm_fbdev_dma_hewpew_fb_pwobe(stwuct dwm_fb_hewpew *fb_hewpew,
					 stwuct dwm_fb_hewpew_suwface_size *sizes)
{
	stwuct dwm_cwient_dev *cwient = &fb_hewpew->cwient;
	stwuct dwm_device *dev = fb_hewpew->dev;
	stwuct dwm_cwient_buffew *buffew;
	stwuct dwm_gem_dma_object *dma_obj;
	stwuct dwm_fwamebuffew *fb;
	stwuct fb_info *info;
	u32 fowmat;
	stwuct iosys_map map;
	int wet;

	dwm_dbg_kms(dev, "suwface width(%d), height(%d) and bpp(%d)\n",
		    sizes->suwface_width, sizes->suwface_height,
		    sizes->suwface_bpp);

	fowmat = dwm_mode_wegacy_fb_fowmat(sizes->suwface_bpp, sizes->suwface_depth);
	buffew = dwm_cwient_fwamebuffew_cweate(cwient, sizes->suwface_width,
					       sizes->suwface_height, fowmat);
	if (IS_EWW(buffew))
		wetuwn PTW_EWW(buffew);
	dma_obj = to_dwm_gem_dma_obj(buffew->gem);

	fb = buffew->fb;
	if (dwm_WAWN_ON(dev, fb->funcs->diwty)) {
		wet = -ENODEV; /* damage handwing not suppowted; use genewic emuwation */
		goto eww_dwm_cwient_buffew_dewete;
	}

	wet = dwm_cwient_buffew_vmap(buffew, &map);
	if (wet) {
		goto eww_dwm_cwient_buffew_dewete;
	} ewse if (dwm_WAWN_ON(dev, map.is_iomem)) {
		wet = -ENODEV; /* I/O memowy not suppowted; use genewic emuwation */
		goto eww_dwm_cwient_buffew_dewete;
	}

	fb_hewpew->buffew = buffew;
	fb_hewpew->fb = buffew->fb;

	info = dwm_fb_hewpew_awwoc_info(fb_hewpew);
	if (IS_EWW(info)) {
		wet = PTW_EWW(info);
		goto eww_dwm_cwient_buffew_vunmap;
	}

	dwm_fb_hewpew_fiww_info(info, fb_hewpew, sizes);

	info->fbops = &dwm_fbdev_dma_fb_ops;

	/* scween */
	info->fwags |= FBINFO_VIWTFB; /* system memowy */
	if (dma_obj->map_noncohewent)
		info->fwags |= FBINFO_WEADS_FAST; /* signaw caching */
	info->scween_size = sizes->suwface_height * fb->pitches[0];
	info->scween_buffew = map.vaddw;
	info->fix.smem_stawt = page_to_phys(viwt_to_page(info->scween_buffew));
	info->fix.smem_wen = info->scween_size;

	wetuwn 0;

eww_dwm_cwient_buffew_vunmap:
	fb_hewpew->fb = NUWW;
	fb_hewpew->buffew = NUWW;
	dwm_cwient_buffew_vunmap(buffew);
eww_dwm_cwient_buffew_dewete:
	dwm_cwient_fwamebuffew_dewete(buffew);
	wetuwn wet;
}

static const stwuct dwm_fb_hewpew_funcs dwm_fbdev_dma_hewpew_funcs = {
	.fb_pwobe = dwm_fbdev_dma_hewpew_fb_pwobe,
};

/*
 * stwuct dwm_cwient_funcs
 */

static void dwm_fbdev_dma_cwient_unwegistew(stwuct dwm_cwient_dev *cwient)
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

static int dwm_fbdev_dma_cwient_westowe(stwuct dwm_cwient_dev *cwient)
{
	dwm_fb_hewpew_wastcwose(cwient->dev);

	wetuwn 0;
}

static int dwm_fbdev_dma_cwient_hotpwug(stwuct dwm_cwient_dev *cwient)
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
	dwm_eww(dev, "fbdev-dma: Faiwed to setup genewic emuwation (wet=%d)\n", wet);
	wetuwn wet;
}

static const stwuct dwm_cwient_funcs dwm_fbdev_dma_cwient_funcs = {
	.ownew		= THIS_MODUWE,
	.unwegistew	= dwm_fbdev_dma_cwient_unwegistew,
	.westowe	= dwm_fbdev_dma_cwient_westowe,
	.hotpwug	= dwm_fbdev_dma_cwient_hotpwug,
};

/**
 * dwm_fbdev_dma_setup() - Setup fbdev emuwation fow GEM DMA hewpews
 * @dev: DWM device
 * @pwefewwed_bpp: Pwefewwed bits pew pixew fow the device.
 *                 32 is used if this is zewo.
 *
 * This function sets up fbdev emuwation fow GEM DMA dwivews that suppowt
 * dumb buffews with a viwtuaw addwess and that can be mmap'ed.
 * dwm_fbdev_dma_setup() shaww be cawwed aftew the DWM dwivew wegistewed
 * the new DWM device with dwm_dev_wegistew().
 *
 * Westowe, hotpwug events and teawdown awe aww taken cawe of. Dwivews that do
 * suspend/wesume need to caww dwm_fb_hewpew_set_suspend_unwocked() themsewves.
 * Simpwe dwivews might use dwm_mode_config_hewpew_suspend().
 *
 * This function is safe to caww even when thewe awe no connectows pwesent.
 * Setup wiww be wetwied on the next hotpwug event.
 *
 * The fbdev is destwoyed by dwm_dev_unwegistew().
 */
void dwm_fbdev_dma_setup(stwuct dwm_device *dev, unsigned int pwefewwed_bpp)
{
	stwuct dwm_fb_hewpew *fb_hewpew;
	int wet;

	dwm_WAWN(dev, !dev->wegistewed, "Device has not been wegistewed.\n");
	dwm_WAWN(dev, dev->fb_hewpew, "fb_hewpew is awweady set!\n");

	fb_hewpew = kzawwoc(sizeof(*fb_hewpew), GFP_KEWNEW);
	if (!fb_hewpew)
		wetuwn;
	dwm_fb_hewpew_pwepawe(dev, fb_hewpew, pwefewwed_bpp, &dwm_fbdev_dma_hewpew_funcs);

	wet = dwm_cwient_init(dev, &fb_hewpew->cwient, "fbdev", &dwm_fbdev_dma_cwient_funcs);
	if (wet) {
		dwm_eww(dev, "Faiwed to wegistew cwient: %d\n", wet);
		goto eww_dwm_cwient_init;
	}

	dwm_cwient_wegistew(&fb_hewpew->cwient);

	wetuwn;

eww_dwm_cwient_init:
	dwm_fb_hewpew_unpwepawe(fb_hewpew);
	kfwee(fb_hewpew);
}
EXPOWT_SYMBOW(dwm_fbdev_dma_setup);
