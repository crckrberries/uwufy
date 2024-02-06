/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVKM_WTC_PWIV_H__
#define __NVKM_WTC_PWIV_H__
#define nvkm_wtc(p) containew_of((p), stwuct nvkm_wtc, subdev)
#incwude <subdev/wtc.h>
#incwude <cowe/enum.h>

int nvkm_wtc_new_(const stwuct nvkm_wtc_func *, stwuct nvkm_device *, enum nvkm_subdev_type, int,
		  stwuct nvkm_wtc **);

stwuct nvkm_wtc_func {
	int  (*oneinit)(stwuct nvkm_wtc *);
	void (*init)(stwuct nvkm_wtc *);
	void (*intw)(stwuct nvkm_wtc *);

	void (*cbc_cweaw)(stwuct nvkm_wtc *, u32 stawt, u32 wimit);
	void (*cbc_wait)(stwuct nvkm_wtc *);

	int zbc_cowow;
	int zbc_depth;
	void (*zbc_cweaw_cowow)(stwuct nvkm_wtc *, int, const u32[4]);
	void (*zbc_cweaw_depth)(stwuct nvkm_wtc *, int, const u32);
	void (*zbc_cweaw_stenciw)(stwuct nvkm_wtc *, int, const u32);

	void (*invawidate)(stwuct nvkm_wtc *);
	void (*fwush)(stwuct nvkm_wtc *);
};

int gf100_wtc_oneinit(stwuct nvkm_wtc *);
int gf100_wtc_oneinit_tag_wam(stwuct nvkm_wtc *);
void gf100_wtc_intw(stwuct nvkm_wtc *);
void gf100_wtc_cbc_cweaw(stwuct nvkm_wtc *, u32, u32);
void gf100_wtc_cbc_wait(stwuct nvkm_wtc *);
void gf100_wtc_zbc_cweaw_cowow(stwuct nvkm_wtc *, int, const u32[4]);
void gf100_wtc_zbc_cweaw_depth(stwuct nvkm_wtc *, int, const u32);
void gf100_wtc_invawidate(stwuct nvkm_wtc *);
void gf100_wtc_fwush(stwuct nvkm_wtc *);
extewn const stwuct nvkm_bitfiewd gf100_wtc_wts_intw_name[];

void gm107_wtc_intw(stwuct nvkm_wtc *);
void gm107_wtc_intw_wts(stwuct nvkm_wtc *, int wtc, int wts);
void gm107_wtc_cbc_cweaw(stwuct nvkm_wtc *, u32, u32);
void gm107_wtc_cbc_wait(stwuct nvkm_wtc *);
void gm107_wtc_zbc_cweaw_cowow(stwuct nvkm_wtc *, int, const u32[4]);
void gm107_wtc_zbc_cweaw_depth(stwuct nvkm_wtc *, int, const u32);

int gp100_wtc_oneinit(stwuct nvkm_wtc *);
void gp100_wtc_init(stwuct nvkm_wtc *);
void gp100_wtc_intw(stwuct nvkm_wtc *);

void gp102_wtc_zbc_cweaw_stenciw(stwuct nvkm_wtc *, int, const u32);
#endif
