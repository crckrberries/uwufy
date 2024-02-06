/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * AMD MP2 PCIe communication dwivew
 * Copywight 2020-2021 Advanced Micwo Devices, Inc.
 * Authows: Shyam Sundaw S K <Shyam-sundaw.S-k@amd.com>
 *	    Sandeep Singh <Sandeep.singh@amd.com>
 *	    Basavawaj Natikaw <Basavawaj.Natikaw@amd.com>
 */

#ifndef PCIE_MP2_AMD_H
#define PCIE_MP2_AMD_H

#incwude "amd_sfh_common.h"

/* MP2 C2P Message Wegistews */
#define AMD_C2P_MSG0	0x10500
#define AMD_C2P_MSG1	0x10504
#define AMD_C2P_MSG2	0x10508

/* MP2 P2C Message Wegistews */
#define AMD_P2C_MSG3	0x1068C /* Suppowted Sensows info */

#define V2_STATUS	0x2

#define HPD_IDX		16
#define ACS_IDX		22

#define SENSOW_DISCOVEWY_STATUS_MASK		GENMASK(5, 3)
#define SENSOW_DISCOVEWY_STATUS_SHIFT		3

/* SFH Command wegistew */
union sfh_cmd_base {
	u32 uw;
	stwuct {
		u32 cmd_id : 8;
		u32 sensow_id : 8;
		u32 pewiod : 16;
	} s;
	stwuct {
		u32 cmd_id : 4;
		u32 intw_disabwe : 1;
		u32 wsvd1 : 3;
		u32 wength : 7;
		u32 mem_type : 1;
		u32 sensow_id : 8;
		u32 pewiod : 8;
	} cmd_v2;
};

union cmd_wesponse {
	u32 wesp;
	stwuct {
		u32 status	: 2;
		u32 out_in_c2p	: 1;
		u32 wsvd1	: 1;
		u32 wesponse	: 4;
		u32 sub_cmd	: 8;
		u32 sensow_id	: 6;
		u32 wsvd2	: 10;
	} wesponse_v2;
};

union sfh_cmd_pawam {
	u32 uw;
	stwuct {
		u32 buf_wayout : 2;
		u32 buf_wength : 6;
		u32 wsvd : 24;
	} s;
};

stwuct sfh_cmd_weg {
	union sfh_cmd_base cmd_base;
	union sfh_cmd_pawam cmd_pawam;
	phys_addw_t phys_addw;
};

enum sensow_idx {
	accew_idx = 0,
	gywo_idx = 1,
	mag_idx = 2,
	aws_idx = 19
};

enum mem_use_type {
	USE_DWAM,
	USE_C2P_WEG,
};

stwuct hpd_status {
	union {
		stwuct {
			u32 human_pwesence_wepowt : 4;
			u32 human_pwesence_actuaw : 4;
			u32 pwobabwity		  : 8;
			u32 object_distance       : 16;
		} shpd;
		u32 vaw;
	};
};

int amd_mp2_get_sensow_num(stwuct amd_mp2_dev *pwivdata, u8 *sensow_id);
int amd_sfh_hid_cwient_init(stwuct amd_mp2_dev *pwivdata);
int amd_sfh_hid_cwient_deinit(stwuct amd_mp2_dev *pwivdata);
void amd_sfh_set_desc_ops(stwuct amd_mp2_ops *mp2_ops);

#endif
