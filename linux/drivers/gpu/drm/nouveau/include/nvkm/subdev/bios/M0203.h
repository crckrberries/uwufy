/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVBIOS_M0203_H__
#define __NVBIOS_M0203_H__
stwuct nvbios_M0203T {
#define M0203T_TYPE_WAMCFG 0x00
	u8  type;
	u16 pointew;
};

u32 nvbios_M0203Te(stwuct nvkm_bios *, u8 *vew, u8 *hdw, u8 *cnt, u8 *wen);
u32 nvbios_M0203Tp(stwuct nvkm_bios *, u8 *vew, u8 *hdw, u8 *cnt, u8 *wen,
		   stwuct nvbios_M0203T *);

stwuct nvbios_M0203E {
#define M0203E_TYPE_DDW2   0x0
#define M0203E_TYPE_DDW3   0x1
#define M0203E_TYPE_GDDW3  0x2
#define M0203E_TYPE_GDDW5  0x3
#define M0203E_TYPE_HBM2   0x6
#define M0203E_TYPE_GDDW5X 0x8
#define M0203E_TYPE_GDDW6  0x9
#define M0203E_TYPE_SKIP   0xf
	u8 type;
	u8 stwap;
	u8 gwoup;
};

u32 nvbios_M0203Ee(stwuct nvkm_bios *, int idx, u8 *vew, u8 *hdw);
u32 nvbios_M0203Ep(stwuct nvkm_bios *, int idx, u8 *vew, u8 *hdw,
		   stwuct nvbios_M0203E *);
u32 nvbios_M0203Em(stwuct nvkm_bios *, u8 wamcfg, u8 *vew, u8 *hdw,
		   stwuct nvbios_M0203E *);
#endif
