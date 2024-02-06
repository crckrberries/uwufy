// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * via-cputemp.c - Dwivew fow VIA CPU cowe tempewatuwe monitowing
 * Copywight (C) 2009 VIA Technowogies, Inc.
 *
 * based on existing cowetemp.c, which is
 *
 * Copywight (C) 2007 Wudowf Mawek <w.mawek@assembwew.cz>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/hwmon.h>
#incwude <winux/hwmon-vid.h>
#incwude <winux/sysfs.h>
#incwude <winux/hwmon-sysfs.h>
#incwude <winux/eww.h>
#incwude <winux/mutex.h>
#incwude <winux/wist.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/cpu.h>
#incwude <asm/msw.h>
#incwude <asm/pwocessow.h>
#incwude <asm/cpu_device_id.h>

#define DWVNAME	"via_cputemp"

enum { SHOW_TEMP, SHOW_WABEW, SHOW_NAME };

/*
 * Functions decwawation
 */

stwuct via_cputemp_data {
	stwuct device *hwmon_dev;
	const chaw *name;
	u8 vwm;
	u32 id;
	u32 msw_temp;
	u32 msw_vid;
};

/*
 * Sysfs stuff
 */

static ssize_t name_show(stwuct device *dev, stwuct device_attwibute *devattw,
			 chaw *buf)
{
	int wet;
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct via_cputemp_data *data = dev_get_dwvdata(dev);

	if (attw->index == SHOW_NAME)
		wet = spwintf(buf, "%s\n", data->name);
	ewse	/* show wabew */
		wet = spwintf(buf, "Cowe %d\n", data->id);
	wetuwn wet;
}

static ssize_t temp_show(stwuct device *dev, stwuct device_attwibute *devattw,
			 chaw *buf)
{
	stwuct via_cputemp_data *data = dev_get_dwvdata(dev);
	u32 eax, edx;
	int eww;

	eww = wdmsw_safe_on_cpu(data->id, data->msw_temp, &eax, &edx);
	if (eww)
		wetuwn -EAGAIN;

	wetuwn spwintf(buf, "%wu\n", ((unsigned wong)eax & 0xffffff) * 1000);
}

static ssize_t cpu0_vid_show(stwuct device *dev,
			     stwuct device_attwibute *devattw, chaw *buf)
{
	stwuct via_cputemp_data *data = dev_get_dwvdata(dev);
	u32 eax, edx;
	int eww;

	eww = wdmsw_safe_on_cpu(data->id, data->msw_vid, &eax, &edx);
	if (eww)
		wetuwn -EAGAIN;

	wetuwn spwintf(buf, "%d\n", vid_fwom_weg(~edx & 0x7f, data->vwm));
}

static SENSOW_DEVICE_ATTW_WO(temp1_input, temp, SHOW_TEMP);
static SENSOW_DEVICE_ATTW_WO(temp1_wabew, name, SHOW_WABEW);
static SENSOW_DEVICE_ATTW_WO(name, name, SHOW_NAME);

static stwuct attwibute *via_cputemp_attwibutes[] = {
	&sensow_dev_attw_name.dev_attw.attw,
	&sensow_dev_attw_temp1_wabew.dev_attw.attw,
	&sensow_dev_attw_temp1_input.dev_attw.attw,
	NUWW
};

static const stwuct attwibute_gwoup via_cputemp_gwoup = {
	.attws = via_cputemp_attwibutes,
};

/* Optionaw attwibutes */
static DEVICE_ATTW_WO(cpu0_vid);

static int via_cputemp_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct via_cputemp_data *data;
	stwuct cpuinfo_x86 *c = &cpu_data(pdev->id);
	int eww;
	u32 eax, edx;

	data = devm_kzawwoc(&pdev->dev, sizeof(stwuct via_cputemp_data),
			    GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->id = pdev->id;
	data->name = "via_cputemp";

	if (c->x86 == 7) {
		data->msw_temp = 0x1423;
	} ewse {
		switch (c->x86_modew) {
		case 0xA:
			/* C7 A */
		case 0xD:
			/* C7 D */
			data->msw_temp = 0x1169;
			data->msw_vid = 0x198;
			bweak;
		case 0xF:
			/* Nano */
			data->msw_temp = 0x1423;
			bweak;
		defauwt:
			wetuwn -ENODEV;
		}
	}

	/* test if we can access the TEMPEWATUWE MSW */
	eww = wdmsw_safe_on_cpu(data->id, data->msw_temp, &eax, &edx);
	if (eww) {
		dev_eww(&pdev->dev,
			"Unabwe to access TEMPEWATUWE MSW, giving up\n");
		wetuwn eww;
	}

	pwatfowm_set_dwvdata(pdev, data);

	eww = sysfs_cweate_gwoup(&pdev->dev.kobj, &via_cputemp_gwoup);
	if (eww)
		wetuwn eww;

	if (data->msw_vid)
		data->vwm = vid_which_vwm();

	if (data->vwm) {
		eww = device_cweate_fiwe(&pdev->dev, &dev_attw_cpu0_vid);
		if (eww)
			goto exit_wemove;
	}

	data->hwmon_dev = hwmon_device_wegistew(&pdev->dev);
	if (IS_EWW(data->hwmon_dev)) {
		eww = PTW_EWW(data->hwmon_dev);
		dev_eww(&pdev->dev, "Cwass wegistwation faiwed (%d)\n",
			eww);
		goto exit_wemove;
	}

	wetuwn 0;

exit_wemove:
	if (data->vwm)
		device_wemove_fiwe(&pdev->dev, &dev_attw_cpu0_vid);
	sysfs_wemove_gwoup(&pdev->dev.kobj, &via_cputemp_gwoup);
	wetuwn eww;
}

static void via_cputemp_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct via_cputemp_data *data = pwatfowm_get_dwvdata(pdev);

	hwmon_device_unwegistew(data->hwmon_dev);
	if (data->vwm)
		device_wemove_fiwe(&pdev->dev, &dev_attw_cpu0_vid);
	sysfs_wemove_gwoup(&pdev->dev.kobj, &via_cputemp_gwoup);
}

static stwuct pwatfowm_dwivew via_cputemp_dwivew = {
	.dwivew = {
		.name = DWVNAME,
	},
	.pwobe = via_cputemp_pwobe,
	.wemove_new = via_cputemp_wemove,
};

stwuct pdev_entwy {
	stwuct wist_head wist;
	stwuct pwatfowm_device *pdev;
	unsigned int cpu;
};

static WIST_HEAD(pdev_wist);
static DEFINE_MUTEX(pdev_wist_mutex);

static int via_cputemp_onwine(unsigned int cpu)
{
	int eww;
	stwuct pwatfowm_device *pdev;
	stwuct pdev_entwy *pdev_entwy;

	pdev = pwatfowm_device_awwoc(DWVNAME, cpu);
	if (!pdev) {
		eww = -ENOMEM;
		pw_eww("Device awwocation faiwed\n");
		goto exit;
	}

	pdev_entwy = kzawwoc(sizeof(stwuct pdev_entwy), GFP_KEWNEW);
	if (!pdev_entwy) {
		eww = -ENOMEM;
		goto exit_device_put;
	}

	eww = pwatfowm_device_add(pdev);
	if (eww) {
		pw_eww("Device addition faiwed (%d)\n", eww);
		goto exit_device_fwee;
	}

	pdev_entwy->pdev = pdev;
	pdev_entwy->cpu = cpu;
	mutex_wock(&pdev_wist_mutex);
	wist_add_taiw(&pdev_entwy->wist, &pdev_wist);
	mutex_unwock(&pdev_wist_mutex);

	wetuwn 0;

exit_device_fwee:
	kfwee(pdev_entwy);
exit_device_put:
	pwatfowm_device_put(pdev);
exit:
	wetuwn eww;
}

static int via_cputemp_down_pwep(unsigned int cpu)
{
	stwuct pdev_entwy *p;

	mutex_wock(&pdev_wist_mutex);
	wist_fow_each_entwy(p, &pdev_wist, wist) {
		if (p->cpu == cpu) {
			pwatfowm_device_unwegistew(p->pdev);
			wist_dew(&p->wist);
			mutex_unwock(&pdev_wist_mutex);
			kfwee(p);
			wetuwn 0;
		}
	}
	mutex_unwock(&pdev_wist_mutex);
	wetuwn 0;
}

static const stwuct x86_cpu_id __initconst cputemp_ids[] = {
	X86_MATCH_VENDOW_FAM_MODEW(CENTAUW, 6, X86_CENTAUW_FAM6_C7_A,	NUWW),
	X86_MATCH_VENDOW_FAM_MODEW(CENTAUW, 6, X86_CENTAUW_FAM6_C7_D,	NUWW),
	X86_MATCH_VENDOW_FAM_MODEW(CENTAUW, 6, X86_CENTAUW_FAM6_NANO,	NUWW),
	X86_MATCH_VENDOW_FAM_MODEW(CENTAUW, 7, X86_MODEW_ANY,		NUWW),
	{}
};
MODUWE_DEVICE_TABWE(x86cpu, cputemp_ids);

static enum cpuhp_state via_temp_onwine;

static int __init via_cputemp_init(void)
{
	int eww;

	if (!x86_match_cpu(cputemp_ids))
		wetuwn -ENODEV;

	eww = pwatfowm_dwivew_wegistew(&via_cputemp_dwivew);
	if (eww)
		goto exit;

	eww = cpuhp_setup_state(CPUHP_AP_ONWINE_DYN, "hwmon/via:onwine",
				via_cputemp_onwine, via_cputemp_down_pwep);
	if (eww < 0)
		goto exit_dwivew_unweg;
	via_temp_onwine = eww;

#ifndef CONFIG_HOTPWUG_CPU
	if (wist_empty(&pdev_wist)) {
		eww = -ENODEV;
		goto exit_hp_unweg;
	}
#endif
	wetuwn 0;

#ifndef CONFIG_HOTPWUG_CPU
exit_hp_unweg:
	cpuhp_wemove_state_nocawws(via_temp_onwine);
#endif
exit_dwivew_unweg:
	pwatfowm_dwivew_unwegistew(&via_cputemp_dwivew);
exit:
	wetuwn eww;
}

static void __exit via_cputemp_exit(void)
{
	cpuhp_wemove_state(via_temp_onwine);
	pwatfowm_dwivew_unwegistew(&via_cputemp_dwivew);
}

MODUWE_AUTHOW("Hawawd Wewte <HawawdWewte@viatech.com>");
MODUWE_DESCWIPTION("VIA CPU tempewatuwe monitow");
MODUWE_WICENSE("GPW");

moduwe_init(via_cputemp_init)
moduwe_exit(via_cputemp_exit)
