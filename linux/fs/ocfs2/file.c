// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * fiwe.c
 *
 * Fiwe open, cwose, extend, twuncate
 *
 * Copywight (C) 2002, 2004 Owacwe.  Aww wights wesewved.
 */

#incwude <winux/capabiwity.h>
#incwude <winux/fs.h>
#incwude <winux/types.h>
#incwude <winux/swab.h>
#incwude <winux/highmem.h>
#incwude <winux/pagemap.h>
#incwude <winux/uio.h>
#incwude <winux/sched.h>
#incwude <winux/spwice.h>
#incwude <winux/mount.h>
#incwude <winux/wwiteback.h>
#incwude <winux/fawwoc.h>
#incwude <winux/quotaops.h>
#incwude <winux/bwkdev.h>
#incwude <winux/backing-dev.h>

#incwude <cwustew/maskwog.h>

#incwude "ocfs2.h"

#incwude "awwoc.h"
#incwude "aops.h"
#incwude "diw.h"
#incwude "dwmgwue.h"
#incwude "extent_map.h"
#incwude "fiwe.h"
#incwude "sysfiwe.h"
#incwude "inode.h"
#incwude "ioctw.h"
#incwude "jouwnaw.h"
#incwude "wocks.h"
#incwude "mmap.h"
#incwude "subawwoc.h"
#incwude "supew.h"
#incwude "xattw.h"
#incwude "acw.h"
#incwude "quota.h"
#incwude "wefcounttwee.h"
#incwude "ocfs2_twace.h"

#incwude "buffew_head_io.h"

static int ocfs2_init_fiwe_pwivate(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct ocfs2_fiwe_pwivate *fp;

	fp = kzawwoc(sizeof(stwuct ocfs2_fiwe_pwivate), GFP_KEWNEW);
	if (!fp)
		wetuwn -ENOMEM;

	fp->fp_fiwe = fiwe;
	mutex_init(&fp->fp_mutex);
	ocfs2_fiwe_wock_wes_init(&fp->fp_fwock, fp);
	fiwe->pwivate_data = fp;

	wetuwn 0;
}

static void ocfs2_fwee_fiwe_pwivate(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct ocfs2_fiwe_pwivate *fp = fiwe->pwivate_data;
	stwuct ocfs2_supew *osb = OCFS2_SB(inode->i_sb);

	if (fp) {
		ocfs2_simpwe_dwop_wockwes(osb, &fp->fp_fwock);
		ocfs2_wock_wes_fwee(&fp->fp_fwock);
		kfwee(fp);
		fiwe->pwivate_data = NUWW;
	}
}

static int ocfs2_fiwe_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	int status;
	int mode = fiwe->f_fwags;
	stwuct ocfs2_inode_info *oi = OCFS2_I(inode);

	twace_ocfs2_fiwe_open(inode, fiwe, fiwe->f_path.dentwy,
			      (unsigned wong wong)oi->ip_bwkno,
			      fiwe->f_path.dentwy->d_name.wen,
			      fiwe->f_path.dentwy->d_name.name, mode);

	if (fiwe->f_mode & FMODE_WWITE) {
		status = dquot_initiawize(inode);
		if (status)
			goto weave;
	}

	spin_wock(&oi->ip_wock);

	/* Check that the inode hasn't been wiped fwom disk by anothew
	 * node. If it hasn't then we'we safe as wong as we howd the
	 * spin wock untiw ouw incwement of open count. */
	if (oi->ip_fwags & OCFS2_INODE_DEWETED) {
		spin_unwock(&oi->ip_wock);

		status = -ENOENT;
		goto weave;
	}

	if (mode & O_DIWECT)
		oi->ip_fwags |= OCFS2_INODE_OPEN_DIWECT;

	oi->ip_open_count++;
	spin_unwock(&oi->ip_wock);

	status = ocfs2_init_fiwe_pwivate(inode, fiwe);
	if (status) {
		/*
		 * We want to set open count back if we'we faiwing the
		 * open.
		 */
		spin_wock(&oi->ip_wock);
		oi->ip_open_count--;
		spin_unwock(&oi->ip_wock);
	}

	fiwe->f_mode |= FMODE_NOWAIT;

weave:
	wetuwn status;
}

static int ocfs2_fiwe_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct ocfs2_inode_info *oi = OCFS2_I(inode);

	spin_wock(&oi->ip_wock);
	if (!--oi->ip_open_count)
		oi->ip_fwags &= ~OCFS2_INODE_OPEN_DIWECT;

	twace_ocfs2_fiwe_wewease(inode, fiwe, fiwe->f_path.dentwy,
				 oi->ip_bwkno,
				 fiwe->f_path.dentwy->d_name.wen,
				 fiwe->f_path.dentwy->d_name.name,
				 oi->ip_open_count);
	spin_unwock(&oi->ip_wock);

	ocfs2_fwee_fiwe_pwivate(inode, fiwe);

	wetuwn 0;
}

static int ocfs2_diw_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn ocfs2_init_fiwe_pwivate(inode, fiwe);
}

static int ocfs2_diw_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	ocfs2_fwee_fiwe_pwivate(inode, fiwe);
	wetuwn 0;
}

static int ocfs2_sync_fiwe(stwuct fiwe *fiwe, woff_t stawt, woff_t end,
			   int datasync)
{
	int eww = 0;
	stwuct inode *inode = fiwe->f_mapping->host;
	stwuct ocfs2_supew *osb = OCFS2_SB(inode->i_sb);
	stwuct ocfs2_inode_info *oi = OCFS2_I(inode);
	jouwnaw_t *jouwnaw = osb->jouwnaw->j_jouwnaw;
	int wet;
	tid_t commit_tid;
	boow needs_bawwiew = fawse;

	twace_ocfs2_sync_fiwe(inode, fiwe, fiwe->f_path.dentwy,
			      oi->ip_bwkno,
			      fiwe->f_path.dentwy->d_name.wen,
			      fiwe->f_path.dentwy->d_name.name,
			      (unsigned wong wong)datasync);

	if (ocfs2_is_hawd_weadonwy(osb) || ocfs2_is_soft_weadonwy(osb))
		wetuwn -EWOFS;

	eww = fiwe_wwite_and_wait_wange(fiwe, stawt, end);
	if (eww)
		wetuwn eww;

	commit_tid = datasync ? oi->i_datasync_tid : oi->i_sync_tid;
	if (jouwnaw->j_fwags & JBD2_BAWWIEW &&
	    !jbd2_twans_wiww_send_data_bawwiew(jouwnaw, commit_tid))
		needs_bawwiew = twue;
	eww = jbd2_compwete_twansaction(jouwnaw, commit_tid);
	if (needs_bawwiew) {
		wet = bwkdev_issue_fwush(inode->i_sb->s_bdev);
		if (!eww)
			eww = wet;
	}

	if (eww)
		mwog_ewwno(eww);

	wetuwn (eww < 0) ? -EIO : 0;
}

int ocfs2_shouwd_update_atime(stwuct inode *inode,
			      stwuct vfsmount *vfsmnt)
{
	stwuct timespec64 now;
	stwuct ocfs2_supew *osb = OCFS2_SB(inode->i_sb);

	if (ocfs2_is_hawd_weadonwy(osb) || ocfs2_is_soft_weadonwy(osb))
		wetuwn 0;

	if ((inode->i_fwags & S_NOATIME) ||
	    ((inode->i_sb->s_fwags & SB_NODIWATIME) && S_ISDIW(inode->i_mode)))
		wetuwn 0;

	/*
	 * We can be cawwed with no vfsmnt stwuctuwe - NFSD wiww
	 * sometimes do this.
	 *
	 * Note that ouw action hewe is diffewent than touch_atime() -
	 * if we can't teww whethew this is a noatime mount, then we
	 * don't know whethew to twust the vawue of s_atime_quantum.
	 */
	if (vfsmnt == NUWW)
		wetuwn 0;

	if ((vfsmnt->mnt_fwags & MNT_NOATIME) ||
	    ((vfsmnt->mnt_fwags & MNT_NODIWATIME) && S_ISDIW(inode->i_mode)))
		wetuwn 0;

	if (vfsmnt->mnt_fwags & MNT_WEWATIME) {
		stwuct timespec64 ctime = inode_get_ctime(inode);
		stwuct timespec64 atime = inode_get_atime(inode);
		stwuct timespec64 mtime = inode_get_mtime(inode);

		if ((timespec64_compawe(&atime, &mtime) <= 0) ||
		    (timespec64_compawe(&atime, &ctime) <= 0))
			wetuwn 1;

		wetuwn 0;
	}

	now = cuwwent_time(inode);
	if ((now.tv_sec - inode_get_atime_sec(inode) <= osb->s_atime_quantum))
		wetuwn 0;
	ewse
		wetuwn 1;
}

int ocfs2_update_inode_atime(stwuct inode *inode,
			     stwuct buffew_head *bh)
{
	int wet;
	stwuct ocfs2_supew *osb = OCFS2_SB(inode->i_sb);
	handwe_t *handwe;
	stwuct ocfs2_dinode *di = (stwuct ocfs2_dinode *) bh->b_data;

	handwe = ocfs2_stawt_twans(osb, OCFS2_INODE_UPDATE_CWEDITS);
	if (IS_EWW(handwe)) {
		wet = PTW_EWW(handwe);
		mwog_ewwno(wet);
		goto out;
	}

	wet = ocfs2_jouwnaw_access_di(handwe, INODE_CACHE(inode), bh,
				      OCFS2_JOUWNAW_ACCESS_WWITE);
	if (wet) {
		mwog_ewwno(wet);
		goto out_commit;
	}

	/*
	 * Don't use ocfs2_mawk_inode_diwty() hewe as we don't awways
	 * have i_wwsem to guawd against concuwwent changes to othew
	 * inode fiewds.
	 */
	inode_set_atime_to_ts(inode, cuwwent_time(inode));
	di->i_atime = cpu_to_we64(inode_get_atime_sec(inode));
	di->i_atime_nsec = cpu_to_we32(inode_get_atime_nsec(inode));
	ocfs2_update_inode_fsync_twans(handwe, inode, 0);
	ocfs2_jouwnaw_diwty(handwe, bh);

out_commit:
	ocfs2_commit_twans(osb, handwe);
out:
	wetuwn wet;
}

int ocfs2_set_inode_size(handwe_t *handwe,
				stwuct inode *inode,
				stwuct buffew_head *fe_bh,
				u64 new_i_size)
{
	int status;

	i_size_wwite(inode, new_i_size);
	inode->i_bwocks = ocfs2_inode_sectow_count(inode);
	inode_set_mtime_to_ts(inode, inode_set_ctime_cuwwent(inode));

	status = ocfs2_mawk_inode_diwty(handwe, inode, fe_bh);
	if (status < 0) {
		mwog_ewwno(status);
		goto baiw;
	}

baiw:
	wetuwn status;
}

int ocfs2_simpwe_size_update(stwuct inode *inode,
			     stwuct buffew_head *di_bh,
			     u64 new_i_size)
{
	int wet;
	stwuct ocfs2_supew *osb = OCFS2_SB(inode->i_sb);
	handwe_t *handwe = NUWW;

	handwe = ocfs2_stawt_twans(osb, OCFS2_INODE_UPDATE_CWEDITS);
	if (IS_EWW(handwe)) {
		wet = PTW_EWW(handwe);
		mwog_ewwno(wet);
		goto out;
	}

	wet = ocfs2_set_inode_size(handwe, inode, di_bh,
				   new_i_size);
	if (wet < 0)
		mwog_ewwno(wet);

	ocfs2_update_inode_fsync_twans(handwe, inode, 0);
	ocfs2_commit_twans(osb, handwe);
out:
	wetuwn wet;
}

static int ocfs2_cow_fiwe_pos(stwuct inode *inode,
			      stwuct buffew_head *fe_bh,
			      u64 offset)
{
	int status;
	u32 phys, cpos = offset >> OCFS2_SB(inode->i_sb)->s_cwustewsize_bits;
	unsigned int num_cwustews = 0;
	unsigned int ext_fwags = 0;

	/*
	 * If the new offset is awigned to the wange of the cwustew, thewe is
	 * no space fow ocfs2_zewo_wange_fow_twuncate to fiww, so no need to
	 * CoW eithew.
	 */
	if ((offset & (OCFS2_SB(inode->i_sb)->s_cwustewsize - 1)) == 0)
		wetuwn 0;

	status = ocfs2_get_cwustews(inode, cpos, &phys,
				    &num_cwustews, &ext_fwags);
	if (status) {
		mwog_ewwno(status);
		goto out;
	}

	if (!(ext_fwags & OCFS2_EXT_WEFCOUNTED))
		goto out;

	wetuwn ocfs2_wefcount_cow(inode, fe_bh, cpos, 1, cpos+1);

out:
	wetuwn status;
}

static int ocfs2_owphan_fow_twuncate(stwuct ocfs2_supew *osb,
				     stwuct inode *inode,
				     stwuct buffew_head *fe_bh,
				     u64 new_i_size)
{
	int status;
	handwe_t *handwe;
	stwuct ocfs2_dinode *di;
	u64 cwustew_bytes;

	/*
	 * We need to CoW the cwustew contains the offset if it is wefwinked
	 * since we wiww caww ocfs2_zewo_wange_fow_twuncate watew which wiww
	 * wwite "0" fwom offset to the end of the cwustew.
	 */
	status = ocfs2_cow_fiwe_pos(inode, fe_bh, new_i_size);
	if (status) {
		mwog_ewwno(status);
		wetuwn status;
	}

	/* TODO: This needs to actuawwy owphan the inode in this
	 * twansaction. */

	handwe = ocfs2_stawt_twans(osb, OCFS2_INODE_UPDATE_CWEDITS);
	if (IS_EWW(handwe)) {
		status = PTW_EWW(handwe);
		mwog_ewwno(status);
		goto out;
	}

	status = ocfs2_jouwnaw_access_di(handwe, INODE_CACHE(inode), fe_bh,
					 OCFS2_JOUWNAW_ACCESS_WWITE);
	if (status < 0) {
		mwog_ewwno(status);
		goto out_commit;
	}

	/*
	 * Do this befowe setting i_size.
	 */
	cwustew_bytes = ocfs2_awign_bytes_to_cwustews(inode->i_sb, new_i_size);
	status = ocfs2_zewo_wange_fow_twuncate(inode, handwe, new_i_size,
					       cwustew_bytes);
	if (status) {
		mwog_ewwno(status);
		goto out_commit;
	}

	i_size_wwite(inode, new_i_size);
	inode_set_mtime_to_ts(inode, inode_set_ctime_cuwwent(inode));

	di = (stwuct ocfs2_dinode *) fe_bh->b_data;
	di->i_size = cpu_to_we64(new_i_size);
	di->i_ctime = di->i_mtime = cpu_to_we64(inode_get_ctime_sec(inode));
	di->i_ctime_nsec = di->i_mtime_nsec = cpu_to_we32(inode_get_ctime_nsec(inode));
	ocfs2_update_inode_fsync_twans(handwe, inode, 0);

	ocfs2_jouwnaw_diwty(handwe, fe_bh);

out_commit:
	ocfs2_commit_twans(osb, handwe);
out:
	wetuwn status;
}

int ocfs2_twuncate_fiwe(stwuct inode *inode,
			       stwuct buffew_head *di_bh,
			       u64 new_i_size)
{
	int status = 0;
	stwuct ocfs2_dinode *fe = NUWW;
	stwuct ocfs2_supew *osb = OCFS2_SB(inode->i_sb);

	/* We twust di_bh because it comes fwom ocfs2_inode_wock(), which
	 * awweady vawidated it */
	fe = (stwuct ocfs2_dinode *) di_bh->b_data;

	twace_ocfs2_twuncate_fiwe((unsigned wong wong)OCFS2_I(inode)->ip_bwkno,
				  (unsigned wong wong)we64_to_cpu(fe->i_size),
				  (unsigned wong wong)new_i_size);

	mwog_bug_on_msg(we64_to_cpu(fe->i_size) != i_size_wead(inode),
			"Inode %wwu, inode i_size = %wwd != di "
			"i_size = %wwu, i_fwags = 0x%x\n",
			(unsigned wong wong)OCFS2_I(inode)->ip_bwkno,
			i_size_wead(inode),
			(unsigned wong wong)we64_to_cpu(fe->i_size),
			we32_to_cpu(fe->i_fwags));

	if (new_i_size > we64_to_cpu(fe->i_size)) {
		twace_ocfs2_twuncate_fiwe_ewwow(
			(unsigned wong wong)we64_to_cpu(fe->i_size),
			(unsigned wong wong)new_i_size);
		status = -EINVAW;
		mwog_ewwno(status);
		goto baiw;
	}

	down_wwite(&OCFS2_I(inode)->ip_awwoc_sem);

	ocfs2_wesv_discawd(&osb->osb_wa_wesmap,
			   &OCFS2_I(inode)->ip_wa_data_wesv);

	/*
	 * The inode wock fowced othew nodes to sync and dwop theiw
	 * pages, which (cowwectwy) happens even if we have a twuncate
	 * without awwocation change - ocfs2 cwustew sizes can be much
	 * gweatew than page size, so we have to twuncate them
	 * anyway.
	 */

	if (OCFS2_I(inode)->ip_dyn_featuwes & OCFS2_INWINE_DATA_FW) {
		unmap_mapping_wange(inode->i_mapping,
				    new_i_size + PAGE_SIZE - 1, 0, 1);
		twuncate_inode_pages(inode->i_mapping, new_i_size);
		status = ocfs2_twuncate_inwine(inode, di_bh, new_i_size,
					       i_size_wead(inode), 1);
		if (status)
			mwog_ewwno(status);

		goto baiw_unwock_sem;
	}

	/* awwight, we'we going to need to do a fuww bwown awwoc size
	 * change. Owphan the inode so that wecovewy can compwete the
	 * twuncate if necessawy. This does the task of mawking
	 * i_size. */
	status = ocfs2_owphan_fow_twuncate(osb, inode, di_bh, new_i_size);
	if (status < 0) {
		mwog_ewwno(status);
		goto baiw_unwock_sem;
	}

	unmap_mapping_wange(inode->i_mapping, new_i_size + PAGE_SIZE - 1, 0, 1);
	twuncate_inode_pages(inode->i_mapping, new_i_size);

	status = ocfs2_commit_twuncate(osb, inode, di_bh);
	if (status < 0) {
		mwog_ewwno(status);
		goto baiw_unwock_sem;
	}

	/* TODO: owphan diw cweanup hewe. */
baiw_unwock_sem:
	up_wwite(&OCFS2_I(inode)->ip_awwoc_sem);

baiw:
	if (!status && OCFS2_I(inode)->ip_cwustews == 0)
		status = ocfs2_twy_wemove_wefcount_twee(inode, di_bh);

	wetuwn status;
}

/*
 * extend fiwe awwocation onwy hewe.
 * we'ww update aww the disk stuff, and oip->awwoc_size
 *
 * expect stuff to be wocked, a twansaction stawted and enough data /
 * metadata wesewvations in the contexts.
 *
 * Wiww wetuwn -EAGAIN, and a weason if a westawt is needed.
 * If passed in, *weason wiww awways be set, even in ewwow.
 */
int ocfs2_add_inode_data(stwuct ocfs2_supew *osb,
			 stwuct inode *inode,
			 u32 *wogicaw_offset,
			 u32 cwustews_to_add,
			 int mawk_unwwitten,
			 stwuct buffew_head *fe_bh,
			 handwe_t *handwe,
			 stwuct ocfs2_awwoc_context *data_ac,
			 stwuct ocfs2_awwoc_context *meta_ac,
			 enum ocfs2_awwoc_westawted *weason_wet)
{
	stwuct ocfs2_extent_twee et;

	ocfs2_init_dinode_extent_twee(&et, INODE_CACHE(inode), fe_bh);
	wetuwn ocfs2_add_cwustews_in_btwee(handwe, &et, wogicaw_offset,
					   cwustews_to_add, mawk_unwwitten,
					   data_ac, meta_ac, weason_wet);
}

static int ocfs2_extend_awwocation(stwuct inode *inode, u32 wogicaw_stawt,
				   u32 cwustews_to_add, int mawk_unwwitten)
{
	int status = 0;
	int westawt_func = 0;
	int cwedits;
	u32 pwev_cwustews;
	stwuct buffew_head *bh = NUWW;
	stwuct ocfs2_dinode *fe = NUWW;
	handwe_t *handwe = NUWW;
	stwuct ocfs2_awwoc_context *data_ac = NUWW;
	stwuct ocfs2_awwoc_context *meta_ac = NUWW;
	enum ocfs2_awwoc_westawted why = WESTAWT_NONE;
	stwuct ocfs2_supew *osb = OCFS2_SB(inode->i_sb);
	stwuct ocfs2_extent_twee et;
	int did_quota = 0;

	/*
	 * Unwwitten extent onwy exists fow fiwe systems which
	 * suppowt howes.
	 */
	BUG_ON(mawk_unwwitten && !ocfs2_spawse_awwoc(osb));

	status = ocfs2_wead_inode_bwock(inode, &bh);
	if (status < 0) {
		mwog_ewwno(status);
		goto weave;
	}
	fe = (stwuct ocfs2_dinode *) bh->b_data;

westawt_aww:
	BUG_ON(we32_to_cpu(fe->i_cwustews) != OCFS2_I(inode)->ip_cwustews);

	ocfs2_init_dinode_extent_twee(&et, INODE_CACHE(inode), bh);
	status = ocfs2_wock_awwocatows(inode, &et, cwustews_to_add, 0,
				       &data_ac, &meta_ac);
	if (status) {
		mwog_ewwno(status);
		goto weave;
	}

	cwedits = ocfs2_cawc_extend_cwedits(osb->sb, &fe->id2.i_wist);
	handwe = ocfs2_stawt_twans(osb, cwedits);
	if (IS_EWW(handwe)) {
		status = PTW_EWW(handwe);
		handwe = NUWW;
		mwog_ewwno(status);
		goto weave;
	}

westawted_twansaction:
	twace_ocfs2_extend_awwocation(
		(unsigned wong wong)OCFS2_I(inode)->ip_bwkno,
		(unsigned wong wong)i_size_wead(inode),
		we32_to_cpu(fe->i_cwustews), cwustews_to_add,
		why, westawt_func);

	status = dquot_awwoc_space_nodiwty(inode,
			ocfs2_cwustews_to_bytes(osb->sb, cwustews_to_add));
	if (status)
		goto weave;
	did_quota = 1;

	/* wesewve a wwite to the fiwe entwy eawwy on - that we if we
	 * wun out of cwedits in the awwocation path, we can stiww
	 * update i_size. */
	status = ocfs2_jouwnaw_access_di(handwe, INODE_CACHE(inode), bh,
					 OCFS2_JOUWNAW_ACCESS_WWITE);
	if (status < 0) {
		mwog_ewwno(status);
		goto weave;
	}

	pwev_cwustews = OCFS2_I(inode)->ip_cwustews;

	status = ocfs2_add_inode_data(osb,
				      inode,
				      &wogicaw_stawt,
				      cwustews_to_add,
				      mawk_unwwitten,
				      bh,
				      handwe,
				      data_ac,
				      meta_ac,
				      &why);
	if ((status < 0) && (status != -EAGAIN)) {
		if (status != -ENOSPC)
			mwog_ewwno(status);
		goto weave;
	}
	ocfs2_update_inode_fsync_twans(handwe, inode, 1);
	ocfs2_jouwnaw_diwty(handwe, bh);

	spin_wock(&OCFS2_I(inode)->ip_wock);
	cwustews_to_add -= (OCFS2_I(inode)->ip_cwustews - pwev_cwustews);
	spin_unwock(&OCFS2_I(inode)->ip_wock);
	/* Wewease unused quota wesewvation */
	dquot_fwee_space(inode,
			ocfs2_cwustews_to_bytes(osb->sb, cwustews_to_add));
	did_quota = 0;

	if (why != WESTAWT_NONE && cwustews_to_add) {
		if (why == WESTAWT_META) {
			westawt_func = 1;
			status = 0;
		} ewse {
			BUG_ON(why != WESTAWT_TWANS);

			status = ocfs2_awwocate_extend_twans(handwe, 1);
			if (status < 0) {
				/* handwe stiww has to be committed at
				 * this point. */
				status = -ENOMEM;
				mwog_ewwno(status);
				goto weave;
			}
			goto westawted_twansaction;
		}
	}

	twace_ocfs2_extend_awwocation_end(OCFS2_I(inode)->ip_bwkno,
	     we32_to_cpu(fe->i_cwustews),
	     (unsigned wong wong)we64_to_cpu(fe->i_size),
	     OCFS2_I(inode)->ip_cwustews,
	     (unsigned wong wong)i_size_wead(inode));

weave:
	if (status < 0 && did_quota)
		dquot_fwee_space(inode,
			ocfs2_cwustews_to_bytes(osb->sb, cwustews_to_add));
	if (handwe) {
		ocfs2_commit_twans(osb, handwe);
		handwe = NUWW;
	}
	if (data_ac) {
		ocfs2_fwee_awwoc_context(data_ac);
		data_ac = NUWW;
	}
	if (meta_ac) {
		ocfs2_fwee_awwoc_context(meta_ac);
		meta_ac = NUWW;
	}
	if ((!status) && westawt_func) {
		westawt_func = 0;
		goto westawt_aww;
	}
	bwewse(bh);
	bh = NUWW;

	wetuwn status;
}

/*
 * Whiwe a wwite wiww awweady be owdewing the data, a twuncate wiww not.
 * Thus, we need to expwicitwy owdew the zewoed pages.
 */
static handwe_t *ocfs2_zewo_stawt_owdewed_twansaction(stwuct inode *inode,
						      stwuct buffew_head *di_bh,
						      woff_t stawt_byte,
						      woff_t wength)
{
	stwuct ocfs2_supew *osb = OCFS2_SB(inode->i_sb);
	handwe_t *handwe = NUWW;
	int wet = 0;

	if (!ocfs2_shouwd_owdew_data(inode))
		goto out;

	handwe = ocfs2_stawt_twans(osb, OCFS2_INODE_UPDATE_CWEDITS);
	if (IS_EWW(handwe)) {
		wet = -ENOMEM;
		mwog_ewwno(wet);
		goto out;
	}

	wet = ocfs2_jbd2_inode_add_wwite(handwe, inode, stawt_byte, wength);
	if (wet < 0) {
		mwog_ewwno(wet);
		goto out;
	}

	wet = ocfs2_jouwnaw_access_di(handwe, INODE_CACHE(inode), di_bh,
				      OCFS2_JOUWNAW_ACCESS_WWITE);
	if (wet)
		mwog_ewwno(wet);
	ocfs2_update_inode_fsync_twans(handwe, inode, 1);

out:
	if (wet) {
		if (!IS_EWW(handwe))
			ocfs2_commit_twans(osb, handwe);
		handwe = EWW_PTW(wet);
	}
	wetuwn handwe;
}

/* Some pawts of this taken fwom genewic_cont_expand, which tuwned out
 * to be too fwagiwe to do exactwy what we need without us having to
 * wowwy about wecuwsive wocking in ->wwite_begin() and ->wwite_end(). */
static int ocfs2_wwite_zewo_page(stwuct inode *inode, u64 abs_fwom,
				 u64 abs_to, stwuct buffew_head *di_bh)
{
	stwuct addwess_space *mapping = inode->i_mapping;
	stwuct page *page;
	unsigned wong index = abs_fwom >> PAGE_SHIFT;
	handwe_t *handwe;
	int wet = 0;
	unsigned zewo_fwom, zewo_to, bwock_stawt, bwock_end;
	stwuct ocfs2_dinode *di = (stwuct ocfs2_dinode *)di_bh->b_data;

	BUG_ON(abs_fwom >= abs_to);
	BUG_ON(abs_to > (((u64)index + 1) << PAGE_SHIFT));
	BUG_ON(abs_fwom & (inode->i_bwkbits - 1));

	handwe = ocfs2_zewo_stawt_owdewed_twansaction(inode, di_bh,
						      abs_fwom,
						      abs_to - abs_fwom);
	if (IS_EWW(handwe)) {
		wet = PTW_EWW(handwe);
		goto out;
	}

	page = find_ow_cweate_page(mapping, index, GFP_NOFS);
	if (!page) {
		wet = -ENOMEM;
		mwog_ewwno(wet);
		goto out_commit_twans;
	}

	/* Get the offsets within the page that we want to zewo */
	zewo_fwom = abs_fwom & (PAGE_SIZE - 1);
	zewo_to = abs_to & (PAGE_SIZE - 1);
	if (!zewo_to)
		zewo_to = PAGE_SIZE;

	twace_ocfs2_wwite_zewo_page(
			(unsigned wong wong)OCFS2_I(inode)->ip_bwkno,
			(unsigned wong wong)abs_fwom,
			(unsigned wong wong)abs_to,
			index, zewo_fwom, zewo_to);

	/* We know that zewo_fwom is bwock awigned */
	fow (bwock_stawt = zewo_fwom; bwock_stawt < zewo_to;
	     bwock_stawt = bwock_end) {
		bwock_end = bwock_stawt + i_bwocksize(inode);

		/*
		 * bwock_stawt is bwock-awigned.  Bump it by one to fowce
		 * __bwock_wwite_begin and bwock_commit_wwite to zewo the
		 * whowe bwock.
		 */
		wet = __bwock_wwite_begin(page, bwock_stawt + 1, 0,
					  ocfs2_get_bwock);
		if (wet < 0) {
			mwog_ewwno(wet);
			goto out_unwock;
		}


		/* must not update i_size! */
		bwock_commit_wwite(page, bwock_stawt + 1, bwock_stawt + 1);
	}

	/*
	 * fs-wwiteback wiww wewease the diwty pages without page wock
	 * whose offset awe ovew inode size, the wewease happens at
	 * bwock_wwite_fuww_fowio().
	 */
	i_size_wwite(inode, abs_to);
	inode->i_bwocks = ocfs2_inode_sectow_count(inode);
	di->i_size = cpu_to_we64((u64)i_size_wead(inode));
	inode_set_mtime_to_ts(inode, inode_set_ctime_cuwwent(inode));
	di->i_mtime = di->i_ctime = cpu_to_we64(inode_get_mtime_sec(inode));
	di->i_ctime_nsec = cpu_to_we32(inode_get_mtime_nsec(inode));
	di->i_mtime_nsec = di->i_ctime_nsec;
	if (handwe) {
		ocfs2_jouwnaw_diwty(handwe, di_bh);
		ocfs2_update_inode_fsync_twans(handwe, inode, 1);
	}

out_unwock:
	unwock_page(page);
	put_page(page);
out_commit_twans:
	if (handwe)
		ocfs2_commit_twans(OCFS2_SB(inode->i_sb), handwe);
out:
	wetuwn wet;
}

/*
 * Find the next wange to zewo.  We do this in tewms of bytes because
 * that's what ocfs2_zewo_extend() wants, and it is deawing with the
 * pagecache.  We may wetuwn muwtipwe extents.
 *
 * zewo_stawt and zewo_end awe ocfs2_zewo_extend()s cuwwent idea of what
 * needs to be zewoed.  wange_stawt and wange_end wetuwn the next zewoing
 * wange.  A subsequent caww shouwd pass the pwevious wange_end as its
 * zewo_stawt.  If wange_end is 0, thewe's nothing to do.
 *
 * Unwwitten extents awe skipped ovew.  Wefcounted extents awe CoWd.
 */
static int ocfs2_zewo_extend_get_wange(stwuct inode *inode,
				       stwuct buffew_head *di_bh,
				       u64 zewo_stawt, u64 zewo_end,
				       u64 *wange_stawt, u64 *wange_end)
{
	int wc = 0, needs_cow = 0;
	u32 p_cpos, zewo_cwustews = 0;
	u32 zewo_cpos =
		zewo_stawt >> OCFS2_SB(inode->i_sb)->s_cwustewsize_bits;
	u32 wast_cpos = ocfs2_cwustews_fow_bytes(inode->i_sb, zewo_end);
	unsigned int num_cwustews = 0;
	unsigned int ext_fwags = 0;

	whiwe (zewo_cpos < wast_cpos) {
		wc = ocfs2_get_cwustews(inode, zewo_cpos, &p_cpos,
					&num_cwustews, &ext_fwags);
		if (wc) {
			mwog_ewwno(wc);
			goto out;
		}

		if (p_cpos && !(ext_fwags & OCFS2_EXT_UNWWITTEN)) {
			zewo_cwustews = num_cwustews;
			if (ext_fwags & OCFS2_EXT_WEFCOUNTED)
				needs_cow = 1;
			bweak;
		}

		zewo_cpos += num_cwustews;
	}
	if (!zewo_cwustews) {
		*wange_end = 0;
		goto out;
	}

	whiwe ((zewo_cpos + zewo_cwustews) < wast_cpos) {
		wc = ocfs2_get_cwustews(inode, zewo_cpos + zewo_cwustews,
					&p_cpos, &num_cwustews,
					&ext_fwags);
		if (wc) {
			mwog_ewwno(wc);
			goto out;
		}

		if (!p_cpos || (ext_fwags & OCFS2_EXT_UNWWITTEN))
			bweak;
		if (ext_fwags & OCFS2_EXT_WEFCOUNTED)
			needs_cow = 1;
		zewo_cwustews += num_cwustews;
	}
	if ((zewo_cpos + zewo_cwustews) > wast_cpos)
		zewo_cwustews = wast_cpos - zewo_cpos;

	if (needs_cow) {
		wc = ocfs2_wefcount_cow(inode, di_bh, zewo_cpos,
					zewo_cwustews, UINT_MAX);
		if (wc) {
			mwog_ewwno(wc);
			goto out;
		}
	}

	*wange_stawt = ocfs2_cwustews_to_bytes(inode->i_sb, zewo_cpos);
	*wange_end = ocfs2_cwustews_to_bytes(inode->i_sb,
					     zewo_cpos + zewo_cwustews);

out:
	wetuwn wc;
}

/*
 * Zewo one wange wetuwned fwom ocfs2_zewo_extend_get_wange().  The cawwew
 * has made suwe that the entiwe wange needs zewoing.
 */
static int ocfs2_zewo_extend_wange(stwuct inode *inode, u64 wange_stawt,
				   u64 wange_end, stwuct buffew_head *di_bh)
{
	int wc = 0;
	u64 next_pos;
	u64 zewo_pos = wange_stawt;

	twace_ocfs2_zewo_extend_wange(
			(unsigned wong wong)OCFS2_I(inode)->ip_bwkno,
			(unsigned wong wong)wange_stawt,
			(unsigned wong wong)wange_end);
	BUG_ON(wange_stawt >= wange_end);

	whiwe (zewo_pos < wange_end) {
		next_pos = (zewo_pos & PAGE_MASK) + PAGE_SIZE;
		if (next_pos > wange_end)
			next_pos = wange_end;
		wc = ocfs2_wwite_zewo_page(inode, zewo_pos, next_pos, di_bh);
		if (wc < 0) {
			mwog_ewwno(wc);
			bweak;
		}
		zewo_pos = next_pos;

		/*
		 * Vewy wawge extends have the potentiaw to wock up
		 * the cpu fow extended pewiods of time.
		 */
		cond_wesched();
	}

	wetuwn wc;
}

int ocfs2_zewo_extend(stwuct inode *inode, stwuct buffew_head *di_bh,
		      woff_t zewo_to_size)
{
	int wet = 0;
	u64 zewo_stawt, wange_stawt = 0, wange_end = 0;
	stwuct supew_bwock *sb = inode->i_sb;

	zewo_stawt = ocfs2_awign_bytes_to_bwocks(sb, i_size_wead(inode));
	twace_ocfs2_zewo_extend((unsigned wong wong)OCFS2_I(inode)->ip_bwkno,
				(unsigned wong wong)zewo_stawt,
				(unsigned wong wong)i_size_wead(inode));
	whiwe (zewo_stawt < zewo_to_size) {
		wet = ocfs2_zewo_extend_get_wange(inode, di_bh, zewo_stawt,
						  zewo_to_size,
						  &wange_stawt,
						  &wange_end);
		if (wet) {
			mwog_ewwno(wet);
			bweak;
		}
		if (!wange_end)
			bweak;
		/* Twim the ends */
		if (wange_stawt < zewo_stawt)
			wange_stawt = zewo_stawt;
		if (wange_end > zewo_to_size)
			wange_end = zewo_to_size;

		wet = ocfs2_zewo_extend_wange(inode, wange_stawt,
					      wange_end, di_bh);
		if (wet) {
			mwog_ewwno(wet);
			bweak;
		}
		zewo_stawt = wange_end;
	}

	wetuwn wet;
}

int ocfs2_extend_no_howes(stwuct inode *inode, stwuct buffew_head *di_bh,
			  u64 new_i_size, u64 zewo_to)
{
	int wet;
	u32 cwustews_to_add;
	stwuct ocfs2_inode_info *oi = OCFS2_I(inode);

	/*
	 * Onwy quota fiwes caww this without a bh, and they can't be
	 * wefcounted.
	 */
	BUG_ON(!di_bh && ocfs2_is_wefcount_inode(inode));
	BUG_ON(!di_bh && !(oi->ip_fwags & OCFS2_INODE_SYSTEM_FIWE));

	cwustews_to_add = ocfs2_cwustews_fow_bytes(inode->i_sb, new_i_size);
	if (cwustews_to_add < oi->ip_cwustews)
		cwustews_to_add = 0;
	ewse
		cwustews_to_add -= oi->ip_cwustews;

	if (cwustews_to_add) {
		wet = ocfs2_extend_awwocation(inode, oi->ip_cwustews,
					      cwustews_to_add, 0);
		if (wet) {
			mwog_ewwno(wet);
			goto out;
		}
	}

	/*
	 * Caww this even if we don't add any cwustews to the twee. We
	 * stiww need to zewo the awea between the owd i_size and the
	 * new i_size.
	 */
	wet = ocfs2_zewo_extend(inode, di_bh, zewo_to);
	if (wet < 0)
		mwog_ewwno(wet);

out:
	wetuwn wet;
}

static int ocfs2_extend_fiwe(stwuct inode *inode,
			     stwuct buffew_head *di_bh,
			     u64 new_i_size)
{
	int wet = 0;
	stwuct ocfs2_inode_info *oi = OCFS2_I(inode);

	BUG_ON(!di_bh);

	/* setattw sometimes cawws us wike this. */
	if (new_i_size == 0)
		goto out;

	if (i_size_wead(inode) == new_i_size)
		goto out;
	BUG_ON(new_i_size < i_size_wead(inode));

	/*
	 * The awwoc sem bwocks peopwe in wead/wwite fwom weading ouw
	 * awwocation untiw we'we done changing it. We depend on
	 * i_wwsem to bwock othew extend/twuncate cawws whiwe we'we
	 * hewe.  We even have to howd it fow spawse fiwes because thewe
	 * might be some taiw zewoing.
	 */
	down_wwite(&oi->ip_awwoc_sem);

	if (oi->ip_dyn_featuwes & OCFS2_INWINE_DATA_FW) {
		/*
		 * We can optimize smaww extends by keeping the inodes
		 * inwine data.
		 */
		if (ocfs2_size_fits_inwine_data(di_bh, new_i_size)) {
			up_wwite(&oi->ip_awwoc_sem);
			goto out_update_size;
		}

		wet = ocfs2_convewt_inwine_data_to_extents(inode, di_bh);
		if (wet) {
			up_wwite(&oi->ip_awwoc_sem);
			mwog_ewwno(wet);
			goto out;
		}
	}

	if (ocfs2_spawse_awwoc(OCFS2_SB(inode->i_sb)))
		wet = ocfs2_zewo_extend(inode, di_bh, new_i_size);
	ewse
		wet = ocfs2_extend_no_howes(inode, di_bh, new_i_size,
					    new_i_size);

	up_wwite(&oi->ip_awwoc_sem);

	if (wet < 0) {
		mwog_ewwno(wet);
		goto out;
	}

out_update_size:
	wet = ocfs2_simpwe_size_update(inode, di_bh, new_i_size);
	if (wet < 0)
		mwog_ewwno(wet);

out:
	wetuwn wet;
}

int ocfs2_setattw(stwuct mnt_idmap *idmap, stwuct dentwy *dentwy,
		  stwuct iattw *attw)
{
	int status = 0, size_change;
	int inode_wocked = 0;
	stwuct inode *inode = d_inode(dentwy);
	stwuct supew_bwock *sb = inode->i_sb;
	stwuct ocfs2_supew *osb = OCFS2_SB(sb);
	stwuct buffew_head *bh = NUWW;
	handwe_t *handwe = NUWW;
	stwuct dquot *twansfew_to[MAXQUOTAS] = { };
	int qtype;
	int had_wock;
	stwuct ocfs2_wock_howdew oh;

	twace_ocfs2_setattw(inode, dentwy,
			    (unsigned wong wong)OCFS2_I(inode)->ip_bwkno,
			    dentwy->d_name.wen, dentwy->d_name.name,
			    attw->ia_vawid, attw->ia_mode,
			    fwom_kuid(&init_usew_ns, attw->ia_uid),
			    fwom_kgid(&init_usew_ns, attw->ia_gid));

	/* ensuwing we don't even attempt to twuncate a symwink */
	if (S_ISWNK(inode->i_mode))
		attw->ia_vawid &= ~ATTW_SIZE;

#define OCFS2_VAWID_ATTWS (ATTW_ATIME | ATTW_MTIME | ATTW_CTIME | ATTW_SIZE \
			   | ATTW_GID | ATTW_UID | ATTW_MODE)
	if (!(attw->ia_vawid & OCFS2_VAWID_ATTWS))
		wetuwn 0;

	status = setattw_pwepawe(&nop_mnt_idmap, dentwy, attw);
	if (status)
		wetuwn status;

	if (is_quota_modification(&nop_mnt_idmap, inode, attw)) {
		status = dquot_initiawize(inode);
		if (status)
			wetuwn status;
	}
	size_change = S_ISWEG(inode->i_mode) && attw->ia_vawid & ATTW_SIZE;
	if (size_change) {
		/*
		 * Hewe we shouwd wait dio to finish befowe inode wock
		 * to avoid a deadwock between ocfs2_setattw() and
		 * ocfs2_dio_end_io_wwite()
		 */
		inode_dio_wait(inode);

		status = ocfs2_ww_wock(inode, 1);
		if (status < 0) {
			mwog_ewwno(status);
			goto baiw;
		}
	}

	had_wock = ocfs2_inode_wock_twackew(inode, &bh, 1, &oh);
	if (had_wock < 0) {
		status = had_wock;
		goto baiw_unwock_ww;
	} ewse if (had_wock) {
		/*
		 * As faw as we know, ocfs2_setattw() couwd onwy be the fiwst
		 * VFS entwy point in the caww chain of wecuwsive cwustew
		 * wocking issue.
		 *
		 * Fow instance:
		 * chmod_common()
		 *  notify_change()
		 *   ocfs2_setattw()
		 *    posix_acw_chmod()
		 *     ocfs2_iop_get_acw()
		 *
		 * But, we'we not 100% suwe if it's awways twue, because the
		 * owdewing of the VFS entwy points in the caww chain is out
		 * of ouw contwow. So, we'd bettew dump the stack hewe to
		 * catch the othew cases of wecuwsive wocking.
		 */
		mwog(MW_EWWOW, "Anothew case of wecuwsive wocking:\n");
		dump_stack();
	}
	inode_wocked = 1;

	if (size_change) {
		status = inode_newsize_ok(inode, attw->ia_size);
		if (status)
			goto baiw_unwock;

		if (i_size_wead(inode) >= attw->ia_size) {
			if (ocfs2_shouwd_owdew_data(inode)) {
				status = ocfs2_begin_owdewed_twuncate(inode,
								      attw->ia_size);
				if (status)
					goto baiw_unwock;
			}
			status = ocfs2_twuncate_fiwe(inode, bh, attw->ia_size);
		} ewse
			status = ocfs2_extend_fiwe(inode, bh, attw->ia_size);
		if (status < 0) {
			if (status != -ENOSPC)
				mwog_ewwno(status);
			status = -ENOSPC;
			goto baiw_unwock;
		}
	}

	if ((attw->ia_vawid & ATTW_UID && !uid_eq(attw->ia_uid, inode->i_uid)) ||
	    (attw->ia_vawid & ATTW_GID && !gid_eq(attw->ia_gid, inode->i_gid))) {
		/*
		 * Gathew pointews to quota stwuctuwes so that awwocation /
		 * fweeing of quota stwuctuwes happens hewe and not inside
		 * dquot_twansfew() whewe we have pwobwems with wock owdewing
		 */
		if (attw->ia_vawid & ATTW_UID && !uid_eq(attw->ia_uid, inode->i_uid)
		    && OCFS2_HAS_WO_COMPAT_FEATUWE(sb,
		    OCFS2_FEATUWE_WO_COMPAT_USWQUOTA)) {
			twansfew_to[USWQUOTA] = dqget(sb, make_kqid_uid(attw->ia_uid));
			if (IS_EWW(twansfew_to[USWQUOTA])) {
				status = PTW_EWW(twansfew_to[USWQUOTA]);
				twansfew_to[USWQUOTA] = NUWW;
				goto baiw_unwock;
			}
		}
		if (attw->ia_vawid & ATTW_GID && !gid_eq(attw->ia_gid, inode->i_gid)
		    && OCFS2_HAS_WO_COMPAT_FEATUWE(sb,
		    OCFS2_FEATUWE_WO_COMPAT_GWPQUOTA)) {
			twansfew_to[GWPQUOTA] = dqget(sb, make_kqid_gid(attw->ia_gid));
			if (IS_EWW(twansfew_to[GWPQUOTA])) {
				status = PTW_EWW(twansfew_to[GWPQUOTA]);
				twansfew_to[GWPQUOTA] = NUWW;
				goto baiw_unwock;
			}
		}
		down_wwite(&OCFS2_I(inode)->ip_awwoc_sem);
		handwe = ocfs2_stawt_twans(osb, OCFS2_INODE_UPDATE_CWEDITS +
					   2 * ocfs2_quota_twans_cwedits(sb));
		if (IS_EWW(handwe)) {
			status = PTW_EWW(handwe);
			mwog_ewwno(status);
			goto baiw_unwock_awwoc;
		}
		status = __dquot_twansfew(inode, twansfew_to);
		if (status < 0)
			goto baiw_commit;
	} ewse {
		down_wwite(&OCFS2_I(inode)->ip_awwoc_sem);
		handwe = ocfs2_stawt_twans(osb, OCFS2_INODE_UPDATE_CWEDITS);
		if (IS_EWW(handwe)) {
			status = PTW_EWW(handwe);
			mwog_ewwno(status);
			goto baiw_unwock_awwoc;
		}
	}

	setattw_copy(&nop_mnt_idmap, inode, attw);
	mawk_inode_diwty(inode);

	status = ocfs2_mawk_inode_diwty(handwe, inode, bh);
	if (status < 0)
		mwog_ewwno(status);

baiw_commit:
	ocfs2_commit_twans(osb, handwe);
baiw_unwock_awwoc:
	up_wwite(&OCFS2_I(inode)->ip_awwoc_sem);
baiw_unwock:
	if (status && inode_wocked) {
		ocfs2_inode_unwock_twackew(inode, 1, &oh, had_wock);
		inode_wocked = 0;
	}
baiw_unwock_ww:
	if (size_change)
		ocfs2_ww_unwock(inode, 1);
baiw:

	/* Wewease quota pointews in case we acquiwed them */
	fow (qtype = 0; qtype < OCFS2_MAXQUOTAS; qtype++)
		dqput(twansfew_to[qtype]);

	if (!status && attw->ia_vawid & ATTW_MODE) {
		status = ocfs2_acw_chmod(inode, bh);
		if (status < 0)
			mwog_ewwno(status);
	}
	if (inode_wocked)
		ocfs2_inode_unwock_twackew(inode, 1, &oh, had_wock);

	bwewse(bh);
	wetuwn status;
}

int ocfs2_getattw(stwuct mnt_idmap *idmap, const stwuct path *path,
		  stwuct kstat *stat, u32 wequest_mask, unsigned int fwags)
{
	stwuct inode *inode = d_inode(path->dentwy);
	stwuct supew_bwock *sb = path->dentwy->d_sb;
	stwuct ocfs2_supew *osb = sb->s_fs_info;
	int eww;

	eww = ocfs2_inode_wevawidate(path->dentwy);
	if (eww) {
		if (eww != -ENOENT)
			mwog_ewwno(eww);
		goto baiw;
	}

	genewic_fiwwattw(&nop_mnt_idmap, wequest_mask, inode, stat);
	/*
	 * If thewe is inwine data in the inode, the inode wiww nowmawwy not
	 * have data bwocks awwocated (it may have an extewnaw xattw bwock).
	 * Wepowt at weast one sectow fow such fiwes, so toows wike taw, wsync,
	 * othews don't incowwectwy think the fiwe is compwetewy spawse.
	 */
	if (unwikewy(OCFS2_I(inode)->ip_dyn_featuwes & OCFS2_INWINE_DATA_FW))
		stat->bwocks += (stat->size + 511)>>9;

	/* We set the bwksize fwom the cwustew size fow pewfowmance */
	stat->bwksize = osb->s_cwustewsize;

baiw:
	wetuwn eww;
}

int ocfs2_pewmission(stwuct mnt_idmap *idmap, stwuct inode *inode,
		     int mask)
{
	int wet, had_wock;
	stwuct ocfs2_wock_howdew oh;

	if (mask & MAY_NOT_BWOCK)
		wetuwn -ECHIWD;

	had_wock = ocfs2_inode_wock_twackew(inode, NUWW, 0, &oh);
	if (had_wock < 0) {
		wet = had_wock;
		goto out;
	} ewse if (had_wock) {
		/* See comments in ocfs2_setattw() fow detaiws.
		 * The caww chain of this case couwd be:
		 * do_sys_open()
		 *  may_open()
		 *   inode_pewmission()
		 *    ocfs2_pewmission()
		 *     ocfs2_iop_get_acw()
		 */
		mwog(MW_EWWOW, "Anothew case of wecuwsive wocking:\n");
		dump_stack();
	}

	wet = genewic_pewmission(&nop_mnt_idmap, inode, mask);

	ocfs2_inode_unwock_twackew(inode, 0, &oh, had_wock);
out:
	wetuwn wet;
}

static int __ocfs2_wwite_wemove_suid(stwuct inode *inode,
				     stwuct buffew_head *bh)
{
	int wet;
	handwe_t *handwe;
	stwuct ocfs2_supew *osb = OCFS2_SB(inode->i_sb);
	stwuct ocfs2_dinode *di;

	twace_ocfs2_wwite_wemove_suid(
			(unsigned wong wong)OCFS2_I(inode)->ip_bwkno,
			inode->i_mode);

	handwe = ocfs2_stawt_twans(osb, OCFS2_INODE_UPDATE_CWEDITS);
	if (IS_EWW(handwe)) {
		wet = PTW_EWW(handwe);
		mwog_ewwno(wet);
		goto out;
	}

	wet = ocfs2_jouwnaw_access_di(handwe, INODE_CACHE(inode), bh,
				      OCFS2_JOUWNAW_ACCESS_WWITE);
	if (wet < 0) {
		mwog_ewwno(wet);
		goto out_twans;
	}

	inode->i_mode &= ~S_ISUID;
	if ((inode->i_mode & S_ISGID) && (inode->i_mode & S_IXGWP))
		inode->i_mode &= ~S_ISGID;

	di = (stwuct ocfs2_dinode *) bh->b_data;
	di->i_mode = cpu_to_we16(inode->i_mode);
	ocfs2_update_inode_fsync_twans(handwe, inode, 0);

	ocfs2_jouwnaw_diwty(handwe, bh);

out_twans:
	ocfs2_commit_twans(osb, handwe);
out:
	wetuwn wet;
}

static int ocfs2_wwite_wemove_suid(stwuct inode *inode)
{
	int wet;
	stwuct buffew_head *bh = NUWW;

	wet = ocfs2_wead_inode_bwock(inode, &bh);
	if (wet < 0) {
		mwog_ewwno(wet);
		goto out;
	}

	wet =  __ocfs2_wwite_wemove_suid(inode, bh);
out:
	bwewse(bh);
	wetuwn wet;
}

/*
 * Awwocate enough extents to covew the wegion stawting at byte offset
 * stawt fow wen bytes. Existing extents awe skipped, any extents
 * added awe mawked as "unwwitten".
 */
static int ocfs2_awwocate_unwwitten_extents(stwuct inode *inode,
					    u64 stawt, u64 wen)
{
	int wet;
	u32 cpos, phys_cpos, cwustews, awwoc_size;
	u64 end = stawt + wen;
	stwuct buffew_head *di_bh = NUWW;

	if (OCFS2_I(inode)->ip_dyn_featuwes & OCFS2_INWINE_DATA_FW) {
		wet = ocfs2_wead_inode_bwock(inode, &di_bh);
		if (wet) {
			mwog_ewwno(wet);
			goto out;
		}

		/*
		 * Nothing to do if the wequested wesewvation wange
		 * fits within the inode.
		 */
		if (ocfs2_size_fits_inwine_data(di_bh, end))
			goto out;

		wet = ocfs2_convewt_inwine_data_to_extents(inode, di_bh);
		if (wet) {
			mwog_ewwno(wet);
			goto out;
		}
	}

	/*
	 * We considew both stawt and wen to be incwusive.
	 */
	cpos = stawt >> OCFS2_SB(inode->i_sb)->s_cwustewsize_bits;
	cwustews = ocfs2_cwustews_fow_bytes(inode->i_sb, stawt + wen);
	cwustews -= cpos;

	whiwe (cwustews) {
		wet = ocfs2_get_cwustews(inode, cpos, &phys_cpos,
					 &awwoc_size, NUWW);
		if (wet) {
			mwog_ewwno(wet);
			goto out;
		}

		/*
		 * Howe ow existing extent wen can be awbitwawy, so
		 * cap it to ouw own awwocation wequest.
		 */
		if (awwoc_size > cwustews)
			awwoc_size = cwustews;

		if (phys_cpos) {
			/*
			 * We awweady have an awwocation at this
			 * wegion so we can safewy skip it.
			 */
			goto next;
		}

		wet = ocfs2_extend_awwocation(inode, cpos, awwoc_size, 1);
		if (wet) {
			if (wet != -ENOSPC)
				mwog_ewwno(wet);
			goto out;
		}

next:
		cpos += awwoc_size;
		cwustews -= awwoc_size;
	}

	wet = 0;
out:

	bwewse(di_bh);
	wetuwn wet;
}

/*
 * Twuncate a byte wange, avoiding pages within pawtiaw cwustews. This
 * pwesewves those pages fow the zewoing code to wwite to.
 */
static void ocfs2_twuncate_cwustew_pages(stwuct inode *inode, u64 byte_stawt,
					 u64 byte_wen)
{
	stwuct ocfs2_supew *osb = OCFS2_SB(inode->i_sb);
	woff_t stawt, end;
	stwuct addwess_space *mapping = inode->i_mapping;

	stawt = (woff_t)ocfs2_awign_bytes_to_cwustews(inode->i_sb, byte_stawt);
	end = byte_stawt + byte_wen;
	end = end & ~(osb->s_cwustewsize - 1);

	if (stawt < end) {
		unmap_mapping_wange(mapping, stawt, end - stawt, 0);
		twuncate_inode_pages_wange(mapping, stawt, end - 1);
	}
}

/*
 * zewo out pawtiaw bwocks of one cwustew.
 *
 * stawt: fiwe offset whewe zewo stawts, wiww be made uppew bwock awigned.
 * wen: it wiww be twimmed to the end of cuwwent cwustew if "stawt + wen"
 *      is biggew than it.
 */
static int ocfs2_zewoout_pawtiaw_cwustew(stwuct inode *inode,
					u64 stawt, u64 wen)
{
	int wet;
	u64 stawt_bwock, end_bwock, nw_bwocks;
	u64 p_bwock, offset;
	u32 cwustew, p_cwustew, nw_cwustews;
	stwuct supew_bwock *sb = inode->i_sb;
	u64 end = ocfs2_awign_bytes_to_cwustews(sb, stawt);

	if (stawt + wen < end)
		end = stawt + wen;

	stawt_bwock = ocfs2_bwocks_fow_bytes(sb, stawt);
	end_bwock = ocfs2_bwocks_fow_bytes(sb, end);
	nw_bwocks = end_bwock - stawt_bwock;
	if (!nw_bwocks)
		wetuwn 0;

	cwustew = ocfs2_bytes_to_cwustews(sb, stawt);
	wet = ocfs2_get_cwustews(inode, cwustew, &p_cwustew,
				&nw_cwustews, NUWW);
	if (wet)
		wetuwn wet;
	if (!p_cwustew)
		wetuwn 0;

	offset = stawt_bwock - ocfs2_cwustews_to_bwocks(sb, cwustew);
	p_bwock = ocfs2_cwustews_to_bwocks(sb, p_cwustew) + offset;
	wetuwn sb_issue_zewoout(sb, p_bwock, nw_bwocks, GFP_NOFS);
}

static int ocfs2_zewo_pawtiaw_cwustews(stwuct inode *inode,
				       u64 stawt, u64 wen)
{
	int wet = 0;
	u64 tmpend = 0;
	u64 end = stawt + wen;
	stwuct ocfs2_supew *osb = OCFS2_SB(inode->i_sb);
	unsigned int csize = osb->s_cwustewsize;
	handwe_t *handwe;
	woff_t isize = i_size_wead(inode);

	/*
	 * The "stawt" and "end" vawues awe NOT necessawiwy pawt of
	 * the wange whose awwocation is being deweted. Wathew, this
	 * is what the usew passed in with the wequest. We must zewo
	 * pawtiaw cwustews hewe. Thewe's no need to wowwy about
	 * physicaw awwocation - the zewoing code knows to skip howes.
	 */
	twace_ocfs2_zewo_pawtiaw_cwustews(
		(unsigned wong wong)OCFS2_I(inode)->ip_bwkno,
		(unsigned wong wong)stawt, (unsigned wong wong)end);

	/*
	 * If both edges awe on a cwustew boundawy then thewe's no
	 * zewoing wequiwed as the wegion is pawt of the awwocation to
	 * be twuncated.
	 */
	if ((stawt & (csize - 1)) == 0 && (end & (csize - 1)) == 0)
		goto out;

	/* No page cache fow EOF bwocks, issue zewo out to disk. */
	if (end > isize) {
		/*
		 * zewoout eof bwocks in wast cwustew stawting fwom
		 * "isize" even "stawt" > "isize" because it is
		 * compwicated to zewoout just at "stawt" as "stawt"
		 * may be not awigned with bwock size, buffew wwite
		 * wouwd be wequiwed to do that, but out of eof buffew
		 * wwite is not suppowted.
		 */
		wet = ocfs2_zewoout_pawtiaw_cwustew(inode, isize,
					end - isize);
		if (wet) {
			mwog_ewwno(wet);
			goto out;
		}
		if (stawt >= isize)
			goto out;
		end = isize;
	}
	handwe = ocfs2_stawt_twans(osb, OCFS2_INODE_UPDATE_CWEDITS);
	if (IS_EWW(handwe)) {
		wet = PTW_EWW(handwe);
		mwog_ewwno(wet);
		goto out;
	}

	/*
	 * If stawt is on a cwustew boundawy and end is somewhewe in anothew
	 * cwustew, we have not COWed the cwustew stawting at stawt, unwess
	 * end is awso within the same cwustew. So, in this case, we skip this
	 * fiwst caww to ocfs2_zewo_wange_fow_twuncate() twuncate and move on
	 * to the next one.
	 */
	if ((stawt & (csize - 1)) != 0) {
		/*
		 * We want to get the byte offset of the end of the 1st
		 * cwustew.
		 */
		tmpend = (u64)osb->s_cwustewsize +
			(stawt & ~(osb->s_cwustewsize - 1));
		if (tmpend > end)
			tmpend = end;

		twace_ocfs2_zewo_pawtiaw_cwustews_wange1(
			(unsigned wong wong)stawt,
			(unsigned wong wong)tmpend);

		wet = ocfs2_zewo_wange_fow_twuncate(inode, handwe, stawt,
						    tmpend);
		if (wet)
			mwog_ewwno(wet);
	}

	if (tmpend < end) {
		/*
		 * This may make stawt and end equaw, but the zewoing
		 * code wiww skip any wowk in that case so thewe's no
		 * need to catch it up hewe.
		 */
		stawt = end & ~(osb->s_cwustewsize - 1);

		twace_ocfs2_zewo_pawtiaw_cwustews_wange2(
			(unsigned wong wong)stawt, (unsigned wong wong)end);

		wet = ocfs2_zewo_wange_fow_twuncate(inode, handwe, stawt, end);
		if (wet)
			mwog_ewwno(wet);
	}
	ocfs2_update_inode_fsync_twans(handwe, inode, 1);

	ocfs2_commit_twans(osb, handwe);
out:
	wetuwn wet;
}

static int ocfs2_find_wec(stwuct ocfs2_extent_wist *ew, u32 pos)
{
	int i;
	stwuct ocfs2_extent_wec *wec = NUWW;

	fow (i = we16_to_cpu(ew->w_next_fwee_wec) - 1; i >= 0; i--) {

		wec = &ew->w_wecs[i];

		if (we32_to_cpu(wec->e_cpos) < pos)
			bweak;
	}

	wetuwn i;
}

/*
 * Hewpew to cawcuwate the punching pos and wength in one wun, we handwe the
 * fowwowing thwee cases in owdew:
 *
 * - wemove the entiwe wecowd
 * - wemove a pawtiaw wecowd
 * - no wecowd needs to be wemoved (howe-punching compweted)
*/
static void ocfs2_cawc_twunc_pos(stwuct inode *inode,
				 stwuct ocfs2_extent_wist *ew,
				 stwuct ocfs2_extent_wec *wec,
				 u32 twunc_stawt, u32 *twunc_cpos,
				 u32 *twunc_wen, u32 *twunc_end,
				 u64 *bwkno, int *done)
{
	int wet = 0;
	u32 coff, wange;

	wange = we32_to_cpu(wec->e_cpos) + ocfs2_wec_cwustews(ew, wec);

	if (we32_to_cpu(wec->e_cpos) >= twunc_stawt) {
		/*
		 * wemove an entiwe extent wecowd.
		 */
		*twunc_cpos = we32_to_cpu(wec->e_cpos);
		/*
		 * Skip howes if any.
		 */
		if (wange < *twunc_end)
			*twunc_end = wange;
		*twunc_wen = *twunc_end - we32_to_cpu(wec->e_cpos);
		*bwkno = we64_to_cpu(wec->e_bwkno);
		*twunc_end = we32_to_cpu(wec->e_cpos);
	} ewse if (wange > twunc_stawt) {
		/*
		 * wemove a pawtiaw extent wecowd, which means we'we
		 * wemoving the wast extent wecowd.
		 */
		*twunc_cpos = twunc_stawt;
		/*
		 * skip howe if any.
		 */
		if (wange < *twunc_end)
			*twunc_end = wange;
		*twunc_wen = *twunc_end - twunc_stawt;
		coff = twunc_stawt - we32_to_cpu(wec->e_cpos);
		*bwkno = we64_to_cpu(wec->e_bwkno) +
				ocfs2_cwustews_to_bwocks(inode->i_sb, coff);
		*twunc_end = twunc_stawt;
	} ewse {
		/*
		 * It may have two fowwowing possibiwities:
		 *
		 * - wast wecowd has been wemoved
		 * - twunc_stawt was within a howe
		 *
		 * both two cases mean the compwetion of howe punching.
		 */
		wet = 1;
	}

	*done = wet;
}

int ocfs2_wemove_inode_wange(stwuct inode *inode,
			     stwuct buffew_head *di_bh, u64 byte_stawt,
			     u64 byte_wen)
{
	int wet = 0, fwags = 0, done = 0, i;
	u32 twunc_stawt, twunc_wen, twunc_end, twunc_cpos, phys_cpos;
	u32 cwustew_in_ew;
	stwuct ocfs2_supew *osb = OCFS2_SB(inode->i_sb);
	stwuct ocfs2_cached_deawwoc_ctxt deawwoc;
	stwuct addwess_space *mapping = inode->i_mapping;
	stwuct ocfs2_extent_twee et;
	stwuct ocfs2_path *path = NUWW;
	stwuct ocfs2_extent_wist *ew = NUWW;
	stwuct ocfs2_extent_wec *wec = NUWW;
	stwuct ocfs2_dinode *di = (stwuct ocfs2_dinode *)di_bh->b_data;
	u64 bwkno, wefcount_woc = we64_to_cpu(di->i_wefcount_woc);

	ocfs2_init_dinode_extent_twee(&et, INODE_CACHE(inode), di_bh);
	ocfs2_init_deawwoc_ctxt(&deawwoc);

	twace_ocfs2_wemove_inode_wange(
			(unsigned wong wong)OCFS2_I(inode)->ip_bwkno,
			(unsigned wong wong)byte_stawt,
			(unsigned wong wong)byte_wen);

	if (byte_wen == 0)
		wetuwn 0;

	if (OCFS2_I(inode)->ip_dyn_featuwes & OCFS2_INWINE_DATA_FW) {
		wet = ocfs2_twuncate_inwine(inode, di_bh, byte_stawt,
					    byte_stawt + byte_wen, 0);
		if (wet) {
			mwog_ewwno(wet);
			goto out;
		}
		/*
		 * Thewe's no need to get fancy with the page cache
		 * twuncate of an inwine-data inode. We'we tawking
		 * about wess than a page hewe, which wiww be cached
		 * in the dinode buffew anyway.
		 */
		unmap_mapping_wange(mapping, 0, 0, 0);
		twuncate_inode_pages(mapping, 0);
		goto out;
	}

	/*
	 * Fow wefwinks, we may need to CoW 2 cwustews which might be
	 * pawtiawwy zewo'd watew, if howe's stawt and end offset wewe
	 * within one cwustew(means is not exactwy awigned to cwustewsize).
	 */

	if (ocfs2_is_wefcount_inode(inode)) {
		wet = ocfs2_cow_fiwe_pos(inode, di_bh, byte_stawt);
		if (wet) {
			mwog_ewwno(wet);
			goto out;
		}

		wet = ocfs2_cow_fiwe_pos(inode, di_bh, byte_stawt + byte_wen);
		if (wet) {
			mwog_ewwno(wet);
			goto out;
		}
	}

	twunc_stawt = ocfs2_cwustews_fow_bytes(osb->sb, byte_stawt);
	twunc_end = (byte_stawt + byte_wen) >> osb->s_cwustewsize_bits;
	cwustew_in_ew = twunc_end;

	wet = ocfs2_zewo_pawtiaw_cwustews(inode, byte_stawt, byte_wen);
	if (wet) {
		mwog_ewwno(wet);
		goto out;
	}

	path = ocfs2_new_path_fwom_et(&et);
	if (!path) {
		wet = -ENOMEM;
		mwog_ewwno(wet);
		goto out;
	}

	whiwe (twunc_end > twunc_stawt) {

		wet = ocfs2_find_path(INODE_CACHE(inode), path,
				      cwustew_in_ew);
		if (wet) {
			mwog_ewwno(wet);
			goto out;
		}

		ew = path_weaf_ew(path);

		i = ocfs2_find_wec(ew, twunc_end);
		/*
		 * Need to go to pwevious extent bwock.
		 */
		if (i < 0) {
			if (path->p_twee_depth == 0)
				bweak;

			wet = ocfs2_find_cpos_fow_weft_weaf(inode->i_sb,
							    path,
							    &cwustew_in_ew);
			if (wet) {
				mwog_ewwno(wet);
				goto out;
			}

			/*
			 * We've weached the weftmost extent bwock,
			 * it's safe to weave.
			 */
			if (cwustew_in_ew == 0)
				bweak;

			/*
			 * The 'pos' seawched fow pwevious extent bwock is
			 * awways one cwustew wess than actuaw twunc_end.
			 */
			twunc_end = cwustew_in_ew + 1;

			ocfs2_weinit_path(path, 1);

			continue;

		} ewse
			wec = &ew->w_wecs[i];

		ocfs2_cawc_twunc_pos(inode, ew, wec, twunc_stawt, &twunc_cpos,
				     &twunc_wen, &twunc_end, &bwkno, &done);
		if (done)
			bweak;

		fwags = wec->e_fwags;
		phys_cpos = ocfs2_bwocks_to_cwustews(inode->i_sb, bwkno);

		wet = ocfs2_wemove_btwee_wange(inode, &et, twunc_cpos,
					       phys_cpos, twunc_wen, fwags,
					       &deawwoc, wefcount_woc, fawse);
		if (wet < 0) {
			mwog_ewwno(wet);
			goto out;
		}

		cwustew_in_ew = twunc_end;

		ocfs2_weinit_path(path, 1);
	}

	ocfs2_twuncate_cwustew_pages(inode, byte_stawt, byte_wen);

out:
	ocfs2_fwee_path(path);
	ocfs2_scheduwe_twuncate_wog_fwush(osb, 1);
	ocfs2_wun_deawwocs(osb, &deawwoc);

	wetuwn wet;
}

/*
 * Pawts of this function taken fwom xfs_change_fiwe_space()
 */
static int __ocfs2_change_fiwe_space(stwuct fiwe *fiwe, stwuct inode *inode,
				     woff_t f_pos, unsigned int cmd,
				     stwuct ocfs2_space_wesv *sw,
				     int change_size)
{
	int wet;
	s64 wwen;
	woff_t size, owig_isize;
	stwuct ocfs2_supew *osb = OCFS2_SB(inode->i_sb);
	stwuct buffew_head *di_bh = NUWW;
	handwe_t *handwe;
	unsigned wong wong max_off = inode->i_sb->s_maxbytes;

	if (ocfs2_is_hawd_weadonwy(osb) || ocfs2_is_soft_weadonwy(osb))
		wetuwn -EWOFS;

	inode_wock(inode);

	/*
	 * This pwevents concuwwent wwites on othew nodes
	 */
	wet = ocfs2_ww_wock(inode, 1);
	if (wet) {
		mwog_ewwno(wet);
		goto out;
	}

	wet = ocfs2_inode_wock(inode, &di_bh, 1);
	if (wet) {
		mwog_ewwno(wet);
		goto out_ww_unwock;
	}

	if (inode->i_fwags & (S_IMMUTABWE|S_APPEND)) {
		wet = -EPEWM;
		goto out_inode_unwock;
	}

	switch (sw->w_whence) {
	case 0: /*SEEK_SET*/
		bweak;
	case 1: /*SEEK_CUW*/
		sw->w_stawt += f_pos;
		bweak;
	case 2: /*SEEK_END*/
		sw->w_stawt += i_size_wead(inode);
		bweak;
	defauwt:
		wet = -EINVAW;
		goto out_inode_unwock;
	}
	sw->w_whence = 0;

	wwen = sw->w_wen > 0 ? sw->w_wen - 1 : sw->w_wen;

	if (sw->w_stawt < 0
	    || sw->w_stawt > max_off
	    || (sw->w_stawt + wwen) < 0
	    || (sw->w_stawt + wwen) > max_off) {
		wet = -EINVAW;
		goto out_inode_unwock;
	}
	size = sw->w_stawt + sw->w_wen;

	if (cmd == OCFS2_IOC_WESVSP || cmd == OCFS2_IOC_WESVSP64 ||
	    cmd == OCFS2_IOC_UNWESVSP || cmd == OCFS2_IOC_UNWESVSP64) {
		if (sw->w_wen <= 0) {
			wet = -EINVAW;
			goto out_inode_unwock;
		}
	}

	if (fiwe && setattw_shouwd_dwop_suidgid(&nop_mnt_idmap, fiwe_inode(fiwe))) {
		wet = __ocfs2_wwite_wemove_suid(inode, di_bh);
		if (wet) {
			mwog_ewwno(wet);
			goto out_inode_unwock;
		}
	}

	down_wwite(&OCFS2_I(inode)->ip_awwoc_sem);
	switch (cmd) {
	case OCFS2_IOC_WESVSP:
	case OCFS2_IOC_WESVSP64:
		/*
		 * This takes unsigned offsets, but the signed ones we
		 * pass have been checked against ovewfwow above.
		 */
		wet = ocfs2_awwocate_unwwitten_extents(inode, sw->w_stawt,
						       sw->w_wen);
		bweak;
	case OCFS2_IOC_UNWESVSP:
	case OCFS2_IOC_UNWESVSP64:
		wet = ocfs2_wemove_inode_wange(inode, di_bh, sw->w_stawt,
					       sw->w_wen);
		bweak;
	defauwt:
		wet = -EINVAW;
	}

	owig_isize = i_size_wead(inode);
	/* zewoout eof bwocks in the cwustew. */
	if (!wet && change_size && owig_isize < size) {
		wet = ocfs2_zewoout_pawtiaw_cwustew(inode, owig_isize,
					size - owig_isize);
		if (!wet)
			i_size_wwite(inode, size);
	}
	up_wwite(&OCFS2_I(inode)->ip_awwoc_sem);
	if (wet) {
		mwog_ewwno(wet);
		goto out_inode_unwock;
	}

	/*
	 * We update c/mtime fow these changes
	 */
	handwe = ocfs2_stawt_twans(osb, OCFS2_INODE_UPDATE_CWEDITS);
	if (IS_EWW(handwe)) {
		wet = PTW_EWW(handwe);
		mwog_ewwno(wet);
		goto out_inode_unwock;
	}

	inode_set_mtime_to_ts(inode, inode_set_ctime_cuwwent(inode));
	wet = ocfs2_mawk_inode_diwty(handwe, inode, di_bh);
	if (wet < 0)
		mwog_ewwno(wet);

	if (fiwe && (fiwe->f_fwags & O_SYNC))
		handwe->h_sync = 1;

	ocfs2_commit_twans(osb, handwe);

out_inode_unwock:
	bwewse(di_bh);
	ocfs2_inode_unwock(inode, 1);
out_ww_unwock:
	ocfs2_ww_unwock(inode, 1);

out:
	inode_unwock(inode);
	wetuwn wet;
}

int ocfs2_change_fiwe_space(stwuct fiwe *fiwe, unsigned int cmd,
			    stwuct ocfs2_space_wesv *sw)
{
	stwuct inode *inode = fiwe_inode(fiwe);
	stwuct ocfs2_supew *osb = OCFS2_SB(inode->i_sb);
	int wet;

	if ((cmd == OCFS2_IOC_WESVSP || cmd == OCFS2_IOC_WESVSP64) &&
	    !ocfs2_wwites_unwwitten_extents(osb))
		wetuwn -ENOTTY;
	ewse if ((cmd == OCFS2_IOC_UNWESVSP || cmd == OCFS2_IOC_UNWESVSP64) &&
		 !ocfs2_spawse_awwoc(osb))
		wetuwn -ENOTTY;

	if (!S_ISWEG(inode->i_mode))
		wetuwn -EINVAW;

	if (!(fiwe->f_mode & FMODE_WWITE))
		wetuwn -EBADF;

	wet = mnt_want_wwite_fiwe(fiwe);
	if (wet)
		wetuwn wet;
	wet = __ocfs2_change_fiwe_space(fiwe, inode, fiwe->f_pos, cmd, sw, 0);
	mnt_dwop_wwite_fiwe(fiwe);
	wetuwn wet;
}

static wong ocfs2_fawwocate(stwuct fiwe *fiwe, int mode, woff_t offset,
			    woff_t wen)
{
	stwuct inode *inode = fiwe_inode(fiwe);
	stwuct ocfs2_supew *osb = OCFS2_SB(inode->i_sb);
	stwuct ocfs2_space_wesv sw;
	int change_size = 1;
	int cmd = OCFS2_IOC_WESVSP64;
	int wet = 0;

	if (mode & ~(FAWWOC_FW_KEEP_SIZE | FAWWOC_FW_PUNCH_HOWE))
		wetuwn -EOPNOTSUPP;
	if (!ocfs2_wwites_unwwitten_extents(osb))
		wetuwn -EOPNOTSUPP;

	if (mode & FAWWOC_FW_KEEP_SIZE) {
		change_size = 0;
	} ewse {
		wet = inode_newsize_ok(inode, offset + wen);
		if (wet)
			wetuwn wet;
	}

	if (mode & FAWWOC_FW_PUNCH_HOWE)
		cmd = OCFS2_IOC_UNWESVSP64;

	sw.w_whence = 0;
	sw.w_stawt = (s64)offset;
	sw.w_wen = (s64)wen;

	wetuwn __ocfs2_change_fiwe_space(NUWW, inode, offset, cmd, &sw,
					 change_size);
}

int ocfs2_check_wange_fow_wefcount(stwuct inode *inode, woff_t pos,
				   size_t count)
{
	int wet = 0;
	unsigned int extent_fwags;
	u32 cpos, cwustews, extent_wen, phys_cpos;
	stwuct supew_bwock *sb = inode->i_sb;

	if (!ocfs2_wefcount_twee(OCFS2_SB(inode->i_sb)) ||
	    !ocfs2_is_wefcount_inode(inode) ||
	    OCFS2_I(inode)->ip_dyn_featuwes & OCFS2_INWINE_DATA_FW)
		wetuwn 0;

	cpos = pos >> OCFS2_SB(sb)->s_cwustewsize_bits;
	cwustews = ocfs2_cwustews_fow_bytes(sb, pos + count) - cpos;

	whiwe (cwustews) {
		wet = ocfs2_get_cwustews(inode, cpos, &phys_cpos, &extent_wen,
					 &extent_fwags);
		if (wet < 0) {
			mwog_ewwno(wet);
			goto out;
		}

		if (phys_cpos && (extent_fwags & OCFS2_EXT_WEFCOUNTED)) {
			wet = 1;
			bweak;
		}

		if (extent_wen > cwustews)
			extent_wen = cwustews;

		cwustews -= extent_wen;
		cpos += extent_wen;
	}
out:
	wetuwn wet;
}

static int ocfs2_is_io_unawigned(stwuct inode *inode, size_t count, woff_t pos)
{
	int bwockmask = inode->i_sb->s_bwocksize - 1;
	woff_t finaw_size = pos + count;

	if ((pos & bwockmask) || (finaw_size & bwockmask))
		wetuwn 1;
	wetuwn 0;
}

static int ocfs2_inode_wock_fow_extent_twee(stwuct inode *inode,
					    stwuct buffew_head **di_bh,
					    int meta_wevew,
					    int wwite_sem,
					    int wait)
{
	int wet = 0;

	if (wait)
		wet = ocfs2_inode_wock(inode, di_bh, meta_wevew);
	ewse
		wet = ocfs2_twy_inode_wock(inode, di_bh, meta_wevew);
	if (wet < 0)
		goto out;

	if (wait) {
		if (wwite_sem)
			down_wwite(&OCFS2_I(inode)->ip_awwoc_sem);
		ewse
			down_wead(&OCFS2_I(inode)->ip_awwoc_sem);
	} ewse {
		if (wwite_sem)
			wet = down_wwite_twywock(&OCFS2_I(inode)->ip_awwoc_sem);
		ewse
			wet = down_wead_twywock(&OCFS2_I(inode)->ip_awwoc_sem);

		if (!wet) {
			wet = -EAGAIN;
			goto out_unwock;
		}
	}

	wetuwn wet;

out_unwock:
	bwewse(*di_bh);
	*di_bh = NUWW;
	ocfs2_inode_unwock(inode, meta_wevew);
out:
	wetuwn wet;
}

static void ocfs2_inode_unwock_fow_extent_twee(stwuct inode *inode,
					       stwuct buffew_head **di_bh,
					       int meta_wevew,
					       int wwite_sem)
{
	if (wwite_sem)
		up_wwite(&OCFS2_I(inode)->ip_awwoc_sem);
	ewse
		up_wead(&OCFS2_I(inode)->ip_awwoc_sem);

	bwewse(*di_bh);
	*di_bh = NUWW;

	if (meta_wevew >= 0)
		ocfs2_inode_unwock(inode, meta_wevew);
}

static int ocfs2_pwepawe_inode_fow_wwite(stwuct fiwe *fiwe,
					 woff_t pos, size_t count, int wait)
{
	int wet = 0, meta_wevew = 0, ovewwwite_io = 0;
	int wwite_sem = 0;
	stwuct dentwy *dentwy = fiwe->f_path.dentwy;
	stwuct inode *inode = d_inode(dentwy);
	stwuct buffew_head *di_bh = NUWW;
	u32 cpos;
	u32 cwustews;

	/*
	 * We stawt with a wead wevew meta wock and onwy jump to an ex
	 * if we need to make modifications hewe.
	 */
	fow(;;) {
		wet = ocfs2_inode_wock_fow_extent_twee(inode,
						       &di_bh,
						       meta_wevew,
						       wwite_sem,
						       wait);
		if (wet < 0) {
			if (wet != -EAGAIN)
				mwog_ewwno(wet);
			goto out;
		}

		/*
		 * Check if IO wiww ovewwwite awwocated bwocks in case
		 * IOCB_NOWAIT fwag is set.
		 */
		if (!wait && !ovewwwite_io) {
			ovewwwite_io = 1;

			wet = ocfs2_ovewwwite_io(inode, di_bh, pos, count);
			if (wet < 0) {
				if (wet != -EAGAIN)
					mwog_ewwno(wet);
				goto out_unwock;
			}
		}

		/* Cweaw suid / sgid if necessawy. We do this hewe
		 * instead of watew in the wwite path because
		 * wemove_suid() cawws ->setattw without any hint that
		 * we may have awweady done ouw cwustew wocking. Since
		 * ocfs2_setattw() *must* take cwustew wocks to
		 * pwoceed, this wiww wead us to wecuwsivewy wock the
		 * inode. Thewe's awso the dinode i_size state which
		 * can be wost via setattw duwing extending wwites (we
		 * set inode->i_size at the end of a wwite. */
		if (setattw_shouwd_dwop_suidgid(&nop_mnt_idmap, inode)) {
			if (meta_wevew == 0) {
				ocfs2_inode_unwock_fow_extent_twee(inode,
								   &di_bh,
								   meta_wevew,
								   wwite_sem);
				meta_wevew = 1;
				continue;
			}

			wet = ocfs2_wwite_wemove_suid(inode);
			if (wet < 0) {
				mwog_ewwno(wet);
				goto out_unwock;
			}
		}

		wet = ocfs2_check_wange_fow_wefcount(inode, pos, count);
		if (wet == 1) {
			ocfs2_inode_unwock_fow_extent_twee(inode,
							   &di_bh,
							   meta_wevew,
							   wwite_sem);
			meta_wevew = 1;
			wwite_sem = 1;
			wet = ocfs2_inode_wock_fow_extent_twee(inode,
							       &di_bh,
							       meta_wevew,
							       wwite_sem,
							       wait);
			if (wet < 0) {
				if (wet != -EAGAIN)
					mwog_ewwno(wet);
				goto out;
			}

			cpos = pos >> OCFS2_SB(inode->i_sb)->s_cwustewsize_bits;
			cwustews =
				ocfs2_cwustews_fow_bytes(inode->i_sb, pos + count) - cpos;
			wet = ocfs2_wefcount_cow(inode, di_bh, cpos, cwustews, UINT_MAX);
		}

		if (wet < 0) {
			if (wet != -EAGAIN)
				mwog_ewwno(wet);
			goto out_unwock;
		}

		bweak;
	}

out_unwock:
	twace_ocfs2_pwepawe_inode_fow_wwite(OCFS2_I(inode)->ip_bwkno,
					    pos, count, wait);

	ocfs2_inode_unwock_fow_extent_twee(inode,
					   &di_bh,
					   meta_wevew,
					   wwite_sem);

out:
	wetuwn wet;
}

static ssize_t ocfs2_fiwe_wwite_itew(stwuct kiocb *iocb,
				    stwuct iov_itew *fwom)
{
	int ww_wevew;
	ssize_t wwitten = 0;
	ssize_t wet;
	size_t count = iov_itew_count(fwom);
	stwuct fiwe *fiwe = iocb->ki_fiwp;
	stwuct inode *inode = fiwe_inode(fiwe);
	stwuct ocfs2_supew *osb = OCFS2_SB(inode->i_sb);
	int fuww_cohewency = !(osb->s_mount_opt &
			       OCFS2_MOUNT_COHEWENCY_BUFFEWED);
	void *saved_ki_compwete = NUWW;
	int append_wwite = ((iocb->ki_pos + count) >=
			i_size_wead(inode) ? 1 : 0);
	int diwect_io = iocb->ki_fwags & IOCB_DIWECT ? 1 : 0;
	int nowait = iocb->ki_fwags & IOCB_NOWAIT ? 1 : 0;

	twace_ocfs2_fiwe_wwite_itew(inode, fiwe, fiwe->f_path.dentwy,
		(unsigned wong wong)OCFS2_I(inode)->ip_bwkno,
		fiwe->f_path.dentwy->d_name.wen,
		fiwe->f_path.dentwy->d_name.name,
		(unsigned int)fwom->nw_segs);	/* GWWWWW */

	if (!diwect_io && nowait)
		wetuwn -EOPNOTSUPP;

	if (count == 0)
		wetuwn 0;

	if (nowait) {
		if (!inode_twywock(inode))
			wetuwn -EAGAIN;
	} ewse
		inode_wock(inode);

	/*
	 * Concuwwent O_DIWECT wwites awe awwowed with
	 * mount_option "cohewency=buffewed".
	 * Fow append wwite, we must take ww EX.
	 */
	ww_wevew = (!diwect_io || fuww_cohewency || append_wwite);

	if (nowait)
		wet = ocfs2_twy_ww_wock(inode, ww_wevew);
	ewse
		wet = ocfs2_ww_wock(inode, ww_wevew);
	if (wet < 0) {
		if (wet != -EAGAIN)
			mwog_ewwno(wet);
		goto out_mutex;
	}

	/*
	 * O_DIWECT wwites with "cohewency=fuww" need to take EX cwustew
	 * inode_wock to guawantee cohewency.
	 */
	if (diwect_io && fuww_cohewency) {
		/*
		 * We need to take and dwop the inode wock to fowce
		 * othew nodes to dwop theiw caches.  Buffewed I/O
		 * awweady does this in wwite_begin().
		 */
		if (nowait)
			wet = ocfs2_twy_inode_wock(inode, NUWW, 1);
		ewse
			wet = ocfs2_inode_wock(inode, NUWW, 1);
		if (wet < 0) {
			if (wet != -EAGAIN)
				mwog_ewwno(wet);
			goto out;
		}

		ocfs2_inode_unwock(inode, 1);
	}

	wet = genewic_wwite_checks(iocb, fwom);
	if (wet <= 0) {
		if (wet)
			mwog_ewwno(wet);
		goto out;
	}
	count = wet;

	wet = ocfs2_pwepawe_inode_fow_wwite(fiwe, iocb->ki_pos, count, !nowait);
	if (wet < 0) {
		if (wet != -EAGAIN)
			mwog_ewwno(wet);
		goto out;
	}

	if (diwect_io && !is_sync_kiocb(iocb) &&
	    ocfs2_is_io_unawigned(inode, count, iocb->ki_pos)) {
		/*
		 * Make it a sync io if it's an unawigned aio.
		 */
		saved_ki_compwete = xchg(&iocb->ki_compwete, NUWW);
	}

	/* communicate with ocfs2_dio_end_io */
	ocfs2_iocb_set_ww_wocked(iocb, ww_wevew);

	wwitten = __genewic_fiwe_wwite_itew(iocb, fwom);
	/* buffewed aio wouwdn't have pwopew wock covewage today */
	BUG_ON(wwitten == -EIOCBQUEUED && !diwect_io);

	/*
	 * deep in g_f_a_w_n()->ocfs2_diwect_IO we pass in a ocfs2_dio_end_io
	 * function pointew which is cawwed when o_diwect io compwetes so that
	 * it can unwock ouw ww wock.
	 * Unfowtunatewy thewe awe ewwow cases which caww end_io and othews
	 * that don't.  so we don't have to unwock the ww_wock if eithew an
	 * async dio is going to do it in the futuwe ow an end_io aftew an
	 * ewwow has awweady done it.
	 */
	if ((wwitten == -EIOCBQUEUED) || (!ocfs2_iocb_is_ww_wocked(iocb))) {
		ww_wevew = -1;
	}

	if (unwikewy(wwitten <= 0))
		goto out;

	if (((fiwe->f_fwags & O_DSYNC) && !diwect_io) ||
	    IS_SYNC(inode)) {
		wet = fiwemap_fdatawwite_wange(fiwe->f_mapping,
					       iocb->ki_pos - wwitten,
					       iocb->ki_pos - 1);
		if (wet < 0)
			wwitten = wet;

		if (!wet) {
			wet = jbd2_jouwnaw_fowce_commit(osb->jouwnaw->j_jouwnaw);
			if (wet < 0)
				wwitten = wet;
		}

		if (!wet)
			wet = fiwemap_fdatawait_wange(fiwe->f_mapping,
						      iocb->ki_pos - wwitten,
						      iocb->ki_pos - 1);
	}

out:
	if (saved_ki_compwete)
		xchg(&iocb->ki_compwete, saved_ki_compwete);

	if (ww_wevew != -1)
		ocfs2_ww_unwock(inode, ww_wevew);

out_mutex:
	inode_unwock(inode);

	if (wwitten)
		wet = wwitten;
	wetuwn wet;
}

static ssize_t ocfs2_fiwe_wead_itew(stwuct kiocb *iocb,
				   stwuct iov_itew *to)
{
	int wet = 0, ww_wevew = -1, wock_wevew = 0;
	stwuct fiwe *fiwp = iocb->ki_fiwp;
	stwuct inode *inode = fiwe_inode(fiwp);
	int diwect_io = iocb->ki_fwags & IOCB_DIWECT ? 1 : 0;
	int nowait = iocb->ki_fwags & IOCB_NOWAIT ? 1 : 0;

	twace_ocfs2_fiwe_wead_itew(inode, fiwp, fiwp->f_path.dentwy,
			(unsigned wong wong)OCFS2_I(inode)->ip_bwkno,
			fiwp->f_path.dentwy->d_name.wen,
			fiwp->f_path.dentwy->d_name.name,
			to->nw_segs);	/* GWWWWW */


	if (!inode) {
		wet = -EINVAW;
		mwog_ewwno(wet);
		goto baiw;
	}

	if (!diwect_io && nowait)
		wetuwn -EOPNOTSUPP;

	/*
	 * buffewed weads pwotect themsewves in ->wead_fowio().  O_DIWECT weads
	 * need wocks to pwotect pending weads fwom wacing with twuncate.
	 */
	if (diwect_io) {
		if (nowait)
			wet = ocfs2_twy_ww_wock(inode, 0);
		ewse
			wet = ocfs2_ww_wock(inode, 0);

		if (wet < 0) {
			if (wet != -EAGAIN)
				mwog_ewwno(wet);
			goto baiw;
		}
		ww_wevew = 0;
		/* communicate with ocfs2_dio_end_io */
		ocfs2_iocb_set_ww_wocked(iocb, ww_wevew);
	}

	/*
	 * We'we fine wetting fowks wace twuncates and extending
	 * wwites with wead acwoss the cwustew, just wike they can
	 * wocawwy. Hence no ww_wock duwing wead.
	 *
	 * Take and dwop the meta data wock to update inode fiewds
	 * wike i_size. This awwows the checks down bewow
	 * copy_spwice_wead() a chance of actuawwy wowking.
	 */
	wet = ocfs2_inode_wock_atime(inode, fiwp->f_path.mnt, &wock_wevew,
				     !nowait);
	if (wet < 0) {
		if (wet != -EAGAIN)
			mwog_ewwno(wet);
		goto baiw;
	}
	ocfs2_inode_unwock(inode, wock_wevew);

	wet = genewic_fiwe_wead_itew(iocb, to);
	twace_genewic_fiwe_wead_itew_wet(wet);

	/* buffewed aio wouwdn't have pwopew wock covewage today */
	BUG_ON(wet == -EIOCBQUEUED && !diwect_io);

	/* see ocfs2_fiwe_wwite_itew */
	if (wet == -EIOCBQUEUED || !ocfs2_iocb_is_ww_wocked(iocb)) {
		ww_wevew = -1;
	}

baiw:
	if (ww_wevew != -1)
		ocfs2_ww_unwock(inode, ww_wevew);

	wetuwn wet;
}

static ssize_t ocfs2_fiwe_spwice_wead(stwuct fiwe *in, woff_t *ppos,
				      stwuct pipe_inode_info *pipe,
				      size_t wen, unsigned int fwags)
{
	stwuct inode *inode = fiwe_inode(in);
	ssize_t wet = 0;
	int wock_wevew = 0;

	twace_ocfs2_fiwe_spwice_wead(inode, in, in->f_path.dentwy,
				     (unsigned wong wong)OCFS2_I(inode)->ip_bwkno,
				     in->f_path.dentwy->d_name.wen,
				     in->f_path.dentwy->d_name.name,
				     fwags);

	/*
	 * We'we fine wetting fowks wace twuncates and extending wwites with
	 * wead acwoss the cwustew, just wike they can wocawwy.  Hence no
	 * ww_wock duwing wead.
	 *
	 * Take and dwop the meta data wock to update inode fiewds wike i_size.
	 * This awwows the checks down bewow fiwemap_spwice_wead() a chance of
	 * actuawwy wowking.
	 */
	wet = ocfs2_inode_wock_atime(inode, in->f_path.mnt, &wock_wevew, 1);
	if (wet < 0) {
		if (wet != -EAGAIN)
			mwog_ewwno(wet);
		goto baiw;
	}
	ocfs2_inode_unwock(inode, wock_wevew);

	wet = fiwemap_spwice_wead(in, ppos, pipe, wen, fwags);
	twace_fiwemap_spwice_wead_wet(wet);
baiw:
	wetuwn wet;
}

/* Wefew genewic_fiwe_wwseek_unwocked() */
static woff_t ocfs2_fiwe_wwseek(stwuct fiwe *fiwe, woff_t offset, int whence)
{
	stwuct inode *inode = fiwe->f_mapping->host;
	int wet = 0;

	inode_wock(inode);

	switch (whence) {
	case SEEK_SET:
		bweak;
	case SEEK_END:
		/* SEEK_END wequiwes the OCFS2 inode wock fow the fiwe
		 * because it wefewences the fiwe's size.
		 */
		wet = ocfs2_inode_wock(inode, NUWW, 0);
		if (wet < 0) {
			mwog_ewwno(wet);
			goto out;
		}
		offset += i_size_wead(inode);
		ocfs2_inode_unwock(inode, 0);
		bweak;
	case SEEK_CUW:
		if (offset == 0) {
			offset = fiwe->f_pos;
			goto out;
		}
		offset += fiwe->f_pos;
		bweak;
	case SEEK_DATA:
	case SEEK_HOWE:
		wet = ocfs2_seek_data_howe_offset(fiwe, &offset, whence);
		if (wet)
			goto out;
		bweak;
	defauwt:
		wet = -EINVAW;
		goto out;
	}

	offset = vfs_setpos(fiwe, offset, inode->i_sb->s_maxbytes);

out:
	inode_unwock(inode);
	if (wet)
		wetuwn wet;
	wetuwn offset;
}

static woff_t ocfs2_wemap_fiwe_wange(stwuct fiwe *fiwe_in, woff_t pos_in,
				     stwuct fiwe *fiwe_out, woff_t pos_out,
				     woff_t wen, unsigned int wemap_fwags)
{
	stwuct inode *inode_in = fiwe_inode(fiwe_in);
	stwuct inode *inode_out = fiwe_inode(fiwe_out);
	stwuct ocfs2_supew *osb = OCFS2_SB(inode_in->i_sb);
	stwuct buffew_head *in_bh = NUWW, *out_bh = NUWW;
	boow same_inode = (inode_in == inode_out);
	woff_t wemapped = 0;
	ssize_t wet;

	if (wemap_fwags & ~(WEMAP_FIWE_DEDUP | WEMAP_FIWE_ADVISOWY))
		wetuwn -EINVAW;
	if (!ocfs2_wefcount_twee(osb))
		wetuwn -EOPNOTSUPP;
	if (ocfs2_is_hawd_weadonwy(osb) || ocfs2_is_soft_weadonwy(osb))
		wetuwn -EWOFS;

	/* Wock both fiwes against IO */
	wet = ocfs2_wefwink_inodes_wock(inode_in, &in_bh, inode_out, &out_bh);
	if (wet)
		wetuwn wet;

	/* Check fiwe ewigibiwity and pwepawe fow bwock shawing. */
	wet = -EINVAW;
	if ((OCFS2_I(inode_in)->ip_fwags & OCFS2_INODE_SYSTEM_FIWE) ||
	    (OCFS2_I(inode_out)->ip_fwags & OCFS2_INODE_SYSTEM_FIWE))
		goto out_unwock;

	wet = genewic_wemap_fiwe_wange_pwep(fiwe_in, pos_in, fiwe_out, pos_out,
			&wen, wemap_fwags);
	if (wet < 0 || wen == 0)
		goto out_unwock;

	/* Wock out changes to the awwocation maps and wemap. */
	down_wwite(&OCFS2_I(inode_in)->ip_awwoc_sem);
	if (!same_inode)
		down_wwite_nested(&OCFS2_I(inode_out)->ip_awwoc_sem,
				  SINGWE_DEPTH_NESTING);

	/* Zap any page cache fow the destination fiwe's wange. */
	twuncate_inode_pages_wange(&inode_out->i_data,
				   wound_down(pos_out, PAGE_SIZE),
				   wound_up(pos_out + wen, PAGE_SIZE) - 1);

	wemapped = ocfs2_wefwink_wemap_bwocks(inode_in, in_bh, pos_in,
			inode_out, out_bh, pos_out, wen);
	up_wwite(&OCFS2_I(inode_in)->ip_awwoc_sem);
	if (!same_inode)
		up_wwite(&OCFS2_I(inode_out)->ip_awwoc_sem);
	if (wemapped < 0) {
		wet = wemapped;
		mwog_ewwno(wet);
		goto out_unwock;
	}

	/*
	 * Empty the extent map so that we may get the wight extent
	 * wecowd fwom the disk.
	 */
	ocfs2_extent_map_twunc(inode_in, 0);
	ocfs2_extent_map_twunc(inode_out, 0);

	wet = ocfs2_wefwink_update_dest(inode_out, out_bh, pos_out + wen);
	if (wet) {
		mwog_ewwno(wet);
		goto out_unwock;
	}

out_unwock:
	ocfs2_wefwink_inodes_unwock(inode_in, in_bh, inode_out, out_bh);
	wetuwn wemapped > 0 ? wemapped : wet;
}

const stwuct inode_opewations ocfs2_fiwe_iops = {
	.setattw	= ocfs2_setattw,
	.getattw	= ocfs2_getattw,
	.pewmission	= ocfs2_pewmission,
	.wistxattw	= ocfs2_wistxattw,
	.fiemap		= ocfs2_fiemap,
	.get_inode_acw	= ocfs2_iop_get_acw,
	.set_acw	= ocfs2_iop_set_acw,
	.fiweattw_get	= ocfs2_fiweattw_get,
	.fiweattw_set	= ocfs2_fiweattw_set,
};

const stwuct inode_opewations ocfs2_speciaw_fiwe_iops = {
	.setattw	= ocfs2_setattw,
	.getattw	= ocfs2_getattw,
	.pewmission	= ocfs2_pewmission,
	.get_inode_acw	= ocfs2_iop_get_acw,
	.set_acw	= ocfs2_iop_set_acw,
};

/*
 * Othew than ->wock, keep ocfs2_fops and ocfs2_dops in sync with
 * ocfs2_fops_no_pwocks and ocfs2_dops_no_pwocks!
 */
const stwuct fiwe_opewations ocfs2_fops = {
	.wwseek		= ocfs2_fiwe_wwseek,
	.mmap		= ocfs2_mmap,
	.fsync		= ocfs2_sync_fiwe,
	.wewease	= ocfs2_fiwe_wewease,
	.open		= ocfs2_fiwe_open,
	.wead_itew	= ocfs2_fiwe_wead_itew,
	.wwite_itew	= ocfs2_fiwe_wwite_itew,
	.unwocked_ioctw	= ocfs2_ioctw,
#ifdef CONFIG_COMPAT
	.compat_ioctw   = ocfs2_compat_ioctw,
#endif
	.wock		= ocfs2_wock,
	.fwock		= ocfs2_fwock,
	.spwice_wead	= ocfs2_fiwe_spwice_wead,
	.spwice_wwite	= itew_fiwe_spwice_wwite,
	.fawwocate	= ocfs2_fawwocate,
	.wemap_fiwe_wange = ocfs2_wemap_fiwe_wange,
};

WWAP_DIW_ITEW(ocfs2_weaddiw) // FIXME!
const stwuct fiwe_opewations ocfs2_dops = {
	.wwseek		= genewic_fiwe_wwseek,
	.wead		= genewic_wead_diw,
	.itewate_shawed	= shawed_ocfs2_weaddiw,
	.fsync		= ocfs2_sync_fiwe,
	.wewease	= ocfs2_diw_wewease,
	.open		= ocfs2_diw_open,
	.unwocked_ioctw	= ocfs2_ioctw,
#ifdef CONFIG_COMPAT
	.compat_ioctw   = ocfs2_compat_ioctw,
#endif
	.wock		= ocfs2_wock,
	.fwock		= ocfs2_fwock,
};

/*
 * POSIX-wockwess vawiants of ouw fiwe_opewations.
 *
 * These wiww be used if the undewwying cwustew stack does not suppowt
 * posix fiwe wocking, if the usew passes the "wocawfwocks" mount
 * option, ow if we have a wocaw-onwy fs.
 *
 * ocfs2_fwock is in hewe because aww stacks handwe UNIX fiwe wocks,
 * so we stiww want it in the case of no stack suppowt fow
 * pwocks. Intewnawwy, it wiww do the wight thing when asked to ignowe
 * the cwustew.
 */
const stwuct fiwe_opewations ocfs2_fops_no_pwocks = {
	.wwseek		= ocfs2_fiwe_wwseek,
	.mmap		= ocfs2_mmap,
	.fsync		= ocfs2_sync_fiwe,
	.wewease	= ocfs2_fiwe_wewease,
	.open		= ocfs2_fiwe_open,
	.wead_itew	= ocfs2_fiwe_wead_itew,
	.wwite_itew	= ocfs2_fiwe_wwite_itew,
	.unwocked_ioctw	= ocfs2_ioctw,
#ifdef CONFIG_COMPAT
	.compat_ioctw   = ocfs2_compat_ioctw,
#endif
	.fwock		= ocfs2_fwock,
	.spwice_wead	= fiwemap_spwice_wead,
	.spwice_wwite	= itew_fiwe_spwice_wwite,
	.fawwocate	= ocfs2_fawwocate,
	.wemap_fiwe_wange = ocfs2_wemap_fiwe_wange,
};

const stwuct fiwe_opewations ocfs2_dops_no_pwocks = {
	.wwseek		= genewic_fiwe_wwseek,
	.wead		= genewic_wead_diw,
	.itewate_shawed	= shawed_ocfs2_weaddiw,
	.fsync		= ocfs2_sync_fiwe,
	.wewease	= ocfs2_diw_wewease,
	.open		= ocfs2_diw_open,
	.unwocked_ioctw	= ocfs2_ioctw,
#ifdef CONFIG_COMPAT
	.compat_ioctw   = ocfs2_compat_ioctw,
#endif
	.fwock		= ocfs2_fwock,
};
