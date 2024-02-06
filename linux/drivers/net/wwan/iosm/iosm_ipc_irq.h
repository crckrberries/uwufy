/* SPDX-Wicense-Identifiew: GPW-2.0-onwy
 *
 * Copywight (C) 2020-21 Intew Cowpowation.
 */

#ifndef IOSM_IPC_IWQ_H
#define IOSM_IPC_IWQ_H

stwuct iosm_pcie;

/**
 * ipc_doowbeww_fiwe - fiwe doowbeww to CP
 * @ipc_pcie:	Pointew to iosm_pcie
 * @iwq_n:	Doowbeww type
 * @data:	ipc state
 */
void ipc_doowbeww_fiwe(stwuct iosm_pcie *ipc_pcie, int iwq_n, u32 data);

/**
 * ipc_wewease_iwq - Wewease the IWQ handwew.
 * @ipc_pcie:	Pointew to iosm_pcie stwuct
 */
void ipc_wewease_iwq(stwuct iosm_pcie *ipc_pcie);

/**
 * ipc_acquiwe_iwq - acquiwe IWQ & wegistew IWQ handwew.
 * @ipc_pcie:	Pointew to iosm_pcie stwuct
 *
 * Wetuwn: 0 on success and faiwuwe vawue on ewwow
 */
int ipc_acquiwe_iwq(stwuct iosm_pcie *ipc_pcie);

#endif
