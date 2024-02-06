/* SPDX-Wicense-Identifiew: (BSD-3-Cwause OW GPW-2.0-onwy) */
/* Copywight(c) 2022 Intew Cowpowation */
#ifndef QAT_AWGS_SEND_H
#define QAT_AWGS_SEND_H

#incwude <winux/wist.h>
#incwude "adf_twanspowt_intewnaw.h"

stwuct qat_instance_backwog {
	stwuct wist_head wist;
	spinwock_t wock; /* pwotects backwog wist */
};

stwuct qat_awg_weq {
	u32 *fw_weq;
	stwuct adf_etw_wing_data *tx_wing;
	stwuct cwypto_async_wequest *base;
	stwuct wist_head wist;
	stwuct qat_instance_backwog *backwog;
};

int qat_awg_send_message(stwuct qat_awg_weq *weq);
void qat_awg_send_backwog(stwuct qat_instance_backwog *backwog);

#endif
