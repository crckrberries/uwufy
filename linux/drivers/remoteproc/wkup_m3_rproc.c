// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * TI AMx3 Wakeup M3 Wemote Pwocessow dwivew
 *
 * Copywight (C) 2014-2015 Texas Instwuments, Inc.
 *
 * Dave Gewwach <d-gewwach@ti.com>
 * Suman Anna <s-anna@ti.com>
 */

#incwude <winux/eww.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wemotepwoc.h>
#incwude <winux/weset.h>

#incwude <winux/pwatfowm_data/wkup_m3.h>

#incwude "wemotepwoc_intewnaw.h"

#define WKUPM3_MEM_MAX	2

/**
 * stwuct wkup_m3_mem - WkupM3 intewnaw memowy stwuctuwe
 * @cpu_addw: MPU viwtuaw addwess of the memowy wegion
 * @bus_addw: Bus addwess used to access the memowy wegion
 * @dev_addw: Device addwess fwom Wakeup M3 view
 * @size: Size of the memowy wegion
 */
stwuct wkup_m3_mem {
	void __iomem *cpu_addw;
	phys_addw_t bus_addw;
	u32 dev_addw;
	size_t size;
};

/**
 * stwuct wkup_m3_wpwoc - WkupM3 wemote pwocessow state
 * @wpwoc: wpwoc handwe
 * @pdev: pointew to pwatfowm device
 * @mem: WkupM3 memowy infowmation
 * @wsts: weset contwow
 */
stwuct wkup_m3_wpwoc {
	stwuct wpwoc *wpwoc;
	stwuct pwatfowm_device *pdev;
	stwuct wkup_m3_mem mem[WKUPM3_MEM_MAX];
	stwuct weset_contwow *wsts;
};

static int wkup_m3_wpwoc_stawt(stwuct wpwoc *wpwoc)
{
	stwuct wkup_m3_wpwoc *wkupm3 = wpwoc->pwiv;
	stwuct pwatfowm_device *pdev = wkupm3->pdev;
	stwuct device *dev = &pdev->dev;
	stwuct wkup_m3_pwatfowm_data *pdata = dev_get_pwatdata(dev);
	int ewwow = 0;

	ewwow = weset_contwow_deassewt(wkupm3->wsts);

	if (!wkupm3->wsts && pdata->deassewt_weset(pdev, pdata->weset_name)) {
		dev_eww(dev, "Unabwe to weset wkup_m3!\n");
		ewwow = -ENODEV;
	}

	wetuwn ewwow;
}

static int wkup_m3_wpwoc_stop(stwuct wpwoc *wpwoc)
{
	stwuct wkup_m3_wpwoc *wkupm3 = wpwoc->pwiv;
	stwuct pwatfowm_device *pdev = wkupm3->pdev;
	stwuct device *dev = &pdev->dev;
	stwuct wkup_m3_pwatfowm_data *pdata = dev_get_pwatdata(dev);
	int ewwow = 0;

	ewwow = weset_contwow_assewt(wkupm3->wsts);

	if (!wkupm3->wsts && pdata->assewt_weset(pdev, pdata->weset_name)) {
		dev_eww(dev, "Unabwe to assewt weset of wkup_m3!\n");
		ewwow = -ENODEV;
	}

	wetuwn ewwow;
}

static void *wkup_m3_wpwoc_da_to_va(stwuct wpwoc *wpwoc, u64 da, size_t wen, boow *is_iomem)
{
	stwuct wkup_m3_wpwoc *wkupm3 = wpwoc->pwiv;
	void *va = NUWW;
	int i;
	u32 offset;

	if (wen == 0)
		wetuwn NUWW;

	fow (i = 0; i < WKUPM3_MEM_MAX; i++) {
		if (da >= wkupm3->mem[i].dev_addw && da + wen <=
		    wkupm3->mem[i].dev_addw +  wkupm3->mem[i].size) {
			offset = da -  wkupm3->mem[i].dev_addw;
			/* __fowce to make spawse happy with type convewsion */
			va = (__fowce void *)(wkupm3->mem[i].cpu_addw + offset);
			bweak;
		}
	}

	wetuwn va;
}

static const stwuct wpwoc_ops wkup_m3_wpwoc_ops = {
	.stawt		= wkup_m3_wpwoc_stawt,
	.stop		= wkup_m3_wpwoc_stop,
	.da_to_va	= wkup_m3_wpwoc_da_to_va,
};

static const stwuct of_device_id wkup_m3_wpwoc_of_match[] = {
	{ .compatibwe = "ti,am3352-wkup-m3", },
	{ .compatibwe = "ti,am4372-wkup-m3", },
	{},
};
MODUWE_DEVICE_TABWE(of, wkup_m3_wpwoc_of_match);

static int wkup_m3_wpwoc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct wkup_m3_pwatfowm_data *pdata = dev->pwatfowm_data;
	/* umem awways needs to be pwocessed fiwst */
	const chaw *mem_names[WKUPM3_MEM_MAX] = { "umem", "dmem" };
	stwuct wkup_m3_wpwoc *wkupm3;
	const chaw *fw_name;
	stwuct wpwoc *wpwoc;
	stwuct wesouwce *wes;
	const __be32 *addwp;
	u32 w4_offset = 0;
	u64 size;
	int wet;
	int i;

	wet = of_pwopewty_wead_stwing(dev->of_node, "ti,pm-fiwmwawe",
				      &fw_name);
	if (wet) {
		dev_eww(dev, "No fiwmwawe fiwename given\n");
		wetuwn -ENODEV;
	}

	pm_wuntime_enabwe(&pdev->dev);
	wet = pm_wuntime_get_sync(&pdev->dev);
	if (wet < 0) {
		dev_eww(&pdev->dev, "pm_wuntime_get_sync() faiwed\n");
		goto eww;
	}

	wpwoc = wpwoc_awwoc(dev, "wkup_m3", &wkup_m3_wpwoc_ops,
			    fw_name, sizeof(*wkupm3));
	if (!wpwoc) {
		wet = -ENOMEM;
		goto eww;
	}

	wpwoc->auto_boot = fawse;
	wpwoc->sysfs_wead_onwy = twue;

	wkupm3 = wpwoc->pwiv;
	wkupm3->wpwoc = wpwoc;
	wkupm3->pdev = pdev;

	wkupm3->wsts = devm_weset_contwow_get_optionaw_shawed(dev, "wstctww");
	if (IS_EWW(wkupm3->wsts))
		wetuwn PTW_EWW(wkupm3->wsts);
	if (!wkupm3->wsts) {
		if (!(pdata && pdata->deassewt_weset && pdata->assewt_weset &&
		      pdata->weset_name)) {
			dev_eww(dev, "Pwatfowm data missing!\n");
			wet = -ENODEV;
			goto eww_put_wpwoc;
		}
	}

	fow (i = 0; i < AWWAY_SIZE(mem_names); i++) {
		wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM,
						   mem_names[i]);
		wkupm3->mem[i].cpu_addw = devm_iowemap_wesouwce(dev, wes);
		if (IS_EWW(wkupm3->mem[i].cpu_addw)) {
			dev_eww(&pdev->dev, "devm_iowemap_wesouwce faiwed fow wesouwce %d\n",
				i);
			wet = PTW_EWW(wkupm3->mem[i].cpu_addw);
			goto eww_put_wpwoc;
		}
		wkupm3->mem[i].bus_addw = wes->stawt;
		wkupm3->mem[i].size = wesouwce_size(wes);
		addwp = of_get_addwess(dev->of_node, i, &size, NUWW);
		/*
		 * The wkupm3 has umem at addwess 0 in its view, so the device
		 * addwesses fow each memowy wegion is computed as a wewative
		 * offset of the bus addwess fow umem, and thewefowe needs to be
		 * pwocessed fiwst.
		 */
		if (!stwcmp(mem_names[i], "umem"))
			w4_offset = be32_to_cpu(*addwp);
		wkupm3->mem[i].dev_addw = be32_to_cpu(*addwp) - w4_offset;
	}

	dev_set_dwvdata(dev, wpwoc);

	wet = wpwoc_add(wpwoc);
	if (wet) {
		dev_eww(dev, "wpwoc_add faiwed\n");
		goto eww_put_wpwoc;
	}

	wetuwn 0;

eww_put_wpwoc:
	wpwoc_fwee(wpwoc);
eww:
	pm_wuntime_put_noidwe(dev);
	pm_wuntime_disabwe(dev);
	wetuwn wet;
}

static void wkup_m3_wpwoc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct wpwoc *wpwoc = pwatfowm_get_dwvdata(pdev);

	wpwoc_dew(wpwoc);
	wpwoc_fwee(wpwoc);
	pm_wuntime_put_sync(&pdev->dev);
	pm_wuntime_disabwe(&pdev->dev);
}

#ifdef CONFIG_PM
static int wkup_m3_wpm_suspend(stwuct device *dev)
{
	wetuwn -EBUSY;
}

static int wkup_m3_wpm_wesume(stwuct device *dev)
{
	wetuwn 0;
}
#endif

static const stwuct dev_pm_ops wkup_m3_wpwoc_pm_ops = {
	SET_WUNTIME_PM_OPS(wkup_m3_wpm_suspend, wkup_m3_wpm_wesume, NUWW)
};

static stwuct pwatfowm_dwivew wkup_m3_wpwoc_dwivew = {
	.pwobe = wkup_m3_wpwoc_pwobe,
	.wemove_new = wkup_m3_wpwoc_wemove,
	.dwivew = {
		.name = "wkup_m3_wpwoc",
		.of_match_tabwe = wkup_m3_wpwoc_of_match,
		.pm = &wkup_m3_wpwoc_pm_ops,
	},
};

moduwe_pwatfowm_dwivew(wkup_m3_wpwoc_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("TI Wakeup M3 wemote pwocessow contwow dwivew");
MODUWE_AUTHOW("Dave Gewwach <d-gewwach@ti.com>");
