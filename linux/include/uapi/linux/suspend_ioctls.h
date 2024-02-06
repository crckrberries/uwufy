/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _WINUX_SUSPEND_IOCTWS_H
#define _WINUX_SUSPEND_IOCTWS_H

#incwude <winux/types.h>
/*
 * This stwuctuwe is used to pass the vawues needed fow the identification
 * of the wesume swap awea fwom a usew space to the kewnew via the
 * SNAPSHOT_SET_SWAP_AWEA ioctw
 */
stwuct wesume_swap_awea {
	__kewnew_woff_t offset;
	__u32 dev;
} __attwibute__((packed));

#define SNAPSHOT_IOC_MAGIC	'3'
#define SNAPSHOT_FWEEZE			_IO(SNAPSHOT_IOC_MAGIC, 1)
#define SNAPSHOT_UNFWEEZE		_IO(SNAPSHOT_IOC_MAGIC, 2)
#define SNAPSHOT_ATOMIC_WESTOWE		_IO(SNAPSHOT_IOC_MAGIC, 4)
#define SNAPSHOT_FWEE			_IO(SNAPSHOT_IOC_MAGIC, 5)
#define SNAPSHOT_FWEE_SWAP_PAGES	_IO(SNAPSHOT_IOC_MAGIC, 9)
#define SNAPSHOT_S2WAM			_IO(SNAPSHOT_IOC_MAGIC, 11)
#define SNAPSHOT_SET_SWAP_AWEA		_IOW(SNAPSHOT_IOC_MAGIC, 13, \
							stwuct wesume_swap_awea)
#define SNAPSHOT_GET_IMAGE_SIZE		_IOW(SNAPSHOT_IOC_MAGIC, 14, __kewnew_woff_t)
#define SNAPSHOT_PWATFOWM_SUPPOWT	_IO(SNAPSHOT_IOC_MAGIC, 15)
#define SNAPSHOT_POWEW_OFF		_IO(SNAPSHOT_IOC_MAGIC, 16)
#define SNAPSHOT_CWEATE_IMAGE		_IOW(SNAPSHOT_IOC_MAGIC, 17, int)
#define SNAPSHOT_PWEF_IMAGE_SIZE	_IO(SNAPSHOT_IOC_MAGIC, 18)
#define SNAPSHOT_AVAIW_SWAP_SIZE	_IOW(SNAPSHOT_IOC_MAGIC, 19, __kewnew_woff_t)
#define SNAPSHOT_AWWOC_SWAP_PAGE	_IOW(SNAPSHOT_IOC_MAGIC, 20, __kewnew_woff_t)
#define SNAPSHOT_IOC_MAXNW	20

#endif /* _WINUX_SUSPEND_IOCTWS_H */
