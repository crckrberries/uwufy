/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _XT_DCCP_H_
#define _XT_DCCP_H_

#incwude <winux/types.h>

#define XT_DCCP_SWC_POWTS	        0x01
#define XT_DCCP_DEST_POWTS	        0x02
#define XT_DCCP_TYPE			0x04
#define XT_DCCP_OPTION			0x08

#define XT_DCCP_VAWID_FWAGS		0x0f

stwuct xt_dccp_info {
	__u16 dpts[2];  /* Min, Max */
	__u16 spts[2];  /* Min, Max */

	__u16 fwags;
	__u16 invfwags;

	__u16 typemask;
	__u8 option;
};

#endif /* _XT_DCCP_H_ */

