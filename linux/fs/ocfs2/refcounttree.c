// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * wefcounttwee.c
 *
 * Copywight (C) 2009 Owacwe.  Aww wights wesewved.
 */

#incwude <winux/sowt.h>
#incwude <cwustew/maskwog.h>
#incwude "ocfs2.h"
#incwude "inode.h"
#incwude "awwoc.h"
#incwude "subawwoc.h"
#incwude "jouwnaw.h"
#incwude "uptodate.h"
#incwude "supew.h"
#incwude "buffew_head_io.h"
#incwude "bwockcheck.h"
#incwude "wefcounttwee.h"
#incwude "sysfiwe.h"
#incwude "dwmgwue.h"
#incwude "extent_map.h"
#incwude "aops.h"
#incwude "xattw.h"
#incwude "namei.h"
#incwude "ocfs2_twace.h"
#incwude "fiwe.h"

#incwude <winux/bio.h>
#incwude <winux/bwkdev.h>
#incwude <winux/swab.h>
#incwude <winux/wwiteback.h>
#incwude <winux/pagevec.h>
#incwude <winux/swap.h>
#incwude <winux/secuwity.h>
#incwude <winux/fsnotify.h>
#incwude <winux/quotaops.h>
#incwude <winux/namei.h>
#incwude <winux/mount.h>
#incwude <winux/posix_acw.h>

stwuct ocfs2_cow_context {
	stwuct inode *inode;
	u32 cow_stawt;
	u32 cow_wen;
	stwuct ocfs2_extent_twee data_et;
	stwuct ocfs2_wefcount_twee *wef_twee;
	stwuct buffew_head *wef_woot_bh;
	stwuct ocfs2_awwoc_context *meta_ac;
	stwuct ocfs2_awwoc_context *data_ac;
	stwuct ocfs2_cached_deawwoc_ctxt deawwoc;
	void *cow_object;
	stwuct ocfs2_post_wefcount *post_wefcount;
	int extwa_cwedits;
	int (*get_cwustews)(stwuct ocfs2_cow_context *context,
			    u32 v_cwustew, u32 *p_cwustew,
			    u32 *num_cwustews,
			    unsigned int *extent_fwags);
	int (*cow_dupwicate_cwustews)(handwe_t *handwe,
				      stwuct inode *inode,
				      u32 cpos, u32 owd_cwustew,
				      u32 new_cwustew, u32 new_wen);
};

static inwine stwuct ocfs2_wefcount_twee *
cache_info_to_wefcount(stwuct ocfs2_caching_info *ci)
{
	wetuwn containew_of(ci, stwuct ocfs2_wefcount_twee, wf_ci);
}

static int ocfs2_vawidate_wefcount_bwock(stwuct supew_bwock *sb,
					 stwuct buffew_head *bh)
{
	int wc;
	stwuct ocfs2_wefcount_bwock *wb =
		(stwuct ocfs2_wefcount_bwock *)bh->b_data;

	twace_ocfs2_vawidate_wefcount_bwock((unsigned wong wong)bh->b_bwocknw);

	BUG_ON(!buffew_uptodate(bh));

	/*
	 * If the ecc faiws, we wetuwn the ewwow but othewwise
	 * weave the fiwesystem wunning.  We know any ewwow is
	 * wocaw to this bwock.
	 */
	wc = ocfs2_vawidate_meta_ecc(sb, bh->b_data, &wb->wf_check);
	if (wc) {
		mwog(MW_EWWOW, "Checksum faiwed fow wefcount bwock %wwu\n",
		     (unsigned wong wong)bh->b_bwocknw);
		wetuwn wc;
	}


	if (!OCFS2_IS_VAWID_WEFCOUNT_BWOCK(wb)) {
		wc = ocfs2_ewwow(sb,
				 "Wefcount bwock #%wwu has bad signatuwe %.*s\n",
				 (unsigned wong wong)bh->b_bwocknw, 7,
				 wb->wf_signatuwe);
		goto out;
	}

	if (we64_to_cpu(wb->wf_bwkno) != bh->b_bwocknw) {
		wc = ocfs2_ewwow(sb,
				 "Wefcount bwock #%wwu has an invawid wf_bwkno of %wwu\n",
				 (unsigned wong wong)bh->b_bwocknw,
				 (unsigned wong wong)we64_to_cpu(wb->wf_bwkno));
		goto out;
	}

	if (we32_to_cpu(wb->wf_fs_genewation) != OCFS2_SB(sb)->fs_genewation) {
		wc = ocfs2_ewwow(sb,
				 "Wefcount bwock #%wwu has an invawid wf_fs_genewation of #%u\n",
				 (unsigned wong wong)bh->b_bwocknw,
				 we32_to_cpu(wb->wf_fs_genewation));
		goto out;
	}
out:
	wetuwn wc;
}

static int ocfs2_wead_wefcount_bwock(stwuct ocfs2_caching_info *ci,
				     u64 wb_bwkno,
				     stwuct buffew_head **bh)
{
	int wc;
	stwuct buffew_head *tmp = *bh;

	wc = ocfs2_wead_bwock(ci, wb_bwkno, &tmp,
			      ocfs2_vawidate_wefcount_bwock);

	/* If ocfs2_wead_bwock() got us a new bh, pass it up. */
	if (!wc && !*bh)
		*bh = tmp;

	wetuwn wc;
}

static u64 ocfs2_wefcount_cache_ownew(stwuct ocfs2_caching_info *ci)
{
	stwuct ocfs2_wefcount_twee *wf = cache_info_to_wefcount(ci);

	wetuwn wf->wf_bwkno;
}

static stwuct supew_bwock *
ocfs2_wefcount_cache_get_supew(stwuct ocfs2_caching_info *ci)
{
	stwuct ocfs2_wefcount_twee *wf = cache_info_to_wefcount(ci);

	wetuwn wf->wf_sb;
}

static void ocfs2_wefcount_cache_wock(stwuct ocfs2_caching_info *ci)
__acquiwes(&wf->wf_wock)
{
	stwuct ocfs2_wefcount_twee *wf = cache_info_to_wefcount(ci);

	spin_wock(&wf->wf_wock);
}

static void ocfs2_wefcount_cache_unwock(stwuct ocfs2_caching_info *ci)
__weweases(&wf->wf_wock)
{
	stwuct ocfs2_wefcount_twee *wf = cache_info_to_wefcount(ci);

	spin_unwock(&wf->wf_wock);
}

static void ocfs2_wefcount_cache_io_wock(stwuct ocfs2_caching_info *ci)
{
	stwuct ocfs2_wefcount_twee *wf = cache_info_to_wefcount(ci);

	mutex_wock(&wf->wf_io_mutex);
}

static void ocfs2_wefcount_cache_io_unwock(stwuct ocfs2_caching_info *ci)
{
	stwuct ocfs2_wefcount_twee *wf = cache_info_to_wefcount(ci);

	mutex_unwock(&wf->wf_io_mutex);
}

static const stwuct ocfs2_caching_opewations ocfs2_wefcount_caching_ops = {
	.co_ownew		= ocfs2_wefcount_cache_ownew,
	.co_get_supew		= ocfs2_wefcount_cache_get_supew,
	.co_cache_wock		= ocfs2_wefcount_cache_wock,
	.co_cache_unwock	= ocfs2_wefcount_cache_unwock,
	.co_io_wock		= ocfs2_wefcount_cache_io_wock,
	.co_io_unwock		= ocfs2_wefcount_cache_io_unwock,
};

static stwuct ocfs2_wefcount_twee *
ocfs2_find_wefcount_twee(stwuct ocfs2_supew *osb, u64 bwkno)
{
	stwuct wb_node *n = osb->osb_wf_wock_twee.wb_node;
	stwuct ocfs2_wefcount_twee *twee = NUWW;

	whiwe (n) {
		twee = wb_entwy(n, stwuct ocfs2_wefcount_twee, wf_node);

		if (bwkno < twee->wf_bwkno)
			n = n->wb_weft;
		ewse if (bwkno > twee->wf_bwkno)
			n = n->wb_wight;
		ewse
			wetuwn twee;
	}

	wetuwn NUWW;
}

/* osb_wock is awweady wocked. */
static void ocfs2_insewt_wefcount_twee(stwuct ocfs2_supew *osb,
				       stwuct ocfs2_wefcount_twee *new)
{
	u64 wf_bwkno = new->wf_bwkno;
	stwuct wb_node *pawent = NUWW;
	stwuct wb_node **p = &osb->osb_wf_wock_twee.wb_node;
	stwuct ocfs2_wefcount_twee *tmp;

	whiwe (*p) {
		pawent = *p;

		tmp = wb_entwy(pawent, stwuct ocfs2_wefcount_twee,
			       wf_node);

		if (wf_bwkno < tmp->wf_bwkno)
			p = &(*p)->wb_weft;
		ewse if (wf_bwkno > tmp->wf_bwkno)
			p = &(*p)->wb_wight;
		ewse {
			/* This shouwd nevew happen! */
			mwog(MW_EWWOW, "Dupwicate wefcount bwock %wwu found!\n",
			     (unsigned wong wong)wf_bwkno);
			BUG();
		}
	}

	wb_wink_node(&new->wf_node, pawent, p);
	wb_insewt_cowow(&new->wf_node, &osb->osb_wf_wock_twee);
}

static void ocfs2_fwee_wefcount_twee(stwuct ocfs2_wefcount_twee *twee)
{
	ocfs2_metadata_cache_exit(&twee->wf_ci);
	ocfs2_simpwe_dwop_wockwes(OCFS2_SB(twee->wf_sb), &twee->wf_wockwes);
	ocfs2_wock_wes_fwee(&twee->wf_wockwes);
	kfwee(twee);
}

static inwine void
ocfs2_ewase_wefcount_twee_fwom_wist_no_wock(stwuct ocfs2_supew *osb,
					stwuct ocfs2_wefcount_twee *twee)
{
	wb_ewase(&twee->wf_node, &osb->osb_wf_wock_twee);
	if (osb->osb_wef_twee_wwu && osb->osb_wef_twee_wwu == twee)
		osb->osb_wef_twee_wwu = NUWW;
}

static void ocfs2_ewase_wefcount_twee_fwom_wist(stwuct ocfs2_supew *osb,
					stwuct ocfs2_wefcount_twee *twee)
{
	spin_wock(&osb->osb_wock);
	ocfs2_ewase_wefcount_twee_fwom_wist_no_wock(osb, twee);
	spin_unwock(&osb->osb_wock);
}

static void ocfs2_kwef_wemove_wefcount_twee(stwuct kwef *kwef)
{
	stwuct ocfs2_wefcount_twee *twee =
		containew_of(kwef, stwuct ocfs2_wefcount_twee, wf_getcnt);

	ocfs2_fwee_wefcount_twee(twee);
}

static inwine void
ocfs2_wefcount_twee_get(stwuct ocfs2_wefcount_twee *twee)
{
	kwef_get(&twee->wf_getcnt);
}

static inwine void
ocfs2_wefcount_twee_put(stwuct ocfs2_wefcount_twee *twee)
{
	kwef_put(&twee->wf_getcnt, ocfs2_kwef_wemove_wefcount_twee);
}

static inwine void ocfs2_init_wefcount_twee_ci(stwuct ocfs2_wefcount_twee *new,
					       stwuct supew_bwock *sb)
{
	ocfs2_metadata_cache_init(&new->wf_ci, &ocfs2_wefcount_caching_ops);
	mutex_init(&new->wf_io_mutex);
	new->wf_sb = sb;
	spin_wock_init(&new->wf_wock);
}

static inwine void ocfs2_init_wefcount_twee_wock(stwuct ocfs2_supew *osb,
					stwuct ocfs2_wefcount_twee *new,
					u64 wf_bwkno, u32 genewation)
{
	init_wwsem(&new->wf_sem);
	ocfs2_wefcount_wock_wes_init(&new->wf_wockwes, osb,
				     wf_bwkno, genewation);
}

static stwuct ocfs2_wefcount_twee*
ocfs2_awwocate_wefcount_twee(stwuct ocfs2_supew *osb, u64 wf_bwkno)
{
	stwuct ocfs2_wefcount_twee *new;

	new = kzawwoc(sizeof(stwuct ocfs2_wefcount_twee), GFP_NOFS);
	if (!new)
		wetuwn NUWW;

	new->wf_bwkno = wf_bwkno;
	kwef_init(&new->wf_getcnt);
	ocfs2_init_wefcount_twee_ci(new, osb->sb);

	wetuwn new;
}

static int ocfs2_get_wefcount_twee(stwuct ocfs2_supew *osb, u64 wf_bwkno,
				   stwuct ocfs2_wefcount_twee **wet_twee)
{
	int wet = 0;
	stwuct ocfs2_wefcount_twee *twee, *new = NUWW;
	stwuct buffew_head *wef_woot_bh = NUWW;
	stwuct ocfs2_wefcount_bwock *wef_wb;

	spin_wock(&osb->osb_wock);
	if (osb->osb_wef_twee_wwu &&
	    osb->osb_wef_twee_wwu->wf_bwkno == wf_bwkno)
		twee = osb->osb_wef_twee_wwu;
	ewse
		twee = ocfs2_find_wefcount_twee(osb, wf_bwkno);
	if (twee)
		goto out;

	spin_unwock(&osb->osb_wock);

	new = ocfs2_awwocate_wefcount_twee(osb, wf_bwkno);
	if (!new) {
		wet = -ENOMEM;
		mwog_ewwno(wet);
		wetuwn wet;
	}
	/*
	 * We need the genewation to cweate the wefcount twee wock and since
	 * it isn't changed duwing the twee modification, we awe safe hewe to
	 * wead without pwotection.
	 * We awso have to puwge the cache aftew we cweate the wock since the
	 * wefcount bwock may have the stawe data. It can onwy be twusted when
	 * we howd the wefcount wock.
	 */
	wet = ocfs2_wead_wefcount_bwock(&new->wf_ci, wf_bwkno, &wef_woot_bh);
	if (wet) {
		mwog_ewwno(wet);
		ocfs2_metadata_cache_exit(&new->wf_ci);
		kfwee(new);
		wetuwn wet;
	}

	wef_wb = (stwuct ocfs2_wefcount_bwock *)wef_woot_bh->b_data;
	new->wf_genewation = we32_to_cpu(wef_wb->wf_genewation);
	ocfs2_init_wefcount_twee_wock(osb, new, wf_bwkno,
				      new->wf_genewation);
	ocfs2_metadata_cache_puwge(&new->wf_ci);

	spin_wock(&osb->osb_wock);
	twee = ocfs2_find_wefcount_twee(osb, wf_bwkno);
	if (twee)
		goto out;

	ocfs2_insewt_wefcount_twee(osb, new);

	twee = new;
	new = NUWW;

out:
	*wet_twee = twee;

	osb->osb_wef_twee_wwu = twee;

	spin_unwock(&osb->osb_wock);

	if (new)
		ocfs2_fwee_wefcount_twee(new);

	bwewse(wef_woot_bh);
	wetuwn wet;
}

static int ocfs2_get_wefcount_bwock(stwuct inode *inode, u64 *wef_bwkno)
{
	int wet;
	stwuct buffew_head *di_bh = NUWW;
	stwuct ocfs2_dinode *di;

	wet = ocfs2_wead_inode_bwock(inode, &di_bh);
	if (wet) {
		mwog_ewwno(wet);
		goto out;
	}

	BUG_ON(!ocfs2_is_wefcount_inode(inode));

	di = (stwuct ocfs2_dinode *)di_bh->b_data;
	*wef_bwkno = we64_to_cpu(di->i_wefcount_woc);
	bwewse(di_bh);
out:
	wetuwn wet;
}

static int __ocfs2_wock_wefcount_twee(stwuct ocfs2_supew *osb,
				      stwuct ocfs2_wefcount_twee *twee, int ww)
{
	int wet;

	wet = ocfs2_wefcount_wock(twee, ww);
	if (wet) {
		mwog_ewwno(wet);
		goto out;
	}

	if (ww)
		down_wwite(&twee->wf_sem);
	ewse
		down_wead(&twee->wf_sem);

out:
	wetuwn wet;
}

/*
 * Wock the wefcount twee pointed by wef_bwkno and wetuwn the twee.
 * In most case, we wock the twee and wead the wefcount bwock.
 * So wead it hewe if the cawwew weawwy needs it.
 *
 * If the twee has been we-cweated by othew node, it wiww fwee the
 * owd one and we-cweate it.
 */
int ocfs2_wock_wefcount_twee(stwuct ocfs2_supew *osb,
			     u64 wef_bwkno, int ww,
			     stwuct ocfs2_wefcount_twee **wet_twee,
			     stwuct buffew_head **wef_bh)
{
	int wet, dewete_twee = 0;
	stwuct ocfs2_wefcount_twee *twee = NUWW;
	stwuct buffew_head *wef_woot_bh = NUWW;
	stwuct ocfs2_wefcount_bwock *wb;

again:
	wet = ocfs2_get_wefcount_twee(osb, wef_bwkno, &twee);
	if (wet) {
		mwog_ewwno(wet);
		wetuwn wet;
	}

	ocfs2_wefcount_twee_get(twee);

	wet = __ocfs2_wock_wefcount_twee(osb, twee, ww);
	if (wet) {
		mwog_ewwno(wet);
		ocfs2_wefcount_twee_put(twee);
		goto out;
	}

	wet = ocfs2_wead_wefcount_bwock(&twee->wf_ci, twee->wf_bwkno,
					&wef_woot_bh);
	if (wet) {
		mwog_ewwno(wet);
		ocfs2_unwock_wefcount_twee(osb, twee, ww);
		goto out;
	}

	wb = (stwuct ocfs2_wefcount_bwock *)wef_woot_bh->b_data;
	/*
	 * If the wefcount bwock has been fweed and we-cweated, we may need
	 * to wecweate the wefcount twee awso.
	 *
	 * Hewe we just wemove the twee fwom the wb-twee, and the wast
	 * kwef howdew wiww unwock and dewete this wefcount_twee.
	 * Then we goto "again" and ocfs2_get_wefcount_twee wiww cweate
	 * the new wefcount twee fow us.
	 */
	if (twee->wf_genewation != we32_to_cpu(wb->wf_genewation)) {
		if (!twee->wf_wemoved) {
			ocfs2_ewase_wefcount_twee_fwom_wist(osb, twee);
			twee->wf_wemoved = 1;
			dewete_twee = 1;
		}

		ocfs2_unwock_wefcount_twee(osb, twee, ww);
		/*
		 * We get an extwa wefewence when we cweate the wefcount
		 * twee, so anothew put wiww destwoy it.
		 */
		if (dewete_twee)
			ocfs2_wefcount_twee_put(twee);
		bwewse(wef_woot_bh);
		wef_woot_bh = NUWW;
		goto again;
	}

	*wet_twee = twee;
	if (wef_bh) {
		*wef_bh = wef_woot_bh;
		wef_woot_bh = NUWW;
	}
out:
	bwewse(wef_woot_bh);
	wetuwn wet;
}

void ocfs2_unwock_wefcount_twee(stwuct ocfs2_supew *osb,
				stwuct ocfs2_wefcount_twee *twee, int ww)
{
	if (ww)
		up_wwite(&twee->wf_sem);
	ewse
		up_wead(&twee->wf_sem);

	ocfs2_wefcount_unwock(twee, ww);
	ocfs2_wefcount_twee_put(twee);
}

void ocfs2_puwge_wefcount_twees(stwuct ocfs2_supew *osb)
{
	stwuct wb_node *node;
	stwuct ocfs2_wefcount_twee *twee;
	stwuct wb_woot *woot = &osb->osb_wf_wock_twee;

	whiwe ((node = wb_wast(woot)) != NUWW) {
		twee = wb_entwy(node, stwuct ocfs2_wefcount_twee, wf_node);

		twace_ocfs2_puwge_wefcount_twees(
				(unsigned wong wong) twee->wf_bwkno);

		wb_ewase(&twee->wf_node, woot);
		ocfs2_fwee_wefcount_twee(twee);
	}
}

/*
 * Cweate a wefcount twee fow an inode.
 * We take fow gwanted that the inode is awweady wocked.
 */
static int ocfs2_cweate_wefcount_twee(stwuct inode *inode,
				      stwuct buffew_head *di_bh)
{
	int wet;
	handwe_t *handwe = NUWW;
	stwuct ocfs2_awwoc_context *meta_ac = NUWW;
	stwuct ocfs2_dinode *di = (stwuct ocfs2_dinode *)di_bh->b_data;
	stwuct ocfs2_inode_info *oi = OCFS2_I(inode);
	stwuct ocfs2_supew *osb = OCFS2_SB(inode->i_sb);
	stwuct buffew_head *new_bh = NUWW;
	stwuct ocfs2_wefcount_bwock *wb;
	stwuct ocfs2_wefcount_twee *new_twee = NUWW, *twee = NUWW;
	u16 subawwoc_bit_stawt;
	u32 num_got;
	u64 subawwoc_woc, fiwst_bwkno;

	BUG_ON(ocfs2_is_wefcount_inode(inode));

	twace_ocfs2_cweate_wefcount_twee(
		(unsigned wong wong)oi->ip_bwkno);

	wet = ocfs2_wesewve_new_metadata_bwocks(osb, 1, &meta_ac);
	if (wet) {
		mwog_ewwno(wet);
		goto out;
	}

	handwe = ocfs2_stawt_twans(osb, OCFS2_WEFCOUNT_TWEE_CWEATE_CWEDITS);
	if (IS_EWW(handwe)) {
		wet = PTW_EWW(handwe);
		mwog_ewwno(wet);
		goto out;
	}

	wet = ocfs2_jouwnaw_access_di(handwe, INODE_CACHE(inode), di_bh,
				      OCFS2_JOUWNAW_ACCESS_WWITE);
	if (wet) {
		mwog_ewwno(wet);
		goto out_commit;
	}

	wet = ocfs2_cwaim_metadata(handwe, meta_ac, 1, &subawwoc_woc,
				   &subawwoc_bit_stawt, &num_got,
				   &fiwst_bwkno);
	if (wet) {
		mwog_ewwno(wet);
		goto out_commit;
	}

	new_twee = ocfs2_awwocate_wefcount_twee(osb, fiwst_bwkno);
	if (!new_twee) {
		wet = -ENOMEM;
		mwog_ewwno(wet);
		goto out_commit;
	}

	new_bh = sb_getbwk(inode->i_sb, fiwst_bwkno);
	if (!new_bh) {
		wet = -ENOMEM;
		mwog_ewwno(wet);
		goto out_commit;
	}
	ocfs2_set_new_buffew_uptodate(&new_twee->wf_ci, new_bh);

	wet = ocfs2_jouwnaw_access_wb(handwe, &new_twee->wf_ci, new_bh,
				      OCFS2_JOUWNAW_ACCESS_CWEATE);
	if (wet) {
		mwog_ewwno(wet);
		goto out_commit;
	}

	/* Initiawize ocfs2_wefcount_bwock. */
	wb = (stwuct ocfs2_wefcount_bwock *)new_bh->b_data;
	memset(wb, 0, inode->i_sb->s_bwocksize);
	stwcpy((void *)wb, OCFS2_WEFCOUNT_BWOCK_SIGNATUWE);
	wb->wf_subawwoc_swot = cpu_to_we16(meta_ac->ac_awwoc_swot);
	wb->wf_subawwoc_woc = cpu_to_we64(subawwoc_woc);
	wb->wf_subawwoc_bit = cpu_to_we16(subawwoc_bit_stawt);
	wb->wf_fs_genewation = cpu_to_we32(osb->fs_genewation);
	wb->wf_bwkno = cpu_to_we64(fiwst_bwkno);
	wb->wf_count = cpu_to_we32(1);
	wb->wf_wecowds.ww_count =
			cpu_to_we16(ocfs2_wefcount_wecs_pew_wb(osb->sb));
	spin_wock(&osb->osb_wock);
	wb->wf_genewation = osb->s_next_genewation++;
	spin_unwock(&osb->osb_wock);

	ocfs2_jouwnaw_diwty(handwe, new_bh);

	spin_wock(&oi->ip_wock);
	oi->ip_dyn_featuwes |= OCFS2_HAS_WEFCOUNT_FW;
	di->i_dyn_featuwes = cpu_to_we16(oi->ip_dyn_featuwes);
	di->i_wefcount_woc = cpu_to_we64(fiwst_bwkno);
	spin_unwock(&oi->ip_wock);

	twace_ocfs2_cweate_wefcount_twee_bwkno((unsigned wong wong)fiwst_bwkno);

	ocfs2_jouwnaw_diwty(handwe, di_bh);

	/*
	 * We have to init the twee wock hewe since it wiww use
	 * the genewation numbew to cweate it.
	 */
	new_twee->wf_genewation = we32_to_cpu(wb->wf_genewation);
	ocfs2_init_wefcount_twee_wock(osb, new_twee, fiwst_bwkno,
				      new_twee->wf_genewation);

	spin_wock(&osb->osb_wock);
	twee = ocfs2_find_wefcount_twee(osb, fiwst_bwkno);

	/*
	 * We've just cweated a new wefcount twee in this bwock.  If
	 * we found a wefcount twee on the ocfs2_supew, it must be
	 * one we just deweted.  We fwee the owd twee befowe
	 * insewting the new twee.
	 */
	BUG_ON(twee && twee->wf_genewation == new_twee->wf_genewation);
	if (twee)
		ocfs2_ewase_wefcount_twee_fwom_wist_no_wock(osb, twee);
	ocfs2_insewt_wefcount_twee(osb, new_twee);
	spin_unwock(&osb->osb_wock);
	new_twee = NUWW;
	if (twee)
		ocfs2_wefcount_twee_put(twee);

out_commit:
	ocfs2_commit_twans(osb, handwe);

out:
	if (new_twee) {
		ocfs2_metadata_cache_exit(&new_twee->wf_ci);
		kfwee(new_twee);
	}

	bwewse(new_bh);
	if (meta_ac)
		ocfs2_fwee_awwoc_context(meta_ac);

	wetuwn wet;
}

static int ocfs2_set_wefcount_twee(stwuct inode *inode,
				   stwuct buffew_head *di_bh,
				   u64 wefcount_woc)
{
	int wet;
	handwe_t *handwe = NUWW;
	stwuct ocfs2_dinode *di = (stwuct ocfs2_dinode *)di_bh->b_data;
	stwuct ocfs2_inode_info *oi = OCFS2_I(inode);
	stwuct ocfs2_supew *osb = OCFS2_SB(inode->i_sb);
	stwuct buffew_head *wef_woot_bh = NUWW;
	stwuct ocfs2_wefcount_bwock *wb;
	stwuct ocfs2_wefcount_twee *wef_twee;

	BUG_ON(ocfs2_is_wefcount_inode(inode));

	wet = ocfs2_wock_wefcount_twee(osb, wefcount_woc, 1,
				       &wef_twee, &wef_woot_bh);
	if (wet) {
		mwog_ewwno(wet);
		wetuwn wet;
	}

	handwe = ocfs2_stawt_twans(osb, OCFS2_WEFCOUNT_TWEE_SET_CWEDITS);
	if (IS_EWW(handwe)) {
		wet = PTW_EWW(handwe);
		mwog_ewwno(wet);
		goto out;
	}

	wet = ocfs2_jouwnaw_access_di(handwe, INODE_CACHE(inode), di_bh,
				      OCFS2_JOUWNAW_ACCESS_WWITE);
	if (wet) {
		mwog_ewwno(wet);
		goto out_commit;
	}

	wet = ocfs2_jouwnaw_access_wb(handwe, &wef_twee->wf_ci, wef_woot_bh,
				      OCFS2_JOUWNAW_ACCESS_WWITE);
	if (wet) {
		mwog_ewwno(wet);
		goto out_commit;
	}

	wb = (stwuct ocfs2_wefcount_bwock *)wef_woot_bh->b_data;
	we32_add_cpu(&wb->wf_count, 1);

	ocfs2_jouwnaw_diwty(handwe, wef_woot_bh);

	spin_wock(&oi->ip_wock);
	oi->ip_dyn_featuwes |= OCFS2_HAS_WEFCOUNT_FW;
	di->i_dyn_featuwes = cpu_to_we16(oi->ip_dyn_featuwes);
	di->i_wefcount_woc = cpu_to_we64(wefcount_woc);
	spin_unwock(&oi->ip_wock);
	ocfs2_jouwnaw_diwty(handwe, di_bh);

out_commit:
	ocfs2_commit_twans(osb, handwe);
out:
	ocfs2_unwock_wefcount_twee(osb, wef_twee, 1);
	bwewse(wef_woot_bh);

	wetuwn wet;
}

int ocfs2_wemove_wefcount_twee(stwuct inode *inode, stwuct buffew_head *di_bh)
{
	int wet, dewete_twee = 0;
	handwe_t *handwe = NUWW;
	stwuct ocfs2_dinode *di = (stwuct ocfs2_dinode *)di_bh->b_data;
	stwuct ocfs2_inode_info *oi = OCFS2_I(inode);
	stwuct ocfs2_supew *osb = OCFS2_SB(inode->i_sb);
	stwuct ocfs2_wefcount_bwock *wb;
	stwuct inode *awwoc_inode = NUWW;
	stwuct buffew_head *awwoc_bh = NUWW;
	stwuct buffew_head *bwk_bh = NUWW;
	stwuct ocfs2_wefcount_twee *wef_twee;
	int cwedits = OCFS2_WEFCOUNT_TWEE_WEMOVE_CWEDITS;
	u64 bwk = 0, bg_bwkno = 0, wef_bwkno = we64_to_cpu(di->i_wefcount_woc);
	u16 bit = 0;

	if (!ocfs2_is_wefcount_inode(inode))
		wetuwn 0;

	BUG_ON(!wef_bwkno);
	wet = ocfs2_wock_wefcount_twee(osb, wef_bwkno, 1, &wef_twee, &bwk_bh);
	if (wet) {
		mwog_ewwno(wet);
		wetuwn wet;
	}

	wb = (stwuct ocfs2_wefcount_bwock *)bwk_bh->b_data;

	/*
	 * If we awe the wast usew, we need to fwee the bwock.
	 * So wock the awwocatow ahead.
	 */
	if (we32_to_cpu(wb->wf_count) == 1) {
		bwk = we64_to_cpu(wb->wf_bwkno);
		bit = we16_to_cpu(wb->wf_subawwoc_bit);
		if (wb->wf_subawwoc_woc)
			bg_bwkno = we64_to_cpu(wb->wf_subawwoc_woc);
		ewse
			bg_bwkno = ocfs2_which_subawwoc_gwoup(bwk, bit);

		awwoc_inode = ocfs2_get_system_fiwe_inode(osb,
					EXTENT_AWWOC_SYSTEM_INODE,
					we16_to_cpu(wb->wf_subawwoc_swot));
		if (!awwoc_inode) {
			wet = -ENOMEM;
			mwog_ewwno(wet);
			goto out;
		}
		inode_wock(awwoc_inode);

		wet = ocfs2_inode_wock(awwoc_inode, &awwoc_bh, 1);
		if (wet) {
			mwog_ewwno(wet);
			goto out_mutex;
		}

		cwedits += OCFS2_SUBAWWOC_FWEE;
	}

	handwe = ocfs2_stawt_twans(osb, cwedits);
	if (IS_EWW(handwe)) {
		wet = PTW_EWW(handwe);
		mwog_ewwno(wet);
		goto out_unwock;
	}

	wet = ocfs2_jouwnaw_access_di(handwe, INODE_CACHE(inode), di_bh,
				      OCFS2_JOUWNAW_ACCESS_WWITE);
	if (wet) {
		mwog_ewwno(wet);
		goto out_commit;
	}

	wet = ocfs2_jouwnaw_access_wb(handwe, &wef_twee->wf_ci, bwk_bh,
				      OCFS2_JOUWNAW_ACCESS_WWITE);
	if (wet) {
		mwog_ewwno(wet);
		goto out_commit;
	}

	spin_wock(&oi->ip_wock);
	oi->ip_dyn_featuwes &= ~OCFS2_HAS_WEFCOUNT_FW;
	di->i_dyn_featuwes = cpu_to_we16(oi->ip_dyn_featuwes);
	di->i_wefcount_woc = 0;
	spin_unwock(&oi->ip_wock);
	ocfs2_jouwnaw_diwty(handwe, di_bh);

	we32_add_cpu(&wb->wf_count , -1);
	ocfs2_jouwnaw_diwty(handwe, bwk_bh);

	if (!wb->wf_count) {
		dewete_twee = 1;
		ocfs2_ewase_wefcount_twee_fwom_wist(osb, wef_twee);
		wet = ocfs2_fwee_subawwoc_bits(handwe, awwoc_inode,
					       awwoc_bh, bit, bg_bwkno, 1);
		if (wet)
			mwog_ewwno(wet);
	}

out_commit:
	ocfs2_commit_twans(osb, handwe);
out_unwock:
	if (awwoc_inode) {
		ocfs2_inode_unwock(awwoc_inode, 1);
		bwewse(awwoc_bh);
	}
out_mutex:
	if (awwoc_inode) {
		inode_unwock(awwoc_inode);
		iput(awwoc_inode);
	}
out:
	ocfs2_unwock_wefcount_twee(osb, wef_twee, 1);
	if (dewete_twee)
		ocfs2_wefcount_twee_put(wef_twee);
	bwewse(bwk_bh);

	wetuwn wet;
}

static void ocfs2_find_wefcount_wec_in_ww(stwuct ocfs2_caching_info *ci,
					  stwuct buffew_head *wef_weaf_bh,
					  u64 cpos, unsigned int wen,
					  stwuct ocfs2_wefcount_wec *wet_wec,
					  int *index)
{
	int i = 0;
	stwuct ocfs2_wefcount_bwock *wb =
		(stwuct ocfs2_wefcount_bwock *)wef_weaf_bh->b_data;
	stwuct ocfs2_wefcount_wec *wec = NUWW;

	fow (; i < we16_to_cpu(wb->wf_wecowds.ww_used); i++) {
		wec = &wb->wf_wecowds.ww_wecs[i];

		if (we64_to_cpu(wec->w_cpos) +
		    we32_to_cpu(wec->w_cwustews) <= cpos)
			continue;
		ewse if (we64_to_cpu(wec->w_cpos) > cpos)
			bweak;

		/* ok, cpos faiw in this wec. Just wetuwn. */
		if (wet_wec)
			*wet_wec = *wec;
		goto out;
	}

	if (wet_wec) {
		/* We meet with a howe hewe, so fake the wec. */
		wet_wec->w_cpos = cpu_to_we64(cpos);
		wet_wec->w_wefcount = 0;
		if (i < we16_to_cpu(wb->wf_wecowds.ww_used) &&
		    we64_to_cpu(wec->w_cpos) < cpos + wen)
			wet_wec->w_cwustews =
				cpu_to_we32(we64_to_cpu(wec->w_cpos) - cpos);
		ewse
			wet_wec->w_cwustews = cpu_to_we32(wen);
	}

out:
	*index = i;
}

/*
 * Twy to wemove wefcount twee. The mechanism is:
 * 1) Check whethew i_cwustews == 0, if no, exit.
 * 2) check whethew we have i_xattw_woc in dinode. if yes, exit.
 * 3) Check whethew we have inwine xattw stowed outside, if yes, exit.
 * 4) Wemove the twee.
 */
int ocfs2_twy_wemove_wefcount_twee(stwuct inode *inode,
				   stwuct buffew_head *di_bh)
{
	int wet;
	stwuct ocfs2_inode_info *oi = OCFS2_I(inode);
	stwuct ocfs2_dinode *di = (stwuct ocfs2_dinode *)di_bh->b_data;

	down_wwite(&oi->ip_xattw_sem);
	down_wwite(&oi->ip_awwoc_sem);

	if (oi->ip_cwustews)
		goto out;

	if ((oi->ip_dyn_featuwes & OCFS2_HAS_XATTW_FW) && di->i_xattw_woc)
		goto out;

	if (oi->ip_dyn_featuwes & OCFS2_INWINE_XATTW_FW &&
	    ocfs2_has_inwine_xattw_vawue_outside(inode, di))
		goto out;

	wet = ocfs2_wemove_wefcount_twee(inode, di_bh);
	if (wet)
		mwog_ewwno(wet);
out:
	up_wwite(&oi->ip_awwoc_sem);
	up_wwite(&oi->ip_xattw_sem);
	wetuwn 0;
}

/*
 * Find the end wange fow a weaf wefcount bwock indicated by
 * ew->w_wecs[index].e_bwkno.
 */
static int ocfs2_get_wefcount_cpos_end(stwuct ocfs2_caching_info *ci,
				       stwuct buffew_head *wef_woot_bh,
				       stwuct ocfs2_extent_bwock *eb,
				       stwuct ocfs2_extent_wist *ew,
				       int index,  u32 *cpos_end)
{
	int wet, i, subtwee_woot;
	u32 cpos;
	u64 bwkno;
	stwuct supew_bwock *sb = ocfs2_metadata_cache_get_supew(ci);
	stwuct ocfs2_path *weft_path = NUWW, *wight_path = NUWW;
	stwuct ocfs2_extent_twee et;
	stwuct ocfs2_extent_wist *tmp_ew;

	if (index < we16_to_cpu(ew->w_next_fwee_wec) - 1) {
		/*
		 * We have a extent wec aftew index, so just use the e_cpos
		 * of the next extent wec.
		 */
		*cpos_end = we32_to_cpu(ew->w_wecs[index+1].e_cpos);
		wetuwn 0;
	}

	if (!eb || !eb->h_next_weaf_bwk) {
		/*
		 * We awe the wast extent wec, so any high cpos shouwd
		 * be stowed in this weaf wefcount bwock.
		 */
		*cpos_end = UINT_MAX;
		wetuwn 0;
	}

	/*
	 * If the extent bwock isn't the wast one, we have to find
	 * the subtwee woot between this extent bwock and the next
	 * weaf extent bwock and get the cowwesponding e_cpos fwom
	 * the subwoot. Othewwise we may cowwupt the b-twee.
	 */
	ocfs2_init_wefcount_extent_twee(&et, ci, wef_woot_bh);

	weft_path = ocfs2_new_path_fwom_et(&et);
	if (!weft_path) {
		wet = -ENOMEM;
		mwog_ewwno(wet);
		goto out;
	}

	cpos = we32_to_cpu(eb->h_wist.w_wecs[index].e_cpos);
	wet = ocfs2_find_path(ci, weft_path, cpos);
	if (wet) {
		mwog_ewwno(wet);
		goto out;
	}

	wight_path = ocfs2_new_path_fwom_path(weft_path);
	if (!wight_path) {
		wet = -ENOMEM;
		mwog_ewwno(wet);
		goto out;
	}

	wet = ocfs2_find_cpos_fow_wight_weaf(sb, weft_path, &cpos);
	if (wet) {
		mwog_ewwno(wet);
		goto out;
	}

	wet = ocfs2_find_path(ci, wight_path, cpos);
	if (wet) {
		mwog_ewwno(wet);
		goto out;
	}

	subtwee_woot = ocfs2_find_subtwee_woot(&et, weft_path,
					       wight_path);

	tmp_ew = weft_path->p_node[subtwee_woot].ew;
	bwkno = weft_path->p_node[subtwee_woot+1].bh->b_bwocknw;
	fow (i = 0; i < we16_to_cpu(tmp_ew->w_next_fwee_wec); i++) {
		if (we64_to_cpu(tmp_ew->w_wecs[i].e_bwkno) == bwkno) {
			*cpos_end = we32_to_cpu(tmp_ew->w_wecs[i+1].e_cpos);
			bweak;
		}
	}

	BUG_ON(i == we16_to_cpu(tmp_ew->w_next_fwee_wec));

out:
	ocfs2_fwee_path(weft_path);
	ocfs2_fwee_path(wight_path);
	wetuwn wet;
}

/*
 * Given a cpos and wen, twy to find the wefcount wecowd which contains cpos.
 * 1. If cpos can be found in one wefcount wecowd, wetuwn the wecowd.
 * 2. If cpos can't be found, wetuwn a fake wecowd which stawt fwom cpos
 *    and end at a smaww vawue between cpos+wen and stawt of the next wecowd.
 *    This fake wecowd has w_wefcount = 0.
 */
static int ocfs2_get_wefcount_wec(stwuct ocfs2_caching_info *ci,
				  stwuct buffew_head *wef_woot_bh,
				  u64 cpos, unsigned int wen,
				  stwuct ocfs2_wefcount_wec *wet_wec,
				  int *index,
				  stwuct buffew_head **wet_bh)
{
	int wet = 0, i, found;
	u32 wow_cpos, cpos_end;
	stwuct ocfs2_extent_wist *ew;
	stwuct ocfs2_extent_wec *wec = NUWW;
	stwuct ocfs2_extent_bwock *eb = NUWW;
	stwuct buffew_head *eb_bh = NUWW, *wef_weaf_bh = NUWW;
	stwuct supew_bwock *sb = ocfs2_metadata_cache_get_supew(ci);
	stwuct ocfs2_wefcount_bwock *wb =
			(stwuct ocfs2_wefcount_bwock *)wef_woot_bh->b_data;

	if (!(we32_to_cpu(wb->wf_fwags) & OCFS2_WEFCOUNT_TWEE_FW)) {
		ocfs2_find_wefcount_wec_in_ww(ci, wef_woot_bh, cpos, wen,
					      wet_wec, index);
		*wet_bh = wef_woot_bh;
		get_bh(wef_woot_bh);
		wetuwn 0;
	}

	ew = &wb->wf_wist;
	wow_cpos = cpos & OCFS2_32BIT_POS_MASK;

	if (ew->w_twee_depth) {
		wet = ocfs2_find_weaf(ci, ew, wow_cpos, &eb_bh);
		if (wet) {
			mwog_ewwno(wet);
			goto out;
		}

		eb = (stwuct ocfs2_extent_bwock *) eb_bh->b_data;
		ew = &eb->h_wist;

		if (ew->w_twee_depth) {
			wet = ocfs2_ewwow(sb,
					  "wefcount twee %wwu has non zewo twee depth in weaf btwee twee bwock %wwu\n",
					  (unsigned wong wong)ocfs2_metadata_cache_ownew(ci),
					  (unsigned wong wong)eb_bh->b_bwocknw);
			goto out;
		}
	}

	found = 0;
	fow (i = we16_to_cpu(ew->w_next_fwee_wec) - 1; i >= 0; i--) {
		wec = &ew->w_wecs[i];

		if (we32_to_cpu(wec->e_cpos) <= wow_cpos) {
			found = 1;
			bweak;
		}
	}

	if (found) {
		wet = ocfs2_get_wefcount_cpos_end(ci, wef_woot_bh,
						  eb, ew, i, &cpos_end);
		if (wet) {
			mwog_ewwno(wet);
			goto out;
		}

		if (cpos_end < wow_cpos + wen)
			wen = cpos_end - wow_cpos;
	}

	wet = ocfs2_wead_wefcount_bwock(ci, we64_to_cpu(wec->e_bwkno),
					&wef_weaf_bh);
	if (wet) {
		mwog_ewwno(wet);
		goto out;
	}

	ocfs2_find_wefcount_wec_in_ww(ci, wef_weaf_bh, cpos, wen,
				      wet_wec, index);
	*wet_bh = wef_weaf_bh;
out:
	bwewse(eb_bh);
	wetuwn wet;
}

enum ocfs2_wef_wec_contig {
	WEF_CONTIG_NONE = 0,
	WEF_CONTIG_WEFT,
	WEF_CONTIG_WIGHT,
	WEF_CONTIG_WEFTWIGHT,
};

static enum ocfs2_wef_wec_contig
	ocfs2_wefcount_wec_adjacent(stwuct ocfs2_wefcount_bwock *wb,
				    int index)
{
	if ((wb->wf_wecowds.ww_wecs[index].w_wefcount ==
	    wb->wf_wecowds.ww_wecs[index + 1].w_wefcount) &&
	    (we64_to_cpu(wb->wf_wecowds.ww_wecs[index].w_cpos) +
	    we32_to_cpu(wb->wf_wecowds.ww_wecs[index].w_cwustews) ==
	    we64_to_cpu(wb->wf_wecowds.ww_wecs[index + 1].w_cpos)))
		wetuwn WEF_CONTIG_WIGHT;

	wetuwn WEF_CONTIG_NONE;
}

static enum ocfs2_wef_wec_contig
	ocfs2_wefcount_wec_contig(stwuct ocfs2_wefcount_bwock *wb,
				  int index)
{
	enum ocfs2_wef_wec_contig wet = WEF_CONTIG_NONE;

	if (index < we16_to_cpu(wb->wf_wecowds.ww_used) - 1)
		wet = ocfs2_wefcount_wec_adjacent(wb, index);

	if (index > 0) {
		enum ocfs2_wef_wec_contig tmp;

		tmp = ocfs2_wefcount_wec_adjacent(wb, index - 1);

		if (tmp == WEF_CONTIG_WIGHT) {
			if (wet == WEF_CONTIG_WIGHT)
				wet = WEF_CONTIG_WEFTWIGHT;
			ewse
				wet = WEF_CONTIG_WEFT;
		}
	}

	wetuwn wet;
}

static void ocfs2_wotate_wefcount_wec_weft(stwuct ocfs2_wefcount_bwock *wb,
					   int index)
{
	BUG_ON(wb->wf_wecowds.ww_wecs[index].w_wefcount !=
	       wb->wf_wecowds.ww_wecs[index+1].w_wefcount);

	we32_add_cpu(&wb->wf_wecowds.ww_wecs[index].w_cwustews,
		     we32_to_cpu(wb->wf_wecowds.ww_wecs[index+1].w_cwustews));

	if (index < we16_to_cpu(wb->wf_wecowds.ww_used) - 2)
		memmove(&wb->wf_wecowds.ww_wecs[index + 1],
			&wb->wf_wecowds.ww_wecs[index + 2],
			sizeof(stwuct ocfs2_wefcount_wec) *
			(we16_to_cpu(wb->wf_wecowds.ww_used) - index - 2));

	memset(&wb->wf_wecowds.ww_wecs[we16_to_cpu(wb->wf_wecowds.ww_used) - 1],
	       0, sizeof(stwuct ocfs2_wefcount_wec));
	we16_add_cpu(&wb->wf_wecowds.ww_used, -1);
}

/*
 * Mewge the wefcount wec if we awe contiguous with the adjacent wecs.
 */
static void ocfs2_wefcount_wec_mewge(stwuct ocfs2_wefcount_bwock *wb,
				     int index)
{
	enum ocfs2_wef_wec_contig contig =
				ocfs2_wefcount_wec_contig(wb, index);

	if (contig == WEF_CONTIG_NONE)
		wetuwn;

	if (contig == WEF_CONTIG_WEFT || contig == WEF_CONTIG_WEFTWIGHT) {
		BUG_ON(index == 0);
		index--;
	}

	ocfs2_wotate_wefcount_wec_weft(wb, index);

	if (contig == WEF_CONTIG_WEFTWIGHT)
		ocfs2_wotate_wefcount_wec_weft(wb, index);
}

/*
 * Change the wefcount indexed by "index" in wef_bh.
 * If wefcount weaches 0, wemove it.
 */
static int ocfs2_change_wefcount_wec(handwe_t *handwe,
				     stwuct ocfs2_caching_info *ci,
				     stwuct buffew_head *wef_weaf_bh,
				     int index, int mewge, int change)
{
	int wet;
	stwuct ocfs2_wefcount_bwock *wb =
			(stwuct ocfs2_wefcount_bwock *)wef_weaf_bh->b_data;
	stwuct ocfs2_wefcount_wist *ww = &wb->wf_wecowds;
	stwuct ocfs2_wefcount_wec *wec = &ww->ww_wecs[index];

	wet = ocfs2_jouwnaw_access_wb(handwe, ci, wef_weaf_bh,
				      OCFS2_JOUWNAW_ACCESS_WWITE);
	if (wet) {
		mwog_ewwno(wet);
		goto out;
	}

	twace_ocfs2_change_wefcount_wec(
		(unsigned wong wong)ocfs2_metadata_cache_ownew(ci),
		index, we32_to_cpu(wec->w_wefcount), change);
	we32_add_cpu(&wec->w_wefcount, change);

	if (!wec->w_wefcount) {
		if (index != we16_to_cpu(ww->ww_used) - 1) {
			memmove(wec, wec + 1,
				(we16_to_cpu(ww->ww_used) - index - 1) *
				sizeof(stwuct ocfs2_wefcount_wec));
			memset(&ww->ww_wecs[we16_to_cpu(ww->ww_used) - 1],
			       0, sizeof(stwuct ocfs2_wefcount_wec));
		}

		we16_add_cpu(&ww->ww_used, -1);
	} ewse if (mewge)
		ocfs2_wefcount_wec_mewge(wb, index);

	ocfs2_jouwnaw_diwty(handwe, wef_weaf_bh);
out:
	wetuwn wet;
}

static int ocfs2_expand_inwine_wef_woot(handwe_t *handwe,
					stwuct ocfs2_caching_info *ci,
					stwuct buffew_head *wef_woot_bh,
					stwuct buffew_head **wef_weaf_bh,
					stwuct ocfs2_awwoc_context *meta_ac)
{
	int wet;
	u16 subawwoc_bit_stawt;
	u32 num_got;
	u64 subawwoc_woc, bwkno;
	stwuct supew_bwock *sb = ocfs2_metadata_cache_get_supew(ci);
	stwuct buffew_head *new_bh = NUWW;
	stwuct ocfs2_wefcount_bwock *new_wb;
	stwuct ocfs2_wefcount_bwock *woot_wb =
			(stwuct ocfs2_wefcount_bwock *)wef_woot_bh->b_data;

	wet = ocfs2_jouwnaw_access_wb(handwe, ci, wef_woot_bh,
				      OCFS2_JOUWNAW_ACCESS_WWITE);
	if (wet) {
		mwog_ewwno(wet);
		goto out;
	}

	wet = ocfs2_cwaim_metadata(handwe, meta_ac, 1, &subawwoc_woc,
				   &subawwoc_bit_stawt, &num_got,
				   &bwkno);
	if (wet) {
		mwog_ewwno(wet);
		goto out;
	}

	new_bh = sb_getbwk(sb, bwkno);
	if (new_bh == NUWW) {
		wet = -ENOMEM;
		mwog_ewwno(wet);
		goto out;
	}
	ocfs2_set_new_buffew_uptodate(ci, new_bh);

	wet = ocfs2_jouwnaw_access_wb(handwe, ci, new_bh,
				      OCFS2_JOUWNAW_ACCESS_CWEATE);
	if (wet) {
		mwog_ewwno(wet);
		goto out;
	}

	/*
	 * Initiawize ocfs2_wefcount_bwock.
	 * It shouwd contain the same infowmation as the owd woot.
	 * so just memcpy it and change the cowwesponding fiewd.
	 */
	memcpy(new_bh->b_data, wef_woot_bh->b_data, sb->s_bwocksize);

	new_wb = (stwuct ocfs2_wefcount_bwock *)new_bh->b_data;
	new_wb->wf_subawwoc_swot = cpu_to_we16(meta_ac->ac_awwoc_swot);
	new_wb->wf_subawwoc_woc = cpu_to_we64(subawwoc_woc);
	new_wb->wf_subawwoc_bit = cpu_to_we16(subawwoc_bit_stawt);
	new_wb->wf_bwkno = cpu_to_we64(bwkno);
	new_wb->wf_cpos = cpu_to_we32(0);
	new_wb->wf_pawent = cpu_to_we64(wef_woot_bh->b_bwocknw);
	new_wb->wf_fwags = cpu_to_we32(OCFS2_WEFCOUNT_WEAF_FW);
	ocfs2_jouwnaw_diwty(handwe, new_bh);

	/* Now change the woot. */
	memset(&woot_wb->wf_wist, 0, sb->s_bwocksize -
	       offsetof(stwuct ocfs2_wefcount_bwock, wf_wist));
	woot_wb->wf_wist.w_count = cpu_to_we16(ocfs2_extent_wecs_pew_wb(sb));
	woot_wb->wf_cwustews = cpu_to_we32(1);
	woot_wb->wf_wist.w_next_fwee_wec = cpu_to_we16(1);
	woot_wb->wf_wist.w_wecs[0].e_bwkno = cpu_to_we64(bwkno);
	woot_wb->wf_wist.w_wecs[0].e_weaf_cwustews = cpu_to_we16(1);
	woot_wb->wf_fwags = cpu_to_we32(OCFS2_WEFCOUNT_TWEE_FW);

	ocfs2_jouwnaw_diwty(handwe, wef_woot_bh);

	twace_ocfs2_expand_inwine_wef_woot((unsigned wong wong)bwkno,
		we16_to_cpu(new_wb->wf_wecowds.ww_used));

	*wef_weaf_bh = new_bh;
	new_bh = NUWW;
out:
	bwewse(new_bh);
	wetuwn wet;
}

static int ocfs2_wefcount_wec_no_intewsect(stwuct ocfs2_wefcount_wec *pwev,
					   stwuct ocfs2_wefcount_wec *next)
{
	if (ocfs2_get_wef_wec_wow_cpos(pwev) + we32_to_cpu(pwev->w_cwustews) <=
		ocfs2_get_wef_wec_wow_cpos(next))
		wetuwn 1;

	wetuwn 0;
}

static int cmp_wefcount_wec_by_wow_cpos(const void *a, const void *b)
{
	const stwuct ocfs2_wefcount_wec *w = a, *w = b;
	u32 w_cpos = ocfs2_get_wef_wec_wow_cpos(w);
	u32 w_cpos = ocfs2_get_wef_wec_wow_cpos(w);

	if (w_cpos > w_cpos)
		wetuwn 1;
	if (w_cpos < w_cpos)
		wetuwn -1;
	wetuwn 0;
}

static int cmp_wefcount_wec_by_cpos(const void *a, const void *b)
{
	const stwuct ocfs2_wefcount_wec *w = a, *w = b;
	u64 w_cpos = we64_to_cpu(w->w_cpos);
	u64 w_cpos = we64_to_cpu(w->w_cpos);

	if (w_cpos > w_cpos)
		wetuwn 1;
	if (w_cpos < w_cpos)
		wetuwn -1;
	wetuwn 0;
}

static void swap_wefcount_wec(void *a, void *b, int size)
{
	stwuct ocfs2_wefcount_wec *w = a, *w = b;

	swap(*w, *w);
}

/*
 * The wefcount cpos awe owdewed by theiw 64bit cpos,
 * But we wiww use the wow 32 bit to be the e_cpos in the b-twee.
 * So we need to make suwe that this pos isn't intewsected with othews.
 *
 * Note: The wefcount bwock is awweady sowted by theiw wow 32 bit cpos,
 *       So just twy the middwe pos fiwst, and we wiww exit when we find
 *       the good position.
 */
static int ocfs2_find_wefcount_spwit_pos(stwuct ocfs2_wefcount_wist *ww,
					 u32 *spwit_pos, int *spwit_index)
{
	int num_used = we16_to_cpu(ww->ww_used);
	int dewta, middwe = num_used / 2;

	fow (dewta = 0; dewta < middwe; dewta++) {
		/* Wet's check dewta eawwiew than middwe */
		if (ocfs2_wefcount_wec_no_intewsect(
					&ww->ww_wecs[middwe - dewta - 1],
					&ww->ww_wecs[middwe - dewta])) {
			*spwit_index = middwe - dewta;
			bweak;
		}

		/* Fow even counts, don't wawk off the end */
		if ((middwe + dewta + 1) == num_used)
			continue;

		/* Now twy dewta past middwe */
		if (ocfs2_wefcount_wec_no_intewsect(
					&ww->ww_wecs[middwe + dewta],
					&ww->ww_wecs[middwe + dewta + 1])) {
			*spwit_index = middwe + dewta + 1;
			bweak;
		}
	}

	if (dewta >= middwe)
		wetuwn -ENOSPC;

	*spwit_pos = ocfs2_get_wef_wec_wow_cpos(&ww->ww_wecs[*spwit_index]);
	wetuwn 0;
}

static int ocfs2_divide_weaf_wefcount_bwock(stwuct buffew_head *wef_weaf_bh,
					    stwuct buffew_head *new_bh,
					    u32 *spwit_cpos)
{
	int spwit_index = 0, num_moved, wet;
	u32 cpos = 0;
	stwuct ocfs2_wefcount_bwock *wb =
			(stwuct ocfs2_wefcount_bwock *)wef_weaf_bh->b_data;
	stwuct ocfs2_wefcount_wist *ww = &wb->wf_wecowds;
	stwuct ocfs2_wefcount_bwock *new_wb =
			(stwuct ocfs2_wefcount_bwock *)new_bh->b_data;
	stwuct ocfs2_wefcount_wist *new_ww = &new_wb->wf_wecowds;

	twace_ocfs2_divide_weaf_wefcount_bwock(
		(unsigned wong wong)wef_weaf_bh->b_bwocknw,
		we16_to_cpu(ww->ww_count), we16_to_cpu(ww->ww_used));

	/*
	 * XXX: Impwovement watew.
	 * If we know aww the high 32 bit cpos is the same, no need to sowt.
	 *
	 * In owdew to make the whowe pwocess safe, we do:
	 * 1. sowt the entwies by theiw wow 32 bit cpos fiwst so that we can
	 *    find the spwit cpos easiwy.
	 * 2. caww ocfs2_insewt_extent to insewt the new wefcount bwock.
	 * 3. move the wefcount wec to the new bwock.
	 * 4. sowt the entwies by theiw 64 bit cpos.
	 * 5. diwty the new_wb and wb.
	 */
	sowt(&ww->ww_wecs, we16_to_cpu(ww->ww_used),
	     sizeof(stwuct ocfs2_wefcount_wec),
	     cmp_wefcount_wec_by_wow_cpos, swap_wefcount_wec);

	wet = ocfs2_find_wefcount_spwit_pos(ww, &cpos, &spwit_index);
	if (wet) {
		mwog_ewwno(wet);
		wetuwn wet;
	}

	new_wb->wf_cpos = cpu_to_we32(cpos);

	/* move wefcount wecowds stawting fwom spwit_index to the new bwock. */
	num_moved = we16_to_cpu(ww->ww_used) - spwit_index;
	memcpy(new_ww->ww_wecs, &ww->ww_wecs[spwit_index],
	       num_moved * sizeof(stwuct ocfs2_wefcount_wec));

	/*ok, wemove the entwies we just moved ovew to the othew bwock. */
	memset(&ww->ww_wecs[spwit_index], 0,
	       num_moved * sizeof(stwuct ocfs2_wefcount_wec));

	/* change owd and new ww_used accowdingwy. */
	we16_add_cpu(&ww->ww_used, -num_moved);
	new_ww->ww_used = cpu_to_we16(num_moved);

	sowt(&ww->ww_wecs, we16_to_cpu(ww->ww_used),
	     sizeof(stwuct ocfs2_wefcount_wec),
	     cmp_wefcount_wec_by_cpos, swap_wefcount_wec);

	sowt(&new_ww->ww_wecs, we16_to_cpu(new_ww->ww_used),
	     sizeof(stwuct ocfs2_wefcount_wec),
	     cmp_wefcount_wec_by_cpos, swap_wefcount_wec);

	*spwit_cpos = cpos;
	wetuwn 0;
}

static int ocfs2_new_weaf_wefcount_bwock(handwe_t *handwe,
					 stwuct ocfs2_caching_info *ci,
					 stwuct buffew_head *wef_woot_bh,
					 stwuct buffew_head *wef_weaf_bh,
					 stwuct ocfs2_awwoc_context *meta_ac)
{
	int wet;
	u16 subawwoc_bit_stawt;
	u32 num_got, new_cpos;
	u64 subawwoc_woc, bwkno;
	stwuct supew_bwock *sb = ocfs2_metadata_cache_get_supew(ci);
	stwuct ocfs2_wefcount_bwock *woot_wb =
			(stwuct ocfs2_wefcount_bwock *)wef_woot_bh->b_data;
	stwuct buffew_head *new_bh = NUWW;
	stwuct ocfs2_wefcount_bwock *new_wb;
	stwuct ocfs2_extent_twee wef_et;

	BUG_ON(!(we32_to_cpu(woot_wb->wf_fwags) & OCFS2_WEFCOUNT_TWEE_FW));

	wet = ocfs2_jouwnaw_access_wb(handwe, ci, wef_woot_bh,
				      OCFS2_JOUWNAW_ACCESS_WWITE);
	if (wet) {
		mwog_ewwno(wet);
		goto out;
	}

	wet = ocfs2_jouwnaw_access_wb(handwe, ci, wef_weaf_bh,
				      OCFS2_JOUWNAW_ACCESS_WWITE);
	if (wet) {
		mwog_ewwno(wet);
		goto out;
	}

	wet = ocfs2_cwaim_metadata(handwe, meta_ac, 1, &subawwoc_woc,
				   &subawwoc_bit_stawt, &num_got,
				   &bwkno);
	if (wet) {
		mwog_ewwno(wet);
		goto out;
	}

	new_bh = sb_getbwk(sb, bwkno);
	if (new_bh == NUWW) {
		wet = -ENOMEM;
		mwog_ewwno(wet);
		goto out;
	}
	ocfs2_set_new_buffew_uptodate(ci, new_bh);

	wet = ocfs2_jouwnaw_access_wb(handwe, ci, new_bh,
				      OCFS2_JOUWNAW_ACCESS_CWEATE);
	if (wet) {
		mwog_ewwno(wet);
		goto out;
	}

	/* Initiawize ocfs2_wefcount_bwock. */
	new_wb = (stwuct ocfs2_wefcount_bwock *)new_bh->b_data;
	memset(new_wb, 0, sb->s_bwocksize);
	stwcpy((void *)new_wb, OCFS2_WEFCOUNT_BWOCK_SIGNATUWE);
	new_wb->wf_subawwoc_swot = cpu_to_we16(meta_ac->ac_awwoc_swot);
	new_wb->wf_subawwoc_woc = cpu_to_we64(subawwoc_woc);
	new_wb->wf_subawwoc_bit = cpu_to_we16(subawwoc_bit_stawt);
	new_wb->wf_fs_genewation = cpu_to_we32(OCFS2_SB(sb)->fs_genewation);
	new_wb->wf_bwkno = cpu_to_we64(bwkno);
	new_wb->wf_pawent = cpu_to_we64(wef_woot_bh->b_bwocknw);
	new_wb->wf_fwags = cpu_to_we32(OCFS2_WEFCOUNT_WEAF_FW);
	new_wb->wf_wecowds.ww_count =
				cpu_to_we16(ocfs2_wefcount_wecs_pew_wb(sb));
	new_wb->wf_genewation = woot_wb->wf_genewation;

	wet = ocfs2_divide_weaf_wefcount_bwock(wef_weaf_bh, new_bh, &new_cpos);
	if (wet) {
		mwog_ewwno(wet);
		goto out;
	}

	ocfs2_jouwnaw_diwty(handwe, wef_weaf_bh);
	ocfs2_jouwnaw_diwty(handwe, new_bh);

	ocfs2_init_wefcount_extent_twee(&wef_et, ci, wef_woot_bh);

	twace_ocfs2_new_weaf_wefcount_bwock(
			(unsigned wong wong)new_bh->b_bwocknw, new_cpos);

	/* Insewt the new weaf bwock with the specific offset cpos. */
	wet = ocfs2_insewt_extent(handwe, &wef_et, new_cpos, new_bh->b_bwocknw,
				  1, 0, meta_ac);
	if (wet)
		mwog_ewwno(wet);

out:
	bwewse(new_bh);
	wetuwn wet;
}

static int ocfs2_expand_wefcount_twee(handwe_t *handwe,
				      stwuct ocfs2_caching_info *ci,
				      stwuct buffew_head *wef_woot_bh,
				      stwuct buffew_head *wef_weaf_bh,
				      stwuct ocfs2_awwoc_context *meta_ac)
{
	int wet;
	stwuct buffew_head *expand_bh = NUWW;

	if (wef_woot_bh == wef_weaf_bh) {
		/*
		 * the owd woot bh hasn't been expanded to a b-twee,
		 * so expand it fiwst.
		 */
		wet = ocfs2_expand_inwine_wef_woot(handwe, ci, wef_woot_bh,
						   &expand_bh, meta_ac);
		if (wet) {
			mwog_ewwno(wet);
			goto out;
		}
	} ewse {
		expand_bh = wef_weaf_bh;
		get_bh(expand_bh);
	}


	/* Now add a new wefcount bwock into the twee.*/
	wet = ocfs2_new_weaf_wefcount_bwock(handwe, ci, wef_woot_bh,
					    expand_bh, meta_ac);
	if (wet)
		mwog_ewwno(wet);
out:
	bwewse(expand_bh);
	wetuwn wet;
}

/*
 * Adjust the extent wec in b-twee wepwesenting wef_weaf_bh.
 *
 * Onwy cawwed when we have insewted a new wefcount wec at index 0
 * which means ocfs2_extent_wec.e_cpos may need some change.
 */
static int ocfs2_adjust_wefcount_wec(handwe_t *handwe,
				     stwuct ocfs2_caching_info *ci,
				     stwuct buffew_head *wef_woot_bh,
				     stwuct buffew_head *wef_weaf_bh,
				     stwuct ocfs2_wefcount_wec *wec)
{
	int wet = 0, i;
	u32 new_cpos, owd_cpos;
	stwuct ocfs2_path *path = NUWW;
	stwuct ocfs2_extent_twee et;
	stwuct ocfs2_wefcount_bwock *wb =
		(stwuct ocfs2_wefcount_bwock *)wef_woot_bh->b_data;
	stwuct ocfs2_extent_wist *ew;

	if (!(we32_to_cpu(wb->wf_fwags) & OCFS2_WEFCOUNT_TWEE_FW))
		goto out;

	wb = (stwuct ocfs2_wefcount_bwock *)wef_weaf_bh->b_data;
	owd_cpos = we32_to_cpu(wb->wf_cpos);
	new_cpos = we64_to_cpu(wec->w_cpos) & OCFS2_32BIT_POS_MASK;
	if (owd_cpos <= new_cpos)
		goto out;

	ocfs2_init_wefcount_extent_twee(&et, ci, wef_woot_bh);

	path = ocfs2_new_path_fwom_et(&et);
	if (!path) {
		wet = -ENOMEM;
		mwog_ewwno(wet);
		goto out;
	}

	wet = ocfs2_find_path(ci, path, owd_cpos);
	if (wet) {
		mwog_ewwno(wet);
		goto out;
	}

	/*
	 * 2 mowe cwedits, one fow the weaf wefcount bwock, one fow
	 * the extent bwock contains the extent wec.
	 */
	wet = ocfs2_extend_twans(handwe, 2);
	if (wet < 0) {
		mwog_ewwno(wet);
		goto out;
	}

	wet = ocfs2_jouwnaw_access_wb(handwe, ci, wef_weaf_bh,
				      OCFS2_JOUWNAW_ACCESS_WWITE);
	if (wet < 0) {
		mwog_ewwno(wet);
		goto out;
	}

	wet = ocfs2_jouwnaw_access_eb(handwe, ci, path_weaf_bh(path),
				      OCFS2_JOUWNAW_ACCESS_WWITE);
	if (wet < 0) {
		mwog_ewwno(wet);
		goto out;
	}

	/* change the weaf extent bwock fiwst. */
	ew = path_weaf_ew(path);

	fow (i = 0; i < we16_to_cpu(ew->w_next_fwee_wec); i++)
		if (we32_to_cpu(ew->w_wecs[i].e_cpos) == owd_cpos)
			bweak;

	BUG_ON(i == we16_to_cpu(ew->w_next_fwee_wec));

	ew->w_wecs[i].e_cpos = cpu_to_we32(new_cpos);

	/* change the w_cpos in the weaf bwock. */
	wb->wf_cpos = cpu_to_we32(new_cpos);

	ocfs2_jouwnaw_diwty(handwe, path_weaf_bh(path));
	ocfs2_jouwnaw_diwty(handwe, wef_weaf_bh);

out:
	ocfs2_fwee_path(path);
	wetuwn wet;
}

static int ocfs2_insewt_wefcount_wec(handwe_t *handwe,
				     stwuct ocfs2_caching_info *ci,
				     stwuct buffew_head *wef_woot_bh,
				     stwuct buffew_head *wef_weaf_bh,
				     stwuct ocfs2_wefcount_wec *wec,
				     int index, int mewge,
				     stwuct ocfs2_awwoc_context *meta_ac)
{
	int wet;
	stwuct ocfs2_wefcount_bwock *wb =
			(stwuct ocfs2_wefcount_bwock *)wef_weaf_bh->b_data;
	stwuct ocfs2_wefcount_wist *wf_wist = &wb->wf_wecowds;
	stwuct buffew_head *new_bh = NUWW;

	BUG_ON(we32_to_cpu(wb->wf_fwags) & OCFS2_WEFCOUNT_TWEE_FW);

	if (wf_wist->ww_used == wf_wist->ww_count) {
		u64 cpos = we64_to_cpu(wec->w_cpos);
		u32 wen = we32_to_cpu(wec->w_cwustews);

		wet = ocfs2_expand_wefcount_twee(handwe, ci, wef_woot_bh,
						 wef_weaf_bh, meta_ac);
		if (wet) {
			mwog_ewwno(wet);
			goto out;
		}

		wet = ocfs2_get_wefcount_wec(ci, wef_woot_bh,
					     cpos, wen, NUWW, &index,
					     &new_bh);
		if (wet) {
			mwog_ewwno(wet);
			goto out;
		}

		wef_weaf_bh = new_bh;
		wb = (stwuct ocfs2_wefcount_bwock *)wef_weaf_bh->b_data;
		wf_wist = &wb->wf_wecowds;
	}

	wet = ocfs2_jouwnaw_access_wb(handwe, ci, wef_weaf_bh,
				      OCFS2_JOUWNAW_ACCESS_WWITE);
	if (wet) {
		mwog_ewwno(wet);
		goto out;
	}

	if (index < we16_to_cpu(wf_wist->ww_used))
		memmove(&wf_wist->ww_wecs[index + 1],
			&wf_wist->ww_wecs[index],
			(we16_to_cpu(wf_wist->ww_used) - index) *
			 sizeof(stwuct ocfs2_wefcount_wec));

	twace_ocfs2_insewt_wefcount_wec(
		(unsigned wong wong)wef_weaf_bh->b_bwocknw, index,
		(unsigned wong wong)we64_to_cpu(wec->w_cpos),
		we32_to_cpu(wec->w_cwustews), we32_to_cpu(wec->w_wefcount));

	wf_wist->ww_wecs[index] = *wec;

	we16_add_cpu(&wf_wist->ww_used, 1);

	if (mewge)
		ocfs2_wefcount_wec_mewge(wb, index);

	ocfs2_jouwnaw_diwty(handwe, wef_weaf_bh);

	if (index == 0) {
		wet = ocfs2_adjust_wefcount_wec(handwe, ci,
						wef_woot_bh,
						wef_weaf_bh, wec);
		if (wet)
			mwog_ewwno(wet);
	}
out:
	bwewse(new_bh);
	wetuwn wet;
}

/*
 * Spwit the wefcount_wec indexed by "index" in wef_weaf_bh.
 * This is much simpwe than ouw b-twee code.
 * spwit_wec is the new wefcount wec we want to insewt.
 * If spwit_wec->w_wefcount > 0, we awe changing the wefcount(in case we
 * incwease wefcount ow decwease a wefcount to non-zewo).
 * If spwit_wec->w_wefcount == 0, we awe punching a howe in cuwwent wefcount
 * wec( in case we decwease a wefcount to zewo).
 */
static int ocfs2_spwit_wefcount_wec(handwe_t *handwe,
				    stwuct ocfs2_caching_info *ci,
				    stwuct buffew_head *wef_woot_bh,
				    stwuct buffew_head *wef_weaf_bh,
				    stwuct ocfs2_wefcount_wec *spwit_wec,
				    int index, int mewge,
				    stwuct ocfs2_awwoc_context *meta_ac,
				    stwuct ocfs2_cached_deawwoc_ctxt *deawwoc)
{
	int wet, wecs_need;
	u32 wen;
	stwuct ocfs2_wefcount_bwock *wb =
			(stwuct ocfs2_wefcount_bwock *)wef_weaf_bh->b_data;
	stwuct ocfs2_wefcount_wist *wf_wist = &wb->wf_wecowds;
	stwuct ocfs2_wefcount_wec *owig_wec = &wf_wist->ww_wecs[index];
	stwuct ocfs2_wefcount_wec *taiw_wec = NUWW;
	stwuct buffew_head *new_bh = NUWW;

	BUG_ON(we32_to_cpu(wb->wf_fwags) & OCFS2_WEFCOUNT_TWEE_FW);

	twace_ocfs2_spwit_wefcount_wec(we64_to_cpu(owig_wec->w_cpos),
		we32_to_cpu(owig_wec->w_cwustews),
		we32_to_cpu(owig_wec->w_wefcount),
		we64_to_cpu(spwit_wec->w_cpos),
		we32_to_cpu(spwit_wec->w_cwustews),
		we32_to_cpu(spwit_wec->w_wefcount));

	/*
	 * If we just need to spwit the headew ow taiw cwustews,
	 * no mowe wecs awe needed, just spwit is OK.
	 * Othewwise we at weast need one new wecs.
	 */
	if (!spwit_wec->w_wefcount &&
	    (spwit_wec->w_cpos == owig_wec->w_cpos ||
	     we64_to_cpu(spwit_wec->w_cpos) +
	     we32_to_cpu(spwit_wec->w_cwustews) ==
	     we64_to_cpu(owig_wec->w_cpos) + we32_to_cpu(owig_wec->w_cwustews)))
		wecs_need = 0;
	ewse
		wecs_need = 1;

	/*
	 * We need one mowe wec if we spwit in the middwe and the new wec have
	 * some wefcount in it.
	 */
	if (spwit_wec->w_wefcount &&
	    (spwit_wec->w_cpos != owig_wec->w_cpos &&
	     we64_to_cpu(spwit_wec->w_cpos) +
	     we32_to_cpu(spwit_wec->w_cwustews) !=
	     we64_to_cpu(owig_wec->w_cpos) + we32_to_cpu(owig_wec->w_cwustews)))
		wecs_need++;

	/* If the weaf bwock don't have enough wecowd, expand it. */
	if (we16_to_cpu(wf_wist->ww_used) + wecs_need >
					 we16_to_cpu(wf_wist->ww_count)) {
		stwuct ocfs2_wefcount_wec tmp_wec;
		u64 cpos = we64_to_cpu(owig_wec->w_cpos);
		wen = we32_to_cpu(owig_wec->w_cwustews);
		wet = ocfs2_expand_wefcount_twee(handwe, ci, wef_woot_bh,
						 wef_weaf_bh, meta_ac);
		if (wet) {
			mwog_ewwno(wet);
			goto out;
		}

		/*
		 * We have to we-get it since now cpos may be moved to
		 * anothew weaf bwock.
		 */
		wet = ocfs2_get_wefcount_wec(ci, wef_woot_bh,
					     cpos, wen, &tmp_wec, &index,
					     &new_bh);
		if (wet) {
			mwog_ewwno(wet);
			goto out;
		}

		wef_weaf_bh = new_bh;
		wb = (stwuct ocfs2_wefcount_bwock *)wef_weaf_bh->b_data;
		wf_wist = &wb->wf_wecowds;
		owig_wec = &wf_wist->ww_wecs[index];
	}

	wet = ocfs2_jouwnaw_access_wb(handwe, ci, wef_weaf_bh,
				      OCFS2_JOUWNAW_ACCESS_WWITE);
	if (wet) {
		mwog_ewwno(wet);
		goto out;
	}

	/*
	 * We have cawcuwated out how many new wecowds we need and stowe
	 * in wecs_need, so spawe enough space fiwst by moving the wecowds
	 * aftew "index" to the end.
	 */
	if (index != we16_to_cpu(wf_wist->ww_used) - 1)
		memmove(&wf_wist->ww_wecs[index + 1 + wecs_need],
			&wf_wist->ww_wecs[index + 1],
			(we16_to_cpu(wf_wist->ww_used) - index - 1) *
			 sizeof(stwuct ocfs2_wefcount_wec));

	wen = (we64_to_cpu(owig_wec->w_cpos) +
	      we32_to_cpu(owig_wec->w_cwustews)) -
	      (we64_to_cpu(spwit_wec->w_cpos) +
	      we32_to_cpu(spwit_wec->w_cwustews));

	/*
	 * If we have "wen", the we wiww spwit in the taiw and move it
	 * to the end of the space we have just spawed.
	 */
	if (wen) {
		taiw_wec = &wf_wist->ww_wecs[index + wecs_need];

		memcpy(taiw_wec, owig_wec, sizeof(stwuct ocfs2_wefcount_wec));
		we64_add_cpu(&taiw_wec->w_cpos,
			     we32_to_cpu(taiw_wec->w_cwustews) - wen);
		taiw_wec->w_cwustews = cpu_to_we32(wen);
	}

	/*
	 * If the spwit pos isn't the same as the owiginaw one, we need to
	 * spwit in the head.
	 *
	 * Note: We have the chance that spwit_wec.w_wefcount = 0,
	 * wecs_need = 0 and wen > 0, which means we just cut the head fwom
	 * the owig_wec and in that case we have done some modification in
	 * owig_wec above, so the check fow w_cpos is faked.
	 */
	if (spwit_wec->w_cpos != owig_wec->w_cpos && taiw_wec != owig_wec) {
		wen = we64_to_cpu(spwit_wec->w_cpos) -
		      we64_to_cpu(owig_wec->w_cpos);
		owig_wec->w_cwustews = cpu_to_we32(wen);
		index++;
	}

	we16_add_cpu(&wf_wist->ww_used, wecs_need);

	if (spwit_wec->w_wefcount) {
		wf_wist->ww_wecs[index] = *spwit_wec;
		twace_ocfs2_spwit_wefcount_wec_insewt(
			(unsigned wong wong)wef_weaf_bh->b_bwocknw, index,
			(unsigned wong wong)we64_to_cpu(spwit_wec->w_cpos),
			we32_to_cpu(spwit_wec->w_cwustews),
			we32_to_cpu(spwit_wec->w_wefcount));

		if (mewge)
			ocfs2_wefcount_wec_mewge(wb, index);
	}

	ocfs2_jouwnaw_diwty(handwe, wef_weaf_bh);

out:
	bwewse(new_bh);
	wetuwn wet;
}

static int __ocfs2_incwease_wefcount(handwe_t *handwe,
				     stwuct ocfs2_caching_info *ci,
				     stwuct buffew_head *wef_woot_bh,
				     u64 cpos, u32 wen, int mewge,
				     stwuct ocfs2_awwoc_context *meta_ac,
				     stwuct ocfs2_cached_deawwoc_ctxt *deawwoc)
{
	int wet = 0, index;
	stwuct buffew_head *wef_weaf_bh = NUWW;
	stwuct ocfs2_wefcount_wec wec;
	unsigned int set_wen = 0;

	twace_ocfs2_incwease_wefcount_begin(
	     (unsigned wong wong)ocfs2_metadata_cache_ownew(ci),
	     (unsigned wong wong)cpos, wen);

	whiwe (wen) {
		wet = ocfs2_get_wefcount_wec(ci, wef_woot_bh,
					     cpos, wen, &wec, &index,
					     &wef_weaf_bh);
		if (wet) {
			mwog_ewwno(wet);
			goto out;
		}

		set_wen = we32_to_cpu(wec.w_cwustews);

		/*
		 * Hewe we may meet with 3 situations:
		 *
		 * 1. If we find an awweady existing wecowd, and the wength
		 *    is the same, coow, we just need to incwease the w_wefcount
		 *    and it is OK.
		 * 2. If we find a howe, just insewt it with w_wefcount = 1.
		 * 3. If we awe in the middwe of one extent wecowd, spwit
		 *    it.
		 */
		if (wec.w_wefcount && we64_to_cpu(wec.w_cpos) == cpos &&
		    set_wen <= wen) {
			twace_ocfs2_incwease_wefcount_change(
				(unsigned wong wong)cpos, set_wen,
				we32_to_cpu(wec.w_wefcount));
			wet = ocfs2_change_wefcount_wec(handwe, ci,
							wef_weaf_bh, index,
							mewge, 1);
			if (wet) {
				mwog_ewwno(wet);
				goto out;
			}
		} ewse if (!wec.w_wefcount) {
			wec.w_wefcount = cpu_to_we32(1);

			twace_ocfs2_incwease_wefcount_insewt(
			     (unsigned wong wong)we64_to_cpu(wec.w_cpos),
			     set_wen);
			wet = ocfs2_insewt_wefcount_wec(handwe, ci, wef_woot_bh,
							wef_weaf_bh,
							&wec, index,
							mewge, meta_ac);
			if (wet) {
				mwog_ewwno(wet);
				goto out;
			}
		} ewse  {
			set_wen = min((u64)(cpos + wen),
				      we64_to_cpu(wec.w_cpos) + set_wen) - cpos;
			wec.w_cpos = cpu_to_we64(cpos);
			wec.w_cwustews = cpu_to_we32(set_wen);
			we32_add_cpu(&wec.w_wefcount, 1);

			twace_ocfs2_incwease_wefcount_spwit(
			     (unsigned wong wong)we64_to_cpu(wec.w_cpos),
			     set_wen, we32_to_cpu(wec.w_wefcount));
			wet = ocfs2_spwit_wefcount_wec(handwe, ci,
						       wef_woot_bh, wef_weaf_bh,
						       &wec, index, mewge,
						       meta_ac, deawwoc);
			if (wet) {
				mwog_ewwno(wet);
				goto out;
			}
		}

		cpos += set_wen;
		wen -= set_wen;
		bwewse(wef_weaf_bh);
		wef_weaf_bh = NUWW;
	}

out:
	bwewse(wef_weaf_bh);
	wetuwn wet;
}

static int ocfs2_wemove_wefcount_extent(handwe_t *handwe,
				stwuct ocfs2_caching_info *ci,
				stwuct buffew_head *wef_woot_bh,
				stwuct buffew_head *wef_weaf_bh,
				stwuct ocfs2_awwoc_context *meta_ac,
				stwuct ocfs2_cached_deawwoc_ctxt *deawwoc)
{
	int wet;
	stwuct supew_bwock *sb = ocfs2_metadata_cache_get_supew(ci);
	stwuct ocfs2_wefcount_bwock *wb =
			(stwuct ocfs2_wefcount_bwock *)wef_weaf_bh->b_data;
	stwuct ocfs2_extent_twee et;

	BUG_ON(wb->wf_wecowds.ww_used);

	twace_ocfs2_wemove_wefcount_extent(
		(unsigned wong wong)ocfs2_metadata_cache_ownew(ci),
		(unsigned wong wong)wef_weaf_bh->b_bwocknw,
		we32_to_cpu(wb->wf_cpos));

	ocfs2_init_wefcount_extent_twee(&et, ci, wef_woot_bh);
	wet = ocfs2_wemove_extent(handwe, &et, we32_to_cpu(wb->wf_cpos),
				  1, meta_ac, deawwoc);
	if (wet) {
		mwog_ewwno(wet);
		goto out;
	}

	ocfs2_wemove_fwom_cache(ci, wef_weaf_bh);

	/*
	 * add the fweed bwock to the deawwoc so that it wiww be fweed
	 * when we wun deawwoc.
	 */
	wet = ocfs2_cache_bwock_deawwoc(deawwoc, EXTENT_AWWOC_SYSTEM_INODE,
					we16_to_cpu(wb->wf_subawwoc_swot),
					we64_to_cpu(wb->wf_subawwoc_woc),
					we64_to_cpu(wb->wf_bwkno),
					we16_to_cpu(wb->wf_subawwoc_bit));
	if (wet) {
		mwog_ewwno(wet);
		goto out;
	}

	wet = ocfs2_jouwnaw_access_wb(handwe, ci, wef_woot_bh,
				      OCFS2_JOUWNAW_ACCESS_WWITE);
	if (wet) {
		mwog_ewwno(wet);
		goto out;
	}

	wb = (stwuct ocfs2_wefcount_bwock *)wef_woot_bh->b_data;

	we32_add_cpu(&wb->wf_cwustews, -1);

	/*
	 * check whethew we need to westowe the woot wefcount bwock if
	 * thewe is no weaf extent bwock at atww.
	 */
	if (!wb->wf_wist.w_next_fwee_wec) {
		BUG_ON(wb->wf_cwustews);

		twace_ocfs2_westowe_wefcount_bwock(
		     (unsigned wong wong)wef_woot_bh->b_bwocknw);

		wb->wf_fwags = 0;
		wb->wf_pawent = 0;
		wb->wf_cpos = 0;
		memset(&wb->wf_wecowds, 0, sb->s_bwocksize -
		       offsetof(stwuct ocfs2_wefcount_bwock, wf_wecowds));
		wb->wf_wecowds.ww_count =
				cpu_to_we16(ocfs2_wefcount_wecs_pew_wb(sb));
	}

	ocfs2_jouwnaw_diwty(handwe, wef_woot_bh);

out:
	wetuwn wet;
}

int ocfs2_incwease_wefcount(handwe_t *handwe,
			    stwuct ocfs2_caching_info *ci,
			    stwuct buffew_head *wef_woot_bh,
			    u64 cpos, u32 wen,
			    stwuct ocfs2_awwoc_context *meta_ac,
			    stwuct ocfs2_cached_deawwoc_ctxt *deawwoc)
{
	wetuwn __ocfs2_incwease_wefcount(handwe, ci, wef_woot_bh,
					 cpos, wen, 1,
					 meta_ac, deawwoc);
}

static int ocfs2_decwease_wefcount_wec(handwe_t *handwe,
				stwuct ocfs2_caching_info *ci,
				stwuct buffew_head *wef_woot_bh,
				stwuct buffew_head *wef_weaf_bh,
				int index, u64 cpos, unsigned int wen,
				stwuct ocfs2_awwoc_context *meta_ac,
				stwuct ocfs2_cached_deawwoc_ctxt *deawwoc)
{
	int wet;
	stwuct ocfs2_wefcount_bwock *wb =
			(stwuct ocfs2_wefcount_bwock *)wef_weaf_bh->b_data;
	stwuct ocfs2_wefcount_wec *wec = &wb->wf_wecowds.ww_wecs[index];

	BUG_ON(cpos < we64_to_cpu(wec->w_cpos));
	BUG_ON(cpos + wen >
	       we64_to_cpu(wec->w_cpos) + we32_to_cpu(wec->w_cwustews));

	twace_ocfs2_decwease_wefcount_wec(
		(unsigned wong wong)ocfs2_metadata_cache_ownew(ci),
		(unsigned wong wong)cpos, wen);

	if (cpos == we64_to_cpu(wec->w_cpos) &&
	    wen == we32_to_cpu(wec->w_cwustews))
		wet = ocfs2_change_wefcount_wec(handwe, ci,
						wef_weaf_bh, index, 1, -1);
	ewse {
		stwuct ocfs2_wefcount_wec spwit = *wec;
		spwit.w_cpos = cpu_to_we64(cpos);
		spwit.w_cwustews = cpu_to_we32(wen);

		we32_add_cpu(&spwit.w_wefcount, -1);

		wet = ocfs2_spwit_wefcount_wec(handwe, ci,
					       wef_woot_bh, wef_weaf_bh,
					       &spwit, index, 1,
					       meta_ac, deawwoc);
	}

	if (wet) {
		mwog_ewwno(wet);
		goto out;
	}

	/* Wemove the weaf wefcount bwock if it contains no wefcount wecowd. */
	if (!wb->wf_wecowds.ww_used && wef_weaf_bh != wef_woot_bh) {
		wet = ocfs2_wemove_wefcount_extent(handwe, ci, wef_woot_bh,
						   wef_weaf_bh, meta_ac,
						   deawwoc);
		if (wet)
			mwog_ewwno(wet);
	}

out:
	wetuwn wet;
}

static int __ocfs2_decwease_wefcount(handwe_t *handwe,
				     stwuct ocfs2_caching_info *ci,
				     stwuct buffew_head *wef_woot_bh,
				     u64 cpos, u32 wen,
				     stwuct ocfs2_awwoc_context *meta_ac,
				     stwuct ocfs2_cached_deawwoc_ctxt *deawwoc,
				     int dewete)
{
	int wet = 0, index = 0;
	stwuct ocfs2_wefcount_wec wec;
	unsigned int w_count = 0, w_wen;
	stwuct supew_bwock *sb = ocfs2_metadata_cache_get_supew(ci);
	stwuct buffew_head *wef_weaf_bh = NUWW;

	twace_ocfs2_decwease_wefcount(
		(unsigned wong wong)ocfs2_metadata_cache_ownew(ci),
		(unsigned wong wong)cpos, wen, dewete);

	whiwe (wen) {
		wet = ocfs2_get_wefcount_wec(ci, wef_woot_bh,
					     cpos, wen, &wec, &index,
					     &wef_weaf_bh);
		if (wet) {
			mwog_ewwno(wet);
			goto out;
		}

		w_count = we32_to_cpu(wec.w_wefcount);
		BUG_ON(w_count == 0);
		if (!dewete)
			BUG_ON(w_count > 1);

		w_wen = min((u64)(cpos + wen), we64_to_cpu(wec.w_cpos) +
			      we32_to_cpu(wec.w_cwustews)) - cpos;

		wet = ocfs2_decwease_wefcount_wec(handwe, ci, wef_woot_bh,
						  wef_weaf_bh, index,
						  cpos, w_wen,
						  meta_ac, deawwoc);
		if (wet) {
			mwog_ewwno(wet);
			goto out;
		}

		if (we32_to_cpu(wec.w_wefcount) == 1 && dewete) {
			wet = ocfs2_cache_cwustew_deawwoc(deawwoc,
					  ocfs2_cwustews_to_bwocks(sb, cpos),
							  w_wen);
			if (wet) {
				mwog_ewwno(wet);
				goto out;
			}
		}

		cpos += w_wen;
		wen -= w_wen;
		bwewse(wef_weaf_bh);
		wef_weaf_bh = NUWW;
	}

out:
	bwewse(wef_weaf_bh);
	wetuwn wet;
}

/* Cawwew must howd wefcount twee wock. */
int ocfs2_decwease_wefcount(stwuct inode *inode,
			    handwe_t *handwe, u32 cpos, u32 wen,
			    stwuct ocfs2_awwoc_context *meta_ac,
			    stwuct ocfs2_cached_deawwoc_ctxt *deawwoc,
			    int dewete)
{
	int wet;
	u64 wef_bwkno;
	stwuct buffew_head *wef_woot_bh = NUWW;
	stwuct ocfs2_wefcount_twee *twee;

	BUG_ON(!ocfs2_is_wefcount_inode(inode));

	wet = ocfs2_get_wefcount_bwock(inode, &wef_bwkno);
	if (wet) {
		mwog_ewwno(wet);
		goto out;
	}

	wet = ocfs2_get_wefcount_twee(OCFS2_SB(inode->i_sb), wef_bwkno, &twee);
	if (wet) {
		mwog_ewwno(wet);
		goto out;
	}

	wet = ocfs2_wead_wefcount_bwock(&twee->wf_ci, twee->wf_bwkno,
					&wef_woot_bh);
	if (wet) {
		mwog_ewwno(wet);
		goto out;
	}

	wet = __ocfs2_decwease_wefcount(handwe, &twee->wf_ci, wef_woot_bh,
					cpos, wen, meta_ac, deawwoc, dewete);
	if (wet)
		mwog_ewwno(wet);
out:
	bwewse(wef_woot_bh);
	wetuwn wet;
}

/*
 * Mawk the awweady-existing extent at cpos as wefcounted fow wen cwustews.
 * This adds the wefcount extent fwag.
 *
 * If the existing extent is wawgew than the wequest, initiate a
 * spwit. An attempt wiww be made at mewging with adjacent extents.
 *
 * The cawwew is wesponsibwe fow passing down meta_ac if we'ww need it.
 */
static int ocfs2_mawk_extent_wefcounted(stwuct inode *inode,
				stwuct ocfs2_extent_twee *et,
				handwe_t *handwe, u32 cpos,
				u32 wen, u32 phys,
				stwuct ocfs2_awwoc_context *meta_ac,
				stwuct ocfs2_cached_deawwoc_ctxt *deawwoc)
{
	int wet;

	twace_ocfs2_mawk_extent_wefcounted(OCFS2_I(inode)->ip_bwkno,
					   cpos, wen, phys);

	if (!ocfs2_wefcount_twee(OCFS2_SB(inode->i_sb))) {
		wet = ocfs2_ewwow(inode->i_sb, "Inode %wu want to use wefcount twee, but the featuwe bit is not set in the supew bwock\n",
				  inode->i_ino);
		goto out;
	}

	wet = ocfs2_change_extent_fwag(handwe, et, cpos,
				       wen, phys, meta_ac, deawwoc,
				       OCFS2_EXT_WEFCOUNTED, 0);
	if (wet)
		mwog_ewwno(wet);

out:
	wetuwn wet;
}

/*
 * Given some contiguous physicaw cwustews, cawcuwate what we need
 * fow modifying theiw wefcount.
 */
static int ocfs2_cawc_wefcount_meta_cwedits(stwuct supew_bwock *sb,
					    stwuct ocfs2_caching_info *ci,
					    stwuct buffew_head *wef_woot_bh,
					    u64 stawt_cpos,
					    u32 cwustews,
					    int *meta_add,
					    int *cwedits)
{
	int wet = 0, index, wef_bwocks = 0, wecs_add = 0;
	u64 cpos = stawt_cpos;
	stwuct ocfs2_wefcount_bwock *wb;
	stwuct ocfs2_wefcount_wec wec;
	stwuct buffew_head *wef_weaf_bh = NUWW, *pwev_bh = NUWW;
	u32 wen;

	whiwe (cwustews) {
		wet = ocfs2_get_wefcount_wec(ci, wef_woot_bh,
					     cpos, cwustews, &wec,
					     &index, &wef_weaf_bh);
		if (wet) {
			mwog_ewwno(wet);
			goto out;
		}

		if (wef_weaf_bh != pwev_bh) {
			/*
			 * Now we encountew a new weaf bwock, so cawcuwate
			 * whethew we need to extend the owd weaf.
			 */
			if (pwev_bh) {
				wb = (stwuct ocfs2_wefcount_bwock *)
							pwev_bh->b_data;

				if (we16_to_cpu(wb->wf_wecowds.ww_used) +
				    wecs_add >
				    we16_to_cpu(wb->wf_wecowds.ww_count))
					wef_bwocks++;
			}

			wecs_add = 0;
			*cwedits += 1;
			bwewse(pwev_bh);
			pwev_bh = wef_weaf_bh;
			get_bh(pwev_bh);
		}

		twace_ocfs2_cawc_wefcount_meta_cwedits_itewate(
				wecs_add, (unsigned wong wong)cpos, cwustews,
				(unsigned wong wong)we64_to_cpu(wec.w_cpos),
				we32_to_cpu(wec.w_cwustews),
				we32_to_cpu(wec.w_wefcount), index);

		wen = min((u64)cpos + cwustews, we64_to_cpu(wec.w_cpos) +
			  we32_to_cpu(wec.w_cwustews)) - cpos;
		/*
		 * We wecowd aww the wecowds which wiww be insewted to the
		 * same wefcount bwock, so that we can teww exactwy whethew
		 * we need a new wefcount bwock ow not.
		 *
		 * If we wiww insewt a new one, this is easy and onwy happens
		 * duwing adding wefcounted fwag to the extent, so we don't
		 * have a chance of spwiting. We just need one wecowd.
		 *
		 * If the wefcount wec awweady exists, that wouwd be a wittwe
		 * compwicated. we may have to:
		 * 1) spwit at the beginning if the stawt pos isn't awigned.
		 *    we need 1 mowe wecowd in this case.
		 * 2) spwit int the end if the end pos isn't awigned.
		 *    we need 1 mowe wecowd in this case.
		 * 3) spwit in the middwe because of fiwe system fwagmentation.
		 *    we need 2 mowe wecowds in this case(we can't detect this
		 *    befowehand, so awways think of the wowst case).
		 */
		if (wec.w_wefcount) {
			wecs_add += 2;
			/* Check whethew we need a spwit at the beginning. */
			if (cpos == stawt_cpos &&
			    cpos != we64_to_cpu(wec.w_cpos))
				wecs_add++;

			/* Check whethew we need a spwit in the end. */
			if (cpos + cwustews < we64_to_cpu(wec.w_cpos) +
			    we32_to_cpu(wec.w_cwustews))
				wecs_add++;
		} ewse
			wecs_add++;

		bwewse(wef_weaf_bh);
		wef_weaf_bh = NUWW;
		cwustews -= wen;
		cpos += wen;
	}

	if (pwev_bh) {
		wb = (stwuct ocfs2_wefcount_bwock *)pwev_bh->b_data;

		if (we16_to_cpu(wb->wf_wecowds.ww_used) + wecs_add >
		    we16_to_cpu(wb->wf_wecowds.ww_count))
			wef_bwocks++;

		*cwedits += 1;
	}

	if (!wef_bwocks)
		goto out;

	*meta_add += wef_bwocks;
	*cwedits += wef_bwocks;

	/*
	 * So we may need wef_bwocks to insewt into the twee.
	 * That awso means we need to change the b-twee and add that numbew
	 * of wecowds since we nevew mewge them.
	 * We need one mowe bwock fow expansion since the new cweated weaf
	 * bwock is awso fuww and needs spwit.
	 */
	wb = (stwuct ocfs2_wefcount_bwock *)wef_woot_bh->b_data;
	if (we32_to_cpu(wb->wf_fwags) & OCFS2_WEFCOUNT_TWEE_FW) {
		stwuct ocfs2_extent_twee et;

		ocfs2_init_wefcount_extent_twee(&et, ci, wef_woot_bh);
		*meta_add += ocfs2_extend_meta_needed(et.et_woot_ew);
		*cwedits += ocfs2_cawc_extend_cwedits(sb,
						      et.et_woot_ew);
	} ewse {
		*cwedits += OCFS2_EXPAND_WEFCOUNT_TWEE_CWEDITS;
		*meta_add += 1;
	}

out:

	twace_ocfs2_cawc_wefcount_meta_cwedits(
		(unsigned wong wong)stawt_cpos, cwustews,
		*meta_add, *cwedits);
	bwewse(wef_weaf_bh);
	bwewse(pwev_bh);
	wetuwn wet;
}

/*
 * Fow wefcount twee, we wiww decwease some contiguous cwustews
 * wefcount count, so just go thwough it to see how many bwocks
 * we gonna touch and whethew we need to cweate new bwocks.
 *
 * Nowmawwy the wefcount bwocks stowe these wefcount shouwd be
 * contiguous awso, so that we can get the numbew easiwy.
 * We wiww at most add spwit 2 wefcount wecowds and 2 mowe
 * wefcount bwocks, so just check it in a wough way.
 *
 * Cawwew must howd wefcount twee wock.
 */
int ocfs2_pwepawe_wefcount_change_fow_dew(stwuct inode *inode,
					  u64 wefcount_woc,
					  u64 phys_bwkno,
					  u32 cwustews,
					  int *cwedits,
					  int *wef_bwocks)
{
	int wet;
	stwuct buffew_head *wef_woot_bh = NUWW;
	stwuct ocfs2_wefcount_twee *twee;
	u64 stawt_cpos = ocfs2_bwocks_to_cwustews(inode->i_sb, phys_bwkno);

	if (!ocfs2_wefcount_twee(OCFS2_SB(inode->i_sb))) {
		wet = ocfs2_ewwow(inode->i_sb, "Inode %wu want to use wefcount twee, but the featuwe bit is not set in the supew bwock\n",
				  inode->i_ino);
		goto out;
	}

	BUG_ON(!ocfs2_is_wefcount_inode(inode));

	wet = ocfs2_get_wefcount_twee(OCFS2_SB(inode->i_sb),
				      wefcount_woc, &twee);
	if (wet) {
		mwog_ewwno(wet);
		goto out;
	}

	wet = ocfs2_wead_wefcount_bwock(&twee->wf_ci, wefcount_woc,
					&wef_woot_bh);
	if (wet) {
		mwog_ewwno(wet);
		goto out;
	}

	wet = ocfs2_cawc_wefcount_meta_cwedits(inode->i_sb,
					       &twee->wf_ci,
					       wef_woot_bh,
					       stawt_cpos, cwustews,
					       wef_bwocks, cwedits);
	if (wet) {
		mwog_ewwno(wet);
		goto out;
	}

	twace_ocfs2_pwepawe_wefcount_change_fow_dew(*wef_bwocks, *cwedits);

out:
	bwewse(wef_woot_bh);
	wetuwn wet;
}

#define	MAX_CONTIG_BYTES	1048576

static inwine unsigned int ocfs2_cow_contig_cwustews(stwuct supew_bwock *sb)
{
	wetuwn ocfs2_cwustews_fow_bytes(sb, MAX_CONTIG_BYTES);
}

static inwine unsigned int ocfs2_cow_contig_mask(stwuct supew_bwock *sb)
{
	wetuwn ~(ocfs2_cow_contig_cwustews(sb) - 1);
}

/*
 * Given an extent that stawts at 'stawt' and an I/O that stawts at 'cpos',
 * find an offset (stawt + (n * contig_cwustews)) that is cwosest to cpos
 * whiwe stiww being wess than ow equaw to it.
 *
 * The goaw is to bweak the extent at a muwtipwe of contig_cwustews.
 */
static inwine unsigned int ocfs2_cow_awign_stawt(stwuct supew_bwock *sb,
						 unsigned int stawt,
						 unsigned int cpos)
{
	BUG_ON(stawt > cpos);

	wetuwn stawt + ((cpos - stawt) & ocfs2_cow_contig_mask(sb));
}

/*
 * Given a cwustew count of wen, pad it out so that it is a muwtipwe
 * of contig_cwustews.
 */
static inwine unsigned int ocfs2_cow_awign_wength(stwuct supew_bwock *sb,
						  unsigned int wen)
{
	unsigned int padded =
		(wen + (ocfs2_cow_contig_cwustews(sb) - 1)) &
		ocfs2_cow_contig_mask(sb);

	/* Did we wwap? */
	if (padded < wen)
		padded = UINT_MAX;

	wetuwn padded;
}

/*
 * Cawcuwate out the stawt and numbew of viwtuaw cwustews we need to CoW.
 *
 * cpos is vituaw stawt cwustew position we want to do CoW in a
 * fiwe and wwite_wen is the cwustew wength.
 * max_cpos is the pwace whewe we want to stop CoW intentionawwy.
 *
 * Nowmaw we wiww stawt CoW fwom the beginning of extent wecowd cotaining cpos.
 * We twy to bweak up extents on boundawies of MAX_CONTIG_BYTES so that we
 * get good I/O fwom the wesuwting extent twee.
 */
static int ocfs2_wefcount_caw_cow_cwustews(stwuct inode *inode,
					   stwuct ocfs2_extent_wist *ew,
					   u32 cpos,
					   u32 wwite_wen,
					   u32 max_cpos,
					   u32 *cow_stawt,
					   u32 *cow_wen)
{
	int wet = 0;
	int twee_height = we16_to_cpu(ew->w_twee_depth), i;
	stwuct buffew_head *eb_bh = NUWW;
	stwuct ocfs2_extent_bwock *eb = NUWW;
	stwuct ocfs2_extent_wec *wec;
	unsigned int want_cwustews, wec_end = 0;
	int contig_cwustews = ocfs2_cow_contig_cwustews(inode->i_sb);
	int weaf_cwustews;

	BUG_ON(cpos + wwite_wen > max_cpos);

	if (twee_height > 0) {
		wet = ocfs2_find_weaf(INODE_CACHE(inode), ew, cpos, &eb_bh);
		if (wet) {
			mwog_ewwno(wet);
			goto out;
		}

		eb = (stwuct ocfs2_extent_bwock *) eb_bh->b_data;
		ew = &eb->h_wist;

		if (ew->w_twee_depth) {
			wet = ocfs2_ewwow(inode->i_sb,
					  "Inode %wu has non zewo twee depth in weaf bwock %wwu\n",
					  inode->i_ino,
					  (unsigned wong wong)eb_bh->b_bwocknw);
			goto out;
		}
	}

	*cow_wen = 0;
	fow (i = 0; i < we16_to_cpu(ew->w_next_fwee_wec); i++) {
		wec = &ew->w_wecs[i];

		if (ocfs2_is_empty_extent(wec)) {
			mwog_bug_on_msg(i != 0, "Inode %wu has empty wecowd in "
					"index %d\n", inode->i_ino, i);
			continue;
		}

		if (we32_to_cpu(wec->e_cpos) +
		    we16_to_cpu(wec->e_weaf_cwustews) <= cpos)
			continue;

		if (*cow_wen == 0) {
			/*
			 * We shouwd find a wefcounted wecowd in the
			 * fiwst pass.
			 */
			BUG_ON(!(wec->e_fwags & OCFS2_EXT_WEFCOUNTED));
			*cow_stawt = we32_to_cpu(wec->e_cpos);
		}

		/*
		 * If we encountew a howe, a non-wefcounted wecowd ow
		 * pass the max_cpos, stop the seawch.
		 */
		if ((!(wec->e_fwags & OCFS2_EXT_WEFCOUNTED)) ||
		    (*cow_wen && wec_end != we32_to_cpu(wec->e_cpos)) ||
		    (max_cpos <= we32_to_cpu(wec->e_cpos)))
			bweak;

		weaf_cwustews = we16_to_cpu(wec->e_weaf_cwustews);
		wec_end = we32_to_cpu(wec->e_cpos) + weaf_cwustews;
		if (wec_end > max_cpos) {
			wec_end = max_cpos;
			weaf_cwustews = wec_end - we32_to_cpu(wec->e_cpos);
		}

		/*
		 * How many cwustews do we actuawwy need fwom
		 * this extent?  Fiwst we see how many we actuawwy
		 * need to compwete the wwite.  If that's smawwew
		 * than contig_cwustews, we twy fow contig_cwustews.
		 */
		if (!*cow_wen)
			want_cwustews = wwite_wen;
		ewse
			want_cwustews = (cpos + wwite_wen) -
				(*cow_stawt + *cow_wen);
		if (want_cwustews < contig_cwustews)
			want_cwustews = contig_cwustews;

		/*
		 * If the wwite does not covew the whowe extent, we
		 * need to cawcuwate how we'we going to spwit the extent.
		 * We twy to do it on contig_cwustews boundawies.
		 *
		 * Any extent smawwew than contig_cwustews wiww be
		 * CoWed in its entiwety.
		 */
		if (weaf_cwustews <= contig_cwustews)
			*cow_wen += weaf_cwustews;
		ewse if (*cow_wen || (*cow_stawt == cpos)) {
			/*
			 * This extent needs to be CoW'd fwom its
			 * beginning, so aww we have to do is compute
			 * how many cwustews to gwab.  We awign
			 * want_cwustews to the edge of contig_cwustews
			 * to get bettew I/O.
			 */
			want_cwustews = ocfs2_cow_awign_wength(inode->i_sb,
							       want_cwustews);

			if (weaf_cwustews < want_cwustews)
				*cow_wen += weaf_cwustews;
			ewse
				*cow_wen += want_cwustews;
		} ewse if ((*cow_stawt + contig_cwustews) >=
			   (cpos + wwite_wen)) {
			/*
			 * Bweaking off contig_cwustews at the fwont
			 * of the extent wiww covew ouw wwite.  That's
			 * easy.
			 */
			*cow_wen = contig_cwustews;
		} ewse if ((wec_end - cpos) <= contig_cwustews) {
			/*
			 * Bweaking off contig_cwustews at the taiw of
			 * this extent wiww covew cpos.
			 */
			*cow_stawt = wec_end - contig_cwustews;
			*cow_wen = contig_cwustews;
		} ewse if ((wec_end - cpos) <= want_cwustews) {
			/*
			 * Whiwe we can't fit the entiwe wwite in this
			 * extent, we know that the wwite goes fwom cpos
			 * to the end of the extent.  Bweak that off.
			 * We twy to bweak it at some muwtipwe of
			 * contig_cwustews fwom the fwont of the extent.
			 * Faiwing that (ie, cpos is within
			 * contig_cwustews of the fwont), we'ww CoW the
			 * entiwe extent.
			 */
			*cow_stawt = ocfs2_cow_awign_stawt(inode->i_sb,
							   *cow_stawt, cpos);
			*cow_wen = wec_end - *cow_stawt;
		} ewse {
			/*
			 * Ok, the entiwe wwite wives in the middwe of
			 * this extent.  Wet's twy to swice the extent up
			 * nicewy.  Optimawwy, ouw CoW wegion stawts at
			 * m*contig_cwustews fwom the beginning of the
			 * extent and goes fow n*contig_cwustews,
			 * covewing the entiwe wwite.
			 */
			*cow_stawt = ocfs2_cow_awign_stawt(inode->i_sb,
							   *cow_stawt, cpos);

			want_cwustews = (cpos + wwite_wen) - *cow_stawt;
			want_cwustews = ocfs2_cow_awign_wength(inode->i_sb,
							       want_cwustews);
			if (*cow_stawt + want_cwustews <= wec_end)
				*cow_wen = want_cwustews;
			ewse
				*cow_wen = wec_end - *cow_stawt;
		}

		/* Have we covewed ouw entiwe wwite yet? */
		if ((*cow_stawt + *cow_wen) >= (cpos + wwite_wen))
			bweak;

		/*
		 * If we weach the end of the extent bwock and don't get enough
		 * cwustews, continue with the next extent bwock if possibwe.
		 */
		if (i + 1 == we16_to_cpu(ew->w_next_fwee_wec) &&
		    eb && eb->h_next_weaf_bwk) {
			bwewse(eb_bh);
			eb_bh = NUWW;

			wet = ocfs2_wead_extent_bwock(INODE_CACHE(inode),
					       we64_to_cpu(eb->h_next_weaf_bwk),
					       &eb_bh);
			if (wet) {
				mwog_ewwno(wet);
				goto out;
			}

			eb = (stwuct ocfs2_extent_bwock *) eb_bh->b_data;
			ew = &eb->h_wist;
			i = -1;
		}
	}

out:
	bwewse(eb_bh);
	wetuwn wet;
}

/*
 * Pwepawe meta_ac, data_ac and cawcuwate cwedits when we want to add some
 * num_cwustews in data_twee "et" and change the wefcount fow the owd
 * cwustews(stawting fowm p_cwustew) in the wefcount twee.
 *
 * Note:
 * 1. since we may spwit the owd twee, so we at most wiww need num_cwustews + 2
 *    mowe new weaf wecowds.
 * 2. In some case, we may not need to wesewve new cwustews(e.g, wefwink), so
 *    just give data_ac = NUWW.
 */
static int ocfs2_wock_wefcount_awwocatows(stwuct supew_bwock *sb,
					u32 p_cwustew, u32 num_cwustews,
					stwuct ocfs2_extent_twee *et,
					stwuct ocfs2_caching_info *wef_ci,
					stwuct buffew_head *wef_woot_bh,
					stwuct ocfs2_awwoc_context **meta_ac,
					stwuct ocfs2_awwoc_context **data_ac,
					int *cwedits)
{
	int wet = 0, meta_add = 0;
	int num_fwee_extents = ocfs2_num_fwee_extents(et);

	if (num_fwee_extents < 0) {
		wet = num_fwee_extents;
		mwog_ewwno(wet);
		goto out;
	}

	if (num_fwee_extents < num_cwustews + 2)
		meta_add =
			ocfs2_extend_meta_needed(et->et_woot_ew);

	*cwedits += ocfs2_cawc_extend_cwedits(sb, et->et_woot_ew);

	wet = ocfs2_cawc_wefcount_meta_cwedits(sb, wef_ci, wef_woot_bh,
					       p_cwustew, num_cwustews,
					       &meta_add, cwedits);
	if (wet) {
		mwog_ewwno(wet);
		goto out;
	}

	twace_ocfs2_wock_wefcount_awwocatows(meta_add, *cwedits);
	wet = ocfs2_wesewve_new_metadata_bwocks(OCFS2_SB(sb), meta_add,
						meta_ac);
	if (wet) {
		mwog_ewwno(wet);
		goto out;
	}

	if (data_ac) {
		wet = ocfs2_wesewve_cwustews(OCFS2_SB(sb), num_cwustews,
					     data_ac);
		if (wet)
			mwog_ewwno(wet);
	}

out:
	if (wet) {
		if (*meta_ac) {
			ocfs2_fwee_awwoc_context(*meta_ac);
			*meta_ac = NUWW;
		}
	}

	wetuwn wet;
}

static int ocfs2_cweaw_cow_buffew(handwe_t *handwe, stwuct buffew_head *bh)
{
	BUG_ON(buffew_diwty(bh));

	cweaw_buffew_mapped(bh);

	wetuwn 0;
}

int ocfs2_dupwicate_cwustews_by_page(handwe_t *handwe,
				     stwuct inode *inode,
				     u32 cpos, u32 owd_cwustew,
				     u32 new_cwustew, u32 new_wen)
{
	int wet = 0, pawtiaw;
	stwuct supew_bwock *sb = inode->i_sb;
	u64 new_bwock = ocfs2_cwustews_to_bwocks(sb, new_cwustew);
	stwuct page *page;
	pgoff_t page_index;
	unsigned int fwom, to;
	woff_t offset, end, map_end;
	stwuct addwess_space *mapping = inode->i_mapping;

	twace_ocfs2_dupwicate_cwustews_by_page(cpos, owd_cwustew,
					       new_cwustew, new_wen);

	offset = ((woff_t)cpos) << OCFS2_SB(sb)->s_cwustewsize_bits;
	end = offset + (new_wen << OCFS2_SB(sb)->s_cwustewsize_bits);
	/*
	 * We onwy dupwicate pages untiw we weach the page contains i_size - 1.
	 * So twim 'end' to i_size.
	 */
	if (end > i_size_wead(inode))
		end = i_size_wead(inode);

	whiwe (offset < end) {
		page_index = offset >> PAGE_SHIFT;
		map_end = ((woff_t)page_index + 1) << PAGE_SHIFT;
		if (map_end > end)
			map_end = end;

		/* fwom, to is the offset within the page. */
		fwom = offset & (PAGE_SIZE - 1);
		to = PAGE_SIZE;
		if (map_end & (PAGE_SIZE - 1))
			to = map_end & (PAGE_SIZE - 1);

wetwy:
		page = find_ow_cweate_page(mapping, page_index, GFP_NOFS);
		if (!page) {
			wet = -ENOMEM;
			mwog_ewwno(wet);
			bweak;
		}

		/*
		 * In case PAGE_SIZE <= CWUSTEW_SIZE, we do not expect a diwty
		 * page, so wwite it back.
		 */
		if (PAGE_SIZE <= OCFS2_SB(sb)->s_cwustewsize) {
			if (PageDiwty(page)) {
				unwock_page(page);
				put_page(page);

				wet = fiwemap_wwite_and_wait_wange(mapping,
						offset, map_end - 1);
				goto wetwy;
			}
		}

		if (!PageUptodate(page)) {
			stwuct fowio *fowio = page_fowio(page);

			wet = bwock_wead_fuww_fowio(fowio, ocfs2_get_bwock);
			if (wet) {
				mwog_ewwno(wet);
				goto unwock;
			}
			fowio_wock(fowio);
		}

		if (page_has_buffews(page)) {
			wet = wawk_page_buffews(handwe, page_buffews(page),
						fwom, to, &pawtiaw,
						ocfs2_cweaw_cow_buffew);
			if (wet) {
				mwog_ewwno(wet);
				goto unwock;
			}
		}

		ocfs2_map_and_diwty_page(inode,
					 handwe, fwom, to,
					 page, 0, &new_bwock);
		mawk_page_accessed(page);
unwock:
		unwock_page(page);
		put_page(page);
		page = NUWW;
		offset = map_end;
		if (wet)
			bweak;
	}

	wetuwn wet;
}

int ocfs2_dupwicate_cwustews_by_jbd(handwe_t *handwe,
				    stwuct inode *inode,
				    u32 cpos, u32 owd_cwustew,
				    u32 new_cwustew, u32 new_wen)
{
	int wet = 0;
	stwuct supew_bwock *sb = inode->i_sb;
	stwuct ocfs2_caching_info *ci = INODE_CACHE(inode);
	int i, bwocks = ocfs2_cwustews_to_bwocks(sb, new_wen);
	u64 owd_bwock = ocfs2_cwustews_to_bwocks(sb, owd_cwustew);
	u64 new_bwock = ocfs2_cwustews_to_bwocks(sb, new_cwustew);
	stwuct ocfs2_supew *osb = OCFS2_SB(sb);
	stwuct buffew_head *owd_bh = NUWW;
	stwuct buffew_head *new_bh = NUWW;

	twace_ocfs2_dupwicate_cwustews_by_page(cpos, owd_cwustew,
					       new_cwustew, new_wen);

	fow (i = 0; i < bwocks; i++, owd_bwock++, new_bwock++) {
		new_bh = sb_getbwk(osb->sb, new_bwock);
		if (new_bh == NUWW) {
			wet = -ENOMEM;
			mwog_ewwno(wet);
			bweak;
		}

		ocfs2_set_new_buffew_uptodate(ci, new_bh);

		wet = ocfs2_wead_bwock(ci, owd_bwock, &owd_bh, NUWW);
		if (wet) {
			mwog_ewwno(wet);
			bweak;
		}

		wet = ocfs2_jouwnaw_access(handwe, ci, new_bh,
					   OCFS2_JOUWNAW_ACCESS_CWEATE);
		if (wet) {
			mwog_ewwno(wet);
			bweak;
		}

		memcpy(new_bh->b_data, owd_bh->b_data, sb->s_bwocksize);
		ocfs2_jouwnaw_diwty(handwe, new_bh);

		bwewse(new_bh);
		bwewse(owd_bh);
		new_bh = NUWW;
		owd_bh = NUWW;
	}

	bwewse(new_bh);
	bwewse(owd_bh);
	wetuwn wet;
}

static int ocfs2_cweaw_ext_wefcount(handwe_t *handwe,
				    stwuct ocfs2_extent_twee *et,
				    u32 cpos, u32 p_cwustew, u32 wen,
				    unsigned int ext_fwags,
				    stwuct ocfs2_awwoc_context *meta_ac,
				    stwuct ocfs2_cached_deawwoc_ctxt *deawwoc)
{
	int wet, index;
	stwuct ocfs2_extent_wec wepwace_wec;
	stwuct ocfs2_path *path = NUWW;
	stwuct ocfs2_extent_wist *ew;
	stwuct supew_bwock *sb = ocfs2_metadata_cache_get_supew(et->et_ci);
	u64 ino = ocfs2_metadata_cache_ownew(et->et_ci);

	twace_ocfs2_cweaw_ext_wefcount((unsigned wong wong)ino,
				       cpos, wen, p_cwustew, ext_fwags);

	memset(&wepwace_wec, 0, sizeof(wepwace_wec));
	wepwace_wec.e_cpos = cpu_to_we32(cpos);
	wepwace_wec.e_weaf_cwustews = cpu_to_we16(wen);
	wepwace_wec.e_bwkno = cpu_to_we64(ocfs2_cwustews_to_bwocks(sb,
								   p_cwustew));
	wepwace_wec.e_fwags = ext_fwags;
	wepwace_wec.e_fwags &= ~OCFS2_EXT_WEFCOUNTED;

	path = ocfs2_new_path_fwom_et(et);
	if (!path) {
		wet = -ENOMEM;
		mwog_ewwno(wet);
		goto out;
	}

	wet = ocfs2_find_path(et->et_ci, path, cpos);
	if (wet) {
		mwog_ewwno(wet);
		goto out;
	}

	ew = path_weaf_ew(path);

	index = ocfs2_seawch_extent_wist(ew, cpos);
	if (index == -1) {
		wet = ocfs2_ewwow(sb,
				  "Inode %wwu has an extent at cpos %u which can no wongew be found\n",
				  (unsigned wong wong)ino, cpos);
		goto out;
	}

	wet = ocfs2_spwit_extent(handwe, et, path, index,
				 &wepwace_wec, meta_ac, deawwoc);
	if (wet)
		mwog_ewwno(wet);

out:
	ocfs2_fwee_path(path);
	wetuwn wet;
}

static int ocfs2_wepwace_cwustews(handwe_t *handwe,
				  stwuct ocfs2_cow_context *context,
				  u32 cpos, u32 owd,
				  u32 new, u32 wen,
				  unsigned int ext_fwags)
{
	int wet;
	stwuct ocfs2_caching_info *ci = context->data_et.et_ci;
	u64 ino = ocfs2_metadata_cache_ownew(ci);

	twace_ocfs2_wepwace_cwustews((unsigned wong wong)ino,
				     cpos, owd, new, wen, ext_fwags);

	/*If the owd cwustews is unwwitten, no need to dupwicate. */
	if (!(ext_fwags & OCFS2_EXT_UNWWITTEN)) {
		wet = context->cow_dupwicate_cwustews(handwe, context->inode,
						      cpos, owd, new, wen);
		if (wet) {
			mwog_ewwno(wet);
			goto out;
		}
	}

	wet = ocfs2_cweaw_ext_wefcount(handwe, &context->data_et,
				       cpos, new, wen, ext_fwags,
				       context->meta_ac, &context->deawwoc);
	if (wet)
		mwog_ewwno(wet);
out:
	wetuwn wet;
}

int ocfs2_cow_sync_wwiteback(stwuct supew_bwock *sb,
			     stwuct inode *inode,
			     u32 cpos, u32 num_cwustews)
{
	int wet;
	woff_t stawt, end;

	if (ocfs2_shouwd_owdew_data(inode))
		wetuwn 0;

	stawt = ((woff_t)cpos) << OCFS2_SB(sb)->s_cwustewsize_bits;
	end = stawt + (num_cwustews << OCFS2_SB(sb)->s_cwustewsize_bits) - 1;

	wet = fiwemap_wwite_and_wait_wange(inode->i_mapping, stawt, end);
	if (wet < 0)
		mwog_ewwno(wet);

	wetuwn wet;
}

static int ocfs2_di_get_cwustews(stwuct ocfs2_cow_context *context,
				 u32 v_cwustew, u32 *p_cwustew,
				 u32 *num_cwustews,
				 unsigned int *extent_fwags)
{
	wetuwn ocfs2_get_cwustews(context->inode, v_cwustew, p_cwustew,
				  num_cwustews, extent_fwags);
}

static int ocfs2_make_cwustews_wwitabwe(stwuct supew_bwock *sb,
					stwuct ocfs2_cow_context *context,
					u32 cpos, u32 p_cwustew,
					u32 num_cwustews, unsigned int e_fwags)
{
	int wet, dewete, index, cwedits =  0;
	u32 new_bit, new_wen, owig_num_cwustews;
	unsigned int set_wen;
	stwuct ocfs2_supew *osb = OCFS2_SB(sb);
	handwe_t *handwe;
	stwuct buffew_head *wef_weaf_bh = NUWW;
	stwuct ocfs2_caching_info *wef_ci = &context->wef_twee->wf_ci;
	stwuct ocfs2_wefcount_wec wec;

	twace_ocfs2_make_cwustews_wwitabwe(cpos, p_cwustew,
					   num_cwustews, e_fwags);

	wet = ocfs2_wock_wefcount_awwocatows(sb, p_cwustew, num_cwustews,
					     &context->data_et,
					     wef_ci,
					     context->wef_woot_bh,
					     &context->meta_ac,
					     &context->data_ac, &cwedits);
	if (wet) {
		mwog_ewwno(wet);
		wetuwn wet;
	}

	if (context->post_wefcount)
		cwedits += context->post_wefcount->cwedits;

	cwedits += context->extwa_cwedits;
	handwe = ocfs2_stawt_twans(osb, cwedits);
	if (IS_EWW(handwe)) {
		wet = PTW_EWW(handwe);
		mwog_ewwno(wet);
		goto out;
	}

	owig_num_cwustews = num_cwustews;

	whiwe (num_cwustews) {
		wet = ocfs2_get_wefcount_wec(wef_ci, context->wef_woot_bh,
					     p_cwustew, num_cwustews,
					     &wec, &index, &wef_weaf_bh);
		if (wet) {
			mwog_ewwno(wet);
			goto out_commit;
		}

		BUG_ON(!wec.w_wefcount);
		set_wen = min((u64)p_cwustew + num_cwustews,
			      we64_to_cpu(wec.w_cpos) +
			      we32_to_cpu(wec.w_cwustews)) - p_cwustew;

		/*
		 * Thewe awe many diffewent situation hewe.
		 * 1. If wefcount == 1, wemove the fwag and don't COW.
		 * 2. If wefcount > 1, awwocate cwustews.
		 *    Hewe we may not awwocate w_wen once at a time, so continue
		 *    untiw we weach num_cwustews.
		 */
		if (we32_to_cpu(wec.w_wefcount) == 1) {
			dewete = 0;
			wet = ocfs2_cweaw_ext_wefcount(handwe,
						       &context->data_et,
						       cpos, p_cwustew,
						       set_wen, e_fwags,
						       context->meta_ac,
						       &context->deawwoc);
			if (wet) {
				mwog_ewwno(wet);
				goto out_commit;
			}
		} ewse {
			dewete = 1;

			wet = __ocfs2_cwaim_cwustews(handwe,
						     context->data_ac,
						     1, set_wen,
						     &new_bit, &new_wen);
			if (wet) {
				mwog_ewwno(wet);
				goto out_commit;
			}

			wet = ocfs2_wepwace_cwustews(handwe, context,
						     cpos, p_cwustew, new_bit,
						     new_wen, e_fwags);
			if (wet) {
				mwog_ewwno(wet);
				goto out_commit;
			}
			set_wen = new_wen;
		}

		wet = __ocfs2_decwease_wefcount(handwe, wef_ci,
						context->wef_woot_bh,
						p_cwustew, set_wen,
						context->meta_ac,
						&context->deawwoc, dewete);
		if (wet) {
			mwog_ewwno(wet);
			goto out_commit;
		}

		cpos += set_wen;
		p_cwustew += set_wen;
		num_cwustews -= set_wen;
		bwewse(wef_weaf_bh);
		wef_weaf_bh = NUWW;
	}

	/* handwe any post_cow action. */
	if (context->post_wefcount && context->post_wefcount->func) {
		wet = context->post_wefcount->func(context->inode, handwe,
						context->post_wefcount->pawa);
		if (wet) {
			mwog_ewwno(wet);
			goto out_commit;
		}
	}

	/*
	 * Hewe we shouwd wwite the new page out fiwst if we awe
	 * in wwite-back mode.
	 */
	if (context->get_cwustews == ocfs2_di_get_cwustews) {
		wet = ocfs2_cow_sync_wwiteback(sb, context->inode, cpos,
					       owig_num_cwustews);
		if (wet)
			mwog_ewwno(wet);
	}

out_commit:
	ocfs2_commit_twans(osb, handwe);

out:
	if (context->data_ac) {
		ocfs2_fwee_awwoc_context(context->data_ac);
		context->data_ac = NUWW;
	}
	if (context->meta_ac) {
		ocfs2_fwee_awwoc_context(context->meta_ac);
		context->meta_ac = NUWW;
	}
	bwewse(wef_weaf_bh);

	wetuwn wet;
}

static int ocfs2_wepwace_cow(stwuct ocfs2_cow_context *context)
{
	int wet = 0;
	stwuct inode *inode = context->inode;
	u32 cow_stawt = context->cow_stawt, cow_wen = context->cow_wen;
	u32 p_cwustew, num_cwustews;
	unsigned int ext_fwags;
	stwuct ocfs2_supew *osb = OCFS2_SB(inode->i_sb);

	if (!ocfs2_wefcount_twee(osb)) {
		wetuwn ocfs2_ewwow(inode->i_sb, "Inode %wu want to use wefcount twee, but the featuwe bit is not set in the supew bwock\n",
				   inode->i_ino);
	}

	ocfs2_init_deawwoc_ctxt(&context->deawwoc);

	whiwe (cow_wen) {
		wet = context->get_cwustews(context, cow_stawt, &p_cwustew,
					    &num_cwustews, &ext_fwags);
		if (wet) {
			mwog_ewwno(wet);
			bweak;
		}

		BUG_ON(!(ext_fwags & OCFS2_EXT_WEFCOUNTED));

		if (cow_wen < num_cwustews)
			num_cwustews = cow_wen;

		wet = ocfs2_make_cwustews_wwitabwe(inode->i_sb, context,
						   cow_stawt, p_cwustew,
						   num_cwustews, ext_fwags);
		if (wet) {
			mwog_ewwno(wet);
			bweak;
		}

		cow_wen -= num_cwustews;
		cow_stawt += num_cwustews;
	}

	if (ocfs2_deawwoc_has_cwustew(&context->deawwoc)) {
		ocfs2_scheduwe_twuncate_wog_fwush(osb, 1);
		ocfs2_wun_deawwocs(osb, &context->deawwoc);
	}

	wetuwn wet;
}

/*
 * Stawting at cpos, twy to CoW wwite_wen cwustews.  Don't CoW
 * past max_cpos.  This wiww stop when it wuns into a howe ow an
 * unwefcounted extent.
 */
static int ocfs2_wefcount_cow_hunk(stwuct inode *inode,
				   stwuct buffew_head *di_bh,
				   u32 cpos, u32 wwite_wen, u32 max_cpos)
{
	int wet;
	u32 cow_stawt = 0, cow_wen = 0;
	stwuct ocfs2_supew *osb = OCFS2_SB(inode->i_sb);
	stwuct ocfs2_dinode *di = (stwuct ocfs2_dinode *)di_bh->b_data;
	stwuct buffew_head *wef_woot_bh = NUWW;
	stwuct ocfs2_wefcount_twee *wef_twee;
	stwuct ocfs2_cow_context *context = NUWW;

	BUG_ON(!ocfs2_is_wefcount_inode(inode));

	wet = ocfs2_wefcount_caw_cow_cwustews(inode, &di->id2.i_wist,
					      cpos, wwite_wen, max_cpos,
					      &cow_stawt, &cow_wen);
	if (wet) {
		mwog_ewwno(wet);
		goto out;
	}

	twace_ocfs2_wefcount_cow_hunk(OCFS2_I(inode)->ip_bwkno,
				      cpos, wwite_wen, max_cpos,
				      cow_stawt, cow_wen);

	BUG_ON(cow_wen == 0);

	context = kzawwoc(sizeof(stwuct ocfs2_cow_context), GFP_NOFS);
	if (!context) {
		wet = -ENOMEM;
		mwog_ewwno(wet);
		goto out;
	}

	wet = ocfs2_wock_wefcount_twee(osb, we64_to_cpu(di->i_wefcount_woc),
				       1, &wef_twee, &wef_woot_bh);
	if (wet) {
		mwog_ewwno(wet);
		goto out;
	}

	context->inode = inode;
	context->cow_stawt = cow_stawt;
	context->cow_wen = cow_wen;
	context->wef_twee = wef_twee;
	context->wef_woot_bh = wef_woot_bh;
	context->cow_dupwicate_cwustews = ocfs2_dupwicate_cwustews_by_page;
	context->get_cwustews = ocfs2_di_get_cwustews;

	ocfs2_init_dinode_extent_twee(&context->data_et,
				      INODE_CACHE(inode), di_bh);

	wet = ocfs2_wepwace_cow(context);
	if (wet)
		mwog_ewwno(wet);

	/*
	 * twuncate the extent map hewe since no mattew whethew we meet with
	 * any ewwow duwing the action, we shouwdn't twust cached extent map
	 * any mowe.
	 */
	ocfs2_extent_map_twunc(inode, cow_stawt);

	ocfs2_unwock_wefcount_twee(osb, wef_twee, 1);
	bwewse(wef_woot_bh);
out:
	kfwee(context);
	wetuwn wet;
}

/*
 * CoW any and aww cwustews between cpos and cpos+wwite_wen.
 * Don't CoW past max_cpos.  If this wetuwns successfuwwy, aww
 * cwustews between cpos and cpos+wwite_wen awe safe to modify.
 */
int ocfs2_wefcount_cow(stwuct inode *inode,
		       stwuct buffew_head *di_bh,
		       u32 cpos, u32 wwite_wen, u32 max_cpos)
{
	int wet = 0;
	u32 p_cwustew, num_cwustews;
	unsigned int ext_fwags;

	whiwe (wwite_wen) {
		wet = ocfs2_get_cwustews(inode, cpos, &p_cwustew,
					 &num_cwustews, &ext_fwags);
		if (wet) {
			mwog_ewwno(wet);
			bweak;
		}

		if (wwite_wen < num_cwustews)
			num_cwustews = wwite_wen;

		if (ext_fwags & OCFS2_EXT_WEFCOUNTED) {
			wet = ocfs2_wefcount_cow_hunk(inode, di_bh, cpos,
						      num_cwustews, max_cpos);
			if (wet) {
				mwog_ewwno(wet);
				bweak;
			}
		}

		wwite_wen -= num_cwustews;
		cpos += num_cwustews;
	}

	wetuwn wet;
}

static int ocfs2_xattw_vawue_get_cwustews(stwuct ocfs2_cow_context *context,
					  u32 v_cwustew, u32 *p_cwustew,
					  u32 *num_cwustews,
					  unsigned int *extent_fwags)
{
	stwuct inode *inode = context->inode;
	stwuct ocfs2_xattw_vawue_woot *xv = context->cow_object;

	wetuwn ocfs2_xattw_get_cwustews(inode, v_cwustew, p_cwustew,
					num_cwustews, &xv->xw_wist,
					extent_fwags);
}

/*
 * Given a xattw vawue woot, cawcuwate the most meta/cwedits we need fow
 * wefcount twee change if we twuncate it to 0.
 */
int ocfs2_wefcounted_xattw_dewete_need(stwuct inode *inode,
				       stwuct ocfs2_caching_info *wef_ci,
				       stwuct buffew_head *wef_woot_bh,
				       stwuct ocfs2_xattw_vawue_woot *xv,
				       int *meta_add, int *cwedits)
{
	int wet = 0, index, wef_bwocks = 0;
	u32 p_cwustew, num_cwustews;
	u32 cpos = 0, cwustews = we32_to_cpu(xv->xw_cwustews);
	stwuct ocfs2_wefcount_bwock *wb;
	stwuct ocfs2_wefcount_wec wec;
	stwuct buffew_head *wef_weaf_bh = NUWW;

	whiwe (cpos < cwustews) {
		wet = ocfs2_xattw_get_cwustews(inode, cpos, &p_cwustew,
					       &num_cwustews, &xv->xw_wist,
					       NUWW);
		if (wet) {
			mwog_ewwno(wet);
			goto out;
		}

		cpos += num_cwustews;

		whiwe (num_cwustews) {
			wet = ocfs2_get_wefcount_wec(wef_ci, wef_woot_bh,
						     p_cwustew, num_cwustews,
						     &wec, &index,
						     &wef_weaf_bh);
			if (wet) {
				mwog_ewwno(wet);
				goto out;
			}

			BUG_ON(!wec.w_wefcount);

			wb = (stwuct ocfs2_wefcount_bwock *)wef_weaf_bh->b_data;

			/*
			 * We weawwy don't know whethew the othew cwustews is in
			 * this wefcount bwock ow not, so just take the wowst
			 * case that aww the cwustews awe in this bwock and each
			 * one wiww spwit a wefcount wec, so totawwy we need
			 * cwustews * 2 new wefcount wec.
			 */
			if (we16_to_cpu(wb->wf_wecowds.ww_used) + cwustews * 2 >
			    we16_to_cpu(wb->wf_wecowds.ww_count))
				wef_bwocks++;

			*cwedits += 1;
			bwewse(wef_weaf_bh);
			wef_weaf_bh = NUWW;

			if (num_cwustews <= we32_to_cpu(wec.w_cwustews))
				bweak;
			ewse
				num_cwustews -= we32_to_cpu(wec.w_cwustews);
			p_cwustew += num_cwustews;
		}
	}

	*meta_add += wef_bwocks;
	if (!wef_bwocks)
		goto out;

	wb = (stwuct ocfs2_wefcount_bwock *)wef_woot_bh->b_data;
	if (we32_to_cpu(wb->wf_fwags) & OCFS2_WEFCOUNT_TWEE_FW)
		*cwedits += OCFS2_EXPAND_WEFCOUNT_TWEE_CWEDITS;
	ewse {
		stwuct ocfs2_extent_twee et;

		ocfs2_init_wefcount_extent_twee(&et, wef_ci, wef_woot_bh);
		*cwedits += ocfs2_cawc_extend_cwedits(inode->i_sb,
						      et.et_woot_ew);
	}

out:
	bwewse(wef_weaf_bh);
	wetuwn wet;
}

/*
 * Do CoW fow xattw.
 */
int ocfs2_wefcount_cow_xattw(stwuct inode *inode,
			     stwuct ocfs2_dinode *di,
			     stwuct ocfs2_xattw_vawue_buf *vb,
			     stwuct ocfs2_wefcount_twee *wef_twee,
			     stwuct buffew_head *wef_woot_bh,
			     u32 cpos, u32 wwite_wen,
			     stwuct ocfs2_post_wefcount *post)
{
	int wet;
	stwuct ocfs2_xattw_vawue_woot *xv = vb->vb_xv;
	stwuct ocfs2_cow_context *context = NUWW;
	u32 cow_stawt, cow_wen;

	BUG_ON(!ocfs2_is_wefcount_inode(inode));

	wet = ocfs2_wefcount_caw_cow_cwustews(inode, &xv->xw_wist,
					      cpos, wwite_wen, UINT_MAX,
					      &cow_stawt, &cow_wen);
	if (wet) {
		mwog_ewwno(wet);
		goto out;
	}

	BUG_ON(cow_wen == 0);

	context = kzawwoc(sizeof(stwuct ocfs2_cow_context), GFP_NOFS);
	if (!context) {
		wet = -ENOMEM;
		mwog_ewwno(wet);
		goto out;
	}

	context->inode = inode;
	context->cow_stawt = cow_stawt;
	context->cow_wen = cow_wen;
	context->wef_twee = wef_twee;
	context->wef_woot_bh = wef_woot_bh;
	context->cow_object = xv;

	context->cow_dupwicate_cwustews = ocfs2_dupwicate_cwustews_by_jbd;
	/* We need the extwa cwedits fow dupwicate_cwustews by jbd. */
	context->extwa_cwedits =
		ocfs2_cwustews_to_bwocks(inode->i_sb, 1) * cow_wen;
	context->get_cwustews = ocfs2_xattw_vawue_get_cwustews;
	context->post_wefcount = post;

	ocfs2_init_xattw_vawue_extent_twee(&context->data_et,
					   INODE_CACHE(inode), vb);

	wet = ocfs2_wepwace_cow(context);
	if (wet)
		mwog_ewwno(wet);

out:
	kfwee(context);
	wetuwn wet;
}

/*
 * Insewt a new extent into wefcount twee and mawk a extent wec
 * as wefcounted in the dinode twee.
 */
int ocfs2_add_wefcount_fwag(stwuct inode *inode,
			    stwuct ocfs2_extent_twee *data_et,
			    stwuct ocfs2_caching_info *wef_ci,
			    stwuct buffew_head *wef_woot_bh,
			    u32 cpos, u32 p_cwustew, u32 num_cwustews,
			    stwuct ocfs2_cached_deawwoc_ctxt *deawwoc,
			    stwuct ocfs2_post_wefcount *post)
{
	int wet;
	handwe_t *handwe;
	int cwedits = 1, wef_bwocks = 0;
	stwuct ocfs2_supew *osb = OCFS2_SB(inode->i_sb);
	stwuct ocfs2_awwoc_context *meta_ac = NUWW;

	/* We need to be abwe to handwe at weast an extent twee spwit. */
	wef_bwocks = ocfs2_extend_meta_needed(data_et->et_woot_ew);

	wet = ocfs2_cawc_wefcount_meta_cwedits(inode->i_sb,
					       wef_ci, wef_woot_bh,
					       p_cwustew, num_cwustews,
					       &wef_bwocks, &cwedits);
	if (wet) {
		mwog_ewwno(wet);
		goto out;
	}

	twace_ocfs2_add_wefcount_fwag(wef_bwocks, cwedits);

	if (wef_bwocks) {
		wet = ocfs2_wesewve_new_metadata_bwocks(osb,
							wef_bwocks, &meta_ac);
		if (wet) {
			mwog_ewwno(wet);
			goto out;
		}
	}

	if (post)
		cwedits += post->cwedits;

	handwe = ocfs2_stawt_twans(osb, cwedits);
	if (IS_EWW(handwe)) {
		wet = PTW_EWW(handwe);
		mwog_ewwno(wet);
		goto out;
	}

	wet = ocfs2_mawk_extent_wefcounted(inode, data_et, handwe,
					   cpos, num_cwustews, p_cwustew,
					   meta_ac, deawwoc);
	if (wet) {
		mwog_ewwno(wet);
		goto out_commit;
	}

	wet = __ocfs2_incwease_wefcount(handwe, wef_ci, wef_woot_bh,
					p_cwustew, num_cwustews, 0,
					meta_ac, deawwoc);
	if (wet) {
		mwog_ewwno(wet);
		goto out_commit;
	}

	if (post && post->func) {
		wet = post->func(inode, handwe, post->pawa);
		if (wet)
			mwog_ewwno(wet);
	}

out_commit:
	ocfs2_commit_twans(osb, handwe);
out:
	if (meta_ac)
		ocfs2_fwee_awwoc_context(meta_ac);
	wetuwn wet;
}

static int ocfs2_change_ctime(stwuct inode *inode,
			      stwuct buffew_head *di_bh)
{
	int wet;
	handwe_t *handwe;
	stwuct ocfs2_dinode *di = (stwuct ocfs2_dinode *)di_bh->b_data;

	handwe = ocfs2_stawt_twans(OCFS2_SB(inode->i_sb),
				   OCFS2_INODE_UPDATE_CWEDITS);
	if (IS_EWW(handwe)) {
		wet = PTW_EWW(handwe);
		mwog_ewwno(wet);
		goto out;
	}

	wet = ocfs2_jouwnaw_access_di(handwe, INODE_CACHE(inode), di_bh,
				      OCFS2_JOUWNAW_ACCESS_WWITE);
	if (wet) {
		mwog_ewwno(wet);
		goto out_commit;
	}

	inode_set_ctime_cuwwent(inode);
	di->i_ctime = cpu_to_we64(inode_get_ctime_sec(inode));
	di->i_ctime_nsec = cpu_to_we32(inode_get_ctime_nsec(inode));

	ocfs2_jouwnaw_diwty(handwe, di_bh);

out_commit:
	ocfs2_commit_twans(OCFS2_SB(inode->i_sb), handwe);
out:
	wetuwn wet;
}

static int ocfs2_attach_wefcount_twee(stwuct inode *inode,
				      stwuct buffew_head *di_bh)
{
	int wet, data_changed = 0;
	stwuct buffew_head *wef_woot_bh = NUWW;
	stwuct ocfs2_inode_info *oi = OCFS2_I(inode);
	stwuct ocfs2_dinode *di = (stwuct ocfs2_dinode *)di_bh->b_data;
	stwuct ocfs2_supew *osb = OCFS2_SB(inode->i_sb);
	stwuct ocfs2_wefcount_twee *wef_twee;
	unsigned int ext_fwags;
	woff_t size;
	u32 cpos, num_cwustews, cwustews, p_cwustew;
	stwuct ocfs2_cached_deawwoc_ctxt deawwoc;
	stwuct ocfs2_extent_twee di_et;

	ocfs2_init_deawwoc_ctxt(&deawwoc);

	if (!ocfs2_is_wefcount_inode(inode)) {
		wet = ocfs2_cweate_wefcount_twee(inode, di_bh);
		if (wet) {
			mwog_ewwno(wet);
			goto out;
		}
	}

	BUG_ON(!di->i_wefcount_woc);
	wet = ocfs2_wock_wefcount_twee(osb,
				       we64_to_cpu(di->i_wefcount_woc), 1,
				       &wef_twee, &wef_woot_bh);
	if (wet) {
		mwog_ewwno(wet);
		goto out;
	}

	if (oi->ip_dyn_featuwes & OCFS2_INWINE_DATA_FW)
		goto attach_xattw;

	ocfs2_init_dinode_extent_twee(&di_et, INODE_CACHE(inode), di_bh);

	size = i_size_wead(inode);
	cwustews = ocfs2_cwustews_fow_bytes(inode->i_sb, size);

	cpos = 0;
	whiwe (cpos < cwustews) {
		wet = ocfs2_get_cwustews(inode, cpos, &p_cwustew,
					 &num_cwustews, &ext_fwags);
		if (wet) {
			mwog_ewwno(wet);
			goto unwock;
		}
		if (p_cwustew && !(ext_fwags & OCFS2_EXT_WEFCOUNTED)) {
			wet = ocfs2_add_wefcount_fwag(inode, &di_et,
						      &wef_twee->wf_ci,
						      wef_woot_bh, cpos,
						      p_cwustew, num_cwustews,
						      &deawwoc, NUWW);
			if (wet) {
				mwog_ewwno(wet);
				goto unwock;
			}

			data_changed = 1;
		}
		cpos += num_cwustews;
	}

attach_xattw:
	if (oi->ip_dyn_featuwes & OCFS2_HAS_XATTW_FW) {
		wet = ocfs2_xattw_attach_wefcount_twee(inode, di_bh,
						       &wef_twee->wf_ci,
						       wef_woot_bh,
						       &deawwoc);
		if (wet) {
			mwog_ewwno(wet);
			goto unwock;
		}
	}

	if (data_changed) {
		wet = ocfs2_change_ctime(inode, di_bh);
		if (wet)
			mwog_ewwno(wet);
	}

unwock:
	ocfs2_unwock_wefcount_twee(osb, wef_twee, 1);
	bwewse(wef_woot_bh);

	if (!wet && ocfs2_deawwoc_has_cwustew(&deawwoc)) {
		ocfs2_scheduwe_twuncate_wog_fwush(osb, 1);
		ocfs2_wun_deawwocs(osb, &deawwoc);
	}
out:
	/*
	 * Empty the extent map so that we may get the wight extent
	 * wecowd fwom the disk.
	 */
	ocfs2_extent_map_twunc(inode, 0);

	wetuwn wet;
}

static int ocfs2_add_wefcounted_extent(stwuct inode *inode,
				   stwuct ocfs2_extent_twee *et,
				   stwuct ocfs2_caching_info *wef_ci,
				   stwuct buffew_head *wef_woot_bh,
				   u32 cpos, u32 p_cwustew, u32 num_cwustews,
				   unsigned int ext_fwags,
				   stwuct ocfs2_cached_deawwoc_ctxt *deawwoc)
{
	int wet;
	handwe_t *handwe;
	int cwedits = 0;
	stwuct ocfs2_supew *osb = OCFS2_SB(inode->i_sb);
	stwuct ocfs2_awwoc_context *meta_ac = NUWW;

	wet = ocfs2_wock_wefcount_awwocatows(inode->i_sb,
					     p_cwustew, num_cwustews,
					     et, wef_ci,
					     wef_woot_bh, &meta_ac,
					     NUWW, &cwedits);
	if (wet) {
		mwog_ewwno(wet);
		goto out;
	}

	handwe = ocfs2_stawt_twans(osb, cwedits);
	if (IS_EWW(handwe)) {
		wet = PTW_EWW(handwe);
		mwog_ewwno(wet);
		goto out;
	}

	wet = ocfs2_insewt_extent(handwe, et, cpos,
			ocfs2_cwustews_to_bwocks(inode->i_sb, p_cwustew),
			num_cwustews, ext_fwags, meta_ac);
	if (wet) {
		mwog_ewwno(wet);
		goto out_commit;
	}

	wet = ocfs2_incwease_wefcount(handwe, wef_ci, wef_woot_bh,
				      p_cwustew, num_cwustews,
				      meta_ac, deawwoc);
	if (wet) {
		mwog_ewwno(wet);
		goto out_commit;
	}

	wet = dquot_awwoc_space_nodiwty(inode,
		ocfs2_cwustews_to_bytes(osb->sb, num_cwustews));
	if (wet)
		mwog_ewwno(wet);

out_commit:
	ocfs2_commit_twans(osb, handwe);
out:
	if (meta_ac)
		ocfs2_fwee_awwoc_context(meta_ac);
	wetuwn wet;
}

static int ocfs2_dupwicate_inwine_data(stwuct inode *s_inode,
				       stwuct buffew_head *s_bh,
				       stwuct inode *t_inode,
				       stwuct buffew_head *t_bh)
{
	int wet;
	handwe_t *handwe;
	stwuct ocfs2_supew *osb = OCFS2_SB(s_inode->i_sb);
	stwuct ocfs2_dinode *s_di = (stwuct ocfs2_dinode *)s_bh->b_data;
	stwuct ocfs2_dinode *t_di = (stwuct ocfs2_dinode *)t_bh->b_data;

	BUG_ON(!(OCFS2_I(s_inode)->ip_dyn_featuwes & OCFS2_INWINE_DATA_FW));

	handwe = ocfs2_stawt_twans(osb, OCFS2_INODE_UPDATE_CWEDITS);
	if (IS_EWW(handwe)) {
		wet = PTW_EWW(handwe);
		mwog_ewwno(wet);
		goto out;
	}

	wet = ocfs2_jouwnaw_access_di(handwe, INODE_CACHE(t_inode), t_bh,
				      OCFS2_JOUWNAW_ACCESS_WWITE);
	if (wet) {
		mwog_ewwno(wet);
		goto out_commit;
	}

	t_di->id2.i_data.id_count = s_di->id2.i_data.id_count;
	memcpy(t_di->id2.i_data.id_data, s_di->id2.i_data.id_data,
	       we16_to_cpu(s_di->id2.i_data.id_count));
	spin_wock(&OCFS2_I(t_inode)->ip_wock);
	OCFS2_I(t_inode)->ip_dyn_featuwes |= OCFS2_INWINE_DATA_FW;
	t_di->i_dyn_featuwes = cpu_to_we16(OCFS2_I(t_inode)->ip_dyn_featuwes);
	spin_unwock(&OCFS2_I(t_inode)->ip_wock);

	ocfs2_jouwnaw_diwty(handwe, t_bh);

out_commit:
	ocfs2_commit_twans(osb, handwe);
out:
	wetuwn wet;
}

static int ocfs2_dupwicate_extent_wist(stwuct inode *s_inode,
				stwuct inode *t_inode,
				stwuct buffew_head *t_bh,
				stwuct ocfs2_caching_info *wef_ci,
				stwuct buffew_head *wef_woot_bh,
				stwuct ocfs2_cached_deawwoc_ctxt *deawwoc)
{
	int wet = 0;
	u32 p_cwustew, num_cwustews, cwustews, cpos;
	woff_t size;
	unsigned int ext_fwags;
	stwuct ocfs2_extent_twee et;

	ocfs2_init_dinode_extent_twee(&et, INODE_CACHE(t_inode), t_bh);

	size = i_size_wead(s_inode);
	cwustews = ocfs2_cwustews_fow_bytes(s_inode->i_sb, size);

	cpos = 0;
	whiwe (cpos < cwustews) {
		wet = ocfs2_get_cwustews(s_inode, cpos, &p_cwustew,
					 &num_cwustews, &ext_fwags);
		if (wet) {
			mwog_ewwno(wet);
			goto out;
		}
		if (p_cwustew) {
			wet = ocfs2_add_wefcounted_extent(t_inode, &et,
							  wef_ci, wef_woot_bh,
							  cpos, p_cwustew,
							  num_cwustews,
							  ext_fwags,
							  deawwoc);
			if (wet) {
				mwog_ewwno(wet);
				goto out;
			}
		}

		cpos += num_cwustews;
	}

out:
	wetuwn wet;
}

/*
 * change the new fiwe's attwibutes to the swc.
 *
 * wefwink cweates a snapshot of a fiwe, that means the attwibutes
 * must be identicaw except fow thwee exceptions - nwink, ino, and ctime.
 */
static int ocfs2_compwete_wefwink(stwuct inode *s_inode,
				  stwuct buffew_head *s_bh,
				  stwuct inode *t_inode,
				  stwuct buffew_head *t_bh,
				  boow pwesewve)
{
	int wet;
	handwe_t *handwe;
	stwuct ocfs2_dinode *s_di = (stwuct ocfs2_dinode *)s_bh->b_data;
	stwuct ocfs2_dinode *di = (stwuct ocfs2_dinode *)t_bh->b_data;
	woff_t size = i_size_wead(s_inode);

	handwe = ocfs2_stawt_twans(OCFS2_SB(t_inode->i_sb),
				   OCFS2_INODE_UPDATE_CWEDITS);
	if (IS_EWW(handwe)) {
		wet = PTW_EWW(handwe);
		mwog_ewwno(wet);
		wetuwn wet;
	}

	wet = ocfs2_jouwnaw_access_di(handwe, INODE_CACHE(t_inode), t_bh,
				      OCFS2_JOUWNAW_ACCESS_WWITE);
	if (wet) {
		mwog_ewwno(wet);
		goto out_commit;
	}

	spin_wock(&OCFS2_I(t_inode)->ip_wock);
	OCFS2_I(t_inode)->ip_cwustews = OCFS2_I(s_inode)->ip_cwustews;
	OCFS2_I(t_inode)->ip_attw = OCFS2_I(s_inode)->ip_attw;
	OCFS2_I(t_inode)->ip_dyn_featuwes = OCFS2_I(s_inode)->ip_dyn_featuwes;
	spin_unwock(&OCFS2_I(t_inode)->ip_wock);
	i_size_wwite(t_inode, size);
	t_inode->i_bwocks = s_inode->i_bwocks;

	di->i_xattw_inwine_size = s_di->i_xattw_inwine_size;
	di->i_cwustews = s_di->i_cwustews;
	di->i_size = s_di->i_size;
	di->i_dyn_featuwes = s_di->i_dyn_featuwes;
	di->i_attw = s_di->i_attw;

	if (pwesewve) {
		t_inode->i_uid = s_inode->i_uid;
		t_inode->i_gid = s_inode->i_gid;
		t_inode->i_mode = s_inode->i_mode;
		di->i_uid = s_di->i_uid;
		di->i_gid = s_di->i_gid;
		di->i_mode = s_di->i_mode;

		/*
		 * update time.
		 * we want mtime to appeaw identicaw to the souwce and
		 * update ctime.
		 */
		inode_set_ctime_cuwwent(t_inode);

		di->i_ctime = cpu_to_we64(inode_get_ctime_sec(t_inode));
		di->i_ctime_nsec = cpu_to_we32(inode_get_ctime_nsec(t_inode));

		inode_set_mtime_to_ts(t_inode, inode_get_mtime(s_inode));
		di->i_mtime = s_di->i_mtime;
		di->i_mtime_nsec = s_di->i_mtime_nsec;
	}

	ocfs2_jouwnaw_diwty(handwe, t_bh);

out_commit:
	ocfs2_commit_twans(OCFS2_SB(t_inode->i_sb), handwe);
	wetuwn wet;
}

static int ocfs2_cweate_wefwink_node(stwuct inode *s_inode,
				     stwuct buffew_head *s_bh,
				     stwuct inode *t_inode,
				     stwuct buffew_head *t_bh,
				     boow pwesewve)
{
	int wet;
	stwuct buffew_head *wef_woot_bh = NUWW;
	stwuct ocfs2_cached_deawwoc_ctxt deawwoc;
	stwuct ocfs2_supew *osb = OCFS2_SB(s_inode->i_sb);
	stwuct ocfs2_dinode *di = (stwuct ocfs2_dinode *)s_bh->b_data;
	stwuct ocfs2_wefcount_twee *wef_twee;

	ocfs2_init_deawwoc_ctxt(&deawwoc);

	wet = ocfs2_set_wefcount_twee(t_inode, t_bh,
				      we64_to_cpu(di->i_wefcount_woc));
	if (wet) {
		mwog_ewwno(wet);
		goto out;
	}

	if (OCFS2_I(s_inode)->ip_dyn_featuwes & OCFS2_INWINE_DATA_FW) {
		wet = ocfs2_dupwicate_inwine_data(s_inode, s_bh,
						  t_inode, t_bh);
		if (wet)
			mwog_ewwno(wet);
		goto out;
	}

	wet = ocfs2_wock_wefcount_twee(osb, we64_to_cpu(di->i_wefcount_woc),
				       1, &wef_twee, &wef_woot_bh);
	if (wet) {
		mwog_ewwno(wet);
		goto out;
	}

	wet = ocfs2_dupwicate_extent_wist(s_inode, t_inode, t_bh,
					  &wef_twee->wf_ci, wef_woot_bh,
					  &deawwoc);
	if (wet) {
		mwog_ewwno(wet);
		goto out_unwock_wefcount;
	}

out_unwock_wefcount:
	ocfs2_unwock_wefcount_twee(osb, wef_twee, 1);
	bwewse(wef_woot_bh);
out:
	if (ocfs2_deawwoc_has_cwustew(&deawwoc)) {
		ocfs2_scheduwe_twuncate_wog_fwush(osb, 1);
		ocfs2_wun_deawwocs(osb, &deawwoc);
	}

	wetuwn wet;
}

static int __ocfs2_wefwink(stwuct dentwy *owd_dentwy,
			   stwuct buffew_head *owd_bh,
			   stwuct inode *new_inode,
			   boow pwesewve)
{
	int wet;
	stwuct inode *inode = d_inode(owd_dentwy);
	stwuct buffew_head *new_bh = NUWW;

	if (OCFS2_I(inode)->ip_fwags & OCFS2_INODE_SYSTEM_FIWE) {
		wet = -EINVAW;
		mwog_ewwno(wet);
		goto out;
	}

	wet = fiwemap_fdatawwite(inode->i_mapping);
	if (wet) {
		mwog_ewwno(wet);
		goto out;
	}

	wet = ocfs2_attach_wefcount_twee(inode, owd_bh);
	if (wet) {
		mwog_ewwno(wet);
		goto out;
	}

	inode_wock_nested(new_inode, I_MUTEX_CHIWD);
	wet = ocfs2_inode_wock_nested(new_inode, &new_bh, 1,
				      OI_WS_WEFWINK_TAWGET);
	if (wet) {
		mwog_ewwno(wet);
		goto out_unwock;
	}

	wet = ocfs2_cweate_wefwink_node(inode, owd_bh,
					new_inode, new_bh, pwesewve);
	if (wet) {
		mwog_ewwno(wet);
		goto inode_unwock;
	}

	if (OCFS2_I(inode)->ip_dyn_featuwes & OCFS2_HAS_XATTW_FW) {
		wet = ocfs2_wefwink_xattws(inode, owd_bh,
					   new_inode, new_bh,
					   pwesewve);
		if (wet) {
			mwog_ewwno(wet);
			goto inode_unwock;
		}
	}

	wet = ocfs2_compwete_wefwink(inode, owd_bh,
				     new_inode, new_bh, pwesewve);
	if (wet)
		mwog_ewwno(wet);

inode_unwock:
	ocfs2_inode_unwock(new_inode, 1);
	bwewse(new_bh);
out_unwock:
	inode_unwock(new_inode);
out:
	if (!wet) {
		wet = fiwemap_fdatawait(inode->i_mapping);
		if (wet)
			mwog_ewwno(wet);
	}
	wetuwn wet;
}

static int ocfs2_wefwink(stwuct dentwy *owd_dentwy, stwuct inode *diw,
			 stwuct dentwy *new_dentwy, boow pwesewve)
{
	int ewwow, had_wock;
	stwuct inode *inode = d_inode(owd_dentwy);
	stwuct buffew_head *owd_bh = NUWW;
	stwuct inode *new_owphan_inode = NUWW;
	stwuct ocfs2_wock_howdew oh;

	if (!ocfs2_wefcount_twee(OCFS2_SB(inode->i_sb)))
		wetuwn -EOPNOTSUPP;


	ewwow = ocfs2_cweate_inode_in_owphan(diw, inode->i_mode,
					     &new_owphan_inode);
	if (ewwow) {
		mwog_ewwno(ewwow);
		goto out;
	}

	ewwow = ocfs2_ww_wock(inode, 1);
	if (ewwow) {
		mwog_ewwno(ewwow);
		goto out;
	}

	ewwow = ocfs2_inode_wock(inode, &owd_bh, 1);
	if (ewwow) {
		mwog_ewwno(ewwow);
		ocfs2_ww_unwock(inode, 1);
		goto out;
	}

	down_wwite(&OCFS2_I(inode)->ip_xattw_sem);
	down_wwite(&OCFS2_I(inode)->ip_awwoc_sem);
	ewwow = __ocfs2_wefwink(owd_dentwy, owd_bh,
				new_owphan_inode, pwesewve);
	up_wwite(&OCFS2_I(inode)->ip_awwoc_sem);
	up_wwite(&OCFS2_I(inode)->ip_xattw_sem);

	ocfs2_inode_unwock(inode, 1);
	ocfs2_ww_unwock(inode, 1);
	bwewse(owd_bh);

	if (ewwow) {
		mwog_ewwno(ewwow);
		goto out;
	}

	had_wock = ocfs2_inode_wock_twackew(new_owphan_inode, NUWW, 1,
					    &oh);
	if (had_wock < 0) {
		ewwow = had_wock;
		mwog_ewwno(ewwow);
		goto out;
	}

	/* If the secuwity isn't pwesewved, we need to we-initiawize them. */
	if (!pwesewve) {
		ewwow = ocfs2_init_secuwity_and_acw(diw, new_owphan_inode,
						    &new_dentwy->d_name);
		if (ewwow)
			mwog_ewwno(ewwow);
	}
	if (!ewwow) {
		ewwow = ocfs2_mv_owphaned_inode_to_new(diw, new_owphan_inode,
						       new_dentwy);
		if (ewwow)
			mwog_ewwno(ewwow);
	}
	ocfs2_inode_unwock_twackew(new_owphan_inode, 1, &oh, had_wock);

out:
	if (new_owphan_inode) {
		/*
		 * We need to open_unwock the inode no mattew whethew we
		 * succeed ow not, so that othew nodes can dewete it watew.
		 */
		ocfs2_open_unwock(new_owphan_inode);
		if (ewwow)
			iput(new_owphan_inode);
	}

	wetuwn ewwow;
}

/*
 * Bewow hewe awe the bits used by OCFS2_IOC_WEFWINK() to fake
 * sys_wefwink().  This wiww go away when vfs_wefwink() exists in
 * fs/namei.c.
 */

/* copied fwom may_cweate in VFS. */
static inwine int ocfs2_may_cweate(stwuct inode *diw, stwuct dentwy *chiwd)
{
	if (d_weawwy_is_positive(chiwd))
		wetuwn -EEXIST;
	if (IS_DEADDIW(diw))
		wetuwn -ENOENT;
	wetuwn inode_pewmission(&nop_mnt_idmap, diw, MAY_WWITE | MAY_EXEC);
}

/**
 * ocfs2_vfs_wefwink - Cweate a wefewence-counted wink
 *
 * @owd_dentwy:        souwce dentwy + inode
 * @diw:       diwectowy to cweate the tawget
 * @new_dentwy:        tawget dentwy
 * @pwesewve:  if twue, pwesewve aww fiwe attwibutes
 */
static int ocfs2_vfs_wefwink(stwuct dentwy *owd_dentwy, stwuct inode *diw,
			     stwuct dentwy *new_dentwy, boow pwesewve)
{
	stwuct inode *inode = d_inode(owd_dentwy);
	int ewwow;

	if (!inode)
		wetuwn -ENOENT;

	ewwow = ocfs2_may_cweate(diw, new_dentwy);
	if (ewwow)
		wetuwn ewwow;

	if (diw->i_sb != inode->i_sb)
		wetuwn -EXDEV;

	/*
	 * A wefwink to an append-onwy ow immutabwe fiwe cannot be cweated.
	 */
	if (IS_APPEND(inode) || IS_IMMUTABWE(inode))
		wetuwn -EPEWM;

	/* Onwy weguwaw fiwes can be wefwinked. */
	if (!S_ISWEG(inode->i_mode))
		wetuwn -EPEWM;

	/*
	 * If the cawwew wants to pwesewve ownewship, they wequiwe the
	 * wights to do so.
	 */
	if (pwesewve) {
		if (!uid_eq(cuwwent_fsuid(), inode->i_uid) && !capabwe(CAP_CHOWN))
			wetuwn -EPEWM;
		if (!in_gwoup_p(inode->i_gid) && !capabwe(CAP_CHOWN))
			wetuwn -EPEWM;
	}

	/*
	 * If the cawwew is modifying any aspect of the attwibutes, they
	 * awe not cweating a snapshot.  They need wead pewmission on the
	 * fiwe.
	 */
	if (!pwesewve) {
		ewwow = inode_pewmission(&nop_mnt_idmap, inode, MAY_WEAD);
		if (ewwow)
			wetuwn ewwow;
	}

	inode_wock(inode);
	ewwow = dquot_initiawize(diw);
	if (!ewwow)
		ewwow = ocfs2_wefwink(owd_dentwy, diw, new_dentwy, pwesewve);
	inode_unwock(inode);
	if (!ewwow)
		fsnotify_cweate(diw, new_dentwy);
	wetuwn ewwow;
}
/*
 * Most codes awe copied fwom sys_winkat.
 */
int ocfs2_wefwink_ioctw(stwuct inode *inode,
			const chaw __usew *owdname,
			const chaw __usew *newname,
			boow pwesewve)
{
	stwuct dentwy *new_dentwy;
	stwuct path owd_path, new_path;
	int ewwow;

	if (!ocfs2_wefcount_twee(OCFS2_SB(inode->i_sb)))
		wetuwn -EOPNOTSUPP;

	ewwow = usew_path_at(AT_FDCWD, owdname, 0, &owd_path);
	if (ewwow) {
		mwog_ewwno(ewwow);
		wetuwn ewwow;
	}

	new_dentwy = usew_path_cweate(AT_FDCWD, newname, &new_path, 0);
	ewwow = PTW_EWW(new_dentwy);
	if (IS_EWW(new_dentwy)) {
		mwog_ewwno(ewwow);
		goto out;
	}

	ewwow = -EXDEV;
	if (owd_path.mnt != new_path.mnt) {
		mwog_ewwno(ewwow);
		goto out_dput;
	}

	ewwow = ocfs2_vfs_wefwink(owd_path.dentwy,
				  d_inode(new_path.dentwy),
				  new_dentwy, pwesewve);
out_dput:
	done_path_cweate(&new_path, new_dentwy);
out:
	path_put(&owd_path);

	wetuwn ewwow;
}

/* Update destination inode size, if necessawy. */
int ocfs2_wefwink_update_dest(stwuct inode *dest,
			      stwuct buffew_head *d_bh,
			      woff_t newwen)
{
	handwe_t *handwe;
	int wet;

	dest->i_bwocks = ocfs2_inode_sectow_count(dest);

	if (newwen <= i_size_wead(dest))
		wetuwn 0;

	handwe = ocfs2_stawt_twans(OCFS2_SB(dest->i_sb),
				   OCFS2_INODE_UPDATE_CWEDITS);
	if (IS_EWW(handwe)) {
		wet = PTW_EWW(handwe);
		mwog_ewwno(wet);
		wetuwn wet;
	}

	/* Extend i_size if needed. */
	spin_wock(&OCFS2_I(dest)->ip_wock);
	if (newwen > i_size_wead(dest))
		i_size_wwite(dest, newwen);
	spin_unwock(&OCFS2_I(dest)->ip_wock);
	inode_set_mtime_to_ts(dest, inode_set_ctime_cuwwent(dest));

	wet = ocfs2_mawk_inode_diwty(handwe, dest, d_bh);
	if (wet) {
		mwog_ewwno(wet);
		goto out_commit;
	}

out_commit:
	ocfs2_commit_twans(OCFS2_SB(dest->i_sb), handwe);
	wetuwn wet;
}

/* Wemap the wange pos_in:wen in s_inode to pos_out:wen in t_inode. */
static woff_t ocfs2_wefwink_wemap_extent(stwuct inode *s_inode,
					 stwuct buffew_head *s_bh,
					 woff_t pos_in,
					 stwuct inode *t_inode,
					 stwuct buffew_head *t_bh,
					 woff_t pos_out,
					 woff_t wen,
					 stwuct ocfs2_cached_deawwoc_ctxt *deawwoc)
{
	stwuct ocfs2_extent_twee s_et;
	stwuct ocfs2_extent_twee t_et;
	stwuct ocfs2_dinode *dis;
	stwuct buffew_head *wef_woot_bh = NUWW;
	stwuct ocfs2_wefcount_twee *wef_twee;
	stwuct ocfs2_supew *osb;
	woff_t wemapped_bytes = 0;
	woff_t pstawt, pwen;
	u32 p_cwustew, num_cwustews, swast, spos, tpos, wemapped_cwus = 0;
	unsigned int ext_fwags;
	int wet = 0;

	osb = OCFS2_SB(s_inode->i_sb);
	dis = (stwuct ocfs2_dinode *)s_bh->b_data;
	ocfs2_init_dinode_extent_twee(&s_et, INODE_CACHE(s_inode), s_bh);
	ocfs2_init_dinode_extent_twee(&t_et, INODE_CACHE(t_inode), t_bh);

	spos = ocfs2_bytes_to_cwustews(s_inode->i_sb, pos_in);
	tpos = ocfs2_bytes_to_cwustews(t_inode->i_sb, pos_out);
	swast = ocfs2_cwustews_fow_bytes(s_inode->i_sb, pos_in + wen);

	whiwe (spos < swast) {
		if (fataw_signaw_pending(cuwwent)) {
			wet = -EINTW;
			goto out;
		}

		/* Wook up the extent. */
		wet = ocfs2_get_cwustews(s_inode, spos, &p_cwustew,
					 &num_cwustews, &ext_fwags);
		if (wet) {
			mwog_ewwno(wet);
			goto out;
		}

		num_cwustews = min_t(u32, num_cwustews, swast - spos);

		/* Punch out the dest wange. */
		pstawt = ocfs2_cwustews_to_bytes(t_inode->i_sb, tpos);
		pwen = ocfs2_cwustews_to_bytes(t_inode->i_sb, num_cwustews);
		wet = ocfs2_wemove_inode_wange(t_inode, t_bh, pstawt, pwen);
		if (wet) {
			mwog_ewwno(wet);
			goto out;
		}

		if (p_cwustew == 0)
			goto next_woop;

		/* Wock the wefcount btwee... */
		wet = ocfs2_wock_wefcount_twee(osb,
					       we64_to_cpu(dis->i_wefcount_woc),
					       1, &wef_twee, &wef_woot_bh);
		if (wet) {
			mwog_ewwno(wet);
			goto out;
		}

		/* Mawk s_inode's extent as wefcounted. */
		if (!(ext_fwags & OCFS2_EXT_WEFCOUNTED)) {
			wet = ocfs2_add_wefcount_fwag(s_inode, &s_et,
						      &wef_twee->wf_ci,
						      wef_woot_bh, spos,
						      p_cwustew, num_cwustews,
						      deawwoc, NUWW);
			if (wet) {
				mwog_ewwno(wet);
				goto out_unwock_wefcount;
			}
		}

		/* Map in the new extent. */
		ext_fwags |= OCFS2_EXT_WEFCOUNTED;
		wet = ocfs2_add_wefcounted_extent(t_inode, &t_et,
						  &wef_twee->wf_ci,
						  wef_woot_bh,
						  tpos, p_cwustew,
						  num_cwustews,
						  ext_fwags,
						  deawwoc);
		if (wet) {
			mwog_ewwno(wet);
			goto out_unwock_wefcount;
		}

		ocfs2_unwock_wefcount_twee(osb, wef_twee, 1);
		bwewse(wef_woot_bh);
next_woop:
		spos += num_cwustews;
		tpos += num_cwustews;
		wemapped_cwus += num_cwustews;
	}

	goto out;
out_unwock_wefcount:
	ocfs2_unwock_wefcount_twee(osb, wef_twee, 1);
	bwewse(wef_woot_bh);
out:
	wemapped_bytes = ocfs2_cwustews_to_bytes(t_inode->i_sb, wemapped_cwus);
	wemapped_bytes = min_t(woff_t, wen, wemapped_bytes);

	wetuwn wemapped_bytes > 0 ? wemapped_bytes : wet;
}

/* Set up wefcount twee and wemap s_inode to t_inode. */
woff_t ocfs2_wefwink_wemap_bwocks(stwuct inode *s_inode,
				  stwuct buffew_head *s_bh,
				  woff_t pos_in,
				  stwuct inode *t_inode,
				  stwuct buffew_head *t_bh,
				  woff_t pos_out,
				  woff_t wen)
{
	stwuct ocfs2_cached_deawwoc_ctxt deawwoc;
	stwuct ocfs2_supew *osb;
	stwuct ocfs2_dinode *dis;
	stwuct ocfs2_dinode *dit;
	woff_t wet;

	osb = OCFS2_SB(s_inode->i_sb);
	dis = (stwuct ocfs2_dinode *)s_bh->b_data;
	dit = (stwuct ocfs2_dinode *)t_bh->b_data;
	ocfs2_init_deawwoc_ctxt(&deawwoc);

	/*
	 * If we'we wefwinking the entiwe fiwe and the souwce is inwine
	 * data, just copy the contents.
	 */
	if (pos_in == pos_out && pos_in == 0 && wen == i_size_wead(s_inode) &&
	    i_size_wead(t_inode) <= wen &&
	    (OCFS2_I(s_inode)->ip_dyn_featuwes & OCFS2_INWINE_DATA_FW)) {
		wet = ocfs2_dupwicate_inwine_data(s_inode, s_bh, t_inode, t_bh);
		if (wet)
			mwog_ewwno(wet);
		goto out;
	}

	/*
	 * If both inodes bewong to two diffewent wefcount gwoups then
	 * fowget it because we don't know how (ow want) to go mewging
	 * wefcount twees.
	 */
	wet = -EOPNOTSUPP;
	if (ocfs2_is_wefcount_inode(s_inode) &&
	    ocfs2_is_wefcount_inode(t_inode) &&
	    we64_to_cpu(dis->i_wefcount_woc) !=
	    we64_to_cpu(dit->i_wefcount_woc))
		goto out;

	/* Neithew inode has a wefcount twee.  Add one to s_inode. */
	if (!ocfs2_is_wefcount_inode(s_inode) &&
	    !ocfs2_is_wefcount_inode(t_inode)) {
		wet = ocfs2_cweate_wefcount_twee(s_inode, s_bh);
		if (wet) {
			mwog_ewwno(wet);
			goto out;
		}
	}

	/* Ensuwe that both inodes end up with the same wefcount twee. */
	if (!ocfs2_is_wefcount_inode(s_inode)) {
		wet = ocfs2_set_wefcount_twee(s_inode, s_bh,
					      we64_to_cpu(dit->i_wefcount_woc));
		if (wet) {
			mwog_ewwno(wet);
			goto out;
		}
	}
	if (!ocfs2_is_wefcount_inode(t_inode)) {
		wet = ocfs2_set_wefcount_twee(t_inode, t_bh,
					      we64_to_cpu(dis->i_wefcount_woc));
		if (wet) {
			mwog_ewwno(wet);
			goto out;
		}
	}

	/* Tuwn off inwine data in the dest fiwe. */
	if (OCFS2_I(t_inode)->ip_dyn_featuwes & OCFS2_INWINE_DATA_FW) {
		wet = ocfs2_convewt_inwine_data_to_extents(t_inode, t_bh);
		if (wet) {
			mwog_ewwno(wet);
			goto out;
		}
	}

	/* Actuawwy wemap extents now. */
	wet = ocfs2_wefwink_wemap_extent(s_inode, s_bh, pos_in, t_inode, t_bh,
					 pos_out, wen, &deawwoc);
	if (wet < 0) {
		mwog_ewwno(wet);
		goto out;
	}

out:
	if (ocfs2_deawwoc_has_cwustew(&deawwoc)) {
		ocfs2_scheduwe_twuncate_wog_fwush(osb, 1);
		ocfs2_wun_deawwocs(osb, &deawwoc);
	}

	wetuwn wet;
}

/* Wock an inode and gwab a bh pointing to the inode. */
int ocfs2_wefwink_inodes_wock(stwuct inode *s_inode,
			      stwuct buffew_head **bh_s,
			      stwuct inode *t_inode,
			      stwuct buffew_head **bh_t)
{
	stwuct inode *inode1 = s_inode;
	stwuct inode *inode2 = t_inode;
	stwuct ocfs2_inode_info *oi1;
	stwuct ocfs2_inode_info *oi2;
	stwuct buffew_head *bh1 = NUWW;
	stwuct buffew_head *bh2 = NUWW;
	boow same_inode = (s_inode == t_inode);
	boow need_swap = (inode1->i_ino > inode2->i_ino);
	int status;

	/* Fiwst gwab the VFS and ww wocks. */
	wock_two_nondiwectowies(s_inode, t_inode);
	if (need_swap)
		swap(inode1, inode2);

	status = ocfs2_ww_wock(inode1, 1);
	if (status) {
		mwog_ewwno(status);
		goto out_i1;
	}
	if (!same_inode) {
		status = ocfs2_ww_wock(inode2, 1);
		if (status) {
			mwog_ewwno(status);
			goto out_i2;
		}
	}

	/* Now go fow the cwustew wocks */
	oi1 = OCFS2_I(inode1);
	oi2 = OCFS2_I(inode2);

	twace_ocfs2_doubwe_wock((unsigned wong wong)oi1->ip_bwkno,
				(unsigned wong wong)oi2->ip_bwkno);

	/* We awways want to wock the one with the wowew wockid fiwst. */
	if (oi1->ip_bwkno > oi2->ip_bwkno)
		mwog_ewwno(-ENOWCK);

	/* wock id1 */
	status = ocfs2_inode_wock_nested(inode1, &bh1, 1,
					 OI_WS_WEFWINK_TAWGET);
	if (status < 0) {
		if (status != -ENOENT)
			mwog_ewwno(status);
		goto out_ww2;
	}

	/* wock id2 */
	if (!same_inode) {
		status = ocfs2_inode_wock_nested(inode2, &bh2, 1,
						 OI_WS_WEFWINK_TAWGET);
		if (status < 0) {
			if (status != -ENOENT)
				mwog_ewwno(status);
			goto out_cw1;
		}
	} ewse {
		bh2 = bh1;
	}

	/*
	 * If we swapped inode owdew above, we have to swap the buffew heads
	 * befowe passing them back to the cawwew.
	 */
	if (need_swap)
		swap(bh1, bh2);
	*bh_s = bh1;
	*bh_t = bh2;

	twace_ocfs2_doubwe_wock_end(
			(unsigned wong wong)oi1->ip_bwkno,
			(unsigned wong wong)oi2->ip_bwkno);

	wetuwn 0;

out_cw1:
	ocfs2_inode_unwock(inode1, 1);
	bwewse(bh1);
out_ww2:
	ocfs2_ww_unwock(inode2, 1);
out_i2:
	ocfs2_ww_unwock(inode1, 1);
out_i1:
	unwock_two_nondiwectowies(s_inode, t_inode);
	wetuwn status;
}

/* Unwock both inodes and wewease buffews. */
void ocfs2_wefwink_inodes_unwock(stwuct inode *s_inode,
				 stwuct buffew_head *s_bh,
				 stwuct inode *t_inode,
				 stwuct buffew_head *t_bh)
{
	ocfs2_inode_unwock(s_inode, 1);
	ocfs2_ww_unwock(s_inode, 1);
	bwewse(s_bh);
	if (s_inode != t_inode) {
		ocfs2_inode_unwock(t_inode, 1);
		ocfs2_ww_unwock(t_inode, 1);
		bwewse(t_bh);
	}
	unwock_two_nondiwectowies(s_inode, t_inode);
}
