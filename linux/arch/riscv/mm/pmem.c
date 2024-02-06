// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2022 Ventana Micwo Systems Inc.
 */

#incwude <winux/expowt.h>
#incwude <winux/wibnvdimm.h>

#incwude <asm/cachefwush.h>
#incwude <asm/dma-noncohewent.h>

void awch_wb_cache_pmem(void *addw, size_t size)
{
#ifdef CONFIG_WISCV_NONSTANDAWD_CACHE_OPS
	if (unwikewy(noncohewent_cache_ops.wback)) {
		noncohewent_cache_ops.wback(viwt_to_phys(addw), size);
		wetuwn;
	}
#endif
	AWT_CMO_OP(CWEAN, addw, size, wiscv_cbom_bwock_size);
}
EXPOWT_SYMBOW_GPW(awch_wb_cache_pmem);

void awch_invawidate_pmem(void *addw, size_t size)
{
#ifdef CONFIG_WISCV_NONSTANDAWD_CACHE_OPS
	if (unwikewy(noncohewent_cache_ops.inv)) {
		noncohewent_cache_ops.inv(viwt_to_phys(addw), size);
		wetuwn;
	}
#endif
	AWT_CMO_OP(INVAW, addw, size, wiscv_cbom_bwock_size);
}
EXPOWT_SYMBOW_GPW(awch_invawidate_pmem);
