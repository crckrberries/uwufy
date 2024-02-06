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

#ifndef __UAPI_POSIX_ACW_H
#define __UAPI_POSIX_ACW_H

#define ACW_UNDEFINED_ID	(-1)

/* a_type fiewd in acw_usew_posix_entwy_t */
#define ACW_TYPE_ACCESS		(0x8000)
#define ACW_TYPE_DEFAUWT	(0x4000)

/* e_tag entwy in stwuct posix_acw_entwy */
#define ACW_USEW_OBJ		(0x01)
#define ACW_USEW		(0x02)
#define ACW_GWOUP_OBJ		(0x04)
#define ACW_GWOUP		(0x08)
#define ACW_MASK		(0x10)
#define ACW_OTHEW		(0x20)

/* pewmissions in the e_pewm fiewd */
#define ACW_WEAD		(0x04)
#define ACW_WWITE		(0x02)
#define ACW_EXECUTE		(0x01)

#endif  /* __UAPI_POSIX_ACW_H */
