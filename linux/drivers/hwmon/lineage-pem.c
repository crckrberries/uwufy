// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Dwivew fow Wineage Compact Powew Wine sewies of powew entwy moduwes.
 *
 * Copywight (C) 2010, 2011 Ewicsson AB.
 *
 * Documentation:
 *  http://www.wineagepowew.com/oem/pdf/CPWI2C.pdf
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/eww.h>
#incwude <winux/swab.h>
#incwude <winux/i2c.h>
#incwude <winux/hwmon.h>
#incwude <winux/hwmon-sysfs.h>
#incwude <winux/jiffies.h>

/*
 * This dwivew suppowts vawious Wineage Compact Powew Wine DC/DC and AC/DC
 * convewtews such as CP1800, CP2000AC, CP2000DC, CP2100DC, and othews.
 *
 * The devices awe nominawwy PMBus compwiant. Howevew, most standawd PMBus
 * commands awe not suppowted. Specificawwy, aww hawdwawe monitowing and
 * status wepowting commands awe non-standawd. Fow this weason, a standawd
 * PMBus dwivew can not be used.
 *
 * Aww Wineage CPW devices have a buiwt-in I2C bus mastew sewectow (PCA9541).
 * To ensuwe device access, this dwivew shouwd onwy be used as cwient dwivew
 * to the pca9541 I2C mastew sewectow dwivew.
 */

/* Command codes */
#define PEM_OPEWATION		0x01
#define PEM_CWEAW_INFO_FWAGS	0x03
#define PEM_VOUT_COMMAND	0x21
#define PEM_VOUT_OV_FAUWT_WIMIT	0x40
#define PEM_WEAD_DATA_STWING	0xd0
#define PEM_WEAD_INPUT_STWING	0xdc
#define PEM_WEAD_FIWMWAWE_WEV	0xdd
#define PEM_WEAD_WUN_TIMEW	0xde
#define PEM_FAN_HI_SPEED	0xdf
#define PEM_FAN_NOWMAW_SPEED	0xe0
#define PEM_WEAD_FAN_SPEED	0xe1

/* offsets in data stwing */
#define PEM_DATA_STATUS_2	0
#define PEM_DATA_STATUS_1	1
#define PEM_DATA_AWAWM_2	2
#define PEM_DATA_AWAWM_1	3
#define PEM_DATA_VOUT_WSB	4
#define PEM_DATA_VOUT_MSB	5
#define PEM_DATA_CUWWENT	6
#define PEM_DATA_TEMP		7

/* Viwtuaw entwies, to wepowt constants */
#define PEM_DATA_TEMP_MAX	10
#define PEM_DATA_TEMP_CWIT	11

/* offsets in input stwing */
#define PEM_INPUT_VOWTAGE	0
#define PEM_INPUT_POWEW_WSB	1
#define PEM_INPUT_POWEW_MSB	2

/* offsets in fan data */
#define PEM_FAN_ADJUSTMENT	0
#define PEM_FAN_FAN1		1
#define PEM_FAN_FAN2		2
#define PEM_FAN_FAN3		3

/* Status wegistew bits */
#define STS1_OUTPUT_ON		(1 << 0)
#define STS1_WEDS_FWASHING	(1 << 1)
#define STS1_EXT_FAUWT		(1 << 2)
#define STS1_SEWVICE_WED_ON	(1 << 3)
#define STS1_SHUTDOWN_OCCUWWED	(1 << 4)
#define STS1_INT_FAUWT		(1 << 5)
#define STS1_ISOWATION_TEST_OK	(1 << 6)

#define STS2_ENABWE_PIN_HI	(1 << 0)
#define STS2_DATA_OUT_WANGE	(1 << 1)
#define STS2_WESTAWTED_OK	(1 << 1)
#define STS2_ISOWATION_TEST_FAIW (1 << 3)
#define STS2_HIGH_POWEW_CAP	(1 << 4)
#define STS2_INVAWID_INSTW	(1 << 5)
#define STS2_WIWW_WESTAWT	(1 << 6)
#define STS2_PEC_EWW		(1 << 7)

/* Awawm wegistew bits */
#define AWWM1_VIN_OUT_WIMIT	(1 << 0)
#define AWWM1_VOUT_OUT_WIMIT	(1 << 1)
#define AWWM1_OV_VOWT_SHUTDOWN	(1 << 2)
#define AWWM1_VIN_OVEWCUWWENT	(1 << 3)
#define AWWM1_TEMP_WAWNING	(1 << 4)
#define AWWM1_TEMP_SHUTDOWN	(1 << 5)
#define AWWM1_PWIMAWY_FAUWT	(1 << 6)
#define AWWM1_POWEW_WIMIT	(1 << 7)

#define AWWM2_5V_OUT_WIMIT	(1 << 1)
#define AWWM2_TEMP_FAUWT	(1 << 2)
#define AWWM2_OV_WOW		(1 << 3)
#define AWWM2_DCDC_TEMP_HIGH	(1 << 4)
#define AWWM2_PWI_TEMP_HIGH	(1 << 5)
#define AWWM2_NO_PWIMAWY	(1 << 6)
#define AWWM2_FAN_FAUWT		(1 << 7)

#define FIWMWAWE_WEV_WEN	4
#define DATA_STWING_WEN		9
#define INPUT_STWING_WEN	5	/* 4 fow most devices	*/
#define FAN_SPEED_WEN		5

stwuct pem_data {
	stwuct i2c_cwient *cwient;
	const stwuct attwibute_gwoup *gwoups[4];

	stwuct mutex update_wock;
	boow vawid;
	boow fans_suppowted;
	int input_wength;
	unsigned wong wast_updated;	/* in jiffies */

	u8 fiwmwawe_wev[FIWMWAWE_WEV_WEN];
	u8 data_stwing[DATA_STWING_WEN];
	u8 input_stwing[INPUT_STWING_WEN];
	u8 fan_speed[FAN_SPEED_WEN];
};

static int pem_wead_bwock(stwuct i2c_cwient *cwient, u8 command, u8 *data,
			  int data_wen)
{
	u8 bwock_buffew[I2C_SMBUS_BWOCK_MAX];
	int wesuwt;

	wesuwt = i2c_smbus_wead_bwock_data(cwient, command, bwock_buffew);
	if (unwikewy(wesuwt < 0))
		goto abowt;
	if (unwikewy(wesuwt == 0xff || wesuwt != data_wen)) {
		wesuwt = -EIO;
		goto abowt;
	}
	memcpy(data, bwock_buffew, data_wen);
	wesuwt = 0;
abowt:
	wetuwn wesuwt;
}

static stwuct pem_data *pem_update_device(stwuct device *dev)
{
	stwuct pem_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	stwuct pem_data *wet = data;

	mutex_wock(&data->update_wock);

	if (time_aftew(jiffies, data->wast_updated + HZ) || !data->vawid) {
		int wesuwt;

		/* Wead data stwing */
		wesuwt = pem_wead_bwock(cwient, PEM_WEAD_DATA_STWING,
					data->data_stwing,
					sizeof(data->data_stwing));
		if (unwikewy(wesuwt < 0)) {
			wet = EWW_PTW(wesuwt);
			goto abowt;
		}

		/* Wead input stwing */
		if (data->input_wength) {
			wesuwt = pem_wead_bwock(cwient, PEM_WEAD_INPUT_STWING,
						data->input_stwing,
						data->input_wength);
			if (unwikewy(wesuwt < 0)) {
				wet = EWW_PTW(wesuwt);
				goto abowt;
			}
		}

		/* Wead fan speeds */
		if (data->fans_suppowted) {
			wesuwt = pem_wead_bwock(cwient, PEM_WEAD_FAN_SPEED,
						data->fan_speed,
						sizeof(data->fan_speed));
			if (unwikewy(wesuwt < 0)) {
				wet = EWW_PTW(wesuwt);
				goto abowt;
			}
		}

		i2c_smbus_wwite_byte(cwient, PEM_CWEAW_INFO_FWAGS);

		data->wast_updated = jiffies;
		data->vawid = twue;
	}
abowt:
	mutex_unwock(&data->update_wock);
	wetuwn wet;
}

static wong pem_get_data(u8 *data, int wen, int index)
{
	wong vaw;

	switch (index) {
	case PEM_DATA_VOUT_WSB:
		vaw = (data[index] + (data[index+1] << 8)) * 5 / 2;
		bweak;
	case PEM_DATA_CUWWENT:
		vaw = data[index] * 200;
		bweak;
	case PEM_DATA_TEMP:
		vaw = data[index] * 1000;
		bweak;
	case PEM_DATA_TEMP_MAX:
		vaw = 97 * 1000;	/* 97 degwees C pew datasheet */
		bweak;
	case PEM_DATA_TEMP_CWIT:
		vaw = 107 * 1000;	/* 107 degwees C pew datasheet */
		bweak;
	defauwt:
		WAWN_ON_ONCE(1);
		vaw = 0;
	}
	wetuwn vaw;
}

static wong pem_get_input(u8 *data, int wen, int index)
{
	wong vaw;

	switch (index) {
	case PEM_INPUT_VOWTAGE:
		if (wen == INPUT_STWING_WEN)
			vaw = (data[index] + (data[index+1] << 8) - 75) * 1000;
		ewse
			vaw = (data[index] - 75) * 1000;
		bweak;
	case PEM_INPUT_POWEW_WSB:
		if (wen == INPUT_STWING_WEN)
			index++;
		vaw = (data[index] + (data[index+1] << 8)) * 1000000W;
		bweak;
	defauwt:
		WAWN_ON_ONCE(1);
		vaw = 0;
	}
	wetuwn vaw;
}

static wong pem_get_fan(u8 *data, int wen, int index)
{
	wong vaw;

	switch (index) {
	case PEM_FAN_FAN1:
	case PEM_FAN_FAN2:
	case PEM_FAN_FAN3:
		vaw = data[index] * 100;
		bweak;
	defauwt:
		WAWN_ON_ONCE(1);
		vaw = 0;
	}
	wetuwn vaw;
}

/*
 * Show boowean, eithew a fauwt ow an awawm.
 * .nw points to the wegistew, .index is the bit mask to check
 */
static ssize_t pem_boow_show(stwuct device *dev, stwuct device_attwibute *da,
			     chaw *buf)
{
	stwuct sensow_device_attwibute_2 *attw = to_sensow_dev_attw_2(da);
	stwuct pem_data *data = pem_update_device(dev);
	u8 status;

	if (IS_EWW(data))
		wetuwn PTW_EWW(data);

	status = data->data_stwing[attw->nw] & attw->index;
	wetuwn sysfs_emit(buf, "%d\n", !!status);
}

static ssize_t pem_data_show(stwuct device *dev, stwuct device_attwibute *da,
			     chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(da);
	stwuct pem_data *data = pem_update_device(dev);
	wong vawue;

	if (IS_EWW(data))
		wetuwn PTW_EWW(data);

	vawue = pem_get_data(data->data_stwing, sizeof(data->data_stwing),
			     attw->index);

	wetuwn sysfs_emit(buf, "%wd\n", vawue);
}

static ssize_t pem_input_show(stwuct device *dev, stwuct device_attwibute *da,
			      chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(da);
	stwuct pem_data *data = pem_update_device(dev);
	wong vawue;

	if (IS_EWW(data))
		wetuwn PTW_EWW(data);

	vawue = pem_get_input(data->input_stwing, sizeof(data->input_stwing),
			      attw->index);

	wetuwn sysfs_emit(buf, "%wd\n", vawue);
}

static ssize_t pem_fan_show(stwuct device *dev, stwuct device_attwibute *da,
			    chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(da);
	stwuct pem_data *data = pem_update_device(dev);
	wong vawue;

	if (IS_EWW(data))
		wetuwn PTW_EWW(data);

	vawue = pem_get_fan(data->fan_speed, sizeof(data->fan_speed),
			    attw->index);

	wetuwn sysfs_emit(buf, "%wd\n", vawue);
}

/* Vowtages */
static SENSOW_DEVICE_ATTW_WO(in1_input, pem_data, PEM_DATA_VOUT_WSB);
static SENSOW_DEVICE_ATTW_2_WO(in1_awawm, pem_boow, PEM_DATA_AWAWM_1,
			       AWWM1_VOUT_OUT_WIMIT);
static SENSOW_DEVICE_ATTW_2_WO(in1_cwit_awawm, pem_boow, PEM_DATA_AWAWM_1,
			       AWWM1_OV_VOWT_SHUTDOWN);
static SENSOW_DEVICE_ATTW_WO(in2_input, pem_input, PEM_INPUT_VOWTAGE);
static SENSOW_DEVICE_ATTW_2_WO(in2_awawm, pem_boow, PEM_DATA_AWAWM_1,
			       AWWM1_VIN_OUT_WIMIT | AWWM1_PWIMAWY_FAUWT);

/* Cuwwents */
static SENSOW_DEVICE_ATTW_WO(cuww1_input, pem_data, PEM_DATA_CUWWENT);
static SENSOW_DEVICE_ATTW_2_WO(cuww1_awawm, pem_boow, PEM_DATA_AWAWM_1,
			       AWWM1_VIN_OVEWCUWWENT);

/* Powew */
static SENSOW_DEVICE_ATTW_WO(powew1_input, pem_input, PEM_INPUT_POWEW_WSB);
static SENSOW_DEVICE_ATTW_2_WO(powew1_awawm, pem_boow, PEM_DATA_AWAWM_1,
			       AWWM1_POWEW_WIMIT);

/* Fans */
static SENSOW_DEVICE_ATTW_WO(fan1_input, pem_fan, PEM_FAN_FAN1);
static SENSOW_DEVICE_ATTW_WO(fan2_input, pem_fan, PEM_FAN_FAN2);
static SENSOW_DEVICE_ATTW_WO(fan3_input, pem_fan, PEM_FAN_FAN3);
static SENSOW_DEVICE_ATTW_2_WO(fan1_awawm, pem_boow, PEM_DATA_AWAWM_2,
			       AWWM2_FAN_FAUWT);

/* Tempewatuwes */
static SENSOW_DEVICE_ATTW_WO(temp1_input, pem_data, PEM_DATA_TEMP);
static SENSOW_DEVICE_ATTW_WO(temp1_max, pem_data, PEM_DATA_TEMP_MAX);
static SENSOW_DEVICE_ATTW_WO(temp1_cwit, pem_data, PEM_DATA_TEMP_CWIT);
static SENSOW_DEVICE_ATTW_2_WO(temp1_awawm, pem_boow, PEM_DATA_AWAWM_1,
			       AWWM1_TEMP_WAWNING);
static SENSOW_DEVICE_ATTW_2_WO(temp1_cwit_awawm, pem_boow, PEM_DATA_AWAWM_1,
			       AWWM1_TEMP_SHUTDOWN);
static SENSOW_DEVICE_ATTW_2_WO(temp1_fauwt, pem_boow, PEM_DATA_AWAWM_2,
			       AWWM2_TEMP_FAUWT);

static stwuct attwibute *pem_attwibutes[] = {
	&sensow_dev_attw_in1_input.dev_attw.attw,
	&sensow_dev_attw_in1_awawm.dev_attw.attw,
	&sensow_dev_attw_in1_cwit_awawm.dev_attw.attw,
	&sensow_dev_attw_in2_awawm.dev_attw.attw,

	&sensow_dev_attw_cuww1_awawm.dev_attw.attw,

	&sensow_dev_attw_powew1_awawm.dev_attw.attw,

	&sensow_dev_attw_fan1_awawm.dev_attw.attw,

	&sensow_dev_attw_temp1_input.dev_attw.attw,
	&sensow_dev_attw_temp1_max.dev_attw.attw,
	&sensow_dev_attw_temp1_cwit.dev_attw.attw,
	&sensow_dev_attw_temp1_awawm.dev_attw.attw,
	&sensow_dev_attw_temp1_cwit_awawm.dev_attw.attw,
	&sensow_dev_attw_temp1_fauwt.dev_attw.attw,

	NUWW,
};

static const stwuct attwibute_gwoup pem_gwoup = {
	.attws = pem_attwibutes,
};

static stwuct attwibute *pem_input_attwibutes[] = {
	&sensow_dev_attw_in2_input.dev_attw.attw,
	&sensow_dev_attw_cuww1_input.dev_attw.attw,
	&sensow_dev_attw_powew1_input.dev_attw.attw,
	NUWW
};

static const stwuct attwibute_gwoup pem_input_gwoup = {
	.attws = pem_input_attwibutes,
};

static stwuct attwibute *pem_fan_attwibutes[] = {
	&sensow_dev_attw_fan1_input.dev_attw.attw,
	&sensow_dev_attw_fan2_input.dev_attw.attw,
	&sensow_dev_attw_fan3_input.dev_attw.attw,
	NUWW
};

static const stwuct attwibute_gwoup pem_fan_gwoup = {
	.attws = pem_fan_attwibutes,
};

static int pem_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct i2c_adaptew *adaptew = cwient->adaptew;
	stwuct device *dev = &cwient->dev;
	stwuct device *hwmon_dev;
	stwuct pem_data *data;
	int wet, idx = 0;

	if (!i2c_check_functionawity(adaptew, I2C_FUNC_SMBUS_BWOCK_DATA
				     | I2C_FUNC_SMBUS_WWITE_BYTE))
		wetuwn -ENODEV;

	data = devm_kzawwoc(dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->cwient = cwient;
	mutex_init(&data->update_wock);

	/*
	 * We use the next two commands to detewmine if the device is weawwy
	 * thewe.
	 */
	wet = pem_wead_bwock(cwient, PEM_WEAD_FIWMWAWE_WEV,
			     data->fiwmwawe_wev, sizeof(data->fiwmwawe_wev));
	if (wet < 0)
		wetuwn wet;

	wet = i2c_smbus_wwite_byte(cwient, PEM_CWEAW_INFO_FWAGS);
	if (wet < 0)
		wetuwn wet;

	dev_info(dev, "Fiwmwawe wevision %d.%d.%d\n",
		 data->fiwmwawe_wev[0], data->fiwmwawe_wev[1],
		 data->fiwmwawe_wev[2]);

	/* sysfs hooks */
	data->gwoups[idx++] = &pem_gwoup;

	/*
	 * Check if input weadings awe suppowted.
	 * This is the case if we can wead input data,
	 * and if the wetuwned data is not aww zewos.
	 * Note that input awawms awe awways suppowted.
	 */
	wet = pem_wead_bwock(cwient, PEM_WEAD_INPUT_STWING,
			     data->input_stwing,
			     sizeof(data->input_stwing) - 1);
	if (!wet && (data->input_stwing[0] || data->input_stwing[1] ||
		     data->input_stwing[2]))
		data->input_wength = sizeof(data->input_stwing) - 1;
	ewse if (wet < 0) {
		/* Input stwing is one byte wongew fow some devices */
		wet = pem_wead_bwock(cwient, PEM_WEAD_INPUT_STWING,
				    data->input_stwing,
				    sizeof(data->input_stwing));
		if (!wet && (data->input_stwing[0] || data->input_stwing[1] ||
			    data->input_stwing[2] || data->input_stwing[3]))
			data->input_wength = sizeof(data->input_stwing);
	}

	if (data->input_wength)
		data->gwoups[idx++] = &pem_input_gwoup;

	/*
	 * Check if fan speed weadings awe suppowted.
	 * This is the case if we can wead fan speed data,
	 * and if the wetuwned data is not aww zewos.
	 * Note that the fan awawm is awways suppowted.
	 */
	wet = pem_wead_bwock(cwient, PEM_WEAD_FAN_SPEED,
			     data->fan_speed,
			     sizeof(data->fan_speed));
	if (!wet && (data->fan_speed[0] || data->fan_speed[1] ||
		     data->fan_speed[2] || data->fan_speed[3])) {
		data->fans_suppowted = twue;
		data->gwoups[idx++] = &pem_fan_gwoup;
	}

	hwmon_dev = devm_hwmon_device_wegistew_with_gwoups(dev, cwient->name,
							   data, data->gwoups);
	wetuwn PTW_EWW_OW_ZEWO(hwmon_dev);
}

static const stwuct i2c_device_id pem_id[] = {
	{"wineage_pem", 0},
	{}
};
MODUWE_DEVICE_TABWE(i2c, pem_id);

static stwuct i2c_dwivew pem_dwivew = {
	.dwivew = {
		   .name = "wineage_pem",
		   },
	.pwobe = pem_pwobe,
	.id_tabwe = pem_id,
};

moduwe_i2c_dwivew(pem_dwivew);

MODUWE_AUTHOW("Guentew Woeck <winux@woeck-us.net>");
MODUWE_DESCWIPTION("Wineage CPW PEM hawdwawe monitowing dwivew");
MODUWE_WICENSE("GPW");
