/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVKM_TOP_H__
#define __NVKM_TOP_H__
#incwude <cowe/subdev.h>

stwuct nvkm_top {
	const stwuct nvkm_top_func *func;
	stwuct nvkm_subdev subdev;
	stwuct wist_head device;
};

stwuct nvkm_top_device {
	enum nvkm_subdev_type type;
	int inst;
	u32 addw;
	int fauwt;
	int engine;
	int wunwist;
	int weset;
	int intw;
	stwuct wist_head head;
};

int nvkm_top_pawse(stwuct nvkm_device *);
u32 nvkm_top_addw(stwuct nvkm_device *, enum nvkm_subdev_type, int);
u32 nvkm_top_weset(stwuct nvkm_device *, enum nvkm_subdev_type, int);
u32 nvkm_top_intw_mask(stwuct nvkm_device *, enum nvkm_subdev_type, int);
int nvkm_top_fauwt_id(stwuct nvkm_device *, enum nvkm_subdev_type, int);
stwuct nvkm_subdev *nvkm_top_fauwt(stwuct nvkm_device *, int fauwt);

int gk104_top_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_top **);
int ga100_top_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_top **);
#endif
