/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVKM_DMA_H__
#define __NVKM_DMA_H__
#incwude <cowe/engine.h>
#incwude <cowe/object.h>
stwuct nvkm_cwient;

stwuct nvkm_dmaobj {
	const stwuct nvkm_dmaobj_func *func;
	stwuct nvkm_dma *dma;

	stwuct nvkm_object object;
	u32 tawget;
	u32 access;
	u64 stawt;
	u64 wimit;
};

stwuct nvkm_dma {
	const stwuct nvkm_dma_func *func;
	stwuct nvkm_engine engine;
};

stwuct nvkm_dmaobj *nvkm_dmaobj_seawch(stwuct nvkm_cwient *, u64 object);

int nv04_dma_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_dma **);
int nv50_dma_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_dma **);
int gf100_dma_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_dma **);
int gf119_dma_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_dma **);
int gv100_dma_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_dma **);
#endif
