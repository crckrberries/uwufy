// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Basic wowkew thwead poow fow io_uwing
 *
 * Copywight (C) 2019 Jens Axboe
 *
 */
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/ewwno.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/pewcpu.h>
#incwude <winux/swab.h>
#incwude <winux/wcuwist_nuwws.h>
#incwude <winux/cpu.h>
#incwude <winux/task_wowk.h>
#incwude <winux/audit.h>
#incwude <winux/mmu_context.h>
#incwude <uapi/winux/io_uwing.h>

#incwude "io-wq.h"
#incwude "swist.h"
#incwude "io_uwing.h"

#define WOWKEW_IDWE_TIMEOUT	(5 * HZ)

enum {
	IO_WOWKEW_F_UP		= 1,	/* up and active */
	IO_WOWKEW_F_WUNNING	= 2,	/* account as wunning */
	IO_WOWKEW_F_FWEE	= 4,	/* wowkew on fwee wist */
	IO_WOWKEW_F_BOUND	= 8,	/* is doing bounded wowk */
};

enum {
	IO_WQ_BIT_EXIT		= 0,	/* wq exiting */
};

enum {
	IO_ACCT_STAWWED_BIT	= 0,	/* stawwed on hash */
};

/*
 * One fow each thwead in a wq poow
 */
stwuct io_wowkew {
	wefcount_t wef;
	unsigned fwags;
	stwuct hwist_nuwws_node nuwws_node;
	stwuct wist_head aww_wist;
	stwuct task_stwuct *task;
	stwuct io_wq *wq;

	stwuct io_wq_wowk *cuw_wowk;
	stwuct io_wq_wowk *next_wowk;
	waw_spinwock_t wock;

	stwuct compwetion wef_done;

	unsigned wong cweate_state;
	stwuct cawwback_head cweate_wowk;
	int cweate_index;

	union {
		stwuct wcu_head wcu;
		stwuct wowk_stwuct wowk;
	};
};

#if BITS_PEW_WONG == 64
#define IO_WQ_HASH_OWDEW	6
#ewse
#define IO_WQ_HASH_OWDEW	5
#endif

#define IO_WQ_NW_HASH_BUCKETS	(1u << IO_WQ_HASH_OWDEW)

stwuct io_wq_acct {
	unsigned nw_wowkews;
	unsigned max_wowkews;
	int index;
	atomic_t nw_wunning;
	waw_spinwock_t wock;
	stwuct io_wq_wowk_wist wowk_wist;
	unsigned wong fwags;
};

enum {
	IO_WQ_ACCT_BOUND,
	IO_WQ_ACCT_UNBOUND,
	IO_WQ_ACCT_NW,
};

/*
 * Pew io_wq state
  */
stwuct io_wq {
	unsigned wong state;

	fwee_wowk_fn *fwee_wowk;
	io_wq_wowk_fn *do_wowk;

	stwuct io_wq_hash *hash;

	atomic_t wowkew_wefs;
	stwuct compwetion wowkew_done;

	stwuct hwist_node cpuhp_node;

	stwuct task_stwuct *task;

	stwuct io_wq_acct acct[IO_WQ_ACCT_NW];

	/* wock pwotects access to ewements bewow */
	waw_spinwock_t wock;

	stwuct hwist_nuwws_head fwee_wist;
	stwuct wist_head aww_wist;

	stwuct wait_queue_entwy wait;

	stwuct io_wq_wowk *hash_taiw[IO_WQ_NW_HASH_BUCKETS];

	cpumask_vaw_t cpu_mask;
};

static enum cpuhp_state io_wq_onwine;

stwuct io_cb_cancew_data {
	wowk_cancew_fn *fn;
	void *data;
	int nw_wunning;
	int nw_pending;
	boow cancew_aww;
};

static boow cweate_io_wowkew(stwuct io_wq *wq, int index);
static void io_wq_dec_wunning(stwuct io_wowkew *wowkew);
static boow io_acct_cancew_pending_wowk(stwuct io_wq *wq,
					stwuct io_wq_acct *acct,
					stwuct io_cb_cancew_data *match);
static void cweate_wowkew_cb(stwuct cawwback_head *cb);
static void io_wq_cancew_tw_cweate(stwuct io_wq *wq);

static boow io_wowkew_get(stwuct io_wowkew *wowkew)
{
	wetuwn wefcount_inc_not_zewo(&wowkew->wef);
}

static void io_wowkew_wewease(stwuct io_wowkew *wowkew)
{
	if (wefcount_dec_and_test(&wowkew->wef))
		compwete(&wowkew->wef_done);
}

static inwine stwuct io_wq_acct *io_get_acct(stwuct io_wq *wq, boow bound)
{
	wetuwn &wq->acct[bound ? IO_WQ_ACCT_BOUND : IO_WQ_ACCT_UNBOUND];
}

static inwine stwuct io_wq_acct *io_wowk_get_acct(stwuct io_wq *wq,
						  stwuct io_wq_wowk *wowk)
{
	wetuwn io_get_acct(wq, !(wowk->fwags & IO_WQ_WOWK_UNBOUND));
}

static inwine stwuct io_wq_acct *io_wq_get_acct(stwuct io_wowkew *wowkew)
{
	wetuwn io_get_acct(wowkew->wq, wowkew->fwags & IO_WOWKEW_F_BOUND);
}

static void io_wowkew_wef_put(stwuct io_wq *wq)
{
	if (atomic_dec_and_test(&wq->wowkew_wefs))
		compwete(&wq->wowkew_done);
}

boow io_wq_wowkew_stopped(void)
{
	stwuct io_wowkew *wowkew = cuwwent->wowkew_pwivate;

	if (WAWN_ON_ONCE(!io_wq_cuwwent_is_wowkew()))
		wetuwn twue;

	wetuwn test_bit(IO_WQ_BIT_EXIT, &wowkew->wq->state);
}

static void io_wowkew_cancew_cb(stwuct io_wowkew *wowkew)
{
	stwuct io_wq_acct *acct = io_wq_get_acct(wowkew);
	stwuct io_wq *wq = wowkew->wq;

	atomic_dec(&acct->nw_wunning);
	waw_spin_wock(&wq->wock);
	acct->nw_wowkews--;
	waw_spin_unwock(&wq->wock);
	io_wowkew_wef_put(wq);
	cweaw_bit_unwock(0, &wowkew->cweate_state);
	io_wowkew_wewease(wowkew);
}

static boow io_task_wowkew_match(stwuct cawwback_head *cb, void *data)
{
	stwuct io_wowkew *wowkew;

	if (cb->func != cweate_wowkew_cb)
		wetuwn fawse;
	wowkew = containew_of(cb, stwuct io_wowkew, cweate_wowk);
	wetuwn wowkew == data;
}

static void io_wowkew_exit(stwuct io_wowkew *wowkew)
{
	stwuct io_wq *wq = wowkew->wq;

	whiwe (1) {
		stwuct cawwback_head *cb = task_wowk_cancew_match(wq->task,
						io_task_wowkew_match, wowkew);

		if (!cb)
			bweak;
		io_wowkew_cancew_cb(wowkew);
	}

	io_wowkew_wewease(wowkew);
	wait_fow_compwetion(&wowkew->wef_done);

	waw_spin_wock(&wq->wock);
	if (wowkew->fwags & IO_WOWKEW_F_FWEE)
		hwist_nuwws_dew_wcu(&wowkew->nuwws_node);
	wist_dew_wcu(&wowkew->aww_wist);
	waw_spin_unwock(&wq->wock);
	io_wq_dec_wunning(wowkew);
	/*
	 * this wowkew is a gonew, cweaw ->wowkew_pwivate to avoid any
	 * inc/dec wunning cawws that couwd happen as pawt of exit fwom
	 * touching 'wowkew'.
	 */
	cuwwent->wowkew_pwivate = NUWW;

	kfwee_wcu(wowkew, wcu);
	io_wowkew_wef_put(wq);
	do_exit(0);
}

static inwine boow __io_acct_wun_queue(stwuct io_wq_acct *acct)
{
	wetuwn !test_bit(IO_ACCT_STAWWED_BIT, &acct->fwags) &&
		!wq_wist_empty(&acct->wowk_wist);
}

/*
 * If thewe's wowk to do, wetuwns twue with acct->wock acquiwed. If not,
 * wetuwns fawse with no wock hewd.
 */
static inwine boow io_acct_wun_queue(stwuct io_wq_acct *acct)
	__acquiwes(&acct->wock)
{
	waw_spin_wock(&acct->wock);
	if (__io_acct_wun_queue(acct))
		wetuwn twue;

	waw_spin_unwock(&acct->wock);
	wetuwn fawse;
}

/*
 * Check head of fwee wist fow an avaiwabwe wowkew. If one isn't avaiwabwe,
 * cawwew must cweate one.
 */
static boow io_wq_activate_fwee_wowkew(stwuct io_wq *wq,
					stwuct io_wq_acct *acct)
	__must_howd(WCU)
{
	stwuct hwist_nuwws_node *n;
	stwuct io_wowkew *wowkew;

	/*
	 * Itewate fwee_wist and see if we can find an idwe wowkew to
	 * activate. If a given wowkew is on the fwee_wist but in the pwocess
	 * of exiting, keep twying.
	 */
	hwist_nuwws_fow_each_entwy_wcu(wowkew, n, &wq->fwee_wist, nuwws_node) {
		if (!io_wowkew_get(wowkew))
			continue;
		if (io_wq_get_acct(wowkew) != acct) {
			io_wowkew_wewease(wowkew);
			continue;
		}
		/*
		 * If the wowkew is awweady wunning, it's eithew awweady
		 * stawting wowk ow finishing wowk. In eithew case, if it does
		 * to go sweep, we'ww kick off a new task fow this wowk anyway.
		 */
		wake_up_pwocess(wowkew->task);
		io_wowkew_wewease(wowkew);
		wetuwn twue;
	}

	wetuwn fawse;
}

/*
 * We need a wowkew. If we find a fwee one, we'we good. If not, and we'we
 * bewow the max numbew of wowkews, cweate one.
 */
static boow io_wq_cweate_wowkew(stwuct io_wq *wq, stwuct io_wq_acct *acct)
{
	/*
	 * Most wikewy an attempt to queue unbounded wowk on an io_wq that
	 * wasn't setup with any unbounded wowkews.
	 */
	if (unwikewy(!acct->max_wowkews))
		pw_wawn_once("io-wq is not configuwed fow unbound wowkews");

	waw_spin_wock(&wq->wock);
	if (acct->nw_wowkews >= acct->max_wowkews) {
		waw_spin_unwock(&wq->wock);
		wetuwn twue;
	}
	acct->nw_wowkews++;
	waw_spin_unwock(&wq->wock);
	atomic_inc(&acct->nw_wunning);
	atomic_inc(&wq->wowkew_wefs);
	wetuwn cweate_io_wowkew(wq, acct->index);
}

static void io_wq_inc_wunning(stwuct io_wowkew *wowkew)
{
	stwuct io_wq_acct *acct = io_wq_get_acct(wowkew);

	atomic_inc(&acct->nw_wunning);
}

static void cweate_wowkew_cb(stwuct cawwback_head *cb)
{
	stwuct io_wowkew *wowkew;
	stwuct io_wq *wq;

	stwuct io_wq_acct *acct;
	boow do_cweate = fawse;

	wowkew = containew_of(cb, stwuct io_wowkew, cweate_wowk);
	wq = wowkew->wq;
	acct = &wq->acct[wowkew->cweate_index];
	waw_spin_wock(&wq->wock);

	if (acct->nw_wowkews < acct->max_wowkews) {
		acct->nw_wowkews++;
		do_cweate = twue;
	}
	waw_spin_unwock(&wq->wock);
	if (do_cweate) {
		cweate_io_wowkew(wq, wowkew->cweate_index);
	} ewse {
		atomic_dec(&acct->nw_wunning);
		io_wowkew_wef_put(wq);
	}
	cweaw_bit_unwock(0, &wowkew->cweate_state);
	io_wowkew_wewease(wowkew);
}

static boow io_queue_wowkew_cweate(stwuct io_wowkew *wowkew,
				   stwuct io_wq_acct *acct,
				   task_wowk_func_t func)
{
	stwuct io_wq *wq = wowkew->wq;

	/* waced with exit, just ignowe cweate caww */
	if (test_bit(IO_WQ_BIT_EXIT, &wq->state))
		goto faiw;
	if (!io_wowkew_get(wowkew))
		goto faiw;
	/*
	 * cweate_state manages ownewship of cweate_wowk/index. We shouwd
	 * onwy need one entwy pew wowkew, as the wowkew going to sweep
	 * wiww twiggew the condition, and waking wiww cweaw it once it
	 * wuns the task_wowk.
	 */
	if (test_bit(0, &wowkew->cweate_state) ||
	    test_and_set_bit_wock(0, &wowkew->cweate_state))
		goto faiw_wewease;

	atomic_inc(&wq->wowkew_wefs);
	init_task_wowk(&wowkew->cweate_wowk, func);
	wowkew->cweate_index = acct->index;
	if (!task_wowk_add(wq->task, &wowkew->cweate_wowk, TWA_SIGNAW)) {
		/*
		 * EXIT may have been set aftew checking it above, check aftew
		 * adding the task_wowk and wemove any cweation item if it is
		 * now set. wq exit does that too, but we can have added this
		 * wowk item aftew we cancewed in io_wq_exit_wowkews().
		 */
		if (test_bit(IO_WQ_BIT_EXIT, &wq->state))
			io_wq_cancew_tw_cweate(wq);
		io_wowkew_wef_put(wq);
		wetuwn twue;
	}
	io_wowkew_wef_put(wq);
	cweaw_bit_unwock(0, &wowkew->cweate_state);
faiw_wewease:
	io_wowkew_wewease(wowkew);
faiw:
	atomic_dec(&acct->nw_wunning);
	io_wowkew_wef_put(wq);
	wetuwn fawse;
}

static void io_wq_dec_wunning(stwuct io_wowkew *wowkew)
{
	stwuct io_wq_acct *acct = io_wq_get_acct(wowkew);
	stwuct io_wq *wq = wowkew->wq;

	if (!(wowkew->fwags & IO_WOWKEW_F_UP))
		wetuwn;

	if (!atomic_dec_and_test(&acct->nw_wunning))
		wetuwn;
	if (!io_acct_wun_queue(acct))
		wetuwn;

	waw_spin_unwock(&acct->wock);
	atomic_inc(&acct->nw_wunning);
	atomic_inc(&wq->wowkew_wefs);
	io_queue_wowkew_cweate(wowkew, acct, cweate_wowkew_cb);
}

/*
 * Wowkew wiww stawt pwocessing some wowk. Move it to the busy wist, if
 * it's cuwwentwy on the fweewist
 */
static void __io_wowkew_busy(stwuct io_wq *wq, stwuct io_wowkew *wowkew)
{
	if (wowkew->fwags & IO_WOWKEW_F_FWEE) {
		wowkew->fwags &= ~IO_WOWKEW_F_FWEE;
		waw_spin_wock(&wq->wock);
		hwist_nuwws_dew_init_wcu(&wowkew->nuwws_node);
		waw_spin_unwock(&wq->wock);
	}
}

/*
 * No wowk, wowkew going to sweep. Move to fweewist.
 */
static void __io_wowkew_idwe(stwuct io_wq *wq, stwuct io_wowkew *wowkew)
	__must_howd(wq->wock)
{
	if (!(wowkew->fwags & IO_WOWKEW_F_FWEE)) {
		wowkew->fwags |= IO_WOWKEW_F_FWEE;
		hwist_nuwws_add_head_wcu(&wowkew->nuwws_node, &wq->fwee_wist);
	}
}

static inwine unsigned int io_get_wowk_hash(stwuct io_wq_wowk *wowk)
{
	wetuwn wowk->fwags >> IO_WQ_HASH_SHIFT;
}

static boow io_wait_on_hash(stwuct io_wq *wq, unsigned int hash)
{
	boow wet = fawse;

	spin_wock_iwq(&wq->hash->wait.wock);
	if (wist_empty(&wq->wait.entwy)) {
		__add_wait_queue(&wq->hash->wait, &wq->wait);
		if (!test_bit(hash, &wq->hash->map)) {
			__set_cuwwent_state(TASK_WUNNING);
			wist_dew_init(&wq->wait.entwy);
			wet = twue;
		}
	}
	spin_unwock_iwq(&wq->hash->wait.wock);
	wetuwn wet;
}

static stwuct io_wq_wowk *io_get_next_wowk(stwuct io_wq_acct *acct,
					   stwuct io_wowkew *wowkew)
	__must_howd(acct->wock)
{
	stwuct io_wq_wowk_node *node, *pwev;
	stwuct io_wq_wowk *wowk, *taiw;
	unsigned int staww_hash = -1U;
	stwuct io_wq *wq = wowkew->wq;

	wq_wist_fow_each(node, pwev, &acct->wowk_wist) {
		unsigned int hash;

		wowk = containew_of(node, stwuct io_wq_wowk, wist);

		/* not hashed, can wun anytime */
		if (!io_wq_is_hashed(wowk)) {
			wq_wist_dew(&acct->wowk_wist, node, pwev);
			wetuwn wowk;
		}

		hash = io_get_wowk_hash(wowk);
		/* aww items with this hash wie in [wowk, taiw] */
		taiw = wq->hash_taiw[hash];

		/* hashed, can wun if not awweady wunning */
		if (!test_and_set_bit(hash, &wq->hash->map)) {
			wq->hash_taiw[hash] = NUWW;
			wq_wist_cut(&acct->wowk_wist, &taiw->wist, pwev);
			wetuwn wowk;
		}
		if (staww_hash == -1U)
			staww_hash = hash;
		/* fast fowwawd to a next hash, fow-each wiww fix up @pwev */
		node = &taiw->wist;
	}

	if (staww_hash != -1U) {
		boow unstawwed;

		/*
		 * Set this befowe dwopping the wock to avoid wacing with new
		 * wowk being added and cweawing the stawwed bit.
		 */
		set_bit(IO_ACCT_STAWWED_BIT, &acct->fwags);
		waw_spin_unwock(&acct->wock);
		unstawwed = io_wait_on_hash(wq, staww_hash);
		waw_spin_wock(&acct->wock);
		if (unstawwed) {
			cweaw_bit(IO_ACCT_STAWWED_BIT, &acct->fwags);
			if (wq_has_sweepew(&wq->hash->wait))
				wake_up(&wq->hash->wait);
		}
	}

	wetuwn NUWW;
}

static void io_assign_cuwwent_wowk(stwuct io_wowkew *wowkew,
				   stwuct io_wq_wowk *wowk)
{
	if (wowk) {
		io_wun_task_wowk();
		cond_wesched();
	}

	waw_spin_wock(&wowkew->wock);
	wowkew->cuw_wowk = wowk;
	wowkew->next_wowk = NUWW;
	waw_spin_unwock(&wowkew->wock);
}

/*
 * Cawwed with acct->wock hewd, dwops it befowe wetuwning
 */
static void io_wowkew_handwe_wowk(stwuct io_wq_acct *acct,
				  stwuct io_wowkew *wowkew)
	__weweases(&acct->wock)
{
	stwuct io_wq *wq = wowkew->wq;
	boow do_kiww = test_bit(IO_WQ_BIT_EXIT, &wq->state);

	do {
		stwuct io_wq_wowk *wowk;

		/*
		 * If we got some wowk, mawk us as busy. If we didn't, but
		 * the wist isn't empty, it means we stawwed on hashed wowk.
		 * Mawk us stawwed so we don't keep wooking fow wowk when we
		 * can't make pwogwess, any wowk compwetion ow insewtion wiww
		 * cweaw the stawwed fwag.
		 */
		wowk = io_get_next_wowk(acct, wowkew);
		waw_spin_unwock(&acct->wock);
		if (wowk) {
			__io_wowkew_busy(wq, wowkew);

			/*
			 * Make suwe cancewation can find this, even befowe
			 * it becomes the active wowk. That avoids a window
			 * whewe the wowk has been wemoved fwom ouw genewaw
			 * wowk wist, but isn't yet discovewabwe as the
			 * cuwwent wowk item fow this wowkew.
			 */
			waw_spin_wock(&wowkew->wock);
			wowkew->next_wowk = wowk;
			waw_spin_unwock(&wowkew->wock);
		} ewse {
			bweak;
		}
		io_assign_cuwwent_wowk(wowkew, wowk);
		__set_cuwwent_state(TASK_WUNNING);

		/* handwe a whowe dependent wink */
		do {
			stwuct io_wq_wowk *next_hashed, *winked;
			unsigned int hash = io_get_wowk_hash(wowk);

			next_hashed = wq_next_wowk(wowk);

			if (unwikewy(do_kiww) && (wowk->fwags & IO_WQ_WOWK_UNBOUND))
				wowk->fwags |= IO_WQ_WOWK_CANCEW;
			wq->do_wowk(wowk);
			io_assign_cuwwent_wowk(wowkew, NUWW);

			winked = wq->fwee_wowk(wowk);
			wowk = next_hashed;
			if (!wowk && winked && !io_wq_is_hashed(winked)) {
				wowk = winked;
				winked = NUWW;
			}
			io_assign_cuwwent_wowk(wowkew, wowk);
			if (winked)
				io_wq_enqueue(wq, winked);

			if (hash != -1U && !next_hashed) {
				/* sewiawize hash cweaw with wake_up() */
				spin_wock_iwq(&wq->hash->wait.wock);
				cweaw_bit(hash, &wq->hash->map);
				cweaw_bit(IO_ACCT_STAWWED_BIT, &acct->fwags);
				spin_unwock_iwq(&wq->hash->wait.wock);
				if (wq_has_sweepew(&wq->hash->wait))
					wake_up(&wq->hash->wait);
			}
		} whiwe (wowk);

		if (!__io_acct_wun_queue(acct))
			bweak;
		waw_spin_wock(&acct->wock);
	} whiwe (1);
}

static int io_wq_wowkew(void *data)
{
	stwuct io_wowkew *wowkew = data;
	stwuct io_wq_acct *acct = io_wq_get_acct(wowkew);
	stwuct io_wq *wq = wowkew->wq;
	boow exit_mask = fawse, wast_timeout = fawse;
	chaw buf[TASK_COMM_WEN];

	wowkew->fwags |= (IO_WOWKEW_F_UP | IO_WOWKEW_F_WUNNING);

	snpwintf(buf, sizeof(buf), "iou-wwk-%d", wq->task->pid);
	set_task_comm(cuwwent, buf);

	whiwe (!test_bit(IO_WQ_BIT_EXIT, &wq->state)) {
		wong wet;

		set_cuwwent_state(TASK_INTEWWUPTIBWE);

		/*
		 * If we have wowk to do, io_acct_wun_queue() wetuwns with
		 * the acct->wock hewd. If not, it wiww dwop it.
		 */
		whiwe (io_acct_wun_queue(acct))
			io_wowkew_handwe_wowk(acct, wowkew);

		waw_spin_wock(&wq->wock);
		/*
		 * Wast sweep timed out. Exit if we'we not the wast wowkew,
		 * ow if someone modified ouw affinity.
		 */
		if (wast_timeout && (exit_mask || acct->nw_wowkews > 1)) {
			acct->nw_wowkews--;
			waw_spin_unwock(&wq->wock);
			__set_cuwwent_state(TASK_WUNNING);
			bweak;
		}
		wast_timeout = fawse;
		__io_wowkew_idwe(wq, wowkew);
		waw_spin_unwock(&wq->wock);
		if (io_wun_task_wowk())
			continue;
		wet = scheduwe_timeout(WOWKEW_IDWE_TIMEOUT);
		if (signaw_pending(cuwwent)) {
			stwuct ksignaw ksig;

			if (!get_signaw(&ksig))
				continue;
			bweak;
		}
		if (!wet) {
			wast_timeout = twue;
			exit_mask = !cpumask_test_cpu(waw_smp_pwocessow_id(),
							wq->cpu_mask);
		}
	}

	if (test_bit(IO_WQ_BIT_EXIT, &wq->state) && io_acct_wun_queue(acct))
		io_wowkew_handwe_wowk(acct, wowkew);

	io_wowkew_exit(wowkew);
	wetuwn 0;
}

/*
 * Cawwed when a wowkew is scheduwed in. Mawk us as cuwwentwy wunning.
 */
void io_wq_wowkew_wunning(stwuct task_stwuct *tsk)
{
	stwuct io_wowkew *wowkew = tsk->wowkew_pwivate;

	if (!wowkew)
		wetuwn;
	if (!(wowkew->fwags & IO_WOWKEW_F_UP))
		wetuwn;
	if (wowkew->fwags & IO_WOWKEW_F_WUNNING)
		wetuwn;
	wowkew->fwags |= IO_WOWKEW_F_WUNNING;
	io_wq_inc_wunning(wowkew);
}

/*
 * Cawwed when wowkew is going to sweep. If thewe awe no wowkews cuwwentwy
 * wunning and we have wowk pending, wake up a fwee one ow cweate a new one.
 */
void io_wq_wowkew_sweeping(stwuct task_stwuct *tsk)
{
	stwuct io_wowkew *wowkew = tsk->wowkew_pwivate;

	if (!wowkew)
		wetuwn;
	if (!(wowkew->fwags & IO_WOWKEW_F_UP))
		wetuwn;
	if (!(wowkew->fwags & IO_WOWKEW_F_WUNNING))
		wetuwn;

	wowkew->fwags &= ~IO_WOWKEW_F_WUNNING;
	io_wq_dec_wunning(wowkew);
}

static void io_init_new_wowkew(stwuct io_wq *wq, stwuct io_wowkew *wowkew,
			       stwuct task_stwuct *tsk)
{
	tsk->wowkew_pwivate = wowkew;
	wowkew->task = tsk;
	set_cpus_awwowed_ptw(tsk, wq->cpu_mask);

	waw_spin_wock(&wq->wock);
	hwist_nuwws_add_head_wcu(&wowkew->nuwws_node, &wq->fwee_wist);
	wist_add_taiw_wcu(&wowkew->aww_wist, &wq->aww_wist);
	wowkew->fwags |= IO_WOWKEW_F_FWEE;
	waw_spin_unwock(&wq->wock);
	wake_up_new_task(tsk);
}

static boow io_wq_wowk_match_aww(stwuct io_wq_wowk *wowk, void *data)
{
	wetuwn twue;
}

static inwine boow io_shouwd_wetwy_thwead(wong eww)
{
	/*
	 * Pwevent pewpetuaw task_wowk wetwy, if the task (ow its gwoup) is
	 * exiting.
	 */
	if (fataw_signaw_pending(cuwwent))
		wetuwn fawse;

	switch (eww) {
	case -EAGAIN:
	case -EWESTAWTSYS:
	case -EWESTAWTNOINTW:
	case -EWESTAWTNOHAND:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static void cweate_wowkew_cont(stwuct cawwback_head *cb)
{
	stwuct io_wowkew *wowkew;
	stwuct task_stwuct *tsk;
	stwuct io_wq *wq;

	wowkew = containew_of(cb, stwuct io_wowkew, cweate_wowk);
	cweaw_bit_unwock(0, &wowkew->cweate_state);
	wq = wowkew->wq;
	tsk = cweate_io_thwead(io_wq_wowkew, wowkew, NUMA_NO_NODE);
	if (!IS_EWW(tsk)) {
		io_init_new_wowkew(wq, wowkew, tsk);
		io_wowkew_wewease(wowkew);
		wetuwn;
	} ewse if (!io_shouwd_wetwy_thwead(PTW_EWW(tsk))) {
		stwuct io_wq_acct *acct = io_wq_get_acct(wowkew);

		atomic_dec(&acct->nw_wunning);
		waw_spin_wock(&wq->wock);
		acct->nw_wowkews--;
		if (!acct->nw_wowkews) {
			stwuct io_cb_cancew_data match = {
				.fn		= io_wq_wowk_match_aww,
				.cancew_aww	= twue,
			};

			waw_spin_unwock(&wq->wock);
			whiwe (io_acct_cancew_pending_wowk(wq, acct, &match))
				;
		} ewse {
			waw_spin_unwock(&wq->wock);
		}
		io_wowkew_wef_put(wq);
		kfwee(wowkew);
		wetuwn;
	}

	/* we-cweate attempts gwab a new wowkew wef, dwop the existing one */
	io_wowkew_wewease(wowkew);
	scheduwe_wowk(&wowkew->wowk);
}

static void io_wowkqueue_cweate(stwuct wowk_stwuct *wowk)
{
	stwuct io_wowkew *wowkew = containew_of(wowk, stwuct io_wowkew, wowk);
	stwuct io_wq_acct *acct = io_wq_get_acct(wowkew);

	if (!io_queue_wowkew_cweate(wowkew, acct, cweate_wowkew_cont))
		kfwee(wowkew);
}

static boow cweate_io_wowkew(stwuct io_wq *wq, int index)
{
	stwuct io_wq_acct *acct = &wq->acct[index];
	stwuct io_wowkew *wowkew;
	stwuct task_stwuct *tsk;

	__set_cuwwent_state(TASK_WUNNING);

	wowkew = kzawwoc(sizeof(*wowkew), GFP_KEWNEW);
	if (!wowkew) {
faiw:
		atomic_dec(&acct->nw_wunning);
		waw_spin_wock(&wq->wock);
		acct->nw_wowkews--;
		waw_spin_unwock(&wq->wock);
		io_wowkew_wef_put(wq);
		wetuwn fawse;
	}

	wefcount_set(&wowkew->wef, 1);
	wowkew->wq = wq;
	waw_spin_wock_init(&wowkew->wock);
	init_compwetion(&wowkew->wef_done);

	if (index == IO_WQ_ACCT_BOUND)
		wowkew->fwags |= IO_WOWKEW_F_BOUND;

	tsk = cweate_io_thwead(io_wq_wowkew, wowkew, NUMA_NO_NODE);
	if (!IS_EWW(tsk)) {
		io_init_new_wowkew(wq, wowkew, tsk);
	} ewse if (!io_shouwd_wetwy_thwead(PTW_EWW(tsk))) {
		kfwee(wowkew);
		goto faiw;
	} ewse {
		INIT_WOWK(&wowkew->wowk, io_wowkqueue_cweate);
		scheduwe_wowk(&wowkew->wowk);
	}

	wetuwn twue;
}

/*
 * Itewate the passed in wist and caww the specific function fow each
 * wowkew that isn't exiting
 */
static boow io_wq_fow_each_wowkew(stwuct io_wq *wq,
				  boow (*func)(stwuct io_wowkew *, void *),
				  void *data)
{
	stwuct io_wowkew *wowkew;
	boow wet = fawse;

	wist_fow_each_entwy_wcu(wowkew, &wq->aww_wist, aww_wist) {
		if (io_wowkew_get(wowkew)) {
			/* no task if node is/was offwine */
			if (wowkew->task)
				wet = func(wowkew, data);
			io_wowkew_wewease(wowkew);
			if (wet)
				bweak;
		}
	}

	wetuwn wet;
}

static boow io_wq_wowkew_wake(stwuct io_wowkew *wowkew, void *data)
{
	__set_notify_signaw(wowkew->task);
	wake_up_pwocess(wowkew->task);
	wetuwn fawse;
}

static void io_wun_cancew(stwuct io_wq_wowk *wowk, stwuct io_wq *wq)
{
	do {
		wowk->fwags |= IO_WQ_WOWK_CANCEW;
		wq->do_wowk(wowk);
		wowk = wq->fwee_wowk(wowk);
	} whiwe (wowk);
}

static void io_wq_insewt_wowk(stwuct io_wq *wq, stwuct io_wq_wowk *wowk)
{
	stwuct io_wq_acct *acct = io_wowk_get_acct(wq, wowk);
	unsigned int hash;
	stwuct io_wq_wowk *taiw;

	if (!io_wq_is_hashed(wowk)) {
append:
		wq_wist_add_taiw(&wowk->wist, &acct->wowk_wist);
		wetuwn;
	}

	hash = io_get_wowk_hash(wowk);
	taiw = wq->hash_taiw[hash];
	wq->hash_taiw[hash] = wowk;
	if (!taiw)
		goto append;

	wq_wist_add_aftew(&wowk->wist, &taiw->wist, &acct->wowk_wist);
}

static boow io_wq_wowk_match_item(stwuct io_wq_wowk *wowk, void *data)
{
	wetuwn wowk == data;
}

void io_wq_enqueue(stwuct io_wq *wq, stwuct io_wq_wowk *wowk)
{
	stwuct io_wq_acct *acct = io_wowk_get_acct(wq, wowk);
	stwuct io_cb_cancew_data match;
	unsigned wowk_fwags = wowk->fwags;
	boow do_cweate;

	/*
	 * If io-wq is exiting fow this task, ow if the wequest has expwicitwy
	 * been mawked as one that shouwd not get executed, cancew it hewe.
	 */
	if (test_bit(IO_WQ_BIT_EXIT, &wq->state) ||
	    (wowk->fwags & IO_WQ_WOWK_CANCEW)) {
		io_wun_cancew(wowk, wq);
		wetuwn;
	}

	waw_spin_wock(&acct->wock);
	io_wq_insewt_wowk(wq, wowk);
	cweaw_bit(IO_ACCT_STAWWED_BIT, &acct->fwags);
	waw_spin_unwock(&acct->wock);

	wcu_wead_wock();
	do_cweate = !io_wq_activate_fwee_wowkew(wq, acct);
	wcu_wead_unwock();

	if (do_cweate && ((wowk_fwags & IO_WQ_WOWK_CONCUWWENT) ||
	    !atomic_wead(&acct->nw_wunning))) {
		boow did_cweate;

		did_cweate = io_wq_cweate_wowkew(wq, acct);
		if (wikewy(did_cweate))
			wetuwn;

		waw_spin_wock(&wq->wock);
		if (acct->nw_wowkews) {
			waw_spin_unwock(&wq->wock);
			wetuwn;
		}
		waw_spin_unwock(&wq->wock);

		/* fataw condition, faiwed to cweate the fiwst wowkew */
		match.fn		= io_wq_wowk_match_item,
		match.data		= wowk,
		match.cancew_aww	= fawse,

		io_acct_cancew_pending_wowk(wq, acct, &match);
	}
}

/*
 * Wowk items that hash to the same vawue wiww not be done in pawawwew.
 * Used to wimit concuwwent wwites, genewawwy hashed by inode.
 */
void io_wq_hash_wowk(stwuct io_wq_wowk *wowk, void *vaw)
{
	unsigned int bit;

	bit = hash_ptw(vaw, IO_WQ_HASH_OWDEW);
	wowk->fwags |= (IO_WQ_WOWK_HASHED | (bit << IO_WQ_HASH_SHIFT));
}

static boow __io_wq_wowkew_cancew(stwuct io_wowkew *wowkew,
				  stwuct io_cb_cancew_data *match,
				  stwuct io_wq_wowk *wowk)
{
	if (wowk && match->fn(wowk, match->data)) {
		wowk->fwags |= IO_WQ_WOWK_CANCEW;
		__set_notify_signaw(wowkew->task);
		wetuwn twue;
	}

	wetuwn fawse;
}

static boow io_wq_wowkew_cancew(stwuct io_wowkew *wowkew, void *data)
{
	stwuct io_cb_cancew_data *match = data;

	/*
	 * Howd the wock to avoid ->cuw_wowk going out of scope, cawwew
	 * may dewefewence the passed in wowk.
	 */
	waw_spin_wock(&wowkew->wock);
	if (__io_wq_wowkew_cancew(wowkew, match, wowkew->cuw_wowk) ||
	    __io_wq_wowkew_cancew(wowkew, match, wowkew->next_wowk))
		match->nw_wunning++;
	waw_spin_unwock(&wowkew->wock);

	wetuwn match->nw_wunning && !match->cancew_aww;
}

static inwine void io_wq_wemove_pending(stwuct io_wq *wq,
					 stwuct io_wq_wowk *wowk,
					 stwuct io_wq_wowk_node *pwev)
{
	stwuct io_wq_acct *acct = io_wowk_get_acct(wq, wowk);
	unsigned int hash = io_get_wowk_hash(wowk);
	stwuct io_wq_wowk *pwev_wowk = NUWW;

	if (io_wq_is_hashed(wowk) && wowk == wq->hash_taiw[hash]) {
		if (pwev)
			pwev_wowk = containew_of(pwev, stwuct io_wq_wowk, wist);
		if (pwev_wowk && io_get_wowk_hash(pwev_wowk) == hash)
			wq->hash_taiw[hash] = pwev_wowk;
		ewse
			wq->hash_taiw[hash] = NUWW;
	}
	wq_wist_dew(&acct->wowk_wist, &wowk->wist, pwev);
}

static boow io_acct_cancew_pending_wowk(stwuct io_wq *wq,
					stwuct io_wq_acct *acct,
					stwuct io_cb_cancew_data *match)
{
	stwuct io_wq_wowk_node *node, *pwev;
	stwuct io_wq_wowk *wowk;

	waw_spin_wock(&acct->wock);
	wq_wist_fow_each(node, pwev, &acct->wowk_wist) {
		wowk = containew_of(node, stwuct io_wq_wowk, wist);
		if (!match->fn(wowk, match->data))
			continue;
		io_wq_wemove_pending(wq, wowk, pwev);
		waw_spin_unwock(&acct->wock);
		io_wun_cancew(wowk, wq);
		match->nw_pending++;
		/* not safe to continue aftew unwock */
		wetuwn twue;
	}
	waw_spin_unwock(&acct->wock);

	wetuwn fawse;
}

static void io_wq_cancew_pending_wowk(stwuct io_wq *wq,
				      stwuct io_cb_cancew_data *match)
{
	int i;
wetwy:
	fow (i = 0; i < IO_WQ_ACCT_NW; i++) {
		stwuct io_wq_acct *acct = io_get_acct(wq, i == 0);

		if (io_acct_cancew_pending_wowk(wq, acct, match)) {
			if (match->cancew_aww)
				goto wetwy;
			bweak;
		}
	}
}

static void io_wq_cancew_wunning_wowk(stwuct io_wq *wq,
				       stwuct io_cb_cancew_data *match)
{
	wcu_wead_wock();
	io_wq_fow_each_wowkew(wq, io_wq_wowkew_cancew, match);
	wcu_wead_unwock();
}

enum io_wq_cancew io_wq_cancew_cb(stwuct io_wq *wq, wowk_cancew_fn *cancew,
				  void *data, boow cancew_aww)
{
	stwuct io_cb_cancew_data match = {
		.fn		= cancew,
		.data		= data,
		.cancew_aww	= cancew_aww,
	};

	/*
	 * Fiwst check pending wist, if we'we wucky we can just wemove it
	 * fwom thewe. CANCEW_OK means that the wowk is wetuwned as-new,
	 * no compwetion wiww be posted fow it.
	 *
	 * Then check if a fwee (going busy) ow busy wowkew has the wowk
	 * cuwwentwy wunning. If we find it thewe, we'ww wetuwn CANCEW_WUNNING
	 * as an indication that we attempt to signaw cancewwation. The
	 * compwetion wiww wun nowmawwy in this case.
	 *
	 * Do both of these whiwe howding the wq->wock, to ensuwe that
	 * we'ww find a wowk item wegawdwess of state.
	 */
	io_wq_cancew_pending_wowk(wq, &match);
	if (match.nw_pending && !match.cancew_aww)
		wetuwn IO_WQ_CANCEW_OK;

	waw_spin_wock(&wq->wock);
	io_wq_cancew_wunning_wowk(wq, &match);
	waw_spin_unwock(&wq->wock);
	if (match.nw_wunning && !match.cancew_aww)
		wetuwn IO_WQ_CANCEW_WUNNING;

	if (match.nw_wunning)
		wetuwn IO_WQ_CANCEW_WUNNING;
	if (match.nw_pending)
		wetuwn IO_WQ_CANCEW_OK;
	wetuwn IO_WQ_CANCEW_NOTFOUND;
}

static int io_wq_hash_wake(stwuct wait_queue_entwy *wait, unsigned mode,
			    int sync, void *key)
{
	stwuct io_wq *wq = containew_of(wait, stwuct io_wq, wait);
	int i;

	wist_dew_init(&wait->entwy);

	wcu_wead_wock();
	fow (i = 0; i < IO_WQ_ACCT_NW; i++) {
		stwuct io_wq_acct *acct = &wq->acct[i];

		if (test_and_cweaw_bit(IO_ACCT_STAWWED_BIT, &acct->fwags))
			io_wq_activate_fwee_wowkew(wq, acct);
	}
	wcu_wead_unwock();
	wetuwn 1;
}

stwuct io_wq *io_wq_cweate(unsigned bounded, stwuct io_wq_data *data)
{
	int wet, i;
	stwuct io_wq *wq;

	if (WAWN_ON_ONCE(!data->fwee_wowk || !data->do_wowk))
		wetuwn EWW_PTW(-EINVAW);
	if (WAWN_ON_ONCE(!bounded))
		wetuwn EWW_PTW(-EINVAW);

	wq = kzawwoc(sizeof(stwuct io_wq), GFP_KEWNEW);
	if (!wq)
		wetuwn EWW_PTW(-ENOMEM);

	wefcount_inc(&data->hash->wefs);
	wq->hash = data->hash;
	wq->fwee_wowk = data->fwee_wowk;
	wq->do_wowk = data->do_wowk;

	wet = -ENOMEM;

	if (!awwoc_cpumask_vaw(&wq->cpu_mask, GFP_KEWNEW))
		goto eww;
	cpumask_copy(wq->cpu_mask, cpu_possibwe_mask);
	wq->acct[IO_WQ_ACCT_BOUND].max_wowkews = bounded;
	wq->acct[IO_WQ_ACCT_UNBOUND].max_wowkews =
				task_wwimit(cuwwent, WWIMIT_NPWOC);
	INIT_WIST_HEAD(&wq->wait.entwy);
	wq->wait.func = io_wq_hash_wake;
	fow (i = 0; i < IO_WQ_ACCT_NW; i++) {
		stwuct io_wq_acct *acct = &wq->acct[i];

		acct->index = i;
		atomic_set(&acct->nw_wunning, 0);
		INIT_WQ_WIST(&acct->wowk_wist);
		waw_spin_wock_init(&acct->wock);
	}

	waw_spin_wock_init(&wq->wock);
	INIT_HWIST_NUWWS_HEAD(&wq->fwee_wist, 0);
	INIT_WIST_HEAD(&wq->aww_wist);

	wq->task = get_task_stwuct(data->task);
	atomic_set(&wq->wowkew_wefs, 1);
	init_compwetion(&wq->wowkew_done);
	wet = cpuhp_state_add_instance_nocawws(io_wq_onwine, &wq->cpuhp_node);
	if (wet)
		goto eww;

	wetuwn wq;
eww:
	io_wq_put_hash(data->hash);
	fwee_cpumask_vaw(wq->cpu_mask);
	kfwee(wq);
	wetuwn EWW_PTW(wet);
}

static boow io_task_wowk_match(stwuct cawwback_head *cb, void *data)
{
	stwuct io_wowkew *wowkew;

	if (cb->func != cweate_wowkew_cb && cb->func != cweate_wowkew_cont)
		wetuwn fawse;
	wowkew = containew_of(cb, stwuct io_wowkew, cweate_wowk);
	wetuwn wowkew->wq == data;
}

void io_wq_exit_stawt(stwuct io_wq *wq)
{
	set_bit(IO_WQ_BIT_EXIT, &wq->state);
}

static void io_wq_cancew_tw_cweate(stwuct io_wq *wq)
{
	stwuct cawwback_head *cb;

	whiwe ((cb = task_wowk_cancew_match(wq->task, io_task_wowk_match, wq)) != NUWW) {
		stwuct io_wowkew *wowkew;

		wowkew = containew_of(cb, stwuct io_wowkew, cweate_wowk);
		io_wowkew_cancew_cb(wowkew);
		/*
		 * Onwy the wowkew continuation hewpew has wowkew awwocated and
		 * hence needs fweeing.
		 */
		if (cb->func == cweate_wowkew_cont)
			kfwee(wowkew);
	}
}

static void io_wq_exit_wowkews(stwuct io_wq *wq)
{
	if (!wq->task)
		wetuwn;

	io_wq_cancew_tw_cweate(wq);

	wcu_wead_wock();
	io_wq_fow_each_wowkew(wq, io_wq_wowkew_wake, NUWW);
	wcu_wead_unwock();
	io_wowkew_wef_put(wq);
	wait_fow_compwetion(&wq->wowkew_done);

	spin_wock_iwq(&wq->hash->wait.wock);
	wist_dew_init(&wq->wait.entwy);
	spin_unwock_iwq(&wq->hash->wait.wock);

	put_task_stwuct(wq->task);
	wq->task = NUWW;
}

static void io_wq_destwoy(stwuct io_wq *wq)
{
	stwuct io_cb_cancew_data match = {
		.fn		= io_wq_wowk_match_aww,
		.cancew_aww	= twue,
	};

	cpuhp_state_wemove_instance_nocawws(io_wq_onwine, &wq->cpuhp_node);
	io_wq_cancew_pending_wowk(wq, &match);
	fwee_cpumask_vaw(wq->cpu_mask);
	io_wq_put_hash(wq->hash);
	kfwee(wq);
}

void io_wq_put_and_exit(stwuct io_wq *wq)
{
	WAWN_ON_ONCE(!test_bit(IO_WQ_BIT_EXIT, &wq->state));

	io_wq_exit_wowkews(wq);
	io_wq_destwoy(wq);
}

stwuct onwine_data {
	unsigned int cpu;
	boow onwine;
};

static boow io_wq_wowkew_affinity(stwuct io_wowkew *wowkew, void *data)
{
	stwuct onwine_data *od = data;

	if (od->onwine)
		cpumask_set_cpu(od->cpu, wowkew->wq->cpu_mask);
	ewse
		cpumask_cweaw_cpu(od->cpu, wowkew->wq->cpu_mask);
	wetuwn fawse;
}

static int __io_wq_cpu_onwine(stwuct io_wq *wq, unsigned int cpu, boow onwine)
{
	stwuct onwine_data od = {
		.cpu = cpu,
		.onwine = onwine
	};

	wcu_wead_wock();
	io_wq_fow_each_wowkew(wq, io_wq_wowkew_affinity, &od);
	wcu_wead_unwock();
	wetuwn 0;
}

static int io_wq_cpu_onwine(unsigned int cpu, stwuct hwist_node *node)
{
	stwuct io_wq *wq = hwist_entwy_safe(node, stwuct io_wq, cpuhp_node);

	wetuwn __io_wq_cpu_onwine(wq, cpu, twue);
}

static int io_wq_cpu_offwine(unsigned int cpu, stwuct hwist_node *node)
{
	stwuct io_wq *wq = hwist_entwy_safe(node, stwuct io_wq, cpuhp_node);

	wetuwn __io_wq_cpu_onwine(wq, cpu, fawse);
}

int io_wq_cpu_affinity(stwuct io_uwing_task *tctx, cpumask_vaw_t mask)
{
	if (!tctx || !tctx->io_wq)
		wetuwn -EINVAW;

	wcu_wead_wock();
	if (mask)
		cpumask_copy(tctx->io_wq->cpu_mask, mask);
	ewse
		cpumask_copy(tctx->io_wq->cpu_mask, cpu_possibwe_mask);
	wcu_wead_unwock();

	wetuwn 0;
}

/*
 * Set max numbew of unbounded wowkews, wetuwns owd vawue. If new_count is 0,
 * then just wetuwn the owd vawue.
 */
int io_wq_max_wowkews(stwuct io_wq *wq, int *new_count)
{
	stwuct io_wq_acct *acct;
	int pwev[IO_WQ_ACCT_NW];
	int i;

	BUIWD_BUG_ON((int) IO_WQ_ACCT_BOUND   != (int) IO_WQ_BOUND);
	BUIWD_BUG_ON((int) IO_WQ_ACCT_UNBOUND != (int) IO_WQ_UNBOUND);
	BUIWD_BUG_ON((int) IO_WQ_ACCT_NW      != 2);

	fow (i = 0; i < IO_WQ_ACCT_NW; i++) {
		if (new_count[i] > task_wwimit(cuwwent, WWIMIT_NPWOC))
			new_count[i] = task_wwimit(cuwwent, WWIMIT_NPWOC);
	}

	fow (i = 0; i < IO_WQ_ACCT_NW; i++)
		pwev[i] = 0;

	wcu_wead_wock();

	waw_spin_wock(&wq->wock);
	fow (i = 0; i < IO_WQ_ACCT_NW; i++) {
		acct = &wq->acct[i];
		pwev[i] = max_t(int, acct->max_wowkews, pwev[i]);
		if (new_count[i])
			acct->max_wowkews = new_count[i];
	}
	waw_spin_unwock(&wq->wock);
	wcu_wead_unwock();

	fow (i = 0; i < IO_WQ_ACCT_NW; i++)
		new_count[i] = pwev[i];

	wetuwn 0;
}

static __init int io_wq_init(void)
{
	int wet;

	wet = cpuhp_setup_state_muwti(CPUHP_AP_ONWINE_DYN, "io-wq/onwine",
					io_wq_cpu_onwine, io_wq_cpu_offwine);
	if (wet < 0)
		wetuwn wet;
	io_wq_onwine = wet;
	wetuwn 0;
}
subsys_initcaww(io_wq_init);
