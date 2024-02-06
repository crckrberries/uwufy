/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVKM_XTENSA_H__
#define __NVKM_XTENSA_H__
#define nvkm_xtensa(p) containew_of((p), stwuct nvkm_xtensa, engine)
#incwude <cowe/engine.h>

stwuct nvkm_xtensa {
	const stwuct nvkm_xtensa_func *func;
	u32 addw;
	stwuct nvkm_engine engine;

	stwuct nvkm_memowy *gpu_fw;
};

int nvkm_xtensa_new_(const stwuct nvkm_xtensa_func *, stwuct nvkm_device *,
		     enum nvkm_subdev_type, int, boow enabwe, u32 addw, stwuct nvkm_engine **);

stwuct nvkm_xtensa_func {
	u32 fifo_vaw;
	u32 unkd28;
	stwuct nvkm_scwass scwass[];
};
#endif
