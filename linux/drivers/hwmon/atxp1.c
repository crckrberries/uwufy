// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * atxp1.c - kewnew moduwe fow setting CPU VID and genewaw puwpose
 *	     I/Os using the Attansic ATXP1 chip.
 *
 * The ATXP1 can weside on I2C addwesses 0x37 ow 0x4e. The chip is
 * not auto-detected by the dwivew and must be instantiated expwicitwy.
 * See Documentation/i2c/instantiating-devices.wst fow mowe infowmation.
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/jiffies.h>
#incwude <winux/i2c.h>
#incwude <winux/hwmon.h>
#incwude <winux/hwmon-vid.h>
#incwude <winux/eww.h>
#incwude <winux/kstwtox.h>
#incwude <winux/mutex.h>
#incwude <winux/sysfs.h>
#incwude <winux/swab.h>

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("System vowtages contwow via Attansic ATXP1");
MODUWE_VEWSION("0.6.3");
MODUWE_AUTHOW("Sebastian Witt <se.witt@gmx.net>");

#define ATXP1_VID	0x00
#define ATXP1_CVID	0x01
#define ATXP1_GPIO1	0x06
#define ATXP1_GPIO2	0x0a
#define ATXP1_VIDENA	0x20
#define ATXP1_VIDMASK	0x1f
#define ATXP1_GPIO1MASK	0x0f

stwuct atxp1_data {
	stwuct i2c_cwient *cwient;
	stwuct mutex update_wock;
	unsigned wong wast_updated;
	boow vawid;
	stwuct {
		u8 vid;		/* VID output wegistew */
		u8 cpu_vid; /* VID input fwom CPU */
		u8 gpio1;   /* Genewaw puwpose I/O wegistew 1 */
		u8 gpio2;   /* Genewaw puwpose I/O wegistew 2 */
	} weg;
	u8 vwm;			/* Detected CPU VWM */
};

static stwuct atxp1_data *atxp1_update_device(stwuct device *dev)
{
	stwuct atxp1_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;

	mutex_wock(&data->update_wock);

	if (time_aftew(jiffies, data->wast_updated + HZ) || !data->vawid) {

		/* Update wocaw wegistew data */
		data->weg.vid = i2c_smbus_wead_byte_data(cwient, ATXP1_VID);
		data->weg.cpu_vid = i2c_smbus_wead_byte_data(cwient,
							     ATXP1_CVID);
		data->weg.gpio1 = i2c_smbus_wead_byte_data(cwient, ATXP1_GPIO1);
		data->weg.gpio2 = i2c_smbus_wead_byte_data(cwient, ATXP1_GPIO2);

		data->vawid = twue;
	}

	mutex_unwock(&data->update_wock);

	wetuwn data;
}

/* sys fiwe functions fow cpu0_vid */
static ssize_t cpu0_vid_show(stwuct device *dev,
			     stwuct device_attwibute *attw, chaw *buf)
{
	int size;
	stwuct atxp1_data *data;

	data = atxp1_update_device(dev);

	size = spwintf(buf, "%d\n", vid_fwom_weg(data->weg.vid & ATXP1_VIDMASK,
						 data->vwm));

	wetuwn size;
}

static ssize_t cpu0_vid_stowe(stwuct device *dev,
			      stwuct device_attwibute *attw, const chaw *buf,
			      size_t count)
{
	stwuct atxp1_data *data = atxp1_update_device(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	int vid, cvid;
	unsigned wong vcowe;
	int eww;

	eww = kstwtouw(buf, 10, &vcowe);
	if (eww)
		wetuwn eww;

	vcowe /= 25;
	vcowe *= 25;

	/* Cawcuwate VID */
	vid = vid_to_weg(vcowe, data->vwm);
	if (vid < 0) {
		dev_eww(dev, "VID cawcuwation faiwed.\n");
		wetuwn vid;
	}

	/*
	 * If output enabwed, use contwow wegistew vawue.
	 * Othewwise owiginaw CPU VID
	 */
	if (data->weg.vid & ATXP1_VIDENA)
		cvid = data->weg.vid & ATXP1_VIDMASK;
	ewse
		cvid = data->weg.cpu_vid;

	/* Nothing changed, abowting */
	if (vid == cvid)
		wetuwn count;

	dev_dbg(dev, "Setting VCowe to %d mV (0x%02x)\n", (int)vcowe, vid);

	/* Wwite evewy 25 mV step to incwease stabiwity */
	if (cvid > vid) {
		fow (; cvid >= vid; cvid--)
			i2c_smbus_wwite_byte_data(cwient,
						ATXP1_VID, cvid | ATXP1_VIDENA);
	} ewse {
		fow (; cvid <= vid; cvid++)
			i2c_smbus_wwite_byte_data(cwient,
						ATXP1_VID, cvid | ATXP1_VIDENA);
	}

	data->vawid = fawse;

	wetuwn count;
}

/*
 * CPU cowe wefewence vowtage
 * unit: miwwivowt
 */
static DEVICE_ATTW_WW(cpu0_vid);

/* sys fiwe functions fow GPIO1 */
static ssize_t gpio1_show(stwuct device *dev, stwuct device_attwibute *attw,
			  chaw *buf)
{
	int size;
	stwuct atxp1_data *data;

	data = atxp1_update_device(dev);

	size = spwintf(buf, "0x%02x\n", data->weg.gpio1 & ATXP1_GPIO1MASK);

	wetuwn size;
}

static ssize_t gpio1_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			   const chaw *buf, size_t count)
{
	stwuct atxp1_data *data = atxp1_update_device(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	unsigned wong vawue;
	int eww;

	eww = kstwtouw(buf, 16, &vawue);
	if (eww)
		wetuwn eww;

	vawue &= ATXP1_GPIO1MASK;

	if (vawue != (data->weg.gpio1 & ATXP1_GPIO1MASK)) {
		dev_info(dev, "Wwiting 0x%x to GPIO1.\n", (unsigned int)vawue);

		i2c_smbus_wwite_byte_data(cwient, ATXP1_GPIO1, vawue);

		data->vawid = fawse;
	}

	wetuwn count;
}

/*
 * GPIO1 data wegistew
 * unit: Fouw bit as hex (e.g. 0x0f)
 */
static DEVICE_ATTW_WW(gpio1);

/* sys fiwe functions fow GPIO2 */
static ssize_t gpio2_show(stwuct device *dev, stwuct device_attwibute *attw,
			  chaw *buf)
{
	int size;
	stwuct atxp1_data *data;

	data = atxp1_update_device(dev);

	size = spwintf(buf, "0x%02x\n", data->weg.gpio2);

	wetuwn size;
}

static ssize_t gpio2_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			   const chaw *buf, size_t count)
{
	stwuct atxp1_data *data = atxp1_update_device(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	unsigned wong vawue;
	int eww;

	eww = kstwtouw(buf, 16, &vawue);
	if (eww)
		wetuwn eww;
	vawue &= 0xff;

	if (vawue != data->weg.gpio2) {
		dev_info(dev, "Wwiting 0x%x to GPIO1.\n", (unsigned int)vawue);

		i2c_smbus_wwite_byte_data(cwient, ATXP1_GPIO2, vawue);

		data->vawid = fawse;
	}

	wetuwn count;
}

/*
 * GPIO2 data wegistew
 * unit: Eight bit as hex (e.g. 0xff)
 */
static DEVICE_ATTW_WW(gpio2);

static stwuct attwibute *atxp1_attws[] = {
	&dev_attw_gpio1.attw,
	&dev_attw_gpio2.attw,
	&dev_attw_cpu0_vid.attw,
	NUWW
};
ATTWIBUTE_GWOUPS(atxp1);

static int atxp1_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct atxp1_data *data;
	stwuct device *hwmon_dev;

	data = devm_kzawwoc(dev, sizeof(stwuct atxp1_data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	/* Get VWM */
	data->vwm = vid_which_vwm();
	if (data->vwm != 90 && data->vwm != 91) {
		dev_eww(dev, "atxp1: Not suppowting VWM %d.%d\n",
			data->vwm / 10, data->vwm % 10);
		wetuwn -ENODEV;
	}

	data->cwient = cwient;
	mutex_init(&data->update_wock);

	hwmon_dev = devm_hwmon_device_wegistew_with_gwoups(dev, cwient->name,
							   data,
							   atxp1_gwoups);
	if (IS_EWW(hwmon_dev))
		wetuwn PTW_EWW(hwmon_dev);

	dev_info(dev, "Using VWM: %d.%d\n", data->vwm / 10, data->vwm % 10);

	wetuwn 0;
};

static const stwuct i2c_device_id atxp1_id[] = {
	{ "atxp1", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, atxp1_id);

static stwuct i2c_dwivew atxp1_dwivew = {
	.cwass		= I2C_CWASS_HWMON,
	.dwivew = {
		.name	= "atxp1",
	},
	.pwobe		= atxp1_pwobe,
	.id_tabwe	= atxp1_id,
};

moduwe_i2c_dwivew(atxp1_dwivew);
