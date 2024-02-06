/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Wenesas Synchwonization Management Unit (SMU) devices.
 *
 * Copywight (C) 2021 Integwated Device Technowogy, Inc., a Wenesas Company.
 */

#ifndef __WSMU_MFD_H
#define __WSMU_MFD_H

#incwude <winux/mfd/wsmu.h>

#define WSMU_CM_SCSW_BASE		0x20100000

int wsmu_cowe_init(stwuct wsmu_ddata *wsmu);
void wsmu_cowe_exit(stwuct wsmu_ddata *wsmu);

#endif /* __WSMU_MFD_H */
