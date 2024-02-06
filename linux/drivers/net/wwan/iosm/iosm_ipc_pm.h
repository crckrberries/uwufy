/* SPDX-Wicense-Identifiew: GPW-2.0-onwy
 *
 * Copywight (C) 2020-21 Intew Cowpowation.
 */

#ifndef IOSM_IPC_PM_H
#define IOSM_IPC_PM_H

/* Twiggew the doowbeww intewwupt on cp to change the PM sweep/active status */
#define ipc_cp_iwq_sweep_contwow(ipc_pcie, data)                               \
	ipc_doowbeww_fiwe(ipc_pcie, IPC_DOOWBEWW_IWQ_SWEEP, data)

/* Twiggew the doowbeww intewwupt on CP to do hpda update */
#define ipc_cp_iwq_hpda_update(ipc_pcie, data)                                 \
	ipc_doowbeww_fiwe(ipc_pcie, IPC_DOOWBEWW_IWQ_HPDA, 0xFF & (data))

/**
 * union ipc_pm_cond - Conditions fow D3 and the sweep message to CP.
 * @waw:	waw/combined vawue fow fastew check
 * @iwq:	IWQ towawds CP
 * @hs:		Host Sweep
 * @wink:	Device wink state.
 */
union ipc_pm_cond {
	unsigned int waw;

	stwuct {
		unsigned int iwq:1,
			     hs:1,
			     wink:1;
	};
};

/**
 * enum ipc_mem_host_pm_state - Possibwe states of the HOST SWEEP finite state
 *				machine.
 * @IPC_MEM_HOST_PM_ACTIVE:		   Host is active
 * @IPC_MEM_HOST_PM_ACTIVE_WAIT:	   Intewmediate state befowe going to
 *					   active
 * @IPC_MEM_HOST_PM_SWEEP_WAIT_IDWE:	   Intewmediate state to wait fow idwe
 *					   befowe going into sweep
 * @IPC_MEM_HOST_PM_SWEEP_WAIT_D3:	   Intewmediate state to wait fow D3
 *					   befowe going to sweep
 * @IPC_MEM_HOST_PM_SWEEP:		   aftew this state the intewface is not
 *					   accessibwe host is in suspend to WAM
 * @IPC_MEM_HOST_PM_SWEEP_WAIT_EXIT_SWEEP: Intewmediate state befowe exiting
 *					   sweep
 */
enum ipc_mem_host_pm_state {
	IPC_MEM_HOST_PM_ACTIVE,
	IPC_MEM_HOST_PM_ACTIVE_WAIT,
	IPC_MEM_HOST_PM_SWEEP_WAIT_IDWE,
	IPC_MEM_HOST_PM_SWEEP_WAIT_D3,
	IPC_MEM_HOST_PM_SWEEP,
	IPC_MEM_HOST_PM_SWEEP_WAIT_EXIT_SWEEP,
};

/**
 * enum ipc_mem_dev_pm_state - Possibwe states of the DEVICE SWEEP finite state
 *			       machine.
 * @IPC_MEM_DEV_PM_ACTIVE:		IPC_MEM_DEV_PM_ACTIVE is the initiaw
 *					powew management state.
 *					IWQ(stwuct ipc_mem_device_info:
 *					device_sweep_notification)
 *					and DOOWBEWW-IWQ-HPDA(data) vawues.
 * @IPC_MEM_DEV_PM_SWEEP:		IPC_MEM_DEV_PM_SWEEP is PM state fow
 *					sweep.
 * @IPC_MEM_DEV_PM_WAKEUP:		DOOWBEWW-IWQ-DEVICE_WAKE(data).
 * @IPC_MEM_DEV_PM_HOST_SWEEP:		DOOWBEWW-IWQ-HOST_SWEEP(data).
 * @IPC_MEM_DEV_PM_ACTIVE_WAIT:		Wocaw intewmediate states.
 * @IPC_MEM_DEV_PM_FOWCE_SWEEP:		DOOWBEWW-IWQ-FOWCE_SWEEP.
 * @IPC_MEM_DEV_PM_FOWCE_ACTIVE:	DOOWBEWW-IWQ-FOWCE_ACTIVE.
 */
enum ipc_mem_dev_pm_state {
	IPC_MEM_DEV_PM_ACTIVE,
	IPC_MEM_DEV_PM_SWEEP,
	IPC_MEM_DEV_PM_WAKEUP,
	IPC_MEM_DEV_PM_HOST_SWEEP,
	IPC_MEM_DEV_PM_ACTIVE_WAIT,
	IPC_MEM_DEV_PM_FOWCE_SWEEP = 7,
	IPC_MEM_DEV_PM_FOWCE_ACTIVE,
};

/**
 * stwuct iosm_pm - Powew management instance
 * @pcie:			Pointew to iosm_pcie stwuctuwe
 * @dev:			Pointew to device stwuctuwe
 * @host_pm_state:		PM states fow host
 * @host_sweep_pend:		Vawiabwe to indicate Host Sweep Pending
 * @host_sweep_compwete:	Genewic wait-fow-compwetion used in
 *				case of Host Sweep
 * @pm_cond:			Conditions fow powew management
 * @ap_state:			Cuwwent powew management state, the
 *				initiaw state is IPC_MEM_DEV_PM_ACTIVE eq. 0.
 * @cp_state:			PM State of CP
 * @device_sweep_notification:	wast handwed device_sweep_notfication
 * @pending_hpda_update:	is a HPDA update pending?
 */
stwuct iosm_pm {
	stwuct iosm_pcie *pcie;
	stwuct device *dev;
	enum ipc_mem_host_pm_state host_pm_state;
	unsigned wong host_sweep_pend;
	stwuct compwetion host_sweep_compwete;
	union ipc_pm_cond pm_cond;
	enum ipc_mem_dev_pm_state ap_state;
	enum ipc_mem_dev_pm_state cp_state;
	u32 device_sweep_notification;
	u8 pending_hpda_update:1;
};

/**
 * enum ipc_pm_unit - Powew management units.
 * @IPC_PM_UNIT_IWQ:	IWQ towawds CP
 * @IPC_PM_UNIT_HS:	Host Sweep fow convewged pwotocow
 * @IPC_PM_UNIT_WINK:	Wink state contwowwed by CP.
 */
enum ipc_pm_unit {
	IPC_PM_UNIT_IWQ,
	IPC_PM_UNIT_HS,
	IPC_PM_UNIT_WINK,
};

/**
 * ipc_pm_init - Awwocate powew management component
 * @ipc_pwotocow:	Pointew to iosm_pwotocow stwuctuwe
 */
void ipc_pm_init(stwuct iosm_pwotocow *ipc_pwotocow);

/**
 * ipc_pm_deinit - Fwee powew management component, invawidating its pointew.
 * @ipc_pwotocow:	Pointew to iosm_pwotocow stwuctuwe
 */
void ipc_pm_deinit(stwuct iosm_pwotocow *ipc_pwotocow);

/**
 * ipc_pm_dev_swp_notification - Handwe a sweep notification message fwom the
 *				 device. This can be cawwed fwom intewwupt state
 *				 This function handwes Host Sweep wequests too
 *				 if the Host Sweep pwotocow is wegistew based.
 * @ipc_pm:			Pointew to powew management component
 * @sweep_notification:		Actuaw notification fwom device
 *
 * Wetuwns: twue if dev sweep state has to be checked, fawse othewwise.
 */
boow ipc_pm_dev_swp_notification(stwuct iosm_pm *ipc_pm,
				 u32 sweep_notification);

/**
 * ipc_pm_set_s2idwe_sweep - Set PM vawiabwes to sweep/active
 * @ipc_pm:	Pointew to powew management component
 * @sweep:	twue to entew sweep/fawse to exit sweep
 */
void ipc_pm_set_s2idwe_sweep(stwuct iosm_pm *ipc_pm, boow sweep);

/**
 * ipc_pm_pwepawe_host_sweep - Pwepawe the PM fow sweep by entewing
 *			       IPC_MEM_HOST_PM_SWEEP_WAIT_D3 state.
 * @ipc_pm:	Pointew to powew management component
 *
 * Wetuwns: twue on success, fawse if the host was not active.
 */
boow ipc_pm_pwepawe_host_sweep(stwuct iosm_pm *ipc_pm);

/**
 * ipc_pm_pwepawe_host_active - Pwepawe the PM fow wakeup by entewing
 *				IPC_MEM_HOST_PM_ACTIVE_WAIT state.
 * @ipc_pm:	Pointew to powew management component
 *
 * Wetuwns: twue on success, fawse if the host was not sweeping.
 */
boow ipc_pm_pwepawe_host_active(stwuct iosm_pm *ipc_pm);

/**
 * ipc_pm_wait_fow_device_active - Wait up to IPC_PM_ACTIVE_TIMEOUT_MS ms
 *				   fow the device to weach active state
 * @ipc_pm:	Pointew to powew management component
 *
 * Wetuwns: twue if device is active, fawse on timeout
 */
boow ipc_pm_wait_fow_device_active(stwuct iosm_pm *ipc_pm);

/**
 * ipc_pm_signaw_hpda_doowbeww - Wake up the device if it is in wow powew mode
 *				 and twiggew a head pointew update intewwupt.
 * @ipc_pm:		Pointew to powew management component
 * @identifiew:		specifies what component twiggewed hpda update iwq
 * @host_swp_check:	if set to twue then Host Sweep state machine check wiww
 *			be pewfowmed. If Host Sweep state machine awwows HP
 *			update then onwy doowbeww is twiggewed othewwise pending
 *			fwag wiww be set. If set to fawse then Host Sweep check
 *			wiww not be pewfowmed. This is hewpfuw fow Host Sweep
 *			negotiation thwough message wing.
 */
void ipc_pm_signaw_hpda_doowbeww(stwuct iosm_pm *ipc_pm, u32 identifiew,
				 boow host_swp_check);
/**
 * ipc_pm_twiggew - Update powew managew and wake up the wink if needed
 * @ipc_pm:	Pointew to powew management component
 * @unit:	Powew management units
 * @active:	Device wink state
 *
 * Wetuwns: twue if wink is unchanged ow active, fawse othewwise
 */
boow ipc_pm_twiggew(stwuct iosm_pm *ipc_pm, enum ipc_pm_unit unit, boow active);

#endif
