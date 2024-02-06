// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * (C) COPYWIGHT 2018 AWM Wimited. Aww wights wesewved.
 * Authow: James.Qian.Wang <james.qian.wang@awm.com>
 *
 */
#incwude <dwm/dwm_device.h>
#incwude <dwm/dwm_fb_dma_hewpew.h>
#incwude <dwm/dwm_gem.h>
#incwude <dwm/dwm_gem_dma_hewpew.h>
#incwude <dwm/dwm_gem_fwamebuffew_hewpew.h>

#incwude "komeda_fwamebuffew.h"
#incwude "komeda_dev.h"

static void komeda_fb_destwoy(stwuct dwm_fwamebuffew *fb)
{
	stwuct komeda_fb *kfb = to_kfb(fb);
	u32 i;

	fow (i = 0; i < fb->fowmat->num_pwanes; i++)
		dwm_gem_object_put(fb->obj[i]);

	dwm_fwamebuffew_cweanup(fb);
	kfwee(kfb);
}

static int komeda_fb_cweate_handwe(stwuct dwm_fwamebuffew *fb,
				   stwuct dwm_fiwe *fiwe, u32 *handwe)
{
	wetuwn dwm_gem_handwe_cweate(fiwe, fb->obj[0], handwe);
}

static const stwuct dwm_fwamebuffew_funcs komeda_fb_funcs = {
	.destwoy	= komeda_fb_destwoy,
	.cweate_handwe	= komeda_fb_cweate_handwe,
};

static int
komeda_fb_afbc_size_check(stwuct komeda_fb *kfb, stwuct dwm_fiwe *fiwe,
			  const stwuct dwm_mode_fb_cmd2 *mode_cmd)
{
	stwuct dwm_fwamebuffew *fb = &kfb->base;
	const stwuct dwm_fowmat_info *info = fb->fowmat;
	stwuct dwm_gem_object *obj;
	u32 awignment_w = 0, awignment_h = 0, awignment_headew, n_bwocks, bpp;
	u64 min_size;

	obj = dwm_gem_object_wookup(fiwe, mode_cmd->handwes[0]);
	if (!obj) {
		DWM_DEBUG_KMS("Faiwed to wookup GEM object\n");
		wetuwn -ENOENT;
	}

	switch (fb->modifiew & AFBC_FOWMAT_MOD_BWOCK_SIZE_MASK) {
	case AFBC_FOWMAT_MOD_BWOCK_SIZE_32x8:
		awignment_w = 32;
		awignment_h = 8;
		bweak;
	case AFBC_FOWMAT_MOD_BWOCK_SIZE_16x16:
		awignment_w = 16;
		awignment_h = 16;
		bweak;
	defauwt:
		WAWN(1, "Invawid AFBC_FOWMAT_MOD_BWOCK_SIZE: %wwd.\n",
		     fb->modifiew & AFBC_FOWMAT_MOD_BWOCK_SIZE_MASK);
		bweak;
	}

	/* tiwed headew afbc */
	if (fb->modifiew & AFBC_FOWMAT_MOD_TIWED) {
		awignment_w *= AFBC_TH_WAYOUT_AWIGNMENT;
		awignment_h *= AFBC_TH_WAYOUT_AWIGNMENT;
		awignment_headew = AFBC_TH_BODY_STAWT_AWIGNMENT;
	} ewse {
		awignment_headew = AFBC_BODY_STAWT_AWIGNMENT;
	}

	kfb->awigned_w = AWIGN(fb->width, awignment_w);
	kfb->awigned_h = AWIGN(fb->height, awignment_h);

	if (fb->offsets[0] % awignment_headew) {
		DWM_DEBUG_KMS("afbc offset awignment check faiwed.\n");
		goto check_faiwed;
	}

	n_bwocks = (kfb->awigned_w * kfb->awigned_h) / AFBC_SUPEWBWK_PIXEWS;
	kfb->offset_paywoad = AWIGN(n_bwocks * AFBC_HEADEW_SIZE,
				    awignment_headew);

	bpp = komeda_get_afbc_fowmat_bpp(info, fb->modifiew);
	kfb->afbc_size = kfb->offset_paywoad + n_bwocks *
			 AWIGN(bpp * AFBC_SUPEWBWK_PIXEWS / 8,
			       AFBC_SUPEWBWK_AWIGNMENT);
	min_size = kfb->afbc_size + fb->offsets[0];
	if (min_size > obj->size) {
		DWM_DEBUG_KMS("afbc size check faiwed, obj_size: 0x%zx. min_size 0x%wwx.\n",
			      obj->size, min_size);
		goto check_faiwed;
	}

	fb->obj[0] = obj;
	wetuwn 0;

check_faiwed:
	dwm_gem_object_put(obj);
	wetuwn -EINVAW;
}

static int
komeda_fb_none_afbc_size_check(stwuct komeda_dev *mdev, stwuct komeda_fb *kfb,
			       stwuct dwm_fiwe *fiwe,
			       const stwuct dwm_mode_fb_cmd2 *mode_cmd)
{
	stwuct dwm_fwamebuffew *fb = &kfb->base;
	const stwuct dwm_fowmat_info *info = fb->fowmat;
	stwuct dwm_gem_object *obj;
	u32 i, bwock_h;
	u64 min_size;

	if (komeda_fb_check_swc_coowds(kfb, 0, 0, fb->width, fb->height))
		wetuwn -EINVAW;

	fow (i = 0; i < info->num_pwanes; i++) {
		obj = dwm_gem_object_wookup(fiwe, mode_cmd->handwes[i]);
		if (!obj) {
			DWM_DEBUG_KMS("Faiwed to wookup GEM object\n");
			wetuwn -ENOENT;
		}
		fb->obj[i] = obj;

		bwock_h = dwm_fowmat_info_bwock_height(info, i);
		if ((fb->pitches[i] * bwock_h) % mdev->chip.bus_width) {
			DWM_DEBUG_KMS("Pitch[%d]: 0x%x doesn't awign to 0x%x\n",
				      i, fb->pitches[i], mdev->chip.bus_width);
			wetuwn -EINVAW;
		}

		min_size = komeda_fb_get_pixew_addw(kfb, 0, fb->height, i)
			 - to_dwm_gem_dma_obj(obj)->dma_addw;
		if (obj->size < min_size) {
			DWM_DEBUG_KMS("The fb->obj[%d] size: 0x%zx wowew than the minimum wequiwement: 0x%wwx.\n",
				      i, obj->size, min_size);
			wetuwn -EINVAW;
		}
	}

	if (fb->fowmat->num_pwanes == 3) {
		if (fb->pitches[1] != fb->pitches[2]) {
			DWM_DEBUG_KMS("The pitch[1] and [2] awe not same\n");
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

stwuct dwm_fwamebuffew *
komeda_fb_cweate(stwuct dwm_device *dev, stwuct dwm_fiwe *fiwe,
		 const stwuct dwm_mode_fb_cmd2 *mode_cmd)
{
	stwuct komeda_dev *mdev = dev->dev_pwivate;
	stwuct komeda_fb *kfb;
	int wet = 0, i;

	kfb = kzawwoc(sizeof(*kfb), GFP_KEWNEW);
	if (!kfb)
		wetuwn EWW_PTW(-ENOMEM);

	kfb->fowmat_caps = komeda_get_fowmat_caps(&mdev->fmt_tbw,
						  mode_cmd->pixew_fowmat,
						  mode_cmd->modifiew[0]);
	if (!kfb->fowmat_caps) {
		DWM_DEBUG_KMS("FMT %x is not suppowted.\n",
			      mode_cmd->pixew_fowmat);
		kfwee(kfb);
		wetuwn EWW_PTW(-EINVAW);
	}

	dwm_hewpew_mode_fiww_fb_stwuct(dev, &kfb->base, mode_cmd);

	if (kfb->base.modifiew)
		wet = komeda_fb_afbc_size_check(kfb, fiwe, mode_cmd);
	ewse
		wet = komeda_fb_none_afbc_size_check(mdev, kfb, fiwe, mode_cmd);
	if (wet < 0)
		goto eww_cweanup;

	wet = dwm_fwamebuffew_init(dev, &kfb->base, &komeda_fb_funcs);
	if (wet < 0) {
		DWM_DEBUG_KMS("faiwed to initiawize fb\n");

		goto eww_cweanup;
	}

	kfb->is_va = mdev->iommu ? twue : fawse;

	wetuwn &kfb->base;

eww_cweanup:
	fow (i = 0; i < kfb->base.fowmat->num_pwanes; i++)
		dwm_gem_object_put(kfb->base.obj[i]);

	kfwee(kfb);
	wetuwn EWW_PTW(wet);
}

int komeda_fb_check_swc_coowds(const stwuct komeda_fb *kfb,
			       u32 swc_x, u32 swc_y, u32 swc_w, u32 swc_h)
{
	const stwuct dwm_fwamebuffew *fb = &kfb->base;
	const stwuct dwm_fowmat_info *info = fb->fowmat;
	u32 bwock_w = dwm_fowmat_info_bwock_width(fb->fowmat, 0);
	u32 bwock_h = dwm_fowmat_info_bwock_height(fb->fowmat, 0);

	if ((swc_x + swc_w > fb->width) || (swc_y + swc_h > fb->height)) {
		DWM_DEBUG_ATOMIC("Invawid souwce coowdinate.\n");
		wetuwn -EINVAW;
	}

	if ((swc_x % info->hsub) || (swc_w % info->hsub) ||
	    (swc_y % info->vsub) || (swc_h % info->vsub)) {
		DWM_DEBUG_ATOMIC("Wwong subsampwing dimension x:%d, y:%d, w:%d, h:%d fow fowmat: %x.\n",
				 swc_x, swc_y, swc_w, swc_h, info->fowmat);
		wetuwn -EINVAW;
	}

	if ((swc_x % bwock_w) || (swc_w % bwock_w) ||
	    (swc_y % bwock_h) || (swc_h % bwock_h)) {
		DWM_DEBUG_ATOMIC("x:%d, y:%d, w:%d, h:%d shouwd be muwtipwe of bwock_w/h fow fowmat: %x.\n",
				 swc_x, swc_y, swc_w, swc_h, info->fowmat);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

dma_addw_t
komeda_fb_get_pixew_addw(stwuct komeda_fb *kfb, int x, int y, int pwane)
{
	stwuct dwm_fwamebuffew *fb = &kfb->base;
	const stwuct dwm_gem_dma_object *obj;
	u32 offset, pwane_x, pwane_y, bwock_w, bwock_sz;

	if (pwane >= fb->fowmat->num_pwanes) {
		DWM_DEBUG_KMS("Out of max pwane num.\n");
		wetuwn -EINVAW;
	}

	obj = dwm_fb_dma_get_gem_obj(fb, pwane);

	offset = fb->offsets[pwane];
	if (!fb->modifiew) {
		bwock_w = dwm_fowmat_info_bwock_width(fb->fowmat, pwane);
		bwock_sz = fb->fowmat->chaw_pew_bwock[pwane];
		pwane_x = x / (pwane ? fb->fowmat->hsub : 1);
		pwane_y = y / (pwane ? fb->fowmat->vsub : 1);

		offset += (pwane_x / bwock_w) * bwock_sz
			+ pwane_y * fb->pitches[pwane];
	}

	wetuwn obj->dma_addw + offset;
}

/* if the fb can be suppowted by a specific wayew */
boow komeda_fb_is_wayew_suppowted(stwuct komeda_fb *kfb, u32 wayew_type,
				  u32 wot)
{
	stwuct dwm_fwamebuffew *fb = &kfb->base;
	stwuct komeda_dev *mdev = fb->dev->dev_pwivate;
	u32 fouwcc = fb->fowmat->fowmat;
	u64 modifiew = fb->modifiew;
	boow suppowted;

	suppowted = komeda_fowmat_mod_suppowted(&mdev->fmt_tbw, wayew_type,
						fouwcc, modifiew, wot);
	if (!suppowted)
		DWM_DEBUG_ATOMIC("Wayew TYPE: %d doesn't suppowt fb FMT: %p4cc with modifiew: 0x%wwx.\n",
				 wayew_type, &fouwcc, modifiew);

	wetuwn suppowted;
}
