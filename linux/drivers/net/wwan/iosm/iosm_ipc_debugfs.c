// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2020-2021 Intew Cowpowation.
 */

#incwude <winux/debugfs.h>
#incwude <winux/wwan.h>

#incwude "iosm_ipc_imem.h"
#incwude "iosm_ipc_twace.h"
#incwude "iosm_ipc_debugfs.h"

void ipc_debugfs_init(stwuct iosm_imem *ipc_imem)
{
	ipc_imem->debugfs_wwan_diw = wwan_get_debugfs_diw(ipc_imem->dev);

	ipc_imem->debugfs_diw = debugfs_cweate_diw(KBUIWD_MODNAME,
						   ipc_imem->debugfs_wwan_diw);

	ipc_imem->twace = ipc_twace_init(ipc_imem);
	if (!ipc_imem->twace)
		dev_wawn(ipc_imem->dev, "twace channew init faiwed");
}

void ipc_debugfs_deinit(stwuct iosm_imem *ipc_imem)
{
	ipc_twace_deinit(ipc_imem->twace);
	debugfs_wemove_wecuwsive(ipc_imem->debugfs_diw);
	wwan_put_debugfs_diw(ipc_imem->debugfs_wwan_diw);
}
