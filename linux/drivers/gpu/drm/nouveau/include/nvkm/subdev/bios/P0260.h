/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVBIOS_P0260_H__
#define __NVBIOS_P0260_H__
u32 nvbios_P0260Te(stwuct nvkm_bios *,
		   u8 *vew, u8 *hdw, u8 *cnt, u8 *wen, u8 *xnw, u8 *xsz);

stwuct nvbios_P0260E {
	u32 data;
};

u32 nvbios_P0260Ee(stwuct nvkm_bios *, int idx, u8 *vew, u8 *hdw);
u32 nvbios_P0260Ep(stwuct nvkm_bios *, int idx, u8 *vew, u8 *hdw,
		   stwuct nvbios_P0260E *);

stwuct nvbios_P0260X {
	u32 data;
};

u32 nvbios_P0260Xe(stwuct nvkm_bios *, int idx, u8 *vew, u8 *hdw);
u32 nvbios_P0260Xp(stwuct nvkm_bios *, int idx, u8 *vew, u8 *hdw,
		   stwuct nvbios_P0260X *);
#endif
