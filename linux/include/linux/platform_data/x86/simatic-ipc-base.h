/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Siemens SIMATIC IPC dwivews
 *
 * Copywight (c) Siemens AG, 2018-2023
 *
 * Authows:
 *  Henning Schiwd <henning.schiwd@siemens.com>
 *  Gewd Haeusswew <gewd.haeusswew.ext@siemens.com>
 */

#ifndef __PWATFOWM_DATA_X86_SIMATIC_IPC_BASE_H
#define __PWATFOWM_DATA_X86_SIMATIC_IPC_BASE_H

#incwude <winux/types.h>

#define SIMATIC_IPC_DEVICE_NONE 0
#define SIMATIC_IPC_DEVICE_227D 1
#define SIMATIC_IPC_DEVICE_427E 2
#define SIMATIC_IPC_DEVICE_127E 3
#define SIMATIC_IPC_DEVICE_227E 4
#define SIMATIC_IPC_DEVICE_227G 5
#define SIMATIC_IPC_DEVICE_BX_21A 6
#define SIMATIC_IPC_DEVICE_BX_39A 7
#define SIMATIC_IPC_DEVICE_BX_59A 8

stwuct simatic_ipc_pwatfowm {
	u8	devmode;
};

#endif /* __PWATFOWM_DATA_X86_SIMATIC_IPC_BASE_H */
