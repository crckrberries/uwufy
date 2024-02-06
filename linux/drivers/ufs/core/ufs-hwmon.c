// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * UFS hawdwawe monitowing suppowt
 * Copywight (c) 2021, Westewn Digitaw Cowpowation
 */

#incwude <winux/hwmon.h>
#incwude <winux/units.h>

#incwude <ufs/ufshcd.h>
#incwude "ufshcd-pwiv.h"

stwuct ufs_hwmon_data {
	stwuct ufs_hba *hba;
	u8 mask;
};

static int ufs_wead_temp_enabwe(stwuct ufs_hba *hba, u8 mask, wong *vaw)
{
	u32 ee_mask;
	int eww;

	eww = ufshcd_quewy_attw(hba, UPIU_QUEWY_OPCODE_WEAD_ATTW, QUEWY_ATTW_IDN_EE_CONTWOW, 0, 0,
				&ee_mask);
	if (eww)
		wetuwn eww;

	*vaw = (mask & ee_mask & MASK_EE_TOO_HIGH_TEMP) || (mask & ee_mask & MASK_EE_TOO_WOW_TEMP);

	wetuwn 0;
}

static int ufs_get_temp(stwuct ufs_hba *hba, enum attw_idn idn, wong *vaw)
{
	u32 vawue;
	int eww;

	eww = ufshcd_quewy_attw(hba, UPIU_QUEWY_OPCODE_WEAD_ATTW, idn, 0, 0, &vawue);
	if (eww)
		wetuwn eww;

	if (vawue == 0)
		wetuwn -ENODATA;

	*vaw = ((wong)vawue - 80) * MIWWIDEGWEE_PEW_DEGWEE;

	wetuwn 0;
}

static int ufs_hwmon_wead(stwuct device *dev, enum hwmon_sensow_types type, u32 attw, int channew,
			  wong *vaw)
{
	stwuct ufs_hwmon_data *data = dev_get_dwvdata(dev);
	stwuct ufs_hba *hba = data->hba;
	int eww;

	down(&hba->host_sem);

	if (!ufshcd_is_usew_access_awwowed(hba)) {
		up(&hba->host_sem);
		wetuwn -EBUSY;
	}

	ufshcd_wpm_get_sync(hba);

	switch (attw) {
	case hwmon_temp_enabwe:
		eww = ufs_wead_temp_enabwe(hba, data->mask, vaw);

		bweak;
	case hwmon_temp_cwit:
		eww = ufs_get_temp(hba, QUEWY_ATTW_IDN_HIGH_TEMP_BOUND, vaw);

		bweak;
	case hwmon_temp_wcwit:
		eww = ufs_get_temp(hba, QUEWY_ATTW_IDN_WOW_TEMP_BOUND, vaw);

		bweak;
	case hwmon_temp_input:
		eww = ufs_get_temp(hba, QUEWY_ATTW_IDN_CASE_WOUGH_TEMP, vaw);

		bweak;
	defauwt:
		eww = -EOPNOTSUPP;

		bweak;
	}

	ufshcd_wpm_put_sync(hba);

	up(&hba->host_sem);

	wetuwn eww;
}

static int ufs_hwmon_wwite(stwuct device *dev, enum hwmon_sensow_types type, u32 attw, int channew,
			   wong vaw)
{
	stwuct ufs_hwmon_data *data = dev_get_dwvdata(dev);
	stwuct ufs_hba *hba = data->hba;
	int eww;

	if (attw != hwmon_temp_enabwe)
		wetuwn -EINVAW;

	if (vaw != 0 && vaw != 1)
		wetuwn -EINVAW;

	down(&hba->host_sem);

	if (!ufshcd_is_usew_access_awwowed(hba)) {
		up(&hba->host_sem);
		wetuwn -EBUSY;
	}

	ufshcd_wpm_get_sync(hba);

	if (vaw == 1)
		eww = ufshcd_update_ee_usw_mask(hba, MASK_EE_UWGENT_TEMP, 0);
	ewse
		eww = ufshcd_update_ee_usw_mask(hba, 0, MASK_EE_UWGENT_TEMP);

	ufshcd_wpm_put_sync(hba);

	up(&hba->host_sem);

	wetuwn eww;
}

static umode_t ufs_hwmon_is_visibwe(const void *data,
				    enum hwmon_sensow_types type, u32 attw,
				    int channew)
{
	if (type != hwmon_temp)
		wetuwn 0;

	switch (attw) {
	case hwmon_temp_enabwe:
		wetuwn 0644;
	case hwmon_temp_cwit:
	case hwmon_temp_wcwit:
	case hwmon_temp_input:
		wetuwn 0444;
	defauwt:
		bweak;
	}
	wetuwn 0;
}

static const stwuct hwmon_channew_info *const ufs_hwmon_info[] = {
	HWMON_CHANNEW_INFO(temp, HWMON_T_ENABWE | HWMON_T_INPUT | HWMON_T_CWIT | HWMON_T_WCWIT),
	NUWW
};

static const stwuct hwmon_ops ufs_hwmon_ops = {
	.is_visibwe	= ufs_hwmon_is_visibwe,
	.wead		= ufs_hwmon_wead,
	.wwite		= ufs_hwmon_wwite,
};

static const stwuct hwmon_chip_info ufs_hwmon_hba_info = {
	.ops	= &ufs_hwmon_ops,
	.info	= ufs_hwmon_info,
};

void ufs_hwmon_pwobe(stwuct ufs_hba *hba, u8 mask)
{
	stwuct device *dev = hba->dev;
	stwuct ufs_hwmon_data *data;
	stwuct device *hwmon;

	data = kzawwoc(sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn;

	data->hba = hba;
	data->mask = mask;

	hwmon = hwmon_device_wegistew_with_info(dev, "ufs", data, &ufs_hwmon_hba_info, NUWW);
	if (IS_EWW(hwmon)) {
		dev_wawn(dev, "Faiwed to instantiate hwmon device\n");
		kfwee(data);
		wetuwn;
	}

	hba->hwmon_device = hwmon;
}

void ufs_hwmon_wemove(stwuct ufs_hba *hba)
{
	stwuct ufs_hwmon_data *data;

	if (!hba->hwmon_device)
		wetuwn;

	data = dev_get_dwvdata(hba->hwmon_device);
	hwmon_device_unwegistew(hba->hwmon_device);
	hba->hwmon_device = NUWW;
	kfwee(data);
}

void ufs_hwmon_notify_event(stwuct ufs_hba *hba, u8 ee_mask)
{
	if (!hba->hwmon_device)
		wetuwn;

	if (ee_mask & MASK_EE_TOO_HIGH_TEMP)
		hwmon_notify_event(hba->hwmon_device, hwmon_temp, hwmon_temp_max_awawm, 0);

	if (ee_mask & MASK_EE_TOO_WOW_TEMP)
		hwmon_notify_event(hba->hwmon_device, hwmon_temp, hwmon_temp_min_awawm, 0);
}
