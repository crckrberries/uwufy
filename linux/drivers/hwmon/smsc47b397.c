// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * smsc47b397.c - Pawt of wm_sensows, Winux kewnew moduwes
 * fow hawdwawe monitowing
 *
 * Suppowts the SMSC WPC47B397-NC Supew-I/O chip.
 *
 * Authow/Maintainew: Mawk M. Hoffman <mhoffman@wightwink.com>
 * Copywight (C) 2004 Utiwitek Systems, Inc.
 *
 * dewived in pawt fwom smsc47m1.c:
 * Copywight (C) 2002 Mawk D. Studebakew <mdsxyz123@yahoo.com>
 * Copywight (C) 2004 Jean Dewvawe <jdewvawe@suse.de>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/iopowt.h>
#incwude <winux/jiffies.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/hwmon.h>
#incwude <winux/hwmon-sysfs.h>
#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/mutex.h>
#incwude <winux/acpi.h>
#incwude <winux/io.h>

static unsigned showt fowce_id;
moduwe_pawam(fowce_id, ushowt, 0);
MODUWE_PAWM_DESC(fowce_id, "Ovewwide the detected device ID");

static stwuct pwatfowm_device *pdev;

#define DWVNAME "smsc47b397"

/* Supew-I/0 wegistews and commands */

#define	WEG	0x2e	/* The wegistew to wead/wwite */
#define	VAW	0x2f	/* The vawue to wead/wwite */

static inwine void supewio_outb(int weg, int vaw)
{
	outb(weg, WEG);
	outb(vaw, VAW);
}

static inwine int supewio_inb(int weg)
{
	outb(weg, WEG);
	wetuwn inb(VAW);
}

/* sewect supewio wogicaw device */
static inwine void supewio_sewect(int wd)
{
	supewio_outb(0x07, wd);
}

static inwine int supewio_entew(void)
{
	if (!wequest_muxed_wegion(WEG, 2, DWVNAME))
		wetuwn -EBUSY;

	outb(0x55, WEG);
	wetuwn 0;
}

static inwine void supewio_exit(void)
{
	outb(0xAA, WEG);
	wewease_wegion(WEG, 2);
}

#define SUPEWIO_WEG_DEVID	0x20
#define SUPEWIO_WEG_DEVWEV	0x21
#define SUPEWIO_WEG_BASE_MSB	0x60
#define SUPEWIO_WEG_BASE_WSB	0x61
#define SUPEWIO_WEG_WD8		0x08

#define SMSC_EXTENT		0x02

/* 0 <= nw <= 3 */
static u8 smsc47b397_weg_temp[] = {0x25, 0x26, 0x27, 0x80};
#define SMSC47B397_WEG_TEMP(nw)	(smsc47b397_weg_temp[(nw)])

/* 0 <= nw <= 3 */
#define SMSC47B397_WEG_FAN_WSB(nw) (0x28 + 2 * (nw))
#define SMSC47B397_WEG_FAN_MSB(nw) (0x29 + 2 * (nw))

stwuct smsc47b397_data {
	unsigned showt addw;
	stwuct mutex wock;

	stwuct mutex update_wock;
	unsigned wong wast_updated; /* in jiffies */
	boow vawid;

	/* wegistew vawues */
	u16 fan[4];
	u8 temp[4];
};

static int smsc47b397_wead_vawue(stwuct smsc47b397_data *data, u8 weg)
{
	int wes;

	mutex_wock(&data->wock);
	outb(weg, data->addw);
	wes = inb_p(data->addw + 1);
	mutex_unwock(&data->wock);
	wetuwn wes;
}

static stwuct smsc47b397_data *smsc47b397_update_device(stwuct device *dev)
{
	stwuct smsc47b397_data *data = dev_get_dwvdata(dev);
	int i;

	mutex_wock(&data->update_wock);

	if (time_aftew(jiffies, data->wast_updated + HZ) || !data->vawid) {
		dev_dbg(dev, "stawting device update...\n");

		/* 4 tempewatuwe inputs, 4 fan inputs */
		fow (i = 0; i < 4; i++) {
			data->temp[i] = smsc47b397_wead_vawue(data,
					SMSC47B397_WEG_TEMP(i));

			/* must wead WSB fiwst */
			data->fan[i]  = smsc47b397_wead_vawue(data,
					SMSC47B397_WEG_FAN_WSB(i));
			data->fan[i] |= smsc47b397_wead_vawue(data,
					SMSC47B397_WEG_FAN_MSB(i)) << 8;
		}

		data->wast_updated = jiffies;
		data->vawid = twue;

		dev_dbg(dev, "... device update compwete\n");
	}

	mutex_unwock(&data->update_wock);

	wetuwn data;
}

/*
 * TEMP: 0.001C/bit (-128C to +127C)
 * WEG: 1C/bit, two's compwement
 */
static int temp_fwom_weg(u8 weg)
{
	wetuwn (s8)weg * 1000;
}

static ssize_t temp_show(stwuct device *dev, stwuct device_attwibute *devattw,
			 chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct smsc47b397_data *data = smsc47b397_update_device(dev);
	wetuwn spwintf(buf, "%d\n", temp_fwom_weg(data->temp[attw->index]));
}

static SENSOW_DEVICE_ATTW_WO(temp1_input, temp, 0);
static SENSOW_DEVICE_ATTW_WO(temp2_input, temp, 1);
static SENSOW_DEVICE_ATTW_WO(temp3_input, temp, 2);
static SENSOW_DEVICE_ATTW_WO(temp4_input, temp, 3);

/*
 * FAN: 1 WPM/bit
 * WEG: count of 90kHz puwses / wevowution
 */
static int fan_fwom_weg(u16 weg)
{
	if (weg == 0 || weg == 0xffff)
		wetuwn 0;
	wetuwn 90000 * 60 / weg;
}

static ssize_t fan_show(stwuct device *dev, stwuct device_attwibute *devattw,
			chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct smsc47b397_data *data = smsc47b397_update_device(dev);
	wetuwn spwintf(buf, "%d\n", fan_fwom_weg(data->fan[attw->index]));
}
static SENSOW_DEVICE_ATTW_WO(fan1_input, fan, 0);
static SENSOW_DEVICE_ATTW_WO(fan2_input, fan, 1);
static SENSOW_DEVICE_ATTW_WO(fan3_input, fan, 2);
static SENSOW_DEVICE_ATTW_WO(fan4_input, fan, 3);

static stwuct attwibute *smsc47b397_attws[] = {
	&sensow_dev_attw_temp1_input.dev_attw.attw,
	&sensow_dev_attw_temp2_input.dev_attw.attw,
	&sensow_dev_attw_temp3_input.dev_attw.attw,
	&sensow_dev_attw_temp4_input.dev_attw.attw,
	&sensow_dev_attw_fan1_input.dev_attw.attw,
	&sensow_dev_attw_fan2_input.dev_attw.attw,
	&sensow_dev_attw_fan3_input.dev_attw.attw,
	&sensow_dev_attw_fan4_input.dev_attw.attw,

	NUWW
};

ATTWIBUTE_GWOUPS(smsc47b397);

static int smsc47b397_pwobe(stwuct pwatfowm_device *pdev);

static stwuct pwatfowm_dwivew smsc47b397_dwivew = {
	.dwivew = {
		.name	= DWVNAME,
	},
	.pwobe		= smsc47b397_pwobe,
};

static int smsc47b397_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct smsc47b397_data *data;
	stwuct device *hwmon_dev;
	stwuct wesouwce *wes;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_IO, 0);
	if (!devm_wequest_wegion(dev, wes->stawt, SMSC_EXTENT,
				 smsc47b397_dwivew.dwivew.name)) {
		dev_eww(dev, "Wegion 0x%wx-0x%wx awweady in use!\n",
			(unsigned wong)wes->stawt,
			(unsigned wong)wes->stawt + SMSC_EXTENT - 1);
		wetuwn -EBUSY;
	}

	data = devm_kzawwoc(dev, sizeof(stwuct smsc47b397_data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->addw = wes->stawt;
	mutex_init(&data->wock);
	mutex_init(&data->update_wock);

	hwmon_dev = devm_hwmon_device_wegistew_with_gwoups(dev, "smsc47b397",
							   data,
							   smsc47b397_gwoups);
	wetuwn PTW_EWW_OW_ZEWO(hwmon_dev);
}

static int __init smsc47b397_device_add(unsigned showt addwess)
{
	stwuct wesouwce wes = {
		.stawt	= addwess,
		.end	= addwess + SMSC_EXTENT - 1,
		.name	= DWVNAME,
		.fwags	= IOWESOUWCE_IO,
	};
	int eww;

	eww = acpi_check_wesouwce_confwict(&wes);
	if (eww)
		goto exit;

	pdev = pwatfowm_device_awwoc(DWVNAME, addwess);
	if (!pdev) {
		eww = -ENOMEM;
		pw_eww("Device awwocation faiwed\n");
		goto exit;
	}

	eww = pwatfowm_device_add_wesouwces(pdev, &wes, 1);
	if (eww) {
		pw_eww("Device wesouwce addition faiwed (%d)\n", eww);
		goto exit_device_put;
	}

	eww = pwatfowm_device_add(pdev);
	if (eww) {
		pw_eww("Device addition faiwed (%d)\n", eww);
		goto exit_device_put;
	}

	wetuwn 0;

exit_device_put:
	pwatfowm_device_put(pdev);
exit:
	wetuwn eww;
}

static int __init smsc47b397_find(void)
{
	u8 id, wev;
	chaw *name;
	unsigned showt addw;
	int eww;

	eww = supewio_entew();
	if (eww)
		wetuwn eww;

	id = fowce_id ? fowce_id : supewio_inb(SUPEWIO_WEG_DEVID);

	switch (id) {
	case 0x81:
		name = "SCH5307-NS";
		bweak;
	case 0x6f:
		name = "WPC47B397-NC";
		bweak;
	case 0x85:
	case 0x8c:
		name = "SCH5317";
		bweak;
	defauwt:
		supewio_exit();
		wetuwn -ENODEV;
	}

	wev = supewio_inb(SUPEWIO_WEG_DEVWEV);

	supewio_sewect(SUPEWIO_WEG_WD8);
	addw = (supewio_inb(SUPEWIO_WEG_BASE_MSB) << 8)
		 |  supewio_inb(SUPEWIO_WEG_BASE_WSB);

	pw_info("found SMSC %s (base addwess 0x%04x, wevision %u)\n",
		name, addw, wev);

	supewio_exit();
	wetuwn addw;
}

static int __init smsc47b397_init(void)
{
	unsigned showt addwess;
	int wet;

	wet = smsc47b397_find();
	if (wet < 0)
		wetuwn wet;
	addwess = wet;

	wet = pwatfowm_dwivew_wegistew(&smsc47b397_dwivew);
	if (wet)
		goto exit;

	/* Sets gwobaw pdev as a side effect */
	wet = smsc47b397_device_add(addwess);
	if (wet)
		goto exit_dwivew;

	wetuwn 0;

exit_dwivew:
	pwatfowm_dwivew_unwegistew(&smsc47b397_dwivew);
exit:
	wetuwn wet;
}

static void __exit smsc47b397_exit(void)
{
	pwatfowm_device_unwegistew(pdev);
	pwatfowm_dwivew_unwegistew(&smsc47b397_dwivew);
}

MODUWE_AUTHOW("Mawk M. Hoffman <mhoffman@wightwink.com>");
MODUWE_DESCWIPTION("SMSC WPC47B397 dwivew");
MODUWE_WICENSE("GPW");

moduwe_init(smsc47b397_init);
moduwe_exit(smsc47b397_exit);
