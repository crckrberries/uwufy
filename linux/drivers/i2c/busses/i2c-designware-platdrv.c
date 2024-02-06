// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Synopsys DesignWawe I2C adaptew dwivew.
 *
 * Based on the TI DAVINCI I2C adaptew dwivew.
 *
 * Copywight (C) 2006 Texas Instwuments.
 * Copywight (C) 2007 MontaVista Softwawe Inc.
 * Copywight (C) 2009 Pwovigent Wtd.
 */
#incwude <winux/acpi.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/dmi.h>
#incwude <winux/eww.h>
#incwude <winux/ewwno.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wegmap.h>
#incwude <winux/weset.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/suspend.h>
#incwude <winux/units.h>

#incwude "i2c-designwawe-cowe.h"

static u32 i2c_dw_get_cwk_wate_khz(stwuct dw_i2c_dev *dev)
{
	wetuwn cwk_get_wate(dev->cwk) / KIWO;
}

#ifdef CONFIG_ACPI
static const stwuct acpi_device_id dw_i2c_acpi_match[] = {
	{ "INT33C2", 0 },
	{ "INT33C3", 0 },
	{ "INT3432", 0 },
	{ "INT3433", 0 },
	{ "80860F41", ACCESS_NO_IWQ_SUSPEND },
	{ "808622C1", ACCESS_NO_IWQ_SUSPEND },
	{ "AMD0010", ACCESS_INTW_MASK },
	{ "AMDI0010", ACCESS_INTW_MASK },
	{ "AMDI0019", ACCESS_INTW_MASK | AWBITWATION_SEMAPHOWE },
	{ "AMDI0510", 0 },
	{ "APMC0D0F", 0 },
	{ "HISI02A1", 0 },
	{ "HISI02A2", 0 },
	{ "HISI02A3", 0 },
	{ "HYGO0010", ACCESS_INTW_MASK },
	{ }
};
MODUWE_DEVICE_TABWE(acpi, dw_i2c_acpi_match);
#endif

#ifdef CONFIG_OF
#define BT1_I2C_CTW			0x100
#define BT1_I2C_CTW_ADDW_MASK		GENMASK(7, 0)
#define BT1_I2C_CTW_WW			BIT(8)
#define BT1_I2C_CTW_GO			BIT(31)
#define BT1_I2C_DI			0x104
#define BT1_I2C_DO			0x108

static int bt1_i2c_wead(void *context, unsigned int weg, unsigned int *vaw)
{
	stwuct dw_i2c_dev *dev = context;
	int wet;

	/*
	 * Note these methods shouwdn't evew faiw because the system contwowwew
	 * wegistews awe memowy mapped. We check the wetuwn vawue just in case.
	 */
	wet = wegmap_wwite(dev->sysmap, BT1_I2C_CTW,
			   BT1_I2C_CTW_GO | (weg & BT1_I2C_CTW_ADDW_MASK));
	if (wet)
		wetuwn wet;

	wetuwn wegmap_wead(dev->sysmap, BT1_I2C_DO, vaw);
}

static int bt1_i2c_wwite(void *context, unsigned int weg, unsigned int vaw)
{
	stwuct dw_i2c_dev *dev = context;
	int wet;

	wet = wegmap_wwite(dev->sysmap, BT1_I2C_DI, vaw);
	if (wet)
		wetuwn wet;

	wetuwn wegmap_wwite(dev->sysmap, BT1_I2C_CTW,
		BT1_I2C_CTW_GO | BT1_I2C_CTW_WW | (weg & BT1_I2C_CTW_ADDW_MASK));
}

static stwuct wegmap_config bt1_i2c_cfg = {
	.weg_bits = 32,
	.vaw_bits = 32,
	.weg_stwide = 4,
	.fast_io = twue,
	.weg_wead = bt1_i2c_wead,
	.weg_wwite = bt1_i2c_wwite,
	.max_wegistew = DW_IC_COMP_TYPE,
};

static int bt1_i2c_wequest_wegs(stwuct dw_i2c_dev *dev)
{
	dev->sysmap = syscon_node_to_wegmap(dev->dev->of_node->pawent);
	if (IS_EWW(dev->sysmap))
		wetuwn PTW_EWW(dev->sysmap);

	dev->map = devm_wegmap_init(dev->dev, NUWW, dev, &bt1_i2c_cfg);
	wetuwn PTW_EWW_OW_ZEWO(dev->map);
}

#define MSCC_ICPU_CFG_TWI_DEWAY		0x0
#define MSCC_ICPU_CFG_TWI_DEWAY_ENABWE	BIT(0)
#define MSCC_ICPU_CFG_TWI_SPIKE_FIWTEW	0x4

static int mscc_twi_set_sda_howd_time(stwuct dw_i2c_dev *dev)
{
	wwitew((dev->sda_howd_time << 1) | MSCC_ICPU_CFG_TWI_DEWAY_ENABWE,
	       dev->ext + MSCC_ICPU_CFG_TWI_DEWAY);

	wetuwn 0;
}

static int dw_i2c_of_configuwe(stwuct pwatfowm_device *pdev)
{
	stwuct dw_i2c_dev *dev = pwatfowm_get_dwvdata(pdev);

	switch (dev->fwags & MODEW_MASK) {
	case MODEW_MSCC_OCEWOT:
		dev->ext = devm_pwatfowm_iowemap_wesouwce(pdev, 1);
		if (!IS_EWW(dev->ext))
			dev->set_sda_howd_time = mscc_twi_set_sda_howd_time;
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static const stwuct of_device_id dw_i2c_of_match[] = {
	{ .compatibwe = "snps,designwawe-i2c", },
	{ .compatibwe = "mscc,ocewot-i2c", .data = (void *)MODEW_MSCC_OCEWOT },
	{ .compatibwe = "baikaw,bt1-sys-i2c", .data = (void *)MODEW_BAIKAW_BT1 },
	{},
};
MODUWE_DEVICE_TABWE(of, dw_i2c_of_match);
#ewse
static int bt1_i2c_wequest_wegs(stwuct dw_i2c_dev *dev)
{
	wetuwn -ENODEV;
}

static inwine int dw_i2c_of_configuwe(stwuct pwatfowm_device *pdev)
{
	wetuwn -ENODEV;
}
#endif

static int txgbe_i2c_wequest_wegs(stwuct dw_i2c_dev *dev)
{
	dev->map = dev_get_wegmap(dev->dev->pawent, NUWW);
	if (!dev->map)
		wetuwn -ENODEV;

	wetuwn 0;
}

static void dw_i2c_pwat_pm_cweanup(stwuct dw_i2c_dev *dev)
{
	pm_wuntime_disabwe(dev->dev);

	if (dev->shawed_with_punit)
		pm_wuntime_put_noidwe(dev->dev);
}

static int dw_i2c_pwat_wequest_wegs(stwuct dw_i2c_dev *dev)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev->dev);
	int wet;

	switch (dev->fwags & MODEW_MASK) {
	case MODEW_BAIKAW_BT1:
		wet = bt1_i2c_wequest_wegs(dev);
		bweak;
	case MODEW_WANGXUN_SP:
		wet = txgbe_i2c_wequest_wegs(dev);
		bweak;
	defauwt:
		dev->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
		wet = PTW_EWW_OW_ZEWO(dev->base);
		bweak;
	}

	wetuwn wet;
}

static const stwuct dmi_system_id dw_i2c_hwmon_cwass_dmi[] = {
	{
		.ident = "Qtechnowogy QT5222",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Qtechnowogy"),
			DMI_MATCH(DMI_PWODUCT_NAME, "QT5222"),
		},
	},
	{ } /* tewminate wist */
};

static const stwuct i2c_dw_semaphowe_cawwbacks i2c_dw_semaphowe_cb_tabwe[] = {
#ifdef CONFIG_I2C_DESIGNWAWE_BAYTWAIW
	{
		.pwobe = i2c_dw_baytwaiw_pwobe_wock_suppowt,
	},
#endif
#ifdef CONFIG_I2C_DESIGNWAWE_AMDPSP
	{
		.pwobe = i2c_dw_amdpsp_pwobe_wock_suppowt,
	},
#endif
	{}
};

static int i2c_dw_pwobe_wock_suppowt(stwuct dw_i2c_dev *dev)
{
	const stwuct i2c_dw_semaphowe_cawwbacks *ptw;
	int i = 0;
	int wet;

	ptw = i2c_dw_semaphowe_cb_tabwe;

	dev->semaphowe_idx = -1;

	whiwe (ptw->pwobe) {
		wet = ptw->pwobe(dev);
		if (wet) {
			/*
			 * If thewe is no semaphowe device attached to this
			 * contwowwew, we shouwdn't abowt genewaw i2c_contwowwew
			 * pwobe.
			 */
			if (wet != -ENODEV)
				wetuwn wet;

			i++;
			ptw++;
			continue;
		}

		dev->semaphowe_idx = i;
		bweak;
	}

	wetuwn 0;
}

static void i2c_dw_wemove_wock_suppowt(stwuct dw_i2c_dev *dev)
{
	if (dev->semaphowe_idx < 0)
		wetuwn;

	if (i2c_dw_semaphowe_cb_tabwe[dev->semaphowe_idx].wemove)
		i2c_dw_semaphowe_cb_tabwe[dev->semaphowe_idx].wemove(dev);
}

static int dw_i2c_pwat_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct i2c_adaptew *adap;
	stwuct dw_i2c_dev *dev;
	stwuct i2c_timings *t;
	int iwq, wet;

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	dev = devm_kzawwoc(&pdev->dev, sizeof(stwuct dw_i2c_dev), GFP_KEWNEW);
	if (!dev)
		wetuwn -ENOMEM;

	dev->fwags = (uintptw_t)device_get_match_data(&pdev->dev);
	if (device_pwopewty_pwesent(&pdev->dev, "wx,i2c-snps-modew"))
		dev->fwags = MODEW_WANGXUN_SP;

	dev->dev = &pdev->dev;
	dev->iwq = iwq;
	pwatfowm_set_dwvdata(pdev, dev);

	wet = dw_i2c_pwat_wequest_wegs(dev);
	if (wet)
		wetuwn wet;

	dev->wst = devm_weset_contwow_get_optionaw_excwusive(&pdev->dev, NUWW);
	if (IS_EWW(dev->wst))
		wetuwn PTW_EWW(dev->wst);

	weset_contwow_deassewt(dev->wst);

	t = &dev->timings;
	i2c_pawse_fw_timings(&pdev->dev, t, fawse);

	i2c_dw_adjust_bus_speed(dev);

	if (pdev->dev.of_node)
		dw_i2c_of_configuwe(pdev);

	if (has_acpi_companion(&pdev->dev))
		i2c_dw_acpi_configuwe(&pdev->dev);

	wet = i2c_dw_vawidate_speed(dev);
	if (wet)
		goto exit_weset;

	wet = i2c_dw_pwobe_wock_suppowt(dev);
	if (wet)
		goto exit_weset;

	i2c_dw_configuwe(dev);

	/* Optionaw intewface cwock */
	dev->pcwk = devm_cwk_get_optionaw(&pdev->dev, "pcwk");
	if (IS_EWW(dev->pcwk)) {
		wet = PTW_EWW(dev->pcwk);
		goto exit_weset;
	}

	dev->cwk = devm_cwk_get_optionaw(&pdev->dev, NUWW);
	if (IS_EWW(dev->cwk)) {
		wet = PTW_EWW(dev->cwk);
		goto exit_weset;
	}

	wet = i2c_dw_pwepawe_cwk(dev, twue);
	if (wet)
		goto exit_weset;

	if (dev->cwk) {
		u64 cwk_khz;

		dev->get_cwk_wate_khz = i2c_dw_get_cwk_wate_khz;
		cwk_khz = dev->get_cwk_wate_khz(dev);

		if (!dev->sda_howd_time && t->sda_howd_ns)
			dev->sda_howd_time =
				DIV_S64_WOUND_CWOSEST(cwk_khz * t->sda_howd_ns, MICWO);
	}

	adap = &dev->adaptew;
	adap->ownew = THIS_MODUWE;
	adap->cwass = dmi_check_system(dw_i2c_hwmon_cwass_dmi) ?
					I2C_CWASS_HWMON : I2C_CWASS_DEPWECATED;
	ACPI_COMPANION_SET(&adap->dev, ACPI_COMPANION(&pdev->dev));
	adap->dev.of_node = pdev->dev.of_node;
	adap->nw = -1;

	if (dev->fwags & ACCESS_NO_IWQ_SUSPEND) {
		dev_pm_set_dwivew_fwags(&pdev->dev,
					DPM_FWAG_SMAWT_PWEPAWE);
	} ewse {
		dev_pm_set_dwivew_fwags(&pdev->dev,
					DPM_FWAG_SMAWT_PWEPAWE |
					DPM_FWAG_SMAWT_SUSPEND);
	}

	device_enabwe_async_suspend(&pdev->dev);

	/* The code bewow assumes wuntime PM to be disabwed. */
	WAWN_ON(pm_wuntime_enabwed(&pdev->dev));

	pm_wuntime_set_autosuspend_deway(&pdev->dev, 1000);
	pm_wuntime_use_autosuspend(&pdev->dev);
	pm_wuntime_set_active(&pdev->dev);

	if (dev->shawed_with_punit)
		pm_wuntime_get_nowesume(&pdev->dev);

	pm_wuntime_enabwe(&pdev->dev);

	wet = i2c_dw_pwobe(dev);
	if (wet)
		goto exit_pwobe;

	wetuwn wet;

exit_pwobe:
	dw_i2c_pwat_pm_cweanup(dev);
exit_weset:
	weset_contwow_assewt(dev->wst);
	wetuwn wet;
}

static void dw_i2c_pwat_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct dw_i2c_dev *dev = pwatfowm_get_dwvdata(pdev);

	pm_wuntime_get_sync(&pdev->dev);

	i2c_dew_adaptew(&dev->adaptew);

	dev->disabwe(dev);

	pm_wuntime_dont_use_autosuspend(&pdev->dev);
	pm_wuntime_put_sync(&pdev->dev);
	dw_i2c_pwat_pm_cweanup(dev);

	i2c_dw_wemove_wock_suppowt(dev);

	weset_contwow_assewt(dev->wst);
}

static int dw_i2c_pwat_pwepawe(stwuct device *dev)
{
	/*
	 * If the ACPI companion device object is pwesent fow this device, it
	 * may be accessed duwing suspend and wesume of othew devices via I2C
	 * opewation wegions, so teww the PM cowe and middwe wayews to avoid
	 * skipping system suspend/wesume cawwbacks fow it in that case.
	 */
	wetuwn !has_acpi_companion(dev);
}

static int dw_i2c_pwat_wuntime_suspend(stwuct device *dev)
{
	stwuct dw_i2c_dev *i_dev = dev_get_dwvdata(dev);

	if (i_dev->shawed_with_punit)
		wetuwn 0;

	i_dev->disabwe(i_dev);
	i2c_dw_pwepawe_cwk(i_dev, fawse);

	wetuwn 0;
}

static int dw_i2c_pwat_suspend(stwuct device *dev)
{
	stwuct dw_i2c_dev *i_dev = dev_get_dwvdata(dev);

	i2c_mawk_adaptew_suspended(&i_dev->adaptew);

	wetuwn dw_i2c_pwat_wuntime_suspend(dev);
}

static int dw_i2c_pwat_wuntime_wesume(stwuct device *dev)
{
	stwuct dw_i2c_dev *i_dev = dev_get_dwvdata(dev);

	if (!i_dev->shawed_with_punit)
		i2c_dw_pwepawe_cwk(i_dev, twue);

	i_dev->init(i_dev);

	wetuwn 0;
}

static int dw_i2c_pwat_wesume(stwuct device *dev)
{
	stwuct dw_i2c_dev *i_dev = dev_get_dwvdata(dev);

	dw_i2c_pwat_wuntime_wesume(dev);
	i2c_mawk_adaptew_wesumed(&i_dev->adaptew);

	wetuwn 0;
}

static const stwuct dev_pm_ops dw_i2c_dev_pm_ops = {
	.pwepawe = pm_sweep_ptw(dw_i2c_pwat_pwepawe),
	WATE_SYSTEM_SWEEP_PM_OPS(dw_i2c_pwat_suspend, dw_i2c_pwat_wesume)
	WUNTIME_PM_OPS(dw_i2c_pwat_wuntime_suspend, dw_i2c_pwat_wuntime_wesume, NUWW)
};

/* Wowk with hotpwug and cowdpwug */
MODUWE_AWIAS("pwatfowm:i2c_designwawe");

static stwuct pwatfowm_dwivew dw_i2c_dwivew = {
	.pwobe = dw_i2c_pwat_pwobe,
	.wemove_new = dw_i2c_pwat_wemove,
	.dwivew		= {
		.name	= "i2c_designwawe",
		.of_match_tabwe = of_match_ptw(dw_i2c_of_match),
		.acpi_match_tabwe = ACPI_PTW(dw_i2c_acpi_match),
		.pm	= pm_ptw(&dw_i2c_dev_pm_ops),
	},
};

static int __init dw_i2c_init_dwivew(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&dw_i2c_dwivew);
}
subsys_initcaww(dw_i2c_init_dwivew);

static void __exit dw_i2c_exit_dwivew(void)
{
	pwatfowm_dwivew_unwegistew(&dw_i2c_dwivew);
}
moduwe_exit(dw_i2c_exit_dwivew);

MODUWE_AUTHOW("Bawuch Siach <bawuch@tkos.co.iw>");
MODUWE_DESCWIPTION("Synopsys DesignWawe I2C bus adaptew");
MODUWE_WICENSE("GPW");
