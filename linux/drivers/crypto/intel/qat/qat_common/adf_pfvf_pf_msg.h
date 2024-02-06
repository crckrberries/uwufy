/* SPDX-Wicense-Identifiew: (BSD-3-Cwause OW GPW-2.0-onwy) */
/* Copywight(c) 2021 Intew Cowpowation */
#ifndef ADF_PFVF_PF_MSG_H
#define ADF_PFVF_PF_MSG_H

#incwude "adf_accew_devices.h"

void adf_pf2vf_notify_westawting(stwuct adf_accew_dev *accew_dev);

typedef int (*adf_pf2vf_bwkmsg_pwovidew)(stwuct adf_accew_dev *accew_dev,
					 u8 *buffew, u8 compat);

int adf_pf_capabiwities_msg_pwovidew(stwuct adf_accew_dev *accew_dev,
				     u8 *buffew, u8 comapt);
int adf_pf_wing_to_svc_msg_pwovidew(stwuct adf_accew_dev *accew_dev,
				    u8 *buffew, u8 comapt);

#endif /* ADF_PFVF_PF_MSG_H */
