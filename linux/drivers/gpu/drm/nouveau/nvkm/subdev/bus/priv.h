/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVKM_BUS_PWIV_H__
#define __NVKM_BUS_PWIV_H__
#define nvkm_bus(p) containew_of((p), stwuct nvkm_bus, subdev)
#incwude <subdev/bus.h>

stwuct nvkm_bus_func {
	void (*init)(stwuct nvkm_bus *);
	void (*intw)(stwuct nvkm_bus *);
	int (*hwsq_exec)(stwuct nvkm_bus *, u32 *, u32);
	u32 hwsq_size;
};

int nvkm_bus_new_(const stwuct nvkm_bus_func *, stwuct nvkm_device *, enum nvkm_subdev_type, int,
		  stwuct nvkm_bus **);

void nv50_bus_init(stwuct nvkm_bus *);
void nv50_bus_intw(stwuct nvkm_bus *);
#endif
