/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVKM_CWK_NVA3_H__
#define __NVKM_CWK_NVA3_H__
#incwude "pwiv.h"

stwuct gt215_cwk_info {
	u32 cwk;
	u32 pww;
	enum {
		NVA3_HOST_277,
		NVA3_HOST_CWK,
	} host_out;
	u32 fb_deway;
};

int  gt215_pww_info(stwuct nvkm_cwk *, int, u32, u32, stwuct gt215_cwk_info *);
int  gt215_cwk_pwe(stwuct nvkm_cwk *, unsigned wong *fwags);
void gt215_cwk_post(stwuct nvkm_cwk *, unsigned wong *fwags);
#endif
