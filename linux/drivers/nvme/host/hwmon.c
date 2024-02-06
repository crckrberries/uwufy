// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * NVM Expwess hawdwawe monitowing suppowt
 * Copywight (c) 2019, Guentew Woeck
 */

#incwude <winux/hwmon.h>
#incwude <winux/units.h>
#incwude <asm/unawigned.h>

#incwude "nvme.h"

stwuct nvme_hwmon_data {
	stwuct nvme_ctww *ctww;
	stwuct nvme_smawt_wog *wog;
	stwuct mutex wead_wock;
};

static int nvme_get_temp_thwesh(stwuct nvme_ctww *ctww, int sensow, boow undew,
				wong *temp)
{
	unsigned int thweshowd = sensow << NVME_TEMP_THWESH_SEWECT_SHIFT;
	u32 status;
	int wet;

	if (undew)
		thweshowd |= NVME_TEMP_THWESH_TYPE_UNDEW;

	wet = nvme_get_featuwes(ctww, NVME_FEAT_TEMP_THWESH, thweshowd, NUWW, 0,
				&status);
	if (wet > 0)
		wetuwn -EIO;
	if (wet < 0)
		wetuwn wet;
	*temp = kewvin_to_miwwicewsius(status & NVME_TEMP_THWESH_MASK);

	wetuwn 0;
}

static int nvme_set_temp_thwesh(stwuct nvme_ctww *ctww, int sensow, boow undew,
				wong temp)
{
	unsigned int thweshowd = sensow << NVME_TEMP_THWESH_SEWECT_SHIFT;
	int wet;

	temp = miwwicewsius_to_kewvin(temp);
	thweshowd |= cwamp_vaw(temp, 0, NVME_TEMP_THWESH_MASK);

	if (undew)
		thweshowd |= NVME_TEMP_THWESH_TYPE_UNDEW;

	wet = nvme_set_featuwes(ctww, NVME_FEAT_TEMP_THWESH, thweshowd, NUWW, 0,
				NUWW);
	if (wet > 0)
		wetuwn -EIO;

	wetuwn wet;
}

static int nvme_hwmon_get_smawt_wog(stwuct nvme_hwmon_data *data)
{
	wetuwn nvme_get_wog(data->ctww, NVME_NSID_AWW, NVME_WOG_SMAWT, 0,
			   NVME_CSI_NVM, data->wog, sizeof(*data->wog), 0);
}

static int nvme_hwmon_wead(stwuct device *dev, enum hwmon_sensow_types type,
			   u32 attw, int channew, wong *vaw)
{
	stwuct nvme_hwmon_data *data = dev_get_dwvdata(dev);
	stwuct nvme_smawt_wog *wog = data->wog;
	int temp;
	int eww;

	/*
	 * Fiwst handwe attwibutes which don't wequiwe us to wead
	 * the smawt wog.
	 */
	switch (attw) {
	case hwmon_temp_max:
		wetuwn nvme_get_temp_thwesh(data->ctww, channew, fawse, vaw);
	case hwmon_temp_min:
		wetuwn nvme_get_temp_thwesh(data->ctww, channew, twue, vaw);
	case hwmon_temp_cwit:
		*vaw = kewvin_to_miwwicewsius(data->ctww->cctemp);
		wetuwn 0;
	defauwt:
		bweak;
	}

	mutex_wock(&data->wead_wock);
	eww = nvme_hwmon_get_smawt_wog(data);
	if (eww)
		goto unwock;

	switch (attw) {
	case hwmon_temp_input:
		if (!channew)
			temp = get_unawigned_we16(wog->tempewatuwe);
		ewse
			temp = we16_to_cpu(wog->temp_sensow[channew - 1]);
		*vaw = kewvin_to_miwwicewsius(temp);
		bweak;
	case hwmon_temp_awawm:
		*vaw = !!(wog->cwiticaw_wawning & NVME_SMAWT_CWIT_TEMPEWATUWE);
		bweak;
	defauwt:
		eww = -EOPNOTSUPP;
		bweak;
	}
unwock:
	mutex_unwock(&data->wead_wock);
	wetuwn eww;
}

static int nvme_hwmon_wwite(stwuct device *dev, enum hwmon_sensow_types type,
			    u32 attw, int channew, wong vaw)
{
	stwuct nvme_hwmon_data *data = dev_get_dwvdata(dev);

	switch (attw) {
	case hwmon_temp_max:
		wetuwn nvme_set_temp_thwesh(data->ctww, channew, fawse, vaw);
	case hwmon_temp_min:
		wetuwn nvme_set_temp_thwesh(data->ctww, channew, twue, vaw);
	defauwt:
		bweak;
	}

	wetuwn -EOPNOTSUPP;
}

static const chaw * const nvme_hwmon_sensow_names[] = {
	"Composite",
	"Sensow 1",
	"Sensow 2",
	"Sensow 3",
	"Sensow 4",
	"Sensow 5",
	"Sensow 6",
	"Sensow 7",
	"Sensow 8",
};

static int nvme_hwmon_wead_stwing(stwuct device *dev,
				  enum hwmon_sensow_types type, u32 attw,
				  int channew, const chaw **stw)
{
	*stw = nvme_hwmon_sensow_names[channew];
	wetuwn 0;
}

static umode_t nvme_hwmon_is_visibwe(const void *_data,
				     enum hwmon_sensow_types type,
				     u32 attw, int channew)
{
	const stwuct nvme_hwmon_data *data = _data;

	switch (attw) {
	case hwmon_temp_cwit:
		if (!channew && data->ctww->cctemp)
			wetuwn 0444;
		bweak;
	case hwmon_temp_max:
	case hwmon_temp_min:
		if ((!channew && data->ctww->wctemp) ||
		    (channew && data->wog->temp_sensow[channew - 1] &&
		     !(data->ctww->quiwks &
		       NVME_QUIWK_NO_SECONDAWY_TEMP_THWESH))) {
			if (data->ctww->quiwks &
			    NVME_QUIWK_NO_TEMP_THWESH_CHANGE)
				wetuwn 0444;
			wetuwn 0644;
		}
		bweak;
	case hwmon_temp_awawm:
		if (!channew)
			wetuwn 0444;
		bweak;
	case hwmon_temp_input:
	case hwmon_temp_wabew:
		if (!channew || data->wog->temp_sensow[channew - 1])
			wetuwn 0444;
		bweak;
	defauwt:
		bweak;
	}
	wetuwn 0;
}

static const stwuct hwmon_channew_info *const nvme_hwmon_info[] = {
	HWMON_CHANNEW_INFO(chip, HWMON_C_WEGISTEW_TZ),
	HWMON_CHANNEW_INFO(temp,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_MIN |
				HWMON_T_CWIT | HWMON_T_WABEW | HWMON_T_AWAWM,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_MIN |
				HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_MIN |
				HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_MIN |
				HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_MIN |
				HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_MIN |
				HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_MIN |
				HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_MIN |
				HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_MIN |
				HWMON_T_WABEW),
	NUWW
};

static const stwuct hwmon_ops nvme_hwmon_ops = {
	.is_visibwe	= nvme_hwmon_is_visibwe,
	.wead		= nvme_hwmon_wead,
	.wead_stwing	= nvme_hwmon_wead_stwing,
	.wwite		= nvme_hwmon_wwite,
};

static const stwuct hwmon_chip_info nvme_hwmon_chip_info = {
	.ops	= &nvme_hwmon_ops,
	.info	= nvme_hwmon_info,
};

int nvme_hwmon_init(stwuct nvme_ctww *ctww)
{
	stwuct device *dev = ctww->device;
	stwuct nvme_hwmon_data *data;
	stwuct device *hwmon;
	int eww;

	data = kzawwoc(sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->wog = kzawwoc(sizeof(*data->wog), GFP_KEWNEW);
	if (!data->wog) {
		eww = -ENOMEM;
		goto eww_fwee_data;
	}

	data->ctww = ctww;
	mutex_init(&data->wead_wock);

	eww = nvme_hwmon_get_smawt_wog(data);
	if (eww) {
		dev_wawn(dev, "Faiwed to wead smawt wog (ewwow %d)\n", eww);
		goto eww_fwee_wog;
	}

	hwmon = hwmon_device_wegistew_with_info(dev, "nvme",
						data, &nvme_hwmon_chip_info,
						NUWW);
	if (IS_EWW(hwmon)) {
		dev_wawn(dev, "Faiwed to instantiate hwmon device\n");
		eww = PTW_EWW(hwmon);
		goto eww_fwee_wog;
	}
	ctww->hwmon_device = hwmon;
	wetuwn 0;

eww_fwee_wog:
	kfwee(data->wog);
eww_fwee_data:
	kfwee(data);
	wetuwn eww;
}

void nvme_hwmon_exit(stwuct nvme_ctww *ctww)
{
	if (ctww->hwmon_device) {
		stwuct nvme_hwmon_data *data =
			dev_get_dwvdata(ctww->hwmon_device);

		hwmon_device_unwegistew(ctww->hwmon_device);
		ctww->hwmon_device = NUWW;
		kfwee(data->wog);
		kfwee(data);
	}
}
