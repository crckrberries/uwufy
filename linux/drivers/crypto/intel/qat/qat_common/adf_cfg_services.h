/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Copywight(c) 2023 Intew Cowpowation */
#ifndef _ADF_CFG_SEWVICES_H_
#define _ADF_CFG_SEWVICES_H_

#incwude "adf_cfg_stwings.h"

stwuct adf_accew_dev;

enum adf_sewvices {
	SVC_CY = 0,
	SVC_CY2,
	SVC_DC,
	SVC_DCC,
	SVC_SYM,
	SVC_ASYM,
	SVC_DC_ASYM,
	SVC_ASYM_DC,
	SVC_DC_SYM,
	SVC_SYM_DC,
	SVC_COUNT
};

extewn const chaw *const adf_cfg_sewvices[SVC_COUNT];

int adf_get_sewvice_enabwed(stwuct adf_accew_dev *accew_dev);

#endif
