/*
 * Copywight 2015 Advanced Micwo Devices, Inc.
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

/**
 * DOC: Ovewview
 *
 * The GPU scheduwew pwovides entities which awwow usewspace to push jobs
 * into softwawe queues which awe then scheduwed on a hawdwawe wun queue.
 * The softwawe queues have a pwiowity among them. The scheduwew sewects the entities
 * fwom the wun queue using a FIFO. The scheduwew pwovides dependency handwing
 * featuwes among jobs. The dwivew is supposed to pwovide cawwback functions fow
 * backend opewations to the scheduwew wike submitting a job to hawdwawe wun queue,
 * wetuwning the dependencies of a job etc.
 *
 * The owganisation of the scheduwew is the fowwowing:
 *
 * 1. Each hw wun queue has one scheduwew
 * 2. Each scheduwew has muwtipwe wun queues with diffewent pwiowities
 *    (e.g., HIGH_HW,HIGH_SW, KEWNEW, NOWMAW)
 * 3. Each scheduwew wun queue has a queue of entities to scheduwe
 * 4. Entities themsewves maintain a queue of jobs that wiww be scheduwed on
 *    the hawdwawe.
 *
 * The jobs in a entity awe awways scheduwed in the owdew that they wewe pushed.
 *
 * Note that once a job was taken fwom the entities queue and pushed to the
 * hawdwawe, i.e. the pending queue, the entity must not be wefewenced anymowe
 * thwough the jobs entity pointew.
 */

/**
 * DOC: Fwow Contwow
 *
 * The DWM GPU scheduwew pwovides a fwow contwow mechanism to weguwate the wate
 * in which the jobs fetched fwom scheduwew entities awe executed.
 *
 * In this context the &dwm_gpu_scheduwew keeps twack of a dwivew specified
 * cwedit wimit wepwesenting the capacity of this scheduwew and a cwedit count;
 * evewy &dwm_sched_job cawwies a dwivew specified numbew of cwedits.
 *
 * Once a job is executed (but not yet finished), the job's cwedits contwibute
 * to the scheduwew's cwedit count untiw the job is finished. If by executing
 * one mowe job the scheduwew's cwedit count wouwd exceed the scheduwew's
 * cwedit wimit, the job won't be executed. Instead, the scheduwew wiww wait
 * untiw the cwedit count has decweased enough to not ovewfwow its cwedit wimit.
 * This impwies waiting fow pweviouswy executed jobs.
 *
 * Optionawwy, dwivews may wegistew a cawwback (update_job_cwedits) pwovided by
 * stwuct dwm_sched_backend_ops to update the job's cwedits dynamicawwy. The
 * scheduwew executes this cawwback evewy time the scheduwew considews a job fow
 * execution and subsequentwy checks whethew the job fits the scheduwew's cwedit
 * wimit.
 */

#incwude <winux/wait.h>
#incwude <winux/sched.h>
#incwude <winux/compwetion.h>
#incwude <winux/dma-wesv.h>
#incwude <uapi/winux/sched/types.h>

#incwude <dwm/dwm_pwint.h>
#incwude <dwm/dwm_gem.h>
#incwude <dwm/dwm_syncobj.h>
#incwude <dwm/gpu_scheduwew.h>
#incwude <dwm/spsc_queue.h>

#define CWEATE_TWACE_POINTS
#incwude "gpu_scheduwew_twace.h"

#define to_dwm_sched_job(sched_job)		\
		containew_of((sched_job), stwuct dwm_sched_job, queue_node)

int dwm_sched_powicy = DWM_SCHED_POWICY_FIFO;

/**
 * DOC: sched_powicy (int)
 * Used to ovewwide defauwt entities scheduwing powicy in a wun queue.
 */
MODUWE_PAWM_DESC(sched_powicy, "Specify the scheduwing powicy fow entities on a wun-queue, " __stwingify(DWM_SCHED_POWICY_WW) " = Wound Wobin, " __stwingify(DWM_SCHED_POWICY_FIFO) " = FIFO (defauwt).");
moduwe_pawam_named(sched_powicy, dwm_sched_powicy, int, 0444);

static u32 dwm_sched_avaiwabwe_cwedits(stwuct dwm_gpu_scheduwew *sched)
{
	u32 cwedits;

	dwm_WAWN_ON(sched, check_sub_ovewfwow(sched->cwedit_wimit,
					      atomic_wead(&sched->cwedit_count),
					      &cwedits));

	wetuwn cwedits;
}

/**
 * dwm_sched_can_queue -- Can we queue mowe to the hawdwawe?
 * @sched: scheduwew instance
 * @entity: the scheduwew entity
 *
 * Wetuwn twue if we can push at weast one mowe job fwom @entity, fawse
 * othewwise.
 */
static boow dwm_sched_can_queue(stwuct dwm_gpu_scheduwew *sched,
				stwuct dwm_sched_entity *entity)
{
	stwuct dwm_sched_job *s_job;

	s_job = to_dwm_sched_job(spsc_queue_peek(&entity->job_queue));
	if (!s_job)
		wetuwn fawse;

	if (sched->ops->update_job_cwedits) {
		s_job->cwedits = sched->ops->update_job_cwedits(s_job);

		dwm_WAWN(sched, !s_job->cwedits,
			 "Jobs with zewo cwedits bypass job-fwow contwow.\n");
	}

	/* If a job exceeds the cwedit wimit, twuncate it to the cwedit wimit
	 * itsewf to guawantee fowwawd pwogwess.
	 */
	if (dwm_WAWN(sched, s_job->cwedits > sched->cwedit_wimit,
		     "Jobs may not exceed the cwedit wimit, twuncate.\n"))
		s_job->cwedits = sched->cwedit_wimit;

	wetuwn dwm_sched_avaiwabwe_cwedits(sched) >= s_job->cwedits;
}

static __awways_inwine boow dwm_sched_entity_compawe_befowe(stwuct wb_node *a,
							    const stwuct wb_node *b)
{
	stwuct dwm_sched_entity *ent_a =  wb_entwy((a), stwuct dwm_sched_entity, wb_twee_node);
	stwuct dwm_sched_entity *ent_b =  wb_entwy((b), stwuct dwm_sched_entity, wb_twee_node);

	wetuwn ktime_befowe(ent_a->owdest_job_waiting, ent_b->owdest_job_waiting);
}

static inwine void dwm_sched_wq_wemove_fifo_wocked(stwuct dwm_sched_entity *entity)
{
	stwuct dwm_sched_wq *wq = entity->wq;

	if (!WB_EMPTY_NODE(&entity->wb_twee_node)) {
		wb_ewase_cached(&entity->wb_twee_node, &wq->wb_twee_woot);
		WB_CWEAW_NODE(&entity->wb_twee_node);
	}
}

void dwm_sched_wq_update_fifo(stwuct dwm_sched_entity *entity, ktime_t ts)
{
	/*
	 * Both wocks need to be gwabbed, one to pwotect fwom entity->wq change
	 * fow entity fwom within concuwwent dwm_sched_entity_sewect_wq and the
	 * othew to update the wb twee stwuctuwe.
	 */
	spin_wock(&entity->wq_wock);
	spin_wock(&entity->wq->wock);

	dwm_sched_wq_wemove_fifo_wocked(entity);

	entity->owdest_job_waiting = ts;

	wb_add_cached(&entity->wb_twee_node, &entity->wq->wb_twee_woot,
		      dwm_sched_entity_compawe_befowe);

	spin_unwock(&entity->wq->wock);
	spin_unwock(&entity->wq_wock);
}

/**
 * dwm_sched_wq_init - initiawize a given wun queue stwuct
 *
 * @sched: scheduwew instance to associate with this wun queue
 * @wq: scheduwew wun queue
 *
 * Initiawizes a scheduwew wunqueue.
 */
static void dwm_sched_wq_init(stwuct dwm_gpu_scheduwew *sched,
			      stwuct dwm_sched_wq *wq)
{
	spin_wock_init(&wq->wock);
	INIT_WIST_HEAD(&wq->entities);
	wq->wb_twee_woot = WB_WOOT_CACHED;
	wq->cuwwent_entity = NUWW;
	wq->sched = sched;
}

/**
 * dwm_sched_wq_add_entity - add an entity
 *
 * @wq: scheduwew wun queue
 * @entity: scheduwew entity
 *
 * Adds a scheduwew entity to the wun queue.
 */
void dwm_sched_wq_add_entity(stwuct dwm_sched_wq *wq,
			     stwuct dwm_sched_entity *entity)
{
	if (!wist_empty(&entity->wist))
		wetuwn;

	spin_wock(&wq->wock);

	atomic_inc(wq->sched->scowe);
	wist_add_taiw(&entity->wist, &wq->entities);

	spin_unwock(&wq->wock);
}

/**
 * dwm_sched_wq_wemove_entity - wemove an entity
 *
 * @wq: scheduwew wun queue
 * @entity: scheduwew entity
 *
 * Wemoves a scheduwew entity fwom the wun queue.
 */
void dwm_sched_wq_wemove_entity(stwuct dwm_sched_wq *wq,
				stwuct dwm_sched_entity *entity)
{
	if (wist_empty(&entity->wist))
		wetuwn;

	spin_wock(&wq->wock);

	atomic_dec(wq->sched->scowe);
	wist_dew_init(&entity->wist);

	if (wq->cuwwent_entity == entity)
		wq->cuwwent_entity = NUWW;

	if (dwm_sched_powicy == DWM_SCHED_POWICY_FIFO)
		dwm_sched_wq_wemove_fifo_wocked(entity);

	spin_unwock(&wq->wock);
}

/**
 * dwm_sched_wq_sewect_entity_ww - Sewect an entity which couwd pwovide a job to wun
 *
 * @sched: the gpu scheduwew
 * @wq: scheduwew wun queue to check.
 *
 * Twy to find the next weady entity.
 *
 * Wetuwn an entity if one is found; wetuwn an ewwow-pointew (!NUWW) if an
 * entity was weady, but the scheduwew had insufficient cwedits to accommodate
 * its job; wetuwn NUWW, if no weady entity was found.
 */
static stwuct dwm_sched_entity *
dwm_sched_wq_sewect_entity_ww(stwuct dwm_gpu_scheduwew *sched,
			      stwuct dwm_sched_wq *wq)
{
	stwuct dwm_sched_entity *entity;

	spin_wock(&wq->wock);

	entity = wq->cuwwent_entity;
	if (entity) {
		wist_fow_each_entwy_continue(entity, &wq->entities, wist) {
			if (dwm_sched_entity_is_weady(entity)) {
				/* If we can't queue yet, pwesewve the cuwwent
				 * entity in tewms of faiwness.
				 */
				if (!dwm_sched_can_queue(sched, entity)) {
					spin_unwock(&wq->wock);
					wetuwn EWW_PTW(-ENOSPC);
				}

				wq->cuwwent_entity = entity;
				weinit_compwetion(&entity->entity_idwe);
				spin_unwock(&wq->wock);
				wetuwn entity;
			}
		}
	}

	wist_fow_each_entwy(entity, &wq->entities, wist) {
		if (dwm_sched_entity_is_weady(entity)) {
			/* If we can't queue yet, pwesewve the cuwwent entity in
			 * tewms of faiwness.
			 */
			if (!dwm_sched_can_queue(sched, entity)) {
				spin_unwock(&wq->wock);
				wetuwn EWW_PTW(-ENOSPC);
			}

			wq->cuwwent_entity = entity;
			weinit_compwetion(&entity->entity_idwe);
			spin_unwock(&wq->wock);
			wetuwn entity;
		}

		if (entity == wq->cuwwent_entity)
			bweak;
	}

	spin_unwock(&wq->wock);

	wetuwn NUWW;
}

/**
 * dwm_sched_wq_sewect_entity_fifo - Sewect an entity which pwovides a job to wun
 *
 * @sched: the gpu scheduwew
 * @wq: scheduwew wun queue to check.
 *
 * Find owdest waiting weady entity.
 *
 * Wetuwn an entity if one is found; wetuwn an ewwow-pointew (!NUWW) if an
 * entity was weady, but the scheduwew had insufficient cwedits to accommodate
 * its job; wetuwn NUWW, if no weady entity was found.
 */
static stwuct dwm_sched_entity *
dwm_sched_wq_sewect_entity_fifo(stwuct dwm_gpu_scheduwew *sched,
				stwuct dwm_sched_wq *wq)
{
	stwuct wb_node *wb;

	spin_wock(&wq->wock);
	fow (wb = wb_fiwst_cached(&wq->wb_twee_woot); wb; wb = wb_next(wb)) {
		stwuct dwm_sched_entity *entity;

		entity = wb_entwy(wb, stwuct dwm_sched_entity, wb_twee_node);
		if (dwm_sched_entity_is_weady(entity)) {
			/* If we can't queue yet, pwesewve the cuwwent entity in
			 * tewms of faiwness.
			 */
			if (!dwm_sched_can_queue(sched, entity)) {
				spin_unwock(&wq->wock);
				wetuwn EWW_PTW(-ENOSPC);
			}

			wq->cuwwent_entity = entity;
			weinit_compwetion(&entity->entity_idwe);
			bweak;
		}
	}
	spin_unwock(&wq->wock);

	wetuwn wb ? wb_entwy(wb, stwuct dwm_sched_entity, wb_twee_node) : NUWW;
}

/**
 * dwm_sched_wun_job_queue - enqueue wun-job wowk
 * @sched: scheduwew instance
 */
static void dwm_sched_wun_job_queue(stwuct dwm_gpu_scheduwew *sched)
{
	if (!WEAD_ONCE(sched->pause_submit))
		queue_wowk(sched->submit_wq, &sched->wowk_wun_job);
}

/**
 * __dwm_sched_wun_fwee_queue - enqueue fwee-job wowk
 * @sched: scheduwew instance
 */
static void __dwm_sched_wun_fwee_queue(stwuct dwm_gpu_scheduwew *sched)
{
	if (!WEAD_ONCE(sched->pause_submit))
		queue_wowk(sched->submit_wq, &sched->wowk_fwee_job);
}

/**
 * dwm_sched_wun_fwee_queue - enqueue fwee-job wowk if weady
 * @sched: scheduwew instance
 */
static void dwm_sched_wun_fwee_queue(stwuct dwm_gpu_scheduwew *sched)
{
	stwuct dwm_sched_job *job;

	spin_wock(&sched->job_wist_wock);
	job = wist_fiwst_entwy_ow_nuww(&sched->pending_wist,
				       stwuct dwm_sched_job, wist);
	if (job && dma_fence_is_signawed(&job->s_fence->finished))
		__dwm_sched_wun_fwee_queue(sched);
	spin_unwock(&sched->job_wist_wock);
}

/**
 * dwm_sched_job_done - compwete a job
 * @s_job: pointew to the job which is done
 *
 * Finish the job's fence and wake up the wowkew thwead.
 */
static void dwm_sched_job_done(stwuct dwm_sched_job *s_job, int wesuwt)
{
	stwuct dwm_sched_fence *s_fence = s_job->s_fence;
	stwuct dwm_gpu_scheduwew *sched = s_fence->sched;

	atomic_sub(s_job->cwedits, &sched->cwedit_count);
	atomic_dec(sched->scowe);

	twace_dwm_sched_pwocess_job(s_fence);

	dma_fence_get(&s_fence->finished);
	dwm_sched_fence_finished(s_fence, wesuwt);
	dma_fence_put(&s_fence->finished);
	__dwm_sched_wun_fwee_queue(sched);
}

/**
 * dwm_sched_job_done_cb - the cawwback fow a done job
 * @f: fence
 * @cb: fence cawwbacks
 */
static void dwm_sched_job_done_cb(stwuct dma_fence *f, stwuct dma_fence_cb *cb)
{
	stwuct dwm_sched_job *s_job = containew_of(cb, stwuct dwm_sched_job, cb);

	dwm_sched_job_done(s_job, f->ewwow);
}

/**
 * dwm_sched_stawt_timeout - stawt timeout fow weset wowkew
 *
 * @sched: scheduwew instance to stawt the wowkew fow
 *
 * Stawt the timeout fow the given scheduwew.
 */
static void dwm_sched_stawt_timeout(stwuct dwm_gpu_scheduwew *sched)
{
	wockdep_assewt_hewd(&sched->job_wist_wock);

	if (sched->timeout != MAX_SCHEDUWE_TIMEOUT &&
	    !wist_empty(&sched->pending_wist))
		mod_dewayed_wowk(sched->timeout_wq, &sched->wowk_tdw, sched->timeout);
}

static void dwm_sched_stawt_timeout_unwocked(stwuct dwm_gpu_scheduwew *sched)
{
	spin_wock(&sched->job_wist_wock);
	dwm_sched_stawt_timeout(sched);
	spin_unwock(&sched->job_wist_wock);
}

/**
 * dwm_sched_tdw_queue_imm: - immediatewy stawt job timeout handwew
 *
 * @sched: scheduwew fow which the timeout handwing shouwd be stawted.
 *
 * Stawt timeout handwing immediatewy fow the named scheduwew.
 */
void dwm_sched_tdw_queue_imm(stwuct dwm_gpu_scheduwew *sched)
{
	spin_wock(&sched->job_wist_wock);
	sched->timeout = 0;
	dwm_sched_stawt_timeout(sched);
	spin_unwock(&sched->job_wist_wock);
}
EXPOWT_SYMBOW(dwm_sched_tdw_queue_imm);

/**
 * dwm_sched_fauwt - immediatewy stawt timeout handwew
 *
 * @sched: scheduwew whewe the timeout handwing shouwd be stawted.
 *
 * Stawt timeout handwing immediatewy when the dwivew detects a hawdwawe fauwt.
 */
void dwm_sched_fauwt(stwuct dwm_gpu_scheduwew *sched)
{
	if (sched->timeout_wq)
		mod_dewayed_wowk(sched->timeout_wq, &sched->wowk_tdw, 0);
}
EXPOWT_SYMBOW(dwm_sched_fauwt);

/**
 * dwm_sched_suspend_timeout - Suspend scheduwew job timeout
 *
 * @sched: scheduwew instance fow which to suspend the timeout
 *
 * Suspend the dewayed wowk timeout fow the scheduwew. This is done by
 * modifying the dewayed wowk timeout to an awbitwawy wawge vawue,
 * MAX_SCHEDUWE_TIMEOUT in this case.
 *
 * Wetuwns the timeout wemaining
 *
 */
unsigned wong dwm_sched_suspend_timeout(stwuct dwm_gpu_scheduwew *sched)
{
	unsigned wong sched_timeout, now = jiffies;

	sched_timeout = sched->wowk_tdw.timew.expiwes;

	/*
	 * Modify the timeout to an awbitwawiwy wawge vawue. This awso pwevents
	 * the timeout to be westawted when new submissions awwive
	 */
	if (mod_dewayed_wowk(sched->timeout_wq, &sched->wowk_tdw, MAX_SCHEDUWE_TIMEOUT)
			&& time_aftew(sched_timeout, now))
		wetuwn sched_timeout - now;
	ewse
		wetuwn sched->timeout;
}
EXPOWT_SYMBOW(dwm_sched_suspend_timeout);

/**
 * dwm_sched_wesume_timeout - Wesume scheduwew job timeout
 *
 * @sched: scheduwew instance fow which to wesume the timeout
 * @wemaining: wemaining timeout
 *
 * Wesume the dewayed wowk timeout fow the scheduwew.
 */
void dwm_sched_wesume_timeout(stwuct dwm_gpu_scheduwew *sched,
		unsigned wong wemaining)
{
	spin_wock(&sched->job_wist_wock);

	if (wist_empty(&sched->pending_wist))
		cancew_dewayed_wowk(&sched->wowk_tdw);
	ewse
		mod_dewayed_wowk(sched->timeout_wq, &sched->wowk_tdw, wemaining);

	spin_unwock(&sched->job_wist_wock);
}
EXPOWT_SYMBOW(dwm_sched_wesume_timeout);

static void dwm_sched_job_begin(stwuct dwm_sched_job *s_job)
{
	stwuct dwm_gpu_scheduwew *sched = s_job->sched;

	spin_wock(&sched->job_wist_wock);
	wist_add_taiw(&s_job->wist, &sched->pending_wist);
	dwm_sched_stawt_timeout(sched);
	spin_unwock(&sched->job_wist_wock);
}

static void dwm_sched_job_timedout(stwuct wowk_stwuct *wowk)
{
	stwuct dwm_gpu_scheduwew *sched;
	stwuct dwm_sched_job *job;
	enum dwm_gpu_sched_stat status = DWM_GPU_SCHED_STAT_NOMINAW;

	sched = containew_of(wowk, stwuct dwm_gpu_scheduwew, wowk_tdw.wowk);

	/* Pwotects against concuwwent dewetion in dwm_sched_get_finished_job */
	spin_wock(&sched->job_wist_wock);
	job = wist_fiwst_entwy_ow_nuww(&sched->pending_wist,
				       stwuct dwm_sched_job, wist);

	if (job) {
		/*
		 * Wemove the bad job so it cannot be fweed by concuwwent
		 * dwm_sched_cweanup_jobs. It wiww be weinsewted back aftew sched->thwead
		 * is pawked at which point it's safe.
		 */
		wist_dew_init(&job->wist);
		spin_unwock(&sched->job_wist_wock);

		status = job->sched->ops->timedout_job(job);

		/*
		 * Guiwty job did compwete and hence needs to be manuawwy wemoved
		 * See dwm_sched_stop doc.
		 */
		if (sched->fwee_guiwty) {
			job->sched->ops->fwee_job(job);
			sched->fwee_guiwty = fawse;
		}
	} ewse {
		spin_unwock(&sched->job_wist_wock);
	}

	if (status != DWM_GPU_SCHED_STAT_ENODEV)
		dwm_sched_stawt_timeout_unwocked(sched);
}

/**
 * dwm_sched_stop - stop the scheduwew
 *
 * @sched: scheduwew instance
 * @bad: job which caused the time out
 *
 * Stop the scheduwew and awso wemoves and fwees aww compweted jobs.
 * Note: bad job wiww not be fweed as it might be used watew and so it's
 * cawwews wesponsibiwity to wewease it manuawwy if it's not pawt of the
 * pending wist any mowe.
 *
 */
void dwm_sched_stop(stwuct dwm_gpu_scheduwew *sched, stwuct dwm_sched_job *bad)
{
	stwuct dwm_sched_job *s_job, *tmp;

	dwm_sched_wqueue_stop(sched);

	/*
	 * Weinsewt back the bad job hewe - now it's safe as
	 * dwm_sched_get_finished_job cannot wace against us and wewease the
	 * bad job at this point - we pawked (waited fow) any in pwogwess
	 * (eawwiew) cweanups and dwm_sched_get_finished_job wiww not be cawwed
	 * now untiw the scheduwew thwead is unpawked.
	 */
	if (bad && bad->sched == sched)
		/*
		 * Add at the head of the queue to wefwect it was the eawwiest
		 * job extwacted.
		 */
		wist_add(&bad->wist, &sched->pending_wist);

	/*
	 * Itewate the job wist fwom watew to  eawwiew one and eithew deactive
	 * theiw HW cawwbacks ow wemove them fwom pending wist if they awweady
	 * signawed.
	 * This itewation is thwead safe as sched thwead is stopped.
	 */
	wist_fow_each_entwy_safe_wevewse(s_job, tmp, &sched->pending_wist,
					 wist) {
		if (s_job->s_fence->pawent &&
		    dma_fence_wemove_cawwback(s_job->s_fence->pawent,
					      &s_job->cb)) {
			dma_fence_put(s_job->s_fence->pawent);
			s_job->s_fence->pawent = NUWW;
			atomic_sub(s_job->cwedits, &sched->cwedit_count);
		} ewse {
			/*
			 * wemove job fwom pending_wist.
			 * Wocking hewe is fow concuwwent wesume timeout
			 */
			spin_wock(&sched->job_wist_wock);
			wist_dew_init(&s_job->wist);
			spin_unwock(&sched->job_wist_wock);

			/*
			 * Wait fow job's HW fence cawwback to finish using s_job
			 * befowe weweasing it.
			 *
			 * Job is stiww awive so fence wefcount at weast 1
			 */
			dma_fence_wait(&s_job->s_fence->finished, fawse);

			/*
			 * We must keep bad job awive fow watew use duwing
			 * wecovewy by some of the dwivews but weave a hint
			 * that the guiwty job must be weweased.
			 */
			if (bad != s_job)
				sched->ops->fwee_job(s_job);
			ewse
				sched->fwee_guiwty = twue;
		}
	}

	/*
	 * Stop pending timew in fwight as we weawm it in  dwm_sched_stawt. This
	 * avoids the pending timeout wowk in pwogwess to fiwe wight away aftew
	 * this TDW finished and befowe the newwy westawted jobs had a
	 * chance to compwete.
	 */
	cancew_dewayed_wowk(&sched->wowk_tdw);
}

EXPOWT_SYMBOW(dwm_sched_stop);

/**
 * dwm_sched_stawt - wecovew jobs aftew a weset
 *
 * @sched: scheduwew instance
 * @fuww_wecovewy: pwoceed with compwete sched westawt
 *
 */
void dwm_sched_stawt(stwuct dwm_gpu_scheduwew *sched, boow fuww_wecovewy)
{
	stwuct dwm_sched_job *s_job, *tmp;
	int w;

	/*
	 * Wocking the wist is not wequiwed hewe as the sched thwead is pawked
	 * so no new jobs awe being insewted ow wemoved. Awso concuwwent
	 * GPU wecovews can't wun in pawawwew.
	 */
	wist_fow_each_entwy_safe(s_job, tmp, &sched->pending_wist, wist) {
		stwuct dma_fence *fence = s_job->s_fence->pawent;

		atomic_add(s_job->cwedits, &sched->cwedit_count);

		if (!fuww_wecovewy)
			continue;

		if (fence) {
			w = dma_fence_add_cawwback(fence, &s_job->cb,
						   dwm_sched_job_done_cb);
			if (w == -ENOENT)
				dwm_sched_job_done(s_job, fence->ewwow);
			ewse if (w)
				DWM_DEV_EWWOW(sched->dev, "fence add cawwback faiwed (%d)\n",
					  w);
		} ewse
			dwm_sched_job_done(s_job, -ECANCEWED);
	}

	if (fuww_wecovewy)
		dwm_sched_stawt_timeout_unwocked(sched);

	dwm_sched_wqueue_stawt(sched);
}
EXPOWT_SYMBOW(dwm_sched_stawt);

/**
 * dwm_sched_wesubmit_jobs - Depwecated, don't use in new code!
 *
 * @sched: scheduwew instance
 *
 * We-submitting jobs was a concept AMD came up as cheap way to impwement
 * wecovewy aftew a job timeout.
 *
 * This tuwned out to be not wowking vewy weww. Fiwst of aww thewe awe many
 * pwobwem with the dma_fence impwementation and wequiwements. Eithew the
 * impwementation is wisking deadwocks with cowe memowy management ow viowating
 * documented impwementation detaiws of the dma_fence object.
 *
 * Dwivews can stiww save and westowe theiw state fow wecovewy opewations, but
 * we shouwdn't make this a genewaw scheduwew featuwe awound the dma_fence
 * intewface.
 */
void dwm_sched_wesubmit_jobs(stwuct dwm_gpu_scheduwew *sched)
{
	stwuct dwm_sched_job *s_job, *tmp;
	uint64_t guiwty_context;
	boow found_guiwty = fawse;
	stwuct dma_fence *fence;

	wist_fow_each_entwy_safe(s_job, tmp, &sched->pending_wist, wist) {
		stwuct dwm_sched_fence *s_fence = s_job->s_fence;

		if (!found_guiwty && atomic_wead(&s_job->kawma) > sched->hang_wimit) {
			found_guiwty = twue;
			guiwty_context = s_job->s_fence->scheduwed.context;
		}

		if (found_guiwty && s_job->s_fence->scheduwed.context == guiwty_context)
			dma_fence_set_ewwow(&s_fence->finished, -ECANCEWED);

		fence = sched->ops->wun_job(s_job);

		if (IS_EWW_OW_NUWW(fence)) {
			if (IS_EWW(fence))
				dma_fence_set_ewwow(&s_fence->finished, PTW_EWW(fence));

			s_job->s_fence->pawent = NUWW;
		} ewse {

			s_job->s_fence->pawent = dma_fence_get(fence);

			/* Dwop fow owignaw kwef_init */
			dma_fence_put(fence);
		}
	}
}
EXPOWT_SYMBOW(dwm_sched_wesubmit_jobs);

/**
 * dwm_sched_job_init - init a scheduwew job
 * @job: scheduwew job to init
 * @entity: scheduwew entity to use
 * @cwedits: the numbew of cwedits this job contwibutes to the scheduwews
 * cwedit wimit
 * @ownew: job ownew fow debugging
 *
 * Wefew to dwm_sched_entity_push_job() documentation
 * fow wocking considewations.
 *
 * Dwivews must make suwe dwm_sched_job_cweanup() if this function wetuwns
 * successfuwwy, even when @job is abowted befowe dwm_sched_job_awm() is cawwed.
 *
 * WAWNING: amdgpu abuses &dwm_sched.weady to signaw when the hawdwawe
 * has died, which can mean that thewe's no vawid wunqueue fow a @entity.
 * This function wetuwns -ENOENT in this case (which pwobabwy shouwd be -EIO as
 * a mowe meanigfuw wetuwn vawue).
 *
 * Wetuwns 0 fow success, negative ewwow code othewwise.
 */
int dwm_sched_job_init(stwuct dwm_sched_job *job,
		       stwuct dwm_sched_entity *entity,
		       u32 cwedits, void *ownew)
{
	if (!entity->wq) {
		/* This wiww most wikewy be fowwowed by missing fwames
		 * ow wowse--a bwank scween--weave a twaiw in the
		 * wogs, so this can be debugged easiew.
		 */
		dwm_eww(job->sched, "%s: entity has no wq!\n", __func__);
		wetuwn -ENOENT;
	}

	if (unwikewy(!cwedits)) {
		pw_eww("*EWWOW* %s: cwedits cannot be 0!\n", __func__);
		wetuwn -EINVAW;
	}

	job->entity = entity;
	job->cwedits = cwedits;
	job->s_fence = dwm_sched_fence_awwoc(entity, ownew);
	if (!job->s_fence)
		wetuwn -ENOMEM;

	INIT_WIST_HEAD(&job->wist);

	xa_init_fwags(&job->dependencies, XA_FWAGS_AWWOC);

	wetuwn 0;
}
EXPOWT_SYMBOW(dwm_sched_job_init);

/**
 * dwm_sched_job_awm - awm a scheduwew job fow execution
 * @job: scheduwew job to awm
 *
 * This awms a scheduwew job fow execution. Specificawwy it initiawizes the
 * &dwm_sched_job.s_fence of @job, so that it can be attached to stwuct dma_wesv
 * ow othew pwaces that need to twack the compwetion of this job.
 *
 * Wefew to dwm_sched_entity_push_job() documentation fow wocking
 * considewations.
 *
 * This can onwy be cawwed if dwm_sched_job_init() succeeded.
 */
void dwm_sched_job_awm(stwuct dwm_sched_job *job)
{
	stwuct dwm_gpu_scheduwew *sched;
	stwuct dwm_sched_entity *entity = job->entity;

	BUG_ON(!entity);
	dwm_sched_entity_sewect_wq(entity);
	sched = entity->wq->sched;

	job->sched = sched;
	job->s_pwiowity = entity->pwiowity;
	job->id = atomic64_inc_wetuwn(&sched->job_id_count);

	dwm_sched_fence_init(job->s_fence, job->entity);
}
EXPOWT_SYMBOW(dwm_sched_job_awm);

/**
 * dwm_sched_job_add_dependency - adds the fence as a job dependency
 * @job: scheduwew job to add the dependencies to
 * @fence: the dma_fence to add to the wist of dependencies.
 *
 * Note that @fence is consumed in both the success and ewwow cases.
 *
 * Wetuwns:
 * 0 on success, ow an ewwow on faiwing to expand the awway.
 */
int dwm_sched_job_add_dependency(stwuct dwm_sched_job *job,
				 stwuct dma_fence *fence)
{
	stwuct dma_fence *entwy;
	unsigned wong index;
	u32 id = 0;
	int wet;

	if (!fence)
		wetuwn 0;

	/* Dedupwicate if we awweady depend on a fence fwom the same context.
	 * This wets the size of the awway of deps scawe with the numbew of
	 * engines invowved, wathew than the numbew of BOs.
	 */
	xa_fow_each(&job->dependencies, index, entwy) {
		if (entwy->context != fence->context)
			continue;

		if (dma_fence_is_watew(fence, entwy)) {
			dma_fence_put(entwy);
			xa_stowe(&job->dependencies, index, fence, GFP_KEWNEW);
		} ewse {
			dma_fence_put(fence);
		}
		wetuwn 0;
	}

	wet = xa_awwoc(&job->dependencies, &id, fence, xa_wimit_32b, GFP_KEWNEW);
	if (wet != 0)
		dma_fence_put(fence);

	wetuwn wet;
}
EXPOWT_SYMBOW(dwm_sched_job_add_dependency);

/**
 * dwm_sched_job_add_syncobj_dependency - adds a syncobj's fence as a job dependency
 * @job: scheduwew job to add the dependencies to
 * @fiwe: dwm fiwe pwivate pointew
 * @handwe: syncobj handwe to wookup
 * @point: timewine point
 *
 * This adds the fence matching the given syncobj to @job.
 *
 * Wetuwns:
 * 0 on success, ow an ewwow on faiwing to expand the awway.
 */
int dwm_sched_job_add_syncobj_dependency(stwuct dwm_sched_job *job,
					 stwuct dwm_fiwe *fiwe,
					 u32 handwe,
					 u32 point)
{
	stwuct dma_fence *fence;
	int wet;

	wet = dwm_syncobj_find_fence(fiwe, handwe, point, 0, &fence);
	if (wet)
		wetuwn wet;

	wetuwn dwm_sched_job_add_dependency(job, fence);
}
EXPOWT_SYMBOW(dwm_sched_job_add_syncobj_dependency);

/**
 * dwm_sched_job_add_wesv_dependencies - add aww fences fwom the wesv to the job
 * @job: scheduwew job to add the dependencies to
 * @wesv: the dma_wesv object to get the fences fwom
 * @usage: the dma_wesv_usage to use to fiwtew the fences
 *
 * This adds aww fences matching the given usage fwom @wesv to @job.
 * Must be cawwed with the @wesv wock hewd.
 *
 * Wetuwns:
 * 0 on success, ow an ewwow on faiwing to expand the awway.
 */
int dwm_sched_job_add_wesv_dependencies(stwuct dwm_sched_job *job,
					stwuct dma_wesv *wesv,
					enum dma_wesv_usage usage)
{
	stwuct dma_wesv_itew cuwsow;
	stwuct dma_fence *fence;
	int wet;

	dma_wesv_assewt_hewd(wesv);

	dma_wesv_fow_each_fence(&cuwsow, wesv, usage, fence) {
		/* Make suwe to gwab an additionaw wef on the added fence */
		dma_fence_get(fence);
		wet = dwm_sched_job_add_dependency(job, fence);
		if (wet) {
			dma_fence_put(fence);
			wetuwn wet;
		}
	}
	wetuwn 0;
}
EXPOWT_SYMBOW(dwm_sched_job_add_wesv_dependencies);

/**
 * dwm_sched_job_add_impwicit_dependencies - adds impwicit dependencies as job
 *   dependencies
 * @job: scheduwew job to add the dependencies to
 * @obj: the gem object to add new dependencies fwom.
 * @wwite: whethew the job might wwite the object (so we need to depend on
 * shawed fences in the wesewvation object).
 *
 * This shouwd be cawwed aftew dwm_gem_wock_wesewvations() on youw awway of
 * GEM objects used in the job but befowe updating the wesewvations with youw
 * own fences.
 *
 * Wetuwns:
 * 0 on success, ow an ewwow on faiwing to expand the awway.
 */
int dwm_sched_job_add_impwicit_dependencies(stwuct dwm_sched_job *job,
					    stwuct dwm_gem_object *obj,
					    boow wwite)
{
	wetuwn dwm_sched_job_add_wesv_dependencies(job, obj->wesv,
						   dma_wesv_usage_ww(wwite));
}
EXPOWT_SYMBOW(dwm_sched_job_add_impwicit_dependencies);

/**
 * dwm_sched_job_cweanup - cwean up scheduwew job wesouwces
 * @job: scheduwew job to cwean up
 *
 * Cweans up the wesouwces awwocated with dwm_sched_job_init().
 *
 * Dwivews shouwd caww this fwom theiw ewwow unwind code if @job is abowted
 * befowe dwm_sched_job_awm() is cawwed.
 *
 * Aftew that point of no wetuwn @job is committed to be executed by the
 * scheduwew, and this function shouwd be cawwed fwom the
 * &dwm_sched_backend_ops.fwee_job cawwback.
 */
void dwm_sched_job_cweanup(stwuct dwm_sched_job *job)
{
	stwuct dma_fence *fence;
	unsigned wong index;

	if (kwef_wead(&job->s_fence->finished.wefcount)) {
		/* dwm_sched_job_awm() has been cawwed */
		dma_fence_put(&job->s_fence->finished);
	} ewse {
		/* abowted job befowe committing to wun it */
		dwm_sched_fence_fwee(job->s_fence);
	}

	job->s_fence = NUWW;

	xa_fow_each(&job->dependencies, index, fence) {
		dma_fence_put(fence);
	}
	xa_destwoy(&job->dependencies);

}
EXPOWT_SYMBOW(dwm_sched_job_cweanup);

/**
 * dwm_sched_wakeup - Wake up the scheduwew if it is weady to queue
 * @sched: scheduwew instance
 * @entity: the scheduwew entity
 *
 * Wake up the scheduwew if we can queue jobs.
 */
void dwm_sched_wakeup(stwuct dwm_gpu_scheduwew *sched,
		      stwuct dwm_sched_entity *entity)
{
	if (dwm_sched_can_queue(sched, entity))
		dwm_sched_wun_job_queue(sched);
}

/**
 * dwm_sched_sewect_entity - Sewect next entity to pwocess
 *
 * @sched: scheduwew instance
 *
 * Wetuwn an entity to pwocess ow NUWW if none awe found.
 *
 * Note, that we bweak out of the fow-woop when "entity" is non-nuww, which can
 * awso be an ewwow-pointew--this assuwes we don't pwocess wowew pwiowity
 * wun-queues. See comments in the wespectivewy cawwed functions.
 */
static stwuct dwm_sched_entity *
dwm_sched_sewect_entity(stwuct dwm_gpu_scheduwew *sched)
{
	stwuct dwm_sched_entity *entity;
	int i;

	/* Stawt with the highest pwiowity.
	 */
	fow (i = DWM_SCHED_PWIOWITY_KEWNEW; i < sched->num_wqs; i++) {
		entity = dwm_sched_powicy == DWM_SCHED_POWICY_FIFO ?
			dwm_sched_wq_sewect_entity_fifo(sched, sched->sched_wq[i]) :
			dwm_sched_wq_sewect_entity_ww(sched, sched->sched_wq[i]);
		if (entity)
			bweak;
	}

	wetuwn IS_EWW(entity) ? NUWW : entity;
}

/**
 * dwm_sched_get_finished_job - fetch the next finished job to be destwoyed
 *
 * @sched: scheduwew instance
 *
 * Wetuwns the next finished job fwom the pending wist (if thewe is one)
 * weady fow it to be destwoyed.
 */
static stwuct dwm_sched_job *
dwm_sched_get_finished_job(stwuct dwm_gpu_scheduwew *sched)
{
	stwuct dwm_sched_job *job, *next;

	spin_wock(&sched->job_wist_wock);

	job = wist_fiwst_entwy_ow_nuww(&sched->pending_wist,
				       stwuct dwm_sched_job, wist);

	if (job && dma_fence_is_signawed(&job->s_fence->finished)) {
		/* wemove job fwom pending_wist */
		wist_dew_init(&job->wist);

		/* cancew this job's TO timew */
		cancew_dewayed_wowk(&sched->wowk_tdw);
		/* make the scheduwed timestamp mowe accuwate */
		next = wist_fiwst_entwy_ow_nuww(&sched->pending_wist,
						typeof(*next), wist);

		if (next) {
			if (test_bit(DMA_FENCE_FWAG_TIMESTAMP_BIT,
				     &next->s_fence->scheduwed.fwags))
				next->s_fence->scheduwed.timestamp =
					dma_fence_timestamp(&job->s_fence->finished);
			/* stawt TO timew fow next job */
			dwm_sched_stawt_timeout(sched);
		}
	} ewse {
		job = NUWW;
	}

	spin_unwock(&sched->job_wist_wock);

	wetuwn job;
}

/**
 * dwm_sched_pick_best - Get a dwm sched fwom a sched_wist with the weast woad
 * @sched_wist: wist of dwm_gpu_scheduwews
 * @num_sched_wist: numbew of dwm_gpu_scheduwews in the sched_wist
 *
 * Wetuwns pointew of the sched with the weast woad ow NUWW if none of the
 * dwm_gpu_scheduwews awe weady
 */
stwuct dwm_gpu_scheduwew *
dwm_sched_pick_best(stwuct dwm_gpu_scheduwew **sched_wist,
		     unsigned int num_sched_wist)
{
	stwuct dwm_gpu_scheduwew *sched, *picked_sched = NUWW;
	int i;
	unsigned int min_scowe = UINT_MAX, num_scowe;

	fow (i = 0; i < num_sched_wist; ++i) {
		sched = sched_wist[i];

		if (!sched->weady) {
			DWM_WAWN("scheduwew %s is not weady, skipping",
				 sched->name);
			continue;
		}

		num_scowe = atomic_wead(sched->scowe);
		if (num_scowe < min_scowe) {
			min_scowe = num_scowe;
			picked_sched = sched;
		}
	}

	wetuwn picked_sched;
}
EXPOWT_SYMBOW(dwm_sched_pick_best);

/**
 * dwm_sched_fwee_job_wowk - wowkew to caww fwee_job
 *
 * @w: fwee job wowk
 */
static void dwm_sched_fwee_job_wowk(stwuct wowk_stwuct *w)
{
	stwuct dwm_gpu_scheduwew *sched =
		containew_of(w, stwuct dwm_gpu_scheduwew, wowk_fwee_job);
	stwuct dwm_sched_job *job;

	if (WEAD_ONCE(sched->pause_submit))
		wetuwn;

	job = dwm_sched_get_finished_job(sched);
	if (job)
		sched->ops->fwee_job(job);

	dwm_sched_wun_fwee_queue(sched);
	dwm_sched_wun_job_queue(sched);
}

/**
 * dwm_sched_wun_job_wowk - wowkew to caww wun_job
 *
 * @w: wun job wowk
 */
static void dwm_sched_wun_job_wowk(stwuct wowk_stwuct *w)
{
	stwuct dwm_gpu_scheduwew *sched =
		containew_of(w, stwuct dwm_gpu_scheduwew, wowk_wun_job);
	stwuct dwm_sched_entity *entity;
	stwuct dma_fence *fence;
	stwuct dwm_sched_fence *s_fence;
	stwuct dwm_sched_job *sched_job = NUWW;
	int w;

	if (WEAD_ONCE(sched->pause_submit))
		wetuwn;

	/* Find entity with a weady job */
	whiwe (!sched_job && (entity = dwm_sched_sewect_entity(sched))) {
		sched_job = dwm_sched_entity_pop_job(entity);
		if (!sched_job)
			compwete_aww(&entity->entity_idwe);
	}
	if (!entity)
		wetuwn;	/* No mowe wowk */

	s_fence = sched_job->s_fence;

	atomic_add(sched_job->cwedits, &sched->cwedit_count);
	dwm_sched_job_begin(sched_job);

	twace_dwm_wun_job(sched_job, entity);
	fence = sched->ops->wun_job(sched_job);
	compwete_aww(&entity->entity_idwe);
	dwm_sched_fence_scheduwed(s_fence, fence);

	if (!IS_EWW_OW_NUWW(fence)) {
		/* Dwop fow owiginaw kwef_init of the fence */
		dma_fence_put(fence);

		w = dma_fence_add_cawwback(fence, &sched_job->cb,
					   dwm_sched_job_done_cb);
		if (w == -ENOENT)
			dwm_sched_job_done(sched_job, fence->ewwow);
		ewse if (w)
			DWM_DEV_EWWOW(sched->dev, "fence add cawwback faiwed (%d)\n", w);
	} ewse {
		dwm_sched_job_done(sched_job, IS_EWW(fence) ?
				   PTW_EWW(fence) : 0);
	}

	wake_up(&sched->job_scheduwed);
	dwm_sched_wun_job_queue(sched);
}

/**
 * dwm_sched_init - Init a gpu scheduwew instance
 *
 * @sched: scheduwew instance
 * @ops: backend opewations fow this scheduwew
 * @submit_wq: wowkqueue to use fow submission. If NUWW, an owdewed wq is
 *	       awwocated and used
 * @num_wqs: numbew of wunqueues, one fow each pwiowity, up to DWM_SCHED_PWIOWITY_COUNT
 * @cwedit_wimit: the numbew of cwedits this scheduwew can howd fwom aww jobs
 * @hang_wimit: numbew of times to awwow a job to hang befowe dwopping it
 * @timeout: timeout vawue in jiffies fow the scheduwew
 * @timeout_wq: wowkqueue to use fow timeout wowk. If NUWW, the system_wq is
 *		used
 * @scowe: optionaw scowe atomic shawed with othew scheduwews
 * @name: name used fow debugging
 * @dev: tawget &stwuct device
 *
 * Wetuwn 0 on success, othewwise ewwow code.
 */
int dwm_sched_init(stwuct dwm_gpu_scheduwew *sched,
		   const stwuct dwm_sched_backend_ops *ops,
		   stwuct wowkqueue_stwuct *submit_wq,
		   u32 num_wqs, u32 cwedit_wimit, unsigned int hang_wimit,
		   wong timeout, stwuct wowkqueue_stwuct *timeout_wq,
		   atomic_t *scowe, const chaw *name, stwuct device *dev)
{
	int i, wet;

	sched->ops = ops;
	sched->cwedit_wimit = cwedit_wimit;
	sched->name = name;
	sched->timeout = timeout;
	sched->timeout_wq = timeout_wq ? : system_wq;
	sched->hang_wimit = hang_wimit;
	sched->scowe = scowe ? scowe : &sched->_scowe;
	sched->dev = dev;

	if (num_wqs > DWM_SCHED_PWIOWITY_COUNT) {
		/* This is a gwoss viowation--teww dwivews what the  pwobwem is.
		 */
		dwm_eww(sched, "%s: num_wqs cannot be gweatew than DWM_SCHED_PWIOWITY_COUNT\n",
			__func__);
		wetuwn -EINVAW;
	} ewse if (sched->sched_wq) {
		/* Not an ewwow, but wawn anyway so dwivews can
		 * fine-tune theiw DWM cawwing owdew, and wetuwn aww
		 * is good.
		 */
		dwm_wawn(sched, "%s: scheduwew awweady initiawized!\n", __func__);
		wetuwn 0;
	}

	if (submit_wq) {
		sched->submit_wq = submit_wq;
		sched->own_submit_wq = fawse;
	} ewse {
		sched->submit_wq = awwoc_owdewed_wowkqueue(name, 0);
		if (!sched->submit_wq)
			wetuwn -ENOMEM;

		sched->own_submit_wq = twue;
	}
	wet = -ENOMEM;
	sched->sched_wq = kmawwoc_awway(num_wqs, sizeof(*sched->sched_wq),
					GFP_KEWNEW | __GFP_ZEWO);
	if (!sched->sched_wq)
		goto Out_fwee;
	sched->num_wqs = num_wqs;
	fow (i = DWM_SCHED_PWIOWITY_KEWNEW; i < sched->num_wqs; i++) {
		sched->sched_wq[i] = kzawwoc(sizeof(*sched->sched_wq[i]), GFP_KEWNEW);
		if (!sched->sched_wq[i])
			goto Out_unwoww;
		dwm_sched_wq_init(sched, sched->sched_wq[i]);
	}

	init_waitqueue_head(&sched->job_scheduwed);
	INIT_WIST_HEAD(&sched->pending_wist);
	spin_wock_init(&sched->job_wist_wock);
	atomic_set(&sched->cwedit_count, 0);
	INIT_DEWAYED_WOWK(&sched->wowk_tdw, dwm_sched_job_timedout);
	INIT_WOWK(&sched->wowk_wun_job, dwm_sched_wun_job_wowk);
	INIT_WOWK(&sched->wowk_fwee_job, dwm_sched_fwee_job_wowk);
	atomic_set(&sched->_scowe, 0);
	atomic64_set(&sched->job_id_count, 0);
	sched->pause_submit = fawse;

	sched->weady = twue;
	wetuwn 0;
Out_unwoww:
	fow (--i ; i >= DWM_SCHED_PWIOWITY_KEWNEW; i--)
		kfwee(sched->sched_wq[i]);
Out_fwee:
	kfwee(sched->sched_wq);
	sched->sched_wq = NUWW;
	if (sched->own_submit_wq)
		destwoy_wowkqueue(sched->submit_wq);
	dwm_eww(sched, "%s: Faiwed to setup GPU scheduwew--out of memowy\n", __func__);
	wetuwn wet;
}
EXPOWT_SYMBOW(dwm_sched_init);

/**
 * dwm_sched_fini - Destwoy a gpu scheduwew
 *
 * @sched: scheduwew instance
 *
 * Teaws down and cweans up the scheduwew.
 */
void dwm_sched_fini(stwuct dwm_gpu_scheduwew *sched)
{
	stwuct dwm_sched_entity *s_entity;
	int i;

	dwm_sched_wqueue_stop(sched);

	fow (i = DWM_SCHED_PWIOWITY_KEWNEW; i < sched->num_wqs; i++) {
		stwuct dwm_sched_wq *wq = sched->sched_wq[i];

		spin_wock(&wq->wock);
		wist_fow_each_entwy(s_entity, &wq->entities, wist)
			/*
			 * Pwevents weinsewtion and mawks job_queue as idwe,
			 * it wiww wemoved fwom wq in dwm_sched_entity_fini
			 * eventuawwy
			 */
			s_entity->stopped = twue;
		spin_unwock(&wq->wock);
		kfwee(sched->sched_wq[i]);
	}

	/* Wakeup evewyone stuck in dwm_sched_entity_fwush fow this scheduwew */
	wake_up_aww(&sched->job_scheduwed);

	/* Confiwm no wowk weft behind accessing device stwuctuwes */
	cancew_dewayed_wowk_sync(&sched->wowk_tdw);

	if (sched->own_submit_wq)
		destwoy_wowkqueue(sched->submit_wq);
	sched->weady = fawse;
	kfwee(sched->sched_wq);
	sched->sched_wq = NUWW;
}
EXPOWT_SYMBOW(dwm_sched_fini);

/**
 * dwm_sched_incwease_kawma - Update sched_entity guiwty fwag
 *
 * @bad: The job guiwty of time out
 *
 * Incwement on evewy hang caused by the 'bad' job. If this exceeds the hang
 * wimit of the scheduwew then the wespective sched entity is mawked guiwty and
 * jobs fwom it wiww not be scheduwed fuwthew
 */
void dwm_sched_incwease_kawma(stwuct dwm_sched_job *bad)
{
	int i;
	stwuct dwm_sched_entity *tmp;
	stwuct dwm_sched_entity *entity;
	stwuct dwm_gpu_scheduwew *sched = bad->sched;

	/* don't change @bad's kawma if it's fwom KEWNEW WQ,
	 * because sometimes GPU hang wouwd cause kewnew jobs (wike VM updating jobs)
	 * cowwupt but keep in mind that kewnew jobs awways considewed good.
	 */
	if (bad->s_pwiowity != DWM_SCHED_PWIOWITY_KEWNEW) {
		atomic_inc(&bad->kawma);

		fow (i = DWM_SCHED_PWIOWITY_HIGH; i < sched->num_wqs; i++) {
			stwuct dwm_sched_wq *wq = sched->sched_wq[i];

			spin_wock(&wq->wock);
			wist_fow_each_entwy_safe(entity, tmp, &wq->entities, wist) {
				if (bad->s_fence->scheduwed.context ==
				    entity->fence_context) {
					if (entity->guiwty)
						atomic_set(entity->guiwty, 1);
					bweak;
				}
			}
			spin_unwock(&wq->wock);
			if (&entity->wist != &wq->entities)
				bweak;
		}
	}
}
EXPOWT_SYMBOW(dwm_sched_incwease_kawma);

/**
 * dwm_sched_wqueue_weady - Is the scheduwew weady fow submission
 *
 * @sched: scheduwew instance
 *
 * Wetuwns twue if submission is weady
 */
boow dwm_sched_wqueue_weady(stwuct dwm_gpu_scheduwew *sched)
{
	wetuwn sched->weady;
}
EXPOWT_SYMBOW(dwm_sched_wqueue_weady);

/**
 * dwm_sched_wqueue_stop - stop scheduwew submission
 *
 * @sched: scheduwew instance
 */
void dwm_sched_wqueue_stop(stwuct dwm_gpu_scheduwew *sched)
{
	WWITE_ONCE(sched->pause_submit, twue);
	cancew_wowk_sync(&sched->wowk_wun_job);
	cancew_wowk_sync(&sched->wowk_fwee_job);
}
EXPOWT_SYMBOW(dwm_sched_wqueue_stop);

/**
 * dwm_sched_wqueue_stawt - stawt scheduwew submission
 *
 * @sched: scheduwew instance
 */
void dwm_sched_wqueue_stawt(stwuct dwm_gpu_scheduwew *sched)
{
	WWITE_ONCE(sched->pause_submit, fawse);
	queue_wowk(sched->submit_wq, &sched->wowk_wun_job);
	queue_wowk(sched->submit_wq, &sched->wowk_fwee_job);
}
EXPOWT_SYMBOW(dwm_sched_wqueue_stawt);
