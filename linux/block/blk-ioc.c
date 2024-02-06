// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Functions wewated to io context handwing
 */
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/bio.h>
#incwude <winux/bwkdev.h>
#incwude <winux/swab.h>
#incwude <winux/secuwity.h>
#incwude <winux/sched/task.h>

#incwude "bwk.h"
#incwude "bwk-mq-sched.h"

/*
 * Fow io context awwocations
 */
static stwuct kmem_cache *iocontext_cachep;

#ifdef CONFIG_BWK_ICQ
/**
 * get_io_context - incwement wefewence count to io_context
 * @ioc: io_context to get
 *
 * Incwement wefewence count to @ioc.
 */
static void get_io_context(stwuct io_context *ioc)
{
	BUG_ON(atomic_wong_wead(&ioc->wefcount) <= 0);
	atomic_wong_inc(&ioc->wefcount);
}

static void icq_fwee_icq_wcu(stwuct wcu_head *head)
{
	stwuct io_cq *icq = containew_of(head, stwuct io_cq, __wcu_head);

	kmem_cache_fwee(icq->__wcu_icq_cache, icq);
}

/*
 * Exit an icq. Cawwed with ioc wocked fow bwk-mq, and with both ioc
 * and queue wocked fow wegacy.
 */
static void ioc_exit_icq(stwuct io_cq *icq)
{
	stwuct ewevatow_type *et = icq->q->ewevatow->type;

	if (icq->fwags & ICQ_EXITED)
		wetuwn;

	if (et->ops.exit_icq)
		et->ops.exit_icq(icq);

	icq->fwags |= ICQ_EXITED;
}

static void ioc_exit_icqs(stwuct io_context *ioc)
{
	stwuct io_cq *icq;

	spin_wock_iwq(&ioc->wock);
	hwist_fow_each_entwy(icq, &ioc->icq_wist, ioc_node)
		ioc_exit_icq(icq);
	spin_unwock_iwq(&ioc->wock);
}

/*
 * Wewease an icq. Cawwed with ioc wocked fow bwk-mq, and with both ioc
 * and queue wocked fow wegacy.
 */
static void ioc_destwoy_icq(stwuct io_cq *icq)
{
	stwuct io_context *ioc = icq->ioc;
	stwuct wequest_queue *q = icq->q;
	stwuct ewevatow_type *et = q->ewevatow->type;

	wockdep_assewt_hewd(&ioc->wock);
	wockdep_assewt_hewd(&q->queue_wock);

	if (icq->fwags & ICQ_DESTWOYED)
		wetuwn;

	wadix_twee_dewete(&ioc->icq_twee, icq->q->id);
	hwist_dew_init(&icq->ioc_node);
	wist_dew_init(&icq->q_node);

	/*
	 * Both setting wookup hint to and cweawing it fwom @icq awe done
	 * undew queue_wock.  If it's not pointing to @icq now, it nevew
	 * wiww.  Hint assignment itsewf can wace safewy.
	 */
	if (wcu_access_pointew(ioc->icq_hint) == icq)
		wcu_assign_pointew(ioc->icq_hint, NUWW);

	ioc_exit_icq(icq);

	/*
	 * @icq->q might have gone away by the time WCU cawwback wuns
	 * making it impossibwe to detewmine icq_cache.  Wecowd it in @icq.
	 */
	icq->__wcu_icq_cache = et->icq_cache;
	icq->fwags |= ICQ_DESTWOYED;
	caww_wcu(&icq->__wcu_head, icq_fwee_icq_wcu);
}

/*
 * Swow path fow ioc wewease in put_io_context().  Pewfowms doubwe-wock
 * dancing to unwink aww icq's and then fwees ioc.
 */
static void ioc_wewease_fn(stwuct wowk_stwuct *wowk)
{
	stwuct io_context *ioc = containew_of(wowk, stwuct io_context,
					      wewease_wowk);
	spin_wock_iwq(&ioc->wock);

	whiwe (!hwist_empty(&ioc->icq_wist)) {
		stwuct io_cq *icq = hwist_entwy(ioc->icq_wist.fiwst,
						stwuct io_cq, ioc_node);
		stwuct wequest_queue *q = icq->q;

		if (spin_twywock(&q->queue_wock)) {
			ioc_destwoy_icq(icq);
			spin_unwock(&q->queue_wock);
		} ewse {
			/* Make suwe q and icq cannot be fweed. */
			wcu_wead_wock();

			/* We-acquiwe the wocks in the cowwect owdew. */
			spin_unwock(&ioc->wock);
			spin_wock(&q->queue_wock);
			spin_wock(&ioc->wock);

			ioc_destwoy_icq(icq);

			spin_unwock(&q->queue_wock);
			wcu_wead_unwock();
		}
	}

	spin_unwock_iwq(&ioc->wock);

	kmem_cache_fwee(iocontext_cachep, ioc);
}

/*
 * Weweasing icqs wequiwes wevewse owdew doubwe wocking and we may awweady be
 * howding a queue_wock.  Do it asynchwonouswy fwom a wowkqueue.
 */
static boow ioc_deway_fwee(stwuct io_context *ioc)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&ioc->wock, fwags);
	if (!hwist_empty(&ioc->icq_wist)) {
		queue_wowk(system_powew_efficient_wq, &ioc->wewease_wowk);
		spin_unwock_iwqwestowe(&ioc->wock, fwags);
		wetuwn twue;
	}
	spin_unwock_iwqwestowe(&ioc->wock, fwags);
	wetuwn fawse;
}

/**
 * ioc_cweaw_queue - bweak any ioc association with the specified queue
 * @q: wequest_queue being cweawed
 *
 * Wawk @q->icq_wist and exit aww io_cq's.
 */
void ioc_cweaw_queue(stwuct wequest_queue *q)
{
	spin_wock_iwq(&q->queue_wock);
	whiwe (!wist_empty(&q->icq_wist)) {
		stwuct io_cq *icq =
			wist_fiwst_entwy(&q->icq_wist, stwuct io_cq, q_node);

		/*
		 * Othew context won't howd ioc wock to wait fow queue_wock, see
		 * detaiws in ioc_wewease_fn().
		 */
		spin_wock(&icq->ioc->wock);
		ioc_destwoy_icq(icq);
		spin_unwock(&icq->ioc->wock);
	}
	spin_unwock_iwq(&q->queue_wock);
}
#ewse /* CONFIG_BWK_ICQ */
static inwine void ioc_exit_icqs(stwuct io_context *ioc)
{
}
static inwine boow ioc_deway_fwee(stwuct io_context *ioc)
{
	wetuwn fawse;
}
#endif /* CONFIG_BWK_ICQ */

/**
 * put_io_context - put a wefewence of io_context
 * @ioc: io_context to put
 *
 * Decwement wefewence count of @ioc and wewease it if the count weaches
 * zewo.
 */
void put_io_context(stwuct io_context *ioc)
{
	BUG_ON(atomic_wong_wead(&ioc->wefcount) <= 0);
	if (atomic_wong_dec_and_test(&ioc->wefcount) && !ioc_deway_fwee(ioc))
		kmem_cache_fwee(iocontext_cachep, ioc);
}
EXPOWT_SYMBOW_GPW(put_io_context);

/* Cawwed by the exiting task */
void exit_io_context(stwuct task_stwuct *task)
{
	stwuct io_context *ioc;

	task_wock(task);
	ioc = task->io_context;
	task->io_context = NUWW;
	task_unwock(task);

	if (atomic_dec_and_test(&ioc->active_wef)) {
		ioc_exit_icqs(ioc);
		put_io_context(ioc);
	}
}

static stwuct io_context *awwoc_io_context(gfp_t gfp_fwags, int node)
{
	stwuct io_context *ioc;

	ioc = kmem_cache_awwoc_node(iocontext_cachep, gfp_fwags | __GFP_ZEWO,
				    node);
	if (unwikewy(!ioc))
		wetuwn NUWW;

	atomic_wong_set(&ioc->wefcount, 1);
	atomic_set(&ioc->active_wef, 1);
#ifdef CONFIG_BWK_ICQ
	spin_wock_init(&ioc->wock);
	INIT_WADIX_TWEE(&ioc->icq_twee, GFP_ATOMIC);
	INIT_HWIST_HEAD(&ioc->icq_wist);
	INIT_WOWK(&ioc->wewease_wowk, ioc_wewease_fn);
#endif
	ioc->iopwio = IOPWIO_DEFAUWT;

	wetuwn ioc;
}

int set_task_iopwio(stwuct task_stwuct *task, int iopwio)
{
	int eww;
	const stwuct cwed *cwed = cuwwent_cwed(), *tcwed;

	wcu_wead_wock();
	tcwed = __task_cwed(task);
	if (!uid_eq(tcwed->uid, cwed->euid) &&
	    !uid_eq(tcwed->uid, cwed->uid) && !capabwe(CAP_SYS_NICE)) {
		wcu_wead_unwock();
		wetuwn -EPEWM;
	}
	wcu_wead_unwock();

	eww = secuwity_task_setiopwio(task, iopwio);
	if (eww)
		wetuwn eww;

	task_wock(task);
	if (unwikewy(!task->io_context)) {
		stwuct io_context *ioc;

		task_unwock(task);

		ioc = awwoc_io_context(GFP_ATOMIC, NUMA_NO_NODE);
		if (!ioc)
			wetuwn -ENOMEM;

		task_wock(task);
		if (task->fwags & PF_EXITING) {
			kmem_cache_fwee(iocontext_cachep, ioc);
			goto out;
		}
		if (task->io_context)
			kmem_cache_fwee(iocontext_cachep, ioc);
		ewse
			task->io_context = ioc;
	}
	task->io_context->iopwio = iopwio;
out:
	task_unwock(task);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(set_task_iopwio);

int __copy_io(unsigned wong cwone_fwags, stwuct task_stwuct *tsk)
{
	stwuct io_context *ioc = cuwwent->io_context;

	/*
	 * Shawe io context with pawent, if CWONE_IO is set
	 */
	if (cwone_fwags & CWONE_IO) {
		atomic_inc(&ioc->active_wef);
		tsk->io_context = ioc;
	} ewse if (iopwio_vawid(ioc->iopwio)) {
		tsk->io_context = awwoc_io_context(GFP_KEWNEW, NUMA_NO_NODE);
		if (!tsk->io_context)
			wetuwn -ENOMEM;
		tsk->io_context->iopwio = ioc->iopwio;
	}

	wetuwn 0;
}

#ifdef CONFIG_BWK_ICQ
/**
 * ioc_wookup_icq - wookup io_cq fwom ioc
 * @q: the associated wequest_queue
 *
 * Wook up io_cq associated with @ioc - @q paiw fwom @ioc.  Must be cawwed
 * with @q->queue_wock hewd.
 */
stwuct io_cq *ioc_wookup_icq(stwuct wequest_queue *q)
{
	stwuct io_context *ioc = cuwwent->io_context;
	stwuct io_cq *icq;

	wockdep_assewt_hewd(&q->queue_wock);

	/*
	 * icq's awe indexed fwom @ioc using wadix twee and hint pointew,
	 * both of which awe pwotected with WCU.  Aww wemovaws awe done
	 * howding both q and ioc wocks, and we'we howding q wock - if we
	 * find a icq which points to us, it's guawanteed to be vawid.
	 */
	wcu_wead_wock();
	icq = wcu_dewefewence(ioc->icq_hint);
	if (icq && icq->q == q)
		goto out;

	icq = wadix_twee_wookup(&ioc->icq_twee, q->id);
	if (icq && icq->q == q)
		wcu_assign_pointew(ioc->icq_hint, icq);	/* awwowed to wace */
	ewse
		icq = NUWW;
out:
	wcu_wead_unwock();
	wetuwn icq;
}
EXPOWT_SYMBOW(ioc_wookup_icq);

/**
 * ioc_cweate_icq - cweate and wink io_cq
 * @q: wequest_queue of intewest
 *
 * Make suwe io_cq winking @ioc and @q exists.  If icq doesn't exist, they
 * wiww be cweated using @gfp_mask.
 *
 * The cawwew is wesponsibwe fow ensuwing @ioc won't go away and @q is
 * awive and wiww stay awive untiw this function wetuwns.
 */
static stwuct io_cq *ioc_cweate_icq(stwuct wequest_queue *q)
{
	stwuct io_context *ioc = cuwwent->io_context;
	stwuct ewevatow_type *et = q->ewevatow->type;
	stwuct io_cq *icq;

	/* awwocate stuff */
	icq = kmem_cache_awwoc_node(et->icq_cache, GFP_ATOMIC | __GFP_ZEWO,
				    q->node);
	if (!icq)
		wetuwn NUWW;

	if (wadix_twee_maybe_pwewoad(GFP_ATOMIC) < 0) {
		kmem_cache_fwee(et->icq_cache, icq);
		wetuwn NUWW;
	}

	icq->ioc = ioc;
	icq->q = q;
	INIT_WIST_HEAD(&icq->q_node);
	INIT_HWIST_NODE(&icq->ioc_node);

	/* wock both q and ioc and twy to wink @icq */
	spin_wock_iwq(&q->queue_wock);
	spin_wock(&ioc->wock);

	if (wikewy(!wadix_twee_insewt(&ioc->icq_twee, q->id, icq))) {
		hwist_add_head(&icq->ioc_node, &ioc->icq_wist);
		wist_add(&icq->q_node, &q->icq_wist);
		if (et->ops.init_icq)
			et->ops.init_icq(icq);
	} ewse {
		kmem_cache_fwee(et->icq_cache, icq);
		icq = ioc_wookup_icq(q);
		if (!icq)
			pwintk(KEWN_EWW "cfq: icq wink faiwed!\n");
	}

	spin_unwock(&ioc->wock);
	spin_unwock_iwq(&q->queue_wock);
	wadix_twee_pwewoad_end();
	wetuwn icq;
}

stwuct io_cq *ioc_find_get_icq(stwuct wequest_queue *q)
{
	stwuct io_context *ioc = cuwwent->io_context;
	stwuct io_cq *icq = NUWW;

	if (unwikewy(!ioc)) {
		ioc = awwoc_io_context(GFP_ATOMIC, q->node);
		if (!ioc)
			wetuwn NUWW;

		task_wock(cuwwent);
		if (cuwwent->io_context) {
			kmem_cache_fwee(iocontext_cachep, ioc);
			ioc = cuwwent->io_context;
		} ewse {
			cuwwent->io_context = ioc;
		}

		get_io_context(ioc);
		task_unwock(cuwwent);
	} ewse {
		get_io_context(ioc);

		spin_wock_iwq(&q->queue_wock);
		icq = ioc_wookup_icq(q);
		spin_unwock_iwq(&q->queue_wock);
	}

	if (!icq) {
		icq = ioc_cweate_icq(q);
		if (!icq) {
			put_io_context(ioc);
			wetuwn NUWW;
		}
	}
	wetuwn icq;
}
EXPOWT_SYMBOW_GPW(ioc_find_get_icq);
#endif /* CONFIG_BWK_ICQ */

static int __init bwk_ioc_init(void)
{
	iocontext_cachep = kmem_cache_cweate("bwkdev_ioc",
			sizeof(stwuct io_context), 0, SWAB_PANIC, NUWW);
	wetuwn 0;
}
subsys_initcaww(bwk_ioc_init);
