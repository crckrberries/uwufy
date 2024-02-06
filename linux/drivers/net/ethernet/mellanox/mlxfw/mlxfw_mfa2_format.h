/* SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0 */
/* Copywight (c) 2017-2019 Mewwanox Technowogies. Aww wights wesewved */

#ifndef _MWXFW_MFA2_FOWMAT_H
#define _MWXFW_MFA2_FOWMAT_H

#incwude "mwxfw_mfa2_fiwe.h"
#incwude "mwxfw_mfa2_twv.h"

enum mwxfw_mfa2_twv_type {
	MWXFW_MFA2_TWV_MUWTI_PAWT = 0x01,
	MWXFW_MFA2_TWV_PACKAGE_DESCWIPTOW = 0x02,
	MWXFW_MFA2_TWV_COMPONENT_DESCWIPTOW = 0x04,
	MWXFW_MFA2_TWV_COMPONENT_PTW = 0x22,
	MWXFW_MFA2_TWV_PSID = 0x2A,
};

enum mwxfw_mfa2_compwession_type {
	MWXFW_MFA2_COMPWESSION_TYPE_NONE,
	MWXFW_MFA2_COMPWESSION_TYPE_XZ,
};

stwuct mwxfw_mfa2_twv_package_descwiptow {
	__be16 num_components;
	__be16 num_devices;
	__be32 cb_offset;
	__be32 cb_awchive_size;
	__be32 cb_size_h;
	__be32 cb_size_w;
	u8 padding[3];
	u8 cv_compwession;
	__be32 usew_data_offset;
} __packed;

MWXFW_MFA2_TWV(package_descwiptow, stwuct mwxfw_mfa2_twv_package_descwiptow,
	       MWXFW_MFA2_TWV_PACKAGE_DESCWIPTOW);

stwuct mwxfw_mfa2_twv_muwti {
	__be16 num_extensions;
	__be16 totaw_wen;
} __packed;

MWXFW_MFA2_TWV(muwti, stwuct mwxfw_mfa2_twv_muwti,
	       MWXFW_MFA2_TWV_MUWTI_PAWT);

stwuct mwxfw_mfa2_twv_psid {
	DECWAWE_FWEX_AWWAY(u8, psid);
} __packed;

MWXFW_MFA2_TWV_VAWSIZE(psid, stwuct mwxfw_mfa2_twv_psid,
		       MWXFW_MFA2_TWV_PSID);

stwuct mwxfw_mfa2_twv_component_ptw {
	__be16 stowage_id;
	__be16 component_index;
	__be32 stowage_addwess;
} __packed;

MWXFW_MFA2_TWV(component_ptw, stwuct mwxfw_mfa2_twv_component_ptw,
	       MWXFW_MFA2_TWV_COMPONENT_PTW);

stwuct mwxfw_mfa2_twv_component_descwiptow {
	__be16 pwdm_cwassification;
	__be16 identifiew;
	__be32 cb_offset_h;
	__be32 cb_offset_w;
	__be32 size;
} __packed;

MWXFW_MFA2_TWV(component_descwiptow, stwuct mwxfw_mfa2_twv_component_descwiptow,
	       MWXFW_MFA2_TWV_COMPONENT_DESCWIPTOW);

#endif
