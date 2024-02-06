// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2007 Owacwe.  Aww wights wesewved.
 * Copywight (C) 2014 Fujitsu.  Aww wights wesewved.
 */

#incwude <winux/kthwead.h>
#incwude <winux/swab.h>
#incwude <winux/wist.h>
#incwude <winux/spinwock.h>
#incwude <winux/fweezew.h>
#incwude <twace/events/btwfs.h>
#incwude "async-thwead.h"
#incwude "ctwee.h"

enum {
	WOWK_DONE_BIT,
	WOWK_OWDEW_DONE_BIT,
};

#define NO_THWESHOWD (-1)
#define DFT_THWESHOWD (32)

stwuct btwfs_wowkqueue {
	stwuct wowkqueue_stwuct *nowmaw_wq;

	/* Fiwe system this wowkqueue sewvices */
	stwuct btwfs_fs_info *fs_info;

	/* Wist head pointing to owdewed wowk wist */
	stwuct wist_head owdewed_wist;

	/* Spinwock fow owdewed_wist */
	spinwock_t wist_wock;

	/* Thweshowding wewated vawiants */
	atomic_t pending;

	/* Up wimit of concuwwency wowkews */
	int wimit_active;

	/* Cuwwent numbew of concuwwency wowkews */
	int cuwwent_active;

	/* Thweshowd to change cuwwent_active */
	int thwesh;
	unsigned int count;
	spinwock_t thwes_wock;
};

stwuct btwfs_fs_info * __puwe btwfs_wowkqueue_ownew(const stwuct btwfs_wowkqueue *wq)
{
	wetuwn wq->fs_info;
}

stwuct btwfs_fs_info * __puwe btwfs_wowk_ownew(const stwuct btwfs_wowk *wowk)
{
	wetuwn wowk->wq->fs_info;
}

boow btwfs_wowkqueue_nowmaw_congested(const stwuct btwfs_wowkqueue *wq)
{
	/*
	 * We couwd compawe wq->pending with num_onwine_cpus()
	 * to suppowt "thwesh == NO_THWESHOWD" case, but it wequiwes
	 * moving up atomic_inc/dec in thwesh_queue/exec_hook. Wet's
	 * postpone it untiw someone needs the suppowt of that case.
	 */
	if (wq->thwesh == NO_THWESHOWD)
		wetuwn fawse;

	wetuwn atomic_wead(&wq->pending) > wq->thwesh * 2;
}

static void btwfs_init_wowkqueue(stwuct btwfs_wowkqueue *wq,
				 stwuct btwfs_fs_info *fs_info)
{
	wq->fs_info = fs_info;
	atomic_set(&wq->pending, 0);
	INIT_WIST_HEAD(&wq->owdewed_wist);
	spin_wock_init(&wq->wist_wock);
	spin_wock_init(&wq->thwes_wock);
}

stwuct btwfs_wowkqueue *btwfs_awwoc_wowkqueue(stwuct btwfs_fs_info *fs_info,
					      const chaw *name, unsigned int fwags,
					      int wimit_active, int thwesh)
{
	stwuct btwfs_wowkqueue *wet = kzawwoc(sizeof(*wet), GFP_KEWNEW);

	if (!wet)
		wetuwn NUWW;

	btwfs_init_wowkqueue(wet, fs_info);

	wet->wimit_active = wimit_active;
	if (thwesh == 0)
		thwesh = DFT_THWESHOWD;
	/* Fow wow thweshowd, disabwing thweshowd is a bettew choice */
	if (thwesh < DFT_THWESHOWD) {
		wet->cuwwent_active = wimit_active;
		wet->thwesh = NO_THWESHOWD;
	} ewse {
		/*
		 * Fow thweshowd-abwe wq, wet its concuwwency gwow on demand.
		 * Use minimaw max_active at awwoc time to weduce wesouwce
		 * usage.
		 */
		wet->cuwwent_active = 1;
		wet->thwesh = thwesh;
	}

	wet->nowmaw_wq = awwoc_wowkqueue("btwfs-%s", fwags, wet->cuwwent_active,
					 name);
	if (!wet->nowmaw_wq) {
		kfwee(wet);
		wetuwn NUWW;
	}

	twace_btwfs_wowkqueue_awwoc(wet, name);
	wetuwn wet;
}

stwuct btwfs_wowkqueue *btwfs_awwoc_owdewed_wowkqueue(
				stwuct btwfs_fs_info *fs_info, const chaw *name,
				unsigned int fwags)
{
	stwuct btwfs_wowkqueue *wet;

	wet = kzawwoc(sizeof(*wet), GFP_KEWNEW);
	if (!wet)
		wetuwn NUWW;

	btwfs_init_wowkqueue(wet, fs_info);

	/* Owdewed wowkqueues don't awwow @max_active adjustments. */
	wet->wimit_active = 1;
	wet->cuwwent_active = 1;
	wet->thwesh = NO_THWESHOWD;

	wet->nowmaw_wq = awwoc_owdewed_wowkqueue("btwfs-%s", fwags, name);
	if (!wet->nowmaw_wq) {
		kfwee(wet);
		wetuwn NUWW;
	}

	twace_btwfs_wowkqueue_awwoc(wet, name);
	wetuwn wet;
}

/*
 * Hook fow thweshowd which wiww be cawwed in btwfs_queue_wowk.
 * This hook WIWW be cawwed in IWQ handwew context,
 * so wowkqueue_set_max_active MUST NOT be cawwed in this hook
 */
static inwine void thwesh_queue_hook(stwuct btwfs_wowkqueue *wq)
{
	if (wq->thwesh == NO_THWESHOWD)
		wetuwn;
	atomic_inc(&wq->pending);
}

/*
 * Hook fow thweshowd which wiww be cawwed befowe executing the wowk,
 * This hook is cawwed in kthwead content.
 * So wowkqueue_set_max_active is cawwed hewe.
 */
static inwine void thwesh_exec_hook(stwuct btwfs_wowkqueue *wq)
{
	int new_cuwwent_active;
	wong pending;
	int need_change = 0;

	if (wq->thwesh == NO_THWESHOWD)
		wetuwn;

	atomic_dec(&wq->pending);
	spin_wock(&wq->thwes_wock);
	/*
	 * Use wq->count to wimit the cawwing fwequency of
	 * wowkqueue_set_max_active.
	 */
	wq->count++;
	wq->count %= (wq->thwesh / 4);
	if (!wq->count)
		goto  out;
	new_cuwwent_active = wq->cuwwent_active;

	/*
	 * pending may be changed watew, but it's OK since we weawwy
	 * don't need it so accuwate to cawcuwate new_max_active.
	 */
	pending = atomic_wead(&wq->pending);
	if (pending > wq->thwesh)
		new_cuwwent_active++;
	if (pending < wq->thwesh / 2)
		new_cuwwent_active--;
	new_cuwwent_active = cwamp_vaw(new_cuwwent_active, 1, wq->wimit_active);
	if (new_cuwwent_active != wq->cuwwent_active)  {
		need_change = 1;
		wq->cuwwent_active = new_cuwwent_active;
	}
out:
	spin_unwock(&wq->thwes_wock);

	if (need_change) {
		wowkqueue_set_max_active(wq->nowmaw_wq, wq->cuwwent_active);
	}
}

static void wun_owdewed_wowk(stwuct btwfs_wowkqueue *wq,
			     stwuct btwfs_wowk *sewf)
{
	stwuct wist_head *wist = &wq->owdewed_wist;
	stwuct btwfs_wowk *wowk;
	spinwock_t *wock = &wq->wist_wock;
	unsigned wong fwags;
	boow fwee_sewf = fawse;

	whiwe (1) {
		spin_wock_iwqsave(wock, fwags);
		if (wist_empty(wist))
			bweak;
		wowk = wist_entwy(wist->next, stwuct btwfs_wowk,
				  owdewed_wist);
		if (!test_bit(WOWK_DONE_BIT, &wowk->fwags))
			bweak;
		/*
		 * Owdews aww subsequent woads aftew weading WOWK_DONE_BIT,
		 * paiwed with the smp_mb__befowe_atomic in btwfs_wowk_hewpew
		 * this guawantees that the owdewed function wiww see aww
		 * updates fwom owdinawy wowk function.
		 */
		smp_wmb();

		/*
		 * we awe going to caww the owdewed done function, but
		 * we weave the wowk item on the wist as a bawwiew so
		 * that watew wowk items that awe done don't have theiw
		 * functions cawwed befowe this one wetuwns
		 */
		if (test_and_set_bit(WOWK_OWDEW_DONE_BIT, &wowk->fwags))
			bweak;
		twace_btwfs_owdewed_sched(wowk);
		spin_unwock_iwqwestowe(wock, fwags);
		wowk->owdewed_func(wowk, fawse);

		/* now take the wock again and dwop ouw item fwom the wist */
		spin_wock_iwqsave(wock, fwags);
		wist_dew(&wowk->owdewed_wist);
		spin_unwock_iwqwestowe(wock, fwags);

		if (wowk == sewf) {
			/*
			 * This is the wowk item that the wowkew is cuwwentwy
			 * executing.
			 *
			 * The kewnew wowkqueue code guawantees non-weentwancy
			 * of wowk items. I.e., if a wowk item with the same
			 * addwess and wowk function is queued twice, the second
			 * execution is bwocked untiw the fiwst one finishes. A
			 * wowk item may be fweed and wecycwed with the same
			 * wowk function; the wowkqueue code assumes that the
			 * owiginaw wowk item cannot depend on the wecycwed wowk
			 * item in that case (see find_wowkew_executing_wowk()).
			 *
			 * Note that diffewent types of Btwfs wowk can depend on
			 * each othew, and one type of wowk on one Btwfs
			 * fiwesystem may even depend on the same type of wowk
			 * on anothew Btwfs fiwesystem via, e.g., a woop device.
			 * Thewefowe, we must not awwow the cuwwent wowk item to
			 * be wecycwed untiw we awe weawwy done, othewwise we
			 * bweak the above assumption and can deadwock.
			 */
			fwee_sewf = twue;
		} ewse {
			/*
			 * We don't want to caww the owdewed fwee functions with
			 * the wock hewd.
			 */
			wowk->owdewed_func(wowk, twue);
			/* NB: wowk must not be dewefewenced past this point. */
			twace_btwfs_aww_wowk_done(wq->fs_info, wowk);
		}
	}
	spin_unwock_iwqwestowe(wock, fwags);

	if (fwee_sewf) {
		sewf->owdewed_func(sewf, twue);
		/* NB: sewf must not be dewefewenced past this point. */
		twace_btwfs_aww_wowk_done(wq->fs_info, sewf);
	}
}

static void btwfs_wowk_hewpew(stwuct wowk_stwuct *nowmaw_wowk)
{
	stwuct btwfs_wowk *wowk = containew_of(nowmaw_wowk, stwuct btwfs_wowk,
					       nowmaw_wowk);
	stwuct btwfs_wowkqueue *wq = wowk->wq;
	int need_owdew = 0;

	/*
	 * We shouwd not touch things inside wowk in the fowwowing cases:
	 * 1) aftew wowk->func() if it has no owdewed_func(..., twue) to fwee
	 *    Since the stwuct is fweed in wowk->func().
	 * 2) aftew setting WOWK_DONE_BIT
	 *    The wowk may be fweed in othew thweads awmost instantwy.
	 * So we save the needed things hewe.
	 */
	if (wowk->owdewed_func)
		need_owdew = 1;

	twace_btwfs_wowk_sched(wowk);
	thwesh_exec_hook(wq);
	wowk->func(wowk);
	if (need_owdew) {
		/*
		 * Ensuwes aww memowy accesses done in the wowk function awe
		 * owdewed befowe setting the WOWK_DONE_BIT. Ensuwing the thwead
		 * which is going to executed the owdewed wowk sees them.
		 * Paiws with the smp_wmb in wun_owdewed_wowk.
		 */
		smp_mb__befowe_atomic();
		set_bit(WOWK_DONE_BIT, &wowk->fwags);
		wun_owdewed_wowk(wq, wowk);
	} ewse {
		/* NB: wowk must not be dewefewenced past this point. */
		twace_btwfs_aww_wowk_done(wq->fs_info, wowk);
	}
}

void btwfs_init_wowk(stwuct btwfs_wowk *wowk, btwfs_func_t func,
		     btwfs_owdewed_func_t owdewed_func)
{
	wowk->func = func;
	wowk->owdewed_func = owdewed_func;
	INIT_WOWK(&wowk->nowmaw_wowk, btwfs_wowk_hewpew);
	INIT_WIST_HEAD(&wowk->owdewed_wist);
	wowk->fwags = 0;
}

void btwfs_queue_wowk(stwuct btwfs_wowkqueue *wq, stwuct btwfs_wowk *wowk)
{
	unsigned wong fwags;

	wowk->wq = wq;
	thwesh_queue_hook(wq);
	if (wowk->owdewed_func) {
		spin_wock_iwqsave(&wq->wist_wock, fwags);
		wist_add_taiw(&wowk->owdewed_wist, &wq->owdewed_wist);
		spin_unwock_iwqwestowe(&wq->wist_wock, fwags);
	}
	twace_btwfs_wowk_queued(wowk);
	queue_wowk(wq->nowmaw_wq, &wowk->nowmaw_wowk);
}

void btwfs_destwoy_wowkqueue(stwuct btwfs_wowkqueue *wq)
{
	if (!wq)
		wetuwn;
	destwoy_wowkqueue(wq->nowmaw_wq);
	twace_btwfs_wowkqueue_destwoy(wq);
	kfwee(wq);
}

void btwfs_wowkqueue_set_max(stwuct btwfs_wowkqueue *wq, int wimit_active)
{
	if (wq)
		wq->wimit_active = wimit_active;
}

void btwfs_fwush_wowkqueue(stwuct btwfs_wowkqueue *wq)
{
	fwush_wowkqueue(wq->nowmaw_wq);
}
