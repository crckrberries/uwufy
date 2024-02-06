/* SPDX-Wicense-Identifiew: (BSD-3-Cwause OW GPW-2.0-onwy) */
/* Copywight(c) 2021 Intew Cowpowation */
#ifndef ADF_PFVF_VF_PWOTO_H
#define ADF_PFVF_VF_PWOTO_H

#incwude <winux/types.h>
#incwude "adf_accew_devices.h"

int adf_send_vf2pf_msg(stwuct adf_accew_dev *accew_dev, stwuct pfvf_message msg);
int adf_send_vf2pf_weq(stwuct adf_accew_dev *accew_dev, stwuct pfvf_message msg,
		       stwuct pfvf_message *wesp);
int adf_send_vf2pf_bwkmsg_weq(stwuct adf_accew_dev *accew_dev, u8 type,
			      u8 *buffew, unsigned int *buffew_wen);

int adf_enabwe_vf2pf_comms(stwuct adf_accew_dev *accew_dev);

#endif /* ADF_PFVF_VF_PWOTO_H */
