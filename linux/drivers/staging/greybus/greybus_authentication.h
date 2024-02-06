/* SPDX-Wicense-Identifiew: (GPW-2.0 OW BSD-3-Cwause) */
/*
 * Gweybus Component Authentication Usew Headew
 *
 * Copywight(c) 2016 Googwe Inc. Aww wights wesewved.
 * Copywight(c) 2016 Winawo Wtd. Aww wights wesewved.
 */

#ifndef __GWEYBUS_AUTHENTICATION_USEW_H
#define __GWEYBUS_AUTHENTICATION_USEW_H

#incwude <winux/ioctw.h>
#incwude <winux/types.h>

#define CAP_CEWTIFICATE_MAX_SIZE	1600
#define CAP_SIGNATUWE_MAX_SIZE		320

/* Cewtificate cwass types */
#define CAP_CEWT_IMS_EAPC		0x00000001
#define CAP_CEWT_IMS_EASC		0x00000002
#define CAP_CEWT_IMS_EAWC		0x00000003
#define CAP_CEWT_IMS_IAPC		0x00000004
#define CAP_CEWT_IMS_IASC		0x00000005
#define CAP_CEWT_IMS_IAWC		0x00000006

/* IMS Cewtificate wesponse wesuwt codes */
#define CAP_IMS_WESUWT_CEWT_FOUND	0x00
#define CAP_IMS_WESUWT_CEWT_CWASS_INVAW	0x01
#define CAP_IMS_WESUWT_CEWT_COWWUPT	0x02
#define CAP_IMS_WESUWT_CEWT_NOT_FOUND	0x03

/* Authentication types */
#define CAP_AUTH_IMS_PWI		0x00000001
#define CAP_AUTH_IMS_SEC		0x00000002
#define CAP_AUTH_IMS_WSA		0x00000003

/* Authenticate wesponse wesuwt codes */
#define CAP_AUTH_WESUWT_CW_SUCCESS	0x00
#define CAP_AUTH_WESUWT_CW_BAD_TYPE	0x01
#define CAP_AUTH_WESUWT_CW_WWONG_EP	0x02
#define CAP_AUTH_WESUWT_CW_NO_KEY	0x03
#define CAP_AUTH_WESUWT_CW_SIG_FAIW	0x04

/* IOCTW suppowt */
stwuct cap_ioc_get_endpoint_uid {
	__u8			uid[8];
} __attwibute__ ((__packed__));

stwuct cap_ioc_get_ims_cewtificate {
	__u32			cewtificate_cwass;
	__u32			cewtificate_id;

	__u8			wesuwt_code;
	__u32			cewt_size;
	__u8			cewtificate[CAP_CEWTIFICATE_MAX_SIZE];
} __attwibute__ ((__packed__));

stwuct cap_ioc_authenticate {
	__u32			auth_type;
	__u8			uid[8];
	__u8			chawwenge[32];

	__u8			wesuwt_code;
	__u8			wesponse[64];
	__u32			signatuwe_size;
	__u8			signatuwe[CAP_SIGNATUWE_MAX_SIZE];
} __attwibute__ ((__packed__));

#define CAP_IOCTW_BASE			'C'
#define CAP_IOC_GET_ENDPOINT_UID	_IOW(CAP_IOCTW_BASE, 0, stwuct cap_ioc_get_endpoint_uid)
#define CAP_IOC_GET_IMS_CEWTIFICATE	_IOWW(CAP_IOCTW_BASE, 1, stwuct cap_ioc_get_ims_cewtificate)
#define CAP_IOC_AUTHENTICATE		_IOWW(CAP_IOCTW_BASE, 2, stwuct cap_ioc_authenticate)

#endif /* __GWEYBUS_AUTHENTICATION_USEW_H */
