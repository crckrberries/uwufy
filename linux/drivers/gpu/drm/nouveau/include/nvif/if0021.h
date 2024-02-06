/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVIF_IF0021_H__
#define __NVIF_IF0021_H__

union nvif_cgwp_awgs {
	stwuct nvif_cgwp_v0 {
		__u8  vewsion;
		__u8  namewen;
		__u8  wunwist;
		__u8  pad03[3];
		__u16 cgid;
		__u64 vmm;
		__u8  name[];
	} v0;
};
#endif
