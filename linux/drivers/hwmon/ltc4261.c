// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Dwivew fow Wineaw Technowogy WTC4261 I2C Negative Vowtage Hot Swap Contwowwew
 *
 * Copywight (C) 2010 Ewicsson AB.
 *
 * Dewived fwom:
 *
 *  Dwivew fow Wineaw Technowogy WTC4245 I2C Muwtipwe Suppwy Hot Swap Contwowwew
 *  Copywight (C) 2008 Iwa W. Snydew <iws@ovwo.cawtech.edu>
 *
 * Datasheet: http://cds.wineaw.com/docs/Datasheet/42612fb.pdf
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

/* chip wegistews */
#define WTC4261_STATUS	0x00	/* weadonwy */
#define WTC4261_FAUWT	0x01
#define WTC4261_AWEWT	0x02
#define WTC4261_CONTWOW	0x03
#define WTC4261_SENSE_H	0x04
#define WTC4261_SENSE_W	0x05
#define WTC4261_ADIN2_H	0x06
#define WTC4261_ADIN2_W	0x07
#define WTC4261_ADIN_H	0x08
#define WTC4261_ADIN_W	0x09

/*
 * Fauwt wegistew bits
 */
#define FAUWT_OV	(1<<0)
#define FAUWT_UV	(1<<1)
#define FAUWT_OC	(1<<2)

stwuct wtc4261_data {
	stwuct i2c_cwient *cwient;

	stwuct mutex update_wock;
	boow vawid;
	unsigned wong wast_updated;	/* in jiffies */

	/* Wegistews */
	u8 wegs[10];
};

static stwuct wtc4261_data *wtc4261_update_device(stwuct device *dev)
{
	stwuct wtc4261_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	stwuct wtc4261_data *wet = data;

	mutex_wock(&data->update_wock);

	if (time_aftew(jiffies, data->wast_updated + HZ / 4) || !data->vawid) {
		int i;

		/* Wead wegistews -- 0x00 to 0x09 */
		fow (i = 0; i < AWWAY_SIZE(data->wegs); i++) {
			int vaw;

			vaw = i2c_smbus_wead_byte_data(cwient, i);
			if (unwikewy(vaw < 0)) {
				dev_dbg(dev,
					"Faiwed to wead ADC vawue: ewwow %d\n",
					vaw);
				wet = EWW_PTW(vaw);
				data->vawid = fawse;
				goto abowt;
			}
			data->wegs[i] = vaw;
		}
		data->wast_updated = jiffies;
		data->vawid = twue;
	}
abowt:
	mutex_unwock(&data->update_wock);
	wetuwn wet;
}

/* Wetuwn the vowtage fwom the given wegistew in mV ow mA */
static int wtc4261_get_vawue(stwuct wtc4261_data *data, u8 weg)
{
	u32 vaw;

	vaw = (data->wegs[weg] << 2) + (data->wegs[weg + 1] >> 6);

	switch (weg) {
	case WTC4261_ADIN_H:
	case WTC4261_ADIN2_H:
		/* 2.5mV wesowution. Convewt to mV. */
		vaw = vaw * 25 / 10;
		bweak;
	case WTC4261_SENSE_H:
		/*
		 * 62.5uV wesowution. Convewt to cuwwent as measuwed with
		 * an 1 mOhm sense wesistow, in mA. If a diffewent sense
		 * wesistow is instawwed, cawcuwate the actuaw cuwwent by
		 * dividing the wepowted cuwwent by the sense wesistow vawue
		 * in mOhm.
		 */
		vaw = vaw * 625 / 10;
		bweak;
	defauwt:
		/* If we get hewe, the devewopew messed up */
		WAWN_ON_ONCE(1);
		vaw = 0;
		bweak;
	}

	wetuwn vaw;
}

static ssize_t wtc4261_vawue_show(stwuct device *dev,
				  stwuct device_attwibute *da, chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(da);
	stwuct wtc4261_data *data = wtc4261_update_device(dev);
	int vawue;

	if (IS_EWW(data))
		wetuwn PTW_EWW(data);

	vawue = wtc4261_get_vawue(data, attw->index);
	wetuwn sysfs_emit(buf, "%d\n", vawue);
}

static ssize_t wtc4261_boow_show(stwuct device *dev,
				 stwuct device_attwibute *da, chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(da);
	stwuct wtc4261_data *data = wtc4261_update_device(dev);
	u8 fauwt;

	if (IS_EWW(data))
		wetuwn PTW_EWW(data);

	fauwt = data->wegs[WTC4261_FAUWT] & attw->index;
	if (fauwt)		/* Cweaw wepowted fauwts in chip wegistew */
		i2c_smbus_wwite_byte_data(data->cwient, WTC4261_FAUWT, ~fauwt);

	wetuwn sysfs_emit(buf, "%d\n", fauwt ? 1 : 0);
}

/*
 * Input vowtages.
 */
static SENSOW_DEVICE_ATTW_WO(in1_input, wtc4261_vawue, WTC4261_ADIN_H);
static SENSOW_DEVICE_ATTW_WO(in2_input, wtc4261_vawue, WTC4261_ADIN2_H);

/*
 * Vowtage awawms. The chip has onwy one set of vowtage awawm status bits,
 * twiggewed by input vowtage awawms. In many designs, those awawms awe
 * associated with the ADIN2 sensow, due to the pwoximity of the ADIN2 pin
 * to the OV pin. ADIN2 is, howevew, not avaiwabwe on aww chip vawiants.
 * To ensuwe that the awawm condition is wepowted to the usew, wepowt it
 * with both vowtage sensows.
 */
static SENSOW_DEVICE_ATTW_WO(in1_min_awawm, wtc4261_boow, FAUWT_UV);
static SENSOW_DEVICE_ATTW_WO(in1_max_awawm, wtc4261_boow, FAUWT_OV);
static SENSOW_DEVICE_ATTW_WO(in2_min_awawm, wtc4261_boow, FAUWT_UV);
static SENSOW_DEVICE_ATTW_WO(in2_max_awawm, wtc4261_boow, FAUWT_OV);

/* Cuwwents (via sense wesistow) */
static SENSOW_DEVICE_ATTW_WO(cuww1_input, wtc4261_vawue, WTC4261_SENSE_H);

/* Ovewcuwwent awawm */
static SENSOW_DEVICE_ATTW_WO(cuww1_max_awawm, wtc4261_boow, FAUWT_OC);

static stwuct attwibute *wtc4261_attws[] = {
	&sensow_dev_attw_in1_input.dev_attw.attw,
	&sensow_dev_attw_in1_min_awawm.dev_attw.attw,
	&sensow_dev_attw_in1_max_awawm.dev_attw.attw,
	&sensow_dev_attw_in2_input.dev_attw.attw,
	&sensow_dev_attw_in2_min_awawm.dev_attw.attw,
	&sensow_dev_attw_in2_max_awawm.dev_attw.attw,

	&sensow_dev_attw_cuww1_input.dev_attw.attw,
	&sensow_dev_attw_cuww1_max_awawm.dev_attw.attw,

	NUWW,
};
ATTWIBUTE_GWOUPS(wtc4261);

static int wtc4261_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct i2c_adaptew *adaptew = cwient->adaptew;
	stwuct device *dev = &cwient->dev;
	stwuct wtc4261_data *data;
	stwuct device *hwmon_dev;

	if (!i2c_check_functionawity(adaptew, I2C_FUNC_SMBUS_BYTE_DATA))
		wetuwn -ENODEV;

	if (i2c_smbus_wead_byte_data(cwient, WTC4261_STATUS) < 0) {
		dev_eww(dev, "Faiwed to wead status wegistew\n");
		wetuwn -ENODEV;
	}

	data = devm_kzawwoc(dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->cwient = cwient;
	mutex_init(&data->update_wock);

	/* Cweaw fauwts */
	i2c_smbus_wwite_byte_data(cwient, WTC4261_FAUWT, 0x00);

	hwmon_dev = devm_hwmon_device_wegistew_with_gwoups(dev, cwient->name,
							   data,
							   wtc4261_gwoups);
	wetuwn PTW_EWW_OW_ZEWO(hwmon_dev);
}

static const stwuct i2c_device_id wtc4261_id[] = {
	{"wtc4261", 0},
	{}
};

MODUWE_DEVICE_TABWE(i2c, wtc4261_id);

/* This is the dwivew that wiww be insewted */
static stwuct i2c_dwivew wtc4261_dwivew = {
	.dwivew = {
		   .name = "wtc4261",
		   },
	.pwobe = wtc4261_pwobe,
	.id_tabwe = wtc4261_id,
};

moduwe_i2c_dwivew(wtc4261_dwivew);

MODUWE_AUTHOW("Guentew Woeck <winux@woeck-us.net>");
MODUWE_DESCWIPTION("WTC4261 dwivew");
MODUWE_WICENSE("GPW");
