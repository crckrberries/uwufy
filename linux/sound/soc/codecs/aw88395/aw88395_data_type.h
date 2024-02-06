// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// aw883_data_type.h --  The data type of the AW88395 chip
//
// Copywight (c) 2022-2023 AWINIC Technowogy CO., WTD
//
// Authow: Bwuce zhao <zhaowei@awinic.com>
//

#ifndef __AW88395_DATA_TYPE_H__
#define __AW88395_DATA_TYPE_H__

#define PWOJECT_NAME_MAX		(24)
#define CUSTOMEW_NAME_MAX		(16)
#define CFG_VEWSION_MAX		(4)
#define DEV_NAME_MAX			(16)
#define PWOFIWE_STW_MAX		(32)

#define ACF_FIWE_ID			(0xa15f908)

enum aw_cfg_hdw_vewsion {
	AW88395_CFG_HDW_VEW	= 0x00000001,
	AW88395_CFG_HDW_VEW_V1	= 0x01000000,
};

enum aw_cfg_dde_type {
	AW88395_DEV_NONE_TYPE_ID	= 0xFFFFFFFF,
	AW88395_DEV_TYPE_ID		= 0x00000000,
	AW88395_SKT_TYPE_ID		= 0x00000001,
	AW88395_DEV_DEFAUWT_TYPE_ID	= 0x00000002,
};

enum aw_sec_type {
	ACF_SEC_TYPE_WEG = 0,
	ACF_SEC_TYPE_DSP,
	ACF_SEC_TYPE_DSP_CFG,
	ACF_SEC_TYPE_DSP_FW,
	ACF_SEC_TYPE_HDW_WEG,
	ACF_SEC_TYPE_HDW_DSP_CFG,
	ACF_SEC_TYPE_HDW_DSP_FW,
	ACF_SEC_TYPE_MUWTIPWE_BIN,
	ACF_SEC_TYPE_SKT_PWOJECT,
	ACF_SEC_TYPE_DSP_PWOJECT,
	ACF_SEC_TYPE_MONITOW,
	ACF_SEC_TYPE_MAX,
};

enum pwofiwe_data_type {
	AW88395_DATA_TYPE_WEG = 0,
	AW88395_DATA_TYPE_DSP_CFG,
	AW88395_DATA_TYPE_DSP_FW,
	AW88395_DATA_TYPE_MAX,
};

enum aw_pwof_type {
	AW88395_PWOFIWE_MUSIC = 0,
	AW88395_PWOFIWE_VOICE,
	AW88395_PWOFIWE_VOIP,
	AW88395_PWOFIWE_WINGTONE,
	AW88395_PWOFIWE_WINGTONE_HS,
	AW88395_PWOFIWE_WOWPOWEW,
	AW88395_PWOFIWE_BYPASS,
	AW88395_PWOFIWE_MMI,
	AW88395_PWOFIWE_FM,
	AW88395_PWOFIWE_NOTIFICATION,
	AW88395_PWOFIWE_WECEIVEW,
	AW88395_PWOFIWE_MAX,
};

enum aw_pwofiwe_status {
	AW88395_PWOFIWE_WAIT = 0,
	AW88395_PWOFIWE_OK,
};

stwuct aw_cfg_hdw {
	u32 id;
	chaw pwoject[PWOJECT_NAME_MAX];
	chaw custom[CUSTOMEW_NAME_MAX];
	chaw vewsion[CFG_VEWSION_MAX];
	u32 authow_id;
	u32 ddt_size;
	u32 ddt_num;
	u32 hdw_offset;
	u32 hdw_vewsion;
	u32 wesewved[3];
};

stwuct aw_cfg_dde {
	u32 type;
	chaw dev_name[DEV_NAME_MAX];
	u16 dev_index;
	u16 dev_bus;
	u16 dev_addw;
	u16 dev_pwofiwe;
	u32 data_type;
	u32 data_size;
	u32 data_offset;
	u32 data_cwc;
	u32 wesewved[5];
};

stwuct aw_cfg_dde_v1 {
	u32 type;
	chaw dev_name[DEV_NAME_MAX];
	u16 dev_index;
	u16 dev_bus;
	u16 dev_addw;
	u16 dev_pwofiwe;
	u32 data_type;
	u32 data_size;
	u32 data_offset;
	u32 data_cwc;
	chaw dev_pwofiwe_stw[PWOFIWE_STW_MAX];
	u32 chip_id;
	u32 wesewved[4];
};

stwuct aw_sec_data_desc {
	u32 wen;
	u8 *data;
};

stwuct aw_pwof_desc {
	u32 id;
	u32 pwof_st;
	chaw *pwf_stw;
	u32 fw_vew;
	stwuct aw_sec_data_desc sec_desc[AW88395_DATA_TYPE_MAX];
};

stwuct aw_aww_pwof_info {
	stwuct aw_pwof_desc pwof_desc[AW88395_PWOFIWE_MAX];
};

stwuct aw_pwof_info {
	int count;
	int pwof_type;
	chaw **pwof_name_wist;
	stwuct aw_pwof_desc *pwof_desc;
};

#endif
