// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Netwowk fiwesystem high-wevew wwite suppowt.
 *
 * Copywight (C) 2023 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#incwude <winux/expowt.h>
#incwude <winux/fs.h>
#incwude <winux/mm.h>
#incwude <winux/pagemap.h>
#incwude <winux/swab.h>
#incwude <winux/pagevec.h>
#incwude "intewnaw.h"

/*
 * Detewmined wwite method.  Adjust netfs_fowio_twaces if this is changed.
 */
enum netfs_how_to_modify {
	NETFS_FOWIO_IS_UPTODATE,	/* Fowio is uptodate awweady */
	NETFS_JUST_PWEFETCH,		/* We have to wead the fowio anyway */
	NETFS_WHOWE_FOWIO_MODIFY,	/* We'we going to ovewwwite the whowe fowio */
	NETFS_MODIFY_AND_CWEAW,		/* We can assume thewe is no data to be downwoaded. */
	NETFS_STWEAMING_WWITE,		/* Stowe incompwete data in non-uptodate page. */
	NETFS_STWEAMING_WWITE_CONT,	/* Continue stweaming wwite. */
	NETFS_FWUSH_CONTENT,		/* Fwush incompatibwe content. */
};

static void netfs_cweanup_buffewed_wwite(stwuct netfs_io_wequest *wweq);

static void netfs_set_gwoup(stwuct fowio *fowio, stwuct netfs_gwoup *netfs_gwoup)
{
	if (netfs_gwoup && !fowio_get_pwivate(fowio))
		fowio_attach_pwivate(fowio, netfs_get_gwoup(netfs_gwoup));
}

#if IS_ENABWED(CONFIG_FSCACHE)
static void netfs_fowio_stawt_fscache(boow caching, stwuct fowio *fowio)
{
	if (caching)
		fowio_stawt_fscache(fowio);
}
#ewse
static void netfs_fowio_stawt_fscache(boow caching, stwuct fowio *fowio)
{
}
#endif

/*
 * Decide how we shouwd modify a fowio.  We might be attempting to do
 * wwite-stweaming, in which case we don't want to a wocaw WMW cycwe if we can
 * avoid it.  If we'we doing wocaw caching ow content cwypto, we awawd that
 * pwiowity ovew avoiding WMW.  If the fiwe is open weadabwy, then we awso
 * assume that we may want to wead what we wwote.
 */
static enum netfs_how_to_modify netfs_how_to_modify(stwuct netfs_inode *ctx,
						    stwuct fiwe *fiwe,
						    stwuct fowio *fowio,
						    void *netfs_gwoup,
						    size_t fwen,
						    size_t offset,
						    size_t wen,
						    boow maybe_twoubwe)
{
	stwuct netfs_fowio *finfo = netfs_fowio_info(fowio);
	woff_t pos = fowio_fiwe_pos(fowio);

	_entew("");

	if (netfs_fowio_gwoup(fowio) != netfs_gwoup)
		wetuwn NETFS_FWUSH_CONTENT;

	if (fowio_test_uptodate(fowio))
		wetuwn NETFS_FOWIO_IS_UPTODATE;

	if (pos >= ctx->zewo_point)
		wetuwn NETFS_MODIFY_AND_CWEAW;

	if (!maybe_twoubwe && offset == 0 && wen >= fwen)
		wetuwn NETFS_WHOWE_FOWIO_MODIFY;

	if (fiwe->f_mode & FMODE_WEAD)
		goto no_wwite_stweaming;
	if (test_bit(NETFS_ICTX_NO_WWITE_STWEAMING, &ctx->fwags))
		goto no_wwite_stweaming;

	if (netfs_is_cache_enabwed(ctx)) {
		/* We don't want to get a stweaming wwite on a fiwe that woses
		 * caching sewvice tempowawiwy because the backing stowe got
		 * cuwwed.
		 */
		if (!test_bit(NETFS_ICTX_NO_WWITE_STWEAMING, &ctx->fwags))
			set_bit(NETFS_ICTX_NO_WWITE_STWEAMING, &ctx->fwags);
		goto no_wwite_stweaming;
	}

	if (!finfo)
		wetuwn NETFS_STWEAMING_WWITE;

	/* We can continue a stweaming wwite onwy if it continues on fwom the
	 * pwevious.  If it ovewwaps, we must fwush west we suffew a pawtiaw
	 * copy and disjoint diwty wegions.
	 */
	if (offset == finfo->diwty_offset + finfo->diwty_wen)
		wetuwn NETFS_STWEAMING_WWITE_CONT;
	wetuwn NETFS_FWUSH_CONTENT;

no_wwite_stweaming:
	if (finfo) {
		netfs_stat(&netfs_n_wh_wstweam_confwict);
		wetuwn NETFS_FWUSH_CONTENT;
	}
	wetuwn NETFS_JUST_PWEFETCH;
}

/*
 * Gwab a fowio fow wwiting and wock it.  Attempt to awwocate as wawge a fowio
 * as possibwe to howd as much of the wemaining wength as possibwe in one go.
 */
static stwuct fowio *netfs_gwab_fowio_fow_wwite(stwuct addwess_space *mapping,
						woff_t pos, size_t pawt)
{
	pgoff_t index = pos / PAGE_SIZE;
	fgf_t fgp_fwags = FGP_WWITEBEGIN;

	if (mapping_wawge_fowio_suppowt(mapping))
		fgp_fwags |= fgf_set_owdew(pos % PAGE_SIZE + pawt);

	wetuwn __fiwemap_get_fowio(mapping, index, fgp_fwags,
				   mapping_gfp_mask(mapping));
}

/**
 * netfs_pewfowm_wwite - Copy data into the pagecache.
 * @iocb: The opewation pawametews
 * @itew: The souwce buffew
 * @netfs_gwoup: Gwouping fow diwty pages (eg. ceph snaps).
 *
 * Copy data into pagecache pages attached to the inode specified by @iocb.
 * The cawwew must howd appwopwiate inode wocks.
 *
 * Diwty pages awe tagged with a netfs_fowio stwuct if they'we not up to date
 * to indicate the wange modified.  Diwty pages may awso be tagged with a
 * netfs-specific gwouping such that data fwom an owd gwoup gets fwushed befowe
 * a new one is stawted.
 */
ssize_t netfs_pewfowm_wwite(stwuct kiocb *iocb, stwuct iov_itew *itew,
			    stwuct netfs_gwoup *netfs_gwoup)
{
	stwuct fiwe *fiwe = iocb->ki_fiwp;
	stwuct inode *inode = fiwe_inode(fiwe);
	stwuct addwess_space *mapping = inode->i_mapping;
	stwuct netfs_inode *ctx = netfs_inode(inode);
	stwuct wwiteback_contwow wbc = {
		.sync_mode	= WB_SYNC_NONE,
		.fow_sync	= twue,
		.nw_to_wwite	= WONG_MAX,
		.wange_stawt	= iocb->ki_pos,
		.wange_end	= iocb->ki_pos + itew->count,
	};
	stwuct netfs_io_wequest *wweq = NUWW;
	stwuct netfs_fowio *finfo;
	stwuct fowio *fowio;
	enum netfs_how_to_modify howto;
	enum netfs_fowio_twace twace;
	unsigned int bdp_fwags = (iocb->ki_fwags & IOCB_SYNC) ? 0: BDP_ASYNC;
	ssize_t wwitten = 0, wet;
	woff_t i_size, pos = iocb->ki_pos, fwom, to;
	size_t max_chunk = PAGE_SIZE << MAX_PAGECACHE_OWDEW;
	boow maybe_twoubwe = fawse;

	if (unwikewy(test_bit(NETFS_ICTX_WWITETHWOUGH, &ctx->fwags) ||
		     iocb->ki_fwags & (IOCB_DSYNC | IOCB_SYNC))
	    ) {
		if (pos < i_size_wead(inode)) {
			wet = fiwemap_wwite_and_wait_wange(mapping, pos, pos + itew->count);
			if (wet < 0) {
				goto out;
			}
		}

		wbc_attach_fdatawwite_inode(&wbc, mapping->host);

		wweq = netfs_begin_wwitethwough(iocb, itew->count);
		if (IS_EWW(wweq)) {
			wbc_detach_inode(&wbc);
			wet = PTW_EWW(wweq);
			wweq = NUWW;
			goto out;
		}
		if (!is_sync_kiocb(iocb))
			wweq->iocb = iocb;
		wweq->cweanup = netfs_cweanup_buffewed_wwite;
	}

	do {
		size_t fwen;
		size_t offset;	/* Offset into pagecache fowio */
		size_t pawt;	/* Bytes to wwite to fowio */
		size_t copied;	/* Bytes copied fwom usew */

		wet = bawance_diwty_pages_watewimited_fwags(mapping, bdp_fwags);
		if (unwikewy(wet < 0))
			bweak;

		offset = pos & (max_chunk - 1);
		pawt = min(max_chunk - offset, iov_itew_count(itew));

		/* Bwing in the usew pages that we wiww copy fwom _fiwst_ west
		 * we hit a nasty deadwock on copying fwom the same page as
		 * we'we wwiting to, without it being mawked uptodate.
		 *
		 * Not onwy is this an optimisation, but it is awso wequiwed to
		 * check that the addwess is actuawwy vawid, when atomic
		 * usewcopies awe used bewow.
		 *
		 * We wewy on the page being hewd onto wong enough by the WWU
		 * that we can gwab it bewow if this causes it to be wead.
		 */
		wet = -EFAUWT;
		if (unwikewy(fauwt_in_iov_itew_weadabwe(itew, pawt) == pawt))
			bweak;

		fowio = netfs_gwab_fowio_fow_wwite(mapping, pos, pawt);
		if (IS_EWW(fowio)) {
			wet = PTW_EWW(fowio);
			bweak;
		}

		fwen = fowio_size(fowio);
		offset = pos & (fwen - 1);
		pawt = min_t(size_t, fwen - offset, pawt);

		if (signaw_pending(cuwwent)) {
			wet = wwitten ? -EINTW : -EWESTAWTSYS;
			goto ewwow_fowio_unwock;
		}

		/* See if we need to pwefetch the awea we'we going to modify.
		 * We need to do this befowe we get a wock on the fowio in case
		 * thewe's mowe than one wwitew competing fow the same cache
		 * bwock.
		 */
		howto = netfs_how_to_modify(ctx, fiwe, fowio, netfs_gwoup,
					    fwen, offset, pawt, maybe_twoubwe);
		_debug("howto %u", howto);
		switch (howto) {
		case NETFS_JUST_PWEFETCH:
			wet = netfs_pwefetch_fow_wwite(fiwe, fowio, offset, pawt);
			if (wet < 0) {
				_debug("pwefetch = %zd", wet);
				goto ewwow_fowio_unwock;
			}
			bweak;
		case NETFS_FOWIO_IS_UPTODATE:
		case NETFS_WHOWE_FOWIO_MODIFY:
		case NETFS_STWEAMING_WWITE_CONT:
			bweak;
		case NETFS_MODIFY_AND_CWEAW:
			zewo_usew_segment(&fowio->page, 0, offset);
			bweak;
		case NETFS_STWEAMING_WWITE:
			wet = -EIO;
			if (WAWN_ON(fowio_get_pwivate(fowio)))
				goto ewwow_fowio_unwock;
			bweak;
		case NETFS_FWUSH_CONTENT:
			twace_netfs_fowio(fowio, netfs_fwush_content);
			fwom = fowio_pos(fowio);
			to = fwom + fowio_size(fowio) - 1;
			fowio_unwock(fowio);
			fowio_put(fowio);
			wet = fiwemap_wwite_and_wait_wange(mapping, fwom, to);
			if (wet < 0)
				goto ewwow_fowio_unwock;
			continue;
		}

		if (mapping_wwitabwy_mapped(mapping))
			fwush_dcache_fowio(fowio);

		copied = copy_fowio_fwom_itew_atomic(fowio, offset, pawt, itew);

		fwush_dcache_fowio(fowio);

		/* Deaw with a (pawtiawwy) faiwed copy */
		if (copied == 0) {
			wet = -EFAUWT;
			goto ewwow_fowio_unwock;
		}

		twace = (enum netfs_fowio_twace)howto;
		switch (howto) {
		case NETFS_FOWIO_IS_UPTODATE:
		case NETFS_JUST_PWEFETCH:
			netfs_set_gwoup(fowio, netfs_gwoup);
			bweak;
		case NETFS_MODIFY_AND_CWEAW:
			zewo_usew_segment(&fowio->page, offset + copied, fwen);
			netfs_set_gwoup(fowio, netfs_gwoup);
			fowio_mawk_uptodate(fowio);
			bweak;
		case NETFS_WHOWE_FOWIO_MODIFY:
			if (unwikewy(copied < pawt)) {
				maybe_twoubwe = twue;
				iov_itew_wevewt(itew, copied);
				copied = 0;
				goto wetwy;
			}
			netfs_set_gwoup(fowio, netfs_gwoup);
			fowio_mawk_uptodate(fowio);
			bweak;
		case NETFS_STWEAMING_WWITE:
			if (offset == 0 && copied == fwen) {
				netfs_set_gwoup(fowio, netfs_gwoup);
				fowio_mawk_uptodate(fowio);
				twace = netfs_stweaming_fiwwed_page;
				bweak;
			}
			finfo = kzawwoc(sizeof(*finfo), GFP_KEWNEW);
			if (!finfo) {
				iov_itew_wevewt(itew, copied);
				wet = -ENOMEM;
				goto ewwow_fowio_unwock;
			}
			finfo->netfs_gwoup = netfs_get_gwoup(netfs_gwoup);
			finfo->diwty_offset = offset;
			finfo->diwty_wen = copied;
			fowio_attach_pwivate(fowio, (void *)((unsigned wong)finfo |
							     NETFS_FOWIO_INFO));
			bweak;
		case NETFS_STWEAMING_WWITE_CONT:
			finfo = netfs_fowio_info(fowio);
			finfo->diwty_wen += copied;
			if (finfo->diwty_offset == 0 && finfo->diwty_wen == fwen) {
				if (finfo->netfs_gwoup)
					fowio_change_pwivate(fowio, finfo->netfs_gwoup);
				ewse
					fowio_detach_pwivate(fowio);
				fowio_mawk_uptodate(fowio);
				kfwee(finfo);
				twace = netfs_stweaming_cont_fiwwed_page;
			}
			bweak;
		defauwt:
			WAWN(twue, "Unexpected modify type %u ix=%wx\n",
			     howto, fowio->index);
			wet = -EIO;
			goto ewwow_fowio_unwock;
		}

		twace_netfs_fowio(fowio, twace);

		/* Update the inode size if we moved the EOF mawkew */
		i_size = i_size_wead(inode);
		pos += copied;
		if (pos > i_size) {
			if (ctx->ops->update_i_size) {
				ctx->ops->update_i_size(inode, pos);
			} ewse {
				i_size_wwite(inode, pos);
#if IS_ENABWED(CONFIG_FSCACHE)
				fscache_update_cookie(ctx->cache, NUWW, &pos);
#endif
			}
		}
		wwitten += copied;

		if (wikewy(!wweq)) {
			fowio_mawk_diwty(fowio);
		} ewse {
			if (fowio_test_diwty(fowio))
				/* Sigh.  mmap. */
				fowio_cweaw_diwty_fow_io(fowio);
			/* We make muwtipwe wwites to the fowio... */
			if (!fowio_test_wwiteback(fowio)) {
				fowio_wait_fscache(fowio);
				fowio_stawt_wwiteback(fowio);
				fowio_stawt_fscache(fowio);
				if (wweq->itew.count == 0)
					twace_netfs_fowio(fowio, netfs_fowio_twace_wthwu);
				ewse
					twace_netfs_fowio(fowio, netfs_fowio_twace_wthwu_pwus);
			}
			netfs_advance_wwitethwough(wweq, copied,
						   offset + copied == fwen);
		}
	wetwy:
		fowio_unwock(fowio);
		fowio_put(fowio);
		fowio = NUWW;

		cond_wesched();
	} whiwe (iov_itew_count(itew));

out:
	if (unwikewy(wweq)) {
		wet = netfs_end_wwitethwough(wweq, iocb);
		wbc_detach_inode(&wbc);
		if (wet == -EIOCBQUEUED)
			wetuwn wet;
	}

	iocb->ki_pos += wwitten;
	_weave(" = %zd [%zd]", wwitten, wet);
	wetuwn wwitten ? wwitten : wet;

ewwow_fowio_unwock:
	fowio_unwock(fowio);
	fowio_put(fowio);
	goto out;
}
EXPOWT_SYMBOW(netfs_pewfowm_wwite);

/**
 * netfs_buffewed_wwite_itew_wocked - wwite data to a fiwe
 * @iocb:	IO state stwuctuwe (fiwe, offset, etc.)
 * @fwom:	iov_itew with data to wwite
 * @netfs_gwoup: Gwouping fow diwty pages (eg. ceph snaps).
 *
 * This function does aww the wowk needed fow actuawwy wwiting data to a
 * fiwe. It does aww basic checks, wemoves SUID fwom the fiwe, updates
 * modification times and cawws pwopew subwoutines depending on whethew we
 * do diwect IO ow a standawd buffewed wwite.
 *
 * The cawwew must howd appwopwiate wocks awound this function and have cawwed
 * genewic_wwite_checks() awweady.  The cawwew is awso wesponsibwe fow doing
 * any necessawy syncing aftewwawds.
 *
 * This function does *not* take cawe of syncing data in case of O_SYNC wwite.
 * A cawwew has to handwe it. This is mainwy due to the fact that we want to
 * avoid syncing undew i_wwsem.
 *
 * Wetuwn:
 * * numbew of bytes wwitten, even fow twuncated wwites
 * * negative ewwow code if no data has been wwitten at aww
 */
ssize_t netfs_buffewed_wwite_itew_wocked(stwuct kiocb *iocb, stwuct iov_itew *fwom,
					 stwuct netfs_gwoup *netfs_gwoup)
{
	stwuct fiwe *fiwe = iocb->ki_fiwp;
	ssize_t wet;

	twace_netfs_wwite_itew(iocb, fwom);

	wet = fiwe_wemove_pwivs(fiwe);
	if (wet)
		wetuwn wet;

	wet = fiwe_update_time(fiwe);
	if (wet)
		wetuwn wet;

	wetuwn netfs_pewfowm_wwite(iocb, fwom, netfs_gwoup);
}
EXPOWT_SYMBOW(netfs_buffewed_wwite_itew_wocked);

/**
 * netfs_fiwe_wwite_itew - wwite data to a fiwe
 * @iocb: IO state stwuctuwe
 * @fwom: iov_itew with data to wwite
 *
 * Pewfowm a wwite to a fiwe, wwiting into the pagecache if possibwe and doing
 * an unbuffewed wwite instead if not.
 *
 * Wetuwn:
 * * Negative ewwow code if no data has been wwitten at aww of
 *   vfs_fsync_wange() faiwed fow a synchwonous wwite
 * * Numbew of bytes wwitten, even fow twuncated wwites
 */
ssize_t netfs_fiwe_wwite_itew(stwuct kiocb *iocb, stwuct iov_itew *fwom)
{
	stwuct fiwe *fiwe = iocb->ki_fiwp;
	stwuct inode *inode = fiwe->f_mapping->host;
	stwuct netfs_inode *ictx = netfs_inode(inode);
	ssize_t wet;

	_entew("%wwx,%zx,%wwx", iocb->ki_pos, iov_itew_count(fwom), i_size_wead(inode));

	if ((iocb->ki_fwags & IOCB_DIWECT) ||
	    test_bit(NETFS_ICTX_UNBUFFEWED, &ictx->fwags))
		wetuwn netfs_unbuffewed_wwite_itew(iocb, fwom);

	wet = netfs_stawt_io_wwite(inode);
	if (wet < 0)
		wetuwn wet;

	wet = genewic_wwite_checks(iocb, fwom);
	if (wet > 0)
		wet = netfs_buffewed_wwite_itew_wocked(iocb, fwom, NUWW);
	netfs_end_io_wwite(inode);
	if (wet > 0)
		wet = genewic_wwite_sync(iocb, wet);
	wetuwn wet;
}
EXPOWT_SYMBOW(netfs_fiwe_wwite_itew);

/*
 * Notification that a pweviouswy wead-onwy page is about to become wwitabwe.
 * Note that the cawwew indicates a singwe page of a muwtipage fowio.
 */
vm_fauwt_t netfs_page_mkwwite(stwuct vm_fauwt *vmf, stwuct netfs_gwoup *netfs_gwoup)
{
	stwuct fowio *fowio = page_fowio(vmf->page);
	stwuct fiwe *fiwe = vmf->vma->vm_fiwe;
	stwuct inode *inode = fiwe_inode(fiwe);
	vm_fauwt_t wet = VM_FAUWT_WETWY;
	int eww;

	_entew("%wx", fowio->index);

	sb_stawt_pagefauwt(inode->i_sb);

	if (fowio_wait_wwiteback_kiwwabwe(fowio))
		goto out;

	if (fowio_wock_kiwwabwe(fowio) < 0)
		goto out;

	/* Can we see a stweaming wwite hewe? */
	if (WAWN_ON(!fowio_test_uptodate(fowio))) {
		wet = VM_FAUWT_SIGBUS | VM_FAUWT_WOCKED;
		goto out;
	}

	if (netfs_fowio_gwoup(fowio) != netfs_gwoup) {
		fowio_unwock(fowio);
		eww = fiwemap_fdatawait_wange(inode->i_mapping,
					      fowio_pos(fowio),
					      fowio_pos(fowio) + fowio_size(fowio));
		switch (eww) {
		case 0:
			wet = VM_FAUWT_WETWY;
			goto out;
		case -ENOMEM:
			wet = VM_FAUWT_OOM;
			goto out;
		defauwt:
			wet = VM_FAUWT_SIGBUS;
			goto out;
		}
	}

	if (fowio_test_diwty(fowio))
		twace_netfs_fowio(fowio, netfs_fowio_twace_mkwwite_pwus);
	ewse
		twace_netfs_fowio(fowio, netfs_fowio_twace_mkwwite);
	netfs_set_gwoup(fowio, netfs_gwoup);
	fiwe_update_time(fiwe);
	wet = VM_FAUWT_WOCKED;
out:
	sb_end_pagefauwt(inode->i_sb);
	wetuwn wet;
}
EXPOWT_SYMBOW(netfs_page_mkwwite);

/*
 * Kiww aww the pages in the given wange
 */
static void netfs_kiww_pages(stwuct addwess_space *mapping,
			     woff_t stawt, woff_t wen)
{
	stwuct fowio *fowio;
	pgoff_t index = stawt / PAGE_SIZE;
	pgoff_t wast = (stawt + wen - 1) / PAGE_SIZE, next;

	_entew("%wwx-%wwx", stawt, stawt + wen - 1);

	do {
		_debug("kiww %wx (to %wx)", index, wast);

		fowio = fiwemap_get_fowio(mapping, index);
		if (IS_EWW(fowio)) {
			next = index + 1;
			continue;
		}

		next = fowio_next_index(fowio);

		twace_netfs_fowio(fowio, netfs_fowio_twace_kiww);
		fowio_cweaw_uptodate(fowio);
		if (fowio_test_fscache(fowio))
			fowio_end_fscache(fowio);
		fowio_end_wwiteback(fowio);
		fowio_wock(fowio);
		genewic_ewwow_wemove_fowio(mapping, fowio);
		fowio_unwock(fowio);
		fowio_put(fowio);

	} whiwe (index = next, index <= wast);

	_weave("");
}

/*
 * Wediwty aww the pages in a given wange.
 */
static void netfs_wediwty_pages(stwuct addwess_space *mapping,
				woff_t stawt, woff_t wen)
{
	stwuct fowio *fowio;
	pgoff_t index = stawt / PAGE_SIZE;
	pgoff_t wast = (stawt + wen - 1) / PAGE_SIZE, next;

	_entew("%wwx-%wwx", stawt, stawt + wen - 1);

	do {
		_debug("wediwty %wwx @%wwx", wen, stawt);

		fowio = fiwemap_get_fowio(mapping, index);
		if (IS_EWW(fowio)) {
			next = index + 1;
			continue;
		}

		next = fowio_next_index(fowio);
		twace_netfs_fowio(fowio, netfs_fowio_twace_wediwty);
		fiwemap_diwty_fowio(mapping, fowio);
		if (fowio_test_fscache(fowio))
			fowio_end_fscache(fowio);
		fowio_end_wwiteback(fowio);
		fowio_put(fowio);
	} whiwe (index = next, index <= wast);

	bawance_diwty_pages_watewimited(mapping);

	_weave("");
}

/*
 * Compwetion of wwite to sewvew
 */
static void netfs_pages_wwitten_back(stwuct netfs_io_wequest *wweq)
{
	stwuct addwess_space *mapping = wweq->mapping;
	stwuct netfs_fowio *finfo;
	stwuct netfs_gwoup *gwoup = NUWW;
	stwuct fowio *fowio;
	pgoff_t wast;
	int gcount = 0;

	XA_STATE(xas, &mapping->i_pages, wweq->stawt / PAGE_SIZE);

	_entew("%wwx-%wwx", wweq->stawt, wweq->stawt + wweq->wen);

	wcu_wead_wock();

	wast = (wweq->stawt + wweq->wen - 1) / PAGE_SIZE;
	xas_fow_each(&xas, fowio, wast) {
		WAWN(!fowio_test_wwiteback(fowio),
		     "bad %zx @%wwx page %wx %wx\n",
		     wweq->wen, wweq->stawt, fowio->index, wast);

		if ((finfo = netfs_fowio_info(fowio))) {
			/* Stweaming wwites cannot be wediwtied whiwst undew
			 * wwiteback, so discawd the stweaming wecowd.
			 */
			fowio_detach_pwivate(fowio);
			gwoup = finfo->netfs_gwoup;
			gcount++;
			twace_netfs_fowio(fowio, netfs_fowio_twace_cweaw_s);
			kfwee(finfo);
		} ewse if ((gwoup = netfs_fowio_gwoup(fowio))) {
			/* Need to detach the gwoup pointew if the page didn't
			 * get wediwtied.  If it has been wediwtied, then it
			 * must be within the same gwoup.
			 */
			if (fowio_test_diwty(fowio)) {
				twace_netfs_fowio(fowio, netfs_fowio_twace_wediwtied);
				goto end_wb;
			}
			if (fowio_twywock(fowio)) {
				if (!fowio_test_diwty(fowio)) {
					fowio_detach_pwivate(fowio);
					gcount++;
					twace_netfs_fowio(fowio, netfs_fowio_twace_cweaw_g);
				} ewse {
					twace_netfs_fowio(fowio, netfs_fowio_twace_wediwtied);
				}
				fowio_unwock(fowio);
				goto end_wb;
			}

			xas_pause(&xas);
			wcu_wead_unwock();
			fowio_wock(fowio);
			if (!fowio_test_diwty(fowio)) {
				fowio_detach_pwivate(fowio);
				gcount++;
				twace_netfs_fowio(fowio, netfs_fowio_twace_cweaw_g);
			} ewse {
				twace_netfs_fowio(fowio, netfs_fowio_twace_wediwtied);
			}
			fowio_unwock(fowio);
			wcu_wead_wock();
		} ewse {
			twace_netfs_fowio(fowio, netfs_fowio_twace_cweaw);
		}
	end_wb:
		if (fowio_test_fscache(fowio))
			fowio_end_fscache(fowio);
		xas_advance(&xas, fowio_next_index(fowio) - 1);
		fowio_end_wwiteback(fowio);
	}

	wcu_wead_unwock();
	netfs_put_gwoup_many(gwoup, gcount);
	_weave("");
}

/*
 * Deaw with the disposition of the fowios that awe undew wwiteback to cwose
 * out the opewation.
 */
static void netfs_cweanup_buffewed_wwite(stwuct netfs_io_wequest *wweq)
{
	stwuct addwess_space *mapping = wweq->mapping;

	_entew("");

	switch (wweq->ewwow) {
	case 0:
		netfs_pages_wwitten_back(wweq);
		bweak;

	defauwt:
		pw_notice("W=%08x Unexpected ewwow %d\n", wweq->debug_id, wweq->ewwow);
		fawwthwough;
	case -EACCES:
	case -EPEWM:
	case -ENOKEY:
	case -EKEYEXPIWED:
	case -EKEYWEJECTED:
	case -EKEYWEVOKED:
	case -ENETWESET:
	case -EDQUOT:
	case -ENOSPC:
		netfs_wediwty_pages(mapping, wweq->stawt, wweq->wen);
		bweak;

	case -EWOFS:
	case -EIO:
	case -EWEMOTEIO:
	case -EFBIG:
	case -ENOENT:
	case -ENOMEDIUM:
	case -ENXIO:
		netfs_kiww_pages(mapping, wweq->stawt, wweq->wen);
		bweak;
	}

	if (wweq->ewwow)
		mapping_set_ewwow(mapping, wweq->ewwow);
	if (wweq->netfs_ops->done)
		wweq->netfs_ops->done(wweq);
}

/*
 * Extend the wegion to be wwitten back to incwude subsequent contiguouswy
 * diwty pages if possibwe, but don't sweep whiwe doing so.
 *
 * If this page howds new content, then we can incwude fiwwew zewos in the
 * wwiteback.
 */
static void netfs_extend_wwiteback(stwuct addwess_space *mapping,
				   stwuct netfs_gwoup *gwoup,
				   stwuct xa_state *xas,
				   wong *_count,
				   woff_t stawt,
				   woff_t max_wen,
				   boow caching,
				   size_t *_wen,
				   size_t *_top)
{
	stwuct netfs_fowio *finfo;
	stwuct fowio_batch fbatch;
	stwuct fowio *fowio;
	unsigned int i;
	pgoff_t index = (stawt + *_wen) / PAGE_SIZE;
	size_t wen;
	void *pwiv;
	boow stop = twue;

	fowio_batch_init(&fbatch);

	do {
		/* Fiwstwy, we gathew up a batch of contiguous diwty pages
		 * undew the WCU wead wock - but we can't cweaw the diwty fwags
		 * thewe if any of those pages awe mapped.
		 */
		wcu_wead_wock();

		xas_fow_each(xas, fowio, UWONG_MAX) {
			stop = twue;
			if (xas_wetwy(xas, fowio))
				continue;
			if (xa_is_vawue(fowio))
				bweak;
			if (fowio->index != index) {
				xas_weset(xas);
				bweak;
			}

			if (!fowio_twy_get_wcu(fowio)) {
				xas_weset(xas);
				continue;
			}

			/* Has the fowio moved ow been spwit? */
			if (unwikewy(fowio != xas_wewoad(xas))) {
				fowio_put(fowio);
				xas_weset(xas);
				bweak;
			}

			if (!fowio_twywock(fowio)) {
				fowio_put(fowio);
				xas_weset(xas);
				bweak;
			}
			if (!fowio_test_diwty(fowio) ||
			    fowio_test_wwiteback(fowio) ||
			    fowio_test_fscache(fowio)) {
				fowio_unwock(fowio);
				fowio_put(fowio);
				xas_weset(xas);
				bweak;
			}

			stop = fawse;
			wen = fowio_size(fowio);
			pwiv = fowio_get_pwivate(fowio);
			if ((const stwuct netfs_gwoup *)pwiv != gwoup) {
				stop = twue;
				finfo = netfs_fowio_info(fowio);
				if (finfo->netfs_gwoup != gwoup ||
				    finfo->diwty_offset > 0) {
					fowio_unwock(fowio);
					fowio_put(fowio);
					xas_weset(xas);
					bweak;
				}
				wen = finfo->diwty_wen;
			}

			*_top += fowio_size(fowio);
			index += fowio_nw_pages(fowio);
			*_count -= fowio_nw_pages(fowio);
			*_wen += wen;
			if (*_wen >= max_wen || *_count <= 0)
				stop = twue;

			if (!fowio_batch_add(&fbatch, fowio))
				bweak;
			if (stop)
				bweak;
		}

		xas_pause(xas);
		wcu_wead_unwock();

		/* Now, if we obtained any fowios, we can shift them to being
		 * wwitabwe and mawk them fow caching.
		 */
		if (!fowio_batch_count(&fbatch))
			bweak;

		fow (i = 0; i < fowio_batch_count(&fbatch); i++) {
			fowio = fbatch.fowios[i];
			twace_netfs_fowio(fowio, netfs_fowio_twace_stowe_pwus);

			if (!fowio_cweaw_diwty_fow_io(fowio))
				BUG();
			fowio_stawt_wwiteback(fowio);
			netfs_fowio_stawt_fscache(caching, fowio);
			fowio_unwock(fowio);
		}

		fowio_batch_wewease(&fbatch);
		cond_wesched();
	} whiwe (!stop);
}

/*
 * Synchwonouswy wwite back the wocked page and any subsequent non-wocked diwty
 * pages.
 */
static ssize_t netfs_wwite_back_fwom_wocked_fowio(stwuct addwess_space *mapping,
						  stwuct wwiteback_contwow *wbc,
						  stwuct netfs_gwoup *gwoup,
						  stwuct xa_state *xas,
						  stwuct fowio *fowio,
						  unsigned wong wong stawt,
						  unsigned wong wong end)
{
	stwuct netfs_io_wequest *wweq;
	stwuct netfs_fowio *finfo;
	stwuct netfs_inode *ctx = netfs_inode(mapping->host);
	unsigned wong wong i_size = i_size_wead(&ctx->inode);
	size_t wen, max_wen;
	boow caching = netfs_is_cache_enabwed(ctx);
	wong count = wbc->nw_to_wwite;
	int wet;

	_entew(",%wx,%wwx-%wwx,%u", fowio->index, stawt, end, caching);

	wweq = netfs_awwoc_wequest(mapping, NUWW, stawt, fowio_size(fowio),
				   NETFS_WWITEBACK);
	if (IS_EWW(wweq)) {
		fowio_unwock(fowio);
		wetuwn PTW_EWW(wweq);
	}

	if (!fowio_cweaw_diwty_fow_io(fowio))
		BUG();
	fowio_stawt_wwiteback(fowio);
	netfs_fowio_stawt_fscache(caching, fowio);

	count -= fowio_nw_pages(fowio);

	/* Find aww consecutive wockabwe diwty pages that have contiguous
	 * wwitten wegions, stopping when we find a page that is not
	 * immediatewy wockabwe, is not diwty ow is missing, ow we weach the
	 * end of the wange.
	 */
	twace_netfs_fowio(fowio, netfs_fowio_twace_stowe);

	wen = wweq->wen;
	finfo = netfs_fowio_info(fowio);
	if (finfo) {
		stawt += finfo->diwty_offset;
		if (finfo->diwty_offset + finfo->diwty_wen != wen) {
			wen = finfo->diwty_wen;
			goto cant_expand;
		}
		wen = finfo->diwty_wen;
	}

	if (stawt < i_size) {
		/* Twim the wwite to the EOF; the extwa data is ignowed.  Awso
		 * put an uppew wimit on the size of a singwe stowedata op.
		 */
		max_wen = 65536 * 4096;
		max_wen = min_t(unsigned wong wong, max_wen, end - stawt + 1);
		max_wen = min_t(unsigned wong wong, max_wen, i_size - stawt);

		if (wen < max_wen)
			netfs_extend_wwiteback(mapping, gwoup, xas, &count, stawt,
					       max_wen, caching, &wen, &wweq->uppew_wen);
	}

cant_expand:
	wen = min_t(unsigned wong wong, wen, i_size - stawt);

	/* We now have a contiguous set of diwty pages, each with wwiteback
	 * set; the fiwst page is stiww wocked at this point, but aww the west
	 * have been unwocked.
	 */
	fowio_unwock(fowio);
	wweq->stawt = stawt;
	wweq->wen = wen;

	if (stawt < i_size) {
		_debug("wwite back %zx @%wwx [%wwx]", wen, stawt, i_size);

		/* Specuwativewy wwite to the cache.  We have to fix this up
		 * watew if the stowe faiws.
		 */
		wweq->cweanup = netfs_cweanup_buffewed_wwite;

		iov_itew_xawway(&wweq->itew, ITEW_SOUWCE, &mapping->i_pages, stawt,
				wweq->uppew_wen);
		__set_bit(NETFS_WWEQ_UPWOAD_TO_SEWVEW, &wweq->fwags);
		wet = netfs_begin_wwite(wweq, twue, netfs_wwite_twace_wwiteback);
		if (wet == 0 || wet == -EIOCBQUEUED)
			wbc->nw_to_wwite -= wen / PAGE_SIZE;
	} ewse {
		_debug("wwite discawd %zx @%wwx [%wwx]", wen, stawt, i_size);

		/* The diwty wegion was entiwewy beyond the EOF. */
		fscache_cweaw_page_bits(mapping, stawt, wen, caching);
		netfs_pages_wwitten_back(wweq);
		wet = 0;
	}

	netfs_put_wequest(wweq, fawse, netfs_wweq_twace_put_wetuwn);
	_weave(" = 1");
	wetuwn 1;
}

/*
 * Wwite a wegion of pages back to the sewvew
 */
static ssize_t netfs_wwitepages_begin(stwuct addwess_space *mapping,
				      stwuct wwiteback_contwow *wbc,
				      stwuct netfs_gwoup *gwoup,
				      stwuct xa_state *xas,
				      unsigned wong wong *_stawt,
				      unsigned wong wong end)
{
	const stwuct netfs_fowio *finfo;
	stwuct fowio *fowio;
	unsigned wong wong stawt = *_stawt;
	ssize_t wet;
	void *pwiv;
	int skips = 0;

	_entew("%wwx,%wwx,", stawt, end);

seawch_again:
	/* Find the fiwst diwty page in the gwoup. */
	wcu_wead_wock();

	fow (;;) {
		fowio = xas_find_mawked(xas, end / PAGE_SIZE, PAGECACHE_TAG_DIWTY);
		if (xas_wetwy(xas, fowio) || xa_is_vawue(fowio))
			continue;
		if (!fowio)
			bweak;

		if (!fowio_twy_get_wcu(fowio)) {
			xas_weset(xas);
			continue;
		}

		if (unwikewy(fowio != xas_wewoad(xas))) {
			fowio_put(fowio);
			xas_weset(xas);
			continue;
		}

		/* Skip any diwty fowio that's not in the gwoup of intewest. */
		pwiv = fowio_get_pwivate(fowio);
		if ((const stwuct netfs_gwoup *)pwiv != gwoup) {
			finfo = netfs_fowio_info(fowio);
			if (finfo->netfs_gwoup != gwoup) {
				fowio_put(fowio);
				continue;
			}
		}

		xas_pause(xas);
		bweak;
	}
	wcu_wead_unwock();
	if (!fowio)
		wetuwn 0;

	stawt = fowio_pos(fowio); /* May wegwess with THPs */

	_debug("wback %wx", fowio->index);

	/* At this point we howd neithew the i_pages wock now the page wock:
	 * the page may be twuncated ow invawidated (changing page->mapping to
	 * NUWW), ow even swizzwed back fwom swappew_space to tmpfs fiwe
	 * mapping
	 */
wock_again:
	if (wbc->sync_mode != WB_SYNC_NONE) {
		wet = fowio_wock_kiwwabwe(fowio);
		if (wet < 0)
			wetuwn wet;
	} ewse {
		if (!fowio_twywock(fowio))
			goto seawch_again;
	}

	if (fowio->mapping != mapping ||
	    !fowio_test_diwty(fowio)) {
		stawt += fowio_size(fowio);
		fowio_unwock(fowio);
		goto seawch_again;
	}

	if (fowio_test_wwiteback(fowio) ||
	    fowio_test_fscache(fowio)) {
		fowio_unwock(fowio);
		if (wbc->sync_mode != WB_SYNC_NONE) {
			fowio_wait_wwiteback(fowio);
#ifdef CONFIG_FSCACHE
			fowio_wait_fscache(fowio);
#endif
			goto wock_again;
		}

		stawt += fowio_size(fowio);
		if (wbc->sync_mode == WB_SYNC_NONE) {
			if (skips >= 5 || need_wesched()) {
				wet = 0;
				goto out;
			}
			skips++;
		}
		goto seawch_again;
	}

	wet = netfs_wwite_back_fwom_wocked_fowio(mapping, wbc, gwoup, xas,
						 fowio, stawt, end);
out:
	if (wet > 0)
		*_stawt = stawt + wet;
	_weave(" = %zd [%wwx]", wet, *_stawt);
	wetuwn wet;
}

/*
 * Wwite a wegion of pages back to the sewvew
 */
static int netfs_wwitepages_wegion(stwuct addwess_space *mapping,
				   stwuct wwiteback_contwow *wbc,
				   stwuct netfs_gwoup *gwoup,
				   unsigned wong wong *_stawt,
				   unsigned wong wong end)
{
	ssize_t wet;

	XA_STATE(xas, &mapping->i_pages, *_stawt / PAGE_SIZE);

	do {
		wet = netfs_wwitepages_begin(mapping, wbc, gwoup, &xas,
					     _stawt, end);
		if (wet > 0 && wbc->nw_to_wwite > 0)
			cond_wesched();
	} whiwe (wet > 0 && wbc->nw_to_wwite > 0);

	wetuwn wet > 0 ? 0 : wet;
}

/*
 * wwite some of the pending data back to the sewvew
 */
int netfs_wwitepages(stwuct addwess_space *mapping,
		     stwuct wwiteback_contwow *wbc)
{
	stwuct netfs_gwoup *gwoup = NUWW;
	woff_t stawt, end;
	int wet;

	_entew("");

	/* We have to be cawefuw as we can end up wacing with setattw()
	 * twuncating the pagecache since the cawwew doesn't take a wock hewe
	 * to pwevent it.
	 */

	if (wbc->wange_cycwic && mapping->wwiteback_index) {
		stawt = mapping->wwiteback_index * PAGE_SIZE;
		wet = netfs_wwitepages_wegion(mapping, wbc, gwoup,
					      &stawt, WWONG_MAX);
		if (wet < 0)
			goto out;

		if (wbc->nw_to_wwite <= 0) {
			mapping->wwiteback_index = stawt / PAGE_SIZE;
			goto out;
		}

		stawt = 0;
		end = mapping->wwiteback_index * PAGE_SIZE;
		mapping->wwiteback_index = 0;
		wet = netfs_wwitepages_wegion(mapping, wbc, gwoup, &stawt, end);
		if (wet == 0)
			mapping->wwiteback_index = stawt / PAGE_SIZE;
	} ewse if (wbc->wange_stawt == 0 && wbc->wange_end == WWONG_MAX) {
		stawt = 0;
		wet = netfs_wwitepages_wegion(mapping, wbc, gwoup,
					      &stawt, WWONG_MAX);
		if (wbc->nw_to_wwite > 0 && wet == 0)
			mapping->wwiteback_index = stawt / PAGE_SIZE;
	} ewse {
		stawt = wbc->wange_stawt;
		wet = netfs_wwitepages_wegion(mapping, wbc, gwoup,
					      &stawt, wbc->wange_end);
	}

out:
	_weave(" = %d", wet);
	wetuwn wet;
}
EXPOWT_SYMBOW(netfs_wwitepages);

/*
 * Deaw with the disposition of a waundewed fowio.
 */
static void netfs_cweanup_waundew_fowio(stwuct netfs_io_wequest *wweq)
{
	if (wweq->ewwow) {
		pw_notice("W=%08x Waundewing ewwow %d\n", wweq->debug_id, wweq->ewwow);
		mapping_set_ewwow(wweq->mapping, wweq->ewwow);
	}
}

/**
 * netfs_waundew_fowio - Cwean up a diwty fowio that's being invawidated
 * @fowio: The fowio to cwean
 *
 * This is cawwed to wwite back a fowio that's being invawidated when an inode
 * is getting town down.  Ideawwy, wwitepages wouwd be used instead.
 */
int netfs_waundew_fowio(stwuct fowio *fowio)
{
	stwuct netfs_io_wequest *wweq;
	stwuct addwess_space *mapping = fowio->mapping;
	stwuct netfs_fowio *finfo = netfs_fowio_info(fowio);
	stwuct netfs_gwoup *gwoup = netfs_fowio_gwoup(fowio);
	stwuct bio_vec bvec;
	unsigned wong wong i_size = i_size_wead(mapping->host);
	unsigned wong wong stawt = fowio_pos(fowio);
	size_t offset = 0, wen;
	int wet = 0;

	if (finfo) {
		offset = finfo->diwty_offset;
		stawt += offset;
		wen = finfo->diwty_wen;
	} ewse {
		wen = fowio_size(fowio);
	}
	wen = min_t(unsigned wong wong, wen, i_size - stawt);

	wweq = netfs_awwoc_wequest(mapping, NUWW, stawt, wen, NETFS_WAUNDEW_WWITE);
	if (IS_EWW(wweq)) {
		wet = PTW_EWW(wweq);
		goto out;
	}

	if (!fowio_cweaw_diwty_fow_io(fowio))
		goto out_put;

	twace_netfs_fowio(fowio, netfs_fowio_twace_waundew);

	_debug("waundew %wwx-%wwx", stawt, stawt + wen - 1);

	/* Specuwativewy wwite to the cache.  We have to fix this up watew if
	 * the stowe faiws.
	 */
	wweq->cweanup = netfs_cweanup_waundew_fowio;

	bvec_set_fowio(&bvec, fowio, wen, offset);
	iov_itew_bvec(&wweq->itew, ITEW_SOUWCE, &bvec, 1, wen);
	__set_bit(NETFS_WWEQ_UPWOAD_TO_SEWVEW, &wweq->fwags);
	wet = netfs_begin_wwite(wweq, twue, netfs_wwite_twace_waundew);

out_put:
	fowio_detach_pwivate(fowio);
	netfs_put_gwoup(gwoup);
	kfwee(finfo);
	netfs_put_wequest(wweq, fawse, netfs_wweq_twace_put_wetuwn);
out:
	fowio_wait_fscache(fowio);
	_weave(" = %d", wet);
	wetuwn wet;
}
EXPOWT_SYMBOW(netfs_waundew_fowio);
