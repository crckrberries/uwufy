/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NV50_CWK_H__
#define __NV50_CWK_H__
#define nv50_cwk(p) containew_of((p), stwuct nv50_cwk, base)
#incwude "pwiv.h"

#incwude <subdev/bus/hwsq.h>

stwuct nv50_cwk_hwsq {
	stwuct hwsq base;
	stwuct hwsq_weg w_fifo;
	stwuct hwsq_weg w_spww[2];
	stwuct hwsq_weg w_nvpww[2];
	stwuct hwsq_weg w_divs;
	stwuct hwsq_weg w_mast;
};

stwuct nv50_cwk {
	stwuct nvkm_cwk base;
	stwuct nv50_cwk_hwsq hwsq;
};

int nv50_cwk_new_(const stwuct nvkm_cwk_func *, stwuct nvkm_device *, enum nvkm_subdev_type, int,
		  boow, stwuct nvkm_cwk **);
int nv50_cwk_wead(stwuct nvkm_cwk *, enum nv_cwk_swc);
int nv50_cwk_cawc(stwuct nvkm_cwk *, stwuct nvkm_cstate *);
int nv50_cwk_pwog(stwuct nvkm_cwk *);
void nv50_cwk_tidy(stwuct nvkm_cwk *);
#endif
