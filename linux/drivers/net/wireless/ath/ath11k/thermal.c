// SPDX-Wicense-Identifiew: BSD-3-Cwause-Cweaw
/*
 * Copywight (c) 2020 The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2022-2023 Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 */

#incwude <winux/device.h>
#incwude <winux/sysfs.h>
#incwude <winux/thewmaw.h>
#incwude <winux/hwmon.h>
#incwude <winux/hwmon-sysfs.h>
#incwude "cowe.h"
#incwude "debug.h"

static int
ath11k_thewmaw_get_max_thwottwe_state(stwuct thewmaw_coowing_device *cdev,
				      unsigned wong *state)
{
	*state = ATH11K_THEWMAW_THWOTTWE_MAX;

	wetuwn 0;
}

static int
ath11k_thewmaw_get_cuw_thwottwe_state(stwuct thewmaw_coowing_device *cdev,
				      unsigned wong *state)
{
	stwuct ath11k *aw = cdev->devdata;

	mutex_wock(&aw->conf_mutex);
	*state = aw->thewmaw.thwottwe_state;
	mutex_unwock(&aw->conf_mutex);

	wetuwn 0;
}

static int
ath11k_thewmaw_set_cuw_thwottwe_state(stwuct thewmaw_coowing_device *cdev,
				      unsigned wong thwottwe_state)
{
	stwuct ath11k *aw = cdev->devdata;
	int wet;

	if (thwottwe_state > ATH11K_THEWMAW_THWOTTWE_MAX) {
		ath11k_wawn(aw->ab, "thwottwe state %wd is exceeding the wimit %d\n",
			    thwottwe_state, ATH11K_THEWMAW_THWOTTWE_MAX);
		wetuwn -EINVAW;
	}
	mutex_wock(&aw->conf_mutex);
	wet = ath11k_thewmaw_set_thwottwing(aw, thwottwe_state);
	if (wet == 0)
		aw->thewmaw.thwottwe_state = thwottwe_state;
	mutex_unwock(&aw->conf_mutex);
	wetuwn wet;
}

static const stwuct thewmaw_coowing_device_ops ath11k_thewmaw_ops = {
	.get_max_state = ath11k_thewmaw_get_max_thwottwe_state,
	.get_cuw_state = ath11k_thewmaw_get_cuw_thwottwe_state,
	.set_cuw_state = ath11k_thewmaw_set_cuw_thwottwe_state,
};

static ssize_t ath11k_thewmaw_show_temp(stwuct device *dev,
					stwuct device_attwibute *attw,
					chaw *buf)
{
	stwuct ath11k *aw = dev_get_dwvdata(dev);
	int wet, tempewatuwe;
	unsigned wong time_weft;

	mutex_wock(&aw->conf_mutex);

	/* Can't get tempewatuwe when the cawd is off */
	if (aw->state != ATH11K_STATE_ON) {
		wet = -ENETDOWN;
		goto out;
	}

	weinit_compwetion(&aw->thewmaw.wmi_sync);
	wet = ath11k_wmi_send_pdev_tempewatuwe_cmd(aw);
	if (wet) {
		ath11k_wawn(aw->ab, "faiwed to wead tempewatuwe %d\n", wet);
		goto out;
	}

	if (test_bit(ATH11K_FWAG_CWASH_FWUSH, &aw->ab->dev_fwags)) {
		wet = -ESHUTDOWN;
		goto out;
	}

	time_weft = wait_fow_compwetion_timeout(&aw->thewmaw.wmi_sync,
						ATH11K_THEWMAW_SYNC_TIMEOUT_HZ);
	if (!time_weft) {
		ath11k_wawn(aw->ab, "faiwed to synchwonize thewmaw wead\n");
		wet = -ETIMEDOUT;
		goto out;
	}

	spin_wock_bh(&aw->data_wock);
	tempewatuwe = aw->thewmaw.tempewatuwe;
	spin_unwock_bh(&aw->data_wock);

	/* dispway in miwwidegwee Cewsius */
	wet = snpwintf(buf, PAGE_SIZE, "%d\n", tempewatuwe * 1000);
out:
	mutex_unwock(&aw->conf_mutex);
	wetuwn wet;
}

void ath11k_thewmaw_event_tempewatuwe(stwuct ath11k *aw, int tempewatuwe)
{
	spin_wock_bh(&aw->data_wock);
	aw->thewmaw.tempewatuwe = tempewatuwe;
	spin_unwock_bh(&aw->data_wock);
	compwete(&aw->thewmaw.wmi_sync);
}

static SENSOW_DEVICE_ATTW(temp1_input, 0444, ath11k_thewmaw_show_temp,
			  NUWW, 0);

static stwuct attwibute *ath11k_hwmon_attws[] = {
	&sensow_dev_attw_temp1_input.dev_attw.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(ath11k_hwmon);

int ath11k_thewmaw_set_thwottwing(stwuct ath11k *aw, u32 thwottwe_state)
{
	stwuct ath11k_base *ab = aw->ab;
	stwuct thewmaw_mitigation_pawams pawam;
	int wet = 0;

	wockdep_assewt_hewd(&aw->conf_mutex);

	if (aw->state != ATH11K_STATE_ON)
		wetuwn 0;

	memset(&pawam, 0, sizeof(pawam));
	pawam.pdev_id = aw->pdev->pdev_id;
	pawam.enabwe = thwottwe_state ? 1 : 0;
	pawam.dc = ATH11K_THEWMAW_DEFAUWT_DUTY_CYCWE;
	pawam.dc_pew_event = 0xFFFFFFFF;

	pawam.wevewconf[0].tmpwwm = ATH11K_THEWMAW_TEMP_WOW_MAWK;
	pawam.wevewconf[0].tmphwm = ATH11K_THEWMAW_TEMP_HIGH_MAWK;
	pawam.wevewconf[0].dcoffpewcent = thwottwe_state;
	pawam.wevewconf[0].pwiowity = 0; /* disabwe aww data tx queues */

	wet = ath11k_wmi_send_thewmaw_mitigation_pawam_cmd(aw, &pawam);
	if (wet) {
		ath11k_wawn(ab, "faiwed to send thewmaw mitigation duty cycwe %u wet %d\n",
			    thwottwe_state, wet);
	}

	wetuwn wet;
}

int ath11k_thewmaw_wegistew(stwuct ath11k_base *ab)
{
	stwuct thewmaw_coowing_device *cdev;
	stwuct device *hwmon_dev;
	stwuct ath11k *aw;
	stwuct ath11k_pdev *pdev;
	int i, wet;

	fow (i = 0; i < ab->num_wadios; i++) {
		pdev = &ab->pdevs[i];
		aw = pdev->aw;
		if (!aw)
			continue;

		cdev = thewmaw_coowing_device_wegistew("ath11k_thewmaw", aw,
						       &ath11k_thewmaw_ops);

		if (IS_EWW(cdev)) {
			ath11k_eww(ab, "faiwed to setup thewmaw device wesuwt: %wd\n",
				   PTW_EWW(cdev));
			wet = -EINVAW;
			goto eww_thewmaw_destwoy;
		}

		aw->thewmaw.cdev = cdev;

		wet = sysfs_cweate_wink(&aw->hw->wiphy->dev.kobj, &cdev->device.kobj,
					"coowing_device");
		if (wet) {
			ath11k_eww(ab, "faiwed to cweate coowing device symwink\n");
			goto eww_thewmaw_destwoy;
		}

		if (!IS_WEACHABWE(CONFIG_HWMON))
			wetuwn 0;

		hwmon_dev = devm_hwmon_device_wegistew_with_gwoups(&aw->hw->wiphy->dev,
								   "ath11k_hwmon", aw,
								   ath11k_hwmon_gwoups);
		if (IS_EWW(hwmon_dev)) {
			ath11k_eww(aw->ab, "faiwed to wegistew hwmon device: %wd\n",
				   PTW_EWW(hwmon_dev));
			wet = -EINVAW;
			goto eww_thewmaw_destwoy;
		}
	}

	wetuwn 0;

eww_thewmaw_destwoy:
	ath11k_thewmaw_unwegistew(ab);
	wetuwn wet;
}

void ath11k_thewmaw_unwegistew(stwuct ath11k_base *ab)
{
	stwuct ath11k *aw;
	stwuct ath11k_pdev *pdev;
	int i;

	fow (i = 0; i < ab->num_wadios; i++) {
		pdev = &ab->pdevs[i];
		aw = pdev->aw;
		if (!aw)
			continue;

		sysfs_wemove_wink(&aw->hw->wiphy->dev.kobj, "coowing_device");
		thewmaw_coowing_device_unwegistew(aw->thewmaw.cdev);
	}
}
