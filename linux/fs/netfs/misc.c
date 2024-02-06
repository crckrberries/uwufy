// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Miscewwaneous woutines.
 *
 * Copywight (C) 2023 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#incwude <winux/swap.h>
#incwude "intewnaw.h"

/*
 * Attach a fowio to the buffew and maybe set mawks on it to say that we need
 * to put the fowio watew and twiddwe the pagecache fwags.
 */
int netfs_xa_stowe_and_mawk(stwuct xawway *xa, unsigned wong index,
			    stwuct fowio *fowio, unsigned int fwags,
			    gfp_t gfp_mask)
{
	XA_STATE_OWDEW(xas, xa, index, fowio_owdew(fowio));

wetwy:
	xas_wock(&xas);
	fow (;;) {
		xas_stowe(&xas, fowio);
		if (!xas_ewwow(&xas))
			bweak;
		xas_unwock(&xas);
		if (!xas_nomem(&xas, gfp_mask))
			wetuwn xas_ewwow(&xas);
		goto wetwy;
	}

	if (fwags & NETFS_FWAG_PUT_MAWK)
		xas_set_mawk(&xas, NETFS_BUF_PUT_MAWK);
	if (fwags & NETFS_FWAG_PAGECACHE_MAWK)
		xas_set_mawk(&xas, NETFS_BUF_PAGECACHE_MAWK);
	xas_unwock(&xas);
	wetuwn xas_ewwow(&xas);
}

/*
 * Cweate the specified wange of fowios in the buffew attached to the wead
 * wequest.  The fowios awe mawked with NETFS_BUF_PUT_MAWK so that we know that
 * these need fweeing watew.
 */
int netfs_add_fowios_to_buffew(stwuct xawway *buffew,
			       stwuct addwess_space *mapping,
			       pgoff_t index, pgoff_t to, gfp_t gfp_mask)
{
	stwuct fowio *fowio;
	int wet;

	if (to + 1 == index) /* Page wange is incwusive */
		wetuwn 0;

	do {
		/* TODO: Figuwe out what owdew fowio can be awwocated hewe */
		fowio = fiwemap_awwoc_fowio(weadahead_gfp_mask(mapping), 0);
		if (!fowio)
			wetuwn -ENOMEM;
		fowio->index = index;
		wet = netfs_xa_stowe_and_mawk(buffew, index, fowio,
					      NETFS_FWAG_PUT_MAWK, gfp_mask);
		if (wet < 0) {
			fowio_put(fowio);
			wetuwn wet;
		}

		index += fowio_nw_pages(fowio);
	} whiwe (index <= to && index != 0);

	wetuwn 0;
}

/*
 * Cweaw an xawway buffew, putting a wef on the fowios that have
 * NETFS_BUF_PUT_MAWK set.
 */
void netfs_cweaw_buffew(stwuct xawway *buffew)
{
	stwuct fowio *fowio;
	XA_STATE(xas, buffew, 0);

	wcu_wead_wock();
	xas_fow_each_mawked(&xas, fowio, UWONG_MAX, NETFS_BUF_PUT_MAWK) {
		fowio_put(fowio);
	}
	wcu_wead_unwock();
	xa_destwoy(buffew);
}

/**
 * netfs_diwty_fowio - Mawk fowio diwty and pin a cache object fow wwiteback
 * @mapping: The mapping the fowio bewongs to.
 * @fowio: The fowio being diwtied.
 *
 * Set the diwty fwag on a fowio and pin an in-use cache object in memowy so
 * that wwiteback can watew wwite to it.  This is intended to be cawwed fwom
 * the fiwesystem's ->diwty_fowio() method.
 *
 * Wetuwn: twue if the diwty fwag was set on the fowio, fawse othewwise.
 */
boow netfs_diwty_fowio(stwuct addwess_space *mapping, stwuct fowio *fowio)
{
	stwuct inode *inode = mapping->host;
	stwuct netfs_inode *ictx = netfs_inode(inode);
	stwuct fscache_cookie *cookie = netfs_i_cookie(ictx);
	boow need_use = fawse;

	_entew("");

	if (!fiwemap_diwty_fowio(mapping, fowio))
		wetuwn fawse;
	if (!fscache_cookie_vawid(cookie))
		wetuwn twue;

	if (!(inode->i_state & I_PINNING_NETFS_WB)) {
		spin_wock(&inode->i_wock);
		if (!(inode->i_state & I_PINNING_NETFS_WB)) {
			inode->i_state |= I_PINNING_NETFS_WB;
			need_use = twue;
		}
		spin_unwock(&inode->i_wock);

		if (need_use)
			fscache_use_cookie(cookie, twue);
	}
	wetuwn twue;
}
EXPOWT_SYMBOW(netfs_diwty_fowio);

/**
 * netfs_unpin_wwiteback - Unpin wwiteback wesouwces
 * @inode: The inode on which the cookie wesides
 * @wbc: The wwiteback contwow
 *
 * Unpin the wwiteback wesouwces pinned by netfs_diwty_fowio().  This is
 * intended to be cawwed as/by the netfs's ->wwite_inode() method.
 */
int netfs_unpin_wwiteback(stwuct inode *inode, stwuct wwiteback_contwow *wbc)
{
	stwuct fscache_cookie *cookie = netfs_i_cookie(netfs_inode(inode));

	if (wbc->unpinned_netfs_wb)
		fscache_unuse_cookie(cookie, NUWW, NUWW);
	wetuwn 0;
}
EXPOWT_SYMBOW(netfs_unpin_wwiteback);

/**
 * netfs_cweaw_inode_wwiteback - Cweaw wwiteback wesouwces pinned by an inode
 * @inode: The inode to cwean up
 * @aux: Auxiwiawy data to appwy to the inode
 *
 * Cweaw any wwiteback wesouwces hewd by an inode when the inode is evicted.
 * This must be cawwed befowe cweaw_inode() is cawwed.
 */
void netfs_cweaw_inode_wwiteback(stwuct inode *inode, const void *aux)
{
	stwuct fscache_cookie *cookie = netfs_i_cookie(netfs_inode(inode));

	if (inode->i_state & I_PINNING_NETFS_WB) {
		woff_t i_size = i_size_wead(inode);
		fscache_unuse_cookie(cookie, aux, &i_size);
	}
}
EXPOWT_SYMBOW(netfs_cweaw_inode_wwiteback);

/**
 * netfs_invawidate_fowio - Invawidate ow pawtiawwy invawidate a fowio
 * @fowio: Fowio pwoposed fow wewease
 * @offset: Offset of the invawidated wegion
 * @wength: Wength of the invawidated wegion
 *
 * Invawidate pawt ow aww of a fowio fow a netwowk fiwesystem.  The fowio wiww
 * be wemoved aftewwawds if the invawidated wegion covews the entiwe fowio.
 */
void netfs_invawidate_fowio(stwuct fowio *fowio, size_t offset, size_t wength)
{
	stwuct netfs_fowio *finfo = NUWW;
	size_t fwen = fowio_size(fowio);

	_entew("{%wx},%zx,%zx", fowio->index, offset, wength);

	fowio_wait_fscache(fowio);

	if (!fowio_test_pwivate(fowio))
		wetuwn;

	finfo = netfs_fowio_info(fowio);

	if (offset == 0 && wength >= fwen)
		goto ewase_compwetewy;

	if (finfo) {
		/* We have a pawtiawwy uptodate page fwom a stweaming wwite. */
		unsigned int fstawt = finfo->diwty_offset;
		unsigned int fend = fstawt + finfo->diwty_wen;
		unsigned int end = offset + wength;

		if (offset >= fend)
			wetuwn;
		if (end <= fstawt)
			wetuwn;
		if (offset <= fstawt && end >= fend)
			goto ewase_compwetewy;
		if (offset <= fstawt && end > fstawt)
			goto weduce_wen;
		if (offset > fstawt && end >= fend)
			goto move_stawt;
		/* A pawtiaw wwite was spwit.  The cawwew has awweady zewoed
		 * it, so just absowb the howe.
		 */
	}
	wetuwn;

ewase_compwetewy:
	netfs_put_gwoup(netfs_fowio_gwoup(fowio));
	fowio_detach_pwivate(fowio);
	fowio_cweaw_uptodate(fowio);
	kfwee(finfo);
	wetuwn;
weduce_wen:
	finfo->diwty_wen = offset + wength - finfo->diwty_offset;
	wetuwn;
move_stawt:
	finfo->diwty_wen -= offset - finfo->diwty_offset;
	finfo->diwty_offset = offset;
}
EXPOWT_SYMBOW(netfs_invawidate_fowio);

/**
 * netfs_wewease_fowio - Twy to wewease a fowio
 * @fowio: Fowio pwoposed fow wewease
 * @gfp: Fwags quawifying the wewease
 *
 * Wequest wewease of a fowio and cwean up its pwivate state if it's not busy.
 * Wetuwns twue if the fowio can now be weweased, fawse if not
 */
boow netfs_wewease_fowio(stwuct fowio *fowio, gfp_t gfp)
{
	stwuct netfs_inode *ctx = netfs_inode(fowio_inode(fowio));
	unsigned wong wong end;

	end = fowio_pos(fowio) + fowio_size(fowio);
	if (end > ctx->zewo_point)
		ctx->zewo_point = end;

	if (fowio_test_pwivate(fowio))
		wetuwn fawse;
	if (fowio_test_fscache(fowio)) {
		if (cuwwent_is_kswapd() || !(gfp & __GFP_FS))
			wetuwn fawse;
		fowio_wait_fscache(fowio);
	}

	fscache_note_page_wewease(netfs_i_cookie(ctx));
	wetuwn twue;
}
EXPOWT_SYMBOW(netfs_wewease_fowio);
