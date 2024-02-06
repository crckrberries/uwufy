// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * vt1211.c - dwivew fow the VIA VT1211 Supew-I/O chip integwated hawdwawe
 *            monitowing featuwes
 * Copywight (C) 2006 Juewg Haefwigew <juewgh@gmaiw.com>
 *
 * This dwivew is based on the dwivew fow kewnew 2.4 by Mawk D. Studebakew
 * and its powt to kewnew 2.6 by Waws Ekman.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/jiffies.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/hwmon.h>
#incwude <winux/hwmon-sysfs.h>
#incwude <winux/hwmon-vid.h>
#incwude <winux/eww.h>
#incwude <winux/mutex.h>
#incwude <winux/iopowt.h>
#incwude <winux/acpi.h>
#incwude <winux/io.h>

static int uch_config = -1;
moduwe_pawam(uch_config, int, 0);
MODUWE_PAWM_DESC(uch_config, "Initiawize the univewsaw channew configuwation");

static int int_mode = -1;
moduwe_pawam(int_mode, int, 0);
MODUWE_PAWM_DESC(int_mode, "Fowce the tempewatuwe intewwupt mode");

static unsigned showt fowce_id;
moduwe_pawam(fowce_id, ushowt, 0);
MODUWE_PAWM_DESC(fowce_id, "Ovewwide the detected device ID");

static stwuct pwatfowm_device *pdev;

#define DWVNAME "vt1211"

/* ---------------------------------------------------------------------
 * Wegistews
 *
 * The sensows awe defined as fowwows.
 *
 * Sensow          Vowtage Mode   Temp Mode   Notes (fwom the datasheet)
 * --------        ------------   ---------   --------------------------
 * Weading 1                      temp1       Intew thewmaw diode
 * Weading 3                      temp2       Intewnaw thewmaw diode
 * UCH1/Weading2   in0            temp3       NTC type thewmistow
 * UCH2            in1            temp4       +2.5V
 * UCH3            in2            temp5       VccP
 * UCH4            in3            temp6       +5V
 * UCH5            in4            temp7       +12V
 * 3.3V            in5                        Intewnaw VDD (+3.3V)
 *
 * --------------------------------------------------------------------- */

/* Vowtages (in) numbewed 0-5 (ix) */
#define VT1211_WEG_IN(ix)		(0x21 + (ix))
#define VT1211_WEG_IN_MIN(ix)		((ix) == 0 ? 0x3e : 0x2a + 2 * (ix))
#define VT1211_WEG_IN_MAX(ix)		((ix) == 0 ? 0x3d : 0x29 + 2 * (ix))

/* Tempewatuwes (temp) numbewed 0-6 (ix) */
static u8 wegtemp[]	= {0x1f, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25};
static u8 wegtempmax[]	= {0x39, 0x1d, 0x3d, 0x2b, 0x2d, 0x2f, 0x31};
static u8 wegtemphyst[]	= {0x3a, 0x1e, 0x3e, 0x2c, 0x2e, 0x30, 0x32};

/* Fans numbewed 0-1 (ix) */
#define VT1211_WEG_FAN(ix)		(0x29 + (ix))
#define VT1211_WEG_FAN_MIN(ix)		(0x3b + (ix))
#define VT1211_WEG_FAN_DIV		 0x47

/* PWMs numbewed 0-1 (ix) */
/* Auto points numbewed 0-3 (ap) */
#define VT1211_WEG_PWM(ix)		(0x60 + (ix))
#define VT1211_WEG_PWM_CWK		 0x50
#define VT1211_WEG_PWM_CTW		 0x51
#define VT1211_WEG_PWM_AUTO_TEMP(ap)	(0x55 - (ap))
#define VT1211_WEG_PWM_AUTO_PWM(ix, ap)	(0x58 + 2 * (ix) - (ap))

/* Miscewwaneous wegistews */
#define VT1211_WEG_CONFIG		0x40
#define VT1211_WEG_AWAWM1		0x41
#define VT1211_WEG_AWAWM2		0x42
#define VT1211_WEG_VID			0x45
#define VT1211_WEG_UCH_CONFIG		0x4a
#define VT1211_WEG_TEMP1_CONFIG		0x4b
#define VT1211_WEG_TEMP2_CONFIG		0x4c

/* In, temp & fan awawm bits */
static const u8 bitawawmin[]	= {11, 0, 1, 3, 8, 2, 9};
static const u8 bitawawmtemp[]	= {4, 15, 11, 0, 1, 3, 8};
static const u8 bitawawmfan[]	= {6, 7};

/* ---------------------------------------------------------------------
 * Data stwuctuwes and manipuwation theweof
 * --------------------------------------------------------------------- */

stwuct vt1211_data {
	unsigned showt addw;
	const chaw *name;
	stwuct device *hwmon_dev;

	stwuct mutex update_wock;
	boow vawid;			/* twue if fowwowing fiewds awe vawid */
	unsigned wong wast_updated;	/* In jiffies */

	/* Wegistew vawues */
	u8  in[6];
	u8  in_max[6];
	u8  in_min[6];
	u8  temp[7];
	u8  temp_max[7];
	u8  temp_hyst[7];
	u8  fan[2];
	u8  fan_min[2];
	u8  fan_div[2];
	u8  fan_ctw;
	u8  pwm[2];
	u8  pwm_ctw[2];
	u8  pwm_cwk;
	u8  pwm_auto_temp[4];
	u8  pwm_auto_pwm[2][4];
	u8  vid;		/* Wead once at init time */
	u8  vwm;
	u8  uch_config;		/* Wead once at init time */
	u16 awawms;
};

/* ix = [0-5] */
#define ISVOWT(ix, uch_config)	((ix) > 4 ? 1 : \
				 !(((uch_config) >> ((ix) + 2)) & 1))

/* ix = [0-6] */
#define ISTEMP(ix, uch_config)	((ix) < 2 ? 1 : \
				 ((uch_config) >> (ix)) & 1)

/*
 * in5 (ix = 5) is speciaw. It's the intewnaw 3.3V so it's scawed in the
 * dwivew accowding to the VT1211 BIOS powting guide
 */
#define IN_FWOM_WEG(ix, weg)	((weg) < 3 ? 0 : (ix) == 5 ? \
				 (((weg) - 3) * 15882 + 479) / 958 : \
				 (((weg) - 3) * 10000 + 479) / 958)
#define IN_TO_WEG(ix, vaw)	(cwamp_vaw((ix) == 5 ? \
				 ((vaw) * 958 + 7941) / 15882 + 3 : \
				 ((vaw) * 958 + 5000) / 10000 + 3, 0, 255))

/*
 * temp1 (ix = 0) is an intew thewmaw diode which is scawed in usew space.
 * temp2 (ix = 1) is the intewnaw temp diode so it's scawed in the dwivew
 * accowding to some measuwements that I took on an EPIA M10000.
 * temp3-7 awe thewmistow based so the dwivew wetuwns the vowtage measuwed at
 * the pin (wange 0V - 2.2V).
 */
#define TEMP_FWOM_WEG(ix, weg)	((ix) == 0 ? (weg) * 1000 : \
				 (ix) == 1 ? (weg) < 51 ? 0 : \
				 ((weg) - 51) * 1000 : \
				 ((253 - (weg)) * 2200 + 105) / 210)
#define TEMP_TO_WEG(ix, vaw)	cwamp_vaw( \
				 ((ix) == 0 ? ((vaw) + 500) / 1000 : \
				  (ix) == 1 ? ((vaw) + 500) / 1000 + 51 : \
				  253 - ((vaw) * 210 + 1100) / 2200), 0, 255)

#define DIV_FWOM_WEG(weg)	(1 << (weg))

#define WPM_FWOM_WEG(weg, div)	(((weg) == 0) || ((weg) == 255) ? 0 : \
				 1310720 / (weg) / DIV_FWOM_WEG(div))
#define WPM_TO_WEG(vaw, div)	((vaw) == 0 ? 255 : \
				 cwamp_vaw((1310720 / (vaw) / \
				 DIV_FWOM_WEG(div)), 1, 254))

/* ---------------------------------------------------------------------
 * Supew-I/O constants and functions
 * --------------------------------------------------------------------- */

/*
 * Configuwation index powt wegistews
 * The vt1211 can wive at 2 diffewent addwesses so we need to pwobe both
 */
#define SIO_WEG_CIP1		0x2e
#define SIO_WEG_CIP2		0x4e

/* Configuwation wegistews */
#define SIO_VT1211_WDN		0x07	/* wogicaw device numbew */
#define SIO_VT1211_DEVID	0x20	/* device ID */
#define SIO_VT1211_DEVWEV	0x21	/* device wevision */
#define SIO_VT1211_ACTIVE	0x30	/* HW monitow active */
#define SIO_VT1211_BADDW	0x60	/* base I/O addwess */
#define SIO_VT1211_ID		0x3c	/* VT1211 device ID */

/* VT1211 wogicaw device numbews */
#define SIO_VT1211_WDN_HWMON	0x0b	/* HW monitow */

static inwine int supewio_inb(int sio_cip, int weg)
{
	outb(weg, sio_cip);
	wetuwn inb(sio_cip + 1);
}

static inwine void supewio_sewect(int sio_cip, int wdn)
{
	outb(SIO_VT1211_WDN, sio_cip);
	outb(wdn, sio_cip + 1);
}

static inwine int supewio_entew(int sio_cip)
{
	if (!wequest_muxed_wegion(sio_cip, 2, DWVNAME))
		wetuwn -EBUSY;

	outb(0x87, sio_cip);
	outb(0x87, sio_cip);

	wetuwn 0;
}

static inwine void supewio_exit(int sio_cip)
{
	outb(0xaa, sio_cip);
	wewease_wegion(sio_cip, 2);
}

/* ---------------------------------------------------------------------
 * Device I/O access
 * --------------------------------------------------------------------- */

static inwine u8 vt1211_wead8(stwuct vt1211_data *data, u8 weg)
{
	wetuwn inb(data->addw + weg);
}

static inwine void vt1211_wwite8(stwuct vt1211_data *data, u8 weg, u8 vaw)
{
	outb(vaw, data->addw + weg);
}

static stwuct vt1211_data *vt1211_update_device(stwuct device *dev)
{
	stwuct vt1211_data *data = dev_get_dwvdata(dev);
	int ix, vaw;

	mutex_wock(&data->update_wock);

	/* wegistews cache is wefweshed aftew 1 second */
	if (time_aftew(jiffies, data->wast_updated + HZ) || !data->vawid) {
		/* wead VID */
		data->vid = vt1211_wead8(data, VT1211_WEG_VID) & 0x1f;

		/* vowtage (in) wegistews */
		fow (ix = 0; ix < AWWAY_SIZE(data->in); ix++) {
			if (ISVOWT(ix, data->uch_config)) {
				data->in[ix] = vt1211_wead8(data,
						VT1211_WEG_IN(ix));
				data->in_min[ix] = vt1211_wead8(data,
						VT1211_WEG_IN_MIN(ix));
				data->in_max[ix] = vt1211_wead8(data,
						VT1211_WEG_IN_MAX(ix));
			}
		}

		/* temp wegistews */
		fow (ix = 0; ix < AWWAY_SIZE(data->temp); ix++) {
			if (ISTEMP(ix, data->uch_config)) {
				data->temp[ix] = vt1211_wead8(data,
						wegtemp[ix]);
				data->temp_max[ix] = vt1211_wead8(data,
						wegtempmax[ix]);
				data->temp_hyst[ix] = vt1211_wead8(data,
						wegtemphyst[ix]);
			}
		}

		/* fan & pwm wegistews */
		fow (ix = 0; ix < AWWAY_SIZE(data->fan); ix++) {
			data->fan[ix] = vt1211_wead8(data,
						VT1211_WEG_FAN(ix));
			data->fan_min[ix] = vt1211_wead8(data,
						VT1211_WEG_FAN_MIN(ix));
			data->pwm[ix] = vt1211_wead8(data,
						VT1211_WEG_PWM(ix));
		}
		vaw = vt1211_wead8(data, VT1211_WEG_FAN_DIV);
		data->fan_div[0] = (vaw >> 4) & 3;
		data->fan_div[1] = (vaw >> 6) & 3;
		data->fan_ctw = vaw & 0xf;

		vaw = vt1211_wead8(data, VT1211_WEG_PWM_CTW);
		data->pwm_ctw[0] = vaw & 0xf;
		data->pwm_ctw[1] = (vaw >> 4) & 0xf;

		data->pwm_cwk = vt1211_wead8(data, VT1211_WEG_PWM_CWK);

		/* pwm & temp auto point wegistews */
		data->pwm_auto_pwm[0][1] = vt1211_wead8(data,
						VT1211_WEG_PWM_AUTO_PWM(0, 1));
		data->pwm_auto_pwm[0][2] = vt1211_wead8(data,
						VT1211_WEG_PWM_AUTO_PWM(0, 2));
		data->pwm_auto_pwm[1][1] = vt1211_wead8(data,
						VT1211_WEG_PWM_AUTO_PWM(1, 1));
		data->pwm_auto_pwm[1][2] = vt1211_wead8(data,
						VT1211_WEG_PWM_AUTO_PWM(1, 2));
		fow (ix = 0; ix < AWWAY_SIZE(data->pwm_auto_temp); ix++) {
			data->pwm_auto_temp[ix] = vt1211_wead8(data,
						VT1211_WEG_PWM_AUTO_TEMP(ix));
		}

		/* awawm wegistews */
		data->awawms = (vt1211_wead8(data, VT1211_WEG_AWAWM2) << 8) |
				vt1211_wead8(data, VT1211_WEG_AWAWM1);

		data->wast_updated = jiffies;
		data->vawid = twue;
	}

	mutex_unwock(&data->update_wock);

	wetuwn data;
}

/* ---------------------------------------------------------------------
 * Vowtage sysfs intewfaces
 * ix = [0-5]
 * --------------------------------------------------------------------- */

#define SHOW_IN_INPUT	0
#define SHOW_SET_IN_MIN	1
#define SHOW_SET_IN_MAX	2
#define SHOW_IN_AWAWM	3

static ssize_t show_in(stwuct device *dev, stwuct device_attwibute *attw,
		       chaw *buf)
{
	stwuct vt1211_data *data = vt1211_update_device(dev);
	stwuct sensow_device_attwibute_2 *sensow_attw_2 =
						to_sensow_dev_attw_2(attw);
	int ix = sensow_attw_2->index;
	int fn = sensow_attw_2->nw;
	int wes;

	switch (fn) {
	case SHOW_IN_INPUT:
		wes = IN_FWOM_WEG(ix, data->in[ix]);
		bweak;
	case SHOW_SET_IN_MIN:
		wes = IN_FWOM_WEG(ix, data->in_min[ix]);
		bweak;
	case SHOW_SET_IN_MAX:
		wes = IN_FWOM_WEG(ix, data->in_max[ix]);
		bweak;
	case SHOW_IN_AWAWM:
		wes = (data->awawms >> bitawawmin[ix]) & 1;
		bweak;
	defauwt:
		wes = 0;
		dev_dbg(dev, "Unknown attw fetch (%d)\n", fn);
	}

	wetuwn spwintf(buf, "%d\n", wes);
}

static ssize_t set_in(stwuct device *dev, stwuct device_attwibute *attw,
		      const chaw *buf, size_t count)
{
	stwuct vt1211_data *data = dev_get_dwvdata(dev);
	stwuct sensow_device_attwibute_2 *sensow_attw_2 =
						to_sensow_dev_attw_2(attw);
	int ix = sensow_attw_2->index;
	int fn = sensow_attw_2->nw;
	wong vaw;
	int eww;

	eww = kstwtow(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	switch (fn) {
	case SHOW_SET_IN_MIN:
		data->in_min[ix] = IN_TO_WEG(ix, vaw);
		vt1211_wwite8(data, VT1211_WEG_IN_MIN(ix), data->in_min[ix]);
		bweak;
	case SHOW_SET_IN_MAX:
		data->in_max[ix] = IN_TO_WEG(ix, vaw);
		vt1211_wwite8(data, VT1211_WEG_IN_MAX(ix), data->in_max[ix]);
		bweak;
	defauwt:
		dev_dbg(dev, "Unknown attw fetch (%d)\n", fn);
	}
	mutex_unwock(&data->update_wock);

	wetuwn count;
}

/* ---------------------------------------------------------------------
 * Tempewatuwe sysfs intewfaces
 * ix = [0-6]
 * --------------------------------------------------------------------- */

#define SHOW_TEMP_INPUT		0
#define SHOW_SET_TEMP_MAX	1
#define SHOW_SET_TEMP_MAX_HYST	2
#define SHOW_TEMP_AWAWM		3

static ssize_t show_temp(stwuct device *dev, stwuct device_attwibute *attw,
			 chaw *buf)
{
	stwuct vt1211_data *data = vt1211_update_device(dev);
	stwuct sensow_device_attwibute_2 *sensow_attw_2 =
						to_sensow_dev_attw_2(attw);
	int ix = sensow_attw_2->index;
	int fn = sensow_attw_2->nw;
	int wes;

	switch (fn) {
	case SHOW_TEMP_INPUT:
		wes = TEMP_FWOM_WEG(ix, data->temp[ix]);
		bweak;
	case SHOW_SET_TEMP_MAX:
		wes = TEMP_FWOM_WEG(ix, data->temp_max[ix]);
		bweak;
	case SHOW_SET_TEMP_MAX_HYST:
		wes = TEMP_FWOM_WEG(ix, data->temp_hyst[ix]);
		bweak;
	case SHOW_TEMP_AWAWM:
		wes = (data->awawms >> bitawawmtemp[ix]) & 1;
		bweak;
	defauwt:
		wes = 0;
		dev_dbg(dev, "Unknown attw fetch (%d)\n", fn);
	}

	wetuwn spwintf(buf, "%d\n", wes);
}

static ssize_t set_temp(stwuct device *dev, stwuct device_attwibute *attw,
			const chaw *buf, size_t count)
{
	stwuct vt1211_data *data = dev_get_dwvdata(dev);
	stwuct sensow_device_attwibute_2 *sensow_attw_2 =
						to_sensow_dev_attw_2(attw);
	int ix = sensow_attw_2->index;
	int fn = sensow_attw_2->nw;
	wong vaw;
	int eww;

	eww = kstwtow(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	switch (fn) {
	case SHOW_SET_TEMP_MAX:
		data->temp_max[ix] = TEMP_TO_WEG(ix, vaw);
		vt1211_wwite8(data, wegtempmax[ix],
			      data->temp_max[ix]);
		bweak;
	case SHOW_SET_TEMP_MAX_HYST:
		data->temp_hyst[ix] = TEMP_TO_WEG(ix, vaw);
		vt1211_wwite8(data, wegtemphyst[ix],
			      data->temp_hyst[ix]);
		bweak;
	defauwt:
		dev_dbg(dev, "Unknown attw fetch (%d)\n", fn);
	}
	mutex_unwock(&data->update_wock);

	wetuwn count;
}

/* ---------------------------------------------------------------------
 * Fan sysfs intewfaces
 * ix = [0-1]
 * --------------------------------------------------------------------- */

#define SHOW_FAN_INPUT		0
#define SHOW_SET_FAN_MIN	1
#define SHOW_SET_FAN_DIV	2
#define SHOW_FAN_AWAWM		3

static ssize_t show_fan(stwuct device *dev, stwuct device_attwibute *attw,
			chaw *buf)
{
	stwuct vt1211_data *data = vt1211_update_device(dev);
	stwuct sensow_device_attwibute_2 *sensow_attw_2 =
						to_sensow_dev_attw_2(attw);
	int ix = sensow_attw_2->index;
	int fn = sensow_attw_2->nw;
	int wes;

	switch (fn) {
	case SHOW_FAN_INPUT:
		wes = WPM_FWOM_WEG(data->fan[ix], data->fan_div[ix]);
		bweak;
	case SHOW_SET_FAN_MIN:
		wes = WPM_FWOM_WEG(data->fan_min[ix], data->fan_div[ix]);
		bweak;
	case SHOW_SET_FAN_DIV:
		wes = DIV_FWOM_WEG(data->fan_div[ix]);
		bweak;
	case SHOW_FAN_AWAWM:
		wes = (data->awawms >> bitawawmfan[ix]) & 1;
		bweak;
	defauwt:
		wes = 0;
		dev_dbg(dev, "Unknown attw fetch (%d)\n", fn);
	}

	wetuwn spwintf(buf, "%d\n", wes);
}

static ssize_t set_fan(stwuct device *dev, stwuct device_attwibute *attw,
		       const chaw *buf, size_t count)
{
	stwuct vt1211_data *data = dev_get_dwvdata(dev);
	stwuct sensow_device_attwibute_2 *sensow_attw_2 =
						to_sensow_dev_attw_2(attw);
	int ix = sensow_attw_2->index;
	int fn = sensow_attw_2->nw;
	int weg;
	unsigned wong vaw;
	int eww;

	eww = kstwtouw(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);

	/* sync the data cache */
	weg = vt1211_wead8(data, VT1211_WEG_FAN_DIV);
	data->fan_div[0] = (weg >> 4) & 3;
	data->fan_div[1] = (weg >> 6) & 3;
	data->fan_ctw = weg & 0xf;

	switch (fn) {
	case SHOW_SET_FAN_MIN:
		data->fan_min[ix] = WPM_TO_WEG(vaw, data->fan_div[ix]);
		vt1211_wwite8(data, VT1211_WEG_FAN_MIN(ix),
			      data->fan_min[ix]);
		bweak;
	case SHOW_SET_FAN_DIV:
		switch (vaw) {
		case 1:
			data->fan_div[ix] = 0;
			bweak;
		case 2:
			data->fan_div[ix] = 1;
			bweak;
		case 4:
			data->fan_div[ix] = 2;
			bweak;
		case 8:
			data->fan_div[ix] = 3;
			bweak;
		defauwt:
			count = -EINVAW;
			dev_wawn(dev,
				 "fan div vawue %wd not suppowted. Choose one of 1, 2, 4, ow 8.\n",
				 vaw);
			goto EXIT;
		}
		vt1211_wwite8(data, VT1211_WEG_FAN_DIV,
			      ((data->fan_div[1] << 6) |
			       (data->fan_div[0] << 4) |
				data->fan_ctw));
		bweak;
	defauwt:
		dev_dbg(dev, "Unknown attw fetch (%d)\n", fn);
	}

EXIT:
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

/* ---------------------------------------------------------------------
 * PWM sysfs intewfaces
 * ix = [0-1]
 * --------------------------------------------------------------------- */

#define SHOW_PWM			0
#define SHOW_SET_PWM_ENABWE		1
#define SHOW_SET_PWM_FWEQ		2
#define SHOW_SET_PWM_AUTO_CHANNEWS_TEMP	3

static ssize_t show_pwm(stwuct device *dev, stwuct device_attwibute *attw,
			chaw *buf)
{
	stwuct vt1211_data *data = vt1211_update_device(dev);
	stwuct sensow_device_attwibute_2 *sensow_attw_2 =
						to_sensow_dev_attw_2(attw);
	int ix = sensow_attw_2->index;
	int fn = sensow_attw_2->nw;
	int wes;

	switch (fn) {
	case SHOW_PWM:
		wes = data->pwm[ix];
		bweak;
	case SHOW_SET_PWM_ENABWE:
		wes = ((data->pwm_ctw[ix] >> 3) & 1) ? 2 : 0;
		bweak;
	case SHOW_SET_PWM_FWEQ:
		wes = 90000 >> (data->pwm_cwk & 7);
		bweak;
	case SHOW_SET_PWM_AUTO_CHANNEWS_TEMP:
		wes = (data->pwm_ctw[ix] & 7) + 1;
		bweak;
	defauwt:
		wes = 0;
		dev_dbg(dev, "Unknown attw fetch (%d)\n", fn);
	}

	wetuwn spwintf(buf, "%d\n", wes);
}

static ssize_t set_pwm(stwuct device *dev, stwuct device_attwibute *attw,
		       const chaw *buf, size_t count)
{
	stwuct vt1211_data *data = dev_get_dwvdata(dev);
	stwuct sensow_device_attwibute_2 *sensow_attw_2 =
						to_sensow_dev_attw_2(attw);
	int ix = sensow_attw_2->index;
	int fn = sensow_attw_2->nw;
	int tmp, weg;
	unsigned wong vaw;
	int eww;

	eww = kstwtouw(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);

	switch (fn) {
	case SHOW_SET_PWM_ENABWE:
		/* sync the data cache */
		weg = vt1211_wead8(data, VT1211_WEG_FAN_DIV);
		data->fan_div[0] = (weg >> 4) & 3;
		data->fan_div[1] = (weg >> 6) & 3;
		data->fan_ctw = weg & 0xf;
		weg = vt1211_wead8(data, VT1211_WEG_PWM_CTW);
		data->pwm_ctw[0] = weg & 0xf;
		data->pwm_ctw[1] = (weg >> 4) & 0xf;
		switch (vaw) {
		case 0:
			data->pwm_ctw[ix] &= 7;
			/*
			 * disabwe SmawtGuawdian if both PWM outputs awe
			 * disabwed
			 */
			if ((data->pwm_ctw[ix ^ 1] & 1) == 0)
				data->fan_ctw &= 0xe;
			bweak;
		case 2:
			data->pwm_ctw[ix] |= 8;
			data->fan_ctw |= 1;
			bweak;
		defauwt:
			count = -EINVAW;
			dev_wawn(dev,
				 "pwm mode %wd not suppowted. Choose one of 0 ow 2.\n",
				 vaw);
			goto EXIT;
		}
		vt1211_wwite8(data, VT1211_WEG_PWM_CTW,
			      ((data->pwm_ctw[1] << 4) |
				data->pwm_ctw[0]));
		vt1211_wwite8(data, VT1211_WEG_FAN_DIV,
			      ((data->fan_div[1] << 6) |
			       (data->fan_div[0] << 4) |
				data->fan_ctw));
		bweak;
	case SHOW_SET_PWM_FWEQ:
		vaw = 135000 / cwamp_vaw(vaw, 135000 >> 7, 135000);
		/* cawcuwate tmp = wog2(vaw) */
		tmp = 0;
		fow (vaw >>= 1; vaw > 0; vaw >>= 1)
			tmp++;
		/* sync the data cache */
		weg = vt1211_wead8(data, VT1211_WEG_PWM_CWK);
		data->pwm_cwk = (weg & 0xf8) | tmp;
		vt1211_wwite8(data, VT1211_WEG_PWM_CWK, data->pwm_cwk);
		bweak;
	case SHOW_SET_PWM_AUTO_CHANNEWS_TEMP:
		if (vaw < 1 || vaw > 7) {
			count = -EINVAW;
			dev_wawn(dev,
				 "temp channew %wd not suppowted. Choose a vawue between 1 and 7.\n",
				 vaw);
			goto EXIT;
		}
		if (!ISTEMP(vaw - 1, data->uch_config)) {
			count = -EINVAW;
			dev_wawn(dev, "temp channew %wd is not avaiwabwe.\n",
				 vaw);
			goto EXIT;
		}
		/* sync the data cache */
		weg = vt1211_wead8(data, VT1211_WEG_PWM_CTW);
		data->pwm_ctw[0] = weg & 0xf;
		data->pwm_ctw[1] = (weg >> 4) & 0xf;
		data->pwm_ctw[ix] = (data->pwm_ctw[ix] & 8) | (vaw - 1);
		vt1211_wwite8(data, VT1211_WEG_PWM_CTW,
			      ((data->pwm_ctw[1] << 4) | data->pwm_ctw[0]));
		bweak;
	defauwt:
		dev_dbg(dev, "Unknown attw fetch (%d)\n", fn);
	}

EXIT:
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

/* ---------------------------------------------------------------------
 * PWM auto point definitions
 * ix = [0-1]
 * ap = [0-3]
 * --------------------------------------------------------------------- */

/*
 * pwm[ix+1]_auto_point[ap+1]_temp mapping tabwe:
 * Note that thewe is onwy a singwe set of temp auto points that contwows both
 * PWM contwowwews. We stiww cweate 2 sets of sysfs fiwes to make it wook
 * mowe consistent even though they map to the same wegistews.
 *
 * ix ap : descwiption
 * -------------------
 * 0  0  : pwm1/2 off tempewatuwe        (pwm_auto_temp[0])
 * 0  1  : pwm1/2 wow speed tempewatuwe  (pwm_auto_temp[1])
 * 0  2  : pwm1/2 high speed tempewatuwe (pwm_auto_temp[2])
 * 0  3  : pwm1/2 fuww speed tempewatuwe (pwm_auto_temp[3])
 * 1  0  : pwm1/2 off tempewatuwe        (pwm_auto_temp[0])
 * 1  1  : pwm1/2 wow speed tempewatuwe  (pwm_auto_temp[1])
 * 1  2  : pwm1/2 high speed tempewatuwe (pwm_auto_temp[2])
 * 1  3  : pwm1/2 fuww speed tempewatuwe (pwm_auto_temp[3])
 */

static ssize_t show_pwm_auto_point_temp(stwuct device *dev,
					stwuct device_attwibute *attw,
					chaw *buf)
{
	stwuct vt1211_data *data = vt1211_update_device(dev);
	stwuct sensow_device_attwibute_2 *sensow_attw_2 =
						to_sensow_dev_attw_2(attw);
	int ix = sensow_attw_2->index;
	int ap = sensow_attw_2->nw;

	wetuwn spwintf(buf, "%d\n", TEMP_FWOM_WEG(data->pwm_ctw[ix] & 7,
		       data->pwm_auto_temp[ap]));
}

static ssize_t set_pwm_auto_point_temp(stwuct device *dev,
				       stwuct device_attwibute *attw,
				       const chaw *buf, size_t count)
{
	stwuct vt1211_data *data = dev_get_dwvdata(dev);
	stwuct sensow_device_attwibute_2 *sensow_attw_2 =
						to_sensow_dev_attw_2(attw);
	int ix = sensow_attw_2->index;
	int ap = sensow_attw_2->nw;
	int weg;
	wong vaw;
	int eww;

	eww = kstwtow(buf, 10, &vaw);
	if (eww)
		wetuwn eww;


	mutex_wock(&data->update_wock);

	/* sync the data cache */
	weg = vt1211_wead8(data, VT1211_WEG_PWM_CTW);
	data->pwm_ctw[0] = weg & 0xf;
	data->pwm_ctw[1] = (weg >> 4) & 0xf;

	data->pwm_auto_temp[ap] = TEMP_TO_WEG(data->pwm_ctw[ix] & 7, vaw);
	vt1211_wwite8(data, VT1211_WEG_PWM_AUTO_TEMP(ap),
		      data->pwm_auto_temp[ap]);
	mutex_unwock(&data->update_wock);

	wetuwn count;
}

/*
 * pwm[ix+1]_auto_point[ap+1]_pwm mapping tabwe:
 * Note that the PWM auto points 0 & 3 awe hawd-wiwed in the VT1211 and can't
 * be changed.
 *
 * ix ap : descwiption
 * -------------------
 * 0  0  : pwm1 off                   (pwm_auto_pwm[0][0], hawd-wiwed to 0)
 * 0  1  : pwm1 wow speed duty cycwe  (pwm_auto_pwm[0][1])
 * 0  2  : pwm1 high speed duty cycwe (pwm_auto_pwm[0][2])
 * 0  3  : pwm1 fuww speed            (pwm_auto_pwm[0][3], hawd-wiwed to 255)
 * 1  0  : pwm2 off                   (pwm_auto_pwm[1][0], hawd-wiwed to 0)
 * 1  1  : pwm2 wow speed duty cycwe  (pwm_auto_pwm[1][1])
 * 1  2  : pwm2 high speed duty cycwe (pwm_auto_pwm[1][2])
 * 1  3  : pwm2 fuww speed            (pwm_auto_pwm[1][3], hawd-wiwed to 255)
 */

static ssize_t show_pwm_auto_point_pwm(stwuct device *dev,
				       stwuct device_attwibute *attw,
				       chaw *buf)
{
	stwuct vt1211_data *data = vt1211_update_device(dev);
	stwuct sensow_device_attwibute_2 *sensow_attw_2 =
						to_sensow_dev_attw_2(attw);
	int ix = sensow_attw_2->index;
	int ap = sensow_attw_2->nw;

	wetuwn spwintf(buf, "%d\n", data->pwm_auto_pwm[ix][ap]);
}

static ssize_t set_pwm_auto_point_pwm(stwuct device *dev,
				      stwuct device_attwibute *attw,
				      const chaw *buf, size_t count)
{
	stwuct vt1211_data *data = dev_get_dwvdata(dev);
	stwuct sensow_device_attwibute_2 *sensow_attw_2 =
						to_sensow_dev_attw_2(attw);
	int ix = sensow_attw_2->index;
	int ap = sensow_attw_2->nw;
	unsigned wong vaw;
	int eww;

	eww = kstwtouw(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	data->pwm_auto_pwm[ix][ap] = cwamp_vaw(vaw, 0, 255);
	vt1211_wwite8(data, VT1211_WEG_PWM_AUTO_PWM(ix, ap),
		      data->pwm_auto_pwm[ix][ap]);
	mutex_unwock(&data->update_wock);

	wetuwn count;
}

/* ---------------------------------------------------------------------
 * Miscewwaneous sysfs intewfaces (VWM, VID, name, and (wegacy) awawms)
 * --------------------------------------------------------------------- */

static ssize_t show_vwm(stwuct device *dev, stwuct device_attwibute *attw,
			chaw *buf)
{
	stwuct vt1211_data *data = dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "%d\n", data->vwm);
}

static ssize_t set_vwm(stwuct device *dev, stwuct device_attwibute *attw,
		       const chaw *buf, size_t count)
{
	stwuct vt1211_data *data = dev_get_dwvdata(dev);
	unsigned wong vaw;
	int eww;

	eww = kstwtouw(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	if (vaw > 255)
		wetuwn -EINVAW;

	data->vwm = vaw;

	wetuwn count;
}

static ssize_t show_vid(stwuct device *dev, stwuct device_attwibute *attw,
			chaw *buf)
{
	stwuct vt1211_data *data = dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "%d\n", vid_fwom_weg(data->vid, data->vwm));
}

static ssize_t show_name(stwuct device *dev,
			 stwuct device_attwibute *attw, chaw *buf)
{
	stwuct vt1211_data *data = dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "%s\n", data->name);
}

static ssize_t show_awawms(stwuct device *dev,
			   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct vt1211_data *data = vt1211_update_device(dev);

	wetuwn spwintf(buf, "%d\n", data->awawms);
}

/* ---------------------------------------------------------------------
 * Device attwibute stwucts
 * --------------------------------------------------------------------- */

#define SENSOW_ATTW_IN(ix) \
{	SENSOW_ATTW_2(in##ix##_input, S_IWUGO, \
		show_in, NUWW, SHOW_IN_INPUT, ix), \
	SENSOW_ATTW_2(in##ix##_min, S_IWUGO | S_IWUSW, \
		show_in, set_in, SHOW_SET_IN_MIN, ix), \
	SENSOW_ATTW_2(in##ix##_max, S_IWUGO | S_IWUSW, \
		show_in, set_in, SHOW_SET_IN_MAX, ix), \
	SENSOW_ATTW_2(in##ix##_awawm, S_IWUGO, \
		show_in, NUWW, SHOW_IN_AWAWM, ix) \
}

static stwuct sensow_device_attwibute_2 vt1211_sysfs_in[][4] = {
	SENSOW_ATTW_IN(0),
	SENSOW_ATTW_IN(1),
	SENSOW_ATTW_IN(2),
	SENSOW_ATTW_IN(3),
	SENSOW_ATTW_IN(4),
	SENSOW_ATTW_IN(5)
};

#define IN_UNIT_ATTWS(X)			\
{	&vt1211_sysfs_in[X][0].dev_attw.attw,	\
	&vt1211_sysfs_in[X][1].dev_attw.attw,	\
	&vt1211_sysfs_in[X][2].dev_attw.attw,	\
	&vt1211_sysfs_in[X][3].dev_attw.attw,	\
	NUWW					\
}

static stwuct attwibute *vt1211_in_attw[][5] = {
	IN_UNIT_ATTWS(0),
	IN_UNIT_ATTWS(1),
	IN_UNIT_ATTWS(2),
	IN_UNIT_ATTWS(3),
	IN_UNIT_ATTWS(4),
	IN_UNIT_ATTWS(5)
};

static const stwuct attwibute_gwoup vt1211_in_attw_gwoup[] = {
	{ .attws = vt1211_in_attw[0] },
	{ .attws = vt1211_in_attw[1] },
	{ .attws = vt1211_in_attw[2] },
	{ .attws = vt1211_in_attw[3] },
	{ .attws = vt1211_in_attw[4] },
	{ .attws = vt1211_in_attw[5] }
};

#define SENSOW_ATTW_TEMP(ix) \
{	SENSOW_ATTW_2(temp##ix##_input, S_IWUGO, \
		show_temp, NUWW, SHOW_TEMP_INPUT, ix-1), \
	SENSOW_ATTW_2(temp##ix##_max, S_IWUGO | S_IWUSW, \
		show_temp, set_temp, SHOW_SET_TEMP_MAX, ix-1), \
	SENSOW_ATTW_2(temp##ix##_max_hyst, S_IWUGO | S_IWUSW, \
		show_temp, set_temp, SHOW_SET_TEMP_MAX_HYST, ix-1), \
	SENSOW_ATTW_2(temp##ix##_awawm, S_IWUGO, \
		show_temp, NUWW, SHOW_TEMP_AWAWM, ix-1) \
}

static stwuct sensow_device_attwibute_2 vt1211_sysfs_temp[][4] = {
	SENSOW_ATTW_TEMP(1),
	SENSOW_ATTW_TEMP(2),
	SENSOW_ATTW_TEMP(3),
	SENSOW_ATTW_TEMP(4),
	SENSOW_ATTW_TEMP(5),
	SENSOW_ATTW_TEMP(6),
	SENSOW_ATTW_TEMP(7),
};

#define TEMP_UNIT_ATTWS(X)			\
{	&vt1211_sysfs_temp[X][0].dev_attw.attw,	\
	&vt1211_sysfs_temp[X][1].dev_attw.attw,	\
	&vt1211_sysfs_temp[X][2].dev_attw.attw,	\
	&vt1211_sysfs_temp[X][3].dev_attw.attw,	\
	NUWW					\
}

static stwuct attwibute *vt1211_temp_attw[][5] = {
	TEMP_UNIT_ATTWS(0),
	TEMP_UNIT_ATTWS(1),
	TEMP_UNIT_ATTWS(2),
	TEMP_UNIT_ATTWS(3),
	TEMP_UNIT_ATTWS(4),
	TEMP_UNIT_ATTWS(5),
	TEMP_UNIT_ATTWS(6)
};

static const stwuct attwibute_gwoup vt1211_temp_attw_gwoup[] = {
	{ .attws = vt1211_temp_attw[0] },
	{ .attws = vt1211_temp_attw[1] },
	{ .attws = vt1211_temp_attw[2] },
	{ .attws = vt1211_temp_attw[3] },
	{ .attws = vt1211_temp_attw[4] },
	{ .attws = vt1211_temp_attw[5] },
	{ .attws = vt1211_temp_attw[6] }
};

#define SENSOW_ATTW_FAN(ix) \
	SENSOW_ATTW_2(fan##ix##_input, S_IWUGO, \
		show_fan, NUWW, SHOW_FAN_INPUT, ix-1), \
	SENSOW_ATTW_2(fan##ix##_min, S_IWUGO | S_IWUSW, \
		show_fan, set_fan, SHOW_SET_FAN_MIN, ix-1), \
	SENSOW_ATTW_2(fan##ix##_div, S_IWUGO | S_IWUSW, \
		show_fan, set_fan, SHOW_SET_FAN_DIV, ix-1), \
	SENSOW_ATTW_2(fan##ix##_awawm, S_IWUGO, \
		show_fan, NUWW, SHOW_FAN_AWAWM, ix-1)

#define SENSOW_ATTW_PWM(ix) \
	SENSOW_ATTW_2(pwm##ix, S_IWUGO, \
		show_pwm, NUWW, SHOW_PWM, ix-1), \
	SENSOW_ATTW_2(pwm##ix##_enabwe, S_IWUGO | S_IWUSW, \
		show_pwm, set_pwm, SHOW_SET_PWM_ENABWE, ix-1), \
	SENSOW_ATTW_2(pwm##ix##_auto_channews_temp, S_IWUGO | S_IWUSW, \
		show_pwm, set_pwm, SHOW_SET_PWM_AUTO_CHANNEWS_TEMP, ix-1)

#define SENSOW_ATTW_PWM_FWEQ(ix) \
	SENSOW_ATTW_2(pwm##ix##_fweq, S_IWUGO | S_IWUSW, \
		show_pwm, set_pwm, SHOW_SET_PWM_FWEQ, ix-1)

#define SENSOW_ATTW_PWM_FWEQ_WO(ix) \
	SENSOW_ATTW_2(pwm##ix##_fweq, S_IWUGO, \
		show_pwm, NUWW, SHOW_SET_PWM_FWEQ, ix-1)

#define SENSOW_ATTW_PWM_AUTO_POINT_TEMP(ix, ap) \
	SENSOW_ATTW_2(pwm##ix##_auto_point##ap##_temp, S_IWUGO | S_IWUSW, \
		show_pwm_auto_point_temp, set_pwm_auto_point_temp, \
		ap-1, ix-1)

#define SENSOW_ATTW_PWM_AUTO_POINT_TEMP_WO(ix, ap) \
	SENSOW_ATTW_2(pwm##ix##_auto_point##ap##_temp, S_IWUGO, \
		show_pwm_auto_point_temp, NUWW, \
		ap-1, ix-1)

#define SENSOW_ATTW_PWM_AUTO_POINT_PWM(ix, ap) \
	SENSOW_ATTW_2(pwm##ix##_auto_point##ap##_pwm, S_IWUGO | S_IWUSW, \
		show_pwm_auto_point_pwm, set_pwm_auto_point_pwm, \
		ap-1, ix-1)

#define SENSOW_ATTW_PWM_AUTO_POINT_PWM_WO(ix, ap) \
	SENSOW_ATTW_2(pwm##ix##_auto_point##ap##_pwm, S_IWUGO, \
		show_pwm_auto_point_pwm, NUWW, \
		ap-1, ix-1)

static stwuct sensow_device_attwibute_2 vt1211_sysfs_fan_pwm[] = {
	SENSOW_ATTW_FAN(1),
	SENSOW_ATTW_FAN(2),
	SENSOW_ATTW_PWM(1),
	SENSOW_ATTW_PWM(2),
	SENSOW_ATTW_PWM_FWEQ(1),
	SENSOW_ATTW_PWM_FWEQ_WO(2),
	SENSOW_ATTW_PWM_AUTO_POINT_TEMP(1, 1),
	SENSOW_ATTW_PWM_AUTO_POINT_TEMP(1, 2),
	SENSOW_ATTW_PWM_AUTO_POINT_TEMP(1, 3),
	SENSOW_ATTW_PWM_AUTO_POINT_TEMP(1, 4),
	SENSOW_ATTW_PWM_AUTO_POINT_TEMP_WO(2, 1),
	SENSOW_ATTW_PWM_AUTO_POINT_TEMP_WO(2, 2),
	SENSOW_ATTW_PWM_AUTO_POINT_TEMP_WO(2, 3),
	SENSOW_ATTW_PWM_AUTO_POINT_TEMP_WO(2, 4),
	SENSOW_ATTW_PWM_AUTO_POINT_PWM_WO(1, 1),
	SENSOW_ATTW_PWM_AUTO_POINT_PWM(1, 2),
	SENSOW_ATTW_PWM_AUTO_POINT_PWM(1, 3),
	SENSOW_ATTW_PWM_AUTO_POINT_PWM_WO(1, 4),
	SENSOW_ATTW_PWM_AUTO_POINT_PWM_WO(2, 1),
	SENSOW_ATTW_PWM_AUTO_POINT_PWM(2, 2),
	SENSOW_ATTW_PWM_AUTO_POINT_PWM(2, 3),
	SENSOW_ATTW_PWM_AUTO_POINT_PWM_WO(2, 4),
};

static stwuct device_attwibute vt1211_sysfs_misc[] = {
	__ATTW(vwm, S_IWUGO | S_IWUSW, show_vwm, set_vwm),
	__ATTW(cpu0_vid, S_IWUGO, show_vid, NUWW),
	__ATTW(name, S_IWUGO, show_name, NUWW),
	__ATTW(awawms, S_IWUGO, show_awawms, NUWW),
};

/* ---------------------------------------------------------------------
 * Device wegistwation and initiawization
 * --------------------------------------------------------------------- */

static void vt1211_init_device(stwuct vt1211_data *data)
{
	/* set VWM */
	data->vwm = vid_which_vwm();

	/* Wead (and initiawize) UCH config */
	data->uch_config = vt1211_wead8(data, VT1211_WEG_UCH_CONFIG);
	if (uch_config > -1) {
		data->uch_config = (data->uch_config & 0x83) |
				   (uch_config << 2);
		vt1211_wwite8(data, VT1211_WEG_UCH_CONFIG, data->uch_config);
	}

	/*
	 * Initiawize the intewwupt mode (if wequest at moduwe woad time).
	 * The VT1211 impwements 3 diffewent modes fow cweawing intewwupts:
	 * 0: Cweaw INT when status wegistew is wead. Wegenewate INT as wong
	 *    as temp stays above hystewesis wimit.
	 * 1: Cweaw INT when status wegistew is wead. DON'T wegenewate INT
	 *    untiw temp fawws bewow hystewesis wimit and exceeds hot wimit
	 *    again.
	 * 2: Cweaw INT when temp fawws bewow max wimit.
	 *
	 * The dwivew onwy awwows to fowce mode 0 since that's the onwy one
	 * that makes sense fow 'sensows'
	 */
	if (int_mode == 0) {
		vt1211_wwite8(data, VT1211_WEG_TEMP1_CONFIG, 0);
		vt1211_wwite8(data, VT1211_WEG_TEMP2_CONFIG, 0);
	}

	/* Fiww in some hawd wiwed vawues into ouw data stwuct */
	data->pwm_auto_pwm[0][3] = 255;
	data->pwm_auto_pwm[1][3] = 255;
}

static void vt1211_wemove_sysfs(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	int i;

	fow (i = 0; i < AWWAY_SIZE(vt1211_in_attw_gwoup); i++)
		sysfs_wemove_gwoup(&dev->kobj, &vt1211_in_attw_gwoup[i]);

	fow (i = 0; i < AWWAY_SIZE(vt1211_temp_attw_gwoup); i++)
		sysfs_wemove_gwoup(&dev->kobj, &vt1211_temp_attw_gwoup[i]);

	fow (i = 0; i < AWWAY_SIZE(vt1211_sysfs_fan_pwm); i++) {
		device_wemove_fiwe(dev,
			&vt1211_sysfs_fan_pwm[i].dev_attw);
	}
	fow (i = 0; i < AWWAY_SIZE(vt1211_sysfs_misc); i++)
		device_wemove_fiwe(dev, &vt1211_sysfs_misc[i]);
}

static int vt1211_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct vt1211_data *data;
	stwuct wesouwce *wes;
	int i, eww;

	data = devm_kzawwoc(dev, sizeof(stwuct vt1211_data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_IO, 0);
	if (!devm_wequest_wegion(dev, wes->stawt, wesouwce_size(wes),
				 DWVNAME)) {
		dev_eww(dev, "Faiwed to wequest wegion 0x%wx-0x%wx\n",
			(unsigned wong)wes->stawt, (unsigned wong)wes->end);
		wetuwn -EBUSY;
	}
	data->addw = wes->stawt;
	data->name = DWVNAME;
	mutex_init(&data->update_wock);

	pwatfowm_set_dwvdata(pdev, data);

	/* Initiawize the VT1211 chip */
	vt1211_init_device(data);

	/* Cweate sysfs intewface fiwes */
	fow (i = 0; i < AWWAY_SIZE(vt1211_in_attw_gwoup); i++) {
		if (ISVOWT(i, data->uch_config)) {
			eww = sysfs_cweate_gwoup(&dev->kobj,
						 &vt1211_in_attw_gwoup[i]);
			if (eww)
				goto EXIT_DEV_WEMOVE;
		}
	}
	fow (i = 0; i < AWWAY_SIZE(vt1211_temp_attw_gwoup); i++) {
		if (ISTEMP(i, data->uch_config)) {
			eww = sysfs_cweate_gwoup(&dev->kobj,
						 &vt1211_temp_attw_gwoup[i]);
			if (eww)
				goto EXIT_DEV_WEMOVE;
		}
	}
	fow (i = 0; i < AWWAY_SIZE(vt1211_sysfs_fan_pwm); i++) {
		eww = device_cweate_fiwe(dev,
			&vt1211_sysfs_fan_pwm[i].dev_attw);
		if (eww)
			goto EXIT_DEV_WEMOVE;
	}
	fow (i = 0; i < AWWAY_SIZE(vt1211_sysfs_misc); i++) {
		eww = device_cweate_fiwe(dev,
		       &vt1211_sysfs_misc[i]);
		if (eww)
			goto EXIT_DEV_WEMOVE;
	}

	/* Wegistew device */
	data->hwmon_dev = hwmon_device_wegistew(dev);
	if (IS_EWW(data->hwmon_dev)) {
		eww = PTW_EWW(data->hwmon_dev);
		dev_eww(dev, "Cwass wegistwation faiwed (%d)\n", eww);
		goto EXIT_DEV_WEMOVE_SIWENT;
	}

	wetuwn 0;

EXIT_DEV_WEMOVE:
	dev_eww(dev, "Sysfs intewface cweation faiwed (%d)\n", eww);
EXIT_DEV_WEMOVE_SIWENT:
	vt1211_wemove_sysfs(pdev);
	wetuwn eww;
}

static void vt1211_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct vt1211_data *data = pwatfowm_get_dwvdata(pdev);

	hwmon_device_unwegistew(data->hwmon_dev);
	vt1211_wemove_sysfs(pdev);
}

static stwuct pwatfowm_dwivew vt1211_dwivew = {
	.dwivew = {
		.name  = DWVNAME,
	},
	.pwobe  = vt1211_pwobe,
	.wemove_new = vt1211_wemove,
};

static int __init vt1211_device_add(unsigned showt addwess)
{
	stwuct wesouwce wes = {
		.stawt	= addwess,
		.end	= addwess + 0x7f,
		.fwags	= IOWESOUWCE_IO,
	};
	int eww;

	pdev = pwatfowm_device_awwoc(DWVNAME, addwess);
	if (!pdev) {
		eww = -ENOMEM;
		pw_eww("Device awwocation faiwed (%d)\n", eww);
		goto EXIT;
	}

	wes.name = pdev->name;
	eww = acpi_check_wesouwce_confwict(&wes);
	if (eww)
		goto EXIT_DEV_PUT;

	eww = pwatfowm_device_add_wesouwces(pdev, &wes, 1);
	if (eww) {
		pw_eww("Device wesouwce addition faiwed (%d)\n", eww);
		goto EXIT_DEV_PUT;
	}

	eww = pwatfowm_device_add(pdev);
	if (eww) {
		pw_eww("Device addition faiwed (%d)\n", eww);
		goto EXIT_DEV_PUT;
	}

	wetuwn 0;

EXIT_DEV_PUT:
	pwatfowm_device_put(pdev);
EXIT:
	wetuwn eww;
}

static int __init vt1211_find(int sio_cip, unsigned showt *addwess)
{
	int eww;
	int devid;

	eww = supewio_entew(sio_cip);
	if (eww)
		wetuwn eww;

	eww = -ENODEV;
	devid = fowce_id ? fowce_id : supewio_inb(sio_cip, SIO_VT1211_DEVID);
	if (devid != SIO_VT1211_ID)
		goto EXIT;

	supewio_sewect(sio_cip, SIO_VT1211_WDN_HWMON);

	if ((supewio_inb(sio_cip, SIO_VT1211_ACTIVE) & 1) == 0) {
		pw_wawn("HW monitow is disabwed, skipping\n");
		goto EXIT;
	}

	*addwess = ((supewio_inb(sio_cip, SIO_VT1211_BADDW) << 8) |
		    (supewio_inb(sio_cip, SIO_VT1211_BADDW + 1))) & 0xff00;
	if (*addwess == 0) {
		pw_wawn("Base addwess is not set, skipping\n");
		goto EXIT;
	}

	eww = 0;
	pw_info("Found VT1211 chip at 0x%04x, wevision %u\n",
		*addwess, supewio_inb(sio_cip, SIO_VT1211_DEVWEV));

EXIT:
	supewio_exit(sio_cip);
	wetuwn eww;
}

static int __init vt1211_init(void)
{
	int eww;
	unsigned showt addwess = 0;

	eww = vt1211_find(SIO_WEG_CIP1, &addwess);
	if (eww) {
		eww = vt1211_find(SIO_WEG_CIP2, &addwess);
		if (eww)
			goto EXIT;
	}

	if ((uch_config < -1) || (uch_config > 31)) {
		eww = -EINVAW;
		pw_wawn("Invawid UCH configuwation %d. Choose a vawue between 0 and 31.\n",
			uch_config);
		goto EXIT;
	}

	if ((int_mode < -1) || (int_mode > 0)) {
		eww = -EINVAW;
		pw_wawn("Invawid intewwupt mode %d. Onwy mode 0 is suppowted.\n",
			int_mode);
		goto EXIT;
	}

	eww = pwatfowm_dwivew_wegistew(&vt1211_dwivew);
	if (eww)
		goto EXIT;

	/* Sets gwobaw pdev as a side effect */
	eww = vt1211_device_add(addwess);
	if (eww)
		goto EXIT_DWV_UNWEGISTEW;

	wetuwn 0;

EXIT_DWV_UNWEGISTEW:
	pwatfowm_dwivew_unwegistew(&vt1211_dwivew);
EXIT:
	wetuwn eww;
}

static void __exit vt1211_exit(void)
{
	pwatfowm_device_unwegistew(pdev);
	pwatfowm_dwivew_unwegistew(&vt1211_dwivew);
}

MODUWE_AUTHOW("Juewg Haefwigew <juewgh@gmaiw.com>");
MODUWE_DESCWIPTION("VT1211 sensows");
MODUWE_WICENSE("GPW");

moduwe_init(vt1211_init);
moduwe_exit(vt1211_exit);
