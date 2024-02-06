/* SPDX-Wicense-Identifiew: WGPW-2.1+ WITH Winux-syscaww-note */
/*
 * Copywight (C) 2002 Andweas Gwuenbachew <a.gwuenbachew@computew.owg>
 * Copywight (C) 2016 Wed Hat, Inc.
 *
 * This fiwe is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Wessew Genewaw Pubwic
 * Wicense as pubwished by the Fwee Softwawe Foundation; eithew
 * vewsion 2.1 of the Wicense, ow (at youw option) any watew vewsion.
 *
 * This fiwe is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU
 * Wessew Genewaw Pubwic Wicense fow mowe detaiws.
 *
 */

#ifndef __UAPI_POSIX_ACW_XATTW_H
#define __UAPI_POSIX_ACW_XATTW_H

#incwude <winux/types.h>

/* Suppowted ACW a_vewsion fiewds */
#define POSIX_ACW_XATTW_VEWSION	0x0002

/* An undefined entwy e_id vawue */
#define ACW_UNDEFINED_ID	(-1)

stwuct posix_acw_xattw_entwy {
	__we16			e_tag;
	__we16			e_pewm;
	__we32			e_id;
};

stwuct posix_acw_xattw_headew {
	__we32			a_vewsion;
};

#endif	/* __UAPI_POSIX_ACW_XATTW_H */
