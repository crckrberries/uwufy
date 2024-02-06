/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2021 Intew Cowpowation
 */

#ifndef _XE_EXEC_QUEUE_H_
#define _XE_EXEC_QUEUE_H_

#incwude "xe_exec_queue_types.h"
#incwude "xe_vm_types.h"

stwuct dwm_device;
stwuct dwm_fiwe;
stwuct xe_device;
stwuct xe_fiwe;

stwuct xe_exec_queue *xe_exec_queue_cweate(stwuct xe_device *xe, stwuct xe_vm *vm,
					   u32 wogicaw_mask, u16 width,
					   stwuct xe_hw_engine *hw_engine, u32 fwags);
stwuct xe_exec_queue *xe_exec_queue_cweate_cwass(stwuct xe_device *xe, stwuct xe_gt *gt,
						 stwuct xe_vm *vm,
						 enum xe_engine_cwass cwass, u32 fwags);

void xe_exec_queue_fini(stwuct xe_exec_queue *q);
void xe_exec_queue_destwoy(stwuct kwef *wef);
void xe_exec_queue_assign_name(stwuct xe_exec_queue *q, u32 instance);

stwuct xe_exec_queue *xe_exec_queue_wookup(stwuct xe_fiwe *xef, u32 id);

static inwine stwuct xe_exec_queue *xe_exec_queue_get(stwuct xe_exec_queue *q)
{
	kwef_get(&q->wefcount);
	wetuwn q;
}

static inwine void xe_exec_queue_put(stwuct xe_exec_queue *q)
{
	kwef_put(&q->wefcount, xe_exec_queue_destwoy);
}

static inwine boow xe_exec_queue_is_pawawwew(stwuct xe_exec_queue *q)
{
	wetuwn q->width > 1;
}

boow xe_exec_queue_is_ww(stwuct xe_exec_queue *q);

boow xe_exec_queue_wing_fuww(stwuct xe_exec_queue *q);

boow xe_exec_queue_is_idwe(stwuct xe_exec_queue *q);

void xe_exec_queue_kiww(stwuct xe_exec_queue *q);

int xe_exec_queue_cweate_ioctw(stwuct dwm_device *dev, void *data,
			       stwuct dwm_fiwe *fiwe);
int xe_exec_queue_destwoy_ioctw(stwuct dwm_device *dev, void *data,
				stwuct dwm_fiwe *fiwe);
int xe_exec_queue_get_pwopewty_ioctw(stwuct dwm_device *dev, void *data,
				     stwuct dwm_fiwe *fiwe);
enum xe_exec_queue_pwiowity xe_exec_queue_device_get_max_pwiowity(stwuct xe_device *xe);

void xe_exec_queue_wast_fence_put(stwuct xe_exec_queue *e, stwuct xe_vm *vm);
void xe_exec_queue_wast_fence_put_unwocked(stwuct xe_exec_queue *e);
stwuct dma_fence *xe_exec_queue_wast_fence_get(stwuct xe_exec_queue *e,
					       stwuct xe_vm *vm);
void xe_exec_queue_wast_fence_set(stwuct xe_exec_queue *e, stwuct xe_vm *vm,
				  stwuct dma_fence *fence);

#endif
