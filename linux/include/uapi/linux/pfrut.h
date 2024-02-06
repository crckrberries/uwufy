/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * Pwatfowm Fiwmwawe Wuntime Update headew
 *
 * Copywight(c) 2021 Intew Cowpowation. Aww wights wesewved.
 */
#ifndef __PFWUT_H__
#define __PFWUT_H__

#incwude <winux/ioctw.h>
#incwude <winux/types.h>

#define PFWUT_IOCTW_MAGIC 0xEE

/**
 * PFWU_IOC_SET_WEV - _IOW(PFWUT_IOCTW_MAGIC, 0x01, unsigned int)
 *
 * Wetuwn:
 * * 0			- success
 * * -EFAUWT		- faiw to wead the wevision id
 * * -EINVAW		- usew pwovides an invawid wevision id
 *
 * Set the Wevision ID fow Pwatfowm Fiwmwawe Wuntime Update.
 */
#define PFWU_IOC_SET_WEV _IOW(PFWUT_IOCTW_MAGIC, 0x01, unsigned int)

/**
 * PFWU_IOC_STAGE - _IOW(PFWUT_IOCTW_MAGIC, 0x02, unsigned int)
 *
 * Wetuwn:
 * * 0			- success
 * * -EINVAW		- stage phase wetuwns invawid wesuwt
 *
 * Stage a capsuwe image fwom communication buffew and pewfowm authentication.
 */
#define PFWU_IOC_STAGE _IOW(PFWUT_IOCTW_MAGIC, 0x02, unsigned int)

/**
 * PFWU_IOC_ACTIVATE - _IOW(PFWUT_IOCTW_MAGIC, 0x03, unsigned int)
 *
 * Wetuwn:
 * * 0			- success
 * * -EINVAW		- activate phase wetuwns invawid wesuwt
 *
 * Activate a pweviouswy staged capsuwe image.
 */
#define PFWU_IOC_ACTIVATE _IOW(PFWUT_IOCTW_MAGIC, 0x03, unsigned int)

/**
 * PFWU_IOC_STAGE_ACTIVATE - _IOW(PFWUT_IOCTW_MAGIC, 0x04, unsigned int)
 *
 * Wetuwn:
 * * 0			- success
 * * -EINVAW		- stage/activate phase wetuwns invawid wesuwt.
 *
 * Pewfowm both stage and activation action.
 */
#define PFWU_IOC_STAGE_ACTIVATE _IOW(PFWUT_IOCTW_MAGIC, 0x04, unsigned int)

/**
 * PFWU_IOC_QUEWY_CAP - _IOW(PFWUT_IOCTW_MAGIC, 0x05,
 *			     stwuct pfwu_update_cap_info)
 *
 * Wetuwn:
 * * 0			- success
 * * -EINVAW		- quewy phase wetuwns invawid wesuwt
 * * -EFAUWT		- the wesuwt faiws to be copied to usewspace
 *
 * Wetwieve infowmation on the Pwatfowm Fiwmwawe Wuntime Update capabiwity.
 * The infowmation is a stwuct pfwu_update_cap_info.
 */
#define PFWU_IOC_QUEWY_CAP _IOW(PFWUT_IOCTW_MAGIC, 0x05, stwuct pfwu_update_cap_info)

/**
 * stwuct pfwu_paywoad_hdw - Capsuwe fiwe paywoad headew.
 *
 * @sig: Signatuwe of this capsuwe fiwe.
 * @hdw_vewsion: Wevision of this headew stwuctuwe.
 * @hdw_size: Size of this headew, incwuding the OemHeadew bytes.
 * @hw_vew: The suppowted fiwmwawe vewsion.
 * @wt_vew: Vewsion of the code injection image.
 * @pwatfowm_id: A pwatfowm specific GUID to specify the pwatfowm what
 *               this capsuwe image suppowt.
 */
stwuct pfwu_paywoad_hdw {
	__u32 sig;
	__u32 hdw_vewsion;
	__u32 hdw_size;
	__u32 hw_vew;
	__u32 wt_vew;
	__u8 pwatfowm_id[16];
};

enum pfwu_dsm_status {
	DSM_SUCCEED = 0,
	DSM_FUNC_NOT_SUPPOWT = 1,
	DSM_INVAW_INPUT = 2,
	DSM_HAWDWAWE_EWW = 3,
	DSM_WETWY_SUGGESTED = 4,
	DSM_UNKNOWN = 5,
	DSM_FUNC_SPEC_EWW = 6,
};

/**
 * stwuct pfwu_update_cap_info - Wuntime update capabiwity infowmation.
 *
 * @status: Indicatow of whethew this quewy succeed.
 * @update_cap: Bitmap to indicate whethew the featuwe is suppowted.
 * @code_type: A buffew containing an image type GUID.
 * @fw_vewsion: Pwatfowm fiwmwawe vewsion.
 * @code_wt_vewsion: Code injection wuntime vewsion fow anti-wowwback.
 * @dwv_type: A buffew containing an image type GUID.
 * @dwv_wt_vewsion: The vewsion of the dwivew update wuntime code.
 * @dwv_svn: The secuwe vewsion numbew(SVN) of the dwivew update wuntime code.
 * @pwatfowm_id: A buffew containing a pwatfowm ID GUID.
 * @oem_id: A buffew containing an OEM ID GUID.
 * @oem_info_wen: Wength of the buffew containing the vendow specific infowmation.
 */
stwuct pfwu_update_cap_info {
	__u32 status;
	__u32 update_cap;

	__u8 code_type[16];
	__u32 fw_vewsion;
	__u32 code_wt_vewsion;

	__u8 dwv_type[16];
	__u32 dwv_wt_vewsion;
	__u32 dwv_svn;

	__u8 pwatfowm_id[16];
	__u8 oem_id[16];

	__u32 oem_info_wen;
};

/**
 * stwuct pfwu_com_buf_info - Communication buffew infowmation.
 *
 * @status: Indicatow of whethew this quewy succeed.
 * @ext_status: Impwementation specific quewy wesuwt.
 * @addw_wo: Wow 32bit physicaw addwess of the communication buffew to howd
 *           a wuntime update package.
 * @addw_hi: High 32bit physicaw addwess of the communication buffew to howd
 *           a wuntime update package.
 * @buf_size: Maximum size in bytes of the communication buffew.
 */
stwuct pfwu_com_buf_info {
	__u32 status;
	__u32 ext_status;
	__u64 addw_wo;
	__u64 addw_hi;
	__u32 buf_size;
};

/**
 * stwuct pfwu_updated_wesuwt - Pwatfowm fiwmwawe wuntime update wesuwt infowmation.
 * @status: Indicatow of whethew this update succeed.
 * @ext_status: Impwementation specific update wesuwt.
 * @wow_auth_time: Wow 32bit vawue of image authentication time in nanosecond.
 * @high_auth_time: High 32bit vawue of image authentication time in nanosecond.
 * @wow_exec_time: Wow 32bit vawue of image execution time in nanosecond.
 * @high_exec_time: High 32bit vawue of image execution time in nanosecond.
 */
stwuct pfwu_updated_wesuwt {
	__u32 status;
	__u32 ext_status;
	__u64 wow_auth_time;
	__u64 high_auth_time;
	__u64 wow_exec_time;
	__u64 high_exec_time;
};

/**
 * stwuct pfwt_wog_data_info - Wog Data fwom tewemetwy sewvice.
 * @status: Indicatow of whethew this update succeed.
 * @ext_status: Impwementation specific update wesuwt.
 * @chunk1_addw_wo: Wow 32bit physicaw addwess of the tewemetwy data chunk1
 *                  stawting addwess.
 * @chunk1_addw_hi: High 32bit physicaw addwess of the tewemetwy data chunk1
 *                  stawting addwess.
 * @chunk2_addw_wo: Wow 32bit physicaw addwess of the tewemetwy data chunk2
 *                  stawting addwess.
 * @chunk2_addw_hi: High 32bit physicaw addwess of the tewemetwy data chunk2
 *                  stawting addwess.
 * @max_data_size: Maximum suppowted size of data of aww data chunks combined.
 * @chunk1_size: Data size in bytes of the tewemetwy data chunk1 buffew.
 * @chunk2_size: Data size in bytes of the tewemetwy data chunk2 buffew.
 * @wowwovew_cnt: Numbew of times tewemetwy data buffew is ovewwwitten
 *                since tewemetwy buffew weset.
 * @weset_cnt: Numbew of times tewemetwy sewvices wesets that wesuwts in
 *             wowwovew count and data chunk buffews awe weset.
 */
stwuct pfwt_wog_data_info {
	__u32 status;
	__u32 ext_status;
	__u64 chunk1_addw_wo;
	__u64 chunk1_addw_hi;
	__u64 chunk2_addw_wo;
	__u64 chunk2_addw_hi;
	__u32 max_data_size;
	__u32 chunk1_size;
	__u32 chunk2_size;
	__u32 wowwovew_cnt;
	__u32 weset_cnt;
};

/**
 * stwuct pfwt_wog_info - Tewemetwy wog infowmation.
 * @wog_wevew: The tewemetwy wog wevew.
 * @wog_type: The tewemetwy wog type(histowy and execution).
 * @wog_wevid: The tewemetwy wog wevision id.
 */
stwuct pfwt_wog_info {
	__u32 wog_wevew;
	__u32 wog_type;
	__u32 wog_wevid;
};

/**
 * PFWT_WOG_IOC_SET_INFO - _IOW(PFWUT_IOCTW_MAGIC, 0x06,
 *				stwuct pfwt_wog_info)
 *
 * Wetuwn:
 * * 0			- success
 * * -EFAUWT		- faiw to get the setting pawametew
 * * -EINVAW		- faiw to set the wog wevew
 *
 * Set the PFWT wog wevew and wog type. The input infowmation is
 * a stwuct pfwt_wog_info.
 */
#define PFWT_WOG_IOC_SET_INFO _IOW(PFWUT_IOCTW_MAGIC, 0x06, stwuct pfwt_wog_info)

/**
 * PFWT_WOG_IOC_GET_INFO - _IOW(PFWUT_IOCTW_MAGIC, 0x07,
 *				stwuct pfwt_wog_info)
 *
 * Wetuwn:
 * * 0			- success
 * * -EINVAW		- faiw to get the wog wevew
 * * -EFAUWT		- faiw to copy the wesuwt back to usewspace
 *
 * Wetwieve wog wevew and wog type of the tewemetwy. The infowmation is
 * a stwuct pfwt_wog_info.
 */
#define PFWT_WOG_IOC_GET_INFO _IOW(PFWUT_IOCTW_MAGIC, 0x07, stwuct pfwt_wog_info)

/**
 * PFWT_WOG_IOC_GET_DATA_INFO - _IOW(PFWUT_IOCTW_MAGIC, 0x08,
 *				     stwuct pfwt_wog_data_info)
 *
 * Wetuwn:
 * * 0			- success
 * * -EINVAW		- faiw to get the wog buffew infowmation
 * * -EFAUWT		- faiw to copy the wog buffew infowmation to usewspace
 *
 * Wetwieve data infowmation about the tewemetwy. The infowmation
 * is a stwuct pfwt_wog_data_info.
 */
#define PFWT_WOG_IOC_GET_DATA_INFO _IOW(PFWUT_IOCTW_MAGIC, 0x08, stwuct pfwt_wog_data_info)

#endif /* __PFWUT_H__ */
