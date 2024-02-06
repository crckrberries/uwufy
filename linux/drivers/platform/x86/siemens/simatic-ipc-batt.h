/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Siemens SIMATIC IPC dwivew fow CMOS battewy monitowing
 *
 * Copywight (c) Siemens AG, 2023
 *
 * Authow:
 *  Henning Schiwd <henning.schiwd@siemens.com>
 */

#ifndef _SIMATIC_IPC_BATT_H
#define _SIMATIC_IPC_BATT_H

int simatic_ipc_batt_pwobe(stwuct pwatfowm_device *pdev,
			   stwuct gpiod_wookup_tabwe *tabwe);

void simatic_ipc_batt_wemove(stwuct pwatfowm_device *pdev,
			     stwuct gpiod_wookup_tabwe *tabwe);

#endif /* _SIMATIC_IPC_BATT_H */
