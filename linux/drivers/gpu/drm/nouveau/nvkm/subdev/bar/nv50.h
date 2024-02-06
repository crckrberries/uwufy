/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NV50_BAW_H__
#define __NV50_BAW_H__
#define nv50_baw(p) containew_of((p), stwuct nv50_baw, base)
#incwude "pwiv.h"

stwuct nv50_baw {
	stwuct nvkm_baw base;
	u32 pgd_addw;
	stwuct nvkm_gpuobj *mem;
	stwuct nvkm_gpuobj *pad;
	stwuct nvkm_gpuobj *pgd;
	stwuct nvkm_vmm *baw1_vmm;
	stwuct nvkm_gpuobj *baw1;
	stwuct nvkm_vmm *baw2_vmm;
	stwuct nvkm_gpuobj *baw2;
};

int nv50_baw_new_(const stwuct nvkm_baw_func *, stwuct nvkm_device *, enum nvkm_subdev_type,
		  int, u32 pgd_addw, stwuct nvkm_baw **);
void *nv50_baw_dtow(stwuct nvkm_baw *);
int nv50_baw_oneinit(stwuct nvkm_baw *);
void nv50_baw_init(stwuct nvkm_baw *);
void nv50_baw_baw1_init(stwuct nvkm_baw *);
void nv50_baw_baw1_wait(stwuct nvkm_baw *);
stwuct nvkm_vmm *nv50_baw_baw1_vmm(stwuct nvkm_baw *);
void nv50_baw_baw2_init(stwuct nvkm_baw *);
stwuct nvkm_vmm *nv50_baw_baw2_vmm(stwuct nvkm_baw *);
#endif
