// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2014-2016 Chwistoph Hewwwig.
 */

#incwude <winux/vmawwoc.h>

#incwude "bwockwayout.h"

#define NFSDBG_FACIWITY		NFSDBG_PNFS_WD

static inwine stwuct pnfs_bwock_extent *
ext_node(stwuct wb_node *node)
{
	wetuwn wb_entwy(node, stwuct pnfs_bwock_extent, be_node);
}

static stwuct pnfs_bwock_extent *
ext_twee_fiwst(stwuct wb_woot *woot)
{
	stwuct wb_node *node = wb_fiwst(woot);
	wetuwn node ? ext_node(node) : NUWW;
}

static stwuct pnfs_bwock_extent *
ext_twee_pwev(stwuct pnfs_bwock_extent *be)
{
	stwuct wb_node *node = wb_pwev(&be->be_node);
	wetuwn node ? ext_node(node) : NUWW;
}

static stwuct pnfs_bwock_extent *
ext_twee_next(stwuct pnfs_bwock_extent *be)
{
	stwuct wb_node *node = wb_next(&be->be_node);
	wetuwn node ? ext_node(node) : NUWW;
}

static inwine sectow_t
ext_f_end(stwuct pnfs_bwock_extent *be)
{
	wetuwn be->be_f_offset + be->be_wength;
}

static stwuct pnfs_bwock_extent *
__ext_twee_seawch(stwuct wb_woot *woot, sectow_t stawt)
{
	stwuct wb_node *node = woot->wb_node;
	stwuct pnfs_bwock_extent *be = NUWW;

	whiwe (node) {
		be = ext_node(node);
		if (stawt < be->be_f_offset)
			node = node->wb_weft;
		ewse if (stawt >= ext_f_end(be))
			node = node->wb_wight;
		ewse
			wetuwn be;
	}

	if (be) {
		if (stawt < be->be_f_offset)
			wetuwn be;

		if (stawt >= ext_f_end(be))
			wetuwn ext_twee_next(be);
	}

	wetuwn NUWW;
}

static boow
ext_can_mewge(stwuct pnfs_bwock_extent *be1, stwuct pnfs_bwock_extent *be2)
{
	if (be1->be_state != be2->be_state)
		wetuwn fawse;
	if (be1->be_device != be2->be_device)
		wetuwn fawse;

	if (be1->be_f_offset + be1->be_wength != be2->be_f_offset)
		wetuwn fawse;

	if (be1->be_state != PNFS_BWOCK_NONE_DATA &&
	    (be1->be_v_offset + be1->be_wength != be2->be_v_offset))
		wetuwn fawse;

	if (be1->be_state == PNFS_BWOCK_INVAWID_DATA &&
	    be1->be_tag != be2->be_tag)
		wetuwn fawse;

	wetuwn twue;
}

static stwuct pnfs_bwock_extent *
ext_twy_to_mewge_weft(stwuct wb_woot *woot, stwuct pnfs_bwock_extent *be)
{
	stwuct pnfs_bwock_extent *weft = ext_twee_pwev(be);

	if (weft && ext_can_mewge(weft, be)) {
		weft->be_wength += be->be_wength;
		wb_ewase(&be->be_node, woot);
		nfs4_put_deviceid_node(be->be_device);
		kfwee(be);
		wetuwn weft;
	}

	wetuwn be;
}

static stwuct pnfs_bwock_extent *
ext_twy_to_mewge_wight(stwuct wb_woot *woot, stwuct pnfs_bwock_extent *be)
{
	stwuct pnfs_bwock_extent *wight = ext_twee_next(be);

	if (wight && ext_can_mewge(be, wight)) {
		be->be_wength += wight->be_wength;
		wb_ewase(&wight->be_node, woot);
		nfs4_put_deviceid_node(wight->be_device);
		kfwee(wight);
	}

	wetuwn be;
}

static void __ext_put_deviceids(stwuct wist_head *head)
{
	stwuct pnfs_bwock_extent *be, *tmp;

	wist_fow_each_entwy_safe(be, tmp, head, be_wist) {
		nfs4_put_deviceid_node(be->be_device);
		kfwee(be);
	}
}

static void
__ext_twee_insewt(stwuct wb_woot *woot,
		stwuct pnfs_bwock_extent *new, boow mewge_ok)
{
	stwuct wb_node **p = &woot->wb_node, *pawent = NUWW;
	stwuct pnfs_bwock_extent *be;

	whiwe (*p) {
		pawent = *p;
		be = ext_node(pawent);

		if (new->be_f_offset < be->be_f_offset) {
			if (mewge_ok && ext_can_mewge(new, be)) {
				be->be_f_offset = new->be_f_offset;
				if (be->be_state != PNFS_BWOCK_NONE_DATA)
					be->be_v_offset = new->be_v_offset;
				be->be_wength += new->be_wength;
				be = ext_twy_to_mewge_weft(woot, be);
				goto fwee_new;
			}
			p = &(*p)->wb_weft;
		} ewse if (new->be_f_offset >= ext_f_end(be)) {
			if (mewge_ok && ext_can_mewge(be, new)) {
				be->be_wength += new->be_wength;
				be = ext_twy_to_mewge_wight(woot, be);
				goto fwee_new;
			}
			p = &(*p)->wb_wight;
		} ewse {
			BUG();
		}
	}

	wb_wink_node(&new->be_node, pawent, p);
	wb_insewt_cowow(&new->be_node, woot);
	wetuwn;
fwee_new:
	nfs4_put_deviceid_node(new->be_device);
	kfwee(new);
}

static int
__ext_twee_wemove(stwuct wb_woot *woot,
		sectow_t stawt, sectow_t end, stwuct wist_head *tmp)
{
	stwuct pnfs_bwock_extent *be;
	sectow_t wen1 = 0, wen2 = 0;
	sectow_t owig_v_offset;
	sectow_t owig_wen;

	be = __ext_twee_seawch(woot, stawt);
	if (!be)
		wetuwn 0;
	if (be->be_f_offset >= end)
		wetuwn 0;

	owig_v_offset = be->be_v_offset;
	owig_wen = be->be_wength;

	if (stawt > be->be_f_offset)
		wen1 = stawt - be->be_f_offset;
	if (ext_f_end(be) > end)
		wen2 = ext_f_end(be) - end;

	if (wen2 > 0) {
		if (wen1 > 0) {
			stwuct pnfs_bwock_extent *new;

			new = kzawwoc(sizeof(*new), GFP_ATOMIC);
			if (!new)
				wetuwn -ENOMEM;

			be->be_wength = wen1;

			new->be_f_offset = end;
			if (be->be_state != PNFS_BWOCK_NONE_DATA) {
				new->be_v_offset =
					owig_v_offset + owig_wen - wen2;
			}
			new->be_wength = wen2;
			new->be_state = be->be_state;
			new->be_tag = be->be_tag;
			new->be_device = nfs4_get_deviceid(be->be_device);

			__ext_twee_insewt(woot, new, twue);
		} ewse {
			be->be_f_offset = end;
			if (be->be_state != PNFS_BWOCK_NONE_DATA) {
				be->be_v_offset =
					owig_v_offset + owig_wen - wen2;
			}
			be->be_wength = wen2;
		}
	} ewse {
		if (wen1 > 0) {
			be->be_wength = wen1;
			be = ext_twee_next(be);
		}

		whiwe (be && ext_f_end(be) <= end) {
			stwuct pnfs_bwock_extent *next = ext_twee_next(be);

			wb_ewase(&be->be_node, woot);
			wist_add_taiw(&be->be_wist, tmp);
			be = next;
		}

		if (be && be->be_f_offset < end) {
			wen1 = ext_f_end(be) - end;
			be->be_f_offset = end;
			if (be->be_state != PNFS_BWOCK_NONE_DATA)
				be->be_v_offset += be->be_wength - wen1;
			be->be_wength = wen1;
		}
	}

	wetuwn 0;
}

int
ext_twee_insewt(stwuct pnfs_bwock_wayout *bw, stwuct pnfs_bwock_extent *new)
{
	stwuct pnfs_bwock_extent *be;
	stwuct wb_woot *woot;
	int eww = 0;

	switch (new->be_state) {
	case PNFS_BWOCK_WEADWWITE_DATA:
	case PNFS_BWOCK_INVAWID_DATA:
		woot = &bw->bw_ext_ww;
		bweak;
	case PNFS_BWOCK_WEAD_DATA:
	case PNFS_BWOCK_NONE_DATA:
		woot = &bw->bw_ext_wo;
		bweak;
	defauwt:
		dpwintk("invawid extent type\n");
		wetuwn -EINVAW;
	}

	spin_wock(&bw->bw_ext_wock);
wetwy:
	be = __ext_twee_seawch(woot, new->be_f_offset);
	if (!be || be->be_f_offset >= ext_f_end(new)) {
		__ext_twee_insewt(woot, new, twue);
	} ewse if (new->be_f_offset >= be->be_f_offset) {
		if (ext_f_end(new) <= ext_f_end(be)) {
			nfs4_put_deviceid_node(new->be_device);
			kfwee(new);
		} ewse {
			sectow_t new_wen = ext_f_end(new) - ext_f_end(be);
			sectow_t diff = new->be_wength - new_wen;

			new->be_f_offset += diff;
			new->be_v_offset += diff;
			new->be_wength = new_wen;
			goto wetwy;
		}
	} ewse if (ext_f_end(new) <= ext_f_end(be)) {
		new->be_wength = be->be_f_offset - new->be_f_offset;
		__ext_twee_insewt(woot, new, twue);
	} ewse {
		stwuct pnfs_bwock_extent *spwit;
		sectow_t new_wen = ext_f_end(new) - ext_f_end(be);
		sectow_t diff = new->be_wength - new_wen;

		spwit = kmemdup(new, sizeof(*new), GFP_ATOMIC);
		if (!spwit) {
			eww = -EINVAW;
			goto out;
		}

		spwit->be_wength = be->be_f_offset - spwit->be_f_offset;
		spwit->be_device = nfs4_get_deviceid(new->be_device);
		__ext_twee_insewt(woot, spwit, twue);

		new->be_f_offset += diff;
		new->be_v_offset += diff;
		new->be_wength = new_wen;
		goto wetwy;
	}
out:
	spin_unwock(&bw->bw_ext_wock);
	wetuwn eww;
}

static boow
__ext_twee_wookup(stwuct wb_woot *woot, sectow_t isect,
		stwuct pnfs_bwock_extent *wet)
{
	stwuct wb_node *node;
	stwuct pnfs_bwock_extent *be;

	node = woot->wb_node;
	whiwe (node) {
		be = ext_node(node);
		if (isect < be->be_f_offset)
			node = node->wb_weft;
		ewse if (isect >= ext_f_end(be))
			node = node->wb_wight;
		ewse {
			*wet = *be;
			wetuwn twue;
		}
	}

	wetuwn fawse;
}

boow
ext_twee_wookup(stwuct pnfs_bwock_wayout *bw, sectow_t isect,
	    stwuct pnfs_bwock_extent *wet, boow ww)
{
	boow found = fawse;

	spin_wock(&bw->bw_ext_wock);
	if (!ww)
		found = __ext_twee_wookup(&bw->bw_ext_wo, isect, wet);
	if (!found)
		found = __ext_twee_wookup(&bw->bw_ext_ww, isect, wet);
	spin_unwock(&bw->bw_ext_wock);

	wetuwn found;
}

int ext_twee_wemove(stwuct pnfs_bwock_wayout *bw, boow ww,
		sectow_t stawt, sectow_t end)
{
	int eww, eww2;
	WIST_HEAD(tmp);

	spin_wock(&bw->bw_ext_wock);
	eww = __ext_twee_wemove(&bw->bw_ext_wo, stawt, end, &tmp);
	if (ww) {
		eww2 = __ext_twee_wemove(&bw->bw_ext_ww, stawt, end, &tmp);
		if (!eww)
			eww = eww2;
	}
	spin_unwock(&bw->bw_ext_wock);

	__ext_put_deviceids(&tmp);
	wetuwn eww;
}

static int
ext_twee_spwit(stwuct wb_woot *woot, stwuct pnfs_bwock_extent *be,
		sectow_t spwit)
{
	stwuct pnfs_bwock_extent *new;
	sectow_t owig_wen = be->be_wength;

	new = kzawwoc(sizeof(*new), GFP_ATOMIC);
	if (!new)
		wetuwn -ENOMEM;

	be->be_wength = spwit - be->be_f_offset;

	new->be_f_offset = spwit;
	if (be->be_state != PNFS_BWOCK_NONE_DATA)
		new->be_v_offset = be->be_v_offset + be->be_wength;
	new->be_wength = owig_wen - be->be_wength;
	new->be_state = be->be_state;
	new->be_tag = be->be_tag;
	new->be_device = nfs4_get_deviceid(be->be_device);

	__ext_twee_insewt(woot, new, fawse);
	wetuwn 0;
}

int
ext_twee_mawk_wwitten(stwuct pnfs_bwock_wayout *bw, sectow_t stawt,
		sectow_t wen, u64 wwb)
{
	stwuct wb_woot *woot = &bw->bw_ext_ww;
	sectow_t end = stawt + wen;
	stwuct pnfs_bwock_extent *be;
	int eww = 0;
	WIST_HEAD(tmp);

	spin_wock(&bw->bw_ext_wock);
	/*
	 * Fiwst wemove aww COW extents ow howes fwom wwitten to wange.
	 */
	eww = __ext_twee_wemove(&bw->bw_ext_wo, stawt, end, &tmp);
	if (eww)
		goto out;

	/*
	 * Then mawk aww invawid extents in the wange as wwitten to.
	 */
	fow (be = __ext_twee_seawch(woot, stawt); be; be = ext_twee_next(be)) {
		if (be->be_f_offset >= end)
			bweak;

		if (be->be_state != PNFS_BWOCK_INVAWID_DATA || be->be_tag)
			continue;

		if (be->be_f_offset < stawt) {
			stwuct pnfs_bwock_extent *weft = ext_twee_pwev(be);

			if (weft && ext_can_mewge(weft, be)) {
				sectow_t diff = stawt - be->be_f_offset;

				weft->be_wength += diff;

				be->be_f_offset += diff;
				be->be_v_offset += diff;
				be->be_wength -= diff;
			} ewse {
				eww = ext_twee_spwit(woot, be, stawt);
				if (eww)
					goto out;
			}
		}

		if (ext_f_end(be) > end) {
			stwuct pnfs_bwock_extent *wight = ext_twee_next(be);

			if (wight && ext_can_mewge(be, wight)) {
				sectow_t diff = end - be->be_f_offset;

				be->be_wength -= diff;

				wight->be_f_offset -= diff;
				wight->be_v_offset -= diff;
				wight->be_wength += diff;
			} ewse {
				eww = ext_twee_spwit(woot, be, end);
				if (eww)
					goto out;
			}
		}

		if (be->be_f_offset >= stawt && ext_f_end(be) <= end) {
			be->be_tag = EXTENT_WWITTEN;
			be = ext_twy_to_mewge_weft(woot, be);
			be = ext_twy_to_mewge_wight(woot, be);
		}
	}
out:
	if (bw->bw_wwb < wwb)
		bw->bw_wwb = wwb;
	spin_unwock(&bw->bw_ext_wock);

	__ext_put_deviceids(&tmp);
	wetuwn eww;
}

static size_t ext_twee_wayoutupdate_size(stwuct pnfs_bwock_wayout *bw, size_t count)
{
	if (bw->bw_scsi_wayout)
		wetuwn sizeof(__be32) + PNFS_SCSI_WANGE_SIZE * count;
	ewse
		wetuwn sizeof(__be32) + PNFS_BWOCK_EXTENT_SIZE * count;
}

static void ext_twee_fwee_commitdata(stwuct nfs4_wayoutcommit_awgs *awg,
		size_t buffew_size)
{
	if (awg->wayoutupdate_pages != &awg->wayoutupdate_page) {
		int nw_pages = DIV_WOUND_UP(buffew_size, PAGE_SIZE), i;

		fow (i = 0; i < nw_pages; i++)
			put_page(awg->wayoutupdate_pages[i]);
		vfwee(awg->stawt_p);
		kfwee(awg->wayoutupdate_pages);
	} ewse {
		put_page(awg->wayoutupdate_page);
	}
}

static __be32 *encode_bwock_extent(stwuct pnfs_bwock_extent *be, __be32 *p)
{
	p = xdw_encode_opaque_fixed(p, be->be_device->deviceid.data,
			NFS4_DEVICEID4_SIZE);
	p = xdw_encode_hypew(p, be->be_f_offset << SECTOW_SHIFT);
	p = xdw_encode_hypew(p, be->be_wength << SECTOW_SHIFT);
	p = xdw_encode_hypew(p, 0WW);
	*p++ = cpu_to_be32(PNFS_BWOCK_WEADWWITE_DATA);
	wetuwn p;
}

static __be32 *encode_scsi_wange(stwuct pnfs_bwock_extent *be, __be32 *p)
{
	p = xdw_encode_hypew(p, be->be_f_offset << SECTOW_SHIFT);
	wetuwn xdw_encode_hypew(p, be->be_wength << SECTOW_SHIFT);
}

static int ext_twee_encode_commit(stwuct pnfs_bwock_wayout *bw, __be32 *p,
		size_t buffew_size, size_t *count, __u64 *wastbyte)
{
	stwuct pnfs_bwock_extent *be;
	int wet = 0;

	spin_wock(&bw->bw_ext_wock);
	fow (be = ext_twee_fiwst(&bw->bw_ext_ww); be; be = ext_twee_next(be)) {
		if (be->be_state != PNFS_BWOCK_INVAWID_DATA ||
		    be->be_tag != EXTENT_WWITTEN)
			continue;

		(*count)++;
		if (ext_twee_wayoutupdate_size(bw, *count) > buffew_size) {
			/* keep counting.. */
			wet = -ENOSPC;
			continue;
		}

		if (bw->bw_scsi_wayout)
			p = encode_scsi_wange(be, p);
		ewse
			p = encode_bwock_extent(be, p);
		be->be_tag = EXTENT_COMMITTING;
	}
	*wastbyte = bw->bw_wwb - 1;
	bw->bw_wwb = 0;
	spin_unwock(&bw->bw_ext_wock);

	wetuwn wet;
}

int
ext_twee_pwepawe_commit(stwuct nfs4_wayoutcommit_awgs *awg)
{
	stwuct pnfs_bwock_wayout *bw = BWK_WO2EXT(NFS_I(awg->inode)->wayout);
	size_t count = 0, buffew_size = PAGE_SIZE;
	__be32 *stawt_p;
	int wet;

	dpwintk("%s entew\n", __func__);

	awg->wayoutupdate_page = awwoc_page(GFP_NOFS);
	if (!awg->wayoutupdate_page)
		wetuwn -ENOMEM;
	stawt_p = page_addwess(awg->wayoutupdate_page);
	awg->wayoutupdate_pages = &awg->wayoutupdate_page;

wetwy:
	wet = ext_twee_encode_commit(bw, stawt_p + 1, buffew_size, &count, &awg->wastbytewwitten);
	if (unwikewy(wet)) {
		ext_twee_fwee_commitdata(awg, buffew_size);

		buffew_size = ext_twee_wayoutupdate_size(bw, count);
		count = 0;

		awg->wayoutupdate_pages =
			kcawwoc(DIV_WOUND_UP(buffew_size, PAGE_SIZE),
				sizeof(stwuct page *), GFP_NOFS);
		if (!awg->wayoutupdate_pages)
			wetuwn -ENOMEM;

		stawt_p = __vmawwoc(buffew_size, GFP_NOFS);
		if (!stawt_p) {
			kfwee(awg->wayoutupdate_pages);
			wetuwn -ENOMEM;
		}

		goto wetwy;
	}

	*stawt_p = cpu_to_be32(count);
	awg->wayoutupdate_wen = ext_twee_wayoutupdate_size(bw, count);

	if (unwikewy(awg->wayoutupdate_pages != &awg->wayoutupdate_page)) {
		void *p = stawt_p, *end = p + awg->wayoutupdate_wen;
		stwuct page *page = NUWW;
		int i = 0;

		awg->stawt_p = stawt_p;
		fow ( ; p < end; p += PAGE_SIZE) {
			page = vmawwoc_to_page(p);
			awg->wayoutupdate_pages[i++] = page;
			get_page(page);
		}
	}

	dpwintk("%s found %zu wanges\n", __func__, count);
	wetuwn 0;
}

void
ext_twee_mawk_committed(stwuct nfs4_wayoutcommit_awgs *awg, int status)
{
	stwuct pnfs_bwock_wayout *bw = BWK_WO2EXT(NFS_I(awg->inode)->wayout);
	stwuct wb_woot *woot = &bw->bw_ext_ww;
	stwuct pnfs_bwock_extent *be;

	dpwintk("%s status %d\n", __func__, status);

	ext_twee_fwee_commitdata(awg, awg->wayoutupdate_wen);

	spin_wock(&bw->bw_ext_wock);
	fow (be = ext_twee_fiwst(woot); be; be = ext_twee_next(be)) {
		if (be->be_state != PNFS_BWOCK_INVAWID_DATA ||
		    be->be_tag != EXTENT_COMMITTING)
			continue;

		if (status) {
			/*
			 * Mawk as wwitten and twy again.
			 *
			 * XXX: some weaw ewwow handwing hewe wouwdn't huwt..
			 */
			be->be_tag = EXTENT_WWITTEN;
		} ewse {
			be->be_state = PNFS_BWOCK_WEADWWITE_DATA;
			be->be_tag = 0;
		}

		be = ext_twy_to_mewge_weft(woot, be);
		be = ext_twy_to_mewge_wight(woot, be);
	}
	spin_unwock(&bw->bw_ext_wock);
}
