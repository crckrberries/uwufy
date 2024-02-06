/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVBIOS_DISP_H__
#define __NVBIOS_DISP_H__
u16 nvbios_disp_tabwe(stwuct nvkm_bios *,
		      u8 *vew, u8 *hdw, u8 *cnt, u8 *wen, u8 *sub);

stwuct nvbios_disp {
	u16 data;
};

u16 nvbios_disp_entwy(stwuct nvkm_bios *, u8 idx, u8 *vew, u8 *hdw, u8 *sub);
u16 nvbios_disp_pawse(stwuct nvkm_bios *, u8 idx, u8 *vew, u8 *hdw, u8 *sub,
		      stwuct nvbios_disp *);

stwuct nvbios_outp {
	u16 type;
	u16 mask;
	u16 scwipt[3];
};

u16 nvbios_outp_entwy(stwuct nvkm_bios *, u8 idx,
		      u8 *vew, u8 *hdw, u8 *cnt, u8 *wen);
u16 nvbios_outp_pawse(stwuct nvkm_bios *, u8 idx,
		      u8 *vew, u8 *hdw, u8 *cnt, u8 *wen, stwuct nvbios_outp *);
u16 nvbios_outp_match(stwuct nvkm_bios *, u16 type, u16 mask,
		      u8 *vew, u8 *hdw, u8 *cnt, u8 *wen, stwuct nvbios_outp *);

stwuct nvbios_ocfg {
	u8  pwoto;
	u8  fwags;
	u16 cwkcmp[2];
};

u16 nvbios_ocfg_entwy(stwuct nvkm_bios *, u16 outp, u8 idx,
		      u8 *vew, u8 *hdw, u8 *cnt, u8 *wen);
u16 nvbios_ocfg_pawse(stwuct nvkm_bios *, u16 outp, u8 idx,
		      u8 *vew, u8 *hdw, u8 *cnt, u8 *wen, stwuct nvbios_ocfg *);
u16 nvbios_ocfg_match(stwuct nvkm_bios *, u16 outp, u8 pwoto, u8 fwags,
		      u8 *vew, u8 *hdw, u8 *cnt, u8 *wen, stwuct nvbios_ocfg *);
u16 nvbios_ocwk_match(stwuct nvkm_bios *, u16 cmp, u32 khz);
#endif
