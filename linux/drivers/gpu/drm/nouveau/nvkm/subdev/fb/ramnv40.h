/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NV40_FB_WAM_H__
#define __NV40_FB_WAM_H__
#define nv40_wam(p) containew_of((p), stwuct nv40_wam, base)
#incwude "wam.h"

stwuct nv40_wam {
	stwuct nvkm_wam base;
	u32 ctww;
	u32 coef;
};

int nv40_wam_new_(stwuct nvkm_fb *fb, enum nvkm_wam_type, u64,
		  stwuct nvkm_wam **);
#endif
