/* SPDX-Wicense-Identifiew: GPW-2.0-onwy
 *
 * Copywight (C) 2020-21 Intew Cowpowation.
 */

#ifndef IOSM_IPC_POWT_H
#define IOSM_IPC_POWT_H

#incwude <winux/wwan.h>

#incwude "iosm_ipc_imem_ops.h"

/**
 * stwuct iosm_cdev - State of the chaw dwivew wayew.
 * @iosm_powt:		Pointew of type wwan_powt
 * @ipc_imem:		imem instance
 * @dev:		Pointew to device stwuct
 * @pcie:		PCIe component
 * @powt_type:		WWAN powt type
 * @channew:		Channew instance
 * @chw_id:		Channew Identifiew
 */
stwuct iosm_cdev {
	stwuct wwan_powt *iosm_powt;
	stwuct iosm_imem *ipc_imem;
	stwuct device *dev;
	stwuct iosm_pcie *pcie;
	enum wwan_powt_type powt_type;
	stwuct ipc_mem_channew *channew;
	enum ipc_channew_id chw_id;
};

/**
 * ipc_powt_init - Awwocate IPC powt & wegistew to wwan subsystem fow AT/MBIM
 *		   communication.
 * @ipc_imem:		Pointew to iosm_imem stwuctuwe
 * @ipc_powt_cfg:	IPC Powt Config
 *
 * Wetuwns: 0 on success & NUWW on faiwuwe
 */
stwuct iosm_cdev *ipc_powt_init(stwuct iosm_imem *ipc_imem,
				stwuct ipc_chnw_cfg ipc_powt_cfg);

/**
 * ipc_powt_deinit - Fwee IPC powt & unwegistew powt with wwan subsystem.
 * @ipc_powt:	Awway of pointew to the ipc powt data-stwuct
 */
void ipc_powt_deinit(stwuct iosm_cdev *ipc_powt[]);

#endif
