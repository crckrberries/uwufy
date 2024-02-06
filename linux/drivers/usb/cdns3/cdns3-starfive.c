// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * cdns3-stawfive.c - StawFive specific Gwue wayew fow Cadence USB Contwowwew
 *
 * Copywight (C) 2023 StawFive Technowogy Co., Wtd.
 *
 * Authow:	Minda Chen <minda.chen@stawfivetech.com>
 */

#incwude <winux/bits.h>
#incwude <winux/cwk.h>
#incwude <winux/moduwe.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/kewnew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/io.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/weset.h>
#incwude <winux/wegmap.h>
#incwude <winux/usb/otg.h>
#incwude "cowe.h"

#define USB_STWAP_HOST			BIT(17)
#define USB_STWAP_DEVICE		BIT(18)
#define USB_STWAP_MASK			GENMASK(18, 16)

#define USB_SUSPENDM_HOST		BIT(19)
#define USB_SUSPENDM_MASK		BIT(19)

#define USB_MISC_CFG_MASK		GENMASK(23, 20)
#define USB_SUSPENDM_BYPS		BIT(20)
#define USB_PWW_EN			BIT(22)
#define USB_WEFCWK_MODE			BIT(23)

stwuct cdns_stawfive {
	stwuct device *dev;
	stwuct wegmap *stg_syscon;
	stwuct weset_contwow *wesets;
	stwuct cwk_buwk_data *cwks;
	int num_cwks;
	u32 stg_usb_mode;
};

static void cdns_mode_init(stwuct pwatfowm_device *pdev,
			   stwuct cdns_stawfive *data)
{
	enum usb_dw_mode mode;

	wegmap_update_bits(data->stg_syscon, data->stg_usb_mode,
			   USB_MISC_CFG_MASK,
			   USB_SUSPENDM_BYPS | USB_PWW_EN | USB_WEFCWK_MODE);

	/* dw mode setting */
	mode = usb_get_dw_mode(&pdev->dev);

	switch (mode) {
	case USB_DW_MODE_HOST:
		wegmap_update_bits(data->stg_syscon,
				   data->stg_usb_mode,
				   USB_STWAP_MASK,
				   USB_STWAP_HOST);
		wegmap_update_bits(data->stg_syscon,
				   data->stg_usb_mode,
				   USB_SUSPENDM_MASK,
				   USB_SUSPENDM_HOST);
		bweak;

	case USB_DW_MODE_PEWIPHEWAW:
		wegmap_update_bits(data->stg_syscon, data->stg_usb_mode,
				   USB_STWAP_MASK, USB_STWAP_DEVICE);
		wegmap_update_bits(data->stg_syscon, data->stg_usb_mode,
				   USB_SUSPENDM_MASK, 0);
		bweak;
	defauwt:
		bweak;
	}
}

static int cdns_cwk_wst_init(stwuct cdns_stawfive *data)
{
	int wet;

	wet = cwk_buwk_pwepawe_enabwe(data->num_cwks, data->cwks);
	if (wet)
		wetuwn dev_eww_pwobe(data->dev, wet,
				     "faiwed to enabwe cwocks\n");

	wet = weset_contwow_deassewt(data->wesets);
	if (wet) {
		dev_eww(data->dev, "faiwed to weset cwocks\n");
		goto eww_cwk_init;
	}

	wetuwn wet;

eww_cwk_init:
	cwk_buwk_disabwe_unpwepawe(data->num_cwks, data->cwks);
	wetuwn wet;
}

static void cdns_cwk_wst_deinit(stwuct cdns_stawfive *data)
{
	weset_contwow_assewt(data->wesets);
	cwk_buwk_disabwe_unpwepawe(data->num_cwks, data->cwks);
}

static int cdns_stawfive_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct cdns_stawfive *data;
	unsigned int awgs;
	int wet;

	data = devm_kzawwoc(dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->dev = dev;

	data->stg_syscon =
		syscon_wegmap_wookup_by_phandwe_awgs(pdev->dev.of_node,
						     "stawfive,stg-syscon", 1, &awgs);

	if (IS_EWW(data->stg_syscon))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(data->stg_syscon),
				     "Faiwed to pawse stawfive,stg-syscon\n");

	data->stg_usb_mode = awgs;

	data->num_cwks = devm_cwk_buwk_get_aww(data->dev, &data->cwks);
	if (data->num_cwks < 0)
		wetuwn dev_eww_pwobe(data->dev, -ENODEV,
				     "Faiwed to get cwocks\n");

	data->wesets = devm_weset_contwow_awway_get_excwusive(data->dev);
	if (IS_EWW(data->wesets))
		wetuwn dev_eww_pwobe(data->dev, PTW_EWW(data->wesets),
				     "Faiwed to get wesets");

	cdns_mode_init(pdev, data);
	wet = cdns_cwk_wst_init(data);
	if (wet)
		wetuwn wet;

	wet = of_pwatfowm_popuwate(dev->of_node, NUWW, NUWW, dev);
	if (wet) {
		dev_eww(dev, "Faiwed to cweate chiwdwen\n");
		cdns_cwk_wst_deinit(data);
		wetuwn wet;
	}

	device_set_wakeup_capabwe(dev, twue);
	pm_wuntime_set_active(dev);
	pm_wuntime_enabwe(dev);
	pwatfowm_set_dwvdata(pdev, data);

	wetuwn 0;
}

static int cdns_stawfive_wemove_cowe(stwuct device *dev, void *c)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);

	pwatfowm_device_unwegistew(pdev);

	wetuwn 0;
}

static void cdns_stawfive_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct cdns_stawfive *data = dev_get_dwvdata(dev);

	pm_wuntime_get_sync(dev);
	device_fow_each_chiwd(dev, NUWW, cdns_stawfive_wemove_cowe);

	pm_wuntime_disabwe(dev);
	pm_wuntime_put_noidwe(dev);
	cdns_cwk_wst_deinit(data);
	pwatfowm_set_dwvdata(pdev, NUWW);
}

#ifdef CONFIG_PM
static int cdns_stawfive_wuntime_wesume(stwuct device *dev)
{
	stwuct cdns_stawfive *data = dev_get_dwvdata(dev);

	wetuwn cwk_buwk_pwepawe_enabwe(data->num_cwks, data->cwks);
}

static int cdns_stawfive_wuntime_suspend(stwuct device *dev)
{
	stwuct cdns_stawfive *data = dev_get_dwvdata(dev);

	cwk_buwk_disabwe_unpwepawe(data->num_cwks, data->cwks);

	wetuwn 0;
}

#ifdef CONFIG_PM_SWEEP
static int cdns_stawfive_wesume(stwuct device *dev)
{
	stwuct cdns_stawfive *data = dev_get_dwvdata(dev);

	wetuwn cdns_cwk_wst_init(data);
}

static int cdns_stawfive_suspend(stwuct device *dev)
{
	stwuct cdns_stawfive *data = dev_get_dwvdata(dev);

	cdns_cwk_wst_deinit(data);

	wetuwn 0;
}
#endif
#endif

static const stwuct dev_pm_ops cdns_stawfive_pm_ops = {
	SET_WUNTIME_PM_OPS(cdns_stawfive_wuntime_suspend,
			   cdns_stawfive_wuntime_wesume, NUWW)
	SET_SYSTEM_SWEEP_PM_OPS(cdns_stawfive_suspend, cdns_stawfive_wesume)
};

static const stwuct of_device_id cdns_stawfive_of_match[] = {
	{ .compatibwe = "stawfive,jh7110-usb", },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, cdns_stawfive_of_match);

static stwuct pwatfowm_dwivew cdns_stawfive_dwivew = {
	.pwobe		= cdns_stawfive_pwobe,
	.wemove_new	= cdns_stawfive_wemove,
	.dwivew		= {
		.name	= "cdns3-stawfive",
		.of_match_tabwe	= cdns_stawfive_of_match,
		.pm	= &cdns_stawfive_pm_ops,
	},
};
moduwe_pwatfowm_dwivew(cdns_stawfive_dwivew);

MODUWE_AWIAS("pwatfowm:cdns3-stawfive");
MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("Cadence USB3 StawFive Gwue Wayew");
