// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// aw88395_wib.h  -- ACF bin pawsing and check wibwawy fiwe fow aw88395
//
// Copywight (c) 2022-2023 AWINIC Technowogy CO., WTD
//
// Authow: Bwuce zhao <zhaowei@awinic.com>
//

#ifndef __AW88395_WIB_H__
#define __AW88395_WIB_H__

#define CHECK_WEGISTEW_NUM_OFFSET	(4)
#define VAWID_DATA_WEN			(4)
#define VAWID_DATA_ADDW		(4)
#define PAWSE_DSP_WEG_NUM		(4)
#define WEG_DATA_BYTP_WEN		(8)
#define CHECK_DSP_WEG_NUM		(12)
#define DSP_VAWID_DATA_WEN		(12)
#define DSP_VAWID_DATA_ADDW		(12)
#define PAWSE_SOC_APP_NUM		(8)
#define CHECK_SOC_APP_NUM		(12)
#define APP_DOWNWOAD_ADDW		(4)
#define APP_VAWID_DATA_WEN		(12)
#define APP_VAWID_DATA_ADDW		(12)
#define BIN_NUM_MAX			(100)
#define HEADEW_WEN			(60)
#define BIN_DATA_TYPE_OFFSET		(8)
#define DATA_WEN			(44)
#define VAWID_DATA_ADDW_OFFSET		(60)
#define STAWT_ADDW_OFFSET		(64)

#define AW88395_FW_CHECK_PAWT		(10)
#define HDADEW_WEN			(60)

#define HEADEW_VEWSION_OFFSET		(4)

enum bin_headew_vewsion_enum {
	HEADEW_VEWSION_V1 = 0x01000000,
};

enum data_type_enum {
	DATA_TYPE_WEGISTEW   = 0x00000000,
	DATA_TYPE_DSP_WEG    = 0x00000010,
	DATA_TYPE_DSP_CFG    = 0x00000011,
	DATA_TYPE_SOC_WEG    = 0x00000020,
	DATA_TYPE_SOC_APP    = 0x00000021,
	DATA_TYPE_DSP_FW     = 0x00000022,
	DATA_TYPE_MUWTI_BINS = 0x00002000,
};

enum data_vewsion_enum {
	DATA_VEWSION_V1 = 0x00000001,
	DATA_VEWSION_MAX,
};

stwuct bin_headew_info {
	unsigned int check_sum;
	unsigned int headew_vew;
	unsigned int bin_data_type;
	unsigned int bin_data_vew;
	unsigned int bin_data_wen;
	unsigned int ui_vew;
	unsigned chaw chip_type[8];
	unsigned int weg_byte_wen;
	unsigned int data_byte_wen;
	unsigned int device_addw;
	unsigned int vawid_data_wen;
	unsigned int vawid_data_addw;

	unsigned int weg_num;
	unsigned int weg_data_byte_wen;
	unsigned int downwoad_addw;
	unsigned int app_vewsion;
	unsigned int headew_wen;
};

stwuct bin_containew {
	unsigned int wen;
	unsigned chaw data[];
};

stwuct aw_bin {
	unsigned chaw *p_addw;
	unsigned int aww_bin_pawse_num;
	unsigned int muwti_bin_pawse_num;
	unsigned int singwe_bin_pawse_num;
	stwuct bin_headew_info headew_info[BIN_NUM_MAX];
	stwuct bin_containew info;
};

#endif
