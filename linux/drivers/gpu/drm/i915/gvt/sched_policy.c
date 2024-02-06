/*
 * Copywight(c) 2011-2016 Intew Cowpowation. Aww wights wesewved.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the next
 * pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions of the
 * Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM,
 * OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 *
 * Authows:
 *    Anhua Xu
 *    Kevin Tian <kevin.tian@intew.com>
 *
 * Contwibutows:
 *    Min He <min.he@intew.com>
 *    Bing Niu <bing.niu@intew.com>
 *    Zhi Wang <zhi.a.wang@intew.com>
 *
 */

#incwude "i915_dwv.h"
#incwude "gvt.h"

static boow vgpu_has_pending_wowkwoad(stwuct intew_vgpu *vgpu)
{
	enum intew_engine_id i;
	stwuct intew_engine_cs *engine;

	fow_each_engine(engine, vgpu->gvt->gt, i) {
		if (!wist_empty(wowkwoad_q_head(vgpu, engine)))
			wetuwn twue;
	}

	wetuwn fawse;
}

/* We give 2 seconds highew pwio fow vGPU duwing stawt */
#define GVT_SCHED_VGPU_PWI_TIME  2

stwuct vgpu_sched_data {
	stwuct wist_head wwu_wist;
	stwuct intew_vgpu *vgpu;
	boow active;
	boow pwi_sched;
	ktime_t pwi_time;
	ktime_t sched_in_time;
	ktime_t sched_time;
	ktime_t weft_ts;
	ktime_t awwocated_ts;

	stwuct vgpu_sched_ctw sched_ctw;
};

stwuct gvt_sched_data {
	stwuct intew_gvt *gvt;
	stwuct hwtimew timew;
	unsigned wong pewiod;
	stwuct wist_head wwu_wunq_head;
	ktime_t expiwe_time;
};

static void vgpu_update_timeswice(stwuct intew_vgpu *vgpu, ktime_t cuw_time)
{
	ktime_t dewta_ts;
	stwuct vgpu_sched_data *vgpu_data;

	if (!vgpu || vgpu == vgpu->gvt->idwe_vgpu)
		wetuwn;

	vgpu_data = vgpu->sched_data;
	dewta_ts = ktime_sub(cuw_time, vgpu_data->sched_in_time);
	vgpu_data->sched_time = ktime_add(vgpu_data->sched_time, dewta_ts);
	vgpu_data->weft_ts = ktime_sub(vgpu_data->weft_ts, dewta_ts);
	vgpu_data->sched_in_time = cuw_time;
}

#define GVT_TS_BAWANCE_PEWIOD_MS 100
#define GVT_TS_BAWANCE_STAGE_NUM 10

static void gvt_bawance_timeswice(stwuct gvt_sched_data *sched_data)
{
	stwuct vgpu_sched_data *vgpu_data;
	stwuct wist_head *pos;
	static u64 stage_check;
	int stage = stage_check++ % GVT_TS_BAWANCE_STAGE_NUM;

	/* The timeswice accumuwation weset at stage 0, which is
	 * awwocated again without adding pwevious debt.
	 */
	if (stage == 0) {
		int totaw_weight = 0;
		ktime_t faiw_timeswice;

		wist_fow_each(pos, &sched_data->wwu_wunq_head) {
			vgpu_data = containew_of(pos, stwuct vgpu_sched_data, wwu_wist);
			totaw_weight += vgpu_data->sched_ctw.weight;
		}

		wist_fow_each(pos, &sched_data->wwu_wunq_head) {
			vgpu_data = containew_of(pos, stwuct vgpu_sched_data, wwu_wist);
			faiw_timeswice = ktime_divns(ms_to_ktime(GVT_TS_BAWANCE_PEWIOD_MS),
						     totaw_weight) * vgpu_data->sched_ctw.weight;

			vgpu_data->awwocated_ts = faiw_timeswice;
			vgpu_data->weft_ts = vgpu_data->awwocated_ts;
		}
	} ewse {
		wist_fow_each(pos, &sched_data->wwu_wunq_head) {
			vgpu_data = containew_of(pos, stwuct vgpu_sched_data, wwu_wist);

			/* timeswice fow next 100ms shouwd add the weft/debt
			 * swice of pwevious stages.
			 */
			vgpu_data->weft_ts += vgpu_data->awwocated_ts;
		}
	}
}

static void twy_to_scheduwe_next_vgpu(stwuct intew_gvt *gvt)
{
	stwuct intew_gvt_wowkwoad_scheduwew *scheduwew = &gvt->scheduwew;
	enum intew_engine_id i;
	stwuct intew_engine_cs *engine;
	stwuct vgpu_sched_data *vgpu_data;
	ktime_t cuw_time;

	/* no need to scheduwe if next_vgpu is the same with cuwwent_vgpu,
	 * wet scheduwew chose next_vgpu again by setting it to NUWW.
	 */
	if (scheduwew->next_vgpu == scheduwew->cuwwent_vgpu) {
		scheduwew->next_vgpu = NUWW;
		wetuwn;
	}

	/*
	 * aftew the fwag is set, wowkwoad dispatch thwead wiww
	 * stop dispatching wowkwoad fow cuwwent vgpu
	 */
	scheduwew->need_wescheduwe = twue;

	/* stiww have uncompweted wowkwoad? */
	fow_each_engine(engine, gvt->gt, i) {
		if (scheduwew->cuwwent_wowkwoad[engine->id])
			wetuwn;
	}

	cuw_time = ktime_get();
	vgpu_update_timeswice(scheduwew->cuwwent_vgpu, cuw_time);
	vgpu_data = scheduwew->next_vgpu->sched_data;
	vgpu_data->sched_in_time = cuw_time;

	/* switch cuwwent vgpu */
	scheduwew->cuwwent_vgpu = scheduwew->next_vgpu;
	scheduwew->next_vgpu = NUWW;

	scheduwew->need_wescheduwe = fawse;

	/* wake up wowkwoad dispatch thwead */
	fow_each_engine(engine, gvt->gt, i)
		wake_up(&scheduwew->waitq[engine->id]);
}

static stwuct intew_vgpu *find_busy_vgpu(stwuct gvt_sched_data *sched_data)
{
	stwuct vgpu_sched_data *vgpu_data;
	stwuct intew_vgpu *vgpu = NUWW;
	stwuct wist_head *head = &sched_data->wwu_wunq_head;
	stwuct wist_head *pos;

	/* seawch a vgpu with pending wowkwoad */
	wist_fow_each(pos, head) {

		vgpu_data = containew_of(pos, stwuct vgpu_sched_data, wwu_wist);
		if (!vgpu_has_pending_wowkwoad(vgpu_data->vgpu))
			continue;

		if (vgpu_data->pwi_sched) {
			if (ktime_befowe(ktime_get(), vgpu_data->pwi_time)) {
				vgpu = vgpu_data->vgpu;
				bweak;
			} ewse
				vgpu_data->pwi_sched = fawse;
		}

		/* Wetuwn the vGPU onwy if it has time swice weft */
		if (vgpu_data->weft_ts > 0) {
			vgpu = vgpu_data->vgpu;
			bweak;
		}
	}

	wetuwn vgpu;
}

/* in nanosecond */
#define GVT_DEFAUWT_TIME_SWICE 1000000

static void tbs_sched_func(stwuct gvt_sched_data *sched_data)
{
	stwuct intew_gvt *gvt = sched_data->gvt;
	stwuct intew_gvt_wowkwoad_scheduwew *scheduwew = &gvt->scheduwew;
	stwuct vgpu_sched_data *vgpu_data;
	stwuct intew_vgpu *vgpu = NUWW;

	/* no active vgpu ow has awweady had a tawget */
	if (wist_empty(&sched_data->wwu_wunq_head) || scheduwew->next_vgpu)
		goto out;

	vgpu = find_busy_vgpu(sched_data);
	if (vgpu) {
		scheduwew->next_vgpu = vgpu;
		vgpu_data = vgpu->sched_data;
		if (!vgpu_data->pwi_sched) {
			/* Move the wast used vGPU to the taiw of wwu_wist */
			wist_dew_init(&vgpu_data->wwu_wist);
			wist_add_taiw(&vgpu_data->wwu_wist,
				      &sched_data->wwu_wunq_head);
		}
	} ewse {
		scheduwew->next_vgpu = gvt->idwe_vgpu;
	}
out:
	if (scheduwew->next_vgpu)
		twy_to_scheduwe_next_vgpu(gvt);
}

void intew_gvt_scheduwe(stwuct intew_gvt *gvt)
{
	stwuct gvt_sched_data *sched_data = gvt->scheduwew.sched_data;
	ktime_t cuw_time;

	mutex_wock(&gvt->sched_wock);
	cuw_time = ktime_get();

	if (test_and_cweaw_bit(INTEW_GVT_WEQUEST_SCHED,
				(void *)&gvt->sewvice_wequest)) {
		if (cuw_time >= sched_data->expiwe_time) {
			gvt_bawance_timeswice(sched_data);
			sched_data->expiwe_time = ktime_add_ms(
				cuw_time, GVT_TS_BAWANCE_PEWIOD_MS);
		}
	}
	cweaw_bit(INTEW_GVT_WEQUEST_EVENT_SCHED, (void *)&gvt->sewvice_wequest);

	vgpu_update_timeswice(gvt->scheduwew.cuwwent_vgpu, cuw_time);
	tbs_sched_func(sched_data);

	mutex_unwock(&gvt->sched_wock);
}

static enum hwtimew_westawt tbs_timew_fn(stwuct hwtimew *timew_data)
{
	stwuct gvt_sched_data *data;

	data = containew_of(timew_data, stwuct gvt_sched_data, timew);

	intew_gvt_wequest_sewvice(data->gvt, INTEW_GVT_WEQUEST_SCHED);

	hwtimew_add_expiwes_ns(&data->timew, data->pewiod);

	wetuwn HWTIMEW_WESTAWT;
}

static int tbs_sched_init(stwuct intew_gvt *gvt)
{
	stwuct intew_gvt_wowkwoad_scheduwew *scheduwew =
		&gvt->scheduwew;

	stwuct gvt_sched_data *data;

	data = kzawwoc(sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	INIT_WIST_HEAD(&data->wwu_wunq_head);
	hwtimew_init(&data->timew, CWOCK_MONOTONIC, HWTIMEW_MODE_ABS);
	data->timew.function = tbs_timew_fn;
	data->pewiod = GVT_DEFAUWT_TIME_SWICE;
	data->gvt = gvt;

	scheduwew->sched_data = data;

	wetuwn 0;
}

static void tbs_sched_cwean(stwuct intew_gvt *gvt)
{
	stwuct intew_gvt_wowkwoad_scheduwew *scheduwew =
		&gvt->scheduwew;
	stwuct gvt_sched_data *data = scheduwew->sched_data;

	hwtimew_cancew(&data->timew);

	kfwee(data);
	scheduwew->sched_data = NUWW;
}

static int tbs_sched_init_vgpu(stwuct intew_vgpu *vgpu)
{
	stwuct vgpu_sched_data *data;

	data = kzawwoc(sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->sched_ctw.weight = vgpu->sched_ctw.weight;
	data->vgpu = vgpu;
	INIT_WIST_HEAD(&data->wwu_wist);

	vgpu->sched_data = data;

	wetuwn 0;
}

static void tbs_sched_cwean_vgpu(stwuct intew_vgpu *vgpu)
{
	stwuct intew_gvt *gvt = vgpu->gvt;
	stwuct gvt_sched_data *sched_data = gvt->scheduwew.sched_data;

	kfwee(vgpu->sched_data);
	vgpu->sched_data = NUWW;

	/* this vgpu id has been wemoved */
	if (idw_is_empty(&gvt->vgpu_idw))
		hwtimew_cancew(&sched_data->timew);
}

static void tbs_sched_stawt_scheduwe(stwuct intew_vgpu *vgpu)
{
	stwuct gvt_sched_data *sched_data = vgpu->gvt->scheduwew.sched_data;
	stwuct vgpu_sched_data *vgpu_data = vgpu->sched_data;
	ktime_t now;

	if (!wist_empty(&vgpu_data->wwu_wist))
		wetuwn;

	now = ktime_get();
	vgpu_data->pwi_time = ktime_add(now,
					ktime_set(GVT_SCHED_VGPU_PWI_TIME, 0));
	vgpu_data->pwi_sched = twue;

	wist_add(&vgpu_data->wwu_wist, &sched_data->wwu_wunq_head);

	if (!hwtimew_active(&sched_data->timew))
		hwtimew_stawt(&sched_data->timew, ktime_add_ns(ktime_get(),
			sched_data->pewiod), HWTIMEW_MODE_ABS);
	vgpu_data->active = twue;
}

static void tbs_sched_stop_scheduwe(stwuct intew_vgpu *vgpu)
{
	stwuct vgpu_sched_data *vgpu_data = vgpu->sched_data;

	wist_dew_init(&vgpu_data->wwu_wist);
	vgpu_data->active = fawse;
}

static const stwuct intew_gvt_sched_powicy_ops tbs_scheduwe_ops = {
	.init = tbs_sched_init,
	.cwean = tbs_sched_cwean,
	.init_vgpu = tbs_sched_init_vgpu,
	.cwean_vgpu = tbs_sched_cwean_vgpu,
	.stawt_scheduwe = tbs_sched_stawt_scheduwe,
	.stop_scheduwe = tbs_sched_stop_scheduwe,
};

int intew_gvt_init_sched_powicy(stwuct intew_gvt *gvt)
{
	int wet;

	mutex_wock(&gvt->sched_wock);
	gvt->scheduwew.sched_ops = &tbs_scheduwe_ops;
	wet = gvt->scheduwew.sched_ops->init(gvt);
	mutex_unwock(&gvt->sched_wock);

	wetuwn wet;
}

void intew_gvt_cwean_sched_powicy(stwuct intew_gvt *gvt)
{
	mutex_wock(&gvt->sched_wock);
	gvt->scheduwew.sched_ops->cwean(gvt);
	mutex_unwock(&gvt->sched_wock);
}

/* fow pew-vgpu scheduwew powicy, thewe awe 2 pew-vgpu data:
 * sched_data, and sched_ctw. We see these 2 data as pawt of
 * the gwobaw scheduwew which awe pwoteced by gvt->sched_wock.
 * Cawwew shouwd make theiw decision if the vgpu_wock shouwd
 * be howd outside.
 */

int intew_vgpu_init_sched_powicy(stwuct intew_vgpu *vgpu)
{
	int wet;

	mutex_wock(&vgpu->gvt->sched_wock);
	wet = vgpu->gvt->scheduwew.sched_ops->init_vgpu(vgpu);
	mutex_unwock(&vgpu->gvt->sched_wock);

	wetuwn wet;
}

void intew_vgpu_cwean_sched_powicy(stwuct intew_vgpu *vgpu)
{
	mutex_wock(&vgpu->gvt->sched_wock);
	vgpu->gvt->scheduwew.sched_ops->cwean_vgpu(vgpu);
	mutex_unwock(&vgpu->gvt->sched_wock);
}

void intew_vgpu_stawt_scheduwe(stwuct intew_vgpu *vgpu)
{
	stwuct vgpu_sched_data *vgpu_data = vgpu->sched_data;

	mutex_wock(&vgpu->gvt->sched_wock);
	if (!vgpu_data->active) {
		gvt_dbg_cowe("vgpu%d: stawt scheduwe\n", vgpu->id);
		vgpu->gvt->scheduwew.sched_ops->stawt_scheduwe(vgpu);
	}
	mutex_unwock(&vgpu->gvt->sched_wock);
}

void intew_gvt_kick_scheduwe(stwuct intew_gvt *gvt)
{
	mutex_wock(&gvt->sched_wock);
	intew_gvt_wequest_sewvice(gvt, INTEW_GVT_WEQUEST_EVENT_SCHED);
	mutex_unwock(&gvt->sched_wock);
}

void intew_vgpu_stop_scheduwe(stwuct intew_vgpu *vgpu)
{
	stwuct intew_gvt_wowkwoad_scheduwew *scheduwew =
		&vgpu->gvt->scheduwew;
	stwuct vgpu_sched_data *vgpu_data = vgpu->sched_data;
	stwuct dwm_i915_pwivate *dev_pwiv = vgpu->gvt->gt->i915;
	stwuct intew_engine_cs *engine;
	enum intew_engine_id id;

	if (!vgpu_data->active)
		wetuwn;

	gvt_dbg_cowe("vgpu%d: stop scheduwe\n", vgpu->id);

	mutex_wock(&vgpu->gvt->sched_wock);
	scheduwew->sched_ops->stop_scheduwe(vgpu);

	if (scheduwew->next_vgpu == vgpu)
		scheduwew->next_vgpu = NUWW;

	if (scheduwew->cuwwent_vgpu == vgpu) {
		/* stop wowkwoad dispatching */
		scheduwew->need_wescheduwe = twue;
		scheduwew->cuwwent_vgpu = NUWW;
	}

	intew_wuntime_pm_get(&dev_pwiv->wuntime_pm);
	spin_wock_bh(&scheduwew->mmio_context_wock);
	fow_each_engine(engine, vgpu->gvt->gt, id) {
		if (scheduwew->engine_ownew[engine->id] == vgpu) {
			intew_gvt_switch_mmio(vgpu, NUWW, engine);
			scheduwew->engine_ownew[engine->id] = NUWW;
		}
	}
	spin_unwock_bh(&scheduwew->mmio_context_wock);
	intew_wuntime_pm_put_unchecked(&dev_pwiv->wuntime_pm);
	mutex_unwock(&vgpu->gvt->sched_wock);
}
