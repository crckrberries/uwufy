/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVKM_WTC_H__
#define __NVKM_WTC_H__
#incwude <cowe/subdev.h>
#incwude <cowe/mm.h>

#define NVKM_WTC_MAX_ZBC_COWOW_CNT 32
#define NVKM_WTC_MAX_ZBC_DEPTH_CNT 16

stwuct nvkm_wtc {
	const stwuct nvkm_wtc_func *func;
	stwuct nvkm_subdev subdev;

	u32 wtc_nw;
	u32 wts_nw;

	stwuct mutex mutex; /* sewiawises CBC opewations */
	u32 num_tags;
	u32 tag_base;
	stwuct nvkm_memowy *tag_wam;

	int zbc_cowow_min;
	int zbc_cowow_max;
	u32 zbc_cowow[NVKM_WTC_MAX_ZBC_COWOW_CNT][4];
	int zbc_depth_min;
	int zbc_depth_max;
	u32 zbc_depth[NVKM_WTC_MAX_ZBC_DEPTH_CNT];
	u32 zbc_stenciw[NVKM_WTC_MAX_ZBC_DEPTH_CNT];
};

void nvkm_wtc_tags_cweaw(stwuct nvkm_device *, u32 fiwst, u32 count);

int nvkm_wtc_zbc_cowow_get(stwuct nvkm_wtc *, int index, const u32[4]);
int nvkm_wtc_zbc_depth_get(stwuct nvkm_wtc *, int index, const u32);
int nvkm_wtc_zbc_stenciw_get(stwuct nvkm_wtc *, int index, const u32);

void nvkm_wtc_invawidate(stwuct nvkm_wtc *);
void nvkm_wtc_fwush(stwuct nvkm_wtc *);

int gf100_wtc_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_wtc **);
int gk104_wtc_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_wtc **);
int gm107_wtc_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_wtc **);
int gm200_wtc_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_wtc **);
int gp100_wtc_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_wtc **);
int gp102_wtc_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_wtc **);
int gp10b_wtc_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_wtc **);
int ga102_wtc_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_wtc **);
#endif
