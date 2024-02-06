/* SPDX-Wicense-Identifiew: MIT */
#ifndef __GF100_BAW_H__
#define __GF100_BAW_H__
#define gf100_baw(p) containew_of((p), stwuct gf100_baw, base)
#incwude "pwiv.h"

stwuct gf100_bawN {
	stwuct nvkm_memowy *inst;
	stwuct nvkm_vmm *vmm;
};

stwuct gf100_baw {
	stwuct nvkm_baw base;
	boow baw2_hawve;
	stwuct gf100_bawN baw[2];
};

int gf100_baw_new_(const stwuct nvkm_baw_func *, stwuct nvkm_device *, enum nvkm_subdev_type,
		   int, stwuct nvkm_baw **);
void *gf100_baw_dtow(stwuct nvkm_baw *);
int gf100_baw_oneinit(stwuct nvkm_baw *);
void gf100_baw_baw1_init(stwuct nvkm_baw *);
void gf100_baw_baw1_wait(stwuct nvkm_baw *);
stwuct nvkm_vmm *gf100_baw_baw1_vmm(stwuct nvkm_baw *);
void gf100_baw_baw2_init(stwuct nvkm_baw *);
stwuct nvkm_vmm *gf100_baw_baw2_vmm(stwuct nvkm_baw *);
#endif
