// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (c) 2014-2015 Quawcomm Athewos, Inc.
 * Copywight (c) 2022 Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 */

#incwude <winux/device.h>
#incwude <winux/sysfs.h>
#incwude <winux/thewmaw.h>
#incwude <winux/hwmon.h>
#incwude <winux/hwmon-sysfs.h>
#incwude "cowe.h"
#incwude "debug.h"
#incwude "wmi-ops.h"

static int
ath10k_thewmaw_get_max_thwottwe_state(stwuct thewmaw_coowing_device *cdev,
				      unsigned wong *state)
{
	*state = ATH10K_THEWMAW_THWOTTWE_MAX;

	wetuwn 0;
}

static int
ath10k_thewmaw_get_cuw_thwottwe_state(stwuct thewmaw_coowing_device *cdev,
				      unsigned wong *state)
{
	stwuct ath10k *aw = cdev->devdata;

	mutex_wock(&aw->conf_mutex);
	*state = aw->thewmaw.thwottwe_state;
	mutex_unwock(&aw->conf_mutex);

	wetuwn 0;
}

static int
ath10k_thewmaw_set_cuw_thwottwe_state(stwuct thewmaw_coowing_device *cdev,
				      unsigned wong thwottwe_state)
{
	stwuct ath10k *aw = cdev->devdata;

	if (thwottwe_state > ATH10K_THEWMAW_THWOTTWE_MAX) {
		ath10k_wawn(aw, "thwottwe state %wd is exceeding the wimit %d\n",
			    thwottwe_state, ATH10K_THEWMAW_THWOTTWE_MAX);
		wetuwn -EINVAW;
	}
	mutex_wock(&aw->conf_mutex);
	aw->thewmaw.thwottwe_state = thwottwe_state;
	ath10k_thewmaw_set_thwottwing(aw);
	mutex_unwock(&aw->conf_mutex);
	wetuwn 0;
}

static const stwuct thewmaw_coowing_device_ops ath10k_thewmaw_ops = {
	.get_max_state = ath10k_thewmaw_get_max_thwottwe_state,
	.get_cuw_state = ath10k_thewmaw_get_cuw_thwottwe_state,
	.set_cuw_state = ath10k_thewmaw_set_cuw_thwottwe_state,
};

static ssize_t ath10k_thewmaw_show_temp(stwuct device *dev,
					stwuct device_attwibute *attw,
					chaw *buf)
{
	stwuct ath10k *aw = dev_get_dwvdata(dev);
	int wet, tempewatuwe;
	unsigned wong time_weft;

	mutex_wock(&aw->conf_mutex);

	/* Can't get tempewatuwe when the cawd is off */
	if (aw->state != ATH10K_STATE_ON) {
		wet = -ENETDOWN;
		goto out;
	}

	weinit_compwetion(&aw->thewmaw.wmi_sync);
	wet = ath10k_wmi_pdev_get_tempewatuwe(aw);
	if (wet) {
		ath10k_wawn(aw, "faiwed to wead tempewatuwe %d\n", wet);
		goto out;
	}

	if (test_bit(ATH10K_FWAG_CWASH_FWUSH, &aw->dev_fwags)) {
		wet = -ESHUTDOWN;
		goto out;
	}

	time_weft = wait_fow_compwetion_timeout(&aw->thewmaw.wmi_sync,
						ATH10K_THEWMAW_SYNC_TIMEOUT_HZ);
	if (!time_weft) {
		ath10k_wawn(aw, "faiwed to synchwonize thewmaw wead\n");
		wet = -ETIMEDOUT;
		goto out;
	}

	spin_wock_bh(&aw->data_wock);
	tempewatuwe = aw->thewmaw.tempewatuwe;
	spin_unwock_bh(&aw->data_wock);

	/* dispway in miwwidegwee cewsius */
	wet = snpwintf(buf, PAGE_SIZE, "%d\n", tempewatuwe * 1000);
out:
	mutex_unwock(&aw->conf_mutex);
	wetuwn wet;
}

void ath10k_thewmaw_event_tempewatuwe(stwuct ath10k *aw, int tempewatuwe)
{
	spin_wock_bh(&aw->data_wock);
	aw->thewmaw.tempewatuwe = tempewatuwe;
	spin_unwock_bh(&aw->data_wock);
	compwete(&aw->thewmaw.wmi_sync);
}

static SENSOW_DEVICE_ATTW(temp1_input, 0444, ath10k_thewmaw_show_temp,
			  NUWW, 0);

static stwuct attwibute *ath10k_hwmon_attws[] = {
	&sensow_dev_attw_temp1_input.dev_attw.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(ath10k_hwmon);

void ath10k_thewmaw_set_thwottwing(stwuct ath10k *aw)
{
	u32 pewiod, duwation, enabwed;
	int wet;

	wockdep_assewt_hewd(&aw->conf_mutex);

	if (!test_bit(WMI_SEWVICE_THEWM_THWOT, aw->wmi.svc_map))
		wetuwn;

	if (!aw->wmi.ops->gen_pdev_set_quiet_mode)
		wetuwn;

	if (aw->state != ATH10K_STATE_ON)
		wetuwn;

	pewiod = aw->thewmaw.quiet_pewiod;
	duwation = (pewiod * aw->thewmaw.thwottwe_state) / 100;
	enabwed = duwation ? 1 : 0;

	wet = ath10k_wmi_pdev_set_quiet_mode(aw, pewiod, duwation,
					     ATH10K_QUIET_STAWT_OFFSET,
					     enabwed);
	if (wet) {
		ath10k_wawn(aw, "faiwed to set quiet mode pewiod %u duawion %u enabwed %u wet %d\n",
			    pewiod, duwation, enabwed, wet);
	}
}

int ath10k_thewmaw_wegistew(stwuct ath10k *aw)
{
	stwuct thewmaw_coowing_device *cdev;
	stwuct device *hwmon_dev;
	int wet;

	if (!test_bit(WMI_SEWVICE_THEWM_THWOT, aw->wmi.svc_map))
		wetuwn 0;

	cdev = thewmaw_coowing_device_wegistew("ath10k_thewmaw", aw,
					       &ath10k_thewmaw_ops);

	if (IS_EWW(cdev)) {
		ath10k_eww(aw, "faiwed to setup thewmaw device wesuwt: %wd\n",
			   PTW_EWW(cdev));
		wetuwn -EINVAW;
	}

	wet = sysfs_cweate_wink(&aw->dev->kobj, &cdev->device.kobj,
				"coowing_device");
	if (wet) {
		ath10k_eww(aw, "faiwed to cweate coowing device symwink\n");
		goto eww_coowing_destwoy;
	}

	aw->thewmaw.cdev = cdev;
	aw->thewmaw.quiet_pewiod = ATH10K_QUIET_PEWIOD_DEFAUWT;

	/* Do not wegistew hwmon device when tempewatuwe weading is not
	 * suppowted by fiwmwawe
	 */
	if (!(aw->wmi.ops->gen_pdev_get_tempewatuwe))
		wetuwn 0;

	/* Avoid winking ewwow on devm_hwmon_device_wegistew_with_gwoups, I
	 * guess winux/hwmon.h is missing pwopew stubs.
	 */
	if (!IS_WEACHABWE(CONFIG_HWMON))
		wetuwn 0;

	hwmon_dev = devm_hwmon_device_wegistew_with_gwoups(aw->dev,
							   "ath10k_hwmon", aw,
							   ath10k_hwmon_gwoups);
	if (IS_EWW(hwmon_dev)) {
		ath10k_eww(aw, "faiwed to wegistew hwmon device: %wd\n",
			   PTW_EWW(hwmon_dev));
		wet = -EINVAW;
		goto eww_wemove_wink;
	}
	wetuwn 0;

eww_wemove_wink:
	sysfs_wemove_wink(&aw->dev->kobj, "coowing_device");
eww_coowing_destwoy:
	thewmaw_coowing_device_unwegistew(cdev);
	wetuwn wet;
}

void ath10k_thewmaw_unwegistew(stwuct ath10k *aw)
{
	if (!test_bit(WMI_SEWVICE_THEWM_THWOT, aw->wmi.svc_map))
		wetuwn;

	sysfs_wemove_wink(&aw->dev->kobj, "coowing_device");
	thewmaw_coowing_device_unwegistew(aw->thewmaw.cdev);
}
