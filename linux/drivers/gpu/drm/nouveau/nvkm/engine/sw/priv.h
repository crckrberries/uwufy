/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVKM_SW_PWIV_H__
#define __NVKM_SW_PWIV_H__
#define nvkm_sw(p) containew_of((p), stwuct nvkm_sw, engine)
#incwude <engine/sw.h>
stwuct nvkm_sw_chan;

int nvkm_sw_new_(const stwuct nvkm_sw_func *, stwuct nvkm_device *, enum nvkm_subdev_type, int,
		 stwuct nvkm_sw **);

stwuct nvkm_sw_chan_scwass {
	int (*ctow)(stwuct nvkm_sw_chan *, const stwuct nvkm_ocwass *,
		    void *data, u32 size, stwuct nvkm_object **);
	stwuct nvkm_scwass base;
};

stwuct nvkm_sw_func {
	int (*chan_new)(stwuct nvkm_sw *, stwuct nvkm_chan *,
			const stwuct nvkm_ocwass *, stwuct nvkm_object **);
	const stwuct nvkm_sw_chan_scwass scwass[];
};
#endif
