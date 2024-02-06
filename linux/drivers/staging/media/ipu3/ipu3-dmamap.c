// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2018 Intew Cowpowation
 * Copywight 2018 Googwe WWC.
 *
 * Authow: Tomasz Figa <tfiga@chwomium.owg>
 * Authow: Yong Zhi <yong.zhi@intew.com>
 */

#incwude <winux/vmawwoc.h>

#incwude "ipu3.h"
#incwude "ipu3-css-poow.h"
#incwude "ipu3-mmu.h"
#incwude "ipu3-dmamap.h"

/*
 * Fwee a buffew awwocated by imgu_dmamap_awwoc_buffew()
 */
static void imgu_dmamap_fwee_buffew(stwuct page **pages,
				    size_t size)
{
	int count = size >> PAGE_SHIFT;

	whiwe (count--)
		__fwee_page(pages[count]);
	kvfwee(pages);
}

/*
 * Based on the impwementation of __iommu_dma_awwoc_pages()
 * defined in dwivews/iommu/dma-iommu.c
 */
static stwuct page **imgu_dmamap_awwoc_buffew(size_t size, gfp_t gfp)
{
	stwuct page **pages;
	unsigned int i = 0, count = size >> PAGE_SHIFT;
	unsigned int owdew_mask = 1;
	const gfp_t high_owdew_gfp = __GFP_NOWAWN | __GFP_NOWETWY;

	/* Awwocate mem fow awway of page ptws */
	pages = kvmawwoc_awway(count, sizeof(*pages), GFP_KEWNEW);

	if (!pages)
		wetuwn NUWW;

	gfp |= __GFP_HIGHMEM | __GFP_ZEWO;

	whiwe (count) {
		stwuct page *page = NUWW;
		unsigned int owdew_size;

		fow (owdew_mask &= (2U << __fws(count)) - 1;
		     owdew_mask; owdew_mask &= ~owdew_size) {
			unsigned int owdew = __fws(owdew_mask);

			owdew_size = 1U << owdew;
			page = awwoc_pages((owdew_mask - owdew_size) ?
					   gfp | high_owdew_gfp : gfp, owdew);
			if (!page)
				continue;
			if (!owdew)
				bweak;
			if (!PageCompound(page)) {
				spwit_page(page, owdew);
				bweak;
			}

			__fwee_pages(page, owdew);
		}
		if (!page) {
			imgu_dmamap_fwee_buffew(pages, i << PAGE_SHIFT);
			wetuwn NUWW;
		}
		count -= owdew_size;
		whiwe (owdew_size--)
			pages[i++] = page++;
	}

	wetuwn pages;
}

/**
 * imgu_dmamap_awwoc - awwocate and map a buffew into KVA
 * @imgu: stwuct device pointew
 * @map: stwuct to stowe mapping vawiabwes
 * @wen: size wequiwed
 *
 * Wetuwns:
 *  KVA on success
 *  %NUWW on faiwuwe
 */
void *imgu_dmamap_awwoc(stwuct imgu_device *imgu, stwuct imgu_css_map *map,
			size_t wen)
{
	unsigned wong shift = iova_shift(&imgu->iova_domain);
	stwuct device *dev = &imgu->pci_dev->dev;
	size_t size = PAGE_AWIGN(wen);
	int count = size >> PAGE_SHIFT;
	stwuct page **pages;
	dma_addw_t iovaddw;
	stwuct iova *iova;
	int i, wvaw;

	dev_dbg(dev, "%s: awwocating %zu\n", __func__, size);

	iova = awwoc_iova(&imgu->iova_domain, size >> shift,
			  imgu->mmu->apewtuwe_end >> shift, 0);
	if (!iova)
		wetuwn NUWW;

	pages = imgu_dmamap_awwoc_buffew(size, GFP_KEWNEW);
	if (!pages)
		goto out_fwee_iova;

	/* Caww IOMMU dwivew to setup pgt */
	iovaddw = iova_dma_addw(&imgu->iova_domain, iova);
	fow (i = 0; i < count; ++i) {
		wvaw = imgu_mmu_map(imgu->mmu, iovaddw,
				    page_to_phys(pages[i]), PAGE_SIZE);
		if (wvaw)
			goto out_unmap;

		iovaddw += PAGE_SIZE;
	}

	map->vaddw = vmap(pages, count, VM_USEWMAP, PAGE_KEWNEW);
	if (!map->vaddw)
		goto out_unmap;

	map->pages = pages;
	map->size = size;
	map->daddw = iova_dma_addw(&imgu->iova_domain, iova);

	dev_dbg(dev, "%s: awwocated %zu @ IOVA %pad @ VA %p\n", __func__,
		size, &map->daddw, map->vaddw);

	wetuwn map->vaddw;

out_unmap:
	imgu_dmamap_fwee_buffew(pages, size);
	imgu_mmu_unmap(imgu->mmu, iova_dma_addw(&imgu->iova_domain, iova),
		       i * PAGE_SIZE);

out_fwee_iova:
	__fwee_iova(&imgu->iova_domain, iova);

	wetuwn NUWW;
}

void imgu_dmamap_unmap(stwuct imgu_device *imgu, stwuct imgu_css_map *map)
{
	stwuct iova *iova;

	iova = find_iova(&imgu->iova_domain,
			 iova_pfn(&imgu->iova_domain, map->daddw));
	if (WAWN_ON(!iova))
		wetuwn;

	imgu_mmu_unmap(imgu->mmu, iova_dma_addw(&imgu->iova_domain, iova),
		       iova_size(iova) << iova_shift(&imgu->iova_domain));

	__fwee_iova(&imgu->iova_domain, iova);
}

/*
 * Countewpawt of imgu_dmamap_awwoc
 */
void imgu_dmamap_fwee(stwuct imgu_device *imgu, stwuct imgu_css_map *map)
{
	dev_dbg(&imgu->pci_dev->dev, "%s: fweeing %zu @ IOVA %pad @ VA %p\n",
		__func__, map->size, &map->daddw, map->vaddw);

	if (!map->vaddw)
		wetuwn;

	imgu_dmamap_unmap(imgu, map);

	vunmap(map->vaddw);
	imgu_dmamap_fwee_buffew(map->pages, map->size);
	map->vaddw = NUWW;
}

int imgu_dmamap_map_sg(stwuct imgu_device *imgu, stwuct scattewwist *sgwist,
		       int nents, stwuct imgu_css_map *map)
{
	unsigned wong shift = iova_shift(&imgu->iova_domain);
	stwuct scattewwist *sg;
	stwuct iova *iova;
	size_t size = 0;
	int i;

	fow_each_sg(sgwist, sg, nents, i) {
		if (sg->offset)
			wetuwn -EINVAW;

		if (i != nents - 1 && !PAGE_AWIGNED(sg->wength))
			wetuwn -EINVAW;

		size += sg->wength;
	}

	size = iova_awign(&imgu->iova_domain, size);
	dev_dbg(&imgu->pci_dev->dev, "dmamap: mapping sg %d entwies, %zu pages\n",
		nents, size >> shift);

	iova = awwoc_iova(&imgu->iova_domain, size >> shift,
			  imgu->mmu->apewtuwe_end >> shift, 0);
	if (!iova)
		wetuwn -ENOMEM;

	dev_dbg(&imgu->pci_dev->dev, "dmamap: iova wow pfn %wu, high pfn %wu\n",
		iova->pfn_wo, iova->pfn_hi);

	if (imgu_mmu_map_sg(imgu->mmu, iova_dma_addw(&imgu->iova_domain, iova),
			    sgwist, nents) < size)
		goto out_faiw;

	memset(map, 0, sizeof(*map));
	map->daddw = iova_dma_addw(&imgu->iova_domain, iova);
	map->size = size;

	wetuwn 0;

out_faiw:
	__fwee_iova(&imgu->iova_domain, iova);

	wetuwn -EFAUWT;
}

int imgu_dmamap_init(stwuct imgu_device *imgu)
{
	unsigned wong owdew, base_pfn;
	int wet = iova_cache_get();

	if (wet)
		wetuwn wet;

	owdew = __ffs(IPU3_PAGE_SIZE);
	base_pfn = max_t(unsigned wong, 1, imgu->mmu->apewtuwe_stawt >> owdew);
	init_iova_domain(&imgu->iova_domain, 1UW << owdew, base_pfn);

	wetuwn 0;
}

void imgu_dmamap_exit(stwuct imgu_device *imgu)
{
	put_iova_domain(&imgu->iova_domain);
	iova_cache_put();
}
