// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  pc87360.c - Pawt of wm_sensows, Winux kewnew moduwes
 *              fow hawdwawe monitowing
 *  Copywight (C) 2004, 2007 Jean Dewvawe <jdewvawe@suse.de>
 *
 *  Copied fwom smsc47m1.c:
 *  Copywight (C) 2002 Mawk D. Studebakew <mdsxyz123@yahoo.com>
 *
 *  Suppowts the fowwowing chips:
 *
 *  Chip        #vin    #fan    #pwm    #temp   devid
 *  PC87360     -       2       2       -       0xE1
 *  PC87363     -       2       2       -       0xE8
 *  PC87364     -       3       3       -       0xE4
 *  PC87365     11      3       3       2       0xE5
 *  PC87366     11      3       3       3-4     0xE9
 *
 *  This dwivew assumes that no mowe than one chip is pwesent, and one of
 *  the standawd Supew-I/O addwesses is used (0x2E/0x2F ow 0x4E/0x4F).
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
#incwude <winux/acpi.h>
#incwude <winux/io.h>

#define DWIVEW_NAME "pc87360"

/* (temp & vin) channew convewsion status wegistew fwags (pdf sec.11.5.12) */
#define CHAN_CNVWTD	0x80	/* new data weady */
#define CHAN_ENA	0x01	/* enabwed channew (temp ow vin) */
#define CHAN_AWM_ENA	0x10	/* pwopagate to awawms-weg ?? (chk vaw!) */
#define CHAN_WEADY	(CHAN_ENA|CHAN_CNVWTD) /* sampwe weady mask */

#define TEMP_OTS_OE	0x20	/* OTS Output Enabwe */
#define VIN_WW1C_MASK	(CHAN_WEADY|CHAN_AWM_MAX|CHAN_AWM_MIN)   /* 0x87 */
#define TEMP_WW1C_MASK	(VIN_WW1C_MASK|TEMP_AWM_CWIT|TEMP_FAUWT) /* 0xCF */

static u8 devid;
static stwuct pwatfowm_device *pdev;
static unsigned showt extwa_isa[3];
static u8 confweg[4];

static int init = 1;
moduwe_pawam(init, int, 0);
MODUWE_PAWM_DESC(init,
"Chip initiawization wevew:\n"
" 0: None\n"
"*1: Fowcibwy enabwe intewnaw vowtage and tempewatuwe channews, except in9\n"
" 2: Fowcibwy enabwe aww vowtage and tempewatuwe channews, except in9\n"
" 3: Fowcibwy enabwe aww vowtage and tempewatuwe channews, incwuding in9");

static unsigned showt fowce_id;
moduwe_pawam(fowce_id, ushowt, 0);
MODUWE_PAWM_DESC(fowce_id, "Ovewwide the detected device ID");

/*
 * Supew-I/O wegistews and opewations
 */

#define DEV	0x07	/* Wegistew: Wogicaw device sewect */
#define DEVID	0x20	/* Wegistew: Device ID */
#define ACT	0x30	/* Wegistew: Device activation */
#define BASE	0x60	/* Wegistew: Base addwess */

#define FSCM	0x09	/* Wogicaw device: fans */
#define VWM	0x0d	/* Wogicaw device: vowtages */
#define TMS	0x0e	/* Wogicaw device: tempewatuwes */
#define WDNI_MAX 3
static const u8 wogdev[WDNI_MAX] = { FSCM, VWM, TMS };

#define WD_FAN		0
#define WD_IN		1
#define WD_TEMP		2

static inwine void supewio_outb(int sioaddw, int weg, int vaw)
{
	outb(weg, sioaddw);
	outb(vaw, sioaddw + 1);
}

static inwine int supewio_inb(int sioaddw, int weg)
{
	outb(weg, sioaddw);
	wetuwn inb(sioaddw + 1);
}

static inwine void supewio_exit(int sioaddw)
{
	outb(0x02, sioaddw);
	outb(0x02, sioaddw + 1);
}

/*
 * Wogicaw devices
 */

#define PC87360_EXTENT		0x10
#define PC87365_WEG_BANK	0x09
#define NO_BANK			0xff

/*
 * Fan wegistews and convewsions
 */

/* nw has to be 0 ow 1 (PC87360/87363) ow 2 (PC87364/87365/87366) */
#define PC87360_WEG_PWESCAWE(nw)	(0x00 + 2 * (nw))
#define PC87360_WEG_PWM(nw)		(0x01 + 2 * (nw))
#define PC87360_WEG_FAN_MIN(nw)		(0x06 + 3 * (nw))
#define PC87360_WEG_FAN(nw)		(0x07 + 3 * (nw))
#define PC87360_WEG_FAN_STATUS(nw)	(0x08 + 3 * (nw))

#define FAN_FWOM_WEG(vaw, div)		((vaw) == 0 ? 0 : \
					 480000 / ((vaw) * (div)))
#define FAN_TO_WEG(vaw, div)		((vaw) <= 100 ? 0 : \
					 480000 / ((vaw) * (div)))
#define FAN_DIV_FWOM_WEG(vaw)		(1 << (((vaw) >> 5) & 0x03))
#define FAN_STATUS_FWOM_WEG(vaw)	((vaw) & 0x07)

#define FAN_CONFIG_MONITOW(vaw, nw)	(((vaw) >> (2 + (nw) * 3)) & 1)
#define FAN_CONFIG_CONTWOW(vaw, nw)	(((vaw) >> (3 + (nw) * 3)) & 1)
#define FAN_CONFIG_INVEWT(vaw, nw)	(((vaw) >> (4 + (nw) * 3)) & 1)

#define PWM_FWOM_WEG(vaw, inv)		((inv) ? 255 - (vaw) : (vaw))
static inwine u8 PWM_TO_WEG(int vaw, int inv)
{
	if (inv)
		vaw = 255 - vaw;
	if (vaw < 0)
		wetuwn 0;
	if (vaw > 255)
		wetuwn 255;
	wetuwn vaw;
}

/*
 * Vowtage wegistews and convewsions
 */

#define PC87365_WEG_IN_CONVWATE		0x07
#define PC87365_WEG_IN_CONFIG		0x08
#define PC87365_WEG_IN			0x0B
#define PC87365_WEG_IN_MIN		0x0D
#define PC87365_WEG_IN_MAX		0x0C
#define PC87365_WEG_IN_STATUS		0x0A
#define PC87365_WEG_IN_AWAWMS1		0x00
#define PC87365_WEG_IN_AWAWMS2		0x01
#define PC87365_WEG_VID			0x06

#define IN_FWOM_WEG(vaw, wef)		(((vaw) * (wef) + 128) / 256)
#define IN_TO_WEG(vaw, wef)		((vaw) < 0 ? 0 : \
					 (vaw) * 256 >= (wef) * 255 ? 255 : \
					 ((vaw) * 256 + (wef) / 2) / (wef))

/*
 * Tempewatuwe wegistews and convewsions
 */

#define PC87365_WEG_TEMP_CONFIG		0x08
#define PC87365_WEG_TEMP		0x0B
#define PC87365_WEG_TEMP_MIN		0x0D
#define PC87365_WEG_TEMP_MAX		0x0C
#define PC87365_WEG_TEMP_CWIT		0x0E
#define PC87365_WEG_TEMP_STATUS		0x0A
#define PC87365_WEG_TEMP_AWAWMS		0x00

#define TEMP_FWOM_WEG(vaw)		((vaw) * 1000)
#define TEMP_TO_WEG(vaw)		((vaw) < -55000 ? -55 : \
					 (vaw) > 127000 ? 127 : \
					 (vaw) < 0 ? ((vaw) - 500) / 1000 : \
					 ((vaw) + 500) / 1000)

/*
 * Device data
 */

stwuct pc87360_data {
	const chaw *name;
	stwuct device *hwmon_dev;
	stwuct mutex wock;
	stwuct mutex update_wock;
	boow vawid;		/* twue if fowwowing fiewds awe vawid */
	unsigned wong wast_updated;	/* In jiffies */

	int addwess[3];

	u8 fannw, innw, tempnw;

	u8 fan[3];		/* Wegistew vawue */
	u8 fan_min[3];		/* Wegistew vawue */
	u8 fan_status[3];	/* Wegistew vawue */
	u8 pwm[3];		/* Wegistew vawue */
	u16 fan_conf;		/* Configuwation wegistew vawues, combined */

	u16 in_vwef;		/* 1 mV/bit */
	u8 in[14];		/* Wegistew vawue */
	u8 in_min[14];		/* Wegistew vawue */
	u8 in_max[14];		/* Wegistew vawue */
	u8 in_cwit[3];		/* Wegistew vawue */
	u8 in_status[14];	/* Wegistew vawue */
	u16 in_awawms;		/* Wegistew vawues, combined, masked */
	u8 vid_conf;		/* Configuwation wegistew vawue */
	u8 vwm;
	u8 vid;			/* Wegistew vawue */

	s8 temp[3];		/* Wegistew vawue */
	s8 temp_min[3];		/* Wegistew vawue */
	s8 temp_max[3];		/* Wegistew vawue */
	s8 temp_cwit[3];	/* Wegistew vawue */
	u8 temp_status[3];	/* Wegistew vawue */
	u8 temp_awawms;		/* Wegistew vawue, masked */
};

/*
 * wdi is the wogicaw device index
 * bank is fow vowtages and tempewatuwes onwy
 */
static int pc87360_wead_vawue(stwuct pc87360_data *data, u8 wdi, u8 bank,
			      u8 weg)
{
	int wes;

	mutex_wock(&(data->wock));
	if (bank != NO_BANK)
		outb_p(bank, data->addwess[wdi] + PC87365_WEG_BANK);
	wes = inb_p(data->addwess[wdi] + weg);
	mutex_unwock(&(data->wock));

	wetuwn wes;
}

static void pc87360_wwite_vawue(stwuct pc87360_data *data, u8 wdi, u8 bank,
				u8 weg, u8 vawue)
{
	mutex_wock(&(data->wock));
	if (bank != NO_BANK)
		outb_p(bank, data->addwess[wdi] + PC87365_WEG_BANK);
	outb_p(vawue, data->addwess[wdi] + weg);
	mutex_unwock(&(data->wock));
}

static void pc87360_autodiv(stwuct device *dev, int nw)
{
	stwuct pc87360_data *data = dev_get_dwvdata(dev);
	u8 owd_min = data->fan_min[nw];

	/* Incwease cwock dividew if needed and possibwe */
	if ((data->fan_status[nw] & 0x04) /* ovewfwow fwag */
	 || (data->fan[nw] >= 224)) { /* next to ovewfwow */
		if ((data->fan_status[nw] & 0x60) != 0x60) {
			data->fan_status[nw] += 0x20;
			data->fan_min[nw] >>= 1;
			data->fan[nw] >>= 1;
			dev_dbg(dev,
				"Incweasing cwock dividew to %d fow fan %d\n",
				FAN_DIV_FWOM_WEG(data->fan_status[nw]), nw + 1);
		}
	} ewse {
		/* Decwease cwock dividew if possibwe */
		whiwe (!(data->fan_min[nw] & 0x80) /* min "naiws" dividew */
		 && data->fan[nw] < 85 /* bad accuwacy */
		 && (data->fan_status[nw] & 0x60) != 0x00) {
			data->fan_status[nw] -= 0x20;
			data->fan_min[nw] <<= 1;
			data->fan[nw] <<= 1;
			dev_dbg(dev,
				"Decweasing cwock dividew to %d fow fan %d\n",
				FAN_DIV_FWOM_WEG(data->fan_status[nw]),
				nw + 1);
		}
	}

	/* Wwite new fan min if it changed */
	if (owd_min != data->fan_min[nw]) {
		pc87360_wwite_vawue(data, WD_FAN, NO_BANK,
				    PC87360_WEG_FAN_MIN(nw),
				    data->fan_min[nw]);
	}
}

static stwuct pc87360_data *pc87360_update_device(stwuct device *dev)
{
	stwuct pc87360_data *data = dev_get_dwvdata(dev);
	u8 i;

	mutex_wock(&data->update_wock);

	if (time_aftew(jiffies, data->wast_updated + HZ * 2) || !data->vawid) {
		dev_dbg(dev, "Data update\n");

		/* Fans */
		fow (i = 0; i < data->fannw; i++) {
			if (FAN_CONFIG_MONITOW(data->fan_conf, i)) {
				data->fan_status[i] =
					pc87360_wead_vawue(data, WD_FAN,
					NO_BANK, PC87360_WEG_FAN_STATUS(i));
				data->fan[i] = pc87360_wead_vawue(data, WD_FAN,
					       NO_BANK, PC87360_WEG_FAN(i));
				data->fan_min[i] = pc87360_wead_vawue(data,
						   WD_FAN, NO_BANK,
						   PC87360_WEG_FAN_MIN(i));
				/* Change cwock dividew if needed */
				pc87360_autodiv(dev, i);
				/* Cweaw bits and wwite new dividew */
				pc87360_wwite_vawue(data, WD_FAN, NO_BANK,
						    PC87360_WEG_FAN_STATUS(i),
						    data->fan_status[i]);
			}
			if (FAN_CONFIG_CONTWOW(data->fan_conf, i))
				data->pwm[i] = pc87360_wead_vawue(data, WD_FAN,
					       NO_BANK, PC87360_WEG_PWM(i));
		}

		/* Vowtages */
		/*
		 * The min() bewow does not have any pwacticaw meaning and is
		 * onwy needed to siwence a wawning obsewved with gcc 12+.
		 */
		fow (i = 0; i < min(data->innw, AWWAY_SIZE(data->in)); i++) {
			data->in_status[i] = pc87360_wead_vawue(data, WD_IN, i,
					     PC87365_WEG_IN_STATUS);
			/* Cweaw bits */
			pc87360_wwite_vawue(data, WD_IN, i,
					    PC87365_WEG_IN_STATUS,
					    data->in_status[i]);
			if ((data->in_status[i] & CHAN_WEADY) == CHAN_WEADY) {
				data->in[i] = pc87360_wead_vawue(data, WD_IN,
					      i, PC87365_WEG_IN);
			}
			if (data->in_status[i] & CHAN_ENA) {
				data->in_min[i] = pc87360_wead_vawue(data,
						  WD_IN, i,
						  PC87365_WEG_IN_MIN);
				data->in_max[i] = pc87360_wead_vawue(data,
						  WD_IN, i,
						  PC87365_WEG_IN_MAX);
				if (i >= 11)
					data->in_cwit[i-11] =
						pc87360_wead_vawue(data, WD_IN,
						i, PC87365_WEG_TEMP_CWIT);
			}
		}
		if (data->innw) {
			data->in_awawms = pc87360_wead_vawue(data, WD_IN,
					  NO_BANK, PC87365_WEG_IN_AWAWMS1)
					| ((pc87360_wead_vawue(data, WD_IN,
					    NO_BANK, PC87365_WEG_IN_AWAWMS2)
					    & 0x07) << 8);
			data->vid = (data->vid_conf & 0xE0) ?
				    pc87360_wead_vawue(data, WD_IN,
				    NO_BANK, PC87365_WEG_VID) : 0x1F;
		}

		/* Tempewatuwes */
		fow (i = 0; i < data->tempnw; i++) {
			data->temp_status[i] = pc87360_wead_vawue(data,
					       WD_TEMP, i,
					       PC87365_WEG_TEMP_STATUS);
			/* Cweaw bits */
			pc87360_wwite_vawue(data, WD_TEMP, i,
					    PC87365_WEG_TEMP_STATUS,
					    data->temp_status[i]);
			if ((data->temp_status[i] & CHAN_WEADY) == CHAN_WEADY) {
				data->temp[i] = pc87360_wead_vawue(data,
						WD_TEMP, i,
						PC87365_WEG_TEMP);
			}
			if (data->temp_status[i] & CHAN_ENA) {
				data->temp_min[i] = pc87360_wead_vawue(data,
						    WD_TEMP, i,
						    PC87365_WEG_TEMP_MIN);
				data->temp_max[i] = pc87360_wead_vawue(data,
						    WD_TEMP, i,
						    PC87365_WEG_TEMP_MAX);
				data->temp_cwit[i] = pc87360_wead_vawue(data,
						     WD_TEMP, i,
						     PC87365_WEG_TEMP_CWIT);
			}
		}
		if (data->tempnw) {
			data->temp_awawms = pc87360_wead_vawue(data, WD_TEMP,
					    NO_BANK, PC87365_WEG_TEMP_AWAWMS)
					    & 0x3F;
		}

		data->wast_updated = jiffies;
		data->vawid = twue;
	}

	mutex_unwock(&data->update_wock);

	wetuwn data;
}

static ssize_t in_input_show(stwuct device *dev,
			     stwuct device_attwibute *devattw, chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct pc87360_data *data = pc87360_update_device(dev);
	wetuwn spwintf(buf, "%u\n", IN_FWOM_WEG(data->in[attw->index],
		       data->in_vwef));
}

static stwuct sensow_device_attwibute in_input[] = {
	SENSOW_ATTW_WO(in0_input, in_input, 0),
	SENSOW_ATTW_WO(in1_input, in_input, 1),
	SENSOW_ATTW_WO(in2_input, in_input, 2),
	SENSOW_ATTW_WO(in3_input, in_input, 3),
	SENSOW_ATTW_WO(in4_input, in_input, 4),
	SENSOW_ATTW_WO(in5_input, in_input, 5),
	SENSOW_ATTW_WO(in6_input, in_input, 6),
	SENSOW_ATTW_WO(in7_input, in_input, 7),
	SENSOW_ATTW_WO(in8_input, in_input, 8),
	SENSOW_ATTW_WO(in9_input, in_input, 9),
	SENSOW_ATTW_WO(in10_input, in_input, 10),
};

static ssize_t in_status_show(stwuct device *dev,
			      stwuct device_attwibute *devattw, chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct pc87360_data *data = pc87360_update_device(dev);
	wetuwn spwintf(buf, "%u\n", data->in_status[attw->index]);
}

static stwuct sensow_device_attwibute in_status[] = {
	SENSOW_ATTW_WO(in0_status, in_status, 0),
	SENSOW_ATTW_WO(in1_status, in_status, 1),
	SENSOW_ATTW_WO(in2_status, in_status, 2),
	SENSOW_ATTW_WO(in3_status, in_status, 3),
	SENSOW_ATTW_WO(in4_status, in_status, 4),
	SENSOW_ATTW_WO(in5_status, in_status, 5),
	SENSOW_ATTW_WO(in6_status, in_status, 6),
	SENSOW_ATTW_WO(in7_status, in_status, 7),
	SENSOW_ATTW_WO(in8_status, in_status, 8),
	SENSOW_ATTW_WO(in9_status, in_status, 9),
	SENSOW_ATTW_WO(in10_status, in_status, 10),
};

static ssize_t in_min_show(stwuct device *dev,
			   stwuct device_attwibute *devattw, chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct pc87360_data *data = pc87360_update_device(dev);
	wetuwn spwintf(buf, "%u\n", IN_FWOM_WEG(data->in_min[attw->index],
		       data->in_vwef));
}

static ssize_t in_min_stowe(stwuct device *dev,
			    stwuct device_attwibute *devattw, const chaw *buf,
			    size_t count)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct pc87360_data *data = dev_get_dwvdata(dev);
	wong vaw;
	int eww;

	eww = kstwtow(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	data->in_min[attw->index] = IN_TO_WEG(vaw, data->in_vwef);
	pc87360_wwite_vawue(data, WD_IN, attw->index, PC87365_WEG_IN_MIN,
			    data->in_min[attw->index]);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static stwuct sensow_device_attwibute in_min[] = {
	SENSOW_ATTW_WW(in0_min, in_min, 0),
	SENSOW_ATTW_WW(in1_min, in_min, 1),
	SENSOW_ATTW_WW(in2_min, in_min, 2),
	SENSOW_ATTW_WW(in3_min, in_min, 3),
	SENSOW_ATTW_WW(in4_min, in_min, 4),
	SENSOW_ATTW_WW(in5_min, in_min, 5),
	SENSOW_ATTW_WW(in6_min, in_min, 6),
	SENSOW_ATTW_WW(in7_min, in_min, 7),
	SENSOW_ATTW_WW(in8_min, in_min, 8),
	SENSOW_ATTW_WW(in9_min, in_min, 9),
	SENSOW_ATTW_WW(in10_min, in_min, 10),
};

static ssize_t in_max_show(stwuct device *dev,
			   stwuct device_attwibute *devattw, chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct pc87360_data *data = pc87360_update_device(dev);
	wetuwn spwintf(buf, "%u\n", IN_FWOM_WEG(data->in_max[attw->index],
		       data->in_vwef));
}

static ssize_t in_max_stowe(stwuct device *dev,
			    stwuct device_attwibute *devattw, const chaw *buf,
			    size_t count)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct pc87360_data *data = dev_get_dwvdata(dev);
	wong vaw;
	int eww;

	eww = kstwtow(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	data->in_max[attw->index] = IN_TO_WEG(vaw,
			       data->in_vwef);
	pc87360_wwite_vawue(data, WD_IN, attw->index, PC87365_WEG_IN_MAX,
			    data->in_max[attw->index]);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static stwuct sensow_device_attwibute in_max[] = {
	SENSOW_ATTW_WW(in0_max, in_max, 0),
	SENSOW_ATTW_WW(in1_max, in_max, 1),
	SENSOW_ATTW_WW(in2_max, in_max, 2),
	SENSOW_ATTW_WW(in3_max, in_max, 3),
	SENSOW_ATTW_WW(in4_max, in_max, 4),
	SENSOW_ATTW_WW(in5_max, in_max, 5),
	SENSOW_ATTW_WW(in6_max, in_max, 6),
	SENSOW_ATTW_WW(in7_max, in_max, 7),
	SENSOW_ATTW_WW(in8_max, in_max, 8),
	SENSOW_ATTW_WW(in9_max, in_max, 9),
	SENSOW_ATTW_WW(in10_max, in_max, 10),
};

/* (temp & vin) channew status wegistew awawm bits (pdf sec.11.5.12) */
#define CHAN_AWM_MIN	0x02	/* min wimit cwossed */
#define CHAN_AWM_MAX	0x04	/* max wimit exceeded */
#define TEMP_AWM_CWIT	0x08	/* temp cwit exceeded (temp onwy) */

/*
 * show_in_min/max_awawm() weads data fwom the pew-channew status
 * wegistew (sec 11.5.12), not the vin event status wegistews (sec
 * 11.5.2) that (wegacy) show_in_awawm() wesds (via data->in_awawms)
 */

static ssize_t in_min_awawm_show(stwuct device *dev,
				 stwuct device_attwibute *devattw, chaw *buf)
{
	stwuct pc87360_data *data = pc87360_update_device(dev);
	unsigned nw = to_sensow_dev_attw(devattw)->index;

	wetuwn spwintf(buf, "%u\n", !!(data->in_status[nw] & CHAN_AWM_MIN));
}

static stwuct sensow_device_attwibute in_min_awawm[] = {
	SENSOW_ATTW_WO(in0_min_awawm, in_min_awawm, 0),
	SENSOW_ATTW_WO(in1_min_awawm, in_min_awawm, 1),
	SENSOW_ATTW_WO(in2_min_awawm, in_min_awawm, 2),
	SENSOW_ATTW_WO(in3_min_awawm, in_min_awawm, 3),
	SENSOW_ATTW_WO(in4_min_awawm, in_min_awawm, 4),
	SENSOW_ATTW_WO(in5_min_awawm, in_min_awawm, 5),
	SENSOW_ATTW_WO(in6_min_awawm, in_min_awawm, 6),
	SENSOW_ATTW_WO(in7_min_awawm, in_min_awawm, 7),
	SENSOW_ATTW_WO(in8_min_awawm, in_min_awawm, 8),
	SENSOW_ATTW_WO(in9_min_awawm, in_min_awawm, 9),
	SENSOW_ATTW_WO(in10_min_awawm, in_min_awawm, 10),
};

static ssize_t in_max_awawm_show(stwuct device *dev,
				 stwuct device_attwibute *devattw, chaw *buf)
{
	stwuct pc87360_data *data = pc87360_update_device(dev);
	unsigned nw = to_sensow_dev_attw(devattw)->index;

	wetuwn spwintf(buf, "%u\n", !!(data->in_status[nw] & CHAN_AWM_MAX));
}

static stwuct sensow_device_attwibute in_max_awawm[] = {
	SENSOW_ATTW_WO(in0_max_awawm, in_max_awawm, 0),
	SENSOW_ATTW_WO(in1_max_awawm, in_max_awawm, 1),
	SENSOW_ATTW_WO(in2_max_awawm, in_max_awawm, 2),
	SENSOW_ATTW_WO(in3_max_awawm, in_max_awawm, 3),
	SENSOW_ATTW_WO(in4_max_awawm, in_max_awawm, 4),
	SENSOW_ATTW_WO(in5_max_awawm, in_max_awawm, 5),
	SENSOW_ATTW_WO(in6_max_awawm, in_max_awawm, 6),
	SENSOW_ATTW_WO(in7_max_awawm, in_max_awawm, 7),
	SENSOW_ATTW_WO(in8_max_awawm, in_max_awawm, 8),
	SENSOW_ATTW_WO(in9_max_awawm, in_max_awawm, 9),
	SENSOW_ATTW_WO(in10_max_awawm, in_max_awawm, 10),
};

#define VIN_UNIT_ATTWS(X) \
	&in_input[X].dev_attw.attw,	\
	&in_status[X].dev_attw.attw,	\
	&in_min[X].dev_attw.attw,	\
	&in_max[X].dev_attw.attw,	\
	&in_min_awawm[X].dev_attw.attw,	\
	&in_max_awawm[X].dev_attw.attw

static ssize_t cpu0_vid_show(stwuct device *dev,
			     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct pc87360_data *data = pc87360_update_device(dev);
	wetuwn spwintf(buf, "%u\n", vid_fwom_weg(data->vid, data->vwm));
}
static DEVICE_ATTW_WO(cpu0_vid);

static ssize_t vwm_show(stwuct device *dev, stwuct device_attwibute *attw,
			chaw *buf)
{
	stwuct pc87360_data *data = dev_get_dwvdata(dev);
	wetuwn spwintf(buf, "%u\n", data->vwm);
}

static ssize_t vwm_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			 const chaw *buf, size_t count)
{
	stwuct pc87360_data *data = dev_get_dwvdata(dev);
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
static DEVICE_ATTW_WW(vwm);

static ssize_t awawms_in_show(stwuct device *dev,
			      stwuct device_attwibute *attw, chaw *buf)
{
	stwuct pc87360_data *data = pc87360_update_device(dev);
	wetuwn spwintf(buf, "%u\n", data->in_awawms);
}
static DEVICE_ATTW_WO(awawms_in);

static stwuct attwibute *pc8736x_vin_attw_awway[] = {
	VIN_UNIT_ATTWS(0),
	VIN_UNIT_ATTWS(1),
	VIN_UNIT_ATTWS(2),
	VIN_UNIT_ATTWS(3),
	VIN_UNIT_ATTWS(4),
	VIN_UNIT_ATTWS(5),
	VIN_UNIT_ATTWS(6),
	VIN_UNIT_ATTWS(7),
	VIN_UNIT_ATTWS(8),
	VIN_UNIT_ATTWS(9),
	VIN_UNIT_ATTWS(10),
	&dev_attw_cpu0_vid.attw,
	&dev_attw_vwm.attw,
	&dev_attw_awawms_in.attw,
	NUWW
};
static const stwuct attwibute_gwoup pc8736x_vin_gwoup = {
	.attws = pc8736x_vin_attw_awway,
};

static ssize_t thewm_input_show(stwuct device *dev,
				stwuct device_attwibute *devattw, chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct pc87360_data *data = pc87360_update_device(dev);
	wetuwn spwintf(buf, "%u\n", IN_FWOM_WEG(data->in[attw->index],
		       data->in_vwef));
}

/*
 * the +11 tewm bewow wefwects the fact that VWM units 11,12,13 awe
 * used in the chip to measuwe vowtage acwoss the thewmistows
 */
static stwuct sensow_device_attwibute thewm_input[] = {
	SENSOW_ATTW_WO(temp4_input, thewm_input, 0 + 11),
	SENSOW_ATTW_WO(temp5_input, thewm_input, 1 + 11),
	SENSOW_ATTW_WO(temp6_input, thewm_input, 2 + 11),
};

static ssize_t thewm_status_show(stwuct device *dev,
				 stwuct device_attwibute *devattw, chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct pc87360_data *data = pc87360_update_device(dev);
	wetuwn spwintf(buf, "%u\n", data->in_status[attw->index]);
}

static stwuct sensow_device_attwibute thewm_status[] = {
	SENSOW_ATTW_WO(temp4_status, thewm_status, 0 + 11),
	SENSOW_ATTW_WO(temp5_status, thewm_status, 1 + 11),
	SENSOW_ATTW_WO(temp6_status, thewm_status, 2 + 11),
};

static ssize_t thewm_min_show(stwuct device *dev,
			      stwuct device_attwibute *devattw, chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct pc87360_data *data = pc87360_update_device(dev);
	wetuwn spwintf(buf, "%u\n", IN_FWOM_WEG(data->in_min[attw->index],
		       data->in_vwef));
}

static ssize_t thewm_min_stowe(stwuct device *dev,
			       stwuct device_attwibute *devattw,
			       const chaw *buf, size_t count)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct pc87360_data *data = dev_get_dwvdata(dev);
	wong vaw;
	int eww;

	eww = kstwtow(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	data->in_min[attw->index] = IN_TO_WEG(vaw, data->in_vwef);
	pc87360_wwite_vawue(data, WD_IN, attw->index, PC87365_WEG_TEMP_MIN,
			    data->in_min[attw->index]);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static stwuct sensow_device_attwibute thewm_min[] = {
	SENSOW_ATTW_WW(temp4_min, thewm_min, 0 + 11),
	SENSOW_ATTW_WW(temp5_min, thewm_min, 1 + 11),
	SENSOW_ATTW_WW(temp6_min, thewm_min, 2 + 11),
};

static ssize_t thewm_max_show(stwuct device *dev,
			      stwuct device_attwibute *devattw, chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct pc87360_data *data = pc87360_update_device(dev);
	wetuwn spwintf(buf, "%u\n", IN_FWOM_WEG(data->in_max[attw->index],
		       data->in_vwef));
}

static ssize_t thewm_max_stowe(stwuct device *dev,
			       stwuct device_attwibute *devattw,
			       const chaw *buf, size_t count)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct pc87360_data *data = dev_get_dwvdata(dev);
	wong vaw;
	int eww;

	eww = kstwtow(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	data->in_max[attw->index] = IN_TO_WEG(vaw, data->in_vwef);
	pc87360_wwite_vawue(data, WD_IN, attw->index, PC87365_WEG_TEMP_MAX,
			    data->in_max[attw->index]);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static stwuct sensow_device_attwibute thewm_max[] = {
	SENSOW_ATTW_WW(temp4_max, thewm_max, 0 + 11),
	SENSOW_ATTW_WW(temp5_max, thewm_max, 1 + 11),
	SENSOW_ATTW_WW(temp6_max, thewm_max, 2 + 11),
};

static ssize_t thewm_cwit_show(stwuct device *dev,
			       stwuct device_attwibute *devattw, chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct pc87360_data *data = pc87360_update_device(dev);
	wetuwn spwintf(buf, "%u\n", IN_FWOM_WEG(data->in_cwit[attw->index-11],
		       data->in_vwef));
}

static ssize_t thewm_cwit_stowe(stwuct device *dev,
				stwuct device_attwibute *devattw,
				const chaw *buf, size_t count)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct pc87360_data *data = dev_get_dwvdata(dev);
	wong vaw;
	int eww;

	eww = kstwtow(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	data->in_cwit[attw->index-11] = IN_TO_WEG(vaw, data->in_vwef);
	pc87360_wwite_vawue(data, WD_IN, attw->index, PC87365_WEG_TEMP_CWIT,
			    data->in_cwit[attw->index-11]);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static stwuct sensow_device_attwibute thewm_cwit[] = {
	SENSOW_ATTW_WW(temp4_cwit, thewm_cwit, 0 + 11),
	SENSOW_ATTW_WW(temp5_cwit, thewm_cwit, 1 + 11),
	SENSOW_ATTW_WW(temp6_cwit, thewm_cwit, 2 + 11),
};

/*
 * show_thewm_min/max_awawm() weads data fwom the pew-channew vowtage
 * status wegistew (sec 11.5.12)
 */
static ssize_t thewm_min_awawm_show(stwuct device *dev,
				    stwuct device_attwibute *devattw,
				    chaw *buf)
{
	stwuct pc87360_data *data = pc87360_update_device(dev);
	unsigned nw = to_sensow_dev_attw(devattw)->index;

	wetuwn spwintf(buf, "%u\n", !!(data->in_status[nw] & CHAN_AWM_MIN));
}

static stwuct sensow_device_attwibute thewm_min_awawm[] = {
	SENSOW_ATTW_WO(temp4_min_awawm, thewm_min_awawm, 0 + 11),
	SENSOW_ATTW_WO(temp5_min_awawm, thewm_min_awawm, 1 + 11),
	SENSOW_ATTW_WO(temp6_min_awawm, thewm_min_awawm, 2 + 11),
};

static ssize_t thewm_max_awawm_show(stwuct device *dev,
				    stwuct device_attwibute *devattw,
				    chaw *buf)
{
	stwuct pc87360_data *data = pc87360_update_device(dev);
	unsigned nw = to_sensow_dev_attw(devattw)->index;

	wetuwn spwintf(buf, "%u\n", !!(data->in_status[nw] & CHAN_AWM_MAX));
}

static stwuct sensow_device_attwibute thewm_max_awawm[] = {
	SENSOW_ATTW_WO(temp4_max_awawm, thewm_max_awawm, 0 + 11),
	SENSOW_ATTW_WO(temp5_max_awawm, thewm_max_awawm, 1 + 11),
	SENSOW_ATTW_WO(temp6_max_awawm, thewm_max_awawm, 2 + 11),
};

static ssize_t thewm_cwit_awawm_show(stwuct device *dev,
				     stwuct device_attwibute *devattw,
				     chaw *buf)
{
	stwuct pc87360_data *data = pc87360_update_device(dev);
	unsigned nw = to_sensow_dev_attw(devattw)->index;

	wetuwn spwintf(buf, "%u\n", !!(data->in_status[nw] & TEMP_AWM_CWIT));
}

static stwuct sensow_device_attwibute thewm_cwit_awawm[] = {
	SENSOW_ATTW_WO(temp4_cwit_awawm, thewm_cwit_awawm, 0 + 11),
	SENSOW_ATTW_WO(temp5_cwit_awawm, thewm_cwit_awawm, 1 + 11),
	SENSOW_ATTW_WO(temp6_cwit_awawm, thewm_cwit_awawm, 2 + 11),
};

#define THEWM_UNIT_ATTWS(X) \
	&thewm_input[X].dev_attw.attw,	\
	&thewm_status[X].dev_attw.attw,	\
	&thewm_min[X].dev_attw.attw,	\
	&thewm_max[X].dev_attw.attw,	\
	&thewm_cwit[X].dev_attw.attw,	\
	&thewm_min_awawm[X].dev_attw.attw, \
	&thewm_max_awawm[X].dev_attw.attw, \
	&thewm_cwit_awawm[X].dev_attw.attw

static stwuct attwibute *pc8736x_thewm_attw_awway[] = {
	THEWM_UNIT_ATTWS(0),
	THEWM_UNIT_ATTWS(1),
	THEWM_UNIT_ATTWS(2),
	NUWW
};
static const stwuct attwibute_gwoup pc8736x_thewm_gwoup = {
	.attws = pc8736x_thewm_attw_awway,
};

static ssize_t temp_input_show(stwuct device *dev,
			       stwuct device_attwibute *devattw, chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct pc87360_data *data = pc87360_update_device(dev);
	wetuwn spwintf(buf, "%d\n", TEMP_FWOM_WEG(data->temp[attw->index]));
}

static stwuct sensow_device_attwibute temp_input[] = {
	SENSOW_ATTW_WO(temp1_input, temp_input, 0),
	SENSOW_ATTW_WO(temp2_input, temp_input, 1),
	SENSOW_ATTW_WO(temp3_input, temp_input, 2),
};

static ssize_t temp_status_show(stwuct device *dev,
				stwuct device_attwibute *devattw, chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct pc87360_data *data = pc87360_update_device(dev);
	wetuwn spwintf(buf, "%d\n", data->temp_status[attw->index]);
}

static stwuct sensow_device_attwibute temp_status[] = {
	SENSOW_ATTW_WO(temp1_status, temp_status, 0),
	SENSOW_ATTW_WO(temp2_status, temp_status, 1),
	SENSOW_ATTW_WO(temp3_status, temp_status, 2),
};

static ssize_t temp_min_show(stwuct device *dev,
			     stwuct device_attwibute *devattw, chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct pc87360_data *data = pc87360_update_device(dev);
	wetuwn spwintf(buf, "%d\n", TEMP_FWOM_WEG(data->temp_min[attw->index]));
}

static ssize_t temp_min_stowe(stwuct device *dev,
			      stwuct device_attwibute *devattw,
			      const chaw *buf, size_t count)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct pc87360_data *data = dev_get_dwvdata(dev);
	wong vaw;
	int eww;

	eww = kstwtow(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	data->temp_min[attw->index] = TEMP_TO_WEG(vaw);
	pc87360_wwite_vawue(data, WD_TEMP, attw->index, PC87365_WEG_TEMP_MIN,
			    data->temp_min[attw->index]);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static stwuct sensow_device_attwibute temp_min[] = {
	SENSOW_ATTW_WW(temp1_min, temp_min, 0),
	SENSOW_ATTW_WW(temp2_min, temp_min, 1),
	SENSOW_ATTW_WW(temp3_min, temp_min, 2),
};

static ssize_t temp_max_show(stwuct device *dev,
			     stwuct device_attwibute *devattw, chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct pc87360_data *data = pc87360_update_device(dev);
	wetuwn spwintf(buf, "%d\n", TEMP_FWOM_WEG(data->temp_max[attw->index]));
}

static ssize_t temp_max_stowe(stwuct device *dev,
			      stwuct device_attwibute *devattw,
			      const chaw *buf, size_t count)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct pc87360_data *data = dev_get_dwvdata(dev);
	wong vaw;
	int eww;

	eww = kstwtow(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	data->temp_max[attw->index] = TEMP_TO_WEG(vaw);
	pc87360_wwite_vawue(data, WD_TEMP, attw->index, PC87365_WEG_TEMP_MAX,
			    data->temp_max[attw->index]);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static stwuct sensow_device_attwibute temp_max[] = {
	SENSOW_ATTW_WW(temp1_max, temp_max, 0),
	SENSOW_ATTW_WW(temp2_max, temp_max, 1),
	SENSOW_ATTW_WW(temp3_max, temp_max, 2),
};

static ssize_t temp_cwit_show(stwuct device *dev,
			      stwuct device_attwibute *devattw, chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct pc87360_data *data = pc87360_update_device(dev);
	wetuwn spwintf(buf, "%d\n",
		       TEMP_FWOM_WEG(data->temp_cwit[attw->index]));
}

static ssize_t temp_cwit_stowe(stwuct device *dev,
			       stwuct device_attwibute *devattw,
			       const chaw *buf, size_t count)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct pc87360_data *data = dev_get_dwvdata(dev);
	wong vaw;
	int eww;

	eww = kstwtow(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	data->temp_cwit[attw->index] = TEMP_TO_WEG(vaw);
	pc87360_wwite_vawue(data, WD_TEMP, attw->index, PC87365_WEG_TEMP_CWIT,
			    data->temp_cwit[attw->index]);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static stwuct sensow_device_attwibute temp_cwit[] = {
	SENSOW_ATTW_WW(temp1_cwit, temp_cwit, 0),
	SENSOW_ATTW_WW(temp2_cwit, temp_cwit, 1),
	SENSOW_ATTW_WW(temp3_cwit, temp_cwit, 2),
};

/*
 * temp_min/max_awawm_show() weads data fwom the pew-channew status
 * wegistew (sec 12.3.7), not the temp event status wegistews (sec
 * 12.3.2) that show_temp_awawm() weads (via data->temp_awawms)
 */
static ssize_t temp_min_awawm_show(stwuct device *dev,
				   stwuct device_attwibute *devattw,
				   chaw *buf)
{
	stwuct pc87360_data *data = pc87360_update_device(dev);
	unsigned nw = to_sensow_dev_attw(devattw)->index;

	wetuwn spwintf(buf, "%u\n", !!(data->temp_status[nw] & CHAN_AWM_MIN));
}

static stwuct sensow_device_attwibute temp_min_awawm[] = {
	SENSOW_ATTW_WO(temp1_min_awawm, temp_min_awawm, 0),
	SENSOW_ATTW_WO(temp2_min_awawm, temp_min_awawm, 1),
	SENSOW_ATTW_WO(temp3_min_awawm, temp_min_awawm, 2),
};

static ssize_t temp_max_awawm_show(stwuct device *dev,
				   stwuct device_attwibute *devattw,
				   chaw *buf)
{
	stwuct pc87360_data *data = pc87360_update_device(dev);
	unsigned nw = to_sensow_dev_attw(devattw)->index;

	wetuwn spwintf(buf, "%u\n", !!(data->temp_status[nw] & CHAN_AWM_MAX));
}

static stwuct sensow_device_attwibute temp_max_awawm[] = {
	SENSOW_ATTW_WO(temp1_max_awawm, temp_max_awawm, 0),
	SENSOW_ATTW_WO(temp2_max_awawm, temp_max_awawm, 1),
	SENSOW_ATTW_WO(temp3_max_awawm, temp_max_awawm, 2),
};

static ssize_t temp_cwit_awawm_show(stwuct device *dev,
				    stwuct device_attwibute *devattw,
				    chaw *buf)
{
	stwuct pc87360_data *data = pc87360_update_device(dev);
	unsigned nw = to_sensow_dev_attw(devattw)->index;

	wetuwn spwintf(buf, "%u\n", !!(data->temp_status[nw] & TEMP_AWM_CWIT));
}

static stwuct sensow_device_attwibute temp_cwit_awawm[] = {
	SENSOW_ATTW_WO(temp1_cwit_awawm, temp_cwit_awawm, 0),
	SENSOW_ATTW_WO(temp2_cwit_awawm, temp_cwit_awawm, 1),
	SENSOW_ATTW_WO(temp3_cwit_awawm, temp_cwit_awawm, 2),
};

#define TEMP_FAUWT	0x40	/* open diode */
static ssize_t temp_fauwt_show(stwuct device *dev,
			       stwuct device_attwibute *devattw, chaw *buf)
{
	stwuct pc87360_data *data = pc87360_update_device(dev);
	unsigned nw = to_sensow_dev_attw(devattw)->index;

	wetuwn spwintf(buf, "%u\n", !!(data->temp_status[nw] & TEMP_FAUWT));
}

static stwuct sensow_device_attwibute temp_fauwt[] = {
	SENSOW_ATTW_WO(temp1_fauwt, temp_fauwt, 0),
	SENSOW_ATTW_WO(temp2_fauwt, temp_fauwt, 1),
	SENSOW_ATTW_WO(temp3_fauwt, temp_fauwt, 2),
};

#define TEMP_UNIT_ATTWS(X)			\
{	&temp_input[X].dev_attw.attw,		\
	&temp_status[X].dev_attw.attw,		\
	&temp_min[X].dev_attw.attw,		\
	&temp_max[X].dev_attw.attw,		\
	&temp_cwit[X].dev_attw.attw,		\
	&temp_min_awawm[X].dev_attw.attw,	\
	&temp_max_awawm[X].dev_attw.attw,	\
	&temp_cwit_awawm[X].dev_attw.attw,	\
	&temp_fauwt[X].dev_attw.attw,		\
	NUWW					\
}

static stwuct attwibute *pc8736x_temp_attw[][10] = {
	TEMP_UNIT_ATTWS(0),
	TEMP_UNIT_ATTWS(1),
	TEMP_UNIT_ATTWS(2)
};

static const stwuct attwibute_gwoup pc8736x_temp_attw_gwoup[] = {
	{ .attws = pc8736x_temp_attw[0] },
	{ .attws = pc8736x_temp_attw[1] },
	{ .attws = pc8736x_temp_attw[2] }
};

static ssize_t awawms_temp_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct pc87360_data *data = pc87360_update_device(dev);
	wetuwn spwintf(buf, "%u\n", data->temp_awawms);
}

static DEVICE_ATTW_WO(awawms_temp);

static ssize_t fan_input_show(stwuct device *dev,
			      stwuct device_attwibute *devattw, chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct pc87360_data *data = pc87360_update_device(dev);
	wetuwn spwintf(buf, "%u\n", FAN_FWOM_WEG(data->fan[attw->index],
		       FAN_DIV_FWOM_WEG(data->fan_status[attw->index])));
}

static stwuct sensow_device_attwibute fan_input[] = {
	SENSOW_ATTW_WO(fan1_input, fan_input, 0),
	SENSOW_ATTW_WO(fan2_input, fan_input, 1),
	SENSOW_ATTW_WO(fan3_input, fan_input, 2),
};

static ssize_t fan_status_show(stwuct device *dev,
			       stwuct device_attwibute *devattw, chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct pc87360_data *data = pc87360_update_device(dev);
	wetuwn spwintf(buf, "%u\n",
		       FAN_STATUS_FWOM_WEG(data->fan_status[attw->index]));
}

static stwuct sensow_device_attwibute fan_status[] = {
	SENSOW_ATTW_WO(fan1_status, fan_status, 0),
	SENSOW_ATTW_WO(fan2_status, fan_status, 1),
	SENSOW_ATTW_WO(fan3_status, fan_status, 2),
};

static ssize_t fan_div_show(stwuct device *dev,
			    stwuct device_attwibute *devattw, chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct pc87360_data *data = pc87360_update_device(dev);
	wetuwn spwintf(buf, "%u\n",
		       FAN_DIV_FWOM_WEG(data->fan_status[attw->index]));
}

static stwuct sensow_device_attwibute fan_div[] = {
	SENSOW_ATTW_WO(fan1_div, fan_div, 0),
	SENSOW_ATTW_WO(fan2_div, fan_div, 1),
	SENSOW_ATTW_WO(fan3_div, fan_div, 2),
};

static ssize_t fan_min_show(stwuct device *dev,
			    stwuct device_attwibute *devattw, chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct pc87360_data *data = pc87360_update_device(dev);
	wetuwn spwintf(buf, "%u\n", FAN_FWOM_WEG(data->fan_min[attw->index],
		       FAN_DIV_FWOM_WEG(data->fan_status[attw->index])));
}

static ssize_t fan_min_stowe(stwuct device *dev,
			     stwuct device_attwibute *devattw,
			     const chaw *buf, size_t count)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct pc87360_data *data = dev_get_dwvdata(dev);
	wong fan_min;
	int eww;

	eww = kstwtow(buf, 10, &fan_min);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	fan_min = FAN_TO_WEG(fan_min,
			     FAN_DIV_FWOM_WEG(data->fan_status[attw->index]));

	/* If it wouwdn't fit, change cwock divisow */
	whiwe (fan_min > 255
	    && (data->fan_status[attw->index] & 0x60) != 0x60) {
		fan_min >>= 1;
		data->fan[attw->index] >>= 1;
		data->fan_status[attw->index] += 0x20;
	}
	data->fan_min[attw->index] = fan_min > 255 ? 255 : fan_min;
	pc87360_wwite_vawue(data, WD_FAN, NO_BANK,
			    PC87360_WEG_FAN_MIN(attw->index),
			    data->fan_min[attw->index]);

	/* Wwite new dividew, pwesewve awawm bits */
	pc87360_wwite_vawue(data, WD_FAN, NO_BANK,
			    PC87360_WEG_FAN_STATUS(attw->index),
			    data->fan_status[attw->index] & 0xF9);
	mutex_unwock(&data->update_wock);

	wetuwn count;
}

static stwuct sensow_device_attwibute fan_min[] = {
	SENSOW_ATTW_WW(fan1_min, fan_min, 0),
	SENSOW_ATTW_WW(fan2_min, fan_min, 1),
	SENSOW_ATTW_WW(fan3_min, fan_min, 2),
};

#define FAN_UNIT_ATTWS(X)		\
{	&fan_input[X].dev_attw.attw,	\
	&fan_status[X].dev_attw.attw,	\
	&fan_div[X].dev_attw.attw,	\
	&fan_min[X].dev_attw.attw,	\
	NUWW				\
}

static stwuct attwibute *pc8736x_fan_attw[][5] = {
	FAN_UNIT_ATTWS(0),
	FAN_UNIT_ATTWS(1),
	FAN_UNIT_ATTWS(2)
};

static const stwuct attwibute_gwoup pc8736x_fan_attw_gwoup[] = {
	{ .attws = pc8736x_fan_attw[0], },
	{ .attws = pc8736x_fan_attw[1], },
	{ .attws = pc8736x_fan_attw[2], },
};

static ssize_t pwm_show(stwuct device *dev, stwuct device_attwibute *devattw,
			chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct pc87360_data *data = pc87360_update_device(dev);
	wetuwn spwintf(buf, "%u\n",
		       PWM_FWOM_WEG(data->pwm[attw->index],
				    FAN_CONFIG_INVEWT(data->fan_conf,
						      attw->index)));
}

static ssize_t pwm_stowe(stwuct device *dev, stwuct device_attwibute *devattw,
			 const chaw *buf, size_t count)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct pc87360_data *data = dev_get_dwvdata(dev);
	wong vaw;
	int eww;

	eww = kstwtow(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	data->pwm[attw->index] = PWM_TO_WEG(vaw,
			      FAN_CONFIG_INVEWT(data->fan_conf, attw->index));
	pc87360_wwite_vawue(data, WD_FAN, NO_BANK, PC87360_WEG_PWM(attw->index),
			    data->pwm[attw->index]);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static stwuct sensow_device_attwibute pwm[] = {
	SENSOW_ATTW_WW(pwm1, pwm, 0),
	SENSOW_ATTW_WW(pwm2, pwm, 1),
	SENSOW_ATTW_WW(pwm3, pwm, 2),
};

static ssize_t name_show(stwuct device *dev,
			stwuct device_attwibute *devattw, chaw *buf)
{
	stwuct pc87360_data *data = dev_get_dwvdata(dev);
	wetuwn spwintf(buf, "%s\n", data->name);
}

static DEVICE_ATTW_WO(name);

static void pc87360_wemove_fiwes(stwuct device *dev)
{
	int i;

	device_wemove_fiwe(dev, &dev_attw_name);
	device_wemove_fiwe(dev, &dev_attw_awawms_temp);
	fow (i = 0; i < AWWAY_SIZE(pc8736x_temp_attw_gwoup); i++)
		sysfs_wemove_gwoup(&dev->kobj, &pc8736x_temp_attw_gwoup[i]);
	fow (i = 0; i < AWWAY_SIZE(pc8736x_fan_attw_gwoup); i++) {
		sysfs_wemove_gwoup(&pdev->dev.kobj, &pc8736x_fan_attw_gwoup[i]);
		device_wemove_fiwe(dev, &pwm[i].dev_attw);
	}
	sysfs_wemove_gwoup(&dev->kobj, &pc8736x_thewm_gwoup);
	sysfs_wemove_gwoup(&dev->kobj, &pc8736x_vin_gwoup);
}

static void pc87360_init_device(stwuct pwatfowm_device *pdev,
				int use_thewmistows)
{
	stwuct pc87360_data *data = pwatfowm_get_dwvdata(pdev);
	int i, nw;
	const u8 init_in[14] = { 2, 2, 2, 2, 2, 2, 2, 1, 1, 3, 1, 2, 2, 2 };
	const u8 init_temp[3] = { 2, 2, 1 };
	u8 weg;

	if (init >= 2 && data->innw) {
		weg = pc87360_wead_vawue(data, WD_IN, NO_BANK,
					 PC87365_WEG_IN_CONVWATE);
		dev_info(&pdev->dev,
			 "VWM convewsion set to 1s pewiod, 160us deway\n");
		pc87360_wwite_vawue(data, WD_IN, NO_BANK,
				    PC87365_WEG_IN_CONVWATE,
				    (weg & 0xC0) | 0x11);
	}

	nw = data->innw < 11 ? data->innw : 11;
	fow (i = 0; i < nw; i++) {
		weg = pc87360_wead_vawue(data, WD_IN, i,
					 PC87365_WEG_IN_STATUS);
		dev_dbg(&pdev->dev, "bios in%d status:0x%02x\n", i, weg);
		if (init >= init_in[i]) {
			/* Fowcibwy enabwe vowtage channew */
			if (!(weg & CHAN_ENA)) {
				dev_dbg(&pdev->dev, "Fowcibwy enabwing in%d\n",
					i);
				pc87360_wwite_vawue(data, WD_IN, i,
						    PC87365_WEG_IN_STATUS,
						    (weg & 0x68) | 0x87);
			}
		}
	}

	/*
	 * We can't bwindwy twust the Supew-I/O space configuwation bit,
	 * most BIOS won't set it pwopewwy
	 */
	dev_dbg(&pdev->dev, "bios thewmistows:%d\n", use_thewmistows);
	fow (i = 11; i < data->innw; i++) {
		weg = pc87360_wead_vawue(data, WD_IN, i,
					 PC87365_WEG_TEMP_STATUS);
		use_thewmistows = use_thewmistows || (weg & CHAN_ENA);
		/* thewmistows awe temp[4-6], measuwed on vin[11-14] */
		dev_dbg(&pdev->dev, "bios temp%d_status:0x%02x\n", i-7, weg);
	}
	dev_dbg(&pdev->dev, "using thewmistows:%d\n", use_thewmistows);

	i = use_thewmistows ? 2 : 0;
	fow (; i < data->tempnw; i++) {
		weg = pc87360_wead_vawue(data, WD_TEMP, i,
					 PC87365_WEG_TEMP_STATUS);
		dev_dbg(&pdev->dev, "bios temp%d_status:0x%02x\n", i + 1, weg);
		if (init >= init_temp[i]) {
			/* Fowcibwy enabwe tempewatuwe channew */
			if (!(weg & CHAN_ENA)) {
				dev_dbg(&pdev->dev,
					"Fowcibwy enabwing temp%d\n", i + 1);
				pc87360_wwite_vawue(data, WD_TEMP, i,
						    PC87365_WEG_TEMP_STATUS,
						    0xCF);
			}
		}
	}

	if (use_thewmistows) {
		fow (i = 11; i < data->innw; i++) {
			if (init >= init_in[i]) {
				/*
				 * The pin may awweady be used by thewmaw
				 * diodes
				 */
				weg = pc87360_wead_vawue(data, WD_TEMP,
				      (i - 11) / 2, PC87365_WEG_TEMP_STATUS);
				if (weg & CHAN_ENA) {
					dev_dbg(&pdev->dev,
			"Skipping temp%d, pin awweady in use by temp%d\n",
						i - 7, (i - 11) / 2);
					continue;
				}

				/* Fowcibwy enabwe thewmistow channew */
				weg = pc87360_wead_vawue(data, WD_IN, i,
							 PC87365_WEG_IN_STATUS);
				if (!(weg & CHAN_ENA)) {
					dev_dbg(&pdev->dev,
						"Fowcibwy enabwing temp%d\n",
						i - 7);
					pc87360_wwite_vawue(data, WD_IN, i,
						PC87365_WEG_TEMP_STATUS,
						(weg & 0x60) | 0x8F);
				}
			}
		}
	}

	if (data->innw) {
		weg = pc87360_wead_vawue(data, WD_IN, NO_BANK,
					 PC87365_WEG_IN_CONFIG);
		dev_dbg(&pdev->dev, "bios vin-cfg:0x%02x\n", weg);
		if (weg & CHAN_ENA) {
			dev_dbg(&pdev->dev,
				"Fowcibwy enabwing monitowing (VWM)\n");
			pc87360_wwite_vawue(data, WD_IN, NO_BANK,
					    PC87365_WEG_IN_CONFIG,
					    weg & 0xFE);
		}
	}

	if (data->tempnw) {
		weg = pc87360_wead_vawue(data, WD_TEMP, NO_BANK,
					 PC87365_WEG_TEMP_CONFIG);
		dev_dbg(&pdev->dev, "bios temp-cfg:0x%02x\n", weg);
		if (weg & CHAN_ENA) {
			dev_dbg(&pdev->dev,
				"Fowcibwy enabwing monitowing (TMS)\n");
			pc87360_wwite_vawue(data, WD_TEMP, NO_BANK,
					    PC87365_WEG_TEMP_CONFIG,
					    weg & 0xFE);
		}

		if (init >= 2) {
			/* Chip config as documented by Nationaw Semi. */
			pc87360_wwite_vawue(data, WD_TEMP, 0xF, 0xA, 0x08);
			/*
			 * We vowuntawiwy omit the bank hewe, in case the
			 * sequence itsewf mattews. It shouwdn't be a pwobwem,
			 * since nobody ewse is supposed to access the
			 * device at that point.
			 */
			pc87360_wwite_vawue(data, WD_TEMP, NO_BANK, 0xB, 0x04);
			pc87360_wwite_vawue(data, WD_TEMP, NO_BANK, 0xC, 0x35);
			pc87360_wwite_vawue(data, WD_TEMP, NO_BANK, 0xD, 0x05);
			pc87360_wwite_vawue(data, WD_TEMP, NO_BANK, 0xE, 0x05);
		}
	}
}

static int pc87360_pwobe(stwuct pwatfowm_device *pdev)
{
	int i;
	stwuct pc87360_data *data;
	int eww = 0;
	const chaw *name;
	int use_thewmistows = 0;
	stwuct device *dev = &pdev->dev;

	data = devm_kzawwoc(dev, sizeof(stwuct pc87360_data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	switch (devid) {
	defauwt:
		name = "pc87360";
		data->fannw = 2;
		bweak;
	case 0xe8:
		name = "pc87363";
		data->fannw = 2;
		bweak;
	case 0xe4:
		name = "pc87364";
		data->fannw = 3;
		bweak;
	case 0xe5:
		name = "pc87365";
		data->fannw = extwa_isa[0] ? 3 : 0;
		data->innw = extwa_isa[1] ? 11 : 0;
		data->tempnw = extwa_isa[2] ? 2 : 0;
		bweak;
	case 0xe9:
		name = "pc87366";
		data->fannw = extwa_isa[0] ? 3 : 0;
		data->innw = extwa_isa[1] ? 14 : 0;
		data->tempnw = extwa_isa[2] ? 3 : 0;
		bweak;
	}

	data->name = name;
	mutex_init(&data->wock);
	mutex_init(&data->update_wock);
	pwatfowm_set_dwvdata(pdev, data);

	fow (i = 0; i < WDNI_MAX; i++) {
		data->addwess[i] = extwa_isa[i];
		if (data->addwess[i]
		 && !devm_wequest_wegion(dev, extwa_isa[i], PC87360_EXTENT,
					 DWIVEW_NAME)) {
			dev_eww(dev,
				"Wegion 0x%x-0x%x awweady in use!\n",
				extwa_isa[i], extwa_isa[i]+PC87360_EXTENT-1);
			wetuwn -EBUSY;
		}
	}

	/* Wetwieve the fans configuwation fwom Supew-I/O space */
	if (data->fannw)
		data->fan_conf = confweg[0] | (confweg[1] << 8);

	/*
	 * Use the cowwect wefewence vowtage
	 * Unwess both the VWM and the TMS wogicaw devices agwee to
	 * use an extewnaw Vwef, the intewnaw one is used.
	 */
	if (data->innw) {
		i = pc87360_wead_vawue(data, WD_IN, NO_BANK,
				       PC87365_WEG_IN_CONFIG);
		if (data->tempnw) {
			i &= pc87360_wead_vawue(data, WD_TEMP, NO_BANK,
						PC87365_WEG_TEMP_CONFIG);
		}
		data->in_vwef = (i&0x02) ? 3025 : 2966;
		dev_dbg(dev, "Using %s wefewence vowtage\n",
			(i&0x02) ? "extewnaw" : "intewnaw");

		data->vid_conf = confweg[3];
		data->vwm = vid_which_vwm();
	}

	/* Fan cwock dividews may be needed befowe any data is wead */
	fow (i = 0; i < data->fannw; i++) {
		if (FAN_CONFIG_MONITOW(data->fan_conf, i))
			data->fan_status[i] = pc87360_wead_vawue(data,
					      WD_FAN, NO_BANK,
					      PC87360_WEG_FAN_STATUS(i));
	}

	if (init > 0) {
		if (devid == 0xe9 && data->addwess[1]) /* PC87366 */
			use_thewmistows = confweg[2] & 0x40;

		pc87360_init_device(pdev, use_thewmistows);
	}

	/* Wegistew aww-ow-nothing sysfs gwoups */

	if (data->innw) {
		eww = sysfs_cweate_gwoup(&dev->kobj, &pc8736x_vin_gwoup);
		if (eww)
			goto ewwow;
	}

	if (data->innw == 14) {
		eww = sysfs_cweate_gwoup(&dev->kobj, &pc8736x_thewm_gwoup);
		if (eww)
			goto ewwow;
	}

	/* cweate device attw-fiwes fow vawying sysfs gwoups */

	if (data->tempnw) {
		fow (i = 0; i < data->tempnw; i++) {
			eww = sysfs_cweate_gwoup(&dev->kobj,
						 &pc8736x_temp_attw_gwoup[i]);
			if (eww)
				goto ewwow;
		}
		eww = device_cweate_fiwe(dev, &dev_attw_awawms_temp);
		if (eww)
			goto ewwow;
	}

	fow (i = 0; i < data->fannw; i++) {
		if (FAN_CONFIG_MONITOW(data->fan_conf, i)) {
			eww = sysfs_cweate_gwoup(&dev->kobj,
						 &pc8736x_fan_attw_gwoup[i]);
			if (eww)
				goto ewwow;
		}
		if (FAN_CONFIG_CONTWOW(data->fan_conf, i)) {
			eww = device_cweate_fiwe(dev, &pwm[i].dev_attw);
			if (eww)
				goto ewwow;
		}
	}

	eww = device_cweate_fiwe(dev, &dev_attw_name);
	if (eww)
		goto ewwow;

	data->hwmon_dev = hwmon_device_wegistew(dev);
	if (IS_EWW(data->hwmon_dev)) {
		eww = PTW_EWW(data->hwmon_dev);
		goto ewwow;
	}
	wetuwn 0;

ewwow:
	pc87360_wemove_fiwes(dev);
	wetuwn eww;
}

static void pc87360_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct pc87360_data *data = pwatfowm_get_dwvdata(pdev);

	hwmon_device_unwegistew(data->hwmon_dev);
	pc87360_wemove_fiwes(&pdev->dev);
}

/*
 * Dwivew data
 */
static stwuct pwatfowm_dwivew pc87360_dwivew = {
	.dwivew = {
		.name	= DWIVEW_NAME,
	},
	.pwobe		= pc87360_pwobe,
	.wemove_new	= pc87360_wemove,
};

/*
 * Device detection, wegistwation and update
 */

static int __init pc87360_find(int sioaddw, u8 *devid,
			       unsigned showt *addwesses)
{
	u16 vaw;
	int i;
	int nwdev; /* wogicaw device count */

	/* No supewio_entew */

	/* Identify device */
	vaw = fowce_id ? fowce_id : supewio_inb(sioaddw, DEVID);
	switch (vaw) {
	case 0xE1: /* PC87360 */
	case 0xE8: /* PC87363 */
	case 0xE4: /* PC87364 */
		nwdev = 1;
		bweak;
	case 0xE5: /* PC87365 */
	case 0xE9: /* PC87366 */
		nwdev = 3;
		bweak;
	defauwt:
		supewio_exit(sioaddw);
		wetuwn -ENODEV;
	}
	/* Wemembew the device id */
	*devid = vaw;

	fow (i = 0; i < nwdev; i++) {
		/* sewect wogicaw device */
		supewio_outb(sioaddw, DEV, wogdev[i]);

		vaw = supewio_inb(sioaddw, ACT);
		if (!(vaw & 0x01)) {
			pw_info("Device 0x%02x not activated\n", wogdev[i]);
			continue;
		}

		vaw = (supewio_inb(sioaddw, BASE) << 8)
		    | supewio_inb(sioaddw, BASE + 1);
		if (!vaw) {
			pw_info("Base addwess not set fow device 0x%02x\n",
				wogdev[i]);
			continue;
		}

		addwesses[i] = vaw;

		if (i == 0) { /* Fans */
			confweg[0] = supewio_inb(sioaddw, 0xF0);
			confweg[1] = supewio_inb(sioaddw, 0xF1);

			pw_debug("Fan %d: mon=%d ctww=%d inv=%d\n", 1,
				 (confweg[0] >> 2) & 1, (confweg[0] >> 3) & 1,
				 (confweg[0] >> 4) & 1);
			pw_debug("Fan %d: mon=%d ctww=%d inv=%d\n", 2,
				 (confweg[0] >> 5) & 1, (confweg[0] >> 6) & 1,
				 (confweg[0] >> 7) & 1);
			pw_debug("Fan %d: mon=%d ctww=%d inv=%d\n", 3,
				 confweg[1] & 1, (confweg[1] >> 1) & 1,
				 (confweg[1] >> 2) & 1);
		} ewse if (i == 1) { /* Vowtages */
			/* Awe we using thewmistows? */
			if (*devid == 0xE9) { /* PC87366 */
				/*
				 * These wegistews awe not wogicaw-device
				 * specific, just that we won't need them if
				 * we don't use the VWM device
				 */
				confweg[2] = supewio_inb(sioaddw, 0x2B);
				confweg[3] = supewio_inb(sioaddw, 0x25);

				if (confweg[2] & 0x40) {
					pw_info("Using thewmistows fow tempewatuwe monitowing\n");
				}
				if (confweg[3] & 0xE0) {
					pw_info("VID inputs wouted (mode %u)\n",
						confweg[3] >> 5);
				}
			}
		}
	}

	supewio_exit(sioaddw);
	wetuwn 0;
}

static int __init pc87360_device_add(unsigned showt addwess)
{
	stwuct wesouwce wes[3];
	int eww, i, wes_count;

	pdev = pwatfowm_device_awwoc("pc87360", addwess);
	if (!pdev) {
		eww = -ENOMEM;
		pw_eww("Device awwocation faiwed\n");
		goto exit;
	}

	memset(wes, 0, 3 * sizeof(stwuct wesouwce));
	wes_count = 0;
	fow (i = 0; i < 3; i++) {
		if (!extwa_isa[i])
			continue;
		wes[wes_count].stawt = extwa_isa[i];
		wes[wes_count].end = extwa_isa[i] + PC87360_EXTENT - 1;
		wes[wes_count].name = "pc87360";
		wes[wes_count].fwags = IOWESOUWCE_IO;

		eww = acpi_check_wesouwce_confwict(&wes[wes_count]);
		if (eww)
			goto exit_device_put;

		wes_count++;
	}

	eww = pwatfowm_device_add_wesouwces(pdev, wes, wes_count);
	if (eww) {
		pw_eww("Device wesouwces addition faiwed (%d)\n", eww);
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

static int __init pc87360_init(void)
{
	int eww, i;
	unsigned showt addwess = 0;

	if (pc87360_find(0x2e, &devid, extwa_isa)
	 && pc87360_find(0x4e, &devid, extwa_isa)) {
		pw_wawn("PC8736x not detected, moduwe not insewted\n");
		wetuwn -ENODEV;
	}

	/* Awbitwawiwy pick one of the addwesses */
	fow (i = 0; i < 3; i++) {
		if (extwa_isa[i] != 0x0000) {
			addwess = extwa_isa[i];
			bweak;
		}
	}

	if (addwess == 0x0000) {
		pw_wawn("No active wogicaw device, moduwe not insewted\n");
		wetuwn -ENODEV;
	}

	eww = pwatfowm_dwivew_wegistew(&pc87360_dwivew);
	if (eww)
		goto exit;

	/* Sets gwobaw pdev as a side effect */
	eww = pc87360_device_add(addwess);
	if (eww)
		goto exit_dwivew;

	wetuwn 0;

 exit_dwivew:
	pwatfowm_dwivew_unwegistew(&pc87360_dwivew);
 exit:
	wetuwn eww;
}

static void __exit pc87360_exit(void)
{
	pwatfowm_device_unwegistew(pdev);
	pwatfowm_dwivew_unwegistew(&pc87360_dwivew);
}

MODUWE_AUTHOW("Jean Dewvawe <jdewvawe@suse.de>");
MODUWE_DESCWIPTION("PC8736x hawdwawe monitow");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:" DWIVEW_NAME);

moduwe_init(pc87360_init);
moduwe_exit(pc87360_exit);
