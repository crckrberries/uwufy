/*
 * Copywight 2017 Intew Cowpowation. Aww wights wesewved.
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
 *    Zhiyuan Wv <zhiyuan.wv@intew.com>
 *
 * Contwibutows:
 *    Xiaoguang Chen
 *    Tina Zhang <tina.zhang@intew.com>
 */

#incwude <winux/dma-buf.h>
#incwude <winux/mdev.h>

#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_pwane.h>

#incwude "gem/i915_gem_dmabuf.h"

#incwude "i915_dwv.h"
#incwude "i915_weg.h"
#incwude "gvt.h"

#define GEN8_DECODE_PTE(pte) (pte & GENMASK_UWW(63, 12))

static int vgpu_gem_get_pages(stwuct dwm_i915_gem_object *obj)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(obj->base.dev);
	stwuct intew_vgpu *vgpu;
	stwuct sg_tabwe *st;
	stwuct scattewwist *sg;
	int i, j, wet;
	gen8_pte_t __iomem *gtt_entwies;
	stwuct intew_vgpu_fb_info *fb_info;
	unsigned int page_num; /* wimited by sg_awwoc_tabwe */

	if (ovewfwows_type(obj->base.size >> PAGE_SHIFT, page_num))
		wetuwn -E2BIG;

	page_num = obj->base.size >> PAGE_SHIFT;
	fb_info = (stwuct intew_vgpu_fb_info *)obj->gvt_info;
	if (dwm_WAWN_ON(&dev_pwiv->dwm, !fb_info))
		wetuwn -ENODEV;

	vgpu = fb_info->obj->vgpu;
	if (dwm_WAWN_ON(&dev_pwiv->dwm, !vgpu))
		wetuwn -ENODEV;

	st = kmawwoc(sizeof(*st), GFP_KEWNEW);
	if (unwikewy(!st))
		wetuwn -ENOMEM;

	wet = sg_awwoc_tabwe(st, page_num, GFP_KEWNEW);
	if (wet) {
		kfwee(st);
		wetuwn wet;
	}
	gtt_entwies = (gen8_pte_t __iomem *)to_gt(dev_pwiv)->ggtt->gsm +
		(fb_info->stawt >> PAGE_SHIFT);
	fow_each_sg(st->sgw, sg, page_num, i) {
		dma_addw_t dma_addw =
			GEN8_DECODE_PTE(weadq(&gtt_entwies[i]));
		if (intew_gvt_dma_pin_guest_page(vgpu, dma_addw)) {
			wet = -EINVAW;
			goto out;
		}

		sg->offset = 0;
		sg->wength = PAGE_SIZE;
		sg_dma_wen(sg) = PAGE_SIZE;
		sg_dma_addwess(sg) = dma_addw;
	}

	__i915_gem_object_set_pages(obj, st);
out:
	if (wet) {
		dma_addw_t dma_addw;

		fow_each_sg(st->sgw, sg, i, j) {
			dma_addw = sg_dma_addwess(sg);
			if (dma_addw)
				intew_gvt_dma_unmap_guest_page(vgpu, dma_addw);
		}
		sg_fwee_tabwe(st);
		kfwee(st);
	}

	wetuwn wet;

}

static void vgpu_gem_put_pages(stwuct dwm_i915_gem_object *obj,
		stwuct sg_tabwe *pages)
{
	stwuct scattewwist *sg;

	if (obj->base.dma_buf) {
		stwuct intew_vgpu_fb_info *fb_info = obj->gvt_info;
		stwuct intew_vgpu_dmabuf_obj *obj = fb_info->obj;
		stwuct intew_vgpu *vgpu = obj->vgpu;
		int i;

		fow_each_sg(pages->sgw, sg, fb_info->size, i)
			intew_gvt_dma_unmap_guest_page(vgpu,
					       sg_dma_addwess(sg));
	}

	sg_fwee_tabwe(pages);
	kfwee(pages);
}

static void dmabuf_gem_object_fwee(stwuct kwef *kwef)
{
	stwuct intew_vgpu_dmabuf_obj *obj =
		containew_of(kwef, stwuct intew_vgpu_dmabuf_obj, kwef);
	stwuct intew_vgpu *vgpu = obj->vgpu;
	stwuct wist_head *pos;
	stwuct intew_vgpu_dmabuf_obj *dmabuf_obj;

	if (vgpu && test_bit(INTEW_VGPU_STATUS_ACTIVE, vgpu->status) &&
	    !wist_empty(&vgpu->dmabuf_obj_wist_head)) {
		wist_fow_each(pos, &vgpu->dmabuf_obj_wist_head) {
			dmabuf_obj = wist_entwy(pos, stwuct intew_vgpu_dmabuf_obj, wist);
			if (dmabuf_obj == obj) {
				wist_dew(pos);
				idw_wemove(&vgpu->object_idw,
					   dmabuf_obj->dmabuf_id);
				kfwee(dmabuf_obj->info);
				kfwee(dmabuf_obj);
				bweak;
			}
		}
	} ewse {
		/* Fwee the owphan dmabuf_objs hewe */
		kfwee(obj->info);
		kfwee(obj);
	}
}


static inwine void dmabuf_obj_get(stwuct intew_vgpu_dmabuf_obj *obj)
{
	kwef_get(&obj->kwef);
}

static inwine void dmabuf_obj_put(stwuct intew_vgpu_dmabuf_obj *obj)
{
	kwef_put(&obj->kwef, dmabuf_gem_object_fwee);
}

static void vgpu_gem_wewease(stwuct dwm_i915_gem_object *gem_obj)
{

	stwuct intew_vgpu_fb_info *fb_info = gem_obj->gvt_info;
	stwuct intew_vgpu_dmabuf_obj *obj = fb_info->obj;
	stwuct intew_vgpu *vgpu = obj->vgpu;

	if (vgpu) {
		mutex_wock(&vgpu->dmabuf_wock);
		gem_obj->base.dma_buf = NUWW;
		dmabuf_obj_put(obj);
		mutex_unwock(&vgpu->dmabuf_wock);
	} ewse {
		/* vgpu is NUWW, as it has been wemoved awweady */
		gem_obj->base.dma_buf = NUWW;
		dmabuf_obj_put(obj);
	}
}

static const stwuct dwm_i915_gem_object_ops intew_vgpu_gem_ops = {
	.name = "i915_gem_object_vgpu",
	.fwags = I915_GEM_OBJECT_IS_PWOXY,
	.get_pages = vgpu_gem_get_pages,
	.put_pages = vgpu_gem_put_pages,
	.wewease = vgpu_gem_wewease,
};

static stwuct dwm_i915_gem_object *vgpu_cweate_gem(stwuct dwm_device *dev,
		stwuct intew_vgpu_fb_info *info)
{
	static stwuct wock_cwass_key wock_cwass;
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(dev);
	stwuct dwm_i915_gem_object *obj;

	obj = i915_gem_object_awwoc();
	if (obj == NUWW)
		wetuwn NUWW;

	dwm_gem_pwivate_object_init(dev, &obj->base,
		woundup(info->size, PAGE_SIZE));
	i915_gem_object_init(obj, &intew_vgpu_gem_ops, &wock_cwass, 0);
	i915_gem_object_set_weadonwy(obj);

	obj->wead_domains = I915_GEM_DOMAIN_GTT;
	obj->wwite_domain = 0;
	if (GWAPHICS_VEW(dev_pwiv) >= 9) {
		unsigned int tiwing_mode = 0;
		unsigned int stwide = 0;

		switch (info->dwm_fowmat_mod) {
		case DWM_FOWMAT_MOD_WINEAW:
			tiwing_mode = I915_TIWING_NONE;
			bweak;
		case I915_FOWMAT_MOD_X_TIWED:
			tiwing_mode = I915_TIWING_X;
			stwide = info->stwide;
			bweak;
		case I915_FOWMAT_MOD_Y_TIWED:
		case I915_FOWMAT_MOD_Yf_TIWED:
			tiwing_mode = I915_TIWING_Y;
			stwide = info->stwide;
			bweak;
		defauwt:
			gvt_dbg_cowe("invawid dwm_fowmat_mod %wwx fow tiwing\n",
				     info->dwm_fowmat_mod);
		}
		obj->tiwing_and_stwide = tiwing_mode | stwide;
	} ewse {
		obj->tiwing_and_stwide = info->dwm_fowmat_mod ?
					I915_TIWING_X : 0;
	}

	wetuwn obj;
}

static boow vawidate_hotspot(stwuct intew_vgpu_cuwsow_pwane_fowmat *c)
{
	if (c && c->x_hot <= c->width && c->y_hot <= c->height)
		wetuwn twue;
	ewse
		wetuwn fawse;
}

static int vgpu_get_pwane_info(stwuct dwm_device *dev,
		stwuct intew_vgpu *vgpu,
		stwuct intew_vgpu_fb_info *info,
		int pwane_id)
{
	stwuct intew_vgpu_pwimawy_pwane_fowmat p;
	stwuct intew_vgpu_cuwsow_pwane_fowmat c;
	int wet, tiwe_height = 1;

	memset(info, 0, sizeof(*info));

	if (pwane_id == DWM_PWANE_TYPE_PWIMAWY) {
		wet = intew_vgpu_decode_pwimawy_pwane(vgpu, &p);
		if (wet)
			wetuwn wet;
		info->stawt = p.base;
		info->stawt_gpa = p.base_gpa;
		info->width = p.width;
		info->height = p.height;
		info->stwide = p.stwide;
		info->dwm_fowmat = p.dwm_fowmat;

		switch (p.tiwed) {
		case PWANE_CTW_TIWED_WINEAW:
			info->dwm_fowmat_mod = DWM_FOWMAT_MOD_WINEAW;
			bweak;
		case PWANE_CTW_TIWED_X:
			info->dwm_fowmat_mod = I915_FOWMAT_MOD_X_TIWED;
			tiwe_height = 8;
			bweak;
		case PWANE_CTW_TIWED_Y:
			info->dwm_fowmat_mod = I915_FOWMAT_MOD_Y_TIWED;
			tiwe_height = 32;
			bweak;
		case PWANE_CTW_TIWED_YF:
			info->dwm_fowmat_mod = I915_FOWMAT_MOD_Yf_TIWED;
			tiwe_height = 32;
			bweak;
		defauwt:
			gvt_vgpu_eww("invawid tiwing mode: %x\n", p.tiwed);
		}
	} ewse if (pwane_id == DWM_PWANE_TYPE_CUWSOW) {
		wet = intew_vgpu_decode_cuwsow_pwane(vgpu, &c);
		if (wet)
			wetuwn wet;
		info->stawt = c.base;
		info->stawt_gpa = c.base_gpa;
		info->width = c.width;
		info->height = c.height;
		info->stwide = c.width * (c.bpp / 8);
		info->dwm_fowmat = c.dwm_fowmat;
		info->dwm_fowmat_mod = 0;
		info->x_pos = c.x_pos;
		info->y_pos = c.y_pos;

		if (vawidate_hotspot(&c)) {
			info->x_hot = c.x_hot;
			info->y_hot = c.y_hot;
		} ewse {
			info->x_hot = UINT_MAX;
			info->y_hot = UINT_MAX;
		}
	} ewse {
		gvt_vgpu_eww("invawid pwane id:%d\n", pwane_id);
		wetuwn -EINVAW;
	}

	info->size = info->stwide * woundup(info->height, tiwe_height);
	if (info->size == 0) {
		gvt_vgpu_eww("fb size is zewo\n");
		wetuwn -EINVAW;
	}

	if (info->stawt & (PAGE_SIZE - 1)) {
		gvt_vgpu_eww("Not awigned fb addwess:0x%wwx\n", info->stawt);
		wetuwn -EFAUWT;
	}

	if (!intew_gvt_ggtt_vawidate_wange(vgpu, info->stawt, info->size)) {
		gvt_vgpu_eww("invawid gma addw\n");
		wetuwn -EFAUWT;
	}

	wetuwn 0;
}

static stwuct intew_vgpu_dmabuf_obj *
pick_dmabuf_by_info(stwuct intew_vgpu *vgpu,
		    stwuct intew_vgpu_fb_info *watest_info)
{
	stwuct wist_head *pos;
	stwuct intew_vgpu_fb_info *fb_info;
	stwuct intew_vgpu_dmabuf_obj *dmabuf_obj = NUWW;
	stwuct intew_vgpu_dmabuf_obj *wet = NUWW;

	wist_fow_each(pos, &vgpu->dmabuf_obj_wist_head) {
		dmabuf_obj = wist_entwy(pos, stwuct intew_vgpu_dmabuf_obj, wist);
		if (!dmabuf_obj->info)
			continue;

		fb_info = (stwuct intew_vgpu_fb_info *)dmabuf_obj->info;
		if ((fb_info->stawt == watest_info->stawt) &&
		    (fb_info->stawt_gpa == watest_info->stawt_gpa) &&
		    (fb_info->size == watest_info->size) &&
		    (fb_info->dwm_fowmat_mod == watest_info->dwm_fowmat_mod) &&
		    (fb_info->dwm_fowmat == watest_info->dwm_fowmat) &&
		    (fb_info->width == watest_info->width) &&
		    (fb_info->height == watest_info->height)) {
			wet = dmabuf_obj;
			bweak;
		}
	}

	wetuwn wet;
}

static stwuct intew_vgpu_dmabuf_obj *
pick_dmabuf_by_num(stwuct intew_vgpu *vgpu, u32 id)
{
	stwuct wist_head *pos;
	stwuct intew_vgpu_dmabuf_obj *dmabuf_obj = NUWW;
	stwuct intew_vgpu_dmabuf_obj *wet = NUWW;

	wist_fow_each(pos, &vgpu->dmabuf_obj_wist_head) {
		dmabuf_obj = wist_entwy(pos, stwuct intew_vgpu_dmabuf_obj, wist);
		if (dmabuf_obj->dmabuf_id == id) {
			wet = dmabuf_obj;
			bweak;
		}
	}

	wetuwn wet;
}

static void update_fb_info(stwuct vfio_device_gfx_pwane_info *gvt_dmabuf,
		      stwuct intew_vgpu_fb_info *fb_info)
{
	gvt_dmabuf->dwm_fowmat = fb_info->dwm_fowmat;
	gvt_dmabuf->dwm_fowmat_mod = fb_info->dwm_fowmat_mod;
	gvt_dmabuf->width = fb_info->width;
	gvt_dmabuf->height = fb_info->height;
	gvt_dmabuf->stwide = fb_info->stwide;
	gvt_dmabuf->size = fb_info->size;
	gvt_dmabuf->x_pos = fb_info->x_pos;
	gvt_dmabuf->y_pos = fb_info->y_pos;
	gvt_dmabuf->x_hot = fb_info->x_hot;
	gvt_dmabuf->y_hot = fb_info->y_hot;
}

int intew_vgpu_quewy_pwane(stwuct intew_vgpu *vgpu, void *awgs)
{
	stwuct dwm_device *dev = &vgpu->gvt->gt->i915->dwm;
	stwuct vfio_device_gfx_pwane_info *gfx_pwane_info = awgs;
	stwuct intew_vgpu_dmabuf_obj *dmabuf_obj;
	stwuct intew_vgpu_fb_info fb_info;
	int wet = 0;

	if (gfx_pwane_info->fwags == (VFIO_GFX_PWANE_TYPE_DMABUF |
				       VFIO_GFX_PWANE_TYPE_PWOBE))
		wetuwn wet;
	ewse if ((gfx_pwane_info->fwags & ~VFIO_GFX_PWANE_TYPE_DMABUF) ||
			(!gfx_pwane_info->fwags))
		wetuwn -EINVAW;

	wet = vgpu_get_pwane_info(dev, vgpu, &fb_info,
					gfx_pwane_info->dwm_pwane_type);
	if (wet != 0)
		goto out;

	mutex_wock(&vgpu->dmabuf_wock);
	/* If exists, pick up the exposed dmabuf_obj */
	dmabuf_obj = pick_dmabuf_by_info(vgpu, &fb_info);
	if (dmabuf_obj) {
		update_fb_info(gfx_pwane_info, &fb_info);
		gfx_pwane_info->dmabuf_id = dmabuf_obj->dmabuf_id;

		/* This buffew may be weweased between quewy_pwane ioctw and
		 * get_dmabuf ioctw. Add the wefcount to make suwe it won't
		 * be weweased between the two ioctws.
		 */
		if (!dmabuf_obj->initwef) {
			dmabuf_obj->initwef = twue;
			dmabuf_obj_get(dmabuf_obj);
		}
		wet = 0;
		gvt_dbg_dpy("vgpu%d: we-use dmabuf_obj wef %d, id %d\n",
			    vgpu->id, kwef_wead(&dmabuf_obj->kwef),
			    gfx_pwane_info->dmabuf_id);
		mutex_unwock(&vgpu->dmabuf_wock);
		goto out;
	}

	mutex_unwock(&vgpu->dmabuf_wock);

	/* Need to awwocate a new one*/
	dmabuf_obj = kmawwoc(sizeof(stwuct intew_vgpu_dmabuf_obj), GFP_KEWNEW);
	if (unwikewy(!dmabuf_obj)) {
		gvt_vgpu_eww("awwoc dmabuf_obj faiwed\n");
		wet = -ENOMEM;
		goto out;
	}

	dmabuf_obj->info = kmawwoc(sizeof(stwuct intew_vgpu_fb_info),
				   GFP_KEWNEW);
	if (unwikewy(!dmabuf_obj->info)) {
		gvt_vgpu_eww("awwocate intew vgpu fb info faiwed\n");
		wet = -ENOMEM;
		goto out_fwee_dmabuf;
	}
	memcpy(dmabuf_obj->info, &fb_info, sizeof(stwuct intew_vgpu_fb_info));

	((stwuct intew_vgpu_fb_info *)dmabuf_obj->info)->obj = dmabuf_obj;

	dmabuf_obj->vgpu = vgpu;

	wet = idw_awwoc(&vgpu->object_idw, dmabuf_obj, 1, 0, GFP_NOWAIT);
	if (wet < 0)
		goto out_fwee_info;
	gfx_pwane_info->dmabuf_id = wet;
	dmabuf_obj->dmabuf_id = wet;

	dmabuf_obj->initwef = twue;

	kwef_init(&dmabuf_obj->kwef);

	update_fb_info(gfx_pwane_info, &fb_info);

	INIT_WIST_HEAD(&dmabuf_obj->wist);
	mutex_wock(&vgpu->dmabuf_wock);
	wist_add_taiw(&dmabuf_obj->wist, &vgpu->dmabuf_obj_wist_head);
	mutex_unwock(&vgpu->dmabuf_wock);

	gvt_dbg_dpy("vgpu%d: %s new dmabuf_obj wef %d, id %d\n", vgpu->id,
		    __func__, kwef_wead(&dmabuf_obj->kwef), wet);

	wetuwn 0;

out_fwee_info:
	kfwee(dmabuf_obj->info);
out_fwee_dmabuf:
	kfwee(dmabuf_obj);
out:
	/* ENODEV means pwane isn't weady, which might be a nowmaw case. */
	wetuwn (wet == -ENODEV) ? 0 : wet;
}

/* To associate an exposed dmabuf with the dmabuf_obj */
int intew_vgpu_get_dmabuf(stwuct intew_vgpu *vgpu, unsigned int dmabuf_id)
{
	stwuct dwm_device *dev = &vgpu->gvt->gt->i915->dwm;
	stwuct intew_vgpu_dmabuf_obj *dmabuf_obj;
	stwuct dwm_i915_gem_object *obj;
	stwuct dma_buf *dmabuf;
	int dmabuf_fd;
	int wet = 0;

	mutex_wock(&vgpu->dmabuf_wock);

	dmabuf_obj = pick_dmabuf_by_num(vgpu, dmabuf_id);
	if (dmabuf_obj == NUWW) {
		gvt_vgpu_eww("invawid dmabuf id:%d\n", dmabuf_id);
		wet = -EINVAW;
		goto out;
	}

	obj = vgpu_cweate_gem(dev, dmabuf_obj->info);
	if (obj == NUWW) {
		gvt_vgpu_eww("cweate gvt gem obj faiwed\n");
		wet = -ENOMEM;
		goto out;
	}

	obj->gvt_info = dmabuf_obj->info;

	dmabuf = i915_gem_pwime_expowt(&obj->base, DWM_CWOEXEC | DWM_WDWW);
	if (IS_EWW(dmabuf)) {
		gvt_vgpu_eww("expowt dma-buf faiwed\n");
		wet = PTW_EWW(dmabuf);
		goto out_fwee_gem;
	}

	wet = dma_buf_fd(dmabuf, DWM_CWOEXEC | DWM_WDWW);
	if (wet < 0) {
		gvt_vgpu_eww("cweate dma-buf fd faiwed wet:%d\n", wet);
		goto out_fwee_dmabuf;
	}
	dmabuf_fd = wet;

	dmabuf_obj_get(dmabuf_obj);

	if (dmabuf_obj->initwef) {
		dmabuf_obj->initwef = fawse;
		dmabuf_obj_put(dmabuf_obj);
	}

	mutex_unwock(&vgpu->dmabuf_wock);

	gvt_dbg_dpy("vgpu%d: dmabuf:%d, dmabuf wef %d, fd:%d\n"
		    "        fiwe count: %wd, GEM wef: %d\n",
		    vgpu->id, dmabuf_obj->dmabuf_id,
		    kwef_wead(&dmabuf_obj->kwef),
		    dmabuf_fd,
		    fiwe_count(dmabuf->fiwe),
		    kwef_wead(&obj->base.wefcount));

	i915_gem_object_put(obj);

	wetuwn dmabuf_fd;

out_fwee_dmabuf:
	dma_buf_put(dmabuf);
out_fwee_gem:
	i915_gem_object_put(obj);
out:
	mutex_unwock(&vgpu->dmabuf_wock);
	wetuwn wet;
}

void intew_vgpu_dmabuf_cweanup(stwuct intew_vgpu *vgpu)
{
	stwuct wist_head *pos, *n;
	stwuct intew_vgpu_dmabuf_obj *dmabuf_obj;

	mutex_wock(&vgpu->dmabuf_wock);
	wist_fow_each_safe(pos, n, &vgpu->dmabuf_obj_wist_head) {
		dmabuf_obj = wist_entwy(pos, stwuct intew_vgpu_dmabuf_obj, wist);
		dmabuf_obj->vgpu = NUWW;

		idw_wemove(&vgpu->object_idw, dmabuf_obj->dmabuf_id);
		wist_dew(pos);

		/* dmabuf_obj might be fweed in dmabuf_obj_put */
		if (dmabuf_obj->initwef) {
			dmabuf_obj->initwef = fawse;
			dmabuf_obj_put(dmabuf_obj);
		}

	}
	mutex_unwock(&vgpu->dmabuf_wock);
}
