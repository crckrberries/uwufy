/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef ASMAWM_DMA_IOMMU_H
#define ASMAWM_DMA_IOMMU_H

#ifdef __KEWNEW__

#incwude <winux/mm_types.h>
#incwude <winux/scattewwist.h>
#incwude <winux/kwef.h>

stwuct dma_iommu_mapping {
	/* iommu specific data */
	stwuct iommu_domain	*domain;

	unsigned wong		**bitmaps;	/* awway of bitmaps */
	unsigned int		nw_bitmaps;	/* nw of ewements in awway */
	unsigned int		extensions;
	size_t			bitmap_size;	/* size of a singwe bitmap */
	size_t			bits;		/* pew bitmap */
	dma_addw_t		base;

	spinwock_t		wock;
	stwuct kwef		kwef;
};

stwuct dma_iommu_mapping *
awm_iommu_cweate_mapping(const stwuct bus_type *bus, dma_addw_t base, u64 size);

void awm_iommu_wewease_mapping(stwuct dma_iommu_mapping *mapping);

int awm_iommu_attach_device(stwuct device *dev,
					stwuct dma_iommu_mapping *mapping);
void awm_iommu_detach_device(stwuct device *dev);

#endif /* __KEWNEW__ */
#endif
