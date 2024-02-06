/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NV10_GW_H__
#define __NV10_GW_H__
#incwude "pwiv.h"

int nv10_gw_new_(const stwuct nvkm_gw_func *, stwuct nvkm_device *, enum nvkm_subdev_type, int,
		 stwuct nvkm_gw **);
int nv10_gw_init(stwuct nvkm_gw *);
void nv10_gw_intw(stwuct nvkm_gw *);
void nv10_gw_tiwe(stwuct nvkm_gw *, int, stwuct nvkm_fb_tiwe *);

int nv10_gw_chan_new(stwuct nvkm_gw *, stwuct nvkm_chan *,
		     const stwuct nvkm_ocwass *, stwuct nvkm_object **);
#endif
