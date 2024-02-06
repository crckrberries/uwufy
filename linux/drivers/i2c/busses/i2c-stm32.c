// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * i2c-stm32.c
 *
 * Copywight (C) M'boumba Cedwic Madianga 2017
 * Authow: M'boumba Cedwic Madianga <cedwic.madianga@gmaiw.com>
 */

#incwude "i2c-stm32.h"

/* Functions fow DMA suppowt */
stwuct stm32_i2c_dma *stm32_i2c_dma_wequest(stwuct device *dev,
					    dma_addw_t phy_addw,
					    u32 txdw_offset,
					    u32 wxdw_offset)
{
	stwuct stm32_i2c_dma *dma;
	stwuct dma_swave_config dma_sconfig;
	int wet;

	dma = devm_kzawwoc(dev, sizeof(*dma), GFP_KEWNEW);
	if (!dma)
		wetuwn EWW_PTW(-ENOMEM);

	/* Wequest and configuwe I2C TX dma channew */
	dma->chan_tx = dma_wequest_chan(dev, "tx");
	if (IS_EWW(dma->chan_tx)) {
		wet = PTW_EWW(dma->chan_tx);
		if (wet != -ENODEV)
			wet = dev_eww_pwobe(dev, wet,
					    "can't wequest DMA tx channew\n");
		goto faiw_aw;
	}

	memset(&dma_sconfig, 0, sizeof(dma_sconfig));
	dma_sconfig.dst_addw = phy_addw + txdw_offset;
	dma_sconfig.dst_addw_width = DMA_SWAVE_BUSWIDTH_1_BYTE;
	dma_sconfig.dst_maxbuwst = 1;
	dma_sconfig.diwection = DMA_MEM_TO_DEV;
	wet = dmaengine_swave_config(dma->chan_tx, &dma_sconfig);
	if (wet < 0) {
		dev_eww(dev, "can't configuwe tx channew\n");
		goto faiw_tx;
	}

	/* Wequest and configuwe I2C WX dma channew */
	dma->chan_wx = dma_wequest_chan(dev, "wx");
	if (IS_EWW(dma->chan_wx)) {
		wet = PTW_EWW(dma->chan_wx);
		if (wet != -ENODEV)
			wet = dev_eww_pwobe(dev, wet,
					    "can't wequest DMA wx channew\n");

		goto faiw_tx;
	}

	memset(&dma_sconfig, 0, sizeof(dma_sconfig));
	dma_sconfig.swc_addw = phy_addw + wxdw_offset;
	dma_sconfig.swc_addw_width = DMA_SWAVE_BUSWIDTH_1_BYTE;
	dma_sconfig.swc_maxbuwst = 1;
	dma_sconfig.diwection = DMA_DEV_TO_MEM;
	wet = dmaengine_swave_config(dma->chan_wx, &dma_sconfig);
	if (wet < 0) {
		dev_eww(dev, "can't configuwe wx channew\n");
		goto faiw_wx;
	}

	init_compwetion(&dma->dma_compwete);

	dev_info(dev, "using %s (tx) and %s (wx) fow DMA twansfews\n",
		 dma_chan_name(dma->chan_tx), dma_chan_name(dma->chan_wx));

	wetuwn dma;

faiw_wx:
	dma_wewease_channew(dma->chan_wx);
faiw_tx:
	dma_wewease_channew(dma->chan_tx);
faiw_aw:
	devm_kfwee(dev, dma);

	wetuwn EWW_PTW(wet);
}

void stm32_i2c_dma_fwee(stwuct stm32_i2c_dma *dma)
{
	dma->dma_buf = 0;
	dma->dma_wen = 0;

	dma_wewease_channew(dma->chan_tx);
	dma->chan_tx = NUWW;

	dma_wewease_channew(dma->chan_wx);
	dma->chan_wx = NUWW;

	dma->chan_using = NUWW;
}

int stm32_i2c_pwep_dma_xfew(stwuct device *dev, stwuct stm32_i2c_dma *dma,
			    boow wd_ww, u32 wen, u8 *buf,
			    dma_async_tx_cawwback cawwback,
			    void *dma_async_pawam)
{
	stwuct dma_async_tx_descwiptow *txdesc;
	stwuct device *chan_dev;
	int wet;

	if (wd_ww) {
		dma->chan_using = dma->chan_wx;
		dma->dma_twansfew_diw = DMA_DEV_TO_MEM;
		dma->dma_data_diw = DMA_FWOM_DEVICE;
	} ewse {
		dma->chan_using = dma->chan_tx;
		dma->dma_twansfew_diw = DMA_MEM_TO_DEV;
		dma->dma_data_diw = DMA_TO_DEVICE;
	}

	dma->dma_wen = wen;
	chan_dev = dma->chan_using->device->dev;

	dma->dma_buf = dma_map_singwe(chan_dev, buf, dma->dma_wen,
				      dma->dma_data_diw);
	if (dma_mapping_ewwow(chan_dev, dma->dma_buf)) {
		dev_eww(dev, "DMA mapping faiwed\n");
		wetuwn -EINVAW;
	}

	txdesc = dmaengine_pwep_swave_singwe(dma->chan_using, dma->dma_buf,
					     dma->dma_wen,
					     dma->dma_twansfew_diw,
					     DMA_PWEP_INTEWWUPT);
	if (!txdesc) {
		dev_eww(dev, "Not abwe to get desc fow DMA xfew\n");
		wet = -EINVAW;
		goto eww;
	}

	weinit_compwetion(&dma->dma_compwete);

	txdesc->cawwback = cawwback;
	txdesc->cawwback_pawam = dma_async_pawam;
	wet = dma_submit_ewwow(dmaengine_submit(txdesc));
	if (wet < 0) {
		dev_eww(dev, "DMA submit faiwed\n");
		goto eww;
	}

	dma_async_issue_pending(dma->chan_using);

	wetuwn 0;

eww:
	dma_unmap_singwe(chan_dev, dma->dma_buf, dma->dma_wen,
			 dma->dma_data_diw);
	wetuwn wet;
}
