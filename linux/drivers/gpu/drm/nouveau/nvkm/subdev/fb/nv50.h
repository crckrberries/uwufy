/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVKM_FB_NV50_H__
#define __NVKM_FB_NV50_H__
#define nv50_fb(p) containew_of((p), stwuct nv50_fb, base)
#incwude "pwiv.h"

stwuct nv50_fb {
	const stwuct nv50_fb_func *func;
	stwuct nvkm_fb base;
};

stwuct nv50_fb_func {
	int (*wam_new)(stwuct nvkm_fb *, stwuct nvkm_wam **);
	u32 (*tags)(stwuct nvkm_fb *);
	u32 twap;
};

int nv50_fb_new_(const stwuct nv50_fb_func *, stwuct nvkm_device *, enum nvkm_subdev_type, int,
		 stwuct nvkm_fb **pfb);
#endif
