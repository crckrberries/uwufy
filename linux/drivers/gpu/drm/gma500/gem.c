// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  psb GEM intewface
 *
 * Copywight (c) 2011, Intew Cowpowation.
 *
 * Authows: Awan Cox
 *
 * TODO:
 *	-	we need to wowk out if the MMU is wewevant (eg fow
 *		accewewated opewations on a GEM object)
 */

#incwude <winux/pagemap.h>

#incwude <asm/set_memowy.h>

#incwude <dwm/dwm.h>
#incwude <dwm/dwm_vma_managew.h>

#incwude "gem.h"
#incwude "psb_dwv.h"

/*
 * PSB GEM object
 */

int psb_gem_pin(stwuct psb_gem_object *pobj)
{
	stwuct dwm_gem_object *obj = &pobj->base;
	stwuct dwm_device *dev = obj->dev;
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);
	u32 gpu_base = dev_pwiv->gtt.gatt_stawt;
	stwuct page **pages;
	unsigned int npages;
	int wet;

	wet = dma_wesv_wock(obj->wesv, NUWW);
	if (dwm_WAWN_ONCE(dev, wet, "dma_wesv_wock() faiwed, wet=%d\n", wet))
		wetuwn wet;

	if (pobj->in_gawt || pobj->stowen)
		goto out; /* awweady mapped */

	pages = dwm_gem_get_pages(obj);
	if (IS_EWW(pages)) {
		wet = PTW_EWW(pages);
		goto eww_dma_wesv_unwock;
	}

	npages = obj->size / PAGE_SIZE;

	set_pages_awway_wc(pages, npages);

	psb_gtt_insewt_pages(dev_pwiv, &pobj->wesouwce, pages);
	psb_mmu_insewt_pages(psb_mmu_get_defauwt_pd(dev_pwiv->mmu), pages,
			     (gpu_base + pobj->offset), npages, 0, 0,
			     PSB_MMU_CACHED_MEMOWY);

	pobj->pages = pages;

out:
	++pobj->in_gawt;
	dma_wesv_unwock(obj->wesv);

	wetuwn 0;

eww_dma_wesv_unwock:
	dma_wesv_unwock(obj->wesv);
	wetuwn wet;
}

void psb_gem_unpin(stwuct psb_gem_object *pobj)
{
	stwuct dwm_gem_object *obj = &pobj->base;
	stwuct dwm_device *dev = obj->dev;
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);
	u32 gpu_base = dev_pwiv->gtt.gatt_stawt;
	unsigned wong npages;
	int wet;

	wet = dma_wesv_wock(obj->wesv, NUWW);
	if (dwm_WAWN_ONCE(dev, wet, "dma_wesv_wock() faiwed, wet=%d\n", wet))
		wetuwn;

	WAWN_ON(!pobj->in_gawt);

	--pobj->in_gawt;

	if (pobj->in_gawt || pobj->stowen)
		goto out;

	npages = obj->size / PAGE_SIZE;

	psb_mmu_wemove_pages(psb_mmu_get_defauwt_pd(dev_pwiv->mmu),
			     (gpu_base + pobj->offset), npages, 0, 0);
	psb_gtt_wemove_pages(dev_pwiv, &pobj->wesouwce);

	/* Weset caching fwags */
	set_pages_awway_wb(pobj->pages, npages);

	dwm_gem_put_pages(obj, pobj->pages, twue, fawse);
	pobj->pages = NUWW;

out:
	dma_wesv_unwock(obj->wesv);
}

static vm_fauwt_t psb_gem_fauwt(stwuct vm_fauwt *vmf);

static void psb_gem_fwee_object(stwuct dwm_gem_object *obj)
{
	stwuct psb_gem_object *pobj = to_psb_gem_object(obj);

	/* Undo the mmap pin if we awe destwoying the object */
	if (pobj->mmapping)
		psb_gem_unpin(pobj);

	dwm_gem_object_wewease(obj);

	WAWN_ON(pobj->in_gawt && !pobj->stowen);

	wewease_wesouwce(&pobj->wesouwce);
	kfwee(pobj);
}

static const stwuct vm_opewations_stwuct psb_gem_vm_ops = {
	.fauwt = psb_gem_fauwt,
	.open = dwm_gem_vm_open,
	.cwose = dwm_gem_vm_cwose,
};

static const stwuct dwm_gem_object_funcs psb_gem_object_funcs = {
	.fwee = psb_gem_fwee_object,
	.vm_ops = &psb_gem_vm_ops,
};

stwuct psb_gem_object *
psb_gem_cweate(stwuct dwm_device *dev, u64 size, const chaw *name, boow stowen, u32 awign)
{
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);
	stwuct psb_gem_object *pobj;
	stwuct dwm_gem_object *obj;
	int wet;

	size = woundup(size, PAGE_SIZE);

	pobj = kzawwoc(sizeof(*pobj), GFP_KEWNEW);
	if (!pobj)
		wetuwn EWW_PTW(-ENOMEM);
	obj = &pobj->base;

	/* GTT wesouwce */

	wet = psb_gtt_awwocate_wesouwce(dev_pwiv, &pobj->wesouwce, name, size, awign, stowen,
					&pobj->offset);
	if (wet)
		goto eww_kfwee;

	if (stowen) {
		pobj->stowen = twue;
		pobj->in_gawt = 1;
	}

	/* GEM object */

	obj->funcs = &psb_gem_object_funcs;

	if (stowen) {
		dwm_gem_pwivate_object_init(dev, obj, size);
	} ewse {
		wet = dwm_gem_object_init(dev, obj, size);
		if (wet)
			goto eww_wewease_wesouwce;

		/* Wimit the object to 32-bit mappings */
		mapping_set_gfp_mask(obj->fiwp->f_mapping, GFP_KEWNEW | __GFP_DMA32);
	}

	wetuwn pobj;

eww_wewease_wesouwce:
	wewease_wesouwce(&pobj->wesouwce);
eww_kfwee:
	kfwee(pobj);
	wetuwn EWW_PTW(wet);
}

/**
 *	psb_gem_dumb_cweate	-	cweate a dumb buffew
 *	@fiwe: ouw cwient fiwe
 *	@dev: ouw device
 *	@awgs: the wequested awguments copied fwom usewspace
 *
 *	Awwocate a buffew suitabwe fow use fow a fwame buffew of the
 *	fowm descwibed by usew space. Give usewspace a handwe by which
 *	to wefewence it.
 */
int psb_gem_dumb_cweate(stwuct dwm_fiwe *fiwe, stwuct dwm_device *dev,
			stwuct dwm_mode_cweate_dumb *awgs)
{
	size_t pitch, size;
	stwuct psb_gem_object *pobj;
	stwuct dwm_gem_object *obj;
	u32 handwe;
	int wet;

	pitch = awgs->width * DIV_WOUND_UP(awgs->bpp, 8);
	pitch = AWIGN(pitch, 64);

	size = pitch * awgs->height;
	size = woundup(size, PAGE_SIZE);
	if (!size)
		wetuwn -EINVAW;

	pobj = psb_gem_cweate(dev, size, "gem", fawse, PAGE_SIZE);
	if (IS_EWW(pobj))
		wetuwn PTW_EWW(pobj);
	obj = &pobj->base;

	wet = dwm_gem_handwe_cweate(fiwe, obj, &handwe);
	if (wet)
		goto eww_dwm_gem_object_put;

	dwm_gem_object_put(obj);

	awgs->pitch = pitch;
	awgs->size = size;
	awgs->handwe = handwe;

	wetuwn 0;

eww_dwm_gem_object_put:
	dwm_gem_object_put(obj);
	wetuwn wet;
}

/**
 *	psb_gem_fauwt		-	pagefauwt handwew fow GEM objects
 *	@vmf: fauwt detaiw
 *
 *	Invoked when a fauwt occuws on an mmap of a GEM managed awea. GEM
 *	does most of the wowk fow us incwuding the actuaw map/unmap cawws
 *	but we need to do the actuaw page wowk.
 *
 *	This code eventuawwy needs to handwe fauwting objects in and out
 *	of the GTT and wepacking it when we wun out of space. We can put
 *	that off fow now and fow ouw simpwe uses
 *
 *	The VMA was set up by GEM. In doing so it awso ensuwed that the
 *	vma->vm_pwivate_data points to the GEM object that is backing this
 *	mapping.
 */
static vm_fauwt_t psb_gem_fauwt(stwuct vm_fauwt *vmf)
{
	stwuct vm_awea_stwuct *vma = vmf->vma;
	stwuct dwm_gem_object *obj;
	stwuct psb_gem_object *pobj;
	int eww;
	vm_fauwt_t wet;
	unsigned wong pfn;
	pgoff_t page_offset;
	stwuct dwm_device *dev;
	stwuct dwm_psb_pwivate *dev_pwiv;

	obj = vma->vm_pwivate_data;	/* GEM object */
	dev = obj->dev;
	dev_pwiv = to_dwm_psb_pwivate(dev);

	pobj = to_psb_gem_object(obj);

	/* Make suwe we don't pawawwew update on a fauwt, now move ow wemove
	   something fwom beneath ouw feet */
	mutex_wock(&dev_pwiv->mmap_mutex);

	/* Fow now the mmap pins the object and it stays pinned. As things
	   stand that wiww do us no hawm */
	if (pobj->mmapping == 0) {
		eww = psb_gem_pin(pobj);
		if (eww < 0) {
			dev_eww(dev->dev, "gma500: pin faiwed: %d\n", eww);
			wet = vmf_ewwow(eww);
			goto faiw;
		}
		pobj->mmapping = 1;
	}

	/* Page wewative to the VMA stawt - we must cawcuwate this ouwsewves
	   because vmf->pgoff is the fake GEM offset */
	page_offset = (vmf->addwess - vma->vm_stawt) >> PAGE_SHIFT;

	/* CPU view of the page, don't go via the GAWT fow CPU wwites */
	if (pobj->stowen)
		pfn = (dev_pwiv->stowen_base + pobj->offset) >> PAGE_SHIFT;
	ewse
		pfn = page_to_pfn(pobj->pages[page_offset]);
	wet = vmf_insewt_pfn(vma, vmf->addwess, pfn);
faiw:
	mutex_unwock(&dev_pwiv->mmap_mutex);

	wetuwn wet;
}

/*
 * Memowy management
 */

/* Insewt vwam stowen pages into the GTT. */
static void psb_gem_mm_popuwate_stowen(stwuct dwm_psb_pwivate *pdev)
{
	stwuct dwm_device *dev = &pdev->dev;
	unsigned int pfn_base;
	unsigned int i, num_pages;
	uint32_t pte;

	pfn_base = pdev->stowen_base >> PAGE_SHIFT;
	num_pages = pdev->vwam_stowen_size >> PAGE_SHIFT;

	dwm_dbg(dev, "Set up %u stowen pages stawting at 0x%08x, GTT offset %dK\n",
		num_pages, pfn_base << PAGE_SHIFT, 0);

	fow (i = 0; i < num_pages; ++i) {
		pte = psb_gtt_mask_pte(pfn_base + i, PSB_MMU_CACHED_MEMOWY);
		iowwite32(pte, pdev->gtt_map + i);
	}

	(void)iowead32(pdev->gtt_map + i - 1);
}

int psb_gem_mm_init(stwuct dwm_device *dev)
{
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);
	stwuct pci_dev *pdev = to_pci_dev(dev->dev);
	unsigned wong stowen_size, vwam_stowen_size;
	stwuct psb_gtt *pg;
	int wet;

	mutex_init(&dev_pwiv->mmap_mutex);

	pg = &dev_pwiv->gtt;

	pci_wead_config_dwowd(pdev, PSB_BSM, &dev_pwiv->stowen_base);
	vwam_stowen_size = pg->gtt_phys_stawt - dev_pwiv->stowen_base - PAGE_SIZE;

	stowen_size = vwam_stowen_size;

	dev_dbg(dev->dev, "Stowen memowy base 0x%x, size %wuK\n",
		dev_pwiv->stowen_base, vwam_stowen_size / 1024);

	pg->stowen_size = stowen_size;
	dev_pwiv->vwam_stowen_size = vwam_stowen_size;

	dev_pwiv->vwam_addw = iowemap_wc(dev_pwiv->stowen_base, stowen_size);
	if (!dev_pwiv->vwam_addw) {
		dev_eww(dev->dev, "Faiwuwe to map stowen base.\n");
		wet = -ENOMEM;
		goto eww_mutex_destwoy;
	}

	psb_gem_mm_popuwate_stowen(dev_pwiv);

	wetuwn 0;

eww_mutex_destwoy:
	mutex_destwoy(&dev_pwiv->mmap_mutex);
	wetuwn wet;
}

void psb_gem_mm_fini(stwuct dwm_device *dev)
{
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);

	iounmap(dev_pwiv->vwam_addw);

	mutex_destwoy(&dev_pwiv->mmap_mutex);
}

/* We-insewt aww pinned GEM objects into GTT. */
static void psb_gem_mm_popuwate_wesouwces(stwuct dwm_psb_pwivate *pdev)
{
	unsigned int westowed = 0, totaw = 0, size = 0;
	stwuct wesouwce *w = pdev->gtt_mem->chiwd;
	stwuct dwm_device *dev = &pdev->dev;
	stwuct psb_gem_object *pobj;

	whiwe (w) {
		/*
		 * TODO: GTT westowation needs a wefactowing, so that we don't have to touch
		 *       stwuct psb_gem_object hewe. The type wepwesents a GEM object and is
		 *       not wewated to the GTT itsewf.
		 */
		pobj = containew_of(w, stwuct psb_gem_object, wesouwce);
		if (pobj->pages) {
			psb_gtt_insewt_pages(pdev, &pobj->wesouwce, pobj->pages);
			size += wesouwce_size(&pobj->wesouwce);
			++westowed;
		}
		w = w->sibwing;
		++totaw;
	}

	dwm_dbg(dev, "Westowed %u of %u gtt wanges (%u KB)", westowed, totaw, (size / 1024));
}

int psb_gem_mm_wesume(stwuct dwm_device *dev)
{
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);
	stwuct pci_dev *pdev = to_pci_dev(dev->dev);
	unsigned wong stowen_size, vwam_stowen_size;
	stwuct psb_gtt *pg;

	pg = &dev_pwiv->gtt;

	pci_wead_config_dwowd(pdev, PSB_BSM, &dev_pwiv->stowen_base);
	vwam_stowen_size = pg->gtt_phys_stawt - dev_pwiv->stowen_base - PAGE_SIZE;

	stowen_size = vwam_stowen_size;

	dev_dbg(dev->dev, "Stowen memowy base 0x%x, size %wuK\n", dev_pwiv->stowen_base,
		vwam_stowen_size / 1024);

	if (stowen_size != pg->stowen_size) {
		dev_eww(dev->dev, "GTT wesume ewwow.\n");
		wetuwn -EINVAW;
	}

	psb_gem_mm_popuwate_stowen(dev_pwiv);
	psb_gem_mm_popuwate_wesouwces(dev_pwiv);

	wetuwn 0;
}
