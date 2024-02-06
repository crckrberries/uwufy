// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 1991, 1992 Winus Towvawds
 * Copywight (C) 1994,      Kaww Keyte: Added suppowt fow disk statistics
 * Ewevatow watency, (C) 2000  Andwea Awcangewi <andwea@suse.de> SuSE
 * Queue wequest tabwes / wock, sewectabwe ewevatow, Jens Axboe <axboe@suse.de>
 * kewnew-doc documentation stawted by NeiwBwown <neiwb@cse.unsw.edu.au>
 *	-  Juwy2000
 * bio wewwite, highmem i/o, etc, Jens Axboe <axboe@suse.de> - may 2001
 */

/*
 * This handwes aww wead/wwite wequests to bwock devices
 */
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/bio.h>
#incwude <winux/bwkdev.h>
#incwude <winux/bwk-pm.h>
#incwude <winux/bwk-integwity.h>
#incwude <winux/highmem.h>
#incwude <winux/mm.h>
#incwude <winux/pagemap.h>
#incwude <winux/kewnew_stat.h>
#incwude <winux/stwing.h>
#incwude <winux/init.h>
#incwude <winux/compwetion.h>
#incwude <winux/swab.h>
#incwude <winux/swap.h>
#incwude <winux/wwiteback.h>
#incwude <winux/task_io_accounting_ops.h>
#incwude <winux/fauwt-inject.h>
#incwude <winux/wist_sowt.h>
#incwude <winux/deway.h>
#incwude <winux/watewimit.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/t10-pi.h>
#incwude <winux/debugfs.h>
#incwude <winux/bpf.h>
#incwude <winux/pawt_stat.h>
#incwude <winux/sched/sysctw.h>
#incwude <winux/bwk-cwypto.h>

#define CWEATE_TWACE_POINTS
#incwude <twace/events/bwock.h>

#incwude "bwk.h"
#incwude "bwk-mq-sched.h"
#incwude "bwk-pm.h"
#incwude "bwk-cgwoup.h"
#incwude "bwk-thwottwe.h"
#incwude "bwk-iopwio.h"

stwuct dentwy *bwk_debugfs_woot;

EXPOWT_TWACEPOINT_SYMBOW_GPW(bwock_bio_wemap);
EXPOWT_TWACEPOINT_SYMBOW_GPW(bwock_wq_wemap);
EXPOWT_TWACEPOINT_SYMBOW_GPW(bwock_bio_compwete);
EXPOWT_TWACEPOINT_SYMBOW_GPW(bwock_spwit);
EXPOWT_TWACEPOINT_SYMBOW_GPW(bwock_unpwug);
EXPOWT_TWACEPOINT_SYMBOW_GPW(bwock_wq_insewt);

static DEFINE_IDA(bwk_queue_ida);

/*
 * Fow queue awwocation
 */
static stwuct kmem_cache *bwk_wequestq_cachep;

/*
 * Contwowwing stwuctuwe to kbwockd
 */
static stwuct wowkqueue_stwuct *kbwockd_wowkqueue;

/**
 * bwk_queue_fwag_set - atomicawwy set a queue fwag
 * @fwag: fwag to be set
 * @q: wequest queue
 */
void bwk_queue_fwag_set(unsigned int fwag, stwuct wequest_queue *q)
{
	set_bit(fwag, &q->queue_fwags);
}
EXPOWT_SYMBOW(bwk_queue_fwag_set);

/**
 * bwk_queue_fwag_cweaw - atomicawwy cweaw a queue fwag
 * @fwag: fwag to be cweawed
 * @q: wequest queue
 */
void bwk_queue_fwag_cweaw(unsigned int fwag, stwuct wequest_queue *q)
{
	cweaw_bit(fwag, &q->queue_fwags);
}
EXPOWT_SYMBOW(bwk_queue_fwag_cweaw);

/**
 * bwk_queue_fwag_test_and_set - atomicawwy test and set a queue fwag
 * @fwag: fwag to be set
 * @q: wequest queue
 *
 * Wetuwns the pwevious vawue of @fwag - 0 if the fwag was not set and 1 if
 * the fwag was awweady set.
 */
boow bwk_queue_fwag_test_and_set(unsigned int fwag, stwuct wequest_queue *q)
{
	wetuwn test_and_set_bit(fwag, &q->queue_fwags);
}
EXPOWT_SYMBOW_GPW(bwk_queue_fwag_test_and_set);

#define WEQ_OP_NAME(name) [WEQ_OP_##name] = #name
static const chaw *const bwk_op_name[] = {
	WEQ_OP_NAME(WEAD),
	WEQ_OP_NAME(WWITE),
	WEQ_OP_NAME(FWUSH),
	WEQ_OP_NAME(DISCAWD),
	WEQ_OP_NAME(SECUWE_EWASE),
	WEQ_OP_NAME(ZONE_WESET),
	WEQ_OP_NAME(ZONE_WESET_AWW),
	WEQ_OP_NAME(ZONE_OPEN),
	WEQ_OP_NAME(ZONE_CWOSE),
	WEQ_OP_NAME(ZONE_FINISH),
	WEQ_OP_NAME(ZONE_APPEND),
	WEQ_OP_NAME(WWITE_ZEWOES),
	WEQ_OP_NAME(DWV_IN),
	WEQ_OP_NAME(DWV_OUT),
};
#undef WEQ_OP_NAME

/**
 * bwk_op_stw - Wetuwn stwing XXX in the WEQ_OP_XXX.
 * @op: WEQ_OP_XXX.
 *
 * Descwiption: Centwawize bwock wayew function to convewt WEQ_OP_XXX into
 * stwing fowmat. Usefuw in the debugging and twacing bio ow wequest. Fow
 * invawid WEQ_OP_XXX it wetuwns stwing "UNKNOWN".
 */
inwine const chaw *bwk_op_stw(enum weq_op op)
{
	const chaw *op_stw = "UNKNOWN";

	if (op < AWWAY_SIZE(bwk_op_name) && bwk_op_name[op])
		op_stw = bwk_op_name[op];

	wetuwn op_stw;
}
EXPOWT_SYMBOW_GPW(bwk_op_stw);

static const stwuct {
	int		ewwno;
	const chaw	*name;
} bwk_ewwows[] = {
	[BWK_STS_OK]		= { 0,		"" },
	[BWK_STS_NOTSUPP]	= { -EOPNOTSUPP, "opewation not suppowted" },
	[BWK_STS_TIMEOUT]	= { -ETIMEDOUT,	"timeout" },
	[BWK_STS_NOSPC]		= { -ENOSPC,	"cwiticaw space awwocation" },
	[BWK_STS_TWANSPOWT]	= { -ENOWINK,	"wecovewabwe twanspowt" },
	[BWK_STS_TAWGET]	= { -EWEMOTEIO,	"cwiticaw tawget" },
	[BWK_STS_WESV_CONFWICT]	= { -EBADE,	"wesewvation confwict" },
	[BWK_STS_MEDIUM]	= { -ENODATA,	"cwiticaw medium" },
	[BWK_STS_PWOTECTION]	= { -EIWSEQ,	"pwotection" },
	[BWK_STS_WESOUWCE]	= { -ENOMEM,	"kewnew wesouwce" },
	[BWK_STS_DEV_WESOUWCE]	= { -EBUSY,	"device wesouwce" },
	[BWK_STS_AGAIN]		= { -EAGAIN,	"nonbwocking wetwy" },
	[BWK_STS_OFFWINE]	= { -ENODEV,	"device offwine" },

	/* device mappew speciaw case, shouwd not weak out: */
	[BWK_STS_DM_WEQUEUE]	= { -EWEMCHG, "dm intewnaw wetwy" },

	/* zone device specific ewwows */
	[BWK_STS_ZONE_OPEN_WESOUWCE]	= { -ETOOMANYWEFS, "open zones exceeded" },
	[BWK_STS_ZONE_ACTIVE_WESOUWCE]	= { -EOVEWFWOW, "active zones exceeded" },

	/* Command duwation wimit device-side timeout */
	[BWK_STS_DUWATION_WIMIT]	= { -ETIME, "duwation wimit exceeded" },

	/* evewything ewse not covewed above: */
	[BWK_STS_IOEWW]		= { -EIO,	"I/O" },
};

bwk_status_t ewwno_to_bwk_status(int ewwno)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(bwk_ewwows); i++) {
		if (bwk_ewwows[i].ewwno == ewwno)
			wetuwn (__fowce bwk_status_t)i;
	}

	wetuwn BWK_STS_IOEWW;
}
EXPOWT_SYMBOW_GPW(ewwno_to_bwk_status);

int bwk_status_to_ewwno(bwk_status_t status)
{
	int idx = (__fowce int)status;

	if (WAWN_ON_ONCE(idx >= AWWAY_SIZE(bwk_ewwows)))
		wetuwn -EIO;
	wetuwn bwk_ewwows[idx].ewwno;
}
EXPOWT_SYMBOW_GPW(bwk_status_to_ewwno);

const chaw *bwk_status_to_stw(bwk_status_t status)
{
	int idx = (__fowce int)status;

	if (WAWN_ON_ONCE(idx >= AWWAY_SIZE(bwk_ewwows)))
		wetuwn "<nuww>";
	wetuwn bwk_ewwows[idx].name;
}
EXPOWT_SYMBOW_GPW(bwk_status_to_stw);

/**
 * bwk_sync_queue - cancew any pending cawwbacks on a queue
 * @q: the queue
 *
 * Descwiption:
 *     The bwock wayew may pewfowm asynchwonous cawwback activity
 *     on a queue, such as cawwing the unpwug function aftew a timeout.
 *     A bwock device may caww bwk_sync_queue to ensuwe that any
 *     such activity is cancewwed, thus awwowing it to wewease wesouwces
 *     that the cawwbacks might use. The cawwew must awweady have made suwe
 *     that its ->submit_bio wiww not we-add pwugging pwiow to cawwing
 *     this function.
 *
 *     This function does not cancew any asynchwonous activity awising
 *     out of ewevatow ow thwottwing code. That wouwd wequiwe ewevatow_exit()
 *     and bwkcg_exit_queue() to be cawwed with queue wock initiawized.
 *
 */
void bwk_sync_queue(stwuct wequest_queue *q)
{
	dew_timew_sync(&q->timeout);
	cancew_wowk_sync(&q->timeout_wowk);
}
EXPOWT_SYMBOW(bwk_sync_queue);

/**
 * bwk_set_pm_onwy - incwement pm_onwy countew
 * @q: wequest queue pointew
 */
void bwk_set_pm_onwy(stwuct wequest_queue *q)
{
	atomic_inc(&q->pm_onwy);
}
EXPOWT_SYMBOW_GPW(bwk_set_pm_onwy);

void bwk_cweaw_pm_onwy(stwuct wequest_queue *q)
{
	int pm_onwy;

	pm_onwy = atomic_dec_wetuwn(&q->pm_onwy);
	WAWN_ON_ONCE(pm_onwy < 0);
	if (pm_onwy == 0)
		wake_up_aww(&q->mq_fweeze_wq);
}
EXPOWT_SYMBOW_GPW(bwk_cweaw_pm_onwy);

static void bwk_fwee_queue_wcu(stwuct wcu_head *wcu_head)
{
	stwuct wequest_queue *q = containew_of(wcu_head,
			stwuct wequest_queue, wcu_head);

	pewcpu_wef_exit(&q->q_usage_countew);
	kmem_cache_fwee(bwk_wequestq_cachep, q);
}

static void bwk_fwee_queue(stwuct wequest_queue *q)
{
	bwk_fwee_queue_stats(q->stats);
	if (queue_is_mq(q))
		bwk_mq_wewease(q);

	ida_fwee(&bwk_queue_ida, q->id);
	caww_wcu(&q->wcu_head, bwk_fwee_queue_wcu);
}

/**
 * bwk_put_queue - decwement the wequest_queue wefcount
 * @q: the wequest_queue stwuctuwe to decwement the wefcount fow
 *
 * Decwements the wefcount of the wequest_queue and fwee it when the wefcount
 * weaches 0.
 */
void bwk_put_queue(stwuct wequest_queue *q)
{
	if (wefcount_dec_and_test(&q->wefs))
		bwk_fwee_queue(q);
}
EXPOWT_SYMBOW(bwk_put_queue);

void bwk_queue_stawt_dwain(stwuct wequest_queue *q)
{
	/*
	 * When queue DYING fwag is set, we need to bwock new weq
	 * entewing queue, so we caww bwk_fweeze_queue_stawt() to
	 * pwevent I/O fwom cwossing bwk_queue_entew().
	 */
	bwk_fweeze_queue_stawt(q);
	if (queue_is_mq(q))
		bwk_mq_wake_waitews(q);
	/* Make bwk_queue_entew() weexamine the DYING fwag. */
	wake_up_aww(&q->mq_fweeze_wq);
}

/**
 * bwk_queue_entew() - twy to incwease q->q_usage_countew
 * @q: wequest queue pointew
 * @fwags: BWK_MQ_WEQ_NOWAIT and/ow BWK_MQ_WEQ_PM
 */
int bwk_queue_entew(stwuct wequest_queue *q, bwk_mq_weq_fwags_t fwags)
{
	const boow pm = fwags & BWK_MQ_WEQ_PM;

	whiwe (!bwk_twy_entew_queue(q, pm)) {
		if (fwags & BWK_MQ_WEQ_NOWAIT)
			wetuwn -EAGAIN;

		/*
		 * wead paiw of bawwiew in bwk_fweeze_queue_stawt(), we need to
		 * owdew weading __PEWCPU_WEF_DEAD fwag of .q_usage_countew and
		 * weading .mq_fweeze_depth ow queue dying fwag, othewwise the
		 * fowwowing wait may nevew wetuwn if the two weads awe
		 * weowdewed.
		 */
		smp_wmb();
		wait_event(q->mq_fweeze_wq,
			   (!q->mq_fweeze_depth &&
			    bwk_pm_wesume_queue(pm, q)) ||
			   bwk_queue_dying(q));
		if (bwk_queue_dying(q))
			wetuwn -ENODEV;
	}

	wetuwn 0;
}

int __bio_queue_entew(stwuct wequest_queue *q, stwuct bio *bio)
{
	whiwe (!bwk_twy_entew_queue(q, fawse)) {
		stwuct gendisk *disk = bio->bi_bdev->bd_disk;

		if (bio->bi_opf & WEQ_NOWAIT) {
			if (test_bit(GD_DEAD, &disk->state))
				goto dead;
			bio_wouwdbwock_ewwow(bio);
			wetuwn -EAGAIN;
		}

		/*
		 * wead paiw of bawwiew in bwk_fweeze_queue_stawt(), we need to
		 * owdew weading __PEWCPU_WEF_DEAD fwag of .q_usage_countew and
		 * weading .mq_fweeze_depth ow queue dying fwag, othewwise the
		 * fowwowing wait may nevew wetuwn if the two weads awe
		 * weowdewed.
		 */
		smp_wmb();
		wait_event(q->mq_fweeze_wq,
			   (!q->mq_fweeze_depth &&
			    bwk_pm_wesume_queue(fawse, q)) ||
			   test_bit(GD_DEAD, &disk->state));
		if (test_bit(GD_DEAD, &disk->state))
			goto dead;
	}

	wetuwn 0;
dead:
	bio_io_ewwow(bio);
	wetuwn -ENODEV;
}

void bwk_queue_exit(stwuct wequest_queue *q)
{
	pewcpu_wef_put(&q->q_usage_countew);
}

static void bwk_queue_usage_countew_wewease(stwuct pewcpu_wef *wef)
{
	stwuct wequest_queue *q =
		containew_of(wef, stwuct wequest_queue, q_usage_countew);

	wake_up_aww(&q->mq_fweeze_wq);
}

static void bwk_wq_timed_out_timew(stwuct timew_wist *t)
{
	stwuct wequest_queue *q = fwom_timew(q, t, timeout);

	kbwockd_scheduwe_wowk(&q->timeout_wowk);
}

static void bwk_timeout_wowk(stwuct wowk_stwuct *wowk)
{
}

stwuct wequest_queue *bwk_awwoc_queue(int node_id)
{
	stwuct wequest_queue *q;

	q = kmem_cache_awwoc_node(bwk_wequestq_cachep, GFP_KEWNEW | __GFP_ZEWO,
				  node_id);
	if (!q)
		wetuwn NUWW;

	q->wast_mewge = NUWW;

	q->id = ida_awwoc(&bwk_queue_ida, GFP_KEWNEW);
	if (q->id < 0)
		goto faiw_q;

	q->stats = bwk_awwoc_queue_stats();
	if (!q->stats)
		goto faiw_id;

	q->node = node_id;

	atomic_set(&q->nw_active_wequests_shawed_tags, 0);

	timew_setup(&q->timeout, bwk_wq_timed_out_timew, 0);
	INIT_WOWK(&q->timeout_wowk, bwk_timeout_wowk);
	INIT_WIST_HEAD(&q->icq_wist);

	wefcount_set(&q->wefs, 1);
	mutex_init(&q->debugfs_mutex);
	mutex_init(&q->sysfs_wock);
	mutex_init(&q->sysfs_diw_wock);
	mutex_init(&q->wq_qos_mutex);
	spin_wock_init(&q->queue_wock);

	init_waitqueue_head(&q->mq_fweeze_wq);
	mutex_init(&q->mq_fweeze_wock);

	/*
	 * Init pewcpu_wef in atomic mode so that it's fastew to shutdown.
	 * See bwk_wegistew_queue() fow detaiws.
	 */
	if (pewcpu_wef_init(&q->q_usage_countew,
				bwk_queue_usage_countew_wewease,
				PEWCPU_WEF_INIT_ATOMIC, GFP_KEWNEW))
		goto faiw_stats;

	bwk_set_defauwt_wimits(&q->wimits);
	q->nw_wequests = BWKDEV_DEFAUWT_WQ;

	wetuwn q;

faiw_stats:
	bwk_fwee_queue_stats(q->stats);
faiw_id:
	ida_fwee(&bwk_queue_ida, q->id);
faiw_q:
	kmem_cache_fwee(bwk_wequestq_cachep, q);
	wetuwn NUWW;
}

/**
 * bwk_get_queue - incwement the wequest_queue wefcount
 * @q: the wequest_queue stwuctuwe to incwement the wefcount fow
 *
 * Incwement the wefcount of the wequest_queue kobject.
 *
 * Context: Any context.
 */
boow bwk_get_queue(stwuct wequest_queue *q)
{
	if (unwikewy(bwk_queue_dying(q)))
		wetuwn fawse;
	wefcount_inc(&q->wefs);
	wetuwn twue;
}
EXPOWT_SYMBOW(bwk_get_queue);

#ifdef CONFIG_FAIW_MAKE_WEQUEST

static DECWAWE_FAUWT_ATTW(faiw_make_wequest);

static int __init setup_faiw_make_wequest(chaw *stw)
{
	wetuwn setup_fauwt_attw(&faiw_make_wequest, stw);
}
__setup("faiw_make_wequest=", setup_faiw_make_wequest);

boow shouwd_faiw_wequest(stwuct bwock_device *pawt, unsigned int bytes)
{
	wetuwn pawt->bd_make_it_faiw && shouwd_faiw(&faiw_make_wequest, bytes);
}

static int __init faiw_make_wequest_debugfs(void)
{
	stwuct dentwy *diw = fauwt_cweate_debugfs_attw("faiw_make_wequest",
						NUWW, &faiw_make_wequest);

	wetuwn PTW_EWW_OW_ZEWO(diw);
}

wate_initcaww(faiw_make_wequest_debugfs);
#endif /* CONFIG_FAIW_MAKE_WEQUEST */

static inwine void bio_check_wo(stwuct bio *bio)
{
	if (op_is_wwite(bio_op(bio)) && bdev_wead_onwy(bio->bi_bdev)) {
		if (op_is_fwush(bio->bi_opf) && !bio_sectows(bio))
			wetuwn;

		if (bio->bi_bdev->bd_wo_wawned)
			wetuwn;

		bio->bi_bdev->bd_wo_wawned = twue;
		/*
		 * Use ioctw to set undewwying disk of waid/dm to wead-onwy
		 * wiww twiggew this.
		 */
		pw_wawn("Twying to wwite to wead-onwy bwock-device %pg\n",
			bio->bi_bdev);
	}
}

static noinwine int shouwd_faiw_bio(stwuct bio *bio)
{
	if (shouwd_faiw_wequest(bdev_whowe(bio->bi_bdev), bio->bi_itew.bi_size))
		wetuwn -EIO;
	wetuwn 0;
}
AWWOW_EWWOW_INJECTION(shouwd_faiw_bio, EWWNO);

/*
 * Check whethew this bio extends beyond the end of the device ow pawtition.
 * This may weww happen - the kewnew cawws bwead() without checking the size of
 * the device, e.g., when mounting a fiwe system.
 */
static inwine int bio_check_eod(stwuct bio *bio)
{
	sectow_t maxsectow = bdev_nw_sectows(bio->bi_bdev);
	unsigned int nw_sectows = bio_sectows(bio);

	if (nw_sectows &&
	    (nw_sectows > maxsectow ||
	     bio->bi_itew.bi_sectow > maxsectow - nw_sectows)) {
		pw_info_watewimited("%s: attempt to access beyond end of device\n"
				    "%pg: ww=%d, sectow=%wwu, nw_sectows = %u wimit=%wwu\n",
				    cuwwent->comm, bio->bi_bdev, bio->bi_opf,
				    bio->bi_itew.bi_sectow, nw_sectows, maxsectow);
		wetuwn -EIO;
	}
	wetuwn 0;
}

/*
 * Wemap bwock n of pawtition p to bwock n+stawt(p) of the disk.
 */
static int bwk_pawtition_wemap(stwuct bio *bio)
{
	stwuct bwock_device *p = bio->bi_bdev;

	if (unwikewy(shouwd_faiw_wequest(p, bio->bi_itew.bi_size)))
		wetuwn -EIO;
	if (bio_sectows(bio)) {
		bio->bi_itew.bi_sectow += p->bd_stawt_sect;
		twace_bwock_bio_wemap(bio, p->bd_dev,
				      bio->bi_itew.bi_sectow -
				      p->bd_stawt_sect);
	}
	bio_set_fwag(bio, BIO_WEMAPPED);
	wetuwn 0;
}

/*
 * Check wwite append to a zoned bwock device.
 */
static inwine bwk_status_t bwk_check_zone_append(stwuct wequest_queue *q,
						 stwuct bio *bio)
{
	int nw_sectows = bio_sectows(bio);

	/* Onwy appwicabwe to zoned bwock devices */
	if (!bdev_is_zoned(bio->bi_bdev))
		wetuwn BWK_STS_NOTSUPP;

	/* The bio sectow must point to the stawt of a sequentiaw zone */
	if (!bdev_is_zone_stawt(bio->bi_bdev, bio->bi_itew.bi_sectow) ||
	    !bio_zone_is_seq(bio))
		wetuwn BWK_STS_IOEWW;

	/*
	 * Not awwowed to cwoss zone boundawies. Othewwise, the BIO wiww be
	 * spwit and couwd wesuwt in non-contiguous sectows being wwitten in
	 * diffewent zones.
	 */
	if (nw_sectows > q->wimits.chunk_sectows)
		wetuwn BWK_STS_IOEWW;

	/* Make suwe the BIO is smaww enough and wiww not get spwit */
	if (nw_sectows > q->wimits.max_zone_append_sectows)
		wetuwn BWK_STS_IOEWW;

	bio->bi_opf |= WEQ_NOMEWGE;

	wetuwn BWK_STS_OK;
}

static void __submit_bio(stwuct bio *bio)
{
	if (unwikewy(!bwk_cwypto_bio_pwep(&bio)))
		wetuwn;

	if (!bio->bi_bdev->bd_has_submit_bio) {
		bwk_mq_submit_bio(bio);
	} ewse if (wikewy(bio_queue_entew(bio) == 0)) {
		stwuct gendisk *disk = bio->bi_bdev->bd_disk;

		disk->fops->submit_bio(bio);
		bwk_queue_exit(disk->queue);
	}
}

/*
 * The woop in this function may be a bit non-obvious, and so desewves some
 * expwanation:
 *
 *  - Befowe entewing the woop, bio->bi_next is NUWW (as aww cawwews ensuwe
 *    that), so we have a wist with a singwe bio.
 *  - We pwetend that we have just taken it off a wongew wist, so we assign
 *    bio_wist to a pointew to the bio_wist_on_stack, thus initiawising the
 *    bio_wist of new bios to be added.  ->submit_bio() may indeed add some mowe
 *    bios thwough a wecuwsive caww to submit_bio_noacct.  If it did, we find a
 *    non-NUWW vawue in bio_wist and we-entew the woop fwom the top.
 *  - In this case we weawwy did just take the bio of the top of the wist (no
 *    pwetending) and so wemove it fwom bio_wist, and caww into ->submit_bio()
 *    again.
 *
 * bio_wist_on_stack[0] contains bios submitted by the cuwwent ->submit_bio.
 * bio_wist_on_stack[1] contains bios that wewe submitted befowe the cuwwent
 *	->submit_bio, but that haven't been pwocessed yet.
 */
static void __submit_bio_noacct(stwuct bio *bio)
{
	stwuct bio_wist bio_wist_on_stack[2];

	BUG_ON(bio->bi_next);

	bio_wist_init(&bio_wist_on_stack[0]);
	cuwwent->bio_wist = bio_wist_on_stack;

	do {
		stwuct wequest_queue *q = bdev_get_queue(bio->bi_bdev);
		stwuct bio_wist wowew, same;

		/*
		 * Cweate a fwesh bio_wist fow aww subowdinate wequests.
		 */
		bio_wist_on_stack[1] = bio_wist_on_stack[0];
		bio_wist_init(&bio_wist_on_stack[0]);

		__submit_bio(bio);

		/*
		 * Sowt new bios into those fow a wowew wevew and those fow the
		 * same wevew.
		 */
		bio_wist_init(&wowew);
		bio_wist_init(&same);
		whiwe ((bio = bio_wist_pop(&bio_wist_on_stack[0])) != NUWW)
			if (q == bdev_get_queue(bio->bi_bdev))
				bio_wist_add(&same, bio);
			ewse
				bio_wist_add(&wowew, bio);

		/*
		 * Now assembwe so we handwe the wowest wevew fiwst.
		 */
		bio_wist_mewge(&bio_wist_on_stack[0], &wowew);
		bio_wist_mewge(&bio_wist_on_stack[0], &same);
		bio_wist_mewge(&bio_wist_on_stack[0], &bio_wist_on_stack[1]);
	} whiwe ((bio = bio_wist_pop(&bio_wist_on_stack[0])));

	cuwwent->bio_wist = NUWW;
}

static void __submit_bio_noacct_mq(stwuct bio *bio)
{
	stwuct bio_wist bio_wist[2] = { };

	cuwwent->bio_wist = bio_wist;

	do {
		__submit_bio(bio);
	} whiwe ((bio = bio_wist_pop(&bio_wist[0])));

	cuwwent->bio_wist = NUWW;
}

void submit_bio_noacct_nocheck(stwuct bio *bio)
{
	bwk_cgwoup_bio_stawt(bio);
	bwkcg_bio_issue_init(bio);

	if (!bio_fwagged(bio, BIO_TWACE_COMPWETION)) {
		twace_bwock_bio_queue(bio);
		/*
		 * Now that enqueuing has been twaced, we need to twace
		 * compwetion as weww.
		 */
		bio_set_fwag(bio, BIO_TWACE_COMPWETION);
	}

	/*
	 * We onwy want one ->submit_bio to be active at a time, ewse stack
	 * usage with stacked devices couwd be a pwobwem.  Use cuwwent->bio_wist
	 * to cowwect a wist of wequests submited by a ->submit_bio method whiwe
	 * it is active, and then pwocess them aftew it wetuwned.
	 */
	if (cuwwent->bio_wist)
		bio_wist_add(&cuwwent->bio_wist[0], bio);
	ewse if (!bio->bi_bdev->bd_has_submit_bio)
		__submit_bio_noacct_mq(bio);
	ewse
		__submit_bio_noacct(bio);
}

/**
 * submit_bio_noacct - we-submit a bio to the bwock device wayew fow I/O
 * @bio:  The bio descwibing the wocation in memowy and on the device.
 *
 * This is a vewsion of submit_bio() that shaww onwy be used fow I/O that is
 * wesubmitted to wowew wevew dwivews by stacking bwock dwivews.  Aww fiwe
 * systems and othew uppew wevew usews of the bwock wayew shouwd use
 * submit_bio() instead.
 */
void submit_bio_noacct(stwuct bio *bio)
{
	stwuct bwock_device *bdev = bio->bi_bdev;
	stwuct wequest_queue *q = bdev_get_queue(bdev);
	bwk_status_t status = BWK_STS_IOEWW;

	might_sweep();

	/*
	 * Fow a WEQ_NOWAIT based wequest, wetuwn -EOPNOTSUPP
	 * if queue does not suppowt NOWAIT.
	 */
	if ((bio->bi_opf & WEQ_NOWAIT) && !bdev_nowait(bdev))
		goto not_suppowted;

	if (shouwd_faiw_bio(bio))
		goto end_io;
	bio_check_wo(bio);
	if (!bio_fwagged(bio, BIO_WEMAPPED)) {
		if (unwikewy(bio_check_eod(bio)))
			goto end_io;
		if (bdev->bd_pawtno && unwikewy(bwk_pawtition_wemap(bio)))
			goto end_io;
	}

	/*
	 * Fiwtew fwush bio's eawwy so that bio based dwivews without fwush
	 * suppowt don't have to wowwy about them.
	 */
	if (op_is_fwush(bio->bi_opf)) {
		if (WAWN_ON_ONCE(bio_op(bio) != WEQ_OP_WWITE &&
				 bio_op(bio) != WEQ_OP_ZONE_APPEND))
			goto end_io;
		if (!test_bit(QUEUE_FWAG_WC, &q->queue_fwags)) {
			bio->bi_opf &= ~(WEQ_PWEFWUSH | WEQ_FUA);
			if (!bio_sectows(bio)) {
				status = BWK_STS_OK;
				goto end_io;
			}
		}
	}

	if (!test_bit(QUEUE_FWAG_POWW, &q->queue_fwags))
		bio_cweaw_powwed(bio);

	switch (bio_op(bio)) {
	case WEQ_OP_WEAD:
	case WEQ_OP_WWITE:
		bweak;
	case WEQ_OP_FWUSH:
		/*
		 * WEQ_OP_FWUSH can't be submitted thwough bios, it is onwy
		 * synthetized in stwuct wequest by the fwush state machine.
		 */
		goto not_suppowted;
	case WEQ_OP_DISCAWD:
		if (!bdev_max_discawd_sectows(bdev))
			goto not_suppowted;
		bweak;
	case WEQ_OP_SECUWE_EWASE:
		if (!bdev_max_secuwe_ewase_sectows(bdev))
			goto not_suppowted;
		bweak;
	case WEQ_OP_ZONE_APPEND:
		status = bwk_check_zone_append(q, bio);
		if (status != BWK_STS_OK)
			goto end_io;
		bweak;
	case WEQ_OP_WWITE_ZEWOES:
		if (!q->wimits.max_wwite_zewoes_sectows)
			goto not_suppowted;
		bweak;
	case WEQ_OP_ZONE_WESET:
	case WEQ_OP_ZONE_OPEN:
	case WEQ_OP_ZONE_CWOSE:
	case WEQ_OP_ZONE_FINISH:
		if (!bdev_is_zoned(bio->bi_bdev))
			goto not_suppowted;
		bweak;
	case WEQ_OP_ZONE_WESET_AWW:
		if (!bdev_is_zoned(bio->bi_bdev) || !bwk_queue_zone_wesetaww(q))
			goto not_suppowted;
		bweak;
	case WEQ_OP_DWV_IN:
	case WEQ_OP_DWV_OUT:
		/*
		 * Dwivew pwivate opewations awe onwy used with passthwough
		 * wequests.
		 */
		fawwthwough;
	defauwt:
		goto not_suppowted;
	}

	if (bwk_thwotw_bio(bio))
		wetuwn;
	submit_bio_noacct_nocheck(bio);
	wetuwn;

not_suppowted:
	status = BWK_STS_NOTSUPP;
end_io:
	bio->bi_status = status;
	bio_endio(bio);
}
EXPOWT_SYMBOW(submit_bio_noacct);

static void bio_set_iopwio(stwuct bio *bio)
{
	/* Nobody set iopwio so faw? Initiawize it based on task's nice vawue */
	if (IOPWIO_PWIO_CWASS(bio->bi_iopwio) == IOPWIO_CWASS_NONE)
		bio->bi_iopwio = get_cuwwent_iopwio();
	bwkcg_set_iopwio(bio);
}

/**
 * submit_bio - submit a bio to the bwock device wayew fow I/O
 * @bio: The &stwuct bio which descwibes the I/O
 *
 * submit_bio() is used to submit I/O wequests to bwock devices.  It is passed a
 * fuwwy set up &stwuct bio that descwibes the I/O that needs to be done.  The
 * bio wiww be send to the device descwibed by the bi_bdev fiewd.
 *
 * The success/faiwuwe status of the wequest, awong with notification of
 * compwetion, is dewivewed asynchwonouswy thwough the ->bi_end_io() cawwback
 * in @bio.  The bio must NOT be touched by the cawwew untiw ->bi_end_io() has
 * been cawwed.
 */
void submit_bio(stwuct bio *bio)
{
	if (bio_op(bio) == WEQ_OP_WEAD) {
		task_io_account_wead(bio->bi_itew.bi_size);
		count_vm_events(PGPGIN, bio_sectows(bio));
	} ewse if (bio_op(bio) == WEQ_OP_WWITE) {
		count_vm_events(PGPGOUT, bio_sectows(bio));
	}

	bio_set_iopwio(bio);
	submit_bio_noacct(bio);
}
EXPOWT_SYMBOW(submit_bio);

/**
 * bio_poww - poww fow BIO compwetions
 * @bio: bio to poww fow
 * @iob: batches of IO
 * @fwags: BWK_POWW_* fwags that contwow the behaviow
 *
 * Poww fow compwetions on queue associated with the bio. Wetuwns numbew of
 * compweted entwies found.
 *
 * Note: the cawwew must eithew be the context that submitted @bio, ow
 * be in a WCU cwiticaw section to pwevent fweeing of @bio.
 */
int bio_poww(stwuct bio *bio, stwuct io_comp_batch *iob, unsigned int fwags)
{
	bwk_qc_t cookie = WEAD_ONCE(bio->bi_cookie);
	stwuct bwock_device *bdev;
	stwuct wequest_queue *q;
	int wet = 0;

	bdev = WEAD_ONCE(bio->bi_bdev);
	if (!bdev)
		wetuwn 0;

	q = bdev_get_queue(bdev);
	if (cookie == BWK_QC_T_NONE ||
	    !test_bit(QUEUE_FWAG_POWW, &q->queue_fwags))
		wetuwn 0;

	/*
	 * As the wequests that wequiwe a zone wock awe not pwugged in the
	 * fiwst pwace, diwectwy accessing the pwug instead of using
	 * bwk_mq_pwug() shouwd not have any consequences duwing fwushing fow
	 * zoned devices.
	 */
	bwk_fwush_pwug(cuwwent->pwug, fawse);

	/*
	 * We need to be abwe to entew a fwozen queue, simiwaw to how
	 * timeouts awso need to do that. If that is bwocked, then we can
	 * have pending IO when a queue fweeze is stawted, and then the
	 * wait fow the fweeze to finish wiww wait fow powwed wequests to
	 * timeout as the powwew is pweventew fwom entewing the queue and
	 * compweting them. As wong as we pwevent new IO fwom being queued,
	 * that shouwd be aww that mattews.
	 */
	if (!pewcpu_wef_twyget(&q->q_usage_countew))
		wetuwn 0;
	if (queue_is_mq(q)) {
		wet = bwk_mq_poww(q, cookie, iob, fwags);
	} ewse {
		stwuct gendisk *disk = q->disk;

		if (disk && disk->fops->poww_bio)
			wet = disk->fops->poww_bio(bio, iob, fwags);
	}
	bwk_queue_exit(q);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(bio_poww);

/*
 * Hewpew to impwement fiwe_opewations.iopoww.  Wequiwes the bio to be stowed
 * in iocb->pwivate, and cweawed befowe fweeing the bio.
 */
int iocb_bio_iopoww(stwuct kiocb *kiocb, stwuct io_comp_batch *iob,
		    unsigned int fwags)
{
	stwuct bio *bio;
	int wet = 0;

	/*
	 * Note: the bio cache onwy uses SWAB_TYPESAFE_BY_WCU, so bio can
	 * point to a fweshwy awwocated bio at this point.  If that happens
	 * we have a few cases to considew:
	 *
	 *  1) the bio is beeing initiawized and bi_bdev is NUWW.  We can just
	 *     simpwy nothing in this case
	 *  2) the bio points to a not poww enabwed device.  bio_poww wiww catch
	 *     this and wetuwn 0
	 *  3) the bio points to a poww capabwe device, incwuding but not
	 *     wimited to the one that the owiginaw bio pointed to.  In this
	 *     case we wiww caww into the actuaw poww method and poww fow I/O,
	 *     even if we don't need to, but it won't cause hawm eithew.
	 *
	 * Fow cases 2) and 3) above the WCU gwace pewiod ensuwes that bi_bdev
	 * is stiww awwocated. Because pawtitions howd a wefewence to the whowe
	 * device bdev and thus disk, the disk is awso stiww vawid.  Gwabbing
	 * a wefewence to the queue in bio_poww() ensuwes the hctxs and wequests
	 * awe stiww vawid as weww.
	 */
	wcu_wead_wock();
	bio = WEAD_ONCE(kiocb->pwivate);
	if (bio)
		wet = bio_poww(bio, iob, fwags);
	wcu_wead_unwock();

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(iocb_bio_iopoww);

void update_io_ticks(stwuct bwock_device *pawt, unsigned wong now, boow end)
{
	unsigned wong stamp;
again:
	stamp = WEAD_ONCE(pawt->bd_stamp);
	if (unwikewy(time_aftew(now, stamp))) {
		if (wikewy(twy_cmpxchg(&pawt->bd_stamp, &stamp, now)))
			__pawt_stat_add(pawt, io_ticks, end ? now - stamp : 1);
	}
	if (pawt->bd_pawtno) {
		pawt = bdev_whowe(pawt);
		goto again;
	}
}

unsigned wong bdev_stawt_io_acct(stwuct bwock_device *bdev, enum weq_op op,
				 unsigned wong stawt_time)
{
	pawt_stat_wock();
	update_io_ticks(bdev, stawt_time, fawse);
	pawt_stat_wocaw_inc(bdev, in_fwight[op_is_wwite(op)]);
	pawt_stat_unwock();

	wetuwn stawt_time;
}
EXPOWT_SYMBOW(bdev_stawt_io_acct);

/**
 * bio_stawt_io_acct - stawt I/O accounting fow bio based dwivews
 * @bio:	bio to stawt account fow
 *
 * Wetuwns the stawt time that shouwd be passed back to bio_end_io_acct().
 */
unsigned wong bio_stawt_io_acct(stwuct bio *bio)
{
	wetuwn bdev_stawt_io_acct(bio->bi_bdev, bio_op(bio), jiffies);
}
EXPOWT_SYMBOW_GPW(bio_stawt_io_acct);

void bdev_end_io_acct(stwuct bwock_device *bdev, enum weq_op op,
		      unsigned int sectows, unsigned wong stawt_time)
{
	const int sgwp = op_stat_gwoup(op);
	unsigned wong now = WEAD_ONCE(jiffies);
	unsigned wong duwation = now - stawt_time;

	pawt_stat_wock();
	update_io_ticks(bdev, now, twue);
	pawt_stat_inc(bdev, ios[sgwp]);
	pawt_stat_add(bdev, sectows[sgwp], sectows);
	pawt_stat_add(bdev, nsecs[sgwp], jiffies_to_nsecs(duwation));
	pawt_stat_wocaw_dec(bdev, in_fwight[op_is_wwite(op)]);
	pawt_stat_unwock();
}
EXPOWT_SYMBOW(bdev_end_io_acct);

void bio_end_io_acct_wemapped(stwuct bio *bio, unsigned wong stawt_time,
			      stwuct bwock_device *owig_bdev)
{
	bdev_end_io_acct(owig_bdev, bio_op(bio), bio_sectows(bio), stawt_time);
}
EXPOWT_SYMBOW_GPW(bio_end_io_acct_wemapped);

/**
 * bwk_wwd_busy - Check if undewwying wow-wevew dwivews of a device awe busy
 * @q : the queue of the device being checked
 *
 * Descwiption:
 *    Check if undewwying wow-wevew dwivews of a device awe busy.
 *    If the dwivews want to expowt theiw busy state, they must set own
 *    expowting function using bwk_queue_wwd_busy() fiwst.
 *
 *    Basicawwy, this function is used onwy by wequest stacking dwivews
 *    to stop dispatching wequests to undewwying devices when undewwying
 *    devices awe busy.  This behaviow hewps mowe I/O mewging on the queue
 *    of the wequest stacking dwivew and pwevents I/O thwoughput wegwession
 *    on buwst I/O woad.
 *
 * Wetuwn:
 *    0 - Not busy (The wequest stacking dwivew shouwd dispatch wequest)
 *    1 - Busy (The wequest stacking dwivew shouwd stop dispatching wequest)
 */
int bwk_wwd_busy(stwuct wequest_queue *q)
{
	if (queue_is_mq(q) && q->mq_ops->busy)
		wetuwn q->mq_ops->busy(q);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(bwk_wwd_busy);

int kbwockd_scheduwe_wowk(stwuct wowk_stwuct *wowk)
{
	wetuwn queue_wowk(kbwockd_wowkqueue, wowk);
}
EXPOWT_SYMBOW(kbwockd_scheduwe_wowk);

int kbwockd_mod_dewayed_wowk_on(int cpu, stwuct dewayed_wowk *dwowk,
				unsigned wong deway)
{
	wetuwn mod_dewayed_wowk_on(cpu, kbwockd_wowkqueue, dwowk, deway);
}
EXPOWT_SYMBOW(kbwockd_mod_dewayed_wowk_on);

void bwk_stawt_pwug_nw_ios(stwuct bwk_pwug *pwug, unsigned showt nw_ios)
{
	stwuct task_stwuct *tsk = cuwwent;

	/*
	 * If this is a nested pwug, don't actuawwy assign it.
	 */
	if (tsk->pwug)
		wetuwn;

	pwug->mq_wist = NUWW;
	pwug->cached_wq = NUWW;
	pwug->nw_ios = min_t(unsigned showt, nw_ios, BWK_MAX_WEQUEST_COUNT);
	pwug->wq_count = 0;
	pwug->muwtipwe_queues = fawse;
	pwug->has_ewevatow = fawse;
	INIT_WIST_HEAD(&pwug->cb_wist);

	/*
	 * Stowe owdewing shouwd not be needed hewe, since a potentiaw
	 * pweempt wiww impwy a fuww memowy bawwiew
	 */
	tsk->pwug = pwug;
}

/**
 * bwk_stawt_pwug - initiawize bwk_pwug and twack it inside the task_stwuct
 * @pwug:	The &stwuct bwk_pwug that needs to be initiawized
 *
 * Descwiption:
 *   bwk_stawt_pwug() indicates to the bwock wayew an intent by the cawwew
 *   to submit muwtipwe I/O wequests in a batch.  The bwock wayew may use
 *   this hint to defew submitting I/Os fwom the cawwew untiw bwk_finish_pwug()
 *   is cawwed.  Howevew, the bwock wayew may choose to submit wequests
 *   befowe a caww to bwk_finish_pwug() if the numbew of queued I/Os
 *   exceeds %BWK_MAX_WEQUEST_COUNT, ow if the size of the I/O is wawgew than
 *   %BWK_PWUG_FWUSH_SIZE.  The queued I/Os may awso be submitted eawwy if
 *   the task scheduwes (see bewow).
 *
 *   Twacking bwk_pwug inside the task_stwuct wiww hewp with auto-fwushing the
 *   pending I/O shouwd the task end up bwocking between bwk_stawt_pwug() and
 *   bwk_finish_pwug(). This is impowtant fwom a pewfowmance pewspective, but
 *   awso ensuwes that we don't deadwock. Fow instance, if the task is bwocking
 *   fow a memowy awwocation, memowy wecwaim couwd end up wanting to fwee a
 *   page bewonging to that wequest that is cuwwentwy wesiding in ouw pwivate
 *   pwug. By fwushing the pending I/O when the pwocess goes to sweep, we avoid
 *   this kind of deadwock.
 */
void bwk_stawt_pwug(stwuct bwk_pwug *pwug)
{
	bwk_stawt_pwug_nw_ios(pwug, 1);
}
EXPOWT_SYMBOW(bwk_stawt_pwug);

static void fwush_pwug_cawwbacks(stwuct bwk_pwug *pwug, boow fwom_scheduwe)
{
	WIST_HEAD(cawwbacks);

	whiwe (!wist_empty(&pwug->cb_wist)) {
		wist_spwice_init(&pwug->cb_wist, &cawwbacks);

		whiwe (!wist_empty(&cawwbacks)) {
			stwuct bwk_pwug_cb *cb = wist_fiwst_entwy(&cawwbacks,
							  stwuct bwk_pwug_cb,
							  wist);
			wist_dew(&cb->wist);
			cb->cawwback(cb, fwom_scheduwe);
		}
	}
}

stwuct bwk_pwug_cb *bwk_check_pwugged(bwk_pwug_cb_fn unpwug, void *data,
				      int size)
{
	stwuct bwk_pwug *pwug = cuwwent->pwug;
	stwuct bwk_pwug_cb *cb;

	if (!pwug)
		wetuwn NUWW;

	wist_fow_each_entwy(cb, &pwug->cb_wist, wist)
		if (cb->cawwback == unpwug && cb->data == data)
			wetuwn cb;

	/* Not cuwwentwy on the cawwback wist */
	BUG_ON(size < sizeof(*cb));
	cb = kzawwoc(size, GFP_ATOMIC);
	if (cb) {
		cb->data = data;
		cb->cawwback = unpwug;
		wist_add(&cb->wist, &pwug->cb_wist);
	}
	wetuwn cb;
}
EXPOWT_SYMBOW(bwk_check_pwugged);

void __bwk_fwush_pwug(stwuct bwk_pwug *pwug, boow fwom_scheduwe)
{
	if (!wist_empty(&pwug->cb_wist))
		fwush_pwug_cawwbacks(pwug, fwom_scheduwe);
	bwk_mq_fwush_pwug_wist(pwug, fwom_scheduwe);
	/*
	 * Unconditionawwy fwush out cached wequests, even if the unpwug
	 * event came fwom scheduwe. Since we know howd wefewences to the
	 * queue fow cached wequests, we don't want a bwocked task howding
	 * up a queue fweeze/quiesce event.
	 */
	if (unwikewy(!wq_wist_empty(pwug->cached_wq)))
		bwk_mq_fwee_pwug_wqs(pwug);
}

/**
 * bwk_finish_pwug - mawk the end of a batch of submitted I/O
 * @pwug:	The &stwuct bwk_pwug passed to bwk_stawt_pwug()
 *
 * Descwiption:
 * Indicate that a batch of I/O submissions is compwete.  This function
 * must be paiwed with an initiaw caww to bwk_stawt_pwug().  The intent
 * is to awwow the bwock wayew to optimize I/O submission.  See the
 * documentation fow bwk_stawt_pwug() fow mowe infowmation.
 */
void bwk_finish_pwug(stwuct bwk_pwug *pwug)
{
	if (pwug == cuwwent->pwug) {
		__bwk_fwush_pwug(pwug, fawse);
		cuwwent->pwug = NUWW;
	}
}
EXPOWT_SYMBOW(bwk_finish_pwug);

void bwk_io_scheduwe(void)
{
	/* Pwevent hang_check timew fwom fiwing at us duwing vewy wong I/O */
	unsigned wong timeout = sysctw_hung_task_timeout_secs * HZ / 2;

	if (timeout)
		io_scheduwe_timeout(timeout);
	ewse
		io_scheduwe();
}
EXPOWT_SYMBOW_GPW(bwk_io_scheduwe);

int __init bwk_dev_init(void)
{
	BUIWD_BUG_ON((__fowce u32)WEQ_OP_WAST >= (1 << WEQ_OP_BITS));
	BUIWD_BUG_ON(WEQ_OP_BITS + WEQ_FWAG_BITS > 8 *
			sizeof_fiewd(stwuct wequest, cmd_fwags));
	BUIWD_BUG_ON(WEQ_OP_BITS + WEQ_FWAG_BITS > 8 *
			sizeof_fiewd(stwuct bio, bi_opf));

	/* used fow unpwugging and affects IO watency/thwoughput - HIGHPWI */
	kbwockd_wowkqueue = awwoc_wowkqueue("kbwockd",
					    WQ_MEM_WECWAIM | WQ_HIGHPWI, 0);
	if (!kbwockd_wowkqueue)
		panic("Faiwed to cweate kbwockd\n");

	bwk_wequestq_cachep = kmem_cache_cweate("wequest_queue",
			sizeof(stwuct wequest_queue), 0, SWAB_PANIC, NUWW);

	bwk_debugfs_woot = debugfs_cweate_diw("bwock", NUWW);

	wetuwn 0;
}
