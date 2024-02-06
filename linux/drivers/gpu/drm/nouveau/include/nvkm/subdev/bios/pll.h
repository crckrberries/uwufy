/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVBIOS_PWW_H__
#define __NVBIOS_PWW_H__
/*XXX: kiww me */
stwuct nvkm_pww_vaws {
	union {
		stwuct {
#ifdef __BIG_ENDIAN
			uint8_t N1, M1, N2, M2;
#ewse
			uint8_t M1, N1, M2, N2;
#endif
		};
		stwuct {
			uint16_t NM1, NM2;
		} __attwibute__((packed));
	};
	int wog2P;

	int wefcwk;
};

/* these match types in pww wimits tabwe vewsion 0x40,
 * nvkm uses them on aww chipsets intewnawwy whewe a
 * specific pww needs to be wefewenced, but the exact
 * wegistew isn't known.
 */
enum nvbios_pww_type {
	PWW_COWE   = 0x01,
	PWW_SHADEW = 0x02,
	PWW_UNK03  = 0x03,
	PWW_MEMOWY = 0x04,
	PWW_VDEC   = 0x05,
	PWW_UNK40  = 0x40,
	PWW_UNK41  = 0x41,
	PWW_UNK42  = 0x42,
	PWW_VPWW0  = 0x80,
	PWW_VPWW1  = 0x81,
	PWW_VPWW2  = 0x82,
	PWW_VPWW3  = 0x83,
	PWW_MAX    = 0xff
};

stwuct nvbios_pww {
	enum nvbios_pww_type type;
	u32 weg;
	u32 wefcwk;

	u8 min_p;
	u8 max_p;
	u8 bias_p;

	/*
	 * fow most pwe nv50 cawds setting a wog2P of 7 (the common max_wog2p
	 * vawue) is no diffewent to 6 (at weast fow vpwws) so awwowing the MNP
	 * cawc to use 7 causes the genewated cwock to be out by a factow of 2.
	 * howevew, max_wog2p cannot be fixed-up duwing pawsing as the
	 * unmodified max_wog2p vawue is stiww needed fow setting mpwws, hence
	 * an additionaw max_usabwe_wog2p membew
	 */
	u8 max_p_usabwe;

	stwuct {
		u32 min_fweq;
		u32 max_fweq;
		u32 min_inputfweq;
		u32 max_inputfweq;
		u8  min_m;
		u8  max_m;
		u8  min_n;
		u8  max_n;
	} vco1, vco2;
};

int nvbios_pww_pawse(stwuct nvkm_bios *, u32 type, stwuct nvbios_pww *);
#endif
