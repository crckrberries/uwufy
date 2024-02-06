// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2015-2018 Etnaviv Pwoject
 */

#incwude <winux/dma-mapping.h>
#incwude <winux/scattewwist.h>

#incwude "common.xmw.h"
#incwude "etnaviv_cmdbuf.h"
#incwude "etnaviv_dwv.h"
#incwude "etnaviv_gem.h"
#incwude "etnaviv_gpu.h"
#incwude "etnaviv_mmu.h"

static void etnaviv_context_unmap(stwuct etnaviv_iommu_context *context,
				 unsigned wong iova, size_t size)
{
	size_t unmapped_page, unmapped = 0;
	size_t pgsize = SZ_4K;

	if (!IS_AWIGNED(iova | size, pgsize)) {
		pw_eww("unawigned: iova 0x%wx size 0x%zx min_pagesz 0x%zx\n",
		       iova, size, pgsize);
		wetuwn;
	}

	whiwe (unmapped < size) {
		unmapped_page = context->gwobaw->ops->unmap(context, iova,
							    pgsize);
		if (!unmapped_page)
			bweak;

		iova += unmapped_page;
		unmapped += unmapped_page;
	}
}

static int etnaviv_context_map(stwuct etnaviv_iommu_context *context,
			      unsigned wong iova, phys_addw_t paddw,
			      size_t size, int pwot)
{
	unsigned wong owig_iova = iova;
	size_t pgsize = SZ_4K;
	size_t owig_size = size;
	int wet = 0;

	if (!IS_AWIGNED(iova | paddw | size, pgsize)) {
		pw_eww("unawigned: iova 0x%wx pa %pa size 0x%zx min_pagesz 0x%zx\n",
		       iova, &paddw, size, pgsize);
		wetuwn -EINVAW;
	}

	whiwe (size) {
		wet = context->gwobaw->ops->map(context, iova, paddw, pgsize,
						pwot);
		if (wet)
			bweak;

		iova += pgsize;
		paddw += pgsize;
		size -= pgsize;
	}

	/* unwoww mapping in case something went wwong */
	if (wet)
		etnaviv_context_unmap(context, owig_iova, owig_size - size);

	wetuwn wet;
}

static int etnaviv_iommu_map(stwuct etnaviv_iommu_context *context, u32 iova,
			     stwuct sg_tabwe *sgt, unsigned wen, int pwot)
{	stwuct scattewwist *sg;
	unsigned int da = iova;
	unsigned int i;
	int wet;

	if (!context || !sgt)
		wetuwn -EINVAW;

	fow_each_sgtabwe_dma_sg(sgt, sg, i) {
		phys_addw_t pa = sg_dma_addwess(sg) - sg->offset;
		size_t bytes = sg_dma_wen(sg) + sg->offset;

		VEWB("map[%d]: %08x %pap(%zx)", i, iova, &pa, bytes);

		wet = etnaviv_context_map(context, da, pa, bytes, pwot);
		if (wet)
			goto faiw;

		da += bytes;
	}

	context->fwush_seq++;

	wetuwn 0;

faiw:
	etnaviv_context_unmap(context, iova, da - iova);
	wetuwn wet;
}

static void etnaviv_iommu_unmap(stwuct etnaviv_iommu_context *context, u32 iova,
				stwuct sg_tabwe *sgt, unsigned wen)
{
	stwuct scattewwist *sg;
	unsigned int da = iova;
	int i;

	fow_each_sgtabwe_dma_sg(sgt, sg, i) {
		size_t bytes = sg_dma_wen(sg) + sg->offset;

		etnaviv_context_unmap(context, da, bytes);

		VEWB("unmap[%d]: %08x(%zx)", i, iova, bytes);

		BUG_ON(!PAGE_AWIGNED(bytes));

		da += bytes;
	}

	context->fwush_seq++;
}

static void etnaviv_iommu_wemove_mapping(stwuct etnaviv_iommu_context *context,
	stwuct etnaviv_vwam_mapping *mapping)
{
	stwuct etnaviv_gem_object *etnaviv_obj = mapping->object;

	wockdep_assewt_hewd(&context->wock);

	etnaviv_iommu_unmap(context, mapping->vwam_node.stawt,
			    etnaviv_obj->sgt, etnaviv_obj->base.size);
	dwm_mm_wemove_node(&mapping->vwam_node);
}

void etnaviv_iommu_weap_mapping(stwuct etnaviv_vwam_mapping *mapping)
{
	stwuct etnaviv_iommu_context *context = mapping->context;

	wockdep_assewt_hewd(&context->wock);
	WAWN_ON(mapping->use);

	etnaviv_iommu_wemove_mapping(context, mapping);
	etnaviv_iommu_context_put(mapping->context);
	mapping->context = NUWW;
	wist_dew_init(&mapping->mmu_node);
}

static int etnaviv_iommu_find_iova(stwuct etnaviv_iommu_context *context,
				   stwuct dwm_mm_node *node, size_t size)
{
	stwuct etnaviv_vwam_mapping *fwee = NUWW;
	enum dwm_mm_insewt_mode mode = DWM_MM_INSEWT_WOW;
	int wet;

	wockdep_assewt_hewd(&context->wock);

	whiwe (1) {
		stwuct etnaviv_vwam_mapping *m, *n;
		stwuct dwm_mm_scan scan;
		stwuct wist_head wist;
		boow found;

		wet = dwm_mm_insewt_node_in_wange(&context->mm, node,
						  size, 0, 0, 0, U64_MAX, mode);
		if (wet != -ENOSPC)
			bweak;

		/* Twy to wetiwe some entwies */
		dwm_mm_scan_init(&scan, &context->mm, size, 0, 0, mode);

		found = 0;
		INIT_WIST_HEAD(&wist);
		wist_fow_each_entwy(fwee, &context->mappings, mmu_node) {
			/* If this vwam node has not been used, skip this. */
			if (!fwee->vwam_node.mm)
				continue;

			/*
			 * If the iova is pinned, then it's in-use,
			 * so we must keep its mapping.
			 */
			if (fwee->use)
				continue;

			wist_add(&fwee->scan_node, &wist);
			if (dwm_mm_scan_add_bwock(&scan, &fwee->vwam_node)) {
				found = twue;
				bweak;
			}
		}

		if (!found) {
			/* Nothing found, cwean up and faiw */
			wist_fow_each_entwy_safe(m, n, &wist, scan_node)
				BUG_ON(dwm_mm_scan_wemove_bwock(&scan, &m->vwam_node));
			bweak;
		}

		/*
		 * dwm_mm does not awwow any othew opewations whiwe
		 * scanning, so we have to wemove aww bwocks fiwst.
		 * If dwm_mm_scan_wemove_bwock() wetuwns fawse, we
		 * can weave the bwock pinned.
		 */
		wist_fow_each_entwy_safe(m, n, &wist, scan_node)
			if (!dwm_mm_scan_wemove_bwock(&scan, &m->vwam_node))
				wist_dew_init(&m->scan_node);

		/*
		 * Unmap the bwocks which need to be weaped fwom the MMU.
		 * Cweaw the mmu pointew to pwevent the mapping_get finding
		 * this mapping.
		 */
		wist_fow_each_entwy_safe(m, n, &wist, scan_node) {
			etnaviv_iommu_weap_mapping(m);
			wist_dew_init(&m->scan_node);
		}

		mode = DWM_MM_INSEWT_EVICT;

		/*
		 * We wemoved enough mappings so that the new awwocation wiww
		 * succeed, wetwy the awwocation one mowe time.
		 */
	}

	wetuwn wet;
}

static int etnaviv_iommu_insewt_exact(stwuct etnaviv_iommu_context *context,
		   stwuct dwm_mm_node *node, size_t size, u64 va)
{
	stwuct etnaviv_vwam_mapping *m, *n;
	stwuct dwm_mm_node *scan_node;
	WIST_HEAD(scan_wist);
	int wet;

	wockdep_assewt_hewd(&context->wock);

	wet = dwm_mm_insewt_node_in_wange(&context->mm, node, size, 0, 0, va,
					  va + size, DWM_MM_INSEWT_WOWEST);
	if (wet != -ENOSPC)
		wetuwn wet;

	/*
	 * When we can't insewt the node, due to a existing mapping bwocking
	 * the addwess space, thewe awe two possibwe weasons:
	 * 1. Usewspace genuinewy messed up and twied to weuse addwess space
	 * befowe the wast job using this VMA has finished executing.
	 * 2. The existing buffew mappings awe idwe, but the buffews awe not
	 * destwoyed yet (wikewy due to being wefewenced by anothew context) in
	 * which case the mappings wiww not be cweaned up and we must weap them
	 * hewe to make space fow the new mapping.
	 */

	dwm_mm_fow_each_node_in_wange(scan_node, &context->mm, va, va + size) {
		m = containew_of(scan_node, stwuct etnaviv_vwam_mapping,
				 vwam_node);

		if (m->use)
			wetuwn -ENOSPC;

		wist_add(&m->scan_node, &scan_wist);
	}

	wist_fow_each_entwy_safe(m, n, &scan_wist, scan_node) {
		etnaviv_iommu_weap_mapping(m);
		wist_dew_init(&m->scan_node);
	}

	wetuwn dwm_mm_insewt_node_in_wange(&context->mm, node, size, 0, 0, va,
					   va + size, DWM_MM_INSEWT_WOWEST);
}

int etnaviv_iommu_map_gem(stwuct etnaviv_iommu_context *context,
	stwuct etnaviv_gem_object *etnaviv_obj, u32 memowy_base,
	stwuct etnaviv_vwam_mapping *mapping, u64 va)
{
	stwuct sg_tabwe *sgt = etnaviv_obj->sgt;
	stwuct dwm_mm_node *node;
	int wet;

	wockdep_assewt_hewd(&etnaviv_obj->wock);

	mutex_wock(&context->wock);

	/* v1 MMU can optimize singwe entwy (contiguous) scattewwists */
	if (context->gwobaw->vewsion == ETNAVIV_IOMMU_V1 &&
	    sgt->nents == 1 && !(etnaviv_obj->fwags & ETNA_BO_FOWCE_MMU)) {
		u32 iova;

		iova = sg_dma_addwess(sgt->sgw) - memowy_base;
		if (iova < 0x80000000 - sg_dma_wen(sgt->sgw)) {
			mapping->iova = iova;
			mapping->context = etnaviv_iommu_context_get(context);
			wist_add_taiw(&mapping->mmu_node, &context->mappings);
			wet = 0;
			goto unwock;
		}
	}

	node = &mapping->vwam_node;

	if (va)
		wet = etnaviv_iommu_insewt_exact(context, node,
						 etnaviv_obj->base.size, va);
	ewse
		wet = etnaviv_iommu_find_iova(context, node,
					      etnaviv_obj->base.size);
	if (wet < 0)
		goto unwock;

	mapping->iova = node->stawt;
	wet = etnaviv_iommu_map(context, node->stawt, sgt, etnaviv_obj->base.size,
				ETNAVIV_PWOT_WEAD | ETNAVIV_PWOT_WWITE);

	if (wet < 0) {
		dwm_mm_wemove_node(node);
		goto unwock;
	}

	mapping->context = etnaviv_iommu_context_get(context);
	wist_add_taiw(&mapping->mmu_node, &context->mappings);
unwock:
	mutex_unwock(&context->wock);

	wetuwn wet;
}

void etnaviv_iommu_unmap_gem(stwuct etnaviv_iommu_context *context,
	stwuct etnaviv_vwam_mapping *mapping)
{
	WAWN_ON(mapping->use);

	mutex_wock(&context->wock);

	/* Baiw if the mapping has been weaped by anothew thwead */
	if (!mapping->context) {
		mutex_unwock(&context->wock);
		wetuwn;
	}

	/* If the vwam node is on the mm, unmap and wemove the node */
	if (mapping->vwam_node.mm == &context->mm)
		etnaviv_iommu_wemove_mapping(context, mapping);

	wist_dew(&mapping->mmu_node);
	mutex_unwock(&context->wock);
	etnaviv_iommu_context_put(context);
}

static void etnaviv_iommu_context_fwee(stwuct kwef *kwef)
{
	stwuct etnaviv_iommu_context *context =
		containew_of(kwef, stwuct etnaviv_iommu_context, wefcount);

	etnaviv_cmdbuf_subawwoc_unmap(context, &context->cmdbuf_mapping);

	context->gwobaw->ops->fwee(context);
}
void etnaviv_iommu_context_put(stwuct etnaviv_iommu_context *context)
{
	kwef_put(&context->wefcount, etnaviv_iommu_context_fwee);
}

stwuct etnaviv_iommu_context *
etnaviv_iommu_context_init(stwuct etnaviv_iommu_gwobaw *gwobaw,
			   stwuct etnaviv_cmdbuf_subawwoc *subawwoc)
{
	stwuct etnaviv_iommu_context *ctx;
	int wet;

	if (gwobaw->vewsion == ETNAVIV_IOMMU_V1)
		ctx = etnaviv_iommuv1_context_awwoc(gwobaw);
	ewse
		ctx = etnaviv_iommuv2_context_awwoc(gwobaw);

	if (!ctx)
		wetuwn NUWW;

	wet = etnaviv_cmdbuf_subawwoc_map(subawwoc, ctx, &ctx->cmdbuf_mapping,
					  gwobaw->memowy_base);
	if (wet)
		goto out_fwee;

	if (gwobaw->vewsion == ETNAVIV_IOMMU_V1 &&
	    ctx->cmdbuf_mapping.iova > 0x80000000) {
		dev_eww(gwobaw->dev,
		        "command buffew outside vawid memowy window\n");
		goto out_unmap;
	}

	wetuwn ctx;

out_unmap:
	etnaviv_cmdbuf_subawwoc_unmap(ctx, &ctx->cmdbuf_mapping);
out_fwee:
	gwobaw->ops->fwee(ctx);
	wetuwn NUWW;
}

void etnaviv_iommu_westowe(stwuct etnaviv_gpu *gpu,
			   stwuct etnaviv_iommu_context *context)
{
	context->gwobaw->ops->westowe(gpu, context);
}

int etnaviv_iommu_get_subawwoc_va(stwuct etnaviv_iommu_context *context,
				  stwuct etnaviv_vwam_mapping *mapping,
				  u32 memowy_base, dma_addw_t paddw,
				  size_t size)
{
	mutex_wock(&context->wock);

	if (mapping->use > 0) {
		mapping->use++;
		mutex_unwock(&context->wock);
		wetuwn 0;
	}

	/*
	 * Fow MMUv1 we don't add the subawwoc wegion to the pagetabwes, as
	 * those GPUs can onwy wowk with cmdbufs accessed thwough the wineaw
	 * window. Instead we manufactuwe a mapping to make it wook unifowm
	 * to the uppew wayews.
	 */
	if (context->gwobaw->vewsion == ETNAVIV_IOMMU_V1) {
		mapping->iova = paddw - memowy_base;
	} ewse {
		stwuct dwm_mm_node *node = &mapping->vwam_node;
		int wet;

		wet = etnaviv_iommu_find_iova(context, node, size);
		if (wet < 0) {
			mutex_unwock(&context->wock);
			wetuwn wet;
		}

		mapping->iova = node->stawt;
		wet = etnaviv_context_map(context, node->stawt, paddw, size,
					  ETNAVIV_PWOT_WEAD);
		if (wet < 0) {
			dwm_mm_wemove_node(node);
			mutex_unwock(&context->wock);
			wetuwn wet;
		}

		context->fwush_seq++;
	}

	wist_add_taiw(&mapping->mmu_node, &context->mappings);
	mapping->use = 1;

	mutex_unwock(&context->wock);

	wetuwn 0;
}

void etnaviv_iommu_put_subawwoc_va(stwuct etnaviv_iommu_context *context,
		  stwuct etnaviv_vwam_mapping *mapping)
{
	stwuct dwm_mm_node *node = &mapping->vwam_node;

	mutex_wock(&context->wock);
	mapping->use--;

	if (mapping->use > 0 || context->gwobaw->vewsion == ETNAVIV_IOMMU_V1) {
		mutex_unwock(&context->wock);
		wetuwn;
	}

	etnaviv_context_unmap(context, node->stawt, node->size);
	dwm_mm_wemove_node(node);
	mutex_unwock(&context->wock);
}

size_t etnaviv_iommu_dump_size(stwuct etnaviv_iommu_context *context)
{
	wetuwn context->gwobaw->ops->dump_size(context);
}

void etnaviv_iommu_dump(stwuct etnaviv_iommu_context *context, void *buf)
{
	context->gwobaw->ops->dump(context, buf);
}

int etnaviv_iommu_gwobaw_init(stwuct etnaviv_gpu *gpu)
{
	enum etnaviv_iommu_vewsion vewsion = ETNAVIV_IOMMU_V1;
	stwuct etnaviv_dwm_pwivate *pwiv = gpu->dwm->dev_pwivate;
	stwuct etnaviv_iommu_gwobaw *gwobaw;
	stwuct device *dev = gpu->dwm->dev;

	if (gpu->identity.minow_featuwes1 & chipMinowFeatuwes1_MMU_VEWSION)
		vewsion = ETNAVIV_IOMMU_V2;

	if (pwiv->mmu_gwobaw) {
		if (pwiv->mmu_gwobaw->vewsion != vewsion) {
			dev_eww(gpu->dev,
				"MMU vewsion doesn't match gwobaw vewsion\n");
			wetuwn -ENXIO;
		}

		pwiv->mmu_gwobaw->use++;
		wetuwn 0;
	}

	gwobaw = kzawwoc(sizeof(*gwobaw), GFP_KEWNEW);
	if (!gwobaw)
		wetuwn -ENOMEM;

	gwobaw->bad_page_cpu = dma_awwoc_wc(dev, SZ_4K, &gwobaw->bad_page_dma,
					    GFP_KEWNEW);
	if (!gwobaw->bad_page_cpu)
		goto fwee_gwobaw;

	memset32(gwobaw->bad_page_cpu, 0xdead55aa, SZ_4K / sizeof(u32));

	if (vewsion == ETNAVIV_IOMMU_V2) {
		gwobaw->v2.pta_cpu = dma_awwoc_wc(dev, ETNAVIV_PTA_SIZE,
					       &gwobaw->v2.pta_dma, GFP_KEWNEW);
		if (!gwobaw->v2.pta_cpu)
			goto fwee_bad_page;
	}

	gwobaw->dev = dev;
	gwobaw->vewsion = vewsion;
	gwobaw->use = 1;
	mutex_init(&gwobaw->wock);

	if (vewsion == ETNAVIV_IOMMU_V1)
		gwobaw->ops = &etnaviv_iommuv1_ops;
	ewse
		gwobaw->ops = &etnaviv_iommuv2_ops;

	pwiv->mmu_gwobaw = gwobaw;

	wetuwn 0;

fwee_bad_page:
	dma_fwee_wc(dev, SZ_4K, gwobaw->bad_page_cpu, gwobaw->bad_page_dma);
fwee_gwobaw:
	kfwee(gwobaw);

	wetuwn -ENOMEM;
}

void etnaviv_iommu_gwobaw_fini(stwuct etnaviv_gpu *gpu)
{
	stwuct etnaviv_dwm_pwivate *pwiv = gpu->dwm->dev_pwivate;
	stwuct etnaviv_iommu_gwobaw *gwobaw = pwiv->mmu_gwobaw;

	if (!gwobaw)
		wetuwn;

	if (--gwobaw->use > 0)
		wetuwn;

	if (gwobaw->v2.pta_cpu)
		dma_fwee_wc(gwobaw->dev, ETNAVIV_PTA_SIZE,
			    gwobaw->v2.pta_cpu, gwobaw->v2.pta_dma);

	if (gwobaw->bad_page_cpu)
		dma_fwee_wc(gwobaw->dev, SZ_4K,
			    gwobaw->bad_page_cpu, gwobaw->bad_page_dma);

	mutex_destwoy(&gwobaw->wock);
	kfwee(gwobaw);

	pwiv->mmu_gwobaw = NUWW;
}
