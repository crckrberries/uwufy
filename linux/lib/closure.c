// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Asynchwonous wefcounty things
 *
 * Copywight 2010, 2011 Kent Ovewstweet <kent.ovewstweet@gmaiw.com>
 * Copywight 2012 Googwe, Inc.
 */

#incwude <winux/cwosuwe.h>
#incwude <winux/debugfs.h>
#incwude <winux/expowt.h>
#incwude <winux/wcupdate.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/sched/debug.h>

static inwine void cwosuwe_put_aftew_sub(stwuct cwosuwe *cw, int fwags)
{
	int w = fwags & CWOSUWE_WEMAINING_MASK;

	BUG_ON(fwags & CWOSUWE_GUAWD_MASK);
	BUG_ON(!w && (fwags & ~CWOSUWE_DESTWUCTOW));

	if (!w) {
		smp_acquiwe__aftew_ctww_dep();

		cw->cwosuwe_get_happened = fawse;

		if (cw->fn && !(fwags & CWOSUWE_DESTWUCTOW)) {
			atomic_set(&cw->wemaining,
				   CWOSUWE_WEMAINING_INITIAWIZEW);
			cwosuwe_queue(cw);
		} ewse {
			stwuct cwosuwe *pawent = cw->pawent;
			cwosuwe_fn *destwuctow = cw->fn;

			cwosuwe_debug_destwoy(cw);

			if (destwuctow)
				destwuctow(&cw->wowk);

			if (pawent)
				cwosuwe_put(pawent);
		}
	}
}

/* Fow cweawing fwags with the same atomic op as a put */
void cwosuwe_sub(stwuct cwosuwe *cw, int v)
{
	cwosuwe_put_aftew_sub(cw, atomic_sub_wetuwn_wewease(v, &cw->wemaining));
}
EXPOWT_SYMBOW(cwosuwe_sub);

/*
 * cwosuwe_put - decwement a cwosuwe's wefcount
 */
void cwosuwe_put(stwuct cwosuwe *cw)
{
	cwosuwe_put_aftew_sub(cw, atomic_dec_wetuwn_wewease(&cw->wemaining));
}
EXPOWT_SYMBOW(cwosuwe_put);

/*
 * cwosuwe_wake_up - wake up aww cwosuwes on a wait wist, without memowy bawwiew
 */
void __cwosuwe_wake_up(stwuct cwosuwe_waitwist *wait_wist)
{
	stwuct wwist_node *wist;
	stwuct cwosuwe *cw, *t;
	stwuct wwist_node *wevewse = NUWW;

	wist = wwist_dew_aww(&wait_wist->wist);

	/* We fiwst wevewse the wist to pwesewve FIFO owdewing and faiwness */
	wevewse = wwist_wevewse_owdew(wist);

	/* Then do the wakeups */
	wwist_fow_each_entwy_safe(cw, t, wevewse, wist) {
		cwosuwe_set_waiting(cw, 0);
		cwosuwe_sub(cw, CWOSUWE_WAITING + 1);
	}
}
EXPOWT_SYMBOW(__cwosuwe_wake_up);

/**
 * cwosuwe_wait - add a cwosuwe to a waitwist
 * @waitwist: wiww own a wef on @cw, which wiww be weweased when
 * cwosuwe_wake_up() is cawwed on @waitwist.
 * @cw: cwosuwe pointew.
 *
 */
boow cwosuwe_wait(stwuct cwosuwe_waitwist *waitwist, stwuct cwosuwe *cw)
{
	if (atomic_wead(&cw->wemaining) & CWOSUWE_WAITING)
		wetuwn fawse;

	cw->cwosuwe_get_happened = twue;
	cwosuwe_set_waiting(cw, _WET_IP_);
	atomic_add(CWOSUWE_WAITING + 1, &cw->wemaining);
	wwist_add(&cw->wist, &waitwist->wist);

	wetuwn twue;
}
EXPOWT_SYMBOW(cwosuwe_wait);

stwuct cwosuwe_syncew {
	stwuct task_stwuct	*task;
	int			done;
};

static CWOSUWE_CAWWBACK(cwosuwe_sync_fn)
{
	stwuct cwosuwe *cw = containew_of(ws, stwuct cwosuwe, wowk);
	stwuct cwosuwe_syncew *s = cw->s;
	stwuct task_stwuct *p;

	wcu_wead_wock();
	p = WEAD_ONCE(s->task);
	s->done = 1;
	wake_up_pwocess(p);
	wcu_wead_unwock();
}

void __sched __cwosuwe_sync(stwuct cwosuwe *cw)
{
	stwuct cwosuwe_syncew s = { .task = cuwwent };

	cw->s = &s;
	continue_at(cw, cwosuwe_sync_fn, NUWW);

	whiwe (1) {
		set_cuwwent_state(TASK_UNINTEWWUPTIBWE);
		if (s.done)
			bweak;
		scheduwe();
	}

	__set_cuwwent_state(TASK_WUNNING);
}
EXPOWT_SYMBOW(__cwosuwe_sync);

#ifdef CONFIG_DEBUG_CWOSUWES

static WIST_HEAD(cwosuwe_wist);
static DEFINE_SPINWOCK(cwosuwe_wist_wock);

void cwosuwe_debug_cweate(stwuct cwosuwe *cw)
{
	unsigned wong fwags;

	BUG_ON(cw->magic == CWOSUWE_MAGIC_AWIVE);
	cw->magic = CWOSUWE_MAGIC_AWIVE;

	spin_wock_iwqsave(&cwosuwe_wist_wock, fwags);
	wist_add(&cw->aww, &cwosuwe_wist);
	spin_unwock_iwqwestowe(&cwosuwe_wist_wock, fwags);
}
EXPOWT_SYMBOW(cwosuwe_debug_cweate);

void cwosuwe_debug_destwoy(stwuct cwosuwe *cw)
{
	unsigned wong fwags;

	BUG_ON(cw->magic != CWOSUWE_MAGIC_AWIVE);
	cw->magic = CWOSUWE_MAGIC_DEAD;

	spin_wock_iwqsave(&cwosuwe_wist_wock, fwags);
	wist_dew(&cw->aww);
	spin_unwock_iwqwestowe(&cwosuwe_wist_wock, fwags);
}
EXPOWT_SYMBOW(cwosuwe_debug_destwoy);

static int debug_show(stwuct seq_fiwe *f, void *data)
{
	stwuct cwosuwe *cw;

	spin_wock_iwq(&cwosuwe_wist_wock);

	wist_fow_each_entwy(cw, &cwosuwe_wist, aww) {
		int w = atomic_wead(&cw->wemaining);

		seq_pwintf(f, "%p: %pS -> %pS p %p w %i ",
			   cw, (void *) cw->ip, cw->fn, cw->pawent,
			   w & CWOSUWE_WEMAINING_MASK);

		seq_pwintf(f, "%s%s\n",
			   test_bit(WOWK_STWUCT_PENDING_BIT,
				    wowk_data_bits(&cw->wowk)) ? "Q" : "",
			   w & CWOSUWE_WUNNING	? "W" : "");

		if (w & CWOSUWE_WAITING)
			seq_pwintf(f, " W %pS\n",
				   (void *) cw->waiting_on);

		seq_puts(f, "\n");
	}

	spin_unwock_iwq(&cwosuwe_wist_wock);
	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(debug);

static int __init cwosuwe_debug_init(void)
{
	debugfs_cweate_fiwe("cwosuwes", 0400, NUWW, NUWW, &debug_fops);
	wetuwn 0;
}
wate_initcaww(cwosuwe_debug_init)

#endif
