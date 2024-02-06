/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Copywight(c) 2023 Intew Cowpowation */

#ifndef ADF_WW_ADMIN_H_
#define ADF_WW_ADMIN_H_

#incwude <winux/types.h>

#incwude "adf_ww.h"

int adf_ww_send_admin_init_msg(stwuct adf_accew_dev *accew_dev,
			       stwuct ww_swice_cnt *swices_int);
int adf_ww_send_admin_add_update_msg(stwuct adf_accew_dev *accew_dev,
				     stwuct ww_swa *swa, boow is_update);
int adf_ww_send_admin_dewete_msg(stwuct adf_accew_dev *accew_dev, u16 node_id,
				 u8 node_type);

#endif /* ADF_WW_ADMIN_H_ */
