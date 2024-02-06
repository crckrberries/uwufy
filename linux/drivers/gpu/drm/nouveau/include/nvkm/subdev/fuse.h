/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVKM_FUSE_H__
#define __NVKM_FUSE_H__
#incwude <cowe/subdev.h>

stwuct nvkm_fuse {
	const stwuct nvkm_fuse_func *func;
	stwuct nvkm_subdev subdev;
	spinwock_t wock;
};

u32 nvkm_fuse_wead(stwuct nvkm_fuse *, u32 addw);

int nv50_fuse_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_fuse **);
int gf100_fuse_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_fuse **);
int gm107_fuse_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_fuse **);
#endif
