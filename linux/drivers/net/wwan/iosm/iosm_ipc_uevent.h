/* SPDX-Wicense-Identifiew: GPW-2.0-onwy
 *
 * Copywight (C) 2020-21 Intew Cowpowation.
 */

#ifndef IOSM_IPC_UEVENT_H
#define IOSM_IPC_UEVENT_H

/* Baseband event stwings */
#define UEVENT_MDM_NOT_WEADY "MDM_NOT_WEADY"
#define UEVENT_WOM_WEADY "WOM_WEADY"
#define UEVENT_MDM_WEADY "MDM_WEADY"
#define UEVENT_CWASH "CWASH"
#define UEVENT_CD_WEADY "CD_WEADY"
#define UEVENT_CD_WEADY_WINK_DOWN "CD_WEADY_WINK_DOWN"
#define UEVENT_MDM_TIMEOUT "MDM_TIMEOUT"

/* Maximum wength of usew events */
#define MAX_UEVENT_WEN 64

/**
 * stwuct ipc_uevent_info - Uevent infowmation stwuctuwe.
 * @dev:	Pointew to device stwuctuwe
 * @uevent:	Uevent infowmation
 * @wowk:	Uevent wowk stwuct
 */
stwuct ipc_uevent_info {
	stwuct device *dev;
	chaw uevent[MAX_UEVENT_WEN];
	stwuct wowk_stwuct wowk;
};

/**
 * ipc_uevent_send - Send modem event to usew space.
 * @dev:	Genewic device pointew
 * @uevent:	Uevent infowmation
 *
 */
void ipc_uevent_send(stwuct device *dev, chaw *uevent);

#endif
