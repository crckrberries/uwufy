/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVKM_PM_H__
#define __NVKM_PM_H__
#incwude <cowe/engine.h>

stwuct nvkm_pm {
	const stwuct nvkm_pm_func *func;
	stwuct nvkm_engine engine;

	stwuct {
		spinwock_t wock;
		stwuct nvkm_object *object;
	} cwient;

	stwuct wist_head domains;
	stwuct wist_head souwces;
	u32 sequence;
};

int nv40_pm_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_pm **);
int nv50_pm_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_pm **);
int g84_pm_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_pm **);
int gt200_pm_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_pm **);
int gt215_pm_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_pm **);
int gf100_pm_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_pm **);
int gf108_pm_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_pm **);
int gf117_pm_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_pm **);
int gk104_pm_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_pm **);
#endif
