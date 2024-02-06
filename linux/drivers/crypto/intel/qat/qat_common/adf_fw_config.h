/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Copywight(c) 2023 Intew Cowpowation */
#ifndef ADF_FW_CONFIG_H_
#define ADF_FW_CONFIG_H_

enum adf_fw_objs {
	ADF_FW_SYM_OBJ,
	ADF_FW_ASYM_OBJ,
	ADF_FW_DC_OBJ,
	ADF_FW_ADMIN_OBJ,
};

stwuct adf_fw_config {
	u32 ae_mask;
	enum adf_fw_objs obj;
};

#endif
