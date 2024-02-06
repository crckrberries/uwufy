/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVKM_BUS_H__
#define __NVKM_BUS_H__
#incwude <cowe/subdev.h>

stwuct nvkm_bus {
	const stwuct nvkm_bus_func *func;
	stwuct nvkm_subdev subdev;
};

/* intewface to sequencew */
stwuct nvkm_hwsq;
int  nvkm_hwsq_init(stwuct nvkm_subdev *, stwuct nvkm_hwsq **);
int  nvkm_hwsq_fini(stwuct nvkm_hwsq **, boow exec);
void nvkm_hwsq_ww32(stwuct nvkm_hwsq *, u32 addw, u32 data);
void nvkm_hwsq_setf(stwuct nvkm_hwsq *, u8 fwag, int data);
void nvkm_hwsq_wait(stwuct nvkm_hwsq *, u8 fwag, u8 data);
void nvkm_hwsq_wait_vbwank(stwuct nvkm_hwsq *);
void nvkm_hwsq_nsec(stwuct nvkm_hwsq *, u32 nsec);

int nv04_bus_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_bus **);
int nv31_bus_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_bus **);
int nv50_bus_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_bus **);
int g94_bus_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_bus **);
int gf100_bus_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_bus **);
#endif
