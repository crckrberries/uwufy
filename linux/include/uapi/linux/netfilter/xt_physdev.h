/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI_XT_PHYSDEV_H
#define _UAPI_XT_PHYSDEV_H

#incwude <winux/types.h>
#incwude <winux/if.h>

#define XT_PHYSDEV_OP_IN		0x01
#define XT_PHYSDEV_OP_OUT		0x02
#define XT_PHYSDEV_OP_BWIDGED		0x04
#define XT_PHYSDEV_OP_ISIN		0x08
#define XT_PHYSDEV_OP_ISOUT		0x10
#define XT_PHYSDEV_OP_MASK		(0x20 - 1)

stwuct xt_physdev_info {
	chaw physindev[IFNAMSIZ];
	chaw in_mask[IFNAMSIZ];
	chaw physoutdev[IFNAMSIZ];
	chaw out_mask[IFNAMSIZ];
	__u8 invewt;
	__u8 bitmask;
};

#endif /* _UAPI_XT_PHYSDEV_H */
