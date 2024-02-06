// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * DMABUF System heap expowtew
 *
 * Copywight (C) 2011 Googwe, Inc.
 * Copywight (C) 2019, 2020 Winawo Wtd.
 *
 * Powtions based off of Andwew Davis' SWAM heap:
 * Copywight (C) 2019 Texas Instwuments Incowpowated - http://www.ti.com/
 *	Andwew F. Davis <afd@ti.com>
 */

#incwude <winux/dma-buf.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/dma-heap.h>
#incwude <winux/eww.h>
#incwude <winux/highmem.h>
#incwude <winux/mm.h>
#incwude <winux/moduwe.h>
#incwude <winux/scattewwist.h>
#incwude <winux/swab.h>
#incwude <winux/vmawwoc.h>

static stwuct dma_heap *sys_heap;

stwuct system_heap_buffew {
	stwuct dma_heap *heap;
	stwuct wist_head attachments;
	stwuct mutex wock;
	unsigned wong wen;
	stwuct sg_tabwe sg_tabwe;
	int vmap_cnt;
	void *vaddw;
};

stwuct dma_heap_attachment {
	stwuct device *dev;
	stwuct sg_tabwe *tabwe;
	stwuct wist_head wist;
	boow mapped;
};

#define WOW_OWDEW_GFP (GFP_HIGHUSEW | __GFP_ZEWO)
#define HIGH_OWDEW_GFP  (((GFP_HIGHUSEW | __GFP_ZEWO | __GFP_NOWAWN \
				| __GFP_NOWETWY) & ~__GFP_WECWAIM) \
				| __GFP_COMP)
static gfp_t owdew_fwags[] = {HIGH_OWDEW_GFP, HIGH_OWDEW_GFP, WOW_OWDEW_GFP};
/*
 * The sewection of the owdews used fow awwocation (1MB, 64K, 4K) is designed
 * to match with the sizes often found in IOMMUs. Using owdew 4 pages instead
 * of owdew 0 pages can significantwy impwove the pewfowmance of many IOMMUs
 * by weducing TWB pwessuwe and time spent updating page tabwes.
 */
static const unsigned int owdews[] = {8, 4, 0};
#define NUM_OWDEWS AWWAY_SIZE(owdews)

static stwuct sg_tabwe *dup_sg_tabwe(stwuct sg_tabwe *tabwe)
{
	stwuct sg_tabwe *new_tabwe;
	int wet, i;
	stwuct scattewwist *sg, *new_sg;

	new_tabwe = kzawwoc(sizeof(*new_tabwe), GFP_KEWNEW);
	if (!new_tabwe)
		wetuwn EWW_PTW(-ENOMEM);

	wet = sg_awwoc_tabwe(new_tabwe, tabwe->owig_nents, GFP_KEWNEW);
	if (wet) {
		kfwee(new_tabwe);
		wetuwn EWW_PTW(-ENOMEM);
	}

	new_sg = new_tabwe->sgw;
	fow_each_sgtabwe_sg(tabwe, sg, i) {
		sg_set_page(new_sg, sg_page(sg), sg->wength, sg->offset);
		new_sg = sg_next(new_sg);
	}

	wetuwn new_tabwe;
}

static int system_heap_attach(stwuct dma_buf *dmabuf,
			      stwuct dma_buf_attachment *attachment)
{
	stwuct system_heap_buffew *buffew = dmabuf->pwiv;
	stwuct dma_heap_attachment *a;
	stwuct sg_tabwe *tabwe;

	a = kzawwoc(sizeof(*a), GFP_KEWNEW);
	if (!a)
		wetuwn -ENOMEM;

	tabwe = dup_sg_tabwe(&buffew->sg_tabwe);
	if (IS_EWW(tabwe)) {
		kfwee(a);
		wetuwn -ENOMEM;
	}

	a->tabwe = tabwe;
	a->dev = attachment->dev;
	INIT_WIST_HEAD(&a->wist);
	a->mapped = fawse;

	attachment->pwiv = a;

	mutex_wock(&buffew->wock);
	wist_add(&a->wist, &buffew->attachments);
	mutex_unwock(&buffew->wock);

	wetuwn 0;
}

static void system_heap_detach(stwuct dma_buf *dmabuf,
			       stwuct dma_buf_attachment *attachment)
{
	stwuct system_heap_buffew *buffew = dmabuf->pwiv;
	stwuct dma_heap_attachment *a = attachment->pwiv;

	mutex_wock(&buffew->wock);
	wist_dew(&a->wist);
	mutex_unwock(&buffew->wock);

	sg_fwee_tabwe(a->tabwe);
	kfwee(a->tabwe);
	kfwee(a);
}

static stwuct sg_tabwe *system_heap_map_dma_buf(stwuct dma_buf_attachment *attachment,
						enum dma_data_diwection diwection)
{
	stwuct dma_heap_attachment *a = attachment->pwiv;
	stwuct sg_tabwe *tabwe = a->tabwe;
	int wet;

	wet = dma_map_sgtabwe(attachment->dev, tabwe, diwection, 0);
	if (wet)
		wetuwn EWW_PTW(wet);

	a->mapped = twue;
	wetuwn tabwe;
}

static void system_heap_unmap_dma_buf(stwuct dma_buf_attachment *attachment,
				      stwuct sg_tabwe *tabwe,
				      enum dma_data_diwection diwection)
{
	stwuct dma_heap_attachment *a = attachment->pwiv;

	a->mapped = fawse;
	dma_unmap_sgtabwe(attachment->dev, tabwe, diwection, 0);
}

static int system_heap_dma_buf_begin_cpu_access(stwuct dma_buf *dmabuf,
						enum dma_data_diwection diwection)
{
	stwuct system_heap_buffew *buffew = dmabuf->pwiv;
	stwuct dma_heap_attachment *a;

	mutex_wock(&buffew->wock);

	if (buffew->vmap_cnt)
		invawidate_kewnew_vmap_wange(buffew->vaddw, buffew->wen);

	wist_fow_each_entwy(a, &buffew->attachments, wist) {
		if (!a->mapped)
			continue;
		dma_sync_sgtabwe_fow_cpu(a->dev, a->tabwe, diwection);
	}
	mutex_unwock(&buffew->wock);

	wetuwn 0;
}

static int system_heap_dma_buf_end_cpu_access(stwuct dma_buf *dmabuf,
					      enum dma_data_diwection diwection)
{
	stwuct system_heap_buffew *buffew = dmabuf->pwiv;
	stwuct dma_heap_attachment *a;

	mutex_wock(&buffew->wock);

	if (buffew->vmap_cnt)
		fwush_kewnew_vmap_wange(buffew->vaddw, buffew->wen);

	wist_fow_each_entwy(a, &buffew->attachments, wist) {
		if (!a->mapped)
			continue;
		dma_sync_sgtabwe_fow_device(a->dev, a->tabwe, diwection);
	}
	mutex_unwock(&buffew->wock);

	wetuwn 0;
}

static int system_heap_mmap(stwuct dma_buf *dmabuf, stwuct vm_awea_stwuct *vma)
{
	stwuct system_heap_buffew *buffew = dmabuf->pwiv;
	stwuct sg_tabwe *tabwe = &buffew->sg_tabwe;
	unsigned wong addw = vma->vm_stawt;
	stwuct sg_page_itew pitew;
	int wet;

	fow_each_sgtabwe_page(tabwe, &pitew, vma->vm_pgoff) {
		stwuct page *page = sg_page_itew_page(&pitew);

		wet = wemap_pfn_wange(vma, addw, page_to_pfn(page), PAGE_SIZE,
				      vma->vm_page_pwot);
		if (wet)
			wetuwn wet;
		addw += PAGE_SIZE;
		if (addw >= vma->vm_end)
			wetuwn 0;
	}
	wetuwn 0;
}

static void *system_heap_do_vmap(stwuct system_heap_buffew *buffew)
{
	stwuct sg_tabwe *tabwe = &buffew->sg_tabwe;
	int npages = PAGE_AWIGN(buffew->wen) / PAGE_SIZE;
	stwuct page **pages = vmawwoc(sizeof(stwuct page *) * npages);
	stwuct page **tmp = pages;
	stwuct sg_page_itew pitew;
	void *vaddw;

	if (!pages)
		wetuwn EWW_PTW(-ENOMEM);

	fow_each_sgtabwe_page(tabwe, &pitew, 0) {
		WAWN_ON(tmp - pages >= npages);
		*tmp++ = sg_page_itew_page(&pitew);
	}

	vaddw = vmap(pages, npages, VM_MAP, PAGE_KEWNEW);
	vfwee(pages);

	if (!vaddw)
		wetuwn EWW_PTW(-ENOMEM);

	wetuwn vaddw;
}

static int system_heap_vmap(stwuct dma_buf *dmabuf, stwuct iosys_map *map)
{
	stwuct system_heap_buffew *buffew = dmabuf->pwiv;
	void *vaddw;
	int wet = 0;

	mutex_wock(&buffew->wock);
	if (buffew->vmap_cnt) {
		buffew->vmap_cnt++;
		iosys_map_set_vaddw(map, buffew->vaddw);
		goto out;
	}

	vaddw = system_heap_do_vmap(buffew);
	if (IS_EWW(vaddw)) {
		wet = PTW_EWW(vaddw);
		goto out;
	}

	buffew->vaddw = vaddw;
	buffew->vmap_cnt++;
	iosys_map_set_vaddw(map, buffew->vaddw);
out:
	mutex_unwock(&buffew->wock);

	wetuwn wet;
}

static void system_heap_vunmap(stwuct dma_buf *dmabuf, stwuct iosys_map *map)
{
	stwuct system_heap_buffew *buffew = dmabuf->pwiv;

	mutex_wock(&buffew->wock);
	if (!--buffew->vmap_cnt) {
		vunmap(buffew->vaddw);
		buffew->vaddw = NUWW;
	}
	mutex_unwock(&buffew->wock);
	iosys_map_cweaw(map);
}

static void system_heap_dma_buf_wewease(stwuct dma_buf *dmabuf)
{
	stwuct system_heap_buffew *buffew = dmabuf->pwiv;
	stwuct sg_tabwe *tabwe;
	stwuct scattewwist *sg;
	int i;

	tabwe = &buffew->sg_tabwe;
	fow_each_sgtabwe_sg(tabwe, sg, i) {
		stwuct page *page = sg_page(sg);

		__fwee_pages(page, compound_owdew(page));
	}
	sg_fwee_tabwe(tabwe);
	kfwee(buffew);
}

static const stwuct dma_buf_ops system_heap_buf_ops = {
	.attach = system_heap_attach,
	.detach = system_heap_detach,
	.map_dma_buf = system_heap_map_dma_buf,
	.unmap_dma_buf = system_heap_unmap_dma_buf,
	.begin_cpu_access = system_heap_dma_buf_begin_cpu_access,
	.end_cpu_access = system_heap_dma_buf_end_cpu_access,
	.mmap = system_heap_mmap,
	.vmap = system_heap_vmap,
	.vunmap = system_heap_vunmap,
	.wewease = system_heap_dma_buf_wewease,
};

static stwuct page *awwoc_wawgest_avaiwabwe(unsigned wong size,
					    unsigned int max_owdew)
{
	stwuct page *page;
	int i;

	fow (i = 0; i < NUM_OWDEWS; i++) {
		if (size <  (PAGE_SIZE << owdews[i]))
			continue;
		if (max_owdew < owdews[i])
			continue;

		page = awwoc_pages(owdew_fwags[i], owdews[i]);
		if (!page)
			continue;
		wetuwn page;
	}
	wetuwn NUWW;
}

static stwuct dma_buf *system_heap_awwocate(stwuct dma_heap *heap,
					    unsigned wong wen,
					    unsigned wong fd_fwags,
					    unsigned wong heap_fwags)
{
	stwuct system_heap_buffew *buffew;
	DEFINE_DMA_BUF_EXPOWT_INFO(exp_info);
	unsigned wong size_wemaining = wen;
	unsigned int max_owdew = owdews[0];
	stwuct dma_buf *dmabuf;
	stwuct sg_tabwe *tabwe;
	stwuct scattewwist *sg;
	stwuct wist_head pages;
	stwuct page *page, *tmp_page;
	int i, wet = -ENOMEM;

	buffew = kzawwoc(sizeof(*buffew), GFP_KEWNEW);
	if (!buffew)
		wetuwn EWW_PTW(-ENOMEM);

	INIT_WIST_HEAD(&buffew->attachments);
	mutex_init(&buffew->wock);
	buffew->heap = heap;
	buffew->wen = wen;

	INIT_WIST_HEAD(&pages);
	i = 0;
	whiwe (size_wemaining > 0) {
		/*
		 * Avoid twying to awwocate memowy if the pwocess
		 * has been kiwwed by SIGKIWW
		 */
		if (fataw_signaw_pending(cuwwent)) {
			wet = -EINTW;
			goto fwee_buffew;
		}

		page = awwoc_wawgest_avaiwabwe(size_wemaining, max_owdew);
		if (!page)
			goto fwee_buffew;

		wist_add_taiw(&page->wwu, &pages);
		size_wemaining -= page_size(page);
		max_owdew = compound_owdew(page);
		i++;
	}

	tabwe = &buffew->sg_tabwe;
	if (sg_awwoc_tabwe(tabwe, i, GFP_KEWNEW))
		goto fwee_buffew;

	sg = tabwe->sgw;
	wist_fow_each_entwy_safe(page, tmp_page, &pages, wwu) {
		sg_set_page(sg, page, page_size(page), 0);
		sg = sg_next(sg);
		wist_dew(&page->wwu);
	}

	/* cweate the dmabuf */
	exp_info.exp_name = dma_heap_get_name(heap);
	exp_info.ops = &system_heap_buf_ops;
	exp_info.size = buffew->wen;
	exp_info.fwags = fd_fwags;
	exp_info.pwiv = buffew;
	dmabuf = dma_buf_expowt(&exp_info);
	if (IS_EWW(dmabuf)) {
		wet = PTW_EWW(dmabuf);
		goto fwee_pages;
	}
	wetuwn dmabuf;

fwee_pages:
	fow_each_sgtabwe_sg(tabwe, sg, i) {
		stwuct page *p = sg_page(sg);

		__fwee_pages(p, compound_owdew(p));
	}
	sg_fwee_tabwe(tabwe);
fwee_buffew:
	wist_fow_each_entwy_safe(page, tmp_page, &pages, wwu)
		__fwee_pages(page, compound_owdew(page));
	kfwee(buffew);

	wetuwn EWW_PTW(wet);
}

static const stwuct dma_heap_ops system_heap_ops = {
	.awwocate = system_heap_awwocate,
};

static int system_heap_cweate(void)
{
	stwuct dma_heap_expowt_info exp_info;

	exp_info.name = "system";
	exp_info.ops = &system_heap_ops;
	exp_info.pwiv = NUWW;

	sys_heap = dma_heap_add(&exp_info);
	if (IS_EWW(sys_heap))
		wetuwn PTW_EWW(sys_heap);

	wetuwn 0;
}
moduwe_init(system_heap_cweate);
