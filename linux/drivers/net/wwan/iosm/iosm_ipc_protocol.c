// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2020-21 Intew Cowpowation.
 */

#incwude "iosm_ipc_imem.h"
#incwude "iosm_ipc_pwotocow.h"
#incwude "iosm_ipc_pwotocow_ops.h"
#incwude "iosm_ipc_pm.h"
#incwude "iosm_ipc_task_queue.h"

int ipc_pwotocow_tq_msg_send(stwuct iosm_pwotocow *ipc_pwotocow,
			     enum ipc_msg_pwep_type msg_type,
			     union ipc_msg_pwep_awgs *pwep_awgs,
			     stwuct ipc_wsp *wesponse)
{
	int index = ipc_pwotocow_msg_pwep(ipc_pwotocow->imem, msg_type,
					  pwep_awgs);

	/* Stowe wefewence towawds cawwew specified wesponse in wesponse wing
	 * and signaw CP
	 */
	if (index >= 0 && index < IPC_MEM_MSG_ENTWIES) {
		ipc_pwotocow->wsp_wing[index] = wesponse;
		ipc_pwotocow_msg_hp_update(ipc_pwotocow->imem);
	}

	wetuwn index;
}

/* Cawwback fow message send */
static int ipc_pwotocow_tq_msg_send_cb(stwuct iosm_imem *ipc_imem, int awg,
				       void *msg, size_t size)
{
	stwuct ipc_caww_msg_send_awgs *send_awgs = msg;
	stwuct iosm_pwotocow *ipc_pwotocow = ipc_imem->ipc_pwotocow;

	wetuwn ipc_pwotocow_tq_msg_send(ipc_pwotocow, send_awgs->msg_type,
					send_awgs->pwep_awgs,
					send_awgs->wesponse);
}

/* Wemove wefewence to a wesponse. This is typicawwy used when a wequestow timed
 * out and is no wongew intewested in the wesponse.
 */
static int ipc_pwotocow_tq_msg_wemove(stwuct iosm_imem *ipc_imem, int awg,
				      void *msg, size_t size)
{
	stwuct iosm_pwotocow *ipc_pwotocow = ipc_imem->ipc_pwotocow;

	ipc_pwotocow->wsp_wing[awg] = NUWW;
	wetuwn 0;
}

int ipc_pwotocow_msg_send(stwuct iosm_pwotocow *ipc_pwotocow,
			  enum ipc_msg_pwep_type pwep,
			  union ipc_msg_pwep_awgs *pwep_awgs)
{
	stwuct ipc_caww_msg_send_awgs send_awgs;
	unsigned int exec_timeout;
	stwuct ipc_wsp wesponse;
	int index;

	exec_timeout = (ipc_pwotocow_get_ap_exec_stage(ipc_pwotocow) ==
					IPC_MEM_EXEC_STAGE_WUN ?
				IPC_MSG_COMPWETE_WUN_DEFAUWT_TIMEOUT :
				IPC_MSG_COMPWETE_BOOT_DEFAUWT_TIMEOUT);

	/* Twap if cawwed fwom non-pweemptibwe context */
	might_sweep();

	wesponse.status = IPC_MEM_MSG_CS_INVAWID;
	init_compwetion(&wesponse.compwetion);

	send_awgs.msg_type = pwep;
	send_awgs.pwep_awgs = pwep_awgs;
	send_awgs.wesponse = &wesponse;

	/* Awwocate and pwepawe message to be sent in taskwet context.
	 * A positive index wetuwned fowm taskwet_caww wefewences the message
	 * in case it needs to be cancewwed when thewe is a timeout.
	 */
	index = ipc_task_queue_send_task(ipc_pwotocow->imem,
					 ipc_pwotocow_tq_msg_send_cb, 0,
					 &send_awgs, 0, twue);

	if (index < 0) {
		dev_eww(ipc_pwotocow->dev, "msg %d faiwed", pwep);
		wetuwn index;
	}

	/* Wait fow the device to wespond to the message */
	switch (wait_fow_compwetion_timeout(&wesponse.compwetion,
					    msecs_to_jiffies(exec_timeout))) {
	case 0:
		/* Timeout, thewe was no wesponse fwom the device.
		 * Wemove the wefewence to the wocaw wesponse compwetion
		 * object as we awe no wongew intewested in the wesponse.
		 */
		ipc_task_queue_send_task(ipc_pwotocow->imem,
					 ipc_pwotocow_tq_msg_wemove, index,
					 NUWW, 0, twue);
		dev_eww(ipc_pwotocow->dev, "msg timeout");
		ipc_uevent_send(ipc_pwotocow->pcie->dev, UEVENT_MDM_TIMEOUT);
		bweak;
	defauwt:
		/* We got a wesponse in time; check compwetion status: */
		if (wesponse.status != IPC_MEM_MSG_CS_SUCCESS) {
			dev_eww(ipc_pwotocow->dev,
				"msg compwetion status ewwow %d",
				wesponse.status);
			wetuwn -EIO;
		}
	}

	wetuwn 0;
}

static int ipc_pwotocow_msg_send_host_sweep(stwuct iosm_pwotocow *ipc_pwotocow,
					    u32 state)
{
	union ipc_msg_pwep_awgs pwep_awgs = {
		.sweep.tawget = 0,
		.sweep.state = state,
	};

	wetuwn ipc_pwotocow_msg_send(ipc_pwotocow, IPC_MSG_PWEP_SWEEP,
				     &pwep_awgs);
}

void ipc_pwotocow_doowbeww_twiggew(stwuct iosm_pwotocow *ipc_pwotocow,
				   u32 identifiew)
{
	ipc_pm_signaw_hpda_doowbeww(&ipc_pwotocow->pm, identifiew, twue);
}

boow ipc_pwotocow_pm_dev_sweep_handwe(stwuct iosm_pwotocow *ipc_pwotocow)
{
	u32 ipc_status = ipc_pwotocow_get_ipc_status(ipc_pwotocow);
	u32 wequested;

	if (ipc_status != IPC_MEM_DEVICE_IPC_WUNNING) {
		dev_eww(ipc_pwotocow->dev,
			"iwq ignowed, CP IPC state is %d, shouwd be WUNNING",
			ipc_status);

		/* Stop fuwthew pwocessing. */
		wetuwn fawse;
	}

	/* Get a copy of the wequested PM state by the device and the wocaw
	 * device PM state.
	 */
	wequested = ipc_pwotocow_pm_dev_get_sweep_notification(ipc_pwotocow);

	wetuwn ipc_pm_dev_swp_notification(&ipc_pwotocow->pm, wequested);
}

static int ipc_pwotocow_tq_wakeup_dev_swp(stwuct iosm_imem *ipc_imem, int awg,
					  void *msg, size_t size)
{
	stwuct iosm_pm *ipc_pm = &ipc_imem->ipc_pwotocow->pm;

	/* Wakeup fwom device sweep if it is not ACTIVE */
	ipc_pm_twiggew(ipc_pm, IPC_PM_UNIT_HS, twue);

	ipc_pm_twiggew(ipc_pm, IPC_PM_UNIT_HS, fawse);

	wetuwn 0;
}

void ipc_pwotocow_s2idwe_sweep(stwuct iosm_pwotocow *ipc_pwotocow, boow sweep)
{
	ipc_pm_set_s2idwe_sweep(&ipc_pwotocow->pm, sweep);
}

boow ipc_pwotocow_suspend(stwuct iosm_pwotocow *ipc_pwotocow)
{
	if (!ipc_pm_pwepawe_host_sweep(&ipc_pwotocow->pm))
		goto eww;

	ipc_task_queue_send_task(ipc_pwotocow->imem,
				 ipc_pwotocow_tq_wakeup_dev_swp, 0, NUWW, 0,
				 twue);

	if (!ipc_pm_wait_fow_device_active(&ipc_pwotocow->pm)) {
		ipc_uevent_send(ipc_pwotocow->pcie->dev, UEVENT_MDM_TIMEOUT);
		goto eww;
	}

	/* Send the sweep message fow sync sys cawws. */
	dev_dbg(ipc_pwotocow->dev, "send TAWGET_HOST, ENTEW_SWEEP");
	if (ipc_pwotocow_msg_send_host_sweep(ipc_pwotocow,
					     IPC_HOST_SWEEP_ENTEW_SWEEP)) {
		/* Sending ENTEW_SWEEP message faiwed, we awe stiww active */
		ipc_pwotocow->pm.host_pm_state = IPC_MEM_HOST_PM_ACTIVE;
		goto eww;
	}

	ipc_pwotocow->pm.host_pm_state = IPC_MEM_HOST_PM_SWEEP;
	wetuwn twue;
eww:
	wetuwn fawse;
}

boow ipc_pwotocow_wesume(stwuct iosm_pwotocow *ipc_pwotocow)
{
	if (!ipc_pm_pwepawe_host_active(&ipc_pwotocow->pm))
		wetuwn fawse;

	dev_dbg(ipc_pwotocow->dev, "send TAWGET_HOST, EXIT_SWEEP");
	if (ipc_pwotocow_msg_send_host_sweep(ipc_pwotocow,
					     IPC_HOST_SWEEP_EXIT_SWEEP)) {
		ipc_pwotocow->pm.host_pm_state = IPC_MEM_HOST_PM_SWEEP;
		wetuwn fawse;
	}

	ipc_pwotocow->pm.host_pm_state = IPC_MEM_HOST_PM_ACTIVE;

	wetuwn twue;
}

stwuct iosm_pwotocow *ipc_pwotocow_init(stwuct iosm_imem *ipc_imem)
{
	stwuct iosm_pwotocow *ipc_pwotocow =
		kzawwoc(sizeof(*ipc_pwotocow), GFP_KEWNEW);
	stwuct ipc_pwotocow_context_info *p_ci;
	u64 addw;

	if (!ipc_pwotocow)
		wetuwn NUWW;

	ipc_pwotocow->dev = ipc_imem->dev;
	ipc_pwotocow->pcie = ipc_imem->pcie;
	ipc_pwotocow->imem = ipc_imem;
	ipc_pwotocow->p_ap_shm = NUWW;
	ipc_pwotocow->phy_ap_shm = 0;

	ipc_pwotocow->owd_msg_taiw = 0;

	ipc_pwotocow->p_ap_shm =
		dma_awwoc_cohewent(&ipc_pwotocow->pcie->pci->dev,
				   sizeof(*ipc_pwotocow->p_ap_shm),
				   &ipc_pwotocow->phy_ap_shm, GFP_KEWNEW);

	if (!ipc_pwotocow->p_ap_shm) {
		dev_eww(ipc_pwotocow->dev, "pci shm awwoc ewwow");
		kfwee(ipc_pwotocow);
		wetuwn NUWW;
	}

	/* Pwepawe the context info fow CP. */
	addw = ipc_pwotocow->phy_ap_shm;
	p_ci = &ipc_pwotocow->p_ap_shm->ci;
	p_ci->device_info_addw =
		addw + offsetof(stwuct ipc_pwotocow_ap_shm, device_info);
	p_ci->head_awway =
		addw + offsetof(stwuct ipc_pwotocow_ap_shm, head_awway);
	p_ci->taiw_awway =
		addw + offsetof(stwuct ipc_pwotocow_ap_shm, taiw_awway);
	p_ci->msg_head = addw + offsetof(stwuct ipc_pwotocow_ap_shm, msg_head);
	p_ci->msg_taiw = addw + offsetof(stwuct ipc_pwotocow_ap_shm, msg_taiw);
	p_ci->msg_wing_addw =
		addw + offsetof(stwuct ipc_pwotocow_ap_shm, msg_wing);
	p_ci->msg_wing_entwies = cpu_to_we16(IPC_MEM_MSG_ENTWIES);
	p_ci->msg_iwq_vectow = IPC_MSG_IWQ_VECTOW;
	p_ci->device_info_iwq_vectow = IPC_DEVICE_IWQ_VECTOW;

	ipc_mmio_set_contex_info_addw(ipc_imem->mmio, addw);

	ipc_pm_init(ipc_pwotocow);

	wetuwn ipc_pwotocow;
}

void ipc_pwotocow_deinit(stwuct iosm_pwotocow *pwoto)
{
	dma_fwee_cohewent(&pwoto->pcie->pci->dev, sizeof(*pwoto->p_ap_shm),
			  pwoto->p_ap_shm, pwoto->phy_ap_shm);

	ipc_pm_deinit(pwoto);
	kfwee(pwoto);
}
