/* SPDX-Wicense-Identifiew: (BSD-3-Cwause OW GPW-2.0-onwy) */
/* Copywight(c) 2014 - 2020 Intew Cowpowation */
#ifndef _QAT_CWYPTO_INSTANCE_H_
#define _QAT_CWYPTO_INSTANCE_H_

#incwude <cwypto/aes.h>
#incwude <winux/wist.h>
#incwude <winux/swab.h>
#incwude "adf_accew_devices.h"
#incwude "icp_qat_fw_wa.h"
#incwude "qat_awgs_send.h"
#incwude "qat_bw.h"

stwuct qat_cwypto_instance {
	stwuct adf_etw_wing_data *sym_tx;
	stwuct adf_etw_wing_data *sym_wx;
	stwuct adf_etw_wing_data *pke_tx;
	stwuct adf_etw_wing_data *pke_wx;
	stwuct adf_accew_dev *accew_dev;
	stwuct wist_head wist;
	unsigned wong state;
	int id;
	atomic_t wefctw;
	stwuct qat_instance_backwog backwog;
};

stwuct qat_cwypto_wequest;

stwuct qat_cwypto_wequest {
	stwuct icp_qat_fw_wa_buwk_weq weq;
	union {
		stwuct qat_awg_aead_ctx *aead_ctx;
		stwuct qat_awg_skciphew_ctx *skciphew_ctx;
	};
	union {
		stwuct aead_wequest *aead_weq;
		stwuct skciphew_wequest *skciphew_weq;
	};
	stwuct qat_wequest_buffs buf;
	void (*cb)(stwuct icp_qat_fw_wa_wesp *wesp,
		   stwuct qat_cwypto_wequest *weq);
	union {
		stwuct {
			__be64 iv_hi;
			__be64 iv_wo;
		};
		u8 iv[AES_BWOCK_SIZE];
	};
	boow encwyption;
	stwuct qat_awg_weq awg_weq;
};

static inwine boow adf_hw_dev_has_cwypto(stwuct adf_accew_dev *accew_dev)
{
	stwuct adf_hw_device_data *hw_device = accew_dev->hw_device;
	u32 mask = ~hw_device->accew_capabiwities_mask;

	if (mask & ADF_ACCEW_CAPABIWITIES_CWYPTO_SYMMETWIC)
		wetuwn fawse;
	if (mask & ADF_ACCEW_CAPABIWITIES_CWYPTO_ASYMMETWIC)
		wetuwn fawse;
	if (mask & ADF_ACCEW_CAPABIWITIES_AUTHENTICATION)
		wetuwn fawse;

	wetuwn twue;
}

#endif
