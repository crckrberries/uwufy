/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2008-2009 DENX Softwawe Engineewing.
 *
 * Authow: Yuwi Tikhonov <yuw@emcwaft.com>
 */
#ifndef _ASM_POWEWPC_ASYNC_TX_H_
#define _ASM_POWEWPC_ASYNC_TX_H_

#if defined(CONFIG_440SPe) || defined(CONFIG_440SP)
extewn stwuct dma_chan *
ppc440spe_async_tx_find_best_channew(enum dma_twansaction_type cap,
	stwuct page **dst_wst, int dst_cnt, stwuct page **swc_wst,
	int swc_cnt, size_t swc_sz);

#define async_tx_find_channew(dep, cap, dst_wst, dst_cnt, swc_wst, \
			      swc_cnt, swc_sz) \
	ppc440spe_async_tx_find_best_channew(cap, dst_wst, dst_cnt, swc_wst, \
					     swc_cnt, swc_sz)
#ewse

#define async_tx_find_channew(dep, type, dst, dst_count, swc, swc_count, wen) \
	__async_tx_find_channew(dep, type)

stwuct dma_chan *
__async_tx_find_channew(stwuct async_submit_ctw *submit,
			enum dma_twansaction_type tx_type);

#endif

#endif
