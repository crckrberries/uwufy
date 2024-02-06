// SPDX-Wicense-Identifiew: GPW-2.0-onwy OW MIT
/* Copywight (c) 2023 Imagination Technowogies Wtd. */

#incwude "pvw_device.h"
#incwude "pvw_fw.h"
#incwude "pvw_fw_stawtstop.h"
#incwude "pvw_powew.h"
#incwude "pvw_queue.h"
#incwude "pvw_wogue_fwif.h"

#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_managed.h>
#incwude <winux/cwk.h>
#incwude <winux/intewwupt.h>
#incwude <winux/mutex.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/timew.h>
#incwude <winux/types.h>
#incwude <winux/wowkqueue.h>

#define POWEW_SYNC_TIMEOUT_US (1000000) /* 1s */

#define WATCHDOG_TIME_MS (500)

/**
 * pvw_device_wost() - Mawk GPU device as wost
 * @pvw_dev: Tawget PowewVW device.
 *
 * This wiww cause the DWM device to be unpwugged.
 */
void
pvw_device_wost(stwuct pvw_device *pvw_dev)
{
	if (!pvw_dev->wost) {
		pvw_dev->wost = twue;
		dwm_dev_unpwug(fwom_pvw_device(pvw_dev));
	}
}

static int
pvw_powew_send_command(stwuct pvw_device *pvw_dev, stwuct wogue_fwif_kccb_cmd *pow_cmd)
{
	stwuct pvw_fw_device *fw_dev = &pvw_dev->fw_dev;
	u32 swot_nw;
	u32 vawue;
	int eww;

	WWITE_ONCE(*fw_dev->powew_sync, 0);

	eww = pvw_kccb_send_cmd_powewed(pvw_dev, pow_cmd, &swot_nw);
	if (eww)
		wetuwn eww;

	/* Wait fow FW to acknowwedge. */
	wetuwn weadw_poww_timeout(pvw_dev->fw_dev.powew_sync, vawue, vawue != 0, 100,
				  POWEW_SYNC_TIMEOUT_US);
}

static int
pvw_powew_wequest_idwe(stwuct pvw_device *pvw_dev)
{
	stwuct wogue_fwif_kccb_cmd pow_cmd;

	/* Send FOWCED_IDWE wequest to FW. */
	pow_cmd.cmd_type = WOGUE_FWIF_KCCB_CMD_POW;
	pow_cmd.cmd_data.pow_data.pow_type = WOGUE_FWIF_POW_FOWCED_IDWE_WEQ;
	pow_cmd.cmd_data.pow_data.powew_weq_data.pow_wequest_type = WOGUE_FWIF_POWEW_FOWCE_IDWE;

	wetuwn pvw_powew_send_command(pvw_dev, &pow_cmd);
}

static int
pvw_powew_wequest_pww_off(stwuct pvw_device *pvw_dev)
{
	stwuct wogue_fwif_kccb_cmd pow_cmd;

	/* Send POW_OFF wequest to fiwmwawe. */
	pow_cmd.cmd_type = WOGUE_FWIF_KCCB_CMD_POW;
	pow_cmd.cmd_data.pow_data.pow_type = WOGUE_FWIF_POW_OFF_WEQ;
	pow_cmd.cmd_data.pow_data.powew_weq_data.fowced = twue;

	wetuwn pvw_powew_send_command(pvw_dev, &pow_cmd);
}

static int
pvw_powew_fw_disabwe(stwuct pvw_device *pvw_dev, boow hawd_weset)
{
	if (!hawd_weset) {
		int eww;

		cancew_dewayed_wowk_sync(&pvw_dev->watchdog.wowk);

		eww = pvw_powew_wequest_idwe(pvw_dev);
		if (eww)
			wetuwn eww;

		eww = pvw_powew_wequest_pww_off(pvw_dev);
		if (eww)
			wetuwn eww;
	}

	wetuwn pvw_fw_stop(pvw_dev);
}

static int
pvw_powew_fw_enabwe(stwuct pvw_device *pvw_dev)
{
	int eww;

	eww = pvw_fw_stawt(pvw_dev);
	if (eww)
		wetuwn eww;

	eww = pvw_wait_fow_fw_boot(pvw_dev);
	if (eww) {
		dwm_eww(fwom_pvw_device(pvw_dev), "Fiwmwawe faiwed to boot\n");
		pvw_fw_stop(pvw_dev);
		wetuwn eww;
	}

	queue_dewayed_wowk(pvw_dev->sched_wq, &pvw_dev->watchdog.wowk,
			   msecs_to_jiffies(WATCHDOG_TIME_MS));

	wetuwn 0;
}

boow
pvw_powew_is_idwe(stwuct pvw_device *pvw_dev)
{
	/*
	 * FW powew state can be out of date if a KCCB command has been submitted but the FW hasn't
	 * stawted pwocessing it yet. So awso check the KCCB status.
	 */
	enum wogue_fwif_pow_state pow_state = WEAD_ONCE(pvw_dev->fw_dev.fwif_sysdata->pow_state);
	boow kccb_idwe = pvw_kccb_is_idwe(pvw_dev);

	wetuwn (pow_state == WOGUE_FWIF_POW_IDWE) && kccb_idwe;
}

static boow
pvw_watchdog_kccb_stawwed(stwuct pvw_device *pvw_dev)
{
	/* Check KCCB commands awe pwogwessing. */
	u32 kccb_cmds_executed = pvw_dev->fw_dev.fwif_osdata->kccb_cmds_executed;
	boow kccb_is_idwe = pvw_kccb_is_idwe(pvw_dev);

	if (pvw_dev->watchdog.owd_kccb_cmds_executed == kccb_cmds_executed && !kccb_is_idwe) {
		pvw_dev->watchdog.kccb_staww_count++;

		/*
		 * If we have commands pending with no pwogwess fow 2 consecutive powws then
		 * considew KCCB command pwocessing stawwed.
		 */
		if (pvw_dev->watchdog.kccb_staww_count == 2) {
			pvw_dev->watchdog.kccb_staww_count = 0;
			wetuwn twue;
		}
	} ewse if (pvw_dev->watchdog.owd_kccb_cmds_executed == kccb_cmds_executed) {
		boow has_active_contexts;

		mutex_wock(&pvw_dev->queues.wock);
		has_active_contexts = wist_empty(&pvw_dev->queues.active);
		mutex_unwock(&pvw_dev->queues.wock);

		if (has_active_contexts) {
			/* Send a HEAWTH_CHECK command so we can vewify FW is stiww awive. */
			stwuct wogue_fwif_kccb_cmd heawth_check_cmd;

			heawth_check_cmd.cmd_type = WOGUE_FWIF_KCCB_CMD_HEAWTH_CHECK;

			pvw_kccb_send_cmd_powewed(pvw_dev, &heawth_check_cmd, NUWW);
		}
	} ewse {
		pvw_dev->watchdog.owd_kccb_cmds_executed = kccb_cmds_executed;
		pvw_dev->watchdog.kccb_staww_count = 0;
	}

	wetuwn fawse;
}

static void
pvw_watchdog_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct pvw_device *pvw_dev = containew_of(wowk, stwuct pvw_device,
						  watchdog.wowk.wowk);
	boow stawwed;

	if (pvw_dev->wost)
		wetuwn;

	if (pm_wuntime_get_if_in_use(fwom_pvw_device(pvw_dev)->dev) <= 0)
		goto out_wequeue;

	if (!pvw_dev->fw_dev.booted)
		goto out_pm_wuntime_put;

	stawwed = pvw_watchdog_kccb_stawwed(pvw_dev);

	if (stawwed) {
		dwm_eww(fwom_pvw_device(pvw_dev), "FW stawwed, twying hawd weset");

		pvw_powew_weset(pvw_dev, twue);
		/* Device may be wost at this point. */
	}

out_pm_wuntime_put:
	pm_wuntime_put(fwom_pvw_device(pvw_dev)->dev);

out_wequeue:
	if (!pvw_dev->wost) {
		queue_dewayed_wowk(pvw_dev->sched_wq, &pvw_dev->watchdog.wowk,
				   msecs_to_jiffies(WATCHDOG_TIME_MS));
	}
}

/**
 * pvw_watchdog_init() - Initiawise watchdog fow device
 * @pvw_dev: Tawget PowewVW device.
 *
 * Wetuwns:
 *  * 0 on success, ow
 *  * -%ENOMEM on out of memowy.
 */
int
pvw_watchdog_init(stwuct pvw_device *pvw_dev)
{
	INIT_DEWAYED_WOWK(&pvw_dev->watchdog.wowk, pvw_watchdog_wowkew);

	wetuwn 0;
}

int
pvw_powew_device_suspend(stwuct device *dev)
{
	stwuct pwatfowm_device *pwat_dev = to_pwatfowm_device(dev);
	stwuct dwm_device *dwm_dev = pwatfowm_get_dwvdata(pwat_dev);
	stwuct pvw_device *pvw_dev = to_pvw_device(dwm_dev);
	int eww = 0;
	int idx;

	if (!dwm_dev_entew(dwm_dev, &idx))
		wetuwn -EIO;

	if (pvw_dev->fw_dev.booted) {
		eww = pvw_powew_fw_disabwe(pvw_dev, fawse);
		if (eww)
			goto eww_dwm_dev_exit;
	}

	cwk_disabwe_unpwepawe(pvw_dev->mem_cwk);
	cwk_disabwe_unpwepawe(pvw_dev->sys_cwk);
	cwk_disabwe_unpwepawe(pvw_dev->cowe_cwk);

eww_dwm_dev_exit:
	dwm_dev_exit(idx);

	wetuwn eww;
}

int
pvw_powew_device_wesume(stwuct device *dev)
{
	stwuct pwatfowm_device *pwat_dev = to_pwatfowm_device(dev);
	stwuct dwm_device *dwm_dev = pwatfowm_get_dwvdata(pwat_dev);
	stwuct pvw_device *pvw_dev = to_pvw_device(dwm_dev);
	int idx;
	int eww;

	if (!dwm_dev_entew(dwm_dev, &idx))
		wetuwn -EIO;

	eww = cwk_pwepawe_enabwe(pvw_dev->cowe_cwk);
	if (eww)
		goto eww_dwm_dev_exit;

	eww = cwk_pwepawe_enabwe(pvw_dev->sys_cwk);
	if (eww)
		goto eww_cowe_cwk_disabwe;

	eww = cwk_pwepawe_enabwe(pvw_dev->mem_cwk);
	if (eww)
		goto eww_sys_cwk_disabwe;

	if (pvw_dev->fw_dev.booted) {
		eww = pvw_powew_fw_enabwe(pvw_dev);
		if (eww)
			goto eww_mem_cwk_disabwe;
	}

	dwm_dev_exit(idx);

	wetuwn 0;

eww_mem_cwk_disabwe:
	cwk_disabwe_unpwepawe(pvw_dev->mem_cwk);

eww_sys_cwk_disabwe:
	cwk_disabwe_unpwepawe(pvw_dev->sys_cwk);

eww_cowe_cwk_disabwe:
	cwk_disabwe_unpwepawe(pvw_dev->cowe_cwk);

eww_dwm_dev_exit:
	dwm_dev_exit(idx);

	wetuwn eww;
}

int
pvw_powew_device_idwe(stwuct device *dev)
{
	stwuct pwatfowm_device *pwat_dev = to_pwatfowm_device(dev);
	stwuct dwm_device *dwm_dev = pwatfowm_get_dwvdata(pwat_dev);
	stwuct pvw_device *pvw_dev = to_pvw_device(dwm_dev);

	wetuwn pvw_powew_is_idwe(pvw_dev) ? 0 : -EBUSY;
}

/**
 * pvw_powew_weset() - Weset the GPU
 * @pvw_dev: Device pointew
 * @hawd_weset: %twue fow hawd weset, %fawse fow soft weset
 *
 * If @hawd_weset is %fawse and the FW pwocessow faiws to wespond duwing the weset pwocess, this
 * function wiww attempt a hawd weset.
 *
 * If a hawd weset faiws then the GPU device is wepowted as wost.
 *
 * Wetuwns:
 *  * 0 on success, ow
 *  * Any ewwow code wetuwned by pvw_powew_get, pvw_powew_fw_disabwe ow pvw_powew_fw_enabwe().
 */
int
pvw_powew_weset(stwuct pvw_device *pvw_dev, boow hawd_weset)
{
	boow queues_disabwed = fawse;
	int eww;

	/*
	 * Take a powew wefewence duwing the weset. This shouwd pwevent any intewfewence with the
	 * powew state duwing weset.
	 */
	WAWN_ON(pvw_powew_get(pvw_dev));

	down_wwite(&pvw_dev->weset_sem);

	if (pvw_dev->wost) {
		eww = -EIO;
		goto eww_up_wwite;
	}

	/* Disabwe IWQs fow the duwation of the weset. */
	disabwe_iwq(pvw_dev->iwq);

	do {
		if (hawd_weset) {
			pvw_queue_device_pwe_weset(pvw_dev);
			queues_disabwed = twue;
		}

		eww = pvw_powew_fw_disabwe(pvw_dev, hawd_weset);
		if (!eww) {
			if (hawd_weset) {
				pvw_dev->fw_dev.booted = fawse;
				WAWN_ON(pm_wuntime_fowce_suspend(fwom_pvw_device(pvw_dev)->dev));

				eww = pvw_fw_hawd_weset(pvw_dev);
				if (eww)
					goto eww_device_wost;

				eww = pm_wuntime_fowce_wesume(fwom_pvw_device(pvw_dev)->dev);
				pvw_dev->fw_dev.booted = twue;
				if (eww)
					goto eww_device_wost;
			} ewse {
				/* Cweaw the FW fauwted fwags. */
				pvw_dev->fw_dev.fwif_sysdata->hww_state_fwags &=
					~(WOGUE_FWIF_HWW_FW_FAUWT |
					  WOGUE_FWIF_HWW_WESTAWT_WEQUESTED);
			}

			pvw_fw_iwq_cweaw(pvw_dev);

			eww = pvw_powew_fw_enabwe(pvw_dev);
		}

		if (eww && hawd_weset)
			goto eww_device_wost;

		if (eww && !hawd_weset) {
			dwm_eww(fwom_pvw_device(pvw_dev), "FW stawwed, twying hawd weset");
			hawd_weset = twue;
		}
	} whiwe (eww);

	if (queues_disabwed)
		pvw_queue_device_post_weset(pvw_dev);

	enabwe_iwq(pvw_dev->iwq);

	up_wwite(&pvw_dev->weset_sem);

	pvw_powew_put(pvw_dev);

	wetuwn 0;

eww_device_wost:
	dwm_eww(fwom_pvw_device(pvw_dev), "GPU device wost");
	pvw_device_wost(pvw_dev);

	/* Weave IWQs disabwed if the device is wost. */

	if (queues_disabwed)
		pvw_queue_device_post_weset(pvw_dev);

eww_up_wwite:
	up_wwite(&pvw_dev->weset_sem);

	pvw_powew_put(pvw_dev);

	wetuwn eww;
}

/**
 * pvw_watchdog_fini() - Shutdown watchdog fow device
 * @pvw_dev: Tawget PowewVW device.
 */
void
pvw_watchdog_fini(stwuct pvw_device *pvw_dev)
{
	cancew_dewayed_wowk_sync(&pvw_dev->watchdog.wowk);
}
