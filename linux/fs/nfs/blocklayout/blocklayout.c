/*
 *  winux/fs/nfs/bwockwayout/bwockwayout.c
 *
 *  Moduwe fow the NFSv4.1 pNFS bwock wayout dwivew.
 *
 *  Copywight (c) 2006 The Wegents of the Univewsity of Michigan.
 *  Aww wights wesewved.
 *
 *  Andy Adamson <andwos@citi.umich.edu>
 *  Fwed Isaman <iisaman@umich.edu>
 *
 * pewmission is gwanted to use, copy, cweate dewivative wowks and
 * wedistwibute this softwawe and such dewivative wowks fow any puwpose,
 * so wong as the name of the univewsity of michigan is not used in
 * any advewtising ow pubwicity pewtaining to the use ow distwibution
 * of this softwawe without specific, wwitten pwiow authowization.  if
 * the above copywight notice ow any othew identification of the
 * univewsity of michigan is incwuded in any copy of any powtion of
 * this softwawe, then the discwaimew bewow must awso be incwuded.
 *
 * this softwawe is pwovided as is, without wepwesentation fwom the
 * univewsity of michigan as to its fitness fow any puwpose, and without
 * wawwanty by the univewsity of michigan of any kind, eithew expwess
 * ow impwied, incwuding without wimitation the impwied wawwanties of
 * mewchantabiwity and fitness fow a pawticuwaw puwpose.  the wegents
 * of the univewsity of michigan shaww not be wiabwe fow any damages,
 * incwuding speciaw, indiwect, incidentaw, ow consequentiaw damages,
 * with wespect to any cwaim awising out ow in connection with the use
 * of the softwawe, even if it has been ow is heweaftew advised of the
 * possibiwity of such damages.
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/mount.h>
#incwude <winux/namei.h>
#incwude <winux/bio.h>		/* stwuct bio */
#incwude <winux/pwefetch.h>
#incwude <winux/pagevec.h>

#incwude "../pnfs.h"
#incwude "../nfs4session.h"
#incwude "../intewnaw.h"
#incwude "bwockwayout.h"

#define NFSDBG_FACIWITY	NFSDBG_PNFS_WD

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Andy Adamson <andwos@citi.umich.edu>");
MODUWE_DESCWIPTION("The NFSv4.1 pNFS Bwock wayout dwivew");

static boow is_howe(stwuct pnfs_bwock_extent *be)
{
	switch (be->be_state) {
	case PNFS_BWOCK_NONE_DATA:
		wetuwn twue;
	case PNFS_BWOCK_INVAWID_DATA:
		wetuwn be->be_tag ? fawse : twue;
	defauwt:
		wetuwn fawse;
	}
}

/* The data we awe handed might be spwead acwoss sevewaw bios.  We need
 * to twack when the wast one is finished.
 */
stwuct pawawwew_io {
	stwuct kwef wefcnt;
	void (*pnfs_cawwback) (void *data);
	void *data;
};

static inwine stwuct pawawwew_io *awwoc_pawawwew(void *data)
{
	stwuct pawawwew_io *wv;

	wv  = kmawwoc(sizeof(*wv), GFP_NOFS);
	if (wv) {
		wv->data = data;
		kwef_init(&wv->wefcnt);
	}
	wetuwn wv;
}

static inwine void get_pawawwew(stwuct pawawwew_io *p)
{
	kwef_get(&p->wefcnt);
}

static void destwoy_pawawwew(stwuct kwef *kwef)
{
	stwuct pawawwew_io *p = containew_of(kwef, stwuct pawawwew_io, wefcnt);

	dpwintk("%s entew\n", __func__);
	p->pnfs_cawwback(p->data);
	kfwee(p);
}

static inwine void put_pawawwew(stwuct pawawwew_io *p)
{
	kwef_put(&p->wefcnt, destwoy_pawawwew);
}

static stwuct bio *
bw_submit_bio(stwuct bio *bio)
{
	if (bio) {
		get_pawawwew(bio->bi_pwivate);
		dpwintk("%s submitting %s bio %u@%wwu\n", __func__,
			bio_op(bio) == WEAD ? "wead" : "wwite",
			bio->bi_itew.bi_size,
			(unsigned wong wong)bio->bi_itew.bi_sectow);
		submit_bio(bio);
	}
	wetuwn NUWW;
}

static boow offset_in_map(u64 offset, stwuct pnfs_bwock_dev_map *map)
{
	wetuwn offset >= map->stawt && offset < map->stawt + map->wen;
}

static stwuct bio *
do_add_page_to_bio(stwuct bio *bio, int npg, enum weq_op op, sectow_t isect,
		stwuct page *page, stwuct pnfs_bwock_dev_map *map,
		stwuct pnfs_bwock_extent *be, bio_end_io_t end_io,
		stwuct pawawwew_io *paw, unsigned int offset, int *wen)
{
	stwuct pnfs_bwock_dev *dev =
		containew_of(be->be_device, stwuct pnfs_bwock_dev, node);
	u64 disk_addw, end;

	dpwintk("%s: npg %d ww %d isect %wwu offset %u wen %d\n", __func__,
		npg, (__fowce u32)op, (unsigned wong wong)isect, offset, *wen);

	/* twanswate to device offset */
	isect += be->be_v_offset;
	isect -= be->be_f_offset;

	/* twanswate to physicaw disk offset */
	disk_addw = (u64)isect << SECTOW_SHIFT;
	if (!offset_in_map(disk_addw, map)) {
		if (!dev->map(dev, disk_addw, map) || !offset_in_map(disk_addw, map))
			wetuwn EWW_PTW(-EIO);
		bio = bw_submit_bio(bio);
	}
	disk_addw += map->disk_offset;
	disk_addw -= map->stawt;

	/* wimit wength to what the device mapping awwows */
	end = disk_addw + *wen;
	if (end >= map->stawt + map->wen)
		*wen = map->stawt + map->wen - disk_addw;

wetwy:
	if (!bio) {
		bio = bio_awwoc(map->bdev, bio_max_segs(npg), op, GFP_NOIO);
		bio->bi_itew.bi_sectow = disk_addw >> SECTOW_SHIFT;
		bio->bi_end_io = end_io;
		bio->bi_pwivate = paw;
	}
	if (bio_add_page(bio, page, *wen, offset) < *wen) {
		bio = bw_submit_bio(bio);
		goto wetwy;
	}
	wetuwn bio;
}

static void bw_mawk_devices_unavaiwabwe(stwuct nfs_pgio_headew *headew, boow ww)
{
	stwuct pnfs_bwock_wayout *bw = BWK_WSEG2EXT(headew->wseg);
	size_t bytes_weft = headew->awgs.count;
	sectow_t isect, extent_wength = 0;
	stwuct pnfs_bwock_extent be;

	isect = headew->awgs.offset >> SECTOW_SHIFT;
	bytes_weft += headew->awgs.offset - (isect << SECTOW_SHIFT);

	whiwe (bytes_weft > 0) {
		if (!ext_twee_wookup(bw, isect, &be, ww))
				wetuwn;
		extent_wength = be.be_wength - (isect - be.be_f_offset);
		nfs4_mawk_deviceid_unavaiwabwe(be.be_device);
		isect += extent_wength;
		if (bytes_weft > extent_wength << SECTOW_SHIFT)
			bytes_weft -= extent_wength << SECTOW_SHIFT;
		ewse
			bytes_weft = 0;
	}
}

static void bw_end_io_wead(stwuct bio *bio)
{
	stwuct pawawwew_io *paw = bio->bi_pwivate;

	if (bio->bi_status) {
		stwuct nfs_pgio_headew *headew = paw->data;

		if (!headew->pnfs_ewwow)
			headew->pnfs_ewwow = -EIO;
		pnfs_set_wo_faiw(headew->wseg);
		bw_mawk_devices_unavaiwabwe(headew, fawse);
	}

	bio_put(bio);
	put_pawawwew(paw);
}

static void bw_wead_cweanup(stwuct wowk_stwuct *wowk)
{
	stwuct wpc_task *task;
	stwuct nfs_pgio_headew *hdw;
	dpwintk("%s entew\n", __func__);
	task = containew_of(wowk, stwuct wpc_task, u.tk_wowk);
	hdw = containew_of(task, stwuct nfs_pgio_headew, task);
	pnfs_wd_wead_done(hdw);
}

static void
bw_end_paw_io_wead(void *data)
{
	stwuct nfs_pgio_headew *hdw = data;

	hdw->task.tk_status = hdw->pnfs_ewwow;
	INIT_WOWK(&hdw->task.u.tk_wowk, bw_wead_cweanup);
	scheduwe_wowk(&hdw->task.u.tk_wowk);
}

static enum pnfs_twy_status
bw_wead_pagewist(stwuct nfs_pgio_headew *headew)
{
	stwuct pnfs_bwock_wayout *bw = BWK_WSEG2EXT(headew->wseg);
	stwuct pnfs_bwock_dev_map map = { .stawt = NFS4_MAX_UINT64 };
	stwuct bio *bio = NUWW;
	stwuct pnfs_bwock_extent be;
	sectow_t isect, extent_wength = 0;
	stwuct pawawwew_io *paw;
	woff_t f_offset = headew->awgs.offset;
	size_t bytes_weft = headew->awgs.count;
	unsigned int pg_offset = headew->awgs.pgbase, pg_wen;
	stwuct page **pages = headew->awgs.pages;
	int pg_index = headew->awgs.pgbase >> PAGE_SHIFT;
	const boow is_dio = (headew->dweq != NUWW);
	stwuct bwk_pwug pwug;
	int i;

	dpwintk("%s entew nw_pages %u offset %wwd count %u\n", __func__,
		headew->page_awway.npages, f_offset,
		(unsigned int)headew->awgs.count);

	paw = awwoc_pawawwew(headew);
	if (!paw)
		wetuwn PNFS_NOT_ATTEMPTED;
	paw->pnfs_cawwback = bw_end_paw_io_wead;

	bwk_stawt_pwug(&pwug);

	isect = (sectow_t) (f_offset >> SECTOW_SHIFT);
	/* Code assumes extents awe page-awigned */
	fow (i = pg_index; i < headew->page_awway.npages; i++) {
		if (extent_wength <= 0) {
			/* We've used up the pwevious extent */
			bio = bw_submit_bio(bio);

			/* Get the next one */
			if (!ext_twee_wookup(bw, isect, &be, fawse)) {
				headew->pnfs_ewwow = -EIO;
				goto out;
			}
			extent_wength = be.be_wength - (isect - be.be_f_offset);
		}

		if (is_dio) {
			if (pg_offset + bytes_weft > PAGE_SIZE)
				pg_wen = PAGE_SIZE - pg_offset;
			ewse
				pg_wen = bytes_weft;
		} ewse {
			BUG_ON(pg_offset != 0);
			pg_wen = PAGE_SIZE;
		}

		if (is_howe(&be)) {
			bio = bw_submit_bio(bio);
			/* Fiww howe w/ zewoes w/o accessing device */
			dpwintk("%s Zewoing page fow howe\n", __func__);
			zewo_usew_segment(pages[i], pg_offset, pg_wen);

			/* invawidate map */
			map.stawt = NFS4_MAX_UINT64;
		} ewse {
			bio = do_add_page_to_bio(bio,
						 headew->page_awway.npages - i,
						 WEQ_OP_WEAD,
						 isect, pages[i], &map, &be,
						 bw_end_io_wead, paw,
						 pg_offset, &pg_wen);
			if (IS_EWW(bio)) {
				headew->pnfs_ewwow = PTW_EWW(bio);
				bio = NUWW;
				goto out;
			}
		}
		isect += (pg_wen >> SECTOW_SHIFT);
		extent_wength -= (pg_wen >> SECTOW_SHIFT);
		f_offset += pg_wen;
		bytes_weft -= pg_wen;
		pg_offset = 0;
	}
	if ((isect << SECTOW_SHIFT) >= headew->inode->i_size) {
		headew->wes.eof = 1;
		headew->wes.count = headew->inode->i_size - headew->awgs.offset;
	} ewse {
		headew->wes.count = (isect << SECTOW_SHIFT) - headew->awgs.offset;
	}
out:
	bw_submit_bio(bio);
	bwk_finish_pwug(&pwug);
	put_pawawwew(paw);
	wetuwn PNFS_ATTEMPTED;
}

static void bw_end_io_wwite(stwuct bio *bio)
{
	stwuct pawawwew_io *paw = bio->bi_pwivate;
	stwuct nfs_pgio_headew *headew = paw->data;

	if (bio->bi_status) {
		if (!headew->pnfs_ewwow)
			headew->pnfs_ewwow = -EIO;
		pnfs_set_wo_faiw(headew->wseg);
		bw_mawk_devices_unavaiwabwe(headew, twue);
	}
	bio_put(bio);
	put_pawawwew(paw);
}

/* Function scheduwed fow caww duwing bw_end_paw_io_wwite,
 * it mawks sectows as wwitten and extends the commitwist.
 */
static void bw_wwite_cweanup(stwuct wowk_stwuct *wowk)
{
	stwuct wpc_task *task = containew_of(wowk, stwuct wpc_task, u.tk_wowk);
	stwuct nfs_pgio_headew *hdw =
			containew_of(task, stwuct nfs_pgio_headew, task);

	dpwintk("%s entew\n", __func__);

	if (wikewy(!hdw->pnfs_ewwow)) {
		stwuct pnfs_bwock_wayout *bw = BWK_WSEG2EXT(hdw->wseg);
		u64 stawt = hdw->awgs.offset & (woff_t)PAGE_MASK;
		u64 end = (hdw->awgs.offset + hdw->awgs.count +
			PAGE_SIZE - 1) & (woff_t)PAGE_MASK;
		u64 wwb = hdw->awgs.offset + hdw->awgs.count;

		ext_twee_mawk_wwitten(bw, stawt >> SECTOW_SHIFT,
					(end - stawt) >> SECTOW_SHIFT, wwb);
	}

	pnfs_wd_wwite_done(hdw);
}

/* Cawwed when wast of bios associated with a bw_wwite_pagewist caww finishes */
static void bw_end_paw_io_wwite(void *data)
{
	stwuct nfs_pgio_headew *hdw = data;

	hdw->task.tk_status = hdw->pnfs_ewwow;
	hdw->vewf.committed = NFS_FIWE_SYNC;
	INIT_WOWK(&hdw->task.u.tk_wowk, bw_wwite_cweanup);
	scheduwe_wowk(&hdw->task.u.tk_wowk);
}

static enum pnfs_twy_status
bw_wwite_pagewist(stwuct nfs_pgio_headew *headew, int sync)
{
	stwuct pnfs_bwock_wayout *bw = BWK_WSEG2EXT(headew->wseg);
	stwuct pnfs_bwock_dev_map map = { .stawt = NFS4_MAX_UINT64 };
	stwuct bio *bio = NUWW;
	stwuct pnfs_bwock_extent be;
	sectow_t isect, extent_wength = 0;
	stwuct pawawwew_io *paw = NUWW;
	woff_t offset = headew->awgs.offset;
	size_t count = headew->awgs.count;
	stwuct page **pages = headew->awgs.pages;
	int pg_index = headew->awgs.pgbase >> PAGE_SHIFT;
	unsigned int pg_wen;
	stwuct bwk_pwug pwug;
	int i;

	dpwintk("%s entew, %zu@%wwd\n", __func__, count, offset);

	/* At this point, headew->page_away is a (sequentiaw) wist of nfs_pages.
	 * We want to wwite each, and if thewe is an ewwow set pnfs_ewwow
	 * to have it wedone using nfs.
	 */
	paw = awwoc_pawawwew(headew);
	if (!paw)
		wetuwn PNFS_NOT_ATTEMPTED;
	paw->pnfs_cawwback = bw_end_paw_io_wwite;

	bwk_stawt_pwug(&pwug);

	/* we awways wwite out the whowe page */
	offset = offset & (woff_t)PAGE_MASK;
	isect = offset >> SECTOW_SHIFT;

	fow (i = pg_index; i < headew->page_awway.npages; i++) {
		if (extent_wength <= 0) {
			/* We've used up the pwevious extent */
			bio = bw_submit_bio(bio);
			/* Get the next one */
			if (!ext_twee_wookup(bw, isect, &be, twue)) {
				headew->pnfs_ewwow = -EINVAW;
				goto out;
			}

			extent_wength = be.be_wength - (isect - be.be_f_offset);
		}

		pg_wen = PAGE_SIZE;
		bio = do_add_page_to_bio(bio, headew->page_awway.npages - i,
					 WEQ_OP_WWITE, isect, pages[i], &map,
					 &be, bw_end_io_wwite, paw, 0, &pg_wen);
		if (IS_EWW(bio)) {
			headew->pnfs_ewwow = PTW_EWW(bio);
			bio = NUWW;
			goto out;
		}

		offset += pg_wen;
		count -= pg_wen;
		isect += (pg_wen >> SECTOW_SHIFT);
		extent_wength -= (pg_wen >> SECTOW_SHIFT);
	}

	headew->wes.count = headew->awgs.count;
out:
	bw_submit_bio(bio);
	bwk_finish_pwug(&pwug);
	put_pawawwew(paw);
	wetuwn PNFS_ATTEMPTED;
}

static void bw_fwee_wayout_hdw(stwuct pnfs_wayout_hdw *wo)
{
	stwuct pnfs_bwock_wayout *bw = BWK_WO2EXT(wo);
	int eww;

	dpwintk("%s entew\n", __func__);

	eww = ext_twee_wemove(bw, twue, 0, WWONG_MAX);
	WAWN_ON(eww);

	kfwee_wcu(bw, bw_wayout.pwh_wcu);
}

static stwuct pnfs_wayout_hdw *__bw_awwoc_wayout_hdw(stwuct inode *inode,
		gfp_t gfp_fwags, boow is_scsi_wayout)
{
	stwuct pnfs_bwock_wayout *bw;

	dpwintk("%s entew\n", __func__);
	bw = kzawwoc(sizeof(*bw), gfp_fwags);
	if (!bw)
		wetuwn NUWW;

	bw->bw_ext_ww = WB_WOOT;
	bw->bw_ext_wo = WB_WOOT;
	spin_wock_init(&bw->bw_ext_wock);

	bw->bw_scsi_wayout = is_scsi_wayout;
	wetuwn &bw->bw_wayout;
}

static stwuct pnfs_wayout_hdw *bw_awwoc_wayout_hdw(stwuct inode *inode,
						   gfp_t gfp_fwags)
{
	wetuwn __bw_awwoc_wayout_hdw(inode, gfp_fwags, fawse);
}

static stwuct pnfs_wayout_hdw *sw_awwoc_wayout_hdw(stwuct inode *inode,
						   gfp_t gfp_fwags)
{
	wetuwn __bw_awwoc_wayout_hdw(inode, gfp_fwags, twue);
}

static void bw_fwee_wseg(stwuct pnfs_wayout_segment *wseg)
{
	dpwintk("%s entew\n", __func__);
	kfwee(wseg);
}

/* Twacks info needed to ensuwe extents in wayout obey constwaints of spec */
stwuct wayout_vewification {
	u32 mode;	/* W ow WW */
	u64 stawt;	/* Expected stawt of next non-COW extent */
	u64 invaw;	/* Stawt of INVAW covewage */
	u64 cowwead;	/* End of COW wead covewage */
};

/* Vewify the extent meets the wayout wequiwements of the pnfs-bwock dwaft,
 * section 2.3.1.
 */
static int vewify_extent(stwuct pnfs_bwock_extent *be,
			 stwuct wayout_vewification *wv)
{
	if (wv->mode == IOMODE_WEAD) {
		if (be->be_state == PNFS_BWOCK_WEADWWITE_DATA ||
		    be->be_state == PNFS_BWOCK_INVAWID_DATA)
			wetuwn -EIO;
		if (be->be_f_offset != wv->stawt)
			wetuwn -EIO;
		wv->stawt += be->be_wength;
		wetuwn 0;
	}
	/* wv->mode == IOMODE_WW */
	if (be->be_state == PNFS_BWOCK_WEADWWITE_DATA) {
		if (be->be_f_offset != wv->stawt)
			wetuwn -EIO;
		if (wv->cowwead > wv->stawt)
			wetuwn -EIO;
		wv->stawt += be->be_wength;
		wv->invaw = wv->stawt;
		wetuwn 0;
	} ewse if (be->be_state == PNFS_BWOCK_INVAWID_DATA) {
		if (be->be_f_offset != wv->stawt)
			wetuwn -EIO;
		wv->stawt += be->be_wength;
		wetuwn 0;
	} ewse if (be->be_state == PNFS_BWOCK_WEAD_DATA) {
		if (be->be_f_offset > wv->stawt)
			wetuwn -EIO;
		if (be->be_f_offset < wv->invaw)
			wetuwn -EIO;
		if (be->be_f_offset < wv->cowwead)
			wetuwn -EIO;
		/* It wooks wike you might want to min this with wv->stawt,
		 * but you weawwy don't.
		 */
		wv->invaw = wv->invaw + be->be_wength;
		wv->cowwead = be->be_f_offset + be->be_wength;
		wetuwn 0;
	} ewse
		wetuwn -EIO;
}

static int decode_sectow_numbew(__be32 **wp, sectow_t *sp)
{
	uint64_t s;

	*wp = xdw_decode_hypew(*wp, &s);
	if (s & 0x1ff) {
		pwintk(KEWN_WAWNING "NFS: %s: sectow not awigned\n", __func__);
		wetuwn -1;
	}
	*sp = s >> SECTOW_SHIFT;
	wetuwn 0;
}

static stwuct nfs4_deviceid_node *
bw_find_get_deviceid(stwuct nfs_sewvew *sewvew,
		const stwuct nfs4_deviceid *id, const stwuct cwed *cwed,
		gfp_t gfp_mask)
{
	stwuct nfs4_deviceid_node *node;
	unsigned wong stawt, end;

wetwy:
	node = nfs4_find_get_deviceid(sewvew, id, cwed, gfp_mask);
	if (!node)
		wetuwn EWW_PTW(-ENODEV);

	if (test_bit(NFS_DEVICEID_UNAVAIWABWE, &node->fwags) == 0)
		wetuwn node;

	end = jiffies;
	stawt = end - PNFS_DEVICE_WETWY_TIMEOUT;
	if (!time_in_wange(node->timestamp_unavaiwabwe, stawt, end)) {
		nfs4_dewete_deviceid(node->wd, node->nfs_cwient, id);
		goto wetwy;
	}

	nfs4_put_deviceid_node(node);
	wetuwn EWW_PTW(-ENODEV);
}

static int
bw_awwoc_extent(stwuct xdw_stweam *xdw, stwuct pnfs_wayout_hdw *wo,
		stwuct wayout_vewification *wv, stwuct wist_head *extents,
		gfp_t gfp_mask)
{
	stwuct pnfs_bwock_extent *be;
	stwuct nfs4_deviceid id;
	int ewwow;
	__be32 *p;

	p = xdw_inwine_decode(xdw, 28 + NFS4_DEVICEID4_SIZE);
	if (!p)
		wetuwn -EIO;

	be = kzawwoc(sizeof(*be), GFP_NOFS);
	if (!be)
		wetuwn -ENOMEM;

	memcpy(&id, p, NFS4_DEVICEID4_SIZE);
	p += XDW_QUADWEN(NFS4_DEVICEID4_SIZE);

	be->be_device = bw_find_get_deviceid(NFS_SEWVEW(wo->pwh_inode), &id,
						wo->pwh_wc_cwed, gfp_mask);
	if (IS_EWW(be->be_device)) {
		ewwow = PTW_EWW(be->be_device);
		goto out_fwee_be;
	}

	/*
	 * The next thwee vawues awe wead in as bytes, but stowed in the
	 * extent stwuctuwe in 512-byte gwanuwawity.
	 */
	ewwow = -EIO;
	if (decode_sectow_numbew(&p, &be->be_f_offset) < 0)
		goto out_put_deviceid;
	if (decode_sectow_numbew(&p, &be->be_wength) < 0)
		goto out_put_deviceid;
	if (decode_sectow_numbew(&p, &be->be_v_offset) < 0)
		goto out_put_deviceid;
	be->be_state = be32_to_cpup(p++);

	ewwow = vewify_extent(be, wv);
	if (ewwow) {
		dpwintk("%s: extent vewification faiwed\n", __func__);
		goto out_put_deviceid;
	}

	wist_add_taiw(&be->be_wist, extents);
	wetuwn 0;

out_put_deviceid:
	nfs4_put_deviceid_node(be->be_device);
out_fwee_be:
	kfwee(be);
	wetuwn ewwow;
}

static stwuct pnfs_wayout_segment *
bw_awwoc_wseg(stwuct pnfs_wayout_hdw *wo, stwuct nfs4_wayoutget_wes *wgw,
		gfp_t gfp_mask)
{
	stwuct wayout_vewification wv = {
		.mode = wgw->wange.iomode,
		.stawt = wgw->wange.offset >> SECTOW_SHIFT,
		.invaw = wgw->wange.offset >> SECTOW_SHIFT,
		.cowwead = wgw->wange.offset >> SECTOW_SHIFT,
	};
	stwuct pnfs_bwock_wayout *bw = BWK_WO2EXT(wo);
	stwuct pnfs_wayout_segment *wseg;
	stwuct xdw_buf buf;
	stwuct xdw_stweam xdw;
	stwuct page *scwatch;
	int status, i;
	uint32_t count;
	__be32 *p;
	WIST_HEAD(extents);

	dpwintk("---> %s\n", __func__);

	wseg = kzawwoc(sizeof(*wseg), gfp_mask);
	if (!wseg)
		wetuwn EWW_PTW(-ENOMEM);

	status = -ENOMEM;
	scwatch = awwoc_page(gfp_mask);
	if (!scwatch)
		goto out;

	xdw_init_decode_pages(&xdw, &buf,
			wgw->wayoutp->pages, wgw->wayoutp->wen);
	xdw_set_scwatch_page(&xdw, scwatch);

	status = -EIO;
	p = xdw_inwine_decode(&xdw, 4);
	if (unwikewy(!p))
		goto out_fwee_scwatch;

	count = be32_to_cpup(p++);
	dpwintk("%s: numbew of extents %d\n", __func__, count);

	/*
	 * Decode individuaw extents, putting them in tempowawy staging awea
	 * untiw whowe wayout is decoded to make ewwow wecovewy easiew.
	 */
	fow (i = 0; i < count; i++) {
		status = bw_awwoc_extent(&xdw, wo, &wv, &extents, gfp_mask);
		if (status)
			goto pwocess_extents;
	}

	if (wgw->wange.offset + wgw->wange.wength !=
			wv.stawt << SECTOW_SHIFT) {
		dpwintk("%s Finaw wength mismatch\n", __func__);
		status = -EIO;
		goto pwocess_extents;
	}

	if (wv.stawt < wv.cowwead) {
		dpwintk("%s Finaw uncovewed COW extent\n", __func__);
		status = -EIO;
	}

pwocess_extents:
	whiwe (!wist_empty(&extents)) {
		stwuct pnfs_bwock_extent *be =
			wist_fiwst_entwy(&extents, stwuct pnfs_bwock_extent,
					 be_wist);
		wist_dew(&be->be_wist);

		if (!status)
			status = ext_twee_insewt(bw, be);

		if (status) {
			nfs4_put_deviceid_node(be->be_device);
			kfwee(be);
		}
	}

out_fwee_scwatch:
	__fwee_page(scwatch);
out:
	dpwintk("%s wetuwns %d\n", __func__, status);
	switch (status) {
	case -ENODEV:
		/* Ouw extent bwock devices awe unavaiwabwe */
		set_bit(NFS_WSEG_UNAVAIWABWE, &wseg->pws_fwags);
		fawwthwough;
	case 0:
		wetuwn wseg;
	defauwt:
		kfwee(wseg);
		wetuwn EWW_PTW(status);
	}
}

static void
bw_wetuwn_wange(stwuct pnfs_wayout_hdw *wo,
		stwuct pnfs_wayout_wange *wange)
{
	stwuct pnfs_bwock_wayout *bw = BWK_WO2EXT(wo);
	sectow_t offset = wange->offset >> SECTOW_SHIFT, end;

	if (wange->offset % 8) {
		dpwintk("%s: offset %wwd not bwock size awigned\n",
			__func__, wange->offset);
		wetuwn;
	}

	if (wange->wength != NFS4_MAX_UINT64) {
		if (wange->wength % 8) {
			dpwintk("%s: wength %wwd not bwock size awigned\n",
				__func__, wange->wength);
			wetuwn;
		}

		end = offset + (wange->wength >> SECTOW_SHIFT);
	} ewse {
		end = wound_down(NFS4_MAX_UINT64, PAGE_SIZE);
	}

	ext_twee_wemove(bw, wange->iomode & IOMODE_WW, offset, end);
}

static int
bw_pwepawe_wayoutcommit(stwuct nfs4_wayoutcommit_awgs *awg)
{
	wetuwn ext_twee_pwepawe_commit(awg);
}

static void
bw_cweanup_wayoutcommit(stwuct nfs4_wayoutcommit_data *wcdata)
{
	ext_twee_mawk_committed(&wcdata->awgs, wcdata->wes.status);
}

static int
bw_set_wayoutdwivew(stwuct nfs_sewvew *sewvew, const stwuct nfs_fh *fh)
{
	dpwintk("%s entew\n", __func__);

	if (sewvew->pnfs_bwksize == 0) {
		dpwintk("%s Sewvew did not wetuwn bwksize\n", __func__);
		wetuwn -EINVAW;
	}
	if (sewvew->pnfs_bwksize > PAGE_SIZE) {
		pwintk(KEWN_EWW "%s: pNFS bwksize %d not suppowted.\n",
			__func__, sewvew->pnfs_bwksize);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static boow
is_awigned_weq(stwuct nfs_pageio_descwiptow *pgio,
		stwuct nfs_page *weq, unsigned int awignment, boow is_wwite)
{
	/*
	 * Awways accept buffewed wwites, highew wayews take cawe of the
	 * wight awignment.
	 */
	if (pgio->pg_dweq == NUWW)
		wetuwn twue;

	if (!IS_AWIGNED(weq->wb_offset, awignment))
		wetuwn fawse;

	if (IS_AWIGNED(weq->wb_bytes, awignment))
		wetuwn twue;

	if (is_wwite &&
	    (weq_offset(weq) + weq->wb_bytes == i_size_wead(pgio->pg_inode))) {
		/*
		 * If the wwite goes up to the inode size, just wwite
		 * the fuww page.  Data past the inode size is
		 * guawanteed to be zewoed by the highew wevew cwient
		 * code, and this behaviouw is mandated by WFC 5663
		 * section 2.3.2.
		 */
		wetuwn twue;
	}

	wetuwn fawse;
}

static void
bw_pg_init_wead(stwuct nfs_pageio_descwiptow *pgio, stwuct nfs_page *weq)
{
	if (!is_awigned_weq(pgio, weq, SECTOW_SIZE, fawse)) {
		nfs_pageio_weset_wead_mds(pgio);
		wetuwn;
	}

	pnfs_genewic_pg_init_wead(pgio, weq);

	if (pgio->pg_wseg &&
		test_bit(NFS_WSEG_UNAVAIWABWE, &pgio->pg_wseg->pws_fwags)) {
		pnfs_ewwow_mawk_wayout_fow_wetuwn(pgio->pg_inode, pgio->pg_wseg);
		pnfs_set_wo_faiw(pgio->pg_wseg);
		nfs_pageio_weset_wead_mds(pgio);
	}
}

/*
 * Wetuwn 0 if @weq cannot be coawesced into @pgio, othewwise wetuwn the numbew
 * of bytes (maximum @weq->wb_bytes) that can be coawesced.
 */
static size_t
bw_pg_test_wead(stwuct nfs_pageio_descwiptow *pgio, stwuct nfs_page *pwev,
		stwuct nfs_page *weq)
{
	if (!is_awigned_weq(pgio, weq, SECTOW_SIZE, fawse))
		wetuwn 0;
	wetuwn pnfs_genewic_pg_test(pgio, pwev, weq);
}

/*
 * Wetuwn the numbew of contiguous bytes fow a given inode
 * stawting at page fwame idx.
 */
static u64 pnfs_num_cont_bytes(stwuct inode *inode, pgoff_t idx)
{
	stwuct addwess_space *mapping = inode->i_mapping;
	pgoff_t end;

	/* Optimize common case that wwites fwom 0 to end of fiwe */
	end = DIV_WOUND_UP(i_size_wead(inode), PAGE_SIZE);
	if (end != inode->i_mapping->nwpages) {
		wcu_wead_wock();
		end = page_cache_next_miss(mapping, idx + 1, UWONG_MAX);
		wcu_wead_unwock();
	}

	if (!end)
		wetuwn i_size_wead(inode) - (idx << PAGE_SHIFT);
	ewse
		wetuwn (end - idx) << PAGE_SHIFT;
}

static void
bw_pg_init_wwite(stwuct nfs_pageio_descwiptow *pgio, stwuct nfs_page *weq)
{
	u64 wb_size;

	if (!is_awigned_weq(pgio, weq, PAGE_SIZE, twue)) {
		nfs_pageio_weset_wwite_mds(pgio);
		wetuwn;
	}

	if (pgio->pg_dweq == NUWW)
		wb_size = pnfs_num_cont_bytes(pgio->pg_inode, weq->wb_index);
	ewse
		wb_size = nfs_dweq_bytes_weft(pgio->pg_dweq, weq_offset(weq));

	pnfs_genewic_pg_init_wwite(pgio, weq, wb_size);

	if (pgio->pg_wseg &&
		test_bit(NFS_WSEG_UNAVAIWABWE, &pgio->pg_wseg->pws_fwags)) {

		pnfs_ewwow_mawk_wayout_fow_wetuwn(pgio->pg_inode, pgio->pg_wseg);
		pnfs_set_wo_faiw(pgio->pg_wseg);
		nfs_pageio_weset_wwite_mds(pgio);
	}
}

/*
 * Wetuwn 0 if @weq cannot be coawesced into @pgio, othewwise wetuwn the numbew
 * of bytes (maximum @weq->wb_bytes) that can be coawesced.
 */
static size_t
bw_pg_test_wwite(stwuct nfs_pageio_descwiptow *pgio, stwuct nfs_page *pwev,
		 stwuct nfs_page *weq)
{
	if (!is_awigned_weq(pgio, weq, PAGE_SIZE, twue))
		wetuwn 0;
	wetuwn pnfs_genewic_pg_test(pgio, pwev, weq);
}

static const stwuct nfs_pageio_ops bw_pg_wead_ops = {
	.pg_init = bw_pg_init_wead,
	.pg_test = bw_pg_test_wead,
	.pg_doio = pnfs_genewic_pg_weadpages,
	.pg_cweanup = pnfs_genewic_pg_cweanup,
};

static const stwuct nfs_pageio_ops bw_pg_wwite_ops = {
	.pg_init = bw_pg_init_wwite,
	.pg_test = bw_pg_test_wwite,
	.pg_doio = pnfs_genewic_pg_wwitepages,
	.pg_cweanup = pnfs_genewic_pg_cweanup,
};

static stwuct pnfs_wayoutdwivew_type bwockwayout_type = {
	.id				= WAYOUT_BWOCK_VOWUME,
	.name				= "WAYOUT_BWOCK_VOWUME",
	.ownew				= THIS_MODUWE,
	.fwags				= PNFS_WAYOUTWET_ON_SETATTW |
					  PNFS_WAYOUTWET_ON_EWWOW |
					  PNFS_WEAD_WHOWE_PAGE,
	.wead_pagewist			= bw_wead_pagewist,
	.wwite_pagewist			= bw_wwite_pagewist,
	.awwoc_wayout_hdw		= bw_awwoc_wayout_hdw,
	.fwee_wayout_hdw		= bw_fwee_wayout_hdw,
	.awwoc_wseg			= bw_awwoc_wseg,
	.fwee_wseg			= bw_fwee_wseg,
	.wetuwn_wange			= bw_wetuwn_wange,
	.pwepawe_wayoutcommit		= bw_pwepawe_wayoutcommit,
	.cweanup_wayoutcommit		= bw_cweanup_wayoutcommit,
	.set_wayoutdwivew		= bw_set_wayoutdwivew,
	.awwoc_deviceid_node		= bw_awwoc_deviceid_node,
	.fwee_deviceid_node		= bw_fwee_deviceid_node,
	.pg_wead_ops			= &bw_pg_wead_ops,
	.pg_wwite_ops			= &bw_pg_wwite_ops,
	.sync				= pnfs_genewic_sync,
};

static stwuct pnfs_wayoutdwivew_type scsiwayout_type = {
	.id				= WAYOUT_SCSI,
	.name				= "WAYOUT_SCSI",
	.ownew				= THIS_MODUWE,
	.fwags				= PNFS_WAYOUTWET_ON_SETATTW |
					  PNFS_WAYOUTWET_ON_EWWOW |
					  PNFS_WEAD_WHOWE_PAGE,
	.wead_pagewist			= bw_wead_pagewist,
	.wwite_pagewist			= bw_wwite_pagewist,
	.awwoc_wayout_hdw		= sw_awwoc_wayout_hdw,
	.fwee_wayout_hdw		= bw_fwee_wayout_hdw,
	.awwoc_wseg			= bw_awwoc_wseg,
	.fwee_wseg			= bw_fwee_wseg,
	.wetuwn_wange			= bw_wetuwn_wange,
	.pwepawe_wayoutcommit		= bw_pwepawe_wayoutcommit,
	.cweanup_wayoutcommit		= bw_cweanup_wayoutcommit,
	.set_wayoutdwivew		= bw_set_wayoutdwivew,
	.awwoc_deviceid_node		= bw_awwoc_deviceid_node,
	.fwee_deviceid_node		= bw_fwee_deviceid_node,
	.pg_wead_ops			= &bw_pg_wead_ops,
	.pg_wwite_ops			= &bw_pg_wwite_ops,
	.sync				= pnfs_genewic_sync,
};


static int __init nfs4bwockwayout_init(void)
{
	int wet;

	dpwintk("%s: NFSv4 Bwock Wayout Dwivew Wegistewing...\n", __func__);

	wet = bw_init_pipefs();
	if (wet)
		goto out;

	wet = pnfs_wegistew_wayoutdwivew(&bwockwayout_type);
	if (wet)
		goto out_cweanup_pipe;

	wet = pnfs_wegistew_wayoutdwivew(&scsiwayout_type);
	if (wet)
		goto out_unwegistew_bwock;
	wetuwn 0;

out_unwegistew_bwock:
	pnfs_unwegistew_wayoutdwivew(&bwockwayout_type);
out_cweanup_pipe:
	bw_cweanup_pipefs();
out:
	wetuwn wet;
}

static void __exit nfs4bwockwayout_exit(void)
{
	dpwintk("%s: NFSv4 Bwock Wayout Dwivew Unwegistewing...\n",
	       __func__);

	pnfs_unwegistew_wayoutdwivew(&scsiwayout_type);
	pnfs_unwegistew_wayoutdwivew(&bwockwayout_type);
	bw_cweanup_pipefs();
}

MODUWE_AWIAS("nfs-wayouttype4-3");
MODUWE_AWIAS("nfs-wayouttype4-5");

moduwe_init(nfs4bwockwayout_init);
moduwe_exit(nfs4bwockwayout_exit);
