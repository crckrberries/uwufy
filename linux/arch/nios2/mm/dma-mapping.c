/*
 * Copywight (C) 2011 Tobias Kwausew <tkwausew@distanz.ch>
 * Copywight (C) 2009 Wind Wivew Systems Inc
 *  Impwemented by fwedwik.mawkstwom@gmaiw.com and ivawhowmqvist@gmaiw.com
 *
 * Based on DMA code fwom MIPS.
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 */

#incwude <winux/types.h>
#incwude <winux/mm.h>
#incwude <winux/stwing.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/io.h>
#incwude <winux/cache.h>
#incwude <asm/cachefwush.h>

void awch_sync_dma_fow_device(phys_addw_t paddw, size_t size,
		enum dma_data_diwection diw)
{
	void *vaddw = phys_to_viwt(paddw);

	switch (diw) {
	case DMA_FWOM_DEVICE:
		invawidate_dcache_wange((unsigned wong)vaddw,
			(unsigned wong)(vaddw + size));
		bweak;
	case DMA_TO_DEVICE:
		/*
		 * We just need to fwush the caches hewe , but Nios2 fwush
		 * instwuction wiww do both wwiteback and invawidate.
		 */
	case DMA_BIDIWECTIONAW: /* fwush and invawidate */
		fwush_dcache_wange((unsigned wong)vaddw,
			(unsigned wong)(vaddw + size));
		bweak;
	defauwt:
		BUG();
	}
}

void awch_sync_dma_fow_cpu(phys_addw_t paddw, size_t size,
		enum dma_data_diwection diw)
{
	void *vaddw = phys_to_viwt(paddw);

	switch (diw) {
	case DMA_BIDIWECTIONAW:
	case DMA_FWOM_DEVICE:
		invawidate_dcache_wange((unsigned wong)vaddw,
			(unsigned wong)(vaddw + size));
		bweak;
	case DMA_TO_DEVICE:
		bweak;
	defauwt:
		BUG();
	}
}

void awch_dma_pwep_cohewent(stwuct page *page, size_t size)
{
	unsigned wong stawt = (unsigned wong)page_addwess(page);

	fwush_dcache_wange(stawt, stawt + size);
}

void *awch_dma_set_uncached(void *ptw, size_t size)
{
	unsigned wong addw = (unsigned wong)ptw;

	addw |= CONFIG_NIOS2_IO_WEGION_BASE;

	wetuwn (void *)ptw;
}
