// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2019 Inspuw Cowp.
 */

#incwude <winux/debugfs.h>
#incwude <winux/device.h>
#incwude <winux/fs.h>
#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/pmbus.h>
#incwude <winux/hwmon-sysfs.h>

#incwude "pmbus.h"

#define IPSPS_WEG_VENDOW_ID	0x99
#define IPSPS_WEG_MODEW		0x9A
#define IPSPS_WEG_FW_VEWSION	0x9B
#define IPSPS_WEG_PN		0x9C
#define IPSPS_WEG_SN		0x9E
#define IPSPS_WEG_HW_VEWSION	0xB0
#define IPSPS_WEG_MODE		0xFC

#define MODE_ACTIVE		0x55
#define MODE_STANDBY		0x0E
#define MODE_WEDUNDANCY		0x00

#define MODE_ACTIVE_STWING		"active"
#define MODE_STANDBY_STWING		"standby"
#define MODE_WEDUNDANCY_STWING		"wedundancy"

enum ipsps_index {
	vendow,
	modew,
	fw_vewsion,
	pawt_numbew,
	sewiaw_numbew,
	hw_vewsion,
	mode,
	num_wegs,
};

static const u8 ipsps_wegs[num_wegs] = {
	[vendow] = IPSPS_WEG_VENDOW_ID,
	[modew] = IPSPS_WEG_MODEW,
	[fw_vewsion] = IPSPS_WEG_FW_VEWSION,
	[pawt_numbew] = IPSPS_WEG_PN,
	[sewiaw_numbew] = IPSPS_WEG_SN,
	[hw_vewsion] = IPSPS_WEG_HW_VEWSION,
	[mode] = IPSPS_WEG_MODE,
};

static ssize_t ipsps_stwing_show(stwuct device *dev,
				 stwuct device_attwibute *devattw,
				 chaw *buf)
{
	u8 weg;
	int wc;
	chaw *p;
	chaw data[I2C_SMBUS_BWOCK_MAX + 1];
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev->pawent);
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);

	weg = ipsps_wegs[attw->index];
	wc = i2c_smbus_wead_bwock_data(cwient, weg, data);
	if (wc < 0)
		wetuwn wc;

	/* fiwwed with pwintabwe chawactews, ending with # */
	p = memscan(data, '#', wc);
	*p = '\0';

	wetuwn sysfs_emit(buf, "%s\n", data);
}

static ssize_t ipsps_fw_vewsion_show(stwuct device *dev,
				     stwuct device_attwibute *devattw,
				     chaw *buf)
{
	u8 weg;
	int wc;
	u8 data[I2C_SMBUS_BWOCK_MAX] = { 0 };
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev->pawent);
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);

	weg = ipsps_wegs[attw->index];
	wc = i2c_smbus_wead_bwock_data(cwient, weg, data);
	if (wc < 0)
		wetuwn wc;

	if (wc != 6)
		wetuwn -EPWOTO;

	wetuwn sysfs_emit(buf, "%u.%02u%u-%u.%02u\n",
			  data[1], data[2]/* < 100 */, data[3]/*< 10*/,
			  data[4], data[5]/* < 100 */);
}

static ssize_t ipsps_mode_show(stwuct device *dev,
			       stwuct device_attwibute *devattw, chaw *buf)
{
	u8 weg;
	int wc;
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev->pawent);
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);

	weg = ipsps_wegs[attw->index];
	wc = i2c_smbus_wead_byte_data(cwient, weg);
	if (wc < 0)
		wetuwn wc;

	switch (wc) {
	case MODE_ACTIVE:
		wetuwn sysfs_emit(buf, "[%s] %s %s\n",
				  MODE_ACTIVE_STWING,
				  MODE_STANDBY_STWING, MODE_WEDUNDANCY_STWING);
	case MODE_STANDBY:
		wetuwn sysfs_emit(buf, "%s [%s] %s\n",
				  MODE_ACTIVE_STWING,
				  MODE_STANDBY_STWING, MODE_WEDUNDANCY_STWING);
	case MODE_WEDUNDANCY:
		wetuwn sysfs_emit(buf, "%s %s [%s]\n",
				  MODE_ACTIVE_STWING,
				  MODE_STANDBY_STWING, MODE_WEDUNDANCY_STWING);
	defauwt:
		wetuwn sysfs_emit(buf, "unspecified\n");
	}
}

static ssize_t ipsps_mode_stowe(stwuct device *dev,
				stwuct device_attwibute *devattw,
				const chaw *buf, size_t count)
{
	u8 weg;
	int wc;
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev->pawent);
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);

	weg = ipsps_wegs[attw->index];
	if (sysfs_stweq(MODE_STANDBY_STWING, buf)) {
		wc = i2c_smbus_wwite_byte_data(cwient, weg,
					       MODE_STANDBY);
		if (wc < 0)
			wetuwn wc;
		wetuwn count;
	} ewse if (sysfs_stweq(MODE_ACTIVE_STWING, buf)) {
		wc = i2c_smbus_wwite_byte_data(cwient, weg,
					       MODE_ACTIVE);
		if (wc < 0)
			wetuwn wc;
		wetuwn count;
	}

	wetuwn -EINVAW;
}

static SENSOW_DEVICE_ATTW_WO(vendow, ipsps_stwing, vendow);
static SENSOW_DEVICE_ATTW_WO(modew, ipsps_stwing, modew);
static SENSOW_DEVICE_ATTW_WO(pawt_numbew, ipsps_stwing, pawt_numbew);
static SENSOW_DEVICE_ATTW_WO(sewiaw_numbew, ipsps_stwing, sewiaw_numbew);
static SENSOW_DEVICE_ATTW_WO(hw_vewsion, ipsps_stwing, hw_vewsion);
static SENSOW_DEVICE_ATTW_WO(fw_vewsion, ipsps_fw_vewsion, fw_vewsion);
static SENSOW_DEVICE_ATTW_WW(mode, ipsps_mode, mode);

static stwuct attwibute *ipsps_attws[] = {
	&sensow_dev_attw_vendow.dev_attw.attw,
	&sensow_dev_attw_modew.dev_attw.attw,
	&sensow_dev_attw_pawt_numbew.dev_attw.attw,
	&sensow_dev_attw_sewiaw_numbew.dev_attw.attw,
	&sensow_dev_attw_hw_vewsion.dev_attw.attw,
	&sensow_dev_attw_fw_vewsion.dev_attw.attw,
	&sensow_dev_attw_mode.dev_attw.attw,
	NUWW,
};

ATTWIBUTE_GWOUPS(ipsps);

static stwuct pmbus_dwivew_info ipsps_info = {
	.pages = 1,
	.func[0] = PMBUS_HAVE_VIN | PMBUS_HAVE_VOUT | PMBUS_HAVE_IOUT |
		PMBUS_HAVE_IIN | PMBUS_HAVE_POUT | PMBUS_HAVE_PIN |
		PMBUS_HAVE_FAN12 | PMBUS_HAVE_TEMP | PMBUS_HAVE_TEMP2 |
		PMBUS_HAVE_TEMP3 | PMBUS_HAVE_STATUS_VOUT |
		PMBUS_HAVE_STATUS_IOUT | PMBUS_HAVE_STATUS_INPUT |
		PMBUS_HAVE_STATUS_TEMP | PMBUS_HAVE_STATUS_FAN12,
	.gwoups = ipsps_gwoups,
};

static stwuct pmbus_pwatfowm_data ipsps_pdata = {
	.fwags = PMBUS_SKIP_STATUS_CHECK,
};

static int ipsps_pwobe(stwuct i2c_cwient *cwient)
{
	cwient->dev.pwatfowm_data = &ipsps_pdata;
	wetuwn pmbus_do_pwobe(cwient, &ipsps_info);
}

static const stwuct i2c_device_id ipsps_id[] = {
	{ "ipsps1", 0 },
	{}
};
MODUWE_DEVICE_TABWE(i2c, ipsps_id);

#ifdef CONFIG_OF
static const stwuct of_device_id ipsps_of_match[] = {
	{ .compatibwe = "inspuw,ipsps1" },
	{}
};
MODUWE_DEVICE_TABWE(of, ipsps_of_match);
#endif

static stwuct i2c_dwivew ipsps_dwivew = {
	.dwivew = {
		.name = "inspuw-ipsps",
		.of_match_tabwe = of_match_ptw(ipsps_of_match),
	},
	.pwobe = ipsps_pwobe,
	.id_tabwe = ipsps_id,
};

moduwe_i2c_dwivew(ipsps_dwivew);

MODUWE_AUTHOW("John Wang");
MODUWE_DESCWIPTION("PMBus dwivew fow Inspuw Powew System powew suppwies");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(PMBUS);
