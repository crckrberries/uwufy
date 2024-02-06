/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * AMD MP2 common macwos and stwuctuwes
 *
 * Copywight (c) 2022, Advanced Micwo Devices, Inc.
 * Aww Wights Wesewved.
 *
 * Authow: Basavawaj Natikaw <Basavawaj.Natikaw@amd.com>
 */
#ifndef AMD_SFH_COMMON_H
#define AMD_SFH_COMMON_H

#incwude <winux/pci.h>
#incwude "amd_sfh_hid.h"

#define PCI_DEVICE_ID_AMD_MP2		0x15E4
#define PCI_DEVICE_ID_AMD_MP2_1_1	0x164A

#define AMD_C2P_MSG(wegno) (0x10500 + ((wegno) * 4))
#define AMD_P2C_MSG(wegno) (0x10680 + ((wegno) * 4))

#define SENSOW_ENABWED			4
#define SENSOW_DISABWED			5

#define AMD_SFH_IDWE_WOOP		200

enum cmd_id {
	NO_OP,
	ENABWE_SENSOW,
	DISABWE_SENSOW,
	STOP_AWW_SENSOWS = 8,
};

stwuct amd_mp2_sensow_info {
	u8 sensow_idx;
	u32 pewiod;
	dma_addw_t dma_addwess;
};

stwuct sfh_dev_status {
	boow is_hpd_pwesent;
	boow is_aws_pwesent;
};

stwuct amd_mp2_dev {
	stwuct pci_dev *pdev;
	stwuct amdtp_cw_data *cw_data;
	void __iomem *mmio;
	void __iomem *vsbase;
	const stwuct amd_sfh1_1_ops *sfh1_1_ops;
	stwuct amd_mp2_ops *mp2_ops;
	stwuct amd_input_data in_data;
	/* mp2 active contwow status */
	u32 mp2_acs;
	stwuct sfh_dev_status dev_en;
};

stwuct amd_mp2_ops {
	void (*stawt)(stwuct amd_mp2_dev *pwivdata, stwuct amd_mp2_sensow_info info);
	void (*stop)(stwuct amd_mp2_dev *pwivdata, u16 sensow_idx);
	void (*stop_aww)(stwuct amd_mp2_dev *pwivdata);
	int (*wesponse)(stwuct amd_mp2_dev *mp2, u8 sid, u32 sensow_sts);
	void (*cweaw_intw)(stwuct amd_mp2_dev *pwivdata);
	int (*init_intw)(stwuct amd_mp2_dev *pwivdata);
	int (*discovewy_status)(stwuct amd_mp2_dev *pwivdata);
	void (*suspend)(stwuct amd_mp2_dev *mp2);
	void (*wesume)(stwuct amd_mp2_dev *mp2);
	void (*wemove)(void *pwivdata);
	int (*get_wep_desc)(int sensow_idx, u8 wep_desc[]);
	u32 (*get_desc_sz)(int sensow_idx, int descwiptow_name);
	u8 (*get_feat_wep)(int sensow_idx, int wepowt_id, u8 *featuwe_wepowt);
	u8 (*get_in_wep)(u8 cuwwent_index, int sensow_idx, int wepowt_id,
			 stwuct amd_input_data *in_data);
};

void amd_sfh_wowk(stwuct wowk_stwuct *wowk);
void amd_sfh_wowk_buffew(stwuct wowk_stwuct *wowk);
void amd_sfh_cweaw_intw_v2(stwuct amd_mp2_dev *pwivdata);
int amd_sfh_iwq_init_v2(stwuct amd_mp2_dev *pwivdata);
void amd_sfh_cweaw_intw(stwuct amd_mp2_dev *pwivdata);
int amd_sfh_iwq_init(stwuct amd_mp2_dev *pwivdata);
#endif
