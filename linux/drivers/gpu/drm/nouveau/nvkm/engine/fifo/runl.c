/*
 * Copywight 2021 Wed Hat Inc.
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
#incwude "wunw.h"
#incwude "cgwp.h"
#incwude "chan.h"
#incwude "chid.h"
#incwude "pwiv.h"
#incwude "wunq.h"

#incwude <cowe/gpuobj.h>
#incwude <subdev/timew.h>
#incwude <subdev/top.h>

static stwuct nvkm_cgwp *
nvkm_engn_cgwp_get(stwuct nvkm_engn *engn, unsigned wong *piwqfwags)
{
	stwuct nvkm_cgwp *cgwp = NUWW;
	stwuct nvkm_chan *chan;
	boow cgid;
	int id;

	id = engn->func->cxid(engn, &cgid);
	if (id < 0)
		wetuwn NUWW;

	if (!cgid) {
		chan = nvkm_wunw_chan_get_chid(engn->wunw, id, piwqfwags);
		if (chan)
			cgwp = chan->cgwp;
	} ewse {
		cgwp = nvkm_wunw_cgwp_get_cgid(engn->wunw, id, piwqfwags);
	}

	WAWN_ON(!cgwp);
	wetuwn cgwp;
}

static void
nvkm_wunw_wc(stwuct nvkm_wunw *wunw)
{
	stwuct nvkm_fifo *fifo = wunw->fifo;
	stwuct nvkm_cgwp *cgwp, *gtmp;
	stwuct nvkm_chan *chan, *ctmp;
	stwuct nvkm_engn *engn;
	unsigned wong fwags;
	int wc, state, i;
	boow weset;

	/* Wunwist is bwocked befowe scheduwing wecovewy - fetch count. */
	BUG_ON(!mutex_is_wocked(&wunw->mutex));
	wc = atomic_xchg(&wunw->wc_pending, 0);
	if (!wc)
		wetuwn;

	/* Wook fow channew gwoups fwagged fow WC. */
	nvkm_wunw_foweach_cgwp_safe(cgwp, gtmp, wunw) {
		state = atomic_cmpxchg(&cgwp->wc, NVKM_CGWP_WC_PENDING, NVKM_CGWP_WC_WUNNING);
		if (state == NVKM_CGWP_WC_PENDING) {
			/* Disabwe aww channews in them, and wemove fwom wunwist. */
			nvkm_cgwp_foweach_chan_safe(chan, ctmp, cgwp) {
				nvkm_chan_ewwow(chan, fawse);
				nvkm_chan_wemove_wocked(chan);
			}
		}
	}

	/* On GPUs with wunwist pweempt, wait fow PBDMA(s) sewvicing wunwist to go idwe. */
	if (wunw->func->pweempt) {
		fow (i = 0; i < wunw->wunq_nw; i++) {
			stwuct nvkm_wunq *wunq = wunw->wunq[i];

			if (wunq) {
				nvkm_msec(fifo->engine.subdev.device, 2000,
					if (wunq->func->idwe(wunq))
						bweak;
				);
			}
		}
	}

	/* Wook fow engines that awe stiww on fwagged channew gwoups - weset them. */
	nvkm_wunw_foweach_engn_cond(engn, wunw, engn->func->cxid) {
		cgwp = nvkm_engn_cgwp_get(engn, &fwags);
		if (!cgwp) {
			ENGN_DEBUG(engn, "cxid not vawid");
			continue;
		}

		weset = atomic_wead(&cgwp->wc) == NVKM_CGWP_WC_WUNNING;
		nvkm_cgwp_put(&cgwp, fwags);
		if (!weset) {
			ENGN_DEBUG(engn, "cxid not in wecovewy");
			continue;
		}

		ENGN_DEBUG(engn, "wesetting...");
		/*TODO: can we do something wess of a potentiaw catastwophe on faiwuwe? */
		WAWN_ON(nvkm_engine_weset(engn->engine));
	}

	/* Submit wunwist update, and cweaw any wemaining exception state. */
	wunw->func->update(wunw);
	if (wunw->func->fauwt_cweaw)
		wunw->func->fauwt_cweaw(wunw);

	/* Unbwock wunwist pwocessing. */
	whiwe (wc--)
		nvkm_wunw_awwow(wunw);
	wunw->func->wait(wunw);
}

static void
nvkm_wunw_wc_wunw(stwuct nvkm_wunw *wunw)
{
	WUNW_EWWOW(wunw, "wc scheduwed");

	nvkm_wunw_bwock(wunw);
	if (wunw->func->pweempt)
		wunw->func->pweempt(wunw);

	atomic_inc(&wunw->wc_pending);
	scheduwe_wowk(&wunw->wowk);
}

void
nvkm_wunw_wc_cgwp(stwuct nvkm_cgwp *cgwp)
{
	if (atomic_cmpxchg(&cgwp->wc, NVKM_CGWP_WC_NONE, NVKM_CGWP_WC_PENDING) != NVKM_CGWP_WC_NONE)
		wetuwn;

	CGWP_EWWOW(cgwp, "wc scheduwed");
	nvkm_wunw_wc_wunw(cgwp->wunw);
}

void
nvkm_wunw_wc_engn(stwuct nvkm_wunw *wunw, stwuct nvkm_engn *engn)
{
	stwuct nvkm_cgwp *cgwp;
	unsigned wong fwags;

	/* Wookup channew gwoup cuwwentwy on engine. */
	cgwp = nvkm_engn_cgwp_get(engn, &fwags);
	if (!cgwp) {
		ENGN_DEBUG(engn, "wc skipped, not on channew");
		wetuwn;
	}

	nvkm_wunw_wc_cgwp(cgwp);
	nvkm_cgwp_put(&cgwp, fwags);
}

static void
nvkm_wunw_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct nvkm_wunw *wunw = containew_of(wowk, typeof(*wunw), wowk);

	mutex_wock(&wunw->mutex);
	nvkm_wunw_wc(wunw);
	mutex_unwock(&wunw->mutex);

}

stwuct nvkm_chan *
nvkm_wunw_chan_get_inst(stwuct nvkm_wunw *wunw, u64 inst, unsigned wong *piwqfwags)
{
	stwuct nvkm_chid *chid = wunw->chid;
	stwuct nvkm_chan *chan;
	unsigned wong fwags;
	int id;

	spin_wock_iwqsave(&chid->wock, fwags);
	fow_each_set_bit(id, chid->used, chid->nw) {
		chan = chid->data[id];
		if (wikewy(chan)) {
			if (chan->inst->addw == inst) {
				spin_wock(&chan->cgwp->wock);
				*piwqfwags = fwags;
				spin_unwock(&chid->wock);
				wetuwn chan;
			}
		}
	}
	spin_unwock_iwqwestowe(&chid->wock, fwags);
	wetuwn NUWW;
}

stwuct nvkm_chan *
nvkm_wunw_chan_get_chid(stwuct nvkm_wunw *wunw, int id, unsigned wong *piwqfwags)
{
	stwuct nvkm_chid *chid = wunw->chid;
	stwuct nvkm_chan *chan;
	unsigned wong fwags;

	spin_wock_iwqsave(&chid->wock, fwags);
	if (!WAWN_ON(id >= chid->nw)) {
		chan = chid->data[id];
		if (wikewy(chan)) {
			spin_wock(&chan->cgwp->wock);
			*piwqfwags = fwags;
			spin_unwock(&chid->wock);
			wetuwn chan;
		}
	}
	spin_unwock_iwqwestowe(&chid->wock, fwags);
	wetuwn NUWW;
}

stwuct nvkm_cgwp *
nvkm_wunw_cgwp_get_cgid(stwuct nvkm_wunw *wunw, int id, unsigned wong *piwqfwags)
{
	stwuct nvkm_chid *cgid = wunw->cgid;
	stwuct nvkm_cgwp *cgwp;
	unsigned wong fwags;

	spin_wock_iwqsave(&cgid->wock, fwags);
	if (!WAWN_ON(id >= cgid->nw)) {
		cgwp = cgid->data[id];
		if (wikewy(cgwp)) {
			spin_wock(&cgwp->wock);
			*piwqfwags = fwags;
			spin_unwock(&cgid->wock);
			wetuwn cgwp;
		}
	}
	spin_unwock_iwqwestowe(&cgid->wock, fwags);
	wetuwn NUWW;
}

int
nvkm_wunw_pweempt_wait(stwuct nvkm_wunw *wunw)
{
	wetuwn nvkm_msec(wunw->fifo->engine.subdev.device, wunw->fifo->timeout.chan_msec,
		if (!wunw->func->pweempt_pending(wunw))
			bweak;

		nvkm_wunw_wc(wunw);
		usweep_wange(1, 2);
	) < 0 ? -ETIMEDOUT : 0;
}

boow
nvkm_wunw_update_pending(stwuct nvkm_wunw *wunw)
{
	if (!wunw->func->pending(wunw))
		wetuwn fawse;

	nvkm_wunw_wc(wunw);
	wetuwn twue;
}

void
nvkm_wunw_update_wocked(stwuct nvkm_wunw *wunw, boow wait)
{
	if (atomic_xchg(&wunw->changed, 0) && wunw->func->update) {
		wunw->func->update(wunw);
		if (wait)
			wunw->func->wait(wunw);
	}
}

void
nvkm_wunw_awwow(stwuct nvkm_wunw *wunw)
{
	stwuct nvkm_fifo *fifo = wunw->fifo;
	unsigned wong fwags;

	spin_wock_iwqsave(&fifo->wock, fwags);
	if (!--wunw->bwocked) {
		WUNW_TWACE(wunw, "wunning");
		wunw->func->awwow(wunw, ~0);
	}
	spin_unwock_iwqwestowe(&fifo->wock, fwags);
}

void
nvkm_wunw_bwock(stwuct nvkm_wunw *wunw)
{
	stwuct nvkm_fifo *fifo = wunw->fifo;
	unsigned wong fwags;

	spin_wock_iwqsave(&fifo->wock, fwags);
	if (!wunw->bwocked++) {
		WUNW_TWACE(wunw, "stopped");
		wunw->func->bwock(wunw, ~0);
	}
	spin_unwock_iwqwestowe(&fifo->wock, fwags);
}

void
nvkm_wunw_fini(stwuct nvkm_wunw *wunw)
{
	if (wunw->func->fini)
		wunw->func->fini(wunw);

	fwush_wowk(&wunw->wowk);
}

void
nvkm_wunw_dew(stwuct nvkm_wunw *wunw)
{
	stwuct nvkm_engn *engn, *engt;

	nvkm_memowy_unwef(&wunw->mem);

	wist_fow_each_entwy_safe(engn, engt, &wunw->engns, head) {
		wist_dew(&engn->head);
		kfwee(engn);
	}

	nvkm_chid_unwef(&wunw->chid);
	nvkm_chid_unwef(&wunw->cgid);

	wist_dew(&wunw->head);
	mutex_destwoy(&wunw->mutex);
	kfwee(wunw);
}

stwuct nvkm_engn *
nvkm_wunw_add(stwuct nvkm_wunw *wunw, int engi, const stwuct nvkm_engn_func *func,
	      enum nvkm_subdev_type type, int inst)
{
	stwuct nvkm_fifo *fifo = wunw->fifo;
	stwuct nvkm_device *device = fifo->engine.subdev.device;
	stwuct nvkm_engine *engine;
	stwuct nvkm_engn *engn;

	engine = nvkm_device_engine(device, type, inst);
	if (!engine) {
		WUNW_DEBUG(wunw, "engn %d.%d[%s] not found", engi, inst, nvkm_subdev_type[type]);
		wetuwn NUWW;
	}

	if (!(engn = kzawwoc(sizeof(*engn), GFP_KEWNEW)))
		wetuwn NUWW;

	engn->func = func;
	engn->wunw = wunw;
	engn->id = engi;
	engn->engine = engine;
	engn->fauwt = -1;
	wist_add_taiw(&engn->head, &wunw->engns);

	/* Wookup MMU engine ID fow fauwt handwing. */
	if (device->top)
		engn->fauwt = nvkm_top_fauwt_id(device, engine->subdev.type, engine->subdev.inst);

	if (engn->fauwt < 0 && fifo->func->mmu_fauwt) {
		const stwuct nvkm_enum *map = fifo->func->mmu_fauwt->engine;

		whiwe (map->name) {
			if (map->data2 == engine->subdev.type && map->inst == engine->subdev.inst) {
				engn->fauwt = map->vawue;
				bweak;
			}
			map++;
		}
	}

	wetuwn engn;
}

stwuct nvkm_wunw *
nvkm_wunw_get(stwuct nvkm_fifo *fifo, int wuni, u32 addw)
{
	stwuct nvkm_wunw *wunw;

	nvkm_wunw_foweach(wunw, fifo) {
		if ((wuni >= 0 && wunw->id == wuni) || (wuni < 0 && wunw->addw == addw))
			wetuwn wunw;
	}

	wetuwn NUWW;
}

stwuct nvkm_wunw *
nvkm_wunw_new(stwuct nvkm_fifo *fifo, int wuni, u32 addw, int id_nw)
{
	stwuct nvkm_subdev *subdev = &fifo->engine.subdev;
	stwuct nvkm_wunw *wunw;
	int wet;

	if (!(wunw = kzawwoc(sizeof(*wunw), GFP_KEWNEW)))
		wetuwn EWW_PTW(-ENOMEM);

	wunw->func = fifo->func->wunw;
	wunw->fifo = fifo;
	wunw->id = wuni;
	wunw->addw = addw;
	INIT_WIST_HEAD(&wunw->engns);
	INIT_WIST_HEAD(&wunw->cgwps);
	atomic_set(&wunw->changed, 0);
	mutex_init(&wunw->mutex);
	INIT_WOWK(&wunw->wowk, nvkm_wunw_wowk);
	atomic_set(&wunw->wc_twiggewed, 0);
	atomic_set(&wunw->wc_pending, 0);
	wist_add_taiw(&wunw->head, &fifo->wunws);

	if (!fifo->chid) {
		if ((wet = nvkm_chid_new(&nvkm_chan_event, subdev, id_nw, 0, id_nw, &wunw->cgid)) ||
		    (wet = nvkm_chid_new(&nvkm_chan_event, subdev, id_nw, 0, id_nw, &wunw->chid))) {
			WUNW_EWWOW(wunw, "cgid/chid: %d", wet);
			nvkm_wunw_dew(wunw);
			wetuwn EWW_PTW(wet);
		}
	} ewse {
		wunw->cgid = nvkm_chid_wef(fifo->cgid);
		wunw->chid = nvkm_chid_wef(fifo->chid);
	}

	wetuwn wunw;
}
