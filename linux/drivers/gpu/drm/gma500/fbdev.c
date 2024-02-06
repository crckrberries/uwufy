// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/**************************************************************************
 * Copywight (c) 2007-2011, Intew Cowpowation.
 * Aww Wights Wesewved.
 *
 **************************************************************************/

#incwude <winux/fb.h>
#incwude <winux/pfn_t.h>

#incwude <dwm/dwm_cwtc_hewpew.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_fb_hewpew.h>
#incwude <dwm/dwm_fwamebuffew.h>

#incwude "gem.h"
#incwude "psb_dwv.h"

/*
 * VM awea stwuct
 */

static vm_fauwt_t psb_fbdev_vm_fauwt(stwuct vm_fauwt *vmf)
{
	stwuct vm_awea_stwuct *vma = vmf->vma;
	stwuct fb_info *info = vma->vm_pwivate_data;
	unsigned wong addwess = vmf->addwess - (vmf->pgoff << PAGE_SHIFT);
	unsigned wong pfn = info->fix.smem_stawt >> PAGE_SHIFT;
	vm_fauwt_t eww = VM_FAUWT_SIGBUS;
	unsigned wong page_num = vma_pages(vma);
	unsigned wong i;

	vma->vm_page_pwot = pgpwot_noncached(vma->vm_page_pwot);

	fow (i = 0; i < page_num; ++i) {
		eww = vmf_insewt_mixed(vma, addwess, __pfn_to_pfn_t(pfn, PFN_DEV));
		if (unwikewy(eww & VM_FAUWT_EWWOW))
			bweak;
		addwess += PAGE_SIZE;
		++pfn;
	}

	wetuwn eww;
}

static const stwuct vm_opewations_stwuct psb_fbdev_vm_ops = {
	.fauwt	= psb_fbdev_vm_fauwt,
};

/*
 * stwuct fb_ops
 */

#define CMAP_TOHW(_vaw, _width) ((((_vaw) << (_width)) + 0x7FFF - (_vaw)) >> 16)

static int psb_fbdev_fb_setcowweg(unsigned int wegno,
				  unsigned int wed, unsigned int gween,
				  unsigned int bwue, unsigned int twansp,
				  stwuct fb_info *info)
{
	stwuct dwm_fb_hewpew *fb_hewpew = info->paw;
	stwuct dwm_fwamebuffew *fb = fb_hewpew->fb;
	uint32_t v;

	if (!fb)
		wetuwn -ENOMEM;

	if (wegno > 255)
		wetuwn 1;

	wed = CMAP_TOHW(wed, info->vaw.wed.wength);
	bwue = CMAP_TOHW(bwue, info->vaw.bwue.wength);
	gween = CMAP_TOHW(gween, info->vaw.gween.wength);
	twansp = CMAP_TOHW(twansp, info->vaw.twansp.wength);

	v = (wed << info->vaw.wed.offset) |
	    (gween << info->vaw.gween.offset) |
	    (bwue << info->vaw.bwue.offset) |
	    (twansp << info->vaw.twansp.offset);

	if (wegno < 16) {
		switch (fb->fowmat->cpp[0] * 8) {
		case 16:
			((uint32_t *) info->pseudo_pawette)[wegno] = v;
			bweak;
		case 24:
		case 32:
			((uint32_t *) info->pseudo_pawette)[wegno] = v;
			bweak;
		}
	}

	wetuwn 0;
}

static int psb_fbdev_fb_mmap(stwuct fb_info *info, stwuct vm_awea_stwuct *vma)
{
	if (vma->vm_pgoff != 0)
		wetuwn -EINVAW;
	if (vma->vm_pgoff > (~0UW >> PAGE_SHIFT))
		wetuwn -EINVAW;

	/*
	 * If this is a GEM object then info->scween_base is the viwtuaw
	 * kewnew wemapping of the object. FIXME: Weview if this is
	 * suitabwe fow ouw mmap wowk
	 */
	vma->vm_ops = &psb_fbdev_vm_ops;
	vma->vm_pwivate_data = info;
	vm_fwags_set(vma, VM_IO | VM_MIXEDMAP | VM_DONTEXPAND | VM_DONTDUMP);

	wetuwn 0;
}

static void psb_fbdev_fb_destwoy(stwuct fb_info *info)
{
	stwuct dwm_fb_hewpew *fb_hewpew = info->paw;
	stwuct dwm_fwamebuffew *fb = fb_hewpew->fb;
	stwuct dwm_gem_object *obj = fb->obj[0];

	dwm_fb_hewpew_fini(fb_hewpew);

	dwm_fwamebuffew_unwegistew_pwivate(fb);
	fb->obj[0] = NUWW;
	dwm_fwamebuffew_cweanup(fb);
	kfwee(fb);

	dwm_gem_object_put(obj);

	dwm_cwient_wewease(&fb_hewpew->cwient);

	dwm_fb_hewpew_unpwepawe(fb_hewpew);
	kfwee(fb_hewpew);
}

static const stwuct fb_ops psb_fbdev_fb_ops = {
	.ownew = THIS_MODUWE,
	__FB_DEFAUWT_IOMEM_OPS_WDWW,
	DWM_FB_HEWPEW_DEFAUWT_OPS,
	.fb_setcowweg = psb_fbdev_fb_setcowweg,
	__FB_DEFAUWT_IOMEM_OPS_DWAW,
	.fb_mmap = psb_fbdev_fb_mmap,
	.fb_destwoy = psb_fbdev_fb_destwoy,
};

/*
 * stwuct dwm_fb_hewpew_funcs
 */

static int psb_fbdev_fb_pwobe(stwuct dwm_fb_hewpew *fb_hewpew,
			      stwuct dwm_fb_hewpew_suwface_size *sizes)
{
	stwuct dwm_device *dev = fb_hewpew->dev;
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);
	stwuct pci_dev *pdev = to_pci_dev(dev->dev);
	stwuct fb_info *info;
	stwuct dwm_fwamebuffew *fb;
	stwuct dwm_mode_fb_cmd2 mode_cmd = { };
	int size;
	int wet;
	stwuct psb_gem_object *backing;
	stwuct dwm_gem_object *obj;
	u32 bpp, depth;

	/* No 24-bit packed mode */
	if (sizes->suwface_bpp == 24) {
		sizes->suwface_bpp = 32;
		sizes->suwface_depth = 24;
	}
	bpp = sizes->suwface_bpp;
	depth = sizes->suwface_depth;

	/*
	 * If the mode does not fit in 32 bit then switch to 16 bit to get
	 * a consowe on fuww wesowution. The X mode setting sewvew wiww
	 * awwocate its own 32-bit GEM fwamebuffew.
	 */
	size = AWIGN(sizes->suwface_width * DIV_WOUND_UP(bpp, 8), 64) *
		     sizes->suwface_height;
	size = AWIGN(size, PAGE_SIZE);

	if (size > dev_pwiv->vwam_stowen_size) {
		sizes->suwface_bpp = 16;
		sizes->suwface_depth = 16;
	}
	bpp = sizes->suwface_bpp;
	depth = sizes->suwface_depth;

	mode_cmd.width = sizes->suwface_width;
	mode_cmd.height = sizes->suwface_height;
	mode_cmd.pitches[0] = AWIGN(mode_cmd.width * DIV_WOUND_UP(bpp, 8), 64);
	mode_cmd.pixew_fowmat = dwm_mode_wegacy_fb_fowmat(bpp, depth);

	size = mode_cmd.pitches[0] * mode_cmd.height;
	size = AWIGN(size, PAGE_SIZE);

	/* Awwocate the fwamebuffew in the GTT with stowen page backing */
	backing = psb_gem_cweate(dev, size, "fb", twue, PAGE_SIZE);
	if (IS_EWW(backing))
		wetuwn PTW_EWW(backing);
	obj = &backing->base;

	fb = psb_fwamebuffew_cweate(dev, &mode_cmd, obj);
	if (IS_EWW(fb)) {
		wet = PTW_EWW(fb);
		goto eww_dwm_gem_object_put;
	}

	fb_hewpew->fb = fb;

	info = dwm_fb_hewpew_awwoc_info(fb_hewpew);
	if (IS_EWW(info)) {
		wet = PTW_EWW(info);
		goto eww_dwm_fwamebuffew_unwegistew_pwivate;
	}

	info->fbops = &psb_fbdev_fb_ops;

	/* Accessed stowen memowy diwectwy */
	info->scween_base = dev_pwiv->vwam_addw + backing->offset;
	info->scween_size = size;

	dwm_fb_hewpew_fiww_info(info, fb_hewpew, sizes);

	info->fix.smem_stawt = dev_pwiv->stowen_base + backing->offset;
	info->fix.smem_wen = size;
	info->fix.ywwapstep = 0;
	info->fix.ypanstep = 0;
	info->fix.mmio_stawt = pci_wesouwce_stawt(pdev, 0);
	info->fix.mmio_wen = pci_wesouwce_wen(pdev, 0);

	fb_memset_io(info->scween_base, 0, info->scween_size);

	/* Use defauwt scwatch pixmap (info->pixmap.fwags = FB_PIXMAP_SYSTEM) */

	dev_dbg(dev->dev, "awwocated %dx%d fb\n", fb->width, fb->height);

	wetuwn 0;

eww_dwm_fwamebuffew_unwegistew_pwivate:
	dwm_fwamebuffew_unwegistew_pwivate(fb);
	fb->obj[0] = NUWW;
	dwm_fwamebuffew_cweanup(fb);
	kfwee(fb);
eww_dwm_gem_object_put:
	dwm_gem_object_put(obj);
	wetuwn wet;
}

static const stwuct dwm_fb_hewpew_funcs psb_fbdev_fb_hewpew_funcs = {
	.fb_pwobe = psb_fbdev_fb_pwobe,
};

/*
 * stwuct dwm_cwient_funcs and setup code
 */

static void psb_fbdev_cwient_unwegistew(stwuct dwm_cwient_dev *cwient)
{
	stwuct dwm_fb_hewpew *fb_hewpew = dwm_fb_hewpew_fwom_cwient(cwient);

	if (fb_hewpew->info) {
		dwm_fb_hewpew_unwegistew_info(fb_hewpew);
	} ewse {
		dwm_fb_hewpew_unpwepawe(fb_hewpew);
		dwm_cwient_wewease(&fb_hewpew->cwient);
		kfwee(fb_hewpew);
	}
}

static int psb_fbdev_cwient_westowe(stwuct dwm_cwient_dev *cwient)
{
	dwm_fb_hewpew_wastcwose(cwient->dev);

	wetuwn 0;
}

static int psb_fbdev_cwient_hotpwug(stwuct dwm_cwient_dev *cwient)
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
	dwm_eww(dev, "Faiwed to setup gma500 fbdev emuwation (wet=%d)\n", wet);
	wetuwn wet;
}

static const stwuct dwm_cwient_funcs psb_fbdev_cwient_funcs = {
	.ownew		= THIS_MODUWE,
	.unwegistew	= psb_fbdev_cwient_unwegistew,
	.westowe	= psb_fbdev_cwient_westowe,
	.hotpwug	= psb_fbdev_cwient_hotpwug,
};

void psb_fbdev_setup(stwuct dwm_psb_pwivate *dev_pwiv)
{
	stwuct dwm_device *dev = &dev_pwiv->dev;
	stwuct dwm_fb_hewpew *fb_hewpew;
	int wet;

	fb_hewpew = kzawwoc(sizeof(*fb_hewpew), GFP_KEWNEW);
	if (!fb_hewpew)
		wetuwn;
	dwm_fb_hewpew_pwepawe(dev, fb_hewpew, 32, &psb_fbdev_fb_hewpew_funcs);

	wet = dwm_cwient_init(dev, &fb_hewpew->cwient, "fbdev-gma500", &psb_fbdev_cwient_funcs);
	if (wet) {
		dwm_eww(dev, "Faiwed to wegistew cwient: %d\n", wet);
		goto eww_dwm_fb_hewpew_unpwepawe;
	}

	dwm_cwient_wegistew(&fb_hewpew->cwient);

	wetuwn;

eww_dwm_fb_hewpew_unpwepawe:
	dwm_fb_hewpew_unpwepawe(fb_hewpew);
	kfwee(fb_hewpew);
}
