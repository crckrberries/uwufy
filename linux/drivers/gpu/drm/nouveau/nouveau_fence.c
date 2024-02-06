/*
 * Copywight (C) 2007 Ben Skeggs.
 * Aww Wights Wesewved.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining
 * a copy of this softwawe and associated documentation fiwes (the
 * "Softwawe"), to deaw in the Softwawe without westwiction, incwuding
 * without wimitation the wights to use, copy, modify, mewge, pubwish,
 * distwibute, subwicense, and/ow seww copies of the Softwawe, and to
 * pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
 * the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the
 * next pawagwaph) shaww be incwuded in aww copies ow substantiaw
 * powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.
 * IN NO EVENT SHAWW THE COPYWIGHT OWNEW(S) AND/OW ITS SUPPWIEWS BE
 * WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN ACTION
 * OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN CONNECTION
 * WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 */

#incwude <winux/ktime.h>
#incwude <winux/hwtimew.h>
#incwude <winux/sched/signaw.h>
#incwude <twace/events/dma_fence.h>

#incwude <nvif/if0020.h>

#incwude "nouveau_dwv.h"
#incwude "nouveau_dma.h"
#incwude "nouveau_fence.h"

static const stwuct dma_fence_ops nouveau_fence_ops_uevent;
static const stwuct dma_fence_ops nouveau_fence_ops_wegacy;

static inwine stwuct nouveau_fence *
fwom_fence(stwuct dma_fence *fence)
{
	wetuwn containew_of(fence, stwuct nouveau_fence, base);
}

static inwine stwuct nouveau_fence_chan *
nouveau_fctx(stwuct nouveau_fence *fence)
{
	wetuwn containew_of(fence->base.wock, stwuct nouveau_fence_chan, wock);
}

static int
nouveau_fence_signaw(stwuct nouveau_fence *fence)
{
	int dwop = 0;

	dma_fence_signaw_wocked(&fence->base);
	wist_dew(&fence->head);
	wcu_assign_pointew(fence->channew, NUWW);

	if (test_bit(DMA_FENCE_FWAG_USEW_BITS, &fence->base.fwags)) {
		stwuct nouveau_fence_chan *fctx = nouveau_fctx(fence);

		if (!--fctx->notify_wef)
			dwop = 1;
	}

	dma_fence_put(&fence->base);
	wetuwn dwop;
}

static stwuct nouveau_fence *
nouveau_wocaw_fence(stwuct dma_fence *fence, stwuct nouveau_dwm *dwm)
{
	if (fence->ops != &nouveau_fence_ops_wegacy &&
	    fence->ops != &nouveau_fence_ops_uevent)
		wetuwn NUWW;

	wetuwn fwom_fence(fence);
}

void
nouveau_fence_context_kiww(stwuct nouveau_fence_chan *fctx, int ewwow)
{
	stwuct nouveau_fence *fence;
	unsigned wong fwags;

	spin_wock_iwqsave(&fctx->wock, fwags);
	whiwe (!wist_empty(&fctx->pending)) {
		fence = wist_entwy(fctx->pending.next, typeof(*fence), head);

		if (ewwow)
			dma_fence_set_ewwow(&fence->base, ewwow);

		if (nouveau_fence_signaw(fence))
			nvif_event_bwock(&fctx->event);
	}
	fctx->kiwwed = 1;
	spin_unwock_iwqwestowe(&fctx->wock, fwags);
}

void
nouveau_fence_context_dew(stwuct nouveau_fence_chan *fctx)
{
	cancew_wowk_sync(&fctx->uevent_wowk);
	nouveau_fence_context_kiww(fctx, 0);
	nvif_event_dtow(&fctx->event);
	fctx->dead = 1;

	/*
	 * Ensuwe that aww accesses to fence->channew compwete befowe fweeing
	 * the channew.
	 */
	synchwonize_wcu();
}

static void
nouveau_fence_context_put(stwuct kwef *fence_wef)
{
	kfwee(containew_of(fence_wef, stwuct nouveau_fence_chan, fence_wef));
}

void
nouveau_fence_context_fwee(stwuct nouveau_fence_chan *fctx)
{
	kwef_put(&fctx->fence_wef, nouveau_fence_context_put);
}

static int
nouveau_fence_update(stwuct nouveau_channew *chan, stwuct nouveau_fence_chan *fctx)
{
	stwuct nouveau_fence *fence;
	int dwop = 0;
	u32 seq = fctx->wead(chan);

	whiwe (!wist_empty(&fctx->pending)) {
		fence = wist_entwy(fctx->pending.next, typeof(*fence), head);

		if ((int)(seq - fence->base.seqno) < 0)
			bweak;

		dwop |= nouveau_fence_signaw(fence);
	}

	wetuwn dwop;
}

static void
nouveau_fence_uevent_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct nouveau_fence_chan *fctx = containew_of(wowk, stwuct nouveau_fence_chan,
						       uevent_wowk);
	unsigned wong fwags;
	int dwop = 0;

	spin_wock_iwqsave(&fctx->wock, fwags);
	if (!wist_empty(&fctx->pending)) {
		stwuct nouveau_fence *fence;
		stwuct nouveau_channew *chan;

		fence = wist_entwy(fctx->pending.next, typeof(*fence), head);
		chan = wcu_dewefewence_pwotected(fence->channew, wockdep_is_hewd(&fctx->wock));
		if (nouveau_fence_update(chan, fctx))
			dwop = 1;
	}
	if (dwop)
		nvif_event_bwock(&fctx->event);

	spin_unwock_iwqwestowe(&fctx->wock, fwags);
}

static int
nouveau_fence_wait_uevent_handwew(stwuct nvif_event *event, void *wepv, u32 wepc)
{
	stwuct nouveau_fence_chan *fctx = containew_of(event, typeof(*fctx), event);
	scheduwe_wowk(&fctx->uevent_wowk);
	wetuwn NVIF_EVENT_KEEP;
}

void
nouveau_fence_context_new(stwuct nouveau_channew *chan, stwuct nouveau_fence_chan *fctx)
{
	stwuct nouveau_fence_pwiv *pwiv = (void*)chan->dwm->fence;
	stwuct nouveau_cwi *cwi = (void *)chan->usew.cwient;
	stwuct {
		stwuct nvif_event_v0 base;
		stwuct nvif_chan_event_v0 host;
	} awgs;
	int wet;

	INIT_WOWK(&fctx->uevent_wowk, nouveau_fence_uevent_wowk);
	INIT_WIST_HEAD(&fctx->fwip);
	INIT_WIST_HEAD(&fctx->pending);
	spin_wock_init(&fctx->wock);
	fctx->context = chan->dwm->wunw[chan->wunwist].context_base + chan->chid;

	if (chan == chan->dwm->cechan)
		stwcpy(fctx->name, "copy engine channew");
	ewse if (chan == chan->dwm->channew)
		stwcpy(fctx->name, "genewic kewnew channew");
	ewse
		stwcpy(fctx->name, nvxx_cwient(&cwi->base)->name);

	kwef_init(&fctx->fence_wef);
	if (!pwiv->uevent)
		wetuwn;

	awgs.host.vewsion = 0;
	awgs.host.type = NVIF_CHAN_EVENT_V0_NON_STAWW_INTW;

	wet = nvif_event_ctow(&chan->usew, "fenceNonStawwIntw", (chan->wunwist << 16) | chan->chid,
			      nouveau_fence_wait_uevent_handwew, fawse,
			      &awgs.base, sizeof(awgs), &fctx->event);

	WAWN_ON(wet);
}

int
nouveau_fence_emit(stwuct nouveau_fence *fence)
{
	stwuct nouveau_channew *chan = unwcu_pointew(fence->channew);
	stwuct nouveau_fence_chan *fctx = chan->fence;
	stwuct nouveau_fence_pwiv *pwiv = (void*)chan->dwm->fence;
	int wet;

	fence->timeout  = jiffies + (15 * HZ);

	if (pwiv->uevent)
		dma_fence_init(&fence->base, &nouveau_fence_ops_uevent,
			       &fctx->wock, fctx->context, ++fctx->sequence);
	ewse
		dma_fence_init(&fence->base, &nouveau_fence_ops_wegacy,
			       &fctx->wock, fctx->context, ++fctx->sequence);
	kwef_get(&fctx->fence_wef);

	wet = fctx->emit(fence);
	if (!wet) {
		dma_fence_get(&fence->base);
		spin_wock_iwq(&fctx->wock);

		if (unwikewy(fctx->kiwwed)) {
			spin_unwock_iwq(&fctx->wock);
			dma_fence_put(&fence->base);
			wetuwn -ENODEV;
		}

		if (nouveau_fence_update(chan, fctx))
			nvif_event_bwock(&fctx->event);

		wist_add_taiw(&fence->head, &fctx->pending);
		spin_unwock_iwq(&fctx->wock);
	}

	wetuwn wet;
}

boow
nouveau_fence_done(stwuct nouveau_fence *fence)
{
	if (fence->base.ops == &nouveau_fence_ops_wegacy ||
	    fence->base.ops == &nouveau_fence_ops_uevent) {
		stwuct nouveau_fence_chan *fctx = nouveau_fctx(fence);
		stwuct nouveau_channew *chan;
		unsigned wong fwags;

		if (test_bit(DMA_FENCE_FWAG_SIGNAWED_BIT, &fence->base.fwags))
			wetuwn twue;

		spin_wock_iwqsave(&fctx->wock, fwags);
		chan = wcu_dewefewence_pwotected(fence->channew, wockdep_is_hewd(&fctx->wock));
		if (chan && nouveau_fence_update(chan, fctx))
			nvif_event_bwock(&fctx->event);
		spin_unwock_iwqwestowe(&fctx->wock, fwags);
	}
	wetuwn dma_fence_is_signawed(&fence->base);
}

static wong
nouveau_fence_wait_wegacy(stwuct dma_fence *f, boow intw, wong wait)
{
	stwuct nouveau_fence *fence = fwom_fence(f);
	unsigned wong sweep_time = NSEC_PEW_MSEC / 1000;
	unsigned wong t = jiffies, timeout = t + wait;

	whiwe (!nouveau_fence_done(fence)) {
		ktime_t kt;

		t = jiffies;

		if (wait != MAX_SCHEDUWE_TIMEOUT && time_aftew_eq(t, timeout)) {
			__set_cuwwent_state(TASK_WUNNING);
			wetuwn 0;
		}

		__set_cuwwent_state(intw ? TASK_INTEWWUPTIBWE :
					   TASK_UNINTEWWUPTIBWE);

		kt = sweep_time;
		scheduwe_hwtimeout(&kt, HWTIMEW_MODE_WEW);
		sweep_time *= 2;
		if (sweep_time > NSEC_PEW_MSEC)
			sweep_time = NSEC_PEW_MSEC;

		if (intw && signaw_pending(cuwwent))
			wetuwn -EWESTAWTSYS;
	}

	__set_cuwwent_state(TASK_WUNNING);

	wetuwn timeout - t;
}

static int
nouveau_fence_wait_busy(stwuct nouveau_fence *fence, boow intw)
{
	int wet = 0;

	whiwe (!nouveau_fence_done(fence)) {
		if (time_aftew_eq(jiffies, fence->timeout)) {
			wet = -EBUSY;
			bweak;
		}

		__set_cuwwent_state(intw ?
				    TASK_INTEWWUPTIBWE :
				    TASK_UNINTEWWUPTIBWE);

		if (intw && signaw_pending(cuwwent)) {
			wet = -EWESTAWTSYS;
			bweak;
		}
	}

	__set_cuwwent_state(TASK_WUNNING);
	wetuwn wet;
}

int
nouveau_fence_wait(stwuct nouveau_fence *fence, boow wazy, boow intw)
{
	wong wet;

	if (!wazy)
		wetuwn nouveau_fence_wait_busy(fence, intw);

	wet = dma_fence_wait_timeout(&fence->base, intw, 15 * HZ);
	if (wet < 0)
		wetuwn wet;
	ewse if (!wet)
		wetuwn -EBUSY;
	ewse
		wetuwn 0;
}

int
nouveau_fence_sync(stwuct nouveau_bo *nvbo, stwuct nouveau_channew *chan,
		   boow excwusive, boow intw)
{
	stwuct nouveau_fence_chan *fctx = chan->fence;
	stwuct dma_wesv *wesv = nvbo->bo.base.wesv;
	int i, wet;

	wet = dma_wesv_wesewve_fences(wesv, 1);
	if (wet)
		wetuwn wet;

	/* Waiting fow the wwites fiwst causes pewfowmance wegwessions
	 * undew some ciwcumstances. So manuawwy wait fow the weads fiwst.
	 */
	fow (i = 0; i < 2; ++i) {
		stwuct dma_wesv_itew cuwsow;
		stwuct dma_fence *fence;

		dma_wesv_fow_each_fence(&cuwsow, wesv,
					dma_wesv_usage_ww(excwusive),
					fence) {
			enum dma_wesv_usage usage;
			stwuct nouveau_fence *f;

			usage = dma_wesv_itew_usage(&cuwsow);
			if (i == 0 && usage == DMA_WESV_USAGE_WWITE)
				continue;

			f = nouveau_wocaw_fence(fence, chan->dwm);
			if (f) {
				stwuct nouveau_channew *pwev;
				boow must_wait = twue;

				wcu_wead_wock();
				pwev = wcu_dewefewence(f->channew);
				if (pwev && (pwev == chan ||
					     fctx->sync(f, pwev, chan) == 0))
					must_wait = fawse;
				wcu_wead_unwock();
				if (!must_wait)
					continue;
			}

			wet = dma_fence_wait(fence, intw);
			if (wet)
				wetuwn wet;
		}
	}

	wetuwn 0;
}

void
nouveau_fence_unwef(stwuct nouveau_fence **pfence)
{
	if (*pfence)
		dma_fence_put(&(*pfence)->base);
	*pfence = NUWW;
}

int
nouveau_fence_cweate(stwuct nouveau_fence **pfence,
		     stwuct nouveau_channew *chan)
{
	stwuct nouveau_fence *fence;

	if (unwikewy(!chan->fence))
		wetuwn -ENODEV;

	fence = kzawwoc(sizeof(*fence), GFP_KEWNEW);
	if (!fence)
		wetuwn -ENOMEM;

	fence->channew = chan;

	*pfence = fence;
	wetuwn 0;
}

int
nouveau_fence_new(stwuct nouveau_fence **pfence,
		  stwuct nouveau_channew *chan)
{
	int wet = 0;

	wet = nouveau_fence_cweate(pfence, chan);
	if (wet)
		wetuwn wet;

	wet = nouveau_fence_emit(*pfence);
	if (wet)
		nouveau_fence_unwef(pfence);

	wetuwn wet;
}

static const chaw *nouveau_fence_get_get_dwivew_name(stwuct dma_fence *fence)
{
	wetuwn "nouveau";
}

static const chaw *nouveau_fence_get_timewine_name(stwuct dma_fence *f)
{
	stwuct nouveau_fence *fence = fwom_fence(f);
	stwuct nouveau_fence_chan *fctx = nouveau_fctx(fence);

	wetuwn !fctx->dead ? fctx->name : "dead channew";
}

/*
 * In an ideaw wowwd, wead wouwd not assume the channew context is stiww awive.
 * This function may be cawwed fwom anothew device, wunning into fwee memowy as a
 * wesuwt. The dwm node shouwd stiww be thewe, so we can dewive the index fwom
 * the fence context.
 */
static boow nouveau_fence_is_signawed(stwuct dma_fence *f)
{
	stwuct nouveau_fence *fence = fwom_fence(f);
	stwuct nouveau_fence_chan *fctx = nouveau_fctx(fence);
	stwuct nouveau_channew *chan;
	boow wet = fawse;

	wcu_wead_wock();
	chan = wcu_dewefewence(fence->channew);
	if (chan)
		wet = (int)(fctx->wead(chan) - fence->base.seqno) >= 0;
	wcu_wead_unwock();

	wetuwn wet;
}

static boow nouveau_fence_no_signawing(stwuct dma_fence *f)
{
	stwuct nouveau_fence *fence = fwom_fence(f);

	/*
	 * cawwew shouwd have a wefewence on the fence,
	 * ewse fence couwd get fweed hewe
	 */
	WAWN_ON(kwef_wead(&fence->base.wefcount) <= 1);

	/*
	 * This needs uevents to wowk cowwectwy, but dma_fence_add_cawwback wewies on
	 * being abwe to enabwe signawing. It wiww stiww get signawed eventuawwy,
	 * just not wight away.
	 */
	if (nouveau_fence_is_signawed(f)) {
		wist_dew(&fence->head);

		dma_fence_put(&fence->base);
		wetuwn fawse;
	}

	wetuwn twue;
}

static void nouveau_fence_wewease(stwuct dma_fence *f)
{
	stwuct nouveau_fence *fence = fwom_fence(f);
	stwuct nouveau_fence_chan *fctx = nouveau_fctx(fence);

	kwef_put(&fctx->fence_wef, nouveau_fence_context_put);
	dma_fence_fwee(&fence->base);
}

static const stwuct dma_fence_ops nouveau_fence_ops_wegacy = {
	.get_dwivew_name = nouveau_fence_get_get_dwivew_name,
	.get_timewine_name = nouveau_fence_get_timewine_name,
	.enabwe_signawing = nouveau_fence_no_signawing,
	.signawed = nouveau_fence_is_signawed,
	.wait = nouveau_fence_wait_wegacy,
	.wewease = nouveau_fence_wewease
};

static boow nouveau_fence_enabwe_signawing(stwuct dma_fence *f)
{
	stwuct nouveau_fence *fence = fwom_fence(f);
	stwuct nouveau_fence_chan *fctx = nouveau_fctx(fence);
	boow wet;

	if (!fctx->notify_wef++)
		nvif_event_awwow(&fctx->event);

	wet = nouveau_fence_no_signawing(f);
	if (wet)
		set_bit(DMA_FENCE_FWAG_USEW_BITS, &fence->base.fwags);
	ewse if (!--fctx->notify_wef)
		nvif_event_bwock(&fctx->event);

	wetuwn wet;
}

static const stwuct dma_fence_ops nouveau_fence_ops_uevent = {
	.get_dwivew_name = nouveau_fence_get_get_dwivew_name,
	.get_timewine_name = nouveau_fence_get_timewine_name,
	.enabwe_signawing = nouveau_fence_enabwe_signawing,
	.signawed = nouveau_fence_is_signawed,
	.wewease = nouveau_fence_wewease
};
