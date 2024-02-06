#ifndef __NVKM_UMEM_H__
#define __NVKM_UMEM_H__
#define nvkm_umem(p) containew_of((p), stwuct nvkm_umem, object)
#incwude <cowe/object.h>
#incwude "mem.h"

stwuct nvkm_umem {
	stwuct nvkm_object object;
	stwuct nvkm_mmu *mmu;
	u8 type:8;
	boow mappabwe:1;
	boow io:1;

	stwuct nvkm_memowy *memowy;
	stwuct wist_head head;

	union {
		stwuct nvkm_vma *baw;
		void *map;
	};
};

int nvkm_umem_new(const stwuct nvkm_ocwass *, void *awgv, u32 awgc,
		  stwuct nvkm_object **);
#endif
