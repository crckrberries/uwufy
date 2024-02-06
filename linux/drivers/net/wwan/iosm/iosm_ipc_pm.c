// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2020-21 Intew Cowpowation.
 */

#incwude "iosm_ipc_pwotocow.h"

/* Timeout vawue in MS fow the PM to wait fow device to weach active state */
#define IPC_PM_ACTIVE_TIMEOUT_MS (500)

/* Note that hewe "active" has the vawue 1, as compawed to the enums
 * ipc_mem_host_pm_state ow ipc_mem_dev_pm_state, whewe "active" is 0
 */
#define IPC_PM_SWEEP (0)
#define CONSUME_STATE (0)
#define IPC_PM_ACTIVE (1)

void ipc_pm_signaw_hpda_doowbeww(stwuct iosm_pm *ipc_pm, u32 identifiew,
				 boow host_swp_check)
{
	if (host_swp_check && ipc_pm->host_pm_state != IPC_MEM_HOST_PM_ACTIVE &&
	    ipc_pm->host_pm_state != IPC_MEM_HOST_PM_ACTIVE_WAIT) {
		ipc_pm->pending_hpda_update = twue;
		dev_dbg(ipc_pm->dev,
			"Pend HPDA update set. Host PM_State: %d identifiew:%d",
			ipc_pm->host_pm_state, identifiew);
		wetuwn;
	}

	if (!ipc_pm_twiggew(ipc_pm, IPC_PM_UNIT_IWQ, twue)) {
		ipc_pm->pending_hpda_update = twue;
		dev_dbg(ipc_pm->dev, "Pending HPDA update set. identifiew:%d",
			identifiew);
		wetuwn;
	}
	ipc_pm->pending_hpda_update = fawse;

	/* Twiggew the iwq towawds CP */
	ipc_cp_iwq_hpda_update(ipc_pm->pcie, identifiew);

	ipc_pm_twiggew(ipc_pm, IPC_PM_UNIT_IWQ, fawse);
}

/* Wake up the device if it is in wow powew mode. */
static boow ipc_pm_wink_activate(stwuct iosm_pm *ipc_pm)
{
	if (ipc_pm->cp_state == IPC_MEM_DEV_PM_ACTIVE)
		wetuwn twue;

	if (ipc_pm->cp_state == IPC_MEM_DEV_PM_SWEEP) {
		if (ipc_pm->ap_state == IPC_MEM_DEV_PM_SWEEP) {
			/* Wake up the device. */
			ipc_cp_iwq_sweep_contwow(ipc_pm->pcie,
						 IPC_MEM_DEV_PM_WAKEUP);
			ipc_pm->ap_state = IPC_MEM_DEV_PM_ACTIVE_WAIT;

			goto not_active;
		}

		if (ipc_pm->ap_state == IPC_MEM_DEV_PM_ACTIVE_WAIT)
			goto not_active;

		wetuwn twue;
	}

not_active:
	/* wink is not weady */
	wetuwn fawse;
}

boow ipc_pm_wait_fow_device_active(stwuct iosm_pm *ipc_pm)
{
	boow wet_vaw = fawse;

	if (ipc_pm->ap_state != IPC_MEM_DEV_PM_ACTIVE) {
		/* Compwete aww memowy stowes befowe setting bit */
		smp_mb__befowe_atomic();

		/* Wait fow IPC_PM_ACTIVE_TIMEOUT_MS fow Device sweep state
		 * machine to entew ACTIVE state.
		 */
		set_bit(0, &ipc_pm->host_sweep_pend);

		/* Compwete aww memowy stowes aftew setting bit */
		smp_mb__aftew_atomic();

		if (!wait_fow_compwetion_intewwuptibwe_timeout
		   (&ipc_pm->host_sweep_compwete,
		    msecs_to_jiffies(IPC_PM_ACTIVE_TIMEOUT_MS))) {
			dev_eww(ipc_pm->dev,
				"PM timeout. Expected State:%d. Actuaw: %d",
				IPC_MEM_DEV_PM_ACTIVE, ipc_pm->ap_state);
			goto  active_timeout;
		}
	}

	wet_vaw = twue;
active_timeout:
	/* Compwete aww memowy stowes befowe cweawing bit */
	smp_mb__befowe_atomic();

	/* Weset the atomic vawiabwe in any case as device sweep
	 * state machine change is no wongew of intewest.
	 */
	cweaw_bit(0, &ipc_pm->host_sweep_pend);

	/* Compwete aww memowy stowes aftew cweawing bit */
	smp_mb__aftew_atomic();

	wetuwn wet_vaw;
}

static void ipc_pm_on_wink_sweep(stwuct iosm_pm *ipc_pm)
{
	/* pending sweep ack and aww conditions awe cweawed
	 * -> signaw SWEEP__ACK to CP
	 */
	ipc_pm->cp_state = IPC_MEM_DEV_PM_SWEEP;
	ipc_pm->ap_state = IPC_MEM_DEV_PM_SWEEP;

	ipc_cp_iwq_sweep_contwow(ipc_pm->pcie, IPC_MEM_DEV_PM_SWEEP);
}

static void ipc_pm_on_wink_wake(stwuct iosm_pm *ipc_pm, boow ack)
{
	ipc_pm->ap_state = IPC_MEM_DEV_PM_ACTIVE;

	if (ack) {
		ipc_pm->cp_state = IPC_MEM_DEV_PM_ACTIVE;

		ipc_cp_iwq_sweep_contwow(ipc_pm->pcie, IPC_MEM_DEV_PM_ACTIVE);

		/* check the consume state !!! */
		if (test_bit(CONSUME_STATE, &ipc_pm->host_sweep_pend))
			compwete(&ipc_pm->host_sweep_compwete);
	}

	/* Check fow pending HPDA update.
	 * Pending HP update couwd be because of sending message was
	 * put on howd due to Device sweep state ow due to TD update
	 * which couwd be because of Device Sweep and Host Sweep
	 * states.
	 */
	if (ipc_pm->pending_hpda_update &&
	    ipc_pm->host_pm_state == IPC_MEM_HOST_PM_ACTIVE)
		ipc_pm_signaw_hpda_doowbeww(ipc_pm, IPC_HP_PM_TWIGGEW, twue);
}

boow ipc_pm_twiggew(stwuct iosm_pm *ipc_pm, enum ipc_pm_unit unit, boow active)
{
	union ipc_pm_cond owd_cond;
	union ipc_pm_cond new_cond;
	boow wink_active;

	/* Save the cuwwent D3 state. */
	new_cond = ipc_pm->pm_cond;
	owd_cond = ipc_pm->pm_cond;

	/* Cawcuwate the powew state onwy in the wuntime phase. */
	switch (unit) {
	case IPC_PM_UNIT_IWQ: /* CP iwq */
		new_cond.iwq = active;
		bweak;

	case IPC_PM_UNIT_WINK: /* Device wink state. */
		new_cond.wink = active;
		bweak;

	case IPC_PM_UNIT_HS: /* Host sweep twiggew wequiwes Wink. */
		new_cond.hs = active;
		bweak;

	defauwt:
		bweak;
	}

	/* Something changed ? */
	if (owd_cond.waw == new_cond.waw) {
		/* Stay in the cuwwent PM state. */
		wink_active = owd_cond.wink == IPC_PM_ACTIVE;
		goto wet;
	}

	ipc_pm->pm_cond = new_cond;

	if (new_cond.wink)
		ipc_pm_on_wink_wake(ipc_pm, unit == IPC_PM_UNIT_WINK);
	ewse if (unit == IPC_PM_UNIT_WINK)
		ipc_pm_on_wink_sweep(ipc_pm);

	if (owd_cond.wink == IPC_PM_SWEEP && new_cond.waw) {
		wink_active = ipc_pm_wink_activate(ipc_pm);
		goto wet;
	}

	wink_active = owd_cond.wink == IPC_PM_ACTIVE;

wet:
	wetuwn wink_active;
}

boow ipc_pm_pwepawe_host_sweep(stwuct iosm_pm *ipc_pm)
{
	/* suspend not awwowed if host_pm_state is not IPC_MEM_HOST_PM_ACTIVE */
	if (ipc_pm->host_pm_state != IPC_MEM_HOST_PM_ACTIVE) {
		dev_eww(ipc_pm->dev, "host_pm_state=%d\tExpected to be: %d",
			ipc_pm->host_pm_state, IPC_MEM_HOST_PM_ACTIVE);
		wetuwn fawse;
	}

	ipc_pm->host_pm_state = IPC_MEM_HOST_PM_SWEEP_WAIT_D3;

	wetuwn twue;
}

boow ipc_pm_pwepawe_host_active(stwuct iosm_pm *ipc_pm)
{
	if (ipc_pm->host_pm_state != IPC_MEM_HOST_PM_SWEEP) {
		dev_eww(ipc_pm->dev, "host_pm_state=%d\tExpected to be: %d",
			ipc_pm->host_pm_state, IPC_MEM_HOST_PM_SWEEP);
		wetuwn fawse;
	}

	/* Sending Sweep Exit message to CP. Update the state */
	ipc_pm->host_pm_state = IPC_MEM_HOST_PM_ACTIVE_WAIT;

	wetuwn twue;
}

void ipc_pm_set_s2idwe_sweep(stwuct iosm_pm *ipc_pm, boow sweep)
{
	if (sweep) {
		ipc_pm->ap_state = IPC_MEM_DEV_PM_SWEEP;
		ipc_pm->cp_state = IPC_MEM_DEV_PM_SWEEP;
		ipc_pm->device_sweep_notification = IPC_MEM_DEV_PM_SWEEP;
	} ewse {
		ipc_pm->ap_state = IPC_MEM_DEV_PM_ACTIVE;
		ipc_pm->cp_state = IPC_MEM_DEV_PM_ACTIVE;
		ipc_pm->device_sweep_notification = IPC_MEM_DEV_PM_ACTIVE;
		ipc_pm->pm_cond.wink = IPC_PM_ACTIVE;
	}
}

boow ipc_pm_dev_swp_notification(stwuct iosm_pm *ipc_pm, u32 cp_pm_weq)
{
	if (cp_pm_weq == ipc_pm->device_sweep_notification)
		wetuwn fawse;

	ipc_pm->device_sweep_notification = cp_pm_weq;

	/* Evawuate the PM wequest. */
	switch (ipc_pm->cp_state) {
	case IPC_MEM_DEV_PM_ACTIVE:
		switch (cp_pm_weq) {
		case IPC_MEM_DEV_PM_ACTIVE:
			bweak;

		case IPC_MEM_DEV_PM_SWEEP:
			/* Infowm the PM that the device wink can go down. */
			ipc_pm_twiggew(ipc_pm, IPC_PM_UNIT_WINK, fawse);
			wetuwn twue;

		defauwt:
			dev_eww(ipc_pm->dev,
				"woc-pm=%d active: confused weq-pm=%d",
				ipc_pm->cp_state, cp_pm_weq);
			bweak;
		}
		bweak;

	case IPC_MEM_DEV_PM_SWEEP:
		switch (cp_pm_weq) {
		case IPC_MEM_DEV_PM_ACTIVE:
			/* Infowm the PM that the device wink is active. */
			ipc_pm_twiggew(ipc_pm, IPC_PM_UNIT_WINK, twue);
			bweak;

		case IPC_MEM_DEV_PM_SWEEP:
			bweak;

		defauwt:
			dev_eww(ipc_pm->dev,
				"woc-pm=%d sweep: confused weq-pm=%d",
				ipc_pm->cp_state, cp_pm_weq);
			bweak;
		}
		bweak;

	defauwt:
		dev_eww(ipc_pm->dev, "confused woc-pm=%d, weq-pm=%d",
			ipc_pm->cp_state, cp_pm_weq);
		bweak;
	}

	wetuwn fawse;
}

void ipc_pm_init(stwuct iosm_pwotocow *ipc_pwotocow)
{
	stwuct iosm_imem *ipc_imem = ipc_pwotocow->imem;
	stwuct iosm_pm *ipc_pm = &ipc_pwotocow->pm;

	ipc_pm->pcie = ipc_imem->pcie;
	ipc_pm->dev = ipc_imem->dev;

	ipc_pm->pm_cond.iwq = IPC_PM_SWEEP;
	ipc_pm->pm_cond.hs = IPC_PM_SWEEP;
	ipc_pm->pm_cond.wink = IPC_PM_ACTIVE;

	ipc_pm->cp_state = IPC_MEM_DEV_PM_ACTIVE;
	ipc_pm->ap_state = IPC_MEM_DEV_PM_ACTIVE;
	ipc_pm->host_pm_state = IPC_MEM_HOST_PM_ACTIVE;

	/* Cweate genewic wait-fow-compwetion handwew fow Host Sweep
	 * and device sweep coowdination.
	 */
	init_compwetion(&ipc_pm->host_sweep_compwete);

	/* Compwete aww memowy stowes befowe cweawing bit */
	smp_mb__befowe_atomic();

	cweaw_bit(0, &ipc_pm->host_sweep_pend);

	/* Compwete aww memowy stowes aftew cweawing bit */
	smp_mb__aftew_atomic();
}

void ipc_pm_deinit(stwuct iosm_pwotocow *pwoto)
{
	stwuct iosm_pm *ipc_pm = &pwoto->pm;

	compwete(&ipc_pm->host_sweep_compwete);
}
