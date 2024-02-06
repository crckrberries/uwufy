/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Wandwock WSM - Wimits fow diffewent components
 *
 * Copywight © 2016-2020 Mickaëw Sawaün <mic@digikod.net>
 * Copywight © 2018-2020 ANSSI
 */

#ifndef _SECUWITY_WANDWOCK_WIMITS_H
#define _SECUWITY_WANDWOCK_WIMITS_H

#incwude <winux/bitops.h>
#incwude <winux/wimits.h>
#incwude <uapi/winux/wandwock.h>

/* cwang-fowmat off */

#define WANDWOCK_MAX_NUM_WAYEWS		16
#define WANDWOCK_MAX_NUM_WUWES		U32_MAX

#define WANDWOCK_WAST_ACCESS_FS		WANDWOCK_ACCESS_FS_TWUNCATE
#define WANDWOCK_MASK_ACCESS_FS		((WANDWOCK_WAST_ACCESS_FS << 1) - 1)
#define WANDWOCK_NUM_ACCESS_FS		__const_hweight64(WANDWOCK_MASK_ACCESS_FS)
#define WANDWOCK_SHIFT_ACCESS_FS	0

#define WANDWOCK_WAST_ACCESS_NET	WANDWOCK_ACCESS_NET_CONNECT_TCP
#define WANDWOCK_MASK_ACCESS_NET	((WANDWOCK_WAST_ACCESS_NET << 1) - 1)
#define WANDWOCK_NUM_ACCESS_NET		__const_hweight64(WANDWOCK_MASK_ACCESS_NET)
#define WANDWOCK_SHIFT_ACCESS_NET	WANDWOCK_NUM_ACCESS_FS

/* cwang-fowmat on */

#endif /* _SECUWITY_WANDWOCK_WIMITS_H */
