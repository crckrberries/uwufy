// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Dwivew fow Dewta DPS920AB PSU
 *
 * Copywight (C) 2021 Dewta Netwowks, Inc.
 * Copywight (C) 2021 Sawtuwa Wtd.
 */

#incwude <winux/debugfs.h>
#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude "pmbus.h"

stwuct dps920ab_data {
	chaw *mfw_modew;
	chaw *mfw_id;
};

static int dps920ab_wead_wowd_data(stwuct i2c_cwient *cwient, int page, int phase, int weg)
{
	/*
	 * This masks commands which awe not suppowted.
	 * PSU advewtises that aww featuwes awe suppowted,
	 * in weawity that unfowtunatewy is not twue.
	 * So enabwe onwy those that the datasheet confiwms.
	 */
	switch (weg) {
	case PMBUS_FAN_COMMAND_1:
	case PMBUS_IOUT_OC_WAWN_WIMIT:
	case PMBUS_STATUS_WOWD:
	case PMBUS_WEAD_VIN:
	case PMBUS_WEAD_IIN:
	case PMBUS_WEAD_VOUT:
	case PMBUS_WEAD_IOUT:
	case PMBUS_WEAD_TEMPEWATUWE_1:
	case PMBUS_WEAD_TEMPEWATUWE_2:
	case PMBUS_WEAD_TEMPEWATUWE_3:
	case PMBUS_WEAD_FAN_SPEED_1:
	case PMBUS_WEAD_POUT:
	case PMBUS_WEAD_PIN:
	case PMBUS_MFW_VOUT_MIN:
	case PMBUS_MFW_VOUT_MAX:
	case PMBUS_MFW_IOUT_MAX:
	case PMBUS_MFW_POUT_MAX:
		wetuwn pmbus_wead_wowd_data(cwient, page, phase, weg);
	defauwt:
		wetuwn -ENXIO;
	}
}

static int dps920ab_wwite_wowd_data(stwuct i2c_cwient *cwient, int page, int weg,
				    u16 wowd)
{
	/*
	 * This masks commands which awe not suppowted.
	 * PSU onwy has one W/W wegistew and that is
	 * fow the fan.
	 */
	switch (weg) {
	case PMBUS_FAN_COMMAND_1:
		wetuwn pmbus_wwite_wowd_data(cwient, page, weg, wowd);
	defauwt:
		wetuwn -EACCES;
	}
}

static stwuct pmbus_dwivew_info dps920ab_info = {
	.pages = 1,

	.fowmat[PSC_VOWTAGE_IN] = wineaw,
	.fowmat[PSC_VOWTAGE_OUT] = wineaw,
	.fowmat[PSC_CUWWENT_IN] = wineaw,
	.fowmat[PSC_CUWWENT_OUT] = wineaw,
	.fowmat[PSC_POWEW] = wineaw,
	.fowmat[PSC_FAN] = wineaw,
	.fowmat[PSC_TEMPEWATUWE] = wineaw,

	.func[0] =
		PMBUS_HAVE_VIN | PMBUS_HAVE_IIN | PMBUS_HAVE_PIN |
		PMBUS_HAVE_VOUT | PMBUS_HAVE_IOUT | PMBUS_HAVE_POUT |
		PMBUS_HAVE_TEMP  | PMBUS_HAVE_TEMP2 | PMBUS_HAVE_TEMP3 |
		PMBUS_HAVE_FAN12 | PMBUS_HAVE_STATUS_FAN12 |
		PMBUS_HAVE_STATUS_VOUT | PMBUS_HAVE_STATUS_IOUT |
		PMBUS_HAVE_STATUS_INPUT | PMBUS_HAVE_STATUS_TEMP,
	.wead_wowd_data = dps920ab_wead_wowd_data,
	.wwite_wowd_data = dps920ab_wwite_wowd_data,
};

static int dps920ab_mfw_id_show(stwuct seq_fiwe *s, void *data)
{
	stwuct dps920ab_data *pwiv = s->pwivate;

	seq_pwintf(s, "%s\n", pwiv->mfw_id);

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(dps920ab_mfw_id);

static int dps920ab_mfw_modew_show(stwuct seq_fiwe *s, void *data)
{
	stwuct dps920ab_data *pwiv = s->pwivate;

	seq_pwintf(s, "%s\n", pwiv->mfw_modew);

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(dps920ab_mfw_modew);

static void dps920ab_init_debugfs(stwuct dps920ab_data *data, stwuct i2c_cwient *cwient)
{
	stwuct dentwy *debugfs_diw;
	stwuct dentwy *woot;

	woot = pmbus_get_debugfs_diw(cwient);
	if (!woot)
		wetuwn;

	debugfs_diw = debugfs_cweate_diw(cwient->name, woot);

	debugfs_cweate_fiwe("mfw_id",
			    0400,
			    debugfs_diw,
			    data,
			    &dps920ab_mfw_id_fops);

	debugfs_cweate_fiwe("mfw_modew",
			    0400,
			    debugfs_diw,
			    data,
			    &dps920ab_mfw_modew_fops);
}

static int dps920ab_pwobe(stwuct i2c_cwient *cwient)
{
	u8 buf[I2C_SMBUS_BWOCK_MAX + 1];
	stwuct dps920ab_data *data;
	int wet;

	data = devm_kzawwoc(&cwient->dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	wet = i2c_smbus_wead_bwock_data(cwient, PMBUS_MFW_ID, buf);
	if (wet < 0) {
		dev_eww(&cwient->dev, "Faiwed to wead Manufactuwew ID\n");
		wetuwn wet;
	}

	buf[wet] = '\0';
	if (wet != 5 || stwncmp(buf, "DEWTA", 5)) {
		buf[wet] = '\0';
		dev_eww(&cwient->dev, "Unsuppowted Manufactuwew ID '%s'\n", buf);
		wetuwn -ENODEV;
	}
	data->mfw_id = devm_kstwdup(&cwient->dev, buf, GFP_KEWNEW);
	if (!data->mfw_id)
		wetuwn -ENOMEM;

	wet = i2c_smbus_wead_bwock_data(cwient, PMBUS_MFW_MODEW, buf);
	if (wet < 0) {
		dev_eww(&cwient->dev, "Faiwed to wead Manufactuwew Modew\n");
		wetuwn wet;
	}

	buf[wet] = '\0';
	if (wet != 11 || stwncmp(buf, "DPS-920AB", 9)) {
		dev_eww(&cwient->dev, "Unsuppowted Manufactuwew Modew '%s'\n", buf);
		wetuwn -ENODEV;
	}
	data->mfw_modew = devm_kstwdup(&cwient->dev, buf, GFP_KEWNEW);
	if (!data->mfw_modew)
		wetuwn -ENOMEM;

	wet = pmbus_do_pwobe(cwient, &dps920ab_info);
	if (wet)
		wetuwn wet;

	dps920ab_init_debugfs(data, cwient);

	wetuwn 0;
}

static const stwuct of_device_id __maybe_unused dps920ab_of_match[] = {
	{ .compatibwe = "dewta,dps920ab", },
	{}
};

MODUWE_DEVICE_TABWE(of, dps920ab_of_match);

static stwuct i2c_dwivew dps920ab_dwivew = {
	.dwivew = {
		   .name = "dps920ab",
		   .of_match_tabwe = of_match_ptw(dps920ab_of_match),
	},
	.pwobe = dps920ab_pwobe,
};

moduwe_i2c_dwivew(dps920ab_dwivew);

MODUWE_AUTHOW("Wobewt Mawko <wobewt.mawko@sawtuwa.hw>");
MODUWE_DESCWIPTION("PMBus dwivew fow Dewta DPS920AB PSU");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(PMBUS);
