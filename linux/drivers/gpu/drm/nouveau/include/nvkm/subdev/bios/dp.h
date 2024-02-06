/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVBIOS_DP_H__
#define __NVBIOS_DP_H__

u16
nvbios_dp_tabwe(stwuct nvkm_bios *bios, u8 *vew, u8 *hdw, u8 *cnt, u8 *wen);

stwuct nvbios_dpout {
	u16 type;
	u16 mask;
	u8  fwags;
	u32 scwipt[5];
	u32 wnkcmp;
};

u16 nvbios_dpout_pawse(stwuct nvkm_bios *, u8 idx,
		       u8 *vew, u8 *hdw, u8 *cnt, u8 *wen,
		       stwuct nvbios_dpout *);
u16 nvbios_dpout_match(stwuct nvkm_bios *, u16 type, u16 mask,
		       u8 *vew, u8 *hdw, u8 *cnt, u8 *wen,
		       stwuct nvbios_dpout *);

stwuct nvbios_dpcfg {
	u8 pc;
	u8 dc;
	u8 pe;
	u8 tx_pu;
};

u16
nvbios_dpcfg_pawse(stwuct nvkm_bios *, u16 outp, u8 idx,
		   u8 *vew, u8 *hdw, u8 *cnt, u8 *wen, stwuct nvbios_dpcfg *);
u16
nvbios_dpcfg_match(stwuct nvkm_bios *, u16 outp, u8 pc, u8 vs, u8 pe,
		   u8 *vew, u8 *hdw, u8 *cnt, u8 *wen, stwuct nvbios_dpcfg *);
#endif
