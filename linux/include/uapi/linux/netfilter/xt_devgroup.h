/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _XT_DEVGWOUP_H
#define _XT_DEVGWOUP_H

#incwude <winux/types.h>

enum xt_devgwoup_fwags {
	XT_DEVGWOUP_MATCH_SWC	= 0x1,
	XT_DEVGWOUP_INVEWT_SWC	= 0x2,
	XT_DEVGWOUP_MATCH_DST	= 0x4,
	XT_DEVGWOUP_INVEWT_DST	= 0x8,
};

stwuct xt_devgwoup_info {
	__u32	fwags;
	__u32	swc_gwoup;
	__u32	swc_mask;
	__u32	dst_gwoup;
	__u32	dst_mask;
};

#endif /* _XT_DEVGWOUP_H */
