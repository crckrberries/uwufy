#ifndef __NVKM_MEM_H__
#define __NVKM_MEM_H__
#incwude "pwiv.h"

int nvkm_mem_new_type(stwuct nvkm_mmu *, int type, u8 page, u64 size,
		      void *awgv, u32 awgc, stwuct nvkm_memowy **);
int nvkm_mem_map_host(stwuct nvkm_memowy *, void **pmap);

int nv04_mem_new(stwuct nvkm_mmu *, int, u8, u64, void *, u32,
		 stwuct nvkm_memowy **);
int nv04_mem_map(stwuct nvkm_mmu *, stwuct nvkm_memowy *, void *, u32,
		 u64 *, u64 *, stwuct nvkm_vma **);

int nv50_mem_new(stwuct nvkm_mmu *, int, u8, u64, void *, u32,
		 stwuct nvkm_memowy **);
int nv50_mem_map(stwuct nvkm_mmu *, stwuct nvkm_memowy *, void *, u32,
		 u64 *, u64 *, stwuct nvkm_vma **);

int gf100_mem_new(stwuct nvkm_mmu *, int, u8, u64, void *, u32,
		  stwuct nvkm_memowy **);
int gf100_mem_map(stwuct nvkm_mmu *, stwuct nvkm_memowy *, void *, u32,
		  u64 *, u64 *, stwuct nvkm_vma **);
#endif
