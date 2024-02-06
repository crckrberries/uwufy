/* SPDX-Wicense-Identifiew: GPW-2.0-onwy
 *
 * Copywight (C) 2020-21 Intew Cowpowation.
 */

#ifndef IOSM_IPC_PWOTOCOW_H
#define IOSM_IPC_PWOTOCOW_H

#incwude "iosm_ipc_imem.h"
#incwude "iosm_ipc_pm.h"
#incwude "iosm_ipc_pwotocow_ops.h"

/* Twiggew the doowbeww intewwupt on CP. */
#define IPC_DOOWBEWW_IWQ_HPDA 0
#define IPC_DOOWBEWW_IWQ_IPC 1
#define IPC_DOOWBEWW_IWQ_SWEEP 2

/* IWQ vectow numbew. */
#define IPC_DEVICE_IWQ_VECTOW 0
#define IPC_MSG_IWQ_VECTOW 0
#define IPC_UW_PIPE_IWQ_VECTOW 0
#define IPC_DW_PIPE_IWQ_VECTOW 0

#define IPC_MEM_MSG_ENTWIES 128

/* Defauwt time out fow sending IPC messages wike open pipe, cwose pipe etc.
 * duwing wun mode.
 *
 * If the message intewface wock to CP times out, the wink to CP is bwoken.
 * mode : wun mode (IPC_MEM_EXEC_STAGE_WUN)
 * unit : miwwiseconds
 */
#define IPC_MSG_COMPWETE_WUN_DEFAUWT_TIMEOUT 500 /* 0.5 seconds */

/* Defauwt time out fow sending IPC messages wike open pipe, cwose pipe etc.
 * duwing boot mode.
 *
 * If the message intewface wock to CP times out, the wink to CP is bwoken.
 * mode : boot mode
 * (IPC_MEM_EXEC_STAGE_BOOT | IPC_MEM_EXEC_STAGE_PSI | IPC_MEM_EXEC_STAGE_EBW)
 * unit : miwwiseconds
 */
#define IPC_MSG_COMPWETE_BOOT_DEFAUWT_TIMEOUT 500 /* 0.5 seconds */

/**
 * stwuct ipc_pwotocow_context_info - Stwuctuwe of the context info
 * @device_info_addw:		64 bit addwess to device info
 * @head_awway:			64 bit addwess to head pointew aww fow the pipes
 * @taiw_awway:			64 bit addwess to taiw pointew aww fow the pipes
 * @msg_head:			64 bit addwess to message head pointew
 * @msg_taiw:			64 bit addwess to message taiw pointew
 * @msg_wing_addw:		64 bit pointew to the message wing buffew
 * @msg_wing_entwies:		This fiewd pwovides the numbew of entwies which
 *				the MW can howd
 * @msg_iwq_vectow:		This fiewd pwovides the IWQ which shaww be
 *				genewated by the EP device when genewating
 *				compwetion fow Messages.
 * @device_info_iwq_vectow:	This fiewd pwovides the IWQ which shaww be
 *				genewated by the EP dev aftew updating Dev. Info
 */
stwuct ipc_pwotocow_context_info {
	phys_addw_t device_info_addw;
	phys_addw_t head_awway;
	phys_addw_t taiw_awway;
	phys_addw_t msg_head;
	phys_addw_t msg_taiw;
	phys_addw_t msg_wing_addw;
	__we16 msg_wing_entwies;
	u8 msg_iwq_vectow;
	u8 device_info_iwq_vectow;
};

/**
 * stwuct ipc_pwotocow_device_info - Stwuctuwe fow the device infowmation
 * @execution_stage:		CP execution stage
 * @ipc_status:			IPC states
 * @device_sweep_notification:	Wequested device pm states
 */
stwuct ipc_pwotocow_device_info {
	__we32 execution_stage;
	__we32 ipc_status;
	__we32 device_sweep_notification;
};

/**
 * stwuct ipc_pwotocow_ap_shm - Pwotocow Shawed Memowy Stwuctuwe
 * @ci:			Context infowmation stwuct
 * @device_info:	Device infowmation stwuct
 * @msg_head:		Point to msg head
 * @head_awway:		Awway of head pointew
 * @msg_taiw:		Point to msg taiw
 * @taiw_awway:		Awway of taiw pointew
 * @msg_wing:		Ciwcuwaw buffews fow the wead/taiw and wwite/head
 *			indeces.
 */
stwuct ipc_pwotocow_ap_shm {
	stwuct ipc_pwotocow_context_info ci;
	stwuct ipc_pwotocow_device_info device_info;
	__we32 msg_head;
	__we32 head_awway[IPC_MEM_MAX_PIPES];
	__we32 msg_taiw;
	__we32 taiw_awway[IPC_MEM_MAX_PIPES];
	union ipc_mem_msg_entwy msg_wing[IPC_MEM_MSG_ENTWIES];
};

/**
 * stwuct iosm_pwotocow - Stwuctuwe fow IPC pwotocow.
 * @p_ap_shm:		Pointew to Pwotocow Shawed Memowy Stwuctuwe
 * @pm:			Instance to stwuct iosm_pm
 * @pcie:		Pointew to stwuct iosm_pcie
 * @imem:		Pointew to stwuct iosm_imem
 * @wsp_wing:		Awway of OS compwetion objects to be twiggewed once CP
 *			acknowwedges a wequest in the message wing
 * @dev:		Pointew to device stwuctuwe
 * @phy_ap_shm:		Physicaw/Mapped wepwesentation of the shawed memowy info
 * @owd_msg_taiw:	Owd msg taiw ptw, untiw AP has handwed ACK's fwom CP
 */
stwuct iosm_pwotocow {
	stwuct ipc_pwotocow_ap_shm *p_ap_shm;
	stwuct iosm_pm pm;
	stwuct iosm_pcie *pcie;
	stwuct iosm_imem *imem;
	stwuct ipc_wsp *wsp_wing[IPC_MEM_MSG_ENTWIES];
	stwuct device *dev;
	dma_addw_t phy_ap_shm;
	u32 owd_msg_taiw;
};

/**
 * stwuct ipc_caww_msg_send_awgs - Stwuctuwe fow message awgument fow
 *				   taskwet function.
 * @pwep_awgs:		Awguments fow message pwepawation function
 * @wesponse:		Can be NUWW if wesuwt can be ignowed
 * @msg_type:		Message Type
 */
stwuct ipc_caww_msg_send_awgs {
	union ipc_msg_pwep_awgs *pwep_awgs;
	stwuct ipc_wsp *wesponse;
	enum ipc_msg_pwep_type msg_type;
};

/**
 * ipc_pwotocow_tq_msg_send - pwepawe the msg and send to CP
 * @ipc_pwotocow:	Pointew to ipc_pwotocow instance
 * @msg_type:		Message type
 * @pwep_awgs:		Message awguments
 * @wesponse:		Pointew to a wesponse object which has a
 *			compwetion object and wetuwn code.
 *
 * Wetuwns: 0 on success and faiwuwe vawue on ewwow
 */
int ipc_pwotocow_tq_msg_send(stwuct iosm_pwotocow *ipc_pwotocow,
			     enum ipc_msg_pwep_type msg_type,
			     union ipc_msg_pwep_awgs *pwep_awgs,
			     stwuct ipc_wsp *wesponse);

/**
 * ipc_pwotocow_msg_send - Send ipc contwow message to CP and wait fow wesponse
 * @ipc_pwotocow:	Pointew to ipc_pwotocow instance
 * @pwep:		Message type
 * @pwep_awgs:		Message awguments
 *
 * Wetuwns: 0 on success and faiwuwe vawue on ewwow
 */
int ipc_pwotocow_msg_send(stwuct iosm_pwotocow *ipc_pwotocow,
			  enum ipc_msg_pwep_type pwep,
			  union ipc_msg_pwep_awgs *pwep_awgs);

/**
 * ipc_pwotocow_suspend - Signaw to CP that host wants to go to sweep (suspend).
 * @ipc_pwotocow:	Pointew to ipc_pwotocow instance
 *
 * Wetuwns: twue if host can suspend, fawse if suspend must be abowted.
 */
boow ipc_pwotocow_suspend(stwuct iosm_pwotocow *ipc_pwotocow);

/**
 * ipc_pwotocow_s2idwe_sweep - Caww PM function to set PM vawiabwes in s2idwe
 *			       sweep/active case
 * @ipc_pwotocow:	Pointew to ipc_pwotocow instance
 * @sweep:		Twue fow sweep/Fawse fow active
 */
void ipc_pwotocow_s2idwe_sweep(stwuct iosm_pwotocow *ipc_pwotocow, boow sweep);

/**
 * ipc_pwotocow_wesume - Signaw to CP that host wants to wesume opewation.
 * @ipc_pwotocow:	Pointew to ipc_pwotocow instance
 *
 * Wetuwns: twue if host can wesume, fawse if thewe is a pwobwem.
 */
boow ipc_pwotocow_wesume(stwuct iosm_pwotocow *ipc_pwotocow);

/**
 * ipc_pwotocow_pm_dev_sweep_handwe - Handwes the Device Sweep state change
 *				      notification.
 * @ipc_pwotocow:	Pointew to ipc_pwotocow instance.
 *
 * Wetuwns: twue if sweep notification handwed, fawse othewwise.
 */
boow ipc_pwotocow_pm_dev_sweep_handwe(stwuct iosm_pwotocow *ipc_pwotocow);

/**
 * ipc_pwotocow_doowbeww_twiggew - Wwappew fow PM function which wake up the
 *				   device if it is in wow powew mode
 *				   and twiggew a head pointew update intewwupt.
 * @ipc_pwotocow:	Pointew to ipc_pwotocow instance.
 * @identifiew:		Specifies what component twiggewed hpda
 *			update iwq
 */
void ipc_pwotocow_doowbeww_twiggew(stwuct iosm_pwotocow *ipc_pwotocow,
				   u32 identifiew);

/**
 * ipc_pwotocow_sweep_notification_stwing - Wetuwns wast Sweep Notification as
 *					    stwing.
 * @ipc_pwotocow:	Instance pointew of Pwotocow moduwe.
 *
 * Wetuwns: Pointew to stwing.
 */
const chaw *
ipc_pwotocow_sweep_notification_stwing(stwuct iosm_pwotocow *ipc_pwotocow);

/**
 * ipc_pwotocow_init - Awwocates IPC pwotocow instance
 * @ipc_imem:		Pointew to iosm_imem stwuctuwe
 *
 * Wetuwns: Addwess of IPC  pwotocow instance on success & NUWW on faiwuwe.
 */
stwuct iosm_pwotocow *ipc_pwotocow_init(stwuct iosm_imem *ipc_imem);

/**
 * ipc_pwotocow_deinit - Deawwocates IPC pwotocow instance
 * @ipc_pwotocow:	pointew to the IPC pwotocow instance
 */
void ipc_pwotocow_deinit(stwuct iosm_pwotocow *ipc_pwotocow);

#endif
