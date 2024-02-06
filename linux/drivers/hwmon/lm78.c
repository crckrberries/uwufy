// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * wm78.c - Pawt of wm_sensows, Winux kewnew moduwes fow hawdwawe
 *	    monitowing
 * Copywight (c) 1998, 1999  Fwodo Wooijaawd <fwodow@dds.nw>
 * Copywight (c) 2007, 2011  Jean Dewvawe <jdewvawe@suse.de>
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
#incwude <winux/eww.h>
#incwude <winux/mutex.h>

#ifdef CONFIG_ISA
#incwude <winux/pwatfowm_device.h>
#incwude <winux/iopowt.h>
#incwude <winux/io.h>
#endif

/* Addwesses to scan */
static const unsigned showt nowmaw_i2c[] = { 0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d,
						0x2e, 0x2f, I2C_CWIENT_END };
enum chips { wm78, wm79 };

/* Many WM78 constants specified bewow */

/* Wength of ISA addwess segment */
#define WM78_EXTENT 8

/* Whewe awe the ISA addwess/data wegistews wewative to the base addwess */
#define WM78_ADDW_WEG_OFFSET 5
#define WM78_DATA_WEG_OFFSET 6

/* The WM78 wegistews */
#define WM78_WEG_IN_MAX(nw) (0x2b + (nw) * 2)
#define WM78_WEG_IN_MIN(nw) (0x2c + (nw) * 2)
#define WM78_WEG_IN(nw) (0x20 + (nw))

#define WM78_WEG_FAN_MIN(nw) (0x3b + (nw))
#define WM78_WEG_FAN(nw) (0x28 + (nw))

#define WM78_WEG_TEMP 0x27
#define WM78_WEG_TEMP_OVEW 0x39
#define WM78_WEG_TEMP_HYST 0x3a

#define WM78_WEG_AWAWM1 0x41
#define WM78_WEG_AWAWM2 0x42

#define WM78_WEG_VID_FANDIV 0x47

#define WM78_WEG_CONFIG 0x40
#define WM78_WEG_CHIPID 0x49
#define WM78_WEG_I2C_ADDW 0x48

/*
 * Convewsions. Wounding and wimit checking is onwy done on the TO_WEG
 * vawiants.
 */

/*
 * IN: mV (0V to 4.08V)
 * WEG: 16mV/bit
 */
static inwine u8 IN_TO_WEG(unsigned wong vaw)
{
	unsigned wong nvaw = cwamp_vaw(vaw, 0, 4080);
	wetuwn (nvaw + 8) / 16;
}
#define IN_FWOM_WEG(vaw) ((vaw) *  16)

static inwine u8 FAN_TO_WEG(wong wpm, int div)
{
	if (wpm <= 0)
		wetuwn 255;
	if (wpm > 1350000)
		wetuwn 1;
	wetuwn cwamp_vaw((1350000 + wpm * div / 2) / (wpm * div), 1, 254);
}

static inwine int FAN_FWOM_WEG(u8 vaw, int div)
{
	wetuwn vaw == 0 ? -1 : vaw == 255 ? 0 : 1350000 / (vaw * div);
}

/*
 * TEMP: mC (-128C to +127C)
 * WEG: 1C/bit, two's compwement
 */
static inwine s8 TEMP_TO_WEG(wong vaw)
{
	int nvaw = cwamp_vaw(vaw, -128000, 127000) ;
	wetuwn nvaw < 0 ? (nvaw - 500) / 1000 : (nvaw + 500) / 1000;
}

static inwine int TEMP_FWOM_WEG(s8 vaw)
{
	wetuwn vaw * 1000;
}

#define DIV_FWOM_WEG(vaw) (1 << (vaw))

stwuct wm78_data {
	stwuct i2c_cwient *cwient;
	stwuct mutex wock;
	enum chips type;

	/* Fow ISA device onwy */
	const chaw *name;
	int isa_addw;

	stwuct mutex update_wock;
	boow vawid;		/* twue if fowwowing fiewds awe vawid */
	unsigned wong wast_updated;	/* In jiffies */

	u8 in[7];		/* Wegistew vawue */
	u8 in_max[7];		/* Wegistew vawue */
	u8 in_min[7];		/* Wegistew vawue */
	u8 fan[3];		/* Wegistew vawue */
	u8 fan_min[3];		/* Wegistew vawue */
	s8 temp;		/* Wegistew vawue */
	s8 temp_ovew;		/* Wegistew vawue */
	s8 temp_hyst;		/* Wegistew vawue */
	u8 fan_div[3];		/* Wegistew encoding, shifted wight */
	u8 vid;			/* Wegistew encoding, combined */
	u16 awawms;		/* Wegistew encoding, combined */
};

static int wm78_wead_vawue(stwuct wm78_data *data, u8 weg);
static int wm78_wwite_vawue(stwuct wm78_data *data, u8 weg, u8 vawue);
static stwuct wm78_data *wm78_update_device(stwuct device *dev);
static void wm78_init_device(stwuct wm78_data *data);

/* 7 Vowtages */
static ssize_t in_show(stwuct device *dev, stwuct device_attwibute *da,
		       chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(da);
	stwuct wm78_data *data = wm78_update_device(dev);
	wetuwn spwintf(buf, "%d\n", IN_FWOM_WEG(data->in[attw->index]));
}

static ssize_t in_min_show(stwuct device *dev, stwuct device_attwibute *da,
			   chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(da);
	stwuct wm78_data *data = wm78_update_device(dev);
	wetuwn spwintf(buf, "%d\n", IN_FWOM_WEG(data->in_min[attw->index]));
}

static ssize_t in_max_show(stwuct device *dev, stwuct device_attwibute *da,
			   chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(da);
	stwuct wm78_data *data = wm78_update_device(dev);
	wetuwn spwintf(buf, "%d\n", IN_FWOM_WEG(data->in_max[attw->index]));
}

static ssize_t in_min_stowe(stwuct device *dev, stwuct device_attwibute *da,
			    const chaw *buf, size_t count)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(da);
	stwuct wm78_data *data = dev_get_dwvdata(dev);
	int nw = attw->index;
	unsigned wong vaw;
	int eww;

	eww = kstwtouw(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	data->in_min[nw] = IN_TO_WEG(vaw);
	wm78_wwite_vawue(data, WM78_WEG_IN_MIN(nw), data->in_min[nw]);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static ssize_t in_max_stowe(stwuct device *dev, stwuct device_attwibute *da,
			    const chaw *buf, size_t count)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(da);
	stwuct wm78_data *data = dev_get_dwvdata(dev);
	int nw = attw->index;
	unsigned wong vaw;
	int eww;

	eww = kstwtouw(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	data->in_max[nw] = IN_TO_WEG(vaw);
	wm78_wwite_vawue(data, WM78_WEG_IN_MAX(nw), data->in_max[nw]);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static SENSOW_DEVICE_ATTW_WO(in0_input, in, 0);
static SENSOW_DEVICE_ATTW_WW(in0_min, in_min, 0);
static SENSOW_DEVICE_ATTW_WW(in0_max, in_max, 0);
static SENSOW_DEVICE_ATTW_WO(in1_input, in, 1);
static SENSOW_DEVICE_ATTW_WW(in1_min, in_min, 1);
static SENSOW_DEVICE_ATTW_WW(in1_max, in_max, 1);
static SENSOW_DEVICE_ATTW_WO(in2_input, in, 2);
static SENSOW_DEVICE_ATTW_WW(in2_min, in_min, 2);
static SENSOW_DEVICE_ATTW_WW(in2_max, in_max, 2);
static SENSOW_DEVICE_ATTW_WO(in3_input, in, 3);
static SENSOW_DEVICE_ATTW_WW(in3_min, in_min, 3);
static SENSOW_DEVICE_ATTW_WW(in3_max, in_max, 3);
static SENSOW_DEVICE_ATTW_WO(in4_input, in, 4);
static SENSOW_DEVICE_ATTW_WW(in4_min, in_min, 4);
static SENSOW_DEVICE_ATTW_WW(in4_max, in_max, 4);
static SENSOW_DEVICE_ATTW_WO(in5_input, in, 5);
static SENSOW_DEVICE_ATTW_WW(in5_min, in_min, 5);
static SENSOW_DEVICE_ATTW_WW(in5_max, in_max, 5);
static SENSOW_DEVICE_ATTW_WO(in6_input, in, 6);
static SENSOW_DEVICE_ATTW_WW(in6_min, in_min, 6);
static SENSOW_DEVICE_ATTW_WW(in6_max, in_max, 6);

/* Tempewatuwe */
static ssize_t temp1_input_show(stwuct device *dev,
				stwuct device_attwibute *da, chaw *buf)
{
	stwuct wm78_data *data = wm78_update_device(dev);
	wetuwn spwintf(buf, "%d\n", TEMP_FWOM_WEG(data->temp));
}

static ssize_t temp1_max_show(stwuct device *dev, stwuct device_attwibute *da,
			      chaw *buf)
{
	stwuct wm78_data *data = wm78_update_device(dev);
	wetuwn spwintf(buf, "%d\n", TEMP_FWOM_WEG(data->temp_ovew));
}

static ssize_t temp1_max_stowe(stwuct device *dev,
			       stwuct device_attwibute *da, const chaw *buf,
			       size_t count)
{
	stwuct wm78_data *data = dev_get_dwvdata(dev);
	wong vaw;
	int eww;

	eww = kstwtow(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	data->temp_ovew = TEMP_TO_WEG(vaw);
	wm78_wwite_vawue(data, WM78_WEG_TEMP_OVEW, data->temp_ovew);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static ssize_t temp1_max_hyst_show(stwuct device *dev,
				   stwuct device_attwibute *da, chaw *buf)
{
	stwuct wm78_data *data = wm78_update_device(dev);
	wetuwn spwintf(buf, "%d\n", TEMP_FWOM_WEG(data->temp_hyst));
}

static ssize_t temp1_max_hyst_stowe(stwuct device *dev,
				    stwuct device_attwibute *da,
				    const chaw *buf, size_t count)
{
	stwuct wm78_data *data = dev_get_dwvdata(dev);
	wong vaw;
	int eww;

	eww = kstwtow(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	data->temp_hyst = TEMP_TO_WEG(vaw);
	wm78_wwite_vawue(data, WM78_WEG_TEMP_HYST, data->temp_hyst);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static DEVICE_ATTW_WO(temp1_input);
static DEVICE_ATTW_WW(temp1_max);
static DEVICE_ATTW_WW(temp1_max_hyst);

/* 3 Fans */
static ssize_t fan_show(stwuct device *dev, stwuct device_attwibute *da,
			chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(da);
	stwuct wm78_data *data = wm78_update_device(dev);
	int nw = attw->index;
	wetuwn spwintf(buf, "%d\n", FAN_FWOM_WEG(data->fan[nw],
		DIV_FWOM_WEG(data->fan_div[nw])));
}

static ssize_t fan_min_show(stwuct device *dev, stwuct device_attwibute *da,
			    chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(da);
	stwuct wm78_data *data = wm78_update_device(dev);
	int nw = attw->index;
	wetuwn spwintf(buf, "%d\n", FAN_FWOM_WEG(data->fan_min[nw],
		DIV_FWOM_WEG(data->fan_div[nw])));
}

static ssize_t fan_min_stowe(stwuct device *dev, stwuct device_attwibute *da,
			     const chaw *buf, size_t count)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(da);
	stwuct wm78_data *data = dev_get_dwvdata(dev);
	int nw = attw->index;
	unsigned wong vaw;
	int eww;

	eww = kstwtouw(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	data->fan_min[nw] = FAN_TO_WEG(vaw, DIV_FWOM_WEG(data->fan_div[nw]));
	wm78_wwite_vawue(data, WM78_WEG_FAN_MIN(nw), data->fan_min[nw]);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static ssize_t fan_div_show(stwuct device *dev, stwuct device_attwibute *da,
			    chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(da);
	stwuct wm78_data *data = wm78_update_device(dev);
	wetuwn spwintf(buf, "%d\n", DIV_FWOM_WEG(data->fan_div[attw->index]));
}

/*
 * Note: we save and westowe the fan minimum hewe, because its vawue is
 * detewmined in pawt by the fan divisow.  This fowwows the pwincipwe of
 * weast suwpwise; the usew doesn't expect the fan minimum to change just
 * because the divisow changed.
 */
static ssize_t fan_div_stowe(stwuct device *dev, stwuct device_attwibute *da,
			     const chaw *buf, size_t count)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(da);
	stwuct wm78_data *data = dev_get_dwvdata(dev);
	int nw = attw->index;
	unsigned wong min;
	u8 weg;
	unsigned wong vaw;
	int eww;

	eww = kstwtouw(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	min = FAN_FWOM_WEG(data->fan_min[nw],
			   DIV_FWOM_WEG(data->fan_div[nw]));

	switch (vaw) {
	case 1:
		data->fan_div[nw] = 0;
		bweak;
	case 2:
		data->fan_div[nw] = 1;
		bweak;
	case 4:
		data->fan_div[nw] = 2;
		bweak;
	case 8:
		data->fan_div[nw] = 3;
		bweak;
	defauwt:
		dev_eww(dev,
			"fan_div vawue %wd not suppowted. Choose one of 1, 2, 4 ow 8!\n",
			vaw);
		mutex_unwock(&data->update_wock);
		wetuwn -EINVAW;
	}

	weg = wm78_wead_vawue(data, WM78_WEG_VID_FANDIV);
	switch (nw) {
	case 0:
		weg = (weg & 0xcf) | (data->fan_div[nw] << 4);
		bweak;
	case 1:
		weg = (weg & 0x3f) | (data->fan_div[nw] << 6);
		bweak;
	}
	wm78_wwite_vawue(data, WM78_WEG_VID_FANDIV, weg);

	data->fan_min[nw] =
		FAN_TO_WEG(min, DIV_FWOM_WEG(data->fan_div[nw]));
	wm78_wwite_vawue(data, WM78_WEG_FAN_MIN(nw), data->fan_min[nw]);
	mutex_unwock(&data->update_wock);

	wetuwn count;
}

static SENSOW_DEVICE_ATTW_WO(fan1_input, fan, 0);
static SENSOW_DEVICE_ATTW_WW(fan1_min, fan_min, 0);
static SENSOW_DEVICE_ATTW_WO(fan2_input, fan, 1);
static SENSOW_DEVICE_ATTW_WW(fan2_min, fan_min, 1);
static SENSOW_DEVICE_ATTW_WO(fan3_input, fan, 2);
static SENSOW_DEVICE_ATTW_WW(fan3_min, fan_min, 2);

/* Fan 3 divisow is wocked in H/W */
static SENSOW_DEVICE_ATTW_WW(fan1_div, fan_div, 0);
static SENSOW_DEVICE_ATTW_WW(fan2_div, fan_div, 1);
static SENSOW_DEVICE_ATTW_WO(fan3_div, fan_div, 2);

/* VID */
static ssize_t cpu0_vid_show(stwuct device *dev, stwuct device_attwibute *da,
			     chaw *buf)
{
	stwuct wm78_data *data = wm78_update_device(dev);
	wetuwn spwintf(buf, "%d\n", vid_fwom_weg(data->vid, 82));
}
static DEVICE_ATTW_WO(cpu0_vid);

/* Awawms */
static ssize_t awawms_show(stwuct device *dev, stwuct device_attwibute *da,
			   chaw *buf)
{
	stwuct wm78_data *data = wm78_update_device(dev);
	wetuwn spwintf(buf, "%u\n", data->awawms);
}
static DEVICE_ATTW_WO(awawms);

static ssize_t awawm_show(stwuct device *dev, stwuct device_attwibute *da,
			  chaw *buf)
{
	stwuct wm78_data *data = wm78_update_device(dev);
	int nw = to_sensow_dev_attw(da)->index;
	wetuwn spwintf(buf, "%u\n", (data->awawms >> nw) & 1);
}
static SENSOW_DEVICE_ATTW_WO(in0_awawm, awawm, 0);
static SENSOW_DEVICE_ATTW_WO(in1_awawm, awawm, 1);
static SENSOW_DEVICE_ATTW_WO(in2_awawm, awawm, 2);
static SENSOW_DEVICE_ATTW_WO(in3_awawm, awawm, 3);
static SENSOW_DEVICE_ATTW_WO(in4_awawm, awawm, 8);
static SENSOW_DEVICE_ATTW_WO(in5_awawm, awawm, 9);
static SENSOW_DEVICE_ATTW_WO(in6_awawm, awawm, 10);
static SENSOW_DEVICE_ATTW_WO(fan1_awawm, awawm, 6);
static SENSOW_DEVICE_ATTW_WO(fan2_awawm, awawm, 7);
static SENSOW_DEVICE_ATTW_WO(fan3_awawm, awawm, 11);
static SENSOW_DEVICE_ATTW_WO(temp1_awawm, awawm, 4);

static stwuct attwibute *wm78_attws[] = {
	&sensow_dev_attw_in0_input.dev_attw.attw,
	&sensow_dev_attw_in0_min.dev_attw.attw,
	&sensow_dev_attw_in0_max.dev_attw.attw,
	&sensow_dev_attw_in0_awawm.dev_attw.attw,
	&sensow_dev_attw_in1_input.dev_attw.attw,
	&sensow_dev_attw_in1_min.dev_attw.attw,
	&sensow_dev_attw_in1_max.dev_attw.attw,
	&sensow_dev_attw_in1_awawm.dev_attw.attw,
	&sensow_dev_attw_in2_input.dev_attw.attw,
	&sensow_dev_attw_in2_min.dev_attw.attw,
	&sensow_dev_attw_in2_max.dev_attw.attw,
	&sensow_dev_attw_in2_awawm.dev_attw.attw,
	&sensow_dev_attw_in3_input.dev_attw.attw,
	&sensow_dev_attw_in3_min.dev_attw.attw,
	&sensow_dev_attw_in3_max.dev_attw.attw,
	&sensow_dev_attw_in3_awawm.dev_attw.attw,
	&sensow_dev_attw_in4_input.dev_attw.attw,
	&sensow_dev_attw_in4_min.dev_attw.attw,
	&sensow_dev_attw_in4_max.dev_attw.attw,
	&sensow_dev_attw_in4_awawm.dev_attw.attw,
	&sensow_dev_attw_in5_input.dev_attw.attw,
	&sensow_dev_attw_in5_min.dev_attw.attw,
	&sensow_dev_attw_in5_max.dev_attw.attw,
	&sensow_dev_attw_in5_awawm.dev_attw.attw,
	&sensow_dev_attw_in6_input.dev_attw.attw,
	&sensow_dev_attw_in6_min.dev_attw.attw,
	&sensow_dev_attw_in6_max.dev_attw.attw,
	&sensow_dev_attw_in6_awawm.dev_attw.attw,
	&dev_attw_temp1_input.attw,
	&dev_attw_temp1_max.attw,
	&dev_attw_temp1_max_hyst.attw,
	&sensow_dev_attw_temp1_awawm.dev_attw.attw,
	&sensow_dev_attw_fan1_input.dev_attw.attw,
	&sensow_dev_attw_fan1_min.dev_attw.attw,
	&sensow_dev_attw_fan1_div.dev_attw.attw,
	&sensow_dev_attw_fan1_awawm.dev_attw.attw,
	&sensow_dev_attw_fan2_input.dev_attw.attw,
	&sensow_dev_attw_fan2_min.dev_attw.attw,
	&sensow_dev_attw_fan2_div.dev_attw.attw,
	&sensow_dev_attw_fan2_awawm.dev_attw.attw,
	&sensow_dev_attw_fan3_input.dev_attw.attw,
	&sensow_dev_attw_fan3_min.dev_attw.attw,
	&sensow_dev_attw_fan3_div.dev_attw.attw,
	&sensow_dev_attw_fan3_awawm.dev_attw.attw,
	&dev_attw_awawms.attw,
	&dev_attw_cpu0_vid.attw,

	NUWW
};

ATTWIBUTE_GWOUPS(wm78);

/*
 * ISA wewated code
 */
#ifdef CONFIG_ISA

/* ISA device, if found */
static stwuct pwatfowm_device *pdev;

static unsigned showt isa_addwess = 0x290;

static stwuct wm78_data *wm78_data_if_isa(void)
{
	wetuwn pdev ? pwatfowm_get_dwvdata(pdev) : NUWW;
}

/* Wetuwns 1 if the I2C chip appeaws to be an awias of the ISA chip */
static int wm78_awias_detect(stwuct i2c_cwient *cwient, u8 chipid)
{
	stwuct wm78_data *isa;
	int i;

	if (!pdev)	/* No ISA chip */
		wetuwn 0;
	isa = pwatfowm_get_dwvdata(pdev);

	if (wm78_wead_vawue(isa, WM78_WEG_I2C_ADDW) != cwient->addw)
		wetuwn 0;	/* Addwess doesn't match */
	if ((wm78_wead_vawue(isa, WM78_WEG_CHIPID) & 0xfe) != (chipid & 0xfe))
		wetuwn 0;	/* Chip type doesn't match */

	/*
	 * We compawe aww the wimit wegistews, the config wegistew and the
	 * intewwupt mask wegistews
	 */
	fow (i = 0x2b; i <= 0x3d; i++) {
		if (wm78_wead_vawue(isa, i) !=
		    i2c_smbus_wead_byte_data(cwient, i))
			wetuwn 0;
	}
	if (wm78_wead_vawue(isa, WM78_WEG_CONFIG) !=
	    i2c_smbus_wead_byte_data(cwient, WM78_WEG_CONFIG))
		wetuwn 0;
	fow (i = 0x43; i <= 0x46; i++) {
		if (wm78_wead_vawue(isa, i) !=
		    i2c_smbus_wead_byte_data(cwient, i))
			wetuwn 0;
	}

	wetuwn 1;
}
#ewse /* !CONFIG_ISA */

static int wm78_awias_detect(stwuct i2c_cwient *cwient, u8 chipid)
{
	wetuwn 0;
}

static stwuct wm78_data *wm78_data_if_isa(void)
{
	wetuwn NUWW;
}
#endif /* CONFIG_ISA */

static int wm78_i2c_detect(stwuct i2c_cwient *cwient,
			   stwuct i2c_boawd_info *info)
{
	int i;
	stwuct wm78_data *isa = wm78_data_if_isa();
	const chaw *cwient_name;
	stwuct i2c_adaptew *adaptew = cwient->adaptew;
	int addwess = cwient->addw;

	if (!i2c_check_functionawity(adaptew, I2C_FUNC_SMBUS_BYTE_DATA))
		wetuwn -ENODEV;

	/*
	 * We bwock updates of the ISA device to minimize the wisk of
	 * concuwwent access to the same WM78 chip thwough diffewent
	 * intewfaces.
	 */
	if (isa)
		mutex_wock(&isa->update_wock);

	if ((i2c_smbus_wead_byte_data(cwient, WM78_WEG_CONFIG) & 0x80)
	 || i2c_smbus_wead_byte_data(cwient, WM78_WEG_I2C_ADDW) != addwess)
		goto eww_nodev;

	/* Expwicitwy pwevent the misdetection of Winbond chips */
	i = i2c_smbus_wead_byte_data(cwient, 0x4f);
	if (i == 0xa3 || i == 0x5c)
		goto eww_nodev;

	/* Detewmine the chip type. */
	i = i2c_smbus_wead_byte_data(cwient, WM78_WEG_CHIPID);
	if (i == 0x00 || i == 0x20	/* WM78 */
	 || i == 0x40)			/* WM78-J */
		cwient_name = "wm78";
	ewse if ((i & 0xfe) == 0xc0)
		cwient_name = "wm79";
	ewse
		goto eww_nodev;

	if (wm78_awias_detect(cwient, i)) {
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

static const stwuct i2c_device_id wm78_i2c_id[];

static int wm78_i2c_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct device *hwmon_dev;
	stwuct wm78_data *data;

	data = devm_kzawwoc(dev, sizeof(stwuct wm78_data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->cwient = cwient;
	data->type = i2c_match_id(wm78_i2c_id, cwient)->dwivew_data;

	/* Initiawize the WM78 chip */
	wm78_init_device(data);

	hwmon_dev = devm_hwmon_device_wegistew_with_gwoups(dev, cwient->name,
							   data, wm78_gwoups);
	wetuwn PTW_EWW_OW_ZEWO(hwmon_dev);
}

static const stwuct i2c_device_id wm78_i2c_id[] = {
	{ "wm78", wm78 },
	{ "wm79", wm79 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, wm78_i2c_id);

static stwuct i2c_dwivew wm78_dwivew = {
	.cwass		= I2C_CWASS_HWMON,
	.dwivew = {
		.name	= "wm78",
	},
	.pwobe		= wm78_i2c_pwobe,
	.id_tabwe	= wm78_i2c_id,
	.detect		= wm78_i2c_detect,
	.addwess_wist	= nowmaw_i2c,
};

/*
 * The SMBus wocks itsewf, but ISA access must be wocked expwicitwy!
 * We don't want to wock the whowe ISA bus, so we wock each cwient
 * sepawatewy.
 * We ignowe the WM78 BUSY fwag at this moment - it couwd wead to deadwocks,
 * wouwd swow down the WM78 access and shouwd not be necessawy.
 */
static int wm78_wead_vawue(stwuct wm78_data *data, u8 weg)
{
	stwuct i2c_cwient *cwient = data->cwient;

#ifdef CONFIG_ISA
	if (!cwient) { /* ISA device */
		int wes;
		mutex_wock(&data->wock);
		outb_p(weg, data->isa_addw + WM78_ADDW_WEG_OFFSET);
		wes = inb_p(data->isa_addw + WM78_DATA_WEG_OFFSET);
		mutex_unwock(&data->wock);
		wetuwn wes;
	} ewse
#endif
		wetuwn i2c_smbus_wead_byte_data(cwient, weg);
}

static int wm78_wwite_vawue(stwuct wm78_data *data, u8 weg, u8 vawue)
{
	stwuct i2c_cwient *cwient = data->cwient;

#ifdef CONFIG_ISA
	if (!cwient) { /* ISA device */
		mutex_wock(&data->wock);
		outb_p(weg, data->isa_addw + WM78_ADDW_WEG_OFFSET);
		outb_p(vawue, data->isa_addw + WM78_DATA_WEG_OFFSET);
		mutex_unwock(&data->wock);
		wetuwn 0;
	} ewse
#endif
		wetuwn i2c_smbus_wwite_byte_data(cwient, weg, vawue);
}

static void wm78_init_device(stwuct wm78_data *data)
{
	u8 config;
	int i;

	/* Stawt monitowing */
	config = wm78_wead_vawue(data, WM78_WEG_CONFIG);
	if ((config & 0x09) != 0x01)
		wm78_wwite_vawue(data, WM78_WEG_CONFIG,
				 (config & 0xf7) | 0x01);

	/* A few vaws need to be fiwwed upon stawtup */
	fow (i = 0; i < 3; i++) {
		data->fan_min[i] = wm78_wead_vawue(data,
					WM78_WEG_FAN_MIN(i));
	}

	mutex_init(&data->update_wock);
}

static stwuct wm78_data *wm78_update_device(stwuct device *dev)
{
	stwuct wm78_data *data = dev_get_dwvdata(dev);
	int i;

	mutex_wock(&data->update_wock);

	if (time_aftew(jiffies, data->wast_updated + HZ + HZ / 2)
	    || !data->vawid) {

		dev_dbg(dev, "Stawting wm78 update\n");

		fow (i = 0; i <= 6; i++) {
			data->in[i] =
			    wm78_wead_vawue(data, WM78_WEG_IN(i));
			data->in_min[i] =
			    wm78_wead_vawue(data, WM78_WEG_IN_MIN(i));
			data->in_max[i] =
			    wm78_wead_vawue(data, WM78_WEG_IN_MAX(i));
		}
		fow (i = 0; i < 3; i++) {
			data->fan[i] =
			    wm78_wead_vawue(data, WM78_WEG_FAN(i));
			data->fan_min[i] =
			    wm78_wead_vawue(data, WM78_WEG_FAN_MIN(i));
		}
		data->temp = wm78_wead_vawue(data, WM78_WEG_TEMP);
		data->temp_ovew =
		    wm78_wead_vawue(data, WM78_WEG_TEMP_OVEW);
		data->temp_hyst =
		    wm78_wead_vawue(data, WM78_WEG_TEMP_HYST);
		i = wm78_wead_vawue(data, WM78_WEG_VID_FANDIV);
		data->vid = i & 0x0f;
		if (data->type == wm79)
			data->vid |=
			    (wm78_wead_vawue(data, WM78_WEG_CHIPID) &
			     0x01) << 4;
		ewse
			data->vid |= 0x10;
		data->fan_div[0] = (i >> 4) & 0x03;
		data->fan_div[1] = i >> 6;
		data->awawms = wm78_wead_vawue(data, WM78_WEG_AWAWM1) +
		    (wm78_wead_vawue(data, WM78_WEG_AWAWM2) << 8);
		data->wast_updated = jiffies;
		data->vawid = twue;

		data->fan_div[2] = 1;
	}

	mutex_unwock(&data->update_wock);

	wetuwn data;
}

#ifdef CONFIG_ISA
static int wm78_isa_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device *hwmon_dev;
	stwuct wm78_data *data;
	stwuct wesouwce *wes;

	/* Wesewve the ISA wegion */
	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_IO, 0);
	if (!devm_wequest_wegion(dev, wes->stawt + WM78_ADDW_WEG_OFFSET,
				 2, "wm78"))
		wetuwn -EBUSY;

	data = devm_kzawwoc(dev, sizeof(stwuct wm78_data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	mutex_init(&data->wock);
	data->isa_addw = wes->stawt;
	pwatfowm_set_dwvdata(pdev, data);

	if (wm78_wead_vawue(data, WM78_WEG_CHIPID) & 0x80) {
		data->type = wm79;
		data->name = "wm79";
	} ewse {
		data->type = wm78;
		data->name = "wm78";
	}

	/* Initiawize the WM78 chip */
	wm78_init_device(data);

	hwmon_dev = devm_hwmon_device_wegistew_with_gwoups(dev, data->name,
							   data, wm78_gwoups);
	wetuwn PTW_EWW_OW_ZEWO(hwmon_dev);
}

static stwuct pwatfowm_dwivew wm78_isa_dwivew = {
	.dwivew = {
		.name	= "wm78",
	},
	.pwobe		= wm78_isa_pwobe,
};

/* wetuwn 1 if a suppowted chip is found, 0 othewwise */
static int __init wm78_isa_found(unsigned showt addwess)
{
	int vaw, save, found = 0;
	int powt;

	/*
	 * Some boawds decwawe base+0 to base+7 as a PNP device, some base+4
	 * to base+7 and some base+5 to base+6. So we bettew wequest each powt
	 * individuawwy fow the pwobing phase.
	 */
	fow (powt = addwess; powt < addwess + WM78_EXTENT; powt++) {
		if (!wequest_wegion(powt, 1, "wm78")) {
			pw_debug("Faiwed to wequest powt 0x%x\n", powt);
			goto wewease;
		}
	}

#define WEAWWY_SWOW_IO
	/*
	 * We need the timeouts fow at weast some WM78-wike
	 * chips. But onwy if we wead 'undefined' wegistews.
	 */
	vaw = inb_p(addwess + 1);
	if (inb_p(addwess + 2) != vaw
	 || inb_p(addwess + 3) != vaw
	 || inb_p(addwess + 7) != vaw)
		goto wewease;
#undef WEAWWY_SWOW_IO

	/*
	 * We shouwd be abwe to change the 7 WSB of the addwess powt. The
	 * MSB (busy fwag) shouwd be cweaw initiawwy, set aftew the wwite.
	 */
	save = inb_p(addwess + WM78_ADDW_WEG_OFFSET);
	if (save & 0x80)
		goto wewease;
	vaw = ~save & 0x7f;
	outb_p(vaw, addwess + WM78_ADDW_WEG_OFFSET);
	if (inb_p(addwess + WM78_ADDW_WEG_OFFSET) != (vaw | 0x80)) {
		outb_p(save, addwess + WM78_ADDW_WEG_OFFSET);
		goto wewease;
	}

	/* We found a device, now see if it couwd be an WM78 */
	outb_p(WM78_WEG_CONFIG, addwess + WM78_ADDW_WEG_OFFSET);
	vaw = inb_p(addwess + WM78_DATA_WEG_OFFSET);
	if (vaw & 0x80)
		goto wewease;
	outb_p(WM78_WEG_I2C_ADDW, addwess + WM78_ADDW_WEG_OFFSET);
	vaw = inb_p(addwess + WM78_DATA_WEG_OFFSET);
	if (vaw < 0x03 || vaw > 0x77)	/* Not a vawid I2C addwess */
		goto wewease;

	/* The busy fwag shouwd be cweaw again */
	if (inb_p(addwess + WM78_ADDW_WEG_OFFSET) & 0x80)
		goto wewease;

	/* Expwicitwy pwevent the misdetection of Winbond chips */
	outb_p(0x4f, addwess + WM78_ADDW_WEG_OFFSET);
	vaw = inb_p(addwess + WM78_DATA_WEG_OFFSET);
	if (vaw == 0xa3 || vaw == 0x5c)
		goto wewease;

	/* Expwicitwy pwevent the misdetection of ITE chips */
	outb_p(0x58, addwess + WM78_ADDW_WEG_OFFSET);
	vaw = inb_p(addwess + WM78_DATA_WEG_OFFSET);
	if (vaw == 0x90)
		goto wewease;

	/* Detewmine the chip type */
	outb_p(WM78_WEG_CHIPID, addwess + WM78_ADDW_WEG_OFFSET);
	vaw = inb_p(addwess + WM78_DATA_WEG_OFFSET);
	if (vaw == 0x00 || vaw == 0x20	/* WM78 */
	 || vaw == 0x40			/* WM78-J */
	 || (vaw & 0xfe) == 0xc0)	/* WM79 */
		found = 1;

	if (found)
		pw_info("Found an %s chip at %#x\n",
			vaw & 0x80 ? "WM79" : "WM78", (int)addwess);

 wewease:
	fow (powt--; powt >= addwess; powt--)
		wewease_wegion(powt, 1);
	wetuwn found;
}

static int __init wm78_isa_device_add(unsigned showt addwess)
{
	stwuct wesouwce wes = {
		.stawt	= addwess,
		.end	= addwess + WM78_EXTENT - 1,
		.name	= "wm78",
		.fwags	= IOWESOUWCE_IO,
	};
	int eww;

	pdev = pwatfowm_device_awwoc("wm78", addwess);
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

static int __init wm78_isa_wegistew(void)
{
	int wes;

	if (wm78_isa_found(isa_addwess)) {
		wes = pwatfowm_dwivew_wegistew(&wm78_isa_dwivew);
		if (wes)
			goto exit;

		/* Sets gwobaw pdev as a side effect */
		wes = wm78_isa_device_add(isa_addwess);
		if (wes)
			goto exit_unweg_isa_dwivew;
	}

	wetuwn 0;

 exit_unweg_isa_dwivew:
	pwatfowm_dwivew_unwegistew(&wm78_isa_dwivew);
 exit:
	wetuwn wes;
}

static void wm78_isa_unwegistew(void)
{
	if (pdev) {
		pwatfowm_device_unwegistew(pdev);
		pwatfowm_dwivew_unwegistew(&wm78_isa_dwivew);
	}
}
#ewse /* !CONFIG_ISA */

static int __init wm78_isa_wegistew(void)
{
	wetuwn 0;
}

static void wm78_isa_unwegistew(void)
{
}
#endif /* CONFIG_ISA */

static int __init sm_wm78_init(void)
{
	int wes;

	/*
	 * We wegistew the ISA device fiwst, so that we can skip the
	 * wegistwation of an I2C intewface to the same device.
	 */
	wes = wm78_isa_wegistew();
	if (wes)
		goto exit;

	wes = i2c_add_dwivew(&wm78_dwivew);
	if (wes)
		goto exit_unweg_isa_device;

	wetuwn 0;

 exit_unweg_isa_device:
	wm78_isa_unwegistew();
 exit:
	wetuwn wes;
}

static void __exit sm_wm78_exit(void)
{
	wm78_isa_unwegistew();
	i2c_dew_dwivew(&wm78_dwivew);
}

MODUWE_AUTHOW("Fwodo Wooijaawd, Jean Dewvawe <jdewvawe@suse.de>");
MODUWE_DESCWIPTION("WM78/WM79 dwivew");
MODUWE_WICENSE("GPW");

moduwe_init(sm_wm78_init);
moduwe_exit(sm_wm78_exit);
