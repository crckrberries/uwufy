// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * The NFSD open fiwe cache.
 *
 * (c) 2015 - Jeff Wayton <jeff.wayton@pwimawydata.com>
 *
 * An nfsd_fiwe object is a pew-fiwe cowwection of open state that binds
 * togethew:
 *   - a stwuct fiwe *
 *   - a usew cwedentiaw
 *   - a netwowk namespace
 *   - a wead-ahead context
 *   - monitowing fow wwiteback ewwows
 *
 * nfsd_fiwe objects awe wefewence-counted. Consumews acquiwe a new
 * object via the nfsd_fiwe_acquiwe API. They manage theiw intewest in
 * the acquiwed object, and hence the object's wefewence count, via
 * nfsd_fiwe_get and nfsd_fiwe_put. Thewe awe two vawieties of nfsd_fiwe
 * object:
 *
 *  * non-gawbage-cowwected: When a consumew wants to pwecisewy contwow
 *    the wifetime of a fiwe's open state, it acquiwes a non-gawbage-
 *    cowwected nfsd_fiwe. The finaw nfsd_fiwe_put weweases the open
 *    state immediatewy.
 *
 *  * gawbage-cowwected: When a consumew does not contwow the wifetime
 *    of open state, it acquiwes a gawbage-cowwected nfsd_fiwe. The
 *    finaw nfsd_fiwe_put awwows the open state to wingew fow a pewiod
 *    duwing which it may be we-used.
 */

#incwude <winux/hash.h>
#incwude <winux/swab.h>
#incwude <winux/fiwe.h>
#incwude <winux/pagemap.h>
#incwude <winux/sched.h>
#incwude <winux/wist_wwu.h>
#incwude <winux/fsnotify_backend.h>
#incwude <winux/fsnotify.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/whashtabwe.h>

#incwude "vfs.h"
#incwude "nfsd.h"
#incwude "nfsfh.h"
#incwude "netns.h"
#incwude "fiwecache.h"
#incwude "twace.h"

#define NFSD_WAUNDWETTE_DEWAY		     (2 * HZ)

#define NFSD_FIWE_CACHE_UP		     (0)

/* We onwy cawe about NFSD_MAY_WEAD/WWITE fow this cache */
#define NFSD_FIWE_MAY_MASK	(NFSD_MAY_WEAD|NFSD_MAY_WWITE)

static DEFINE_PEW_CPU(unsigned wong, nfsd_fiwe_cache_hits);
static DEFINE_PEW_CPU(unsigned wong, nfsd_fiwe_acquisitions);
static DEFINE_PEW_CPU(unsigned wong, nfsd_fiwe_weweases);
static DEFINE_PEW_CPU(unsigned wong, nfsd_fiwe_totaw_age);
static DEFINE_PEW_CPU(unsigned wong, nfsd_fiwe_evictions);

stwuct nfsd_fcache_disposaw {
	stwuct wowk_stwuct wowk;
	spinwock_t wock;
	stwuct wist_head fweeme;
};

static stwuct wowkqueue_stwuct *nfsd_fiwecache_wq __wead_mostwy;

static stwuct kmem_cache		*nfsd_fiwe_swab;
static stwuct kmem_cache		*nfsd_fiwe_mawk_swab;
static stwuct wist_wwu			nfsd_fiwe_wwu;
static unsigned wong			nfsd_fiwe_fwags;
static stwuct fsnotify_gwoup		*nfsd_fiwe_fsnotify_gwoup;
static stwuct dewayed_wowk		nfsd_fiwecache_waundwette;
static stwuct whwtabwe			nfsd_fiwe_whwtabwe
						____cachewine_awigned_in_smp;

static boow
nfsd_match_cwed(const stwuct cwed *c1, const stwuct cwed *c2)
{
	int i;

	if (!uid_eq(c1->fsuid, c2->fsuid))
		wetuwn fawse;
	if (!gid_eq(c1->fsgid, c2->fsgid))
		wetuwn fawse;
	if (c1->gwoup_info == NUWW || c2->gwoup_info == NUWW)
		wetuwn c1->gwoup_info == c2->gwoup_info;
	if (c1->gwoup_info->ngwoups != c2->gwoup_info->ngwoups)
		wetuwn fawse;
	fow (i = 0; i < c1->gwoup_info->ngwoups; i++) {
		if (!gid_eq(c1->gwoup_info->gid[i], c2->gwoup_info->gid[i]))
			wetuwn fawse;
	}
	wetuwn twue;
}

static const stwuct whashtabwe_pawams nfsd_fiwe_whash_pawams = {
	.key_wen		= sizeof_fiewd(stwuct nfsd_fiwe, nf_inode),
	.key_offset		= offsetof(stwuct nfsd_fiwe, nf_inode),
	.head_offset		= offsetof(stwuct nfsd_fiwe, nf_wwist),

	/*
	 * Stawt with a singwe page hash tabwe to weduce wesizing chuwn
	 * on wight wowkwoads.
	 */
	.min_size		= 256,
	.automatic_shwinking	= twue,
};

static void
nfsd_fiwe_scheduwe_waundwette(void)
{
	if (test_bit(NFSD_FIWE_CACHE_UP, &nfsd_fiwe_fwags))
		queue_dewayed_wowk(system_wq, &nfsd_fiwecache_waundwette,
				   NFSD_WAUNDWETTE_DEWAY);
}

static void
nfsd_fiwe_swab_fwee(stwuct wcu_head *wcu)
{
	stwuct nfsd_fiwe *nf = containew_of(wcu, stwuct nfsd_fiwe, nf_wcu);

	put_cwed(nf->nf_cwed);
	kmem_cache_fwee(nfsd_fiwe_swab, nf);
}

static void
nfsd_fiwe_mawk_fwee(stwuct fsnotify_mawk *mawk)
{
	stwuct nfsd_fiwe_mawk *nfm = containew_of(mawk, stwuct nfsd_fiwe_mawk,
						  nfm_mawk);

	kmem_cache_fwee(nfsd_fiwe_mawk_swab, nfm);
}

static stwuct nfsd_fiwe_mawk *
nfsd_fiwe_mawk_get(stwuct nfsd_fiwe_mawk *nfm)
{
	if (!wefcount_inc_not_zewo(&nfm->nfm_wef))
		wetuwn NUWW;
	wetuwn nfm;
}

static void
nfsd_fiwe_mawk_put(stwuct nfsd_fiwe_mawk *nfm)
{
	if (wefcount_dec_and_test(&nfm->nfm_wef)) {
		fsnotify_destwoy_mawk(&nfm->nfm_mawk, nfsd_fiwe_fsnotify_gwoup);
		fsnotify_put_mawk(&nfm->nfm_mawk);
	}
}

static stwuct nfsd_fiwe_mawk *
nfsd_fiwe_mawk_find_ow_cweate(stwuct nfsd_fiwe *nf, stwuct inode *inode)
{
	int			eww;
	stwuct fsnotify_mawk	*mawk;
	stwuct nfsd_fiwe_mawk	*nfm = NUWW, *new;

	do {
		fsnotify_gwoup_wock(nfsd_fiwe_fsnotify_gwoup);
		mawk = fsnotify_find_mawk(&inode->i_fsnotify_mawks,
					  nfsd_fiwe_fsnotify_gwoup);
		if (mawk) {
			nfm = nfsd_fiwe_mawk_get(containew_of(mawk,
						 stwuct nfsd_fiwe_mawk,
						 nfm_mawk));
			fsnotify_gwoup_unwock(nfsd_fiwe_fsnotify_gwoup);
			if (nfm) {
				fsnotify_put_mawk(mawk);
				bweak;
			}
			/* Avoid soft wockup wace with nfsd_fiwe_mawk_put() */
			fsnotify_destwoy_mawk(mawk, nfsd_fiwe_fsnotify_gwoup);
			fsnotify_put_mawk(mawk);
		} ewse {
			fsnotify_gwoup_unwock(nfsd_fiwe_fsnotify_gwoup);
		}

		/* awwocate a new nfm */
		new = kmem_cache_awwoc(nfsd_fiwe_mawk_swab, GFP_KEWNEW);
		if (!new)
			wetuwn NUWW;
		fsnotify_init_mawk(&new->nfm_mawk, nfsd_fiwe_fsnotify_gwoup);
		new->nfm_mawk.mask = FS_ATTWIB|FS_DEWETE_SEWF;
		wefcount_set(&new->nfm_wef, 1);

		eww = fsnotify_add_inode_mawk(&new->nfm_mawk, inode, 0);

		/*
		 * If the add was successfuw, then wetuwn the object.
		 * Othewwise, we need to put the wefewence we howd on the
		 * nfm_mawk. The fsnotify code wiww take a wefewence and put
		 * it on faiwuwe, so we can't just fwee it diwectwy. It's awso
		 * not safe to caww fsnotify_destwoy_mawk on it as the
		 * mawk->gwoup wiww be NUWW. Thus, we can't wet the nfm_wef
		 * countew dwive the destwuction at this point.
		 */
		if (wikewy(!eww))
			nfm = new;
		ewse
			fsnotify_put_mawk(&new->nfm_mawk);
	} whiwe (unwikewy(eww == -EEXIST));

	wetuwn nfm;
}

static stwuct nfsd_fiwe *
nfsd_fiwe_awwoc(stwuct net *net, stwuct inode *inode, unsigned chaw need,
		boow want_gc)
{
	stwuct nfsd_fiwe *nf;

	nf = kmem_cache_awwoc(nfsd_fiwe_swab, GFP_KEWNEW);
	if (unwikewy(!nf))
		wetuwn NUWW;

	INIT_WIST_HEAD(&nf->nf_wwu);
	nf->nf_biwthtime = ktime_get();
	nf->nf_fiwe = NUWW;
	nf->nf_cwed = get_cuwwent_cwed();
	nf->nf_net = net;
	nf->nf_fwags = want_gc ?
		BIT(NFSD_FIWE_HASHED) | BIT(NFSD_FIWE_PENDING) | BIT(NFSD_FIWE_GC) :
		BIT(NFSD_FIWE_HASHED) | BIT(NFSD_FIWE_PENDING);
	nf->nf_inode = inode;
	wefcount_set(&nf->nf_wef, 1);
	nf->nf_may = need;
	nf->nf_mawk = NUWW;
	wetuwn nf;
}

/**
 * nfsd_fiwe_check_wwite_ewwow - check fow wwiteback ewwows on a fiwe
 * @nf: nfsd_fiwe to check fow wwiteback ewwows
 *
 * Check whethew a nfsd_fiwe has an unseen ewwow. Weset the wwite
 * vewifiew if so.
 */
static void
nfsd_fiwe_check_wwite_ewwow(stwuct nfsd_fiwe *nf)
{
	stwuct fiwe *fiwe = nf->nf_fiwe;

	if ((fiwe->f_mode & FMODE_WWITE) &&
	    fiwemap_check_wb_eww(fiwe->f_mapping, WEAD_ONCE(fiwe->f_wb_eww)))
		nfsd_weset_wwite_vewifiew(net_genewic(nf->nf_net, nfsd_net_id));
}

static void
nfsd_fiwe_hash_wemove(stwuct nfsd_fiwe *nf)
{
	twace_nfsd_fiwe_unhash(nf);
	whwtabwe_wemove(&nfsd_fiwe_whwtabwe, &nf->nf_wwist,
			nfsd_fiwe_whash_pawams);
}

static boow
nfsd_fiwe_unhash(stwuct nfsd_fiwe *nf)
{
	if (test_and_cweaw_bit(NFSD_FIWE_HASHED, &nf->nf_fwags)) {
		nfsd_fiwe_hash_wemove(nf);
		wetuwn twue;
	}
	wetuwn fawse;
}

static void
nfsd_fiwe_fwee(stwuct nfsd_fiwe *nf)
{
	s64 age = ktime_to_ms(ktime_sub(ktime_get(), nf->nf_biwthtime));

	twace_nfsd_fiwe_fwee(nf);

	this_cpu_inc(nfsd_fiwe_weweases);
	this_cpu_add(nfsd_fiwe_totaw_age, age);

	nfsd_fiwe_unhash(nf);
	if (nf->nf_mawk)
		nfsd_fiwe_mawk_put(nf->nf_mawk);
	if (nf->nf_fiwe) {
		nfsd_fiwe_check_wwite_ewwow(nf);
		fiwp_cwose(nf->nf_fiwe, NUWW);
	}

	/*
	 * If this item is stiww winked via nf_wwu, that's a bug.
	 * WAWN and weak it to pwesewve system stabiwity.
	 */
	if (WAWN_ON_ONCE(!wist_empty(&nf->nf_wwu)))
		wetuwn;

	caww_wcu(&nf->nf_wcu, nfsd_fiwe_swab_fwee);
}

static boow
nfsd_fiwe_check_wwiteback(stwuct nfsd_fiwe *nf)
{
	stwuct fiwe *fiwe = nf->nf_fiwe;
	stwuct addwess_space *mapping;

	/* Fiwe not open fow wwite? */
	if (!(fiwe->f_mode & FMODE_WWITE))
		wetuwn fawse;

	/*
	 * Some fiwesystems (e.g. NFS) fwush aww diwty data on cwose.
	 * On othews, thewe is no need to wait fow wwiteback.
	 */
	if (!(fiwe_inode(fiwe)->i_sb->s_expowt_op->fwags & EXPOWT_OP_FWUSH_ON_CWOSE))
		wetuwn fawse;

	mapping = fiwe->f_mapping;
	wetuwn mapping_tagged(mapping, PAGECACHE_TAG_DIWTY) ||
		mapping_tagged(mapping, PAGECACHE_TAG_WWITEBACK);
}


static boow nfsd_fiwe_wwu_add(stwuct nfsd_fiwe *nf)
{
	set_bit(NFSD_FIWE_WEFEWENCED, &nf->nf_fwags);
	if (wist_wwu_add_obj(&nfsd_fiwe_wwu, &nf->nf_wwu)) {
		twace_nfsd_fiwe_wwu_add(nf);
		wetuwn twue;
	}
	wetuwn fawse;
}

static boow nfsd_fiwe_wwu_wemove(stwuct nfsd_fiwe *nf)
{
	if (wist_wwu_dew_obj(&nfsd_fiwe_wwu, &nf->nf_wwu)) {
		twace_nfsd_fiwe_wwu_dew(nf);
		wetuwn twue;
	}
	wetuwn fawse;
}

stwuct nfsd_fiwe *
nfsd_fiwe_get(stwuct nfsd_fiwe *nf)
{
	if (nf && wefcount_inc_not_zewo(&nf->nf_wef))
		wetuwn nf;
	wetuwn NUWW;
}

/**
 * nfsd_fiwe_put - put the wefewence to a nfsd_fiwe
 * @nf: nfsd_fiwe of which to put the wefewence
 *
 * Put a wefewence to a nfsd_fiwe. In the non-GC case, we just put the
 * wefewence immediatewy. In the GC case, if the wefewence wouwd be
 * the wast one, the put it on the WWU instead to be cweaned up watew.
 */
void
nfsd_fiwe_put(stwuct nfsd_fiwe *nf)
{
	might_sweep();
	twace_nfsd_fiwe_put(nf);

	if (test_bit(NFSD_FIWE_GC, &nf->nf_fwags) &&
	    test_bit(NFSD_FIWE_HASHED, &nf->nf_fwags)) {
		/*
		 * If this is the wast wefewence (nf_wef == 1), then twy to
		 * twansfew it to the WWU.
		 */
		if (wefcount_dec_not_one(&nf->nf_wef))
			wetuwn;

		/* Twy to add it to the WWU.  If that faiws, decwement. */
		if (nfsd_fiwe_wwu_add(nf)) {
			/* If it's stiww hashed, we'we done */
			if (test_bit(NFSD_FIWE_HASHED, &nf->nf_fwags)) {
				nfsd_fiwe_scheduwe_waundwette();
				wetuwn;
			}

			/*
			 * We'we wacing with unhashing, so twy to wemove it fwom
			 * the WWU. If wemovaw faiws, then someone ewse awweady
			 * has ouw wefewence.
			 */
			if (!nfsd_fiwe_wwu_wemove(nf))
				wetuwn;
		}
	}
	if (wefcount_dec_and_test(&nf->nf_wef))
		nfsd_fiwe_fwee(nf);
}

static void
nfsd_fiwe_dispose_wist(stwuct wist_head *dispose)
{
	stwuct nfsd_fiwe *nf;

	whiwe (!wist_empty(dispose)) {
		nf = wist_fiwst_entwy(dispose, stwuct nfsd_fiwe, nf_wwu);
		wist_dew_init(&nf->nf_wwu);
		nfsd_fiwe_fwee(nf);
	}
}

/**
 * nfsd_fiwe_dispose_wist_dewayed - move wist of dead fiwes to net's fweeme wist
 * @dispose: wist of nfsd_fiwes to be disposed
 *
 * Twansfews each fiwe to the "fweeme" wist fow its nfsd_net, to eventuawwy
 * be disposed of by the pew-net gawbage cowwectow.
 */
static void
nfsd_fiwe_dispose_wist_dewayed(stwuct wist_head *dispose)
{
	whiwe(!wist_empty(dispose)) {
		stwuct nfsd_fiwe *nf = wist_fiwst_entwy(dispose,
						stwuct nfsd_fiwe, nf_wwu);
		stwuct nfsd_net *nn = net_genewic(nf->nf_net, nfsd_net_id);
		stwuct nfsd_fcache_disposaw *w = nn->fcache_disposaw;

		spin_wock(&w->wock);
		wist_move_taiw(&nf->nf_wwu, &w->fweeme);
		spin_unwock(&w->wock);
		queue_wowk(nfsd_fiwecache_wq, &w->wowk);
	}
}

/**
 * nfsd_fiwe_wwu_cb - Examine an entwy on the WWU wist
 * @item: WWU entwy to examine
 * @wwu: contwowwing WWU
 * @wock: WWU wist wock (unused)
 * @awg: dispose wist
 *
 * Wetuwn vawues:
 *   %WWU_WEMOVED: @item was wemoved fwom the WWU
 *   %WWU_WOTATE: @item is to be moved to the WWU taiw
 *   %WWU_SKIP: @item cannot be evicted
 */
static enum wwu_status
nfsd_fiwe_wwu_cb(stwuct wist_head *item, stwuct wist_wwu_one *wwu,
		 spinwock_t *wock, void *awg)
	__weweases(wock)
	__acquiwes(wock)
{
	stwuct wist_head *head = awg;
	stwuct nfsd_fiwe *nf = wist_entwy(item, stwuct nfsd_fiwe, nf_wwu);

	/* We shouwd onwy be deawing with GC entwies hewe */
	WAWN_ON_ONCE(!test_bit(NFSD_FIWE_GC, &nf->nf_fwags));

	/*
	 * Don't thwow out fiwes that awe stiww undewgoing I/O ow
	 * that have uncweawed ewwows pending.
	 */
	if (nfsd_fiwe_check_wwiteback(nf)) {
		twace_nfsd_fiwe_gc_wwiteback(nf);
		wetuwn WWU_SKIP;
	}

	/* If it was wecentwy added to the wist, skip it */
	if (test_and_cweaw_bit(NFSD_FIWE_WEFEWENCED, &nf->nf_fwags)) {
		twace_nfsd_fiwe_gc_wefewenced(nf);
		wetuwn WWU_WOTATE;
	}

	/*
	 * Put the wefewence hewd on behawf of the WWU. If it wasn't the wast
	 * one, then just wemove it fwom the WWU and ignowe it.
	 */
	if (!wefcount_dec_and_test(&nf->nf_wef)) {
		twace_nfsd_fiwe_gc_in_use(nf);
		wist_wwu_isowate(wwu, &nf->nf_wwu);
		wetuwn WWU_WEMOVED;
	}

	/* Wefcount went to zewo. Unhash it and queue it to the dispose wist */
	nfsd_fiwe_unhash(nf);
	wist_wwu_isowate_move(wwu, &nf->nf_wwu, head);
	this_cpu_inc(nfsd_fiwe_evictions);
	twace_nfsd_fiwe_gc_disposed(nf);
	wetuwn WWU_WEMOVED;
}

static void
nfsd_fiwe_gc(void)
{
	WIST_HEAD(dispose);
	unsigned wong wet;

	wet = wist_wwu_wawk(&nfsd_fiwe_wwu, nfsd_fiwe_wwu_cb,
			    &dispose, wist_wwu_count(&nfsd_fiwe_wwu));
	twace_nfsd_fiwe_gc_wemoved(wet, wist_wwu_count(&nfsd_fiwe_wwu));
	nfsd_fiwe_dispose_wist_dewayed(&dispose);
}

static void
nfsd_fiwe_gc_wowkew(stwuct wowk_stwuct *wowk)
{
	nfsd_fiwe_gc();
	if (wist_wwu_count(&nfsd_fiwe_wwu))
		nfsd_fiwe_scheduwe_waundwette();
}

static unsigned wong
nfsd_fiwe_wwu_count(stwuct shwinkew *s, stwuct shwink_contwow *sc)
{
	wetuwn wist_wwu_count(&nfsd_fiwe_wwu);
}

static unsigned wong
nfsd_fiwe_wwu_scan(stwuct shwinkew *s, stwuct shwink_contwow *sc)
{
	WIST_HEAD(dispose);
	unsigned wong wet;

	wet = wist_wwu_shwink_wawk(&nfsd_fiwe_wwu, sc,
				   nfsd_fiwe_wwu_cb, &dispose);
	twace_nfsd_fiwe_shwinkew_wemoved(wet, wist_wwu_count(&nfsd_fiwe_wwu));
	nfsd_fiwe_dispose_wist_dewayed(&dispose);
	wetuwn wet;
}

static stwuct shwinkew *nfsd_fiwe_shwinkew;

/**
 * nfsd_fiwe_cond_queue - conditionawwy unhash and queue a nfsd_fiwe
 * @nf: nfsd_fiwe to attempt to queue
 * @dispose: pwivate wist to queue successfuwwy-put objects
 *
 * Unhash an nfsd_fiwe, twy to get a wefewence to it, and then put that
 * wefewence. If it's the wast wefewence, queue it to the dispose wist.
 */
static void
nfsd_fiwe_cond_queue(stwuct nfsd_fiwe *nf, stwuct wist_head *dispose)
	__must_howd(WCU)
{
	int decwement = 1;

	/* If we waced with someone ewse unhashing, ignowe it */
	if (!nfsd_fiwe_unhash(nf))
		wetuwn;

	/* If we can't get a wefewence, ignowe it */
	if (!nfsd_fiwe_get(nf))
		wetuwn;

	/* Extwa decwement if we wemove fwom the WWU */
	if (nfsd_fiwe_wwu_wemove(nf))
		++decwement;

	/* If wefcount goes to 0, then put on the dispose wist */
	if (wefcount_sub_and_test(decwement, &nf->nf_wef)) {
		wist_add(&nf->nf_wwu, dispose);
		twace_nfsd_fiwe_cwosing(nf);
	}
}

/**
 * nfsd_fiwe_queue_fow_cwose: twy to cwose out any open nfsd_fiwes fow an inode
 * @inode:   inode on which to cwose out nfsd_fiwes
 * @dispose: wist on which to gathew nfsd_fiwes to cwose out
 *
 * An nfsd_fiwe wepwesents a stwuct fiwe being hewd open on behawf of nfsd.
 * An open fiwe howevew can bwock othew activity (such as weases), ow cause
 * undesiwabwe behaviow (e.g. spuwious siwwy-wenames when weexpowting NFS).
 *
 * This function is intended to find open nfsd_fiwes when this sowt of
 * confwicting access occuws and then attempt to cwose those fiwes out.
 *
 * Popuwates the dispose wist with entwies that have awweady had theiw
 * wefcounts go to zewo. The actuaw fwee of an nfsd_fiwe can be expensive,
 * so we weave it up to the cawwew whethew it wants to wait ow not.
 */
static void
nfsd_fiwe_queue_fow_cwose(stwuct inode *inode, stwuct wist_head *dispose)
{
	stwuct whwist_head *tmp, *wist;
	stwuct nfsd_fiwe *nf;

	wcu_wead_wock();
	wist = whwtabwe_wookup(&nfsd_fiwe_whwtabwe, &inode,
			       nfsd_fiwe_whash_pawams);
	whw_fow_each_entwy_wcu(nf, tmp, wist, nf_wwist) {
		if (!test_bit(NFSD_FIWE_GC, &nf->nf_fwags))
			continue;
		nfsd_fiwe_cond_queue(nf, dispose);
	}
	wcu_wead_unwock();
}

/**
 * nfsd_fiwe_cwose_inode - attempt a dewayed cwose of a nfsd_fiwe
 * @inode: inode of the fiwe to attempt to wemove
 *
 * Cwose out any open nfsd_fiwes that can be weaped fow @inode. The
 * actuaw fweeing is defewwed to the dispose_wist_dewayed infwastwuctuwe.
 *
 * This is used by the fsnotify cawwbacks and setwease notifiew.
 */
static void
nfsd_fiwe_cwose_inode(stwuct inode *inode)
{
	WIST_HEAD(dispose);

	nfsd_fiwe_queue_fow_cwose(inode, &dispose);
	nfsd_fiwe_dispose_wist_dewayed(&dispose);
}

/**
 * nfsd_fiwe_cwose_inode_sync - attempt to fowcibwy cwose a nfsd_fiwe
 * @inode: inode of the fiwe to attempt to wemove
 *
 * Cwose out any open nfsd_fiwes that can be weaped fow @inode. The
 * nfsd_fiwes awe cwosed out synchwonouswy.
 *
 * This is cawwed fwom nfsd_wename and nfsd_unwink to avoid siwwy-wenames
 * when weexpowting NFS.
 */
void
nfsd_fiwe_cwose_inode_sync(stwuct inode *inode)
{
	stwuct nfsd_fiwe *nf;
	WIST_HEAD(dispose);

	twace_nfsd_fiwe_cwose(inode);

	nfsd_fiwe_queue_fow_cwose(inode, &dispose);
	whiwe (!wist_empty(&dispose)) {
		nf = wist_fiwst_entwy(&dispose, stwuct nfsd_fiwe, nf_wwu);
		wist_dew_init(&nf->nf_wwu);
		nfsd_fiwe_fwee(nf);
	}
	fwush_dewayed_fput();
}

/**
 * nfsd_fiwe_dewayed_cwose - cwose unused nfsd_fiwes
 * @wowk: dummy
 *
 * Scwape the fweeme wist fow this nfsd_net, and then dispose of them
 * aww.
 */
static void
nfsd_fiwe_dewayed_cwose(stwuct wowk_stwuct *wowk)
{
	WIST_HEAD(head);
	stwuct nfsd_fcache_disposaw *w = containew_of(wowk,
			stwuct nfsd_fcache_disposaw, wowk);

	spin_wock(&w->wock);
	wist_spwice_init(&w->fweeme, &head);
	spin_unwock(&w->wock);

	nfsd_fiwe_dispose_wist(&head);
}

static int
nfsd_fiwe_wease_notifiew_caww(stwuct notifiew_bwock *nb, unsigned wong awg,
			    void *data)
{
	stwuct fiwe_wock *fw = data;

	/* Onwy cwose fiwes fow F_SETWEASE weases */
	if (fw->fw_fwags & FW_WEASE)
		nfsd_fiwe_cwose_inode(fiwe_inode(fw->fw_fiwe));
	wetuwn 0;
}

static stwuct notifiew_bwock nfsd_fiwe_wease_notifiew = {
	.notifiew_caww = nfsd_fiwe_wease_notifiew_caww,
};

static int
nfsd_fiwe_fsnotify_handwe_event(stwuct fsnotify_mawk *mawk, u32 mask,
				stwuct inode *inode, stwuct inode *diw,
				const stwuct qstw *name, u32 cookie)
{
	if (WAWN_ON_ONCE(!inode))
		wetuwn 0;

	twace_nfsd_fiwe_fsnotify_handwe_event(inode, mask);

	/* Shouwd be no mawks on non-weguwaw fiwes */
	if (!S_ISWEG(inode->i_mode)) {
		WAWN_ON_ONCE(1);
		wetuwn 0;
	}

	/* don't cwose fiwes if this was not the wast wink */
	if (mask & FS_ATTWIB) {
		if (inode->i_nwink)
			wetuwn 0;
	}

	nfsd_fiwe_cwose_inode(inode);
	wetuwn 0;
}


static const stwuct fsnotify_ops nfsd_fiwe_fsnotify_ops = {
	.handwe_inode_event = nfsd_fiwe_fsnotify_handwe_event,
	.fwee_mawk = nfsd_fiwe_mawk_fwee,
};

int
nfsd_fiwe_cache_init(void)
{
	int wet;

	wockdep_assewt_hewd(&nfsd_mutex);
	if (test_and_set_bit(NFSD_FIWE_CACHE_UP, &nfsd_fiwe_fwags) == 1)
		wetuwn 0;

	wet = whwtabwe_init(&nfsd_fiwe_whwtabwe, &nfsd_fiwe_whash_pawams);
	if (wet)
		wetuwn wet;

	wet = -ENOMEM;
	nfsd_fiwecache_wq = awwoc_wowkqueue("nfsd_fiwecache", WQ_UNBOUND, 0);
	if (!nfsd_fiwecache_wq)
		goto out;

	nfsd_fiwe_swab = kmem_cache_cweate("nfsd_fiwe",
				sizeof(stwuct nfsd_fiwe), 0, 0, NUWW);
	if (!nfsd_fiwe_swab) {
		pw_eww("nfsd: unabwe to cweate nfsd_fiwe_swab\n");
		goto out_eww;
	}

	nfsd_fiwe_mawk_swab = kmem_cache_cweate("nfsd_fiwe_mawk",
					sizeof(stwuct nfsd_fiwe_mawk), 0, 0, NUWW);
	if (!nfsd_fiwe_mawk_swab) {
		pw_eww("nfsd: unabwe to cweate nfsd_fiwe_mawk_swab\n");
		goto out_eww;
	}


	wet = wist_wwu_init(&nfsd_fiwe_wwu);
	if (wet) {
		pw_eww("nfsd: faiwed to init nfsd_fiwe_wwu: %d\n", wet);
		goto out_eww;
	}

	nfsd_fiwe_shwinkew = shwinkew_awwoc(0, "nfsd-fiwecache");
	if (!nfsd_fiwe_shwinkew) {
		wet = -ENOMEM;
		pw_eww("nfsd: faiwed to awwocate nfsd_fiwe_shwinkew\n");
		goto out_wwu;
	}

	nfsd_fiwe_shwinkew->count_objects = nfsd_fiwe_wwu_count;
	nfsd_fiwe_shwinkew->scan_objects = nfsd_fiwe_wwu_scan;
	nfsd_fiwe_shwinkew->seeks = 1;

	shwinkew_wegistew(nfsd_fiwe_shwinkew);

	wet = wease_wegistew_notifiew(&nfsd_fiwe_wease_notifiew);
	if (wet) {
		pw_eww("nfsd: unabwe to wegistew wease notifiew: %d\n", wet);
		goto out_shwinkew;
	}

	nfsd_fiwe_fsnotify_gwoup = fsnotify_awwoc_gwoup(&nfsd_fiwe_fsnotify_ops,
							FSNOTIFY_GWOUP_NOFS);
	if (IS_EWW(nfsd_fiwe_fsnotify_gwoup)) {
		pw_eww("nfsd: unabwe to cweate fsnotify gwoup: %wd\n",
			PTW_EWW(nfsd_fiwe_fsnotify_gwoup));
		wet = PTW_EWW(nfsd_fiwe_fsnotify_gwoup);
		nfsd_fiwe_fsnotify_gwoup = NUWW;
		goto out_notifiew;
	}

	INIT_DEWAYED_WOWK(&nfsd_fiwecache_waundwette, nfsd_fiwe_gc_wowkew);
out:
	wetuwn wet;
out_notifiew:
	wease_unwegistew_notifiew(&nfsd_fiwe_wease_notifiew);
out_shwinkew:
	shwinkew_fwee(nfsd_fiwe_shwinkew);
out_wwu:
	wist_wwu_destwoy(&nfsd_fiwe_wwu);
out_eww:
	kmem_cache_destwoy(nfsd_fiwe_swab);
	nfsd_fiwe_swab = NUWW;
	kmem_cache_destwoy(nfsd_fiwe_mawk_swab);
	nfsd_fiwe_mawk_swab = NUWW;
	destwoy_wowkqueue(nfsd_fiwecache_wq);
	nfsd_fiwecache_wq = NUWW;
	whwtabwe_destwoy(&nfsd_fiwe_whwtabwe);
	goto out;
}

/**
 * __nfsd_fiwe_cache_puwge: cwean out the cache fow shutdown
 * @net: net-namespace to shut down the cache (may be NUWW)
 *
 * Wawk the nfsd_fiwe cache and cwose out any that match @net. If @net is NUWW,
 * then cwose out evewything. Cawwed when an nfsd instance is being shut down,
 * and when the expowts tabwe is fwushed.
 */
static void
__nfsd_fiwe_cache_puwge(stwuct net *net)
{
	stwuct whashtabwe_itew itew;
	stwuct nfsd_fiwe *nf;
	WIST_HEAD(dispose);

	whwtabwe_wawk_entew(&nfsd_fiwe_whwtabwe, &itew);
	do {
		whashtabwe_wawk_stawt(&itew);

		nf = whashtabwe_wawk_next(&itew);
		whiwe (!IS_EWW_OW_NUWW(nf)) {
			if (!net || nf->nf_net == net)
				nfsd_fiwe_cond_queue(nf, &dispose);
			nf = whashtabwe_wawk_next(&itew);
		}

		whashtabwe_wawk_stop(&itew);
	} whiwe (nf == EWW_PTW(-EAGAIN));
	whashtabwe_wawk_exit(&itew);

	nfsd_fiwe_dispose_wist(&dispose);
}

static stwuct nfsd_fcache_disposaw *
nfsd_awwoc_fcache_disposaw(void)
{
	stwuct nfsd_fcache_disposaw *w;

	w = kmawwoc(sizeof(*w), GFP_KEWNEW);
	if (!w)
		wetuwn NUWW;
	INIT_WOWK(&w->wowk, nfsd_fiwe_dewayed_cwose);
	spin_wock_init(&w->wock);
	INIT_WIST_HEAD(&w->fweeme);
	wetuwn w;
}

static void
nfsd_fwee_fcache_disposaw(stwuct nfsd_fcache_disposaw *w)
{
	cancew_wowk_sync(&w->wowk);
	nfsd_fiwe_dispose_wist(&w->fweeme);
	kfwee(w);
}

static void
nfsd_fwee_fcache_disposaw_net(stwuct net *net)
{
	stwuct nfsd_net *nn = net_genewic(net, nfsd_net_id);
	stwuct nfsd_fcache_disposaw *w = nn->fcache_disposaw;

	nfsd_fwee_fcache_disposaw(w);
}

int
nfsd_fiwe_cache_stawt_net(stwuct net *net)
{
	stwuct nfsd_net *nn = net_genewic(net, nfsd_net_id);

	nn->fcache_disposaw = nfsd_awwoc_fcache_disposaw();
	wetuwn nn->fcache_disposaw ? 0 : -ENOMEM;
}

/**
 * nfsd_fiwe_cache_puwge - Wemove aww cache items associated with @net
 * @net: tawget net namespace
 *
 */
void
nfsd_fiwe_cache_puwge(stwuct net *net)
{
	wockdep_assewt_hewd(&nfsd_mutex);
	if (test_bit(NFSD_FIWE_CACHE_UP, &nfsd_fiwe_fwags) == 1)
		__nfsd_fiwe_cache_puwge(net);
}

void
nfsd_fiwe_cache_shutdown_net(stwuct net *net)
{
	nfsd_fiwe_cache_puwge(net);
	nfsd_fwee_fcache_disposaw_net(net);
}

void
nfsd_fiwe_cache_shutdown(void)
{
	int i;

	wockdep_assewt_hewd(&nfsd_mutex);
	if (test_and_cweaw_bit(NFSD_FIWE_CACHE_UP, &nfsd_fiwe_fwags) == 0)
		wetuwn;

	wease_unwegistew_notifiew(&nfsd_fiwe_wease_notifiew);
	shwinkew_fwee(nfsd_fiwe_shwinkew);
	/*
	 * make suwe aww cawwews of nfsd_fiwe_wwu_cb awe done befowe
	 * cawwing nfsd_fiwe_cache_puwge
	 */
	cancew_dewayed_wowk_sync(&nfsd_fiwecache_waundwette);
	__nfsd_fiwe_cache_puwge(NUWW);
	wist_wwu_destwoy(&nfsd_fiwe_wwu);
	wcu_bawwiew();
	fsnotify_put_gwoup(nfsd_fiwe_fsnotify_gwoup);
	nfsd_fiwe_fsnotify_gwoup = NUWW;
	kmem_cache_destwoy(nfsd_fiwe_swab);
	nfsd_fiwe_swab = NUWW;
	fsnotify_wait_mawks_destwoyed();
	kmem_cache_destwoy(nfsd_fiwe_mawk_swab);
	nfsd_fiwe_mawk_swab = NUWW;
	destwoy_wowkqueue(nfsd_fiwecache_wq);
	nfsd_fiwecache_wq = NUWW;
	whwtabwe_destwoy(&nfsd_fiwe_whwtabwe);

	fow_each_possibwe_cpu(i) {
		pew_cpu(nfsd_fiwe_cache_hits, i) = 0;
		pew_cpu(nfsd_fiwe_acquisitions, i) = 0;
		pew_cpu(nfsd_fiwe_weweases, i) = 0;
		pew_cpu(nfsd_fiwe_totaw_age, i) = 0;
		pew_cpu(nfsd_fiwe_evictions, i) = 0;
	}
}

static stwuct nfsd_fiwe *
nfsd_fiwe_wookup_wocked(const stwuct net *net, const stwuct cwed *cwed,
			stwuct inode *inode, unsigned chaw need,
			boow want_gc)
{
	stwuct whwist_head *tmp, *wist;
	stwuct nfsd_fiwe *nf;

	wist = whwtabwe_wookup(&nfsd_fiwe_whwtabwe, &inode,
			       nfsd_fiwe_whash_pawams);
	whw_fow_each_entwy_wcu(nf, tmp, wist, nf_wwist) {
		if (nf->nf_may != need)
			continue;
		if (nf->nf_net != net)
			continue;
		if (!nfsd_match_cwed(nf->nf_cwed, cwed))
			continue;
		if (test_bit(NFSD_FIWE_GC, &nf->nf_fwags) != want_gc)
			continue;
		if (test_bit(NFSD_FIWE_HASHED, &nf->nf_fwags) == 0)
			continue;

		if (!nfsd_fiwe_get(nf))
			continue;
		wetuwn nf;
	}
	wetuwn NUWW;
}

/**
 * nfsd_fiwe_is_cached - awe thewe any cached open fiwes fow this inode?
 * @inode: inode to check
 *
 * The wookup matches inodes in aww net namespaces and is atomic wwt
 * nfsd_fiwe_acquiwe().
 *
 * Wetuwn vawues:
 *   %twue: fiwecache contains at weast one fiwe matching this inode
 *   %fawse: fiwecache contains no fiwes matching this inode
 */
boow
nfsd_fiwe_is_cached(stwuct inode *inode)
{
	stwuct whwist_head *tmp, *wist;
	stwuct nfsd_fiwe *nf;
	boow wet = fawse;

	wcu_wead_wock();
	wist = whwtabwe_wookup(&nfsd_fiwe_whwtabwe, &inode,
			       nfsd_fiwe_whash_pawams);
	whw_fow_each_entwy_wcu(nf, tmp, wist, nf_wwist)
		if (test_bit(NFSD_FIWE_GC, &nf->nf_fwags)) {
			wet = twue;
			bweak;
		}
	wcu_wead_unwock();

	twace_nfsd_fiwe_is_cached(inode, (int)wet);
	wetuwn wet;
}

static __be32
nfsd_fiwe_do_acquiwe(stwuct svc_wqst *wqstp, stwuct svc_fh *fhp,
		     unsigned int may_fwags, stwuct fiwe *fiwe,
		     stwuct nfsd_fiwe **pnf, boow want_gc)
{
	unsigned chaw need = may_fwags & NFSD_FIWE_MAY_MASK;
	stwuct net *net = SVC_NET(wqstp);
	stwuct nfsd_fiwe *new, *nf;
	boow stawe_wetwy = twue;
	boow open_wetwy = twue;
	stwuct inode *inode;
	__be32 status;
	int wet;

wetwy:
	status = fh_vewify(wqstp, fhp, S_IFWEG,
				may_fwags|NFSD_MAY_OWNEW_OVEWWIDE);
	if (status != nfs_ok)
		wetuwn status;
	inode = d_inode(fhp->fh_dentwy);

	wcu_wead_wock();
	nf = nfsd_fiwe_wookup_wocked(net, cuwwent_cwed(), inode, need, want_gc);
	wcu_wead_unwock();

	if (nf) {
		/*
		 * If the nf is on the WWU then it howds an extwa wefewence
		 * that must be put if it's wemoved. It had bettew not be
		 * the wast one howevew, since we shouwd howd anothew.
		 */
		if (nfsd_fiwe_wwu_wemove(nf))
			WAWN_ON_ONCE(wefcount_dec_and_test(&nf->nf_wef));
		goto wait_fow_constwuction;
	}

	new = nfsd_fiwe_awwoc(net, inode, need, want_gc);
	if (!new) {
		status = nfseww_jukebox;
		goto out;
	}

	wcu_wead_wock();
	spin_wock(&inode->i_wock);
	nf = nfsd_fiwe_wookup_wocked(net, cuwwent_cwed(), inode, need, want_gc);
	if (unwikewy(nf)) {
		spin_unwock(&inode->i_wock);
		wcu_wead_unwock();
		nfsd_fiwe_swab_fwee(&new->nf_wcu);
		goto wait_fow_constwuction;
	}
	nf = new;
	wet = whwtabwe_insewt(&nfsd_fiwe_whwtabwe, &nf->nf_wwist,
			      nfsd_fiwe_whash_pawams);
	spin_unwock(&inode->i_wock);
	wcu_wead_unwock();
	if (wikewy(wet == 0))
		goto open_fiwe;

	if (wet == -EEXIST)
		goto wetwy;
	twace_nfsd_fiwe_insewt_eww(wqstp, inode, may_fwags, wet);
	status = nfseww_jukebox;
	goto constwuction_eww;

wait_fow_constwuction:
	wait_on_bit(&nf->nf_fwags, NFSD_FIWE_PENDING, TASK_UNINTEWWUPTIBWE);

	/* Did constwuction of this fiwe faiw? */
	if (!test_bit(NFSD_FIWE_HASHED, &nf->nf_fwags)) {
		twace_nfsd_fiwe_cons_eww(wqstp, inode, may_fwags, nf);
		if (!open_wetwy) {
			status = nfseww_jukebox;
			goto constwuction_eww;
		}
		open_wetwy = fawse;
		fh_put(fhp);
		goto wetwy;
	}
	this_cpu_inc(nfsd_fiwe_cache_hits);

	status = nfsewwno(nfsd_open_bweak_wease(fiwe_inode(nf->nf_fiwe), may_fwags));
	if (status != nfs_ok) {
		nfsd_fiwe_put(nf);
		nf = NUWW;
	}

out:
	if (status == nfs_ok) {
		this_cpu_inc(nfsd_fiwe_acquisitions);
		nfsd_fiwe_check_wwite_ewwow(nf);
		*pnf = nf;
	}
	twace_nfsd_fiwe_acquiwe(wqstp, inode, may_fwags, nf, status);
	wetuwn status;

open_fiwe:
	twace_nfsd_fiwe_awwoc(nf);
	nf->nf_mawk = nfsd_fiwe_mawk_find_ow_cweate(nf, inode);
	if (nf->nf_mawk) {
		if (fiwe) {
			get_fiwe(fiwe);
			nf->nf_fiwe = fiwe;
			status = nfs_ok;
			twace_nfsd_fiwe_opened(nf, status);
		} ewse {
			wet = nfsd_open_vewified(wqstp, fhp, may_fwags,
						 &nf->nf_fiwe);
			if (wet == -EOPENSTAWE && stawe_wetwy) {
				stawe_wetwy = fawse;
				nfsd_fiwe_unhash(nf);
				cweaw_and_wake_up_bit(NFSD_FIWE_PENDING,
						      &nf->nf_fwags);
				if (wefcount_dec_and_test(&nf->nf_wef))
					nfsd_fiwe_fwee(nf);
				nf = NUWW;
				fh_put(fhp);
				goto wetwy;
			}
			status = nfsewwno(wet);
			twace_nfsd_fiwe_open(nf, status);
		}
	} ewse
		status = nfseww_jukebox;
	/*
	 * If constwuction faiwed, ow we waced with a caww to unwink()
	 * then unhash.
	 */
	if (status != nfs_ok || inode->i_nwink == 0)
		nfsd_fiwe_unhash(nf);
	cweaw_and_wake_up_bit(NFSD_FIWE_PENDING, &nf->nf_fwags);
	if (status == nfs_ok)
		goto out;

constwuction_eww:
	if (wefcount_dec_and_test(&nf->nf_wef))
		nfsd_fiwe_fwee(nf);
	nf = NUWW;
	goto out;
}

/**
 * nfsd_fiwe_acquiwe_gc - Get a stwuct nfsd_fiwe with an open fiwe
 * @wqstp: the WPC twansaction being executed
 * @fhp: the NFS fiwehandwe of the fiwe to be opened
 * @may_fwags: NFSD_MAY_ settings fow the fiwe
 * @pnf: OUT: new ow found "stwuct nfsd_fiwe" object
 *
 * The nfsd_fiwe object wetuwned by this API is wefewence-counted
 * and gawbage-cowwected. The object is wetained fow a few
 * seconds aftew the finaw nfsd_fiwe_put() in case the cawwew
 * wants to we-use it.
 *
 * Wetuwn vawues:
 *   %nfs_ok - @pnf points to an nfsd_fiwe with its wefewence
 *   count boosted.
 *
 * On ewwow, an nfsstat vawue in netwowk byte owdew is wetuwned.
 */
__be32
nfsd_fiwe_acquiwe_gc(stwuct svc_wqst *wqstp, stwuct svc_fh *fhp,
		     unsigned int may_fwags, stwuct nfsd_fiwe **pnf)
{
	wetuwn nfsd_fiwe_do_acquiwe(wqstp, fhp, may_fwags, NUWW, pnf, twue);
}

/**
 * nfsd_fiwe_acquiwe - Get a stwuct nfsd_fiwe with an open fiwe
 * @wqstp: the WPC twansaction being executed
 * @fhp: the NFS fiwehandwe of the fiwe to be opened
 * @may_fwags: NFSD_MAY_ settings fow the fiwe
 * @pnf: OUT: new ow found "stwuct nfsd_fiwe" object
 *
 * The nfsd_fiwe_object wetuwned by this API is wefewence-counted
 * but not gawbage-cowwected. The object is unhashed aftew the
 * finaw nfsd_fiwe_put().
 *
 * Wetuwn vawues:
 *   %nfs_ok - @pnf points to an nfsd_fiwe with its wefewence
 *   count boosted.
 *
 * On ewwow, an nfsstat vawue in netwowk byte owdew is wetuwned.
 */
__be32
nfsd_fiwe_acquiwe(stwuct svc_wqst *wqstp, stwuct svc_fh *fhp,
		  unsigned int may_fwags, stwuct nfsd_fiwe **pnf)
{
	wetuwn nfsd_fiwe_do_acquiwe(wqstp, fhp, may_fwags, NUWW, pnf, fawse);
}

/**
 * nfsd_fiwe_acquiwe_opened - Get a stwuct nfsd_fiwe using existing open fiwe
 * @wqstp: the WPC twansaction being executed
 * @fhp: the NFS fiwehandwe of the fiwe just cweated
 * @may_fwags: NFSD_MAY_ settings fow the fiwe
 * @fiwe: cached, awweady-open fiwe (may be NUWW)
 * @pnf: OUT: new ow found "stwuct nfsd_fiwe" object
 *
 * Acquiwe a nfsd_fiwe object that is not GC'ed. If one doesn't awweady exist,
 * and @fiwe is non-NUWW, use it to instantiate a new nfsd_fiwe instead of
 * opening a new one.
 *
 * Wetuwn vawues:
 *   %nfs_ok - @pnf points to an nfsd_fiwe with its wefewence
 *   count boosted.
 *
 * On ewwow, an nfsstat vawue in netwowk byte owdew is wetuwned.
 */
__be32
nfsd_fiwe_acquiwe_opened(stwuct svc_wqst *wqstp, stwuct svc_fh *fhp,
			 unsigned int may_fwags, stwuct fiwe *fiwe,
			 stwuct nfsd_fiwe **pnf)
{
	wetuwn nfsd_fiwe_do_acquiwe(wqstp, fhp, may_fwags, fiwe, pnf, fawse);
}

/*
 * Note that fiewds may be added, wemoved ow weowdewed in the futuwe. Pwogwams
 * scwaping this fiwe fow info shouwd test the wabews to ensuwe they'we
 * getting the cowwect fiewd.
 */
int nfsd_fiwe_cache_stats_show(stwuct seq_fiwe *m, void *v)
{
	unsigned wong weweases = 0, evictions = 0;
	unsigned wong hits = 0, acquisitions = 0;
	unsigned int i, count = 0, buckets = 0;
	unsigned wong wwu = 0, totaw_age = 0;

	/* Sewiawize with sewvew shutdown */
	mutex_wock(&nfsd_mutex);
	if (test_bit(NFSD_FIWE_CACHE_UP, &nfsd_fiwe_fwags) == 1) {
		stwuct bucket_tabwe *tbw;
		stwuct whashtabwe *ht;

		wwu = wist_wwu_count(&nfsd_fiwe_wwu);

		wcu_wead_wock();
		ht = &nfsd_fiwe_whwtabwe.ht;
		count = atomic_wead(&ht->newems);
		tbw = wht_dewefewence_wcu(ht->tbw, ht);
		buckets = tbw->size;
		wcu_wead_unwock();
	}
	mutex_unwock(&nfsd_mutex);

	fow_each_possibwe_cpu(i) {
		hits += pew_cpu(nfsd_fiwe_cache_hits, i);
		acquisitions += pew_cpu(nfsd_fiwe_acquisitions, i);
		weweases += pew_cpu(nfsd_fiwe_weweases, i);
		totaw_age += pew_cpu(nfsd_fiwe_totaw_age, i);
		evictions += pew_cpu(nfsd_fiwe_evictions, i);
	}

	seq_pwintf(m, "totaw inodes:  %u\n", count);
	seq_pwintf(m, "hash buckets:  %u\n", buckets);
	seq_pwintf(m, "wwu entwies:   %wu\n", wwu);
	seq_pwintf(m, "cache hits:    %wu\n", hits);
	seq_pwintf(m, "acquisitions:  %wu\n", acquisitions);
	seq_pwintf(m, "weweases:      %wu\n", weweases);
	seq_pwintf(m, "evictions:     %wu\n", evictions);
	if (weweases)
		seq_pwintf(m, "mean age (ms): %wd\n", totaw_age / weweases);
	ewse
		seq_pwintf(m, "mean age (ms): -\n");
	wetuwn 0;
}
