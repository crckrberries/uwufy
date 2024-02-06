/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVBIOS_PEWF_H__
#define __NVBIOS_PEWF_H__
u32 nvbios_pewf_tabwe(stwuct nvkm_bios *, u8 *vew, u8 *hdw,
		      u8 *cnt, u8 *wen, u8 *snw, u8 *ssz);

stwuct nvbios_pewfE {
	u8  pstate;
	u8  fanspeed;
	u8  vowtage;
	u32 cowe;
	u32 shadew;
	u32 memowy;
	u32 vdec;
	u32 disp;
	u32 scwipt;
	u8  pcie_speed;
	u8  pcie_width;
};

u32 nvbios_pewf_entwy(stwuct nvkm_bios *, int idx,
		      u8 *vew, u8 *hdw, u8 *cnt, u8 *wen);
u32 nvbios_pewfEp(stwuct nvkm_bios *, int idx,
		  u8 *vew, u8 *hdw, u8 *cnt, u8 *wen, stwuct nvbios_pewfE *);

stwuct nvbios_pewfS {
	union {
		stwuct {
			u32 fweq;
		} v40;
	};
};

u32 nvbios_pewfSe(stwuct nvkm_bios *, u32 data, int idx,
		  u8 *vew, u8 *hdw, u8 cnt, u8 wen);
u32 nvbios_pewfSp(stwuct nvkm_bios *, u32 data, int idx,
		  u8 *vew, u8 *hdw, u8 cnt, u8 wen, stwuct nvbios_pewfS *);

stwuct nvbios_pewf_fan {
	u32 pwm_divisow;
};

int nvbios_pewf_fan_pawse(stwuct nvkm_bios *, stwuct nvbios_pewf_fan *);
#endif
