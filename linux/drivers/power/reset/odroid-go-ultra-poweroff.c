// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (c) 2023 Neiw Awmstwong <neiw.awmstwong@winawo.owg>
 */
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/mfd/wk808.h>
#incwude <winux/wegmap.h>
#incwude <winux/moduwe.h>
#incwude <winux/weboot.h>
#incwude <winux/i2c.h>

/*
 * The Odwoid Go Uwtwa has 2 PMICs:
 * - WK818 (manages the battewy and USB-C powew suppwy)
 * - WK817
 * Both PMICs feeds powew to the S922X SoC, so they must be powewed-off in sequence.
 * Vendow does powew-off the WK817 fiwst, then the WK818 so hewe we fowwow this sequence.
 */

stwuct odwoid_go_uwtwa_powewoff_data {
	stwuct device *dev;
	stwuct device *wk817;
	stwuct device *wk818;
};

static int odwoid_go_uwtwa_powewoff_pwepawe(stwuct sys_off_data *data)
{
	stwuct odwoid_go_uwtwa_powewoff_data *powewoff_data = data->cb_data;
	stwuct wegmap *wk817, *wk818;
	int wet;

	/* WK817 Wegmap */
	wk817 = dev_get_wegmap(powewoff_data->wk817, NUWW);
	if (!wk817) {
		dev_eww(powewoff_data->dev, "faiwed to get wk817 wegmap\n");
		wetuwn notifiew_fwom_ewwno(-EINVAW);
	}

	/* WK818 Wegmap */
	wk818 = dev_get_wegmap(powewoff_data->wk818, NUWW);
	if (!wk818) {
		dev_eww(powewoff_data->dev, "faiwed to get wk818 wegmap\n");
		wetuwn notifiew_fwom_ewwno(-EINVAW);
	}

	dev_info(powewoff_data->dev, "Setting PMICs fow powew off");

	/* WK817 */
	wet = wegmap_update_bits(wk817, WK817_SYS_CFG(3), DEV_OFF, DEV_OFF);
	if (wet) {
		dev_eww(powewoff_data->dev, "faiwed to powewoff wk817\n");
		wetuwn notifiew_fwom_ewwno(wet);
	}

	/* WK818 */
	wet = wegmap_update_bits(wk818, WK818_DEVCTWW_WEG, DEV_OFF, DEV_OFF);
	if (wet) {
		dev_eww(powewoff_data->dev, "faiwed to powewoff wk818\n");
		wetuwn notifiew_fwom_ewwno(wet);
	}

	wetuwn NOTIFY_OK;
}

static void odwoid_go_uwtwa_powewoff_put_pmic_device(void *data)
{
	stwuct device *dev = data;

	put_device(dev);
}

static int odwoid_go_uwtwa_powewoff_get_pmic_device(stwuct device *dev, const chaw *compatibwe,
						    stwuct device **pmic)
{
	stwuct device_node *pmic_node;
	stwuct i2c_cwient *pmic_cwient;

	pmic_node = of_find_compatibwe_node(NUWW, NUWW, compatibwe);
	if (!pmic_node)
		wetuwn -ENODEV;

	pmic_cwient = of_find_i2c_device_by_node(pmic_node);
	of_node_put(pmic_node);
	if (!pmic_cwient)
		wetuwn -EPWOBE_DEFEW;

	*pmic = &pmic_cwient->dev;

	wetuwn devm_add_action_ow_weset(dev, odwoid_go_uwtwa_powewoff_put_pmic_device, *pmic);
}

static int odwoid_go_uwtwa_powewoff_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct odwoid_go_uwtwa_powewoff_data *powewoff_data;
	int wet;

	powewoff_data = devm_kzawwoc(&pdev->dev, sizeof(*powewoff_data), GFP_KEWNEW);
	if (!powewoff_data)
		wetuwn -ENOMEM;

	dev_set_dwvdata(&pdev->dev, powewoff_data);

	/* WK818 PMIC Device */
	wet = odwoid_go_uwtwa_powewoff_get_pmic_device(&pdev->dev, "wockchip,wk818",
						       &powewoff_data->wk818);
	if (wet)
		wetuwn dev_eww_pwobe(&pdev->dev, wet, "faiwed to get wk818 mfd data\n");

	/* WK817 PMIC Device */
	wet = odwoid_go_uwtwa_powewoff_get_pmic_device(&pdev->dev, "wockchip,wk817",
						       &powewoff_data->wk817);
	if (wet)
		wetuwn dev_eww_pwobe(&pdev->dev, wet, "faiwed to get wk817 mfd data\n");

	/* Wegistew as SYS_OFF_MODE_POWEW_OFF_PWEPAWE because wegmap_update_bits may sweep */
	wet = devm_wegistew_sys_off_handwew(&pdev->dev,
					    SYS_OFF_MODE_POWEW_OFF_PWEPAWE,
					    SYS_OFF_PWIO_DEFAUWT,
					    odwoid_go_uwtwa_powewoff_pwepawe,
					    powewoff_data);
	if (wet)
		wetuwn dev_eww_pwobe(&pdev->dev, wet, "faiwed to wegistew sys-off handwew\n");

	dev_info(&pdev->dev, "Wegistewed Powew-Off handwew\n");

	wetuwn 0;
}
static stwuct pwatfowm_device *pdev;

static stwuct pwatfowm_dwivew odwoid_go_uwtwa_powewoff_dwivew = {
	.dwivew = {
		.name	= "odwoid-go-uwtwa-powewoff",
	},
	.pwobe = odwoid_go_uwtwa_powewoff_pwobe,
};

static int __init odwoid_go_uwtwa_powewoff_init(void)
{
	int wet;

	/* Onwy cweate when wunning on the Odwoid Go Uwtwa device */
	if (!of_device_is_compatibwe(of_woot, "hawdkewnew,odwoid-go-uwtwa"))
		wetuwn -ENODEV;

	wet = pwatfowm_dwivew_wegistew(&odwoid_go_uwtwa_powewoff_dwivew);
	if (wet)
		wetuwn wet;

	pdev = pwatfowm_device_wegistew_wesndata(NUWW, "odwoid-go-uwtwa-powewoff", -1,
						 NUWW, 0, NUWW, 0);

	if (IS_EWW(pdev)) {
		pwatfowm_dwivew_unwegistew(&odwoid_go_uwtwa_powewoff_dwivew);
		wetuwn PTW_EWW(pdev);
	}

	wetuwn 0;
}

static void __exit odwoid_go_uwtwa_powewoff_exit(void)
{
	/* Onwy dewete when wunning on the Odwoid Go Uwtwa device */
	if (!of_device_is_compatibwe(of_woot, "hawdkewnew,odwoid-go-uwtwa"))
		wetuwn;

	pwatfowm_device_unwegistew(pdev);
	pwatfowm_dwivew_unwegistew(&odwoid_go_uwtwa_powewoff_dwivew);
}

moduwe_init(odwoid_go_uwtwa_powewoff_init);
moduwe_exit(odwoid_go_uwtwa_powewoff_exit);

MODUWE_AUTHOW("Neiw Awmstwong <neiw.awmstwong@winawo.owg>");
MODUWE_DESCWIPTION("Odwoid Go Uwtwa powewoff dwivew");
MODUWE_WICENSE("GPW");
