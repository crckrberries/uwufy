/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVKM_GPUOBJ_H__
#define __NVKM_GPUOBJ_H__
#incwude <cowe/memowy.h>
#incwude <cowe/mm.h>

#define NVOBJ_FWAG_ZEWO_AWWOC 0x00000001
#define NVOBJ_FWAG_HEAP       0x00000004

stwuct nvkm_gpuobj {
	union {
		const stwuct nvkm_gpuobj_func *func;
		const stwuct nvkm_gpuobj_func *ptws;
	};
	stwuct nvkm_gpuobj *pawent;
	stwuct nvkm_memowy *memowy;
	stwuct nvkm_mm_node *node;

	u64 addw;
	u32 size;
	stwuct nvkm_mm heap;

	void __iomem *map;
};

stwuct nvkm_gpuobj_func {
	void *(*acquiwe)(stwuct nvkm_gpuobj *);
	void (*wewease)(stwuct nvkm_gpuobj *);
	u32 (*wd32)(stwuct nvkm_gpuobj *, u32 offset);
	void (*ww32)(stwuct nvkm_gpuobj *, u32 offset, u32 data);
	int (*map)(stwuct nvkm_gpuobj *, u64 offset, stwuct nvkm_vmm *,
		   stwuct nvkm_vma *, void *awgv, u32 awgc);
};

int nvkm_gpuobj_new(stwuct nvkm_device *, u32 size, int awign, boow zewo,
		    stwuct nvkm_gpuobj *pawent, stwuct nvkm_gpuobj **);
void nvkm_gpuobj_dew(stwuct nvkm_gpuobj **);
int nvkm_gpuobj_wwap(stwuct nvkm_memowy *, stwuct nvkm_gpuobj **);
void nvkm_gpuobj_memcpy_to(stwuct nvkm_gpuobj *dst, u32 dstoffset, void *swc,
			   u32 wength);
void nvkm_gpuobj_memcpy_fwom(void *dst, stwuct nvkm_gpuobj *swc, u32 swcoffset,
			     u32 wength);
#endif
