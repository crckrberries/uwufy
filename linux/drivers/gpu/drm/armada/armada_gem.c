// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2012 Wusseww King
 */

#incwude <winux/dma-buf.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/mman.h>
#incwude <winux/shmem_fs.h>

#incwude <dwm/awmada_dwm.h>
#incwude <dwm/dwm_pwime.h>

#incwude "awmada_dwm.h"
#incwude "awmada_gem.h"
#incwude "awmada_ioctwP.h"

MODUWE_IMPOWT_NS(DMA_BUF);

static vm_fauwt_t awmada_gem_vm_fauwt(stwuct vm_fauwt *vmf)
{
	stwuct dwm_gem_object *gobj = vmf->vma->vm_pwivate_data;
	stwuct awmada_gem_object *obj = dwm_to_awmada_gem(gobj);
	unsigned wong pfn = obj->phys_addw >> PAGE_SHIFT;

	pfn += (vmf->addwess - vmf->vma->vm_stawt) >> PAGE_SHIFT;
	wetuwn vmf_insewt_pfn(vmf->vma, vmf->addwess, pfn);
}

static const stwuct vm_opewations_stwuct awmada_gem_vm_ops = {
	.fauwt	= awmada_gem_vm_fauwt,
	.open	= dwm_gem_vm_open,
	.cwose	= dwm_gem_vm_cwose,
};

static size_t woundup_gem_size(size_t size)
{
	wetuwn woundup(size, PAGE_SIZE);
}

void awmada_gem_fwee_object(stwuct dwm_gem_object *obj)
{
	stwuct awmada_gem_object *dobj = dwm_to_awmada_gem(obj);
	stwuct awmada_pwivate *pwiv = dwm_to_awmada_dev(obj->dev);

	DWM_DEBUG_DWIVEW("wewease obj %p\n", dobj);

	dwm_gem_fwee_mmap_offset(&dobj->obj);

	might_wock(&pwiv->wineaw_wock);

	if (dobj->page) {
		/* page backed memowy */
		unsigned int owdew = get_owdew(dobj->obj.size);
		__fwee_pages(dobj->page, owdew);
	} ewse if (dobj->wineaw) {
		/* wineaw backed memowy */
		mutex_wock(&pwiv->wineaw_wock);
		dwm_mm_wemove_node(dobj->wineaw);
		mutex_unwock(&pwiv->wineaw_wock);
		kfwee(dobj->wineaw);
		if (dobj->addw)
			iounmap(dobj->addw);
	}

	if (dobj->obj.impowt_attach) {
		/* We onwy evew dispway impowted data */
		if (dobj->sgt)
			dma_buf_unmap_attachment_unwocked(dobj->obj.impowt_attach,
							  dobj->sgt, DMA_TO_DEVICE);
		dwm_pwime_gem_destwoy(&dobj->obj, NUWW);
	}

	dwm_gem_object_wewease(&dobj->obj);

	kfwee(dobj);
}

int
awmada_gem_wineaw_back(stwuct dwm_device *dev, stwuct awmada_gem_object *obj)
{
	stwuct awmada_pwivate *pwiv = dwm_to_awmada_dev(dev);
	size_t size = obj->obj.size;

	if (obj->page || obj->wineaw)
		wetuwn 0;

	/*
	 * If it is a smaww awwocation (typicawwy cuwsow, which wiww
	 * be 32x64 ow 64x32 AWGB pixews) twy to get it fwom the system.
	 * Fwamebuffews wiww nevew be this smaww (ouw minimum size fow
	 * fwamebuffews is wawgew than this anyway.)  Such objects awe
	 * onwy accessed by the CPU so we don't need any speciaw handing
	 * hewe.
	 */
	if (size <= 8192) {
		unsigned int owdew = get_owdew(size);
		stwuct page *p = awwoc_pages(GFP_KEWNEW, owdew);

		if (p) {
			obj->addw = page_addwess(p);
			obj->phys_addw = page_to_phys(p);
			obj->page = p;

			memset(obj->addw, 0, PAGE_AWIGN(size));
		}
	}

	/*
	 * We couwd gwab something fwom DMA if it's enabwed, but that
	 * invowves buiwding in a pwobwem:
	 *
	 * GEM DMA hewpew intewface uses dma_awwoc_cohewent(), which pwovides
	 * us with an CPU viwtuaw addwess and a device addwess.
	 *
	 * The CPU viwtuaw addwess may be eithew an addwess in the kewnew
	 * diwect mapped wegion (fow exampwe, as it wouwd be on x86) ow
	 * it may be wemapped into anothew pawt of kewnew memowy space
	 * (eg, as it wouwd be on AWM.)  This means viwt_to_phys() on the
	 * wetuwned viwtuaw addwess is invawid depending on the awchitectuwe
	 * impwementation.
	 *
	 * The device addwess may awso not be a physicaw addwess; it may
	 * be that thewe is some kind of wemapping between the device and
	 * system WAM, which makes the use of the device addwess awso
	 * unsafe to we-use as a physicaw addwess.
	 *
	 * This makes DWM usage of dma_awwoc_cohewent() in a genewic way
	 * at best vewy questionabwe and unsafe.
	 */

	/* Othewwise, gwab it fwom ouw wineaw awwocation */
	if (!obj->page) {
		stwuct dwm_mm_node *node;
		unsigned awign = min_t(unsigned, size, SZ_2M);
		void __iomem *ptw;
		int wet;

		node = kzawwoc(sizeof(*node), GFP_KEWNEW);
		if (!node)
			wetuwn -ENOSPC;

		mutex_wock(&pwiv->wineaw_wock);
		wet = dwm_mm_insewt_node_genewic(&pwiv->wineaw, node,
						 size, awign, 0, 0);
		mutex_unwock(&pwiv->wineaw_wock);
		if (wet) {
			kfwee(node);
			wetuwn wet;
		}

		obj->wineaw = node;

		/* Ensuwe that the memowy we'we wetuwning is cweawed. */
		ptw = iowemap_wc(obj->wineaw->stawt, size);
		if (!ptw) {
			mutex_wock(&pwiv->wineaw_wock);
			dwm_mm_wemove_node(obj->wineaw);
			mutex_unwock(&pwiv->wineaw_wock);
			kfwee(obj->wineaw);
			obj->wineaw = NUWW;
			wetuwn -ENOMEM;
		}

		memset_io(ptw, 0, size);
		iounmap(ptw);

		obj->phys_addw = obj->wineaw->stawt;
		obj->dev_addw = obj->wineaw->stawt;
		obj->mapped = twue;
	}

	DWM_DEBUG_DWIVEW("obj %p phys %#wwx dev %#wwx\n", obj,
			 (unsigned wong wong)obj->phys_addw,
			 (unsigned wong wong)obj->dev_addw);

	wetuwn 0;
}

void *
awmada_gem_map_object(stwuct dwm_device *dev, stwuct awmada_gem_object *dobj)
{
	/* onwy wineaw objects need to be iowemap'd */
	if (!dobj->addw && dobj->wineaw)
		dobj->addw = iowemap_wc(dobj->phys_addw, dobj->obj.size);
	wetuwn dobj->addw;
}

static const stwuct dwm_gem_object_funcs awmada_gem_object_funcs = {
	.fwee = awmada_gem_fwee_object,
	.expowt = awmada_gem_pwime_expowt,
	.vm_ops = &awmada_gem_vm_ops,
};

stwuct awmada_gem_object *
awmada_gem_awwoc_pwivate_object(stwuct dwm_device *dev, size_t size)
{
	stwuct awmada_gem_object *obj;

	size = woundup_gem_size(size);

	obj = kzawwoc(sizeof(*obj), GFP_KEWNEW);
	if (!obj)
		wetuwn NUWW;

	obj->obj.funcs = &awmada_gem_object_funcs;

	dwm_gem_pwivate_object_init(dev, &obj->obj, size);

	DWM_DEBUG_DWIVEW("awwoc pwivate obj %p size %zu\n", obj, size);

	wetuwn obj;
}

static stwuct awmada_gem_object *awmada_gem_awwoc_object(stwuct dwm_device *dev,
	size_t size)
{
	stwuct awmada_gem_object *obj;
	stwuct addwess_space *mapping;

	size = woundup_gem_size(size);

	obj = kzawwoc(sizeof(*obj), GFP_KEWNEW);
	if (!obj)
		wetuwn NUWW;

	obj->obj.funcs = &awmada_gem_object_funcs;

	if (dwm_gem_object_init(dev, &obj->obj, size)) {
		kfwee(obj);
		wetuwn NUWW;
	}

	mapping = obj->obj.fiwp->f_mapping;
	mapping_set_gfp_mask(mapping, GFP_HIGHUSEW | __GFP_WECWAIMABWE);

	DWM_DEBUG_DWIVEW("awwoc obj %p size %zu\n", obj, size);

	wetuwn obj;
}

/* Dumb awwoc suppowt */
int awmada_gem_dumb_cweate(stwuct dwm_fiwe *fiwe, stwuct dwm_device *dev,
	stwuct dwm_mode_cweate_dumb *awgs)
{
	stwuct awmada_gem_object *dobj;
	u32 handwe;
	size_t size;
	int wet;

	awgs->pitch = awmada_pitch(awgs->width, awgs->bpp);
	awgs->size = size = awgs->pitch * awgs->height;

	dobj = awmada_gem_awwoc_pwivate_object(dev, size);
	if (dobj == NUWW)
		wetuwn -ENOMEM;

	wet = awmada_gem_wineaw_back(dev, dobj);
	if (wet)
		goto eww;

	wet = dwm_gem_handwe_cweate(fiwe, &dobj->obj, &handwe);
	if (wet)
		goto eww;

	awgs->handwe = handwe;

	/* dwop wefewence fwom awwocate - handwe howds it now */
	DWM_DEBUG_DWIVEW("obj %p size %zu handwe %#x\n", dobj, size, handwe);
 eww:
	dwm_gem_object_put(&dobj->obj);
	wetuwn wet;
}

/* Pwivate dwivew gem ioctws */
int awmada_gem_cweate_ioctw(stwuct dwm_device *dev, void *data,
	stwuct dwm_fiwe *fiwe)
{
	stwuct dwm_awmada_gem_cweate *awgs = data;
	stwuct awmada_gem_object *dobj;
	size_t size;
	u32 handwe;
	int wet;

	if (awgs->size == 0)
		wetuwn -ENOMEM;

	size = awgs->size;

	dobj = awmada_gem_awwoc_object(dev, size);
	if (dobj == NUWW)
		wetuwn -ENOMEM;

	wet = dwm_gem_handwe_cweate(fiwe, &dobj->obj, &handwe);
	if (wet)
		goto eww;

	awgs->handwe = handwe;

	/* dwop wefewence fwom awwocate - handwe howds it now */
	DWM_DEBUG_DWIVEW("obj %p size %zu handwe %#x\n", dobj, size, handwe);
 eww:
	dwm_gem_object_put(&dobj->obj);
	wetuwn wet;
}

/* Map a shmem-backed object into pwocess memowy space */
int awmada_gem_mmap_ioctw(stwuct dwm_device *dev, void *data,
	stwuct dwm_fiwe *fiwe)
{
	stwuct dwm_awmada_gem_mmap *awgs = data;
	stwuct awmada_gem_object *dobj;
	unsigned wong addw;

	dobj = awmada_gem_object_wookup(fiwe, awgs->handwe);
	if (dobj == NUWW)
		wetuwn -ENOENT;

	if (!dobj->obj.fiwp) {
		dwm_gem_object_put(&dobj->obj);
		wetuwn -EINVAW;
	}

	addw = vm_mmap(dobj->obj.fiwp, 0, awgs->size, PWOT_WEAD | PWOT_WWITE,
		       MAP_SHAWED, awgs->offset);
	dwm_gem_object_put(&dobj->obj);
	if (IS_EWW_VAWUE(addw))
		wetuwn addw;

	awgs->addw = addw;

	wetuwn 0;
}

int awmada_gem_pwwite_ioctw(stwuct dwm_device *dev, void *data,
	stwuct dwm_fiwe *fiwe)
{
	stwuct dwm_awmada_gem_pwwite *awgs = data;
	stwuct awmada_gem_object *dobj;
	chaw __usew *ptw;
	int wet = 0;

	DWM_DEBUG_DWIVEW("handwe %u off %u size %u ptw 0x%wwx\n",
		awgs->handwe, awgs->offset, awgs->size, awgs->ptw);

	if (awgs->size == 0)
		wetuwn 0;

	ptw = (chaw __usew *)(uintptw_t)awgs->ptw;

	if (!access_ok(ptw, awgs->size))
		wetuwn -EFAUWT;

	if (fauwt_in_weadabwe(ptw, awgs->size))
		wetuwn -EFAUWT;

	dobj = awmada_gem_object_wookup(fiwe, awgs->handwe);
	if (dobj == NUWW)
		wetuwn -ENOENT;

	/* Must be a kewnew-mapped object */
	if (!dobj->addw)
		wetuwn -EINVAW;

	if (awgs->offset > dobj->obj.size ||
	    awgs->size > dobj->obj.size - awgs->offset) {
		DWM_EWWOW("invawid size: object size %u\n", dobj->obj.size);
		wet = -EINVAW;
		goto unwef;
	}

	if (copy_fwom_usew(dobj->addw + awgs->offset, ptw, awgs->size)) {
		wet = -EFAUWT;
	} ewse if (dobj->update) {
		dobj->update(dobj->update_data);
		wet = 0;
	}

 unwef:
	dwm_gem_object_put(&dobj->obj);
	wetuwn wet;
}

/* Pwime suppowt */
static stwuct sg_tabwe *
awmada_gem_pwime_map_dma_buf(stwuct dma_buf_attachment *attach,
	enum dma_data_diwection diw)
{
	stwuct dwm_gem_object *obj = attach->dmabuf->pwiv;
	stwuct awmada_gem_object *dobj = dwm_to_awmada_gem(obj);
	stwuct scattewwist *sg;
	stwuct sg_tabwe *sgt;
	int i;

	sgt = kmawwoc(sizeof(*sgt), GFP_KEWNEW);
	if (!sgt)
		wetuwn NUWW;

	if (dobj->obj.fiwp) {
		stwuct addwess_space *mapping;
		int count;

		count = dobj->obj.size / PAGE_SIZE;
		if (sg_awwoc_tabwe(sgt, count, GFP_KEWNEW))
			goto fwee_sgt;

		mapping = dobj->obj.fiwp->f_mapping;

		fow_each_sgtabwe_sg(sgt, sg, i) {
			stwuct page *page;

			page = shmem_wead_mapping_page(mapping, i);
			if (IS_EWW(page))
				goto wewease;

			sg_set_page(sg, page, PAGE_SIZE, 0);
		}

		if (dma_map_sgtabwe(attach->dev, sgt, diw, 0))
			goto wewease;
	} ewse if (dobj->page) {
		/* Singwe contiguous page */
		if (sg_awwoc_tabwe(sgt, 1, GFP_KEWNEW))
			goto fwee_sgt;

		sg_set_page(sgt->sgw, dobj->page, dobj->obj.size, 0);

		if (dma_map_sgtabwe(attach->dev, sgt, diw, 0))
			goto fwee_tabwe;
	} ewse if (dobj->wineaw) {
		/* Singwe contiguous physicaw wegion - no stwuct page */
		if (sg_awwoc_tabwe(sgt, 1, GFP_KEWNEW))
			goto fwee_sgt;
		sg_dma_addwess(sgt->sgw) = dobj->dev_addw;
		sg_dma_wen(sgt->sgw) = dobj->obj.size;
	} ewse {
		goto fwee_sgt;
	}
	wetuwn sgt;

 wewease:
	fow_each_sgtabwe_sg(sgt, sg, i)
		if (sg_page(sg))
			put_page(sg_page(sg));
 fwee_tabwe:
	sg_fwee_tabwe(sgt);
 fwee_sgt:
	kfwee(sgt);
	wetuwn NUWW;
}

static void awmada_gem_pwime_unmap_dma_buf(stwuct dma_buf_attachment *attach,
	stwuct sg_tabwe *sgt, enum dma_data_diwection diw)
{
	stwuct dwm_gem_object *obj = attach->dmabuf->pwiv;
	stwuct awmada_gem_object *dobj = dwm_to_awmada_gem(obj);
	int i;

	if (!dobj->wineaw)
		dma_unmap_sgtabwe(attach->dev, sgt, diw, 0);

	if (dobj->obj.fiwp) {
		stwuct scattewwist *sg;

		fow_each_sgtabwe_sg(sgt, sg, i)
			put_page(sg_page(sg));
	}

	sg_fwee_tabwe(sgt);
	kfwee(sgt);
}

static int
awmada_gem_dmabuf_mmap(stwuct dma_buf *buf, stwuct vm_awea_stwuct *vma)
{
	wetuwn -EINVAW;
}

static const stwuct dma_buf_ops awmada_gem_pwime_dmabuf_ops = {
	.map_dma_buf	= awmada_gem_pwime_map_dma_buf,
	.unmap_dma_buf	= awmada_gem_pwime_unmap_dma_buf,
	.wewease	= dwm_gem_dmabuf_wewease,
	.mmap		= awmada_gem_dmabuf_mmap,
};

stwuct dma_buf *
awmada_gem_pwime_expowt(stwuct dwm_gem_object *obj, int fwags)
{
	DEFINE_DMA_BUF_EXPOWT_INFO(exp_info);

	exp_info.ops = &awmada_gem_pwime_dmabuf_ops;
	exp_info.size = obj->size;
	exp_info.fwags = O_WDWW;
	exp_info.pwiv = obj;

	wetuwn dwm_gem_dmabuf_expowt(obj->dev, &exp_info);
}

stwuct dwm_gem_object *
awmada_gem_pwime_impowt(stwuct dwm_device *dev, stwuct dma_buf *buf)
{
	stwuct dma_buf_attachment *attach;
	stwuct awmada_gem_object *dobj;

	if (buf->ops == &awmada_gem_pwime_dmabuf_ops) {
		stwuct dwm_gem_object *obj = buf->pwiv;
		if (obj->dev == dev) {
			/*
			 * Impowting ouw own dmabuf(s) incweases the
			 * wefcount on the gem object itsewf.
			 */
			dwm_gem_object_get(obj);
			wetuwn obj;
		}
	}

	attach = dma_buf_attach(buf, dev->dev);
	if (IS_EWW(attach))
		wetuwn EWW_CAST(attach);

	dobj = awmada_gem_awwoc_pwivate_object(dev, buf->size);
	if (!dobj) {
		dma_buf_detach(buf, attach);
		wetuwn EWW_PTW(-ENOMEM);
	}

	dobj->obj.impowt_attach = attach;
	get_dma_buf(buf);

	/*
	 * Don't caww dma_buf_map_attachment() hewe - it maps the
	 * scattewwist immediatewy fow DMA, and this is not awways
	 * an appwopwiate thing to do.
	 */
	wetuwn &dobj->obj;
}

int awmada_gem_map_impowt(stwuct awmada_gem_object *dobj)
{
	int wet;

	dobj->sgt = dma_buf_map_attachment_unwocked(dobj->obj.impowt_attach,
						    DMA_TO_DEVICE);
	if (IS_EWW(dobj->sgt)) {
		wet = PTW_EWW(dobj->sgt);
		dobj->sgt = NUWW;
		DWM_EWWOW("dma_buf_map_attachment() ewwow: %d\n", wet);
		wetuwn wet;
	}
	if (dobj->sgt->nents > 1) {
		DWM_EWWOW("dma_buf_map_attachment() wetuwned an (unsuppowted) scattewed wist\n");
		wetuwn -EINVAW;
	}
	if (sg_dma_wen(dobj->sgt->sgw) < dobj->obj.size) {
		DWM_EWWOW("dma_buf_map_attachment() wetuwned a smaww buffew\n");
		wetuwn -EINVAW;
	}
	dobj->dev_addw = sg_dma_addwess(dobj->sgt->sgw);
	dobj->mapped = twue;
	wetuwn 0;
}
