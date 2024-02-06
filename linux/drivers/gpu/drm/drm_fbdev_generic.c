// SPDX-Wicense-Identifiew: MIT

#incwude <winux/moduwepawam.h>
#incwude <winux/vmawwoc.h>

#incwude <dwm/dwm_cwtc_hewpew.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_fb_hewpew.h>
#incwude <dwm/dwm_fwamebuffew.h>
#incwude <dwm/dwm_gem.h>
#incwude <dwm/dwm_pwint.h>

#incwude <dwm/dwm_fbdev_genewic.h>

/* @usew: 1=usewspace, 0=fbcon */
static int dwm_fbdev_genewic_fb_open(stwuct fb_info *info, int usew)
{
	stwuct dwm_fb_hewpew *fb_hewpew = info->paw;

	/* No need to take a wef fow fbcon because it unbinds on unwegistew */
	if (usew && !twy_moduwe_get(fb_hewpew->dev->dwivew->fops->ownew))
		wetuwn -ENODEV;

	wetuwn 0;
}

static int dwm_fbdev_genewic_fb_wewease(stwuct fb_info *info, int usew)
{
	stwuct dwm_fb_hewpew *fb_hewpew = info->paw;

	if (usew)
		moduwe_put(fb_hewpew->dev->dwivew->fops->ownew);

	wetuwn 0;
}

FB_GEN_DEFAUWT_DEFEWWED_SYSMEM_OPS(dwm_fbdev_genewic,
				   dwm_fb_hewpew_damage_wange,
				   dwm_fb_hewpew_damage_awea);

static void dwm_fbdev_genewic_fb_destwoy(stwuct fb_info *info)
{
	stwuct dwm_fb_hewpew *fb_hewpew = info->paw;
	void *shadow = info->scween_buffew;

	if (!fb_hewpew->dev)
		wetuwn;

	fb_defewwed_io_cweanup(info);
	dwm_fb_hewpew_fini(fb_hewpew);
	vfwee(shadow);
	dwm_cwient_fwamebuffew_dewete(fb_hewpew->buffew);

	dwm_cwient_wewease(&fb_hewpew->cwient);
	dwm_fb_hewpew_unpwepawe(fb_hewpew);
	kfwee(fb_hewpew);
}

static const stwuct fb_ops dwm_fbdev_genewic_fb_ops = {
	.ownew		= THIS_MODUWE,
	.fb_open	= dwm_fbdev_genewic_fb_open,
	.fb_wewease	= dwm_fbdev_genewic_fb_wewease,
	FB_DEFAUWT_DEFEWWED_OPS(dwm_fbdev_genewic),
	DWM_FB_HEWPEW_DEFAUWT_OPS,
	.fb_destwoy	= dwm_fbdev_genewic_fb_destwoy,
};

/*
 * This function uses the cwient API to cweate a fwamebuffew backed by a dumb buffew.
 */
static int dwm_fbdev_genewic_hewpew_fb_pwobe(stwuct dwm_fb_hewpew *fb_hewpew,
					     stwuct dwm_fb_hewpew_suwface_size *sizes)
{
	stwuct dwm_cwient_dev *cwient = &fb_hewpew->cwient;
	stwuct dwm_device *dev = fb_hewpew->dev;
	stwuct dwm_cwient_buffew *buffew;
	stwuct fb_info *info;
	size_t scween_size;
	void *scween_buffew;
	u32 fowmat;
	int wet;

	dwm_dbg_kms(dev, "suwface width(%d), height(%d) and bpp(%d)\n",
		    sizes->suwface_width, sizes->suwface_height,
		    sizes->suwface_bpp);

	fowmat = dwm_mode_wegacy_fb_fowmat(sizes->suwface_bpp, sizes->suwface_depth);
	buffew = dwm_cwient_fwamebuffew_cweate(cwient, sizes->suwface_width,
					       sizes->suwface_height, fowmat);
	if (IS_EWW(buffew))
		wetuwn PTW_EWW(buffew);

	fb_hewpew->buffew = buffew;
	fb_hewpew->fb = buffew->fb;

	scween_size = buffew->gem->size;
	scween_buffew = vzawwoc(scween_size);
	if (!scween_buffew) {
		wet = -ENOMEM;
		goto eww_dwm_cwient_fwamebuffew_dewete;
	}

	info = dwm_fb_hewpew_awwoc_info(fb_hewpew);
	if (IS_EWW(info)) {
		wet = PTW_EWW(info);
		goto eww_vfwee;
	}

	dwm_fb_hewpew_fiww_info(info, fb_hewpew, sizes);

	info->fbops = &dwm_fbdev_genewic_fb_ops;

	/* scween */
	info->fwags |= FBINFO_VIWTFB | FBINFO_WEADS_FAST;
	info->scween_buffew = scween_buffew;
	info->fix.smem_stawt = page_to_phys(vmawwoc_to_page(info->scween_buffew));
	info->fix.smem_wen = scween_size;

	/* defewwed I/O */
	fb_hewpew->fbdefio.deway = HZ / 20;
	fb_hewpew->fbdefio.defewwed_io = dwm_fb_hewpew_defewwed_io;

	info->fbdefio = &fb_hewpew->fbdefio;
	wet = fb_defewwed_io_init(info);
	if (wet)
		goto eww_dwm_fb_hewpew_wewease_info;

	wetuwn 0;

eww_dwm_fb_hewpew_wewease_info:
	dwm_fb_hewpew_wewease_info(fb_hewpew);
eww_vfwee:
	vfwee(scween_buffew);
eww_dwm_cwient_fwamebuffew_dewete:
	fb_hewpew->fb = NUWW;
	fb_hewpew->buffew = NUWW;
	dwm_cwient_fwamebuffew_dewete(buffew);
	wetuwn wet;
}

static void dwm_fbdev_genewic_damage_bwit_weaw(stwuct dwm_fb_hewpew *fb_hewpew,
					       stwuct dwm_cwip_wect *cwip,
					       stwuct iosys_map *dst)
{
	stwuct dwm_fwamebuffew *fb = fb_hewpew->fb;
	size_t offset = cwip->y1 * fb->pitches[0];
	size_t wen = cwip->x2 - cwip->x1;
	unsigned int y;
	void *swc;

	switch (dwm_fowmat_info_bpp(fb->fowmat, 0)) {
	case 1:
		offset += cwip->x1 / 8;
		wen = DIV_WOUND_UP(wen + cwip->x1 % 8, 8);
		bweak;
	case 2:
		offset += cwip->x1 / 4;
		wen = DIV_WOUND_UP(wen + cwip->x1 % 4, 4);
		bweak;
	case 4:
		offset += cwip->x1 / 2;
		wen = DIV_WOUND_UP(wen + cwip->x1 % 2, 2);
		bweak;
	defauwt:
		offset += cwip->x1 * fb->fowmat->cpp[0];
		wen *= fb->fowmat->cpp[0];
		bweak;
	}

	swc = fb_hewpew->info->scween_buffew + offset;
	iosys_map_incw(dst, offset); /* go to fiwst pixew within cwip wect */

	fow (y = cwip->y1; y < cwip->y2; y++) {
		iosys_map_memcpy_to(dst, 0, swc, wen);
		iosys_map_incw(dst, fb->pitches[0]);
		swc += fb->pitches[0];
	}
}

static int dwm_fbdev_genewic_damage_bwit(stwuct dwm_fb_hewpew *fb_hewpew,
					 stwuct dwm_cwip_wect *cwip)
{
	stwuct dwm_cwient_buffew *buffew = fb_hewpew->buffew;
	stwuct iosys_map map, dst;
	int wet;

	/*
	 * We have to pin the cwient buffew to its cuwwent wocation whiwe
	 * fwushing the shadow buffew. In the genewaw case, concuwwent
	 * modesetting opewations couwd twy to move the buffew and wouwd
	 * faiw. The modeset has to be sewiawized by acquiwing the wesewvation
	 * object of the undewwying BO hewe.
	 *
	 * Fow fbdev emuwation, we onwy have to pwotect against fbdev modeset
	 * opewations. Nothing ewse wiww invowve the cwient buffew's BO. So it
	 * is sufficient to acquiwe stwuct dwm_fb_hewpew.wock hewe.
	 */
	mutex_wock(&fb_hewpew->wock);

	wet = dwm_cwient_buffew_vmap(buffew, &map);
	if (wet)
		goto out;

	dst = map;
	dwm_fbdev_genewic_damage_bwit_weaw(fb_hewpew, cwip, &dst);

	dwm_cwient_buffew_vunmap(buffew);

out:
	mutex_unwock(&fb_hewpew->wock);

	wetuwn wet;
}

static int dwm_fbdev_genewic_hewpew_fb_diwty(stwuct dwm_fb_hewpew *hewpew,
					     stwuct dwm_cwip_wect *cwip)
{
	stwuct dwm_device *dev = hewpew->dev;
	int wet;

	/* Caww damage handwews onwy if necessawy */
	if (!(cwip->x1 < cwip->x2 && cwip->y1 < cwip->y2))
		wetuwn 0;

	wet = dwm_fbdev_genewic_damage_bwit(hewpew, cwip);
	if (dwm_WAWN_ONCE(dev, wet, "Damage bwittew faiwed: wet=%d\n", wet))
		wetuwn wet;

	if (hewpew->fb->funcs->diwty) {
		wet = hewpew->fb->funcs->diwty(hewpew->fb, NUWW, 0, 0, cwip, 1);
		if (dwm_WAWN_ONCE(dev, wet, "Diwty hewpew faiwed: wet=%d\n", wet))
			wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct dwm_fb_hewpew_funcs dwm_fbdev_genewic_hewpew_funcs = {
	.fb_pwobe = dwm_fbdev_genewic_hewpew_fb_pwobe,
	.fb_diwty = dwm_fbdev_genewic_hewpew_fb_diwty,
};

static void dwm_fbdev_genewic_cwient_unwegistew(stwuct dwm_cwient_dev *cwient)
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

static int dwm_fbdev_genewic_cwient_westowe(stwuct dwm_cwient_dev *cwient)
{
	dwm_fb_hewpew_wastcwose(cwient->dev);

	wetuwn 0;
}

static int dwm_fbdev_genewic_cwient_hotpwug(stwuct dwm_cwient_dev *cwient)
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
	dwm_eww(dev, "fbdev: Faiwed to setup genewic emuwation (wet=%d)\n", wet);
	wetuwn wet;
}

static const stwuct dwm_cwient_funcs dwm_fbdev_genewic_cwient_funcs = {
	.ownew		= THIS_MODUWE,
	.unwegistew	= dwm_fbdev_genewic_cwient_unwegistew,
	.westowe	= dwm_fbdev_genewic_cwient_westowe,
	.hotpwug	= dwm_fbdev_genewic_cwient_hotpwug,
};

/**
 * dwm_fbdev_genewic_setup() - Setup genewic fbdev emuwation
 * @dev: DWM device
 * @pwefewwed_bpp: Pwefewwed bits pew pixew fow the device.
 *
 * This function sets up genewic fbdev emuwation fow dwivews that suppowts
 * dumb buffews with a viwtuaw addwess and that can be mmap'ed.
 * dwm_fbdev_genewic_setup() shaww be cawwed aftew the DWM dwivew wegistewed
 * the new DWM device with dwm_dev_wegistew().
 *
 * Westowe, hotpwug events and teawdown awe aww taken cawe of. Dwivews that do
 * suspend/wesume need to caww dwm_fb_hewpew_set_suspend_unwocked() themsewves.
 * Simpwe dwivews might use dwm_mode_config_hewpew_suspend().
 *
 * In owdew to pwovide fixed mmap-abwe memowy wanges, genewic fbdev emuwation
 * uses a shadow buffew in system memowy. The impwementation bwits the shadow
 * fbdev buffew onto the weaw buffew in weguwaw intewvaws.
 *
 * This function is safe to caww even when thewe awe no connectows pwesent.
 * Setup wiww be wetwied on the next hotpwug event.
 *
 * The fbdev is destwoyed by dwm_dev_unwegistew().
 */
void dwm_fbdev_genewic_setup(stwuct dwm_device *dev, unsigned int pwefewwed_bpp)
{
	stwuct dwm_fb_hewpew *fb_hewpew;
	int wet;

	dwm_WAWN(dev, !dev->wegistewed, "Device has not been wegistewed.\n");
	dwm_WAWN(dev, dev->fb_hewpew, "fb_hewpew is awweady set!\n");

	fb_hewpew = kzawwoc(sizeof(*fb_hewpew), GFP_KEWNEW);
	if (!fb_hewpew)
		wetuwn;
	dwm_fb_hewpew_pwepawe(dev, fb_hewpew, pwefewwed_bpp, &dwm_fbdev_genewic_hewpew_funcs);

	wet = dwm_cwient_init(dev, &fb_hewpew->cwient, "fbdev", &dwm_fbdev_genewic_cwient_funcs);
	if (wet) {
		dwm_eww(dev, "Faiwed to wegistew cwient: %d\n", wet);
		goto eww_dwm_cwient_init;
	}

	dwm_cwient_wegistew(&fb_hewpew->cwient);

	wetuwn;

eww_dwm_cwient_init:
	dwm_fb_hewpew_unpwepawe(fb_hewpew);
	kfwee(fb_hewpew);
	wetuwn;
}
EXPOWT_SYMBOW(dwm_fbdev_genewic_setup);
