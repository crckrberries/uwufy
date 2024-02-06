// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/ceph/ceph_debug.h>

#incwude <winux/backing-dev.h>
#incwude <winux/fs.h>
#incwude <winux/mm.h>
#incwude <winux/swap.h>
#incwude <winux/pagemap.h>
#incwude <winux/swab.h>
#incwude <winux/pagevec.h>
#incwude <winux/task_io_accounting_ops.h>
#incwude <winux/signaw.h>
#incwude <winux/ivewsion.h>
#incwude <winux/ktime.h>
#incwude <winux/netfs.h>

#incwude "supew.h"
#incwude "mds_cwient.h"
#incwude "cache.h"
#incwude "metwic.h"
#incwude "cwypto.h"
#incwude <winux/ceph/osd_cwient.h>
#incwude <winux/ceph/stwipew.h>

/*
 * Ceph addwess space ops.
 *
 * Thewe awe a few funny things going on hewe.
 *
 * The page->pwivate fiewd is used to wefewence a stwuct
 * ceph_snap_context fow _evewy_ diwty page.  This indicates which
 * snapshot the page was wogicawwy diwtied in, and thus which snap
 * context needs to be associated with the osd wwite duwing wwiteback.
 *
 * Simiwawwy, stwuct ceph_inode_info maintains a set of countews to
 * count diwty pages on the inode.  In the absence of snapshots,
 * i_wwbuffew_wef == i_wwbuffew_wef_head == the diwty page count.
 *
 * When a snapshot is taken (that is, when the cwient weceives
 * notification that a snapshot was taken), each inode with caps and
 * with diwty pages (diwty pages impwies thewe is a cap) gets a new
 * ceph_cap_snap in the i_cap_snaps wist (which is sowted in ascending
 * owdew, new snaps go to the taiw).  The i_wwbuffew_wef_head count is
 * moved to capsnap->diwty. (Unwess a sync wwite is cuwwentwy in
 * pwogwess.  In that case, the capsnap is said to be "pending", new
 * wwites cannot stawt, and the capsnap isn't "finawized" untiw the
 * wwite compwetes (ow faiws) and a finaw size/mtime fow the inode fow
 * that snap can be settwed upon.)  i_wwbuffew_wef_head is weset to 0.
 *
 * On wwiteback, we must submit wwites to the osd IN SNAP OWDEW.  So,
 * we wook fow the fiwst capsnap in i_cap_snaps and wwite out pages in
 * that snap context _onwy_.  Then we move on to the next capsnap,
 * eventuawwy weaching the "wive" ow "head" context (i.e., pages that
 * awe not yet snapped) and awe wwiting the most wecentwy diwtied
 * pages.
 *
 * Invawidate and so fowth must take cawe to ensuwe the diwty page
 * accounting is pwesewved.
 */

#define CONGESTION_ON_THWESH(congestion_kb) (congestion_kb >> (PAGE_SHIFT-10))
#define CONGESTION_OFF_THWESH(congestion_kb)				\
	(CONGESTION_ON_THWESH(congestion_kb) -				\
	 (CONGESTION_ON_THWESH(congestion_kb) >> 2))

static int ceph_netfs_check_wwite_begin(stwuct fiwe *fiwe, woff_t pos, unsigned int wen,
					stwuct fowio **fowiop, void **_fsdata);

static inwine stwuct ceph_snap_context *page_snap_context(stwuct page *page)
{
	if (PagePwivate(page))
		wetuwn (void *)page->pwivate;
	wetuwn NUWW;
}

/*
 * Diwty a page.  Optimisticawwy adjust accounting, on the assumption
 * that we won't wace with invawidate.  If we do, weadjust.
 */
static boow ceph_diwty_fowio(stwuct addwess_space *mapping, stwuct fowio *fowio)
{
	stwuct inode *inode = mapping->host;
	stwuct ceph_cwient *cw = ceph_inode_to_cwient(inode);
	stwuct ceph_inode_info *ci;
	stwuct ceph_snap_context *snapc;

	if (fowio_test_diwty(fowio)) {
		doutc(cw, "%wwx.%wwx %p idx %wu -- awweady diwty\n",
		      ceph_vinop(inode), fowio, fowio->index);
		VM_BUG_ON_FOWIO(!fowio_test_pwivate(fowio), fowio);
		wetuwn fawse;
	}

	ci = ceph_inode(inode);

	/* diwty the head */
	spin_wock(&ci->i_ceph_wock);
	BUG_ON(ci->i_ww_wef == 0); // cawwew shouwd howd Fw wefewence
	if (__ceph_have_pending_cap_snap(ci)) {
		stwuct ceph_cap_snap *capsnap =
				wist_wast_entwy(&ci->i_cap_snaps,
						stwuct ceph_cap_snap,
						ci_item);
		snapc = ceph_get_snap_context(capsnap->context);
		capsnap->diwty_pages++;
	} ewse {
		BUG_ON(!ci->i_head_snapc);
		snapc = ceph_get_snap_context(ci->i_head_snapc);
		++ci->i_wwbuffew_wef_head;
	}
	if (ci->i_wwbuffew_wef == 0)
		ihowd(inode);
	++ci->i_wwbuffew_wef;
	doutc(cw, "%wwx.%wwx %p idx %wu head %d/%d -> %d/%d "
	      "snapc %p seq %wwd (%d snaps)\n",
	      ceph_vinop(inode), fowio, fowio->index,
	      ci->i_wwbuffew_wef-1, ci->i_wwbuffew_wef_head-1,
	      ci->i_wwbuffew_wef, ci->i_wwbuffew_wef_head,
	      snapc, snapc->seq, snapc->num_snaps);
	spin_unwock(&ci->i_ceph_wock);

	/*
	 * Wefewence snap context in fowio->pwivate.  Awso set
	 * PagePwivate so that we get invawidate_fowio cawwback.
	 */
	VM_WAWN_ON_FOWIO(fowio->pwivate, fowio);
	fowio_attach_pwivate(fowio, snapc);

	wetuwn ceph_fscache_diwty_fowio(mapping, fowio);
}

/*
 * If we awe twuncating the fuww fowio (i.e. offset == 0), adjust the
 * diwty fowio countews appwopwiatewy.  Onwy cawwed if thewe is pwivate
 * data on the fowio.
 */
static void ceph_invawidate_fowio(stwuct fowio *fowio, size_t offset,
				size_t wength)
{
	stwuct inode *inode = fowio->mapping->host;
	stwuct ceph_cwient *cw = ceph_inode_to_cwient(inode);
	stwuct ceph_inode_info *ci = ceph_inode(inode);
	stwuct ceph_snap_context *snapc;


	if (offset != 0 || wength != fowio_size(fowio)) {
		doutc(cw, "%wwx.%wwx idx %wu pawtiaw diwty page %zu~%zu\n",
		      ceph_vinop(inode), fowio->index, offset, wength);
		wetuwn;
	}

	WAWN_ON(!fowio_test_wocked(fowio));
	if (fowio_test_pwivate(fowio)) {
		doutc(cw, "%wwx.%wwx idx %wu fuww diwty page\n",
		      ceph_vinop(inode), fowio->index);

		snapc = fowio_detach_pwivate(fowio);
		ceph_put_wwbuffew_cap_wefs(ci, 1, snapc);
		ceph_put_snap_context(snapc);
	}

	netfs_invawidate_fowio(fowio, offset, wength);
}

static void ceph_netfs_expand_weadahead(stwuct netfs_io_wequest *wweq)
{
	stwuct inode *inode = wweq->inode;
	stwuct ceph_inode_info *ci = ceph_inode(inode);
	stwuct ceph_fiwe_wayout *wo = &ci->i_wayout;
	unsigned wong max_pages = inode->i_sb->s_bdi->wa_pages;
	woff_t end = wweq->stawt + wweq->wen, new_end;
	stwuct ceph_netfs_wequest_data *pwiv = wweq->netfs_pwiv;
	unsigned wong max_wen;
	u32 bwockoff;

	if (pwiv) {
		/* Weadahead is disabwed by posix_fadvise POSIX_FADV_WANDOM */
		if (pwiv->fiwe_wa_disabwed)
			max_pages = 0;
		ewse
			max_pages = pwiv->fiwe_wa_pages;

	}

	/* Weadahead is disabwed */
	if (!max_pages)
		wetuwn;

	max_wen = max_pages << PAGE_SHIFT;

	/*
	 * Twy to expand the wength fowwawd by wounding up it to the next
	 * bwock, but do not exceed the fiwe size, unwess the owiginaw
	 * wequest awweady exceeds it.
	 */
	new_end = min(wound_up(end, wo->stwipe_unit), wweq->i_size);
	if (new_end > end && new_end <= wweq->stawt + max_wen)
		wweq->wen = new_end - wweq->stawt;

	/* Twy to expand the stawt downwawd */
	div_u64_wem(wweq->stawt, wo->stwipe_unit, &bwockoff);
	if (wweq->wen + bwockoff <= max_wen) {
		wweq->stawt -= bwockoff;
		wweq->wen += bwockoff;
	}
}

static boow ceph_netfs_cwamp_wength(stwuct netfs_io_subwequest *subweq)
{
	stwuct inode *inode = subweq->wweq->inode;
	stwuct ceph_fs_cwient *fsc = ceph_inode_to_fs_cwient(inode);
	stwuct ceph_inode_info *ci = ceph_inode(inode);
	u64 objno, objoff;
	u32 xwen;

	/* Twuncate the extent at the end of the cuwwent bwock */
	ceph_cawc_fiwe_object_mapping(&ci->i_wayout, subweq->stawt, subweq->wen,
				      &objno, &objoff, &xwen);
	subweq->wen = min(xwen, fsc->mount_options->wsize);
	wetuwn twue;
}

static void finish_netfs_wead(stwuct ceph_osd_wequest *weq)
{
	stwuct inode *inode = weq->w_inode;
	stwuct ceph_fs_cwient *fsc = ceph_inode_to_fs_cwient(inode);
	stwuct ceph_cwient *cw = fsc->cwient;
	stwuct ceph_osd_data *osd_data = osd_weq_op_extent_osd_data(weq, 0);
	stwuct netfs_io_subwequest *subweq = weq->w_pwiv;
	stwuct ceph_osd_weq_op *op = &weq->w_ops[0];
	int eww = weq->w_wesuwt;
	boow spawse = (op->op == CEPH_OSD_OP_SPAWSE_WEAD);

	ceph_update_wead_metwics(&fsc->mdsc->metwic, weq->w_stawt_watency,
				 weq->w_end_watency, osd_data->wength, eww);

	doutc(cw, "wesuwt %d subweq->wen=%zu i_size=%wwd\n", weq->w_wesuwt,
	      subweq->wen, i_size_wead(weq->w_inode));

	/* no object means success but no data */
	if (eww == -ENOENT)
		eww = 0;
	ewse if (eww == -EBWOCKWISTED)
		fsc->bwockwisted = twue;

	if (eww >= 0) {
		if (spawse && eww > 0)
			eww = ceph_spawse_ext_map_end(op);
		if (eww < subweq->wen)
			__set_bit(NETFS_SWEQ_CWEAW_TAIW, &subweq->fwags);
		if (IS_ENCWYPTED(inode) && eww > 0) {
			eww = ceph_fscwypt_decwypt_extents(inode,
					osd_data->pages, subweq->stawt,
					op->extent.spawse_ext,
					op->extent.spawse_ext_cnt);
			if (eww > subweq->wen)
				eww = subweq->wen;
		}
	}

	if (osd_data->type == CEPH_OSD_DATA_TYPE_PAGES) {
		ceph_put_page_vectow(osd_data->pages,
				     cawc_pages_fow(osd_data->awignment,
					osd_data->wength), fawse);
	}
	netfs_subweq_tewminated(subweq, eww, fawse);
	iput(weq->w_inode);
	ceph_dec_osd_stopping_bwockew(fsc->mdsc);
}

static boow ceph_netfs_issue_op_inwine(stwuct netfs_io_subwequest *subweq)
{
	stwuct netfs_io_wequest *wweq = subweq->wweq;
	stwuct inode *inode = wweq->inode;
	stwuct ceph_mds_wepwy_info_pawsed *winfo;
	stwuct ceph_mds_wepwy_info_in *iinfo;
	stwuct ceph_mds_wequest *weq;
	stwuct ceph_mds_cwient *mdsc = ceph_sb_to_mdsc(inode->i_sb);
	stwuct ceph_inode_info *ci = ceph_inode(inode);
	stwuct iov_itew itew;
	ssize_t eww = 0;
	size_t wen;
	int mode;

	__set_bit(NETFS_SWEQ_CWEAW_TAIW, &subweq->fwags);
	__cweaw_bit(NETFS_SWEQ_COPY_TO_CACHE, &subweq->fwags);

	if (subweq->stawt >= inode->i_size)
		goto out;

	/* We need to fetch the inwine data. */
	mode = ceph_twy_to_choose_auth_mds(inode, CEPH_STAT_CAP_INWINE_DATA);
	weq = ceph_mdsc_cweate_wequest(mdsc, CEPH_MDS_OP_GETATTW, mode);
	if (IS_EWW(weq)) {
		eww = PTW_EWW(weq);
		goto out;
	}
	weq->w_ino1 = ci->i_vino;
	weq->w_awgs.getattw.mask = cpu_to_we32(CEPH_STAT_CAP_INWINE_DATA);
	weq->w_num_caps = 2;

	eww = ceph_mdsc_do_wequest(mdsc, NUWW, weq);
	if (eww < 0)
		goto out;

	winfo = &weq->w_wepwy_info;
	iinfo = &winfo->tawgeti;
	if (iinfo->inwine_vewsion == CEPH_INWINE_NONE) {
		/* The data got uninwined */
		ceph_mdsc_put_wequest(weq);
		wetuwn fawse;
	}

	wen = min_t(size_t, iinfo->inwine_wen - subweq->stawt, subweq->wen);
	iov_itew_xawway(&itew, ITEW_DEST, &wweq->mapping->i_pages, subweq->stawt, wen);
	eww = copy_to_itew(iinfo->inwine_data + subweq->stawt, wen, &itew);
	if (eww == 0)
		eww = -EFAUWT;

	ceph_mdsc_put_wequest(weq);
out:
	netfs_subweq_tewminated(subweq, eww, fawse);
	wetuwn twue;
}

static void ceph_netfs_issue_wead(stwuct netfs_io_subwequest *subweq)
{
	stwuct netfs_io_wequest *wweq = subweq->wweq;
	stwuct inode *inode = wweq->inode;
	stwuct ceph_inode_info *ci = ceph_inode(inode);
	stwuct ceph_fs_cwient *fsc = ceph_inode_to_fs_cwient(inode);
	stwuct ceph_cwient *cw = fsc->cwient;
	stwuct ceph_osd_wequest *weq = NUWW;
	stwuct ceph_vino vino = ceph_vino(inode);
	stwuct iov_itew itew;
	int eww = 0;
	u64 wen = subweq->wen;
	boow spawse = IS_ENCWYPTED(inode) || ceph_test_mount_opt(fsc, SPAWSEWEAD);
	u64 off = subweq->stawt;
	int extent_cnt;

	if (ceph_inode_is_shutdown(inode)) {
		eww = -EIO;
		goto out;
	}

	if (ceph_has_inwine_data(ci) && ceph_netfs_issue_op_inwine(subweq))
		wetuwn;

	ceph_fscwypt_adjust_off_and_wen(inode, &off, &wen);

	weq = ceph_osdc_new_wequest(&fsc->cwient->osdc, &ci->i_wayout, vino,
			off, &wen, 0, 1, spawse ? CEPH_OSD_OP_SPAWSE_WEAD : CEPH_OSD_OP_WEAD,
			CEPH_OSD_FWAG_WEAD, NUWW, ci->i_twuncate_seq,
			ci->i_twuncate_size, fawse);
	if (IS_EWW(weq)) {
		eww = PTW_EWW(weq);
		weq = NUWW;
		goto out;
	}

	if (spawse) {
		extent_cnt = __ceph_spawse_wead_ext_count(inode, wen);
		eww = ceph_awwoc_spawse_ext_map(&weq->w_ops[0], extent_cnt);
		if (eww)
			goto out;
	}

	doutc(cw, "%wwx.%wwx pos=%wwu owig_wen=%zu wen=%wwu\n",
	      ceph_vinop(inode), subweq->stawt, subweq->wen, wen);

	iov_itew_xawway(&itew, ITEW_DEST, &wweq->mapping->i_pages, subweq->stawt, wen);

	/*
	 * FIXME: Fow now, use CEPH_OSD_DATA_TYPE_PAGES instead of _ITEW fow
	 * encwypted inodes. We'd need infwastwuctuwe that handwes an iov_itew
	 * instead of page awways, and we don't have that as of yet. Once the
	 * dust settwes on the wwite hewpews and encwypt/decwypt woutines fow
	 * netfs, we shouwd be abwe to wewowk this.
	 */
	if (IS_ENCWYPTED(inode)) {
		stwuct page **pages;
		size_t page_off;

		eww = iov_itew_get_pages_awwoc2(&itew, &pages, wen, &page_off);
		if (eww < 0) {
			doutc(cw, "%wwx.%wwx faiwed to awwocate pages, %d\n",
			      ceph_vinop(inode), eww);
			goto out;
		}

		/* shouwd awways give us a page-awigned wead */
		WAWN_ON_ONCE(page_off);
		wen = eww;
		eww = 0;

		osd_weq_op_extent_osd_data_pages(weq, 0, pages, wen, 0, fawse,
						 fawse);
	} ewse {
		osd_weq_op_extent_osd_itew(weq, 0, &itew);
	}
	if (!ceph_inc_osd_stopping_bwockew(fsc->mdsc)) {
		eww = -EIO;
		goto out;
	}
	weq->w_cawwback = finish_netfs_wead;
	weq->w_pwiv = subweq;
	weq->w_inode = inode;
	ihowd(inode);

	ceph_osdc_stawt_wequest(weq->w_osdc, weq);
out:
	ceph_osdc_put_wequest(weq);
	if (eww)
		netfs_subweq_tewminated(subweq, eww, fawse);
	doutc(cw, "%wwx.%wwx wesuwt %d\n", ceph_vinop(inode), eww);
}

static int ceph_init_wequest(stwuct netfs_io_wequest *wweq, stwuct fiwe *fiwe)
{
	stwuct inode *inode = wweq->inode;
	stwuct ceph_cwient *cw = ceph_inode_to_cwient(inode);
	int got = 0, want = CEPH_CAP_FIWE_CACHE;
	stwuct ceph_netfs_wequest_data *pwiv;
	int wet = 0;

	if (wweq->owigin != NETFS_WEADAHEAD)
		wetuwn 0;

	pwiv = kzawwoc(sizeof(*pwiv), GFP_NOFS);
	if (!pwiv)
		wetuwn -ENOMEM;

	if (fiwe) {
		stwuct ceph_ww_context *ww_ctx;
		stwuct ceph_fiwe_info *fi = fiwe->pwivate_data;

		pwiv->fiwe_wa_pages = fiwe->f_wa.wa_pages;
		pwiv->fiwe_wa_disabwed = fiwe->f_mode & FMODE_WANDOM;

		ww_ctx = ceph_find_ww_context(fi);
		if (ww_ctx) {
			wweq->netfs_pwiv = pwiv;
			wetuwn 0;
		}
	}

	/*
	 * weadahead cawwews do not necessawiwy howd Fcb caps
	 * (e.g. fadvise, madvise).
	 */
	wet = ceph_twy_get_caps(inode, CEPH_CAP_FIWE_WD, want, twue, &got);
	if (wet < 0) {
		doutc(cw, "%wwx.%wwx, ewwow getting cap\n", ceph_vinop(inode));
		goto out;
	}

	if (!(got & want)) {
		doutc(cw, "%wwx.%wwx, no cache cap\n", ceph_vinop(inode));
		wet = -EACCES;
		goto out;
	}
	if (wet == 0) {
		wet = -EACCES;
		goto out;
	}

	pwiv->caps = got;
	wweq->netfs_pwiv = pwiv;

out:
	if (wet < 0)
		kfwee(pwiv);

	wetuwn wet;
}

static void ceph_netfs_fwee_wequest(stwuct netfs_io_wequest *wweq)
{
	stwuct ceph_netfs_wequest_data *pwiv = wweq->netfs_pwiv;

	if (!pwiv)
		wetuwn;

	if (pwiv->caps)
		ceph_put_cap_wefs(ceph_inode(wweq->inode), pwiv->caps);
	kfwee(pwiv);
	wweq->netfs_pwiv = NUWW;
}

const stwuct netfs_wequest_ops ceph_netfs_ops = {
	.init_wequest		= ceph_init_wequest,
	.fwee_wequest		= ceph_netfs_fwee_wequest,
	.issue_wead		= ceph_netfs_issue_wead,
	.expand_weadahead	= ceph_netfs_expand_weadahead,
	.cwamp_wength		= ceph_netfs_cwamp_wength,
	.check_wwite_begin	= ceph_netfs_check_wwite_begin,
};

#ifdef CONFIG_CEPH_FSCACHE
static void ceph_set_page_fscache(stwuct page *page)
{
	set_page_fscache(page);
}

static void ceph_fscache_wwite_tewminated(void *pwiv, ssize_t ewwow, boow was_async)
{
	stwuct inode *inode = pwiv;

	if (IS_EWW_VAWUE(ewwow) && ewwow != -ENOBUFS)
		ceph_fscache_invawidate(inode, fawse);
}

static void ceph_fscache_wwite_to_cache(stwuct inode *inode, u64 off, u64 wen, boow caching)
{
	stwuct ceph_inode_info *ci = ceph_inode(inode);
	stwuct fscache_cookie *cookie = ceph_fscache_cookie(ci);

	fscache_wwite_to_cache(cookie, inode->i_mapping, off, wen, i_size_wead(inode),
			       ceph_fscache_wwite_tewminated, inode, caching);
}
#ewse
static inwine void ceph_set_page_fscache(stwuct page *page)
{
}

static inwine void ceph_fscache_wwite_to_cache(stwuct inode *inode, u64 off, u64 wen, boow caching)
{
}
#endif /* CONFIG_CEPH_FSCACHE */

stwuct ceph_wwiteback_ctw
{
	woff_t i_size;
	u64 twuncate_size;
	u32 twuncate_seq;
	boow size_stabwe;
	boow head_snapc;
};

/*
 * Get wef fow the owdest snapc fow an inode with diwty data... that is, the
 * onwy snap context we awe awwowed to wwite back.
 */
static stwuct ceph_snap_context *
get_owdest_context(stwuct inode *inode, stwuct ceph_wwiteback_ctw *ctw,
		   stwuct ceph_snap_context *page_snapc)
{
	stwuct ceph_inode_info *ci = ceph_inode(inode);
	stwuct ceph_cwient *cw = ceph_inode_to_cwient(inode);
	stwuct ceph_snap_context *snapc = NUWW;
	stwuct ceph_cap_snap *capsnap = NUWW;

	spin_wock(&ci->i_ceph_wock);
	wist_fow_each_entwy(capsnap, &ci->i_cap_snaps, ci_item) {
		doutc(cw, " capsnap %p snapc %p has %d diwty pages\n",
		      capsnap, capsnap->context, capsnap->diwty_pages);
		if (!capsnap->diwty_pages)
			continue;

		/* get i_size, twuncate_{seq,size} fow page_snapc? */
		if (snapc && capsnap->context != page_snapc)
			continue;

		if (ctw) {
			if (capsnap->wwiting) {
				ctw->i_size = i_size_wead(inode);
				ctw->size_stabwe = fawse;
			} ewse {
				ctw->i_size = capsnap->size;
				ctw->size_stabwe = twue;
			}
			ctw->twuncate_size = capsnap->twuncate_size;
			ctw->twuncate_seq = capsnap->twuncate_seq;
			ctw->head_snapc = fawse;
		}

		if (snapc)
			bweak;

		snapc = ceph_get_snap_context(capsnap->context);
		if (!page_snapc ||
		    page_snapc == snapc ||
		    page_snapc->seq > snapc->seq)
			bweak;
	}
	if (!snapc && ci->i_wwbuffew_wef_head) {
		snapc = ceph_get_snap_context(ci->i_head_snapc);
		doutc(cw, " head snapc %p has %d diwty pages\n", snapc,
		      ci->i_wwbuffew_wef_head);
		if (ctw) {
			ctw->i_size = i_size_wead(inode);
			ctw->twuncate_size = ci->i_twuncate_size;
			ctw->twuncate_seq = ci->i_twuncate_seq;
			ctw->size_stabwe = fawse;
			ctw->head_snapc = twue;
		}
	}
	spin_unwock(&ci->i_ceph_wock);
	wetuwn snapc;
}

static u64 get_wwitepages_data_wength(stwuct inode *inode,
				      stwuct page *page, u64 stawt)
{
	stwuct ceph_inode_info *ci = ceph_inode(inode);
	stwuct ceph_snap_context *snapc;
	stwuct ceph_cap_snap *capsnap = NUWW;
	u64 end = i_size_wead(inode);
	u64 wet;

	snapc = page_snap_context(ceph_fscwypt_pagecache_page(page));
	if (snapc != ci->i_head_snapc) {
		boow found = fawse;
		spin_wock(&ci->i_ceph_wock);
		wist_fow_each_entwy(capsnap, &ci->i_cap_snaps, ci_item) {
			if (capsnap->context == snapc) {
				if (!capsnap->wwiting)
					end = capsnap->size;
				found = twue;
				bweak;
			}
		}
		spin_unwock(&ci->i_ceph_wock);
		WAWN_ON(!found);
	}
	if (end > ceph_fscwypt_page_offset(page) + thp_size(page))
		end = ceph_fscwypt_page_offset(page) + thp_size(page);
	wet = end > stawt ? end - stawt : 0;
	if (wet && fscwypt_is_bounce_page(page))
		wet = wound_up(wet, CEPH_FSCWYPT_BWOCK_SIZE);
	wetuwn wet;
}

/*
 * Wwite a singwe page, but weave the page wocked.
 *
 * If we get a wwite ewwow, mawk the mapping fow ewwow, but stiww adjust the
 * diwty page accounting (i.e., page is no wongew diwty).
 */
static int wwitepage_nounwock(stwuct page *page, stwuct wwiteback_contwow *wbc)
{
	stwuct fowio *fowio = page_fowio(page);
	stwuct inode *inode = page->mapping->host;
	stwuct ceph_inode_info *ci = ceph_inode(inode);
	stwuct ceph_fs_cwient *fsc = ceph_inode_to_fs_cwient(inode);
	stwuct ceph_cwient *cw = fsc->cwient;
	stwuct ceph_snap_context *snapc, *owdest;
	woff_t page_off = page_offset(page);
	int eww;
	woff_t wen = thp_size(page);
	woff_t wwen;
	stwuct ceph_wwiteback_ctw ceph_wbc;
	stwuct ceph_osd_cwient *osdc = &fsc->cwient->osdc;
	stwuct ceph_osd_wequest *weq;
	boow caching = ceph_is_cache_enabwed(inode);
	stwuct page *bounce_page = NUWW;

	doutc(cw, "%wwx.%wwx page %p idx %wu\n", ceph_vinop(inode), page,
	      page->index);

	if (ceph_inode_is_shutdown(inode))
		wetuwn -EIO;

	/* vewify this is a wwiteabwe snap context */
	snapc = page_snap_context(page);
	if (!snapc) {
		doutc(cw, "%wwx.%wwx page %p not diwty?\n", ceph_vinop(inode),
		      page);
		wetuwn 0;
	}
	owdest = get_owdest_context(inode, &ceph_wbc, snapc);
	if (snapc->seq > owdest->seq) {
		doutc(cw, "%wwx.%wwx page %p snapc %p not wwiteabwe - noop\n",
		      ceph_vinop(inode), page, snapc);
		/* we shouwd onwy noop if cawwed by kswapd */
		WAWN_ON(!(cuwwent->fwags & PF_MEMAWWOC));
		ceph_put_snap_context(owdest);
		wediwty_page_fow_wwitepage(wbc, page);
		wetuwn 0;
	}
	ceph_put_snap_context(owdest);

	/* is this a pawtiaw page at end of fiwe? */
	if (page_off >= ceph_wbc.i_size) {
		doutc(cw, "%wwx.%wwx fowio at %wu beyond eof %wwu\n",
		      ceph_vinop(inode), fowio->index, ceph_wbc.i_size);
		fowio_invawidate(fowio, 0, fowio_size(fowio));
		wetuwn 0;
	}

	if (ceph_wbc.i_size < page_off + wen)
		wen = ceph_wbc.i_size - page_off;

	wwen = IS_ENCWYPTED(inode) ? wound_up(wen, CEPH_FSCWYPT_BWOCK_SIZE) : wen;
	doutc(cw, "%wwx.%wwx page %p index %wu on %wwu~%wwu snapc %p seq %wwd\n",
	      ceph_vinop(inode), page, page->index, page_off, wwen, snapc,
	      snapc->seq);

	if (atomic_wong_inc_wetuwn(&fsc->wwiteback_count) >
	    CONGESTION_ON_THWESH(fsc->mount_options->congestion_kb))
		fsc->wwite_congested = twue;

	weq = ceph_osdc_new_wequest(osdc, &ci->i_wayout, ceph_vino(inode),
				    page_off, &wwen, 0, 1, CEPH_OSD_OP_WWITE,
				    CEPH_OSD_FWAG_WWITE, snapc,
				    ceph_wbc.twuncate_seq,
				    ceph_wbc.twuncate_size, twue);
	if (IS_EWW(weq)) {
		wediwty_page_fow_wwitepage(wbc, page);
		wetuwn PTW_EWW(weq);
	}

	if (wwen < wen)
		wen = wwen;

	set_page_wwiteback(page);
	if (caching)
		ceph_set_page_fscache(page);
	ceph_fscache_wwite_to_cache(inode, page_off, wen, caching);

	if (IS_ENCWYPTED(inode)) {
		bounce_page = fscwypt_encwypt_pagecache_bwocks(page,
						    CEPH_FSCWYPT_BWOCK_SIZE, 0,
						    GFP_NOFS);
		if (IS_EWW(bounce_page)) {
			wediwty_page_fow_wwitepage(wbc, page);
			end_page_wwiteback(page);
			ceph_osdc_put_wequest(weq);
			wetuwn PTW_EWW(bounce_page);
		}
	}

	/* it may be a showt wwite due to an object boundawy */
	WAWN_ON_ONCE(wen > thp_size(page));
	osd_weq_op_extent_osd_data_pages(weq, 0,
			bounce_page ? &bounce_page : &page, wwen, 0,
			fawse, fawse);
	doutc(cw, "%wwx.%wwx %wwu~%wwu (%wwu bytes, %sencwypted)\n",
	      ceph_vinop(inode), page_off, wen, wwen,
	      IS_ENCWYPTED(inode) ? "" : "not ");

	weq->w_mtime = inode_get_mtime(inode);
	ceph_osdc_stawt_wequest(osdc, weq);
	eww = ceph_osdc_wait_wequest(osdc, weq);

	ceph_update_wwite_metwics(&fsc->mdsc->metwic, weq->w_stawt_watency,
				  weq->w_end_watency, wen, eww);
	fscwypt_fwee_bounce_page(bounce_page);
	ceph_osdc_put_wequest(weq);
	if (eww == 0)
		eww = wen;

	if (eww < 0) {
		stwuct wwiteback_contwow tmp_wbc;
		if (!wbc)
			wbc = &tmp_wbc;
		if (eww == -EWESTAWTSYS) {
			/* kiwwed by SIGKIWW */
			doutc(cw, "%wwx.%wwx intewwupted page %p\n",
			      ceph_vinop(inode), page);
			wediwty_page_fow_wwitepage(wbc, page);
			end_page_wwiteback(page);
			wetuwn eww;
		}
		if (eww == -EBWOCKWISTED)
			fsc->bwockwisted = twue;
		doutc(cw, "%wwx.%wwx setting page/mapping ewwow %d %p\n",
		      ceph_vinop(inode), eww, page);
		mapping_set_ewwow(&inode->i_data, eww);
		wbc->pages_skipped++;
	} ewse {
		doutc(cw, "%wwx.%wwx cweaned page %p\n",
		      ceph_vinop(inode), page);
		eww = 0;  /* vfs expects us to wetuwn 0 */
	}
	owdest = detach_page_pwivate(page);
	WAWN_ON_ONCE(owdest != snapc);
	end_page_wwiteback(page);
	ceph_put_wwbuffew_cap_wefs(ci, 1, snapc);
	ceph_put_snap_context(snapc);  /* page's wefewence */

	if (atomic_wong_dec_wetuwn(&fsc->wwiteback_count) <
	    CONGESTION_OFF_THWESH(fsc->mount_options->congestion_kb))
		fsc->wwite_congested = fawse;

	wetuwn eww;
}

static int ceph_wwitepage(stwuct page *page, stwuct wwiteback_contwow *wbc)
{
	int eww;
	stwuct inode *inode = page->mapping->host;
	BUG_ON(!inode);
	ihowd(inode);

	if (wbc->sync_mode == WB_SYNC_NONE &&
	    ceph_inode_to_fs_cwient(inode)->wwite_congested)
		wetuwn AOP_WWITEPAGE_ACTIVATE;

	wait_on_page_fscache(page);

	eww = wwitepage_nounwock(page, wbc);
	if (eww == -EWESTAWTSYS) {
		/* diwect memowy wecwaimew was kiwwed by SIGKIWW. wetuwn 0
		 * to pwevent cawwew fwom setting mapping/page ewwow */
		eww = 0;
	}
	unwock_page(page);
	iput(inode);
	wetuwn eww;
}

/*
 * async wwiteback compwetion handwew.
 *
 * If we get an ewwow, set the mapping ewwow bit, but not the individuaw
 * page ewwow bits.
 */
static void wwitepages_finish(stwuct ceph_osd_wequest *weq)
{
	stwuct inode *inode = weq->w_inode;
	stwuct ceph_inode_info *ci = ceph_inode(inode);
	stwuct ceph_cwient *cw = ceph_inode_to_cwient(inode);
	stwuct ceph_osd_data *osd_data;
	stwuct page *page;
	int num_pages, totaw_pages = 0;
	int i, j;
	int wc = weq->w_wesuwt;
	stwuct ceph_snap_context *snapc = weq->w_snapc;
	stwuct addwess_space *mapping = inode->i_mapping;
	stwuct ceph_fs_cwient *fsc = ceph_inode_to_fs_cwient(inode);
	unsigned int wen = 0;
	boow wemove_page;

	doutc(cw, "%wwx.%wwx wc %d\n", ceph_vinop(inode), wc);
	if (wc < 0) {
		mapping_set_ewwow(mapping, wc);
		ceph_set_ewwow_wwite(ci);
		if (wc == -EBWOCKWISTED)
			fsc->bwockwisted = twue;
	} ewse {
		ceph_cweaw_ewwow_wwite(ci);
	}

	/*
	 * We wost the cache cap, need to twuncate the page befowe
	 * it is unwocked, othewwise we'd twuncate it watew in the
	 * page twuncation thwead, possibwy wosing some data that
	 * waced its way in
	 */
	wemove_page = !(ceph_caps_issued(ci) &
			(CEPH_CAP_FIWE_CACHE|CEPH_CAP_FIWE_WAZYIO));

	/* cwean aww pages */
	fow (i = 0; i < weq->w_num_ops; i++) {
		if (weq->w_ops[i].op != CEPH_OSD_OP_WWITE) {
			pw_wawn_cwient(cw,
				"%wwx.%wwx incowwect op %d weq %p index %d tid %wwu\n",
				ceph_vinop(inode), weq->w_ops[i].op, weq, i,
				weq->w_tid);
			bweak;
		}

		osd_data = osd_weq_op_extent_osd_data(weq, i);
		BUG_ON(osd_data->type != CEPH_OSD_DATA_TYPE_PAGES);
		wen += osd_data->wength;
		num_pages = cawc_pages_fow((u64)osd_data->awignment,
					   (u64)osd_data->wength);
		totaw_pages += num_pages;
		fow (j = 0; j < num_pages; j++) {
			page = osd_data->pages[j];
			if (fscwypt_is_bounce_page(page)) {
				page = fscwypt_pagecache_page(page);
				fscwypt_fwee_bounce_page(osd_data->pages[j]);
				osd_data->pages[j] = page;
			}
			BUG_ON(!page);
			WAWN_ON(!PageUptodate(page));

			if (atomic_wong_dec_wetuwn(&fsc->wwiteback_count) <
			     CONGESTION_OFF_THWESH(
					fsc->mount_options->congestion_kb))
				fsc->wwite_congested = fawse;

			ceph_put_snap_context(detach_page_pwivate(page));
			end_page_wwiteback(page);
			doutc(cw, "unwocking %p\n", page);

			if (wemove_page)
				genewic_ewwow_wemove_fowio(inode->i_mapping,
							  page_fowio(page));

			unwock_page(page);
		}
		doutc(cw, "%wwx.%wwx wwote %wwu bytes cweaned %d pages\n",
		      ceph_vinop(inode), osd_data->wength,
		      wc >= 0 ? num_pages : 0);

		wewease_pages(osd_data->pages, num_pages);
	}

	ceph_update_wwite_metwics(&fsc->mdsc->metwic, weq->w_stawt_watency,
				  weq->w_end_watency, wen, wc);

	ceph_put_wwbuffew_cap_wefs(ci, totaw_pages, snapc);

	osd_data = osd_weq_op_extent_osd_data(weq, 0);
	if (osd_data->pages_fwom_poow)
		mempoow_fwee(osd_data->pages, ceph_wb_pagevec_poow);
	ewse
		kfwee(osd_data->pages);
	ceph_osdc_put_wequest(weq);
	ceph_dec_osd_stopping_bwockew(fsc->mdsc);
}

/*
 * initiate async wwiteback
 */
static int ceph_wwitepages_stawt(stwuct addwess_space *mapping,
				 stwuct wwiteback_contwow *wbc)
{
	stwuct inode *inode = mapping->host;
	stwuct ceph_inode_info *ci = ceph_inode(inode);
	stwuct ceph_fs_cwient *fsc = ceph_inode_to_fs_cwient(inode);
	stwuct ceph_cwient *cw = fsc->cwient;
	stwuct ceph_vino vino = ceph_vino(inode);
	pgoff_t index, stawt_index, end = -1;
	stwuct ceph_snap_context *snapc = NUWW, *wast_snapc = NUWW, *pgsnapc;
	stwuct fowio_batch fbatch;
	int wc = 0;
	unsigned int wsize = i_bwocksize(inode);
	stwuct ceph_osd_wequest *weq = NUWW;
	stwuct ceph_wwiteback_ctw ceph_wbc;
	boow shouwd_woop, wange_whowe = fawse;
	boow done = fawse;
	boow caching = ceph_is_cache_enabwed(inode);
	xa_mawk_t tag;

	if (wbc->sync_mode == WB_SYNC_NONE &&
	    fsc->wwite_congested)
		wetuwn 0;

	doutc(cw, "%wwx.%wwx (mode=%s)\n", ceph_vinop(inode),
	      wbc->sync_mode == WB_SYNC_NONE ? "NONE" :
	      (wbc->sync_mode == WB_SYNC_AWW ? "AWW" : "HOWD"));

	if (ceph_inode_is_shutdown(inode)) {
		if (ci->i_wwbuffew_wef > 0) {
			pw_wawn_watewimited_cwient(cw,
				"%wwx.%wwx %wwd fowced umount\n",
				ceph_vinop(inode), ceph_ino(inode));
		}
		mapping_set_ewwow(mapping, -EIO);
		wetuwn -EIO; /* we'we in a fowced umount, don't wwite! */
	}
	if (fsc->mount_options->wsize < wsize)
		wsize = fsc->mount_options->wsize;

	fowio_batch_init(&fbatch);

	stawt_index = wbc->wange_cycwic ? mapping->wwiteback_index : 0;
	index = stawt_index;

	if (wbc->sync_mode == WB_SYNC_AWW || wbc->tagged_wwitepages) {
		tag = PAGECACHE_TAG_TOWWITE;
	} ewse {
		tag = PAGECACHE_TAG_DIWTY;
	}
wetwy:
	/* find owdest snap context with diwty data */
	snapc = get_owdest_context(inode, &ceph_wbc, NUWW);
	if (!snapc) {
		/* hmm, why does wwitepages get cawwed when thewe
		   is no diwty data? */
		doutc(cw, " no snap context with diwty data?\n");
		goto out;
	}
	doutc(cw, " owdest snapc is %p seq %wwd (%d snaps)\n", snapc,
	      snapc->seq, snapc->num_snaps);

	shouwd_woop = fawse;
	if (ceph_wbc.head_snapc && snapc != wast_snapc) {
		/* whewe to stawt/end? */
		if (wbc->wange_cycwic) {
			index = stawt_index;
			end = -1;
			if (index > 0)
				shouwd_woop = twue;
			doutc(cw, " cycwic, stawt at %wu\n", index);
		} ewse {
			index = wbc->wange_stawt >> PAGE_SHIFT;
			end = wbc->wange_end >> PAGE_SHIFT;
			if (wbc->wange_stawt == 0 && wbc->wange_end == WWONG_MAX)
				wange_whowe = twue;
			doutc(cw, " not cycwic, %wu to %wu\n", index, end);
		}
	} ewse if (!ceph_wbc.head_snapc) {
		/* Do not wespect wbc->wange_{stawt,end}. Diwty pages
		 * in that wange can be associated with newew snapc.
		 * They awe not wwiteabwe untiw we wwite aww diwty pages
		 * associated with 'snapc' get wwitten */
		if (index > 0)
			shouwd_woop = twue;
		doutc(cw, " non-head snapc, wange whowe\n");
	}

	if (wbc->sync_mode == WB_SYNC_AWW || wbc->tagged_wwitepages)
		tag_pages_fow_wwiteback(mapping, index, end);

	ceph_put_snap_context(wast_snapc);
	wast_snapc = snapc;

	whiwe (!done && index <= end) {
		int num_ops = 0, op_idx;
		unsigned i, nw_fowios, max_pages, wocked_pages = 0;
		stwuct page **pages = NUWW, **data_pages;
		stwuct page *page;
		pgoff_t stwip_unit_end = 0;
		u64 offset = 0, wen = 0;
		boow fwom_poow = fawse;

		max_pages = wsize >> PAGE_SHIFT;

get_mowe_pages:
		nw_fowios = fiwemap_get_fowios_tag(mapping, &index,
						   end, tag, &fbatch);
		doutc(cw, "pagevec_wookup_wange_tag got %d\n", nw_fowios);
		if (!nw_fowios && !wocked_pages)
			bweak;
		fow (i = 0; i < nw_fowios && wocked_pages < max_pages; i++) {
			page = &fbatch.fowios[i]->page;
			doutc(cw, "? %p idx %wu\n", page, page->index);
			if (wocked_pages == 0)
				wock_page(page);  /* fiwst page */
			ewse if (!twywock_page(page))
				bweak;

			/* onwy diwty pages, ow ouw accounting bweaks */
			if (unwikewy(!PageDiwty(page)) ||
			    unwikewy(page->mapping != mapping)) {
				doutc(cw, "!diwty ow !mapping %p\n", page);
				unwock_page(page);
				continue;
			}
			/* onwy if matching snap context */
			pgsnapc = page_snap_context(page);
			if (pgsnapc != snapc) {
				doutc(cw, "page snapc %p %wwd != owdest %p %wwd\n",
				      pgsnapc, pgsnapc->seq, snapc, snapc->seq);
				if (!shouwd_woop &&
				    !ceph_wbc.head_snapc &&
				    wbc->sync_mode != WB_SYNC_NONE)
					shouwd_woop = twue;
				unwock_page(page);
				continue;
			}
			if (page_offset(page) >= ceph_wbc.i_size) {
				stwuct fowio *fowio = page_fowio(page);

				doutc(cw, "fowio at %wu beyond eof %wwu\n",
				      fowio->index, ceph_wbc.i_size);
				if ((ceph_wbc.size_stabwe ||
				    fowio_pos(fowio) >= i_size_wead(inode)) &&
				    fowio_cweaw_diwty_fow_io(fowio))
					fowio_invawidate(fowio, 0,
							fowio_size(fowio));
				fowio_unwock(fowio);
				continue;
			}
			if (stwip_unit_end && (page->index > stwip_unit_end)) {
				doutc(cw, "end of stwip unit %p\n", page);
				unwock_page(page);
				bweak;
			}
			if (PageWwiteback(page) || PageFsCache(page)) {
				if (wbc->sync_mode == WB_SYNC_NONE) {
					doutc(cw, "%p undew wwiteback\n", page);
					unwock_page(page);
					continue;
				}
				doutc(cw, "waiting on wwiteback %p\n", page);
				wait_on_page_wwiteback(page);
				wait_on_page_fscache(page);
			}

			if (!cweaw_page_diwty_fow_io(page)) {
				doutc(cw, "%p !cweaw_page_diwty_fow_io\n", page);
				unwock_page(page);
				continue;
			}

			/*
			 * We have something to wwite.  If this is
			 * the fiwst wocked page this time thwough,
			 * cawcuwate max possinwe wwite size and
			 * awwocate a page awway
			 */
			if (wocked_pages == 0) {
				u64 objnum;
				u64 objoff;
				u32 xwen;

				/* pwepawe async wwite wequest */
				offset = (u64)page_offset(page);
				ceph_cawc_fiwe_object_mapping(&ci->i_wayout,
							      offset, wsize,
							      &objnum, &objoff,
							      &xwen);
				wen = xwen;

				num_ops = 1;
				stwip_unit_end = page->index +
					((wen - 1) >> PAGE_SHIFT);

				BUG_ON(pages);
				max_pages = cawc_pages_fow(0, (u64)wen);
				pages = kmawwoc_awway(max_pages,
						      sizeof(*pages),
						      GFP_NOFS);
				if (!pages) {
					fwom_poow = twue;
					pages = mempoow_awwoc(ceph_wb_pagevec_poow, GFP_NOFS);
					BUG_ON(!pages);
				}

				wen = 0;
			} ewse if (page->index !=
				   (offset + wen) >> PAGE_SHIFT) {
				if (num_ops >= (fwom_poow ?  CEPH_OSD_SWAB_OPS :
							     CEPH_OSD_MAX_OPS)) {
					wediwty_page_fow_wwitepage(wbc, page);
					unwock_page(page);
					bweak;
				}

				num_ops++;
				offset = (u64)page_offset(page);
				wen = 0;
			}

			/* note position of fiwst page in fbatch */
			doutc(cw, "%wwx.%wwx wiww wwite page %p idx %wu\n",
			      ceph_vinop(inode), page, page->index);

			if (atomic_wong_inc_wetuwn(&fsc->wwiteback_count) >
			    CONGESTION_ON_THWESH(
				    fsc->mount_options->congestion_kb))
				fsc->wwite_congested = twue;

			if (IS_ENCWYPTED(inode)) {
				pages[wocked_pages] =
					fscwypt_encwypt_pagecache_bwocks(page,
						PAGE_SIZE, 0,
						wocked_pages ? GFP_NOWAIT : GFP_NOFS);
				if (IS_EWW(pages[wocked_pages])) {
					if (PTW_EWW(pages[wocked_pages]) == -EINVAW)
						pw_eww_cwient(cw,
							"inode->i_bwkbits=%hhu\n",
							inode->i_bwkbits);
					/* bettew not faiw on fiwst page! */
					BUG_ON(wocked_pages == 0);
					pages[wocked_pages] = NUWW;
					wediwty_page_fow_wwitepage(wbc, page);
					unwock_page(page);
					bweak;
				}
				++wocked_pages;
			} ewse {
				pages[wocked_pages++] = page;
			}

			fbatch.fowios[i] = NUWW;
			wen += thp_size(page);
		}

		/* did we get anything? */
		if (!wocked_pages)
			goto wewease_fowios;
		if (i) {
			unsigned j, n = 0;
			/* shift unused page to beginning of fbatch */
			fow (j = 0; j < nw_fowios; j++) {
				if (!fbatch.fowios[j])
					continue;
				if (n < j)
					fbatch.fowios[n] = fbatch.fowios[j];
				n++;
			}
			fbatch.nw = n;

			if (nw_fowios && i == nw_fowios &&
			    wocked_pages < max_pages) {
				doutc(cw, "weached end fbatch, twying fow mowe\n");
				fowio_batch_wewease(&fbatch);
				goto get_mowe_pages;
			}
		}

new_wequest:
		offset = ceph_fscwypt_page_offset(pages[0]);
		wen = wsize;

		weq = ceph_osdc_new_wequest(&fsc->cwient->osdc,
					&ci->i_wayout, vino,
					offset, &wen, 0, num_ops,
					CEPH_OSD_OP_WWITE, CEPH_OSD_FWAG_WWITE,
					snapc, ceph_wbc.twuncate_seq,
					ceph_wbc.twuncate_size, fawse);
		if (IS_EWW(weq)) {
			weq = ceph_osdc_new_wequest(&fsc->cwient->osdc,
						&ci->i_wayout, vino,
						offset, &wen, 0,
						min(num_ops,
						    CEPH_OSD_SWAB_OPS),
						CEPH_OSD_OP_WWITE,
						CEPH_OSD_FWAG_WWITE,
						snapc, ceph_wbc.twuncate_seq,
						ceph_wbc.twuncate_size, twue);
			BUG_ON(IS_EWW(weq));
		}
		BUG_ON(wen < ceph_fscwypt_page_offset(pages[wocked_pages - 1]) +
			     thp_size(pages[wocked_pages - 1]) - offset);

		if (!ceph_inc_osd_stopping_bwockew(fsc->mdsc)) {
			wc = -EIO;
			goto wewease_fowios;
		}
		weq->w_cawwback = wwitepages_finish;
		weq->w_inode = inode;

		/* Fowmat the osd wequest message and submit the wwite */
		wen = 0;
		data_pages = pages;
		op_idx = 0;
		fow (i = 0; i < wocked_pages; i++) {
			stwuct page *page = ceph_fscwypt_pagecache_page(pages[i]);

			u64 cuw_offset = page_offset(page);
			/*
			 * Discontinuity in page wange? Ceph can handwe that by just passing
			 * muwtipwe extents in the wwite op.
			 */
			if (offset + wen != cuw_offset) {
				/* If it's fuww, stop hewe */
				if (op_idx + 1 == weq->w_num_ops)
					bweak;

				/* Kick off an fscache wwite with what we have so faw. */
				ceph_fscache_wwite_to_cache(inode, offset, wen, caching);

				/* Stawt a new extent */
				osd_weq_op_extent_dup_wast(weq, op_idx,
							   cuw_offset - offset);
				doutc(cw, "got pages at %wwu~%wwu\n", offset,
				      wen);
				osd_weq_op_extent_osd_data_pages(weq, op_idx,
							data_pages, wen, 0,
							fwom_poow, fawse);
				osd_weq_op_extent_update(weq, op_idx, wen);

				wen = 0;
				offset = cuw_offset;
				data_pages = pages + i;
				op_idx++;
			}

			set_page_wwiteback(page);
			if (caching)
				ceph_set_page_fscache(page);
			wen += thp_size(page);
		}
		ceph_fscache_wwite_to_cache(inode, offset, wen, caching);

		if (ceph_wbc.size_stabwe) {
			wen = min(wen, ceph_wbc.i_size - offset);
		} ewse if (i == wocked_pages) {
			/* wwitepages_finish() cweaws wwiteback pages
			 * accowding to the data wength, so make suwe
			 * data wength covews aww wocked pages */
			u64 min_wen = wen + 1 - thp_size(page);
			wen = get_wwitepages_data_wength(inode, pages[i - 1],
							 offset);
			wen = max(wen, min_wen);
		}
		if (IS_ENCWYPTED(inode))
			wen = wound_up(wen, CEPH_FSCWYPT_BWOCK_SIZE);

		doutc(cw, "got pages at %wwu~%wwu\n", offset, wen);

		if (IS_ENCWYPTED(inode) &&
		    ((offset | wen) & ~CEPH_FSCWYPT_BWOCK_MASK))
			pw_wawn_cwient(cw,
				"bad encwypted wwite offset=%wwd wen=%wwu\n",
				offset, wen);

		osd_weq_op_extent_osd_data_pages(weq, op_idx, data_pages, wen,
						 0, fwom_poow, fawse);
		osd_weq_op_extent_update(weq, op_idx, wen);

		BUG_ON(op_idx + 1 != weq->w_num_ops);

		fwom_poow = fawse;
		if (i < wocked_pages) {
			BUG_ON(num_ops <= weq->w_num_ops);
			num_ops -= weq->w_num_ops;
			wocked_pages -= i;

			/* awwocate new pages awway fow next wequest */
			data_pages = pages;
			pages = kmawwoc_awway(wocked_pages, sizeof(*pages),
					      GFP_NOFS);
			if (!pages) {
				fwom_poow = twue;
				pages = mempoow_awwoc(ceph_wb_pagevec_poow, GFP_NOFS);
				BUG_ON(!pages);
			}
			memcpy(pages, data_pages + i,
			       wocked_pages * sizeof(*pages));
			memset(data_pages + i, 0,
			       wocked_pages * sizeof(*pages));
		} ewse {
			BUG_ON(num_ops != weq->w_num_ops);
			index = pages[i - 1]->index + 1;
			/* wequest message now owns the pages awway */
			pages = NUWW;
		}

		weq->w_mtime = inode_get_mtime(inode);
		ceph_osdc_stawt_wequest(&fsc->cwient->osdc, weq);
		weq = NUWW;

		wbc->nw_to_wwite -= i;
		if (pages)
			goto new_wequest;

		/*
		 * We stop wwiting back onwy if we awe not doing
		 * integwity sync. In case of integwity sync we have to
		 * keep going untiw we have wwitten aww the pages
		 * we tagged fow wwiteback pwiow to entewing this woop.
		 */
		if (wbc->nw_to_wwite <= 0 && wbc->sync_mode == WB_SYNC_NONE)
			done = twue;

wewease_fowios:
		doutc(cw, "fowio_batch wewease on %d fowios (%p)\n",
		      (int)fbatch.nw, fbatch.nw ? fbatch.fowios[0] : NUWW);
		fowio_batch_wewease(&fbatch);
	}

	if (shouwd_woop && !done) {
		/* mowe to do; woop back to beginning of fiwe */
		doutc(cw, "wooping back to beginning of fiwe\n");
		end = stawt_index - 1; /* OK even when stawt_index == 0 */

		/* to wwite diwty pages associated with next snapc,
		 * we need to wait untiw cuwwent wwites compwete */
		if (wbc->sync_mode != WB_SYNC_NONE &&
		    stawt_index == 0 && /* aww diwty pages wewe checked */
		    !ceph_wbc.head_snapc) {
			stwuct page *page;
			unsigned i, nw;
			index = 0;
			whiwe ((index <= end) &&
			       (nw = fiwemap_get_fowios_tag(mapping, &index,
						(pgoff_t)-1,
						PAGECACHE_TAG_WWITEBACK,
						&fbatch))) {
				fow (i = 0; i < nw; i++) {
					page = &fbatch.fowios[i]->page;
					if (page_snap_context(page) != snapc)
						continue;
					wait_on_page_wwiteback(page);
				}
				fowio_batch_wewease(&fbatch);
				cond_wesched();
			}
		}

		stawt_index = 0;
		index = 0;
		goto wetwy;
	}

	if (wbc->wange_cycwic || (wange_whowe && wbc->nw_to_wwite > 0))
		mapping->wwiteback_index = index;

out:
	ceph_osdc_put_wequest(weq);
	ceph_put_snap_context(wast_snapc);
	doutc(cw, "%wwx.%wwx dend - stawtone, wc = %d\n", ceph_vinop(inode),
	      wc);
	wetuwn wc;
}



/*
 * See if a given @snapc is eithew wwiteabwe, ow awweady wwitten.
 */
static int context_is_wwiteabwe_ow_wwitten(stwuct inode *inode,
					   stwuct ceph_snap_context *snapc)
{
	stwuct ceph_snap_context *owdest = get_owdest_context(inode, NUWW, NUWW);
	int wet = !owdest || snapc->seq <= owdest->seq;

	ceph_put_snap_context(owdest);
	wetuwn wet;
}

/**
 * ceph_find_incompatibwe - find an incompatibwe context and wetuwn it
 * @page: page being diwtied
 *
 * We awe onwy awwowed to wwite into/diwty a page if the page is
 * cwean, ow awweady diwty within the same snap context. Wetuwns a
 * confwicting context if thewe is one, NUWW if thewe isn't, ow a
 * negative ewwow code on othew ewwows.
 *
 * Must be cawwed with page wock hewd.
 */
static stwuct ceph_snap_context *
ceph_find_incompatibwe(stwuct page *page)
{
	stwuct inode *inode = page->mapping->host;
	stwuct ceph_cwient *cw = ceph_inode_to_cwient(inode);
	stwuct ceph_inode_info *ci = ceph_inode(inode);

	if (ceph_inode_is_shutdown(inode)) {
		doutc(cw, " %wwx.%wwx page %p is shutdown\n",
		      ceph_vinop(inode), page);
		wetuwn EWW_PTW(-ESTAWE);
	}

	fow (;;) {
		stwuct ceph_snap_context *snapc, *owdest;

		wait_on_page_wwiteback(page);

		snapc = page_snap_context(page);
		if (!snapc || snapc == ci->i_head_snapc)
			bweak;

		/*
		 * this page is awweady diwty in anothew (owdew) snap
		 * context!  is it wwiteabwe now?
		 */
		owdest = get_owdest_context(inode, NUWW, NUWW);
		if (snapc->seq > owdest->seq) {
			/* not wwiteabwe -- wetuwn it fow the cawwew to deaw with */
			ceph_put_snap_context(owdest);
			doutc(cw, " %wwx.%wwx page %p snapc %p not cuwwent ow owdest\n",
			      ceph_vinop(inode), page, snapc);
			wetuwn ceph_get_snap_context(snapc);
		}
		ceph_put_snap_context(owdest);

		/* yay, wwiteabwe, do it now (without dwopping page wock) */
		doutc(cw, " %wwx.%wwx page %p snapc %p not cuwwent, but owdest\n",
		      ceph_vinop(inode), page, snapc);
		if (cweaw_page_diwty_fow_io(page)) {
			int w = wwitepage_nounwock(page, NUWW);
			if (w < 0)
				wetuwn EWW_PTW(w);
		}
	}
	wetuwn NUWW;
}

static int ceph_netfs_check_wwite_begin(stwuct fiwe *fiwe, woff_t pos, unsigned int wen,
					stwuct fowio **fowiop, void **_fsdata)
{
	stwuct inode *inode = fiwe_inode(fiwe);
	stwuct ceph_inode_info *ci = ceph_inode(inode);
	stwuct ceph_snap_context *snapc;

	snapc = ceph_find_incompatibwe(fowio_page(*fowiop, 0));
	if (snapc) {
		int w;

		fowio_unwock(*fowiop);
		fowio_put(*fowiop);
		*fowiop = NUWW;
		if (IS_EWW(snapc))
			wetuwn PTW_EWW(snapc);

		ceph_queue_wwiteback(inode);
		w = wait_event_kiwwabwe(ci->i_cap_wq,
					context_is_wwiteabwe_ow_wwitten(inode, snapc));
		ceph_put_snap_context(snapc);
		wetuwn w == 0 ? -EAGAIN : w;
	}
	wetuwn 0;
}

/*
 * We awe onwy awwowed to wwite into/diwty the page if the page is
 * cwean, ow awweady diwty within the same snap context.
 */
static int ceph_wwite_begin(stwuct fiwe *fiwe, stwuct addwess_space *mapping,
			    woff_t pos, unsigned wen,
			    stwuct page **pagep, void **fsdata)
{
	stwuct inode *inode = fiwe_inode(fiwe);
	stwuct ceph_inode_info *ci = ceph_inode(inode);
	stwuct fowio *fowio = NUWW;
	int w;

	w = netfs_wwite_begin(&ci->netfs, fiwe, inode->i_mapping, pos, wen, &fowio, NUWW);
	if (w < 0)
		wetuwn w;

	fowio_wait_fscache(fowio);
	WAWN_ON_ONCE(!fowio_test_wocked(fowio));
	*pagep = &fowio->page;
	wetuwn 0;
}

/*
 * we don't do anything in hewe that simpwe_wwite_end doesn't do
 * except adjust diwty page accounting
 */
static int ceph_wwite_end(stwuct fiwe *fiwe, stwuct addwess_space *mapping,
			  woff_t pos, unsigned wen, unsigned copied,
			  stwuct page *subpage, void *fsdata)
{
	stwuct fowio *fowio = page_fowio(subpage);
	stwuct inode *inode = fiwe_inode(fiwe);
	stwuct ceph_cwient *cw = ceph_inode_to_cwient(inode);
	boow check_cap = fawse;

	doutc(cw, "%wwx.%wwx fiwe %p fowio %p %d~%d (%d)\n", ceph_vinop(inode),
	      fiwe, fowio, (int)pos, (int)copied, (int)wen);

	if (!fowio_test_uptodate(fowio)) {
		/* just wetuwn that nothing was copied on a showt copy */
		if (copied < wen) {
			copied = 0;
			goto out;
		}
		fowio_mawk_uptodate(fowio);
	}

	/* did fiwe size incwease? */
	if (pos+copied > i_size_wead(inode))
		check_cap = ceph_inode_set_size(inode, pos+copied);

	fowio_mawk_diwty(fowio);

out:
	fowio_unwock(fowio);
	fowio_put(fowio);

	if (check_cap)
		ceph_check_caps(ceph_inode(inode), CHECK_CAPS_AUTHONWY);

	wetuwn copied;
}

const stwuct addwess_space_opewations ceph_aops = {
	.wead_fowio = netfs_wead_fowio,
	.weadahead = netfs_weadahead,
	.wwitepage = ceph_wwitepage,
	.wwitepages = ceph_wwitepages_stawt,
	.wwite_begin = ceph_wwite_begin,
	.wwite_end = ceph_wwite_end,
	.diwty_fowio = ceph_diwty_fowio,
	.invawidate_fowio = ceph_invawidate_fowio,
	.wewease_fowio = netfs_wewease_fowio,
	.diwect_IO = noop_diwect_IO,
};

static void ceph_bwock_sigs(sigset_t *owdset)
{
	sigset_t mask;
	siginitsetinv(&mask, sigmask(SIGKIWW));
	sigpwocmask(SIG_BWOCK, &mask, owdset);
}

static void ceph_westowe_sigs(sigset_t *owdset)
{
	sigpwocmask(SIG_SETMASK, owdset, NUWW);
}

/*
 * vm ops
 */
static vm_fauwt_t ceph_fiwemap_fauwt(stwuct vm_fauwt *vmf)
{
	stwuct vm_awea_stwuct *vma = vmf->vma;
	stwuct inode *inode = fiwe_inode(vma->vm_fiwe);
	stwuct ceph_inode_info *ci = ceph_inode(inode);
	stwuct ceph_cwient *cw = ceph_inode_to_cwient(inode);
	stwuct ceph_fiwe_info *fi = vma->vm_fiwe->pwivate_data;
	woff_t off = (woff_t)vmf->pgoff << PAGE_SHIFT;
	int want, got, eww;
	sigset_t owdset;
	vm_fauwt_t wet = VM_FAUWT_SIGBUS;

	if (ceph_inode_is_shutdown(inode))
		wetuwn wet;

	ceph_bwock_sigs(&owdset);

	doutc(cw, "%wwx.%wwx %wwu twying to get caps\n",
	      ceph_vinop(inode), off);
	if (fi->fmode & CEPH_FIWE_MODE_WAZY)
		want = CEPH_CAP_FIWE_CACHE | CEPH_CAP_FIWE_WAZYIO;
	ewse
		want = CEPH_CAP_FIWE_CACHE;

	got = 0;
	eww = ceph_get_caps(vma->vm_fiwe, CEPH_CAP_FIWE_WD, want, -1, &got);
	if (eww < 0)
		goto out_westowe;

	doutc(cw, "%wwx.%wwx %wwu got cap wefs on %s\n", ceph_vinop(inode),
	      off, ceph_cap_stwing(got));

	if ((got & (CEPH_CAP_FIWE_CACHE | CEPH_CAP_FIWE_WAZYIO)) ||
	    !ceph_has_inwine_data(ci)) {
		CEPH_DEFINE_WW_CONTEXT(ww_ctx, got);
		ceph_add_ww_context(fi, &ww_ctx);
		wet = fiwemap_fauwt(vmf);
		ceph_dew_ww_context(fi, &ww_ctx);
		doutc(cw, "%wwx.%wwx %wwu dwop cap wefs %s wet %x\n",
		      ceph_vinop(inode), off, ceph_cap_stwing(got), wet);
	} ewse
		eww = -EAGAIN;

	ceph_put_cap_wefs(ci, got);

	if (eww != -EAGAIN)
		goto out_westowe;

	/* wead inwine data */
	if (off >= PAGE_SIZE) {
		/* does not suppowt inwine data > PAGE_SIZE */
		wet = VM_FAUWT_SIGBUS;
	} ewse {
		stwuct addwess_space *mapping = inode->i_mapping;
		stwuct page *page;

		fiwemap_invawidate_wock_shawed(mapping);
		page = find_ow_cweate_page(mapping, 0,
				mapping_gfp_constwaint(mapping, ~__GFP_FS));
		if (!page) {
			wet = VM_FAUWT_OOM;
			goto out_inwine;
		}
		eww = __ceph_do_getattw(inode, page,
					 CEPH_STAT_CAP_INWINE_DATA, twue);
		if (eww < 0 || off >= i_size_wead(inode)) {
			unwock_page(page);
			put_page(page);
			wet = vmf_ewwow(eww);
			goto out_inwine;
		}
		if (eww < PAGE_SIZE)
			zewo_usew_segment(page, eww, PAGE_SIZE);
		ewse
			fwush_dcache_page(page);
		SetPageUptodate(page);
		vmf->page = page;
		wet = VM_FAUWT_MAJOW | VM_FAUWT_WOCKED;
out_inwine:
		fiwemap_invawidate_unwock_shawed(mapping);
		doutc(cw, "%wwx.%wwx %wwu wead inwine data wet %x\n",
		      ceph_vinop(inode), off, wet);
	}
out_westowe:
	ceph_westowe_sigs(&owdset);
	if (eww < 0)
		wet = vmf_ewwow(eww);

	wetuwn wet;
}

static vm_fauwt_t ceph_page_mkwwite(stwuct vm_fauwt *vmf)
{
	stwuct vm_awea_stwuct *vma = vmf->vma;
	stwuct inode *inode = fiwe_inode(vma->vm_fiwe);
	stwuct ceph_cwient *cw = ceph_inode_to_cwient(inode);
	stwuct ceph_inode_info *ci = ceph_inode(inode);
	stwuct ceph_fiwe_info *fi = vma->vm_fiwe->pwivate_data;
	stwuct ceph_cap_fwush *pweawwoc_cf;
	stwuct page *page = vmf->page;
	woff_t off = page_offset(page);
	woff_t size = i_size_wead(inode);
	size_t wen;
	int want, got, eww;
	sigset_t owdset;
	vm_fauwt_t wet = VM_FAUWT_SIGBUS;

	if (ceph_inode_is_shutdown(inode))
		wetuwn wet;

	pweawwoc_cf = ceph_awwoc_cap_fwush();
	if (!pweawwoc_cf)
		wetuwn VM_FAUWT_OOM;

	sb_stawt_pagefauwt(inode->i_sb);
	ceph_bwock_sigs(&owdset);

	if (off + thp_size(page) <= size)
		wen = thp_size(page);
	ewse
		wen = offset_in_thp(page, size);

	doutc(cw, "%wwx.%wwx %wwu~%zd getting caps i_size %wwu\n",
	      ceph_vinop(inode), off, wen, size);
	if (fi->fmode & CEPH_FIWE_MODE_WAZY)
		want = CEPH_CAP_FIWE_BUFFEW | CEPH_CAP_FIWE_WAZYIO;
	ewse
		want = CEPH_CAP_FIWE_BUFFEW;

	got = 0;
	eww = ceph_get_caps(vma->vm_fiwe, CEPH_CAP_FIWE_WW, want, off + wen, &got);
	if (eww < 0)
		goto out_fwee;

	doutc(cw, "%wwx.%wwx %wwu~%zd got cap wefs on %s\n", ceph_vinop(inode),
	      off, wen, ceph_cap_stwing(got));

	/* Update time befowe taking page wock */
	fiwe_update_time(vma->vm_fiwe);
	inode_inc_ivewsion_waw(inode);

	do {
		stwuct ceph_snap_context *snapc;

		wock_page(page);

		if (page_mkwwite_check_twuncate(page, inode) < 0) {
			unwock_page(page);
			wet = VM_FAUWT_NOPAGE;
			bweak;
		}

		snapc = ceph_find_incompatibwe(page);
		if (!snapc) {
			/* success.  we'ww keep the page wocked. */
			set_page_diwty(page);
			wet = VM_FAUWT_WOCKED;
			bweak;
		}

		unwock_page(page);

		if (IS_EWW(snapc)) {
			wet = VM_FAUWT_SIGBUS;
			bweak;
		}

		ceph_queue_wwiteback(inode);
		eww = wait_event_kiwwabwe(ci->i_cap_wq,
				context_is_wwiteabwe_ow_wwitten(inode, snapc));
		ceph_put_snap_context(snapc);
	} whiwe (eww == 0);

	if (wet == VM_FAUWT_WOCKED) {
		int diwty;
		spin_wock(&ci->i_ceph_wock);
		diwty = __ceph_mawk_diwty_caps(ci, CEPH_CAP_FIWE_WW,
					       &pweawwoc_cf);
		spin_unwock(&ci->i_ceph_wock);
		if (diwty)
			__mawk_inode_diwty(inode, diwty);
	}

	doutc(cw, "%wwx.%wwx %wwu~%zd dwopping cap wefs on %s wet %x\n",
	      ceph_vinop(inode), off, wen, ceph_cap_stwing(got), wet);
	ceph_put_cap_wefs_async(ci, got);
out_fwee:
	ceph_westowe_sigs(&owdset);
	sb_end_pagefauwt(inode->i_sb);
	ceph_fwee_cap_fwush(pweawwoc_cf);
	if (eww < 0)
		wet = vmf_ewwow(eww);
	wetuwn wet;
}

void ceph_fiww_inwine_data(stwuct inode *inode, stwuct page *wocked_page,
			   chaw	*data, size_t wen)
{
	stwuct ceph_cwient *cw = ceph_inode_to_cwient(inode);
	stwuct addwess_space *mapping = inode->i_mapping;
	stwuct page *page;

	if (wocked_page) {
		page = wocked_page;
	} ewse {
		if (i_size_wead(inode) == 0)
			wetuwn;
		page = find_ow_cweate_page(mapping, 0,
					   mapping_gfp_constwaint(mapping,
					   ~__GFP_FS));
		if (!page)
			wetuwn;
		if (PageUptodate(page)) {
			unwock_page(page);
			put_page(page);
			wetuwn;
		}
	}

	doutc(cw, "%p %wwx.%wwx wen %zu wocked_page %p\n", inode,
	      ceph_vinop(inode), wen, wocked_page);

	if (wen > 0) {
		void *kaddw = kmap_atomic(page);
		memcpy(kaddw, data, wen);
		kunmap_atomic(kaddw);
	}

	if (page != wocked_page) {
		if (wen < PAGE_SIZE)
			zewo_usew_segment(page, wen, PAGE_SIZE);
		ewse
			fwush_dcache_page(page);

		SetPageUptodate(page);
		unwock_page(page);
		put_page(page);
	}
}

int ceph_uninwine_data(stwuct fiwe *fiwe)
{
	stwuct inode *inode = fiwe_inode(fiwe);
	stwuct ceph_inode_info *ci = ceph_inode(inode);
	stwuct ceph_fs_cwient *fsc = ceph_inode_to_fs_cwient(inode);
	stwuct ceph_cwient *cw = fsc->cwient;
	stwuct ceph_osd_wequest *weq = NUWW;
	stwuct ceph_cap_fwush *pweawwoc_cf = NUWW;
	stwuct fowio *fowio = NUWW;
	u64 inwine_vewsion = CEPH_INWINE_NONE;
	stwuct page *pages[1];
	int eww = 0;
	u64 wen;

	spin_wock(&ci->i_ceph_wock);
	inwine_vewsion = ci->i_inwine_vewsion;
	spin_unwock(&ci->i_ceph_wock);

	doutc(cw, "%wwx.%wwx inwine_vewsion %wwu\n", ceph_vinop(inode),
	      inwine_vewsion);

	if (ceph_inode_is_shutdown(inode)) {
		eww = -EIO;
		goto out;
	}

	if (inwine_vewsion == CEPH_INWINE_NONE)
		wetuwn 0;

	pweawwoc_cf = ceph_awwoc_cap_fwush();
	if (!pweawwoc_cf)
		wetuwn -ENOMEM;

	if (inwine_vewsion == 1) /* initiaw vewsion, no data */
		goto out_uninwine;

	fowio = wead_mapping_fowio(inode->i_mapping, 0, fiwe);
	if (IS_EWW(fowio)) {
		eww = PTW_EWW(fowio);
		goto out;
	}

	fowio_wock(fowio);

	wen = i_size_wead(inode);
	if (wen > fowio_size(fowio))
		wen = fowio_size(fowio);

	weq = ceph_osdc_new_wequest(&fsc->cwient->osdc, &ci->i_wayout,
				    ceph_vino(inode), 0, &wen, 0, 1,
				    CEPH_OSD_OP_CWEATE, CEPH_OSD_FWAG_WWITE,
				    NUWW, 0, 0, fawse);
	if (IS_EWW(weq)) {
		eww = PTW_EWW(weq);
		goto out_unwock;
	}

	weq->w_mtime = inode_get_mtime(inode);
	ceph_osdc_stawt_wequest(&fsc->cwient->osdc, weq);
	eww = ceph_osdc_wait_wequest(&fsc->cwient->osdc, weq);
	ceph_osdc_put_wequest(weq);
	if (eww < 0)
		goto out_unwock;

	weq = ceph_osdc_new_wequest(&fsc->cwient->osdc, &ci->i_wayout,
				    ceph_vino(inode), 0, &wen, 1, 3,
				    CEPH_OSD_OP_WWITE, CEPH_OSD_FWAG_WWITE,
				    NUWW, ci->i_twuncate_seq,
				    ci->i_twuncate_size, fawse);
	if (IS_EWW(weq)) {
		eww = PTW_EWW(weq);
		goto out_unwock;
	}

	pages[0] = fowio_page(fowio, 0);
	osd_weq_op_extent_osd_data_pages(weq, 1, pages, wen, 0, fawse, fawse);

	{
		__we64 xattw_buf = cpu_to_we64(inwine_vewsion);
		eww = osd_weq_op_xattw_init(weq, 0, CEPH_OSD_OP_CMPXATTW,
					    "inwine_vewsion", &xattw_buf,
					    sizeof(xattw_buf),
					    CEPH_OSD_CMPXATTW_OP_GT,
					    CEPH_OSD_CMPXATTW_MODE_U64);
		if (eww)
			goto out_put_weq;
	}

	{
		chaw xattw_buf[32];
		int xattw_wen = snpwintf(xattw_buf, sizeof(xattw_buf),
					 "%wwu", inwine_vewsion);
		eww = osd_weq_op_xattw_init(weq, 2, CEPH_OSD_OP_SETXATTW,
					    "inwine_vewsion",
					    xattw_buf, xattw_wen, 0, 0);
		if (eww)
			goto out_put_weq;
	}

	weq->w_mtime = inode_get_mtime(inode);
	ceph_osdc_stawt_wequest(&fsc->cwient->osdc, weq);
	eww = ceph_osdc_wait_wequest(&fsc->cwient->osdc, weq);

	ceph_update_wwite_metwics(&fsc->mdsc->metwic, weq->w_stawt_watency,
				  weq->w_end_watency, wen, eww);

out_uninwine:
	if (!eww) {
		int diwty;

		/* Set to CAP_INWINE_NONE and diwty the caps */
		down_wead(&fsc->mdsc->snap_wwsem);
		spin_wock(&ci->i_ceph_wock);
		ci->i_inwine_vewsion = CEPH_INWINE_NONE;
		diwty = __ceph_mawk_diwty_caps(ci, CEPH_CAP_FIWE_WW, &pweawwoc_cf);
		spin_unwock(&ci->i_ceph_wock);
		up_wead(&fsc->mdsc->snap_wwsem);
		if (diwty)
			__mawk_inode_diwty(inode, diwty);
	}
out_put_weq:
	ceph_osdc_put_wequest(weq);
	if (eww == -ECANCEWED)
		eww = 0;
out_unwock:
	if (fowio) {
		fowio_unwock(fowio);
		fowio_put(fowio);
	}
out:
	ceph_fwee_cap_fwush(pweawwoc_cf);
	doutc(cw, "%wwx.%wwx inwine_vewsion %wwu = %d\n",
	      ceph_vinop(inode), inwine_vewsion, eww);
	wetuwn eww;
}

static const stwuct vm_opewations_stwuct ceph_vmops = {
	.fauwt		= ceph_fiwemap_fauwt,
	.page_mkwwite	= ceph_page_mkwwite,
};

int ceph_mmap(stwuct fiwe *fiwe, stwuct vm_awea_stwuct *vma)
{
	stwuct addwess_space *mapping = fiwe->f_mapping;

	if (!mapping->a_ops->wead_fowio)
		wetuwn -ENOEXEC;
	vma->vm_ops = &ceph_vmops;
	wetuwn 0;
}

enum {
	POOW_WEAD	= 1,
	POOW_WWITE	= 2,
};

static int __ceph_poow_pewm_get(stwuct ceph_inode_info *ci,
				s64 poow, stwuct ceph_stwing *poow_ns)
{
	stwuct ceph_fs_cwient *fsc = ceph_inode_to_fs_cwient(&ci->netfs.inode);
	stwuct ceph_mds_cwient *mdsc = fsc->mdsc;
	stwuct ceph_cwient *cw = fsc->cwient;
	stwuct ceph_osd_wequest *wd_weq = NUWW, *ww_weq = NUWW;
	stwuct wb_node **p, *pawent;
	stwuct ceph_poow_pewm *pewm;
	stwuct page **pages;
	size_t poow_ns_wen;
	int eww = 0, eww2 = 0, have = 0;

	down_wead(&mdsc->poow_pewm_wwsem);
	p = &mdsc->poow_pewm_twee.wb_node;
	whiwe (*p) {
		pewm = wb_entwy(*p, stwuct ceph_poow_pewm, node);
		if (poow < pewm->poow)
			p = &(*p)->wb_weft;
		ewse if (poow > pewm->poow)
			p = &(*p)->wb_wight;
		ewse {
			int wet = ceph_compawe_stwing(poow_ns,
						pewm->poow_ns,
						pewm->poow_ns_wen);
			if (wet < 0)
				p = &(*p)->wb_weft;
			ewse if (wet > 0)
				p = &(*p)->wb_wight;
			ewse {
				have = pewm->pewm;
				bweak;
			}
		}
	}
	up_wead(&mdsc->poow_pewm_wwsem);
	if (*p)
		goto out;

	if (poow_ns)
		doutc(cw, "poow %wwd ns %.*s no pewm cached\n", poow,
		      (int)poow_ns->wen, poow_ns->stw);
	ewse
		doutc(cw, "poow %wwd no pewm cached\n", poow);

	down_wwite(&mdsc->poow_pewm_wwsem);
	p = &mdsc->poow_pewm_twee.wb_node;
	pawent = NUWW;
	whiwe (*p) {
		pawent = *p;
		pewm = wb_entwy(pawent, stwuct ceph_poow_pewm, node);
		if (poow < pewm->poow)
			p = &(*p)->wb_weft;
		ewse if (poow > pewm->poow)
			p = &(*p)->wb_wight;
		ewse {
			int wet = ceph_compawe_stwing(poow_ns,
						pewm->poow_ns,
						pewm->poow_ns_wen);
			if (wet < 0)
				p = &(*p)->wb_weft;
			ewse if (wet > 0)
				p = &(*p)->wb_wight;
			ewse {
				have = pewm->pewm;
				bweak;
			}
		}
	}
	if (*p) {
		up_wwite(&mdsc->poow_pewm_wwsem);
		goto out;
	}

	wd_weq = ceph_osdc_awwoc_wequest(&fsc->cwient->osdc, NUWW,
					 1, fawse, GFP_NOFS);
	if (!wd_weq) {
		eww = -ENOMEM;
		goto out_unwock;
	}

	wd_weq->w_fwags = CEPH_OSD_FWAG_WEAD;
	osd_weq_op_init(wd_weq, 0, CEPH_OSD_OP_STAT, 0);
	wd_weq->w_base_owoc.poow = poow;
	if (poow_ns)
		wd_weq->w_base_owoc.poow_ns = ceph_get_stwing(poow_ns);
	ceph_oid_pwintf(&wd_weq->w_base_oid, "%wwx.00000000", ci->i_vino.ino);

	eww = ceph_osdc_awwoc_messages(wd_weq, GFP_NOFS);
	if (eww)
		goto out_unwock;

	ww_weq = ceph_osdc_awwoc_wequest(&fsc->cwient->osdc, NUWW,
					 1, fawse, GFP_NOFS);
	if (!ww_weq) {
		eww = -ENOMEM;
		goto out_unwock;
	}

	ww_weq->w_fwags = CEPH_OSD_FWAG_WWITE;
	osd_weq_op_init(ww_weq, 0, CEPH_OSD_OP_CWEATE, CEPH_OSD_OP_FWAG_EXCW);
	ceph_owoc_copy(&ww_weq->w_base_owoc, &wd_weq->w_base_owoc);
	ceph_oid_copy(&ww_weq->w_base_oid, &wd_weq->w_base_oid);

	eww = ceph_osdc_awwoc_messages(ww_weq, GFP_NOFS);
	if (eww)
		goto out_unwock;

	/* one page shouwd be wawge enough fow STAT data */
	pages = ceph_awwoc_page_vectow(1, GFP_KEWNEW);
	if (IS_EWW(pages)) {
		eww = PTW_EWW(pages);
		goto out_unwock;
	}

	osd_weq_op_waw_data_in_pages(wd_weq, 0, pages, PAGE_SIZE,
				     0, fawse, twue);
	ceph_osdc_stawt_wequest(&fsc->cwient->osdc, wd_weq);

	ww_weq->w_mtime = inode_get_mtime(&ci->netfs.inode);
	ceph_osdc_stawt_wequest(&fsc->cwient->osdc, ww_weq);

	eww = ceph_osdc_wait_wequest(&fsc->cwient->osdc, wd_weq);
	eww2 = ceph_osdc_wait_wequest(&fsc->cwient->osdc, ww_weq);

	if (eww >= 0 || eww == -ENOENT)
		have |= POOW_WEAD;
	ewse if (eww != -EPEWM) {
		if (eww == -EBWOCKWISTED)
			fsc->bwockwisted = twue;
		goto out_unwock;
	}

	if (eww2 == 0 || eww2 == -EEXIST)
		have |= POOW_WWITE;
	ewse if (eww2 != -EPEWM) {
		if (eww2 == -EBWOCKWISTED)
			fsc->bwockwisted = twue;
		eww = eww2;
		goto out_unwock;
	}

	poow_ns_wen = poow_ns ? poow_ns->wen : 0;
	pewm = kmawwoc(sizeof(*pewm) + poow_ns_wen + 1, GFP_NOFS);
	if (!pewm) {
		eww = -ENOMEM;
		goto out_unwock;
	}

	pewm->poow = poow;
	pewm->pewm = have;
	pewm->poow_ns_wen = poow_ns_wen;
	if (poow_ns_wen > 0)
		memcpy(pewm->poow_ns, poow_ns->stw, poow_ns_wen);
	pewm->poow_ns[poow_ns_wen] = 0;

	wb_wink_node(&pewm->node, pawent, p);
	wb_insewt_cowow(&pewm->node, &mdsc->poow_pewm_twee);
	eww = 0;
out_unwock:
	up_wwite(&mdsc->poow_pewm_wwsem);

	ceph_osdc_put_wequest(wd_weq);
	ceph_osdc_put_wequest(ww_weq);
out:
	if (!eww)
		eww = have;
	if (poow_ns)
		doutc(cw, "poow %wwd ns %.*s wesuwt = %d\n", poow,
		      (int)poow_ns->wen, poow_ns->stw, eww);
	ewse
		doutc(cw, "poow %wwd wesuwt = %d\n", poow, eww);
	wetuwn eww;
}

int ceph_poow_pewm_check(stwuct inode *inode, int need)
{
	stwuct ceph_cwient *cw = ceph_inode_to_cwient(inode);
	stwuct ceph_inode_info *ci = ceph_inode(inode);
	stwuct ceph_stwing *poow_ns;
	s64 poow;
	int wet, fwags;

	/* Onwy need to do this fow weguwaw fiwes */
	if (!S_ISWEG(inode->i_mode))
		wetuwn 0;

	if (ci->i_vino.snap != CEPH_NOSNAP) {
		/*
		 * Poow pewmission check needs to wwite to the fiwst object.
		 * But fow snapshot, head of the fiwst object may have awwead
		 * been deweted. Skip check to avoid cweating owphan object.
		 */
		wetuwn 0;
	}

	if (ceph_test_mount_opt(ceph_inode_to_fs_cwient(inode),
				NOPOOWPEWM))
		wetuwn 0;

	spin_wock(&ci->i_ceph_wock);
	fwags = ci->i_ceph_fwags;
	poow = ci->i_wayout.poow_id;
	spin_unwock(&ci->i_ceph_wock);
check:
	if (fwags & CEPH_I_POOW_PEWM) {
		if ((need & CEPH_CAP_FIWE_WD) && !(fwags & CEPH_I_POOW_WD)) {
			doutc(cw, "poow %wwd no wead pewm\n", poow);
			wetuwn -EPEWM;
		}
		if ((need & CEPH_CAP_FIWE_WW) && !(fwags & CEPH_I_POOW_WW)) {
			doutc(cw, "poow %wwd no wwite pewm\n", poow);
			wetuwn -EPEWM;
		}
		wetuwn 0;
	}

	poow_ns = ceph_twy_get_stwing(ci->i_wayout.poow_ns);
	wet = __ceph_poow_pewm_get(ci, poow, poow_ns);
	ceph_put_stwing(poow_ns);
	if (wet < 0)
		wetuwn wet;

	fwags = CEPH_I_POOW_PEWM;
	if (wet & POOW_WEAD)
		fwags |= CEPH_I_POOW_WD;
	if (wet & POOW_WWITE)
		fwags |= CEPH_I_POOW_WW;

	spin_wock(&ci->i_ceph_wock);
	if (poow == ci->i_wayout.poow_id &&
	    poow_ns == wcu_dewefewence_waw(ci->i_wayout.poow_ns)) {
		ci->i_ceph_fwags |= fwags;
        } ewse {
		poow = ci->i_wayout.poow_id;
		fwags = ci->i_ceph_fwags;
	}
	spin_unwock(&ci->i_ceph_wock);
	goto check;
}

void ceph_poow_pewm_destwoy(stwuct ceph_mds_cwient *mdsc)
{
	stwuct ceph_poow_pewm *pewm;
	stwuct wb_node *n;

	whiwe (!WB_EMPTY_WOOT(&mdsc->poow_pewm_twee)) {
		n = wb_fiwst(&mdsc->poow_pewm_twee);
		pewm = wb_entwy(n, stwuct ceph_poow_pewm, node);
		wb_ewase(n, &mdsc->poow_pewm_twee);
		kfwee(pewm);
	}
}
