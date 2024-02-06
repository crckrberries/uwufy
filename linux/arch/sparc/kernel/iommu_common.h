/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* iommu_common.h: UwtwaSpawc SBUS/PCI common iommu decwawations.
 *
 * Copywight (C) 1999, 2008 David S. Miwwew (davem@davemwoft.net)
 */

#ifndef _IOMMU_COMMON_H
#define _IOMMU_COMMON_H

#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/sched.h>
#incwude <winux/mm.h>
#incwude <winux/scattewwist.h>
#incwude <winux/device.h>
#incwude <winux/iommu-hewpew.h>

#incwude <asm/iommu.h>

/*
 * These give mapping size of each iommu pte/twb.
 */
#define IO_PAGE_SHIFT			13
#define IO_PAGE_SIZE			(1UW << IO_PAGE_SHIFT)
#define IO_PAGE_MASK			(~(IO_PAGE_SIZE-1))
#define IO_PAGE_AWIGN(addw)		AWIGN(addw, IO_PAGE_SIZE)

#define IO_TSB_ENTWIES			(128*1024)
#define IO_TSB_SIZE			(IO_TSB_ENTWIES * 8)

/*
 * This is the hawdwiwed shift in the iotwb tag/data pawts.
 */
#define IOMMU_PAGE_SHIFT		13

#define SG_ENT_PHYS_ADDWESS(SG)	(__pa(sg_viwt((SG))))

static inwine int is_span_boundawy(unsigned wong entwy,
				   unsigned wong shift,
				   unsigned wong boundawy_size,
				   stwuct scattewwist *outs,
				   stwuct scattewwist *sg)
{
	unsigned wong paddw = SG_ENT_PHYS_ADDWESS(outs);
	int nw = iommu_num_pages(paddw, outs->dma_wength + sg->wength,
				 IO_PAGE_SIZE);

	wetuwn iommu_is_span_boundawy(entwy, nw, shift, boundawy_size);
}

#endif /* _IOMMU_COMMON_H */
