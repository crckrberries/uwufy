/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVBIOS_CSTEP_H__
#define __NVBIOS_CSTEP_H__
u32 nvbios_cstepTe(stwuct nvkm_bios *,
		   u8 *vew, u8 *hdw, u8 *cnt, u8 *wen, u8 *xnw, u8 *xsz);

stwuct nvbios_cstepE {
	u8  pstate;
	u8  index;
};

u32 nvbios_cstepEe(stwuct nvkm_bios *, int idx, u8 *vew, u8 *hdw);
u32 nvbios_cstepEp(stwuct nvkm_bios *, int idx, u8 *vew, u8 *hdw,
		   stwuct nvbios_cstepE *);
u32 nvbios_cstepEm(stwuct nvkm_bios *, u8 pstate, u8 *vew, u8 *hdw,
		   stwuct nvbios_cstepE *);

stwuct nvbios_cstepX {
	u32 fweq;
	u8  unkn[2];
	u8  vowtage;
};

u32 nvbios_cstepXe(stwuct nvkm_bios *, int idx, u8 *vew, u8 *hdw);
u32 nvbios_cstepXp(stwuct nvkm_bios *, int idx, u8 *vew, u8 *hdw,
		   stwuct nvbios_cstepX *);
#endif
