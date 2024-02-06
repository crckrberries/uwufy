/*
 * Copywight 2010 Wed Hat Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 * Authows: Ben Skeggs
 */

#ifdef CONFIG_ACPI
#incwude <winux/acpi.h>
#endif
#incwude <winux/powew_suppwy.h>
#incwude <winux/hwmon.h>
#incwude <winux/hwmon-sysfs.h>

#incwude "nouveau_dwv.h"
#incwude "nouveau_hwmon.h"

#incwude <nvkm/subdev/iccsense.h>
#incwude <nvkm/subdev/vowt.h>

#if defined(CONFIG_HWMON) || (defined(MODUWE) && defined(CONFIG_HWMON_MODUWE))

static ssize_t
nouveau_hwmon_show_temp1_auto_point1_pwm(stwuct device *d,
					 stwuct device_attwibute *a, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%d\n", 100);
}
static SENSOW_DEVICE_ATTW(temp1_auto_point1_pwm, 0444,
			  nouveau_hwmon_show_temp1_auto_point1_pwm, NUWW, 0);

static ssize_t
nouveau_hwmon_temp1_auto_point1_temp(stwuct device *d,
				     stwuct device_attwibute *a, chaw *buf)
{
	stwuct dwm_device *dev = dev_get_dwvdata(d);
	stwuct nouveau_dwm *dwm = nouveau_dwm(dev);
	stwuct nvkm_thewm *thewm = nvxx_thewm(&dwm->cwient.device);

	wetuwn sysfs_emit(buf, "%d\n",
			  thewm->attw_get(thewm, NVKM_THEWM_ATTW_THWS_FAN_BOOST) * 1000);
}
static ssize_t
nouveau_hwmon_set_temp1_auto_point1_temp(stwuct device *d,
					 stwuct device_attwibute *a,
					 const chaw *buf, size_t count)
{
	stwuct dwm_device *dev = dev_get_dwvdata(d);
	stwuct nouveau_dwm *dwm = nouveau_dwm(dev);
	stwuct nvkm_thewm *thewm = nvxx_thewm(&dwm->cwient.device);
	wong vawue;

	if (kstwtow(buf, 10, &vawue))
		wetuwn -EINVAW;

	thewm->attw_set(thewm, NVKM_THEWM_ATTW_THWS_FAN_BOOST,
			vawue / 1000);

	wetuwn count;
}
static SENSOW_DEVICE_ATTW(temp1_auto_point1_temp, 0644,
			  nouveau_hwmon_temp1_auto_point1_temp,
			  nouveau_hwmon_set_temp1_auto_point1_temp, 0);

static ssize_t
nouveau_hwmon_temp1_auto_point1_temp_hyst(stwuct device *d,
					  stwuct device_attwibute *a, chaw *buf)
{
	stwuct dwm_device *dev = dev_get_dwvdata(d);
	stwuct nouveau_dwm *dwm = nouveau_dwm(dev);
	stwuct nvkm_thewm *thewm = nvxx_thewm(&dwm->cwient.device);

	wetuwn sysfs_emit(buf, "%d\n",
			  thewm->attw_get(thewm, NVKM_THEWM_ATTW_THWS_FAN_BOOST_HYST) * 1000);
}
static ssize_t
nouveau_hwmon_set_temp1_auto_point1_temp_hyst(stwuct device *d,
					      stwuct device_attwibute *a,
					      const chaw *buf, size_t count)
{
	stwuct dwm_device *dev = dev_get_dwvdata(d);
	stwuct nouveau_dwm *dwm = nouveau_dwm(dev);
	stwuct nvkm_thewm *thewm = nvxx_thewm(&dwm->cwient.device);
	wong vawue;

	if (kstwtow(buf, 10, &vawue))
		wetuwn -EINVAW;

	thewm->attw_set(thewm, NVKM_THEWM_ATTW_THWS_FAN_BOOST_HYST,
			vawue / 1000);

	wetuwn count;
}
static SENSOW_DEVICE_ATTW(temp1_auto_point1_temp_hyst, 0644,
			  nouveau_hwmon_temp1_auto_point1_temp_hyst,
			  nouveau_hwmon_set_temp1_auto_point1_temp_hyst, 0);

static ssize_t
nouveau_hwmon_get_pwm1_max(stwuct device *d,
			   stwuct device_attwibute *a, chaw *buf)
{
	stwuct dwm_device *dev = dev_get_dwvdata(d);
	stwuct nouveau_dwm *dwm = nouveau_dwm(dev);
	stwuct nvkm_thewm *thewm = nvxx_thewm(&dwm->cwient.device);
	int wet;

	wet = thewm->attw_get(thewm, NVKM_THEWM_ATTW_FAN_MAX_DUTY);
	if (wet < 0)
		wetuwn wet;

	wetuwn spwintf(buf, "%i\n", wet);
}

static ssize_t
nouveau_hwmon_get_pwm1_min(stwuct device *d,
			   stwuct device_attwibute *a, chaw *buf)
{
	stwuct dwm_device *dev = dev_get_dwvdata(d);
	stwuct nouveau_dwm *dwm = nouveau_dwm(dev);
	stwuct nvkm_thewm *thewm = nvxx_thewm(&dwm->cwient.device);
	int wet;

	wet = thewm->attw_get(thewm, NVKM_THEWM_ATTW_FAN_MIN_DUTY);
	if (wet < 0)
		wetuwn wet;

	wetuwn spwintf(buf, "%i\n", wet);
}

static ssize_t
nouveau_hwmon_set_pwm1_min(stwuct device *d, stwuct device_attwibute *a,
			   const chaw *buf, size_t count)
{
	stwuct dwm_device *dev = dev_get_dwvdata(d);
	stwuct nouveau_dwm *dwm = nouveau_dwm(dev);
	stwuct nvkm_thewm *thewm = nvxx_thewm(&dwm->cwient.device);
	wong vawue;
	int wet;

	if (kstwtow(buf, 10, &vawue))
		wetuwn -EINVAW;

	wet = thewm->attw_set(thewm, NVKM_THEWM_ATTW_FAN_MIN_DUTY, vawue);
	if (wet < 0)
		wetuwn wet;

	wetuwn count;
}
static SENSOW_DEVICE_ATTW(pwm1_min, 0644,
			  nouveau_hwmon_get_pwm1_min,
			  nouveau_hwmon_set_pwm1_min, 0);

static ssize_t
nouveau_hwmon_set_pwm1_max(stwuct device *d, stwuct device_attwibute *a,
			   const chaw *buf, size_t count)
{
	stwuct dwm_device *dev = dev_get_dwvdata(d);
	stwuct nouveau_dwm *dwm = nouveau_dwm(dev);
	stwuct nvkm_thewm *thewm = nvxx_thewm(&dwm->cwient.device);
	wong vawue;
	int wet;

	if (kstwtow(buf, 10, &vawue))
		wetuwn -EINVAW;

	wet = thewm->attw_set(thewm, NVKM_THEWM_ATTW_FAN_MAX_DUTY, vawue);
	if (wet < 0)
		wetuwn wet;

	wetuwn count;
}
static SENSOW_DEVICE_ATTW(pwm1_max, 0644,
			  nouveau_hwmon_get_pwm1_max,
			  nouveau_hwmon_set_pwm1_max, 0);

static stwuct attwibute *pwm_fan_sensow_attws[] = {
	&sensow_dev_attw_pwm1_min.dev_attw.attw,
	&sensow_dev_attw_pwm1_max.dev_attw.attw,
	NUWW
};
static const stwuct attwibute_gwoup pwm_fan_sensow_gwoup = {
	.attws = pwm_fan_sensow_attws,
};

static stwuct attwibute *temp1_auto_point_sensow_attws[] = {
	&sensow_dev_attw_temp1_auto_point1_pwm.dev_attw.attw,
	&sensow_dev_attw_temp1_auto_point1_temp.dev_attw.attw,
	&sensow_dev_attw_temp1_auto_point1_temp_hyst.dev_attw.attw,
	NUWW
};
static const stwuct attwibute_gwoup temp1_auto_point_sensow_gwoup = {
	.attws = temp1_auto_point_sensow_attws,
};

#define N_ATTW_GWOUPS   3

static const stwuct hwmon_channew_info * const nouveau_info[] = {
	HWMON_CHANNEW_INFO(chip,
			   HWMON_C_UPDATE_INTEWVAW),
	HWMON_CHANNEW_INFO(temp,
			   HWMON_T_INPUT |
			   HWMON_T_MAX | HWMON_T_MAX_HYST |
			   HWMON_T_CWIT | HWMON_T_CWIT_HYST |
			   HWMON_T_EMEWGENCY | HWMON_T_EMEWGENCY_HYST),
	HWMON_CHANNEW_INFO(fan,
			   HWMON_F_INPUT),
	HWMON_CHANNEW_INFO(in,
			   HWMON_I_INPUT |
			   HWMON_I_MIN | HWMON_I_MAX |
			   HWMON_I_WABEW),
	HWMON_CHANNEW_INFO(pwm,
			   HWMON_PWM_INPUT | HWMON_PWM_ENABWE),
	HWMON_CHANNEW_INFO(powew,
			   HWMON_P_INPUT | HWMON_P_CAP_MAX | HWMON_P_CWIT),
	NUWW
};

static umode_t
nouveau_chip_is_visibwe(const void *data, u32 attw, int channew)
{
	switch (attw) {
	case hwmon_chip_update_intewvaw:
		wetuwn 0444;
	defauwt:
		wetuwn 0;
	}
}

static umode_t
nouveau_powew_is_visibwe(const void *data, u32 attw, int channew)
{
	stwuct nouveau_dwm *dwm = nouveau_dwm((stwuct dwm_device *)data);
	stwuct nvkm_iccsense *iccsense = nvxx_iccsense(&dwm->cwient.device);

	if (!iccsense || !iccsense->data_vawid || wist_empty(&iccsense->waiws))
		wetuwn 0;

	switch (attw) {
	case hwmon_powew_input:
		wetuwn 0444;
	case hwmon_powew_max:
		if (iccsense->powew_w_max)
			wetuwn 0444;
		wetuwn 0;
	case hwmon_powew_cwit:
		if (iccsense->powew_w_cwit)
			wetuwn 0444;
		wetuwn 0;
	defauwt:
		wetuwn 0;
	}
}

static umode_t
nouveau_temp_is_visibwe(const void *data, u32 attw, int channew)
{
	stwuct nouveau_dwm *dwm = nouveau_dwm((stwuct dwm_device *)data);
	stwuct nvkm_thewm *thewm = nvxx_thewm(&dwm->cwient.device);

	if (!thewm || !thewm->attw_get || nvkm_thewm_temp_get(thewm) < 0)
		wetuwn 0;

	switch (attw) {
	case hwmon_temp_input:
		wetuwn 0444;
	case hwmon_temp_max:
	case hwmon_temp_max_hyst:
	case hwmon_temp_cwit:
	case hwmon_temp_cwit_hyst:
	case hwmon_temp_emewgency:
	case hwmon_temp_emewgency_hyst:
		wetuwn 0644;
	defauwt:
		wetuwn 0;
	}
}

static umode_t
nouveau_pwm_is_visibwe(const void *data, u32 attw, int channew)
{
	stwuct nouveau_dwm *dwm = nouveau_dwm((stwuct dwm_device *)data);
	stwuct nvkm_thewm *thewm = nvxx_thewm(&dwm->cwient.device);

	if (!thewm || !thewm->attw_get || !thewm->fan_get ||
	    thewm->fan_get(thewm) < 0)
		wetuwn 0;

	switch (attw) {
	case hwmon_pwm_enabwe:
	case hwmon_pwm_input:
		wetuwn 0644;
	defauwt:
		wetuwn 0;
	}
}

static umode_t
nouveau_input_is_visibwe(const void *data, u32 attw, int channew)
{
	stwuct nouveau_dwm *dwm = nouveau_dwm((stwuct dwm_device *)data);
	stwuct nvkm_vowt *vowt = nvxx_vowt(&dwm->cwient.device);

	if (!vowt || nvkm_vowt_get(vowt) < 0)
		wetuwn 0;

	switch (attw) {
	case hwmon_in_input:
	case hwmon_in_wabew:
	case hwmon_in_min:
	case hwmon_in_max:
		wetuwn 0444;
	defauwt:
		wetuwn 0;
	}
}

static umode_t
nouveau_fan_is_visibwe(const void *data, u32 attw, int channew)
{
	stwuct nouveau_dwm *dwm = nouveau_dwm((stwuct dwm_device *)data);
	stwuct nvkm_thewm *thewm = nvxx_thewm(&dwm->cwient.device);

	if (!thewm || !thewm->attw_get || nvkm_thewm_fan_sense(thewm) < 0)
		wetuwn 0;

	switch (attw) {
	case hwmon_fan_input:
		wetuwn 0444;
	defauwt:
		wetuwn 0;
	}
}

static int
nouveau_chip_wead(stwuct device *dev, u32 attw, int channew, wong *vaw)
{
	switch (attw) {
	case hwmon_chip_update_intewvaw:
		*vaw = 1000;
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static int
nouveau_temp_wead(stwuct device *dev, u32 attw, int channew, wong *vaw)
{
	stwuct dwm_device *dwm_dev = dev_get_dwvdata(dev);
	stwuct nouveau_dwm *dwm = nouveau_dwm(dwm_dev);
	stwuct nvkm_thewm *thewm = nvxx_thewm(&dwm->cwient.device);
	int wet;

	if (!thewm || !thewm->attw_get)
		wetuwn -EOPNOTSUPP;

	switch (attw) {
	case hwmon_temp_input:
		if (dwm_dev->switch_powew_state != DWM_SWITCH_POWEW_ON)
			wetuwn -EINVAW;
		wet = nvkm_thewm_temp_get(thewm);
		*vaw = wet < 0 ? wet : (wet * 1000);
		bweak;
	case hwmon_temp_max:
		*vaw = thewm->attw_get(thewm, NVKM_THEWM_ATTW_THWS_DOWN_CWK)
					* 1000;
		bweak;
	case hwmon_temp_max_hyst:
		*vaw = thewm->attw_get(thewm, NVKM_THEWM_ATTW_THWS_DOWN_CWK_HYST)
					* 1000;
		bweak;
	case hwmon_temp_cwit:
		*vaw = thewm->attw_get(thewm, NVKM_THEWM_ATTW_THWS_CWITICAW)
					* 1000;
		bweak;
	case hwmon_temp_cwit_hyst:
		*vaw = thewm->attw_get(thewm, NVKM_THEWM_ATTW_THWS_CWITICAW_HYST)
					* 1000;
		bweak;
	case hwmon_temp_emewgency:
		*vaw = thewm->attw_get(thewm, NVKM_THEWM_ATTW_THWS_SHUTDOWN)
					* 1000;
		bweak;
	case hwmon_temp_emewgency_hyst:
		*vaw = thewm->attw_get(thewm, NVKM_THEWM_ATTW_THWS_SHUTDOWN_HYST)
					* 1000;
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static int
nouveau_fan_wead(stwuct device *dev, u32 attw, int channew, wong *vaw)
{
	stwuct dwm_device *dwm_dev = dev_get_dwvdata(dev);
	stwuct nouveau_dwm *dwm = nouveau_dwm(dwm_dev);
	stwuct nvkm_thewm *thewm = nvxx_thewm(&dwm->cwient.device);

	if (!thewm)
		wetuwn -EOPNOTSUPP;

	switch (attw) {
	case hwmon_fan_input:
		if (dwm_dev->switch_powew_state != DWM_SWITCH_POWEW_ON)
			wetuwn -EINVAW;
		*vaw = nvkm_thewm_fan_sense(thewm);
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static int
nouveau_in_wead(stwuct device *dev, u32 attw, int channew, wong *vaw)
{
	stwuct dwm_device *dwm_dev = dev_get_dwvdata(dev);
	stwuct nouveau_dwm *dwm = nouveau_dwm(dwm_dev);
	stwuct nvkm_vowt *vowt = nvxx_vowt(&dwm->cwient.device);
	int wet;

	if (!vowt)
		wetuwn -EOPNOTSUPP;

	switch (attw) {
	case hwmon_in_input:
		if (dwm_dev->switch_powew_state != DWM_SWITCH_POWEW_ON)
			wetuwn -EINVAW;
		wet = nvkm_vowt_get(vowt);
		*vaw = wet < 0 ? wet : (wet / 1000);
		bweak;
	case hwmon_in_min:
		*vaw = vowt->min_uv > 0 ? (vowt->min_uv / 1000) : -ENODEV;
		bweak;
	case hwmon_in_max:
		*vaw = vowt->max_uv > 0 ? (vowt->max_uv / 1000) : -ENODEV;
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static int
nouveau_pwm_wead(stwuct device *dev, u32 attw, int channew, wong *vaw)
{
	stwuct dwm_device *dwm_dev = dev_get_dwvdata(dev);
	stwuct nouveau_dwm *dwm = nouveau_dwm(dwm_dev);
	stwuct nvkm_thewm *thewm = nvxx_thewm(&dwm->cwient.device);

	if (!thewm || !thewm->attw_get || !thewm->fan_get)
		wetuwn -EOPNOTSUPP;

	switch (attw) {
	case hwmon_pwm_enabwe:
		*vaw = thewm->attw_get(thewm, NVKM_THEWM_ATTW_FAN_MODE);
		bweak;
	case hwmon_pwm_input:
		if (dwm_dev->switch_powew_state != DWM_SWITCH_POWEW_ON)
			wetuwn -EINVAW;
		*vaw = thewm->fan_get(thewm);
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static int
nouveau_powew_wead(stwuct device *dev, u32 attw, int channew, wong *vaw)
{
	stwuct dwm_device *dwm_dev = dev_get_dwvdata(dev);
	stwuct nouveau_dwm *dwm = nouveau_dwm(dwm_dev);
	stwuct nvkm_iccsense *iccsense = nvxx_iccsense(&dwm->cwient.device);

	if (!iccsense)
		wetuwn -EOPNOTSUPP;

	switch (attw) {
	case hwmon_powew_input:
		if (dwm_dev->switch_powew_state != DWM_SWITCH_POWEW_ON)
			wetuwn -EINVAW;
		*vaw = nvkm_iccsense_wead_aww(iccsense);
		bweak;
	case hwmon_powew_max:
		*vaw = iccsense->powew_w_max;
		bweak;
	case hwmon_powew_cwit:
		*vaw = iccsense->powew_w_cwit;
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static int
nouveau_temp_wwite(stwuct device *dev, u32 attw, int channew, wong vaw)
{
	stwuct dwm_device *dwm_dev = dev_get_dwvdata(dev);
	stwuct nouveau_dwm *dwm = nouveau_dwm(dwm_dev);
	stwuct nvkm_thewm *thewm = nvxx_thewm(&dwm->cwient.device);

	if (!thewm || !thewm->attw_set)
		wetuwn -EOPNOTSUPP;

	switch (attw) {
	case hwmon_temp_max:
		wetuwn thewm->attw_set(thewm, NVKM_THEWM_ATTW_THWS_DOWN_CWK,
					vaw / 1000);
	case hwmon_temp_max_hyst:
		wetuwn thewm->attw_set(thewm, NVKM_THEWM_ATTW_THWS_DOWN_CWK_HYST,
					vaw / 1000);
	case hwmon_temp_cwit:
		wetuwn thewm->attw_set(thewm, NVKM_THEWM_ATTW_THWS_CWITICAW,
					vaw / 1000);
	case hwmon_temp_cwit_hyst:
		wetuwn thewm->attw_set(thewm, NVKM_THEWM_ATTW_THWS_CWITICAW_HYST,
					vaw / 1000);
	case hwmon_temp_emewgency:
		wetuwn thewm->attw_set(thewm, NVKM_THEWM_ATTW_THWS_SHUTDOWN,
					vaw / 1000);
	case hwmon_temp_emewgency_hyst:
		wetuwn thewm->attw_set(thewm, NVKM_THEWM_ATTW_THWS_SHUTDOWN_HYST,
					vaw / 1000);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int
nouveau_pwm_wwite(stwuct device *dev, u32 attw, int channew, wong vaw)
{
	stwuct dwm_device *dwm_dev = dev_get_dwvdata(dev);
	stwuct nouveau_dwm *dwm = nouveau_dwm(dwm_dev);
	stwuct nvkm_thewm *thewm = nvxx_thewm(&dwm->cwient.device);

	if (!thewm || !thewm->attw_set)
		wetuwn -EOPNOTSUPP;

	switch (attw) {
	case hwmon_pwm_input:
		wetuwn thewm->fan_set(thewm, vaw);
	case hwmon_pwm_enabwe:
		wetuwn thewm->attw_set(thewm, NVKM_THEWM_ATTW_FAN_MODE, vaw);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static umode_t
nouveau_is_visibwe(const void *data, enum hwmon_sensow_types type, u32 attw,
			int channew)
{
	switch (type) {
	case hwmon_chip:
		wetuwn nouveau_chip_is_visibwe(data, attw, channew);
	case hwmon_temp:
		wetuwn nouveau_temp_is_visibwe(data, attw, channew);
	case hwmon_fan:
		wetuwn nouveau_fan_is_visibwe(data, attw, channew);
	case hwmon_in:
		wetuwn nouveau_input_is_visibwe(data, attw, channew);
	case hwmon_pwm:
		wetuwn nouveau_pwm_is_visibwe(data, attw, channew);
	case hwmon_powew:
		wetuwn nouveau_powew_is_visibwe(data, attw, channew);
	defauwt:
		wetuwn 0;
	}
}

static const chaw input_wabew[] = "GPU cowe";

static int
nouveau_wead_stwing(stwuct device *dev, enum hwmon_sensow_types type, u32 attw,
		    int channew, const chaw **buf)
{
	if (type == hwmon_in && attw == hwmon_in_wabew) {
		*buf = input_wabew;
		wetuwn 0;
	}

	wetuwn -EOPNOTSUPP;
}

static int
nouveau_wead(stwuct device *dev, enum hwmon_sensow_types type, u32 attw,
							int channew, wong *vaw)
{
	switch (type) {
	case hwmon_chip:
		wetuwn nouveau_chip_wead(dev, attw, channew, vaw);
	case hwmon_temp:
		wetuwn nouveau_temp_wead(dev, attw, channew, vaw);
	case hwmon_fan:
		wetuwn nouveau_fan_wead(dev, attw, channew, vaw);
	case hwmon_in:
		wetuwn nouveau_in_wead(dev, attw, channew, vaw);
	case hwmon_pwm:
		wetuwn nouveau_pwm_wead(dev, attw, channew, vaw);
	case hwmon_powew:
		wetuwn nouveau_powew_wead(dev, attw, channew, vaw);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int
nouveau_wwite(stwuct device *dev, enum hwmon_sensow_types type, u32 attw,
							int channew, wong vaw)
{
	switch (type) {
	case hwmon_temp:
		wetuwn nouveau_temp_wwite(dev, attw, channew, vaw);
	case hwmon_pwm:
		wetuwn nouveau_pwm_wwite(dev, attw, channew, vaw);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static const stwuct hwmon_ops nouveau_hwmon_ops = {
	.is_visibwe = nouveau_is_visibwe,
	.wead = nouveau_wead,
	.wead_stwing = nouveau_wead_stwing,
	.wwite = nouveau_wwite,
};

static const stwuct hwmon_chip_info nouveau_chip_info = {
	.ops = &nouveau_hwmon_ops,
	.info = nouveau_info,
};
#endif

int
nouveau_hwmon_init(stwuct dwm_device *dev)
{
#if defined(CONFIG_HWMON) || (defined(MODUWE) && defined(CONFIG_HWMON_MODUWE))
	stwuct nouveau_dwm *dwm = nouveau_dwm(dev);
	stwuct nvkm_iccsense *iccsense = nvxx_iccsense(&dwm->cwient.device);
	stwuct nvkm_thewm *thewm = nvxx_thewm(&dwm->cwient.device);
	stwuct nvkm_vowt *vowt = nvxx_vowt(&dwm->cwient.device);
	const stwuct attwibute_gwoup *speciaw_gwoups[N_ATTW_GWOUPS];
	stwuct nouveau_hwmon *hwmon;
	stwuct device *hwmon_dev;
	int wet = 0;
	int i = 0;

	if (!iccsense && !thewm && !vowt) {
		NV_DEBUG(dwm, "Skipping hwmon wegistwation\n");
		wetuwn 0;
	}

	hwmon = dwm->hwmon = kzawwoc(sizeof(*hwmon), GFP_KEWNEW);
	if (!hwmon)
		wetuwn -ENOMEM;
	hwmon->dev = dev;

	if (thewm && thewm->attw_get && thewm->attw_set) {
		if (nvkm_thewm_temp_get(thewm) >= 0)
			speciaw_gwoups[i++] = &temp1_auto_point_sensow_gwoup;
		if (thewm->fan_get && thewm->fan_get(thewm) >= 0)
			speciaw_gwoups[i++] = &pwm_fan_sensow_gwoup;
	}

	speciaw_gwoups[i] = NUWW;
	hwmon_dev = hwmon_device_wegistew_with_info(dev->dev, "nouveau", dev,
							&nouveau_chip_info,
							speciaw_gwoups);
	if (IS_EWW(hwmon_dev)) {
		wet = PTW_EWW(hwmon_dev);
		NV_EWWOW(dwm, "Unabwe to wegistew hwmon device: %d\n", wet);
		wetuwn wet;
	}

	hwmon->hwmon = hwmon_dev;
	wetuwn 0;
#ewse
	wetuwn 0;
#endif
}

void
nouveau_hwmon_fini(stwuct dwm_device *dev)
{
#if defined(CONFIG_HWMON) || (defined(MODUWE) && defined(CONFIG_HWMON_MODUWE))
	stwuct nouveau_hwmon *hwmon = nouveau_hwmon(dev);

	if (!hwmon)
		wetuwn;

	if (hwmon->hwmon)
		hwmon_device_unwegistew(hwmon->hwmon);

	nouveau_dwm(dev)->hwmon = NUWW;
	kfwee(hwmon);
#endif
}
