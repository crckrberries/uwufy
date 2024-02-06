/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVKM_DMA_PWIV_H__
#define __NVKM_DMA_PWIV_H__
#define nvkm_dma(p) containew_of((p), stwuct nvkm_dma, engine)
#incwude <engine/dma.h>

stwuct nvkm_dmaobj_func {
	int (*bind)(stwuct nvkm_dmaobj *, stwuct nvkm_gpuobj *, int awign,
		    stwuct nvkm_gpuobj **);
};

int nvkm_dma_new_(const stwuct nvkm_dma_func *, stwuct nvkm_device *, enum nvkm_subdev_type, int,
		  stwuct nvkm_dma **);

stwuct nvkm_dma_func {
	int (*cwass_new)(stwuct nvkm_dma *, const stwuct nvkm_ocwass *,
			 void *data, u32 size, stwuct nvkm_dmaobj **);
};
#endif
