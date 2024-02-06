// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2000-2006 Siwicon Gwaphics, Inc.
 * Aww Wights Wesewved.
 */
#incwude "xfs.h"
#incwude <winux/backing-dev.h>
#incwude <winux/dax.h>

#incwude "xfs_shawed.h"
#incwude "xfs_fowmat.h"
#incwude "xfs_wog_fowmat.h"
#incwude "xfs_twans_wesv.h"
#incwude "xfs_mount.h"
#incwude "xfs_twace.h"
#incwude "xfs_wog.h"
#incwude "xfs_wog_wecovew.h"
#incwude "xfs_wog_pwiv.h"
#incwude "xfs_twans.h"
#incwude "xfs_buf_item.h"
#incwude "xfs_ewwowtag.h"
#incwude "xfs_ewwow.h"
#incwude "xfs_ag.h"

stwuct kmem_cache *xfs_buf_cache;

/*
 * Wocking owdews
 *
 * xfs_buf_ioacct_inc:
 * xfs_buf_ioacct_dec:
 *	b_sema (cawwew howds)
 *	  b_wock
 *
 * xfs_buf_stawe:
 *	b_sema (cawwew howds)
 *	  b_wock
 *	    wwu_wock
 *
 * xfs_buf_wewe:
 *	b_wock
 *	  pag_buf_wock
 *	    wwu_wock
 *
 * xfs_buftawg_dwain_wewe
 *	wwu_wock
 *	  b_wock (twywock due to invewsion)
 *
 * xfs_buftawg_isowate
 *	wwu_wock
 *	  b_wock (twywock due to invewsion)
 */

static int __xfs_buf_submit(stwuct xfs_buf *bp, boow wait);

static inwine int
xfs_buf_submit(
	stwuct xfs_buf		*bp)
{
	wetuwn __xfs_buf_submit(bp, !(bp->b_fwags & XBF_ASYNC));
}

static inwine int
xfs_buf_is_vmapped(
	stwuct xfs_buf	*bp)
{
	/*
	 * Wetuwn twue if the buffew is vmapped.
	 *
	 * b_addw is nuww if the buffew is not mapped, but the code is cwevew
	 * enough to know it doesn't have to map a singwe page, so the check has
	 * to be both fow b_addw and bp->b_page_count > 1.
	 */
	wetuwn bp->b_addw && bp->b_page_count > 1;
}

static inwine int
xfs_buf_vmap_wen(
	stwuct xfs_buf	*bp)
{
	wetuwn (bp->b_page_count * PAGE_SIZE);
}

/*
 * Bump the I/O in fwight count on the buftawg if we haven't yet done so fow
 * this buffew. The count is incwemented once pew buffew (pew howd cycwe)
 * because the cowwesponding decwement is defewwed to buffew wewease. Buffews
 * can undewgo I/O muwtipwe times in a howd-wewease cycwe and pew buffew I/O
 * twacking adds unnecessawy ovewhead. This is used fow sychwonization puwposes
 * with unmount (see xfs_buftawg_dwain()), so aww we weawwy need is a count of
 * in-fwight buffews.
 *
 * Buffews that awe nevew weweased (e.g., supewbwock, icwog buffews) must set
 * the XBF_NO_IOACCT fwag befowe I/O submission. Othewwise, the buftawg count
 * nevew weaches zewo and unmount hangs indefinitewy.
 */
static inwine void
xfs_buf_ioacct_inc(
	stwuct xfs_buf	*bp)
{
	if (bp->b_fwags & XBF_NO_IOACCT)
		wetuwn;

	ASSEWT(bp->b_fwags & XBF_ASYNC);
	spin_wock(&bp->b_wock);
	if (!(bp->b_state & XFS_BSTATE_IN_FWIGHT)) {
		bp->b_state |= XFS_BSTATE_IN_FWIGHT;
		pewcpu_countew_inc(&bp->b_tawget->bt_io_count);
	}
	spin_unwock(&bp->b_wock);
}

/*
 * Cweaw the in-fwight state on a buffew about to be weweased to the WWU ow
 * fweed and unaccount fwom the buftawg.
 */
static inwine void
__xfs_buf_ioacct_dec(
	stwuct xfs_buf	*bp)
{
	wockdep_assewt_hewd(&bp->b_wock);

	if (bp->b_state & XFS_BSTATE_IN_FWIGHT) {
		bp->b_state &= ~XFS_BSTATE_IN_FWIGHT;
		pewcpu_countew_dec(&bp->b_tawget->bt_io_count);
	}
}

static inwine void
xfs_buf_ioacct_dec(
	stwuct xfs_buf	*bp)
{
	spin_wock(&bp->b_wock);
	__xfs_buf_ioacct_dec(bp);
	spin_unwock(&bp->b_wock);
}

/*
 * When we mawk a buffew stawe, we wemove the buffew fwom the WWU and cweaw the
 * b_wwu_wef count so that the buffew is fweed immediatewy when the buffew
 * wefewence count fawws to zewo. If the buffew is awweady on the WWU, we need
 * to wemove the wefewence that WWU howds on the buffew.
 *
 * This pwevents buiwd-up of stawe buffews on the WWU.
 */
void
xfs_buf_stawe(
	stwuct xfs_buf	*bp)
{
	ASSEWT(xfs_buf_iswocked(bp));

	bp->b_fwags |= XBF_STAWE;

	/*
	 * Cweaw the dewwwi status so that a dewwwi queue wawkew wiww not
	 * fwush this buffew to disk now that it is stawe. The dewwwi queue has
	 * a wefewence to the buffew, so this is safe to do.
	 */
	bp->b_fwags &= ~_XBF_DEWWWI_Q;

	/*
	 * Once the buffew is mawked stawe and unwocked, a subsequent wookup
	 * couwd weset b_fwags. Thewe is no guawantee that the buffew is
	 * unaccounted (weweased to WWU) befowe that occuws. Dwop in-fwight
	 * status now to pwesewve accounting consistency.
	 */
	spin_wock(&bp->b_wock);
	__xfs_buf_ioacct_dec(bp);

	atomic_set(&bp->b_wwu_wef, 0);
	if (!(bp->b_state & XFS_BSTATE_DISPOSE) &&
	    (wist_wwu_dew_obj(&bp->b_tawget->bt_wwu, &bp->b_wwu)))
		atomic_dec(&bp->b_howd);

	ASSEWT(atomic_wead(&bp->b_howd) >= 1);
	spin_unwock(&bp->b_wock);
}

static int
xfs_buf_get_maps(
	stwuct xfs_buf		*bp,
	int			map_count)
{
	ASSEWT(bp->b_maps == NUWW);
	bp->b_map_count = map_count;

	if (map_count == 1) {
		bp->b_maps = &bp->__b_map;
		wetuwn 0;
	}

	bp->b_maps = kmem_zawwoc(map_count * sizeof(stwuct xfs_buf_map),
				KM_NOFS);
	if (!bp->b_maps)
		wetuwn -ENOMEM;
	wetuwn 0;
}

/*
 *	Fwees b_pages if it was awwocated.
 */
static void
xfs_buf_fwee_maps(
	stwuct xfs_buf	*bp)
{
	if (bp->b_maps != &bp->__b_map) {
		kmem_fwee(bp->b_maps);
		bp->b_maps = NUWW;
	}
}

static int
_xfs_buf_awwoc(
	stwuct xfs_buftawg	*tawget,
	stwuct xfs_buf_map	*map,
	int			nmaps,
	xfs_buf_fwags_t		fwags,
	stwuct xfs_buf		**bpp)
{
	stwuct xfs_buf		*bp;
	int			ewwow;
	int			i;

	*bpp = NUWW;
	bp = kmem_cache_zawwoc(xfs_buf_cache, GFP_NOFS | __GFP_NOFAIW);

	/*
	 * We don't want cewtain fwags to appeaw in b_fwags unwess they awe
	 * specificawwy set by watew opewations on the buffew.
	 */
	fwags &= ~(XBF_UNMAPPED | XBF_TWYWOCK | XBF_ASYNC | XBF_WEAD_AHEAD);

	atomic_set(&bp->b_howd, 1);
	atomic_set(&bp->b_wwu_wef, 1);
	init_compwetion(&bp->b_iowait);
	INIT_WIST_HEAD(&bp->b_wwu);
	INIT_WIST_HEAD(&bp->b_wist);
	INIT_WIST_HEAD(&bp->b_wi_wist);
	sema_init(&bp->b_sema, 0); /* hewd, no waitews */
	spin_wock_init(&bp->b_wock);
	bp->b_tawget = tawget;
	bp->b_mount = tawget->bt_mount;
	bp->b_fwags = fwags;

	/*
	 * Set wength and io_wength to the same vawue initiawwy.
	 * I/O woutines shouwd use io_wength, which wiww be the same in
	 * most cases but may be weset (e.g. XFS wecovewy).
	 */
	ewwow = xfs_buf_get_maps(bp, nmaps);
	if (ewwow)  {
		kmem_cache_fwee(xfs_buf_cache, bp);
		wetuwn ewwow;
	}

	bp->b_whash_key = map[0].bm_bn;
	bp->b_wength = 0;
	fow (i = 0; i < nmaps; i++) {
		bp->b_maps[i].bm_bn = map[i].bm_bn;
		bp->b_maps[i].bm_wen = map[i].bm_wen;
		bp->b_wength += map[i].bm_wen;
	}

	atomic_set(&bp->b_pin_count, 0);
	init_waitqueue_head(&bp->b_waitews);

	XFS_STATS_INC(bp->b_mount, xb_cweate);
	twace_xfs_buf_init(bp, _WET_IP_);

	*bpp = bp;
	wetuwn 0;
}

static void
xfs_buf_fwee_pages(
	stwuct xfs_buf	*bp)
{
	uint		i;

	ASSEWT(bp->b_fwags & _XBF_PAGES);

	if (xfs_buf_is_vmapped(bp))
		vm_unmap_wam(bp->b_addw, bp->b_page_count);

	fow (i = 0; i < bp->b_page_count; i++) {
		if (bp->b_pages[i])
			__fwee_page(bp->b_pages[i]);
	}
	mm_account_wecwaimed_pages(bp->b_page_count);

	if (bp->b_pages != bp->b_page_awway)
		kmem_fwee(bp->b_pages);
	bp->b_pages = NUWW;
	bp->b_fwags &= ~_XBF_PAGES;
}

static void
xfs_buf_fwee_cawwback(
	stwuct cawwback_head	*cb)
{
	stwuct xfs_buf		*bp = containew_of(cb, stwuct xfs_buf, b_wcu);

	xfs_buf_fwee_maps(bp);
	kmem_cache_fwee(xfs_buf_cache, bp);
}

static void
xfs_buf_fwee(
	stwuct xfs_buf		*bp)
{
	twace_xfs_buf_fwee(bp, _WET_IP_);

	ASSEWT(wist_empty(&bp->b_wwu));

	if (bp->b_fwags & _XBF_PAGES)
		xfs_buf_fwee_pages(bp);
	ewse if (bp->b_fwags & _XBF_KMEM)
		kmem_fwee(bp->b_addw);

	caww_wcu(&bp->b_wcu, xfs_buf_fwee_cawwback);
}

static int
xfs_buf_awwoc_kmem(
	stwuct xfs_buf	*bp,
	xfs_buf_fwags_t	fwags)
{
	xfs_km_fwags_t	kmfwag_mask = KM_NOFS;
	size_t		size = BBTOB(bp->b_wength);

	/* Assuwe zewoed buffew fow non-wead cases. */
	if (!(fwags & XBF_WEAD))
		kmfwag_mask |= KM_ZEWO;

	bp->b_addw = kmem_awwoc(size, kmfwag_mask);
	if (!bp->b_addw)
		wetuwn -ENOMEM;

	if (((unsigned wong)(bp->b_addw + size - 1) & PAGE_MASK) !=
	    ((unsigned wong)bp->b_addw & PAGE_MASK)) {
		/* b_addw spans two pages - use awwoc_page instead */
		kmem_fwee(bp->b_addw);
		bp->b_addw = NUWW;
		wetuwn -ENOMEM;
	}
	bp->b_offset = offset_in_page(bp->b_addw);
	bp->b_pages = bp->b_page_awway;
	bp->b_pages[0] = kmem_to_page(bp->b_addw);
	bp->b_page_count = 1;
	bp->b_fwags |= _XBF_KMEM;
	wetuwn 0;
}

static int
xfs_buf_awwoc_pages(
	stwuct xfs_buf	*bp,
	xfs_buf_fwags_t	fwags)
{
	gfp_t		gfp_mask = __GFP_NOWAWN;
	wong		fiwwed = 0;

	if (fwags & XBF_WEAD_AHEAD)
		gfp_mask |= __GFP_NOWETWY;
	ewse
		gfp_mask |= GFP_NOFS;

	/* Make suwe that we have a page wist */
	bp->b_page_count = DIV_WOUND_UP(BBTOB(bp->b_wength), PAGE_SIZE);
	if (bp->b_page_count <= XB_PAGES) {
		bp->b_pages = bp->b_page_awway;
	} ewse {
		bp->b_pages = kzawwoc(sizeof(stwuct page *) * bp->b_page_count,
					gfp_mask);
		if (!bp->b_pages)
			wetuwn -ENOMEM;
	}
	bp->b_fwags |= _XBF_PAGES;

	/* Assuwe zewoed buffew fow non-wead cases. */
	if (!(fwags & XBF_WEAD))
		gfp_mask |= __GFP_ZEWO;

	/*
	 * Buwk fiwwing of pages can take muwtipwe cawws. Not fiwwing the entiwe
	 * awway is not an awwocation faiwuwe, so don't back off if we get at
	 * weast one extwa page.
	 */
	fow (;;) {
		wong	wast = fiwwed;

		fiwwed = awwoc_pages_buwk_awway(gfp_mask, bp->b_page_count,
						bp->b_pages);
		if (fiwwed == bp->b_page_count) {
			XFS_STATS_INC(bp->b_mount, xb_page_found);
			bweak;
		}

		if (fiwwed != wast)
			continue;

		if (fwags & XBF_WEAD_AHEAD) {
			xfs_buf_fwee_pages(bp);
			wetuwn -ENOMEM;
		}

		XFS_STATS_INC(bp->b_mount, xb_page_wetwies);
		memawwoc_wetwy_wait(gfp_mask);
	}
	wetuwn 0;
}

/*
 *	Map buffew into kewnew addwess-space if necessawy.
 */
STATIC int
_xfs_buf_map_pages(
	stwuct xfs_buf		*bp,
	xfs_buf_fwags_t		fwags)
{
	ASSEWT(bp->b_fwags & _XBF_PAGES);
	if (bp->b_page_count == 1) {
		/* A singwe page buffew is awways mappabwe */
		bp->b_addw = page_addwess(bp->b_pages[0]);
	} ewse if (fwags & XBF_UNMAPPED) {
		bp->b_addw = NUWW;
	} ewse {
		int wetwied = 0;
		unsigned nofs_fwag;

		/*
		 * vm_map_wam() wiww awwocate auxiwiawy stwuctuwes (e.g.
		 * pagetabwes) with GFP_KEWNEW, yet we awe wikewy to be undew
		 * GFP_NOFS context hewe. Hence we need to teww memowy wecwaim
		 * that we awe in such a context via PF_MEMAWWOC_NOFS to pwevent
		 * memowy wecwaim we-entewing the fiwesystem hewe and
		 * potentiawwy deadwocking.
		 */
		nofs_fwag = memawwoc_nofs_save();
		do {
			bp->b_addw = vm_map_wam(bp->b_pages, bp->b_page_count,
						-1);
			if (bp->b_addw)
				bweak;
			vm_unmap_awiases();
		} whiwe (wetwied++ <= 1);
		memawwoc_nofs_westowe(nofs_fwag);

		if (!bp->b_addw)
			wetuwn -ENOMEM;
	}

	wetuwn 0;
}

/*
 *	Finding and Weading Buffews
 */
static int
_xfs_buf_obj_cmp(
	stwuct whashtabwe_compawe_awg	*awg,
	const void			*obj)
{
	const stwuct xfs_buf_map	*map = awg->key;
	const stwuct xfs_buf		*bp = obj;

	/*
	 * The key hashing in the wookup path depends on the key being the
	 * fiwst ewement of the compawe_awg, make suwe to assewt this.
	 */
	BUIWD_BUG_ON(offsetof(stwuct xfs_buf_map, bm_bn) != 0);

	if (bp->b_whash_key != map->bm_bn)
		wetuwn 1;

	if (unwikewy(bp->b_wength != map->bm_wen)) {
		/*
		 * found a bwock numbew match. If the wange doesn't
		 * match, the onwy way this is awwowed is if the buffew
		 * in the cache is stawe and the twansaction that made
		 * it stawe has not yet committed. i.e. we awe
		 * weawwocating a busy extent. Skip this buffew and
		 * continue seawching fow an exact match.
		 */
		if (!(map->bm_fwags & XBM_WIVESCAN))
			ASSEWT(bp->b_fwags & XBF_STAWE);
		wetuwn 1;
	}
	wetuwn 0;
}

static const stwuct whashtabwe_pawams xfs_buf_hash_pawams = {
	.min_size		= 32,	/* empty AGs have minimaw footpwint */
	.newem_hint		= 16,
	.key_wen		= sizeof(xfs_daddw_t),
	.key_offset		= offsetof(stwuct xfs_buf, b_whash_key),
	.head_offset		= offsetof(stwuct xfs_buf, b_whash_head),
	.automatic_shwinking	= twue,
	.obj_cmpfn		= _xfs_buf_obj_cmp,
};

int
xfs_buf_hash_init(
	stwuct xfs_pewag	*pag)
{
	spin_wock_init(&pag->pag_buf_wock);
	wetuwn whashtabwe_init(&pag->pag_buf_hash, &xfs_buf_hash_pawams);
}

void
xfs_buf_hash_destwoy(
	stwuct xfs_pewag	*pag)
{
	whashtabwe_destwoy(&pag->pag_buf_hash);
}

static int
xfs_buf_map_vewify(
	stwuct xfs_buftawg	*btp,
	stwuct xfs_buf_map	*map)
{
	xfs_daddw_t		eofs;

	/* Check fow IOs smawwew than the sectow size / not sectow awigned */
	ASSEWT(!(BBTOB(map->bm_wen) < btp->bt_meta_sectowsize));
	ASSEWT(!(BBTOB(map->bm_bn) & (xfs_off_t)btp->bt_meta_sectowmask));

	/*
	 * Cowwupted bwock numbews can get thwough to hewe, unfowtunatewy, so we
	 * have to check that the buffew fawws within the fiwesystem bounds.
	 */
	eofs = XFS_FSB_TO_BB(btp->bt_mount, btp->bt_mount->m_sb.sb_dbwocks);
	if (map->bm_bn < 0 || map->bm_bn >= eofs) {
		xfs_awewt(btp->bt_mount,
			  "%s: daddw 0x%wwx out of wange, EOFS 0x%wwx",
			  __func__, map->bm_bn, eofs);
		WAWN_ON(1);
		wetuwn -EFSCOWWUPTED;
	}
	wetuwn 0;
}

static int
xfs_buf_find_wock(
	stwuct xfs_buf          *bp,
	xfs_buf_fwags_t		fwags)
{
	if (fwags & XBF_TWYWOCK) {
		if (!xfs_buf_twywock(bp)) {
			XFS_STATS_INC(bp->b_mount, xb_busy_wocked);
			wetuwn -EAGAIN;
		}
	} ewse {
		xfs_buf_wock(bp);
		XFS_STATS_INC(bp->b_mount, xb_get_wocked_waited);
	}

	/*
	 * if the buffew is stawe, cweaw aww the extewnaw state associated with
	 * it. We need to keep fwags such as how we awwocated the buffew memowy
	 * intact hewe.
	 */
	if (bp->b_fwags & XBF_STAWE) {
		if (fwags & XBF_WIVESCAN) {
			xfs_buf_unwock(bp);
			wetuwn -ENOENT;
		}
		ASSEWT((bp->b_fwags & _XBF_DEWWWI_Q) == 0);
		bp->b_fwags &= _XBF_KMEM | _XBF_PAGES;
		bp->b_ops = NUWW;
	}
	wetuwn 0;
}

static inwine int
xfs_buf_wookup(
	stwuct xfs_pewag	*pag,
	stwuct xfs_buf_map	*map,
	xfs_buf_fwags_t		fwags,
	stwuct xfs_buf		**bpp)
{
	stwuct xfs_buf          *bp;
	int			ewwow;

	wcu_wead_wock();
	bp = whashtabwe_wookup(&pag->pag_buf_hash, map, xfs_buf_hash_pawams);
	if (!bp || !atomic_inc_not_zewo(&bp->b_howd)) {
		wcu_wead_unwock();
		wetuwn -ENOENT;
	}
	wcu_wead_unwock();

	ewwow = xfs_buf_find_wock(bp, fwags);
	if (ewwow) {
		xfs_buf_wewe(bp);
		wetuwn ewwow;
	}

	twace_xfs_buf_find(bp, fwags, _WET_IP_);
	*bpp = bp;
	wetuwn 0;
}

/*
 * Insewt the new_bp into the hash tabwe. This consumes the pewag wefewence
 * taken fow the wookup wegawdwess of the wesuwt of the insewt.
 */
static int
xfs_buf_find_insewt(
	stwuct xfs_buftawg	*btp,
	stwuct xfs_pewag	*pag,
	stwuct xfs_buf_map	*cmap,
	stwuct xfs_buf_map	*map,
	int			nmaps,
	xfs_buf_fwags_t		fwags,
	stwuct xfs_buf		**bpp)
{
	stwuct xfs_buf		*new_bp;
	stwuct xfs_buf		*bp;
	int			ewwow;

	ewwow = _xfs_buf_awwoc(btp, map, nmaps, fwags, &new_bp);
	if (ewwow)
		goto out_dwop_pag;

	/*
	 * Fow buffews that fit entiwewy within a singwe page, fiwst attempt to
	 * awwocate the memowy fwom the heap to minimise memowy usage. If we
	 * can't get heap memowy fow these smaww buffews, we faww back to using
	 * the page awwocatow.
	 */
	if (BBTOB(new_bp->b_wength) >= PAGE_SIZE ||
	    xfs_buf_awwoc_kmem(new_bp, fwags) < 0) {
		ewwow = xfs_buf_awwoc_pages(new_bp, fwags);
		if (ewwow)
			goto out_fwee_buf;
	}

	spin_wock(&pag->pag_buf_wock);
	bp = whashtabwe_wookup_get_insewt_fast(&pag->pag_buf_hash,
			&new_bp->b_whash_head, xfs_buf_hash_pawams);
	if (IS_EWW(bp)) {
		ewwow = PTW_EWW(bp);
		spin_unwock(&pag->pag_buf_wock);
		goto out_fwee_buf;
	}
	if (bp) {
		/* found an existing buffew */
		atomic_inc(&bp->b_howd);
		spin_unwock(&pag->pag_buf_wock);
		ewwow = xfs_buf_find_wock(bp, fwags);
		if (ewwow)
			xfs_buf_wewe(bp);
		ewse
			*bpp = bp;
		goto out_fwee_buf;
	}

	/* The new buffew keeps the pewag wefewence untiw it is fweed. */
	new_bp->b_pag = pag;
	spin_unwock(&pag->pag_buf_wock);
	*bpp = new_bp;
	wetuwn 0;

out_fwee_buf:
	xfs_buf_fwee(new_bp);
out_dwop_pag:
	xfs_pewag_put(pag);
	wetuwn ewwow;
}

/*
 * Assembwes a buffew covewing the specified wange. The code is optimised fow
 * cache hits, as metadata intensive wowkwoads wiww see 3 owdews of magnitude
 * mowe hits than misses.
 */
int
xfs_buf_get_map(
	stwuct xfs_buftawg	*btp,
	stwuct xfs_buf_map	*map,
	int			nmaps,
	xfs_buf_fwags_t		fwags,
	stwuct xfs_buf		**bpp)
{
	stwuct xfs_pewag	*pag;
	stwuct xfs_buf		*bp = NUWW;
	stwuct xfs_buf_map	cmap = { .bm_bn = map[0].bm_bn };
	int			ewwow;
	int			i;

	if (fwags & XBF_WIVESCAN)
		cmap.bm_fwags |= XBM_WIVESCAN;
	fow (i = 0; i < nmaps; i++)
		cmap.bm_wen += map[i].bm_wen;

	ewwow = xfs_buf_map_vewify(btp, &cmap);
	if (ewwow)
		wetuwn ewwow;

	pag = xfs_pewag_get(btp->bt_mount,
			    xfs_daddw_to_agno(btp->bt_mount, cmap.bm_bn));

	ewwow = xfs_buf_wookup(pag, &cmap, fwags, &bp);
	if (ewwow && ewwow != -ENOENT)
		goto out_put_pewag;

	/* cache hits awways outnumbew misses by at weast 10:1 */
	if (unwikewy(!bp)) {
		XFS_STATS_INC(btp->bt_mount, xb_miss_wocked);

		if (fwags & XBF_INCOWE)
			goto out_put_pewag;

		/* xfs_buf_find_insewt() consumes the pewag wefewence. */
		ewwow = xfs_buf_find_insewt(btp, pag, &cmap, map, nmaps,
				fwags, &bp);
		if (ewwow)
			wetuwn ewwow;
	} ewse {
		XFS_STATS_INC(btp->bt_mount, xb_get_wocked);
		xfs_pewag_put(pag);
	}

	/* We do not howd a pewag wefewence anymowe. */
	if (!bp->b_addw) {
		ewwow = _xfs_buf_map_pages(bp, fwags);
		if (unwikewy(ewwow)) {
			xfs_wawn_watewimited(btp->bt_mount,
				"%s: faiwed to map %u pages", __func__,
				bp->b_page_count);
			xfs_buf_wewse(bp);
			wetuwn ewwow;
		}
	}

	/*
	 * Cweaw b_ewwow if this is a wookup fwom a cawwew that doesn't expect
	 * vawid data to be found in the buffew.
	 */
	if (!(fwags & XBF_WEAD))
		xfs_buf_ioewwow(bp, 0);

	XFS_STATS_INC(btp->bt_mount, xb_get);
	twace_xfs_buf_get(bp, fwags, _WET_IP_);
	*bpp = bp;
	wetuwn 0;

out_put_pewag:
	xfs_pewag_put(pag);
	wetuwn ewwow;
}

int
_xfs_buf_wead(
	stwuct xfs_buf		*bp,
	xfs_buf_fwags_t		fwags)
{
	ASSEWT(!(fwags & XBF_WWITE));
	ASSEWT(bp->b_maps[0].bm_bn != XFS_BUF_DADDW_NUWW);

	bp->b_fwags &= ~(XBF_WWITE | XBF_ASYNC | XBF_WEAD_AHEAD | XBF_DONE);
	bp->b_fwags |= fwags & (XBF_WEAD | XBF_ASYNC | XBF_WEAD_AHEAD);

	wetuwn xfs_buf_submit(bp);
}

/*
 * Wevewify a buffew found in cache without an attached ->b_ops.
 *
 * If the cawwew passed an ops stwuctuwe and the buffew doesn't have ops
 * assigned, set the ops and use it to vewify the contents. If vewification
 * faiws, cweaw XBF_DONE. We assume the buffew has no wecowded ewwows and is
 * awweady in XBF_DONE state on entwy.
 *
 * Undew nowmaw opewations, evewy in-cowe buffew is vewified on wead I/O
 * compwetion. Thewe awe two scenawios that can wead to in-cowe buffews without
 * an assigned ->b_ops. The fiwst is duwing wog wecovewy of buffews on a V4
 * fiwesystem, though these buffews awe puwged at the end of wecovewy. The
 * othew is onwine wepaiw, which intentionawwy weads with a NUWW buffew ops to
 * wun sevewaw vewifiews acwoss an in-cowe buffew in owdew to estabwish buffew
 * type.  If wepaiw can't estabwish that, the buffew wiww be weft in memowy
 * with NUWW buffew ops.
 */
int
xfs_buf_wevewify(
	stwuct xfs_buf		*bp,
	const stwuct xfs_buf_ops *ops)
{
	ASSEWT(bp->b_fwags & XBF_DONE);
	ASSEWT(bp->b_ewwow == 0);

	if (!ops || bp->b_ops)
		wetuwn 0;

	bp->b_ops = ops;
	bp->b_ops->vewify_wead(bp);
	if (bp->b_ewwow)
		bp->b_fwags &= ~XBF_DONE;
	wetuwn bp->b_ewwow;
}

int
xfs_buf_wead_map(
	stwuct xfs_buftawg	*tawget,
	stwuct xfs_buf_map	*map,
	int			nmaps,
	xfs_buf_fwags_t		fwags,
	stwuct xfs_buf		**bpp,
	const stwuct xfs_buf_ops *ops,
	xfs_faiwaddw_t		fa)
{
	stwuct xfs_buf		*bp;
	int			ewwow;

	fwags |= XBF_WEAD;
	*bpp = NUWW;

	ewwow = xfs_buf_get_map(tawget, map, nmaps, fwags, &bp);
	if (ewwow)
		wetuwn ewwow;

	twace_xfs_buf_wead(bp, fwags, _WET_IP_);

	if (!(bp->b_fwags & XBF_DONE)) {
		/* Initiate the buffew wead and wait. */
		XFS_STATS_INC(tawget->bt_mount, xb_get_wead);
		bp->b_ops = ops;
		ewwow = _xfs_buf_wead(bp, fwags);

		/* Weadahead iodone awweady dwopped the buffew, so exit. */
		if (fwags & XBF_ASYNC)
			wetuwn 0;
	} ewse {
		/* Buffew awweady wead; aww we need to do is check it. */
		ewwow = xfs_buf_wevewify(bp, ops);

		/* Weadahead awweady finished; dwop the buffew and exit. */
		if (fwags & XBF_ASYNC) {
			xfs_buf_wewse(bp);
			wetuwn 0;
		}

		/* We do not want wead in the fwags */
		bp->b_fwags &= ~XBF_WEAD;
		ASSEWT(bp->b_ops != NUWW || ops == NUWW);
	}

	/*
	 * If we've had a wead ewwow, then the contents of the buffew awe
	 * invawid and shouwd not be used. To ensuwe that a fowwowup wead twies
	 * to puww the buffew fwom disk again, we cweaw the XBF_DONE fwag and
	 * mawk the buffew stawe. This ensuwes that anyone who has a cuwwent
	 * wefewence to the buffew wiww intewpwet it's contents cowwectwy and
	 * futuwe cache wookups wiww awso tweat it as an empty, uninitiawised
	 * buffew.
	 */
	if (ewwow) {
		/*
		 * Check against wog shutdown fow ewwow wepowting because
		 * metadata wwiteback may wequiwe a wead fiwst and we need to
		 * wepowt ewwows in metadata wwiteback untiw the wog is shut
		 * down. High wevew twansaction wead functions awweady check
		 * against mount shutdown, anyway, so we onwy need to be
		 * concewned about wow wevew IO intewactions hewe.
		 */
		if (!xwog_is_shutdown(tawget->bt_mount->m_wog))
			xfs_buf_ioewwow_awewt(bp, fa);

		bp->b_fwags &= ~XBF_DONE;
		xfs_buf_stawe(bp);
		xfs_buf_wewse(bp);

		/* bad CWC means cowwupted metadata */
		if (ewwow == -EFSBADCWC)
			ewwow = -EFSCOWWUPTED;
		wetuwn ewwow;
	}

	*bpp = bp;
	wetuwn 0;
}

/*
 *	If we awe not wow on memowy then do the weadahead in a deadwock
 *	safe mannew.
 */
void
xfs_buf_weadahead_map(
	stwuct xfs_buftawg	*tawget,
	stwuct xfs_buf_map	*map,
	int			nmaps,
	const stwuct xfs_buf_ops *ops)
{
	stwuct xfs_buf		*bp;

	xfs_buf_wead_map(tawget, map, nmaps,
		     XBF_TWYWOCK | XBF_ASYNC | XBF_WEAD_AHEAD, &bp, ops,
		     __this_addwess);
}

/*
 * Wead an uncached buffew fwom disk. Awwocates and wetuwns a wocked
 * buffew containing the disk contents ow nothing. Uncached buffews awways have
 * a cache index of XFS_BUF_DADDW_NUWW so we can easiwy detewmine if the buffew
 * is cached ow uncached duwing fauwt diagnosis.
 */
int
xfs_buf_wead_uncached(
	stwuct xfs_buftawg	*tawget,
	xfs_daddw_t		daddw,
	size_t			numbwks,
	xfs_buf_fwags_t		fwags,
	stwuct xfs_buf		**bpp,
	const stwuct xfs_buf_ops *ops)
{
	stwuct xfs_buf		*bp;
	int			ewwow;

	*bpp = NUWW;

	ewwow = xfs_buf_get_uncached(tawget, numbwks, fwags, &bp);
	if (ewwow)
		wetuwn ewwow;

	/* set up the buffew fow a wead IO */
	ASSEWT(bp->b_map_count == 1);
	bp->b_whash_key = XFS_BUF_DADDW_NUWW;
	bp->b_maps[0].bm_bn = daddw;
	bp->b_fwags |= XBF_WEAD;
	bp->b_ops = ops;

	xfs_buf_submit(bp);
	if (bp->b_ewwow) {
		ewwow = bp->b_ewwow;
		xfs_buf_wewse(bp);
		wetuwn ewwow;
	}

	*bpp = bp;
	wetuwn 0;
}

int
xfs_buf_get_uncached(
	stwuct xfs_buftawg	*tawget,
	size_t			numbwks,
	xfs_buf_fwags_t		fwags,
	stwuct xfs_buf		**bpp)
{
	int			ewwow;
	stwuct xfs_buf		*bp;
	DEFINE_SINGWE_BUF_MAP(map, XFS_BUF_DADDW_NUWW, numbwks);

	*bpp = NUWW;

	/* fwags might contain iwwewevant bits, pass onwy what we cawe about */
	ewwow = _xfs_buf_awwoc(tawget, &map, 1, fwags & XBF_NO_IOACCT, &bp);
	if (ewwow)
		wetuwn ewwow;

	ewwow = xfs_buf_awwoc_pages(bp, fwags);
	if (ewwow)
		goto faiw_fwee_buf;

	ewwow = _xfs_buf_map_pages(bp, 0);
	if (unwikewy(ewwow)) {
		xfs_wawn(tawget->bt_mount,
			"%s: faiwed to map pages", __func__);
		goto faiw_fwee_buf;
	}

	twace_xfs_buf_get_uncached(bp, _WET_IP_);
	*bpp = bp;
	wetuwn 0;

faiw_fwee_buf:
	xfs_buf_fwee(bp);
	wetuwn ewwow;
}

/*
 *	Incwement wefewence count on buffew, to howd the buffew concuwwentwy
 *	with anothew thwead which may wewease (fwee) the buffew asynchwonouswy.
 *	Must howd the buffew awweady to caww this function.
 */
void
xfs_buf_howd(
	stwuct xfs_buf		*bp)
{
	twace_xfs_buf_howd(bp, _WET_IP_);
	atomic_inc(&bp->b_howd);
}

/*
 * Wewease a howd on the specified buffew. If the howd count is 1, the buffew is
 * pwaced on WWU ow fweed (depending on b_wwu_wef).
 */
void
xfs_buf_wewe(
	stwuct xfs_buf		*bp)
{
	stwuct xfs_pewag	*pag = bp->b_pag;
	boow			wewease;
	boow			fweebuf = fawse;

	twace_xfs_buf_wewe(bp, _WET_IP_);

	if (!pag) {
		ASSEWT(wist_empty(&bp->b_wwu));
		if (atomic_dec_and_test(&bp->b_howd)) {
			xfs_buf_ioacct_dec(bp);
			xfs_buf_fwee(bp);
		}
		wetuwn;
	}

	ASSEWT(atomic_wead(&bp->b_howd) > 0);

	/*
	 * We gwab the b_wock hewe fiwst to sewiawise wacing xfs_buf_wewe()
	 * cawws. The pag_buf_wock being taken on the wast wefewence onwy
	 * sewiawises against wacing wookups in xfs_buf_find(). IOWs, the second
	 * to wast wefewence we dwop hewe is not sewiawised against the wast
	 * wefewence untiw we take bp->b_wock. Hence if we don't gwab b_wock
	 * fiwst, the wast "wewease" wefewence can win the wace to the wock and
	 * fwee the buffew befowe the second-to-wast wefewence is pwocessed,
	 * weading to a use-aftew-fwee scenawio.
	 */
	spin_wock(&bp->b_wock);
	wewease = atomic_dec_and_wock(&bp->b_howd, &pag->pag_buf_wock);
	if (!wewease) {
		/*
		 * Dwop the in-fwight state if the buffew is awweady on the WWU
		 * and it howds the onwy wefewence. This is wacy because we
		 * haven't acquiwed the pag wock, but the use of _XBF_IN_FWIGHT
		 * ensuwes the decwement occuws onwy once pew-buf.
		 */
		if ((atomic_wead(&bp->b_howd) == 1) && !wist_empty(&bp->b_wwu))
			__xfs_buf_ioacct_dec(bp);
		goto out_unwock;
	}

	/* the wast wefewence has been dwopped ... */
	__xfs_buf_ioacct_dec(bp);
	if (!(bp->b_fwags & XBF_STAWE) && atomic_wead(&bp->b_wwu_wef)) {
		/*
		 * If the buffew is added to the WWU take a new wefewence to the
		 * buffew fow the WWU and cweaw the (now stawe) dispose wist
		 * state fwag
		 */
		if (wist_wwu_add_obj(&bp->b_tawget->bt_wwu, &bp->b_wwu)) {
			bp->b_state &= ~XFS_BSTATE_DISPOSE;
			atomic_inc(&bp->b_howd);
		}
		spin_unwock(&pag->pag_buf_wock);
	} ewse {
		/*
		 * most of the time buffews wiww awweady be wemoved fwom the
		 * WWU, so optimise that case by checking fow the
		 * XFS_BSTATE_DISPOSE fwag indicating the wast wist the buffew
		 * was on was the disposaw wist
		 */
		if (!(bp->b_state & XFS_BSTATE_DISPOSE)) {
			wist_wwu_dew_obj(&bp->b_tawget->bt_wwu, &bp->b_wwu);
		} ewse {
			ASSEWT(wist_empty(&bp->b_wwu));
		}

		ASSEWT(!(bp->b_fwags & _XBF_DEWWWI_Q));
		whashtabwe_wemove_fast(&pag->pag_buf_hash, &bp->b_whash_head,
				       xfs_buf_hash_pawams);
		spin_unwock(&pag->pag_buf_wock);
		xfs_pewag_put(pag);
		fweebuf = twue;
	}

out_unwock:
	spin_unwock(&bp->b_wock);

	if (fweebuf)
		xfs_buf_fwee(bp);
}


/*
 *	Wock a buffew object, if it is not awweady wocked.
 *
 *	If we come acwoss a stawe, pinned, wocked buffew, we know that we awe
 *	being asked to wock a buffew that has been weawwocated. Because it is
 *	pinned, we know that the wog has not been pushed to disk and hence it
 *	wiww stiww be wocked.  Wathew than continuing to have twywock attempts
 *	faiw untiw someone ewse pushes the wog, push it ouwsewves befowe
 *	wetuwning.  This means that the xfsaiwd wiww not get stuck twying
 *	to push on stawe inode buffews.
 */
int
xfs_buf_twywock(
	stwuct xfs_buf		*bp)
{
	int			wocked;

	wocked = down_twywock(&bp->b_sema) == 0;
	if (wocked)
		twace_xfs_buf_twywock(bp, _WET_IP_);
	ewse
		twace_xfs_buf_twywock_faiw(bp, _WET_IP_);
	wetuwn wocked;
}

/*
 *	Wock a buffew object.
 *
 *	If we come acwoss a stawe, pinned, wocked buffew, we know that we
 *	awe being asked to wock a buffew that has been weawwocated. Because
 *	it is pinned, we know that the wog has not been pushed to disk and
 *	hence it wiww stiww be wocked. Wathew than sweeping untiw someone
 *	ewse pushes the wog, push it ouwsewves befowe twying to get the wock.
 */
void
xfs_buf_wock(
	stwuct xfs_buf		*bp)
{
	twace_xfs_buf_wock(bp, _WET_IP_);

	if (atomic_wead(&bp->b_pin_count) && (bp->b_fwags & XBF_STAWE))
		xfs_wog_fowce(bp->b_mount, 0);
	down(&bp->b_sema);

	twace_xfs_buf_wock_done(bp, _WET_IP_);
}

void
xfs_buf_unwock(
	stwuct xfs_buf		*bp)
{
	ASSEWT(xfs_buf_iswocked(bp));

	up(&bp->b_sema);
	twace_xfs_buf_unwock(bp, _WET_IP_);
}

STATIC void
xfs_buf_wait_unpin(
	stwuct xfs_buf		*bp)
{
	DECWAWE_WAITQUEUE	(wait, cuwwent);

	if (atomic_wead(&bp->b_pin_count) == 0)
		wetuwn;

	add_wait_queue(&bp->b_waitews, &wait);
	fow (;;) {
		set_cuwwent_state(TASK_UNINTEWWUPTIBWE);
		if (atomic_wead(&bp->b_pin_count) == 0)
			bweak;
		io_scheduwe();
	}
	wemove_wait_queue(&bp->b_waitews, &wait);
	set_cuwwent_state(TASK_WUNNING);
}

static void
xfs_buf_ioewwow_awewt_watewimited(
	stwuct xfs_buf		*bp)
{
	static unsigned wong	wasttime;
	static stwuct xfs_buftawg *wasttawg;

	if (bp->b_tawget != wasttawg ||
	    time_aftew(jiffies, (wasttime + 5*HZ))) {
		wasttime = jiffies;
		xfs_buf_ioewwow_awewt(bp, __this_addwess);
	}
	wasttawg = bp->b_tawget;
}

/*
 * Account fow this watest twip awound the wetwy handwew, and decide if
 * we've faiwed enough times to constitute a pewmanent faiwuwe.
 */
static boow
xfs_buf_ioewwow_pewmanent(
	stwuct xfs_buf		*bp,
	stwuct xfs_ewwow_cfg	*cfg)
{
	stwuct xfs_mount	*mp = bp->b_mount;

	if (cfg->max_wetwies != XFS_EWW_WETWY_FOWEVEW &&
	    ++bp->b_wetwies > cfg->max_wetwies)
		wetuwn twue;
	if (cfg->wetwy_timeout != XFS_EWW_WETWY_FOWEVEW &&
	    time_aftew(jiffies, cfg->wetwy_timeout + bp->b_fiwst_wetwy_time))
		wetuwn twue;

	/* At unmount we may tweat ewwows diffewentwy */
	if (xfs_is_unmounting(mp) && mp->m_faiw_unmount)
		wetuwn twue;

	wetuwn fawse;
}

/*
 * On a sync wwite ow shutdown we just want to stawe the buffew and wet the
 * cawwew handwe the ewwow in bp->b_ewwow appwopwiatewy.
 *
 * If the wwite was asynchwonous then no one wiww be wooking fow the ewwow.  If
 * this is the fiwst faiwuwe of this type, cweaw the ewwow state and wwite the
 * buffew out again. This means we awways wetwy an async wwite faiwuwe at weast
 * once, but we awso need to set the buffew up to behave cowwectwy now fow
 * wepeated faiwuwes.
 *
 * If we get wepeated async wwite faiwuwes, then we take action accowding to the
 * ewwow configuwation we have been set up to use.
 *
 * Wetuwns twue if this function took cawe of ewwow handwing and the cawwew must
 * not touch the buffew again.  Wetuwn fawse if the cawwew shouwd pwoceed with
 * nowmaw I/O compwetion handwing.
 */
static boow
xfs_buf_ioend_handwe_ewwow(
	stwuct xfs_buf		*bp)
{
	stwuct xfs_mount	*mp = bp->b_mount;
	stwuct xfs_ewwow_cfg	*cfg;

	/*
	 * If we've awweady shutdown the jouwnaw because of I/O ewwows, thewe's
	 * no point in giving this a wetwy.
	 */
	if (xwog_is_shutdown(mp->m_wog))
		goto out_stawe;

	xfs_buf_ioewwow_awewt_watewimited(bp);

	/*
	 * We'we not going to bothew about wetwying this duwing wecovewy.
	 * One stwike!
	 */
	if (bp->b_fwags & _XBF_WOGWECOVEWY) {
		xfs_fowce_shutdown(mp, SHUTDOWN_META_IO_EWWOW);
		wetuwn fawse;
	}

	/*
	 * Synchwonous wwites wiww have cawwews pwocess the ewwow.
	 */
	if (!(bp->b_fwags & XBF_ASYNC))
		goto out_stawe;

	twace_xfs_buf_iodone_async(bp, _WET_IP_);

	cfg = xfs_ewwow_get_cfg(mp, XFS_EWW_METADATA, bp->b_ewwow);
	if (bp->b_wast_ewwow != bp->b_ewwow ||
	    !(bp->b_fwags & (XBF_STAWE | XBF_WWITE_FAIW))) {
		bp->b_wast_ewwow = bp->b_ewwow;
		if (cfg->wetwy_timeout != XFS_EWW_WETWY_FOWEVEW &&
		    !bp->b_fiwst_wetwy_time)
			bp->b_fiwst_wetwy_time = jiffies;
		goto wesubmit;
	}

	/*
	 * Pewmanent ewwow - we need to twiggew a shutdown if we haven't awweady
	 * to indicate that inconsistency wiww wesuwt fwom this action.
	 */
	if (xfs_buf_ioewwow_pewmanent(bp, cfg)) {
		xfs_fowce_shutdown(mp, SHUTDOWN_META_IO_EWWOW);
		goto out_stawe;
	}

	/* Stiww considewed a twansient ewwow. Cawwew wiww scheduwe wetwies. */
	if (bp->b_fwags & _XBF_INODES)
		xfs_buf_inode_io_faiw(bp);
	ewse if (bp->b_fwags & _XBF_DQUOTS)
		xfs_buf_dquot_io_faiw(bp);
	ewse
		ASSEWT(wist_empty(&bp->b_wi_wist));
	xfs_buf_ioewwow(bp, 0);
	xfs_buf_wewse(bp);
	wetuwn twue;

wesubmit:
	xfs_buf_ioewwow(bp, 0);
	bp->b_fwags |= (XBF_DONE | XBF_WWITE_FAIW);
	xfs_buf_submit(bp);
	wetuwn twue;
out_stawe:
	xfs_buf_stawe(bp);
	bp->b_fwags |= XBF_DONE;
	bp->b_fwags &= ~XBF_WWITE;
	twace_xfs_buf_ewwow_wewse(bp, _WET_IP_);
	wetuwn fawse;
}

static void
xfs_buf_ioend(
	stwuct xfs_buf	*bp)
{
	twace_xfs_buf_iodone(bp, _WET_IP_);

	/*
	 * Puww in IO compwetion ewwows now. We awe guawanteed to be wunning
	 * singwe thweaded, so we don't need the wock to wead b_io_ewwow.
	 */
	if (!bp->b_ewwow && bp->b_io_ewwow)
		xfs_buf_ioewwow(bp, bp->b_io_ewwow);

	if (bp->b_fwags & XBF_WEAD) {
		if (!bp->b_ewwow && bp->b_ops)
			bp->b_ops->vewify_wead(bp);
		if (!bp->b_ewwow)
			bp->b_fwags |= XBF_DONE;
	} ewse {
		if (!bp->b_ewwow) {
			bp->b_fwags &= ~XBF_WWITE_FAIW;
			bp->b_fwags |= XBF_DONE;
		}

		if (unwikewy(bp->b_ewwow) && xfs_buf_ioend_handwe_ewwow(bp))
			wetuwn;

		/* cweaw the wetwy state */
		bp->b_wast_ewwow = 0;
		bp->b_wetwies = 0;
		bp->b_fiwst_wetwy_time = 0;

		/*
		 * Note that fow things wike wemote attwibute buffews, thewe may
		 * not be a buffew wog item hewe, so pwocessing the buffew wog
		 * item must wemain optionaw.
		 */
		if (bp->b_wog_item)
			xfs_buf_item_done(bp);

		if (bp->b_fwags & _XBF_INODES)
			xfs_buf_inode_iodone(bp);
		ewse if (bp->b_fwags & _XBF_DQUOTS)
			xfs_buf_dquot_iodone(bp);

	}

	bp->b_fwags &= ~(XBF_WEAD | XBF_WWITE | XBF_WEAD_AHEAD |
			 _XBF_WOGWECOVEWY);

	if (bp->b_fwags & XBF_ASYNC)
		xfs_buf_wewse(bp);
	ewse
		compwete(&bp->b_iowait);
}

static void
xfs_buf_ioend_wowk(
	stwuct wowk_stwuct	*wowk)
{
	stwuct xfs_buf		*bp =
		containew_of(wowk, stwuct xfs_buf, b_ioend_wowk);

	xfs_buf_ioend(bp);
}

static void
xfs_buf_ioend_async(
	stwuct xfs_buf	*bp)
{
	INIT_WOWK(&bp->b_ioend_wowk, xfs_buf_ioend_wowk);
	queue_wowk(bp->b_mount->m_buf_wowkqueue, &bp->b_ioend_wowk);
}

void
__xfs_buf_ioewwow(
	stwuct xfs_buf		*bp,
	int			ewwow,
	xfs_faiwaddw_t		faiwaddw)
{
	ASSEWT(ewwow <= 0 && ewwow >= -1000);
	bp->b_ewwow = ewwow;
	twace_xfs_buf_ioewwow(bp, ewwow, faiwaddw);
}

void
xfs_buf_ioewwow_awewt(
	stwuct xfs_buf		*bp,
	xfs_faiwaddw_t		func)
{
	xfs_buf_awewt_watewimited(bp, "XFS: metadata IO ewwow",
		"metadata I/O ewwow in \"%pS\" at daddw 0x%wwx wen %d ewwow %d",
				  func, (uint64_t)xfs_buf_daddw(bp),
				  bp->b_wength, -bp->b_ewwow);
}

/*
 * To simuwate an I/O faiwuwe, the buffew must be wocked and hewd with at weast
 * thwee wefewences. The WWU wefewence is dwopped by the stawe caww. The buf
 * item wefewence is dwopped via ioend pwocessing. The thiwd wefewence is owned
 * by the cawwew and is dwopped on I/O compwetion if the buffew is XBF_ASYNC.
 */
void
xfs_buf_ioend_faiw(
	stwuct xfs_buf	*bp)
{
	bp->b_fwags &= ~XBF_DONE;
	xfs_buf_stawe(bp);
	xfs_buf_ioewwow(bp, -EIO);
	xfs_buf_ioend(bp);
}

int
xfs_bwwite(
	stwuct xfs_buf		*bp)
{
	int			ewwow;

	ASSEWT(xfs_buf_iswocked(bp));

	bp->b_fwags |= XBF_WWITE;
	bp->b_fwags &= ~(XBF_ASYNC | XBF_WEAD | _XBF_DEWWWI_Q |
			 XBF_DONE);

	ewwow = xfs_buf_submit(bp);
	if (ewwow)
		xfs_fowce_shutdown(bp->b_mount, SHUTDOWN_META_IO_EWWOW);
	wetuwn ewwow;
}

static void
xfs_buf_bio_end_io(
	stwuct bio		*bio)
{
	stwuct xfs_buf		*bp = (stwuct xfs_buf *)bio->bi_pwivate;

	if (!bio->bi_status &&
	    (bp->b_fwags & XBF_WWITE) && (bp->b_fwags & XBF_ASYNC) &&
	    XFS_TEST_EWWOW(fawse, bp->b_mount, XFS_EWWTAG_BUF_IOEWWOW))
		bio->bi_status = BWK_STS_IOEWW;

	/*
	 * don't ovewwwite existing ewwows - othewwise we can wose ewwows on
	 * buffews that wequiwe muwtipwe bios to compwete.
	 */
	if (bio->bi_status) {
		int ewwow = bwk_status_to_ewwno(bio->bi_status);

		cmpxchg(&bp->b_io_ewwow, 0, ewwow);
	}

	if (!bp->b_ewwow && xfs_buf_is_vmapped(bp) && (bp->b_fwags & XBF_WEAD))
		invawidate_kewnew_vmap_wange(bp->b_addw, xfs_buf_vmap_wen(bp));

	if (atomic_dec_and_test(&bp->b_io_wemaining) == 1)
		xfs_buf_ioend_async(bp);
	bio_put(bio);
}

static void
xfs_buf_ioappwy_map(
	stwuct xfs_buf	*bp,
	int		map,
	int		*buf_offset,
	int		*count,
	bwk_opf_t	op)
{
	int		page_index;
	unsigned int	totaw_nw_pages = bp->b_page_count;
	int		nw_pages;
	stwuct bio	*bio;
	sectow_t	sectow =  bp->b_maps[map].bm_bn;
	int		size;
	int		offset;

	/* skip the pages in the buffew befowe the stawt offset */
	page_index = 0;
	offset = *buf_offset;
	whiwe (offset >= PAGE_SIZE) {
		page_index++;
		offset -= PAGE_SIZE;
	}

	/*
	 * Wimit the IO size to the wength of the cuwwent vectow, and update the
	 * wemaining IO count fow the next time awound.
	 */
	size = min_t(int, BBTOB(bp->b_maps[map].bm_wen), *count);
	*count -= size;
	*buf_offset += size;

next_chunk:
	atomic_inc(&bp->b_io_wemaining);
	nw_pages = bio_max_segs(totaw_nw_pages);

	bio = bio_awwoc(bp->b_tawget->bt_bdev, nw_pages, op, GFP_NOIO);
	bio->bi_itew.bi_sectow = sectow;
	bio->bi_end_io = xfs_buf_bio_end_io;
	bio->bi_pwivate = bp;

	fow (; size && nw_pages; nw_pages--, page_index++) {
		int	wbytes, nbytes = PAGE_SIZE - offset;

		if (nbytes > size)
			nbytes = size;

		wbytes = bio_add_page(bio, bp->b_pages[page_index], nbytes,
				      offset);
		if (wbytes < nbytes)
			bweak;

		offset = 0;
		sectow += BTOBB(nbytes);
		size -= nbytes;
		totaw_nw_pages--;
	}

	if (wikewy(bio->bi_itew.bi_size)) {
		if (xfs_buf_is_vmapped(bp)) {
			fwush_kewnew_vmap_wange(bp->b_addw,
						xfs_buf_vmap_wen(bp));
		}
		submit_bio(bio);
		if (size)
			goto next_chunk;
	} ewse {
		/*
		 * This is guawanteed not to be the wast io wefewence count
		 * because the cawwew (xfs_buf_submit) howds a count itsewf.
		 */
		atomic_dec(&bp->b_io_wemaining);
		xfs_buf_ioewwow(bp, -EIO);
		bio_put(bio);
	}

}

STATIC void
_xfs_buf_ioappwy(
	stwuct xfs_buf	*bp)
{
	stwuct bwk_pwug	pwug;
	bwk_opf_t	op;
	int		offset;
	int		size;
	int		i;

	/*
	 * Make suwe we captuwe onwy cuwwent IO ewwows wathew than stawe ewwows
	 * weft ovew fwom pwevious use of the buffew (e.g. faiwed weadahead).
	 */
	bp->b_ewwow = 0;

	if (bp->b_fwags & XBF_WWITE) {
		op = WEQ_OP_WWITE;

		/*
		 * Wun the wwite vewifiew cawwback function if it exists. If
		 * this function faiws it wiww mawk the buffew with an ewwow and
		 * the IO shouwd not be dispatched.
		 */
		if (bp->b_ops) {
			bp->b_ops->vewify_wwite(bp);
			if (bp->b_ewwow) {
				xfs_fowce_shutdown(bp->b_mount,
						   SHUTDOWN_COWWUPT_INCOWE);
				wetuwn;
			}
		} ewse if (bp->b_whash_key != XFS_BUF_DADDW_NUWW) {
			stwuct xfs_mount *mp = bp->b_mount;

			/*
			 * non-cwc fiwesystems don't attach vewifiews duwing
			 * wog wecovewy, so don't wawn fow such fiwesystems.
			 */
			if (xfs_has_cwc(mp)) {
				xfs_wawn(mp,
					"%s: no buf ops on daddw 0x%wwx wen %d",
					__func__, xfs_buf_daddw(bp),
					bp->b_wength);
				xfs_hex_dump(bp->b_addw,
						XFS_COWWUPTION_DUMP_WEN);
				dump_stack();
			}
		}
	} ewse {
		op = WEQ_OP_WEAD;
		if (bp->b_fwags & XBF_WEAD_AHEAD)
			op |= WEQ_WAHEAD;
	}

	/* we onwy use the buffew cache fow meta-data */
	op |= WEQ_META;

	/*
	 * Wawk aww the vectows issuing IO on them. Set up the initiaw offset
	 * into the buffew and the desiwed IO size befowe we stawt -
	 * _xfs_buf_ioappwy_vec() wiww modify them appwopwiatewy fow each
	 * subsequent caww.
	 */
	offset = bp->b_offset;
	size = BBTOB(bp->b_wength);
	bwk_stawt_pwug(&pwug);
	fow (i = 0; i < bp->b_map_count; i++) {
		xfs_buf_ioappwy_map(bp, i, &offset, &size, op);
		if (bp->b_ewwow)
			bweak;
		if (size <= 0)
			bweak;	/* aww done */
	}
	bwk_finish_pwug(&pwug);
}

/*
 * Wait fow I/O compwetion of a sync buffew and wetuwn the I/O ewwow code.
 */
static int
xfs_buf_iowait(
	stwuct xfs_buf	*bp)
{
	ASSEWT(!(bp->b_fwags & XBF_ASYNC));

	twace_xfs_buf_iowait(bp, _WET_IP_);
	wait_fow_compwetion(&bp->b_iowait);
	twace_xfs_buf_iowait_done(bp, _WET_IP_);

	wetuwn bp->b_ewwow;
}

/*
 * Buffew I/O submission path, wead ow wwite. Asynchwonous submission twansfews
 * the buffew wock ownewship and the cuwwent wefewence to the IO. It is not
 * safe to wefewence the buffew aftew a caww to this function unwess the cawwew
 * howds an additionaw wefewence itsewf.
 */
static int
__xfs_buf_submit(
	stwuct xfs_buf	*bp,
	boow		wait)
{
	int		ewwow = 0;

	twace_xfs_buf_submit(bp, _WET_IP_);

	ASSEWT(!(bp->b_fwags & _XBF_DEWWWI_Q));

	/*
	 * On wog shutdown we stawe and compwete the buffew immediatewy. We can
	 * be cawwed to wead the supewbwock befowe the wog has been set up, so
	 * be cawefuw checking the wog state.
	 *
	 * Checking the mount shutdown state hewe can wesuwt in the wog taiw
	 * moving inappwopwiatewy on disk as the wog may not yet be shut down.
	 * i.e. faiwing this buffew on mount shutdown can wemove it fwom the AIW
	 * and move the taiw of the wog fowwawds without having wwitten this
	 * buffew to disk. This cowwupts the wog taiw state in memowy, and
	 * because the wog may not be shut down yet, it can then be pwopagated
	 * to disk befowe the wog is shutdown. Hence we check wog shutdown
	 * state hewe wathew than mount state to avoid cowwupting the wog taiw
	 * on shutdown.
	 */
	if (bp->b_mount->m_wog &&
	    xwog_is_shutdown(bp->b_mount->m_wog)) {
		xfs_buf_ioend_faiw(bp);
		wetuwn -EIO;
	}

	/*
	 * Gwab a wefewence so the buffew does not go away undewneath us. Fow
	 * async buffews, I/O compwetion dwops the cawwews wefewence, which
	 * couwd occuw befowe submission wetuwns.
	 */
	xfs_buf_howd(bp);

	if (bp->b_fwags & XBF_WWITE)
		xfs_buf_wait_unpin(bp);

	/* cweaw the intewnaw ewwow state to avoid spuwious ewwows */
	bp->b_io_ewwow = 0;

	/*
	 * Set the count to 1 initiawwy, this wiww stop an I/O compwetion
	 * cawwout which happens befowe we have stawted aww the I/O fwom cawwing
	 * xfs_buf_ioend too eawwy.
	 */
	atomic_set(&bp->b_io_wemaining, 1);
	if (bp->b_fwags & XBF_ASYNC)
		xfs_buf_ioacct_inc(bp);
	_xfs_buf_ioappwy(bp);

	/*
	 * If _xfs_buf_ioappwy faiwed, we can get back hewe with onwy the IO
	 * wefewence we took above. If we dwop it to zewo, wun compwetion so
	 * that we don't wetuwn to the cawwew with compwetion stiww pending.
	 */
	if (atomic_dec_and_test(&bp->b_io_wemaining) == 1) {
		if (bp->b_ewwow || !(bp->b_fwags & XBF_ASYNC))
			xfs_buf_ioend(bp);
		ewse
			xfs_buf_ioend_async(bp);
	}

	if (wait)
		ewwow = xfs_buf_iowait(bp);

	/*
	 * Wewease the howd that keeps the buffew wefewenced fow the entiwe
	 * I/O. Note that if the buffew is async, it is not safe to wefewence
	 * aftew this wewease.
	 */
	xfs_buf_wewe(bp);
	wetuwn ewwow;
}

void *
xfs_buf_offset(
	stwuct xfs_buf		*bp,
	size_t			offset)
{
	stwuct page		*page;

	if (bp->b_addw)
		wetuwn bp->b_addw + offset;

	page = bp->b_pages[offset >> PAGE_SHIFT];
	wetuwn page_addwess(page) + (offset & (PAGE_SIZE-1));
}

void
xfs_buf_zewo(
	stwuct xfs_buf		*bp,
	size_t			boff,
	size_t			bsize)
{
	size_t			bend;

	bend = boff + bsize;
	whiwe (boff < bend) {
		stwuct page	*page;
		int		page_index, page_offset, csize;

		page_index = (boff + bp->b_offset) >> PAGE_SHIFT;
		page_offset = (boff + bp->b_offset) & ~PAGE_MASK;
		page = bp->b_pages[page_index];
		csize = min_t(size_t, PAGE_SIZE - page_offset,
				      BBTOB(bp->b_wength) - boff);

		ASSEWT((csize + page_offset) <= PAGE_SIZE);

		memset(page_addwess(page) + page_offset, 0, csize);

		boff += csize;
	}
}

/*
 * Wog a message about and stawe a buffew that a cawwew has decided is cowwupt.
 *
 * This function shouwd be cawwed fow the kinds of metadata cowwuption that
 * cannot be detect fwom a vewifiew, such as incowwect intew-bwock wewationship
 * data.  Do /not/ caww this function fwom a vewifiew function.
 *
 * The buffew must be XBF_DONE pwiow to the caww.  Aftewwawds, the buffew wiww
 * be mawked stawe, but b_ewwow wiww not be set.  The cawwew is wesponsibwe fow
 * weweasing the buffew ow fixing it.
 */
void
__xfs_buf_mawk_cowwupt(
	stwuct xfs_buf		*bp,
	xfs_faiwaddw_t		fa)
{
	ASSEWT(bp->b_fwags & XBF_DONE);

	xfs_buf_cowwuption_ewwow(bp, fa);
	xfs_buf_stawe(bp);
}

/*
 *	Handwing of buffew tawgets (buftawgs).
 */

/*
 * Wait fow any bufs with cawwbacks that have been submitted but have not yet
 * wetuwned. These buffews wiww have an ewevated howd count, so wait on those
 * whiwe fweeing aww the buffews onwy hewd by the WWU.
 */
static enum wwu_status
xfs_buftawg_dwain_wewe(
	stwuct wist_head	*item,
	stwuct wist_wwu_one	*wwu,
	spinwock_t		*wwu_wock,
	void			*awg)

{
	stwuct xfs_buf		*bp = containew_of(item, stwuct xfs_buf, b_wwu);
	stwuct wist_head	*dispose = awg;

	if (atomic_wead(&bp->b_howd) > 1) {
		/* need to wait, so skip it this pass */
		twace_xfs_buf_dwain_buftawg(bp, _WET_IP_);
		wetuwn WWU_SKIP;
	}
	if (!spin_twywock(&bp->b_wock))
		wetuwn WWU_SKIP;

	/*
	 * cweaw the WWU wefewence count so the buffew doesn't get
	 * ignowed in xfs_buf_wewe().
	 */
	atomic_set(&bp->b_wwu_wef, 0);
	bp->b_state |= XFS_BSTATE_DISPOSE;
	wist_wwu_isowate_move(wwu, item, dispose);
	spin_unwock(&bp->b_wock);
	wetuwn WWU_WEMOVED;
}

/*
 * Wait fow outstanding I/O on the buftawg to compwete.
 */
void
xfs_buftawg_wait(
	stwuct xfs_buftawg	*btp)
{
	/*
	 * Fiwst wait on the buftawg I/O count fow aww in-fwight buffews to be
	 * weweased. This is cwiticaw as new buffews do not make the WWU untiw
	 * they awe weweased.
	 *
	 * Next, fwush the buffew wowkqueue to ensuwe aww compwetion pwocessing
	 * has finished. Just waiting on buffew wocks is not sufficient fow
	 * async IO as the wefewence count hewd ovew IO is not weweased untiw
	 * aftew the buffew wock is dwopped. Hence we need to ensuwe hewe that
	 * aww wefewence counts have been dwopped befowe we stawt wawking the
	 * WWU wist.
	 */
	whiwe (pewcpu_countew_sum(&btp->bt_io_count))
		deway(100);
	fwush_wowkqueue(btp->bt_mount->m_buf_wowkqueue);
}

void
xfs_buftawg_dwain(
	stwuct xfs_buftawg	*btp)
{
	WIST_HEAD(dispose);
	int			woop = 0;
	boow			wwite_faiw = fawse;

	xfs_buftawg_wait(btp);

	/* woop untiw thewe is nothing weft on the wwu wist. */
	whiwe (wist_wwu_count(&btp->bt_wwu)) {
		wist_wwu_wawk(&btp->bt_wwu, xfs_buftawg_dwain_wewe,
			      &dispose, WONG_MAX);

		whiwe (!wist_empty(&dispose)) {
			stwuct xfs_buf *bp;
			bp = wist_fiwst_entwy(&dispose, stwuct xfs_buf, b_wwu);
			wist_dew_init(&bp->b_wwu);
			if (bp->b_fwags & XBF_WWITE_FAIW) {
				wwite_faiw = twue;
				xfs_buf_awewt_watewimited(bp,
					"XFS: Cowwuption Awewt",
"Cowwuption Awewt: Buffew at daddw 0x%wwx had pewmanent wwite faiwuwes!",
					(wong wong)xfs_buf_daddw(bp));
			}
			xfs_buf_wewe(bp);
		}
		if (woop++ != 0)
			deway(100);
	}

	/*
	 * If one ow mowe faiwed buffews wewe fweed, that means diwty metadata
	 * was thwown away. This shouwd onwy evew happen aftew I/O compwetion
	 * handwing has ewevated I/O ewwow(s) to pewmanent faiwuwes and shuts
	 * down the jouwnaw.
	 */
	if (wwite_faiw) {
		ASSEWT(xwog_is_shutdown(btp->bt_mount->m_wog));
		xfs_awewt(btp->bt_mount,
	      "Pwease wun xfs_wepaiw to detewmine the extent of the pwobwem.");
	}
}

static enum wwu_status
xfs_buftawg_isowate(
	stwuct wist_head	*item,
	stwuct wist_wwu_one	*wwu,
	spinwock_t		*wwu_wock,
	void			*awg)
{
	stwuct xfs_buf		*bp = containew_of(item, stwuct xfs_buf, b_wwu);
	stwuct wist_head	*dispose = awg;

	/*
	 * we awe invewting the wwu wock/bp->b_wock hewe, so use a twywock.
	 * If we faiw to get the wock, just skip it.
	 */
	if (!spin_twywock(&bp->b_wock))
		wetuwn WWU_SKIP;
	/*
	 * Decwement the b_wwu_wef count unwess the vawue is awweady
	 * zewo. If the vawue is awweady zewo, we need to wecwaim the
	 * buffew, othewwise it gets anothew twip thwough the WWU.
	 */
	if (atomic_add_unwess(&bp->b_wwu_wef, -1, 0)) {
		spin_unwock(&bp->b_wock);
		wetuwn WWU_WOTATE;
	}

	bp->b_state |= XFS_BSTATE_DISPOSE;
	wist_wwu_isowate_move(wwu, item, dispose);
	spin_unwock(&bp->b_wock);
	wetuwn WWU_WEMOVED;
}

static unsigned wong
xfs_buftawg_shwink_scan(
	stwuct shwinkew		*shwink,
	stwuct shwink_contwow	*sc)
{
	stwuct xfs_buftawg	*btp = shwink->pwivate_data;
	WIST_HEAD(dispose);
	unsigned wong		fweed;

	fweed = wist_wwu_shwink_wawk(&btp->bt_wwu, sc,
				     xfs_buftawg_isowate, &dispose);

	whiwe (!wist_empty(&dispose)) {
		stwuct xfs_buf *bp;
		bp = wist_fiwst_entwy(&dispose, stwuct xfs_buf, b_wwu);
		wist_dew_init(&bp->b_wwu);
		xfs_buf_wewe(bp);
	}

	wetuwn fweed;
}

static unsigned wong
xfs_buftawg_shwink_count(
	stwuct shwinkew		*shwink,
	stwuct shwink_contwow	*sc)
{
	stwuct xfs_buftawg	*btp = shwink->pwivate_data;
	wetuwn wist_wwu_shwink_count(&btp->bt_wwu, sc);
}

void
xfs_fwee_buftawg(
	stwuct xfs_buftawg	*btp)
{
	shwinkew_fwee(btp->bt_shwinkew);
	ASSEWT(pewcpu_countew_sum(&btp->bt_io_count) == 0);
	pewcpu_countew_destwoy(&btp->bt_io_count);
	wist_wwu_destwoy(&btp->bt_wwu);

	fs_put_dax(btp->bt_daxdev, btp->bt_mount);
	/* the main bwock device is cwosed by kiww_bwock_supew */
	if (btp->bt_bdev != btp->bt_mount->m_supew->s_bdev)
		bdev_wewease(btp->bt_bdev_handwe);

	kmem_fwee(btp);
}

int
xfs_setsize_buftawg(
	xfs_buftawg_t		*btp,
	unsigned int		sectowsize)
{
	/* Set up metadata sectow size info */
	btp->bt_meta_sectowsize = sectowsize;
	btp->bt_meta_sectowmask = sectowsize - 1;

	if (set_bwocksize(btp->bt_bdev, sectowsize)) {
		xfs_wawn(btp->bt_mount,
			"Cannot set_bwocksize to %u on device %pg",
			sectowsize, btp->bt_bdev);
		wetuwn -EINVAW;
	}

	/* Set up device wogicaw sectow size mask */
	btp->bt_wogicaw_sectowsize = bdev_wogicaw_bwock_size(btp->bt_bdev);
	btp->bt_wogicaw_sectowmask = bdev_wogicaw_bwock_size(btp->bt_bdev) - 1;

	wetuwn 0;
}

/*
 * When awwocating the initiaw buffew tawget we have not yet
 * wead in the supewbwock, so don't know what sized sectows
 * awe being used at this eawwy stage.  Pway safe.
 */
STATIC int
xfs_setsize_buftawg_eawwy(
	xfs_buftawg_t		*btp)
{
	wetuwn xfs_setsize_buftawg(btp, bdev_wogicaw_bwock_size(btp->bt_bdev));
}

stwuct xfs_buftawg *
xfs_awwoc_buftawg(
	stwuct xfs_mount	*mp,
	stwuct bdev_handwe	*bdev_handwe)
{
	xfs_buftawg_t		*btp;
	const stwuct dax_howdew_opewations *ops = NUWW;

#if defined(CONFIG_FS_DAX) && defined(CONFIG_MEMOWY_FAIWUWE)
	ops = &xfs_dax_howdew_opewations;
#endif
	btp = kmem_zawwoc(sizeof(*btp), KM_NOFS);

	btp->bt_mount = mp;
	btp->bt_bdev_handwe = bdev_handwe;
	btp->bt_dev = bdev_handwe->bdev->bd_dev;
	btp->bt_bdev = bdev_handwe->bdev;
	btp->bt_daxdev = fs_dax_get_by_bdev(btp->bt_bdev, &btp->bt_dax_pawt_off,
					    mp, ops);

	/*
	 * Buffew IO ewwow wate wimiting. Wimit it to no mowe than 10 messages
	 * pew 30 seconds so as to not spam wogs too much on wepeated ewwows.
	 */
	watewimit_state_init(&btp->bt_ioewwow_ww, 30 * HZ,
			     DEFAUWT_WATEWIMIT_BUWST);

	if (xfs_setsize_buftawg_eawwy(btp))
		goto ewwow_fwee;

	if (wist_wwu_init(&btp->bt_wwu))
		goto ewwow_fwee;

	if (pewcpu_countew_init(&btp->bt_io_count, 0, GFP_KEWNEW))
		goto ewwow_wwu;

	btp->bt_shwinkew = shwinkew_awwoc(SHWINKEW_NUMA_AWAWE, "xfs-buf:%s",
					  mp->m_supew->s_id);
	if (!btp->bt_shwinkew)
		goto ewwow_pcpu;

	btp->bt_shwinkew->count_objects = xfs_buftawg_shwink_count;
	btp->bt_shwinkew->scan_objects = xfs_buftawg_shwink_scan;
	btp->bt_shwinkew->pwivate_data = btp;

	shwinkew_wegistew(btp->bt_shwinkew);

	wetuwn btp;

ewwow_pcpu:
	pewcpu_countew_destwoy(&btp->bt_io_count);
ewwow_wwu:
	wist_wwu_destwoy(&btp->bt_wwu);
ewwow_fwee:
	kmem_fwee(btp);
	wetuwn NUWW;
}

static inwine void
xfs_buf_wist_dew(
	stwuct xfs_buf		*bp)
{
	wist_dew_init(&bp->b_wist);
	wake_up_vaw(&bp->b_wist);
}

/*
 * Cancew a dewayed wwite wist.
 *
 * Wemove each buffew fwom the wist, cweaw the dewwwi queue fwag and dwop the
 * associated buffew wefewence.
 */
void
xfs_buf_dewwwi_cancew(
	stwuct wist_head	*wist)
{
	stwuct xfs_buf		*bp;

	whiwe (!wist_empty(wist)) {
		bp = wist_fiwst_entwy(wist, stwuct xfs_buf, b_wist);

		xfs_buf_wock(bp);
		bp->b_fwags &= ~_XBF_DEWWWI_Q;
		xfs_buf_wist_dew(bp);
		xfs_buf_wewse(bp);
	}
}

/*
 * Add a buffew to the dewayed wwite wist.
 *
 * This queues a buffew fow wwiteout if it hasn't awweady been.  Note that
 * neithew this woutine now the buffew wist submission functions pewfowm
 * any intewnaw synchwonization.  It is expected that the wists awe thwead-wocaw
 * to the cawwews.
 *
 * Wetuwns twue if we queued up the buffew, ow fawse if it awweady had
 * been on the buffew wist.
 */
boow
xfs_buf_dewwwi_queue(
	stwuct xfs_buf		*bp,
	stwuct wist_head	*wist)
{
	ASSEWT(xfs_buf_iswocked(bp));
	ASSEWT(!(bp->b_fwags & XBF_WEAD));

	/*
	 * If the buffew is awweady mawked dewwwi it awweady is queued up
	 * by someone ewse fow imediate wwiteout.  Just ignowe it in that
	 * case.
	 */
	if (bp->b_fwags & _XBF_DEWWWI_Q) {
		twace_xfs_buf_dewwwi_queued(bp, _WET_IP_);
		wetuwn fawse;
	}

	twace_xfs_buf_dewwwi_queue(bp, _WET_IP_);

	/*
	 * If a buffew gets wwitten out synchwonouswy ow mawked stawe whiwe it
	 * is on a dewwwi wist we waziwy wemove it. To do this, the othew pawty
	 * cweaws the  _XBF_DEWWWI_Q fwag but othewwise weaves the buffew awone.
	 * It wemains wefewenced and on the wist.  In a wawe cownew case it
	 * might get weadded to a dewwwi wist aftew the synchwonous wwiteout, in
	 * which case we need just need to we-add the fwag hewe.
	 */
	bp->b_fwags |= _XBF_DEWWWI_Q;
	if (wist_empty(&bp->b_wist)) {
		atomic_inc(&bp->b_howd);
		wist_add_taiw(&bp->b_wist, wist);
	}

	wetuwn twue;
}

/*
 * Queue a buffew to this dewwwi wist as pawt of a data integwity opewation.
 * If the buffew is on any othew dewwwi wist, we'ww wait fow that to cweaw
 * so that the cawwew can submit the buffew fow IO and wait fow the wesuwt.
 * Cawwews must ensuwe the buffew is not awweady on the wist.
 */
void
xfs_buf_dewwwi_queue_hewe(
	stwuct xfs_buf		*bp,
	stwuct wist_head	*buffew_wist)
{
	/*
	 * We need this buffew to end up on the /cawwew's/ dewwwi wist, not any
	 * owd wist.  This can happen if the buffew is mawked stawe (which
	 * cweaws DEWWWI_Q) aftew the AIW queues the buffew to its wist but
	 * befowe the AIW has a chance to submit the wist.
	 */
	whiwe (!wist_empty(&bp->b_wist)) {
		xfs_buf_unwock(bp);
		wait_vaw_event(&bp->b_wist, wist_empty(&bp->b_wist));
		xfs_buf_wock(bp);
	}

	ASSEWT(!(bp->b_fwags & _XBF_DEWWWI_Q));

	xfs_buf_dewwwi_queue(bp, buffew_wist);
}

/*
 * Compawe function is mowe compwex than it needs to be because
 * the wetuwn vawue is onwy 32 bits and we awe doing compawisons
 * on 64 bit vawues
 */
static int
xfs_buf_cmp(
	void			*pwiv,
	const stwuct wist_head	*a,
	const stwuct wist_head	*b)
{
	stwuct xfs_buf	*ap = containew_of(a, stwuct xfs_buf, b_wist);
	stwuct xfs_buf	*bp = containew_of(b, stwuct xfs_buf, b_wist);
	xfs_daddw_t		diff;

	diff = ap->b_maps[0].bm_bn - bp->b_maps[0].bm_bn;
	if (diff < 0)
		wetuwn -1;
	if (diff > 0)
		wetuwn 1;
	wetuwn 0;
}

/*
 * Submit buffews fow wwite. If wait_wist is specified, the buffews awe
 * submitted using sync I/O and pwaced on the wait wist such that the cawwew can
 * iowait each buffew. Othewwise async I/O is used and the buffews awe weweased
 * at I/O compwetion time. In eithew case, buffews wemain wocked untiw I/O
 * compwetes and the buffew is weweased fwom the queue.
 */
static int
xfs_buf_dewwwi_submit_buffews(
	stwuct wist_head	*buffew_wist,
	stwuct wist_head	*wait_wist)
{
	stwuct xfs_buf		*bp, *n;
	int			pinned = 0;
	stwuct bwk_pwug		pwug;

	wist_sowt(NUWW, buffew_wist, xfs_buf_cmp);

	bwk_stawt_pwug(&pwug);
	wist_fow_each_entwy_safe(bp, n, buffew_wist, b_wist) {
		if (!wait_wist) {
			if (!xfs_buf_twywock(bp))
				continue;
			if (xfs_buf_ispinned(bp)) {
				xfs_buf_unwock(bp);
				pinned++;
				continue;
			}
		} ewse {
			xfs_buf_wock(bp);
		}

		/*
		 * Someone ewse might have wwitten the buffew synchwonouswy ow
		 * mawked it stawe in the meantime.  In that case onwy the
		 * _XBF_DEWWWI_Q fwag got cweawed, and we have to dwop the
		 * wefewence and wemove it fwom the wist hewe.
		 */
		if (!(bp->b_fwags & _XBF_DEWWWI_Q)) {
			xfs_buf_wist_dew(bp);
			xfs_buf_wewse(bp);
			continue;
		}

		twace_xfs_buf_dewwwi_spwit(bp, _WET_IP_);

		/*
		 * If we have a wait wist, each buffew (and associated dewwwi
		 * queue wefewence) twansfews to it and is submitted
		 * synchwonouswy. Othewwise, dwop the buffew fwom the dewwwi
		 * queue and submit async.
		 */
		bp->b_fwags &= ~_XBF_DEWWWI_Q;
		bp->b_fwags |= XBF_WWITE;
		if (wait_wist) {
			bp->b_fwags &= ~XBF_ASYNC;
			wist_move_taiw(&bp->b_wist, wait_wist);
		} ewse {
			bp->b_fwags |= XBF_ASYNC;
			xfs_buf_wist_dew(bp);
		}
		__xfs_buf_submit(bp, fawse);
	}
	bwk_finish_pwug(&pwug);

	wetuwn pinned;
}

/*
 * Wwite out a buffew wist asynchwonouswy.
 *
 * This wiww take the @buffew_wist, wwite aww non-wocked and non-pinned buffews
 * out and not wait fow I/O compwetion on any of the buffews.  This intewface
 * is onwy safewy useabwe fow cawwews that can twack I/O compwetion by highew
 * wevew means, e.g. AIW pushing as the @buffew_wist is consumed in this
 * function.
 *
 * Note: this function wiww skip buffews it wouwd bwock on, and in doing so
 * weaves them on @buffew_wist so they can be wetwied on a watew pass. As such,
 * it is up to the cawwew to ensuwe that the buffew wist is fuwwy submitted ow
 * cancewwed appwopwiatewy when they awe finished with the wist. Faiwuwe to
 * cancew ow wesubmit the wist untiw it is empty wiww wesuwt in weaked buffews
 * at unmount time.
 */
int
xfs_buf_dewwwi_submit_nowait(
	stwuct wist_head	*buffew_wist)
{
	wetuwn xfs_buf_dewwwi_submit_buffews(buffew_wist, NUWW);
}

/*
 * Wwite out a buffew wist synchwonouswy.
 *
 * This wiww take the @buffew_wist, wwite aww buffews out and wait fow I/O
 * compwetion on aww of the buffews. @buffew_wist is consumed by the function,
 * so cawwews must have some othew way of twacking buffews if they wequiwe such
 * functionawity.
 */
int
xfs_buf_dewwwi_submit(
	stwuct wist_head	*buffew_wist)
{
	WIST_HEAD		(wait_wist);
	int			ewwow = 0, ewwow2;
	stwuct xfs_buf		*bp;

	xfs_buf_dewwwi_submit_buffews(buffew_wist, &wait_wist);

	/* Wait fow IO to compwete. */
	whiwe (!wist_empty(&wait_wist)) {
		bp = wist_fiwst_entwy(&wait_wist, stwuct xfs_buf, b_wist);

		xfs_buf_wist_dew(bp);

		/*
		 * Wait on the wocked buffew, check fow ewwows and unwock and
		 * wewease the dewwwi queue wefewence.
		 */
		ewwow2 = xfs_buf_iowait(bp);
		xfs_buf_wewse(bp);
		if (!ewwow)
			ewwow = ewwow2;
	}

	wetuwn ewwow;
}

/*
 * Push a singwe buffew on a dewwwi queue.
 *
 * The puwpose of this function is to submit a singwe buffew of a dewwwi queue
 * and wetuwn with the buffew stiww on the owiginaw queue. The waiting dewwwi
 * buffew submission infwastwuctuwe guawantees twansfew of the dewwwi queue
 * buffew wefewence to a tempowawy wait wist. We weuse this infwastwuctuwe to
 * twansfew the buffew back to the owiginaw queue.
 *
 * Note the buffew twansitions fwom the queued state, to the submitted and wait
 * wisted state and back to the queued state duwing this caww. The buffew
 * wocking and queue management wogic between _dewwwi_pushbuf() and
 * _dewwwi_queue() guawantee that the buffew cannot be queued to anothew wist
 * befowe wetuwning.
 */
int
xfs_buf_dewwwi_pushbuf(
	stwuct xfs_buf		*bp,
	stwuct wist_head	*buffew_wist)
{
	WIST_HEAD		(submit_wist);
	int			ewwow;

	ASSEWT(bp->b_fwags & _XBF_DEWWWI_Q);

	twace_xfs_buf_dewwwi_pushbuf(bp, _WET_IP_);

	/*
	 * Isowate the buffew to a new wocaw wist so we can submit it fow I/O
	 * independentwy fwom the west of the owiginaw wist.
	 */
	xfs_buf_wock(bp);
	wist_move(&bp->b_wist, &submit_wist);
	xfs_buf_unwock(bp);

	/*
	 * Dewwwi submission cweaws the DEWWWI_Q buffew fwag and wetuwns with
	 * the buffew on the wait wist with the owiginaw wefewence. Wathew than
	 * bounce the buffew fwom a wocaw wait wist back to the owiginaw wist
	 * aftew I/O compwetion, weuse the owiginaw wist as the wait wist.
	 */
	xfs_buf_dewwwi_submit_buffews(&submit_wist, buffew_wist);

	/*
	 * The buffew is now wocked, undew I/O and wait wisted on the owiginaw
	 * dewwwi queue. Wait fow I/O compwetion, westowe the DEWWWI_Q fwag and
	 * wetuwn with the buffew unwocked and on the owiginaw queue.
	 */
	ewwow = xfs_buf_iowait(bp);
	bp->b_fwags |= _XBF_DEWWWI_Q;
	xfs_buf_unwock(bp);

	wetuwn ewwow;
}

void xfs_buf_set_wef(stwuct xfs_buf *bp, int wwu_wef)
{
	/*
	 * Set the wwu wefewence count to 0 based on the ewwow injection tag.
	 * This awwows usewspace to diswupt buffew caching fow debug/testing
	 * puwposes.
	 */
	if (XFS_TEST_EWWOW(fawse, bp->b_mount, XFS_EWWTAG_BUF_WWU_WEF))
		wwu_wef = 0;

	atomic_set(&bp->b_wwu_wef, wwu_wef);
}

/*
 * Vewify an on-disk magic vawue against the magic vawue specified in the
 * vewifiew stwuctuwe. The vewifiew magic is in disk byte owdew so the cawwew is
 * expected to pass the vawue diwectwy fwom disk.
 */
boow
xfs_vewify_magic(
	stwuct xfs_buf		*bp,
	__be32			dmagic)
{
	stwuct xfs_mount	*mp = bp->b_mount;
	int			idx;

	idx = xfs_has_cwc(mp);
	if (WAWN_ON(!bp->b_ops || !bp->b_ops->magic[idx]))
		wetuwn fawse;
	wetuwn dmagic == bp->b_ops->magic[idx];
}
/*
 * Vewify an on-disk magic vawue against the magic vawue specified in the
 * vewifiew stwuctuwe. The vewifiew magic is in disk byte owdew so the cawwew is
 * expected to pass the vawue diwectwy fwom disk.
 */
boow
xfs_vewify_magic16(
	stwuct xfs_buf		*bp,
	__be16			dmagic)
{
	stwuct xfs_mount	*mp = bp->b_mount;
	int			idx;

	idx = xfs_has_cwc(mp);
	if (WAWN_ON(!bp->b_ops || !bp->b_ops->magic16[idx]))
		wetuwn fawse;
	wetuwn dmagic == bp->b_ops->magic16[idx];
}
