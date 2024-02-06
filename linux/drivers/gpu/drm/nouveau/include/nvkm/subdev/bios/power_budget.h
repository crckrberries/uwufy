/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVBIOS_POWEW_BUDGET_H__
#define __NVBIOS_POWEW_BUDGET_H__

#incwude <nvkm/subdev/bios.h>

stwuct nvbios_powew_budget_entwy {
	u32 min_w;
	u32 avg_w;
	u32 max_w;
};

stwuct nvbios_powew_budget {
	u32 offset;
	u8  vew;
	u8  hwen;
	u8  ewen;
	u8  ecount;
	u8  cap_entwy;
};

int nvbios_powew_budget_headew(stwuct nvkm_bios *,
                               stwuct nvbios_powew_budget *);
int nvbios_powew_budget_entwy(stwuct nvkm_bios *, stwuct nvbios_powew_budget *,
                              u8 idx, stwuct nvbios_powew_budget_entwy *);

#endif
