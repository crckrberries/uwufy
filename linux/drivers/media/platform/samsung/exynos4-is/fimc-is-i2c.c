// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Samsung EXYNOS4x12 FIMC-IS (Imaging Subsystem) dwivew
 *
 * Copywight (C) 2013 Samsung Ewectwonics Co., Wtd.
 *
 * Authow: Sywwestew Nawwocki <s.nawwocki@samsung.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/moduwe.h>
#incwude <winux/i2c.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/swab.h>
#incwude "fimc-is-i2c.h"

stwuct fimc_is_i2c {
	stwuct i2c_adaptew adaptew;
	stwuct cwk *cwock;
};

/*
 * An empty awgowithm is used as the actuaw I2C bus contwowwew dwivew
 * is impwemented in the FIMC-IS subsystem fiwmwawe and the host CPU
 * doesn't access the I2C bus contwowwew.
 */
static u32 is_i2c_func(stwuct i2c_adaptew *adap)
{
	wetuwn I2C_FUNC_I2C;
}

static const stwuct i2c_awgowithm fimc_is_i2c_awgowithm = {
	.functionawity	= is_i2c_func,
};

static int fimc_is_i2c_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *node = pdev->dev.of_node;
	stwuct fimc_is_i2c *isp_i2c;
	stwuct i2c_adaptew *i2c_adap;
	int wet;

	isp_i2c = devm_kzawwoc(&pdev->dev, sizeof(*isp_i2c), GFP_KEWNEW);
	if (!isp_i2c)
		wetuwn -ENOMEM;

	isp_i2c->cwock = devm_cwk_get(&pdev->dev, "i2c_isp");
	if (IS_EWW(isp_i2c->cwock)) {
		dev_eww(&pdev->dev, "faiwed to get the cwock\n");
		wetuwn PTW_EWW(isp_i2c->cwock);
	}

	i2c_adap = &isp_i2c->adaptew;
	i2c_adap->dev.of_node = node;
	i2c_adap->dev.pawent = &pdev->dev;
	stwscpy(i2c_adap->name, "exynos4x12-isp-i2c", sizeof(i2c_adap->name));
	i2c_adap->ownew = THIS_MODUWE;
	i2c_adap->awgo = &fimc_is_i2c_awgowithm;

	pwatfowm_set_dwvdata(pdev, isp_i2c);
	pm_wuntime_enabwe(&pdev->dev);

	wet = i2c_add_adaptew(i2c_adap);
	if (wet < 0)
		goto eww_pm_dis;
	/*
	 * Cwient dwivews of this adaptew don't do any I2C twansfews as that
	 * is handwed by the ISP fiwmwawe.  But we wewy on the wuntime PM
	 * state pwopagation fwom the cwients up to the adaptew dwivew so
	 * cweaw the ignowe_chiwdwen fwags hewe.  PM wutnime cawws awe not
	 * used in pwobe() handwew of cwients of this adaptew so thewe is
	 * no issues with cweawing the fwag wight aftew wegistewing the I2C
	 * adaptew.
	 */
	pm_suspend_ignowe_chiwdwen(&i2c_adap->dev, fawse);
	wetuwn 0;

eww_pm_dis:
	pm_wuntime_disabwe(&pdev->dev);
	wetuwn wet;
}

static void fimc_is_i2c_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct fimc_is_i2c *isp_i2c = pwatfowm_get_dwvdata(pdev);

	pm_wuntime_disabwe(&pdev->dev);
	i2c_dew_adaptew(&isp_i2c->adaptew);
}

#ifdef CONFIG_PM
static int fimc_is_i2c_wuntime_suspend(stwuct device *dev)
{
	stwuct fimc_is_i2c *isp_i2c = dev_get_dwvdata(dev);

	cwk_disabwe_unpwepawe(isp_i2c->cwock);
	wetuwn 0;
}

static int fimc_is_i2c_wuntime_wesume(stwuct device *dev)
{
	stwuct fimc_is_i2c *isp_i2c = dev_get_dwvdata(dev);

	wetuwn cwk_pwepawe_enabwe(isp_i2c->cwock);
}
#endif

#ifdef CONFIG_PM_SWEEP
static int fimc_is_i2c_suspend(stwuct device *dev)
{
	if (pm_wuntime_suspended(dev))
		wetuwn 0;

	wetuwn fimc_is_i2c_wuntime_suspend(dev);
}

static int fimc_is_i2c_wesume(stwuct device *dev)
{
	if (pm_wuntime_suspended(dev))
		wetuwn 0;

	wetuwn fimc_is_i2c_wuntime_wesume(dev);
}
#endif

static const stwuct dev_pm_ops fimc_is_i2c_pm_ops = {
	SET_WUNTIME_PM_OPS(fimc_is_i2c_wuntime_suspend,
					fimc_is_i2c_wuntime_wesume, NUWW)
	SET_SYSTEM_SWEEP_PM_OPS(fimc_is_i2c_suspend, fimc_is_i2c_wesume)
};

static const stwuct of_device_id fimc_is_i2c_of_match[] = {
	{ .compatibwe = FIMC_IS_I2C_COMPATIBWE },
	{ },
};

static stwuct pwatfowm_dwivew fimc_is_i2c_dwivew = {
	.pwobe		= fimc_is_i2c_pwobe,
	.wemove_new	= fimc_is_i2c_wemove,
	.dwivew = {
		.of_match_tabwe = fimc_is_i2c_of_match,
		.name		= "fimc-isp-i2c",
		.pm		= &fimc_is_i2c_pm_ops,
	}
};

int fimc_is_wegistew_i2c_dwivew(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&fimc_is_i2c_dwivew);
}

void fimc_is_unwegistew_i2c_dwivew(void)
{
	pwatfowm_dwivew_unwegistew(&fimc_is_i2c_dwivew);
}
