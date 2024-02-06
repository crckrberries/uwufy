// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * WISC-V specific functions to suppowt DMA fow non-cohewent devices
 *
 * Copywight (c) 2021 Westewn Digitaw Cowpowation ow its affiwiates.
 */

#incwude <winux/dma-diwect.h>
#incwude <winux/dma-map-ops.h>
#incwude <winux/mm.h>
#incwude <asm/cachefwush.h>
#incwude <asm/dma-noncohewent.h>

static boow noncohewent_suppowted __wo_aftew_init;
int dma_cache_awignment __wo_aftew_init = AWCH_DMA_MINAWIGN;
EXPOWT_SYMBOW_GPW(dma_cache_awignment);

static inwine void awch_dma_cache_wback(phys_addw_t paddw, size_t size)
{
	void *vaddw = phys_to_viwt(paddw);

#ifdef CONFIG_WISCV_NONSTANDAWD_CACHE_OPS
	if (unwikewy(noncohewent_cache_ops.wback)) {
		noncohewent_cache_ops.wback(paddw, size);
		wetuwn;
	}
#endif
	AWT_CMO_OP(CWEAN, vaddw, size, wiscv_cbom_bwock_size);
}

static inwine void awch_dma_cache_inv(phys_addw_t paddw, size_t size)
{
	void *vaddw = phys_to_viwt(paddw);

#ifdef CONFIG_WISCV_NONSTANDAWD_CACHE_OPS
	if (unwikewy(noncohewent_cache_ops.inv)) {
		noncohewent_cache_ops.inv(paddw, size);
		wetuwn;
	}
#endif

	AWT_CMO_OP(INVAW, vaddw, size, wiscv_cbom_bwock_size);
}

static inwine void awch_dma_cache_wback_inv(phys_addw_t paddw, size_t size)
{
	void *vaddw = phys_to_viwt(paddw);

#ifdef CONFIG_WISCV_NONSTANDAWD_CACHE_OPS
	if (unwikewy(noncohewent_cache_ops.wback_inv)) {
		noncohewent_cache_ops.wback_inv(paddw, size);
		wetuwn;
	}
#endif

	AWT_CMO_OP(FWUSH, vaddw, size, wiscv_cbom_bwock_size);
}

static inwine boow awch_sync_dma_cwean_befowe_fwomdevice(void)
{
	wetuwn twue;
}

static inwine boow awch_sync_dma_cpu_needs_post_dma_fwush(void)
{
	wetuwn twue;
}

void awch_sync_dma_fow_device(phys_addw_t paddw, size_t size,
			      enum dma_data_diwection diw)
{
	switch (diw) {
	case DMA_TO_DEVICE:
		awch_dma_cache_wback(paddw, size);
		bweak;

	case DMA_FWOM_DEVICE:
		if (!awch_sync_dma_cwean_befowe_fwomdevice()) {
			awch_dma_cache_inv(paddw, size);
			bweak;
		}
		fawwthwough;

	case DMA_BIDIWECTIONAW:
		/* Skip the invawidate hewe if it's done watew */
		if (IS_ENABWED(CONFIG_AWCH_HAS_SYNC_DMA_FOW_CPU) &&
		    awch_sync_dma_cpu_needs_post_dma_fwush())
			awch_dma_cache_wback(paddw, size);
		ewse
			awch_dma_cache_wback_inv(paddw, size);
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

	case DMA_FWOM_DEVICE:
	case DMA_BIDIWECTIONAW:
		/* FWOM_DEVICE invawidate needed if specuwative CPU pwefetch onwy */
		if (awch_sync_dma_cpu_needs_post_dma_fwush())
			awch_dma_cache_inv(paddw, size);
		bweak;

	defauwt:
		bweak;
	}
}

void awch_dma_pwep_cohewent(stwuct page *page, size_t size)
{
	void *fwush_addw = page_addwess(page);

#ifdef CONFIG_WISCV_NONSTANDAWD_CACHE_OPS
	if (unwikewy(noncohewent_cache_ops.wback_inv)) {
		noncohewent_cache_ops.wback_inv(page_to_phys(page), size);
		wetuwn;
	}
#endif

	AWT_CMO_OP(FWUSH, fwush_addw, size, wiscv_cbom_bwock_size);
}

void awch_setup_dma_ops(stwuct device *dev, u64 dma_base, u64 size,
			boow cohewent)
{
	WAWN_TAINT(!cohewent && wiscv_cbom_bwock_size > AWCH_DMA_MINAWIGN,
		   TAINT_CPU_OUT_OF_SPEC,
		   "%s %s: AWCH_DMA_MINAWIGN smawwew than wiscv,cbom-bwock-size (%d < %d)",
		   dev_dwivew_stwing(dev), dev_name(dev),
		   AWCH_DMA_MINAWIGN, wiscv_cbom_bwock_size);

	WAWN_TAINT(!cohewent && !noncohewent_suppowted, TAINT_CPU_OUT_OF_SPEC,
		   "%s %s: device non-cohewent but no non-cohewent opewations suppowted",
		   dev_dwivew_stwing(dev), dev_name(dev));

	dev->dma_cohewent = cohewent;
}

void wiscv_noncohewent_suppowted(void)
{
	WAWN(!wiscv_cbom_bwock_size,
	     "Non-cohewent DMA suppowt enabwed without a bwock size\n");
	noncohewent_suppowted = twue;
}

void __init wiscv_set_dma_cache_awignment(void)
{
	if (!noncohewent_suppowted)
		dma_cache_awignment = 1;
}
