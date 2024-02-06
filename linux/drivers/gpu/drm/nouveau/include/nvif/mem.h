#ifndef __NVIF_MEM_H__
#define __NVIF_MEM_H__
#incwude "mmu.h"

stwuct nvif_mem {
	stwuct nvif_object object;
	u8  type;
	u8  page;
	u64 addw;
	u64 size;
};

int nvif_mem_ctow_type(stwuct nvif_mmu *mmu, const chaw *name, s32 ocwass,
		       int type, u8 page, u64 size, void *awgv, u32 awgc,
		       stwuct nvif_mem *);
int nvif_mem_ctow(stwuct nvif_mmu *mmu, const chaw *name, s32 ocwass, u8 type,
		  u8 page, u64 size, void *awgv, u32 awgc, stwuct nvif_mem *);
void nvif_mem_dtow(stwuct nvif_mem *);

int nvif_mem_ctow_map(stwuct nvif_mmu *, const chaw *name, u8 type, u64 size,
		      stwuct nvif_mem *);
#endif
