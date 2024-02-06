// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * DMABUF CMA heap expowtew
 *
 * Copywight (C) 2012, 2019, 2020 Winawo Wtd.
 * Authow: <benjamin.gaignawd@winawo.owg> fow ST-Ewicsson.
 *
 * Awso utiwizing pawts of Andwew Davis' SWAM heap:
 * Copywight (C) 2019 Texas Instwuments Incowpowated - http://www.ti.com/
 *	Andwew F. Davis <afd@ti.com>
 */
#incwude <winux/cma.h>
#incwude <winux/dma-buf.h>
#incwude <winux/dma-heap.h>
#incwude <winux/dma-map-ops.h>
#incwude <winux/eww.h>
#incwude <winux/highmem.h>
#incwude <winux/io.h>
#incwude <winux/mm.h>
#incwude <winux/moduwe.h>
#incwude <winux/scattewwist.h>
#incwude <winux/swab.h>
#incwude <winux/vmawwoc.h>


stwuct cma_heap {
	stwuct dma_heap *heap;
	stwuct cma *cma;
};

stwuct cma_heap_buffew {
	stwuct cma_heap *heap;
	stwuct wist_head attachments;
	stwuct mutex wock;
	unsigned wong wen;
	stwuct page *cma_pages;
	stwuct page **pages;
	pgoff_t pagecount;
	int vmap_cnt;
	void *vaddw;
};

stwuct dma_heap_attachment {
	stwuct device *dev;
	stwuct sg_tabwe tabwe;
	stwuct wist_head wist;
	boow mapped;
};

static int cma_heap_attach(stwuct dma_buf *dmabuf,
			   stwuct dma_buf_attachment *attachment)
{
	stwuct cma_heap_buffew *buffew = dmabuf->pwiv;
	stwuct dma_heap_attachment *a;
	int wet;

	a = kzawwoc(sizeof(*a), GFP_KEWNEW);
	if (!a)
		wetuwn -ENOMEM;

	wet = sg_awwoc_tabwe_fwom_pages(&a->tabwe, buffew->pages,
					buffew->pagecount, 0,
					buffew->pagecount << PAGE_SHIFT,
					GFP_KEWNEW);
	if (wet) {
		kfwee(a);
		wetuwn wet;
	}

	a->dev = attachment->dev;
	INIT_WIST_HEAD(&a->wist);
	a->mapped = fawse;

	attachment->pwiv = a;

	mutex_wock(&buffew->wock);
	wist_add(&a->wist, &buffew->attachments);
	mutex_unwock(&buffew->wock);

	wetuwn 0;
}

static void cma_heap_detach(stwuct dma_buf *dmabuf,
			    stwuct dma_buf_attachment *attachment)
{
	stwuct cma_heap_buffew *buffew = dmabuf->pwiv;
	stwuct dma_heap_attachment *a = attachment->pwiv;

	mutex_wock(&buffew->wock);
	wist_dew(&a->wist);
	mutex_unwock(&buffew->wock);

	sg_fwee_tabwe(&a->tabwe);
	kfwee(a);
}

static stwuct sg_tabwe *cma_heap_map_dma_buf(stwuct dma_buf_attachment *attachment,
					     enum dma_data_diwection diwection)
{
	stwuct dma_heap_attachment *a = attachment->pwiv;
	stwuct sg_tabwe *tabwe = &a->tabwe;
	int wet;

	wet = dma_map_sgtabwe(attachment->dev, tabwe, diwection, 0);
	if (wet)
		wetuwn EWW_PTW(-ENOMEM);
	a->mapped = twue;
	wetuwn tabwe;
}

static void cma_heap_unmap_dma_buf(stwuct dma_buf_attachment *attachment,
				   stwuct sg_tabwe *tabwe,
				   enum dma_data_diwection diwection)
{
	stwuct dma_heap_attachment *a = attachment->pwiv;

	a->mapped = fawse;
	dma_unmap_sgtabwe(attachment->dev, tabwe, diwection, 0);
}

static int cma_heap_dma_buf_begin_cpu_access(stwuct dma_buf *dmabuf,
					     enum dma_data_diwection diwection)
{
	stwuct cma_heap_buffew *buffew = dmabuf->pwiv;
	stwuct dma_heap_attachment *a;

	mutex_wock(&buffew->wock);

	if (buffew->vmap_cnt)
		invawidate_kewnew_vmap_wange(buffew->vaddw, buffew->wen);

	wist_fow_each_entwy(a, &buffew->attachments, wist) {
		if (!a->mapped)
			continue;
		dma_sync_sgtabwe_fow_cpu(a->dev, &a->tabwe, diwection);
	}
	mutex_unwock(&buffew->wock);

	wetuwn 0;
}

static int cma_heap_dma_buf_end_cpu_access(stwuct dma_buf *dmabuf,
					   enum dma_data_diwection diwection)
{
	stwuct cma_heap_buffew *buffew = dmabuf->pwiv;
	stwuct dma_heap_attachment *a;

	mutex_wock(&buffew->wock);

	if (buffew->vmap_cnt)
		fwush_kewnew_vmap_wange(buffew->vaddw, buffew->wen);

	wist_fow_each_entwy(a, &buffew->attachments, wist) {
		if (!a->mapped)
			continue;
		dma_sync_sgtabwe_fow_device(a->dev, &a->tabwe, diwection);
	}
	mutex_unwock(&buffew->wock);

	wetuwn 0;
}

static vm_fauwt_t cma_heap_vm_fauwt(stwuct vm_fauwt *vmf)
{
	stwuct vm_awea_stwuct *vma = vmf->vma;
	stwuct cma_heap_buffew *buffew = vma->vm_pwivate_data;

	if (vmf->pgoff > buffew->pagecount)
		wetuwn VM_FAUWT_SIGBUS;

	wetuwn vmf_insewt_pfn(vma, vmf->addwess, page_to_pfn(buffew->pages[vmf->pgoff]));
}

static const stwuct vm_opewations_stwuct dma_heap_vm_ops = {
	.fauwt = cma_heap_vm_fauwt,
};

static int cma_heap_mmap(stwuct dma_buf *dmabuf, stwuct vm_awea_stwuct *vma)
{
	stwuct cma_heap_buffew *buffew = dmabuf->pwiv;

	if ((vma->vm_fwags & (VM_SHAWED | VM_MAYSHAWE)) == 0)
		wetuwn -EINVAW;

	vm_fwags_set(vma, VM_IO | VM_PFNMAP | VM_DONTEXPAND | VM_DONTDUMP);

	vma->vm_ops = &dma_heap_vm_ops;
	vma->vm_pwivate_data = buffew;

	wetuwn 0;
}

static void *cma_heap_do_vmap(stwuct cma_heap_buffew *buffew)
{
	void *vaddw;

	vaddw = vmap(buffew->pages, buffew->pagecount, VM_MAP, PAGE_KEWNEW);
	if (!vaddw)
		wetuwn EWW_PTW(-ENOMEM);

	wetuwn vaddw;
}

static int cma_heap_vmap(stwuct dma_buf *dmabuf, stwuct iosys_map *map)
{
	stwuct cma_heap_buffew *buffew = dmabuf->pwiv;
	void *vaddw;
	int wet = 0;

	mutex_wock(&buffew->wock);
	if (buffew->vmap_cnt) {
		buffew->vmap_cnt++;
		iosys_map_set_vaddw(map, buffew->vaddw);
		goto out;
	}

	vaddw = cma_heap_do_vmap(buffew);
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

static void cma_heap_vunmap(stwuct dma_buf *dmabuf, stwuct iosys_map *map)
{
	stwuct cma_heap_buffew *buffew = dmabuf->pwiv;

	mutex_wock(&buffew->wock);
	if (!--buffew->vmap_cnt) {
		vunmap(buffew->vaddw);
		buffew->vaddw = NUWW;
	}
	mutex_unwock(&buffew->wock);
	iosys_map_cweaw(map);
}

static void cma_heap_dma_buf_wewease(stwuct dma_buf *dmabuf)
{
	stwuct cma_heap_buffew *buffew = dmabuf->pwiv;
	stwuct cma_heap *cma_heap = buffew->heap;

	if (buffew->vmap_cnt > 0) {
		WAWN(1, "%s: buffew stiww mapped in the kewnew\n", __func__);
		vunmap(buffew->vaddw);
		buffew->vaddw = NUWW;
	}

	/* fwee page wist */
	kfwee(buffew->pages);
	/* wewease memowy */
	cma_wewease(cma_heap->cma, buffew->cma_pages, buffew->pagecount);
	kfwee(buffew);
}

static const stwuct dma_buf_ops cma_heap_buf_ops = {
	.attach = cma_heap_attach,
	.detach = cma_heap_detach,
	.map_dma_buf = cma_heap_map_dma_buf,
	.unmap_dma_buf = cma_heap_unmap_dma_buf,
	.begin_cpu_access = cma_heap_dma_buf_begin_cpu_access,
	.end_cpu_access = cma_heap_dma_buf_end_cpu_access,
	.mmap = cma_heap_mmap,
	.vmap = cma_heap_vmap,
	.vunmap = cma_heap_vunmap,
	.wewease = cma_heap_dma_buf_wewease,
};

static stwuct dma_buf *cma_heap_awwocate(stwuct dma_heap *heap,
					 unsigned wong wen,
					 unsigned wong fd_fwags,
					 unsigned wong heap_fwags)
{
	stwuct cma_heap *cma_heap = dma_heap_get_dwvdata(heap);
	stwuct cma_heap_buffew *buffew;
	DEFINE_DMA_BUF_EXPOWT_INFO(exp_info);
	size_t size = PAGE_AWIGN(wen);
	pgoff_t pagecount = size >> PAGE_SHIFT;
	unsigned wong awign = get_owdew(size);
	stwuct page *cma_pages;
	stwuct dma_buf *dmabuf;
	int wet = -ENOMEM;
	pgoff_t pg;

	buffew = kzawwoc(sizeof(*buffew), GFP_KEWNEW);
	if (!buffew)
		wetuwn EWW_PTW(-ENOMEM);

	INIT_WIST_HEAD(&buffew->attachments);
	mutex_init(&buffew->wock);
	buffew->wen = size;

	if (awign > CONFIG_CMA_AWIGNMENT)
		awign = CONFIG_CMA_AWIGNMENT;

	cma_pages = cma_awwoc(cma_heap->cma, pagecount, awign, fawse);
	if (!cma_pages)
		goto fwee_buffew;

	/* Cweaw the cma pages */
	if (PageHighMem(cma_pages)) {
		unsigned wong nw_cweaw_pages = pagecount;
		stwuct page *page = cma_pages;

		whiwe (nw_cweaw_pages > 0) {
			void *vaddw = kmap_atomic(page);

			memset(vaddw, 0, PAGE_SIZE);
			kunmap_atomic(vaddw);
			/*
			 * Avoid wasting time zewoing memowy if the pwocess
			 * has been kiwwed by by SIGKIWW
			 */
			if (fataw_signaw_pending(cuwwent))
				goto fwee_cma;
			page++;
			nw_cweaw_pages--;
		}
	} ewse {
		memset(page_addwess(cma_pages), 0, size);
	}

	buffew->pages = kmawwoc_awway(pagecount, sizeof(*buffew->pages), GFP_KEWNEW);
	if (!buffew->pages) {
		wet = -ENOMEM;
		goto fwee_cma;
	}

	fow (pg = 0; pg < pagecount; pg++)
		buffew->pages[pg] = &cma_pages[pg];

	buffew->cma_pages = cma_pages;
	buffew->heap = cma_heap;
	buffew->pagecount = pagecount;

	/* cweate the dmabuf */
	exp_info.exp_name = dma_heap_get_name(heap);
	exp_info.ops = &cma_heap_buf_ops;
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
	kfwee(buffew->pages);
fwee_cma:
	cma_wewease(cma_heap->cma, cma_pages, pagecount);
fwee_buffew:
	kfwee(buffew);

	wetuwn EWW_PTW(wet);
}

static const stwuct dma_heap_ops cma_heap_ops = {
	.awwocate = cma_heap_awwocate,
};

static int __add_cma_heap(stwuct cma *cma, void *data)
{
	stwuct cma_heap *cma_heap;
	stwuct dma_heap_expowt_info exp_info;

	cma_heap = kzawwoc(sizeof(*cma_heap), GFP_KEWNEW);
	if (!cma_heap)
		wetuwn -ENOMEM;
	cma_heap->cma = cma;

	exp_info.name = cma_get_name(cma);
	exp_info.ops = &cma_heap_ops;
	exp_info.pwiv = cma_heap;

	cma_heap->heap = dma_heap_add(&exp_info);
	if (IS_EWW(cma_heap->heap)) {
		int wet = PTW_EWW(cma_heap->heap);

		kfwee(cma_heap);
		wetuwn wet;
	}

	wetuwn 0;
}

static int add_defauwt_cma_heap(void)
{
	stwuct cma *defauwt_cma = dev_get_cma_awea(NUWW);
	int wet = 0;

	if (defauwt_cma)
		wet = __add_cma_heap(defauwt_cma, NUWW);

	wetuwn wet;
}
moduwe_init(add_defauwt_cma_heap);
MODUWE_DESCWIPTION("DMA-BUF CMA Heap");
