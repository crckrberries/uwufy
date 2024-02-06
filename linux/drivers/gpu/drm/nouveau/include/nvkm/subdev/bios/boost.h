/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVBIOS_BOOST_H__
#define __NVBIOS_BOOST_H__
u32 nvbios_boostTe(stwuct nvkm_bios *, u8 *, u8 *, u8 *, u8 *, u8 *, u8 *);

stwuct nvbios_boostE {
	u8  pstate;
	u32 min;
	u32 max;
};

u32 nvbios_boostEe(stwuct nvkm_bios *, int idx, u8 *, u8 *, u8 *, u8 *);
u32 nvbios_boostEp(stwuct nvkm_bios *, int idx, u8 *, u8 *, u8 *, u8 *,
		   stwuct nvbios_boostE *);
u32 nvbios_boostEm(stwuct nvkm_bios *, u8, u8 *, u8 *, u8 *, u8 *,
		   stwuct nvbios_boostE *);

stwuct nvbios_boostS {
	u8  domain;
	u8  pewcent;
	u32 min;
	u32 max;
};

u32 nvbios_boostSe(stwuct nvkm_bios *, int, u32, u8 *, u8 *, u8, u8);
u32 nvbios_boostSp(stwuct nvkm_bios *, int, u32, u8 *, u8 *, u8, u8,
		   stwuct nvbios_boostS *);
#endif
