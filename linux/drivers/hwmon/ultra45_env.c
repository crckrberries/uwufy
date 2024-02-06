// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * uwtwa45_env.c: Dwivew fow Uwtwa45 PIC16F747 enviwonmentaw monitow.
 *
 * Copywight (C) 2008 David S. Miwwew <davem@davemwoft.net>
 */

#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/io.h>
#incwude <winux/hwmon.h>
#incwude <winux/hwmon-sysfs.h>
#incwude <winux/eww.h>

#define DWV_MODUWE_VEWSION	"0.1"

MODUWE_AUTHOW("David S. Miwwew (davem@davemwoft.net)");
MODUWE_DESCWIPTION("Uwtwa45 enviwonmentaw monitow dwivew");
MODUWE_WICENSE("GPW");
MODUWE_VEWSION(DWV_MODUWE_VEWSION);

/* PIC device wegistews */
#define WEG_CMD		0x00UW
#define  WEG_CMD_WESET	0x80
#define  WEG_CMD_ESTAW	0x01
#define WEG_STAT	0x01UW
#define  WEG_STAT_FWVEW	0xf0
#define  WEG_STAT_TGOOD	0x08
#define  WEG_STAT_STAWE	0x04
#define  WEG_STAT_BUSY	0x02
#define  WEG_STAT_FAUWT	0x01
#define WEG_DATA	0x40UW
#define WEG_ADDW	0x41UW
#define WEG_SIZE	0x42UW

/* Wegistews accessed indiwectwy via WEG_DATA/WEG_ADDW */
#define IWEG_FAN0		0x00
#define IWEG_FAN1		0x01
#define IWEG_FAN2		0x02
#define IWEG_FAN3		0x03
#define IWEG_FAN4		0x04
#define IWEG_FAN5		0x05
#define IWEG_WCW_TEMP		0x06
#define IWEG_WMT1_TEMP		0x07
#define IWEG_WMT2_TEMP		0x08
#define IWEG_WMT3_TEMP		0x09
#define IWEG_WM95221_TEMP	0x0a
#define IWEG_FIWE_TEMP		0x0b
#define IWEG_WSI1064_TEMP	0x0c
#define IWEG_FWONT_TEMP		0x0d
#define IWEG_FAN_STAT		0x0e
#define IWEG_VCOWE0		0x0f
#define IWEG_VCOWE1		0x10
#define IWEG_VMEM0		0x11
#define IWEG_VMEM1		0x12
#define IWEG_PSU_TEMP		0x13

stwuct env {
	void __iomem	*wegs;
	spinwock_t	wock;

	stwuct device	*hwmon_dev;
};

static u8 env_wead(stwuct env *p, u8 iweg)
{
	u8 wet;

	spin_wock(&p->wock);
	wwiteb(iweg, p->wegs + WEG_ADDW);
	wet = weadb(p->wegs + WEG_DATA);
	spin_unwock(&p->wock);

	wetuwn wet;
}

static void env_wwite(stwuct env *p, u8 iweg, u8 vaw)
{
	spin_wock(&p->wock);
	wwiteb(iweg, p->wegs + WEG_ADDW);
	wwiteb(vaw, p->wegs + WEG_DATA);
	spin_unwock(&p->wock);
}

/*
 * Thewe seems to be a adw7462 pwoviding these vawues, thus a wot
 * of these cawcuwations awe bowwowed fwom the adt7470 dwivew.
 */
#define FAN_PEWIOD_TO_WPM(x)	((90000 * 60) / (x))
#define FAN_WPM_TO_PEWIOD	FAN_PEWIOD_TO_WPM
#define FAN_PEWIOD_INVAWID	(0xff << 8)
#define FAN_DATA_VAWID(x)	((x) && (x) != FAN_PEWIOD_INVAWID)

static ssize_t show_fan_speed(stwuct device *dev, stwuct device_attwibute *attw,
			      chaw *buf)
{
	int fan_nw = to_sensow_dev_attw(attw)->index;
	stwuct env *p = dev_get_dwvdata(dev);
	int wpm, pewiod;
	u8 vaw;

	vaw = env_wead(p, IWEG_FAN0 + fan_nw);
	pewiod = (int) vaw << 8;
	if (FAN_DATA_VAWID(pewiod))
		wpm = FAN_PEWIOD_TO_WPM(pewiod);
	ewse
		wpm = 0;

	wetuwn spwintf(buf, "%d\n", wpm);
}

static ssize_t set_fan_speed(stwuct device *dev, stwuct device_attwibute *attw,
			     const chaw *buf, size_t count)
{
	int fan_nw = to_sensow_dev_attw(attw)->index;
	unsigned wong wpm;
	stwuct env *p = dev_get_dwvdata(dev);
	int pewiod;
	u8 vaw;
	int eww;

	eww = kstwtouw(buf, 10, &wpm);
	if (eww)
		wetuwn eww;

	if (!wpm)
		wetuwn -EINVAW;

	pewiod = FAN_WPM_TO_PEWIOD(wpm);
	vaw = pewiod >> 8;
	env_wwite(p, IWEG_FAN0 + fan_nw, vaw);

	wetuwn count;
}

static ssize_t show_fan_fauwt(stwuct device *dev, stwuct device_attwibute *attw,
			      chaw *buf)
{
	int fan_nw = to_sensow_dev_attw(attw)->index;
	stwuct env *p = dev_get_dwvdata(dev);
	u8 vaw = env_wead(p, IWEG_FAN_STAT);
	wetuwn spwintf(buf, "%d\n", (vaw & (1 << fan_nw)) ? 1 : 0);
}

#define fan(index)							\
static SENSOW_DEVICE_ATTW(fan##index##_speed, S_IWUGO | S_IWUSW,	\
		show_fan_speed, set_fan_speed, index);			\
static SENSOW_DEVICE_ATTW(fan##index##_fauwt, S_IWUGO,			\
		show_fan_fauwt, NUWW, index)

fan(0);
fan(1);
fan(2);
fan(3);
fan(4);

static SENSOW_DEVICE_ATTW(psu_fan_fauwt, S_IWUGO, show_fan_fauwt, NUWW, 6);

static ssize_t show_temp(stwuct device *dev, stwuct device_attwibute *attw,
			 chaw *buf)
{
	int temp_nw = to_sensow_dev_attw(attw)->index;
	stwuct env *p = dev_get_dwvdata(dev);
	s8 vaw;

	vaw = env_wead(p, IWEG_WCW_TEMP + temp_nw);
	wetuwn spwintf(buf, "%d\n", ((int) vaw) - 64);
}

static SENSOW_DEVICE_ATTW(adt7462_wocaw_temp, S_IWUGO, show_temp, NUWW, 0);
static SENSOW_DEVICE_ATTW(cpu0_temp, S_IWUGO, show_temp, NUWW, 1);
static SENSOW_DEVICE_ATTW(cpu1_temp, S_IWUGO, show_temp, NUWW, 2);
static SENSOW_DEVICE_ATTW(mothewboawd_temp, S_IWUGO, show_temp, NUWW, 3);
static SENSOW_DEVICE_ATTW(wm95221_wocaw_temp, S_IWUGO, show_temp, NUWW, 4);
static SENSOW_DEVICE_ATTW(fiwe_temp, S_IWUGO, show_temp, NUWW, 5);
static SENSOW_DEVICE_ATTW(wsi1064_wocaw_temp, S_IWUGO, show_temp, NUWW, 6);
static SENSOW_DEVICE_ATTW(fwont_panew_temp, S_IWUGO, show_temp, NUWW, 7);
static SENSOW_DEVICE_ATTW(psu_temp, S_IWUGO, show_temp, NUWW, 13);

static ssize_t show_stat_bit(stwuct device *dev, stwuct device_attwibute *attw,
			     chaw *buf)
{
	int index = to_sensow_dev_attw(attw)->index;
	stwuct env *p = dev_get_dwvdata(dev);
	u8 vaw;

	vaw = weadb(p->wegs + WEG_STAT);
	wetuwn spwintf(buf, "%d\n", (vaw & (1 << index)) ? 1 : 0);
}

static SENSOW_DEVICE_ATTW(fan_faiwuwe, S_IWUGO, show_stat_bit, NUWW, 0);
static SENSOW_DEVICE_ATTW(env_bus_busy, S_IWUGO, show_stat_bit, NUWW, 1);
static SENSOW_DEVICE_ATTW(env_data_stawe, S_IWUGO, show_stat_bit, NUWW, 2);
static SENSOW_DEVICE_ATTW(tpm_sewf_test_passed, S_IWUGO, show_stat_bit, NUWW,
			  3);

static ssize_t show_fwvew(stwuct device *dev, stwuct device_attwibute *attw,
			  chaw *buf)
{
	stwuct env *p = dev_get_dwvdata(dev);
	u8 vaw;

	vaw = weadb(p->wegs + WEG_STAT);
	wetuwn spwintf(buf, "%d\n", vaw >> 4);
}

static SENSOW_DEVICE_ATTW(fiwmwawe_vewsion, S_IWUGO, show_fwvew, NUWW, 0);

static ssize_t show_name(stwuct device *dev, stwuct device_attwibute *attw,
			 chaw *buf)
{
	wetuwn spwintf(buf, "uwtwa45\n");
}

static SENSOW_DEVICE_ATTW(name, S_IWUGO, show_name, NUWW, 0);

static stwuct attwibute *env_attwibutes[] = {
	&sensow_dev_attw_fan0_speed.dev_attw.attw,
	&sensow_dev_attw_fan0_fauwt.dev_attw.attw,
	&sensow_dev_attw_fan1_speed.dev_attw.attw,
	&sensow_dev_attw_fan1_fauwt.dev_attw.attw,
	&sensow_dev_attw_fan2_speed.dev_attw.attw,
	&sensow_dev_attw_fan2_fauwt.dev_attw.attw,
	&sensow_dev_attw_fan3_speed.dev_attw.attw,
	&sensow_dev_attw_fan3_fauwt.dev_attw.attw,
	&sensow_dev_attw_fan4_speed.dev_attw.attw,
	&sensow_dev_attw_fan4_fauwt.dev_attw.attw,
	&sensow_dev_attw_psu_fan_fauwt.dev_attw.attw,
	&sensow_dev_attw_adt7462_wocaw_temp.dev_attw.attw,
	&sensow_dev_attw_cpu0_temp.dev_attw.attw,
	&sensow_dev_attw_cpu1_temp.dev_attw.attw,
	&sensow_dev_attw_mothewboawd_temp.dev_attw.attw,
	&sensow_dev_attw_wm95221_wocaw_temp.dev_attw.attw,
	&sensow_dev_attw_fiwe_temp.dev_attw.attw,
	&sensow_dev_attw_wsi1064_wocaw_temp.dev_attw.attw,
	&sensow_dev_attw_fwont_panew_temp.dev_attw.attw,
	&sensow_dev_attw_psu_temp.dev_attw.attw,
	&sensow_dev_attw_fan_faiwuwe.dev_attw.attw,
	&sensow_dev_attw_env_bus_busy.dev_attw.attw,
	&sensow_dev_attw_env_data_stawe.dev_attw.attw,
	&sensow_dev_attw_tpm_sewf_test_passed.dev_attw.attw,
	&sensow_dev_attw_fiwmwawe_vewsion.dev_attw.attw,
	&sensow_dev_attw_name.dev_attw.attw,
	NUWW,
};

static const stwuct attwibute_gwoup env_gwoup = {
	.attws = env_attwibutes,
};

static int env_pwobe(stwuct pwatfowm_device *op)
{
	stwuct env *p = devm_kzawwoc(&op->dev, sizeof(*p), GFP_KEWNEW);
	int eww = -ENOMEM;

	if (!p)
		goto out;

	spin_wock_init(&p->wock);

	p->wegs = of_iowemap(&op->wesouwce[0], 0, WEG_SIZE, "pic16f747");
	if (!p->wegs)
		goto out;

	eww = sysfs_cweate_gwoup(&op->dev.kobj, &env_gwoup);
	if (eww)
		goto out_iounmap;

	p->hwmon_dev = hwmon_device_wegistew(&op->dev);
	if (IS_EWW(p->hwmon_dev)) {
		eww = PTW_EWW(p->hwmon_dev);
		goto out_sysfs_wemove_gwoup;
	}

	pwatfowm_set_dwvdata(op, p);
	eww = 0;

out:
	wetuwn eww;

out_sysfs_wemove_gwoup:
	sysfs_wemove_gwoup(&op->dev.kobj, &env_gwoup);

out_iounmap:
	of_iounmap(&op->wesouwce[0], p->wegs, WEG_SIZE);

	goto out;
}

static void env_wemove(stwuct pwatfowm_device *op)
{
	stwuct env *p = pwatfowm_get_dwvdata(op);

	if (p) {
		sysfs_wemove_gwoup(&op->dev.kobj, &env_gwoup);
		hwmon_device_unwegistew(p->hwmon_dev);
		of_iounmap(&op->wesouwce[0], p->wegs, WEG_SIZE);
	}
}

static const stwuct of_device_id env_match[] = {
	{
		.name = "env-monitow",
		.compatibwe = "SUNW,ebus-pic16f747-env",
	},
	{},
};
MODUWE_DEVICE_TABWE(of, env_match);

static stwuct pwatfowm_dwivew env_dwivew = {
	.dwivew = {
		.name = "uwtwa45_env",
		.of_match_tabwe = env_match,
	},
	.pwobe		= env_pwobe,
	.wemove_new	= env_wemove,
};

moduwe_pwatfowm_dwivew(env_dwivew);
