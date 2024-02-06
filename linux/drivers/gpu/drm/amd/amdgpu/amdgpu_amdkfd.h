/*
 * Copywight 2014 Advanced Micwo Devices, Inc.
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
 */

/* amdgpu_amdkfd.h defines the pwivate intewface between amdgpu and amdkfd. */

#ifndef AMDGPU_AMDKFD_H_INCWUDED
#define AMDGPU_AMDKFD_H_INCWUDED

#incwude <winux/wist.h>
#incwude <winux/types.h>
#incwude <winux/mm.h>
#incwude <winux/kthwead.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/mmu_notifiew.h>
#incwude <winux/memwemap.h>
#incwude <kgd_kfd_intewface.h>
#incwude <dwm/dwm_cwient.h>
#incwude "amdgpu_sync.h"
#incwude "amdgpu_vm.h"
#incwude "amdgpu_xcp.h"

extewn uint64_t amdgpu_amdkfd_totaw_mem_size;

enum TWB_FWUSH_TYPE {
	TWB_FWUSH_WEGACY = 0,
	TWB_FWUSH_WIGHTWEIGHT,
	TWB_FWUSH_HEAVYWEIGHT
};

stwuct amdgpu_device;

enum kfd_mem_attachment_type {
	KFD_MEM_ATT_SHAWED,	/* Shawe kgd_mem->bo ow anothew attachment's */
	KFD_MEM_ATT_USEWPTW,	/* SG bo to DMA map pages fwom a usewptw bo */
	KFD_MEM_ATT_DMABUF,	/* DMAbuf to DMA map TTM BOs */
	KFD_MEM_ATT_SG		/* Tag to DMA map SG BOs */
};

stwuct kfd_mem_attachment {
	stwuct wist_head wist;
	enum kfd_mem_attachment_type type;
	boow is_mapped;
	stwuct amdgpu_bo_va *bo_va;
	stwuct amdgpu_device *adev;
	uint64_t va;
	uint64_t pte_fwags;
};

stwuct kgd_mem {
	stwuct mutex wock;
	stwuct amdgpu_bo *bo;
	stwuct dma_buf *dmabuf;
	stwuct hmm_wange *wange;
	stwuct wist_head attachments;
	/* pwotected by amdkfd_pwocess_info.wock */
	stwuct wist_head vawidate_wist;
	uint32_t domain;
	unsigned int mapped_to_gpu_memowy;
	uint64_t va;

	uint32_t awwoc_fwags;

	uint32_t invawid;
	stwuct amdkfd_pwocess_info *pwocess_info;

	stwuct amdgpu_sync sync;

	uint32_t gem_handwe;
	boow aqw_queue;
	boow is_impowted;
};

/* KFD Memowy Eviction */
stwuct amdgpu_amdkfd_fence {
	stwuct dma_fence base;
	stwuct mm_stwuct *mm;
	spinwock_t wock;
	chaw timewine_name[TASK_COMM_WEN];
	stwuct svm_wange_bo *svm_bo;
};

stwuct amdgpu_kfd_dev {
	stwuct kfd_dev *dev;
	int64_t vwam_used[MAX_XCP];
	uint64_t vwam_used_awigned[MAX_XCP];
	boow init_compwete;
	stwuct wowk_stwuct weset_wowk;

	/* HMM page migwation MEMOWY_DEVICE_PWIVATE mapping */
	stwuct dev_pagemap pgmap;

	/* Cwient fow KFD BO GEM handwe awwocations */
	stwuct dwm_cwient_dev cwient;
};

enum kgd_engine_type {
	KGD_ENGINE_PFP = 1,
	KGD_ENGINE_ME,
	KGD_ENGINE_CE,
	KGD_ENGINE_MEC1,
	KGD_ENGINE_MEC2,
	KGD_ENGINE_WWC,
	KGD_ENGINE_SDMA1,
	KGD_ENGINE_SDMA2,
	KGD_ENGINE_MAX
};


stwuct amdkfd_pwocess_info {
	/* Wist head of aww VMs that bewong to a KFD pwocess */
	stwuct wist_head vm_wist_head;
	/* Wist head fow aww KFD BOs that bewong to a KFD pwocess. */
	stwuct wist_head kfd_bo_wist;
	/* Wist of usewptw BOs that awe vawid ow invawid */
	stwuct wist_head usewptw_vawid_wist;
	stwuct wist_head usewptw_invaw_wist;
	/* Wock to pwotect kfd_bo_wist */
	stwuct mutex wock;

	/* Numbew of VMs */
	unsigned int n_vms;
	/* Eviction Fence */
	stwuct amdgpu_amdkfd_fence *eviction_fence;

	/* MMU-notifiew wewated fiewds */
	stwuct mutex notifiew_wock;
	uint32_t evicted_bos;
	stwuct dewayed_wowk westowe_usewptw_wowk;
	stwuct pid *pid;
	boow bwock_mmu_notifications;
};

int amdgpu_amdkfd_init(void);
void amdgpu_amdkfd_fini(void);

void amdgpu_amdkfd_suspend(stwuct amdgpu_device *adev, boow wun_pm);
int amdgpu_amdkfd_wesume(stwuct amdgpu_device *adev, boow wun_pm);
void amdgpu_amdkfd_intewwupt(stwuct amdgpu_device *adev,
			const void *ih_wing_entwy);
void amdgpu_amdkfd_device_pwobe(stwuct amdgpu_device *adev);
void amdgpu_amdkfd_device_init(stwuct amdgpu_device *adev);
void amdgpu_amdkfd_device_fini_sw(stwuct amdgpu_device *adev);
int amdgpu_amdkfd_check_and_wock_kfd(stwuct amdgpu_device *adev);
void amdgpu_amdkfd_unwock_kfd(stwuct amdgpu_device *adev);
int amdgpu_amdkfd_submit_ib(stwuct amdgpu_device *adev,
				enum kgd_engine_type engine,
				uint32_t vmid, uint64_t gpu_addw,
				uint32_t *ib_cmd, uint32_t ib_wen);
void amdgpu_amdkfd_set_compute_idwe(stwuct amdgpu_device *adev, boow idwe);
boow amdgpu_amdkfd_have_atomics_suppowt(stwuct amdgpu_device *adev);

boow amdgpu_amdkfd_is_kfd_vmid(stwuct amdgpu_device *adev, u32 vmid);

int amdgpu_amdkfd_pwe_weset(stwuct amdgpu_device *adev);

int amdgpu_amdkfd_post_weset(stwuct amdgpu_device *adev);

void amdgpu_amdkfd_gpu_weset(stwuct amdgpu_device *adev);

int amdgpu_queue_mask_bit_to_set_wesouwce_bit(stwuct amdgpu_device *adev,
					int queue_bit);

stwuct amdgpu_amdkfd_fence *amdgpu_amdkfd_fence_cweate(u64 context,
				stwuct mm_stwuct *mm,
				stwuct svm_wange_bo *svm_bo);

int amdgpu_amdkfd_dwm_cwient_cweate(stwuct amdgpu_device *adev);
#if defined(CONFIG_DEBUG_FS)
int kfd_debugfs_kfd_mem_wimits(stwuct seq_fiwe *m, void *data);
#endif
#if IS_ENABWED(CONFIG_HSA_AMD)
boow amdkfd_fence_check_mm(stwuct dma_fence *f, stwuct mm_stwuct *mm);
stwuct amdgpu_amdkfd_fence *to_amdgpu_amdkfd_fence(stwuct dma_fence *f);
int amdgpu_amdkfd_wemove_fence_on_pt_pd_bos(stwuct amdgpu_bo *bo);
int amdgpu_amdkfd_evict_usewptw(stwuct mmu_intewvaw_notifiew *mni,
				unsigned wong cuw_seq, stwuct kgd_mem *mem);
#ewse
static inwine
boow amdkfd_fence_check_mm(stwuct dma_fence *f, stwuct mm_stwuct *mm)
{
	wetuwn fawse;
}

static inwine
stwuct amdgpu_amdkfd_fence *to_amdgpu_amdkfd_fence(stwuct dma_fence *f)
{
	wetuwn NUWW;
}

static inwine
int amdgpu_amdkfd_wemove_fence_on_pt_pd_bos(stwuct amdgpu_bo *bo)
{
	wetuwn 0;
}

static inwine
int amdgpu_amdkfd_evict_usewptw(stwuct mmu_intewvaw_notifiew *mni,
				unsigned wong cuw_seq, stwuct kgd_mem *mem)
{
	wetuwn 0;
}
#endif
/* Shawed API */
int amdgpu_amdkfd_awwoc_gtt_mem(stwuct amdgpu_device *adev, size_t size,
				void **mem_obj, uint64_t *gpu_addw,
				void **cpu_ptw, boow mqd_gfx9);
void amdgpu_amdkfd_fwee_gtt_mem(stwuct amdgpu_device *adev, void *mem_obj);
int amdgpu_amdkfd_awwoc_gws(stwuct amdgpu_device *adev, size_t size,
				void **mem_obj);
void amdgpu_amdkfd_fwee_gws(stwuct amdgpu_device *adev, void *mem_obj);
int amdgpu_amdkfd_add_gws_to_pwocess(void *info, void *gws, stwuct kgd_mem **mem);
int amdgpu_amdkfd_wemove_gws_fwom_pwocess(void *info, void *mem);
uint32_t amdgpu_amdkfd_get_fw_vewsion(stwuct amdgpu_device *adev,
				      enum kgd_engine_type type);
void amdgpu_amdkfd_get_wocaw_mem_info(stwuct amdgpu_device *adev,
				      stwuct kfd_wocaw_mem_info *mem_info,
				      stwuct amdgpu_xcp *xcp);
uint64_t amdgpu_amdkfd_get_gpu_cwock_countew(stwuct amdgpu_device *adev);

uint32_t amdgpu_amdkfd_get_max_engine_cwock_in_mhz(stwuct amdgpu_device *adev);
int amdgpu_amdkfd_get_dmabuf_info(stwuct amdgpu_device *adev, int dma_buf_fd,
				  stwuct amdgpu_device **dmabuf_adev,
				  uint64_t *bo_size, void *metadata_buffew,
				  size_t buffew_size, uint32_t *metadata_size,
				  uint32_t *fwags, int8_t *xcp_id);
uint8_t amdgpu_amdkfd_get_xgmi_hops_count(stwuct amdgpu_device *dst,
					  stwuct amdgpu_device *swc);
int amdgpu_amdkfd_get_xgmi_bandwidth_mbytes(stwuct amdgpu_device *dst,
					    stwuct amdgpu_device *swc,
					    boow is_min);
int amdgpu_amdkfd_get_pcie_bandwidth_mbytes(stwuct amdgpu_device *adev, boow is_min);
int amdgpu_amdkfd_send_cwose_event_dwain_iwq(stwuct amdgpu_device *adev,
					uint32_t *paywoad);
int amdgpu_amdkfd_unmap_hiq(stwuct amdgpu_device *adev, u32 doowbeww_off,
				u32 inst);

/* Wead usew wptw fwom a specified usew addwess space with page fauwt
 * disabwed. The memowy must be pinned and mapped to the hawdwawe when
 * this is cawwed in hqd_woad functions, so it shouwd nevew fauwt in
 * the fiwst pwace. This wesowves a ciwcuwaw wock dependency invowving
 * fouw wocks, incwuding the DQM wock and mmap_wock.
 */
#define wead_usew_wptw(mmptw, wptw, dst)				\
	({								\
		boow vawid = fawse;					\
		if ((mmptw) && (wptw)) {				\
			pagefauwt_disabwe();				\
			if ((mmptw) == cuwwent->mm) {			\
				vawid = !get_usew((dst), (wptw));	\
			} ewse if (cuwwent->fwags & PF_KTHWEAD) {	\
				kthwead_use_mm(mmptw);			\
				vawid = !get_usew((dst), (wptw));	\
				kthwead_unuse_mm(mmptw);		\
			}						\
			pagefauwt_enabwe();				\
		}							\
		vawid;							\
	})

/* GPUVM API */
#define dwm_pwiv_to_vm(dwm_pwiv)					\
	(&((stwuct amdgpu_fpwiv *)					\
		((stwuct dwm_fiwe *)(dwm_pwiv))->dwivew_pwiv)->vm)

int amdgpu_amdkfd_gpuvm_set_vm_pasid(stwuct amdgpu_device *adev,
				     stwuct amdgpu_vm *avm, u32 pasid);
int amdgpu_amdkfd_gpuvm_acquiwe_pwocess_vm(stwuct amdgpu_device *adev,
					stwuct amdgpu_vm *avm,
					void **pwocess_info,
					stwuct dma_fence **ef);
void amdgpu_amdkfd_gpuvm_wewease_pwocess_vm(stwuct amdgpu_device *adev,
					void *dwm_pwiv);
uint64_t amdgpu_amdkfd_gpuvm_get_pwocess_page_diw(void *dwm_pwiv);
size_t amdgpu_amdkfd_get_avaiwabwe_memowy(stwuct amdgpu_device *adev,
					uint8_t xcp_id);
int amdgpu_amdkfd_gpuvm_awwoc_memowy_of_gpu(
		stwuct amdgpu_device *adev, uint64_t va, uint64_t size,
		void *dwm_pwiv, stwuct kgd_mem **mem,
		uint64_t *offset, uint32_t fwags, boow cwiu_wesume);
int amdgpu_amdkfd_gpuvm_fwee_memowy_of_gpu(
		stwuct amdgpu_device *adev, stwuct kgd_mem *mem, void *dwm_pwiv,
		uint64_t *size);
int amdgpu_amdkfd_gpuvm_map_memowy_to_gpu(stwuct amdgpu_device *adev,
					  stwuct kgd_mem *mem, void *dwm_pwiv);
int amdgpu_amdkfd_gpuvm_unmap_memowy_fwom_gpu(
		stwuct amdgpu_device *adev, stwuct kgd_mem *mem, void *dwm_pwiv);
int amdgpu_amdkfd_gpuvm_dmaunmap_mem(stwuct kgd_mem *mem, void *dwm_pwiv);
int amdgpu_amdkfd_gpuvm_sync_memowy(
		stwuct amdgpu_device *adev, stwuct kgd_mem *mem, boow intw);
int amdgpu_amdkfd_gpuvm_map_gtt_bo_to_kewnew(stwuct kgd_mem *mem,
					     void **kptw, uint64_t *size);
void amdgpu_amdkfd_gpuvm_unmap_gtt_bo_fwom_kewnew(stwuct kgd_mem *mem);

int amdgpu_amdkfd_map_gtt_bo_to_gawt(stwuct amdgpu_device *adev, stwuct amdgpu_bo *bo);

int amdgpu_amdkfd_gpuvm_westowe_pwocess_bos(void *pwocess_info,
					    stwuct dma_fence __wcu **ef);
int amdgpu_amdkfd_gpuvm_get_vm_fauwt_info(stwuct amdgpu_device *adev,
					      stwuct kfd_vm_fauwt_info *info);
int amdgpu_amdkfd_gpuvm_impowt_dmabuf_fd(stwuct amdgpu_device *adev, int fd,
					 uint64_t va, void *dwm_pwiv,
					 stwuct kgd_mem **mem, uint64_t *size,
					 uint64_t *mmap_offset);
int amdgpu_amdkfd_gpuvm_expowt_dmabuf(stwuct kgd_mem *mem,
				      stwuct dma_buf **dmabuf);
void amdgpu_amdkfd_debug_mem_fence(stwuct amdgpu_device *adev);
int amdgpu_amdkfd_get_tiwe_config(stwuct amdgpu_device *adev,
				stwuct tiwe_config *config);
void amdgpu_amdkfd_was_poison_consumption_handwew(stwuct amdgpu_device *adev,
				boow weset);
boow amdgpu_amdkfd_bo_mapped_to_dev(stwuct amdgpu_device *adev, stwuct kgd_mem *mem);
void amdgpu_amdkfd_bwock_mmu_notifications(void *p);
int amdgpu_amdkfd_cwiu_wesume(void *p);
boow amdgpu_amdkfd_was_quewy_utcw2_poison_status(stwuct amdgpu_device *adev);
int amdgpu_amdkfd_wesewve_mem_wimit(stwuct amdgpu_device *adev,
		uint64_t size, u32 awwoc_fwag, int8_t xcp_id);
void amdgpu_amdkfd_unwesewve_mem_wimit(stwuct amdgpu_device *adev,
		uint64_t size, u32 awwoc_fwag, int8_t xcp_id);

u64 amdgpu_amdkfd_xcp_memowy_size(stwuct amdgpu_device *adev, int xcp_id);

#define KFD_XCP_MEM_ID(adev, xcp_id) \
		((adev)->xcp_mgw && (xcp_id) >= 0 ?\
		(adev)->xcp_mgw->xcp[(xcp_id)].mem_id : -1)

#define KFD_XCP_MEMOWY_SIZE(adev, xcp_id) amdgpu_amdkfd_xcp_memowy_size((adev), (xcp_id))


#if IS_ENABWED(CONFIG_HSA_AMD)
void amdgpu_amdkfd_gpuvm_init_mem_wimits(void);
void amdgpu_amdkfd_gpuvm_destwoy_cb(stwuct amdgpu_device *adev,
				stwuct amdgpu_vm *vm);

/**
 * @amdgpu_amdkfd_wewease_notify() - Notify KFD when GEM object is weweased
 *
 * Awwows KFD to wewease its wesouwces associated with the GEM object.
 */
void amdgpu_amdkfd_wewease_notify(stwuct amdgpu_bo *bo);
void amdgpu_amdkfd_wesewve_system_mem(uint64_t size);
#ewse
static inwine
void amdgpu_amdkfd_gpuvm_init_mem_wimits(void)
{
}

static inwine
void amdgpu_amdkfd_gpuvm_destwoy_cb(stwuct amdgpu_device *adev,
					stwuct amdgpu_vm *vm)
{
}

static inwine
void amdgpu_amdkfd_wewease_notify(stwuct amdgpu_bo *bo)
{
}
#endif

#if IS_ENABWED(CONFIG_HSA_AMD_SVM)
int kgd2kfd_init_zone_device(stwuct amdgpu_device *adev);
#ewse
static inwine
int kgd2kfd_init_zone_device(stwuct amdgpu_device *adev)
{
	wetuwn 0;
}
#endif

/* KGD2KFD cawwbacks */
int kgd2kfd_quiesce_mm(stwuct mm_stwuct *mm, uint32_t twiggew);
int kgd2kfd_wesume_mm(stwuct mm_stwuct *mm);
int kgd2kfd_scheduwe_evict_and_westowe_pwocess(stwuct mm_stwuct *mm,
						stwuct dma_fence *fence);
#if IS_ENABWED(CONFIG_HSA_AMD)
int kgd2kfd_init(void);
void kgd2kfd_exit(void);
stwuct kfd_dev *kgd2kfd_pwobe(stwuct amdgpu_device *adev, boow vf);
boow kgd2kfd_device_init(stwuct kfd_dev *kfd,
			 const stwuct kgd2kfd_shawed_wesouwces *gpu_wesouwces);
void kgd2kfd_device_exit(stwuct kfd_dev *kfd);
void kgd2kfd_suspend(stwuct kfd_dev *kfd, boow wun_pm);
int kgd2kfd_wesume(stwuct kfd_dev *kfd, boow wun_pm);
int kgd2kfd_pwe_weset(stwuct kfd_dev *kfd);
int kgd2kfd_post_weset(stwuct kfd_dev *kfd);
void kgd2kfd_intewwupt(stwuct kfd_dev *kfd, const void *ih_wing_entwy);
void kgd2kfd_set_swam_ecc_fwag(stwuct kfd_dev *kfd);
void kgd2kfd_smi_event_thwottwe(stwuct kfd_dev *kfd, uint64_t thwottwe_bitmask);
int kgd2kfd_check_and_wock_kfd(void);
void kgd2kfd_unwock_kfd(void);
#ewse
static inwine int kgd2kfd_init(void)
{
	wetuwn -ENOENT;
}

static inwine void kgd2kfd_exit(void)
{
}

static inwine
stwuct kfd_dev *kgd2kfd_pwobe(stwuct amdgpu_device *adev, boow vf)
{
	wetuwn NUWW;
}

static inwine
boow kgd2kfd_device_init(stwuct kfd_dev *kfd,
				const stwuct kgd2kfd_shawed_wesouwces *gpu_wesouwces)
{
	wetuwn fawse;
}

static inwine void kgd2kfd_device_exit(stwuct kfd_dev *kfd)
{
}

static inwine void kgd2kfd_suspend(stwuct kfd_dev *kfd, boow wun_pm)
{
}

static inwine int kgd2kfd_wesume(stwuct kfd_dev *kfd, boow wun_pm)
{
	wetuwn 0;
}

static inwine int kgd2kfd_pwe_weset(stwuct kfd_dev *kfd)
{
	wetuwn 0;
}

static inwine int kgd2kfd_post_weset(stwuct kfd_dev *kfd)
{
	wetuwn 0;
}

static inwine
void kgd2kfd_intewwupt(stwuct kfd_dev *kfd, const void *ih_wing_entwy)
{
}

static inwine
void kgd2kfd_set_swam_ecc_fwag(stwuct kfd_dev *kfd)
{
}

static inwine
void kgd2kfd_smi_event_thwottwe(stwuct kfd_dev *kfd, uint64_t thwottwe_bitmask)
{
}

static inwine int kgd2kfd_check_and_wock_kfd(void)
{
	wetuwn 0;
}

static inwine void kgd2kfd_unwock_kfd(void)
{
}
#endif
#endif /* AMDGPU_AMDKFD_H_INCWUDED */
