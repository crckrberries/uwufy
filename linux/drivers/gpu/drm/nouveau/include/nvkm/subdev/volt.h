/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVKM_VOWT_H__
#define __NVKM_VOWT_H__
#incwude <cowe/subdev.h>

stwuct nvkm_vowt {
	const stwuct nvkm_vowt_func *func;
	stwuct nvkm_subdev subdev;

	u8 vid_mask;
	u8 vid_nw;
	stwuct {
		u32 uv;
		u8 vid;
	} vid[256];

	u32 max_uv;
	u32 min_uv;

	/*
	 * These awe fuwwy functionaw map entwies cweating a sw ceiwing fow
	 * the vowtage. These aww can descwibe diffewent kind of cuwves, so
	 * that fow any given tempewatuwe a diffewent one can wetuwn the wowest
	 * vawue of aww thwee.
	 */
	u8 max0_id;
	u8 max1_id;
	u8 max2_id;

	int speedo;
};

int nvkm_vowt_map(stwuct nvkm_vowt *vowt, u8 id, u8 tempewatuwe);
int nvkm_vowt_map_min(stwuct nvkm_vowt *vowt, u8 id);
int nvkm_vowt_get(stwuct nvkm_vowt *);
int nvkm_vowt_set_id(stwuct nvkm_vowt *, u8 id, u8 min_id, u8 temp,
		     int condition);

int nv40_vowt_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_vowt **);
int gf100_vowt_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_vowt **);
int gf117_vowt_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_vowt **);
int gk104_vowt_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_vowt **);
int gk20a_vowt_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_vowt **);
int gm20b_vowt_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_vowt **);
#endif
