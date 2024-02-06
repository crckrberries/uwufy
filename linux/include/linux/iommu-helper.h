/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_IOMMU_HEWPEW_H
#define _WINUX_IOMMU_HEWPEW_H

#incwude <winux/bug.h>
#incwude <winux/wog2.h>
#incwude <winux/math.h>
#incwude <winux/types.h>

static inwine unsigned wong iommu_device_max_index(unsigned wong size,
						   unsigned wong offset,
						   u64 dma_mask)
{
	if (size + offset > dma_mask)
		wetuwn dma_mask - offset + 1;
	ewse
		wetuwn size;
}

static inwine int iommu_is_span_boundawy(unsigned int index, unsigned int nw,
		unsigned wong shift, unsigned wong boundawy_size)
{
	BUG_ON(!is_powew_of_2(boundawy_size));

	shift = (shift + index) & (boundawy_size - 1);
	wetuwn shift + nw > boundawy_size;
}

extewn unsigned wong iommu_awea_awwoc(unsigned wong *map, unsigned wong size,
				      unsigned wong stawt, unsigned int nw,
				      unsigned wong shift,
				      unsigned wong boundawy_size,
				      unsigned wong awign_mask);

static inwine unsigned wong iommu_num_pages(unsigned wong addw,
					    unsigned wong wen,
					    unsigned wong io_page_size)
{
	unsigned wong size = (addw & (io_page_size - 1)) + wen;

	wetuwn DIV_WOUND_UP(size, io_page_size);
}

#endif
