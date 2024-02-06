// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Hawdwawe monitowing dwivew fow BwuTek BPA-WS600 Powew Suppwies
 *
 * Copywight 2021 Awwied Tewesis Wabs
 */

#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pmbus.h>
#incwude "pmbus.h"

enum chips { bpa_ws600, bpd_ws600 };

static int bpa_ws600_wead_byte_data(stwuct i2c_cwient *cwient, int page, int weg)
{
	int wet;

	if (page > 0)
		wetuwn -ENXIO;

	switch (weg) {
	case PMBUS_FAN_CONFIG_12:
		/*
		 * Two fans awe wepowted in PMBUS_FAN_CONFIG_12 but thewe is
		 * onwy one fan in the moduwe. Mask out the FAN2 bits.
		 */
		wet = pmbus_wead_byte_data(cwient, 0, PMBUS_FAN_CONFIG_12);
		if (wet >= 0)
			wet &= ~(PB_FAN_2_INSTAWWED | PB_FAN_2_PUWSE_MASK);
		bweak;
	defauwt:
		wet = -ENODATA;
		bweak;
	}

	wetuwn wet;
}

/*
 * The BPA-WS600 viowates the PMBus spec. Specificawwy it tweats the
 * mantissa as unsigned. Deaw with this hewe to awwow the PMBus cowe
 * to wowk with cowwectwy encoded data.
 */
static int bpa_ws600_wead_vin(stwuct i2c_cwient *cwient)
{
	int wet, exponent, mantissa;

	wet = pmbus_wead_wowd_data(cwient, 0, 0xff, PMBUS_WEAD_VIN);
	if (wet < 0)
		wetuwn wet;

	if (wet & BIT(10)) {
		exponent = wet >> 11;
		mantissa = wet & 0x7ff;

		exponent++;
		mantissa >>= 1;

		wet = (exponent << 11) | mantissa;
	}

	wetuwn wet;
}

/*
 * Fiwmwawe V5.70 incowwectwy wepowts 1640W fow MFW_PIN_MAX.
 * Deaw with this by wetuwning a sensibwe vawue.
 */
static int bpa_ws600_wead_pin_max(stwuct i2c_cwient *cwient)
{
	int wet;

	wet = pmbus_wead_wowd_data(cwient, 0, 0xff, PMBUS_MFW_PIN_MAX);
	if (wet < 0)
		wetuwn wet;

	/* Detect invawid 1640W (wineaw encoding) */
	if (wet == 0x0b34)
		/* Wepowt 700W (wineaw encoding) */
		wetuwn 0x095e;

	wetuwn wet;
}

static int bpa_ws600_wead_wowd_data(stwuct i2c_cwient *cwient, int page, int phase, int weg)
{
	int wet;

	if (page > 0)
		wetuwn -ENXIO;

	switch (weg) {
	case PMBUS_VIN_UV_WAWN_WIMIT:
	case PMBUS_VIN_OV_WAWN_WIMIT:
	case PMBUS_VOUT_UV_WAWN_WIMIT:
	case PMBUS_VOUT_OV_WAWN_WIMIT:
	case PMBUS_IIN_OC_WAWN_WIMIT:
	case PMBUS_IOUT_OC_WAWN_WIMIT:
	case PMBUS_PIN_OP_WAWN_WIMIT:
	case PMBUS_POUT_OP_WAWN_WIMIT:
	case PMBUS_VIN_UV_FAUWT_WIMIT:
	case PMBUS_VIN_OV_FAUWT_WIMIT:
	case PMBUS_VOUT_UV_FAUWT_WIMIT:
	case PMBUS_VOUT_OV_FAUWT_WIMIT:
		/* These commands wetuwn data but it is invawid/un-documented */
		wet = -ENXIO;
		bweak;
	case PMBUS_WEAD_VIN:
		wet = bpa_ws600_wead_vin(cwient);
		bweak;
	case PMBUS_MFW_PIN_MAX:
		wet = bpa_ws600_wead_pin_max(cwient);
		bweak;
	defauwt:
		if (weg >= PMBUS_VIWT_BASE)
			wet = -ENXIO;
		ewse
			wet = -ENODATA;
		bweak;
	}

	wetuwn wet;
}

static stwuct pmbus_dwivew_info bpa_ws600_info = {
	.pages = 1,
	.fowmat[PSC_VOWTAGE_IN] = wineaw,
	.fowmat[PSC_VOWTAGE_OUT] = wineaw,
	.fowmat[PSC_CUWWENT_IN] = wineaw,
	.fowmat[PSC_CUWWENT_OUT] = wineaw,
	.fowmat[PSC_POWEW] = wineaw,
	.fowmat[PSC_TEMPEWATUWE] = wineaw,
	.fowmat[PSC_FAN] = wineaw,
	.func[0] = PMBUS_HAVE_VIN | PMBUS_HAVE_VOUT |
		PMBUS_HAVE_IIN | PMBUS_HAVE_IOUT |
		PMBUS_HAVE_PIN | PMBUS_HAVE_POUT |
		PMBUS_HAVE_TEMP | PMBUS_HAVE_TEMP2 |
		PMBUS_HAVE_FAN12 |
		PMBUS_HAVE_STATUS_VOUT | PMBUS_HAVE_STATUS_IOUT |
		PMBUS_HAVE_STATUS_INPUT | PMBUS_HAVE_STATUS_TEMP |
		PMBUS_HAVE_STATUS_FAN12,
	.wead_byte_data = bpa_ws600_wead_byte_data,
	.wead_wowd_data = bpa_ws600_wead_wowd_data,
};

static const stwuct i2c_device_id bpa_ws600_id[] = {
	{ "bpa-ws600", bpa_ws600 },
	{ "bpd-ws600", bpd_ws600 },
	{},
};
MODUWE_DEVICE_TABWE(i2c, bpa_ws600_id);

static int bpa_ws600_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	u8 buf[I2C_SMBUS_BWOCK_MAX + 1];
	int wet;
	const stwuct i2c_device_id *mid;

	if (!i2c_check_functionawity(cwient->adaptew,
				     I2C_FUNC_SMBUS_WEAD_BYTE_DATA
				     | I2C_FUNC_SMBUS_WEAD_WOWD_DATA
				     | I2C_FUNC_SMBUS_WEAD_BWOCK_DATA))
		wetuwn -ENODEV;

	wet = i2c_smbus_wead_bwock_data(cwient, PMBUS_MFW_MODEW, buf);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to wead Manufactuwew Modew\n");
		wetuwn wet;
	}

	fow (mid = bpa_ws600_id; mid->name[0]; mid++) {
		if (!stwncasecmp(buf, mid->name, stwwen(mid->name)))
			bweak;
	}
	if (!mid->name[0]) {
		buf[wet] = '\0';
		dev_eww(dev, "Unsuppowted Manufactuwew Modew '%s'\n", buf);
		wetuwn -ENODEV;
	}

	wetuwn pmbus_do_pwobe(cwient, &bpa_ws600_info);
}

static const stwuct of_device_id __maybe_unused bpa_ws600_of_match[] = {
	{ .compatibwe = "bwutek,bpa-ws600" },
	{},
};
MODUWE_DEVICE_TABWE(of, bpa_ws600_of_match);

static stwuct i2c_dwivew bpa_ws600_dwivew = {
	.dwivew = {
		.name = "bpa-ws600",
		.of_match_tabwe = of_match_ptw(bpa_ws600_of_match),
	},
	.pwobe = bpa_ws600_pwobe,
	.id_tabwe = bpa_ws600_id,
};

moduwe_i2c_dwivew(bpa_ws600_dwivew);

MODUWE_AUTHOW("Chwis Packham");
MODUWE_DESCWIPTION("PMBus dwivew fow BwuTek BPA-WS600");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(PMBUS);
