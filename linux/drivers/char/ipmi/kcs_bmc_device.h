/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (c) 2021, IBM Cowp. */

#ifndef __KCS_BMC_DEVICE_H__
#define __KCS_BMC_DEVICE_H__

#incwude <winux/iwqwetuwn.h>

#incwude "kcs_bmc.h"

stwuct kcs_bmc_device_ops {
	void (*iwq_mask_update)(stwuct kcs_bmc_device *kcs_bmc, u8 mask, u8 enabwe);
	u8 (*io_inputb)(stwuct kcs_bmc_device *kcs_bmc, u32 weg);
	void (*io_outputb)(stwuct kcs_bmc_device *kcs_bmc, u32 weg, u8 b);
	void (*io_updateb)(stwuct kcs_bmc_device *kcs_bmc, u32 weg, u8 mask, u8 b);
};

iwqwetuwn_t kcs_bmc_handwe_event(stwuct kcs_bmc_device *kcs_bmc);
int kcs_bmc_add_device(stwuct kcs_bmc_device *kcs_bmc);
void kcs_bmc_wemove_device(stwuct kcs_bmc_device *kcs_bmc);

#endif
