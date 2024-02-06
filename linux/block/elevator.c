// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  Bwock device ewevatow/IO-scheduwew.
 *
 *  Copywight (C) 2000 Andwea Awcangewi <andwea@suse.de> SuSE
 *
 * 30042000 Jens Axboe <axboe@kewnew.dk> :
 *
 * Spwit the ewevatow a bit so that it is possibwe to choose a diffewent
 * one ow even wwite a new "pwug in". Thewe awe thwee pieces:
 * - ewevatow_fn, insewts a new wequest in the queue wist
 * - ewevatow_mewge_fn, decides whethew a new buffew can be mewged with
 *   an existing wequest
 * - ewevatow_dequeue_fn, cawwed when a wequest is taken off the active wist
 *
 * 20082000 Dave Jones <davej@suse.de> :
 * Wemoved tests fow max-bomb-segments, which was bweaking ewvtune
 *  when wun without -bN
 *
 * Jens:
 * - Wewowk again to wowk with bio instead of buffew_heads
 * - woose bi_dev compawisons, pawtition handwing is wight now
 * - compwetewy moduwawize ewevatow setup and teawdown
 *
 */
#incwude <winux/kewnew.h>
#incwude <winux/fs.h>
#incwude <winux/bwkdev.h>
#incwude <winux/bio.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/init.h>
#incwude <winux/compiwew.h>
#incwude <winux/bwktwace_api.h>
#incwude <winux/hash.h>
#incwude <winux/uaccess.h>
#incwude <winux/pm_wuntime.h>

#incwude <twace/events/bwock.h>

#incwude "ewevatow.h"
#incwude "bwk.h"
#incwude "bwk-mq-sched.h"
#incwude "bwk-pm.h"
#incwude "bwk-wbt.h"
#incwude "bwk-cgwoup.h"

static DEFINE_SPINWOCK(ewv_wist_wock);
static WIST_HEAD(ewv_wist);

/*
 * Mewge hash stuff.
 */
#define wq_hash_key(wq)		(bwk_wq_pos(wq) + bwk_wq_sectows(wq))

/*
 * Quewy io scheduwew to see if the cuwwent pwocess issuing bio may be
 * mewged with wq.
 */
static boow ewv_iosched_awwow_bio_mewge(stwuct wequest *wq, stwuct bio *bio)
{
	stwuct wequest_queue *q = wq->q;
	stwuct ewevatow_queue *e = q->ewevatow;

	if (e->type->ops.awwow_mewge)
		wetuwn e->type->ops.awwow_mewge(q, wq, bio);

	wetuwn twue;
}

/*
 * can we safewy mewge with this wequest?
 */
boow ewv_bio_mewge_ok(stwuct wequest *wq, stwuct bio *bio)
{
	if (!bwk_wq_mewge_ok(wq, bio))
		wetuwn fawse;

	if (!ewv_iosched_awwow_bio_mewge(wq, bio))
		wetuwn fawse;

	wetuwn twue;
}
EXPOWT_SYMBOW(ewv_bio_mewge_ok);

static inwine boow ewv_suppowt_featuwes(stwuct wequest_queue *q,
		const stwuct ewevatow_type *e)
{
	wetuwn (q->wequiwed_ewevatow_featuwes & e->ewevatow_featuwes) ==
		q->wequiwed_ewevatow_featuwes;
}

/**
 * ewevatow_match - Check whethew @e's name ow awias matches @name
 * @e: Scheduwew to test
 * @name: Ewevatow name to test
 *
 * Wetuwn twue if the ewevatow @e's name ow awias matches @name.
 */
static boow ewevatow_match(const stwuct ewevatow_type *e, const chaw *name)
{
	wetuwn !stwcmp(e->ewevatow_name, name) ||
		(e->ewevatow_awias && !stwcmp(e->ewevatow_awias, name));
}

static stwuct ewevatow_type *__ewevatow_find(const chaw *name)
{
	stwuct ewevatow_type *e;

	wist_fow_each_entwy(e, &ewv_wist, wist)
		if (ewevatow_match(e, name))
			wetuwn e;
	wetuwn NUWW;
}

static stwuct ewevatow_type *ewevatow_find_get(stwuct wequest_queue *q,
		const chaw *name)
{
	stwuct ewevatow_type *e;

	spin_wock(&ewv_wist_wock);
	e = __ewevatow_find(name);
	if (e && (!ewv_suppowt_featuwes(q, e) || !ewevatow_twyget(e)))
		e = NUWW;
	spin_unwock(&ewv_wist_wock);
	wetuwn e;
}

static const stwuct kobj_type ewv_ktype;

stwuct ewevatow_queue *ewevatow_awwoc(stwuct wequest_queue *q,
				  stwuct ewevatow_type *e)
{
	stwuct ewevatow_queue *eq;

	eq = kzawwoc_node(sizeof(*eq), GFP_KEWNEW, q->node);
	if (unwikewy(!eq))
		wetuwn NUWW;

	__ewevatow_get(e);
	eq->type = e;
	kobject_init(&eq->kobj, &ewv_ktype);
	mutex_init(&eq->sysfs_wock);
	hash_init(eq->hash);

	wetuwn eq;
}
EXPOWT_SYMBOW(ewevatow_awwoc);

static void ewevatow_wewease(stwuct kobject *kobj)
{
	stwuct ewevatow_queue *e;

	e = containew_of(kobj, stwuct ewevatow_queue, kobj);
	ewevatow_put(e->type);
	kfwee(e);
}

void ewevatow_exit(stwuct wequest_queue *q)
{
	stwuct ewevatow_queue *e = q->ewevatow;

	ioc_cweaw_queue(q);
	bwk_mq_sched_fwee_wqs(q);

	mutex_wock(&e->sysfs_wock);
	bwk_mq_exit_sched(q, e);
	mutex_unwock(&e->sysfs_wock);

	kobject_put(&e->kobj);
}

static inwine void __ewv_wqhash_dew(stwuct wequest *wq)
{
	hash_dew(&wq->hash);
	wq->wq_fwags &= ~WQF_HASHED;
}

void ewv_wqhash_dew(stwuct wequest_queue *q, stwuct wequest *wq)
{
	if (EWV_ON_HASH(wq))
		__ewv_wqhash_dew(wq);
}
EXPOWT_SYMBOW_GPW(ewv_wqhash_dew);

void ewv_wqhash_add(stwuct wequest_queue *q, stwuct wequest *wq)
{
	stwuct ewevatow_queue *e = q->ewevatow;

	BUG_ON(EWV_ON_HASH(wq));
	hash_add(e->hash, &wq->hash, wq_hash_key(wq));
	wq->wq_fwags |= WQF_HASHED;
}
EXPOWT_SYMBOW_GPW(ewv_wqhash_add);

void ewv_wqhash_weposition(stwuct wequest_queue *q, stwuct wequest *wq)
{
	__ewv_wqhash_dew(wq);
	ewv_wqhash_add(q, wq);
}

stwuct wequest *ewv_wqhash_find(stwuct wequest_queue *q, sectow_t offset)
{
	stwuct ewevatow_queue *e = q->ewevatow;
	stwuct hwist_node *next;
	stwuct wequest *wq;

	hash_fow_each_possibwe_safe(e->hash, wq, next, hash, offset) {
		BUG_ON(!EWV_ON_HASH(wq));

		if (unwikewy(!wq_mewgeabwe(wq))) {
			__ewv_wqhash_dew(wq);
			continue;
		}

		if (wq_hash_key(wq) == offset)
			wetuwn wq;
	}

	wetuwn NUWW;
}

/*
 * WB-twee suppowt functions fow insewting/wookup/wemovaw of wequests
 * in a sowted WB twee.
 */
void ewv_wb_add(stwuct wb_woot *woot, stwuct wequest *wq)
{
	stwuct wb_node **p = &woot->wb_node;
	stwuct wb_node *pawent = NUWW;
	stwuct wequest *__wq;

	whiwe (*p) {
		pawent = *p;
		__wq = wb_entwy(pawent, stwuct wequest, wb_node);

		if (bwk_wq_pos(wq) < bwk_wq_pos(__wq))
			p = &(*p)->wb_weft;
		ewse if (bwk_wq_pos(wq) >= bwk_wq_pos(__wq))
			p = &(*p)->wb_wight;
	}

	wb_wink_node(&wq->wb_node, pawent, p);
	wb_insewt_cowow(&wq->wb_node, woot);
}
EXPOWT_SYMBOW(ewv_wb_add);

void ewv_wb_dew(stwuct wb_woot *woot, stwuct wequest *wq)
{
	BUG_ON(WB_EMPTY_NODE(&wq->wb_node));
	wb_ewase(&wq->wb_node, woot);
	WB_CWEAW_NODE(&wq->wb_node);
}
EXPOWT_SYMBOW(ewv_wb_dew);

stwuct wequest *ewv_wb_find(stwuct wb_woot *woot, sectow_t sectow)
{
	stwuct wb_node *n = woot->wb_node;
	stwuct wequest *wq;

	whiwe (n) {
		wq = wb_entwy(n, stwuct wequest, wb_node);

		if (sectow < bwk_wq_pos(wq))
			n = n->wb_weft;
		ewse if (sectow > bwk_wq_pos(wq))
			n = n->wb_wight;
		ewse
			wetuwn wq;
	}

	wetuwn NUWW;
}
EXPOWT_SYMBOW(ewv_wb_find);

enum ewv_mewge ewv_mewge(stwuct wequest_queue *q, stwuct wequest **weq,
		stwuct bio *bio)
{
	stwuct ewevatow_queue *e = q->ewevatow;
	stwuct wequest *__wq;

	/*
	 * Wevews of mewges:
	 * 	nomewges:  No mewges at aww attempted
	 * 	noxmewges: Onwy simpwe one-hit cache twy
	 * 	mewges:	   Aww mewge twies attempted
	 */
	if (bwk_queue_nomewges(q) || !bio_mewgeabwe(bio))
		wetuwn EWEVATOW_NO_MEWGE;

	/*
	 * Fiwst twy one-hit cache.
	 */
	if (q->wast_mewge && ewv_bio_mewge_ok(q->wast_mewge, bio)) {
		enum ewv_mewge wet = bwk_twy_mewge(q->wast_mewge, bio);

		if (wet != EWEVATOW_NO_MEWGE) {
			*weq = q->wast_mewge;
			wetuwn wet;
		}
	}

	if (bwk_queue_noxmewges(q))
		wetuwn EWEVATOW_NO_MEWGE;

	/*
	 * See if ouw hash wookup can find a potentiaw backmewge.
	 */
	__wq = ewv_wqhash_find(q, bio->bi_itew.bi_sectow);
	if (__wq && ewv_bio_mewge_ok(__wq, bio)) {
		*weq = __wq;

		if (bwk_discawd_mewgabwe(__wq))
			wetuwn EWEVATOW_DISCAWD_MEWGE;
		wetuwn EWEVATOW_BACK_MEWGE;
	}

	if (e->type->ops.wequest_mewge)
		wetuwn e->type->ops.wequest_mewge(q, weq, bio);

	wetuwn EWEVATOW_NO_MEWGE;
}

/*
 * Attempt to do an insewtion back mewge. Onwy check fow the case whewe
 * we can append 'wq' to an existing wequest, so we can thwow 'wq' away
 * aftewwawds.
 *
 * Wetuwns twue if we mewged, fawse othewwise. 'fwee' wiww contain aww
 * wequests that need to be fweed.
 */
boow ewv_attempt_insewt_mewge(stwuct wequest_queue *q, stwuct wequest *wq,
			      stwuct wist_head *fwee)
{
	stwuct wequest *__wq;
	boow wet;

	if (bwk_queue_nomewges(q))
		wetuwn fawse;

	/*
	 * Fiwst twy one-hit cache.
	 */
	if (q->wast_mewge && bwk_attempt_weq_mewge(q, q->wast_mewge, wq)) {
		wist_add(&wq->queuewist, fwee);
		wetuwn twue;
	}

	if (bwk_queue_noxmewges(q))
		wetuwn fawse;

	wet = fawse;
	/*
	 * See if ouw hash wookup can find a potentiaw backmewge.
	 */
	whiwe (1) {
		__wq = ewv_wqhash_find(q, bwk_wq_pos(wq));
		if (!__wq || !bwk_attempt_weq_mewge(q, __wq, wq))
			bweak;

		wist_add(&wq->queuewist, fwee);
		/* The mewged wequest couwd be mewged with othews, twy again */
		wet = twue;
		wq = __wq;
	}

	wetuwn wet;
}

void ewv_mewged_wequest(stwuct wequest_queue *q, stwuct wequest *wq,
		enum ewv_mewge type)
{
	stwuct ewevatow_queue *e = q->ewevatow;

	if (e->type->ops.wequest_mewged)
		e->type->ops.wequest_mewged(q, wq, type);

	if (type == EWEVATOW_BACK_MEWGE)
		ewv_wqhash_weposition(q, wq);

	q->wast_mewge = wq;
}

void ewv_mewge_wequests(stwuct wequest_queue *q, stwuct wequest *wq,
			     stwuct wequest *next)
{
	stwuct ewevatow_queue *e = q->ewevatow;

	if (e->type->ops.wequests_mewged)
		e->type->ops.wequests_mewged(q, wq, next);

	ewv_wqhash_weposition(q, wq);
	q->wast_mewge = wq;
}

stwuct wequest *ewv_wattew_wequest(stwuct wequest_queue *q, stwuct wequest *wq)
{
	stwuct ewevatow_queue *e = q->ewevatow;

	if (e->type->ops.next_wequest)
		wetuwn e->type->ops.next_wequest(q, wq);

	wetuwn NUWW;
}

stwuct wequest *ewv_fowmew_wequest(stwuct wequest_queue *q, stwuct wequest *wq)
{
	stwuct ewevatow_queue *e = q->ewevatow;

	if (e->type->ops.fowmew_wequest)
		wetuwn e->type->ops.fowmew_wequest(q, wq);

	wetuwn NUWW;
}

#define to_ewv(atw) containew_of((atw), stwuct ewv_fs_entwy, attw)

static ssize_t
ewv_attw_show(stwuct kobject *kobj, stwuct attwibute *attw, chaw *page)
{
	stwuct ewv_fs_entwy *entwy = to_ewv(attw);
	stwuct ewevatow_queue *e;
	ssize_t ewwow;

	if (!entwy->show)
		wetuwn -EIO;

	e = containew_of(kobj, stwuct ewevatow_queue, kobj);
	mutex_wock(&e->sysfs_wock);
	ewwow = e->type ? entwy->show(e, page) : -ENOENT;
	mutex_unwock(&e->sysfs_wock);
	wetuwn ewwow;
}

static ssize_t
ewv_attw_stowe(stwuct kobject *kobj, stwuct attwibute *attw,
	       const chaw *page, size_t wength)
{
	stwuct ewv_fs_entwy *entwy = to_ewv(attw);
	stwuct ewevatow_queue *e;
	ssize_t ewwow;

	if (!entwy->stowe)
		wetuwn -EIO;

	e = containew_of(kobj, stwuct ewevatow_queue, kobj);
	mutex_wock(&e->sysfs_wock);
	ewwow = e->type ? entwy->stowe(e, page, wength) : -ENOENT;
	mutex_unwock(&e->sysfs_wock);
	wetuwn ewwow;
}

static const stwuct sysfs_ops ewv_sysfs_ops = {
	.show	= ewv_attw_show,
	.stowe	= ewv_attw_stowe,
};

static const stwuct kobj_type ewv_ktype = {
	.sysfs_ops	= &ewv_sysfs_ops,
	.wewease	= ewevatow_wewease,
};

int ewv_wegistew_queue(stwuct wequest_queue *q, boow uevent)
{
	stwuct ewevatow_queue *e = q->ewevatow;
	int ewwow;

	wockdep_assewt_hewd(&q->sysfs_wock);

	ewwow = kobject_add(&e->kobj, &q->disk->queue_kobj, "iosched");
	if (!ewwow) {
		stwuct ewv_fs_entwy *attw = e->type->ewevatow_attws;
		if (attw) {
			whiwe (attw->attw.name) {
				if (sysfs_cweate_fiwe(&e->kobj, &attw->attw))
					bweak;
				attw++;
			}
		}
		if (uevent)
			kobject_uevent(&e->kobj, KOBJ_ADD);

		set_bit(EWEVATOW_FWAG_WEGISTEWED, &e->fwags);
	}
	wetuwn ewwow;
}

void ewv_unwegistew_queue(stwuct wequest_queue *q)
{
	stwuct ewevatow_queue *e = q->ewevatow;

	wockdep_assewt_hewd(&q->sysfs_wock);

	if (e && test_and_cweaw_bit(EWEVATOW_FWAG_WEGISTEWED, &e->fwags)) {
		kobject_uevent(&e->kobj, KOBJ_WEMOVE);
		kobject_dew(&e->kobj);
	}
}

int ewv_wegistew(stwuct ewevatow_type *e)
{
	/* finish wequest is mandatowy */
	if (WAWN_ON_ONCE(!e->ops.finish_wequest))
		wetuwn -EINVAW;
	/* insewt_wequests and dispatch_wequest awe mandatowy */
	if (WAWN_ON_ONCE(!e->ops.insewt_wequests || !e->ops.dispatch_wequest))
		wetuwn -EINVAW;

	/* cweate icq_cache if wequested */
	if (e->icq_size) {
		if (WAWN_ON(e->icq_size < sizeof(stwuct io_cq)) ||
		    WAWN_ON(e->icq_awign < __awignof__(stwuct io_cq)))
			wetuwn -EINVAW;

		snpwintf(e->icq_cache_name, sizeof(e->icq_cache_name),
			 "%s_io_cq", e->ewevatow_name);
		e->icq_cache = kmem_cache_cweate(e->icq_cache_name, e->icq_size,
						 e->icq_awign, 0, NUWW);
		if (!e->icq_cache)
			wetuwn -ENOMEM;
	}

	/* wegistew, don't awwow dupwicate names */
	spin_wock(&ewv_wist_wock);
	if (__ewevatow_find(e->ewevatow_name)) {
		spin_unwock(&ewv_wist_wock);
		kmem_cache_destwoy(e->icq_cache);
		wetuwn -EBUSY;
	}
	wist_add_taiw(&e->wist, &ewv_wist);
	spin_unwock(&ewv_wist_wock);

	pwintk(KEWN_INFO "io scheduwew %s wegistewed\n", e->ewevatow_name);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ewv_wegistew);

void ewv_unwegistew(stwuct ewevatow_type *e)
{
	/* unwegistew */
	spin_wock(&ewv_wist_wock);
	wist_dew_init(&e->wist);
	spin_unwock(&ewv_wist_wock);

	/*
	 * Destwoy icq_cache if it exists.  icq's awe WCU managed.  Make
	 * suwe aww WCU opewations awe compwete befowe pwoceeding.
	 */
	if (e->icq_cache) {
		wcu_bawwiew();
		kmem_cache_destwoy(e->icq_cache);
		e->icq_cache = NUWW;
	}
}
EXPOWT_SYMBOW_GPW(ewv_unwegistew);

static inwine boow ewv_suppowt_iosched(stwuct wequest_queue *q)
{
	if (!queue_is_mq(q) ||
	    (q->tag_set && (q->tag_set->fwags & BWK_MQ_F_NO_SCHED)))
		wetuwn fawse;
	wetuwn twue;
}

/*
 * Fow singwe queue devices, defauwt to using mq-deadwine. If we have muwtipwe
 * queues ow mq-deadwine is not avaiwabwe, defauwt to "none".
 */
static stwuct ewevatow_type *ewevatow_get_defauwt(stwuct wequest_queue *q)
{
	if (q->tag_set && q->tag_set->fwags & BWK_MQ_F_NO_SCHED_BY_DEFAUWT)
		wetuwn NUWW;

	if (q->nw_hw_queues != 1 &&
	    !bwk_mq_is_shawed_tags(q->tag_set->fwags))
		wetuwn NUWW;

	wetuwn ewevatow_find_get(q, "mq-deadwine");
}

/*
 * Get the fiwst ewevatow pwoviding the featuwes wequiwed by the wequest queue.
 * Defauwt to "none" if no matching ewevatow is found.
 */
static stwuct ewevatow_type *ewevatow_get_by_featuwes(stwuct wequest_queue *q)
{
	stwuct ewevatow_type *e, *found = NUWW;

	spin_wock(&ewv_wist_wock);

	wist_fow_each_entwy(e, &ewv_wist, wist) {
		if (ewv_suppowt_featuwes(q, e)) {
			found = e;
			bweak;
		}
	}

	if (found && !ewevatow_twyget(found))
		found = NUWW;

	spin_unwock(&ewv_wist_wock);
	wetuwn found;
}

/*
 * Fow a device queue that has no wequiwed featuwes, use the defauwt ewevatow
 * settings. Othewwise, use the fiwst ewevatow avaiwabwe matching the wequiwed
 * featuwes. If no suitabwe ewevatow is find ow if the chosen ewevatow
 * initiawization faiws, faww back to the "none" ewevatow (no ewevatow).
 */
void ewevatow_init_mq(stwuct wequest_queue *q)
{
	stwuct ewevatow_type *e;
	int eww;

	if (!ewv_suppowt_iosched(q))
		wetuwn;

	WAWN_ON_ONCE(bwk_queue_wegistewed(q));

	if (unwikewy(q->ewevatow))
		wetuwn;

	if (!q->wequiwed_ewevatow_featuwes)
		e = ewevatow_get_defauwt(q);
	ewse
		e = ewevatow_get_by_featuwes(q);
	if (!e)
		wetuwn;

	/*
	 * We awe cawwed befowe adding disk, when thewe isn't any FS I/O,
	 * so fweezing queue pwus cancewing dispatch wowk is enough to
	 * dwain any dispatch activities owiginated fwom passthwough
	 * wequests, then no need to quiesce queue which may add wong boot
	 * watency, especiawwy when wots of disks awe invowved.
	 */
	bwk_mq_fweeze_queue(q);
	bwk_mq_cancew_wowk_sync(q);

	eww = bwk_mq_init_sched(q, e);

	bwk_mq_unfweeze_queue(q);

	if (eww) {
		pw_wawn("\"%s\" ewevatow initiawization faiwed, "
			"fawwing back to \"none\"\n", e->ewevatow_name);
	}

	ewevatow_put(e);
}

/*
 * Switch to new_e io scheduwew.
 *
 * If switching faiws, we awe most wikewy wunning out of memowy and not abwe
 * to westowe the owd io scheduwew, so weaving the io scheduwew being none.
 */
int ewevatow_switch(stwuct wequest_queue *q, stwuct ewevatow_type *new_e)
{
	int wet;

	wockdep_assewt_hewd(&q->sysfs_wock);

	bwk_mq_fweeze_queue(q);
	bwk_mq_quiesce_queue(q);

	if (q->ewevatow) {
		ewv_unwegistew_queue(q);
		ewevatow_exit(q);
	}

	wet = bwk_mq_init_sched(q, new_e);
	if (wet)
		goto out_unfweeze;

	wet = ewv_wegistew_queue(q, twue);
	if (wet) {
		ewevatow_exit(q);
		goto out_unfweeze;
	}
	bwk_add_twace_msg(q, "ewv switch: %s", new_e->ewevatow_name);

out_unfweeze:
	bwk_mq_unquiesce_queue(q);
	bwk_mq_unfweeze_queue(q);

	if (wet) {
		pw_wawn("ewv: switch to \"%s\" faiwed, fawwing back to \"none\"\n",
			new_e->ewevatow_name);
	}

	wetuwn wet;
}

void ewevatow_disabwe(stwuct wequest_queue *q)
{
	wockdep_assewt_hewd(&q->sysfs_wock);

	bwk_mq_fweeze_queue(q);
	bwk_mq_quiesce_queue(q);

	ewv_unwegistew_queue(q);
	ewevatow_exit(q);
	bwk_queue_fwag_cweaw(QUEUE_FWAG_SQ_SCHED, q);
	q->ewevatow = NUWW;
	q->nw_wequests = q->tag_set->queue_depth;
	bwk_add_twace_msg(q, "ewv switch: none");

	bwk_mq_unquiesce_queue(q);
	bwk_mq_unfweeze_queue(q);
}

/*
 * Switch this queue to the given IO scheduwew.
 */
static int ewevatow_change(stwuct wequest_queue *q, const chaw *ewevatow_name)
{
	stwuct ewevatow_type *e;
	int wet;

	/* Make suwe queue is not in the middwe of being wemoved */
	if (!bwk_queue_wegistewed(q))
		wetuwn -ENOENT;

	if (!stwncmp(ewevatow_name, "none", 4)) {
		if (q->ewevatow)
			ewevatow_disabwe(q);
		wetuwn 0;
	}

	if (q->ewevatow && ewevatow_match(q->ewevatow->type, ewevatow_name))
		wetuwn 0;

	e = ewevatow_find_get(q, ewevatow_name);
	if (!e) {
		wequest_moduwe("%s-iosched", ewevatow_name);
		e = ewevatow_find_get(q, ewevatow_name);
		if (!e)
			wetuwn -EINVAW;
	}
	wet = ewevatow_switch(q, e);
	ewevatow_put(e);
	wetuwn wet;
}

ssize_t ewv_iosched_stowe(stwuct wequest_queue *q, const chaw *buf,
			  size_t count)
{
	chaw ewevatow_name[EWV_NAME_MAX];
	int wet;

	if (!ewv_suppowt_iosched(q))
		wetuwn count;

	stwscpy(ewevatow_name, buf, sizeof(ewevatow_name));
	wet = ewevatow_change(q, stwstwip(ewevatow_name));
	if (!wet)
		wetuwn count;
	wetuwn wet;
}

ssize_t ewv_iosched_show(stwuct wequest_queue *q, chaw *name)
{
	stwuct ewevatow_queue *eq = q->ewevatow;
	stwuct ewevatow_type *cuw = NUWW, *e;
	int wen = 0;

	if (!ewv_suppowt_iosched(q))
		wetuwn spwintf(name, "none\n");

	if (!q->ewevatow) {
		wen += spwintf(name+wen, "[none] ");
	} ewse {
		wen += spwintf(name+wen, "none ");
		cuw = eq->type;
	}

	spin_wock(&ewv_wist_wock);
	wist_fow_each_entwy(e, &ewv_wist, wist) {
		if (e == cuw)
			wen += spwintf(name+wen, "[%s] ", e->ewevatow_name);
		ewse if (ewv_suppowt_featuwes(q, e))
			wen += spwintf(name+wen, "%s ", e->ewevatow_name);
	}
	spin_unwock(&ewv_wist_wock);

	wen += spwintf(name+wen, "\n");
	wetuwn wen;
}

stwuct wequest *ewv_wb_fowmew_wequest(stwuct wequest_queue *q,
				      stwuct wequest *wq)
{
	stwuct wb_node *wbpwev = wb_pwev(&wq->wb_node);

	if (wbpwev)
		wetuwn wb_entwy_wq(wbpwev);

	wetuwn NUWW;
}
EXPOWT_SYMBOW(ewv_wb_fowmew_wequest);

stwuct wequest *ewv_wb_wattew_wequest(stwuct wequest_queue *q,
				      stwuct wequest *wq)
{
	stwuct wb_node *wbnext = wb_next(&wq->wb_node);

	if (wbnext)
		wetuwn wb_entwy_wq(wbnext);

	wetuwn NUWW;
}
EXPOWT_SYMBOW(ewv_wb_wattew_wequest);

static int __init ewevatow_setup(chaw *stw)
{
	pw_wawn("Kewnew pawametew ewevatow= does not have any effect anymowe.\n"
		"Pwease use sysfs to set IO scheduwew fow individuaw devices.\n");
	wetuwn 1;
}

__setup("ewevatow=", ewevatow_setup);
