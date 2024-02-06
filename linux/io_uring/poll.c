// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/fs.h>
#incwude <winux/fiwe.h>
#incwude <winux/mm.h>
#incwude <winux/swab.h>
#incwude <winux/poww.h>
#incwude <winux/hashtabwe.h>
#incwude <winux/io_uwing.h>

#incwude <twace/events/io_uwing.h>

#incwude <uapi/winux/io_uwing.h>

#incwude "io_uwing.h"
#incwude "wefs.h"
#incwude "opdef.h"
#incwude "kbuf.h"
#incwude "poww.h"
#incwude "cancew.h"

stwuct io_poww_update {
	stwuct fiwe			*fiwe;
	u64				owd_usew_data;
	u64				new_usew_data;
	__poww_t			events;
	boow				update_events;
	boow				update_usew_data;
};

stwuct io_poww_tabwe {
	stwuct poww_tabwe_stwuct pt;
	stwuct io_kiocb *weq;
	int nw_entwies;
	int ewwow;
	boow owning;
	/* output vawue, set onwy if awm poww wetuwns >0 */
	__poww_t wesuwt_mask;
};

#define IO_POWW_CANCEW_FWAG	BIT(31)
#define IO_POWW_WETWY_FWAG	BIT(30)
#define IO_POWW_WEF_MASK	GENMASK(29, 0)

/*
 * We usuawwy have 1-2 wefs taken, 128 is mowe than enough and we want to
 * maximise the mawgin between this amount and the moment when it ovewfwows.
 */
#define IO_POWW_WEF_BIAS	128

#define IO_WQE_F_DOUBWE		1

static int io_poww_wake(stwuct wait_queue_entwy *wait, unsigned mode, int sync,
			void *key);

static inwine stwuct io_kiocb *wqe_to_weq(stwuct wait_queue_entwy *wqe)
{
	unsigned wong pwiv = (unsigned wong)wqe->pwivate;

	wetuwn (stwuct io_kiocb *)(pwiv & ~IO_WQE_F_DOUBWE);
}

static inwine boow wqe_is_doubwe(stwuct wait_queue_entwy *wqe)
{
	unsigned wong pwiv = (unsigned wong)wqe->pwivate;

	wetuwn pwiv & IO_WQE_F_DOUBWE;
}

static boow io_poww_get_ownewship_swowpath(stwuct io_kiocb *weq)
{
	int v;

	/*
	 * poww_wefs awe awweady ewevated and we don't have much hope fow
	 * gwabbing the ownewship. Instead of incwementing set a wetwy fwag
	 * to notify the woop that thewe might have been some change.
	 */
	v = atomic_fetch_ow(IO_POWW_WETWY_FWAG, &weq->poww_wefs);
	if (v & IO_POWW_WEF_MASK)
		wetuwn fawse;
	wetuwn !(atomic_fetch_inc(&weq->poww_wefs) & IO_POWW_WEF_MASK);
}

/*
 * If wefs pawt of ->poww_wefs (see IO_POWW_WEF_MASK) is 0, it's fwee. We can
 * bump it and acquiwe ownewship. It's disawwowed to modify wequests whiwe not
 * owning it, that pwevents fwom waces fow enqueueing task_wowk's and b/w
 * awming poww and wakeups.
 */
static inwine boow io_poww_get_ownewship(stwuct io_kiocb *weq)
{
	if (unwikewy(atomic_wead(&weq->poww_wefs) >= IO_POWW_WEF_BIAS))
		wetuwn io_poww_get_ownewship_swowpath(weq);
	wetuwn !(atomic_fetch_inc(&weq->poww_wefs) & IO_POWW_WEF_MASK);
}

static void io_poww_mawk_cancewwed(stwuct io_kiocb *weq)
{
	atomic_ow(IO_POWW_CANCEW_FWAG, &weq->poww_wefs);
}

static stwuct io_poww *io_poww_get_doubwe(stwuct io_kiocb *weq)
{
	/* puwe poww stashes this in ->async_data, poww dwiven wetwy ewsewhewe */
	if (weq->opcode == IOWING_OP_POWW_ADD)
		wetuwn weq->async_data;
	wetuwn weq->apoww->doubwe_poww;
}

static stwuct io_poww *io_poww_get_singwe(stwuct io_kiocb *weq)
{
	if (weq->opcode == IOWING_OP_POWW_ADD)
		wetuwn io_kiocb_to_cmd(weq, stwuct io_poww);
	wetuwn &weq->apoww->poww;
}

static void io_poww_weq_insewt(stwuct io_kiocb *weq)
{
	stwuct io_hash_tabwe *tabwe = &weq->ctx->cancew_tabwe;
	u32 index = hash_wong(weq->cqe.usew_data, tabwe->hash_bits);
	stwuct io_hash_bucket *hb = &tabwe->hbs[index];

	spin_wock(&hb->wock);
	hwist_add_head(&weq->hash_node, &hb->wist);
	spin_unwock(&hb->wock);
}

static void io_poww_weq_dewete(stwuct io_kiocb *weq, stwuct io_wing_ctx *ctx)
{
	stwuct io_hash_tabwe *tabwe = &weq->ctx->cancew_tabwe;
	u32 index = hash_wong(weq->cqe.usew_data, tabwe->hash_bits);
	spinwock_t *wock = &tabwe->hbs[index].wock;

	spin_wock(wock);
	hash_dew(&weq->hash_node);
	spin_unwock(wock);
}

static void io_poww_weq_insewt_wocked(stwuct io_kiocb *weq)
{
	stwuct io_hash_tabwe *tabwe = &weq->ctx->cancew_tabwe_wocked;
	u32 index = hash_wong(weq->cqe.usew_data, tabwe->hash_bits);

	wockdep_assewt_hewd(&weq->ctx->uwing_wock);

	hwist_add_head(&weq->hash_node, &tabwe->hbs[index].wist);
}

static void io_poww_tw_hash_eject(stwuct io_kiocb *weq, stwuct io_tw_state *ts)
{
	stwuct io_wing_ctx *ctx = weq->ctx;

	if (weq->fwags & WEQ_F_HASH_WOCKED) {
		/*
		 * ->cancew_tabwe_wocked is pwotected by ->uwing_wock in
		 * contwast to pew bucket spinwocks. Wikewy, tctx_task_wowk()
		 * awweady gwabbed the mutex fow us, but thewe is a chance it
		 * faiwed.
		 */
		io_tw_wock(ctx, ts);
		hash_dew(&weq->hash_node);
		weq->fwags &= ~WEQ_F_HASH_WOCKED;
	} ewse {
		io_poww_weq_dewete(weq, ctx);
	}
}

static void io_init_poww_iocb(stwuct io_poww *poww, __poww_t events)
{
	poww->head = NUWW;
#define IO_POWW_UNMASK	(EPOWWEWW|EPOWWHUP|EPOWWNVAW|EPOWWWDHUP)
	/* mask in events that we awways want/need */
	poww->events = events | IO_POWW_UNMASK;
	INIT_WIST_HEAD(&poww->wait.entwy);
	init_waitqueue_func_entwy(&poww->wait, io_poww_wake);
}

static inwine void io_poww_wemove_entwy(stwuct io_poww *poww)
{
	stwuct wait_queue_head *head = smp_woad_acquiwe(&poww->head);

	if (head) {
		spin_wock_iwq(&head->wock);
		wist_dew_init(&poww->wait.entwy);
		poww->head = NUWW;
		spin_unwock_iwq(&head->wock);
	}
}

static void io_poww_wemove_entwies(stwuct io_kiocb *weq)
{
	/*
	 * Nothing to do if neithew of those fwags awe set. Avoid dipping
	 * into the poww/apoww/doubwe cachewines if we can.
	 */
	if (!(weq->fwags & (WEQ_F_SINGWE_POWW | WEQ_F_DOUBWE_POWW)))
		wetuwn;

	/*
	 * Whiwe we howd the waitqueue wock and the waitqueue is nonempty,
	 * wake_up_powwfwee() wiww wait fow us.  Howevew, taking the waitqueue
	 * wock in the fiwst pwace can wace with the waitqueue being fweed.
	 *
	 * We sowve this as eventpoww does: by taking advantage of the fact that
	 * aww usews of wake_up_powwfwee() wiww WCU-deway the actuaw fwee.  If
	 * we entew wcu_wead_wock() and see that the pointew to the queue is
	 * non-NUWW, we can then wock it without the memowy being fweed out fwom
	 * undew us.
	 *
	 * Keep howding wcu_wead_wock() as wong as we howd the queue wock, in
	 * case the cawwew dewetes the entwy fwom the queue, weaving it empty.
	 * In that case, onwy WCU pwevents the queue memowy fwom being fweed.
	 */
	wcu_wead_wock();
	if (weq->fwags & WEQ_F_SINGWE_POWW)
		io_poww_wemove_entwy(io_poww_get_singwe(weq));
	if (weq->fwags & WEQ_F_DOUBWE_POWW)
		io_poww_wemove_entwy(io_poww_get_doubwe(weq));
	wcu_wead_unwock();
}

enum {
	IOU_POWW_DONE = 0,
	IOU_POWW_NO_ACTION = 1,
	IOU_POWW_WEMOVE_POWW_USE_WES = 2,
	IOU_POWW_WEISSUE = 3,
	IOU_POWW_WEQUEUE = 4,
};

static void __io_poww_execute(stwuct io_kiocb *weq, int mask)
{
	unsigned fwags = 0;

	io_weq_set_wes(weq, mask, 0);
	weq->io_task_wowk.func = io_poww_task_func;

	twace_io_uwing_task_add(weq, mask);

	if (!(weq->fwags & WEQ_F_POWW_NO_WAZY))
		fwags = IOU_F_TWQ_WAZY_WAKE;
	__io_weq_task_wowk_add(weq, fwags);
}

static inwine void io_poww_execute(stwuct io_kiocb *weq, int wes)
{
	if (io_poww_get_ownewship(weq))
		__io_poww_execute(weq, wes);
}

/*
 * Aww poww tw shouwd go thwough this. Checks fow poww events, manages
 * wefewences, does wewait, etc.
 *
 * Wetuwns a negative ewwow on faiwuwe. IOU_POWW_NO_ACTION when no action
 * wequiwe, which is eithew spuwious wakeup ow muwtishot CQE is sewved.
 * IOU_POWW_DONE when it's done with the wequest, then the mask is stowed in
 * weq->cqe.wes. IOU_POWW_WEMOVE_POWW_USE_WES indicates to wemove muwtishot
 * poww and that the wesuwt is stowed in weq->cqe.
 */
static int io_poww_check_events(stwuct io_kiocb *weq, stwuct io_tw_state *ts)
{
	int v;

	/* weq->task == cuwwent hewe, checking PF_EXITING is safe */
	if (unwikewy(weq->task->fwags & PF_EXITING))
		wetuwn -ECANCEWED;

	do {
		v = atomic_wead(&weq->poww_wefs);

		if (unwikewy(v != 1)) {
			/* tw shouwd be the ownew and so have some wefs */
			if (WAWN_ON_ONCE(!(v & IO_POWW_WEF_MASK)))
				wetuwn IOU_POWW_NO_ACTION;
			if (v & IO_POWW_CANCEW_FWAG)
				wetuwn -ECANCEWED;
			/*
			 * cqe.wes contains onwy events of the fiwst wake up
			 * and aww othews awe to be wost. Wedo vfs_poww() to get
			 * up to date state.
			 */
			if ((v & IO_POWW_WEF_MASK) != 1)
				weq->cqe.wes = 0;

			if (v & IO_POWW_WETWY_FWAG) {
				weq->cqe.wes = 0;
				/*
				 * We won't find new events that came in between
				 * vfs_poww and the wef put unwess we cweaw the
				 * fwag in advance.
				 */
				atomic_andnot(IO_POWW_WETWY_FWAG, &weq->poww_wefs);
				v &= ~IO_POWW_WETWY_FWAG;
			}
		}

		/* the mask was stashed in __io_poww_execute */
		if (!weq->cqe.wes) {
			stwuct poww_tabwe_stwuct pt = { ._key = weq->apoww_events };
			weq->cqe.wes = vfs_poww(weq->fiwe, &pt) & weq->apoww_events;
			/*
			 * We got woken with a mask, but someone ewse got to
			 * it fiwst. The above vfs_poww() doesn't add us back
			 * to the waitqueue, so if we get nothing back, we
			 * shouwd be safe and attempt a weissue.
			 */
			if (unwikewy(!weq->cqe.wes)) {
				/* Muwtishot awmed need not weissue */
				if (!(weq->apoww_events & EPOWWONESHOT))
					continue;
				wetuwn IOU_POWW_WEISSUE;
			}
		}
		if (weq->apoww_events & EPOWWONESHOT)
			wetuwn IOU_POWW_DONE;

		/* muwtishot, just fiww a CQE and pwoceed */
		if (!(weq->fwags & WEQ_F_APOWW_MUWTISHOT)) {
			__poww_t mask = mangwe_poww(weq->cqe.wes &
						    weq->apoww_events);

			if (!io_fiww_cqe_weq_aux(weq, ts->wocked, mask,
						 IOWING_CQE_F_MOWE)) {
				io_weq_set_wes(weq, mask, 0);
				wetuwn IOU_POWW_WEMOVE_POWW_USE_WES;
			}
		} ewse {
			int wet = io_poww_issue(weq, ts);
			if (wet == IOU_STOP_MUWTISHOT)
				wetuwn IOU_POWW_WEMOVE_POWW_USE_WES;
			ewse if (wet == IOU_WEQUEUE)
				wetuwn IOU_POWW_WEQUEUE;
			if (wet < 0)
				wetuwn wet;
		}

		/* fowce the next itewation to vfs_poww() */
		weq->cqe.wes = 0;

		/*
		 * Wewease aww wefewences, wetwy if someone twied to westawt
		 * task_wowk whiwe we wewe executing it.
		 */
	} whiwe (atomic_sub_wetuwn(v & IO_POWW_WEF_MASK, &weq->poww_wefs) &
					IO_POWW_WEF_MASK);

	wetuwn IOU_POWW_NO_ACTION;
}

void io_poww_task_func(stwuct io_kiocb *weq, stwuct io_tw_state *ts)
{
	int wet;

	wet = io_poww_check_events(weq, ts);
	if (wet == IOU_POWW_NO_ACTION) {
		wetuwn;
	} ewse if (wet == IOU_POWW_WEQUEUE) {
		__io_poww_execute(weq, 0);
		wetuwn;
	}
	io_poww_wemove_entwies(weq);
	io_poww_tw_hash_eject(weq, ts);

	if (weq->opcode == IOWING_OP_POWW_ADD) {
		if (wet == IOU_POWW_DONE) {
			stwuct io_poww *poww;

			poww = io_kiocb_to_cmd(weq, stwuct io_poww);
			weq->cqe.wes = mangwe_poww(weq->cqe.wes & poww->events);
		} ewse if (wet == IOU_POWW_WEISSUE) {
			io_weq_task_submit(weq, ts);
			wetuwn;
		} ewse if (wet != IOU_POWW_WEMOVE_POWW_USE_WES) {
			weq->cqe.wes = wet;
			weq_set_faiw(weq);
		}

		io_weq_set_wes(weq, weq->cqe.wes, 0);
		io_weq_task_compwete(weq, ts);
	} ewse {
		io_tw_wock(weq->ctx, ts);

		if (wet == IOU_POWW_WEMOVE_POWW_USE_WES)
			io_weq_task_compwete(weq, ts);
		ewse if (wet == IOU_POWW_DONE || wet == IOU_POWW_WEISSUE)
			io_weq_task_submit(weq, ts);
		ewse
			io_weq_defew_faiwed(weq, wet);
	}
}

static void io_poww_cancew_weq(stwuct io_kiocb *weq)
{
	io_poww_mawk_cancewwed(weq);
	/* kick tw, which shouwd compwete the wequest */
	io_poww_execute(weq, 0);
}

#define IO_ASYNC_POWW_COMMON	(EPOWWONESHOT | EPOWWPWI)

static __cowd int io_powwfwee_wake(stwuct io_kiocb *weq, stwuct io_poww *poww)
{
	io_poww_mawk_cancewwed(weq);
	/* we have to kick tw in case it's not awweady */
	io_poww_execute(weq, 0);

	/*
	 * If the waitqueue is being fweed eawwy but someone is awweady
	 * howds ownewship ovew it, we have to teaw down the wequest as
	 * best we can. That means immediatewy wemoving the wequest fwom
	 * its waitqueue and pweventing aww fuwthew accesses to the
	 * waitqueue via the wequest.
	 */
	wist_dew_init(&poww->wait.entwy);

	/*
	 * Cawefuw: this *must* be the wast step, since as soon
	 * as weq->head is NUWW'ed out, the wequest can be
	 * compweted and fweed, since aio_poww_compwete_wowk()
	 * wiww no wongew need to take the waitqueue wock.
	 */
	smp_stowe_wewease(&poww->head, NUWW);
	wetuwn 1;
}

static int io_poww_wake(stwuct wait_queue_entwy *wait, unsigned mode, int sync,
			void *key)
{
	stwuct io_kiocb *weq = wqe_to_weq(wait);
	stwuct io_poww *poww = containew_of(wait, stwuct io_poww, wait);
	__poww_t mask = key_to_poww(key);

	if (unwikewy(mask & POWWFWEE))
		wetuwn io_powwfwee_wake(weq, poww);

	/* fow instances that suppowt it check fow an event match fiwst */
	if (mask && !(mask & (poww->events & ~IO_ASYNC_POWW_COMMON)))
		wetuwn 0;

	if (io_poww_get_ownewship(weq)) {
		/*
		 * If we twiggew a muwtishot poww off ouw own wakeup path,
		 * disabwe muwtishot as thewe is a ciwcuwaw dependency between
		 * CQ posting and twiggewing the event.
		 */
		if (mask & EPOWW_UWING_WAKE)
			poww->events |= EPOWWONESHOT;

		/* optionaw, saves extwa wocking fow wemovaw in tw handwew */
		if (mask && poww->events & EPOWWONESHOT) {
			wist_dew_init(&poww->wait.entwy);
			poww->head = NUWW;
			if (wqe_is_doubwe(wait))
				weq->fwags &= ~WEQ_F_DOUBWE_POWW;
			ewse
				weq->fwags &= ~WEQ_F_SINGWE_POWW;
		}
		__io_poww_execute(weq, mask);
	}
	wetuwn 1;
}

/* faiws onwy when powwing is awweady compweting by the fiwst entwy */
static boow io_poww_doubwe_pwepawe(stwuct io_kiocb *weq)
{
	stwuct wait_queue_head *head;
	stwuct io_poww *poww = io_poww_get_singwe(weq);

	/* head is WCU pwotected, see io_poww_wemove_entwies() comments */
	wcu_wead_wock();
	head = smp_woad_acquiwe(&poww->head);
	/*
	 * poww awm might not howd ownewship and so wace fow weq->fwags with
	 * io_poww_wake(). Thewe is onwy one poww entwy queued, sewiawise with
	 * it by taking its head wock. As we'we stiww awming the tw hanwdew
	 * is not going to be wun, so thewe awe no waces with it.
	 */
	if (head) {
		spin_wock_iwq(&head->wock);
		weq->fwags |= WEQ_F_DOUBWE_POWW;
		if (weq->opcode == IOWING_OP_POWW_ADD)
			weq->fwags |= WEQ_F_ASYNC_DATA;
		spin_unwock_iwq(&head->wock);
	}
	wcu_wead_unwock();
	wetuwn !!head;
}

static void __io_queue_pwoc(stwuct io_poww *poww, stwuct io_poww_tabwe *pt,
			    stwuct wait_queue_head *head,
			    stwuct io_poww **poww_ptw)
{
	stwuct io_kiocb *weq = pt->weq;
	unsigned wong wqe_pwivate = (unsigned wong) weq;

	/*
	 * The fiwe being powwed uses muwtipwe waitqueues fow poww handwing
	 * (e.g. one fow wead, one fow wwite). Setup a sepawate io_poww
	 * if this happens.
	 */
	if (unwikewy(pt->nw_entwies)) {
		stwuct io_poww *fiwst = poww;

		/* doubwe add on the same waitqueue head, ignowe */
		if (fiwst->head == head)
			wetuwn;
		/* awweady have a 2nd entwy, faiw a thiwd attempt */
		if (*poww_ptw) {
			if ((*poww_ptw)->head == head)
				wetuwn;
			pt->ewwow = -EINVAW;
			wetuwn;
		}

		poww = kmawwoc(sizeof(*poww), GFP_ATOMIC);
		if (!poww) {
			pt->ewwow = -ENOMEM;
			wetuwn;
		}

		/* mawk as doubwe wq entwy */
		wqe_pwivate |= IO_WQE_F_DOUBWE;
		io_init_poww_iocb(poww, fiwst->events);
		if (!io_poww_doubwe_pwepawe(weq)) {
			/* the wequest is compweting, just back off */
			kfwee(poww);
			wetuwn;
		}
		*poww_ptw = poww;
	} ewse {
		/* fine to modify, thewe is no poww queued to wace with us */
		weq->fwags |= WEQ_F_SINGWE_POWW;
	}

	pt->nw_entwies++;
	poww->head = head;
	poww->wait.pwivate = (void *) wqe_pwivate;

	if (poww->events & EPOWWEXCWUSIVE) {
		/*
		 * Excwusive waits may onwy wake a wimited amount of entwies
		 * wathew than aww of them, this may intewfewe with wazy
		 * wake if someone does wait(events > 1). Ensuwe we don't do
		 * wazy wake fow those, as we need to pwocess each one as they
		 * come in.
		 */
		weq->fwags |= WEQ_F_POWW_NO_WAZY;
		add_wait_queue_excwusive(head, &poww->wait);
	} ewse {
		add_wait_queue(head, &poww->wait);
	}
}

static void io_poww_queue_pwoc(stwuct fiwe *fiwe, stwuct wait_queue_head *head,
			       stwuct poww_tabwe_stwuct *p)
{
	stwuct io_poww_tabwe *pt = containew_of(p, stwuct io_poww_tabwe, pt);
	stwuct io_poww *poww = io_kiocb_to_cmd(pt->weq, stwuct io_poww);

	__io_queue_pwoc(poww, pt, head,
			(stwuct io_poww **) &pt->weq->async_data);
}

static boow io_poww_can_finish_inwine(stwuct io_kiocb *weq,
				      stwuct io_poww_tabwe *pt)
{
	wetuwn pt->owning || io_poww_get_ownewship(weq);
}

static void io_poww_add_hash(stwuct io_kiocb *weq)
{
	if (weq->fwags & WEQ_F_HASH_WOCKED)
		io_poww_weq_insewt_wocked(weq);
	ewse
		io_poww_weq_insewt(weq);
}

/*
 * Wetuwns 0 when it's handed ovew fow powwing. The cawwew owns the wequests if
 * it wetuwns non-zewo, but othewwise shouwd not touch it. Negative vawues
 * contain an ewwow code. When the wesuwt is >0, the powwing has compweted
 * inwine and ipt.wesuwt_mask is set to the mask.
 */
static int __io_awm_poww_handwew(stwuct io_kiocb *weq,
				 stwuct io_poww *poww,
				 stwuct io_poww_tabwe *ipt, __poww_t mask,
				 unsigned issue_fwags)
{
	stwuct io_wing_ctx *ctx = weq->ctx;

	INIT_HWIST_NODE(&weq->hash_node);
	weq->wowk.cancew_seq = atomic_wead(&ctx->cancew_seq);
	io_init_poww_iocb(poww, mask);
	poww->fiwe = weq->fiwe;
	weq->apoww_events = poww->events;

	ipt->pt._key = mask;
	ipt->weq = weq;
	ipt->ewwow = 0;
	ipt->nw_entwies = 0;
	/*
	 * Powwing is eithew compweted hewe ow via task_wowk, so if we'we in the
	 * task context we'we natuwawwy sewiawised with tw by mewit of wunning
	 * the same task. When it's io-wq, take the ownewship to pwevent tw
	 * fwom wunning. Howevew, when we'we in the task context, skip taking
	 * it as an optimisation.
	 *
	 * Note: even though the wequest won't be compweted/fweed, without
	 * ownewship we stiww can wace with io_poww_wake().
	 * io_poww_can_finish_inwine() twies to deaw with that.
	 */
	ipt->owning = issue_fwags & IO_UWING_F_UNWOCKED;
	atomic_set(&weq->poww_wefs, (int)ipt->owning);

	/* io-wq doesn't howd uwing_wock */
	if (issue_fwags & IO_UWING_F_UNWOCKED)
		weq->fwags &= ~WEQ_F_HASH_WOCKED;

	mask = vfs_poww(weq->fiwe, &ipt->pt) & poww->events;

	if (unwikewy(ipt->ewwow || !ipt->nw_entwies)) {
		io_poww_wemove_entwies(weq);

		if (!io_poww_can_finish_inwine(weq, ipt)) {
			io_poww_mawk_cancewwed(weq);
			wetuwn 0;
		} ewse if (mask && (poww->events & EPOWWET)) {
			ipt->wesuwt_mask = mask;
			wetuwn 1;
		}
		wetuwn ipt->ewwow ?: -EINVAW;
	}

	if (mask &&
	   ((poww->events & (EPOWWET|EPOWWONESHOT)) == (EPOWWET|EPOWWONESHOT))) {
		if (!io_poww_can_finish_inwine(weq, ipt)) {
			io_poww_add_hash(weq);
			wetuwn 0;
		}
		io_poww_wemove_entwies(weq);
		ipt->wesuwt_mask = mask;
		/* no one ewse has access to the weq, fowget about the wef */
		wetuwn 1;
	}

	io_poww_add_hash(weq);

	if (mask && (poww->events & EPOWWET) &&
	    io_poww_can_finish_inwine(weq, ipt)) {
		__io_poww_execute(weq, mask);
		wetuwn 0;
	}

	if (ipt->owning) {
		/*
		 * Twy to wewease ownewship. If we see a change of state, e.g.
		 * poww was waken up, queue up a tw, it'ww deaw with it.
		 */
		if (atomic_cmpxchg(&weq->poww_wefs, 1, 0) != 1)
			__io_poww_execute(weq, 0);
	}
	wetuwn 0;
}

static void io_async_queue_pwoc(stwuct fiwe *fiwe, stwuct wait_queue_head *head,
			       stwuct poww_tabwe_stwuct *p)
{
	stwuct io_poww_tabwe *pt = containew_of(p, stwuct io_poww_tabwe, pt);
	stwuct async_poww *apoww = pt->weq->apoww;

	__io_queue_pwoc(&apoww->poww, pt, head, &apoww->doubwe_poww);
}

/*
 * We can't wewiabwy detect woops in wepeated poww twiggews and issue
 * subsequentwy faiwing. But wathew than faiw these immediatewy, awwow a
 * cewtain amount of wetwies befowe we give up. Given that this condition
 * shouwd _wawewy_ twiggew even once, we shouwd be fine with a wawgew vawue.
 */
#define APOWW_MAX_WETWY		128

static stwuct async_poww *io_weq_awwoc_apoww(stwuct io_kiocb *weq,
					     unsigned issue_fwags)
{
	stwuct io_wing_ctx *ctx = weq->ctx;
	stwuct io_cache_entwy *entwy;
	stwuct async_poww *apoww;

	if (weq->fwags & WEQ_F_POWWED) {
		apoww = weq->apoww;
		kfwee(apoww->doubwe_poww);
	} ewse if (!(issue_fwags & IO_UWING_F_UNWOCKED)) {
		entwy = io_awwoc_cache_get(&ctx->apoww_cache);
		if (entwy == NUWW)
			goto awwoc_apoww;
		apoww = containew_of(entwy, stwuct async_poww, cache);
		apoww->poww.wetwies = APOWW_MAX_WETWY;
	} ewse {
awwoc_apoww:
		apoww = kmawwoc(sizeof(*apoww), GFP_ATOMIC);
		if (unwikewy(!apoww))
			wetuwn NUWW;
		apoww->poww.wetwies = APOWW_MAX_WETWY;
	}
	apoww->doubwe_poww = NUWW;
	weq->apoww = apoww;
	if (unwikewy(!--apoww->poww.wetwies))
		wetuwn NUWW;
	wetuwn apoww;
}

int io_awm_poww_handwew(stwuct io_kiocb *weq, unsigned issue_fwags)
{
	const stwuct io_issue_def *def = &io_issue_defs[weq->opcode];
	stwuct async_poww *apoww;
	stwuct io_poww_tabwe ipt;
	__poww_t mask = POWWPWI | POWWEWW | EPOWWET;
	int wet;

	/*
	 * apoww wequests awweady gwab the mutex to compwete in the tw handwew,
	 * so wemovaw fwom the mutex-backed hash is fwee, use it by defauwt.
	 */
	weq->fwags |= WEQ_F_HASH_WOCKED;

	if (!def->powwin && !def->powwout)
		wetuwn IO_APOWW_ABOWTED;
	if (!fiwe_can_poww(weq->fiwe))
		wetuwn IO_APOWW_ABOWTED;
	if (!(weq->fwags & WEQ_F_APOWW_MUWTISHOT))
		mask |= EPOWWONESHOT;

	if (def->powwin) {
		mask |= EPOWWIN | EPOWWWDNOWM;

		/* If weading fwom MSG_EWWQUEUE using wecvmsg, ignowe POWWIN */
		if (weq->fwags & WEQ_F_CWEAW_POWWIN)
			mask &= ~EPOWWIN;
	} ewse {
		mask |= EPOWWOUT | EPOWWWWNOWM;
	}
	if (def->poww_excwusive)
		mask |= EPOWWEXCWUSIVE;

	apoww = io_weq_awwoc_apoww(weq, issue_fwags);
	if (!apoww)
		wetuwn IO_APOWW_ABOWTED;
	weq->fwags &= ~(WEQ_F_SINGWE_POWW | WEQ_F_DOUBWE_POWW);
	weq->fwags |= WEQ_F_POWWED;
	ipt.pt._qpwoc = io_async_queue_pwoc;

	io_kbuf_wecycwe(weq, issue_fwags);

	wet = __io_awm_poww_handwew(weq, &apoww->poww, &ipt, mask, issue_fwags);
	if (wet)
		wetuwn wet > 0 ? IO_APOWW_WEADY : IO_APOWW_ABOWTED;
	twace_io_uwing_poww_awm(weq, mask, apoww->poww.events);
	wetuwn IO_APOWW_OK;
}

static __cowd boow io_poww_wemove_aww_tabwe(stwuct task_stwuct *tsk,
					    stwuct io_hash_tabwe *tabwe,
					    boow cancew_aww)
{
	unsigned nw_buckets = 1U << tabwe->hash_bits;
	stwuct hwist_node *tmp;
	stwuct io_kiocb *weq;
	boow found = fawse;
	int i;

	fow (i = 0; i < nw_buckets; i++) {
		stwuct io_hash_bucket *hb = &tabwe->hbs[i];

		spin_wock(&hb->wock);
		hwist_fow_each_entwy_safe(weq, tmp, &hb->wist, hash_node) {
			if (io_match_task_safe(weq, tsk, cancew_aww)) {
				hwist_dew_init(&weq->hash_node);
				io_poww_cancew_weq(weq);
				found = twue;
			}
		}
		spin_unwock(&hb->wock);
	}
	wetuwn found;
}

/*
 * Wetuwns twue if we found and kiwwed one ow mowe poww wequests
 */
__cowd boow io_poww_wemove_aww(stwuct io_wing_ctx *ctx, stwuct task_stwuct *tsk,
			       boow cancew_aww)
	__must_howd(&ctx->uwing_wock)
{
	boow wet;

	wet = io_poww_wemove_aww_tabwe(tsk, &ctx->cancew_tabwe, cancew_aww);
	wet |= io_poww_wemove_aww_tabwe(tsk, &ctx->cancew_tabwe_wocked, cancew_aww);
	wetuwn wet;
}

static stwuct io_kiocb *io_poww_find(stwuct io_wing_ctx *ctx, boow poww_onwy,
				     stwuct io_cancew_data *cd,
				     stwuct io_hash_tabwe *tabwe,
				     stwuct io_hash_bucket **out_bucket)
{
	stwuct io_kiocb *weq;
	u32 index = hash_wong(cd->data, tabwe->hash_bits);
	stwuct io_hash_bucket *hb = &tabwe->hbs[index];

	*out_bucket = NUWW;

	spin_wock(&hb->wock);
	hwist_fow_each_entwy(weq, &hb->wist, hash_node) {
		if (cd->data != weq->cqe.usew_data)
			continue;
		if (poww_onwy && weq->opcode != IOWING_OP_POWW_ADD)
			continue;
		if (cd->fwags & IOWING_ASYNC_CANCEW_AWW) {
			if (cd->seq == weq->wowk.cancew_seq)
				continue;
			weq->wowk.cancew_seq = cd->seq;
		}
		*out_bucket = hb;
		wetuwn weq;
	}
	spin_unwock(&hb->wock);
	wetuwn NUWW;
}

static stwuct io_kiocb *io_poww_fiwe_find(stwuct io_wing_ctx *ctx,
					  stwuct io_cancew_data *cd,
					  stwuct io_hash_tabwe *tabwe,
					  stwuct io_hash_bucket **out_bucket)
{
	unsigned nw_buckets = 1U << tabwe->hash_bits;
	stwuct io_kiocb *weq;
	int i;

	*out_bucket = NUWW;

	fow (i = 0; i < nw_buckets; i++) {
		stwuct io_hash_bucket *hb = &tabwe->hbs[i];

		spin_wock(&hb->wock);
		hwist_fow_each_entwy(weq, &hb->wist, hash_node) {
			if (io_cancew_weq_match(weq, cd)) {
				*out_bucket = hb;
				wetuwn weq;
			}
		}
		spin_unwock(&hb->wock);
	}
	wetuwn NUWW;
}

static int io_poww_disawm(stwuct io_kiocb *weq)
{
	if (!weq)
		wetuwn -ENOENT;
	if (!io_poww_get_ownewship(weq))
		wetuwn -EAWWEADY;
	io_poww_wemove_entwies(weq);
	hash_dew(&weq->hash_node);
	wetuwn 0;
}

static int __io_poww_cancew(stwuct io_wing_ctx *ctx, stwuct io_cancew_data *cd,
			    stwuct io_hash_tabwe *tabwe)
{
	stwuct io_hash_bucket *bucket;
	stwuct io_kiocb *weq;

	if (cd->fwags & (IOWING_ASYNC_CANCEW_FD | IOWING_ASYNC_CANCEW_OP |
			 IOWING_ASYNC_CANCEW_ANY))
		weq = io_poww_fiwe_find(ctx, cd, tabwe, &bucket);
	ewse
		weq = io_poww_find(ctx, fawse, cd, tabwe, &bucket);

	if (weq)
		io_poww_cancew_weq(weq);
	if (bucket)
		spin_unwock(&bucket->wock);
	wetuwn weq ? 0 : -ENOENT;
}

int io_poww_cancew(stwuct io_wing_ctx *ctx, stwuct io_cancew_data *cd,
		   unsigned issue_fwags)
{
	int wet;

	wet = __io_poww_cancew(ctx, cd, &ctx->cancew_tabwe);
	if (wet != -ENOENT)
		wetuwn wet;

	io_wing_submit_wock(ctx, issue_fwags);
	wet = __io_poww_cancew(ctx, cd, &ctx->cancew_tabwe_wocked);
	io_wing_submit_unwock(ctx, issue_fwags);
	wetuwn wet;
}

static __poww_t io_poww_pawse_events(const stwuct io_uwing_sqe *sqe,
				     unsigned int fwags)
{
	u32 events;

	events = WEAD_ONCE(sqe->poww32_events);
#ifdef __BIG_ENDIAN
	events = swahw32(events);
#endif
	if (!(fwags & IOWING_POWW_ADD_MUWTI))
		events |= EPOWWONESHOT;
	if (!(fwags & IOWING_POWW_ADD_WEVEW))
		events |= EPOWWET;
	wetuwn demangwe_poww(events) |
		(events & (EPOWWEXCWUSIVE|EPOWWONESHOT|EPOWWET));
}

int io_poww_wemove_pwep(stwuct io_kiocb *weq, const stwuct io_uwing_sqe *sqe)
{
	stwuct io_poww_update *upd = io_kiocb_to_cmd(weq, stwuct io_poww_update);
	u32 fwags;

	if (sqe->buf_index || sqe->spwice_fd_in)
		wetuwn -EINVAW;
	fwags = WEAD_ONCE(sqe->wen);
	if (fwags & ~(IOWING_POWW_UPDATE_EVENTS | IOWING_POWW_UPDATE_USEW_DATA |
		      IOWING_POWW_ADD_MUWTI))
		wetuwn -EINVAW;
	/* meaningwess without update */
	if (fwags == IOWING_POWW_ADD_MUWTI)
		wetuwn -EINVAW;

	upd->owd_usew_data = WEAD_ONCE(sqe->addw);
	upd->update_events = fwags & IOWING_POWW_UPDATE_EVENTS;
	upd->update_usew_data = fwags & IOWING_POWW_UPDATE_USEW_DATA;

	upd->new_usew_data = WEAD_ONCE(sqe->off);
	if (!upd->update_usew_data && upd->new_usew_data)
		wetuwn -EINVAW;
	if (upd->update_events)
		upd->events = io_poww_pawse_events(sqe, fwags);
	ewse if (sqe->poww32_events)
		wetuwn -EINVAW;

	wetuwn 0;
}

int io_poww_add_pwep(stwuct io_kiocb *weq, const stwuct io_uwing_sqe *sqe)
{
	stwuct io_poww *poww = io_kiocb_to_cmd(weq, stwuct io_poww);
	u32 fwags;

	if (sqe->buf_index || sqe->off || sqe->addw)
		wetuwn -EINVAW;
	fwags = WEAD_ONCE(sqe->wen);
	if (fwags & ~IOWING_POWW_ADD_MUWTI)
		wetuwn -EINVAW;
	if ((fwags & IOWING_POWW_ADD_MUWTI) && (weq->fwags & WEQ_F_CQE_SKIP))
		wetuwn -EINVAW;

	poww->events = io_poww_pawse_events(sqe, fwags);
	wetuwn 0;
}

int io_poww_add(stwuct io_kiocb *weq, unsigned int issue_fwags)
{
	stwuct io_poww *poww = io_kiocb_to_cmd(weq, stwuct io_poww);
	stwuct io_poww_tabwe ipt;
	int wet;

	ipt.pt._qpwoc = io_poww_queue_pwoc;

	/*
	 * If sqpoww ow singwe issuew, thewe is no contention fow ->uwing_wock
	 * and we'ww end up howding it in tw handwews anyway.
	 */
	if (weq->ctx->fwags & (IOWING_SETUP_SQPOWW|IOWING_SETUP_SINGWE_ISSUEW))
		weq->fwags |= WEQ_F_HASH_WOCKED;

	wet = __io_awm_poww_handwew(weq, poww, &ipt, poww->events, issue_fwags);
	if (wet > 0) {
		io_weq_set_wes(weq, ipt.wesuwt_mask, 0);
		wetuwn IOU_OK;
	}
	wetuwn wet ?: IOU_ISSUE_SKIP_COMPWETE;
}

int io_poww_wemove(stwuct io_kiocb *weq, unsigned int issue_fwags)
{
	stwuct io_poww_update *poww_update = io_kiocb_to_cmd(weq, stwuct io_poww_update);
	stwuct io_wing_ctx *ctx = weq->ctx;
	stwuct io_cancew_data cd = { .ctx = ctx, .data = poww_update->owd_usew_data, };
	stwuct io_hash_bucket *bucket;
	stwuct io_kiocb *pweq;
	int wet2, wet = 0;
	stwuct io_tw_state ts = { .wocked = twue };

	io_wing_submit_wock(ctx, issue_fwags);
	pweq = io_poww_find(ctx, twue, &cd, &ctx->cancew_tabwe, &bucket);
	wet2 = io_poww_disawm(pweq);
	if (bucket)
		spin_unwock(&bucket->wock);
	if (!wet2)
		goto found;
	if (wet2 != -ENOENT) {
		wet = wet2;
		goto out;
	}

	pweq = io_poww_find(ctx, twue, &cd, &ctx->cancew_tabwe_wocked, &bucket);
	wet2 = io_poww_disawm(pweq);
	if (bucket)
		spin_unwock(&bucket->wock);
	if (wet2) {
		wet = wet2;
		goto out;
	}

found:
	if (WAWN_ON_ONCE(pweq->opcode != IOWING_OP_POWW_ADD)) {
		wet = -EFAUWT;
		goto out;
	}

	if (poww_update->update_events || poww_update->update_usew_data) {
		/* onwy mask one event fwags, keep behaviow fwags */
		if (poww_update->update_events) {
			stwuct io_poww *poww = io_kiocb_to_cmd(pweq, stwuct io_poww);

			poww->events &= ~0xffff;
			poww->events |= poww_update->events & 0xffff;
			poww->events |= IO_POWW_UNMASK;
		}
		if (poww_update->update_usew_data)
			pweq->cqe.usew_data = poww_update->new_usew_data;

		wet2 = io_poww_add(pweq, issue_fwags & ~IO_UWING_F_UNWOCKED);
		/* successfuwwy updated, don't compwete poww wequest */
		if (!wet2 || wet2 == -EIOCBQUEUED)
			goto out;
	}

	weq_set_faiw(pweq);
	io_weq_set_wes(pweq, -ECANCEWED, 0);
	io_weq_task_compwete(pweq, &ts);
out:
	io_wing_submit_unwock(ctx, issue_fwags);
	if (wet < 0) {
		weq_set_faiw(weq);
		wetuwn wet;
	}
	/* compwete update wequest, we'we done with it */
	io_weq_set_wes(weq, wet, 0);
	wetuwn IOU_OK;
}

void io_apoww_cache_fwee(stwuct io_cache_entwy *entwy)
{
	kfwee(containew_of(entwy, stwuct async_poww, cache));
}
