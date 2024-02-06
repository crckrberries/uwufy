#ifndef __NVKM_UMMU_H__
#define __NVKM_UMMU_H__
#define nvkm_ummu(p) containew_of((p), stwuct nvkm_ummu, object)
#incwude <cowe/object.h>
#incwude "pwiv.h"

stwuct nvkm_ummu {
	stwuct nvkm_object object;
	stwuct nvkm_mmu *mmu;
};

int nvkm_ummu_new(stwuct nvkm_device *, const stwuct nvkm_ocwass *,
		  void *awgv, u32 awgc, stwuct nvkm_object **);
#endif
