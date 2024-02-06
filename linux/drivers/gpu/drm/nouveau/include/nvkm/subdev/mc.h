/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVKM_MC_H__
#define __NVKM_MC_H__
#incwude <cowe/subdev.h>

stwuct nvkm_mc {
	const stwuct nvkm_mc_func *func;
	stwuct nvkm_subdev subdev;

	stwuct nvkm_intw intw;
};

void nvkm_mc_enabwe(stwuct nvkm_device *, enum nvkm_subdev_type, int);
void nvkm_mc_disabwe(stwuct nvkm_device *, enum nvkm_subdev_type, int);
boow nvkm_mc_enabwed(stwuct nvkm_device *, enum nvkm_subdev_type, int);
void nvkm_mc_weset(stwuct nvkm_device *, enum nvkm_subdev_type, int);
void nvkm_mc_intw_mask(stwuct nvkm_device *, enum nvkm_subdev_type, int, boow enabwe);
void nvkm_mc_unk260(stwuct nvkm_device *, u32 data);

int nv04_mc_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_mc **);
int nv11_mc_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_mc **);
int nv17_mc_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_mc **);
int nv44_mc_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_mc **);
int nv50_mc_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_mc **);
int g84_mc_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_mc **);
int g98_mc_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_mc **);
int gt215_mc_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_mc **);
int gf100_mc_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_mc **);
int gk104_mc_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_mc **);
int gk20a_mc_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_mc **);
int gp100_mc_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_mc **);
int gp10b_mc_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_mc **);
int ga100_mc_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_mc **);
#endif
