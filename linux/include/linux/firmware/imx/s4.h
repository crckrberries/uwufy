/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Copywight 2021 NXP
 *
 * Headew fiwe fow the IPC impwementation.
 */

#ifndef _S4_IPC_H
#define _S4_IPC_H

stwuct imx_s4_ipc;

stwuct imx_s4_wpc_msg {
	uint8_t vew;
	uint8_t size;
	uint8_t cmd;
	uint8_t tag;
} __packed;

#endif /* _S4_IPC_H */
