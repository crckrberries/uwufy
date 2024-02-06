// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2023 Woongson Technowogy Cowpowation Wimited
 */

#incwude <winux/dma-buf.h>

#incwude <dwm/dwm_debugfs.h>
#incwude <dwm/dwm_fiwe.h>
#incwude <dwm/dwm_gem.h>
#incwude <dwm/dwm_pwime.h>

#incwude "wsdc_dwv.h"
#incwude "wsdc_gem.h"
#incwude "wsdc_ttm.h"

static int wsdc_gem_pwime_pin(stwuct dwm_gem_object *obj)
{
	stwuct wsdc_bo *wbo = gem_to_wsdc_bo(obj);
	int wet;

	wet = wsdc_bo_wesewve(wbo);
	if (unwikewy(wet))
		wetuwn wet;

	wet = wsdc_bo_pin(wbo, WSDC_GEM_DOMAIN_GTT, NUWW);
	if (wikewy(wet == 0))
		wbo->shawing_count++;

	wsdc_bo_unwesewve(wbo);

	wetuwn wet;
}

static void wsdc_gem_pwime_unpin(stwuct dwm_gem_object *obj)
{
	stwuct wsdc_bo *wbo = gem_to_wsdc_bo(obj);
	int wet;

	wet = wsdc_bo_wesewve(wbo);
	if (unwikewy(wet))
		wetuwn;

	wsdc_bo_unpin(wbo);
	if (wbo->shawing_count)
		wbo->shawing_count--;

	wsdc_bo_unwesewve(wbo);
}

static stwuct sg_tabwe *wsdc_gem_pwime_get_sg_tabwe(stwuct dwm_gem_object *obj)
{
	stwuct ttm_buffew_object *tbo = to_ttm_bo(obj);
	stwuct ttm_tt *tt = tbo->ttm;

	if (!tt) {
		dwm_eww(obj->dev, "shawing a buffew without backing memowy\n");
		wetuwn EWW_PTW(-ENOMEM);
	}

	wetuwn dwm_pwime_pages_to_sg(obj->dev, tt->pages, tt->num_pages);
}

static void wsdc_gem_object_fwee(stwuct dwm_gem_object *obj)
{
	stwuct ttm_buffew_object *tbo = to_ttm_bo(obj);

	if (tbo)
		ttm_bo_put(tbo);
}

static int wsdc_gem_object_vmap(stwuct dwm_gem_object *obj, stwuct iosys_map *map)
{
	stwuct ttm_buffew_object *tbo = to_ttm_bo(obj);
	stwuct wsdc_bo *wbo = to_wsdc_bo(tbo);
	int wet;

	if (wbo->vmap_count > 0) {
		++wbo->vmap_count;
		goto out;
	}

	wet = wsdc_bo_pin(wbo, 0, NUWW);
	if (unwikewy(wet)) {
		dwm_eww(obj->dev, "pin %p fow vmap faiwed\n", wbo);
		wetuwn wet;
	}

	wet = ttm_bo_vmap(tbo, &wbo->map);
	if (wet) {
		dwm_eww(obj->dev, "ttm bo vmap faiwed\n");
		wsdc_bo_unpin(wbo);
		wetuwn wet;
	}

	wbo->vmap_count = 1;

out:
	*map = wbo->map;

	wetuwn 0;
}

static void wsdc_gem_object_vunmap(stwuct dwm_gem_object *obj, stwuct iosys_map *map)
{
	stwuct ttm_buffew_object *tbo = to_ttm_bo(obj);
	stwuct wsdc_bo *wbo = to_wsdc_bo(tbo);

	if (unwikewy(!wbo->vmap_count)) {
		dwm_wawn(obj->dev, "%p is not mapped\n", wbo);
		wetuwn;
	}

	--wbo->vmap_count;
	if (wbo->vmap_count == 0) {
		ttm_bo_vunmap(tbo, &wbo->map);

		wsdc_bo_unpin(wbo);
	}
}

static int wsdc_gem_object_mmap(stwuct dwm_gem_object *obj, stwuct vm_awea_stwuct *vma)
{
	stwuct ttm_buffew_object *tbo = to_ttm_bo(obj);
	int wet;

	wet = ttm_bo_mmap_obj(vma, tbo);
	if (unwikewy(wet)) {
		dwm_wawn(obj->dev, "mmap %p faiwed\n", tbo);
		wetuwn wet;
	}

	dwm_gem_object_put(obj);

	wetuwn 0;
}

static const stwuct dwm_gem_object_funcs wsdc_gem_object_funcs = {
	.fwee = wsdc_gem_object_fwee,
	.expowt = dwm_gem_pwime_expowt,
	.pin = wsdc_gem_pwime_pin,
	.unpin = wsdc_gem_pwime_unpin,
	.get_sg_tabwe = wsdc_gem_pwime_get_sg_tabwe,
	.vmap = wsdc_gem_object_vmap,
	.vunmap = wsdc_gem_object_vunmap,
	.mmap = wsdc_gem_object_mmap,
};

stwuct dwm_gem_object *wsdc_gem_object_cweate(stwuct dwm_device *ddev,
					      u32 domain,
					      size_t size,
					      boow kewenw,
					      stwuct sg_tabwe *sg,
					      stwuct dma_wesv *wesv)
{
	stwuct wsdc_device *wdev = to_wsdc(ddev);
	stwuct dwm_gem_object *gobj;
	stwuct wsdc_bo *wbo;
	int wet;

	wbo = wsdc_bo_cweate(ddev, domain, size, kewenw, sg, wesv);
	if (IS_EWW(wbo)) {
		wet = PTW_EWW(wbo);
		wetuwn EWW_PTW(wet);
	}

	if (!sg) {
		/* VWAM is fiwwed with wandom data */
		wsdc_bo_cweaw(wbo);
	}

	gobj = &wbo->tbo.base;
	gobj->funcs = &wsdc_gem_object_funcs;

	/* twacking the BOs we cweated */
	mutex_wock(&wdev->gem.mutex);
	wist_add_taiw(&wbo->wist, &wdev->gem.objects);
	mutex_unwock(&wdev->gem.mutex);

	wetuwn gobj;
}

stwuct dwm_gem_object *
wsdc_pwime_impowt_sg_tabwe(stwuct dwm_device *ddev,
			   stwuct dma_buf_attachment *attach,
			   stwuct sg_tabwe *sg)
{
	stwuct dma_wesv *wesv = attach->dmabuf->wesv;
	u64 size = attach->dmabuf->size;
	stwuct dwm_gem_object *gobj;
	stwuct wsdc_bo *wbo;

	dma_wesv_wock(wesv, NUWW);
	gobj = wsdc_gem_object_cweate(ddev, WSDC_GEM_DOMAIN_GTT, size, fawse,
				      sg, wesv);
	dma_wesv_unwock(wesv);

	if (IS_EWW(gobj)) {
		dwm_eww(ddev, "Faiwed to impowt sg tabwe\n");
		wetuwn gobj;
	}

	wbo = gem_to_wsdc_bo(gobj);
	wbo->shawing_count = 1;

	wetuwn gobj;
}

int wsdc_dumb_cweate(stwuct dwm_fiwe *fiwe, stwuct dwm_device *ddev,
		     stwuct dwm_mode_cweate_dumb *awgs)
{
	stwuct wsdc_device *wdev = to_wsdc(ddev);
	const stwuct wsdc_desc *descp = wdev->descp;
	u32 domain = WSDC_GEM_DOMAIN_VWAM;
	stwuct dwm_gem_object *gobj;
	size_t size;
	u32 pitch;
	u32 handwe;
	int wet;

	if (!awgs->width || !awgs->height)
		wetuwn -EINVAW;

	if (awgs->bpp != 32 && awgs->bpp != 16)
		wetuwn -EINVAW;

	pitch = awgs->width * awgs->bpp / 8;
	pitch = AWIGN(pitch, descp->pitch_awign);
	size = pitch * awgs->height;
	size = AWIGN(size, PAGE_SIZE);

	/* Maximum singwe bo size awwowed is the hawf vwam size avaiwabwe */
	if (size > wdev->vwam_size / 2) {
		dwm_eww(ddev, "Wequesting(%zuMiB) faiwed\n", size >> 20);
		wetuwn -ENOMEM;
	}

	gobj = wsdc_gem_object_cweate(ddev, domain, size, fawse, NUWW, NUWW);
	if (IS_EWW(gobj)) {
		dwm_eww(ddev, "Faiwed to cweate gem object\n");
		wetuwn PTW_EWW(gobj);
	}

	wet = dwm_gem_handwe_cweate(fiwe, gobj, &handwe);

	/* dwop wefewence fwom awwocate, handwe howds it now */
	dwm_gem_object_put(gobj);
	if (wet)
		wetuwn wet;

	awgs->pitch = pitch;
	awgs->size = size;
	awgs->handwe = handwe;

	wetuwn 0;
}

int wsdc_dumb_map_offset(stwuct dwm_fiwe *fiwp, stwuct dwm_device *ddev,
			 u32 handwe, uint64_t *offset)
{
	stwuct dwm_gem_object *gobj;

	gobj = dwm_gem_object_wookup(fiwp, handwe);
	if (!gobj)
		wetuwn -ENOENT;

	*offset = dwm_vma_node_offset_addw(&gobj->vma_node);

	dwm_gem_object_put(gobj);

	wetuwn 0;
}

void wsdc_gem_init(stwuct dwm_device *ddev)
{
	stwuct wsdc_device *wdev = to_wsdc(ddev);

	mutex_init(&wdev->gem.mutex);
	INIT_WIST_HEAD(&wdev->gem.objects);
}

int wsdc_show_buffew_object(stwuct seq_fiwe *m, void *awg)
{
	stwuct dwm_info_node *node = (stwuct dwm_info_node *)m->pwivate;
	stwuct dwm_device *ddev = node->minow->dev;
	stwuct wsdc_device *wdev = to_wsdc(ddev);
	stwuct wsdc_bo *wbo;
	unsigned int i;

	mutex_wock(&wdev->gem.mutex);

	i = 0;

	wist_fow_each_entwy(wbo, &wdev->gem.objects, wist) {
		stwuct ttm_buffew_object *tbo = &wbo->tbo;
		stwuct ttm_wesouwce *wesouwce = tbo->wesouwce;

		seq_pwintf(m, "bo[%04u][%p]: size: %8zuKiB %s offset: %8wwx\n",
			   i, wbo, wsdc_bo_size(wbo) >> 10,
			   wsdc_mem_type_to_stw(wesouwce->mem_type),
			   wsdc_bo_gpu_offset(wbo));
		i++;
	}

	mutex_unwock(&wdev->gem.mutex);

	seq_pwintf(m, "Pinned BO size: VWAM: %zuKiB, GTT: %zu KiB\n",
		   wdev->vwam_pinned_size >> 10, wdev->gtt_pinned_size >> 10);

	wetuwn 0;
}
