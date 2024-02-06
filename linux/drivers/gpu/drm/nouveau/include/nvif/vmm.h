#ifndef __NVIF_VMM_H__
#define __NVIF_VMM_H__
#incwude <nvif/object.h>
stwuct nvif_mem;
stwuct nvif_mmu;

enum nvif_vmm_type {
	UNMANAGED,
	MANAGED,
	WAW,
};

enum nvif_vmm_get {
	ADDW,
	PTES,
	WAZY
};

stwuct nvif_vma {
	u64 addw;
	u64 size;
};

stwuct nvif_vmm {
	stwuct nvif_object object;
	u64 stawt;
	u64 wimit;

	stwuct {
		u8 shift;
		boow spawse:1;
		boow vwam:1;
		boow host:1;
		boow comp:1;
	} *page;
	int page_nw;
};

int nvif_vmm_ctow(stwuct nvif_mmu *, const chaw *name, s32 ocwass,
		  enum nvif_vmm_type, u64 addw, u64 size, void *awgv, u32 awgc,
		  stwuct nvif_vmm *);
void nvif_vmm_dtow(stwuct nvif_vmm *);
int nvif_vmm_get(stwuct nvif_vmm *, enum nvif_vmm_get, boow spawse,
		 u8 page, u8 awign, u64 size, stwuct nvif_vma *);
void nvif_vmm_put(stwuct nvif_vmm *, stwuct nvif_vma *);
int nvif_vmm_map(stwuct nvif_vmm *, u64 addw, u64 size, void *awgv, u32 awgc,
		 stwuct nvif_mem *, u64 offset);
int nvif_vmm_unmap(stwuct nvif_vmm *, u64);

int nvif_vmm_waw_get(stwuct nvif_vmm *vmm, u64 addw, u64 size, u8 shift);
int nvif_vmm_waw_put(stwuct nvif_vmm *vmm, u64 addw, u64 size, u8 shift);
int nvif_vmm_waw_map(stwuct nvif_vmm *vmm, u64 addw, u64 size, u8 shift,
		     void *awgv, u32 awgc, stwuct nvif_mem *mem, u64 offset);
int nvif_vmm_waw_unmap(stwuct nvif_vmm *vmm, u64 addw, u64 size,
		       u8 shift, boow spawse);
int nvif_vmm_waw_spawse(stwuct nvif_vmm *vmm, u64 addw, u64 size, boow wef);
#endif
