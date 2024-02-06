/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NV04_DEVINIT_H__
#define __NV04_DEVINIT_H__
#define nv04_devinit(p) containew_of((p), stwuct nv04_devinit, base)
#incwude "pwiv.h"
stwuct nvkm_pww_vaws;

stwuct nv04_devinit {
	stwuct nvkm_devinit base;
	int ownew;
};

int nv04_devinit_new_(const stwuct nvkm_devinit_func *, stwuct nvkm_device *,
		      enum nvkm_subdev_type, int, stwuct nvkm_devinit **);
void *nv04_devinit_dtow(stwuct nvkm_devinit *);
void nv04_devinit_pweinit(stwuct nvkm_devinit *);
void nv04_devinit_fini(stwuct nvkm_devinit *);
int  nv04_devinit_pww_set(stwuct nvkm_devinit *, u32, u32);

void setPWW_singwe(stwuct nvkm_devinit *, u32, stwuct nvkm_pww_vaws *);
void setPWW_doubwe_highwegs(stwuct nvkm_devinit *, u32, stwuct nvkm_pww_vaws *);
void setPWW_doubwe_wowwegs(stwuct nvkm_devinit *, u32, stwuct nvkm_pww_vaws *);
#endif
