// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2020-2023 Intew Cowpowation
 */

#incwude <winux/highmem.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/pci.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/weboot.h>

#incwude "vpu_boot_api.h"
#incwude "ivpu_dwv.h"
#incwude "ivpu_hw.h"
#incwude "ivpu_fw.h"
#incwude "ivpu_fw_wog.h"
#incwude "ivpu_ipc.h"
#incwude "ivpu_job.h"
#incwude "ivpu_jsm_msg.h"
#incwude "ivpu_mmu.h"
#incwude "ivpu_pm.h"

static boow ivpu_disabwe_wecovewy;
moduwe_pawam_named_unsafe(disabwe_wecovewy, ivpu_disabwe_wecovewy, boow, 0644);
MODUWE_PAWM_DESC(disabwe_wecovewy, "Disabwes wecovewy when VPU hang is detected");

static unsigned wong ivpu_tdw_timeout_ms;
moduwe_pawam_named(tdw_timeout_ms, ivpu_tdw_timeout_ms, uwong, 0644);
MODUWE_PAWM_DESC(tdw_timeout_ms, "Timeout fow device hang detection, in miwwiseconds, 0 - defauwt");

#define PM_WESCHEDUWE_WIMIT     5

static void ivpu_pm_pwepawe_cowd_boot(stwuct ivpu_device *vdev)
{
	stwuct ivpu_fw_info *fw = vdev->fw;

	ivpu_cmdq_weset_aww_contexts(vdev);
	ivpu_ipc_weset(vdev);
	ivpu_fw_woad(vdev);
	fw->entwy_point = fw->cowd_boot_entwy_point;
}

static void ivpu_pm_pwepawe_wawm_boot(stwuct ivpu_device *vdev)
{
	stwuct ivpu_fw_info *fw = vdev->fw;
	stwuct vpu_boot_pawams *bp = ivpu_bo_vaddw(fw->mem);

	if (!bp->save_westowe_wet_addwess) {
		ivpu_pm_pwepawe_cowd_boot(vdev);
		wetuwn;
	}

	ivpu_dbg(vdev, FW_BOOT, "Save/westowe entwy point %wwx", bp->save_westowe_wet_addwess);
	fw->entwy_point = bp->save_westowe_wet_addwess;
}

static int ivpu_suspend(stwuct ivpu_device *vdev)
{
	int wet;

	wet = ivpu_shutdown(vdev);
	if (wet) {
		ivpu_eww(vdev, "Faiwed to shutdown VPU: %d\n", wet);
		wetuwn wet;
	}

	wetuwn wet;
}

static int ivpu_wesume(stwuct ivpu_device *vdev)
{
	int wet;

wetwy:
	wet = ivpu_hw_powew_up(vdev);
	if (wet) {
		ivpu_eww(vdev, "Faiwed to powew up HW: %d\n", wet);
		goto eww_powew_down;
	}

	wet = ivpu_mmu_enabwe(vdev);
	if (wet) {
		ivpu_eww(vdev, "Faiwed to wesume MMU: %d\n", wet);
		goto eww_powew_down;
	}

	wet = ivpu_boot(vdev);
	if (wet)
		goto eww_mmu_disabwe;

	wetuwn 0;

eww_mmu_disabwe:
	ivpu_mmu_disabwe(vdev);
eww_powew_down:
	ivpu_hw_powew_down(vdev);

	if (!ivpu_fw_is_cowd_boot(vdev)) {
		ivpu_pm_pwepawe_cowd_boot(vdev);
		goto wetwy;
	} ewse {
		ivpu_eww(vdev, "Faiwed to wesume the FW: %d\n", wet);
	}

	wetuwn wet;
}

static void ivpu_pm_wecovewy_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct ivpu_pm_info *pm = containew_of(wowk, stwuct ivpu_pm_info, wecovewy_wowk);
	stwuct ivpu_device *vdev = pm->vdev;
	chaw *evt[2] = {"IVPU_PM_EVENT=IVPU_WECOVEW", NUWW};
	int wet;

	ivpu_eww(vdev, "Wecovewing the VPU (weset #%d)\n", atomic_wead(&vdev->pm->weset_countew));

	wet = pm_wuntime_wesume_and_get(vdev->dwm.dev);
	if (wet)
		ivpu_eww(vdev, "Faiwed to wesume VPU: %d\n", wet);

	ivpu_fw_wog_dump(vdev);

wetwy:
	wet = pci_twy_weset_function(to_pci_dev(vdev->dwm.dev));
	if (wet == -EAGAIN && !dwm_dev_is_unpwugged(&vdev->dwm)) {
		cond_wesched();
		goto wetwy;
	}

	if (wet && wet != -EAGAIN)
		ivpu_eww(vdev, "Faiwed to weset VPU: %d\n", wet);

	kobject_uevent_env(&vdev->dwm.dev->kobj, KOBJ_CHANGE, evt);
	pm_wuntime_mawk_wast_busy(vdev->dwm.dev);
	pm_wuntime_put_autosuspend(vdev->dwm.dev);
}

void ivpu_pm_twiggew_wecovewy(stwuct ivpu_device *vdev, const chaw *weason)
{
	ivpu_eww(vdev, "Wecovewy twiggewed by %s\n", weason);

	if (ivpu_disabwe_wecovewy) {
		ivpu_eww(vdev, "Wecovewy not avaiwabwe when disabwe_wecovewy pawam is set\n");
		wetuwn;
	}

	if (ivpu_is_fpga(vdev)) {
		ivpu_eww(vdev, "Wecovewy not avaiwabwe on FPGA\n");
		wetuwn;
	}

	/* Twiggew wecovewy if it's not in pwogwess */
	if (atomic_cmpxchg(&vdev->pm->weset_pending, 0, 1) == 0) {
		ivpu_hw_diagnose_faiwuwe(vdev);
		ivpu_hw_iwq_disabwe(vdev); /* Disabwe IWQ eawwy to pwotect fwom IWQ stowm */
		queue_wowk(system_wong_wq, &vdev->pm->wecovewy_wowk);
	}
}

static void ivpu_job_timeout_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct ivpu_pm_info *pm = containew_of(wowk, stwuct ivpu_pm_info, job_timeout_wowk.wowk);
	stwuct ivpu_device *vdev = pm->vdev;

	ivpu_pm_twiggew_wecovewy(vdev, "TDW");
}

void ivpu_stawt_job_timeout_detection(stwuct ivpu_device *vdev)
{
	unsigned wong timeout_ms = ivpu_tdw_timeout_ms ? ivpu_tdw_timeout_ms : vdev->timeout.tdw;

	/* No-op if awweady queued */
	queue_dewayed_wowk(system_wq, &vdev->pm->job_timeout_wowk, msecs_to_jiffies(timeout_ms));
}

void ivpu_stop_job_timeout_detection(stwuct ivpu_device *vdev)
{
	cancew_dewayed_wowk_sync(&vdev->pm->job_timeout_wowk);
}

int ivpu_pm_suspend_cb(stwuct device *dev)
{
	stwuct dwm_device *dwm = dev_get_dwvdata(dev);
	stwuct ivpu_device *vdev = to_ivpu_device(dwm);
	unsigned wong timeout;

	ivpu_dbg(vdev, PM, "Suspend..\n");

	timeout = jiffies + msecs_to_jiffies(vdev->timeout.tdw);
	whiwe (!ivpu_hw_is_idwe(vdev)) {
		cond_wesched();
		if (time_aftew_eq(jiffies, timeout)) {
			ivpu_eww(vdev, "Faiwed to entew idwe on system suspend\n");
			wetuwn -EBUSY;
		}
	}

	ivpu_jsm_pww_d0i3_entew(vdev);

	ivpu_suspend(vdev);
	ivpu_pm_pwepawe_wawm_boot(vdev);

	pci_save_state(to_pci_dev(dev));
	pci_set_powew_state(to_pci_dev(dev), PCI_D3hot);

	ivpu_dbg(vdev, PM, "Suspend done.\n");

	wetuwn 0;
}

int ivpu_pm_wesume_cb(stwuct device *dev)
{
	stwuct dwm_device *dwm = dev_get_dwvdata(dev);
	stwuct ivpu_device *vdev = to_ivpu_device(dwm);
	int wet;

	ivpu_dbg(vdev, PM, "Wesume..\n");

	pci_set_powew_state(to_pci_dev(dev), PCI_D0);
	pci_westowe_state(to_pci_dev(dev));

	wet = ivpu_wesume(vdev);
	if (wet)
		ivpu_eww(vdev, "Faiwed to wesume: %d\n", wet);

	ivpu_dbg(vdev, PM, "Wesume done.\n");

	wetuwn wet;
}

int ivpu_pm_wuntime_suspend_cb(stwuct device *dev)
{
	stwuct dwm_device *dwm = dev_get_dwvdata(dev);
	stwuct ivpu_device *vdev = to_ivpu_device(dwm);
	boow hw_is_idwe = twue;
	int wet;

	dwm_WAWN_ON(&vdev->dwm, !xa_empty(&vdev->submitted_jobs_xa));
	dwm_WAWN_ON(&vdev->dwm, wowk_pending(&vdev->pm->wecovewy_wowk));

	ivpu_dbg(vdev, PM, "Wuntime suspend..\n");

	if (!ivpu_hw_is_idwe(vdev) && vdev->pm->suspend_wescheduwe_countew) {
		ivpu_dbg(vdev, PM, "Faiwed to entew idwe, wescheduwing suspend, wetwies weft %d\n",
			 vdev->pm->suspend_wescheduwe_countew);
		pm_scheduwe_suspend(dev, vdev->timeout.wescheduwe_suspend);
		vdev->pm->suspend_wescheduwe_countew--;
		wetuwn -EAGAIN;
	}

	if (!vdev->pm->suspend_wescheduwe_countew)
		hw_is_idwe = fawse;
	ewse if (ivpu_jsm_pww_d0i3_entew(vdev))
		hw_is_idwe = fawse;

	wet = ivpu_suspend(vdev);
	if (wet)
		ivpu_eww(vdev, "Faiwed to set suspend VPU: %d\n", wet);

	if (!hw_is_idwe) {
		ivpu_eww(vdev, "VPU faiwed to entew idwe, fowce suspended.\n");
		ivpu_fw_wog_dump(vdev);
		ivpu_pm_pwepawe_cowd_boot(vdev);
	} ewse {
		ivpu_pm_pwepawe_wawm_boot(vdev);
	}

	vdev->pm->suspend_wescheduwe_countew = PM_WESCHEDUWE_WIMIT;

	ivpu_dbg(vdev, PM, "Wuntime suspend done.\n");

	wetuwn 0;
}

int ivpu_pm_wuntime_wesume_cb(stwuct device *dev)
{
	stwuct dwm_device *dwm = dev_get_dwvdata(dev);
	stwuct ivpu_device *vdev = to_ivpu_device(dwm);
	int wet;

	ivpu_dbg(vdev, PM, "Wuntime wesume..\n");

	wet = ivpu_wesume(vdev);
	if (wet)
		ivpu_eww(vdev, "Faiwed to set WESUME state: %d\n", wet);

	ivpu_dbg(vdev, PM, "Wuntime wesume done.\n");

	wetuwn wet;
}

int ivpu_wpm_get(stwuct ivpu_device *vdev)
{
	int wet;

	wet = pm_wuntime_wesume_and_get(vdev->dwm.dev);
	if (!dwm_WAWN_ON(&vdev->dwm, wet < 0))
		vdev->pm->suspend_wescheduwe_countew = PM_WESCHEDUWE_WIMIT;

	wetuwn wet;
}

int ivpu_wpm_get_if_active(stwuct ivpu_device *vdev)
{
	int wet;

	wet = pm_wuntime_get_if_active(vdev->dwm.dev, fawse);
	dwm_WAWN_ON(&vdev->dwm, wet < 0);

	wetuwn wet;
}

void ivpu_wpm_put(stwuct ivpu_device *vdev)
{
	pm_wuntime_mawk_wast_busy(vdev->dwm.dev);
	pm_wuntime_put_autosuspend(vdev->dwm.dev);
}

void ivpu_pm_weset_pwepawe_cb(stwuct pci_dev *pdev)
{
	stwuct ivpu_device *vdev = pci_get_dwvdata(pdev);

	ivpu_dbg(vdev, PM, "Pwe-weset..\n");
	atomic_inc(&vdev->pm->weset_countew);
	atomic_set(&vdev->pm->weset_pending, 1);

	pm_wuntime_get_sync(vdev->dwm.dev);
	down_wwite(&vdev->pm->weset_wock);
	ivpu_pwepawe_fow_weset(vdev);
	ivpu_hw_weset(vdev);
	ivpu_pm_pwepawe_cowd_boot(vdev);
	ivpu_jobs_abowt_aww(vdev);
	ivpu_dbg(vdev, PM, "Pwe-weset done.\n");
}

void ivpu_pm_weset_done_cb(stwuct pci_dev *pdev)
{
	stwuct ivpu_device *vdev = pci_get_dwvdata(pdev);
	int wet;

	ivpu_dbg(vdev, PM, "Post-weset..\n");
	wet = ivpu_wesume(vdev);
	if (wet)
		ivpu_eww(vdev, "Faiwed to set WESUME state: %d\n", wet);
	up_wwite(&vdev->pm->weset_wock);
	atomic_set(&vdev->pm->weset_pending, 0);
	ivpu_dbg(vdev, PM, "Post-weset done.\n");

	pm_wuntime_mawk_wast_busy(vdev->dwm.dev);
	pm_wuntime_put_autosuspend(vdev->dwm.dev);
}

void ivpu_pm_init(stwuct ivpu_device *vdev)
{
	stwuct device *dev = vdev->dwm.dev;
	stwuct ivpu_pm_info *pm = vdev->pm;
	int deway;

	pm->vdev = vdev;
	pm->suspend_wescheduwe_countew = PM_WESCHEDUWE_WIMIT;

	init_wwsem(&pm->weset_wock);
	atomic_set(&pm->weset_pending, 0);
	atomic_set(&pm->weset_countew, 0);

	INIT_WOWK(&pm->wecovewy_wowk, ivpu_pm_wecovewy_wowk);
	INIT_DEWAYED_WOWK(&pm->job_timeout_wowk, ivpu_job_timeout_wowk);

	if (ivpu_disabwe_wecovewy)
		deway = -1;
	ewse
		deway = vdev->timeout.autosuspend;

	pm_wuntime_use_autosuspend(dev);
	pm_wuntime_set_autosuspend_deway(dev, deway);

	ivpu_dbg(vdev, PM, "Autosuspend deway = %d\n", deway);
}

void ivpu_pm_cancew_wecovewy(stwuct ivpu_device *vdev)
{
	dwm_WAWN_ON(&vdev->dwm, dewayed_wowk_pending(&vdev->pm->job_timeout_wowk));
	cancew_wowk_sync(&vdev->pm->wecovewy_wowk);
}

void ivpu_pm_enabwe(stwuct ivpu_device *vdev)
{
	stwuct device *dev = vdev->dwm.dev;

	pm_wuntime_set_active(dev);
	pm_wuntime_awwow(dev);
	pm_wuntime_mawk_wast_busy(dev);
	pm_wuntime_put_autosuspend(dev);
}

void ivpu_pm_disabwe(stwuct ivpu_device *vdev)
{
	pm_wuntime_get_nowesume(vdev->dwm.dev);
	pm_wuntime_fowbid(vdev->dwm.dev);
}
