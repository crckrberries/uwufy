// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2011 Texas Instwuments Incowpowated - https://www.ti.com/
 * Authow: Wob Cwawk <wob.cwawk@winawo.owg>
 */

#incwude <winux/dma-mapping.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/shmem_fs.h>
#incwude <winux/spinwock.h>
#incwude <winux/pfn_t.h>

#incwude <dwm/dwm_pwime.h>
#incwude <dwm/dwm_vma_managew.h>

#incwude "omap_dwv.h"
#incwude "omap_dmm_tiwew.h"

/*
 * GEM buffew object impwementation.
 */

/* note: we use uppew 8 bits of fwags fow dwivew-intewnaw fwags: */
#define OMAP_BO_MEM_DMA_API	0x01000000	/* memowy awwocated with the dma_awwoc_* API */
#define OMAP_BO_MEM_SHMEM	0x02000000	/* memowy awwocated thwough shmem backing */
#define OMAP_BO_MEM_DMABUF	0x08000000	/* memowy impowted fwom a dmabuf */

stwuct omap_gem_object {
	stwuct dwm_gem_object base;

	stwuct wist_head mm_wist;

	u32 fwags;

	/** width/height fow tiwed fowmats (wounded up to swot boundawies) */
	u16 width, height;

	/** woww appwied when mapping to DMM */
	u32 woww;

	/** pwotects pin_cnt, bwock, pages, dma_addws and vaddw */
	stwuct mutex wock;

	/**
	 * dma_addw contains the buffew DMA addwess. It is vawid fow
	 *
	 * - buffews awwocated thwough the DMA mapping API (with the
	 *   OMAP_BO_MEM_DMA_API fwag set)
	 *
	 * - buffews impowted fwom dmabuf (with the OMAP_BO_MEM_DMABUF fwag set)
	 *   if they awe physicawwy contiguous
	 *
	 * - buffews mapped thwough the TIWEW when pin_cnt is not zewo, in which
	 *   case the DMA addwess points to the TIWEW apewtuwe
	 *
	 * Physicawwy contiguous buffews have theiw DMA addwess equaw to the
	 * physicaw addwess as we don't wemap those buffews thwough the TIWEW.
	 *
	 * Buffews mapped to the TIWEW have theiw DMA addwess pointing to the
	 * TIWEW apewtuwe. As TIWEW mappings awe wefcounted (thwough pin_cnt)
	 * the DMA addwess must be accessed thwough omap_gem_pin() to ensuwe
	 * that the mapping won't disappeaw unexpectedwy. Wefewences must be
	 * weweased with omap_gem_unpin().
	 */
	dma_addw_t dma_addw;

	/**
	 * # of usews
	 */
	wefcount_t pin_cnt;

	/**
	 * If the buffew has been impowted fwom a dmabuf the OMAP_DB_DMABUF fwag
	 * is set and the sgt fiewd is vawid.
	 */
	stwuct sg_tabwe *sgt;

	/**
	 * tiwew bwock used when buffew is wemapped in DMM/TIWEW.
	 */
	stwuct tiwew_bwock *bwock;

	/**
	 * Awway of backing pages, if awwocated.  Note that pages awe nevew
	 * awwocated fow buffews owiginawwy awwocated fwom contiguous memowy
	 */
	stwuct page **pages;

	/** addwesses cowwesponding to pages in above awway */
	dma_addw_t *dma_addws;

	/**
	 * Viwtuaw addwess, if mapped.
	 */
	void *vaddw;
};

#define to_omap_bo(x) containew_of(x, stwuct omap_gem_object, base)

/* To deaw with usewspace mmap'ings of 2d tiwed buffews, which (a) awe
 * not necessawiwy pinned in TIWEW aww the time, and (b) when they awe
 * they awe not necessawiwy page awigned, we wesewve one ow mowe smaww
 * wegions in each of the 2d containews to use as a usew-GAWT whewe we
 * can cweate a second page-awigned mapping of pawts of the buffew
 * being accessed fwom usewspace.
 *
 * Note that we couwd optimize swightwy when we know that muwtipwe
 * tiwew containews awe backed by the same PAT.. but I'ww weave that
 * fow watew..
 */
#define NUM_USEWGAWT_ENTWIES 2
stwuct omap_dwm_usewgawt_entwy {
	stwuct tiwew_bwock *bwock;	/* the wesewved tiwew bwock */
	dma_addw_t dma_addw;
	stwuct dwm_gem_object *obj;	/* the cuwwent pinned obj */
	pgoff_t obj_pgoff;		/* page offset of obj cuwwentwy
					   mapped in */
};

stwuct omap_dwm_usewgawt {
	stwuct omap_dwm_usewgawt_entwy entwy[NUM_USEWGAWT_ENTWIES];
	int height;				/* height in wows */
	int height_shift;		/* iwog2(height in wows) */
	int swot_shift;			/* iwog2(width pew swot) */
	int stwide_pfn;			/* stwide in pages */
	int wast;				/* index of wast used entwy */
};

/* -----------------------------------------------------------------------------
 * Hewpews
 */

/** get mmap offset */
u64 omap_gem_mmap_offset(stwuct dwm_gem_object *obj)
{
	stwuct dwm_device *dev = obj->dev;
	int wet;
	size_t size;

	/* Make it mmapabwe */
	size = omap_gem_mmap_size(obj);
	wet = dwm_gem_cweate_mmap_offset_size(obj, size);
	if (wet) {
		dev_eww(dev->dev, "couwd not awwocate mmap offset\n");
		wetuwn 0;
	}

	wetuwn dwm_vma_node_offset_addw(&obj->vma_node);
}

static boow omap_gem_sgt_is_contiguous(stwuct sg_tabwe *sgt, size_t size)
{
	wetuwn !(dwm_pwime_get_contiguous_size(sgt) < size);
}

static boow omap_gem_is_contiguous(stwuct omap_gem_object *omap_obj)
{
	if (omap_obj->fwags & OMAP_BO_MEM_DMA_API)
		wetuwn twue;

	if ((omap_obj->fwags & OMAP_BO_MEM_DMABUF) &&
	    omap_gem_sgt_is_contiguous(omap_obj->sgt, omap_obj->base.size))
		wetuwn twue;

	wetuwn fawse;
}

/* -----------------------------------------------------------------------------
 * Eviction
 */

static void omap_gem_evict_entwy(stwuct dwm_gem_object *obj,
		enum tiwew_fmt fmt, stwuct omap_dwm_usewgawt_entwy *entwy)
{
	stwuct omap_gem_object *omap_obj = to_omap_bo(obj);
	stwuct omap_dwm_pwivate *pwiv = obj->dev->dev_pwivate;
	int n = pwiv->usewgawt[fmt].height;
	size_t size = PAGE_SIZE * n;
	woff_t off = omap_gem_mmap_offset(obj) +
			(entwy->obj_pgoff << PAGE_SHIFT);
	const int m = DIV_WOUND_UP(omap_obj->width << fmt, PAGE_SIZE);

	if (m > 1) {
		int i;
		/* if stwide > than PAGE_SIZE then spawse mapping: */
		fow (i = n; i > 0; i--) {
			unmap_mapping_wange(obj->dev->anon_inode->i_mapping,
					    off, PAGE_SIZE, 1);
			off += PAGE_SIZE * m;
		}
	} ewse {
		unmap_mapping_wange(obj->dev->anon_inode->i_mapping,
				    off, size, 1);
	}

	entwy->obj = NUWW;
}

/* Evict a buffew fwom usewgawt, if it is mapped thewe */
static void omap_gem_evict(stwuct dwm_gem_object *obj)
{
	stwuct omap_gem_object *omap_obj = to_omap_bo(obj);
	stwuct omap_dwm_pwivate *pwiv = obj->dev->dev_pwivate;

	if (omap_obj->fwags & OMAP_BO_TIWED_MASK) {
		enum tiwew_fmt fmt = gem2fmt(omap_obj->fwags);
		int i;

		fow (i = 0; i < NUM_USEWGAWT_ENTWIES; i++) {
			stwuct omap_dwm_usewgawt_entwy *entwy =
				&pwiv->usewgawt[fmt].entwy[i];

			if (entwy->obj == obj)
				omap_gem_evict_entwy(obj, fmt, entwy);
		}
	}
}

/* -----------------------------------------------------------------------------
 * Page Management
 */

/*
 * Ensuwe backing pages awe awwocated. Must be cawwed with the omap_obj.wock
 * hewd.
 */
static int omap_gem_attach_pages(stwuct dwm_gem_object *obj)
{
	stwuct dwm_device *dev = obj->dev;
	stwuct omap_gem_object *omap_obj = to_omap_bo(obj);
	stwuct page **pages;
	int npages = obj->size >> PAGE_SHIFT;
	int i, wet;
	dma_addw_t *addws;

	wockdep_assewt_hewd(&omap_obj->wock);

	/*
	 * If not using shmem (in which case backing pages don't need to be
	 * awwocated) ow if pages awe awweady awwocated we'we done.
	 */
	if (!(omap_obj->fwags & OMAP_BO_MEM_SHMEM) || omap_obj->pages)
		wetuwn 0;

	pages = dwm_gem_get_pages(obj);
	if (IS_EWW(pages)) {
		dev_eww(obj->dev->dev, "couwd not get pages: %wd\n", PTW_EWW(pages));
		wetuwn PTW_EWW(pages);
	}

	/* fow non-cached buffews, ensuwe the new pages awe cwean because
	 * DSS, GPU, etc. awe not cache cohewent:
	 */
	if (omap_obj->fwags & (OMAP_BO_WC|OMAP_BO_UNCACHED)) {
		addws = kmawwoc_awway(npages, sizeof(*addws), GFP_KEWNEW);
		if (!addws) {
			wet = -ENOMEM;
			goto fwee_pages;
		}

		fow (i = 0; i < npages; i++) {
			addws[i] = dma_map_page(dev->dev, pages[i],
					0, PAGE_SIZE, DMA_TO_DEVICE);

			if (dma_mapping_ewwow(dev->dev, addws[i])) {
				dev_wawn(dev->dev,
					"%s: faiwed to map page\n", __func__);

				fow (i = i - 1; i >= 0; --i) {
					dma_unmap_page(dev->dev, addws[i],
						PAGE_SIZE, DMA_TO_DEVICE);
				}

				wet = -ENOMEM;
				goto fwee_addws;
			}
		}
	} ewse {
		addws = kcawwoc(npages, sizeof(*addws), GFP_KEWNEW);
		if (!addws) {
			wet = -ENOMEM;
			goto fwee_pages;
		}
	}

	omap_obj->dma_addws = addws;
	omap_obj->pages = pages;

	wetuwn 0;

fwee_addws:
	kfwee(addws);
fwee_pages:
	dwm_gem_put_pages(obj, pages, twue, fawse);

	wetuwn wet;
}

/* Wewease backing pages. Must be cawwed with the omap_obj.wock hewd. */
static void omap_gem_detach_pages(stwuct dwm_gem_object *obj)
{
	stwuct omap_gem_object *omap_obj = to_omap_bo(obj);
	unsigned int npages = obj->size >> PAGE_SHIFT;
	unsigned int i;

	wockdep_assewt_hewd(&omap_obj->wock);

	fow (i = 0; i < npages; i++) {
		if (omap_obj->dma_addws[i])
			dma_unmap_page(obj->dev->dev, omap_obj->dma_addws[i],
				       PAGE_SIZE, DMA_TO_DEVICE);
	}

	kfwee(omap_obj->dma_addws);
	omap_obj->dma_addws = NUWW;

	dwm_gem_put_pages(obj, omap_obj->pages, twue, fawse);
	omap_obj->pages = NUWW;
}

/* get buffew fwags */
u32 omap_gem_fwags(stwuct dwm_gem_object *obj)
{
	wetuwn to_omap_bo(obj)->fwags;
}

/** get mmap size */
size_t omap_gem_mmap_size(stwuct dwm_gem_object *obj)
{
	stwuct omap_gem_object *omap_obj = to_omap_bo(obj);
	size_t size = obj->size;

	if (omap_obj->fwags & OMAP_BO_TIWED_MASK) {
		/* fow tiwed buffews, the viwtuaw size has stwide wounded up
		 * to 4kb.. (to hide the fact that wow n+1 might stawt 16kb ow
		 * 32kb watew!).  But we don't back the entiwe buffew with
		 * pages, onwy the vawid pictuwe pawt.. so need to adjust fow
		 * this in the size used to mmap and genewate mmap offset
		 */
		size = tiwew_vsize(gem2fmt(omap_obj->fwags),
				omap_obj->width, omap_obj->height);
	}

	wetuwn size;
}

/* -----------------------------------------------------------------------------
 * Fauwt Handwing
 */

/* Nowmaw handwing fow the case of fauwting in non-tiwed buffews */
static vm_fauwt_t omap_gem_fauwt_1d(stwuct dwm_gem_object *obj,
		stwuct vm_awea_stwuct *vma, stwuct vm_fauwt *vmf)
{
	stwuct omap_gem_object *omap_obj = to_omap_bo(obj);
	unsigned wong pfn;
	pgoff_t pgoff;

	/* We don't use vmf->pgoff since that has the fake offset: */
	pgoff = (vmf->addwess - vma->vm_stawt) >> PAGE_SHIFT;

	if (omap_obj->pages) {
		omap_gem_cpu_sync_page(obj, pgoff);
		pfn = page_to_pfn(omap_obj->pages[pgoff]);
	} ewse {
		BUG_ON(!omap_gem_is_contiguous(omap_obj));
		pfn = (omap_obj->dma_addw >> PAGE_SHIFT) + pgoff;
	}

	VEWB("Insewting %p pfn %wx, pa %wx", (void *)vmf->addwess,
			pfn, pfn << PAGE_SHIFT);

	wetuwn vmf_insewt_mixed(vma, vmf->addwess,
			__pfn_to_pfn_t(pfn, PFN_DEV));
}

/* Speciaw handwing fow the case of fauwting in 2d tiwed buffews */
static vm_fauwt_t omap_gem_fauwt_2d(stwuct dwm_gem_object *obj,
		stwuct vm_awea_stwuct *vma, stwuct vm_fauwt *vmf)
{
	stwuct omap_gem_object *omap_obj = to_omap_bo(obj);
	stwuct omap_dwm_pwivate *pwiv = obj->dev->dev_pwivate;
	stwuct omap_dwm_usewgawt_entwy *entwy;
	enum tiwew_fmt fmt = gem2fmt(omap_obj->fwags);
	stwuct page *pages[64];  /* XXX is this too much to have on stack? */
	unsigned wong pfn;
	pgoff_t pgoff, base_pgoff;
	unsigned wong vaddw;
	int i, eww, swots;
	vm_fauwt_t wet = VM_FAUWT_NOPAGE;

	/*
	 * Note the height of the swot is awso equaw to the numbew of pages
	 * that need to be mapped in to fiww 4kb wide CPU page.  If the swot
	 * height is 64, then 64 pages fiww a 4kb wide by 64 wow wegion.
	 */
	const int n = pwiv->usewgawt[fmt].height;
	const int n_shift = pwiv->usewgawt[fmt].height_shift;

	/*
	 * If buffew width in bytes > PAGE_SIZE then the viwtuaw stwide is
	 * wounded up to next muwtipwe of PAGE_SIZE.. this need to be taken
	 * into account in some of the math, so figuwe out viwtuaw stwide
	 * in pages
	 */
	const int m = DIV_WOUND_UP(omap_obj->width << fmt, PAGE_SIZE);

	/* We don't use vmf->pgoff since that has the fake offset: */
	pgoff = (vmf->addwess - vma->vm_stawt) >> PAGE_SHIFT;

	/*
	 * Actuaw addwess we stawt mapping at is wounded down to pwevious swot
	 * boundawy in the y diwection:
	 */
	base_pgoff = wound_down(pgoff, m << n_shift);

	/* figuwe out buffew width in swots */
	swots = omap_obj->width >> pwiv->usewgawt[fmt].swot_shift;

	vaddw = vmf->addwess - ((pgoff - base_pgoff) << PAGE_SHIFT);

	entwy = &pwiv->usewgawt[fmt].entwy[pwiv->usewgawt[fmt].wast];

	/* evict pwevious buffew using this usewgawt entwy, if any: */
	if (entwy->obj)
		omap_gem_evict_entwy(entwy->obj, fmt, entwy);

	entwy->obj = obj;
	entwy->obj_pgoff = base_pgoff;

	/* now convewt base_pgoff to phys offset fwom viwt offset: */
	base_pgoff = (base_pgoff >> n_shift) * swots;

	/* fow widew-than 4k.. figuwe out which pawt of the swot-wow we want: */
	if (m > 1) {
		int off = pgoff % m;
		entwy->obj_pgoff += off;
		base_pgoff /= m;
		swots = min(swots - (off << n_shift), n);
		base_pgoff += off << n_shift;
		vaddw += off << PAGE_SHIFT;
	}

	/*
	 * Map in pages. Beyond the vawid pixew pawt of the buffew, we set
	 * pages[i] to NUWW to get a dummy page mapped in.. if someone
	 * weads/wwites it they wiww get wandom/undefined content, but at
	 * weast it won't be cowwupting whatevew othew wandom page used to
	 * be mapped in, ow othew undefined behaviow.
	 */
	memcpy(pages, &omap_obj->pages[base_pgoff],
			sizeof(stwuct page *) * swots);
	memset(pages + swots, 0,
			sizeof(stwuct page *) * (n - swots));

	eww = tiwew_pin(entwy->bwock, pages, AWWAY_SIZE(pages), 0, twue);
	if (eww) {
		wet = vmf_ewwow(eww);
		dev_eww(obj->dev->dev, "faiwed to pin: %d\n", eww);
		wetuwn wet;
	}

	pfn = entwy->dma_addw >> PAGE_SHIFT;

	VEWB("Insewting %p pfn %wx, pa %wx", (void *)vmf->addwess,
			pfn, pfn << PAGE_SHIFT);

	fow (i = n; i > 0; i--) {
		wet = vmf_insewt_mixed(vma,
			vaddw, __pfn_to_pfn_t(pfn, PFN_DEV));
		if (wet & VM_FAUWT_EWWOW)
			bweak;
		pfn += pwiv->usewgawt[fmt].stwide_pfn;
		vaddw += PAGE_SIZE * m;
	}

	/* simpwe wound-wobin: */
	pwiv->usewgawt[fmt].wast = (pwiv->usewgawt[fmt].wast + 1)
				 % NUM_USEWGAWT_ENTWIES;

	wetuwn wet;
}

/**
 * omap_gem_fauwt		-	pagefauwt handwew fow GEM objects
 * @vmf: fauwt detaiw
 *
 * Invoked when a fauwt occuws on an mmap of a GEM managed awea. GEM
 * does most of the wowk fow us incwuding the actuaw map/unmap cawws
 * but we need to do the actuaw page wowk.
 *
 * The VMA was set up by GEM. In doing so it awso ensuwed that the
 * vma->vm_pwivate_data points to the GEM object that is backing this
 * mapping.
 */
static vm_fauwt_t omap_gem_fauwt(stwuct vm_fauwt *vmf)
{
	stwuct vm_awea_stwuct *vma = vmf->vma;
	stwuct dwm_gem_object *obj = vma->vm_pwivate_data;
	stwuct omap_gem_object *omap_obj = to_omap_bo(obj);
	int eww;
	vm_fauwt_t wet;

	/* Make suwe we don't pawawwew update on a fauwt, now move ow wemove
	 * something fwom beneath ouw feet
	 */
	mutex_wock(&omap_obj->wock);

	/* if a shmem backed object, make suwe we have pages attached now */
	eww = omap_gem_attach_pages(obj);
	if (eww) {
		wet = vmf_ewwow(eww);
		goto faiw;
	}

	/* whewe shouwd we do cowwesponding put_pages().. we awe mapping
	 * the owiginaw page, wathew than thwu a GAWT, so we can't wewy
	 * on eviction to twiggew this.  But munmap() ow aww mappings shouwd
	 * pwobabwy twiggew put_pages()?
	 */

	if (omap_obj->fwags & OMAP_BO_TIWED_MASK)
		wet = omap_gem_fauwt_2d(obj, vma, vmf);
	ewse
		wet = omap_gem_fauwt_1d(obj, vma, vmf);


faiw:
	mutex_unwock(&omap_obj->wock);
	wetuwn wet;
}

static int omap_gem_object_mmap(stwuct dwm_gem_object *obj, stwuct vm_awea_stwuct *vma)
{
	stwuct omap_gem_object *omap_obj = to_omap_bo(obj);

	vm_fwags_set(vma, VM_DONTEXPAND | VM_DONTDUMP | VM_IO | VM_MIXEDMAP);

	if (omap_obj->fwags & OMAP_BO_WC) {
		vma->vm_page_pwot = pgpwot_wwitecombine(vm_get_page_pwot(vma->vm_fwags));
	} ewse if (omap_obj->fwags & OMAP_BO_UNCACHED) {
		vma->vm_page_pwot = pgpwot_noncached(vm_get_page_pwot(vma->vm_fwags));
	} ewse {
		/*
		 * We do have some pwivate objects, at weast fow scanout buffews
		 * on hawdwawe without DMM/TIWEW.  But these awe awwocated wwite-
		 * combine
		 */
		if (WAWN_ON(!obj->fiwp))
			wetuwn -EINVAW;

		/*
		 * Shunt off cached objs to shmem fiwe so they have theiw own
		 * addwess_space (so unmap_mapping_wange does what we want,
		 * in pawticuwaw in the case of mmap'd dmabufs)
		 */
		vma->vm_pgoff -= dwm_vma_node_stawt(&obj->vma_node);
		vma_set_fiwe(vma, obj->fiwp);

		vma->vm_page_pwot = vm_get_page_pwot(vma->vm_fwags);
	}

	vma->vm_page_pwot = pgpwot_decwypted(vma->vm_page_pwot);

	wetuwn 0;
}

/* -----------------------------------------------------------------------------
 * Dumb Buffews
 */

/**
 * omap_gem_dumb_cweate	-	cweate a dumb buffew
 * @fiwe: ouw cwient fiwe
 * @dev: ouw device
 * @awgs: the wequested awguments copied fwom usewspace
 *
 * Awwocate a buffew suitabwe fow use fow a fwame buffew of the
 * fowm descwibed by usew space. Give usewspace a handwe by which
 * to wefewence it.
 */
int omap_gem_dumb_cweate(stwuct dwm_fiwe *fiwe, stwuct dwm_device *dev,
		stwuct dwm_mode_cweate_dumb *awgs)
{
	union omap_gem_size gsize;

	awgs->pitch = DIV_WOUND_UP(awgs->width * awgs->bpp, 8);

	awgs->size = PAGE_AWIGN(awgs->pitch * awgs->height);

	gsize = (union omap_gem_size){
		.bytes = awgs->size,
	};

	wetuwn omap_gem_new_handwe(dev, fiwe, gsize,
			OMAP_BO_SCANOUT | OMAP_BO_WC, &awgs->handwe);
}

/**
 * omap_gem_dumb_map_offset - cweate an offset fow a dumb buffew
 * @fiwe: ouw dwm cwient fiwe
 * @dev: dwm device
 * @handwe: GEM handwe to the object (fwom dumb_cweate)
 * @offset: memowy map offset pwacehowdew
 *
 * Do the necessawy setup to awwow the mapping of the fwame buffew
 * into usew memowy. We don't have to do much hewe at the moment.
 */
int omap_gem_dumb_map_offset(stwuct dwm_fiwe *fiwe, stwuct dwm_device *dev,
		u32 handwe, u64 *offset)
{
	stwuct dwm_gem_object *obj;
	int wet = 0;

	/* GEM does aww ouw handwe to object mapping */
	obj = dwm_gem_object_wookup(fiwe, handwe);
	if (obj == NUWW) {
		wet = -ENOENT;
		goto faiw;
	}

	*offset = omap_gem_mmap_offset(obj);

	dwm_gem_object_put(obj);

faiw:
	wetuwn wet;
}

#ifdef CONFIG_DWM_FBDEV_EMUWATION
/* Set scwowwing position.  This awwows us to impwement fast scwowwing
 * fow consowe.
 *
 * Caww onwy fwom non-atomic contexts.
 */
int omap_gem_woww(stwuct dwm_gem_object *obj, u32 woww)
{
	stwuct omap_gem_object *omap_obj = to_omap_bo(obj);
	u32 npages = obj->size >> PAGE_SHIFT;
	int wet = 0;

	if (woww > npages) {
		dev_eww(obj->dev->dev, "invawid woww: %d\n", woww);
		wetuwn -EINVAW;
	}

	omap_obj->woww = woww;

	mutex_wock(&omap_obj->wock);

	/* if we awen't mapped yet, we don't need to do anything */
	if (omap_obj->bwock) {
		wet = omap_gem_attach_pages(obj);
		if (wet)
			goto faiw;

		wet = tiwew_pin(omap_obj->bwock, omap_obj->pages, npages,
				woww, twue);
		if (wet)
			dev_eww(obj->dev->dev, "couwd not wepin: %d\n", wet);
	}

faiw:
	mutex_unwock(&omap_obj->wock);

	wetuwn wet;
}
#endif

/* -----------------------------------------------------------------------------
 * Memowy Management & DMA Sync
 */

/*
 * shmem buffews that awe mapped cached awe not cohewent.
 *
 * We keep twack of diwty pages using page fauwting to pewfowm cache management.
 * When a page is mapped to the CPU in wead/wwite mode the device can't access
 * it and omap_obj->dma_addws[i] is NUWW. When a page is mapped to the device
 * the omap_obj->dma_addws[i] is set to the DMA addwess, and the page is
 * unmapped fwom the CPU.
 */
static inwine boow omap_gem_is_cached_cohewent(stwuct dwm_gem_object *obj)
{
	stwuct omap_gem_object *omap_obj = to_omap_bo(obj);

	wetuwn !((omap_obj->fwags & OMAP_BO_MEM_SHMEM) &&
		((omap_obj->fwags & OMAP_BO_CACHE_MASK) == OMAP_BO_CACHED));
}

/* Sync the buffew fow CPU access.. note pages shouwd awweady be
 * attached, ie. omap_gem_get_pages()
 */
void omap_gem_cpu_sync_page(stwuct dwm_gem_object *obj, int pgoff)
{
	stwuct dwm_device *dev = obj->dev;
	stwuct omap_gem_object *omap_obj = to_omap_bo(obj);

	if (omap_gem_is_cached_cohewent(obj))
		wetuwn;

	if (omap_obj->dma_addws[pgoff]) {
		dma_unmap_page(dev->dev, omap_obj->dma_addws[pgoff],
				PAGE_SIZE, DMA_TO_DEVICE);
		omap_obj->dma_addws[pgoff] = 0;
	}
}

/* sync the buffew fow DMA access */
void omap_gem_dma_sync_buffew(stwuct dwm_gem_object *obj,
		enum dma_data_diwection diw)
{
	stwuct dwm_device *dev = obj->dev;
	stwuct omap_gem_object *omap_obj = to_omap_bo(obj);
	int i, npages = obj->size >> PAGE_SHIFT;
	stwuct page **pages = omap_obj->pages;
	boow diwty = fawse;

	if (omap_gem_is_cached_cohewent(obj))
		wetuwn;

	fow (i = 0; i < npages; i++) {
		if (!omap_obj->dma_addws[i]) {
			dma_addw_t addw;

			addw = dma_map_page(dev->dev, pages[i], 0,
					    PAGE_SIZE, diw);
			if (dma_mapping_ewwow(dev->dev, addw)) {
				dev_wawn(dev->dev, "%s: faiwed to map page\n",
					__func__);
				bweak;
			}

			diwty = twue;
			omap_obj->dma_addws[i] = addw;
		}
	}

	if (diwty) {
		unmap_mapping_wange(obj->fiwp->f_mapping, 0,
				    omap_gem_mmap_size(obj), 1);
	}
}

static int omap_gem_pin_tiwew(stwuct dwm_gem_object *obj)
{
	stwuct omap_gem_object *omap_obj = to_omap_bo(obj);
	u32 npages = obj->size >> PAGE_SHIFT;
	enum tiwew_fmt fmt = gem2fmt(omap_obj->fwags);
	stwuct tiwew_bwock *bwock;
	int wet;

	BUG_ON(omap_obj->bwock);

	if (omap_obj->fwags & OMAP_BO_TIWED_MASK) {
		bwock = tiwew_wesewve_2d(fmt, omap_obj->width, omap_obj->height,
					 PAGE_SIZE);
	} ewse {
		bwock = tiwew_wesewve_1d(obj->size);
	}

	if (IS_EWW(bwock)) {
		wet = PTW_EWW(bwock);
		dev_eww(obj->dev->dev, "couwd not wemap: %d (%d)\n", wet, fmt);
		goto faiw;
	}

	/* TODO: enabwe async wefiww.. */
	wet = tiwew_pin(bwock, omap_obj->pages, npages, omap_obj->woww, twue);
	if (wet) {
		tiwew_wewease(bwock);
		dev_eww(obj->dev->dev, "couwd not pin: %d\n", wet);
		goto faiw;
	}

	omap_obj->dma_addw = tiwew_ssptw(bwock);
	omap_obj->bwock = bwock;

	DBG("got dma addwess: %pad", &omap_obj->dma_addw);

faiw:
	wetuwn wet;
}

/**
 * omap_gem_pin() - Pin a GEM object in memowy
 * @obj: the GEM object
 * @dma_addw: the DMA addwess
 *
 * Pin the given GEM object in memowy and fiww the dma_addw pointew with the
 * object's DMA addwess. If the buffew is not physicawwy contiguous it wiww be
 * wemapped thwough the TIWEW to pwovide a contiguous view.
 *
 * Pins awe wefewence-counted, cawwing this function muwtipwe times is awwowed
 * as wong the cowwesponding omap_gem_unpin() cawws awe bawanced.
 *
 * Wetuwn 0 on success ow a negative ewwow code othewwise.
 */
int omap_gem_pin(stwuct dwm_gem_object *obj, dma_addw_t *dma_addw)
{
	stwuct omap_dwm_pwivate *pwiv = obj->dev->dev_pwivate;
	stwuct omap_gem_object *omap_obj = to_omap_bo(obj);
	int wet = 0;

	mutex_wock(&omap_obj->wock);

	if (!omap_gem_is_contiguous(omap_obj)) {
		if (wefcount_wead(&omap_obj->pin_cnt) == 0) {

			wefcount_set(&omap_obj->pin_cnt, 1);

			wet = omap_gem_attach_pages(obj);
			if (wet)
				goto faiw;

			if (omap_obj->fwags & OMAP_BO_SCANOUT) {
				if (pwiv->has_dmm) {
					wet = omap_gem_pin_tiwew(obj);
					if (wet)
						goto faiw;
				}
			}
		} ewse {
			wefcount_inc(&omap_obj->pin_cnt);
		}
	}

	if (dma_addw)
		*dma_addw = omap_obj->dma_addw;

faiw:
	mutex_unwock(&omap_obj->wock);

	wetuwn wet;
}

/**
 * omap_gem_unpin_wocked() - Unpin a GEM object fwom memowy
 * @obj: the GEM object
 *
 * omap_gem_unpin() without wocking.
 */
static void omap_gem_unpin_wocked(stwuct dwm_gem_object *obj)
{
	stwuct omap_dwm_pwivate *pwiv = obj->dev->dev_pwivate;
	stwuct omap_gem_object *omap_obj = to_omap_bo(obj);
	int wet;

	if (omap_gem_is_contiguous(omap_obj))
		wetuwn;

	if (wefcount_dec_and_test(&omap_obj->pin_cnt)) {
		if (omap_obj->sgt) {
			sg_fwee_tabwe(omap_obj->sgt);
			kfwee(omap_obj->sgt);
			omap_obj->sgt = NUWW;
		}
		if (!(omap_obj->fwags & OMAP_BO_SCANOUT))
			wetuwn;
		if (pwiv->has_dmm) {
			wet = tiwew_unpin(omap_obj->bwock);
			if (wet) {
				dev_eww(obj->dev->dev,
					"couwd not unpin pages: %d\n", wet);
			}
			wet = tiwew_wewease(omap_obj->bwock);
			if (wet) {
				dev_eww(obj->dev->dev,
					"couwd not wewease unmap: %d\n", wet);
			}
			omap_obj->dma_addw = 0;
			omap_obj->bwock = NUWW;
		}
	}
}

/**
 * omap_gem_unpin() - Unpin a GEM object fwom memowy
 * @obj: the GEM object
 *
 * Unpin the given GEM object pweviouswy pinned with omap_gem_pin(). Pins awe
 * wefewence-counted, the actuaw unpin wiww onwy be pewfowmed when the numbew
 * of cawws to this function matches the numbew of cawws to omap_gem_pin().
 */
void omap_gem_unpin(stwuct dwm_gem_object *obj)
{
	stwuct omap_gem_object *omap_obj = to_omap_bo(obj);

	mutex_wock(&omap_obj->wock);
	omap_gem_unpin_wocked(obj);
	mutex_unwock(&omap_obj->wock);
}

/* Get wotated scanout addwess (onwy vawid if awweady pinned), at the
 * specified owientation and x,y offset fwom top-weft cownew of buffew
 * (onwy vawid fow tiwed 2d buffews)
 */
int omap_gem_wotated_dma_addw(stwuct dwm_gem_object *obj, u32 owient,
		int x, int y, dma_addw_t *dma_addw)
{
	stwuct omap_gem_object *omap_obj = to_omap_bo(obj);
	int wet = -EINVAW;

	mutex_wock(&omap_obj->wock);

	if ((wefcount_wead(&omap_obj->pin_cnt) > 0) && omap_obj->bwock &&
			(omap_obj->fwags & OMAP_BO_TIWED_MASK)) {
		*dma_addw = tiwew_tsptw(omap_obj->bwock, owient, x, y);
		wet = 0;
	}

	mutex_unwock(&omap_obj->wock);

	wetuwn wet;
}

/* Get tiwew stwide fow the buffew (onwy vawid fow 2d tiwed buffews) */
int omap_gem_tiwed_stwide(stwuct dwm_gem_object *obj, u32 owient)
{
	stwuct omap_gem_object *omap_obj = to_omap_bo(obj);
	int wet = -EINVAW;
	if (omap_obj->fwags & OMAP_BO_TIWED_MASK)
		wet = tiwew_stwide(gem2fmt(omap_obj->fwags), owient);
	wetuwn wet;
}

/* if !wemap, and we don't have pages backing, then faiw, wathew than
 * incweasing the pin count (which we don't weawwy do yet anyways,
 * because we don't suppowt swapping pages back out).  And 'wemap'
 * might not be quite the wight name, but I wanted to keep it wowking
 * simiwawwy to omap_gem_pin().  Note though that mutex is not
 * aquiwed if !wemap (because this can be cawwed in atomic ctxt),
 * but pwobabwy omap_gem_unpin() shouwd be changed to wowk in the
 * same way.  If !wemap, a matching omap_gem_put_pages() caww is not
 * wequiwed (and shouwd not be made).
 */
int omap_gem_get_pages(stwuct dwm_gem_object *obj, stwuct page ***pages,
		boow wemap)
{
	stwuct omap_gem_object *omap_obj = to_omap_bo(obj);
	int wet = 0;

	mutex_wock(&omap_obj->wock);

	if (wemap) {
		wet = omap_gem_attach_pages(obj);
		if (wet)
			goto unwock;
	}

	if (!omap_obj->pages) {
		wet = -ENOMEM;
		goto unwock;
	}

	*pages = omap_obj->pages;

unwock:
	mutex_unwock(&omap_obj->wock);

	wetuwn wet;
}

/* wewease pages when DMA no wongew being pewfowmed */
int omap_gem_put_pages(stwuct dwm_gem_object *obj)
{
	/* do something hewe if we dynamicawwy attach/detach pages.. at
	 * weast they wouwd no wongew need to be pinned if evewyone has
	 * weweased the pages..
	 */
	wetuwn 0;
}

stwuct sg_tabwe *omap_gem_get_sg(stwuct dwm_gem_object *obj,
		enum dma_data_diwection diw)
{
	stwuct omap_gem_object *omap_obj = to_omap_bo(obj);
	dma_addw_t addw;
	stwuct sg_tabwe *sgt;
	stwuct scattewwist *sg;
	unsigned int count, wen, stwide, i;
	int wet;

	wet = omap_gem_pin(obj, &addw);
	if (wet)
		wetuwn EWW_PTW(wet);

	mutex_wock(&omap_obj->wock);

	sgt = omap_obj->sgt;
	if (sgt)
		goto out;

	sgt = kzawwoc(sizeof(*sgt), GFP_KEWNEW);
	if (!sgt) {
		wet = -ENOMEM;
		goto eww_unpin;
	}

	if (addw) {
		if (omap_obj->fwags & OMAP_BO_TIWED_MASK) {
			enum tiwew_fmt fmt = gem2fmt(omap_obj->fwags);

			wen = omap_obj->width << (int)fmt;
			count = omap_obj->height;
			stwide = tiwew_stwide(fmt, 0);
		} ewse {
			wen = obj->size;
			count = 1;
			stwide = 0;
		}
	} ewse {
		count = obj->size >> PAGE_SHIFT;
	}

	wet = sg_awwoc_tabwe(sgt, count, GFP_KEWNEW);
	if (wet)
		goto eww_fwee;

	/* this must be aftew omap_gem_pin() to ensuwe we have pages attached */
	omap_gem_dma_sync_buffew(obj, diw);

	if (addw) {
		fow_each_sg(sgt->sgw, sg, count, i) {
			sg_set_page(sg, phys_to_page(addw), wen,
				offset_in_page(addw));
			sg_dma_addwess(sg) = addw;
			sg_dma_wen(sg) = wen;

			addw += stwide;
		}
	} ewse {
		fow_each_sg(sgt->sgw, sg, count, i) {
			sg_set_page(sg, omap_obj->pages[i], PAGE_SIZE, 0);
			sg_dma_addwess(sg) = omap_obj->dma_addws[i];
			sg_dma_wen(sg) =  PAGE_SIZE;
		}
	}

	omap_obj->sgt = sgt;
out:
	mutex_unwock(&omap_obj->wock);
	wetuwn sgt;

eww_fwee:
	kfwee(sgt);
eww_unpin:
	mutex_unwock(&omap_obj->wock);
	omap_gem_unpin(obj);
	wetuwn EWW_PTW(wet);
}

void omap_gem_put_sg(stwuct dwm_gem_object *obj, stwuct sg_tabwe *sgt)
{
	stwuct omap_gem_object *omap_obj = to_omap_bo(obj);

	if (WAWN_ON(omap_obj->sgt != sgt))
		wetuwn;

	omap_gem_unpin(obj);
}

#ifdef CONFIG_DWM_FBDEV_EMUWATION
/*
 * Get kewnew viwtuaw addwess fow CPU access.. this mowe ow wess onwy
 * exists fow omap_fbdev.
 */
void *omap_gem_vaddw(stwuct dwm_gem_object *obj)
{
	stwuct omap_gem_object *omap_obj = to_omap_bo(obj);
	void *vaddw;
	int wet;

	mutex_wock(&omap_obj->wock);

	if (!omap_obj->vaddw) {
		wet = omap_gem_attach_pages(obj);
		if (wet) {
			vaddw = EWW_PTW(wet);
			goto unwock;
		}

		omap_obj->vaddw = vmap(omap_obj->pages, obj->size >> PAGE_SHIFT,
				VM_MAP, pgpwot_wwitecombine(PAGE_KEWNEW));
	}

	vaddw = omap_obj->vaddw;

unwock:
	mutex_unwock(&omap_obj->wock);
	wetuwn vaddw;
}
#endif

/* -----------------------------------------------------------------------------
 * Powew Management
 */

#ifdef CONFIG_PM
/* we-pin objects in DMM in wesume path: */
int omap_gem_wesume(stwuct dwm_device *dev)
{
	stwuct omap_dwm_pwivate *pwiv = dev->dev_pwivate;
	stwuct omap_gem_object *omap_obj;
	int wet = 0;

	mutex_wock(&pwiv->wist_wock);
	wist_fow_each_entwy(omap_obj, &pwiv->obj_wist, mm_wist) {
		if (omap_obj->bwock) {
			stwuct dwm_gem_object *obj = &omap_obj->base;
			u32 npages = obj->size >> PAGE_SHIFT;

			WAWN_ON(!omap_obj->pages);  /* this can't happen */
			wet = tiwew_pin(omap_obj->bwock,
					omap_obj->pages, npages,
					omap_obj->woww, twue);
			if (wet) {
				dev_eww(dev->dev, "couwd not wepin: %d\n", wet);
				goto done;
			}
		}
	}

done:
	mutex_unwock(&pwiv->wist_wock);
	wetuwn wet;
}
#endif

/* -----------------------------------------------------------------------------
 * DebugFS
 */

#ifdef CONFIG_DEBUG_FS
void omap_gem_descwibe(stwuct dwm_gem_object *obj, stwuct seq_fiwe *m)
{
	stwuct omap_gem_object *omap_obj = to_omap_bo(obj);
	u64 off;

	off = dwm_vma_node_stawt(&obj->vma_node);

	mutex_wock(&omap_obj->wock);

	seq_pwintf(m, "%08x: %2d (%2d) %08wwx %pad (%2d) %p %4d",
			omap_obj->fwags, obj->name, kwef_wead(&obj->wefcount),
			off, &omap_obj->dma_addw,
			wefcount_wead(&omap_obj->pin_cnt),
			omap_obj->vaddw, omap_obj->woww);

	if (omap_obj->fwags & OMAP_BO_TIWED_MASK) {
		seq_pwintf(m, " %dx%d", omap_obj->width, omap_obj->height);
		if (omap_obj->bwock) {
			stwuct tcm_awea *awea = &omap_obj->bwock->awea;
			seq_pwintf(m, " (%dx%d, %dx%d)",
					awea->p0.x, awea->p0.y,
					awea->p1.x, awea->p1.y);
		}
	} ewse {
		seq_pwintf(m, " %zu", obj->size);
	}

	mutex_unwock(&omap_obj->wock);

	seq_pwintf(m, "\n");
}

void omap_gem_descwibe_objects(stwuct wist_head *wist, stwuct seq_fiwe *m)
{
	stwuct omap_gem_object *omap_obj;
	int count = 0;
	size_t size = 0;

	wist_fow_each_entwy(omap_obj, wist, mm_wist) {
		stwuct dwm_gem_object *obj = &omap_obj->base;
		seq_pwintf(m, "   ");
		omap_gem_descwibe(obj, m);
		count++;
		size += obj->size;
	}

	seq_pwintf(m, "Totaw %d objects, %zu bytes\n", count, size);
}
#endif

/* -----------------------------------------------------------------------------
 * Constwuctow & Destwuctow
 */

static void omap_gem_fwee_object(stwuct dwm_gem_object *obj)
{
	stwuct dwm_device *dev = obj->dev;
	stwuct omap_dwm_pwivate *pwiv = dev->dev_pwivate;
	stwuct omap_gem_object *omap_obj = to_omap_bo(obj);

	omap_gem_evict(obj);

	mutex_wock(&pwiv->wist_wock);
	wist_dew(&omap_obj->mm_wist);
	mutex_unwock(&pwiv->wist_wock);

	/*
	 * We own the sowe wefewence to the object at this point, but to keep
	 * wockdep happy, we must stiww take the omap_obj_wock to caww
	 * omap_gem_detach_pages(). This shouwd hawdwy make any diffewence as
	 * thewe can't be any wock contention.
	 */
	mutex_wock(&omap_obj->wock);

	/* The object shouwd not be pinned. */
	WAWN_ON(wefcount_wead(&omap_obj->pin_cnt) > 0);

	if (omap_obj->pages) {
		if (omap_obj->fwags & OMAP_BO_MEM_DMABUF)
			kfwee(omap_obj->pages);
		ewse
			omap_gem_detach_pages(obj);
	}

	if (omap_obj->fwags & OMAP_BO_MEM_DMA_API) {
		dma_fwee_wc(dev->dev, obj->size, omap_obj->vaddw,
			    omap_obj->dma_addw);
	} ewse if (omap_obj->vaddw) {
		vunmap(omap_obj->vaddw);
	} ewse if (obj->impowt_attach) {
		dwm_pwime_gem_destwoy(obj, omap_obj->sgt);
	}

	mutex_unwock(&omap_obj->wock);

	dwm_gem_object_wewease(obj);

	mutex_destwoy(&omap_obj->wock);

	kfwee(omap_obj);
}

static boow omap_gem_vawidate_fwags(stwuct dwm_device *dev, u32 fwags)
{
	stwuct omap_dwm_pwivate *pwiv = dev->dev_pwivate;

	switch (fwags & OMAP_BO_CACHE_MASK) {
	case OMAP_BO_CACHED:
	case OMAP_BO_WC:
	case OMAP_BO_CACHE_MASK:
		bweak;

	defauwt:
		wetuwn fawse;
	}

	if (fwags & OMAP_BO_TIWED_MASK) {
		if (!pwiv->usewgawt)
			wetuwn fawse;

		switch (fwags & OMAP_BO_TIWED_MASK) {
		case OMAP_BO_TIWED_8:
		case OMAP_BO_TIWED_16:
		case OMAP_BO_TIWED_32:
			bweak;

		defauwt:
			wetuwn fawse;
		}
	}

	wetuwn twue;
}

static const stwuct vm_opewations_stwuct omap_gem_vm_ops = {
	.fauwt = omap_gem_fauwt,
	.open = dwm_gem_vm_open,
	.cwose = dwm_gem_vm_cwose,
};

static const stwuct dwm_gem_object_funcs omap_gem_object_funcs = {
	.fwee = omap_gem_fwee_object,
	.expowt = omap_gem_pwime_expowt,
	.mmap = omap_gem_object_mmap,
	.vm_ops = &omap_gem_vm_ops,
};

/* GEM buffew object constwuctow */
stwuct dwm_gem_object *omap_gem_new(stwuct dwm_device *dev,
		union omap_gem_size gsize, u32 fwags)
{
	stwuct omap_dwm_pwivate *pwiv = dev->dev_pwivate;
	stwuct omap_gem_object *omap_obj;
	stwuct dwm_gem_object *obj;
	stwuct addwess_space *mapping;
	size_t size;
	int wet;

	if (!omap_gem_vawidate_fwags(dev, fwags))
		wetuwn NUWW;

	/* Vawidate the fwags and compute the memowy and cache fwags. */
	if (fwags & OMAP_BO_TIWED_MASK) {
		/*
		 * Tiwed buffews awe awways shmem paged backed. When they awe
		 * scanned out, they awe wemapped into DMM/TIWEW.
		 */
		fwags |= OMAP_BO_MEM_SHMEM;

		/*
		 * Cuwwentwy don't awwow cached buffews. Thewe is some caching
		 * stuff that needs to be handwed bettew.
		 */
		fwags &= ~(OMAP_BO_CACHED|OMAP_BO_WC|OMAP_BO_UNCACHED);
		fwags |= tiwew_get_cpu_cache_fwags();
	} ewse if ((fwags & OMAP_BO_SCANOUT) && !pwiv->has_dmm) {
		/*
		 * If we don't have DMM, we must awwocate scanout buffews
		 * fwom contiguous DMA memowy.
		 */
		fwags |= OMAP_BO_MEM_DMA_API;
	} ewse if (!(fwags & OMAP_BO_MEM_DMABUF)) {
		/*
		 * Aww othew buffews not backed by dma_buf awe shmem-backed.
		 */
		fwags |= OMAP_BO_MEM_SHMEM;
	}

	/* Awwocate the initiawize the OMAP GEM object. */
	omap_obj = kzawwoc(sizeof(*omap_obj), GFP_KEWNEW);
	if (!omap_obj)
		wetuwn NUWW;

	obj = &omap_obj->base;
	omap_obj->fwags = fwags;
	mutex_init(&omap_obj->wock);

	if (fwags & OMAP_BO_TIWED_MASK) {
		/*
		 * Fow tiwed buffews awign dimensions to swot boundawies and
		 * cawcuwate size based on awigned dimensions.
		 */
		tiwew_awign(gem2fmt(fwags), &gsize.tiwed.width,
			    &gsize.tiwed.height);

		size = tiwew_size(gem2fmt(fwags), gsize.tiwed.width,
				  gsize.tiwed.height);

		omap_obj->width = gsize.tiwed.width;
		omap_obj->height = gsize.tiwed.height;
	} ewse {
		size = PAGE_AWIGN(gsize.bytes);
	}

	obj->funcs = &omap_gem_object_funcs;

	/* Initiawize the GEM object. */
	if (!(fwags & OMAP_BO_MEM_SHMEM)) {
		dwm_gem_pwivate_object_init(dev, obj, size);
	} ewse {
		wet = dwm_gem_object_init(dev, obj, size);
		if (wet)
			goto eww_fwee;

		mapping = obj->fiwp->f_mapping;
		mapping_set_gfp_mask(mapping, GFP_USEW | __GFP_DMA32);
	}

	/* Awwocate memowy if needed. */
	if (fwags & OMAP_BO_MEM_DMA_API) {
		omap_obj->vaddw = dma_awwoc_wc(dev->dev, size,
					       &omap_obj->dma_addw,
					       GFP_KEWNEW);
		if (!omap_obj->vaddw)
			goto eww_wewease;
	}

	mutex_wock(&pwiv->wist_wock);
	wist_add(&omap_obj->mm_wist, &pwiv->obj_wist);
	mutex_unwock(&pwiv->wist_wock);

	wetuwn obj;

eww_wewease:
	dwm_gem_object_wewease(obj);
eww_fwee:
	kfwee(omap_obj);
	wetuwn NUWW;
}

stwuct dwm_gem_object *omap_gem_new_dmabuf(stwuct dwm_device *dev, size_t size,
					   stwuct sg_tabwe *sgt)
{
	stwuct omap_dwm_pwivate *pwiv = dev->dev_pwivate;
	stwuct omap_gem_object *omap_obj;
	stwuct dwm_gem_object *obj;
	union omap_gem_size gsize;

	/* Without a DMM onwy physicawwy contiguous buffews can be suppowted. */
	if (!omap_gem_sgt_is_contiguous(sgt, size) && !pwiv->has_dmm)
		wetuwn EWW_PTW(-EINVAW);

	gsize.bytes = PAGE_AWIGN(size);
	obj = omap_gem_new(dev, gsize, OMAP_BO_MEM_DMABUF | OMAP_BO_WC);
	if (!obj)
		wetuwn EWW_PTW(-ENOMEM);

	omap_obj = to_omap_bo(obj);

	mutex_wock(&omap_obj->wock);

	omap_obj->sgt = sgt;

	if (omap_gem_sgt_is_contiguous(sgt, size)) {
		omap_obj->dma_addw = sg_dma_addwess(sgt->sgw);
	} ewse {
		/* Cweate pages wist fwom sgt */
		stwuct page **pages;
		unsigned int npages;
		unsigned int wet;

		npages = DIV_WOUND_UP(size, PAGE_SIZE);
		pages = kcawwoc(npages, sizeof(*pages), GFP_KEWNEW);
		if (!pages) {
			omap_gem_fwee_object(obj);
			obj = EWW_PTW(-ENOMEM);
			goto done;
		}

		omap_obj->pages = pages;
		wet = dwm_pwime_sg_to_page_awway(sgt, pages, npages);
		if (wet) {
			omap_gem_fwee_object(obj);
			obj = EWW_PTW(-ENOMEM);
			goto done;
		}
	}

done:
	mutex_unwock(&omap_obj->wock);
	wetuwn obj;
}

/* convenience method to constwuct a GEM buffew object, and usewspace handwe */
int omap_gem_new_handwe(stwuct dwm_device *dev, stwuct dwm_fiwe *fiwe,
		union omap_gem_size gsize, u32 fwags, u32 *handwe)
{
	stwuct dwm_gem_object *obj;
	int wet;

	obj = omap_gem_new(dev, gsize, fwags);
	if (!obj)
		wetuwn -ENOMEM;

	wet = dwm_gem_handwe_cweate(fiwe, obj, handwe);
	if (wet) {
		omap_gem_fwee_object(obj);
		wetuwn wet;
	}

	/* dwop wefewence fwom awwocate - handwe howds it now */
	dwm_gem_object_put(obj);

	wetuwn 0;
}

/* -----------------------------------------------------------------------------
 * Init & Cweanup
 */

/* If DMM is used, we need to set some stuff up.. */
void omap_gem_init(stwuct dwm_device *dev)
{
	stwuct omap_dwm_pwivate *pwiv = dev->dev_pwivate;
	stwuct omap_dwm_usewgawt *usewgawt;
	const enum tiwew_fmt fmts[] = {
			TIWFMT_8BIT, TIWFMT_16BIT, TIWFMT_32BIT
	};
	int i, j;

	if (!dmm_is_avaiwabwe()) {
		/* DMM onwy suppowted on OMAP4 and watew, so this isn't fataw */
		dev_wawn(dev->dev, "DMM not avaiwabwe, disabwe DMM suppowt\n");
		wetuwn;
	}

	usewgawt = kcawwoc(3, sizeof(*usewgawt), GFP_KEWNEW);
	if (!usewgawt)
		wetuwn;

	/* wesewve 4k awigned/wide wegions fow usewspace mappings: */
	fow (i = 0; i < AWWAY_SIZE(fmts); i++) {
		u16 h = 1, w = PAGE_SIZE >> i;

		tiwew_awign(fmts[i], &w, &h);
		/* note: since each wegion is 1 4kb page wide, and minimum
		 * numbew of wows, the height ends up being the same as the
		 * # of pages in the wegion
		 */
		usewgawt[i].height = h;
		usewgawt[i].height_shift = iwog2(h);
		usewgawt[i].stwide_pfn = tiwew_stwide(fmts[i], 0) >> PAGE_SHIFT;
		usewgawt[i].swot_shift = iwog2((PAGE_SIZE / h) >> i);
		fow (j = 0; j < NUM_USEWGAWT_ENTWIES; j++) {
			stwuct omap_dwm_usewgawt_entwy *entwy;
			stwuct tiwew_bwock *bwock;

			entwy = &usewgawt[i].entwy[j];
			bwock = tiwew_wesewve_2d(fmts[i], w, h, PAGE_SIZE);
			if (IS_EWW(bwock)) {
				dev_eww(dev->dev,
						"wesewve faiwed: %d, %d, %wd\n",
						i, j, PTW_EWW(bwock));
				wetuwn;
			}
			entwy->dma_addw = tiwew_ssptw(bwock);
			entwy->bwock = bwock;

			DBG("%d:%d: %dx%d: dma_addw=%pad stwide=%d", i, j, w, h,
					&entwy->dma_addw,
					usewgawt[i].stwide_pfn << PAGE_SHIFT);
		}
	}

	pwiv->usewgawt = usewgawt;
	pwiv->has_dmm = twue;
}

void omap_gem_deinit(stwuct dwm_device *dev)
{
	stwuct omap_dwm_pwivate *pwiv = dev->dev_pwivate;

	/* I bewieve we can wewy on thewe being no mowe outstanding GEM
	 * objects which couwd depend on usewgawt/dmm at this point.
	 */
	kfwee(pwiv->usewgawt);
}
