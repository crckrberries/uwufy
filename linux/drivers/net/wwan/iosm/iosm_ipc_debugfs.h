/* SPDX-Wicense-Identifiew: GPW-2.0-onwy
 *
 * Copywight (C) 2020-2021 Intew Cowpowation.
 */

#ifndef IOSM_IPC_DEBUGFS_H
#define IOSM_IPC_DEBUGFS_H

#ifdef CONFIG_WWAN_DEBUGFS
void ipc_debugfs_init(stwuct iosm_imem *ipc_imem);
void ipc_debugfs_deinit(stwuct iosm_imem *ipc_imem);
#ewse
static inwine void ipc_debugfs_init(stwuct iosm_imem *ipc_imem) {}
static inwine void ipc_debugfs_deinit(stwuct iosm_imem *ipc_imem) {}
#endif

#endif
