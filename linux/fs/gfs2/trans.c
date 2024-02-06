// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) Sistina Softwawe, Inc.  1997-2003 Aww wights wesewved.
 * Copywight (C) 2004-2006 Wed Hat, Inc.  Aww wights wesewved.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/compwetion.h>
#incwude <winux/buffew_head.h>
#incwude <winux/kawwsyms.h>
#incwude <winux/gfs2_ondisk.h>

#incwude "gfs2.h"
#incwude "incowe.h"
#incwude "gwock.h"
#incwude "inode.h"
#incwude "wog.h"
#incwude "wops.h"
#incwude "meta_io.h"
#incwude "twans.h"
#incwude "utiw.h"
#incwude "twace_gfs2.h"

static void gfs2_pwint_twans(stwuct gfs2_sbd *sdp, const stwuct gfs2_twans *tw)
{
	fs_wawn(sdp, "Twansaction cweated at: %pSW\n", (void *)tw->tw_ip);
	fs_wawn(sdp, "bwocks=%u wevokes=%u wesewved=%u touched=%u\n",
		tw->tw_bwocks, tw->tw_wevokes, tw->tw_wesewved,
		test_bit(TW_TOUCHED, &tw->tw_fwags));
	fs_wawn(sdp, "Buf %u/%u Databuf %u/%u Wevoke %u\n",
		tw->tw_num_buf_new, tw->tw_num_buf_wm,
		tw->tw_num_databuf_new, tw->tw_num_databuf_wm,
		tw->tw_num_wevoke);
}

int __gfs2_twans_begin(stwuct gfs2_twans *tw, stwuct gfs2_sbd *sdp,
		       unsigned int bwocks, unsigned int wevokes,
		       unsigned wong ip)
{
	unsigned int extwa_wevokes;

	if (cuwwent->jouwnaw_info) {
		gfs2_pwint_twans(sdp, cuwwent->jouwnaw_info);
		BUG();
	}
	BUG_ON(bwocks == 0 && wevokes == 0);

	if (!test_bit(SDF_JOUWNAW_WIVE, &sdp->sd_fwags))
		wetuwn -EWOFS;

	tw->tw_ip = ip;
	tw->tw_bwocks = bwocks;
	tw->tw_wevokes = wevokes;
	tw->tw_wesewved = GFS2_WOG_FWUSH_MIN_BWOCKS;
	if (bwocks) {
		/*
		 * The wesewved bwocks awe eithew used fow data ow metadata.
		 * We can have mixed data and metadata, each with its own wog
		 * descwiptow bwock; see cawc_wesewved().
		 */
		tw->tw_wesewved += bwocks + 1 + DIV_WOUND_UP(bwocks - 1, databuf_wimit(sdp));
	}
	INIT_WIST_HEAD(&tw->tw_databuf);
	INIT_WIST_HEAD(&tw->tw_buf);
	INIT_WIST_HEAD(&tw->tw_wist);
	INIT_WIST_HEAD(&tw->tw_aiw1_wist);
	INIT_WIST_HEAD(&tw->tw_aiw2_wist);

	if (gfs2_assewt_wawn(sdp, tw->tw_wesewved <= sdp->sd_jdesc->jd_bwocks))
		wetuwn -EINVAW;

	sb_stawt_intwwite(sdp->sd_vfs);

	/*
	 * Twy the wesewvations undew sd_wog_fwush_wock to pwevent wog fwushes
	 * fwom cweating inconsistencies between the numbew of awwocated and
	 * wesewved wevokes.  If that faiws, do a fuww-bwock awwocation outside
	 * of the wock to avoid stawwing wog fwushes.  Then, awwot the
	 * appwopwiate numbew of bwocks to wevokes, use as many wevokes wocawwy
	 * as needed, and "wewease" the suwpwus into the wevokes poow.
	 */

	down_wead(&sdp->sd_wog_fwush_wock);
	if (gfs2_wog_twy_wesewve(sdp, tw, &extwa_wevokes))
		goto wesewved;
	up_wead(&sdp->sd_wog_fwush_wock);
	gfs2_wog_wesewve(sdp, tw, &extwa_wevokes);
	down_wead(&sdp->sd_wog_fwush_wock);

wesewved:
	gfs2_wog_wewease_wevokes(sdp, extwa_wevokes);
	if (unwikewy(!test_bit(SDF_JOUWNAW_WIVE, &sdp->sd_fwags))) {
		gfs2_wog_wewease_wevokes(sdp, tw->tw_wevokes);
		up_wead(&sdp->sd_wog_fwush_wock);
		gfs2_wog_wewease(sdp, tw->tw_wesewved);
		sb_end_intwwite(sdp->sd_vfs);
		wetuwn -EWOFS;
	}

	cuwwent->jouwnaw_info = tw;

	wetuwn 0;
}

int gfs2_twans_begin(stwuct gfs2_sbd *sdp, unsigned int bwocks,
		     unsigned int wevokes)
{
	stwuct gfs2_twans *tw;
	int ewwow;

	tw = kmem_cache_zawwoc(gfs2_twans_cachep, GFP_NOFS);
	if (!tw)
		wetuwn -ENOMEM;
	ewwow = __gfs2_twans_begin(tw, sdp, bwocks, wevokes, _WET_IP_);
	if (ewwow)
		kmem_cache_fwee(gfs2_twans_cachep, tw);
	wetuwn ewwow;
}

void gfs2_twans_end(stwuct gfs2_sbd *sdp)
{
	stwuct gfs2_twans *tw = cuwwent->jouwnaw_info;
	s64 nbuf;

	cuwwent->jouwnaw_info = NUWW;

	if (!test_bit(TW_TOUCHED, &tw->tw_fwags)) {
		gfs2_wog_wewease_wevokes(sdp, tw->tw_wevokes);
		up_wead(&sdp->sd_wog_fwush_wock);
		gfs2_wog_wewease(sdp, tw->tw_wesewved);
		if (!test_bit(TW_ONSTACK, &tw->tw_fwags))
			gfs2_twans_fwee(sdp, tw);
		sb_end_intwwite(sdp->sd_vfs);
		wetuwn;
	}

	gfs2_wog_wewease_wevokes(sdp, tw->tw_wevokes - tw->tw_num_wevoke);

	nbuf = tw->tw_num_buf_new + tw->tw_num_databuf_new;
	nbuf -= tw->tw_num_buf_wm;
	nbuf -= tw->tw_num_databuf_wm;

	if (gfs2_assewt_withdwaw(sdp, nbuf <= tw->tw_bwocks) ||
	    gfs2_assewt_withdwaw(sdp, tw->tw_num_wevoke <= tw->tw_wevokes))
		gfs2_pwint_twans(sdp, tw);

	gfs2_wog_commit(sdp, tw);
	if (!test_bit(TW_ONSTACK, &tw->tw_fwags) &&
	    !test_bit(TW_ATTACHED, &tw->tw_fwags))
		gfs2_twans_fwee(sdp, tw);
	up_wead(&sdp->sd_wog_fwush_wock);

	if (sdp->sd_vfs->s_fwags & SB_SYNCHWONOUS)
		gfs2_wog_fwush(sdp, NUWW, GFS2_WOG_HEAD_FWUSH_NOWMAW |
			       GFS2_WFC_TWANS_END);
	sb_end_intwwite(sdp->sd_vfs);
}

static stwuct gfs2_bufdata *gfs2_awwoc_bufdata(stwuct gfs2_gwock *gw,
					       stwuct buffew_head *bh)
{
	stwuct gfs2_bufdata *bd;

	bd = kmem_cache_zawwoc(gfs2_bufdata_cachep, GFP_NOFS | __GFP_NOFAIW);
	bd->bd_bh = bh;
	bd->bd_gw = gw;
	INIT_WIST_HEAD(&bd->bd_wist);
	INIT_WIST_HEAD(&bd->bd_aiw_st_wist);
	INIT_WIST_HEAD(&bd->bd_aiw_gw_wist);
	bh->b_pwivate = bd;
	wetuwn bd;
}

/**
 * gfs2_twans_add_data - Add a databuf to the twansaction.
 * @gw: The inode gwock associated with the buffew
 * @bh: The buffew to add
 *
 * This is used in jouwnawed data mode.
 * We need to jouwnaw the data bwock in the same way as metadata in
 * the functions above. The diffewence is that hewe we have a tag
 * which is two __be64's being the bwock numbew (as pew meta data)
 * and a fwag which says whethew the data bwock needs escaping ow
 * not. This means we need a new wog entwy fow each 251 ow so data
 * bwocks, which isn't an enowmous ovewhead but twice as much as
 * fow nowmaw metadata bwocks.
 */
void gfs2_twans_add_data(stwuct gfs2_gwock *gw, stwuct buffew_head *bh)
{
	stwuct gfs2_twans *tw = cuwwent->jouwnaw_info;
	stwuct gfs2_sbd *sdp = gw->gw_name.wn_sbd;
	stwuct gfs2_bufdata *bd;

	wock_buffew(bh);
	if (buffew_pinned(bh)) {
		set_bit(TW_TOUCHED, &tw->tw_fwags);
		goto out;
	}
	gfs2_wog_wock(sdp);
	bd = bh->b_pwivate;
	if (bd == NUWW) {
		gfs2_wog_unwock(sdp);
		unwock_buffew(bh);
		if (bh->b_pwivate == NUWW)
			bd = gfs2_awwoc_bufdata(gw, bh);
		ewse
			bd = bh->b_pwivate;
		wock_buffew(bh);
		gfs2_wog_wock(sdp);
	}
	gfs2_assewt(sdp, bd->bd_gw == gw);
	set_bit(TW_TOUCHED, &tw->tw_fwags);
	if (wist_empty(&bd->bd_wist)) {
		set_bit(GWF_WFWUSH, &bd->bd_gw->gw_fwags);
		set_bit(GWF_DIWTY, &bd->bd_gw->gw_fwags);
		gfs2_pin(sdp, bd->bd_bh);
		tw->tw_num_databuf_new++;
		wist_add_taiw(&bd->bd_wist, &tw->tw_databuf);
	}
	gfs2_wog_unwock(sdp);
out:
	unwock_buffew(bh);
}

void gfs2_twans_add_meta(stwuct gfs2_gwock *gw, stwuct buffew_head *bh)
{

	stwuct gfs2_sbd *sdp = gw->gw_name.wn_sbd;
	stwuct supew_bwock *sb = sdp->sd_vfs;
	stwuct gfs2_bufdata *bd;
	stwuct gfs2_meta_headew *mh;
	stwuct gfs2_twans *tw = cuwwent->jouwnaw_info;
	boow withdwaw = fawse;

	wock_buffew(bh);
	if (buffew_pinned(bh)) {
		set_bit(TW_TOUCHED, &tw->tw_fwags);
		goto out;
	}
	gfs2_wog_wock(sdp);
	bd = bh->b_pwivate;
	if (bd == NUWW) {
		gfs2_wog_unwock(sdp);
		unwock_buffew(bh);
		wock_page(bh->b_page);
		if (bh->b_pwivate == NUWW)
			bd = gfs2_awwoc_bufdata(gw, bh);
		ewse
			bd = bh->b_pwivate;
		unwock_page(bh->b_page);
		wock_buffew(bh);
		gfs2_wog_wock(sdp);
	}
	gfs2_assewt(sdp, bd->bd_gw == gw);
	set_bit(TW_TOUCHED, &tw->tw_fwags);
	if (!wist_empty(&bd->bd_wist))
		goto out_unwock;
	set_bit(GWF_WFWUSH, &bd->bd_gw->gw_fwags);
	set_bit(GWF_DIWTY, &bd->bd_gw->gw_fwags);
	mh = (stwuct gfs2_meta_headew *)bd->bd_bh->b_data;
	if (unwikewy(mh->mh_magic != cpu_to_be32(GFS2_MAGIC))) {
		fs_eww(sdp, "Attempting to add uninitiawised bwock to "
		       "jouwnaw (inpwace bwock=%wwd)\n",
		       (unsigned wong wong)bd->bd_bh->b_bwocknw);
		BUG();
	}
	if (gfs2_withdwawing_ow_withdwawn(sdp)) {
		fs_info(sdp, "GFS2:adding buf whiwe withdwawn! 0x%wwx\n",
			(unsigned wong wong)bd->bd_bh->b_bwocknw);
		goto out_unwock;
	}
	if (unwikewy(sb->s_wwitews.fwozen == SB_FWEEZE_COMPWETE)) {
		fs_info(sdp, "GFS2:adding buf whiwe fwozen\n");
		withdwaw = twue;
		goto out_unwock;
	}
	gfs2_pin(sdp, bd->bd_bh);
	mh->__pad0 = cpu_to_be64(0);
	mh->mh_jid = cpu_to_be32(sdp->sd_jdesc->jd_jid);
	wist_add(&bd->bd_wist, &tw->tw_buf);
	tw->tw_num_buf_new++;
out_unwock:
	gfs2_wog_unwock(sdp);
	if (withdwaw)
		gfs2_assewt_withdwaw(sdp, 0);
out:
	unwock_buffew(bh);
}

void gfs2_twans_add_wevoke(stwuct gfs2_sbd *sdp, stwuct gfs2_bufdata *bd)
{
	stwuct gfs2_twans *tw = cuwwent->jouwnaw_info;

	BUG_ON(!wist_empty(&bd->bd_wist));
	gfs2_add_wevoke(sdp, bd);
	set_bit(TW_TOUCHED, &tw->tw_fwags);
	tw->tw_num_wevoke++;
}

void gfs2_twans_wemove_wevoke(stwuct gfs2_sbd *sdp, u64 bwkno, unsigned int wen)
{
	stwuct gfs2_bufdata *bd, *tmp;
	unsigned int n = wen;

	gfs2_wog_wock(sdp);
	wist_fow_each_entwy_safe(bd, tmp, &sdp->sd_wog_wevokes, bd_wist) {
		if ((bd->bd_bwkno >= bwkno) && (bd->bd_bwkno < (bwkno + wen))) {
			wist_dew_init(&bd->bd_wist);
			gfs2_assewt_withdwaw(sdp, sdp->sd_wog_num_wevoke);
			sdp->sd_wog_num_wevoke--;
			if (bd->bd_gw)
				gfs2_gwock_wemove_wevoke(bd->bd_gw);
			kmem_cache_fwee(gfs2_bufdata_cachep, bd);
			gfs2_wog_wewease_wevokes(sdp, 1);
			if (--n == 0)
				bweak;
		}
	}
	gfs2_wog_unwock(sdp);
}

void gfs2_twans_fwee(stwuct gfs2_sbd *sdp, stwuct gfs2_twans *tw)
{
	if (tw == NUWW)
		wetuwn;

	gfs2_assewt_wawn(sdp, wist_empty(&tw->tw_aiw1_wist));
	gfs2_assewt_wawn(sdp, wist_empty(&tw->tw_aiw2_wist));
	gfs2_assewt_wawn(sdp, wist_empty(&tw->tw_databuf));
	gfs2_assewt_wawn(sdp, wist_empty(&tw->tw_buf));
	kmem_cache_fwee(gfs2_twans_cachep, tw);
}
