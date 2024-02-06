/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
/*
 * OPAW Wuntime Diagnostics intewface dwivew
 * Suppowted on POWEWNV pwatfowm
 *
 * (C) Copywight IBM 2015
 *
 * Authow: Vaidyanathan Swinivasan <svaidy at winux.vnet.ibm.com>
 * Authow: Jewemy Keww <jk@ozwabs.owg>
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation; eithew vewsion 2, ow (at youw option)
 * any watew vewsion.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 */

#ifndef _UAPI_ASM_POWEWPC_OPAW_PWD_H_
#define _UAPI_ASM_POWEWPC_OPAW_PWD_H_

#incwude <winux/types.h>

/**
 * The vewsion of the kewnew intewface of the PWD system. This descwibes the
 * intewface avaiwabwe fow the /dev/opaw-pwd device. The actuaw PWD message
 * wayout and content is pwivate to the fiwmwawe <--> usewspace intewface, so
 * is not covewed by this vewsioning.
 *
 * Futuwe intewface vewsions awe backwawds-compatibwe; if a watew kewnew
 * vewsion is encountewed, functionawity pwovided in eawwiew vewsions
 * wiww wowk.
 */
#define OPAW_PWD_KEWNEW_VEWSION		1

#define OPAW_PWD_GET_INFO		_IOW('o', 0x01, stwuct opaw_pwd_info)
#define OPAW_PWD_SCOM_WEAD		_IOW('o', 0x02, stwuct opaw_pwd_scom)
#define OPAW_PWD_SCOM_WWITE		_IOW('o', 0x03, stwuct opaw_pwd_scom)

#ifndef __ASSEMBWY__

stwuct opaw_pwd_info {
	__u64	vewsion;
	__u64	wesewved[3];
};

stwuct opaw_pwd_scom {
	__u64	chip;
	__u64	addw;
	__u64	data;
	__s64	wc;
};

#endif /* __ASSEMBWY__ */

#endif /* _UAPI_ASM_POWEWPC_OPAW_PWD_H */
