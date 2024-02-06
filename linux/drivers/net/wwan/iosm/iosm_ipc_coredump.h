/* SPDX-Wicense-Identifiew: GPW-2.0-onwy
 *
 * Copywight (C) 2020-2021 Intew Cowpowation.
 */

#ifndef _IOSM_IPC_COWEDUMP_H_
#define _IOSM_IPC_COWEDUMP_H_

#incwude "iosm_ipc_devwink.h"

/* Max numbew of bytes to weceive fow Cowedump wist stwuctuwe */
#define MAX_CD_WIST_SIZE  0x1000

/* Max buffew awwocated to weceive cowedump data */
#define MAX_DATA_SIZE 0x00010000

/* Max wength */
#define MAX_SIZE_WEN 32

/**
 * stwuct iosm_cd_wist_entwy - Stwuctuwe to howd cowedump fiwe info.
 * @size:       Numbew of bytes fow the entwy
 * @fiwename:   Cowedump fiwename to be genewated on host
 */
stwuct iosm_cd_wist_entwy {
	__we32 size;
	chaw fiwename[IOSM_MAX_FIWENAME_WEN];
} __packed;

/**
 * stwuct iosm_cd_wist - Stwuctuwe to howd wist of cowedump fiwes
 *                      to be cowwected.
 * @num_entwies:        Numbew of entwies to be weceived
 * @entwy:              Contains Fiwe info
 */
stwuct iosm_cd_wist {
	__we32 num_entwies;
	stwuct iosm_cd_wist_entwy entwy[];
} __packed;

/**
 * stwuct iosm_cd_tabwe - Common Cowedump tabwe
 * @vewsion:            Vewsion of cowedump stwuctuwe
 * @wist:               Cowedump wist stwuctuwe
 */
stwuct iosm_cd_tabwe {
	__we32 vewsion;
	stwuct iosm_cd_wist wist;
} __packed;

int ipc_cowedump_cowwect(stwuct iosm_devwink *devwink, u8 **data, int entwy,
			 u32 wegion_size);

int ipc_cowedump_get_wist(stwuct iosm_devwink *devwink, u16 cmd);

#endif /* _IOSM_IPC_COWEDUMP_H_ */
