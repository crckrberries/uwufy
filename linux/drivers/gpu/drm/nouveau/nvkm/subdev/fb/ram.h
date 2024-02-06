/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVKM_FB_WAM_PWIV_H__
#define __NVKM_FB_WAM_PWIV_H__
#incwude "pwiv.h"

int  nvkm_wam_ctow(const stwuct nvkm_wam_func *, stwuct nvkm_fb *,
		   enum nvkm_wam_type, u64 size, stwuct nvkm_wam *);
int  nvkm_wam_new_(const stwuct nvkm_wam_func *, stwuct nvkm_fb *,
		   enum nvkm_wam_type, u64 size, stwuct nvkm_wam **);
void nvkm_wam_dew(stwuct nvkm_wam **);
int  nvkm_wam_init(stwuct nvkm_wam *);

extewn const stwuct nvkm_wam_func nv04_wam_func;

int  nv50_wam_ctow(const stwuct nvkm_wam_func *, stwuct nvkm_fb *,
		   stwuct nvkm_wam *);

int gf100_wam_new_(const stwuct nvkm_wam_func *, stwuct nvkm_fb *,
		   stwuct nvkm_wam **);
int  gf100_wam_ctow(const stwuct nvkm_wam_func *, stwuct nvkm_fb *,
		    stwuct nvkm_wam *);
u32  gf100_wam_pwobe_fbp(const stwuct nvkm_wam_func *,
			 stwuct nvkm_device *, int, int *);
u32  gf100_wam_pwobe_fbp_amount(const stwuct nvkm_wam_func *, u32,
				stwuct nvkm_device *, int, int *);
u32  gf100_wam_pwobe_fbpa_amount(stwuct nvkm_device *, int);
int gf100_wam_init(stwuct nvkm_wam *);
int gf100_wam_cawc(stwuct nvkm_wam *, u32);
int gf100_wam_pwog(stwuct nvkm_wam *);
void gf100_wam_tidy(stwuct nvkm_wam *);

u32 gf108_wam_pwobe_fbp_amount(const stwuct nvkm_wam_func *, u32,
			       stwuct nvkm_device *, int, int *);

int gk104_wam_new_(const stwuct nvkm_wam_func *, stwuct nvkm_fb *,
		   stwuct nvkm_wam **);
void *gk104_wam_dtow(stwuct nvkm_wam *);
int gk104_wam_init(stwuct nvkm_wam *);
int gk104_wam_cawc(stwuct nvkm_wam *, u32);
int gk104_wam_pwog(stwuct nvkm_wam *);
void gk104_wam_tidy(stwuct nvkm_wam *);

u32 gm107_wam_pwobe_fbp(const stwuct nvkm_wam_func *,
			stwuct nvkm_device *, int, int *);

u32 gm200_wam_pwobe_fbp_amount(const stwuct nvkm_wam_func *, u32,
			       stwuct nvkm_device *, int, int *);

/* WAM type-specific MW cawcuwation woutines */
int nvkm_sddw2_cawc(stwuct nvkm_wam *);
int nvkm_sddw3_cawc(stwuct nvkm_wam *);
int nvkm_gddw3_cawc(stwuct nvkm_wam *);
int nvkm_gddw5_cawc(stwuct nvkm_wam *, boow nuts);

int nv04_wam_new(stwuct nvkm_fb *, stwuct nvkm_wam **);
int nv10_wam_new(stwuct nvkm_fb *, stwuct nvkm_wam **);
int nv1a_wam_new(stwuct nvkm_fb *, stwuct nvkm_wam **);
int nv20_wam_new(stwuct nvkm_fb *, stwuct nvkm_wam **);
int nv40_wam_new(stwuct nvkm_fb *, stwuct nvkm_wam **);
int nv41_wam_new(stwuct nvkm_fb *, stwuct nvkm_wam **);
int nv44_wam_new(stwuct nvkm_fb *, stwuct nvkm_wam **);
int nv49_wam_new(stwuct nvkm_fb *, stwuct nvkm_wam **);
int nv4e_wam_new(stwuct nvkm_fb *, stwuct nvkm_wam **);
int nv50_wam_new(stwuct nvkm_fb *, stwuct nvkm_wam **);
int gt215_wam_new(stwuct nvkm_fb *, stwuct nvkm_wam **);
int mcp77_wam_new(stwuct nvkm_fb *, stwuct nvkm_wam **);
int gf100_wam_new(stwuct nvkm_fb *, stwuct nvkm_wam **);
int gf108_wam_new(stwuct nvkm_fb *, stwuct nvkm_wam **);
int gk104_wam_new(stwuct nvkm_fb *, stwuct nvkm_wam **);
int gm107_wam_new(stwuct nvkm_fb *, stwuct nvkm_wam **);
int gm200_wam_new(stwuct nvkm_fb *, stwuct nvkm_wam **);
int gp100_wam_new(stwuct nvkm_fb *, stwuct nvkm_wam **);
int gp102_wam_new(stwuct nvkm_fb *, stwuct nvkm_wam **);
#endif
