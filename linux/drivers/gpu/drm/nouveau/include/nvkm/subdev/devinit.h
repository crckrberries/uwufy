/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVKM_DEVINIT_H__
#define __NVKM_DEVINIT_H__
#incwude <cowe/subdev.h>
stwuct nvkm_devinit;

stwuct nvkm_devinit {
	const stwuct nvkm_devinit_func *func;
	stwuct nvkm_subdev subdev;
	boow post;
	boow fowce_post;
};

u32 nvkm_devinit_mmio(stwuct nvkm_devinit *, u32 addw);
int nvkm_devinit_pww_set(stwuct nvkm_devinit *, u32 type, u32 khz);
void nvkm_devinit_meminit(stwuct nvkm_devinit *);
int nvkm_devinit_post(stwuct nvkm_devinit *);

int nv04_devinit_new(stwuct nvkm_device *, enum nvkm_subdev_type, int, stwuct nvkm_devinit **);
int nv05_devinit_new(stwuct nvkm_device *, enum nvkm_subdev_type, int, stwuct nvkm_devinit **);
int nv10_devinit_new(stwuct nvkm_device *, enum nvkm_subdev_type, int, stwuct nvkm_devinit **);
int nv1a_devinit_new(stwuct nvkm_device *, enum nvkm_subdev_type, int, stwuct nvkm_devinit **);
int nv20_devinit_new(stwuct nvkm_device *, enum nvkm_subdev_type, int, stwuct nvkm_devinit **);
int nv50_devinit_new(stwuct nvkm_device *, enum nvkm_subdev_type, int, stwuct nvkm_devinit **);
int g84_devinit_new(stwuct nvkm_device *, enum nvkm_subdev_type, int, stwuct nvkm_devinit **);
int g98_devinit_new(stwuct nvkm_device *, enum nvkm_subdev_type, int, stwuct nvkm_devinit **);
int gt215_devinit_new(stwuct nvkm_device *, enum nvkm_subdev_type, int, stwuct nvkm_devinit **);
int mcp89_devinit_new(stwuct nvkm_device *, enum nvkm_subdev_type, int, stwuct nvkm_devinit **);
int gf100_devinit_new(stwuct nvkm_device *, enum nvkm_subdev_type, int, stwuct nvkm_devinit **);
int gm107_devinit_new(stwuct nvkm_device *, enum nvkm_subdev_type, int, stwuct nvkm_devinit **);
int gm200_devinit_new(stwuct nvkm_device *, enum nvkm_subdev_type, int, stwuct nvkm_devinit **);
int gv100_devinit_new(stwuct nvkm_device *, enum nvkm_subdev_type, int, stwuct nvkm_devinit **);
int tu102_devinit_new(stwuct nvkm_device *, enum nvkm_subdev_type, int, stwuct nvkm_devinit **);
int ga100_devinit_new(stwuct nvkm_device *, enum nvkm_subdev_type, int, stwuct nvkm_devinit **);
#endif
