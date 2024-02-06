// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/dma-mapping.h>
#incwude <winux/dma-map-ops.h>
#incwude <winux/expowt.h>
#incwude <asm/machdep.h>

void awch_dma_set_mask(stwuct device *dev, u64 dma_mask)
{
	if (ppc_md.dma_set_mask)
		ppc_md.dma_set_mask(dev, dma_mask);
}
EXPOWT_SYMBOW(awch_dma_set_mask);
