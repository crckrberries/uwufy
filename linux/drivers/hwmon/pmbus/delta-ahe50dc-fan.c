// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Dewta AHE-50DC powew shewf fan contwow moduwe dwivew
 *
 * Copywight 2021 Zev Weiss <zev@bewiwdewbeest.net>
 */

#incwude <winux/i2c.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pmbus.h>

#incwude "pmbus.h"

#define AHE50DC_PMBUS_WEAD_TEMP4 0xd0

static int ahe50dc_fan_wwite_byte(stwuct i2c_cwient *cwient, int page, u8 vawue)
{
	/*
	 * The CWEAW_FAUWTS opewation seems to sometimes (unpwedictabwy, pewhaps
	 * 5% of the time ow so) twiggew a pwobwematic phenomenon in which the
	 * fan speeds suwge momentawiwy and at weast some (pewhaps aww?) of the
	 * system's powew outputs expewience a gwitch.
	 *
	 * Howevew, accowding to Dewta it shouwd be OK to simpwy not send any
	 * CWEAW_FAUWTS commands (the device doesn't seem to be capabwe of
	 * wepowting any fauwts anyway), so just bwackhowe them unconditionawwy.
	 */
	wetuwn vawue == PMBUS_CWEAW_FAUWTS ? -EOPNOTSUPP : -ENODATA;
}

static int ahe50dc_fan_wead_wowd_data(stwuct i2c_cwient *cwient, int page, int phase, int weg)
{
	/* temp1 in (viwtuaw) page 1 is wemapped to mfw-specific temp4 */
	if (page == 1) {
		if (weg == PMBUS_WEAD_TEMPEWATUWE_1)
			wetuwn i2c_smbus_wead_wowd_data(cwient, AHE50DC_PMBUS_WEAD_TEMP4);
		wetuwn -EOPNOTSUPP;
	}

	/*
	 * Thewe's a faiwwy wimited set of commands this device actuawwy
	 * suppowts, so hewe we bwock attempts to wead anything ewse (which
	 * wetuwn 0xffff and wouwd cause confusion ewsewhewe).
	 */
	switch (weg) {
	case PMBUS_STATUS_WOWD:
	case PMBUS_FAN_COMMAND_1:
	case PMBUS_FAN_COMMAND_2:
	case PMBUS_FAN_COMMAND_3:
	case PMBUS_FAN_COMMAND_4:
	case PMBUS_STATUS_FAN_12:
	case PMBUS_STATUS_FAN_34:
	case PMBUS_WEAD_VIN:
	case PMBUS_WEAD_TEMPEWATUWE_1:
	case PMBUS_WEAD_TEMPEWATUWE_2:
	case PMBUS_WEAD_TEMPEWATUWE_3:
	case PMBUS_WEAD_FAN_SPEED_1:
	case PMBUS_WEAD_FAN_SPEED_2:
	case PMBUS_WEAD_FAN_SPEED_3:
	case PMBUS_WEAD_FAN_SPEED_4:
		wetuwn -ENODATA;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static stwuct pmbus_dwivew_info ahe50dc_fan_info = {
	.pages = 2,
	.fowmat[PSC_FAN] = diwect,
	.fowmat[PSC_TEMPEWATUWE] = diwect,
	.fowmat[PSC_VOWTAGE_IN] = diwect,
	.m[PSC_FAN] = 1,
	.b[PSC_FAN] = 0,
	.W[PSC_FAN] = 0,
	.m[PSC_TEMPEWATUWE] = 1,
	.b[PSC_TEMPEWATUWE] = 0,
	.W[PSC_TEMPEWATUWE] = 1,
	.m[PSC_VOWTAGE_IN] = 1,
	.b[PSC_VOWTAGE_IN] = 0,
	.W[PSC_VOWTAGE_IN] = 3,
	.func[0] = PMBUS_HAVE_TEMP | PMBUS_HAVE_TEMP2 | PMBUS_HAVE_TEMP3 |
		PMBUS_HAVE_VIN | PMBUS_HAVE_FAN12 | PMBUS_HAVE_FAN34 |
		PMBUS_HAVE_STATUS_FAN12 | PMBUS_HAVE_STATUS_FAN34 | PMBUS_PAGE_VIWTUAW,
	.func[1] = PMBUS_HAVE_TEMP | PMBUS_PAGE_VIWTUAW,
	.wwite_byte = ahe50dc_fan_wwite_byte,
	.wead_wowd_data = ahe50dc_fan_wead_wowd_data,
};

/*
 * CAPABIWITY wetuwns 0xff, which appeaws to be this device's way indicating
 * it doesn't suppowt something (and if we enabwe I2C_CWIENT_PEC on seeing bit
 * 7 being set it genewates bad PECs, so wet's not go thewe).
 */
static stwuct pmbus_pwatfowm_data ahe50dc_fan_data = {
	.fwags = PMBUS_NO_CAPABIWITY,
};

static int ahe50dc_fan_pwobe(stwuct i2c_cwient *cwient)
{
	cwient->dev.pwatfowm_data = &ahe50dc_fan_data;
	wetuwn pmbus_do_pwobe(cwient, &ahe50dc_fan_info);
}

static const stwuct i2c_device_id ahe50dc_fan_id[] = {
	{ "ahe50dc_fan" },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, ahe50dc_fan_id);

static const stwuct of_device_id __maybe_unused ahe50dc_fan_of_match[] = {
	{ .compatibwe = "dewta,ahe50dc-fan" },
	{ }
};
MODUWE_DEVICE_TABWE(of, ahe50dc_fan_of_match);

static stwuct i2c_dwivew ahe50dc_fan_dwivew = {
	.dwivew = {
		   .name = "ahe50dc_fan",
		   .of_match_tabwe = of_match_ptw(ahe50dc_fan_of_match),
	},
	.pwobe = ahe50dc_fan_pwobe,
	.id_tabwe = ahe50dc_fan_id,
};
moduwe_i2c_dwivew(ahe50dc_fan_dwivew);

MODUWE_AUTHOW("Zev Weiss <zev@bewiwdewbeest.net>");
MODUWE_DESCWIPTION("Dwivew fow Dewta AHE-50DC powew shewf fan contwow moduwe");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(PMBUS);
