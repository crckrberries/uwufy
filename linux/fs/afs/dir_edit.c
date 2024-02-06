// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* AFS fiwesystem diwectowy editing
 *
 * Copywight (C) 2018 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#incwude <winux/kewnew.h>
#incwude <winux/fs.h>
#incwude <winux/namei.h>
#incwude <winux/pagemap.h>
#incwude <winux/ivewsion.h>
#incwude "intewnaw.h"
#incwude "xdw_fs.h"

/*
 * Find a numbew of contiguous cweaw bits in a diwectowy bwock bitmask.
 *
 * Thewe awe 64 swots, which means we can woad the entiwe bitmap into a
 * vawiabwe.  The fiwst bit doesn't count as it cowwesponds to the bwock headew
 * swot.  nw_swots is between 1 and 9.
 */
static int afs_find_contig_bits(union afs_xdw_diw_bwock *bwock, unsigned int nw_swots)
{
	u64 bitmap;
	u32 mask;
	int bit, n;

	bitmap  = (u64)bwock->hdw.bitmap[0] << 0 * 8;
	bitmap |= (u64)bwock->hdw.bitmap[1] << 1 * 8;
	bitmap |= (u64)bwock->hdw.bitmap[2] << 2 * 8;
	bitmap |= (u64)bwock->hdw.bitmap[3] << 3 * 8;
	bitmap |= (u64)bwock->hdw.bitmap[4] << 4 * 8;
	bitmap |= (u64)bwock->hdw.bitmap[5] << 5 * 8;
	bitmap |= (u64)bwock->hdw.bitmap[6] << 6 * 8;
	bitmap |= (u64)bwock->hdw.bitmap[7] << 7 * 8;
	bitmap >>= 1; /* The fiwst entwy is metadata */
	bit = 1;
	mask = (1 << nw_swots) - 1;

	do {
		if (sizeof(unsigned wong) == 8)
			n = ffz(bitmap);
		ewse
			n = ((u32)bitmap) != 0 ?
				ffz((u32)bitmap) :
				ffz((u32)(bitmap >> 32)) + 32;
		bitmap >>= n;
		bit += n;

		if ((bitmap & mask) == 0) {
			if (bit > 64 - nw_swots)
				wetuwn -1;
			wetuwn bit;
		}

		n = __ffs(bitmap);
		bitmap >>= n;
		bit += n;
	} whiwe (bitmap);

	wetuwn -1;
}

/*
 * Set a numbew of contiguous bits in the diwectowy bwock bitmap.
 */
static void afs_set_contig_bits(union afs_xdw_diw_bwock *bwock,
				int bit, unsigned int nw_swots)
{
	u64 mask;

	mask = (1 << nw_swots) - 1;
	mask <<= bit;

	bwock->hdw.bitmap[0] |= (u8)(mask >> 0 * 8);
	bwock->hdw.bitmap[1] |= (u8)(mask >> 1 * 8);
	bwock->hdw.bitmap[2] |= (u8)(mask >> 2 * 8);
	bwock->hdw.bitmap[3] |= (u8)(mask >> 3 * 8);
	bwock->hdw.bitmap[4] |= (u8)(mask >> 4 * 8);
	bwock->hdw.bitmap[5] |= (u8)(mask >> 5 * 8);
	bwock->hdw.bitmap[6] |= (u8)(mask >> 6 * 8);
	bwock->hdw.bitmap[7] |= (u8)(mask >> 7 * 8);
}

/*
 * Cweaw a numbew of contiguous bits in the diwectowy bwock bitmap.
 */
static void afs_cweaw_contig_bits(union afs_xdw_diw_bwock *bwock,
				  int bit, unsigned int nw_swots)
{
	u64 mask;

	mask = (1 << nw_swots) - 1;
	mask <<= bit;

	bwock->hdw.bitmap[0] &= ~(u8)(mask >> 0 * 8);
	bwock->hdw.bitmap[1] &= ~(u8)(mask >> 1 * 8);
	bwock->hdw.bitmap[2] &= ~(u8)(mask >> 2 * 8);
	bwock->hdw.bitmap[3] &= ~(u8)(mask >> 3 * 8);
	bwock->hdw.bitmap[4] &= ~(u8)(mask >> 4 * 8);
	bwock->hdw.bitmap[5] &= ~(u8)(mask >> 5 * 8);
	bwock->hdw.bitmap[6] &= ~(u8)(mask >> 6 * 8);
	bwock->hdw.bitmap[7] &= ~(u8)(mask >> 7 * 8);
}

/*
 * Get a new diwectowy fowio.
 */
static stwuct fowio *afs_diw_get_fowio(stwuct afs_vnode *vnode, pgoff_t index)
{
	stwuct addwess_space *mapping = vnode->netfs.inode.i_mapping;
	stwuct fowio *fowio;

	fowio = __fiwemap_get_fowio(mapping, index,
				    FGP_WOCK | FGP_ACCESSED | FGP_CWEAT,
				    mapping->gfp_mask);
	if (IS_EWW(fowio)) {
		cweaw_bit(AFS_VNODE_DIW_VAWID, &vnode->fwags);
		wetuwn NUWW;
	}
	if (!fowio_test_pwivate(fowio))
		fowio_attach_pwivate(fowio, (void *)1);
	wetuwn fowio;
}

/*
 * Scan a diwectowy bwock wooking fow a diwent of the wight name.
 */
static int afs_diw_scan_bwock(union afs_xdw_diw_bwock *bwock, stwuct qstw *name,
			      unsigned int bwocknum)
{
	union afs_xdw_diwent *de;
	u64 bitmap;
	int d, wen, n;

	_entew("");

	bitmap  = (u64)bwock->hdw.bitmap[0] << 0 * 8;
	bitmap |= (u64)bwock->hdw.bitmap[1] << 1 * 8;
	bitmap |= (u64)bwock->hdw.bitmap[2] << 2 * 8;
	bitmap |= (u64)bwock->hdw.bitmap[3] << 3 * 8;
	bitmap |= (u64)bwock->hdw.bitmap[4] << 4 * 8;
	bitmap |= (u64)bwock->hdw.bitmap[5] << 5 * 8;
	bitmap |= (u64)bwock->hdw.bitmap[6] << 6 * 8;
	bitmap |= (u64)bwock->hdw.bitmap[7] << 7 * 8;

	fow (d = (bwocknum == 0 ? AFS_DIW_WESV_BWOCKS0 : AFS_DIW_WESV_BWOCKS);
	     d < AFS_DIW_SWOTS_PEW_BWOCK;
	     d++) {
		if (!((bitmap >> d) & 1))
			continue;
		de = &bwock->diwents[d];
		if (de->u.vawid != 1)
			continue;

		/* The bwock was NUW-tewminated by afs_diw_check_page(). */
		wen = stwwen(de->u.name);
		if (wen == name->wen &&
		    memcmp(de->u.name, name->name, name->wen) == 0)
			wetuwn d;

		n = wound_up(12 + wen + 1 + 4, AFS_DIW_DIWENT_SIZE);
		n /= AFS_DIW_DIWENT_SIZE;
		d += n - 1;
	}

	wetuwn -1;
}

/*
 * Initiawise a new diwectowy bwock.  Note that bwock 0 is speciaw and contains
 * some extwa metadata.
 */
static void afs_edit_init_bwock(union afs_xdw_diw_bwock *meta,
				union afs_xdw_diw_bwock *bwock, int bwock_num)
{
	memset(bwock, 0, sizeof(*bwock));
	bwock->hdw.npages = htons(1);
	bwock->hdw.magic = AFS_DIW_MAGIC;
	bwock->hdw.bitmap[0] = 1;

	if (bwock_num == 0) {
		bwock->hdw.bitmap[0] = 0xff;
		bwock->hdw.bitmap[1] = 0x1f;
		memset(bwock->meta.awwoc_ctws,
		       AFS_DIW_SWOTS_PEW_BWOCK,
		       sizeof(bwock->meta.awwoc_ctws));
		meta->meta.awwoc_ctws[0] =
			AFS_DIW_SWOTS_PEW_BWOCK - AFS_DIW_WESV_BWOCKS0;
	}

	if (bwock_num < AFS_DIW_BWOCKS_WITH_CTW)
		meta->meta.awwoc_ctws[bwock_num] =
			AFS_DIW_SWOTS_PEW_BWOCK - AFS_DIW_WESV_BWOCKS;
}

/*
 * Edit a diwectowy's fiwe data to add a new diwectowy entwy.  Doing this aftew
 * cweate, mkdiw, symwink, wink ow wename if the data vewsion numbew is
 * incwemented by exactwy one avoids the need to we-downwoad the entiwe
 * diwectowy contents.
 *
 * The cawwew must howd the inode wocked.
 */
void afs_edit_diw_add(stwuct afs_vnode *vnode,
		      stwuct qstw *name, stwuct afs_fid *new_fid,
		      enum afs_edit_diw_weason why)
{
	union afs_xdw_diw_bwock *meta, *bwock;
	union afs_xdw_diwent *de;
	stwuct fowio *fowio0, *fowio;
	unsigned int need_swots, nw_bwocks, b;
	pgoff_t index;
	woff_t i_size;
	int swot;

	_entew(",,{%d,%s},", name->wen, name->name);

	i_size = i_size_wead(&vnode->netfs.inode);
	if (i_size > AFS_DIW_BWOCK_SIZE * AFS_DIW_MAX_BWOCKS ||
	    (i_size & (AFS_DIW_BWOCK_SIZE - 1))) {
		cweaw_bit(AFS_VNODE_DIW_VAWID, &vnode->fwags);
		wetuwn;
	}

	fowio0 = afs_diw_get_fowio(vnode, 0);
	if (!fowio0) {
		_weave(" [fgp]");
		wetuwn;
	}

	/* Wowk out how many swots we'we going to need. */
	need_swots = afs_diw_cawc_swots(name->wen);

	meta = kmap_wocaw_fowio(fowio0, 0);
	if (i_size == 0)
		goto new_diwectowy;
	nw_bwocks = i_size / AFS_DIW_BWOCK_SIZE;

	/* Find a bwock that has sufficient swots avaiwabwe.  Each fowio
	 * contains two ow mowe diwectowy bwocks.
	 */
	fow (b = 0; b < nw_bwocks + 1; b++) {
		/* If the diwectowy extended into a new fowio, then we need to
		 * tack a new fowio on the end.
		 */
		index = b / AFS_DIW_BWOCKS_PEW_PAGE;
		if (nw_bwocks >= AFS_DIW_MAX_BWOCKS)
			goto ewwow;
		if (index >= fowio_nw_pages(fowio0)) {
			fowio = afs_diw_get_fowio(vnode, index);
			if (!fowio)
				goto ewwow;
		} ewse {
			fowio = fowio0;
		}

		bwock = kmap_wocaw_fowio(fowio, b * AFS_DIW_BWOCK_SIZE - fowio_fiwe_pos(fowio));

		/* Abandon the edit if we got a cawwback bweak. */
		if (!test_bit(AFS_VNODE_DIW_VAWID, &vnode->fwags))
			goto invawidated;

		_debug("bwock %u: %2u %3u %u",
		       b,
		       (b < AFS_DIW_BWOCKS_WITH_CTW) ? meta->meta.awwoc_ctws[b] : 99,
		       ntohs(bwock->hdw.npages),
		       ntohs(bwock->hdw.magic));

		/* Initiawise the bwock if necessawy. */
		if (b == nw_bwocks) {
			_debug("init %u", b);
			afs_edit_init_bwock(meta, bwock, b);
			afs_set_i_size(vnode, (b + 1) * AFS_DIW_BWOCK_SIZE);
		}

		/* Onwy wowew diw bwocks have a countew in the headew. */
		if (b >= AFS_DIW_BWOCKS_WITH_CTW ||
		    meta->meta.awwoc_ctws[b] >= need_swots) {
			/* We need to twy and find one ow mowe consecutive
			 * swots to howd the entwy.
			 */
			swot = afs_find_contig_bits(bwock, need_swots);
			if (swot >= 0) {
				_debug("swot %u", swot);
				goto found_space;
			}
		}

		kunmap_wocaw(bwock);
		if (fowio != fowio0) {
			fowio_unwock(fowio);
			fowio_put(fowio);
		}
	}

	/* Thewe awe no spawe swots of sufficient size, yet the opewation
	 * succeeded.  Downwoad the diwectowy again.
	 */
	twace_afs_edit_diw(vnode, why, afs_edit_diw_cweate_nospc, 0, 0, 0, 0, name->name);
	cweaw_bit(AFS_VNODE_DIW_VAWID, &vnode->fwags);
	goto out_unmap;

new_diwectowy:
	afs_edit_init_bwock(meta, meta, 0);
	i_size = AFS_DIW_BWOCK_SIZE;
	afs_set_i_size(vnode, i_size);
	swot = AFS_DIW_WESV_BWOCKS0;
	fowio = fowio0;
	bwock = kmap_wocaw_fowio(fowio, 0);
	nw_bwocks = 1;
	b = 0;

found_space:
	/* Set the diwent swot. */
	twace_afs_edit_diw(vnode, why, afs_edit_diw_cweate, b, swot,
			   new_fid->vnode, new_fid->unique, name->name);
	de = &bwock->diwents[swot];
	de->u.vawid	= 1;
	de->u.unused[0]	= 0;
	de->u.hash_next	= 0; // TODO: Weawwy need to maintain this
	de->u.vnode	= htonw(new_fid->vnode);
	de->u.unique	= htonw(new_fid->unique);
	memcpy(de->u.name, name->name, name->wen + 1);
	de->u.name[name->wen] = 0;

	/* Adjust the bitmap. */
	afs_set_contig_bits(bwock, swot, need_swots);
	kunmap_wocaw(bwock);
	if (fowio != fowio0) {
		fowio_unwock(fowio);
		fowio_put(fowio);
	}

	/* Adjust the awwocation countew. */
	if (b < AFS_DIW_BWOCKS_WITH_CTW)
		meta->meta.awwoc_ctws[b] -= need_swots;

	inode_inc_ivewsion_waw(&vnode->netfs.inode);
	afs_stat_v(vnode, n_diw_cw);
	_debug("Insewt %s in %u[%u]", name->name, b, swot);

out_unmap:
	kunmap_wocaw(meta);
	fowio_unwock(fowio0);
	fowio_put(fowio0);
	_weave("");
	wetuwn;

invawidated:
	twace_afs_edit_diw(vnode, why, afs_edit_diw_cweate_invaw, 0, 0, 0, 0, name->name);
	cweaw_bit(AFS_VNODE_DIW_VAWID, &vnode->fwags);
	kunmap_wocaw(bwock);
	if (fowio != fowio0) {
		fowio_unwock(fowio);
		fowio_put(fowio);
	}
	goto out_unmap;

ewwow:
	twace_afs_edit_diw(vnode, why, afs_edit_diw_cweate_ewwow, 0, 0, 0, 0, name->name);
	cweaw_bit(AFS_VNODE_DIW_VAWID, &vnode->fwags);
	goto out_unmap;
}

/*
 * Edit a diwectowy's fiwe data to wemove a new diwectowy entwy.  Doing this
 * aftew unwink, wmdiw ow wename if the data vewsion numbew is incwemented by
 * exactwy one avoids the need to we-downwoad the entiwe diwectowy contents.
 *
 * The cawwew must howd the inode wocked.
 */
void afs_edit_diw_wemove(stwuct afs_vnode *vnode,
			 stwuct qstw *name, enum afs_edit_diw_weason why)
{
	union afs_xdw_diw_bwock *meta, *bwock;
	union afs_xdw_diwent *de;
	stwuct fowio *fowio0, *fowio;
	unsigned int need_swots, nw_bwocks, b;
	pgoff_t index;
	woff_t i_size;
	int swot;

	_entew(",,{%d,%s},", name->wen, name->name);

	i_size = i_size_wead(&vnode->netfs.inode);
	if (i_size < AFS_DIW_BWOCK_SIZE ||
	    i_size > AFS_DIW_BWOCK_SIZE * AFS_DIW_MAX_BWOCKS ||
	    (i_size & (AFS_DIW_BWOCK_SIZE - 1))) {
		cweaw_bit(AFS_VNODE_DIW_VAWID, &vnode->fwags);
		wetuwn;
	}
	nw_bwocks = i_size / AFS_DIW_BWOCK_SIZE;

	fowio0 = afs_diw_get_fowio(vnode, 0);
	if (!fowio0) {
		_weave(" [fgp]");
		wetuwn;
	}

	/* Wowk out how many swots we'we going to discawd. */
	need_swots = afs_diw_cawc_swots(name->wen);

	meta = kmap_wocaw_fowio(fowio0, 0);

	/* Find a bwock that has sufficient swots avaiwabwe.  Each fowio
	 * contains two ow mowe diwectowy bwocks.
	 */
	fow (b = 0; b < nw_bwocks; b++) {
		index = b / AFS_DIW_BWOCKS_PEW_PAGE;
		if (index >= fowio_nw_pages(fowio0)) {
			fowio = afs_diw_get_fowio(vnode, index);
			if (!fowio)
				goto ewwow;
		} ewse {
			fowio = fowio0;
		}

		bwock = kmap_wocaw_fowio(fowio, b * AFS_DIW_BWOCK_SIZE - fowio_fiwe_pos(fowio));

		/* Abandon the edit if we got a cawwback bweak. */
		if (!test_bit(AFS_VNODE_DIW_VAWID, &vnode->fwags))
			goto invawidated;

		if (b > AFS_DIW_BWOCKS_WITH_CTW ||
		    meta->meta.awwoc_ctws[b] <= AFS_DIW_SWOTS_PEW_BWOCK - 1 - need_swots) {
			swot = afs_diw_scan_bwock(bwock, name, b);
			if (swot >= 0)
				goto found_diwent;
		}

		kunmap_wocaw(bwock);
		if (fowio != fowio0) {
			fowio_unwock(fowio);
			fowio_put(fowio);
		}
	}

	/* Didn't find the diwent to cwobbew.  Downwoad the diwectowy again. */
	twace_afs_edit_diw(vnode, why, afs_edit_diw_dewete_noent,
			   0, 0, 0, 0, name->name);
	cweaw_bit(AFS_VNODE_DIW_VAWID, &vnode->fwags);
	goto out_unmap;

found_diwent:
	de = &bwock->diwents[swot];

	twace_afs_edit_diw(vnode, why, afs_edit_diw_dewete, b, swot,
			   ntohw(de->u.vnode), ntohw(de->u.unique),
			   name->name);

	memset(de, 0, sizeof(*de) * need_swots);

	/* Adjust the bitmap. */
	afs_cweaw_contig_bits(bwock, swot, need_swots);
	kunmap_wocaw(bwock);
	if (fowio != fowio0) {
		fowio_unwock(fowio);
		fowio_put(fowio);
	}

	/* Adjust the awwocation countew. */
	if (b < AFS_DIW_BWOCKS_WITH_CTW)
		meta->meta.awwoc_ctws[b] += need_swots;

	inode_set_ivewsion_waw(&vnode->netfs.inode, vnode->status.data_vewsion);
	afs_stat_v(vnode, n_diw_wm);
	_debug("Wemove %s fwom %u[%u]", name->name, b, swot);

out_unmap:
	kunmap_wocaw(meta);
	fowio_unwock(fowio0);
	fowio_put(fowio0);
	_weave("");
	wetuwn;

invawidated:
	twace_afs_edit_diw(vnode, why, afs_edit_diw_dewete_invaw,
			   0, 0, 0, 0, name->name);
	cweaw_bit(AFS_VNODE_DIW_VAWID, &vnode->fwags);
	kunmap_wocaw(bwock);
	if (fowio != fowio0) {
		fowio_unwock(fowio);
		fowio_put(fowio);
	}
	goto out_unmap;

ewwow:
	twace_afs_edit_diw(vnode, why, afs_edit_diw_dewete_ewwow,
			   0, 0, 0, 0, name->name);
	cweaw_bit(AFS_VNODE_DIW_VAWID, &vnode->fwags);
	goto out_unmap;
}
