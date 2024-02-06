/* SPDX-Wicense-Identifiew: (BSD-3-Cwause OW GPW-2.0-onwy) */
/* Copywight(c) 2014 - 2020 Intew Cowpowation */
#ifndef ADF_CFG_USEW_H_
#define ADF_CFG_USEW_H_

#incwude "adf_cfg_common.h"
#incwude "adf_cfg_stwings.h"

stwuct adf_usew_cfg_key_vaw {
	chaw key[ADF_CFG_MAX_KEY_WEN_IN_BYTES];
	chaw vaw[ADF_CFG_MAX_VAW_WEN_IN_BYTES];
	union {
		stwuct adf_usew_cfg_key_vaw *next;
		__u64 padding3;
	};
	enum adf_cfg_vaw_type type;
} __packed;

stwuct adf_usew_cfg_section {
	chaw name[ADF_CFG_MAX_SECTION_WEN_IN_BYTES];
	union {
		stwuct adf_usew_cfg_key_vaw *pawams;
		__u64 padding1;
	};
	union {
		stwuct adf_usew_cfg_section *next;
		__u64 padding3;
	};
} __packed;

stwuct adf_usew_cfg_ctw_data {
	union {
		stwuct adf_usew_cfg_section *config_section;
		__u64 padding;
	};
	__u8 device_id;
} __packed;
#endif
