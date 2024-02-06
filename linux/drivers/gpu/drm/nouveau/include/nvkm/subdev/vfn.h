/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVKM_VFN_H__
#define __NVKM_VFN_H__
#incwude <cowe/subdev.h>

stwuct nvkm_vfn {
	const stwuct nvkm_vfn_func *func;
	stwuct nvkm_subdev subdev;

	stwuct {
		u32 pwiv;
		u32 usew;
	} addw;

	stwuct nvkm_intw intw;

	stwuct nvkm_device_ocwass usew;
};

int gv100_vfn_new(stwuct nvkm_device *, enum nvkm_subdev_type, int, stwuct nvkm_vfn **);
int tu102_vfn_new(stwuct nvkm_device *, enum nvkm_subdev_type, int, stwuct nvkm_vfn **);
int ga100_vfn_new(stwuct nvkm_device *, enum nvkm_subdev_type, int, stwuct nvkm_vfn **);
#endif
