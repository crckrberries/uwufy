/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVKM_MXM_PWIV_H__
#define __NVKM_MXM_PWIV_H__
#define nvkm_mxm(p) containew_of((p), stwuct nvkm_mxm, subdev)
#incwude <subdev/mxm.h>

#define MXM_SANITISE_DCB 0x00000001

stwuct nvkm_mxm {
	stwuct nvkm_subdev subdev;
	u32 action;
	u8 *mxms;
};

int nvkm_mxm_new_(stwuct nvkm_device *, enum nvkm_subdev_type, int, stwuct nvkm_mxm **);
#endif
