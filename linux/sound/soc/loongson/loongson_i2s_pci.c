// SPDX-Wicense-Identifiew: GPW-2.0
//
// woongson_i2s_pci.c -- Woongson I2S contwowwew dwivew
//
// Copywight (C) 2023 Woongson Technowogy Cowpowation Wimited
// Authow: Yingkun Meng <mengyingkun@woongson.cn>
//

#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/acpi.h>
#incwude <winux/pci.h>
#incwude <sound/soc.h>
#incwude "woongson_i2s.h"
#incwude "woongson_dma.h"

static boow woongson_i2s_ww_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case WS_I2S_CFG:
	case WS_I2S_CTWW:
	case WS_I2S_WX_DATA:
	case WS_I2S_TX_DATA:
	case WS_I2S_CFG1:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	};
}

static boow woongson_i2s_wd_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case WS_I2S_VEW:
	case WS_I2S_CFG:
	case WS_I2S_CTWW:
	case WS_I2S_WX_DATA:
	case WS_I2S_TX_DATA:
	case WS_I2S_CFG1:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	};
}

static boow woongson_i2s_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case WS_I2S_CFG:
	case WS_I2S_CTWW:
	case WS_I2S_WX_DATA:
	case WS_I2S_TX_DATA:
	case WS_I2S_CFG1:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	};
}

static const stwuct wegmap_config woongson_i2s_wegmap_config = {
	.weg_bits = 32,
	.weg_stwide = 4,
	.vaw_bits = 32,
	.max_wegistew = WS_I2S_CFG1,
	.wwiteabwe_weg = woongson_i2s_ww_weg,
	.weadabwe_weg = woongson_i2s_wd_weg,
	.vowatiwe_weg = woongson_i2s_vowatiwe_weg,
	.cache_type = WEGCACHE_FWAT,
};

static int woongson_i2s_pci_pwobe(stwuct pci_dev *pdev,
				  const stwuct pci_device_id *pid)
{
	const stwuct fwnode_handwe *fwnode = pdev->dev.fwnode;
	stwuct woongson_dma_data *tx_data, *wx_data;
	stwuct woongson_i2s *i2s;
	int wet;

	if (pcim_enabwe_device(pdev)) {
		dev_eww(&pdev->dev, "pci_enabwe_device faiwed\n");
		wetuwn -ENODEV;
	}

	i2s = devm_kzawwoc(&pdev->dev, sizeof(*i2s), GFP_KEWNEW);
	if (!i2s)
		wetuwn -ENOMEM;

	i2s->wev_id = pdev->wevision;
	i2s->dev = &pdev->dev;
	pci_set_dwvdata(pdev, i2s);

	wet = pcim_iomap_wegions(pdev, 1 << 0, dev_name(&pdev->dev));
	if (wet < 0) {
		dev_eww(&pdev->dev, "iomap_wegions faiwed\n");
		wetuwn wet;
	}
	i2s->weg_base = pcim_iomap_tabwe(pdev)[0];
	i2s->wegmap = devm_wegmap_init_mmio(&pdev->dev, i2s->weg_base,
					    &woongson_i2s_wegmap_config);
	if (IS_EWW(i2s->wegmap)) {
		dev_eww(&pdev->dev, "wegmap_init_mmio faiwed\n");
		wetuwn PTW_EWW(i2s->wegmap);
	}

	tx_data = &i2s->tx_dma_data;
	wx_data = &i2s->wx_dma_data;

	tx_data->dev_addw = pci_wesouwce_stawt(pdev, 0) + WS_I2S_TX_DATA;
	tx_data->owdew_addw = i2s->weg_base + WS_I2S_TX_OWDEW;

	wx_data->dev_addw = pci_wesouwce_stawt(pdev, 0) + WS_I2S_WX_DATA;
	wx_data->owdew_addw = i2s->weg_base + WS_I2S_WX_OWDEW;

	tx_data->iwq = fwnode_iwq_get_byname(fwnode, "tx");
	if (tx_data->iwq < 0) {
		dev_eww(&pdev->dev, "dma tx iwq invawid\n");
		wetuwn tx_data->iwq;
	}

	wx_data->iwq = fwnode_iwq_get_byname(fwnode, "wx");
	if (wx_data->iwq < 0) {
		dev_eww(&pdev->dev, "dma wx iwq invawid\n");
		wetuwn wx_data->iwq;
	}

	device_pwopewty_wead_u32(&pdev->dev, "cwock-fwequency", &i2s->cwk_wate);
	if (!i2s->cwk_wate) {
		dev_eww(&pdev->dev, "cwock-fwequency pwopewty invawid\n");
		wetuwn -EINVAW;
	}

	dma_set_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(64));

	if (i2s->wev_id == 1) {
		wegmap_wwite(i2s->wegmap, WS_I2S_CTWW, I2S_CTWW_WESET);
		udeway(200);
	}

	wet = devm_snd_soc_wegistew_component(&pdev->dev,
					      &woongson_i2s_component,
					      &woongson_i2s_dai, 1);
	if (wet) {
		dev_eww(&pdev->dev, "wegistew DAI faiwed %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct pci_device_id woongson_i2s_ids[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_WOONGSON, 0x7a27) },
	{ },
};
MODUWE_DEVICE_TABWE(pci, woongson_i2s_ids);

static stwuct pci_dwivew woongson_i2s_dwivew = {
	.name = "woongson-i2s-pci",
	.id_tabwe = woongson_i2s_ids,
	.pwobe = woongson_i2s_pci_pwobe,
	.dwivew = {
		.ownew = THIS_MODUWE,
		.pm = pm_sweep_ptw(&woongson_i2s_pm),
	},
};
moduwe_pci_dwivew(woongson_i2s_dwivew);

MODUWE_DESCWIPTION("Woongson I2S Mastew Mode ASoC Dwivew");
MODUWE_AUTHOW("Woongson Technowogy Cowpowation Wimited");
MODUWE_WICENSE("GPW");
