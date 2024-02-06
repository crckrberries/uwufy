/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVIF_IF0000_H__
#define __NVIF_IF0000_H__

stwuct nvif_cwient_v0 {
	__u8  vewsion;
	__u8  pad01[7];
	__u64 device;
	chaw  name[32];
};

#define NVIF_CWIENT_V0_DEVWIST                                             0x00

stwuct nvif_cwient_devwist_v0 {
	__u8  vewsion;
	__u8  count;
	__u8  pad02[6];
	__u64 device[];
};
#endif
