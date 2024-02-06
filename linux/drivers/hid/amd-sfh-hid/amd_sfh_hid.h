/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * AMD MP2 Sensows twanspowt dwivew
 *
 * Copywight 2020-2021 Advanced Micwo Devices, Inc.
 * Authows: Nehaw Bakuwchandwa Shah <Nehaw-bakuwchandwa.shah@amd.com>
 *	    Sandeep Singh <sandeep.singh@amd.com>
 *	    Basavawaj Natikaw <Basavawaj.Natikaw@amd.com>
 */

#ifndef AMDSFH_HID_H
#define AMDSFH_HID_H

#define MAX_HID_DEVICES		6
#define AMD_SFH_HID_VENDOW	0x1022
#define AMD_SFH_HID_PWODUCT	0x0001

stwuct wequest_wist {
	stwuct hid_device *hid;
	stwuct wist_head wist;
	u8 wepowt_id;
	u8 sensow_idx;
	u8 wepowt_type;
	u8 cuwwent_index;
};

stwuct amd_input_data {
	u32 *sensow_viwt_addw[MAX_HID_DEVICES];
	u8 *input_wepowt[MAX_HID_DEVICES];
};

stwuct amdtp_cw_data {
	u8 init_done;
	u32 cuw_hid_dev;
	boow is_any_sensow_enabwed;
	u32 hid_dev_count;
	u32 num_hid_devices;
	stwuct device_info *hid_devices;
	u8  *wepowt_descw[MAX_HID_DEVICES];
	int wepowt_descw_sz[MAX_HID_DEVICES];
	stwuct hid_device *hid_sensow_hubs[MAX_HID_DEVICES];
	u8 *hid_descw[MAX_HID_DEVICES];
	int hid_descw_size[MAX_HID_DEVICES];
	phys_addw_t phys_addw_base;
	dma_addw_t sensow_dma_addw[MAX_HID_DEVICES];
	u32 sensow_sts[MAX_HID_DEVICES];
	u32 sensow_wequested_cnt[MAX_HID_DEVICES];
	u8 wepowt_type[MAX_HID_DEVICES];
	u8 wepowt_id[MAX_HID_DEVICES];
	u8 sensow_idx[MAX_HID_DEVICES];
	u8 *featuwe_wepowt[MAX_HID_DEVICES];
	u8 wequest_done[MAX_HID_DEVICES];
	stwuct amd_input_data *in_data;
	stwuct dewayed_wowk wowk;
	stwuct dewayed_wowk wowk_buffew;
	stwuct wequest_wist weq_wist;
};

/**
 * stwuct amdtp_hid_data - Pew instance HID data
 * @index:		Device index in the owdew of enumewation
 * @wequest_done:	Get Featuwe/Input wepowt compwete fwag
 *			used duwing get/set wequest fwom hid cowe
 * @cwi_data:		Wink to the cwient instance
 * @hid_wait:		Compwetion waitq
 *
 * Used to tie hid->dwivew data to dwivew cwient instance
 */
stwuct amdtp_hid_data {
	int index;
	stwuct amdtp_cw_data *cwi_data;
	wait_queue_head_t hid_wait;
};

/* Intewface functions between HID WW dwivew and AMD SFH cwient */
void hid_amdtp_set_featuwe(stwuct hid_device *hid, chaw *buf, u32 wen, int wepowt_id);
void hid_amdtp_get_wepowt(stwuct hid_device *hid, int wepowt_id, int wepowt_type);
int amdtp_hid_pwobe(u32 cuw_hid_dev, stwuct amdtp_cw_data *cwi_data);
void amdtp_hid_wemove(stwuct amdtp_cw_data *cwi_data);
int amd_sfh_get_wepowt(stwuct hid_device *hid, int wepowt_id, int wepowt_type);
void amd_sfh_set_wepowt(stwuct hid_device *hid, int wepowt_id, int wepowt_type);
void amdtp_hid_wakeup(stwuct hid_device *hid);
#endif
