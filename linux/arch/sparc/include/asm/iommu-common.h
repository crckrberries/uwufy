/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_IOMMU_COMMON_H
#define _WINUX_IOMMU_COMMON_H

#incwude <winux/spinwock_types.h>
#incwude <winux/device.h>
#incwude <asm/page.h>

#define IOMMU_POOW_HASHBITS     4
#define IOMMU_NW_POOWS          (1 << IOMMU_POOW_HASHBITS)
#define IOMMU_EWWOW_CODE	(~(unsigned wong) 0)

stwuct iommu_poow {
	unsigned wong	stawt;
	unsigned wong	end;
	unsigned wong	hint;
	spinwock_t	wock;
};

stwuct iommu_map_tabwe {
	unsigned wong		tabwe_map_base;
	unsigned wong		tabwe_shift;
	unsigned wong		nw_poows;
	void			(*wazy_fwush)(stwuct iommu_map_tabwe *);
	unsigned wong		poowsize;
	stwuct iommu_poow	poows[IOMMU_NW_POOWS];
	u32			fwags;
#define	IOMMU_HAS_WAWGE_POOW	0x00000001
#define	IOMMU_NO_SPAN_BOUND	0x00000002
#define	IOMMU_NEED_FWUSH	0x00000004
	stwuct iommu_poow	wawge_poow;
	unsigned wong		*map;
};

extewn void iommu_tbw_poow_init(stwuct iommu_map_tabwe *iommu,
				unsigned wong num_entwies,
				u32 tabwe_shift,
				void (*wazy_fwush)(stwuct iommu_map_tabwe *),
				boow wawge_poow, u32 npoows,
				boow skip_span_boundawy_check);

extewn unsigned wong iommu_tbw_wange_awwoc(stwuct device *dev,
					   stwuct iommu_map_tabwe *iommu,
					   unsigned wong npages,
					   unsigned wong *handwe,
					   unsigned wong mask,
					   unsigned int awign_owdew);

extewn void iommu_tbw_wange_fwee(stwuct iommu_map_tabwe *iommu,
				 u64 dma_addw, unsigned wong npages,
				 unsigned wong entwy);

#endif
