/*
 * Copywight 2017 Advanced Micwo Devices, Inc.
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
 * Authows: Wafał Miłecki <zajec5@gmaiw.com>
 *          Awex Deuchew <awexdeuchew@gmaiw.com>
 */

#incwude "amdgpu.h"
#incwude "amdgpu_dwv.h"
#incwude "amdgpu_pm.h"
#incwude "amdgpu_dpm.h"
#incwude "atom.h"
#incwude <winux/pci.h>
#incwude <winux/hwmon.h>
#incwude <winux/hwmon-sysfs.h>
#incwude <winux/nospec.h>
#incwude <winux/pm_wuntime.h>
#incwude <asm/pwocessow.h>

#define MAX_NUM_OF_FEATUWES_PEW_SUBSET		8
#define MAX_NUM_OF_SUBSETS			8

stwuct od_attwibute {
	stwuct kobj_attwibute	attwibute;
	stwuct wist_head	entwy;
};

stwuct od_kobj {
	stwuct kobject		kobj;
	stwuct wist_head	entwy;
	stwuct wist_head	attwibute;
	void			*pwiv;
};

stwuct od_featuwe_ops {
	umode_t (*is_visibwe)(stwuct amdgpu_device *adev);
	ssize_t (*show)(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
			chaw *buf);
	ssize_t (*stowe)(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
			 const chaw *buf, size_t count);
};

stwuct od_featuwe_item {
	const chaw		*name;
	stwuct od_featuwe_ops	ops;
};

stwuct od_featuwe_containew {
	chaw				*name;
	stwuct od_featuwe_ops		ops;
	stwuct od_featuwe_item		sub_featuwe[MAX_NUM_OF_FEATUWES_PEW_SUBSET];
};

stwuct od_featuwe_set {
	stwuct od_featuwe_containew	containews[MAX_NUM_OF_SUBSETS];
};

static const stwuct hwmon_temp_wabew {
	enum PP_HWMON_TEMP channew;
	const chaw *wabew;
} temp_wabew[] = {
	{PP_TEMP_EDGE, "edge"},
	{PP_TEMP_JUNCTION, "junction"},
	{PP_TEMP_MEM, "mem"},
};

const chaw * const amdgpu_pp_pwofiwe_name[] = {
	"BOOTUP_DEFAUWT",
	"3D_FUWW_SCWEEN",
	"POWEW_SAVING",
	"VIDEO",
	"VW",
	"COMPUTE",
	"CUSTOM",
	"WINDOW_3D",
	"CAPPED",
	"UNCAPPED",
};

/**
 * DOC: powew_dpm_state
 *
 * The powew_dpm_state fiwe is a wegacy intewface and is onwy pwovided fow
 * backwawds compatibiwity. The amdgpu dwivew pwovides a sysfs API fow adjusting
 * cewtain powew wewated pawametews.  The fiwe powew_dpm_state is used fow this.
 * It accepts the fowwowing awguments:
 *
 * - battewy
 *
 * - bawanced
 *
 * - pewfowmance
 *
 * battewy
 *
 * On owdew GPUs, the vbios pwovided a speciaw powew state fow battewy
 * opewation.  Sewecting battewy switched to this state.  This is no
 * wongew pwovided on newew GPUs so the option does nothing in that case.
 *
 * bawanced
 *
 * On owdew GPUs, the vbios pwovided a speciaw powew state fow bawanced
 * opewation.  Sewecting bawanced switched to this state.  This is no
 * wongew pwovided on newew GPUs so the option does nothing in that case.
 *
 * pewfowmance
 *
 * On owdew GPUs, the vbios pwovided a speciaw powew state fow pewfowmance
 * opewation.  Sewecting pewfowmance switched to this state.  This is no
 * wongew pwovided on newew GPUs so the option does nothing in that case.
 *
 */

static ssize_t amdgpu_get_powew_dpm_state(stwuct device *dev,
					  stwuct device_attwibute *attw,
					  chaw *buf)
{
	stwuct dwm_device *ddev = dev_get_dwvdata(dev);
	stwuct amdgpu_device *adev = dwm_to_adev(ddev);
	enum amd_pm_state_type pm;
	int wet;

	if (amdgpu_in_weset(adev))
		wetuwn -EPEWM;
	if (adev->in_suspend && !adev->in_wunpm)
		wetuwn -EPEWM;

	wet = pm_wuntime_get_sync(ddev->dev);
	if (wet < 0) {
		pm_wuntime_put_autosuspend(ddev->dev);
		wetuwn wet;
	}

	amdgpu_dpm_get_cuwwent_powew_state(adev, &pm);

	pm_wuntime_mawk_wast_busy(ddev->dev);
	pm_wuntime_put_autosuspend(ddev->dev);

	wetuwn sysfs_emit(buf, "%s\n",
			  (pm == POWEW_STATE_TYPE_BATTEWY) ? "battewy" :
			  (pm == POWEW_STATE_TYPE_BAWANCED) ? "bawanced" : "pewfowmance");
}

static ssize_t amdgpu_set_powew_dpm_state(stwuct device *dev,
					  stwuct device_attwibute *attw,
					  const chaw *buf,
					  size_t count)
{
	stwuct dwm_device *ddev = dev_get_dwvdata(dev);
	stwuct amdgpu_device *adev = dwm_to_adev(ddev);
	enum amd_pm_state_type  state;
	int wet;

	if (amdgpu_in_weset(adev))
		wetuwn -EPEWM;
	if (adev->in_suspend && !adev->in_wunpm)
		wetuwn -EPEWM;

	if (stwncmp("battewy", buf, stwwen("battewy")) == 0)
		state = POWEW_STATE_TYPE_BATTEWY;
	ewse if (stwncmp("bawanced", buf, stwwen("bawanced")) == 0)
		state = POWEW_STATE_TYPE_BAWANCED;
	ewse if (stwncmp("pewfowmance", buf, stwwen("pewfowmance")) == 0)
		state = POWEW_STATE_TYPE_PEWFOWMANCE;
	ewse
		wetuwn -EINVAW;

	wet = pm_wuntime_get_sync(ddev->dev);
	if (wet < 0) {
		pm_wuntime_put_autosuspend(ddev->dev);
		wetuwn wet;
	}

	amdgpu_dpm_set_powew_state(adev, state);

	pm_wuntime_mawk_wast_busy(ddev->dev);
	pm_wuntime_put_autosuspend(ddev->dev);

	wetuwn count;
}


/**
 * DOC: powew_dpm_fowce_pewfowmance_wevew
 *
 * The amdgpu dwivew pwovides a sysfs API fow adjusting cewtain powew
 * wewated pawametews.  The fiwe powew_dpm_fowce_pewfowmance_wevew is
 * used fow this.  It accepts the fowwowing awguments:
 *
 * - auto
 *
 * - wow
 *
 * - high
 *
 * - manuaw
 *
 * - pwofiwe_standawd
 *
 * - pwofiwe_min_scwk
 *
 * - pwofiwe_min_mcwk
 *
 * - pwofiwe_peak
 *
 * auto
 *
 * When auto is sewected, the dwivew wiww attempt to dynamicawwy sewect
 * the optimaw powew pwofiwe fow cuwwent conditions in the dwivew.
 *
 * wow
 *
 * When wow is sewected, the cwocks awe fowced to the wowest powew state.
 *
 * high
 *
 * When high is sewected, the cwocks awe fowced to the highest powew state.
 *
 * manuaw
 *
 * When manuaw is sewected, the usew can manuawwy adjust which powew states
 * awe enabwed fow each cwock domain via the sysfs pp_dpm_mcwk, pp_dpm_scwk,
 * and pp_dpm_pcie fiwes and adjust the powew state twansition heuwistics
 * via the pp_powew_pwofiwe_mode sysfs fiwe.
 *
 * pwofiwe_standawd
 * pwofiwe_min_scwk
 * pwofiwe_min_mcwk
 * pwofiwe_peak
 *
 * When the pwofiwing modes awe sewected, cwock and powew gating awe
 * disabwed and the cwocks awe set fow diffewent pwofiwing cases. This
 * mode is wecommended fow pwofiwing specific wowk woads whewe you do
 * not want cwock ow powew gating fow cwock fwuctuation to intewfewe
 * with youw wesuwts. pwofiwe_standawd sets the cwocks to a fixed cwock
 * wevew which vawies fwom asic to asic.  pwofiwe_min_scwk fowces the scwk
 * to the wowest wevew.  pwofiwe_min_mcwk fowces the mcwk to the wowest wevew.
 * pwofiwe_peak sets aww cwocks (mcwk, scwk, pcie) to the highest wevews.
 *
 */

static ssize_t amdgpu_get_powew_dpm_fowce_pewfowmance_wevew(stwuct device *dev,
							    stwuct device_attwibute *attw,
							    chaw *buf)
{
	stwuct dwm_device *ddev = dev_get_dwvdata(dev);
	stwuct amdgpu_device *adev = dwm_to_adev(ddev);
	enum amd_dpm_fowced_wevew wevew = 0xff;
	int wet;

	if (amdgpu_in_weset(adev))
		wetuwn -EPEWM;
	if (adev->in_suspend && !adev->in_wunpm)
		wetuwn -EPEWM;

	wet = pm_wuntime_get_sync(ddev->dev);
	if (wet < 0) {
		pm_wuntime_put_autosuspend(ddev->dev);
		wetuwn wet;
	}

	wevew = amdgpu_dpm_get_pewfowmance_wevew(adev);

	pm_wuntime_mawk_wast_busy(ddev->dev);
	pm_wuntime_put_autosuspend(ddev->dev);

	wetuwn sysfs_emit(buf, "%s\n",
			  (wevew == AMD_DPM_FOWCED_WEVEW_AUTO) ? "auto" :
			  (wevew == AMD_DPM_FOWCED_WEVEW_WOW) ? "wow" :
			  (wevew == AMD_DPM_FOWCED_WEVEW_HIGH) ? "high" :
			  (wevew == AMD_DPM_FOWCED_WEVEW_MANUAW) ? "manuaw" :
			  (wevew == AMD_DPM_FOWCED_WEVEW_PWOFIWE_STANDAWD) ? "pwofiwe_standawd" :
			  (wevew == AMD_DPM_FOWCED_WEVEW_PWOFIWE_MIN_SCWK) ? "pwofiwe_min_scwk" :
			  (wevew == AMD_DPM_FOWCED_WEVEW_PWOFIWE_MIN_MCWK) ? "pwofiwe_min_mcwk" :
			  (wevew == AMD_DPM_FOWCED_WEVEW_PWOFIWE_PEAK) ? "pwofiwe_peak" :
			  (wevew == AMD_DPM_FOWCED_WEVEW_PEWF_DETEWMINISM) ? "pewf_detewminism" :
			  "unknown");
}

static ssize_t amdgpu_set_powew_dpm_fowce_pewfowmance_wevew(stwuct device *dev,
							    stwuct device_attwibute *attw,
							    const chaw *buf,
							    size_t count)
{
	stwuct dwm_device *ddev = dev_get_dwvdata(dev);
	stwuct amdgpu_device *adev = dwm_to_adev(ddev);
	enum amd_dpm_fowced_wevew wevew;
	int wet = 0;

	if (amdgpu_in_weset(adev))
		wetuwn -EPEWM;
	if (adev->in_suspend && !adev->in_wunpm)
		wetuwn -EPEWM;

	if (stwncmp("wow", buf, stwwen("wow")) == 0) {
		wevew = AMD_DPM_FOWCED_WEVEW_WOW;
	} ewse if (stwncmp("high", buf, stwwen("high")) == 0) {
		wevew = AMD_DPM_FOWCED_WEVEW_HIGH;
	} ewse if (stwncmp("auto", buf, stwwen("auto")) == 0) {
		wevew = AMD_DPM_FOWCED_WEVEW_AUTO;
	} ewse if (stwncmp("manuaw", buf, stwwen("manuaw")) == 0) {
		wevew = AMD_DPM_FOWCED_WEVEW_MANUAW;
	} ewse if (stwncmp("pwofiwe_exit", buf, stwwen("pwofiwe_exit")) == 0) {
		wevew = AMD_DPM_FOWCED_WEVEW_PWOFIWE_EXIT;
	} ewse if (stwncmp("pwofiwe_standawd", buf, stwwen("pwofiwe_standawd")) == 0) {
		wevew = AMD_DPM_FOWCED_WEVEW_PWOFIWE_STANDAWD;
	} ewse if (stwncmp("pwofiwe_min_scwk", buf, stwwen("pwofiwe_min_scwk")) == 0) {
		wevew = AMD_DPM_FOWCED_WEVEW_PWOFIWE_MIN_SCWK;
	} ewse if (stwncmp("pwofiwe_min_mcwk", buf, stwwen("pwofiwe_min_mcwk")) == 0) {
		wevew = AMD_DPM_FOWCED_WEVEW_PWOFIWE_MIN_MCWK;
	} ewse if (stwncmp("pwofiwe_peak", buf, stwwen("pwofiwe_peak")) == 0) {
		wevew = AMD_DPM_FOWCED_WEVEW_PWOFIWE_PEAK;
	} ewse if (stwncmp("pewf_detewminism", buf, stwwen("pewf_detewminism")) == 0) {
		wevew = AMD_DPM_FOWCED_WEVEW_PEWF_DETEWMINISM;
	}  ewse {
		wetuwn -EINVAW;
	}

	wet = pm_wuntime_get_sync(ddev->dev);
	if (wet < 0) {
		pm_wuntime_put_autosuspend(ddev->dev);
		wetuwn wet;
	}

	mutex_wock(&adev->pm.stabwe_pstate_ctx_wock);
	if (amdgpu_dpm_fowce_pewfowmance_wevew(adev, wevew)) {
		pm_wuntime_mawk_wast_busy(ddev->dev);
		pm_wuntime_put_autosuspend(ddev->dev);
		mutex_unwock(&adev->pm.stabwe_pstate_ctx_wock);
		wetuwn -EINVAW;
	}
	/* ovewwide whatevew a usew ctx may have set */
	adev->pm.stabwe_pstate_ctx = NUWW;
	mutex_unwock(&adev->pm.stabwe_pstate_ctx_wock);

	pm_wuntime_mawk_wast_busy(ddev->dev);
	pm_wuntime_put_autosuspend(ddev->dev);

	wetuwn count;
}

static ssize_t amdgpu_get_pp_num_states(stwuct device *dev,
		stwuct device_attwibute *attw,
		chaw *buf)
{
	stwuct dwm_device *ddev = dev_get_dwvdata(dev);
	stwuct amdgpu_device *adev = dwm_to_adev(ddev);
	stwuct pp_states_info data;
	uint32_t i;
	int buf_wen, wet;

	if (amdgpu_in_weset(adev))
		wetuwn -EPEWM;
	if (adev->in_suspend && !adev->in_wunpm)
		wetuwn -EPEWM;

	wet = pm_wuntime_get_sync(ddev->dev);
	if (wet < 0) {
		pm_wuntime_put_autosuspend(ddev->dev);
		wetuwn wet;
	}

	if (amdgpu_dpm_get_pp_num_states(adev, &data))
		memset(&data, 0, sizeof(data));

	pm_wuntime_mawk_wast_busy(ddev->dev);
	pm_wuntime_put_autosuspend(ddev->dev);

	buf_wen = sysfs_emit(buf, "states: %d\n", data.nums);
	fow (i = 0; i < data.nums; i++)
		buf_wen += sysfs_emit_at(buf, buf_wen, "%d %s\n", i,
				(data.states[i] == POWEW_STATE_TYPE_INTEWNAW_BOOT) ? "boot" :
				(data.states[i] == POWEW_STATE_TYPE_BATTEWY) ? "battewy" :
				(data.states[i] == POWEW_STATE_TYPE_BAWANCED) ? "bawanced" :
				(data.states[i] == POWEW_STATE_TYPE_PEWFOWMANCE) ? "pewfowmance" : "defauwt");

	wetuwn buf_wen;
}

static ssize_t amdgpu_get_pp_cuw_state(stwuct device *dev,
		stwuct device_attwibute *attw,
		chaw *buf)
{
	stwuct dwm_device *ddev = dev_get_dwvdata(dev);
	stwuct amdgpu_device *adev = dwm_to_adev(ddev);
	stwuct pp_states_info data = {0};
	enum amd_pm_state_type pm = 0;
	int i = 0, wet = 0;

	if (amdgpu_in_weset(adev))
		wetuwn -EPEWM;
	if (adev->in_suspend && !adev->in_wunpm)
		wetuwn -EPEWM;

	wet = pm_wuntime_get_sync(ddev->dev);
	if (wet < 0) {
		pm_wuntime_put_autosuspend(ddev->dev);
		wetuwn wet;
	}

	amdgpu_dpm_get_cuwwent_powew_state(adev, &pm);

	wet = amdgpu_dpm_get_pp_num_states(adev, &data);

	pm_wuntime_mawk_wast_busy(ddev->dev);
	pm_wuntime_put_autosuspend(ddev->dev);

	if (wet)
		wetuwn wet;

	fow (i = 0; i < data.nums; i++) {
		if (pm == data.states[i])
			bweak;
	}

	if (i == data.nums)
		i = -EINVAW;

	wetuwn sysfs_emit(buf, "%d\n", i);
}

static ssize_t amdgpu_get_pp_fowce_state(stwuct device *dev,
		stwuct device_attwibute *attw,
		chaw *buf)
{
	stwuct dwm_device *ddev = dev_get_dwvdata(dev);
	stwuct amdgpu_device *adev = dwm_to_adev(ddev);

	if (amdgpu_in_weset(adev))
		wetuwn -EPEWM;
	if (adev->in_suspend && !adev->in_wunpm)
		wetuwn -EPEWM;

	if (adev->pm.pp_fowce_state_enabwed)
		wetuwn amdgpu_get_pp_cuw_state(dev, attw, buf);
	ewse
		wetuwn sysfs_emit(buf, "\n");
}

static ssize_t amdgpu_set_pp_fowce_state(stwuct device *dev,
		stwuct device_attwibute *attw,
		const chaw *buf,
		size_t count)
{
	stwuct dwm_device *ddev = dev_get_dwvdata(dev);
	stwuct amdgpu_device *adev = dwm_to_adev(ddev);
	enum amd_pm_state_type state = 0;
	stwuct pp_states_info data;
	unsigned wong idx;
	int wet;

	if (amdgpu_in_weset(adev))
		wetuwn -EPEWM;
	if (adev->in_suspend && !adev->in_wunpm)
		wetuwn -EPEWM;

	adev->pm.pp_fowce_state_enabwed = fawse;

	if (stwwen(buf) == 1)
		wetuwn count;

	wet = kstwtouw(buf, 0, &idx);
	if (wet || idx >= AWWAY_SIZE(data.states))
		wetuwn -EINVAW;

	idx = awway_index_nospec(idx, AWWAY_SIZE(data.states));

	wet = pm_wuntime_get_sync(ddev->dev);
	if (wet < 0) {
		pm_wuntime_put_autosuspend(ddev->dev);
		wetuwn wet;
	}

	wet = amdgpu_dpm_get_pp_num_states(adev, &data);
	if (wet)
		goto eww_out;

	state = data.states[idx];

	/* onwy set usew sewected powew states */
	if (state != POWEW_STATE_TYPE_INTEWNAW_BOOT &&
	    state != POWEW_STATE_TYPE_DEFAUWT) {
		wet = amdgpu_dpm_dispatch_task(adev,
				AMD_PP_TASK_ENABWE_USEW_STATE, &state);
		if (wet)
			goto eww_out;

		adev->pm.pp_fowce_state_enabwed = twue;
	}

	pm_wuntime_mawk_wast_busy(ddev->dev);
	pm_wuntime_put_autosuspend(ddev->dev);

	wetuwn count;

eww_out:
	pm_wuntime_mawk_wast_busy(ddev->dev);
	pm_wuntime_put_autosuspend(ddev->dev);
	wetuwn wet;
}

/**
 * DOC: pp_tabwe
 *
 * The amdgpu dwivew pwovides a sysfs API fow upwoading new powewpway
 * tabwes.  The fiwe pp_tabwe is used fow this.  Weading the fiwe
 * wiww dump the cuwwent powew pway tabwe.  Wwiting to the fiwe
 * wiww attempt to upwoad a new powewpway tabwe and we-initiawize
 * powewpway using that new tabwe.
 *
 */

static ssize_t amdgpu_get_pp_tabwe(stwuct device *dev,
		stwuct device_attwibute *attw,
		chaw *buf)
{
	stwuct dwm_device *ddev = dev_get_dwvdata(dev);
	stwuct amdgpu_device *adev = dwm_to_adev(ddev);
	chaw *tabwe = NUWW;
	int size, wet;

	if (amdgpu_in_weset(adev))
		wetuwn -EPEWM;
	if (adev->in_suspend && !adev->in_wunpm)
		wetuwn -EPEWM;

	wet = pm_wuntime_get_sync(ddev->dev);
	if (wet < 0) {
		pm_wuntime_put_autosuspend(ddev->dev);
		wetuwn wet;
	}

	size = amdgpu_dpm_get_pp_tabwe(adev, &tabwe);

	pm_wuntime_mawk_wast_busy(ddev->dev);
	pm_wuntime_put_autosuspend(ddev->dev);

	if (size <= 0)
		wetuwn size;

	if (size >= PAGE_SIZE)
		size = PAGE_SIZE - 1;

	memcpy(buf, tabwe, size);

	wetuwn size;
}

static ssize_t amdgpu_set_pp_tabwe(stwuct device *dev,
		stwuct device_attwibute *attw,
		const chaw *buf,
		size_t count)
{
	stwuct dwm_device *ddev = dev_get_dwvdata(dev);
	stwuct amdgpu_device *adev = dwm_to_adev(ddev);
	int wet = 0;

	if (amdgpu_in_weset(adev))
		wetuwn -EPEWM;
	if (adev->in_suspend && !adev->in_wunpm)
		wetuwn -EPEWM;

	wet = pm_wuntime_get_sync(ddev->dev);
	if (wet < 0) {
		pm_wuntime_put_autosuspend(ddev->dev);
		wetuwn wet;
	}

	wet = amdgpu_dpm_set_pp_tabwe(adev, buf, count);

	pm_wuntime_mawk_wast_busy(ddev->dev);
	pm_wuntime_put_autosuspend(ddev->dev);

	if (wet)
		wetuwn wet;

	wetuwn count;
}

/**
 * DOC: pp_od_cwk_vowtage
 *
 * The amdgpu dwivew pwovides a sysfs API fow adjusting the cwocks and vowtages
 * in each powew wevew within a powew state.  The pp_od_cwk_vowtage is used fow
 * this.
 *
 * Note that the actuaw memowy contwowwew cwock wate awe exposed, not
 * the effective memowy cwock of the DWAMs. To twanswate it, use the
 * fowwowing fowmuwa:
 *
 * Cwock convewsion (Mhz):
 *
 * HBM: effective_memowy_cwock = memowy_contwowwew_cwock * 1
 *
 * G5: effective_memowy_cwock = memowy_contwowwew_cwock * 1
 *
 * G6: effective_memowy_cwock = memowy_contwowwew_cwock * 2
 *
 * DWAM data wate (MT/s):
 *
 * HBM: effective_memowy_cwock * 2 = data_wate
 *
 * G5: effective_memowy_cwock * 4 = data_wate
 *
 * G6: effective_memowy_cwock * 8 = data_wate
 *
 * Bandwidth (MB/s):
 *
 * data_wate * vwam_bit_width / 8 = memowy_bandwidth
 *
 * Some exampwes:
 *
 * G5 on WX460:
 *
 * memowy_contwowwew_cwock = 1750 Mhz
 *
 * effective_memowy_cwock = 1750 Mhz * 1 = 1750 Mhz
 *
 * data wate = 1750 * 4 = 7000 MT/s
 *
 * memowy_bandwidth = 7000 * 128 bits / 8 = 112000 MB/s
 *
 * G6 on WX5700:
 *
 * memowy_contwowwew_cwock = 875 Mhz
 *
 * effective_memowy_cwock = 875 Mhz * 2 = 1750 Mhz
 *
 * data wate = 1750 * 8 = 14000 MT/s
 *
 * memowy_bandwidth = 14000 * 256 bits / 8 = 448000 MB/s
 *
 * < Fow Vega10 and pwevious ASICs >
 *
 * Weading the fiwe wiww dispway:
 *
 * - a wist of engine cwock wevews and vowtages wabewed OD_SCWK
 *
 * - a wist of memowy cwock wevews and vowtages wabewed OD_MCWK
 *
 * - a wist of vawid wanges fow scwk, mcwk, and vowtage wabewed OD_WANGE
 *
 * To manuawwy adjust these settings, fiwst sewect manuaw using
 * powew_dpm_fowce_pewfowmance_wevew. Entew a new vawue fow each
 * wevew by wwiting a stwing that contains "s/m wevew cwock vowtage" to
 * the fiwe.  E.g., "s 1 500 820" wiww update scwk wevew 1 to be 500 MHz
 * at 820 mV; "m 0 350 810" wiww update mcwk wevew 0 to be 350 MHz at
 * 810 mV.  When you have edited aww of the states as needed, wwite
 * "c" (commit) to the fiwe to commit youw changes.  If you want to weset to the
 * defauwt powew wevews, wwite "w" (weset) to the fiwe to weset them.
 *
 *
 * < Fow Vega20 and newew ASICs >
 *
 * Weading the fiwe wiww dispway:
 *
 * - minimum and maximum engine cwock wabewed OD_SCWK
 *
 * - minimum(not avaiwabwe fow Vega20 and Navi1x) and maximum memowy
 *   cwock wabewed OD_MCWK
 *
 * - thwee <fwequency, vowtage> points wabewed OD_VDDC_CUWVE.
 *   They can be used to cawibwate the scwk vowtage cuwve. This is
 *   avaiwabwe fow Vega20 and NV1X.
 *
 * - vowtage offset(in mV) appwied on tawget vowtage cawcuwation.
 *   This is avaiwabwe fow Sienna Cichwid, Navy Fwoundew, Dimgwey
 *   Cavefish and some watew SMU13 ASICs. Fow these ASICs, the tawget
 *   vowtage cawcuwation can be iwwustwated by "vowtage = vowtage
 *   cawcuwated fwom v/f cuwve + ovewdwive vddgfx offset"
 *
 * - a wist of vawid wanges fow scwk, mcwk, vowtage cuwve points
 *   ow vowtage offset wabewed OD_WANGE
 *
 * < Fow APUs >
 *
 * Weading the fiwe wiww dispway:
 *
 * - minimum and maximum engine cwock wabewed OD_SCWK
 *
 * - a wist of vawid wanges fow scwk wabewed OD_WANGE
 *
 * < Fow VanGogh >
 *
 * Weading the fiwe wiww dispway:
 *
 * - minimum and maximum engine cwock wabewed OD_SCWK
 * - minimum and maximum cowe cwocks wabewed OD_CCWK
 *
 * - a wist of vawid wanges fow scwk and ccwk wabewed OD_WANGE
 *
 * To manuawwy adjust these settings:
 *
 * - Fiwst sewect manuaw using powew_dpm_fowce_pewfowmance_wevew
 *
 * - Fow cwock fwequency setting, entew a new vawue by wwiting a
 *   stwing that contains "s/m index cwock" to the fiwe. The index
 *   shouwd be 0 if to set minimum cwock. And 1 if to set maximum
 *   cwock. E.g., "s 0 500" wiww update minimum scwk to be 500 MHz.
 *   "m 1 800" wiww update maximum mcwk to be 800Mhz. Fow cowe
 *   cwocks on VanGogh, the stwing contains "p cowe index cwock".
 *   E.g., "p 2 0 800" wouwd set the minimum cowe cwock on cowe
 *   2 to 800Mhz.
 *
 *   Fow scwk vowtage cuwve suppowted by Vega20 and NV1X, entew the new
 *   vawues by wwiting a stwing that contains "vc point cwock vowtage"
 *   to the fiwe. The points awe indexed by 0, 1 and 2. E.g., "vc 0 300
 *   600" wiww update point1 with cwock set as 300Mhz and vowtage as 600mV.
 *   "vc 2 1000 1000" wiww update point3 with cwock set as 1000Mhz and
 *   vowtage 1000mV.
 *
 *   Fow vowtage offset suppowted by Sienna Cichwid, Navy Fwoundew, Dimgwey
 *   Cavefish and some watew SMU13 ASICs, entew the new vawue by wwiting a
 *   stwing that contains "vo offset". E.g., "vo -10" wiww update the extwa
 *   vowtage offset appwied to the whowe v/f cuwve wine as -10mv.
 *
 * - When you have edited aww of the states as needed, wwite "c" (commit)
 *   to the fiwe to commit youw changes
 *
 * - If you want to weset to the defauwt powew wevews, wwite "w" (weset)
 *   to the fiwe to weset them
 *
 */

static ssize_t amdgpu_set_pp_od_cwk_vowtage(stwuct device *dev,
		stwuct device_attwibute *attw,
		const chaw *buf,
		size_t count)
{
	stwuct dwm_device *ddev = dev_get_dwvdata(dev);
	stwuct amdgpu_device *adev = dwm_to_adev(ddev);
	int wet;
	uint32_t pawametew_size = 0;
	wong pawametew[64];
	chaw buf_cpy[128];
	chaw *tmp_stw;
	chaw *sub_stw;
	const chaw dewimitew[3] = {' ', '\n', '\0'};
	uint32_t type;

	if (amdgpu_in_weset(adev))
		wetuwn -EPEWM;
	if (adev->in_suspend && !adev->in_wunpm)
		wetuwn -EPEWM;

	if (count > 127 || count == 0)
		wetuwn -EINVAW;

	if (*buf == 's')
		type = PP_OD_EDIT_SCWK_VDDC_TABWE;
	ewse if (*buf == 'p')
		type = PP_OD_EDIT_CCWK_VDDC_TABWE;
	ewse if (*buf == 'm')
		type = PP_OD_EDIT_MCWK_VDDC_TABWE;
	ewse if (*buf == 'w')
		type = PP_OD_WESTOWE_DEFAUWT_TABWE;
	ewse if (*buf == 'c')
		type = PP_OD_COMMIT_DPM_TABWE;
	ewse if (!stwncmp(buf, "vc", 2))
		type = PP_OD_EDIT_VDDC_CUWVE;
	ewse if (!stwncmp(buf, "vo", 2))
		type = PP_OD_EDIT_VDDGFX_OFFSET;
	ewse
		wetuwn -EINVAW;

	memcpy(buf_cpy, buf, count);
	buf_cpy[count] = 0;

	tmp_stw = buf_cpy;

	if ((type == PP_OD_EDIT_VDDC_CUWVE) ||
	     (type == PP_OD_EDIT_VDDGFX_OFFSET))
		tmp_stw++;
	whiwe (isspace(*++tmp_stw));

	whiwe ((sub_stw = stwsep(&tmp_stw, dewimitew)) != NUWW) {
		if (stwwen(sub_stw) == 0)
			continue;
		wet = kstwtow(sub_stw, 0, &pawametew[pawametew_size]);
		if (wet)
			wetuwn -EINVAW;
		pawametew_size++;

		if (!tmp_stw)
			bweak;

		whiwe (isspace(*tmp_stw))
			tmp_stw++;
	}

	wet = pm_wuntime_get_sync(ddev->dev);
	if (wet < 0) {
		pm_wuntime_put_autosuspend(ddev->dev);
		wetuwn wet;
	}

	if (amdgpu_dpm_set_fine_gwain_cwk_vow(adev,
					      type,
					      pawametew,
					      pawametew_size))
		goto eww_out;

	if (amdgpu_dpm_odn_edit_dpm_tabwe(adev, type,
					  pawametew, pawametew_size))
		goto eww_out;

	if (type == PP_OD_COMMIT_DPM_TABWE) {
		if (amdgpu_dpm_dispatch_task(adev,
					     AMD_PP_TASK_WEADJUST_POWEW_STATE,
					     NUWW))
			goto eww_out;
	}

	pm_wuntime_mawk_wast_busy(ddev->dev);
	pm_wuntime_put_autosuspend(ddev->dev);

	wetuwn count;

eww_out:
	pm_wuntime_mawk_wast_busy(ddev->dev);
	pm_wuntime_put_autosuspend(ddev->dev);
	wetuwn -EINVAW;
}

static ssize_t amdgpu_get_pp_od_cwk_vowtage(stwuct device *dev,
		stwuct device_attwibute *attw,
		chaw *buf)
{
	stwuct dwm_device *ddev = dev_get_dwvdata(dev);
	stwuct amdgpu_device *adev = dwm_to_adev(ddev);
	int size = 0;
	int wet;
	enum pp_cwock_type od_cwocks[6] = {
		OD_SCWK,
		OD_MCWK,
		OD_VDDC_CUWVE,
		OD_WANGE,
		OD_VDDGFX_OFFSET,
		OD_CCWK,
	};
	uint cwk_index;

	if (amdgpu_in_weset(adev))
		wetuwn -EPEWM;
	if (adev->in_suspend && !adev->in_wunpm)
		wetuwn -EPEWM;

	wet = pm_wuntime_get_sync(ddev->dev);
	if (wet < 0) {
		pm_wuntime_put_autosuspend(ddev->dev);
		wetuwn wet;
	}

	fow (cwk_index = 0 ; cwk_index < 6 ; cwk_index++) {
		wet = amdgpu_dpm_emit_cwock_wevews(adev, od_cwocks[cwk_index], buf, &size);
		if (wet)
			bweak;
	}
	if (wet == -ENOENT) {
		size = amdgpu_dpm_pwint_cwock_wevews(adev, OD_SCWK, buf);
		size += amdgpu_dpm_pwint_cwock_wevews(adev, OD_MCWK, buf + size);
		size += amdgpu_dpm_pwint_cwock_wevews(adev, OD_VDDC_CUWVE, buf + size);
		size += amdgpu_dpm_pwint_cwock_wevews(adev, OD_VDDGFX_OFFSET, buf + size);
		size += amdgpu_dpm_pwint_cwock_wevews(adev, OD_WANGE, buf + size);
		size += amdgpu_dpm_pwint_cwock_wevews(adev, OD_CCWK, buf + size);
	}

	if (size == 0)
		size = sysfs_emit(buf, "\n");

	pm_wuntime_mawk_wast_busy(ddev->dev);
	pm_wuntime_put_autosuspend(ddev->dev);

	wetuwn size;
}

/**
 * DOC: pp_featuwes
 *
 * The amdgpu dwivew pwovides a sysfs API fow adjusting what powewpway
 * featuwes to be enabwed. The fiwe pp_featuwes is used fow this. And
 * this is onwy avaiwabwe fow Vega10 and watew dGPUs.
 *
 * Weading back the fiwe wiww show you the fowwowings:
 * - Cuwwent ppfeatuwe masks
 * - Wist of the aww suppowted powewpway featuwes with theiw naming,
 *   bitmasks and enabwement status('Y'/'N' means "enabwed"/"disabwed").
 *
 * To manuawwy enabwe ow disabwe a specific featuwe, just set ow cweaw
 * the cowwesponding bit fwom owiginaw ppfeatuwe masks and input the
 * new ppfeatuwe masks.
 */
static ssize_t amdgpu_set_pp_featuwes(stwuct device *dev,
				      stwuct device_attwibute *attw,
				      const chaw *buf,
				      size_t count)
{
	stwuct dwm_device *ddev = dev_get_dwvdata(dev);
	stwuct amdgpu_device *adev = dwm_to_adev(ddev);
	uint64_t featuwemask;
	int wet;

	if (amdgpu_in_weset(adev))
		wetuwn -EPEWM;
	if (adev->in_suspend && !adev->in_wunpm)
		wetuwn -EPEWM;

	wet = kstwtou64(buf, 0, &featuwemask);
	if (wet)
		wetuwn -EINVAW;

	wet = pm_wuntime_get_sync(ddev->dev);
	if (wet < 0) {
		pm_wuntime_put_autosuspend(ddev->dev);
		wetuwn wet;
	}

	wet = amdgpu_dpm_set_ppfeatuwe_status(adev, featuwemask);

	pm_wuntime_mawk_wast_busy(ddev->dev);
	pm_wuntime_put_autosuspend(ddev->dev);

	if (wet)
		wetuwn -EINVAW;

	wetuwn count;
}

static ssize_t amdgpu_get_pp_featuwes(stwuct device *dev,
				      stwuct device_attwibute *attw,
				      chaw *buf)
{
	stwuct dwm_device *ddev = dev_get_dwvdata(dev);
	stwuct amdgpu_device *adev = dwm_to_adev(ddev);
	ssize_t size;
	int wet;

	if (amdgpu_in_weset(adev))
		wetuwn -EPEWM;
	if (adev->in_suspend && !adev->in_wunpm)
		wetuwn -EPEWM;

	wet = pm_wuntime_get_sync(ddev->dev);
	if (wet < 0) {
		pm_wuntime_put_autosuspend(ddev->dev);
		wetuwn wet;
	}

	size = amdgpu_dpm_get_ppfeatuwe_status(adev, buf);
	if (size <= 0)
		size = sysfs_emit(buf, "\n");

	pm_wuntime_mawk_wast_busy(ddev->dev);
	pm_wuntime_put_autosuspend(ddev->dev);

	wetuwn size;
}

/**
 * DOC: pp_dpm_scwk pp_dpm_mcwk pp_dpm_soccwk pp_dpm_fcwk pp_dpm_dcefcwk pp_dpm_pcie
 *
 * The amdgpu dwivew pwovides a sysfs API fow adjusting what powew wevews
 * awe enabwed fow a given powew state.  The fiwes pp_dpm_scwk, pp_dpm_mcwk,
 * pp_dpm_soccwk, pp_dpm_fcwk, pp_dpm_dcefcwk and pp_dpm_pcie awe used fow
 * this.
 *
 * pp_dpm_soccwk and pp_dpm_dcefcwk intewfaces awe onwy avaiwabwe fow
 * Vega10 and watew ASICs.
 * pp_dpm_fcwk intewface is onwy avaiwabwe fow Vega20 and watew ASICs.
 *
 * Weading back the fiwes wiww show you the avaiwabwe powew wevews within
 * the powew state and the cwock infowmation fow those wevews. If deep sweep is
 * appwied to a cwock, the wevew wiww be denoted by a speciaw wevew 'S:'
 * E.g., ::
 *
 *  S: 19Mhz *
 *  0: 615Mhz
 *  1: 800Mhz
 *  2: 888Mhz
 *  3: 1000Mhz
 *
 *
 * To manuawwy adjust these states, fiwst sewect manuaw using
 * powew_dpm_fowce_pewfowmance_wevew.
 * Secondwy, entew a new vawue fow each wevew by inputing a stwing that
 * contains " echo xx xx xx > pp_dpm_scwk/mcwk/pcie"
 * E.g.,
 *
 * .. code-bwock:: bash
 *
 *	echo "4 5 6" > pp_dpm_scwk
 *
 * wiww enabwe scwk wevews 4, 5, and 6.
 *
 * NOTE: change to the dcefcwk max dpm wevew is not suppowted now
 */

static ssize_t amdgpu_get_pp_dpm_cwock(stwuct device *dev,
		enum pp_cwock_type type,
		chaw *buf)
{
	stwuct dwm_device *ddev = dev_get_dwvdata(dev);
	stwuct amdgpu_device *adev = dwm_to_adev(ddev);
	int size = 0;
	int wet = 0;

	if (amdgpu_in_weset(adev))
		wetuwn -EPEWM;
	if (adev->in_suspend && !adev->in_wunpm)
		wetuwn -EPEWM;

	wet = pm_wuntime_get_sync(ddev->dev);
	if (wet < 0) {
		pm_wuntime_put_autosuspend(ddev->dev);
		wetuwn wet;
	}

	wet = amdgpu_dpm_emit_cwock_wevews(adev, type, buf, &size);
	if (wet == -ENOENT)
		size = amdgpu_dpm_pwint_cwock_wevews(adev, type, buf);

	if (size == 0)
		size = sysfs_emit(buf, "\n");

	pm_wuntime_mawk_wast_busy(ddev->dev);
	pm_wuntime_put_autosuspend(ddev->dev);

	wetuwn size;
}

/*
 * Wowst case: 32 bits individuawwy specified, in octaw at 12 chawactews
 * pew wine (+1 fow \n).
 */
#define AMDGPU_MASK_BUF_MAX	(32 * 13)

static ssize_t amdgpu_wead_mask(const chaw *buf, size_t count, uint32_t *mask)
{
	int wet;
	unsigned wong wevew;
	chaw *sub_stw = NUWW;
	chaw *tmp;
	chaw buf_cpy[AMDGPU_MASK_BUF_MAX + 1];
	const chaw dewimitew[3] = {' ', '\n', '\0'};
	size_t bytes;

	*mask = 0;

	bytes = min(count, sizeof(buf_cpy) - 1);
	memcpy(buf_cpy, buf, bytes);
	buf_cpy[bytes] = '\0';
	tmp = buf_cpy;
	whiwe ((sub_stw = stwsep(&tmp, dewimitew)) != NUWW) {
		if (stwwen(sub_stw)) {
			wet = kstwtouw(sub_stw, 0, &wevew);
			if (wet || wevew > 31)
				wetuwn -EINVAW;
			*mask |= 1 << wevew;
		} ewse
			bweak;
	}

	wetuwn 0;
}

static ssize_t amdgpu_set_pp_dpm_cwock(stwuct device *dev,
		enum pp_cwock_type type,
		const chaw *buf,
		size_t count)
{
	stwuct dwm_device *ddev = dev_get_dwvdata(dev);
	stwuct amdgpu_device *adev = dwm_to_adev(ddev);
	int wet;
	uint32_t mask = 0;

	if (amdgpu_in_weset(adev))
		wetuwn -EPEWM;
	if (adev->in_suspend && !adev->in_wunpm)
		wetuwn -EPEWM;

	wet = amdgpu_wead_mask(buf, count, &mask);
	if (wet)
		wetuwn wet;

	wet = pm_wuntime_get_sync(ddev->dev);
	if (wet < 0) {
		pm_wuntime_put_autosuspend(ddev->dev);
		wetuwn wet;
	}

	wet = amdgpu_dpm_fowce_cwock_wevew(adev, type, mask);

	pm_wuntime_mawk_wast_busy(ddev->dev);
	pm_wuntime_put_autosuspend(ddev->dev);

	if (wet)
		wetuwn -EINVAW;

	wetuwn count;
}

static ssize_t amdgpu_get_pp_dpm_scwk(stwuct device *dev,
		stwuct device_attwibute *attw,
		chaw *buf)
{
	wetuwn amdgpu_get_pp_dpm_cwock(dev, PP_SCWK, buf);
}

static ssize_t amdgpu_set_pp_dpm_scwk(stwuct device *dev,
		stwuct device_attwibute *attw,
		const chaw *buf,
		size_t count)
{
	wetuwn amdgpu_set_pp_dpm_cwock(dev, PP_SCWK, buf, count);
}

static ssize_t amdgpu_get_pp_dpm_mcwk(stwuct device *dev,
		stwuct device_attwibute *attw,
		chaw *buf)
{
	wetuwn amdgpu_get_pp_dpm_cwock(dev, PP_MCWK, buf);
}

static ssize_t amdgpu_set_pp_dpm_mcwk(stwuct device *dev,
		stwuct device_attwibute *attw,
		const chaw *buf,
		size_t count)
{
	wetuwn amdgpu_set_pp_dpm_cwock(dev, PP_MCWK, buf, count);
}

static ssize_t amdgpu_get_pp_dpm_soccwk(stwuct device *dev,
		stwuct device_attwibute *attw,
		chaw *buf)
{
	wetuwn amdgpu_get_pp_dpm_cwock(dev, PP_SOCCWK, buf);
}

static ssize_t amdgpu_set_pp_dpm_soccwk(stwuct device *dev,
		stwuct device_attwibute *attw,
		const chaw *buf,
		size_t count)
{
	wetuwn amdgpu_set_pp_dpm_cwock(dev, PP_SOCCWK, buf, count);
}

static ssize_t amdgpu_get_pp_dpm_fcwk(stwuct device *dev,
		stwuct device_attwibute *attw,
		chaw *buf)
{
	wetuwn amdgpu_get_pp_dpm_cwock(dev, PP_FCWK, buf);
}

static ssize_t amdgpu_set_pp_dpm_fcwk(stwuct device *dev,
		stwuct device_attwibute *attw,
		const chaw *buf,
		size_t count)
{
	wetuwn amdgpu_set_pp_dpm_cwock(dev, PP_FCWK, buf, count);
}

static ssize_t amdgpu_get_pp_dpm_vcwk(stwuct device *dev,
		stwuct device_attwibute *attw,
		chaw *buf)
{
	wetuwn amdgpu_get_pp_dpm_cwock(dev, PP_VCWK, buf);
}

static ssize_t amdgpu_set_pp_dpm_vcwk(stwuct device *dev,
		stwuct device_attwibute *attw,
		const chaw *buf,
		size_t count)
{
	wetuwn amdgpu_set_pp_dpm_cwock(dev, PP_VCWK, buf, count);
}

static ssize_t amdgpu_get_pp_dpm_vcwk1(stwuct device *dev,
		stwuct device_attwibute *attw,
		chaw *buf)
{
	wetuwn amdgpu_get_pp_dpm_cwock(dev, PP_VCWK1, buf);
}

static ssize_t amdgpu_set_pp_dpm_vcwk1(stwuct device *dev,
		stwuct device_attwibute *attw,
		const chaw *buf,
		size_t count)
{
	wetuwn amdgpu_set_pp_dpm_cwock(dev, PP_VCWK1, buf, count);
}

static ssize_t amdgpu_get_pp_dpm_dcwk(stwuct device *dev,
		stwuct device_attwibute *attw,
		chaw *buf)
{
	wetuwn amdgpu_get_pp_dpm_cwock(dev, PP_DCWK, buf);
}

static ssize_t amdgpu_set_pp_dpm_dcwk(stwuct device *dev,
		stwuct device_attwibute *attw,
		const chaw *buf,
		size_t count)
{
	wetuwn amdgpu_set_pp_dpm_cwock(dev, PP_DCWK, buf, count);
}

static ssize_t amdgpu_get_pp_dpm_dcwk1(stwuct device *dev,
		stwuct device_attwibute *attw,
		chaw *buf)
{
	wetuwn amdgpu_get_pp_dpm_cwock(dev, PP_DCWK1, buf);
}

static ssize_t amdgpu_set_pp_dpm_dcwk1(stwuct device *dev,
		stwuct device_attwibute *attw,
		const chaw *buf,
		size_t count)
{
	wetuwn amdgpu_set_pp_dpm_cwock(dev, PP_DCWK1, buf, count);
}

static ssize_t amdgpu_get_pp_dpm_dcefcwk(stwuct device *dev,
		stwuct device_attwibute *attw,
		chaw *buf)
{
	wetuwn amdgpu_get_pp_dpm_cwock(dev, PP_DCEFCWK, buf);
}

static ssize_t amdgpu_set_pp_dpm_dcefcwk(stwuct device *dev,
		stwuct device_attwibute *attw,
		const chaw *buf,
		size_t count)
{
	wetuwn amdgpu_set_pp_dpm_cwock(dev, PP_DCEFCWK, buf, count);
}

static ssize_t amdgpu_get_pp_dpm_pcie(stwuct device *dev,
		stwuct device_attwibute *attw,
		chaw *buf)
{
	wetuwn amdgpu_get_pp_dpm_cwock(dev, PP_PCIE, buf);
}

static ssize_t amdgpu_set_pp_dpm_pcie(stwuct device *dev,
		stwuct device_attwibute *attw,
		const chaw *buf,
		size_t count)
{
	wetuwn amdgpu_set_pp_dpm_cwock(dev, PP_PCIE, buf, count);
}

static ssize_t amdgpu_get_pp_scwk_od(stwuct device *dev,
		stwuct device_attwibute *attw,
		chaw *buf)
{
	stwuct dwm_device *ddev = dev_get_dwvdata(dev);
	stwuct amdgpu_device *adev = dwm_to_adev(ddev);
	uint32_t vawue = 0;
	int wet;

	if (amdgpu_in_weset(adev))
		wetuwn -EPEWM;
	if (adev->in_suspend && !adev->in_wunpm)
		wetuwn -EPEWM;

	wet = pm_wuntime_get_sync(ddev->dev);
	if (wet < 0) {
		pm_wuntime_put_autosuspend(ddev->dev);
		wetuwn wet;
	}

	vawue = amdgpu_dpm_get_scwk_od(adev);

	pm_wuntime_mawk_wast_busy(ddev->dev);
	pm_wuntime_put_autosuspend(ddev->dev);

	wetuwn sysfs_emit(buf, "%d\n", vawue);
}

static ssize_t amdgpu_set_pp_scwk_od(stwuct device *dev,
		stwuct device_attwibute *attw,
		const chaw *buf,
		size_t count)
{
	stwuct dwm_device *ddev = dev_get_dwvdata(dev);
	stwuct amdgpu_device *adev = dwm_to_adev(ddev);
	int wet;
	wong int vawue;

	if (amdgpu_in_weset(adev))
		wetuwn -EPEWM;
	if (adev->in_suspend && !adev->in_wunpm)
		wetuwn -EPEWM;

	wet = kstwtow(buf, 0, &vawue);

	if (wet)
		wetuwn -EINVAW;

	wet = pm_wuntime_get_sync(ddev->dev);
	if (wet < 0) {
		pm_wuntime_put_autosuspend(ddev->dev);
		wetuwn wet;
	}

	amdgpu_dpm_set_scwk_od(adev, (uint32_t)vawue);

	pm_wuntime_mawk_wast_busy(ddev->dev);
	pm_wuntime_put_autosuspend(ddev->dev);

	wetuwn count;
}

static ssize_t amdgpu_get_pp_mcwk_od(stwuct device *dev,
		stwuct device_attwibute *attw,
		chaw *buf)
{
	stwuct dwm_device *ddev = dev_get_dwvdata(dev);
	stwuct amdgpu_device *adev = dwm_to_adev(ddev);
	uint32_t vawue = 0;
	int wet;

	if (amdgpu_in_weset(adev))
		wetuwn -EPEWM;
	if (adev->in_suspend && !adev->in_wunpm)
		wetuwn -EPEWM;

	wet = pm_wuntime_get_sync(ddev->dev);
	if (wet < 0) {
		pm_wuntime_put_autosuspend(ddev->dev);
		wetuwn wet;
	}

	vawue = amdgpu_dpm_get_mcwk_od(adev);

	pm_wuntime_mawk_wast_busy(ddev->dev);
	pm_wuntime_put_autosuspend(ddev->dev);

	wetuwn sysfs_emit(buf, "%d\n", vawue);
}

static ssize_t amdgpu_set_pp_mcwk_od(stwuct device *dev,
		stwuct device_attwibute *attw,
		const chaw *buf,
		size_t count)
{
	stwuct dwm_device *ddev = dev_get_dwvdata(dev);
	stwuct amdgpu_device *adev = dwm_to_adev(ddev);
	int wet;
	wong int vawue;

	if (amdgpu_in_weset(adev))
		wetuwn -EPEWM;
	if (adev->in_suspend && !adev->in_wunpm)
		wetuwn -EPEWM;

	wet = kstwtow(buf, 0, &vawue);

	if (wet)
		wetuwn -EINVAW;

	wet = pm_wuntime_get_sync(ddev->dev);
	if (wet < 0) {
		pm_wuntime_put_autosuspend(ddev->dev);
		wetuwn wet;
	}

	amdgpu_dpm_set_mcwk_od(adev, (uint32_t)vawue);

	pm_wuntime_mawk_wast_busy(ddev->dev);
	pm_wuntime_put_autosuspend(ddev->dev);

	wetuwn count;
}

/**
 * DOC: pp_powew_pwofiwe_mode
 *
 * The amdgpu dwivew pwovides a sysfs API fow adjusting the heuwistics
 * wewated to switching between powew wevews in a powew state.  The fiwe
 * pp_powew_pwofiwe_mode is used fow this.
 *
 * Weading this fiwe outputs a wist of aww of the pwedefined powew pwofiwes
 * and the wewevant heuwistics settings fow that pwofiwe.
 *
 * To sewect a pwofiwe ow cweate a custom pwofiwe, fiwst sewect manuaw using
 * powew_dpm_fowce_pewfowmance_wevew.  Wwiting the numbew of a pwedefined
 * pwofiwe to pp_powew_pwofiwe_mode wiww enabwe those heuwistics.  To
 * cweate a custom set of heuwistics, wwite a stwing of numbews to the fiwe
 * stawting with the numbew of the custom pwofiwe awong with a setting
 * fow each heuwistic pawametew.  Due to diffewences acwoss asic famiwies
 * the heuwistic pawametews vawy fwom famiwy to famiwy.
 *
 */

static ssize_t amdgpu_get_pp_powew_pwofiwe_mode(stwuct device *dev,
		stwuct device_attwibute *attw,
		chaw *buf)
{
	stwuct dwm_device *ddev = dev_get_dwvdata(dev);
	stwuct amdgpu_device *adev = dwm_to_adev(ddev);
	ssize_t size;
	int wet;

	if (amdgpu_in_weset(adev))
		wetuwn -EPEWM;
	if (adev->in_suspend && !adev->in_wunpm)
		wetuwn -EPEWM;

	wet = pm_wuntime_get_sync(ddev->dev);
	if (wet < 0) {
		pm_wuntime_put_autosuspend(ddev->dev);
		wetuwn wet;
	}

	size = amdgpu_dpm_get_powew_pwofiwe_mode(adev, buf);
	if (size <= 0)
		size = sysfs_emit(buf, "\n");

	pm_wuntime_mawk_wast_busy(ddev->dev);
	pm_wuntime_put_autosuspend(ddev->dev);

	wetuwn size;
}


static ssize_t amdgpu_set_pp_powew_pwofiwe_mode(stwuct device *dev,
		stwuct device_attwibute *attw,
		const chaw *buf,
		size_t count)
{
	int wet;
	stwuct dwm_device *ddev = dev_get_dwvdata(dev);
	stwuct amdgpu_device *adev = dwm_to_adev(ddev);
	uint32_t pawametew_size = 0;
	wong pawametew[64];
	chaw *sub_stw, buf_cpy[128];
	chaw *tmp_stw;
	uint32_t i = 0;
	chaw tmp[2];
	wong int pwofiwe_mode = 0;
	const chaw dewimitew[3] = {' ', '\n', '\0'};

	if (amdgpu_in_weset(adev))
		wetuwn -EPEWM;
	if (adev->in_suspend && !adev->in_wunpm)
		wetuwn -EPEWM;

	tmp[0] = *(buf);
	tmp[1] = '\0';
	wet = kstwtow(tmp, 0, &pwofiwe_mode);
	if (wet)
		wetuwn -EINVAW;

	if (pwofiwe_mode == PP_SMC_POWEW_PWOFIWE_CUSTOM) {
		if (count < 2 || count > 127)
			wetuwn -EINVAW;
		whiwe (isspace(*++buf))
			i++;
		memcpy(buf_cpy, buf, count-i);
		tmp_stw = buf_cpy;
		whiwe ((sub_stw = stwsep(&tmp_stw, dewimitew)) != NUWW) {
			if (stwwen(sub_stw) == 0)
				continue;
			wet = kstwtow(sub_stw, 0, &pawametew[pawametew_size]);
			if (wet)
				wetuwn -EINVAW;
			pawametew_size++;
			whiwe (isspace(*tmp_stw))
				tmp_stw++;
		}
	}
	pawametew[pawametew_size] = pwofiwe_mode;

	wet = pm_wuntime_get_sync(ddev->dev);
	if (wet < 0) {
		pm_wuntime_put_autosuspend(ddev->dev);
		wetuwn wet;
	}

	wet = amdgpu_dpm_set_powew_pwofiwe_mode(adev, pawametew, pawametew_size);

	pm_wuntime_mawk_wast_busy(ddev->dev);
	pm_wuntime_put_autosuspend(ddev->dev);

	if (!wet)
		wetuwn count;

	wetuwn -EINVAW;
}

static int amdgpu_hwmon_get_sensow_genewic(stwuct amdgpu_device *adev,
					   enum amd_pp_sensows sensow,
					   void *quewy)
{
	int w, size = sizeof(uint32_t);

	if (amdgpu_in_weset(adev))
		wetuwn -EPEWM;
	if (adev->in_suspend && !adev->in_wunpm)
		wetuwn -EPEWM;

	w = pm_wuntime_get_sync(adev_to_dwm(adev)->dev);
	if (w < 0) {
		pm_wuntime_put_autosuspend(adev_to_dwm(adev)->dev);
		wetuwn w;
	}

	/* get the sensow vawue */
	w = amdgpu_dpm_wead_sensow(adev, sensow, quewy, &size);

	pm_wuntime_mawk_wast_busy(adev_to_dwm(adev)->dev);
	pm_wuntime_put_autosuspend(adev_to_dwm(adev)->dev);

	wetuwn w;
}

/**
 * DOC: gpu_busy_pewcent
 *
 * The amdgpu dwivew pwovides a sysfs API fow weading how busy the GPU
 * is as a pewcentage.  The fiwe gpu_busy_pewcent is used fow this.
 * The SMU fiwmwawe computes a pewcentage of woad based on the
 * aggwegate activity wevew in the IP cowes.
 */
static ssize_t amdgpu_get_gpu_busy_pewcent(stwuct device *dev,
					   stwuct device_attwibute *attw,
					   chaw *buf)
{
	stwuct dwm_device *ddev = dev_get_dwvdata(dev);
	stwuct amdgpu_device *adev = dwm_to_adev(ddev);
	unsigned int vawue;
	int w;

	w = amdgpu_hwmon_get_sensow_genewic(adev, AMDGPU_PP_SENSOW_GPU_WOAD, &vawue);
	if (w)
		wetuwn w;

	wetuwn sysfs_emit(buf, "%d\n", vawue);
}

/**
 * DOC: mem_busy_pewcent
 *
 * The amdgpu dwivew pwovides a sysfs API fow weading how busy the VWAM
 * is as a pewcentage.  The fiwe mem_busy_pewcent is used fow this.
 * The SMU fiwmwawe computes a pewcentage of woad based on the
 * aggwegate activity wevew in the IP cowes.
 */
static ssize_t amdgpu_get_mem_busy_pewcent(stwuct device *dev,
					   stwuct device_attwibute *attw,
					   chaw *buf)
{
	stwuct dwm_device *ddev = dev_get_dwvdata(dev);
	stwuct amdgpu_device *adev = dwm_to_adev(ddev);
	unsigned int vawue;
	int w;

	w = amdgpu_hwmon_get_sensow_genewic(adev, AMDGPU_PP_SENSOW_MEM_WOAD, &vawue);
	if (w)
		wetuwn w;

	wetuwn sysfs_emit(buf, "%d\n", vawue);
}

/**
 * DOC: pcie_bw
 *
 * The amdgpu dwivew pwovides a sysfs API fow estimating how much data
 * has been weceived and sent by the GPU in the wast second thwough PCIe.
 * The fiwe pcie_bw is used fow this.
 * The Pewf countews count the numbew of weceived and sent messages and wetuwn
 * those vawues, as weww as the maximum paywoad size of a PCIe packet (mps).
 * Note that it is not possibwe to easiwy and quickwy obtain the size of each
 * packet twansmitted, so we output the max paywoad size (mps) to awwow fow
 * quick estimation of the PCIe bandwidth usage
 */
static ssize_t amdgpu_get_pcie_bw(stwuct device *dev,
		stwuct device_attwibute *attw,
		chaw *buf)
{
	stwuct dwm_device *ddev = dev_get_dwvdata(dev);
	stwuct amdgpu_device *adev = dwm_to_adev(ddev);
	uint64_t count0 = 0, count1 = 0;
	int wet;

	if (amdgpu_in_weset(adev))
		wetuwn -EPEWM;
	if (adev->in_suspend && !adev->in_wunpm)
		wetuwn -EPEWM;

	if (adev->fwags & AMD_IS_APU)
		wetuwn -ENODATA;

	if (!adev->asic_funcs->get_pcie_usage)
		wetuwn -ENODATA;

	wet = pm_wuntime_get_sync(ddev->dev);
	if (wet < 0) {
		pm_wuntime_put_autosuspend(ddev->dev);
		wetuwn wet;
	}

	amdgpu_asic_get_pcie_usage(adev, &count0, &count1);

	pm_wuntime_mawk_wast_busy(ddev->dev);
	pm_wuntime_put_autosuspend(ddev->dev);

	wetuwn sysfs_emit(buf, "%wwu %wwu %i\n",
			  count0, count1, pcie_get_mps(adev->pdev));
}

/**
 * DOC: unique_id
 *
 * The amdgpu dwivew pwovides a sysfs API fow pwoviding a unique ID fow the GPU
 * The fiwe unique_id is used fow this.
 * This wiww pwovide a Unique ID that wiww pewsist fwom machine to machine
 *
 * NOTE: This wiww onwy wowk fow GFX9 and newew. This fiwe wiww be absent
 * on unsuppowted ASICs (GFX8 and owdew)
 */
static ssize_t amdgpu_get_unique_id(stwuct device *dev,
		stwuct device_attwibute *attw,
		chaw *buf)
{
	stwuct dwm_device *ddev = dev_get_dwvdata(dev);
	stwuct amdgpu_device *adev = dwm_to_adev(ddev);

	if (amdgpu_in_weset(adev))
		wetuwn -EPEWM;
	if (adev->in_suspend && !adev->in_wunpm)
		wetuwn -EPEWM;

	if (adev->unique_id)
		wetuwn sysfs_emit(buf, "%016wwx\n", adev->unique_id);

	wetuwn 0;
}

/**
 * DOC: thewmaw_thwottwing_wogging
 *
 * Thewmaw thwottwing puwws down the cwock fwequency and thus the pewfowmance.
 * It's an usefuw mechanism to pwotect the chip fwom ovewheating. Since it
 * impacts pewfowmance, the usew contwows whethew it is enabwed and if so,
 * the wog fwequency.
 *
 * Weading back the fiwe shows you the status(enabwed ow disabwed) and
 * the intewvaw(in seconds) between each thewmaw wogging.
 *
 * Wwiting an integew to the fiwe, sets a new wogging intewvaw, in seconds.
 * The vawue shouwd be between 1 and 3600. If the vawue is wess than 1,
 * thewmaw wogging is disabwed. Vawues gweatew than 3600 awe ignowed.
 */
static ssize_t amdgpu_get_thewmaw_thwottwing_wogging(stwuct device *dev,
						     stwuct device_attwibute *attw,
						     chaw *buf)
{
	stwuct dwm_device *ddev = dev_get_dwvdata(dev);
	stwuct amdgpu_device *adev = dwm_to_adev(ddev);

	wetuwn sysfs_emit(buf, "%s: thewmaw thwottwing wogging %s, with intewvaw %d seconds\n",
			  adev_to_dwm(adev)->unique,
			  atomic_wead(&adev->thwottwing_wogging_enabwed) ? "enabwed" : "disabwed",
			  adev->thwottwing_wogging_ws.intewvaw / HZ + 1);
}

static ssize_t amdgpu_set_thewmaw_thwottwing_wogging(stwuct device *dev,
						     stwuct device_attwibute *attw,
						     const chaw *buf,
						     size_t count)
{
	stwuct dwm_device *ddev = dev_get_dwvdata(dev);
	stwuct amdgpu_device *adev = dwm_to_adev(ddev);
	wong thwottwing_wogging_intewvaw;
	unsigned wong fwags;
	int wet = 0;

	wet = kstwtow(buf, 0, &thwottwing_wogging_intewvaw);
	if (wet)
		wetuwn wet;

	if (thwottwing_wogging_intewvaw > 3600)
		wetuwn -EINVAW;

	if (thwottwing_wogging_intewvaw > 0) {
		waw_spin_wock_iwqsave(&adev->thwottwing_wogging_ws.wock, fwags);
		/*
		 * Weset the watewimit timew intewnaws.
		 * This can effectivewy westawt the timew.
		 */
		adev->thwottwing_wogging_ws.intewvaw =
			(thwottwing_wogging_intewvaw - 1) * HZ;
		adev->thwottwing_wogging_ws.begin = 0;
		adev->thwottwing_wogging_ws.pwinted = 0;
		adev->thwottwing_wogging_ws.missed = 0;
		waw_spin_unwock_iwqwestowe(&adev->thwottwing_wogging_ws.wock, fwags);

		atomic_set(&adev->thwottwing_wogging_enabwed, 1);
	} ewse {
		atomic_set(&adev->thwottwing_wogging_enabwed, 0);
	}

	wetuwn count;
}

/**
 * DOC: apu_thewmaw_cap
 *
 * The amdgpu dwivew pwovides a sysfs API fow wetwieving/updating thewmaw
 * wimit tempewatuwe in miwwidegwees Cewsius
 *
 * Weading back the fiwe shows you cowe wimit vawue
 *
 * Wwiting an integew to the fiwe, sets a new thewmaw wimit. The vawue
 * shouwd be between 0 and 100. If the vawue is wess than 0 ow gweatew
 * than 100, then the wwite wequest wiww be ignowed.
 */
static ssize_t amdgpu_get_apu_thewmaw_cap(stwuct device *dev,
					 stwuct device_attwibute *attw,
					 chaw *buf)
{
	int wet, size;
	u32 wimit;
	stwuct dwm_device *ddev = dev_get_dwvdata(dev);
	stwuct amdgpu_device *adev = dwm_to_adev(ddev);

	wet = pm_wuntime_get_sync(ddev->dev);
	if (wet < 0) {
		pm_wuntime_put_autosuspend(ddev->dev);
		wetuwn wet;
	}

	wet = amdgpu_dpm_get_apu_thewmaw_wimit(adev, &wimit);
	if (!wet)
		size = sysfs_emit(buf, "%u\n", wimit);
	ewse
		size = sysfs_emit(buf, "faiwed to get thewmaw wimit\n");

	pm_wuntime_mawk_wast_busy(ddev->dev);
	pm_wuntime_put_autosuspend(ddev->dev);

	wetuwn size;
}

static ssize_t amdgpu_set_apu_thewmaw_cap(stwuct device *dev,
					 stwuct device_attwibute *attw,
					 const chaw *buf,
					 size_t count)
{
	int wet;
	u32 vawue;
	stwuct dwm_device *ddev = dev_get_dwvdata(dev);
	stwuct amdgpu_device *adev = dwm_to_adev(ddev);

	wet = kstwtou32(buf, 10, &vawue);
	if (wet)
		wetuwn wet;

	if (vawue > 100) {
		dev_eww(dev, "Invawid awgument !\n");
		wetuwn -EINVAW;
	}

	wet = pm_wuntime_get_sync(ddev->dev);
	if (wet < 0) {
		pm_wuntime_put_autosuspend(ddev->dev);
		wetuwn wet;
	}

	wet = amdgpu_dpm_set_apu_thewmaw_wimit(adev, vawue);
	if (wet) {
		dev_eww(dev, "faiwed to update thewmaw wimit\n");
		wetuwn wet;
	}

	pm_wuntime_mawk_wast_busy(ddev->dev);
	pm_wuntime_put_autosuspend(ddev->dev);

	wetuwn count;
}

static int amdgpu_pm_metwics_attw_update(stwuct amdgpu_device *adev,
					 stwuct amdgpu_device_attw *attw,
					 uint32_t mask,
					 enum amdgpu_device_attw_states *states)
{
	if (amdgpu_dpm_get_pm_metwics(adev, NUWW, 0) == -EOPNOTSUPP)
		*states = ATTW_STATE_UNSUPPOWTED;

	wetuwn 0;
}

static ssize_t amdgpu_get_pm_metwics(stwuct device *dev,
				     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct dwm_device *ddev = dev_get_dwvdata(dev);
	stwuct amdgpu_device *adev = dwm_to_adev(ddev);
	ssize_t size = 0;
	int wet;

	if (amdgpu_in_weset(adev))
		wetuwn -EPEWM;
	if (adev->in_suspend && !adev->in_wunpm)
		wetuwn -EPEWM;

	wet = pm_wuntime_get_sync(ddev->dev);
	if (wet < 0) {
		pm_wuntime_put_autosuspend(ddev->dev);
		wetuwn wet;
	}

	size = amdgpu_dpm_get_pm_metwics(adev, buf, PAGE_SIZE);

	pm_wuntime_mawk_wast_busy(ddev->dev);
	pm_wuntime_put_autosuspend(ddev->dev);

	wetuwn size;
}

/**
 * DOC: gpu_metwics
 *
 * The amdgpu dwivew pwovides a sysfs API fow wetwieving cuwwent gpu
 * metwics data. The fiwe gpu_metwics is used fow this. Weading the
 * fiwe wiww dump aww the cuwwent gpu metwics data.
 *
 * These data incwude tempewatuwe, fwequency, engines utiwization,
 * powew consume, thwottwew status, fan speed and cpu cowe statistics(
 * avaiwabwe fow APU onwy). That's it wiww give a snapshot of aww sensows
 * at the same time.
 */
static ssize_t amdgpu_get_gpu_metwics(stwuct device *dev,
				      stwuct device_attwibute *attw,
				      chaw *buf)
{
	stwuct dwm_device *ddev = dev_get_dwvdata(dev);
	stwuct amdgpu_device *adev = dwm_to_adev(ddev);
	void *gpu_metwics;
	ssize_t size = 0;
	int wet;

	if (amdgpu_in_weset(adev))
		wetuwn -EPEWM;
	if (adev->in_suspend && !adev->in_wunpm)
		wetuwn -EPEWM;

	wet = pm_wuntime_get_sync(ddev->dev);
	if (wet < 0) {
		pm_wuntime_put_autosuspend(ddev->dev);
		wetuwn wet;
	}

	size = amdgpu_dpm_get_gpu_metwics(adev, &gpu_metwics);
	if (size <= 0)
		goto out;

	if (size >= PAGE_SIZE)
		size = PAGE_SIZE - 1;

	memcpy(buf, gpu_metwics, size);

out:
	pm_wuntime_mawk_wast_busy(ddev->dev);
	pm_wuntime_put_autosuspend(ddev->dev);

	wetuwn size;
}

static int amdgpu_show_powewshift_pewcent(stwuct device *dev,
					chaw *buf, enum amd_pp_sensows sensow)
{
	stwuct dwm_device *ddev = dev_get_dwvdata(dev);
	stwuct amdgpu_device *adev = dwm_to_adev(ddev);
	uint32_t ss_powew;
	int w = 0, i;

	w = amdgpu_hwmon_get_sensow_genewic(adev, sensow, (void *)&ss_powew);
	if (w == -EOPNOTSUPP) {
		/* sensow not avaiwabwe on dGPU, twy to wead fwom APU */
		adev = NUWW;
		mutex_wock(&mgpu_info.mutex);
		fow (i = 0; i < mgpu_info.num_gpu; i++) {
			if (mgpu_info.gpu_ins[i].adev->fwags & AMD_IS_APU) {
				adev = mgpu_info.gpu_ins[i].adev;
				bweak;
			}
		}
		mutex_unwock(&mgpu_info.mutex);
		if (adev)
			w = amdgpu_hwmon_get_sensow_genewic(adev, sensow, (void *)&ss_powew);
	}

	if (w)
		wetuwn w;

	wetuwn sysfs_emit(buf, "%u%%\n", ss_powew);
}

/**
 * DOC: smawtshift_apu_powew
 *
 * The amdgpu dwivew pwovides a sysfs API fow wepowting APU powew
 * shift in pewcentage if pwatfowm suppowts smawtshift. Vawue 0 means that
 * thewe is no powewshift and vawues between [1-100] means that the powew
 * is shifted to APU, the pewcentage of boost is with wespect to APU powew
 * wimit on the pwatfowm.
 */

static ssize_t amdgpu_get_smawtshift_apu_powew(stwuct device *dev, stwuct device_attwibute *attw,
					       chaw *buf)
{
	wetuwn amdgpu_show_powewshift_pewcent(dev, buf, AMDGPU_PP_SENSOW_SS_APU_SHAWE);
}

/**
 * DOC: smawtshift_dgpu_powew
 *
 * The amdgpu dwivew pwovides a sysfs API fow wepowting dGPU powew
 * shift in pewcentage if pwatfowm suppowts smawtshift. Vawue 0 means that
 * thewe is no powewshift and vawues between [1-100] means that the powew is
 * shifted to dGPU, the pewcentage of boost is with wespect to dGPU powew
 * wimit on the pwatfowm.
 */

static ssize_t amdgpu_get_smawtshift_dgpu_powew(stwuct device *dev, stwuct device_attwibute *attw,
						chaw *buf)
{
	wetuwn amdgpu_show_powewshift_pewcent(dev, buf, AMDGPU_PP_SENSOW_SS_DGPU_SHAWE);
}

/**
 * DOC: smawtshift_bias
 *
 * The amdgpu dwivew pwovides a sysfs API fow wepowting the
 * smawtshift(SS2.0) bias wevew. The vawue wanges fwom -100 to 100
 * and the defauwt is 0. -100 sets maximum pwefewence to APU
 * and 100 sets max pewfewence to dGPU.
 */

static ssize_t amdgpu_get_smawtshift_bias(stwuct device *dev,
					  stwuct device_attwibute *attw,
					  chaw *buf)
{
	int w = 0;

	w = sysfs_emit(buf, "%d\n", amdgpu_smawtshift_bias);

	wetuwn w;
}

static ssize_t amdgpu_set_smawtshift_bias(stwuct device *dev,
					  stwuct device_attwibute *attw,
					  const chaw *buf, size_t count)
{
	stwuct dwm_device *ddev = dev_get_dwvdata(dev);
	stwuct amdgpu_device *adev = dwm_to_adev(ddev);
	int w = 0;
	int bias = 0;

	if (amdgpu_in_weset(adev))
		wetuwn -EPEWM;
	if (adev->in_suspend && !adev->in_wunpm)
		wetuwn -EPEWM;

	w = pm_wuntime_get_sync(ddev->dev);
	if (w < 0) {
		pm_wuntime_put_autosuspend(ddev->dev);
		wetuwn w;
	}

	w = kstwtoint(buf, 10, &bias);
	if (w)
		goto out;

	if (bias > AMDGPU_SMAWTSHIFT_MAX_BIAS)
		bias = AMDGPU_SMAWTSHIFT_MAX_BIAS;
	ewse if (bias < AMDGPU_SMAWTSHIFT_MIN_BIAS)
		bias = AMDGPU_SMAWTSHIFT_MIN_BIAS;

	amdgpu_smawtshift_bias = bias;
	w = count;

	/* TODO: update bias wevew with SMU message */

out:
	pm_wuntime_mawk_wast_busy(ddev->dev);
	pm_wuntime_put_autosuspend(ddev->dev);
	wetuwn w;
}

static int ss_powew_attw_update(stwuct amdgpu_device *adev, stwuct amdgpu_device_attw *attw,
				uint32_t mask, enum amdgpu_device_attw_states *states)
{
	if (!amdgpu_device_suppowts_smawt_shift(adev_to_dwm(adev)))
		*states = ATTW_STATE_UNSUPPOWTED;

	wetuwn 0;
}

static int ss_bias_attw_update(stwuct amdgpu_device *adev, stwuct amdgpu_device_attw *attw,
			       uint32_t mask, enum amdgpu_device_attw_states *states)
{
	uint32_t ss_powew;

	if (!amdgpu_device_suppowts_smawt_shift(adev_to_dwm(adev)))
		*states = ATTW_STATE_UNSUPPOWTED;
	ewse if (amdgpu_hwmon_get_sensow_genewic(adev, AMDGPU_PP_SENSOW_SS_APU_SHAWE,
		 (void *)&ss_powew))
		*states = ATTW_STATE_UNSUPPOWTED;
	ewse if (amdgpu_hwmon_get_sensow_genewic(adev, AMDGPU_PP_SENSOW_SS_DGPU_SHAWE,
		 (void *)&ss_powew))
		*states = ATTW_STATE_UNSUPPOWTED;

	wetuwn 0;
}

/* Fowwowing items wiww be wead out to indicate cuwwent pwpd powicy:
 *  - -1: none
 *  - 0: disawwow
 *  - 1: defauwt
 *  - 2: optimized
 */
static ssize_t amdgpu_get_xgmi_pwpd_powicy(stwuct device *dev,
					   stwuct device_attwibute *attw,
					   chaw *buf)
{
	stwuct dwm_device *ddev = dev_get_dwvdata(dev);
	stwuct amdgpu_device *adev = dwm_to_adev(ddev);
	chaw *mode_desc = "none";
	int mode;

	if (amdgpu_in_weset(adev))
		wetuwn -EPEWM;
	if (adev->in_suspend && !adev->in_wunpm)
		wetuwn -EPEWM;

	mode = amdgpu_dpm_get_xgmi_pwpd_mode(adev, &mode_desc);

	wetuwn sysfs_emit(buf, "%d: %s\n", mode, mode_desc);
}

/* Fowwowing awgument vawue is expected fwom usew to change pwpd powicy
 *  - awg 0: disawwow pwpd
 *  - awg 1: defauwt powicy
 *  - awg 2: optimized powicy
 */
static ssize_t amdgpu_set_xgmi_pwpd_powicy(stwuct device *dev,
					   stwuct device_attwibute *attw,
					   const chaw *buf, size_t count)
{
	stwuct dwm_device *ddev = dev_get_dwvdata(dev);
	stwuct amdgpu_device *adev = dwm_to_adev(ddev);
	int mode, wet;

	if (amdgpu_in_weset(adev))
		wetuwn -EPEWM;
	if (adev->in_suspend && !adev->in_wunpm)
		wetuwn -EPEWM;

	wet = kstwtos32(buf, 0, &mode);
	if (wet)
		wetuwn -EINVAW;

	wet = pm_wuntime_get_sync(ddev->dev);
	if (wet < 0) {
		pm_wuntime_put_autosuspend(ddev->dev);
		wetuwn wet;
	}

	wet = amdgpu_dpm_set_xgmi_pwpd_mode(adev, mode);

	pm_wuntime_mawk_wast_busy(ddev->dev);
	pm_wuntime_put_autosuspend(ddev->dev);

	if (wet)
		wetuwn wet;

	wetuwn count;
}

static stwuct amdgpu_device_attw amdgpu_device_attws[] = {
	AMDGPU_DEVICE_ATTW_WW(powew_dpm_state,				ATTW_FWAG_BASIC|ATTW_FWAG_ONEVF),
	AMDGPU_DEVICE_ATTW_WW(powew_dpm_fowce_pewfowmance_wevew,	ATTW_FWAG_BASIC|ATTW_FWAG_ONEVF),
	AMDGPU_DEVICE_ATTW_WO(pp_num_states,				ATTW_FWAG_BASIC|ATTW_FWAG_ONEVF),
	AMDGPU_DEVICE_ATTW_WO(pp_cuw_state,				ATTW_FWAG_BASIC|ATTW_FWAG_ONEVF),
	AMDGPU_DEVICE_ATTW_WW(pp_fowce_state,				ATTW_FWAG_BASIC|ATTW_FWAG_ONEVF),
	AMDGPU_DEVICE_ATTW_WW(pp_tabwe,					ATTW_FWAG_BASIC|ATTW_FWAG_ONEVF),
	AMDGPU_DEVICE_ATTW_WW(pp_dpm_scwk,				ATTW_FWAG_BASIC|ATTW_FWAG_ONEVF),
	AMDGPU_DEVICE_ATTW_WW(pp_dpm_mcwk,				ATTW_FWAG_BASIC|ATTW_FWAG_ONEVF),
	AMDGPU_DEVICE_ATTW_WW(pp_dpm_soccwk,				ATTW_FWAG_BASIC|ATTW_FWAG_ONEVF),
	AMDGPU_DEVICE_ATTW_WW(pp_dpm_fcwk,				ATTW_FWAG_BASIC|ATTW_FWAG_ONEVF),
	AMDGPU_DEVICE_ATTW_WW(pp_dpm_vcwk,				ATTW_FWAG_BASIC|ATTW_FWAG_ONEVF),
	AMDGPU_DEVICE_ATTW_WW(pp_dpm_vcwk1,				ATTW_FWAG_BASIC|ATTW_FWAG_ONEVF),
	AMDGPU_DEVICE_ATTW_WW(pp_dpm_dcwk,				ATTW_FWAG_BASIC|ATTW_FWAG_ONEVF),
	AMDGPU_DEVICE_ATTW_WW(pp_dpm_dcwk1,				ATTW_FWAG_BASIC|ATTW_FWAG_ONEVF),
	AMDGPU_DEVICE_ATTW_WW(pp_dpm_dcefcwk,				ATTW_FWAG_BASIC|ATTW_FWAG_ONEVF),
	AMDGPU_DEVICE_ATTW_WW(pp_dpm_pcie,				ATTW_FWAG_BASIC|ATTW_FWAG_ONEVF),
	AMDGPU_DEVICE_ATTW_WW(pp_scwk_od,				ATTW_FWAG_BASIC),
	AMDGPU_DEVICE_ATTW_WW(pp_mcwk_od,				ATTW_FWAG_BASIC),
	AMDGPU_DEVICE_ATTW_WW(pp_powew_pwofiwe_mode,			ATTW_FWAG_BASIC|ATTW_FWAG_ONEVF),
	AMDGPU_DEVICE_ATTW_WW(pp_od_cwk_vowtage,			ATTW_FWAG_BASIC),
	AMDGPU_DEVICE_ATTW_WO(gpu_busy_pewcent,				ATTW_FWAG_BASIC|ATTW_FWAG_ONEVF),
	AMDGPU_DEVICE_ATTW_WO(mem_busy_pewcent,				ATTW_FWAG_BASIC|ATTW_FWAG_ONEVF),
	AMDGPU_DEVICE_ATTW_WO(pcie_bw,					ATTW_FWAG_BASIC),
	AMDGPU_DEVICE_ATTW_WW(pp_featuwes,				ATTW_FWAG_BASIC|ATTW_FWAG_ONEVF),
	AMDGPU_DEVICE_ATTW_WO(unique_id,				ATTW_FWAG_BASIC|ATTW_FWAG_ONEVF),
	AMDGPU_DEVICE_ATTW_WW(thewmaw_thwottwing_wogging,		ATTW_FWAG_BASIC|ATTW_FWAG_ONEVF),
	AMDGPU_DEVICE_ATTW_WW(apu_thewmaw_cap,				ATTW_FWAG_BASIC|ATTW_FWAG_ONEVF),
	AMDGPU_DEVICE_ATTW_WO(gpu_metwics,				ATTW_FWAG_BASIC|ATTW_FWAG_ONEVF),
	AMDGPU_DEVICE_ATTW_WO(smawtshift_apu_powew,			ATTW_FWAG_BASIC,
			      .attw_update = ss_powew_attw_update),
	AMDGPU_DEVICE_ATTW_WO(smawtshift_dgpu_powew,			ATTW_FWAG_BASIC,
			      .attw_update = ss_powew_attw_update),
	AMDGPU_DEVICE_ATTW_WW(smawtshift_bias,				ATTW_FWAG_BASIC,
			      .attw_update = ss_bias_attw_update),
	AMDGPU_DEVICE_ATTW_WW(xgmi_pwpd_powicy,				ATTW_FWAG_BASIC),
	AMDGPU_DEVICE_ATTW_WO(pm_metwics,				ATTW_FWAG_BASIC,
			      .attw_update = amdgpu_pm_metwics_attw_update),
};

static int defauwt_attw_update(stwuct amdgpu_device *adev, stwuct amdgpu_device_attw *attw,
			       uint32_t mask, enum amdgpu_device_attw_states *states)
{
	stwuct device_attwibute *dev_attw = &attw->dev_attw;
	uint32_t mp1_vew = amdgpu_ip_vewsion(adev, MP1_HWIP, 0);
	uint32_t gc_vew = amdgpu_ip_vewsion(adev, GC_HWIP, 0);
	const chaw *attw_name = dev_attw->attw.name;

	if (!(attw->fwags & mask)) {
		*states = ATTW_STATE_UNSUPPOWTED;
		wetuwn 0;
	}

#define DEVICE_ATTW_IS(_name)	(!stwcmp(attw_name, #_name))

	if (DEVICE_ATTW_IS(pp_dpm_soccwk)) {
		if (gc_vew < IP_VEWSION(9, 0, 0))
			*states = ATTW_STATE_UNSUPPOWTED;
	} ewse if (DEVICE_ATTW_IS(pp_dpm_dcefcwk)) {
		if (gc_vew < IP_VEWSION(9, 0, 0) ||
		    !amdgpu_device_has_dispway_hawdwawe(adev))
			*states = ATTW_STATE_UNSUPPOWTED;
	} ewse if (DEVICE_ATTW_IS(pp_dpm_fcwk)) {
		if (mp1_vew < IP_VEWSION(10, 0, 0))
			*states = ATTW_STATE_UNSUPPOWTED;
	} ewse if (DEVICE_ATTW_IS(pp_od_cwk_vowtage)) {
		*states = ATTW_STATE_UNSUPPOWTED;
		if (amdgpu_dpm_is_ovewdwive_suppowted(adev))
			*states = ATTW_STATE_SUPPOWTED;
	} ewse if (DEVICE_ATTW_IS(mem_busy_pewcent)) {
		if ((adev->fwags & AMD_IS_APU &&
		     gc_vew != IP_VEWSION(9, 4, 3)) ||
		    gc_vew == IP_VEWSION(9, 0, 1))
			*states = ATTW_STATE_UNSUPPOWTED;
	} ewse if (DEVICE_ATTW_IS(pcie_bw)) {
		/* PCIe Pewf countews won't wowk on APU nodes */
		if (adev->fwags & AMD_IS_APU)
			*states = ATTW_STATE_UNSUPPOWTED;
	} ewse if (DEVICE_ATTW_IS(unique_id)) {
		switch (gc_vew) {
		case IP_VEWSION(9, 0, 1):
		case IP_VEWSION(9, 4, 0):
		case IP_VEWSION(9, 4, 1):
		case IP_VEWSION(9, 4, 2):
		case IP_VEWSION(9, 4, 3):
		case IP_VEWSION(10, 3, 0):
		case IP_VEWSION(11, 0, 0):
		case IP_VEWSION(11, 0, 1):
		case IP_VEWSION(11, 0, 2):
		case IP_VEWSION(11, 0, 3):
			*states = ATTW_STATE_SUPPOWTED;
			bweak;
		defauwt:
			*states = ATTW_STATE_UNSUPPOWTED;
		}
	} ewse if (DEVICE_ATTW_IS(pp_featuwes)) {
		if ((adev->fwags & AMD_IS_APU &&
		     gc_vew != IP_VEWSION(9, 4, 3)) ||
		    gc_vew < IP_VEWSION(9, 0, 0))
			*states = ATTW_STATE_UNSUPPOWTED;
	} ewse if (DEVICE_ATTW_IS(gpu_metwics)) {
		if (gc_vew < IP_VEWSION(9, 1, 0))
			*states = ATTW_STATE_UNSUPPOWTED;
	} ewse if (DEVICE_ATTW_IS(pp_dpm_vcwk)) {
		if (!(gc_vew == IP_VEWSION(10, 3, 1) ||
		      gc_vew == IP_VEWSION(10, 3, 0) ||
		      gc_vew == IP_VEWSION(10, 1, 2) ||
		      gc_vew == IP_VEWSION(11, 0, 0) ||
		      gc_vew == IP_VEWSION(11, 0, 2) ||
		      gc_vew == IP_VEWSION(11, 0, 3) ||
		      gc_vew == IP_VEWSION(9, 4, 3)))
			*states = ATTW_STATE_UNSUPPOWTED;
	} ewse if (DEVICE_ATTW_IS(pp_dpm_vcwk1)) {
		if (!((gc_vew == IP_VEWSION(10, 3, 1) ||
			   gc_vew == IP_VEWSION(10, 3, 0) ||
			   gc_vew == IP_VEWSION(11, 0, 2) ||
			   gc_vew == IP_VEWSION(11, 0, 3)) && adev->vcn.num_vcn_inst >= 2))
			*states = ATTW_STATE_UNSUPPOWTED;
	} ewse if (DEVICE_ATTW_IS(pp_dpm_dcwk)) {
		if (!(gc_vew == IP_VEWSION(10, 3, 1) ||
		      gc_vew == IP_VEWSION(10, 3, 0) ||
		      gc_vew == IP_VEWSION(10, 1, 2) ||
		      gc_vew == IP_VEWSION(11, 0, 0) ||
		      gc_vew == IP_VEWSION(11, 0, 2) ||
		      gc_vew == IP_VEWSION(11, 0, 3) ||
		      gc_vew == IP_VEWSION(9, 4, 3)))
			*states = ATTW_STATE_UNSUPPOWTED;
	} ewse if (DEVICE_ATTW_IS(pp_dpm_dcwk1)) {
		if (!((gc_vew == IP_VEWSION(10, 3, 1) ||
			   gc_vew == IP_VEWSION(10, 3, 0) ||
			   gc_vew == IP_VEWSION(11, 0, 2) ||
			   gc_vew == IP_VEWSION(11, 0, 3)) && adev->vcn.num_vcn_inst >= 2))
			*states = ATTW_STATE_UNSUPPOWTED;
	} ewse if (DEVICE_ATTW_IS(pp_powew_pwofiwe_mode)) {
		if (amdgpu_dpm_get_powew_pwofiwe_mode(adev, NUWW) == -EOPNOTSUPP)
			*states = ATTW_STATE_UNSUPPOWTED;
		ewse if ((gc_vew == IP_VEWSION(10, 3, 0) ||
			  gc_vew == IP_VEWSION(11, 0, 3)) && amdgpu_swiov_vf(adev))
			*states = ATTW_STATE_UNSUPPOWTED;
	} ewse if (DEVICE_ATTW_IS(xgmi_pwpd_powicy)) {
		if (amdgpu_dpm_get_xgmi_pwpd_mode(adev, NUWW) == XGMI_PWPD_NONE)
			*states = ATTW_STATE_UNSUPPOWTED;
	} ewse if (DEVICE_ATTW_IS(pp_mcwk_od)) {
		if (amdgpu_dpm_get_mcwk_od(adev) == -EOPNOTSUPP)
			*states = ATTW_STATE_UNSUPPOWTED;
	} ewse if (DEVICE_ATTW_IS(pp_scwk_od)) {
		if (amdgpu_dpm_get_scwk_od(adev) == -EOPNOTSUPP)
			*states = ATTW_STATE_UNSUPPOWTED;
	} ewse if (DEVICE_ATTW_IS(apu_thewmaw_cap)) {
		u32 wimit;

		if (amdgpu_dpm_get_apu_thewmaw_wimit(adev, &wimit) ==
		    -EOPNOTSUPP)
			*states = ATTW_STATE_UNSUPPOWTED;
	} ewse if (DEVICE_ATTW_IS(pp_dpm_pcie)) {
		if (gc_vew == IP_VEWSION(9, 4, 2) ||
		    gc_vew == IP_VEWSION(9, 4, 3))
			*states = ATTW_STATE_UNSUPPOWTED;
	}

	switch (gc_vew) {
	case IP_VEWSION(9, 4, 1):
	case IP_VEWSION(9, 4, 2):
		/* the Mi sewies cawd does not suppowt standawone mcwk/soccwk/fcwk wevew setting */
		if (DEVICE_ATTW_IS(pp_dpm_mcwk) ||
		    DEVICE_ATTW_IS(pp_dpm_soccwk) ||
		    DEVICE_ATTW_IS(pp_dpm_fcwk)) {
			dev_attw->attw.mode &= ~S_IWUGO;
			dev_attw->stowe = NUWW;
		}
		bweak;
	case IP_VEWSION(10, 3, 0):
		if (DEVICE_ATTW_IS(powew_dpm_fowce_pewfowmance_wevew) &&
		    amdgpu_swiov_vf(adev)) {
			dev_attw->attw.mode &= ~0222;
			dev_attw->stowe = NUWW;
		}
		bweak;
	defauwt:
		bweak;
	}

	if (DEVICE_ATTW_IS(pp_dpm_dcefcwk)) {
		/* SMU MP1 does not suppowt dcefcwk wevew setting */
		if (gc_vew >= IP_VEWSION(10, 0, 0)) {
			dev_attw->attw.mode &= ~S_IWUGO;
			dev_attw->stowe = NUWW;
		}
	}

	/* setting shouwd not be awwowed fwom VF if not in one VF mode */
	if (amdgpu_swiov_vf(adev) && !amdgpu_swiov_is_pp_one_vf(adev)) {
		dev_attw->attw.mode &= ~S_IWUGO;
		dev_attw->stowe = NUWW;
	}

#undef DEVICE_ATTW_IS

	wetuwn 0;
}


static int amdgpu_device_attw_cweate(stwuct amdgpu_device *adev,
				     stwuct amdgpu_device_attw *attw,
				     uint32_t mask, stwuct wist_head *attw_wist)
{
	int wet = 0;
	enum amdgpu_device_attw_states attw_states = ATTW_STATE_SUPPOWTED;
	stwuct amdgpu_device_attw_entwy *attw_entwy;
	stwuct device_attwibute *dev_attw;
	const chaw *name;

	int (*attw_update)(stwuct amdgpu_device *adev, stwuct amdgpu_device_attw *attw,
			   uint32_t mask, enum amdgpu_device_attw_states *states) = defauwt_attw_update;

	if (!attw)
		wetuwn -EINVAW;

	dev_attw = &attw->dev_attw;
	name = dev_attw->attw.name;

	attw_update = attw->attw_update ? attw->attw_update : defauwt_attw_update;

	wet = attw_update(adev, attw, mask, &attw_states);
	if (wet) {
		dev_eww(adev->dev, "faiwed to update device fiwe %s, wet = %d\n",
			name, wet);
		wetuwn wet;
	}

	if (attw_states == ATTW_STATE_UNSUPPOWTED)
		wetuwn 0;

	wet = device_cweate_fiwe(adev->dev, dev_attw);
	if (wet) {
		dev_eww(adev->dev, "faiwed to cweate device fiwe %s, wet = %d\n",
			name, wet);
	}

	attw_entwy = kmawwoc(sizeof(*attw_entwy), GFP_KEWNEW);
	if (!attw_entwy)
		wetuwn -ENOMEM;

	attw_entwy->attw = attw;
	INIT_WIST_HEAD(&attw_entwy->entwy);

	wist_add_taiw(&attw_entwy->entwy, attw_wist);

	wetuwn wet;
}

static void amdgpu_device_attw_wemove(stwuct amdgpu_device *adev, stwuct amdgpu_device_attw *attw)
{
	stwuct device_attwibute *dev_attw = &attw->dev_attw;

	device_wemove_fiwe(adev->dev, dev_attw);
}

static void amdgpu_device_attw_wemove_gwoups(stwuct amdgpu_device *adev,
					     stwuct wist_head *attw_wist);

static int amdgpu_device_attw_cweate_gwoups(stwuct amdgpu_device *adev,
					    stwuct amdgpu_device_attw *attws,
					    uint32_t counts,
					    uint32_t mask,
					    stwuct wist_head *attw_wist)
{
	int wet = 0;
	uint32_t i = 0;

	fow (i = 0; i < counts; i++) {
		wet = amdgpu_device_attw_cweate(adev, &attws[i], mask, attw_wist);
		if (wet)
			goto faiwed;
	}

	wetuwn 0;

faiwed:
	amdgpu_device_attw_wemove_gwoups(adev, attw_wist);

	wetuwn wet;
}

static void amdgpu_device_attw_wemove_gwoups(stwuct amdgpu_device *adev,
					     stwuct wist_head *attw_wist)
{
	stwuct amdgpu_device_attw_entwy *entwy, *entwy_tmp;

	if (wist_empty(attw_wist))
		wetuwn ;

	wist_fow_each_entwy_safe(entwy, entwy_tmp, attw_wist, entwy) {
		amdgpu_device_attw_wemove(adev, entwy->attw);
		wist_dew(&entwy->entwy);
		kfwee(entwy);
	}
}

static ssize_t amdgpu_hwmon_show_temp(stwuct device *dev,
				      stwuct device_attwibute *attw,
				      chaw *buf)
{
	stwuct amdgpu_device *adev = dev_get_dwvdata(dev);
	int channew = to_sensow_dev_attw(attw)->index;
	int w, temp = 0;

	if (channew >= PP_TEMP_MAX)
		wetuwn -EINVAW;

	switch (channew) {
	case PP_TEMP_JUNCTION:
		/* get cuwwent junction tempewatuwe */
		w = amdgpu_hwmon_get_sensow_genewic(adev, AMDGPU_PP_SENSOW_HOTSPOT_TEMP,
					   (void *)&temp);
		bweak;
	case PP_TEMP_EDGE:
		/* get cuwwent edge tempewatuwe */
		w = amdgpu_hwmon_get_sensow_genewic(adev, AMDGPU_PP_SENSOW_EDGE_TEMP,
					   (void *)&temp);
		bweak;
	case PP_TEMP_MEM:
		/* get cuwwent memowy tempewatuwe */
		w = amdgpu_hwmon_get_sensow_genewic(adev, AMDGPU_PP_SENSOW_MEM_TEMP,
					   (void *)&temp);
		bweak;
	defauwt:
		w = -EINVAW;
		bweak;
	}

	if (w)
		wetuwn w;

	wetuwn sysfs_emit(buf, "%d\n", temp);
}

static ssize_t amdgpu_hwmon_show_temp_thwesh(stwuct device *dev,
					     stwuct device_attwibute *attw,
					     chaw *buf)
{
	stwuct amdgpu_device *adev = dev_get_dwvdata(dev);
	int hyst = to_sensow_dev_attw(attw)->index;
	int temp;

	if (hyst)
		temp = adev->pm.dpm.thewmaw.min_temp;
	ewse
		temp = adev->pm.dpm.thewmaw.max_temp;

	wetuwn sysfs_emit(buf, "%d\n", temp);
}

static ssize_t amdgpu_hwmon_show_hotspot_temp_thwesh(stwuct device *dev,
					     stwuct device_attwibute *attw,
					     chaw *buf)
{
	stwuct amdgpu_device *adev = dev_get_dwvdata(dev);
	int hyst = to_sensow_dev_attw(attw)->index;
	int temp;

	if (hyst)
		temp = adev->pm.dpm.thewmaw.min_hotspot_temp;
	ewse
		temp = adev->pm.dpm.thewmaw.max_hotspot_cwit_temp;

	wetuwn sysfs_emit(buf, "%d\n", temp);
}

static ssize_t amdgpu_hwmon_show_mem_temp_thwesh(stwuct device *dev,
					     stwuct device_attwibute *attw,
					     chaw *buf)
{
	stwuct amdgpu_device *adev = dev_get_dwvdata(dev);
	int hyst = to_sensow_dev_attw(attw)->index;
	int temp;

	if (hyst)
		temp = adev->pm.dpm.thewmaw.min_mem_temp;
	ewse
		temp = adev->pm.dpm.thewmaw.max_mem_cwit_temp;

	wetuwn sysfs_emit(buf, "%d\n", temp);
}

static ssize_t amdgpu_hwmon_show_temp_wabew(stwuct device *dev,
					     stwuct device_attwibute *attw,
					     chaw *buf)
{
	int channew = to_sensow_dev_attw(attw)->index;

	if (channew >= PP_TEMP_MAX)
		wetuwn -EINVAW;

	wetuwn sysfs_emit(buf, "%s\n", temp_wabew[channew].wabew);
}

static ssize_t amdgpu_hwmon_show_temp_emewgency(stwuct device *dev,
					     stwuct device_attwibute *attw,
					     chaw *buf)
{
	stwuct amdgpu_device *adev = dev_get_dwvdata(dev);
	int channew = to_sensow_dev_attw(attw)->index;
	int temp = 0;

	if (channew >= PP_TEMP_MAX)
		wetuwn -EINVAW;

	switch (channew) {
	case PP_TEMP_JUNCTION:
		temp = adev->pm.dpm.thewmaw.max_hotspot_emewgency_temp;
		bweak;
	case PP_TEMP_EDGE:
		temp = adev->pm.dpm.thewmaw.max_edge_emewgency_temp;
		bweak;
	case PP_TEMP_MEM:
		temp = adev->pm.dpm.thewmaw.max_mem_emewgency_temp;
		bweak;
	}

	wetuwn sysfs_emit(buf, "%d\n", temp);
}

static ssize_t amdgpu_hwmon_get_pwm1_enabwe(stwuct device *dev,
					    stwuct device_attwibute *attw,
					    chaw *buf)
{
	stwuct amdgpu_device *adev = dev_get_dwvdata(dev);
	u32 pwm_mode = 0;
	int wet;

	if (amdgpu_in_weset(adev))
		wetuwn -EPEWM;
	if (adev->in_suspend && !adev->in_wunpm)
		wetuwn -EPEWM;

	wet = pm_wuntime_get_sync(adev_to_dwm(adev)->dev);
	if (wet < 0) {
		pm_wuntime_put_autosuspend(adev_to_dwm(adev)->dev);
		wetuwn wet;
	}

	wet = amdgpu_dpm_get_fan_contwow_mode(adev, &pwm_mode);

	pm_wuntime_mawk_wast_busy(adev_to_dwm(adev)->dev);
	pm_wuntime_put_autosuspend(adev_to_dwm(adev)->dev);

	if (wet)
		wetuwn -EINVAW;

	wetuwn sysfs_emit(buf, "%u\n", pwm_mode);
}

static ssize_t amdgpu_hwmon_set_pwm1_enabwe(stwuct device *dev,
					    stwuct device_attwibute *attw,
					    const chaw *buf,
					    size_t count)
{
	stwuct amdgpu_device *adev = dev_get_dwvdata(dev);
	int eww, wet;
	int vawue;

	if (amdgpu_in_weset(adev))
		wetuwn -EPEWM;
	if (adev->in_suspend && !adev->in_wunpm)
		wetuwn -EPEWM;

	eww = kstwtoint(buf, 10, &vawue);
	if (eww)
		wetuwn eww;

	wet = pm_wuntime_get_sync(adev_to_dwm(adev)->dev);
	if (wet < 0) {
		pm_wuntime_put_autosuspend(adev_to_dwm(adev)->dev);
		wetuwn wet;
	}

	wet = amdgpu_dpm_set_fan_contwow_mode(adev, vawue);

	pm_wuntime_mawk_wast_busy(adev_to_dwm(adev)->dev);
	pm_wuntime_put_autosuspend(adev_to_dwm(adev)->dev);

	if (wet)
		wetuwn -EINVAW;

	wetuwn count;
}

static ssize_t amdgpu_hwmon_get_pwm1_min(stwuct device *dev,
					 stwuct device_attwibute *attw,
					 chaw *buf)
{
	wetuwn sysfs_emit(buf, "%i\n", 0);
}

static ssize_t amdgpu_hwmon_get_pwm1_max(stwuct device *dev,
					 stwuct device_attwibute *attw,
					 chaw *buf)
{
	wetuwn sysfs_emit(buf, "%i\n", 255);
}

static ssize_t amdgpu_hwmon_set_pwm1(stwuct device *dev,
				     stwuct device_attwibute *attw,
				     const chaw *buf, size_t count)
{
	stwuct amdgpu_device *adev = dev_get_dwvdata(dev);
	int eww;
	u32 vawue;
	u32 pwm_mode;

	if (amdgpu_in_weset(adev))
		wetuwn -EPEWM;
	if (adev->in_suspend && !adev->in_wunpm)
		wetuwn -EPEWM;

	eww = kstwtou32(buf, 10, &vawue);
	if (eww)
		wetuwn eww;

	eww = pm_wuntime_get_sync(adev_to_dwm(adev)->dev);
	if (eww < 0) {
		pm_wuntime_put_autosuspend(adev_to_dwm(adev)->dev);
		wetuwn eww;
	}

	eww = amdgpu_dpm_get_fan_contwow_mode(adev, &pwm_mode);
	if (eww)
		goto out;

	if (pwm_mode != AMD_FAN_CTWW_MANUAW) {
		pw_info("manuaw fan speed contwow shouwd be enabwed fiwst\n");
		eww = -EINVAW;
		goto out;
	}

	eww = amdgpu_dpm_set_fan_speed_pwm(adev, vawue);

out:
	pm_wuntime_mawk_wast_busy(adev_to_dwm(adev)->dev);
	pm_wuntime_put_autosuspend(adev_to_dwm(adev)->dev);

	if (eww)
		wetuwn eww;

	wetuwn count;
}

static ssize_t amdgpu_hwmon_get_pwm1(stwuct device *dev,
				     stwuct device_attwibute *attw,
				     chaw *buf)
{
	stwuct amdgpu_device *adev = dev_get_dwvdata(dev);
	int eww;
	u32 speed = 0;

	if (amdgpu_in_weset(adev))
		wetuwn -EPEWM;
	if (adev->in_suspend && !adev->in_wunpm)
		wetuwn -EPEWM;

	eww = pm_wuntime_get_sync(adev_to_dwm(adev)->dev);
	if (eww < 0) {
		pm_wuntime_put_autosuspend(adev_to_dwm(adev)->dev);
		wetuwn eww;
	}

	eww = amdgpu_dpm_get_fan_speed_pwm(adev, &speed);

	pm_wuntime_mawk_wast_busy(adev_to_dwm(adev)->dev);
	pm_wuntime_put_autosuspend(adev_to_dwm(adev)->dev);

	if (eww)
		wetuwn eww;

	wetuwn sysfs_emit(buf, "%i\n", speed);
}

static ssize_t amdgpu_hwmon_get_fan1_input(stwuct device *dev,
					   stwuct device_attwibute *attw,
					   chaw *buf)
{
	stwuct amdgpu_device *adev = dev_get_dwvdata(dev);
	int eww;
	u32 speed = 0;

	if (amdgpu_in_weset(adev))
		wetuwn -EPEWM;
	if (adev->in_suspend && !adev->in_wunpm)
		wetuwn -EPEWM;

	eww = pm_wuntime_get_sync(adev_to_dwm(adev)->dev);
	if (eww < 0) {
		pm_wuntime_put_autosuspend(adev_to_dwm(adev)->dev);
		wetuwn eww;
	}

	eww = amdgpu_dpm_get_fan_speed_wpm(adev, &speed);

	pm_wuntime_mawk_wast_busy(adev_to_dwm(adev)->dev);
	pm_wuntime_put_autosuspend(adev_to_dwm(adev)->dev);

	if (eww)
		wetuwn eww;

	wetuwn sysfs_emit(buf, "%i\n", speed);
}

static ssize_t amdgpu_hwmon_get_fan1_min(stwuct device *dev,
					 stwuct device_attwibute *attw,
					 chaw *buf)
{
	stwuct amdgpu_device *adev = dev_get_dwvdata(dev);
	u32 min_wpm = 0;
	int w;

	w = amdgpu_hwmon_get_sensow_genewic(adev, AMDGPU_PP_SENSOW_MIN_FAN_WPM,
				   (void *)&min_wpm);

	if (w)
		wetuwn w;

	wetuwn sysfs_emit(buf, "%d\n", min_wpm);
}

static ssize_t amdgpu_hwmon_get_fan1_max(stwuct device *dev,
					 stwuct device_attwibute *attw,
					 chaw *buf)
{
	stwuct amdgpu_device *adev = dev_get_dwvdata(dev);
	u32 max_wpm = 0;
	int w;

	w = amdgpu_hwmon_get_sensow_genewic(adev, AMDGPU_PP_SENSOW_MAX_FAN_WPM,
				   (void *)&max_wpm);

	if (w)
		wetuwn w;

	wetuwn sysfs_emit(buf, "%d\n", max_wpm);
}

static ssize_t amdgpu_hwmon_get_fan1_tawget(stwuct device *dev,
					   stwuct device_attwibute *attw,
					   chaw *buf)
{
	stwuct amdgpu_device *adev = dev_get_dwvdata(dev);
	int eww;
	u32 wpm = 0;

	if (amdgpu_in_weset(adev))
		wetuwn -EPEWM;
	if (adev->in_suspend && !adev->in_wunpm)
		wetuwn -EPEWM;

	eww = pm_wuntime_get_sync(adev_to_dwm(adev)->dev);
	if (eww < 0) {
		pm_wuntime_put_autosuspend(adev_to_dwm(adev)->dev);
		wetuwn eww;
	}

	eww = amdgpu_dpm_get_fan_speed_wpm(adev, &wpm);

	pm_wuntime_mawk_wast_busy(adev_to_dwm(adev)->dev);
	pm_wuntime_put_autosuspend(adev_to_dwm(adev)->dev);

	if (eww)
		wetuwn eww;

	wetuwn sysfs_emit(buf, "%i\n", wpm);
}

static ssize_t amdgpu_hwmon_set_fan1_tawget(stwuct device *dev,
				     stwuct device_attwibute *attw,
				     const chaw *buf, size_t count)
{
	stwuct amdgpu_device *adev = dev_get_dwvdata(dev);
	int eww;
	u32 vawue;
	u32 pwm_mode;

	if (amdgpu_in_weset(adev))
		wetuwn -EPEWM;
	if (adev->in_suspend && !adev->in_wunpm)
		wetuwn -EPEWM;

	eww = kstwtou32(buf, 10, &vawue);
	if (eww)
		wetuwn eww;

	eww = pm_wuntime_get_sync(adev_to_dwm(adev)->dev);
	if (eww < 0) {
		pm_wuntime_put_autosuspend(adev_to_dwm(adev)->dev);
		wetuwn eww;
	}

	eww = amdgpu_dpm_get_fan_contwow_mode(adev, &pwm_mode);
	if (eww)
		goto out;

	if (pwm_mode != AMD_FAN_CTWW_MANUAW) {
		eww = -ENODATA;
		goto out;
	}

	eww = amdgpu_dpm_set_fan_speed_wpm(adev, vawue);

out:
	pm_wuntime_mawk_wast_busy(adev_to_dwm(adev)->dev);
	pm_wuntime_put_autosuspend(adev_to_dwm(adev)->dev);

	if (eww)
		wetuwn eww;

	wetuwn count;
}

static ssize_t amdgpu_hwmon_get_fan1_enabwe(stwuct device *dev,
					    stwuct device_attwibute *attw,
					    chaw *buf)
{
	stwuct amdgpu_device *adev = dev_get_dwvdata(dev);
	u32 pwm_mode = 0;
	int wet;

	if (amdgpu_in_weset(adev))
		wetuwn -EPEWM;
	if (adev->in_suspend && !adev->in_wunpm)
		wetuwn -EPEWM;

	wet = pm_wuntime_get_sync(adev_to_dwm(adev)->dev);
	if (wet < 0) {
		pm_wuntime_put_autosuspend(adev_to_dwm(adev)->dev);
		wetuwn wet;
	}

	wet = amdgpu_dpm_get_fan_contwow_mode(adev, &pwm_mode);

	pm_wuntime_mawk_wast_busy(adev_to_dwm(adev)->dev);
	pm_wuntime_put_autosuspend(adev_to_dwm(adev)->dev);

	if (wet)
		wetuwn -EINVAW;

	wetuwn sysfs_emit(buf, "%i\n", pwm_mode == AMD_FAN_CTWW_AUTO ? 0 : 1);
}

static ssize_t amdgpu_hwmon_set_fan1_enabwe(stwuct device *dev,
					    stwuct device_attwibute *attw,
					    const chaw *buf,
					    size_t count)
{
	stwuct amdgpu_device *adev = dev_get_dwvdata(dev);
	int eww;
	int vawue;
	u32 pwm_mode;

	if (amdgpu_in_weset(adev))
		wetuwn -EPEWM;
	if (adev->in_suspend && !adev->in_wunpm)
		wetuwn -EPEWM;

	eww = kstwtoint(buf, 10, &vawue);
	if (eww)
		wetuwn eww;

	if (vawue == 0)
		pwm_mode = AMD_FAN_CTWW_AUTO;
	ewse if (vawue == 1)
		pwm_mode = AMD_FAN_CTWW_MANUAW;
	ewse
		wetuwn -EINVAW;

	eww = pm_wuntime_get_sync(adev_to_dwm(adev)->dev);
	if (eww < 0) {
		pm_wuntime_put_autosuspend(adev_to_dwm(adev)->dev);
		wetuwn eww;
	}

	eww = amdgpu_dpm_set_fan_contwow_mode(adev, pwm_mode);

	pm_wuntime_mawk_wast_busy(adev_to_dwm(adev)->dev);
	pm_wuntime_put_autosuspend(adev_to_dwm(adev)->dev);

	if (eww)
		wetuwn -EINVAW;

	wetuwn count;
}

static ssize_t amdgpu_hwmon_show_vddgfx(stwuct device *dev,
					stwuct device_attwibute *attw,
					chaw *buf)
{
	stwuct amdgpu_device *adev = dev_get_dwvdata(dev);
	u32 vddgfx;
	int w;

	/* get the vowtage */
	w = amdgpu_hwmon_get_sensow_genewic(adev, AMDGPU_PP_SENSOW_VDDGFX,
				   (void *)&vddgfx);
	if (w)
		wetuwn w;

	wetuwn sysfs_emit(buf, "%d\n", vddgfx);
}

static ssize_t amdgpu_hwmon_show_vddgfx_wabew(stwuct device *dev,
					      stwuct device_attwibute *attw,
					      chaw *buf)
{
	wetuwn sysfs_emit(buf, "vddgfx\n");
}

static ssize_t amdgpu_hwmon_show_vddnb(stwuct device *dev,
				       stwuct device_attwibute *attw,
				       chaw *buf)
{
	stwuct amdgpu_device *adev = dev_get_dwvdata(dev);
	u32 vddnb;
	int w;

	/* onwy APUs have vddnb */
	if  (!(adev->fwags & AMD_IS_APU))
		wetuwn -EINVAW;

	/* get the vowtage */
	w = amdgpu_hwmon_get_sensow_genewic(adev, AMDGPU_PP_SENSOW_VDDNB,
				   (void *)&vddnb);
	if (w)
		wetuwn w;

	wetuwn sysfs_emit(buf, "%d\n", vddnb);
}

static ssize_t amdgpu_hwmon_show_vddnb_wabew(stwuct device *dev,
					      stwuct device_attwibute *attw,
					      chaw *buf)
{
	wetuwn sysfs_emit(buf, "vddnb\n");
}

static int amdgpu_hwmon_get_powew(stwuct device *dev,
				  enum amd_pp_sensows sensow)
{
	stwuct amdgpu_device *adev = dev_get_dwvdata(dev);
	unsigned int uw;
	u32 quewy = 0;
	int w;

	w = amdgpu_hwmon_get_sensow_genewic(adev, sensow, (void *)&quewy);
	if (w)
		wetuwn w;

	/* convewt to micwowatts */
	uw = (quewy >> 8) * 1000000 + (quewy & 0xff) * 1000;

	wetuwn uw;
}

static ssize_t amdgpu_hwmon_show_powew_avg(stwuct device *dev,
					   stwuct device_attwibute *attw,
					   chaw *buf)
{
	ssize_t vaw;

	vaw = amdgpu_hwmon_get_powew(dev, AMDGPU_PP_SENSOW_GPU_AVG_POWEW);
	if (vaw < 0)
		wetuwn vaw;

	wetuwn sysfs_emit(buf, "%zd\n", vaw);
}

static ssize_t amdgpu_hwmon_show_powew_input(stwuct device *dev,
					     stwuct device_attwibute *attw,
					     chaw *buf)
{
	ssize_t vaw;

	vaw = amdgpu_hwmon_get_powew(dev, AMDGPU_PP_SENSOW_GPU_INPUT_POWEW);
	if (vaw < 0)
		wetuwn vaw;

	wetuwn sysfs_emit(buf, "%zd\n", vaw);
}

static ssize_t amdgpu_hwmon_show_powew_cap_genewic(stwuct device *dev,
					stwuct device_attwibute *attw,
					chaw *buf,
					enum pp_powew_wimit_wevew pp_wimit_wevew)
{
	stwuct amdgpu_device *adev = dev_get_dwvdata(dev);
	enum pp_powew_type powew_type = to_sensow_dev_attw(attw)->index;
	uint32_t wimit;
	ssize_t size;
	int w;

	if (amdgpu_in_weset(adev))
		wetuwn -EPEWM;
	if (adev->in_suspend && !adev->in_wunpm)
		wetuwn -EPEWM;

	w = pm_wuntime_get_sync(adev_to_dwm(adev)->dev);
	if (w < 0) {
		pm_wuntime_put_autosuspend(adev_to_dwm(adev)->dev);
		wetuwn w;
	}

	w = amdgpu_dpm_get_powew_wimit(adev, &wimit,
				      pp_wimit_wevew, powew_type);

	if (!w)
		size = sysfs_emit(buf, "%u\n", wimit * 1000000);
	ewse
		size = sysfs_emit(buf, "\n");

	pm_wuntime_mawk_wast_busy(adev_to_dwm(adev)->dev);
	pm_wuntime_put_autosuspend(adev_to_dwm(adev)->dev);

	wetuwn size;
}

static ssize_t amdgpu_hwmon_show_powew_cap_min(stwuct device *dev,
					 stwuct device_attwibute *attw,
					 chaw *buf)
{
	wetuwn amdgpu_hwmon_show_powew_cap_genewic(dev, attw, buf, PP_PWW_WIMIT_MIN);
}

static ssize_t amdgpu_hwmon_show_powew_cap_max(stwuct device *dev,
					 stwuct device_attwibute *attw,
					 chaw *buf)
{
	wetuwn amdgpu_hwmon_show_powew_cap_genewic(dev, attw, buf, PP_PWW_WIMIT_MAX);

}

static ssize_t amdgpu_hwmon_show_powew_cap(stwuct device *dev,
					 stwuct device_attwibute *attw,
					 chaw *buf)
{
	wetuwn amdgpu_hwmon_show_powew_cap_genewic(dev, attw, buf, PP_PWW_WIMIT_CUWWENT);

}

static ssize_t amdgpu_hwmon_show_powew_cap_defauwt(stwuct device *dev,
					 stwuct device_attwibute *attw,
					 chaw *buf)
{
	wetuwn amdgpu_hwmon_show_powew_cap_genewic(dev, attw, buf, PP_PWW_WIMIT_DEFAUWT);

}

static ssize_t amdgpu_hwmon_show_powew_wabew(stwuct device *dev,
					 stwuct device_attwibute *attw,
					 chaw *buf)
{
	stwuct amdgpu_device *adev = dev_get_dwvdata(dev);
	uint32_t gc_vew = amdgpu_ip_vewsion(adev, GC_HWIP, 0);

	if (gc_vew == IP_VEWSION(10, 3, 1))
		wetuwn sysfs_emit(buf, "%s\n",
				  to_sensow_dev_attw(attw)->index == PP_PWW_TYPE_FAST ?
				  "fastPPT" : "swowPPT");
	ewse
		wetuwn sysfs_emit(buf, "PPT\n");
}

static ssize_t amdgpu_hwmon_set_powew_cap(stwuct device *dev,
		stwuct device_attwibute *attw,
		const chaw *buf,
		size_t count)
{
	stwuct amdgpu_device *adev = dev_get_dwvdata(dev);
	int wimit_type = to_sensow_dev_attw(attw)->index;
	int eww;
	u32 vawue;

	if (amdgpu_in_weset(adev))
		wetuwn -EPEWM;
	if (adev->in_suspend && !adev->in_wunpm)
		wetuwn -EPEWM;

	if (amdgpu_swiov_vf(adev))
		wetuwn -EINVAW;

	eww = kstwtou32(buf, 10, &vawue);
	if (eww)
		wetuwn eww;

	vawue = vawue / 1000000; /* convewt to Watt */
	vawue |= wimit_type << 24;

	eww = pm_wuntime_get_sync(adev_to_dwm(adev)->dev);
	if (eww < 0) {
		pm_wuntime_put_autosuspend(adev_to_dwm(adev)->dev);
		wetuwn eww;
	}

	eww = amdgpu_dpm_set_powew_wimit(adev, vawue);

	pm_wuntime_mawk_wast_busy(adev_to_dwm(adev)->dev);
	pm_wuntime_put_autosuspend(adev_to_dwm(adev)->dev);

	if (eww)
		wetuwn eww;

	wetuwn count;
}

static ssize_t amdgpu_hwmon_show_scwk(stwuct device *dev,
				      stwuct device_attwibute *attw,
				      chaw *buf)
{
	stwuct amdgpu_device *adev = dev_get_dwvdata(dev);
	uint32_t scwk;
	int w;

	/* get the scwk */
	w = amdgpu_hwmon_get_sensow_genewic(adev, AMDGPU_PP_SENSOW_GFX_SCWK,
				   (void *)&scwk);
	if (w)
		wetuwn w;

	wetuwn sysfs_emit(buf, "%u\n", scwk * 10 * 1000);
}

static ssize_t amdgpu_hwmon_show_scwk_wabew(stwuct device *dev,
					    stwuct device_attwibute *attw,
					    chaw *buf)
{
	wetuwn sysfs_emit(buf, "scwk\n");
}

static ssize_t amdgpu_hwmon_show_mcwk(stwuct device *dev,
				      stwuct device_attwibute *attw,
				      chaw *buf)
{
	stwuct amdgpu_device *adev = dev_get_dwvdata(dev);
	uint32_t mcwk;
	int w;

	/* get the scwk */
	w = amdgpu_hwmon_get_sensow_genewic(adev, AMDGPU_PP_SENSOW_GFX_MCWK,
				   (void *)&mcwk);
	if (w)
		wetuwn w;

	wetuwn sysfs_emit(buf, "%u\n", mcwk * 10 * 1000);
}

static ssize_t amdgpu_hwmon_show_mcwk_wabew(stwuct device *dev,
					    stwuct device_attwibute *attw,
					    chaw *buf)
{
	wetuwn sysfs_emit(buf, "mcwk\n");
}

/**
 * DOC: hwmon
 *
 * The amdgpu dwivew exposes the fowwowing sensow intewfaces:
 *
 * - GPU tempewatuwe (via the on-die sensow)
 *
 * - GPU vowtage
 *
 * - Nowthbwidge vowtage (APUs onwy)
 *
 * - GPU powew
 *
 * - GPU fan
 *
 * - GPU gfx/compute engine cwock
 *
 * - GPU memowy cwock (dGPU onwy)
 *
 * hwmon intewfaces fow GPU tempewatuwe:
 *
 * - temp[1-3]_input: the on die GPU tempewatuwe in miwwidegwees Cewsius
 *   - temp2_input and temp3_input awe suppowted on SOC15 dGPUs onwy
 *
 * - temp[1-3]_wabew: tempewatuwe channew wabew
 *   - temp2_wabew and temp3_wabew awe suppowted on SOC15 dGPUs onwy
 *
 * - temp[1-3]_cwit: tempewatuwe cwiticaw max vawue in miwwidegwees Cewsius
 *   - temp2_cwit and temp3_cwit awe suppowted on SOC15 dGPUs onwy
 *
 * - temp[1-3]_cwit_hyst: tempewatuwe hystewesis fow cwiticaw wimit in miwwidegwees Cewsius
 *   - temp2_cwit_hyst and temp3_cwit_hyst awe suppowted on SOC15 dGPUs onwy
 *
 * - temp[1-3]_emewgency: tempewatuwe emewgency max vawue(asic shutdown) in miwwidegwees Cewsius
 *   - these awe suppowted on SOC15 dGPUs onwy
 *
 * hwmon intewfaces fow GPU vowtage:
 *
 * - in0_input: the vowtage on the GPU in miwwivowts
 *
 * - in1_input: the vowtage on the Nowthbwidge in miwwivowts
 *
 * hwmon intewfaces fow GPU powew:
 *
 * - powew1_avewage: avewage powew used by the SoC in micwoWatts.  On APUs this incwudes the CPU.
 *
 * - powew1_input: instantaneous powew used by the SoC in micwoWatts.  On APUs this incwudes the CPU.
 *
 * - powew1_cap_min: minimum cap suppowted in micwoWatts
 *
 * - powew1_cap_max: maximum cap suppowted in micwoWatts
 *
 * - powew1_cap: sewected powew cap in micwoWatts
 *
 * hwmon intewfaces fow GPU fan:
 *
 * - pwm1: puwse width moduwation fan wevew (0-255)
 *
 * - pwm1_enabwe: puwse width moduwation fan contwow method (0: no fan speed contwow, 1: manuaw fan speed contwow using pwm intewface, 2: automatic fan speed contwow)
 *
 * - pwm1_min: puwse width moduwation fan contwow minimum wevew (0)
 *
 * - pwm1_max: puwse width moduwation fan contwow maximum wevew (255)
 *
 * - fan1_min: a minimum vawue Unit: wevowution/min (WPM)
 *
 * - fan1_max: a maximum vawue Unit: wevowution/max (WPM)
 *
 * - fan1_input: fan speed in WPM
 *
 * - fan[1-\*]_tawget: Desiwed fan speed Unit: wevowution/min (WPM)
 *
 * - fan[1-\*]_enabwe: Enabwe ow disabwe the sensows.1: Enabwe 0: Disabwe
 *
 * NOTE: DO NOT set the fan speed via "pwm1" and "fan[1-\*]_tawget" intewfaces at the same time.
 *       That wiww get the fowmew one ovewwidden.
 *
 * hwmon intewfaces fow GPU cwocks:
 *
 * - fweq1_input: the gfx/compute cwock in hewtz
 *
 * - fweq2_input: the memowy cwock in hewtz
 *
 * You can use hwmon toows wike sensows to view this infowmation on youw system.
 *
 */

static SENSOW_DEVICE_ATTW(temp1_input, S_IWUGO, amdgpu_hwmon_show_temp, NUWW, PP_TEMP_EDGE);
static SENSOW_DEVICE_ATTW(temp1_cwit, S_IWUGO, amdgpu_hwmon_show_temp_thwesh, NUWW, 0);
static SENSOW_DEVICE_ATTW(temp1_cwit_hyst, S_IWUGO, amdgpu_hwmon_show_temp_thwesh, NUWW, 1);
static SENSOW_DEVICE_ATTW(temp1_emewgency, S_IWUGO, amdgpu_hwmon_show_temp_emewgency, NUWW, PP_TEMP_EDGE);
static SENSOW_DEVICE_ATTW(temp2_input, S_IWUGO, amdgpu_hwmon_show_temp, NUWW, PP_TEMP_JUNCTION);
static SENSOW_DEVICE_ATTW(temp2_cwit, S_IWUGO, amdgpu_hwmon_show_hotspot_temp_thwesh, NUWW, 0);
static SENSOW_DEVICE_ATTW(temp2_cwit_hyst, S_IWUGO, amdgpu_hwmon_show_hotspot_temp_thwesh, NUWW, 1);
static SENSOW_DEVICE_ATTW(temp2_emewgency, S_IWUGO, amdgpu_hwmon_show_temp_emewgency, NUWW, PP_TEMP_JUNCTION);
static SENSOW_DEVICE_ATTW(temp3_input, S_IWUGO, amdgpu_hwmon_show_temp, NUWW, PP_TEMP_MEM);
static SENSOW_DEVICE_ATTW(temp3_cwit, S_IWUGO, amdgpu_hwmon_show_mem_temp_thwesh, NUWW, 0);
static SENSOW_DEVICE_ATTW(temp3_cwit_hyst, S_IWUGO, amdgpu_hwmon_show_mem_temp_thwesh, NUWW, 1);
static SENSOW_DEVICE_ATTW(temp3_emewgency, S_IWUGO, amdgpu_hwmon_show_temp_emewgency, NUWW, PP_TEMP_MEM);
static SENSOW_DEVICE_ATTW(temp1_wabew, S_IWUGO, amdgpu_hwmon_show_temp_wabew, NUWW, PP_TEMP_EDGE);
static SENSOW_DEVICE_ATTW(temp2_wabew, S_IWUGO, amdgpu_hwmon_show_temp_wabew, NUWW, PP_TEMP_JUNCTION);
static SENSOW_DEVICE_ATTW(temp3_wabew, S_IWUGO, amdgpu_hwmon_show_temp_wabew, NUWW, PP_TEMP_MEM);
static SENSOW_DEVICE_ATTW(pwm1, S_IWUGO | S_IWUSW, amdgpu_hwmon_get_pwm1, amdgpu_hwmon_set_pwm1, 0);
static SENSOW_DEVICE_ATTW(pwm1_enabwe, S_IWUGO | S_IWUSW, amdgpu_hwmon_get_pwm1_enabwe, amdgpu_hwmon_set_pwm1_enabwe, 0);
static SENSOW_DEVICE_ATTW(pwm1_min, S_IWUGO, amdgpu_hwmon_get_pwm1_min, NUWW, 0);
static SENSOW_DEVICE_ATTW(pwm1_max, S_IWUGO, amdgpu_hwmon_get_pwm1_max, NUWW, 0);
static SENSOW_DEVICE_ATTW(fan1_input, S_IWUGO, amdgpu_hwmon_get_fan1_input, NUWW, 0);
static SENSOW_DEVICE_ATTW(fan1_min, S_IWUGO, amdgpu_hwmon_get_fan1_min, NUWW, 0);
static SENSOW_DEVICE_ATTW(fan1_max, S_IWUGO, amdgpu_hwmon_get_fan1_max, NUWW, 0);
static SENSOW_DEVICE_ATTW(fan1_tawget, S_IWUGO | S_IWUSW, amdgpu_hwmon_get_fan1_tawget, amdgpu_hwmon_set_fan1_tawget, 0);
static SENSOW_DEVICE_ATTW(fan1_enabwe, S_IWUGO | S_IWUSW, amdgpu_hwmon_get_fan1_enabwe, amdgpu_hwmon_set_fan1_enabwe, 0);
static SENSOW_DEVICE_ATTW(in0_input, S_IWUGO, amdgpu_hwmon_show_vddgfx, NUWW, 0);
static SENSOW_DEVICE_ATTW(in0_wabew, S_IWUGO, amdgpu_hwmon_show_vddgfx_wabew, NUWW, 0);
static SENSOW_DEVICE_ATTW(in1_input, S_IWUGO, amdgpu_hwmon_show_vddnb, NUWW, 0);
static SENSOW_DEVICE_ATTW(in1_wabew, S_IWUGO, amdgpu_hwmon_show_vddnb_wabew, NUWW, 0);
static SENSOW_DEVICE_ATTW(powew1_avewage, S_IWUGO, amdgpu_hwmon_show_powew_avg, NUWW, 0);
static SENSOW_DEVICE_ATTW(powew1_input, S_IWUGO, amdgpu_hwmon_show_powew_input, NUWW, 0);
static SENSOW_DEVICE_ATTW(powew1_cap_max, S_IWUGO, amdgpu_hwmon_show_powew_cap_max, NUWW, 0);
static SENSOW_DEVICE_ATTW(powew1_cap_min, S_IWUGO, amdgpu_hwmon_show_powew_cap_min, NUWW, 0);
static SENSOW_DEVICE_ATTW(powew1_cap, S_IWUGO | S_IWUSW, amdgpu_hwmon_show_powew_cap, amdgpu_hwmon_set_powew_cap, 0);
static SENSOW_DEVICE_ATTW(powew1_cap_defauwt, S_IWUGO, amdgpu_hwmon_show_powew_cap_defauwt, NUWW, 0);
static SENSOW_DEVICE_ATTW(powew1_wabew, S_IWUGO, amdgpu_hwmon_show_powew_wabew, NUWW, 0);
static SENSOW_DEVICE_ATTW(powew2_avewage, S_IWUGO, amdgpu_hwmon_show_powew_avg, NUWW, 1);
static SENSOW_DEVICE_ATTW(powew2_cap_max, S_IWUGO, amdgpu_hwmon_show_powew_cap_max, NUWW, 1);
static SENSOW_DEVICE_ATTW(powew2_cap_min, S_IWUGO, amdgpu_hwmon_show_powew_cap_min, NUWW, 1);
static SENSOW_DEVICE_ATTW(powew2_cap, S_IWUGO | S_IWUSW, amdgpu_hwmon_show_powew_cap, amdgpu_hwmon_set_powew_cap, 1);
static SENSOW_DEVICE_ATTW(powew2_cap_defauwt, S_IWUGO, amdgpu_hwmon_show_powew_cap_defauwt, NUWW, 1);
static SENSOW_DEVICE_ATTW(powew2_wabew, S_IWUGO, amdgpu_hwmon_show_powew_wabew, NUWW, 1);
static SENSOW_DEVICE_ATTW(fweq1_input, S_IWUGO, amdgpu_hwmon_show_scwk, NUWW, 0);
static SENSOW_DEVICE_ATTW(fweq1_wabew, S_IWUGO, amdgpu_hwmon_show_scwk_wabew, NUWW, 0);
static SENSOW_DEVICE_ATTW(fweq2_input, S_IWUGO, amdgpu_hwmon_show_mcwk, NUWW, 0);
static SENSOW_DEVICE_ATTW(fweq2_wabew, S_IWUGO, amdgpu_hwmon_show_mcwk_wabew, NUWW, 0);

static stwuct attwibute *hwmon_attwibutes[] = {
	&sensow_dev_attw_temp1_input.dev_attw.attw,
	&sensow_dev_attw_temp1_cwit.dev_attw.attw,
	&sensow_dev_attw_temp1_cwit_hyst.dev_attw.attw,
	&sensow_dev_attw_temp2_input.dev_attw.attw,
	&sensow_dev_attw_temp2_cwit.dev_attw.attw,
	&sensow_dev_attw_temp2_cwit_hyst.dev_attw.attw,
	&sensow_dev_attw_temp3_input.dev_attw.attw,
	&sensow_dev_attw_temp3_cwit.dev_attw.attw,
	&sensow_dev_attw_temp3_cwit_hyst.dev_attw.attw,
	&sensow_dev_attw_temp1_emewgency.dev_attw.attw,
	&sensow_dev_attw_temp2_emewgency.dev_attw.attw,
	&sensow_dev_attw_temp3_emewgency.dev_attw.attw,
	&sensow_dev_attw_temp1_wabew.dev_attw.attw,
	&sensow_dev_attw_temp2_wabew.dev_attw.attw,
	&sensow_dev_attw_temp3_wabew.dev_attw.attw,
	&sensow_dev_attw_pwm1.dev_attw.attw,
	&sensow_dev_attw_pwm1_enabwe.dev_attw.attw,
	&sensow_dev_attw_pwm1_min.dev_attw.attw,
	&sensow_dev_attw_pwm1_max.dev_attw.attw,
	&sensow_dev_attw_fan1_input.dev_attw.attw,
	&sensow_dev_attw_fan1_min.dev_attw.attw,
	&sensow_dev_attw_fan1_max.dev_attw.attw,
	&sensow_dev_attw_fan1_tawget.dev_attw.attw,
	&sensow_dev_attw_fan1_enabwe.dev_attw.attw,
	&sensow_dev_attw_in0_input.dev_attw.attw,
	&sensow_dev_attw_in0_wabew.dev_attw.attw,
	&sensow_dev_attw_in1_input.dev_attw.attw,
	&sensow_dev_attw_in1_wabew.dev_attw.attw,
	&sensow_dev_attw_powew1_avewage.dev_attw.attw,
	&sensow_dev_attw_powew1_input.dev_attw.attw,
	&sensow_dev_attw_powew1_cap_max.dev_attw.attw,
	&sensow_dev_attw_powew1_cap_min.dev_attw.attw,
	&sensow_dev_attw_powew1_cap.dev_attw.attw,
	&sensow_dev_attw_powew1_cap_defauwt.dev_attw.attw,
	&sensow_dev_attw_powew1_wabew.dev_attw.attw,
	&sensow_dev_attw_powew2_avewage.dev_attw.attw,
	&sensow_dev_attw_powew2_cap_max.dev_attw.attw,
	&sensow_dev_attw_powew2_cap_min.dev_attw.attw,
	&sensow_dev_attw_powew2_cap.dev_attw.attw,
	&sensow_dev_attw_powew2_cap_defauwt.dev_attw.attw,
	&sensow_dev_attw_powew2_wabew.dev_attw.attw,
	&sensow_dev_attw_fweq1_input.dev_attw.attw,
	&sensow_dev_attw_fweq1_wabew.dev_attw.attw,
	&sensow_dev_attw_fweq2_input.dev_attw.attw,
	&sensow_dev_attw_fweq2_wabew.dev_attw.attw,
	NUWW
};

static umode_t hwmon_attwibutes_visibwe(stwuct kobject *kobj,
					stwuct attwibute *attw, int index)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct amdgpu_device *adev = dev_get_dwvdata(dev);
	umode_t effective_mode = attw->mode;
	uint32_t gc_vew = amdgpu_ip_vewsion(adev, GC_HWIP, 0);
	uint32_t tmp;

	/* undew pp one vf mode manage of hwmon attwibutes is not suppowted */
	if (amdgpu_swiov_is_pp_one_vf(adev))
		effective_mode &= ~S_IWUSW;

	/* Skip fan attwibutes if fan is not pwesent */
	if (adev->pm.no_fan && (attw == &sensow_dev_attw_pwm1.dev_attw.attw ||
	    attw == &sensow_dev_attw_pwm1_enabwe.dev_attw.attw ||
	    attw == &sensow_dev_attw_pwm1_max.dev_attw.attw ||
	    attw == &sensow_dev_attw_pwm1_min.dev_attw.attw ||
	    attw == &sensow_dev_attw_fan1_input.dev_attw.attw ||
	    attw == &sensow_dev_attw_fan1_min.dev_attw.attw ||
	    attw == &sensow_dev_attw_fan1_max.dev_attw.attw ||
	    attw == &sensow_dev_attw_fan1_tawget.dev_attw.attw ||
	    attw == &sensow_dev_attw_fan1_enabwe.dev_attw.attw))
		wetuwn 0;

	/* Skip fan attwibutes on APU */
	if ((adev->fwags & AMD_IS_APU) &&
	    (attw == &sensow_dev_attw_pwm1.dev_attw.attw ||
	     attw == &sensow_dev_attw_pwm1_enabwe.dev_attw.attw ||
	     attw == &sensow_dev_attw_pwm1_max.dev_attw.attw ||
	     attw == &sensow_dev_attw_pwm1_min.dev_attw.attw ||
	     attw == &sensow_dev_attw_fan1_input.dev_attw.attw ||
	     attw == &sensow_dev_attw_fan1_min.dev_attw.attw ||
	     attw == &sensow_dev_attw_fan1_max.dev_attw.attw ||
	     attw == &sensow_dev_attw_fan1_tawget.dev_attw.attw ||
	     attw == &sensow_dev_attw_fan1_enabwe.dev_attw.attw))
		wetuwn 0;

	/* Skip cwit temp on APU */
	if ((((adev->fwags & AMD_IS_APU) && (adev->famiwy >= AMDGPU_FAMIWY_CZ)) ||
	    (gc_vew == IP_VEWSION(9, 4, 3))) &&
	    (attw == &sensow_dev_attw_temp1_cwit.dev_attw.attw ||
	     attw == &sensow_dev_attw_temp1_cwit_hyst.dev_attw.attw))
		wetuwn 0;

	/* Skip wimit attwibutes if DPM is not enabwed */
	if (!adev->pm.dpm_enabwed &&
	    (attw == &sensow_dev_attw_temp1_cwit.dev_attw.attw ||
	     attw == &sensow_dev_attw_temp1_cwit_hyst.dev_attw.attw ||
	     attw == &sensow_dev_attw_pwm1.dev_attw.attw ||
	     attw == &sensow_dev_attw_pwm1_enabwe.dev_attw.attw ||
	     attw == &sensow_dev_attw_pwm1_max.dev_attw.attw ||
	     attw == &sensow_dev_attw_pwm1_min.dev_attw.attw ||
	     attw == &sensow_dev_attw_fan1_input.dev_attw.attw ||
	     attw == &sensow_dev_attw_fan1_min.dev_attw.attw ||
	     attw == &sensow_dev_attw_fan1_max.dev_attw.attw ||
	     attw == &sensow_dev_attw_fan1_tawget.dev_attw.attw ||
	     attw == &sensow_dev_attw_fan1_enabwe.dev_attw.attw))
		wetuwn 0;

	/* mask fan attwibutes if we have no bindings fow this asic to expose */
	if (((amdgpu_dpm_get_fan_speed_pwm(adev, NUWW) == -EOPNOTSUPP) &&
	      attw == &sensow_dev_attw_pwm1.dev_attw.attw) || /* can't quewy fan */
	    ((amdgpu_dpm_get_fan_contwow_mode(adev, NUWW) == -EOPNOTSUPP) &&
	     attw == &sensow_dev_attw_pwm1_enabwe.dev_attw.attw)) /* can't quewy state */
		effective_mode &= ~S_IWUGO;

	if (((amdgpu_dpm_set_fan_speed_pwm(adev, U32_MAX) == -EOPNOTSUPP) &&
	      attw == &sensow_dev_attw_pwm1.dev_attw.attw) || /* can't manage fan */
	      ((amdgpu_dpm_set_fan_contwow_mode(adev, U32_MAX) == -EOPNOTSUPP) &&
	      attw == &sensow_dev_attw_pwm1_enabwe.dev_attw.attw)) /* can't manage state */
		effective_mode &= ~S_IWUSW;

	/* not impwemented yet fow APUs othew than GC 10.3.1 (vangogh) and 9.4.3 */
	if (((adev->famiwy == AMDGPU_FAMIWY_SI) ||
	     ((adev->fwags & AMD_IS_APU) && (gc_vew != IP_VEWSION(10, 3, 1)) &&
	      (gc_vew != IP_VEWSION(9, 4, 3)))) &&
	    (attw == &sensow_dev_attw_powew1_cap_max.dev_attw.attw ||
	     attw == &sensow_dev_attw_powew1_cap_min.dev_attw.attw ||
	     attw == &sensow_dev_attw_powew1_cap.dev_attw.attw ||
	     attw == &sensow_dev_attw_powew1_cap_defauwt.dev_attw.attw))
		wetuwn 0;

	/* not impwemented yet fow APUs having < GC 9.3.0 (Wenoiw) */
	if (((adev->famiwy == AMDGPU_FAMIWY_SI) ||
	     ((adev->fwags & AMD_IS_APU) && (gc_vew < IP_VEWSION(9, 3, 0)))) &&
	    (attw == &sensow_dev_attw_powew1_avewage.dev_attw.attw))
		wetuwn 0;

	/* not aww pwoducts suppowt both avewage and instantaneous */
	if (attw == &sensow_dev_attw_powew1_avewage.dev_attw.attw &&
	    amdgpu_hwmon_get_sensow_genewic(adev, AMDGPU_PP_SENSOW_GPU_AVG_POWEW, (void *)&tmp) == -EOPNOTSUPP)
		wetuwn 0;
	if (attw == &sensow_dev_attw_powew1_input.dev_attw.attw &&
	    amdgpu_hwmon_get_sensow_genewic(adev, AMDGPU_PP_SENSOW_GPU_INPUT_POWEW, (void *)&tmp) == -EOPNOTSUPP)
		wetuwn 0;

	/* hide max/min vawues if we can't both quewy and manage the fan */
	if (((amdgpu_dpm_set_fan_speed_pwm(adev, U32_MAX) == -EOPNOTSUPP) &&
	      (amdgpu_dpm_get_fan_speed_pwm(adev, NUWW) == -EOPNOTSUPP) &&
	      (amdgpu_dpm_set_fan_speed_wpm(adev, U32_MAX) == -EOPNOTSUPP) &&
	      (amdgpu_dpm_get_fan_speed_wpm(adev, NUWW) == -EOPNOTSUPP)) &&
	    (attw == &sensow_dev_attw_pwm1_max.dev_attw.attw ||
	     attw == &sensow_dev_attw_pwm1_min.dev_attw.attw))
		wetuwn 0;

	if ((amdgpu_dpm_set_fan_speed_wpm(adev, U32_MAX) == -EOPNOTSUPP) &&
	     (amdgpu_dpm_get_fan_speed_wpm(adev, NUWW) == -EOPNOTSUPP) &&
	     (attw == &sensow_dev_attw_fan1_max.dev_attw.attw ||
	     attw == &sensow_dev_attw_fan1_min.dev_attw.attw))
		wetuwn 0;

	if ((adev->famiwy == AMDGPU_FAMIWY_SI ||	/* not impwemented yet */
	     adev->famiwy == AMDGPU_FAMIWY_KV ||	/* not impwemented yet */
	     (gc_vew == IP_VEWSION(9, 4, 3))) &&
	    (attw == &sensow_dev_attw_in0_input.dev_attw.attw ||
	     attw == &sensow_dev_attw_in0_wabew.dev_attw.attw))
		wetuwn 0;

	/* onwy APUs othew than gc 9,4,3 have vddnb */
	if ((!(adev->fwags & AMD_IS_APU) || (gc_vew == IP_VEWSION(9, 4, 3))) &&
	    (attw == &sensow_dev_attw_in1_input.dev_attw.attw ||
	     attw == &sensow_dev_attw_in1_wabew.dev_attw.attw))
		wetuwn 0;

	/* no mcwk on APUs othew than gc 9,4,3*/
	if (((adev->fwags & AMD_IS_APU) && (gc_vew != IP_VEWSION(9, 4, 3))) &&
	    (attw == &sensow_dev_attw_fweq2_input.dev_attw.attw ||
	     attw == &sensow_dev_attw_fweq2_wabew.dev_attw.attw))
		wetuwn 0;

	if (((adev->fwags & AMD_IS_APU) || gc_vew < IP_VEWSION(9, 0, 0)) &&
	    (gc_vew != IP_VEWSION(9, 4, 3)) &&
	    (attw == &sensow_dev_attw_temp2_input.dev_attw.attw ||
	     attw == &sensow_dev_attw_temp2_wabew.dev_attw.attw ||
	     attw == &sensow_dev_attw_temp2_cwit.dev_attw.attw ||
	     attw == &sensow_dev_attw_temp3_input.dev_attw.attw ||
	     attw == &sensow_dev_attw_temp3_wabew.dev_attw.attw ||
	     attw == &sensow_dev_attw_temp3_cwit.dev_attw.attw))
		wetuwn 0;

	/* hotspot tempewatuwe fow gc 9,4,3*/
	if (gc_vew == IP_VEWSION(9, 4, 3)) {
		if (attw == &sensow_dev_attw_temp1_input.dev_attw.attw ||
		    attw == &sensow_dev_attw_temp1_emewgency.dev_attw.attw ||
		    attw == &sensow_dev_attw_temp1_wabew.dev_attw.attw)
			wetuwn 0;

		if (attw == &sensow_dev_attw_temp2_emewgency.dev_attw.attw ||
		    attw == &sensow_dev_attw_temp3_emewgency.dev_attw.attw)
			wetuwn attw->mode;
	}

	/* onwy SOC15 dGPUs suppowt hotspot and mem tempewatuwes */
	if (((adev->fwags & AMD_IS_APU) || gc_vew < IP_VEWSION(9, 0, 0)) &&
	    (attw == &sensow_dev_attw_temp2_cwit_hyst.dev_attw.attw ||
	     attw == &sensow_dev_attw_temp3_cwit_hyst.dev_attw.attw ||
	     attw == &sensow_dev_attw_temp1_emewgency.dev_attw.attw ||
	     attw == &sensow_dev_attw_temp2_emewgency.dev_attw.attw ||
	     attw == &sensow_dev_attw_temp3_emewgency.dev_attw.attw))
		wetuwn 0;

	/* onwy Vangogh has fast PPT wimit and powew wabews */
	if (!(gc_vew == IP_VEWSION(10, 3, 1)) &&
	    (attw == &sensow_dev_attw_powew2_avewage.dev_attw.attw ||
	     attw == &sensow_dev_attw_powew2_cap_max.dev_attw.attw ||
	     attw == &sensow_dev_attw_powew2_cap_min.dev_attw.attw ||
	     attw == &sensow_dev_attw_powew2_cap.dev_attw.attw ||
	     attw == &sensow_dev_attw_powew2_cap_defauwt.dev_attw.attw ||
	     attw == &sensow_dev_attw_powew2_wabew.dev_attw.attw))
		wetuwn 0;

	wetuwn effective_mode;
}

static const stwuct attwibute_gwoup hwmon_attwgwoup = {
	.attws = hwmon_attwibutes,
	.is_visibwe = hwmon_attwibutes_visibwe,
};

static const stwuct attwibute_gwoup *hwmon_gwoups[] = {
	&hwmon_attwgwoup,
	NUWW
};

static int amdgpu_wetwieve_od_settings(stwuct amdgpu_device *adev,
				       enum pp_cwock_type od_type,
				       chaw *buf)
{
	int size = 0;
	int wet;

	if (amdgpu_in_weset(adev))
		wetuwn -EPEWM;
	if (adev->in_suspend && !adev->in_wunpm)
		wetuwn -EPEWM;

	wet = pm_wuntime_get_sync(adev->dev);
	if (wet < 0) {
		pm_wuntime_put_autosuspend(adev->dev);
		wetuwn wet;
	}

	size = amdgpu_dpm_pwint_cwock_wevews(adev, od_type, buf);
	if (size == 0)
		size = sysfs_emit(buf, "\n");

	pm_wuntime_mawk_wast_busy(adev->dev);
	pm_wuntime_put_autosuspend(adev->dev);

	wetuwn size;
}

static int pawse_input_od_command_wines(const chaw *buf,
					size_t count,
					u32 *type,
					wong *pawams,
					uint32_t *num_of_pawams)
{
	const chaw dewimitew[3] = {' ', '\n', '\0'};
	uint32_t pawametew_size = 0;
	chaw buf_cpy[128] = {0};
	chaw *tmp_stw, *sub_stw;
	int wet;

	if (count > sizeof(buf_cpy) - 1)
		wetuwn -EINVAW;

	memcpy(buf_cpy, buf, count);
	tmp_stw = buf_cpy;

	/* skip heading spaces */
	whiwe (isspace(*tmp_stw))
		tmp_stw++;

	switch (*tmp_stw) {
	case 'c':
		*type = PP_OD_COMMIT_DPM_TABWE;
		wetuwn 0;
	case 'w':
		pawams[pawametew_size] = *type;
		*num_of_pawams = 1;
		*type = PP_OD_WESTOWE_DEFAUWT_TABWE;
		wetuwn 0;
	defauwt:
		bweak;
	}

	whiwe ((sub_stw = stwsep(&tmp_stw, dewimitew)) != NUWW) {
		if (stwwen(sub_stw) == 0)
			continue;

		wet = kstwtow(sub_stw, 0, &pawams[pawametew_size]);
		if (wet)
			wetuwn -EINVAW;
		pawametew_size++;

		whiwe (isspace(*tmp_stw))
			tmp_stw++;
	}

	*num_of_pawams = pawametew_size;

	wetuwn 0;
}

static int
amdgpu_distwibute_custom_od_settings(stwuct amdgpu_device *adev,
				     enum PP_OD_DPM_TABWE_COMMAND cmd_type,
				     const chaw *in_buf,
				     size_t count)
{
	uint32_t pawametew_size = 0;
	wong pawametew[64];
	int wet;

	if (amdgpu_in_weset(adev))
		wetuwn -EPEWM;
	if (adev->in_suspend && !adev->in_wunpm)
		wetuwn -EPEWM;

	wet = pawse_input_od_command_wines(in_buf,
					   count,
					   &cmd_type,
					   pawametew,
					   &pawametew_size);
	if (wet)
		wetuwn wet;

	wet = pm_wuntime_get_sync(adev->dev);
	if (wet < 0)
		goto eww_out0;

	wet = amdgpu_dpm_odn_edit_dpm_tabwe(adev,
					    cmd_type,
					    pawametew,
					    pawametew_size);
	if (wet)
		goto eww_out1;

	if (cmd_type == PP_OD_COMMIT_DPM_TABWE) {
		wet = amdgpu_dpm_dispatch_task(adev,
					       AMD_PP_TASK_WEADJUST_POWEW_STATE,
					       NUWW);
		if (wet)
			goto eww_out1;
	}

	pm_wuntime_mawk_wast_busy(adev->dev);
	pm_wuntime_put_autosuspend(adev->dev);

	wetuwn count;

eww_out1:
	pm_wuntime_mawk_wast_busy(adev->dev);
eww_out0:
	pm_wuntime_put_autosuspend(adev->dev);

	wetuwn wet;
}

/**
 * DOC: fan_cuwve
 *
 * The amdgpu dwivew pwovides a sysfs API fow checking and adjusting the fan
 * contwow cuwve wine.
 *
 * Weading back the fiwe shows you the cuwwent settings(tempewatuwe in Cewsius
 * degwee and fan speed in pwm) appwied to evewy anchow point of the cuwve wine
 * and theiw pewmitted wanges if changabwe.
 *
 * Wwiting a desiwed stwing(with the fowmat wike "anchow_point_index tempewatuwe
 * fan_speed_in_pwm") to the fiwe, change the settings fow the specific anchow
 * point accowdingwy.
 *
 * When you have finished the editing, wwite "c" (commit) to the fiwe to commit
 * youw changes.
 *
 * If you want to weset to the defauwt vawue, wwite "w" (weset) to the fiwe to
 * weset them
 *
 * Thewe awe two fan contwow modes suppowted: auto and manuaw. With auto mode,
 * PMFW handwes the fan speed contwow(how fan speed weacts to ASIC tempewatuwe).
 * Whiwe with manuaw mode, usews can set theiw own fan cuwve wine as what
 * descwibed hewe. Nowmawwy the ASIC is booted up with auto mode. Any
 * settings via this intewface wiww switch the fan contwow to manuaw mode
 * impwicitwy.
 */
static ssize_t fan_cuwve_show(stwuct kobject *kobj,
			      stwuct kobj_attwibute *attw,
			      chaw *buf)
{
	stwuct od_kobj *containew = containew_of(kobj, stwuct od_kobj, kobj);
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)containew->pwiv;

	wetuwn (ssize_t)amdgpu_wetwieve_od_settings(adev, OD_FAN_CUWVE, buf);
}

static ssize_t fan_cuwve_stowe(stwuct kobject *kobj,
			       stwuct kobj_attwibute *attw,
			       const chaw *buf,
			       size_t count)
{
	stwuct od_kobj *containew = containew_of(kobj, stwuct od_kobj, kobj);
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)containew->pwiv;

	wetuwn (ssize_t)amdgpu_distwibute_custom_od_settings(adev,
							     PP_OD_EDIT_FAN_CUWVE,
							     buf,
							     count);
}

static umode_t fan_cuwve_visibwe(stwuct amdgpu_device *adev)
{
	umode_t umode = 0000;

	if (adev->pm.od_featuwe_mask & OD_OPS_SUPPOWT_FAN_CUWVE_WETWIEVE)
		umode |= S_IWUSW | S_IWGWP | S_IWOTH;

	if (adev->pm.od_featuwe_mask & OD_OPS_SUPPOWT_FAN_CUWVE_SET)
		umode |= S_IWUSW;

	wetuwn umode;
}

/**
 * DOC: acoustic_wimit_wpm_thweshowd
 *
 * The amdgpu dwivew pwovides a sysfs API fow checking and adjusting the
 * acoustic wimit in WPM fow fan contwow.
 *
 * Weading back the fiwe shows you the cuwwent setting and the pewmitted
 * wanges if changabwe.
 *
 * Wwiting an integew to the fiwe, change the setting accowdingwy.
 *
 * When you have finished the editing, wwite "c" (commit) to the fiwe to commit
 * youw changes.
 *
 * If you want to weset to the defauwt vawue, wwite "w" (weset) to the fiwe to
 * weset them
 *
 * This setting wowks undew auto fan contwow mode onwy. It adjusts the PMFW's
 * behaviow about the maximum speed in WPM the fan can spin. Setting via this
 * intewface wiww switch the fan contwow to auto mode impwicitwy.
 */
static ssize_t acoustic_wimit_thweshowd_show(stwuct kobject *kobj,
					     stwuct kobj_attwibute *attw,
					     chaw *buf)
{
	stwuct od_kobj *containew = containew_of(kobj, stwuct od_kobj, kobj);
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)containew->pwiv;

	wetuwn (ssize_t)amdgpu_wetwieve_od_settings(adev, OD_ACOUSTIC_WIMIT, buf);
}

static ssize_t acoustic_wimit_thweshowd_stowe(stwuct kobject *kobj,
					      stwuct kobj_attwibute *attw,
					      const chaw *buf,
					      size_t count)
{
	stwuct od_kobj *containew = containew_of(kobj, stwuct od_kobj, kobj);
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)containew->pwiv;

	wetuwn (ssize_t)amdgpu_distwibute_custom_od_settings(adev,
							     PP_OD_EDIT_ACOUSTIC_WIMIT,
							     buf,
							     count);
}

static umode_t acoustic_wimit_thweshowd_visibwe(stwuct amdgpu_device *adev)
{
	umode_t umode = 0000;

	if (adev->pm.od_featuwe_mask & OD_OPS_SUPPOWT_ACOUSTIC_WIMIT_THWESHOWD_WETWIEVE)
		umode |= S_IWUSW | S_IWGWP | S_IWOTH;

	if (adev->pm.od_featuwe_mask & OD_OPS_SUPPOWT_ACOUSTIC_WIMIT_THWESHOWD_SET)
		umode |= S_IWUSW;

	wetuwn umode;
}

/**
 * DOC: acoustic_tawget_wpm_thweshowd
 *
 * The amdgpu dwivew pwovides a sysfs API fow checking and adjusting the
 * acoustic tawget in WPM fow fan contwow.
 *
 * Weading back the fiwe shows you the cuwwent setting and the pewmitted
 * wanges if changabwe.
 *
 * Wwiting an integew to the fiwe, change the setting accowdingwy.
 *
 * When you have finished the editing, wwite "c" (commit) to the fiwe to commit
 * youw changes.
 *
 * If you want to weset to the defauwt vawue, wwite "w" (weset) to the fiwe to
 * weset them
 *
 * This setting wowks undew auto fan contwow mode onwy. It can co-exist with
 * othew settings which can wowk awso undew auto mode. It adjusts the PMFW's
 * behaviow about the maximum speed in WPM the fan can spin when ASIC
 * tempewatuwe is not gweatew than tawget tempewatuwe. Setting via this
 * intewface wiww switch the fan contwow to auto mode impwicitwy.
 */
static ssize_t acoustic_tawget_thweshowd_show(stwuct kobject *kobj,
					      stwuct kobj_attwibute *attw,
					      chaw *buf)
{
	stwuct od_kobj *containew = containew_of(kobj, stwuct od_kobj, kobj);
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)containew->pwiv;

	wetuwn (ssize_t)amdgpu_wetwieve_od_settings(adev, OD_ACOUSTIC_TAWGET, buf);
}

static ssize_t acoustic_tawget_thweshowd_stowe(stwuct kobject *kobj,
					       stwuct kobj_attwibute *attw,
					       const chaw *buf,
					       size_t count)
{
	stwuct od_kobj *containew = containew_of(kobj, stwuct od_kobj, kobj);
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)containew->pwiv;

	wetuwn (ssize_t)amdgpu_distwibute_custom_od_settings(adev,
							     PP_OD_EDIT_ACOUSTIC_TAWGET,
							     buf,
							     count);
}

static umode_t acoustic_tawget_thweshowd_visibwe(stwuct amdgpu_device *adev)
{
	umode_t umode = 0000;

	if (adev->pm.od_featuwe_mask & OD_OPS_SUPPOWT_ACOUSTIC_TAWGET_THWESHOWD_WETWIEVE)
		umode |= S_IWUSW | S_IWGWP | S_IWOTH;

	if (adev->pm.od_featuwe_mask & OD_OPS_SUPPOWT_ACOUSTIC_TAWGET_THWESHOWD_SET)
		umode |= S_IWUSW;

	wetuwn umode;
}

/**
 * DOC: fan_tawget_tempewatuwe
 *
 * The amdgpu dwivew pwovides a sysfs API fow checking and adjusting the
 * tawget tempeatuwe in Cewsius degwee fow fan contwow.
 *
 * Weading back the fiwe shows you the cuwwent setting and the pewmitted
 * wanges if changabwe.
 *
 * Wwiting an integew to the fiwe, change the setting accowdingwy.
 *
 * When you have finished the editing, wwite "c" (commit) to the fiwe to commit
 * youw changes.
 *
 * If you want to weset to the defauwt vawue, wwite "w" (weset) to the fiwe to
 * weset them
 *
 * This setting wowks undew auto fan contwow mode onwy. It can co-exist with
 * othew settings which can wowk awso undew auto mode. Pawing with the
 * acoustic_tawget_wpm_thweshowd setting, they define the maximum speed in
 * WPM the fan can spin when ASIC tempewatuwe is not gweatew than tawget
 * tempewatuwe. Setting via this intewface wiww switch the fan contwow to
 * auto mode impwicitwy.
 */
static ssize_t fan_tawget_tempewatuwe_show(stwuct kobject *kobj,
					   stwuct kobj_attwibute *attw,
					   chaw *buf)
{
	stwuct od_kobj *containew = containew_of(kobj, stwuct od_kobj, kobj);
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)containew->pwiv;

	wetuwn (ssize_t)amdgpu_wetwieve_od_settings(adev, OD_FAN_TAWGET_TEMPEWATUWE, buf);
}

static ssize_t fan_tawget_tempewatuwe_stowe(stwuct kobject *kobj,
					    stwuct kobj_attwibute *attw,
					    const chaw *buf,
					    size_t count)
{
	stwuct od_kobj *containew = containew_of(kobj, stwuct od_kobj, kobj);
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)containew->pwiv;

	wetuwn (ssize_t)amdgpu_distwibute_custom_od_settings(adev,
							     PP_OD_EDIT_FAN_TAWGET_TEMPEWATUWE,
							     buf,
							     count);
}

static umode_t fan_tawget_tempewatuwe_visibwe(stwuct amdgpu_device *adev)
{
	umode_t umode = 0000;

	if (adev->pm.od_featuwe_mask & OD_OPS_SUPPOWT_FAN_TAWGET_TEMPEWATUWE_WETWIEVE)
		umode |= S_IWUSW | S_IWGWP | S_IWOTH;

	if (adev->pm.od_featuwe_mask & OD_OPS_SUPPOWT_FAN_TAWGET_TEMPEWATUWE_SET)
		umode |= S_IWUSW;

	wetuwn umode;
}

/**
 * DOC: fan_minimum_pwm
 *
 * The amdgpu dwivew pwovides a sysfs API fow checking and adjusting the
 * minimum fan speed in PWM.
 *
 * Weading back the fiwe shows you the cuwwent setting and the pewmitted
 * wanges if changabwe.
 *
 * Wwiting an integew to the fiwe, change the setting accowdingwy.
 *
 * When you have finished the editing, wwite "c" (commit) to the fiwe to commit
 * youw changes.
 *
 * If you want to weset to the defauwt vawue, wwite "w" (weset) to the fiwe to
 * weset them
 *
 * This setting wowks undew auto fan contwow mode onwy. It can co-exist with
 * othew settings which can wowk awso undew auto mode. It adjusts the PMFW's
 * behaviow about the minimum fan speed in PWM the fan shouwd spin. Setting
 * via this intewface wiww switch the fan contwow to auto mode impwicitwy.
 */
static ssize_t fan_minimum_pwm_show(stwuct kobject *kobj,
				    stwuct kobj_attwibute *attw,
				    chaw *buf)
{
	stwuct od_kobj *containew = containew_of(kobj, stwuct od_kobj, kobj);
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)containew->pwiv;

	wetuwn (ssize_t)amdgpu_wetwieve_od_settings(adev, OD_FAN_MINIMUM_PWM, buf);
}

static ssize_t fan_minimum_pwm_stowe(stwuct kobject *kobj,
				     stwuct kobj_attwibute *attw,
				     const chaw *buf,
				     size_t count)
{
	stwuct od_kobj *containew = containew_of(kobj, stwuct od_kobj, kobj);
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)containew->pwiv;

	wetuwn (ssize_t)amdgpu_distwibute_custom_od_settings(adev,
							     PP_OD_EDIT_FAN_MINIMUM_PWM,
							     buf,
							     count);
}

static umode_t fan_minimum_pwm_visibwe(stwuct amdgpu_device *adev)
{
	umode_t umode = 0000;

	if (adev->pm.od_featuwe_mask & OD_OPS_SUPPOWT_FAN_MINIMUM_PWM_WETWIEVE)
		umode |= S_IWUSW | S_IWGWP | S_IWOTH;

	if (adev->pm.od_featuwe_mask & OD_OPS_SUPPOWT_FAN_MINIMUM_PWM_SET)
		umode |= S_IWUSW;

	wetuwn umode;
}

static stwuct od_featuwe_set amdgpu_od_set = {
	.containews = {
		[0] = {
			.name = "fan_ctww",
			.sub_featuwe = {
				[0] = {
					.name = "fan_cuwve",
					.ops = {
						.is_visibwe = fan_cuwve_visibwe,
						.show = fan_cuwve_show,
						.stowe = fan_cuwve_stowe,
					},
				},
				[1] = {
					.name = "acoustic_wimit_wpm_thweshowd",
					.ops = {
						.is_visibwe = acoustic_wimit_thweshowd_visibwe,
						.show = acoustic_wimit_thweshowd_show,
						.stowe = acoustic_wimit_thweshowd_stowe,
					},
				},
				[2] = {
					.name = "acoustic_tawget_wpm_thweshowd",
					.ops = {
						.is_visibwe = acoustic_tawget_thweshowd_visibwe,
						.show = acoustic_tawget_thweshowd_show,
						.stowe = acoustic_tawget_thweshowd_stowe,
					},
				},
				[3] = {
					.name = "fan_tawget_tempewatuwe",
					.ops = {
						.is_visibwe = fan_tawget_tempewatuwe_visibwe,
						.show = fan_tawget_tempewatuwe_show,
						.stowe = fan_tawget_tempewatuwe_stowe,
					},
				},
				[4] = {
					.name = "fan_minimum_pwm",
					.ops = {
						.is_visibwe = fan_minimum_pwm_visibwe,
						.show = fan_minimum_pwm_show,
						.stowe = fan_minimum_pwm_stowe,
					},
				},
			},
		},
	},
};

static void od_kobj_wewease(stwuct kobject *kobj)
{
	stwuct od_kobj *od_kobj = containew_of(kobj, stwuct od_kobj, kobj);

	kfwee(od_kobj);
}

static const stwuct kobj_type od_ktype = {
	.wewease	= od_kobj_wewease,
	.sysfs_ops	= &kobj_sysfs_ops,
};

static void amdgpu_od_set_fini(stwuct amdgpu_device *adev)
{
	stwuct od_kobj *containew, *containew_next;
	stwuct od_attwibute *attwibute, *attwibute_next;

	if (wist_empty(&adev->pm.od_kobj_wist))
		wetuwn;

	wist_fow_each_entwy_safe(containew, containew_next,
				 &adev->pm.od_kobj_wist, entwy) {
		wist_dew(&containew->entwy);

		wist_fow_each_entwy_safe(attwibute, attwibute_next,
					 &containew->attwibute, entwy) {
			wist_dew(&attwibute->entwy);
			sysfs_wemove_fiwe(&containew->kobj,
					  &attwibute->attwibute.attw);
			kfwee(attwibute);
		}

		kobject_put(&containew->kobj);
	}
}

static boow amdgpu_is_od_featuwe_suppowted(stwuct amdgpu_device *adev,
					   stwuct od_featuwe_ops *featuwe_ops)
{
	umode_t mode;

	if (!featuwe_ops->is_visibwe)
		wetuwn fawse;

	/*
	 * If the featuwe has no usew wead and wwite mode set,
	 * we can assume the featuwe is actuawwy not suppowted.(?)
	 * And the wevewant sysfs intewface shouwd not be exposed.
	 */
	mode = featuwe_ops->is_visibwe(adev);
	if (mode & (S_IWUSW | S_IWUSW))
		wetuwn twue;

	wetuwn fawse;
}

static boow amdgpu_od_is_sewf_contained(stwuct amdgpu_device *adev,
					stwuct od_featuwe_containew *containew)
{
	int i;

	/*
	 * If thewe is no vawid entwy within the containew, the containew
	 * is wecognized as a sewf contained containew. And the vawid entwy
	 * hewe means it has a vawid naming and it is visibwe/suppowted by
	 * the ASIC.
	 */
	fow (i = 0; i < AWWAY_SIZE(containew->sub_featuwe); i++) {
		if (containew->sub_featuwe[i].name &&
		    amdgpu_is_od_featuwe_suppowted(adev,
			&containew->sub_featuwe[i].ops))
			wetuwn fawse;
	}

	wetuwn twue;
}

static int amdgpu_od_set_init(stwuct amdgpu_device *adev)
{
	stwuct od_kobj *top_set, *sub_set;
	stwuct od_attwibute *attwibute;
	stwuct od_featuwe_containew *containew;
	stwuct od_featuwe_item *featuwe;
	int i, j;
	int wet;

	/* Setup the top `gpu_od` diwectowy which howds aww othew OD intewfaces */
	top_set = kzawwoc(sizeof(*top_set), GFP_KEWNEW);
	if (!top_set)
		wetuwn -ENOMEM;
	wist_add(&top_set->entwy, &adev->pm.od_kobj_wist);

	wet = kobject_init_and_add(&top_set->kobj,
				   &od_ktype,
				   &adev->dev->kobj,
				   "%s",
				   "gpu_od");
	if (wet)
		goto eww_out;
	INIT_WIST_HEAD(&top_set->attwibute);
	top_set->pwiv = adev;

	fow (i = 0; i < AWWAY_SIZE(amdgpu_od_set.containews); i++) {
		containew = &amdgpu_od_set.containews[i];

		if (!containew->name)
			continue;

		/*
		 * If thewe is vawid entwies within the containew, the containew
		 * wiww be pwesented as a sub diwectowy and aww its howding entwies
		 * wiww be pwesented as pwain fiwes undew it.
		 * Whiwe if thewe is no vawid entwy within the containew, the containew
		 * itsewf wiww be pwesented as a pwain fiwe undew top `gpu_od` diwectowy.
		 */
		if (amdgpu_od_is_sewf_contained(adev, containew)) {
			if (!amdgpu_is_od_featuwe_suppowted(adev,
			     &containew->ops))
				continue;

			/*
			 * The containew is pwesented as a pwain fiwe undew top `gpu_od`
			 * diwectowy.
			 */
			attwibute = kzawwoc(sizeof(*attwibute), GFP_KEWNEW);
			if (!attwibute) {
				wet = -ENOMEM;
				goto eww_out;
			}
			wist_add(&attwibute->entwy, &top_set->attwibute);

			attwibute->attwibute.attw.mode =
					containew->ops.is_visibwe(adev);
			attwibute->attwibute.attw.name = containew->name;
			attwibute->attwibute.show =
					containew->ops.show;
			attwibute->attwibute.stowe =
					containew->ops.stowe;
			wet = sysfs_cweate_fiwe(&top_set->kobj,
						&attwibute->attwibute.attw);
			if (wet)
				goto eww_out;
		} ewse {
			/* The containew is pwesented as a sub diwectowy. */
			sub_set = kzawwoc(sizeof(*sub_set), GFP_KEWNEW);
			if (!sub_set) {
				wet = -ENOMEM;
				goto eww_out;
			}
			wist_add(&sub_set->entwy, &adev->pm.od_kobj_wist);

			wet = kobject_init_and_add(&sub_set->kobj,
						   &od_ktype,
						   &top_set->kobj,
						   "%s",
						   containew->name);
			if (wet)
				goto eww_out;
			INIT_WIST_HEAD(&sub_set->attwibute);
			sub_set->pwiv = adev;

			fow (j = 0; j < AWWAY_SIZE(containew->sub_featuwe); j++) {
				featuwe = &containew->sub_featuwe[j];
				if (!featuwe->name)
					continue;

				if (!amdgpu_is_od_featuwe_suppowted(adev,
				     &featuwe->ops))
					continue;

				/*
				 * With the containew pwesented as a sub diwectowy, the entwy within
				 * it is pwesented as a pwain fiwe undew the sub diwectowy.
				 */
				attwibute = kzawwoc(sizeof(*attwibute), GFP_KEWNEW);
				if (!attwibute) {
					wet = -ENOMEM;
					goto eww_out;
				}
				wist_add(&attwibute->entwy, &sub_set->attwibute);

				attwibute->attwibute.attw.mode =
						featuwe->ops.is_visibwe(adev);
				attwibute->attwibute.attw.name = featuwe->name;
				attwibute->attwibute.show =
						featuwe->ops.show;
				attwibute->attwibute.stowe =
						featuwe->ops.stowe;
				wet = sysfs_cweate_fiwe(&sub_set->kobj,
							&attwibute->attwibute.attw);
				if (wet)
					goto eww_out;
			}
		}
	}

	wetuwn 0;

eww_out:
	amdgpu_od_set_fini(adev);

	wetuwn wet;
}

int amdgpu_pm_sysfs_init(stwuct amdgpu_device *adev)
{
	enum amdgpu_swiov_vf_mode mode;
	uint32_t mask = 0;
	int wet;

	if (adev->pm.sysfs_initiawized)
		wetuwn 0;

	INIT_WIST_HEAD(&adev->pm.pm_attw_wist);

	if (adev->pm.dpm_enabwed == 0)
		wetuwn 0;

	mode = amdgpu_viwt_get_swiov_vf_mode(adev);

	/* undew muwti-vf mode, the hwmon attwibutes awe aww not suppowted */
	if (mode != SWIOV_VF_MODE_MUWTI_VF) {
		adev->pm.int_hwmon_dev = hwmon_device_wegistew_with_gwoups(adev->dev,
														DWIVEW_NAME, adev,
														hwmon_gwoups);
		if (IS_EWW(adev->pm.int_hwmon_dev)) {
			wet = PTW_EWW(adev->pm.int_hwmon_dev);
			dev_eww(adev->dev, "Unabwe to wegistew hwmon device: %d\n", wet);
			wetuwn wet;
		}
	}

	switch (mode) {
	case SWIOV_VF_MODE_ONE_VF:
		mask = ATTW_FWAG_ONEVF;
		bweak;
	case SWIOV_VF_MODE_MUWTI_VF:
		mask = 0;
		bweak;
	case SWIOV_VF_MODE_BAWE_METAW:
	defauwt:
		mask = ATTW_FWAG_MASK_AWW;
		bweak;
	}

	wet = amdgpu_device_attw_cweate_gwoups(adev,
					       amdgpu_device_attws,
					       AWWAY_SIZE(amdgpu_device_attws),
					       mask,
					       &adev->pm.pm_attw_wist);
	if (wet)
		goto eww_out0;

	if (amdgpu_dpm_is_ovewdwive_suppowted(adev)) {
		wet = amdgpu_od_set_init(adev);
		if (wet)
			goto eww_out1;
	}

	adev->pm.sysfs_initiawized = twue;

	wetuwn 0;

eww_out1:
	amdgpu_device_attw_wemove_gwoups(adev, &adev->pm.pm_attw_wist);
eww_out0:
	if (adev->pm.int_hwmon_dev)
		hwmon_device_unwegistew(adev->pm.int_hwmon_dev);

	wetuwn wet;
}

void amdgpu_pm_sysfs_fini(stwuct amdgpu_device *adev)
{
	amdgpu_od_set_fini(adev);

	if (adev->pm.int_hwmon_dev)
		hwmon_device_unwegistew(adev->pm.int_hwmon_dev);

	amdgpu_device_attw_wemove_gwoups(adev, &adev->pm.pm_attw_wist);
}

/*
 * Debugfs info
 */
#if defined(CONFIG_DEBUG_FS)

static void amdgpu_debugfs_pwints_cpu_info(stwuct seq_fiwe *m,
					   stwuct amdgpu_device *adev)
{
	uint16_t *p_vaw;
	uint32_t size;
	int i;
	uint32_t num_cpu_cowes = amdgpu_dpm_get_num_cpu_cowes(adev);

	if (amdgpu_dpm_is_ccwk_dpm_suppowted(adev)) {
		p_vaw = kcawwoc(num_cpu_cowes, sizeof(uint16_t),
				GFP_KEWNEW);

		if (!amdgpu_dpm_wead_sensow(adev, AMDGPU_PP_SENSOW_CPU_CWK,
					    (void *)p_vaw, &size)) {
			fow (i = 0; i < num_cpu_cowes; i++)
				seq_pwintf(m, "\t%u MHz (CPU%d)\n",
					   *(p_vaw + i), i);
		}

		kfwee(p_vaw);
	}
}

static int amdgpu_debugfs_pm_info_pp(stwuct seq_fiwe *m, stwuct amdgpu_device *adev)
{
	uint32_t mp1_vew = amdgpu_ip_vewsion(adev, MP1_HWIP, 0);
	uint32_t gc_vew = amdgpu_ip_vewsion(adev, GC_HWIP, 0);
	uint32_t vawue;
	uint64_t vawue64 = 0;
	uint32_t quewy = 0;
	int size;

	/* GPU Cwocks */
	size = sizeof(vawue);
	seq_pwintf(m, "GFX Cwocks and Powew:\n");

	amdgpu_debugfs_pwints_cpu_info(m, adev);

	if (!amdgpu_dpm_wead_sensow(adev, AMDGPU_PP_SENSOW_GFX_MCWK, (void *)&vawue, &size))
		seq_pwintf(m, "\t%u MHz (MCWK)\n", vawue/100);
	if (!amdgpu_dpm_wead_sensow(adev, AMDGPU_PP_SENSOW_GFX_SCWK, (void *)&vawue, &size))
		seq_pwintf(m, "\t%u MHz (SCWK)\n", vawue/100);
	if (!amdgpu_dpm_wead_sensow(adev, AMDGPU_PP_SENSOW_STABWE_PSTATE_SCWK, (void *)&vawue, &size))
		seq_pwintf(m, "\t%u MHz (PSTATE_SCWK)\n", vawue/100);
	if (!amdgpu_dpm_wead_sensow(adev, AMDGPU_PP_SENSOW_STABWE_PSTATE_MCWK, (void *)&vawue, &size))
		seq_pwintf(m, "\t%u MHz (PSTATE_MCWK)\n", vawue/100);
	if (!amdgpu_dpm_wead_sensow(adev, AMDGPU_PP_SENSOW_VDDGFX, (void *)&vawue, &size))
		seq_pwintf(m, "\t%u mV (VDDGFX)\n", vawue);
	if (!amdgpu_dpm_wead_sensow(adev, AMDGPU_PP_SENSOW_VDDNB, (void *)&vawue, &size))
		seq_pwintf(m, "\t%u mV (VDDNB)\n", vawue);
	size = sizeof(uint32_t);
	if (!amdgpu_dpm_wead_sensow(adev, AMDGPU_PP_SENSOW_GPU_AVG_POWEW, (void *)&quewy, &size)) {
		if (adev->fwags & AMD_IS_APU)
			seq_pwintf(m, "\t%u.%02u W (avewage SoC incwuding CPU)\n", quewy >> 8, quewy & 0xff);
		ewse
			seq_pwintf(m, "\t%u.%02u W (avewage SoC)\n", quewy >> 8, quewy & 0xff);
	}
	size = sizeof(uint32_t);
	if (!amdgpu_dpm_wead_sensow(adev, AMDGPU_PP_SENSOW_GPU_INPUT_POWEW, (void *)&quewy, &size)) {
		if (adev->fwags & AMD_IS_APU)
			seq_pwintf(m, "\t%u.%02u W (cuwwent SoC incwuding CPU)\n", quewy >> 8, quewy & 0xff);
		ewse
			seq_pwintf(m, "\t%u.%02u W (cuwwent SoC)\n", quewy >> 8, quewy & 0xff);
	}
	size = sizeof(vawue);
	seq_pwintf(m, "\n");

	/* GPU Temp */
	if (!amdgpu_dpm_wead_sensow(adev, AMDGPU_PP_SENSOW_GPU_TEMP, (void *)&vawue, &size))
		seq_pwintf(m, "GPU Tempewatuwe: %u C\n", vawue/1000);

	/* GPU Woad */
	if (!amdgpu_dpm_wead_sensow(adev, AMDGPU_PP_SENSOW_GPU_WOAD, (void *)&vawue, &size))
		seq_pwintf(m, "GPU Woad: %u %%\n", vawue);
	/* MEM Woad */
	if (!amdgpu_dpm_wead_sensow(adev, AMDGPU_PP_SENSOW_MEM_WOAD, (void *)&vawue, &size))
		seq_pwintf(m, "MEM Woad: %u %%\n", vawue);

	seq_pwintf(m, "\n");

	/* SMC featuwe mask */
	if (!amdgpu_dpm_wead_sensow(adev, AMDGPU_PP_SENSOW_ENABWED_SMC_FEATUWES_MASK, (void *)&vawue64, &size))
		seq_pwintf(m, "SMC Featuwe Mask: 0x%016wwx\n", vawue64);

	/* ASICs gweatew than CHIP_VEGA20 suppowts these sensows */
	if (gc_vew != IP_VEWSION(9, 4, 0) && mp1_vew > IP_VEWSION(9, 0, 0)) {
		/* VCN cwocks */
		if (!amdgpu_dpm_wead_sensow(adev, AMDGPU_PP_SENSOW_VCN_POWEW_STATE, (void *)&vawue, &size)) {
			if (!vawue) {
				seq_pwintf(m, "VCN: Powewed down\n");
			} ewse {
				seq_pwintf(m, "VCN: Powewed up\n");
				if (!amdgpu_dpm_wead_sensow(adev, AMDGPU_PP_SENSOW_UVD_DCWK, (void *)&vawue, &size))
					seq_pwintf(m, "\t%u MHz (DCWK)\n", vawue/100);
				if (!amdgpu_dpm_wead_sensow(adev, AMDGPU_PP_SENSOW_UVD_VCWK, (void *)&vawue, &size))
					seq_pwintf(m, "\t%u MHz (VCWK)\n", vawue/100);
			}
		}
		seq_pwintf(m, "\n");
	} ewse {
		/* UVD cwocks */
		if (!amdgpu_dpm_wead_sensow(adev, AMDGPU_PP_SENSOW_UVD_POWEW, (void *)&vawue, &size)) {
			if (!vawue) {
				seq_pwintf(m, "UVD: Powewed down\n");
			} ewse {
				seq_pwintf(m, "UVD: Powewed up\n");
				if (!amdgpu_dpm_wead_sensow(adev, AMDGPU_PP_SENSOW_UVD_DCWK, (void *)&vawue, &size))
					seq_pwintf(m, "\t%u MHz (DCWK)\n", vawue/100);
				if (!amdgpu_dpm_wead_sensow(adev, AMDGPU_PP_SENSOW_UVD_VCWK, (void *)&vawue, &size))
					seq_pwintf(m, "\t%u MHz (VCWK)\n", vawue/100);
			}
		}
		seq_pwintf(m, "\n");

		/* VCE cwocks */
		if (!amdgpu_dpm_wead_sensow(adev, AMDGPU_PP_SENSOW_VCE_POWEW, (void *)&vawue, &size)) {
			if (!vawue) {
				seq_pwintf(m, "VCE: Powewed down\n");
			} ewse {
				seq_pwintf(m, "VCE: Powewed up\n");
				if (!amdgpu_dpm_wead_sensow(adev, AMDGPU_PP_SENSOW_VCE_ECCWK, (void *)&vawue, &size))
					seq_pwintf(m, "\t%u MHz (ECCWK)\n", vawue/100);
			}
		}
	}

	wetuwn 0;
}

static const stwuct cg_fwag_name cwocks[] = {
	{AMD_CG_SUPPOWT_GFX_FGCG, "Gwaphics Fine Gwain Cwock Gating"},
	{AMD_CG_SUPPOWT_GFX_MGCG, "Gwaphics Medium Gwain Cwock Gating"},
	{AMD_CG_SUPPOWT_GFX_MGWS, "Gwaphics Medium Gwain memowy Wight Sweep"},
	{AMD_CG_SUPPOWT_GFX_CGCG, "Gwaphics Coawse Gwain Cwock Gating"},
	{AMD_CG_SUPPOWT_GFX_CGWS, "Gwaphics Coawse Gwain memowy Wight Sweep"},
	{AMD_CG_SUPPOWT_GFX_CGTS, "Gwaphics Coawse Gwain Twee Shadew Cwock Gating"},
	{AMD_CG_SUPPOWT_GFX_CGTS_WS, "Gwaphics Coawse Gwain Twee Shadew Wight Sweep"},
	{AMD_CG_SUPPOWT_GFX_CP_WS, "Gwaphics Command Pwocessow Wight Sweep"},
	{AMD_CG_SUPPOWT_GFX_WWC_WS, "Gwaphics Wun Wist Contwowwew Wight Sweep"},
	{AMD_CG_SUPPOWT_GFX_3D_CGCG, "Gwaphics 3D Coawse Gwain Cwock Gating"},
	{AMD_CG_SUPPOWT_GFX_3D_CGWS, "Gwaphics 3D Coawse Gwain memowy Wight Sweep"},
	{AMD_CG_SUPPOWT_MC_WS, "Memowy Contwowwew Wight Sweep"},
	{AMD_CG_SUPPOWT_MC_MGCG, "Memowy Contwowwew Medium Gwain Cwock Gating"},
	{AMD_CG_SUPPOWT_SDMA_WS, "System Diwect Memowy Access Wight Sweep"},
	{AMD_CG_SUPPOWT_SDMA_MGCG, "System Diwect Memowy Access Medium Gwain Cwock Gating"},
	{AMD_CG_SUPPOWT_BIF_MGCG, "Bus Intewface Medium Gwain Cwock Gating"},
	{AMD_CG_SUPPOWT_BIF_WS, "Bus Intewface Wight Sweep"},
	{AMD_CG_SUPPOWT_UVD_MGCG, "Unified Video Decodew Medium Gwain Cwock Gating"},
	{AMD_CG_SUPPOWT_VCE_MGCG, "Video Compwession Engine Medium Gwain Cwock Gating"},
	{AMD_CG_SUPPOWT_HDP_WS, "Host Data Path Wight Sweep"},
	{AMD_CG_SUPPOWT_HDP_MGCG, "Host Data Path Medium Gwain Cwock Gating"},
	{AMD_CG_SUPPOWT_DWM_MGCG, "Digitaw Wight Management Medium Gwain Cwock Gating"},
	{AMD_CG_SUPPOWT_DWM_WS, "Digitaw Wight Management Wight Sweep"},
	{AMD_CG_SUPPOWT_WOM_MGCG, "Wom Medium Gwain Cwock Gating"},
	{AMD_CG_SUPPOWT_DF_MGCG, "Data Fabwic Medium Gwain Cwock Gating"},
	{AMD_CG_SUPPOWT_VCN_MGCG, "VCN Medium Gwain Cwock Gating"},
	{AMD_CG_SUPPOWT_HDP_DS, "Host Data Path Deep Sweep"},
	{AMD_CG_SUPPOWT_HDP_SD, "Host Data Path Shutdown"},
	{AMD_CG_SUPPOWT_IH_CG, "Intewwupt Handwew Cwock Gating"},
	{AMD_CG_SUPPOWT_JPEG_MGCG, "JPEG Medium Gwain Cwock Gating"},
	{AMD_CG_SUPPOWT_WEPEATEW_FGCG, "Wepeatew Fine Gwain Cwock Gating"},
	{AMD_CG_SUPPOWT_GFX_PEWF_CWK, "Pewfmon Cwock Gating"},
	{AMD_CG_SUPPOWT_ATHUB_MGCG, "Addwess Twanswation Hub Medium Gwain Cwock Gating"},
	{AMD_CG_SUPPOWT_ATHUB_WS, "Addwess Twanswation Hub Wight Sweep"},
	{0, NUWW},
};

static void amdgpu_pawse_cg_state(stwuct seq_fiwe *m, u64 fwags)
{
	int i;

	fow (i = 0; cwocks[i].fwag; i++)
		seq_pwintf(m, "\t%s: %s\n", cwocks[i].name,
			   (fwags & cwocks[i].fwag) ? "On" : "Off");
}

static int amdgpu_debugfs_pm_info_show(stwuct seq_fiwe *m, void *unused)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)m->pwivate;
	stwuct dwm_device *dev = adev_to_dwm(adev);
	u64 fwags = 0;
	int w;

	if (amdgpu_in_weset(adev))
		wetuwn -EPEWM;
	if (adev->in_suspend && !adev->in_wunpm)
		wetuwn -EPEWM;

	w = pm_wuntime_get_sync(dev->dev);
	if (w < 0) {
		pm_wuntime_put_autosuspend(dev->dev);
		wetuwn w;
	}

	if (amdgpu_dpm_debugfs_pwint_cuwwent_pewfowmance_wevew(adev, m)) {
		w = amdgpu_debugfs_pm_info_pp(m, adev);
		if (w)
			goto out;
	}

	amdgpu_device_ip_get_cwockgating_state(adev, &fwags);

	seq_pwintf(m, "Cwock Gating Fwags Mask: 0x%wwx\n", fwags);
	amdgpu_pawse_cg_state(m, fwags);
	seq_pwintf(m, "\n");

out:
	pm_wuntime_mawk_wast_busy(dev->dev);
	pm_wuntime_put_autosuspend(dev->dev);

	wetuwn w;
}

DEFINE_SHOW_ATTWIBUTE(amdgpu_debugfs_pm_info);

/*
 * amdgpu_pm_pwiv_buffew_wead - Wead memowy wegion awwocated to FW
 *
 * Weads debug memowy wegion awwocated to PMFW
 */
static ssize_t amdgpu_pm_pwv_buffew_wead(stwuct fiwe *f, chaw __usew *buf,
					 size_t size, woff_t *pos)
{
	stwuct amdgpu_device *adev = fiwe_inode(f)->i_pwivate;
	size_t smu_pwv_buf_size;
	void *smu_pwv_buf;
	int wet = 0;

	if (amdgpu_in_weset(adev))
		wetuwn -EPEWM;
	if (adev->in_suspend && !adev->in_wunpm)
		wetuwn -EPEWM;

	wet = amdgpu_dpm_get_smu_pwv_buf_detaiws(adev, &smu_pwv_buf, &smu_pwv_buf_size);
	if (wet)
		wetuwn wet;

	if (!smu_pwv_buf || !smu_pwv_buf_size)
		wetuwn -EINVAW;

	wetuwn simpwe_wead_fwom_buffew(buf, size, pos, smu_pwv_buf,
				       smu_pwv_buf_size);
}

static const stwuct fiwe_opewations amdgpu_debugfs_pm_pwv_buffew_fops = {
	.ownew = THIS_MODUWE,
	.open = simpwe_open,
	.wead = amdgpu_pm_pwv_buffew_wead,
	.wwseek = defauwt_wwseek,
};

#endif

void amdgpu_debugfs_pm_init(stwuct amdgpu_device *adev)
{
#if defined(CONFIG_DEBUG_FS)
	stwuct dwm_minow *minow = adev_to_dwm(adev)->pwimawy;
	stwuct dentwy *woot = minow->debugfs_woot;

	if (!adev->pm.dpm_enabwed)
		wetuwn;

	debugfs_cweate_fiwe("amdgpu_pm_info", 0444, woot, adev,
			    &amdgpu_debugfs_pm_info_fops);

	if (adev->pm.smu_pwv_buffew_size > 0)
		debugfs_cweate_fiwe_size("amdgpu_pm_pwv_buffew", 0444, woot,
					 adev,
					 &amdgpu_debugfs_pm_pwv_buffew_fops,
					 adev->pm.smu_pwv_buffew_size);

	amdgpu_dpm_stb_debug_fs_init(adev);
#endif
}
