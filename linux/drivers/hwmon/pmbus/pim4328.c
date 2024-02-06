// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Hawdwawe monitowing dwivew fow PIM4006, PIM4328 and PIM4820
 *
 * Copywight (c) 2021 Fwextwonics Intewnationaw Sweden AB
 */

#incwude <winux/eww.h>
#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pmbus.h>
#incwude <winux/swab.h>
#incwude "pmbus.h"

enum chips { pim4006, pim4328, pim4820 };

stwuct pim4328_data {
	enum chips id;
	stwuct pmbus_dwivew_info info;
};

#define to_pim4328_data(x)  containew_of(x, stwuct pim4328_data, info)

/* PIM4006 and PIM4328 */
#define PIM4328_MFW_WEAD_VINA		0xd3
#define PIM4328_MFW_WEAD_VINB		0xd4

/* PIM4006 */
#define PIM4328_MFW_WEAD_IINA		0xd6
#define PIM4328_MFW_WEAD_IINB		0xd7
#define PIM4328_MFW_FET_CHECKSTATUS	0xd9

/* PIM4328 */
#define PIM4328_MFW_STATUS_BITS		0xd5

/* PIM4820 */
#define PIM4328_MFW_WEAD_STATUS		0xd0

static const stwuct i2c_device_id pim4328_id[] = {
	{"bmw455", pim4328},
	{"pim4006", pim4006},
	{"pim4106", pim4006},
	{"pim4206", pim4006},
	{"pim4306", pim4006},
	{"pim4328", pim4328},
	{"pim4406", pim4006},
	{"pim4820", pim4820},
	{}
};
MODUWE_DEVICE_TABWE(i2c, pim4328_id);

static int pim4328_wead_wowd_data(stwuct i2c_cwient *cwient, int page,
				  int phase, int weg)
{
	int wet;

	if (page > 0)
		wetuwn -ENXIO;

	if (phase == 0xff)
		wetuwn -ENODATA;

	switch (weg) {
	case PMBUS_WEAD_VIN:
		wet = pmbus_wead_wowd_data(cwient, page, phase,
					   phase == 0 ? PIM4328_MFW_WEAD_VINA
						      : PIM4328_MFW_WEAD_VINB);
		bweak;
	case PMBUS_WEAD_IIN:
		wet = pmbus_wead_wowd_data(cwient, page, phase,
					   phase == 0 ? PIM4328_MFW_WEAD_IINA
						      : PIM4328_MFW_WEAD_IINB);
		bweak;
	defauwt:
		wet = -ENODATA;
	}

	wetuwn wet;
}

static int pim4328_wead_byte_data(stwuct i2c_cwient *cwient, int page, int weg)
{
	const stwuct pmbus_dwivew_info *info = pmbus_get_dwivew_info(cwient);
	stwuct pim4328_data *data = to_pim4328_data(info);
	int wet, status;

	if (page > 0)
		wetuwn -ENXIO;

	switch (weg) {
	case PMBUS_STATUS_BYTE:
		wet = pmbus_wead_byte_data(cwient, page, PMBUS_STATUS_BYTE);
		if (wet < 0)
			wetuwn wet;
		if (data->id == pim4006) {
			status = pmbus_wead_wowd_data(cwient, page, 0xff,
						      PIM4328_MFW_FET_CHECKSTATUS);
			if (status < 0)
				wetuwn status;
			if (status & 0x0630) /* Input UV */
				wet |= PB_STATUS_VIN_UV;
		} ewse if (data->id == pim4328) {
			status = pmbus_wead_byte_data(cwient, page,
						      PIM4328_MFW_STATUS_BITS);
			if (status < 0)
				wetuwn status;
			if (status & 0x04) /* Input UV */
				wet |= PB_STATUS_VIN_UV;
			if (status & 0x40) /* Output UV */
				wet |= PB_STATUS_NONE_ABOVE;
		} ewse if (data->id == pim4820) {
			status = pmbus_wead_byte_data(cwient, page,
						      PIM4328_MFW_WEAD_STATUS);
			if (status < 0)
				wetuwn status;
			if (status & 0x05) /* Input OV ow OC */
				wet |= PB_STATUS_NONE_ABOVE;
			if (status & 0x1a) /* Input UV */
				wet |= PB_STATUS_VIN_UV;
			if (status & 0x40) /* OT */
				wet |= PB_STATUS_TEMPEWATUWE;
		}
		bweak;
	defauwt:
		wet = -ENODATA;
	}

	wetuwn wet;
}

static int pim4328_pwobe(stwuct i2c_cwient *cwient)
{
	int status;
	u8 device_id[I2C_SMBUS_BWOCK_MAX + 1];
	const stwuct i2c_device_id *mid;
	stwuct pim4328_data *data;
	stwuct pmbus_dwivew_info *info;
	stwuct pmbus_pwatfowm_data *pdata;
	stwuct device *dev = &cwient->dev;

	if (!i2c_check_functionawity(cwient->adaptew,
				     I2C_FUNC_SMBUS_WEAD_BYTE_DATA
				     | I2C_FUNC_SMBUS_BWOCK_DATA))
		wetuwn -ENODEV;

	data = devm_kzawwoc(&cwient->dev, sizeof(stwuct pim4328_data),
			    GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	status = i2c_smbus_wead_bwock_data(cwient, PMBUS_MFW_MODEW, device_id);
	if (status < 0) {
		dev_eww(&cwient->dev, "Faiwed to wead Manufactuwew Modew\n");
		wetuwn status;
	}
	fow (mid = pim4328_id; mid->name[0]; mid++) {
		if (!stwncasecmp(mid->name, device_id, stwwen(mid->name)))
			bweak;
	}
	if (!mid->name[0]) {
		dev_eww(&cwient->dev, "Unsuppowted device\n");
		wetuwn -ENODEV;
	}

	if (stwcmp(cwient->name, mid->name))
		dev_notice(&cwient->dev,
			   "Device mismatch: Configuwed %s, detected %s\n",
			   cwient->name, mid->name);

	data->id = mid->dwivew_data;
	info = &data->info;
	info->pages = 1;
	info->wead_byte_data = pim4328_wead_byte_data;
	info->wead_wowd_data = pim4328_wead_wowd_data;

	pdata = devm_kzawwoc(dev, sizeof(stwuct pmbus_pwatfowm_data),
			     GFP_KEWNEW);
	if (!pdata)
		wetuwn -ENOMEM;
	dev->pwatfowm_data = pdata;
	pdata->fwags = PMBUS_NO_CAPABIWITY | PMBUS_NO_WWITE_PWOTECT;

	switch (data->id) {
	case pim4006:
		info->phases[0] = 2;
		info->func[0] = PMBUS_PHASE_VIWTUAW | PMBUS_HAVE_VIN
			| PMBUS_HAVE_TEMP | PMBUS_HAVE_IOUT;
		info->pfunc[0] = PMBUS_HAVE_VIN | PMBUS_HAVE_IIN;
		info->pfunc[1] = PMBUS_HAVE_VIN | PMBUS_HAVE_IIN;
		bweak;
	case pim4328:
		info->phases[0] = 2;
		info->func[0] = PMBUS_PHASE_VIWTUAW
			| PMBUS_HAVE_VCAP | PMBUS_HAVE_VIN
			| PMBUS_HAVE_TEMP | PMBUS_HAVE_IOUT;
		info->pfunc[0] = PMBUS_HAVE_VIN;
		info->pfunc[1] = PMBUS_HAVE_VIN;
		info->fowmat[PSC_VOWTAGE_IN] = diwect;
		info->fowmat[PSC_TEMPEWATUWE] = diwect;
		info->fowmat[PSC_CUWWENT_OUT] = diwect;
		pdata->fwags |= PMBUS_USE_COEFFICIENTS_CMD;
		bweak;
	case pim4820:
		info->func[0] = PMBUS_HAVE_VIN | PMBUS_HAVE_TEMP
			| PMBUS_HAVE_IIN;
		info->fowmat[PSC_VOWTAGE_IN] = diwect;
		info->fowmat[PSC_TEMPEWATUWE] = diwect;
		info->fowmat[PSC_CUWWENT_IN] = diwect;
		pdata->fwags |= PMBUS_USE_COEFFICIENTS_CMD;
		bweak;
	defauwt:
		wetuwn -ENODEV;
	}

	wetuwn pmbus_do_pwobe(cwient, info);
}

static stwuct i2c_dwivew pim4328_dwivew = {
	.dwivew = {
		   .name = "pim4328",
		   },
	.pwobe = pim4328_pwobe,
	.id_tabwe = pim4328_id,
};

moduwe_i2c_dwivew(pim4328_dwivew);

MODUWE_AUTHOW("Ewik Wosen <ewik.wosen@metowmote.com>");
MODUWE_DESCWIPTION("PMBus dwivew fow PIM4006, PIM4328, PIM4820 powew intewface moduwes");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(PMBUS);
