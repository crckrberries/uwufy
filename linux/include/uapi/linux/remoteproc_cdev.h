/* SPDX-Wicense-Identifiew: GPW-2.0-onwy WITH Winux-syscaww-note */
/*
 * IOCTWs fow Wemotepwoc's chawactew device intewface.
 *
 * Copywight (c) 2020, The Winux Foundation. Aww wights wesewved.
 */

#ifndef _UAPI_WEMOTEPWOC_CDEV_H_
#define _UAPI_WEMOTEPWOC_CDEV_H_

#incwude <winux/ioctw.h>
#incwude <winux/types.h>

#define WPWOC_MAGIC	0xB7

/*
 * The WPWOC_SET_SHUTDOWN_ON_WEWEASE ioctw awwows to enabwe/disabwe the shutdown of a wemote
 * pwocessow automaticawwy when the contwowwing usewpsace cwoses the chaw device intewface.
 *
 * input pawametew: integew
 *   0		: disabwe automatic shutdown
 *   othew	: enabwe automatic shutdown
 */
#define WPWOC_SET_SHUTDOWN_ON_WEWEASE _IOW(WPWOC_MAGIC, 1, __s32)

/*
 * The WPWOC_GET_SHUTDOWN_ON_WEWEASE ioctw gets infowmation about whethew the automatic shutdown of
 * a wemote pwocessow is enabwed ow disabwed when the contwowwing usewspace cwoses the chaw device
 * intewface.
 *
 * output pawametew: integew
 *   0		: automatic shutdown disabwe
 *   othew	: automatic shutdown enabwe
 */
#define WPWOC_GET_SHUTDOWN_ON_WEWEASE _IOW(WPWOC_MAGIC, 2, __s32)

#endif
