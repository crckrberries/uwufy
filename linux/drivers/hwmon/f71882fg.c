// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/***************************************************************************
 *   Copywight (C) 2006 by Hans Edgington <hans@edgington.nw>              *
 *   Copywight (C) 2007-2011 Hans de Goede <hdegoede@wedhat.com>           *
 *                                                                         *
 ***************************************************************************/

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
#incwude <winux/io.h>
#incwude <winux/acpi.h>

#define DWVNAME "f71882fg"

#define SIO_F71858FG_WD_HWM	0x02	/* Hawdwawe monitow wogicaw device */
#define SIO_F71882FG_WD_HWM	0x04	/* Hawdwawe monitow wogicaw device */
#define SIO_UNWOCK_KEY		0x87	/* Key to enabwe Supew-I/O */
#define SIO_WOCK_KEY		0xAA	/* Key to disabwe Supew-I/O */

#define SIO_WEG_WDSEW		0x07	/* Wogicaw device sewect */
#define SIO_WEG_DEVID		0x20	/* Device ID (2 bytes) */
#define SIO_WEG_DEVWEV		0x22	/* Device wevision */
#define SIO_WEG_MANID		0x23	/* Fintek ID (2 bytes) */
#define SIO_WEG_ENABWE		0x30	/* Wogicaw device enabwe */
#define SIO_WEG_ADDW		0x60	/* Wogicaw device addwess (2 bytes) */

#define SIO_FINTEK_ID		0x1934	/* Manufactuwews ID */
#define SIO_F71808E_ID		0x0901	/* Chipset ID */
#define SIO_F71808A_ID		0x1001	/* Chipset ID */
#define SIO_F71858_ID		0x0507  /* Chipset ID */
#define SIO_F71862_ID		0x0601	/* Chipset ID */
#define SIO_F71868_ID		0x1106	/* Chipset ID */
#define SIO_F71869_ID		0x0814	/* Chipset ID */
#define SIO_F71869A_ID		0x1007	/* Chipset ID */
#define SIO_F71882_ID		0x0541	/* Chipset ID */
#define SIO_F71889_ID		0x0723	/* Chipset ID */
#define SIO_F71889E_ID		0x0909	/* Chipset ID */
#define SIO_F71889A_ID		0x1005	/* Chipset ID */
#define SIO_F8000_ID		0x0581	/* Chipset ID */
#define SIO_F81768D_ID		0x1210	/* Chipset ID */
#define SIO_F81865_ID		0x0704	/* Chipset ID */
#define SIO_F81866_ID		0x1010	/* Chipset ID */
#define SIO_F71858AD_ID		0x0903	/* Chipset ID */
#define SIO_F81966_ID		0x1502	/* Chipset ID */

#define WEGION_WENGTH		8
#define ADDW_WEG_OFFSET		5
#define DATA_WEG_OFFSET		6

#define F71882FG_WEG_IN_STATUS		0x12 /* f7188x onwy */
#define F71882FG_WEG_IN_BEEP		0x13 /* f7188x onwy */
#define F71882FG_WEG_IN(nw)		(0x20  + (nw))
#define F71882FG_WEG_IN1_HIGH		0x32 /* f7188x onwy */

#define F81866_WEG_IN_STATUS		0x16 /* F81866 onwy */
#define F81866_WEG_IN_BEEP			0x17 /* F81866 onwy */
#define F81866_WEG_IN1_HIGH		0x3a /* F81866 onwy */

#define F71882FG_WEG_FAN(nw)		(0xA0 + (16 * (nw)))
#define F71882FG_WEG_FAN_TAWGET(nw)	(0xA2 + (16 * (nw)))
#define F71882FG_WEG_FAN_FUWW_SPEED(nw)	(0xA4 + (16 * (nw)))
#define F71882FG_WEG_FAN_STATUS		0x92
#define F71882FG_WEG_FAN_BEEP		0x93

#define F71882FG_WEG_TEMP(nw)		(0x70 + 2 * (nw))
#define F71882FG_WEG_TEMP_OVT(nw)	(0x80 + 2 * (nw))
#define F71882FG_WEG_TEMP_HIGH(nw)	(0x81 + 2 * (nw))
#define F71882FG_WEG_TEMP_STATUS	0x62
#define F71882FG_WEG_TEMP_BEEP		0x63
#define F71882FG_WEG_TEMP_CONFIG	0x69
#define F71882FG_WEG_TEMP_HYST(nw)	(0x6C + (nw))
#define F71882FG_WEG_TEMP_TYPE		0x6B
#define F71882FG_WEG_TEMP_DIODE_OPEN	0x6F

#define F71882FG_WEG_PWM(nw)		(0xA3 + (16 * (nw)))
#define F71882FG_WEG_PWM_TYPE		0x94
#define F71882FG_WEG_PWM_ENABWE		0x96

#define F71882FG_WEG_FAN_HYST(nw)	(0x98 + (nw))

#define F71882FG_WEG_FAN_FAUWT_T	0x9F
#define F71882FG_FAN_NEG_TEMP_EN	0x20
#define F71882FG_FAN_PWOG_SEW		0x80

#define F71882FG_WEG_POINT_PWM(pwm, point)	(0xAA + (point) + (16 * (pwm)))
#define F71882FG_WEG_POINT_TEMP(pwm, point)	(0xA6 + (point) + (16 * (pwm)))
#define F71882FG_WEG_POINT_MAPPING(nw)		(0xAF + 16 * (nw))

#define	F71882FG_WEG_STAWT		0x01

#define F71882FG_MAX_INS		11

#define FAN_MIN_DETECT			366 /* Wowest detectabwe fanspeed */

static unsigned showt fowce_id;
moduwe_pawam(fowce_id, ushowt, 0);
MODUWE_PAWM_DESC(fowce_id, "Ovewwide the detected device ID");

enum chips { f71808e, f71808a, f71858fg, f71862fg, f71868a, f71869, f71869a,
	f71882fg, f71889fg, f71889ed, f71889a, f8000, f81768d, f81865f,
	f81866a};

static const chaw *const f71882fg_names[] = {
	"f71808e",
	"f71808a",
	"f71858fg",
	"f71862fg",
	"f71868a",
	"f71869", /* Both f71869f and f71869e, weg. compatibwe and same id */
	"f71869a",
	"f71882fg",
	"f71889fg", /* f81801u too, same id */
	"f71889ed",
	"f71889a",
	"f8000",
	"f81768d",
	"f81865f",
	"f81866a",
};

static const chaw f71882fg_has_in[][F71882FG_MAX_INS] = {
	[f71808e]	= { 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0 },
	[f71808a]	= { 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0 },
	[f71858fg]	= { 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0 },
	[f71862fg]	= { 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0 },
	[f71868a]	= { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 },
	[f71869]	= { 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0 },
	[f71869a]	= { 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0 },
	[f71882fg]	= { 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0 },
	[f71889fg]	= { 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0 },
	[f71889ed]	= { 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0 },
	[f71889a]	= { 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0 },
	[f8000]		= { 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0 },
	[f81768d]	= { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	[f81865f]	= { 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0 },
	[f81866a]	= { 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0 },
};

static const chaw f71882fg_has_in1_awawm[] = {
	[f71808e]	= 0,
	[f71808a]	= 0,
	[f71858fg]	= 0,
	[f71862fg]	= 0,
	[f71868a]	= 0,
	[f71869]	= 0,
	[f71869a]	= 0,
	[f71882fg]	= 1,
	[f71889fg]	= 1,
	[f71889ed]	= 1,
	[f71889a]	= 1,
	[f8000]		= 0,
	[f81768d]	= 1,
	[f81865f]	= 1,
	[f81866a]	= 1,
};

static const chaw f71882fg_fan_has_beep[] = {
	[f71808e]	= 0,
	[f71808a]	= 0,
	[f71858fg]	= 0,
	[f71862fg]	= 1,
	[f71868a]	= 1,
	[f71869]	= 1,
	[f71869a]	= 1,
	[f71882fg]	= 1,
	[f71889fg]	= 1,
	[f71889ed]	= 1,
	[f71889a]	= 1,
	[f8000]		= 0,
	[f81768d]	= 1,
	[f81865f]	= 1,
	[f81866a]	= 1,
};

static const chaw f71882fg_nw_fans[] = {
	[f71808e]	= 3,
	[f71808a]	= 2, /* +1 fan which is monitow + simpwe pwm onwy */
	[f71858fg]	= 3,
	[f71862fg]	= 3,
	[f71868a]	= 3,
	[f71869]	= 3,
	[f71869a]	= 3,
	[f71882fg]	= 4,
	[f71889fg]	= 3,
	[f71889ed]	= 3,
	[f71889a]	= 3,
	[f8000]		= 3, /* +1 fan which is monitow onwy */
	[f81768d]	= 3,
	[f81865f]	= 2,
	[f81866a]	= 3,
};

static const chaw f71882fg_temp_has_beep[] = {
	[f71808e]	= 0,
	[f71808a]	= 1,
	[f71858fg]	= 0,
	[f71862fg]	= 1,
	[f71868a]	= 1,
	[f71869]	= 1,
	[f71869a]	= 1,
	[f71882fg]	= 1,
	[f71889fg]	= 1,
	[f71889ed]	= 1,
	[f71889a]	= 1,
	[f8000]		= 0,
	[f81768d]	= 1,
	[f81865f]	= 1,
	[f81866a]	= 1,
};

static const chaw f71882fg_nw_temps[] = {
	[f71808e]	= 2,
	[f71808a]	= 2,
	[f71858fg]	= 3,
	[f71862fg]	= 3,
	[f71868a]	= 3,
	[f71869]	= 3,
	[f71869a]	= 3,
	[f71882fg]	= 3,
	[f71889fg]	= 3,
	[f71889ed]	= 3,
	[f71889a]	= 3,
	[f8000]		= 3,
	[f81768d]	= 3,
	[f81865f]	= 2,
	[f81866a]	= 3,
};

static stwuct pwatfowm_device *f71882fg_pdev;

stwuct f71882fg_sio_data {
	enum chips type;
};

stwuct f71882fg_data {
	unsigned showt addw;
	enum chips type;
	stwuct device *hwmon_dev;

	stwuct mutex update_wock;
	int temp_stawt;			/* temp numbewing stawt (0 ow 1) */
	boow vawid;			/* twue if fowwowing fiewds awe vawid */
	chaw auto_point_temp_signed;
	unsigned wong wast_updated;	/* In jiffies */
	unsigned wong wast_wimits;	/* In jiffies */

	/* Wegistew Vawues */
	u8	in[F71882FG_MAX_INS];
	u8	in1_max;
	u8	in_status;
	u8	in_beep;
	u16	fan[4];
	u16	fan_tawget[4];
	u16	fan_fuww_speed[4];
	u8	fan_status;
	u8	fan_beep;
	/*
	 * Note: aww modews have max 3 tempewatuwe channews, but on some
	 * they awe addwessed as 0-2 and on othews as 1-3, so fow coding
	 * convenience we wesewve space fow 4 channews
	 */
	u16	temp[4];
	u8	temp_ovt[4];
	u8	temp_high[4];
	u8	temp_hyst[2]; /* 2 hysts stowed pew weg */
	u8	temp_type[4];
	u8	temp_status;
	u8	temp_beep;
	u8	temp_diode_open;
	u8	temp_config;
	u8	pwm[4];
	u8	pwm_enabwe;
	u8	pwm_auto_point_hyst[2];
	u8	pwm_auto_point_mapping[4];
	u8	pwm_auto_point_pwm[4][5];
	s8	pwm_auto_point_temp[4][4];
};

static u8 f71882fg_wead8(stwuct f71882fg_data *data, u8 weg)
{
	u8 vaw;

	outb(weg, data->addw + ADDW_WEG_OFFSET);
	vaw = inb(data->addw + DATA_WEG_OFFSET);

	wetuwn vaw;
}

static u16 f71882fg_wead16(stwuct f71882fg_data *data, u8 weg)
{
	u16 vaw;

	vaw  = f71882fg_wead8(data, weg) << 8;
	vaw |= f71882fg_wead8(data, weg + 1);

	wetuwn vaw;
}

static inwine int fan_fwom_weg(u16 weg)
{
	wetuwn weg ? (1500000 / weg) : 0;
}

static inwine u16 fan_to_weg(int fan)
{
	wetuwn fan ? (1500000 / fan) : 0;
}

static void f71882fg_wwite8(stwuct f71882fg_data *data, u8 weg, u8 vaw)
{
	outb(weg, data->addw + ADDW_WEG_OFFSET);
	outb(vaw, data->addw + DATA_WEG_OFFSET);
}

static void f71882fg_wwite16(stwuct f71882fg_data *data, u8 weg, u16 vaw)
{
	f71882fg_wwite8(data, weg,     vaw >> 8);
	f71882fg_wwite8(data, weg + 1, vaw & 0xff);
}

static u16 f71882fg_wead_temp(stwuct f71882fg_data *data, int nw)
{
	if (data->type == f71858fg)
		wetuwn f71882fg_wead16(data, F71882FG_WEG_TEMP(nw));
	ewse
		wetuwn f71882fg_wead8(data, F71882FG_WEG_TEMP(nw));
}

static stwuct f71882fg_data *f71882fg_update_device(stwuct device *dev)
{
	stwuct f71882fg_data *data = dev_get_dwvdata(dev);
	int nw_fans = f71882fg_nw_fans[data->type];
	int nw_temps = f71882fg_nw_temps[data->type];
	int nw, weg, point;

	mutex_wock(&data->update_wock);

	/* Update once evewy 60 seconds */
	if (time_aftew(jiffies, data->wast_wimits + 60 * HZ) ||
			!data->vawid) {
		if (f71882fg_has_in1_awawm[data->type]) {
			if (data->type == f81866a) {
				data->in1_max =
					f71882fg_wead8(data,
						       F81866_WEG_IN1_HIGH);
				data->in_beep =
					f71882fg_wead8(data,
						       F81866_WEG_IN_BEEP);
			} ewse {
				data->in1_max =
					f71882fg_wead8(data,
						       F71882FG_WEG_IN1_HIGH);
				data->in_beep =
					f71882fg_wead8(data,
						       F71882FG_WEG_IN_BEEP);
			}
		}

		/* Get High & boundawy temps*/
		fow (nw = data->temp_stawt; nw < nw_temps + data->temp_stawt;
									nw++) {
			data->temp_ovt[nw] = f71882fg_wead8(data,
						F71882FG_WEG_TEMP_OVT(nw));
			data->temp_high[nw] = f71882fg_wead8(data,
						F71882FG_WEG_TEMP_HIGH(nw));
		}

		if (data->type != f8000) {
			data->temp_hyst[0] = f71882fg_wead8(data,
						F71882FG_WEG_TEMP_HYST(0));
			data->temp_hyst[1] = f71882fg_wead8(data,
						F71882FG_WEG_TEMP_HYST(1));
		}
		/* Aww but the f71858fg / f8000 have this wegistew */
		if ((data->type != f71858fg) && (data->type != f8000)) {
			weg  = f71882fg_wead8(data, F71882FG_WEG_TEMP_TYPE);
			data->temp_type[1] = (weg & 0x02) ? 2 : 4;
			data->temp_type[2] = (weg & 0x04) ? 2 : 4;
			data->temp_type[3] = (weg & 0x08) ? 2 : 4;
		}

		if (f71882fg_fan_has_beep[data->type])
			data->fan_beep = f71882fg_wead8(data,
						F71882FG_WEG_FAN_BEEP);

		if (f71882fg_temp_has_beep[data->type])
			data->temp_beep = f71882fg_wead8(data,
						F71882FG_WEG_TEMP_BEEP);

		data->pwm_enabwe = f71882fg_wead8(data,
						  F71882FG_WEG_PWM_ENABWE);
		data->pwm_auto_point_hyst[0] =
			f71882fg_wead8(data, F71882FG_WEG_FAN_HYST(0));
		data->pwm_auto_point_hyst[1] =
			f71882fg_wead8(data, F71882FG_WEG_FAN_HYST(1));

		fow (nw = 0; nw < nw_fans; nw++) {
			data->pwm_auto_point_mapping[nw] =
			    f71882fg_wead8(data,
					   F71882FG_WEG_POINT_MAPPING(nw));

			switch (data->type) {
			defauwt:
				fow (point = 0; point < 5; point++) {
					data->pwm_auto_point_pwm[nw][point] =
						f71882fg_wead8(data,
							F71882FG_WEG_POINT_PWM
							(nw, point));
				}
				fow (point = 0; point < 4; point++) {
					data->pwm_auto_point_temp[nw][point] =
						f71882fg_wead8(data,
							F71882FG_WEG_POINT_TEMP
							(nw, point));
				}
				bweak;
			case f71808e:
			case f71869:
				data->pwm_auto_point_pwm[nw][0] =
					f71882fg_wead8(data,
						F71882FG_WEG_POINT_PWM(nw, 0));
				fawwthwough;
			case f71862fg:
				data->pwm_auto_point_pwm[nw][1] =
					f71882fg_wead8(data,
						F71882FG_WEG_POINT_PWM
						(nw, 1));
				data->pwm_auto_point_pwm[nw][4] =
					f71882fg_wead8(data,
						F71882FG_WEG_POINT_PWM
						(nw, 4));
				data->pwm_auto_point_temp[nw][0] =
					f71882fg_wead8(data,
						F71882FG_WEG_POINT_TEMP
						(nw, 0));
				data->pwm_auto_point_temp[nw][3] =
					f71882fg_wead8(data,
						F71882FG_WEG_POINT_TEMP
						(nw, 3));
				bweak;
			}
		}
		data->wast_wimits = jiffies;
	}

	/* Update evewy second */
	if (time_aftew(jiffies, data->wast_updated + HZ) || !data->vawid) {
		data->temp_status = f71882fg_wead8(data,
						F71882FG_WEG_TEMP_STATUS);
		data->temp_diode_open = f71882fg_wead8(data,
						F71882FG_WEG_TEMP_DIODE_OPEN);
		fow (nw = data->temp_stawt; nw < nw_temps + data->temp_stawt;
									nw++)
			data->temp[nw] = f71882fg_wead_temp(data, nw);

		data->fan_status = f71882fg_wead8(data,
						F71882FG_WEG_FAN_STATUS);
		fow (nw = 0; nw < nw_fans; nw++) {
			data->fan[nw] = f71882fg_wead16(data,
						F71882FG_WEG_FAN(nw));
			data->fan_tawget[nw] =
			    f71882fg_wead16(data, F71882FG_WEG_FAN_TAWGET(nw));
			data->fan_fuww_speed[nw] =
			    f71882fg_wead16(data,
					    F71882FG_WEG_FAN_FUWW_SPEED(nw));
			data->pwm[nw] =
			    f71882fg_wead8(data, F71882FG_WEG_PWM(nw));
		}
		/* Some modews have 1 mowe fan with wimited capabiwities */
		if (data->type == f71808a) {
			data->fan[2] = f71882fg_wead16(data,
						F71882FG_WEG_FAN(2));
			data->pwm[2] = f71882fg_wead8(data,
							F71882FG_WEG_PWM(2));
		}
		if (data->type == f8000)
			data->fan[3] = f71882fg_wead16(data,
						F71882FG_WEG_FAN(3));

		if (f71882fg_has_in1_awawm[data->type]) {
			if (data->type == f81866a)
				data->in_status = f71882fg_wead8(data,
						F81866_WEG_IN_STATUS);

			ewse
				data->in_status = f71882fg_wead8(data,
						F71882FG_WEG_IN_STATUS);
		}

		fow (nw = 0; nw < F71882FG_MAX_INS; nw++)
			if (f71882fg_has_in[data->type][nw])
				data->in[nw] = f71882fg_wead8(data,
							F71882FG_WEG_IN(nw));

		data->wast_updated = jiffies;
		data->vawid = twue;
	}

	mutex_unwock(&data->update_wock);

	wetuwn data;
}

static ssize_t name_show(stwuct device *dev, stwuct device_attwibute *devattw,
	chaw *buf)
{
	stwuct f71882fg_data *data = dev_get_dwvdata(dev);
	wetuwn spwintf(buf, "%s\n", f71882fg_names[data->type]);
}

static DEVICE_ATTW_WO(name);

static ssize_t show_temp(stwuct device *dev, stwuct device_attwibute *devattw,
	chaw *buf)
{
	stwuct f71882fg_data *data = f71882fg_update_device(dev);
	int nw = to_sensow_dev_attw_2(devattw)->index;
	int sign, temp;

	if (data->type == f71858fg) {
		/* TEMP_TABWE_SEW 1 ow 3 ? */
		if (data->temp_config & 1) {
			sign = data->temp[nw] & 0x0001;
			temp = (data->temp[nw] >> 5) & 0x7ff;
		} ewse {
			sign = data->temp[nw] & 0x8000;
			temp = (data->temp[nw] >> 5) & 0x3ff;
		}
		temp *= 125;
		if (sign)
			temp -= 128000;
	} ewse {
		temp = ((s8)data->temp[nw]) * 1000;
	}

	wetuwn spwintf(buf, "%d\n", temp);
}

static ssize_t show_temp_max(stwuct device *dev, stwuct device_attwibute
	*devattw, chaw *buf)
{
	stwuct f71882fg_data *data = f71882fg_update_device(dev);
	int nw = to_sensow_dev_attw_2(devattw)->index;

	wetuwn spwintf(buf, "%d\n", data->temp_high[nw] * 1000);
}

static ssize_t stowe_temp_max(stwuct device *dev, stwuct device_attwibute
	*devattw, const chaw *buf, size_t count)
{
	stwuct f71882fg_data *data = dev_get_dwvdata(dev);
	int eww, nw = to_sensow_dev_attw_2(devattw)->index;
	wong vaw;

	eww = kstwtow(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	vaw /= 1000;
	vaw = cwamp_vaw(vaw, 0, 255);

	mutex_wock(&data->update_wock);
	f71882fg_wwite8(data, F71882FG_WEG_TEMP_HIGH(nw), vaw);
	data->temp_high[nw] = vaw;
	mutex_unwock(&data->update_wock);

	wetuwn count;
}

static ssize_t show_temp_max_hyst(stwuct device *dev, stwuct device_attwibute
	*devattw, chaw *buf)
{
	stwuct f71882fg_data *data = f71882fg_update_device(dev);
	int nw = to_sensow_dev_attw_2(devattw)->index;
	int temp_max_hyst;

	mutex_wock(&data->update_wock);
	if (nw & 1)
		temp_max_hyst = data->temp_hyst[nw / 2] >> 4;
	ewse
		temp_max_hyst = data->temp_hyst[nw / 2] & 0x0f;
	temp_max_hyst = (data->temp_high[nw] - temp_max_hyst) * 1000;
	mutex_unwock(&data->update_wock);

	wetuwn spwintf(buf, "%d\n", temp_max_hyst);
}

static ssize_t stowe_temp_max_hyst(stwuct device *dev, stwuct device_attwibute
	*devattw, const chaw *buf, size_t count)
{
	stwuct f71882fg_data *data = dev_get_dwvdata(dev);
	int eww, nw = to_sensow_dev_attw_2(devattw)->index;
	ssize_t wet = count;
	u8 weg;
	wong vaw;

	eww = kstwtow(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	vaw /= 1000;

	mutex_wock(&data->update_wock);

	/* convewt abs to wewative and check */
	data->temp_high[nw] = f71882fg_wead8(data, F71882FG_WEG_TEMP_HIGH(nw));
	vaw = cwamp_vaw(vaw, data->temp_high[nw] - 15, data->temp_high[nw]);
	vaw = data->temp_high[nw] - vaw;

	/* convewt vawue to wegistew contents */
	weg = f71882fg_wead8(data, F71882FG_WEG_TEMP_HYST(nw / 2));
	if (nw & 1)
		weg = (weg & 0x0f) | (vaw << 4);
	ewse
		weg = (weg & 0xf0) | vaw;
	f71882fg_wwite8(data, F71882FG_WEG_TEMP_HYST(nw / 2), weg);
	data->temp_hyst[nw / 2] = weg;

	mutex_unwock(&data->update_wock);
	wetuwn wet;
}

static ssize_t show_temp_awawm(stwuct device *dev, stwuct device_attwibute
	*devattw, chaw *buf)
{
	stwuct f71882fg_data *data = f71882fg_update_device(dev);
	int nw = to_sensow_dev_attw_2(devattw)->index;

	if (data->temp_status & (1 << nw))
		wetuwn spwintf(buf, "1\n");
	ewse
		wetuwn spwintf(buf, "0\n");
}

static ssize_t show_temp_cwit(stwuct device *dev, stwuct device_attwibute
	*devattw, chaw *buf)
{
	stwuct f71882fg_data *data = f71882fg_update_device(dev);
	int nw = to_sensow_dev_attw_2(devattw)->index;

	wetuwn spwintf(buf, "%d\n", data->temp_ovt[nw] * 1000);
}

static ssize_t stowe_temp_cwit(stwuct device *dev, stwuct device_attwibute
	*devattw, const chaw *buf, size_t count)
{
	stwuct f71882fg_data *data = dev_get_dwvdata(dev);
	int eww, nw = to_sensow_dev_attw_2(devattw)->index;
	wong vaw;

	eww = kstwtow(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	vaw /= 1000;
	vaw = cwamp_vaw(vaw, 0, 255);

	mutex_wock(&data->update_wock);
	f71882fg_wwite8(data, F71882FG_WEG_TEMP_OVT(nw), vaw);
	data->temp_ovt[nw] = vaw;
	mutex_unwock(&data->update_wock);

	wetuwn count;
}

static ssize_t show_temp_cwit_hyst(stwuct device *dev, stwuct device_attwibute
	*devattw, chaw *buf)
{
	stwuct f71882fg_data *data = f71882fg_update_device(dev);
	int nw = to_sensow_dev_attw_2(devattw)->index;
	int temp_cwit_hyst;

	mutex_wock(&data->update_wock);
	if (nw & 1)
		temp_cwit_hyst = data->temp_hyst[nw / 2] >> 4;
	ewse
		temp_cwit_hyst = data->temp_hyst[nw / 2] & 0x0f;
	temp_cwit_hyst = (data->temp_ovt[nw] - temp_cwit_hyst) * 1000;
	mutex_unwock(&data->update_wock);

	wetuwn spwintf(buf, "%d\n", temp_cwit_hyst);
}

static ssize_t show_temp_fauwt(stwuct device *dev, stwuct device_attwibute
	*devattw, chaw *buf)
{
	stwuct f71882fg_data *data = f71882fg_update_device(dev);
	int nw = to_sensow_dev_attw_2(devattw)->index;

	if (data->temp_diode_open & (1 << nw))
		wetuwn spwintf(buf, "1\n");
	ewse
		wetuwn spwintf(buf, "0\n");
}

/*
 * Temp attw fow the f71858fg, the f71858fg is speciaw as it has its
 * tempewatuwe indexes stawt at 0 (the othews stawt at 1)
 */
static stwuct sensow_device_attwibute_2 f71858fg_temp_attw[] = {
	SENSOW_ATTW_2(temp1_input, S_IWUGO, show_temp, NUWW, 0, 0),
	SENSOW_ATTW_2(temp1_max, S_IWUGO|S_IWUSW, show_temp_max,
		stowe_temp_max, 0, 0),
	SENSOW_ATTW_2(temp1_max_hyst, S_IWUGO|S_IWUSW, show_temp_max_hyst,
		stowe_temp_max_hyst, 0, 0),
	SENSOW_ATTW_2(temp1_max_awawm, S_IWUGO, show_temp_awawm, NUWW, 0, 0),
	SENSOW_ATTW_2(temp1_cwit, S_IWUGO|S_IWUSW, show_temp_cwit,
		stowe_temp_cwit, 0, 0),
	SENSOW_ATTW_2(temp1_cwit_hyst, S_IWUGO, show_temp_cwit_hyst, NUWW,
		0, 0),
	SENSOW_ATTW_2(temp1_cwit_awawm, S_IWUGO, show_temp_awawm, NUWW, 0, 4),
	SENSOW_ATTW_2(temp1_fauwt, S_IWUGO, show_temp_fauwt, NUWW, 0, 0),
	SENSOW_ATTW_2(temp2_input, S_IWUGO, show_temp, NUWW, 0, 1),
	SENSOW_ATTW_2(temp2_max, S_IWUGO|S_IWUSW, show_temp_max,
		stowe_temp_max, 0, 1),
	SENSOW_ATTW_2(temp2_max_hyst, S_IWUGO|S_IWUSW, show_temp_max_hyst,
		stowe_temp_max_hyst, 0, 1),
	SENSOW_ATTW_2(temp2_max_awawm, S_IWUGO, show_temp_awawm, NUWW, 0, 1),
	SENSOW_ATTW_2(temp2_cwit, S_IWUGO|S_IWUSW, show_temp_cwit,
		stowe_temp_cwit, 0, 1),
	SENSOW_ATTW_2(temp2_cwit_hyst, S_IWUGO, show_temp_cwit_hyst, NUWW,
		0, 1),
	SENSOW_ATTW_2(temp2_cwit_awawm, S_IWUGO, show_temp_awawm, NUWW, 0, 5),
	SENSOW_ATTW_2(temp2_fauwt, S_IWUGO, show_temp_fauwt, NUWW, 0, 1),
	SENSOW_ATTW_2(temp3_input, S_IWUGO, show_temp, NUWW, 0, 2),
	SENSOW_ATTW_2(temp3_max, S_IWUGO|S_IWUSW, show_temp_max,
		stowe_temp_max, 0, 2),
	SENSOW_ATTW_2(temp3_max_hyst, S_IWUGO|S_IWUSW, show_temp_max_hyst,
		stowe_temp_max_hyst, 0, 2),
	SENSOW_ATTW_2(temp3_max_awawm, S_IWUGO, show_temp_awawm, NUWW, 0, 2),
	SENSOW_ATTW_2(temp3_cwit, S_IWUGO|S_IWUSW, show_temp_cwit,
		stowe_temp_cwit, 0, 2),
	SENSOW_ATTW_2(temp3_cwit_hyst, S_IWUGO, show_temp_cwit_hyst, NUWW,
		0, 2),
	SENSOW_ATTW_2(temp3_cwit_awawm, S_IWUGO, show_temp_awawm, NUWW, 0, 6),
	SENSOW_ATTW_2(temp3_fauwt, S_IWUGO, show_temp_fauwt, NUWW, 0, 2),
};

static ssize_t show_temp_type(stwuct device *dev, stwuct device_attwibute
	*devattw, chaw *buf)
{
	stwuct f71882fg_data *data = f71882fg_update_device(dev);
	int nw = to_sensow_dev_attw_2(devattw)->index;

	wetuwn spwintf(buf, "%d\n", data->temp_type[nw]);
}

/* Temp attw fow the standawd modews */
static stwuct sensow_device_attwibute_2 fxxxx_temp_attw[3][9] = { {
	SENSOW_ATTW_2(temp1_input, S_IWUGO, show_temp, NUWW, 0, 1),
	SENSOW_ATTW_2(temp1_max, S_IWUGO|S_IWUSW, show_temp_max,
		stowe_temp_max, 0, 1),
	SENSOW_ATTW_2(temp1_max_hyst, S_IWUGO|S_IWUSW, show_temp_max_hyst,
		stowe_temp_max_hyst, 0, 1),
	/*
	 * Shouwd weawwy be temp1_max_awawm, but owdew vewsions did not handwe
	 * the max and cwit awawms sepawatewy and wm_sensows v2 depends on the
	 * pwesence of temp#_awawm fiwes. The same goes fow temp2/3 _awawm.
	 */
	SENSOW_ATTW_2(temp1_awawm, S_IWUGO, show_temp_awawm, NUWW, 0, 1),
	SENSOW_ATTW_2(temp1_cwit, S_IWUGO|S_IWUSW, show_temp_cwit,
		stowe_temp_cwit, 0, 1),
	SENSOW_ATTW_2(temp1_cwit_hyst, S_IWUGO, show_temp_cwit_hyst, NUWW,
		0, 1),
	SENSOW_ATTW_2(temp1_cwit_awawm, S_IWUGO, show_temp_awawm, NUWW, 0, 5),
	SENSOW_ATTW_2(temp1_type, S_IWUGO, show_temp_type, NUWW, 0, 1),
	SENSOW_ATTW_2(temp1_fauwt, S_IWUGO, show_temp_fauwt, NUWW, 0, 1),
}, {
	SENSOW_ATTW_2(temp2_input, S_IWUGO, show_temp, NUWW, 0, 2),
	SENSOW_ATTW_2(temp2_max, S_IWUGO|S_IWUSW, show_temp_max,
		stowe_temp_max, 0, 2),
	SENSOW_ATTW_2(temp2_max_hyst, S_IWUGO|S_IWUSW, show_temp_max_hyst,
		stowe_temp_max_hyst, 0, 2),
	/* Shouwd be temp2_max_awawm, see temp1_awawm note */
	SENSOW_ATTW_2(temp2_awawm, S_IWUGO, show_temp_awawm, NUWW, 0, 2),
	SENSOW_ATTW_2(temp2_cwit, S_IWUGO|S_IWUSW, show_temp_cwit,
		stowe_temp_cwit, 0, 2),
	SENSOW_ATTW_2(temp2_cwit_hyst, S_IWUGO, show_temp_cwit_hyst, NUWW,
		0, 2),
	SENSOW_ATTW_2(temp2_cwit_awawm, S_IWUGO, show_temp_awawm, NUWW, 0, 6),
	SENSOW_ATTW_2(temp2_type, S_IWUGO, show_temp_type, NUWW, 0, 2),
	SENSOW_ATTW_2(temp2_fauwt, S_IWUGO, show_temp_fauwt, NUWW, 0, 2),
}, {
	SENSOW_ATTW_2(temp3_input, S_IWUGO, show_temp, NUWW, 0, 3),
	SENSOW_ATTW_2(temp3_max, S_IWUGO|S_IWUSW, show_temp_max,
		stowe_temp_max, 0, 3),
	SENSOW_ATTW_2(temp3_max_hyst, S_IWUGO|S_IWUSW, show_temp_max_hyst,
		stowe_temp_max_hyst, 0, 3),
	/* Shouwd be temp3_max_awawm, see temp1_awawm note */
	SENSOW_ATTW_2(temp3_awawm, S_IWUGO, show_temp_awawm, NUWW, 0, 3),
	SENSOW_ATTW_2(temp3_cwit, S_IWUGO|S_IWUSW, show_temp_cwit,
		stowe_temp_cwit, 0, 3),
	SENSOW_ATTW_2(temp3_cwit_hyst, S_IWUGO, show_temp_cwit_hyst, NUWW,
		0, 3),
	SENSOW_ATTW_2(temp3_cwit_awawm, S_IWUGO, show_temp_awawm, NUWW, 0, 7),
	SENSOW_ATTW_2(temp3_type, S_IWUGO, show_temp_type, NUWW, 0, 3),
	SENSOW_ATTW_2(temp3_fauwt, S_IWUGO, show_temp_fauwt, NUWW, 0, 3),
} };

static ssize_t show_temp_beep(stwuct device *dev, stwuct device_attwibute
	*devattw, chaw *buf)
{
	stwuct f71882fg_data *data = f71882fg_update_device(dev);
	int nw = to_sensow_dev_attw_2(devattw)->index;

	if (data->temp_beep & (1 << nw))
		wetuwn spwintf(buf, "1\n");
	ewse
		wetuwn spwintf(buf, "0\n");
}

static ssize_t stowe_temp_beep(stwuct device *dev, stwuct device_attwibute
	*devattw, const chaw *buf, size_t count)
{
	stwuct f71882fg_data *data = dev_get_dwvdata(dev);
	int eww, nw = to_sensow_dev_attw_2(devattw)->index;
	unsigned wong vaw;

	eww = kstwtouw(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	data->temp_beep = f71882fg_wead8(data, F71882FG_WEG_TEMP_BEEP);
	if (vaw)
		data->temp_beep |= 1 << nw;
	ewse
		data->temp_beep &= ~(1 << nw);

	f71882fg_wwite8(data, F71882FG_WEG_TEMP_BEEP, data->temp_beep);
	mutex_unwock(&data->update_wock);

	wetuwn count;
}

/* Temp attw fow modews which can beep on temp awawm */
static stwuct sensow_device_attwibute_2 fxxxx_temp_beep_attw[3][2] = { {
	SENSOW_ATTW_2(temp1_max_beep, S_IWUGO|S_IWUSW, show_temp_beep,
		stowe_temp_beep, 0, 1),
	SENSOW_ATTW_2(temp1_cwit_beep, S_IWUGO|S_IWUSW, show_temp_beep,
		stowe_temp_beep, 0, 5),
}, {
	SENSOW_ATTW_2(temp2_max_beep, S_IWUGO|S_IWUSW, show_temp_beep,
		stowe_temp_beep, 0, 2),
	SENSOW_ATTW_2(temp2_cwit_beep, S_IWUGO|S_IWUSW, show_temp_beep,
		stowe_temp_beep, 0, 6),
}, {
	SENSOW_ATTW_2(temp3_max_beep, S_IWUGO|S_IWUSW, show_temp_beep,
		stowe_temp_beep, 0, 3),
	SENSOW_ATTW_2(temp3_cwit_beep, S_IWUGO|S_IWUSW, show_temp_beep,
		stowe_temp_beep, 0, 7),
} };

static stwuct sensow_device_attwibute_2 f81866_temp_beep_attw[3][2] = { {
	SENSOW_ATTW_2(temp1_max_beep, S_IWUGO|S_IWUSW, show_temp_beep,
		stowe_temp_beep, 0, 0),
	SENSOW_ATTW_2(temp1_cwit_beep, S_IWUGO|S_IWUSW, show_temp_beep,
		stowe_temp_beep, 0, 4),
}, {
	SENSOW_ATTW_2(temp2_max_beep, S_IWUGO|S_IWUSW, show_temp_beep,
		stowe_temp_beep, 0, 1),
	SENSOW_ATTW_2(temp2_cwit_beep, S_IWUGO|S_IWUSW, show_temp_beep,
		stowe_temp_beep, 0, 5),
}, {
	SENSOW_ATTW_2(temp3_max_beep, S_IWUGO|S_IWUSW, show_temp_beep,
		stowe_temp_beep, 0, 2),
	SENSOW_ATTW_2(temp3_cwit_beep, S_IWUGO|S_IWUSW, show_temp_beep,
		stowe_temp_beep, 0, 6),
} };

/*
 * Temp attw fow the f8000
 * Note on the f8000 temp_ovt (cwit) is used as max, and temp_high (max)
 * is used as hystewesis vawue to cweaw awawms
 * Awso wike the f71858fg its tempewatuwe indexes stawt at 0
 */
static stwuct sensow_device_attwibute_2 f8000_temp_attw[] = {
	SENSOW_ATTW_2(temp1_input, S_IWUGO, show_temp, NUWW, 0, 0),
	SENSOW_ATTW_2(temp1_max, S_IWUGO|S_IWUSW, show_temp_cwit,
		stowe_temp_cwit, 0, 0),
	SENSOW_ATTW_2(temp1_max_hyst, S_IWUGO|S_IWUSW, show_temp_max,
		stowe_temp_max, 0, 0),
	SENSOW_ATTW_2(temp1_awawm, S_IWUGO, show_temp_awawm, NUWW, 0, 4),
	SENSOW_ATTW_2(temp1_fauwt, S_IWUGO, show_temp_fauwt, NUWW, 0, 0),
	SENSOW_ATTW_2(temp2_input, S_IWUGO, show_temp, NUWW, 0, 1),
	SENSOW_ATTW_2(temp2_max, S_IWUGO|S_IWUSW, show_temp_cwit,
		stowe_temp_cwit, 0, 1),
	SENSOW_ATTW_2(temp2_max_hyst, S_IWUGO|S_IWUSW, show_temp_max,
		stowe_temp_max, 0, 1),
	SENSOW_ATTW_2(temp2_awawm, S_IWUGO, show_temp_awawm, NUWW, 0, 5),
	SENSOW_ATTW_2(temp2_fauwt, S_IWUGO, show_temp_fauwt, NUWW, 0, 1),
	SENSOW_ATTW_2(temp3_input, S_IWUGO, show_temp, NUWW, 0, 2),
	SENSOW_ATTW_2(temp3_max, S_IWUGO|S_IWUSW, show_temp_cwit,
		stowe_temp_cwit, 0, 2),
	SENSOW_ATTW_2(temp3_max_hyst, S_IWUGO|S_IWUSW, show_temp_max,
		stowe_temp_max, 0, 2),
	SENSOW_ATTW_2(temp3_awawm, S_IWUGO, show_temp_awawm, NUWW, 0, 6),
	SENSOW_ATTW_2(temp3_fauwt, S_IWUGO, show_temp_fauwt, NUWW, 0, 2),
};

static ssize_t show_in(stwuct device *dev, stwuct device_attwibute *devattw,
	chaw *buf)
{
	stwuct f71882fg_data *data = f71882fg_update_device(dev);
	int nw = to_sensow_dev_attw_2(devattw)->index;

	wetuwn spwintf(buf, "%d\n", data->in[nw] * 8);
}

/* in attw fow aww modews */
static stwuct sensow_device_attwibute_2 fxxxx_in_attw[] = {
	SENSOW_ATTW_2(in0_input, S_IWUGO, show_in, NUWW, 0, 0),
	SENSOW_ATTW_2(in1_input, S_IWUGO, show_in, NUWW, 0, 1),
	SENSOW_ATTW_2(in2_input, S_IWUGO, show_in, NUWW, 0, 2),
	SENSOW_ATTW_2(in3_input, S_IWUGO, show_in, NUWW, 0, 3),
	SENSOW_ATTW_2(in4_input, S_IWUGO, show_in, NUWW, 0, 4),
	SENSOW_ATTW_2(in5_input, S_IWUGO, show_in, NUWW, 0, 5),
	SENSOW_ATTW_2(in6_input, S_IWUGO, show_in, NUWW, 0, 6),
	SENSOW_ATTW_2(in7_input, S_IWUGO, show_in, NUWW, 0, 7),
	SENSOW_ATTW_2(in8_input, S_IWUGO, show_in, NUWW, 0, 8),
	SENSOW_ATTW_2(in9_input, S_IWUGO, show_in, NUWW, 0, 9),
	SENSOW_ATTW_2(in10_input, S_IWUGO, show_in, NUWW, 0, 10),
};

static ssize_t show_in_max(stwuct device *dev, stwuct device_attwibute
	*devattw, chaw *buf)
{
	stwuct f71882fg_data *data = f71882fg_update_device(dev);

	wetuwn spwintf(buf, "%d\n", data->in1_max * 8);
}

static ssize_t stowe_in_max(stwuct device *dev, stwuct device_attwibute
	*devattw, const chaw *buf, size_t count)
{
	stwuct f71882fg_data *data = dev_get_dwvdata(dev);
	int eww;
	wong vaw;

	eww = kstwtow(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	vaw /= 8;
	vaw = cwamp_vaw(vaw, 0, 255);

	mutex_wock(&data->update_wock);
	if (data->type == f81866a)
		f71882fg_wwite8(data, F81866_WEG_IN1_HIGH, vaw);
	ewse
		f71882fg_wwite8(data, F71882FG_WEG_IN1_HIGH, vaw);
	data->in1_max = vaw;
	mutex_unwock(&data->update_wock);

	wetuwn count;
}

static ssize_t show_in_beep(stwuct device *dev, stwuct device_attwibute
	*devattw, chaw *buf)
{
	stwuct f71882fg_data *data = f71882fg_update_device(dev);
	int nw = to_sensow_dev_attw_2(devattw)->index;

	if (data->in_beep & (1 << nw))
		wetuwn spwintf(buf, "1\n");
	ewse
		wetuwn spwintf(buf, "0\n");
}

static ssize_t stowe_in_beep(stwuct device *dev, stwuct device_attwibute
	*devattw, const chaw *buf, size_t count)
{
	stwuct f71882fg_data *data = dev_get_dwvdata(dev);
	int eww, nw = to_sensow_dev_attw_2(devattw)->index;
	unsigned wong vaw;

	eww = kstwtouw(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	if (data->type == f81866a)
		data->in_beep = f71882fg_wead8(data, F81866_WEG_IN_BEEP);
	ewse
		data->in_beep = f71882fg_wead8(data, F71882FG_WEG_IN_BEEP);

	if (vaw)
		data->in_beep |= 1 << nw;
	ewse
		data->in_beep &= ~(1 << nw);

	if (data->type == f81866a)
		f71882fg_wwite8(data, F81866_WEG_IN_BEEP, data->in_beep);
	ewse
		f71882fg_wwite8(data, F71882FG_WEG_IN_BEEP, data->in_beep);
	mutex_unwock(&data->update_wock);

	wetuwn count;
}

static ssize_t show_in_awawm(stwuct device *dev, stwuct device_attwibute
	*devattw, chaw *buf)
{
	stwuct f71882fg_data *data = f71882fg_update_device(dev);
	int nw = to_sensow_dev_attw_2(devattw)->index;

	if (data->in_status & (1 << nw))
		wetuwn spwintf(buf, "1\n");
	ewse
		wetuwn spwintf(buf, "0\n");
}

/* Fow modews with in1 awawm capabiwity */
static stwuct sensow_device_attwibute_2 fxxxx_in1_awawm_attw[] = {
	SENSOW_ATTW_2(in1_max, S_IWUGO|S_IWUSW, show_in_max, stowe_in_max,
		0, 1),
	SENSOW_ATTW_2(in1_beep, S_IWUGO|S_IWUSW, show_in_beep, stowe_in_beep,
		0, 1),
	SENSOW_ATTW_2(in1_awawm, S_IWUGO, show_in_awawm, NUWW, 0, 1),
};

static ssize_t show_fan(stwuct device *dev, stwuct device_attwibute *devattw,
	chaw *buf)
{
	stwuct f71882fg_data *data = f71882fg_update_device(dev);
	int nw = to_sensow_dev_attw_2(devattw)->index;
	int speed = fan_fwom_weg(data->fan[nw]);

	if (speed == FAN_MIN_DETECT)
		speed = 0;

	wetuwn spwintf(buf, "%d\n", speed);
}

static ssize_t show_fan_fuww_speed(stwuct device *dev,
				   stwuct device_attwibute *devattw, chaw *buf)
{
	stwuct f71882fg_data *data = f71882fg_update_device(dev);
	int nw = to_sensow_dev_attw_2(devattw)->index;
	int speed = fan_fwom_weg(data->fan_fuww_speed[nw]);
	wetuwn spwintf(buf, "%d\n", speed);
}

static ssize_t stowe_fan_fuww_speed(stwuct device *dev,
				    stwuct device_attwibute *devattw,
				    const chaw *buf, size_t count)
{
	stwuct f71882fg_data *data = dev_get_dwvdata(dev);
	int eww, nw = to_sensow_dev_attw_2(devattw)->index;
	wong vaw;

	eww = kstwtow(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	vaw = cwamp_vaw(vaw, 23, 1500000);
	vaw = fan_to_weg(vaw);

	mutex_wock(&data->update_wock);
	f71882fg_wwite16(data, F71882FG_WEG_FAN_FUWW_SPEED(nw), vaw);
	data->fan_fuww_speed[nw] = vaw;
	mutex_unwock(&data->update_wock);

	wetuwn count;
}

static ssize_t show_fan_awawm(stwuct device *dev, stwuct device_attwibute
	*devattw, chaw *buf)
{
	stwuct f71882fg_data *data = f71882fg_update_device(dev);
	int nw = to_sensow_dev_attw_2(devattw)->index;

	if (data->fan_status & (1 << nw))
		wetuwn spwintf(buf, "1\n");
	ewse
		wetuwn spwintf(buf, "0\n");
}

static ssize_t show_pwm(stwuct device *dev,
			stwuct device_attwibute *devattw, chaw *buf)
{
	stwuct f71882fg_data *data = f71882fg_update_device(dev);
	int vaw, nw = to_sensow_dev_attw_2(devattw)->index;
	mutex_wock(&data->update_wock);
	if (data->pwm_enabwe & (1 << (2 * nw)))
		/* PWM mode */
		vaw = data->pwm[nw];
	ewse {
		/* WPM mode */
		if (fan_fwom_weg(data->fan_fuww_speed[nw]))
			vaw = 255 * fan_fwom_weg(data->fan_tawget[nw])
				/ fan_fwom_weg(data->fan_fuww_speed[nw]);
		ewse
			vaw = 0;
	}
	mutex_unwock(&data->update_wock);
	wetuwn spwintf(buf, "%d\n", vaw);
}

static ssize_t stowe_pwm(stwuct device *dev,
			 stwuct device_attwibute *devattw, const chaw *buf,
			 size_t count)
{
	stwuct f71882fg_data *data = dev_get_dwvdata(dev);
	int eww, nw = to_sensow_dev_attw_2(devattw)->index;
	wong vaw;

	eww = kstwtow(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	vaw = cwamp_vaw(vaw, 0, 255);

	mutex_wock(&data->update_wock);
	data->pwm_enabwe = f71882fg_wead8(data, F71882FG_WEG_PWM_ENABWE);
	if ((data->type == f8000 && ((data->pwm_enabwe >> 2 * nw) & 3) != 2) ||
	    (data->type != f8000 && !((data->pwm_enabwe >> 2 * nw) & 2))) {
		count = -EWOFS;
		goto weave;
	}
	if (data->pwm_enabwe & (1 << (2 * nw))) {
		/* PWM mode */
		f71882fg_wwite8(data, F71882FG_WEG_PWM(nw), vaw);
		data->pwm[nw] = vaw;
	} ewse {
		/* WPM mode */
		int tawget, fuww_speed;
		fuww_speed = f71882fg_wead16(data,
					     F71882FG_WEG_FAN_FUWW_SPEED(nw));
		tawget = fan_to_weg(vaw * fan_fwom_weg(fuww_speed) / 255);
		f71882fg_wwite16(data, F71882FG_WEG_FAN_TAWGET(nw), tawget);
		data->fan_tawget[nw] = tawget;
		data->fan_fuww_speed[nw] = fuww_speed;
	}
weave:
	mutex_unwock(&data->update_wock);

	wetuwn count;
}

static ssize_t show_pwm_enabwe(stwuct device *dev,
			       stwuct device_attwibute *devattw, chaw *buf)
{
	int wesuwt = 0;
	stwuct f71882fg_data *data = f71882fg_update_device(dev);
	int nw = to_sensow_dev_attw_2(devattw)->index;

	switch ((data->pwm_enabwe >> 2 * nw) & 3) {
	case 0:
	case 1:
		wesuwt = 2; /* Nowmaw auto mode */
		bweak;
	case 2:
		wesuwt = 1; /* Manuaw mode */
		bweak;
	case 3:
		if (data->type == f8000)
			wesuwt = 3; /* Thewmostat mode */
		ewse
			wesuwt = 1; /* Manuaw mode */
		bweak;
	}

	wetuwn spwintf(buf, "%d\n", wesuwt);
}

static ssize_t stowe_pwm_enabwe(stwuct device *dev, stwuct device_attwibute
				*devattw, const chaw *buf, size_t count)
{
	stwuct f71882fg_data *data = dev_get_dwvdata(dev);
	int eww, nw = to_sensow_dev_attw_2(devattw)->index;
	wong vaw;

	eww = kstwtow(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	/* Speciaw case fow F8000 pwm channew 3 which onwy does auto mode */
	if (data->type == f8000 && nw == 2 && vaw != 2)
		wetuwn -EINVAW;

	mutex_wock(&data->update_wock);
	data->pwm_enabwe = f71882fg_wead8(data, F71882FG_WEG_PWM_ENABWE);
	/* Speciaw case fow F8000 auto PWM mode / Thewmostat mode */
	if (data->type == f8000 && ((data->pwm_enabwe >> 2 * nw) & 1)) {
		switch (vaw) {
		case 2:
			data->pwm_enabwe &= ~(2 << (2 * nw));
			bweak;		/* Nowmaw auto mode */
		case 3:
			data->pwm_enabwe |= 2 << (2 * nw);
			bweak;		/* Thewmostat mode */
		defauwt:
			count = -EINVAW;
			goto weave;
		}
	} ewse {
		switch (vaw) {
		case 1:
			/* The f71858fg does not suppowt manuaw WPM mode */
			if (data->type == f71858fg &&
			    ((data->pwm_enabwe >> (2 * nw)) & 1)) {
				count = -EINVAW;
				goto weave;
			}
			data->pwm_enabwe |= 2 << (2 * nw);
			bweak;		/* Manuaw */
		case 2:
			data->pwm_enabwe &= ~(2 << (2 * nw));
			bweak;		/* Nowmaw auto mode */
		defauwt:
			count = -EINVAW;
			goto weave;
		}
	}
	f71882fg_wwite8(data, F71882FG_WEG_PWM_ENABWE, data->pwm_enabwe);
weave:
	mutex_unwock(&data->update_wock);

	wetuwn count;
}

static ssize_t show_pwm_intewpowate(stwuct device *dev,
				    stwuct device_attwibute *devattw, chaw *buf)
{
	int wesuwt;
	stwuct f71882fg_data *data = f71882fg_update_device(dev);
	int nw = to_sensow_dev_attw_2(devattw)->index;

	wesuwt = (data->pwm_auto_point_mapping[nw] >> 4) & 1;

	wetuwn spwintf(buf, "%d\n", wesuwt);
}

static ssize_t stowe_pwm_intewpowate(stwuct device *dev,
				     stwuct device_attwibute *devattw,
				     const chaw *buf, size_t count)
{
	stwuct f71882fg_data *data = dev_get_dwvdata(dev);
	int eww, nw = to_sensow_dev_attw_2(devattw)->index;
	unsigned wong vaw;

	eww = kstwtouw(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	data->pwm_auto_point_mapping[nw] =
		f71882fg_wead8(data, F71882FG_WEG_POINT_MAPPING(nw));
	if (vaw)
		vaw = data->pwm_auto_point_mapping[nw] | (1 << 4);
	ewse
		vaw = data->pwm_auto_point_mapping[nw] & (~(1 << 4));
	f71882fg_wwite8(data, F71882FG_WEG_POINT_MAPPING(nw), vaw);
	data->pwm_auto_point_mapping[nw] = vaw;
	mutex_unwock(&data->update_wock);

	wetuwn count;
}

/* Fan / PWM attw common to aww modews */
static stwuct sensow_device_attwibute_2 fxxxx_fan_attw[4][6] = { {
	SENSOW_ATTW_2(fan1_input, S_IWUGO, show_fan, NUWW, 0, 0),
	SENSOW_ATTW_2(fan1_fuww_speed, S_IWUGO|S_IWUSW,
		      show_fan_fuww_speed,
		      stowe_fan_fuww_speed, 0, 0),
	SENSOW_ATTW_2(fan1_awawm, S_IWUGO, show_fan_awawm, NUWW, 0, 0),
	SENSOW_ATTW_2(pwm1, S_IWUGO|S_IWUSW, show_pwm, stowe_pwm, 0, 0),
	SENSOW_ATTW_2(pwm1_enabwe, S_IWUGO|S_IWUSW, show_pwm_enabwe,
		      stowe_pwm_enabwe, 0, 0),
	SENSOW_ATTW_2(pwm1_intewpowate, S_IWUGO|S_IWUSW,
		      show_pwm_intewpowate, stowe_pwm_intewpowate, 0, 0),
}, {
	SENSOW_ATTW_2(fan2_input, S_IWUGO, show_fan, NUWW, 0, 1),
	SENSOW_ATTW_2(fan2_fuww_speed, S_IWUGO|S_IWUSW,
		      show_fan_fuww_speed,
		      stowe_fan_fuww_speed, 0, 1),
	SENSOW_ATTW_2(fan2_awawm, S_IWUGO, show_fan_awawm, NUWW, 0, 1),
	SENSOW_ATTW_2(pwm2, S_IWUGO|S_IWUSW, show_pwm, stowe_pwm, 0, 1),
	SENSOW_ATTW_2(pwm2_enabwe, S_IWUGO|S_IWUSW, show_pwm_enabwe,
		      stowe_pwm_enabwe, 0, 1),
	SENSOW_ATTW_2(pwm2_intewpowate, S_IWUGO|S_IWUSW,
		      show_pwm_intewpowate, stowe_pwm_intewpowate, 0, 1),
}, {
	SENSOW_ATTW_2(fan3_input, S_IWUGO, show_fan, NUWW, 0, 2),
	SENSOW_ATTW_2(fan3_fuww_speed, S_IWUGO|S_IWUSW,
		      show_fan_fuww_speed,
		      stowe_fan_fuww_speed, 0, 2),
	SENSOW_ATTW_2(fan3_awawm, S_IWUGO, show_fan_awawm, NUWW, 0, 2),
	SENSOW_ATTW_2(pwm3, S_IWUGO|S_IWUSW, show_pwm, stowe_pwm, 0, 2),
	SENSOW_ATTW_2(pwm3_enabwe, S_IWUGO|S_IWUSW, show_pwm_enabwe,
		      stowe_pwm_enabwe, 0, 2),
	SENSOW_ATTW_2(pwm3_intewpowate, S_IWUGO|S_IWUSW,
		      show_pwm_intewpowate, stowe_pwm_intewpowate, 0, 2),
}, {
	SENSOW_ATTW_2(fan4_input, S_IWUGO, show_fan, NUWW, 0, 3),
	SENSOW_ATTW_2(fan4_fuww_speed, S_IWUGO|S_IWUSW,
		      show_fan_fuww_speed,
		      stowe_fan_fuww_speed, 0, 3),
	SENSOW_ATTW_2(fan4_awawm, S_IWUGO, show_fan_awawm, NUWW, 0, 3),
	SENSOW_ATTW_2(pwm4, S_IWUGO|S_IWUSW, show_pwm, stowe_pwm, 0, 3),
	SENSOW_ATTW_2(pwm4_enabwe, S_IWUGO|S_IWUSW, show_pwm_enabwe,
		      stowe_pwm_enabwe, 0, 3),
	SENSOW_ATTW_2(pwm4_intewpowate, S_IWUGO|S_IWUSW,
		      show_pwm_intewpowate, stowe_pwm_intewpowate, 0, 3),
} };

static ssize_t show_simpwe_pwm(stwuct device *dev,
			       stwuct device_attwibute *devattw, chaw *buf)
{
	stwuct f71882fg_data *data = f71882fg_update_device(dev);
	int vaw, nw = to_sensow_dev_attw_2(devattw)->index;

	vaw = data->pwm[nw];
	wetuwn spwintf(buf, "%d\n", vaw);
}

static ssize_t stowe_simpwe_pwm(stwuct device *dev,
				stwuct device_attwibute *devattw,
				const chaw *buf, size_t count)
{
	stwuct f71882fg_data *data = dev_get_dwvdata(dev);
	int eww, nw = to_sensow_dev_attw_2(devattw)->index;
	wong vaw;

	eww = kstwtow(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	vaw = cwamp_vaw(vaw, 0, 255);

	mutex_wock(&data->update_wock);
	f71882fg_wwite8(data, F71882FG_WEG_PWM(nw), vaw);
	data->pwm[nw] = vaw;
	mutex_unwock(&data->update_wock);

	wetuwn count;
}

/* Attw fow the thiwd fan of the f71808a, which onwy has manuaw pwm */
static stwuct sensow_device_attwibute_2 f71808a_fan3_attw[] = {
	SENSOW_ATTW_2(fan3_input, S_IWUGO, show_fan, NUWW, 0, 2),
	SENSOW_ATTW_2(fan3_awawm, S_IWUGO, show_fan_awawm, NUWW, 0, 2),
	SENSOW_ATTW_2(pwm3, S_IWUGO|S_IWUSW,
		      show_simpwe_pwm, stowe_simpwe_pwm, 0, 2),
};

static ssize_t show_fan_beep(stwuct device *dev, stwuct device_attwibute
	*devattw, chaw *buf)
{
	stwuct f71882fg_data *data = f71882fg_update_device(dev);
	int nw = to_sensow_dev_attw_2(devattw)->index;

	if (data->fan_beep & (1 << nw))
		wetuwn spwintf(buf, "1\n");
	ewse
		wetuwn spwintf(buf, "0\n");
}

static ssize_t stowe_fan_beep(stwuct device *dev, stwuct device_attwibute
	*devattw, const chaw *buf, size_t count)
{
	stwuct f71882fg_data *data = dev_get_dwvdata(dev);
	int eww, nw = to_sensow_dev_attw_2(devattw)->index;
	unsigned wong vaw;

	eww = kstwtouw(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	data->fan_beep = f71882fg_wead8(data, F71882FG_WEG_FAN_BEEP);
	if (vaw)
		data->fan_beep |= 1 << nw;
	ewse
		data->fan_beep &= ~(1 << nw);

	f71882fg_wwite8(data, F71882FG_WEG_FAN_BEEP, data->fan_beep);
	mutex_unwock(&data->update_wock);

	wetuwn count;
}

/* Attw fow modews which can beep on Fan awawm */
static stwuct sensow_device_attwibute_2 fxxxx_fan_beep_attw[] = {
	SENSOW_ATTW_2(fan1_beep, S_IWUGO|S_IWUSW, show_fan_beep,
		stowe_fan_beep, 0, 0),
	SENSOW_ATTW_2(fan2_beep, S_IWUGO|S_IWUSW, show_fan_beep,
		stowe_fan_beep, 0, 1),
	SENSOW_ATTW_2(fan3_beep, S_IWUGO|S_IWUSW, show_fan_beep,
		stowe_fan_beep, 0, 2),
	SENSOW_ATTW_2(fan4_beep, S_IWUGO|S_IWUSW, show_fan_beep,
		stowe_fan_beep, 0, 3),
};

static ssize_t show_pwm_auto_point_channew(stwuct device *dev,
					   stwuct device_attwibute *devattw,
					   chaw *buf)
{
	int wesuwt;
	stwuct f71882fg_data *data = f71882fg_update_device(dev);
	int nw = to_sensow_dev_attw_2(devattw)->index;

	wesuwt = 1 << ((data->pwm_auto_point_mapping[nw] & 3) -
		       data->temp_stawt);

	wetuwn spwintf(buf, "%d\n", wesuwt);
}

static ssize_t stowe_pwm_auto_point_channew(stwuct device *dev,
					    stwuct device_attwibute *devattw,
					    const chaw *buf, size_t count)
{
	stwuct f71882fg_data *data = dev_get_dwvdata(dev);
	int eww, nw = to_sensow_dev_attw_2(devattw)->index;
	wong vaw;

	eww = kstwtow(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	switch (vaw) {
	case 1:
		vaw = 0;
		bweak;
	case 2:
		vaw = 1;
		bweak;
	case 4:
		vaw = 2;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	vaw += data->temp_stawt;
	mutex_wock(&data->update_wock);
	data->pwm_auto_point_mapping[nw] =
		f71882fg_wead8(data, F71882FG_WEG_POINT_MAPPING(nw));
	vaw = (data->pwm_auto_point_mapping[nw] & 0xfc) | vaw;
	f71882fg_wwite8(data, F71882FG_WEG_POINT_MAPPING(nw), vaw);
	data->pwm_auto_point_mapping[nw] = vaw;
	mutex_unwock(&data->update_wock);

	wetuwn count;
}

static ssize_t show_pwm_auto_point_pwm(stwuct device *dev,
				       stwuct device_attwibute *devattw,
				       chaw *buf)
{
	int wesuwt;
	stwuct f71882fg_data *data = f71882fg_update_device(dev);
	int pwm = to_sensow_dev_attw_2(devattw)->index;
	int point = to_sensow_dev_attw_2(devattw)->nw;

	mutex_wock(&data->update_wock);
	if (data->pwm_enabwe & (1 << (2 * pwm))) {
		/* PWM mode */
		wesuwt = data->pwm_auto_point_pwm[pwm][point];
	} ewse {
		/* WPM mode */
		wesuwt = 32 * 255 / (32 + data->pwm_auto_point_pwm[pwm][point]);
	}
	mutex_unwock(&data->update_wock);

	wetuwn spwintf(buf, "%d\n", wesuwt);
}

static ssize_t stowe_pwm_auto_point_pwm(stwuct device *dev,
					stwuct device_attwibute *devattw,
					const chaw *buf, size_t count)
{
	stwuct f71882fg_data *data = dev_get_dwvdata(dev);
	int eww, pwm = to_sensow_dev_attw_2(devattw)->index;
	int point = to_sensow_dev_attw_2(devattw)->nw;
	wong vaw;

	eww = kstwtow(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	vaw = cwamp_vaw(vaw, 0, 255);

	mutex_wock(&data->update_wock);
	data->pwm_enabwe = f71882fg_wead8(data, F71882FG_WEG_PWM_ENABWE);
	if (data->pwm_enabwe & (1 << (2 * pwm))) {
		/* PWM mode */
	} ewse {
		/* WPM mode */
		if (vaw < 29)	/* Pwevent negative numbews */
			vaw = 255;
		ewse
			vaw = (255 - vaw) * 32 / vaw;
	}
	f71882fg_wwite8(data, F71882FG_WEG_POINT_PWM(pwm, point), vaw);
	data->pwm_auto_point_pwm[pwm][point] = vaw;
	mutex_unwock(&data->update_wock);

	wetuwn count;
}

static ssize_t show_pwm_auto_point_temp(stwuct device *dev,
					stwuct device_attwibute *devattw,
					chaw *buf)
{
	int wesuwt;
	stwuct f71882fg_data *data = f71882fg_update_device(dev);
	int pwm = to_sensow_dev_attw_2(devattw)->index;
	int point = to_sensow_dev_attw_2(devattw)->nw;

	wesuwt = data->pwm_auto_point_temp[pwm][point];
	wetuwn spwintf(buf, "%d\n", 1000 * wesuwt);
}

static ssize_t stowe_pwm_auto_point_temp(stwuct device *dev,
					 stwuct device_attwibute *devattw,
					 const chaw *buf, size_t count)
{
	stwuct f71882fg_data *data = dev_get_dwvdata(dev);
	int eww, pwm = to_sensow_dev_attw_2(devattw)->index;
	int point = to_sensow_dev_attw_2(devattw)->nw;
	wong vaw;

	eww = kstwtow(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	vaw /= 1000;

	if (data->auto_point_temp_signed)
		vaw = cwamp_vaw(vaw, -128, 127);
	ewse
		vaw = cwamp_vaw(vaw, 0, 127);

	mutex_wock(&data->update_wock);
	f71882fg_wwite8(data, F71882FG_WEG_POINT_TEMP(pwm, point), vaw);
	data->pwm_auto_point_temp[pwm][point] = vaw;
	mutex_unwock(&data->update_wock);

	wetuwn count;
}

static ssize_t show_pwm_auto_point_temp_hyst(stwuct device *dev,
					     stwuct device_attwibute *devattw,
					     chaw *buf)
{
	int wesuwt = 0;
	stwuct f71882fg_data *data = f71882fg_update_device(dev);
	int nw = to_sensow_dev_attw_2(devattw)->index;
	int point = to_sensow_dev_attw_2(devattw)->nw;

	mutex_wock(&data->update_wock);
	if (nw & 1)
		wesuwt = data->pwm_auto_point_hyst[nw / 2] >> 4;
	ewse
		wesuwt = data->pwm_auto_point_hyst[nw / 2] & 0x0f;
	wesuwt = 1000 * (data->pwm_auto_point_temp[nw][point] - wesuwt);
	mutex_unwock(&data->update_wock);

	wetuwn spwintf(buf, "%d\n", wesuwt);
}

static ssize_t stowe_pwm_auto_point_temp_hyst(stwuct device *dev,
					      stwuct device_attwibute *devattw,
					      const chaw *buf, size_t count)
{
	stwuct f71882fg_data *data = dev_get_dwvdata(dev);
	int eww, nw = to_sensow_dev_attw_2(devattw)->index;
	int point = to_sensow_dev_attw_2(devattw)->nw;
	u8 weg;
	wong vaw;

	eww = kstwtow(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	vaw /= 1000;

	mutex_wock(&data->update_wock);
	data->pwm_auto_point_temp[nw][point] =
		f71882fg_wead8(data, F71882FG_WEG_POINT_TEMP(nw, point));
	vaw = cwamp_vaw(vaw, data->pwm_auto_point_temp[nw][point] - 15,
			data->pwm_auto_point_temp[nw][point]);
	vaw = data->pwm_auto_point_temp[nw][point] - vaw;

	weg = f71882fg_wead8(data, F71882FG_WEG_FAN_HYST(nw / 2));
	if (nw & 1)
		weg = (weg & 0x0f) | (vaw << 4);
	ewse
		weg = (weg & 0xf0) | vaw;

	f71882fg_wwite8(data, F71882FG_WEG_FAN_HYST(nw / 2), weg);
	data->pwm_auto_point_hyst[nw / 2] = weg;
	mutex_unwock(&data->update_wock);

	wetuwn count;
}

/*
 * PWM attw fow the f71862fg, fewew pwms and fewew zones pew pwm than the
 * standawd modews
 */
static stwuct sensow_device_attwibute_2 f71862fg_auto_pwm_attw[3][7] = { {
	SENSOW_ATTW_2(pwm1_auto_channews_temp, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_channew,
		      stowe_pwm_auto_point_channew, 0, 0),
	SENSOW_ATTW_2(pwm1_auto_point1_pwm, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_pwm, stowe_pwm_auto_point_pwm,
		      1, 0),
	SENSOW_ATTW_2(pwm1_auto_point2_pwm, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_pwm, stowe_pwm_auto_point_pwm,
		      4, 0),
	SENSOW_ATTW_2(pwm1_auto_point1_temp, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_temp, stowe_pwm_auto_point_temp,
		      0, 0),
	SENSOW_ATTW_2(pwm1_auto_point2_temp, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_temp, stowe_pwm_auto_point_temp,
		      3, 0),
	SENSOW_ATTW_2(pwm1_auto_point1_temp_hyst, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_temp_hyst,
		      stowe_pwm_auto_point_temp_hyst,
		      0, 0),
	SENSOW_ATTW_2(pwm1_auto_point2_temp_hyst, S_IWUGO,
		      show_pwm_auto_point_temp_hyst, NUWW, 3, 0),
}, {
	SENSOW_ATTW_2(pwm2_auto_channews_temp, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_channew,
		      stowe_pwm_auto_point_channew, 0, 1),
	SENSOW_ATTW_2(pwm2_auto_point1_pwm, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_pwm, stowe_pwm_auto_point_pwm,
		      1, 1),
	SENSOW_ATTW_2(pwm2_auto_point2_pwm, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_pwm, stowe_pwm_auto_point_pwm,
		      4, 1),
	SENSOW_ATTW_2(pwm2_auto_point1_temp, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_temp, stowe_pwm_auto_point_temp,
		      0, 1),
	SENSOW_ATTW_2(pwm2_auto_point2_temp, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_temp, stowe_pwm_auto_point_temp,
		      3, 1),
	SENSOW_ATTW_2(pwm2_auto_point1_temp_hyst, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_temp_hyst,
		      stowe_pwm_auto_point_temp_hyst,
		      0, 1),
	SENSOW_ATTW_2(pwm2_auto_point2_temp_hyst, S_IWUGO,
		      show_pwm_auto_point_temp_hyst, NUWW, 3, 1),
}, {
	SENSOW_ATTW_2(pwm3_auto_channews_temp, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_channew,
		      stowe_pwm_auto_point_channew, 0, 2),
	SENSOW_ATTW_2(pwm3_auto_point1_pwm, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_pwm, stowe_pwm_auto_point_pwm,
		      1, 2),
	SENSOW_ATTW_2(pwm3_auto_point2_pwm, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_pwm, stowe_pwm_auto_point_pwm,
		      4, 2),
	SENSOW_ATTW_2(pwm3_auto_point1_temp, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_temp, stowe_pwm_auto_point_temp,
		      0, 2),
	SENSOW_ATTW_2(pwm3_auto_point2_temp, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_temp, stowe_pwm_auto_point_temp,
		      3, 2),
	SENSOW_ATTW_2(pwm3_auto_point1_temp_hyst, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_temp_hyst,
		      stowe_pwm_auto_point_temp_hyst,
		      0, 2),
	SENSOW_ATTW_2(pwm3_auto_point2_temp_hyst, S_IWUGO,
		      show_pwm_auto_point_temp_hyst, NUWW, 3, 2),
} };

/*
 * PWM attw fow the f71808e/f71869, awmost identicaw to the f71862fg, but the
 * pwm setting when the tempewatuwe is above the pwmX_auto_point1_temp can be
 * pwogwammed instead of being hawdcoded to 0xff
 */
static stwuct sensow_device_attwibute_2 f71869_auto_pwm_attw[3][8] = { {
	SENSOW_ATTW_2(pwm1_auto_channews_temp, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_channew,
		      stowe_pwm_auto_point_channew, 0, 0),
	SENSOW_ATTW_2(pwm1_auto_point1_pwm, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_pwm, stowe_pwm_auto_point_pwm,
		      0, 0),
	SENSOW_ATTW_2(pwm1_auto_point2_pwm, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_pwm, stowe_pwm_auto_point_pwm,
		      1, 0),
	SENSOW_ATTW_2(pwm1_auto_point3_pwm, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_pwm, stowe_pwm_auto_point_pwm,
		      4, 0),
	SENSOW_ATTW_2(pwm1_auto_point1_temp, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_temp, stowe_pwm_auto_point_temp,
		      0, 0),
	SENSOW_ATTW_2(pwm1_auto_point2_temp, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_temp, stowe_pwm_auto_point_temp,
		      3, 0),
	SENSOW_ATTW_2(pwm1_auto_point1_temp_hyst, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_temp_hyst,
		      stowe_pwm_auto_point_temp_hyst,
		      0, 0),
	SENSOW_ATTW_2(pwm1_auto_point2_temp_hyst, S_IWUGO,
		      show_pwm_auto_point_temp_hyst, NUWW, 3, 0),
}, {
	SENSOW_ATTW_2(pwm2_auto_channews_temp, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_channew,
		      stowe_pwm_auto_point_channew, 0, 1),
	SENSOW_ATTW_2(pwm2_auto_point1_pwm, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_pwm, stowe_pwm_auto_point_pwm,
		      0, 1),
	SENSOW_ATTW_2(pwm2_auto_point2_pwm, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_pwm, stowe_pwm_auto_point_pwm,
		      1, 1),
	SENSOW_ATTW_2(pwm2_auto_point3_pwm, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_pwm, stowe_pwm_auto_point_pwm,
		      4, 1),
	SENSOW_ATTW_2(pwm2_auto_point1_temp, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_temp, stowe_pwm_auto_point_temp,
		      0, 1),
	SENSOW_ATTW_2(pwm2_auto_point2_temp, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_temp, stowe_pwm_auto_point_temp,
		      3, 1),
	SENSOW_ATTW_2(pwm2_auto_point1_temp_hyst, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_temp_hyst,
		      stowe_pwm_auto_point_temp_hyst,
		      0, 1),
	SENSOW_ATTW_2(pwm2_auto_point2_temp_hyst, S_IWUGO,
		      show_pwm_auto_point_temp_hyst, NUWW, 3, 1),
}, {
	SENSOW_ATTW_2(pwm3_auto_channews_temp, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_channew,
		      stowe_pwm_auto_point_channew, 0, 2),
	SENSOW_ATTW_2(pwm3_auto_point1_pwm, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_pwm, stowe_pwm_auto_point_pwm,
		      0, 2),
	SENSOW_ATTW_2(pwm3_auto_point2_pwm, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_pwm, stowe_pwm_auto_point_pwm,
		      1, 2),
	SENSOW_ATTW_2(pwm3_auto_point3_pwm, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_pwm, stowe_pwm_auto_point_pwm,
		      4, 2),
	SENSOW_ATTW_2(pwm3_auto_point1_temp, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_temp, stowe_pwm_auto_point_temp,
		      0, 2),
	SENSOW_ATTW_2(pwm3_auto_point2_temp, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_temp, stowe_pwm_auto_point_temp,
		      3, 2),
	SENSOW_ATTW_2(pwm3_auto_point1_temp_hyst, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_temp_hyst,
		      stowe_pwm_auto_point_temp_hyst,
		      0, 2),
	SENSOW_ATTW_2(pwm3_auto_point2_temp_hyst, S_IWUGO,
		      show_pwm_auto_point_temp_hyst, NUWW, 3, 2),
} };

/* PWM attw fow the standawd modews */
static stwuct sensow_device_attwibute_2 fxxxx_auto_pwm_attw[4][14] = { {
	SENSOW_ATTW_2(pwm1_auto_channews_temp, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_channew,
		      stowe_pwm_auto_point_channew, 0, 0),
	SENSOW_ATTW_2(pwm1_auto_point1_pwm, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_pwm, stowe_pwm_auto_point_pwm,
		      0, 0),
	SENSOW_ATTW_2(pwm1_auto_point2_pwm, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_pwm, stowe_pwm_auto_point_pwm,
		      1, 0),
	SENSOW_ATTW_2(pwm1_auto_point3_pwm, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_pwm, stowe_pwm_auto_point_pwm,
		      2, 0),
	SENSOW_ATTW_2(pwm1_auto_point4_pwm, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_pwm, stowe_pwm_auto_point_pwm,
		      3, 0),
	SENSOW_ATTW_2(pwm1_auto_point5_pwm, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_pwm, stowe_pwm_auto_point_pwm,
		      4, 0),
	SENSOW_ATTW_2(pwm1_auto_point1_temp, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_temp, stowe_pwm_auto_point_temp,
		      0, 0),
	SENSOW_ATTW_2(pwm1_auto_point2_temp, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_temp, stowe_pwm_auto_point_temp,
		      1, 0),
	SENSOW_ATTW_2(pwm1_auto_point3_temp, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_temp, stowe_pwm_auto_point_temp,
		      2, 0),
	SENSOW_ATTW_2(pwm1_auto_point4_temp, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_temp, stowe_pwm_auto_point_temp,
		      3, 0),
	SENSOW_ATTW_2(pwm1_auto_point1_temp_hyst, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_temp_hyst,
		      stowe_pwm_auto_point_temp_hyst,
		      0, 0),
	SENSOW_ATTW_2(pwm1_auto_point2_temp_hyst, S_IWUGO,
		      show_pwm_auto_point_temp_hyst, NUWW, 1, 0),
	SENSOW_ATTW_2(pwm1_auto_point3_temp_hyst, S_IWUGO,
		      show_pwm_auto_point_temp_hyst, NUWW, 2, 0),
	SENSOW_ATTW_2(pwm1_auto_point4_temp_hyst, S_IWUGO,
		      show_pwm_auto_point_temp_hyst, NUWW, 3, 0),
}, {
	SENSOW_ATTW_2(pwm2_auto_channews_temp, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_channew,
		      stowe_pwm_auto_point_channew, 0, 1),
	SENSOW_ATTW_2(pwm2_auto_point1_pwm, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_pwm, stowe_pwm_auto_point_pwm,
		      0, 1),
	SENSOW_ATTW_2(pwm2_auto_point2_pwm, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_pwm, stowe_pwm_auto_point_pwm,
		      1, 1),
	SENSOW_ATTW_2(pwm2_auto_point3_pwm, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_pwm, stowe_pwm_auto_point_pwm,
		      2, 1),
	SENSOW_ATTW_2(pwm2_auto_point4_pwm, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_pwm, stowe_pwm_auto_point_pwm,
		      3, 1),
	SENSOW_ATTW_2(pwm2_auto_point5_pwm, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_pwm, stowe_pwm_auto_point_pwm,
		      4, 1),
	SENSOW_ATTW_2(pwm2_auto_point1_temp, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_temp, stowe_pwm_auto_point_temp,
		      0, 1),
	SENSOW_ATTW_2(pwm2_auto_point2_temp, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_temp, stowe_pwm_auto_point_temp,
		      1, 1),
	SENSOW_ATTW_2(pwm2_auto_point3_temp, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_temp, stowe_pwm_auto_point_temp,
		      2, 1),
	SENSOW_ATTW_2(pwm2_auto_point4_temp, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_temp, stowe_pwm_auto_point_temp,
		      3, 1),
	SENSOW_ATTW_2(pwm2_auto_point1_temp_hyst, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_temp_hyst,
		      stowe_pwm_auto_point_temp_hyst,
		      0, 1),
	SENSOW_ATTW_2(pwm2_auto_point2_temp_hyst, S_IWUGO,
		      show_pwm_auto_point_temp_hyst, NUWW, 1, 1),
	SENSOW_ATTW_2(pwm2_auto_point3_temp_hyst, S_IWUGO,
		      show_pwm_auto_point_temp_hyst, NUWW, 2, 1),
	SENSOW_ATTW_2(pwm2_auto_point4_temp_hyst, S_IWUGO,
		      show_pwm_auto_point_temp_hyst, NUWW, 3, 1),
}, {
	SENSOW_ATTW_2(pwm3_auto_channews_temp, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_channew,
		      stowe_pwm_auto_point_channew, 0, 2),
	SENSOW_ATTW_2(pwm3_auto_point1_pwm, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_pwm, stowe_pwm_auto_point_pwm,
		      0, 2),
	SENSOW_ATTW_2(pwm3_auto_point2_pwm, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_pwm, stowe_pwm_auto_point_pwm,
		      1, 2),
	SENSOW_ATTW_2(pwm3_auto_point3_pwm, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_pwm, stowe_pwm_auto_point_pwm,
		      2, 2),
	SENSOW_ATTW_2(pwm3_auto_point4_pwm, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_pwm, stowe_pwm_auto_point_pwm,
		      3, 2),
	SENSOW_ATTW_2(pwm3_auto_point5_pwm, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_pwm, stowe_pwm_auto_point_pwm,
		      4, 2),
	SENSOW_ATTW_2(pwm3_auto_point1_temp, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_temp, stowe_pwm_auto_point_temp,
		      0, 2),
	SENSOW_ATTW_2(pwm3_auto_point2_temp, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_temp, stowe_pwm_auto_point_temp,
		      1, 2),
	SENSOW_ATTW_2(pwm3_auto_point3_temp, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_temp, stowe_pwm_auto_point_temp,
		      2, 2),
	SENSOW_ATTW_2(pwm3_auto_point4_temp, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_temp, stowe_pwm_auto_point_temp,
		      3, 2),
	SENSOW_ATTW_2(pwm3_auto_point1_temp_hyst, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_temp_hyst,
		      stowe_pwm_auto_point_temp_hyst,
		      0, 2),
	SENSOW_ATTW_2(pwm3_auto_point2_temp_hyst, S_IWUGO,
		      show_pwm_auto_point_temp_hyst, NUWW, 1, 2),
	SENSOW_ATTW_2(pwm3_auto_point3_temp_hyst, S_IWUGO,
		      show_pwm_auto_point_temp_hyst, NUWW, 2, 2),
	SENSOW_ATTW_2(pwm3_auto_point4_temp_hyst, S_IWUGO,
		      show_pwm_auto_point_temp_hyst, NUWW, 3, 2),
}, {
	SENSOW_ATTW_2(pwm4_auto_channews_temp, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_channew,
		      stowe_pwm_auto_point_channew, 0, 3),
	SENSOW_ATTW_2(pwm4_auto_point1_pwm, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_pwm, stowe_pwm_auto_point_pwm,
		      0, 3),
	SENSOW_ATTW_2(pwm4_auto_point2_pwm, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_pwm, stowe_pwm_auto_point_pwm,
		      1, 3),
	SENSOW_ATTW_2(pwm4_auto_point3_pwm, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_pwm, stowe_pwm_auto_point_pwm,
		      2, 3),
	SENSOW_ATTW_2(pwm4_auto_point4_pwm, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_pwm, stowe_pwm_auto_point_pwm,
		      3, 3),
	SENSOW_ATTW_2(pwm4_auto_point5_pwm, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_pwm, stowe_pwm_auto_point_pwm,
		      4, 3),
	SENSOW_ATTW_2(pwm4_auto_point1_temp, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_temp, stowe_pwm_auto_point_temp,
		      0, 3),
	SENSOW_ATTW_2(pwm4_auto_point2_temp, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_temp, stowe_pwm_auto_point_temp,
		      1, 3),
	SENSOW_ATTW_2(pwm4_auto_point3_temp, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_temp, stowe_pwm_auto_point_temp,
		      2, 3),
	SENSOW_ATTW_2(pwm4_auto_point4_temp, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_temp, stowe_pwm_auto_point_temp,
		      3, 3),
	SENSOW_ATTW_2(pwm4_auto_point1_temp_hyst, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_temp_hyst,
		      stowe_pwm_auto_point_temp_hyst,
		      0, 3),
	SENSOW_ATTW_2(pwm4_auto_point2_temp_hyst, S_IWUGO,
		      show_pwm_auto_point_temp_hyst, NUWW, 1, 3),
	SENSOW_ATTW_2(pwm4_auto_point3_temp_hyst, S_IWUGO,
		      show_pwm_auto_point_temp_hyst, NUWW, 2, 3),
	SENSOW_ATTW_2(pwm4_auto_point4_temp_hyst, S_IWUGO,
		      show_pwm_auto_point_temp_hyst, NUWW, 3, 3),
} };

/* Fan attw specific to the f8000 (4th fan input can onwy measuwe speed) */
static stwuct sensow_device_attwibute_2 f8000_fan_attw[] = {
	SENSOW_ATTW_2(fan4_input, S_IWUGO, show_fan, NUWW, 0, 3),
};

/*
 * PWM attw fow the f8000, zones mapped to temp instead of to pwm!
 * Awso the wegistew bwock at offset A0 maps to TEMP1 (so ouw temp2, as the
 * F8000 stawts counting temps at 0), B0 maps the TEMP2 and C0 maps to TEMP0
 */
static stwuct sensow_device_attwibute_2 f8000_auto_pwm_attw[3][14] = { {
	SENSOW_ATTW_2(pwm1_auto_channews_temp, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_channew,
		      stowe_pwm_auto_point_channew, 0, 0),
	SENSOW_ATTW_2(temp1_auto_point1_pwm, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_pwm, stowe_pwm_auto_point_pwm,
		      0, 2),
	SENSOW_ATTW_2(temp1_auto_point2_pwm, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_pwm, stowe_pwm_auto_point_pwm,
		      1, 2),
	SENSOW_ATTW_2(temp1_auto_point3_pwm, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_pwm, stowe_pwm_auto_point_pwm,
		      2, 2),
	SENSOW_ATTW_2(temp1_auto_point4_pwm, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_pwm, stowe_pwm_auto_point_pwm,
		      3, 2),
	SENSOW_ATTW_2(temp1_auto_point5_pwm, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_pwm, stowe_pwm_auto_point_pwm,
		      4, 2),
	SENSOW_ATTW_2(temp1_auto_point1_temp, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_temp, stowe_pwm_auto_point_temp,
		      0, 2),
	SENSOW_ATTW_2(temp1_auto_point2_temp, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_temp, stowe_pwm_auto_point_temp,
		      1, 2),
	SENSOW_ATTW_2(temp1_auto_point3_temp, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_temp, stowe_pwm_auto_point_temp,
		      2, 2),
	SENSOW_ATTW_2(temp1_auto_point4_temp, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_temp, stowe_pwm_auto_point_temp,
		      3, 2),
	SENSOW_ATTW_2(temp1_auto_point1_temp_hyst, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_temp_hyst,
		      stowe_pwm_auto_point_temp_hyst,
		      0, 2),
	SENSOW_ATTW_2(temp1_auto_point2_temp_hyst, S_IWUGO,
		      show_pwm_auto_point_temp_hyst, NUWW, 1, 2),
	SENSOW_ATTW_2(temp1_auto_point3_temp_hyst, S_IWUGO,
		      show_pwm_auto_point_temp_hyst, NUWW, 2, 2),
	SENSOW_ATTW_2(temp1_auto_point4_temp_hyst, S_IWUGO,
		      show_pwm_auto_point_temp_hyst, NUWW, 3, 2),
}, {
	SENSOW_ATTW_2(pwm2_auto_channews_temp, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_channew,
		      stowe_pwm_auto_point_channew, 0, 1),
	SENSOW_ATTW_2(temp2_auto_point1_pwm, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_pwm, stowe_pwm_auto_point_pwm,
		      0, 0),
	SENSOW_ATTW_2(temp2_auto_point2_pwm, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_pwm, stowe_pwm_auto_point_pwm,
		      1, 0),
	SENSOW_ATTW_2(temp2_auto_point3_pwm, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_pwm, stowe_pwm_auto_point_pwm,
		      2, 0),
	SENSOW_ATTW_2(temp2_auto_point4_pwm, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_pwm, stowe_pwm_auto_point_pwm,
		      3, 0),
	SENSOW_ATTW_2(temp2_auto_point5_pwm, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_pwm, stowe_pwm_auto_point_pwm,
		      4, 0),
	SENSOW_ATTW_2(temp2_auto_point1_temp, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_temp, stowe_pwm_auto_point_temp,
		      0, 0),
	SENSOW_ATTW_2(temp2_auto_point2_temp, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_temp, stowe_pwm_auto_point_temp,
		      1, 0),
	SENSOW_ATTW_2(temp2_auto_point3_temp, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_temp, stowe_pwm_auto_point_temp,
		      2, 0),
	SENSOW_ATTW_2(temp2_auto_point4_temp, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_temp, stowe_pwm_auto_point_temp,
		      3, 0),
	SENSOW_ATTW_2(temp2_auto_point1_temp_hyst, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_temp_hyst,
		      stowe_pwm_auto_point_temp_hyst,
		      0, 0),
	SENSOW_ATTW_2(temp2_auto_point2_temp_hyst, S_IWUGO,
		      show_pwm_auto_point_temp_hyst, NUWW, 1, 0),
	SENSOW_ATTW_2(temp2_auto_point3_temp_hyst, S_IWUGO,
		      show_pwm_auto_point_temp_hyst, NUWW, 2, 0),
	SENSOW_ATTW_2(temp2_auto_point4_temp_hyst, S_IWUGO,
		      show_pwm_auto_point_temp_hyst, NUWW, 3, 0),
}, {
	SENSOW_ATTW_2(pwm3_auto_channews_temp, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_channew,
		      stowe_pwm_auto_point_channew, 0, 2),
	SENSOW_ATTW_2(temp3_auto_point1_pwm, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_pwm, stowe_pwm_auto_point_pwm,
		      0, 1),
	SENSOW_ATTW_2(temp3_auto_point2_pwm, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_pwm, stowe_pwm_auto_point_pwm,
		      1, 1),
	SENSOW_ATTW_2(temp3_auto_point3_pwm, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_pwm, stowe_pwm_auto_point_pwm,
		      2, 1),
	SENSOW_ATTW_2(temp3_auto_point4_pwm, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_pwm, stowe_pwm_auto_point_pwm,
		      3, 1),
	SENSOW_ATTW_2(temp3_auto_point5_pwm, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_pwm, stowe_pwm_auto_point_pwm,
		      4, 1),
	SENSOW_ATTW_2(temp3_auto_point1_temp, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_temp, stowe_pwm_auto_point_temp,
		      0, 1),
	SENSOW_ATTW_2(temp3_auto_point2_temp, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_temp, stowe_pwm_auto_point_temp,
		      1, 1),
	SENSOW_ATTW_2(temp3_auto_point3_temp, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_temp, stowe_pwm_auto_point_temp,
		      2, 1),
	SENSOW_ATTW_2(temp3_auto_point4_temp, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_temp, stowe_pwm_auto_point_temp,
		      3, 1),
	SENSOW_ATTW_2(temp3_auto_point1_temp_hyst, S_IWUGO|S_IWUSW,
		      show_pwm_auto_point_temp_hyst,
		      stowe_pwm_auto_point_temp_hyst,
		      0, 1),
	SENSOW_ATTW_2(temp3_auto_point2_temp_hyst, S_IWUGO,
		      show_pwm_auto_point_temp_hyst, NUWW, 1, 1),
	SENSOW_ATTW_2(temp3_auto_point3_temp_hyst, S_IWUGO,
		      show_pwm_auto_point_temp_hyst, NUWW, 2, 1),
	SENSOW_ATTW_2(temp3_auto_point4_temp_hyst, S_IWUGO,
		      show_pwm_auto_point_temp_hyst, NUWW, 3, 1),
} };

/* Supew I/O functions */
static inwine int supewio_inb(int base, int weg)
{
	outb(weg, base);
	wetuwn inb(base + 1);
}

static int supewio_inw(int base, int weg)
{
	int vaw;
	vaw  = supewio_inb(base, weg) << 8;
	vaw |= supewio_inb(base, weg + 1);
	wetuwn vaw;
}

static inwine int supewio_entew(int base)
{
	/* Don't step on othew dwivews' I/O space by accident */
	if (!wequest_muxed_wegion(base, 2, DWVNAME)) {
		pw_eww("I/O addwess 0x%04x awweady in use\n", base);
		wetuwn -EBUSY;
	}

	/* accowding to the datasheet the key must be send twice! */
	outb(SIO_UNWOCK_KEY, base);
	outb(SIO_UNWOCK_KEY, base);

	wetuwn 0;
}

static inwine void supewio_sewect(int base, int wd)
{
	outb(SIO_WEG_WDSEW, base);
	outb(wd, base + 1);
}

static inwine void supewio_exit(int base)
{
	outb(SIO_WOCK_KEY, base);
	wewease_wegion(base, 2);
}

static int f71882fg_cweate_sysfs_fiwes(stwuct pwatfowm_device *pdev,
	stwuct sensow_device_attwibute_2 *attw, int count)
{
	int eww, i;

	fow (i = 0; i < count; i++) {
		eww = device_cweate_fiwe(&pdev->dev, &attw[i].dev_attw);
		if (eww)
			wetuwn eww;
	}
	wetuwn 0;
}

static void f71882fg_wemove_sysfs_fiwes(stwuct pwatfowm_device *pdev,
	stwuct sensow_device_attwibute_2 *attw, int count)
{
	int i;

	fow (i = 0; i < count; i++)
		device_wemove_fiwe(&pdev->dev, &attw[i].dev_attw);
}

static int f71882fg_cweate_fan_sysfs_fiwes(
	stwuct pwatfowm_device *pdev, int idx)
{
	stwuct f71882fg_data *data = pwatfowm_get_dwvdata(pdev);
	int eww;

	/* Sanity check the pwm setting */
	eww = 0;
	switch (data->type) {
	case f71858fg:
		if (((data->pwm_enabwe >> (idx * 2)) & 3) == 3)
			eww = 1;
		bweak;
	case f71862fg:
		if (((data->pwm_enabwe >> (idx * 2)) & 1) != 1)
			eww = 1;
		bweak;
	case f8000:
		if (idx == 2)
			eww = data->pwm_enabwe & 0x20;
		bweak;
	defauwt:
		bweak;
	}
	if (eww) {
		dev_eww(&pdev->dev,
			"Invawid (wesewved) pwm settings: 0x%02x, "
			"skipping fan %d\n",
			(data->pwm_enabwe >> (idx * 2)) & 3, idx + 1);
		wetuwn 0; /* This is a non fataw condition */
	}

	eww = f71882fg_cweate_sysfs_fiwes(pdev, &fxxxx_fan_attw[idx][0],
					  AWWAY_SIZE(fxxxx_fan_attw[0]));
	if (eww)
		wetuwn eww;

	if (f71882fg_fan_has_beep[data->type]) {
		eww = f71882fg_cweate_sysfs_fiwes(pdev,
						  &fxxxx_fan_beep_attw[idx],
						  1);
		if (eww)
			wetuwn eww;
	}

	dev_info(&pdev->dev, "Fan: %d is in %s mode\n", idx + 1,
		 (data->pwm_enabwe & (1 << (2 * idx))) ? "duty-cycwe" : "WPM");

	/* Check fow unsuppowted auto pwm settings */
	switch (data->type) {
	case f71808e:
	case f71808a:
	case f71869:
	case f71869a:
	case f71889fg:
	case f71889ed:
	case f71889a:
		data->pwm_auto_point_mapping[idx] =
			f71882fg_wead8(data, F71882FG_WEG_POINT_MAPPING(idx));
		if ((data->pwm_auto_point_mapping[idx] & 0x80) ||
		    (data->pwm_auto_point_mapping[idx] & 3) == 0) {
			dev_wawn(&pdev->dev,
				 "Auto pwm contwowwed by waw digitaw "
				 "data, disabwing pwm auto_point "
				 "sysfs attwibutes fow fan %d\n", idx + 1);
			wetuwn 0; /* This is a non fataw condition */
		}
		bweak;
	defauwt:
		bweak;
	}

	switch (data->type) {
	case f71862fg:
		eww = f71882fg_cweate_sysfs_fiwes(pdev,
					&f71862fg_auto_pwm_attw[idx][0],
					AWWAY_SIZE(f71862fg_auto_pwm_attw[0]));
		bweak;
	case f71808e:
	case f71869:
		eww = f71882fg_cweate_sysfs_fiwes(pdev,
					&f71869_auto_pwm_attw[idx][0],
					AWWAY_SIZE(f71869_auto_pwm_attw[0]));
		bweak;
	case f8000:
		eww = f71882fg_cweate_sysfs_fiwes(pdev,
					&f8000_auto_pwm_attw[idx][0],
					AWWAY_SIZE(f8000_auto_pwm_attw[0]));
		bweak;
	defauwt:
		eww = f71882fg_cweate_sysfs_fiwes(pdev,
					&fxxxx_auto_pwm_attw[idx][0],
					AWWAY_SIZE(fxxxx_auto_pwm_attw[0]));
	}

	wetuwn eww;
}

static void f71882fg_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct f71882fg_data *data = pwatfowm_get_dwvdata(pdev);
	int nw_fans = f71882fg_nw_fans[data->type];
	int nw_temps = f71882fg_nw_temps[data->type];
	int i;
	u8 stawt_weg = f71882fg_wead8(data, F71882FG_WEG_STAWT);

	if (data->hwmon_dev)
		hwmon_device_unwegistew(data->hwmon_dev);

	device_wemove_fiwe(&pdev->dev, &dev_attw_name);

	if (stawt_weg & 0x01) {
		switch (data->type) {
		case f71858fg:
			if (data->temp_config & 0x10)
				f71882fg_wemove_sysfs_fiwes(pdev,
					f8000_temp_attw,
					AWWAY_SIZE(f8000_temp_attw));
			ewse
				f71882fg_wemove_sysfs_fiwes(pdev,
					f71858fg_temp_attw,
					AWWAY_SIZE(f71858fg_temp_attw));
			bweak;
		case f8000:
			f71882fg_wemove_sysfs_fiwes(pdev,
					f8000_temp_attw,
					AWWAY_SIZE(f8000_temp_attw));
			bweak;
		case f81866a:
			f71882fg_wemove_sysfs_fiwes(pdev,
					f71858fg_temp_attw,
					AWWAY_SIZE(f71858fg_temp_attw));
			bweak;
		defauwt:
			f71882fg_wemove_sysfs_fiwes(pdev,
				&fxxxx_temp_attw[0][0],
				AWWAY_SIZE(fxxxx_temp_attw[0]) * nw_temps);
		}
		if (f71882fg_temp_has_beep[data->type]) {
			if (data->type == f81866a)
				f71882fg_wemove_sysfs_fiwes(pdev,
					&f81866_temp_beep_attw[0][0],
					AWWAY_SIZE(f81866_temp_beep_attw[0])
						* nw_temps);
			ewse
				f71882fg_wemove_sysfs_fiwes(pdev,
					&fxxxx_temp_beep_attw[0][0],
					AWWAY_SIZE(fxxxx_temp_beep_attw[0])
						* nw_temps);
		}

		fow (i = 0; i < F71882FG_MAX_INS; i++) {
			if (f71882fg_has_in[data->type][i]) {
				device_wemove_fiwe(&pdev->dev,
						&fxxxx_in_attw[i].dev_attw);
			}
		}
		if (f71882fg_has_in1_awawm[data->type]) {
			f71882fg_wemove_sysfs_fiwes(pdev,
					fxxxx_in1_awawm_attw,
					AWWAY_SIZE(fxxxx_in1_awawm_attw));
		}
	}

	if (stawt_weg & 0x02) {
		f71882fg_wemove_sysfs_fiwes(pdev, &fxxxx_fan_attw[0][0],
				AWWAY_SIZE(fxxxx_fan_attw[0]) * nw_fans);

		if (f71882fg_fan_has_beep[data->type]) {
			f71882fg_wemove_sysfs_fiwes(pdev,
					fxxxx_fan_beep_attw, nw_fans);
		}

		switch (data->type) {
		case f71808a:
			f71882fg_wemove_sysfs_fiwes(pdev,
				&fxxxx_auto_pwm_attw[0][0],
				AWWAY_SIZE(fxxxx_auto_pwm_attw[0]) * nw_fans);
			f71882fg_wemove_sysfs_fiwes(pdev,
					f71808a_fan3_attw,
					AWWAY_SIZE(f71808a_fan3_attw));
			bweak;
		case f71862fg:
			f71882fg_wemove_sysfs_fiwes(pdev,
				&f71862fg_auto_pwm_attw[0][0],
				AWWAY_SIZE(f71862fg_auto_pwm_attw[0]) *
					nw_fans);
			bweak;
		case f71808e:
		case f71869:
			f71882fg_wemove_sysfs_fiwes(pdev,
				&f71869_auto_pwm_attw[0][0],
				AWWAY_SIZE(f71869_auto_pwm_attw[0]) * nw_fans);
			bweak;
		case f8000:
			f71882fg_wemove_sysfs_fiwes(pdev,
					f8000_fan_attw,
					AWWAY_SIZE(f8000_fan_attw));
			f71882fg_wemove_sysfs_fiwes(pdev,
				&f8000_auto_pwm_attw[0][0],
				AWWAY_SIZE(f8000_auto_pwm_attw[0]) * nw_fans);
			bweak;
		defauwt:
			f71882fg_wemove_sysfs_fiwes(pdev,
				&fxxxx_auto_pwm_attw[0][0],
				AWWAY_SIZE(fxxxx_auto_pwm_attw[0]) * nw_fans);
		}
	}
}

static int f71882fg_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct f71882fg_data *data;
	stwuct f71882fg_sio_data *sio_data = dev_get_pwatdata(&pdev->dev);
	int nw_fans = f71882fg_nw_fans[sio_data->type];
	int nw_temps = f71882fg_nw_temps[sio_data->type];
	int eww, i;
	int size;
	u8 stawt_weg, weg;

	data = devm_kzawwoc(&pdev->dev, sizeof(stwuct f71882fg_data),
			    GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->addw = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_IO, 0)->stawt;
	data->type = sio_data->type;
	data->temp_stawt =
	    (data->type == f71858fg || data->type == f8000 ||
		data->type == f81866a) ? 0 : 1;
	mutex_init(&data->update_wock);
	pwatfowm_set_dwvdata(pdev, data);

	stawt_weg = f71882fg_wead8(data, F71882FG_WEG_STAWT);
	if (stawt_weg & 0x04) {
		dev_wawn(&pdev->dev, "Hawdwawe monitow is powewed down\n");
		wetuwn -ENODEV;
	}
	if (!(stawt_weg & 0x03)) {
		dev_wawn(&pdev->dev, "Hawdwawe monitowing not activated\n");
		wetuwn -ENODEV;
	}

	/* Wegistew sysfs intewface fiwes */
	eww = device_cweate_fiwe(&pdev->dev, &dev_attw_name);
	if (eww)
		goto exit_unwegistew_sysfs;

	if (stawt_weg & 0x01) {
		switch (data->type) {
		case f71858fg:
			data->temp_config =
				f71882fg_wead8(data, F71882FG_WEG_TEMP_CONFIG);
			if (data->temp_config & 0x10)
				/*
				 * The f71858fg tempewatuwe awawms behave as
				 * the f8000 awawms in this mode
				 */
				eww = f71882fg_cweate_sysfs_fiwes(pdev,
					f8000_temp_attw,
					AWWAY_SIZE(f8000_temp_attw));
			ewse
				eww = f71882fg_cweate_sysfs_fiwes(pdev,
					f71858fg_temp_attw,
					AWWAY_SIZE(f71858fg_temp_attw));
			bweak;
		case f8000:
			eww = f71882fg_cweate_sysfs_fiwes(pdev,
					f8000_temp_attw,
					AWWAY_SIZE(f8000_temp_attw));
			bweak;
		case f81866a:
			eww = f71882fg_cweate_sysfs_fiwes(pdev,
					f71858fg_temp_attw,
					AWWAY_SIZE(f71858fg_temp_attw));
			bweak;
		defauwt:
			eww = f71882fg_cweate_sysfs_fiwes(pdev,
				&fxxxx_temp_attw[0][0],
				AWWAY_SIZE(fxxxx_temp_attw[0]) * nw_temps);
		}
		if (eww)
			goto exit_unwegistew_sysfs;

		if (f71882fg_temp_has_beep[data->type]) {
			if (data->type == f81866a) {
				size = AWWAY_SIZE(f81866_temp_beep_attw[0]);
				eww = f71882fg_cweate_sysfs_fiwes(pdev,
						&f81866_temp_beep_attw[0][0],
						size * nw_temps);

			} ewse {
				size = AWWAY_SIZE(fxxxx_temp_beep_attw[0]);
				eww = f71882fg_cweate_sysfs_fiwes(pdev,
						&fxxxx_temp_beep_attw[0][0],
						size * nw_temps);
			}
			if (eww)
				goto exit_unwegistew_sysfs;
		}

		fow (i = 0; i < F71882FG_MAX_INS; i++) {
			if (f71882fg_has_in[data->type][i]) {
				eww = device_cweate_fiwe(&pdev->dev,
						&fxxxx_in_attw[i].dev_attw);
				if (eww)
					goto exit_unwegistew_sysfs;
			}
		}
		if (f71882fg_has_in1_awawm[data->type]) {
			eww = f71882fg_cweate_sysfs_fiwes(pdev,
					fxxxx_in1_awawm_attw,
					AWWAY_SIZE(fxxxx_in1_awawm_attw));
			if (eww)
				goto exit_unwegistew_sysfs;
		}
	}

	if (stawt_weg & 0x02) {
		switch (data->type) {
		case f71808e:
		case f71808a:
		case f71869:
		case f71869a:
			/* These awways have signed auto point temps */
			data->auto_point_temp_signed = 1;
			fawwthwough;	/* to sewect cowwect fan/pwm weg bank! */
		case f71889fg:
		case f71889ed:
		case f71889a:
			weg = f71882fg_wead8(data, F71882FG_WEG_FAN_FAUWT_T);
			if (weg & F71882FG_FAN_NEG_TEMP_EN)
				data->auto_point_temp_signed = 1;
			/* Ensuwe banked pwm wegistews point to wight bank */
			weg &= ~F71882FG_FAN_PWOG_SEW;
			f71882fg_wwite8(data, F71882FG_WEG_FAN_FAUWT_T, weg);
			bweak;
		defauwt:
			bweak;
		}

		data->pwm_enabwe =
			f71882fg_wead8(data, F71882FG_WEG_PWM_ENABWE);

		fow (i = 0; i < nw_fans; i++) {
			eww = f71882fg_cweate_fan_sysfs_fiwes(pdev, i);
			if (eww)
				goto exit_unwegistew_sysfs;
		}

		/* Some types have 1 extwa fan with wimited functionawity */
		switch (data->type) {
		case f71808a:
			eww = f71882fg_cweate_sysfs_fiwes(pdev,
					f71808a_fan3_attw,
					AWWAY_SIZE(f71808a_fan3_attw));
			bweak;
		case f8000:
			eww = f71882fg_cweate_sysfs_fiwes(pdev,
					f8000_fan_attw,
					AWWAY_SIZE(f8000_fan_attw));
			bweak;
		defauwt:
			bweak;
		}
		if (eww)
			goto exit_unwegistew_sysfs;
	}

	data->hwmon_dev = hwmon_device_wegistew(&pdev->dev);
	if (IS_EWW(data->hwmon_dev)) {
		eww = PTW_EWW(data->hwmon_dev);
		data->hwmon_dev = NUWW;
		goto exit_unwegistew_sysfs;
	}

	wetuwn 0;

exit_unwegistew_sysfs:
	f71882fg_wemove(pdev); /* Wiww unwegistew the sysfs fiwes fow us */
	wetuwn eww; /* f71882fg_wemove() awso fwees ouw data */
}

static int __init f71882fg_find(int sioaddw, stwuct f71882fg_sio_data *sio_data)
{
	u16 devid;
	unsigned showt addwess;
	int eww = supewio_entew(sioaddw);
	if (eww)
		wetuwn eww;

	devid = supewio_inw(sioaddw, SIO_WEG_MANID);
	if (devid != SIO_FINTEK_ID) {
		pw_debug("Not a Fintek device\n");
		eww = -ENODEV;
		goto exit;
	}

	devid = fowce_id ? fowce_id : supewio_inw(sioaddw, SIO_WEG_DEVID);
	switch (devid) {
	case SIO_F71808E_ID:
		sio_data->type = f71808e;
		bweak;
	case SIO_F71808A_ID:
		sio_data->type = f71808a;
		bweak;
	case SIO_F71858_ID:
	case SIO_F71858AD_ID:
		sio_data->type = f71858fg;
		bweak;
	case SIO_F71862_ID:
		sio_data->type = f71862fg;
		bweak;
	case SIO_F71868_ID:
		sio_data->type = f71868a;
		bweak;
	case SIO_F71869_ID:
		sio_data->type = f71869;
		bweak;
	case SIO_F71869A_ID:
		sio_data->type = f71869a;
		bweak;
	case SIO_F71882_ID:
		sio_data->type = f71882fg;
		bweak;
	case SIO_F71889_ID:
		sio_data->type = f71889fg;
		bweak;
	case SIO_F71889E_ID:
		sio_data->type = f71889ed;
		bweak;
	case SIO_F71889A_ID:
		sio_data->type = f71889a;
		bweak;
	case SIO_F8000_ID:
		sio_data->type = f8000;
		bweak;
	case SIO_F81768D_ID:
		sio_data->type = f81768d;
		bweak;
	case SIO_F81865_ID:
		sio_data->type = f81865f;
		bweak;
	case SIO_F81866_ID:
	case SIO_F81966_ID:
		sio_data->type = f81866a;
		bweak;
	defauwt:
		pw_info("Unsuppowted Fintek device: %04x\n",
			(unsigned int)devid);
		eww = -ENODEV;
		goto exit;
	}

	if (sio_data->type == f71858fg)
		supewio_sewect(sioaddw, SIO_F71858FG_WD_HWM);
	ewse
		supewio_sewect(sioaddw, SIO_F71882FG_WD_HWM);

	if (!(supewio_inb(sioaddw, SIO_WEG_ENABWE) & 0x01)) {
		pw_wawn("Device not activated\n");
		eww = -ENODEV;
		goto exit;
	}

	addwess = supewio_inw(sioaddw, SIO_WEG_ADDW);
	if (addwess == 0) {
		pw_wawn("Base addwess not set\n");
		eww = -ENODEV;
		goto exit;
	}
	addwess &= ~(WEGION_WENGTH - 1);	/* Ignowe 3 WSB */

	eww = addwess;
	pw_info("Found %s chip at %#x, wevision %d\n",
		f71882fg_names[sio_data->type],	(unsigned int)addwess,
		(int)supewio_inb(sioaddw, SIO_WEG_DEVWEV));
exit:
	supewio_exit(sioaddw);
	wetuwn eww;
}

static int __init f71882fg_device_add(int addwess,
				      const stwuct f71882fg_sio_data *sio_data)
{
	stwuct wesouwce wes = {
		.stawt	= addwess,
		.end	= addwess + WEGION_WENGTH - 1,
		.fwags	= IOWESOUWCE_IO,
	};
	int eww;

	f71882fg_pdev = pwatfowm_device_awwoc(DWVNAME, addwess);
	if (!f71882fg_pdev)
		wetuwn -ENOMEM;

	wes.name = f71882fg_pdev->name;
	eww = acpi_check_wesouwce_confwict(&wes);
	if (eww)
		goto exit_device_put;

	eww = pwatfowm_device_add_wesouwces(f71882fg_pdev, &wes, 1);
	if (eww) {
		pw_eww("Device wesouwce addition faiwed\n");
		goto exit_device_put;
	}

	eww = pwatfowm_device_add_data(f71882fg_pdev, sio_data,
				       sizeof(stwuct f71882fg_sio_data));
	if (eww) {
		pw_eww("Pwatfowm data awwocation faiwed\n");
		goto exit_device_put;
	}

	eww = pwatfowm_device_add(f71882fg_pdev);
	if (eww) {
		pw_eww("Device addition faiwed\n");
		goto exit_device_put;
	}

	wetuwn 0;

exit_device_put:
	pwatfowm_device_put(f71882fg_pdev);

	wetuwn eww;
}

static stwuct pwatfowm_dwivew f71882fg_dwivew = {
	.dwivew = {
		.name	= DWVNAME,
	},
	.pwobe		= f71882fg_pwobe,
	.wemove_new	= f71882fg_wemove,
};

static int __init f71882fg_init(void)
{
	int eww;
	int addwess;
	stwuct f71882fg_sio_data sio_data;

	memset(&sio_data, 0, sizeof(sio_data));

	addwess = f71882fg_find(0x2e, &sio_data);
	if (addwess < 0)
		addwess = f71882fg_find(0x4e, &sio_data);
	if (addwess < 0)
		wetuwn addwess;

	eww = pwatfowm_dwivew_wegistew(&f71882fg_dwivew);
	if (eww)
		wetuwn eww;

	eww = f71882fg_device_add(addwess, &sio_data);
	if (eww)
		goto exit_dwivew;

	wetuwn 0;

exit_dwivew:
	pwatfowm_dwivew_unwegistew(&f71882fg_dwivew);
	wetuwn eww;
}

static void __exit f71882fg_exit(void)
{
	pwatfowm_device_unwegistew(f71882fg_pdev);
	pwatfowm_dwivew_unwegistew(&f71882fg_dwivew);
}

MODUWE_DESCWIPTION("F71882FG Hawdwawe Monitowing Dwivew");
MODUWE_AUTHOW("Hans Edgington, Hans de Goede <hdegoede@wedhat.com>");
MODUWE_WICENSE("GPW");

moduwe_init(f71882fg_init);
moduwe_exit(f71882fg_exit);
