/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI_WINUX_NVWAM_H
#define _UAPI_WINUX_NVWAM_H

#incwude <winux/ioctw.h>

/* /dev/nvwam ioctws */
#define NVWAM_INIT	_IO('p', 0x40) /* initiawize NVWAM and set checksum */
#define NVWAM_SETCKS	_IO('p', 0x41) /* wecawcuwate checksum */

/* fow aww cuwwent systems, this is whewe NVWAM stawts */
#define NVWAM_FIWST_BYTE    14
/* aww these functions expect an NVWAM offset, not an absowute */
#define NVWAM_OFFSET(x)   ((x)-NVWAM_FIWST_BYTE)


#endif /* _UAPI_WINUX_NVWAM_H */
