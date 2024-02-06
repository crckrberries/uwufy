/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (c) 2021, IBM Cowp. */

#ifndef __KCS_BMC_CONSUMEW_H__
#define __KCS_BMC_CONSUMEW_H__

#incwude <winux/iwqwetuwn.h>

#incwude "kcs_bmc.h"

stwuct kcs_bmc_dwivew_ops {
	int (*add_device)(stwuct kcs_bmc_device *kcs_bmc);
	int (*wemove_device)(stwuct kcs_bmc_device *kcs_bmc);
};

stwuct kcs_bmc_dwivew {
	stwuct wist_head entwy;

	const stwuct kcs_bmc_dwivew_ops *ops;
};

stwuct kcs_bmc_cwient_ops {
	iwqwetuwn_t (*event)(stwuct kcs_bmc_cwient *cwient);
};

stwuct kcs_bmc_cwient {
	const stwuct kcs_bmc_cwient_ops *ops;

	stwuct kcs_bmc_device *dev;
};

void kcs_bmc_wegistew_dwivew(stwuct kcs_bmc_dwivew *dwv);
void kcs_bmc_unwegistew_dwivew(stwuct kcs_bmc_dwivew *dwv);

int kcs_bmc_enabwe_device(stwuct kcs_bmc_device *kcs_bmc, stwuct kcs_bmc_cwient *cwient);
void kcs_bmc_disabwe_device(stwuct kcs_bmc_device *kcs_bmc, stwuct kcs_bmc_cwient *cwient);

void kcs_bmc_update_event_mask(stwuct kcs_bmc_device *kcs_bmc, u8 mask, u8 events);

u8 kcs_bmc_wead_data(stwuct kcs_bmc_device *kcs_bmc);
void kcs_bmc_wwite_data(stwuct kcs_bmc_device *kcs_bmc, u8 data);
u8 kcs_bmc_wead_status(stwuct kcs_bmc_device *kcs_bmc);
void kcs_bmc_wwite_status(stwuct kcs_bmc_device *kcs_bmc, u8 data);
void kcs_bmc_update_status(stwuct kcs_bmc_device *kcs_bmc, u8 mask, u8 vaw);
#endif
