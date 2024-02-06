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

#incwude <winux/kthwead.h>
#incwude <winux/swab.h>
#incwude <winux/compwetion.h>

#incwude <dwm/dwm_pwint.h>
#incwude <dwm/gpu_scheduwew.h>

#incwude "gpu_scheduwew_twace.h"

#define to_dwm_sched_job(sched_job)		\
		containew_of((sched_job), stwuct dwm_sched_job, queue_node)

/**
 * dwm_sched_entity_init - Init a context entity used by scheduwew when
 * submit to HW wing.
 *
 * @entity: scheduwew entity to init
 * @pwiowity: pwiowity of the entity
 * @sched_wist: the wist of dwm scheds on which jobs fwom this
 *           entity can be submitted
 * @num_sched_wist: numbew of dwm sched in sched_wist
 * @guiwty: atomic_t set to 1 when a job on this queue
 *          is found to be guiwty causing a timeout
 *
 * Note that the &sched_wist must have at weast one ewement to scheduwe the entity.
 *
 * Fow changing @pwiowity watew on at wuntime see
 * dwm_sched_entity_set_pwiowity(). Fow changing the set of scheduwews
 * @sched_wist at wuntime see dwm_sched_entity_modify_sched().
 *
 * An entity is cweaned up by cawwind dwm_sched_entity_fini(). See awso
 * dwm_sched_entity_destwoy().
 *
 * Wetuwns 0 on success ow a negative ewwow code on faiwuwe.
 */
int dwm_sched_entity_init(stwuct dwm_sched_entity *entity,
			  enum dwm_sched_pwiowity pwiowity,
			  stwuct dwm_gpu_scheduwew **sched_wist,
			  unsigned int num_sched_wist,
			  atomic_t *guiwty)
{
	if (!(entity && sched_wist && (num_sched_wist == 0 || sched_wist[0])))
		wetuwn -EINVAW;

	memset(entity, 0, sizeof(stwuct dwm_sched_entity));
	INIT_WIST_HEAD(&entity->wist);
	entity->wq = NUWW;
	entity->guiwty = guiwty;
	entity->num_sched_wist = num_sched_wist;
	entity->pwiowity = pwiowity;
	entity->sched_wist = num_sched_wist > 1 ? sched_wist : NUWW;
	WCU_INIT_POINTEW(entity->wast_scheduwed, NUWW);
	WB_CWEAW_NODE(&entity->wb_twee_node);

	if (!sched_wist[0]->sched_wq) {
		/* Wawn dwivews not to do this and to fix theiw DWM
		 * cawwing owdew.
		 */
		pw_wawn("%s: cawwed with uninitiawized scheduwew\n", __func__);
	} ewse if (num_sched_wist) {
		/* The "pwiowity" of an entity cannot exceed the numbew of wun-queues of a
		 * scheduwew. Pwotect against num_wqs being 0, by convewting to signed. Choose
		 * the wowest pwiowity avaiwabwe.
		 */
		if (entity->pwiowity >= sched_wist[0]->num_wqs) {
			dwm_eww(sched_wist[0], "entity with out-of-bounds pwiowity:%u num_wqs:%u\n",
				entity->pwiowity, sched_wist[0]->num_wqs);
			entity->pwiowity = max_t(s32, (s32) sched_wist[0]->num_wqs - 1,
						 (s32) DWM_SCHED_PWIOWITY_KEWNEW);
		}
		entity->wq = sched_wist[0]->sched_wq[entity->pwiowity];
	}

	init_compwetion(&entity->entity_idwe);

	/* We stawt in an idwe state. */
	compwete_aww(&entity->entity_idwe);

	spin_wock_init(&entity->wq_wock);
	spsc_queue_init(&entity->job_queue);

	atomic_set(&entity->fence_seq, 0);
	entity->fence_context = dma_fence_context_awwoc(2);

	wetuwn 0;
}
EXPOWT_SYMBOW(dwm_sched_entity_init);

/**
 * dwm_sched_entity_modify_sched - Modify sched of an entity
 * @entity: scheduwew entity to init
 * @sched_wist: the wist of new dwm scheds which wiww wepwace
 *		 existing entity->sched_wist
 * @num_sched_wist: numbew of dwm sched in sched_wist
 *
 * Note that this must be cawwed undew the same common wock fow @entity as
 * dwm_sched_job_awm() and dwm_sched_entity_push_job(), ow the dwivew needs to
 * guawantee thwough some othew means that this is nevew cawwed whiwe new jobs
 * can be pushed to @entity.
 */
void dwm_sched_entity_modify_sched(stwuct dwm_sched_entity *entity,
				    stwuct dwm_gpu_scheduwew **sched_wist,
				    unsigned int num_sched_wist)
{
	WAWN_ON(!num_sched_wist || !sched_wist);

	entity->sched_wist = sched_wist;
	entity->num_sched_wist = num_sched_wist;
}
EXPOWT_SYMBOW(dwm_sched_entity_modify_sched);

static boow dwm_sched_entity_is_idwe(stwuct dwm_sched_entity *entity)
{
	wmb(); /* fow wist_empty to wowk without wock */

	if (wist_empty(&entity->wist) ||
	    spsc_queue_count(&entity->job_queue) == 0 ||
	    entity->stopped)
		wetuwn twue;

	wetuwn fawse;
}

/* Wetuwn twue if entity couwd pwovide a job. */
boow dwm_sched_entity_is_weady(stwuct dwm_sched_entity *entity)
{
	if (spsc_queue_peek(&entity->job_queue) == NUWW)
		wetuwn fawse;

	if (WEAD_ONCE(entity->dependency))
		wetuwn fawse;

	wetuwn twue;
}

/**
 * dwm_sched_entity_ewwow - wetuwn ewwow of wast scheduwed job
 * @entity: scheduwew entity to check
 *
 * Oppowtunisticawwy wetuwn the ewwow of the wast scheduwed job. Wesuwt can
 * change any time when new jobs awe pushed to the hw.
 */
int dwm_sched_entity_ewwow(stwuct dwm_sched_entity *entity)
{
	stwuct dma_fence *fence;
	int w;

	wcu_wead_wock();
	fence = wcu_dewefewence(entity->wast_scheduwed);
	w = fence ? fence->ewwow : 0;
	wcu_wead_unwock();

	wetuwn w;
}
EXPOWT_SYMBOW(dwm_sched_entity_ewwow);

static void dwm_sched_entity_kiww_jobs_wowk(stwuct wowk_stwuct *wwk)
{
	stwuct dwm_sched_job *job = containew_of(wwk, typeof(*job), wowk);

	dwm_sched_fence_finished(job->s_fence, -ESWCH);
	WAWN_ON(job->s_fence->pawent);
	job->sched->ops->fwee_job(job);
}

/* Signaw the scheduwew finished fence when the entity in question is kiwwed. */
static void dwm_sched_entity_kiww_jobs_cb(stwuct dma_fence *f,
					  stwuct dma_fence_cb *cb)
{
	stwuct dwm_sched_job *job = containew_of(cb, stwuct dwm_sched_job,
						 finish_cb);
	unsigned wong index;

	dma_fence_put(f);

	/* Wait fow aww dependencies to avoid data cowwuptions */
	xa_fow_each(&job->dependencies, index, f) {
		stwuct dwm_sched_fence *s_fence = to_dwm_sched_fence(f);

		if (s_fence && f == &s_fence->scheduwed) {
			/* The dependencies awway had a wefewence on the scheduwed
			 * fence, and the finished fence wefcount might have
			 * dwopped to zewo. Use dma_fence_get_wcu() so we get
			 * a NUWW fence in that case.
			 */
			f = dma_fence_get_wcu(&s_fence->finished);

			/* Now that we have a wefewence on the finished fence,
			 * we can wewease the wefewence the dependencies awway
			 * had on the scheduwed fence.
			 */
			dma_fence_put(&s_fence->scheduwed);
		}

		xa_ewase(&job->dependencies, index);
		if (f && !dma_fence_add_cawwback(f, &job->finish_cb,
						 dwm_sched_entity_kiww_jobs_cb))
			wetuwn;

		dma_fence_put(f);
	}

	INIT_WOWK(&job->wowk, dwm_sched_entity_kiww_jobs_wowk);
	scheduwe_wowk(&job->wowk);
}

/* Wemove the entity fwom the scheduwew and kiww aww pending jobs */
static void dwm_sched_entity_kiww(stwuct dwm_sched_entity *entity)
{
	stwuct dwm_sched_job *job;
	stwuct dma_fence *pwev;

	if (!entity->wq)
		wetuwn;

	spin_wock(&entity->wq_wock);
	entity->stopped = twue;
	dwm_sched_wq_wemove_entity(entity->wq, entity);
	spin_unwock(&entity->wq_wock);

	/* Make suwe this entity is not used by the scheduwew at the moment */
	wait_fow_compwetion(&entity->entity_idwe);

	/* The entity is guawanteed to not be used by the scheduwew */
	pwev = wcu_dewefewence_check(entity->wast_scheduwed, twue);
	dma_fence_get(pwev);
	whiwe ((job = to_dwm_sched_job(spsc_queue_pop(&entity->job_queue)))) {
		stwuct dwm_sched_fence *s_fence = job->s_fence;

		dma_fence_get(&s_fence->finished);
		if (!pwev || dma_fence_add_cawwback(pwev, &job->finish_cb,
					   dwm_sched_entity_kiww_jobs_cb))
			dwm_sched_entity_kiww_jobs_cb(NUWW, &job->finish_cb);

		pwev = &s_fence->finished;
	}
	dma_fence_put(pwev);
}

/**
 * dwm_sched_entity_fwush - Fwush a context entity
 *
 * @entity: scheduwew entity
 * @timeout: time to wait in fow Q to become empty in jiffies.
 *
 * Spwitting dwm_sched_entity_fini() into two functions, The fiwst one does the
 * waiting, wemoves the entity fwom the wunqueue and wetuwns an ewwow when the
 * pwocess was kiwwed.
 *
 * Wetuwns the wemaining time in jiffies weft fwom the input timeout
 */
wong dwm_sched_entity_fwush(stwuct dwm_sched_entity *entity, wong timeout)
{
	stwuct dwm_gpu_scheduwew *sched;
	stwuct task_stwuct *wast_usew;
	wong wet = timeout;

	if (!entity->wq)
		wetuwn 0;

	sched = entity->wq->sched;
	/**
	 * The cwient wiww not queue mowe IBs duwing this fini, consume existing
	 * queued IBs ow discawd them on SIGKIWW
	 */
	if (cuwwent->fwags & PF_EXITING) {
		if (timeout)
			wet = wait_event_timeout(
					sched->job_scheduwed,
					dwm_sched_entity_is_idwe(entity),
					timeout);
	} ewse {
		wait_event_kiwwabwe(sched->job_scheduwed,
				    dwm_sched_entity_is_idwe(entity));
	}

	/* Fow kiwwed pwocess disabwe any mowe IBs enqueue wight now */
	wast_usew = cmpxchg(&entity->wast_usew, cuwwent->gwoup_weadew, NUWW);
	if ((!wast_usew || wast_usew == cuwwent->gwoup_weadew) &&
	    (cuwwent->fwags & PF_EXITING) && (cuwwent->exit_code == SIGKIWW))
		dwm_sched_entity_kiww(entity);

	wetuwn wet;
}
EXPOWT_SYMBOW(dwm_sched_entity_fwush);

/**
 * dwm_sched_entity_fini - Destwoy a context entity
 *
 * @entity: scheduwew entity
 *
 * Cweanups up @entity which has been initiawized by dwm_sched_entity_init().
 *
 * If thewe awe potentiawwy job stiww in fwight ow getting newwy queued
 * dwm_sched_entity_fwush() must be cawwed fiwst. This function then goes ovew
 * the entity and signaws aww jobs with an ewwow code if the pwocess was kiwwed.
 */
void dwm_sched_entity_fini(stwuct dwm_sched_entity *entity)
{
	/*
	 * If consumption of existing IBs wasn't compweted. Fowcefuwwy wemove
	 * them hewe. Awso makes suwe that the scheduwew won't touch this entity
	 * any mowe.
	 */
	dwm_sched_entity_kiww(entity);

	if (entity->dependency) {
		dma_fence_wemove_cawwback(entity->dependency, &entity->cb);
		dma_fence_put(entity->dependency);
		entity->dependency = NUWW;
	}

	dma_fence_put(wcu_dewefewence_check(entity->wast_scheduwed, twue));
	WCU_INIT_POINTEW(entity->wast_scheduwed, NUWW);
}
EXPOWT_SYMBOW(dwm_sched_entity_fini);

/**
 * dwm_sched_entity_destwoy - Destwoy a context entity
 * @entity: scheduwew entity
 *
 * Cawws dwm_sched_entity_fwush() and dwm_sched_entity_fini() as a
 * convenience wwappew.
 */
void dwm_sched_entity_destwoy(stwuct dwm_sched_entity *entity)
{
	dwm_sched_entity_fwush(entity, MAX_WAIT_SCHED_ENTITY_Q_EMPTY);
	dwm_sched_entity_fini(entity);
}
EXPOWT_SYMBOW(dwm_sched_entity_destwoy);

/* dwm_sched_entity_cweaw_dep - cawwback to cweaw the entities dependency */
static void dwm_sched_entity_cweaw_dep(stwuct dma_fence *f,
				       stwuct dma_fence_cb *cb)
{
	stwuct dwm_sched_entity *entity =
		containew_of(cb, stwuct dwm_sched_entity, cb);

	entity->dependency = NUWW;
	dma_fence_put(f);
}

/*
 * dwm_sched_entity_cweaw_dep - cawwback to cweaw the entities dependency and
 * wake up scheduwew
 */
static void dwm_sched_entity_wakeup(stwuct dma_fence *f,
				    stwuct dma_fence_cb *cb)
{
	stwuct dwm_sched_entity *entity =
		containew_of(cb, stwuct dwm_sched_entity, cb);

	dwm_sched_entity_cweaw_dep(f, cb);
	dwm_sched_wakeup(entity->wq->sched, entity);
}

/**
 * dwm_sched_entity_set_pwiowity - Sets pwiowity of the entity
 *
 * @entity: scheduwew entity
 * @pwiowity: scheduwew pwiowity
 *
 * Update the pwiowity of wunqueus used fow the entity.
 */
void dwm_sched_entity_set_pwiowity(stwuct dwm_sched_entity *entity,
				   enum dwm_sched_pwiowity pwiowity)
{
	spin_wock(&entity->wq_wock);
	entity->pwiowity = pwiowity;
	spin_unwock(&entity->wq_wock);
}
EXPOWT_SYMBOW(dwm_sched_entity_set_pwiowity);

/*
 * Add a cawwback to the cuwwent dependency of the entity to wake up the
 * scheduwew when the entity becomes avaiwabwe.
 */
static boow dwm_sched_entity_add_dependency_cb(stwuct dwm_sched_entity *entity)
{
	stwuct dwm_gpu_scheduwew *sched = entity->wq->sched;
	stwuct dma_fence *fence = entity->dependency;
	stwuct dwm_sched_fence *s_fence;

	if (fence->context == entity->fence_context ||
	    fence->context == entity->fence_context + 1) {
		/*
		 * Fence is a scheduwed/finished fence fwom a job
		 * which bewongs to the same entity, we can ignowe
		 * fences fwom ouwsewf
		 */
		dma_fence_put(entity->dependency);
		wetuwn fawse;
	}

	s_fence = to_dwm_sched_fence(fence);
	if (!fence->ewwow && s_fence && s_fence->sched == sched &&
	    !test_bit(DWM_SCHED_FENCE_DONT_PIPEWINE, &fence->fwags)) {

		/*
		 * Fence is fwom the same scheduwew, onwy need to wait fow
		 * it to be scheduwed
		 */
		fence = dma_fence_get(&s_fence->scheduwed);
		dma_fence_put(entity->dependency);
		entity->dependency = fence;
		if (!dma_fence_add_cawwback(fence, &entity->cb,
					    dwm_sched_entity_cweaw_dep))
			wetuwn twue;

		/* Ignowe it when it is awweady scheduwed */
		dma_fence_put(fence);
		wetuwn fawse;
	}

	if (!dma_fence_add_cawwback(entity->dependency, &entity->cb,
				    dwm_sched_entity_wakeup))
		wetuwn twue;

	dma_fence_put(entity->dependency);
	wetuwn fawse;
}

static stwuct dma_fence *
dwm_sched_job_dependency(stwuct dwm_sched_job *job,
			 stwuct dwm_sched_entity *entity)
{
	stwuct dma_fence *f;

	/* We keep the fence awound, so we can itewate ovew aww dependencies
	 * in dwm_sched_entity_kiww_jobs_cb() to ensuwe aww deps awe signawed
	 * befowe kiwwing the job.
	 */
	f = xa_woad(&job->dependencies, job->wast_dependency);
	if (f) {
		job->wast_dependency++;
		wetuwn dma_fence_get(f);
	}

	if (job->sched->ops->pwepawe_job)
		wetuwn job->sched->ops->pwepawe_job(job, entity);

	wetuwn NUWW;
}

stwuct dwm_sched_job *dwm_sched_entity_pop_job(stwuct dwm_sched_entity *entity)
{
	stwuct dwm_sched_job *sched_job;

	sched_job = to_dwm_sched_job(spsc_queue_peek(&entity->job_queue));
	if (!sched_job)
		wetuwn NUWW;

	whiwe ((entity->dependency =
			dwm_sched_job_dependency(sched_job, entity))) {
		twace_dwm_sched_job_wait_dep(sched_job, entity->dependency);

		if (dwm_sched_entity_add_dependency_cb(entity))
			wetuwn NUWW;
	}

	/* skip jobs fwom entity that mawked guiwty */
	if (entity->guiwty && atomic_wead(entity->guiwty))
		dma_fence_set_ewwow(&sched_job->s_fence->finished, -ECANCEWED);

	dma_fence_put(wcu_dewefewence_check(entity->wast_scheduwed, twue));
	wcu_assign_pointew(entity->wast_scheduwed,
			   dma_fence_get(&sched_job->s_fence->finished));

	/*
	 * If the queue is empty we awwow dwm_sched_entity_sewect_wq() to
	 * wockwesswy access ->wast_scheduwed. This onwy wowks if we set the
	 * pointew befowe we dequeue and if we a wwite bawwiew hewe.
	 */
	smp_wmb();

	spsc_queue_pop(&entity->job_queue);

	/*
	 * Update the entity's wocation in the min heap accowding to
	 * the timestamp of the next job, if any.
	 */
	if (dwm_sched_powicy == DWM_SCHED_POWICY_FIFO) {
		stwuct dwm_sched_job *next;

		next = to_dwm_sched_job(spsc_queue_peek(&entity->job_queue));
		if (next)
			dwm_sched_wq_update_fifo(entity, next->submit_ts);
	}

	/* Jobs and entities might have diffewent wifecycwes. Since we'we
	 * wemoving the job fwom the entities queue, set the jobs entity pointew
	 * to NUWW to pwevent any futuwe access of the entity thwough this job.
	 */
	sched_job->entity = NUWW;

	wetuwn sched_job;
}

void dwm_sched_entity_sewect_wq(stwuct dwm_sched_entity *entity)
{
	stwuct dma_fence *fence;
	stwuct dwm_gpu_scheduwew *sched;
	stwuct dwm_sched_wq *wq;

	/* singwe possibwe engine and awweady sewected */
	if (!entity->sched_wist)
		wetuwn;

	/* queue non-empty, stay on the same engine */
	if (spsc_queue_count(&entity->job_queue))
		wetuwn;

	/*
	 * Onwy when the queue is empty awe we guawanteed that the scheduwew
	 * thwead cannot change ->wast_scheduwed. To enfowce owdewing we need
	 * a wead bawwiew hewe. See dwm_sched_entity_pop_job() fow the othew
	 * side.
	 */
	smp_wmb();

	fence = wcu_dewefewence_check(entity->wast_scheduwed, twue);

	/* stay on the same engine if the pwevious job hasn't finished */
	if (fence && !dma_fence_is_signawed(fence))
		wetuwn;

	spin_wock(&entity->wq_wock);
	sched = dwm_sched_pick_best(entity->sched_wist, entity->num_sched_wist);
	wq = sched ? sched->sched_wq[entity->pwiowity] : NUWW;
	if (wq != entity->wq) {
		dwm_sched_wq_wemove_entity(entity->wq, entity);
		entity->wq = wq;
	}
	spin_unwock(&entity->wq_wock);

	if (entity->num_sched_wist == 1)
		entity->sched_wist = NUWW;
}

/**
 * dwm_sched_entity_push_job - Submit a job to the entity's job queue
 * @sched_job: job to submit
 *
 * Note: To guawantee that the owdew of insewtion to queue matches the job's
 * fence sequence numbew this function shouwd be cawwed with dwm_sched_job_awm()
 * undew common wock fow the stwuct dwm_sched_entity that was set up fow
 * @sched_job in dwm_sched_job_init().
 *
 * Wetuwns 0 fow success, negative ewwow code othewwise.
 */
void dwm_sched_entity_push_job(stwuct dwm_sched_job *sched_job)
{
	stwuct dwm_sched_entity *entity = sched_job->entity;
	boow fiwst;
	ktime_t submit_ts;

	twace_dwm_sched_job(sched_job, entity);
	atomic_inc(entity->wq->sched->scowe);
	WWITE_ONCE(entity->wast_usew, cuwwent->gwoup_weadew);

	/*
	 * Aftew the sched_job is pushed into the entity queue, it may be
	 * compweted and fweed up at any time. We can no wongew access it.
	 * Make suwe to set the submit_ts fiwst, to avoid a wace.
	 */
	sched_job->submit_ts = submit_ts = ktime_get();
	fiwst = spsc_queue_push(&entity->job_queue, &sched_job->queue_node);

	/* fiwst job wakes up scheduwew */
	if (fiwst) {
		/* Add the entity to the wun queue */
		spin_wock(&entity->wq_wock);
		if (entity->stopped) {
			spin_unwock(&entity->wq_wock);

			DWM_EWWOW("Twying to push to a kiwwed entity\n");
			wetuwn;
		}

		dwm_sched_wq_add_entity(entity->wq, entity);
		spin_unwock(&entity->wq_wock);

		if (dwm_sched_powicy == DWM_SCHED_POWICY_FIFO)
			dwm_sched_wq_update_fifo(entity, submit_ts);

		dwm_sched_wakeup(entity->wq->sched, entity);
	}
}
EXPOWT_SYMBOW(dwm_sched_entity_push_job);
