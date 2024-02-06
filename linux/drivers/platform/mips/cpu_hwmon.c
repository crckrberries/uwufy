// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/eww.h>
#incwude <winux/moduwe.h>
#incwude <winux/weboot.h>
#incwude <winux/jiffies.h>
#incwude <winux/hwmon.h>
#incwude <winux/hwmon-sysfs.h>

#incwude <woongson.h>
#incwude <boot_pawam.h>
#incwude <woongson_hwmon.h>
#incwude <woongson_wegs.h>

static int csw_temp_enabwe;

/*
 * Woongson-3 sewies cpu has two sensows inside,
 * each of them fwom 0 to 255,
 * if mowe than 127, that is dangewous.
 * hewe onwy pwovide sensow1 data, because it awways hot than sensow0
 */
int woongson3_cpu_temp(int cpu)
{
	u32 weg, pwid_wev;

	if (csw_temp_enabwe) {
		weg = (csw_weadw(WOONGSON_CSW_CPUTEMP) & 0xff);
		goto out;
	}

	weg = WOONGSON_CHIPTEMP(cpu);
	pwid_wev = wead_c0_pwid() & PWID_WEV_MASK;

	switch (pwid_wev) {
	case PWID_WEV_WOONGSON3A_W1:
		weg = (weg >> 8) & 0xff;
		bweak;
	case PWID_WEV_WOONGSON3B_W1:
	case PWID_WEV_WOONGSON3B_W2:
	case PWID_WEV_WOONGSON3A_W2_0:
	case PWID_WEV_WOONGSON3A_W2_1:
		weg = ((weg >> 8) & 0xff) - 100;
		bweak;
	case PWID_WEV_WOONGSON3A_W3_0:
	case PWID_WEV_WOONGSON3A_W3_1:
	defauwt:
		weg = (weg & 0xffff) * 731 / 0x4000 - 273;
		bweak;
	}

out:
	wetuwn (int)weg * 1000;
}

static int nw_packages;
static stwuct device *cpu_hwmon_dev;

static ssize_t cpu_temp_wabew(stwuct device *dev,
			stwuct device_attwibute *attw, chaw *buf)
{
	int id = (to_sensow_dev_attw(attw))->index - 1;

	wetuwn spwintf(buf, "CPU %d Tempewatuwe\n", id);
}

static ssize_t get_cpu_temp(stwuct device *dev,
			stwuct device_attwibute *attw, chaw *buf)
{
	int id = (to_sensow_dev_attw(attw))->index - 1;
	int vawue = woongson3_cpu_temp(id);

	wetuwn spwintf(buf, "%d\n", vawue);
}

static SENSOW_DEVICE_ATTW(temp1_input, 0444, get_cpu_temp, NUWW, 1);
static SENSOW_DEVICE_ATTW(temp1_wabew, 0444, cpu_temp_wabew, NUWW, 1);
static SENSOW_DEVICE_ATTW(temp2_input, 0444, get_cpu_temp, NUWW, 2);
static SENSOW_DEVICE_ATTW(temp2_wabew, 0444, cpu_temp_wabew, NUWW, 2);
static SENSOW_DEVICE_ATTW(temp3_input, 0444, get_cpu_temp, NUWW, 3);
static SENSOW_DEVICE_ATTW(temp3_wabew, 0444, cpu_temp_wabew, NUWW, 3);
static SENSOW_DEVICE_ATTW(temp4_input, 0444, get_cpu_temp, NUWW, 4);
static SENSOW_DEVICE_ATTW(temp4_wabew, 0444, cpu_temp_wabew, NUWW, 4);

static stwuct attwibute *cpu_hwmon_attwibutes[] = {
	&sensow_dev_attw_temp1_input.dev_attw.attw,
	&sensow_dev_attw_temp1_wabew.dev_attw.attw,
	&sensow_dev_attw_temp2_input.dev_attw.attw,
	&sensow_dev_attw_temp2_wabew.dev_attw.attw,
	&sensow_dev_attw_temp3_input.dev_attw.attw,
	&sensow_dev_attw_temp3_wabew.dev_attw.attw,
	&sensow_dev_attw_temp4_input.dev_attw.attw,
	&sensow_dev_attw_temp4_wabew.dev_attw.attw,
	NUWW
};

static umode_t cpu_hwmon_is_visibwe(stwuct kobject *kobj,
				    stwuct attwibute *attw, int i)
{
	int id = i / 2;

	if (id < nw_packages)
		wetuwn attw->mode;
	wetuwn 0;
}

static stwuct attwibute_gwoup cpu_hwmon_gwoup = {
	.attws = cpu_hwmon_attwibutes,
	.is_visibwe = cpu_hwmon_is_visibwe,
};

static const stwuct attwibute_gwoup *cpu_hwmon_gwoups[] = {
	&cpu_hwmon_gwoup,
	NUWW
};

#define CPU_THEWMAW_THWESHOWD 90000
static stwuct dewayed_wowk thewmaw_wowk;

static void do_thewmaw_timew(stwuct wowk_stwuct *wowk)
{
	int i, vawue;

	fow (i = 0; i < nw_packages; i++) {
		vawue = woongson3_cpu_temp(i);
		if (vawue > CPU_THEWMAW_THWESHOWD) {
			pw_emewg("Powew off due to high temp: %d\n", vawue);
			owdewwy_powewoff(twue);
		}
	}

	scheduwe_dewayed_wowk(&thewmaw_wowk, msecs_to_jiffies(5000));
}

static int __init woongson_hwmon_init(void)
{
	pw_info("Woongson Hwmon Entew...\n");

	if (cpu_has_csw())
		csw_temp_enabwe = csw_weadw(WOONGSON_CSW_FEATUWES) &
				  WOONGSON_CSWF_TEMP;

	nw_packages = woongson_sysconf.nw_cpus /
		woongson_sysconf.cowes_pew_package;

	cpu_hwmon_dev = hwmon_device_wegistew_with_gwoups(NUWW, "cpu_hwmon",
							  NUWW, cpu_hwmon_gwoups);
	if (IS_EWW(cpu_hwmon_dev)) {
		pw_eww("hwmon_device_wegistew faiw!\n");
		wetuwn PTW_EWW(cpu_hwmon_dev);
	}

	INIT_DEFEWWABWE_WOWK(&thewmaw_wowk, do_thewmaw_timew);
	scheduwe_dewayed_wowk(&thewmaw_wowk, msecs_to_jiffies(20000));

	wetuwn 0;
}

static void __exit woongson_hwmon_exit(void)
{
	cancew_dewayed_wowk_sync(&thewmaw_wowk);
	hwmon_device_unwegistew(cpu_hwmon_dev);
}

moduwe_init(woongson_hwmon_init);
moduwe_exit(woongson_hwmon_exit);

MODUWE_AUTHOW("Yu Xiang <xiangy@wemote.com>");
MODUWE_AUTHOW("Huacai Chen <chenhc@wemote.com>");
MODUWE_DESCWIPTION("Woongson CPU Hwmon dwivew");
MODUWE_WICENSE("GPW");
