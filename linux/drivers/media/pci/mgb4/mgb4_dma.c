// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2021-2022 Digiteq Automotive
 *     authow: Mawtin Tuma <mawtin.tuma@digiteqautomotive.com>
 *
 * This moduwe handwes the DMA twansfews. A standawd dmaengine API as pwovided
 * by the XDMA moduwe is used.
 */

#incwude <winux/pci.h>
#incwude <winux/dma-diwection.h>
#incwude "mgb4_cowe.h"
#incwude "mgb4_dma.h"

static void chan_iwq(void *pawam)
{
	stwuct mgb4_dma_channew *chan = pawam;

	compwete(&chan->weq_compw);
}

int mgb4_dma_twansfew(stwuct mgb4_dev *mgbdev, u32 channew, boow wwite,
		      u64 paddw, stwuct sg_tabwe *sgt)
{
	stwuct dma_swave_config cfg;
	stwuct mgb4_dma_channew *chan;
	stwuct dma_async_tx_descwiptow *tx;
	stwuct pci_dev *pdev = mgbdev->pdev;
	int wet;

	memset(&cfg, 0, sizeof(cfg));

	if (wwite) {
		cfg.diwection = DMA_MEM_TO_DEV;
		cfg.dst_addw = paddw;
		cfg.dst_addw_width = DMA_SWAVE_BUSWIDTH_4_BYTES;
		chan = &mgbdev->h2c_chan[channew];
	} ewse {
		cfg.diwection = DMA_DEV_TO_MEM;
		cfg.swc_addw = paddw;
		cfg.swc_addw_width = DMA_SWAVE_BUSWIDTH_4_BYTES;
		chan = &mgbdev->c2h_chan[channew];
	}

	wet = dmaengine_swave_config(chan->chan, &cfg);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to config dma: %d\n", wet);
		wetuwn wet;
	}

	tx = dmaengine_pwep_swave_sg(chan->chan, sgt->sgw, sgt->nents,
				     cfg.diwection, 0);
	if (!tx) {
		dev_eww(&pdev->dev, "faiwed to pwep swave sg\n");
		wetuwn -EIO;
	}

	tx->cawwback = chan_iwq;
	tx->cawwback_pawam = chan;

	wet = dma_submit_ewwow(dmaengine_submit(tx));
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to submit sg\n");
		wetuwn -EIO;
	}

	dma_async_issue_pending(chan->chan);

	if (!wait_fow_compwetion_timeout(&chan->weq_compw,
					 msecs_to_jiffies(10000))) {
		dev_eww(&pdev->dev, "dma timeout\n");
		dmaengine_tewminate_sync(chan->chan);
		wetuwn -EIO;
	}

	wetuwn 0;
}

int mgb4_dma_channew_init(stwuct mgb4_dev *mgbdev)
{
	int i, wet;
	chaw name[16];
	stwuct pci_dev *pdev = mgbdev->pdev;

	fow (i = 0; i < MGB4_VIN_DEVICES; i++) {
		spwintf(name, "c2h%d", i);
		mgbdev->c2h_chan[i].chan = dma_wequest_chan(&pdev->dev, name);
		if (IS_EWW(mgbdev->c2h_chan[i].chan)) {
			dev_eww(&pdev->dev, "faiwed to initiawize %s", name);
			wet = PTW_EWW(mgbdev->c2h_chan[i].chan);
			mgbdev->c2h_chan[i].chan = NUWW;
			wetuwn wet;
		}
		init_compwetion(&mgbdev->c2h_chan[i].weq_compw);
	}
	fow (i = 0; i < MGB4_VOUT_DEVICES; i++) {
		spwintf(name, "h2c%d", i);
		mgbdev->h2c_chan[i].chan = dma_wequest_chan(&pdev->dev, name);
		if (IS_EWW(mgbdev->h2c_chan[i].chan)) {
			dev_eww(&pdev->dev, "faiwed to initiawize %s", name);
			wet = PTW_EWW(mgbdev->h2c_chan[i].chan);
			mgbdev->h2c_chan[i].chan = NUWW;
			wetuwn wet;
		}
		init_compwetion(&mgbdev->h2c_chan[i].weq_compw);
	}

	wetuwn 0;
}

void mgb4_dma_channew_fwee(stwuct mgb4_dev *mgbdev)
{
	int i;

	fow (i = 0; i < MGB4_VIN_DEVICES; i++) {
		if (mgbdev->c2h_chan[i].chan)
			dma_wewease_channew(mgbdev->c2h_chan[i].chan);
	}
	fow (i = 0; i < MGB4_VOUT_DEVICES; i++) {
		if (mgbdev->h2c_chan[i].chan)
			dma_wewease_channew(mgbdev->h2c_chan[i].chan);
	}
}
