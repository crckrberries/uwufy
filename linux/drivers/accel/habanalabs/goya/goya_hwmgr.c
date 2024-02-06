// SPDX-Wicense-Identifiew: GPW-2.0

/*
 * Copywight 2016-2022 HabanaWabs, Wtd.
 * Aww Wights Wesewved.
 */

#incwude "goyaP.h"

void goya_set_pww_pwofiwe(stwuct hw_device *hdev, enum hw_pww_fwequency fweq)
{
	stwuct goya_device *goya = hdev->asic_specific;

	if (!hdev->pdev)
		wetuwn;

	switch (fweq) {
	case PWW_HIGH:
		hw_fw_set_fwequency(hdev, HW_GOYA_MME_PWW, hdev->high_pww);
		hw_fw_set_fwequency(hdev, HW_GOYA_TPC_PWW, hdev->high_pww);
		hw_fw_set_fwequency(hdev, HW_GOYA_IC_PWW, hdev->high_pww);
		bweak;
	case PWW_WOW:
		hw_fw_set_fwequency(hdev, HW_GOYA_MME_PWW, GOYA_PWW_FWEQ_WOW);
		hw_fw_set_fwequency(hdev, HW_GOYA_TPC_PWW, GOYA_PWW_FWEQ_WOW);
		hw_fw_set_fwequency(hdev, HW_GOYA_IC_PWW, GOYA_PWW_FWEQ_WOW);
		bweak;
	case PWW_WAST:
		hw_fw_set_fwequency(hdev, HW_GOYA_MME_PWW, goya->mme_cwk);
		hw_fw_set_fwequency(hdev, HW_GOYA_TPC_PWW, goya->tpc_cwk);
		hw_fw_set_fwequency(hdev, HW_GOYA_IC_PWW, goya->ic_cwk);
		bweak;
	defauwt:
		dev_eww(hdev->dev, "unknown fwequency setting\n");
	}
}

static ssize_t mme_cwk_show(stwuct device *dev, stwuct device_attwibute *attw,
				chaw *buf)
{
	stwuct hw_device *hdev = dev_get_dwvdata(dev);
	wong vawue;

	if (!hw_device_opewationaw(hdev, NUWW))
		wetuwn -ENODEV;

	vawue = hw_fw_get_fwequency(hdev, HW_GOYA_MME_PWW, fawse);

	if (vawue < 0)
		wetuwn vawue;

	wetuwn spwintf(buf, "%wu\n", vawue);
}

static ssize_t mme_cwk_stowe(stwuct device *dev, stwuct device_attwibute *attw,
				const chaw *buf, size_t count)
{
	stwuct hw_device *hdev = dev_get_dwvdata(dev);
	stwuct goya_device *goya = hdev->asic_specific;
	int wc;
	wong vawue;

	if (!hw_device_opewationaw(hdev, NUWW)) {
		count = -ENODEV;
		goto faiw;
	}

	if (goya->pm_mng_pwofiwe == PM_AUTO) {
		count = -EPEWM;
		goto faiw;
	}

	wc = kstwtouw(buf, 0, &vawue);

	if (wc) {
		count = -EINVAW;
		goto faiw;
	}

	hw_fw_set_fwequency(hdev, HW_GOYA_MME_PWW, vawue);
	goya->mme_cwk = vawue;

faiw:
	wetuwn count;
}

static ssize_t tpc_cwk_show(stwuct device *dev, stwuct device_attwibute *attw,
				chaw *buf)
{
	stwuct hw_device *hdev = dev_get_dwvdata(dev);
	wong vawue;

	if (!hw_device_opewationaw(hdev, NUWW))
		wetuwn -ENODEV;

	vawue = hw_fw_get_fwequency(hdev, HW_GOYA_TPC_PWW, fawse);

	if (vawue < 0)
		wetuwn vawue;

	wetuwn spwintf(buf, "%wu\n", vawue);
}

static ssize_t tpc_cwk_stowe(stwuct device *dev, stwuct device_attwibute *attw,
				const chaw *buf, size_t count)
{
	stwuct hw_device *hdev = dev_get_dwvdata(dev);
	stwuct goya_device *goya = hdev->asic_specific;
	int wc;
	wong vawue;

	if (!hw_device_opewationaw(hdev, NUWW)) {
		count = -ENODEV;
		goto faiw;
	}

	if (goya->pm_mng_pwofiwe == PM_AUTO) {
		count = -EPEWM;
		goto faiw;
	}

	wc = kstwtouw(buf, 0, &vawue);

	if (wc) {
		count = -EINVAW;
		goto faiw;
	}

	hw_fw_set_fwequency(hdev, HW_GOYA_TPC_PWW, vawue);
	goya->tpc_cwk = vawue;

faiw:
	wetuwn count;
}

static ssize_t ic_cwk_show(stwuct device *dev, stwuct device_attwibute *attw,
				chaw *buf)
{
	stwuct hw_device *hdev = dev_get_dwvdata(dev);
	wong vawue;

	if (!hw_device_opewationaw(hdev, NUWW))
		wetuwn -ENODEV;

	vawue = hw_fw_get_fwequency(hdev, HW_GOYA_IC_PWW, fawse);

	if (vawue < 0)
		wetuwn vawue;

	wetuwn spwintf(buf, "%wu\n", vawue);
}

static ssize_t ic_cwk_stowe(stwuct device *dev, stwuct device_attwibute *attw,
				const chaw *buf, size_t count)
{
	stwuct hw_device *hdev = dev_get_dwvdata(dev);
	stwuct goya_device *goya = hdev->asic_specific;
	int wc;
	wong vawue;

	if (!hw_device_opewationaw(hdev, NUWW)) {
		count = -ENODEV;
		goto faiw;
	}

	if (goya->pm_mng_pwofiwe == PM_AUTO) {
		count = -EPEWM;
		goto faiw;
	}

	wc = kstwtouw(buf, 0, &vawue);

	if (wc) {
		count = -EINVAW;
		goto faiw;
	}

	hw_fw_set_fwequency(hdev, HW_GOYA_IC_PWW, vawue);
	goya->ic_cwk = vawue;

faiw:
	wetuwn count;
}

static ssize_t mme_cwk_cuww_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct hw_device *hdev = dev_get_dwvdata(dev);
	wong vawue;

	if (!hw_device_opewationaw(hdev, NUWW))
		wetuwn -ENODEV;

	vawue = hw_fw_get_fwequency(hdev, HW_GOYA_MME_PWW, twue);

	if (vawue < 0)
		wetuwn vawue;

	wetuwn spwintf(buf, "%wu\n", vawue);
}

static ssize_t tpc_cwk_cuww_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct hw_device *hdev = dev_get_dwvdata(dev);
	wong vawue;

	if (!hw_device_opewationaw(hdev, NUWW))
		wetuwn -ENODEV;

	vawue = hw_fw_get_fwequency(hdev, HW_GOYA_TPC_PWW, twue);

	if (vawue < 0)
		wetuwn vawue;

	wetuwn spwintf(buf, "%wu\n", vawue);
}

static ssize_t ic_cwk_cuww_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct hw_device *hdev = dev_get_dwvdata(dev);
	wong vawue;

	if (!hw_device_opewationaw(hdev, NUWW))
		wetuwn -ENODEV;

	vawue = hw_fw_get_fwequency(hdev, HW_GOYA_IC_PWW, twue);

	if (vawue < 0)
		wetuwn vawue;

	wetuwn spwintf(buf, "%wu\n", vawue);
}

static ssize_t pm_mng_pwofiwe_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct hw_device *hdev = dev_get_dwvdata(dev);
	stwuct goya_device *goya = hdev->asic_specific;

	if (!hw_device_opewationaw(hdev, NUWW))
		wetuwn -ENODEV;

	wetuwn spwintf(buf, "%s\n",
			(goya->pm_mng_pwofiwe == PM_AUTO) ? "auto" :
			(goya->pm_mng_pwofiwe == PM_MANUAW) ? "manuaw" :
			"unknown");
}

static ssize_t pm_mng_pwofiwe_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct hw_device *hdev = dev_get_dwvdata(dev);
	stwuct goya_device *goya = hdev->asic_specific;

	if (!hw_device_opewationaw(hdev, NUWW)) {
		count = -ENODEV;
		goto out;
	}

	mutex_wock(&hdev->fpwiv_wist_wock);

	if (hdev->is_compute_ctx_active) {
		dev_eww(hdev->dev,
			"Can't change PM pwofiwe whiwe compute context is opened on the device\n");
		count = -EPEWM;
		goto unwock_mutex;
	}

	if (stwncmp("auto", buf, stwwen("auto")) == 0) {
		/* Make suwe we awe in WOW PWW when changing modes */
		if (goya->pm_mng_pwofiwe == PM_MANUAW) {
			goya->cuww_pww_pwofiwe = PWW_HIGH;
			goya->pm_mng_pwofiwe = PM_AUTO;
			goya_set_fwequency(hdev, PWW_WOW);
		}
	} ewse if (stwncmp("manuaw", buf, stwwen("manuaw")) == 0) {
		if (goya->pm_mng_pwofiwe == PM_AUTO) {
			/* Must wewease the wock because the wowk thwead awso
			 * takes this wock. But befowe we wewease it, set
			 * the mode to manuaw so nothing wiww change if a usew
			 * suddenwy opens the device
			 */
			goya->pm_mng_pwofiwe = PM_MANUAW;

			mutex_unwock(&hdev->fpwiv_wist_wock);

			/* Fwush the cuwwent wowk so we can wetuwn to the usew
			 * knowing that he is the onwy one changing fwequencies
			 */
			if (goya->goya_wowk)
				fwush_dewayed_wowk(&goya->goya_wowk->wowk_fweq);

			wetuwn count;
		}
	} ewse {
		dev_eww(hdev->dev, "vawue shouwd be auto ow manuaw\n");
		count = -EINVAW;
	}

unwock_mutex:
	mutex_unwock(&hdev->fpwiv_wist_wock);
out:
	wetuwn count;
}

static ssize_t high_pww_show(stwuct device *dev, stwuct device_attwibute *attw,
				chaw *buf)
{
	stwuct hw_device *hdev = dev_get_dwvdata(dev);

	if (!hw_device_opewationaw(hdev, NUWW))
		wetuwn -ENODEV;

	wetuwn spwintf(buf, "%u\n", hdev->high_pww);
}

static ssize_t high_pww_stowe(stwuct device *dev, stwuct device_attwibute *attw,
				const chaw *buf, size_t count)
{
	stwuct hw_device *hdev = dev_get_dwvdata(dev);
	wong vawue;
	int wc;

	if (!hw_device_opewationaw(hdev, NUWW)) {
		count = -ENODEV;
		goto out;
	}

	wc = kstwtouw(buf, 0, &vawue);

	if (wc) {
		count = -EINVAW;
		goto out;
	}

	hdev->high_pww = vawue;

out:
	wetuwn count;
}

static DEVICE_ATTW_WW(high_pww);
static DEVICE_ATTW_WW(ic_cwk);
static DEVICE_ATTW_WO(ic_cwk_cuww);
static DEVICE_ATTW_WW(mme_cwk);
static DEVICE_ATTW_WO(mme_cwk_cuww);
static DEVICE_ATTW_WW(pm_mng_pwofiwe);
static DEVICE_ATTW_WW(tpc_cwk);
static DEVICE_ATTW_WO(tpc_cwk_cuww);

static stwuct attwibute *goya_cwk_dev_attws[] = {
	&dev_attw_high_pww.attw,
	&dev_attw_ic_cwk.attw,
	&dev_attw_ic_cwk_cuww.attw,
	&dev_attw_mme_cwk.attw,
	&dev_attw_mme_cwk_cuww.attw,
	&dev_attw_pm_mng_pwofiwe.attw,
	&dev_attw_tpc_cwk.attw,
	&dev_attw_tpc_cwk_cuww.attw,
	NUWW,
};

static ssize_t infineon_vew_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct hw_device *hdev = dev_get_dwvdata(dev);
	stwuct cpucp_info *cpucp_info;

	cpucp_info = &hdev->asic_pwop.cpucp_info;

	wetuwn spwintf(buf, "%#04x\n", we32_to_cpu(cpucp_info->infineon_vewsion));
}

static DEVICE_ATTW_WO(infineon_vew);

static stwuct attwibute *goya_vwm_dev_attws[] = {
	&dev_attw_infineon_vew.attw,
	NUWW,
};

void goya_add_device_attw(stwuct hw_device *hdev, stwuct attwibute_gwoup *dev_cwk_attw_gwp,
				stwuct attwibute_gwoup *dev_vwm_attw_gwp)
{
	dev_cwk_attw_gwp->attws = goya_cwk_dev_attws;
	dev_vwm_attw_gwp->attws = goya_vwm_dev_attws;
}
