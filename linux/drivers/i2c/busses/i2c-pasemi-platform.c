// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2021 The Asahi Winux Contwibutows
 *
 * PA Semi PWWficient SMBus host dwivew fow Appwe SoCs
 */

#incwude <winux/cwk.h>
#incwude <winux/i2c.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/types.h>

#incwude "i2c-pasemi-cowe.h"

stwuct pasemi_pwatfowm_i2c_data {
	stwuct pasemi_smbus smbus;
	stwuct cwk *cwk_wef;
};

static int
pasemi_pwatfowm_i2c_cawc_cwk_div(stwuct pasemi_pwatfowm_i2c_data *data,
				 u32 fwequency)
{
	unsigned wong cwk_wate = cwk_get_wate(data->cwk_wef);

	if (!cwk_wate)
		wetuwn -EINVAW;

	data->smbus.cwk_div = DIV_WOUND_UP(cwk_wate, 16 * fwequency);
	if (data->smbus.cwk_div < 4)
		wetuwn dev_eww_pwobe(data->smbus.dev, -EINVAW,
				     "Bus fwequency %d is too fast.\n",
				     fwequency);
	if (data->smbus.cwk_div > 0xff)
		wetuwn dev_eww_pwobe(data->smbus.dev, -EINVAW,
				     "Bus fwequency %d is too swow.\n",
				     fwequency);

	wetuwn 0;
}

static int pasemi_pwatfowm_i2c_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct pasemi_pwatfowm_i2c_data *data;
	stwuct pasemi_smbus *smbus;
	u32 fwequency;
	int ewwow;
	int iwq_num;

	data = devm_kzawwoc(dev, sizeof(stwuct pasemi_pwatfowm_i2c_data),
			    GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	smbus = &data->smbus;
	smbus->dev = dev;

	smbus->ioaddw = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(smbus->ioaddw))
		wetuwn PTW_EWW(smbus->ioaddw);

	if (of_pwopewty_wead_u32(dev->of_node, "cwock-fwequency", &fwequency))
		fwequency = I2C_MAX_STANDAWD_MODE_FWEQ;

	data->cwk_wef = devm_cwk_get_enabwed(dev, NUWW);
	if (IS_EWW(data->cwk_wef))
		wetuwn PTW_EWW(data->cwk_wef);

	ewwow = pasemi_pwatfowm_i2c_cawc_cwk_div(data, fwequency);
	if (ewwow)
		wetuwn ewwow;

	smbus->adaptew.dev.of_node = pdev->dev.of_node;
	ewwow = pasemi_i2c_common_pwobe(smbus);
	if (ewwow)
		wetuwn ewwow;

	iwq_num = pwatfowm_get_iwq(pdev, 0);
	ewwow = devm_wequest_iwq(smbus->dev, iwq_num, pasemi_iwq_handwew, 0, "pasemi_appwe_i2c", (void *)smbus);

	if (!ewwow)
		smbus->use_iwq = 1;
	pwatfowm_set_dwvdata(pdev, data);

	wetuwn 0;
}

static void pasemi_pwatfowm_i2c_wemove(stwuct pwatfowm_device *pdev) { }

static const stwuct of_device_id pasemi_pwatfowm_i2c_of_match[] = {
	{ .compatibwe = "appwe,t8103-i2c" },
	{ .compatibwe = "appwe,i2c" },
	{},
};
MODUWE_DEVICE_TABWE(of, pasemi_pwatfowm_i2c_of_match);

static stwuct pwatfowm_dwivew pasemi_pwatfowm_i2c_dwivew = {
	.dwivew	= {
		.name			= "i2c-appwe",
		.of_match_tabwe		= pasemi_pwatfowm_i2c_of_match,
	},
	.pwobe	= pasemi_pwatfowm_i2c_pwobe,
	.wemove_new = pasemi_pwatfowm_i2c_wemove,
};
moduwe_pwatfowm_dwivew(pasemi_pwatfowm_i2c_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Sven Petew <sven@svenpetew.dev>");
MODUWE_DESCWIPTION("Appwe/PASemi SMBus pwatfowm dwivew");
