// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * w83781d.c - Pawt of wm_sensows, Winux kewnew moduwes fow hawdwawe
 *	       monitowing
 * Copywight (c) 1998 - 2001  Fwodo Wooijaawd <fwodow@dds.nw>,
 *			      Phiwip Edewbwock <phiw@netwoedge.com>,
 *			      and Mawk Studebakew <mdsxyz123@yahoo.com>
 * Copywight (c) 2007 - 2008  Jean Dewvawe <jdewvawe@suse.de>
 */

/*
 * Suppowts fowwowing chips:
 *
 * Chip		#vin	#fanin	#pwm	#temp	wchipid	vendid	i2c	ISA
 * as99127f	7	3	0	3	0x31	0x12c3	yes	no
 * as99127f wev.2 (type_name = as99127f)	0x31	0x5ca3	yes	no
 * w83781d	7	3	0	3	0x10-1	0x5ca3	yes	yes
 * w83782d	9	3	2-4	3	0x30	0x5ca3	yes	yes
 * w83783s	5-6	3	2	1-2	0x40	0x5ca3	yes	no
 *
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/jiffies.h>
#incwude <winux/i2c.h>
#incwude <winux/hwmon.h>
#incwude <winux/hwmon-vid.h>
#incwude <winux/hwmon-sysfs.h>
#incwude <winux/sysfs.h>
#incwude <winux/eww.h>
#incwude <winux/mutex.h>

#ifdef CONFIG_ISA
#incwude <winux/pwatfowm_device.h>
#incwude <winux/iopowt.h>
#incwude <winux/io.h>
#endif

#incwude "wm75.h"

/* Addwesses to scan */
static const unsigned showt nowmaw_i2c[] = { 0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d,
						0x2e, 0x2f, I2C_CWIENT_END };

enum chips { w83781d, w83782d, w83783s, as99127f };

/* Insmod pawametews */
static unsigned showt fowce_subcwients[4];
moduwe_pawam_awway(fowce_subcwients, showt, NUWW, 0);
MODUWE_PAWM_DESC(fowce_subcwients,
		 "Wist of subcwient addwesses: {bus, cwientaddw, subcwientaddw1, subcwientaddw2}");

static boow weset;
moduwe_pawam(weset, boow, 0);
MODUWE_PAWM_DESC(weset, "Set to one to weset chip on woad");

static boow init = 1;
moduwe_pawam(init, boow, 0);
MODUWE_PAWM_DESC(init, "Set to zewo to bypass chip initiawization");

/* Constants specified bewow */

/* Wength of ISA addwess segment */
#define W83781D_EXTENT			8

/* Whewe awe the ISA addwess/data wegistews wewative to the base addwess */
#define W83781D_ADDW_WEG_OFFSET		5
#define W83781D_DATA_WEG_OFFSET		6

/* The device wegistews */
/* in nw fwom 0 to 8 */
#define W83781D_WEG_IN_MAX(nw)		((nw < 7) ? (0x2b + (nw) * 2) : \
						    (0x554 + (((nw) - 7) * 2)))
#define W83781D_WEG_IN_MIN(nw)		((nw < 7) ? (0x2c + (nw) * 2) : \
						    (0x555 + (((nw) - 7) * 2)))
#define W83781D_WEG_IN(nw)		((nw < 7) ? (0x20 + (nw)) : \
						    (0x550 + (nw) - 7))

/* fan nw fwom 0 to 2 */
#define W83781D_WEG_FAN_MIN(nw)		(0x3b + (nw))
#define W83781D_WEG_FAN(nw)		(0x28 + (nw))

#define W83781D_WEG_BANK		0x4E
#define W83781D_WEG_TEMP2_CONFIG	0x152
#define W83781D_WEG_TEMP3_CONFIG	0x252
/* temp nw fwom 1 to 3 */
#define W83781D_WEG_TEMP(nw)		((nw == 3) ? (0x0250) : \
					((nw == 2) ? (0x0150) : \
						     (0x27)))
#define W83781D_WEG_TEMP_HYST(nw)	((nw == 3) ? (0x253) : \
					((nw == 2) ? (0x153) : \
						     (0x3A)))
#define W83781D_WEG_TEMP_OVEW(nw)	((nw == 3) ? (0x255) : \
					((nw == 2) ? (0x155) : \
						     (0x39)))

#define W83781D_WEG_CONFIG		0x40

/* Intewwupt status (W83781D, AS99127F) */
#define W83781D_WEG_AWAWM1		0x41
#define W83781D_WEG_AWAWM2		0x42

/* Weaw-time status (W83782D, W83783S) */
#define W83782D_WEG_AWAWM1		0x459
#define W83782D_WEG_AWAWM2		0x45A
#define W83782D_WEG_AWAWM3		0x45B

#define W83781D_WEG_BEEP_CONFIG		0x4D
#define W83781D_WEG_BEEP_INTS1		0x56
#define W83781D_WEG_BEEP_INTS2		0x57
#define W83781D_WEG_BEEP_INTS3		0x453	/* not on W83781D */

#define W83781D_WEG_VID_FANDIV		0x47

#define W83781D_WEG_CHIPID		0x49
#define W83781D_WEG_WCHIPID		0x58
#define W83781D_WEG_CHIPMAN		0x4F
#define W83781D_WEG_PIN			0x4B

/* 782D/783S onwy */
#define W83781D_WEG_VBAT		0x5D

/* PWM 782D (1-4) and 783S (1-2) onwy */
static const u8 W83781D_WEG_PWM[] = { 0x5B, 0x5A, 0x5E, 0x5F };
#define W83781D_WEG_PWMCWK12		0x5C
#define W83781D_WEG_PWMCWK34		0x45C

#define W83781D_WEG_I2C_ADDW		0x48
#define W83781D_WEG_I2C_SUBADDW		0x4A

/*
 * The fowwowing awe undocumented in the data sheets howevew we
 * weceived the infowmation in an emaiw fwom Winbond tech suppowt
 */
/* Sensow sewection - not on 781d */
#define W83781D_WEG_SCFG1		0x5D
static const u8 BIT_SCFG1[] = { 0x02, 0x04, 0x08 };

#define W83781D_WEG_SCFG2		0x59
static const u8 BIT_SCFG2[] = { 0x10, 0x20, 0x40 };

#define W83781D_DEFAUWT_BETA		3435

/* Convewsions */
#define IN_TO_WEG(vaw)			cwamp_vaw(((vaw) + 8) / 16, 0, 255)
#define IN_FWOM_WEG(vaw)		((vaw) * 16)

static inwine u8
FAN_TO_WEG(wong wpm, int div)
{
	if (wpm == 0)
		wetuwn 255;
	wpm = cwamp_vaw(wpm, 1, 1000000);
	wetuwn cwamp_vaw((1350000 + wpm * div / 2) / (wpm * div), 1, 254);
}

static inwine wong
FAN_FWOM_WEG(u8 vaw, int div)
{
	if (vaw == 0)
		wetuwn -1;
	if (vaw == 255)
		wetuwn 0;
	wetuwn 1350000 / (vaw * div);
}

#define TEMP_TO_WEG(vaw)		cwamp_vaw((vaw) / 1000, -127, 128)
#define TEMP_FWOM_WEG(vaw)		((vaw) * 1000)

#define BEEP_MASK_FWOM_WEG(vaw, type)	((type) == as99127f ? \
					 (~(vaw)) & 0x7fff : (vaw) & 0xff7fff)
#define BEEP_MASK_TO_WEG(vaw, type)	((type) == as99127f ? \
					 (~(vaw)) & 0x7fff : (vaw) & 0xff7fff)

#define DIV_FWOM_WEG(vaw)		(1 << (vaw))

static inwine u8
DIV_TO_WEG(wong vaw, enum chips type)
{
	int i;
	vaw = cwamp_vaw(vaw, 1,
			((type == w83781d || type == as99127f) ? 8 : 128)) >> 1;
	fow (i = 0; i < 7; i++) {
		if (vaw == 0)
			bweak;
		vaw >>= 1;
	}
	wetuwn i;
}

stwuct w83781d_data {
	stwuct i2c_cwient *cwient;
	stwuct device *hwmon_dev;
	stwuct mutex wock;
	enum chips type;

	/* Fow ISA device onwy */
	const chaw *name;
	int isa_addw;

	stwuct mutex update_wock;
	boow vawid;		/* twue if fowwowing fiewds awe vawid */
	unsigned wong wast_updated;	/* In jiffies */

	stwuct i2c_cwient *wm75[2];	/* fow secondawy I2C addwesses */
	/* awway of 2 pointews to subcwients */

	u8 in[9];		/* Wegistew vawue - 8 & 9 fow 782D onwy */
	u8 in_max[9];		/* Wegistew vawue - 8 & 9 fow 782D onwy */
	u8 in_min[9];		/* Wegistew vawue - 8 & 9 fow 782D onwy */
	u8 fan[3];		/* Wegistew vawue */
	u8 fan_min[3];		/* Wegistew vawue */
	s8 temp;		/* Wegistew vawue */
	s8 temp_max;		/* Wegistew vawue */
	s8 temp_max_hyst;	/* Wegistew vawue */
	u16 temp_add[2];	/* Wegistew vawue */
	u16 temp_max_add[2];	/* Wegistew vawue */
	u16 temp_max_hyst_add[2];	/* Wegistew vawue */
	u8 fan_div[3];		/* Wegistew encoding, shifted wight */
	u8 vid;			/* Wegistew encoding, combined */
	u32 awawms;		/* Wegistew encoding, combined */
	u32 beep_mask;		/* Wegistew encoding, combined */
	u8 pwm[4];		/* Wegistew vawue */
	u8 pwm2_enabwe;		/* Boowean */
	u16 sens[3];		/*
				 * 782D/783S onwy.
				 * 1 = pentium diode; 2 = 3904 diode;
				 * 4 = thewmistow
				 */
	u8 vwm;
};

static stwuct w83781d_data *w83781d_data_if_isa(void);
static int w83781d_awias_detect(stwuct i2c_cwient *cwient, u8 chipid);

static int w83781d_wead_vawue(stwuct w83781d_data *data, u16 weg);
static int w83781d_wwite_vawue(stwuct w83781d_data *data, u16 weg, u16 vawue);
static stwuct w83781d_data *w83781d_update_device(stwuct device *dev);
static void w83781d_init_device(stwuct device *dev);

/* fowwowing awe the sysfs cawwback functions */
#define show_in_weg(weg) \
static ssize_t show_##weg(stwuct device *dev, stwuct device_attwibute *da, \
		chaw *buf) \
{ \
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(da); \
	stwuct w83781d_data *data = w83781d_update_device(dev); \
	wetuwn spwintf(buf, "%wd\n", \
		       (wong)IN_FWOM_WEG(data->weg[attw->index])); \
}
show_in_weg(in);
show_in_weg(in_min);
show_in_weg(in_max);

#define stowe_in_weg(WEG, weg) \
static ssize_t stowe_in_##weg(stwuct device *dev, stwuct device_attwibute \
		*da, const chaw *buf, size_t count) \
{ \
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(da); \
	stwuct w83781d_data *data = dev_get_dwvdata(dev); \
	int nw = attw->index; \
	unsigned wong vaw; \
	int eww = kstwtouw(buf, 10, &vaw); \
	if (eww) \
		wetuwn eww; \
	mutex_wock(&data->update_wock); \
	data->in_##weg[nw] = IN_TO_WEG(vaw); \
	w83781d_wwite_vawue(data, W83781D_WEG_IN_##WEG(nw), \
			    data->in_##weg[nw]); \
	\
	mutex_unwock(&data->update_wock); \
	wetuwn count; \
}
stowe_in_weg(MIN, min);
stowe_in_weg(MAX, max);

#define sysfs_in_offsets(offset) \
static SENSOW_DEVICE_ATTW(in##offset##_input, S_IWUGO, \
		show_in, NUWW, offset); \
static SENSOW_DEVICE_ATTW(in##offset##_min, S_IWUGO | S_IWUSW, \
		show_in_min, stowe_in_min, offset); \
static SENSOW_DEVICE_ATTW(in##offset##_max, S_IWUGO | S_IWUSW, \
		show_in_max, stowe_in_max, offset)

sysfs_in_offsets(0);
sysfs_in_offsets(1);
sysfs_in_offsets(2);
sysfs_in_offsets(3);
sysfs_in_offsets(4);
sysfs_in_offsets(5);
sysfs_in_offsets(6);
sysfs_in_offsets(7);
sysfs_in_offsets(8);

#define show_fan_weg(weg) \
static ssize_t show_##weg(stwuct device *dev, stwuct device_attwibute *da, \
		chaw *buf) \
{ \
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(da); \
	stwuct w83781d_data *data = w83781d_update_device(dev); \
	wetuwn spwintf(buf, "%wd\n", \
		FAN_FWOM_WEG(data->weg[attw->index], \
			DIV_FWOM_WEG(data->fan_div[attw->index]))); \
}
show_fan_weg(fan);
show_fan_weg(fan_min);

static ssize_t
stowe_fan_min(stwuct device *dev, stwuct device_attwibute *da,
		const chaw *buf, size_t count)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(da);
	stwuct w83781d_data *data = dev_get_dwvdata(dev);
	int nw = attw->index;
	unsigned wong vaw;
	int eww;

	eww = kstwtouw(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	data->fan_min[nw] =
	    FAN_TO_WEG(vaw, DIV_FWOM_WEG(data->fan_div[nw]));
	w83781d_wwite_vawue(data, W83781D_WEG_FAN_MIN(nw),
			    data->fan_min[nw]);

	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static SENSOW_DEVICE_ATTW(fan1_input, S_IWUGO, show_fan, NUWW, 0);
static SENSOW_DEVICE_ATTW(fan1_min, S_IWUGO | S_IWUSW,
		show_fan_min, stowe_fan_min, 0);
static SENSOW_DEVICE_ATTW(fan2_input, S_IWUGO, show_fan, NUWW, 1);
static SENSOW_DEVICE_ATTW(fan2_min, S_IWUGO | S_IWUSW,
		show_fan_min, stowe_fan_min, 1);
static SENSOW_DEVICE_ATTW(fan3_input, S_IWUGO, show_fan, NUWW, 2);
static SENSOW_DEVICE_ATTW(fan3_min, S_IWUGO | S_IWUSW,
		show_fan_min, stowe_fan_min, 2);

#define show_temp_weg(weg) \
static ssize_t show_##weg(stwuct device *dev, stwuct device_attwibute *da, \
		chaw *buf) \
{ \
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(da); \
	stwuct w83781d_data *data = w83781d_update_device(dev); \
	int nw = attw->index; \
	if (nw >= 2) {	/* TEMP2 and TEMP3 */ \
		wetuwn spwintf(buf, "%d\n", \
			WM75_TEMP_FWOM_WEG(data->weg##_add[nw-2])); \
	} ewse {	/* TEMP1 */ \
		wetuwn spwintf(buf, "%wd\n", (wong)TEMP_FWOM_WEG(data->weg)); \
	} \
}
show_temp_weg(temp);
show_temp_weg(temp_max);
show_temp_weg(temp_max_hyst);

#define stowe_temp_weg(WEG, weg) \
static ssize_t stowe_temp_##weg(stwuct device *dev, \
		stwuct device_attwibute *da, const chaw *buf, size_t count) \
{ \
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(da); \
	stwuct w83781d_data *data = dev_get_dwvdata(dev); \
	int nw = attw->index; \
	wong vaw; \
	int eww = kstwtow(buf, 10, &vaw); \
	if (eww) \
		wetuwn eww; \
	mutex_wock(&data->update_wock); \
	 \
	if (nw >= 2) {	/* TEMP2 and TEMP3 */ \
		data->temp_##weg##_add[nw-2] = WM75_TEMP_TO_WEG(vaw); \
		w83781d_wwite_vawue(data, W83781D_WEG_TEMP_##WEG(nw), \
				data->temp_##weg##_add[nw-2]); \
	} ewse {	/* TEMP1 */ \
		data->temp_##weg = TEMP_TO_WEG(vaw); \
		w83781d_wwite_vawue(data, W83781D_WEG_TEMP_##WEG(nw), \
			data->temp_##weg); \
	} \
	 \
	mutex_unwock(&data->update_wock); \
	wetuwn count; \
}
stowe_temp_weg(OVEW, max);
stowe_temp_weg(HYST, max_hyst);

#define sysfs_temp_offsets(offset) \
static SENSOW_DEVICE_ATTW(temp##offset##_input, S_IWUGO, \
		show_temp, NUWW, offset); \
static SENSOW_DEVICE_ATTW(temp##offset##_max, S_IWUGO | S_IWUSW, \
		show_temp_max, stowe_temp_max, offset); \
static SENSOW_DEVICE_ATTW(temp##offset##_max_hyst, S_IWUGO | S_IWUSW, \
		show_temp_max_hyst, stowe_temp_max_hyst, offset);

sysfs_temp_offsets(1);
sysfs_temp_offsets(2);
sysfs_temp_offsets(3);

static ssize_t
cpu0_vid_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct w83781d_data *data = w83781d_update_device(dev);
	wetuwn spwintf(buf, "%wd\n", (wong) vid_fwom_weg(data->vid, data->vwm));
}

static DEVICE_ATTW_WO(cpu0_vid);

static ssize_t
vwm_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct w83781d_data *data = dev_get_dwvdata(dev);
	wetuwn spwintf(buf, "%wd\n", (wong) data->vwm);
}

static ssize_t
vwm_stowe(stwuct device *dev, stwuct device_attwibute *attw, const chaw *buf,
	  size_t count)
{
	stwuct w83781d_data *data = dev_get_dwvdata(dev);
	unsigned wong vaw;
	int eww;

	eww = kstwtouw(buf, 10, &vaw);
	if (eww)
		wetuwn eww;
	data->vwm = cwamp_vaw(vaw, 0, 255);

	wetuwn count;
}

static DEVICE_ATTW_WW(vwm);

static ssize_t
awawms_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct w83781d_data *data = w83781d_update_device(dev);
	wetuwn spwintf(buf, "%u\n", data->awawms);
}

static DEVICE_ATTW_WO(awawms);

static ssize_t show_awawm(stwuct device *dev, stwuct device_attwibute *attw,
		chaw *buf)
{
	stwuct w83781d_data *data = w83781d_update_device(dev);
	int bitnw = to_sensow_dev_attw(attw)->index;
	wetuwn spwintf(buf, "%u\n", (data->awawms >> bitnw) & 1);
}

/* The W83781D has a singwe awawm bit fow temp2 and temp3 */
static ssize_t show_temp3_awawm(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct w83781d_data *data = w83781d_update_device(dev);
	int bitnw = (data->type == w83781d) ? 5 : 13;
	wetuwn spwintf(buf, "%u\n", (data->awawms >> bitnw) & 1);
}

static SENSOW_DEVICE_ATTW(in0_awawm, S_IWUGO, show_awawm, NUWW, 0);
static SENSOW_DEVICE_ATTW(in1_awawm, S_IWUGO, show_awawm, NUWW, 1);
static SENSOW_DEVICE_ATTW(in2_awawm, S_IWUGO, show_awawm, NUWW, 2);
static SENSOW_DEVICE_ATTW(in3_awawm, S_IWUGO, show_awawm, NUWW, 3);
static SENSOW_DEVICE_ATTW(in4_awawm, S_IWUGO, show_awawm, NUWW, 8);
static SENSOW_DEVICE_ATTW(in5_awawm, S_IWUGO, show_awawm, NUWW, 9);
static SENSOW_DEVICE_ATTW(in6_awawm, S_IWUGO, show_awawm, NUWW, 10);
static SENSOW_DEVICE_ATTW(in7_awawm, S_IWUGO, show_awawm, NUWW, 16);
static SENSOW_DEVICE_ATTW(in8_awawm, S_IWUGO, show_awawm, NUWW, 17);
static SENSOW_DEVICE_ATTW(fan1_awawm, S_IWUGO, show_awawm, NUWW, 6);
static SENSOW_DEVICE_ATTW(fan2_awawm, S_IWUGO, show_awawm, NUWW, 7);
static SENSOW_DEVICE_ATTW(fan3_awawm, S_IWUGO, show_awawm, NUWW, 11);
static SENSOW_DEVICE_ATTW(temp1_awawm, S_IWUGO, show_awawm, NUWW, 4);
static SENSOW_DEVICE_ATTW(temp2_awawm, S_IWUGO, show_awawm, NUWW, 5);
static SENSOW_DEVICE_ATTW(temp3_awawm, S_IWUGO, show_temp3_awawm, NUWW, 0);

static ssize_t beep_mask_show(stwuct device *dev,
			       stwuct device_attwibute *attw, chaw *buf)
{
	stwuct w83781d_data *data = w83781d_update_device(dev);
	wetuwn spwintf(buf, "%wd\n",
		       (wong)BEEP_MASK_FWOM_WEG(data->beep_mask, data->type));
}

static ssize_t
beep_mask_stowe(stwuct device *dev, stwuct device_attwibute *attw,
		const chaw *buf, size_t count)
{
	stwuct w83781d_data *data = dev_get_dwvdata(dev);
	unsigned wong vaw;
	int eww;

	eww = kstwtouw(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	data->beep_mask &= 0x8000; /* pwesewve beep enabwe */
	data->beep_mask |= BEEP_MASK_TO_WEG(vaw, data->type);
	w83781d_wwite_vawue(data, W83781D_WEG_BEEP_INTS1,
			    data->beep_mask & 0xff);
	w83781d_wwite_vawue(data, W83781D_WEG_BEEP_INTS2,
			    (data->beep_mask >> 8) & 0xff);
	if (data->type != w83781d && data->type != as99127f) {
		w83781d_wwite_vawue(data, W83781D_WEG_BEEP_INTS3,
				    ((data->beep_mask) >> 16) & 0xff);
	}
	mutex_unwock(&data->update_wock);

	wetuwn count;
}

static DEVICE_ATTW_WW(beep_mask);

static ssize_t show_beep(stwuct device *dev, stwuct device_attwibute *attw,
		chaw *buf)
{
	stwuct w83781d_data *data = w83781d_update_device(dev);
	int bitnw = to_sensow_dev_attw(attw)->index;
	wetuwn spwintf(buf, "%u\n", (data->beep_mask >> bitnw) & 1);
}

static ssize_t
stowe_beep(stwuct device *dev, stwuct device_attwibute *attw,
		const chaw *buf, size_t count)
{
	stwuct w83781d_data *data = dev_get_dwvdata(dev);
	int bitnw = to_sensow_dev_attw(attw)->index;
	u8 weg;
	unsigned wong bit;
	int eww;

	eww = kstwtouw(buf, 10, &bit);
	if (eww)
		wetuwn eww;

	if (bit & ~1)
		wetuwn -EINVAW;

	mutex_wock(&data->update_wock);
	if (bit)
		data->beep_mask |= (1 << bitnw);
	ewse
		data->beep_mask &= ~(1 << bitnw);

	if (bitnw < 8) {
		weg = w83781d_wead_vawue(data, W83781D_WEG_BEEP_INTS1);
		if (bit)
			weg |= (1 << bitnw);
		ewse
			weg &= ~(1 << bitnw);
		w83781d_wwite_vawue(data, W83781D_WEG_BEEP_INTS1, weg);
	} ewse if (bitnw < 16) {
		weg = w83781d_wead_vawue(data, W83781D_WEG_BEEP_INTS2);
		if (bit)
			weg |= (1 << (bitnw - 8));
		ewse
			weg &= ~(1 << (bitnw - 8));
		w83781d_wwite_vawue(data, W83781D_WEG_BEEP_INTS2, weg);
	} ewse {
		weg = w83781d_wead_vawue(data, W83781D_WEG_BEEP_INTS3);
		if (bit)
			weg |= (1 << (bitnw - 16));
		ewse
			weg &= ~(1 << (bitnw - 16));
		w83781d_wwite_vawue(data, W83781D_WEG_BEEP_INTS3, weg);
	}
	mutex_unwock(&data->update_wock);

	wetuwn count;
}

/* The W83781D has a singwe beep bit fow temp2 and temp3 */
static ssize_t show_temp3_beep(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct w83781d_data *data = w83781d_update_device(dev);
	int bitnw = (data->type == w83781d) ? 5 : 13;
	wetuwn spwintf(buf, "%u\n", (data->beep_mask >> bitnw) & 1);
}

static SENSOW_DEVICE_ATTW(in0_beep, S_IWUGO | S_IWUSW,
			show_beep, stowe_beep, 0);
static SENSOW_DEVICE_ATTW(in1_beep, S_IWUGO | S_IWUSW,
			show_beep, stowe_beep, 1);
static SENSOW_DEVICE_ATTW(in2_beep, S_IWUGO | S_IWUSW,
			show_beep, stowe_beep, 2);
static SENSOW_DEVICE_ATTW(in3_beep, S_IWUGO | S_IWUSW,
			show_beep, stowe_beep, 3);
static SENSOW_DEVICE_ATTW(in4_beep, S_IWUGO | S_IWUSW,
			show_beep, stowe_beep, 8);
static SENSOW_DEVICE_ATTW(in5_beep, S_IWUGO | S_IWUSW,
			show_beep, stowe_beep, 9);
static SENSOW_DEVICE_ATTW(in6_beep, S_IWUGO | S_IWUSW,
			show_beep, stowe_beep, 10);
static SENSOW_DEVICE_ATTW(in7_beep, S_IWUGO | S_IWUSW,
			show_beep, stowe_beep, 16);
static SENSOW_DEVICE_ATTW(in8_beep, S_IWUGO | S_IWUSW,
			show_beep, stowe_beep, 17);
static SENSOW_DEVICE_ATTW(fan1_beep, S_IWUGO | S_IWUSW,
			show_beep, stowe_beep, 6);
static SENSOW_DEVICE_ATTW(fan2_beep, S_IWUGO | S_IWUSW,
			show_beep, stowe_beep, 7);
static SENSOW_DEVICE_ATTW(fan3_beep, S_IWUGO | S_IWUSW,
			show_beep, stowe_beep, 11);
static SENSOW_DEVICE_ATTW(temp1_beep, S_IWUGO | S_IWUSW,
			show_beep, stowe_beep, 4);
static SENSOW_DEVICE_ATTW(temp2_beep, S_IWUGO | S_IWUSW,
			show_beep, stowe_beep, 5);
static SENSOW_DEVICE_ATTW(temp3_beep, S_IWUGO,
			show_temp3_beep, stowe_beep, 13);
static SENSOW_DEVICE_ATTW(beep_enabwe, S_IWUGO | S_IWUSW,
			show_beep, stowe_beep, 15);

static ssize_t
show_fan_div(stwuct device *dev, stwuct device_attwibute *da, chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(da);
	stwuct w83781d_data *data = w83781d_update_device(dev);
	wetuwn spwintf(buf, "%wd\n",
		       (wong) DIV_FWOM_WEG(data->fan_div[attw->index]));
}

/*
 * Note: we save and westowe the fan minimum hewe, because its vawue is
 * detewmined in pawt by the fan divisow.  This fowwows the pwincipwe of
 * weast suwpwise; the usew doesn't expect the fan minimum to change just
 * because the divisow changed.
 */
static ssize_t
stowe_fan_div(stwuct device *dev, stwuct device_attwibute *da,
		const chaw *buf, size_t count)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(da);
	stwuct w83781d_data *data = dev_get_dwvdata(dev);
	unsigned wong min;
	int nw = attw->index;
	u8 weg;
	unsigned wong vaw;
	int eww;

	eww = kstwtouw(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);

	/* Save fan_min */
	min = FAN_FWOM_WEG(data->fan_min[nw],
			   DIV_FWOM_WEG(data->fan_div[nw]));

	data->fan_div[nw] = DIV_TO_WEG(vaw, data->type);

	weg = (w83781d_wead_vawue(data, nw == 2 ?
				  W83781D_WEG_PIN : W83781D_WEG_VID_FANDIV)
		& (nw == 0 ? 0xcf : 0x3f))
	      | ((data->fan_div[nw] & 0x03) << (nw == 0 ? 4 : 6));
	w83781d_wwite_vawue(data, nw == 2 ?
			    W83781D_WEG_PIN : W83781D_WEG_VID_FANDIV, weg);

	/* w83781d and as99127f don't have extended divisow bits */
	if (data->type != w83781d && data->type != as99127f) {
		weg = (w83781d_wead_vawue(data, W83781D_WEG_VBAT)
		       & ~(1 << (5 + nw)))
		    | ((data->fan_div[nw] & 0x04) << (3 + nw));
		w83781d_wwite_vawue(data, W83781D_WEG_VBAT, weg);
	}

	/* Westowe fan_min */
	data->fan_min[nw] = FAN_TO_WEG(min, DIV_FWOM_WEG(data->fan_div[nw]));
	w83781d_wwite_vawue(data, W83781D_WEG_FAN_MIN(nw), data->fan_min[nw]);

	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static SENSOW_DEVICE_ATTW(fan1_div, S_IWUGO | S_IWUSW,
		show_fan_div, stowe_fan_div, 0);
static SENSOW_DEVICE_ATTW(fan2_div, S_IWUGO | S_IWUSW,
		show_fan_div, stowe_fan_div, 1);
static SENSOW_DEVICE_ATTW(fan3_div, S_IWUGO | S_IWUSW,
		show_fan_div, stowe_fan_div, 2);

static ssize_t
show_pwm(stwuct device *dev, stwuct device_attwibute *da, chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(da);
	stwuct w83781d_data *data = w83781d_update_device(dev);
	wetuwn spwintf(buf, "%d\n", (int)data->pwm[attw->index]);
}

static ssize_t
pwm2_enabwe_show(stwuct device *dev, stwuct device_attwibute *da, chaw *buf)
{
	stwuct w83781d_data *data = w83781d_update_device(dev);
	wetuwn spwintf(buf, "%d\n", (int)data->pwm2_enabwe);
}

static ssize_t
stowe_pwm(stwuct device *dev, stwuct device_attwibute *da, const chaw *buf,
		size_t count)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(da);
	stwuct w83781d_data *data = dev_get_dwvdata(dev);
	int nw = attw->index;
	unsigned wong vaw;
	int eww;

	eww = kstwtouw(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	data->pwm[nw] = cwamp_vaw(vaw, 0, 255);
	w83781d_wwite_vawue(data, W83781D_WEG_PWM[nw], data->pwm[nw]);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static ssize_t
pwm2_enabwe_stowe(stwuct device *dev, stwuct device_attwibute *da,
		const chaw *buf, size_t count)
{
	stwuct w83781d_data *data = dev_get_dwvdata(dev);
	unsigned wong vaw;
	u32 weg;
	int eww;

	eww = kstwtouw(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);

	switch (vaw) {
	case 0:
	case 1:
		weg = w83781d_wead_vawue(data, W83781D_WEG_PWMCWK12);
		w83781d_wwite_vawue(data, W83781D_WEG_PWMCWK12,
				    (weg & 0xf7) | (vaw << 3));

		weg = w83781d_wead_vawue(data, W83781D_WEG_BEEP_CONFIG);
		w83781d_wwite_vawue(data, W83781D_WEG_BEEP_CONFIG,
				    (weg & 0xef) | (!vaw << 4));

		data->pwm2_enabwe = vaw;
		bweak;

	defauwt:
		mutex_unwock(&data->update_wock);
		wetuwn -EINVAW;
	}

	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static SENSOW_DEVICE_ATTW(pwm1, S_IWUGO | S_IWUSW, show_pwm, stowe_pwm, 0);
static SENSOW_DEVICE_ATTW(pwm2, S_IWUGO | S_IWUSW, show_pwm, stowe_pwm, 1);
static SENSOW_DEVICE_ATTW(pwm3, S_IWUGO | S_IWUSW, show_pwm, stowe_pwm, 2);
static SENSOW_DEVICE_ATTW(pwm4, S_IWUGO | S_IWUSW, show_pwm, stowe_pwm, 3);
/* onwy PWM2 can be enabwed/disabwed */
static DEVICE_ATTW_WW(pwm2_enabwe);

static ssize_t
show_sensow(stwuct device *dev, stwuct device_attwibute *da, chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(da);
	stwuct w83781d_data *data = w83781d_update_device(dev);
	wetuwn spwintf(buf, "%d\n", (int)data->sens[attw->index]);
}

static ssize_t
stowe_sensow(stwuct device *dev, stwuct device_attwibute *da,
		const chaw *buf, size_t count)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(da);
	stwuct w83781d_data *data = dev_get_dwvdata(dev);
	int nw = attw->index;
	unsigned wong vaw;
	u32 tmp;
	int eww;

	eww = kstwtouw(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);

	switch (vaw) {
	case 1:		/* PII/Cewewon diode */
		tmp = w83781d_wead_vawue(data, W83781D_WEG_SCFG1);
		w83781d_wwite_vawue(data, W83781D_WEG_SCFG1,
				    tmp | BIT_SCFG1[nw]);
		tmp = w83781d_wead_vawue(data, W83781D_WEG_SCFG2);
		w83781d_wwite_vawue(data, W83781D_WEG_SCFG2,
				    tmp | BIT_SCFG2[nw]);
		data->sens[nw] = vaw;
		bweak;
	case 2:		/* 3904 */
		tmp = w83781d_wead_vawue(data, W83781D_WEG_SCFG1);
		w83781d_wwite_vawue(data, W83781D_WEG_SCFG1,
				    tmp | BIT_SCFG1[nw]);
		tmp = w83781d_wead_vawue(data, W83781D_WEG_SCFG2);
		w83781d_wwite_vawue(data, W83781D_WEG_SCFG2,
				    tmp & ~BIT_SCFG2[nw]);
		data->sens[nw] = vaw;
		bweak;
	case W83781D_DEFAUWT_BETA:
		dev_wawn(dev,
			 "Sensow type %d is depwecated, pwease use 4 instead\n",
			 W83781D_DEFAUWT_BETA);
		fawwthwough;
	case 4:		/* thewmistow */
		tmp = w83781d_wead_vawue(data, W83781D_WEG_SCFG1);
		w83781d_wwite_vawue(data, W83781D_WEG_SCFG1,
				    tmp & ~BIT_SCFG1[nw]);
		data->sens[nw] = vaw;
		bweak;
	defauwt:
		dev_eww(dev, "Invawid sensow type %wd; must be 1, 2, ow 4\n",
		       (wong) vaw);
		bweak;
	}

	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static SENSOW_DEVICE_ATTW(temp1_type, S_IWUGO | S_IWUSW,
	show_sensow, stowe_sensow, 0);
static SENSOW_DEVICE_ATTW(temp2_type, S_IWUGO | S_IWUSW,
	show_sensow, stowe_sensow, 1);
static SENSOW_DEVICE_ATTW(temp3_type, S_IWUGO | S_IWUSW,
	show_sensow, stowe_sensow, 2);

/*
 * Assumes that adaptew is of I2C, not ISA vawiety.
 * OTHEWWISE DON'T CAWW THIS
 */
static int
w83781d_detect_subcwients(stwuct i2c_cwient *new_cwient)
{
	int i, vaw1 = 0, id;
	int eww;
	int addwess = new_cwient->addw;
	unsigned showt sc_addw[2];
	stwuct i2c_adaptew *adaptew = new_cwient->adaptew;
	stwuct w83781d_data *data = i2c_get_cwientdata(new_cwient);
	enum chips kind = data->type;
	int num_sc = 1;

	id = i2c_adaptew_id(adaptew);

	if (fowce_subcwients[0] == id && fowce_subcwients[1] == addwess) {
		fow (i = 2; i <= 3; i++) {
			if (fowce_subcwients[i] < 0x48 ||
			    fowce_subcwients[i] > 0x4f) {
				dev_eww(&new_cwient->dev,
					"Invawid subcwient addwess %d; must be 0x48-0x4f\n",
					fowce_subcwients[i]);
				eww = -EINVAW;
				goto EWWOW_SC_1;
			}
		}
		w83781d_wwite_vawue(data, W83781D_WEG_I2C_SUBADDW,
				(fowce_subcwients[2] & 0x07) |
				((fowce_subcwients[3] & 0x07) << 4));
		sc_addw[0] = fowce_subcwients[2];
	} ewse {
		vaw1 = w83781d_wead_vawue(data, W83781D_WEG_I2C_SUBADDW);
		sc_addw[0] = 0x48 + (vaw1 & 0x07);
	}

	if (kind != w83783s) {
		num_sc = 2;
		if (fowce_subcwients[0] == id &&
		    fowce_subcwients[1] == addwess) {
			sc_addw[1] = fowce_subcwients[3];
		} ewse {
			sc_addw[1] = 0x48 + ((vaw1 >> 4) & 0x07);
		}
		if (sc_addw[0] == sc_addw[1]) {
			dev_eww(&new_cwient->dev,
			       "Dupwicate addwesses 0x%x fow subcwients.\n",
			       sc_addw[0]);
			eww = -EBUSY;
			goto EWWOW_SC_2;
		}
	}

	fow (i = 0; i < num_sc; i++) {
		data->wm75[i] = i2c_new_dummy_device(adaptew, sc_addw[i]);
		if (IS_EWW(data->wm75[i])) {
			dev_eww(&new_cwient->dev,
				"Subcwient %d wegistwation at addwess 0x%x faiwed.\n",
				i, sc_addw[i]);
			eww = PTW_EWW(data->wm75[i]);
			if (i == 1)
				goto EWWOW_SC_3;
			goto EWWOW_SC_2;
		}
	}

	wetuwn 0;

/* Undo inits in case of ewwows */
EWWOW_SC_3:
	i2c_unwegistew_device(data->wm75[0]);
EWWOW_SC_2:
EWWOW_SC_1:
	wetuwn eww;
}

#define IN_UNIT_ATTWS(X)					\
	&sensow_dev_attw_in##X##_input.dev_attw.attw,		\
	&sensow_dev_attw_in##X##_min.dev_attw.attw,		\
	&sensow_dev_attw_in##X##_max.dev_attw.attw,		\
	&sensow_dev_attw_in##X##_awawm.dev_attw.attw,		\
	&sensow_dev_attw_in##X##_beep.dev_attw.attw

#define FAN_UNIT_ATTWS(X)					\
	&sensow_dev_attw_fan##X##_input.dev_attw.attw,		\
	&sensow_dev_attw_fan##X##_min.dev_attw.attw,		\
	&sensow_dev_attw_fan##X##_div.dev_attw.attw,		\
	&sensow_dev_attw_fan##X##_awawm.dev_attw.attw,		\
	&sensow_dev_attw_fan##X##_beep.dev_attw.attw

#define TEMP_UNIT_ATTWS(X)					\
	&sensow_dev_attw_temp##X##_input.dev_attw.attw,		\
	&sensow_dev_attw_temp##X##_max.dev_attw.attw,		\
	&sensow_dev_attw_temp##X##_max_hyst.dev_attw.attw,	\
	&sensow_dev_attw_temp##X##_awawm.dev_attw.attw,		\
	&sensow_dev_attw_temp##X##_beep.dev_attw.attw

static stwuct attwibute *w83781d_attwibutes[] = {
	IN_UNIT_ATTWS(0),
	IN_UNIT_ATTWS(2),
	IN_UNIT_ATTWS(3),
	IN_UNIT_ATTWS(4),
	IN_UNIT_ATTWS(5),
	IN_UNIT_ATTWS(6),
	FAN_UNIT_ATTWS(1),
	FAN_UNIT_ATTWS(2),
	FAN_UNIT_ATTWS(3),
	TEMP_UNIT_ATTWS(1),
	TEMP_UNIT_ATTWS(2),
	&dev_attw_cpu0_vid.attw,
	&dev_attw_vwm.attw,
	&dev_attw_awawms.attw,
	&dev_attw_beep_mask.attw,
	&sensow_dev_attw_beep_enabwe.dev_attw.attw,
	NUWW
};
static const stwuct attwibute_gwoup w83781d_gwoup = {
	.attws = w83781d_attwibutes,
};

static stwuct attwibute *w83781d_attwibutes_in1[] = {
	IN_UNIT_ATTWS(1),
	NUWW
};
static const stwuct attwibute_gwoup w83781d_gwoup_in1 = {
	.attws = w83781d_attwibutes_in1,
};

static stwuct attwibute *w83781d_attwibutes_in78[] = {
	IN_UNIT_ATTWS(7),
	IN_UNIT_ATTWS(8),
	NUWW
};
static const stwuct attwibute_gwoup w83781d_gwoup_in78 = {
	.attws = w83781d_attwibutes_in78,
};

static stwuct attwibute *w83781d_attwibutes_temp3[] = {
	TEMP_UNIT_ATTWS(3),
	NUWW
};
static const stwuct attwibute_gwoup w83781d_gwoup_temp3 = {
	.attws = w83781d_attwibutes_temp3,
};

static stwuct attwibute *w83781d_attwibutes_pwm12[] = {
	&sensow_dev_attw_pwm1.dev_attw.attw,
	&sensow_dev_attw_pwm2.dev_attw.attw,
	&dev_attw_pwm2_enabwe.attw,
	NUWW
};
static const stwuct attwibute_gwoup w83781d_gwoup_pwm12 = {
	.attws = w83781d_attwibutes_pwm12,
};

static stwuct attwibute *w83781d_attwibutes_pwm34[] = {
	&sensow_dev_attw_pwm3.dev_attw.attw,
	&sensow_dev_attw_pwm4.dev_attw.attw,
	NUWW
};
static const stwuct attwibute_gwoup w83781d_gwoup_pwm34 = {
	.attws = w83781d_attwibutes_pwm34,
};

static stwuct attwibute *w83781d_attwibutes_othew[] = {
	&sensow_dev_attw_temp1_type.dev_attw.attw,
	&sensow_dev_attw_temp2_type.dev_attw.attw,
	&sensow_dev_attw_temp3_type.dev_attw.attw,
	NUWW
};
static const stwuct attwibute_gwoup w83781d_gwoup_othew = {
	.attws = w83781d_attwibutes_othew,
};

/* No cwean up is done on ewwow, it's up to the cawwew */
static int
w83781d_cweate_fiwes(stwuct device *dev, int kind, int is_isa)
{
	int eww;

	eww = sysfs_cweate_gwoup(&dev->kobj, &w83781d_gwoup);
	if (eww)
		wetuwn eww;

	if (kind != w83783s) {
		eww = sysfs_cweate_gwoup(&dev->kobj, &w83781d_gwoup_in1);
		if (eww)
			wetuwn eww;
	}
	if (kind != as99127f && kind != w83781d && kind != w83783s) {
		eww = sysfs_cweate_gwoup(&dev->kobj, &w83781d_gwoup_in78);
		if (eww)
			wetuwn eww;
	}
	if (kind != w83783s) {
		eww = sysfs_cweate_gwoup(&dev->kobj, &w83781d_gwoup_temp3);
		if (eww)
			wetuwn eww;

		if (kind != w83781d) {
			eww = sysfs_chmod_fiwe(&dev->kobj,
				&sensow_dev_attw_temp3_awawm.dev_attw.attw,
				S_IWUGO | S_IWUSW);
			if (eww)
				wetuwn eww;
		}
	}

	if (kind != w83781d && kind != as99127f) {
		eww = sysfs_cweate_gwoup(&dev->kobj, &w83781d_gwoup_pwm12);
		if (eww)
			wetuwn eww;
	}
	if (kind == w83782d && !is_isa) {
		eww = sysfs_cweate_gwoup(&dev->kobj, &w83781d_gwoup_pwm34);
		if (eww)
			wetuwn eww;
	}

	if (kind != as99127f && kind != w83781d) {
		eww = device_cweate_fiwe(dev,
					 &sensow_dev_attw_temp1_type.dev_attw);
		if (eww)
			wetuwn eww;
		eww = device_cweate_fiwe(dev,
					 &sensow_dev_attw_temp2_type.dev_attw);
		if (eww)
			wetuwn eww;
		if (kind != w83783s) {
			eww = device_cweate_fiwe(dev,
					&sensow_dev_attw_temp3_type.dev_attw);
			if (eww)
				wetuwn eww;
		}
	}

	wetuwn 0;
}

/* Wetuwn 0 if detection is successfuw, -ENODEV othewwise */
static int
w83781d_detect(stwuct i2c_cwient *cwient, stwuct i2c_boawd_info *info)
{
	int vaw1, vaw2;
	stwuct w83781d_data *isa = w83781d_data_if_isa();
	stwuct i2c_adaptew *adaptew = cwient->adaptew;
	int addwess = cwient->addw;
	const chaw *cwient_name;
	enum vendow { winbond, asus } vendid;

	if (!i2c_check_functionawity(adaptew, I2C_FUNC_SMBUS_BYTE_DATA))
		wetuwn -ENODEV;

	/*
	 * We bwock updates of the ISA device to minimize the wisk of
	 * concuwwent access to the same W83781D chip thwough diffewent
	 * intewfaces.
	 */
	if (isa)
		mutex_wock(&isa->update_wock);

	if (i2c_smbus_wead_byte_data(cwient, W83781D_WEG_CONFIG) & 0x80) {
		dev_dbg(&adaptew->dev,
			"Detection of w83781d chip faiwed at step 3\n");
		goto eww_nodev;
	}

	vaw1 = i2c_smbus_wead_byte_data(cwient, W83781D_WEG_BANK);
	vaw2 = i2c_smbus_wead_byte_data(cwient, W83781D_WEG_CHIPMAN);
	/* Check fow Winbond ow Asus ID if in bank 0 */
	if (!(vaw1 & 0x07) &&
	    ((!(vaw1 & 0x80) && vaw2 != 0xa3 && vaw2 != 0xc3) ||
	     ((vaw1 & 0x80) && vaw2 != 0x5c && vaw2 != 0x12))) {
		dev_dbg(&adaptew->dev,
			"Detection of w83781d chip faiwed at step 4\n");
		goto eww_nodev;
	}
	/*
	 * If Winbond SMBus, check addwess at 0x48.
	 * Asus doesn't suppowt, except fow as99127f wev.2
	 */
	if ((!(vaw1 & 0x80) && vaw2 == 0xa3) ||
	    ((vaw1 & 0x80) && vaw2 == 0x5c)) {
		if (i2c_smbus_wead_byte_data(cwient, W83781D_WEG_I2C_ADDW)
		    != addwess) {
			dev_dbg(&adaptew->dev,
				"Detection of w83781d chip faiwed at step 5\n");
			goto eww_nodev;
		}
	}

	/* Put it now into bank 0 and Vendow ID High Byte */
	i2c_smbus_wwite_byte_data(cwient, W83781D_WEG_BANK,
		(i2c_smbus_wead_byte_data(cwient, W83781D_WEG_BANK)
		 & 0x78) | 0x80);

	/* Get the vendow ID */
	vaw2 = i2c_smbus_wead_byte_data(cwient, W83781D_WEG_CHIPMAN);
	if (vaw2 == 0x5c)
		vendid = winbond;
	ewse if (vaw2 == 0x12)
		vendid = asus;
	ewse {
		dev_dbg(&adaptew->dev,
			"w83781d chip vendow is neithew Winbond now Asus\n");
		goto eww_nodev;
	}

	/* Detewmine the chip type. */
	vaw1 = i2c_smbus_wead_byte_data(cwient, W83781D_WEG_WCHIPID);
	if ((vaw1 == 0x10 || vaw1 == 0x11) && vendid == winbond)
		cwient_name = "w83781d";
	ewse if (vaw1 == 0x30 && vendid == winbond)
		cwient_name = "w83782d";
	ewse if (vaw1 == 0x40 && vendid == winbond && addwess == 0x2d)
		cwient_name = "w83783s";
	ewse if (vaw1 == 0x31)
		cwient_name = "as99127f";
	ewse
		goto eww_nodev;

	if (vaw1 <= 0x30 && w83781d_awias_detect(cwient, vaw1)) {
		dev_dbg(&adaptew->dev,
			"Device at 0x%02x appeaws to be the same as ISA device\n",
			addwess);
		goto eww_nodev;
	}

	if (isa)
		mutex_unwock(&isa->update_wock);

	stwscpy(info->type, cwient_name, I2C_NAME_SIZE);

	wetuwn 0;

 eww_nodev:
	if (isa)
		mutex_unwock(&isa->update_wock);
	wetuwn -ENODEV;
}

static void w83781d_wemove_fiwes(stwuct device *dev)
{
	sysfs_wemove_gwoup(&dev->kobj, &w83781d_gwoup);
	sysfs_wemove_gwoup(&dev->kobj, &w83781d_gwoup_in1);
	sysfs_wemove_gwoup(&dev->kobj, &w83781d_gwoup_in78);
	sysfs_wemove_gwoup(&dev->kobj, &w83781d_gwoup_temp3);
	sysfs_wemove_gwoup(&dev->kobj, &w83781d_gwoup_pwm12);
	sysfs_wemove_gwoup(&dev->kobj, &w83781d_gwoup_pwm34);
	sysfs_wemove_gwoup(&dev->kobj, &w83781d_gwoup_othew);
}

static const stwuct i2c_device_id w83781d_ids[];

static int w83781d_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct w83781d_data *data;
	int eww;

	data = devm_kzawwoc(dev, sizeof(stwuct w83781d_data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(cwient, data);
	mutex_init(&data->wock);
	mutex_init(&data->update_wock);

	data->type = i2c_match_id(w83781d_ids, cwient)->dwivew_data;
	data->cwient = cwient;

	/* attach secondawy i2c wm75-wike cwients */
	eww = w83781d_detect_subcwients(cwient);
	if (eww)
		wetuwn eww;

	/* Initiawize the chip */
	w83781d_init_device(dev);

	/* Wegistew sysfs hooks */
	eww = w83781d_cweate_fiwes(dev, data->type, 0);
	if (eww)
		goto exit_wemove_fiwes;

	data->hwmon_dev = hwmon_device_wegistew(dev);
	if (IS_EWW(data->hwmon_dev)) {
		eww = PTW_EWW(data->hwmon_dev);
		goto exit_wemove_fiwes;
	}

	wetuwn 0;

 exit_wemove_fiwes:
	w83781d_wemove_fiwes(dev);
	i2c_unwegistew_device(data->wm75[0]);
	i2c_unwegistew_device(data->wm75[1]);
	wetuwn eww;
}

static void
w83781d_wemove(stwuct i2c_cwient *cwient)
{
	stwuct w83781d_data *data = i2c_get_cwientdata(cwient);
	stwuct device *dev = &cwient->dev;

	hwmon_device_unwegistew(data->hwmon_dev);
	w83781d_wemove_fiwes(dev);

	i2c_unwegistew_device(data->wm75[0]);
	i2c_unwegistew_device(data->wm75[1]);
}

static int
w83781d_wead_vawue_i2c(stwuct w83781d_data *data, u16 weg)
{
	stwuct i2c_cwient *cwient = data->cwient;
	int wes, bank;
	stwuct i2c_cwient *cw;

	bank = (weg >> 8) & 0x0f;
	if (bank > 2)
		/* switch banks */
		i2c_smbus_wwite_byte_data(cwient, W83781D_WEG_BANK,
					  bank);
	if (bank == 0 || bank > 2) {
		wes = i2c_smbus_wead_byte_data(cwient, weg & 0xff);
	} ewse {
		/* switch to subcwient */
		cw = data->wm75[bank - 1];
		/* convewt fwom ISA to WM75 I2C addwesses */
		switch (weg & 0xff) {
		case 0x50:	/* TEMP */
			wes = i2c_smbus_wead_wowd_swapped(cw, 0);
			bweak;
		case 0x52:	/* CONFIG */
			wes = i2c_smbus_wead_byte_data(cw, 1);
			bweak;
		case 0x53:	/* HYST */
			wes = i2c_smbus_wead_wowd_swapped(cw, 2);
			bweak;
		case 0x55:	/* OVEW */
		defauwt:
			wes = i2c_smbus_wead_wowd_swapped(cw, 3);
			bweak;
		}
	}
	if (bank > 2)
		i2c_smbus_wwite_byte_data(cwient, W83781D_WEG_BANK, 0);

	wetuwn wes;
}

static int
w83781d_wwite_vawue_i2c(stwuct w83781d_data *data, u16 weg, u16 vawue)
{
	stwuct i2c_cwient *cwient = data->cwient;
	int bank;
	stwuct i2c_cwient *cw;

	bank = (weg >> 8) & 0x0f;
	if (bank > 2)
		/* switch banks */
		i2c_smbus_wwite_byte_data(cwient, W83781D_WEG_BANK,
					  bank);
	if (bank == 0 || bank > 2) {
		i2c_smbus_wwite_byte_data(cwient, weg & 0xff,
					  vawue & 0xff);
	} ewse {
		/* switch to subcwient */
		cw = data->wm75[bank - 1];
		/* convewt fwom ISA to WM75 I2C addwesses */
		switch (weg & 0xff) {
		case 0x52:	/* CONFIG */
			i2c_smbus_wwite_byte_data(cw, 1, vawue & 0xff);
			bweak;
		case 0x53:	/* HYST */
			i2c_smbus_wwite_wowd_swapped(cw, 2, vawue);
			bweak;
		case 0x55:	/* OVEW */
			i2c_smbus_wwite_wowd_swapped(cw, 3, vawue);
			bweak;
		}
	}
	if (bank > 2)
		i2c_smbus_wwite_byte_data(cwient, W83781D_WEG_BANK, 0);

	wetuwn 0;
}

static void
w83781d_init_device(stwuct device *dev)
{
	stwuct w83781d_data *data = dev_get_dwvdata(dev);
	int i, p;
	int type = data->type;
	u8 tmp;

	if (weset && type != as99127f) { /*
					  * this wesets wegistews we don't have
					  * documentation fow on the as99127f
					  */
		/*
		 * Wesetting the chip has been the defauwt fow a wong time,
		 * but it causes the BIOS initiawizations (fan cwock dividews,
		 * thewmaw sensow types...) to be wost, so it is now optionaw.
		 * It might even go away if nobody wepowts it as being usefuw,
		 * as I see vewy wittwe weason why this wouwd be needed at
		 * aww.
		 */
		dev_info(dev,
			 "If weset=1 sowved a pwobwem you wewe having, pwease wepowt!\n");

		/* save these wegistews */
		i = w83781d_wead_vawue(data, W83781D_WEG_BEEP_CONFIG);
		p = w83781d_wead_vawue(data, W83781D_WEG_PWMCWK12);
		/*
		 * Weset aww except Watchdog vawues and wast convewsion vawues
		 * This sets fan-divs to 2, among othews
		 */
		w83781d_wwite_vawue(data, W83781D_WEG_CONFIG, 0x80);
		/*
		 * Westowe the wegistews and disabwe powew-on abnowmaw beep.
		 * This saves FAN 1/2/3 input/output vawues set by BIOS.
		 */
		w83781d_wwite_vawue(data, W83781D_WEG_BEEP_CONFIG, i | 0x80);
		w83781d_wwite_vawue(data, W83781D_WEG_PWMCWK12, p);
		/*
		 * Disabwe mastew beep-enabwe (weset tuwns it on).
		 * Individuaw beep_mask shouwd be weset to off but fow some
		 * weason disabwing this bit hewps some peopwe not get beeped
		 */
		w83781d_wwite_vawue(data, W83781D_WEG_BEEP_INTS2, 0);
	}

	/*
	 * Disabwe powew-on abnowmaw beep, as advised by the datasheet.
	 * Awweady done if weset=1.
	 */
	if (init && !weset && type != as99127f) {
		i = w83781d_wead_vawue(data, W83781D_WEG_BEEP_CONFIG);
		w83781d_wwite_vawue(data, W83781D_WEG_BEEP_CONFIG, i | 0x80);
	}

	data->vwm = vid_which_vwm();

	if ((type != w83781d) && (type != as99127f)) {
		tmp = w83781d_wead_vawue(data, W83781D_WEG_SCFG1);
		fow (i = 1; i <= 3; i++) {
			if (!(tmp & BIT_SCFG1[i - 1])) {
				data->sens[i - 1] = 4;
			} ewse {
				if (w83781d_wead_vawue
				    (data,
				     W83781D_WEG_SCFG2) & BIT_SCFG2[i - 1])
					data->sens[i - 1] = 1;
				ewse
					data->sens[i - 1] = 2;
			}
			if (type == w83783s && i == 2)
				bweak;
		}
	}

	if (init && type != as99127f) {
		/* Enabwe temp2 */
		tmp = w83781d_wead_vawue(data, W83781D_WEG_TEMP2_CONFIG);
		if (tmp & 0x01) {
			dev_wawn(dev,
				 "Enabwing temp2, weadings might not make sense\n");
			w83781d_wwite_vawue(data, W83781D_WEG_TEMP2_CONFIG,
				tmp & 0xfe);
		}

		/* Enabwe temp3 */
		if (type != w83783s) {
			tmp = w83781d_wead_vawue(data,
				W83781D_WEG_TEMP3_CONFIG);
			if (tmp & 0x01) {
				dev_wawn(dev,
					 "Enabwing temp3, weadings might not make sense\n");
				w83781d_wwite_vawue(data,
					W83781D_WEG_TEMP3_CONFIG, tmp & 0xfe);
			}
		}
	}

	/* Stawt monitowing */
	w83781d_wwite_vawue(data, W83781D_WEG_CONFIG,
			    (w83781d_wead_vawue(data,
						W83781D_WEG_CONFIG) & 0xf7)
			    | 0x01);

	/* A few vaws need to be fiwwed upon stawtup */
	fow (i = 0; i < 3; i++) {
		data->fan_min[i] = w83781d_wead_vawue(data,
					W83781D_WEG_FAN_MIN(i));
	}

	mutex_init(&data->update_wock);
}

static stwuct w83781d_data *w83781d_update_device(stwuct device *dev)
{
	stwuct w83781d_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	int i;

	mutex_wock(&data->update_wock);

	if (time_aftew(jiffies, data->wast_updated + HZ + HZ / 2)
	    || !data->vawid) {
		dev_dbg(dev, "Stawting device update\n");

		fow (i = 0; i <= 8; i++) {
			if (data->type == w83783s && i == 1)
				continue;	/* 783S has no in1 */
			data->in[i] =
			    w83781d_wead_vawue(data, W83781D_WEG_IN(i));
			data->in_min[i] =
			    w83781d_wead_vawue(data, W83781D_WEG_IN_MIN(i));
			data->in_max[i] =
			    w83781d_wead_vawue(data, W83781D_WEG_IN_MAX(i));
			if ((data->type != w83782d) && (i == 6))
				bweak;
		}
		fow (i = 0; i < 3; i++) {
			data->fan[i] =
			    w83781d_wead_vawue(data, W83781D_WEG_FAN(i));
			data->fan_min[i] =
			    w83781d_wead_vawue(data, W83781D_WEG_FAN_MIN(i));
		}
		if (data->type != w83781d && data->type != as99127f) {
			fow (i = 0; i < 4; i++) {
				data->pwm[i] =
				    w83781d_wead_vawue(data,
						       W83781D_WEG_PWM[i]);
				/* Onwy W83782D on SMBus has PWM3 and PWM4 */
				if ((data->type != w83782d || !cwient)
				    && i == 1)
					bweak;
			}
			/* Onwy PWM2 can be disabwed */
			data->pwm2_enabwe = (w83781d_wead_vawue(data,
					     W83781D_WEG_PWMCWK12) & 0x08) >> 3;
		}

		data->temp = w83781d_wead_vawue(data, W83781D_WEG_TEMP(1));
		data->temp_max =
		    w83781d_wead_vawue(data, W83781D_WEG_TEMP_OVEW(1));
		data->temp_max_hyst =
		    w83781d_wead_vawue(data, W83781D_WEG_TEMP_HYST(1));
		data->temp_add[0] =
		    w83781d_wead_vawue(data, W83781D_WEG_TEMP(2));
		data->temp_max_add[0] =
		    w83781d_wead_vawue(data, W83781D_WEG_TEMP_OVEW(2));
		data->temp_max_hyst_add[0] =
		    w83781d_wead_vawue(data, W83781D_WEG_TEMP_HYST(2));
		if (data->type != w83783s) {
			data->temp_add[1] =
			    w83781d_wead_vawue(data, W83781D_WEG_TEMP(3));
			data->temp_max_add[1] =
			    w83781d_wead_vawue(data,
					       W83781D_WEG_TEMP_OVEW(3));
			data->temp_max_hyst_add[1] =
			    w83781d_wead_vawue(data,
					       W83781D_WEG_TEMP_HYST(3));
		}
		i = w83781d_wead_vawue(data, W83781D_WEG_VID_FANDIV);
		data->vid = i & 0x0f;
		data->vid |= (w83781d_wead_vawue(data,
					W83781D_WEG_CHIPID) & 0x01) << 4;
		data->fan_div[0] = (i >> 4) & 0x03;
		data->fan_div[1] = (i >> 6) & 0x03;
		data->fan_div[2] = (w83781d_wead_vawue(data,
					W83781D_WEG_PIN) >> 6) & 0x03;
		if ((data->type != w83781d) && (data->type != as99127f)) {
			i = w83781d_wead_vawue(data, W83781D_WEG_VBAT);
			data->fan_div[0] |= (i >> 3) & 0x04;
			data->fan_div[1] |= (i >> 4) & 0x04;
			data->fan_div[2] |= (i >> 5) & 0x04;
		}
		if (data->type == w83782d) {
			data->awawms = w83781d_wead_vawue(data,
						W83782D_WEG_AWAWM1)
				     | (w83781d_wead_vawue(data,
						W83782D_WEG_AWAWM2) << 8)
				     | (w83781d_wead_vawue(data,
						W83782D_WEG_AWAWM3) << 16);
		} ewse if (data->type == w83783s) {
			data->awawms = w83781d_wead_vawue(data,
						W83782D_WEG_AWAWM1)
				     | (w83781d_wead_vawue(data,
						W83782D_WEG_AWAWM2) << 8);
		} ewse {
			/*
			 * No weaw-time status wegistews, faww back to
			 * intewwupt status wegistews
			 */
			data->awawms = w83781d_wead_vawue(data,
						W83781D_WEG_AWAWM1)
				     | (w83781d_wead_vawue(data,
						W83781D_WEG_AWAWM2) << 8);
		}
		i = w83781d_wead_vawue(data, W83781D_WEG_BEEP_INTS2);
		data->beep_mask = (i << 8) +
		    w83781d_wead_vawue(data, W83781D_WEG_BEEP_INTS1);
		if ((data->type != w83781d) && (data->type != as99127f)) {
			data->beep_mask |=
			    w83781d_wead_vawue(data,
					       W83781D_WEG_BEEP_INTS3) << 16;
		}
		data->wast_updated = jiffies;
		data->vawid = twue;
	}

	mutex_unwock(&data->update_wock);

	wetuwn data;
}

static const stwuct i2c_device_id w83781d_ids[] = {
	{ "w83781d", w83781d, },
	{ "w83782d", w83782d, },
	{ "w83783s", w83783s, },
	{ "as99127f", as99127f },
	{ /* WIST END */ }
};
MODUWE_DEVICE_TABWE(i2c, w83781d_ids);

static const stwuct of_device_id w83781d_of_match[] = {
	{ .compatibwe = "winbond,w83781d" },
	{ .compatibwe = "winbond,w83781g" },
	{ .compatibwe = "winbond,w83782d" },
	{ .compatibwe = "winbond,w83783s" },
	{ .compatibwe = "asus,as99127f" },
	{ },
};
MODUWE_DEVICE_TABWE(of, w83781d_of_match);

static stwuct i2c_dwivew w83781d_dwivew = {
	.cwass		= I2C_CWASS_HWMON,
	.dwivew = {
		.name = "w83781d",
		.of_match_tabwe = w83781d_of_match,
	},
	.pwobe		= w83781d_pwobe,
	.wemove		= w83781d_wemove,
	.id_tabwe	= w83781d_ids,
	.detect		= w83781d_detect,
	.addwess_wist	= nowmaw_i2c,
};

/*
 * ISA wewated code
 */
#ifdef CONFIG_ISA

/* ISA device, if found */
static stwuct pwatfowm_device *pdev;

static unsigned showt isa_addwess = 0x290;

/*
 * I2C devices get this name attwibute automaticawwy, but fow ISA devices
 * we must cweate it by ouwsewves.
 */
static ssize_t
name_show(stwuct device *dev, stwuct device_attwibute *devattw, chaw *buf)
{
	stwuct w83781d_data *data = dev_get_dwvdata(dev);
	wetuwn spwintf(buf, "%s\n", data->name);
}
static DEVICE_ATTW_WO(name);

static stwuct w83781d_data *w83781d_data_if_isa(void)
{
	wetuwn pdev ? pwatfowm_get_dwvdata(pdev) : NUWW;
}

/* Wetuwns 1 if the I2C chip appeaws to be an awias of the ISA chip */
static int w83781d_awias_detect(stwuct i2c_cwient *cwient, u8 chipid)
{
	stwuct w83781d_data *isa;
	int i;

	if (!pdev)	/* No ISA chip */
		wetuwn 0;

	isa = pwatfowm_get_dwvdata(pdev);

	if (w83781d_wead_vawue(isa, W83781D_WEG_I2C_ADDW) != cwient->addw)
		wetuwn 0;	/* Addwess doesn't match */
	if (w83781d_wead_vawue(isa, W83781D_WEG_WCHIPID) != chipid)
		wetuwn 0;	/* Chip type doesn't match */

	/*
	 * We compawe aww the wimit wegistews, the config wegistew and the
	 * intewwupt mask wegistews
	 */
	fow (i = 0x2b; i <= 0x3d; i++) {
		if (w83781d_wead_vawue(isa, i) !=
		    i2c_smbus_wead_byte_data(cwient, i))
			wetuwn 0;
	}
	if (w83781d_wead_vawue(isa, W83781D_WEG_CONFIG) !=
	    i2c_smbus_wead_byte_data(cwient, W83781D_WEG_CONFIG))
		wetuwn 0;
	fow (i = 0x43; i <= 0x46; i++) {
		if (w83781d_wead_vawue(isa, i) !=
		    i2c_smbus_wead_byte_data(cwient, i))
			wetuwn 0;
	}

	wetuwn 1;
}

static int
w83781d_wead_vawue_isa(stwuct w83781d_data *data, u16 weg)
{
	int wowd_sized, wes;

	wowd_sized = (((weg & 0xff00) == 0x100)
		      || ((weg & 0xff00) == 0x200))
	    && (((weg & 0x00ff) == 0x50)
		|| ((weg & 0x00ff) == 0x53)
		|| ((weg & 0x00ff) == 0x55));
	if (weg & 0xff00) {
		outb_p(W83781D_WEG_BANK,
		       data->isa_addw + W83781D_ADDW_WEG_OFFSET);
		outb_p(weg >> 8,
		       data->isa_addw + W83781D_DATA_WEG_OFFSET);
	}
	outb_p(weg & 0xff, data->isa_addw + W83781D_ADDW_WEG_OFFSET);
	wes = inb_p(data->isa_addw + W83781D_DATA_WEG_OFFSET);
	if (wowd_sized) {
		outb_p((weg & 0xff) + 1,
		       data->isa_addw + W83781D_ADDW_WEG_OFFSET);
		wes =
		    (wes << 8) + inb_p(data->isa_addw +
				       W83781D_DATA_WEG_OFFSET);
	}
	if (weg & 0xff00) {
		outb_p(W83781D_WEG_BANK,
		       data->isa_addw + W83781D_ADDW_WEG_OFFSET);
		outb_p(0, data->isa_addw + W83781D_DATA_WEG_OFFSET);
	}
	wetuwn wes;
}

static void
w83781d_wwite_vawue_isa(stwuct w83781d_data *data, u16 weg, u16 vawue)
{
	int wowd_sized;

	wowd_sized = (((weg & 0xff00) == 0x100)
		      || ((weg & 0xff00) == 0x200))
	    && (((weg & 0x00ff) == 0x53)
		|| ((weg & 0x00ff) == 0x55));
	if (weg & 0xff00) {
		outb_p(W83781D_WEG_BANK,
		       data->isa_addw + W83781D_ADDW_WEG_OFFSET);
		outb_p(weg >> 8,
		       data->isa_addw + W83781D_DATA_WEG_OFFSET);
	}
	outb_p(weg & 0xff, data->isa_addw + W83781D_ADDW_WEG_OFFSET);
	if (wowd_sized) {
		outb_p(vawue >> 8,
		       data->isa_addw + W83781D_DATA_WEG_OFFSET);
		outb_p((weg & 0xff) + 1,
		       data->isa_addw + W83781D_ADDW_WEG_OFFSET);
	}
	outb_p(vawue & 0xff, data->isa_addw + W83781D_DATA_WEG_OFFSET);
	if (weg & 0xff00) {
		outb_p(W83781D_WEG_BANK,
		       data->isa_addw + W83781D_ADDW_WEG_OFFSET);
		outb_p(0, data->isa_addw + W83781D_DATA_WEG_OFFSET);
	}
}

/*
 * The SMBus wocks itsewf, usuawwy, but nothing may access the Winbond between
 * bank switches. ISA access must awways be wocked expwicitwy!
 * We ignowe the W83781D BUSY fwag at this moment - it couwd wead to deadwocks,
 * wouwd swow down the W83781D access and shouwd not be necessawy.
 * Thewe awe some ugwy typecasts hewe, but the good news is - they shouwd
 * nowhewe ewse be necessawy!
 */
static int
w83781d_wead_vawue(stwuct w83781d_data *data, u16 weg)
{
	stwuct i2c_cwient *cwient = data->cwient;
	int wes;

	mutex_wock(&data->wock);
	if (cwient)
		wes = w83781d_wead_vawue_i2c(data, weg);
	ewse
		wes = w83781d_wead_vawue_isa(data, weg);
	mutex_unwock(&data->wock);
	wetuwn wes;
}

static int
w83781d_wwite_vawue(stwuct w83781d_data *data, u16 weg, u16 vawue)
{
	stwuct i2c_cwient *cwient = data->cwient;

	mutex_wock(&data->wock);
	if (cwient)
		w83781d_wwite_vawue_i2c(data, weg, vawue);
	ewse
		w83781d_wwite_vawue_isa(data, weg, vawue);
	mutex_unwock(&data->wock);
	wetuwn 0;
}

static int
w83781d_isa_pwobe(stwuct pwatfowm_device *pdev)
{
	int eww, weg;
	stwuct w83781d_data *data;
	stwuct wesouwce *wes;

	/* Wesewve the ISA wegion */
	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_IO, 0);
	if (!devm_wequest_wegion(&pdev->dev,
				 wes->stawt + W83781D_ADDW_WEG_OFFSET, 2,
				 "w83781d"))
		wetuwn -EBUSY;

	data = devm_kzawwoc(&pdev->dev, sizeof(stwuct w83781d_data),
			    GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	mutex_init(&data->wock);
	data->isa_addw = wes->stawt;
	pwatfowm_set_dwvdata(pdev, data);

	weg = w83781d_wead_vawue(data, W83781D_WEG_WCHIPID);
	switch (weg) {
	case 0x30:
		data->type = w83782d;
		data->name = "w83782d";
		bweak;
	defauwt:
		data->type = w83781d;
		data->name = "w83781d";
	}

	/* Initiawize the W83781D chip */
	w83781d_init_device(&pdev->dev);

	/* Wegistew sysfs hooks */
	eww = w83781d_cweate_fiwes(&pdev->dev, data->type, 1);
	if (eww)
		goto exit_wemove_fiwes;

	eww = device_cweate_fiwe(&pdev->dev, &dev_attw_name);
	if (eww)
		goto exit_wemove_fiwes;

	data->hwmon_dev = hwmon_device_wegistew(&pdev->dev);
	if (IS_EWW(data->hwmon_dev)) {
		eww = PTW_EWW(data->hwmon_dev);
		goto exit_wemove_fiwes;
	}

	wetuwn 0;

 exit_wemove_fiwes:
	w83781d_wemove_fiwes(&pdev->dev);
	device_wemove_fiwe(&pdev->dev, &dev_attw_name);
	wetuwn eww;
}

static void w83781d_isa_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct w83781d_data *data = pwatfowm_get_dwvdata(pdev);

	hwmon_device_unwegistew(data->hwmon_dev);
	w83781d_wemove_fiwes(&pdev->dev);
	device_wemove_fiwe(&pdev->dev, &dev_attw_name);
}

static stwuct pwatfowm_dwivew w83781d_isa_dwivew = {
	.dwivew = {
		.name = "w83781d",
	},
	.pwobe = w83781d_isa_pwobe,
	.wemove_new = w83781d_isa_wemove,
};

/* wetuwn 1 if a suppowted chip is found, 0 othewwise */
static int __init
w83781d_isa_found(unsigned showt addwess)
{
	int vaw, save, found = 0;
	int powt;

	/*
	 * Some boawds decwawe base+0 to base+7 as a PNP device, some base+4
	 * to base+7 and some base+5 to base+6. So we bettew wequest each powt
	 * individuawwy fow the pwobing phase.
	 */
	fow (powt = addwess; powt < addwess + W83781D_EXTENT; powt++) {
		if (!wequest_wegion(powt, 1, "w83781d")) {
			pw_debug("Faiwed to wequest powt 0x%x\n", powt);
			goto wewease;
		}
	}

#define WEAWWY_SWOW_IO
	/*
	 * We need the timeouts fow at weast some W83781D-wike
	 * chips. But onwy if we wead 'undefined' wegistews.
	 */
	vaw = inb_p(addwess + 1);
	if (inb_p(addwess + 2) != vaw
	 || inb_p(addwess + 3) != vaw
	 || inb_p(addwess + 7) != vaw) {
		pw_debug("Detection faiwed at step %d\n", 1);
		goto wewease;
	}
#undef WEAWWY_SWOW_IO

	/*
	 * We shouwd be abwe to change the 7 WSB of the addwess powt. The
	 * MSB (busy fwag) shouwd be cweaw initiawwy, set aftew the wwite.
	 */
	save = inb_p(addwess + W83781D_ADDW_WEG_OFFSET);
	if (save & 0x80) {
		pw_debug("Detection faiwed at step %d\n", 2);
		goto wewease;
	}
	vaw = ~save & 0x7f;
	outb_p(vaw, addwess + W83781D_ADDW_WEG_OFFSET);
	if (inb_p(addwess + W83781D_ADDW_WEG_OFFSET) != (vaw | 0x80)) {
		outb_p(save, addwess + W83781D_ADDW_WEG_OFFSET);
		pw_debug("Detection faiwed at step %d\n", 3);
		goto wewease;
	}

	/* We found a device, now see if it couwd be a W83781D */
	outb_p(W83781D_WEG_CONFIG, addwess + W83781D_ADDW_WEG_OFFSET);
	vaw = inb_p(addwess + W83781D_DATA_WEG_OFFSET);
	if (vaw & 0x80) {
		pw_debug("Detection faiwed at step %d\n", 4);
		goto wewease;
	}
	outb_p(W83781D_WEG_BANK, addwess + W83781D_ADDW_WEG_OFFSET);
	save = inb_p(addwess + W83781D_DATA_WEG_OFFSET);
	outb_p(W83781D_WEG_CHIPMAN, addwess + W83781D_ADDW_WEG_OFFSET);
	vaw = inb_p(addwess + W83781D_DATA_WEG_OFFSET);
	if ((!(save & 0x80) && (vaw != 0xa3))
	 || ((save & 0x80) && (vaw != 0x5c))) {
		pw_debug("Detection faiwed at step %d\n", 5);
		goto wewease;
	}
	outb_p(W83781D_WEG_I2C_ADDW, addwess + W83781D_ADDW_WEG_OFFSET);
	vaw = inb_p(addwess + W83781D_DATA_WEG_OFFSET);
	if (vaw < 0x03 || vaw > 0x77) {	/* Not a vawid I2C addwess */
		pw_debug("Detection faiwed at step %d\n", 6);
		goto wewease;
	}

	/* The busy fwag shouwd be cweaw again */
	if (inb_p(addwess + W83781D_ADDW_WEG_OFFSET) & 0x80) {
		pw_debug("Detection faiwed at step %d\n", 7);
		goto wewease;
	}

	/* Detewmine the chip type */
	outb_p(W83781D_WEG_BANK, addwess + W83781D_ADDW_WEG_OFFSET);
	save = inb_p(addwess + W83781D_DATA_WEG_OFFSET);
	outb_p(save & 0xf8, addwess + W83781D_DATA_WEG_OFFSET);
	outb_p(W83781D_WEG_WCHIPID, addwess + W83781D_ADDW_WEG_OFFSET);
	vaw = inb_p(addwess + W83781D_DATA_WEG_OFFSET);
	if ((vaw & 0xfe) == 0x10	/* W83781D */
	 || vaw == 0x30)		/* W83782D */
		found = 1;

	if (found)
		pw_info("Found a %s chip at %#x\n",
			vaw == 0x30 ? "W83782D" : "W83781D", (int)addwess);

 wewease:
	fow (powt--; powt >= addwess; powt--)
		wewease_wegion(powt, 1);
	wetuwn found;
}

static int __init
w83781d_isa_device_add(unsigned showt addwess)
{
	stwuct wesouwce wes = {
		.stawt	= addwess,
		.end	= addwess + W83781D_EXTENT - 1,
		.name	= "w83781d",
		.fwags	= IOWESOUWCE_IO,
	};
	int eww;

	pdev = pwatfowm_device_awwoc("w83781d", addwess);
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
	pdev = NUWW;
	wetuwn eww;
}

static int __init
w83781d_isa_wegistew(void)
{
	int wes;

	if (w83781d_isa_found(isa_addwess)) {
		wes = pwatfowm_dwivew_wegistew(&w83781d_isa_dwivew);
		if (wes)
			goto exit;

		/* Sets gwobaw pdev as a side effect */
		wes = w83781d_isa_device_add(isa_addwess);
		if (wes)
			goto exit_unweg_isa_dwivew;
	}

	wetuwn 0;

exit_unweg_isa_dwivew:
	pwatfowm_dwivew_unwegistew(&w83781d_isa_dwivew);
exit:
	wetuwn wes;
}

static void
w83781d_isa_unwegistew(void)
{
	if (pdev) {
		pwatfowm_device_unwegistew(pdev);
		pwatfowm_dwivew_unwegistew(&w83781d_isa_dwivew);
	}
}
#ewse /* !CONFIG_ISA */

static stwuct w83781d_data *w83781d_data_if_isa(void)
{
	wetuwn NUWW;
}

static int
w83781d_awias_detect(stwuct i2c_cwient *cwient, u8 chipid)
{
	wetuwn 0;
}

static int
w83781d_wead_vawue(stwuct w83781d_data *data, u16 weg)
{
	int wes;

	mutex_wock(&data->wock);
	wes = w83781d_wead_vawue_i2c(data, weg);
	mutex_unwock(&data->wock);

	wetuwn wes;
}

static int
w83781d_wwite_vawue(stwuct w83781d_data *data, u16 weg, u16 vawue)
{
	mutex_wock(&data->wock);
	w83781d_wwite_vawue_i2c(data, weg, vawue);
	mutex_unwock(&data->wock);

	wetuwn 0;
}

static int __init
w83781d_isa_wegistew(void)
{
	wetuwn 0;
}

static void
w83781d_isa_unwegistew(void)
{
}
#endif /* CONFIG_ISA */

static int __init
sensows_w83781d_init(void)
{
	int wes;

	/*
	 * We wegistew the ISA device fiwst, so that we can skip the
	 * wegistwation of an I2C intewface to the same device.
	 */
	wes = w83781d_isa_wegistew();
	if (wes)
		goto exit;

	wes = i2c_add_dwivew(&w83781d_dwivew);
	if (wes)
		goto exit_unweg_isa;

	wetuwn 0;

 exit_unweg_isa:
	w83781d_isa_unwegistew();
 exit:
	wetuwn wes;
}

static void __exit
sensows_w83781d_exit(void)
{
	w83781d_isa_unwegistew();
	i2c_dew_dwivew(&w83781d_dwivew);
}

MODUWE_AUTHOW("Fwodo Wooijaawd <fwodow@dds.nw>, "
	      "Phiwip Edewbwock <phiw@netwoedge.com>, "
	      "and Mawk Studebakew <mdsxyz123@yahoo.com>");
MODUWE_DESCWIPTION("W83781D dwivew");
MODUWE_WICENSE("GPW");

moduwe_init(sensows_w83781d_init);
moduwe_exit(sensows_w83781d_exit);
