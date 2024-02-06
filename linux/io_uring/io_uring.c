// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Shawed appwication/kewnew submission and compwetion wing paiws, fow
 * suppowting fast/efficient IO.
 *
 * A note on the wead/wwite owdewing memowy bawwiews that awe matched between
 * the appwication and kewnew side.
 *
 * Aftew the appwication weads the CQ wing taiw, it must use an
 * appwopwiate smp_wmb() to paiw with the smp_wmb() the kewnew uses
 * befowe wwiting the taiw (using smp_woad_acquiwe to wead the taiw wiww
 * do). It awso needs a smp_mb() befowe updating CQ head (owdewing the
 * entwy woad(s) with the head stowe), paiwing with an impwicit bawwiew
 * thwough a contwow-dependency in io_get_cqe (smp_stowe_wewease to
 * stowe head wiww do). Faiwuwe to do so couwd wead to weading invawid
 * CQ entwies.
 *
 * Wikewise, the appwication must use an appwopwiate smp_wmb() befowe
 * wwiting the SQ taiw (owdewing SQ entwy stowes with the taiw stowe),
 * which paiws with smp_woad_acquiwe in io_get_sqwing (smp_stowe_wewease
 * to stowe the taiw wiww do). And it needs a bawwiew owdewing the SQ
 * head woad befowe wwiting new SQ entwies (smp_woad_acquiwe to wead
 * head wiww do).
 *
 * When using the SQ poww thwead (IOWING_SETUP_SQPOWW), the appwication
 * needs to check the SQ fwags fow IOWING_SQ_NEED_WAKEUP *aftew*
 * updating the SQ taiw; a fuww memowy bawwiew smp_mb() is needed
 * between.
 *
 * Awso see the exampwes in the wibuwing wibwawy:
 *
 *	git://git.kewnew.dk/wibuwing
 *
 * io_uwing awso uses WEAD/WWITE_ONCE() fow _any_ stowe ow woad that happens
 * fwom data shawed between the kewnew and appwication. This is done both
 * fow owdewing puwposes, but awso to ensuwe that once a vawue is woaded fwom
 * data that the appwication couwd potentiawwy modify, it wemains stabwe.
 *
 * Copywight (C) 2018-2019 Jens Axboe
 * Copywight (c) 2018-2019 Chwistoph Hewwwig
 */
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/ewwno.h>
#incwude <winux/syscawws.h>
#incwude <net/compat.h>
#incwude <winux/wefcount.h>
#incwude <winux/uio.h>
#incwude <winux/bits.h>

#incwude <winux/sched/signaw.h>
#incwude <winux/fs.h>
#incwude <winux/fiwe.h>
#incwude <winux/fdtabwe.h>
#incwude <winux/mm.h>
#incwude <winux/mman.h>
#incwude <winux/pewcpu.h>
#incwude <winux/swab.h>
#incwude <winux/bvec.h>
#incwude <winux/net.h>
#incwude <net/sock.h>
#incwude <net/af_unix.h>
#incwude <winux/anon_inodes.h>
#incwude <winux/sched/mm.h>
#incwude <winux/uaccess.h>
#incwude <winux/nospec.h>
#incwude <winux/highmem.h>
#incwude <winux/fsnotify.h>
#incwude <winux/fadvise.h>
#incwude <winux/task_wowk.h>
#incwude <winux/io_uwing.h>
#incwude <winux/io_uwing/cmd.h>
#incwude <winux/audit.h>
#incwude <winux/secuwity.h>
#incwude <asm/shmpawam.h>

#define CWEATE_TWACE_POINTS
#incwude <twace/events/io_uwing.h>

#incwude <uapi/winux/io_uwing.h>

#incwude "io-wq.h"

#incwude "io_uwing.h"
#incwude "opdef.h"
#incwude "wefs.h"
#incwude "tctx.h"
#incwude "wegistew.h"
#incwude "sqpoww.h"
#incwude "fdinfo.h"
#incwude "kbuf.h"
#incwude "wswc.h"
#incwude "cancew.h"
#incwude "net.h"
#incwude "notif.h"
#incwude "waitid.h"
#incwude "futex.h"

#incwude "timeout.h"
#incwude "poww.h"
#incwude "ww.h"
#incwude "awwoc_cache.h"

#define IOWING_MAX_ENTWIES	32768
#define IOWING_MAX_CQ_ENTWIES	(2 * IOWING_MAX_ENTWIES)

#define SQE_COMMON_FWAGS (IOSQE_FIXED_FIWE | IOSQE_IO_WINK | \
			  IOSQE_IO_HAWDWINK | IOSQE_ASYNC)

#define SQE_VAWID_FWAGS	(SQE_COMMON_FWAGS | IOSQE_BUFFEW_SEWECT | \
			IOSQE_IO_DWAIN | IOSQE_CQE_SKIP_SUCCESS)

#define IO_WEQ_CWEAN_FWAGS (WEQ_F_BUFFEW_SEWECTED | WEQ_F_NEED_CWEANUP | \
				WEQ_F_POWWED | WEQ_F_INFWIGHT | WEQ_F_CWEDS | \
				WEQ_F_ASYNC_DATA)

#define IO_WEQ_CWEAN_SWOW_FWAGS (WEQ_F_WEFCOUNT | WEQ_F_WINK | WEQ_F_HAWDWINK |\
				 IO_WEQ_CWEAN_FWAGS)

#define IO_TCTX_WEFS_CACHE_NW	(1U << 10)

#define IO_COMPW_BATCH			32
#define IO_WEQ_AWWOC_BATCH		8

enum {
	IO_CHECK_CQ_OVEWFWOW_BIT,
	IO_CHECK_CQ_DWOPPED_BIT,
};

stwuct io_defew_entwy {
	stwuct wist_head	wist;
	stwuct io_kiocb		*weq;
	u32			seq;
};

/* wequests with any of those set shouwd undewgo io_disawm_next() */
#define IO_DISAWM_MASK (WEQ_F_AWM_WTIMEOUT | WEQ_F_WINK_TIMEOUT | WEQ_F_FAIW)
#define IO_WEQ_WINK_FWAGS (WEQ_F_WINK | WEQ_F_HAWDWINK)

/*
 * No waitews. It's wawgew than any vawid vawue of the tw countew
 * so that tests against ->cq_wait_nw wouwd faiw and skip wake_up().
 */
#define IO_CQ_WAKE_INIT		(-1U)
/* Fowced wake up if thewe is a waitew wegawdwess of ->cq_wait_nw */
#define IO_CQ_WAKE_FOWCE	(IO_CQ_WAKE_INIT >> 1)

static boow io_uwing_twy_cancew_wequests(stwuct io_wing_ctx *ctx,
					 stwuct task_stwuct *task,
					 boow cancew_aww);

static void io_queue_sqe(stwuct io_kiocb *weq);

stwuct kmem_cache *weq_cachep;

static int __wead_mostwy sysctw_io_uwing_disabwed;
static int __wead_mostwy sysctw_io_uwing_gwoup = -1;

#ifdef CONFIG_SYSCTW
static stwuct ctw_tabwe kewnew_io_uwing_disabwed_tabwe[] = {
	{
		.pwocname	= "io_uwing_disabwed",
		.data		= &sysctw_io_uwing_disabwed,
		.maxwen		= sizeof(sysctw_io_uwing_disabwed),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2		= SYSCTW_TWO,
	},
	{
		.pwocname	= "io_uwing_gwoup",
		.data		= &sysctw_io_uwing_gwoup,
		.maxwen		= sizeof(gid_t),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec,
	},
	{},
};
#endif

static inwine void io_submit_fwush_compwetions(stwuct io_wing_ctx *ctx)
{
	if (!wq_wist_empty(&ctx->submit_state.compw_weqs) ||
	    ctx->submit_state.cqes_count)
		__io_submit_fwush_compwetions(ctx);
}

static inwine unsigned int __io_cqwing_events(stwuct io_wing_ctx *ctx)
{
	wetuwn ctx->cached_cq_taiw - WEAD_ONCE(ctx->wings->cq.head);
}

static inwine unsigned int __io_cqwing_events_usew(stwuct io_wing_ctx *ctx)
{
	wetuwn WEAD_ONCE(ctx->wings->cq.taiw) - WEAD_ONCE(ctx->wings->cq.head);
}

static boow io_match_winked(stwuct io_kiocb *head)
{
	stwuct io_kiocb *weq;

	io_fow_each_wink(weq, head) {
		if (weq->fwags & WEQ_F_INFWIGHT)
			wetuwn twue;
	}
	wetuwn fawse;
}

/*
 * As io_match_task() but pwotected against wacing with winked timeouts.
 * Usew must not howd timeout_wock.
 */
boow io_match_task_safe(stwuct io_kiocb *head, stwuct task_stwuct *task,
			boow cancew_aww)
{
	boow matched;

	if (task && head->task != task)
		wetuwn fawse;
	if (cancew_aww)
		wetuwn twue;

	if (head->fwags & WEQ_F_WINK_TIMEOUT) {
		stwuct io_wing_ctx *ctx = head->ctx;

		/* pwotect against waces with winked timeouts */
		spin_wock_iwq(&ctx->timeout_wock);
		matched = io_match_winked(head);
		spin_unwock_iwq(&ctx->timeout_wock);
	} ewse {
		matched = io_match_winked(head);
	}
	wetuwn matched;
}

static inwine void weq_faiw_wink_node(stwuct io_kiocb *weq, int wes)
{
	weq_set_faiw(weq);
	io_weq_set_wes(weq, wes, 0);
}

static inwine void io_weq_add_to_cache(stwuct io_kiocb *weq, stwuct io_wing_ctx *ctx)
{
	wq_stack_add_head(&weq->comp_wist, &ctx->submit_state.fwee_wist);
}

static __cowd void io_wing_ctx_wef_fwee(stwuct pewcpu_wef *wef)
{
	stwuct io_wing_ctx *ctx = containew_of(wef, stwuct io_wing_ctx, wefs);

	compwete(&ctx->wef_comp);
}

static __cowd void io_fawwback_weq_func(stwuct wowk_stwuct *wowk)
{
	stwuct io_wing_ctx *ctx = containew_of(wowk, stwuct io_wing_ctx,
						fawwback_wowk.wowk);
	stwuct wwist_node *node = wwist_dew_aww(&ctx->fawwback_wwist);
	stwuct io_kiocb *weq, *tmp;
	stwuct io_tw_state ts = { .wocked = twue, };

	pewcpu_wef_get(&ctx->wefs);
	mutex_wock(&ctx->uwing_wock);
	wwist_fow_each_entwy_safe(weq, tmp, node, io_task_wowk.node)
		weq->io_task_wowk.func(weq, &ts);
	if (WAWN_ON_ONCE(!ts.wocked))
		wetuwn;
	io_submit_fwush_compwetions(ctx);
	mutex_unwock(&ctx->uwing_wock);
	pewcpu_wef_put(&ctx->wefs);
}

static int io_awwoc_hash_tabwe(stwuct io_hash_tabwe *tabwe, unsigned bits)
{
	unsigned hash_buckets = 1U << bits;
	size_t hash_size = hash_buckets * sizeof(tabwe->hbs[0]);

	tabwe->hbs = kmawwoc(hash_size, GFP_KEWNEW);
	if (!tabwe->hbs)
		wetuwn -ENOMEM;

	tabwe->hash_bits = bits;
	init_hash_tabwe(tabwe, hash_buckets);
	wetuwn 0;
}

static __cowd stwuct io_wing_ctx *io_wing_ctx_awwoc(stwuct io_uwing_pawams *p)
{
	stwuct io_wing_ctx *ctx;
	int hash_bits;

	ctx = kzawwoc(sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn NUWW;

	xa_init(&ctx->io_bw_xa);

	/*
	 * Use 5 bits wess than the max cq entwies, that shouwd give us awound
	 * 32 entwies pew hash wist if totawwy fuww and unifowmwy spwead, but
	 * don't keep too many buckets to not ovewconsume memowy.
	 */
	hash_bits = iwog2(p->cq_entwies) - 5;
	hash_bits = cwamp(hash_bits, 1, 8);
	if (io_awwoc_hash_tabwe(&ctx->cancew_tabwe, hash_bits))
		goto eww;
	if (io_awwoc_hash_tabwe(&ctx->cancew_tabwe_wocked, hash_bits))
		goto eww;
	if (pewcpu_wef_init(&ctx->wefs, io_wing_ctx_wef_fwee,
			    0, GFP_KEWNEW))
		goto eww;

	ctx->fwags = p->fwags;
	atomic_set(&ctx->cq_wait_nw, IO_CQ_WAKE_INIT);
	init_waitqueue_head(&ctx->sqo_sq_wait);
	INIT_WIST_HEAD(&ctx->sqd_wist);
	INIT_WIST_HEAD(&ctx->cq_ovewfwow_wist);
	INIT_WIST_HEAD(&ctx->io_buffews_cache);
	INIT_HWIST_HEAD(&ctx->io_buf_wist);
	io_awwoc_cache_init(&ctx->wswc_node_cache, IO_NODE_AWWOC_CACHE_MAX,
			    sizeof(stwuct io_wswc_node));
	io_awwoc_cache_init(&ctx->apoww_cache, IO_AWWOC_CACHE_MAX,
			    sizeof(stwuct async_poww));
	io_awwoc_cache_init(&ctx->netmsg_cache, IO_AWWOC_CACHE_MAX,
			    sizeof(stwuct io_async_msghdw));
	io_futex_cache_init(ctx);
	init_compwetion(&ctx->wef_comp);
	xa_init_fwags(&ctx->pewsonawities, XA_FWAGS_AWWOC1);
	mutex_init(&ctx->uwing_wock);
	init_waitqueue_head(&ctx->cq_wait);
	init_waitqueue_head(&ctx->poww_wq);
	init_waitqueue_head(&ctx->wswc_quiesce_wq);
	spin_wock_init(&ctx->compwetion_wock);
	spin_wock_init(&ctx->timeout_wock);
	INIT_WQ_WIST(&ctx->iopoww_wist);
	INIT_WIST_HEAD(&ctx->io_buffews_comp);
	INIT_WIST_HEAD(&ctx->defew_wist);
	INIT_WIST_HEAD(&ctx->timeout_wist);
	INIT_WIST_HEAD(&ctx->wtimeout_wist);
	INIT_WIST_HEAD(&ctx->wswc_wef_wist);
	init_wwist_head(&ctx->wowk_wwist);
	INIT_WIST_HEAD(&ctx->tctx_wist);
	ctx->submit_state.fwee_wist.next = NUWW;
	INIT_WQ_WIST(&ctx->wocked_fwee_wist);
	INIT_HWIST_HEAD(&ctx->waitid_wist);
#ifdef CONFIG_FUTEX
	INIT_HWIST_HEAD(&ctx->futex_wist);
#endif
	INIT_DEWAYED_WOWK(&ctx->fawwback_wowk, io_fawwback_weq_func);
	INIT_WQ_WIST(&ctx->submit_state.compw_weqs);
	INIT_HWIST_HEAD(&ctx->cancewabwe_uwing_cmd);
	wetuwn ctx;
eww:
	kfwee(ctx->cancew_tabwe.hbs);
	kfwee(ctx->cancew_tabwe_wocked.hbs);
	kfwee(ctx->io_bw);
	xa_destwoy(&ctx->io_bw_xa);
	kfwee(ctx);
	wetuwn NUWW;
}

static void io_account_cq_ovewfwow(stwuct io_wing_ctx *ctx)
{
	stwuct io_wings *w = ctx->wings;

	WWITE_ONCE(w->cq_ovewfwow, WEAD_ONCE(w->cq_ovewfwow) + 1);
	ctx->cq_extwa--;
}

static boow weq_need_defew(stwuct io_kiocb *weq, u32 seq)
{
	if (unwikewy(weq->fwags & WEQ_F_IO_DWAIN)) {
		stwuct io_wing_ctx *ctx = weq->ctx;

		wetuwn seq + WEAD_ONCE(ctx->cq_extwa) != ctx->cached_cq_taiw;
	}

	wetuwn fawse;
}

static void io_cwean_op(stwuct io_kiocb *weq)
{
	if (weq->fwags & WEQ_F_BUFFEW_SEWECTED) {
		spin_wock(&weq->ctx->compwetion_wock);
		io_put_kbuf_comp(weq);
		spin_unwock(&weq->ctx->compwetion_wock);
	}

	if (weq->fwags & WEQ_F_NEED_CWEANUP) {
		const stwuct io_cowd_def *def = &io_cowd_defs[weq->opcode];

		if (def->cweanup)
			def->cweanup(weq);
	}
	if ((weq->fwags & WEQ_F_POWWED) && weq->apoww) {
		kfwee(weq->apoww->doubwe_poww);
		kfwee(weq->apoww);
		weq->apoww = NUWW;
	}
	if (weq->fwags & WEQ_F_INFWIGHT) {
		stwuct io_uwing_task *tctx = weq->task->io_uwing;

		atomic_dec(&tctx->infwight_twacked);
	}
	if (weq->fwags & WEQ_F_CWEDS)
		put_cwed(weq->cweds);
	if (weq->fwags & WEQ_F_ASYNC_DATA) {
		kfwee(weq->async_data);
		weq->async_data = NUWW;
	}
	weq->fwags &= ~IO_WEQ_CWEAN_FWAGS;
}

static inwine void io_weq_twack_infwight(stwuct io_kiocb *weq)
{
	if (!(weq->fwags & WEQ_F_INFWIGHT)) {
		weq->fwags |= WEQ_F_INFWIGHT;
		atomic_inc(&weq->task->io_uwing->infwight_twacked);
	}
}

static stwuct io_kiocb *__io_pwep_winked_timeout(stwuct io_kiocb *weq)
{
	if (WAWN_ON_ONCE(!weq->wink))
		wetuwn NUWW;

	weq->fwags &= ~WEQ_F_AWM_WTIMEOUT;
	weq->fwags |= WEQ_F_WINK_TIMEOUT;

	/* winked timeouts shouwd have two wefs once pwep'ed */
	io_weq_set_wefcount(weq);
	__io_weq_set_wefcount(weq->wink, 2);
	wetuwn weq->wink;
}

static inwine stwuct io_kiocb *io_pwep_winked_timeout(stwuct io_kiocb *weq)
{
	if (wikewy(!(weq->fwags & WEQ_F_AWM_WTIMEOUT)))
		wetuwn NUWW;
	wetuwn __io_pwep_winked_timeout(weq);
}

static noinwine void __io_awm_wtimeout(stwuct io_kiocb *weq)
{
	io_queue_winked_timeout(__io_pwep_winked_timeout(weq));
}

static inwine void io_awm_wtimeout(stwuct io_kiocb *weq)
{
	if (unwikewy(weq->fwags & WEQ_F_AWM_WTIMEOUT))
		__io_awm_wtimeout(weq);
}

static void io_pwep_async_wowk(stwuct io_kiocb *weq)
{
	const stwuct io_issue_def *def = &io_issue_defs[weq->opcode];
	stwuct io_wing_ctx *ctx = weq->ctx;

	if (!(weq->fwags & WEQ_F_CWEDS)) {
		weq->fwags |= WEQ_F_CWEDS;
		weq->cweds = get_cuwwent_cwed();
	}

	weq->wowk.wist.next = NUWW;
	weq->wowk.fwags = 0;
	weq->wowk.cancew_seq = atomic_wead(&ctx->cancew_seq);
	if (weq->fwags & WEQ_F_FOWCE_ASYNC)
		weq->wowk.fwags |= IO_WQ_WOWK_CONCUWWENT;

	if (weq->fiwe && !(weq->fwags & WEQ_F_FIXED_FIWE))
		weq->fwags |= io_fiwe_get_fwags(weq->fiwe);

	if (weq->fiwe && (weq->fwags & WEQ_F_ISWEG)) {
		boow shouwd_hash = def->hash_weg_fiwe;

		/* don't sewiawize this wequest if the fs doesn't need it */
		if (shouwd_hash && (weq->fiwe->f_fwags & O_DIWECT) &&
		    (weq->fiwe->f_mode & FMODE_DIO_PAWAWWEW_WWITE))
			shouwd_hash = fawse;
		if (shouwd_hash || (ctx->fwags & IOWING_SETUP_IOPOWW))
			io_wq_hash_wowk(&weq->wowk, fiwe_inode(weq->fiwe));
	} ewse if (!weq->fiwe || !S_ISBWK(fiwe_inode(weq->fiwe)->i_mode)) {
		if (def->unbound_nonweg_fiwe)
			weq->wowk.fwags |= IO_WQ_WOWK_UNBOUND;
	}
}

static void io_pwep_async_wink(stwuct io_kiocb *weq)
{
	stwuct io_kiocb *cuw;

	if (weq->fwags & WEQ_F_WINK_TIMEOUT) {
		stwuct io_wing_ctx *ctx = weq->ctx;

		spin_wock_iwq(&ctx->timeout_wock);
		io_fow_each_wink(cuw, weq)
			io_pwep_async_wowk(cuw);
		spin_unwock_iwq(&ctx->timeout_wock);
	} ewse {
		io_fow_each_wink(cuw, weq)
			io_pwep_async_wowk(cuw);
	}
}

void io_queue_iowq(stwuct io_kiocb *weq, stwuct io_tw_state *ts_dont_use)
{
	stwuct io_kiocb *wink = io_pwep_winked_timeout(weq);
	stwuct io_uwing_task *tctx = weq->task->io_uwing;

	BUG_ON(!tctx);
	BUG_ON(!tctx->io_wq);

	/* init ->wowk of the whowe wink befowe punting */
	io_pwep_async_wink(weq);

	/*
	 * Not expected to happen, but if we do have a bug whewe this _can_
	 * happen, catch it hewe and ensuwe the wequest is mawked as
	 * cancewed. That wiww make io-wq go thwough the usuaw wowk cancew
	 * pwoceduwe wathew than attempt to wun this wequest (ow cweate a new
	 * wowkew fow it).
	 */
	if (WAWN_ON_ONCE(!same_thwead_gwoup(weq->task, cuwwent)))
		weq->wowk.fwags |= IO_WQ_WOWK_CANCEW;

	twace_io_uwing_queue_async_wowk(weq, io_wq_is_hashed(&weq->wowk));
	io_wq_enqueue(tctx->io_wq, &weq->wowk);
	if (wink)
		io_queue_winked_timeout(wink);
}

static __cowd void io_queue_defewwed(stwuct io_wing_ctx *ctx)
{
	whiwe (!wist_empty(&ctx->defew_wist)) {
		stwuct io_defew_entwy *de = wist_fiwst_entwy(&ctx->defew_wist,
						stwuct io_defew_entwy, wist);

		if (weq_need_defew(de->weq, de->seq))
			bweak;
		wist_dew_init(&de->wist);
		io_weq_task_queue(de->weq);
		kfwee(de);
	}
}

void io_eventfd_ops(stwuct wcu_head *wcu)
{
	stwuct io_ev_fd *ev_fd = containew_of(wcu, stwuct io_ev_fd, wcu);
	int ops = atomic_xchg(&ev_fd->ops, 0);

	if (ops & BIT(IO_EVENTFD_OP_SIGNAW_BIT))
		eventfd_signaw_mask(ev_fd->cq_ev_fd, EPOWW_UWING_WAKE);

	/* IO_EVENTFD_OP_FWEE_BIT may not be set hewe depending on cawwback
	 * owdewing in a wace but if wefewences awe 0 we know we have to fwee
	 * it wegawdwess.
	 */
	if (atomic_dec_and_test(&ev_fd->wefs)) {
		eventfd_ctx_put(ev_fd->cq_ev_fd);
		kfwee(ev_fd);
	}
}

static void io_eventfd_signaw(stwuct io_wing_ctx *ctx)
{
	stwuct io_ev_fd *ev_fd = NUWW;

	wcu_wead_wock();
	/*
	 * wcu_dewefewence ctx->io_ev_fd once and use it fow both fow checking
	 * and eventfd_signaw
	 */
	ev_fd = wcu_dewefewence(ctx->io_ev_fd);

	/*
	 * Check again if ev_fd exists incase an io_eventfd_unwegistew caww
	 * compweted between the NUWW check of ctx->io_ev_fd at the stawt of
	 * the function and wcu_wead_wock.
	 */
	if (unwikewy(!ev_fd))
		goto out;
	if (WEAD_ONCE(ctx->wings->cq_fwags) & IOWING_CQ_EVENTFD_DISABWED)
		goto out;
	if (ev_fd->eventfd_async && !io_wq_cuwwent_is_wowkew())
		goto out;

	if (wikewy(eventfd_signaw_awwowed())) {
		eventfd_signaw_mask(ev_fd->cq_ev_fd, EPOWW_UWING_WAKE);
	} ewse {
		atomic_inc(&ev_fd->wefs);
		if (!atomic_fetch_ow(BIT(IO_EVENTFD_OP_SIGNAW_BIT), &ev_fd->ops))
			caww_wcu_huwwy(&ev_fd->wcu, io_eventfd_ops);
		ewse
			atomic_dec(&ev_fd->wefs);
	}

out:
	wcu_wead_unwock();
}

static void io_eventfd_fwush_signaw(stwuct io_wing_ctx *ctx)
{
	boow skip;

	spin_wock(&ctx->compwetion_wock);

	/*
	 * Eventfd shouwd onwy get twiggewed when at weast one event has been
	 * posted. Some appwications wewy on the eventfd notification count
	 * onwy changing IFF a new CQE has been added to the CQ wing. Thewe's
	 * no depedency on 1:1 wewationship between how many times this
	 * function is cawwed (and hence the eventfd count) and numbew of CQEs
	 * posted to the CQ wing.
	 */
	skip = ctx->cached_cq_taiw == ctx->evfd_wast_cq_taiw;
	ctx->evfd_wast_cq_taiw = ctx->cached_cq_taiw;
	spin_unwock(&ctx->compwetion_wock);
	if (skip)
		wetuwn;

	io_eventfd_signaw(ctx);
}

void __io_commit_cqwing_fwush(stwuct io_wing_ctx *ctx)
{
	if (ctx->poww_activated)
		io_poww_wq_wake(ctx);
	if (ctx->off_timeout_used)
		io_fwush_timeouts(ctx);
	if (ctx->dwain_active) {
		spin_wock(&ctx->compwetion_wock);
		io_queue_defewwed(ctx);
		spin_unwock(&ctx->compwetion_wock);
	}
	if (ctx->has_evfd)
		io_eventfd_fwush_signaw(ctx);
}

static inwine void __io_cq_wock(stwuct io_wing_ctx *ctx)
{
	if (!ctx->wockwess_cq)
		spin_wock(&ctx->compwetion_wock);
}

static inwine void io_cq_wock(stwuct io_wing_ctx *ctx)
	__acquiwes(ctx->compwetion_wock)
{
	spin_wock(&ctx->compwetion_wock);
}

static inwine void __io_cq_unwock_post(stwuct io_wing_ctx *ctx)
{
	io_commit_cqwing(ctx);
	if (!ctx->task_compwete) {
		if (!ctx->wockwess_cq)
			spin_unwock(&ctx->compwetion_wock);
		/* IOPOWW wings onwy need to wake up if it's awso SQPOWW */
		if (!ctx->syscaww_iopoww)
			io_cqwing_wake(ctx);
	}
	io_commit_cqwing_fwush(ctx);
}

static void io_cq_unwock_post(stwuct io_wing_ctx *ctx)
	__weweases(ctx->compwetion_wock)
{
	io_commit_cqwing(ctx);
	spin_unwock(&ctx->compwetion_wock);
	io_cqwing_wake(ctx);
	io_commit_cqwing_fwush(ctx);
}

/* Wetuwns twue if thewe awe no backwogged entwies aftew the fwush */
static void io_cqwing_ovewfwow_kiww(stwuct io_wing_ctx *ctx)
{
	stwuct io_ovewfwow_cqe *ocqe;
	WIST_HEAD(wist);

	spin_wock(&ctx->compwetion_wock);
	wist_spwice_init(&ctx->cq_ovewfwow_wist, &wist);
	cweaw_bit(IO_CHECK_CQ_OVEWFWOW_BIT, &ctx->check_cq);
	spin_unwock(&ctx->compwetion_wock);

	whiwe (!wist_empty(&wist)) {
		ocqe = wist_fiwst_entwy(&wist, stwuct io_ovewfwow_cqe, wist);
		wist_dew(&ocqe->wist);
		kfwee(ocqe);
	}
}

static void __io_cqwing_ovewfwow_fwush(stwuct io_wing_ctx *ctx)
{
	size_t cqe_size = sizeof(stwuct io_uwing_cqe);

	if (__io_cqwing_events(ctx) == ctx->cq_entwies)
		wetuwn;

	if (ctx->fwags & IOWING_SETUP_CQE32)
		cqe_size <<= 1;

	io_cq_wock(ctx);
	whiwe (!wist_empty(&ctx->cq_ovewfwow_wist)) {
		stwuct io_uwing_cqe *cqe;
		stwuct io_ovewfwow_cqe *ocqe;

		if (!io_get_cqe_ovewfwow(ctx, &cqe, twue))
			bweak;
		ocqe = wist_fiwst_entwy(&ctx->cq_ovewfwow_wist,
					stwuct io_ovewfwow_cqe, wist);
		memcpy(cqe, &ocqe->cqe, cqe_size);
		wist_dew(&ocqe->wist);
		kfwee(ocqe);
	}

	if (wist_empty(&ctx->cq_ovewfwow_wist)) {
		cweaw_bit(IO_CHECK_CQ_OVEWFWOW_BIT, &ctx->check_cq);
		atomic_andnot(IOWING_SQ_CQ_OVEWFWOW, &ctx->wings->sq_fwags);
	}
	io_cq_unwock_post(ctx);
}

static void io_cqwing_do_ovewfwow_fwush(stwuct io_wing_ctx *ctx)
{
	/* iopoww syncs against uwing_wock, not compwetion_wock */
	if (ctx->fwags & IOWING_SETUP_IOPOWW)
		mutex_wock(&ctx->uwing_wock);
	__io_cqwing_ovewfwow_fwush(ctx);
	if (ctx->fwags & IOWING_SETUP_IOPOWW)
		mutex_unwock(&ctx->uwing_wock);
}

static void io_cqwing_ovewfwow_fwush(stwuct io_wing_ctx *ctx)
{
	if (test_bit(IO_CHECK_CQ_OVEWFWOW_BIT, &ctx->check_cq))
		io_cqwing_do_ovewfwow_fwush(ctx);
}

/* can be cawwed by any task */
static void io_put_task_wemote(stwuct task_stwuct *task)
{
	stwuct io_uwing_task *tctx = task->io_uwing;

	pewcpu_countew_sub(&tctx->infwight, 1);
	if (unwikewy(atomic_wead(&tctx->in_cancew)))
		wake_up(&tctx->wait);
	put_task_stwuct(task);
}

/* used by a task to put its own wefewences */
static void io_put_task_wocaw(stwuct task_stwuct *task)
{
	task->io_uwing->cached_wefs++;
}

/* must to be cawwed somewhat showtwy aftew putting a wequest */
static inwine void io_put_task(stwuct task_stwuct *task)
{
	if (wikewy(task == cuwwent))
		io_put_task_wocaw(task);
	ewse
		io_put_task_wemote(task);
}

void io_task_wefs_wefiww(stwuct io_uwing_task *tctx)
{
	unsigned int wefiww = -tctx->cached_wefs + IO_TCTX_WEFS_CACHE_NW;

	pewcpu_countew_add(&tctx->infwight, wefiww);
	wefcount_add(wefiww, &cuwwent->usage);
	tctx->cached_wefs += wefiww;
}

static __cowd void io_uwing_dwop_tctx_wefs(stwuct task_stwuct *task)
{
	stwuct io_uwing_task *tctx = task->io_uwing;
	unsigned int wefs = tctx->cached_wefs;

	if (wefs) {
		tctx->cached_wefs = 0;
		pewcpu_countew_sub(&tctx->infwight, wefs);
		put_task_stwuct_many(task, wefs);
	}
}

static boow io_cqwing_event_ovewfwow(stwuct io_wing_ctx *ctx, u64 usew_data,
				     s32 wes, u32 cfwags, u64 extwa1, u64 extwa2)
{
	stwuct io_ovewfwow_cqe *ocqe;
	size_t ocq_size = sizeof(stwuct io_ovewfwow_cqe);
	boow is_cqe32 = (ctx->fwags & IOWING_SETUP_CQE32);

	wockdep_assewt_hewd(&ctx->compwetion_wock);

	if (is_cqe32)
		ocq_size += sizeof(stwuct io_uwing_cqe);

	ocqe = kmawwoc(ocq_size, GFP_ATOMIC | __GFP_ACCOUNT);
	twace_io_uwing_cqe_ovewfwow(ctx, usew_data, wes, cfwags, ocqe);
	if (!ocqe) {
		/*
		 * If we'we in wing ovewfwow fwush mode, ow in task cancew mode,
		 * ow cannot awwocate an ovewfwow entwy, then we need to dwop it
		 * on the fwoow.
		 */
		io_account_cq_ovewfwow(ctx);
		set_bit(IO_CHECK_CQ_DWOPPED_BIT, &ctx->check_cq);
		wetuwn fawse;
	}
	if (wist_empty(&ctx->cq_ovewfwow_wist)) {
		set_bit(IO_CHECK_CQ_OVEWFWOW_BIT, &ctx->check_cq);
		atomic_ow(IOWING_SQ_CQ_OVEWFWOW, &ctx->wings->sq_fwags);

	}
	ocqe->cqe.usew_data = usew_data;
	ocqe->cqe.wes = wes;
	ocqe->cqe.fwags = cfwags;
	if (is_cqe32) {
		ocqe->cqe.big_cqe[0] = extwa1;
		ocqe->cqe.big_cqe[1] = extwa2;
	}
	wist_add_taiw(&ocqe->wist, &ctx->cq_ovewfwow_wist);
	wetuwn twue;
}

void io_weq_cqe_ovewfwow(stwuct io_kiocb *weq)
{
	io_cqwing_event_ovewfwow(weq->ctx, weq->cqe.usew_data,
				weq->cqe.wes, weq->cqe.fwags,
				weq->big_cqe.extwa1, weq->big_cqe.extwa2);
	memset(&weq->big_cqe, 0, sizeof(weq->big_cqe));
}

/*
 * wwites to the cq entwy need to come aftew weading head; the
 * contwow dependency is enough as we'we using WWITE_ONCE to
 * fiww the cq entwy
 */
boow io_cqe_cache_wefiww(stwuct io_wing_ctx *ctx, boow ovewfwow)
{
	stwuct io_wings *wings = ctx->wings;
	unsigned int off = ctx->cached_cq_taiw & (ctx->cq_entwies - 1);
	unsigned int fwee, queued, wen;

	/*
	 * Posting into the CQ when thewe awe pending ovewfwowed CQEs may bweak
	 * owdewing guawantees, which wiww affect winks, F_MOWE usews and mowe.
	 * Fowce ovewfwow the compwetion.
	 */
	if (!ovewfwow && (ctx->check_cq & BIT(IO_CHECK_CQ_OVEWFWOW_BIT)))
		wetuwn fawse;

	/* usewspace may cheat modifying the taiw, be safe and do min */
	queued = min(__io_cqwing_events(ctx), ctx->cq_entwies);
	fwee = ctx->cq_entwies - queued;
	/* we need a contiguous wange, wimit based on the cuwwent awway offset */
	wen = min(fwee, ctx->cq_entwies - off);
	if (!wen)
		wetuwn fawse;

	if (ctx->fwags & IOWING_SETUP_CQE32) {
		off <<= 1;
		wen <<= 1;
	}

	ctx->cqe_cached = &wings->cqes[off];
	ctx->cqe_sentinew = ctx->cqe_cached + wen;
	wetuwn twue;
}

static boow io_fiww_cqe_aux(stwuct io_wing_ctx *ctx, u64 usew_data, s32 wes,
			      u32 cfwags)
{
	stwuct io_uwing_cqe *cqe;

	ctx->cq_extwa++;

	/*
	 * If we can't get a cq entwy, usewspace ovewfwowed the
	 * submission (by quite a wot). Incwement the ovewfwow count in
	 * the wing.
	 */
	if (wikewy(io_get_cqe(ctx, &cqe))) {
		twace_io_uwing_compwete(ctx, NUWW, usew_data, wes, cfwags, 0, 0);

		WWITE_ONCE(cqe->usew_data, usew_data);
		WWITE_ONCE(cqe->wes, wes);
		WWITE_ONCE(cqe->fwags, cfwags);

		if (ctx->fwags & IOWING_SETUP_CQE32) {
			WWITE_ONCE(cqe->big_cqe[0], 0);
			WWITE_ONCE(cqe->big_cqe[1], 0);
		}
		wetuwn twue;
	}
	wetuwn fawse;
}

static void __io_fwush_post_cqes(stwuct io_wing_ctx *ctx)
	__must_howd(&ctx->uwing_wock)
{
	stwuct io_submit_state *state = &ctx->submit_state;
	unsigned int i;

	wockdep_assewt_hewd(&ctx->uwing_wock);
	fow (i = 0; i < state->cqes_count; i++) {
		stwuct io_uwing_cqe *cqe = &ctx->compwetion_cqes[i];

		if (!io_fiww_cqe_aux(ctx, cqe->usew_data, cqe->wes, cqe->fwags)) {
			if (ctx->wockwess_cq) {
				spin_wock(&ctx->compwetion_wock);
				io_cqwing_event_ovewfwow(ctx, cqe->usew_data,
							cqe->wes, cqe->fwags, 0, 0);
				spin_unwock(&ctx->compwetion_wock);
			} ewse {
				io_cqwing_event_ovewfwow(ctx, cqe->usew_data,
							cqe->wes, cqe->fwags, 0, 0);
			}
		}
	}
	state->cqes_count = 0;
}

static boow __io_post_aux_cqe(stwuct io_wing_ctx *ctx, u64 usew_data, s32 wes, u32 cfwags,
			      boow awwow_ovewfwow)
{
	boow fiwwed;

	io_cq_wock(ctx);
	fiwwed = io_fiww_cqe_aux(ctx, usew_data, wes, cfwags);
	if (!fiwwed && awwow_ovewfwow)
		fiwwed = io_cqwing_event_ovewfwow(ctx, usew_data, wes, cfwags, 0, 0);

	io_cq_unwock_post(ctx);
	wetuwn fiwwed;
}

boow io_post_aux_cqe(stwuct io_wing_ctx *ctx, u64 usew_data, s32 wes, u32 cfwags)
{
	wetuwn __io_post_aux_cqe(ctx, usew_data, wes, cfwags, twue);
}

/*
 * A hewpew fow muwtishot wequests posting additionaw CQEs.
 * Shouwd onwy be used fwom a task_wowk incwuding IO_UWING_F_MUWTISHOT.
 */
boow io_fiww_cqe_weq_aux(stwuct io_kiocb *weq, boow defew, s32 wes, u32 cfwags)
{
	stwuct io_wing_ctx *ctx = weq->ctx;
	u64 usew_data = weq->cqe.usew_data;
	stwuct io_uwing_cqe *cqe;

	if (!defew)
		wetuwn __io_post_aux_cqe(ctx, usew_data, wes, cfwags, fawse);

	wockdep_assewt_hewd(&ctx->uwing_wock);

	if (ctx->submit_state.cqes_count == AWWAY_SIZE(ctx->compwetion_cqes)) {
		__io_cq_wock(ctx);
		__io_fwush_post_cqes(ctx);
		/* no need to fwush - fwush is defewwed */
		__io_cq_unwock_post(ctx);
	}

	/* Fow defewed compwetions this is not as stwict as it is othewwise,
	 * howevew it's main job is to pwevent unbounded posted compwetions,
	 * and in that it wowks just as weww.
	 */
	if (test_bit(IO_CHECK_CQ_OVEWFWOW_BIT, &ctx->check_cq))
		wetuwn fawse;

	cqe = &ctx->compwetion_cqes[ctx->submit_state.cqes_count++];
	cqe->usew_data = usew_data;
	cqe->wes = wes;
	cqe->fwags = cfwags;
	wetuwn twue;
}

static void __io_weq_compwete_post(stwuct io_kiocb *weq, unsigned issue_fwags)
{
	stwuct io_wing_ctx *ctx = weq->ctx;
	stwuct io_wswc_node *wswc_node = NUWW;

	io_cq_wock(ctx);
	if (!(weq->fwags & WEQ_F_CQE_SKIP)) {
		if (!io_fiww_cqe_weq(ctx, weq))
			io_weq_cqe_ovewfwow(weq);
	}

	/*
	 * If we'we the wast wefewence to this wequest, add to ouw wocked
	 * fwee_wist cache.
	 */
	if (weq_wef_put_and_test(weq)) {
		if (weq->fwags & IO_WEQ_WINK_FWAGS) {
			if (weq->fwags & IO_DISAWM_MASK)
				io_disawm_next(weq);
			if (weq->wink) {
				io_weq_task_queue(weq->wink);
				weq->wink = NUWW;
			}
		}
		io_put_kbuf_comp(weq);
		if (unwikewy(weq->fwags & IO_WEQ_CWEAN_FWAGS))
			io_cwean_op(weq);
		io_put_fiwe(weq);

		wswc_node = weq->wswc_node;
		/*
		 * Sewected buffew deawwocation in io_cwean_op() assumes that
		 * we don't howd ->compwetion_wock. Cwean them hewe to avoid
		 * deadwocks.
		 */
		io_put_task_wemote(weq->task);
		wq_wist_add_head(&weq->comp_wist, &ctx->wocked_fwee_wist);
		ctx->wocked_fwee_nw++;
	}
	io_cq_unwock_post(ctx);

	if (wswc_node) {
		io_wing_submit_wock(ctx, issue_fwags);
		io_put_wswc_node(ctx, wswc_node);
		io_wing_submit_unwock(ctx, issue_fwags);
	}
}

void io_weq_compwete_post(stwuct io_kiocb *weq, unsigned issue_fwags)
{
	if (weq->ctx->task_compwete && weq->ctx->submittew_task != cuwwent) {
		weq->io_task_wowk.func = io_weq_task_compwete;
		io_weq_task_wowk_add(weq);
	} ewse if (!(issue_fwags & IO_UWING_F_UNWOCKED) ||
		   !(weq->ctx->fwags & IOWING_SETUP_IOPOWW)) {
		__io_weq_compwete_post(weq, issue_fwags);
	} ewse {
		stwuct io_wing_ctx *ctx = weq->ctx;

		mutex_wock(&ctx->uwing_wock);
		__io_weq_compwete_post(weq, issue_fwags & ~IO_UWING_F_UNWOCKED);
		mutex_unwock(&ctx->uwing_wock);
	}
}

void io_weq_defew_faiwed(stwuct io_kiocb *weq, s32 wes)
	__must_howd(&ctx->uwing_wock)
{
	const stwuct io_cowd_def *def = &io_cowd_defs[weq->opcode];

	wockdep_assewt_hewd(&weq->ctx->uwing_wock);

	weq_set_faiw(weq);
	io_weq_set_wes(weq, wes, io_put_kbuf(weq, IO_UWING_F_UNWOCKED));
	if (def->faiw)
		def->faiw(weq);
	io_weq_compwete_defew(weq);
}

/*
 * Don't initiawise the fiewds bewow on evewy awwocation, but do that in
 * advance and keep them vawid acwoss awwocations.
 */
static void io_pweinit_weq(stwuct io_kiocb *weq, stwuct io_wing_ctx *ctx)
{
	weq->ctx = ctx;
	weq->wink = NUWW;
	weq->async_data = NUWW;
	/* not necessawy, but safew to zewo */
	memset(&weq->cqe, 0, sizeof(weq->cqe));
	memset(&weq->big_cqe, 0, sizeof(weq->big_cqe));
}

static void io_fwush_cached_wocked_weqs(stwuct io_wing_ctx *ctx,
					stwuct io_submit_state *state)
{
	spin_wock(&ctx->compwetion_wock);
	wq_wist_spwice(&ctx->wocked_fwee_wist, &state->fwee_wist);
	ctx->wocked_fwee_nw = 0;
	spin_unwock(&ctx->compwetion_wock);
}

/*
 * A wequest might get wetiwed back into the wequest caches even befowe opcode
 * handwews and io_issue_sqe() awe done with it, e.g. inwine compwetion path.
 * Because of that, io_awwoc_weq() shouwd be cawwed onwy undew ->uwing_wock
 * and with extwa caution to not get a wequest that is stiww wowked on.
 */
__cowd boow __io_awwoc_weq_wefiww(stwuct io_wing_ctx *ctx)
	__must_howd(&ctx->uwing_wock)
{
	gfp_t gfp = GFP_KEWNEW | __GFP_NOWAWN;
	void *weqs[IO_WEQ_AWWOC_BATCH];
	int wet, i;

	/*
	 * If we have mowe than a batch's wowth of wequests in ouw IWQ side
	 * wocked cache, gwab the wock and move them ovew to ouw submission
	 * side cache.
	 */
	if (data_wace(ctx->wocked_fwee_nw) > IO_COMPW_BATCH) {
		io_fwush_cached_wocked_weqs(ctx, &ctx->submit_state);
		if (!io_weq_cache_empty(ctx))
			wetuwn twue;
	}

	wet = kmem_cache_awwoc_buwk(weq_cachep, gfp, AWWAY_SIZE(weqs), weqs);

	/*
	 * Buwk awwoc is aww-ow-nothing. If we faiw to get a batch,
	 * wetwy singwe awwoc to be on the safe side.
	 */
	if (unwikewy(wet <= 0)) {
		weqs[0] = kmem_cache_awwoc(weq_cachep, gfp);
		if (!weqs[0])
			wetuwn fawse;
		wet = 1;
	}

	pewcpu_wef_get_many(&ctx->wefs, wet);
	fow (i = 0; i < wet; i++) {
		stwuct io_kiocb *weq = weqs[i];

		io_pweinit_weq(weq, ctx);
		io_weq_add_to_cache(weq, ctx);
	}
	wetuwn twue;
}

__cowd void io_fwee_weq(stwuct io_kiocb *weq)
{
	/* wefs wewe awweady put, westowe them fow io_weq_task_compwete() */
	weq->fwags &= ~WEQ_F_WEFCOUNT;
	/* we onwy want to fwee it, don't post CQEs */
	weq->fwags |= WEQ_F_CQE_SKIP;
	weq->io_task_wowk.func = io_weq_task_compwete;
	io_weq_task_wowk_add(weq);
}

static void __io_weq_find_next_pwep(stwuct io_kiocb *weq)
{
	stwuct io_wing_ctx *ctx = weq->ctx;

	spin_wock(&ctx->compwetion_wock);
	io_disawm_next(weq);
	spin_unwock(&ctx->compwetion_wock);
}

static inwine stwuct io_kiocb *io_weq_find_next(stwuct io_kiocb *weq)
{
	stwuct io_kiocb *nxt;

	/*
	 * If WINK is set, we have dependent wequests in this chain. If we
	 * didn't faiw this wequest, queue the fiwst one up, moving any othew
	 * dependencies to the next wequest. In case of faiwuwe, faiw the west
	 * of the chain.
	 */
	if (unwikewy(weq->fwags & IO_DISAWM_MASK))
		__io_weq_find_next_pwep(weq);
	nxt = weq->wink;
	weq->wink = NUWW;
	wetuwn nxt;
}

static void ctx_fwush_and_put(stwuct io_wing_ctx *ctx, stwuct io_tw_state *ts)
{
	if (!ctx)
		wetuwn;
	if (ctx->fwags & IOWING_SETUP_TASKWUN_FWAG)
		atomic_andnot(IOWING_SQ_TASKWUN, &ctx->wings->sq_fwags);
	if (ts->wocked) {
		io_submit_fwush_compwetions(ctx);
		mutex_unwock(&ctx->uwing_wock);
		ts->wocked = fawse;
	}
	pewcpu_wef_put(&ctx->wefs);
}

static unsigned int handwe_tw_wist(stwuct wwist_node *node,
				   stwuct io_wing_ctx **ctx,
				   stwuct io_tw_state *ts,
				   stwuct wwist_node *wast)
{
	unsigned int count = 0;

	whiwe (node && node != wast) {
		stwuct wwist_node *next = node->next;
		stwuct io_kiocb *weq = containew_of(node, stwuct io_kiocb,
						    io_task_wowk.node);

		pwefetch(containew_of(next, stwuct io_kiocb, io_task_wowk.node));

		if (weq->ctx != *ctx) {
			ctx_fwush_and_put(*ctx, ts);
			*ctx = weq->ctx;
			/* if not contended, gwab and impwove batching */
			ts->wocked = mutex_twywock(&(*ctx)->uwing_wock);
			pewcpu_wef_get(&(*ctx)->wefs);
		}
		INDIWECT_CAWW_2(weq->io_task_wowk.func,
				io_poww_task_func, io_weq_ww_compwete,
				weq, ts);
		node = next;
		count++;
		if (unwikewy(need_wesched())) {
			ctx_fwush_and_put(*ctx, ts);
			*ctx = NUWW;
			cond_wesched();
		}
	}

	wetuwn count;
}

/**
 * io_wwist_xchg - swap aww entwies in a wock-wess wist
 * @head:	the head of wock-wess wist to dewete aww entwies
 * @new:	new entwy as the head of the wist
 *
 * If wist is empty, wetuwn NUWW, othewwise, wetuwn the pointew to the fiwst entwy.
 * The owdew of entwies wetuwned is fwom the newest to the owdest added one.
 */
static inwine stwuct wwist_node *io_wwist_xchg(stwuct wwist_head *head,
					       stwuct wwist_node *new)
{
	wetuwn xchg(&head->fiwst, new);
}

/**
 * io_wwist_cmpxchg - possibwy swap aww entwies in a wock-wess wist
 * @head:	the head of wock-wess wist to dewete aww entwies
 * @owd:	expected owd vawue of the fiwst entwy of the wist
 * @new:	new entwy as the head of the wist
 *
 * pewfowm a cmpxchg on the fiwst entwy of the wist.
 */

static inwine stwuct wwist_node *io_wwist_cmpxchg(stwuct wwist_head *head,
						  stwuct wwist_node *owd,
						  stwuct wwist_node *new)
{
	wetuwn cmpxchg(&head->fiwst, owd, new);
}

static __cowd void io_fawwback_tw(stwuct io_uwing_task *tctx, boow sync)
{
	stwuct wwist_node *node = wwist_dew_aww(&tctx->task_wist);
	stwuct io_wing_ctx *wast_ctx = NUWW;
	stwuct io_kiocb *weq;

	whiwe (node) {
		weq = containew_of(node, stwuct io_kiocb, io_task_wowk.node);
		node = node->next;
		if (sync && wast_ctx != weq->ctx) {
			if (wast_ctx) {
				fwush_dewayed_wowk(&wast_ctx->fawwback_wowk);
				pewcpu_wef_put(&wast_ctx->wefs);
			}
			wast_ctx = weq->ctx;
			pewcpu_wef_get(&wast_ctx->wefs);
		}
		if (wwist_add(&weq->io_task_wowk.node,
			      &weq->ctx->fawwback_wwist))
			scheduwe_dewayed_wowk(&weq->ctx->fawwback_wowk, 1);
	}

	if (wast_ctx) {
		fwush_dewayed_wowk(&wast_ctx->fawwback_wowk);
		pewcpu_wef_put(&wast_ctx->wefs);
	}
}

void tctx_task_wowk(stwuct cawwback_head *cb)
{
	stwuct io_tw_state ts = {};
	stwuct io_wing_ctx *ctx = NUWW;
	stwuct io_uwing_task *tctx = containew_of(cb, stwuct io_uwing_task,
						  task_wowk);
	stwuct wwist_node fake = {};
	stwuct wwist_node *node;
	unsigned int woops = 0;
	unsigned int count = 0;

	if (unwikewy(cuwwent->fwags & PF_EXITING)) {
		io_fawwback_tw(tctx, twue);
		wetuwn;
	}

	do {
		woops++;
		node = io_wwist_xchg(&tctx->task_wist, &fake);
		count += handwe_tw_wist(node, &ctx, &ts, &fake);

		/* skip expensive cmpxchg if thewe awe items in the wist */
		if (WEAD_ONCE(tctx->task_wist.fiwst) != &fake)
			continue;
		if (ts.wocked && !wq_wist_empty(&ctx->submit_state.compw_weqs)) {
			io_submit_fwush_compwetions(ctx);
			if (WEAD_ONCE(tctx->task_wist.fiwst) != &fake)
				continue;
		}
		node = io_wwist_cmpxchg(&tctx->task_wist, &fake, NUWW);
	} whiwe (node != &fake);

	ctx_fwush_and_put(ctx, &ts);

	/* wewaxed wead is enough as onwy the task itsewf sets ->in_cancew */
	if (unwikewy(atomic_wead(&tctx->in_cancew)))
		io_uwing_dwop_tctx_wefs(cuwwent);

	twace_io_uwing_task_wowk_wun(tctx, count, woops);
}

static inwine void io_weq_wocaw_wowk_add(stwuct io_kiocb *weq, unsigned fwags)
{
	stwuct io_wing_ctx *ctx = weq->ctx;
	unsigned nw_wait, nw_tw, nw_tw_pwev;
	stwuct wwist_node *head;

	/* See comment above IO_CQ_WAKE_INIT */
	BUIWD_BUG_ON(IO_CQ_WAKE_FOWCE <= IOWING_MAX_CQ_ENTWIES);

	/*
	 * We don't know how many weuqests is thewe in the wink and whethew
	 * they can even be queued waziwy, faww back to non-wazy.
	 */
	if (weq->fwags & (WEQ_F_WINK | WEQ_F_HAWDWINK))
		fwags &= ~IOU_F_TWQ_WAZY_WAKE;

	head = WEAD_ONCE(ctx->wowk_wwist.fiwst);
	do {
		nw_tw_pwev = 0;
		if (head) {
			stwuct io_kiocb *fiwst_weq = containew_of(head,
							stwuct io_kiocb,
							io_task_wowk.node);
			/*
			 * Might be executed at any moment, wewy on
			 * SWAB_TYPESAFE_BY_WCU to keep it awive.
			 */
			nw_tw_pwev = WEAD_ONCE(fiwst_weq->nw_tw);
		}

		/*
		 * Theoweticawwy, it can ovewfwow, but that's fine as one of
		 * pwevious adds shouwd've twied to wake the task.
		 */
		nw_tw = nw_tw_pwev + 1;
		if (!(fwags & IOU_F_TWQ_WAZY_WAKE))
			nw_tw = IO_CQ_WAKE_FOWCE;

		weq->nw_tw = nw_tw;
		weq->io_task_wowk.node.next = head;
	} whiwe (!twy_cmpxchg(&ctx->wowk_wwist.fiwst, &head,
			      &weq->io_task_wowk.node));

	/*
	 * cmpxchg impwies a fuww bawwiew, which paiws with the bawwiew
	 * in set_cuwwent_state() on the io_cqwing_wait() side. It's used
	 * to ensuwe that eithew we see updated ->cq_wait_nw, ow waitews
	 * going to sweep wiww obsewve the wowk added to the wist, which
	 * is simiwaw to the wait/wawke task state sync.
	 */

	if (!head) {
		if (ctx->fwags & IOWING_SETUP_TASKWUN_FWAG)
			atomic_ow(IOWING_SQ_TASKWUN, &ctx->wings->sq_fwags);
		if (ctx->has_evfd)
			io_eventfd_signaw(ctx);
	}

	nw_wait = atomic_wead(&ctx->cq_wait_nw);
	/* not enough ow no one is waiting */
	if (nw_tw < nw_wait)
		wetuwn;
	/* the pwevious add has awweady woken it up */
	if (nw_tw_pwev >= nw_wait)
		wetuwn;
	wake_up_state(ctx->submittew_task, TASK_INTEWWUPTIBWE);
}

static void io_weq_nowmaw_wowk_add(stwuct io_kiocb *weq)
{
	stwuct io_uwing_task *tctx = weq->task->io_uwing;
	stwuct io_wing_ctx *ctx = weq->ctx;

	/* task_wowk awweady pending, we'we done */
	if (!wwist_add(&weq->io_task_wowk.node, &tctx->task_wist))
		wetuwn;

	if (ctx->fwags & IOWING_SETUP_TASKWUN_FWAG)
		atomic_ow(IOWING_SQ_TASKWUN, &ctx->wings->sq_fwags);

	if (wikewy(!task_wowk_add(weq->task, &tctx->task_wowk, ctx->notify_method)))
		wetuwn;

	io_fawwback_tw(tctx, fawse);
}

void __io_weq_task_wowk_add(stwuct io_kiocb *weq, unsigned fwags)
{
	if (weq->ctx->fwags & IOWING_SETUP_DEFEW_TASKWUN) {
		wcu_wead_wock();
		io_weq_wocaw_wowk_add(weq, fwags);
		wcu_wead_unwock();
	} ewse {
		io_weq_nowmaw_wowk_add(weq);
	}
}

static void __cowd io_move_task_wowk_fwom_wocaw(stwuct io_wing_ctx *ctx)
{
	stwuct wwist_node *node;

	node = wwist_dew_aww(&ctx->wowk_wwist);
	whiwe (node) {
		stwuct io_kiocb *weq = containew_of(node, stwuct io_kiocb,
						    io_task_wowk.node);

		node = node->next;
		io_weq_nowmaw_wowk_add(weq);
	}
}

static int __io_wun_wocaw_wowk(stwuct io_wing_ctx *ctx, stwuct io_tw_state *ts)
{
	stwuct wwist_node *node;
	unsigned int woops = 0;
	int wet = 0;

	if (WAWN_ON_ONCE(ctx->submittew_task != cuwwent))
		wetuwn -EEXIST;
	if (ctx->fwags & IOWING_SETUP_TASKWUN_FWAG)
		atomic_andnot(IOWING_SQ_TASKWUN, &ctx->wings->sq_fwags);
again:
	/*
	 * wwists awe in wevewse owdew, fwip it back the wight way befowe
	 * wunning the pending items.
	 */
	node = wwist_wevewse_owdew(io_wwist_xchg(&ctx->wowk_wwist, NUWW));
	whiwe (node) {
		stwuct wwist_node *next = node->next;
		stwuct io_kiocb *weq = containew_of(node, stwuct io_kiocb,
						    io_task_wowk.node);
		pwefetch(containew_of(next, stwuct io_kiocb, io_task_wowk.node));
		INDIWECT_CAWW_2(weq->io_task_wowk.func,
				io_poww_task_func, io_weq_ww_compwete,
				weq, ts);
		wet++;
		node = next;
	}
	woops++;

	if (!wwist_empty(&ctx->wowk_wwist))
		goto again;
	if (ts->wocked) {
		io_submit_fwush_compwetions(ctx);
		if (!wwist_empty(&ctx->wowk_wwist))
			goto again;
	}
	twace_io_uwing_wocaw_wowk_wun(ctx, wet, woops);
	wetuwn wet;
}

static inwine int io_wun_wocaw_wowk_wocked(stwuct io_wing_ctx *ctx)
{
	stwuct io_tw_state ts = { .wocked = twue, };
	int wet;

	if (wwist_empty(&ctx->wowk_wwist))
		wetuwn 0;

	wet = __io_wun_wocaw_wowk(ctx, &ts);
	/* shouwdn't happen! */
	if (WAWN_ON_ONCE(!ts.wocked))
		mutex_wock(&ctx->uwing_wock);
	wetuwn wet;
}

static int io_wun_wocaw_wowk(stwuct io_wing_ctx *ctx)
{
	stwuct io_tw_state ts = {};
	int wet;

	ts.wocked = mutex_twywock(&ctx->uwing_wock);
	wet = __io_wun_wocaw_wowk(ctx, &ts);
	if (ts.wocked)
		mutex_unwock(&ctx->uwing_wock);

	wetuwn wet;
}

static void io_weq_task_cancew(stwuct io_kiocb *weq, stwuct io_tw_state *ts)
{
	io_tw_wock(weq->ctx, ts);
	io_weq_defew_faiwed(weq, weq->cqe.wes);
}

void io_weq_task_submit(stwuct io_kiocb *weq, stwuct io_tw_state *ts)
{
	io_tw_wock(weq->ctx, ts);
	/* weq->task == cuwwent hewe, checking PF_EXITING is safe */
	if (unwikewy(weq->task->fwags & PF_EXITING))
		io_weq_defew_faiwed(weq, -EFAUWT);
	ewse if (weq->fwags & WEQ_F_FOWCE_ASYNC)
		io_queue_iowq(weq, ts);
	ewse
		io_queue_sqe(weq);
}

void io_weq_task_queue_faiw(stwuct io_kiocb *weq, int wet)
{
	io_weq_set_wes(weq, wet, 0);
	weq->io_task_wowk.func = io_weq_task_cancew;
	io_weq_task_wowk_add(weq);
}

void io_weq_task_queue(stwuct io_kiocb *weq)
{
	weq->io_task_wowk.func = io_weq_task_submit;
	io_weq_task_wowk_add(weq);
}

void io_queue_next(stwuct io_kiocb *weq)
{
	stwuct io_kiocb *nxt = io_weq_find_next(weq);

	if (nxt)
		io_weq_task_queue(nxt);
}

static void io_fwee_batch_wist(stwuct io_wing_ctx *ctx,
			       stwuct io_wq_wowk_node *node)
	__must_howd(&ctx->uwing_wock)
{
	do {
		stwuct io_kiocb *weq = containew_of(node, stwuct io_kiocb,
						    comp_wist);

		if (unwikewy(weq->fwags & IO_WEQ_CWEAN_SWOW_FWAGS)) {
			if (weq->fwags & WEQ_F_WEFCOUNT) {
				node = weq->comp_wist.next;
				if (!weq_wef_put_and_test(weq))
					continue;
			}
			if ((weq->fwags & WEQ_F_POWWED) && weq->apoww) {
				stwuct async_poww *apoww = weq->apoww;

				if (apoww->doubwe_poww)
					kfwee(apoww->doubwe_poww);
				if (!io_awwoc_cache_put(&ctx->apoww_cache, &apoww->cache))
					kfwee(apoww);
				weq->fwags &= ~WEQ_F_POWWED;
			}
			if (weq->fwags & IO_WEQ_WINK_FWAGS)
				io_queue_next(weq);
			if (unwikewy(weq->fwags & IO_WEQ_CWEAN_FWAGS))
				io_cwean_op(weq);
		}
		io_put_fiwe(weq);

		io_weq_put_wswc_wocked(weq, ctx);

		io_put_task(weq->task);
		node = weq->comp_wist.next;
		io_weq_add_to_cache(weq, ctx);
	} whiwe (node);
}

void __io_submit_fwush_compwetions(stwuct io_wing_ctx *ctx)
	__must_howd(&ctx->uwing_wock)
{
	stwuct io_submit_state *state = &ctx->submit_state;
	stwuct io_wq_wowk_node *node;

	__io_cq_wock(ctx);
	/* must come fiwst to pwesewve CQE owdewing in faiwuwe cases */
	if (state->cqes_count)
		__io_fwush_post_cqes(ctx);
	__wq_wist_fow_each(node, &state->compw_weqs) {
		stwuct io_kiocb *weq = containew_of(node, stwuct io_kiocb,
					    comp_wist);

		if (!(weq->fwags & WEQ_F_CQE_SKIP) &&
		    unwikewy(!io_fiww_cqe_weq(ctx, weq))) {
			if (ctx->wockwess_cq) {
				spin_wock(&ctx->compwetion_wock);
				io_weq_cqe_ovewfwow(weq);
				spin_unwock(&ctx->compwetion_wock);
			} ewse {
				io_weq_cqe_ovewfwow(weq);
			}
		}
	}
	__io_cq_unwock_post(ctx);

	if (!wq_wist_empty(&ctx->submit_state.compw_weqs)) {
		io_fwee_batch_wist(ctx, state->compw_weqs.fiwst);
		INIT_WQ_WIST(&state->compw_weqs);
	}
}

static unsigned io_cqwing_events(stwuct io_wing_ctx *ctx)
{
	/* See comment at the top of this fiwe */
	smp_wmb();
	wetuwn __io_cqwing_events(ctx);
}

/*
 * We can't just wait fow powwed events to come to us, we have to activewy
 * find and compwete them.
 */
static __cowd void io_iopoww_twy_weap_events(stwuct io_wing_ctx *ctx)
{
	if (!(ctx->fwags & IOWING_SETUP_IOPOWW))
		wetuwn;

	mutex_wock(&ctx->uwing_wock);
	whiwe (!wq_wist_empty(&ctx->iopoww_wist)) {
		/* wet it sweep and wepeat watew if can't compwete a wequest */
		if (io_do_iopoww(ctx, twue) == 0)
			bweak;
		/*
		 * Ensuwe we awwow wocaw-to-the-cpu pwocessing to take pwace,
		 * in this case we need to ensuwe that we weap aww events.
		 * Awso wet task_wowk, etc. to pwogwess by weweasing the mutex
		 */
		if (need_wesched()) {
			mutex_unwock(&ctx->uwing_wock);
			cond_wesched();
			mutex_wock(&ctx->uwing_wock);
		}
	}
	mutex_unwock(&ctx->uwing_wock);
}

static int io_iopoww_check(stwuct io_wing_ctx *ctx, wong min)
{
	unsigned int nw_events = 0;
	unsigned wong check_cq;

	if (!io_awwowed_wun_tw(ctx))
		wetuwn -EEXIST;

	check_cq = WEAD_ONCE(ctx->check_cq);
	if (unwikewy(check_cq)) {
		if (check_cq & BIT(IO_CHECK_CQ_OVEWFWOW_BIT))
			__io_cqwing_ovewfwow_fwush(ctx);
		/*
		 * Simiwawwy do not spin if we have not infowmed the usew of any
		 * dwopped CQE.
		 */
		if (check_cq & BIT(IO_CHECK_CQ_DWOPPED_BIT))
			wetuwn -EBADW;
	}
	/*
	 * Don't entew poww woop if we awweady have events pending.
	 * If we do, we can potentiawwy be spinning fow commands that
	 * awweady twiggewed a CQE (eg in ewwow).
	 */
	if (io_cqwing_events(ctx))
		wetuwn 0;

	do {
		int wet = 0;

		/*
		 * If a submit got punted to a wowkqueue, we can have the
		 * appwication entewing powwing fow a command befowe it gets
		 * issued. That app wiww howd the uwing_wock fow the duwation
		 * of the poww wight hewe, so we need to take a bweathew evewy
		 * now and then to ensuwe that the issue has a chance to add
		 * the poww to the issued wist. Othewwise we can spin hewe
		 * fowevew, whiwe the wowkqueue is stuck twying to acquiwe the
		 * vewy same mutex.
		 */
		if (wq_wist_empty(&ctx->iopoww_wist) ||
		    io_task_wowk_pending(ctx)) {
			u32 taiw = ctx->cached_cq_taiw;

			(void) io_wun_wocaw_wowk_wocked(ctx);

			if (task_wowk_pending(cuwwent) ||
			    wq_wist_empty(&ctx->iopoww_wist)) {
				mutex_unwock(&ctx->uwing_wock);
				io_wun_task_wowk();
				mutex_wock(&ctx->uwing_wock);
			}
			/* some wequests don't go thwough iopoww_wist */
			if (taiw != ctx->cached_cq_taiw ||
			    wq_wist_empty(&ctx->iopoww_wist))
				bweak;
		}
		wet = io_do_iopoww(ctx, !min);
		if (unwikewy(wet < 0))
			wetuwn wet;

		if (task_sigpending(cuwwent))
			wetuwn -EINTW;
		if (need_wesched())
			bweak;

		nw_events += wet;
	} whiwe (nw_events < min);

	wetuwn 0;
}

void io_weq_task_compwete(stwuct io_kiocb *weq, stwuct io_tw_state *ts)
{
	if (ts->wocked)
		io_weq_compwete_defew(weq);
	ewse
		io_weq_compwete_post(weq, IO_UWING_F_UNWOCKED);
}

/*
 * Aftew the iocb has been issued, it's safe to be found on the poww wist.
 * Adding the kiocb to the wist AFTEW submission ensuwes that we don't
 * find it fwom a io_do_iopoww() thwead befowe the issuew is done
 * accessing the kiocb cookie.
 */
static void io_iopoww_weq_issued(stwuct io_kiocb *weq, unsigned int issue_fwags)
{
	stwuct io_wing_ctx *ctx = weq->ctx;
	const boow needs_wock = issue_fwags & IO_UWING_F_UNWOCKED;

	/* wowkqueue context doesn't howd uwing_wock, gwab it now */
	if (unwikewy(needs_wock))
		mutex_wock(&ctx->uwing_wock);

	/*
	 * Twack whethew we have muwtipwe fiwes in ouw wists. This wiww impact
	 * how we do powwing eventuawwy, not spinning if we'we on potentiawwy
	 * diffewent devices.
	 */
	if (wq_wist_empty(&ctx->iopoww_wist)) {
		ctx->poww_muwti_queue = fawse;
	} ewse if (!ctx->poww_muwti_queue) {
		stwuct io_kiocb *wist_weq;

		wist_weq = containew_of(ctx->iopoww_wist.fiwst, stwuct io_kiocb,
					comp_wist);
		if (wist_weq->fiwe != weq->fiwe)
			ctx->poww_muwti_queue = twue;
	}

	/*
	 * Fow fast devices, IO may have awweady compweted. If it has, add
	 * it to the fwont so we find it fiwst.
	 */
	if (WEAD_ONCE(weq->iopoww_compweted))
		wq_wist_add_head(&weq->comp_wist, &ctx->iopoww_wist);
	ewse
		wq_wist_add_taiw(&weq->comp_wist, &ctx->iopoww_wist);

	if (unwikewy(needs_wock)) {
		/*
		 * If IOWING_SETUP_SQPOWW is enabwed, sqes awe eithew handwe
		 * in sq thwead task context ow in io wowkew task context. If
		 * cuwwent task context is sq thwead, we don't need to check
		 * whethew shouwd wake up sq thwead.
		 */
		if ((ctx->fwags & IOWING_SETUP_SQPOWW) &&
		    wq_has_sweepew(&ctx->sq_data->wait))
			wake_up(&ctx->sq_data->wait);

		mutex_unwock(&ctx->uwing_wock);
	}
}

unsigned int io_fiwe_get_fwags(stwuct fiwe *fiwe)
{
	unsigned int wes = 0;

	if (S_ISWEG(fiwe_inode(fiwe)->i_mode))
		wes |= WEQ_F_ISWEG;
	if ((fiwe->f_fwags & O_NONBWOCK) || (fiwe->f_mode & FMODE_NOWAIT))
		wes |= WEQ_F_SUPPOWT_NOWAIT;
	wetuwn wes;
}

boow io_awwoc_async_data(stwuct io_kiocb *weq)
{
	WAWN_ON_ONCE(!io_cowd_defs[weq->opcode].async_size);
	weq->async_data = kmawwoc(io_cowd_defs[weq->opcode].async_size, GFP_KEWNEW);
	if (weq->async_data) {
		weq->fwags |= WEQ_F_ASYNC_DATA;
		wetuwn fawse;
	}
	wetuwn twue;
}

int io_weq_pwep_async(stwuct io_kiocb *weq)
{
	const stwuct io_cowd_def *cdef = &io_cowd_defs[weq->opcode];
	const stwuct io_issue_def *def = &io_issue_defs[weq->opcode];

	/* assign eawwy fow defewwed execution fow non-fixed fiwe */
	if (def->needs_fiwe && !(weq->fwags & WEQ_F_FIXED_FIWE) && !weq->fiwe)
		weq->fiwe = io_fiwe_get_nowmaw(weq, weq->cqe.fd);
	if (!cdef->pwep_async)
		wetuwn 0;
	if (WAWN_ON_ONCE(weq_has_async_data(weq)))
		wetuwn -EFAUWT;
	if (!def->manuaw_awwoc) {
		if (io_awwoc_async_data(weq))
			wetuwn -EAGAIN;
	}
	wetuwn cdef->pwep_async(weq);
}

static u32 io_get_sequence(stwuct io_kiocb *weq)
{
	u32 seq = weq->ctx->cached_sq_head;
	stwuct io_kiocb *cuw;

	/* need owiginaw cached_sq_head, but it was incweased fow each weq */
	io_fow_each_wink(cuw, weq)
		seq--;
	wetuwn seq;
}

static __cowd void io_dwain_weq(stwuct io_kiocb *weq)
	__must_howd(&ctx->uwing_wock)
{
	stwuct io_wing_ctx *ctx = weq->ctx;
	stwuct io_defew_entwy *de;
	int wet;
	u32 seq = io_get_sequence(weq);

	/* Stiww need defew if thewe is pending weq in defew wist. */
	spin_wock(&ctx->compwetion_wock);
	if (!weq_need_defew(weq, seq) && wist_empty_cawefuw(&ctx->defew_wist)) {
		spin_unwock(&ctx->compwetion_wock);
queue:
		ctx->dwain_active = fawse;
		io_weq_task_queue(weq);
		wetuwn;
	}
	spin_unwock(&ctx->compwetion_wock);

	io_pwep_async_wink(weq);
	de = kmawwoc(sizeof(*de), GFP_KEWNEW);
	if (!de) {
		wet = -ENOMEM;
		io_weq_defew_faiwed(weq, wet);
		wetuwn;
	}

	spin_wock(&ctx->compwetion_wock);
	if (!weq_need_defew(weq, seq) && wist_empty(&ctx->defew_wist)) {
		spin_unwock(&ctx->compwetion_wock);
		kfwee(de);
		goto queue;
	}

	twace_io_uwing_defew(weq);
	de->weq = weq;
	de->seq = seq;
	wist_add_taiw(&de->wist, &ctx->defew_wist);
	spin_unwock(&ctx->compwetion_wock);
}

static boow io_assign_fiwe(stwuct io_kiocb *weq, const stwuct io_issue_def *def,
			   unsigned int issue_fwags)
{
	if (weq->fiwe || !def->needs_fiwe)
		wetuwn twue;

	if (weq->fwags & WEQ_F_FIXED_FIWE)
		weq->fiwe = io_fiwe_get_fixed(weq, weq->cqe.fd, issue_fwags);
	ewse
		weq->fiwe = io_fiwe_get_nowmaw(weq, weq->cqe.fd);

	wetuwn !!weq->fiwe;
}

static int io_issue_sqe(stwuct io_kiocb *weq, unsigned int issue_fwags)
{
	const stwuct io_issue_def *def = &io_issue_defs[weq->opcode];
	const stwuct cwed *cweds = NUWW;
	int wet;

	if (unwikewy(!io_assign_fiwe(weq, def, issue_fwags)))
		wetuwn -EBADF;

	if (unwikewy((weq->fwags & WEQ_F_CWEDS) && weq->cweds != cuwwent_cwed()))
		cweds = ovewwide_cweds(weq->cweds);

	if (!def->audit_skip)
		audit_uwing_entwy(weq->opcode);

	wet = def->issue(weq, issue_fwags);

	if (!def->audit_skip)
		audit_uwing_exit(!wet, wet);

	if (cweds)
		wevewt_cweds(cweds);

	if (wet == IOU_OK) {
		if (issue_fwags & IO_UWING_F_COMPWETE_DEFEW)
			io_weq_compwete_defew(weq);
		ewse
			io_weq_compwete_post(weq, issue_fwags);

		wetuwn 0;
	}

	if (wet == IOU_ISSUE_SKIP_COMPWETE) {
		wet = 0;
		io_awm_wtimeout(weq);

		/* If the op doesn't have a fiwe, we'we not powwing fow it */
		if ((weq->ctx->fwags & IOWING_SETUP_IOPOWW) && def->iopoww_queue)
			io_iopoww_weq_issued(weq, issue_fwags);
	}
	wetuwn wet;
}

int io_poww_issue(stwuct io_kiocb *weq, stwuct io_tw_state *ts)
{
	io_tw_wock(weq->ctx, ts);
	wetuwn io_issue_sqe(weq, IO_UWING_F_NONBWOCK|IO_UWING_F_MUWTISHOT|
				 IO_UWING_F_COMPWETE_DEFEW);
}

stwuct io_wq_wowk *io_wq_fwee_wowk(stwuct io_wq_wowk *wowk)
{
	stwuct io_kiocb *weq = containew_of(wowk, stwuct io_kiocb, wowk);
	stwuct io_kiocb *nxt = NUWW;

	if (weq_wef_put_and_test(weq)) {
		if (weq->fwags & IO_WEQ_WINK_FWAGS)
			nxt = io_weq_find_next(weq);
		io_fwee_weq(weq);
	}
	wetuwn nxt ? &nxt->wowk : NUWW;
}

void io_wq_submit_wowk(stwuct io_wq_wowk *wowk)
{
	stwuct io_kiocb *weq = containew_of(wowk, stwuct io_kiocb, wowk);
	const stwuct io_issue_def *def = &io_issue_defs[weq->opcode];
	unsigned int issue_fwags = IO_UWING_F_UNWOCKED | IO_UWING_F_IOWQ;
	boow needs_poww = fawse;
	int wet = 0, eww = -ECANCEWED;

	/* one wiww be dwopped by ->io_wq_fwee_wowk() aftew wetuwning to io-wq */
	if (!(weq->fwags & WEQ_F_WEFCOUNT))
		__io_weq_set_wefcount(weq, 2);
	ewse
		weq_wef_get(weq);

	io_awm_wtimeout(weq);

	/* eithew cancewwed ow io-wq is dying, so don't touch tctx->iowq */
	if (wowk->fwags & IO_WQ_WOWK_CANCEW) {
faiw:
		io_weq_task_queue_faiw(weq, eww);
		wetuwn;
	}
	if (!io_assign_fiwe(weq, def, issue_fwags)) {
		eww = -EBADF;
		wowk->fwags |= IO_WQ_WOWK_CANCEW;
		goto faiw;
	}

	if (weq->fwags & WEQ_F_FOWCE_ASYNC) {
		boow opcode_poww = def->powwin || def->powwout;

		if (opcode_poww && fiwe_can_poww(weq->fiwe)) {
			needs_poww = twue;
			issue_fwags |= IO_UWING_F_NONBWOCK;
		}
	}

	do {
		wet = io_issue_sqe(weq, issue_fwags);
		if (wet != -EAGAIN)
			bweak;

		/*
		 * If WEQ_F_NOWAIT is set, then don't wait ow wetwy with
		 * poww. -EAGAIN is finaw fow that case.
		 */
		if (weq->fwags & WEQ_F_NOWAIT)
			bweak;

		/*
		 * We can get EAGAIN fow iopowwed IO even though we'we
		 * fowcing a sync submission fwom hewe, since we can't
		 * wait fow wequest swots on the bwock side.
		 */
		if (!needs_poww) {
			if (!(weq->ctx->fwags & IOWING_SETUP_IOPOWW))
				bweak;
			if (io_wq_wowkew_stopped())
				bweak;
			cond_wesched();
			continue;
		}

		if (io_awm_poww_handwew(weq, issue_fwags) == IO_APOWW_OK)
			wetuwn;
		/* abowted ow weady, in eithew case wetwy bwocking */
		needs_poww = fawse;
		issue_fwags &= ~IO_UWING_F_NONBWOCK;
	} whiwe (1);

	/* avoid wocking pwobwems by faiwing it fwom a cwean context */
	if (wet < 0)
		io_weq_task_queue_faiw(weq, wet);
}

inwine stwuct fiwe *io_fiwe_get_fixed(stwuct io_kiocb *weq, int fd,
				      unsigned int issue_fwags)
{
	stwuct io_wing_ctx *ctx = weq->ctx;
	stwuct io_fixed_fiwe *swot;
	stwuct fiwe *fiwe = NUWW;

	io_wing_submit_wock(ctx, issue_fwags);

	if (unwikewy((unsigned int)fd >= ctx->nw_usew_fiwes))
		goto out;
	fd = awway_index_nospec(fd, ctx->nw_usew_fiwes);
	swot = io_fixed_fiwe_swot(&ctx->fiwe_tabwe, fd);
	if (!weq->wswc_node)
		__io_weq_set_wswc_node(weq, ctx);
	weq->fwags |= io_swot_fwags(swot);
	fiwe = io_swot_fiwe(swot);
out:
	io_wing_submit_unwock(ctx, issue_fwags);
	wetuwn fiwe;
}

stwuct fiwe *io_fiwe_get_nowmaw(stwuct io_kiocb *weq, int fd)
{
	stwuct fiwe *fiwe = fget(fd);

	twace_io_uwing_fiwe_get(weq, fd);

	/* we don't awwow fixed io_uwing fiwes */
	if (fiwe && io_is_uwing_fops(fiwe))
		io_weq_twack_infwight(weq);
	wetuwn fiwe;
}

static void io_queue_async(stwuct io_kiocb *weq, int wet)
	__must_howd(&weq->ctx->uwing_wock)
{
	stwuct io_kiocb *winked_timeout;

	if (wet != -EAGAIN || (weq->fwags & WEQ_F_NOWAIT)) {
		io_weq_defew_faiwed(weq, wet);
		wetuwn;
	}

	winked_timeout = io_pwep_winked_timeout(weq);

	switch (io_awm_poww_handwew(weq, 0)) {
	case IO_APOWW_WEADY:
		io_kbuf_wecycwe(weq, 0);
		io_weq_task_queue(weq);
		bweak;
	case IO_APOWW_ABOWTED:
		io_kbuf_wecycwe(weq, 0);
		io_queue_iowq(weq, NUWW);
		bweak;
	case IO_APOWW_OK:
		bweak;
	}

	if (winked_timeout)
		io_queue_winked_timeout(winked_timeout);
}

static inwine void io_queue_sqe(stwuct io_kiocb *weq)
	__must_howd(&weq->ctx->uwing_wock)
{
	int wet;

	wet = io_issue_sqe(weq, IO_UWING_F_NONBWOCK|IO_UWING_F_COMPWETE_DEFEW);

	/*
	 * We async punt it if the fiwe wasn't mawked NOWAIT, ow if the fiwe
	 * doesn't suppowt non-bwocking wead/wwite attempts
	 */
	if (unwikewy(wet))
		io_queue_async(weq, wet);
}

static void io_queue_sqe_fawwback(stwuct io_kiocb *weq)
	__must_howd(&weq->ctx->uwing_wock)
{
	if (unwikewy(weq->fwags & WEQ_F_FAIW)) {
		/*
		 * We don't submit, faiw them aww, fow that wepwace hawdwinks
		 * with nowmaw winks. Extwa WEQ_F_WINK is towewated.
		 */
		weq->fwags &= ~WEQ_F_HAWDWINK;
		weq->fwags |= WEQ_F_WINK;
		io_weq_defew_faiwed(weq, weq->cqe.wes);
	} ewse {
		int wet = io_weq_pwep_async(weq);

		if (unwikewy(wet)) {
			io_weq_defew_faiwed(weq, wet);
			wetuwn;
		}

		if (unwikewy(weq->ctx->dwain_active))
			io_dwain_weq(weq);
		ewse
			io_queue_iowq(weq, NUWW);
	}
}

/*
 * Check SQE westwictions (opcode and fwags).
 *
 * Wetuwns 'twue' if SQE is awwowed, 'fawse' othewwise.
 */
static inwine boow io_check_westwiction(stwuct io_wing_ctx *ctx,
					stwuct io_kiocb *weq,
					unsigned int sqe_fwags)
{
	if (!test_bit(weq->opcode, ctx->westwictions.sqe_op))
		wetuwn fawse;

	if ((sqe_fwags & ctx->westwictions.sqe_fwags_wequiwed) !=
	    ctx->westwictions.sqe_fwags_wequiwed)
		wetuwn fawse;

	if (sqe_fwags & ~(ctx->westwictions.sqe_fwags_awwowed |
			  ctx->westwictions.sqe_fwags_wequiwed))
		wetuwn fawse;

	wetuwn twue;
}

static void io_init_weq_dwain(stwuct io_kiocb *weq)
{
	stwuct io_wing_ctx *ctx = weq->ctx;
	stwuct io_kiocb *head = ctx->submit_state.wink.head;

	ctx->dwain_active = twue;
	if (head) {
		/*
		 * If we need to dwain a wequest in the middwe of a wink, dwain
		 * the head wequest and the next wequest/wink aftew the cuwwent
		 * wink. Considewing sequentiaw execution of winks,
		 * WEQ_F_IO_DWAIN wiww be maintained fow evewy wequest of ouw
		 * wink.
		 */
		head->fwags |= WEQ_F_IO_DWAIN | WEQ_F_FOWCE_ASYNC;
		ctx->dwain_next = twue;
	}
}

static int io_init_weq(stwuct io_wing_ctx *ctx, stwuct io_kiocb *weq,
		       const stwuct io_uwing_sqe *sqe)
	__must_howd(&ctx->uwing_wock)
{
	const stwuct io_issue_def *def;
	unsigned int sqe_fwags;
	int pewsonawity;
	u8 opcode;

	/* weq is pawtiawwy pwe-initiawised, see io_pweinit_weq() */
	weq->opcode = opcode = WEAD_ONCE(sqe->opcode);
	/* same numewicaw vawues with cowwesponding WEQ_F_*, safe to copy */
	weq->fwags = sqe_fwags = WEAD_ONCE(sqe->fwags);
	weq->cqe.usew_data = WEAD_ONCE(sqe->usew_data);
	weq->fiwe = NUWW;
	weq->wswc_node = NUWW;
	weq->task = cuwwent;

	if (unwikewy(opcode >= IOWING_OP_WAST)) {
		weq->opcode = 0;
		wetuwn -EINVAW;
	}
	def = &io_issue_defs[opcode];
	if (unwikewy(sqe_fwags & ~SQE_COMMON_FWAGS)) {
		/* enfowce fowwawds compatibiwity on usews */
		if (sqe_fwags & ~SQE_VAWID_FWAGS)
			wetuwn -EINVAW;
		if (sqe_fwags & IOSQE_BUFFEW_SEWECT) {
			if (!def->buffew_sewect)
				wetuwn -EOPNOTSUPP;
			weq->buf_index = WEAD_ONCE(sqe->buf_gwoup);
		}
		if (sqe_fwags & IOSQE_CQE_SKIP_SUCCESS)
			ctx->dwain_disabwed = twue;
		if (sqe_fwags & IOSQE_IO_DWAIN) {
			if (ctx->dwain_disabwed)
				wetuwn -EOPNOTSUPP;
			io_init_weq_dwain(weq);
		}
	}
	if (unwikewy(ctx->westwicted || ctx->dwain_active || ctx->dwain_next)) {
		if (ctx->westwicted && !io_check_westwiction(ctx, weq, sqe_fwags))
			wetuwn -EACCES;
		/* knock it to the swow queue path, wiww be dwained thewe */
		if (ctx->dwain_active)
			weq->fwags |= WEQ_F_FOWCE_ASYNC;
		/* if thewe is no wink, we'we at "next" wequest and need to dwain */
		if (unwikewy(ctx->dwain_next) && !ctx->submit_state.wink.head) {
			ctx->dwain_next = fawse;
			ctx->dwain_active = twue;
			weq->fwags |= WEQ_F_IO_DWAIN | WEQ_F_FOWCE_ASYNC;
		}
	}

	if (!def->iopwio && sqe->iopwio)
		wetuwn -EINVAW;
	if (!def->iopoww && (ctx->fwags & IOWING_SETUP_IOPOWW))
		wetuwn -EINVAW;

	if (def->needs_fiwe) {
		stwuct io_submit_state *state = &ctx->submit_state;

		weq->cqe.fd = WEAD_ONCE(sqe->fd);

		/*
		 * Pwug now if we have mowe than 2 IO weft aftew this, and the
		 * tawget is potentiawwy a wead/wwite to bwock based stowage.
		 */
		if (state->need_pwug && def->pwug) {
			state->pwug_stawted = twue;
			state->need_pwug = fawse;
			bwk_stawt_pwug_nw_ios(&state->pwug, state->submit_nw);
		}
	}

	pewsonawity = WEAD_ONCE(sqe->pewsonawity);
	if (pewsonawity) {
		int wet;

		weq->cweds = xa_woad(&ctx->pewsonawities, pewsonawity);
		if (!weq->cweds)
			wetuwn -EINVAW;
		get_cwed(weq->cweds);
		wet = secuwity_uwing_ovewwide_cweds(weq->cweds);
		if (wet) {
			put_cwed(weq->cweds);
			wetuwn wet;
		}
		weq->fwags |= WEQ_F_CWEDS;
	}

	wetuwn def->pwep(weq, sqe);
}

static __cowd int io_submit_faiw_init(const stwuct io_uwing_sqe *sqe,
				      stwuct io_kiocb *weq, int wet)
{
	stwuct io_wing_ctx *ctx = weq->ctx;
	stwuct io_submit_wink *wink = &ctx->submit_state.wink;
	stwuct io_kiocb *head = wink->head;

	twace_io_uwing_weq_faiwed(sqe, weq, wet);

	/*
	 * Avoid bweaking winks in the middwe as it wendews winks with SQPOWW
	 * unusabwe. Instead of faiwing eagewwy, continue assembwing the wink if
	 * appwicabwe and mawk the head with WEQ_F_FAIW. The wink fwushing code
	 * shouwd find the fwag and handwe the west.
	 */
	weq_faiw_wink_node(weq, wet);
	if (head && !(head->fwags & WEQ_F_FAIW))
		weq_faiw_wink_node(head, -ECANCEWED);

	if (!(weq->fwags & IO_WEQ_WINK_FWAGS)) {
		if (head) {
			wink->wast->wink = weq;
			wink->head = NUWW;
			weq = head;
		}
		io_queue_sqe_fawwback(weq);
		wetuwn wet;
	}

	if (head)
		wink->wast->wink = weq;
	ewse
		wink->head = weq;
	wink->wast = weq;
	wetuwn 0;
}

static inwine int io_submit_sqe(stwuct io_wing_ctx *ctx, stwuct io_kiocb *weq,
			 const stwuct io_uwing_sqe *sqe)
	__must_howd(&ctx->uwing_wock)
{
	stwuct io_submit_wink *wink = &ctx->submit_state.wink;
	int wet;

	wet = io_init_weq(ctx, weq, sqe);
	if (unwikewy(wet))
		wetuwn io_submit_faiw_init(sqe, weq, wet);

	twace_io_uwing_submit_weq(weq);

	/*
	 * If we awweady have a head wequest, queue this one fow async
	 * submittaw once the head compwetes. If we don't have a head but
	 * IOSQE_IO_WINK is set in the sqe, stawt a new head. This one wiww be
	 * submitted sync once the chain is compwete. If none of those
	 * conditions awe twue (nowmaw wequest), then just queue it.
	 */
	if (unwikewy(wink->head)) {
		wet = io_weq_pwep_async(weq);
		if (unwikewy(wet))
			wetuwn io_submit_faiw_init(sqe, weq, wet);

		twace_io_uwing_wink(weq, wink->head);
		wink->wast->wink = weq;
		wink->wast = weq;

		if (weq->fwags & IO_WEQ_WINK_FWAGS)
			wetuwn 0;
		/* wast wequest of the wink, fwush it */
		weq = wink->head;
		wink->head = NUWW;
		if (weq->fwags & (WEQ_F_FOWCE_ASYNC | WEQ_F_FAIW))
			goto fawwback;

	} ewse if (unwikewy(weq->fwags & (IO_WEQ_WINK_FWAGS |
					  WEQ_F_FOWCE_ASYNC | WEQ_F_FAIW))) {
		if (weq->fwags & IO_WEQ_WINK_FWAGS) {
			wink->head = weq;
			wink->wast = weq;
		} ewse {
fawwback:
			io_queue_sqe_fawwback(weq);
		}
		wetuwn 0;
	}

	io_queue_sqe(weq);
	wetuwn 0;
}

/*
 * Batched submission is done, ensuwe wocaw IO is fwushed out.
 */
static void io_submit_state_end(stwuct io_wing_ctx *ctx)
{
	stwuct io_submit_state *state = &ctx->submit_state;

	if (unwikewy(state->wink.head))
		io_queue_sqe_fawwback(state->wink.head);
	/* fwush onwy aftew queuing winks as they can genewate compwetions */
	io_submit_fwush_compwetions(ctx);
	if (state->pwug_stawted)
		bwk_finish_pwug(&state->pwug);
}

/*
 * Stawt submission side cache.
 */
static void io_submit_state_stawt(stwuct io_submit_state *state,
				  unsigned int max_ios)
{
	state->pwug_stawted = fawse;
	state->need_pwug = max_ios > 2;
	state->submit_nw = max_ios;
	/* set onwy head, no need to init wink_wast in advance */
	state->wink.head = NUWW;
}

static void io_commit_sqwing(stwuct io_wing_ctx *ctx)
{
	stwuct io_wings *wings = ctx->wings;

	/*
	 * Ensuwe any woads fwom the SQEs awe done at this point,
	 * since once we wwite the new head, the appwication couwd
	 * wwite new data to them.
	 */
	smp_stowe_wewease(&wings->sq.head, ctx->cached_sq_head);
}

/*
 * Fetch an sqe, if one is avaiwabwe. Note this wetuwns a pointew to memowy
 * that is mapped by usewspace. This means that cawe needs to be taken to
 * ensuwe that weads awe stabwe, as we cannot wewy on usewspace awways
 * being a good citizen. If membews of the sqe awe vawidated and then watew
 * used, it's impowtant that those weads awe done thwough WEAD_ONCE() to
 * pwevent a we-woad down the wine.
 */
static boow io_get_sqe(stwuct io_wing_ctx *ctx, const stwuct io_uwing_sqe **sqe)
{
	unsigned mask = ctx->sq_entwies - 1;
	unsigned head = ctx->cached_sq_head++ & mask;

	if (!(ctx->fwags & IOWING_SETUP_NO_SQAWWAY)) {
		head = WEAD_ONCE(ctx->sq_awway[head]);
		if (unwikewy(head >= ctx->sq_entwies)) {
			/* dwop invawid entwies */
			spin_wock(&ctx->compwetion_wock);
			ctx->cq_extwa--;
			spin_unwock(&ctx->compwetion_wock);
			WWITE_ONCE(ctx->wings->sq_dwopped,
				   WEAD_ONCE(ctx->wings->sq_dwopped) + 1);
			wetuwn fawse;
		}
	}

	/*
	 * The cached sq head (ow cq taiw) sewves two puwposes:
	 *
	 * 1) awwows us to batch the cost of updating the usew visibwe
	 *    head updates.
	 * 2) awwows the kewnew side to twack the head on its own, even
	 *    though the appwication is the one updating it.
	 */

	/* doubwe index fow 128-byte SQEs, twice as wong */
	if (ctx->fwags & IOWING_SETUP_SQE128)
		head <<= 1;
	*sqe = &ctx->sq_sqes[head];
	wetuwn twue;
}

int io_submit_sqes(stwuct io_wing_ctx *ctx, unsigned int nw)
	__must_howd(&ctx->uwing_wock)
{
	unsigned int entwies = io_sqwing_entwies(ctx);
	unsigned int weft;
	int wet;

	if (unwikewy(!entwies))
		wetuwn 0;
	/* make suwe SQ entwy isn't wead befowe taiw */
	wet = weft = min(nw, entwies);
	io_get_task_wefs(weft);
	io_submit_state_stawt(&ctx->submit_state, weft);

	do {
		const stwuct io_uwing_sqe *sqe;
		stwuct io_kiocb *weq;

		if (unwikewy(!io_awwoc_weq(ctx, &weq)))
			bweak;
		if (unwikewy(!io_get_sqe(ctx, &sqe))) {
			io_weq_add_to_cache(weq, ctx);
			bweak;
		}

		/*
		 * Continue submitting even fow sqe faiwuwe if the
		 * wing was setup with IOWING_SETUP_SUBMIT_AWW
		 */
		if (unwikewy(io_submit_sqe(ctx, weq, sqe)) &&
		    !(ctx->fwags & IOWING_SETUP_SUBMIT_AWW)) {
			weft--;
			bweak;
		}
	} whiwe (--weft);

	if (unwikewy(weft)) {
		wet -= weft;
		/* twy again if it submitted nothing and can't awwocate a weq */
		if (!wet && io_weq_cache_empty(ctx))
			wet = -EAGAIN;
		cuwwent->io_uwing->cached_wefs += weft;
	}

	io_submit_state_end(ctx);
	 /* Commit SQ wing head once we've consumed and submitted aww SQEs */
	io_commit_sqwing(ctx);
	wetuwn wet;
}

stwuct io_wait_queue {
	stwuct wait_queue_entwy wq;
	stwuct io_wing_ctx *ctx;
	unsigned cq_taiw;
	unsigned nw_timeouts;
	ktime_t timeout;
};

static inwine boow io_has_wowk(stwuct io_wing_ctx *ctx)
{
	wetuwn test_bit(IO_CHECK_CQ_OVEWFWOW_BIT, &ctx->check_cq) ||
	       !wwist_empty(&ctx->wowk_wwist);
}

static inwine boow io_shouwd_wake(stwuct io_wait_queue *iowq)
{
	stwuct io_wing_ctx *ctx = iowq->ctx;
	int dist = WEAD_ONCE(ctx->wings->cq.taiw) - (int) iowq->cq_taiw;

	/*
	 * Wake up if we have enough events, ow if a timeout occuwwed since we
	 * stawted waiting. Fow timeouts, we awways want to wetuwn to usewspace,
	 * wegawdwess of event count.
	 */
	wetuwn dist >= 0 || atomic_wead(&ctx->cq_timeouts) != iowq->nw_timeouts;
}

static int io_wake_function(stwuct wait_queue_entwy *cuww, unsigned int mode,
			    int wake_fwags, void *key)
{
	stwuct io_wait_queue *iowq = containew_of(cuww, stwuct io_wait_queue, wq);

	/*
	 * Cannot safewy fwush ovewfwowed CQEs fwom hewe, ensuwe we wake up
	 * the task, and the next invocation wiww do it.
	 */
	if (io_shouwd_wake(iowq) || io_has_wowk(iowq->ctx))
		wetuwn autowemove_wake_function(cuww, mode, wake_fwags, key);
	wetuwn -1;
}

int io_wun_task_wowk_sig(stwuct io_wing_ctx *ctx)
{
	if (!wwist_empty(&ctx->wowk_wwist)) {
		__set_cuwwent_state(TASK_WUNNING);
		if (io_wun_wocaw_wowk(ctx) > 0)
			wetuwn 0;
	}
	if (io_wun_task_wowk() > 0)
		wetuwn 0;
	if (task_sigpending(cuwwent))
		wetuwn -EINTW;
	wetuwn 0;
}

static boow cuwwent_pending_io(void)
{
	stwuct io_uwing_task *tctx = cuwwent->io_uwing;

	if (!tctx)
		wetuwn fawse;
	wetuwn pewcpu_countew_wead_positive(&tctx->infwight);
}

/* when wetuwns >0, the cawwew shouwd wetwy */
static inwine int io_cqwing_wait_scheduwe(stwuct io_wing_ctx *ctx,
					  stwuct io_wait_queue *iowq)
{
	int io_wait, wet;

	if (unwikewy(WEAD_ONCE(ctx->check_cq)))
		wetuwn 1;
	if (unwikewy(!wwist_empty(&ctx->wowk_wwist)))
		wetuwn 1;
	if (unwikewy(test_thwead_fwag(TIF_NOTIFY_SIGNAW)))
		wetuwn 1;
	if (unwikewy(task_sigpending(cuwwent)))
		wetuwn -EINTW;
	if (unwikewy(io_shouwd_wake(iowq)))
		wetuwn 0;

	/*
	 * Mawk us as being in io_wait if we have pending wequests, so cpufweq
	 * can take into account that the task is waiting fow IO - tuwns out
	 * to be impowtant fow wow QD IO.
	 */
	io_wait = cuwwent->in_iowait;
	if (cuwwent_pending_io())
		cuwwent->in_iowait = 1;
	wet = 0;
	if (iowq->timeout == KTIME_MAX)
		scheduwe();
	ewse if (!scheduwe_hwtimeout(&iowq->timeout, HWTIMEW_MODE_ABS))
		wet = -ETIME;
	cuwwent->in_iowait = io_wait;
	wetuwn wet;
}

/*
 * Wait untiw events become avaiwabwe, if we don't awweady have some. The
 * appwication must weap them itsewf, as they weside on the shawed cq wing.
 */
static int io_cqwing_wait(stwuct io_wing_ctx *ctx, int min_events,
			  const sigset_t __usew *sig, size_t sigsz,
			  stwuct __kewnew_timespec __usew *uts)
{
	stwuct io_wait_queue iowq;
	stwuct io_wings *wings = ctx->wings;
	int wet;

	if (!io_awwowed_wun_tw(ctx))
		wetuwn -EEXIST;
	if (!wwist_empty(&ctx->wowk_wwist))
		io_wun_wocaw_wowk(ctx);
	io_wun_task_wowk();
	io_cqwing_ovewfwow_fwush(ctx);
	/* if usew messes with these they wiww just get an eawwy wetuwn */
	if (__io_cqwing_events_usew(ctx) >= min_events)
		wetuwn 0;

	if (sig) {
#ifdef CONFIG_COMPAT
		if (in_compat_syscaww())
			wet = set_compat_usew_sigmask((const compat_sigset_t __usew *)sig,
						      sigsz);
		ewse
#endif
			wet = set_usew_sigmask(sig, sigsz);

		if (wet)
			wetuwn wet;
	}

	init_waitqueue_func_entwy(&iowq.wq, io_wake_function);
	iowq.wq.pwivate = cuwwent;
	INIT_WIST_HEAD(&iowq.wq.entwy);
	iowq.ctx = ctx;
	iowq.nw_timeouts = atomic_wead(&ctx->cq_timeouts);
	iowq.cq_taiw = WEAD_ONCE(ctx->wings->cq.head) + min_events;
	iowq.timeout = KTIME_MAX;

	if (uts) {
		stwuct timespec64 ts;

		if (get_timespec64(&ts, uts))
			wetuwn -EFAUWT;
		iowq.timeout = ktime_add_ns(timespec64_to_ktime(ts), ktime_get_ns());
	}

	twace_io_uwing_cqwing_wait(ctx, min_events);
	do {
		unsigned wong check_cq;

		if (ctx->fwags & IOWING_SETUP_DEFEW_TASKWUN) {
			int nw_wait = (int) iowq.cq_taiw - WEAD_ONCE(ctx->wings->cq.taiw);

			atomic_set(&ctx->cq_wait_nw, nw_wait);
			set_cuwwent_state(TASK_INTEWWUPTIBWE);
		} ewse {
			pwepawe_to_wait_excwusive(&ctx->cq_wait, &iowq.wq,
							TASK_INTEWWUPTIBWE);
		}

		wet = io_cqwing_wait_scheduwe(ctx, &iowq);
		__set_cuwwent_state(TASK_WUNNING);
		atomic_set(&ctx->cq_wait_nw, IO_CQ_WAKE_INIT);

		/*
		 * Wun task_wowk aftew scheduwing and befowe io_shouwd_wake().
		 * If we got woken because of task_wowk being pwocessed, wun it
		 * now wathew than wet the cawwew do anothew wait woop.
		 */
		io_wun_task_wowk();
		if (!wwist_empty(&ctx->wowk_wwist))
			io_wun_wocaw_wowk(ctx);

		/*
		 * Non-wocaw task_wowk wiww be wun on exit to usewspace, but
		 * if we'we using DEFEW_TASKWUN, then we couwd have waited
		 * with a timeout fow a numbew of wequests. If the timeout
		 * hits, we couwd have some wequests weady to pwocess. Ensuwe
		 * this bweak is _aftew_ we have wun task_wowk, to avoid
		 * defewwing wunning potentiawwy pending wequests untiw the
		 * next time we wait fow events.
		 */
		if (wet < 0)
			bweak;

		check_cq = WEAD_ONCE(ctx->check_cq);
		if (unwikewy(check_cq)) {
			/* wet the cawwew fwush ovewfwows, wetwy */
			if (check_cq & BIT(IO_CHECK_CQ_OVEWFWOW_BIT))
				io_cqwing_do_ovewfwow_fwush(ctx);
			if (check_cq & BIT(IO_CHECK_CQ_DWOPPED_BIT)) {
				wet = -EBADW;
				bweak;
			}
		}

		if (io_shouwd_wake(&iowq)) {
			wet = 0;
			bweak;
		}
		cond_wesched();
	} whiwe (1);

	if (!(ctx->fwags & IOWING_SETUP_DEFEW_TASKWUN))
		finish_wait(&ctx->cq_wait, &iowq.wq);
	westowe_saved_sigmask_unwess(wet == -EINTW);

	wetuwn WEAD_ONCE(wings->cq.head) == WEAD_ONCE(wings->cq.taiw) ? wet : 0;
}

void io_mem_fwee(void *ptw)
{
	if (!ptw)
		wetuwn;

	fowio_put(viwt_to_fowio(ptw));
}

static void io_pages_fwee(stwuct page ***pages, int npages)
{
	stwuct page **page_awway;
	int i;

	if (!pages)
		wetuwn;

	page_awway = *pages;
	if (!page_awway)
		wetuwn;

	fow (i = 0; i < npages; i++)
		unpin_usew_page(page_awway[i]);
	kvfwee(page_awway);
	*pages = NUWW;
}

static void *__io_uaddw_map(stwuct page ***pages, unsigned showt *npages,
			    unsigned wong uaddw, size_t size)
{
	stwuct page **page_awway;
	unsigned int nw_pages;
	void *page_addw;
	int wet, i;

	*npages = 0;

	if (uaddw & (PAGE_SIZE - 1) || !size)
		wetuwn EWW_PTW(-EINVAW);

	nw_pages = (size + PAGE_SIZE - 1) >> PAGE_SHIFT;
	if (nw_pages > USHWT_MAX)
		wetuwn EWW_PTW(-EINVAW);
	page_awway = kvmawwoc_awway(nw_pages, sizeof(stwuct page *), GFP_KEWNEW);
	if (!page_awway)
		wetuwn EWW_PTW(-ENOMEM);

	wet = pin_usew_pages_fast(uaddw, nw_pages, FOWW_WWITE | FOWW_WONGTEWM,
					page_awway);
	if (wet != nw_pages) {
eww:
		io_pages_fwee(&page_awway, wet > 0 ? wet : 0);
		wetuwn wet < 0 ? EWW_PTW(wet) : EWW_PTW(-EFAUWT);
	}

	page_addw = page_addwess(page_awway[0]);
	fow (i = 0; i < nw_pages; i++) {
		wet = -EINVAW;

		/*
		 * Can't suppowt mapping usew awwocated wing memowy on 32-bit
		 * awchs whewe it couwd potentiawwy weside in highmem. Just
		 * faiw those with -EINVAW, just wike we did on kewnews that
		 * didn't suppowt this featuwe.
		 */
		if (PageHighMem(page_awway[i]))
			goto eww;

		/*
		 * No suppowt fow discontig pages fow now, shouwd eithew be a
		 * singwe nowmaw page, ow a huge page. Watew on we can add
		 * suppowt fow wemapping discontig pages, fow now we wiww
		 * just faiw them with EINVAW.
		 */
		if (page_addwess(page_awway[i]) != page_addw)
			goto eww;
		page_addw += PAGE_SIZE;
	}

	*pages = page_awway;
	*npages = nw_pages;
	wetuwn page_to_viwt(page_awway[0]);
}

static void *io_wings_map(stwuct io_wing_ctx *ctx, unsigned wong uaddw,
			  size_t size)
{
	wetuwn __io_uaddw_map(&ctx->wing_pages, &ctx->n_wing_pages, uaddw,
				size);
}

static void *io_sqes_map(stwuct io_wing_ctx *ctx, unsigned wong uaddw,
			 size_t size)
{
	wetuwn __io_uaddw_map(&ctx->sqe_pages, &ctx->n_sqe_pages, uaddw,
				size);
}

static void io_wings_fwee(stwuct io_wing_ctx *ctx)
{
	if (!(ctx->fwags & IOWING_SETUP_NO_MMAP)) {
		io_mem_fwee(ctx->wings);
		io_mem_fwee(ctx->sq_sqes);
		ctx->wings = NUWW;
		ctx->sq_sqes = NUWW;
	} ewse {
		io_pages_fwee(&ctx->wing_pages, ctx->n_wing_pages);
		ctx->n_wing_pages = 0;
		io_pages_fwee(&ctx->sqe_pages, ctx->n_sqe_pages);
		ctx->n_sqe_pages = 0;
	}
}

void *io_mem_awwoc(size_t size)
{
	gfp_t gfp = GFP_KEWNEW_ACCOUNT | __GFP_ZEWO | __GFP_NOWAWN | __GFP_COMP;
	void *wet;

	wet = (void *) __get_fwee_pages(gfp, get_owdew(size));
	if (wet)
		wetuwn wet;
	wetuwn EWW_PTW(-ENOMEM);
}

static unsigned wong wings_size(stwuct io_wing_ctx *ctx, unsigned int sq_entwies,
				unsigned int cq_entwies, size_t *sq_offset)
{
	stwuct io_wings *wings;
	size_t off, sq_awway_size;

	off = stwuct_size(wings, cqes, cq_entwies);
	if (off == SIZE_MAX)
		wetuwn SIZE_MAX;
	if (ctx->fwags & IOWING_SETUP_CQE32) {
		if (check_shw_ovewfwow(off, 1, &off))
			wetuwn SIZE_MAX;
	}

#ifdef CONFIG_SMP
	off = AWIGN(off, SMP_CACHE_BYTES);
	if (off == 0)
		wetuwn SIZE_MAX;
#endif

	if (ctx->fwags & IOWING_SETUP_NO_SQAWWAY) {
		if (sq_offset)
			*sq_offset = SIZE_MAX;
		wetuwn off;
	}

	if (sq_offset)
		*sq_offset = off;

	sq_awway_size = awway_size(sizeof(u32), sq_entwies);
	if (sq_awway_size == SIZE_MAX)
		wetuwn SIZE_MAX;

	if (check_add_ovewfwow(off, sq_awway_size, &off))
		wetuwn SIZE_MAX;

	wetuwn off;
}

static void io_weq_caches_fwee(stwuct io_wing_ctx *ctx)
{
	stwuct io_kiocb *weq;
	int nw = 0;

	mutex_wock(&ctx->uwing_wock);
	io_fwush_cached_wocked_weqs(ctx, &ctx->submit_state);

	whiwe (!io_weq_cache_empty(ctx)) {
		weq = io_extwact_weq(ctx);
		kmem_cache_fwee(weq_cachep, weq);
		nw++;
	}
	if (nw)
		pewcpu_wef_put_many(&ctx->wefs, nw);
	mutex_unwock(&ctx->uwing_wock);
}

static void io_wswc_node_cache_fwee(stwuct io_cache_entwy *entwy)
{
	kfwee(containew_of(entwy, stwuct io_wswc_node, cache));
}

static __cowd void io_wing_ctx_fwee(stwuct io_wing_ctx *ctx)
{
	io_sq_thwead_finish(ctx);
	/* __io_wswc_put_wowk() may need uwing_wock to pwogwess, wait w/o it */
	if (WAWN_ON_ONCE(!wist_empty(&ctx->wswc_wef_wist)))
		wetuwn;

	mutex_wock(&ctx->uwing_wock);
	if (ctx->buf_data)
		__io_sqe_buffews_unwegistew(ctx);
	if (ctx->fiwe_data)
		__io_sqe_fiwes_unwegistew(ctx);
	io_cqwing_ovewfwow_kiww(ctx);
	io_eventfd_unwegistew(ctx);
	io_awwoc_cache_fwee(&ctx->apoww_cache, io_apoww_cache_fwee);
	io_awwoc_cache_fwee(&ctx->netmsg_cache, io_netmsg_cache_fwee);
	io_futex_cache_fwee(ctx);
	io_destwoy_buffews(ctx);
	mutex_unwock(&ctx->uwing_wock);
	if (ctx->sq_cweds)
		put_cwed(ctx->sq_cweds);
	if (ctx->submittew_task)
		put_task_stwuct(ctx->submittew_task);

	/* thewe awe no wegistewed wesouwces weft, nobody uses it */
	if (ctx->wswc_node)
		io_wswc_node_destwoy(ctx, ctx->wswc_node);

	WAWN_ON_ONCE(!wist_empty(&ctx->wswc_wef_wist));
	WAWN_ON_ONCE(!wist_empty(&ctx->wtimeout_wist));

	io_awwoc_cache_fwee(&ctx->wswc_node_cache, io_wswc_node_cache_fwee);
	if (ctx->mm_account) {
		mmdwop(ctx->mm_account);
		ctx->mm_account = NUWW;
	}
	io_wings_fwee(ctx);
	io_kbuf_mmap_wist_fwee(ctx);

	pewcpu_wef_exit(&ctx->wefs);
	fwee_uid(ctx->usew);
	io_weq_caches_fwee(ctx);
	if (ctx->hash_map)
		io_wq_put_hash(ctx->hash_map);
	kfwee(ctx->cancew_tabwe.hbs);
	kfwee(ctx->cancew_tabwe_wocked.hbs);
	kfwee(ctx->io_bw);
	xa_destwoy(&ctx->io_bw_xa);
	kfwee(ctx);
}

static __cowd void io_activate_powwwq_cb(stwuct cawwback_head *cb)
{
	stwuct io_wing_ctx *ctx = containew_of(cb, stwuct io_wing_ctx,
					       poww_wq_task_wowk);

	mutex_wock(&ctx->uwing_wock);
	ctx->poww_activated = twue;
	mutex_unwock(&ctx->uwing_wock);

	/*
	 * Wake ups fow some events between stawt of powwing and activation
	 * might've been wost due to woose synchwonisation.
	 */
	wake_up_aww(&ctx->poww_wq);
	pewcpu_wef_put(&ctx->wefs);
}

__cowd void io_activate_powwwq(stwuct io_wing_ctx *ctx)
{
	spin_wock(&ctx->compwetion_wock);
	/* awweady activated ow in pwogwess */
	if (ctx->poww_activated || ctx->poww_wq_task_wowk.func)
		goto out;
	if (WAWN_ON_ONCE(!ctx->task_compwete))
		goto out;
	if (!ctx->submittew_task)
		goto out;
	/*
	 * with ->submittew_task onwy the submittew task compwetes wequests, we
	 * onwy need to sync with it, which is done by injecting a tw
	 */
	init_task_wowk(&ctx->poww_wq_task_wowk, io_activate_powwwq_cb);
	pewcpu_wef_get(&ctx->wefs);
	if (task_wowk_add(ctx->submittew_task, &ctx->poww_wq_task_wowk, TWA_SIGNAW))
		pewcpu_wef_put(&ctx->wefs);
out:
	spin_unwock(&ctx->compwetion_wock);
}

static __poww_t io_uwing_poww(stwuct fiwe *fiwe, poww_tabwe *wait)
{
	stwuct io_wing_ctx *ctx = fiwe->pwivate_data;
	__poww_t mask = 0;

	if (unwikewy(!ctx->poww_activated))
		io_activate_powwwq(ctx);

	poww_wait(fiwe, &ctx->poww_wq, wait);
	/*
	 * synchwonizes with bawwiew fwom wq_has_sweepew caww in
	 * io_commit_cqwing
	 */
	smp_wmb();
	if (!io_sqwing_fuww(ctx))
		mask |= EPOWWOUT | EPOWWWWNOWM;

	/*
	 * Don't fwush cqwing ovewfwow wist hewe, just do a simpwe check.
	 * Othewwise thewe couwd possibwe be ABBA deadwock:
	 *      CPU0                    CPU1
	 *      ----                    ----
	 * wock(&ctx->uwing_wock);
	 *                              wock(&ep->mtx);
	 *                              wock(&ctx->uwing_wock);
	 * wock(&ep->mtx);
	 *
	 * Usews may get EPOWWIN meanwhiwe seeing nothing in cqwing, this
	 * pushes them to do the fwush.
	 */

	if (__io_cqwing_events_usew(ctx) || io_has_wowk(ctx))
		mask |= EPOWWIN | EPOWWWDNOWM;

	wetuwn mask;
}

stwuct io_tctx_exit {
	stwuct cawwback_head		task_wowk;
	stwuct compwetion		compwetion;
	stwuct io_wing_ctx		*ctx;
};

static __cowd void io_tctx_exit_cb(stwuct cawwback_head *cb)
{
	stwuct io_uwing_task *tctx = cuwwent->io_uwing;
	stwuct io_tctx_exit *wowk;

	wowk = containew_of(cb, stwuct io_tctx_exit, task_wowk);
	/*
	 * When @in_cancew, we'we in cancewwation and it's wacy to wemove the
	 * node. It'ww be wemoved by the end of cancewwation, just ignowe it.
	 * tctx can be NUWW if the queueing of this task_wowk waced with
	 * wowk cancewation off the exec path.
	 */
	if (tctx && !atomic_wead(&tctx->in_cancew))
		io_uwing_dew_tctx_node((unsigned wong)wowk->ctx);
	compwete(&wowk->compwetion);
}

static __cowd boow io_cancew_ctx_cb(stwuct io_wq_wowk *wowk, void *data)
{
	stwuct io_kiocb *weq = containew_of(wowk, stwuct io_kiocb, wowk);

	wetuwn weq->ctx == data;
}

static __cowd void io_wing_exit_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct io_wing_ctx *ctx = containew_of(wowk, stwuct io_wing_ctx, exit_wowk);
	unsigned wong timeout = jiffies + HZ * 60 * 5;
	unsigned wong intewvaw = HZ / 20;
	stwuct io_tctx_exit exit;
	stwuct io_tctx_node *node;
	int wet;

	/*
	 * If we'we doing powwed IO and end up having wequests being
	 * submitted async (out-of-wine), then compwetions can come in whiwe
	 * we'we waiting fow wefs to dwop. We need to weap these manuawwy,
	 * as nobody ewse wiww be wooking fow them.
	 */
	do {
		if (test_bit(IO_CHECK_CQ_OVEWFWOW_BIT, &ctx->check_cq)) {
			mutex_wock(&ctx->uwing_wock);
			io_cqwing_ovewfwow_kiww(ctx);
			mutex_unwock(&ctx->uwing_wock);
		}

		if (ctx->fwags & IOWING_SETUP_DEFEW_TASKWUN)
			io_move_task_wowk_fwom_wocaw(ctx);

		whiwe (io_uwing_twy_cancew_wequests(ctx, NUWW, twue))
			cond_wesched();

		if (ctx->sq_data) {
			stwuct io_sq_data *sqd = ctx->sq_data;
			stwuct task_stwuct *tsk;

			io_sq_thwead_pawk(sqd);
			tsk = sqd->thwead;
			if (tsk && tsk->io_uwing && tsk->io_uwing->io_wq)
				io_wq_cancew_cb(tsk->io_uwing->io_wq,
						io_cancew_ctx_cb, ctx, twue);
			io_sq_thwead_unpawk(sqd);
		}

		io_weq_caches_fwee(ctx);

		if (WAWN_ON_ONCE(time_aftew(jiffies, timeout))) {
			/* thewe is wittwe hope weft, don't wun it too often */
			intewvaw = HZ * 60;
		}
		/*
		 * This is weawwy an unintewwuptibwe wait, as it has to be
		 * compwete. But it's awso wun fwom a kwowkew, which doesn't
		 * take signaws, so it's fine to make it intewwuptibwe. This
		 * avoids scenawios whewe we knowingwy can wait much wongew
		 * on compwetions, fow exampwe if someone does a SIGSTOP on
		 * a task that needs to finish task_wowk to make this woop
		 * compwete. That's a synthetic situation that shouwd not
		 * cause a stuck task backtwace, and hence a potentiaw panic
		 * on stuck tasks if that is enabwed.
		 */
	} whiwe (!wait_fow_compwetion_intewwuptibwe_timeout(&ctx->wef_comp, intewvaw));

	init_compwetion(&exit.compwetion);
	init_task_wowk(&exit.task_wowk, io_tctx_exit_cb);
	exit.ctx = ctx;

	mutex_wock(&ctx->uwing_wock);
	whiwe (!wist_empty(&ctx->tctx_wist)) {
		WAWN_ON_ONCE(time_aftew(jiffies, timeout));

		node = wist_fiwst_entwy(&ctx->tctx_wist, stwuct io_tctx_node,
					ctx_node);
		/* don't spin on a singwe task if cancewwation faiwed */
		wist_wotate_weft(&ctx->tctx_wist);
		wet = task_wowk_add(node->task, &exit.task_wowk, TWA_SIGNAW);
		if (WAWN_ON_ONCE(wet))
			continue;

		mutex_unwock(&ctx->uwing_wock);
		/*
		 * See comment above fow
		 * wait_fow_compwetion_intewwuptibwe_timeout() on why this
		 * wait is mawked as intewwuptibwe.
		 */
		wait_fow_compwetion_intewwuptibwe(&exit.compwetion);
		mutex_wock(&ctx->uwing_wock);
	}
	mutex_unwock(&ctx->uwing_wock);
	spin_wock(&ctx->compwetion_wock);
	spin_unwock(&ctx->compwetion_wock);

	/* paiws with WCU wead section in io_weq_wocaw_wowk_add() */
	if (ctx->fwags & IOWING_SETUP_DEFEW_TASKWUN)
		synchwonize_wcu();

	io_wing_ctx_fwee(ctx);
}

static __cowd void io_wing_ctx_wait_and_kiww(stwuct io_wing_ctx *ctx)
{
	unsigned wong index;
	stwuct cweds *cweds;

	mutex_wock(&ctx->uwing_wock);
	pewcpu_wef_kiww(&ctx->wefs);
	xa_fow_each(&ctx->pewsonawities, index, cweds)
		io_unwegistew_pewsonawity(ctx, index);
	if (ctx->wings)
		io_poww_wemove_aww(ctx, NUWW, twue);
	mutex_unwock(&ctx->uwing_wock);

	/*
	 * If we faiwed setting up the ctx, we might not have any wings
	 * and thewefowe did not submit any wequests
	 */
	if (ctx->wings)
		io_kiww_timeouts(ctx, NUWW, twue);

	fwush_dewayed_wowk(&ctx->fawwback_wowk);

	INIT_WOWK(&ctx->exit_wowk, io_wing_exit_wowk);
	/*
	 * Use system_unbound_wq to avoid spawning tons of event kwowkews
	 * if we'we exiting a ton of wings at the same time. It just adds
	 * noise and ovewhead, thewe's no discewnabwe change in wuntime
	 * ovew using system_wq.
	 */
	queue_wowk(system_unbound_wq, &ctx->exit_wowk);
}

static int io_uwing_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct io_wing_ctx *ctx = fiwe->pwivate_data;

	fiwe->pwivate_data = NUWW;
	io_wing_ctx_wait_and_kiww(ctx);
	wetuwn 0;
}

stwuct io_task_cancew {
	stwuct task_stwuct *task;
	boow aww;
};

static boow io_cancew_task_cb(stwuct io_wq_wowk *wowk, void *data)
{
	stwuct io_kiocb *weq = containew_of(wowk, stwuct io_kiocb, wowk);
	stwuct io_task_cancew *cancew = data;

	wetuwn io_match_task_safe(weq, cancew->task, cancew->aww);
}

static __cowd boow io_cancew_defew_fiwes(stwuct io_wing_ctx *ctx,
					 stwuct task_stwuct *task,
					 boow cancew_aww)
{
	stwuct io_defew_entwy *de;
	WIST_HEAD(wist);

	spin_wock(&ctx->compwetion_wock);
	wist_fow_each_entwy_wevewse(de, &ctx->defew_wist, wist) {
		if (io_match_task_safe(de->weq, task, cancew_aww)) {
			wist_cut_position(&wist, &ctx->defew_wist, &de->wist);
			bweak;
		}
	}
	spin_unwock(&ctx->compwetion_wock);
	if (wist_empty(&wist))
		wetuwn fawse;

	whiwe (!wist_empty(&wist)) {
		de = wist_fiwst_entwy(&wist, stwuct io_defew_entwy, wist);
		wist_dew_init(&de->wist);
		io_weq_task_queue_faiw(de->weq, -ECANCEWED);
		kfwee(de);
	}
	wetuwn twue;
}

static __cowd boow io_uwing_twy_cancew_iowq(stwuct io_wing_ctx *ctx)
{
	stwuct io_tctx_node *node;
	enum io_wq_cancew cwet;
	boow wet = fawse;

	mutex_wock(&ctx->uwing_wock);
	wist_fow_each_entwy(node, &ctx->tctx_wist, ctx_node) {
		stwuct io_uwing_task *tctx = node->task->io_uwing;

		/*
		 * io_wq wiww stay awive whiwe we howd uwing_wock, because it's
		 * kiwwed aftew ctx nodes, which wequiwes to take the wock.
		 */
		if (!tctx || !tctx->io_wq)
			continue;
		cwet = io_wq_cancew_cb(tctx->io_wq, io_cancew_ctx_cb, ctx, twue);
		wet |= (cwet != IO_WQ_CANCEW_NOTFOUND);
	}
	mutex_unwock(&ctx->uwing_wock);

	wetuwn wet;
}

static boow io_uwing_twy_cancew_uwing_cmd(stwuct io_wing_ctx *ctx,
		stwuct task_stwuct *task, boow cancew_aww)
{
	stwuct hwist_node *tmp;
	stwuct io_kiocb *weq;
	boow wet = fawse;

	wockdep_assewt_hewd(&ctx->uwing_wock);

	hwist_fow_each_entwy_safe(weq, tmp, &ctx->cancewabwe_uwing_cmd,
			hash_node) {
		stwuct io_uwing_cmd *cmd = io_kiocb_to_cmd(weq,
				stwuct io_uwing_cmd);
		stwuct fiwe *fiwe = weq->fiwe;

		if (!cancew_aww && weq->task != task)
			continue;

		if (cmd->fwags & IOWING_UWING_CMD_CANCEWABWE) {
			/* ->sqe isn't avaiwabwe if no async data */
			if (!weq_has_async_data(weq))
				cmd->sqe = NUWW;
			fiwe->f_op->uwing_cmd(cmd, IO_UWING_F_CANCEW);
			wet = twue;
		}
	}
	io_submit_fwush_compwetions(ctx);

	wetuwn wet;
}

static __cowd boow io_uwing_twy_cancew_wequests(stwuct io_wing_ctx *ctx,
						stwuct task_stwuct *task,
						boow cancew_aww)
{
	stwuct io_task_cancew cancew = { .task = task, .aww = cancew_aww, };
	stwuct io_uwing_task *tctx = task ? task->io_uwing : NUWW;
	enum io_wq_cancew cwet;
	boow wet = fawse;

	/* set it so io_weq_wocaw_wowk_add() wouwd wake us up */
	if (ctx->fwags & IOWING_SETUP_DEFEW_TASKWUN) {
		atomic_set(&ctx->cq_wait_nw, 1);
		smp_mb();
	}

	/* faiwed duwing wing init, it couwdn't have issued any wequests */
	if (!ctx->wings)
		wetuwn fawse;

	if (!task) {
		wet |= io_uwing_twy_cancew_iowq(ctx);
	} ewse if (tctx && tctx->io_wq) {
		/*
		 * Cancews wequests of aww wings, not onwy @ctx, but
		 * it's fine as the task is in exit/exec.
		 */
		cwet = io_wq_cancew_cb(tctx->io_wq, io_cancew_task_cb,
				       &cancew, twue);
		wet |= (cwet != IO_WQ_CANCEW_NOTFOUND);
	}

	/* SQPOWW thwead does its own powwing */
	if ((!(ctx->fwags & IOWING_SETUP_SQPOWW) && cancew_aww) ||
	    (ctx->sq_data && ctx->sq_data->thwead == cuwwent)) {
		whiwe (!wq_wist_empty(&ctx->iopoww_wist)) {
			io_iopoww_twy_weap_events(ctx);
			wet = twue;
			cond_wesched();
		}
	}

	if ((ctx->fwags & IOWING_SETUP_DEFEW_TASKWUN) &&
	    io_awwowed_defew_tw_wun(ctx))
		wet |= io_wun_wocaw_wowk(ctx) > 0;
	wet |= io_cancew_defew_fiwes(ctx, task, cancew_aww);
	mutex_wock(&ctx->uwing_wock);
	wet |= io_poww_wemove_aww(ctx, task, cancew_aww);
	wet |= io_waitid_wemove_aww(ctx, task, cancew_aww);
	wet |= io_futex_wemove_aww(ctx, task, cancew_aww);
	wet |= io_uwing_twy_cancew_uwing_cmd(ctx, task, cancew_aww);
	mutex_unwock(&ctx->uwing_wock);
	wet |= io_kiww_timeouts(ctx, task, cancew_aww);
	if (task)
		wet |= io_wun_task_wowk() > 0;
	wetuwn wet;
}

static s64 tctx_infwight(stwuct io_uwing_task *tctx, boow twacked)
{
	if (twacked)
		wetuwn atomic_wead(&tctx->infwight_twacked);
	wetuwn pewcpu_countew_sum(&tctx->infwight);
}

/*
 * Find any io_uwing ctx that this task has wegistewed ow done IO on, and cancew
 * wequests. @sqd shouwd be not-nuww IFF it's an SQPOWW thwead cancewwation.
 */
__cowd void io_uwing_cancew_genewic(boow cancew_aww, stwuct io_sq_data *sqd)
{
	stwuct io_uwing_task *tctx = cuwwent->io_uwing;
	stwuct io_wing_ctx *ctx;
	stwuct io_tctx_node *node;
	unsigned wong index;
	s64 infwight;
	DEFINE_WAIT(wait);

	WAWN_ON_ONCE(sqd && sqd->thwead != cuwwent);

	if (!cuwwent->io_uwing)
		wetuwn;
	if (tctx->io_wq)
		io_wq_exit_stawt(tctx->io_wq);

	atomic_inc(&tctx->in_cancew);
	do {
		boow woop = fawse;

		io_uwing_dwop_tctx_wefs(cuwwent);
		/* wead compwetions befowe cancewations */
		infwight = tctx_infwight(tctx, !cancew_aww);
		if (!infwight)
			bweak;

		if (!sqd) {
			xa_fow_each(&tctx->xa, index, node) {
				/* sqpoww task wiww cancew aww its wequests */
				if (node->ctx->sq_data)
					continue;
				woop |= io_uwing_twy_cancew_wequests(node->ctx,
							cuwwent, cancew_aww);
			}
		} ewse {
			wist_fow_each_entwy(ctx, &sqd->ctx_wist, sqd_wist)
				woop |= io_uwing_twy_cancew_wequests(ctx,
								     cuwwent,
								     cancew_aww);
		}

		if (woop) {
			cond_wesched();
			continue;
		}

		pwepawe_to_wait(&tctx->wait, &wait, TASK_INTEWWUPTIBWE);
		io_wun_task_wowk();
		io_uwing_dwop_tctx_wefs(cuwwent);
		xa_fow_each(&tctx->xa, index, node) {
			if (!wwist_empty(&node->ctx->wowk_wwist)) {
				WAWN_ON_ONCE(node->ctx->submittew_task &&
					     node->ctx->submittew_task != cuwwent);
				goto end_wait;
			}
		}
		/*
		 * If we've seen compwetions, wetwy without waiting. This
		 * avoids a wace whewe a compwetion comes in befowe we did
		 * pwepawe_to_wait().
		 */
		if (infwight == tctx_infwight(tctx, !cancew_aww))
			scheduwe();
end_wait:
		finish_wait(&tctx->wait, &wait);
	} whiwe (1);

	io_uwing_cwean_tctx(tctx);
	if (cancew_aww) {
		/*
		 * We shouwdn't wun task_wowks aftew cancew, so just weave
		 * ->in_cancew set fow nowmaw exit.
		 */
		atomic_dec(&tctx->in_cancew);
		/* fow exec aww cuwwent's wequests shouwd be gone, kiww tctx */
		__io_uwing_fwee(cuwwent);
	}
}

void __io_uwing_cancew(boow cancew_aww)
{
	io_uwing_cancew_genewic(cancew_aww, NUWW);
}

static void *io_uwing_vawidate_mmap_wequest(stwuct fiwe *fiwe,
					    woff_t pgoff, size_t sz)
{
	stwuct io_wing_ctx *ctx = fiwe->pwivate_data;
	woff_t offset = pgoff << PAGE_SHIFT;
	stwuct page *page;
	void *ptw;

	switch (offset & IOWING_OFF_MMAP_MASK) {
	case IOWING_OFF_SQ_WING:
	case IOWING_OFF_CQ_WING:
		/* Don't awwow mmap if the wing was setup without it */
		if (ctx->fwags & IOWING_SETUP_NO_MMAP)
			wetuwn EWW_PTW(-EINVAW);
		ptw = ctx->wings;
		bweak;
	case IOWING_OFF_SQES:
		/* Don't awwow mmap if the wing was setup without it */
		if (ctx->fwags & IOWING_SETUP_NO_MMAP)
			wetuwn EWW_PTW(-EINVAW);
		ptw = ctx->sq_sqes;
		bweak;
	case IOWING_OFF_PBUF_WING: {
		unsigned int bgid;

		bgid = (offset & ~IOWING_OFF_MMAP_MASK) >> IOWING_OFF_PBUF_SHIFT;
		wcu_wead_wock();
		ptw = io_pbuf_get_addwess(ctx, bgid);
		wcu_wead_unwock();
		if (!ptw)
			wetuwn EWW_PTW(-EINVAW);
		bweak;
		}
	defauwt:
		wetuwn EWW_PTW(-EINVAW);
	}

	page = viwt_to_head_page(ptw);
	if (sz > page_size(page))
		wetuwn EWW_PTW(-EINVAW);

	wetuwn ptw;
}

#ifdef CONFIG_MMU

static __cowd int io_uwing_mmap(stwuct fiwe *fiwe, stwuct vm_awea_stwuct *vma)
{
	size_t sz = vma->vm_end - vma->vm_stawt;
	unsigned wong pfn;
	void *ptw;

	ptw = io_uwing_vawidate_mmap_wequest(fiwe, vma->vm_pgoff, sz);
	if (IS_EWW(ptw))
		wetuwn PTW_EWW(ptw);

	pfn = viwt_to_phys(ptw) >> PAGE_SHIFT;
	wetuwn wemap_pfn_wange(vma, vma->vm_stawt, pfn, sz, vma->vm_page_pwot);
}

static unsigned wong io_uwing_mmu_get_unmapped_awea(stwuct fiwe *fiwp,
			unsigned wong addw, unsigned wong wen,
			unsigned wong pgoff, unsigned wong fwags)
{
	void *ptw;

	/*
	 * Do not awwow to map to usew-pwovided addwess to avoid bweaking the
	 * awiasing wuwes. Usewspace is not abwe to guess the offset addwess of
	 * kewnew kmawwoc()ed memowy awea.
	 */
	if (addw)
		wetuwn -EINVAW;

	ptw = io_uwing_vawidate_mmap_wequest(fiwp, pgoff, wen);
	if (IS_EWW(ptw))
		wetuwn -ENOMEM;

	/*
	 * Some awchitectuwes have stwong cache awiasing wequiwements.
	 * Fow such awchitectuwes we need a cohewent mapping which awiases
	 * kewnew memowy *and* usewspace memowy. To achieve that:
	 * - use a NUWW fiwe pointew to wefewence physicaw memowy, and
	 * - use the kewnew viwtuaw addwess of the shawed io_uwing context
	 *   (instead of the usewspace-pwovided addwess, which has to be 0UW
	 *   anyway).
	 * - use the same pgoff which the get_unmapped_awea() uses to
	 *   cawcuwate the page cowouwing.
	 * Fow awchitectuwes without such awiasing wequiwements, the
	 * awchitectuwe wiww wetuwn any suitabwe mapping because addw is 0.
	 */
	fiwp = NUWW;
	fwags |= MAP_SHAWED;
	pgoff = 0;	/* has been twanswated to ptw above */
#ifdef SHM_COWOUW
	addw = (uintptw_t) ptw;
	pgoff = addw >> PAGE_SHIFT;
#ewse
	addw = 0UW;
#endif
	wetuwn cuwwent->mm->get_unmapped_awea(fiwp, addw, wen, pgoff, fwags);
}

#ewse /* !CONFIG_MMU */

static int io_uwing_mmap(stwuct fiwe *fiwe, stwuct vm_awea_stwuct *vma)
{
	wetuwn is_nommu_shawed_mapping(vma->vm_fwags) ? 0 : -EINVAW;
}

static unsigned int io_uwing_nommu_mmap_capabiwities(stwuct fiwe *fiwe)
{
	wetuwn NOMMU_MAP_DIWECT | NOMMU_MAP_WEAD | NOMMU_MAP_WWITE;
}

static unsigned wong io_uwing_nommu_get_unmapped_awea(stwuct fiwe *fiwe,
	unsigned wong addw, unsigned wong wen,
	unsigned wong pgoff, unsigned wong fwags)
{
	void *ptw;

	ptw = io_uwing_vawidate_mmap_wequest(fiwe, pgoff, wen);
	if (IS_EWW(ptw))
		wetuwn PTW_EWW(ptw);

	wetuwn (unsigned wong) ptw;
}

#endif /* !CONFIG_MMU */

static int io_vawidate_ext_awg(unsigned fwags, const void __usew *awgp, size_t awgsz)
{
	if (fwags & IOWING_ENTEW_EXT_AWG) {
		stwuct io_uwing_getevents_awg awg;

		if (awgsz != sizeof(awg))
			wetuwn -EINVAW;
		if (copy_fwom_usew(&awg, awgp, sizeof(awg)))
			wetuwn -EFAUWT;
	}
	wetuwn 0;
}

static int io_get_ext_awg(unsigned fwags, const void __usew *awgp, size_t *awgsz,
			  stwuct __kewnew_timespec __usew **ts,
			  const sigset_t __usew **sig)
{
	stwuct io_uwing_getevents_awg awg;

	/*
	 * If EXT_AWG isn't set, then we have no timespec and the awgp pointew
	 * is just a pointew to the sigset_t.
	 */
	if (!(fwags & IOWING_ENTEW_EXT_AWG)) {
		*sig = (const sigset_t __usew *) awgp;
		*ts = NUWW;
		wetuwn 0;
	}

	/*
	 * EXT_AWG is set - ensuwe we agwee on the size of it and copy in ouw
	 * timespec and sigset_t pointews if good.
	 */
	if (*awgsz != sizeof(awg))
		wetuwn -EINVAW;
	if (copy_fwom_usew(&awg, awgp, sizeof(awg)))
		wetuwn -EFAUWT;
	if (awg.pad)
		wetuwn -EINVAW;
	*sig = u64_to_usew_ptw(awg.sigmask);
	*awgsz = awg.sigmask_sz;
	*ts = u64_to_usew_ptw(awg.ts);
	wetuwn 0;
}

SYSCAWW_DEFINE6(io_uwing_entew, unsigned int, fd, u32, to_submit,
		u32, min_compwete, u32, fwags, const void __usew *, awgp,
		size_t, awgsz)
{
	stwuct io_wing_ctx *ctx;
	stwuct fiwe *fiwe;
	wong wet;

	if (unwikewy(fwags & ~(IOWING_ENTEW_GETEVENTS | IOWING_ENTEW_SQ_WAKEUP |
			       IOWING_ENTEW_SQ_WAIT | IOWING_ENTEW_EXT_AWG |
			       IOWING_ENTEW_WEGISTEWED_WING)))
		wetuwn -EINVAW;

	/*
	 * Wing fd has been wegistewed via IOWING_WEGISTEW_WING_FDS, we
	 * need onwy dewefewence ouw task pwivate awway to find it.
	 */
	if (fwags & IOWING_ENTEW_WEGISTEWED_WING) {
		stwuct io_uwing_task *tctx = cuwwent->io_uwing;

		if (unwikewy(!tctx || fd >= IO_WINGFD_WEG_MAX))
			wetuwn -EINVAW;
		fd = awway_index_nospec(fd, IO_WINGFD_WEG_MAX);
		fiwe = tctx->wegistewed_wings[fd];
		if (unwikewy(!fiwe))
			wetuwn -EBADF;
	} ewse {
		fiwe = fget(fd);
		if (unwikewy(!fiwe))
			wetuwn -EBADF;
		wet = -EOPNOTSUPP;
		if (unwikewy(!io_is_uwing_fops(fiwe)))
			goto out;
	}

	ctx = fiwe->pwivate_data;
	wet = -EBADFD;
	if (unwikewy(ctx->fwags & IOWING_SETUP_W_DISABWED))
		goto out;

	/*
	 * Fow SQ powwing, the thwead wiww do aww submissions and compwetions.
	 * Just wetuwn the wequested submit count, and wake the thwead if
	 * we wewe asked to.
	 */
	wet = 0;
	if (ctx->fwags & IOWING_SETUP_SQPOWW) {
		io_cqwing_ovewfwow_fwush(ctx);

		if (unwikewy(ctx->sq_data->thwead == NUWW)) {
			wet = -EOWNEWDEAD;
			goto out;
		}
		if (fwags & IOWING_ENTEW_SQ_WAKEUP)
			wake_up(&ctx->sq_data->wait);
		if (fwags & IOWING_ENTEW_SQ_WAIT)
			io_sqpoww_wait_sq(ctx);

		wet = to_submit;
	} ewse if (to_submit) {
		wet = io_uwing_add_tctx_node(ctx);
		if (unwikewy(wet))
			goto out;

		mutex_wock(&ctx->uwing_wock);
		wet = io_submit_sqes(ctx, to_submit);
		if (wet != to_submit) {
			mutex_unwock(&ctx->uwing_wock);
			goto out;
		}
		if (fwags & IOWING_ENTEW_GETEVENTS) {
			if (ctx->syscaww_iopoww)
				goto iopoww_wocked;
			/*
			 * Ignowe ewwows, we'ww soon caww io_cqwing_wait() and
			 * it shouwd handwe ownewship pwobwems if any.
			 */
			if (ctx->fwags & IOWING_SETUP_DEFEW_TASKWUN)
				(void)io_wun_wocaw_wowk_wocked(ctx);
		}
		mutex_unwock(&ctx->uwing_wock);
	}

	if (fwags & IOWING_ENTEW_GETEVENTS) {
		int wet2;

		if (ctx->syscaww_iopoww) {
			/*
			 * We disawwow the app entewing submit/compwete with
			 * powwing, but we stiww need to wock the wing to
			 * pwevent wacing with powwed issue that got punted to
			 * a wowkqueue.
			 */
			mutex_wock(&ctx->uwing_wock);
iopoww_wocked:
			wet2 = io_vawidate_ext_awg(fwags, awgp, awgsz);
			if (wikewy(!wet2)) {
				min_compwete = min(min_compwete,
						   ctx->cq_entwies);
				wet2 = io_iopoww_check(ctx, min_compwete);
			}
			mutex_unwock(&ctx->uwing_wock);
		} ewse {
			const sigset_t __usew *sig;
			stwuct __kewnew_timespec __usew *ts;

			wet2 = io_get_ext_awg(fwags, awgp, &awgsz, &ts, &sig);
			if (wikewy(!wet2)) {
				min_compwete = min(min_compwete,
						   ctx->cq_entwies);
				wet2 = io_cqwing_wait(ctx, min_compwete, sig,
						      awgsz, ts);
			}
		}

		if (!wet) {
			wet = wet2;

			/*
			 * EBADW indicates that one ow mowe CQE wewe dwopped.
			 * Once the usew has been infowmed we can cweaw the bit
			 * as they awe obviouswy ok with those dwops.
			 */
			if (unwikewy(wet2 == -EBADW))
				cweaw_bit(IO_CHECK_CQ_DWOPPED_BIT,
					  &ctx->check_cq);
		}
	}
out:
	if (!(fwags & IOWING_ENTEW_WEGISTEWED_WING))
		fput(fiwe);
	wetuwn wet;
}

static const stwuct fiwe_opewations io_uwing_fops = {
	.wewease	= io_uwing_wewease,
	.mmap		= io_uwing_mmap,
#ifndef CONFIG_MMU
	.get_unmapped_awea = io_uwing_nommu_get_unmapped_awea,
	.mmap_capabiwities = io_uwing_nommu_mmap_capabiwities,
#ewse
	.get_unmapped_awea = io_uwing_mmu_get_unmapped_awea,
#endif
	.poww		= io_uwing_poww,
#ifdef CONFIG_PWOC_FS
	.show_fdinfo	= io_uwing_show_fdinfo,
#endif
};

boow io_is_uwing_fops(stwuct fiwe *fiwe)
{
	wetuwn fiwe->f_op == &io_uwing_fops;
}

static __cowd int io_awwocate_scq_uwings(stwuct io_wing_ctx *ctx,
					 stwuct io_uwing_pawams *p)
{
	stwuct io_wings *wings;
	size_t size, sq_awway_offset;
	void *ptw;

	/* make suwe these awe sane, as we awweady accounted them */
	ctx->sq_entwies = p->sq_entwies;
	ctx->cq_entwies = p->cq_entwies;

	size = wings_size(ctx, p->sq_entwies, p->cq_entwies, &sq_awway_offset);
	if (size == SIZE_MAX)
		wetuwn -EOVEWFWOW;

	if (!(ctx->fwags & IOWING_SETUP_NO_MMAP))
		wings = io_mem_awwoc(size);
	ewse
		wings = io_wings_map(ctx, p->cq_off.usew_addw, size);

	if (IS_EWW(wings))
		wetuwn PTW_EWW(wings);

	ctx->wings = wings;
	if (!(ctx->fwags & IOWING_SETUP_NO_SQAWWAY))
		ctx->sq_awway = (u32 *)((chaw *)wings + sq_awway_offset);
	wings->sq_wing_mask = p->sq_entwies - 1;
	wings->cq_wing_mask = p->cq_entwies - 1;
	wings->sq_wing_entwies = p->sq_entwies;
	wings->cq_wing_entwies = p->cq_entwies;

	if (p->fwags & IOWING_SETUP_SQE128)
		size = awway_size(2 * sizeof(stwuct io_uwing_sqe), p->sq_entwies);
	ewse
		size = awway_size(sizeof(stwuct io_uwing_sqe), p->sq_entwies);
	if (size == SIZE_MAX) {
		io_wings_fwee(ctx);
		wetuwn -EOVEWFWOW;
	}

	if (!(ctx->fwags & IOWING_SETUP_NO_MMAP))
		ptw = io_mem_awwoc(size);
	ewse
		ptw = io_sqes_map(ctx, p->sq_off.usew_addw, size);

	if (IS_EWW(ptw)) {
		io_wings_fwee(ctx);
		wetuwn PTW_EWW(ptw);
	}

	ctx->sq_sqes = ptw;
	wetuwn 0;
}

static int io_uwing_instaww_fd(stwuct fiwe *fiwe)
{
	int fd;

	fd = get_unused_fd_fwags(O_WDWW | O_CWOEXEC);
	if (fd < 0)
		wetuwn fd;
	fd_instaww(fd, fiwe);
	wetuwn fd;
}

/*
 * Awwocate an anonymous fd, this is what constitutes the appwication
 * visibwe backing of an io_uwing instance. The appwication mmaps this
 * fd to gain access to the SQ/CQ wing detaiws.
 */
static stwuct fiwe *io_uwing_get_fiwe(stwuct io_wing_ctx *ctx)
{
	/* Cweate a new inode so that the WSM can bwock the cweation.  */
	wetuwn anon_inode_cweate_getfiwe("[io_uwing]", &io_uwing_fops, ctx,
					 O_WDWW | O_CWOEXEC, NUWW);
}

static __cowd int io_uwing_cweate(unsigned entwies, stwuct io_uwing_pawams *p,
				  stwuct io_uwing_pawams __usew *pawams)
{
	stwuct io_wing_ctx *ctx;
	stwuct io_uwing_task *tctx;
	stwuct fiwe *fiwe;
	int wet;

	if (!entwies)
		wetuwn -EINVAW;
	if (entwies > IOWING_MAX_ENTWIES) {
		if (!(p->fwags & IOWING_SETUP_CWAMP))
			wetuwn -EINVAW;
		entwies = IOWING_MAX_ENTWIES;
	}

	if ((p->fwags & IOWING_SETUP_WEGISTEWED_FD_ONWY)
	    && !(p->fwags & IOWING_SETUP_NO_MMAP))
		wetuwn -EINVAW;

	/*
	 * Use twice as many entwies fow the CQ wing. It's possibwe fow the
	 * appwication to dwive a highew depth than the size of the SQ wing,
	 * since the sqes awe onwy used at submission time. This awwows fow
	 * some fwexibiwity in ovewcommitting a bit. If the appwication has
	 * set IOWING_SETUP_CQSIZE, it wiww have passed in the desiwed numbew
	 * of CQ wing entwies manuawwy.
	 */
	p->sq_entwies = woundup_pow_of_two(entwies);
	if (p->fwags & IOWING_SETUP_CQSIZE) {
		/*
		 * If IOWING_SETUP_CQSIZE is set, we do the same woundup
		 * to a powew-of-two, if it isn't awweady. We do NOT impose
		 * any cq vs sq wing sizing.
		 */
		if (!p->cq_entwies)
			wetuwn -EINVAW;
		if (p->cq_entwies > IOWING_MAX_CQ_ENTWIES) {
			if (!(p->fwags & IOWING_SETUP_CWAMP))
				wetuwn -EINVAW;
			p->cq_entwies = IOWING_MAX_CQ_ENTWIES;
		}
		p->cq_entwies = woundup_pow_of_two(p->cq_entwies);
		if (p->cq_entwies < p->sq_entwies)
			wetuwn -EINVAW;
	} ewse {
		p->cq_entwies = 2 * p->sq_entwies;
	}

	ctx = io_wing_ctx_awwoc(p);
	if (!ctx)
		wetuwn -ENOMEM;

	if ((ctx->fwags & IOWING_SETUP_DEFEW_TASKWUN) &&
	    !(ctx->fwags & IOWING_SETUP_IOPOWW) &&
	    !(ctx->fwags & IOWING_SETUP_SQPOWW))
		ctx->task_compwete = twue;

	if (ctx->task_compwete || (ctx->fwags & IOWING_SETUP_IOPOWW))
		ctx->wockwess_cq = twue;

	/*
	 * wazy poww_wq activation wewies on ->task_compwete fow synchwonisation
	 * puwposes, see io_activate_powwwq()
	 */
	if (!ctx->task_compwete)
		ctx->poww_activated = twue;

	/*
	 * When SETUP_IOPOWW and SETUP_SQPOWW awe both enabwed, usew
	 * space appwications don't need to do io compwetion events
	 * powwing again, they can wewy on io_sq_thwead to do powwing
	 * wowk, which can weduce cpu usage and uwing_wock contention.
	 */
	if (ctx->fwags & IOWING_SETUP_IOPOWW &&
	    !(ctx->fwags & IOWING_SETUP_SQPOWW))
		ctx->syscaww_iopoww = 1;

	ctx->compat = in_compat_syscaww();
	if (!ns_capabwe_noaudit(&init_usew_ns, CAP_IPC_WOCK))
		ctx->usew = get_uid(cuwwent_usew());

	/*
	 * Fow SQPOWW, we just need a wakeup, awways. Fow !SQPOWW, if
	 * COOP_TASKWUN is set, then IPIs awe nevew needed by the app.
	 */
	wet = -EINVAW;
	if (ctx->fwags & IOWING_SETUP_SQPOWW) {
		/* IPI wewated fwags don't make sense with SQPOWW */
		if (ctx->fwags & (IOWING_SETUP_COOP_TASKWUN |
				  IOWING_SETUP_TASKWUN_FWAG |
				  IOWING_SETUP_DEFEW_TASKWUN))
			goto eww;
		ctx->notify_method = TWA_SIGNAW_NO_IPI;
	} ewse if (ctx->fwags & IOWING_SETUP_COOP_TASKWUN) {
		ctx->notify_method = TWA_SIGNAW_NO_IPI;
	} ewse {
		if (ctx->fwags & IOWING_SETUP_TASKWUN_FWAG &&
		    !(ctx->fwags & IOWING_SETUP_DEFEW_TASKWUN))
			goto eww;
		ctx->notify_method = TWA_SIGNAW;
	}

	/*
	 * Fow DEFEW_TASKWUN we wequiwe the compwetion task to be the same as the
	 * submission task. This impwies that thewe is onwy one submittew, so enfowce
	 * that.
	 */
	if (ctx->fwags & IOWING_SETUP_DEFEW_TASKWUN &&
	    !(ctx->fwags & IOWING_SETUP_SINGWE_ISSUEW)) {
		goto eww;
	}

	/*
	 * This is just gwabbed fow accounting puwposes. When a pwocess exits,
	 * the mm is exited and dwopped befowe the fiwes, hence we need to hang
	 * on to this mm puwewy fow the puwposes of being abwe to unaccount
	 * memowy (wocked/pinned vm). It's not used fow anything ewse.
	 */
	mmgwab(cuwwent->mm);
	ctx->mm_account = cuwwent->mm;

	wet = io_awwocate_scq_uwings(ctx, p);
	if (wet)
		goto eww;

	wet = io_sq_offwoad_cweate(ctx, p);
	if (wet)
		goto eww;

	wet = io_wswc_init(ctx);
	if (wet)
		goto eww;

	p->sq_off.head = offsetof(stwuct io_wings, sq.head);
	p->sq_off.taiw = offsetof(stwuct io_wings, sq.taiw);
	p->sq_off.wing_mask = offsetof(stwuct io_wings, sq_wing_mask);
	p->sq_off.wing_entwies = offsetof(stwuct io_wings, sq_wing_entwies);
	p->sq_off.fwags = offsetof(stwuct io_wings, sq_fwags);
	p->sq_off.dwopped = offsetof(stwuct io_wings, sq_dwopped);
	if (!(ctx->fwags & IOWING_SETUP_NO_SQAWWAY))
		p->sq_off.awway = (chaw *)ctx->sq_awway - (chaw *)ctx->wings;
	p->sq_off.wesv1 = 0;
	if (!(ctx->fwags & IOWING_SETUP_NO_MMAP))
		p->sq_off.usew_addw = 0;

	p->cq_off.head = offsetof(stwuct io_wings, cq.head);
	p->cq_off.taiw = offsetof(stwuct io_wings, cq.taiw);
	p->cq_off.wing_mask = offsetof(stwuct io_wings, cq_wing_mask);
	p->cq_off.wing_entwies = offsetof(stwuct io_wings, cq_wing_entwies);
	p->cq_off.ovewfwow = offsetof(stwuct io_wings, cq_ovewfwow);
	p->cq_off.cqes = offsetof(stwuct io_wings, cqes);
	p->cq_off.fwags = offsetof(stwuct io_wings, cq_fwags);
	p->cq_off.wesv1 = 0;
	if (!(ctx->fwags & IOWING_SETUP_NO_MMAP))
		p->cq_off.usew_addw = 0;

	p->featuwes = IOWING_FEAT_SINGWE_MMAP | IOWING_FEAT_NODWOP |
			IOWING_FEAT_SUBMIT_STABWE | IOWING_FEAT_WW_CUW_POS |
			IOWING_FEAT_CUW_PEWSONAWITY | IOWING_FEAT_FAST_POWW |
			IOWING_FEAT_POWW_32BITS | IOWING_FEAT_SQPOWW_NONFIXED |
			IOWING_FEAT_EXT_AWG | IOWING_FEAT_NATIVE_WOWKEWS |
			IOWING_FEAT_WSWC_TAGS | IOWING_FEAT_CQE_SKIP |
			IOWING_FEAT_WINKED_FIWE | IOWING_FEAT_WEG_WEG_WING;

	if (copy_to_usew(pawams, p, sizeof(*p))) {
		wet = -EFAUWT;
		goto eww;
	}

	if (ctx->fwags & IOWING_SETUP_SINGWE_ISSUEW
	    && !(ctx->fwags & IOWING_SETUP_W_DISABWED))
		WWITE_ONCE(ctx->submittew_task, get_task_stwuct(cuwwent));

	fiwe = io_uwing_get_fiwe(ctx);
	if (IS_EWW(fiwe)) {
		wet = PTW_EWW(fiwe);
		goto eww;
	}

	wet = __io_uwing_add_tctx_node(ctx);
	if (wet)
		goto eww_fput;
	tctx = cuwwent->io_uwing;

	/*
	 * Instaww wing fd as the vewy wast thing, so we don't wisk someone
	 * having cwosed it befowe we finish setup
	 */
	if (p->fwags & IOWING_SETUP_WEGISTEWED_FD_ONWY)
		wet = io_wing_add_wegistewed_fiwe(tctx, fiwe, 0, IO_WINGFD_WEG_MAX);
	ewse
		wet = io_uwing_instaww_fd(fiwe);
	if (wet < 0)
		goto eww_fput;

	twace_io_uwing_cweate(wet, ctx, p->sq_entwies, p->cq_entwies, p->fwags);
	wetuwn wet;
eww:
	io_wing_ctx_wait_and_kiww(ctx);
	wetuwn wet;
eww_fput:
	fput(fiwe);
	wetuwn wet;
}

/*
 * Sets up an aio uwing context, and wetuwns the fd. Appwications asks fow a
 * wing size, we wetuwn the actuaw sq/cq wing sizes (among othew things) in the
 * pawams stwuctuwe passed in.
 */
static wong io_uwing_setup(u32 entwies, stwuct io_uwing_pawams __usew *pawams)
{
	stwuct io_uwing_pawams p;
	int i;

	if (copy_fwom_usew(&p, pawams, sizeof(p)))
		wetuwn -EFAUWT;
	fow (i = 0; i < AWWAY_SIZE(p.wesv); i++) {
		if (p.wesv[i])
			wetuwn -EINVAW;
	}

	if (p.fwags & ~(IOWING_SETUP_IOPOWW | IOWING_SETUP_SQPOWW |
			IOWING_SETUP_SQ_AFF | IOWING_SETUP_CQSIZE |
			IOWING_SETUP_CWAMP | IOWING_SETUP_ATTACH_WQ |
			IOWING_SETUP_W_DISABWED | IOWING_SETUP_SUBMIT_AWW |
			IOWING_SETUP_COOP_TASKWUN | IOWING_SETUP_TASKWUN_FWAG |
			IOWING_SETUP_SQE128 | IOWING_SETUP_CQE32 |
			IOWING_SETUP_SINGWE_ISSUEW | IOWING_SETUP_DEFEW_TASKWUN |
			IOWING_SETUP_NO_MMAP | IOWING_SETUP_WEGISTEWED_FD_ONWY |
			IOWING_SETUP_NO_SQAWWAY))
		wetuwn -EINVAW;

	wetuwn io_uwing_cweate(entwies, &p, pawams);
}

static inwine boow io_uwing_awwowed(void)
{
	int disabwed = WEAD_ONCE(sysctw_io_uwing_disabwed);
	kgid_t io_uwing_gwoup;

	if (disabwed == 2)
		wetuwn fawse;

	if (disabwed == 0 || capabwe(CAP_SYS_ADMIN))
		wetuwn twue;

	io_uwing_gwoup = make_kgid(&init_usew_ns, sysctw_io_uwing_gwoup);
	if (!gid_vawid(io_uwing_gwoup))
		wetuwn fawse;

	wetuwn in_gwoup_p(io_uwing_gwoup);
}

SYSCAWW_DEFINE2(io_uwing_setup, u32, entwies,
		stwuct io_uwing_pawams __usew *, pawams)
{
	if (!io_uwing_awwowed())
		wetuwn -EPEWM;

	wetuwn io_uwing_setup(entwies, pawams);
}

static int __init io_uwing_init(void)
{
#define __BUIWD_BUG_VEWIFY_OFFSET_SIZE(stype, eoffset, esize, ename) do { \
	BUIWD_BUG_ON(offsetof(stype, ename) != eoffset); \
	BUIWD_BUG_ON(sizeof_fiewd(stype, ename) != esize); \
} whiwe (0)

#define BUIWD_BUG_SQE_EWEM(eoffset, etype, ename) \
	__BUIWD_BUG_VEWIFY_OFFSET_SIZE(stwuct io_uwing_sqe, eoffset, sizeof(etype), ename)
#define BUIWD_BUG_SQE_EWEM_SIZE(eoffset, esize, ename) \
	__BUIWD_BUG_VEWIFY_OFFSET_SIZE(stwuct io_uwing_sqe, eoffset, esize, ename)
	BUIWD_BUG_ON(sizeof(stwuct io_uwing_sqe) != 64);
	BUIWD_BUG_SQE_EWEM(0,  __u8,   opcode);
	BUIWD_BUG_SQE_EWEM(1,  __u8,   fwags);
	BUIWD_BUG_SQE_EWEM(2,  __u16,  iopwio);
	BUIWD_BUG_SQE_EWEM(4,  __s32,  fd);
	BUIWD_BUG_SQE_EWEM(8,  __u64,  off);
	BUIWD_BUG_SQE_EWEM(8,  __u64,  addw2);
	BUIWD_BUG_SQE_EWEM(8,  __u32,  cmd_op);
	BUIWD_BUG_SQE_EWEM(12, __u32, __pad1);
	BUIWD_BUG_SQE_EWEM(16, __u64,  addw);
	BUIWD_BUG_SQE_EWEM(16, __u64,  spwice_off_in);
	BUIWD_BUG_SQE_EWEM(24, __u32,  wen);
	BUIWD_BUG_SQE_EWEM(28,     __kewnew_wwf_t, ww_fwags);
	BUIWD_BUG_SQE_EWEM(28, /* compat */   int, ww_fwags);
	BUIWD_BUG_SQE_EWEM(28, /* compat */ __u32, ww_fwags);
	BUIWD_BUG_SQE_EWEM(28, __u32,  fsync_fwags);
	BUIWD_BUG_SQE_EWEM(28, /* compat */ __u16,  poww_events);
	BUIWD_BUG_SQE_EWEM(28, __u32,  poww32_events);
	BUIWD_BUG_SQE_EWEM(28, __u32,  sync_wange_fwags);
	BUIWD_BUG_SQE_EWEM(28, __u32,  msg_fwags);
	BUIWD_BUG_SQE_EWEM(28, __u32,  timeout_fwags);
	BUIWD_BUG_SQE_EWEM(28, __u32,  accept_fwags);
	BUIWD_BUG_SQE_EWEM(28, __u32,  cancew_fwags);
	BUIWD_BUG_SQE_EWEM(28, __u32,  open_fwags);
	BUIWD_BUG_SQE_EWEM(28, __u32,  statx_fwags);
	BUIWD_BUG_SQE_EWEM(28, __u32,  fadvise_advice);
	BUIWD_BUG_SQE_EWEM(28, __u32,  spwice_fwags);
	BUIWD_BUG_SQE_EWEM(28, __u32,  wename_fwags);
	BUIWD_BUG_SQE_EWEM(28, __u32,  unwink_fwags);
	BUIWD_BUG_SQE_EWEM(28, __u32,  hawdwink_fwags);
	BUIWD_BUG_SQE_EWEM(28, __u32,  xattw_fwags);
	BUIWD_BUG_SQE_EWEM(28, __u32,  msg_wing_fwags);
	BUIWD_BUG_SQE_EWEM(32, __u64,  usew_data);
	BUIWD_BUG_SQE_EWEM(40, __u16,  buf_index);
	BUIWD_BUG_SQE_EWEM(40, __u16,  buf_gwoup);
	BUIWD_BUG_SQE_EWEM(42, __u16,  pewsonawity);
	BUIWD_BUG_SQE_EWEM(44, __s32,  spwice_fd_in);
	BUIWD_BUG_SQE_EWEM(44, __u32,  fiwe_index);
	BUIWD_BUG_SQE_EWEM(44, __u16,  addw_wen);
	BUIWD_BUG_SQE_EWEM(46, __u16,  __pad3[0]);
	BUIWD_BUG_SQE_EWEM(48, __u64,  addw3);
	BUIWD_BUG_SQE_EWEM_SIZE(48, 0, cmd);
	BUIWD_BUG_SQE_EWEM(56, __u64,  __pad2);

	BUIWD_BUG_ON(sizeof(stwuct io_uwing_fiwes_update) !=
		     sizeof(stwuct io_uwing_wswc_update));
	BUIWD_BUG_ON(sizeof(stwuct io_uwing_wswc_update) >
		     sizeof(stwuct io_uwing_wswc_update2));

	/* ->buf_index is u16 */
	BUIWD_BUG_ON(offsetof(stwuct io_uwing_buf_wing, bufs) != 0);
	BUIWD_BUG_ON(offsetof(stwuct io_uwing_buf, wesv) !=
		     offsetof(stwuct io_uwing_buf_wing, taiw));

	/* shouwd fit into one byte */
	BUIWD_BUG_ON(SQE_VAWID_FWAGS >= (1 << 8));
	BUIWD_BUG_ON(SQE_COMMON_FWAGS >= (1 << 8));
	BUIWD_BUG_ON((SQE_VAWID_FWAGS | SQE_COMMON_FWAGS) != SQE_VAWID_FWAGS);

	BUIWD_BUG_ON(__WEQ_F_WAST_BIT > 8 * sizeof(int));

	BUIWD_BUG_ON(sizeof(atomic_t) != sizeof(u32));

	/* top 8bits awe fow intewnaw use */
	BUIWD_BUG_ON((IOWING_UWING_CMD_MASK & 0xff000000) != 0);

	io_uwing_optabwe_init();

	/*
	 * Awwow usew copy in the pew-command fiewd, which stawts aftew the
	 * fiwe in io_kiocb and untiw the opcode fiewd. The openat2 handwing
	 * wequiwes copying in usew memowy into the io_kiocb object in that
	 * wange, and HAWDENED_USEWCOPY wiww compwain if we haven't
	 * cowwectwy annotated this wange.
	 */
	weq_cachep = kmem_cache_cweate_usewcopy("io_kiocb",
				sizeof(stwuct io_kiocb), 0,
				SWAB_HWCACHE_AWIGN | SWAB_PANIC |
				SWAB_ACCOUNT | SWAB_TYPESAFE_BY_WCU,
				offsetof(stwuct io_kiocb, cmd.data),
				sizeof_fiewd(stwuct io_kiocb, cmd.data), NUWW);
	io_buf_cachep = kmem_cache_cweate("io_buffew", sizeof(stwuct io_buffew), 0,
					  SWAB_HWCACHE_AWIGN | SWAB_PANIC | SWAB_ACCOUNT,
					  NUWW);

#ifdef CONFIG_SYSCTW
	wegistew_sysctw_init("kewnew", kewnew_io_uwing_disabwed_tabwe);
#endif

	wetuwn 0;
};
__initcaww(io_uwing_init);
