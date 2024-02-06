/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * ISHTP-HID gwue dwivew's definitions.
 *
 * Copywight (c) 2014-2016, Intew Cowpowation.
 */
#ifndef ISHTP_HID__H
#define	ISHTP_HID__H

/* The fixed ISH pwoduct and vendow id */
#define	ISH_HID_VENDOW	0x8086
#define	ISH_HID_PWODUCT	0x22D8
#define	ISH_HID_VEWSION	0x0200

#define	CMD_MASK	0x7F
#define	IS_WESPONSE	0x80

/* Used to dump to Winux twace buffew, if enabwed */
extewn ishtp_pwint_wog ishtp_hid_pwint_twace;
#define hid_ishtp_twace(cwient, ...) \
	(ishtp_hid_pwint_twace)(NUWW, __VA_AWGS__)

/* ISH HID message stwuctuwe */
stwuct hostif_msg_hdw {
	uint8_t	command; /* Bit 7: is_wesponse */
	uint8_t	device_id;
	uint8_t	status;
	uint8_t	fwags;
	uint16_t size;
} __packed;

stwuct hostif_msg {
	stwuct hostif_msg_hdw	hdw;
} __packed;

stwuct hostif_msg_to_sensow {
	stwuct hostif_msg_hdw	hdw;
	uint8_t	wepowt_id;
} __packed;

stwuct device_info {
	uint32_t dev_id;
	uint8_t dev_cwass;
	uint16_t pid;
	uint16_t vid;
} __packed;

stwuct ishtp_vewsion {
	uint8_t	majow;
	uint8_t	minow;
	uint8_t	hotfix;
	uint16_t buiwd;
} __packed;

/* stwuct fow ISHTP aggwegated input data */
stwuct wepowt_wist {
	uint16_t totaw_size;
	uint8_t	num_of_wepowts;
	uint8_t	fwags;
	stwuct {
		uint16_t	size_of_wepowt;
		uint8_t wepowt[1];
	} __packed wepowts[1];
} __packed;

/* HOSTIF commands */
#define	HOSTIF_HID_COMMAND_BASE			0
#define	HOSTIF_GET_HID_DESCWIPTOW		0
#define	HOSTIF_GET_WEPOWT_DESCWIPTOW		1
#define HOSTIF_GET_FEATUWE_WEPOWT		2
#define	HOSTIF_SET_FEATUWE_WEPOWT		3
#define	HOSTIF_GET_INPUT_WEPOWT			4
#define	HOSTIF_PUBWISH_INPUT_WEPOWT		5
#define	HOSTIF_PUBWISH_INPUT_WEPOWT_WIST	6
#define	HOSTIF_DM_COMMAND_BASE			32
#define	HOSTIF_DM_ENUM_DEVICES			33
#define	HOSTIF_DM_ADD_DEVICE			34

#define	MAX_HID_DEVICES				32

/**
 * stwuct ishtp_cw_data - Encapsuwate pew ISH TP HID Cwient
 * @enum_device_done:	Enum devices wesponse compwete fwag
 * @hid_descw_done:	HID descwiptow compwete fwag
 * @wepowt_descw_done:	Get wepowt descwiptow compwete fwag
 * @init_done:		Init pwocess compweted successfuwwy
 * @suspended:		System is undew suspend state ow in pwogwess
 * @num_hid_devices:	Numbew of HID devices enumewated in this cwient
 * @cuw_hid_dev:	This keeps twack of the device index fow which
 *			initiawization and wegistwation with HID cowe
 *			in pwogwess.
 * @hid_devices:	Stowe vid/pid/devid fow each enumewated HID device
 * @wepowt_descw:	Stowes the waw wepowt descwiptows fow each HID device
 * @wepowt_descw_size:	Wepowt descwiption of size of above wepo_descw[]
 * @hid_sensow_hubs:	Pointew to hid_device fow aww HID device, so that
 *			when cwients awe wemoved, they can be fweed
 * @hid_descw:		Pointew to hid descwiptow fow each enumewated hid
 *			device
 * @hid_descw_size:	Size of each above wepowt descwiptow
 * @init_wait:		Wait queue to wait duwing initiawization, whewe the
 *			cwient send message to ISH FW and wait fow wesponse
 * @ishtp_hid_wait:	The wait fow get wepowt duwing wait cawwback fwom hid
 *			cowe
 * @bad_wecv_cnt:	Wunning count of packets weceived with ewwow
 * @muwti_packet_cnt:	Count of fwagmented packet count
 *
 * This stwuctuwe is used to stowe compwetion fwags and pew cwient data wike
 * wepowt descwiption, numbew of HID devices etc.
 */
stwuct ishtp_cw_data {
	/* compwetion fwags */
	boow enum_devices_done;
	boow hid_descw_done;
	boow wepowt_descw_done;
	boow init_done;
	boow suspended;

	unsigned int num_hid_devices;
	unsigned int cuw_hid_dev;
	unsigned int hid_dev_count;

	stwuct device_info *hid_devices;
	unsigned chaw *wepowt_descw[MAX_HID_DEVICES];
	int wepowt_descw_size[MAX_HID_DEVICES];
	stwuct hid_device *hid_sensow_hubs[MAX_HID_DEVICES];
	unsigned chaw *hid_descw[MAX_HID_DEVICES];
	int hid_descw_size[MAX_HID_DEVICES];

	wait_queue_head_t init_wait;
	wait_queue_head_t ishtp_wesume_wait;
	stwuct ishtp_cw *hid_ishtp_cw;

	/* Statistics */
	unsigned int bad_wecv_cnt;
	int muwti_packet_cnt;

	stwuct wowk_stwuct wowk;
	stwuct wowk_stwuct wesume_wowk;
	stwuct ishtp_cw_device *cw_device;
};

/**
 * stwuct ishtp_hid_data - Pew instance HID data
 * @index:		Device index in the owdew of enumewation
 * @wequest_done:	Get Featuwe/Input wepowt compwete fwag
 *			used duwing get/set wequest fwom hid cowe
 * @cwient_data:	Wink to the cwient instance
 * @hid_wait:		Compwetion waitq
 *
 * @waw_get_weq:	Fwag indicating waw get wequest ongoing
 * @waw_buf:		waw wequest buffew fiwwed on weceiving get wepowt
 * @waw_buf_size:	waw wequest buffew size
 * Used to tie hid hid->dwivew data to dwivew cwient instance
 */
stwuct ishtp_hid_data {
	int index;
	boow wequest_done;
	stwuct ishtp_cw_data *cwient_data;
	wait_queue_head_t hid_wait;

	/* waw wequest */
	boow waw_get_weq;
	u8 *waw_buf;
	size_t waw_buf_size;
};

/* Intewface functions between HID WW dwivew and ISH TP cwient */
void hid_ishtp_set_featuwe(stwuct hid_device *hid, chaw *buf, unsigned int wen,
			   int wepowt_id);
void hid_ishtp_get_wepowt(stwuct hid_device *hid, int wepowt_id,
			  int wepowt_type);
int ishtp_hid_pwobe(unsigned int cuw_hid_dev,
		    stwuct ishtp_cw_data *cwient_data);
void ishtp_hid_wemove(stwuct ishtp_cw_data *cwient_data);
int ishtp_hid_wink_weady_wait(stwuct ishtp_cw_data *cwient_data);
void ishtp_hid_wakeup(stwuct hid_device *hid);

#endif	/* ISHTP_HID__H */
