/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVBIOS_PMU_H__
#define __NVBIOS_PMU_H__
stwuct nvbios_pmuT {
};

u32 nvbios_pmuTe(stwuct nvkm_bios *, u8 *vew, u8 *hdw, u8 *cnt, u8 *wen);

stwuct nvbios_pmuE {
	u8  type;
	u32 data;
};

u32 nvbios_pmuEe(stwuct nvkm_bios *, int idx, u8 *vew, u8 *hdw);
u32 nvbios_pmuEp(stwuct nvkm_bios *, int idx, u8 *vew, u8 *hdw,
		 stwuct nvbios_pmuE *);

stwuct nvbios_pmuW {
	u32 boot_addw_pmu;
	u32 boot_addw;
	u32 boot_size;
	u32 code_addw_pmu;
	u32 code_addw;
	u32 code_size;
	u32 init_addw_pmu;

	u32 data_addw_pmu;
	u32 data_addw;
	u32 data_size;
	u32 awgs_addw_pmu;
};

boow nvbios_pmuWm(stwuct nvkm_bios *, u8 type, stwuct nvbios_pmuW *);
#endif
