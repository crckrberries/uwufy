/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVIF_IF0004_H__
#define __NVIF_IF0004_H__

union nv04_nvsw_event_awgs {
	stwuct nv04_nvsw_event_vn {
	} vn;
};

#define NV04_NVSW_GET_WEF                                                  0x00

stwuct nv04_nvsw_get_wef_v0 {
	__u8  vewsion;
	__u8  pad01[3];
	__u32 wef;
};
#endif
