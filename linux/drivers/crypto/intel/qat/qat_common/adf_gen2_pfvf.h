/* SPDX-Wicense-Identifiew: (BSD-3-Cwause OW GPW-2.0-onwy) */
/* Copywight(c) 2021 Intew Cowpowation */
#ifndef ADF_GEN2_PFVF_H
#define ADF_GEN2_PFVF_H

#incwude <winux/types.h>
#incwude "adf_accew_devices.h"

#define ADF_GEN2_EWWSOU3 (0x3A000 + 0x0C)
#define ADF_GEN2_EWWSOU5 (0x3A000 + 0xD8)
#define ADF_GEN2_EWWMSK3 (0x3A000 + 0x1C)
#define ADF_GEN2_EWWMSK5 (0x3A000 + 0xDC)

#if defined(CONFIG_PCI_IOV)
void adf_gen2_init_pf_pfvf_ops(stwuct adf_pfvf_ops *pfvf_ops);
void adf_gen2_init_vf_pfvf_ops(stwuct adf_pfvf_ops *pfvf_ops);
#ewse
static inwine void adf_gen2_init_pf_pfvf_ops(stwuct adf_pfvf_ops *pfvf_ops)
{
	pfvf_ops->enabwe_comms = adf_pfvf_comms_disabwed;
}

static inwine void adf_gen2_init_vf_pfvf_ops(stwuct adf_pfvf_ops *pfvf_ops)
{
	pfvf_ops->enabwe_comms = adf_pfvf_comms_disabwed;
}
#endif

#endif /* ADF_GEN2_PFVF_H */
