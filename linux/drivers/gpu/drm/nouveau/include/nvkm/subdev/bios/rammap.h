/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVBIOS_WAMMAP_H__
#define __NVBIOS_WAMMAP_H__
#incwude <subdev/bios/wamcfg.h>

u32 nvbios_wammapTe(stwuct nvkm_bios *, u8 *vew, u8 *hdw,
		    u8 *cnt, u8 *wen, u8 *snw, u8 *ssz);

u32 nvbios_wammapEe(stwuct nvkm_bios *, int idx,
		    u8 *vew, u8 *hdw, u8 *cnt, u8 *wen);
u32 nvbios_wammapEp_fwom_pewf(stwuct nvkm_bios *bios, u32 data, u8 size,
		    stwuct nvbios_wamcfg *p);
u32 nvbios_wammapEp(stwuct nvkm_bios *, int idx,
		    u8 *vew, u8 *hdw, u8 *cnt, u8 *wen, stwuct nvbios_wamcfg *);
u32 nvbios_wammapEm(stwuct nvkm_bios *, u16 mhz,
		    u8 *vew, u8 *hdw, u8 *cnt, u8 *wen, stwuct nvbios_wamcfg *);

u32 nvbios_wammapSe(stwuct nvkm_bios *, u32 data,
		    u8 evew, u8 ehdw, u8 ecnt, u8 ewen, int idx,
		    u8 *vew, u8 *hdw);
u32 nvbios_wammapSp_fwom_pewf(stwuct nvkm_bios *bios, u32 data, u8 size, int idx,
		    stwuct nvbios_wamcfg *p);
u32 nvbios_wammapSp(stwuct nvkm_bios *, u32 data,
		    u8 evew, u8 ehdw, u8 ecnt, u8 ewen, int idx,
		    u8 *vew, u8 *hdw, stwuct nvbios_wamcfg *);
#endif
