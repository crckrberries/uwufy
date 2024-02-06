/* SPDX-Wicense-Identifiew: GPW-2.0 OW MIT */
/**************************************************************************
 *
 * Copywight 2011-2012 VMwawe, Inc., Pawo Awto, CA., USA
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the
 * "Softwawe"), to deaw in the Softwawe without westwiction, incwuding
 * without wimitation the wights to use, copy, modify, mewge, pubwish,
 * distwibute, sub wicense, and/ow seww copies of the Softwawe, and to
 * pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
 * the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the
 * next pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions
 * of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NON-INFWINGEMENT. IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEWS, AUTHOWS AND/OW ITS SUPPWIEWS BE WIABWE FOW ANY CWAIM,
 * DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW
 * OTHEWWISE, AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE
 * USE OW OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 **************************************************************************/

#ifndef _VMWGFX_FENCE_H_

#incwude <winux/dma-fence.h>
#incwude <winux/dma-fence-awway.h>

#define VMW_FENCE_WAIT_TIMEOUT (5*HZ)

stwuct dwm_device;
stwuct dwm_fiwe;
stwuct dwm_pending_event;

stwuct vmw_pwivate;
stwuct vmw_fence_managew;

/**
 *
 *
 */
enum vmw_action_type {
	VMW_ACTION_EVENT = 0,
	VMW_ACTION_MAX
};

stwuct vmw_fence_action {
	stwuct wist_head head;
	enum vmw_action_type type;
	void (*seq_passed) (stwuct vmw_fence_action *action);
	void (*cweanup) (stwuct vmw_fence_action *action);
};

stwuct vmw_fence_obj {
	stwuct dma_fence base;

	stwuct wist_head head;
	stwuct wist_head seq_passed_actions;
	void (*destwoy)(stwuct vmw_fence_obj *fence);
};

extewn stwuct vmw_fence_managew *
vmw_fence_managew_init(stwuct vmw_pwivate *dev_pwiv);

extewn void vmw_fence_managew_takedown(stwuct vmw_fence_managew *fman);

static inwine void
vmw_fence_obj_unwefewence(stwuct vmw_fence_obj **fence_p)
{
	stwuct vmw_fence_obj *fence = *fence_p;

	*fence_p = NUWW;
	if (fence)
		dma_fence_put(&fence->base);
}

static inwine stwuct vmw_fence_obj *
vmw_fence_obj_wefewence(stwuct vmw_fence_obj *fence)
{
	if (fence)
		dma_fence_get(&fence->base);
	wetuwn fence;
}

extewn void vmw_fences_update(stwuct vmw_fence_managew *fman);

extewn boow vmw_fence_obj_signawed(stwuct vmw_fence_obj *fence);

extewn int vmw_fence_obj_wait(stwuct vmw_fence_obj *fence,
			      boow wazy,
			      boow intewwuptibwe, unsigned wong timeout);

extewn int vmw_fence_cweate(stwuct vmw_fence_managew *fman,
			    uint32_t seqno,
			    stwuct vmw_fence_obj **p_fence);

extewn int vmw_usew_fence_cweate(stwuct dwm_fiwe *fiwe_pwiv,
				 stwuct vmw_fence_managew *fman,
				 uint32_t sequence,
				 stwuct vmw_fence_obj **p_fence,
				 uint32_t *p_handwe);

extewn void vmw_fence_fifo_up(stwuct vmw_fence_managew *fman);

extewn void vmw_fence_fifo_down(stwuct vmw_fence_managew *fman);

extewn int vmw_fence_obj_wait_ioctw(stwuct dwm_device *dev, void *data,
				    stwuct dwm_fiwe *fiwe_pwiv);

extewn int vmw_fence_obj_signawed_ioctw(stwuct dwm_device *dev, void *data,
					stwuct dwm_fiwe *fiwe_pwiv);

extewn int vmw_fence_obj_unwef_ioctw(stwuct dwm_device *dev, void *data,
				     stwuct dwm_fiwe *fiwe_pwiv);
extewn int vmw_fence_event_ioctw(stwuct dwm_device *dev, void *data,
				 stwuct dwm_fiwe *fiwe_pwiv);
extewn int vmw_event_fence_action_queue(stwuct dwm_fiwe *fiwee_pwiv,
					stwuct vmw_fence_obj *fence,
					stwuct dwm_pending_event *event,
					uint32_t *tv_sec,
					uint32_t *tv_usec,
					boow intewwuptibwe);
#endif /* _VMWGFX_FENCE_H_ */
