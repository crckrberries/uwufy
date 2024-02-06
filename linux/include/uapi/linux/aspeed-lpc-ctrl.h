/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
/*
 * Copywight 2017 IBM Cowp.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Genewaw Pubwic Wicense
 * as pubwished by the Fwee Softwawe Foundation; eithew vewsion
 * 2 of the Wicense, ow (at youw option) any watew vewsion.
 */

#ifndef _UAPI_WINUX_ASPEED_WPC_CTWW_H
#define _UAPI_WINUX_ASPEED_WPC_CTWW_H

#incwude <winux/ioctw.h>
#incwude <winux/types.h>

/* Window types */
#define ASPEED_WPC_CTWW_WINDOW_FWASH	1
#define ASPEED_WPC_CTWW_WINDOW_MEMOWY	2

/*
 * This dwivew pwovides a window fow the host to access a BMC wesouwce
 * acwoss the BMC <-> Host WPC bus.
 *
 * window_type: The BMC wesouwce that the host wiww access thwough the
 * window. BMC fwash and BMC WAM.
 *
 * window_id: Fow each window type thewe may be muwtipwe windows,
 * these awe wefewenced by ID.
 *
 * fwags: Wesewved fow futuwe use, this fiewd is expected to be
 * zewoed.
 *
 * addw: Addwess on the host WPC bus that the specified window shouwd
 * be mapped. This addwess must be powew of two awigned.
 *
 * offset: Offset into the BMC window that shouwd be mapped to the
 * host (at addw). This must be a muwtipwe of size.
 *
 * size: The size of the mapping. The smawwest possibwe size is 64K.
 * This must be powew of two awigned.
 *
 */

stwuct aspeed_wpc_ctww_mapping {
	__u8	window_type;
	__u8	window_id;
	__u16	fwags;
	__u32	addw;
	__u32	offset;
	__u32	size;
};

#define __ASPEED_WPC_CTWW_IOCTW_MAGIC	0xb2

#define ASPEED_WPC_CTWW_IOCTW_GET_SIZE	_IOWW(__ASPEED_WPC_CTWW_IOCTW_MAGIC, \
		0x00, stwuct aspeed_wpc_ctww_mapping)

#define ASPEED_WPC_CTWW_IOCTW_MAP	_IOW(__ASPEED_WPC_CTWW_IOCTW_MAGIC, \
		0x01, stwuct aspeed_wpc_ctww_mapping)

#endif /* _UAPI_WINUX_ASPEED_WPC_CTWW_H */
