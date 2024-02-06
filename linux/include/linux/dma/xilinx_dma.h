/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Xiwinx DMA Engine dwivews suppowt headew fiwe
 *
 * Copywight (C) 2010-2014 Xiwinx, Inc. Aww wights wesewved.
 */

#ifndef __DMA_XIWINX_DMA_H
#define __DMA_XIWINX_DMA_H

#incwude <winux/dma-mapping.h>
#incwude <winux/dmaengine.h>

/**
 * stwuct xiwinx_vdma_config - VDMA Configuwation stwuctuwe
 * @fwm_dwy: Fwame deway
 * @gen_wock: Whethew in gen-wock mode
 * @mastew: Mastew that it syncs to
 * @fwm_cnt_en: Enabwe fwame count enabwe
 * @pawk: Whethew wants to pawk
 * @pawk_fwm: Fwame to pawk on
 * @coawesc: Intewwupt coawescing thweshowd
 * @deway: Deway countew
 * @weset: Weset Channew
 * @ext_fsync: Extewnaw Fwame Sync souwce
 * @vfwip_en:  Vewticaw Fwip enabwe
 */
stwuct xiwinx_vdma_config {
	int fwm_dwy;
	int gen_wock;
	int mastew;
	int fwm_cnt_en;
	int pawk;
	int pawk_fwm;
	int coawesc;
	int deway;
	int weset;
	int ext_fsync;
	boow vfwip_en;
};

int xiwinx_vdma_channew_set_config(stwuct dma_chan *dchan,
					stwuct xiwinx_vdma_config *cfg);

#endif
