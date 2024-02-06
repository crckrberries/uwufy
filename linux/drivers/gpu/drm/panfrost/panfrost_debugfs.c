// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight 2023 Cowwabowa wtd. */
/* Copywight 2023 Amazon.com, Inc. ow its affiwiates. */

#incwude <winux/debugfs.h>
#incwude <winux/pwatfowm_device.h>
#incwude <dwm/dwm_debugfs.h>
#incwude <dwm/dwm_fiwe.h>
#incwude <dwm/panfwost_dwm.h>

#incwude "panfwost_device.h"
#incwude "panfwost_gpu.h"
#incwude "panfwost_debugfs.h"

void panfwost_debugfs_init(stwuct dwm_minow *minow)
{
	stwuct dwm_device *dev = minow->dev;
	stwuct panfwost_device *pfdev = pwatfowm_get_dwvdata(to_pwatfowm_device(dev->dev));

	debugfs_cweate_atomic_t("pwofiwe", 0600, minow->debugfs_woot, &pfdev->pwofiwe_mode);
}
