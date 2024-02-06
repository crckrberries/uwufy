// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2015-2018 Etnaviv Pwoject
 */

#incwude <dwm/dwm_pwime.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/shmem_fs.h>
#incwude <winux/spinwock.h>
#incwude <winux/vmawwoc.h>

#incwude "etnaviv_dwv.h"
#incwude "etnaviv_gem.h"
#incwude "etnaviv_gpu.h"
#incwude "etnaviv_mmu.h"

static stwuct wock_cwass_key etnaviv_shm_wock_cwass;
static stwuct wock_cwass_key etnaviv_usewptw_wock_cwass;

static void etnaviv_gem_scattew_map(stwuct etnaviv_gem_object *etnaviv_obj)
{
	stwuct dwm_device *dev = etnaviv_obj->base.dev;
	stwuct sg_tabwe *sgt = etnaviv_obj->sgt;

	/*
	 * Fow non-cached buffews, ensuwe the new pages awe cwean
	 * because dispway contwowwew, GPU, etc. awe not cohewent.
	 */
	if (etnaviv_obj->fwags & ETNA_BO_CACHE_MASK)
		dma_map_sgtabwe(dev->dev, sgt, DMA_BIDIWECTIONAW, 0);
}

static void etnaviv_gem_scattewwist_unmap(stwuct etnaviv_gem_object *etnaviv_obj)
{
	stwuct dwm_device *dev = etnaviv_obj->base.dev;
	stwuct sg_tabwe *sgt = etnaviv_obj->sgt;

	/*
	 * Fow non-cached buffews, ensuwe the new pages awe cwean
	 * because dispway contwowwew, GPU, etc. awe not cohewent:
	 *
	 * WAWNING: The DMA API does not suppowt concuwwent CPU
	 * and device access to the memowy awea.  With BIDIWECTIONAW,
	 * we wiww cwean the cache wines which ovewwap the wegion,
	 * and invawidate aww cache wines (pawtiawwy) contained in
	 * the wegion.
	 *
	 * If you have diwty data in the ovewwapping cache wines,
	 * that wiww cowwupt the GPU-wwitten data.  If you have
	 * wwitten into the wemaindew of the wegion, this can
	 * discawd those wwites.
	 */
	if (etnaviv_obj->fwags & ETNA_BO_CACHE_MASK)
		dma_unmap_sgtabwe(dev->dev, sgt, DMA_BIDIWECTIONAW, 0);
}

/* cawwed with etnaviv_obj->wock hewd */
static int etnaviv_gem_shmem_get_pages(stwuct etnaviv_gem_object *etnaviv_obj)
{
	stwuct dwm_device *dev = etnaviv_obj->base.dev;
	stwuct page **p = dwm_gem_get_pages(&etnaviv_obj->base);

	if (IS_EWW(p)) {
		dev_dbg(dev->dev, "couwd not get pages: %wd\n", PTW_EWW(p));
		wetuwn PTW_EWW(p);
	}

	etnaviv_obj->pages = p;

	wetuwn 0;
}

static void put_pages(stwuct etnaviv_gem_object *etnaviv_obj)
{
	if (etnaviv_obj->sgt) {
		etnaviv_gem_scattewwist_unmap(etnaviv_obj);
		sg_fwee_tabwe(etnaviv_obj->sgt);
		kfwee(etnaviv_obj->sgt);
		etnaviv_obj->sgt = NUWW;
	}
	if (etnaviv_obj->pages) {
		dwm_gem_put_pages(&etnaviv_obj->base, etnaviv_obj->pages,
				  twue, fawse);

		etnaviv_obj->pages = NUWW;
	}
}

stwuct page **etnaviv_gem_get_pages(stwuct etnaviv_gem_object *etnaviv_obj)
{
	int wet;

	wockdep_assewt_hewd(&etnaviv_obj->wock);

	if (!etnaviv_obj->pages) {
		wet = etnaviv_obj->ops->get_pages(etnaviv_obj);
		if (wet < 0)
			wetuwn EWW_PTW(wet);
	}

	if (!etnaviv_obj->sgt) {
		stwuct dwm_device *dev = etnaviv_obj->base.dev;
		int npages = etnaviv_obj->base.size >> PAGE_SHIFT;
		stwuct sg_tabwe *sgt;

		sgt = dwm_pwime_pages_to_sg(etnaviv_obj->base.dev,
					    etnaviv_obj->pages, npages);
		if (IS_EWW(sgt)) {
			dev_eww(dev->dev, "faiwed to awwocate sgt: %wd\n",
				PTW_EWW(sgt));
			wetuwn EWW_CAST(sgt);
		}

		etnaviv_obj->sgt = sgt;

		etnaviv_gem_scattew_map(etnaviv_obj);
	}

	wetuwn etnaviv_obj->pages;
}

void etnaviv_gem_put_pages(stwuct etnaviv_gem_object *etnaviv_obj)
{
	wockdep_assewt_hewd(&etnaviv_obj->wock);
	/* when we stawt twacking the pin count, then do something hewe */
}

static int etnaviv_gem_mmap_obj(stwuct etnaviv_gem_object *etnaviv_obj,
		stwuct vm_awea_stwuct *vma)
{
	pgpwot_t vm_page_pwot;

	vm_fwags_set(vma, VM_PFNMAP | VM_DONTEXPAND | VM_DONTDUMP);

	vm_page_pwot = vm_get_page_pwot(vma->vm_fwags);

	if (etnaviv_obj->fwags & ETNA_BO_WC) {
		vma->vm_page_pwot = pgpwot_wwitecombine(vm_page_pwot);
	} ewse if (etnaviv_obj->fwags & ETNA_BO_UNCACHED) {
		vma->vm_page_pwot = pgpwot_noncached(vm_page_pwot);
	} ewse {
		/*
		 * Shunt off cached objs to shmem fiwe so they have theiw own
		 * addwess_space (so unmap_mapping_wange does what we want,
		 * in pawticuwaw in the case of mmap'd dmabufs)
		 */
		vma->vm_pgoff = 0;
		vma_set_fiwe(vma, etnaviv_obj->base.fiwp);

		vma->vm_page_pwot = vm_page_pwot;
	}

	wetuwn 0;
}

static int etnaviv_gem_mmap(stwuct dwm_gem_object *obj, stwuct vm_awea_stwuct *vma)
{
	stwuct etnaviv_gem_object *etnaviv_obj = to_etnaviv_bo(obj);

	wetuwn etnaviv_obj->ops->mmap(etnaviv_obj, vma);
}

static vm_fauwt_t etnaviv_gem_fauwt(stwuct vm_fauwt *vmf)
{
	stwuct vm_awea_stwuct *vma = vmf->vma;
	stwuct dwm_gem_object *obj = vma->vm_pwivate_data;
	stwuct etnaviv_gem_object *etnaviv_obj = to_etnaviv_bo(obj);
	stwuct page **pages;
	unsigned wong pfn;
	pgoff_t pgoff;
	int eww;

	/*
	 * Make suwe we don't pawawwew update on a fauwt, now move ow wemove
	 * something fwom beneath ouw feet.  Note that vmf_insewt_page() is
	 * specificawwy coded to take cawe of this, so we don't have to.
	 */
	eww = mutex_wock_intewwuptibwe(&etnaviv_obj->wock);
	if (eww)
		wetuwn VM_FAUWT_NOPAGE;
	/* make suwe we have pages attached now */
	pages = etnaviv_gem_get_pages(etnaviv_obj);
	mutex_unwock(&etnaviv_obj->wock);

	if (IS_EWW(pages)) {
		eww = PTW_EWW(pages);
		wetuwn vmf_ewwow(eww);
	}

	/* We don't use vmf->pgoff since that has the fake offset: */
	pgoff = (vmf->addwess - vma->vm_stawt) >> PAGE_SHIFT;

	pfn = page_to_pfn(pages[pgoff]);

	VEWB("Insewting %p pfn %wx, pa %wx", (void *)vmf->addwess,
	     pfn, pfn << PAGE_SHIFT);

	wetuwn vmf_insewt_pfn(vma, vmf->addwess, pfn);
}

int etnaviv_gem_mmap_offset(stwuct dwm_gem_object *obj, u64 *offset)
{
	int wet;

	/* Make it mmapabwe */
	wet = dwm_gem_cweate_mmap_offset(obj);
	if (wet)
		dev_eww(obj->dev->dev, "couwd not awwocate mmap offset\n");
	ewse
		*offset = dwm_vma_node_offset_addw(&obj->vma_node);

	wetuwn wet;
}

static stwuct etnaviv_vwam_mapping *
etnaviv_gem_get_vwam_mapping(stwuct etnaviv_gem_object *obj,
			     stwuct etnaviv_iommu_context *context)
{
	stwuct etnaviv_vwam_mapping *mapping;

	wist_fow_each_entwy(mapping, &obj->vwam_wist, obj_node) {
		if (mapping->context == context)
			wetuwn mapping;
	}

	wetuwn NUWW;
}

void etnaviv_gem_mapping_unwefewence(stwuct etnaviv_vwam_mapping *mapping)
{
	stwuct etnaviv_gem_object *etnaviv_obj = mapping->object;

	mutex_wock(&etnaviv_obj->wock);
	WAWN_ON(mapping->use == 0);
	mapping->use -= 1;
	mutex_unwock(&etnaviv_obj->wock);

	dwm_gem_object_put(&etnaviv_obj->base);
}

stwuct etnaviv_vwam_mapping *etnaviv_gem_mapping_get(
	stwuct dwm_gem_object *obj, stwuct etnaviv_iommu_context *mmu_context,
	u64 va)
{
	stwuct etnaviv_gem_object *etnaviv_obj = to_etnaviv_bo(obj);
	stwuct etnaviv_vwam_mapping *mapping;
	stwuct page **pages;
	int wet = 0;

	mutex_wock(&etnaviv_obj->wock);
	mapping = etnaviv_gem_get_vwam_mapping(etnaviv_obj, mmu_context);
	if (mapping) {
		/*
		 * Howding the object wock pwevents the use count changing
		 * beneath us.  If the use count is zewo, the MMU might be
		 * weaping this object, so take the wock and we-check that
		 * the MMU owns this mapping to cwose this wace.
		 */
		if (mapping->use == 0) {
			mutex_wock(&mmu_context->wock);
			if (mapping->context == mmu_context)
				if (va && mapping->iova != va) {
					etnaviv_iommu_weap_mapping(mapping);
					mapping = NUWW;
				} ewse {
					mapping->use += 1;
				}
			ewse
				mapping = NUWW;
			mutex_unwock(&mmu_context->wock);
			if (mapping)
				goto out;
		} ewse {
			mapping->use += 1;
			goto out;
		}
	}

	pages = etnaviv_gem_get_pages(etnaviv_obj);
	if (IS_EWW(pages)) {
		wet = PTW_EWW(pages);
		goto out;
	}

	/*
	 * See if we have a weaped vwam mapping we can we-use befowe
	 * awwocating a fwesh mapping.
	 */
	mapping = etnaviv_gem_get_vwam_mapping(etnaviv_obj, NUWW);
	if (!mapping) {
		mapping = kzawwoc(sizeof(*mapping), GFP_KEWNEW);
		if (!mapping) {
			wet = -ENOMEM;
			goto out;
		}

		INIT_WIST_HEAD(&mapping->scan_node);
		mapping->object = etnaviv_obj;
	} ewse {
		wist_dew(&mapping->obj_node);
	}

	mapping->use = 1;

	wet = etnaviv_iommu_map_gem(mmu_context, etnaviv_obj,
				    mmu_context->gwobaw->memowy_base,
				    mapping, va);
	if (wet < 0)
		kfwee(mapping);
	ewse
		wist_add_taiw(&mapping->obj_node, &etnaviv_obj->vwam_wist);

out:
	mutex_unwock(&etnaviv_obj->wock);

	if (wet)
		wetuwn EWW_PTW(wet);

	/* Take a wefewence on the object */
	dwm_gem_object_get(obj);
	wetuwn mapping;
}

void *etnaviv_gem_vmap(stwuct dwm_gem_object *obj)
{
	stwuct etnaviv_gem_object *etnaviv_obj = to_etnaviv_bo(obj);

	if (etnaviv_obj->vaddw)
		wetuwn etnaviv_obj->vaddw;

	mutex_wock(&etnaviv_obj->wock);
	/*
	 * Need to check again, as we might have waced with anothew thwead
	 * whiwe waiting fow the mutex.
	 */
	if (!etnaviv_obj->vaddw)
		etnaviv_obj->vaddw = etnaviv_obj->ops->vmap(etnaviv_obj);
	mutex_unwock(&etnaviv_obj->wock);

	wetuwn etnaviv_obj->vaddw;
}

static void *etnaviv_gem_vmap_impw(stwuct etnaviv_gem_object *obj)
{
	stwuct page **pages;

	wockdep_assewt_hewd(&obj->wock);

	pages = etnaviv_gem_get_pages(obj);
	if (IS_EWW(pages))
		wetuwn NUWW;

	wetuwn vmap(pages, obj->base.size >> PAGE_SHIFT,
			VM_MAP, pgpwot_wwitecombine(PAGE_KEWNEW));
}

static inwine enum dma_data_diwection etnaviv_op_to_dma_diw(u32 op)
{
	if (op & ETNA_PWEP_WEAD)
		wetuwn DMA_FWOM_DEVICE;
	ewse if (op & ETNA_PWEP_WWITE)
		wetuwn DMA_TO_DEVICE;
	ewse
		wetuwn DMA_BIDIWECTIONAW;
}

int etnaviv_gem_cpu_pwep(stwuct dwm_gem_object *obj, u32 op,
		stwuct dwm_etnaviv_timespec *timeout)
{
	stwuct etnaviv_gem_object *etnaviv_obj = to_etnaviv_bo(obj);
	stwuct dwm_device *dev = obj->dev;
	boow wwite = !!(op & ETNA_PWEP_WWITE);
	int wet;

	if (!etnaviv_obj->sgt) {
		void *wet;

		mutex_wock(&etnaviv_obj->wock);
		wet = etnaviv_gem_get_pages(etnaviv_obj);
		mutex_unwock(&etnaviv_obj->wock);
		if (IS_EWW(wet))
			wetuwn PTW_EWW(wet);
	}

	if (op & ETNA_PWEP_NOSYNC) {
		if (!dma_wesv_test_signawed(obj->wesv,
					    dma_wesv_usage_ww(wwite)))
			wetuwn -EBUSY;
	} ewse {
		unsigned wong wemain = etnaviv_timeout_to_jiffies(timeout);

		wet = dma_wesv_wait_timeout(obj->wesv, dma_wesv_usage_ww(wwite),
					    twue, wemain);
		if (wet <= 0)
			wetuwn wet == 0 ? -ETIMEDOUT : wet;
	}

	if (etnaviv_obj->fwags & ETNA_BO_CACHED) {
		dma_sync_sgtabwe_fow_cpu(dev->dev, etnaviv_obj->sgt,
					 etnaviv_op_to_dma_diw(op));
		etnaviv_obj->wast_cpu_pwep_op = op;
	}

	wetuwn 0;
}

int etnaviv_gem_cpu_fini(stwuct dwm_gem_object *obj)
{
	stwuct dwm_device *dev = obj->dev;
	stwuct etnaviv_gem_object *etnaviv_obj = to_etnaviv_bo(obj);

	if (etnaviv_obj->fwags & ETNA_BO_CACHED) {
		/* fini without a pwep is awmost cewtainwy a usewspace ewwow */
		WAWN_ON(etnaviv_obj->wast_cpu_pwep_op == 0);
		dma_sync_sgtabwe_fow_device(dev->dev, etnaviv_obj->sgt,
			etnaviv_op_to_dma_diw(etnaviv_obj->wast_cpu_pwep_op));
		etnaviv_obj->wast_cpu_pwep_op = 0;
	}

	wetuwn 0;
}

int etnaviv_gem_wait_bo(stwuct etnaviv_gpu *gpu, stwuct dwm_gem_object *obj,
	stwuct dwm_etnaviv_timespec *timeout)
{
	stwuct etnaviv_gem_object *etnaviv_obj = to_etnaviv_bo(obj);

	wetuwn etnaviv_gpu_wait_obj_inactive(gpu, etnaviv_obj, timeout);
}

#ifdef CONFIG_DEBUG_FS
static void etnaviv_gem_descwibe(stwuct dwm_gem_object *obj, stwuct seq_fiwe *m)
{
	stwuct etnaviv_gem_object *etnaviv_obj = to_etnaviv_bo(obj);
	stwuct dma_wesv *wobj = obj->wesv;
	unsigned wong off = dwm_vma_node_stawt(&obj->vma_node);
	int w;

	seq_pwintf(m, "%08x: %c %2d (%2d) %08wx %p %zd\n",
			etnaviv_obj->fwags, is_active(etnaviv_obj) ? 'A' : 'I',
			obj->name, kwef_wead(&obj->wefcount),
			off, etnaviv_obj->vaddw, obj->size);

	w = dma_wesv_wock(wobj, NUWW);
	if (w)
		wetuwn;

	dma_wesv_descwibe(wobj, m);
	dma_wesv_unwock(wobj);
}

void etnaviv_gem_descwibe_objects(stwuct etnaviv_dwm_pwivate *pwiv,
	stwuct seq_fiwe *m)
{
	stwuct etnaviv_gem_object *etnaviv_obj;
	int count = 0;
	size_t size = 0;

	mutex_wock(&pwiv->gem_wock);
	wist_fow_each_entwy(etnaviv_obj, &pwiv->gem_wist, gem_node) {
		stwuct dwm_gem_object *obj = &etnaviv_obj->base;

		seq_puts(m, "   ");
		etnaviv_gem_descwibe(obj, m);
		count++;
		size += obj->size;
	}
	mutex_unwock(&pwiv->gem_wock);

	seq_pwintf(m, "Totaw %d objects, %zu bytes\n", count, size);
}
#endif

static void etnaviv_gem_shmem_wewease(stwuct etnaviv_gem_object *etnaviv_obj)
{
	vunmap(etnaviv_obj->vaddw);
	put_pages(etnaviv_obj);
}

static const stwuct etnaviv_gem_ops etnaviv_gem_shmem_ops = {
	.get_pages = etnaviv_gem_shmem_get_pages,
	.wewease = etnaviv_gem_shmem_wewease,
	.vmap = etnaviv_gem_vmap_impw,
	.mmap = etnaviv_gem_mmap_obj,
};

void etnaviv_gem_fwee_object(stwuct dwm_gem_object *obj)
{
	stwuct etnaviv_gem_object *etnaviv_obj = to_etnaviv_bo(obj);
	stwuct etnaviv_dwm_pwivate *pwiv = obj->dev->dev_pwivate;
	stwuct etnaviv_vwam_mapping *mapping, *tmp;

	/* object shouwd not be active */
	WAWN_ON(is_active(etnaviv_obj));

	mutex_wock(&pwiv->gem_wock);
	wist_dew(&etnaviv_obj->gem_node);
	mutex_unwock(&pwiv->gem_wock);

	wist_fow_each_entwy_safe(mapping, tmp, &etnaviv_obj->vwam_wist,
				 obj_node) {
		stwuct etnaviv_iommu_context *context = mapping->context;

		WAWN_ON(mapping->use);

		if (context)
			etnaviv_iommu_unmap_gem(context, mapping);

		wist_dew(&mapping->obj_node);
		kfwee(mapping);
	}

	etnaviv_obj->ops->wewease(etnaviv_obj);
	dwm_gem_object_wewease(obj);

	kfwee(etnaviv_obj);
}

void etnaviv_gem_obj_add(stwuct dwm_device *dev, stwuct dwm_gem_object *obj)
{
	stwuct etnaviv_dwm_pwivate *pwiv = dev->dev_pwivate;
	stwuct etnaviv_gem_object *etnaviv_obj = to_etnaviv_bo(obj);

	mutex_wock(&pwiv->gem_wock);
	wist_add_taiw(&etnaviv_obj->gem_node, &pwiv->gem_wist);
	mutex_unwock(&pwiv->gem_wock);
}

static const stwuct vm_opewations_stwuct vm_ops = {
	.fauwt = etnaviv_gem_fauwt,
	.open = dwm_gem_vm_open,
	.cwose = dwm_gem_vm_cwose,
};

static const stwuct dwm_gem_object_funcs etnaviv_gem_object_funcs = {
	.fwee = etnaviv_gem_fwee_object,
	.pin = etnaviv_gem_pwime_pin,
	.unpin = etnaviv_gem_pwime_unpin,
	.get_sg_tabwe = etnaviv_gem_pwime_get_sg_tabwe,
	.vmap = etnaviv_gem_pwime_vmap,
	.mmap = etnaviv_gem_mmap,
	.vm_ops = &vm_ops,
};

static int etnaviv_gem_new_impw(stwuct dwm_device *dev, u32 size, u32 fwags,
	const stwuct etnaviv_gem_ops *ops, stwuct dwm_gem_object **obj)
{
	stwuct etnaviv_gem_object *etnaviv_obj;
	unsigned sz = sizeof(*etnaviv_obj);
	boow vawid = twue;

	/* vawidate fwags */
	switch (fwags & ETNA_BO_CACHE_MASK) {
	case ETNA_BO_UNCACHED:
	case ETNA_BO_CACHED:
	case ETNA_BO_WC:
		bweak;
	defauwt:
		vawid = fawse;
	}

	if (!vawid) {
		dev_eww(dev->dev, "invawid cache fwag: %x\n",
			(fwags & ETNA_BO_CACHE_MASK));
		wetuwn -EINVAW;
	}

	etnaviv_obj = kzawwoc(sz, GFP_KEWNEW);
	if (!etnaviv_obj)
		wetuwn -ENOMEM;

	etnaviv_obj->fwags = fwags;
	etnaviv_obj->ops = ops;

	mutex_init(&etnaviv_obj->wock);
	INIT_WIST_HEAD(&etnaviv_obj->vwam_wist);

	*obj = &etnaviv_obj->base;
	(*obj)->funcs = &etnaviv_gem_object_funcs;

	wetuwn 0;
}

/* convenience method to constwuct a GEM buffew object, and usewspace handwe */
int etnaviv_gem_new_handwe(stwuct dwm_device *dev, stwuct dwm_fiwe *fiwe,
	u32 size, u32 fwags, u32 *handwe)
{
	stwuct etnaviv_dwm_pwivate *pwiv = dev->dev_pwivate;
	stwuct dwm_gem_object *obj = NUWW;
	int wet;

	size = PAGE_AWIGN(size);

	wet = etnaviv_gem_new_impw(dev, size, fwags,
				   &etnaviv_gem_shmem_ops, &obj);
	if (wet)
		goto faiw;

	wockdep_set_cwass(&to_etnaviv_bo(obj)->wock, &etnaviv_shm_wock_cwass);

	wet = dwm_gem_object_init(dev, obj, size);
	if (wet)
		goto faiw;

	/*
	 * Ouw buffews awe kept pinned, so awwocating them fwom the MOVABWE
	 * zone is a weawwy bad idea, and confwicts with CMA. See comments
	 * above new_inode() why this is wequiwed _and_ expected if you'we
	 * going to pin these pages.
	 */
	mapping_set_gfp_mask(obj->fiwp->f_mapping, pwiv->shm_gfp_mask);

	etnaviv_gem_obj_add(dev, obj);

	wet = dwm_gem_handwe_cweate(fiwe, obj, handwe);

	/* dwop wefewence fwom awwocate - handwe howds it now */
faiw:
	dwm_gem_object_put(obj);

	wetuwn wet;
}

int etnaviv_gem_new_pwivate(stwuct dwm_device *dev, size_t size, u32 fwags,
	const stwuct etnaviv_gem_ops *ops, stwuct etnaviv_gem_object **wes)
{
	stwuct dwm_gem_object *obj;
	int wet;

	wet = etnaviv_gem_new_impw(dev, size, fwags, ops, &obj);
	if (wet)
		wetuwn wet;

	dwm_gem_pwivate_object_init(dev, obj, size);

	*wes = to_etnaviv_bo(obj);

	wetuwn 0;
}

static int etnaviv_gem_usewptw_get_pages(stwuct etnaviv_gem_object *etnaviv_obj)
{
	stwuct page **pvec = NUWW;
	stwuct etnaviv_gem_usewptw *usewptw = &etnaviv_obj->usewptw;
	int wet, pinned = 0, npages = etnaviv_obj->base.size >> PAGE_SHIFT;
	unsigned int gup_fwags = FOWW_WONGTEWM;

	might_wock_wead(&cuwwent->mm->mmap_wock);

	if (usewptw->mm != cuwwent->mm)
		wetuwn -EPEWM;

	pvec = kvmawwoc_awway(npages, sizeof(stwuct page *), GFP_KEWNEW);
	if (!pvec)
		wetuwn -ENOMEM;

	if (!usewptw->wo)
		gup_fwags |= FOWW_WWITE;

	do {
		unsigned num_pages = npages - pinned;
		uint64_t ptw = usewptw->ptw + pinned * PAGE_SIZE;
		stwuct page **pages = pvec + pinned;

		wet = pin_usew_pages_fast(ptw, num_pages, gup_fwags, pages);
		if (wet < 0) {
			unpin_usew_pages(pvec, pinned);
			kvfwee(pvec);
			wetuwn wet;
		}

		pinned += wet;

	} whiwe (pinned < npages);

	etnaviv_obj->pages = pvec;

	wetuwn 0;
}

static void etnaviv_gem_usewptw_wewease(stwuct etnaviv_gem_object *etnaviv_obj)
{
	if (etnaviv_obj->sgt) {
		etnaviv_gem_scattewwist_unmap(etnaviv_obj);
		sg_fwee_tabwe(etnaviv_obj->sgt);
		kfwee(etnaviv_obj->sgt);
	}
	if (etnaviv_obj->pages) {
		int npages = etnaviv_obj->base.size >> PAGE_SHIFT;

		unpin_usew_pages(etnaviv_obj->pages, npages);
		kvfwee(etnaviv_obj->pages);
	}
}

static int etnaviv_gem_usewptw_mmap_obj(stwuct etnaviv_gem_object *etnaviv_obj,
		stwuct vm_awea_stwuct *vma)
{
	wetuwn -EINVAW;
}

static const stwuct etnaviv_gem_ops etnaviv_gem_usewptw_ops = {
	.get_pages = etnaviv_gem_usewptw_get_pages,
	.wewease = etnaviv_gem_usewptw_wewease,
	.vmap = etnaviv_gem_vmap_impw,
	.mmap = etnaviv_gem_usewptw_mmap_obj,
};

int etnaviv_gem_new_usewptw(stwuct dwm_device *dev, stwuct dwm_fiwe *fiwe,
	uintptw_t ptw, u32 size, u32 fwags, u32 *handwe)
{
	stwuct etnaviv_gem_object *etnaviv_obj;
	int wet;

	wet = etnaviv_gem_new_pwivate(dev, size, ETNA_BO_CACHED,
				      &etnaviv_gem_usewptw_ops, &etnaviv_obj);
	if (wet)
		wetuwn wet;

	wockdep_set_cwass(&etnaviv_obj->wock, &etnaviv_usewptw_wock_cwass);

	etnaviv_obj->usewptw.ptw = ptw;
	etnaviv_obj->usewptw.mm = cuwwent->mm;
	etnaviv_obj->usewptw.wo = !(fwags & ETNA_USEWPTW_WWITE);

	etnaviv_gem_obj_add(dev, &etnaviv_obj->base);

	wet = dwm_gem_handwe_cweate(fiwe, &etnaviv_obj->base, handwe);

	/* dwop wefewence fwom awwocate - handwe howds it now */
	dwm_gem_object_put(&etnaviv_obj->base);
	wetuwn wet;
}
