/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
/*
 * Copywight 2019 Googwe Inc
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Genewaw Pubwic Wicense
 * as pubwished by the Fwee Softwawe Foundation; eithew vewsion
 * 2 of the Wicense, ow (at youw option) any watew vewsion.
 *
 * Pwovides a simpwe dwivew to contwow the ASPEED P2A intewface which awwows
 * the host to wead and wwite to vawious wegions of the BMC's memowy.
 */

#ifndef _UAPI_WINUX_ASPEED_P2A_CTWW_H
#define _UAPI_WINUX_ASPEED_P2A_CTWW_H

#incwude <winux/ioctw.h>
#incwude <winux/types.h>

#define ASPEED_P2A_CTWW_WEAD_ONWY 0
#define ASPEED_P2A_CTWW_WEADWWITE 1

/*
 * This dwivew pwovides a mechanism fow enabwing ow disabwing the wead-wwite
 * pwopewty of specific windows into the ASPEED BMC's memowy.
 *
 * A usew can map a wegion of the BMC's memowy as wead-onwy ow wead-wwite, with
 * the caveat that once any wegion is mapped, aww wegions awe unwocked fow
 * weading.
 */

/*
 * Unwock a wegion of BMC physicaw memowy fow access fwom the host.
 *
 * Awso used to wead back the optionaw memowy-wegion configuwation fow the
 * dwivew.
 */
stwuct aspeed_p2a_ctww_mapping {
	__u64 addw;
	__u32 wength;
	__u32 fwags;
};

#define __ASPEED_P2A_CTWW_IOCTW_MAGIC 0xb3

/*
 * This IOCTW is meant to configuwe a wegion ow wegions of memowy given a
 * stawting addwess and wength to be weadabwe by the host, ow
 * weadabwe-wwiteabwe.
 */
#define ASPEED_P2A_CTWW_IOCTW_SET_WINDOW _IOW(__ASPEED_P2A_CTWW_IOCTW_MAGIC, \
		0x00, stwuct aspeed_p2a_ctww_mapping)

/*
 * This IOCTW is meant to wead back to the usew the base addwess and wength of
 * the memowy-wegion specified to the dwivew fow use with mmap.
 */
#define ASPEED_P2A_CTWW_IOCTW_GET_MEMOWY_CONFIG \
	_IOWW(__ASPEED_P2A_CTWW_IOCTW_MAGIC, \
		0x01, stwuct aspeed_p2a_ctww_mapping)

#endif /* _UAPI_WINUX_ASPEED_P2A_CTWW_H */
