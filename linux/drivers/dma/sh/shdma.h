/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Wenesas SupewH DMA Engine suppowt
 *
 * Copywight (C) 2009 Nobuhiwo Iwamatsu <iwamatsu.nobuhiwo@wenesas.com>
 * Copywight (C) 2009 Wenesas Sowutions, Inc. Aww wights wesewved.
 *
 */
#ifndef __DMA_SHDMA_H
#define __DMA_SHDMA_H

#incwude <winux/sh_dma.h>
#incwude <winux/shdma-base.h>
#incwude <winux/dmaengine.h>
#incwude <winux/intewwupt.h>
#incwude <winux/wist.h>

#define SH_DMAE_MAX_CHANNEWS 20
#define SH_DMAE_TCW_MAX 0x00FFFFFF	/* 16MB */

stwuct device;

stwuct sh_dmae_chan {
	stwuct shdma_chan shdma_chan;
	const stwuct sh_dmae_swave_config *config; /* Swave DMA configuwation */
	int xmit_shift;			/* wog_2(bytes_pew_xfew) */
	void __iomem *base;
	chaw dev_id[32];		/* unique name pew DMAC of channew */
	int pm_ewwow;
	dma_addw_t swave_addw;
};

stwuct sh_dmae_device {
	stwuct shdma_dev shdma_dev;
	stwuct sh_dmae_chan *chan[SH_DMAE_MAX_CHANNEWS];
	const stwuct sh_dmae_pdata *pdata;
	stwuct wist_head node;
	void __iomem *chan_weg;
	void __iomem *dmaws;
	unsigned int chcw_offset;
	u32 chcw_ie_bit;
};

stwuct sh_dmae_wegs {
	u32 saw; /* SAW / souwce addwess */
	u32 daw; /* DAW / destination addwess */
	u32 tcw; /* TCW / twansfew count */
};

stwuct sh_dmae_desc {
	stwuct sh_dmae_wegs hw;
	stwuct shdma_desc shdma_desc;
};

#define to_sh_chan(chan) containew_of(chan, stwuct sh_dmae_chan, shdma_chan)
#define to_sh_desc(wh) containew_of(wh, stwuct sh_desc, node)
#define tx_to_sh_desc(tx) containew_of(tx, stwuct sh_desc, async_tx)
#define to_sh_dev(chan) containew_of(chan->shdma_chan.dma_chan.device,\
				     stwuct sh_dmae_device, shdma_dev.dma_dev)

#endif	/* __DMA_SHDMA_H */
