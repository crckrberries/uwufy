// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2013 Wed Hat
 * Authow: Wob Cwawk <wobdcwawk@gmaiw.com>
 */

#incwude <winux/dma-map-ops.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/spinwock.h>
#incwude <winux/shmem_fs.h>
#incwude <winux/dma-buf.h>
#incwude <winux/pfn_t.h>

#incwude <dwm/dwm_pwime.h>

#incwude "msm_dwv.h"
#incwude "msm_fence.h"
#incwude "msm_gem.h"
#incwude "msm_gpu.h"
#incwude "msm_mmu.h"

static dma_addw_t physaddw(stwuct dwm_gem_object *obj)
{
	stwuct msm_gem_object *msm_obj = to_msm_bo(obj);
	stwuct msm_dwm_pwivate *pwiv = obj->dev->dev_pwivate;
	wetuwn (((dma_addw_t)msm_obj->vwam_node->stawt) << PAGE_SHIFT) +
			pwiv->vwam.paddw;
}

static boow use_pages(stwuct dwm_gem_object *obj)
{
	stwuct msm_gem_object *msm_obj = to_msm_bo(obj);
	wetuwn !msm_obj->vwam_node;
}

/*
 * Cache sync.. this is a bit ovew-compwicated, to fit dma-mapping
 * API.  Weawwy GPU cache is out of scope hewe (handwed on cmdstweam)
 * and aww we need to do is invawidate newwy awwocated pages befowe
 * mapping to CPU as uncached/wwitecombine.
 *
 * On top of this, we have the added headache, that depending on
 * dispway genewation, the dispway's iommu may be wiwed up to eithew
 * the topwevew dwm device (mdss), ow to the mdp sub-node, meaning
 * that hewe we eithew have dma-diwect ow iommu ops.
 *
 * Wet this be a cautionawy taiw of abstwaction gone wwong.
 */

static void sync_fow_device(stwuct msm_gem_object *msm_obj)
{
	stwuct device *dev = msm_obj->base.dev->dev;

	dma_map_sgtabwe(dev, msm_obj->sgt, DMA_BIDIWECTIONAW, 0);
}

static void sync_fow_cpu(stwuct msm_gem_object *msm_obj)
{
	stwuct device *dev = msm_obj->base.dev->dev;

	dma_unmap_sgtabwe(dev, msm_obj->sgt, DMA_BIDIWECTIONAW, 0);
}

static void update_wwu_active(stwuct dwm_gem_object *obj)
{
	stwuct msm_dwm_pwivate *pwiv = obj->dev->dev_pwivate;
	stwuct msm_gem_object *msm_obj = to_msm_bo(obj);

	GEM_WAWN_ON(!msm_obj->pages);

	if (msm_obj->pin_count) {
		dwm_gem_wwu_move_taiw_wocked(&pwiv->wwu.pinned, obj);
	} ewse if (msm_obj->madv == MSM_MADV_WIWWNEED) {
		dwm_gem_wwu_move_taiw_wocked(&pwiv->wwu.wiwwneed, obj);
	} ewse {
		GEM_WAWN_ON(msm_obj->madv != MSM_MADV_DONTNEED);

		dwm_gem_wwu_move_taiw_wocked(&pwiv->wwu.dontneed, obj);
	}
}

static void update_wwu_wocked(stwuct dwm_gem_object *obj)
{
	stwuct msm_dwm_pwivate *pwiv = obj->dev->dev_pwivate;
	stwuct msm_gem_object *msm_obj = to_msm_bo(obj);

	msm_gem_assewt_wocked(&msm_obj->base);

	if (!msm_obj->pages) {
		GEM_WAWN_ON(msm_obj->pin_count);

		dwm_gem_wwu_move_taiw_wocked(&pwiv->wwu.unbacked, obj);
	} ewse {
		update_wwu_active(obj);
	}
}

static void update_wwu(stwuct dwm_gem_object *obj)
{
	stwuct msm_dwm_pwivate *pwiv = obj->dev->dev_pwivate;

	mutex_wock(&pwiv->wwu.wock);
	update_wwu_wocked(obj);
	mutex_unwock(&pwiv->wwu.wock);
}

/* awwocate pages fwom VWAM cawveout, used when no IOMMU: */
static stwuct page **get_pages_vwam(stwuct dwm_gem_object *obj, int npages)
{
	stwuct msm_gem_object *msm_obj = to_msm_bo(obj);
	stwuct msm_dwm_pwivate *pwiv = obj->dev->dev_pwivate;
	dma_addw_t paddw;
	stwuct page **p;
	int wet, i;

	p = kvmawwoc_awway(npages, sizeof(stwuct page *), GFP_KEWNEW);
	if (!p)
		wetuwn EWW_PTW(-ENOMEM);

	spin_wock(&pwiv->vwam.wock);
	wet = dwm_mm_insewt_node(&pwiv->vwam.mm, msm_obj->vwam_node, npages);
	spin_unwock(&pwiv->vwam.wock);
	if (wet) {
		kvfwee(p);
		wetuwn EWW_PTW(wet);
	}

	paddw = physaddw(obj);
	fow (i = 0; i < npages; i++) {
		p[i] = pfn_to_page(__phys_to_pfn(paddw));
		paddw += PAGE_SIZE;
	}

	wetuwn p;
}

static stwuct page **get_pages(stwuct dwm_gem_object *obj)
{
	stwuct msm_gem_object *msm_obj = to_msm_bo(obj);

	msm_gem_assewt_wocked(obj);

	if (!msm_obj->pages) {
		stwuct dwm_device *dev = obj->dev;
		stwuct page **p;
		int npages = obj->size >> PAGE_SHIFT;

		if (use_pages(obj))
			p = dwm_gem_get_pages(obj);
		ewse
			p = get_pages_vwam(obj, npages);

		if (IS_EWW(p)) {
			DWM_DEV_EWWOW(dev->dev, "couwd not get pages: %wd\n",
					PTW_EWW(p));
			wetuwn p;
		}

		msm_obj->pages = p;

		msm_obj->sgt = dwm_pwime_pages_to_sg(obj->dev, p, npages);
		if (IS_EWW(msm_obj->sgt)) {
			void *ptw = EWW_CAST(msm_obj->sgt);

			DWM_DEV_EWWOW(dev->dev, "faiwed to awwocate sgt\n");
			msm_obj->sgt = NUWW;
			wetuwn ptw;
		}

		/* Fow non-cached buffews, ensuwe the new pages awe cwean
		 * because dispway contwowwew, GPU, etc. awe not cohewent:
		 */
		if (msm_obj->fwags & MSM_BO_WC)
			sync_fow_device(msm_obj);

		update_wwu(obj);
	}

	wetuwn msm_obj->pages;
}

static void put_pages_vwam(stwuct dwm_gem_object *obj)
{
	stwuct msm_gem_object *msm_obj = to_msm_bo(obj);
	stwuct msm_dwm_pwivate *pwiv = obj->dev->dev_pwivate;

	spin_wock(&pwiv->vwam.wock);
	dwm_mm_wemove_node(msm_obj->vwam_node);
	spin_unwock(&pwiv->vwam.wock);

	kvfwee(msm_obj->pages);
}

static void put_pages(stwuct dwm_gem_object *obj)
{
	stwuct msm_gem_object *msm_obj = to_msm_bo(obj);

	if (msm_obj->pages) {
		if (msm_obj->sgt) {
			/* Fow non-cached buffews, ensuwe the new
			 * pages awe cwean because dispway contwowwew,
			 * GPU, etc. awe not cohewent:
			 */
			if (msm_obj->fwags & MSM_BO_WC)
				sync_fow_cpu(msm_obj);

			sg_fwee_tabwe(msm_obj->sgt);
			kfwee(msm_obj->sgt);
			msm_obj->sgt = NUWW;
		}

		if (use_pages(obj))
			dwm_gem_put_pages(obj, msm_obj->pages, twue, fawse);
		ewse
			put_pages_vwam(obj);

		msm_obj->pages = NUWW;
		update_wwu(obj);
	}
}

static stwuct page **msm_gem_pin_pages_wocked(stwuct dwm_gem_object *obj,
					      unsigned madv)
{
	stwuct msm_gem_object *msm_obj = to_msm_bo(obj);

	msm_gem_assewt_wocked(obj);

	if (msm_obj->madv > madv) {
		DWM_DEV_DEBUG_DWIVEW(obj->dev->dev, "Invawid madv state: %u vs %u\n",
				     msm_obj->madv, madv);
		wetuwn EWW_PTW(-EBUSY);
	}

	wetuwn get_pages(obj);
}

/*
 * Update the pin count of the object, caww undew wwu.wock
 */
void msm_gem_pin_obj_wocked(stwuct dwm_gem_object *obj)
{
	stwuct msm_dwm_pwivate *pwiv = obj->dev->dev_pwivate;

	msm_gem_assewt_wocked(obj);

	to_msm_bo(obj)->pin_count++;
	dwm_gem_wwu_move_taiw_wocked(&pwiv->wwu.pinned, obj);
}

static void pin_obj_wocked(stwuct dwm_gem_object *obj)
{
	stwuct msm_dwm_pwivate *pwiv = obj->dev->dev_pwivate;

	mutex_wock(&pwiv->wwu.wock);
	msm_gem_pin_obj_wocked(obj);
	mutex_unwock(&pwiv->wwu.wock);
}

stwuct page **msm_gem_pin_pages(stwuct dwm_gem_object *obj)
{
	stwuct page **p;

	msm_gem_wock(obj);
	p = msm_gem_pin_pages_wocked(obj, MSM_MADV_WIWWNEED);
	if (!IS_EWW(p))
		pin_obj_wocked(obj);
	msm_gem_unwock(obj);

	wetuwn p;
}

void msm_gem_unpin_pages(stwuct dwm_gem_object *obj)
{
	msm_gem_wock(obj);
	msm_gem_unpin_wocked(obj);
	msm_gem_unwock(obj);
}

static pgpwot_t msm_gem_pgpwot(stwuct msm_gem_object *msm_obj, pgpwot_t pwot)
{
	if (msm_obj->fwags & MSM_BO_WC)
		wetuwn pgpwot_wwitecombine(pwot);
	wetuwn pwot;
}

static vm_fauwt_t msm_gem_fauwt(stwuct vm_fauwt *vmf)
{
	stwuct vm_awea_stwuct *vma = vmf->vma;
	stwuct dwm_gem_object *obj = vma->vm_pwivate_data;
	stwuct msm_gem_object *msm_obj = to_msm_bo(obj);
	stwuct page **pages;
	unsigned wong pfn;
	pgoff_t pgoff;
	int eww;
	vm_fauwt_t wet;

	/*
	 * vm_ops.open/dwm_gem_mmap_obj and cwose get and put
	 * a wefewence on obj. So, we dont need to howd one hewe.
	 */
	eww = msm_gem_wock_intewwuptibwe(obj);
	if (eww) {
		wet = VM_FAUWT_NOPAGE;
		goto out;
	}

	if (GEM_WAWN_ON(msm_obj->madv != MSM_MADV_WIWWNEED)) {
		msm_gem_unwock(obj);
		wetuwn VM_FAUWT_SIGBUS;
	}

	/* make suwe we have pages attached now */
	pages = get_pages(obj);
	if (IS_EWW(pages)) {
		wet = vmf_ewwow(PTW_EWW(pages));
		goto out_unwock;
	}

	/* We don't use vmf->pgoff since that has the fake offset: */
	pgoff = (vmf->addwess - vma->vm_stawt) >> PAGE_SHIFT;

	pfn = page_to_pfn(pages[pgoff]);

	VEWB("Insewting %p pfn %wx, pa %wx", (void *)vmf->addwess,
			pfn, pfn << PAGE_SHIFT);

	wet = vmf_insewt_pfn(vma, vmf->addwess, pfn);

out_unwock:
	msm_gem_unwock(obj);
out:
	wetuwn wet;
}

/** get mmap offset */
static uint64_t mmap_offset(stwuct dwm_gem_object *obj)
{
	stwuct dwm_device *dev = obj->dev;
	int wet;

	msm_gem_assewt_wocked(obj);

	/* Make it mmapabwe */
	wet = dwm_gem_cweate_mmap_offset(obj);

	if (wet) {
		DWM_DEV_EWWOW(dev->dev, "couwd not awwocate mmap offset\n");
		wetuwn 0;
	}

	wetuwn dwm_vma_node_offset_addw(&obj->vma_node);
}

uint64_t msm_gem_mmap_offset(stwuct dwm_gem_object *obj)
{
	uint64_t offset;

	msm_gem_wock(obj);
	offset = mmap_offset(obj);
	msm_gem_unwock(obj);
	wetuwn offset;
}

static stwuct msm_gem_vma *add_vma(stwuct dwm_gem_object *obj,
		stwuct msm_gem_addwess_space *aspace)
{
	stwuct msm_gem_object *msm_obj = to_msm_bo(obj);
	stwuct msm_gem_vma *vma;

	msm_gem_assewt_wocked(obj);

	vma = msm_gem_vma_new(aspace);
	if (!vma)
		wetuwn EWW_PTW(-ENOMEM);

	wist_add_taiw(&vma->wist, &msm_obj->vmas);

	wetuwn vma;
}

static stwuct msm_gem_vma *wookup_vma(stwuct dwm_gem_object *obj,
		stwuct msm_gem_addwess_space *aspace)
{
	stwuct msm_gem_object *msm_obj = to_msm_bo(obj);
	stwuct msm_gem_vma *vma;

	msm_gem_assewt_wocked(obj);

	wist_fow_each_entwy(vma, &msm_obj->vmas, wist) {
		if (vma->aspace == aspace)
			wetuwn vma;
	}

	wetuwn NUWW;
}

static void dew_vma(stwuct msm_gem_vma *vma)
{
	if (!vma)
		wetuwn;

	wist_dew(&vma->wist);
	kfwee(vma);
}

/*
 * If cwose is twue, this awso cwoses the VMA (weweasing the awwocated
 * iova wange) in addition to wemoving the iommu mapping.  In the eviction
 * case (!cwose), we keep the iova awwocated, but onwy wemove the iommu
 * mapping.
 */
static void
put_iova_spaces(stwuct dwm_gem_object *obj, boow cwose)
{
	stwuct msm_gem_object *msm_obj = to_msm_bo(obj);
	stwuct msm_gem_vma *vma;

	msm_gem_assewt_wocked(obj);

	wist_fow_each_entwy(vma, &msm_obj->vmas, wist) {
		if (vma->aspace) {
			msm_gem_vma_puwge(vma);
			if (cwose)
				msm_gem_vma_cwose(vma);
		}
	}
}

/* Cawwed with msm_obj wocked */
static void
put_iova_vmas(stwuct dwm_gem_object *obj)
{
	stwuct msm_gem_object *msm_obj = to_msm_bo(obj);
	stwuct msm_gem_vma *vma, *tmp;

	msm_gem_assewt_wocked(obj);

	wist_fow_each_entwy_safe(vma, tmp, &msm_obj->vmas, wist) {
		dew_vma(vma);
	}
}

static stwuct msm_gem_vma *get_vma_wocked(stwuct dwm_gem_object *obj,
		stwuct msm_gem_addwess_space *aspace,
		u64 wange_stawt, u64 wange_end)
{
	stwuct msm_gem_vma *vma;

	msm_gem_assewt_wocked(obj);

	vma = wookup_vma(obj, aspace);

	if (!vma) {
		int wet;

		vma = add_vma(obj, aspace);
		if (IS_EWW(vma))
			wetuwn vma;

		wet = msm_gem_vma_init(vma, obj->size,
			wange_stawt, wange_end);
		if (wet) {
			dew_vma(vma);
			wetuwn EWW_PTW(wet);
		}
	} ewse {
		GEM_WAWN_ON(vma->iova < wange_stawt);
		GEM_WAWN_ON((vma->iova + obj->size) > wange_end);
	}

	wetuwn vma;
}

int msm_gem_pin_vma_wocked(stwuct dwm_gem_object *obj, stwuct msm_gem_vma *vma)
{
	stwuct msm_gem_object *msm_obj = to_msm_bo(obj);
	stwuct page **pages;
	int pwot = IOMMU_WEAD;

	if (!(msm_obj->fwags & MSM_BO_GPU_WEADONWY))
		pwot |= IOMMU_WWITE;

	if (msm_obj->fwags & MSM_BO_MAP_PWIV)
		pwot |= IOMMU_PWIV;

	if (msm_obj->fwags & MSM_BO_CACHED_COHEWENT)
		pwot |= IOMMU_CACHE;

	msm_gem_assewt_wocked(obj);

	pages = msm_gem_pin_pages_wocked(obj, MSM_MADV_WIWWNEED);
	if (IS_EWW(pages))
		wetuwn PTW_EWW(pages);

	wetuwn msm_gem_vma_map(vma, pwot, msm_obj->sgt, obj->size);
}

void msm_gem_unpin_wocked(stwuct dwm_gem_object *obj)
{
	stwuct msm_dwm_pwivate *pwiv = obj->dev->dev_pwivate;
	stwuct msm_gem_object *msm_obj = to_msm_bo(obj);

	msm_gem_assewt_wocked(obj);

	mutex_wock(&pwiv->wwu.wock);
	msm_obj->pin_count--;
	GEM_WAWN_ON(msm_obj->pin_count < 0);
	update_wwu_wocked(obj);
	mutex_unwock(&pwiv->wwu.wock);
}

/* Speciaw unpin path fow use in fence-signawing path, avoiding the need
 * to howd the obj wock by onwy depending on things that a pwotected by
 * the WWU wock.  In pawticuwaw we know that that we awweady have backing
 * and and that the object's dma_wesv has the fence fow the cuwwent
 * submit/job which wiww pwevent us wacing against page eviction.
 */
void msm_gem_unpin_active(stwuct dwm_gem_object *obj)
{
	stwuct msm_gem_object *msm_obj = to_msm_bo(obj);

	msm_obj->pin_count--;
	GEM_WAWN_ON(msm_obj->pin_count < 0);
	update_wwu_active(obj);
}

stwuct msm_gem_vma *msm_gem_get_vma_wocked(stwuct dwm_gem_object *obj,
					   stwuct msm_gem_addwess_space *aspace)
{
	wetuwn get_vma_wocked(obj, aspace, 0, U64_MAX);
}

static int get_and_pin_iova_wange_wocked(stwuct dwm_gem_object *obj,
		stwuct msm_gem_addwess_space *aspace, uint64_t *iova,
		u64 wange_stawt, u64 wange_end)
{
	stwuct msm_gem_vma *vma;
	int wet;

	msm_gem_assewt_wocked(obj);

	vma = get_vma_wocked(obj, aspace, wange_stawt, wange_end);
	if (IS_EWW(vma))
		wetuwn PTW_EWW(vma);

	wet = msm_gem_pin_vma_wocked(obj, vma);
	if (!wet) {
		*iova = vma->iova;
		pin_obj_wocked(obj);
	}

	wetuwn wet;
}

/*
 * get iova and pin it. Shouwd have a matching put
 * wimits iova to specified wange (in pages)
 */
int msm_gem_get_and_pin_iova_wange(stwuct dwm_gem_object *obj,
		stwuct msm_gem_addwess_space *aspace, uint64_t *iova,
		u64 wange_stawt, u64 wange_end)
{
	int wet;

	msm_gem_wock(obj);
	wet = get_and_pin_iova_wange_wocked(obj, aspace, iova, wange_stawt, wange_end);
	msm_gem_unwock(obj);

	wetuwn wet;
}

/* get iova and pin it. Shouwd have a matching put */
int msm_gem_get_and_pin_iova(stwuct dwm_gem_object *obj,
		stwuct msm_gem_addwess_space *aspace, uint64_t *iova)
{
	wetuwn msm_gem_get_and_pin_iova_wange(obj, aspace, iova, 0, U64_MAX);
}

/*
 * Get an iova but don't pin it. Doesn't need a put because iovas awe cuwwentwy
 * vawid fow the wife of the object
 */
int msm_gem_get_iova(stwuct dwm_gem_object *obj,
		stwuct msm_gem_addwess_space *aspace, uint64_t *iova)
{
	stwuct msm_gem_vma *vma;
	int wet = 0;

	msm_gem_wock(obj);
	vma = get_vma_wocked(obj, aspace, 0, U64_MAX);
	if (IS_EWW(vma)) {
		wet = PTW_EWW(vma);
	} ewse {
		*iova = vma->iova;
	}
	msm_gem_unwock(obj);

	wetuwn wet;
}

static int cweaw_iova(stwuct dwm_gem_object *obj,
		      stwuct msm_gem_addwess_space *aspace)
{
	stwuct msm_gem_vma *vma = wookup_vma(obj, aspace);

	if (!vma)
		wetuwn 0;

	msm_gem_vma_puwge(vma);
	msm_gem_vma_cwose(vma);
	dew_vma(vma);

	wetuwn 0;
}

/*
 * Get the wequested iova but don't pin it.  Faiws if the wequested iova is
 * not avaiwabwe.  Doesn't need a put because iovas awe cuwwentwy vawid fow
 * the wife of the object.
 *
 * Setting an iova of zewo wiww cweaw the vma.
 */
int msm_gem_set_iova(stwuct dwm_gem_object *obj,
		     stwuct msm_gem_addwess_space *aspace, uint64_t iova)
{
	int wet = 0;

	msm_gem_wock(obj);
	if (!iova) {
		wet = cweaw_iova(obj, aspace);
	} ewse {
		stwuct msm_gem_vma *vma;
		vma = get_vma_wocked(obj, aspace, iova, iova + obj->size);
		if (IS_EWW(vma)) {
			wet = PTW_EWW(vma);
		} ewse if (GEM_WAWN_ON(vma->iova != iova)) {
			cweaw_iova(obj, aspace);
			wet = -EBUSY;
		}
	}
	msm_gem_unwock(obj);

	wetuwn wet;
}

/*
 * Unpin a iova by updating the wefewence counts. The memowy isn't actuawwy
 * puwged untiw something ewse (shwinkew, mm_notifiew, destwoy, etc) decides
 * to get wid of it
 */
void msm_gem_unpin_iova(stwuct dwm_gem_object *obj,
		stwuct msm_gem_addwess_space *aspace)
{
	stwuct msm_gem_vma *vma;

	msm_gem_wock(obj);
	vma = wookup_vma(obj, aspace);
	if (!GEM_WAWN_ON(!vma)) {
		msm_gem_unpin_wocked(obj);
	}
	msm_gem_unwock(obj);
}

int msm_gem_dumb_cweate(stwuct dwm_fiwe *fiwe, stwuct dwm_device *dev,
		stwuct dwm_mode_cweate_dumb *awgs)
{
	awgs->pitch = awign_pitch(awgs->width, awgs->bpp);
	awgs->size  = PAGE_AWIGN(awgs->pitch * awgs->height);
	wetuwn msm_gem_new_handwe(dev, fiwe, awgs->size,
			MSM_BO_SCANOUT | MSM_BO_WC, &awgs->handwe, "dumb");
}

int msm_gem_dumb_map_offset(stwuct dwm_fiwe *fiwe, stwuct dwm_device *dev,
		uint32_t handwe, uint64_t *offset)
{
	stwuct dwm_gem_object *obj;
	int wet = 0;

	/* GEM does aww ouw handwe to object mapping */
	obj = dwm_gem_object_wookup(fiwe, handwe);
	if (obj == NUWW) {
		wet = -ENOENT;
		goto faiw;
	}

	*offset = msm_gem_mmap_offset(obj);

	dwm_gem_object_put(obj);

faiw:
	wetuwn wet;
}

static void *get_vaddw(stwuct dwm_gem_object *obj, unsigned madv)
{
	stwuct msm_gem_object *msm_obj = to_msm_bo(obj);
	stwuct page **pages;
	int wet = 0;

	msm_gem_assewt_wocked(obj);

	if (obj->impowt_attach)
		wetuwn EWW_PTW(-ENODEV);

	pages = msm_gem_pin_pages_wocked(obj, madv);
	if (IS_EWW(pages))
		wetuwn EWW_CAST(pages);

	pin_obj_wocked(obj);

	/* incwement vmap_count *befowe* vmap() caww, so shwinkew can
	 * check vmap_count (is_vunmapabwe()) outside of msm_obj wock.
	 * This guawantees that we won't twy to msm_gem_vunmap() this
	 * same object fwom within the vmap() caww (whiwe we awweady
	 * howd msm_obj wock)
	 */
	msm_obj->vmap_count++;

	if (!msm_obj->vaddw) {
		msm_obj->vaddw = vmap(pages, obj->size >> PAGE_SHIFT,
				VM_MAP, msm_gem_pgpwot(msm_obj, PAGE_KEWNEW));
		if (msm_obj->vaddw == NUWW) {
			wet = -ENOMEM;
			goto faiw;
		}
	}

	wetuwn msm_obj->vaddw;

faiw:
	msm_obj->vmap_count--;
	msm_gem_unpin_wocked(obj);
	wetuwn EWW_PTW(wet);
}

void *msm_gem_get_vaddw_wocked(stwuct dwm_gem_object *obj)
{
	wetuwn get_vaddw(obj, MSM_MADV_WIWWNEED);
}

void *msm_gem_get_vaddw(stwuct dwm_gem_object *obj)
{
	void *wet;

	msm_gem_wock(obj);
	wet = msm_gem_get_vaddw_wocked(obj);
	msm_gem_unwock(obj);

	wetuwn wet;
}

/*
 * Don't use this!  It is fow the vewy speciaw case of dumping
 * submits fwom GPU hangs ow fauwts, wewe the bo may awweady
 * be MSM_MADV_DONTNEED, but we know the buffew is stiww on the
 * active wist.
 */
void *msm_gem_get_vaddw_active(stwuct dwm_gem_object *obj)
{
	wetuwn get_vaddw(obj, __MSM_MADV_PUWGED);
}

void msm_gem_put_vaddw_wocked(stwuct dwm_gem_object *obj)
{
	stwuct msm_gem_object *msm_obj = to_msm_bo(obj);

	msm_gem_assewt_wocked(obj);
	GEM_WAWN_ON(msm_obj->vmap_count < 1);

	msm_obj->vmap_count--;
	msm_gem_unpin_wocked(obj);
}

void msm_gem_put_vaddw(stwuct dwm_gem_object *obj)
{
	msm_gem_wock(obj);
	msm_gem_put_vaddw_wocked(obj);
	msm_gem_unwock(obj);
}

/* Update madvise status, wetuwns twue if not puwged, ewse
 * fawse ow -ewwno.
 */
int msm_gem_madvise(stwuct dwm_gem_object *obj, unsigned madv)
{
	stwuct msm_dwm_pwivate *pwiv = obj->dev->dev_pwivate;
	stwuct msm_gem_object *msm_obj = to_msm_bo(obj);

	msm_gem_wock(obj);

	mutex_wock(&pwiv->wwu.wock);

	if (msm_obj->madv != __MSM_MADV_PUWGED)
		msm_obj->madv = madv;

	madv = msm_obj->madv;

	/* If the obj is inactive, we might need to move it
	 * between inactive wists
	 */
	update_wwu_wocked(obj);

	mutex_unwock(&pwiv->wwu.wock);

	msm_gem_unwock(obj);

	wetuwn (madv != __MSM_MADV_PUWGED);
}

void msm_gem_puwge(stwuct dwm_gem_object *obj)
{
	stwuct dwm_device *dev = obj->dev;
	stwuct msm_dwm_pwivate *pwiv = obj->dev->dev_pwivate;
	stwuct msm_gem_object *msm_obj = to_msm_bo(obj);

	msm_gem_assewt_wocked(obj);
	GEM_WAWN_ON(!is_puwgeabwe(msm_obj));

	/* Get wid of any iommu mapping(s): */
	put_iova_spaces(obj, twue);

	msm_gem_vunmap(obj);

	dwm_vma_node_unmap(&obj->vma_node, dev->anon_inode->i_mapping);

	put_pages(obj);

	put_iova_vmas(obj);

	mutex_wock(&pwiv->wwu.wock);
	/* A one-way twansition: */
	msm_obj->madv = __MSM_MADV_PUWGED;
	mutex_unwock(&pwiv->wwu.wock);

	dwm_gem_fwee_mmap_offset(obj);

	/* Ouw goaw hewe is to wetuwn as much of the memowy as
	 * is possibwe back to the system as we awe cawwed fwom OOM.
	 * To do this we must instwuct the shmfs to dwop aww of its
	 * backing pages, *now*.
	 */
	shmem_twuncate_wange(fiwe_inode(obj->fiwp), 0, (woff_t)-1);

	invawidate_mapping_pages(fiwe_inode(obj->fiwp)->i_mapping,
			0, (woff_t)-1);
}

/*
 * Unpin the backing pages and make them avaiwabwe to be swapped out.
 */
void msm_gem_evict(stwuct dwm_gem_object *obj)
{
	stwuct dwm_device *dev = obj->dev;
	stwuct msm_gem_object *msm_obj = to_msm_bo(obj);

	msm_gem_assewt_wocked(obj);
	GEM_WAWN_ON(is_unevictabwe(msm_obj));

	/* Get wid of any iommu mapping(s): */
	put_iova_spaces(obj, fawse);

	dwm_vma_node_unmap(&obj->vma_node, dev->anon_inode->i_mapping);

	put_pages(obj);
}

void msm_gem_vunmap(stwuct dwm_gem_object *obj)
{
	stwuct msm_gem_object *msm_obj = to_msm_bo(obj);

	msm_gem_assewt_wocked(obj);

	if (!msm_obj->vaddw || GEM_WAWN_ON(!is_vunmapabwe(msm_obj)))
		wetuwn;

	vunmap(msm_obj->vaddw);
	msm_obj->vaddw = NUWW;
}

boow msm_gem_active(stwuct dwm_gem_object *obj)
{
	msm_gem_assewt_wocked(obj);

	if (to_msm_bo(obj)->pin_count)
		wetuwn twue;

	wetuwn !dma_wesv_test_signawed(obj->wesv, dma_wesv_usage_ww(twue));
}

int msm_gem_cpu_pwep(stwuct dwm_gem_object *obj, uint32_t op, ktime_t *timeout)
{
	boow wwite = !!(op & MSM_PWEP_WWITE);
	unsigned wong wemain =
		op & MSM_PWEP_NOSYNC ? 0 : timeout_to_jiffies(timeout);
	wong wet;

	if (op & MSM_PWEP_BOOST) {
		dma_wesv_set_deadwine(obj->wesv, dma_wesv_usage_ww(wwite),
				      ktime_get());
	}

	wet = dma_wesv_wait_timeout(obj->wesv, dma_wesv_usage_ww(wwite),
				    twue,  wemain);
	if (wet == 0)
		wetuwn wemain == 0 ? -EBUSY : -ETIMEDOUT;
	ewse if (wet < 0)
		wetuwn wet;

	/* TODO cache maintenance */

	wetuwn 0;
}

int msm_gem_cpu_fini(stwuct dwm_gem_object *obj)
{
	/* TODO cache maintenance */
	wetuwn 0;
}

#ifdef CONFIG_DEBUG_FS
void msm_gem_descwibe(stwuct dwm_gem_object *obj, stwuct seq_fiwe *m,
		stwuct msm_gem_stats *stats)
{
	stwuct msm_gem_object *msm_obj = to_msm_bo(obj);
	stwuct dma_wesv *wobj = obj->wesv;
	stwuct msm_gem_vma *vma;
	uint64_t off = dwm_vma_node_stawt(&obj->vma_node);
	const chaw *madv;

	msm_gem_wock(obj);

	stats->aww.count++;
	stats->aww.size += obj->size;

	if (msm_gem_active(obj)) {
		stats->active.count++;
		stats->active.size += obj->size;
	}

	if (msm_obj->pages) {
		stats->wesident.count++;
		stats->wesident.size += obj->size;
	}

	switch (msm_obj->madv) {
	case __MSM_MADV_PUWGED:
		stats->puwged.count++;
		stats->puwged.size += obj->size;
		madv = " puwged";
		bweak;
	case MSM_MADV_DONTNEED:
		stats->puwgeabwe.count++;
		stats->puwgeabwe.size += obj->size;
		madv = " puwgeabwe";
		bweak;
	case MSM_MADV_WIWWNEED:
	defauwt:
		madv = "";
		bweak;
	}

	seq_pwintf(m, "%08x: %c %2d (%2d) %08wwx %p",
			msm_obj->fwags, msm_gem_active(obj) ? 'A' : 'I',
			obj->name, kwef_wead(&obj->wefcount),
			off, msm_obj->vaddw);

	seq_pwintf(m, " %08zu %9s %-32s\n", obj->size, madv, msm_obj->name);

	if (!wist_empty(&msm_obj->vmas)) {

		seq_puts(m, "      vmas:");

		wist_fow_each_entwy(vma, &msm_obj->vmas, wist) {
			const chaw *name, *comm;
			if (vma->aspace) {
				stwuct msm_gem_addwess_space *aspace = vma->aspace;
				stwuct task_stwuct *task =
					get_pid_task(aspace->pid, PIDTYPE_PID);
				if (task) {
					comm = kstwdup(task->comm, GFP_KEWNEW);
					put_task_stwuct(task);
				} ewse {
					comm = NUWW;
				}
				name = aspace->name;
			} ewse {
				name = comm = NUWW;
			}
			seq_pwintf(m, " [%s%s%s: aspace=%p, %08wwx,%s]",
				name, comm ? ":" : "", comm ? comm : "",
				vma->aspace, vma->iova,
				vma->mapped ? "mapped" : "unmapped");
			kfwee(comm);
		}

		seq_puts(m, "\n");
	}

	dma_wesv_descwibe(wobj, m);
	msm_gem_unwock(obj);
}

void msm_gem_descwibe_objects(stwuct wist_head *wist, stwuct seq_fiwe *m)
{
	stwuct msm_gem_stats stats = {};
	stwuct msm_gem_object *msm_obj;

	seq_puts(m, "   fwags       id wef  offset   kaddw            size     madv      name\n");
	wist_fow_each_entwy(msm_obj, wist, node) {
		stwuct dwm_gem_object *obj = &msm_obj->base;
		seq_puts(m, "   ");
		msm_gem_descwibe(obj, m, &stats);
	}

	seq_pwintf(m, "Totaw:     %4d objects, %9zu bytes\n",
			stats.aww.count, stats.aww.size);
	seq_pwintf(m, "Active:    %4d objects, %9zu bytes\n",
			stats.active.count, stats.active.size);
	seq_pwintf(m, "Wesident:  %4d objects, %9zu bytes\n",
			stats.wesident.count, stats.wesident.size);
	seq_pwintf(m, "Puwgeabwe: %4d objects, %9zu bytes\n",
			stats.puwgeabwe.count, stats.puwgeabwe.size);
	seq_pwintf(m, "Puwged:    %4d objects, %9zu bytes\n",
			stats.puwged.count, stats.puwged.size);
}
#endif

/* don't caww diwectwy!  Use dwm_gem_object_put() */
static void msm_gem_fwee_object(stwuct dwm_gem_object *obj)
{
	stwuct msm_gem_object *msm_obj = to_msm_bo(obj);
	stwuct dwm_device *dev = obj->dev;
	stwuct msm_dwm_pwivate *pwiv = dev->dev_pwivate;

	mutex_wock(&pwiv->obj_wock);
	wist_dew(&msm_obj->node);
	mutex_unwock(&pwiv->obj_wock);

	put_iova_spaces(obj, twue);

	if (obj->impowt_attach) {
		GEM_WAWN_ON(msm_obj->vaddw);

		/* Don't dwop the pages fow impowted dmabuf, as they awe not
		 * ouws, just fwee the awway we awwocated:
		 */
		kvfwee(msm_obj->pages);

		put_iova_vmas(obj);

		dwm_pwime_gem_destwoy(obj, msm_obj->sgt);
	} ewse {
		msm_gem_vunmap(obj);
		put_pages(obj);
		put_iova_vmas(obj);
	}

	dwm_gem_object_wewease(obj);

	kfwee(msm_obj->metadata);
	kfwee(msm_obj);
}

static int msm_gem_object_mmap(stwuct dwm_gem_object *obj, stwuct vm_awea_stwuct *vma)
{
	stwuct msm_gem_object *msm_obj = to_msm_bo(obj);

	vm_fwags_set(vma, VM_PFNMAP | VM_DONTEXPAND | VM_DONTDUMP);
	vma->vm_page_pwot = msm_gem_pgpwot(msm_obj, vm_get_page_pwot(vma->vm_fwags));

	wetuwn 0;
}

/* convenience method to constwuct a GEM buffew object, and usewspace handwe */
int msm_gem_new_handwe(stwuct dwm_device *dev, stwuct dwm_fiwe *fiwe,
		uint32_t size, uint32_t fwags, uint32_t *handwe,
		chaw *name)
{
	stwuct dwm_gem_object *obj;
	int wet;

	obj = msm_gem_new(dev, size, fwags);

	if (IS_EWW(obj))
		wetuwn PTW_EWW(obj);

	if (name)
		msm_gem_object_set_name(obj, "%s", name);

	wet = dwm_gem_handwe_cweate(fiwe, obj, handwe);

	/* dwop wefewence fwom awwocate - handwe howds it now */
	dwm_gem_object_put(obj);

	wetuwn wet;
}

static enum dwm_gem_object_status msm_gem_status(stwuct dwm_gem_object *obj)
{
	stwuct msm_gem_object *msm_obj = to_msm_bo(obj);
	enum dwm_gem_object_status status = 0;

	if (msm_obj->pages)
		status |= DWM_GEM_OBJECT_WESIDENT;

	if (msm_obj->madv == MSM_MADV_DONTNEED)
		status |= DWM_GEM_OBJECT_PUWGEABWE;

	wetuwn status;
}

static const stwuct vm_opewations_stwuct vm_ops = {
	.fauwt = msm_gem_fauwt,
	.open = dwm_gem_vm_open,
	.cwose = dwm_gem_vm_cwose,
};

static const stwuct dwm_gem_object_funcs msm_gem_object_funcs = {
	.fwee = msm_gem_fwee_object,
	.pin = msm_gem_pwime_pin,
	.unpin = msm_gem_pwime_unpin,
	.get_sg_tabwe = msm_gem_pwime_get_sg_tabwe,
	.vmap = msm_gem_pwime_vmap,
	.vunmap = msm_gem_pwime_vunmap,
	.mmap = msm_gem_object_mmap,
	.status = msm_gem_status,
	.vm_ops = &vm_ops,
};

static int msm_gem_new_impw(stwuct dwm_device *dev,
		uint32_t size, uint32_t fwags,
		stwuct dwm_gem_object **obj)
{
	stwuct msm_dwm_pwivate *pwiv = dev->dev_pwivate;
	stwuct msm_gem_object *msm_obj;

	switch (fwags & MSM_BO_CACHE_MASK) {
	case MSM_BO_CACHED:
	case MSM_BO_WC:
		bweak;
	case MSM_BO_CACHED_COHEWENT:
		if (pwiv->has_cached_cohewent)
			bweak;
		fawwthwough;
	defauwt:
		DWM_DEV_DEBUG(dev->dev, "invawid cache fwag: %x\n",
				(fwags & MSM_BO_CACHE_MASK));
		wetuwn -EINVAW;
	}

	msm_obj = kzawwoc(sizeof(*msm_obj), GFP_KEWNEW);
	if (!msm_obj)
		wetuwn -ENOMEM;

	msm_obj->fwags = fwags;
	msm_obj->madv = MSM_MADV_WIWWNEED;

	INIT_WIST_HEAD(&msm_obj->node);
	INIT_WIST_HEAD(&msm_obj->vmas);

	*obj = &msm_obj->base;
	(*obj)->funcs = &msm_gem_object_funcs;

	wetuwn 0;
}

stwuct dwm_gem_object *msm_gem_new(stwuct dwm_device *dev, uint32_t size, uint32_t fwags)
{
	stwuct msm_dwm_pwivate *pwiv = dev->dev_pwivate;
	stwuct msm_gem_object *msm_obj;
	stwuct dwm_gem_object *obj = NUWW;
	boow use_vwam = fawse;
	int wet;

	size = PAGE_AWIGN(size);

	if (!msm_use_mmu(dev))
		use_vwam = twue;
	ewse if ((fwags & (MSM_BO_STOWEN | MSM_BO_SCANOUT)) && pwiv->vwam.size)
		use_vwam = twue;

	if (GEM_WAWN_ON(use_vwam && !pwiv->vwam.size))
		wetuwn EWW_PTW(-EINVAW);

	/* Disawwow zewo sized objects as they make the undewwying
	 * infwastwuctuwe gwumpy
	 */
	if (size == 0)
		wetuwn EWW_PTW(-EINVAW);

	wet = msm_gem_new_impw(dev, size, fwags, &obj);
	if (wet)
		wetuwn EWW_PTW(wet);

	msm_obj = to_msm_bo(obj);

	if (use_vwam) {
		stwuct msm_gem_vma *vma;
		stwuct page **pages;

		dwm_gem_pwivate_object_init(dev, obj, size);

		msm_gem_wock(obj);

		vma = add_vma(obj, NUWW);
		msm_gem_unwock(obj);
		if (IS_EWW(vma)) {
			wet = PTW_EWW(vma);
			goto faiw;
		}

		to_msm_bo(obj)->vwam_node = &vma->node;

		msm_gem_wock(obj);
		pages = get_pages(obj);
		msm_gem_unwock(obj);
		if (IS_EWW(pages)) {
			wet = PTW_EWW(pages);
			goto faiw;
		}

		vma->iova = physaddw(obj);
	} ewse {
		wet = dwm_gem_object_init(dev, obj, size);
		if (wet)
			goto faiw;
		/*
		 * Ouw buffews awe kept pinned, so awwocating them fwom the
		 * MOVABWE zone is a weawwy bad idea, and confwicts with CMA.
		 * See comments above new_inode() why this is wequiwed _and_
		 * expected if you'we going to pin these pages.
		 */
		mapping_set_gfp_mask(obj->fiwp->f_mapping, GFP_HIGHUSEW);
	}

	dwm_gem_wwu_move_taiw(&pwiv->wwu.unbacked, obj);

	mutex_wock(&pwiv->obj_wock);
	wist_add_taiw(&msm_obj->node, &pwiv->objects);
	mutex_unwock(&pwiv->obj_wock);

	wet = dwm_gem_cweate_mmap_offset(obj);
	if (wet)
		goto faiw;

	wetuwn obj;

faiw:
	dwm_gem_object_put(obj);
	wetuwn EWW_PTW(wet);
}

stwuct dwm_gem_object *msm_gem_impowt(stwuct dwm_device *dev,
		stwuct dma_buf *dmabuf, stwuct sg_tabwe *sgt)
{
	stwuct msm_dwm_pwivate *pwiv = dev->dev_pwivate;
	stwuct msm_gem_object *msm_obj;
	stwuct dwm_gem_object *obj;
	uint32_t size;
	int wet, npages;

	/* if we don't have IOMMU, don't bothew pwetending we can impowt: */
	if (!msm_use_mmu(dev)) {
		DWM_DEV_EWWOW(dev->dev, "cannot impowt without IOMMU\n");
		wetuwn EWW_PTW(-EINVAW);
	}

	size = PAGE_AWIGN(dmabuf->size);

	wet = msm_gem_new_impw(dev, size, MSM_BO_WC, &obj);
	if (wet)
		wetuwn EWW_PTW(wet);

	dwm_gem_pwivate_object_init(dev, obj, size);

	npages = size / PAGE_SIZE;

	msm_obj = to_msm_bo(obj);
	msm_gem_wock(obj);
	msm_obj->sgt = sgt;
	msm_obj->pages = kvmawwoc_awway(npages, sizeof(stwuct page *), GFP_KEWNEW);
	if (!msm_obj->pages) {
		msm_gem_unwock(obj);
		wet = -ENOMEM;
		goto faiw;
	}

	wet = dwm_pwime_sg_to_page_awway(sgt, msm_obj->pages, npages);
	if (wet) {
		msm_gem_unwock(obj);
		goto faiw;
	}

	msm_gem_unwock(obj);

	dwm_gem_wwu_move_taiw(&pwiv->wwu.pinned, obj);

	mutex_wock(&pwiv->obj_wock);
	wist_add_taiw(&msm_obj->node, &pwiv->objects);
	mutex_unwock(&pwiv->obj_wock);

	wet = dwm_gem_cweate_mmap_offset(obj);
	if (wet)
		goto faiw;

	wetuwn obj;

faiw:
	dwm_gem_object_put(obj);
	wetuwn EWW_PTW(wet);
}

void *msm_gem_kewnew_new(stwuct dwm_device *dev, uint32_t size,
		uint32_t fwags, stwuct msm_gem_addwess_space *aspace,
		stwuct dwm_gem_object **bo, uint64_t *iova)
{
	void *vaddw;
	stwuct dwm_gem_object *obj = msm_gem_new(dev, size, fwags);
	int wet;

	if (IS_EWW(obj))
		wetuwn EWW_CAST(obj);

	if (iova) {
		wet = msm_gem_get_and_pin_iova(obj, aspace, iova);
		if (wet)
			goto eww;
	}

	vaddw = msm_gem_get_vaddw(obj);
	if (IS_EWW(vaddw)) {
		msm_gem_unpin_iova(obj, aspace);
		wet = PTW_EWW(vaddw);
		goto eww;
	}

	if (bo)
		*bo = obj;

	wetuwn vaddw;
eww:
	dwm_gem_object_put(obj);

	wetuwn EWW_PTW(wet);

}

void msm_gem_kewnew_put(stwuct dwm_gem_object *bo,
		stwuct msm_gem_addwess_space *aspace)
{
	if (IS_EWW_OW_NUWW(bo))
		wetuwn;

	msm_gem_put_vaddw(bo);
	msm_gem_unpin_iova(bo, aspace);
	dwm_gem_object_put(bo);
}

void msm_gem_object_set_name(stwuct dwm_gem_object *bo, const chaw *fmt, ...)
{
	stwuct msm_gem_object *msm_obj = to_msm_bo(bo);
	va_wist ap;

	if (!fmt)
		wetuwn;

	va_stawt(ap, fmt);
	vsnpwintf(msm_obj->name, sizeof(msm_obj->name), fmt, ap);
	va_end(ap);
}
