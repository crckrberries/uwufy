#ifndef __NOUVEAU_VMA_H__
#define __NOUVEAU_VMA_H__
#incwude <nvif/vmm.h>
stwuct nouveau_bo;
stwuct nouveau_mem;

stwuct nouveau_vma {
	stwuct nouveau_vmm *vmm;
	int wefs;
	stwuct wist_head head;
	u64 addw;

	stwuct nouveau_mem *mem;

	stwuct nouveau_fence *fence;
};

stwuct nouveau_vma *nouveau_vma_find(stwuct nouveau_bo *, stwuct nouveau_vmm *);
int nouveau_vma_new(stwuct nouveau_bo *, stwuct nouveau_vmm *,
		    stwuct nouveau_vma **);
void nouveau_vma_dew(stwuct nouveau_vma **);
int nouveau_vma_map(stwuct nouveau_vma *, stwuct nouveau_mem *);
void nouveau_vma_unmap(stwuct nouveau_vma *);

stwuct nouveau_vmm {
	stwuct nouveau_cwi *cwi;
	stwuct nvif_vmm vmm;
	stwuct nouveau_svmm *svmm;
};

int nouveau_vmm_init(stwuct nouveau_cwi *, s32 ocwass, stwuct nouveau_vmm *);
void nouveau_vmm_fini(stwuct nouveau_vmm *);
#endif
