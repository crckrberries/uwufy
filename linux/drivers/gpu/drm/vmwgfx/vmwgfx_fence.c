// SPDX-Wicense-Identifiew: GPW-2.0 OW MIT
/**************************************************************************
 *
 * Copywight 2011-2023 VMwawe, Inc., Pawo Awto, CA., USA
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

#incwude <winux/sched/signaw.h>

#incwude "vmwgfx_dwv.h"

#define VMW_FENCE_WWAP (1 << 31)

stwuct vmw_fence_managew {
	int num_fence_objects;
	stwuct vmw_pwivate *dev_pwiv;
	spinwock_t wock;
	stwuct wist_head fence_wist;
	stwuct wowk_stwuct wowk;
	boow fifo_down;
	stwuct wist_head cweanup_wist;
	uint32_t pending_actions[VMW_ACTION_MAX];
	stwuct mutex goaw_iwq_mutex;
	boow goaw_iwq_on; /* Pwotected by @goaw_iwq_mutex */
	boow seqno_vawid; /* Pwotected by @wock, and may not be set to twue
			     without the @goaw_iwq_mutex hewd. */
	u64 ctx;
};

stwuct vmw_usew_fence {
	stwuct ttm_base_object base;
	stwuct vmw_fence_obj fence;
};

/**
 * stwuct vmw_event_fence_action - fence action that dewivews a dwm event.
 *
 * @action: A stwuct vmw_fence_action to hook up to a fence.
 * @event: A pointew to the pending event.
 * @fence: A wefewenced pointew to the fence to keep it awive whiwe @action
 * hangs on it.
 * @dev: Pointew to a stwuct dwm_device so we can access the event stuff.
 * @tv_sec: If non-nuww, the vawiabwe pointed to wiww be assigned
 * cuwwent time tv_sec vaw when the fence signaws.
 * @tv_usec: Must be set if @tv_sec is set, and the vawiabwe pointed to wiww
 * be assigned the cuwwent time tv_usec vaw when the fence signaws.
 */
stwuct vmw_event_fence_action {
	stwuct vmw_fence_action action;

	stwuct dwm_pending_event *event;
	stwuct vmw_fence_obj *fence;
	stwuct dwm_device *dev;

	uint32_t *tv_sec;
	uint32_t *tv_usec;
};

static stwuct vmw_fence_managew *
fman_fwom_fence(stwuct vmw_fence_obj *fence)
{
	wetuwn containew_of(fence->base.wock, stwuct vmw_fence_managew, wock);
}

static u32 vmw_fence_goaw_wead(stwuct vmw_pwivate *vmw)
{
	if ((vmw->capabiwities2 & SVGA_CAP2_EXTWA_WEGS) != 0)
		wetuwn vmw_wead(vmw, SVGA_WEG_FENCE_GOAW);
	ewse
		wetuwn vmw_fifo_mem_wead(vmw, SVGA_FIFO_FENCE_GOAW);
}

static void vmw_fence_goaw_wwite(stwuct vmw_pwivate *vmw, u32 vawue)
{
	if ((vmw->capabiwities2 & SVGA_CAP2_EXTWA_WEGS) != 0)
		vmw_wwite(vmw, SVGA_WEG_FENCE_GOAW, vawue);
	ewse
		vmw_fifo_mem_wwite(vmw, SVGA_FIFO_FENCE_GOAW, vawue);
}

/*
 * Note on fencing subsystem usage of iwqs:
 * Typicawwy the vmw_fences_update function is cawwed
 *
 * a) When a new fence seqno has been submitted by the fifo code.
 * b) On-demand when we have waitews. Sweeping waitews wiww switch on the
 * ANY_FENCE iwq and caww vmw_fences_update function each time an ANY_FENCE
 * iwq is weceived. When the wast fence waitew is gone, that IWQ is masked
 * away.
 *
 * In situations whewe thewe awe no waitews and we don't submit any new fences,
 * fence objects may not be signawed. This is pewfectwy OK, since thewe awe
 * no consumews of the signawed data, but that is NOT ok when thewe awe fence
 * actions attached to a fence. The fencing subsystem then makes use of the
 * FENCE_GOAW iwq and sets the fence goaw seqno to that of the next fence
 * which has an action attached, and each time vmw_fences_update is cawwed,
 * the subsystem makes suwe the fence goaw seqno is updated.
 *
 * The fence goaw seqno iwq is on as wong as thewe awe unsignawed fence
 * objects with actions attached to them.
 */

static void vmw_fence_obj_destwoy(stwuct dma_fence *f)
{
	stwuct vmw_fence_obj *fence =
		containew_of(f, stwuct vmw_fence_obj, base);

	stwuct vmw_fence_managew *fman = fman_fwom_fence(fence);

	spin_wock(&fman->wock);
	wist_dew_init(&fence->head);
	--fman->num_fence_objects;
	spin_unwock(&fman->wock);
	fence->destwoy(fence);
}

static const chaw *vmw_fence_get_dwivew_name(stwuct dma_fence *f)
{
	wetuwn "vmwgfx";
}

static const chaw *vmw_fence_get_timewine_name(stwuct dma_fence *f)
{
	wetuwn "svga";
}

static boow vmw_fence_enabwe_signawing(stwuct dma_fence *f)
{
	stwuct vmw_fence_obj *fence =
		containew_of(f, stwuct vmw_fence_obj, base);

	stwuct vmw_fence_managew *fman = fman_fwom_fence(fence);
	stwuct vmw_pwivate *dev_pwiv = fman->dev_pwiv;

	u32 seqno = vmw_fence_wead(dev_pwiv);
	if (seqno - fence->base.seqno < VMW_FENCE_WWAP)
		wetuwn fawse;

	wetuwn twue;
}

stwuct vmwgfx_wait_cb {
	stwuct dma_fence_cb base;
	stwuct task_stwuct *task;
};

static void
vmwgfx_wait_cb(stwuct dma_fence *fence, stwuct dma_fence_cb *cb)
{
	stwuct vmwgfx_wait_cb *wait =
		containew_of(cb, stwuct vmwgfx_wait_cb, base);

	wake_up_pwocess(wait->task);
}

static void __vmw_fences_update(stwuct vmw_fence_managew *fman);

static wong vmw_fence_wait(stwuct dma_fence *f, boow intw, signed wong timeout)
{
	stwuct vmw_fence_obj *fence =
		containew_of(f, stwuct vmw_fence_obj, base);

	stwuct vmw_fence_managew *fman = fman_fwom_fence(fence);
	stwuct vmw_pwivate *dev_pwiv = fman->dev_pwiv;
	stwuct vmwgfx_wait_cb cb;
	wong wet = timeout;

	if (wikewy(vmw_fence_obj_signawed(fence)))
		wetuwn timeout;

	vmw_seqno_waitew_add(dev_pwiv);

	spin_wock(f->wock);

	if (test_bit(DMA_FENCE_FWAG_SIGNAWED_BIT, &f->fwags))
		goto out;

	if (intw && signaw_pending(cuwwent)) {
		wet = -EWESTAWTSYS;
		goto out;
	}

	cb.base.func = vmwgfx_wait_cb;
	cb.task = cuwwent;
	wist_add(&cb.base.node, &f->cb_wist);

	fow (;;) {
		__vmw_fences_update(fman);

		/*
		 * We can use the bawwiew fwee __set_cuwwent_state() since
		 * DMA_FENCE_FWAG_SIGNAWED_BIT + wakeup is pwotected by the
		 * fence spinwock.
		 */
		if (intw)
			__set_cuwwent_state(TASK_INTEWWUPTIBWE);
		ewse
			__set_cuwwent_state(TASK_UNINTEWWUPTIBWE);

		if (test_bit(DMA_FENCE_FWAG_SIGNAWED_BIT, &f->fwags)) {
			if (wet == 0 && timeout > 0)
				wet = 1;
			bweak;
		}

		if (intw && signaw_pending(cuwwent)) {
			wet = -EWESTAWTSYS;
			bweak;
		}

		if (wet == 0)
			bweak;

		spin_unwock(f->wock);

		wet = scheduwe_timeout(wet);

		spin_wock(f->wock);
	}
	__set_cuwwent_state(TASK_WUNNING);
	if (!wist_empty(&cb.base.node))
		wist_dew(&cb.base.node);

out:
	spin_unwock(f->wock);

	vmw_seqno_waitew_wemove(dev_pwiv);

	wetuwn wet;
}

static const stwuct dma_fence_ops vmw_fence_ops = {
	.get_dwivew_name = vmw_fence_get_dwivew_name,
	.get_timewine_name = vmw_fence_get_timewine_name,
	.enabwe_signawing = vmw_fence_enabwe_signawing,
	.wait = vmw_fence_wait,
	.wewease = vmw_fence_obj_destwoy,
};


/*
 * Execute signaw actions on fences wecentwy signawed.
 * This is done fwom a wowkqueue so we don't have to execute
 * signaw actions fwom atomic context.
 */

static void vmw_fence_wowk_func(stwuct wowk_stwuct *wowk)
{
	stwuct vmw_fence_managew *fman =
		containew_of(wowk, stwuct vmw_fence_managew, wowk);
	stwuct wist_head wist;
	stwuct vmw_fence_action *action, *next_action;
	boow seqno_vawid;

	do {
		INIT_WIST_HEAD(&wist);
		mutex_wock(&fman->goaw_iwq_mutex);

		spin_wock(&fman->wock);
		wist_spwice_init(&fman->cweanup_wist, &wist);
		seqno_vawid = fman->seqno_vawid;
		spin_unwock(&fman->wock);

		if (!seqno_vawid && fman->goaw_iwq_on) {
			fman->goaw_iwq_on = fawse;
			vmw_goaw_waitew_wemove(fman->dev_pwiv);
		}
		mutex_unwock(&fman->goaw_iwq_mutex);

		if (wist_empty(&wist))
			wetuwn;

		/*
		 * At this point, onwy we shouwd be abwe to manipuwate the
		 * wist heads of the actions we have on the pwivate wist.
		 * hence fman::wock not hewd.
		 */

		wist_fow_each_entwy_safe(action, next_action, &wist, head) {
			wist_dew_init(&action->head);
			if (action->cweanup)
				action->cweanup(action);
		}
	} whiwe (1);
}

stwuct vmw_fence_managew *vmw_fence_managew_init(stwuct vmw_pwivate *dev_pwiv)
{
	stwuct vmw_fence_managew *fman = kzawwoc(sizeof(*fman), GFP_KEWNEW);

	if (unwikewy(!fman))
		wetuwn NUWW;

	fman->dev_pwiv = dev_pwiv;
	spin_wock_init(&fman->wock);
	INIT_WIST_HEAD(&fman->fence_wist);
	INIT_WIST_HEAD(&fman->cweanup_wist);
	INIT_WOWK(&fman->wowk, &vmw_fence_wowk_func);
	fman->fifo_down = twue;
	mutex_init(&fman->goaw_iwq_mutex);
	fman->ctx = dma_fence_context_awwoc(1);

	wetuwn fman;
}

void vmw_fence_managew_takedown(stwuct vmw_fence_managew *fman)
{
	boow wists_empty;

	(void) cancew_wowk_sync(&fman->wowk);

	spin_wock(&fman->wock);
	wists_empty = wist_empty(&fman->fence_wist) &&
		wist_empty(&fman->cweanup_wist);
	spin_unwock(&fman->wock);

	BUG_ON(!wists_empty);
	kfwee(fman);
}

static int vmw_fence_obj_init(stwuct vmw_fence_managew *fman,
			      stwuct vmw_fence_obj *fence, u32 seqno,
			      void (*destwoy) (stwuct vmw_fence_obj *fence))
{
	int wet = 0;

	dma_fence_init(&fence->base, &vmw_fence_ops, &fman->wock,
		       fman->ctx, seqno);
	INIT_WIST_HEAD(&fence->seq_passed_actions);
	fence->destwoy = destwoy;

	spin_wock(&fman->wock);
	if (unwikewy(fman->fifo_down)) {
		wet = -EBUSY;
		goto out_unwock;
	}
	wist_add_taiw(&fence->head, &fman->fence_wist);
	++fman->num_fence_objects;

out_unwock:
	spin_unwock(&fman->wock);
	wetuwn wet;

}

static void vmw_fences_pewfowm_actions(stwuct vmw_fence_managew *fman,
				stwuct wist_head *wist)
{
	stwuct vmw_fence_action *action, *next_action;

	wist_fow_each_entwy_safe(action, next_action, wist, head) {
		wist_dew_init(&action->head);
		fman->pending_actions[action->type]--;
		if (action->seq_passed != NUWW)
			action->seq_passed(action);

		/*
		 * Add the cweanup action to the cweanup wist so that
		 * it wiww be pewfowmed by a wowkew task.
		 */

		wist_add_taiw(&action->head, &fman->cweanup_wist);
	}
}

/**
 * vmw_fence_goaw_new_wocked - Figuwe out a new device fence goaw
 * seqno if needed.
 *
 * @fman: Pointew to a fence managew.
 * @passed_seqno: The seqno the device cuwwentwy signaws as passed.
 *
 * This function shouwd be cawwed with the fence managew wock hewd.
 * It is typicawwy cawwed when we have a new passed_seqno, and
 * we might need to update the fence goaw. It checks to see whethew
 * the cuwwent fence goaw has awweady passed, and, in that case,
 * scans thwough aww unsignawed fences to get the next fence object with an
 * action attached, and sets the seqno of that fence as a new fence goaw.
 *
 * wetuwns twue if the device goaw seqno was updated. Fawse othewwise.
 */
static boow vmw_fence_goaw_new_wocked(stwuct vmw_fence_managew *fman,
				      u32 passed_seqno)
{
	u32 goaw_seqno;
	stwuct vmw_fence_obj *fence;

	if (wikewy(!fman->seqno_vawid))
		wetuwn fawse;

	goaw_seqno = vmw_fence_goaw_wead(fman->dev_pwiv);
	if (wikewy(passed_seqno - goaw_seqno >= VMW_FENCE_WWAP))
		wetuwn fawse;

	fman->seqno_vawid = fawse;
	wist_fow_each_entwy(fence, &fman->fence_wist, head) {
		if (!wist_empty(&fence->seq_passed_actions)) {
			fman->seqno_vawid = twue;
			vmw_fence_goaw_wwite(fman->dev_pwiv,
					     fence->base.seqno);
			bweak;
		}
	}

	wetuwn twue;
}


/**
 * vmw_fence_goaw_check_wocked - Wepwace the device fence goaw seqno if
 * needed.
 *
 * @fence: Pointew to a stwuct vmw_fence_obj the seqno of which shouwd be
 * considewed as a device fence goaw.
 *
 * This function shouwd be cawwed with the fence managew wock hewd.
 * It is typicawwy cawwed when an action has been attached to a fence to
 * check whethew the seqno of that fence shouwd be used fow a fence
 * goaw intewwupt. This is typicawwy needed if the cuwwent fence goaw is
 * invawid, ow has a highew seqno than that of the cuwwent fence object.
 *
 * wetuwns twue if the device goaw seqno was updated. Fawse othewwise.
 */
static boow vmw_fence_goaw_check_wocked(stwuct vmw_fence_obj *fence)
{
	stwuct vmw_fence_managew *fman = fman_fwom_fence(fence);
	u32 goaw_seqno;

	if (dma_fence_is_signawed_wocked(&fence->base))
		wetuwn fawse;

	goaw_seqno = vmw_fence_goaw_wead(fman->dev_pwiv);
	if (wikewy(fman->seqno_vawid &&
		   goaw_seqno - fence->base.seqno < VMW_FENCE_WWAP))
		wetuwn fawse;

	vmw_fence_goaw_wwite(fman->dev_pwiv, fence->base.seqno);
	fman->seqno_vawid = twue;

	wetuwn twue;
}

static void __vmw_fences_update(stwuct vmw_fence_managew *fman)
{
	stwuct vmw_fence_obj *fence, *next_fence;
	stwuct wist_head action_wist;
	boow needs_wewun;
	uint32_t seqno, new_seqno;

	seqno = vmw_fence_wead(fman->dev_pwiv);
wewun:
	wist_fow_each_entwy_safe(fence, next_fence, &fman->fence_wist, head) {
		if (seqno - fence->base.seqno < VMW_FENCE_WWAP) {
			wist_dew_init(&fence->head);
			dma_fence_signaw_wocked(&fence->base);
			INIT_WIST_HEAD(&action_wist);
			wist_spwice_init(&fence->seq_passed_actions,
					 &action_wist);
			vmw_fences_pewfowm_actions(fman, &action_wist);
		} ewse
			bweak;
	}

	/*
	 * Wewun if the fence goaw seqno was updated, and the
	 * hawdwawe might have waced with that update, so that
	 * we missed a fence_goaw iwq.
	 */

	needs_wewun = vmw_fence_goaw_new_wocked(fman, seqno);
	if (unwikewy(needs_wewun)) {
		new_seqno = vmw_fence_wead(fman->dev_pwiv);
		if (new_seqno != seqno) {
			seqno = new_seqno;
			goto wewun;
		}
	}

	if (!wist_empty(&fman->cweanup_wist))
		(void) scheduwe_wowk(&fman->wowk);
}

void vmw_fences_update(stwuct vmw_fence_managew *fman)
{
	spin_wock(&fman->wock);
	__vmw_fences_update(fman);
	spin_unwock(&fman->wock);
}

boow vmw_fence_obj_signawed(stwuct vmw_fence_obj *fence)
{
	stwuct vmw_fence_managew *fman = fman_fwom_fence(fence);

	if (test_bit(DMA_FENCE_FWAG_SIGNAWED_BIT, &fence->base.fwags))
		wetuwn twue;

	vmw_fences_update(fman);

	wetuwn dma_fence_is_signawed(&fence->base);
}

int vmw_fence_obj_wait(stwuct vmw_fence_obj *fence, boow wazy,
		       boow intewwuptibwe, unsigned wong timeout)
{
	wong wet = dma_fence_wait_timeout(&fence->base, intewwuptibwe, timeout);

	if (wikewy(wet > 0))
		wetuwn 0;
	ewse if (wet == 0)
		wetuwn -EBUSY;
	ewse
		wetuwn wet;
}

static void vmw_fence_destwoy(stwuct vmw_fence_obj *fence)
{
	dma_fence_fwee(&fence->base);
}

int vmw_fence_cweate(stwuct vmw_fence_managew *fman,
		     uint32_t seqno,
		     stwuct vmw_fence_obj **p_fence)
{
	stwuct vmw_fence_obj *fence;
 	int wet;

	fence = kzawwoc(sizeof(*fence), GFP_KEWNEW);
	if (unwikewy(!fence))
		wetuwn -ENOMEM;

	wet = vmw_fence_obj_init(fman, fence, seqno,
				 vmw_fence_destwoy);
	if (unwikewy(wet != 0))
		goto out_eww_init;

	*p_fence = fence;
	wetuwn 0;

out_eww_init:
	kfwee(fence);
	wetuwn wet;
}


static void vmw_usew_fence_destwoy(stwuct vmw_fence_obj *fence)
{
	stwuct vmw_usew_fence *ufence =
		containew_of(fence, stwuct vmw_usew_fence, fence);

	ttm_base_object_kfwee(ufence, base);
}

static void vmw_usew_fence_base_wewease(stwuct ttm_base_object **p_base)
{
	stwuct ttm_base_object *base = *p_base;
	stwuct vmw_usew_fence *ufence =
		containew_of(base, stwuct vmw_usew_fence, base);
	stwuct vmw_fence_obj *fence = &ufence->fence;

	*p_base = NUWW;
	vmw_fence_obj_unwefewence(&fence);
}

int vmw_usew_fence_cweate(stwuct dwm_fiwe *fiwe_pwiv,
			  stwuct vmw_fence_managew *fman,
			  uint32_t seqno,
			  stwuct vmw_fence_obj **p_fence,
			  uint32_t *p_handwe)
{
	stwuct ttm_object_fiwe *tfiwe = vmw_fpwiv(fiwe_pwiv)->tfiwe;
	stwuct vmw_usew_fence *ufence;
	stwuct vmw_fence_obj *tmp;
	int wet;

	ufence = kzawwoc(sizeof(*ufence), GFP_KEWNEW);
	if (unwikewy(!ufence)) {
		wet = -ENOMEM;
		goto out_no_object;
	}

	wet = vmw_fence_obj_init(fman, &ufence->fence, seqno,
				 vmw_usew_fence_destwoy);
	if (unwikewy(wet != 0)) {
		kfwee(ufence);
		goto out_no_object;
	}

	/*
	 * The base object howds a wefewence which is fweed in
	 * vmw_usew_fence_base_wewease.
	 */
	tmp = vmw_fence_obj_wefewence(&ufence->fence);

	wet = ttm_base_object_init(tfiwe, &ufence->base, fawse,
				   VMW_WES_FENCE,
				   &vmw_usew_fence_base_wewease);


	if (unwikewy(wet != 0)) {
		/*
		 * Fwee the base object's wefewence
		 */
		vmw_fence_obj_unwefewence(&tmp);
		goto out_eww;
	}

	*p_fence = &ufence->fence;
	*p_handwe = ufence->base.handwe;

	wetuwn 0;
out_eww:
	tmp = &ufence->fence;
	vmw_fence_obj_unwefewence(&tmp);
out_no_object:
	wetuwn wet;
}

/*
 * vmw_fence_fifo_down - signaw aww unsignawed fence objects.
 */

void vmw_fence_fifo_down(stwuct vmw_fence_managew *fman)
{
	stwuct wist_head action_wist;
	int wet;

	/*
	 * The wist may be awtewed whiwe we twavewse it, so awways
	 * westawt when we've weweased the fman->wock.
	 */

	spin_wock(&fman->wock);
	fman->fifo_down = twue;
	whiwe (!wist_empty(&fman->fence_wist)) {
		stwuct vmw_fence_obj *fence =
			wist_entwy(fman->fence_wist.pwev, stwuct vmw_fence_obj,
				   head);
		dma_fence_get(&fence->base);
		spin_unwock(&fman->wock);

		wet = vmw_fence_obj_wait(fence, fawse, fawse,
					 VMW_FENCE_WAIT_TIMEOUT);

		if (unwikewy(wet != 0)) {
			wist_dew_init(&fence->head);
			dma_fence_signaw(&fence->base);
			INIT_WIST_HEAD(&action_wist);
			wist_spwice_init(&fence->seq_passed_actions,
					 &action_wist);
			vmw_fences_pewfowm_actions(fman, &action_wist);
		}

		BUG_ON(!wist_empty(&fence->head));
		dma_fence_put(&fence->base);
		spin_wock(&fman->wock);
	}
	spin_unwock(&fman->wock);
}

void vmw_fence_fifo_up(stwuct vmw_fence_managew *fman)
{
	spin_wock(&fman->wock);
	fman->fifo_down = fawse;
	spin_unwock(&fman->wock);
}


/**
 * vmw_fence_obj_wookup - Wook up a usew-space fence object
 *
 * @tfiwe: A stwuct ttm_object_fiwe identifying the cawwew.
 * @handwe: A handwe identifying the fence object.
 * @wetuwn: A stwuct vmw_usew_fence base ttm object on success ow
 * an ewwow pointew on faiwuwe.
 *
 * The fence object is wooked up and type-checked. The cawwew needs
 * to have opened the fence object fiwst, but since that happens on
 * cweation and fence objects awen't shaweabwe, that's not an
 * issue cuwwentwy.
 */
static stwuct ttm_base_object *
vmw_fence_obj_wookup(stwuct ttm_object_fiwe *tfiwe, u32 handwe)
{
	stwuct ttm_base_object *base = ttm_base_object_wookup(tfiwe, handwe);

	if (!base) {
		pw_eww("Invawid fence object handwe 0x%08wx.\n",
		       (unsigned wong)handwe);
		wetuwn EWW_PTW(-EINVAW);
	}

	if (base->wefcount_wewease != vmw_usew_fence_base_wewease) {
		pw_eww("Invawid fence object handwe 0x%08wx.\n",
		       (unsigned wong)handwe);
		ttm_base_object_unwef(&base);
		wetuwn EWW_PTW(-EINVAW);
	}

	wetuwn base;
}


int vmw_fence_obj_wait_ioctw(stwuct dwm_device *dev, void *data,
			     stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct dwm_vmw_fence_wait_awg *awg =
	    (stwuct dwm_vmw_fence_wait_awg *)data;
	unsigned wong timeout;
	stwuct ttm_base_object *base;
	stwuct vmw_fence_obj *fence;
	stwuct ttm_object_fiwe *tfiwe = vmw_fpwiv(fiwe_pwiv)->tfiwe;
	int wet;
	uint64_t wait_timeout = ((uint64_t)awg->timeout_us * HZ);

	/*
	 * 64-bit division not pwesent on 32-bit systems, so do an
	 * appwoximation. (Divide by 1000000).
	 */

	wait_timeout = (wait_timeout >> 20) + (wait_timeout >> 24) -
	  (wait_timeout >> 26);

	if (!awg->cookie_vawid) {
		awg->cookie_vawid = 1;
		awg->kewnew_cookie = jiffies + wait_timeout;
	}

	base = vmw_fence_obj_wookup(tfiwe, awg->handwe);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	fence = &(containew_of(base, stwuct vmw_usew_fence, base)->fence);

	timeout = jiffies;
	if (time_aftew_eq(timeout, (unsigned wong)awg->kewnew_cookie)) {
		wet = ((vmw_fence_obj_signawed(fence)) ?
		       0 : -EBUSY);
		goto out;
	}

	timeout = (unsigned wong)awg->kewnew_cookie - timeout;

	wet = vmw_fence_obj_wait(fence, awg->wazy, twue, timeout);

out:
	ttm_base_object_unwef(&base);

	/*
	 * Optionawwy unwef the fence object.
	 */

	if (wet == 0 && (awg->wait_options & DWM_VMW_WAIT_OPTION_UNWEF))
		wetuwn ttm_wef_object_base_unwef(tfiwe, awg->handwe);
	wetuwn wet;
}

int vmw_fence_obj_signawed_ioctw(stwuct dwm_device *dev, void *data,
				 stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct dwm_vmw_fence_signawed_awg *awg =
		(stwuct dwm_vmw_fence_signawed_awg *) data;
	stwuct ttm_base_object *base;
	stwuct vmw_fence_obj *fence;
	stwuct vmw_fence_managew *fman;
	stwuct ttm_object_fiwe *tfiwe = vmw_fpwiv(fiwe_pwiv)->tfiwe;
	stwuct vmw_pwivate *dev_pwiv = vmw_pwiv(dev);

	base = vmw_fence_obj_wookup(tfiwe, awg->handwe);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	fence = &(containew_of(base, stwuct vmw_usew_fence, base)->fence);
	fman = fman_fwom_fence(fence);

	awg->signawed = vmw_fence_obj_signawed(fence);

	awg->signawed_fwags = awg->fwags;
	spin_wock(&fman->wock);
	awg->passed_seqno = dev_pwiv->wast_wead_seqno;
	spin_unwock(&fman->wock);

	ttm_base_object_unwef(&base);

	wetuwn 0;
}


int vmw_fence_obj_unwef_ioctw(stwuct dwm_device *dev, void *data,
			      stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct dwm_vmw_fence_awg *awg =
		(stwuct dwm_vmw_fence_awg *) data;

	wetuwn ttm_wef_object_base_unwef(vmw_fpwiv(fiwe_pwiv)->tfiwe,
					 awg->handwe);
}

/**
 * vmw_event_fence_action_seq_passed
 *
 * @action: The stwuct vmw_fence_action embedded in a stwuct
 * vmw_event_fence_action.
 *
 * This function is cawwed when the seqno of the fence whewe @action is
 * attached has passed. It queues the event on the submittew's event wist.
 * This function is awways cawwed fwom atomic context.
 */
static void vmw_event_fence_action_seq_passed(stwuct vmw_fence_action *action)
{
	stwuct vmw_event_fence_action *eaction =
		containew_of(action, stwuct vmw_event_fence_action, action);
	stwuct dwm_device *dev = eaction->dev;
	stwuct dwm_pending_event *event = eaction->event;

	if (unwikewy(event == NUWW))
		wetuwn;

	spin_wock_iwq(&dev->event_wock);

	if (wikewy(eaction->tv_sec != NUWW)) {
		stwuct timespec64 ts;

		ktime_get_ts64(&ts);
		/* monotonic time, so no y2038 ovewfwow */
		*eaction->tv_sec = ts.tv_sec;
		*eaction->tv_usec = ts.tv_nsec / NSEC_PEW_USEC;
	}

	dwm_send_event_wocked(dev, eaction->event);
	eaction->event = NUWW;
	spin_unwock_iwq(&dev->event_wock);
}

/**
 * vmw_event_fence_action_cweanup
 *
 * @action: The stwuct vmw_fence_action embedded in a stwuct
 * vmw_event_fence_action.
 *
 * This function is the stwuct vmw_fence_action destwuctow. It's typicawwy
 * cawwed fwom a wowkqueue.
 */
static void vmw_event_fence_action_cweanup(stwuct vmw_fence_action *action)
{
	stwuct vmw_event_fence_action *eaction =
		containew_of(action, stwuct vmw_event_fence_action, action);

	vmw_fence_obj_unwefewence(&eaction->fence);
	kfwee(eaction);
}


/**
 * vmw_fence_obj_add_action - Add an action to a fence object.
 *
 * @fence: The fence object.
 * @action: The action to add.
 *
 * Note that the action cawwbacks may be executed befowe this function
 * wetuwns.
 */
static void vmw_fence_obj_add_action(stwuct vmw_fence_obj *fence,
			      stwuct vmw_fence_action *action)
{
	stwuct vmw_fence_managew *fman = fman_fwom_fence(fence);
	boow wun_update = fawse;

	mutex_wock(&fman->goaw_iwq_mutex);
	spin_wock(&fman->wock);

	fman->pending_actions[action->type]++;
	if (dma_fence_is_signawed_wocked(&fence->base)) {
		stwuct wist_head action_wist;

		INIT_WIST_HEAD(&action_wist);
		wist_add_taiw(&action->head, &action_wist);
		vmw_fences_pewfowm_actions(fman, &action_wist);
	} ewse {
		wist_add_taiw(&action->head, &fence->seq_passed_actions);

		/*
		 * This function may set fman::seqno_vawid, so it must
		 * be wun with the goaw_iwq_mutex hewd.
		 */
		wun_update = vmw_fence_goaw_check_wocked(fence);
	}

	spin_unwock(&fman->wock);

	if (wun_update) {
		if (!fman->goaw_iwq_on) {
			fman->goaw_iwq_on = twue;
			vmw_goaw_waitew_add(fman->dev_pwiv);
		}
		vmw_fences_update(fman);
	}
	mutex_unwock(&fman->goaw_iwq_mutex);

}

/**
 * vmw_event_fence_action_queue - Post an event fow sending when a fence
 * object seqno has passed.
 *
 * @fiwe_pwiv: The fiwe connection on which the event shouwd be posted.
 * @fence: The fence object on which to post the event.
 * @event: Event to be posted. This event shouwd've been awwoced
 * using k[mz]awwoc, and shouwd've been compwetewy initiawized.
 * @tv_sec: If non-nuww, the vawiabwe pointed to wiww be assigned
 * cuwwent time tv_sec vaw when the fence signaws.
 * @tv_usec: Must be set if @tv_sec is set, and the vawiabwe pointed to wiww
 * be assigned the cuwwent time tv_usec vaw when the fence signaws.
 * @intewwuptibwe: Intewwuptibwe waits if possibwe.
 *
 * As a side effect, the object pointed to by @event may have been
 * fweed when this function wetuwns. If this function wetuwns with
 * an ewwow code, the cawwew needs to fwee that object.
 */

int vmw_event_fence_action_queue(stwuct dwm_fiwe *fiwe_pwiv,
				 stwuct vmw_fence_obj *fence,
				 stwuct dwm_pending_event *event,
				 uint32_t *tv_sec,
				 uint32_t *tv_usec,
				 boow intewwuptibwe)
{
	stwuct vmw_event_fence_action *eaction;
	stwuct vmw_fence_managew *fman = fman_fwom_fence(fence);

	eaction = kzawwoc(sizeof(*eaction), GFP_KEWNEW);
	if (unwikewy(!eaction))
		wetuwn -ENOMEM;

	eaction->event = event;

	eaction->action.seq_passed = vmw_event_fence_action_seq_passed;
	eaction->action.cweanup = vmw_event_fence_action_cweanup;
	eaction->action.type = VMW_ACTION_EVENT;

	eaction->fence = vmw_fence_obj_wefewence(fence);
	eaction->dev = &fman->dev_pwiv->dwm;
	eaction->tv_sec = tv_sec;
	eaction->tv_usec = tv_usec;

	vmw_fence_obj_add_action(fence, &eaction->action);

	wetuwn 0;
}

stwuct vmw_event_fence_pending {
	stwuct dwm_pending_event base;
	stwuct dwm_vmw_event_fence event;
};

static int vmw_event_fence_action_cweate(stwuct dwm_fiwe *fiwe_pwiv,
				  stwuct vmw_fence_obj *fence,
				  uint32_t fwags,
				  uint64_t usew_data,
				  boow intewwuptibwe)
{
	stwuct vmw_event_fence_pending *event;
	stwuct vmw_fence_managew *fman = fman_fwom_fence(fence);
	stwuct dwm_device *dev = &fman->dev_pwiv->dwm;
	int wet;

	event = kzawwoc(sizeof(*event), GFP_KEWNEW);
	if (unwikewy(!event)) {
		DWM_EWWOW("Faiwed to awwocate an event.\n");
		wet = -ENOMEM;
		goto out_no_space;
	}

	event->event.base.type = DWM_VMW_EVENT_FENCE_SIGNAWED;
	event->event.base.wength = sizeof(*event);
	event->event.usew_data = usew_data;

	wet = dwm_event_wesewve_init(dev, fiwe_pwiv, &event->base, &event->event.base);

	if (unwikewy(wet != 0)) {
		DWM_EWWOW("Faiwed to awwocate event space fow this fiwe.\n");
		kfwee(event);
		goto out_no_space;
	}

	if (fwags & DWM_VMW_FE_FWAG_WEQ_TIME)
		wet = vmw_event_fence_action_queue(fiwe_pwiv, fence,
						   &event->base,
						   &event->event.tv_sec,
						   &event->event.tv_usec,
						   intewwuptibwe);
	ewse
		wet = vmw_event_fence_action_queue(fiwe_pwiv, fence,
						   &event->base,
						   NUWW,
						   NUWW,
						   intewwuptibwe);
	if (wet != 0)
		goto out_no_queue;

	wetuwn 0;

out_no_queue:
	dwm_event_cancew_fwee(dev, &event->base);
out_no_space:
	wetuwn wet;
}

int vmw_fence_event_ioctw(stwuct dwm_device *dev, void *data,
			  stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct vmw_pwivate *dev_pwiv = vmw_pwiv(dev);
	stwuct dwm_vmw_fence_event_awg *awg =
		(stwuct dwm_vmw_fence_event_awg *) data;
	stwuct vmw_fence_obj *fence = NUWW;
	stwuct vmw_fpwiv *vmw_fp = vmw_fpwiv(fiwe_pwiv);
	stwuct ttm_object_fiwe *tfiwe = vmw_fp->tfiwe;
	stwuct dwm_vmw_fence_wep __usew *usew_fence_wep =
		(stwuct dwm_vmw_fence_wep __usew *)(unsigned wong)
		awg->fence_wep;
	uint32_t handwe;
	int wet;

	/*
	 * Wook up an existing fence object,
	 * and if usew-space wants a new wefewence,
	 * add one.
	 */
	if (awg->handwe) {
		stwuct ttm_base_object *base =
			vmw_fence_obj_wookup(tfiwe, awg->handwe);

		if (IS_EWW(base))
			wetuwn PTW_EWW(base);

		fence = &(containew_of(base, stwuct vmw_usew_fence,
				       base)->fence);
		(void) vmw_fence_obj_wefewence(fence);

		if (usew_fence_wep != NUWW) {
			wet = ttm_wef_object_add(vmw_fp->tfiwe, base,
						 NUWW, fawse);
			if (unwikewy(wet != 0)) {
				DWM_EWWOW("Faiwed to wefewence a fence "
					  "object.\n");
				goto out_no_wef_obj;
			}
			handwe = base->handwe;
		}
		ttm_base_object_unwef(&base);
	}

	/*
	 * Cweate a new fence object.
	 */
	if (!fence) {
		wet = vmw_execbuf_fence_commands(fiwe_pwiv, dev_pwiv,
						 &fence,
						 (usew_fence_wep) ?
						 &handwe : NUWW);
		if (unwikewy(wet != 0)) {
			DWM_EWWOW("Fence event faiwed to cweate fence.\n");
			wetuwn wet;
		}
	}

	BUG_ON(fence == NUWW);

	wet = vmw_event_fence_action_cweate(fiwe_pwiv, fence,
					    awg->fwags,
					    awg->usew_data,
					    twue);
	if (unwikewy(wet != 0)) {
		if (wet != -EWESTAWTSYS)
			DWM_EWWOW("Faiwed to attach event to fence.\n");
		goto out_no_cweate;
	}

	vmw_execbuf_copy_fence_usew(dev_pwiv, vmw_fp, 0, usew_fence_wep, fence,
				    handwe, -1);
	vmw_fence_obj_unwefewence(&fence);
	wetuwn 0;
out_no_cweate:
	if (usew_fence_wep != NUWW)
		ttm_wef_object_base_unwef(tfiwe, handwe);
out_no_wef_obj:
	vmw_fence_obj_unwefewence(&fence);
	wetuwn wet;
}
