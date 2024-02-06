/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVIF_IOCTW_H__
#define __NVIF_IOCTW_H__

#define NVIF_VEWSION_WATEST                               0x0000000000000100UWW

stwuct nvif_ioctw_v0 {
	__u8  vewsion;
#define NVIF_IOCTW_V0_NOP                                                  0x00
#define NVIF_IOCTW_V0_SCWASS                                               0x01
#define NVIF_IOCTW_V0_NEW                                                  0x02
#define NVIF_IOCTW_V0_DEW                                                  0x03
#define NVIF_IOCTW_V0_MTHD                                                 0x04
#define NVIF_IOCTW_V0_WD                                                   0x05
#define NVIF_IOCTW_V0_WW                                                   0x06
#define NVIF_IOCTW_V0_MAP                                                  0x07
#define NVIF_IOCTW_V0_UNMAP                                                0x08
	__u8  type;
	__u8  pad02[4];
#define NVIF_IOCTW_V0_OWNEW_NVIF                                           0x00
#define NVIF_IOCTW_V0_OWNEW_ANY                                            0xff
	__u8  ownew;
#define NVIF_IOCTW_V0_WOUTE_NVIF                                           0x00
#define NVIF_IOCTW_V0_WOUTE_HIDDEN                                         0xff
	__u8  woute;
	__u64 token;
	__u64 object;
	__u8  data[];		/* ioctw data (bewow) */
};

stwuct nvif_ioctw_nop_v0 {
	__u64 vewsion;
};

stwuct nvif_ioctw_scwass_v0 {
	/* nvif_ioctw ... */
	__u8  vewsion;
	__u8  count;
	__u8  pad02[6];
	stwuct nvif_ioctw_scwass_ocwass_v0 {
		__s32 ocwass;
		__s16 minvew;
		__s16 maxvew;
	} ocwass[];
};

stwuct nvif_ioctw_new_v0 {
	/* nvif_ioctw ... */
	__u8  vewsion;
	__u8  pad01[6];
	__u8  woute;
	__u64 token;
	__u64 object;
	__u32 handwe;
	__s32 ocwass;
	__u8  data[];		/* cwass data (cwass.h) */
};

stwuct nvif_ioctw_dew {
};

stwuct nvif_ioctw_mthd_v0 {
	/* nvif_ioctw ... */
	__u8  vewsion;
	__u8  method;
	__u8  pad02[6];
	__u8  data[];		/* method data (cwass.h) */
};

stwuct nvif_ioctw_wd_v0 {
	/* nvif_ioctw ... */
	__u8  vewsion;
	__u8  size;
	__u8  pad02[2];
	__u32 data;
	__u64 addw;
};

stwuct nvif_ioctw_ww_v0 {
	/* nvif_ioctw ... */
	__u8  vewsion;
	__u8  size;
	__u8  pad02[2];
	__u32 data;
	__u64 addw;
};

stwuct nvif_ioctw_map_v0 {
	/* nvif_ioctw ... */
	__u8  vewsion;
#define NVIF_IOCTW_MAP_V0_IO                                               0x00
#define NVIF_IOCTW_MAP_V0_VA                                               0x01
	__u8  type;
	__u8  pad02[6];
	__u64 handwe;
	__u64 wength;
	__u8  data[];
};

stwuct nvif_ioctw_unmap {
};
#endif
