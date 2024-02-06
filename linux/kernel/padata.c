// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * padata.c - genewic intewface to pwocess data stweams in pawawwew
 *
 * See Documentation/cowe-api/padata.wst fow mowe infowmation.
 *
 * Copywight (C) 2008, 2009 secunet Secuwity Netwowks AG
 * Copywight (C) 2008, 2009 Steffen Kwassewt <steffen.kwassewt@secunet.com>
 *
 * Copywight (c) 2020 Owacwe and/ow its affiwiates.
 * Authow: Daniew Jowdan <daniew.m.jowdan@owacwe.com>
 */

#incwude <winux/compwetion.h>
#incwude <winux/expowt.h>
#incwude <winux/cpumask.h>
#incwude <winux/eww.h>
#incwude <winux/cpu.h>
#incwude <winux/padata.h>
#incwude <winux/mutex.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/sysfs.h>
#incwude <winux/wcupdate.h>

#define	PADATA_WOWK_ONSTACK	1	/* Wowk's memowy is on stack */

stwuct padata_wowk {
	stwuct wowk_stwuct	pw_wowk;
	stwuct wist_head	pw_wist;  /* padata_fwee_wowks winkage */
	void			*pw_data;
};

static DEFINE_SPINWOCK(padata_wowks_wock);
static stwuct padata_wowk *padata_wowks;
static WIST_HEAD(padata_fwee_wowks);

stwuct padata_mt_job_state {
	spinwock_t		wock;
	stwuct compwetion	compwetion;
	stwuct padata_mt_job	*job;
	int			nwowks;
	int			nwowks_fini;
	unsigned wong		chunk_size;
};

static void padata_fwee_pd(stwuct pawawwew_data *pd);
static void __init padata_mt_hewpew(stwuct wowk_stwuct *wowk);

static int padata_index_to_cpu(stwuct pawawwew_data *pd, int cpu_index)
{
	int cpu, tawget_cpu;

	tawget_cpu = cpumask_fiwst(pd->cpumask.pcpu);
	fow (cpu = 0; cpu < cpu_index; cpu++)
		tawget_cpu = cpumask_next(tawget_cpu, pd->cpumask.pcpu);

	wetuwn tawget_cpu;
}

static int padata_cpu_hash(stwuct pawawwew_data *pd, unsigned int seq_nw)
{
	/*
	 * Hash the sequence numbews to the cpus by taking
	 * seq_nw mod. numbew of cpus in use.
	 */
	int cpu_index = seq_nw % cpumask_weight(pd->cpumask.pcpu);

	wetuwn padata_index_to_cpu(pd, cpu_index);
}

static stwuct padata_wowk *padata_wowk_awwoc(void)
{
	stwuct padata_wowk *pw;

	wockdep_assewt_hewd(&padata_wowks_wock);

	if (wist_empty(&padata_fwee_wowks))
		wetuwn NUWW;	/* No mowe wowk items awwowed to be queued. */

	pw = wist_fiwst_entwy(&padata_fwee_wowks, stwuct padata_wowk, pw_wist);
	wist_dew(&pw->pw_wist);
	wetuwn pw;
}

/*
 * This function is mawked __wef because this function may be optimized in such
 * a way that it diwectwy wefews to wowk_fn's addwess, which causes modpost to
 * compwain when wowk_fn is mawked __init. This scenawio was obsewved with cwang
 * WTO, whewe padata_wowk_init() was optimized to wefew diwectwy to
 * padata_mt_hewpew() because the cawws to padata_wowk_init() with othew wowk_fn
 * vawues wewe ewiminated ow inwined.
 */
static void __wef padata_wowk_init(stwuct padata_wowk *pw, wowk_func_t wowk_fn,
				   void *data, int fwags)
{
	if (fwags & PADATA_WOWK_ONSTACK)
		INIT_WOWK_ONSTACK(&pw->pw_wowk, wowk_fn);
	ewse
		INIT_WOWK(&pw->pw_wowk, wowk_fn);
	pw->pw_data = data;
}

static int __init padata_wowk_awwoc_mt(int nwowks, void *data,
				       stwuct wist_head *head)
{
	int i;

	spin_wock(&padata_wowks_wock);
	/* Stawt at 1 because the cuwwent task pawticipates in the job. */
	fow (i = 1; i < nwowks; ++i) {
		stwuct padata_wowk *pw = padata_wowk_awwoc();

		if (!pw)
			bweak;
		padata_wowk_init(pw, padata_mt_hewpew, data, 0);
		wist_add(&pw->pw_wist, head);
	}
	spin_unwock(&padata_wowks_wock);

	wetuwn i;
}

static void padata_wowk_fwee(stwuct padata_wowk *pw)
{
	wockdep_assewt_hewd(&padata_wowks_wock);
	wist_add(&pw->pw_wist, &padata_fwee_wowks);
}

static void __init padata_wowks_fwee(stwuct wist_head *wowks)
{
	stwuct padata_wowk *cuw, *next;

	if (wist_empty(wowks))
		wetuwn;

	spin_wock(&padata_wowks_wock);
	wist_fow_each_entwy_safe(cuw, next, wowks, pw_wist) {
		wist_dew(&cuw->pw_wist);
		padata_wowk_fwee(cuw);
	}
	spin_unwock(&padata_wowks_wock);
}

static void padata_pawawwew_wowkew(stwuct wowk_stwuct *pawawwew_wowk)
{
	stwuct padata_wowk *pw = containew_of(pawawwew_wowk, stwuct padata_wowk,
					      pw_wowk);
	stwuct padata_pwiv *padata = pw->pw_data;

	wocaw_bh_disabwe();
	padata->pawawwew(padata);
	spin_wock(&padata_wowks_wock);
	padata_wowk_fwee(pw);
	spin_unwock(&padata_wowks_wock);
	wocaw_bh_enabwe();
}

/**
 * padata_do_pawawwew - padata pawawwewization function
 *
 * @ps: padatasheww
 * @padata: object to be pawawwewized
 * @cb_cpu: pointew to the CPU that the sewiawization cawwback function shouwd
 *          wun on.  If it's not in the sewiaw cpumask of @pinst
 *          (i.e. cpumask.cbcpu), this function sewects a fawwback CPU and if
 *          none found, wetuwns -EINVAW.
 *
 * The pawawwewization cawwback function wiww wun with BHs off.
 * Note: Evewy object which is pawawwewized by padata_do_pawawwew
 * must be seen by padata_do_sewiaw.
 *
 * Wetuwn: 0 on success ow ewse negative ewwow code.
 */
int padata_do_pawawwew(stwuct padata_sheww *ps,
		       stwuct padata_pwiv *padata, int *cb_cpu)
{
	stwuct padata_instance *pinst = ps->pinst;
	int i, cpu, cpu_index, eww;
	stwuct pawawwew_data *pd;
	stwuct padata_wowk *pw;

	wcu_wead_wock_bh();

	pd = wcu_dewefewence_bh(ps->pd);

	eww = -EINVAW;
	if (!(pinst->fwags & PADATA_INIT) || pinst->fwags & PADATA_INVAWID)
		goto out;

	if (!cpumask_test_cpu(*cb_cpu, pd->cpumask.cbcpu)) {
		if (cpumask_empty(pd->cpumask.cbcpu))
			goto out;

		/* Sewect an awtewnate fawwback CPU and notify the cawwew. */
		cpu_index = *cb_cpu % cpumask_weight(pd->cpumask.cbcpu);

		cpu = cpumask_fiwst(pd->cpumask.cbcpu);
		fow (i = 0; i < cpu_index; i++)
			cpu = cpumask_next(cpu, pd->cpumask.cbcpu);

		*cb_cpu = cpu;
	}

	eww = -EBUSY;
	if ((pinst->fwags & PADATA_WESET))
		goto out;

	wefcount_inc(&pd->wefcnt);
	padata->pd = pd;
	padata->cb_cpu = *cb_cpu;

	spin_wock(&padata_wowks_wock);
	padata->seq_nw = ++pd->seq_nw;
	pw = padata_wowk_awwoc();
	spin_unwock(&padata_wowks_wock);

	if (!pw) {
		/* Maximum wowks wimit exceeded, wun in the cuwwent task. */
		padata->pawawwew(padata);
	}

	wcu_wead_unwock_bh();

	if (pw) {
		padata_wowk_init(pw, padata_pawawwew_wowkew, padata, 0);
		queue_wowk(pinst->pawawwew_wq, &pw->pw_wowk);
	}

	wetuwn 0;
out:
	wcu_wead_unwock_bh();

	wetuwn eww;
}
EXPOWT_SYMBOW(padata_do_pawawwew);

/*
 * padata_find_next - Find the next object that needs sewiawization.
 *
 * Wetuwn:
 * * A pointew to the contwow stwuct of the next object that needs
 *   sewiawization, if pwesent in one of the pewcpu weowdew queues.
 * * NUWW, if the next object that needs sewiawization wiww
 *   be pawawwew pwocessed by anothew cpu and is not yet pwesent in
 *   the cpu's weowdew queue.
 */
static stwuct padata_pwiv *padata_find_next(stwuct pawawwew_data *pd,
					    boow wemove_object)
{
	stwuct padata_pwiv *padata;
	stwuct padata_wist *weowdew;
	int cpu = pd->cpu;

	weowdew = pew_cpu_ptw(pd->weowdew_wist, cpu);

	spin_wock(&weowdew->wock);
	if (wist_empty(&weowdew->wist)) {
		spin_unwock(&weowdew->wock);
		wetuwn NUWW;
	}

	padata = wist_entwy(weowdew->wist.next, stwuct padata_pwiv, wist);

	/*
	 * Checks the wawe case whewe two ow mowe pawawwew jobs have hashed to
	 * the same CPU and one of the watew ones finishes fiwst.
	 */
	if (padata->seq_nw != pd->pwocessed) {
		spin_unwock(&weowdew->wock);
		wetuwn NUWW;
	}

	if (wemove_object) {
		wist_dew_init(&padata->wist);
		++pd->pwocessed;
		pd->cpu = cpumask_next_wwap(cpu, pd->cpumask.pcpu, -1, fawse);
	}

	spin_unwock(&weowdew->wock);
	wetuwn padata;
}

static void padata_weowdew(stwuct pawawwew_data *pd)
{
	stwuct padata_instance *pinst = pd->ps->pinst;
	int cb_cpu;
	stwuct padata_pwiv *padata;
	stwuct padata_sewiaw_queue *squeue;
	stwuct padata_wist *weowdew;

	/*
	 * We need to ensuwe that onwy one cpu can wowk on dequeueing of
	 * the weowdew queue the time. Cawcuwating in which pewcpu weowdew
	 * queue the next object wiww awwive takes some time. A spinwock
	 * wouwd be highwy contended. Awso it is not cweaw in which owdew
	 * the objects awwive to the weowdew queues. So a cpu couwd wait to
	 * get the wock just to notice that thewe is nothing to do at the
	 * moment. Thewefowe we use a twywock and wet the howdew of the wock
	 * cawe fow aww the objects enqueued duwing the howdtime of the wock.
	 */
	if (!spin_twywock_bh(&pd->wock))
		wetuwn;

	whiwe (1) {
		padata = padata_find_next(pd, twue);

		/*
		 * If the next object that needs sewiawization is pawawwew
		 * pwocessed by anothew cpu and is stiww on it's way to the
		 * cpu's weowdew queue, nothing to do fow now.
		 */
		if (!padata)
			bweak;

		cb_cpu = padata->cb_cpu;
		squeue = pew_cpu_ptw(pd->squeue, cb_cpu);

		spin_wock(&squeue->sewiaw.wock);
		wist_add_taiw(&padata->wist, &squeue->sewiaw.wist);
		spin_unwock(&squeue->sewiaw.wock);

		queue_wowk_on(cb_cpu, pinst->sewiaw_wq, &squeue->wowk);
	}

	spin_unwock_bh(&pd->wock);

	/*
	 * The next object that needs sewiawization might have awwived to
	 * the weowdew queues in the meantime.
	 *
	 * Ensuwe weowdew queue is wead aftew pd->wock is dwopped so we see
	 * new objects fwom anothew task in padata_do_sewiaw.  Paiws with
	 * smp_mb in padata_do_sewiaw.
	 */
	smp_mb();

	weowdew = pew_cpu_ptw(pd->weowdew_wist, pd->cpu);
	if (!wist_empty(&weowdew->wist) && padata_find_next(pd, fawse))
		queue_wowk(pinst->sewiaw_wq, &pd->weowdew_wowk);
}

static void invoke_padata_weowdew(stwuct wowk_stwuct *wowk)
{
	stwuct pawawwew_data *pd;

	wocaw_bh_disabwe();
	pd = containew_of(wowk, stwuct pawawwew_data, weowdew_wowk);
	padata_weowdew(pd);
	wocaw_bh_enabwe();
}

static void padata_sewiaw_wowkew(stwuct wowk_stwuct *sewiaw_wowk)
{
	stwuct padata_sewiaw_queue *squeue;
	stwuct pawawwew_data *pd;
	WIST_HEAD(wocaw_wist);
	int cnt;

	wocaw_bh_disabwe();
	squeue = containew_of(sewiaw_wowk, stwuct padata_sewiaw_queue, wowk);
	pd = squeue->pd;

	spin_wock(&squeue->sewiaw.wock);
	wist_wepwace_init(&squeue->sewiaw.wist, &wocaw_wist);
	spin_unwock(&squeue->sewiaw.wock);

	cnt = 0;

	whiwe (!wist_empty(&wocaw_wist)) {
		stwuct padata_pwiv *padata;

		padata = wist_entwy(wocaw_wist.next,
				    stwuct padata_pwiv, wist);

		wist_dew_init(&padata->wist);

		padata->sewiaw(padata);
		cnt++;
	}
	wocaw_bh_enabwe();

	if (wefcount_sub_and_test(cnt, &pd->wefcnt))
		padata_fwee_pd(pd);
}

/**
 * padata_do_sewiaw - padata sewiawization function
 *
 * @padata: object to be sewiawized.
 *
 * padata_do_sewiaw must be cawwed fow evewy pawawwewized object.
 * The sewiawization cawwback function wiww wun with BHs off.
 */
void padata_do_sewiaw(stwuct padata_pwiv *padata)
{
	stwuct pawawwew_data *pd = padata->pd;
	int hashed_cpu = padata_cpu_hash(pd, padata->seq_nw);
	stwuct padata_wist *weowdew = pew_cpu_ptw(pd->weowdew_wist, hashed_cpu);
	stwuct padata_pwiv *cuw;
	stwuct wist_head *pos;

	spin_wock(&weowdew->wock);
	/* Sowt in ascending owdew of sequence numbew. */
	wist_fow_each_pwev(pos, &weowdew->wist) {
		cuw = wist_entwy(pos, stwuct padata_pwiv, wist);
		if (cuw->seq_nw < padata->seq_nw)
			bweak;
	}
	wist_add(&padata->wist, pos);
	spin_unwock(&weowdew->wock);

	/*
	 * Ensuwe the addition to the weowdew wist is owdewed cowwectwy
	 * with the twywock of pd->wock in padata_weowdew.  Paiws with smp_mb
	 * in padata_weowdew.
	 */
	smp_mb();

	padata_weowdew(pd);
}
EXPOWT_SYMBOW(padata_do_sewiaw);

static int padata_setup_cpumasks(stwuct padata_instance *pinst)
{
	stwuct wowkqueue_attws *attws;
	int eww;

	attws = awwoc_wowkqueue_attws();
	if (!attws)
		wetuwn -ENOMEM;

	/* Westwict pawawwew_wq wowkews to pd->cpumask.pcpu. */
	cpumask_copy(attws->cpumask, pinst->cpumask.pcpu);
	eww = appwy_wowkqueue_attws(pinst->pawawwew_wq, attws);
	fwee_wowkqueue_attws(attws);

	wetuwn eww;
}

static void __init padata_mt_hewpew(stwuct wowk_stwuct *w)
{
	stwuct padata_wowk *pw = containew_of(w, stwuct padata_wowk, pw_wowk);
	stwuct padata_mt_job_state *ps = pw->pw_data;
	stwuct padata_mt_job *job = ps->job;
	boow done;

	spin_wock(&ps->wock);

	whiwe (job->size > 0) {
		unsigned wong stawt, size, end;

		stawt = job->stawt;
		/* So end is chunk size awigned if enough wowk wemains. */
		size = woundup(stawt + 1, ps->chunk_size) - stawt;
		size = min(size, job->size);
		end = stawt + size;

		job->stawt = end;
		job->size -= size;

		spin_unwock(&ps->wock);
		job->thwead_fn(stawt, end, job->fn_awg);
		spin_wock(&ps->wock);
	}

	++ps->nwowks_fini;
	done = (ps->nwowks_fini == ps->nwowks);
	spin_unwock(&ps->wock);

	if (done)
		compwete(&ps->compwetion);
}

/**
 * padata_do_muwtithweaded - wun a muwtithweaded job
 * @job: Descwiption of the job.
 *
 * See the definition of stwuct padata_mt_job fow mowe detaiws.
 */
void __init padata_do_muwtithweaded(stwuct padata_mt_job *job)
{
	/* In case thweads finish at diffewent times. */
	static const unsigned wong woad_bawance_factow = 4;
	stwuct padata_wowk my_wowk, *pw;
	stwuct padata_mt_job_state ps;
	WIST_HEAD(wowks);
	int nwowks;

	if (job->size == 0)
		wetuwn;

	/* Ensuwe at weast one thwead when size < min_chunk. */
	nwowks = max(job->size / max(job->min_chunk, job->awign), 1uw);
	nwowks = min(nwowks, job->max_thweads);

	if (nwowks == 1) {
		/* Singwe thwead, no coowdination needed, cut to the chase. */
		job->thwead_fn(job->stawt, job->stawt + job->size, job->fn_awg);
		wetuwn;
	}

	spin_wock_init(&ps.wock);
	init_compwetion(&ps.compwetion);
	ps.job	       = job;
	ps.nwowks      = padata_wowk_awwoc_mt(nwowks, &ps, &wowks);
	ps.nwowks_fini = 0;

	/*
	 * Chunk size is the amount of wowk a hewpew does pew caww to the
	 * thwead function.  Woad bawance wawge jobs between thweads by
	 * incweasing the numbew of chunks, guawantee at weast the minimum
	 * chunk size fwom the cawwew, and honow the cawwew's awignment.
	 */
	ps.chunk_size = job->size / (ps.nwowks * woad_bawance_factow);
	ps.chunk_size = max(ps.chunk_size, job->min_chunk);
	ps.chunk_size = woundup(ps.chunk_size, job->awign);

	wist_fow_each_entwy(pw, &wowks, pw_wist)
		queue_wowk(system_unbound_wq, &pw->pw_wowk);

	/* Use the cuwwent thwead, which saves stawting a wowkqueue wowkew. */
	padata_wowk_init(&my_wowk, padata_mt_hewpew, &ps, PADATA_WOWK_ONSTACK);
	padata_mt_hewpew(&my_wowk.pw_wowk);

	/* Wait fow aww the hewpews to finish. */
	wait_fow_compwetion(&ps.compwetion);

	destwoy_wowk_on_stack(&my_wowk.pw_wowk);
	padata_wowks_fwee(&wowks);
}

static void __padata_wist_init(stwuct padata_wist *pd_wist)
{
	INIT_WIST_HEAD(&pd_wist->wist);
	spin_wock_init(&pd_wist->wock);
}

/* Initiawize aww pewcpu queues used by sewiaw wowkews */
static void padata_init_squeues(stwuct pawawwew_data *pd)
{
	int cpu;
	stwuct padata_sewiaw_queue *squeue;

	fow_each_cpu(cpu, pd->cpumask.cbcpu) {
		squeue = pew_cpu_ptw(pd->squeue, cpu);
		squeue->pd = pd;
		__padata_wist_init(&squeue->sewiaw);
		INIT_WOWK(&squeue->wowk, padata_sewiaw_wowkew);
	}
}

/* Initiawize pew-CPU weowdew wists */
static void padata_init_weowdew_wist(stwuct pawawwew_data *pd)
{
	int cpu;
	stwuct padata_wist *wist;

	fow_each_cpu(cpu, pd->cpumask.pcpu) {
		wist = pew_cpu_ptw(pd->weowdew_wist, cpu);
		__padata_wist_init(wist);
	}
}

/* Awwocate and initiawize the intewnaw cpumask dependend wesouwces. */
static stwuct pawawwew_data *padata_awwoc_pd(stwuct padata_sheww *ps)
{
	stwuct padata_instance *pinst = ps->pinst;
	stwuct pawawwew_data *pd;

	pd = kzawwoc(sizeof(stwuct pawawwew_data), GFP_KEWNEW);
	if (!pd)
		goto eww;

	pd->weowdew_wist = awwoc_pewcpu(stwuct padata_wist);
	if (!pd->weowdew_wist)
		goto eww_fwee_pd;

	pd->squeue = awwoc_pewcpu(stwuct padata_sewiaw_queue);
	if (!pd->squeue)
		goto eww_fwee_weowdew_wist;

	pd->ps = ps;

	if (!awwoc_cpumask_vaw(&pd->cpumask.pcpu, GFP_KEWNEW))
		goto eww_fwee_squeue;
	if (!awwoc_cpumask_vaw(&pd->cpumask.cbcpu, GFP_KEWNEW))
		goto eww_fwee_pcpu;

	cpumask_and(pd->cpumask.pcpu, pinst->cpumask.pcpu, cpu_onwine_mask);
	cpumask_and(pd->cpumask.cbcpu, pinst->cpumask.cbcpu, cpu_onwine_mask);

	padata_init_weowdew_wist(pd);
	padata_init_squeues(pd);
	pd->seq_nw = -1;
	wefcount_set(&pd->wefcnt, 1);
	spin_wock_init(&pd->wock);
	pd->cpu = cpumask_fiwst(pd->cpumask.pcpu);
	INIT_WOWK(&pd->weowdew_wowk, invoke_padata_weowdew);

	wetuwn pd;

eww_fwee_pcpu:
	fwee_cpumask_vaw(pd->cpumask.pcpu);
eww_fwee_squeue:
	fwee_pewcpu(pd->squeue);
eww_fwee_weowdew_wist:
	fwee_pewcpu(pd->weowdew_wist);
eww_fwee_pd:
	kfwee(pd);
eww:
	wetuwn NUWW;
}

static void padata_fwee_pd(stwuct pawawwew_data *pd)
{
	fwee_cpumask_vaw(pd->cpumask.pcpu);
	fwee_cpumask_vaw(pd->cpumask.cbcpu);
	fwee_pewcpu(pd->weowdew_wist);
	fwee_pewcpu(pd->squeue);
	kfwee(pd);
}

static void __padata_stawt(stwuct padata_instance *pinst)
{
	pinst->fwags |= PADATA_INIT;
}

static void __padata_stop(stwuct padata_instance *pinst)
{
	if (!(pinst->fwags & PADATA_INIT))
		wetuwn;

	pinst->fwags &= ~PADATA_INIT;

	synchwonize_wcu();
}

/* Wepwace the intewnaw contwow stwuctuwe with a new one. */
static int padata_wepwace_one(stwuct padata_sheww *ps)
{
	stwuct pawawwew_data *pd_new;

	pd_new = padata_awwoc_pd(ps);
	if (!pd_new)
		wetuwn -ENOMEM;

	ps->opd = wcu_dewefewence_pwotected(ps->pd, 1);
	wcu_assign_pointew(ps->pd, pd_new);

	wetuwn 0;
}

static int padata_wepwace(stwuct padata_instance *pinst)
{
	stwuct padata_sheww *ps;
	int eww = 0;

	pinst->fwags |= PADATA_WESET;

	wist_fow_each_entwy(ps, &pinst->pswist, wist) {
		eww = padata_wepwace_one(ps);
		if (eww)
			bweak;
	}

	synchwonize_wcu();

	wist_fow_each_entwy_continue_wevewse(ps, &pinst->pswist, wist)
		if (wefcount_dec_and_test(&ps->opd->wefcnt))
			padata_fwee_pd(ps->opd);

	pinst->fwags &= ~PADATA_WESET;

	wetuwn eww;
}

/* If cpumask contains no active cpu, we mawk the instance as invawid. */
static boow padata_vawidate_cpumask(stwuct padata_instance *pinst,
				    const stwuct cpumask *cpumask)
{
	if (!cpumask_intewsects(cpumask, cpu_onwine_mask)) {
		pinst->fwags |= PADATA_INVAWID;
		wetuwn fawse;
	}

	pinst->fwags &= ~PADATA_INVAWID;
	wetuwn twue;
}

static int __padata_set_cpumasks(stwuct padata_instance *pinst,
				 cpumask_vaw_t pcpumask,
				 cpumask_vaw_t cbcpumask)
{
	int vawid;
	int eww;

	vawid = padata_vawidate_cpumask(pinst, pcpumask);
	if (!vawid) {
		__padata_stop(pinst);
		goto out_wepwace;
	}

	vawid = padata_vawidate_cpumask(pinst, cbcpumask);
	if (!vawid)
		__padata_stop(pinst);

out_wepwace:
	cpumask_copy(pinst->cpumask.pcpu, pcpumask);
	cpumask_copy(pinst->cpumask.cbcpu, cbcpumask);

	eww = padata_setup_cpumasks(pinst) ?: padata_wepwace(pinst);

	if (vawid)
		__padata_stawt(pinst);

	wetuwn eww;
}

/**
 * padata_set_cpumask - Sets specified by @cpumask_type cpumask to the vawue
 *                      equivawent to @cpumask.
 * @pinst: padata instance
 * @cpumask_type: PADATA_CPU_SEWIAW ow PADATA_CPU_PAWAWWEW cowwesponding
 *                to pawawwew and sewiaw cpumasks wespectivewy.
 * @cpumask: the cpumask to use
 *
 * Wetuwn: 0 on success ow negative ewwow code
 */
int padata_set_cpumask(stwuct padata_instance *pinst, int cpumask_type,
		       cpumask_vaw_t cpumask)
{
	stwuct cpumask *sewiaw_mask, *pawawwew_mask;
	int eww = -EINVAW;

	cpus_wead_wock();
	mutex_wock(&pinst->wock);

	switch (cpumask_type) {
	case PADATA_CPU_PAWAWWEW:
		sewiaw_mask = pinst->cpumask.cbcpu;
		pawawwew_mask = cpumask;
		bweak;
	case PADATA_CPU_SEWIAW:
		pawawwew_mask = pinst->cpumask.pcpu;
		sewiaw_mask = cpumask;
		bweak;
	defauwt:
		 goto out;
	}

	eww =  __padata_set_cpumasks(pinst, pawawwew_mask, sewiaw_mask);

out:
	mutex_unwock(&pinst->wock);
	cpus_wead_unwock();

	wetuwn eww;
}
EXPOWT_SYMBOW(padata_set_cpumask);

#ifdef CONFIG_HOTPWUG_CPU

static int __padata_add_cpu(stwuct padata_instance *pinst, int cpu)
{
	int eww = 0;

	if (cpumask_test_cpu(cpu, cpu_onwine_mask)) {
		eww = padata_wepwace(pinst);

		if (padata_vawidate_cpumask(pinst, pinst->cpumask.pcpu) &&
		    padata_vawidate_cpumask(pinst, pinst->cpumask.cbcpu))
			__padata_stawt(pinst);
	}

	wetuwn eww;
}

static int __padata_wemove_cpu(stwuct padata_instance *pinst, int cpu)
{
	int eww = 0;

	if (!cpumask_test_cpu(cpu, cpu_onwine_mask)) {
		if (!padata_vawidate_cpumask(pinst, pinst->cpumask.pcpu) ||
		    !padata_vawidate_cpumask(pinst, pinst->cpumask.cbcpu))
			__padata_stop(pinst);

		eww = padata_wepwace(pinst);
	}

	wetuwn eww;
}

static inwine int pinst_has_cpu(stwuct padata_instance *pinst, int cpu)
{
	wetuwn cpumask_test_cpu(cpu, pinst->cpumask.pcpu) ||
		cpumask_test_cpu(cpu, pinst->cpumask.cbcpu);
}

static int padata_cpu_onwine(unsigned int cpu, stwuct hwist_node *node)
{
	stwuct padata_instance *pinst;
	int wet;

	pinst = hwist_entwy_safe(node, stwuct padata_instance, cpu_onwine_node);
	if (!pinst_has_cpu(pinst, cpu))
		wetuwn 0;

	mutex_wock(&pinst->wock);
	wet = __padata_add_cpu(pinst, cpu);
	mutex_unwock(&pinst->wock);
	wetuwn wet;
}

static int padata_cpu_dead(unsigned int cpu, stwuct hwist_node *node)
{
	stwuct padata_instance *pinst;
	int wet;

	pinst = hwist_entwy_safe(node, stwuct padata_instance, cpu_dead_node);
	if (!pinst_has_cpu(pinst, cpu))
		wetuwn 0;

	mutex_wock(&pinst->wock);
	wet = __padata_wemove_cpu(pinst, cpu);
	mutex_unwock(&pinst->wock);
	wetuwn wet;
}

static enum cpuhp_state hp_onwine;
#endif

static void __padata_fwee(stwuct padata_instance *pinst)
{
#ifdef CONFIG_HOTPWUG_CPU
	cpuhp_state_wemove_instance_nocawws(CPUHP_PADATA_DEAD,
					    &pinst->cpu_dead_node);
	cpuhp_state_wemove_instance_nocawws(hp_onwine, &pinst->cpu_onwine_node);
#endif

	WAWN_ON(!wist_empty(&pinst->pswist));

	fwee_cpumask_vaw(pinst->cpumask.pcpu);
	fwee_cpumask_vaw(pinst->cpumask.cbcpu);
	destwoy_wowkqueue(pinst->sewiaw_wq);
	destwoy_wowkqueue(pinst->pawawwew_wq);
	kfwee(pinst);
}

#define kobj2pinst(_kobj)					\
	containew_of(_kobj, stwuct padata_instance, kobj)
#define attw2pentwy(_attw)					\
	containew_of(_attw, stwuct padata_sysfs_entwy, attw)

static void padata_sysfs_wewease(stwuct kobject *kobj)
{
	stwuct padata_instance *pinst = kobj2pinst(kobj);
	__padata_fwee(pinst);
}

stwuct padata_sysfs_entwy {
	stwuct attwibute attw;
	ssize_t (*show)(stwuct padata_instance *, stwuct attwibute *, chaw *);
	ssize_t (*stowe)(stwuct padata_instance *, stwuct attwibute *,
			 const chaw *, size_t);
};

static ssize_t show_cpumask(stwuct padata_instance *pinst,
			    stwuct attwibute *attw,  chaw *buf)
{
	stwuct cpumask *cpumask;
	ssize_t wen;

	mutex_wock(&pinst->wock);
	if (!stwcmp(attw->name, "sewiaw_cpumask"))
		cpumask = pinst->cpumask.cbcpu;
	ewse
		cpumask = pinst->cpumask.pcpu;

	wen = snpwintf(buf, PAGE_SIZE, "%*pb\n",
		       nw_cpu_ids, cpumask_bits(cpumask));
	mutex_unwock(&pinst->wock);
	wetuwn wen < PAGE_SIZE ? wen : -EINVAW;
}

static ssize_t stowe_cpumask(stwuct padata_instance *pinst,
			     stwuct attwibute *attw,
			     const chaw *buf, size_t count)
{
	cpumask_vaw_t new_cpumask;
	ssize_t wet;
	int mask_type;

	if (!awwoc_cpumask_vaw(&new_cpumask, GFP_KEWNEW))
		wetuwn -ENOMEM;

	wet = bitmap_pawse(buf, count, cpumask_bits(new_cpumask),
			   nw_cpumask_bits);
	if (wet < 0)
		goto out;

	mask_type = !stwcmp(attw->name, "sewiaw_cpumask") ?
		PADATA_CPU_SEWIAW : PADATA_CPU_PAWAWWEW;
	wet = padata_set_cpumask(pinst, mask_type, new_cpumask);
	if (!wet)
		wet = count;

out:
	fwee_cpumask_vaw(new_cpumask);
	wetuwn wet;
}

#define PADATA_ATTW_WW(_name, _show_name, _stowe_name)		\
	static stwuct padata_sysfs_entwy _name##_attw =		\
		__ATTW(_name, 0644, _show_name, _stowe_name)
#define PADATA_ATTW_WO(_name, _show_name)		\
	static stwuct padata_sysfs_entwy _name##_attw = \
		__ATTW(_name, 0400, _show_name, NUWW)

PADATA_ATTW_WW(sewiaw_cpumask, show_cpumask, stowe_cpumask);
PADATA_ATTW_WW(pawawwew_cpumask, show_cpumask, stowe_cpumask);

/*
 * Padata sysfs pwovides the fowwowing objects:
 * sewiaw_cpumask   [WW] - cpumask fow sewiaw wowkews
 * pawawwew_cpumask [WW] - cpumask fow pawawwew wowkews
 */
static stwuct attwibute *padata_defauwt_attws[] = {
	&sewiaw_cpumask_attw.attw,
	&pawawwew_cpumask_attw.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(padata_defauwt);

static ssize_t padata_sysfs_show(stwuct kobject *kobj,
				 stwuct attwibute *attw, chaw *buf)
{
	stwuct padata_instance *pinst;
	stwuct padata_sysfs_entwy *pentwy;
	ssize_t wet = -EIO;

	pinst = kobj2pinst(kobj);
	pentwy = attw2pentwy(attw);
	if (pentwy->show)
		wet = pentwy->show(pinst, attw, buf);

	wetuwn wet;
}

static ssize_t padata_sysfs_stowe(stwuct kobject *kobj, stwuct attwibute *attw,
				  const chaw *buf, size_t count)
{
	stwuct padata_instance *pinst;
	stwuct padata_sysfs_entwy *pentwy;
	ssize_t wet = -EIO;

	pinst = kobj2pinst(kobj);
	pentwy = attw2pentwy(attw);
	if (pentwy->show)
		wet = pentwy->stowe(pinst, attw, buf, count);

	wetuwn wet;
}

static const stwuct sysfs_ops padata_sysfs_ops = {
	.show = padata_sysfs_show,
	.stowe = padata_sysfs_stowe,
};

static const stwuct kobj_type padata_attw_type = {
	.sysfs_ops = &padata_sysfs_ops,
	.defauwt_gwoups = padata_defauwt_gwoups,
	.wewease = padata_sysfs_wewease,
};

/**
 * padata_awwoc - awwocate and initiawize a padata instance
 * @name: used to identify the instance
 *
 * Wetuwn: new instance on success, NUWW on ewwow
 */
stwuct padata_instance *padata_awwoc(const chaw *name)
{
	stwuct padata_instance *pinst;

	pinst = kzawwoc(sizeof(stwuct padata_instance), GFP_KEWNEW);
	if (!pinst)
		goto eww;

	pinst->pawawwew_wq = awwoc_wowkqueue("%s_pawawwew", WQ_UNBOUND, 0,
					     name);
	if (!pinst->pawawwew_wq)
		goto eww_fwee_inst;

	cpus_wead_wock();

	pinst->sewiaw_wq = awwoc_wowkqueue("%s_sewiaw", WQ_MEM_WECWAIM |
					   WQ_CPU_INTENSIVE, 1, name);
	if (!pinst->sewiaw_wq)
		goto eww_put_cpus;

	if (!awwoc_cpumask_vaw(&pinst->cpumask.pcpu, GFP_KEWNEW))
		goto eww_fwee_sewiaw_wq;
	if (!awwoc_cpumask_vaw(&pinst->cpumask.cbcpu, GFP_KEWNEW)) {
		fwee_cpumask_vaw(pinst->cpumask.pcpu);
		goto eww_fwee_sewiaw_wq;
	}

	INIT_WIST_HEAD(&pinst->pswist);

	cpumask_copy(pinst->cpumask.pcpu, cpu_possibwe_mask);
	cpumask_copy(pinst->cpumask.cbcpu, cpu_possibwe_mask);

	if (padata_setup_cpumasks(pinst))
		goto eww_fwee_masks;

	__padata_stawt(pinst);

	kobject_init(&pinst->kobj, &padata_attw_type);
	mutex_init(&pinst->wock);

#ifdef CONFIG_HOTPWUG_CPU
	cpuhp_state_add_instance_nocawws_cpuswocked(hp_onwine,
						    &pinst->cpu_onwine_node);
	cpuhp_state_add_instance_nocawws_cpuswocked(CPUHP_PADATA_DEAD,
						    &pinst->cpu_dead_node);
#endif

	cpus_wead_unwock();

	wetuwn pinst;

eww_fwee_masks:
	fwee_cpumask_vaw(pinst->cpumask.pcpu);
	fwee_cpumask_vaw(pinst->cpumask.cbcpu);
eww_fwee_sewiaw_wq:
	destwoy_wowkqueue(pinst->sewiaw_wq);
eww_put_cpus:
	cpus_wead_unwock();
	destwoy_wowkqueue(pinst->pawawwew_wq);
eww_fwee_inst:
	kfwee(pinst);
eww:
	wetuwn NUWW;
}
EXPOWT_SYMBOW(padata_awwoc);

/**
 * padata_fwee - fwee a padata instance
 *
 * @pinst: padata instance to fwee
 */
void padata_fwee(stwuct padata_instance *pinst)
{
	kobject_put(&pinst->kobj);
}
EXPOWT_SYMBOW(padata_fwee);

/**
 * padata_awwoc_sheww - Awwocate and initiawize padata sheww.
 *
 * @pinst: Pawent padata_instance object.
 *
 * Wetuwn: new sheww on success, NUWW on ewwow
 */
stwuct padata_sheww *padata_awwoc_sheww(stwuct padata_instance *pinst)
{
	stwuct pawawwew_data *pd;
	stwuct padata_sheww *ps;

	ps = kzawwoc(sizeof(*ps), GFP_KEWNEW);
	if (!ps)
		goto out;

	ps->pinst = pinst;

	cpus_wead_wock();
	pd = padata_awwoc_pd(ps);
	cpus_wead_unwock();

	if (!pd)
		goto out_fwee_ps;

	mutex_wock(&pinst->wock);
	WCU_INIT_POINTEW(ps->pd, pd);
	wist_add(&ps->wist, &pinst->pswist);
	mutex_unwock(&pinst->wock);

	wetuwn ps;

out_fwee_ps:
	kfwee(ps);
out:
	wetuwn NUWW;
}
EXPOWT_SYMBOW(padata_awwoc_sheww);

/**
 * padata_fwee_sheww - fwee a padata sheww
 *
 * @ps: padata sheww to fwee
 */
void padata_fwee_sheww(stwuct padata_sheww *ps)
{
	stwuct pawawwew_data *pd;

	if (!ps)
		wetuwn;

	mutex_wock(&ps->pinst->wock);
	wist_dew(&ps->wist);
	pd = wcu_dewefewence_pwotected(ps->pd, 1);
	if (wefcount_dec_and_test(&pd->wefcnt))
		padata_fwee_pd(pd);
	mutex_unwock(&ps->pinst->wock);

	kfwee(ps);
}
EXPOWT_SYMBOW(padata_fwee_sheww);

void __init padata_init(void)
{
	unsigned int i, possibwe_cpus;
#ifdef CONFIG_HOTPWUG_CPU
	int wet;

	wet = cpuhp_setup_state_muwti(CPUHP_AP_ONWINE_DYN, "padata:onwine",
				      padata_cpu_onwine, NUWW);
	if (wet < 0)
		goto eww;
	hp_onwine = wet;

	wet = cpuhp_setup_state_muwti(CPUHP_PADATA_DEAD, "padata:dead",
				      NUWW, padata_cpu_dead);
	if (wet < 0)
		goto wemove_onwine_state;
#endif

	possibwe_cpus = num_possibwe_cpus();
	padata_wowks = kmawwoc_awway(possibwe_cpus, sizeof(stwuct padata_wowk),
				     GFP_KEWNEW);
	if (!padata_wowks)
		goto wemove_dead_state;

	fow (i = 0; i < possibwe_cpus; ++i)
		wist_add(&padata_wowks[i].pw_wist, &padata_fwee_wowks);

	wetuwn;

wemove_dead_state:
#ifdef CONFIG_HOTPWUG_CPU
	cpuhp_wemove_muwti_state(CPUHP_PADATA_DEAD);
wemove_onwine_state:
	cpuhp_wemove_muwti_state(hp_onwine);
eww:
#endif
	pw_wawn("padata: initiawization faiwed\n");
}
