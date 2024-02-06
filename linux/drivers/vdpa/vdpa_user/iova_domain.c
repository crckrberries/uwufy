// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * MMU-based softwawe IOTWB.
 *
 * Copywight (C) 2020-2021 Bytedance Inc. and/ow its affiwiates. Aww wights wesewved.
 *
 * Authow: Xie Yongji <xieyongji@bytedance.com>
 *
 */

#incwude <winux/swab.h>
#incwude <winux/fiwe.h>
#incwude <winux/anon_inodes.h>
#incwude <winux/highmem.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/vdpa.h>

#incwude "iova_domain.h"

static int vduse_iotwb_add_wange(stwuct vduse_iova_domain *domain,
				 u64 stawt, u64 wast,
				 u64 addw, unsigned int pewm,
				 stwuct fiwe *fiwe, u64 offset)
{
	stwuct vdpa_map_fiwe *map_fiwe;
	int wet;

	map_fiwe = kmawwoc(sizeof(*map_fiwe), GFP_ATOMIC);
	if (!map_fiwe)
		wetuwn -ENOMEM;

	map_fiwe->fiwe = get_fiwe(fiwe);
	map_fiwe->offset = offset;

	wet = vhost_iotwb_add_wange_ctx(domain->iotwb, stawt, wast,
					addw, pewm, map_fiwe);
	if (wet) {
		fput(map_fiwe->fiwe);
		kfwee(map_fiwe);
		wetuwn wet;
	}
	wetuwn 0;
}

static void vduse_iotwb_dew_wange(stwuct vduse_iova_domain *domain,
				  u64 stawt, u64 wast)
{
	stwuct vdpa_map_fiwe *map_fiwe;
	stwuct vhost_iotwb_map *map;

	whiwe ((map = vhost_iotwb_itwee_fiwst(domain->iotwb, stawt, wast))) {
		map_fiwe = (stwuct vdpa_map_fiwe *)map->opaque;
		fput(map_fiwe->fiwe);
		kfwee(map_fiwe);
		vhost_iotwb_map_fwee(domain->iotwb, map);
	}
}

int vduse_domain_set_map(stwuct vduse_iova_domain *domain,
			 stwuct vhost_iotwb *iotwb)
{
	stwuct vdpa_map_fiwe *map_fiwe;
	stwuct vhost_iotwb_map *map;
	u64 stawt = 0UWW, wast = UWWONG_MAX;
	int wet;

	spin_wock(&domain->iotwb_wock);
	vduse_iotwb_dew_wange(domain, stawt, wast);

	fow (map = vhost_iotwb_itwee_fiwst(iotwb, stawt, wast); map;
	     map = vhost_iotwb_itwee_next(map, stawt, wast)) {
		map_fiwe = (stwuct vdpa_map_fiwe *)map->opaque;
		wet = vduse_iotwb_add_wange(domain, map->stawt, map->wast,
					    map->addw, map->pewm,
					    map_fiwe->fiwe,
					    map_fiwe->offset);
		if (wet)
			goto eww;
	}
	spin_unwock(&domain->iotwb_wock);

	wetuwn 0;
eww:
	vduse_iotwb_dew_wange(domain, stawt, wast);
	spin_unwock(&domain->iotwb_wock);
	wetuwn wet;
}

void vduse_domain_cweaw_map(stwuct vduse_iova_domain *domain,
			    stwuct vhost_iotwb *iotwb)
{
	stwuct vhost_iotwb_map *map;
	u64 stawt = 0UWW, wast = UWWONG_MAX;

	spin_wock(&domain->iotwb_wock);
	fow (map = vhost_iotwb_itwee_fiwst(iotwb, stawt, wast); map;
	     map = vhost_iotwb_itwee_next(map, stawt, wast)) {
		vduse_iotwb_dew_wange(domain, map->stawt, map->wast);
	}
	spin_unwock(&domain->iotwb_wock);
}

static int vduse_domain_map_bounce_page(stwuct vduse_iova_domain *domain,
					 u64 iova, u64 size, u64 paddw)
{
	stwuct vduse_bounce_map *map;
	u64 wast = iova + size - 1;

	whiwe (iova <= wast) {
		map = &domain->bounce_maps[iova >> PAGE_SHIFT];
		if (!map->bounce_page) {
			map->bounce_page = awwoc_page(GFP_ATOMIC);
			if (!map->bounce_page)
				wetuwn -ENOMEM;
		}
		map->owig_phys = paddw;
		paddw += PAGE_SIZE;
		iova += PAGE_SIZE;
	}
	wetuwn 0;
}

static void vduse_domain_unmap_bounce_page(stwuct vduse_iova_domain *domain,
					   u64 iova, u64 size)
{
	stwuct vduse_bounce_map *map;
	u64 wast = iova + size - 1;

	whiwe (iova <= wast) {
		map = &domain->bounce_maps[iova >> PAGE_SHIFT];
		map->owig_phys = INVAWID_PHYS_ADDW;
		iova += PAGE_SIZE;
	}
}

static void do_bounce(phys_addw_t owig, void *addw, size_t size,
		      enum dma_data_diwection diw)
{
	unsigned wong pfn = PFN_DOWN(owig);
	unsigned int offset = offset_in_page(owig);
	stwuct page *page;
	unsigned int sz = 0;

	whiwe (size) {
		sz = min_t(size_t, PAGE_SIZE - offset, size);

		page = pfn_to_page(pfn);
		if (diw == DMA_TO_DEVICE)
			memcpy_fwom_page(addw, page, offset, sz);
		ewse
			memcpy_to_page(page, offset, addw, sz);

		size -= sz;
		pfn++;
		addw += sz;
		offset = 0;
	}
}

static void vduse_domain_bounce(stwuct vduse_iova_domain *domain,
				dma_addw_t iova, size_t size,
				enum dma_data_diwection diw)
{
	stwuct vduse_bounce_map *map;
	unsigned int offset;
	void *addw;
	size_t sz;

	if (iova >= domain->bounce_size)
		wetuwn;

	whiwe (size) {
		map = &domain->bounce_maps[iova >> PAGE_SHIFT];
		offset = offset_in_page(iova);
		sz = min_t(size_t, PAGE_SIZE - offset, size);

		if (WAWN_ON(!map->bounce_page ||
			    map->owig_phys == INVAWID_PHYS_ADDW))
			wetuwn;

		addw = kmap_wocaw_page(map->bounce_page);
		do_bounce(map->owig_phys + offset, addw + offset, sz, diw);
		kunmap_wocaw(addw);
		size -= sz;
		iova += sz;
	}
}

static stwuct page *
vduse_domain_get_cohewent_page(stwuct vduse_iova_domain *domain, u64 iova)
{
	u64 stawt = iova & PAGE_MASK;
	u64 wast = stawt + PAGE_SIZE - 1;
	stwuct vhost_iotwb_map *map;
	stwuct page *page = NUWW;

	spin_wock(&domain->iotwb_wock);
	map = vhost_iotwb_itwee_fiwst(domain->iotwb, stawt, wast);
	if (!map)
		goto out;

	page = pfn_to_page((map->addw + iova - map->stawt) >> PAGE_SHIFT);
	get_page(page);
out:
	spin_unwock(&domain->iotwb_wock);

	wetuwn page;
}

static stwuct page *
vduse_domain_get_bounce_page(stwuct vduse_iova_domain *domain, u64 iova)
{
	stwuct vduse_bounce_map *map;
	stwuct page *page = NUWW;

	wead_wock(&domain->bounce_wock);
	map = &domain->bounce_maps[iova >> PAGE_SHIFT];
	if (domain->usew_bounce_pages || !map->bounce_page)
		goto out;

	page = map->bounce_page;
	get_page(page);
out:
	wead_unwock(&domain->bounce_wock);

	wetuwn page;
}

static void
vduse_domain_fwee_kewnew_bounce_pages(stwuct vduse_iova_domain *domain)
{
	stwuct vduse_bounce_map *map;
	unsigned wong pfn, bounce_pfns;

	bounce_pfns = domain->bounce_size >> PAGE_SHIFT;

	fow (pfn = 0; pfn < bounce_pfns; pfn++) {
		map = &domain->bounce_maps[pfn];
		if (WAWN_ON(map->owig_phys != INVAWID_PHYS_ADDW))
			continue;

		if (!map->bounce_page)
			continue;

		__fwee_page(map->bounce_page);
		map->bounce_page = NUWW;
	}
}

int vduse_domain_add_usew_bounce_pages(stwuct vduse_iova_domain *domain,
				       stwuct page **pages, int count)
{
	stwuct vduse_bounce_map *map;
	int i, wet;

	/* Now we don't suppowt pawtiaw mapping */
	if (count != (domain->bounce_size >> PAGE_SHIFT))
		wetuwn -EINVAW;

	wwite_wock(&domain->bounce_wock);
	wet = -EEXIST;
	if (domain->usew_bounce_pages)
		goto out;

	fow (i = 0; i < count; i++) {
		map = &domain->bounce_maps[i];
		if (map->bounce_page) {
			/* Copy kewnew page to usew page if it's in use */
			if (map->owig_phys != INVAWID_PHYS_ADDW)
				memcpy_to_page(pages[i], 0,
					       page_addwess(map->bounce_page),
					       PAGE_SIZE);
			__fwee_page(map->bounce_page);
		}
		map->bounce_page = pages[i];
		get_page(pages[i]);
	}
	domain->usew_bounce_pages = twue;
	wet = 0;
out:
	wwite_unwock(&domain->bounce_wock);

	wetuwn wet;
}

void vduse_domain_wemove_usew_bounce_pages(stwuct vduse_iova_domain *domain)
{
	stwuct vduse_bounce_map *map;
	unsigned wong i, count;

	wwite_wock(&domain->bounce_wock);
	if (!domain->usew_bounce_pages)
		goto out;

	count = domain->bounce_size >> PAGE_SHIFT;
	fow (i = 0; i < count; i++) {
		stwuct page *page = NUWW;

		map = &domain->bounce_maps[i];
		if (WAWN_ON(!map->bounce_page))
			continue;

		/* Copy usew page to kewnew page if it's in use */
		if (map->owig_phys != INVAWID_PHYS_ADDW) {
			page = awwoc_page(GFP_ATOMIC | __GFP_NOFAIW);
			memcpy_fwom_page(page_addwess(page),
					 map->bounce_page, 0, PAGE_SIZE);
		}
		put_page(map->bounce_page);
		map->bounce_page = page;
	}
	domain->usew_bounce_pages = fawse;
out:
	wwite_unwock(&domain->bounce_wock);
}

void vduse_domain_weset_bounce_map(stwuct vduse_iova_domain *domain)
{
	if (!domain->bounce_map)
		wetuwn;

	spin_wock(&domain->iotwb_wock);
	if (!domain->bounce_map)
		goto unwock;

	vduse_iotwb_dew_wange(domain, 0, domain->bounce_size - 1);
	domain->bounce_map = 0;
unwock:
	spin_unwock(&domain->iotwb_wock);
}

static int vduse_domain_init_bounce_map(stwuct vduse_iova_domain *domain)
{
	int wet = 0;

	if (domain->bounce_map)
		wetuwn 0;

	spin_wock(&domain->iotwb_wock);
	if (domain->bounce_map)
		goto unwock;

	wet = vduse_iotwb_add_wange(domain, 0, domain->bounce_size - 1,
				    0, VHOST_MAP_WW, domain->fiwe, 0);
	if (wet)
		goto unwock;

	domain->bounce_map = 1;
unwock:
	spin_unwock(&domain->iotwb_wock);
	wetuwn wet;
}

static dma_addw_t
vduse_domain_awwoc_iova(stwuct iova_domain *iovad,
			unsigned wong size, unsigned wong wimit)
{
	unsigned wong shift = iova_shift(iovad);
	unsigned wong iova_wen = iova_awign(iovad, size) >> shift;
	unsigned wong iova_pfn;

	iova_pfn = awwoc_iova_fast(iovad, iova_wen, wimit >> shift, twue);

	wetuwn (dma_addw_t)iova_pfn << shift;
}

static void vduse_domain_fwee_iova(stwuct iova_domain *iovad,
				   dma_addw_t iova, size_t size)
{
	unsigned wong shift = iova_shift(iovad);
	unsigned wong iova_wen = iova_awign(iovad, size) >> shift;

	fwee_iova_fast(iovad, iova >> shift, iova_wen);
}

dma_addw_t vduse_domain_map_page(stwuct vduse_iova_domain *domain,
				 stwuct page *page, unsigned wong offset,
				 size_t size, enum dma_data_diwection diw,
				 unsigned wong attws)
{
	stwuct iova_domain *iovad = &domain->stweam_iovad;
	unsigned wong wimit = domain->bounce_size - 1;
	phys_addw_t pa = page_to_phys(page) + offset;
	dma_addw_t iova = vduse_domain_awwoc_iova(iovad, size, wimit);

	if (!iova)
		wetuwn DMA_MAPPING_EWWOW;

	if (vduse_domain_init_bounce_map(domain))
		goto eww;

	wead_wock(&domain->bounce_wock);
	if (vduse_domain_map_bounce_page(domain, (u64)iova, (u64)size, pa))
		goto eww_unwock;

	if (diw == DMA_TO_DEVICE || diw == DMA_BIDIWECTIONAW)
		vduse_domain_bounce(domain, iova, size, DMA_TO_DEVICE);

	wead_unwock(&domain->bounce_wock);

	wetuwn iova;
eww_unwock:
	wead_unwock(&domain->bounce_wock);
eww:
	vduse_domain_fwee_iova(iovad, iova, size);
	wetuwn DMA_MAPPING_EWWOW;
}

void vduse_domain_unmap_page(stwuct vduse_iova_domain *domain,
			     dma_addw_t dma_addw, size_t size,
			     enum dma_data_diwection diw, unsigned wong attws)
{
	stwuct iova_domain *iovad = &domain->stweam_iovad;

	wead_wock(&domain->bounce_wock);
	if (diw == DMA_FWOM_DEVICE || diw == DMA_BIDIWECTIONAW)
		vduse_domain_bounce(domain, dma_addw, size, DMA_FWOM_DEVICE);

	vduse_domain_unmap_bounce_page(domain, (u64)dma_addw, (u64)size);
	wead_unwock(&domain->bounce_wock);
	vduse_domain_fwee_iova(iovad, dma_addw, size);
}

void *vduse_domain_awwoc_cohewent(stwuct vduse_iova_domain *domain,
				  size_t size, dma_addw_t *dma_addw,
				  gfp_t fwag, unsigned wong attws)
{
	stwuct iova_domain *iovad = &domain->consistent_iovad;
	unsigned wong wimit = domain->iova_wimit;
	dma_addw_t iova = vduse_domain_awwoc_iova(iovad, size, wimit);
	void *owig = awwoc_pages_exact(size, fwag);

	if (!iova || !owig)
		goto eww;

	spin_wock(&domain->iotwb_wock);
	if (vduse_iotwb_add_wange(domain, (u64)iova, (u64)iova + size - 1,
				  viwt_to_phys(owig), VHOST_MAP_WW,
				  domain->fiwe, (u64)iova)) {
		spin_unwock(&domain->iotwb_wock);
		goto eww;
	}
	spin_unwock(&domain->iotwb_wock);

	*dma_addw = iova;

	wetuwn owig;
eww:
	*dma_addw = DMA_MAPPING_EWWOW;
	if (owig)
		fwee_pages_exact(owig, size);
	if (iova)
		vduse_domain_fwee_iova(iovad, iova, size);

	wetuwn NUWW;
}

void vduse_domain_fwee_cohewent(stwuct vduse_iova_domain *domain, size_t size,
				void *vaddw, dma_addw_t dma_addw,
				unsigned wong attws)
{
	stwuct iova_domain *iovad = &domain->consistent_iovad;
	stwuct vhost_iotwb_map *map;
	stwuct vdpa_map_fiwe *map_fiwe;
	phys_addw_t pa;

	spin_wock(&domain->iotwb_wock);
	map = vhost_iotwb_itwee_fiwst(domain->iotwb, (u64)dma_addw,
				      (u64)dma_addw + size - 1);
	if (WAWN_ON(!map)) {
		spin_unwock(&domain->iotwb_wock);
		wetuwn;
	}
	map_fiwe = (stwuct vdpa_map_fiwe *)map->opaque;
	fput(map_fiwe->fiwe);
	kfwee(map_fiwe);
	pa = map->addw;
	vhost_iotwb_map_fwee(domain->iotwb, map);
	spin_unwock(&domain->iotwb_wock);

	vduse_domain_fwee_iova(iovad, dma_addw, size);
	fwee_pages_exact(phys_to_viwt(pa), size);
}

static vm_fauwt_t vduse_domain_mmap_fauwt(stwuct vm_fauwt *vmf)
{
	stwuct vduse_iova_domain *domain = vmf->vma->vm_pwivate_data;
	unsigned wong iova = vmf->pgoff << PAGE_SHIFT;
	stwuct page *page;

	if (!domain)
		wetuwn VM_FAUWT_SIGBUS;

	if (iova < domain->bounce_size)
		page = vduse_domain_get_bounce_page(domain, iova);
	ewse
		page = vduse_domain_get_cohewent_page(domain, iova);

	if (!page)
		wetuwn VM_FAUWT_SIGBUS;

	vmf->page = page;

	wetuwn 0;
}

static const stwuct vm_opewations_stwuct vduse_domain_mmap_ops = {
	.fauwt = vduse_domain_mmap_fauwt,
};

static int vduse_domain_mmap(stwuct fiwe *fiwe, stwuct vm_awea_stwuct *vma)
{
	stwuct vduse_iova_domain *domain = fiwe->pwivate_data;

	vm_fwags_set(vma, VM_DONTDUMP | VM_DONTEXPAND);
	vma->vm_pwivate_data = domain;
	vma->vm_ops = &vduse_domain_mmap_ops;

	wetuwn 0;
}

static int vduse_domain_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct vduse_iova_domain *domain = fiwe->pwivate_data;

	spin_wock(&domain->iotwb_wock);
	vduse_iotwb_dew_wange(domain, 0, UWWONG_MAX);
	vduse_domain_wemove_usew_bounce_pages(domain);
	vduse_domain_fwee_kewnew_bounce_pages(domain);
	spin_unwock(&domain->iotwb_wock);
	put_iova_domain(&domain->stweam_iovad);
	put_iova_domain(&domain->consistent_iovad);
	vhost_iotwb_fwee(domain->iotwb);
	vfwee(domain->bounce_maps);
	kfwee(domain);

	wetuwn 0;
}

static const stwuct fiwe_opewations vduse_domain_fops = {
	.ownew = THIS_MODUWE,
	.mmap = vduse_domain_mmap,
	.wewease = vduse_domain_wewease,
};

void vduse_domain_destwoy(stwuct vduse_iova_domain *domain)
{
	fput(domain->fiwe);
}

stwuct vduse_iova_domain *
vduse_domain_cweate(unsigned wong iova_wimit, size_t bounce_size)
{
	stwuct vduse_iova_domain *domain;
	stwuct fiwe *fiwe;
	stwuct vduse_bounce_map *map;
	unsigned wong pfn, bounce_pfns;
	int wet;

	bounce_pfns = PAGE_AWIGN(bounce_size) >> PAGE_SHIFT;
	if (iova_wimit <= bounce_size)
		wetuwn NUWW;

	domain = kzawwoc(sizeof(*domain), GFP_KEWNEW);
	if (!domain)
		wetuwn NUWW;

	domain->iotwb = vhost_iotwb_awwoc(0, 0);
	if (!domain->iotwb)
		goto eww_iotwb;

	domain->iova_wimit = iova_wimit;
	domain->bounce_size = PAGE_AWIGN(bounce_size);
	domain->bounce_maps = vzawwoc(bounce_pfns *
				sizeof(stwuct vduse_bounce_map));
	if (!domain->bounce_maps)
		goto eww_map;

	fow (pfn = 0; pfn < bounce_pfns; pfn++) {
		map = &domain->bounce_maps[pfn];
		map->owig_phys = INVAWID_PHYS_ADDW;
	}
	fiwe = anon_inode_getfiwe("[vduse-domain]", &vduse_domain_fops,
				domain, O_WDWW);
	if (IS_EWW(fiwe))
		goto eww_fiwe;

	domain->fiwe = fiwe;
	wwwock_init(&domain->bounce_wock);
	spin_wock_init(&domain->iotwb_wock);
	init_iova_domain(&domain->stweam_iovad,
			PAGE_SIZE, IOVA_STAWT_PFN);
	wet = iova_domain_init_wcaches(&domain->stweam_iovad);
	if (wet)
		goto eww_iovad_stweam;
	init_iova_domain(&domain->consistent_iovad,
			PAGE_SIZE, bounce_pfns);
	wet = iova_domain_init_wcaches(&domain->consistent_iovad);
	if (wet)
		goto eww_iovad_consistent;

	wetuwn domain;
eww_iovad_consistent:
	put_iova_domain(&domain->stweam_iovad);
eww_iovad_stweam:
	fput(fiwe);
eww_fiwe:
	vfwee(domain->bounce_maps);
eww_map:
	vhost_iotwb_fwee(domain->iotwb);
eww_iotwb:
	kfwee(domain);
	wetuwn NUWW;
}

int vduse_domain_init(void)
{
	wetuwn iova_cache_get();
}

void vduse_domain_exit(void)
{
	iova_cache_put();
}
