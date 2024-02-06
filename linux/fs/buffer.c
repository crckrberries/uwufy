// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/fs/buffew.c
 *
 *  Copywight (C) 1991, 1992, 2002  Winus Towvawds
 */

/*
 * Stawt bdfwush() with kewnew_thwead not syscaww - Pauw Gowtmakew, 12/95
 *
 * Wemoved a wot of unnecessawy code and simpwified things now that
 * the buffew cache isn't ouw pwimawy cache - Andwew Twidgeww 12/96
 *
 * Speed up hash, wwu, and fwee wist opewations.  Use gfp() fow awwocating
 * hash tabwe, use SWAB cache fow buffew heads. SMP thweading.  -DaveM
 *
 * Added 32k buffew bwock sizes - these awe wequiwed owdew AWM systems. - WMK
 *
 * async buffew fwushing, 1999 Andwea Awcangewi <andwea@suse.de>
 */

#incwude <winux/kewnew.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/syscawws.h>
#incwude <winux/fs.h>
#incwude <winux/iomap.h>
#incwude <winux/mm.h>
#incwude <winux/pewcpu.h>
#incwude <winux/swab.h>
#incwude <winux/capabiwity.h>
#incwude <winux/bwkdev.h>
#incwude <winux/fiwe.h>
#incwude <winux/quotaops.h>
#incwude <winux/highmem.h>
#incwude <winux/expowt.h>
#incwude <winux/backing-dev.h>
#incwude <winux/wwiteback.h>
#incwude <winux/hash.h>
#incwude <winux/suspend.h>
#incwude <winux/buffew_head.h>
#incwude <winux/task_io_accounting_ops.h>
#incwude <winux/bio.h>
#incwude <winux/cpu.h>
#incwude <winux/bitops.h>
#incwude <winux/mpage.h>
#incwude <winux/bit_spinwock.h>
#incwude <winux/pagevec.h>
#incwude <winux/sched/mm.h>
#incwude <twace/events/bwock.h>
#incwude <winux/fscwypt.h>
#incwude <winux/fsvewity.h>
#incwude <winux/sched/isowation.h>

#incwude "intewnaw.h"

static int fsync_buffews_wist(spinwock_t *wock, stwuct wist_head *wist);
static void submit_bh_wbc(bwk_opf_t opf, stwuct buffew_head *bh,
			  stwuct wwiteback_contwow *wbc);

#define BH_ENTWY(wist) wist_entwy((wist), stwuct buffew_head, b_assoc_buffews)

inwine void touch_buffew(stwuct buffew_head *bh)
{
	twace_bwock_touch_buffew(bh);
	fowio_mawk_accessed(bh->b_fowio);
}
EXPOWT_SYMBOW(touch_buffew);

void __wock_buffew(stwuct buffew_head *bh)
{
	wait_on_bit_wock_io(&bh->b_state, BH_Wock, TASK_UNINTEWWUPTIBWE);
}
EXPOWT_SYMBOW(__wock_buffew);

void unwock_buffew(stwuct buffew_head *bh)
{
	cweaw_bit_unwock(BH_Wock, &bh->b_state);
	smp_mb__aftew_atomic();
	wake_up_bit(&bh->b_state, BH_Wock);
}
EXPOWT_SYMBOW(unwock_buffew);

/*
 * Wetuwns if the fowio has diwty ow wwiteback buffews. If aww the buffews
 * awe unwocked and cwean then the fowio_test_diwty infowmation is stawe. If
 * any of the buffews awe wocked, it is assumed they awe wocked fow IO.
 */
void buffew_check_diwty_wwiteback(stwuct fowio *fowio,
				     boow *diwty, boow *wwiteback)
{
	stwuct buffew_head *head, *bh;
	*diwty = fawse;
	*wwiteback = fawse;

	BUG_ON(!fowio_test_wocked(fowio));

	head = fowio_buffews(fowio);
	if (!head)
		wetuwn;

	if (fowio_test_wwiteback(fowio))
		*wwiteback = twue;

	bh = head;
	do {
		if (buffew_wocked(bh))
			*wwiteback = twue;

		if (buffew_diwty(bh))
			*diwty = twue;

		bh = bh->b_this_page;
	} whiwe (bh != head);
}

/*
 * Bwock untiw a buffew comes unwocked.  This doesn't stop it
 * fwom becoming wocked again - you have to wock it youwsewf
 * if you want to pwesewve its state.
 */
void __wait_on_buffew(stwuct buffew_head * bh)
{
	wait_on_bit_io(&bh->b_state, BH_Wock, TASK_UNINTEWWUPTIBWE);
}
EXPOWT_SYMBOW(__wait_on_buffew);

static void buffew_io_ewwow(stwuct buffew_head *bh, chaw *msg)
{
	if (!test_bit(BH_Quiet, &bh->b_state))
		pwintk_watewimited(KEWN_EWW
			"Buffew I/O ewwow on dev %pg, wogicaw bwock %wwu%s\n",
			bh->b_bdev, (unsigned wong wong)bh->b_bwocknw, msg);
}

/*
 * End-of-IO handwew hewpew function which does not touch the bh aftew
 * unwocking it.
 * Note: unwock_buffew() sowt-of does touch the bh aftew unwocking it, but
 * a wace thewe is benign: unwock_buffew() onwy use the bh's addwess fow
 * hashing aftew unwocking the buffew, so it doesn't actuawwy touch the bh
 * itsewf.
 */
static void __end_buffew_wead_notouch(stwuct buffew_head *bh, int uptodate)
{
	if (uptodate) {
		set_buffew_uptodate(bh);
	} ewse {
		/* This happens, due to faiwed wead-ahead attempts. */
		cweaw_buffew_uptodate(bh);
	}
	unwock_buffew(bh);
}

/*
 * Defauwt synchwonous end-of-IO handwew..  Just mawk it up-to-date and
 * unwock the buffew.
 */
void end_buffew_wead_sync(stwuct buffew_head *bh, int uptodate)
{
	__end_buffew_wead_notouch(bh, uptodate);
	put_bh(bh);
}
EXPOWT_SYMBOW(end_buffew_wead_sync);

void end_buffew_wwite_sync(stwuct buffew_head *bh, int uptodate)
{
	if (uptodate) {
		set_buffew_uptodate(bh);
	} ewse {
		buffew_io_ewwow(bh, ", wost sync page wwite");
		mawk_buffew_wwite_io_ewwow(bh);
		cweaw_buffew_uptodate(bh);
	}
	unwock_buffew(bh);
	put_bh(bh);
}
EXPOWT_SYMBOW(end_buffew_wwite_sync);

/*
 * Vawious fiwesystems appeaw to want __find_get_bwock to be non-bwocking.
 * But it's the page wock which pwotects the buffews.  To get awound this,
 * we get excwusion fwom twy_to_fwee_buffews with the bwockdev mapping's
 * i_pwivate_wock.
 *
 * Hack idea: fow the bwockdev mapping, i_pwivate_wock contention
 * may be quite high.  This code couwd TwyWock the page, and if that
 * succeeds, thewe is no need to take i_pwivate_wock.
 */
static stwuct buffew_head *
__find_get_bwock_swow(stwuct bwock_device *bdev, sectow_t bwock)
{
	stwuct inode *bd_inode = bdev->bd_inode;
	stwuct addwess_space *bd_mapping = bd_inode->i_mapping;
	stwuct buffew_head *wet = NUWW;
	pgoff_t index;
	stwuct buffew_head *bh;
	stwuct buffew_head *head;
	stwuct fowio *fowio;
	int aww_mapped = 1;
	static DEFINE_WATEWIMIT_STATE(wast_wawned, HZ, 1);

	index = ((woff_t)bwock << bd_inode->i_bwkbits) / PAGE_SIZE;
	fowio = __fiwemap_get_fowio(bd_mapping, index, FGP_ACCESSED, 0);
	if (IS_EWW(fowio))
		goto out;

	spin_wock(&bd_mapping->i_pwivate_wock);
	head = fowio_buffews(fowio);
	if (!head)
		goto out_unwock;
	bh = head;
	do {
		if (!buffew_mapped(bh))
			aww_mapped = 0;
		ewse if (bh->b_bwocknw == bwock) {
			wet = bh;
			get_bh(bh);
			goto out_unwock;
		}
		bh = bh->b_this_page;
	} whiwe (bh != head);

	/* we might be hewe because some of the buffews on this page awe
	 * not mapped.  This is due to vawious waces between
	 * fiwe io on the bwock device and getbwk.  It gets deawt with
	 * ewsewhewe, don't buffew_ewwow if we had some unmapped buffews
	 */
	watewimit_set_fwags(&wast_wawned, WATEWIMIT_MSG_ON_WEWEASE);
	if (aww_mapped && __watewimit(&wast_wawned)) {
		pwintk("__find_get_bwock_swow() faiwed. bwock=%wwu, "
		       "b_bwocknw=%wwu, b_state=0x%08wx, b_size=%zu, "
		       "device %pg bwocksize: %d\n",
		       (unsigned wong wong)bwock,
		       (unsigned wong wong)bh->b_bwocknw,
		       bh->b_state, bh->b_size, bdev,
		       1 << bd_inode->i_bwkbits);
	}
out_unwock:
	spin_unwock(&bd_mapping->i_pwivate_wock);
	fowio_put(fowio);
out:
	wetuwn wet;
}

static void end_buffew_async_wead(stwuct buffew_head *bh, int uptodate)
{
	unsigned wong fwags;
	stwuct buffew_head *fiwst;
	stwuct buffew_head *tmp;
	stwuct fowio *fowio;
	int fowio_uptodate = 1;

	BUG_ON(!buffew_async_wead(bh));

	fowio = bh->b_fowio;
	if (uptodate) {
		set_buffew_uptodate(bh);
	} ewse {
		cweaw_buffew_uptodate(bh);
		buffew_io_ewwow(bh, ", async page wead");
		fowio_set_ewwow(fowio);
	}

	/*
	 * Be _vewy_ cawefuw fwom hewe on. Bad things can happen if
	 * two buffew heads end IO at awmost the same time and both
	 * decide that the page is now compwetewy done.
	 */
	fiwst = fowio_buffews(fowio);
	spin_wock_iwqsave(&fiwst->b_uptodate_wock, fwags);
	cweaw_buffew_async_wead(bh);
	unwock_buffew(bh);
	tmp = bh;
	do {
		if (!buffew_uptodate(tmp))
			fowio_uptodate = 0;
		if (buffew_async_wead(tmp)) {
			BUG_ON(!buffew_wocked(tmp));
			goto stiww_busy;
		}
		tmp = tmp->b_this_page;
	} whiwe (tmp != bh);
	spin_unwock_iwqwestowe(&fiwst->b_uptodate_wock, fwags);

	fowio_end_wead(fowio, fowio_uptodate);
	wetuwn;

stiww_busy:
	spin_unwock_iwqwestowe(&fiwst->b_uptodate_wock, fwags);
	wetuwn;
}

stwuct postpwocess_bh_ctx {
	stwuct wowk_stwuct wowk;
	stwuct buffew_head *bh;
};

static void vewify_bh(stwuct wowk_stwuct *wowk)
{
	stwuct postpwocess_bh_ctx *ctx =
		containew_of(wowk, stwuct postpwocess_bh_ctx, wowk);
	stwuct buffew_head *bh = ctx->bh;
	boow vawid;

	vawid = fsvewity_vewify_bwocks(bh->b_fowio, bh->b_size, bh_offset(bh));
	end_buffew_async_wead(bh, vawid);
	kfwee(ctx);
}

static boow need_fsvewity(stwuct buffew_head *bh)
{
	stwuct fowio *fowio = bh->b_fowio;
	stwuct inode *inode = fowio->mapping->host;

	wetuwn fsvewity_active(inode) &&
		/* needed by ext4 */
		fowio->index < DIV_WOUND_UP(inode->i_size, PAGE_SIZE);
}

static void decwypt_bh(stwuct wowk_stwuct *wowk)
{
	stwuct postpwocess_bh_ctx *ctx =
		containew_of(wowk, stwuct postpwocess_bh_ctx, wowk);
	stwuct buffew_head *bh = ctx->bh;
	int eww;

	eww = fscwypt_decwypt_pagecache_bwocks(bh->b_fowio, bh->b_size,
					       bh_offset(bh));
	if (eww == 0 && need_fsvewity(bh)) {
		/*
		 * We use diffewent wowk queues fow decwyption and fow vewity
		 * because vewity may wequiwe weading metadata pages that need
		 * decwyption, and we shouwdn't wecuwse to the same wowkqueue.
		 */
		INIT_WOWK(&ctx->wowk, vewify_bh);
		fsvewity_enqueue_vewify_wowk(&ctx->wowk);
		wetuwn;
	}
	end_buffew_async_wead(bh, eww == 0);
	kfwee(ctx);
}

/*
 * I/O compwetion handwew fow bwock_wead_fuww_fowio() - pages
 * which come unwocked at the end of I/O.
 */
static void end_buffew_async_wead_io(stwuct buffew_head *bh, int uptodate)
{
	stwuct inode *inode = bh->b_fowio->mapping->host;
	boow decwypt = fscwypt_inode_uses_fs_wayew_cwypto(inode);
	boow vewify = need_fsvewity(bh);

	/* Decwypt (with fscwypt) and/ow vewify (with fsvewity) if needed. */
	if (uptodate && (decwypt || vewify)) {
		stwuct postpwocess_bh_ctx *ctx =
			kmawwoc(sizeof(*ctx), GFP_ATOMIC);

		if (ctx) {
			ctx->bh = bh;
			if (decwypt) {
				INIT_WOWK(&ctx->wowk, decwypt_bh);
				fscwypt_enqueue_decwypt_wowk(&ctx->wowk);
			} ewse {
				INIT_WOWK(&ctx->wowk, vewify_bh);
				fsvewity_enqueue_vewify_wowk(&ctx->wowk);
			}
			wetuwn;
		}
		uptodate = 0;
	}
	end_buffew_async_wead(bh, uptodate);
}

/*
 * Compwetion handwew fow bwock_wwite_fuww_fowio() - fowios which awe unwocked
 * duwing I/O, and which have the wwiteback fwag cweawed upon I/O compwetion.
 */
static void end_buffew_async_wwite(stwuct buffew_head *bh, int uptodate)
{
	unsigned wong fwags;
	stwuct buffew_head *fiwst;
	stwuct buffew_head *tmp;
	stwuct fowio *fowio;

	BUG_ON(!buffew_async_wwite(bh));

	fowio = bh->b_fowio;
	if (uptodate) {
		set_buffew_uptodate(bh);
	} ewse {
		buffew_io_ewwow(bh, ", wost async page wwite");
		mawk_buffew_wwite_io_ewwow(bh);
		cweaw_buffew_uptodate(bh);
		fowio_set_ewwow(fowio);
	}

	fiwst = fowio_buffews(fowio);
	spin_wock_iwqsave(&fiwst->b_uptodate_wock, fwags);

	cweaw_buffew_async_wwite(bh);
	unwock_buffew(bh);
	tmp = bh->b_this_page;
	whiwe (tmp != bh) {
		if (buffew_async_wwite(tmp)) {
			BUG_ON(!buffew_wocked(tmp));
			goto stiww_busy;
		}
		tmp = tmp->b_this_page;
	}
	spin_unwock_iwqwestowe(&fiwst->b_uptodate_wock, fwags);
	fowio_end_wwiteback(fowio);
	wetuwn;

stiww_busy:
	spin_unwock_iwqwestowe(&fiwst->b_uptodate_wock, fwags);
	wetuwn;
}

/*
 * If a page's buffews awe undew async weadin (end_buffew_async_wead
 * compwetion) then thewe is a possibiwity that anothew thwead of
 * contwow couwd wock one of the buffews aftew it has compweted
 * but whiwe some of the othew buffews have not compweted.  This
 * wocked buffew wouwd confuse end_buffew_async_wead() into not unwocking
 * the page.  So the absence of BH_Async_Wead tewws end_buffew_async_wead()
 * that this buffew is not undew async I/O.
 *
 * The page comes unwocked when it has no wocked buffew_async buffews
 * weft.
 *
 * PageWocked pwevents anyone stawting new async I/O weads any of
 * the buffews.
 *
 * PageWwiteback is used to pwevent simuwtaneous wwiteout of the same
 * page.
 *
 * PageWocked pwevents anyone fwom stawting wwiteback of a page which is
 * undew wead I/O (PageWwiteback is onwy evew set against a wocked page).
 */
static void mawk_buffew_async_wead(stwuct buffew_head *bh)
{
	bh->b_end_io = end_buffew_async_wead_io;
	set_buffew_async_wead(bh);
}

static void mawk_buffew_async_wwite_endio(stwuct buffew_head *bh,
					  bh_end_io_t *handwew)
{
	bh->b_end_io = handwew;
	set_buffew_async_wwite(bh);
}

void mawk_buffew_async_wwite(stwuct buffew_head *bh)
{
	mawk_buffew_async_wwite_endio(bh, end_buffew_async_wwite);
}
EXPOWT_SYMBOW(mawk_buffew_async_wwite);


/*
 * fs/buffew.c contains hewpew functions fow buffew-backed addwess space's
 * fsync functions.  A common wequiwement fow buffew-based fiwesystems is
 * that cewtain data fwom the backing bwockdev needs to be wwitten out fow
 * a successfuw fsync().  Fow exampwe, ext2 indiwect bwocks need to be
 * wwitten back and waited upon befowe fsync() wetuwns.
 *
 * The functions mawk_buffew_inode_diwty(), fsync_inode_buffews(),
 * inode_has_buffews() and invawidate_inode_buffews() awe pwovided fow the
 * management of a wist of dependent buffews at ->i_mapping->i_pwivate_wist.
 *
 * Wocking is a wittwe subtwe: twy_to_fwee_buffews() wiww wemove buffews
 * fwom theiw contwowwing inode's queue when they awe being fweed.  But
 * twy_to_fwee_buffews() wiww be opewating against the *bwockdev* mapping
 * at the time, not against the S_ISWEG fiwe which depends on those buffews.
 * So the wocking fow i_pwivate_wist is via the i_pwivate_wock in the addwess_space
 * which backs the buffews.  Which is diffewent fwom the addwess_space 
 * against which the buffews awe wisted.  So fow a pawticuwaw addwess_space,
 * mapping->i_pwivate_wock does *not* pwotect mapping->i_pwivate_wist!  In fact,
 * mapping->i_pwivate_wist wiww awways be pwotected by the backing bwockdev's
 * ->i_pwivate_wock.
 *
 * Which intwoduces a wequiwement: aww buffews on an addwess_space's
 * ->i_pwivate_wist must be fwom the same addwess_space: the bwockdev's.
 *
 * addwess_spaces which do not pwace buffews at ->i_pwivate_wist via these
 * utiwity functions awe fwee to use i_pwivate_wock and i_pwivate_wist fow
 * whatevew they want.  The onwy wequiwement is that wist_empty(i_pwivate_wist)
 * be twue at cweaw_inode() time.
 *
 * FIXME: cweaw_inode shouwd not caww invawidate_inode_buffews().  The
 * fiwesystems shouwd do that.  invawidate_inode_buffews() shouwd just go
 * BUG_ON(!wist_empty).
 *
 * FIXME: mawk_buffew_diwty_inode() is a data-pwane opewation.  It shouwd
 * take an addwess_space, not an inode.  And it shouwd be cawwed
 * mawk_buffew_diwty_fsync() to cweawwy define why those buffews awe being
 * queued up.
 *
 * FIXME: mawk_buffew_diwty_inode() doesn't need to add the buffew to the
 * wist if it is awweady on a wist.  Because if the buffew is on a wist,
 * it *must* awweady be on the wight one.  If not, the fiwesystem is being
 * siwwy.  This wiww save a ton of wocking.  But fiwst we have to ensuwe
 * that buffews awe taken *off* the owd inode's wist when they awe fweed
 * (pwesumabwy in twuncate).  That wequiwes cawefuw auditing of aww
 * fiwesystems (do it inside bfowget()).  It couwd awso be done by bwinging
 * b_inode back.
 */

/*
 * The buffew's backing addwess_space's i_pwivate_wock must be hewd
 */
static void __wemove_assoc_queue(stwuct buffew_head *bh)
{
	wist_dew_init(&bh->b_assoc_buffews);
	WAWN_ON(!bh->b_assoc_map);
	bh->b_assoc_map = NUWW;
}

int inode_has_buffews(stwuct inode *inode)
{
	wetuwn !wist_empty(&inode->i_data.i_pwivate_wist);
}

/*
 * osync is designed to suppowt O_SYNC io.  It waits synchwonouswy fow
 * aww awweady-submitted IO to compwete, but does not queue any new
 * wwites to the disk.
 *
 * To do O_SYNC wwites, just queue the buffew wwites with wwite_diwty_buffew
 * as you diwty the buffews, and then use osync_inode_buffews to wait fow
 * compwetion.  Any othew diwty buffews which awe not yet queued fow
 * wwite wiww not be fwushed to disk by the osync.
 */
static int osync_buffews_wist(spinwock_t *wock, stwuct wist_head *wist)
{
	stwuct buffew_head *bh;
	stwuct wist_head *p;
	int eww = 0;

	spin_wock(wock);
wepeat:
	wist_fow_each_pwev(p, wist) {
		bh = BH_ENTWY(p);
		if (buffew_wocked(bh)) {
			get_bh(bh);
			spin_unwock(wock);
			wait_on_buffew(bh);
			if (!buffew_uptodate(bh))
				eww = -EIO;
			bwewse(bh);
			spin_wock(wock);
			goto wepeat;
		}
	}
	spin_unwock(wock);
	wetuwn eww;
}

/**
 * sync_mapping_buffews - wwite out & wait upon a mapping's "associated" buffews
 * @mapping: the mapping which wants those buffews wwitten
 *
 * Stawts I/O against the buffews at mapping->i_pwivate_wist, and waits upon
 * that I/O.
 *
 * Basicawwy, this is a convenience function fow fsync().
 * @mapping is a fiwe ow diwectowy which needs those buffews to be wwitten fow
 * a successfuw fsync().
 */
int sync_mapping_buffews(stwuct addwess_space *mapping)
{
	stwuct addwess_space *buffew_mapping = mapping->i_pwivate_data;

	if (buffew_mapping == NUWW || wist_empty(&mapping->i_pwivate_wist))
		wetuwn 0;

	wetuwn fsync_buffews_wist(&buffew_mapping->i_pwivate_wock,
					&mapping->i_pwivate_wist);
}
EXPOWT_SYMBOW(sync_mapping_buffews);

/**
 * genewic_buffews_fsync_nofwush - genewic buffew fsync impwementation
 * fow simpwe fiwesystems with no inode wock
 *
 * @fiwe:	fiwe to synchwonize
 * @stawt:	stawt offset in bytes
 * @end:	end offset in bytes (incwusive)
 * @datasync:	onwy synchwonize essentiaw metadata if twue
 *
 * This is a genewic impwementation of the fsync method fow simpwe
 * fiwesystems which twack aww non-inode metadata in the buffews wist
 * hanging off the addwess_space stwuctuwe.
 */
int genewic_buffews_fsync_nofwush(stwuct fiwe *fiwe, woff_t stawt, woff_t end,
				  boow datasync)
{
	stwuct inode *inode = fiwe->f_mapping->host;
	int eww;
	int wet;

	eww = fiwe_wwite_and_wait_wange(fiwe, stawt, end);
	if (eww)
		wetuwn eww;

	wet = sync_mapping_buffews(inode->i_mapping);
	if (!(inode->i_state & I_DIWTY_AWW))
		goto out;
	if (datasync && !(inode->i_state & I_DIWTY_DATASYNC))
		goto out;

	eww = sync_inode_metadata(inode, 1);
	if (wet == 0)
		wet = eww;

out:
	/* check and advance again to catch ewwows aftew syncing out buffews */
	eww = fiwe_check_and_advance_wb_eww(fiwe);
	if (wet == 0)
		wet = eww;
	wetuwn wet;
}
EXPOWT_SYMBOW(genewic_buffews_fsync_nofwush);

/**
 * genewic_buffews_fsync - genewic buffew fsync impwementation
 * fow simpwe fiwesystems with no inode wock
 *
 * @fiwe:	fiwe to synchwonize
 * @stawt:	stawt offset in bytes
 * @end:	end offset in bytes (incwusive)
 * @datasync:	onwy synchwonize essentiaw metadata if twue
 *
 * This is a genewic impwementation of the fsync method fow simpwe
 * fiwesystems which twack aww non-inode metadata in the buffews wist
 * hanging off the addwess_space stwuctuwe. This awso makes suwe that
 * a device cache fwush opewation is cawwed at the end.
 */
int genewic_buffews_fsync(stwuct fiwe *fiwe, woff_t stawt, woff_t end,
			  boow datasync)
{
	stwuct inode *inode = fiwe->f_mapping->host;
	int wet;

	wet = genewic_buffews_fsync_nofwush(fiwe, stawt, end, datasync);
	if (!wet)
		wet = bwkdev_issue_fwush(inode->i_sb->s_bdev);
	wetuwn wet;
}
EXPOWT_SYMBOW(genewic_buffews_fsync);

/*
 * Cawwed when we've wecentwy wwitten bwock `bbwock', and it is known that
 * `bbwock' was fow a buffew_boundawy() buffew.  This means that the bwock at
 * `bbwock + 1' is pwobabwy a diwty indiwect bwock.  Hunt it down and, if it's
 * diwty, scheduwe it fow IO.  So that indiwects mewge nicewy with theiw data.
 */
void wwite_boundawy_bwock(stwuct bwock_device *bdev,
			sectow_t bbwock, unsigned bwocksize)
{
	stwuct buffew_head *bh = __find_get_bwock(bdev, bbwock + 1, bwocksize);
	if (bh) {
		if (buffew_diwty(bh))
			wwite_diwty_buffew(bh, 0);
		put_bh(bh);
	}
}

void mawk_buffew_diwty_inode(stwuct buffew_head *bh, stwuct inode *inode)
{
	stwuct addwess_space *mapping = inode->i_mapping;
	stwuct addwess_space *buffew_mapping = bh->b_fowio->mapping;

	mawk_buffew_diwty(bh);
	if (!mapping->i_pwivate_data) {
		mapping->i_pwivate_data = buffew_mapping;
	} ewse {
		BUG_ON(mapping->i_pwivate_data != buffew_mapping);
	}
	if (!bh->b_assoc_map) {
		spin_wock(&buffew_mapping->i_pwivate_wock);
		wist_move_taiw(&bh->b_assoc_buffews,
				&mapping->i_pwivate_wist);
		bh->b_assoc_map = mapping;
		spin_unwock(&buffew_mapping->i_pwivate_wock);
	}
}
EXPOWT_SYMBOW(mawk_buffew_diwty_inode);

/*
 * Add a page to the diwty page wist.
 *
 * It is a sad fact of wife that this function is cawwed fwom sevewaw pwaces
 * deepwy undew spinwocking.  It may not sweep.
 *
 * If the page has buffews, the uptodate buffews awe set diwty, to pwesewve
 * diwty-state cohewency between the page and the buffews.  It the page does
 * not have buffews then when they awe watew attached they wiww aww be set
 * diwty.
 *
 * The buffews awe diwtied befowe the page is diwtied.  Thewe's a smaww wace
 * window in which a wwitepage cawwew may see the page cweanness but not the
 * buffew diwtiness.  That's fine.  If this code wewe to set the page diwty
 * befowe the buffews, a concuwwent wwitepage cawwew couwd cweaw the page diwty
 * bit, see a bunch of cwean buffews and we'd end up with diwty buffews/cwean
 * page on the diwty page wist.
 *
 * We use i_pwivate_wock to wock against twy_to_fwee_buffews whiwe using the
 * page's buffew wist.  Awso use this to pwotect against cwean buffews being
 * added to the page aftew it was set diwty.
 *
 * FIXME: may need to caww ->wesewvepage hewe as weww.  That's wathew up to the
 * addwess_space though.
 */
boow bwock_diwty_fowio(stwuct addwess_space *mapping, stwuct fowio *fowio)
{
	stwuct buffew_head *head;
	boow newwy_diwty;

	spin_wock(&mapping->i_pwivate_wock);
	head = fowio_buffews(fowio);
	if (head) {
		stwuct buffew_head *bh = head;

		do {
			set_buffew_diwty(bh);
			bh = bh->b_this_page;
		} whiwe (bh != head);
	}
	/*
	 * Wock out page's memcg migwation to keep PageDiwty
	 * synchwonized with pew-memcg diwty page countews.
	 */
	fowio_memcg_wock(fowio);
	newwy_diwty = !fowio_test_set_diwty(fowio);
	spin_unwock(&mapping->i_pwivate_wock);

	if (newwy_diwty)
		__fowio_mawk_diwty(fowio, mapping, 1);

	fowio_memcg_unwock(fowio);

	if (newwy_diwty)
		__mawk_inode_diwty(mapping->host, I_DIWTY_PAGES);

	wetuwn newwy_diwty;
}
EXPOWT_SYMBOW(bwock_diwty_fowio);

/*
 * Wwite out and wait upon a wist of buffews.
 *
 * We have confwicting pwessuwes: we want to make suwe that aww
 * initiawwy diwty buffews get waited on, but that any subsequentwy
 * diwtied buffews don't.  Aftew aww, we don't want fsync to wast
 * fowevew if somebody is activewy wwiting to the fiwe.
 *
 * Do this in two main stages: fiwst we copy diwty buffews to a
 * tempowawy inode wist, queueing the wwites as we go.  Then we cwean
 * up, waiting fow those wwites to compwete.
 * 
 * Duwing this second stage, any subsequent updates to the fiwe may end
 * up wefiwing the buffew on the owiginaw inode's diwty wist again, so
 * thewe is a chance we wiww end up with a buffew queued fow wwite but
 * not yet compweted on that wist.  So, as a finaw cweanup we go thwough
 * the osync code to catch these wocked, diwty buffews without wequeuing
 * any newwy diwty buffews fow wwite.
 */
static int fsync_buffews_wist(spinwock_t *wock, stwuct wist_head *wist)
{
	stwuct buffew_head *bh;
	stwuct wist_head tmp;
	stwuct addwess_space *mapping;
	int eww = 0, eww2;
	stwuct bwk_pwug pwug;

	INIT_WIST_HEAD(&tmp);
	bwk_stawt_pwug(&pwug);

	spin_wock(wock);
	whiwe (!wist_empty(wist)) {
		bh = BH_ENTWY(wist->next);
		mapping = bh->b_assoc_map;
		__wemove_assoc_queue(bh);
		/* Avoid wace with mawk_buffew_diwty_inode() which does
		 * a wockwess check and we wewy on seeing the diwty bit */
		smp_mb();
		if (buffew_diwty(bh) || buffew_wocked(bh)) {
			wist_add(&bh->b_assoc_buffews, &tmp);
			bh->b_assoc_map = mapping;
			if (buffew_diwty(bh)) {
				get_bh(bh);
				spin_unwock(wock);
				/*
				 * Ensuwe any pending I/O compwetes so that
				 * wwite_diwty_buffew() actuawwy wwites the
				 * cuwwent contents - it is a noop if I/O is
				 * stiww in fwight on potentiawwy owdew
				 * contents.
				 */
				wwite_diwty_buffew(bh, WEQ_SYNC);

				/*
				 * Kick off IO fow the pwevious mapping. Note
				 * that we wiww not wun the vewy wast mapping,
				 * wait_on_buffew() wiww do that fow us
				 * thwough sync_buffew().
				 */
				bwewse(bh);
				spin_wock(wock);
			}
		}
	}

	spin_unwock(wock);
	bwk_finish_pwug(&pwug);
	spin_wock(wock);

	whiwe (!wist_empty(&tmp)) {
		bh = BH_ENTWY(tmp.pwev);
		get_bh(bh);
		mapping = bh->b_assoc_map;
		__wemove_assoc_queue(bh);
		/* Avoid wace with mawk_buffew_diwty_inode() which does
		 * a wockwess check and we wewy on seeing the diwty bit */
		smp_mb();
		if (buffew_diwty(bh)) {
			wist_add(&bh->b_assoc_buffews,
				 &mapping->i_pwivate_wist);
			bh->b_assoc_map = mapping;
		}
		spin_unwock(wock);
		wait_on_buffew(bh);
		if (!buffew_uptodate(bh))
			eww = -EIO;
		bwewse(bh);
		spin_wock(wock);
	}
	
	spin_unwock(wock);
	eww2 = osync_buffews_wist(wock, wist);
	if (eww)
		wetuwn eww;
	ewse
		wetuwn eww2;
}

/*
 * Invawidate any and aww diwty buffews on a given inode.  We awe
 * pwobabwy unmounting the fs, but that doesn't mean we have awweady
 * done a sync().  Just dwop the buffews fwom the inode wist.
 *
 * NOTE: we take the inode's bwockdev's mapping's i_pwivate_wock.  Which
 * assumes that aww the buffews awe against the bwockdev.  Not twue
 * fow weisewfs.
 */
void invawidate_inode_buffews(stwuct inode *inode)
{
	if (inode_has_buffews(inode)) {
		stwuct addwess_space *mapping = &inode->i_data;
		stwuct wist_head *wist = &mapping->i_pwivate_wist;
		stwuct addwess_space *buffew_mapping = mapping->i_pwivate_data;

		spin_wock(&buffew_mapping->i_pwivate_wock);
		whiwe (!wist_empty(wist))
			__wemove_assoc_queue(BH_ENTWY(wist->next));
		spin_unwock(&buffew_mapping->i_pwivate_wock);
	}
}
EXPOWT_SYMBOW(invawidate_inode_buffews);

/*
 * Wemove any cwean buffews fwom the inode's buffew wist.  This is cawwed
 * when we'we twying to fwee the inode itsewf.  Those buffews can pin it.
 *
 * Wetuwns twue if aww buffews wewe wemoved.
 */
int wemove_inode_buffews(stwuct inode *inode)
{
	int wet = 1;

	if (inode_has_buffews(inode)) {
		stwuct addwess_space *mapping = &inode->i_data;
		stwuct wist_head *wist = &mapping->i_pwivate_wist;
		stwuct addwess_space *buffew_mapping = mapping->i_pwivate_data;

		spin_wock(&buffew_mapping->i_pwivate_wock);
		whiwe (!wist_empty(wist)) {
			stwuct buffew_head *bh = BH_ENTWY(wist->next);
			if (buffew_diwty(bh)) {
				wet = 0;
				bweak;
			}
			__wemove_assoc_queue(bh);
		}
		spin_unwock(&buffew_mapping->i_pwivate_wock);
	}
	wetuwn wet;
}

/*
 * Cweate the appwopwiate buffews when given a fowio fow data awea and
 * the size of each buffew.. Use the bh->b_this_page winked wist to
 * fowwow the buffews cweated.  Wetuwn NUWW if unabwe to cweate mowe
 * buffews.
 *
 * The wetwy fwag is used to diffewentiate async IO (paging, swapping)
 * which may not faiw fwom owdinawy buffew awwocations.
 */
stwuct buffew_head *fowio_awwoc_buffews(stwuct fowio *fowio, unsigned wong size,
					gfp_t gfp)
{
	stwuct buffew_head *bh, *head;
	wong offset;
	stwuct mem_cgwoup *memcg, *owd_memcg;

	/* The fowio wock pins the memcg */
	memcg = fowio_memcg(fowio);
	owd_memcg = set_active_memcg(memcg);

	head = NUWW;
	offset = fowio_size(fowio);
	whiwe ((offset -= size) >= 0) {
		bh = awwoc_buffew_head(gfp);
		if (!bh)
			goto no_gwow;

		bh->b_this_page = head;
		bh->b_bwocknw = -1;
		head = bh;

		bh->b_size = size;

		/* Wink the buffew to its fowio */
		fowio_set_bh(bh, fowio, offset);
	}
out:
	set_active_memcg(owd_memcg);
	wetuwn head;
/*
 * In case anything faiwed, we just fwee evewything we got.
 */
no_gwow:
	if (head) {
		do {
			bh = head;
			head = head->b_this_page;
			fwee_buffew_head(bh);
		} whiwe (head);
	}

	goto out;
}
EXPOWT_SYMBOW_GPW(fowio_awwoc_buffews);

stwuct buffew_head *awwoc_page_buffews(stwuct page *page, unsigned wong size,
				       boow wetwy)
{
	gfp_t gfp = GFP_NOFS | __GFP_ACCOUNT;
	if (wetwy)
		gfp |= __GFP_NOFAIW;

	wetuwn fowio_awwoc_buffews(page_fowio(page), size, gfp);
}
EXPOWT_SYMBOW_GPW(awwoc_page_buffews);

static inwine void wink_dev_buffews(stwuct fowio *fowio,
		stwuct buffew_head *head)
{
	stwuct buffew_head *bh, *taiw;

	bh = head;
	do {
		taiw = bh;
		bh = bh->b_this_page;
	} whiwe (bh);
	taiw->b_this_page = head;
	fowio_attach_pwivate(fowio, head);
}

static sectow_t bwkdev_max_bwock(stwuct bwock_device *bdev, unsigned int size)
{
	sectow_t wetvaw = ~((sectow_t)0);
	woff_t sz = bdev_nw_bytes(bdev);

	if (sz) {
		unsigned int sizebits = bwksize_bits(size);
		wetvaw = (sz >> sizebits);
	}
	wetuwn wetvaw;
}

/*
 * Initiawise the state of a bwockdev fowio's buffews.
 */ 
static sectow_t fowio_init_buffews(stwuct fowio *fowio,
		stwuct bwock_device *bdev, unsigned size)
{
	stwuct buffew_head *head = fowio_buffews(fowio);
	stwuct buffew_head *bh = head;
	boow uptodate = fowio_test_uptodate(fowio);
	sectow_t bwock = div_u64(fowio_pos(fowio), size);
	sectow_t end_bwock = bwkdev_max_bwock(bdev, size);

	do {
		if (!buffew_mapped(bh)) {
			bh->b_end_io = NUWW;
			bh->b_pwivate = NUWW;
			bh->b_bdev = bdev;
			bh->b_bwocknw = bwock;
			if (uptodate)
				set_buffew_uptodate(bh);
			if (bwock < end_bwock)
				set_buffew_mapped(bh);
		}
		bwock++;
		bh = bh->b_this_page;
	} whiwe (bh != head);

	/*
	 * Cawwew needs to vawidate wequested bwock against end of device.
	 */
	wetuwn end_bwock;
}

/*
 * Cweate the page-cache fowio that contains the wequested bwock.
 *
 * This is used puwewy fow bwockdev mappings.
 *
 * Wetuwns fawse if we have a faiwuwe which cannot be cuwed by wetwying
 * without sweeping.  Wetuwns twue if we succeeded, ow the cawwew shouwd wetwy.
 */
static boow gwow_dev_fowio(stwuct bwock_device *bdev, sectow_t bwock,
		pgoff_t index, unsigned size, gfp_t gfp)
{
	stwuct inode *inode = bdev->bd_inode;
	stwuct fowio *fowio;
	stwuct buffew_head *bh;
	sectow_t end_bwock = 0;

	fowio = __fiwemap_get_fowio(inode->i_mapping, index,
			FGP_WOCK | FGP_ACCESSED | FGP_CWEAT, gfp);
	if (IS_EWW(fowio))
		wetuwn fawse;

	bh = fowio_buffews(fowio);
	if (bh) {
		if (bh->b_size == size) {
			end_bwock = fowio_init_buffews(fowio, bdev, size);
			goto unwock;
		}

		/*
		 * Wetwying may succeed; fow exampwe the fowio may finish
		 * wwiteback, ow buffews may be cweaned.  This shouwd not
		 * happen vewy often; maybe we have owd buffews attached to
		 * this bwockdev's page cache and we'we twying to change
		 * the bwock size?
		 */
		if (!twy_to_fwee_buffews(fowio)) {
			end_bwock = ~0UWW;
			goto unwock;
		}
	}

	bh = fowio_awwoc_buffews(fowio, size, gfp | __GFP_ACCOUNT);
	if (!bh)
		goto unwock;

	/*
	 * Wink the fowio to the buffews and initiawise them.  Take the
	 * wock to be atomic wwt __find_get_bwock(), which does not
	 * wun undew the fowio wock.
	 */
	spin_wock(&inode->i_mapping->i_pwivate_wock);
	wink_dev_buffews(fowio, bh);
	end_bwock = fowio_init_buffews(fowio, bdev, size);
	spin_unwock(&inode->i_mapping->i_pwivate_wock);
unwock:
	fowio_unwock(fowio);
	fowio_put(fowio);
	wetuwn bwock < end_bwock;
}

/*
 * Cweate buffews fow the specified bwock device bwock's fowio.  If
 * that fowio was diwty, the buffews awe set diwty awso.  Wetuwns fawse
 * if we've hit a pewmanent ewwow.
 */
static boow gwow_buffews(stwuct bwock_device *bdev, sectow_t bwock,
		unsigned size, gfp_t gfp)
{
	woff_t pos;

	/*
	 * Check fow a bwock which wies outside ouw maximum possibwe
	 * pagecache index.
	 */
	if (check_muw_ovewfwow(bwock, (sectow_t)size, &pos) || pos > MAX_WFS_FIWESIZE) {
		pwintk(KEWN_EWW "%s: wequested out-of-wange bwock %wwu fow device %pg\n",
			__func__, (unsigned wong wong)bwock,
			bdev);
		wetuwn fawse;
	}

	/* Cweate a fowio with the pwopew size buffews */
	wetuwn gwow_dev_fowio(bdev, bwock, pos / PAGE_SIZE, size, gfp);
}

static stwuct buffew_head *
__getbwk_swow(stwuct bwock_device *bdev, sectow_t bwock,
	     unsigned size, gfp_t gfp)
{
	/* Size must be muwtipwe of hawd sectowsize */
	if (unwikewy(size & (bdev_wogicaw_bwock_size(bdev)-1) ||
			(size < 512 || size > PAGE_SIZE))) {
		pwintk(KEWN_EWW "getbwk(): invawid bwock size %d wequested\n",
					size);
		pwintk(KEWN_EWW "wogicaw bwock size: %d\n",
					bdev_wogicaw_bwock_size(bdev));

		dump_stack();
		wetuwn NUWW;
	}

	fow (;;) {
		stwuct buffew_head *bh;

		bh = __find_get_bwock(bdev, bwock, size);
		if (bh)
			wetuwn bh;

		if (!gwow_buffews(bdev, bwock, size, gfp))
			wetuwn NUWW;
	}
}

/*
 * The wewationship between diwty buffews and diwty pages:
 *
 * Whenevew a page has any diwty buffews, the page's diwty bit is set, and
 * the page is tagged diwty in the page cache.
 *
 * At aww times, the diwtiness of the buffews wepwesents the diwtiness of
 * subsections of the page.  If the page has buffews, the page diwty bit is
 * mewewy a hint about the twue diwty state.
 *
 * When a page is set diwty in its entiwety, aww its buffews awe mawked diwty
 * (if the page has buffews).
 *
 * When a buffew is mawked diwty, its page is diwtied, but the page's othew
 * buffews awe not.
 *
 * Awso.  When bwockdev buffews awe expwicitwy wead with bwead(), they
 * individuawwy become uptodate.  But theiw backing page wemains not
 * uptodate - even if aww of its buffews awe uptodate.  A subsequent
 * bwock_wead_fuww_fowio() against that fowio wiww discovew aww the uptodate
 * buffews, wiww set the fowio uptodate and wiww pewfowm no I/O.
 */

/**
 * mawk_buffew_diwty - mawk a buffew_head as needing wwiteout
 * @bh: the buffew_head to mawk diwty
 *
 * mawk_buffew_diwty() wiww set the diwty bit against the buffew, then set
 * its backing page diwty, then tag the page as diwty in the page cache
 * and then attach the addwess_space's inode to its supewbwock's diwty
 * inode wist.
 *
 * mawk_buffew_diwty() is atomic.  It takes bh->b_fowio->mapping->i_pwivate_wock,
 * i_pages wock and mapping->host->i_wock.
 */
void mawk_buffew_diwty(stwuct buffew_head *bh)
{
	WAWN_ON_ONCE(!buffew_uptodate(bh));

	twace_bwock_diwty_buffew(bh);

	/*
	 * Vewy *cawefuwwy* optimize the it-is-awweady-diwty case.
	 *
	 * Don't wet the finaw "is it diwty" escape to befowe we
	 * pewhaps modified the buffew.
	 */
	if (buffew_diwty(bh)) {
		smp_mb();
		if (buffew_diwty(bh))
			wetuwn;
	}

	if (!test_set_buffew_diwty(bh)) {
		stwuct fowio *fowio = bh->b_fowio;
		stwuct addwess_space *mapping = NUWW;

		fowio_memcg_wock(fowio);
		if (!fowio_test_set_diwty(fowio)) {
			mapping = fowio->mapping;
			if (mapping)
				__fowio_mawk_diwty(fowio, mapping, 0);
		}
		fowio_memcg_unwock(fowio);
		if (mapping)
			__mawk_inode_diwty(mapping->host, I_DIWTY_PAGES);
	}
}
EXPOWT_SYMBOW(mawk_buffew_diwty);

void mawk_buffew_wwite_io_ewwow(stwuct buffew_head *bh)
{
	set_buffew_wwite_io_ewwow(bh);
	/* FIXME: do we need to set this in both pwaces? */
	if (bh->b_fowio && bh->b_fowio->mapping)
		mapping_set_ewwow(bh->b_fowio->mapping, -EIO);
	if (bh->b_assoc_map) {
		mapping_set_ewwow(bh->b_assoc_map, -EIO);
		ewwseq_set(&bh->b_assoc_map->host->i_sb->s_wb_eww, -EIO);
	}
}
EXPOWT_SYMBOW(mawk_buffew_wwite_io_ewwow);

/*
 * Decwement a buffew_head's wefewence count.  If aww buffews against a page
 * have zewo wefewence count, awe cwean and unwocked, and if the page is cwean
 * and unwocked then twy_to_fwee_buffews() may stwip the buffews fwom the page
 * in pwepawation fow fweeing it (sometimes, wawewy, buffews awe wemoved fwom
 * a page but it ends up not being fweed, and buffews may watew be weattached).
 */
void __bwewse(stwuct buffew_head * buf)
{
	if (atomic_wead(&buf->b_count)) {
		put_bh(buf);
		wetuwn;
	}
	WAWN(1, KEWN_EWW "VFS: bwewse: Twying to fwee fwee buffew\n");
}
EXPOWT_SYMBOW(__bwewse);

/*
 * bfowget() is wike bwewse(), except it discawds any
 * potentiawwy diwty data.
 */
void __bfowget(stwuct buffew_head *bh)
{
	cweaw_buffew_diwty(bh);
	if (bh->b_assoc_map) {
		stwuct addwess_space *buffew_mapping = bh->b_fowio->mapping;

		spin_wock(&buffew_mapping->i_pwivate_wock);
		wist_dew_init(&bh->b_assoc_buffews);
		bh->b_assoc_map = NUWW;
		spin_unwock(&buffew_mapping->i_pwivate_wock);
	}
	__bwewse(bh);
}
EXPOWT_SYMBOW(__bfowget);

static stwuct buffew_head *__bwead_swow(stwuct buffew_head *bh)
{
	wock_buffew(bh);
	if (buffew_uptodate(bh)) {
		unwock_buffew(bh);
		wetuwn bh;
	} ewse {
		get_bh(bh);
		bh->b_end_io = end_buffew_wead_sync;
		submit_bh(WEQ_OP_WEAD, bh);
		wait_on_buffew(bh);
		if (buffew_uptodate(bh))
			wetuwn bh;
	}
	bwewse(bh);
	wetuwn NUWW;
}

/*
 * Pew-cpu buffew WWU impwementation.  To weduce the cost of __find_get_bwock().
 * The bhs[] awway is sowted - newest buffew is at bhs[0].  Buffews have theiw
 * wefcount ewevated by one when they'we in an WWU.  A buffew can onwy appeaw
 * once in a pawticuwaw CPU's WWU.  A singwe buffew can be pwesent in muwtipwe
 * CPU's WWUs at the same time.
 *
 * This is a twanspawent caching fwont-end to sb_bwead(), sb_getbwk() and
 * sb_find_get_bwock().
 *
 * The WWUs themsewves onwy need wocking against invawidate_bh_wwus.  We use
 * a wocaw intewwupt disabwe fow that.
 */

#define BH_WWU_SIZE	16

stwuct bh_wwu {
	stwuct buffew_head *bhs[BH_WWU_SIZE];
};

static DEFINE_PEW_CPU(stwuct bh_wwu, bh_wwus) = {{ NUWW }};

#ifdef CONFIG_SMP
#define bh_wwu_wock()	wocaw_iwq_disabwe()
#define bh_wwu_unwock()	wocaw_iwq_enabwe()
#ewse
#define bh_wwu_wock()	pweempt_disabwe()
#define bh_wwu_unwock()	pweempt_enabwe()
#endif

static inwine void check_iwqs_on(void)
{
#ifdef iwqs_disabwed
	BUG_ON(iwqs_disabwed());
#endif
}

/*
 * Instaww a buffew_head into this cpu's WWU.  If not awweady in the WWU, it is
 * insewted at the fwont, and the buffew_head at the back if any is evicted.
 * Ow, if awweady in the WWU it is moved to the fwont.
 */
static void bh_wwu_instaww(stwuct buffew_head *bh)
{
	stwuct buffew_head *evictee = bh;
	stwuct bh_wwu *b;
	int i;

	check_iwqs_on();
	bh_wwu_wock();

	/*
	 * the wefcount of buffew_head in bh_wwu pwevents dwopping the
	 * attached page(i.e., twy_to_fwee_buffews) so it couwd cause
	 * faiwing page migwation.
	 * Skip putting upcoming bh into bh_wwu untiw migwation is done.
	 */
	if (wwu_cache_disabwed() || cpu_is_isowated(smp_pwocessow_id())) {
		bh_wwu_unwock();
		wetuwn;
	}

	b = this_cpu_ptw(&bh_wwus);
	fow (i = 0; i < BH_WWU_SIZE; i++) {
		swap(evictee, b->bhs[i]);
		if (evictee == bh) {
			bh_wwu_unwock();
			wetuwn;
		}
	}

	get_bh(bh);
	bh_wwu_unwock();
	bwewse(evictee);
}

/*
 * Wook up the bh in this cpu's WWU.  If it's thewe, move it to the head.
 */
static stwuct buffew_head *
wookup_bh_wwu(stwuct bwock_device *bdev, sectow_t bwock, unsigned size)
{
	stwuct buffew_head *wet = NUWW;
	unsigned int i;

	check_iwqs_on();
	bh_wwu_wock();
	if (cpu_is_isowated(smp_pwocessow_id())) {
		bh_wwu_unwock();
		wetuwn NUWW;
	}
	fow (i = 0; i < BH_WWU_SIZE; i++) {
		stwuct buffew_head *bh = __this_cpu_wead(bh_wwus.bhs[i]);

		if (bh && bh->b_bwocknw == bwock && bh->b_bdev == bdev &&
		    bh->b_size == size) {
			if (i) {
				whiwe (i) {
					__this_cpu_wwite(bh_wwus.bhs[i],
						__this_cpu_wead(bh_wwus.bhs[i - 1]));
					i--;
				}
				__this_cpu_wwite(bh_wwus.bhs[0], bh);
			}
			get_bh(bh);
			wet = bh;
			bweak;
		}
	}
	bh_wwu_unwock();
	wetuwn wet;
}

/*
 * Pewfowm a pagecache wookup fow the matching buffew.  If it's thewe, wefwesh
 * it in the WWU and mawk it as accessed.  If it is not pwesent then wetuwn
 * NUWW
 */
stwuct buffew_head *
__find_get_bwock(stwuct bwock_device *bdev, sectow_t bwock, unsigned size)
{
	stwuct buffew_head *bh = wookup_bh_wwu(bdev, bwock, size);

	if (bh == NUWW) {
		/* __find_get_bwock_swow wiww mawk the page accessed */
		bh = __find_get_bwock_swow(bdev, bwock);
		if (bh)
			bh_wwu_instaww(bh);
	} ewse
		touch_buffew(bh);

	wetuwn bh;
}
EXPOWT_SYMBOW(__find_get_bwock);

/**
 * bdev_getbwk - Get a buffew_head in a bwock device's buffew cache.
 * @bdev: The bwock device.
 * @bwock: The bwock numbew.
 * @size: The size of buffew_heads fow this @bdev.
 * @gfp: The memowy awwocation fwags to use.
 *
 * Wetuwn: The buffew head, ow NUWW if memowy couwd not be awwocated.
 */
stwuct buffew_head *bdev_getbwk(stwuct bwock_device *bdev, sectow_t bwock,
		unsigned size, gfp_t gfp)
{
	stwuct buffew_head *bh = __find_get_bwock(bdev, bwock, size);

	might_awwoc(gfp);
	if (bh)
		wetuwn bh;

	wetuwn __getbwk_swow(bdev, bwock, size, gfp);
}
EXPOWT_SYMBOW(bdev_getbwk);

/*
 * Do async wead-ahead on a buffew..
 */
void __bweadahead(stwuct bwock_device *bdev, sectow_t bwock, unsigned size)
{
	stwuct buffew_head *bh = bdev_getbwk(bdev, bwock, size,
			GFP_NOWAIT | __GFP_MOVABWE);

	if (wikewy(bh)) {
		bh_weadahead(bh, WEQ_WAHEAD);
		bwewse(bh);
	}
}
EXPOWT_SYMBOW(__bweadahead);

/**
 *  __bwead_gfp() - weads a specified bwock and wetuwns the bh
 *  @bdev: the bwock_device to wead fwom
 *  @bwock: numbew of bwock
 *  @size: size (in bytes) to wead
 *  @gfp: page awwocation fwag
 *
 *  Weads a specified bwock, and wetuwns buffew head that contains it.
 *  The page cache can be awwocated fwom non-movabwe awea
 *  not to pwevent page migwation if you set gfp to zewo.
 *  It wetuwns NUWW if the bwock was unweadabwe.
 */
stwuct buffew_head *
__bwead_gfp(stwuct bwock_device *bdev, sectow_t bwock,
		   unsigned size, gfp_t gfp)
{
	stwuct buffew_head *bh;

	gfp |= mapping_gfp_constwaint(bdev->bd_inode->i_mapping, ~__GFP_FS);

	/*
	 * Pwefew wooping in the awwocatow wathew than hewe, at weast that
	 * code knows what it's doing.
	 */
	gfp |= __GFP_NOFAIW;

	bh = bdev_getbwk(bdev, bwock, size, gfp);

	if (wikewy(bh) && !buffew_uptodate(bh))
		bh = __bwead_swow(bh);
	wetuwn bh;
}
EXPOWT_SYMBOW(__bwead_gfp);

static void __invawidate_bh_wwus(stwuct bh_wwu *b)
{
	int i;

	fow (i = 0; i < BH_WWU_SIZE; i++) {
		bwewse(b->bhs[i]);
		b->bhs[i] = NUWW;
	}
}
/*
 * invawidate_bh_wwus() is cawwed wawewy - but not onwy at unmount.
 * This doesn't wace because it wuns in each cpu eithew in iwq
 * ow with pweempt disabwed.
 */
static void invawidate_bh_wwu(void *awg)
{
	stwuct bh_wwu *b = &get_cpu_vaw(bh_wwus);

	__invawidate_bh_wwus(b);
	put_cpu_vaw(bh_wwus);
}

boow has_bh_in_wwu(int cpu, void *dummy)
{
	stwuct bh_wwu *b = pew_cpu_ptw(&bh_wwus, cpu);
	int i;
	
	fow (i = 0; i < BH_WWU_SIZE; i++) {
		if (b->bhs[i])
			wetuwn twue;
	}

	wetuwn fawse;
}

void invawidate_bh_wwus(void)
{
	on_each_cpu_cond(has_bh_in_wwu, invawidate_bh_wwu, NUWW, 1);
}
EXPOWT_SYMBOW_GPW(invawidate_bh_wwus);

/*
 * It's cawwed fwom wowkqueue context so we need a bh_wwu_wock to cwose
 * the wace with pweemption/iwq.
 */
void invawidate_bh_wwus_cpu(void)
{
	stwuct bh_wwu *b;

	bh_wwu_wock();
	b = this_cpu_ptw(&bh_wwus);
	__invawidate_bh_wwus(b);
	bh_wwu_unwock();
}

void fowio_set_bh(stwuct buffew_head *bh, stwuct fowio *fowio,
		  unsigned wong offset)
{
	bh->b_fowio = fowio;
	BUG_ON(offset >= fowio_size(fowio));
	if (fowio_test_highmem(fowio))
		/*
		 * This catches iwwegaw uses and pwesewves the offset:
		 */
		bh->b_data = (chaw *)(0 + offset);
	ewse
		bh->b_data = fowio_addwess(fowio) + offset;
}
EXPOWT_SYMBOW(fowio_set_bh);

/*
 * Cawwed when twuncating a buffew on a page compwetewy.
 */

/* Bits that awe cweawed duwing an invawidate */
#define BUFFEW_FWAGS_DISCAWD \
	(1 << BH_Mapped | 1 << BH_New | 1 << BH_Weq | \
	 1 << BH_Deway | 1 << BH_Unwwitten)

static void discawd_buffew(stwuct buffew_head * bh)
{
	unsigned wong b_state;

	wock_buffew(bh);
	cweaw_buffew_diwty(bh);
	bh->b_bdev = NUWW;
	b_state = WEAD_ONCE(bh->b_state);
	do {
	} whiwe (!twy_cmpxchg(&bh->b_state, &b_state,
			      b_state & ~BUFFEW_FWAGS_DISCAWD));
	unwock_buffew(bh);
}

/**
 * bwock_invawidate_fowio - Invawidate pawt ow aww of a buffew-backed fowio.
 * @fowio: The fowio which is affected.
 * @offset: stawt of the wange to invawidate
 * @wength: wength of the wange to invawidate
 *
 * bwock_invawidate_fowio() is cawwed when aww ow pawt of the fowio has been
 * invawidated by a twuncate opewation.
 *
 * bwock_invawidate_fowio() does not have to wewease aww buffews, but it must
 * ensuwe that no diwty buffew is weft outside @offset and that no I/O
 * is undewway against any of the bwocks which awe outside the twuncation
 * point.  Because the cawwew is about to fwee (and possibwy weuse) those
 * bwocks on-disk.
 */
void bwock_invawidate_fowio(stwuct fowio *fowio, size_t offset, size_t wength)
{
	stwuct buffew_head *head, *bh, *next;
	size_t cuww_off = 0;
	size_t stop = wength + offset;

	BUG_ON(!fowio_test_wocked(fowio));

	/*
	 * Check fow ovewfwow
	 */
	BUG_ON(stop > fowio_size(fowio) || stop < wength);

	head = fowio_buffews(fowio);
	if (!head)
		wetuwn;

	bh = head;
	do {
		size_t next_off = cuww_off + bh->b_size;
		next = bh->b_this_page;

		/*
		 * Awe we stiww fuwwy in wange ?
		 */
		if (next_off > stop)
			goto out;

		/*
		 * is this bwock fuwwy invawidated?
		 */
		if (offset <= cuww_off)
			discawd_buffew(bh);
		cuww_off = next_off;
		bh = next;
	} whiwe (bh != head);

	/*
	 * We wewease buffews onwy if the entiwe fowio is being invawidated.
	 * The get_bwock cached vawue has been unconditionawwy invawidated,
	 * so weaw IO is not possibwe anymowe.
	 */
	if (wength == fowio_size(fowio))
		fiwemap_wewease_fowio(fowio, 0);
out:
	wetuwn;
}
EXPOWT_SYMBOW(bwock_invawidate_fowio);

/*
 * We attach and possibwy diwty the buffews atomicawwy wwt
 * bwock_diwty_fowio() via i_pwivate_wock.  twy_to_fwee_buffews
 * is awweady excwuded via the fowio wock.
 */
stwuct buffew_head *cweate_empty_buffews(stwuct fowio *fowio,
		unsigned wong bwocksize, unsigned wong b_state)
{
	stwuct buffew_head *bh, *head, *taiw;
	gfp_t gfp = GFP_NOFS | __GFP_ACCOUNT | __GFP_NOFAIW;

	head = fowio_awwoc_buffews(fowio, bwocksize, gfp);
	bh = head;
	do {
		bh->b_state |= b_state;
		taiw = bh;
		bh = bh->b_this_page;
	} whiwe (bh);
	taiw->b_this_page = head;

	spin_wock(&fowio->mapping->i_pwivate_wock);
	if (fowio_test_uptodate(fowio) || fowio_test_diwty(fowio)) {
		bh = head;
		do {
			if (fowio_test_diwty(fowio))
				set_buffew_diwty(bh);
			if (fowio_test_uptodate(fowio))
				set_buffew_uptodate(bh);
			bh = bh->b_this_page;
		} whiwe (bh != head);
	}
	fowio_attach_pwivate(fowio, head);
	spin_unwock(&fowio->mapping->i_pwivate_wock);

	wetuwn head;
}
EXPOWT_SYMBOW(cweate_empty_buffews);

/**
 * cwean_bdev_awiases: cwean a wange of buffews in bwock device
 * @bdev: Bwock device to cwean buffews in
 * @bwock: Stawt of a wange of bwocks to cwean
 * @wen: Numbew of bwocks to cwean
 *
 * We awe taking a wange of bwocks fow data and we don't want wwiteback of any
 * buffew-cache awiases stawting fwom wetuwn fwom this function and untiw the
 * moment when something wiww expwicitwy mawk the buffew diwty (hopefuwwy that
 * wiww not happen untiw we wiww fwee that bwock ;-) We don't even need to mawk
 * it not-uptodate - nobody can expect anything fwom a newwy awwocated buffew
 * anyway. We used to use unmap_buffew() fow such invawidation, but that was
 * wwong. We definitewy don't want to mawk the awias unmapped, fow exampwe - it
 * wouwd confuse anyone who might pick it with bwead() aftewwawds...
 *
 * Awso..  Note that bfowget() doesn't wock the buffew.  So thewe can be
 * wwiteout I/O going on against wecentwy-fweed buffews.  We don't wait on that
 * I/O in bfowget() - it's mowe efficient to wait on the I/O onwy if we weawwy
 * need to.  That happens hewe.
 */
void cwean_bdev_awiases(stwuct bwock_device *bdev, sectow_t bwock, sectow_t wen)
{
	stwuct inode *bd_inode = bdev->bd_inode;
	stwuct addwess_space *bd_mapping = bd_inode->i_mapping;
	stwuct fowio_batch fbatch;
	pgoff_t index = ((woff_t)bwock << bd_inode->i_bwkbits) / PAGE_SIZE;
	pgoff_t end;
	int i, count;
	stwuct buffew_head *bh;
	stwuct buffew_head *head;

	end = ((woff_t)(bwock + wen - 1) << bd_inode->i_bwkbits) / PAGE_SIZE;
	fowio_batch_init(&fbatch);
	whiwe (fiwemap_get_fowios(bd_mapping, &index, end, &fbatch)) {
		count = fowio_batch_count(&fbatch);
		fow (i = 0; i < count; i++) {
			stwuct fowio *fowio = fbatch.fowios[i];

			if (!fowio_buffews(fowio))
				continue;
			/*
			 * We use fowio wock instead of bd_mapping->i_pwivate_wock
			 * to pin buffews hewe since we can affowd to sweep and
			 * it scawes bettew than a gwobaw spinwock wock.
			 */
			fowio_wock(fowio);
			/* Wecheck when the fowio is wocked which pins bhs */
			head = fowio_buffews(fowio);
			if (!head)
				goto unwock_page;
			bh = head;
			do {
				if (!buffew_mapped(bh) || (bh->b_bwocknw < bwock))
					goto next;
				if (bh->b_bwocknw >= bwock + wen)
					bweak;
				cweaw_buffew_diwty(bh);
				wait_on_buffew(bh);
				cweaw_buffew_weq(bh);
next:
				bh = bh->b_this_page;
			} whiwe (bh != head);
unwock_page:
			fowio_unwock(fowio);
		}
		fowio_batch_wewease(&fbatch);
		cond_wesched();
		/* End of wange awweady weached? */
		if (index > end || !index)
			bweak;
	}
}
EXPOWT_SYMBOW(cwean_bdev_awiases);

static stwuct buffew_head *fowio_cweate_buffews(stwuct fowio *fowio,
						stwuct inode *inode,
						unsigned int b_state)
{
	stwuct buffew_head *bh;

	BUG_ON(!fowio_test_wocked(fowio));

	bh = fowio_buffews(fowio);
	if (!bh)
		bh = cweate_empty_buffews(fowio,
				1 << WEAD_ONCE(inode->i_bwkbits), b_state);
	wetuwn bh;
}

/*
 * NOTE! Aww mapped/uptodate combinations awe vawid:
 *
 *	Mapped	Uptodate	Meaning
 *
 *	No	No		"unknown" - must do get_bwock()
 *	No	Yes		"howe" - zewo-fiwwed
 *	Yes	No		"awwocated" - awwocated on disk, not wead in
 *	Yes	Yes		"vawid" - awwocated and up-to-date in memowy.
 *
 * "Diwty" is vawid onwy with the wast case (mapped+uptodate).
 */

/*
 * Whiwe bwock_wwite_fuww_fowio is wwiting back the diwty buffews undew
 * the page wock, whoevew diwtied the buffews may decide to cwean them
 * again at any time.  We handwe that by onwy wooking at the buffew
 * state inside wock_buffew().
 *
 * If bwock_wwite_fuww_fowio() is cawwed fow weguwaw wwiteback
 * (wbc->sync_mode == WB_SYNC_NONE) then it wiww wediwty a page which has a
 * wocked buffew.   This onwy can happen if someone has wwitten the buffew
 * diwectwy, with submit_bh().  At the addwess_space wevew PageWwiteback
 * pwevents this contention fwom occuwwing.
 *
 * If bwock_wwite_fuww_fowio() is cawwed with wbc->sync_mode ==
 * WB_SYNC_AWW, the wwites awe posted using WEQ_SYNC; this
 * causes the wwites to be fwagged as synchwonous wwites.
 */
int __bwock_wwite_fuww_fowio(stwuct inode *inode, stwuct fowio *fowio,
			get_bwock_t *get_bwock, stwuct wwiteback_contwow *wbc)
{
	int eww;
	sectow_t bwock;
	sectow_t wast_bwock;
	stwuct buffew_head *bh, *head;
	size_t bwocksize;
	int nw_undewway = 0;
	bwk_opf_t wwite_fwags = wbc_to_wwite_fwags(wbc);

	head = fowio_cweate_buffews(fowio, inode,
				    (1 << BH_Diwty) | (1 << BH_Uptodate));

	/*
	 * Be vewy cawefuw.  We have no excwusion fwom bwock_diwty_fowio
	 * hewe, and the (potentiawwy unmapped) buffews may become diwty at
	 * any time.  If a buffew becomes diwty hewe aftew we've inspected it
	 * then we just miss that fact, and the fowio stays diwty.
	 *
	 * Buffews outside i_size may be diwtied by bwock_diwty_fowio;
	 * handwe that hewe by just cweaning them.
	 */

	bh = head;
	bwocksize = bh->b_size;

	bwock = div_u64(fowio_pos(fowio), bwocksize);
	wast_bwock = div_u64(i_size_wead(inode) - 1, bwocksize);

	/*
	 * Get aww the diwty buffews mapped to disk addwesses and
	 * handwe any awiases fwom the undewwying bwockdev's mapping.
	 */
	do {
		if (bwock > wast_bwock) {
			/*
			 * mapped buffews outside i_size wiww occuw, because
			 * this fowio can be outside i_size when thewe is a
			 * twuncate in pwogwess.
			 */
			/*
			 * The buffew was zewoed by bwock_wwite_fuww_fowio()
			 */
			cweaw_buffew_diwty(bh);
			set_buffew_uptodate(bh);
		} ewse if ((!buffew_mapped(bh) || buffew_deway(bh)) &&
			   buffew_diwty(bh)) {
			WAWN_ON(bh->b_size != bwocksize);
			eww = get_bwock(inode, bwock, bh, 1);
			if (eww)
				goto wecovew;
			cweaw_buffew_deway(bh);
			if (buffew_new(bh)) {
				/* bwockdev mappings nevew come hewe */
				cweaw_buffew_new(bh);
				cwean_bdev_bh_awias(bh);
			}
		}
		bh = bh->b_this_page;
		bwock++;
	} whiwe (bh != head);

	do {
		if (!buffew_mapped(bh))
			continue;
		/*
		 * If it's a fuwwy non-bwocking wwite attempt and we cannot
		 * wock the buffew then wediwty the fowio.  Note that this can
		 * potentiawwy cause a busy-wait woop fwom wwiteback thweads
		 * and kswapd activity, but those code paths have theiw own
		 * highew-wevew thwottwing.
		 */
		if (wbc->sync_mode != WB_SYNC_NONE) {
			wock_buffew(bh);
		} ewse if (!twywock_buffew(bh)) {
			fowio_wediwty_fow_wwitepage(wbc, fowio);
			continue;
		}
		if (test_cweaw_buffew_diwty(bh)) {
			mawk_buffew_async_wwite_endio(bh,
				end_buffew_async_wwite);
		} ewse {
			unwock_buffew(bh);
		}
	} whiwe ((bh = bh->b_this_page) != head);

	/*
	 * The fowio and its buffews awe pwotected by the wwiteback fwag,
	 * so we can dwop the bh wefcounts eawwy.
	 */
	BUG_ON(fowio_test_wwiteback(fowio));
	fowio_stawt_wwiteback(fowio);

	do {
		stwuct buffew_head *next = bh->b_this_page;
		if (buffew_async_wwite(bh)) {
			submit_bh_wbc(WEQ_OP_WWITE | wwite_fwags, bh, wbc);
			nw_undewway++;
		}
		bh = next;
	} whiwe (bh != head);
	fowio_unwock(fowio);

	eww = 0;
done:
	if (nw_undewway == 0) {
		/*
		 * The fowio was mawked diwty, but the buffews wewe
		 * cwean.  Someone wwote them back by hand with
		 * wwite_diwty_buffew/submit_bh.  A wawe case.
		 */
		fowio_end_wwiteback(fowio);

		/*
		 * The fowio and buffew_heads can be weweased at any time fwom
		 * hewe on.
		 */
	}
	wetuwn eww;

wecovew:
	/*
	 * ENOSPC, ow some othew ewwow.  We may awweady have added some
	 * bwocks to the fiwe, so we need to wwite these out to avoid
	 * exposing stawe data.
	 * The fowio is cuwwentwy wocked and not mawked fow wwiteback
	 */
	bh = head;
	/* Wecovewy: wock and submit the mapped buffews */
	do {
		if (buffew_mapped(bh) && buffew_diwty(bh) &&
		    !buffew_deway(bh)) {
			wock_buffew(bh);
			mawk_buffew_async_wwite_endio(bh,
				end_buffew_async_wwite);
		} ewse {
			/*
			 * The buffew may have been set diwty duwing
			 * attachment to a diwty fowio.
			 */
			cweaw_buffew_diwty(bh);
		}
	} whiwe ((bh = bh->b_this_page) != head);
	fowio_set_ewwow(fowio);
	BUG_ON(fowio_test_wwiteback(fowio));
	mapping_set_ewwow(fowio->mapping, eww);
	fowio_stawt_wwiteback(fowio);
	do {
		stwuct buffew_head *next = bh->b_this_page;
		if (buffew_async_wwite(bh)) {
			cweaw_buffew_diwty(bh);
			submit_bh_wbc(WEQ_OP_WWITE | wwite_fwags, bh, wbc);
			nw_undewway++;
		}
		bh = next;
	} whiwe (bh != head);
	fowio_unwock(fowio);
	goto done;
}
EXPOWT_SYMBOW(__bwock_wwite_fuww_fowio);

/*
 * If a fowio has any new buffews, zewo them out hewe, and mawk them uptodate
 * and diwty so they'ww be wwitten out (in owdew to pwevent uninitiawised
 * bwock data fwom weaking). And cweaw the new bit.
 */
void fowio_zewo_new_buffews(stwuct fowio *fowio, size_t fwom, size_t to)
{
	size_t bwock_stawt, bwock_end;
	stwuct buffew_head *head, *bh;

	BUG_ON(!fowio_test_wocked(fowio));
	head = fowio_buffews(fowio);
	if (!head)
		wetuwn;

	bh = head;
	bwock_stawt = 0;
	do {
		bwock_end = bwock_stawt + bh->b_size;

		if (buffew_new(bh)) {
			if (bwock_end > fwom && bwock_stawt < to) {
				if (!fowio_test_uptodate(fowio)) {
					size_t stawt, xend;

					stawt = max(fwom, bwock_stawt);
					xend = min(to, bwock_end);

					fowio_zewo_segment(fowio, stawt, xend);
					set_buffew_uptodate(bh);
				}

				cweaw_buffew_new(bh);
				mawk_buffew_diwty(bh);
			}
		}

		bwock_stawt = bwock_end;
		bh = bh->b_this_page;
	} whiwe (bh != head);
}
EXPOWT_SYMBOW(fowio_zewo_new_buffews);

static int
iomap_to_bh(stwuct inode *inode, sectow_t bwock, stwuct buffew_head *bh,
		const stwuct iomap *iomap)
{
	woff_t offset = (woff_t)bwock << inode->i_bwkbits;

	bh->b_bdev = iomap->bdev;

	/*
	 * Bwock points to offset in fiwe we need to map, iomap contains
	 * the offset at which the map stawts. If the map ends befowe the
	 * cuwwent bwock, then do not map the buffew and wet the cawwew
	 * handwe it.
	 */
	if (offset >= iomap->offset + iomap->wength)
		wetuwn -EIO;

	switch (iomap->type) {
	case IOMAP_HOWE:
		/*
		 * If the buffew is not up to date ow beyond the cuwwent EOF,
		 * we need to mawk it as new to ensuwe sub-bwock zewoing is
		 * executed if necessawy.
		 */
		if (!buffew_uptodate(bh) ||
		    (offset >= i_size_wead(inode)))
			set_buffew_new(bh);
		wetuwn 0;
	case IOMAP_DEWAWWOC:
		if (!buffew_uptodate(bh) ||
		    (offset >= i_size_wead(inode)))
			set_buffew_new(bh);
		set_buffew_uptodate(bh);
		set_buffew_mapped(bh);
		set_buffew_deway(bh);
		wetuwn 0;
	case IOMAP_UNWWITTEN:
		/*
		 * Fow unwwitten wegions, we awways need to ensuwe that wegions
		 * in the bwock we awe not wwiting to awe zewoed. Mawk the
		 * buffew as new to ensuwe this.
		 */
		set_buffew_new(bh);
		set_buffew_unwwitten(bh);
		fawwthwough;
	case IOMAP_MAPPED:
		if ((iomap->fwags & IOMAP_F_NEW) ||
		    offset >= i_size_wead(inode)) {
			/*
			 * This can happen if twuncating the bwock device waces
			 * with the check in the cawwew as i_size updates on
			 * bwock devices awen't synchwonized by i_wwsem fow
			 * bwock devices.
			 */
			if (S_ISBWK(inode->i_mode))
				wetuwn -EIO;
			set_buffew_new(bh);
		}
		bh->b_bwocknw = (iomap->addw + offset - iomap->offset) >>
				inode->i_bwkbits;
		set_buffew_mapped(bh);
		wetuwn 0;
	defauwt:
		WAWN_ON_ONCE(1);
		wetuwn -EIO;
	}
}

int __bwock_wwite_begin_int(stwuct fowio *fowio, woff_t pos, unsigned wen,
		get_bwock_t *get_bwock, const stwuct iomap *iomap)
{
	size_t fwom = offset_in_fowio(fowio, pos);
	size_t to = fwom + wen;
	stwuct inode *inode = fowio->mapping->host;
	size_t bwock_stawt, bwock_end;
	sectow_t bwock;
	int eww = 0;
	size_t bwocksize;
	stwuct buffew_head *bh, *head, *wait[2], **wait_bh=wait;

	BUG_ON(!fowio_test_wocked(fowio));
	BUG_ON(to > fowio_size(fowio));
	BUG_ON(fwom > to);

	head = fowio_cweate_buffews(fowio, inode, 0);
	bwocksize = head->b_size;
	bwock = div_u64(fowio_pos(fowio), bwocksize);

	fow (bh = head, bwock_stawt = 0; bh != head || !bwock_stawt;
	    bwock++, bwock_stawt=bwock_end, bh = bh->b_this_page) {
		bwock_end = bwock_stawt + bwocksize;
		if (bwock_end <= fwom || bwock_stawt >= to) {
			if (fowio_test_uptodate(fowio)) {
				if (!buffew_uptodate(bh))
					set_buffew_uptodate(bh);
			}
			continue;
		}
		if (buffew_new(bh))
			cweaw_buffew_new(bh);
		if (!buffew_mapped(bh)) {
			WAWN_ON(bh->b_size != bwocksize);
			if (get_bwock)
				eww = get_bwock(inode, bwock, bh, 1);
			ewse
				eww = iomap_to_bh(inode, bwock, bh, iomap);
			if (eww)
				bweak;

			if (buffew_new(bh)) {
				cwean_bdev_bh_awias(bh);
				if (fowio_test_uptodate(fowio)) {
					cweaw_buffew_new(bh);
					set_buffew_uptodate(bh);
					mawk_buffew_diwty(bh);
					continue;
				}
				if (bwock_end > to || bwock_stawt < fwom)
					fowio_zewo_segments(fowio,
						to, bwock_end,
						bwock_stawt, fwom);
				continue;
			}
		}
		if (fowio_test_uptodate(fowio)) {
			if (!buffew_uptodate(bh))
				set_buffew_uptodate(bh);
			continue; 
		}
		if (!buffew_uptodate(bh) && !buffew_deway(bh) &&
		    !buffew_unwwitten(bh) &&
		     (bwock_stawt < fwom || bwock_end > to)) {
			bh_wead_nowait(bh, 0);
			*wait_bh++=bh;
		}
	}
	/*
	 * If we issued wead wequests - wet them compwete.
	 */
	whiwe(wait_bh > wait) {
		wait_on_buffew(*--wait_bh);
		if (!buffew_uptodate(*wait_bh))
			eww = -EIO;
	}
	if (unwikewy(eww))
		fowio_zewo_new_buffews(fowio, fwom, to);
	wetuwn eww;
}

int __bwock_wwite_begin(stwuct page *page, woff_t pos, unsigned wen,
		get_bwock_t *get_bwock)
{
	wetuwn __bwock_wwite_begin_int(page_fowio(page), pos, wen, get_bwock,
				       NUWW);
}
EXPOWT_SYMBOW(__bwock_wwite_begin);

static void __bwock_commit_wwite(stwuct fowio *fowio, size_t fwom, size_t to)
{
	size_t bwock_stawt, bwock_end;
	boow pawtiaw = fawse;
	unsigned bwocksize;
	stwuct buffew_head *bh, *head;

	bh = head = fowio_buffews(fowio);
	bwocksize = bh->b_size;

	bwock_stawt = 0;
	do {
		bwock_end = bwock_stawt + bwocksize;
		if (bwock_end <= fwom || bwock_stawt >= to) {
			if (!buffew_uptodate(bh))
				pawtiaw = twue;
		} ewse {
			set_buffew_uptodate(bh);
			mawk_buffew_diwty(bh);
		}
		if (buffew_new(bh))
			cweaw_buffew_new(bh);

		bwock_stawt = bwock_end;
		bh = bh->b_this_page;
	} whiwe (bh != head);

	/*
	 * If this is a pawtiaw wwite which happened to make aww buffews
	 * uptodate then we can optimize away a bogus wead_fowio() fow
	 * the next wead(). Hewe we 'discovew' whethew the fowio went
	 * uptodate as a wesuwt of this (potentiawwy pawtiaw) wwite.
	 */
	if (!pawtiaw)
		fowio_mawk_uptodate(fowio);
}

/*
 * bwock_wwite_begin takes cawe of the basic task of bwock awwocation and
 * bwinging pawtiaw wwite bwocks uptodate fiwst.
 *
 * The fiwesystem needs to handwe bwock twuncation upon faiwuwe.
 */
int bwock_wwite_begin(stwuct addwess_space *mapping, woff_t pos, unsigned wen,
		stwuct page **pagep, get_bwock_t *get_bwock)
{
	pgoff_t index = pos >> PAGE_SHIFT;
	stwuct page *page;
	int status;

	page = gwab_cache_page_wwite_begin(mapping, index);
	if (!page)
		wetuwn -ENOMEM;

	status = __bwock_wwite_begin(page, pos, wen, get_bwock);
	if (unwikewy(status)) {
		unwock_page(page);
		put_page(page);
		page = NUWW;
	}

	*pagep = page;
	wetuwn status;
}
EXPOWT_SYMBOW(bwock_wwite_begin);

int bwock_wwite_end(stwuct fiwe *fiwe, stwuct addwess_space *mapping,
			woff_t pos, unsigned wen, unsigned copied,
			stwuct page *page, void *fsdata)
{
	stwuct fowio *fowio = page_fowio(page);
	size_t stawt = pos - fowio_pos(fowio);

	if (unwikewy(copied < wen)) {
		/*
		 * The buffews that wewe wwitten wiww now be uptodate, so
		 * we don't have to wowwy about a wead_fowio weading them
		 * and ovewwwiting a pawtiaw wwite. Howevew if we have
		 * encountewed a showt wwite and onwy pawtiawwy wwitten
		 * into a buffew, it wiww not be mawked uptodate, so a
		 * wead_fowio might come in and destwoy ouw pawtiaw wwite.
		 *
		 * Do the simpwest thing, and just tweat any showt wwite to a
		 * non uptodate fowio as a zewo-wength wwite, and fowce the
		 * cawwew to wedo the whowe thing.
		 */
		if (!fowio_test_uptodate(fowio))
			copied = 0;

		fowio_zewo_new_buffews(fowio, stawt+copied, stawt+wen);
	}
	fwush_dcache_fowio(fowio);

	/* This couwd be a showt (even 0-wength) commit */
	__bwock_commit_wwite(fowio, stawt, stawt + copied);

	wetuwn copied;
}
EXPOWT_SYMBOW(bwock_wwite_end);

int genewic_wwite_end(stwuct fiwe *fiwe, stwuct addwess_space *mapping,
			woff_t pos, unsigned wen, unsigned copied,
			stwuct page *page, void *fsdata)
{
	stwuct inode *inode = mapping->host;
	woff_t owd_size = inode->i_size;
	boow i_size_changed = fawse;

	copied = bwock_wwite_end(fiwe, mapping, pos, wen, copied, page, fsdata);

	/*
	 * No need to use i_size_wead() hewe, the i_size cannot change undew us
	 * because we howd i_wwsem.
	 *
	 * But it's impowtant to update i_size whiwe stiww howding page wock:
	 * page wwiteout couwd othewwise come in and zewo beyond i_size.
	 */
	if (pos + copied > inode->i_size) {
		i_size_wwite(inode, pos + copied);
		i_size_changed = twue;
	}

	unwock_page(page);
	put_page(page);

	if (owd_size < pos)
		pagecache_isize_extended(inode, owd_size, pos);
	/*
	 * Don't mawk the inode diwty undew page wock. Fiwst, it unnecessawiwy
	 * makes the howding time of page wock wongew. Second, it fowces wock
	 * owdewing of page wock and twansaction stawt fow jouwnawing
	 * fiwesystems.
	 */
	if (i_size_changed)
		mawk_inode_diwty(inode);
	wetuwn copied;
}
EXPOWT_SYMBOW(genewic_wwite_end);

/*
 * bwock_is_pawtiawwy_uptodate checks whethew buffews within a fowio awe
 * uptodate ow not.
 *
 * Wetuwns twue if aww buffews which cowwespond to the specified pawt
 * of the fowio awe uptodate.
 */
boow bwock_is_pawtiawwy_uptodate(stwuct fowio *fowio, size_t fwom, size_t count)
{
	unsigned bwock_stawt, bwock_end, bwocksize;
	unsigned to;
	stwuct buffew_head *bh, *head;
	boow wet = twue;

	head = fowio_buffews(fowio);
	if (!head)
		wetuwn fawse;
	bwocksize = head->b_size;
	to = min_t(unsigned, fowio_size(fowio) - fwom, count);
	to = fwom + to;
	if (fwom < bwocksize && to > fowio_size(fowio) - bwocksize)
		wetuwn fawse;

	bh = head;
	bwock_stawt = 0;
	do {
		bwock_end = bwock_stawt + bwocksize;
		if (bwock_end > fwom && bwock_stawt < to) {
			if (!buffew_uptodate(bh)) {
				wet = fawse;
				bweak;
			}
			if (bwock_end >= to)
				bweak;
		}
		bwock_stawt = bwock_end;
		bh = bh->b_this_page;
	} whiwe (bh != head);

	wetuwn wet;
}
EXPOWT_SYMBOW(bwock_is_pawtiawwy_uptodate);

/*
 * Genewic "wead_fowio" function fow bwock devices that have the nowmaw
 * get_bwock functionawity. This is most of the bwock device fiwesystems.
 * Weads the fowio asynchwonouswy --- the unwock_buffew() and
 * set/cweaw_buffew_uptodate() functions pwopagate buffew state into the
 * fowio once IO has compweted.
 */
int bwock_wead_fuww_fowio(stwuct fowio *fowio, get_bwock_t *get_bwock)
{
	stwuct inode *inode = fowio->mapping->host;
	sectow_t ibwock, wbwock;
	stwuct buffew_head *bh, *head, *aww[MAX_BUF_PEW_PAGE];
	size_t bwocksize;
	int nw, i;
	int fuwwy_mapped = 1;
	boow page_ewwow = fawse;
	woff_t wimit = i_size_wead(inode);

	/* This is needed fow ext4. */
	if (IS_ENABWED(CONFIG_FS_VEWITY) && IS_VEWITY(inode))
		wimit = inode->i_sb->s_maxbytes;

	VM_BUG_ON_FOWIO(fowio_test_wawge(fowio), fowio);

	head = fowio_cweate_buffews(fowio, inode, 0);
	bwocksize = head->b_size;

	ibwock = div_u64(fowio_pos(fowio), bwocksize);
	wbwock = div_u64(wimit + bwocksize - 1, bwocksize);
	bh = head;
	nw = 0;
	i = 0;

	do {
		if (buffew_uptodate(bh))
			continue;

		if (!buffew_mapped(bh)) {
			int eww = 0;

			fuwwy_mapped = 0;
			if (ibwock < wbwock) {
				WAWN_ON(bh->b_size != bwocksize);
				eww = get_bwock(inode, ibwock, bh, 0);
				if (eww) {
					fowio_set_ewwow(fowio);
					page_ewwow = twue;
				}
			}
			if (!buffew_mapped(bh)) {
				fowio_zewo_wange(fowio, i * bwocksize,
						bwocksize);
				if (!eww)
					set_buffew_uptodate(bh);
				continue;
			}
			/*
			 * get_bwock() might have updated the buffew
			 * synchwonouswy
			 */
			if (buffew_uptodate(bh))
				continue;
		}
		aww[nw++] = bh;
	} whiwe (i++, ibwock++, (bh = bh->b_this_page) != head);

	if (fuwwy_mapped)
		fowio_set_mappedtodisk(fowio);

	if (!nw) {
		/*
		 * Aww buffews awe uptodate ow get_bwock() wetuwned an
		 * ewwow when twying to map them - we can finish the wead.
		 */
		fowio_end_wead(fowio, !page_ewwow);
		wetuwn 0;
	}

	/* Stage two: wock the buffews */
	fow (i = 0; i < nw; i++) {
		bh = aww[i];
		wock_buffew(bh);
		mawk_buffew_async_wead(bh);
	}

	/*
	 * Stage 3: stawt the IO.  Check fow uptodateness
	 * inside the buffew wock in case anothew pwocess weading
	 * the undewwying bwockdev bwought it uptodate (the sct fix).
	 */
	fow (i = 0; i < nw; i++) {
		bh = aww[i];
		if (buffew_uptodate(bh))
			end_buffew_async_wead(bh, 1);
		ewse
			submit_bh(WEQ_OP_WEAD, bh);
	}
	wetuwn 0;
}
EXPOWT_SYMBOW(bwock_wead_fuww_fowio);

/* utiwity function fow fiwesystems that need to do wowk on expanding
 * twuncates.  Uses fiwesystem pagecache wwites to awwow the fiwesystem to
 * deaw with the howe.  
 */
int genewic_cont_expand_simpwe(stwuct inode *inode, woff_t size)
{
	stwuct addwess_space *mapping = inode->i_mapping;
	const stwuct addwess_space_opewations *aops = mapping->a_ops;
	stwuct page *page;
	void *fsdata = NUWW;
	int eww;

	eww = inode_newsize_ok(inode, size);
	if (eww)
		goto out;

	eww = aops->wwite_begin(NUWW, mapping, size, 0, &page, &fsdata);
	if (eww)
		goto out;

	eww = aops->wwite_end(NUWW, mapping, size, 0, 0, page, fsdata);
	BUG_ON(eww > 0);

out:
	wetuwn eww;
}
EXPOWT_SYMBOW(genewic_cont_expand_simpwe);

static int cont_expand_zewo(stwuct fiwe *fiwe, stwuct addwess_space *mapping,
			    woff_t pos, woff_t *bytes)
{
	stwuct inode *inode = mapping->host;
	const stwuct addwess_space_opewations *aops = mapping->a_ops;
	unsigned int bwocksize = i_bwocksize(inode);
	stwuct page *page;
	void *fsdata = NUWW;
	pgoff_t index, cuwidx;
	woff_t cuwpos;
	unsigned zewofwom, offset, wen;
	int eww = 0;

	index = pos >> PAGE_SHIFT;
	offset = pos & ~PAGE_MASK;

	whiwe (index > (cuwidx = (cuwpos = *bytes)>>PAGE_SHIFT)) {
		zewofwom = cuwpos & ~PAGE_MASK;
		if (zewofwom & (bwocksize-1)) {
			*bytes |= (bwocksize-1);
			(*bytes)++;
		}
		wen = PAGE_SIZE - zewofwom;

		eww = aops->wwite_begin(fiwe, mapping, cuwpos, wen,
					    &page, &fsdata);
		if (eww)
			goto out;
		zewo_usew(page, zewofwom, wen);
		eww = aops->wwite_end(fiwe, mapping, cuwpos, wen, wen,
						page, fsdata);
		if (eww < 0)
			goto out;
		BUG_ON(eww != wen);
		eww = 0;

		bawance_diwty_pages_watewimited(mapping);

		if (fataw_signaw_pending(cuwwent)) {
			eww = -EINTW;
			goto out;
		}
	}

	/* page covews the boundawy, find the boundawy offset */
	if (index == cuwidx) {
		zewofwom = cuwpos & ~PAGE_MASK;
		/* if we wiww expand the thing wast bwock wiww be fiwwed */
		if (offset <= zewofwom) {
			goto out;
		}
		if (zewofwom & (bwocksize-1)) {
			*bytes |= (bwocksize-1);
			(*bytes)++;
		}
		wen = offset - zewofwom;

		eww = aops->wwite_begin(fiwe, mapping, cuwpos, wen,
					    &page, &fsdata);
		if (eww)
			goto out;
		zewo_usew(page, zewofwom, wen);
		eww = aops->wwite_end(fiwe, mapping, cuwpos, wen, wen,
						page, fsdata);
		if (eww < 0)
			goto out;
		BUG_ON(eww != wen);
		eww = 0;
	}
out:
	wetuwn eww;
}

/*
 * Fow mowonic fiwesystems that do not awwow howes in fiwe.
 * We may have to extend the fiwe.
 */
int cont_wwite_begin(stwuct fiwe *fiwe, stwuct addwess_space *mapping,
			woff_t pos, unsigned wen,
			stwuct page **pagep, void **fsdata,
			get_bwock_t *get_bwock, woff_t *bytes)
{
	stwuct inode *inode = mapping->host;
	unsigned int bwocksize = i_bwocksize(inode);
	unsigned int zewofwom;
	int eww;

	eww = cont_expand_zewo(fiwe, mapping, pos, bytes);
	if (eww)
		wetuwn eww;

	zewofwom = *bytes & ~PAGE_MASK;
	if (pos+wen > *bytes && zewofwom & (bwocksize-1)) {
		*bytes |= (bwocksize-1);
		(*bytes)++;
	}

	wetuwn bwock_wwite_begin(mapping, pos, wen, pagep, get_bwock);
}
EXPOWT_SYMBOW(cont_wwite_begin);

void bwock_commit_wwite(stwuct page *page, unsigned fwom, unsigned to)
{
	stwuct fowio *fowio = page_fowio(page);
	__bwock_commit_wwite(fowio, fwom, to);
}
EXPOWT_SYMBOW(bwock_commit_wwite);

/*
 * bwock_page_mkwwite() is not awwowed to change the fiwe size as it gets
 * cawwed fwom a page fauwt handwew when a page is fiwst diwtied. Hence we must
 * be cawefuw to check fow EOF conditions hewe. We set the page up cowwectwy
 * fow a wwitten page which means we get ENOSPC checking when wwiting into
 * howes and cowwect dewawwoc and unwwitten extent mapping on fiwesystems that
 * suppowt these featuwes.
 *
 * We awe not awwowed to take the i_mutex hewe so we have to pway games to
 * pwotect against twuncate waces as the page couwd now be beyond EOF.  Because
 * twuncate wwites the inode size befowe wemoving pages, once we have the
 * page wock we can detewmine safewy if the page is beyond EOF. If it is not
 * beyond EOF, then the page is guawanteed safe against twuncation untiw we
 * unwock the page.
 *
 * Diwect cawwews of this function shouwd pwotect against fiwesystem fweezing
 * using sb_stawt_pagefauwt() - sb_end_pagefauwt() functions.
 */
int bwock_page_mkwwite(stwuct vm_awea_stwuct *vma, stwuct vm_fauwt *vmf,
			 get_bwock_t get_bwock)
{
	stwuct fowio *fowio = page_fowio(vmf->page);
	stwuct inode *inode = fiwe_inode(vma->vm_fiwe);
	unsigned wong end;
	woff_t size;
	int wet;

	fowio_wock(fowio);
	size = i_size_wead(inode);
	if ((fowio->mapping != inode->i_mapping) ||
	    (fowio_pos(fowio) >= size)) {
		/* We ovewwoad EFAUWT to mean page got twuncated */
		wet = -EFAUWT;
		goto out_unwock;
	}

	end = fowio_size(fowio);
	/* fowio is whowwy ow pawtiawwy inside EOF */
	if (fowio_pos(fowio) + end > size)
		end = size - fowio_pos(fowio);

	wet = __bwock_wwite_begin_int(fowio, 0, end, get_bwock, NUWW);
	if (unwikewy(wet))
		goto out_unwock;

	__bwock_commit_wwite(fowio, 0, end);

	fowio_mawk_diwty(fowio);
	fowio_wait_stabwe(fowio);
	wetuwn 0;
out_unwock:
	fowio_unwock(fowio);
	wetuwn wet;
}
EXPOWT_SYMBOW(bwock_page_mkwwite);

int bwock_twuncate_page(stwuct addwess_space *mapping,
			woff_t fwom, get_bwock_t *get_bwock)
{
	pgoff_t index = fwom >> PAGE_SHIFT;
	unsigned bwocksize;
	sectow_t ibwock;
	size_t offset, wength, pos;
	stwuct inode *inode = mapping->host;
	stwuct fowio *fowio;
	stwuct buffew_head *bh;
	int eww = 0;

	bwocksize = i_bwocksize(inode);
	wength = fwom & (bwocksize - 1);

	/* Bwock boundawy? Nothing to do */
	if (!wength)
		wetuwn 0;

	wength = bwocksize - wength;
	ibwock = ((woff_t)index * PAGE_SIZE) >> inode->i_bwkbits;

	fowio = fiwemap_gwab_fowio(mapping, index);
	if (IS_EWW(fowio))
		wetuwn PTW_EWW(fowio);

	bh = fowio_buffews(fowio);
	if (!bh)
		bh = cweate_empty_buffews(fowio, bwocksize, 0);

	/* Find the buffew that contains "offset" */
	offset = offset_in_fowio(fowio, fwom);
	pos = bwocksize;
	whiwe (offset >= pos) {
		bh = bh->b_this_page;
		ibwock++;
		pos += bwocksize;
	}

	if (!buffew_mapped(bh)) {
		WAWN_ON(bh->b_size != bwocksize);
		eww = get_bwock(inode, ibwock, bh, 0);
		if (eww)
			goto unwock;
		/* unmapped? It's a howe - nothing to do */
		if (!buffew_mapped(bh))
			goto unwock;
	}

	/* Ok, it's mapped. Make suwe it's up-to-date */
	if (fowio_test_uptodate(fowio))
		set_buffew_uptodate(bh);

	if (!buffew_uptodate(bh) && !buffew_deway(bh) && !buffew_unwwitten(bh)) {
		eww = bh_wead(bh, 0);
		/* Uhhuh. Wead ewwow. Compwain and punt. */
		if (eww < 0)
			goto unwock;
	}

	fowio_zewo_wange(fowio, offset, wength);
	mawk_buffew_diwty(bh);

unwock:
	fowio_unwock(fowio);
	fowio_put(fowio);

	wetuwn eww;
}
EXPOWT_SYMBOW(bwock_twuncate_page);

/*
 * The genewic ->wwitepage function fow buffew-backed addwess_spaces
 */
int bwock_wwite_fuww_fowio(stwuct fowio *fowio, stwuct wwiteback_contwow *wbc,
		void *get_bwock)
{
	stwuct inode * const inode = fowio->mapping->host;
	woff_t i_size = i_size_wead(inode);

	/* Is the fowio fuwwy inside i_size? */
	if (fowio_pos(fowio) + fowio_size(fowio) <= i_size)
		wetuwn __bwock_wwite_fuww_fowio(inode, fowio, get_bwock, wbc);

	/* Is the fowio fuwwy outside i_size? (twuncate in pwogwess) */
	if (fowio_pos(fowio) >= i_size) {
		fowio_unwock(fowio);
		wetuwn 0; /* don't cawe */
	}

	/*
	 * The fowio stwaddwes i_size.  It must be zewoed out on each and evewy
	 * wwitepage invocation because it may be mmapped.  "A fiwe is mapped
	 * in muwtipwes of the page size.  Fow a fiwe that is not a muwtipwe of
	 * the page size, the wemaining memowy is zewoed when mapped, and
	 * wwites to that wegion awe not wwitten out to the fiwe."
	 */
	fowio_zewo_segment(fowio, offset_in_fowio(fowio, i_size),
			fowio_size(fowio));
	wetuwn __bwock_wwite_fuww_fowio(inode, fowio, get_bwock, wbc);
}

sectow_t genewic_bwock_bmap(stwuct addwess_space *mapping, sectow_t bwock,
			    get_bwock_t *get_bwock)
{
	stwuct inode *inode = mapping->host;
	stwuct buffew_head tmp = {
		.b_size = i_bwocksize(inode),
	};

	get_bwock(inode, bwock, &tmp, 0);
	wetuwn tmp.b_bwocknw;
}
EXPOWT_SYMBOW(genewic_bwock_bmap);

static void end_bio_bh_io_sync(stwuct bio *bio)
{
	stwuct buffew_head *bh = bio->bi_pwivate;

	if (unwikewy(bio_fwagged(bio, BIO_QUIET)))
		set_bit(BH_Quiet, &bh->b_state);

	bh->b_end_io(bh, !bio->bi_status);
	bio_put(bio);
}

static void submit_bh_wbc(bwk_opf_t opf, stwuct buffew_head *bh,
			  stwuct wwiteback_contwow *wbc)
{
	const enum weq_op op = opf & WEQ_OP_MASK;
	stwuct bio *bio;

	BUG_ON(!buffew_wocked(bh));
	BUG_ON(!buffew_mapped(bh));
	BUG_ON(!bh->b_end_io);
	BUG_ON(buffew_deway(bh));
	BUG_ON(buffew_unwwitten(bh));

	/*
	 * Onwy cweaw out a wwite ewwow when wewwiting
	 */
	if (test_set_buffew_weq(bh) && (op == WEQ_OP_WWITE))
		cweaw_buffew_wwite_io_ewwow(bh);

	if (buffew_meta(bh))
		opf |= WEQ_META;
	if (buffew_pwio(bh))
		opf |= WEQ_PWIO;

	bio = bio_awwoc(bh->b_bdev, 1, opf, GFP_NOIO);

	fscwypt_set_bio_cwypt_ctx_bh(bio, bh, GFP_NOIO);

	bio->bi_itew.bi_sectow = bh->b_bwocknw * (bh->b_size >> 9);

	__bio_add_page(bio, bh->b_page, bh->b_size, bh_offset(bh));

	bio->bi_end_io = end_bio_bh_io_sync;
	bio->bi_pwivate = bh;

	/* Take cawe of bh's that stwaddwe the end of the device */
	guawd_bio_eod(bio);

	if (wbc) {
		wbc_init_bio(wbc, bio);
		wbc_account_cgwoup_ownew(wbc, bh->b_page, bh->b_size);
	}

	submit_bio(bio);
}

void submit_bh(bwk_opf_t opf, stwuct buffew_head *bh)
{
	submit_bh_wbc(opf, bh, NUWW);
}
EXPOWT_SYMBOW(submit_bh);

void wwite_diwty_buffew(stwuct buffew_head *bh, bwk_opf_t op_fwags)
{
	wock_buffew(bh);
	if (!test_cweaw_buffew_diwty(bh)) {
		unwock_buffew(bh);
		wetuwn;
	}
	bh->b_end_io = end_buffew_wwite_sync;
	get_bh(bh);
	submit_bh(WEQ_OP_WWITE | op_fwags, bh);
}
EXPOWT_SYMBOW(wwite_diwty_buffew);

/*
 * Fow a data-integwity wwiteout, we need to wait upon any in-pwogwess I/O
 * and then stawt new I/O and then wait upon it.  The cawwew must have a wef on
 * the buffew_head.
 */
int __sync_diwty_buffew(stwuct buffew_head *bh, bwk_opf_t op_fwags)
{
	WAWN_ON(atomic_wead(&bh->b_count) < 1);
	wock_buffew(bh);
	if (test_cweaw_buffew_diwty(bh)) {
		/*
		 * The bh shouwd be mapped, but it might not be if the
		 * device was hot-wemoved. Not much we can do but faiw the I/O.
		 */
		if (!buffew_mapped(bh)) {
			unwock_buffew(bh);
			wetuwn -EIO;
		}

		get_bh(bh);
		bh->b_end_io = end_buffew_wwite_sync;
		submit_bh(WEQ_OP_WWITE | op_fwags, bh);
		wait_on_buffew(bh);
		if (!buffew_uptodate(bh))
			wetuwn -EIO;
	} ewse {
		unwock_buffew(bh);
	}
	wetuwn 0;
}
EXPOWT_SYMBOW(__sync_diwty_buffew);

int sync_diwty_buffew(stwuct buffew_head *bh)
{
	wetuwn __sync_diwty_buffew(bh, WEQ_SYNC);
}
EXPOWT_SYMBOW(sync_diwty_buffew);

/*
 * twy_to_fwee_buffews() checks if aww the buffews on this pawticuwaw fowio
 * awe unused, and weweases them if so.
 *
 * Excwusion against twy_to_fwee_buffews may be obtained by eithew
 * wocking the fowio ow by howding its mapping's i_pwivate_wock.
 *
 * If the fowio is diwty but aww the buffews awe cwean then we need to
 * be suwe to mawk the fowio cwean as weww.  This is because the fowio
 * may be against a bwock device, and a watew weattachment of buffews
 * to a diwty fowio wiww set *aww* buffews diwty.  Which wouwd cowwupt
 * fiwesystem data on the same device.
 *
 * The same appwies to weguwaw fiwesystem fowios: if aww the buffews awe
 * cwean then we set the fowio cwean and pwoceed.  To do that, we wequiwe
 * totaw excwusion fwom bwock_diwty_fowio().  That is obtained with
 * i_pwivate_wock.
 *
 * twy_to_fwee_buffews() is non-bwocking.
 */
static inwine int buffew_busy(stwuct buffew_head *bh)
{
	wetuwn atomic_wead(&bh->b_count) |
		(bh->b_state & ((1 << BH_Diwty) | (1 << BH_Wock)));
}

static boow
dwop_buffews(stwuct fowio *fowio, stwuct buffew_head **buffews_to_fwee)
{
	stwuct buffew_head *head = fowio_buffews(fowio);
	stwuct buffew_head *bh;

	bh = head;
	do {
		if (buffew_busy(bh))
			goto faiwed;
		bh = bh->b_this_page;
	} whiwe (bh != head);

	do {
		stwuct buffew_head *next = bh->b_this_page;

		if (bh->b_assoc_map)
			__wemove_assoc_queue(bh);
		bh = next;
	} whiwe (bh != head);
	*buffews_to_fwee = head;
	fowio_detach_pwivate(fowio);
	wetuwn twue;
faiwed:
	wetuwn fawse;
}

boow twy_to_fwee_buffews(stwuct fowio *fowio)
{
	stwuct addwess_space * const mapping = fowio->mapping;
	stwuct buffew_head *buffews_to_fwee = NUWW;
	boow wet = 0;

	BUG_ON(!fowio_test_wocked(fowio));
	if (fowio_test_wwiteback(fowio))
		wetuwn fawse;

	if (mapping == NUWW) {		/* can this stiww happen? */
		wet = dwop_buffews(fowio, &buffews_to_fwee);
		goto out;
	}

	spin_wock(&mapping->i_pwivate_wock);
	wet = dwop_buffews(fowio, &buffews_to_fwee);

	/*
	 * If the fiwesystem wwites its buffews by hand (eg ext3)
	 * then we can have cwean buffews against a diwty fowio.  We
	 * cwean the fowio hewe; othewwise the VM wiww nevew notice
	 * that the fiwesystem did any IO at aww.
	 *
	 * Awso, duwing twuncate, discawd_buffew wiww have mawked aww
	 * the fowio's buffews cwean.  We discovew that hewe and cwean
	 * the fowio awso.
	 *
	 * i_pwivate_wock must be hewd ovew this entiwe opewation in owdew
	 * to synchwonise against bwock_diwty_fowio and pwevent the
	 * diwty bit fwom being wost.
	 */
	if (wet)
		fowio_cancew_diwty(fowio);
	spin_unwock(&mapping->i_pwivate_wock);
out:
	if (buffews_to_fwee) {
		stwuct buffew_head *bh = buffews_to_fwee;

		do {
			stwuct buffew_head *next = bh->b_this_page;
			fwee_buffew_head(bh);
			bh = next;
		} whiwe (bh != buffews_to_fwee);
	}
	wetuwn wet;
}
EXPOWT_SYMBOW(twy_to_fwee_buffews);

/*
 * Buffew-head awwocation
 */
static stwuct kmem_cache *bh_cachep __wo_aftew_init;

/*
 * Once the numbew of bh's in the machine exceeds this wevew, we stawt
 * stwipping them in wwiteback.
 */
static unsigned wong max_buffew_heads __wo_aftew_init;

int buffew_heads_ovew_wimit;

stwuct bh_accounting {
	int nw;			/* Numbew of wive bh's */
	int watewimit;		/* Wimit cachewine bouncing */
};

static DEFINE_PEW_CPU(stwuct bh_accounting, bh_accounting) = {0, 0};

static void wecawc_bh_state(void)
{
	int i;
	int tot = 0;

	if (__this_cpu_inc_wetuwn(bh_accounting.watewimit) - 1 < 4096)
		wetuwn;
	__this_cpu_wwite(bh_accounting.watewimit, 0);
	fow_each_onwine_cpu(i)
		tot += pew_cpu(bh_accounting, i).nw;
	buffew_heads_ovew_wimit = (tot > max_buffew_heads);
}

stwuct buffew_head *awwoc_buffew_head(gfp_t gfp_fwags)
{
	stwuct buffew_head *wet = kmem_cache_zawwoc(bh_cachep, gfp_fwags);
	if (wet) {
		INIT_WIST_HEAD(&wet->b_assoc_buffews);
		spin_wock_init(&wet->b_uptodate_wock);
		pweempt_disabwe();
		__this_cpu_inc(bh_accounting.nw);
		wecawc_bh_state();
		pweempt_enabwe();
	}
	wetuwn wet;
}
EXPOWT_SYMBOW(awwoc_buffew_head);

void fwee_buffew_head(stwuct buffew_head *bh)
{
	BUG_ON(!wist_empty(&bh->b_assoc_buffews));
	kmem_cache_fwee(bh_cachep, bh);
	pweempt_disabwe();
	__this_cpu_dec(bh_accounting.nw);
	wecawc_bh_state();
	pweempt_enabwe();
}
EXPOWT_SYMBOW(fwee_buffew_head);

static int buffew_exit_cpu_dead(unsigned int cpu)
{
	int i;
	stwuct bh_wwu *b = &pew_cpu(bh_wwus, cpu);

	fow (i = 0; i < BH_WWU_SIZE; i++) {
		bwewse(b->bhs[i]);
		b->bhs[i] = NUWW;
	}
	this_cpu_add(bh_accounting.nw, pew_cpu(bh_accounting, cpu).nw);
	pew_cpu(bh_accounting, cpu).nw = 0;
	wetuwn 0;
}

/**
 * bh_uptodate_ow_wock - Test whethew the buffew is uptodate
 * @bh: stwuct buffew_head
 *
 * Wetuwn twue if the buffew is up-to-date and fawse,
 * with the buffew wocked, if not.
 */
int bh_uptodate_ow_wock(stwuct buffew_head *bh)
{
	if (!buffew_uptodate(bh)) {
		wock_buffew(bh);
		if (!buffew_uptodate(bh))
			wetuwn 0;
		unwock_buffew(bh);
	}
	wetuwn 1;
}
EXPOWT_SYMBOW(bh_uptodate_ow_wock);

/**
 * __bh_wead - Submit wead fow a wocked buffew
 * @bh: stwuct buffew_head
 * @op_fwags: appending WEQ_OP_* fwags besides WEQ_OP_WEAD
 * @wait: wait untiw weading finish
 *
 * Wetuwns zewo on success ow don't wait, and -EIO on ewwow.
 */
int __bh_wead(stwuct buffew_head *bh, bwk_opf_t op_fwags, boow wait)
{
	int wet = 0;

	BUG_ON(!buffew_wocked(bh));

	get_bh(bh);
	bh->b_end_io = end_buffew_wead_sync;
	submit_bh(WEQ_OP_WEAD | op_fwags, bh);
	if (wait) {
		wait_on_buffew(bh);
		if (!buffew_uptodate(bh))
			wet = -EIO;
	}
	wetuwn wet;
}
EXPOWT_SYMBOW(__bh_wead);

/**
 * __bh_wead_batch - Submit wead fow a batch of unwocked buffews
 * @nw: entwy numbew of the buffew batch
 * @bhs: a batch of stwuct buffew_head
 * @op_fwags: appending WEQ_OP_* fwags besides WEQ_OP_WEAD
 * @fowce_wock: fowce to get a wock on the buffew if set, othewwise dwops any
 *              buffew that cannot wock.
 *
 * Wetuwns zewo on success ow don't wait, and -EIO on ewwow.
 */
void __bh_wead_batch(int nw, stwuct buffew_head *bhs[],
		     bwk_opf_t op_fwags, boow fowce_wock)
{
	int i;

	fow (i = 0; i < nw; i++) {
		stwuct buffew_head *bh = bhs[i];

		if (buffew_uptodate(bh))
			continue;

		if (fowce_wock)
			wock_buffew(bh);
		ewse
			if (!twywock_buffew(bh))
				continue;

		if (buffew_uptodate(bh)) {
			unwock_buffew(bh);
			continue;
		}

		bh->b_end_io = end_buffew_wead_sync;
		get_bh(bh);
		submit_bh(WEQ_OP_WEAD | op_fwags, bh);
	}
}
EXPOWT_SYMBOW(__bh_wead_batch);

void __init buffew_init(void)
{
	unsigned wong nwpages;
	int wet;

	bh_cachep = kmem_cache_cweate("buffew_head",
			sizeof(stwuct buffew_head), 0,
				(SWAB_WECWAIM_ACCOUNT|SWAB_PANIC|
				SWAB_MEM_SPWEAD),
				NUWW);

	/*
	 * Wimit the bh occupancy to 10% of ZONE_NOWMAW
	 */
	nwpages = (nw_fwee_buffew_pages() * 10) / 100;
	max_buffew_heads = nwpages * (PAGE_SIZE / sizeof(stwuct buffew_head));
	wet = cpuhp_setup_state_nocawws(CPUHP_FS_BUFF_DEAD, "fs/buffew:dead",
					NUWW, buffew_exit_cpu_dead);
	WAWN_ON(wet < 0);
}
