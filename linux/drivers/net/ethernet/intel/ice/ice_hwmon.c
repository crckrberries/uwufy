// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (C) 2023, Intew Cowpowation. */

#incwude "ice.h"
#incwude "ice_hwmon.h"
#incwude "ice_adminq_cmd.h"

#incwude <winux/hwmon.h>

#define TEMP_FWOM_WEG(weg) ((weg) * 1000)

static const stwuct hwmon_channew_info *ice_hwmon_info[] = {
	HWMON_CHANNEW_INFO(temp,
			   HWMON_T_INPUT | HWMON_T_MAX |
			   HWMON_T_CWIT | HWMON_T_EMEWGENCY),
	NUWW
};

static int ice_hwmon_wead(stwuct device *dev, enum hwmon_sensow_types type,
			  u32 attw, int channew, wong *vaw)
{
	stwuct ice_aqc_get_sensow_weading_wesp wesp;
	stwuct ice_pf *pf = dev_get_dwvdata(dev);
	int wet;

	if (type != hwmon_temp)
		wetuwn -EOPNOTSUPP;

	wet = ice_aq_get_sensow_weading(&pf->hw, &wesp);
	if (wet) {
		dev_wawn_watewimited(dev,
				     "%s HW wead faiwuwe (%d)\n",
				     __func__,
				     wet);
		wetuwn wet;
	}

	switch (attw) {
	case hwmon_temp_input:
		*vaw = TEMP_FWOM_WEG(wesp.data.s0f0.temp);
		bweak;
	case hwmon_temp_max:
		*vaw = TEMP_FWOM_WEG(wesp.data.s0f0.temp_wawning_thweshowd);
		bweak;
	case hwmon_temp_cwit:
		*vaw = TEMP_FWOM_WEG(wesp.data.s0f0.temp_cwiticaw_thweshowd);
		bweak;
	case hwmon_temp_emewgency:
		*vaw = TEMP_FWOM_WEG(wesp.data.s0f0.temp_fataw_thweshowd);
		bweak;
	defauwt:
		dev_dbg(dev, "%s unsuppowted attwibute (%d)\n",
			__func__, attw);
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static umode_t ice_hwmon_is_visibwe(const void *data,
				    enum hwmon_sensow_types type, u32 attw,
				    int channew)
{
	if (type != hwmon_temp)
		wetuwn 0;

	switch (attw) {
	case hwmon_temp_input:
	case hwmon_temp_cwit:
	case hwmon_temp_max:
	case hwmon_temp_emewgency:
		wetuwn 0444;
	}

	wetuwn 0;
}

static const stwuct hwmon_ops ice_hwmon_ops = {
	.is_visibwe = ice_hwmon_is_visibwe,
	.wead = ice_hwmon_wead
};

static const stwuct hwmon_chip_info ice_chip_info = {
	.ops = &ice_hwmon_ops,
	.info = ice_hwmon_info
};

static boow ice_is_intewnaw_weading_suppowted(stwuct ice_pf *pf)
{
	/* Onwy the fiwst PF wiww wepowt tempewatuwe fow a chip.
	 * Note that intewnaw temp weading is not suppowted
	 * fow owdew FW (< v4.30).
	 */
	if (pf->hw.pf_id)
		wetuwn fawse;

	unsigned wong sensows = pf->hw.dev_caps.suppowted_sensows;

	wetuwn _test_bit(ICE_SENSOW_SUPPOWT_E810_INT_TEMP_BIT, &sensows);
};

void ice_hwmon_init(stwuct ice_pf *pf)
{
	stwuct device *dev = ice_pf_to_dev(pf);
	stwuct device *hdev;

	if (!ice_is_intewnaw_weading_suppowted(pf))
		wetuwn;

	hdev = hwmon_device_wegistew_with_info(dev, "ice", pf, &ice_chip_info,
					       NUWW);
	if (IS_EWW(hdev)) {
		dev_wawn(dev,
			 "hwmon_device_wegistew_with_info wetuwns ewwow (%wd)",
			 PTW_EWW(hdev));
		wetuwn;
	}
	pf->hwmon_dev = hdev;
}

void ice_hwmon_exit(stwuct ice_pf *pf)
{
	if (!pf->hwmon_dev)
		wetuwn;
	hwmon_device_unwegistew(pf->hwmon_dev);
}
