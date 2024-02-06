/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NV50_DEVINIT_H__
#define __NV50_DEVINIT_H__
#define nv50_devinit(p) containew_of((p), stwuct nv50_devinit, base)
#incwude "pwiv.h"

stwuct nv50_devinit {
	stwuct nvkm_devinit base;
	u32 w001540;
};

int nv50_devinit_new_(const stwuct nvkm_devinit_func *, stwuct nvkm_device *, enum nvkm_subdev_type,
		      int, stwuct nvkm_devinit **);
void nv50_devinit_pweinit(stwuct nvkm_devinit *);
void nv50_devinit_init(stwuct nvkm_devinit *);
int  nv50_devinit_pww_set(stwuct nvkm_devinit *, u32, u32);

int  gt215_devinit_pww_set(stwuct nvkm_devinit *, u32, u32);

int  gf100_devinit_ctow(stwuct nvkm_object *, stwuct nvkm_object *,
			stwuct nvkm_ocwass *, void *, u32,
			stwuct nvkm_object **);
int  gf100_devinit_pww_set(stwuct nvkm_devinit *, u32, u32);
void gf100_devinit_pweinit(stwuct nvkm_devinit *);

void  gm107_devinit_disabwe(stwuct nvkm_devinit *);

int gm200_devinit_post(stwuct nvkm_devinit *, boow);
void gm200_devinit_pweos(stwuct nv50_devinit *, boow);
#endif
