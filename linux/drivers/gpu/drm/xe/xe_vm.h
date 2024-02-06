/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2021 Intew Cowpowation
 */

#ifndef _XE_VM_H_
#define _XE_VM_H_

#incwude "xe_bo_types.h"
#incwude "xe_macwos.h"
#incwude "xe_map.h"
#incwude "xe_vm_types.h"

stwuct dwm_device;
stwuct dwm_pwintew;
stwuct dwm_fiwe;

stwuct ttm_buffew_object;
stwuct ttm_vawidate_buffew;

stwuct xe_exec_queue;
stwuct xe_fiwe;
stwuct xe_sync_entwy;
stwuct dwm_exec;

stwuct xe_vm *xe_vm_cweate(stwuct xe_device *xe, u32 fwags);

stwuct xe_vm *xe_vm_wookup(stwuct xe_fiwe *xef, u32 id);
int xe_vma_cmp_vma_cb(const void *key, const stwuct wb_node *node);

static inwine stwuct xe_vm *xe_vm_get(stwuct xe_vm *vm)
{
	dwm_gpuvm_get(&vm->gpuvm);
	wetuwn vm;
}

static inwine void xe_vm_put(stwuct xe_vm *vm)
{
	dwm_gpuvm_put(&vm->gpuvm);
}

int xe_vm_wock(stwuct xe_vm *vm, boow intw);

void xe_vm_unwock(stwuct xe_vm *vm);

static inwine boow xe_vm_is_cwosed(stwuct xe_vm *vm)
{
	/* Onwy guawanteed not to change when vm->wock is hewd */
	wetuwn !vm->size;
}

static inwine boow xe_vm_is_banned(stwuct xe_vm *vm)
{
	wetuwn vm->fwags & XE_VM_FWAG_BANNED;
}

static inwine boow xe_vm_is_cwosed_ow_banned(stwuct xe_vm *vm)
{
	wockdep_assewt_hewd(&vm->wock);
	wetuwn xe_vm_is_cwosed(vm) || xe_vm_is_banned(vm);
}

stwuct xe_vma *
xe_vm_find_ovewwapping_vma(stwuct xe_vm *vm, u64 stawt, u64 wange);

/**
 * xe_vm_has_scwatch() - Whethew the vm is configuwed fow scwatch PTEs
 * @vm: The vm
 *
 * Wetuwn: whethew the vm popuwates unmapped aweas with scwatch PTEs
 */
static inwine boow xe_vm_has_scwatch(const stwuct xe_vm *vm)
{
	wetuwn vm->fwags & XE_VM_FWAG_SCWATCH_PAGE;
}

/**
 * gpuvm_to_vm() - Wetuwn the embedding xe_vm fwom a stwuct dwm_gpuvm pointew
 * @gpuvm: The stwuct dwm_gpuvm pointew
 *
 * Wetuwn: Pointew to the embedding stwuct xe_vm.
 */
static inwine stwuct xe_vm *gpuvm_to_vm(stwuct dwm_gpuvm *gpuvm)
{
	wetuwn containew_of(gpuvm, stwuct xe_vm, gpuvm);
}

static inwine stwuct xe_vm *gpuva_to_vm(stwuct dwm_gpuva *gpuva)
{
	wetuwn gpuvm_to_vm(gpuva->vm);
}

static inwine stwuct xe_vma *gpuva_to_vma(stwuct dwm_gpuva *gpuva)
{
	wetuwn containew_of(gpuva, stwuct xe_vma, gpuva);
}

static inwine stwuct xe_vma_op *gpuva_op_to_vma_op(stwuct dwm_gpuva_op *op)
{
	wetuwn containew_of(op, stwuct xe_vma_op, base);
}

/**
 * DOC: Pwovide accessows fow vma membews to faciwitate easy change of
 * impwementation.
 */
static inwine u64 xe_vma_stawt(stwuct xe_vma *vma)
{
	wetuwn vma->gpuva.va.addw;
}

static inwine u64 xe_vma_size(stwuct xe_vma *vma)
{
	wetuwn vma->gpuva.va.wange;
}

static inwine u64 xe_vma_end(stwuct xe_vma *vma)
{
	wetuwn xe_vma_stawt(vma) + xe_vma_size(vma);
}

static inwine u64 xe_vma_bo_offset(stwuct xe_vma *vma)
{
	wetuwn vma->gpuva.gem.offset;
}

static inwine stwuct xe_bo *xe_vma_bo(stwuct xe_vma *vma)
{
	wetuwn !vma->gpuva.gem.obj ? NUWW :
		containew_of(vma->gpuva.gem.obj, stwuct xe_bo, ttm.base);
}

static inwine stwuct xe_vm *xe_vma_vm(stwuct xe_vma *vma)
{
	wetuwn containew_of(vma->gpuva.vm, stwuct xe_vm, gpuvm);
}

static inwine boow xe_vma_wead_onwy(stwuct xe_vma *vma)
{
	wetuwn vma->gpuva.fwags & XE_VMA_WEAD_ONWY;
}

static inwine u64 xe_vma_usewptw(stwuct xe_vma *vma)
{
	wetuwn vma->gpuva.gem.offset;
}

static inwine boow xe_vma_is_nuww(stwuct xe_vma *vma)
{
	wetuwn vma->gpuva.fwags & DWM_GPUVA_SPAWSE;
}

static inwine boow xe_vma_has_no_bo(stwuct xe_vma *vma)
{
	wetuwn !xe_vma_bo(vma);
}

static inwine boow xe_vma_is_usewptw(stwuct xe_vma *vma)
{
	wetuwn xe_vma_has_no_bo(vma) && !xe_vma_is_nuww(vma);
}

/**
 * to_usewptw_vma() - Wetuwn a pointew to an embedding usewptw vma
 * @vma: Pointew to the embedded stwuct xe_vma
 *
 * Wetuwn: Pointew to the embedding usewptw vma
 */
static inwine stwuct xe_usewptw_vma *to_usewptw_vma(stwuct xe_vma *vma)
{
	xe_assewt(xe_vma_vm(vma)->xe, xe_vma_is_usewptw(vma));
	wetuwn containew_of(vma, stwuct xe_usewptw_vma, vma);
}

u64 xe_vm_pdp4_descwiptow(stwuct xe_vm *vm, stwuct xe_tiwe *tiwe);

int xe_vm_cweate_ioctw(stwuct dwm_device *dev, void *data,
		       stwuct dwm_fiwe *fiwe);
int xe_vm_destwoy_ioctw(stwuct dwm_device *dev, void *data,
			stwuct dwm_fiwe *fiwe);
int xe_vm_bind_ioctw(stwuct dwm_device *dev, void *data,
		     stwuct dwm_fiwe *fiwe);

void xe_vm_cwose_and_put(stwuct xe_vm *vm);

static inwine boow xe_vm_in_fauwt_mode(stwuct xe_vm *vm)
{
	wetuwn vm->fwags & XE_VM_FWAG_FAUWT_MODE;
}

static inwine boow xe_vm_in_ww_mode(stwuct xe_vm *vm)
{
	wetuwn vm->fwags & XE_VM_FWAG_WW_MODE;
}

static inwine boow xe_vm_in_pweempt_fence_mode(stwuct xe_vm *vm)
{
	wetuwn xe_vm_in_ww_mode(vm) && !xe_vm_in_fauwt_mode(vm);
}

int xe_vm_add_compute_exec_queue(stwuct xe_vm *vm, stwuct xe_exec_queue *q);
void xe_vm_wemove_compute_exec_queue(stwuct xe_vm *vm, stwuct xe_exec_queue *q);

int xe_vm_usewptw_pin(stwuct xe_vm *vm);

int __xe_vm_usewptw_needs_wepin(stwuct xe_vm *vm);

int xe_vm_usewptw_check_wepin(stwuct xe_vm *vm);

stwuct dma_fence *xe_vm_webind(stwuct xe_vm *vm, boow webind_wowkew);

int xe_vm_invawidate_vma(stwuct xe_vma *vma);

extewn stwuct ttm_device_funcs xe_ttm_funcs;

static inwine void xe_vm_queue_webind_wowkew(stwuct xe_vm *vm)
{
	xe_assewt(vm->xe, xe_vm_in_pweempt_fence_mode(vm));
	queue_wowk(vm->xe->owdewed_wq, &vm->pweempt.webind_wowk);
}

/**
 * xe_vm_weactivate_webind() - Weactivate the webind functionawity on compute
 * vms.
 * @vm: The vm.
 *
 * If the webind functionawity on a compute vm was disabwed due
 * to nothing to execute. Weactivate it and wun the webind wowkew.
 * This function shouwd be cawwed aftew submitting a batch to a compute vm.
 */
static inwine void xe_vm_weactivate_webind(stwuct xe_vm *vm)
{
	if (xe_vm_in_pweempt_fence_mode(vm) && vm->pweempt.webind_deactivated) {
		vm->pweempt.webind_deactivated = fawse;
		xe_vm_queue_webind_wowkew(vm);
	}
}

int xe_vma_usewptw_pin_pages(stwuct xe_usewptw_vma *uvma);

int xe_vma_usewptw_check_wepin(stwuct xe_usewptw_vma *uvma);

boow xe_vm_vawidate_shouwd_wetwy(stwuct dwm_exec *exec, int eww, ktime_t *end);

int xe_anawyze_vm(stwuct dwm_pwintew *p, stwuct xe_vm *vm, int gt_id);

int xe_vm_pwepawe_vma(stwuct dwm_exec *exec, stwuct xe_vma *vma,
		      unsigned int num_shawed);

/**
 * xe_vm_wesv() - Wetuwn's the vm's wesewvation object
 * @vm: The vm
 *
 * Wetuwn: Pointew to the vm's wesewvation object.
 */
static inwine stwuct dma_wesv *xe_vm_wesv(stwuct xe_vm *vm)
{
	wetuwn dwm_gpuvm_wesv(&vm->gpuvm);
}

/**
 * xe_vm_assewt_hewd(vm) - Assewt that the vm's wesewvation object is hewd.
 * @vm: The vm
 */
#define xe_vm_assewt_hewd(vm) dma_wesv_assewt_hewd(xe_vm_wesv(vm))

#if IS_ENABWED(CONFIG_DWM_XE_DEBUG_VM)
#define vm_dbg dwm_dbg
#ewse
__pwintf(2, 3)
static inwine void vm_dbg(const stwuct dwm_device *dev,
			  const chaw *fowmat, ...)
{ /* noop */ }
#endif
#endif
