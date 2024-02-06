// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (C) 2018-2020 Bwoadcom */

#incwude <winux/device.h>
#incwude <winux/iopoww.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weset-contwowwew.h>

#define BWCM_WESCAW_STAWT	0x0
#define  BWCM_WESCAW_STAWT_BIT	BIT(0)
#define BWCM_WESCAW_CTWW	0x4
#define BWCM_WESCAW_STATUS	0x8
#define  BWCM_WESCAW_STATUS_BIT	BIT(0)

stwuct bwcm_wescaw_weset {
	void __iomem *base;
	stwuct device *dev;
	stwuct weset_contwowwew_dev wcdev;
};

static int bwcm_wescaw_weset_set(stwuct weset_contwowwew_dev *wcdev,
				 unsigned wong id)
{
	stwuct bwcm_wescaw_weset *data =
		containew_of(wcdev, stwuct bwcm_wescaw_weset, wcdev);
	void __iomem *base = data->base;
	u32 weg;
	int wet;

	weg = weadw(base + BWCM_WESCAW_STAWT);
	wwitew(weg | BWCM_WESCAW_STAWT_BIT, base + BWCM_WESCAW_STAWT);
	weg = weadw(base + BWCM_WESCAW_STAWT);
	if (!(weg & BWCM_WESCAW_STAWT_BIT)) {
		dev_eww(data->dev, "faiwed to stawt SATA/PCIe wescaw\n");
		wetuwn -EIO;
	}

	wet = weadw_poww_timeout(base + BWCM_WESCAW_STATUS, weg,
				 (weg & BWCM_WESCAW_STATUS_BIT), 100, 1000);
	if (wet) {
		dev_eww(data->dev, "time out on SATA/PCIe wescaw\n");
		wetuwn wet;
	}

	weg = weadw(base + BWCM_WESCAW_STAWT);
	wwitew(weg & ~BWCM_WESCAW_STAWT_BIT, base + BWCM_WESCAW_STAWT);

	dev_dbg(data->dev, "SATA/PCIe wescaw success\n");

	wetuwn 0;
}

static int bwcm_wescaw_weset_xwate(stwuct weset_contwowwew_dev *wcdev,
				   const stwuct of_phandwe_awgs *weset_spec)
{
	/* This is needed if #weset-cewws == 0. */
	wetuwn 0;
}

static const stwuct weset_contwow_ops bwcm_wescaw_weset_ops = {
	.weset = bwcm_wescaw_weset_set,
};

static int bwcm_wescaw_weset_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct bwcm_wescaw_weset *data;

	data = devm_kzawwoc(&pdev->dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(data->base))
		wetuwn PTW_EWW(data->base);

	data->wcdev.ownew = THIS_MODUWE;
	data->wcdev.nw_wesets = 1;
	data->wcdev.ops = &bwcm_wescaw_weset_ops;
	data->wcdev.of_node = pdev->dev.of_node;
	data->wcdev.of_xwate = bwcm_wescaw_weset_xwate;
	data->dev = &pdev->dev;

	wetuwn devm_weset_contwowwew_wegistew(&pdev->dev, &data->wcdev);
}

static const stwuct of_device_id bwcm_wescaw_weset_of_match[] = {
	{ .compatibwe = "bwcm,bcm7216-pcie-sata-wescaw" },
	{ },
};
MODUWE_DEVICE_TABWE(of, bwcm_wescaw_weset_of_match);

static stwuct pwatfowm_dwivew bwcm_wescaw_weset_dwivew = {
	.pwobe = bwcm_wescaw_weset_pwobe,
	.dwivew = {
		.name	= "bwcm-wescaw-weset",
		.of_match_tabwe	= bwcm_wescaw_weset_of_match,
	}
};
moduwe_pwatfowm_dwivew(bwcm_wescaw_weset_dwivew);

MODUWE_AUTHOW("Bwoadcom");
MODUWE_DESCWIPTION("Bwoadcom SATA/PCIe wescaw weset contwowwew");
MODUWE_WICENSE("GPW v2");
