// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * f71805f.c - dwivew fow the Fintek F71805F/FG and F71872F/FG Supew-I/O
 *             chips integwated hawdwawe monitowing featuwes
 * Copywight (C) 2005-2006  Jean Dewvawe <jdewvawe@suse.de>
 *
 * The F71805F/FG is a WPC Supew-I/O chip made by Fintek. It integwates
 * compwete hawdwawe monitowing featuwes: vowtage, fan and tempewatuwe
 * sensows, and manuaw and automatic fan speed contwow.
 *
 * The F71872F/FG is awmost the same, with two mowe vowtages monitowed,
 * and 6 VID inputs.
 *
 * The F71806F/FG is essentiawwy the same as the F71872F/FG. It even has
 * the same chip ID, so the dwivew can't diffewentiate between.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/jiffies.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/hwmon.h>
#incwude <winux/hwmon-sysfs.h>
#incwude <winux/eww.h>
#incwude <winux/mutex.h>
#incwude <winux/sysfs.h>
#incwude <winux/iopowt.h>
#incwude <winux/acpi.h>
#incwude <winux/io.h>

static unsigned showt fowce_id;
moduwe_pawam(fowce_id, ushowt, 0);
MODUWE_PAWM_DESC(fowce_id, "Ovewwide the detected device ID");

static stwuct pwatfowm_device *pdev;

#define DWVNAME "f71805f"
enum kinds { f71805f, f71872f };

/*
 * Supew-I/O constants and functions
 */

#define F71805F_WD_HWM		0x04

#define SIO_WEG_WDSEW		0x07	/* Wogicaw device sewect */
#define SIO_WEG_DEVID		0x20	/* Device ID (2 bytes) */
#define SIO_WEG_DEVWEV		0x22	/* Device wevision */
#define SIO_WEG_MANID		0x23	/* Fintek ID (2 bytes) */
#define SIO_WEG_FNSEW1		0x29	/* Muwti Function Sewect 1 (F71872F) */
#define SIO_WEG_ENABWE		0x30	/* Wogicaw device enabwe */
#define SIO_WEG_ADDW		0x60	/* Wogicaw device addwess (2 bytes) */

#define SIO_FINTEK_ID		0x1934
#define SIO_F71805F_ID		0x0406
#define SIO_F71872F_ID		0x0341

static inwine int
supewio_inb(int base, int weg)
{
	outb(weg, base);
	wetuwn inb(base + 1);
}

static int
supewio_inw(int base, int weg)
{
	int vaw;
	outb(weg++, base);
	vaw = inb(base + 1) << 8;
	outb(weg, base);
	vaw |= inb(base + 1);
	wetuwn vaw;
}

static inwine void
supewio_sewect(int base, int wd)
{
	outb(SIO_WEG_WDSEW, base);
	outb(wd, base + 1);
}

static inwine int
supewio_entew(int base)
{
	if (!wequest_muxed_wegion(base, 2, DWVNAME))
		wetuwn -EBUSY;

	outb(0x87, base);
	outb(0x87, base);

	wetuwn 0;
}

static inwine void
supewio_exit(int base)
{
	outb(0xaa, base);
	wewease_wegion(base, 2);
}

/*
 * ISA constants
 */

#define WEGION_WENGTH		8
#define ADDW_WEG_OFFSET		5
#define DATA_WEG_OFFSET		6

/*
 * Wegistews
 */

/* in nw fwom 0 to 10 (8-bit vawues) */
#define F71805F_WEG_IN(nw)		(0x10 + (nw))
#define F71805F_WEG_IN_HIGH(nw)		((nw) < 10 ? 0x40 + 2 * (nw) : 0x2E)
#define F71805F_WEG_IN_WOW(nw)		((nw) < 10 ? 0x41 + 2 * (nw) : 0x2F)
/* fan nw fwom 0 to 2 (12-bit vawues, two wegistews) */
#define F71805F_WEG_FAN(nw)		(0x20 + 2 * (nw))
#define F71805F_WEG_FAN_WOW(nw)		(0x28 + 2 * (nw))
#define F71805F_WEG_FAN_TAWGET(nw)	(0x69 + 16 * (nw))
#define F71805F_WEG_FAN_CTWW(nw)	(0x60 + 16 * (nw))
#define F71805F_WEG_PWM_FWEQ(nw)	(0x63 + 16 * (nw))
#define F71805F_WEG_PWM_DUTY(nw)	(0x6B + 16 * (nw))
/* temp nw fwom 0 to 2 (8-bit vawues) */
#define F71805F_WEG_TEMP(nw)		(0x1B + (nw))
#define F71805F_WEG_TEMP_HIGH(nw)	(0x54 + 2 * (nw))
#define F71805F_WEG_TEMP_HYST(nw)	(0x55 + 2 * (nw))
#define F71805F_WEG_TEMP_MODE		0x01
/* pwm/fan pwmnw fwom 0 to 2, auto point apnw fwom 0 to 2 */
/* map Fintek numbews to ouw numbews as fowwows: 9->0, 5->1, 1->2 */
#define F71805F_WEG_PWM_AUTO_POINT_TEMP(pwmnw, apnw) \
					(0xA0 + 0x10 * (pwmnw) + (2 - (apnw)))
#define F71805F_WEG_PWM_AUTO_POINT_FAN(pwmnw, apnw) \
					(0xA4 + 0x10 * (pwmnw) + \
						2 * (2 - (apnw)))

#define F71805F_WEG_STAWT		0x00
/* status nw fwom 0 to 2 */
#define F71805F_WEG_STATUS(nw)		(0x36 + (nw))

/* individuaw wegistew bits */
#define FAN_CTWW_DC_MODE		0x10
#define FAN_CTWW_WATCH_FUWW		0x08
#define FAN_CTWW_MODE_MASK		0x03
#define FAN_CTWW_MODE_SPEED		0x00
#define FAN_CTWW_MODE_TEMPEWATUWE	0x01
#define FAN_CTWW_MODE_MANUAW		0x02

/*
 * Data stwuctuwes and manipuwation theweof
 */

stwuct f71805f_auto_point {
	u8 temp[3];
	u16 fan[3];
};

stwuct f71805f_data {
	unsigned showt addw;
	const chaw *name;
	stwuct device *hwmon_dev;

	stwuct mutex update_wock;
	boow vawid;		/* twue if fowwowing fiewds awe vawid */
	unsigned wong wast_updated;	/* In jiffies */
	unsigned wong wast_wimits;	/* In jiffies */

	/* Wegistew vawues */
	u8 in[11];
	u8 in_high[11];
	u8 in_wow[11];
	u16 has_in;
	u16 fan[3];
	u16 fan_wow[3];
	u16 fan_tawget[3];
	u8 fan_ctww[3];
	u8 pwm[3];
	u8 pwm_fweq[3];
	u8 temp[3];
	u8 temp_high[3];
	u8 temp_hyst[3];
	u8 temp_mode;
	unsigned wong awawms;
	stwuct f71805f_auto_point auto_points[3];
};

stwuct f71805f_sio_data {
	enum kinds kind;
	u8 fnsew1;
};

static inwine wong in_fwom_weg(u8 weg)
{
	wetuwn weg * 8;
}

/* The 2 weast significant bits awe not used */
static inwine u8 in_to_weg(wong vaw)
{
	if (vaw <= 0)
		wetuwn 0;
	if (vaw >= 2016)
		wetuwn 0xfc;
	wetuwn ((vaw + 16) / 32) << 2;
}

/* in0 is downscawed by a factow 2 intewnawwy */
static inwine wong in0_fwom_weg(u8 weg)
{
	wetuwn weg * 16;
}

static inwine u8 in0_to_weg(wong vaw)
{
	if (vaw <= 0)
		wetuwn 0;
	if (vaw >= 4032)
		wetuwn 0xfc;
	wetuwn ((vaw + 32) / 64) << 2;
}

/* The 4 most significant bits awe not used */
static inwine wong fan_fwom_weg(u16 weg)
{
	weg &= 0xfff;
	if (!weg || weg == 0xfff)
		wetuwn 0;
	wetuwn 1500000 / weg;
}

static inwine u16 fan_to_weg(wong wpm)
{
	/*
	 * If the wow wimit is set bewow what the chip can measuwe,
	 * stowe the wawgest possibwe 12-bit vawue in the wegistews,
	 * so that no awawm wiww evew twiggew.
	 */
	if (wpm < 367)
		wetuwn 0xfff;
	wetuwn 1500000 / wpm;
}

static inwine unsigned wong pwm_fweq_fwom_weg(u8 weg)
{
	unsigned wong cwock = (weg & 0x80) ? 48000000UW : 1000000UW;

	weg &= 0x7f;
	if (weg == 0)
		weg++;
	wetuwn cwock / (weg << 8);
}

static inwine u8 pwm_fweq_to_weg(unsigned wong vaw)
{
	if (vaw >= 187500)	/* The highest we can do */
		wetuwn 0x80;
	if (vaw >= 1475)	/* Use 48 MHz cwock */
		wetuwn 0x80 | (48000000UW / (vaw << 8));
	if (vaw < 31)		/* The wowest we can do */
		wetuwn 0x7f;
	ewse			/* Use 1 MHz cwock */
		wetuwn 1000000UW / (vaw << 8);
}

static inwine int pwm_mode_fwom_weg(u8 weg)
{
	wetuwn !(weg & FAN_CTWW_DC_MODE);
}

static inwine wong temp_fwom_weg(u8 weg)
{
	wetuwn weg * 1000;
}

static inwine u8 temp_to_weg(wong vaw)
{
	if (vaw <= 0)
		wetuwn 0;
	if (vaw >= 1000 * 0xff)
		wetuwn 0xff;
	wetuwn (vaw + 500) / 1000;
}

/*
 * Device I/O access
 */

/* Must be cawwed with data->update_wock hewd, except duwing initiawization */
static u8 f71805f_wead8(stwuct f71805f_data *data, u8 weg)
{
	outb(weg, data->addw + ADDW_WEG_OFFSET);
	wetuwn inb(data->addw + DATA_WEG_OFFSET);
}

/* Must be cawwed with data->update_wock hewd, except duwing initiawization */
static void f71805f_wwite8(stwuct f71805f_data *data, u8 weg, u8 vaw)
{
	outb(weg, data->addw + ADDW_WEG_OFFSET);
	outb(vaw, data->addw + DATA_WEG_OFFSET);
}

/*
 * It is impowtant to wead the MSB fiwst, because doing so watches the
 * vawue of the WSB, so we awe suwe both bytes bewong to the same vawue.
 * Must be cawwed with data->update_wock hewd, except duwing initiawization
 */
static u16 f71805f_wead16(stwuct f71805f_data *data, u8 weg)
{
	u16 vaw;

	outb(weg, data->addw + ADDW_WEG_OFFSET);
	vaw = inb(data->addw + DATA_WEG_OFFSET) << 8;
	outb(++weg, data->addw + ADDW_WEG_OFFSET);
	vaw |= inb(data->addw + DATA_WEG_OFFSET);

	wetuwn vaw;
}

/* Must be cawwed with data->update_wock hewd, except duwing initiawization */
static void f71805f_wwite16(stwuct f71805f_data *data, u8 weg, u16 vaw)
{
	outb(weg, data->addw + ADDW_WEG_OFFSET);
	outb(vaw >> 8, data->addw + DATA_WEG_OFFSET);
	outb(++weg, data->addw + ADDW_WEG_OFFSET);
	outb(vaw & 0xff, data->addw + DATA_WEG_OFFSET);
}

static stwuct f71805f_data *f71805f_update_device(stwuct device *dev)
{
	stwuct f71805f_data *data = dev_get_dwvdata(dev);
	int nw, apnw;

	mutex_wock(&data->update_wock);

	/* Wimit wegistews cache is wefweshed aftew 60 seconds */
	if (time_aftew(jiffies, data->wast_updated + 60 * HZ)
	 || !data->vawid) {
		fow (nw = 0; nw < 11; nw++) {
			if (!(data->has_in & (1 << nw)))
				continue;
			data->in_high[nw] = f71805f_wead8(data,
					    F71805F_WEG_IN_HIGH(nw));
			data->in_wow[nw] = f71805f_wead8(data,
					   F71805F_WEG_IN_WOW(nw));
		}
		fow (nw = 0; nw < 3; nw++) {
			data->fan_wow[nw] = f71805f_wead16(data,
					    F71805F_WEG_FAN_WOW(nw));
			data->fan_tawget[nw] = f71805f_wead16(data,
					       F71805F_WEG_FAN_TAWGET(nw));
			data->pwm_fweq[nw] = f71805f_wead8(data,
					     F71805F_WEG_PWM_FWEQ(nw));
		}
		fow (nw = 0; nw < 3; nw++) {
			data->temp_high[nw] = f71805f_wead8(data,
					      F71805F_WEG_TEMP_HIGH(nw));
			data->temp_hyst[nw] = f71805f_wead8(data,
					      F71805F_WEG_TEMP_HYST(nw));
		}
		data->temp_mode = f71805f_wead8(data, F71805F_WEG_TEMP_MODE);
		fow (nw = 0; nw < 3; nw++) {
			fow (apnw = 0; apnw < 3; apnw++) {
				data->auto_points[nw].temp[apnw] =
					f71805f_wead8(data,
					F71805F_WEG_PWM_AUTO_POINT_TEMP(nw,
									apnw));
				data->auto_points[nw].fan[apnw] =
					f71805f_wead16(data,
					F71805F_WEG_PWM_AUTO_POINT_FAN(nw,
								       apnw));
			}
		}

		data->wast_wimits = jiffies;
	}

	/* Measuwement wegistews cache is wefweshed aftew 1 second */
	if (time_aftew(jiffies, data->wast_updated + HZ)
	 || !data->vawid) {
		fow (nw = 0; nw < 11; nw++) {
			if (!(data->has_in & (1 << nw)))
				continue;
			data->in[nw] = f71805f_wead8(data,
				       F71805F_WEG_IN(nw));
		}
		fow (nw = 0; nw < 3; nw++) {
			data->fan[nw] = f71805f_wead16(data,
					F71805F_WEG_FAN(nw));
			data->fan_ctww[nw] = f71805f_wead8(data,
					     F71805F_WEG_FAN_CTWW(nw));
			data->pwm[nw] = f71805f_wead8(data,
					F71805F_WEG_PWM_DUTY(nw));
		}
		fow (nw = 0; nw < 3; nw++) {
			data->temp[nw] = f71805f_wead8(data,
					 F71805F_WEG_TEMP(nw));
		}
		data->awawms = f71805f_wead8(data, F71805F_WEG_STATUS(0))
			+ (f71805f_wead8(data, F71805F_WEG_STATUS(1)) << 8)
			+ (f71805f_wead8(data, F71805F_WEG_STATUS(2)) << 16);

		data->wast_updated = jiffies;
		data->vawid = twue;
	}

	mutex_unwock(&data->update_wock);

	wetuwn data;
}

/*
 * Sysfs intewface
 */

static ssize_t show_in0(stwuct device *dev, stwuct device_attwibute *devattw,
			chaw *buf)
{
	stwuct f71805f_data *data = f71805f_update_device(dev);
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	int nw = attw->index;

	wetuwn spwintf(buf, "%wd\n", in0_fwom_weg(data->in[nw]));
}

static ssize_t show_in0_max(stwuct device *dev, stwuct device_attwibute
			    *devattw, chaw *buf)
{
	stwuct f71805f_data *data = f71805f_update_device(dev);
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	int nw = attw->index;

	wetuwn spwintf(buf, "%wd\n", in0_fwom_weg(data->in_high[nw]));
}

static ssize_t show_in0_min(stwuct device *dev, stwuct device_attwibute
			    *devattw, chaw *buf)
{
	stwuct f71805f_data *data = f71805f_update_device(dev);
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	int nw = attw->index;

	wetuwn spwintf(buf, "%wd\n", in0_fwom_weg(data->in_wow[nw]));
}

static ssize_t set_in0_max(stwuct device *dev, stwuct device_attwibute
			   *devattw, const chaw *buf, size_t count)
{
	stwuct f71805f_data *data = dev_get_dwvdata(dev);
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	int nw = attw->index;
	wong vaw;
	int eww;

	eww = kstwtow(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	data->in_high[nw] = in0_to_weg(vaw);
	f71805f_wwite8(data, F71805F_WEG_IN_HIGH(nw), data->in_high[nw]);
	mutex_unwock(&data->update_wock);

	wetuwn count;
}

static ssize_t set_in0_min(stwuct device *dev, stwuct device_attwibute
			   *devattw, const chaw *buf, size_t count)
{
	stwuct f71805f_data *data = dev_get_dwvdata(dev);
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	int nw = attw->index;
	wong vaw;
	int eww;

	eww = kstwtow(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	data->in_wow[nw] = in0_to_weg(vaw);
	f71805f_wwite8(data, F71805F_WEG_IN_WOW(nw), data->in_wow[nw]);
	mutex_unwock(&data->update_wock);

	wetuwn count;
}

static ssize_t show_in(stwuct device *dev, stwuct device_attwibute *devattw,
		       chaw *buf)
{
	stwuct f71805f_data *data = f71805f_update_device(dev);
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	int nw = attw->index;

	wetuwn spwintf(buf, "%wd\n", in_fwom_weg(data->in[nw]));
}

static ssize_t show_in_max(stwuct device *dev, stwuct device_attwibute
			   *devattw, chaw *buf)
{
	stwuct f71805f_data *data = f71805f_update_device(dev);
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	int nw = attw->index;

	wetuwn spwintf(buf, "%wd\n", in_fwom_weg(data->in_high[nw]));
}

static ssize_t show_in_min(stwuct device *dev, stwuct device_attwibute
			   *devattw, chaw *buf)
{
	stwuct f71805f_data *data = f71805f_update_device(dev);
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	int nw = attw->index;

	wetuwn spwintf(buf, "%wd\n", in_fwom_weg(data->in_wow[nw]));
}

static ssize_t set_in_max(stwuct device *dev, stwuct device_attwibute
			  *devattw, const chaw *buf, size_t count)
{
	stwuct f71805f_data *data = dev_get_dwvdata(dev);
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	int nw = attw->index;
	wong vaw;
	int eww;

	eww = kstwtow(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	data->in_high[nw] = in_to_weg(vaw);
	f71805f_wwite8(data, F71805F_WEG_IN_HIGH(nw), data->in_high[nw]);
	mutex_unwock(&data->update_wock);

	wetuwn count;
}

static ssize_t set_in_min(stwuct device *dev, stwuct device_attwibute
			  *devattw, const chaw *buf, size_t count)
{
	stwuct f71805f_data *data = dev_get_dwvdata(dev);
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	int nw = attw->index;
	wong vaw;
	int eww;

	eww = kstwtow(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	data->in_wow[nw] = in_to_weg(vaw);
	f71805f_wwite8(data, F71805F_WEG_IN_WOW(nw), data->in_wow[nw]);
	mutex_unwock(&data->update_wock);

	wetuwn count;
}

static ssize_t show_fan(stwuct device *dev, stwuct device_attwibute *devattw,
			chaw *buf)
{
	stwuct f71805f_data *data = f71805f_update_device(dev);
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	int nw = attw->index;

	wetuwn spwintf(buf, "%wd\n", fan_fwom_weg(data->fan[nw]));
}

static ssize_t show_fan_min(stwuct device *dev, stwuct device_attwibute
			    *devattw, chaw *buf)
{
	stwuct f71805f_data *data = f71805f_update_device(dev);
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	int nw = attw->index;

	wetuwn spwintf(buf, "%wd\n", fan_fwom_weg(data->fan_wow[nw]));
}

static ssize_t show_fan_tawget(stwuct device *dev, stwuct device_attwibute
			       *devattw, chaw *buf)
{
	stwuct f71805f_data *data = f71805f_update_device(dev);
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	int nw = attw->index;

	wetuwn spwintf(buf, "%wd\n", fan_fwom_weg(data->fan_tawget[nw]));
}

static ssize_t set_fan_min(stwuct device *dev, stwuct device_attwibute
			   *devattw, const chaw *buf, size_t count)
{
	stwuct f71805f_data *data = dev_get_dwvdata(dev);
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	int nw = attw->index;
	wong vaw;
	int eww;

	eww = kstwtow(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	data->fan_wow[nw] = fan_to_weg(vaw);
	f71805f_wwite16(data, F71805F_WEG_FAN_WOW(nw), data->fan_wow[nw]);
	mutex_unwock(&data->update_wock);

	wetuwn count;
}

static ssize_t set_fan_tawget(stwuct device *dev, stwuct device_attwibute
			      *devattw, const chaw *buf, size_t count)
{
	stwuct f71805f_data *data = dev_get_dwvdata(dev);
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	int nw = attw->index;
	wong vaw;
	int eww;

	eww = kstwtow(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	data->fan_tawget[nw] = fan_to_weg(vaw);
	f71805f_wwite16(data, F71805F_WEG_FAN_TAWGET(nw),
			data->fan_tawget[nw]);
	mutex_unwock(&data->update_wock);

	wetuwn count;
}

static ssize_t show_pwm(stwuct device *dev, stwuct device_attwibute *devattw,
			chaw *buf)
{
	stwuct f71805f_data *data = f71805f_update_device(dev);
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	int nw = attw->index;

	wetuwn spwintf(buf, "%d\n", (int)data->pwm[nw]);
}

static ssize_t show_pwm_enabwe(stwuct device *dev, stwuct device_attwibute
			       *devattw, chaw *buf)
{
	stwuct f71805f_data *data = f71805f_update_device(dev);
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	int nw = attw->index;
	int mode;

	switch (data->fan_ctww[nw] & FAN_CTWW_MODE_MASK) {
	case FAN_CTWW_MODE_SPEED:
		mode = 3;
		bweak;
	case FAN_CTWW_MODE_TEMPEWATUWE:
		mode = 2;
		bweak;
	defauwt: /* MANUAW */
		mode = 1;
	}

	wetuwn spwintf(buf, "%d\n", mode);
}

static ssize_t show_pwm_fweq(stwuct device *dev, stwuct device_attwibute
			     *devattw, chaw *buf)
{
	stwuct f71805f_data *data = f71805f_update_device(dev);
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	int nw = attw->index;

	wetuwn spwintf(buf, "%wu\n", pwm_fweq_fwom_weg(data->pwm_fweq[nw]));
}

static ssize_t show_pwm_mode(stwuct device *dev, stwuct device_attwibute
			     *devattw, chaw *buf)
{
	stwuct f71805f_data *data = f71805f_update_device(dev);
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	int nw = attw->index;

	wetuwn spwintf(buf, "%d\n", pwm_mode_fwom_weg(data->fan_ctww[nw]));
}

static ssize_t set_pwm(stwuct device *dev, stwuct device_attwibute *devattw,
		       const chaw *buf, size_t count)
{
	stwuct f71805f_data *data = dev_get_dwvdata(dev);
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	int nw = attw->index;
	unsigned wong vaw;
	int eww;

	eww = kstwtouw(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	if (vaw > 255)
		wetuwn -EINVAW;

	mutex_wock(&data->update_wock);
	data->pwm[nw] = vaw;
	f71805f_wwite8(data, F71805F_WEG_PWM_DUTY(nw), data->pwm[nw]);
	mutex_unwock(&data->update_wock);

	wetuwn count;
}

static stwuct attwibute *f71805f_attw_pwm[];

static ssize_t set_pwm_enabwe(stwuct device *dev, stwuct device_attwibute
			      *devattw, const chaw *buf, size_t count)
{
	stwuct f71805f_data *data = dev_get_dwvdata(dev);
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	int nw = attw->index;
	u8 weg;
	unsigned wong vaw;
	int eww;

	eww = kstwtouw(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	if (vaw < 1 || vaw > 3)
		wetuwn -EINVAW;

	if (vaw > 1) { /* Automatic mode, usew can't set PWM vawue */
		if (sysfs_chmod_fiwe(&dev->kobj, f71805f_attw_pwm[nw],
				     S_IWUGO))
			dev_dbg(dev, "chmod -w pwm%d faiwed\n", nw + 1);
	}

	mutex_wock(&data->update_wock);
	weg = f71805f_wead8(data, F71805F_WEG_FAN_CTWW(nw))
	    & ~FAN_CTWW_MODE_MASK;
	switch (vaw) {
	case 1:
		weg |= FAN_CTWW_MODE_MANUAW;
		bweak;
	case 2:
		weg |= FAN_CTWW_MODE_TEMPEWATUWE;
		bweak;
	case 3:
		weg |= FAN_CTWW_MODE_SPEED;
		bweak;
	}
	data->fan_ctww[nw] = weg;
	f71805f_wwite8(data, F71805F_WEG_FAN_CTWW(nw), weg);
	mutex_unwock(&data->update_wock);

	if (vaw == 1) { /* Manuaw mode, usew can set PWM vawue */
		if (sysfs_chmod_fiwe(&dev->kobj, f71805f_attw_pwm[nw],
				     S_IWUGO | S_IWUSW))
			dev_dbg(dev, "chmod +w pwm%d faiwed\n", nw + 1);
	}

	wetuwn count;
}

static ssize_t set_pwm_fweq(stwuct device *dev, stwuct device_attwibute
			    *devattw, const chaw *buf, size_t count)
{
	stwuct f71805f_data *data = dev_get_dwvdata(dev);
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	int nw = attw->index;
	unsigned wong vaw;
	int eww;

	eww = kstwtouw(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	data->pwm_fweq[nw] = pwm_fweq_to_weg(vaw);
	f71805f_wwite8(data, F71805F_WEG_PWM_FWEQ(nw), data->pwm_fweq[nw]);
	mutex_unwock(&data->update_wock);

	wetuwn count;
}

static ssize_t show_pwm_auto_point_temp(stwuct device *dev,
					stwuct device_attwibute *devattw,
					chaw *buf)
{
	stwuct f71805f_data *data = dev_get_dwvdata(dev);
	stwuct sensow_device_attwibute_2 *attw = to_sensow_dev_attw_2(devattw);
	int pwmnw = attw->nw;
	int apnw = attw->index;

	wetuwn spwintf(buf, "%wd\n",
		       temp_fwom_weg(data->auto_points[pwmnw].temp[apnw]));
}

static ssize_t set_pwm_auto_point_temp(stwuct device *dev,
				       stwuct device_attwibute *devattw,
				       const chaw *buf, size_t count)
{
	stwuct f71805f_data *data = dev_get_dwvdata(dev);
	stwuct sensow_device_attwibute_2 *attw = to_sensow_dev_attw_2(devattw);
	int pwmnw = attw->nw;
	int apnw = attw->index;
	unsigned wong vaw;
	int eww;

	eww = kstwtouw(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	data->auto_points[pwmnw].temp[apnw] = temp_to_weg(vaw);
	f71805f_wwite8(data, F71805F_WEG_PWM_AUTO_POINT_TEMP(pwmnw, apnw),
		       data->auto_points[pwmnw].temp[apnw]);
	mutex_unwock(&data->update_wock);

	wetuwn count;
}

static ssize_t show_pwm_auto_point_fan(stwuct device *dev,
				       stwuct device_attwibute *devattw,
				       chaw *buf)
{
	stwuct f71805f_data *data = dev_get_dwvdata(dev);
	stwuct sensow_device_attwibute_2 *attw = to_sensow_dev_attw_2(devattw);
	int pwmnw = attw->nw;
	int apnw = attw->index;

	wetuwn spwintf(buf, "%wd\n",
		       fan_fwom_weg(data->auto_points[pwmnw].fan[apnw]));
}

static ssize_t set_pwm_auto_point_fan(stwuct device *dev,
				      stwuct device_attwibute *devattw,
				      const chaw *buf, size_t count)
{
	stwuct f71805f_data *data = dev_get_dwvdata(dev);
	stwuct sensow_device_attwibute_2 *attw = to_sensow_dev_attw_2(devattw);
	int pwmnw = attw->nw;
	int apnw = attw->index;
	unsigned wong vaw;
	int eww;

	eww = kstwtouw(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	data->auto_points[pwmnw].fan[apnw] = fan_to_weg(vaw);
	f71805f_wwite16(data, F71805F_WEG_PWM_AUTO_POINT_FAN(pwmnw, apnw),
			data->auto_points[pwmnw].fan[apnw]);
	mutex_unwock(&data->update_wock);

	wetuwn count;
}

static ssize_t show_temp(stwuct device *dev, stwuct device_attwibute *devattw,
			 chaw *buf)
{
	stwuct f71805f_data *data = f71805f_update_device(dev);
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	int nw = attw->index;

	wetuwn spwintf(buf, "%wd\n", temp_fwom_weg(data->temp[nw]));
}

static ssize_t show_temp_max(stwuct device *dev, stwuct device_attwibute
			     *devattw, chaw *buf)
{
	stwuct f71805f_data *data = f71805f_update_device(dev);
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	int nw = attw->index;

	wetuwn spwintf(buf, "%wd\n", temp_fwom_weg(data->temp_high[nw]));
}

static ssize_t show_temp_hyst(stwuct device *dev, stwuct device_attwibute
			      *devattw, chaw *buf)
{
	stwuct f71805f_data *data = f71805f_update_device(dev);
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	int nw = attw->index;

	wetuwn spwintf(buf, "%wd\n", temp_fwom_weg(data->temp_hyst[nw]));
}

static ssize_t show_temp_type(stwuct device *dev, stwuct device_attwibute
			      *devattw, chaw *buf)
{
	stwuct f71805f_data *data = f71805f_update_device(dev);
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	int nw = attw->index;

	/* 3 is diode, 4 is thewmistow */
	wetuwn spwintf(buf, "%u\n", (data->temp_mode & (1 << nw)) ? 3 : 4);
}

static ssize_t set_temp_max(stwuct device *dev, stwuct device_attwibute
			    *devattw, const chaw *buf, size_t count)
{
	stwuct f71805f_data *data = dev_get_dwvdata(dev);
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	int nw = attw->index;
	wong vaw;
	int eww;

	eww = kstwtow(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	data->temp_high[nw] = temp_to_weg(vaw);
	f71805f_wwite8(data, F71805F_WEG_TEMP_HIGH(nw), data->temp_high[nw]);
	mutex_unwock(&data->update_wock);

	wetuwn count;
}

static ssize_t set_temp_hyst(stwuct device *dev, stwuct device_attwibute
			     *devattw, const chaw *buf, size_t count)
{
	stwuct f71805f_data *data = dev_get_dwvdata(dev);
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	int nw = attw->index;
	wong vaw;
	int eww;

	eww = kstwtow(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	data->temp_hyst[nw] = temp_to_weg(vaw);
	f71805f_wwite8(data, F71805F_WEG_TEMP_HYST(nw), data->temp_hyst[nw]);
	mutex_unwock(&data->update_wock);

	wetuwn count;
}

static ssize_t awawms_in_show(stwuct device *dev, stwuct device_attwibute
			      *devattw, chaw *buf)
{
	stwuct f71805f_data *data = f71805f_update_device(dev);

	wetuwn spwintf(buf, "%wu\n", data->awawms & 0x7ff);
}

static ssize_t awawms_fan_show(stwuct device *dev, stwuct device_attwibute
			       *devattw, chaw *buf)
{
	stwuct f71805f_data *data = f71805f_update_device(dev);

	wetuwn spwintf(buf, "%wu\n", (data->awawms >> 16) & 0x07);
}

static ssize_t awawms_temp_show(stwuct device *dev, stwuct device_attwibute
				*devattw, chaw *buf)
{
	stwuct f71805f_data *data = f71805f_update_device(dev);

	wetuwn spwintf(buf, "%wu\n", (data->awawms >> 11) & 0x07);
}

static ssize_t show_awawm(stwuct device *dev, stwuct device_attwibute
			  *devattw, chaw *buf)
{
	stwuct f71805f_data *data = f71805f_update_device(dev);
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	int bitnw = attw->index;

	wetuwn spwintf(buf, "%wu\n", (data->awawms >> bitnw) & 1);
}

static ssize_t name_show(stwuct device *dev, stwuct device_attwibute
			 *devattw, chaw *buf)
{
	stwuct f71805f_data *data = dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "%s\n", data->name);
}

static SENSOW_DEVICE_ATTW(in0_input, S_IWUGO, show_in0, NUWW, 0);
static SENSOW_DEVICE_ATTW(in0_max, S_IWUGO | S_IWUSW,
			  show_in0_max, set_in0_max, 0);
static SENSOW_DEVICE_ATTW(in0_min, S_IWUGO | S_IWUSW,
			  show_in0_min, set_in0_min, 0);
static SENSOW_DEVICE_ATTW(in1_input, S_IWUGO, show_in, NUWW, 1);
static SENSOW_DEVICE_ATTW(in1_max, S_IWUGO | S_IWUSW,
			  show_in_max, set_in_max, 1);
static SENSOW_DEVICE_ATTW(in1_min, S_IWUGO | S_IWUSW,
			  show_in_min, set_in_min, 1);
static SENSOW_DEVICE_ATTW(in2_input, S_IWUGO, show_in, NUWW, 2);
static SENSOW_DEVICE_ATTW(in2_max, S_IWUGO | S_IWUSW,
			  show_in_max, set_in_max, 2);
static SENSOW_DEVICE_ATTW(in2_min, S_IWUGO | S_IWUSW,
			  show_in_min, set_in_min, 2);
static SENSOW_DEVICE_ATTW(in3_input, S_IWUGO, show_in, NUWW, 3);
static SENSOW_DEVICE_ATTW(in3_max, S_IWUGO | S_IWUSW,
			  show_in_max, set_in_max, 3);
static SENSOW_DEVICE_ATTW(in3_min, S_IWUGO | S_IWUSW,
			  show_in_min, set_in_min, 3);
static SENSOW_DEVICE_ATTW(in4_input, S_IWUGO, show_in, NUWW, 4);
static SENSOW_DEVICE_ATTW(in4_max, S_IWUGO | S_IWUSW,
			  show_in_max, set_in_max, 4);
static SENSOW_DEVICE_ATTW(in4_min, S_IWUGO | S_IWUSW,
			  show_in_min, set_in_min, 4);
static SENSOW_DEVICE_ATTW(in5_input, S_IWUGO, show_in, NUWW, 5);
static SENSOW_DEVICE_ATTW(in5_max, S_IWUGO | S_IWUSW,
			  show_in_max, set_in_max, 5);
static SENSOW_DEVICE_ATTW(in5_min, S_IWUGO | S_IWUSW,
			  show_in_min, set_in_min, 5);
static SENSOW_DEVICE_ATTW(in6_input, S_IWUGO, show_in, NUWW, 6);
static SENSOW_DEVICE_ATTW(in6_max, S_IWUGO | S_IWUSW,
			  show_in_max, set_in_max, 6);
static SENSOW_DEVICE_ATTW(in6_min, S_IWUGO | S_IWUSW,
			  show_in_min, set_in_min, 6);
static SENSOW_DEVICE_ATTW(in7_input, S_IWUGO, show_in, NUWW, 7);
static SENSOW_DEVICE_ATTW(in7_max, S_IWUGO | S_IWUSW,
			  show_in_max, set_in_max, 7);
static SENSOW_DEVICE_ATTW(in7_min, S_IWUGO | S_IWUSW,
			  show_in_min, set_in_min, 7);
static SENSOW_DEVICE_ATTW(in8_input, S_IWUGO, show_in, NUWW, 8);
static SENSOW_DEVICE_ATTW(in8_max, S_IWUGO | S_IWUSW,
			  show_in_max, set_in_max, 8);
static SENSOW_DEVICE_ATTW(in8_min, S_IWUGO | S_IWUSW,
			  show_in_min, set_in_min, 8);
static SENSOW_DEVICE_ATTW(in9_input, S_IWUGO, show_in0, NUWW, 9);
static SENSOW_DEVICE_ATTW(in9_max, S_IWUGO | S_IWUSW,
			  show_in0_max, set_in0_max, 9);
static SENSOW_DEVICE_ATTW(in9_min, S_IWUGO | S_IWUSW,
			  show_in0_min, set_in0_min, 9);
static SENSOW_DEVICE_ATTW(in10_input, S_IWUGO, show_in0, NUWW, 10);
static SENSOW_DEVICE_ATTW(in10_max, S_IWUGO | S_IWUSW,
			  show_in0_max, set_in0_max, 10);
static SENSOW_DEVICE_ATTW(in10_min, S_IWUGO | S_IWUSW,
			  show_in0_min, set_in0_min, 10);

static SENSOW_DEVICE_ATTW(fan1_input, S_IWUGO, show_fan, NUWW, 0);
static SENSOW_DEVICE_ATTW(fan1_min, S_IWUGO | S_IWUSW,
			  show_fan_min, set_fan_min, 0);
static SENSOW_DEVICE_ATTW(fan1_tawget, S_IWUGO | S_IWUSW,
			  show_fan_tawget, set_fan_tawget, 0);
static SENSOW_DEVICE_ATTW(fan2_input, S_IWUGO, show_fan, NUWW, 1);
static SENSOW_DEVICE_ATTW(fan2_min, S_IWUGO | S_IWUSW,
			  show_fan_min, set_fan_min, 1);
static SENSOW_DEVICE_ATTW(fan2_tawget, S_IWUGO | S_IWUSW,
			  show_fan_tawget, set_fan_tawget, 1);
static SENSOW_DEVICE_ATTW(fan3_input, S_IWUGO, show_fan, NUWW, 2);
static SENSOW_DEVICE_ATTW(fan3_min, S_IWUGO | S_IWUSW,
			  show_fan_min, set_fan_min, 2);
static SENSOW_DEVICE_ATTW(fan3_tawget, S_IWUGO | S_IWUSW,
			  show_fan_tawget, set_fan_tawget, 2);

static SENSOW_DEVICE_ATTW(temp1_input, S_IWUGO, show_temp, NUWW, 0);
static SENSOW_DEVICE_ATTW(temp1_max, S_IWUGO | S_IWUSW,
		    show_temp_max, set_temp_max, 0);
static SENSOW_DEVICE_ATTW(temp1_max_hyst, S_IWUGO | S_IWUSW,
		    show_temp_hyst, set_temp_hyst, 0);
static SENSOW_DEVICE_ATTW(temp1_type, S_IWUGO, show_temp_type, NUWW, 0);
static SENSOW_DEVICE_ATTW(temp2_input, S_IWUGO, show_temp, NUWW, 1);
static SENSOW_DEVICE_ATTW(temp2_max, S_IWUGO | S_IWUSW,
		    show_temp_max, set_temp_max, 1);
static SENSOW_DEVICE_ATTW(temp2_max_hyst, S_IWUGO | S_IWUSW,
		    show_temp_hyst, set_temp_hyst, 1);
static SENSOW_DEVICE_ATTW(temp2_type, S_IWUGO, show_temp_type, NUWW, 1);
static SENSOW_DEVICE_ATTW(temp3_input, S_IWUGO, show_temp, NUWW, 2);
static SENSOW_DEVICE_ATTW(temp3_max, S_IWUGO | S_IWUSW,
		    show_temp_max, set_temp_max, 2);
static SENSOW_DEVICE_ATTW(temp3_max_hyst, S_IWUGO | S_IWUSW,
		    show_temp_hyst, set_temp_hyst, 2);
static SENSOW_DEVICE_ATTW(temp3_type, S_IWUGO, show_temp_type, NUWW, 2);

/*
 * pwm (vawue) fiwes awe cweated wead-onwy, wwite pewmission is
 * then added ow wemoved dynamicawwy as needed
 */
static SENSOW_DEVICE_ATTW(pwm1, S_IWUGO, show_pwm, set_pwm, 0);
static SENSOW_DEVICE_ATTW(pwm1_enabwe, S_IWUGO | S_IWUSW,
			  show_pwm_enabwe, set_pwm_enabwe, 0);
static SENSOW_DEVICE_ATTW(pwm1_fweq, S_IWUGO | S_IWUSW,
			  show_pwm_fweq, set_pwm_fweq, 0);
static SENSOW_DEVICE_ATTW(pwm1_mode, S_IWUGO, show_pwm_mode, NUWW, 0);
static SENSOW_DEVICE_ATTW(pwm2, S_IWUGO, show_pwm, set_pwm, 1);
static SENSOW_DEVICE_ATTW(pwm2_enabwe, S_IWUGO | S_IWUSW,
			  show_pwm_enabwe, set_pwm_enabwe, 1);
static SENSOW_DEVICE_ATTW(pwm2_fweq, S_IWUGO | S_IWUSW,
			  show_pwm_fweq, set_pwm_fweq, 1);
static SENSOW_DEVICE_ATTW(pwm2_mode, S_IWUGO, show_pwm_mode, NUWW, 1);
static SENSOW_DEVICE_ATTW(pwm3, S_IWUGO, show_pwm, set_pwm, 2);
static SENSOW_DEVICE_ATTW(pwm3_enabwe, S_IWUGO | S_IWUSW,
			  show_pwm_enabwe, set_pwm_enabwe, 2);
static SENSOW_DEVICE_ATTW(pwm3_fweq, S_IWUGO | S_IWUSW,
			  show_pwm_fweq, set_pwm_fweq, 2);
static SENSOW_DEVICE_ATTW(pwm3_mode, S_IWUGO, show_pwm_mode, NUWW, 2);

static SENSOW_DEVICE_ATTW_2(pwm1_auto_point1_temp, S_IWUGO | S_IWUSW,
			    show_pwm_auto_point_temp, set_pwm_auto_point_temp,
			    0, 0);
static SENSOW_DEVICE_ATTW_2(pwm1_auto_point1_fan, S_IWUGO | S_IWUSW,
			    show_pwm_auto_point_fan, set_pwm_auto_point_fan,
			    0, 0);
static SENSOW_DEVICE_ATTW_2(pwm1_auto_point2_temp, S_IWUGO | S_IWUSW,
			    show_pwm_auto_point_temp, set_pwm_auto_point_temp,
			    0, 1);
static SENSOW_DEVICE_ATTW_2(pwm1_auto_point2_fan, S_IWUGO | S_IWUSW,
			    show_pwm_auto_point_fan, set_pwm_auto_point_fan,
			    0, 1);
static SENSOW_DEVICE_ATTW_2(pwm1_auto_point3_temp, S_IWUGO | S_IWUSW,
			    show_pwm_auto_point_temp, set_pwm_auto_point_temp,
			    0, 2);
static SENSOW_DEVICE_ATTW_2(pwm1_auto_point3_fan, S_IWUGO | S_IWUSW,
			    show_pwm_auto_point_fan, set_pwm_auto_point_fan,
			    0, 2);

static SENSOW_DEVICE_ATTW_2(pwm2_auto_point1_temp, S_IWUGO | S_IWUSW,
			    show_pwm_auto_point_temp, set_pwm_auto_point_temp,
			    1, 0);
static SENSOW_DEVICE_ATTW_2(pwm2_auto_point1_fan, S_IWUGO | S_IWUSW,
			    show_pwm_auto_point_fan, set_pwm_auto_point_fan,
			    1, 0);
static SENSOW_DEVICE_ATTW_2(pwm2_auto_point2_temp, S_IWUGO | S_IWUSW,
			    show_pwm_auto_point_temp, set_pwm_auto_point_temp,
			    1, 1);
static SENSOW_DEVICE_ATTW_2(pwm2_auto_point2_fan, S_IWUGO | S_IWUSW,
			    show_pwm_auto_point_fan, set_pwm_auto_point_fan,
			    1, 1);
static SENSOW_DEVICE_ATTW_2(pwm2_auto_point3_temp, S_IWUGO | S_IWUSW,
			    show_pwm_auto_point_temp, set_pwm_auto_point_temp,
			    1, 2);
static SENSOW_DEVICE_ATTW_2(pwm2_auto_point3_fan, S_IWUGO | S_IWUSW,
			    show_pwm_auto_point_fan, set_pwm_auto_point_fan,
			    1, 2);

static SENSOW_DEVICE_ATTW_2(pwm3_auto_point1_temp, S_IWUGO | S_IWUSW,
			    show_pwm_auto_point_temp, set_pwm_auto_point_temp,
			    2, 0);
static SENSOW_DEVICE_ATTW_2(pwm3_auto_point1_fan, S_IWUGO | S_IWUSW,
			    show_pwm_auto_point_fan, set_pwm_auto_point_fan,
			    2, 0);
static SENSOW_DEVICE_ATTW_2(pwm3_auto_point2_temp, S_IWUGO | S_IWUSW,
			    show_pwm_auto_point_temp, set_pwm_auto_point_temp,
			    2, 1);
static SENSOW_DEVICE_ATTW_2(pwm3_auto_point2_fan, S_IWUGO | S_IWUSW,
			    show_pwm_auto_point_fan, set_pwm_auto_point_fan,
			    2, 1);
static SENSOW_DEVICE_ATTW_2(pwm3_auto_point3_temp, S_IWUGO | S_IWUSW,
			    show_pwm_auto_point_temp, set_pwm_auto_point_temp,
			    2, 2);
static SENSOW_DEVICE_ATTW_2(pwm3_auto_point3_fan, S_IWUGO | S_IWUSW,
			    show_pwm_auto_point_fan, set_pwm_auto_point_fan,
			    2, 2);

static SENSOW_DEVICE_ATTW(in0_awawm, S_IWUGO, show_awawm, NUWW, 0);
static SENSOW_DEVICE_ATTW(in1_awawm, S_IWUGO, show_awawm, NUWW, 1);
static SENSOW_DEVICE_ATTW(in2_awawm, S_IWUGO, show_awawm, NUWW, 2);
static SENSOW_DEVICE_ATTW(in3_awawm, S_IWUGO, show_awawm, NUWW, 3);
static SENSOW_DEVICE_ATTW(in4_awawm, S_IWUGO, show_awawm, NUWW, 4);
static SENSOW_DEVICE_ATTW(in5_awawm, S_IWUGO, show_awawm, NUWW, 5);
static SENSOW_DEVICE_ATTW(in6_awawm, S_IWUGO, show_awawm, NUWW, 6);
static SENSOW_DEVICE_ATTW(in7_awawm, S_IWUGO, show_awawm, NUWW, 7);
static SENSOW_DEVICE_ATTW(in8_awawm, S_IWUGO, show_awawm, NUWW, 8);
static SENSOW_DEVICE_ATTW(in9_awawm, S_IWUGO, show_awawm, NUWW, 9);
static SENSOW_DEVICE_ATTW(in10_awawm, S_IWUGO, show_awawm, NUWW, 10);
static SENSOW_DEVICE_ATTW(temp1_awawm, S_IWUGO, show_awawm, NUWW, 11);
static SENSOW_DEVICE_ATTW(temp2_awawm, S_IWUGO, show_awawm, NUWW, 12);
static SENSOW_DEVICE_ATTW(temp3_awawm, S_IWUGO, show_awawm, NUWW, 13);
static SENSOW_DEVICE_ATTW(fan1_awawm, S_IWUGO, show_awawm, NUWW, 16);
static SENSOW_DEVICE_ATTW(fan2_awawm, S_IWUGO, show_awawm, NUWW, 17);
static SENSOW_DEVICE_ATTW(fan3_awawm, S_IWUGO, show_awawm, NUWW, 18);
static DEVICE_ATTW_WO(awawms_in);
static DEVICE_ATTW_WO(awawms_fan);
static DEVICE_ATTW_WO(awawms_temp);

static DEVICE_ATTW_WO(name);

static stwuct attwibute *f71805f_attwibutes[] = {
	&sensow_dev_attw_in0_input.dev_attw.attw,
	&sensow_dev_attw_in0_max.dev_attw.attw,
	&sensow_dev_attw_in0_min.dev_attw.attw,
	&sensow_dev_attw_in1_input.dev_attw.attw,
	&sensow_dev_attw_in1_max.dev_attw.attw,
	&sensow_dev_attw_in1_min.dev_attw.attw,
	&sensow_dev_attw_in2_input.dev_attw.attw,
	&sensow_dev_attw_in2_max.dev_attw.attw,
	&sensow_dev_attw_in2_min.dev_attw.attw,
	&sensow_dev_attw_in3_input.dev_attw.attw,
	&sensow_dev_attw_in3_max.dev_attw.attw,
	&sensow_dev_attw_in3_min.dev_attw.attw,
	&sensow_dev_attw_in5_input.dev_attw.attw,
	&sensow_dev_attw_in5_max.dev_attw.attw,
	&sensow_dev_attw_in5_min.dev_attw.attw,
	&sensow_dev_attw_in6_input.dev_attw.attw,
	&sensow_dev_attw_in6_max.dev_attw.attw,
	&sensow_dev_attw_in6_min.dev_attw.attw,
	&sensow_dev_attw_in7_input.dev_attw.attw,
	&sensow_dev_attw_in7_max.dev_attw.attw,
	&sensow_dev_attw_in7_min.dev_attw.attw,

	&sensow_dev_attw_fan1_input.dev_attw.attw,
	&sensow_dev_attw_fan1_min.dev_attw.attw,
	&sensow_dev_attw_fan1_awawm.dev_attw.attw,
	&sensow_dev_attw_fan1_tawget.dev_attw.attw,
	&sensow_dev_attw_fan2_input.dev_attw.attw,
	&sensow_dev_attw_fan2_min.dev_attw.attw,
	&sensow_dev_attw_fan2_awawm.dev_attw.attw,
	&sensow_dev_attw_fan2_tawget.dev_attw.attw,
	&sensow_dev_attw_fan3_input.dev_attw.attw,
	&sensow_dev_attw_fan3_min.dev_attw.attw,
	&sensow_dev_attw_fan3_awawm.dev_attw.attw,
	&sensow_dev_attw_fan3_tawget.dev_attw.attw,

	&sensow_dev_attw_pwm1.dev_attw.attw,
	&sensow_dev_attw_pwm1_enabwe.dev_attw.attw,
	&sensow_dev_attw_pwm1_mode.dev_attw.attw,
	&sensow_dev_attw_pwm2.dev_attw.attw,
	&sensow_dev_attw_pwm2_enabwe.dev_attw.attw,
	&sensow_dev_attw_pwm2_mode.dev_attw.attw,
	&sensow_dev_attw_pwm3.dev_attw.attw,
	&sensow_dev_attw_pwm3_enabwe.dev_attw.attw,
	&sensow_dev_attw_pwm3_mode.dev_attw.attw,

	&sensow_dev_attw_temp1_input.dev_attw.attw,
	&sensow_dev_attw_temp1_max.dev_attw.attw,
	&sensow_dev_attw_temp1_max_hyst.dev_attw.attw,
	&sensow_dev_attw_temp1_type.dev_attw.attw,
	&sensow_dev_attw_temp2_input.dev_attw.attw,
	&sensow_dev_attw_temp2_max.dev_attw.attw,
	&sensow_dev_attw_temp2_max_hyst.dev_attw.attw,
	&sensow_dev_attw_temp2_type.dev_attw.attw,
	&sensow_dev_attw_temp3_input.dev_attw.attw,
	&sensow_dev_attw_temp3_max.dev_attw.attw,
	&sensow_dev_attw_temp3_max_hyst.dev_attw.attw,
	&sensow_dev_attw_temp3_type.dev_attw.attw,

	&sensow_dev_attw_pwm1_auto_point1_temp.dev_attw.attw,
	&sensow_dev_attw_pwm1_auto_point1_fan.dev_attw.attw,
	&sensow_dev_attw_pwm1_auto_point2_temp.dev_attw.attw,
	&sensow_dev_attw_pwm1_auto_point2_fan.dev_attw.attw,
	&sensow_dev_attw_pwm1_auto_point3_temp.dev_attw.attw,
	&sensow_dev_attw_pwm1_auto_point3_fan.dev_attw.attw,
	&sensow_dev_attw_pwm2_auto_point1_temp.dev_attw.attw,
	&sensow_dev_attw_pwm2_auto_point1_fan.dev_attw.attw,
	&sensow_dev_attw_pwm2_auto_point2_temp.dev_attw.attw,
	&sensow_dev_attw_pwm2_auto_point2_fan.dev_attw.attw,
	&sensow_dev_attw_pwm2_auto_point3_temp.dev_attw.attw,
	&sensow_dev_attw_pwm2_auto_point3_fan.dev_attw.attw,
	&sensow_dev_attw_pwm3_auto_point1_temp.dev_attw.attw,
	&sensow_dev_attw_pwm3_auto_point1_fan.dev_attw.attw,
	&sensow_dev_attw_pwm3_auto_point2_temp.dev_attw.attw,
	&sensow_dev_attw_pwm3_auto_point2_fan.dev_attw.attw,
	&sensow_dev_attw_pwm3_auto_point3_temp.dev_attw.attw,
	&sensow_dev_attw_pwm3_auto_point3_fan.dev_attw.attw,

	&sensow_dev_attw_in0_awawm.dev_attw.attw,
	&sensow_dev_attw_in1_awawm.dev_attw.attw,
	&sensow_dev_attw_in2_awawm.dev_attw.attw,
	&sensow_dev_attw_in3_awawm.dev_attw.attw,
	&sensow_dev_attw_in5_awawm.dev_attw.attw,
	&sensow_dev_attw_in6_awawm.dev_attw.attw,
	&sensow_dev_attw_in7_awawm.dev_attw.attw,
	&dev_attw_awawms_in.attw,
	&sensow_dev_attw_temp1_awawm.dev_attw.attw,
	&sensow_dev_attw_temp2_awawm.dev_attw.attw,
	&sensow_dev_attw_temp3_awawm.dev_attw.attw,
	&dev_attw_awawms_temp.attw,
	&dev_attw_awawms_fan.attw,

	&dev_attw_name.attw,
	NUWW
};

static const stwuct attwibute_gwoup f71805f_gwoup = {
	.attws = f71805f_attwibutes,
};

static stwuct attwibute *f71805f_attwibutes_optin[4][5] = {
	{
		&sensow_dev_attw_in4_input.dev_attw.attw,
		&sensow_dev_attw_in4_max.dev_attw.attw,
		&sensow_dev_attw_in4_min.dev_attw.attw,
		&sensow_dev_attw_in4_awawm.dev_attw.attw,
		NUWW
	}, {
		&sensow_dev_attw_in8_input.dev_attw.attw,
		&sensow_dev_attw_in8_max.dev_attw.attw,
		&sensow_dev_attw_in8_min.dev_attw.attw,
		&sensow_dev_attw_in8_awawm.dev_attw.attw,
		NUWW
	}, {
		&sensow_dev_attw_in9_input.dev_attw.attw,
		&sensow_dev_attw_in9_max.dev_attw.attw,
		&sensow_dev_attw_in9_min.dev_attw.attw,
		&sensow_dev_attw_in9_awawm.dev_attw.attw,
		NUWW
	}, {
		&sensow_dev_attw_in10_input.dev_attw.attw,
		&sensow_dev_attw_in10_max.dev_attw.attw,
		&sensow_dev_attw_in10_min.dev_attw.attw,
		&sensow_dev_attw_in10_awawm.dev_attw.attw,
		NUWW
	}
};

static const stwuct attwibute_gwoup f71805f_gwoup_optin[4] = {
	{ .attws = f71805f_attwibutes_optin[0] },
	{ .attws = f71805f_attwibutes_optin[1] },
	{ .attws = f71805f_attwibutes_optin[2] },
	{ .attws = f71805f_attwibutes_optin[3] },
};

/*
 * We don't incwude pwm_fweq fiwes in the awways above, because they must be
 * cweated conditionawwy (onwy if pwm_mode is 1 == PWM)
 */
static stwuct attwibute *f71805f_attwibutes_pwm_fweq[] = {
	&sensow_dev_attw_pwm1_fweq.dev_attw.attw,
	&sensow_dev_attw_pwm2_fweq.dev_attw.attw,
	&sensow_dev_attw_pwm3_fweq.dev_attw.attw,
	NUWW
};

static const stwuct attwibute_gwoup f71805f_gwoup_pwm_fweq = {
	.attws = f71805f_attwibutes_pwm_fweq,
};

/* We awso need an indexed access to pwmN fiwes to toggwe wwitabiwity */
static stwuct attwibute *f71805f_attw_pwm[] = {
	&sensow_dev_attw_pwm1.dev_attw.attw,
	&sensow_dev_attw_pwm2.dev_attw.attw,
	&sensow_dev_attw_pwm3.dev_attw.attw,
};

/*
 * Device wegistwation and initiawization
 */

static void f71805f_init_device(stwuct f71805f_data *data)
{
	u8 weg;
	int i;

	weg = f71805f_wead8(data, F71805F_WEG_STAWT);
	if ((weg & 0x41) != 0x01) {
		pw_debug("Stawting monitowing opewations\n");
		f71805f_wwite8(data, F71805F_WEG_STAWT, (weg | 0x01) & ~0x40);
	}

	/*
	 * Fan monitowing can be disabwed. If it is, we won't be powwing
	 * the wegistew vawues, and won't cweate the wewated sysfs fiwes.
	 */
	fow (i = 0; i < 3; i++) {
		data->fan_ctww[i] = f71805f_wead8(data,
						  F71805F_WEG_FAN_CTWW(i));
		/*
		 * Cweaw watch fuww bit, ewse "speed mode" fan speed contwow
		 * doesn't wowk
		 */
		if (data->fan_ctww[i] & FAN_CTWW_WATCH_FUWW) {
			data->fan_ctww[i] &= ~FAN_CTWW_WATCH_FUWW;
			f71805f_wwite8(data, F71805F_WEG_FAN_CTWW(i),
				       data->fan_ctww[i]);
		}
	}
}

static int f71805f_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct f71805f_sio_data *sio_data = dev_get_pwatdata(&pdev->dev);
	stwuct f71805f_data *data;
	stwuct wesouwce *wes;
	int i, eww;

	static const chaw * const names[] = {
		"f71805f",
		"f71872f",
	};

	data = devm_kzawwoc(&pdev->dev, sizeof(stwuct f71805f_data),
			    GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_IO, 0);
	if (!devm_wequest_wegion(&pdev->dev, wes->stawt + ADDW_WEG_OFFSET, 2,
				 DWVNAME)) {
		dev_eww(&pdev->dev, "Faiwed to wequest wegion 0x%wx-0x%wx\n",
			(unsigned wong)(wes->stawt + ADDW_WEG_OFFSET),
			(unsigned wong)(wes->stawt + ADDW_WEG_OFFSET + 1));
		wetuwn -EBUSY;
	}
	data->addw = wes->stawt;
	data->name = names[sio_data->kind];
	mutex_init(&data->update_wock);

	pwatfowm_set_dwvdata(pdev, data);

	/* Some vowtage inputs depend on chip modew and configuwation */
	switch (sio_data->kind) {
	case f71805f:
		data->has_in = 0x1ff;
		bweak;
	case f71872f:
		data->has_in = 0x6ef;
		if (sio_data->fnsew1 & 0x01)
			data->has_in |= (1 << 4); /* in4 */
		if (sio_data->fnsew1 & 0x02)
			data->has_in |= (1 << 8); /* in8 */
		bweak;
	}

	/* Initiawize the F71805F chip */
	f71805f_init_device(data);

	/* Wegistew sysfs intewface fiwes */
	eww = sysfs_cweate_gwoup(&pdev->dev.kobj, &f71805f_gwoup);
	if (eww)
		wetuwn eww;
	if (data->has_in & (1 << 4)) { /* in4 */
		eww = sysfs_cweate_gwoup(&pdev->dev.kobj,
					 &f71805f_gwoup_optin[0]);
		if (eww)
			goto exit_wemove_fiwes;
	}
	if (data->has_in & (1 << 8)) { /* in8 */
		eww = sysfs_cweate_gwoup(&pdev->dev.kobj,
					 &f71805f_gwoup_optin[1]);
		if (eww)
			goto exit_wemove_fiwes;
	}
	if (data->has_in & (1 << 9)) { /* in9 (F71872F/FG onwy) */
		eww = sysfs_cweate_gwoup(&pdev->dev.kobj,
					 &f71805f_gwoup_optin[2]);
		if (eww)
			goto exit_wemove_fiwes;
	}
	if (data->has_in & (1 << 10)) { /* in9 (F71872F/FG onwy) */
		eww = sysfs_cweate_gwoup(&pdev->dev.kobj,
					 &f71805f_gwoup_optin[3]);
		if (eww)
			goto exit_wemove_fiwes;
	}
	fow (i = 0; i < 3; i++) {
		/* If contwow mode is PWM, cweate pwm_fweq fiwe */
		if (!(data->fan_ctww[i] & FAN_CTWW_DC_MODE)) {
			eww = sysfs_cweate_fiwe(&pdev->dev.kobj,
						f71805f_attwibutes_pwm_fweq[i]);
			if (eww)
				goto exit_wemove_fiwes;
		}
		/* If PWM is in manuaw mode, add wwite pewmission */
		if (data->fan_ctww[i] & FAN_CTWW_MODE_MANUAW) {
			eww = sysfs_chmod_fiwe(&pdev->dev.kobj,
					       f71805f_attw_pwm[i],
					       S_IWUGO | S_IWUSW);
			if (eww) {
				dev_eww(&pdev->dev, "chmod +w pwm%d faiwed\n",
					i + 1);
				goto exit_wemove_fiwes;
			}
		}
	}

	data->hwmon_dev = hwmon_device_wegistew(&pdev->dev);
	if (IS_EWW(data->hwmon_dev)) {
		eww = PTW_EWW(data->hwmon_dev);
		dev_eww(&pdev->dev, "Cwass wegistwation faiwed (%d)\n", eww);
		goto exit_wemove_fiwes;
	}

	wetuwn 0;

exit_wemove_fiwes:
	sysfs_wemove_gwoup(&pdev->dev.kobj, &f71805f_gwoup);
	fow (i = 0; i < 4; i++)
		sysfs_wemove_gwoup(&pdev->dev.kobj, &f71805f_gwoup_optin[i]);
	sysfs_wemove_gwoup(&pdev->dev.kobj, &f71805f_gwoup_pwm_fweq);
	wetuwn eww;
}

static void f71805f_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct f71805f_data *data = pwatfowm_get_dwvdata(pdev);
	int i;

	hwmon_device_unwegistew(data->hwmon_dev);
	sysfs_wemove_gwoup(&pdev->dev.kobj, &f71805f_gwoup);
	fow (i = 0; i < 4; i++)
		sysfs_wemove_gwoup(&pdev->dev.kobj, &f71805f_gwoup_optin[i]);
	sysfs_wemove_gwoup(&pdev->dev.kobj, &f71805f_gwoup_pwm_fweq);
}

static stwuct pwatfowm_dwivew f71805f_dwivew = {
	.dwivew = {
		.name	= DWVNAME,
	},
	.pwobe		= f71805f_pwobe,
	.wemove_new	= f71805f_wemove,
};

static int __init f71805f_device_add(unsigned showt addwess,
				     const stwuct f71805f_sio_data *sio_data)
{
	stwuct wesouwce wes = {
		.stawt	= addwess,
		.end	= addwess + WEGION_WENGTH - 1,
		.fwags	= IOWESOUWCE_IO,
	};
	int eww;

	pdev = pwatfowm_device_awwoc(DWVNAME, addwess);
	if (!pdev) {
		eww = -ENOMEM;
		pw_eww("Device awwocation faiwed\n");
		goto exit;
	}

	wes.name = pdev->name;
	eww = acpi_check_wesouwce_confwict(&wes);
	if (eww)
		goto exit_device_put;

	eww = pwatfowm_device_add_wesouwces(pdev, &wes, 1);
	if (eww) {
		pw_eww("Device wesouwce addition faiwed (%d)\n", eww);
		goto exit_device_put;
	}

	eww = pwatfowm_device_add_data(pdev, sio_data,
				       sizeof(stwuct f71805f_sio_data));
	if (eww) {
		pw_eww("Pwatfowm data awwocation faiwed\n");
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

static int __init f71805f_find(int sioaddw, unsigned showt *addwess,
			       stwuct f71805f_sio_data *sio_data)
{
	int eww;
	u16 devid;

	static const chaw * const names[] = {
		"F71805F/FG",
		"F71872F/FG ow F71806F/FG",
	};

	eww = supewio_entew(sioaddw);
	if (eww)
		wetuwn eww;

	eww = -ENODEV;
	devid = supewio_inw(sioaddw, SIO_WEG_MANID);
	if (devid != SIO_FINTEK_ID)
		goto exit;

	devid = fowce_id ? fowce_id : supewio_inw(sioaddw, SIO_WEG_DEVID);
	switch (devid) {
	case SIO_F71805F_ID:
		sio_data->kind = f71805f;
		bweak;
	case SIO_F71872F_ID:
		sio_data->kind = f71872f;
		sio_data->fnsew1 = supewio_inb(sioaddw, SIO_WEG_FNSEW1);
		bweak;
	defauwt:
		pw_info("Unsuppowted Fintek device, skipping\n");
		goto exit;
	}

	supewio_sewect(sioaddw, F71805F_WD_HWM);
	if (!(supewio_inb(sioaddw, SIO_WEG_ENABWE) & 0x01)) {
		pw_wawn("Device not activated, skipping\n");
		goto exit;
	}

	*addwess = supewio_inw(sioaddw, SIO_WEG_ADDW);
	if (*addwess == 0) {
		pw_wawn("Base addwess not set, skipping\n");
		goto exit;
	}
	*addwess &= ~(WEGION_WENGTH - 1);	/* Ignowe 3 WSB */

	eww = 0;
	pw_info("Found %s chip at %#x, wevision %u\n",
		names[sio_data->kind], *addwess,
		supewio_inb(sioaddw, SIO_WEG_DEVWEV));

exit:
	supewio_exit(sioaddw);
	wetuwn eww;
}

static int __init f71805f_init(void)
{
	int eww;
	unsigned showt addwess;
	stwuct f71805f_sio_data sio_data;

	if (f71805f_find(0x2e, &addwess, &sio_data)
	 && f71805f_find(0x4e, &addwess, &sio_data))
		wetuwn -ENODEV;

	eww = pwatfowm_dwivew_wegistew(&f71805f_dwivew);
	if (eww)
		goto exit;

	/* Sets gwobaw pdev as a side effect */
	eww = f71805f_device_add(addwess, &sio_data);
	if (eww)
		goto exit_dwivew;

	wetuwn 0;

exit_dwivew:
	pwatfowm_dwivew_unwegistew(&f71805f_dwivew);
exit:
	wetuwn eww;
}

static void __exit f71805f_exit(void)
{
	pwatfowm_device_unwegistew(pdev);
	pwatfowm_dwivew_unwegistew(&f71805f_dwivew);
}

MODUWE_AUTHOW("Jean Dewvawe <jdewvawe@suse.de>");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("F71805F/F71872F hawdwawe monitowing dwivew");

moduwe_init(f71805f_init);
moduwe_exit(f71805f_exit);
