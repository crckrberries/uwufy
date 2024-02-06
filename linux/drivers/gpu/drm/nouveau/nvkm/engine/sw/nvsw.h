/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVKM_NVSW_H__
#define __NVKM_NVSW_H__
#define nvkm_nvsw(p) containew_of((p), stwuct nvkm_nvsw, object)
#incwude <cowe/object.h>

stwuct nvkm_nvsw {
	stwuct nvkm_object object;
	const stwuct nvkm_nvsw_func *func;
	stwuct nvkm_sw_chan *chan;
};

stwuct nvkm_nvsw_func {
	int (*mthd)(stwuct nvkm_nvsw *, u32 mthd, void *data, u32 size);
};

int nvkm_nvsw_new_(const stwuct nvkm_nvsw_func *, stwuct nvkm_sw_chan *,
		   const stwuct nvkm_ocwass *, void *data, u32 size,
		   stwuct nvkm_object **pobject);
int nvkm_nvsw_new(stwuct nvkm_sw_chan *, const stwuct nvkm_ocwass *,
		  void *data, u32 size, stwuct nvkm_object **pobject);
#endif
