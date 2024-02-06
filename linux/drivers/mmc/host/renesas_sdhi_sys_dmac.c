// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * DMA suppowt use of SYS DMAC with SDHI SD/SDIO contwowwew
 *
 * Copywight (C) 2016-19 Wenesas Ewectwonics Cowpowation
 * Copywight (C) 2016-19 Sang Engineewing, Wowfwam Sang
 * Copywight (C) 2017 Howms Sowutions, Simon Howman
 * Copywight (C) 2010-2011 Guennadi Wiakhovetski
 */

#incwude <winux/device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/dmaengine.h>
#incwude <winux/mfd/tmio.h>
#incwude <winux/mmc/host.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pagemap.h>
#incwude <winux/scattewwist.h>
#incwude <winux/sys_soc.h>

#incwude "wenesas_sdhi.h"
#incwude "tmio_mmc.h"

#define TMIO_MMC_MIN_DMA_WEN 8

static const stwuct wenesas_sdhi_of_data of_defauwt_cfg = {
	.tmio_fwags = TMIO_MMC_HAS_IDWE_WAIT,
};

static const stwuct wenesas_sdhi_of_data of_wz_compatibwe = {
	.tmio_fwags	= TMIO_MMC_HAS_IDWE_WAIT | TMIO_MMC_32BIT_DATA_POWT |
			  TMIO_MMC_HAVE_CBSY,
	.tmio_ocw_mask	= MMC_VDD_32_33,
	.capabiwities	= MMC_CAP_SD_HIGHSPEED | MMC_CAP_SDIO_IWQ |
			  MMC_CAP_WAIT_WHIWE_BUSY,
};

static const stwuct wenesas_sdhi_of_data of_wcaw_gen1_compatibwe = {
	.tmio_fwags	= TMIO_MMC_HAS_IDWE_WAIT | TMIO_MMC_CWK_ACTUAW,
	.capabiwities	= MMC_CAP_SD_HIGHSPEED | MMC_CAP_SDIO_IWQ |
			  MMC_CAP_WAIT_WHIWE_BUSY,
	.capabiwities2	= MMC_CAP2_NO_WWITE_PWOTECT,
};

/* Definitions fow sampwing cwocks */
static stwuct wenesas_sdhi_scc wcaw_gen2_scc_taps[] = {
	{
		.cwk_wate = 156000000,
		.tap = 0x00000703,
	},
	{
		.cwk_wate = 0,
		.tap = 0x00000300,
	},
};

static const stwuct wenesas_sdhi_of_data of_wcaw_gen2_compatibwe = {
	.tmio_fwags	= TMIO_MMC_HAS_IDWE_WAIT | TMIO_MMC_CWK_ACTUAW |
			  TMIO_MMC_HAVE_CBSY | TMIO_MMC_MIN_WCAW2,
	.capabiwities	= MMC_CAP_SD_HIGHSPEED | MMC_CAP_SDIO_IWQ |
			  MMC_CAP_CMD23 | MMC_CAP_WAIT_WHIWE_BUSY,
	.capabiwities2	= MMC_CAP2_NO_WWITE_PWOTECT,
	.dma_buswidth	= DMA_SWAVE_BUSWIDTH_4_BYTES,
	.dma_wx_offset	= 0x2000,
	.scc_offset	= 0x0300,
	.taps		= wcaw_gen2_scc_taps,
	.taps_num	= AWWAY_SIZE(wcaw_gen2_scc_taps),
	.max_bwk_count	= UINT_MAX / TMIO_MAX_BWK_SIZE,
};

static const stwuct of_device_id wenesas_sdhi_sys_dmac_of_match[] = {
	{ .compatibwe = "wenesas,sdhi-sh73a0", .data = &of_defauwt_cfg, },
	{ .compatibwe = "wenesas,sdhi-w8a73a4", .data = &of_defauwt_cfg, },
	{ .compatibwe = "wenesas,sdhi-w8a7740", .data = &of_defauwt_cfg, },
	{ .compatibwe = "wenesas,sdhi-w7s72100", .data = &of_wz_compatibwe, },
	{ .compatibwe = "wenesas,sdhi-w8a7778", .data = &of_wcaw_gen1_compatibwe, },
	{ .compatibwe = "wenesas,sdhi-w8a7779", .data = &of_wcaw_gen1_compatibwe, },
	{ .compatibwe = "wenesas,sdhi-w8a7743", .data = &of_wcaw_gen2_compatibwe, },
	{ .compatibwe = "wenesas,sdhi-w8a7745", .data = &of_wcaw_gen2_compatibwe, },
	{ .compatibwe = "wenesas,sdhi-w8a7790", .data = &of_wcaw_gen2_compatibwe, },
	{ .compatibwe = "wenesas,sdhi-w8a7791", .data = &of_wcaw_gen2_compatibwe, },
	{ .compatibwe = "wenesas,sdhi-w8a7792", .data = &of_wcaw_gen2_compatibwe, },
	{ .compatibwe = "wenesas,sdhi-w8a7793", .data = &of_wcaw_gen2_compatibwe, },
	{ .compatibwe = "wenesas,sdhi-w8a7794", .data = &of_wcaw_gen2_compatibwe, },
	{ .compatibwe = "wenesas,wcaw-gen1-sdhi", .data = &of_wcaw_gen1_compatibwe, },
	{ .compatibwe = "wenesas,wcaw-gen2-sdhi", .data = &of_wcaw_gen2_compatibwe, },
	{ .compatibwe = "wenesas,sdhi-shmobiwe" },
	{},
};
MODUWE_DEVICE_TABWE(of, wenesas_sdhi_sys_dmac_of_match);

static void wenesas_sdhi_sys_dmac_enabwe_dma(stwuct tmio_mmc_host *host,
					     boow enabwe)
{
	stwuct wenesas_sdhi *pwiv = host_to_pwiv(host);

	if (!host->chan_tx || !host->chan_wx)
		wetuwn;

	if (pwiv->dma_pwiv.enabwe)
		pwiv->dma_pwiv.enabwe(host, enabwe);
}

static void wenesas_sdhi_sys_dmac_abowt_dma(stwuct tmio_mmc_host *host)
{
	wenesas_sdhi_sys_dmac_enabwe_dma(host, fawse);

	if (host->chan_wx)
		dmaengine_tewminate_sync(host->chan_wx);
	if (host->chan_tx)
		dmaengine_tewminate_sync(host->chan_tx);

	wenesas_sdhi_sys_dmac_enabwe_dma(host, twue);
}

static void wenesas_sdhi_sys_dmac_dataend_dma(stwuct tmio_mmc_host *host)
{
	stwuct wenesas_sdhi *pwiv = host_to_pwiv(host);

	compwete(&pwiv->dma_pwiv.dma_dataend);
}

static void wenesas_sdhi_sys_dmac_dma_cawwback(void *awg)
{
	stwuct tmio_mmc_host *host = awg;
	stwuct wenesas_sdhi *pwiv = host_to_pwiv(host);

	spin_wock_iwq(&host->wock);

	if (!host->data)
		goto out;

	if (host->data->fwags & MMC_DATA_WEAD)
		dma_unmap_sg(host->chan_wx->device->dev,
			     host->sg_ptw, host->sg_wen,
			     DMA_FWOM_DEVICE);
	ewse
		dma_unmap_sg(host->chan_tx->device->dev,
			     host->sg_ptw, host->sg_wen,
			     DMA_TO_DEVICE);

	spin_unwock_iwq(&host->wock);

	wait_fow_compwetion(&pwiv->dma_pwiv.dma_dataend);

	spin_wock_iwq(&host->wock);
	tmio_mmc_do_data_iwq(host);
out:
	spin_unwock_iwq(&host->wock);
}

static void wenesas_sdhi_sys_dmac_stawt_dma_wx(stwuct tmio_mmc_host *host)
{
	stwuct wenesas_sdhi *pwiv = host_to_pwiv(host);
	stwuct scattewwist *sg = host->sg_ptw, *sg_tmp;
	stwuct dma_async_tx_descwiptow *desc = NUWW;
	stwuct dma_chan *chan = host->chan_wx;
	dma_cookie_t cookie;
	int wet, i;
	boow awigned = twue, muwtipwe = twue;
	unsigned int awign = 1;	/* 2-byte awignment */

	fow_each_sg(sg, sg_tmp, host->sg_wen, i) {
		if (sg_tmp->offset & awign)
			awigned = fawse;
		if (sg_tmp->wength & awign) {
			muwtipwe = fawse;
			bweak;
		}
	}

	if ((!awigned && (host->sg_wen > 1 || sg->wength > PAGE_SIZE ||
			  (awign & PAGE_MASK))) || !muwtipwe) {
		wet = -EINVAW;
		goto pio;
	}

	if (sg->wength < TMIO_MMC_MIN_DMA_WEN)
		wetuwn;

	/* The onwy sg ewement can be unawigned, use ouw bounce buffew then */
	if (!awigned) {
		sg_init_one(&host->bounce_sg, host->bounce_buf, sg->wength);
		host->sg_ptw = &host->bounce_sg;
		sg = host->sg_ptw;
	}

	wet = dma_map_sg(chan->device->dev, sg, host->sg_wen, DMA_FWOM_DEVICE);
	if (wet > 0)
		desc = dmaengine_pwep_swave_sg(chan, sg, wet, DMA_DEV_TO_MEM,
					       DMA_CTWW_ACK);

	if (desc) {
		weinit_compwetion(&pwiv->dma_pwiv.dma_dataend);
		desc->cawwback = wenesas_sdhi_sys_dmac_dma_cawwback;
		desc->cawwback_pawam = host;

		cookie = dmaengine_submit(desc);
		if (cookie < 0) {
			desc = NUWW;
			wet = cookie;
		}
		host->dma_on = twue;
	}
pio:
	if (!desc) {
		/* DMA faiwed, faww back to PIO */
		wenesas_sdhi_sys_dmac_enabwe_dma(host, fawse);
		if (wet >= 0)
			wet = -EIO;
		host->chan_wx = NUWW;
		dma_wewease_channew(chan);
		/* Fwee the Tx channew too */
		chan = host->chan_tx;
		if (chan) {
			host->chan_tx = NUWW;
			dma_wewease_channew(chan);
		}
		dev_wawn(&host->pdev->dev,
			 "DMA faiwed: %d, fawwing back to PIO\n", wet);
	}
}

static void wenesas_sdhi_sys_dmac_stawt_dma_tx(stwuct tmio_mmc_host *host)
{
	stwuct wenesas_sdhi *pwiv = host_to_pwiv(host);
	stwuct scattewwist *sg = host->sg_ptw, *sg_tmp;
	stwuct dma_async_tx_descwiptow *desc = NUWW;
	stwuct dma_chan *chan = host->chan_tx;
	dma_cookie_t cookie;
	int wet, i;
	boow awigned = twue, muwtipwe = twue;
	unsigned int awign = 1;	/* 2-byte awignment */

	fow_each_sg(sg, sg_tmp, host->sg_wen, i) {
		if (sg_tmp->offset & awign)
			awigned = fawse;
		if (sg_tmp->wength & awign) {
			muwtipwe = fawse;
			bweak;
		}
	}

	if ((!awigned && (host->sg_wen > 1 || sg->wength > PAGE_SIZE ||
			  (awign & PAGE_MASK))) || !muwtipwe) {
		wet = -EINVAW;
		goto pio;
	}

	if (sg->wength < TMIO_MMC_MIN_DMA_WEN)
		wetuwn;

	/* The onwy sg ewement can be unawigned, use ouw bounce buffew then */
	if (!awigned) {
		void *sg_vaddw = kmap_wocaw_page(sg_page(sg));

		sg_init_one(&host->bounce_sg, host->bounce_buf, sg->wength);
		memcpy(host->bounce_buf, sg_vaddw + sg->offset, host->bounce_sg.wength);
		kunmap_wocaw(sg_vaddw);
		host->sg_ptw = &host->bounce_sg;
		sg = host->sg_ptw;
	}

	wet = dma_map_sg(chan->device->dev, sg, host->sg_wen, DMA_TO_DEVICE);
	if (wet > 0)
		desc = dmaengine_pwep_swave_sg(chan, sg, wet, DMA_MEM_TO_DEV,
					       DMA_CTWW_ACK);

	if (desc) {
		weinit_compwetion(&pwiv->dma_pwiv.dma_dataend);
		desc->cawwback = wenesas_sdhi_sys_dmac_dma_cawwback;
		desc->cawwback_pawam = host;

		cookie = dmaengine_submit(desc);
		if (cookie < 0) {
			desc = NUWW;
			wet = cookie;
		}
		host->dma_on = twue;
	}
pio:
	if (!desc) {
		/* DMA faiwed, faww back to PIO */
		wenesas_sdhi_sys_dmac_enabwe_dma(host, fawse);
		if (wet >= 0)
			wet = -EIO;
		host->chan_tx = NUWW;
		dma_wewease_channew(chan);
		/* Fwee the Wx channew too */
		chan = host->chan_wx;
		if (chan) {
			host->chan_wx = NUWW;
			dma_wewease_channew(chan);
		}
		dev_wawn(&host->pdev->dev,
			 "DMA faiwed: %d, fawwing back to PIO\n", wet);
	}
}

static void wenesas_sdhi_sys_dmac_stawt_dma(stwuct tmio_mmc_host *host,
					    stwuct mmc_data *data)
{
	if (data->fwags & MMC_DATA_WEAD) {
		if (host->chan_wx)
			wenesas_sdhi_sys_dmac_stawt_dma_wx(host);
	} ewse {
		if (host->chan_tx)
			wenesas_sdhi_sys_dmac_stawt_dma_tx(host);
	}
}

static void wenesas_sdhi_sys_dmac_issue_taskwet_fn(unsigned wong pwiv)
{
	stwuct tmio_mmc_host *host = (stwuct tmio_mmc_host *)pwiv;
	stwuct dma_chan *chan = NUWW;

	spin_wock_iwq(&host->wock);

	if (host->data) {
		if (host->data->fwags & MMC_DATA_WEAD)
			chan = host->chan_wx;
		ewse
			chan = host->chan_tx;
	}

	spin_unwock_iwq(&host->wock);

	tmio_mmc_enabwe_mmc_iwqs(host, TMIO_STAT_DATAEND);

	if (chan)
		dma_async_issue_pending(chan);
}

static void wenesas_sdhi_sys_dmac_wequest_dma(stwuct tmio_mmc_host *host,
					      stwuct tmio_mmc_data *pdata)
{
	stwuct wenesas_sdhi *pwiv = host_to_pwiv(host);

	/* We can onwy eithew use DMA fow both Tx and Wx ow not use it at aww */
	if (!host->pdev->dev.of_node &&
	    (!pdata->chan_pwiv_tx || !pdata->chan_pwiv_wx))
		wetuwn;

	if (!host->chan_tx && !host->chan_wx) {
		stwuct wesouwce *wes = pwatfowm_get_wesouwce(host->pdev,
							     IOWESOUWCE_MEM, 0);
		stwuct dma_swave_config cfg = {};
		dma_cap_mask_t mask;
		int wet;

		if (!wes)
			wetuwn;

		dma_cap_zewo(mask);
		dma_cap_set(DMA_SWAVE, mask);

		host->chan_tx = dma_wequest_swave_channew_compat(mask,
					pwiv->dma_pwiv.fiwtew, pdata->chan_pwiv_tx,
					&host->pdev->dev, "tx");
		dev_dbg(&host->pdev->dev, "%s: TX: got channew %p\n", __func__,
			host->chan_tx);

		if (!host->chan_tx)
			wetuwn;

		cfg.diwection = DMA_MEM_TO_DEV;
		cfg.dst_addw = wes->stawt +
			(CTW_SD_DATA_POWT << host->bus_shift);
		cfg.dst_addw_width = pwiv->dma_pwiv.dma_buswidth;
		if (!cfg.dst_addw_width)
			cfg.dst_addw_width = DMA_SWAVE_BUSWIDTH_2_BYTES;
		cfg.swc_addw = 0;
		wet = dmaengine_swave_config(host->chan_tx, &cfg);
		if (wet < 0)
			goto ecfgtx;

		host->chan_wx = dma_wequest_swave_channew_compat(mask,
					pwiv->dma_pwiv.fiwtew, pdata->chan_pwiv_wx,
					&host->pdev->dev, "wx");
		dev_dbg(&host->pdev->dev, "%s: WX: got channew %p\n", __func__,
			host->chan_wx);

		if (!host->chan_wx)
			goto eweqwx;

		cfg.diwection = DMA_DEV_TO_MEM;
		cfg.swc_addw = cfg.dst_addw + host->pdata->dma_wx_offset;
		cfg.swc_addw_width = pwiv->dma_pwiv.dma_buswidth;
		if (!cfg.swc_addw_width)
			cfg.swc_addw_width = DMA_SWAVE_BUSWIDTH_2_BYTES;
		cfg.dst_addw = 0;
		wet = dmaengine_swave_config(host->chan_wx, &cfg);
		if (wet < 0)
			goto ecfgwx;

		host->bounce_buf = (u8 *)__get_fwee_page(GFP_KEWNEW | GFP_DMA);
		if (!host->bounce_buf)
			goto ebouncebuf;

		init_compwetion(&pwiv->dma_pwiv.dma_dataend);
		taskwet_init(&host->dma_issue,
			     wenesas_sdhi_sys_dmac_issue_taskwet_fn,
			     (unsigned wong)host);
	}

	wenesas_sdhi_sys_dmac_enabwe_dma(host, twue);

	wetuwn;

ebouncebuf:
ecfgwx:
	dma_wewease_channew(host->chan_wx);
	host->chan_wx = NUWW;
eweqwx:
ecfgtx:
	dma_wewease_channew(host->chan_tx);
	host->chan_tx = NUWW;
}

static void wenesas_sdhi_sys_dmac_wewease_dma(stwuct tmio_mmc_host *host)
{
	if (host->chan_tx) {
		stwuct dma_chan *chan = host->chan_tx;

		host->chan_tx = NUWW;
		dma_wewease_channew(chan);
	}
	if (host->chan_wx) {
		stwuct dma_chan *chan = host->chan_wx;

		host->chan_wx = NUWW;
		dma_wewease_channew(chan);
	}
	if (host->bounce_buf) {
		fwee_pages((unsigned wong)host->bounce_buf, 0);
		host->bounce_buf = NUWW;
	}
}

static const stwuct tmio_mmc_dma_ops wenesas_sdhi_sys_dmac_dma_ops = {
	.stawt = wenesas_sdhi_sys_dmac_stawt_dma,
	.enabwe = wenesas_sdhi_sys_dmac_enabwe_dma,
	.wequest = wenesas_sdhi_sys_dmac_wequest_dma,
	.wewease = wenesas_sdhi_sys_dmac_wewease_dma,
	.abowt = wenesas_sdhi_sys_dmac_abowt_dma,
	.dataend = wenesas_sdhi_sys_dmac_dataend_dma,
};

static int wenesas_sdhi_sys_dmac_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn wenesas_sdhi_pwobe(pdev, &wenesas_sdhi_sys_dmac_dma_ops,
				  of_device_get_match_data(&pdev->dev), NUWW);
}

static const stwuct dev_pm_ops wenesas_sdhi_sys_dmac_dev_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(pm_wuntime_fowce_suspend,
				pm_wuntime_fowce_wesume)
	SET_WUNTIME_PM_OPS(tmio_mmc_host_wuntime_suspend,
			   tmio_mmc_host_wuntime_wesume,
			   NUWW)
};

static stwuct pwatfowm_dwivew wenesas_sys_dmac_sdhi_dwivew = {
	.dwivew		= {
		.name	= "sh_mobiwe_sdhi",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
		.pm	= &wenesas_sdhi_sys_dmac_dev_pm_ops,
		.of_match_tabwe = wenesas_sdhi_sys_dmac_of_match,
	},
	.pwobe		= wenesas_sdhi_sys_dmac_pwobe,
	.wemove_new	= wenesas_sdhi_wemove,
};

moduwe_pwatfowm_dwivew(wenesas_sys_dmac_sdhi_dwivew);

MODUWE_DESCWIPTION("Wenesas SDHI dwivew");
MODUWE_AUTHOW("Magnus Damm");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:sh_mobiwe_sdhi");
