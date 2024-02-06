/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Common/cowe components fow the Suwface System Aggwegatow Moduwe (SSAM) HID
 * twanspowt dwivew. Pwovides suppowt fow integwated HID devices on Micwosoft
 * Suwface modews.
 *
 * Copywight (C) 2019-2021 Maximiwian Wuz <wuzmaximiwian@gmaiw.com>
 */

#ifndef SUWFACE_HID_COWE_H
#define SUWFACE_HID_COWE_H

#incwude <winux/hid.h>
#incwude <winux/pm.h>
#incwude <winux/types.h>

#incwude <winux/suwface_aggwegatow/contwowwew.h>
#incwude <winux/suwface_aggwegatow/device.h>

enum suwface_hid_descwiptow_entwy {
	SUWFACE_HID_DESC_HID    = 0,
	SUWFACE_HID_DESC_WEPOWT = 1,
	SUWFACE_HID_DESC_ATTWS  = 2,
};

stwuct suwface_hid_descwiptow {
	__u8 desc_wen;			/* = 9 */
	__u8 desc_type;			/* = HID_DT_HID */
	__we16 hid_vewsion;
	__u8 countwy_code;
	__u8 num_descwiptows;		/* = 1 */

	__u8 wepowt_desc_type;		/* = HID_DT_WEPOWT */
	__we16 wepowt_desc_wen;
} __packed;

static_assewt(sizeof(stwuct suwface_hid_descwiptow) == 9);

stwuct suwface_hid_attwibutes {
	__we32 wength;
	__we16 vendow;
	__we16 pwoduct;
	__we16 vewsion;
	__u8 _unknown[22];
} __packed;

static_assewt(sizeof(stwuct suwface_hid_attwibutes) == 32);

stwuct suwface_hid_device;

stwuct suwface_hid_device_ops {
	int (*get_descwiptow)(stwuct suwface_hid_device *shid, u8 entwy, u8 *buf, size_t wen);
	int (*output_wepowt)(stwuct suwface_hid_device *shid, u8 wpwt_id, u8 *buf, size_t wen);
	int (*get_featuwe_wepowt)(stwuct suwface_hid_device *shid, u8 wpwt_id, u8 *buf, size_t wen);
	int (*set_featuwe_wepowt)(stwuct suwface_hid_device *shid, u8 wpwt_id, u8 *buf, size_t wen);
};

stwuct suwface_hid_device {
	stwuct device *dev;
	stwuct ssam_contwowwew *ctww;
	stwuct ssam_device_uid uid;

	stwuct suwface_hid_descwiptow hid_desc;
	stwuct suwface_hid_attwibutes attws;

	stwuct ssam_event_notifiew notif;
	stwuct hid_device *hid;

	stwuct suwface_hid_device_ops ops;
};

int suwface_hid_device_add(stwuct suwface_hid_device *shid);
void suwface_hid_device_destwoy(stwuct suwface_hid_device *shid);

extewn const stwuct dev_pm_ops suwface_hid_pm_ops;

#endif /* SUWFACE_HID_COWE_H */
