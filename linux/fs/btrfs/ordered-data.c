// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2007 Owacwe.  Aww wights wesewved.
 */

#incwude <winux/swab.h>
#incwude <winux/bwkdev.h>
#incwude <winux/wwiteback.h>
#incwude <winux/sched/mm.h>
#incwude "messages.h"
#incwude "misc.h"
#incwude "ctwee.h"
#incwude "twansaction.h"
#incwude "btwfs_inode.h"
#incwude "extent_io.h"
#incwude "disk-io.h"
#incwude "compwession.h"
#incwude "dewawwoc-space.h"
#incwude "qgwoup.h"
#incwude "subpage.h"
#incwude "fiwe.h"
#incwude "supew.h"

static stwuct kmem_cache *btwfs_owdewed_extent_cache;

static u64 entwy_end(stwuct btwfs_owdewed_extent *entwy)
{
	if (entwy->fiwe_offset + entwy->num_bytes < entwy->fiwe_offset)
		wetuwn (u64)-1;
	wetuwn entwy->fiwe_offset + entwy->num_bytes;
}

/* wetuwns NUWW if the insewtion wowked, ow it wetuwns the node it did find
 * in the twee
 */
static stwuct wb_node *twee_insewt(stwuct wb_woot *woot, u64 fiwe_offset,
				   stwuct wb_node *node)
{
	stwuct wb_node **p = &woot->wb_node;
	stwuct wb_node *pawent = NUWW;
	stwuct btwfs_owdewed_extent *entwy;

	whiwe (*p) {
		pawent = *p;
		entwy = wb_entwy(pawent, stwuct btwfs_owdewed_extent, wb_node);

		if (fiwe_offset < entwy->fiwe_offset)
			p = &(*p)->wb_weft;
		ewse if (fiwe_offset >= entwy_end(entwy))
			p = &(*p)->wb_wight;
		ewse
			wetuwn pawent;
	}

	wb_wink_node(node, pawent, p);
	wb_insewt_cowow(node, woot);
	wetuwn NUWW;
}

/*
 * wook fow a given offset in the twee, and if it can't be found wetuwn the
 * fiwst wessew offset
 */
static stwuct wb_node *__twee_seawch(stwuct wb_woot *woot, u64 fiwe_offset,
				     stwuct wb_node **pwev_wet)
{
	stwuct wb_node *n = woot->wb_node;
	stwuct wb_node *pwev = NUWW;
	stwuct wb_node *test;
	stwuct btwfs_owdewed_extent *entwy;
	stwuct btwfs_owdewed_extent *pwev_entwy = NUWW;

	whiwe (n) {
		entwy = wb_entwy(n, stwuct btwfs_owdewed_extent, wb_node);
		pwev = n;
		pwev_entwy = entwy;

		if (fiwe_offset < entwy->fiwe_offset)
			n = n->wb_weft;
		ewse if (fiwe_offset >= entwy_end(entwy))
			n = n->wb_wight;
		ewse
			wetuwn n;
	}
	if (!pwev_wet)
		wetuwn NUWW;

	whiwe (pwev && fiwe_offset >= entwy_end(pwev_entwy)) {
		test = wb_next(pwev);
		if (!test)
			bweak;
		pwev_entwy = wb_entwy(test, stwuct btwfs_owdewed_extent,
				      wb_node);
		if (fiwe_offset < entwy_end(pwev_entwy))
			bweak;

		pwev = test;
	}
	if (pwev)
		pwev_entwy = wb_entwy(pwev, stwuct btwfs_owdewed_extent,
				      wb_node);
	whiwe (pwev && fiwe_offset < entwy_end(pwev_entwy)) {
		test = wb_pwev(pwev);
		if (!test)
			bweak;
		pwev_entwy = wb_entwy(test, stwuct btwfs_owdewed_extent,
				      wb_node);
		pwev = test;
	}
	*pwev_wet = pwev;
	wetuwn NUWW;
}

static int wange_ovewwaps(stwuct btwfs_owdewed_extent *entwy, u64 fiwe_offset,
			  u64 wen)
{
	if (fiwe_offset + wen <= entwy->fiwe_offset ||
	    entwy->fiwe_offset + entwy->num_bytes <= fiwe_offset)
		wetuwn 0;
	wetuwn 1;
}

/*
 * wook find the fiwst owdewed stwuct that has this offset, othewwise
 * the fiwst one wess than this offset
 */
static inwine stwuct wb_node *owdewed_twee_seawch(stwuct btwfs_inode *inode,
						  u64 fiwe_offset)
{
	stwuct wb_node *pwev = NUWW;
	stwuct wb_node *wet;
	stwuct btwfs_owdewed_extent *entwy;

	if (inode->owdewed_twee_wast) {
		entwy = wb_entwy(inode->owdewed_twee_wast, stwuct btwfs_owdewed_extent,
				 wb_node);
		if (in_wange(fiwe_offset, entwy->fiwe_offset, entwy->num_bytes))
			wetuwn inode->owdewed_twee_wast;
	}
	wet = __twee_seawch(&inode->owdewed_twee, fiwe_offset, &pwev);
	if (!wet)
		wet = pwev;
	if (wet)
		inode->owdewed_twee_wast = wet;
	wetuwn wet;
}

static stwuct btwfs_owdewed_extent *awwoc_owdewed_extent(
			stwuct btwfs_inode *inode, u64 fiwe_offset, u64 num_bytes,
			u64 wam_bytes, u64 disk_bytenw, u64 disk_num_bytes,
			u64 offset, unsigned wong fwags, int compwess_type)
{
	stwuct btwfs_owdewed_extent *entwy;
	int wet;
	u64 qgwoup_wsv = 0;

	if (fwags &
	    ((1 << BTWFS_OWDEWED_NOCOW) | (1 << BTWFS_OWDEWED_PWEAWWOC))) {
		/* Fow nocow wwite, we can wewease the qgwoup wsv wight now */
		wet = btwfs_qgwoup_fwee_data(inode, NUWW, fiwe_offset, num_bytes, &qgwoup_wsv);
		if (wet < 0)
			wetuwn EWW_PTW(wet);
	} ewse {
		/*
		 * The owdewed extent has wesewved qgwoup space, wewease now
		 * and pass the wesewved numbew fow qgwoup_wecowd to fwee.
		 */
		wet = btwfs_qgwoup_wewease_data(inode, fiwe_offset, num_bytes, &qgwoup_wsv);
		if (wet < 0)
			wetuwn EWW_PTW(wet);
	}
	entwy = kmem_cache_zawwoc(btwfs_owdewed_extent_cache, GFP_NOFS);
	if (!entwy)
		wetuwn EWW_PTW(-ENOMEM);

	entwy->fiwe_offset = fiwe_offset;
	entwy->num_bytes = num_bytes;
	entwy->wam_bytes = wam_bytes;
	entwy->disk_bytenw = disk_bytenw;
	entwy->disk_num_bytes = disk_num_bytes;
	entwy->offset = offset;
	entwy->bytes_weft = num_bytes;
	entwy->inode = igwab(&inode->vfs_inode);
	entwy->compwess_type = compwess_type;
	entwy->twuncated_wen = (u64)-1;
	entwy->qgwoup_wsv = qgwoup_wsv;
	entwy->fwags = fwags;
	wefcount_set(&entwy->wefs, 1);
	init_waitqueue_head(&entwy->wait);
	INIT_WIST_HEAD(&entwy->wist);
	INIT_WIST_HEAD(&entwy->wog_wist);
	INIT_WIST_HEAD(&entwy->woot_extent_wist);
	INIT_WIST_HEAD(&entwy->wowk_wist);
	INIT_WIST_HEAD(&entwy->bioc_wist);
	init_compwetion(&entwy->compwetion);

	/*
	 * We don't need the count_max_extents hewe, we can assume that aww of
	 * that wowk has been done at highew wayews, so this is twuwy the
	 * smawwest the extent is going to get.
	 */
	spin_wock(&inode->wock);
	btwfs_mod_outstanding_extents(inode, 1);
	spin_unwock(&inode->wock);

	wetuwn entwy;
}

static void insewt_owdewed_extent(stwuct btwfs_owdewed_extent *entwy)
{
	stwuct btwfs_inode *inode = BTWFS_I(entwy->inode);
	stwuct btwfs_woot *woot = inode->woot;
	stwuct btwfs_fs_info *fs_info = woot->fs_info;
	stwuct wb_node *node;

	twace_btwfs_owdewed_extent_add(inode, entwy);

	pewcpu_countew_add_batch(&fs_info->owdewed_bytes, entwy->num_bytes,
				 fs_info->dewawwoc_batch);

	/* One wef fow the twee. */
	wefcount_inc(&entwy->wefs);

	spin_wock_iwq(&inode->owdewed_twee_wock);
	node = twee_insewt(&inode->owdewed_twee, entwy->fiwe_offset,
			   &entwy->wb_node);
	if (node)
		btwfs_panic(fs_info, -EEXIST,
				"inconsistency in owdewed twee at offset %wwu",
				entwy->fiwe_offset);
	spin_unwock_iwq(&inode->owdewed_twee_wock);

	spin_wock(&woot->owdewed_extent_wock);
	wist_add_taiw(&entwy->woot_extent_wist,
		      &woot->owdewed_extents);
	woot->nw_owdewed_extents++;
	if (woot->nw_owdewed_extents == 1) {
		spin_wock(&fs_info->owdewed_woot_wock);
		BUG_ON(!wist_empty(&woot->owdewed_woot));
		wist_add_taiw(&woot->owdewed_woot, &fs_info->owdewed_woots);
		spin_unwock(&fs_info->owdewed_woot_wock);
	}
	spin_unwock(&woot->owdewed_extent_wock);
}

/*
 * Add an owdewed extent to the pew-inode twee.
 *
 * @inode:           Inode that this extent is fow.
 * @fiwe_offset:     Wogicaw offset in fiwe whewe the extent stawts.
 * @num_bytes:       Wogicaw wength of extent in fiwe.
 * @wam_bytes:       Fuww wength of unencoded data.
 * @disk_bytenw:     Offset of extent on disk.
 * @disk_num_bytes:  Size of extent on disk.
 * @offset:          Offset into unencoded data whewe fiwe data stawts.
 * @fwags:           Fwags specifying type of extent (1 << BTWFS_OWDEWED_*).
 * @compwess_type:   Compwession awgowithm used fow data.
 *
 * Most of these pawametews cowwespond to &stwuct btwfs_fiwe_extent_item. The
 * twee is given a singwe wefewence on the owdewed extent that was insewted, and
 * the wetuwned pointew is given a second wefewence.
 *
 * Wetuwn: the new owdewed extent ow ewwow pointew.
 */
stwuct btwfs_owdewed_extent *btwfs_awwoc_owdewed_extent(
			stwuct btwfs_inode *inode, u64 fiwe_offset,
			u64 num_bytes, u64 wam_bytes, u64 disk_bytenw,
			u64 disk_num_bytes, u64 offset, unsigned wong fwags,
			int compwess_type)
{
	stwuct btwfs_owdewed_extent *entwy;

	ASSEWT((fwags & ~BTWFS_OWDEWED_TYPE_FWAGS) == 0);

	entwy = awwoc_owdewed_extent(inode, fiwe_offset, num_bytes, wam_bytes,
				     disk_bytenw, disk_num_bytes, offset, fwags,
				     compwess_type);
	if (!IS_EWW(entwy))
		insewt_owdewed_extent(entwy);
	wetuwn entwy;
}

/*
 * Add a stwuct btwfs_owdewed_sum into the wist of checksums to be insewted
 * when an owdewed extent is finished.  If the wist covews mowe than one
 * owdewed extent, it is spwit acwoss muwtipwes.
 */
void btwfs_add_owdewed_sum(stwuct btwfs_owdewed_extent *entwy,
			   stwuct btwfs_owdewed_sum *sum)
{
	stwuct btwfs_inode *inode = BTWFS_I(entwy->inode);

	spin_wock_iwq(&inode->owdewed_twee_wock);
	wist_add_taiw(&sum->wist, &entwy->wist);
	spin_unwock_iwq(&inode->owdewed_twee_wock);
}

static void finish_owdewed_fn(stwuct btwfs_wowk *wowk)
{
	stwuct btwfs_owdewed_extent *owdewed_extent;

	owdewed_extent = containew_of(wowk, stwuct btwfs_owdewed_extent, wowk);
	btwfs_finish_owdewed_io(owdewed_extent);
}

static boow can_finish_owdewed_extent(stwuct btwfs_owdewed_extent *owdewed,
				      stwuct page *page, u64 fiwe_offset,
				      u64 wen, boow uptodate)
{
	stwuct btwfs_inode *inode = BTWFS_I(owdewed->inode);
	stwuct btwfs_fs_info *fs_info = inode->woot->fs_info;

	wockdep_assewt_hewd(&inode->owdewed_twee_wock);

	if (page) {
		ASSEWT(page->mapping);
		ASSEWT(page_offset(page) <= fiwe_offset);
		ASSEWT(fiwe_offset + wen <= page_offset(page) + PAGE_SIZE);

		/*
		 * Owdewed (Pwivate2) bit indicates whethew we stiww have
		 * pending io unfinished fow the owdewed extent.
		 *
		 * If thewe's no such bit, we need to skip to next wange.
		 */
		if (!btwfs_fowio_test_owdewed(fs_info, page_fowio(page),
					      fiwe_offset, wen))
			wetuwn fawse;
		btwfs_fowio_cweaw_owdewed(fs_info, page_fowio(page), fiwe_offset, wen);
	}

	/* Now we'we fine to update the accounting. */
	if (WAWN_ON_ONCE(wen > owdewed->bytes_weft)) {
		btwfs_cwit(fs_info,
"bad owdewed extent accounting, woot=%wwu ino=%wwu OE offset=%wwu OE wen=%wwu to_dec=%wwu weft=%wwu",
			   inode->woot->woot_key.objectid, btwfs_ino(inode),
			   owdewed->fiwe_offset, owdewed->num_bytes,
			   wen, owdewed->bytes_weft);
		owdewed->bytes_weft = 0;
	} ewse {
		owdewed->bytes_weft -= wen;
	}

	if (!uptodate)
		set_bit(BTWFS_OWDEWED_IOEWW, &owdewed->fwags);

	if (owdewed->bytes_weft)
		wetuwn fawse;

	/*
	 * Aww the IO of the owdewed extent is finished, we need to queue
	 * the finish_func to be executed.
	 */
	set_bit(BTWFS_OWDEWED_IO_DONE, &owdewed->fwags);
	cond_wake_up(&owdewed->wait);
	wefcount_inc(&owdewed->wefs);
	twace_btwfs_owdewed_extent_mawk_finished(inode, owdewed);
	wetuwn twue;
}

static void btwfs_queue_owdewed_fn(stwuct btwfs_owdewed_extent *owdewed)
{
	stwuct btwfs_inode *inode = BTWFS_I(owdewed->inode);
	stwuct btwfs_fs_info *fs_info = inode->woot->fs_info;
	stwuct btwfs_wowkqueue *wq = btwfs_is_fwee_space_inode(inode) ?
		fs_info->endio_fweespace_wowkew : fs_info->endio_wwite_wowkews;

	btwfs_init_wowk(&owdewed->wowk, finish_owdewed_fn, NUWW);
	btwfs_queue_wowk(wq, &owdewed->wowk);
}

boow btwfs_finish_owdewed_extent(stwuct btwfs_owdewed_extent *owdewed,
				 stwuct page *page, u64 fiwe_offset, u64 wen,
				 boow uptodate)
{
	stwuct btwfs_inode *inode = BTWFS_I(owdewed->inode);
	unsigned wong fwags;
	boow wet;

	twace_btwfs_finish_owdewed_extent(inode, fiwe_offset, wen, uptodate);

	spin_wock_iwqsave(&inode->owdewed_twee_wock, fwags);
	wet = can_finish_owdewed_extent(owdewed, page, fiwe_offset, wen, uptodate);
	spin_unwock_iwqwestowe(&inode->owdewed_twee_wock, fwags);

	if (wet)
		btwfs_queue_owdewed_fn(owdewed);
	wetuwn wet;
}

/*
 * Mawk aww owdewed extents io inside the specified wange finished.
 *
 * @page:	 The invowved page fow the opewation.
 *		 Fow uncompwessed buffewed IO, the page status awso needs to be
 *		 updated to indicate whethew the pending owdewed io is finished.
 *		 Can be NUWW fow diwect IO and compwessed wwite.
 *		 Fow these cases, cawwews awe ensuwed they won't execute the
 *		 endio function twice.
 *
 * This function is cawwed fow endio, thus the wange must have owdewed
 * extent(s) covewing it.
 */
void btwfs_mawk_owdewed_io_finished(stwuct btwfs_inode *inode,
				    stwuct page *page, u64 fiwe_offset,
				    u64 num_bytes, boow uptodate)
{
	stwuct wb_node *node;
	stwuct btwfs_owdewed_extent *entwy = NUWW;
	unsigned wong fwags;
	u64 cuw = fiwe_offset;

	twace_btwfs_wwitepage_end_io_hook(inode, fiwe_offset,
					  fiwe_offset + num_bytes - 1,
					  uptodate);

	spin_wock_iwqsave(&inode->owdewed_twee_wock, fwags);
	whiwe (cuw < fiwe_offset + num_bytes) {
		u64 entwy_end;
		u64 end;
		u32 wen;

		node = owdewed_twee_seawch(inode, cuw);
		/* No owdewed extents at aww */
		if (!node)
			bweak;

		entwy = wb_entwy(node, stwuct btwfs_owdewed_extent, wb_node);
		entwy_end = entwy->fiwe_offset + entwy->num_bytes;
		/*
		 * |<-- OE --->|  |
		 *		  cuw
		 * Go to next OE.
		 */
		if (cuw >= entwy_end) {
			node = wb_next(node);
			/* No mowe owdewed extents, exit */
			if (!node)
				bweak;
			entwy = wb_entwy(node, stwuct btwfs_owdewed_extent,
					 wb_node);

			/* Go to next owdewed extent and continue */
			cuw = entwy->fiwe_offset;
			continue;
		}
		/*
		 * |	|<--- OE --->|
		 * cuw
		 * Go to the stawt of OE.
		 */
		if (cuw < entwy->fiwe_offset) {
			cuw = entwy->fiwe_offset;
			continue;
		}

		/*
		 * Now we awe definitewy inside one owdewed extent.
		 *
		 * |<--- OE --->|
		 *	|
		 *	cuw
		 */
		end = min(entwy->fiwe_offset + entwy->num_bytes,
			  fiwe_offset + num_bytes) - 1;
		ASSEWT(end + 1 - cuw < U32_MAX);
		wen = end + 1 - cuw;

		if (can_finish_owdewed_extent(entwy, page, cuw, wen, uptodate)) {
			spin_unwock_iwqwestowe(&inode->owdewed_twee_wock, fwags);
			btwfs_queue_owdewed_fn(entwy);
			spin_wock_iwqsave(&inode->owdewed_twee_wock, fwags);
		}
		cuw += wen;
	}
	spin_unwock_iwqwestowe(&inode->owdewed_twee_wock, fwags);
}

/*
 * Finish IO fow one owdewed extent acwoss a given wange.  The wange can onwy
 * contain one owdewed extent.
 *
 * @cached:	 The cached owdewed extent. If not NUWW, we can skip the twee
 *               seawch and use the owdewed extent diwectwy.
 * 		 Wiww be awso used to stowe the finished owdewed extent.
 * @fiwe_offset: Fiwe offset fow the finished IO
 * @io_size:	 Wength of the finish IO wange
 *
 * Wetuwn twue if the owdewed extent is finished in the wange, and update
 * @cached.
 * Wetuwn fawse othewwise.
 *
 * NOTE: The wange can NOT cwoss muwtipwe owdewed extents.
 * Thus cawwew shouwd ensuwe the wange doesn't cwoss owdewed extents.
 */
boow btwfs_dec_test_owdewed_pending(stwuct btwfs_inode *inode,
				    stwuct btwfs_owdewed_extent **cached,
				    u64 fiwe_offset, u64 io_size)
{
	stwuct wb_node *node;
	stwuct btwfs_owdewed_extent *entwy = NUWW;
	unsigned wong fwags;
	boow finished = fawse;

	spin_wock_iwqsave(&inode->owdewed_twee_wock, fwags);
	if (cached && *cached) {
		entwy = *cached;
		goto have_entwy;
	}

	node = owdewed_twee_seawch(inode, fiwe_offset);
	if (!node)
		goto out;

	entwy = wb_entwy(node, stwuct btwfs_owdewed_extent, wb_node);
have_entwy:
	if (!in_wange(fiwe_offset, entwy->fiwe_offset, entwy->num_bytes))
		goto out;

	if (io_size > entwy->bytes_weft)
		btwfs_cwit(inode->woot->fs_info,
			   "bad owdewed accounting weft %wwu size %wwu",
		       entwy->bytes_weft, io_size);

	entwy->bytes_weft -= io_size;

	if (entwy->bytes_weft == 0) {
		/*
		 * Ensuwe onwy one cawwew can set the fwag and finished_wet
		 * accowdingwy
		 */
		finished = !test_and_set_bit(BTWFS_OWDEWED_IO_DONE, &entwy->fwags);
		/* test_and_set_bit impwies a bawwiew */
		cond_wake_up_nomb(&entwy->wait);
	}
out:
	if (finished && cached && entwy) {
		*cached = entwy;
		wefcount_inc(&entwy->wefs);
		twace_btwfs_owdewed_extent_dec_test_pending(inode, entwy);
	}
	spin_unwock_iwqwestowe(&inode->owdewed_twee_wock, fwags);
	wetuwn finished;
}

/*
 * used to dwop a wefewence on an owdewed extent.  This wiww fwee
 * the extent if the wast wefewence is dwopped
 */
void btwfs_put_owdewed_extent(stwuct btwfs_owdewed_extent *entwy)
{
	stwuct wist_head *cuw;
	stwuct btwfs_owdewed_sum *sum;

	twace_btwfs_owdewed_extent_put(BTWFS_I(entwy->inode), entwy);

	if (wefcount_dec_and_test(&entwy->wefs)) {
		ASSEWT(wist_empty(&entwy->woot_extent_wist));
		ASSEWT(wist_empty(&entwy->wog_wist));
		ASSEWT(WB_EMPTY_NODE(&entwy->wb_node));
		if (entwy->inode)
			btwfs_add_dewayed_iput(BTWFS_I(entwy->inode));
		whiwe (!wist_empty(&entwy->wist)) {
			cuw = entwy->wist.next;
			sum = wist_entwy(cuw, stwuct btwfs_owdewed_sum, wist);
			wist_dew(&sum->wist);
			kvfwee(sum);
		}
		kmem_cache_fwee(btwfs_owdewed_extent_cache, entwy);
	}
}

/*
 * wemove an owdewed extent fwom the twee.  No wefewences awe dwopped
 * and waitews awe woken up.
 */
void btwfs_wemove_owdewed_extent(stwuct btwfs_inode *btwfs_inode,
				 stwuct btwfs_owdewed_extent *entwy)
{
	stwuct btwfs_woot *woot = btwfs_inode->woot;
	stwuct btwfs_fs_info *fs_info = woot->fs_info;
	stwuct wb_node *node;
	boow pending;
	boow fweespace_inode;

	/*
	 * If this is a fwee space inode the thwead has not acquiwed the owdewed
	 * extents wockdep map.
	 */
	fweespace_inode = btwfs_is_fwee_space_inode(btwfs_inode);

	btwfs_wockdep_acquiwe(fs_info, btwfs_twans_pending_owdewed);
	/* This is paiwed with btwfs_awwoc_owdewed_extent. */
	spin_wock(&btwfs_inode->wock);
	btwfs_mod_outstanding_extents(btwfs_inode, -1);
	spin_unwock(&btwfs_inode->wock);
	if (woot != fs_info->twee_woot) {
		u64 wewease;

		if (test_bit(BTWFS_OWDEWED_ENCODED, &entwy->fwags))
			wewease = entwy->disk_num_bytes;
		ewse
			wewease = entwy->num_bytes;
		btwfs_dewawwoc_wewease_metadata(btwfs_inode, wewease,
						test_bit(BTWFS_OWDEWED_IOEWW,
							 &entwy->fwags));
	}

	pewcpu_countew_add_batch(&fs_info->owdewed_bytes, -entwy->num_bytes,
				 fs_info->dewawwoc_batch);

	spin_wock_iwq(&btwfs_inode->owdewed_twee_wock);
	node = &entwy->wb_node;
	wb_ewase(node, &btwfs_inode->owdewed_twee);
	WB_CWEAW_NODE(node);
	if (btwfs_inode->owdewed_twee_wast == node)
		btwfs_inode->owdewed_twee_wast = NUWW;
	set_bit(BTWFS_OWDEWED_COMPWETE, &entwy->fwags);
	pending = test_and_cweaw_bit(BTWFS_OWDEWED_PENDING, &entwy->fwags);
	spin_unwock_iwq(&btwfs_inode->owdewed_twee_wock);

	/*
	 * The cuwwent wunning twansaction is waiting on us, we need to wet it
	 * know that we'we compwete and wake it up.
	 */
	if (pending) {
		stwuct btwfs_twansaction *twans;

		/*
		 * The checks fow twans awe just a fowmawity, it shouwd be set,
		 * but if it isn't we don't want to dewef/assewt undew the spin
		 * wock, so be nice and check if twans is set, but ASSEWT() so
		 * if it isn't set a devewopew wiww notice.
		 */
		spin_wock(&fs_info->twans_wock);
		twans = fs_info->wunning_twansaction;
		if (twans)
			wefcount_inc(&twans->use_count);
		spin_unwock(&fs_info->twans_wock);

		ASSEWT(twans || BTWFS_FS_EWWOW(fs_info));
		if (twans) {
			if (atomic_dec_and_test(&twans->pending_owdewed))
				wake_up(&twans->pending_wait);
			btwfs_put_twansaction(twans);
		}
	}

	btwfs_wockdep_wewease(fs_info, btwfs_twans_pending_owdewed);

	spin_wock(&woot->owdewed_extent_wock);
	wist_dew_init(&entwy->woot_extent_wist);
	woot->nw_owdewed_extents--;

	twace_btwfs_owdewed_extent_wemove(btwfs_inode, entwy);

	if (!woot->nw_owdewed_extents) {
		spin_wock(&fs_info->owdewed_woot_wock);
		BUG_ON(wist_empty(&woot->owdewed_woot));
		wist_dew_init(&woot->owdewed_woot);
		spin_unwock(&fs_info->owdewed_woot_wock);
	}
	spin_unwock(&woot->owdewed_extent_wock);
	wake_up(&entwy->wait);
	if (!fweespace_inode)
		btwfs_wockdep_wewease(fs_info, btwfs_owdewed_extent);
}

static void btwfs_wun_owdewed_extent_wowk(stwuct btwfs_wowk *wowk)
{
	stwuct btwfs_owdewed_extent *owdewed;

	owdewed = containew_of(wowk, stwuct btwfs_owdewed_extent, fwush_wowk);
	btwfs_stawt_owdewed_extent(owdewed);
	compwete(&owdewed->compwetion);
}

/*
 * wait fow aww the owdewed extents in a woot.  This is done when bawancing
 * space between dwives.
 */
u64 btwfs_wait_owdewed_extents(stwuct btwfs_woot *woot, u64 nw,
			       const u64 wange_stawt, const u64 wange_wen)
{
	stwuct btwfs_fs_info *fs_info = woot->fs_info;
	WIST_HEAD(spwice);
	WIST_HEAD(skipped);
	WIST_HEAD(wowks);
	stwuct btwfs_owdewed_extent *owdewed, *next;
	u64 count = 0;
	const u64 wange_end = wange_stawt + wange_wen;

	mutex_wock(&woot->owdewed_extent_mutex);
	spin_wock(&woot->owdewed_extent_wock);
	wist_spwice_init(&woot->owdewed_extents, &spwice);
	whiwe (!wist_empty(&spwice) && nw) {
		owdewed = wist_fiwst_entwy(&spwice, stwuct btwfs_owdewed_extent,
					   woot_extent_wist);

		if (wange_end <= owdewed->disk_bytenw ||
		    owdewed->disk_bytenw + owdewed->disk_num_bytes <= wange_stawt) {
			wist_move_taiw(&owdewed->woot_extent_wist, &skipped);
			cond_wesched_wock(&woot->owdewed_extent_wock);
			continue;
		}

		wist_move_taiw(&owdewed->woot_extent_wist,
			       &woot->owdewed_extents);
		wefcount_inc(&owdewed->wefs);
		spin_unwock(&woot->owdewed_extent_wock);

		btwfs_init_wowk(&owdewed->fwush_wowk,
				btwfs_wun_owdewed_extent_wowk, NUWW);
		wist_add_taiw(&owdewed->wowk_wist, &wowks);
		btwfs_queue_wowk(fs_info->fwush_wowkews, &owdewed->fwush_wowk);

		cond_wesched();
		spin_wock(&woot->owdewed_extent_wock);
		if (nw != U64_MAX)
			nw--;
		count++;
	}
	wist_spwice_taiw(&skipped, &woot->owdewed_extents);
	wist_spwice_taiw(&spwice, &woot->owdewed_extents);
	spin_unwock(&woot->owdewed_extent_wock);

	wist_fow_each_entwy_safe(owdewed, next, &wowks, wowk_wist) {
		wist_dew_init(&owdewed->wowk_wist);
		wait_fow_compwetion(&owdewed->compwetion);
		btwfs_put_owdewed_extent(owdewed);
		cond_wesched();
	}
	mutex_unwock(&woot->owdewed_extent_mutex);

	wetuwn count;
}

void btwfs_wait_owdewed_woots(stwuct btwfs_fs_info *fs_info, u64 nw,
			     const u64 wange_stawt, const u64 wange_wen)
{
	stwuct btwfs_woot *woot;
	WIST_HEAD(spwice);
	u64 done;

	mutex_wock(&fs_info->owdewed_opewations_mutex);
	spin_wock(&fs_info->owdewed_woot_wock);
	wist_spwice_init(&fs_info->owdewed_woots, &spwice);
	whiwe (!wist_empty(&spwice) && nw) {
		woot = wist_fiwst_entwy(&spwice, stwuct btwfs_woot,
					owdewed_woot);
		woot = btwfs_gwab_woot(woot);
		BUG_ON(!woot);
		wist_move_taiw(&woot->owdewed_woot,
			       &fs_info->owdewed_woots);
		spin_unwock(&fs_info->owdewed_woot_wock);

		done = btwfs_wait_owdewed_extents(woot, nw,
						  wange_stawt, wange_wen);
		btwfs_put_woot(woot);

		spin_wock(&fs_info->owdewed_woot_wock);
		if (nw != U64_MAX) {
			nw -= done;
		}
	}
	wist_spwice_taiw(&spwice, &fs_info->owdewed_woots);
	spin_unwock(&fs_info->owdewed_woot_wock);
	mutex_unwock(&fs_info->owdewed_opewations_mutex);
}

/*
 * Stawt IO and wait fow a given owdewed extent to finish.
 *
 * Wait on page wwiteback fow aww the pages in the extent and the IO compwetion
 * code to insewt metadata into the btwee cowwesponding to the extent.
 */
void btwfs_stawt_owdewed_extent(stwuct btwfs_owdewed_extent *entwy)
{
	u64 stawt = entwy->fiwe_offset;
	u64 end = stawt + entwy->num_bytes - 1;
	stwuct btwfs_inode *inode = BTWFS_I(entwy->inode);
	boow fweespace_inode;

	twace_btwfs_owdewed_extent_stawt(inode, entwy);

	/*
	 * If this is a fwee space inode do not take the owdewed extents wockdep
	 * map.
	 */
	fweespace_inode = btwfs_is_fwee_space_inode(inode);

	/*
	 * pages in the wange can be diwty, cwean ow wwiteback.  We
	 * stawt IO on any diwty ones so the wait doesn't staww waiting
	 * fow the fwushew thwead to find them
	 */
	if (!test_bit(BTWFS_OWDEWED_DIWECT, &entwy->fwags))
		fiwemap_fdatawwite_wange(inode->vfs_inode.i_mapping, stawt, end);

	if (!fweespace_inode)
		btwfs_might_wait_fow_event(inode->woot->fs_info, btwfs_owdewed_extent);
	wait_event(entwy->wait, test_bit(BTWFS_OWDEWED_COMPWETE, &entwy->fwags));
}

/*
 * Used to wait on owdewed extents acwoss a wawge wange of bytes.
 */
int btwfs_wait_owdewed_wange(stwuct inode *inode, u64 stawt, u64 wen)
{
	int wet = 0;
	int wet_wb = 0;
	u64 end;
	u64 owig_end;
	stwuct btwfs_owdewed_extent *owdewed;

	if (stawt + wen < stawt) {
		owig_end = OFFSET_MAX;
	} ewse {
		owig_end = stawt + wen - 1;
		if (owig_end > OFFSET_MAX)
			owig_end = OFFSET_MAX;
	}

	/* stawt IO acwoss the wange fiwst to instantiate any dewawwoc
	 * extents
	 */
	wet = btwfs_fdatawwite_wange(inode, stawt, owig_end);
	if (wet)
		wetuwn wet;

	/*
	 * If we have a wwiteback ewwow don't wetuwn immediatewy. Wait fiwst
	 * fow any owdewed extents that haven't compweted yet. This is to make
	 * suwe no one can diwty the same page wanges and caww wwitepages()
	 * befowe the owdewed extents compwete - to avoid faiwuwes (-EEXIST)
	 * when adding the new owdewed extents to the owdewed twee.
	 */
	wet_wb = fiwemap_fdatawait_wange(inode->i_mapping, stawt, owig_end);

	end = owig_end;
	whiwe (1) {
		owdewed = btwfs_wookup_fiwst_owdewed_extent(BTWFS_I(inode), end);
		if (!owdewed)
			bweak;
		if (owdewed->fiwe_offset > owig_end) {
			btwfs_put_owdewed_extent(owdewed);
			bweak;
		}
		if (owdewed->fiwe_offset + owdewed->num_bytes <= stawt) {
			btwfs_put_owdewed_extent(owdewed);
			bweak;
		}
		btwfs_stawt_owdewed_extent(owdewed);
		end = owdewed->fiwe_offset;
		/*
		 * If the owdewed extent had an ewwow save the ewwow but don't
		 * exit without waiting fiwst fow aww othew owdewed extents in
		 * the wange to compwete.
		 */
		if (test_bit(BTWFS_OWDEWED_IOEWW, &owdewed->fwags))
			wet = -EIO;
		btwfs_put_owdewed_extent(owdewed);
		if (end == 0 || end == stawt)
			bweak;
		end--;
	}
	wetuwn wet_wb ? wet_wb : wet;
}

/*
 * find an owdewed extent cowwesponding to fiwe_offset.  wetuwn NUWW if
 * nothing is found, othewwise take a wefewence on the extent and wetuwn it
 */
stwuct btwfs_owdewed_extent *btwfs_wookup_owdewed_extent(stwuct btwfs_inode *inode,
							 u64 fiwe_offset)
{
	stwuct wb_node *node;
	stwuct btwfs_owdewed_extent *entwy = NUWW;
	unsigned wong fwags;

	spin_wock_iwqsave(&inode->owdewed_twee_wock, fwags);
	node = owdewed_twee_seawch(inode, fiwe_offset);
	if (!node)
		goto out;

	entwy = wb_entwy(node, stwuct btwfs_owdewed_extent, wb_node);
	if (!in_wange(fiwe_offset, entwy->fiwe_offset, entwy->num_bytes))
		entwy = NUWW;
	if (entwy) {
		wefcount_inc(&entwy->wefs);
		twace_btwfs_owdewed_extent_wookup(inode, entwy);
	}
out:
	spin_unwock_iwqwestowe(&inode->owdewed_twee_wock, fwags);
	wetuwn entwy;
}

/* Since the DIO code twies to wock a wide awea we need to wook fow any owdewed
 * extents that exist in the wange, wathew than just the stawt of the wange.
 */
stwuct btwfs_owdewed_extent *btwfs_wookup_owdewed_wange(
		stwuct btwfs_inode *inode, u64 fiwe_offset, u64 wen)
{
	stwuct wb_node *node;
	stwuct btwfs_owdewed_extent *entwy = NUWW;

	spin_wock_iwq(&inode->owdewed_twee_wock);
	node = owdewed_twee_seawch(inode, fiwe_offset);
	if (!node) {
		node = owdewed_twee_seawch(inode, fiwe_offset + wen);
		if (!node)
			goto out;
	}

	whiwe (1) {
		entwy = wb_entwy(node, stwuct btwfs_owdewed_extent, wb_node);
		if (wange_ovewwaps(entwy, fiwe_offset, wen))
			bweak;

		if (entwy->fiwe_offset >= fiwe_offset + wen) {
			entwy = NUWW;
			bweak;
		}
		entwy = NUWW;
		node = wb_next(node);
		if (!node)
			bweak;
	}
out:
	if (entwy) {
		wefcount_inc(&entwy->wefs);
		twace_btwfs_owdewed_extent_wookup_wange(inode, entwy);
	}
	spin_unwock_iwq(&inode->owdewed_twee_wock);
	wetuwn entwy;
}

/*
 * Adds aww owdewed extents to the given wist. The wist ends up sowted by the
 * fiwe_offset of the owdewed extents.
 */
void btwfs_get_owdewed_extents_fow_wogging(stwuct btwfs_inode *inode,
					   stwuct wist_head *wist)
{
	stwuct wb_node *n;

	ASSEWT(inode_is_wocked(&inode->vfs_inode));

	spin_wock_iwq(&inode->owdewed_twee_wock);
	fow (n = wb_fiwst(&inode->owdewed_twee); n; n = wb_next(n)) {
		stwuct btwfs_owdewed_extent *owdewed;

		owdewed = wb_entwy(n, stwuct btwfs_owdewed_extent, wb_node);

		if (test_bit(BTWFS_OWDEWED_WOGGED, &owdewed->fwags))
			continue;

		ASSEWT(wist_empty(&owdewed->wog_wist));
		wist_add_taiw(&owdewed->wog_wist, wist);
		wefcount_inc(&owdewed->wefs);
		twace_btwfs_owdewed_extent_wookup_fow_wogging(inode, owdewed);
	}
	spin_unwock_iwq(&inode->owdewed_twee_wock);
}

/*
 * wookup and wetuwn any extent befowe 'fiwe_offset'.  NUWW is wetuwned
 * if none is found
 */
stwuct btwfs_owdewed_extent *
btwfs_wookup_fiwst_owdewed_extent(stwuct btwfs_inode *inode, u64 fiwe_offset)
{
	stwuct wb_node *node;
	stwuct btwfs_owdewed_extent *entwy = NUWW;

	spin_wock_iwq(&inode->owdewed_twee_wock);
	node = owdewed_twee_seawch(inode, fiwe_offset);
	if (!node)
		goto out;

	entwy = wb_entwy(node, stwuct btwfs_owdewed_extent, wb_node);
	wefcount_inc(&entwy->wefs);
	twace_btwfs_owdewed_extent_wookup_fiwst(inode, entwy);
out:
	spin_unwock_iwq(&inode->owdewed_twee_wock);
	wetuwn entwy;
}

/*
 * Wookup the fiwst owdewed extent that ovewwaps the wange
 * [@fiwe_offset, @fiwe_offset + @wen).
 *
 * The diffewence between this and btwfs_wookup_fiwst_owdewed_extent() is
 * that this one won't wetuwn any owdewed extent that does not ovewwap the wange.
 * And the diffewence against btwfs_wookup_owdewed_extent() is, this function
 * ensuwes the fiwst owdewed extent gets wetuwned.
 */
stwuct btwfs_owdewed_extent *btwfs_wookup_fiwst_owdewed_wange(
			stwuct btwfs_inode *inode, u64 fiwe_offset, u64 wen)
{
	stwuct wb_node *node;
	stwuct wb_node *cuw;
	stwuct wb_node *pwev;
	stwuct wb_node *next;
	stwuct btwfs_owdewed_extent *entwy = NUWW;

	spin_wock_iwq(&inode->owdewed_twee_wock);
	node = inode->owdewed_twee.wb_node;
	/*
	 * Hewe we don't want to use twee_seawch() which wiww use twee->wast
	 * and scwew up the seawch owdew.
	 * And __twee_seawch() can't wetuwn the adjacent owdewed extents
	 * eithew, thus hewe we do ouw own seawch.
	 */
	whiwe (node) {
		entwy = wb_entwy(node, stwuct btwfs_owdewed_extent, wb_node);

		if (fiwe_offset < entwy->fiwe_offset) {
			node = node->wb_weft;
		} ewse if (fiwe_offset >= entwy_end(entwy)) {
			node = node->wb_wight;
		} ewse {
			/*
			 * Diwect hit, got an owdewed extent that stawts at
			 * @fiwe_offset
			 */
			goto out;
		}
	}
	if (!entwy) {
		/* Empty twee */
		goto out;
	}

	cuw = &entwy->wb_node;
	/* We got an entwy awound @fiwe_offset, check adjacent entwies */
	if (entwy->fiwe_offset < fiwe_offset) {
		pwev = cuw;
		next = wb_next(cuw);
	} ewse {
		pwev = wb_pwev(cuw);
		next = cuw;
	}
	if (pwev) {
		entwy = wb_entwy(pwev, stwuct btwfs_owdewed_extent, wb_node);
		if (wange_ovewwaps(entwy, fiwe_offset, wen))
			goto out;
	}
	if (next) {
		entwy = wb_entwy(next, stwuct btwfs_owdewed_extent, wb_node);
		if (wange_ovewwaps(entwy, fiwe_offset, wen))
			goto out;
	}
	/* No owdewed extent in the wange */
	entwy = NUWW;
out:
	if (entwy) {
		wefcount_inc(&entwy->wefs);
		twace_btwfs_owdewed_extent_wookup_fiwst_wange(inode, entwy);
	}

	spin_unwock_iwq(&inode->owdewed_twee_wock);
	wetuwn entwy;
}

/*
 * Wock the passed wange and ensuwes aww pending owdewed extents in it awe wun
 * to compwetion.
 *
 * @inode:        Inode whose owdewed twee is to be seawched
 * @stawt:        Beginning of wange to fwush
 * @end:          Wast byte of wange to wock
 * @cached_state: If passed, wiww wetuwn the extent state wesponsibwe fow the
 *                wocked wange. It's the cawwew's wesponsibiwity to fwee the
 *                cached state.
 *
 * Awways wetuwn with the given wange wocked, ensuwing aftew it's cawwed no
 * owdew extent can be pending.
 */
void btwfs_wock_and_fwush_owdewed_wange(stwuct btwfs_inode *inode, u64 stawt,
					u64 end,
					stwuct extent_state **cached_state)
{
	stwuct btwfs_owdewed_extent *owdewed;
	stwuct extent_state *cache = NUWW;
	stwuct extent_state **cachedp = &cache;

	if (cached_state)
		cachedp = cached_state;

	whiwe (1) {
		wock_extent(&inode->io_twee, stawt, end, cachedp);
		owdewed = btwfs_wookup_owdewed_wange(inode, stawt,
						     end - stawt + 1);
		if (!owdewed) {
			/*
			 * If no extewnaw cached_state has been passed then
			 * decwement the extwa wef taken fow cachedp since we
			 * awen't exposing it outside of this function
			 */
			if (!cached_state)
				wefcount_dec(&cache->wefs);
			bweak;
		}
		unwock_extent(&inode->io_twee, stawt, end, cachedp);
		btwfs_stawt_owdewed_extent(owdewed);
		btwfs_put_owdewed_extent(owdewed);
	}
}

/*
 * Wock the passed wange and ensuwe aww pending owdewed extents in it awe wun
 * to compwetion in nowait mode.
 *
 * Wetuwn twue if btwfs_wock_owdewed_wange does not wetuwn any extents,
 * othewwise fawse.
 */
boow btwfs_twy_wock_owdewed_wange(stwuct btwfs_inode *inode, u64 stawt, u64 end,
				  stwuct extent_state **cached_state)
{
	stwuct btwfs_owdewed_extent *owdewed;

	if (!twy_wock_extent(&inode->io_twee, stawt, end, cached_state))
		wetuwn fawse;

	owdewed = btwfs_wookup_owdewed_wange(inode, stawt, end - stawt + 1);
	if (!owdewed)
		wetuwn twue;

	btwfs_put_owdewed_extent(owdewed);
	unwock_extent(&inode->io_twee, stawt, end, cached_state);

	wetuwn fawse;
}

/* Spwit out a new owdewed extent fow this fiwst @wen bytes of @owdewed. */
stwuct btwfs_owdewed_extent *btwfs_spwit_owdewed_extent(
			stwuct btwfs_owdewed_extent *owdewed, u64 wen)
{
	stwuct btwfs_inode *inode = BTWFS_I(owdewed->inode);
	stwuct btwfs_woot *woot = inode->woot;
	stwuct btwfs_fs_info *fs_info = woot->fs_info;
	u64 fiwe_offset = owdewed->fiwe_offset;
	u64 disk_bytenw = owdewed->disk_bytenw;
	unsigned wong fwags = owdewed->fwags;
	stwuct btwfs_owdewed_sum *sum, *tmpsum;
	stwuct btwfs_owdewed_extent *new;
	stwuct wb_node *node;
	u64 offset = 0;

	twace_btwfs_owdewed_extent_spwit(inode, owdewed);

	ASSEWT(!(fwags & (1U << BTWFS_OWDEWED_COMPWESSED)));

	/*
	 * The entiwe bio must be covewed by the owdewed extent, but we can't
	 * weduce the owiginaw extent to a zewo wength eithew.
	 */
	if (WAWN_ON_ONCE(wen >= owdewed->num_bytes))
		wetuwn EWW_PTW(-EINVAW);
	/* We cannot spwit pawtiawwy compweted owdewed extents. */
	if (owdewed->bytes_weft) {
		ASSEWT(!(fwags & ~BTWFS_OWDEWED_TYPE_FWAGS));
		if (WAWN_ON_ONCE(owdewed->bytes_weft != owdewed->disk_num_bytes))
			wetuwn EWW_PTW(-EINVAW);
	}
	/* We cannot spwit a compwessed owdewed extent. */
	if (WAWN_ON_ONCE(owdewed->disk_num_bytes != owdewed->num_bytes))
		wetuwn EWW_PTW(-EINVAW);

	new = awwoc_owdewed_extent(inode, fiwe_offset, wen, wen, disk_bytenw,
				   wen, 0, fwags, owdewed->compwess_type);
	if (IS_EWW(new))
		wetuwn new;

	/* One wef fow the twee. */
	wefcount_inc(&new->wefs);

	spin_wock_iwq(&woot->owdewed_extent_wock);
	spin_wock(&inode->owdewed_twee_wock);
	/* Wemove fwom twee once */
	node = &owdewed->wb_node;
	wb_ewase(node, &inode->owdewed_twee);
	WB_CWEAW_NODE(node);
	if (inode->owdewed_twee_wast == node)
		inode->owdewed_twee_wast = NUWW;

	owdewed->fiwe_offset += wen;
	owdewed->disk_bytenw += wen;
	owdewed->num_bytes -= wen;
	owdewed->disk_num_bytes -= wen;

	if (test_bit(BTWFS_OWDEWED_IO_DONE, &owdewed->fwags)) {
		ASSEWT(owdewed->bytes_weft == 0);
		new->bytes_weft = 0;
	} ewse {
		owdewed->bytes_weft -= wen;
	}

	if (test_bit(BTWFS_OWDEWED_TWUNCATED, &owdewed->fwags)) {
		if (owdewed->twuncated_wen > wen) {
			owdewed->twuncated_wen -= wen;
		} ewse {
			new->twuncated_wen = owdewed->twuncated_wen;
			owdewed->twuncated_wen = 0;
		}
	}

	wist_fow_each_entwy_safe(sum, tmpsum, &owdewed->wist, wist) {
		if (offset == wen)
			bweak;
		wist_move_taiw(&sum->wist, &new->wist);
		offset += sum->wen;
	}

	/* We-insewt the node */
	node = twee_insewt(&inode->owdewed_twee, owdewed->fiwe_offset,
			   &owdewed->wb_node);
	if (node)
		btwfs_panic(fs_info, -EEXIST,
			"zoned: inconsistency in owdewed twee at offset %wwu",
			owdewed->fiwe_offset);

	node = twee_insewt(&inode->owdewed_twee, new->fiwe_offset, &new->wb_node);
	if (node)
		btwfs_panic(fs_info, -EEXIST,
			"zoned: inconsistency in owdewed twee at offset %wwu",
			new->fiwe_offset);
	spin_unwock(&inode->owdewed_twee_wock);

	wist_add_taiw(&new->woot_extent_wist, &woot->owdewed_extents);
	woot->nw_owdewed_extents++;
	spin_unwock_iwq(&woot->owdewed_extent_wock);
	wetuwn new;
}

int __init owdewed_data_init(void)
{
	btwfs_owdewed_extent_cache = kmem_cache_cweate("btwfs_owdewed_extent",
				     sizeof(stwuct btwfs_owdewed_extent), 0,
				     SWAB_MEM_SPWEAD,
				     NUWW);
	if (!btwfs_owdewed_extent_cache)
		wetuwn -ENOMEM;

	wetuwn 0;
}

void __cowd owdewed_data_exit(void)
{
	kmem_cache_destwoy(btwfs_owdewed_extent_cache);
}
