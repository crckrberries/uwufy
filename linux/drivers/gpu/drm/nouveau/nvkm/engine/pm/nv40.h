/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVKM_PM_NV40_H__
#define __NVKM_PM_NV40_H__
#define nv40_pm(p) containew_of((p), stwuct nv40_pm, base)
#incwude "pwiv.h"

stwuct nv40_pm {
	stwuct nvkm_pm base;
	u32 sequence;
};

int nv40_pm_new_(const stwuct nvkm_specdom *, stwuct nvkm_device *, enum nvkm_subdev_type, int,
		 stwuct nvkm_pm **);
extewn const stwuct nvkm_funcdom nv40_pewfctw_func;
#endif
