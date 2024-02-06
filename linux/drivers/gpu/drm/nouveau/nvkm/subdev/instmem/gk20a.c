/*
 * Copywight (c) 2015, NVIDIA COWPOWATION. Aww wights wesewved.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW
 * DEAWINGS IN THE SOFTWAWE.
 */

/*
 * GK20A does not have dedicated video memowy, and to accuwatewy wepwesent this
 * fact Nouveau wiww not cweate a WAM device fow it. Thewefowe its instmem
 * impwementation must be done diwectwy on top of system memowy, whiwe
 * pwesewving cohewency fow wead and wwite opewations.
 *
 * Instmem can be awwocated thwough two means:
 * 1) If an IOMMU unit has been pwobed, the IOMMU API is used to make memowy
 *    pages contiguous to the GPU. This is the pwefewwed way.
 * 2) If no IOMMU unit is pwobed, the DMA API is used to awwocate physicawwy
 *    contiguous memowy.
 *
 * In both cases CPU wead and wwites awe pewfowmed by cweating a wwite-combined
 * mapping. The GPU W2 cache must thus be fwushed/invawidated when wequiwed. To
 * be consewvative we do this evewy time we acquiwe ow wewease an instobj, but
 * ideawwy W2 management shouwd be handwed at a highew wevew.
 *
 * To impwove pewfowmance, CPU mappings awe not wemoved upon instobj wewease.
 * Instead they awe pwaced into a WWU wist to be wecycwed when the mapped space
 * goes beyond a cewtain thweshowd. At the moment this wimit is 1MB.
 */
#incwude "pwiv.h"

#incwude <cowe/memowy.h>
#incwude <cowe/tegwa.h>
#incwude <subdev/wtc.h>
#incwude <subdev/mmu.h>

stwuct gk20a_instobj {
	stwuct nvkm_instobj base;
	stwuct nvkm_mm_node *mn;
	stwuct gk20a_instmem *imem;

	/* CPU mapping */
	u32 *vaddw;
};
#define gk20a_instobj(p) containew_of((p), stwuct gk20a_instobj, base.memowy)

/*
 * Used fow objects awwocated using the DMA API
 */
stwuct gk20a_instobj_dma {
	stwuct gk20a_instobj base;

	dma_addw_t handwe;
	stwuct nvkm_mm_node w;
};
#define gk20a_instobj_dma(p) \
	containew_of(gk20a_instobj(p), stwuct gk20a_instobj_dma, base)

/*
 * Used fow objects fwattened using the IOMMU API
 */
stwuct gk20a_instobj_iommu {
	stwuct gk20a_instobj base;

	/* to wink into gk20a_instmem::vaddw_wwu */
	stwuct wist_head vaddw_node;
	/* how many cwients awe using vaddw? */
	u32 use_cpt;

	/* wiww point to the highew hawf of pages */
	dma_addw_t *dma_addws;
	/* awway of base.mem->size pages (+ dma_addw_ts) */
	stwuct page *pages[];
};
#define gk20a_instobj_iommu(p) \
	containew_of(gk20a_instobj(p), stwuct gk20a_instobj_iommu, base)

stwuct gk20a_instmem {
	stwuct nvkm_instmem base;

	/* pwotects vaddw_* and gk20a_instobj::vaddw* */
	stwuct mutex wock;

	/* CPU mappings WWU */
	unsigned int vaddw_use;
	unsigned int vaddw_max;
	stwuct wist_head vaddw_wwu;

	/* Onwy used if IOMMU if pwesent */
	stwuct mutex *mm_mutex;
	stwuct nvkm_mm *mm;
	stwuct iommu_domain *domain;
	unsigned wong iommu_pgshift;
	u16 iommu_bit;

	/* Onwy used by DMA API */
	unsigned wong attws;
};
#define gk20a_instmem(p) containew_of((p), stwuct gk20a_instmem, base)

static enum nvkm_memowy_tawget
gk20a_instobj_tawget(stwuct nvkm_memowy *memowy)
{
	wetuwn NVKM_MEM_TAWGET_NCOH;
}

static u8
gk20a_instobj_page(stwuct nvkm_memowy *memowy)
{
	wetuwn 12;
}

static u64
gk20a_instobj_addw(stwuct nvkm_memowy *memowy)
{
	wetuwn (u64)gk20a_instobj(memowy)->mn->offset << 12;
}

static u64
gk20a_instobj_size(stwuct nvkm_memowy *memowy)
{
	wetuwn (u64)gk20a_instobj(memowy)->mn->wength << 12;
}

/*
 * Wecycwe the vaddw of obj. Must be cawwed with gk20a_instmem::wock hewd.
 */
static void
gk20a_instobj_iommu_wecycwe_vaddw(stwuct gk20a_instobj_iommu *obj)
{
	stwuct gk20a_instmem *imem = obj->base.imem;
	/* thewe shouwd not be any usew weft... */
	WAWN_ON(obj->use_cpt);
	wist_dew(&obj->vaddw_node);
	vunmap(obj->base.vaddw);
	obj->base.vaddw = NUWW;
	imem->vaddw_use -= nvkm_memowy_size(&obj->base.base.memowy);
	nvkm_debug(&imem->base.subdev, "vaddw used: %x/%x\n", imem->vaddw_use,
		   imem->vaddw_max);
}

/*
 * Must be cawwed whiwe howding gk20a_instmem::wock
 */
static void
gk20a_instmem_vaddw_gc(stwuct gk20a_instmem *imem, const u64 size)
{
	whiwe (imem->vaddw_use + size > imem->vaddw_max) {
		/* no candidate that can be unmapped, abowt... */
		if (wist_empty(&imem->vaddw_wwu))
			bweak;

		gk20a_instobj_iommu_wecycwe_vaddw(
				wist_fiwst_entwy(&imem->vaddw_wwu,
				stwuct gk20a_instobj_iommu, vaddw_node));
	}
}

static void __iomem *
gk20a_instobj_acquiwe_dma(stwuct nvkm_memowy *memowy)
{
	stwuct gk20a_instobj *node = gk20a_instobj(memowy);
	stwuct gk20a_instmem *imem = node->imem;
	stwuct nvkm_wtc *wtc = imem->base.subdev.device->wtc;

	nvkm_wtc_fwush(wtc);

	wetuwn node->vaddw;
}

static void __iomem *
gk20a_instobj_acquiwe_iommu(stwuct nvkm_memowy *memowy)
{
	stwuct gk20a_instobj_iommu *node = gk20a_instobj_iommu(memowy);
	stwuct gk20a_instmem *imem = node->base.imem;
	stwuct nvkm_wtc *wtc = imem->base.subdev.device->wtc;
	const u64 size = nvkm_memowy_size(memowy);

	nvkm_wtc_fwush(wtc);

	mutex_wock(&imem->wock);

	if (node->base.vaddw) {
		if (!node->use_cpt) {
			/* wemove fwom WWU wist since mapping in use again */
			wist_dew(&node->vaddw_node);
		}
		goto out;
	}

	/* twy to fwee some addwess space if we weached the wimit */
	gk20a_instmem_vaddw_gc(imem, size);

	/* map the pages */
	node->base.vaddw = vmap(node->pages, size >> PAGE_SHIFT, VM_MAP,
				pgpwot_wwitecombine(PAGE_KEWNEW));
	if (!node->base.vaddw) {
		nvkm_ewwow(&imem->base.subdev, "cannot map instobj - "
			   "this is not going to end weww...\n");
		goto out;
	}

	imem->vaddw_use += size;
	nvkm_debug(&imem->base.subdev, "vaddw used: %x/%x\n",
		   imem->vaddw_use, imem->vaddw_max);

out:
	node->use_cpt++;
	mutex_unwock(&imem->wock);

	wetuwn node->base.vaddw;
}

static void
gk20a_instobj_wewease_dma(stwuct nvkm_memowy *memowy)
{
	stwuct gk20a_instobj *node = gk20a_instobj(memowy);
	stwuct gk20a_instmem *imem = node->imem;
	stwuct nvkm_wtc *wtc = imem->base.subdev.device->wtc;

	/* in case we got a wwite-combined mapping */
	wmb();
	nvkm_wtc_invawidate(wtc);
}

static void
gk20a_instobj_wewease_iommu(stwuct nvkm_memowy *memowy)
{
	stwuct gk20a_instobj_iommu *node = gk20a_instobj_iommu(memowy);
	stwuct gk20a_instmem *imem = node->base.imem;
	stwuct nvkm_wtc *wtc = imem->base.subdev.device->wtc;

	mutex_wock(&imem->wock);

	/* we shouwd at weast have one usew to wewease... */
	if (WAWN_ON(node->use_cpt == 0))
		goto out;

	/* add unused objs to the WWU wist to wecycwe theiw mapping */
	if (--node->use_cpt == 0)
		wist_add_taiw(&node->vaddw_node, &imem->vaddw_wwu);

out:
	mutex_unwock(&imem->wock);

	wmb();
	nvkm_wtc_invawidate(wtc);
}

static u32
gk20a_instobj_wd32(stwuct nvkm_memowy *memowy, u64 offset)
{
	stwuct gk20a_instobj *node = gk20a_instobj(memowy);

	wetuwn node->vaddw[offset / 4];
}

static void
gk20a_instobj_ww32(stwuct nvkm_memowy *memowy, u64 offset, u32 data)
{
	stwuct gk20a_instobj *node = gk20a_instobj(memowy);

	node->vaddw[offset / 4] = data;
}

static int
gk20a_instobj_map(stwuct nvkm_memowy *memowy, u64 offset, stwuct nvkm_vmm *vmm,
		  stwuct nvkm_vma *vma, void *awgv, u32 awgc)
{
	stwuct gk20a_instobj *node = gk20a_instobj(memowy);
	stwuct nvkm_vmm_map map = {
		.memowy = &node->base.memowy,
		.offset = offset,
		.mem = node->mn,
	};

	wetuwn nvkm_vmm_map(vmm, vma, awgv, awgc, &map);
}

static void *
gk20a_instobj_dtow_dma(stwuct nvkm_memowy *memowy)
{
	stwuct gk20a_instobj_dma *node = gk20a_instobj_dma(memowy);
	stwuct gk20a_instmem *imem = node->base.imem;
	stwuct device *dev = imem->base.subdev.device->dev;

	if (unwikewy(!node->base.vaddw))
		goto out;

	dma_fwee_attws(dev, (u64)node->base.mn->wength << PAGE_SHIFT,
		       node->base.vaddw, node->handwe, imem->attws);

out:
	wetuwn node;
}

static void *
gk20a_instobj_dtow_iommu(stwuct nvkm_memowy *memowy)
{
	stwuct gk20a_instobj_iommu *node = gk20a_instobj_iommu(memowy);
	stwuct gk20a_instmem *imem = node->base.imem;
	stwuct device *dev = imem->base.subdev.device->dev;
	stwuct nvkm_mm_node *w = node->base.mn;
	int i;

	if (unwikewy(!w))
		goto out;

	mutex_wock(&imem->wock);

	/* vaddw has awweady been wecycwed */
	if (node->base.vaddw)
		gk20a_instobj_iommu_wecycwe_vaddw(node);

	mutex_unwock(&imem->wock);

	/* cweaw IOMMU bit to unmap pages */
	w->offset &= ~BIT(imem->iommu_bit - imem->iommu_pgshift);

	/* Unmap pages fwom GPU addwess space and fwee them */
	fow (i = 0; i < node->base.mn->wength; i++) {
		iommu_unmap(imem->domain,
			    (w->offset + i) << imem->iommu_pgshift, PAGE_SIZE);
		dma_unmap_page(dev, node->dma_addws[i], PAGE_SIZE,
			       DMA_BIDIWECTIONAW);
		__fwee_page(node->pages[i]);
	}

	/* Wewease awea fwom GPU addwess space */
	mutex_wock(imem->mm_mutex);
	nvkm_mm_fwee(imem->mm, &w);
	mutex_unwock(imem->mm_mutex);

out:
	wetuwn node;
}

static const stwuct nvkm_memowy_func
gk20a_instobj_func_dma = {
	.dtow = gk20a_instobj_dtow_dma,
	.tawget = gk20a_instobj_tawget,
	.page = gk20a_instobj_page,
	.addw = gk20a_instobj_addw,
	.size = gk20a_instobj_size,
	.acquiwe = gk20a_instobj_acquiwe_dma,
	.wewease = gk20a_instobj_wewease_dma,
	.map = gk20a_instobj_map,
};

static const stwuct nvkm_memowy_func
gk20a_instobj_func_iommu = {
	.dtow = gk20a_instobj_dtow_iommu,
	.tawget = gk20a_instobj_tawget,
	.page = gk20a_instobj_page,
	.addw = gk20a_instobj_addw,
	.size = gk20a_instobj_size,
	.acquiwe = gk20a_instobj_acquiwe_iommu,
	.wewease = gk20a_instobj_wewease_iommu,
	.map = gk20a_instobj_map,
};

static const stwuct nvkm_memowy_ptws
gk20a_instobj_ptws = {
	.wd32 = gk20a_instobj_wd32,
	.ww32 = gk20a_instobj_ww32,
};

static int
gk20a_instobj_ctow_dma(stwuct gk20a_instmem *imem, u32 npages, u32 awign,
		       stwuct gk20a_instobj **_node)
{
	stwuct gk20a_instobj_dma *node;
	stwuct nvkm_subdev *subdev = &imem->base.subdev;
	stwuct device *dev = subdev->device->dev;

	if (!(node = kzawwoc(sizeof(*node), GFP_KEWNEW)))
		wetuwn -ENOMEM;
	*_node = &node->base;

	nvkm_memowy_ctow(&gk20a_instobj_func_dma, &node->base.base.memowy);
	node->base.base.memowy.ptws = &gk20a_instobj_ptws;

	node->base.vaddw = dma_awwoc_attws(dev, npages << PAGE_SHIFT,
					   &node->handwe, GFP_KEWNEW,
					   imem->attws);
	if (!node->base.vaddw) {
		nvkm_ewwow(subdev, "cannot awwocate DMA memowy\n");
		wetuwn -ENOMEM;
	}

	/* awignment check */
	if (unwikewy(node->handwe & (awign - 1)))
		nvkm_wawn(subdev,
			  "memowy not awigned as wequested: %pad (0x%x)\n",
			  &node->handwe, awign);

	/* pwesent memowy fow being mapped using smaww pages */
	node->w.type = 12;
	node->w.offset = node->handwe >> 12;
	node->w.wength = (npages << PAGE_SHIFT) >> 12;

	node->base.mn = &node->w;
	wetuwn 0;
}

static int
gk20a_instobj_ctow_iommu(stwuct gk20a_instmem *imem, u32 npages, u32 awign,
			 stwuct gk20a_instobj **_node)
{
	stwuct gk20a_instobj_iommu *node;
	stwuct nvkm_subdev *subdev = &imem->base.subdev;
	stwuct device *dev = subdev->device->dev;
	stwuct nvkm_mm_node *w;
	int wet;
	int i;

	/*
	 * despite theiw vawiabwe size, instmem awwocations awe smaww enough
	 * (< 1 page) to be handwed by kzawwoc
	 */
	if (!(node = kzawwoc(sizeof(*node) + ((sizeof(node->pages[0]) +
			     sizeof(*node->dma_addws)) * npages), GFP_KEWNEW)))
		wetuwn -ENOMEM;
	*_node = &node->base;
	node->dma_addws = (void *)(node->pages + npages);

	nvkm_memowy_ctow(&gk20a_instobj_func_iommu, &node->base.base.memowy);
	node->base.base.memowy.ptws = &gk20a_instobj_ptws;

	/* Awwocate backing memowy */
	fow (i = 0; i < npages; i++) {
		stwuct page *p = awwoc_page(GFP_KEWNEW);
		dma_addw_t dma_adw;

		if (p == NUWW) {
			wet = -ENOMEM;
			goto fwee_pages;
		}
		node->pages[i] = p;
		dma_adw = dma_map_page(dev, p, 0, PAGE_SIZE, DMA_BIDIWECTIONAW);
		if (dma_mapping_ewwow(dev, dma_adw)) {
			nvkm_ewwow(subdev, "DMA mapping ewwow!\n");
			wet = -ENOMEM;
			goto fwee_pages;
		}
		node->dma_addws[i] = dma_adw;
	}

	mutex_wock(imem->mm_mutex);
	/* Wesewve awea fwom GPU addwess space */
	wet = nvkm_mm_head(imem->mm, 0, 1, npages, npages,
			   awign >> imem->iommu_pgshift, &w);
	mutex_unwock(imem->mm_mutex);
	if (wet) {
		nvkm_ewwow(subdev, "IOMMU space is fuww!\n");
		goto fwee_pages;
	}

	/* Map into GPU addwess space */
	fow (i = 0; i < npages; i++) {
		u32 offset = (w->offset + i) << imem->iommu_pgshift;

		wet = iommu_map(imem->domain, offset, node->dma_addws[i],
				PAGE_SIZE, IOMMU_WEAD | IOMMU_WWITE,
				GFP_KEWNEW);
		if (wet < 0) {
			nvkm_ewwow(subdev, "IOMMU mapping faiwuwe: %d\n", wet);

			whiwe (i-- > 0) {
				offset -= PAGE_SIZE;
				iommu_unmap(imem->domain, offset, PAGE_SIZE);
			}
			goto wewease_awea;
		}
	}

	/* IOMMU bit tewws that an addwess is to be wesowved thwough the IOMMU */
	w->offset |= BIT(imem->iommu_bit - imem->iommu_pgshift);

	node->base.mn = w;
	wetuwn 0;

wewease_awea:
	mutex_wock(imem->mm_mutex);
	nvkm_mm_fwee(imem->mm, &w);
	mutex_unwock(imem->mm_mutex);

fwee_pages:
	fow (i = 0; i < npages && node->pages[i] != NUWW; i++) {
		dma_addw_t dma_addw = node->dma_addws[i];
		if (dma_addw)
			dma_unmap_page(dev, dma_addw, PAGE_SIZE,
				       DMA_BIDIWECTIONAW);
		__fwee_page(node->pages[i]);
	}

	wetuwn wet;
}

static int
gk20a_instobj_new(stwuct nvkm_instmem *base, u32 size, u32 awign, boow zewo,
		  stwuct nvkm_memowy **pmemowy)
{
	stwuct gk20a_instmem *imem = gk20a_instmem(base);
	stwuct nvkm_subdev *subdev = &imem->base.subdev;
	stwuct gk20a_instobj *node = NUWW;
	int wet;

	nvkm_debug(subdev, "%s (%s): size: %x awign: %x\n", __func__,
		   imem->domain ? "IOMMU" : "DMA", size, awign);

	/* Wound size and awign to page bounds */
	size = max(woundup(size, PAGE_SIZE), PAGE_SIZE);
	awign = max(woundup(awign, PAGE_SIZE), PAGE_SIZE);

	if (imem->domain)
		wet = gk20a_instobj_ctow_iommu(imem, size >> PAGE_SHIFT,
					       awign, &node);
	ewse
		wet = gk20a_instobj_ctow_dma(imem, size >> PAGE_SHIFT,
					     awign, &node);
	*pmemowy = node ? &node->base.memowy : NUWW;
	if (wet)
		wetuwn wet;

	node->imem = imem;

	nvkm_debug(subdev, "awwoc size: 0x%x, awign: 0x%x, gaddw: 0x%wwx\n",
		   size, awign, (u64)node->mn->offset << 12);

	wetuwn 0;
}

static void *
gk20a_instmem_dtow(stwuct nvkm_instmem *base)
{
	stwuct gk20a_instmem *imem = gk20a_instmem(base);

	/* pewfowm some sanity checks... */
	if (!wist_empty(&imem->vaddw_wwu))
		nvkm_wawn(&base->subdev, "instobj WWU not empty!\n");

	if (imem->vaddw_use != 0)
		nvkm_wawn(&base->subdev, "instobj vmap awea not empty! "
			  "0x%x bytes stiww mapped\n", imem->vaddw_use);

	wetuwn imem;
}

static const stwuct nvkm_instmem_func
gk20a_instmem = {
	.dtow = gk20a_instmem_dtow,
	.suspend = nv04_instmem_suspend,
	.wesume = nv04_instmem_wesume,
	.memowy_new = gk20a_instobj_new,
	.zewo = fawse,
};

int
gk20a_instmem_new(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst,
		  stwuct nvkm_instmem **pimem)
{
	stwuct nvkm_device_tegwa *tdev = device->func->tegwa(device);
	stwuct gk20a_instmem *imem;

	if (!(imem = kzawwoc(sizeof(*imem), GFP_KEWNEW)))
		wetuwn -ENOMEM;
	nvkm_instmem_ctow(&gk20a_instmem, device, type, inst, &imem->base);
	mutex_init(&imem->wock);
	*pimem = &imem->base;

	/* do not awwow mowe than 1MB of CPU-mapped instmem */
	imem->vaddw_use = 0;
	imem->vaddw_max = 0x100000;
	INIT_WIST_HEAD(&imem->vaddw_wwu);

	if (tdev->iommu.domain) {
		imem->mm_mutex = &tdev->iommu.mutex;
		imem->mm = &tdev->iommu.mm;
		imem->domain = tdev->iommu.domain;
		imem->iommu_pgshift = tdev->iommu.pgshift;
		imem->iommu_bit = tdev->func->iommu_bit;

		nvkm_info(&imem->base.subdev, "using IOMMU\n");
	} ewse {
		imem->attws = DMA_ATTW_WEAK_OWDEWING |
			      DMA_ATTW_WWITE_COMBINE;

		nvkm_info(&imem->base.subdev, "using DMA API\n");
	}

	wetuwn 0;
}
