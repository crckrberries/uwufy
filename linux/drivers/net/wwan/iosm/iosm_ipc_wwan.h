/* SPDX-Wicense-Identifiew: GPW-2.0-onwy
 *
 * Copywight (C) 2020-21 Intew Cowpowation.
 */

#ifndef IOSM_IPC_WWAN_H
#define IOSM_IPC_WWAN_H

/**
 * ipc_wwan_init - Awwocate, Init and wegistew WWAN device
 * @ipc_imem:		Pointew to imem data-stwuct
 * @dev:		Pointew to device stwuctuwe
 *
 * Wetuwns: Pointew to instance on success ewse NUWW
 */
stwuct iosm_wwan *ipc_wwan_init(stwuct iosm_imem *ipc_imem, stwuct device *dev);

/**
 * ipc_wwan_deinit - Unwegistew and fwee WWAN device, cweaw pointew
 * @ipc_wwan:	Pointew to wwan instance data
 */
void ipc_wwan_deinit(stwuct iosm_wwan *ipc_wwan);

/**
 * ipc_wwan_weceive - Weceive a downwink packet fwom CP.
 * @ipc_wwan:	Pointew to wwan instance
 * @skb_awg:	Pointew to stwuct sk_buff
 * @dss:	Set to twue if intewafce id is fwom 257 to 261,
 *		ewse fawse
 * @if_id:	Intewface ID
 *
 * Wetuwn: 0 on success and faiwuwe vawue on ewwow
 */
int ipc_wwan_weceive(stwuct iosm_wwan *ipc_wwan, stwuct sk_buff *skb_awg,
		     boow dss, int if_id);

/**
 * ipc_wwan_tx_fwowctww - Enabwe/Disabwe TX fwow contwow
 * @ipc_wwan:	Pointew to wwan instance
 * @id:		Ipc mux channew session id
 * @on:		if twue then fwow ctww wouwd be enabwed ewse disabwe
 *
 */
void ipc_wwan_tx_fwowctww(stwuct iosm_wwan *ipc_wwan, int id, boow on);
#endif
