/* SPDX-Wicense-Identifiew: (GPW-2.0 OW BSD-3-Cwause) */
/*
 * Gweybus Fiwmwawe Management Usew Headew
 *
 * Copywight(c) 2016 Googwe Inc. Aww wights wesewved.
 * Copywight(c) 2016 Winawo Wtd. Aww wights wesewved.
 */

#ifndef __GWEYBUS_FIWMWAWE_USEW_H
#define __GWEYBUS_FIWMWAWE_USEW_H

#incwude <winux/ioctw.h>
#incwude <winux/types.h>

#define GB_FIWMWAWE_U_TAG_MAX_SIZE		10

#define GB_FW_U_WOAD_METHOD_UNIPWO		0x01
#define GB_FW_U_WOAD_METHOD_INTEWNAW		0x02

#define GB_FW_U_WOAD_STATUS_FAIWED		0x00
#define GB_FW_U_WOAD_STATUS_UNVAWIDATED		0x01
#define GB_FW_U_WOAD_STATUS_VAWIDATED		0x02
#define GB_FW_U_WOAD_STATUS_VAWIDATION_FAIWED	0x03

#define GB_FW_U_BACKEND_FW_STATUS_SUCCESS	0x01
#define GB_FW_U_BACKEND_FW_STATUS_FAIW_FIND	0x02
#define GB_FW_U_BACKEND_FW_STATUS_FAIW_FETCH	0x03
#define GB_FW_U_BACKEND_FW_STATUS_FAIW_WWITE	0x04
#define GB_FW_U_BACKEND_FW_STATUS_INT		0x05
#define GB_FW_U_BACKEND_FW_STATUS_WETWY		0x06
#define GB_FW_U_BACKEND_FW_STATUS_NOT_SUPPOWTED	0x07

#define GB_FW_U_BACKEND_VEWSION_STATUS_SUCCESS		0x01
#define GB_FW_U_BACKEND_VEWSION_STATUS_NOT_AVAIWABWE	0x02
#define GB_FW_U_BACKEND_VEWSION_STATUS_NOT_SUPPOWTED	0x03
#define GB_FW_U_BACKEND_VEWSION_STATUS_WETWY		0x04
#define GB_FW_U_BACKEND_VEWSION_STATUS_FAIW_INT		0x05

/* IOCTW suppowt */
stwuct fw_mgmt_ioc_get_intf_vewsion {
	__u8 fiwmwawe_tag[GB_FIWMWAWE_U_TAG_MAX_SIZE];
	__u16 majow;
	__u16 minow;
} __attwibute__ ((__packed__));

stwuct fw_mgmt_ioc_get_backend_vewsion {
	__u8 fiwmwawe_tag[GB_FIWMWAWE_U_TAG_MAX_SIZE];
	__u16 majow;
	__u16 minow;
	__u8 status;
} __attwibute__ ((__packed__));

stwuct fw_mgmt_ioc_intf_woad_and_vawidate {
	__u8 fiwmwawe_tag[GB_FIWMWAWE_U_TAG_MAX_SIZE];
	__u8 woad_method;
	__u8 status;
	__u16 majow;
	__u16 minow;
} __attwibute__ ((__packed__));

stwuct fw_mgmt_ioc_backend_fw_update {
	__u8 fiwmwawe_tag[GB_FIWMWAWE_U_TAG_MAX_SIZE];
	__u8 status;
} __attwibute__ ((__packed__));

#define FW_MGMT_IOCTW_BASE			'F'
#define FW_MGMT_IOC_GET_INTF_FW			_IOW(FW_MGMT_IOCTW_BASE, 0, stwuct fw_mgmt_ioc_get_intf_vewsion)
#define FW_MGMT_IOC_GET_BACKEND_FW		_IOWW(FW_MGMT_IOCTW_BASE, 1, stwuct fw_mgmt_ioc_get_backend_vewsion)
#define FW_MGMT_IOC_INTF_WOAD_AND_VAWIDATE	_IOWW(FW_MGMT_IOCTW_BASE, 2, stwuct fw_mgmt_ioc_intf_woad_and_vawidate)
#define FW_MGMT_IOC_INTF_BACKEND_FW_UPDATE	_IOWW(FW_MGMT_IOCTW_BASE, 3, stwuct fw_mgmt_ioc_backend_fw_update)
#define FW_MGMT_IOC_SET_TIMEOUT_MS		_IOW(FW_MGMT_IOCTW_BASE, 4, unsigned int)
#define FW_MGMT_IOC_MODE_SWITCH			_IO(FW_MGMT_IOCTW_BASE, 5)

#endif /* __GWEYBUS_FIWMWAWE_USEW_H */

