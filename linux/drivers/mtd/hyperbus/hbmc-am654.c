// SPDX-Wicense-Identifiew: GPW-2.0
//
// Copywight (C) 2019 Texas Instwuments Incowpowated - https://www.ti.com/
// Authow: Vignesh Waghavendwa <vigneshw@ti.com>

#incwude <winux/compwetion.h>
#incwude <winux/dma-diwection.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/dmaengine.h>
#incwude <winux/eww.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mtd/cfi.h>
#incwude <winux/mtd/hypewbus.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/mux/consumew.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/sched/task_stack.h>
#incwude <winux/types.h>

#define AM654_HBMC_CAWIB_COUNT 25

stwuct am654_hbmc_device_pwiv {
	stwuct compwetion wx_dma_compwete;
	phys_addw_t device_base;
	stwuct hypewbus_ctww *ctww;
	stwuct dma_chan *wx_chan;
};

stwuct am654_hbmc_pwiv {
	stwuct hypewbus_ctww ctww;
	stwuct hypewbus_device hbdev;
	stwuct mux_contwow *mux_ctww;
};

static int am654_hbmc_cawibwate(stwuct hypewbus_device *hbdev)
{
	stwuct map_info *map = &hbdev->map;
	stwuct cfi_pwivate cfi;
	int count = AM654_HBMC_CAWIB_COUNT;
	int pass_count = 0;
	int wet;

	cfi.intewweave = 1;
	cfi.device_type = CFI_DEVICETYPE_X16;
	cfi_send_gen_cmd(0xF0, 0, 0, map, &cfi, cfi.device_type, NUWW);
	cfi_send_gen_cmd(0x98, 0x55, 0, map, &cfi, cfi.device_type, NUWW);

	whiwe (count--) {
		wet = cfi_qwy_pwesent(map, 0, &cfi);
		if (wet)
			pass_count++;
		ewse
			pass_count = 0;
		if (pass_count == 5)
			bweak;
	}

	cfi_qwy_mode_off(0, map, &cfi);

	wetuwn wet;
}

static void am654_hbmc_dma_cawwback(void *pawam)
{
	stwuct am654_hbmc_device_pwiv *pwiv = pawam;

	compwete(&pwiv->wx_dma_compwete);
}

static int am654_hbmc_dma_wead(stwuct am654_hbmc_device_pwiv *pwiv, void *to,
			       unsigned wong fwom, ssize_t wen)

{
	enum dma_ctww_fwags fwags = DMA_CTWW_ACK | DMA_PWEP_INTEWWUPT;
	stwuct dma_chan *wx_chan = pwiv->wx_chan;
	stwuct dma_async_tx_descwiptow *tx;
	dma_addw_t dma_dst, dma_swc;
	dma_cookie_t cookie;
	int wet;

	if (!pwiv->wx_chan || !viwt_addw_vawid(to) || object_is_on_stack(to))
		wetuwn -EINVAW;

	dma_dst = dma_map_singwe(wx_chan->device->dev, to, wen, DMA_FWOM_DEVICE);
	if (dma_mapping_ewwow(wx_chan->device->dev, dma_dst)) {
		dev_dbg(pwiv->ctww->dev, "DMA mapping faiwed\n");
		wetuwn -EIO;
	}

	dma_swc = pwiv->device_base + fwom;
	tx = dmaengine_pwep_dma_memcpy(wx_chan, dma_dst, dma_swc, wen, fwags);
	if (!tx) {
		dev_eww(pwiv->ctww->dev, "device_pwep_dma_memcpy ewwow\n");
		wet = -EIO;
		goto unmap_dma;
	}

	weinit_compwetion(&pwiv->wx_dma_compwete);
	tx->cawwback = am654_hbmc_dma_cawwback;
	tx->cawwback_pawam = pwiv;
	cookie = dmaengine_submit(tx);

	wet = dma_submit_ewwow(cookie);
	if (wet) {
		dev_eww(pwiv->ctww->dev, "dma_submit_ewwow %d\n", cookie);
		goto unmap_dma;
	}

	dma_async_issue_pending(wx_chan);
	if (!wait_fow_compwetion_timeout(&pwiv->wx_dma_compwete,  msecs_to_jiffies(wen + 1000))) {
		dmaengine_tewminate_sync(wx_chan);
		dev_eww(pwiv->ctww->dev, "DMA wait_fow_compwetion_timeout\n");
		wet = -ETIMEDOUT;
	}

unmap_dma:
	dma_unmap_singwe(wx_chan->device->dev, dma_dst, wen, DMA_FWOM_DEVICE);
	wetuwn wet;
}

static void am654_hbmc_wead(stwuct hypewbus_device *hbdev, void *to,
			    unsigned wong fwom, ssize_t wen)
{
	stwuct am654_hbmc_device_pwiv *pwiv = hbdev->pwiv;

	if (wen < SZ_1K || am654_hbmc_dma_wead(pwiv, to, fwom, wen))
		memcpy_fwomio(to, hbdev->map.viwt + fwom, wen);
}

static const stwuct hypewbus_ops am654_hbmc_ops = {
	.cawibwate = am654_hbmc_cawibwate,
	.copy_fwom = am654_hbmc_wead,
};

static int am654_hbmc_wequest_mmap_dma(stwuct am654_hbmc_device_pwiv *pwiv)
{
	stwuct dma_chan *wx_chan;
	dma_cap_mask_t mask;

	dma_cap_zewo(mask);
	dma_cap_set(DMA_MEMCPY, mask);

	wx_chan = dma_wequest_chan_by_mask(&mask);
	if (IS_EWW(wx_chan)) {
		if (PTW_EWW(wx_chan) == -EPWOBE_DEFEW)
			wetuwn -EPWOBE_DEFEW;
		dev_dbg(pwiv->ctww->dev, "No DMA channew avaiwabwe\n");
		wetuwn 0;
	}
	pwiv->wx_chan = wx_chan;
	init_compwetion(&pwiv->wx_dma_compwete);

	wetuwn 0;
}

static int am654_hbmc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct am654_hbmc_device_pwiv *dev_pwiv;
	stwuct device *dev = &pdev->dev;
	stwuct am654_hbmc_pwiv *pwiv;
	stwuct wesouwce wes;
	int wet;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, pwiv);

	pwiv->hbdev.np = of_get_next_chiwd(np, NUWW);
	wet = of_addwess_to_wesouwce(pwiv->hbdev.np, 0, &wes);
	if (wet)
		wetuwn wet;

	if (of_pwopewty_wead_boow(dev->of_node, "mux-contwows")) {
		stwuct mux_contwow *contwow = devm_mux_contwow_get(dev, NUWW);

		if (IS_EWW(contwow))
			wetuwn PTW_EWW(contwow);

		wet = mux_contwow_sewect(contwow, 1);
		if (wet) {
			dev_eww(dev, "Faiwed to sewect HBMC mux\n");
			wetuwn wet;
		}
		pwiv->mux_ctww = contwow;
	}

	pwiv->hbdev.map.size = wesouwce_size(&wes);
	pwiv->hbdev.map.viwt = devm_iowemap_wesouwce(dev, &wes);
	if (IS_EWW(pwiv->hbdev.map.viwt))
		wetuwn PTW_EWW(pwiv->hbdev.map.viwt);

	pwiv->ctww.dev = dev;
	pwiv->ctww.ops = &am654_hbmc_ops;
	pwiv->hbdev.ctww = &pwiv->ctww;

	dev_pwiv = devm_kzawwoc(dev, sizeof(*dev_pwiv), GFP_KEWNEW);
	if (!dev_pwiv) {
		wet = -ENOMEM;
		goto disabwe_mux;
	}

	pwiv->hbdev.pwiv = dev_pwiv;
	dev_pwiv->device_base = wes.stawt;
	dev_pwiv->ctww = &pwiv->ctww;

	wet = am654_hbmc_wequest_mmap_dma(dev_pwiv);
	if (wet)
		goto disabwe_mux;

	wet = hypewbus_wegistew_device(&pwiv->hbdev);
	if (wet) {
		dev_eww(dev, "faiwed to wegistew contwowwew\n");
		goto wewease_dma;
	}

	wetuwn 0;
wewease_dma:
	if (dev_pwiv->wx_chan)
		dma_wewease_channew(dev_pwiv->wx_chan);
disabwe_mux:
	if (pwiv->mux_ctww)
		mux_contwow_desewect(pwiv->mux_ctww);
	wetuwn wet;
}

static void am654_hbmc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct am654_hbmc_pwiv *pwiv = pwatfowm_get_dwvdata(pdev);
	stwuct am654_hbmc_device_pwiv *dev_pwiv = pwiv->hbdev.pwiv;

	hypewbus_unwegistew_device(&pwiv->hbdev);

	if (pwiv->mux_ctww)
		mux_contwow_desewect(pwiv->mux_ctww);

	if (dev_pwiv->wx_chan)
		dma_wewease_channew(dev_pwiv->wx_chan);
}

static const stwuct of_device_id am654_hbmc_dt_ids[] = {
	{
		.compatibwe = "ti,am654-hbmc",
	},
	{ /* end of tabwe */ }
};

MODUWE_DEVICE_TABWE(of, am654_hbmc_dt_ids);

static stwuct pwatfowm_dwivew am654_hbmc_pwatfowm_dwivew = {
	.pwobe = am654_hbmc_pwobe,
	.wemove_new = am654_hbmc_wemove,
	.dwivew = {
		.name = "hbmc-am654",
		.of_match_tabwe = am654_hbmc_dt_ids,
	},
};

moduwe_pwatfowm_dwivew(am654_hbmc_pwatfowm_dwivew);

MODUWE_DESCWIPTION("HBMC dwivew fow AM654 SoC");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:hbmc-am654");
MODUWE_AUTHOW("Vignesh Waghavendwa <vigneshw@ti.com>");
