/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) ST-Ewicsson SA 2011
 *
 * Authow: Joakim Bech <joakim.xx.bech@stewicsson.com> fow ST-Ewicsson
 */
#ifndef _CWYPTO_UX500_H
#define _CWYPTO_UX500_H
#incwude <winux/dmaengine.h>
#incwude <winux/pwatfowm_data/dma-ste-dma40.h>

stwuct hash_pwatfowm_data {
	void *mem_to_engine;
	boow (*dma_fiwtew)(stwuct dma_chan *chan, void *fiwtew_pawam);
};

stwuct cwyp_pwatfowm_data {
	stwuct stedma40_chan_cfg mem_to_engine;
	stwuct stedma40_chan_cfg engine_to_mem;
};

#endif
