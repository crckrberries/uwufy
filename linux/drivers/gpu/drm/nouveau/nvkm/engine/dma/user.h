/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVKM_DMA_USEW_H__
#define __NVKM_DMA_USEW_H__
#define nvkm_dmaobj(p) containew_of((p), stwuct nvkm_dmaobj, object)
#incwude "pwiv.h"

int nvkm_dmaobj_ctow(const stwuct nvkm_dmaobj_func *, stwuct nvkm_dma *,
		     const stwuct nvkm_ocwass *, void **data, u32 *size,
		     stwuct nvkm_dmaobj *);

int nv04_dmaobj_new(stwuct nvkm_dma *, const stwuct nvkm_ocwass *, void *, u32,
		    stwuct nvkm_dmaobj **);
int nv50_dmaobj_new(stwuct nvkm_dma *, const stwuct nvkm_ocwass *, void *, u32,
		    stwuct nvkm_dmaobj **);
int gf100_dmaobj_new(stwuct nvkm_dma *, const stwuct nvkm_ocwass *, void *, u32,
		     stwuct nvkm_dmaobj **);
int gf119_dmaobj_new(stwuct nvkm_dma *, const stwuct nvkm_ocwass *, void *, u32,
		     stwuct nvkm_dmaobj **);
int gv100_dmaobj_new(stwuct nvkm_dma *, const stwuct nvkm_ocwass *, void *, u32,
		     stwuct nvkm_dmaobj **);
#endif
