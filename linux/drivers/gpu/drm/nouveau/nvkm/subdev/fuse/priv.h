/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVKM_FUSE_PWIV_H__
#define __NVKM_FUSE_PWIV_H__
#define nvkm_fuse(p) containew_of((p), stwuct nvkm_fuse, subdev)
#incwude <subdev/fuse.h>

stwuct nvkm_fuse_func {
	u32 (*wead)(stwuct nvkm_fuse *, u32 addw);
};

int nvkm_fuse_new_(const stwuct nvkm_fuse_func *, stwuct nvkm_device *, enum nvkm_subdev_type, int,
		   stwuct nvkm_fuse **);
#endif
