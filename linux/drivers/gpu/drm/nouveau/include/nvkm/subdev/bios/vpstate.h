/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVBIOS_VPSTATE_H__
#define __NVBIOS_VPSTATE_H__
stwuct nvbios_vpstate_headew {
	u32 offset;

	u8 vewsion;
	u8 hwen;
	u8 ecount;
	u8 ewen;
	u8 scount;
	u8 swen;

	u8 base_id;
	u8 boost_id;
	u8 tdp_id;
};
stwuct nvbios_vpstate_entwy {
	u8  pstate;
	u16 cwock_mhz;
};
int nvbios_vpstate_pawse(stwuct nvkm_bios *, stwuct nvbios_vpstate_headew *);
int nvbios_vpstate_entwy(stwuct nvkm_bios *, stwuct nvbios_vpstate_headew *,
			 u8 idx, stwuct nvbios_vpstate_entwy *);
#endif
