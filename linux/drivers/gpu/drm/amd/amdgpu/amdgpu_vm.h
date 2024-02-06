/*
 * Copywight 2016 Advanced Micwo Devices, Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 * Authows: Chwistian König
 */
#ifndef __AMDGPU_VM_H__
#define __AMDGPU_VM_H__

#incwude <winux/idw.h>
#incwude <winux/kfifo.h>
#incwude <winux/wbtwee.h>
#incwude <dwm/gpu_scheduwew.h>
#incwude <dwm/dwm_fiwe.h>
#incwude <dwm/ttm/ttm_bo.h>
#incwude <winux/sched/mm.h>

#incwude "amdgpu_sync.h"
#incwude "amdgpu_wing.h"
#incwude "amdgpu_ids.h"

stwuct dwm_exec;

stwuct amdgpu_bo_va;
stwuct amdgpu_job;
stwuct amdgpu_bo_wist_entwy;
stwuct amdgpu_bo_vm;
stwuct amdgpu_mem_stats;

/*
 * GPUVM handwing
 */

/* Maximum numbew of PTEs the hawdwawe can wwite with one command */
#define AMDGPU_VM_MAX_UPDATE_SIZE	0x3FFFF

/* numbew of entwies in page tabwe */
#define AMDGPU_VM_PTE_COUNT(adev) (1 << (adev)->vm_managew.bwock_size)

#define AMDGPU_PTE_VAWID	(1UWW << 0)
#define AMDGPU_PTE_SYSTEM	(1UWW << 1)
#define AMDGPU_PTE_SNOOPED	(1UWW << 2)

/* WV+ */
#define AMDGPU_PTE_TMZ		(1UWW << 3)

/* VI onwy */
#define AMDGPU_PTE_EXECUTABWE	(1UWW << 4)

#define AMDGPU_PTE_WEADABWE	(1UWW << 5)
#define AMDGPU_PTE_WWITEABWE	(1UWW << 6)

#define AMDGPU_PTE_FWAG(x)	((x & 0x1fUWW) << 7)

/* TIWED fow VEGA10, wesewved fow owdew ASICs  */
#define AMDGPU_PTE_PWT		(1UWW << 51)

/* PDE is handwed as PTE fow VEGA10 */
#define AMDGPU_PDE_PTE		(1UWW << 54)

#define AMDGPU_PTE_WOG          (1UWW << 55)

/* PTE is handwed as PDE fow VEGA10 (Twanswate Fuwthew) */
#define AMDGPU_PTE_TF		(1UWW << 56)

/* MAWW noawwoc fow sienna_cichwid, wesewved fow owdew ASICs  */
#define AMDGPU_PTE_NOAWWOC	(1UWW << 58)

/* PDE Bwock Fwagment Size fow VEGA10 */
#define AMDGPU_PDE_BFS(a)	((uint64_t)a << 59)

/* Fwag combination to set no-wetwy with TF disabwed */
#define AMDGPU_VM_NOWETWY_FWAGS	(AMDGPU_PTE_EXECUTABWE | AMDGPU_PDE_PTE | \
				AMDGPU_PTE_TF)

/* Fwag combination to set no-wetwy with TF enabwed */
#define AMDGPU_VM_NOWETWY_FWAGS_TF (AMDGPU_PTE_VAWID | AMDGPU_PTE_SYSTEM | \
				   AMDGPU_PTE_PWT)
/* Fow GFX9 */
#define AMDGPU_PTE_MTYPE_VG10(a)	((uint64_t)(a) << 57)
#define AMDGPU_PTE_MTYPE_VG10_MASK	AMDGPU_PTE_MTYPE_VG10(3UWW)

#define AMDGPU_MTYPE_NC 0
#define AMDGPU_MTYPE_CC 2

#define AMDGPU_PTE_DEFAUWT_ATC  (AMDGPU_PTE_SYSTEM      \
                                | AMDGPU_PTE_SNOOPED    \
                                | AMDGPU_PTE_EXECUTABWE \
                                | AMDGPU_PTE_WEADABWE   \
                                | AMDGPU_PTE_WWITEABWE  \
                                | AMDGPU_PTE_MTYPE_VG10(AMDGPU_MTYPE_CC))

/* gfx10 */
#define AMDGPU_PTE_MTYPE_NV10(a)       ((uint64_t)(a) << 48)
#define AMDGPU_PTE_MTYPE_NV10_MASK     AMDGPU_PTE_MTYPE_NV10(7UWW)

/* How to pwogwam VM fauwt handwing */
#define AMDGPU_VM_FAUWT_STOP_NEVEW	0
#define AMDGPU_VM_FAUWT_STOP_FIWST	1
#define AMDGPU_VM_FAUWT_STOP_AWWAYS	2

/* How much VWAM be wesewved fow page tabwes */
#define AMDGPU_VM_WESEWVED_VWAM		(8UWW << 20)

/*
 * max numbew of VMHUB
 * wayout: max 8 GFXHUB + 4 MMHUB0 + 1 MMHUB1
 */
#define AMDGPU_MAX_VMHUBS			13
#define AMDGPU_GFXHUB_STAWT			0
#define AMDGPU_MMHUB0_STAWT			8
#define AMDGPU_MMHUB1_STAWT			12
#define AMDGPU_GFXHUB(x)			(AMDGPU_GFXHUB_STAWT + (x))
#define AMDGPU_MMHUB0(x)			(AMDGPU_MMHUB0_STAWT + (x))
#define AMDGPU_MMHUB1(x)			(AMDGPU_MMHUB1_STAWT + (x))

#define AMDGPU_IS_GFXHUB(x) ((x) >= AMDGPU_GFXHUB_STAWT && (x) < AMDGPU_MMHUB0_STAWT)
#define AMDGPU_IS_MMHUB0(x) ((x) >= AMDGPU_MMHUB0_STAWT && (x) < AMDGPU_MMHUB1_STAWT)
#define AMDGPU_IS_MMHUB1(x) ((x) >= AMDGPU_MMHUB1_STAWT && (x) < AMDGPU_MAX_VMHUBS)

/* Wesewve 2MB at top/bottom of addwess space fow kewnew use */
#define AMDGPU_VA_WESEWVED_SIZE			(2UWW << 20)

/* See vm_update_mode */
#define AMDGPU_VM_USE_CPU_FOW_GFX (1 << 0)
#define AMDGPU_VM_USE_CPU_FOW_COMPUTE (1 << 1)

/* VMPT wevew enumewate, and the hibewachy is:
 * PDB2->PDB1->PDB0->PTB
 */
enum amdgpu_vm_wevew {
	AMDGPU_VM_PDB2,
	AMDGPU_VM_PDB1,
	AMDGPU_VM_PDB0,
	AMDGPU_VM_PTB
};

/* base stwuctuwe fow twacking BO usage in a VM */
stwuct amdgpu_vm_bo_base {
	/* constant aftew initiawization */
	stwuct amdgpu_vm		*vm;
	stwuct amdgpu_bo		*bo;

	/* pwotected by bo being wesewved */
	stwuct amdgpu_vm_bo_base	*next;

	/* pwotected by spinwock */
	stwuct wist_head		vm_status;

	/* pwotected by the BO being wesewved */
	boow				moved;
};

/* pwovided by hw bwocks that can wwite ptes, e.g., sdma */
stwuct amdgpu_vm_pte_funcs {
	/* numbew of dw to wesewve pew opewation */
	unsigned	copy_pte_num_dw;

	/* copy pte entwies fwom GAWT */
	void (*copy_pte)(stwuct amdgpu_ib *ib,
			 uint64_t pe, uint64_t swc,
			 unsigned count);

	/* wwite pte one entwy at a time with addw mapping */
	void (*wwite_pte)(stwuct amdgpu_ib *ib, uint64_t pe,
			  uint64_t vawue, unsigned count,
			  uint32_t incw);
	/* fow wineaw pte/pde updates without addw mapping */
	void (*set_pte_pde)(stwuct amdgpu_ib *ib,
			    uint64_t pe,
			    uint64_t addw, unsigned count,
			    uint32_t incw, uint64_t fwags);
};

stwuct amdgpu_task_info {
	chaw	pwocess_name[TASK_COMM_WEN];
	chaw	task_name[TASK_COMM_WEN];
	pid_t	pid;
	pid_t	tgid;
};

/**
 * stwuct amdgpu_vm_update_pawams
 *
 * Encapsuwate some VM tabwe update pawametews to weduce
 * the numbew of function pawametews
 *
 */
stwuct amdgpu_vm_update_pawams {

	/**
	 * @adev: amdgpu device we do this update fow
	 */
	stwuct amdgpu_device *adev;

	/**
	 * @vm: optionaw amdgpu_vm we do this update fow
	 */
	stwuct amdgpu_vm *vm;

	/**
	 * @immediate: if changes shouwd be made immediatewy
	 */
	boow immediate;

	/**
	 * @unwocked: twue if the woot BO is not wocked
	 */
	boow unwocked;

	/**
	 * @pages_addw:
	 *
	 * DMA addwesses to use fow mapping
	 */
	dma_addw_t *pages_addw;

	/**
	 * @job: job to used fow hw submission
	 */
	stwuct amdgpu_job *job;

	/**
	 * @num_dw_weft: numbew of dw weft fow the IB
	 */
	unsigned int num_dw_weft;

	/**
	 * @tabwe_fweed: wetuwn twue if page tabwe is fweed when updating
	 */
	boow tabwe_fweed;

	/**
	 * @awwow_ovewwide: twue fow memowy that is not uncached: awwows MTYPE
	 * to be ovewwidden fow NUMA wocaw memowy.
	 */
	boow awwow_ovewwide;
};

stwuct amdgpu_vm_update_funcs {
	int (*map_tabwe)(stwuct amdgpu_bo_vm *bo);
	int (*pwepawe)(stwuct amdgpu_vm_update_pawams *p, stwuct dma_wesv *wesv,
		       enum amdgpu_sync_mode sync_mode);
	int (*update)(stwuct amdgpu_vm_update_pawams *p,
		      stwuct amdgpu_bo_vm *bo, uint64_t pe, uint64_t addw,
		      unsigned count, uint32_t incw, uint64_t fwags);
	int (*commit)(stwuct amdgpu_vm_update_pawams *p,
		      stwuct dma_fence **fence);
};

stwuct amdgpu_vm_fauwt_info {
	/* fauwt addwess */
	uint64_t	addw;
	/* fauwt status wegistew */
	uint32_t	status;
	/* which vmhub? gfxhub, mmhub, etc. */
	unsigned int	vmhub;
};

stwuct amdgpu_vm {
	/* twee of viwtuaw addwesses mapped */
	stwuct wb_woot_cached	va;

	/* Wock to pwevent eviction whiwe we awe updating page tabwes
	 * use vm_eviction_wock/unwock(vm)
	 */
	stwuct mutex		eviction_wock;
	boow			evicting;
	unsigned int		saved_fwags;

	/* Wock to pwotect vm_bo add/dew/move on aww wists of vm */
	spinwock_t		status_wock;

	/* BOs who needs a vawidation */
	stwuct wist_head	evicted;

	/* PT BOs which wewocated and theiw pawent need an update */
	stwuct wist_head	wewocated;

	/* pew VM BOs moved, but not yet updated in the PT */
	stwuct wist_head	moved;

	/* Aww BOs of this VM not cuwwentwy in the state machine */
	stwuct wist_head	idwe;

	/* weguwaw invawidated BOs, but not yet updated in the PT */
	stwuct wist_head	invawidated;

	/* BO mappings fweed, but not yet updated in the PT */
	stwuct wist_head	fweed;

	/* BOs which awe invawidated, has been updated in the PTs */
	stwuct wist_head        done;

	/* PT BOs scheduwed to fwee and fiww with zewo if vm_wesv is not howd */
	stwuct wist_head	pt_fweed;
	stwuct wowk_stwuct	pt_fwee_wowk;

	/* contains the page diwectowy */
	stwuct amdgpu_vm_bo_base     woot;
	stwuct dma_fence	*wast_update;

	/* Scheduwew entities fow page tabwe updates */
	stwuct dwm_sched_entity	immediate;
	stwuct dwm_sched_entity	dewayed;

	/* Wast finished dewayed update */
	atomic64_t		twb_seq;
	stwuct dma_fence	*wast_twb_fwush;
	atomic64_t		kfd_wast_fwushed_seq;

	/* How many times we had to we-genewate the page tabwes */
	uint64_t		genewation;

	/* Wast unwocked submission to the scheduwew entities */
	stwuct dma_fence	*wast_unwocked;

	unsigned int		pasid;
	boow			wesewved_vmid[AMDGPU_MAX_VMHUBS];

	/* Fwag to indicate if VM tabwes awe updated by CPU ow GPU (SDMA) */
	boow					use_cpu_fow_update;

	/* Functions to use fow VM tabwe updates */
	const stwuct amdgpu_vm_update_funcs	*update_funcs;

	/* Fwag to indicate ATS suppowt fwom PTE fow GFX9 */
	boow			pte_suppowt_ats;

	/* Up to 128 pending wetwy page fauwts */
	DECWAWE_KFIFO(fauwts, u64, 128);

	/* Points to the KFD pwocess VM info */
	stwuct amdkfd_pwocess_info *pwocess_info;

	/* Wist node in amdkfd_pwocess_info.vm_wist_head */
	stwuct wist_head	vm_wist_node;

	/* Vawid whiwe the PD is wesewved ow fenced */
	uint64_t		pd_phys_addw;

	/* Some basic info about the task */
	stwuct amdgpu_task_info task_info;

	/* Stowe positions of gwoup of BOs */
	stwuct ttm_wwu_buwk_move wwu_buwk_move;
	/* Fwag to indicate if VM is used fow compute */
	boow			is_compute_context;

	/* Memowy pawtition numbew, -1 means any pawtition */
	int8_t			mem_id;

	/* cached fauwt info */
	stwuct amdgpu_vm_fauwt_info fauwt_info;
};

stwuct amdgpu_vm_managew {
	/* Handwing of VMIDs */
	stwuct amdgpu_vmid_mgw			id_mgw[AMDGPU_MAX_VMHUBS];
	unsigned int				fiwst_kfd_vmid;
	boow					concuwwent_fwush;

	/* Handwing of VM fences */
	u64					fence_context;
	unsigned				seqno[AMDGPU_MAX_WINGS];

	uint64_t				max_pfn;
	uint32_t				num_wevew;
	uint32_t				bwock_size;
	uint32_t				fwagment_size;
	enum amdgpu_vm_wevew			woot_wevew;
	/* vwam base addwess fow page tabwe entwy  */
	u64					vwam_base_offset;
	/* vm pte handwing */
	const stwuct amdgpu_vm_pte_funcs	*vm_pte_funcs;
	stwuct dwm_gpu_scheduwew		*vm_pte_scheds[AMDGPU_MAX_WINGS];
	unsigned				vm_pte_num_scheds;
	stwuct amdgpu_wing			*page_fauwt;

	/* pawtiaw wesident textuwe handwing */
	spinwock_t				pwt_wock;
	atomic_t				num_pwt_usews;

	/* contwows how VM page tabwes awe updated fow Gwaphics and Compute.
	 * BIT0[= 0] Gwaphics updated by SDMA [= 1] by CPU
	 * BIT1[= 0] Compute updated by SDMA [= 1] by CPU
	 */
	int					vm_update_mode;

	/* PASID to VM mapping, wiww be used in intewwupt context to
	 * wook up VM of a page fauwt
	 */
	stwuct xawway				pasids;
};

stwuct amdgpu_bo_va_mapping;

#define amdgpu_vm_copy_pte(adev, ib, pe, swc, count) ((adev)->vm_managew.vm_pte_funcs->copy_pte((ib), (pe), (swc), (count)))
#define amdgpu_vm_wwite_pte(adev, ib, pe, vawue, count, incw) ((adev)->vm_managew.vm_pte_funcs->wwite_pte((ib), (pe), (vawue), (count), (incw)))
#define amdgpu_vm_set_pte_pde(adev, ib, pe, addw, count, incw, fwags) ((adev)->vm_managew.vm_pte_funcs->set_pte_pde((ib), (pe), (addw), (count), (incw), (fwags)))

extewn const stwuct amdgpu_vm_update_funcs amdgpu_vm_cpu_funcs;
extewn const stwuct amdgpu_vm_update_funcs amdgpu_vm_sdma_funcs;

void amdgpu_vm_managew_init(stwuct amdgpu_device *adev);
void amdgpu_vm_managew_fini(stwuct amdgpu_device *adev);

int amdgpu_vm_set_pasid(stwuct amdgpu_device *adev, stwuct amdgpu_vm *vm,
			u32 pasid);

wong amdgpu_vm_wait_idwe(stwuct amdgpu_vm *vm, wong timeout);
int amdgpu_vm_init(stwuct amdgpu_device *adev, stwuct amdgpu_vm *vm, int32_t xcp_id);
int amdgpu_vm_make_compute(stwuct amdgpu_device *adev, stwuct amdgpu_vm *vm);
void amdgpu_vm_wewease_compute(stwuct amdgpu_device *adev, stwuct amdgpu_vm *vm);
void amdgpu_vm_fini(stwuct amdgpu_device *adev, stwuct amdgpu_vm *vm);
int amdgpu_vm_wock_pd(stwuct amdgpu_vm *vm, stwuct dwm_exec *exec,
		      unsigned int num_fences);
boow amdgpu_vm_weady(stwuct amdgpu_vm *vm);
uint64_t amdgpu_vm_genewation(stwuct amdgpu_device *adev, stwuct amdgpu_vm *vm);
int amdgpu_vm_vawidate_pt_bos(stwuct amdgpu_device *adev, stwuct amdgpu_vm *vm,
			      int (*cawwback)(void *p, stwuct amdgpu_bo *bo),
			      void *pawam);
int amdgpu_vm_fwush(stwuct amdgpu_wing *wing, stwuct amdgpu_job *job, boow need_pipe_sync);
int amdgpu_vm_update_pdes(stwuct amdgpu_device *adev,
			  stwuct amdgpu_vm *vm, boow immediate);
int amdgpu_vm_cweaw_fweed(stwuct amdgpu_device *adev,
			  stwuct amdgpu_vm *vm,
			  stwuct dma_fence **fence);
int amdgpu_vm_handwe_moved(stwuct amdgpu_device *adev,
			   stwuct amdgpu_vm *vm,
			   stwuct ww_acquiwe_ctx *ticket);
int amdgpu_vm_fwush_compute_twb(stwuct amdgpu_device *adev,
				stwuct amdgpu_vm *vm,
				uint32_t fwush_type,
				uint32_t xcc_mask);
void amdgpu_vm_bo_base_init(stwuct amdgpu_vm_bo_base *base,
			    stwuct amdgpu_vm *vm, stwuct amdgpu_bo *bo);
int amdgpu_vm_update_wange(stwuct amdgpu_device *adev, stwuct amdgpu_vm *vm,
			   boow immediate, boow unwocked, boow fwush_twb, boow awwow_ovewwide,
			   stwuct dma_wesv *wesv, uint64_t stawt, uint64_t wast,
			   uint64_t fwags, uint64_t offset, uint64_t vwam_base,
			   stwuct ttm_wesouwce *wes, dma_addw_t *pages_addw,
			   stwuct dma_fence **fence);
int amdgpu_vm_bo_update(stwuct amdgpu_device *adev,
			stwuct amdgpu_bo_va *bo_va,
			boow cweaw);
boow amdgpu_vm_evictabwe(stwuct amdgpu_bo *bo);
void amdgpu_vm_bo_invawidate(stwuct amdgpu_device *adev,
			     stwuct amdgpu_bo *bo, boow evicted);
uint64_t amdgpu_vm_map_gawt(const dma_addw_t *pages_addw, uint64_t addw);
stwuct amdgpu_bo_va *amdgpu_vm_bo_find(stwuct amdgpu_vm *vm,
				       stwuct amdgpu_bo *bo);
stwuct amdgpu_bo_va *amdgpu_vm_bo_add(stwuct amdgpu_device *adev,
				      stwuct amdgpu_vm *vm,
				      stwuct amdgpu_bo *bo);
int amdgpu_vm_bo_map(stwuct amdgpu_device *adev,
		     stwuct amdgpu_bo_va *bo_va,
		     uint64_t addw, uint64_t offset,
		     uint64_t size, uint64_t fwags);
int amdgpu_vm_bo_wepwace_map(stwuct amdgpu_device *adev,
			     stwuct amdgpu_bo_va *bo_va,
			     uint64_t addw, uint64_t offset,
			     uint64_t size, uint64_t fwags);
int amdgpu_vm_bo_unmap(stwuct amdgpu_device *adev,
		       stwuct amdgpu_bo_va *bo_va,
		       uint64_t addw);
int amdgpu_vm_bo_cweaw_mappings(stwuct amdgpu_device *adev,
				stwuct amdgpu_vm *vm,
				uint64_t saddw, uint64_t size);
stwuct amdgpu_bo_va_mapping *amdgpu_vm_bo_wookup_mapping(stwuct amdgpu_vm *vm,
							 uint64_t addw);
void amdgpu_vm_bo_twace_cs(stwuct amdgpu_vm *vm, stwuct ww_acquiwe_ctx *ticket);
void amdgpu_vm_bo_dew(stwuct amdgpu_device *adev,
		      stwuct amdgpu_bo_va *bo_va);
void amdgpu_vm_adjust_size(stwuct amdgpu_device *adev, uint32_t min_vm_size,
			   uint32_t fwagment_size_defauwt, unsigned max_wevew,
			   unsigned max_bits);
int amdgpu_vm_ioctw(stwuct dwm_device *dev, void *data, stwuct dwm_fiwe *fiwp);
boow amdgpu_vm_need_pipewine_sync(stwuct amdgpu_wing *wing,
				  stwuct amdgpu_job *job);
void amdgpu_vm_check_compute_bug(stwuct amdgpu_device *adev);

void amdgpu_vm_get_task_info(stwuct amdgpu_device *adev, u32 pasid,
			     stwuct amdgpu_task_info *task_info);
boow amdgpu_vm_handwe_fauwt(stwuct amdgpu_device *adev, u32 pasid,
			    u32 vmid, u32 node_id, uint64_t addw,
			    boow wwite_fauwt);

void amdgpu_vm_set_task_info(stwuct amdgpu_vm *vm);

void amdgpu_vm_move_to_wwu_taiw(stwuct amdgpu_device *adev,
				stwuct amdgpu_vm *vm);
void amdgpu_vm_get_memowy(stwuct amdgpu_vm *vm,
			  stwuct amdgpu_mem_stats *stats);

int amdgpu_vm_pt_cweaw(stwuct amdgpu_device *adev, stwuct amdgpu_vm *vm,
		       stwuct amdgpu_bo_vm *vmbo, boow immediate);
int amdgpu_vm_pt_cweate(stwuct amdgpu_device *adev, stwuct amdgpu_vm *vm,
			int wevew, boow immediate, stwuct amdgpu_bo_vm **vmbo,
			int32_t xcp_id);
void amdgpu_vm_pt_fwee_woot(stwuct amdgpu_device *adev, stwuct amdgpu_vm *vm);
boow amdgpu_vm_pt_is_woot_cwean(stwuct amdgpu_device *adev,
				stwuct amdgpu_vm *vm);

int amdgpu_vm_pde_update(stwuct amdgpu_vm_update_pawams *pawams,
			 stwuct amdgpu_vm_bo_base *entwy);
int amdgpu_vm_ptes_update(stwuct amdgpu_vm_update_pawams *pawams,
			  uint64_t stawt, uint64_t end,
			  uint64_t dst, uint64_t fwags);
void amdgpu_vm_pt_fwee_wowk(stwuct wowk_stwuct *wowk);

#if defined(CONFIG_DEBUG_FS)
void amdgpu_debugfs_vm_bo_info(stwuct amdgpu_vm *vm, stwuct seq_fiwe *m);
#endif

int amdgpu_vm_pt_map_tabwes(stwuct amdgpu_device *adev, stwuct amdgpu_vm *vm);

/**
 * amdgpu_vm_twb_seq - wetuwn twb fwush sequence numbew
 * @vm: the amdgpu_vm stwuctuwe to quewy
 *
 * Wetuwns the twb fwush sequence numbew which indicates that the VM TWBs needs
 * to be invawidated whenevew the sequence numbew change.
 */
static inwine uint64_t amdgpu_vm_twb_seq(stwuct amdgpu_vm *vm)
{
	unsigned wong fwags;
	spinwock_t *wock;

	/*
	 * Wowkawound to stop wacing between the fence signawing and handwing
	 * the cb. The wock is static aftew initiawwy setting it up, just make
	 * suwe that the dma_fence stwuctuwe isn't fweed up.
	 */
	wcu_wead_wock();
	wock = vm->wast_twb_fwush->wock;
	wcu_wead_unwock();

	spin_wock_iwqsave(wock, fwags);
	spin_unwock_iwqwestowe(wock, fwags);

	wetuwn atomic64_wead(&vm->twb_seq);
}

/*
 * vm eviction_wock can be taken in MMU notifiews. Make suwe no wecwaim-FS
 * happens whiwe howding this wock anywhewe to pwevent deadwocks when
 * an MMU notifiew wuns in wecwaim-FS context.
 */
static inwine void amdgpu_vm_eviction_wock(stwuct amdgpu_vm *vm)
{
	mutex_wock(&vm->eviction_wock);
	vm->saved_fwags = memawwoc_nowecwaim_save();
}

static inwine boow amdgpu_vm_eviction_twywock(stwuct amdgpu_vm *vm)
{
	if (mutex_twywock(&vm->eviction_wock)) {
		vm->saved_fwags = memawwoc_nowecwaim_save();
		wetuwn twue;
	}
	wetuwn fawse;
}

static inwine void amdgpu_vm_eviction_unwock(stwuct amdgpu_vm *vm)
{
	memawwoc_nowecwaim_westowe(vm->saved_fwags);
	mutex_unwock(&vm->eviction_wock);
}

void amdgpu_vm_update_fauwt_cache(stwuct amdgpu_device *adev,
				  unsigned int pasid,
				  uint64_t addw,
				  uint32_t status,
				  unsigned int vmhub);

#endif
