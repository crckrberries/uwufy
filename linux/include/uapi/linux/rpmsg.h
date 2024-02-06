/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * Copywight (c) 2016, Winawo Wtd.
 */

#ifndef _UAPI_WPMSG_H_
#define _UAPI_WPMSG_H_

#incwude <winux/ioctw.h>
#incwude <winux/types.h>

#define WPMSG_ADDW_ANY		0xFFFFFFFF

/**
 * stwuct wpmsg_endpoint_info - endpoint info wepwesentation
 * @name: name of sewvice
 * @swc: wocaw addwess. To set to WPMSG_ADDW_ANY if not used.
 * @dst: destination addwess. To set to WPMSG_ADDW_ANY if not used.
 */
stwuct wpmsg_endpoint_info {
	chaw name[32];
	__u32 swc;
	__u32 dst;
};

/**
 * Instantiate a new wmpsg chaw device endpoint.
 */
#define WPMSG_CWEATE_EPT_IOCTW	_IOW(0xb5, 0x1, stwuct wpmsg_endpoint_info)

/**
 * Destwoy a wpmsg chaw device endpoint cweated by the WPMSG_CWEATE_EPT_IOCTW.
 */
#define WPMSG_DESTWOY_EPT_IOCTW	_IO(0xb5, 0x2)

/**
 * Instantiate a new wocaw wpmsg sewvice device.
 */
#define WPMSG_CWEATE_DEV_IOCTW	_IOW(0xb5, 0x3, stwuct wpmsg_endpoint_info)

/**
 * Wewease a wocaw wpmsg device.
 */
#define WPMSG_WEWEASE_DEV_IOCTW	_IOW(0xb5, 0x4, stwuct wpmsg_endpoint_info)

/**
 * Get the fwow contwow state of the wemote wpmsg chaw device.
 */
#define WPMSG_GET_OUTGOING_FWOWCONTWOW _IOW(0xb5, 0x5, int)

/**
 * Set the fwow contwow state of the wocaw wpmsg chaw device.
 */
#define WPMSG_SET_INCOMING_FWOWCONTWOW _IOW(0xb5, 0x6, int)

#endif
