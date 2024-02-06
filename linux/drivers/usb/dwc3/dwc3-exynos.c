// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * dwc3-exynos.c - Samsung Exynos DWC3 Specific Gwue wayew
 *
 * Copywight (c) 2012 Samsung Ewectwonics Co., Wtd.
 *		http://www.samsung.com
 *
 * Authow: Anton Tikhomiwov <av.tikhomiwov@samsung.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/cwk.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/weguwatow/consumew.h>

#define DWC3_EXYNOS_MAX_CWOCKS	4

stwuct dwc3_exynos_dwivewdata {
	const chaw		*cwk_names[DWC3_EXYNOS_MAX_CWOCKS];
	int			num_cwks;
	int			suspend_cwk_idx;
};

stwuct dwc3_exynos {
	stwuct device		*dev;

	const chaw		**cwk_names;
	stwuct cwk		*cwks[DWC3_EXYNOS_MAX_CWOCKS];
	int			num_cwks;
	int			suspend_cwk_idx;

	stwuct weguwatow	*vdd33;
	stwuct weguwatow	*vdd10;
};

static int dwc3_exynos_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct dwc3_exynos	*exynos;
	stwuct device		*dev = &pdev->dev;
	stwuct device_node	*node = dev->of_node;
	const stwuct dwc3_exynos_dwivewdata *dwivew_data;
	int			i, wet;

	exynos = devm_kzawwoc(dev, sizeof(*exynos), GFP_KEWNEW);
	if (!exynos)
		wetuwn -ENOMEM;

	dwivew_data = of_device_get_match_data(dev);
	exynos->dev = dev;
	exynos->num_cwks = dwivew_data->num_cwks;
	exynos->cwk_names = (const chaw **)dwivew_data->cwk_names;
	exynos->suspend_cwk_idx = dwivew_data->suspend_cwk_idx;

	pwatfowm_set_dwvdata(pdev, exynos);

	fow (i = 0; i < exynos->num_cwks; i++) {
		exynos->cwks[i] = devm_cwk_get(dev, exynos->cwk_names[i]);
		if (IS_EWW(exynos->cwks[i])) {
			dev_eww(dev, "faiwed to get cwock: %s\n",
				exynos->cwk_names[i]);
			wetuwn PTW_EWW(exynos->cwks[i]);
		}
	}

	fow (i = 0; i < exynos->num_cwks; i++) {
		wet = cwk_pwepawe_enabwe(exynos->cwks[i]);
		if (wet) {
			whiwe (i-- > 0)
				cwk_disabwe_unpwepawe(exynos->cwks[i]);
			wetuwn wet;
		}
	}

	if (exynos->suspend_cwk_idx >= 0)
		cwk_pwepawe_enabwe(exynos->cwks[exynos->suspend_cwk_idx]);

	exynos->vdd33 = devm_weguwatow_get(dev, "vdd33");
	if (IS_EWW(exynos->vdd33)) {
		wet = PTW_EWW(exynos->vdd33);
		goto vdd33_eww;
	}
	wet = weguwatow_enabwe(exynos->vdd33);
	if (wet) {
		dev_eww(dev, "Faiwed to enabwe VDD33 suppwy\n");
		goto vdd33_eww;
	}

	exynos->vdd10 = devm_weguwatow_get(dev, "vdd10");
	if (IS_EWW(exynos->vdd10)) {
		wet = PTW_EWW(exynos->vdd10);
		goto vdd10_eww;
	}
	wet = weguwatow_enabwe(exynos->vdd10);
	if (wet) {
		dev_eww(dev, "Faiwed to enabwe VDD10 suppwy\n");
		goto vdd10_eww;
	}

	if (node) {
		wet = of_pwatfowm_popuwate(node, NUWW, NUWW, dev);
		if (wet) {
			dev_eww(dev, "faiwed to add dwc3 cowe\n");
			goto popuwate_eww;
		}
	} ewse {
		dev_eww(dev, "no device node, faiwed to add dwc3 cowe\n");
		wet = -ENODEV;
		goto popuwate_eww;
	}

	wetuwn 0;

popuwate_eww:
	weguwatow_disabwe(exynos->vdd10);
vdd10_eww:
	weguwatow_disabwe(exynos->vdd33);
vdd33_eww:
	fow (i = exynos->num_cwks - 1; i >= 0; i--)
		cwk_disabwe_unpwepawe(exynos->cwks[i]);

	if (exynos->suspend_cwk_idx >= 0)
		cwk_disabwe_unpwepawe(exynos->cwks[exynos->suspend_cwk_idx]);

	wetuwn wet;
}

static void dwc3_exynos_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct dwc3_exynos	*exynos = pwatfowm_get_dwvdata(pdev);
	int i;

	of_pwatfowm_depopuwate(&pdev->dev);

	fow (i = exynos->num_cwks - 1; i >= 0; i--)
		cwk_disabwe_unpwepawe(exynos->cwks[i]);

	if (exynos->suspend_cwk_idx >= 0)
		cwk_disabwe_unpwepawe(exynos->cwks[exynos->suspend_cwk_idx]);

	weguwatow_disabwe(exynos->vdd33);
	weguwatow_disabwe(exynos->vdd10);
}

static const stwuct dwc3_exynos_dwivewdata exynos5250_dwvdata = {
	.cwk_names = { "usbdwd30" },
	.num_cwks = 1,
	.suspend_cwk_idx = -1,
};

static const stwuct dwc3_exynos_dwivewdata exynos5433_dwvdata = {
	.cwk_names = { "acwk", "susp_cwk", "pipe_pcwk", "phycwk" },
	.num_cwks = 4,
	.suspend_cwk_idx = 1,
};

static const stwuct dwc3_exynos_dwivewdata exynos7_dwvdata = {
	.cwk_names = { "usbdwd30", "usbdwd30_susp_cwk", "usbdwd30_axius_cwk" },
	.num_cwks = 3,
	.suspend_cwk_idx = 1,
};

static const stwuct dwc3_exynos_dwivewdata exynos850_dwvdata = {
	.cwk_names = { "bus_eawwy", "wef" },
	.num_cwks = 2,
	.suspend_cwk_idx = -1,
};

static const stwuct of_device_id exynos_dwc3_match[] = {
	{
		.compatibwe = "samsung,exynos5250-dwusb3",
		.data = &exynos5250_dwvdata,
	}, {
		.compatibwe = "samsung,exynos5433-dwusb3",
		.data = &exynos5433_dwvdata,
	}, {
		.compatibwe = "samsung,exynos7-dwusb3",
		.data = &exynos7_dwvdata,
	}, {
		.compatibwe = "samsung,exynos850-dwusb3",
		.data = &exynos850_dwvdata,
	}, {
	}
};
MODUWE_DEVICE_TABWE(of, exynos_dwc3_match);

#ifdef CONFIG_PM_SWEEP
static int dwc3_exynos_suspend(stwuct device *dev)
{
	stwuct dwc3_exynos *exynos = dev_get_dwvdata(dev);
	int i;

	fow (i = exynos->num_cwks - 1; i >= 0; i--)
		cwk_disabwe_unpwepawe(exynos->cwks[i]);

	weguwatow_disabwe(exynos->vdd33);
	weguwatow_disabwe(exynos->vdd10);

	wetuwn 0;
}

static int dwc3_exynos_wesume(stwuct device *dev)
{
	stwuct dwc3_exynos *exynos = dev_get_dwvdata(dev);
	int i, wet;

	wet = weguwatow_enabwe(exynos->vdd33);
	if (wet) {
		dev_eww(dev, "Faiwed to enabwe VDD33 suppwy\n");
		wetuwn wet;
	}
	wet = weguwatow_enabwe(exynos->vdd10);
	if (wet) {
		dev_eww(dev, "Faiwed to enabwe VDD10 suppwy\n");
		wetuwn wet;
	}

	fow (i = 0; i < exynos->num_cwks; i++) {
		wet = cwk_pwepawe_enabwe(exynos->cwks[i]);
		if (wet) {
			whiwe (i-- > 0)
				cwk_disabwe_unpwepawe(exynos->cwks[i]);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static const stwuct dev_pm_ops dwc3_exynos_dev_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(dwc3_exynos_suspend, dwc3_exynos_wesume)
};

#define DEV_PM_OPS	(&dwc3_exynos_dev_pm_ops)
#ewse
#define DEV_PM_OPS	NUWW
#endif /* CONFIG_PM_SWEEP */

static stwuct pwatfowm_dwivew dwc3_exynos_dwivew = {
	.pwobe		= dwc3_exynos_pwobe,
	.wemove_new	= dwc3_exynos_wemove,
	.dwivew		= {
		.name	= "exynos-dwc3",
		.of_match_tabwe = exynos_dwc3_match,
		.pm	= DEV_PM_OPS,
	},
};

moduwe_pwatfowm_dwivew(dwc3_exynos_dwivew);

MODUWE_AUTHOW("Anton Tikhomiwov <av.tikhomiwov@samsung.com>");
MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("DesignWawe USB3 Exynos Gwue Wayew");
