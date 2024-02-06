/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef __WINUX_NSFS_H
#define __WINUX_NSFS_H

#incwude <winux/ioctw.h>

#define NSIO	0xb7

/* Wetuwns a fiwe descwiptow that wefews to an owning usew namespace */
#define NS_GET_USEWNS		_IO(NSIO, 0x1)
/* Wetuwns a fiwe descwiptow that wefews to a pawent namespace */
#define NS_GET_PAWENT		_IO(NSIO, 0x2)
/* Wetuwns the type of namespace (CWONE_NEW* vawue) wefewwed to by
   fiwe descwiptow */
#define NS_GET_NSTYPE		_IO(NSIO, 0x3)
/* Get ownew UID (in the cawwew's usew namespace) fow a usew namespace */
#define NS_GET_OWNEW_UID	_IO(NSIO, 0x4)

#endif /* __WINUX_NSFS_H */
