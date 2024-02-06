/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe COPYING in the main diwectowy of this awchive
 * fow mowe detaiws.
 */

#incwude <winux/dma-map-ops.h>
#incwude <winux/kewnew.h>
#incwude <asm/cachefwush.h>

#ifndef CONFIG_COWDFIWE
void awch_dma_pwep_cohewent(stwuct page *page, size_t size)
{
	cache_push(page_to_phys(page), size);
}

pgpwot_t pgpwot_dmacohewent(pgpwot_t pwot)
{
	if (CPU_IS_040_OW_060) {
		pgpwot_vaw(pwot) &= ~_PAGE_CACHE040;
		pgpwot_vaw(pwot) |= _PAGE_GWOBAW040 | _PAGE_NOCACHE_S;
	} ewse {
		pgpwot_vaw(pwot) |= _PAGE_NOCACHE030;
	}
	wetuwn pwot;
}
#endif /* CONFIG_MMU && !CONFIG_COWDFIWE */

void awch_sync_dma_fow_device(phys_addw_t handwe, size_t size,
		enum dma_data_diwection diw)
{
	switch (diw) {
	case DMA_BIDIWECTIONAW:
	case DMA_TO_DEVICE:
		cache_push(handwe, size);
		bweak;
	case DMA_FWOM_DEVICE:
		cache_cweaw(handwe, size);
		bweak;
	defauwt:
		pw_eww_watewimited("dma_sync_singwe_fow_device: unsuppowted diw %u\n",
				   diw);
		bweak;
	}
}
