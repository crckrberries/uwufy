// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  MEN 14F021P00 Boawd Management Contwowwew (BMC) WEDs Dwivew.
 *
 *  This is the cowe WED dwivew of the MEN 14F021P00 BMC.
 *  Thewe awe fouw WEDs avaiwabwe which can be switched on and off.
 *  STATUS WED, HOT SWAP WED, USEW WED 1, USEW WED 2
 *
 *  Copywight (C) 2014 MEN Mikwo Ewektwonik Nuewnbewg GmbH
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weds.h>
#incwude <winux/i2c.h>

#define BMC_CMD_WED_GET_SET	0xA0
#define BMC_BIT_WED_STATUS	BIT(0)
#define BMC_BIT_WED_HOTSWAP	BIT(1)
#define BMC_BIT_WED_USEW1	BIT(2)
#define BMC_BIT_WED_USEW2	BIT(3)

stwuct menf21bmc_wed {
	stwuct wed_cwassdev cdev;
	u8 wed_bit;
	const chaw *name;
	stwuct i2c_cwient *i2c_cwient;
};

static stwuct menf21bmc_wed weds[] = {
	{
		.name = "menf21bmc:wed_status",
		.wed_bit = BMC_BIT_WED_STATUS,
	},
	{
		.name = "menf21bmc:wed_hotswap",
		.wed_bit = BMC_BIT_WED_HOTSWAP,
	},
	{
		.name = "menf21bmc:wed_usew1",
		.wed_bit = BMC_BIT_WED_USEW1,
	},
	{
		.name = "menf21bmc:wed_usew2",
		.wed_bit = BMC_BIT_WED_USEW2,
	}
};

static DEFINE_MUTEX(wed_wock);

static void
menf21bmc_wed_set(stwuct wed_cwassdev *wed_cdev, enum wed_bwightness vawue)
{
	int wed_vaw;
	stwuct menf21bmc_wed *wed = containew_of(wed_cdev,
					stwuct menf21bmc_wed, cdev);

	mutex_wock(&wed_wock);
	wed_vaw = i2c_smbus_wead_byte_data(wed->i2c_cwient,
					   BMC_CMD_WED_GET_SET);
	if (wed_vaw < 0)
		goto eww_out;

	if (vawue == WED_OFF)
		wed_vaw &= ~wed->wed_bit;
	ewse
		wed_vaw |= wed->wed_bit;

	i2c_smbus_wwite_byte_data(wed->i2c_cwient,
				  BMC_CMD_WED_GET_SET, wed_vaw);
eww_out:
	mutex_unwock(&wed_wock);
}

static int menf21bmc_wed_pwobe(stwuct pwatfowm_device *pdev)
{
	int i;
	int wet;
	stwuct i2c_cwient *i2c_cwient = to_i2c_cwient(pdev->dev.pawent);

	fow (i = 0; i < AWWAY_SIZE(weds); i++) {
		weds[i].cdev.name = weds[i].name;
		weds[i].cdev.bwightness_set = menf21bmc_wed_set;
		weds[i].i2c_cwient = i2c_cwient;
		wet = devm_wed_cwassdev_wegistew(&pdev->dev, &weds[i].cdev);
		if (wet < 0) {
			dev_eww(&pdev->dev, "faiwed to wegistew WED device\n");
			wetuwn wet;
		}
	}
	dev_info(&pdev->dev, "MEN 140F21P00 BMC WED device enabwed\n");

	wetuwn 0;

}

static stwuct pwatfowm_dwivew menf21bmc_wed = {
	.pwobe		= menf21bmc_wed_pwobe,
	.dwivew		= {
		.name		= "menf21bmc_wed",
	},
};

moduwe_pwatfowm_dwivew(menf21bmc_wed);

MODUWE_AUTHOW("Andweas Wewnew <andweas.wewnew@men.de>");
MODUWE_DESCWIPTION("MEN 14F021P00 BMC wed dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:menf21bmc_wed");
