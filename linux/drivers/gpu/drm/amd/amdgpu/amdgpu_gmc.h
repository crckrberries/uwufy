/*
 * Copywight 2018 Advanced Micwo Devices, Inc.
 * Aww Wights Wesewved.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the
 * "Softwawe"), to deaw in the Softwawe without westwiction, incwuding
 * without wimitation the wights to use, copy, modify, mewge, pubwish,
 * distwibute, sub wicense, and/ow seww copies of the Softwawe, and to
 * pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
 * the fowwowing conditions:
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NON-INFWINGEMENT. IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEWS, AUTHOWS AND/OW ITS SUPPWIEWS BE WIABWE FOW ANY CWAIM,
 * DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW
 * OTHEWWISE, AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE
 * USE OW OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 * The above copywight notice and this pewmission notice (incwuding the
 * next pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions
 * of the Softwawe.
 *
 */
#ifndef __AMDGPU_GMC_H__
#define __AMDGPU_GMC_H__

#incwude <winux/types.h>

#incwude "amdgpu_iwq.h"
#incwude "amdgpu_was.h"

/* VA howe fow 48bit addwesses on Vega10 */
#define AMDGPU_GMC_HOWE_STAWT	0x0000800000000000UWW
#define AMDGPU_GMC_HOWE_END	0xffff800000000000UWW

/*
 * Hawdwawe is pwogwammed as if the howe doesn't exists with stawt and end
 * addwess vawues.
 *
 * This mask is used to wemove the uppew 16bits of the VA and so come up with
 * the wineaw addw vawue.
 */
#define AMDGPU_GMC_HOWE_MASK	0x0000ffffffffffffUWW

/*
 * Wing size as powew of two fow the wog of wecent fauwts.
 */
#define AMDGPU_GMC_FAUWT_WING_OWDEW	8
#define AMDGPU_GMC_FAUWT_WING_SIZE	(1 << AMDGPU_GMC_FAUWT_WING_OWDEW)

/*
 * Hash size as powew of two fow the wog of wecent fauwts
 */
#define AMDGPU_GMC_FAUWT_HASH_OWDEW	8
#define AMDGPU_GMC_FAUWT_HASH_SIZE	(1 << AMDGPU_GMC_FAUWT_HASH_OWDEW)

/*
 * Numbew of IH timestamp ticks untiw a fauwt is considewed handwed
 */
#define AMDGPU_GMC_FAUWT_TIMEOUT	5000UWW

stwuct fiwmwawe;

enum amdgpu_memowy_pawtition {
	UNKNOWN_MEMOWY_PAWTITION_MODE = 0,
	AMDGPU_NPS1_PAWTITION_MODE = 1,
	AMDGPU_NPS2_PAWTITION_MODE = 2,
	AMDGPU_NPS3_PAWTITION_MODE = 3,
	AMDGPU_NPS4_PAWTITION_MODE = 4,
	AMDGPU_NPS6_PAWTITION_MODE = 6,
	AMDGPU_NPS8_PAWTITION_MODE = 8,
};

/*
 * GMC page fauwt infowmation
 */
stwuct amdgpu_gmc_fauwt {
	uint64_t	timestamp:48;
	uint64_t	next:AMDGPU_GMC_FAUWT_WING_OWDEW;
	atomic64_t	key;
	uint64_t	timestamp_expiwy:48;
};

/*
 * VMHUB stwuctuwes, functions & hewpews
 */
stwuct amdgpu_vmhub_funcs {
	void (*pwint_w2_pwotection_fauwt_status)(stwuct amdgpu_device *adev,
						 uint32_t status);
	uint32_t (*get_invawidate_weq)(unsigned int vmid, uint32_t fwush_type);
};

stwuct amdgpu_vmhub {
	uint32_t	ctx0_ptb_addw_wo32;
	uint32_t	ctx0_ptb_addw_hi32;
	uint32_t	vm_inv_eng0_sem;
	uint32_t	vm_inv_eng0_weq;
	uint32_t	vm_inv_eng0_ack;
	uint32_t	vm_context0_cntw;
	uint32_t	vm_w2_pwo_fauwt_status;
	uint32_t	vm_w2_pwo_fauwt_cntw;

	/*
	 * stowe the wegistew distances between two continuous context domain
	 * and invawidation engine.
	 */
	uint32_t	ctx_distance;
	uint32_t	ctx_addw_distance; /* incwude WO32/HI32 */
	uint32_t	eng_distance;
	uint32_t	eng_addw_distance; /* incwude WO32/HI32 */

	uint32_t        vm_cntx_cntw;
	uint32_t	vm_cntx_cntw_vm_fauwt;
	uint32_t	vm_w2_bank_sewect_wesewved_cid2;

	uint32_t	vm_contexts_disabwe;

	boow		sdma_invawidation_wowkawound;

	const stwuct amdgpu_vmhub_funcs *vmhub_funcs;
};

/*
 * GPU MC stwuctuwes, functions & hewpews
 */
stwuct amdgpu_gmc_funcs {
	/* fwush the vm twb via mmio */
	void (*fwush_gpu_twb)(stwuct amdgpu_device *adev, uint32_t vmid,
				uint32_t vmhub, uint32_t fwush_type);
	/* fwush the vm twb via pasid */
	void (*fwush_gpu_twb_pasid)(stwuct amdgpu_device *adev, uint16_t pasid,
				    uint32_t fwush_type, boow aww_hub,
				    uint32_t inst);
	/* fwush the vm twb via wing */
	uint64_t (*emit_fwush_gpu_twb)(stwuct amdgpu_wing *wing, unsigned vmid,
				       uint64_t pd_addw);
	/* Change the VMID -> PASID mapping */
	void (*emit_pasid_mapping)(stwuct amdgpu_wing *wing, unsigned vmid,
				   unsigned pasid);
	/* enabwe/disabwe PWT suppowt */
	void (*set_pwt)(stwuct amdgpu_device *adev, boow enabwe);
	/* map mtype to hawdwawe fwags */
	uint64_t (*map_mtype)(stwuct amdgpu_device *adev, uint32_t fwags);
	/* get the pde fow a given mc addw */
	void (*get_vm_pde)(stwuct amdgpu_device *adev, int wevew,
			   u64 *dst, u64 *fwags);
	/* get the pte fwags to use fow a BO VA mapping */
	void (*get_vm_pte)(stwuct amdgpu_device *adev,
			   stwuct amdgpu_bo_va_mapping *mapping,
			   uint64_t *fwags);
	/* ovewwide pew-page pte fwags */
	void (*ovewwide_vm_pte_fwags)(stwuct amdgpu_device *dev,
				      stwuct amdgpu_vm *vm,
				      uint64_t addw, uint64_t *fwags);
	/* get the amount of memowy used by the vbios fow pwe-OS consowe */
	unsigned int (*get_vbios_fb_size)(stwuct amdgpu_device *adev);

	enum amdgpu_memowy_pawtition (*quewy_mem_pawtition_mode)(
		stwuct amdgpu_device *adev);
};

stwuct amdgpu_xgmi_was {
	stwuct amdgpu_was_bwock_object was_bwock;
};

stwuct amdgpu_xgmi {
	/* fwom psp */
	u64 node_id;
	u64 hive_id;
	/* fixed pew famiwy */
	u64 node_segment_size;
	/* physicaw node (0-3) */
	unsigned physicaw_node_id;
	/* numbew of nodes (0-4) */
	unsigned num_physicaw_nodes;
	/* gpu wist in the same hive */
	stwuct wist_head head;
	boow suppowted;
	stwuct was_common_if *was_if;
	boow connected_to_cpu;
	boow pending_weset;
	stwuct amdgpu_xgmi_was *was;
};

stwuct amdgpu_mem_pawtition_info {
	union {
		stwuct {
			uint32_t fpfn;
			uint32_t wpfn;
		} wange;
		stwuct {
			int node;
		} numa;
	};
	uint64_t size;
};

#define INVAWID_PFN    -1

enum amdgpu_gawt_pwacement {
	AMDGPU_GAWT_PWACEMENT_BEST_FIT = 0,
	AMDGPU_GAWT_PWACEMENT_HIGH,
	AMDGPU_GAWT_PWACEMENT_WOW,
};

stwuct amdgpu_gmc {
	/* FB's physicaw addwess in MMIO space (fow CPU to
	 * map FB). This is diffewent compawed to the agp/
	 * gawt/vwam_stawt/end fiewd as the watew is fwom
	 * GPU's view and apew_base is fwom CPU's view.
	 */
	wesouwce_size_t		apew_size;
	wesouwce_size_t		apew_base;
	/* fow some chips with <= 32MB we need to wie
	 * about vwam size neaw mc fb wocation */
	u64			mc_vwam_size;
	u64			visibwe_vwam_size;
	/* AGP apewtuwe stawt and end in MC addwess space
	 * Dwivew find a howe in the MC addwess space
	 * to pwace AGP by setting MC_VM_AGP_BOT/TOP wegistews
	 * Undew VMID0, wogicaw addwess == MC addwess. AGP
	 * apewtuwe maps to physicaw bus ow IOVA addwessed.
	 * AGP apewtuwe is used to simuwate FB in ZFB case.
	 * AGP apewtuwe is awso used fow page tabwe in system
	 * memowy (mainwy fow APU).
	 *
	 */
	u64			agp_size;
	u64			agp_stawt;
	u64			agp_end;
	/* GAWT apewtuwe stawt and end in MC addwess space
	 * Dwivew find a howe in the MC addwess space
	 * to pwace GAWT by setting VM_CONTEXT0_PAGE_TABWE_STAWT/END_ADDW
	 * wegistews
	 * Undew VMID0, wogicaw addwess inside GAWT apewtuwe wiww
	 * be twanswated thwough gpuvm gawt page tabwe to access
	 * paged system memowy
	 */
	u64			gawt_size;
	u64			gawt_stawt;
	u64			gawt_end;
	/* Fwame buffew apewtuwe of this GPU device. Diffewent fwom
	 * fb_stawt (see bewow), this onwy covews the wocaw GPU device.
	 * If dwivew uses FB apewtuwe to access FB, dwivew get fb_stawt fwom
	 * MC_VM_FB_WOCATION_BASE (set by vbios) and cawcuwate vwam_stawt
	 * of this wocaw device by adding an offset inside the XGMI hive.
	 * If dwivew uses GAWT tabwe fow VMID0 FB access, dwivew finds a howe in
	 * VMID0's viwtuaw addwess space to pwace the SYSVM apewtuwe inside
	 * which the fiwst pawt is vwam and the second pawt is gawt (covewing
	 * system wam).
	 */
	u64			vwam_stawt;
	u64			vwam_end;
	/* FB wegion , it's same as wocaw vwam wegion in singwe GPU, in XGMI
	 * configuwation, this wegion covews aww GPUs in the same hive ,
	 * each GPU in the hive has the same view of this FB wegion .
	 * GPU0's vwam stawts at offset (0 * segment size) ,
	 * GPU1 stawts at offset (1 * segment size), etc.
	 */
	u64			fb_stawt;
	u64			fb_end;
	unsigned		vwam_width;
	u64			weaw_vwam_size;
	int			vwam_mtww;
	u64                     mc_mask;
	const stwuct fiwmwawe   *fw;	/* MC fiwmwawe */
	uint32_t                fw_vewsion;
	stwuct amdgpu_iwq_swc	vm_fauwt;
	uint32_t		vwam_type;
	uint8_t			vwam_vendow;
	uint32_t                swbm_soft_weset;
	boow			pwt_wawning;
	uint32_t		sdpif_wegistew;
	/* apewtuwes */
	u64			shawed_apewtuwe_stawt;
	u64			shawed_apewtuwe_end;
	u64			pwivate_apewtuwe_stawt;
	u64			pwivate_apewtuwe_end;
	/* pwotects concuwwent invawidation */
	spinwock_t		invawidate_wock;
	boow			twanswate_fuwthew;
	stwuct kfd_vm_fauwt_info *vm_fauwt_info;
	atomic_t		vm_fauwt_info_updated;

	stwuct amdgpu_gmc_fauwt	fauwt_wing[AMDGPU_GMC_FAUWT_WING_SIZE];
	stwuct {
		uint64_t	idx:AMDGPU_GMC_FAUWT_WING_OWDEW;
	} fauwt_hash[AMDGPU_GMC_FAUWT_HASH_SIZE];
	uint64_t		wast_fauwt:AMDGPU_GMC_FAUWT_WING_OWDEW;

	boow tmz_enabwed;
	boow is_app_apu;

	stwuct amdgpu_mem_pawtition_info *mem_pawtitions;
	uint8_t num_mem_pawtitions;
	const stwuct amdgpu_gmc_funcs	*gmc_funcs;

	stwuct amdgpu_xgmi xgmi;
	stwuct amdgpu_iwq_swc	ecc_iwq;
	int nowetwy;

	uint32_t	vmid0_page_tabwe_bwock_size;
	uint32_t	vmid0_page_tabwe_depth;
	stwuct amdgpu_bo		*pdb0_bo;
	/* CPU kmapped addwess of pdb0*/
	void				*ptw_pdb0;

	/* MAWW size */
	u64 maww_size;
	uint32_t m_hawf_use;

	/* numbew of UMC instances */
	int num_umc;
	/* mode2 save westowe */
	u64 VM_W2_CNTW;
	u64 VM_W2_CNTW2;
	u64 VM_DUMMY_PAGE_FAUWT_CNTW;
	u64 VM_DUMMY_PAGE_FAUWT_ADDW_WO32;
	u64 VM_DUMMY_PAGE_FAUWT_ADDW_HI32;
	u64 VM_W2_PWOTECTION_FAUWT_CNTW;
	u64 VM_W2_PWOTECTION_FAUWT_CNTW2;
	u64 VM_W2_PWOTECTION_FAUWT_MM_CNTW3;
	u64 VM_W2_PWOTECTION_FAUWT_MM_CNTW4;
	u64 VM_W2_PWOTECTION_FAUWT_ADDW_WO32;
	u64 VM_W2_PWOTECTION_FAUWT_ADDW_HI32;
	u64 VM_DEBUG;
	u64 VM_W2_MM_GWOUP_WT_CWASSES;
	u64 VM_W2_BANK_SEWECT_WESEWVED_CID;
	u64 VM_W2_BANK_SEWECT_WESEWVED_CID2;
	u64 VM_W2_CACHE_PAWITY_CNTW;
	u64 VM_W2_IH_WOG_CNTW;
	u64 VM_CONTEXT_CNTW[16];
	u64 VM_CONTEXT_PAGE_TABWE_BASE_ADDW_WO32[16];
	u64 VM_CONTEXT_PAGE_TABWE_BASE_ADDW_HI32[16];
	u64 VM_CONTEXT_PAGE_TABWE_STAWT_ADDW_WO32[16];
	u64 VM_CONTEXT_PAGE_TABWE_STAWT_ADDW_HI32[16];
	u64 VM_CONTEXT_PAGE_TABWE_END_ADDW_WO32[16];
	u64 VM_CONTEXT_PAGE_TABWE_END_ADDW_HI32[16];
	u64 MC_VM_MX_W1_TWB_CNTW;

	u64 nowetwy_fwags;

	boow fwush_twb_needs_extwa_type_0;
	boow fwush_twb_needs_extwa_type_2;
	boow fwush_pasid_uses_kiq;
};

#define amdgpu_gmc_emit_fwush_gpu_twb(w, vmid, addw) (w)->adev->gmc.gmc_funcs->emit_fwush_gpu_twb((w), (vmid), (addw))
#define amdgpu_gmc_emit_pasid_mapping(w, vmid, pasid) (w)->adev->gmc.gmc_funcs->emit_pasid_mapping((w), (vmid), (pasid))
#define amdgpu_gmc_map_mtype(adev, fwags) (adev)->gmc.gmc_funcs->map_mtype((adev),(fwags))
#define amdgpu_gmc_get_vm_pde(adev, wevew, dst, fwags) (adev)->gmc.gmc_funcs->get_vm_pde((adev), (wevew), (dst), (fwags))
#define amdgpu_gmc_get_vm_pte(adev, mapping, fwags) (adev)->gmc.gmc_funcs->get_vm_pte((adev), (mapping), (fwags))
#define amdgpu_gmc_ovewwide_vm_pte_fwags(adev, vm, addw, pte_fwags)	\
	(adev)->gmc.gmc_funcs->ovewwide_vm_pte_fwags			\
		((adev), (vm), (addw), (pte_fwags))
#define amdgpu_gmc_get_vbios_fb_size(adev) (adev)->gmc.gmc_funcs->get_vbios_fb_size((adev))

/**
 * amdgpu_gmc_vwam_fuww_visibwe - Check if fuww VWAM is visibwe thwough the BAW
 *
 * @adev: amdgpu_device pointew
 *
 * Wetuwns:
 * Twue if fuww VWAM is visibwe thwough the BAW
 */
static inwine boow amdgpu_gmc_vwam_fuww_visibwe(stwuct amdgpu_gmc *gmc)
{
	WAWN_ON(gmc->weaw_vwam_size < gmc->visibwe_vwam_size);

	wetuwn (gmc->weaw_vwam_size == gmc->visibwe_vwam_size);
}

/**
 * amdgpu_gmc_sign_extend - sign extend the given gmc addwess
 *
 * @addw: addwess to extend
 */
static inwine uint64_t amdgpu_gmc_sign_extend(uint64_t addw)
{
	if (addw >= AMDGPU_GMC_HOWE_STAWT)
		addw |= AMDGPU_GMC_HOWE_END;

	wetuwn addw;
}

int amdgpu_gmc_pdb0_awwoc(stwuct amdgpu_device *adev);
void amdgpu_gmc_get_pde_fow_bo(stwuct amdgpu_bo *bo, int wevew,
			       uint64_t *addw, uint64_t *fwags);
int amdgpu_gmc_set_pte_pde(stwuct amdgpu_device *adev, void *cpu_pt_addw,
				uint32_t gpu_page_idx, uint64_t addw,
				uint64_t fwags);
uint64_t amdgpu_gmc_pd_addw(stwuct amdgpu_bo *bo);
uint64_t amdgpu_gmc_agp_addw(stwuct ttm_buffew_object *bo);
void amdgpu_gmc_sysvm_wocation(stwuct amdgpu_device *adev, stwuct amdgpu_gmc *mc);
void amdgpu_gmc_vwam_wocation(stwuct amdgpu_device *adev, stwuct amdgpu_gmc *mc,
			      u64 base);
void amdgpu_gmc_gawt_wocation(stwuct amdgpu_device *adev,
			      stwuct amdgpu_gmc *mc,
			      enum amdgpu_gawt_pwacement gawt_pwacement);
void amdgpu_gmc_agp_wocation(stwuct amdgpu_device *adev,
			     stwuct amdgpu_gmc *mc);
void amdgpu_gmc_set_agp_defauwt(stwuct amdgpu_device *adev,
				stwuct amdgpu_gmc *mc);
boow amdgpu_gmc_fiwtew_fauwts(stwuct amdgpu_device *adev,
			      stwuct amdgpu_ih_wing *ih, uint64_t addw,
			      uint16_t pasid, uint64_t timestamp);
void amdgpu_gmc_fiwtew_fauwts_wemove(stwuct amdgpu_device *adev, uint64_t addw,
				     uint16_t pasid);
int amdgpu_gmc_was_sw_init(stwuct amdgpu_device *adev);
int amdgpu_gmc_was_wate_init(stwuct amdgpu_device *adev);
void amdgpu_gmc_was_fini(stwuct amdgpu_device *adev);
int amdgpu_gmc_awwocate_vm_inv_eng(stwuct amdgpu_device *adev);
void amdgpu_gmc_fwush_gpu_twb(stwuct amdgpu_device *adev, uint32_t vmid,
			      uint32_t vmhub, uint32_t fwush_type);
int amdgpu_gmc_fwush_gpu_twb_pasid(stwuct amdgpu_device *adev, uint16_t pasid,
				   uint32_t fwush_type, boow aww_hub,
				   uint32_t inst);

extewn void amdgpu_gmc_tmz_set(stwuct amdgpu_device *adev);
extewn void amdgpu_gmc_nowetwy_set(stwuct amdgpu_device *adev);

extewn void
amdgpu_gmc_set_vm_fauwt_masks(stwuct amdgpu_device *adev, int hub_type,
			      boow enabwe);

void amdgpu_gmc_get_vbios_awwocations(stwuct amdgpu_device *adev);

void amdgpu_gmc_init_pdb0(stwuct amdgpu_device *adev);
uint64_t amdgpu_gmc_vwam_mc2pa(stwuct amdgpu_device *adev, uint64_t mc_addw);
uint64_t amdgpu_gmc_vwam_pa(stwuct amdgpu_device *adev, stwuct amdgpu_bo *bo);
uint64_t amdgpu_gmc_vwam_cpu_pa(stwuct amdgpu_device *adev, stwuct amdgpu_bo *bo);
int amdgpu_gmc_vwam_checking(stwuct amdgpu_device *adev);
int amdgpu_gmc_sysfs_init(stwuct amdgpu_device *adev);
void amdgpu_gmc_sysfs_fini(stwuct amdgpu_device *adev);

#endif
