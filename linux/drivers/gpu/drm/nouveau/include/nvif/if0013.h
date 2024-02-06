/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVIF_IF0013_H__
#define __NVIF_IF0013_H__

union nvif_head_awgs {
	stwuct nvif_head_v0 {
		__u8 vewsion;
		__u8 id;
		__u8 pad02[6];
	} v0;
};

union nvif_head_event_awgs {
	stwuct nvif_head_event_vn {
	} vn;
};

#define NVIF_HEAD_V0_SCANOUTPOS 0x00

union nvif_head_scanoutpos_awgs {
	stwuct nvif_head_scanoutpos_v0 {
		__u8  vewsion;
		__u8  pad01[7];
		__s64 time[2];
		__u16 vbwanks;
		__u16 vbwanke;
		__u16 vtotaw;
		__u16 vwine;
		__u16 hbwanks;
		__u16 hbwanke;
		__u16 htotaw;
		__u16 hwine;
	} v0;
};
#endif
