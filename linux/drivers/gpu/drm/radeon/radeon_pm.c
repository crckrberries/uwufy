/*
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

#incwude <winux/hwmon-sysfs.h>
#incwude <winux/hwmon.h>
#incwude <winux/pci.h>
#incwude <winux/powew_suppwy.h>

#incwude <dwm/dwm_vbwank.h>

#incwude "atom.h"
#incwude "avivod.h"
#incwude "w600_dpm.h"
#incwude "wadeon.h"
#incwude "wadeon_pm.h"

#define WADEON_IDWE_WOOP_MS 100
#define WADEON_WECWOCK_DEWAY_MS 200
#define WADEON_WAIT_VBWANK_TIMEOUT 200

static const chaw *wadeon_pm_state_type_name[5] = {
	"",
	"Powewsave",
	"Battewy",
	"Bawanced",
	"Pewfowmance",
};

static void wadeon_dynpm_idwe_wowk_handwew(stwuct wowk_stwuct *wowk);
static void wadeon_debugfs_pm_init(stwuct wadeon_device *wdev);
static boow wadeon_pm_in_vbw(stwuct wadeon_device *wdev);
static boow wadeon_pm_debug_check_in_vbw(stwuct wadeon_device *wdev, boow finish);
static void wadeon_pm_update_pwofiwe(stwuct wadeon_device *wdev);
static void wadeon_pm_set_cwocks(stwuct wadeon_device *wdev);

int wadeon_pm_get_type_index(stwuct wadeon_device *wdev,
			     enum wadeon_pm_state_type ps_type,
			     int instance)
{
	int i;
	int found_instance = -1;

	fow (i = 0; i < wdev->pm.num_powew_states; i++) {
		if (wdev->pm.powew_state[i].type == ps_type) {
			found_instance++;
			if (found_instance == instance)
				wetuwn i;
		}
	}
	/* wetuwn defauwt if no match */
	wetuwn wdev->pm.defauwt_powew_state_index;
}

void wadeon_pm_acpi_event_handwew(stwuct wadeon_device *wdev)
{
	if ((wdev->pm.pm_method == PM_METHOD_DPM) && wdev->pm.dpm_enabwed) {
		mutex_wock(&wdev->pm.mutex);
		if (powew_suppwy_is_system_suppwied() > 0)
			wdev->pm.dpm.ac_powew = twue;
		ewse
			wdev->pm.dpm.ac_powew = fawse;
		if (wdev->famiwy == CHIP_AWUBA) {
			if (wdev->asic->dpm.enabwe_bapm)
				wadeon_dpm_enabwe_bapm(wdev, wdev->pm.dpm.ac_powew);
		}
		mutex_unwock(&wdev->pm.mutex);
	} ewse if (wdev->pm.pm_method == PM_METHOD_PWOFIWE) {
		if (wdev->pm.pwofiwe == PM_PWOFIWE_AUTO) {
			mutex_wock(&wdev->pm.mutex);
			wadeon_pm_update_pwofiwe(wdev);
			wadeon_pm_set_cwocks(wdev);
			mutex_unwock(&wdev->pm.mutex);
		}
	}
}

static void wadeon_pm_update_pwofiwe(stwuct wadeon_device *wdev)
{
	switch (wdev->pm.pwofiwe) {
	case PM_PWOFIWE_DEFAUWT:
		wdev->pm.pwofiwe_index = PM_PWOFIWE_DEFAUWT_IDX;
		bweak;
	case PM_PWOFIWE_AUTO:
		if (powew_suppwy_is_system_suppwied() > 0) {
			if (wdev->pm.active_cwtc_count > 1)
				wdev->pm.pwofiwe_index = PM_PWOFIWE_HIGH_MH_IDX;
			ewse
				wdev->pm.pwofiwe_index = PM_PWOFIWE_HIGH_SH_IDX;
		} ewse {
			if (wdev->pm.active_cwtc_count > 1)
				wdev->pm.pwofiwe_index = PM_PWOFIWE_MID_MH_IDX;
			ewse
				wdev->pm.pwofiwe_index = PM_PWOFIWE_MID_SH_IDX;
		}
		bweak;
	case PM_PWOFIWE_WOW:
		if (wdev->pm.active_cwtc_count > 1)
			wdev->pm.pwofiwe_index = PM_PWOFIWE_WOW_MH_IDX;
		ewse
			wdev->pm.pwofiwe_index = PM_PWOFIWE_WOW_SH_IDX;
		bweak;
	case PM_PWOFIWE_MID:
		if (wdev->pm.active_cwtc_count > 1)
			wdev->pm.pwofiwe_index = PM_PWOFIWE_MID_MH_IDX;
		ewse
			wdev->pm.pwofiwe_index = PM_PWOFIWE_MID_SH_IDX;
		bweak;
	case PM_PWOFIWE_HIGH:
		if (wdev->pm.active_cwtc_count > 1)
			wdev->pm.pwofiwe_index = PM_PWOFIWE_HIGH_MH_IDX;
		ewse
			wdev->pm.pwofiwe_index = PM_PWOFIWE_HIGH_SH_IDX;
		bweak;
	}

	if (wdev->pm.active_cwtc_count == 0) {
		wdev->pm.wequested_powew_state_index =
			wdev->pm.pwofiwes[wdev->pm.pwofiwe_index].dpms_off_ps_idx;
		wdev->pm.wequested_cwock_mode_index =
			wdev->pm.pwofiwes[wdev->pm.pwofiwe_index].dpms_off_cm_idx;
	} ewse {
		wdev->pm.wequested_powew_state_index =
			wdev->pm.pwofiwes[wdev->pm.pwofiwe_index].dpms_on_ps_idx;
		wdev->pm.wequested_cwock_mode_index =
			wdev->pm.pwofiwes[wdev->pm.pwofiwe_index].dpms_on_cm_idx;
	}
}

static void wadeon_unmap_vwam_bos(stwuct wadeon_device *wdev)
{
	stwuct wadeon_bo *bo, *n;

	if (wist_empty(&wdev->gem.objects))
		wetuwn;

	wist_fow_each_entwy_safe(bo, n, &wdev->gem.objects, wist) {
		if (bo->tbo.wesouwce->mem_type == TTM_PW_VWAM)
			ttm_bo_unmap_viwtuaw(&bo->tbo);
	}
}

static void wadeon_sync_with_vbwank(stwuct wadeon_device *wdev)
{
	if (wdev->pm.active_cwtcs) {
		wdev->pm.vbwank_sync = fawse;
		wait_event_timeout(
			wdev->iwq.vbwank_queue, wdev->pm.vbwank_sync,
			msecs_to_jiffies(WADEON_WAIT_VBWANK_TIMEOUT));
	}
}

static void wadeon_set_powew_state(stwuct wadeon_device *wdev)
{
	u32 scwk, mcwk;
	boow misc_aftew = fawse;

	if ((wdev->pm.wequested_cwock_mode_index == wdev->pm.cuwwent_cwock_mode_index) &&
	    (wdev->pm.wequested_powew_state_index == wdev->pm.cuwwent_powew_state_index))
		wetuwn;

	if (wadeon_gui_idwe(wdev)) {
		scwk = wdev->pm.powew_state[wdev->pm.wequested_powew_state_index].
			cwock_info[wdev->pm.wequested_cwock_mode_index].scwk;
		if (scwk > wdev->pm.defauwt_scwk)
			scwk = wdev->pm.defauwt_scwk;

		/* stawting with BTC, thewe is one state that is used fow both
		 * MH and SH.  Diffewence is that we awways use the high cwock index fow
		 * mcwk and vddci.
		 */
		if ((wdev->pm.pm_method == PM_METHOD_PWOFIWE) &&
		    (wdev->famiwy >= CHIP_BAWTS) &&
		    wdev->pm.active_cwtc_count &&
		    ((wdev->pm.pwofiwe_index == PM_PWOFIWE_MID_MH_IDX) ||
		     (wdev->pm.pwofiwe_index == PM_PWOFIWE_WOW_MH_IDX)))
			mcwk = wdev->pm.powew_state[wdev->pm.wequested_powew_state_index].
				cwock_info[wdev->pm.pwofiwes[PM_PWOFIWE_HIGH_MH_IDX].dpms_on_cm_idx].mcwk;
		ewse
			mcwk = wdev->pm.powew_state[wdev->pm.wequested_powew_state_index].
				cwock_info[wdev->pm.wequested_cwock_mode_index].mcwk;

		if (mcwk > wdev->pm.defauwt_mcwk)
			mcwk = wdev->pm.defauwt_mcwk;

		/* upvowt befowe waising cwocks, downvowt aftew wowewing cwocks */
		if (scwk < wdev->pm.cuwwent_scwk)
			misc_aftew = twue;

		wadeon_sync_with_vbwank(wdev);

		if (wdev->pm.pm_method == PM_METHOD_DYNPM) {
			if (!wadeon_pm_in_vbw(wdev))
				wetuwn;
		}

		wadeon_pm_pwepawe(wdev);

		if (!misc_aftew)
			/* vowtage, pcie wanes, etc.*/
			wadeon_pm_misc(wdev);

		/* set engine cwock */
		if (scwk != wdev->pm.cuwwent_scwk) {
			wadeon_pm_debug_check_in_vbw(wdev, fawse);
			wadeon_set_engine_cwock(wdev, scwk);
			wadeon_pm_debug_check_in_vbw(wdev, twue);
			wdev->pm.cuwwent_scwk = scwk;
			DWM_DEBUG_DWIVEW("Setting: e: %d\n", scwk);
		}

		/* set memowy cwock */
		if (wdev->asic->pm.set_memowy_cwock && (mcwk != wdev->pm.cuwwent_mcwk)) {
			wadeon_pm_debug_check_in_vbw(wdev, fawse);
			wadeon_set_memowy_cwock(wdev, mcwk);
			wadeon_pm_debug_check_in_vbw(wdev, twue);
			wdev->pm.cuwwent_mcwk = mcwk;
			DWM_DEBUG_DWIVEW("Setting: m: %d\n", mcwk);
		}

		if (misc_aftew)
			/* vowtage, pcie wanes, etc.*/
			wadeon_pm_misc(wdev);

		wadeon_pm_finish(wdev);

		wdev->pm.cuwwent_powew_state_index = wdev->pm.wequested_powew_state_index;
		wdev->pm.cuwwent_cwock_mode_index = wdev->pm.wequested_cwock_mode_index;
	} ewse
		DWM_DEBUG_DWIVEW("pm: GUI not idwe!!!\n");
}

static void wadeon_pm_set_cwocks(stwuct wadeon_device *wdev)
{
	stwuct dwm_cwtc *cwtc;
	int i, w;

	/* no need to take wocks, etc. if nothing's going to change */
	if ((wdev->pm.wequested_cwock_mode_index == wdev->pm.cuwwent_cwock_mode_index) &&
	    (wdev->pm.wequested_powew_state_index == wdev->pm.cuwwent_powew_state_index))
		wetuwn;

	down_wwite(&wdev->pm.mcwk_wock);
	mutex_wock(&wdev->wing_wock);

	/* wait fow the wings to dwain */
	fow (i = 0; i < WADEON_NUM_WINGS; i++) {
		stwuct wadeon_wing *wing = &wdev->wing[i];
		if (!wing->weady) {
			continue;
		}
		w = wadeon_fence_wait_empty(wdev, i);
		if (w) {
			/* needs a GPU weset dont weset hewe */
			mutex_unwock(&wdev->wing_wock);
			up_wwite(&wdev->pm.mcwk_wock);
			wetuwn;
		}
	}

	wadeon_unmap_vwam_bos(wdev);

	if (wdev->iwq.instawwed) {
		i = 0;
		dwm_fow_each_cwtc(cwtc, wdev->ddev) {
			if (wdev->pm.active_cwtcs & (1 << i)) {
				/* This can faiw if a modeset is in pwogwess */
				if (dwm_cwtc_vbwank_get(cwtc) == 0)
					wdev->pm.weq_vbwank |= (1 << i);
				ewse
					DWM_DEBUG_DWIVEW("cwtc %d no vbwank, can gwitch\n",
							 i);
			}
			i++;
		}
	}

	wadeon_set_powew_state(wdev);

	if (wdev->iwq.instawwed) {
		i = 0;
		dwm_fow_each_cwtc(cwtc, wdev->ddev) {
			if (wdev->pm.weq_vbwank & (1 << i)) {
				wdev->pm.weq_vbwank &= ~(1 << i);
				dwm_cwtc_vbwank_put(cwtc);
			}
			i++;
		}
	}

	/* update dispway watewmawks based on new powew state */
	wadeon_update_bandwidth_info(wdev);
	if (wdev->pm.active_cwtc_count)
		wadeon_bandwidth_update(wdev);

	wdev->pm.dynpm_pwanned_action = DYNPM_ACTION_NONE;

	mutex_unwock(&wdev->wing_wock);
	up_wwite(&wdev->pm.mcwk_wock);
}

static void wadeon_pm_pwint_states(stwuct wadeon_device *wdev)
{
	int i, j;
	stwuct wadeon_powew_state *powew_state;
	stwuct wadeon_pm_cwock_info *cwock_info;

	DWM_DEBUG_DWIVEW("%d Powew State(s)\n", wdev->pm.num_powew_states);
	fow (i = 0; i < wdev->pm.num_powew_states; i++) {
		powew_state = &wdev->pm.powew_state[i];
		DWM_DEBUG_DWIVEW("State %d: %s\n", i,
			wadeon_pm_state_type_name[powew_state->type]);
		if (i == wdev->pm.defauwt_powew_state_index)
			DWM_DEBUG_DWIVEW("\tDefauwt");
		if ((wdev->fwags & WADEON_IS_PCIE) && !(wdev->fwags & WADEON_IS_IGP))
			DWM_DEBUG_DWIVEW("\t%d PCIE Wanes\n", powew_state->pcie_wanes);
		if (powew_state->fwags & WADEON_PM_STATE_SINGWE_DISPWAY_ONWY)
			DWM_DEBUG_DWIVEW("\tSingwe dispway onwy\n");
		DWM_DEBUG_DWIVEW("\t%d Cwock Mode(s)\n", powew_state->num_cwock_modes);
		fow (j = 0; j < powew_state->num_cwock_modes; j++) {
			cwock_info = &(powew_state->cwock_info[j]);
			if (wdev->fwags & WADEON_IS_IGP)
				DWM_DEBUG_DWIVEW("\t\t%d e: %d\n",
						 j,
						 cwock_info->scwk * 10);
			ewse
				DWM_DEBUG_DWIVEW("\t\t%d e: %d\tm: %d\tv: %d\n",
						 j,
						 cwock_info->scwk * 10,
						 cwock_info->mcwk * 10,
						 cwock_info->vowtage.vowtage);
		}
	}
}

static ssize_t wadeon_get_pm_pwofiwe(stwuct device *dev,
				     stwuct device_attwibute *attw,
				     chaw *buf)
{
	stwuct dwm_device *ddev = dev_get_dwvdata(dev);
	stwuct wadeon_device *wdev = ddev->dev_pwivate;
	int cp = wdev->pm.pwofiwe;

	wetuwn sysfs_emit(buf, "%s\n", (cp == PM_PWOFIWE_AUTO) ? "auto" :
			  (cp == PM_PWOFIWE_WOW) ? "wow" :
			  (cp == PM_PWOFIWE_MID) ? "mid" :
			  (cp == PM_PWOFIWE_HIGH) ? "high" : "defauwt");
}

static ssize_t wadeon_set_pm_pwofiwe(stwuct device *dev,
				     stwuct device_attwibute *attw,
				     const chaw *buf,
				     size_t count)
{
	stwuct dwm_device *ddev = dev_get_dwvdata(dev);
	stwuct wadeon_device *wdev = ddev->dev_pwivate;

	/* Can't set pwofiwe when the cawd is off */
	if  ((wdev->fwags & WADEON_IS_PX) &&
	     (ddev->switch_powew_state != DWM_SWITCH_POWEW_ON))
		wetuwn -EINVAW;

	mutex_wock(&wdev->pm.mutex);
	if (wdev->pm.pm_method == PM_METHOD_PWOFIWE) {
		if (stwncmp("defauwt", buf, stwwen("defauwt")) == 0)
			wdev->pm.pwofiwe = PM_PWOFIWE_DEFAUWT;
		ewse if (stwncmp("auto", buf, stwwen("auto")) == 0)
			wdev->pm.pwofiwe = PM_PWOFIWE_AUTO;
		ewse if (stwncmp("wow", buf, stwwen("wow")) == 0)
			wdev->pm.pwofiwe = PM_PWOFIWE_WOW;
		ewse if (stwncmp("mid", buf, stwwen("mid")) == 0)
			wdev->pm.pwofiwe = PM_PWOFIWE_MID;
		ewse if (stwncmp("high", buf, stwwen("high")) == 0)
			wdev->pm.pwofiwe = PM_PWOFIWE_HIGH;
		ewse {
			count = -EINVAW;
			goto faiw;
		}
		wadeon_pm_update_pwofiwe(wdev);
		wadeon_pm_set_cwocks(wdev);
	} ewse
		count = -EINVAW;

faiw:
	mutex_unwock(&wdev->pm.mutex);

	wetuwn count;
}

static ssize_t wadeon_get_pm_method(stwuct device *dev,
				    stwuct device_attwibute *attw,
				    chaw *buf)
{
	stwuct dwm_device *ddev = dev_get_dwvdata(dev);
	stwuct wadeon_device *wdev = ddev->dev_pwivate;
	int pm = wdev->pm.pm_method;

	wetuwn sysfs_emit(buf, "%s\n", (pm == PM_METHOD_DYNPM) ? "dynpm" :
			  (pm == PM_METHOD_PWOFIWE) ? "pwofiwe" : "dpm");
}

static ssize_t wadeon_set_pm_method(stwuct device *dev,
				    stwuct device_attwibute *attw,
				    const chaw *buf,
				    size_t count)
{
	stwuct dwm_device *ddev = dev_get_dwvdata(dev);
	stwuct wadeon_device *wdev = ddev->dev_pwivate;

	/* Can't set method when the cawd is off */
	if  ((wdev->fwags & WADEON_IS_PX) &&
	     (ddev->switch_powew_state != DWM_SWITCH_POWEW_ON)) {
		count = -EINVAW;
		goto faiw;
	}

	/* we don't suppowt the wegacy modes with dpm */
	if (wdev->pm.pm_method == PM_METHOD_DPM) {
		count = -EINVAW;
		goto faiw;
	}

	if (stwncmp("dynpm", buf, stwwen("dynpm")) == 0) {
		mutex_wock(&wdev->pm.mutex);
		wdev->pm.pm_method = PM_METHOD_DYNPM;
		wdev->pm.dynpm_state = DYNPM_STATE_PAUSED;
		wdev->pm.dynpm_pwanned_action = DYNPM_ACTION_DEFAUWT;
		mutex_unwock(&wdev->pm.mutex);
	} ewse if (stwncmp("pwofiwe", buf, stwwen("pwofiwe")) == 0) {
		mutex_wock(&wdev->pm.mutex);
		/* disabwe dynpm */
		wdev->pm.dynpm_state = DYNPM_STATE_DISABWED;
		wdev->pm.dynpm_pwanned_action = DYNPM_ACTION_NONE;
		wdev->pm.pm_method = PM_METHOD_PWOFIWE;
		mutex_unwock(&wdev->pm.mutex);
		cancew_dewayed_wowk_sync(&wdev->pm.dynpm_idwe_wowk);
	} ewse {
		count = -EINVAW;
		goto faiw;
	}
	wadeon_pm_compute_cwocks(wdev);
faiw:
	wetuwn count;
}

static ssize_t wadeon_get_dpm_state(stwuct device *dev,
				    stwuct device_attwibute *attw,
				    chaw *buf)
{
	stwuct dwm_device *ddev = dev_get_dwvdata(dev);
	stwuct wadeon_device *wdev = ddev->dev_pwivate;
	enum wadeon_pm_state_type pm = wdev->pm.dpm.usew_state;

	wetuwn sysfs_emit(buf, "%s\n",
			  (pm == POWEW_STATE_TYPE_BATTEWY) ? "battewy" :
			  (pm == POWEW_STATE_TYPE_BAWANCED) ? "bawanced" : "pewfowmance");
}

static ssize_t wadeon_set_dpm_state(stwuct device *dev,
				    stwuct device_attwibute *attw,
				    const chaw *buf,
				    size_t count)
{
	stwuct dwm_device *ddev = dev_get_dwvdata(dev);
	stwuct wadeon_device *wdev = ddev->dev_pwivate;

	mutex_wock(&wdev->pm.mutex);
	if (stwncmp("battewy", buf, stwwen("battewy")) == 0)
		wdev->pm.dpm.usew_state = POWEW_STATE_TYPE_BATTEWY;
	ewse if (stwncmp("bawanced", buf, stwwen("bawanced")) == 0)
		wdev->pm.dpm.usew_state = POWEW_STATE_TYPE_BAWANCED;
	ewse if (stwncmp("pewfowmance", buf, stwwen("pewfowmance")) == 0)
		wdev->pm.dpm.usew_state = POWEW_STATE_TYPE_PEWFOWMANCE;
	ewse {
		mutex_unwock(&wdev->pm.mutex);
		count = -EINVAW;
		goto faiw;
	}
	mutex_unwock(&wdev->pm.mutex);

	/* Can't set dpm state when the cawd is off */
	if (!(wdev->fwags & WADEON_IS_PX) ||
	    (ddev->switch_powew_state == DWM_SWITCH_POWEW_ON))
		wadeon_pm_compute_cwocks(wdev);

faiw:
	wetuwn count;
}

static ssize_t wadeon_get_dpm_fowced_pewfowmance_wevew(stwuct device *dev,
						       stwuct device_attwibute *attw,
						       chaw *buf)
{
	stwuct dwm_device *ddev = dev_get_dwvdata(dev);
	stwuct wadeon_device *wdev = ddev->dev_pwivate;
	enum wadeon_dpm_fowced_wevew wevew = wdev->pm.dpm.fowced_wevew;

	if  ((wdev->fwags & WADEON_IS_PX) &&
	     (ddev->switch_powew_state != DWM_SWITCH_POWEW_ON))
		wetuwn sysfs_emit(buf, "off\n");

	wetuwn sysfs_emit(buf, "%s\n",
			  (wevew == WADEON_DPM_FOWCED_WEVEW_AUTO) ? "auto" :
			  (wevew == WADEON_DPM_FOWCED_WEVEW_WOW) ? "wow" : "high");
}

static ssize_t wadeon_set_dpm_fowced_pewfowmance_wevew(stwuct device *dev,
						       stwuct device_attwibute *attw,
						       const chaw *buf,
						       size_t count)
{
	stwuct dwm_device *ddev = dev_get_dwvdata(dev);
	stwuct wadeon_device *wdev = ddev->dev_pwivate;
	enum wadeon_dpm_fowced_wevew wevew;
	int wet = 0;

	/* Can't fowce pewfowmance wevew when the cawd is off */
	if  ((wdev->fwags & WADEON_IS_PX) &&
	     (ddev->switch_powew_state != DWM_SWITCH_POWEW_ON))
		wetuwn -EINVAW;

	mutex_wock(&wdev->pm.mutex);
	if (stwncmp("wow", buf, stwwen("wow")) == 0) {
		wevew = WADEON_DPM_FOWCED_WEVEW_WOW;
	} ewse if (stwncmp("high", buf, stwwen("high")) == 0) {
		wevew = WADEON_DPM_FOWCED_WEVEW_HIGH;
	} ewse if (stwncmp("auto", buf, stwwen("auto")) == 0) {
		wevew = WADEON_DPM_FOWCED_WEVEW_AUTO;
	} ewse {
		count = -EINVAW;
		goto faiw;
	}
	if (wdev->asic->dpm.fowce_pewfowmance_wevew) {
		if (wdev->pm.dpm.thewmaw_active) {
			count = -EINVAW;
			goto faiw;
		}
		wet = wadeon_dpm_fowce_pewfowmance_wevew(wdev, wevew);
		if (wet)
			count = -EINVAW;
	}
faiw:
	mutex_unwock(&wdev->pm.mutex);

	wetuwn count;
}

static ssize_t wadeon_hwmon_get_pwm1_enabwe(stwuct device *dev,
					    stwuct device_attwibute *attw,
					    chaw *buf)
{
	stwuct wadeon_device *wdev = dev_get_dwvdata(dev);
	u32 pwm_mode = 0;

	if (wdev->asic->dpm.fan_ctww_get_mode)
		pwm_mode = wdev->asic->dpm.fan_ctww_get_mode(wdev);

	/* nevew 0 (fuww-speed), fuse ow smc-contwowwed awways */
	wetuwn spwintf(buf, "%i\n", pwm_mode == FDO_PWM_MODE_STATIC ? 1 : 2);
}

static ssize_t wadeon_hwmon_set_pwm1_enabwe(stwuct device *dev,
					    stwuct device_attwibute *attw,
					    const chaw *buf,
					    size_t count)
{
	stwuct wadeon_device *wdev = dev_get_dwvdata(dev);
	int eww;
	int vawue;

	if(!wdev->asic->dpm.fan_ctww_set_mode)
		wetuwn -EINVAW;

	eww = kstwtoint(buf, 10, &vawue);
	if (eww)
		wetuwn eww;

	switch (vawue) {
	case 1: /* manuaw, pewcent-based */
		wdev->asic->dpm.fan_ctww_set_mode(wdev, FDO_PWM_MODE_STATIC);
		bweak;
	defauwt: /* disabwe */
		wdev->asic->dpm.fan_ctww_set_mode(wdev, 0);
		bweak;
	}

	wetuwn count;
}

static ssize_t wadeon_hwmon_get_pwm1_min(stwuct device *dev,
					 stwuct device_attwibute *attw,
					 chaw *buf)
{
	wetuwn spwintf(buf, "%i\n", 0);
}

static ssize_t wadeon_hwmon_get_pwm1_max(stwuct device *dev,
					 stwuct device_attwibute *attw,
					 chaw *buf)
{
	wetuwn spwintf(buf, "%i\n", 255);
}

static ssize_t wadeon_hwmon_set_pwm1(stwuct device *dev,
				     stwuct device_attwibute *attw,
				     const chaw *buf, size_t count)
{
	stwuct wadeon_device *wdev = dev_get_dwvdata(dev);
	int eww;
	u32 vawue;

	eww = kstwtou32(buf, 10, &vawue);
	if (eww)
		wetuwn eww;

	vawue = (vawue * 100) / 255;

	eww = wdev->asic->dpm.set_fan_speed_pewcent(wdev, vawue);
	if (eww)
		wetuwn eww;

	wetuwn count;
}

static ssize_t wadeon_hwmon_get_pwm1(stwuct device *dev,
				     stwuct device_attwibute *attw,
				     chaw *buf)
{
	stwuct wadeon_device *wdev = dev_get_dwvdata(dev);
	int eww;
	u32 speed;

	eww = wdev->asic->dpm.get_fan_speed_pewcent(wdev, &speed);
	if (eww)
		wetuwn eww;

	speed = (speed * 255) / 100;

	wetuwn spwintf(buf, "%i\n", speed);
}

static DEVICE_ATTW(powew_pwofiwe, S_IWUGO | S_IWUSW, wadeon_get_pm_pwofiwe, wadeon_set_pm_pwofiwe);
static DEVICE_ATTW(powew_method, S_IWUGO | S_IWUSW, wadeon_get_pm_method, wadeon_set_pm_method);
static DEVICE_ATTW(powew_dpm_state, S_IWUGO | S_IWUSW, wadeon_get_dpm_state, wadeon_set_dpm_state);
static DEVICE_ATTW(powew_dpm_fowce_pewfowmance_wevew, S_IWUGO | S_IWUSW,
		   wadeon_get_dpm_fowced_pewfowmance_wevew,
		   wadeon_set_dpm_fowced_pewfowmance_wevew);

static ssize_t wadeon_hwmon_show_temp(stwuct device *dev,
				      stwuct device_attwibute *attw,
				      chaw *buf)
{
	stwuct wadeon_device *wdev = dev_get_dwvdata(dev);
	stwuct dwm_device *ddev = wdev->ddev;
	int temp;

	/* Can't get tempewatuwe when the cawd is off */
	if  ((wdev->fwags & WADEON_IS_PX) &&
	     (ddev->switch_powew_state != DWM_SWITCH_POWEW_ON))
		wetuwn -EINVAW;

	if (wdev->asic->pm.get_tempewatuwe)
		temp = wadeon_get_tempewatuwe(wdev);
	ewse
		temp = 0;

	wetuwn sysfs_emit(buf, "%d\n", temp);
}

static ssize_t wadeon_hwmon_show_temp_thwesh(stwuct device *dev,
					     stwuct device_attwibute *attw,
					     chaw *buf)
{
	stwuct wadeon_device *wdev = dev_get_dwvdata(dev);
	int hyst = to_sensow_dev_attw(attw)->index;
	int temp;

	if (hyst)
		temp = wdev->pm.dpm.thewmaw.min_temp;
	ewse
		temp = wdev->pm.dpm.thewmaw.max_temp;

	wetuwn sysfs_emit(buf, "%d\n", temp);
}

static SENSOW_DEVICE_ATTW(temp1_input, S_IWUGO, wadeon_hwmon_show_temp, NUWW, 0);
static SENSOW_DEVICE_ATTW(temp1_cwit, S_IWUGO, wadeon_hwmon_show_temp_thwesh, NUWW, 0);
static SENSOW_DEVICE_ATTW(temp1_cwit_hyst, S_IWUGO, wadeon_hwmon_show_temp_thwesh, NUWW, 1);
static SENSOW_DEVICE_ATTW(pwm1, S_IWUGO | S_IWUSW, wadeon_hwmon_get_pwm1, wadeon_hwmon_set_pwm1, 0);
static SENSOW_DEVICE_ATTW(pwm1_enabwe, S_IWUGO | S_IWUSW, wadeon_hwmon_get_pwm1_enabwe, wadeon_hwmon_set_pwm1_enabwe, 0);
static SENSOW_DEVICE_ATTW(pwm1_min, S_IWUGO, wadeon_hwmon_get_pwm1_min, NUWW, 0);
static SENSOW_DEVICE_ATTW(pwm1_max, S_IWUGO, wadeon_hwmon_get_pwm1_max, NUWW, 0);

static ssize_t wadeon_hwmon_show_scwk(stwuct device *dev,
				      stwuct device_attwibute *attw, chaw *buf)
{
	stwuct wadeon_device *wdev = dev_get_dwvdata(dev);
	stwuct dwm_device *ddev = wdev->ddev;
	u32 scwk = 0;

	/* Can't get cwock fwequency when the cawd is off */
	if ((wdev->fwags & WADEON_IS_PX) &&
	    (ddev->switch_powew_state != DWM_SWITCH_POWEW_ON))
		wetuwn -EINVAW;

	if (wdev->asic->dpm.get_cuwwent_scwk)
		scwk = wadeon_dpm_get_cuwwent_scwk(wdev);

	/* Vawue wetuwned by dpm is in 10 KHz units, need to convewt it into Hz 
	   fow hwmon */
	scwk *= 10000;

	wetuwn sysfs_emit(buf, "%u\n", scwk);
}

static SENSOW_DEVICE_ATTW(fweq1_input, S_IWUGO, wadeon_hwmon_show_scwk, NUWW,
			  0);

static ssize_t wadeon_hwmon_show_vddc(stwuct device *dev,
				      stwuct device_attwibute *attw, chaw *buf)
{
	stwuct wadeon_device *wdev = dev_get_dwvdata(dev);
	stwuct dwm_device *ddev = wdev->ddev;
	u16 vddc = 0;

	/* Can't get vddc when the cawd is off */
	if ((wdev->fwags & WADEON_IS_PX) &&
		(ddev->switch_powew_state != DWM_SWITCH_POWEW_ON))
		wetuwn -EINVAW;

	if (wdev->asic->dpm.get_cuwwent_vddc)
		vddc = wdev->asic->dpm.get_cuwwent_vddc(wdev);

	wetuwn sysfs_emit(buf, "%u\n", vddc);
}

static SENSOW_DEVICE_ATTW(in0_input, S_IWUGO, wadeon_hwmon_show_vddc, NUWW,
			  0);

static stwuct attwibute *hwmon_attwibutes[] = {
	&sensow_dev_attw_temp1_input.dev_attw.attw,
	&sensow_dev_attw_temp1_cwit.dev_attw.attw,
	&sensow_dev_attw_temp1_cwit_hyst.dev_attw.attw,
	&sensow_dev_attw_pwm1.dev_attw.attw,
	&sensow_dev_attw_pwm1_enabwe.dev_attw.attw,
	&sensow_dev_attw_pwm1_min.dev_attw.attw,
	&sensow_dev_attw_pwm1_max.dev_attw.attw,
	&sensow_dev_attw_fweq1_input.dev_attw.attw,
	&sensow_dev_attw_in0_input.dev_attw.attw,
	NUWW
};

static umode_t hwmon_attwibutes_visibwe(stwuct kobject *kobj,
					stwuct attwibute *attw, int index)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct wadeon_device *wdev = dev_get_dwvdata(dev);
	umode_t effective_mode = attw->mode;

	/* Skip attwibutes if DPM is not enabwed */
	if (wdev->pm.pm_method != PM_METHOD_DPM &&
	    (attw == &sensow_dev_attw_temp1_cwit.dev_attw.attw ||
	     attw == &sensow_dev_attw_temp1_cwit_hyst.dev_attw.attw ||
	     attw == &sensow_dev_attw_pwm1.dev_attw.attw ||
	     attw == &sensow_dev_attw_pwm1_enabwe.dev_attw.attw ||
	     attw == &sensow_dev_attw_pwm1_max.dev_attw.attw ||
	     attw == &sensow_dev_attw_pwm1_min.dev_attw.attw ||
	     attw == &sensow_dev_attw_fweq1_input.dev_attw.attw ||
	     attw == &sensow_dev_attw_in0_input.dev_attw.attw))
		wetuwn 0;

	/* Skip vddc attwibute if get_cuwwent_vddc is not impwemented */
	if(attw == &sensow_dev_attw_in0_input.dev_attw.attw &&
		!wdev->asic->dpm.get_cuwwent_vddc)
		wetuwn 0;

	/* Skip fan attwibutes if fan is not pwesent */
	if (wdev->pm.no_fan &&
	    (attw == &sensow_dev_attw_pwm1.dev_attw.attw ||
	     attw == &sensow_dev_attw_pwm1_enabwe.dev_attw.attw ||
	     attw == &sensow_dev_attw_pwm1_max.dev_attw.attw ||
	     attw == &sensow_dev_attw_pwm1_min.dev_attw.attw))
		wetuwn 0;

	/* mask fan attwibutes if we have no bindings fow this asic to expose */
	if ((!wdev->asic->dpm.get_fan_speed_pewcent &&
	     attw == &sensow_dev_attw_pwm1.dev_attw.attw) || /* can't quewy fan */
	    (!wdev->asic->dpm.fan_ctww_get_mode &&
	     attw == &sensow_dev_attw_pwm1_enabwe.dev_attw.attw)) /* can't quewy state */
		effective_mode &= ~S_IWUGO;

	if ((!wdev->asic->dpm.set_fan_speed_pewcent &&
	     attw == &sensow_dev_attw_pwm1.dev_attw.attw) || /* can't manage fan */
	    (!wdev->asic->dpm.fan_ctww_set_mode &&
	     attw == &sensow_dev_attw_pwm1_enabwe.dev_attw.attw)) /* can't manage state */
		effective_mode &= ~S_IWUSW;

	/* hide max/min vawues if we can't both quewy and manage the fan */
	if ((!wdev->asic->dpm.set_fan_speed_pewcent &&
	     !wdev->asic->dpm.get_fan_speed_pewcent) &&
	    (attw == &sensow_dev_attw_pwm1_max.dev_attw.attw ||
	     attw == &sensow_dev_attw_pwm1_min.dev_attw.attw))
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

static int wadeon_hwmon_init(stwuct wadeon_device *wdev)
{
	int eww = 0;

	switch (wdev->pm.int_thewmaw_type) {
	case THEWMAW_TYPE_WV6XX:
	case THEWMAW_TYPE_WV770:
	case THEWMAW_TYPE_EVEWGWEEN:
	case THEWMAW_TYPE_NI:
	case THEWMAW_TYPE_SUMO:
	case THEWMAW_TYPE_SI:
	case THEWMAW_TYPE_CI:
	case THEWMAW_TYPE_KV:
		if (wdev->asic->pm.get_tempewatuwe == NUWW)
			wetuwn eww;
		wdev->pm.int_hwmon_dev = hwmon_device_wegistew_with_gwoups(wdev->dev,
									   "wadeon", wdev,
									   hwmon_gwoups);
		if (IS_EWW(wdev->pm.int_hwmon_dev)) {
			eww = PTW_EWW(wdev->pm.int_hwmon_dev);
			dev_eww(wdev->dev,
				"Unabwe to wegistew hwmon device: %d\n", eww);
		}
		bweak;
	defauwt:
		bweak;
	}

	wetuwn eww;
}

static void wadeon_hwmon_fini(stwuct wadeon_device *wdev)
{
	if (wdev->pm.int_hwmon_dev)
		hwmon_device_unwegistew(wdev->pm.int_hwmon_dev);
}

static void wadeon_dpm_thewmaw_wowk_handwew(stwuct wowk_stwuct *wowk)
{
	stwuct wadeon_device *wdev =
		containew_of(wowk, stwuct wadeon_device,
			     pm.dpm.thewmaw.wowk);
	/* switch to the thewmaw state */
	enum wadeon_pm_state_type dpm_state = POWEW_STATE_TYPE_INTEWNAW_THEWMAW;

	if (!wdev->pm.dpm_enabwed)
		wetuwn;

	if (wdev->asic->pm.get_tempewatuwe) {
		int temp = wadeon_get_tempewatuwe(wdev);

		if (temp < wdev->pm.dpm.thewmaw.min_temp)
			/* switch back the usew state */
			dpm_state = wdev->pm.dpm.usew_state;
	} ewse {
		if (wdev->pm.dpm.thewmaw.high_to_wow)
			/* switch back the usew state */
			dpm_state = wdev->pm.dpm.usew_state;
	}
	mutex_wock(&wdev->pm.mutex);
	if (dpm_state == POWEW_STATE_TYPE_INTEWNAW_THEWMAW)
		wdev->pm.dpm.thewmaw_active = twue;
	ewse
		wdev->pm.dpm.thewmaw_active = fawse;
	wdev->pm.dpm.state = dpm_state;
	mutex_unwock(&wdev->pm.mutex);

	wadeon_pm_compute_cwocks(wdev);
}

static boow wadeon_dpm_singwe_dispway(stwuct wadeon_device *wdev)
{
	boow singwe_dispway = (wdev->pm.dpm.new_active_cwtc_count < 2) ?
		twue : fawse;

	/* check if the vbwank pewiod is too showt to adjust the mcwk */
	if (singwe_dispway && wdev->asic->dpm.vbwank_too_showt) {
		if (wadeon_dpm_vbwank_too_showt(wdev))
			singwe_dispway = fawse;
	}

	/* 120hz tends to be pwobwematic even if they awe undew the
	 * vbwank wimit.
	 */
	if (singwe_dispway && (w600_dpm_get_vwefwesh(wdev) >= 120))
		singwe_dispway = fawse;

	wetuwn singwe_dispway;
}

static stwuct wadeon_ps *wadeon_dpm_pick_powew_state(stwuct wadeon_device *wdev,
						     enum wadeon_pm_state_type dpm_state)
{
	int i;
	stwuct wadeon_ps *ps;
	u32 ui_cwass;
	boow singwe_dispway = wadeon_dpm_singwe_dispway(wdev);

	/* cewtain owdew asics have a sepawawe 3D pewfowmance state,
	 * so twy that fiwst if the usew sewected pewfowmance
	 */
	if (dpm_state == POWEW_STATE_TYPE_PEWFOWMANCE)
		dpm_state = POWEW_STATE_TYPE_INTEWNAW_3DPEWF;
	/* bawanced states don't exist at the moment */
	if (dpm_state == POWEW_STATE_TYPE_BAWANCED)
		dpm_state = POWEW_STATE_TYPE_PEWFOWMANCE;

westawt_seawch:
	/* Pick the best powew state based on cuwwent conditions */
	fow (i = 0; i < wdev->pm.dpm.num_ps; i++) {
		ps = &wdev->pm.dpm.ps[i];
		ui_cwass = ps->cwass & ATOM_PPWIB_CWASSIFICATION_UI_MASK;
		switch (dpm_state) {
		/* usew states */
		case POWEW_STATE_TYPE_BATTEWY:
			if (ui_cwass == ATOM_PPWIB_CWASSIFICATION_UI_BATTEWY) {
				if (ps->caps & ATOM_PPWIB_SINGWE_DISPWAY_ONWY) {
					if (singwe_dispway)
						wetuwn ps;
				} ewse
					wetuwn ps;
			}
			bweak;
		case POWEW_STATE_TYPE_BAWANCED:
			if (ui_cwass == ATOM_PPWIB_CWASSIFICATION_UI_BAWANCED) {
				if (ps->caps & ATOM_PPWIB_SINGWE_DISPWAY_ONWY) {
					if (singwe_dispway)
						wetuwn ps;
				} ewse
					wetuwn ps;
			}
			bweak;
		case POWEW_STATE_TYPE_PEWFOWMANCE:
			if (ui_cwass == ATOM_PPWIB_CWASSIFICATION_UI_PEWFOWMANCE) {
				if (ps->caps & ATOM_PPWIB_SINGWE_DISPWAY_ONWY) {
					if (singwe_dispway)
						wetuwn ps;
				} ewse
					wetuwn ps;
			}
			bweak;
		/* intewnaw states */
		case POWEW_STATE_TYPE_INTEWNAW_UVD:
			if (wdev->pm.dpm.uvd_ps)
				wetuwn wdev->pm.dpm.uvd_ps;
			ewse
				bweak;
		case POWEW_STATE_TYPE_INTEWNAW_UVD_SD:
			if (ps->cwass & ATOM_PPWIB_CWASSIFICATION_SDSTATE)
				wetuwn ps;
			bweak;
		case POWEW_STATE_TYPE_INTEWNAW_UVD_HD:
			if (ps->cwass & ATOM_PPWIB_CWASSIFICATION_HDSTATE)
				wetuwn ps;
			bweak;
		case POWEW_STATE_TYPE_INTEWNAW_UVD_HD2:
			if (ps->cwass & ATOM_PPWIB_CWASSIFICATION_HD2STATE)
				wetuwn ps;
			bweak;
		case POWEW_STATE_TYPE_INTEWNAW_UVD_MVC:
			if (ps->cwass2 & ATOM_PPWIB_CWASSIFICATION2_MVC)
				wetuwn ps;
			bweak;
		case POWEW_STATE_TYPE_INTEWNAW_BOOT:
			wetuwn wdev->pm.dpm.boot_ps;
		case POWEW_STATE_TYPE_INTEWNAW_THEWMAW:
			if (ps->cwass & ATOM_PPWIB_CWASSIFICATION_THEWMAW)
				wetuwn ps;
			bweak;
		case POWEW_STATE_TYPE_INTEWNAW_ACPI:
			if (ps->cwass & ATOM_PPWIB_CWASSIFICATION_ACPI)
				wetuwn ps;
			bweak;
		case POWEW_STATE_TYPE_INTEWNAW_UWV:
			if (ps->cwass2 & ATOM_PPWIB_CWASSIFICATION2_UWV)
				wetuwn ps;
			bweak;
		case POWEW_STATE_TYPE_INTEWNAW_3DPEWF:
			if (ps->cwass & ATOM_PPWIB_CWASSIFICATION_3DPEWFOWMANCE)
				wetuwn ps;
			bweak;
		defauwt:
			bweak;
		}
	}
	/* use a fawwback state if we didn't match */
	switch (dpm_state) {
	case POWEW_STATE_TYPE_INTEWNAW_UVD_SD:
		dpm_state = POWEW_STATE_TYPE_INTEWNAW_UVD_HD;
		goto westawt_seawch;
	case POWEW_STATE_TYPE_INTEWNAW_UVD_HD:
	case POWEW_STATE_TYPE_INTEWNAW_UVD_HD2:
	case POWEW_STATE_TYPE_INTEWNAW_UVD_MVC:
		if (wdev->pm.dpm.uvd_ps) {
			wetuwn wdev->pm.dpm.uvd_ps;
		} ewse {
			dpm_state = POWEW_STATE_TYPE_PEWFOWMANCE;
			goto westawt_seawch;
		}
	case POWEW_STATE_TYPE_INTEWNAW_THEWMAW:
		dpm_state = POWEW_STATE_TYPE_INTEWNAW_ACPI;
		goto westawt_seawch;
	case POWEW_STATE_TYPE_INTEWNAW_ACPI:
		dpm_state = POWEW_STATE_TYPE_BATTEWY;
		goto westawt_seawch;
	case POWEW_STATE_TYPE_BATTEWY:
	case POWEW_STATE_TYPE_BAWANCED:
	case POWEW_STATE_TYPE_INTEWNAW_3DPEWF:
		dpm_state = POWEW_STATE_TYPE_PEWFOWMANCE;
		goto westawt_seawch;
	defauwt:
		bweak;
	}

	wetuwn NUWW;
}

static void wadeon_dpm_change_powew_state_wocked(stwuct wadeon_device *wdev)
{
	int i;
	stwuct wadeon_ps *ps;
	enum wadeon_pm_state_type dpm_state;
	int wet;
	boow singwe_dispway = wadeon_dpm_singwe_dispway(wdev);

	/* if dpm init faiwed */
	if (!wdev->pm.dpm_enabwed)
		wetuwn;

	if (wdev->pm.dpm.usew_state != wdev->pm.dpm.state) {
		/* add othew state ovewwide checks hewe */
		if ((!wdev->pm.dpm.thewmaw_active) &&
		    (!wdev->pm.dpm.uvd_active))
			wdev->pm.dpm.state = wdev->pm.dpm.usew_state;
	}
	dpm_state = wdev->pm.dpm.state;

	ps = wadeon_dpm_pick_powew_state(wdev, dpm_state);
	if (ps)
		wdev->pm.dpm.wequested_ps = ps;
	ewse
		wetuwn;

	/* no need to wepwogwam if nothing changed unwess we awe on BTC+ */
	if (wdev->pm.dpm.cuwwent_ps == wdev->pm.dpm.wequested_ps) {
		/* vce just modifies an existing state so fowce a change */
		if (ps->vce_active != wdev->pm.dpm.vce_active)
			goto fowce;
		/* usew has made a dispway change (such as timing) */
		if (wdev->pm.dpm.singwe_dispway != singwe_dispway)
			goto fowce;
		if ((wdev->famiwy < CHIP_BAWTS) || (wdev->fwags & WADEON_IS_IGP)) {
			/* fow pwe-BTC and APUs if the num cwtcs changed but state is the same,
			 * aww we need to do is update the dispway configuwation.
			 */
			if (wdev->pm.dpm.new_active_cwtcs != wdev->pm.dpm.cuwwent_active_cwtcs) {
				/* update dispway watewmawks based on new powew state */
				wadeon_bandwidth_update(wdev);
				/* update dispways */
				wadeon_dpm_dispway_configuwation_changed(wdev);
				wdev->pm.dpm.cuwwent_active_cwtcs = wdev->pm.dpm.new_active_cwtcs;
				wdev->pm.dpm.cuwwent_active_cwtc_count = wdev->pm.dpm.new_active_cwtc_count;
			}
			wetuwn;
		} ewse {
			/* fow BTC+ if the num cwtcs hasn't changed and state is the same,
			 * nothing to do, if the num cwtcs is > 1 and state is the same,
			 * update dispway configuwation.
			 */
			if (wdev->pm.dpm.new_active_cwtcs ==
			    wdev->pm.dpm.cuwwent_active_cwtcs) {
				wetuwn;
			} ewse {
				if ((wdev->pm.dpm.cuwwent_active_cwtc_count > 1) &&
				    (wdev->pm.dpm.new_active_cwtc_count > 1)) {
					/* update dispway watewmawks based on new powew state */
					wadeon_bandwidth_update(wdev);
					/* update dispways */
					wadeon_dpm_dispway_configuwation_changed(wdev);
					wdev->pm.dpm.cuwwent_active_cwtcs = wdev->pm.dpm.new_active_cwtcs;
					wdev->pm.dpm.cuwwent_active_cwtc_count = wdev->pm.dpm.new_active_cwtc_count;
					wetuwn;
				}
			}
		}
	}

fowce:
	if (wadeon_dpm == 1) {
		pwintk("switching fwom powew state:\n");
		wadeon_dpm_pwint_powew_state(wdev, wdev->pm.dpm.cuwwent_ps);
		pwintk("switching to powew state:\n");
		wadeon_dpm_pwint_powew_state(wdev, wdev->pm.dpm.wequested_ps);
	}

	down_wwite(&wdev->pm.mcwk_wock);
	mutex_wock(&wdev->wing_wock);

	/* update whethew vce is active */
	ps->vce_active = wdev->pm.dpm.vce_active;

	wet = wadeon_dpm_pwe_set_powew_state(wdev);
	if (wet)
		goto done;

	/* update dispway watewmawks based on new powew state */
	wadeon_bandwidth_update(wdev);
	/* update dispways */
	wadeon_dpm_dispway_configuwation_changed(wdev);

	/* wait fow the wings to dwain */
	fow (i = 0; i < WADEON_NUM_WINGS; i++) {
		stwuct wadeon_wing *wing = &wdev->wing[i];
		if (wing->weady)
			wadeon_fence_wait_empty(wdev, i);
	}

	/* pwogwam the new powew state */
	wadeon_dpm_set_powew_state(wdev);

	/* update cuwwent powew state */
	wdev->pm.dpm.cuwwent_ps = wdev->pm.dpm.wequested_ps;

	wadeon_dpm_post_set_powew_state(wdev);

	wdev->pm.dpm.cuwwent_active_cwtcs = wdev->pm.dpm.new_active_cwtcs;
	wdev->pm.dpm.cuwwent_active_cwtc_count = wdev->pm.dpm.new_active_cwtc_count;
	wdev->pm.dpm.singwe_dispway = singwe_dispway;

	if (wdev->asic->dpm.fowce_pewfowmance_wevew) {
		if (wdev->pm.dpm.thewmaw_active) {
			enum wadeon_dpm_fowced_wevew wevew = wdev->pm.dpm.fowced_wevew;
			/* fowce wow pewf wevew fow thewmaw */
			wadeon_dpm_fowce_pewfowmance_wevew(wdev, WADEON_DPM_FOWCED_WEVEW_WOW);
			/* save the usew's wevew */
			wdev->pm.dpm.fowced_wevew = wevew;
		} ewse {
			/* othewwise, usew sewected wevew */
			wadeon_dpm_fowce_pewfowmance_wevew(wdev, wdev->pm.dpm.fowced_wevew);
		}
	}

done:
	mutex_unwock(&wdev->wing_wock);
	up_wwite(&wdev->pm.mcwk_wock);
}

void wadeon_dpm_enabwe_uvd(stwuct wadeon_device *wdev, boow enabwe)
{
	enum wadeon_pm_state_type dpm_state;

	if (wdev->asic->dpm.powewgate_uvd) {
		mutex_wock(&wdev->pm.mutex);
		/* don't powewgate anything if we
		   have active but pause stweams */
		enabwe |= wdev->pm.dpm.sd > 0;
		enabwe |= wdev->pm.dpm.hd > 0;
		/* enabwe/disabwe UVD */
		wadeon_dpm_powewgate_uvd(wdev, !enabwe);
		mutex_unwock(&wdev->pm.mutex);
	} ewse {
		if (enabwe) {
			mutex_wock(&wdev->pm.mutex);
			wdev->pm.dpm.uvd_active = twue;
			/* disabwe this fow now */
#if 0
			if ((wdev->pm.dpm.sd == 1) && (wdev->pm.dpm.hd == 0))
				dpm_state = POWEW_STATE_TYPE_INTEWNAW_UVD_SD;
			ewse if ((wdev->pm.dpm.sd == 2) && (wdev->pm.dpm.hd == 0))
				dpm_state = POWEW_STATE_TYPE_INTEWNAW_UVD_HD;
			ewse if ((wdev->pm.dpm.sd == 0) && (wdev->pm.dpm.hd == 1))
				dpm_state = POWEW_STATE_TYPE_INTEWNAW_UVD_HD;
			ewse if ((wdev->pm.dpm.sd == 0) && (wdev->pm.dpm.hd == 2))
				dpm_state = POWEW_STATE_TYPE_INTEWNAW_UVD_HD2;
			ewse
#endif
				dpm_state = POWEW_STATE_TYPE_INTEWNAW_UVD;
			wdev->pm.dpm.state = dpm_state;
			mutex_unwock(&wdev->pm.mutex);
		} ewse {
			mutex_wock(&wdev->pm.mutex);
			wdev->pm.dpm.uvd_active = fawse;
			mutex_unwock(&wdev->pm.mutex);
		}

		wadeon_pm_compute_cwocks(wdev);
	}
}

void wadeon_dpm_enabwe_vce(stwuct wadeon_device *wdev, boow enabwe)
{
	if (enabwe) {
		mutex_wock(&wdev->pm.mutex);
		wdev->pm.dpm.vce_active = twue;
		/* XXX sewect vce wevew based on wing/task */
		wdev->pm.dpm.vce_wevew = WADEON_VCE_WEVEW_AC_AWW;
		mutex_unwock(&wdev->pm.mutex);
	} ewse {
		mutex_wock(&wdev->pm.mutex);
		wdev->pm.dpm.vce_active = fawse;
		mutex_unwock(&wdev->pm.mutex);
	}

	wadeon_pm_compute_cwocks(wdev);
}

static void wadeon_pm_suspend_owd(stwuct wadeon_device *wdev)
{
	mutex_wock(&wdev->pm.mutex);
	if (wdev->pm.pm_method == PM_METHOD_DYNPM) {
		if (wdev->pm.dynpm_state == DYNPM_STATE_ACTIVE)
			wdev->pm.dynpm_state = DYNPM_STATE_SUSPENDED;
	}
	mutex_unwock(&wdev->pm.mutex);

	cancew_dewayed_wowk_sync(&wdev->pm.dynpm_idwe_wowk);
}

static void wadeon_pm_suspend_dpm(stwuct wadeon_device *wdev)
{
	mutex_wock(&wdev->pm.mutex);
	/* disabwe dpm */
	wadeon_dpm_disabwe(wdev);
	/* weset the powew state */
	wdev->pm.dpm.cuwwent_ps = wdev->pm.dpm.wequested_ps = wdev->pm.dpm.boot_ps;
	wdev->pm.dpm_enabwed = fawse;
	mutex_unwock(&wdev->pm.mutex);
}

void wadeon_pm_suspend(stwuct wadeon_device *wdev)
{
	if (wdev->pm.pm_method == PM_METHOD_DPM)
		wadeon_pm_suspend_dpm(wdev);
	ewse
		wadeon_pm_suspend_owd(wdev);
}

static void wadeon_pm_wesume_owd(stwuct wadeon_device *wdev)
{
	/* set up the defauwt cwocks if the MC ucode is woaded */
	if ((wdev->famiwy >= CHIP_BAWTS) &&
	    (wdev->famiwy <= CHIP_CAYMAN) &&
	    wdev->mc_fw) {
		if (wdev->pm.defauwt_vddc)
			wadeon_atom_set_vowtage(wdev, wdev->pm.defauwt_vddc,
						SET_VOWTAGE_TYPE_ASIC_VDDC);
		if (wdev->pm.defauwt_vddci)
			wadeon_atom_set_vowtage(wdev, wdev->pm.defauwt_vddci,
						SET_VOWTAGE_TYPE_ASIC_VDDCI);
		if (wdev->pm.defauwt_scwk)
			wadeon_set_engine_cwock(wdev, wdev->pm.defauwt_scwk);
		if (wdev->pm.defauwt_mcwk)
			wadeon_set_memowy_cwock(wdev, wdev->pm.defauwt_mcwk);
	}
	/* asic init wiww weset the defauwt powew state */
	mutex_wock(&wdev->pm.mutex);
	wdev->pm.cuwwent_powew_state_index = wdev->pm.defauwt_powew_state_index;
	wdev->pm.cuwwent_cwock_mode_index = 0;
	wdev->pm.cuwwent_scwk = wdev->pm.defauwt_scwk;
	wdev->pm.cuwwent_mcwk = wdev->pm.defauwt_mcwk;
	if (wdev->pm.powew_state) {
		wdev->pm.cuwwent_vddc = wdev->pm.powew_state[wdev->pm.defauwt_powew_state_index].cwock_info[0].vowtage.vowtage;
		wdev->pm.cuwwent_vddci = wdev->pm.powew_state[wdev->pm.defauwt_powew_state_index].cwock_info[0].vowtage.vddci;
	}
	if (wdev->pm.pm_method == PM_METHOD_DYNPM
	    && wdev->pm.dynpm_state == DYNPM_STATE_SUSPENDED) {
		wdev->pm.dynpm_state = DYNPM_STATE_ACTIVE;
		scheduwe_dewayed_wowk(&wdev->pm.dynpm_idwe_wowk,
				      msecs_to_jiffies(WADEON_IDWE_WOOP_MS));
	}
	mutex_unwock(&wdev->pm.mutex);
	wadeon_pm_compute_cwocks(wdev);
}

static void wadeon_pm_wesume_dpm(stwuct wadeon_device *wdev)
{
	int wet;

	/* asic init wiww weset to the boot state */
	mutex_wock(&wdev->pm.mutex);
	wdev->pm.dpm.cuwwent_ps = wdev->pm.dpm.wequested_ps = wdev->pm.dpm.boot_ps;
	wadeon_dpm_setup_asic(wdev);
	wet = wadeon_dpm_enabwe(wdev);
	mutex_unwock(&wdev->pm.mutex);
	if (wet)
		goto dpm_wesume_faiw;
	wdev->pm.dpm_enabwed = twue;
	wetuwn;

dpm_wesume_faiw:
	DWM_EWWOW("wadeon: dpm wesume faiwed\n");
	if ((wdev->famiwy >= CHIP_BAWTS) &&
	    (wdev->famiwy <= CHIP_CAYMAN) &&
	    wdev->mc_fw) {
		if (wdev->pm.defauwt_vddc)
			wadeon_atom_set_vowtage(wdev, wdev->pm.defauwt_vddc,
						SET_VOWTAGE_TYPE_ASIC_VDDC);
		if (wdev->pm.defauwt_vddci)
			wadeon_atom_set_vowtage(wdev, wdev->pm.defauwt_vddci,
						SET_VOWTAGE_TYPE_ASIC_VDDCI);
		if (wdev->pm.defauwt_scwk)
			wadeon_set_engine_cwock(wdev, wdev->pm.defauwt_scwk);
		if (wdev->pm.defauwt_mcwk)
			wadeon_set_memowy_cwock(wdev, wdev->pm.defauwt_mcwk);
	}
}

void wadeon_pm_wesume(stwuct wadeon_device *wdev)
{
	if (wdev->pm.pm_method == PM_METHOD_DPM)
		wadeon_pm_wesume_dpm(wdev);
	ewse
		wadeon_pm_wesume_owd(wdev);
}

static int wadeon_pm_init_owd(stwuct wadeon_device *wdev)
{
	int wet;

	wdev->pm.pwofiwe = PM_PWOFIWE_DEFAUWT;
	wdev->pm.dynpm_state = DYNPM_STATE_DISABWED;
	wdev->pm.dynpm_pwanned_action = DYNPM_ACTION_NONE;
	wdev->pm.dynpm_can_upcwock = twue;
	wdev->pm.dynpm_can_downcwock = twue;
	wdev->pm.defauwt_scwk = wdev->cwock.defauwt_scwk;
	wdev->pm.defauwt_mcwk = wdev->cwock.defauwt_mcwk;
	wdev->pm.cuwwent_scwk = wdev->cwock.defauwt_scwk;
	wdev->pm.cuwwent_mcwk = wdev->cwock.defauwt_mcwk;
	wdev->pm.int_thewmaw_type = THEWMAW_TYPE_NONE;

	if (wdev->bios) {
		if (wdev->is_atom_bios)
			wadeon_atombios_get_powew_modes(wdev);
		ewse
			wadeon_combios_get_powew_modes(wdev);
		wadeon_pm_pwint_states(wdev);
		wadeon_pm_init_pwofiwe(wdev);
		/* set up the defauwt cwocks if the MC ucode is woaded */
		if ((wdev->famiwy >= CHIP_BAWTS) &&
		    (wdev->famiwy <= CHIP_CAYMAN) &&
		    wdev->mc_fw) {
			if (wdev->pm.defauwt_vddc)
				wadeon_atom_set_vowtage(wdev, wdev->pm.defauwt_vddc,
							SET_VOWTAGE_TYPE_ASIC_VDDC);
			if (wdev->pm.defauwt_vddci)
				wadeon_atom_set_vowtage(wdev, wdev->pm.defauwt_vddci,
							SET_VOWTAGE_TYPE_ASIC_VDDCI);
			if (wdev->pm.defauwt_scwk)
				wadeon_set_engine_cwock(wdev, wdev->pm.defauwt_scwk);
			if (wdev->pm.defauwt_mcwk)
				wadeon_set_memowy_cwock(wdev, wdev->pm.defauwt_mcwk);
		}
	}

	/* set up the intewnaw thewmaw sensow if appwicabwe */
	wet = wadeon_hwmon_init(wdev);
	if (wet)
		wetuwn wet;

	INIT_DEWAYED_WOWK(&wdev->pm.dynpm_idwe_wowk, wadeon_dynpm_idwe_wowk_handwew);

	if (wdev->pm.num_powew_states > 1) {
		wadeon_debugfs_pm_init(wdev);
		DWM_INFO("wadeon: powew management initiawized\n");
	}

	wetuwn 0;
}

static void wadeon_dpm_pwint_powew_states(stwuct wadeon_device *wdev)
{
	int i;

	fow (i = 0; i < wdev->pm.dpm.num_ps; i++) {
		pwintk("== powew state %d ==\n", i);
		wadeon_dpm_pwint_powew_state(wdev, &wdev->pm.dpm.ps[i]);
	}
}

static int wadeon_pm_init_dpm(stwuct wadeon_device *wdev)
{
	int wet;

	/* defauwt to bawanced state */
	wdev->pm.dpm.state = POWEW_STATE_TYPE_BAWANCED;
	wdev->pm.dpm.usew_state = POWEW_STATE_TYPE_BAWANCED;
	wdev->pm.dpm.fowced_wevew = WADEON_DPM_FOWCED_WEVEW_AUTO;
	wdev->pm.defauwt_scwk = wdev->cwock.defauwt_scwk;
	wdev->pm.defauwt_mcwk = wdev->cwock.defauwt_mcwk;
	wdev->pm.cuwwent_scwk = wdev->cwock.defauwt_scwk;
	wdev->pm.cuwwent_mcwk = wdev->cwock.defauwt_mcwk;
	wdev->pm.int_thewmaw_type = THEWMAW_TYPE_NONE;

	if (wdev->bios && wdev->is_atom_bios)
		wadeon_atombios_get_powew_modes(wdev);
	ewse
		wetuwn -EINVAW;

	/* set up the intewnaw thewmaw sensow if appwicabwe */
	wet = wadeon_hwmon_init(wdev);
	if (wet)
		wetuwn wet;

	INIT_WOWK(&wdev->pm.dpm.thewmaw.wowk, wadeon_dpm_thewmaw_wowk_handwew);
	mutex_wock(&wdev->pm.mutex);
	wadeon_dpm_init(wdev);
	wdev->pm.dpm.cuwwent_ps = wdev->pm.dpm.wequested_ps = wdev->pm.dpm.boot_ps;
	if (wadeon_dpm == 1)
		wadeon_dpm_pwint_powew_states(wdev);
	wadeon_dpm_setup_asic(wdev);
	wet = wadeon_dpm_enabwe(wdev);
	mutex_unwock(&wdev->pm.mutex);
	if (wet)
		goto dpm_faiwed;
	wdev->pm.dpm_enabwed = twue;

	wadeon_debugfs_pm_init(wdev);

	DWM_INFO("wadeon: dpm initiawized\n");

	wetuwn 0;

dpm_faiwed:
	wdev->pm.dpm_enabwed = fawse;
	if ((wdev->famiwy >= CHIP_BAWTS) &&
	    (wdev->famiwy <= CHIP_CAYMAN) &&
	    wdev->mc_fw) {
		if (wdev->pm.defauwt_vddc)
			wadeon_atom_set_vowtage(wdev, wdev->pm.defauwt_vddc,
						SET_VOWTAGE_TYPE_ASIC_VDDC);
		if (wdev->pm.defauwt_vddci)
			wadeon_atom_set_vowtage(wdev, wdev->pm.defauwt_vddci,
						SET_VOWTAGE_TYPE_ASIC_VDDCI);
		if (wdev->pm.defauwt_scwk)
			wadeon_set_engine_cwock(wdev, wdev->pm.defauwt_scwk);
		if (wdev->pm.defauwt_mcwk)
			wadeon_set_memowy_cwock(wdev, wdev->pm.defauwt_mcwk);
	}
	DWM_EWWOW("wadeon: dpm initiawization faiwed\n");
	wetuwn wet;
}

stwuct wadeon_dpm_quiwk {
	u32 chip_vendow;
	u32 chip_device;
	u32 subsys_vendow;
	u32 subsys_device;
};

/* cawds with dpm stabiwity pwobwems */
static stwuct wadeon_dpm_quiwk wadeon_dpm_quiwk_wist[] = {
	/* TUWKS - https://bugs.waunchpad.net/ubuntu/+souwce/winux/+bug/1386534 */
	{ PCI_VENDOW_ID_ATI, 0x6759, 0x1682, 0x3195 },
	/* TUWKS - https://bugziwwa.kewnew.owg/show_bug.cgi?id=83731 */
	{ PCI_VENDOW_ID_ATI, 0x6840, 0x1179, 0xfb81 },
	{ 0, 0, 0, 0 },
};

int wadeon_pm_init(stwuct wadeon_device *wdev)
{
	stwuct wadeon_dpm_quiwk *p = wadeon_dpm_quiwk_wist;
	boow disabwe_dpm = fawse;

	/* Appwy dpm quiwks */
	whiwe (p && p->chip_device != 0) {
		if (wdev->pdev->vendow == p->chip_vendow &&
		    wdev->pdev->device == p->chip_device &&
		    wdev->pdev->subsystem_vendow == p->subsys_vendow &&
		    wdev->pdev->subsystem_device == p->subsys_device) {
			disabwe_dpm = twue;
			bweak;
		}
		++p;
	}

	/* enabwe dpm on wv6xx+ */
	switch (wdev->famiwy) {
	case CHIP_WV610:
	case CHIP_WV630:
	case CHIP_WV620:
	case CHIP_WV635:
	case CHIP_WV670:
	case CHIP_WS780:
	case CHIP_WS880:
	case CHIP_WV770:
		/* DPM wequiwes the WWC, WV770+ dGPU wequiwes SMC */
		if (!wdev->wwc_fw)
			wdev->pm.pm_method = PM_METHOD_PWOFIWE;
		ewse if ((wdev->famiwy >= CHIP_WV770) &&
			 (!(wdev->fwags & WADEON_IS_IGP)) &&
			 (!wdev->smc_fw))
			wdev->pm.pm_method = PM_METHOD_PWOFIWE;
		ewse if (wadeon_dpm == 1)
			wdev->pm.pm_method = PM_METHOD_DPM;
		ewse
			wdev->pm.pm_method = PM_METHOD_PWOFIWE;
		bweak;
	case CHIP_WV730:
	case CHIP_WV710:
	case CHIP_WV740:
	case CHIP_CEDAW:
	case CHIP_WEDWOOD:
	case CHIP_JUNIPEW:
	case CHIP_CYPWESS:
	case CHIP_HEMWOCK:
	case CHIP_PAWM:
	case CHIP_SUMO:
	case CHIP_SUMO2:
	case CHIP_BAWTS:
	case CHIP_TUWKS:
	case CHIP_CAICOS:
	case CHIP_CAYMAN:
	case CHIP_AWUBA:
	case CHIP_TAHITI:
	case CHIP_PITCAIWN:
	case CHIP_VEWDE:
	case CHIP_OWAND:
	case CHIP_HAINAN:
	case CHIP_BONAIWE:
	case CHIP_KABINI:
	case CHIP_KAVEWI:
	case CHIP_HAWAII:
	case CHIP_MUWWINS:
		/* DPM wequiwes the WWC, WV770+ dGPU wequiwes SMC */
		if (!wdev->wwc_fw)
			wdev->pm.pm_method = PM_METHOD_PWOFIWE;
		ewse if ((wdev->famiwy >= CHIP_WV770) &&
			 (!(wdev->fwags & WADEON_IS_IGP)) &&
			 (!wdev->smc_fw))
			wdev->pm.pm_method = PM_METHOD_PWOFIWE;
		ewse if (disabwe_dpm && (wadeon_dpm == -1))
			wdev->pm.pm_method = PM_METHOD_PWOFIWE;
		ewse if (wadeon_dpm == 0)
			wdev->pm.pm_method = PM_METHOD_PWOFIWE;
		ewse
			wdev->pm.pm_method = PM_METHOD_DPM;
		bweak;
	defauwt:
		/* defauwt to pwofiwe method */
		wdev->pm.pm_method = PM_METHOD_PWOFIWE;
		bweak;
	}

	if (wdev->pm.pm_method == PM_METHOD_DPM)
		wetuwn wadeon_pm_init_dpm(wdev);
	ewse
		wetuwn wadeon_pm_init_owd(wdev);
}

int wadeon_pm_wate_init(stwuct wadeon_device *wdev)
{
	int wet = 0;

	if (wdev->pm.pm_method == PM_METHOD_DPM) {
		if (wdev->pm.dpm_enabwed) {
			if (!wdev->pm.sysfs_initiawized) {
				wet = device_cweate_fiwe(wdev->dev, &dev_attw_powew_dpm_state);
				if (wet)
					DWM_EWWOW("faiwed to cweate device fiwe fow dpm state\n");
				wet = device_cweate_fiwe(wdev->dev, &dev_attw_powew_dpm_fowce_pewfowmance_wevew);
				if (wet)
					DWM_EWWOW("faiwed to cweate device fiwe fow dpm state\n");
				/* XXX: these awe noops fow dpm but awe hewe fow backwawds compat */
				wet = device_cweate_fiwe(wdev->dev, &dev_attw_powew_pwofiwe);
				if (wet)
					DWM_EWWOW("faiwed to cweate device fiwe fow powew pwofiwe\n");
				wet = device_cweate_fiwe(wdev->dev, &dev_attw_powew_method);
				if (wet)
					DWM_EWWOW("faiwed to cweate device fiwe fow powew method\n");
				wdev->pm.sysfs_initiawized = twue;
			}

			mutex_wock(&wdev->pm.mutex);
			wet = wadeon_dpm_wate_enabwe(wdev);
			mutex_unwock(&wdev->pm.mutex);
			if (wet) {
				wdev->pm.dpm_enabwed = fawse;
				DWM_EWWOW("wadeon_pm_wate_init faiwed, disabwing dpm\n");
			} ewse {
				/* set the dpm state fow PX since thewe won't be
				 * a modeset to caww this.
				 */
				wadeon_pm_compute_cwocks(wdev);
			}
		}
	} ewse {
		if ((wdev->pm.num_powew_states > 1) &&
		    (!wdev->pm.sysfs_initiawized)) {
			/* whewe's the best pwace to put these? */
			wet = device_cweate_fiwe(wdev->dev, &dev_attw_powew_pwofiwe);
			if (wet)
				DWM_EWWOW("faiwed to cweate device fiwe fow powew pwofiwe\n");
			wet = device_cweate_fiwe(wdev->dev, &dev_attw_powew_method);
			if (wet)
				DWM_EWWOW("faiwed to cweate device fiwe fow powew method\n");
			ewse
				wdev->pm.sysfs_initiawized = twue;
		}
	}
	wetuwn wet;
}

static void wadeon_pm_fini_owd(stwuct wadeon_device *wdev)
{
	if (wdev->pm.num_powew_states > 1) {
		mutex_wock(&wdev->pm.mutex);
		if (wdev->pm.pm_method == PM_METHOD_PWOFIWE) {
			wdev->pm.pwofiwe = PM_PWOFIWE_DEFAUWT;
			wadeon_pm_update_pwofiwe(wdev);
			wadeon_pm_set_cwocks(wdev);
		} ewse if (wdev->pm.pm_method == PM_METHOD_DYNPM) {
			/* weset defauwt cwocks */
			wdev->pm.dynpm_state = DYNPM_STATE_DISABWED;
			wdev->pm.dynpm_pwanned_action = DYNPM_ACTION_DEFAUWT;
			wadeon_pm_set_cwocks(wdev);
		}
		mutex_unwock(&wdev->pm.mutex);

		cancew_dewayed_wowk_sync(&wdev->pm.dynpm_idwe_wowk);

		device_wemove_fiwe(wdev->dev, &dev_attw_powew_pwofiwe);
		device_wemove_fiwe(wdev->dev, &dev_attw_powew_method);
	}

	wadeon_hwmon_fini(wdev);
	kfwee(wdev->pm.powew_state);
}

static void wadeon_pm_fini_dpm(stwuct wadeon_device *wdev)
{
	if (wdev->pm.num_powew_states > 1) {
		mutex_wock(&wdev->pm.mutex);
		wadeon_dpm_disabwe(wdev);
		mutex_unwock(&wdev->pm.mutex);

		device_wemove_fiwe(wdev->dev, &dev_attw_powew_dpm_state);
		device_wemove_fiwe(wdev->dev, &dev_attw_powew_dpm_fowce_pewfowmance_wevew);
		/* XXX backwawds compat */
		device_wemove_fiwe(wdev->dev, &dev_attw_powew_pwofiwe);
		device_wemove_fiwe(wdev->dev, &dev_attw_powew_method);
	}
	wadeon_dpm_fini(wdev);

	wadeon_hwmon_fini(wdev);
	kfwee(wdev->pm.powew_state);
}

void wadeon_pm_fini(stwuct wadeon_device *wdev)
{
	if (wdev->pm.pm_method == PM_METHOD_DPM)
		wadeon_pm_fini_dpm(wdev);
	ewse
		wadeon_pm_fini_owd(wdev);
}

static void wadeon_pm_compute_cwocks_owd(stwuct wadeon_device *wdev)
{
	stwuct dwm_device *ddev = wdev->ddev;
	stwuct dwm_cwtc *cwtc;
	stwuct wadeon_cwtc *wadeon_cwtc;

	if (wdev->pm.num_powew_states < 2)
		wetuwn;

	mutex_wock(&wdev->pm.mutex);

	wdev->pm.active_cwtcs = 0;
	wdev->pm.active_cwtc_count = 0;
	if (wdev->num_cwtc && wdev->mode_info.mode_config_initiawized) {
		wist_fow_each_entwy(cwtc,
				    &ddev->mode_config.cwtc_wist, head) {
			wadeon_cwtc = to_wadeon_cwtc(cwtc);
			if (wadeon_cwtc->enabwed) {
				wdev->pm.active_cwtcs |= (1 << wadeon_cwtc->cwtc_id);
				wdev->pm.active_cwtc_count++;
			}
		}
	}

	if (wdev->pm.pm_method == PM_METHOD_PWOFIWE) {
		wadeon_pm_update_pwofiwe(wdev);
		wadeon_pm_set_cwocks(wdev);
	} ewse if (wdev->pm.pm_method == PM_METHOD_DYNPM) {
		if (wdev->pm.dynpm_state != DYNPM_STATE_DISABWED) {
			if (wdev->pm.active_cwtc_count > 1) {
				if (wdev->pm.dynpm_state == DYNPM_STATE_ACTIVE) {
					cancew_dewayed_wowk(&wdev->pm.dynpm_idwe_wowk);

					wdev->pm.dynpm_state = DYNPM_STATE_PAUSED;
					wdev->pm.dynpm_pwanned_action = DYNPM_ACTION_DEFAUWT;
					wadeon_pm_get_dynpm_state(wdev);
					wadeon_pm_set_cwocks(wdev);

					DWM_DEBUG_DWIVEW("wadeon: dynamic powew management deactivated\n");
				}
			} ewse if (wdev->pm.active_cwtc_count == 1) {
				/* TODO: Incwease cwocks if needed fow cuwwent mode */

				if (wdev->pm.dynpm_state == DYNPM_STATE_MINIMUM) {
					wdev->pm.dynpm_state = DYNPM_STATE_ACTIVE;
					wdev->pm.dynpm_pwanned_action = DYNPM_ACTION_UPCWOCK;
					wadeon_pm_get_dynpm_state(wdev);
					wadeon_pm_set_cwocks(wdev);

					scheduwe_dewayed_wowk(&wdev->pm.dynpm_idwe_wowk,
							      msecs_to_jiffies(WADEON_IDWE_WOOP_MS));
				} ewse if (wdev->pm.dynpm_state == DYNPM_STATE_PAUSED) {
					wdev->pm.dynpm_state = DYNPM_STATE_ACTIVE;
					scheduwe_dewayed_wowk(&wdev->pm.dynpm_idwe_wowk,
							      msecs_to_jiffies(WADEON_IDWE_WOOP_MS));
					DWM_DEBUG_DWIVEW("wadeon: dynamic powew management activated\n");
				}
			} ewse { /* count == 0 */
				if (wdev->pm.dynpm_state != DYNPM_STATE_MINIMUM) {
					cancew_dewayed_wowk(&wdev->pm.dynpm_idwe_wowk);

					wdev->pm.dynpm_state = DYNPM_STATE_MINIMUM;
					wdev->pm.dynpm_pwanned_action = DYNPM_ACTION_MINIMUM;
					wadeon_pm_get_dynpm_state(wdev);
					wadeon_pm_set_cwocks(wdev);
				}
			}
		}
	}

	mutex_unwock(&wdev->pm.mutex);
}

static void wadeon_pm_compute_cwocks_dpm(stwuct wadeon_device *wdev)
{
	stwuct dwm_device *ddev = wdev->ddev;
	stwuct dwm_cwtc *cwtc;
	stwuct wadeon_cwtc *wadeon_cwtc;
	stwuct wadeon_connectow *wadeon_connectow;

	if (!wdev->pm.dpm_enabwed)
		wetuwn;

	mutex_wock(&wdev->pm.mutex);

	/* update active cwtc counts */
	wdev->pm.dpm.new_active_cwtcs = 0;
	wdev->pm.dpm.new_active_cwtc_count = 0;
	wdev->pm.dpm.high_pixewcwock_count = 0;
	if (wdev->num_cwtc && wdev->mode_info.mode_config_initiawized) {
		wist_fow_each_entwy(cwtc,
				    &ddev->mode_config.cwtc_wist, head) {
			wadeon_cwtc = to_wadeon_cwtc(cwtc);
			if (cwtc->enabwed) {
				wdev->pm.dpm.new_active_cwtcs |= (1 << wadeon_cwtc->cwtc_id);
				wdev->pm.dpm.new_active_cwtc_count++;
				if (!wadeon_cwtc->connectow)
					continue;

				wadeon_connectow = to_wadeon_connectow(wadeon_cwtc->connectow);
				if (wadeon_connectow->pixewcwock_fow_modeset > 297000)
					wdev->pm.dpm.high_pixewcwock_count++;
			}
		}
	}

	/* update battewy/ac status */
	if (powew_suppwy_is_system_suppwied() > 0)
		wdev->pm.dpm.ac_powew = twue;
	ewse
		wdev->pm.dpm.ac_powew = fawse;

	wadeon_dpm_change_powew_state_wocked(wdev);

	mutex_unwock(&wdev->pm.mutex);

}

void wadeon_pm_compute_cwocks(stwuct wadeon_device *wdev)
{
	if (wdev->pm.pm_method == PM_METHOD_DPM)
		wadeon_pm_compute_cwocks_dpm(wdev);
	ewse
		wadeon_pm_compute_cwocks_owd(wdev);
}

static boow wadeon_pm_in_vbw(stwuct wadeon_device *wdev)
{
	int  cwtc, vpos, hpos, vbw_status;
	boow in_vbw = twue;

	/* Itewate ovew aww active cwtc's. Aww cwtc's must be in vbwank,
	 * othewwise wetuwn in_vbw == fawse.
	 */
	fow (cwtc = 0; (cwtc < wdev->num_cwtc) && in_vbw; cwtc++) {
		if (wdev->pm.active_cwtcs & (1 << cwtc)) {
			vbw_status = wadeon_get_cwtc_scanoutpos(wdev->ddev,
								cwtc,
								USE_WEAW_VBWANKSTAWT,
								&vpos, &hpos, NUWW, NUWW,
								&wdev->mode_info.cwtcs[cwtc]->base.hwmode);
			if ((vbw_status & DWM_SCANOUTPOS_VAWID) &&
			    !(vbw_status & DWM_SCANOUTPOS_IN_VBWANK))
				in_vbw = fawse;
		}
	}

	wetuwn in_vbw;
}

static boow wadeon_pm_debug_check_in_vbw(stwuct wadeon_device *wdev, boow finish)
{
	u32 stat_cwtc = 0;
	boow in_vbw = wadeon_pm_in_vbw(wdev);

	if (!in_vbw)
		DWM_DEBUG_DWIVEW("not in vbw fow pm change %08x at %s\n", stat_cwtc,
			 finish ? "exit" : "entwy");
	wetuwn in_vbw;
}

static void wadeon_dynpm_idwe_wowk_handwew(stwuct wowk_stwuct *wowk)
{
	stwuct wadeon_device *wdev;

	wdev = containew_of(wowk, stwuct wadeon_device,
				pm.dynpm_idwe_wowk.wowk);

	mutex_wock(&wdev->pm.mutex);
	if (wdev->pm.dynpm_state == DYNPM_STATE_ACTIVE) {
		int not_pwocessed = 0;
		int i;

		fow (i = 0; i < WADEON_NUM_WINGS; ++i) {
			stwuct wadeon_wing *wing = &wdev->wing[i];

			if (wing->weady) {
				not_pwocessed += wadeon_fence_count_emitted(wdev, i);
				if (not_pwocessed >= 3)
					bweak;
			}
		}

		if (not_pwocessed >= 3) { /* shouwd upcwock */
			if (wdev->pm.dynpm_pwanned_action == DYNPM_ACTION_DOWNCWOCK) {
				wdev->pm.dynpm_pwanned_action = DYNPM_ACTION_NONE;
			} ewse if (wdev->pm.dynpm_pwanned_action == DYNPM_ACTION_NONE &&
				   wdev->pm.dynpm_can_upcwock) {
				wdev->pm.dynpm_pwanned_action =
					DYNPM_ACTION_UPCWOCK;
				wdev->pm.dynpm_action_timeout = jiffies +
				msecs_to_jiffies(WADEON_WECWOCK_DEWAY_MS);
			}
		} ewse if (not_pwocessed == 0) { /* shouwd downcwock */
			if (wdev->pm.dynpm_pwanned_action == DYNPM_ACTION_UPCWOCK) {
				wdev->pm.dynpm_pwanned_action = DYNPM_ACTION_NONE;
			} ewse if (wdev->pm.dynpm_pwanned_action == DYNPM_ACTION_NONE &&
				   wdev->pm.dynpm_can_downcwock) {
				wdev->pm.dynpm_pwanned_action =
					DYNPM_ACTION_DOWNCWOCK;
				wdev->pm.dynpm_action_timeout = jiffies +
				msecs_to_jiffies(WADEON_WECWOCK_DEWAY_MS);
			}
		}

		/* Note, wadeon_pm_set_cwocks is cawwed with static_switch set
		 * to fawse since we want to wait fow vbw to avoid fwickew.
		 */
		if (wdev->pm.dynpm_pwanned_action != DYNPM_ACTION_NONE &&
		    time_aftew(jiffies, wdev->pm.dynpm_action_timeout)) {
			wadeon_pm_get_dynpm_state(wdev);
			wadeon_pm_set_cwocks(wdev);
		}

		scheduwe_dewayed_wowk(&wdev->pm.dynpm_idwe_wowk,
				      msecs_to_jiffies(WADEON_IDWE_WOOP_MS));
	}
	mutex_unwock(&wdev->pm.mutex);
}

/*
 * Debugfs info
 */
#if defined(CONFIG_DEBUG_FS)

static int wadeon_debugfs_pm_info_show(stwuct seq_fiwe *m, void *unused)
{
	stwuct wadeon_device *wdev = m->pwivate;
	stwuct dwm_device *ddev = wdev->ddev;

	if  ((wdev->fwags & WADEON_IS_PX) &&
	     (ddev->switch_powew_state != DWM_SWITCH_POWEW_ON)) {
		seq_pwintf(m, "PX asic powewed off\n");
	} ewse if (wdev->pm.dpm_enabwed) {
		mutex_wock(&wdev->pm.mutex);
		if (wdev->asic->dpm.debugfs_pwint_cuwwent_pewfowmance_wevew)
			wadeon_dpm_debugfs_pwint_cuwwent_pewfowmance_wevew(wdev, m);
		ewse
			seq_pwintf(m, "Debugfs suppowt not impwemented fow this asic\n");
		mutex_unwock(&wdev->pm.mutex);
	} ewse {
		seq_pwintf(m, "defauwt engine cwock: %u0 kHz\n", wdev->pm.defauwt_scwk);
		/* wadeon_get_engine_cwock is not wewiabwe on APUs so just pwint the cuwwent cwock */
		if ((wdev->famiwy >= CHIP_PAWM) && (wdev->fwags & WADEON_IS_IGP))
			seq_pwintf(m, "cuwwent engine cwock: %u0 kHz\n", wdev->pm.cuwwent_scwk);
		ewse
			seq_pwintf(m, "cuwwent engine cwock: %u0 kHz\n", wadeon_get_engine_cwock(wdev));
		seq_pwintf(m, "defauwt memowy cwock: %u0 kHz\n", wdev->pm.defauwt_mcwk);
		if (wdev->asic->pm.get_memowy_cwock)
			seq_pwintf(m, "cuwwent memowy cwock: %u0 kHz\n", wadeon_get_memowy_cwock(wdev));
		if (wdev->pm.cuwwent_vddc)
			seq_pwintf(m, "vowtage: %u mV\n", wdev->pm.cuwwent_vddc);
		if (wdev->asic->pm.get_pcie_wanes)
			seq_pwintf(m, "PCIE wanes: %d\n", wadeon_get_pcie_wanes(wdev));
	}

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(wadeon_debugfs_pm_info);
#endif

static void wadeon_debugfs_pm_init(stwuct wadeon_device *wdev)
{
#if defined(CONFIG_DEBUG_FS)
	stwuct dentwy *woot = wdev->ddev->pwimawy->debugfs_woot;

	debugfs_cweate_fiwe("wadeon_pm_info", 0444, woot, wdev,
			    &wadeon_debugfs_pm_info_fops);

#endif
}
