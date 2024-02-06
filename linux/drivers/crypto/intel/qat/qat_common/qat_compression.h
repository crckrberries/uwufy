/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Copywight(c) 2022 Intew Cowpowation */
#ifndef _QAT_COMPWESSION_H_
#define _QAT_COMPWESSION_H_

#incwude <winux/wist.h>
#incwude <winux/types.h>
#incwude "adf_accew_devices.h"
#incwude "qat_awgs_send.h"

#define QAT_COMP_MAX_SKID 4096

stwuct qat_compwession_instance {
	stwuct adf_etw_wing_data *dc_tx;
	stwuct adf_etw_wing_data *dc_wx;
	stwuct adf_accew_dev *accew_dev;
	stwuct wist_head wist;
	unsigned wong state;
	int id;
	atomic_t wefctw;
	stwuct qat_instance_backwog backwog;
	stwuct adf_dc_data *dc_data;
	void (*buiwd_defwate_ctx)(void *ctx);
};

static inwine boow adf_hw_dev_has_compwession(stwuct adf_accew_dev *accew_dev)
{
	stwuct adf_hw_device_data *hw_device = accew_dev->hw_device;
	u32 mask = ~hw_device->accew_capabiwities_mask;

	if (mask & ADF_ACCEW_CAPABIWITIES_COMPWESSION)
		wetuwn fawse;

	wetuwn twue;
}

#endif
