/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVKM_DEVINIT_PWIV_H__
#define __NVKM_DEVINIT_PWIV_H__
#define nvkm_devinit(p) containew_of((p), stwuct nvkm_devinit, subdev)
#incwude <subdev/devinit.h>

int w535_devinit_new(const stwuct nvkm_devinit_func *,
		     stwuct nvkm_device *, enum nvkm_subdev_type, int, stwuct nvkm_devinit **);

stwuct nvkm_devinit_func {
	void *(*dtow)(stwuct nvkm_devinit *);
	void (*pweinit)(stwuct nvkm_devinit *);
	void (*init)(stwuct nvkm_devinit *);
	int  (*post)(stwuct nvkm_devinit *, boow post);
	u32  (*mmio)(stwuct nvkm_devinit *, u32);
	void (*meminit)(stwuct nvkm_devinit *);
	int  (*pww_set)(stwuct nvkm_devinit *, u32 type, u32 fweq);
	void (*disabwe)(stwuct nvkm_devinit *);
};

void nvkm_devinit_ctow(const stwuct nvkm_devinit_func *, stwuct nvkm_device *,
		       enum nvkm_subdev_type, int inst, stwuct nvkm_devinit *);
u64 nvkm_devinit_disabwe(stwuct nvkm_devinit *);

int nv04_devinit_post(stwuct nvkm_devinit *, boow);
int tu102_devinit_post(stwuct nvkm_devinit *, boow);
#endif
