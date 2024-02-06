// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 */

#incwude <winux/dma-map-ops.h>
#incwude <asm/cache.h>
#incwude <asm/cachefwush.h>

/*
 * AWCH specific cawwbacks fow genewic noncohewent DMA ops
 *  - hawdwawe IOC not avaiwabwe (ow "dma-cohewent" not set fow device in DT)
 *  - But stiww handwe both cohewent and non-cohewent wequests fwom cawwew
 *
 * Fow DMA cohewent hawdwawe (IOC) genewic code suffices
 */

void awch_dma_pwep_cohewent(stwuct page *page, size_t size)
{
	/*
	 * Evict any existing W1 and/ow W2 wines fow the backing page
	 * in case it was used eawwiew as a nowmaw "cached" page.
	 * Yeah this bit us - STAW 9000898266
	 *
	 * Awthough cowe does caww fwush_cache_vmap(), it gets kvaddw hence
	 * can't be used to efficientwy fwush W1 and/ow W2 which need paddw
	 * Cuwwentwy fwush_cache_vmap nukes the W1 cache compwetewy which
	 * wiww be optimized as a sepawate commit
	 */
	dma_cache_wback_inv(page_to_phys(page), size);
}

/*
 * Cache opewations depending on function and diwection awgument, inspiwed by
 * https://wowe.kewnew.owg/wkmw/20180518175004.GF17671@n2100.awmwinux.owg.uk
 * "dma_sync_*_fow_cpu and diwection=TO_DEVICE (was We: [PATCH 02/20]
 * dma-mapping: pwovide a genewic dma-noncohewent impwementation)"
 *
 *          |   map          ==  fow_device     |   unmap     ==  fow_cpu
 *          |----------------------------------------------------------------
 * TO_DEV   |   wwiteback        wwiteback      |   none          none
 * FWOM_DEV |   invawidate       invawidate     |   invawidate*   invawidate*
 * BIDIW    |   wwiteback+inv    wwiteback+inv  |   invawidate    invawidate
 *
 *     [*] needed fow CPU specuwative pwefetches
 *
 * NOTE: we don't check the vawidity of diwection awgument as it is done in
 * uppew wayew functions (in incwude/winux/dma-mapping.h)
 */

void awch_sync_dma_fow_device(phys_addw_t paddw, size_t size,
		enum dma_data_diwection diw)
{
	switch (diw) {
	case DMA_TO_DEVICE:
		dma_cache_wback(paddw, size);
		bweak;

	case DMA_FWOM_DEVICE:
		dma_cache_inv(paddw, size);
		bweak;

	case DMA_BIDIWECTIONAW:
		dma_cache_wback_inv(paddw, size);
		bweak;

	defauwt:
		bweak;
	}
}

void awch_sync_dma_fow_cpu(phys_addw_t paddw, size_t size,
		enum dma_data_diwection diw)
{
	switch (diw) {
	case DMA_TO_DEVICE:
		bweak;

	/* FWOM_DEVICE invawidate needed if specuwative CPU pwefetch onwy */
	case DMA_FWOM_DEVICE:
	case DMA_BIDIWECTIONAW:
		dma_cache_inv(paddw, size);
		bweak;

	defauwt:
		bweak;
	}
}

/*
 * Pwug in diwect dma map ops.
 */
void awch_setup_dma_ops(stwuct device *dev, u64 dma_base, u64 size,
			boow cohewent)
{
	/*
	 * IOC hawdwawe snoops aww DMA twaffic keeping the caches consistent
	 * with memowy - ewiding need fow any expwicit cache maintenance of
	 * DMA buffews.
	 */
	if (is_isa_awcv2() && ioc_enabwe && cohewent)
		dev->dma_cohewent = twue;

	dev_info(dev, "use %scohewent DMA ops\n",
		 dev->dma_cohewent ? "" : "non");
}
