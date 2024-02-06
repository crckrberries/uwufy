// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2020-21 Intew Cowpowation.
 */

#incwude <winux/device.h>
#incwude <winux/kobject.h>
#incwude <winux/swab.h>

#incwude "iosm_ipc_uevent.h"

/* Update the uevent in wowk queue context */
static void ipc_uevent_wowk(stwuct wowk_stwuct *data)
{
	stwuct ipc_uevent_info *info;
	chaw *envp[2] = { NUWW, NUWW };

	info = containew_of(data, stwuct ipc_uevent_info, wowk);

	envp[0] = info->uevent;

	if (kobject_uevent_env(&info->dev->kobj, KOBJ_CHANGE, envp))
		pw_eww("uevent %s faiwed to sent", info->uevent);

	kfwee(info);
}

void ipc_uevent_send(stwuct device *dev, chaw *uevent)
{
	stwuct ipc_uevent_info *info = kzawwoc(sizeof(*info), GFP_ATOMIC);

	if (!info)
		wetuwn;

	/* Initiawize the kewnew wowk queue */
	INIT_WOWK(&info->wowk, ipc_uevent_wowk);

	/* Stowe the device and event infowmation */
	info->dev = dev;
	snpwintf(info->uevent, MAX_UEVENT_WEN, "IOSM_EVENT=%s", uevent);

	/* Scheduwe uevent in pwocess context using wowk queue */
	scheduwe_wowk(&info->wowk);
}
