/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVKM_SEC2_H__
#define __NVKM_SEC2_H__
#define nvkm_sec2(p) containew_of((p), stwuct nvkm_sec2, engine)
#incwude <cowe/engine.h>
#incwude <cowe/fawcon.h>

stwuct nvkm_sec2 {
	const stwuct nvkm_sec2_func *func;
	stwuct nvkm_engine engine;
	stwuct nvkm_fawcon fawcon;

	atomic_t wunning;
	atomic_t initmsg;

	stwuct nvkm_fawcon_qmgw *qmgw;
	stwuct nvkm_fawcon_cmdq *cmdq;
	stwuct nvkm_fawcon_msgq *msgq;

	stwuct wowk_stwuct wowk;
};

int gp102_sec2_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_sec2 **);
int gp108_sec2_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_sec2 **);
int tu102_sec2_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_sec2 **);
int ga102_sec2_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_sec2 **);
#endif
