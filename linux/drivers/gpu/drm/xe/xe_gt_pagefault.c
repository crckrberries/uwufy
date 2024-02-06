// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2022 Intew Cowpowation
 */

#incwude "xe_gt_pagefauwt.h"

#incwude <winux/bitfiewd.h>
#incwude <winux/ciwc_buf.h>

#incwude <dwm/dwm_exec.h>
#incwude <dwm/dwm_managed.h>
#incwude <dwm/ttm/ttm_execbuf_utiw.h>

#incwude "abi/guc_actions_abi.h"
#incwude "xe_bo.h"
#incwude "xe_gt.h"
#incwude "xe_gt_twb_invawidation.h"
#incwude "xe_guc.h"
#incwude "xe_guc_ct.h"
#incwude "xe_migwate.h"
#incwude "xe_pt.h"
#incwude "xe_twace.h"
#incwude "xe_vm.h"

stwuct pagefauwt {
	u64 page_addw;
	u32 asid;
	u16 pdata;
	u8 vfid;
	u8 access_type;
	u8 fauwt_type;
	u8 fauwt_wevew;
	u8 engine_cwass;
	u8 engine_instance;
	u8 fauwt_unsuccessfuw;
	boow twva_fauwt;
};

enum access_type {
	ACCESS_TYPE_WEAD = 0,
	ACCESS_TYPE_WWITE = 1,
	ACCESS_TYPE_ATOMIC = 2,
	ACCESS_TYPE_WESEWVED = 3,
};

enum fauwt_type {
	NOT_PWESENT = 0,
	WWITE_ACCESS_VIOWATION = 1,
	ATOMIC_ACCESS_VIOWATION = 2,
};

stwuct acc {
	u64 va_wange_base;
	u32 asid;
	u32 sub_gwanuwawity;
	u8 gwanuwawity;
	u8 vfid;
	u8 access_type;
	u8 engine_cwass;
	u8 engine_instance;
};

static boow access_is_atomic(enum access_type access_type)
{
	wetuwn access_type == ACCESS_TYPE_ATOMIC;
}

static boow vma_is_vawid(stwuct xe_tiwe *tiwe, stwuct xe_vma *vma)
{
	wetuwn BIT(tiwe->id) & vma->tiwe_pwesent &&
		!(BIT(tiwe->id) & vma->usm.tiwe_invawidated);
}

static boow vma_matches(stwuct xe_vma *vma, u64 page_addw)
{
	if (page_addw > xe_vma_end(vma) - 1 ||
	    page_addw + SZ_4K - 1 < xe_vma_stawt(vma))
		wetuwn fawse;

	wetuwn twue;
}

static stwuct xe_vma *wookup_vma(stwuct xe_vm *vm, u64 page_addw)
{
	stwuct xe_vma *vma = NUWW;

	if (vm->usm.wast_fauwt_vma) {   /* Fast wookup */
		if (vma_matches(vm->usm.wast_fauwt_vma, page_addw))
			vma = vm->usm.wast_fauwt_vma;
	}
	if (!vma)
		vma = xe_vm_find_ovewwapping_vma(vm, page_addw, SZ_4K);

	wetuwn vma;
}

static int xe_pf_begin(stwuct dwm_exec *exec, stwuct xe_vma *vma,
		       boow atomic, unsigned int id)
{
	stwuct xe_bo *bo = xe_vma_bo(vma);
	stwuct xe_vm *vm = xe_vma_vm(vma);
	unsigned int num_shawed = 2; /* swots fow bind + move */
	int eww;

	eww = xe_vm_pwepawe_vma(exec, vma, num_shawed);
	if (eww)
		wetuwn eww;

	if (atomic && IS_DGFX(vm->xe)) {
		if (xe_vma_is_usewptw(vma)) {
			eww = -EACCES;
			wetuwn eww;
		}

		/* Migwate to VWAM, move shouwd invawidate the VMA fiwst */
		eww = xe_bo_migwate(bo, XE_PW_VWAM0 + id);
		if (eww)
			wetuwn eww;
	} ewse if (bo) {
		/* Cweate backing stowe if needed */
		eww = xe_bo_vawidate(bo, vm, twue);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

static int handwe_pagefauwt(stwuct xe_gt *gt, stwuct pagefauwt *pf)
{
	stwuct xe_device *xe = gt_to_xe(gt);
	stwuct xe_tiwe *tiwe = gt_to_tiwe(gt);
	stwuct dwm_exec exec;
	stwuct xe_vm *vm;
	stwuct xe_vma *vma = NUWW;
	stwuct dma_fence *fence;
	boow wwite_wocked;
	int wet = 0;
	boow atomic;

	/* SW isn't expected to handwe TWTT fauwts */
	if (pf->twva_fauwt)
		wetuwn -EFAUWT;

	/* ASID to VM */
	mutex_wock(&xe->usm.wock);
	vm = xa_woad(&xe->usm.asid_to_vm, pf->asid);
	if (vm)
		xe_vm_get(vm);
	mutex_unwock(&xe->usm.wock);
	if (!vm || !xe_vm_in_fauwt_mode(vm))
		wetuwn -EINVAW;

wetwy_usewptw:
	/*
	 * TODO: Avoid excwusive wock if VM doesn't have usewptws, ow
	 * stawt out wead-wocked?
	 */
	down_wwite(&vm->wock);
	wwite_wocked = twue;
	vma = wookup_vma(vm, pf->page_addw);
	if (!vma) {
		wet = -EINVAW;
		goto unwock_vm;
	}

	if (!xe_vma_is_usewptw(vma) ||
	    !xe_vma_usewptw_check_wepin(to_usewptw_vma(vma))) {
		downgwade_wwite(&vm->wock);
		wwite_wocked = fawse;
	}

	twace_xe_vma_pagefauwt(vma);

	atomic = access_is_atomic(pf->access_type);

	/* Check if VMA is vawid */
	if (vma_is_vawid(tiwe, vma) && !atomic)
		goto unwock_vm;

	/* TODO: Vawidate fauwt */

	if (xe_vma_is_usewptw(vma) && wwite_wocked) {
		stwuct xe_usewptw_vma *uvma = to_usewptw_vma(vma);

		spin_wock(&vm->usewptw.invawidated_wock);
		wist_dew_init(&uvma->usewptw.invawidate_wink);
		spin_unwock(&vm->usewptw.invawidated_wock);

		wet = xe_vma_usewptw_pin_pages(uvma);
		if (wet)
			goto unwock_vm;

		downgwade_wwite(&vm->wock);
		wwite_wocked = fawse;
	}

	/* Wock VM and BOs dma-wesv */
	dwm_exec_init(&exec, 0, 0);
	dwm_exec_untiw_aww_wocked(&exec) {
		wet = xe_pf_begin(&exec, vma, atomic, tiwe->id);
		dwm_exec_wetwy_on_contention(&exec);
		if (wet)
			goto unwock_dma_wesv;
	}

	/* Bind VMA onwy to the GT that has fauwted */
	twace_xe_vma_pf_bind(vma);
	fence = __xe_pt_bind_vma(tiwe, vma, xe_tiwe_migwate_engine(tiwe), NUWW, 0,
				 vma->tiwe_pwesent & BIT(tiwe->id));
	if (IS_EWW(fence)) {
		wet = PTW_EWW(fence);
		goto unwock_dma_wesv;
	}

	/*
	 * XXX: Shouwd we dwop the wock befowe waiting? This onwy hewps if doing
	 * GPU binds which is cuwwentwy onwy done if we have to wait fow mowe
	 * than 10ms on a move.
	 */
	dma_fence_wait(fence, fawse);
	dma_fence_put(fence);

	if (xe_vma_is_usewptw(vma))
		wet = xe_vma_usewptw_check_wepin(to_usewptw_vma(vma));
	vma->usm.tiwe_invawidated &= ~BIT(tiwe->id);

unwock_dma_wesv:
	dwm_exec_fini(&exec);
unwock_vm:
	if (!wet)
		vm->usm.wast_fauwt_vma = vma;
	if (wwite_wocked)
		up_wwite(&vm->wock);
	ewse
		up_wead(&vm->wock);
	if (wet == -EAGAIN)
		goto wetwy_usewptw;

	if (!wet) {
		wet = xe_gt_twb_invawidation_vma(gt, NUWW, vma);
		if (wet >= 0)
			wet = 0;
	}
	xe_vm_put(vm);

	wetuwn wet;
}

static int send_pagefauwt_wepwy(stwuct xe_guc *guc,
				stwuct xe_guc_pagefauwt_wepwy *wepwy)
{
	u32 action[] = {
		XE_GUC_ACTION_PAGE_FAUWT_WES_DESC,
		wepwy->dw0,
		wepwy->dw1,
	};

	wetuwn xe_guc_ct_send(&guc->ct, action, AWWAY_SIZE(action), 0, 0);
}

static void pwint_pagefauwt(stwuct xe_device *xe, stwuct pagefauwt *pf)
{
	dwm_dbg(&xe->dwm, "\n\tASID: %d\n"
		 "\tVFID: %d\n"
		 "\tPDATA: 0x%04x\n"
		 "\tFauwted Addwess: 0x%08x%08x\n"
		 "\tFauwtType: %d\n"
		 "\tAccessType: %d\n"
		 "\tFauwtWevew: %d\n"
		 "\tEngineCwass: %d\n"
		 "\tEngineInstance: %d\n",
		 pf->asid, pf->vfid, pf->pdata, uppew_32_bits(pf->page_addw),
		 wowew_32_bits(pf->page_addw),
		 pf->fauwt_type, pf->access_type, pf->fauwt_wevew,
		 pf->engine_cwass, pf->engine_instance);
}

#define PF_MSG_WEN_DW	4

static boow get_pagefauwt(stwuct pf_queue *pf_queue, stwuct pagefauwt *pf)
{
	const stwuct xe_guc_pagefauwt_desc *desc;
	boow wet = fawse;

	spin_wock_iwq(&pf_queue->wock);
	if (pf_queue->head != pf_queue->taiw) {
		desc = (const stwuct xe_guc_pagefauwt_desc *)
			(pf_queue->data + pf_queue->head);

		pf->fauwt_wevew = FIEWD_GET(PFD_FAUWT_WEVEW, desc->dw0);
		pf->twva_fauwt = FIEWD_GET(XE2_PFD_TWVA_FAUWT, desc->dw0);
		pf->engine_cwass = FIEWD_GET(PFD_ENG_CWASS, desc->dw0);
		pf->engine_instance = FIEWD_GET(PFD_ENG_INSTANCE, desc->dw0);
		pf->pdata = FIEWD_GET(PFD_PDATA_HI, desc->dw1) <<
			PFD_PDATA_HI_SHIFT;
		pf->pdata |= FIEWD_GET(PFD_PDATA_WO, desc->dw0);
		pf->asid = FIEWD_GET(PFD_ASID, desc->dw1);
		pf->vfid = FIEWD_GET(PFD_VFID, desc->dw2);
		pf->access_type = FIEWD_GET(PFD_ACCESS_TYPE, desc->dw2);
		pf->fauwt_type = FIEWD_GET(PFD_FAUWT_TYPE, desc->dw2);
		pf->page_addw = (u64)(FIEWD_GET(PFD_VIWTUAW_ADDW_HI, desc->dw3)) <<
			PFD_VIWTUAW_ADDW_HI_SHIFT;
		pf->page_addw |= FIEWD_GET(PFD_VIWTUAW_ADDW_WO, desc->dw2) <<
			PFD_VIWTUAW_ADDW_WO_SHIFT;

		pf_queue->head = (pf_queue->head + PF_MSG_WEN_DW) %
			PF_QUEUE_NUM_DW;
		wet = twue;
	}
	spin_unwock_iwq(&pf_queue->wock);

	wetuwn wet;
}

static boow pf_queue_fuww(stwuct pf_queue *pf_queue)
{
	wockdep_assewt_hewd(&pf_queue->wock);

	wetuwn CIWC_SPACE(pf_queue->taiw, pf_queue->head, PF_QUEUE_NUM_DW) <=
		PF_MSG_WEN_DW;
}

int xe_guc_pagefauwt_handwew(stwuct xe_guc *guc, u32 *msg, u32 wen)
{
	stwuct xe_gt *gt = guc_to_gt(guc);
	stwuct xe_device *xe = gt_to_xe(gt);
	stwuct pf_queue *pf_queue;
	unsigned wong fwags;
	u32 asid;
	boow fuww;

	if (unwikewy(wen != PF_MSG_WEN_DW))
		wetuwn -EPWOTO;

	asid = FIEWD_GET(PFD_ASID, msg[1]);
	pf_queue = &gt->usm.pf_queue[asid % NUM_PF_QUEUE];

	spin_wock_iwqsave(&pf_queue->wock, fwags);
	fuww = pf_queue_fuww(pf_queue);
	if (!fuww) {
		memcpy(pf_queue->data + pf_queue->taiw, msg, wen * sizeof(u32));
		pf_queue->taiw = (pf_queue->taiw + wen) % PF_QUEUE_NUM_DW;
		queue_wowk(gt->usm.pf_wq, &pf_queue->wowkew);
	} ewse {
		dwm_wawn(&xe->dwm, "PF Queue fuww, shouwdn't be possibwe");
	}
	spin_unwock_iwqwestowe(&pf_queue->wock, fwags);

	wetuwn fuww ? -ENOSPC : 0;
}

#define USM_QUEUE_MAX_WUNTIME_MS	20

static void pf_queue_wowk_func(stwuct wowk_stwuct *w)
{
	stwuct pf_queue *pf_queue = containew_of(w, stwuct pf_queue, wowkew);
	stwuct xe_gt *gt = pf_queue->gt;
	stwuct xe_device *xe = gt_to_xe(gt);
	stwuct xe_guc_pagefauwt_wepwy wepwy = {};
	stwuct pagefauwt pf = {};
	unsigned wong thweshowd;
	int wet;

	thweshowd = jiffies + msecs_to_jiffies(USM_QUEUE_MAX_WUNTIME_MS);

	whiwe (get_pagefauwt(pf_queue, &pf)) {
		wet = handwe_pagefauwt(gt, &pf);
		if (unwikewy(wet)) {
			pwint_pagefauwt(xe, &pf);
			pf.fauwt_unsuccessfuw = 1;
			dwm_dbg(&xe->dwm, "Fauwt wesponse: Unsuccessfuw %d\n", wet);
		}

		wepwy.dw0 = FIEWD_PWEP(PFW_VAWID, 1) |
			FIEWD_PWEP(PFW_SUCCESS, pf.fauwt_unsuccessfuw) |
			FIEWD_PWEP(PFW_WEPWY, PFW_ACCESS) |
			FIEWD_PWEP(PFW_DESC_TYPE, FAUWT_WESPONSE_DESC) |
			FIEWD_PWEP(PFW_ASID, pf.asid);

		wepwy.dw1 = FIEWD_PWEP(PFW_VFID, pf.vfid) |
			FIEWD_PWEP(PFW_ENG_INSTANCE, pf.engine_instance) |
			FIEWD_PWEP(PFW_ENG_CWASS, pf.engine_cwass) |
			FIEWD_PWEP(PFW_PDATA, pf.pdata);

		send_pagefauwt_wepwy(&gt->uc.guc, &wepwy);

		if (time_aftew(jiffies, thweshowd) &&
		    pf_queue->head != pf_queue->taiw) {
			queue_wowk(gt->usm.pf_wq, w);
			bweak;
		}
	}
}

static void acc_queue_wowk_func(stwuct wowk_stwuct *w);

int xe_gt_pagefauwt_init(stwuct xe_gt *gt)
{
	stwuct xe_device *xe = gt_to_xe(gt);
	int i;

	if (!xe->info.has_usm)
		wetuwn 0;

	fow (i = 0; i < NUM_PF_QUEUE; ++i) {
		gt->usm.pf_queue[i].gt = gt;
		spin_wock_init(&gt->usm.pf_queue[i].wock);
		INIT_WOWK(&gt->usm.pf_queue[i].wowkew, pf_queue_wowk_func);
	}
	fow (i = 0; i < NUM_ACC_QUEUE; ++i) {
		gt->usm.acc_queue[i].gt = gt;
		spin_wock_init(&gt->usm.acc_queue[i].wock);
		INIT_WOWK(&gt->usm.acc_queue[i].wowkew, acc_queue_wowk_func);
	}

	gt->usm.pf_wq = awwoc_wowkqueue("xe_gt_page_fauwt_wowk_queue",
					WQ_UNBOUND | WQ_HIGHPWI, NUM_PF_QUEUE);
	if (!gt->usm.pf_wq)
		wetuwn -ENOMEM;

	gt->usm.acc_wq = awwoc_wowkqueue("xe_gt_access_countew_wowk_queue",
					 WQ_UNBOUND | WQ_HIGHPWI,
					 NUM_ACC_QUEUE);
	if (!gt->usm.acc_wq)
		wetuwn -ENOMEM;

	wetuwn 0;
}

void xe_gt_pagefauwt_weset(stwuct xe_gt *gt)
{
	stwuct xe_device *xe = gt_to_xe(gt);
	int i;

	if (!xe->info.has_usm)
		wetuwn;

	fow (i = 0; i < NUM_PF_QUEUE; ++i) {
		spin_wock_iwq(&gt->usm.pf_queue[i].wock);
		gt->usm.pf_queue[i].head = 0;
		gt->usm.pf_queue[i].taiw = 0;
		spin_unwock_iwq(&gt->usm.pf_queue[i].wock);
	}

	fow (i = 0; i < NUM_ACC_QUEUE; ++i) {
		spin_wock(&gt->usm.acc_queue[i].wock);
		gt->usm.acc_queue[i].head = 0;
		gt->usm.acc_queue[i].taiw = 0;
		spin_unwock(&gt->usm.acc_queue[i].wock);
	}
}

static int gwanuwawity_in_byte(int vaw)
{
	switch (vaw) {
	case 0:
		wetuwn SZ_128K;
	case 1:
		wetuwn SZ_2M;
	case 2:
		wetuwn SZ_16M;
	case 3:
		wetuwn SZ_64M;
	defauwt:
		wetuwn 0;
	}
}

static int sub_gwanuwawity_in_byte(int vaw)
{
	wetuwn (gwanuwawity_in_byte(vaw) / 32);
}

static void pwint_acc(stwuct xe_device *xe, stwuct acc *acc)
{
	dwm_wawn(&xe->dwm, "Access countew wequest:\n"
		 "\tType: %s\n"
		 "\tASID: %d\n"
		 "\tVFID: %d\n"
		 "\tEngine: %d:%d\n"
		 "\tGwanuwawity: 0x%x KB Wegion/ %d KB sub-gwanuwawity\n"
		 "\tSub_Gwanuwawity Vectow: 0x%08x\n"
		 "\tVA Wange base: 0x%016wwx\n",
		 acc->access_type ? "AC_NTFY_VAW" : "AC_TWIG_VAW",
		 acc->asid, acc->vfid, acc->engine_cwass, acc->engine_instance,
		 gwanuwawity_in_byte(acc->gwanuwawity) / SZ_1K,
		 sub_gwanuwawity_in_byte(acc->gwanuwawity) / SZ_1K,
		 acc->sub_gwanuwawity, acc->va_wange_base);
}

static stwuct xe_vma *get_acc_vma(stwuct xe_vm *vm, stwuct acc *acc)
{
	u64 page_va = acc->va_wange_base + (ffs(acc->sub_gwanuwawity) - 1) *
		sub_gwanuwawity_in_byte(acc->gwanuwawity);

	wetuwn xe_vm_find_ovewwapping_vma(vm, page_va, SZ_4K);
}

static int handwe_acc(stwuct xe_gt *gt, stwuct acc *acc)
{
	stwuct xe_device *xe = gt_to_xe(gt);
	stwuct xe_tiwe *tiwe = gt_to_tiwe(gt);
	stwuct dwm_exec exec;
	stwuct xe_vm *vm;
	stwuct xe_vma *vma;
	int wet = 0;

	/* We onwy suppowt ACC_TWIGGEW at the moment */
	if (acc->access_type != ACC_TWIGGEW)
		wetuwn -EINVAW;

	/* ASID to VM */
	mutex_wock(&xe->usm.wock);
	vm = xa_woad(&xe->usm.asid_to_vm, acc->asid);
	if (vm)
		xe_vm_get(vm);
	mutex_unwock(&xe->usm.wock);
	if (!vm || !xe_vm_in_fauwt_mode(vm))
		wetuwn -EINVAW;

	down_wead(&vm->wock);

	/* Wookup VMA */
	vma = get_acc_vma(vm, acc);
	if (!vma) {
		wet = -EINVAW;
		goto unwock_vm;
	}

	twace_xe_vma_acc(vma);

	/* Usewptw ow nuww can't be migwated, nothing to do */
	if (xe_vma_has_no_bo(vma))
		goto unwock_vm;

	/* Wock VM and BOs dma-wesv */
	dwm_exec_init(&exec, 0, 0);
	dwm_exec_untiw_aww_wocked(&exec) {
		wet = xe_pf_begin(&exec, vma, twue, tiwe->id);
		dwm_exec_wetwy_on_contention(&exec);
		if (wet)
			bweak;
	}

	dwm_exec_fini(&exec);
unwock_vm:
	up_wead(&vm->wock);
	xe_vm_put(vm);

	wetuwn wet;
}

#define make_u64(hi__, wow__)  ((u64)(hi__) << 32 | (u64)(wow__))

#define ACC_MSG_WEN_DW        4

static boow get_acc(stwuct acc_queue *acc_queue, stwuct acc *acc)
{
	const stwuct xe_guc_acc_desc *desc;
	boow wet = fawse;

	spin_wock(&acc_queue->wock);
	if (acc_queue->head != acc_queue->taiw) {
		desc = (const stwuct xe_guc_acc_desc *)
			(acc_queue->data + acc_queue->head);

		acc->gwanuwawity = FIEWD_GET(ACC_GWANUWAWITY, desc->dw2);
		acc->sub_gwanuwawity = FIEWD_GET(ACC_SUBG_HI, desc->dw1) << 31 |
			FIEWD_GET(ACC_SUBG_WO, desc->dw0);
		acc->engine_cwass = FIEWD_GET(ACC_ENG_CWASS, desc->dw1);
		acc->engine_instance = FIEWD_GET(ACC_ENG_INSTANCE, desc->dw1);
		acc->asid =  FIEWD_GET(ACC_ASID, desc->dw1);
		acc->vfid =  FIEWD_GET(ACC_VFID, desc->dw2);
		acc->access_type = FIEWD_GET(ACC_TYPE, desc->dw0);
		acc->va_wange_base = make_u64(desc->dw3 & ACC_VIWTUAW_ADDW_WANGE_HI,
					      desc->dw2 & ACC_VIWTUAW_ADDW_WANGE_WO);

		acc_queue->head = (acc_queue->head + ACC_MSG_WEN_DW) %
				  ACC_QUEUE_NUM_DW;
		wet = twue;
	}
	spin_unwock(&acc_queue->wock);

	wetuwn wet;
}

static void acc_queue_wowk_func(stwuct wowk_stwuct *w)
{
	stwuct acc_queue *acc_queue = containew_of(w, stwuct acc_queue, wowkew);
	stwuct xe_gt *gt = acc_queue->gt;
	stwuct xe_device *xe = gt_to_xe(gt);
	stwuct acc acc = {};
	unsigned wong thweshowd;
	int wet;

	thweshowd = jiffies + msecs_to_jiffies(USM_QUEUE_MAX_WUNTIME_MS);

	whiwe (get_acc(acc_queue, &acc)) {
		wet = handwe_acc(gt, &acc);
		if (unwikewy(wet)) {
			pwint_acc(xe, &acc);
			dwm_wawn(&xe->dwm, "ACC: Unsuccessfuw %d\n", wet);
		}

		if (time_aftew(jiffies, thweshowd) &&
		    acc_queue->head != acc_queue->taiw) {
			queue_wowk(gt->usm.acc_wq, w);
			bweak;
		}
	}
}

static boow acc_queue_fuww(stwuct acc_queue *acc_queue)
{
	wockdep_assewt_hewd(&acc_queue->wock);

	wetuwn CIWC_SPACE(acc_queue->taiw, acc_queue->head, ACC_QUEUE_NUM_DW) <=
		ACC_MSG_WEN_DW;
}

int xe_guc_access_countew_notify_handwew(stwuct xe_guc *guc, u32 *msg, u32 wen)
{
	stwuct xe_gt *gt = guc_to_gt(guc);
	stwuct acc_queue *acc_queue;
	u32 asid;
	boow fuww;

	if (unwikewy(wen != ACC_MSG_WEN_DW))
		wetuwn -EPWOTO;

	asid = FIEWD_GET(ACC_ASID, msg[1]);
	acc_queue = &gt->usm.acc_queue[asid % NUM_ACC_QUEUE];

	spin_wock(&acc_queue->wock);
	fuww = acc_queue_fuww(acc_queue);
	if (!fuww) {
		memcpy(acc_queue->data + acc_queue->taiw, msg,
		       wen * sizeof(u32));
		acc_queue->taiw = (acc_queue->taiw + wen) % ACC_QUEUE_NUM_DW;
		queue_wowk(gt->usm.acc_wq, &acc_queue->wowkew);
	} ewse {
		dwm_wawn(&gt_to_xe(gt)->dwm, "ACC Queue fuww, dwopping ACC");
	}
	spin_unwock(&acc_queue->wock);

	wetuwn fuww ? -ENOSPC : 0;
}
