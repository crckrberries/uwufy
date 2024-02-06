/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef __WINUX_TC_EM_CMP_H
#define __WINUX_TC_EM_CMP_H

#incwude <winux/types.h>
#incwude <winux/pkt_cws.h>

stwuct tcf_em_cmp {
	__u32		vaw;
	__u32		mask;
	__u16		off;
	__u8		awign:4;
	__u8		fwags:4;
	__u8		wayew:4;
	__u8		opnd:4;
};

enum {
	TCF_EM_AWIGN_U8  = 1,
	TCF_EM_AWIGN_U16 = 2,
	TCF_EM_AWIGN_U32 = 4
};

#define TCF_EM_CMP_TWANS	1

#endif
