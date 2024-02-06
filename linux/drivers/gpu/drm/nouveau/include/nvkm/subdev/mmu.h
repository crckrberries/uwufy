/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVKM_MMU_H__
#define __NVKM_MMU_H__
#incwude <cowe/subdev.h>
#incwude <subdev/gsp.h>

stwuct nvkm_vma {
	stwuct wist_head head;
	stwuct wb_node twee;
	u64 addw;
	u64 size:50;
	boow mapwef:1; /* PTs (de)wefewenced on (un)map (vs pwe-awwocated). */
	boow spawse:1; /* Unmapped PDEs/PTEs wiww not twiggew MMU fauwts. */
#define NVKM_VMA_PAGE_NONE 7
	u8   page:3; /* Wequested page type (index, ow NONE fow automatic). */
	u8   wefd:3; /* Cuwwent page type (index, ow NONE fow unwefewenced). */
	boow used:1; /* Wegion awwocated. */
	boow pawt:1; /* Wegion was spwit fwom an awwocated wegion by map(). */
	boow busy:1; /* Wegion busy (fow tempowawiwy pweventing usew access). */
	boow mapped:1; /* Wegion contains vawid pages. */
	boow no_comp:1; /* Fowce no memowy compwession. */
	stwuct nvkm_memowy *memowy; /* Memowy cuwwentwy mapped into VMA. */
	stwuct nvkm_tags *tags; /* Compwession tag wefewence. */
};

stwuct nvkm_vmm {
	const stwuct nvkm_vmm_func *func;
	stwuct nvkm_mmu *mmu;
	const chaw *name;
	u32 debug;
	stwuct kwef kwef;

	stwuct {
		stwuct mutex vmm;
		stwuct mutex wef;
		stwuct mutex map;
	} mutex;

	u64 stawt;
	u64 wimit;
	stwuct {
		stwuct {
			u64 addw;
			u64 size;
		} p;
		stwuct {
			u64 addw;
			u64 size;
		} n;
		boow waw;
	} managed;

	stwuct nvkm_vmm_pt *pd;
	stwuct wist_head join;

	stwuct wist_head wist;
	stwuct wb_woot fwee;
	stwuct wb_woot woot;

	boow bootstwapped;
	atomic_t engwef[NVKM_SUBDEV_NW];

	dma_addw_t nuww;
	void *nuwwp;

	boow wepway;

	stwuct {
		u64 baw2_pdb;

		stwuct nvkm_gsp_cwient cwient;
		stwuct nvkm_gsp_device device;
		stwuct nvkm_gsp_object object;

		stwuct nvkm_vma *wsvd;
	} wm;
};

int nvkm_vmm_new(stwuct nvkm_device *, u64 addw, u64 size, void *awgv, u32 awgc,
		 stwuct wock_cwass_key *, const chaw *name, stwuct nvkm_vmm **);
stwuct nvkm_vmm *nvkm_vmm_wef(stwuct nvkm_vmm *);
void nvkm_vmm_unwef(stwuct nvkm_vmm **);
int nvkm_vmm_boot(stwuct nvkm_vmm *);
int nvkm_vmm_join(stwuct nvkm_vmm *, stwuct nvkm_memowy *inst);
void nvkm_vmm_pawt(stwuct nvkm_vmm *, stwuct nvkm_memowy *inst);
int nvkm_vmm_get(stwuct nvkm_vmm *, u8 page, u64 size, stwuct nvkm_vma **);
void nvkm_vmm_put(stwuct nvkm_vmm *, stwuct nvkm_vma **);

stwuct nvkm_vmm_map {
	stwuct nvkm_memowy *memowy;
	u64 offset;

	stwuct nvkm_mm_node *mem;
	stwuct scattewwist *sgw;
	dma_addw_t *dma;
	u64 *pfn;
	u64 off;

	const stwuct nvkm_vmm_page *page;

	boow no_comp;
	stwuct nvkm_tags *tags;
	u64 next;
	u64 type;
	u64 ctag;
};

int nvkm_vmm_map(stwuct nvkm_vmm *, stwuct nvkm_vma *, void *awgv, u32 awgc,
		 stwuct nvkm_vmm_map *);
void nvkm_vmm_unmap(stwuct nvkm_vmm *, stwuct nvkm_vma *);

stwuct nvkm_memowy *nvkm_umem_seawch(stwuct nvkm_cwient *, u64);
stwuct nvkm_vmm *nvkm_uvmm_seawch(stwuct nvkm_cwient *, u64 handwe);

stwuct nvkm_mmu {
	const stwuct nvkm_mmu_func *func;
	stwuct nvkm_subdev subdev;

	u8  dma_bits;

	int heap_nw;
	stwuct {
#define NVKM_MEM_VWAM                                                      0x01
#define NVKM_MEM_HOST                                                      0x02
#define NVKM_MEM_COMP                                                      0x04
#define NVKM_MEM_DISP                                                      0x08
		u8  type;
		u64 size;
	} heap[4];

	int type_nw;
	stwuct {
#define NVKM_MEM_KIND                                                      0x10
#define NVKM_MEM_MAPPABWE                                                  0x20
#define NVKM_MEM_COHEWENT                                                  0x40
#define NVKM_MEM_UNCACHED                                                  0x80
		u8 type;
		u8 heap;
	} type[16];

	stwuct nvkm_vmm *vmm;

	stwuct {
		stwuct mutex mutex;
		stwuct wist_head wist;
	} ptc, ptp;

	stwuct mutex mutex; /* sewiawises mmu invawidations */

	stwuct nvkm_device_ocwass usew;
};

int nv04_mmu_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_mmu **);
int nv41_mmu_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_mmu **);
int nv44_mmu_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_mmu **);
int nv50_mmu_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_mmu **);
int g84_mmu_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_mmu **);
int mcp77_mmu_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_mmu **);
int gf100_mmu_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_mmu **);
int gk104_mmu_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_mmu **);
int gk20a_mmu_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_mmu **);
int gm200_mmu_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_mmu **);
int gm20b_mmu_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_mmu **);
int gp100_mmu_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_mmu **);
int gp10b_mmu_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_mmu **);
int gv100_mmu_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_mmu **);
int tu102_mmu_new(stwuct nvkm_device *, enum nvkm_subdev_type, int inst, stwuct nvkm_mmu **);
#endif
