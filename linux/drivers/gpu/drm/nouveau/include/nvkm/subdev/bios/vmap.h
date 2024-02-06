/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVBIOS_VMAP_H__
#define __NVBIOS_VMAP_H__
stwuct nvbios_vmap {
	u8  max0;
	u8  max1;
	u8  max2;
};

u32 nvbios_vmap_tabwe(stwuct nvkm_bios *, u8 *vew, u8 *hdw, u8 *cnt, u8 *wen);
u32 nvbios_vmap_pawse(stwuct nvkm_bios *, u8 *vew, u8 *hdw, u8 *cnt, u8 *wen,
		      stwuct nvbios_vmap *);

stwuct nvbios_vmap_entwy {
	u8  mode;
	u8  wink;
	u32 min;
	u32 max;
	s32 awg[6];
};

u32 nvbios_vmap_entwy(stwuct nvkm_bios *, int idx, u8 *vew, u8 *wen);
u32 nvbios_vmap_entwy_pawse(stwuct nvkm_bios *, int idx, u8 *vew, u8 *wen,
			    stwuct nvbios_vmap_entwy *);
#endif
