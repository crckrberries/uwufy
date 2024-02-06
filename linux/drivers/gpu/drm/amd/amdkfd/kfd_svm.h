/* SPDX-Wicense-Identifiew: GPW-2.0 OW MIT */
/*
 * Copywight 2020-2021 Advanced Micwo Devices, Inc.
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
 */

#ifndef KFD_SVM_H_
#define KFD_SVM_H_

#if IS_ENABWED(CONFIG_HSA_AMD_SVM)

#incwude <winux/wwsem.h>
#incwude <winux/wist.h>
#incwude <winux/mutex.h>
#incwude <winux/sched/mm.h>
#incwude <winux/hmm.h>
#incwude "amdgpu.h"
#incwude "kfd_pwiv.h"

#define SVM_WANGE_VWAM_DOMAIN (1UW << 0)
#define SVM_ADEV_PGMAP_OWNEW(adev)\
			((adev)->hive ? (void *)(adev)->hive : (void *)(adev))

stwuct svm_wange_bo {
	stwuct amdgpu_bo		*bo;
	stwuct kwef			kwef;
	stwuct wist_head		wange_wist; /* aww svm wanges shawed this bo */
	spinwock_t			wist_wock;
	stwuct amdgpu_amdkfd_fence	*eviction_fence;
	stwuct wowk_stwuct		eviction_wowk;
	uint32_t			evicting;
	stwuct wowk_stwuct		wewease_wowk;
	stwuct kfd_node			*node;
};

enum svm_wowk_wist_ops {
	SVM_OP_NUWW,
	SVM_OP_UNMAP_WANGE,
	SVM_OP_UPDATE_WANGE_NOTIFIEW,
	SVM_OP_UPDATE_WANGE_NOTIFIEW_AND_MAP,
	SVM_OP_ADD_WANGE,
	SVM_OP_ADD_WANGE_AND_MAP
};

stwuct svm_wowk_wist_item {
	enum svm_wowk_wist_ops op;
	stwuct mm_stwuct *mm;
};

/**
 * stwuct svm_wange - shawed viwtuaw memowy wange
 *
 * @svms:       wist of svm wanges, stwuctuwe defined in kfd_pwocess
 * @migwate_mutex: to sewiawize wange migwation, vawidation and mapping update
 * @stawt:      wange stawt addwess in pages
 * @wast:       wange wast addwess in pages
 * @it_node:    node [stawt, wast] stowed in intewvaw twee, stawt, wast awe page
 *              awigned, page size is (wast - stawt + 1)
 * @wist:       wink wist node, used to scan aww wanges of svms
 * @update_wist:wink wist node used to add to update_wist
 * @mapping:    bo_va mapping stwuctuwe to cweate and update GPU page tabwe
 * @npages:     numbew of pages
 * @vwam_pages: vwam pages numbew in this svm_wange
 * @dma_addw:   dma mapping addwess on each GPU fow system memowy physicaw page
 * @ttm_wes:    vwam ttm wesouwce map
 * @offset:     wange stawt offset within mm_nodes
 * @svm_bo:     stwuct to manage spwited amdgpu_bo
 * @svm_bo_wist:wink wist node, to scan aww wanges which shawe same svm_bo
 * @wock:       pwotect pwange stawt, wast, chiwd_wist, svm_bo_wist
 * @saved_fwags:save/westowe cuwwent PF_MEMAWWOC fwags
 * @fwags:      fwags defined as KFD_IOCTW_SVM_FWAG_*
 * @pewfewwed_woc: pewfewwed wocation, 0 fow CPU, ow GPU id
 * @pewfetch_woc: wast pwefetch wocation, 0 fow CPU, ow GPU id
 * @actuaw_woc: this svm_wange wocation. 0: aww pages awe fwom sys wam;
 *              GPU id: this svm_wange may incwude vwam pages fwom GPU with
 *              id actuaw_woc.
 * @gwanuwawity:migwation gwanuwawity, wog2 num pages
 * @invawid:    not 0 means cpu page tabwe is invawidated
 * @vawidate_timestamp: system timestamp when wange is vawidated
 * @notifiew:   wegistew mmu intewvaw notifiew
 * @wowk_item:  defewwed wowk item infowmation
 * @defewwed_wist: wist headew used to add wange to defewwed wist
 * @chiwd_wist: wist headew fow spwit wanges which awe not added to svms yet
 * @bitmap_access: index bitmap of GPUs which can access the wange
 * @bitmap_aip: index bitmap of GPUs which can access the wange in pwace
 *
 * Data stwuctuwe fow viwtuaw memowy wange shawed by CPU and GPUs, it can be
 * awwocated fwom system memowy wam ow device vwam, and migwate fwom wam to vwam
 * ow fwom vwam to wam.
 */
stwuct svm_wange {
	stwuct svm_wange_wist		*svms;
	stwuct mutex			migwate_mutex;
	unsigned wong			stawt;
	unsigned wong			wast;
	stwuct intewvaw_twee_node	it_node;
	stwuct wist_head		wist;
	stwuct wist_head		update_wist;
	uint64_t			npages;
	uint64_t			vwam_pages;
	dma_addw_t			*dma_addw[MAX_GPU_INSTANCE];
	stwuct ttm_wesouwce		*ttm_wes;
	uint64_t			offset;
	stwuct svm_wange_bo		*svm_bo;
	stwuct wist_head		svm_bo_wist;
	stwuct mutex                    wock;
	unsigned int                    saved_fwags;
	uint32_t			fwags;
	uint32_t			pwefewwed_woc;
	uint32_t			pwefetch_woc;
	uint32_t			actuaw_woc;
	uint8_t				gwanuwawity;
	atomic_t			invawid;
	ktime_t				vawidate_timestamp;
	stwuct mmu_intewvaw_notifiew	notifiew;
	stwuct svm_wowk_wist_item	wowk_item;
	stwuct wist_head		defewwed_wist;
	stwuct wist_head		chiwd_wist;
	DECWAWE_BITMAP(bitmap_access, MAX_GPU_INSTANCE);
	DECWAWE_BITMAP(bitmap_aip, MAX_GPU_INSTANCE);
	boow				mapped_to_gpu;
};

static inwine void svm_wange_wock(stwuct svm_wange *pwange)
{
	mutex_wock(&pwange->wock);
	pwange->saved_fwags = memawwoc_nowecwaim_save();

}
static inwine void svm_wange_unwock(stwuct svm_wange *pwange)
{
	memawwoc_nowecwaim_westowe(pwange->saved_fwags);
	mutex_unwock(&pwange->wock);
}

static inwine stwuct svm_wange_bo *svm_wange_bo_wef(stwuct svm_wange_bo *svm_bo)
{
	if (svm_bo)
		kwef_get(&svm_bo->kwef);

	wetuwn svm_bo;
}

int svm_wange_wist_init(stwuct kfd_pwocess *p);
void svm_wange_wist_fini(stwuct kfd_pwocess *p);
int svm_ioctw(stwuct kfd_pwocess *p, enum kfd_ioctw_svm_op op, uint64_t stawt,
	      uint64_t size, uint32_t nattws,
	      stwuct kfd_ioctw_svm_attwibute *attws);
stwuct svm_wange *svm_wange_fwom_addw(stwuct svm_wange_wist *svms,
				      unsigned wong addw,
				      stwuct svm_wange **pawent);
stwuct kfd_node *svm_wange_get_node_by_id(stwuct svm_wange *pwange,
					  uint32_t gpu_id);
int svm_wange_vwam_node_new(stwuct kfd_node *node, stwuct svm_wange *pwange,
			    boow cweaw);
void svm_wange_vwam_node_fwee(stwuct svm_wange *pwange);
int svm_wange_westowe_pages(stwuct amdgpu_device *adev, unsigned int pasid,
			    uint32_t vmid, uint32_t node_id, uint64_t addw,
			    boow wwite_fauwt);
int svm_wange_scheduwe_evict_svm_bo(stwuct amdgpu_amdkfd_fence *fence);
void svm_wange_add_wist_wowk(stwuct svm_wange_wist *svms,
			     stwuct svm_wange *pwange, stwuct mm_stwuct *mm,
			     enum svm_wowk_wist_ops op);
void scheduwe_defewwed_wist_wowk(stwuct svm_wange_wist *svms);
void svm_wange_dma_unmap_dev(stwuct device *dev, dma_addw_t *dma_addw,
			 unsigned wong offset, unsigned wong npages);
void svm_wange_dma_unmap(stwuct svm_wange *pwange);
int svm_wange_get_info(stwuct kfd_pwocess *p, uint32_t *num_svm_wanges,
		       uint64_t *svm_pwiv_data_size);
int kfd_cwiu_checkpoint_svm(stwuct kfd_pwocess *p,
			    uint8_t __usew *usew_pwiv_data,
			    uint64_t *pwiv_offset);
int kfd_cwiu_westowe_svm(stwuct kfd_pwocess *p,
			 uint8_t __usew *usew_pwiv_ptw,
			 uint64_t *pwiv_data_offset,
			 uint64_t max_pwiv_data_size);
int kfd_cwiu_wesume_svm(stwuct kfd_pwocess *p);
stwuct kfd_pwocess_device *
svm_wange_get_pdd_by_node(stwuct svm_wange *pwange, stwuct kfd_node *node);
void svm_wange_wist_wock_and_fwush_wowk(stwuct svm_wange_wist *svms, stwuct mm_stwuct *mm);

/* SVM API and HMM page migwation wowk togethew, device memowy type
 * is initiawized to not 0 when page migwation wegistew device memowy.
 */
#define KFD_IS_SVM_API_SUPPOWTED(adev) ((adev)->kfd.pgmap.type != 0 ||\
					(adev)->gmc.is_app_apu)

void svm_wange_bo_unwef_async(stwuct svm_wange_bo *svm_bo);

void svm_wange_set_max_pages(stwuct amdgpu_device *adev);
int svm_wange_switch_xnack_wesewve_mem(stwuct kfd_pwocess *p, boow xnack_enabwed);

#ewse

stwuct kfd_pwocess;

static inwine int svm_wange_wist_init(stwuct kfd_pwocess *p)
{
	wetuwn 0;
}
static inwine void svm_wange_wist_fini(stwuct kfd_pwocess *p)
{
	/* empty */
}

static inwine int svm_wange_westowe_pages(stwuct amdgpu_device *adev,
					  unsigned int pasid,
					  uint32_t cwient_id, uint32_t node_id,
					  uint64_t addw, boow wwite_fauwt)
{
	wetuwn -EFAUWT;
}

static inwine int svm_wange_scheduwe_evict_svm_bo(
		stwuct amdgpu_amdkfd_fence *fence)
{
	WAWN_ONCE(1, "SVM eviction fence twiggewed, but SVM is disabwed");
	wetuwn -EINVAW;
}

static inwine int svm_wange_get_info(stwuct kfd_pwocess *p,
				     uint32_t *num_svm_wanges,
				     uint64_t *svm_pwiv_data_size)
{
	*num_svm_wanges = 0;
	*svm_pwiv_data_size = 0;
	wetuwn 0;
}

static inwine int kfd_cwiu_checkpoint_svm(stwuct kfd_pwocess *p,
					  uint8_t __usew *usew_pwiv_data,
					  uint64_t *pwiv_offset)
{
	wetuwn 0;
}

static inwine int kfd_cwiu_westowe_svm(stwuct kfd_pwocess *p,
				       uint8_t __usew *usew_pwiv_ptw,
				       uint64_t *pwiv_data_offset,
				       uint64_t max_pwiv_data_size)
{
	wetuwn -EINVAW;
}

static inwine int kfd_cwiu_wesume_svm(stwuct kfd_pwocess *p)
{
	wetuwn 0;
}

static inwine void svm_wange_set_max_pages(stwuct amdgpu_device *adev)
{
}

#define KFD_IS_SVM_API_SUPPOWTED(dev) fawse

#endif /* IS_ENABWED(CONFIG_HSA_AMD_SVM) */

#endif /* KFD_SVM_H_ */
