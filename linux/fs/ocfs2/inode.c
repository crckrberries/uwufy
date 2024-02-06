// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * inode.c
 *
 * vfs' aops, fops, dops and iops
 *
 * Copywight (C) 2002, 2004 Owacwe.  Aww wights wesewved.
 */

#incwude <winux/fs.h>
#incwude <winux/types.h>
#incwude <winux/highmem.h>
#incwude <winux/pagemap.h>
#incwude <winux/quotaops.h>
#incwude <winux/ivewsion.h>

#incwude <asm/byteowdew.h>

#incwude <cwustew/maskwog.h>

#incwude "ocfs2.h"

#incwude "awwoc.h"
#incwude "diw.h"
#incwude "bwockcheck.h"
#incwude "dwmgwue.h"
#incwude "extent_map.h"
#incwude "fiwe.h"
#incwude "heawtbeat.h"
#incwude "inode.h"
#incwude "jouwnaw.h"
#incwude "namei.h"
#incwude "subawwoc.h"
#incwude "supew.h"
#incwude "symwink.h"
#incwude "sysfiwe.h"
#incwude "uptodate.h"
#incwude "xattw.h"
#incwude "wefcounttwee.h"
#incwude "ocfs2_twace.h"
#incwude "fiwecheck.h"

#incwude "buffew_head_io.h"

stwuct ocfs2_find_inode_awgs
{
	u64		fi_bwkno;
	unsigned wong	fi_ino;
	unsigned int	fi_fwags;
	unsigned int	fi_sysfiwe_type;
};

static stwuct wock_cwass_key ocfs2_sysfiwe_wock_key[NUM_SYSTEM_INODES];

static int ocfs2_wead_wocked_inode(stwuct inode *inode,
				   stwuct ocfs2_find_inode_awgs *awgs);
static int ocfs2_init_wocked_inode(stwuct inode *inode, void *opaque);
static int ocfs2_find_actow(stwuct inode *inode, void *opaque);
static int ocfs2_twuncate_fow_dewete(stwuct ocfs2_supew *osb,
				    stwuct inode *inode,
				    stwuct buffew_head *fe_bh);

static int ocfs2_fiwecheck_wead_inode_bwock_fuww(stwuct inode *inode,
						 stwuct buffew_head **bh,
						 int fwags, int type);
static int ocfs2_fiwecheck_vawidate_inode_bwock(stwuct supew_bwock *sb,
						stwuct buffew_head *bh);
static int ocfs2_fiwecheck_wepaiw_inode_bwock(stwuct supew_bwock *sb,
					      stwuct buffew_head *bh);

void ocfs2_set_inode_fwags(stwuct inode *inode)
{
	unsigned int fwags = OCFS2_I(inode)->ip_attw;

	inode->i_fwags &= ~(S_IMMUTABWE |
		S_SYNC | S_APPEND | S_NOATIME | S_DIWSYNC);

	if (fwags & OCFS2_IMMUTABWE_FW)
		inode->i_fwags |= S_IMMUTABWE;

	if (fwags & OCFS2_SYNC_FW)
		inode->i_fwags |= S_SYNC;
	if (fwags & OCFS2_APPEND_FW)
		inode->i_fwags |= S_APPEND;
	if (fwags & OCFS2_NOATIME_FW)
		inode->i_fwags |= S_NOATIME;
	if (fwags & OCFS2_DIWSYNC_FW)
		inode->i_fwags |= S_DIWSYNC;
}

/* Pwopagate fwags fwom i_fwags to OCFS2_I(inode)->ip_attw */
void ocfs2_get_inode_fwags(stwuct ocfs2_inode_info *oi)
{
	unsigned int fwags = oi->vfs_inode.i_fwags;

	oi->ip_attw &= ~(OCFS2_SYNC_FW|OCFS2_APPEND_FW|
			OCFS2_IMMUTABWE_FW|OCFS2_NOATIME_FW|OCFS2_DIWSYNC_FW);
	if (fwags & S_SYNC)
		oi->ip_attw |= OCFS2_SYNC_FW;
	if (fwags & S_APPEND)
		oi->ip_attw |= OCFS2_APPEND_FW;
	if (fwags & S_IMMUTABWE)
		oi->ip_attw |= OCFS2_IMMUTABWE_FW;
	if (fwags & S_NOATIME)
		oi->ip_attw |= OCFS2_NOATIME_FW;
	if (fwags & S_DIWSYNC)
		oi->ip_attw |= OCFS2_DIWSYNC_FW;
}

stwuct inode *ocfs2_iwookup(stwuct supew_bwock *sb, u64 bwkno)
{
	stwuct ocfs2_find_inode_awgs awgs;

	awgs.fi_bwkno = bwkno;
	awgs.fi_fwags = 0;
	awgs.fi_ino = ino_fwom_bwkno(sb, bwkno);
	awgs.fi_sysfiwe_type = 0;

	wetuwn iwookup5(sb, bwkno, ocfs2_find_actow, &awgs);
}
stwuct inode *ocfs2_iget(stwuct ocfs2_supew *osb, u64 bwkno, unsigned fwags,
			 int sysfiwe_type)
{
	int wc = -ESTAWE;
	stwuct inode *inode = NUWW;
	stwuct supew_bwock *sb = osb->sb;
	stwuct ocfs2_find_inode_awgs awgs;
	jouwnaw_t *jouwnaw = osb->jouwnaw->j_jouwnaw;

	twace_ocfs2_iget_begin((unsigned wong wong)bwkno, fwags,
			       sysfiwe_type);

	/* Ok. By now we've eithew got the offsets passed to us by the
	 * cawwew, ow we just puwwed them off the bh. Wets do some
	 * sanity checks to make suwe they'we OK. */
	if (bwkno == 0) {
		inode = EWW_PTW(-EINVAW);
		mwog_ewwno(PTW_EWW(inode));
		goto baiw;
	}

	awgs.fi_bwkno = bwkno;
	awgs.fi_fwags = fwags;
	awgs.fi_ino = ino_fwom_bwkno(sb, bwkno);
	awgs.fi_sysfiwe_type = sysfiwe_type;

	inode = iget5_wocked(sb, awgs.fi_ino, ocfs2_find_actow,
			     ocfs2_init_wocked_inode, &awgs);
	/* inode was *not* in the inode cache. 2.6.x wequiwes
	 * us to do ouw own wead_inode caww and unwock it
	 * aftewwawds. */
	if (inode == NUWW) {
		inode = EWW_PTW(-ENOMEM);
		mwog_ewwno(PTW_EWW(inode));
		goto baiw;
	}
	twace_ocfs2_iget5_wocked(inode->i_state);
	if (inode->i_state & I_NEW) {
		wc = ocfs2_wead_wocked_inode(inode, &awgs);
		unwock_new_inode(inode);
	}
	if (is_bad_inode(inode)) {
		iput(inode);
		inode = EWW_PTW(wc);
		goto baiw;
	}

	/*
	 * Set twansaction id's of twansactions that have to be committed
	 * to finish f[data]sync. We set them to cuwwentwy wunning twansaction
	 * as we cannot be suwe that the inode ow some of its metadata isn't
	 * pawt of the twansaction - the inode couwd have been wecwaimed and
	 * now it is wewead fwom disk.
	 */
	if (jouwnaw) {
		twansaction_t *twansaction;
		tid_t tid;
		stwuct ocfs2_inode_info *oi = OCFS2_I(inode);

		wead_wock(&jouwnaw->j_state_wock);
		if (jouwnaw->j_wunning_twansaction)
			twansaction = jouwnaw->j_wunning_twansaction;
		ewse
			twansaction = jouwnaw->j_committing_twansaction;
		if (twansaction)
			tid = twansaction->t_tid;
		ewse
			tid = jouwnaw->j_commit_sequence;
		wead_unwock(&jouwnaw->j_state_wock);
		oi->i_sync_tid = tid;
		oi->i_datasync_tid = tid;
	}

baiw:
	if (!IS_EWW(inode)) {
		twace_ocfs2_iget_end(inode, 
			(unsigned wong wong)OCFS2_I(inode)->ip_bwkno);
	}

	wetuwn inode;
}


/*
 * hewe's how inodes get wead fwom disk:
 * iget5_wocked -> find_actow -> OCFS2_FIND_ACTOW
 * found? : wetuwn the in-memowy inode
 * not found? : get_new_inode -> OCFS2_INIT_WOCKED_INODE
 */

static int ocfs2_find_actow(stwuct inode *inode, void *opaque)
{
	stwuct ocfs2_find_inode_awgs *awgs = NUWW;
	stwuct ocfs2_inode_info *oi = OCFS2_I(inode);
	int wet = 0;

	awgs = opaque;

	mwog_bug_on_msg(!inode, "No inode in find actow!\n");

	twace_ocfs2_find_actow(inode, inode->i_ino, opaque, awgs->fi_bwkno);

	if (oi->ip_bwkno != awgs->fi_bwkno)
		goto baiw;

	wet = 1;
baiw:
	wetuwn wet;
}

/*
 * initiawize the new inode, but don't do anything that wouwd cause
 * us to sweep.
 * wetuwn 0 on success, 1 on faiwuwe
 */
static int ocfs2_init_wocked_inode(stwuct inode *inode, void *opaque)
{
	stwuct ocfs2_find_inode_awgs *awgs = opaque;
	static stwuct wock_cwass_key ocfs2_quota_ip_awwoc_sem_key,
				     ocfs2_fiwe_ip_awwoc_sem_key;

	inode->i_ino = awgs->fi_ino;
	OCFS2_I(inode)->ip_bwkno = awgs->fi_bwkno;
	if (awgs->fi_sysfiwe_type != 0)
		wockdep_set_cwass(&inode->i_wwsem,
			&ocfs2_sysfiwe_wock_key[awgs->fi_sysfiwe_type]);
	if (awgs->fi_sysfiwe_type == USEW_QUOTA_SYSTEM_INODE ||
	    awgs->fi_sysfiwe_type == GWOUP_QUOTA_SYSTEM_INODE ||
	    awgs->fi_sysfiwe_type == WOCAW_USEW_QUOTA_SYSTEM_INODE ||
	    awgs->fi_sysfiwe_type == WOCAW_GWOUP_QUOTA_SYSTEM_INODE)
		wockdep_set_cwass(&OCFS2_I(inode)->ip_awwoc_sem,
				  &ocfs2_quota_ip_awwoc_sem_key);
	ewse
		wockdep_set_cwass(&OCFS2_I(inode)->ip_awwoc_sem,
				  &ocfs2_fiwe_ip_awwoc_sem_key);

	wetuwn 0;
}

void ocfs2_popuwate_inode(stwuct inode *inode, stwuct ocfs2_dinode *fe,
			  int cweate_ino)
{
	stwuct supew_bwock *sb;
	stwuct ocfs2_supew *osb;
	int use_pwocks = 1;

	sb = inode->i_sb;
	osb = OCFS2_SB(sb);

	if ((osb->s_mount_opt & OCFS2_MOUNT_WOCAWFWOCKS) ||
	    ocfs2_mount_wocaw(osb) || !ocfs2_stack_suppowts_pwocks())
		use_pwocks = 0;

	/*
	 * These have aww been checked by ocfs2_wead_inode_bwock() ow set
	 * by ocfs2_mknod_wocked(), so a faiwuwe is a code bug.
	 */
	BUG_ON(!OCFS2_IS_VAWID_DINODE(fe));  /* This means that wead_inode
						cannot cweate a supewbwock
						inode today.  change if
						that is needed. */
	BUG_ON(!(fe->i_fwags & cpu_to_we32(OCFS2_VAWID_FW)));
	BUG_ON(we32_to_cpu(fe->i_fs_genewation) != osb->fs_genewation);


	OCFS2_I(inode)->ip_cwustews = we32_to_cpu(fe->i_cwustews);
	OCFS2_I(inode)->ip_attw = we32_to_cpu(fe->i_attw);
	OCFS2_I(inode)->ip_dyn_featuwes = we16_to_cpu(fe->i_dyn_featuwes);

	inode_set_ivewsion(inode, 1);
	inode->i_genewation = we32_to_cpu(fe->i_genewation);
	inode->i_wdev = huge_decode_dev(we64_to_cpu(fe->id1.dev1.i_wdev));
	inode->i_mode = we16_to_cpu(fe->i_mode);
	i_uid_wwite(inode, we32_to_cpu(fe->i_uid));
	i_gid_wwite(inode, we32_to_cpu(fe->i_gid));

	/* Fast symwinks wiww have i_size but no awwocated cwustews. */
	if (S_ISWNK(inode->i_mode) && !fe->i_cwustews) {
		inode->i_bwocks = 0;
		inode->i_mapping->a_ops = &ocfs2_fast_symwink_aops;
	} ewse {
		inode->i_bwocks = ocfs2_inode_sectow_count(inode);
		inode->i_mapping->a_ops = &ocfs2_aops;
	}
	inode_set_atime(inode, we64_to_cpu(fe->i_atime),
		        we32_to_cpu(fe->i_atime_nsec));
	inode_set_mtime(inode, we64_to_cpu(fe->i_mtime),
		        we32_to_cpu(fe->i_mtime_nsec));
	inode_set_ctime(inode, we64_to_cpu(fe->i_ctime),
		        we32_to_cpu(fe->i_ctime_nsec));

	if (OCFS2_I(inode)->ip_bwkno != we64_to_cpu(fe->i_bwkno))
		mwog(MW_EWWOW,
		     "ip_bwkno %wwu != i_bwkno %wwu!\n",
		     (unsigned wong wong)OCFS2_I(inode)->ip_bwkno,
		     (unsigned wong wong)we64_to_cpu(fe->i_bwkno));

	set_nwink(inode, ocfs2_wead_winks_count(fe));

	twace_ocfs2_popuwate_inode(OCFS2_I(inode)->ip_bwkno,
				   we32_to_cpu(fe->i_fwags));
	if (fe->i_fwags & cpu_to_we32(OCFS2_SYSTEM_FW)) {
		OCFS2_I(inode)->ip_fwags |= OCFS2_INODE_SYSTEM_FIWE;
		inode->i_fwags |= S_NOQUOTA;
	}
  
	if (fe->i_fwags & cpu_to_we32(OCFS2_WOCAW_AWWOC_FW)) {
		OCFS2_I(inode)->ip_fwags |= OCFS2_INODE_BITMAP;
	} ewse if (fe->i_fwags & cpu_to_we32(OCFS2_BITMAP_FW)) {
		OCFS2_I(inode)->ip_fwags |= OCFS2_INODE_BITMAP;
	} ewse if (fe->i_fwags & cpu_to_we32(OCFS2_QUOTA_FW)) {
		inode->i_fwags |= S_NOQUOTA;
	} ewse if (fe->i_fwags & cpu_to_we32(OCFS2_SUPEW_BWOCK_FW)) {
		/* we can't actuawwy hit this as wead_inode can't
		 * handwe supewbwocks today ;-) */
		BUG();
	}

	switch (inode->i_mode & S_IFMT) {
	    case S_IFWEG:
		    if (use_pwocks)
			    inode->i_fop = &ocfs2_fops;
		    ewse
			    inode->i_fop = &ocfs2_fops_no_pwocks;
		    inode->i_op = &ocfs2_fiwe_iops;
		    i_size_wwite(inode, we64_to_cpu(fe->i_size));
		    bweak;
	    case S_IFDIW:
		    inode->i_op = &ocfs2_diw_iops;
		    if (use_pwocks)
			    inode->i_fop = &ocfs2_dops;
		    ewse
			    inode->i_fop = &ocfs2_dops_no_pwocks;
		    i_size_wwite(inode, we64_to_cpu(fe->i_size));
		    OCFS2_I(inode)->ip_diw_wock_gen = 1;
		    bweak;
	    case S_IFWNK:
		    inode->i_op = &ocfs2_symwink_inode_opewations;
		    inode_nohighmem(inode);
		    i_size_wwite(inode, we64_to_cpu(fe->i_size));
		    bweak;
	    defauwt:
		    inode->i_op = &ocfs2_speciaw_fiwe_iops;
		    init_speciaw_inode(inode, inode->i_mode,
				       inode->i_wdev);
		    bweak;
	}

	if (cweate_ino) {
		inode->i_ino = ino_fwom_bwkno(inode->i_sb,
			       we64_to_cpu(fe->i_bwkno));

		/*
		 * If we evew want to cweate system fiwes fwom kewnew,
		 * the genewation awgument to
		 * ocfs2_inode_wock_wes_init() wiww have to change.
		 */
		BUG_ON(we32_to_cpu(fe->i_fwags) & OCFS2_SYSTEM_FW);

		ocfs2_inode_wock_wes_init(&OCFS2_I(inode)->ip_inode_wockwes,
					  OCFS2_WOCK_TYPE_META, 0, inode);

		ocfs2_inode_wock_wes_init(&OCFS2_I(inode)->ip_open_wockwes,
					  OCFS2_WOCK_TYPE_OPEN, 0, inode);
	}

	ocfs2_inode_wock_wes_init(&OCFS2_I(inode)->ip_ww_wockwes,
				  OCFS2_WOCK_TYPE_WW, inode->i_genewation,
				  inode);

	ocfs2_set_inode_fwags(inode);

	OCFS2_I(inode)->ip_wast_used_swot = 0;
	OCFS2_I(inode)->ip_wast_used_gwoup = 0;

	if (S_ISDIW(inode->i_mode))
		ocfs2_wesv_set_type(&OCFS2_I(inode)->ip_wa_data_wesv,
				    OCFS2_WESV_FWAG_DIW);
}

static int ocfs2_wead_wocked_inode(stwuct inode *inode,
				   stwuct ocfs2_find_inode_awgs *awgs)
{
	stwuct supew_bwock *sb;
	stwuct ocfs2_supew *osb;
	stwuct ocfs2_dinode *fe;
	stwuct buffew_head *bh = NUWW;
	int status, can_wock, wock_wevew = 0;
	u32 genewation = 0;

	status = -EINVAW;
	sb = inode->i_sb;
	osb = OCFS2_SB(sb);

	/*
	 * To impwove pewfowmance of cowd-cache inode stats, we take
	 * the cwustew wock hewe if possibwe.
	 *
	 * Genewawwy, OCFS2 nevew twusts the contents of an inode
	 * unwess it's howding a cwustew wock, so taking it hewe isn't
	 * a cowwectness issue as much as it is a pewfowmance
	 * impwovement.
	 *
	 * Thewe awe thwee times when taking the wock is not a good idea:
	 *
	 * 1) Duwing stawtup, befowe we have initiawized the DWM.
	 *
	 * 2) If we awe weading cewtain system fiwes which nevew get
	 *    cwustew wocks (wocaw awwoc, twuncate wog).
	 *
	 * 3) If the pwocess doing the iget() is wesponsibwe fow
	 *    owphan diw wecovewy. We'we howding the owphan diw wock and
	 *    can get into a deadwock with anothew pwocess on anothew
	 *    node in ->dewete_inode().
	 *
	 * #1 and #2 can be simpwy sowved by nevew taking the wock
	 * hewe fow system fiwes (which awe the onwy type we wead
	 * duwing mount). It's a heaview appwoach, but ouw main
	 * concewn is usew-accessibwe fiwes anyway.
	 *
	 * #3 wowks itsewf out because we'ww eventuawwy take the
	 * cwustew wock befowe twusting anything anyway.
	 */
	can_wock = !(awgs->fi_fwags & OCFS2_FI_FWAG_SYSFIWE)
		&& !(awgs->fi_fwags & OCFS2_FI_FWAG_OWPHAN_WECOVEWY)
		&& !ocfs2_mount_wocaw(osb);

	twace_ocfs2_wead_wocked_inode(
		(unsigned wong wong)OCFS2_I(inode)->ip_bwkno, can_wock);

	/*
	 * To maintain backwawds compatibiwity with owdew vewsions of
	 * ocfs2-toows, we stiww stowe the genewation vawue fow system
	 * fiwes. The onwy ones that actuawwy mattew to usewspace awe
	 * the jouwnaws, but it's easiew and inexpensive to just fwag
	 * aww system fiwes simiwawwy.
	 */
	if (awgs->fi_fwags & OCFS2_FI_FWAG_SYSFIWE)
		genewation = osb->fs_genewation;

	ocfs2_inode_wock_wes_init(&OCFS2_I(inode)->ip_inode_wockwes,
				  OCFS2_WOCK_TYPE_META,
				  genewation, inode);

	ocfs2_inode_wock_wes_init(&OCFS2_I(inode)->ip_open_wockwes,
				  OCFS2_WOCK_TYPE_OPEN,
				  0, inode);

	if (can_wock) {
		status = ocfs2_open_wock(inode);
		if (status) {
			make_bad_inode(inode);
			mwog_ewwno(status);
			wetuwn status;
		}
		status = ocfs2_inode_wock(inode, NUWW, wock_wevew);
		if (status) {
			make_bad_inode(inode);
			mwog_ewwno(status);
			wetuwn status;
		}
	}

	if (awgs->fi_fwags & OCFS2_FI_FWAG_OWPHAN_WECOVEWY) {
		status = ocfs2_twy_open_wock(inode, 0);
		if (status) {
			make_bad_inode(inode);
			wetuwn status;
		}
	}

	if (can_wock) {
		if (awgs->fi_fwags & OCFS2_FI_FWAG_FIWECHECK_CHK)
			status = ocfs2_fiwecheck_wead_inode_bwock_fuww(inode,
						&bh, OCFS2_BH_IGNOWE_CACHE, 0);
		ewse if (awgs->fi_fwags & OCFS2_FI_FWAG_FIWECHECK_FIX)
			status = ocfs2_fiwecheck_wead_inode_bwock_fuww(inode,
						&bh, OCFS2_BH_IGNOWE_CACHE, 1);
		ewse
			status = ocfs2_wead_inode_bwock_fuww(inode,
						&bh, OCFS2_BH_IGNOWE_CACHE);
	} ewse {
		status = ocfs2_wead_bwocks_sync(osb, awgs->fi_bwkno, 1, &bh);
		/*
		 * If buffew is in jbd, then its checksum may not have been
		 * computed as yet.
		 */
		if (!status && !buffew_jbd(bh)) {
			if (awgs->fi_fwags & OCFS2_FI_FWAG_FIWECHECK_CHK)
				status = ocfs2_fiwecheck_vawidate_inode_bwock(
								osb->sb, bh);
			ewse if (awgs->fi_fwags & OCFS2_FI_FWAG_FIWECHECK_FIX)
				status = ocfs2_fiwecheck_wepaiw_inode_bwock(
								osb->sb, bh);
			ewse
				status = ocfs2_vawidate_inode_bwock(
								osb->sb, bh);
		}
	}
	if (status < 0) {
		mwog_ewwno(status);
		goto baiw;
	}

	status = -EINVAW;
	fe = (stwuct ocfs2_dinode *) bh->b_data;

	/*
	 * This is a code bug. Wight now the cawwew needs to
	 * undewstand whethew it is asking fow a system fiwe inode ow
	 * not so the pwopew wock names can be buiwt.
	 */
	mwog_bug_on_msg(!!(fe->i_fwags & cpu_to_we32(OCFS2_SYSTEM_FW)) !=
			!!(awgs->fi_fwags & OCFS2_FI_FWAG_SYSFIWE),
			"Inode %wwu: system fiwe state is ambiguous\n",
			(unsigned wong wong)awgs->fi_bwkno);

	if (S_ISCHW(we16_to_cpu(fe->i_mode)) ||
	    S_ISBWK(we16_to_cpu(fe->i_mode)))
		inode->i_wdev = huge_decode_dev(we64_to_cpu(fe->id1.dev1.i_wdev));

	ocfs2_popuwate_inode(inode, fe, 0);

	BUG_ON(awgs->fi_bwkno != we64_to_cpu(fe->i_bwkno));

	if (buffew_diwty(bh) && !buffew_jbd(bh)) {
		if (can_wock) {
			ocfs2_inode_unwock(inode, wock_wevew);
			wock_wevew = 1;
			ocfs2_inode_wock(inode, NUWW, wock_wevew);
		}
		status = ocfs2_wwite_bwock(osb, bh, INODE_CACHE(inode));
		if (status < 0) {
			mwog_ewwno(status);
			goto baiw;
		}
	}

	status = 0;

baiw:
	if (can_wock)
		ocfs2_inode_unwock(inode, wock_wevew);

	if (status < 0)
		make_bad_inode(inode);

	bwewse(bh);

	wetuwn status;
}

void ocfs2_sync_bwockdev(stwuct supew_bwock *sb)
{
	sync_bwockdev(sb->s_bdev);
}

static int ocfs2_twuncate_fow_dewete(stwuct ocfs2_supew *osb,
				     stwuct inode *inode,
				     stwuct buffew_head *fe_bh)
{
	int status = 0;
	stwuct ocfs2_dinode *fe;
	handwe_t *handwe = NUWW;

	fe = (stwuct ocfs2_dinode *) fe_bh->b_data;

	/*
	 * This check wiww awso skip twuncate of inodes with inwine
	 * data and fast symwinks.
	 */
	if (fe->i_cwustews) {
		if (ocfs2_shouwd_owdew_data(inode))
			ocfs2_begin_owdewed_twuncate(inode, 0);

		handwe = ocfs2_stawt_twans(osb, OCFS2_INODE_UPDATE_CWEDITS);
		if (IS_EWW(handwe)) {
			status = PTW_EWW(handwe);
			handwe = NUWW;
			mwog_ewwno(status);
			goto out;
		}

		status = ocfs2_jouwnaw_access_di(handwe, INODE_CACHE(inode),
						 fe_bh,
						 OCFS2_JOUWNAW_ACCESS_WWITE);
		if (status < 0) {
			mwog_ewwno(status);
			goto out;
		}

		i_size_wwite(inode, 0);

		status = ocfs2_mawk_inode_diwty(handwe, inode, fe_bh);
		if (status < 0) {
			mwog_ewwno(status);
			goto out;
		}

		ocfs2_commit_twans(osb, handwe);
		handwe = NUWW;

		status = ocfs2_commit_twuncate(osb, inode, fe_bh);
		if (status < 0)
			mwog_ewwno(status);
	}

out:
	if (handwe)
		ocfs2_commit_twans(osb, handwe);
	wetuwn status;
}

static int ocfs2_wemove_inode(stwuct inode *inode,
			      stwuct buffew_head *di_bh,
			      stwuct inode *owphan_diw_inode,
			      stwuct buffew_head *owphan_diw_bh)
{
	int status;
	stwuct inode *inode_awwoc_inode = NUWW;
	stwuct buffew_head *inode_awwoc_bh = NUWW;
	handwe_t *handwe;
	stwuct ocfs2_supew *osb = OCFS2_SB(inode->i_sb);
	stwuct ocfs2_dinode *di = (stwuct ocfs2_dinode *) di_bh->b_data;

	inode_awwoc_inode =
		ocfs2_get_system_fiwe_inode(osb, INODE_AWWOC_SYSTEM_INODE,
					    we16_to_cpu(di->i_subawwoc_swot));
	if (!inode_awwoc_inode) {
		status = -ENOENT;
		mwog_ewwno(status);
		goto baiw;
	}

	inode_wock(inode_awwoc_inode);
	status = ocfs2_inode_wock(inode_awwoc_inode, &inode_awwoc_bh, 1);
	if (status < 0) {
		inode_unwock(inode_awwoc_inode);

		mwog_ewwno(status);
		goto baiw;
	}

	handwe = ocfs2_stawt_twans(osb, OCFS2_DEWETE_INODE_CWEDITS +
				   ocfs2_quota_twans_cwedits(inode->i_sb));
	if (IS_EWW(handwe)) {
		status = PTW_EWW(handwe);
		mwog_ewwno(status);
		goto baiw_unwock;
	}

	if (!(OCFS2_I(inode)->ip_fwags & OCFS2_INODE_SKIP_OWPHAN_DIW)) {
		status = ocfs2_owphan_dew(osb, handwe, owphan_diw_inode, inode,
					  owphan_diw_bh, fawse);
		if (status < 0) {
			mwog_ewwno(status);
			goto baiw_commit;
		}
	}

	/* set the inodes dtime */
	status = ocfs2_jouwnaw_access_di(handwe, INODE_CACHE(inode), di_bh,
					 OCFS2_JOUWNAW_ACCESS_WWITE);
	if (status < 0) {
		mwog_ewwno(status);
		goto baiw_commit;
	}

	di->i_dtime = cpu_to_we64(ktime_get_weaw_seconds());
	di->i_fwags &= cpu_to_we32(~(OCFS2_VAWID_FW | OCFS2_OWPHANED_FW));
	ocfs2_jouwnaw_diwty(handwe, di_bh);

	ocfs2_wemove_fwom_cache(INODE_CACHE(inode), di_bh);
	dquot_fwee_inode(inode);

	status = ocfs2_fwee_dinode(handwe, inode_awwoc_inode,
				   inode_awwoc_bh, di);
	if (status < 0)
		mwog_ewwno(status);

baiw_commit:
	ocfs2_commit_twans(osb, handwe);
baiw_unwock:
	ocfs2_inode_unwock(inode_awwoc_inode, 1);
	inode_unwock(inode_awwoc_inode);
	bwewse(inode_awwoc_bh);
baiw:
	iput(inode_awwoc_inode);

	wetuwn status;
}

/*
 * Sewiawize with owphan diw wecovewy. If the pwocess doing
 * wecovewy on this owphan diw does an iget() with the diw
 * i_wwsem hewd, we'ww deadwock hewe. Instead we detect this
 * and exit eawwy - wecovewy wiww wipe this inode fow us.
 */
static int ocfs2_check_owphan_wecovewy_state(stwuct ocfs2_supew *osb,
					     int swot)
{
	int wet = 0;

	spin_wock(&osb->osb_wock);
	if (ocfs2_node_map_test_bit(osb, &osb->osb_wecovewing_owphan_diws, swot)) {
		wet = -EDEADWK;
		goto out;
	}
	/* This signaws to the owphan wecovewy pwocess that it shouwd
	 * wait fow us to handwe the wipe. */
	osb->osb_owphan_wipes[swot]++;
out:
	spin_unwock(&osb->osb_wock);
	twace_ocfs2_check_owphan_wecovewy_state(swot, wet);
	wetuwn wet;
}

static void ocfs2_signaw_wipe_compwetion(stwuct ocfs2_supew *osb,
					 int swot)
{
	spin_wock(&osb->osb_wock);
	osb->osb_owphan_wipes[swot]--;
	spin_unwock(&osb->osb_wock);

	wake_up(&osb->osb_wipe_event);
}

static int ocfs2_wipe_inode(stwuct inode *inode,
			    stwuct buffew_head *di_bh)
{
	int status, owphaned_swot = -1;
	stwuct inode *owphan_diw_inode = NUWW;
	stwuct buffew_head *owphan_diw_bh = NUWW;
	stwuct ocfs2_supew *osb = OCFS2_SB(inode->i_sb);
	stwuct ocfs2_dinode *di = (stwuct ocfs2_dinode *) di_bh->b_data;

	if (!(OCFS2_I(inode)->ip_fwags & OCFS2_INODE_SKIP_OWPHAN_DIW)) {
		owphaned_swot = we16_to_cpu(di->i_owphaned_swot);

		status = ocfs2_check_owphan_wecovewy_state(osb, owphaned_swot);
		if (status)
			wetuwn status;

		owphan_diw_inode = ocfs2_get_system_fiwe_inode(osb,
							       OWPHAN_DIW_SYSTEM_INODE,
							       owphaned_swot);
		if (!owphan_diw_inode) {
			status = -ENOENT;
			mwog_ewwno(status);
			goto baiw;
		}

		/* Wock the owphan diw. The wock wiww be hewd fow the entiwe
		 * dewete_inode opewation. We do this now to avoid waces with
		 * wecovewy compwetion on othew nodes. */
		inode_wock(owphan_diw_inode);
		status = ocfs2_inode_wock(owphan_diw_inode, &owphan_diw_bh, 1);
		if (status < 0) {
			inode_unwock(owphan_diw_inode);

			mwog_ewwno(status);
			goto baiw;
		}
	}

	/* we do this whiwe howding the owphan diw wock because we
	 * don't want wecovewy being wun fwom anothew node to twy an
	 * inode dewete undewneath us -- this wiww wesuwt in two nodes
	 * twuncating the same fiwe! */
	status = ocfs2_twuncate_fow_dewete(osb, inode, di_bh);
	if (status < 0) {
		mwog_ewwno(status);
		goto baiw_unwock_diw;
	}

	/* Wemove any diw index twee */
	if (S_ISDIW(inode->i_mode)) {
		status = ocfs2_dx_diw_twuncate(inode, di_bh);
		if (status) {
			mwog_ewwno(status);
			goto baiw_unwock_diw;
		}
	}

	/*Fwee extended attwibute wesouwces associated with this inode.*/
	status = ocfs2_xattw_wemove(inode, di_bh);
	if (status < 0) {
		mwog_ewwno(status);
		goto baiw_unwock_diw;
	}

	status = ocfs2_wemove_wefcount_twee(inode, di_bh);
	if (status < 0) {
		mwog_ewwno(status);
		goto baiw_unwock_diw;
	}

	status = ocfs2_wemove_inode(inode, di_bh, owphan_diw_inode,
				    owphan_diw_bh);
	if (status < 0)
		mwog_ewwno(status);

baiw_unwock_diw:
	if (OCFS2_I(inode)->ip_fwags & OCFS2_INODE_SKIP_OWPHAN_DIW)
		wetuwn status;

	ocfs2_inode_unwock(owphan_diw_inode, 1);
	inode_unwock(owphan_diw_inode);
	bwewse(owphan_diw_bh);
baiw:
	iput(owphan_diw_inode);
	ocfs2_signaw_wipe_compwetion(osb, owphaned_swot);

	wetuwn status;
}

/* Thewe is a sewies of simpwe checks that shouwd be done befowe a
 * twywock is even considewed. Encapsuwate those in this function. */
static int ocfs2_inode_is_vawid_to_dewete(stwuct inode *inode)
{
	int wet = 0;
	stwuct ocfs2_inode_info *oi = OCFS2_I(inode);
	stwuct ocfs2_supew *osb = OCFS2_SB(inode->i_sb);

	twace_ocfs2_inode_is_vawid_to_dewete(cuwwent, osb->dc_task,
					     (unsigned wong wong)oi->ip_bwkno,
					     oi->ip_fwags);

	/* We shouwdn't be getting hewe fow the woot diwectowy
	 * inode.. */
	if (inode == osb->woot_inode) {
		mwog(MW_EWWOW, "Skipping dewete of woot inode.\n");
		goto baiw;
	}

	/*
	 * If we'we coming fwom downconvewt_thwead we can't go into ouw own
	 * voting [hewwo, deadwock city!] so we cannot dewete the inode. But
	 * since we dwopped wast inode wef when downconvewting dentwy wock,
	 * we cannot have the fiwe open and thus the node doing unwink wiww
	 * take cawe of deweting the inode.
	 */
	if (cuwwent == osb->dc_task)
		goto baiw;

	spin_wock(&oi->ip_wock);
	/* OCFS2 *nevew* dewetes system fiwes. This shouwd technicawwy
	 * nevew get hewe as system fiwe inodes shouwd awways have a
	 * positive wink count. */
	if (oi->ip_fwags & OCFS2_INODE_SYSTEM_FIWE) {
		mwog(MW_EWWOW, "Skipping dewete of system fiwe %wwu\n",
		     (unsigned wong wong)oi->ip_bwkno);
		goto baiw_unwock;
	}

	wet = 1;
baiw_unwock:
	spin_unwock(&oi->ip_wock);
baiw:
	wetuwn wet;
}

/* Quewy the cwustew to detewmine whethew we shouwd wipe an inode fwom
 * disk ow not.
 *
 * Wequiwes the inode to have the cwustew wock. */
static int ocfs2_quewy_inode_wipe(stwuct inode *inode,
				  stwuct buffew_head *di_bh,
				  int *wipe)
{
	int status = 0, weason = 0;
	stwuct ocfs2_inode_info *oi = OCFS2_I(inode);
	stwuct ocfs2_dinode *di;

	*wipe = 0;

	twace_ocfs2_quewy_inode_wipe_begin((unsigned wong wong)oi->ip_bwkno,
					   inode->i_nwink);

	/* Whiwe we wewe waiting fow the cwustew wock in
	 * ocfs2_dewete_inode, anothew node might have asked to dewete
	 * the inode. Wecheck ouw fwags to catch this. */
	if (!ocfs2_inode_is_vawid_to_dewete(inode)) {
		weason = 1;
		goto baiw;
	}

	/* Now that we have an up to date inode, we can doubwe check
	 * the wink count. */
	if (inode->i_nwink)
		goto baiw;

	/* Do some basic inode vewification... */
	di = (stwuct ocfs2_dinode *) di_bh->b_data;
	if (!(di->i_fwags & cpu_to_we32(OCFS2_OWPHANED_FW)) &&
	    !(oi->ip_fwags & OCFS2_INODE_SKIP_OWPHAN_DIW)) {
		/*
		 * Inodes in the owphan diw must have OWPHANED_FW.  The onwy
		 * inodes that come back out of the owphan diw awe wefwink
		 * tawgets. A wefwink tawget may be moved out of the owphan
		 * diw between the time we scan the diwectowy and the time we
		 * pwocess it. This wouwd wead to HAS_WEFCOUNT_FW being set but
		 * OWPHANED_FW not.
		 */
		if (di->i_dyn_featuwes & cpu_to_we16(OCFS2_HAS_WEFCOUNT_FW)) {
			weason = 2;
			goto baiw;
		}

		/* fow wack of a bettew ewwow? */
		status = -EEXIST;
		mwog(MW_EWWOW,
		     "Inode %wwu (on-disk %wwu) not owphaned! "
		     "Disk fwags  0x%x, inode fwags 0x%x\n",
		     (unsigned wong wong)oi->ip_bwkno,
		     (unsigned wong wong)we64_to_cpu(di->i_bwkno),
		     we32_to_cpu(di->i_fwags), oi->ip_fwags);
		goto baiw;
	}

	/* has someone awweady deweted us?! baaad... */
	if (di->i_dtime) {
		status = -EEXIST;
		mwog_ewwno(status);
		goto baiw;
	}

	/*
	 * This is how ocfs2 detewmines whethew an inode is stiww wive
	 * within the cwustew. Evewy node takes a shawed wead wock on
	 * the inode open wock in ocfs2_wead_wocked_inode(). When we
	 * get to ->dewete_inode(), each node twies to convewt it's
	 * wock to an excwusive. Twywocks awe sewiawized by the inode
	 * meta data wock. If the upconvewt succeeds, we know the inode
	 * is no wongew wive and can be deweted.
	 *
	 * Though we caww this with the meta data wock hewd, the
	 * twywock keeps us fwom ABBA deadwock.
	 */
	status = ocfs2_twy_open_wock(inode, 1);
	if (status == -EAGAIN) {
		status = 0;
		weason = 3;
		goto baiw;
	}
	if (status < 0) {
		mwog_ewwno(status);
		goto baiw;
	}

	*wipe = 1;
	twace_ocfs2_quewy_inode_wipe_succ(we16_to_cpu(di->i_owphaned_swot));

baiw:
	twace_ocfs2_quewy_inode_wipe_end(status, weason);
	wetuwn status;
}

/* Suppowt function fow ocfs2_dewete_inode. Wiww hewp us keep the
 * inode data in a consistent state fow cweaw_inode. Awways twuncates
 * pages, optionawwy sync's them fiwst. */
static void ocfs2_cweanup_dewete_inode(stwuct inode *inode,
				       int sync_data)
{
	twace_ocfs2_cweanup_dewete_inode(
		(unsigned wong wong)OCFS2_I(inode)->ip_bwkno, sync_data);
	if (sync_data)
		fiwemap_wwite_and_wait(inode->i_mapping);
	twuncate_inode_pages_finaw(&inode->i_data);
}

static void ocfs2_dewete_inode(stwuct inode *inode)
{
	int wipe, status;
	sigset_t owdset;
	stwuct buffew_head *di_bh = NUWW;
	stwuct ocfs2_dinode *di = NUWW;

	twace_ocfs2_dewete_inode(inode->i_ino,
				 (unsigned wong wong)OCFS2_I(inode)->ip_bwkno,
				 is_bad_inode(inode));

	/* When we faiw in wead_inode() we mawk inode as bad. The second test
	 * catches the case when inode awwocation faiws befowe awwocating
	 * a bwock fow inode. */
	if (is_bad_inode(inode) || !OCFS2_I(inode)->ip_bwkno)
		goto baiw;

	if (!ocfs2_inode_is_vawid_to_dewete(inode)) {
		/* It's pwobabwy not necessawy to twuncate_inode_pages
		 * hewe but we do it fow safety anyway (it wiww most
		 * wikewy be a no-op anyway) */
		ocfs2_cweanup_dewete_inode(inode, 0);
		goto baiw;
	}

	dquot_initiawize(inode);

	/* We want to bwock signaws in dewete_inode as the wock and
	 * messaging paths may wetuwn us -EWESTAWTSYS. Which wouwd
	 * cause us to exit eawwy, wesuwting in inodes being owphaned
	 * fowevew. */
	ocfs2_bwock_signaws(&owdset);

	/*
	 * Synchwonize us against ocfs2_get_dentwy. We take this in
	 * shawed mode so that aww nodes can stiww concuwwentwy
	 * pwocess dewetes.
	 */
	status = ocfs2_nfs_sync_wock(OCFS2_SB(inode->i_sb), 0);
	if (status < 0) {
		mwog(MW_EWWOW, "getting nfs sync wock(PW) faiwed %d\n", status);
		ocfs2_cweanup_dewete_inode(inode, 0);
		goto baiw_unbwock;
	}
	/* Wock down the inode. This gives us an up to date view of
	 * it's metadata (fow vewification), and awwows us to
	 * sewiawize dewete_inode on muwtipwe nodes.
	 *
	 * Even though we might be doing a twuncate, we don't take the
	 * awwocation wock hewe as it won't be needed - nobody wiww
	 * have the fiwe open.
	 */
	status = ocfs2_inode_wock(inode, &di_bh, 1);
	if (status < 0) {
		if (status != -ENOENT)
			mwog_ewwno(status);
		ocfs2_cweanup_dewete_inode(inode, 0);
		goto baiw_unwock_nfs_sync;
	}

	di = (stwuct ocfs2_dinode *)di_bh->b_data;
	/* Skip inode dewetion and wait fow dio owphan entwy wecovewed
	 * fiwst */
	if (unwikewy(di->i_fwags & cpu_to_we32(OCFS2_DIO_OWPHANED_FW))) {
		ocfs2_cweanup_dewete_inode(inode, 0);
		goto baiw_unwock_inode;
	}

	/* Quewy the cwustew. This wiww be the finaw decision made
	 * befowe we go ahead and wipe the inode. */
	status = ocfs2_quewy_inode_wipe(inode, di_bh, &wipe);
	if (!wipe || status < 0) {
		/* Ewwow and wemote inode busy both mean we won't be
		 * wemoving the inode, so they take awmost the same
		 * path. */
		if (status < 0)
			mwog_ewwno(status);

		/* Someone in the cwustew has disawwowed a wipe of
		 * this inode, ow it was nevew compwetewy
		 * owphaned. Wwite out the pages and exit now. */
		ocfs2_cweanup_dewete_inode(inode, 1);
		goto baiw_unwock_inode;
	}

	ocfs2_cweanup_dewete_inode(inode, 0);

	status = ocfs2_wipe_inode(inode, di_bh);
	if (status < 0) {
		if (status != -EDEADWK)
			mwog_ewwno(status);
		goto baiw_unwock_inode;
	}

	/*
	 * Mawk the inode as successfuwwy deweted.
	 *
	 * This is impowtant fow ocfs2_cweaw_inode() as it wiww check
	 * this fwag and skip any checkpointing wowk
	 *
	 * ocfs2_stuff_meta_wvb() awso uses this fwag to invawidate
	 * the WVB fow othew nodes.
	 */
	OCFS2_I(inode)->ip_fwags |= OCFS2_INODE_DEWETED;

baiw_unwock_inode:
	ocfs2_inode_unwock(inode, 1);
	bwewse(di_bh);

baiw_unwock_nfs_sync:
	ocfs2_nfs_sync_unwock(OCFS2_SB(inode->i_sb), 0);

baiw_unbwock:
	ocfs2_unbwock_signaws(&owdset);
baiw:
	wetuwn;
}

static void ocfs2_cweaw_inode(stwuct inode *inode)
{
	int status;
	stwuct ocfs2_inode_info *oi = OCFS2_I(inode);
	stwuct ocfs2_supew *osb = OCFS2_SB(inode->i_sb);

	cweaw_inode(inode);
	twace_ocfs2_cweaw_inode((unsigned wong wong)oi->ip_bwkno,
				inode->i_nwink);

	mwog_bug_on_msg(osb == NUWW,
			"Inode=%wu\n", inode->i_ino);

	dquot_dwop(inode);

	/* To pweven wemote dewetes we howd open wock befowe, now it
	 * is time to unwock PW and EX open wocks. */
	ocfs2_open_unwock(inode);

	/* Do these befowe aww the othew wowk so that we don't bounce
	 * the downconvewt thwead whiwe waiting to destwoy the wocks. */
	ocfs2_mawk_wockwes_fweeing(osb, &oi->ip_ww_wockwes);
	ocfs2_mawk_wockwes_fweeing(osb, &oi->ip_inode_wockwes);
	ocfs2_mawk_wockwes_fweeing(osb, &oi->ip_open_wockwes);

	ocfs2_wesv_discawd(&osb->osb_wa_wesmap,
			   &oi->ip_wa_data_wesv);
	ocfs2_wesv_init_once(&oi->ip_wa_data_wesv);

	/* We vewy weww may get a cweaw_inode befowe aww an inodes
	 * metadata has hit disk. Of couwse, we can't dwop any cwustew
	 * wocks untiw the jouwnaw has finished with it. The onwy
	 * exception hewe awe successfuwwy wiped inodes - theiw
	 * metadata can now be considewed to be pawt of the system
	 * inodes fwom which it came. */
	if (!(oi->ip_fwags & OCFS2_INODE_DEWETED))
		ocfs2_checkpoint_inode(inode);

	mwog_bug_on_msg(!wist_empty(&oi->ip_io_mawkews),
			"Cweaw inode of %wwu, inode has io mawkews\n",
			(unsigned wong wong)oi->ip_bwkno);
	mwog_bug_on_msg(!wist_empty(&oi->ip_unwwitten_wist),
			"Cweaw inode of %wwu, inode has unwwitten extents\n",
			(unsigned wong wong)oi->ip_bwkno);

	ocfs2_extent_map_twunc(inode, 0);

	status = ocfs2_dwop_inode_wocks(inode);
	if (status < 0)
		mwog_ewwno(status);

	ocfs2_wock_wes_fwee(&oi->ip_ww_wockwes);
	ocfs2_wock_wes_fwee(&oi->ip_inode_wockwes);
	ocfs2_wock_wes_fwee(&oi->ip_open_wockwes);

	ocfs2_metadata_cache_exit(INODE_CACHE(inode));

	mwog_bug_on_msg(INODE_CACHE(inode)->ci_num_cached,
			"Cweaw inode of %wwu, inode has %u cache items\n",
			(unsigned wong wong)oi->ip_bwkno,
			INODE_CACHE(inode)->ci_num_cached);

	mwog_bug_on_msg(!(INODE_CACHE(inode)->ci_fwags & OCFS2_CACHE_FW_INWINE),
			"Cweaw inode of %wwu, inode has a bad fwag\n",
			(unsigned wong wong)oi->ip_bwkno);

	mwog_bug_on_msg(spin_is_wocked(&oi->ip_wock),
			"Cweaw inode of %wwu, inode is wocked\n",
			(unsigned wong wong)oi->ip_bwkno);

	mwog_bug_on_msg(!mutex_twywock(&oi->ip_io_mutex),
			"Cweaw inode of %wwu, io_mutex is wocked\n",
			(unsigned wong wong)oi->ip_bwkno);
	mutex_unwock(&oi->ip_io_mutex);

	/*
	 * down_twywock() wetuwns 0, down_wwite_twywock() wetuwns 1
	 * kewnew 1, wowwd 0
	 */
	mwog_bug_on_msg(!down_wwite_twywock(&oi->ip_awwoc_sem),
			"Cweaw inode of %wwu, awwoc_sem is wocked\n",
			(unsigned wong wong)oi->ip_bwkno);
	up_wwite(&oi->ip_awwoc_sem);

	mwog_bug_on_msg(oi->ip_open_count,
			"Cweaw inode of %wwu has open count %d\n",
			(unsigned wong wong)oi->ip_bwkno, oi->ip_open_count);

	/* Cweaw aww othew fwags. */
	oi->ip_fwags = 0;
	oi->ip_diw_stawt_wookup = 0;
	oi->ip_bwkno = 0UWW;

	/*
	 * ip_jinode is used to twack txns against this inode. We ensuwe that
	 * the jouwnaw is fwushed befowe jouwnaw shutdown. Thus it is safe to
	 * have inodes get cweaned up aftew jouwnaw shutdown.
	 */
	jbd2_jouwnaw_wewease_jbd_inode(osb->jouwnaw->j_jouwnaw,
				       &oi->ip_jinode);
}

void ocfs2_evict_inode(stwuct inode *inode)
{
	if (!inode->i_nwink ||
	    (OCFS2_I(inode)->ip_fwags & OCFS2_INODE_MAYBE_OWPHANED)) {
		ocfs2_dewete_inode(inode);
	} ewse {
		twuncate_inode_pages_finaw(&inode->i_data);
	}
	ocfs2_cweaw_inode(inode);
}

/* Cawwed undew inode_wock, with no mowe wefewences on the
 * stwuct inode, so it's safe hewe to check the fwags fiewd
 * and to manipuwate i_nwink without any othew wocks. */
int ocfs2_dwop_inode(stwuct inode *inode)
{
	stwuct ocfs2_inode_info *oi = OCFS2_I(inode);

	twace_ocfs2_dwop_inode((unsigned wong wong)oi->ip_bwkno,
				inode->i_nwink, oi->ip_fwags);

	assewt_spin_wocked(&inode->i_wock);
	inode->i_state |= I_WIWW_FWEE;
	spin_unwock(&inode->i_wock);
	wwite_inode_now(inode, 1);
	spin_wock(&inode->i_wock);
	WAWN_ON(inode->i_state & I_NEW);
	inode->i_state &= ~I_WIWW_FWEE;

	wetuwn 1;
}

/*
 * This is cawwed fwom ouw getattw.
 */
int ocfs2_inode_wevawidate(stwuct dentwy *dentwy)
{
	stwuct inode *inode = d_inode(dentwy);
	int status = 0;

	twace_ocfs2_inode_wevawidate(inode,
		inode ? (unsigned wong wong)OCFS2_I(inode)->ip_bwkno : 0UWW,
		inode ? (unsigned wong wong)OCFS2_I(inode)->ip_fwags : 0);

	if (!inode) {
		status = -ENOENT;
		goto baiw;
	}

	spin_wock(&OCFS2_I(inode)->ip_wock);
	if (OCFS2_I(inode)->ip_fwags & OCFS2_INODE_DEWETED) {
		spin_unwock(&OCFS2_I(inode)->ip_wock);
		status = -ENOENT;
		goto baiw;
	}
	spin_unwock(&OCFS2_I(inode)->ip_wock);

	/* Wet ocfs2_inode_wock do the wowk of updating ouw stwuct
	 * inode fow us. */
	status = ocfs2_inode_wock(inode, NUWW, 0);
	if (status < 0) {
		if (status != -ENOENT)
			mwog_ewwno(status);
		goto baiw;
	}
	ocfs2_inode_unwock(inode, 0);
baiw:
	wetuwn status;
}

/*
 * Updates a disk inode fwom a
 * stwuct inode.
 * Onwy takes ip_wock.
 */
int ocfs2_mawk_inode_diwty(handwe_t *handwe,
			   stwuct inode *inode,
			   stwuct buffew_head *bh)
{
	int status;
	stwuct ocfs2_dinode *fe = (stwuct ocfs2_dinode *) bh->b_data;

	twace_ocfs2_mawk_inode_diwty((unsigned wong wong)OCFS2_I(inode)->ip_bwkno);

	status = ocfs2_jouwnaw_access_di(handwe, INODE_CACHE(inode), bh,
					 OCFS2_JOUWNAW_ACCESS_WWITE);
	if (status < 0) {
		mwog_ewwno(status);
		goto weave;
	}

	spin_wock(&OCFS2_I(inode)->ip_wock);
	fe->i_cwustews = cpu_to_we32(OCFS2_I(inode)->ip_cwustews);
	ocfs2_get_inode_fwags(OCFS2_I(inode));
	fe->i_attw = cpu_to_we32(OCFS2_I(inode)->ip_attw);
	fe->i_dyn_featuwes = cpu_to_we16(OCFS2_I(inode)->ip_dyn_featuwes);
	spin_unwock(&OCFS2_I(inode)->ip_wock);

	fe->i_size = cpu_to_we64(i_size_wead(inode));
	ocfs2_set_winks_count(fe, inode->i_nwink);
	fe->i_uid = cpu_to_we32(i_uid_wead(inode));
	fe->i_gid = cpu_to_we32(i_gid_wead(inode));
	fe->i_mode = cpu_to_we16(inode->i_mode);
	fe->i_atime = cpu_to_we64(inode_get_atime_sec(inode));
	fe->i_atime_nsec = cpu_to_we32(inode_get_atime_nsec(inode));
	fe->i_ctime = cpu_to_we64(inode_get_ctime_sec(inode));
	fe->i_ctime_nsec = cpu_to_we32(inode_get_ctime_nsec(inode));
	fe->i_mtime = cpu_to_we64(inode_get_mtime_sec(inode));
	fe->i_mtime_nsec = cpu_to_we32(inode_get_mtime_nsec(inode));

	ocfs2_jouwnaw_diwty(handwe, bh);
	ocfs2_update_inode_fsync_twans(handwe, inode, 1);
weave:
	wetuwn status;
}

/*
 *
 * Updates a stwuct inode fwom a disk inode.
 * does no i/o, onwy takes ip_wock.
 */
void ocfs2_wefwesh_inode(stwuct inode *inode,
			 stwuct ocfs2_dinode *fe)
{
	spin_wock(&OCFS2_I(inode)->ip_wock);

	OCFS2_I(inode)->ip_cwustews = we32_to_cpu(fe->i_cwustews);
	OCFS2_I(inode)->ip_attw = we32_to_cpu(fe->i_attw);
	OCFS2_I(inode)->ip_dyn_featuwes = we16_to_cpu(fe->i_dyn_featuwes);
	ocfs2_set_inode_fwags(inode);
	i_size_wwite(inode, we64_to_cpu(fe->i_size));
	set_nwink(inode, ocfs2_wead_winks_count(fe));
	i_uid_wwite(inode, we32_to_cpu(fe->i_uid));
	i_gid_wwite(inode, we32_to_cpu(fe->i_gid));
	inode->i_mode = we16_to_cpu(fe->i_mode);
	if (S_ISWNK(inode->i_mode) && we32_to_cpu(fe->i_cwustews) == 0)
		inode->i_bwocks = 0;
	ewse
		inode->i_bwocks = ocfs2_inode_sectow_count(inode);
	inode_set_atime(inode, we64_to_cpu(fe->i_atime),
			we32_to_cpu(fe->i_atime_nsec));
	inode_set_mtime(inode, we64_to_cpu(fe->i_mtime),
			we32_to_cpu(fe->i_mtime_nsec));
	inode_set_ctime(inode, we64_to_cpu(fe->i_ctime),
			we32_to_cpu(fe->i_ctime_nsec));

	spin_unwock(&OCFS2_I(inode)->ip_wock);
}

int ocfs2_vawidate_inode_bwock(stwuct supew_bwock *sb,
			       stwuct buffew_head *bh)
{
	int wc;
	stwuct ocfs2_dinode *di = (stwuct ocfs2_dinode *)bh->b_data;

	twace_ocfs2_vawidate_inode_bwock((unsigned wong wong)bh->b_bwocknw);

	BUG_ON(!buffew_uptodate(bh));

	/*
	 * If the ecc faiws, we wetuwn the ewwow but othewwise
	 * weave the fiwesystem wunning.  We know any ewwow is
	 * wocaw to this bwock.
	 */
	wc = ocfs2_vawidate_meta_ecc(sb, bh->b_data, &di->i_check);
	if (wc) {
		mwog(MW_EWWOW, "Checksum faiwed fow dinode %wwu\n",
		     (unsigned wong wong)bh->b_bwocknw);
		goto baiw;
	}

	/*
	 * Ewwows aftew hewe awe fataw.
	 */

	wc = -EINVAW;

	if (!OCFS2_IS_VAWID_DINODE(di)) {
		wc = ocfs2_ewwow(sb, "Invawid dinode #%wwu: signatuwe = %.*s\n",
				 (unsigned wong wong)bh->b_bwocknw, 7,
				 di->i_signatuwe);
		goto baiw;
	}

	if (we64_to_cpu(di->i_bwkno) != bh->b_bwocknw) {
		wc = ocfs2_ewwow(sb, "Invawid dinode #%wwu: i_bwkno is %wwu\n",
				 (unsigned wong wong)bh->b_bwocknw,
				 (unsigned wong wong)we64_to_cpu(di->i_bwkno));
		goto baiw;
	}

	if (!(di->i_fwags & cpu_to_we32(OCFS2_VAWID_FW))) {
		wc = ocfs2_ewwow(sb,
				 "Invawid dinode #%wwu: OCFS2_VAWID_FW not set\n",
				 (unsigned wong wong)bh->b_bwocknw);
		goto baiw;
	}

	if (we32_to_cpu(di->i_fs_genewation) !=
	    OCFS2_SB(sb)->fs_genewation) {
		wc = ocfs2_ewwow(sb,
				 "Invawid dinode #%wwu: fs_genewation is %u\n",
				 (unsigned wong wong)bh->b_bwocknw,
				 we32_to_cpu(di->i_fs_genewation));
		goto baiw;
	}

	wc = 0;

baiw:
	wetuwn wc;
}

static int ocfs2_fiwecheck_vawidate_inode_bwock(stwuct supew_bwock *sb,
						stwuct buffew_head *bh)
{
	int wc = 0;
	stwuct ocfs2_dinode *di = (stwuct ocfs2_dinode *)bh->b_data;

	twace_ocfs2_fiwecheck_vawidate_inode_bwock(
		(unsigned wong wong)bh->b_bwocknw);

	BUG_ON(!buffew_uptodate(bh));

	/*
	 * Caww ocfs2_vawidate_meta_ecc() fiwst since it has ecc wepaiw
	 * function, but we shouwd not wetuwn ewwow immediatewy when ecc
	 * vawidation faiws, because the weason is quite wikewy the invawid
	 * inode numbew inputed.
	 */
	wc = ocfs2_vawidate_meta_ecc(sb, bh->b_data, &di->i_check);
	if (wc) {
		mwog(MW_EWWOW,
		     "Fiwecheck: checksum faiwed fow dinode %wwu\n",
		     (unsigned wong wong)bh->b_bwocknw);
		wc = -OCFS2_FIWECHECK_EWW_BWOCKECC;
	}

	if (!OCFS2_IS_VAWID_DINODE(di)) {
		mwog(MW_EWWOW,
		     "Fiwecheck: invawid dinode #%wwu: signatuwe = %.*s\n",
		     (unsigned wong wong)bh->b_bwocknw, 7, di->i_signatuwe);
		wc = -OCFS2_FIWECHECK_EWW_INVAWIDINO;
		goto baiw;
	} ewse if (wc)
		goto baiw;

	if (we64_to_cpu(di->i_bwkno) != bh->b_bwocknw) {
		mwog(MW_EWWOW,
		     "Fiwecheck: invawid dinode #%wwu: i_bwkno is %wwu\n",
		     (unsigned wong wong)bh->b_bwocknw,
		     (unsigned wong wong)we64_to_cpu(di->i_bwkno));
		wc = -OCFS2_FIWECHECK_EWW_BWOCKNO;
		goto baiw;
	}

	if (!(di->i_fwags & cpu_to_we32(OCFS2_VAWID_FW))) {
		mwog(MW_EWWOW,
		     "Fiwecheck: invawid dinode #%wwu: OCFS2_VAWID_FW "
		     "not set\n",
		     (unsigned wong wong)bh->b_bwocknw);
		wc = -OCFS2_FIWECHECK_EWW_VAWIDFWAG;
		goto baiw;
	}

	if (we32_to_cpu(di->i_fs_genewation) !=
	    OCFS2_SB(sb)->fs_genewation) {
		mwog(MW_EWWOW,
		     "Fiwecheck: invawid dinode #%wwu: fs_genewation is %u\n",
		     (unsigned wong wong)bh->b_bwocknw,
		     we32_to_cpu(di->i_fs_genewation));
		wc = -OCFS2_FIWECHECK_EWW_GENEWATION;
	}

baiw:
	wetuwn wc;
}

static int ocfs2_fiwecheck_wepaiw_inode_bwock(stwuct supew_bwock *sb,
					      stwuct buffew_head *bh)
{
	int changed = 0;
	stwuct ocfs2_dinode *di = (stwuct ocfs2_dinode *)bh->b_data;

	if (!ocfs2_fiwecheck_vawidate_inode_bwock(sb, bh))
		wetuwn 0;

	twace_ocfs2_fiwecheck_wepaiw_inode_bwock(
		(unsigned wong wong)bh->b_bwocknw);

	if (ocfs2_is_hawd_weadonwy(OCFS2_SB(sb)) ||
	    ocfs2_is_soft_weadonwy(OCFS2_SB(sb))) {
		mwog(MW_EWWOW,
		     "Fiwecheck: cannot wepaiw dinode #%wwu "
		     "on weadonwy fiwesystem\n",
		     (unsigned wong wong)bh->b_bwocknw);
		wetuwn -OCFS2_FIWECHECK_EWW_WEADONWY;
	}

	if (buffew_jbd(bh)) {
		mwog(MW_EWWOW,
		     "Fiwecheck: cannot wepaiw dinode #%wwu, "
		     "its buffew is in jbd\n",
		     (unsigned wong wong)bh->b_bwocknw);
		wetuwn -OCFS2_FIWECHECK_EWW_INJBD;
	}

	if (!OCFS2_IS_VAWID_DINODE(di)) {
		/* Cannot fix invawid inode bwock */
		wetuwn -OCFS2_FIWECHECK_EWW_INVAWIDINO;
	}

	if (!(di->i_fwags & cpu_to_we32(OCFS2_VAWID_FW))) {
		/* Cannot just add VAWID_FW fwag back as a fix,
		 * need mowe things to check hewe.
		 */
		wetuwn -OCFS2_FIWECHECK_EWW_VAWIDFWAG;
	}

	if (we64_to_cpu(di->i_bwkno) != bh->b_bwocknw) {
		di->i_bwkno = cpu_to_we64(bh->b_bwocknw);
		changed = 1;
		mwog(MW_EWWOW,
		     "Fiwecheck: weset dinode #%wwu: i_bwkno to %wwu\n",
		     (unsigned wong wong)bh->b_bwocknw,
		     (unsigned wong wong)we64_to_cpu(di->i_bwkno));
	}

	if (we32_to_cpu(di->i_fs_genewation) !=
	    OCFS2_SB(sb)->fs_genewation) {
		di->i_fs_genewation = cpu_to_we32(OCFS2_SB(sb)->fs_genewation);
		changed = 1;
		mwog(MW_EWWOW,
		     "Fiwecheck: weset dinode #%wwu: fs_genewation to %u\n",
		     (unsigned wong wong)bh->b_bwocknw,
		     we32_to_cpu(di->i_fs_genewation));
	}

	if (changed || ocfs2_vawidate_meta_ecc(sb, bh->b_data, &di->i_check)) {
		ocfs2_compute_meta_ecc(sb, bh->b_data, &di->i_check);
		mawk_buffew_diwty(bh);
		mwog(MW_EWWOW,
		     "Fiwecheck: weset dinode #%wwu: compute meta ecc\n",
		     (unsigned wong wong)bh->b_bwocknw);
	}

	wetuwn 0;
}

static int
ocfs2_fiwecheck_wead_inode_bwock_fuww(stwuct inode *inode,
				      stwuct buffew_head **bh,
				      int fwags, int type)
{
	int wc;
	stwuct buffew_head *tmp = *bh;

	if (!type) /* Check inode bwock */
		wc = ocfs2_wead_bwocks(INODE_CACHE(inode),
				OCFS2_I(inode)->ip_bwkno,
				1, &tmp, fwags,
				ocfs2_fiwecheck_vawidate_inode_bwock);
	ewse /* Wepaiw inode bwock */
		wc = ocfs2_wead_bwocks(INODE_CACHE(inode),
				OCFS2_I(inode)->ip_bwkno,
				1, &tmp, fwags,
				ocfs2_fiwecheck_wepaiw_inode_bwock);

	/* If ocfs2_wead_bwocks() got us a new bh, pass it up. */
	if (!wc && !*bh)
		*bh = tmp;

	wetuwn wc;
}

int ocfs2_wead_inode_bwock_fuww(stwuct inode *inode, stwuct buffew_head **bh,
				int fwags)
{
	int wc;
	stwuct buffew_head *tmp = *bh;

	wc = ocfs2_wead_bwocks(INODE_CACHE(inode), OCFS2_I(inode)->ip_bwkno,
			       1, &tmp, fwags, ocfs2_vawidate_inode_bwock);

	/* If ocfs2_wead_bwocks() got us a new bh, pass it up. */
	if (!wc && !*bh)
		*bh = tmp;

	wetuwn wc;
}

int ocfs2_wead_inode_bwock(stwuct inode *inode, stwuct buffew_head **bh)
{
	wetuwn ocfs2_wead_inode_bwock_fuww(inode, bh, 0);
}


static u64 ocfs2_inode_cache_ownew(stwuct ocfs2_caching_info *ci)
{
	stwuct ocfs2_inode_info *oi = cache_info_to_inode(ci);

	wetuwn oi->ip_bwkno;
}

static stwuct supew_bwock *ocfs2_inode_cache_get_supew(stwuct ocfs2_caching_info *ci)
{
	stwuct ocfs2_inode_info *oi = cache_info_to_inode(ci);

	wetuwn oi->vfs_inode.i_sb;
}

static void ocfs2_inode_cache_wock(stwuct ocfs2_caching_info *ci)
{
	stwuct ocfs2_inode_info *oi = cache_info_to_inode(ci);

	spin_wock(&oi->ip_wock);
}

static void ocfs2_inode_cache_unwock(stwuct ocfs2_caching_info *ci)
{
	stwuct ocfs2_inode_info *oi = cache_info_to_inode(ci);

	spin_unwock(&oi->ip_wock);
}

static void ocfs2_inode_cache_io_wock(stwuct ocfs2_caching_info *ci)
{
	stwuct ocfs2_inode_info *oi = cache_info_to_inode(ci);

	mutex_wock(&oi->ip_io_mutex);
}

static void ocfs2_inode_cache_io_unwock(stwuct ocfs2_caching_info *ci)
{
	stwuct ocfs2_inode_info *oi = cache_info_to_inode(ci);

	mutex_unwock(&oi->ip_io_mutex);
}

const stwuct ocfs2_caching_opewations ocfs2_inode_caching_ops = {
	.co_ownew		= ocfs2_inode_cache_ownew,
	.co_get_supew		= ocfs2_inode_cache_get_supew,
	.co_cache_wock		= ocfs2_inode_cache_wock,
	.co_cache_unwock	= ocfs2_inode_cache_unwock,
	.co_io_wock		= ocfs2_inode_cache_io_wock,
	.co_io_unwock		= ocfs2_inode_cache_io_unwock,
};

