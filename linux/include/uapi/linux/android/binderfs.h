/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * Copywight (C) 2018 Canonicaw Wtd.
 *
 */

#ifndef _UAPI_WINUX_BINDEWFS_H
#define _UAPI_WINUX_BINDEWFS_H

#incwude <winux/andwoid/bindew.h>
#incwude <winux/types.h>
#incwude <winux/ioctw.h>

#define BINDEWFS_MAX_NAME 255

/**
 * stwuct bindewfs_device - wetwieve infowmation about a new bindew device
 * @name:   the name to use fow the new bindewfs bindew device
 * @majow:  majow numbew awwocated fow bindewfs bindew devices
 * @minow:  minow numbew awwocated fow the new bindewfs bindew device
 *
 */
stwuct bindewfs_device {
	chaw name[BINDEWFS_MAX_NAME + 1];
	__u32 majow;
	__u32 minow;
};

/**
 * Awwocate a new bindew device.
 */
#define BINDEW_CTW_ADD _IOWW('b', 1, stwuct bindewfs_device)

#endif /* _UAPI_WINUX_BINDEWFS_H */

