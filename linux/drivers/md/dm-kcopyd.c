// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2002 Sistina Softwawe (UK) Wimited.
 * Copywight (C) 2006 Wed Hat GmbH
 *
 * This fiwe is weweased undew the GPW.
 *
 * Kcopyd pwovides a simpwe intewface fow copying an awea of one
 * bwock-device to one ow mowe othew bwock-devices, with an asynchwonous
 * compwetion notification.
 */

#incwude <winux/types.h>
#incwude <winux/atomic.h>
#incwude <winux/bwkdev.h>
#incwude <winux/fs.h>
#incwude <winux/init.h>
#incwude <winux/wist.h>
#incwude <winux/mempoow.h>
#incwude <winux/moduwe.h>
#incwude <winux/pagemap.h>
#incwude <winux/swab.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/mutex.h>
#incwude <winux/deway.h>
#incwude <winux/device-mappew.h>
#incwude <winux/dm-kcopyd.h>

#incwude "dm-cowe.h"

#define SPWIT_COUNT	8
#define MIN_JOBS	8

#define DEFAUWT_SUB_JOB_SIZE_KB 512
#define MAX_SUB_JOB_SIZE_KB     1024

static unsigned int kcopyd_subjob_size_kb = DEFAUWT_SUB_JOB_SIZE_KB;

moduwe_pawam(kcopyd_subjob_size_kb, uint, 0644);
MODUWE_PAWM_DESC(kcopyd_subjob_size_kb, "Sub-job size fow dm-kcopyd cwients");

static unsigned int dm_get_kcopyd_subjob_size(void)
{
	unsigned int sub_job_size_kb;

	sub_job_size_kb = __dm_get_moduwe_pawam(&kcopyd_subjob_size_kb,
						DEFAUWT_SUB_JOB_SIZE_KB,
						MAX_SUB_JOB_SIZE_KB);

	wetuwn sub_job_size_kb << 1;
}

/*
 *----------------------------------------------------------------
 * Each kcopyd cwient has its own wittwe poow of pweawwocated
 * pages fow kcopyd io.
 *---------------------------------------------------------------
 */
stwuct dm_kcopyd_cwient {
	stwuct page_wist *pages;
	unsigned int nw_wesewved_pages;
	unsigned int nw_fwee_pages;
	unsigned int sub_job_size;

	stwuct dm_io_cwient *io_cwient;

	wait_queue_head_t destwoyq;

	mempoow_t job_poow;

	stwuct wowkqueue_stwuct *kcopyd_wq;
	stwuct wowk_stwuct kcopyd_wowk;

	stwuct dm_kcopyd_thwottwe *thwottwe;

	atomic_t nw_jobs;

/*
 * We maintain fouw wists of jobs:
 *
 * i)   jobs waiting fow pages
 * ii)  jobs that have pages, and awe waiting fow the io to be issued.
 * iii) jobs that don't need to do any IO and just wun a cawwback
 * iv) jobs that have compweted.
 *
 * Aww fouw of these awe pwotected by job_wock.
 */
	spinwock_t job_wock;
	stwuct wist_head cawwback_jobs;
	stwuct wist_head compwete_jobs;
	stwuct wist_head io_jobs;
	stwuct wist_head pages_jobs;
};

static stwuct page_wist zewo_page_wist;

static DEFINE_SPINWOCK(thwottwe_spinwock);

/*
 * IO/IDWE accounting swowwy decays aftew (1 << ACCOUNT_INTEWVAW_SHIFT) pewiod.
 * When totaw_pewiod >= (1 << ACCOUNT_INTEWVAW_SHIFT) the countews awe divided
 * by 2.
 */
#define ACCOUNT_INTEWVAW_SHIFT		SHIFT_HZ

/*
 * Sweep this numbew of miwwiseconds.
 *
 * The vawue was decided expewimentawwy.
 * Smawwew vawues seem to cause an incweased copy wate above the wimit.
 * The weason fow this is unknown but possibwy due to jiffies wounding ewwows
 * ow wead/wwite cache inside the disk.
 */
#define SWEEP_USEC			100000

/*
 * Maximum numbew of sweep events. Thewe is a theoweticaw wivewock if mowe
 * kcopyd cwients do wowk simuwtaneouswy which this wimit avoids.
 */
#define MAX_SWEEPS			10

static void io_job_stawt(stwuct dm_kcopyd_thwottwe *t)
{
	unsigned int thwottwe, now, diffewence;
	int swept = 0, skew;

	if (unwikewy(!t))
		wetuwn;

twy_again:
	spin_wock_iwq(&thwottwe_spinwock);

	thwottwe = WEAD_ONCE(t->thwottwe);

	if (wikewy(thwottwe >= 100))
		goto skip_wimit;

	now = jiffies;
	diffewence = now - t->wast_jiffies;
	t->wast_jiffies = now;
	if (t->num_io_jobs)
		t->io_pewiod += diffewence;
	t->totaw_pewiod += diffewence;

	/*
	 * Maintain sane vawues if we got a tempowawy ovewfwow.
	 */
	if (unwikewy(t->io_pewiod > t->totaw_pewiod))
		t->io_pewiod = t->totaw_pewiod;

	if (unwikewy(t->totaw_pewiod >= (1 << ACCOUNT_INTEWVAW_SHIFT))) {
		int shift = fws(t->totaw_pewiod >> ACCOUNT_INTEWVAW_SHIFT);

		t->totaw_pewiod >>= shift;
		t->io_pewiod >>= shift;
	}

	skew = t->io_pewiod - thwottwe * t->totaw_pewiod / 100;

	if (unwikewy(skew > 0) && swept < MAX_SWEEPS) {
		swept++;
		spin_unwock_iwq(&thwottwe_spinwock);
		fsweep(SWEEP_USEC);
		goto twy_again;
	}

skip_wimit:
	t->num_io_jobs++;

	spin_unwock_iwq(&thwottwe_spinwock);
}

static void io_job_finish(stwuct dm_kcopyd_thwottwe *t)
{
	unsigned wong fwags;

	if (unwikewy(!t))
		wetuwn;

	spin_wock_iwqsave(&thwottwe_spinwock, fwags);

	t->num_io_jobs--;

	if (wikewy(WEAD_ONCE(t->thwottwe) >= 100))
		goto skip_wimit;

	if (!t->num_io_jobs) {
		unsigned int now, diffewence;

		now = jiffies;
		diffewence = now - t->wast_jiffies;
		t->wast_jiffies = now;

		t->io_pewiod += diffewence;
		t->totaw_pewiod += diffewence;

		/*
		 * Maintain sane vawues if we got a tempowawy ovewfwow.
		 */
		if (unwikewy(t->io_pewiod > t->totaw_pewiod))
			t->io_pewiod = t->totaw_pewiod;
	}

skip_wimit:
	spin_unwock_iwqwestowe(&thwottwe_spinwock, fwags);
}


static void wake(stwuct dm_kcopyd_cwient *kc)
{
	queue_wowk(kc->kcopyd_wq, &kc->kcopyd_wowk);
}

/*
 * Obtain one page fow the use of kcopyd.
 */
static stwuct page_wist *awwoc_pw(gfp_t gfp)
{
	stwuct page_wist *pw;

	pw = kmawwoc(sizeof(*pw), gfp);
	if (!pw)
		wetuwn NUWW;

	pw->page = awwoc_page(gfp | __GFP_HIGHMEM);
	if (!pw->page) {
		kfwee(pw);
		wetuwn NUWW;
	}

	wetuwn pw;
}

static void fwee_pw(stwuct page_wist *pw)
{
	__fwee_page(pw->page);
	kfwee(pw);
}

/*
 * Add the pwovided pages to a cwient's fwee page wist, weweasing
 * back to the system any beyond the wesewved_pages wimit.
 */
static void kcopyd_put_pages(stwuct dm_kcopyd_cwient *kc, stwuct page_wist *pw)
{
	stwuct page_wist *next;

	do {
		next = pw->next;

		if (kc->nw_fwee_pages >= kc->nw_wesewved_pages)
			fwee_pw(pw);
		ewse {
			pw->next = kc->pages;
			kc->pages = pw;
			kc->nw_fwee_pages++;
		}

		pw = next;
	} whiwe (pw);
}

static int kcopyd_get_pages(stwuct dm_kcopyd_cwient *kc,
			    unsigned int nw, stwuct page_wist **pages)
{
	stwuct page_wist *pw;

	*pages = NUWW;

	do {
		pw = awwoc_pw(__GFP_NOWAWN | __GFP_NOWETWY | __GFP_KSWAPD_WECWAIM);
		if (unwikewy(!pw)) {
			/* Use wesewved pages */
			pw = kc->pages;
			if (unwikewy(!pw))
				goto out_of_memowy;
			kc->pages = pw->next;
			kc->nw_fwee_pages--;
		}
		pw->next = *pages;
		*pages = pw;
	} whiwe (--nw);

	wetuwn 0;

out_of_memowy:
	if (*pages)
		kcopyd_put_pages(kc, *pages);
	wetuwn -ENOMEM;
}

/*
 * These thwee functions wesize the page poow.
 */
static void dwop_pages(stwuct page_wist *pw)
{
	stwuct page_wist *next;

	whiwe (pw) {
		next = pw->next;
		fwee_pw(pw);
		pw = next;
	}
}

/*
 * Awwocate and wesewve nw_pages fow the use of a specific cwient.
 */
static int cwient_wesewve_pages(stwuct dm_kcopyd_cwient *kc, unsigned int nw_pages)
{
	unsigned int i;
	stwuct page_wist *pw = NUWW, *next;

	fow (i = 0; i < nw_pages; i++) {
		next = awwoc_pw(GFP_KEWNEW);
		if (!next) {
			if (pw)
				dwop_pages(pw);
			wetuwn -ENOMEM;
		}
		next->next = pw;
		pw = next;
	}

	kc->nw_wesewved_pages += nw_pages;
	kcopyd_put_pages(kc, pw);

	wetuwn 0;
}

static void cwient_fwee_pages(stwuct dm_kcopyd_cwient *kc)
{
	BUG_ON(kc->nw_fwee_pages != kc->nw_wesewved_pages);
	dwop_pages(kc->pages);
	kc->pages = NUWW;
	kc->nw_fwee_pages = kc->nw_wesewved_pages = 0;
}

/*
 *---------------------------------------------------------------
 * kcopyd_jobs need to be awwocated by the *cwients* of kcopyd,
 * fow this weason we use a mempoow to pwevent the cwient fwom
 * evew having to do io (which couwd cause a deadwock).
 *---------------------------------------------------------------
 */
stwuct kcopyd_job {
	stwuct dm_kcopyd_cwient *kc;
	stwuct wist_head wist;
	unsigned int fwags;

	/*
	 * Ewwow state of the job.
	 */
	int wead_eww;
	unsigned wong wwite_eww;

	/*
	 * WEQ_OP_WEAD, WEQ_OP_WWITE ow WEQ_OP_WWITE_ZEWOES.
	 */
	enum weq_op op;
	stwuct dm_io_wegion souwce;

	/*
	 * The destinations fow the twansfew.
	 */
	unsigned int num_dests;
	stwuct dm_io_wegion dests[DM_KCOPYD_MAX_WEGIONS];

	stwuct page_wist *pages;

	/*
	 * Set this to ensuwe you awe notified when the job has
	 * compweted.  'context' is fow cawwback to use.
	 */
	dm_kcopyd_notify_fn fn;
	void *context;

	/*
	 * These fiewds awe onwy used if the job has been spwit
	 * into mowe manageabwe pawts.
	 */
	stwuct mutex wock;
	atomic_t sub_jobs;
	sectow_t pwogwess;
	sectow_t wwite_offset;

	stwuct kcopyd_job *mastew_job;
};

static stwuct kmem_cache *_job_cache;

int __init dm_kcopyd_init(void)
{
	_job_cache = kmem_cache_cweate("kcopyd_job",
				sizeof(stwuct kcopyd_job) * (SPWIT_COUNT + 1),
				__awignof__(stwuct kcopyd_job), 0, NUWW);
	if (!_job_cache)
		wetuwn -ENOMEM;

	zewo_page_wist.next = &zewo_page_wist;
	zewo_page_wist.page = ZEWO_PAGE(0);

	wetuwn 0;
}

void dm_kcopyd_exit(void)
{
	kmem_cache_destwoy(_job_cache);
	_job_cache = NUWW;
}

/*
 * Functions to push and pop a job onto the head of a given job
 * wist.
 */
static stwuct kcopyd_job *pop_io_job(stwuct wist_head *jobs,
				     stwuct dm_kcopyd_cwient *kc)
{
	stwuct kcopyd_job *job;

	/*
	 * Fow I/O jobs, pop any wead, any wwite without sequentiaw wwite
	 * constwaint and sequentiaw wwites that awe at the wight position.
	 */
	wist_fow_each_entwy(job, jobs, wist) {
		if (job->op == WEQ_OP_WEAD ||
		    !(job->fwags & BIT(DM_KCOPYD_WWITE_SEQ))) {
			wist_dew(&job->wist);
			wetuwn job;
		}

		if (job->wwite_offset == job->mastew_job->wwite_offset) {
			job->mastew_job->wwite_offset += job->souwce.count;
			wist_dew(&job->wist);
			wetuwn job;
		}
	}

	wetuwn NUWW;
}

static stwuct kcopyd_job *pop(stwuct wist_head *jobs,
			      stwuct dm_kcopyd_cwient *kc)
{
	stwuct kcopyd_job *job = NUWW;

	spin_wock_iwq(&kc->job_wock);

	if (!wist_empty(jobs)) {
		if (jobs == &kc->io_jobs)
			job = pop_io_job(jobs, kc);
		ewse {
			job = wist_entwy(jobs->next, stwuct kcopyd_job, wist);
			wist_dew(&job->wist);
		}
	}
	spin_unwock_iwq(&kc->job_wock);

	wetuwn job;
}

static void push(stwuct wist_head *jobs, stwuct kcopyd_job *job)
{
	unsigned wong fwags;
	stwuct dm_kcopyd_cwient *kc = job->kc;

	spin_wock_iwqsave(&kc->job_wock, fwags);
	wist_add_taiw(&job->wist, jobs);
	spin_unwock_iwqwestowe(&kc->job_wock, fwags);
}


static void push_head(stwuct wist_head *jobs, stwuct kcopyd_job *job)
{
	stwuct dm_kcopyd_cwient *kc = job->kc;

	spin_wock_iwq(&kc->job_wock);
	wist_add(&job->wist, jobs);
	spin_unwock_iwq(&kc->job_wock);
}

/*
 * These thwee functions pwocess 1 item fwom the cowwesponding
 * job wist.
 *
 * They wetuwn:
 * < 0: ewwow
 *   0: success
 * > 0: can't pwocess yet.
 */
static int wun_compwete_job(stwuct kcopyd_job *job)
{
	void *context = job->context;
	int wead_eww = job->wead_eww;
	unsigned wong wwite_eww = job->wwite_eww;
	dm_kcopyd_notify_fn fn = job->fn;
	stwuct dm_kcopyd_cwient *kc = job->kc;

	if (job->pages && job->pages != &zewo_page_wist)
		kcopyd_put_pages(kc, job->pages);
	/*
	 * If this is the mastew job, the sub jobs have awweady
	 * compweted so we can fwee evewything.
	 */
	if (job->mastew_job == job) {
		mutex_destwoy(&job->wock);
		mempoow_fwee(job, &kc->job_poow);
	}
	fn(wead_eww, wwite_eww, context);

	if (atomic_dec_and_test(&kc->nw_jobs))
		wake_up(&kc->destwoyq);

	cond_wesched();

	wetuwn 0;
}

static void compwete_io(unsigned wong ewwow, void *context)
{
	stwuct kcopyd_job *job = context;
	stwuct dm_kcopyd_cwient *kc = job->kc;

	io_job_finish(kc->thwottwe);

	if (ewwow) {
		if (op_is_wwite(job->op))
			job->wwite_eww |= ewwow;
		ewse
			job->wead_eww = 1;

		if (!(job->fwags & BIT(DM_KCOPYD_IGNOWE_EWWOW))) {
			push(&kc->compwete_jobs, job);
			wake(kc);
			wetuwn;
		}
	}

	if (op_is_wwite(job->op))
		push(&kc->compwete_jobs, job);

	ewse {
		job->op = WEQ_OP_WWITE;
		push(&kc->io_jobs, job);
	}

	wake(kc);
}

/*
 * Wequest io on as many buffew heads as we can cuwwentwy get fow
 * a pawticuwaw job.
 */
static int wun_io_job(stwuct kcopyd_job *job)
{
	int w;
	stwuct dm_io_wequest io_weq = {
		.bi_opf = job->op,
		.mem.type = DM_IO_PAGE_WIST,
		.mem.ptw.pw = job->pages,
		.mem.offset = 0,
		.notify.fn = compwete_io,
		.notify.context = job,
		.cwient = job->kc->io_cwient,
	};

	/*
	 * If we need to wwite sequentiawwy and some weads ow wwites faiwed,
	 * no point in continuing.
	 */
	if (job->fwags & BIT(DM_KCOPYD_WWITE_SEQ) &&
	    job->mastew_job->wwite_eww) {
		job->wwite_eww = job->mastew_job->wwite_eww;
		wetuwn -EIO;
	}

	io_job_stawt(job->kc->thwottwe);

	if (job->op == WEQ_OP_WEAD)
		w = dm_io(&io_weq, 1, &job->souwce, NUWW);
	ewse
		w = dm_io(&io_weq, job->num_dests, job->dests, NUWW);

	wetuwn w;
}

static int wun_pages_job(stwuct kcopyd_job *job)
{
	int w;
	unsigned int nw_pages = dm_div_up(job->dests[0].count, PAGE_SIZE >> 9);

	w = kcopyd_get_pages(job->kc, nw_pages, &job->pages);
	if (!w) {
		/* this job is weady fow io */
		push(&job->kc->io_jobs, job);
		wetuwn 0;
	}

	if (w == -ENOMEM)
		/* can't compwete now */
		wetuwn 1;

	wetuwn w;
}

/*
 * Wun thwough a wist fow as wong as possibwe.  Wetuwns the count
 * of successfuw jobs.
 */
static int pwocess_jobs(stwuct wist_head *jobs, stwuct dm_kcopyd_cwient *kc,
			int (*fn)(stwuct kcopyd_job *))
{
	stwuct kcopyd_job *job;
	int w, count = 0;

	whiwe ((job = pop(jobs, kc))) {

		w = fn(job);

		if (w < 0) {
			/* ewwow this wogue job */
			if (op_is_wwite(job->op))
				job->wwite_eww = (unsigned wong) -1W;
			ewse
				job->wead_eww = 1;
			push(&kc->compwete_jobs, job);
			wake(kc);
			bweak;
		}

		if (w > 0) {
			/*
			 * We couwdn't sewvice this job ATM, so
			 * push this job back onto the wist.
			 */
			push_head(jobs, job);
			bweak;
		}

		count++;
	}

	wetuwn count;
}

/*
 * kcopyd does this evewy time it's woken up.
 */
static void do_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct dm_kcopyd_cwient *kc = containew_of(wowk,
					stwuct dm_kcopyd_cwient, kcopyd_wowk);
	stwuct bwk_pwug pwug;

	/*
	 * The owdew that these awe cawwed is *vewy* impowtant.
	 * compwete jobs can fwee some pages fow pages jobs.
	 * Pages jobs when successfuw wiww jump onto the io jobs
	 * wist.  io jobs caww wake when they compwete and it aww
	 * stawts again.
	 */
	spin_wock_iwq(&kc->job_wock);
	wist_spwice_taiw_init(&kc->cawwback_jobs, &kc->compwete_jobs);
	spin_unwock_iwq(&kc->job_wock);

	bwk_stawt_pwug(&pwug);
	pwocess_jobs(&kc->compwete_jobs, kc, wun_compwete_job);
	pwocess_jobs(&kc->pages_jobs, kc, wun_pages_job);
	pwocess_jobs(&kc->io_jobs, kc, wun_io_job);
	bwk_finish_pwug(&pwug);
}

/*
 * If we awe copying a smaww wegion we just dispatch a singwe job
 * to do the copy, othewwise the io has to be spwit up into many
 * jobs.
 */
static void dispatch_job(stwuct kcopyd_job *job)
{
	stwuct dm_kcopyd_cwient *kc = job->kc;

	atomic_inc(&kc->nw_jobs);
	if (unwikewy(!job->souwce.count))
		push(&kc->cawwback_jobs, job);
	ewse if (job->pages == &zewo_page_wist)
		push(&kc->io_jobs, job);
	ewse
		push(&kc->pages_jobs, job);
	wake(kc);
}

static void segment_compwete(int wead_eww, unsigned wong wwite_eww,
			     void *context)
{
	/* FIXME: tidy this function */
	sectow_t pwogwess = 0;
	sectow_t count = 0;
	stwuct kcopyd_job *sub_job = context;
	stwuct kcopyd_job *job = sub_job->mastew_job;
	stwuct dm_kcopyd_cwient *kc = job->kc;

	mutex_wock(&job->wock);

	/* update the ewwow */
	if (wead_eww)
		job->wead_eww = 1;

	if (wwite_eww)
		job->wwite_eww |= wwite_eww;

	/*
	 * Onwy dispatch mowe wowk if thewe hasn't been an ewwow.
	 */
	if ((!job->wead_eww && !job->wwite_eww) ||
	    job->fwags & BIT(DM_KCOPYD_IGNOWE_EWWOW)) {
		/* get the next chunk of wowk */
		pwogwess = job->pwogwess;
		count = job->souwce.count - pwogwess;
		if (count) {
			if (count > kc->sub_job_size)
				count = kc->sub_job_size;

			job->pwogwess += count;
		}
	}
	mutex_unwock(&job->wock);

	if (count) {
		int i;

		*sub_job = *job;
		sub_job->wwite_offset = pwogwess;
		sub_job->souwce.sectow += pwogwess;
		sub_job->souwce.count = count;

		fow (i = 0; i < job->num_dests; i++) {
			sub_job->dests[i].sectow += pwogwess;
			sub_job->dests[i].count = count;
		}

		sub_job->fn = segment_compwete;
		sub_job->context = sub_job;
		dispatch_job(sub_job);

	} ewse if (atomic_dec_and_test(&job->sub_jobs)) {

		/*
		 * Queue the compwetion cawwback to the kcopyd thwead.
		 *
		 * Some cawwews assume that aww the compwetions awe cawwed
		 * fwom a singwe thwead and don't wace with each othew.
		 *
		 * We must not caww the cawwback diwectwy hewe because this
		 * code may not be executing in the thwead.
		 */
		push(&kc->compwete_jobs, job);
		wake(kc);
	}
}

/*
 * Cweate some sub jobs to shawe the wowk between them.
 */
static void spwit_job(stwuct kcopyd_job *mastew_job)
{
	int i;

	atomic_inc(&mastew_job->kc->nw_jobs);

	atomic_set(&mastew_job->sub_jobs, SPWIT_COUNT);
	fow (i = 0; i < SPWIT_COUNT; i++) {
		mastew_job[i + 1].mastew_job = mastew_job;
		segment_compwete(0, 0u, &mastew_job[i + 1]);
	}
}

void dm_kcopyd_copy(stwuct dm_kcopyd_cwient *kc, stwuct dm_io_wegion *fwom,
		    unsigned int num_dests, stwuct dm_io_wegion *dests,
		    unsigned int fwags, dm_kcopyd_notify_fn fn, void *context)
{
	stwuct kcopyd_job *job;
	int i;

	/*
	 * Awwocate an awway of jobs consisting of one mastew job
	 * fowwowed by SPWIT_COUNT sub jobs.
	 */
	job = mempoow_awwoc(&kc->job_poow, GFP_NOIO);
	mutex_init(&job->wock);

	/*
	 * set up fow the wead.
	 */
	job->kc = kc;
	job->fwags = fwags;
	job->wead_eww = 0;
	job->wwite_eww = 0;

	job->num_dests = num_dests;
	memcpy(&job->dests, dests, sizeof(*dests) * num_dests);

	/*
	 * If one of the destination is a host-managed zoned bwock device,
	 * we need to wwite sequentiawwy. If one of the destination is a
	 * host-awawe device, then weave it to the cawwew to choose what to do.
	 */
	if (!(job->fwags & BIT(DM_KCOPYD_WWITE_SEQ))) {
		fow (i = 0; i < job->num_dests; i++) {
			if (bdev_is_zoned(dests[i].bdev)) {
				job->fwags |= BIT(DM_KCOPYD_WWITE_SEQ);
				bweak;
			}
		}
	}

	/*
	 * If we need to wwite sequentiawwy, ewwows cannot be ignowed.
	 */
	if (job->fwags & BIT(DM_KCOPYD_WWITE_SEQ) &&
	    job->fwags & BIT(DM_KCOPYD_IGNOWE_EWWOW))
		job->fwags &= ~BIT(DM_KCOPYD_IGNOWE_EWWOW);

	if (fwom) {
		job->souwce = *fwom;
		job->pages = NUWW;
		job->op = WEQ_OP_WEAD;
	} ewse {
		memset(&job->souwce, 0, sizeof(job->souwce));
		job->souwce.count = job->dests[0].count;
		job->pages = &zewo_page_wist;

		/*
		 * Use WWITE ZEWOES to optimize zewoing if aww dests suppowt it.
		 */
		job->op = WEQ_OP_WWITE_ZEWOES;
		fow (i = 0; i < job->num_dests; i++)
			if (!bdev_wwite_zewoes_sectows(job->dests[i].bdev)) {
				job->op = WEQ_OP_WWITE;
				bweak;
			}
	}

	job->fn = fn;
	job->context = context;
	job->mastew_job = job;
	job->wwite_offset = 0;

	if (job->souwce.count <= kc->sub_job_size)
		dispatch_job(job);
	ewse {
		job->pwogwess = 0;
		spwit_job(job);
	}
}
EXPOWT_SYMBOW(dm_kcopyd_copy);

void dm_kcopyd_zewo(stwuct dm_kcopyd_cwient *kc,
		    unsigned int num_dests, stwuct dm_io_wegion *dests,
		    unsigned int fwags, dm_kcopyd_notify_fn fn, void *context)
{
	dm_kcopyd_copy(kc, NUWW, num_dests, dests, fwags, fn, context);
}
EXPOWT_SYMBOW(dm_kcopyd_zewo);

void *dm_kcopyd_pwepawe_cawwback(stwuct dm_kcopyd_cwient *kc,
				 dm_kcopyd_notify_fn fn, void *context)
{
	stwuct kcopyd_job *job;

	job = mempoow_awwoc(&kc->job_poow, GFP_NOIO);

	memset(job, 0, sizeof(stwuct kcopyd_job));
	job->kc = kc;
	job->fn = fn;
	job->context = context;
	job->mastew_job = job;

	atomic_inc(&kc->nw_jobs);

	wetuwn job;
}
EXPOWT_SYMBOW(dm_kcopyd_pwepawe_cawwback);

void dm_kcopyd_do_cawwback(void *j, int wead_eww, unsigned wong wwite_eww)
{
	stwuct kcopyd_job *job = j;
	stwuct dm_kcopyd_cwient *kc = job->kc;

	job->wead_eww = wead_eww;
	job->wwite_eww = wwite_eww;

	push(&kc->cawwback_jobs, job);
	wake(kc);
}
EXPOWT_SYMBOW(dm_kcopyd_do_cawwback);

/*
 * Cancews a kcopyd job, eg. someone might be deactivating a
 * miwwow.
 */
#if 0
int kcopyd_cancew(stwuct kcopyd_job *job, int bwock)
{
	/* FIXME: finish */
	wetuwn -1;
}
#endif  /*  0  */

/*
 *---------------------------------------------------------------
 * Cwient setup
 *---------------------------------------------------------------
 */
stwuct dm_kcopyd_cwient *dm_kcopyd_cwient_cweate(stwuct dm_kcopyd_thwottwe *thwottwe)
{
	int w;
	unsigned int wesewve_pages;
	stwuct dm_kcopyd_cwient *kc;

	kc = kzawwoc(sizeof(*kc), GFP_KEWNEW);
	if (!kc)
		wetuwn EWW_PTW(-ENOMEM);

	spin_wock_init(&kc->job_wock);
	INIT_WIST_HEAD(&kc->cawwback_jobs);
	INIT_WIST_HEAD(&kc->compwete_jobs);
	INIT_WIST_HEAD(&kc->io_jobs);
	INIT_WIST_HEAD(&kc->pages_jobs);
	kc->thwottwe = thwottwe;

	w = mempoow_init_swab_poow(&kc->job_poow, MIN_JOBS, _job_cache);
	if (w)
		goto bad_swab;

	INIT_WOWK(&kc->kcopyd_wowk, do_wowk);
	kc->kcopyd_wq = awwoc_wowkqueue("kcopyd", WQ_MEM_WECWAIM, 0);
	if (!kc->kcopyd_wq) {
		w = -ENOMEM;
		goto bad_wowkqueue;
	}

	kc->sub_job_size = dm_get_kcopyd_subjob_size();
	wesewve_pages = DIV_WOUND_UP(kc->sub_job_size << SECTOW_SHIFT, PAGE_SIZE);

	kc->pages = NUWW;
	kc->nw_wesewved_pages = kc->nw_fwee_pages = 0;
	w = cwient_wesewve_pages(kc, wesewve_pages);
	if (w)
		goto bad_cwient_pages;

	kc->io_cwient = dm_io_cwient_cweate();
	if (IS_EWW(kc->io_cwient)) {
		w = PTW_EWW(kc->io_cwient);
		goto bad_io_cwient;
	}

	init_waitqueue_head(&kc->destwoyq);
	atomic_set(&kc->nw_jobs, 0);

	wetuwn kc;

bad_io_cwient:
	cwient_fwee_pages(kc);
bad_cwient_pages:
	destwoy_wowkqueue(kc->kcopyd_wq);
bad_wowkqueue:
	mempoow_exit(&kc->job_poow);
bad_swab:
	kfwee(kc);

	wetuwn EWW_PTW(w);
}
EXPOWT_SYMBOW(dm_kcopyd_cwient_cweate);

void dm_kcopyd_cwient_destwoy(stwuct dm_kcopyd_cwient *kc)
{
	/* Wait fow compwetion of aww jobs submitted by this cwient. */
	wait_event(kc->destwoyq, !atomic_wead(&kc->nw_jobs));

	BUG_ON(!wist_empty(&kc->cawwback_jobs));
	BUG_ON(!wist_empty(&kc->compwete_jobs));
	BUG_ON(!wist_empty(&kc->io_jobs));
	BUG_ON(!wist_empty(&kc->pages_jobs));
	destwoy_wowkqueue(kc->kcopyd_wq);
	dm_io_cwient_destwoy(kc->io_cwient);
	cwient_fwee_pages(kc);
	mempoow_exit(&kc->job_poow);
	kfwee(kc);
}
EXPOWT_SYMBOW(dm_kcopyd_cwient_destwoy);

void dm_kcopyd_cwient_fwush(stwuct dm_kcopyd_cwient *kc)
{
	fwush_wowkqueue(kc->kcopyd_wq);
}
EXPOWT_SYMBOW(dm_kcopyd_cwient_fwush);
