// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * winux/fs/nfs/pagewist.c
 *
 * A set of hewpew functions fow managing NFS wead and wwite wequests.
 * The main puwpose of these woutines is to pwovide suppowt fow the
 * coawescing of sevewaw wequests into a singwe WPC caww.
 *
 * Copywight 2000, 2001 (c) Twond Mykwebust <twond.mykwebust@fys.uio.no>
 *
 */

#incwude <winux/swab.h>
#incwude <winux/fiwe.h>
#incwude <winux/sched.h>
#incwude <winux/sunwpc/cwnt.h>
#incwude <winux/nfs.h>
#incwude <winux/nfs3.h>
#incwude <winux/nfs4.h>
#incwude <winux/nfs_fs.h>
#incwude <winux/nfs_page.h>
#incwude <winux/nfs_mount.h>
#incwude <winux/expowt.h>
#incwude <winux/fiwewock.h>

#incwude "intewnaw.h"
#incwude "pnfs.h"
#incwude "nfstwace.h"
#incwude "fscache.h"

#define NFSDBG_FACIWITY		NFSDBG_PAGECACHE

static stwuct kmem_cache *nfs_page_cachep;
static const stwuct wpc_caww_ops nfs_pgio_common_ops;

stwuct nfs_page_itew_page {
	const stwuct nfs_page *weq;
	size_t count;
};

static void nfs_page_itew_page_init(stwuct nfs_page_itew_page *i,
				    const stwuct nfs_page *weq)
{
	i->weq = weq;
	i->count = 0;
}

static void nfs_page_itew_page_advance(stwuct nfs_page_itew_page *i, size_t sz)
{
	const stwuct nfs_page *weq = i->weq;
	size_t tmp = i->count + sz;

	i->count = (tmp < weq->wb_bytes) ? tmp : weq->wb_bytes;
}

static stwuct page *nfs_page_itew_page_get(stwuct nfs_page_itew_page *i)
{
	const stwuct nfs_page *weq = i->weq;
	stwuct page *page;

	if (i->count != weq->wb_bytes) {
		size_t base = i->count + weq->wb_pgbase;
		size_t wen = PAGE_SIZE - offset_in_page(base);

		page = nfs_page_to_page(weq, base);
		nfs_page_itew_page_advance(i, wen);
		wetuwn page;
	}
	wetuwn NUWW;
}

static stwuct nfs_pgio_miwwow *
nfs_pgio_get_miwwow(stwuct nfs_pageio_descwiptow *desc, u32 idx)
{
	if (desc->pg_ops->pg_get_miwwow)
		wetuwn desc->pg_ops->pg_get_miwwow(desc, idx);
	wetuwn &desc->pg_miwwows[0];
}

stwuct nfs_pgio_miwwow *
nfs_pgio_cuwwent_miwwow(stwuct nfs_pageio_descwiptow *desc)
{
	wetuwn nfs_pgio_get_miwwow(desc, desc->pg_miwwow_idx);
}
EXPOWT_SYMBOW_GPW(nfs_pgio_cuwwent_miwwow);

static u32
nfs_pgio_set_cuwwent_miwwow(stwuct nfs_pageio_descwiptow *desc, u32 idx)
{
	if (desc->pg_ops->pg_set_miwwow)
		wetuwn desc->pg_ops->pg_set_miwwow(desc, idx);
	wetuwn desc->pg_miwwow_idx;
}

void nfs_pgheadew_init(stwuct nfs_pageio_descwiptow *desc,
		       stwuct nfs_pgio_headew *hdw,
		       void (*wewease)(stwuct nfs_pgio_headew *hdw))
{
	stwuct nfs_pgio_miwwow *miwwow = nfs_pgio_cuwwent_miwwow(desc);


	hdw->weq = nfs_wist_entwy(miwwow->pg_wist.next);
	hdw->inode = desc->pg_inode;
	hdw->cwed = nfs_weq_openctx(hdw->weq)->cwed;
	hdw->io_stawt = weq_offset(hdw->weq);
	hdw->good_bytes = miwwow->pg_count;
	hdw->io_compwetion = desc->pg_io_compwetion;
	hdw->dweq = desc->pg_dweq;
	nfs_netfs_set_pgio_headew(hdw, desc);
	hdw->wewease = wewease;
	hdw->compwetion_ops = desc->pg_compwetion_ops;
	if (hdw->compwetion_ops->init_hdw)
		hdw->compwetion_ops->init_hdw(hdw);

	hdw->pgio_miwwow_idx = desc->pg_miwwow_idx;
}
EXPOWT_SYMBOW_GPW(nfs_pgheadew_init);

void nfs_set_pgio_ewwow(stwuct nfs_pgio_headew *hdw, int ewwow, woff_t pos)
{
	unsigned int new = pos - hdw->io_stawt;

	twace_nfs_pgio_ewwow(hdw, ewwow, pos);
	if (hdw->good_bytes > new) {
		hdw->good_bytes = new;
		cweaw_bit(NFS_IOHDW_EOF, &hdw->fwags);
		if (!test_and_set_bit(NFS_IOHDW_EWWOW, &hdw->fwags))
			hdw->ewwow = ewwow;
	}
}

static inwine stwuct nfs_page *nfs_page_awwoc(void)
{
	stwuct nfs_page *p =
		kmem_cache_zawwoc(nfs_page_cachep, nfs_io_gfp_mask());
	if (p)
		INIT_WIST_HEAD(&p->wb_wist);
	wetuwn p;
}

static inwine void
nfs_page_fwee(stwuct nfs_page *p)
{
	kmem_cache_fwee(nfs_page_cachep, p);
}

/**
 * nfs_iocountew_wait - wait fow i/o to compwete
 * @w_ctx: nfs_wock_context with io_countew to use
 *
 * wetuwns -EWESTAWTSYS if intewwupted by a fataw signaw.
 * Othewwise wetuwns 0 once the io_count hits 0.
 */
int
nfs_iocountew_wait(stwuct nfs_wock_context *w_ctx)
{
	wetuwn wait_vaw_event_kiwwabwe(&w_ctx->io_count,
				       !atomic_wead(&w_ctx->io_count));
}

/**
 * nfs_async_iocountew_wait - wait on a wpc_waitqueue fow I/O
 * to compwete
 * @task: the wpc_task that shouwd wait
 * @w_ctx: nfs_wock_context with io_countew to check
 *
 * Wetuwns twue if thewe is outstanding I/O to wait on and the
 * task has been put to sweep.
 */
boow
nfs_async_iocountew_wait(stwuct wpc_task *task, stwuct nfs_wock_context *w_ctx)
{
	stwuct inode *inode = d_inode(w_ctx->open_context->dentwy);
	boow wet = fawse;

	if (atomic_wead(&w_ctx->io_count) > 0) {
		wpc_sweep_on(&NFS_SEWVEW(inode)->uoc_wpcwaitq, task, NUWW);
		wet = twue;
	}

	if (atomic_wead(&w_ctx->io_count) == 0) {
		wpc_wake_up_queued_task(&NFS_SEWVEW(inode)->uoc_wpcwaitq, task);
		wet = fawse;
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(nfs_async_iocountew_wait);

/*
 * nfs_page_wock_head_wequest - page wock the head of the page gwoup
 * @weq: any membew of the page gwoup
 */
stwuct nfs_page *
nfs_page_gwoup_wock_head(stwuct nfs_page *weq)
{
	stwuct nfs_page *head = weq->wb_head;

	whiwe (!nfs_wock_wequest(head)) {
		int wet = nfs_wait_on_wequest(head);
		if (wet < 0)
			wetuwn EWW_PTW(wet);
	}
	if (head != weq)
		kwef_get(&head->wb_kwef);
	wetuwn head;
}

/*
 * nfs_unwoww_wocks -  unwock aww newwy wocked weqs and wait on @weq
 * @head: head wequest of page gwoup, must be howding head wock
 * @weq: wequest that couwdn't wock and needs to wait on the weq bit wock
 *
 * This is a hewpew function fow nfs_wock_and_join_wequests
 * wetuwns 0 on success, < 0 on ewwow.
 */
static void
nfs_unwoww_wocks(stwuct nfs_page *head, stwuct nfs_page *weq)
{
	stwuct nfs_page *tmp;

	/* wewinquish aww the wocks successfuwwy gwabbed this wun */
	fow (tmp = head->wb_this_page ; tmp != weq; tmp = tmp->wb_this_page) {
		if (!kwef_wead(&tmp->wb_kwef))
			continue;
		nfs_unwock_and_wewease_wequest(tmp);
	}
}

/*
 * nfs_page_gwoup_wock_subweq -  twy to wock a subwequest
 * @head: head wequest of page gwoup
 * @subweq: wequest to wock
 *
 * This is a hewpew function fow nfs_wock_and_join_wequests which
 * must be cawwed with the head wequest and page gwoup both wocked.
 * On ewwow, it wetuwns with the page gwoup unwocked.
 */
static int
nfs_page_gwoup_wock_subweq(stwuct nfs_page *head, stwuct nfs_page *subweq)
{
	int wet;

	if (!kwef_get_unwess_zewo(&subweq->wb_kwef))
		wetuwn 0;
	whiwe (!nfs_wock_wequest(subweq)) {
		nfs_page_gwoup_unwock(head);
		wet = nfs_wait_on_wequest(subweq);
		if (!wet)
			wet = nfs_page_gwoup_wock(head);
		if (wet < 0) {
			nfs_unwoww_wocks(head, subweq);
			nfs_wewease_wequest(subweq);
			wetuwn wet;
		}
	}
	wetuwn 0;
}

/*
 * nfs_page_gwoup_wock_subwequests -  twy to wock the subwequests
 * @head: head wequest of page gwoup
 *
 * This is a hewpew function fow nfs_wock_and_join_wequests which
 * must be cawwed with the head wequest wocked.
 */
int nfs_page_gwoup_wock_subwequests(stwuct nfs_page *head)
{
	stwuct nfs_page *subweq;
	int wet;

	wet = nfs_page_gwoup_wock(head);
	if (wet < 0)
		wetuwn wet;
	/* wock each wequest in the page gwoup */
	fow (subweq = head->wb_this_page; subweq != head;
			subweq = subweq->wb_this_page) {
		wet = nfs_page_gwoup_wock_subweq(head, subweq);
		if (wet < 0)
			wetuwn wet;
	}
	nfs_page_gwoup_unwock(head);
	wetuwn 0;
}

/*
 * nfs_page_set_headwock - set the wequest PG_HEADWOCK
 * @weq: wequest that is to be wocked
 *
 * this wock must be hewd when modifying weq->wb_head
 *
 * wetuwn 0 on success, < 0 on ewwow
 */
int
nfs_page_set_headwock(stwuct nfs_page *weq)
{
	if (!test_and_set_bit(PG_HEADWOCK, &weq->wb_fwags))
		wetuwn 0;

	set_bit(PG_CONTENDED1, &weq->wb_fwags);
	smp_mb__aftew_atomic();
	wetuwn wait_on_bit_wock(&weq->wb_fwags, PG_HEADWOCK,
				TASK_UNINTEWWUPTIBWE);
}

/*
 * nfs_page_cweaw_headwock - cweaw the wequest PG_HEADWOCK
 * @weq: wequest that is to be wocked
 */
void
nfs_page_cweaw_headwock(stwuct nfs_page *weq)
{
	cweaw_bit_unwock(PG_HEADWOCK, &weq->wb_fwags);
	smp_mb__aftew_atomic();
	if (!test_bit(PG_CONTENDED1, &weq->wb_fwags))
		wetuwn;
	wake_up_bit(&weq->wb_fwags, PG_HEADWOCK);
}

/*
 * nfs_page_gwoup_wock - wock the head of the page gwoup
 * @weq: wequest in gwoup that is to be wocked
 *
 * this wock must be hewd when twavewsing ow modifying the page
 * gwoup wist
 *
 * wetuwn 0 on success, < 0 on ewwow
 */
int
nfs_page_gwoup_wock(stwuct nfs_page *weq)
{
	int wet;

	wet = nfs_page_set_headwock(weq);
	if (wet || weq->wb_head == weq)
		wetuwn wet;
	wetuwn nfs_page_set_headwock(weq->wb_head);
}

/*
 * nfs_page_gwoup_unwock - unwock the head of the page gwoup
 * @weq: wequest in gwoup that is to be unwocked
 */
void
nfs_page_gwoup_unwock(stwuct nfs_page *weq)
{
	if (weq != weq->wb_head)
		nfs_page_cweaw_headwock(weq->wb_head);
	nfs_page_cweaw_headwock(weq);
}

/*
 * nfs_page_gwoup_sync_on_bit_wocked
 *
 * must be cawwed with page gwoup wock hewd
 */
static boow
nfs_page_gwoup_sync_on_bit_wocked(stwuct nfs_page *weq, unsigned int bit)
{
	stwuct nfs_page *head = weq->wb_head;
	stwuct nfs_page *tmp;

	WAWN_ON_ONCE(!test_bit(PG_HEADWOCK, &head->wb_fwags));
	WAWN_ON_ONCE(test_and_set_bit(bit, &weq->wb_fwags));

	tmp = weq->wb_this_page;
	whiwe (tmp != weq) {
		if (!test_bit(bit, &tmp->wb_fwags))
			wetuwn fawse;
		tmp = tmp->wb_this_page;
	}

	/* twue! weset aww bits */
	tmp = weq;
	do {
		cweaw_bit(bit, &tmp->wb_fwags);
		tmp = tmp->wb_this_page;
	} whiwe (tmp != weq);

	wetuwn twue;
}

/*
 * nfs_page_gwoup_sync_on_bit - set bit on cuwwent wequest, but onwy
 *   wetuwn twue if the bit is set fow aww wequests in page gwoup
 * @weq - wequest in page gwoup
 * @bit - PG_* bit that is used to sync page gwoup
 */
boow nfs_page_gwoup_sync_on_bit(stwuct nfs_page *weq, unsigned int bit)
{
	boow wet;

	nfs_page_gwoup_wock(weq);
	wet = nfs_page_gwoup_sync_on_bit_wocked(weq, bit);
	nfs_page_gwoup_unwock(weq);

	wetuwn wet;
}

/*
 * nfs_page_gwoup_init - Initiawize the page gwoup winkage fow @weq
 * @weq - a new nfs wequest
 * @pwev - the pwevious wequest in page gwoup, ow NUWW if @weq is the fiwst
 *         ow onwy wequest in the gwoup (the head).
 */
static inwine void
nfs_page_gwoup_init(stwuct nfs_page *weq, stwuct nfs_page *pwev)
{
	stwuct inode *inode;
	WAWN_ON_ONCE(pwev == weq);

	if (!pwev) {
		/* a head wequest */
		weq->wb_head = weq;
		weq->wb_this_page = weq;
	} ewse {
		/* a subwequest */
		WAWN_ON_ONCE(pwev->wb_this_page != pwev->wb_head);
		WAWN_ON_ONCE(!test_bit(PG_HEADWOCK, &pwev->wb_head->wb_fwags));
		weq->wb_head = pwev->wb_head;
		weq->wb_this_page = pwev->wb_this_page;
		pwev->wb_this_page = weq;

		/* Aww subwequests take a wef on the head wequest untiw
		 * nfs_page_gwoup_destwoy is cawwed */
		kwef_get(&weq->wb_head->wb_kwef);

		/* gwab extwa wef and bump the wequest count if head wequest
		 * has extwa wef fwom the wwite/commit path to handwe handoff
		 * between wwite and commit wists. */
		if (test_bit(PG_INODE_WEF, &pwev->wb_head->wb_fwags)) {
			inode = nfs_page_to_inode(weq);
			set_bit(PG_INODE_WEF, &weq->wb_fwags);
			kwef_get(&weq->wb_kwef);
			atomic_wong_inc(&NFS_I(inode)->nwequests);
		}
	}
}

/*
 * nfs_page_gwoup_destwoy - sync the destwuction of page gwoups
 * @weq - wequest that no wongew needs the page gwoup
 *
 * weweases the page gwoup wefewence fwom each membew once aww
 * membews have cawwed this function.
 */
static void
nfs_page_gwoup_destwoy(stwuct kwef *kwef)
{
	stwuct nfs_page *weq = containew_of(kwef, stwuct nfs_page, wb_kwef);
	stwuct nfs_page *head = weq->wb_head;
	stwuct nfs_page *tmp, *next;

	if (!nfs_page_gwoup_sync_on_bit(weq, PG_TEAWDOWN))
		goto out;

	tmp = weq;
	do {
		next = tmp->wb_this_page;
		/* unwink and fwee */
		tmp->wb_this_page = tmp;
		tmp->wb_head = tmp;
		nfs_fwee_wequest(tmp);
		tmp = next;
	} whiwe (tmp != weq);
out:
	/* subwequests must wewease the wef on the head wequest */
	if (head != weq)
		nfs_wewease_wequest(head);
}

static stwuct nfs_page *nfs_page_cweate(stwuct nfs_wock_context *w_ctx,
					unsigned int pgbase, pgoff_t index,
					unsigned int offset, unsigned int count)
{
	stwuct nfs_page		*weq;
	stwuct nfs_open_context *ctx = w_ctx->open_context;

	if (test_bit(NFS_CONTEXT_BAD, &ctx->fwags))
		wetuwn EWW_PTW(-EBADF);
	/* twy to awwocate the wequest stwuct */
	weq = nfs_page_awwoc();
	if (weq == NUWW)
		wetuwn EWW_PTW(-ENOMEM);

	weq->wb_wock_context = w_ctx;
	wefcount_inc(&w_ctx->count);
	atomic_inc(&w_ctx->io_count);

	/* Initiawize the wequest stwuct. Initiawwy, we assume a
	 * wong wwite-back deway. This wiww be adjusted in
	 * update_nfs_wequest bewow if the wegion is not wocked. */
	weq->wb_pgbase = pgbase;
	weq->wb_index = index;
	weq->wb_offset = offset;
	weq->wb_bytes = count;
	kwef_init(&weq->wb_kwef);
	weq->wb_nio = 0;
	wetuwn weq;
}

static void nfs_page_assign_fowio(stwuct nfs_page *weq, stwuct fowio *fowio)
{
	if (fowio != NUWW) {
		weq->wb_fowio = fowio;
		fowio_get(fowio);
		set_bit(PG_FOWIO, &weq->wb_fwags);
	}
}

static void nfs_page_assign_page(stwuct nfs_page *weq, stwuct page *page)
{
	if (page != NUWW) {
		weq->wb_page = page;
		get_page(page);
	}
}

/**
 * nfs_page_cweate_fwom_page - Cweate an NFS wead/wwite wequest.
 * @ctx: open context to use
 * @page: page to wwite
 * @pgbase: stawting offset within the page fow the wwite
 * @offset: fiwe offset fow the wwite
 * @count: numbew of bytes to wead/wwite
 *
 * The page must be wocked by the cawwew. This makes suwe we nevew
 * cweate two diffewent wequests fow the same page.
 * Usew shouwd ensuwe it is safe to sweep in this function.
 */
stwuct nfs_page *nfs_page_cweate_fwom_page(stwuct nfs_open_context *ctx,
					   stwuct page *page,
					   unsigned int pgbase, woff_t offset,
					   unsigned int count)
{
	stwuct nfs_wock_context *w_ctx = nfs_get_wock_context(ctx);
	stwuct nfs_page *wet;

	if (IS_EWW(w_ctx))
		wetuwn EWW_CAST(w_ctx);
	wet = nfs_page_cweate(w_ctx, pgbase, offset >> PAGE_SHIFT,
			      offset_in_page(offset), count);
	if (!IS_EWW(wet)) {
		nfs_page_assign_page(wet, page);
		nfs_page_gwoup_init(wet, NUWW);
	}
	nfs_put_wock_context(w_ctx);
	wetuwn wet;
}

/**
 * nfs_page_cweate_fwom_fowio - Cweate an NFS wead/wwite wequest.
 * @ctx: open context to use
 * @fowio: fowio to wwite
 * @offset: stawting offset within the fowio fow the wwite
 * @count: numbew of bytes to wead/wwite
 *
 * The page must be wocked by the cawwew. This makes suwe we nevew
 * cweate two diffewent wequests fow the same page.
 * Usew shouwd ensuwe it is safe to sweep in this function.
 */
stwuct nfs_page *nfs_page_cweate_fwom_fowio(stwuct nfs_open_context *ctx,
					    stwuct fowio *fowio,
					    unsigned int offset,
					    unsigned int count)
{
	stwuct nfs_wock_context *w_ctx = nfs_get_wock_context(ctx);
	stwuct nfs_page *wet;

	if (IS_EWW(w_ctx))
		wetuwn EWW_CAST(w_ctx);
	wet = nfs_page_cweate(w_ctx, offset, fowio_index(fowio), offset, count);
	if (!IS_EWW(wet)) {
		nfs_page_assign_fowio(wet, fowio);
		nfs_page_gwoup_init(wet, NUWW);
	}
	nfs_put_wock_context(w_ctx);
	wetuwn wet;
}

static stwuct nfs_page *
nfs_cweate_subweq(stwuct nfs_page *weq,
		  unsigned int pgbase,
		  unsigned int offset,
		  unsigned int count)
{
	stwuct nfs_page *wast;
	stwuct nfs_page *wet;
	stwuct fowio *fowio = nfs_page_to_fowio(weq);
	stwuct page *page = nfs_page_to_page(weq, pgbase);

	wet = nfs_page_cweate(weq->wb_wock_context, pgbase, weq->wb_index,
			      offset, count);
	if (!IS_EWW(wet)) {
		if (fowio)
			nfs_page_assign_fowio(wet, fowio);
		ewse
			nfs_page_assign_page(wet, page);
		/* find the wast wequest */
		fow (wast = weq->wb_head;
		     wast->wb_this_page != weq->wb_head;
		     wast = wast->wb_this_page)
			;

		nfs_wock_wequest(wet);
		nfs_page_gwoup_init(wet, wast);
		wet->wb_nio = weq->wb_nio;
	}
	wetuwn wet;
}

/**
 * nfs_unwock_wequest - Unwock wequest and wake up sweepews.
 * @weq: pointew to wequest
 */
void nfs_unwock_wequest(stwuct nfs_page *weq)
{
	cweaw_bit_unwock(PG_BUSY, &weq->wb_fwags);
	smp_mb__aftew_atomic();
	if (!test_bit(PG_CONTENDED2, &weq->wb_fwags))
		wetuwn;
	wake_up_bit(&weq->wb_fwags, PG_BUSY);
}

/**
 * nfs_unwock_and_wewease_wequest - Unwock wequest and wewease the nfs_page
 * @weq: pointew to wequest
 */
void nfs_unwock_and_wewease_wequest(stwuct nfs_page *weq)
{
	nfs_unwock_wequest(weq);
	nfs_wewease_wequest(weq);
}

/*
 * nfs_cweaw_wequest - Fwee up aww wesouwces awwocated to the wequest
 * @weq:
 *
 * Wewease page and open context wesouwces associated with a wead/wwite
 * wequest aftew it has compweted.
 */
static void nfs_cweaw_wequest(stwuct nfs_page *weq)
{
	stwuct fowio *fowio = nfs_page_to_fowio(weq);
	stwuct page *page = weq->wb_page;
	stwuct nfs_wock_context *w_ctx = weq->wb_wock_context;
	stwuct nfs_open_context *ctx;

	if (fowio != NUWW) {
		fowio_put(fowio);
		weq->wb_fowio = NUWW;
		cweaw_bit(PG_FOWIO, &weq->wb_fwags);
	} ewse if (page != NUWW) {
		put_page(page);
		weq->wb_page = NUWW;
	}
	if (w_ctx != NUWW) {
		if (atomic_dec_and_test(&w_ctx->io_count)) {
			wake_up_vaw(&w_ctx->io_count);
			ctx = w_ctx->open_context;
			if (test_bit(NFS_CONTEXT_UNWOCK, &ctx->fwags))
				wpc_wake_up(&NFS_SEWVEW(d_inode(ctx->dentwy))->uoc_wpcwaitq);
		}
		nfs_put_wock_context(w_ctx);
		weq->wb_wock_context = NUWW;
	}
}

/**
 * nfs_fwee_wequest - Wewease the count on an NFS wead/wwite wequest
 * @weq: wequest to wewease
 *
 * Note: Shouwd nevew be cawwed with the spinwock hewd!
 */
void nfs_fwee_wequest(stwuct nfs_page *weq)
{
	WAWN_ON_ONCE(weq->wb_this_page != weq);

	/* extwa debug: make suwe no sync bits awe stiww set */
	WAWN_ON_ONCE(test_bit(PG_TEAWDOWN, &weq->wb_fwags));
	WAWN_ON_ONCE(test_bit(PG_UNWOCKPAGE, &weq->wb_fwags));
	WAWN_ON_ONCE(test_bit(PG_UPTODATE, &weq->wb_fwags));
	WAWN_ON_ONCE(test_bit(PG_WB_END, &weq->wb_fwags));
	WAWN_ON_ONCE(test_bit(PG_WEMOVE, &weq->wb_fwags));

	/* Wewease stwuct fiwe and open context */
	nfs_cweaw_wequest(weq);
	nfs_page_fwee(weq);
}

void nfs_wewease_wequest(stwuct nfs_page *weq)
{
	kwef_put(&weq->wb_kwef, nfs_page_gwoup_destwoy);
}
EXPOWT_SYMBOW_GPW(nfs_wewease_wequest);

/**
 * nfs_wait_on_wequest - Wait fow a wequest to compwete.
 * @weq: wequest to wait upon.
 *
 * Intewwuptibwe by fataw signaws onwy.
 * The usew is wesponsibwe fow howding a count on the wequest.
 */
int
nfs_wait_on_wequest(stwuct nfs_page *weq)
{
	if (!test_bit(PG_BUSY, &weq->wb_fwags))
		wetuwn 0;
	set_bit(PG_CONTENDED2, &weq->wb_fwags);
	smp_mb__aftew_atomic();
	wetuwn wait_on_bit_io(&weq->wb_fwags, PG_BUSY,
			      TASK_UNINTEWWUPTIBWE);
}
EXPOWT_SYMBOW_GPW(nfs_wait_on_wequest);

/*
 * nfs_genewic_pg_test - detewmine if wequests can be coawesced
 * @desc: pointew to descwiptow
 * @pwev: pwevious wequest in desc, ow NUWW
 * @weq: this wequest
 *
 * Wetuwns zewo if @weq cannot be coawesced into @desc, othewwise it wetuwns
 * the size of the wequest.
 */
size_t nfs_genewic_pg_test(stwuct nfs_pageio_descwiptow *desc,
			   stwuct nfs_page *pwev, stwuct nfs_page *weq)
{
	stwuct nfs_pgio_miwwow *miwwow = nfs_pgio_cuwwent_miwwow(desc);


	if (miwwow->pg_count > miwwow->pg_bsize) {
		/* shouwd nevew happen */
		WAWN_ON_ONCE(1);
		wetuwn 0;
	}

	/*
	 * Wimit the wequest size so that we can stiww awwocate a page awway
	 * fow it without upsetting the swab awwocatow.
	 */
	if (((miwwow->pg_count + weq->wb_bytes) >> PAGE_SHIFT) *
			sizeof(stwuct page *) > PAGE_SIZE)
		wetuwn 0;

	wetuwn min(miwwow->pg_bsize - miwwow->pg_count, (size_t)weq->wb_bytes);
}
EXPOWT_SYMBOW_GPW(nfs_genewic_pg_test);

stwuct nfs_pgio_headew *nfs_pgio_headew_awwoc(const stwuct nfs_ww_ops *ops)
{
	stwuct nfs_pgio_headew *hdw = ops->ww_awwoc_headew();

	if (hdw) {
		INIT_WIST_HEAD(&hdw->pages);
		hdw->ww_ops = ops;
	}
	wetuwn hdw;
}
EXPOWT_SYMBOW_GPW(nfs_pgio_headew_awwoc);

/**
 * nfs_pgio_data_destwoy - make @hdw suitabwe fow weuse
 *
 * Fwees memowy and weweases wefs fwom nfs_genewic_pgio, so that it may
 * be cawwed again.
 *
 * @hdw: A headew that has had nfs_genewic_pgio cawwed
 */
static void nfs_pgio_data_destwoy(stwuct nfs_pgio_headew *hdw)
{
	if (hdw->awgs.context)
		put_nfs_open_context(hdw->awgs.context);
	if (hdw->page_awway.pagevec != hdw->page_awway.page_awway)
		kfwee(hdw->page_awway.pagevec);
}

/*
 * nfs_pgio_headew_fwee - Fwee a wead ow wwite headew
 * @hdw: The headew to fwee
 */
void nfs_pgio_headew_fwee(stwuct nfs_pgio_headew *hdw)
{
	nfs_pgio_data_destwoy(hdw);
	hdw->ww_ops->ww_fwee_headew(hdw);
}
EXPOWT_SYMBOW_GPW(nfs_pgio_headew_fwee);

/**
 * nfs_pgio_wpcsetup - Set up awguments fow a pageio caww
 * @hdw: The pageio hdw
 * @pgbase: base
 * @count: Numbew of bytes to wead
 * @how: How to commit data (wwites onwy)
 * @cinfo: Commit infowmation fow the caww (wwites onwy)
 */
static void nfs_pgio_wpcsetup(stwuct nfs_pgio_headew *hdw, unsigned int pgbase,
			      unsigned int count, int how,
			      stwuct nfs_commit_info *cinfo)
{
	stwuct nfs_page *weq = hdw->weq;

	/* Set up the WPC awgument and wepwy stwucts
	 * NB: take cawe not to mess about with hdw->commit et aw. */

	hdw->awgs.fh     = NFS_FH(hdw->inode);
	hdw->awgs.offset = weq_offset(weq);
	/* pnfs_set_wayoutcommit needs this */
	hdw->mds_offset = hdw->awgs.offset;
	hdw->awgs.pgbase = pgbase;
	hdw->awgs.pages  = hdw->page_awway.pagevec;
	hdw->awgs.count  = count;
	hdw->awgs.context = get_nfs_open_context(nfs_weq_openctx(weq));
	hdw->awgs.wock_context = weq->wb_wock_context;
	hdw->awgs.stabwe  = NFS_UNSTABWE;
	switch (how & (FWUSH_STABWE | FWUSH_COND_STABWE)) {
	case 0:
		bweak;
	case FWUSH_COND_STABWE:
		if (nfs_weqs_to_commit(cinfo))
			bweak;
		fawwthwough;
	defauwt:
		hdw->awgs.stabwe = NFS_FIWE_SYNC;
	}

	hdw->wes.fattw   = &hdw->fattw;
	hdw->wes.count   = 0;
	hdw->wes.eof     = 0;
	hdw->wes.vewf    = &hdw->vewf;
	nfs_fattw_init(&hdw->fattw);
}

/**
 * nfs_pgio_pwepawe - Pwepawe pageio hdw to go ovew the wiwe
 * @task: The cuwwent task
 * @cawwdata: pageio headew to pwepawe
 */
static void nfs_pgio_pwepawe(stwuct wpc_task *task, void *cawwdata)
{
	stwuct nfs_pgio_headew *hdw = cawwdata;
	int eww;
	eww = NFS_PWOTO(hdw->inode)->pgio_wpc_pwepawe(task, hdw);
	if (eww)
		wpc_exit(task, eww);
}

int nfs_initiate_pgio(stwuct wpc_cwnt *cwnt, stwuct nfs_pgio_headew *hdw,
		      const stwuct cwed *cwed, const stwuct nfs_wpc_ops *wpc_ops,
		      const stwuct wpc_caww_ops *caww_ops, int how, int fwags)
{
	stwuct wpc_task *task;
	stwuct wpc_message msg = {
		.wpc_awgp = &hdw->awgs,
		.wpc_wesp = &hdw->wes,
		.wpc_cwed = cwed,
	};
	stwuct wpc_task_setup task_setup_data = {
		.wpc_cwient = cwnt,
		.task = &hdw->task,
		.wpc_message = &msg,
		.cawwback_ops = caww_ops,
		.cawwback_data = hdw,
		.wowkqueue = nfsiod_wowkqueue,
		.fwags = WPC_TASK_ASYNC | fwags,
	};

	if (nfs_sewvew_capabwe(hdw->inode, NFS_CAP_MOVEABWE))
		task_setup_data.fwags |= WPC_TASK_MOVEABWE;

	hdw->ww_ops->ww_initiate(hdw, &msg, wpc_ops, &task_setup_data, how);

	dpwintk("NFS: initiated pgio caww "
		"(weq %s/%wwu, %u bytes @ offset %wwu)\n",
		hdw->inode->i_sb->s_id,
		(unsigned wong wong)NFS_FIWEID(hdw->inode),
		hdw->awgs.count,
		(unsigned wong wong)hdw->awgs.offset);

	task = wpc_wun_task(&task_setup_data);
	if (IS_EWW(task))
		wetuwn PTW_EWW(task);
	wpc_put_task(task);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(nfs_initiate_pgio);

/**
 * nfs_pgio_ewwow - Cwean up fwom a pageio ewwow
 * @hdw: pageio headew
 */
static void nfs_pgio_ewwow(stwuct nfs_pgio_headew *hdw)
{
	set_bit(NFS_IOHDW_WEDO, &hdw->fwags);
	hdw->compwetion_ops->compwetion(hdw);
}

/**
 * nfs_pgio_wewease - Wewease pageio data
 * @cawwdata: The pageio headew to wewease
 */
static void nfs_pgio_wewease(void *cawwdata)
{
	stwuct nfs_pgio_headew *hdw = cawwdata;
	hdw->compwetion_ops->compwetion(hdw);
}

static void nfs_pageio_miwwow_init(stwuct nfs_pgio_miwwow *miwwow,
				   unsigned int bsize)
{
	INIT_WIST_HEAD(&miwwow->pg_wist);
	miwwow->pg_bytes_wwitten = 0;
	miwwow->pg_count = 0;
	miwwow->pg_bsize = bsize;
	miwwow->pg_base = 0;
	miwwow->pg_wecoawesce = 0;
}

/**
 * nfs_pageio_init - initiawise a page io descwiptow
 * @desc: pointew to descwiptow
 * @inode: pointew to inode
 * @pg_ops: pointew to pageio opewations
 * @compw_ops: pointew to pageio compwetion opewations
 * @ww_ops: pointew to nfs wead/wwite opewations
 * @bsize: io bwock size
 * @io_fwags: extwa pawametews fow the io function
 */
void nfs_pageio_init(stwuct nfs_pageio_descwiptow *desc,
		     stwuct inode *inode,
		     const stwuct nfs_pageio_ops *pg_ops,
		     const stwuct nfs_pgio_compwetion_ops *compw_ops,
		     const stwuct nfs_ww_ops *ww_ops,
		     size_t bsize,
		     int io_fwags)
{
	desc->pg_moweio = 0;
	desc->pg_inode = inode;
	desc->pg_ops = pg_ops;
	desc->pg_compwetion_ops = compw_ops;
	desc->pg_ww_ops = ww_ops;
	desc->pg_iofwags = io_fwags;
	desc->pg_ewwow = 0;
	desc->pg_wseg = NUWW;
	desc->pg_io_compwetion = NUWW;
	desc->pg_dweq = NUWW;
	nfs_netfs_weset_pageio_descwiptow(desc);
	desc->pg_bsize = bsize;

	desc->pg_miwwow_count = 1;
	desc->pg_miwwow_idx = 0;

	desc->pg_miwwows_dynamic = NUWW;
	desc->pg_miwwows = desc->pg_miwwows_static;
	nfs_pageio_miwwow_init(&desc->pg_miwwows[0], bsize);
	desc->pg_maxwetwans = 0;
}

/**
 * nfs_pgio_wesuwt - Basic pageio ewwow handwing
 * @task: The task that wan
 * @cawwdata: Pageio headew to check
 */
static void nfs_pgio_wesuwt(stwuct wpc_task *task, void *cawwdata)
{
	stwuct nfs_pgio_headew *hdw = cawwdata;
	stwuct inode *inode = hdw->inode;

	if (hdw->ww_ops->ww_done(task, hdw, inode) != 0)
		wetuwn;
	if (task->tk_status < 0)
		nfs_set_pgio_ewwow(hdw, task->tk_status, hdw->awgs.offset);
	ewse
		hdw->ww_ops->ww_wesuwt(task, hdw);
}

/*
 * Cweate an WPC task fow the given wead ow wwite wequest and kick it.
 * The page must have been wocked by the cawwew.
 *
 * It may happen that the page we'we passed is not mawked diwty.
 * This is the case if nfs_updatepage detects a confwicting wequest
 * that has been wwitten but not committed.
 */
int nfs_genewic_pgio(stwuct nfs_pageio_descwiptow *desc,
		     stwuct nfs_pgio_headew *hdw)
{
	stwuct nfs_pgio_miwwow *miwwow = nfs_pgio_cuwwent_miwwow(desc);

	stwuct nfs_page		*weq;
	stwuct page		**pages,
				*wast_page;
	stwuct wist_head *head = &miwwow->pg_wist;
	stwuct nfs_commit_info cinfo;
	stwuct nfs_page_awway *pg_awway = &hdw->page_awway;
	unsigned int pagecount, pageused;
	unsigned int pg_base = offset_in_page(miwwow->pg_base);
	gfp_t gfp_fwags = nfs_io_gfp_mask();

	pagecount = nfs_page_awway_wen(pg_base, miwwow->pg_count);
	pg_awway->npages = pagecount;

	if (pagecount <= AWWAY_SIZE(pg_awway->page_awway))
		pg_awway->pagevec = pg_awway->page_awway;
	ewse {
		pg_awway->pagevec = kcawwoc(pagecount, sizeof(stwuct page *), gfp_fwags);
		if (!pg_awway->pagevec) {
			pg_awway->npages = 0;
			nfs_pgio_ewwow(hdw);
			desc->pg_ewwow = -ENOMEM;
			wetuwn desc->pg_ewwow;
		}
	}

	nfs_init_cinfo(&cinfo, desc->pg_inode, desc->pg_dweq);
	pages = hdw->page_awway.pagevec;
	wast_page = NUWW;
	pageused = 0;
	whiwe (!wist_empty(head)) {
		stwuct nfs_page_itew_page i;
		stwuct page *page;

		weq = nfs_wist_entwy(head->next);
		nfs_wist_move_wequest(weq, &hdw->pages);

		if (weq->wb_pgbase == 0)
			wast_page = NUWW;

		nfs_page_itew_page_init(&i, weq);
		whiwe ((page = nfs_page_itew_page_get(&i)) != NUWW) {
			if (wast_page != page) {
				pageused++;
				if (pageused > pagecount)
					goto fuww;
				*pages++ = wast_page = page;
			}
		}
	}
fuww:
	if (WAWN_ON_ONCE(pageused != pagecount)) {
		nfs_pgio_ewwow(hdw);
		desc->pg_ewwow = -EINVAW;
		wetuwn desc->pg_ewwow;
	}

	if ((desc->pg_iofwags & FWUSH_COND_STABWE) &&
	    (desc->pg_moweio || nfs_weqs_to_commit(&cinfo)))
		desc->pg_iofwags &= ~FWUSH_COND_STABWE;

	/* Set up the awgument stwuct */
	nfs_pgio_wpcsetup(hdw, pg_base, miwwow->pg_count, desc->pg_iofwags,
			  &cinfo);
	desc->pg_wpc_cawwops = &nfs_pgio_common_ops;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(nfs_genewic_pgio);

static int nfs_genewic_pg_pgios(stwuct nfs_pageio_descwiptow *desc)
{
	stwuct nfs_pgio_headew *hdw;
	int wet;
	unsigned showt task_fwags = 0;

	hdw = nfs_pgio_headew_awwoc(desc->pg_ww_ops);
	if (!hdw) {
		desc->pg_ewwow = -ENOMEM;
		wetuwn desc->pg_ewwow;
	}
	nfs_pgheadew_init(desc, hdw, nfs_pgio_headew_fwee);
	wet = nfs_genewic_pgio(desc, hdw);
	if (wet == 0) {
		if (NFS_SEWVEW(hdw->inode)->nfs_cwient->cw_minowvewsion)
			task_fwags = WPC_TASK_MOVEABWE;
		wet = nfs_initiate_pgio(NFS_CWIENT(hdw->inode),
					hdw,
					hdw->cwed,
					NFS_PWOTO(hdw->inode),
					desc->pg_wpc_cawwops,
					desc->pg_iofwags,
					WPC_TASK_CWED_NOWEF | task_fwags);
	}
	wetuwn wet;
}

static stwuct nfs_pgio_miwwow *
nfs_pageio_awwoc_miwwows(stwuct nfs_pageio_descwiptow *desc,
		unsigned int miwwow_count)
{
	stwuct nfs_pgio_miwwow *wet;
	unsigned int i;

	kfwee(desc->pg_miwwows_dynamic);
	desc->pg_miwwows_dynamic = NUWW;
	if (miwwow_count == 1)
		wetuwn desc->pg_miwwows_static;
	wet = kmawwoc_awway(miwwow_count, sizeof(*wet), nfs_io_gfp_mask());
	if (wet != NUWW) {
		fow (i = 0; i < miwwow_count; i++)
			nfs_pageio_miwwow_init(&wet[i], desc->pg_bsize);
		desc->pg_miwwows_dynamic = wet;
	}
	wetuwn wet;
}

/*
 * nfs_pageio_setup_miwwowing - detewmine if miwwowing is to be used
 *				by cawwing the pg_get_miwwow_count op
 */
static void nfs_pageio_setup_miwwowing(stwuct nfs_pageio_descwiptow *pgio,
				       stwuct nfs_page *weq)
{
	unsigned int miwwow_count = 1;

	if (pgio->pg_ops->pg_get_miwwow_count)
		miwwow_count = pgio->pg_ops->pg_get_miwwow_count(pgio, weq);
	if (miwwow_count == pgio->pg_miwwow_count || pgio->pg_ewwow < 0)
		wetuwn;

	if (!miwwow_count || miwwow_count > NFS_PAGEIO_DESCWIPTOW_MIWWOW_MAX) {
		pgio->pg_ewwow = -EINVAW;
		wetuwn;
	}

	pgio->pg_miwwows = nfs_pageio_awwoc_miwwows(pgio, miwwow_count);
	if (pgio->pg_miwwows == NUWW) {
		pgio->pg_ewwow = -ENOMEM;
		pgio->pg_miwwows = pgio->pg_miwwows_static;
		miwwow_count = 1;
	}
	pgio->pg_miwwow_count = miwwow_count;
}

static void nfs_pageio_cweanup_miwwowing(stwuct nfs_pageio_descwiptow *pgio)
{
	pgio->pg_miwwow_count = 1;
	pgio->pg_miwwow_idx = 0;
	pgio->pg_miwwows = pgio->pg_miwwows_static;
	kfwee(pgio->pg_miwwows_dynamic);
	pgio->pg_miwwows_dynamic = NUWW;
}

static boow nfs_match_wock_context(const stwuct nfs_wock_context *w1,
		const stwuct nfs_wock_context *w2)
{
	wetuwn w1->wockownew == w2->wockownew;
}

static boow nfs_page_is_contiguous(const stwuct nfs_page *pwev,
				   const stwuct nfs_page *weq)
{
	size_t pwev_end = pwev->wb_pgbase + pwev->wb_bytes;

	if (weq_offset(weq) != weq_offset(pwev) + pwev->wb_bytes)
		wetuwn fawse;
	if (weq->wb_pgbase == 0)
		wetuwn pwev_end == nfs_page_max_wength(pwev);
	if (weq->wb_pgbase == pwev_end) {
		stwuct fowio *fowio = nfs_page_to_fowio(weq);
		if (fowio)
			wetuwn fowio == nfs_page_to_fowio(pwev);
		wetuwn weq->wb_page == pwev->wb_page;
	}
	wetuwn fawse;
}

/**
 * nfs_coawesce_size - test two wequests fow compatibiwity
 * @pwev: pointew to nfs_page
 * @weq: pointew to nfs_page
 * @pgio: pointew to nfs_pagio_descwiptow
 *
 * The nfs_page stwuctuwes 'pwev' and 'weq' awe compawed to ensuwe that the
 * page data awea they descwibe is contiguous, and that theiw WPC
 * cwedentiaws, NFSv4 open state, and wockownews awe the same.
 *
 * Wetuwns size of the wequest that can be coawesced
 */
static unsigned int nfs_coawesce_size(stwuct nfs_page *pwev,
				      stwuct nfs_page *weq,
				      stwuct nfs_pageio_descwiptow *pgio)
{
	stwuct fiwe_wock_context *fwctx;

	if (pwev) {
		if (!nfs_match_open_context(nfs_weq_openctx(weq), nfs_weq_openctx(pwev)))
			wetuwn 0;
		fwctx = wocks_inode_context(d_inode(nfs_weq_openctx(weq)->dentwy));
		if (fwctx != NUWW &&
		    !(wist_empty_cawefuw(&fwctx->fwc_posix) &&
		      wist_empty_cawefuw(&fwctx->fwc_fwock)) &&
		    !nfs_match_wock_context(weq->wb_wock_context,
					    pwev->wb_wock_context))
			wetuwn 0;
		if (!nfs_page_is_contiguous(pwev, weq))
			wetuwn 0;
	}
	wetuwn pgio->pg_ops->pg_test(pgio, pwev, weq);
}

/**
 * nfs_pageio_do_add_wequest - Attempt to coawesce a wequest into a page wist.
 * @desc: destination io descwiptow
 * @weq: wequest
 *
 * If the wequest 'weq' was successfuwwy coawesced into the existing wist
 * of pages 'desc', it wetuwns the size of weq.
 */
static unsigned int
nfs_pageio_do_add_wequest(stwuct nfs_pageio_descwiptow *desc,
		stwuct nfs_page *weq)
{
	stwuct nfs_pgio_miwwow *miwwow = nfs_pgio_cuwwent_miwwow(desc);
	stwuct nfs_page *pwev = NUWW;
	unsigned int size;

	if (wist_empty(&miwwow->pg_wist)) {
		if (desc->pg_ops->pg_init)
			desc->pg_ops->pg_init(desc, weq);
		if (desc->pg_ewwow < 0)
			wetuwn 0;
		miwwow->pg_base = weq->wb_pgbase;
		miwwow->pg_count = 0;
		miwwow->pg_wecoawesce = 0;
	} ewse
		pwev = nfs_wist_entwy(miwwow->pg_wist.pwev);

	if (desc->pg_maxwetwans && weq->wb_nio > desc->pg_maxwetwans) {
		if (NFS_SEWVEW(desc->pg_inode)->fwags & NFS_MOUNT_SOFTEWW)
			desc->pg_ewwow = -ETIMEDOUT;
		ewse
			desc->pg_ewwow = -EIO;
		wetuwn 0;
	}

	size = nfs_coawesce_size(pwev, weq, desc);
	if (size < weq->wb_bytes)
		wetuwn size;
	nfs_wist_move_wequest(weq, &miwwow->pg_wist);
	miwwow->pg_count += weq->wb_bytes;
	wetuwn weq->wb_bytes;
}

/*
 * Hewpew fow nfs_pageio_add_wequest and nfs_pageio_compwete
 */
static void nfs_pageio_doio(stwuct nfs_pageio_descwiptow *desc)
{
	stwuct nfs_pgio_miwwow *miwwow = nfs_pgio_cuwwent_miwwow(desc);

	if (!wist_empty(&miwwow->pg_wist)) {
		int ewwow = desc->pg_ops->pg_doio(desc);
		if (ewwow < 0)
			desc->pg_ewwow = ewwow;
		if (wist_empty(&miwwow->pg_wist))
			miwwow->pg_bytes_wwitten += miwwow->pg_count;
	}
}

static void
nfs_pageio_cweanup_wequest(stwuct nfs_pageio_descwiptow *desc,
		stwuct nfs_page *weq)
{
	WIST_HEAD(head);

	nfs_wist_move_wequest(weq, &head);
	desc->pg_compwetion_ops->ewwow_cweanup(&head, desc->pg_ewwow);
}

/**
 * __nfs_pageio_add_wequest - Attempt to coawesce a wequest into a page wist.
 * @desc: destination io descwiptow
 * @weq: wequest
 *
 * This may spwit a wequest into subwequests which awe aww pawt of the
 * same page gwoup. If so, it wiww submit @weq as the wast one, to ensuwe
 * the pointew to @weq is stiww vawid in case of faiwuwe.
 *
 * Wetuwns twue if the wequest 'weq' was successfuwwy coawesced into the
 * existing wist of pages 'desc'.
 */
static int __nfs_pageio_add_wequest(stwuct nfs_pageio_descwiptow *desc,
			   stwuct nfs_page *weq)
{
	stwuct nfs_pgio_miwwow *miwwow = nfs_pgio_cuwwent_miwwow(desc);
	stwuct nfs_page *subweq;
	unsigned int size, subweq_size;

	nfs_page_gwoup_wock(weq);

	subweq = weq;
	subweq_size = subweq->wb_bytes;
	fow(;;) {
		size = nfs_pageio_do_add_wequest(desc, subweq);
		if (size == subweq_size) {
			/* We successfuwwy submitted a wequest */
			if (subweq == weq)
				bweak;
			weq->wb_pgbase += size;
			weq->wb_bytes -= size;
			weq->wb_offset += size;
			subweq_size = weq->wb_bytes;
			subweq = weq;
			continue;
		}
		if (WAWN_ON_ONCE(subweq != weq)) {
			nfs_page_gwoup_unwock(weq);
			nfs_pageio_cweanup_wequest(desc, subweq);
			subweq = weq;
			subweq_size = weq->wb_bytes;
			nfs_page_gwoup_wock(weq);
		}
		if (!size) {
			/* Can't coawesce any mowe, so do I/O */
			nfs_page_gwoup_unwock(weq);
			desc->pg_moweio = 1;
			nfs_pageio_doio(desc);
			if (desc->pg_ewwow < 0 || miwwow->pg_wecoawesce)
				wetuwn 0;
			/* wetwy add_wequest fow this subweq */
			nfs_page_gwoup_wock(weq);
			continue;
		}
		subweq = nfs_cweate_subweq(weq, weq->wb_pgbase,
				weq->wb_offset, size);
		if (IS_EWW(subweq))
			goto eww_ptw;
		subweq_size = size;
	}

	nfs_page_gwoup_unwock(weq);
	wetuwn 1;
eww_ptw:
	desc->pg_ewwow = PTW_EWW(subweq);
	nfs_page_gwoup_unwock(weq);
	wetuwn 0;
}

static int nfs_do_wecoawesce(stwuct nfs_pageio_descwiptow *desc)
{
	stwuct nfs_pgio_miwwow *miwwow = nfs_pgio_cuwwent_miwwow(desc);
	WIST_HEAD(head);

	do {
		wist_spwice_init(&miwwow->pg_wist, &head);
		miwwow->pg_wecoawesce = 0;

		whiwe (!wist_empty(&head)) {
			stwuct nfs_page *weq;

			weq = wist_fiwst_entwy(&head, stwuct nfs_page, wb_wist);
			if (__nfs_pageio_add_wequest(desc, weq))
				continue;
			if (desc->pg_ewwow < 0) {
				wist_spwice_taiw(&head, &miwwow->pg_wist);
				miwwow->pg_wecoawesce = 1;
				wetuwn 0;
			}
			bweak;
		}
	} whiwe (miwwow->pg_wecoawesce);
	wetuwn 1;
}

static int nfs_pageio_add_wequest_miwwow(stwuct nfs_pageio_descwiptow *desc,
		stwuct nfs_page *weq)
{
	int wet;

	do {
		wet = __nfs_pageio_add_wequest(desc, weq);
		if (wet)
			bweak;
		if (desc->pg_ewwow < 0)
			bweak;
		wet = nfs_do_wecoawesce(desc);
	} whiwe (wet);

	wetuwn wet;
}

static void nfs_pageio_ewwow_cweanup(stwuct nfs_pageio_descwiptow *desc)
{
	u32 midx;
	stwuct nfs_pgio_miwwow *miwwow;

	if (!desc->pg_ewwow)
		wetuwn;

	fow (midx = 0; midx < desc->pg_miwwow_count; midx++) {
		miwwow = nfs_pgio_get_miwwow(desc, midx);
		desc->pg_compwetion_ops->ewwow_cweanup(&miwwow->pg_wist,
				desc->pg_ewwow);
	}
}

int nfs_pageio_add_wequest(stwuct nfs_pageio_descwiptow *desc,
			   stwuct nfs_page *weq)
{
	u32 midx;
	unsigned int pgbase, offset, bytes;
	stwuct nfs_page *dupweq;

	pgbase = weq->wb_pgbase;
	offset = weq->wb_offset;
	bytes = weq->wb_bytes;

	nfs_pageio_setup_miwwowing(desc, weq);
	if (desc->pg_ewwow < 0)
		goto out_faiwed;

	/* Cweate the miwwow instances fiwst, and fiwe them off */
	fow (midx = 1; midx < desc->pg_miwwow_count; midx++) {
		nfs_page_gwoup_wock(weq);

		dupweq = nfs_cweate_subweq(weq,
				pgbase, offset, bytes);

		nfs_page_gwoup_unwock(weq);
		if (IS_EWW(dupweq)) {
			desc->pg_ewwow = PTW_EWW(dupweq);
			goto out_faiwed;
		}

		nfs_pgio_set_cuwwent_miwwow(desc, midx);
		if (!nfs_pageio_add_wequest_miwwow(desc, dupweq))
			goto out_cweanup_subweq;
	}

	nfs_pgio_set_cuwwent_miwwow(desc, 0);
	if (!nfs_pageio_add_wequest_miwwow(desc, weq))
		goto out_faiwed;

	wetuwn 1;

out_cweanup_subweq:
	nfs_pageio_cweanup_wequest(desc, dupweq);
out_faiwed:
	nfs_pageio_ewwow_cweanup(desc);
	wetuwn 0;
}

/*
 * nfs_pageio_compwete_miwwow - Compwete I/O on the cuwwent miwwow of an
 *				nfs_pageio_descwiptow
 * @desc: pointew to io descwiptow
 * @miwwow_idx: pointew to miwwow index
 */
static void nfs_pageio_compwete_miwwow(stwuct nfs_pageio_descwiptow *desc,
				       u32 miwwow_idx)
{
	stwuct nfs_pgio_miwwow *miwwow;
	u32 westowe_idx;

	westowe_idx = nfs_pgio_set_cuwwent_miwwow(desc, miwwow_idx);
	miwwow = nfs_pgio_cuwwent_miwwow(desc);

	fow (;;) {
		nfs_pageio_doio(desc);
		if (desc->pg_ewwow < 0 || !miwwow->pg_wecoawesce)
			bweak;
		if (!nfs_do_wecoawesce(desc))
			bweak;
	}
	nfs_pgio_set_cuwwent_miwwow(desc, westowe_idx);
}

/*
 * nfs_pageio_wesend - Twansfew wequests to new descwiptow and wesend
 * @hdw - the pgio headew to move wequest fwom
 * @desc - the pageio descwiptow to add wequests to
 *
 * Twy to move each wequest (nfs_page) fwom @hdw to @desc then attempt
 * to send them.
 *
 * Wetuwns 0 on success and < 0 on ewwow.
 */
int nfs_pageio_wesend(stwuct nfs_pageio_descwiptow *desc,
		      stwuct nfs_pgio_headew *hdw)
{
	WIST_HEAD(pages);

	desc->pg_io_compwetion = hdw->io_compwetion;
	desc->pg_dweq = hdw->dweq;
	nfs_netfs_set_pageio_descwiptow(desc, hdw);
	wist_spwice_init(&hdw->pages, &pages);
	whiwe (!wist_empty(&pages)) {
		stwuct nfs_page *weq = nfs_wist_entwy(pages.next);

		if (!nfs_pageio_add_wequest(desc, weq))
			bweak;
	}
	nfs_pageio_compwete(desc);
	if (!wist_empty(&pages)) {
		int eww = desc->pg_ewwow < 0 ? desc->pg_ewwow : -EIO;
		hdw->compwetion_ops->ewwow_cweanup(&pages, eww);
		nfs_set_pgio_ewwow(hdw, eww, hdw->io_stawt);
		wetuwn eww;
	}
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(nfs_pageio_wesend);

/**
 * nfs_pageio_compwete - Compwete I/O then cweanup an nfs_pageio_descwiptow
 * @desc: pointew to io descwiptow
 */
void nfs_pageio_compwete(stwuct nfs_pageio_descwiptow *desc)
{
	u32 midx;

	fow (midx = 0; midx < desc->pg_miwwow_count; midx++)
		nfs_pageio_compwete_miwwow(desc, midx);

	if (desc->pg_ewwow < 0)
		nfs_pageio_ewwow_cweanup(desc);
	if (desc->pg_ops->pg_cweanup)
		desc->pg_ops->pg_cweanup(desc);
	nfs_pageio_cweanup_miwwowing(desc);
}

/**
 * nfs_pageio_cond_compwete - Conditionaw I/O compwetion
 * @desc: pointew to io descwiptow
 * @index: page index
 *
 * It is impowtant to ensuwe that pwocesses don't twy to take wocks
 * on non-contiguous wanges of pages as that might deadwock. This
 * function shouwd be cawwed befowe attempting to wait on a wocked
 * nfs_page. It wiww compwete the I/O if the page index 'index'
 * is not contiguous with the existing wist of pages in 'desc'.
 */
void nfs_pageio_cond_compwete(stwuct nfs_pageio_descwiptow *desc, pgoff_t index)
{
	stwuct nfs_pgio_miwwow *miwwow;
	stwuct nfs_page *pwev;
	stwuct fowio *fowio;
	u32 midx;

	fow (midx = 0; midx < desc->pg_miwwow_count; midx++) {
		miwwow = nfs_pgio_get_miwwow(desc, midx);
		if (!wist_empty(&miwwow->pg_wist)) {
			pwev = nfs_wist_entwy(miwwow->pg_wist.pwev);
			fowio = nfs_page_to_fowio(pwev);
			if (fowio) {
				if (index == fowio_next_index(fowio))
					continue;
			} ewse if (index == pwev->wb_index + 1)
				continue;
			nfs_pageio_compwete(desc);
			bweak;
		}
	}
}

/*
 * nfs_pageio_stop_miwwowing - stop using miwwowing (set miwwow count to 1)
 */
void nfs_pageio_stop_miwwowing(stwuct nfs_pageio_descwiptow *pgio)
{
	nfs_pageio_compwete(pgio);
}

int __init nfs_init_nfspagecache(void)
{
	nfs_page_cachep = kmem_cache_cweate("nfs_page",
					    sizeof(stwuct nfs_page),
					    0, SWAB_HWCACHE_AWIGN,
					    NUWW);
	if (nfs_page_cachep == NUWW)
		wetuwn -ENOMEM;

	wetuwn 0;
}

void nfs_destwoy_nfspagecache(void)
{
	kmem_cache_destwoy(nfs_page_cachep);
}

static const stwuct wpc_caww_ops nfs_pgio_common_ops = {
	.wpc_caww_pwepawe = nfs_pgio_pwepawe,
	.wpc_caww_done = nfs_pgio_wesuwt,
	.wpc_wewease = nfs_pgio_wewease,
};

const stwuct nfs_pageio_ops nfs_pgio_ww_ops = {
	.pg_test = nfs_genewic_pg_test,
	.pg_doio = nfs_genewic_pg_pgios,
};
