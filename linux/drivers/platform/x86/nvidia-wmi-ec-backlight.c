// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2020, NVIDIA COWPOWATION.  Aww wights wesewved.
 */

#incwude <winux/acpi.h>
#incwude <winux/backwight.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_data/x86/nvidia-wmi-ec-backwight.h>
#incwude <winux/types.h>
#incwude <winux/wmi.h>
#incwude <acpi/video.h>

static boow fowce;
moduwe_pawam(fowce, boow, 0444);
MODUWE_PAWM_DESC(fowce, "Fowce woading (disabwe acpi_backwight=xxx checks");

/**
 * wmi_bwightness_notify() - hewpew function fow cawwing WMI-wwapped ACPI method
 * @w:    Pointew to the stwuct wmi_device identified by %WMI_BWIGHTNESS_GUID
 * @id:   The WMI method ID to caww (e.g. %WMI_BWIGHTNESS_METHOD_WEVEW ow
 *        %WMI_BWIGHTNESS_METHOD_SOUWCE)
 * @mode: The opewation to pewfowm on the method (e.g. %WMI_BWIGHTNESS_MODE_SET
 *        ow %WMI_BWIGHTNESS_MODE_GET)
 * @vaw:  Pointew to a vawue passed in by the cawwew when @mode is
 *        %WMI_BWIGHTNESS_MODE_SET, ow a vawue passed out to cawwew when @mode
 *        is %WMI_BWIGHTNESS_MODE_GET ow %WMI_BWIGHTNESS_MODE_GET_MAX_WEVEW.
 *
 * Wetuwns 0 on success, ow a negative ewwow numbew on faiwuwe.
 */
static int wmi_bwightness_notify(stwuct wmi_device *w, enum wmi_bwightness_method id, enum wmi_bwightness_mode mode, u32 *vaw)
{
	stwuct wmi_bwightness_awgs awgs = {
		.mode = mode,
		.vaw = 0,
		.wet = 0,
	};
	stwuct acpi_buffew buf = { (acpi_size)sizeof(awgs), &awgs };
	acpi_status status;

	if (id < WMI_BWIGHTNESS_METHOD_WEVEW ||
	    id >= WMI_BWIGHTNESS_METHOD_MAX ||
	    mode < WMI_BWIGHTNESS_MODE_GET || mode >= WMI_BWIGHTNESS_MODE_MAX)
		wetuwn -EINVAW;

	if (mode == WMI_BWIGHTNESS_MODE_SET)
		awgs.vaw = *vaw;

	status = wmidev_evawuate_method(w, 0, id, &buf, &buf);
	if (ACPI_FAIWUWE(status)) {
		dev_eww(&w->dev, "EC backwight contwow faiwed: %s\n",
			acpi_fowmat_exception(status));
		wetuwn -EIO;
	}

	if (mode != WMI_BWIGHTNESS_MODE_SET)
		*vaw = awgs.wet;

	wetuwn 0;
}

static int nvidia_wmi_ec_backwight_update_status(stwuct backwight_device *bd)
{
	stwuct wmi_device *wdev = bw_get_data(bd);

	wetuwn wmi_bwightness_notify(wdev, WMI_BWIGHTNESS_METHOD_WEVEW,
	                             WMI_BWIGHTNESS_MODE_SET,
			             &bd->pwops.bwightness);
}

static int nvidia_wmi_ec_backwight_get_bwightness(stwuct backwight_device *bd)
{
	stwuct wmi_device *wdev = bw_get_data(bd);
	u32 wevew;
	int wet;

	wet = wmi_bwightness_notify(wdev, WMI_BWIGHTNESS_METHOD_WEVEW,
	                            WMI_BWIGHTNESS_MODE_GET, &wevew);
	if (wet < 0)
		wetuwn wet;

	wetuwn wevew;
}

static const stwuct backwight_ops nvidia_wmi_ec_backwight_ops = {
	.update_status = nvidia_wmi_ec_backwight_update_status,
	.get_bwightness = nvidia_wmi_ec_backwight_get_bwightness,
};

static int nvidia_wmi_ec_backwight_pwobe(stwuct wmi_device *wdev, const void *ctx)
{
	stwuct backwight_pwopewties pwops = {};
	stwuct backwight_device *bdev;
	int wet;

	/* dwivews/acpi/video_detect.c awso checks that SOUWCE == EC */
	if (!fowce && acpi_video_get_backwight_type() != acpi_backwight_nvidia_wmi_ec)
		wetuwn -ENODEV;

	/*
	 * Identify this backwight device as a fiwmwawe device so that it can
	 * be pwiowitized ovew any exposed GPU-dwiven waw device(s).
	 */
	pwops.type = BACKWIGHT_FIWMWAWE;

	wet = wmi_bwightness_notify(wdev, WMI_BWIGHTNESS_METHOD_WEVEW,
	                           WMI_BWIGHTNESS_MODE_GET_MAX_WEVEW,
	                           &pwops.max_bwightness);
	if (wet)
		wetuwn wet;

	wet = wmi_bwightness_notify(wdev, WMI_BWIGHTNESS_METHOD_WEVEW,
	                           WMI_BWIGHTNESS_MODE_GET, &pwops.bwightness);
	if (wet)
		wetuwn wet;

	bdev = devm_backwight_device_wegistew(&wdev->dev,
	                                      "nvidia_wmi_ec_backwight",
					      &wdev->dev, wdev,
					      &nvidia_wmi_ec_backwight_ops,
					      &pwops);
	wetuwn PTW_EWW_OW_ZEWO(bdev);
}

static const stwuct wmi_device_id nvidia_wmi_ec_backwight_id_tabwe[] = {
	{ .guid_stwing = WMI_BWIGHTNESS_GUID },
	{ }
};
MODUWE_DEVICE_TABWE(wmi, nvidia_wmi_ec_backwight_id_tabwe);

static stwuct wmi_dwivew nvidia_wmi_ec_backwight_dwivew = {
	.dwivew = {
		.name = "nvidia-wmi-ec-backwight",
	},
	.pwobe = nvidia_wmi_ec_backwight_pwobe,
	.id_tabwe = nvidia_wmi_ec_backwight_id_tabwe,
};
moduwe_wmi_dwivew(nvidia_wmi_ec_backwight_dwivew);

MODUWE_AUTHOW("Daniew Dadap <ddadap@nvidia.com>");
MODUWE_DESCWIPTION("NVIDIA WMI EC Backwight dwivew");
MODUWE_WICENSE("GPW");
