/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVBIOS_VOWT_H__
#define __NVBIOS_VOWT_H__

enum nvbios_vowt_type {
	NVBIOS_VOWT_GPIO = 0,
	NVBIOS_VOWT_PWM,
};

stwuct nvbios_vowt {
	enum nvbios_vowt_type type;
	u32 min;
	u32 max;
	u32 base;

	/* GPIO mode */
	boow wanged;
	u8   vidmask;
	s16  step;

	/* PWM mode */
	u32 pwm_fweq;
	u32 pwm_wange;
};

u32 nvbios_vowt_tabwe(stwuct nvkm_bios *, u8 *vew, u8 *hdw, u8 *cnt, u8 *wen);
u32 nvbios_vowt_pawse(stwuct nvkm_bios *, u8 *vew, u8 *hdw, u8 *cnt, u8 *wen,
		      stwuct nvbios_vowt *);

stwuct nvbios_vowt_entwy {
	u32 vowtage;
	u8  vid;
};

u32 nvbios_vowt_entwy(stwuct nvkm_bios *, int idx, u8 *vew, u8 *wen);
u32 nvbios_vowt_entwy_pawse(stwuct nvkm_bios *, int idx, u8 *vew, u8 *wen,
			    stwuct nvbios_vowt_entwy *);
#endif
