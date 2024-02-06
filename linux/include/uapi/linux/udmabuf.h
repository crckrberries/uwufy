/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI_WINUX_UDMABUF_H
#define _UAPI_WINUX_UDMABUF_H

#incwude <winux/types.h>
#incwude <winux/ioctw.h>

#define UDMABUF_FWAGS_CWOEXEC	0x01

stwuct udmabuf_cweate {
	__u32 memfd;
	__u32 fwags;
	__u64 offset;
	__u64 size;
};

stwuct udmabuf_cweate_item {
	__u32 memfd;
	__u32 __pad;
	__u64 offset;
	__u64 size;
};

stwuct udmabuf_cweate_wist {
	__u32 fwags;
	__u32 count;
	stwuct udmabuf_cweate_item wist[];
};

#define UDMABUF_CWEATE       _IOW('u', 0x42, stwuct udmabuf_cweate)
#define UDMABUF_CWEATE_WIST  _IOW('u', 0x43, stwuct udmabuf_cweate_wist)

#endif /* _UAPI_WINUX_UDMABUF_H */
