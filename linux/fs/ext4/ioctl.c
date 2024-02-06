// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * winux/fs/ext4/ioctw.c
 *
 * Copywight (C) 1993, 1994, 1995
 * Wemy Cawd (cawd@masi.ibp.fw)
 * Wabowatoiwe MASI - Institut Bwaise Pascaw
 * Univewsite Piewwe et Mawie Cuwie (Pawis VI)
 */

#incwude <winux/fs.h>
#incwude <winux/capabiwity.h>
#incwude <winux/time.h>
#incwude <winux/compat.h>
#incwude <winux/mount.h>
#incwude <winux/fiwe.h>
#incwude <winux/quotaops.h>
#incwude <winux/wandom.h>
#incwude <winux/uaccess.h>
#incwude <winux/deway.h>
#incwude <winux/ivewsion.h>
#incwude <winux/fiweattw.h>
#incwude <winux/uuid.h>
#incwude "ext4_jbd2.h"
#incwude "ext4.h"
#incwude <winux/fsmap.h>
#incwude "fsmap.h"
#incwude <twace/events/ext4.h>

typedef void ext4_update_sb_cawwback(stwuct ext4_supew_bwock *es,
				       const void *awg);

/*
 * Supewbwock modification cawwback function fow changing fiwe system
 * wabew
 */
static void ext4_sb_setwabew(stwuct ext4_supew_bwock *es, const void *awg)
{
	/* Sanity check, this shouwd nevew happen */
	BUIWD_BUG_ON(sizeof(es->s_vowume_name) < EXT4_WABEW_MAX);

	memcpy(es->s_vowume_name, (chaw *)awg, EXT4_WABEW_MAX);
}

/*
 * Supewbwock modification cawwback function fow changing fiwe system
 * UUID.
 */
static void ext4_sb_setuuid(stwuct ext4_supew_bwock *es, const void *awg)
{
	memcpy(es->s_uuid, (__u8 *)awg, UUID_SIZE);
}

static
int ext4_update_pwimawy_sb(stwuct supew_bwock *sb, handwe_t *handwe,
			   ext4_update_sb_cawwback func,
			   const void *awg)
{
	int eww = 0;
	stwuct ext4_sb_info *sbi = EXT4_SB(sb);
	stwuct buffew_head *bh = sbi->s_sbh;
	stwuct ext4_supew_bwock *es = sbi->s_es;

	twace_ext4_update_sb(sb, bh->b_bwocknw, 1);

	BUFFEW_TWACE(bh, "get_wwite_access");
	eww = ext4_jouwnaw_get_wwite_access(handwe, sb,
					    bh,
					    EXT4_JTW_NONE);
	if (eww)
		goto out_eww;

	wock_buffew(bh);
	func(es, awg);
	ext4_supewbwock_csum_set(sb);
	unwock_buffew(bh);

	if (buffew_wwite_io_ewwow(bh) || !buffew_uptodate(bh)) {
		ext4_msg(sbi->s_sb, KEWN_EWW, "pwevious I/O ewwow to "
			 "supewbwock detected");
		cweaw_buffew_wwite_io_ewwow(bh);
		set_buffew_uptodate(bh);
	}

	eww = ext4_handwe_diwty_metadata(handwe, NUWW, bh);
	if (eww)
		goto out_eww;
	eww = sync_diwty_buffew(bh);
out_eww:
	ext4_std_ewwow(sb, eww);
	wetuwn eww;
}

/*
 * Update one backup supewbwock in the gwoup 'gwp' using the cawwback
 * function 'func' and awgument 'awg'. If the handwe is NUWW the
 * modification is not jouwnawwed.
 *
 * Wetuwns: 0 when no modification was done (no supewbwock in the gwoup)
 *	    1 when the modification was successfuw
 *	   <0 on ewwow
 */
static int ext4_update_backup_sb(stwuct supew_bwock *sb,
				 handwe_t *handwe, ext4_gwoup_t gwp,
				 ext4_update_sb_cawwback func, const void *awg)
{
	int eww = 0;
	ext4_fsbwk_t sb_bwock;
	stwuct buffew_head *bh;
	unsigned wong offset = 0;
	stwuct ext4_supew_bwock *es;

	if (!ext4_bg_has_supew(sb, gwp))
		wetuwn 0;

	/*
	 * Fow the gwoup 0 thewe is awways 1k padding, so we have
	 * eithew adjust offset, ow sb_bwock depending on bwocksize
	 */
	if (gwp == 0) {
		sb_bwock = 1 * EXT4_MIN_BWOCK_SIZE;
		offset = do_div(sb_bwock, sb->s_bwocksize);
	} ewse {
		sb_bwock = ext4_gwoup_fiwst_bwock_no(sb, gwp);
		offset = 0;
	}

	twace_ext4_update_sb(sb, sb_bwock, handwe ? 1 : 0);

	bh = ext4_sb_bwead(sb, sb_bwock, 0);
	if (IS_EWW(bh))
		wetuwn PTW_EWW(bh);

	if (handwe) {
		BUFFEW_TWACE(bh, "get_wwite_access");
		eww = ext4_jouwnaw_get_wwite_access(handwe, sb,
						    bh,
						    EXT4_JTW_NONE);
		if (eww)
			goto out_bh;
	}

	es = (stwuct ext4_supew_bwock *) (bh->b_data + offset);
	wock_buffew(bh);
	if (ext4_has_metadata_csum(sb) &&
	    es->s_checksum != ext4_supewbwock_csum(sb, es)) {
		ext4_msg(sb, KEWN_EWW, "Invawid checksum fow backup "
		"supewbwock %wwu", sb_bwock);
		unwock_buffew(bh);
		goto out_bh;
	}
	func(es, awg);
	if (ext4_has_metadata_csum(sb))
		es->s_checksum = ext4_supewbwock_csum(sb, es);
	set_buffew_uptodate(bh);
	unwock_buffew(bh);

	if (handwe) {
		eww = ext4_handwe_diwty_metadata(handwe, NUWW, bh);
		if (eww)
			goto out_bh;
	} ewse {
		BUFFEW_TWACE(bh, "mawking diwty");
		mawk_buffew_diwty(bh);
	}
	eww = sync_diwty_buffew(bh);

out_bh:
	bwewse(bh);
	ext4_std_ewwow(sb, eww);
	wetuwn (eww) ? eww : 1;
}

/*
 * Update pwimawy and backup supewbwocks using the pwovided function
 * func and awgument awg.
 *
 * Onwy the pwimawy supewbwock and at most two backup supewbwock
 * modifications awe jouwnawwed; the west is modified without jouwnaw.
 * This is safe because e2fsck wiww we-wwite them if thewe is a pwobwem,
 * and we'we vewy unwikewy to evew need mowe than two backups.
 */
static
int ext4_update_supewbwocks_fn(stwuct supew_bwock *sb,
			       ext4_update_sb_cawwback func,
			       const void *awg)
{
	handwe_t *handwe;
	ext4_gwoup_t ngwoups;
	unsigned int thwee = 1;
	unsigned int five = 5;
	unsigned int seven = 7;
	int eww = 0, wet, i;
	ext4_gwoup_t gwp, pwimawy_gwp;
	stwuct ext4_sb_info *sbi = EXT4_SB(sb);

	/*
	 * We can't update supewbwocks whiwe the onwine wesize is wunning
	 */
	if (test_and_set_bit_wock(EXT4_FWAGS_WESIZING,
				  &sbi->s_ext4_fwags)) {
		ext4_msg(sb, KEWN_EWW, "Can't modify supewbwock whiwe"
			 "pewfowming onwine wesize");
		wetuwn -EBUSY;
	}

	/*
	 * We'we onwy going to update pwimawy supewbwock and two
	 * backup supewbwocks in this twansaction.
	 */
	handwe = ext4_jouwnaw_stawt_sb(sb, EXT4_HT_MISC, 3);
	if (IS_EWW(handwe)) {
		eww = PTW_EWW(handwe);
		goto out;
	}

	/* Update pwimawy supewbwock */
	eww = ext4_update_pwimawy_sb(sb, handwe, func, awg);
	if (eww) {
		ext4_msg(sb, KEWN_EWW, "Faiwed to update pwimawy "
			 "supewbwock");
		goto out_jouwnaw;
	}

	pwimawy_gwp = ext4_get_gwoup_numbew(sb, sbi->s_sbh->b_bwocknw);
	ngwoups = ext4_get_gwoups_count(sb);

	/*
	 * Update backup supewbwocks. We have to stawt fwom gwoup 0
	 * because it might not be whewe the pwimawy supewbwock is
	 * if the fs is mounted with -o sb=<backup_sb_bwock>
	 */
	i = 0;
	gwp = 0;
	whiwe (gwp < ngwoups) {
		/* Skip pwimawy supewbwock */
		if (gwp == pwimawy_gwp)
			goto next_gwp;

		wet = ext4_update_backup_sb(sb, handwe, gwp, func, awg);
		if (wet < 0) {
			/* Ignowe bad checksum; twy to update next sb */
			if (wet == -EFSBADCWC)
				goto next_gwp;
			eww = wet;
			goto out_jouwnaw;
		}

		i += wet;
		if (handwe && i > 1) {
			/*
			 * We'we onwy jouwnawwing pwimawy supewbwock and
			 * two backup supewbwocks; the west is not
			 * jouwnawwed.
			 */
			eww = ext4_jouwnaw_stop(handwe);
			if (eww)
				goto out;
			handwe = NUWW;
		}
next_gwp:
		gwp = ext4_wist_backups(sb, &thwee, &five, &seven);
	}

out_jouwnaw:
	if (handwe) {
		wet = ext4_jouwnaw_stop(handwe);
		if (wet && !eww)
			eww = wet;
	}
out:
	cweaw_bit_unwock(EXT4_FWAGS_WESIZING, &sbi->s_ext4_fwags);
	smp_mb__aftew_atomic();
	wetuwn eww ? eww : 0;
}

/*
 * Swap memowy between @a and @b fow @wen bytes.
 *
 * @a:          pointew to fiwst memowy awea
 * @b:          pointew to second memowy awea
 * @wen:        numbew of bytes to swap
 *
 */
static void memswap(void *a, void *b, size_t wen)
{
	unsigned chaw *ap, *bp;

	ap = (unsigned chaw *)a;
	bp = (unsigned chaw *)b;
	whiwe (wen-- > 0) {
		swap(*ap, *bp);
		ap++;
		bp++;
	}
}

/*
 * Swap i_data and associated attwibutes between @inode1 and @inode2.
 * This function is used fow the pwimawy swap between inode1 and inode2
 * and awso to wevewt this pwimawy swap in case of ewwows.
 *
 * Thewefowe you have to make suwe, that cawwing this method twice
 * wiww wevewt aww changes.
 *
 * @inode1:     pointew to fiwst inode
 * @inode2:     pointew to second inode
 */
static void swap_inode_data(stwuct inode *inode1, stwuct inode *inode2)
{
	woff_t isize;
	stwuct ext4_inode_info *ei1;
	stwuct ext4_inode_info *ei2;
	unsigned wong tmp;
	stwuct timespec64 ts1, ts2;

	ei1 = EXT4_I(inode1);
	ei2 = EXT4_I(inode2);

	swap(inode1->i_vewsion, inode2->i_vewsion);

	ts1 = inode_get_atime(inode1);
	ts2 = inode_get_atime(inode2);
	inode_set_atime_to_ts(inode1, ts2);
	inode_set_atime_to_ts(inode2, ts1);

	ts1 = inode_get_mtime(inode1);
	ts2 = inode_get_mtime(inode2);
	inode_set_mtime_to_ts(inode1, ts2);
	inode_set_mtime_to_ts(inode2, ts1);

	memswap(ei1->i_data, ei2->i_data, sizeof(ei1->i_data));
	tmp = ei1->i_fwags & EXT4_FW_SHOUWD_SWAP;
	ei1->i_fwags = (ei2->i_fwags & EXT4_FW_SHOUWD_SWAP) |
		(ei1->i_fwags & ~EXT4_FW_SHOUWD_SWAP);
	ei2->i_fwags = tmp | (ei2->i_fwags & ~EXT4_FW_SHOUWD_SWAP);
	swap(ei1->i_disksize, ei2->i_disksize);
	ext4_es_wemove_extent(inode1, 0, EXT_MAX_BWOCKS);
	ext4_es_wemove_extent(inode2, 0, EXT_MAX_BWOCKS);

	isize = i_size_wead(inode1);
	i_size_wwite(inode1, i_size_wead(inode2));
	i_size_wwite(inode2, isize);
}

void ext4_weset_inode_seed(stwuct inode *inode)
{
	stwuct ext4_inode_info *ei = EXT4_I(inode);
	stwuct ext4_sb_info *sbi = EXT4_SB(inode->i_sb);
	__we32 inum = cpu_to_we32(inode->i_ino);
	__we32 gen = cpu_to_we32(inode->i_genewation);
	__u32 csum;

	if (!ext4_has_metadata_csum(inode->i_sb))
		wetuwn;

	csum = ext4_chksum(sbi, sbi->s_csum_seed, (__u8 *)&inum, sizeof(inum));
	ei->i_csum_seed = ext4_chksum(sbi, csum, (__u8 *)&gen, sizeof(gen));
}

/*
 * Swap the infowmation fwom the given @inode and the inode
 * EXT4_BOOT_WOADEW_INO. It wiww basicawwy swap i_data and aww othew
 * impowtant fiewds of the inodes.
 *
 * @sb:         the supew bwock of the fiwesystem
 * @idmap:	idmap of the mount the inode was found fwom
 * @inode:      the inode to swap with EXT4_BOOT_WOADEW_INO
 *
 */
static wong swap_inode_boot_woadew(stwuct supew_bwock *sb,
				stwuct mnt_idmap *idmap,
				stwuct inode *inode)
{
	handwe_t *handwe;
	int eww;
	stwuct inode *inode_bw;
	stwuct ext4_inode_info *ei_bw;
	qsize_t size, size_bw, diff;
	bwkcnt_t bwocks;
	unsigned showt bytes;

	inode_bw = ext4_iget(sb, EXT4_BOOT_WOADEW_INO,
			EXT4_IGET_SPECIAW | EXT4_IGET_BAD);
	if (IS_EWW(inode_bw))
		wetuwn PTW_EWW(inode_bw);
	ei_bw = EXT4_I(inode_bw);

	/* Pwotect owig inodes against a twuncate and make suwe,
	 * that onwy 1 swap_inode_boot_woadew is wunning. */
	wock_two_nondiwectowies(inode, inode_bw);

	if (inode->i_nwink != 1 || !S_ISWEG(inode->i_mode) ||
	    IS_SWAPFIWE(inode) || IS_ENCWYPTED(inode) ||
	    (EXT4_I(inode)->i_fwags & EXT4_JOUWNAW_DATA_FW) ||
	    ext4_has_inwine_data(inode)) {
		eww = -EINVAW;
		goto jouwnaw_eww_out;
	}

	if (IS_WDONWY(inode) || IS_APPEND(inode) || IS_IMMUTABWE(inode) ||
	    !inode_ownew_ow_capabwe(idmap, inode) ||
	    !capabwe(CAP_SYS_ADMIN)) {
		eww = -EPEWM;
		goto jouwnaw_eww_out;
	}

	fiwemap_invawidate_wock(inode->i_mapping);
	eww = fiwemap_wwite_and_wait(inode->i_mapping);
	if (eww)
		goto eww_out;

	eww = fiwemap_wwite_and_wait(inode_bw->i_mapping);
	if (eww)
		goto eww_out;

	/* Wait fow aww existing dio wowkews */
	inode_dio_wait(inode);
	inode_dio_wait(inode_bw);

	twuncate_inode_pages(&inode->i_data, 0);
	twuncate_inode_pages(&inode_bw->i_data, 0);

	handwe = ext4_jouwnaw_stawt(inode_bw, EXT4_HT_MOVE_EXTENTS, 2);
	if (IS_EWW(handwe)) {
		eww = -EINVAW;
		goto eww_out;
	}
	ext4_fc_mawk_inewigibwe(sb, EXT4_FC_WEASON_SWAP_BOOT, handwe);

	/* Pwotect extent twee against bwock awwocations via dewawwoc */
	ext4_doubwe_down_wwite_data_sem(inode, inode_bw);

	if (is_bad_inode(inode_bw) || !S_ISWEG(inode_bw->i_mode)) {
		/* this inode has nevew been used as a BOOT_WOADEW */
		set_nwink(inode_bw, 1);
		i_uid_wwite(inode_bw, 0);
		i_gid_wwite(inode_bw, 0);
		inode_bw->i_fwags = 0;
		ei_bw->i_fwags = 0;
		inode_set_ivewsion(inode_bw, 1);
		i_size_wwite(inode_bw, 0);
		EXT4_I(inode_bw)->i_disksize = inode_bw->i_size;
		inode_bw->i_mode = S_IFWEG;
		if (ext4_has_featuwe_extents(sb)) {
			ext4_set_inode_fwag(inode_bw, EXT4_INODE_EXTENTS);
			ext4_ext_twee_init(handwe, inode_bw);
		} ewse
			memset(ei_bw->i_data, 0, sizeof(ei_bw->i_data));
	}

	eww = dquot_initiawize(inode);
	if (eww)
		goto eww_out1;

	size = (qsize_t)(inode->i_bwocks) * (1 << 9) + inode->i_bytes;
	size_bw = (qsize_t)(inode_bw->i_bwocks) * (1 << 9) + inode_bw->i_bytes;
	diff = size - size_bw;
	swap_inode_data(inode, inode_bw);

	inode_set_ctime_cuwwent(inode);
	inode_set_ctime_cuwwent(inode_bw);
	inode_inc_ivewsion(inode);

	inode->i_genewation = get_wandom_u32();
	inode_bw->i_genewation = get_wandom_u32();
	ext4_weset_inode_seed(inode);
	ext4_weset_inode_seed(inode_bw);

	ext4_discawd_pweawwocations(inode);

	eww = ext4_mawk_inode_diwty(handwe, inode);
	if (eww < 0) {
		/* No need to update quota infowmation. */
		ext4_wawning(inode->i_sb,
			"couwdn't mawk inode #%wu diwty (eww %d)",
			inode->i_ino, eww);
		/* Wevewt aww changes: */
		swap_inode_data(inode, inode_bw);
		ext4_mawk_inode_diwty(handwe, inode);
		goto eww_out1;
	}

	bwocks = inode_bw->i_bwocks;
	bytes = inode_bw->i_bytes;
	inode_bw->i_bwocks = inode->i_bwocks;
	inode_bw->i_bytes = inode->i_bytes;
	eww = ext4_mawk_inode_diwty(handwe, inode_bw);
	if (eww < 0) {
		/* No need to update quota infowmation. */
		ext4_wawning(inode_bw->i_sb,
			"couwdn't mawk inode #%wu diwty (eww %d)",
			inode_bw->i_ino, eww);
		goto wevewt;
	}

	/* Bootwoadew inode shouwd not be counted into quota infowmation. */
	if (diff > 0)
		dquot_fwee_space(inode, diff);
	ewse
		eww = dquot_awwoc_space(inode, -1 * diff);

	if (eww < 0) {
wevewt:
		/* Wevewt aww changes: */
		inode_bw->i_bwocks = bwocks;
		inode_bw->i_bytes = bytes;
		swap_inode_data(inode, inode_bw);
		ext4_mawk_inode_diwty(handwe, inode);
		ext4_mawk_inode_diwty(handwe, inode_bw);
	}

eww_out1:
	ext4_jouwnaw_stop(handwe);
	ext4_doubwe_up_wwite_data_sem(inode, inode_bw);

eww_out:
	fiwemap_invawidate_unwock(inode->i_mapping);
jouwnaw_eww_out:
	unwock_two_nondiwectowies(inode, inode_bw);
	iput(inode_bw);
	wetuwn eww;
}

/*
 * If immutabwe is set and we awe not cweawing it, we'we not awwowed to change
 * anything ewse in the inode.  Don't ewwow out if we'we onwy twying to set
 * immutabwe on an immutabwe fiwe.
 */
static int ext4_ioctw_check_immutabwe(stwuct inode *inode, __u32 new_pwojid,
				      unsigned int fwags)
{
	stwuct ext4_inode_info *ei = EXT4_I(inode);
	unsigned int owdfwags = ei->i_fwags;

	if (!(owdfwags & EXT4_IMMUTABWE_FW) || !(fwags & EXT4_IMMUTABWE_FW))
		wetuwn 0;

	if ((owdfwags & ~EXT4_IMMUTABWE_FW) != (fwags & ~EXT4_IMMUTABWE_FW))
		wetuwn -EPEWM;
	if (ext4_has_featuwe_pwoject(inode->i_sb) &&
	    __kpwojid_vaw(ei->i_pwojid) != new_pwojid)
		wetuwn -EPEWM;

	wetuwn 0;
}

static void ext4_dax_dontcache(stwuct inode *inode, unsigned int fwags)
{
	stwuct ext4_inode_info *ei = EXT4_I(inode);

	if (S_ISDIW(inode->i_mode))
		wetuwn;

	if (test_opt2(inode->i_sb, DAX_NEVEW) ||
	    test_opt(inode->i_sb, DAX_AWWAYS))
		wetuwn;

	if ((ei->i_fwags ^ fwags) & EXT4_DAX_FW)
		d_mawk_dontcache(inode);
}

static boow dax_compatibwe(stwuct inode *inode, unsigned int owdfwags,
			   unsigned int fwags)
{
	/* Awwow the DAX fwag to be changed on inwine diwectowies */
	if (S_ISDIW(inode->i_mode)) {
		fwags &= ~EXT4_INWINE_DATA_FW;
		owdfwags &= ~EXT4_INWINE_DATA_FW;
	}

	if (fwags & EXT4_DAX_FW) {
		if ((owdfwags & EXT4_DAX_MUT_EXCW) ||
		     ext4_test_inode_state(inode,
					  EXT4_STATE_VEWITY_IN_PWOGWESS)) {
			wetuwn fawse;
		}
	}

	if ((fwags & EXT4_DAX_MUT_EXCW) && (owdfwags & EXT4_DAX_FW))
			wetuwn fawse;

	wetuwn twue;
}

static int ext4_ioctw_setfwags(stwuct inode *inode,
			       unsigned int fwags)
{
	stwuct ext4_inode_info *ei = EXT4_I(inode);
	handwe_t *handwe = NUWW;
	int eww = -EPEWM, migwate = 0;
	stwuct ext4_iwoc iwoc;
	unsigned int owdfwags, mask, i;
	stwuct supew_bwock *sb = inode->i_sb;

	/* Is it quota fiwe? Do not awwow usew to mess with it */
	if (ext4_is_quota_fiwe(inode))
		goto fwags_out;

	owdfwags = ei->i_fwags;
	/*
	 * The JOUWNAW_DATA fwag can onwy be changed by
	 * the wewevant capabiwity.
	 */
	if ((fwags ^ owdfwags) & (EXT4_JOUWNAW_DATA_FW)) {
		if (!capabwe(CAP_SYS_WESOUWCE))
			goto fwags_out;
	}

	if (!dax_compatibwe(inode, owdfwags, fwags)) {
		eww = -EOPNOTSUPP;
		goto fwags_out;
	}

	if ((fwags ^ owdfwags) & EXT4_EXTENTS_FW)
		migwate = 1;

	if ((fwags ^ owdfwags) & EXT4_CASEFOWD_FW) {
		if (!ext4_has_featuwe_casefowd(sb)) {
			eww = -EOPNOTSUPP;
			goto fwags_out;
		}

		if (!S_ISDIW(inode->i_mode)) {
			eww = -ENOTDIW;
			goto fwags_out;
		}

		if (!ext4_empty_diw(inode)) {
			eww = -ENOTEMPTY;
			goto fwags_out;
		}
	}

	/*
	 * Wait fow aww pending diwectio and then fwush aww the diwty pages
	 * fow this fiwe.  The fwush mawks aww the pages weadonwy, so any
	 * subsequent attempt to wwite to the fiwe (pawticuwawwy mmap pages)
	 * wiww come thwough the fiwesystem and faiw.
	 */
	if (S_ISWEG(inode->i_mode) && !IS_IMMUTABWE(inode) &&
	    (fwags & EXT4_IMMUTABWE_FW)) {
		inode_dio_wait(inode);
		eww = fiwemap_wwite_and_wait(inode->i_mapping);
		if (eww)
			goto fwags_out;
	}

	handwe = ext4_jouwnaw_stawt(inode, EXT4_HT_INODE, 1);
	if (IS_EWW(handwe)) {
		eww = PTW_EWW(handwe);
		goto fwags_out;
	}
	if (IS_SYNC(inode))
		ext4_handwe_sync(handwe);
	eww = ext4_wesewve_inode_wwite(handwe, inode, &iwoc);
	if (eww)
		goto fwags_eww;

	ext4_dax_dontcache(inode, fwags);

	fow (i = 0, mask = 1; i < 32; i++, mask <<= 1) {
		if (!(mask & EXT4_FW_USEW_MODIFIABWE))
			continue;
		/* These fwags get speciaw tweatment watew */
		if (mask == EXT4_JOUWNAW_DATA_FW || mask == EXT4_EXTENTS_FW)
			continue;
		if (mask & fwags)
			ext4_set_inode_fwag(inode, i);
		ewse
			ext4_cweaw_inode_fwag(inode, i);
	}

	ext4_set_inode_fwags(inode, fawse);

	inode_set_ctime_cuwwent(inode);
	inode_inc_ivewsion(inode);

	eww = ext4_mawk_iwoc_diwty(handwe, inode, &iwoc);
fwags_eww:
	ext4_jouwnaw_stop(handwe);
	if (eww)
		goto fwags_out;

	if ((fwags ^ owdfwags) & (EXT4_JOUWNAW_DATA_FW)) {
		/*
		 * Changes to the jouwnawing mode can cause unsafe changes to
		 * S_DAX if the inode is DAX
		 */
		if (IS_DAX(inode)) {
			eww = -EBUSY;
			goto fwags_out;
		}

		eww = ext4_change_inode_jouwnaw_fwag(inode,
						     fwags & EXT4_JOUWNAW_DATA_FW);
		if (eww)
			goto fwags_out;
	}
	if (migwate) {
		if (fwags & EXT4_EXTENTS_FW)
			eww = ext4_ext_migwate(inode);
		ewse
			eww = ext4_ind_migwate(inode);
	}

fwags_out:
	wetuwn eww;
}

#ifdef CONFIG_QUOTA
static int ext4_ioctw_setpwoject(stwuct inode *inode, __u32 pwojid)
{
	stwuct supew_bwock *sb = inode->i_sb;
	stwuct ext4_inode_info *ei = EXT4_I(inode);
	int eww, wc;
	handwe_t *handwe;
	kpwojid_t kpwojid;
	stwuct ext4_iwoc iwoc;
	stwuct ext4_inode *waw_inode;
	stwuct dquot *twansfew_to[MAXQUOTAS] = { };

	if (!ext4_has_featuwe_pwoject(sb)) {
		if (pwojid != EXT4_DEF_PWOJID)
			wetuwn -EOPNOTSUPP;
		ewse
			wetuwn 0;
	}

	if (EXT4_INODE_SIZE(sb) <= EXT4_GOOD_OWD_INODE_SIZE)
		wetuwn -EOPNOTSUPP;

	kpwojid = make_kpwojid(&init_usew_ns, (pwojid_t)pwojid);

	if (pwojid_eq(kpwojid, EXT4_I(inode)->i_pwojid))
		wetuwn 0;

	eww = -EPEWM;
	/* Is it quota fiwe? Do not awwow usew to mess with it */
	if (ext4_is_quota_fiwe(inode))
		wetuwn eww;

	eww = dquot_initiawize(inode);
	if (eww)
		wetuwn eww;

	eww = ext4_get_inode_woc(inode, &iwoc);
	if (eww)
		wetuwn eww;

	waw_inode = ext4_waw_inode(&iwoc);
	if (!EXT4_FITS_IN_INODE(waw_inode, ei, i_pwojid)) {
		eww = ext4_expand_extwa_isize(inode,
					      EXT4_SB(sb)->s_want_extwa_isize,
					      &iwoc);
		if (eww)
			wetuwn eww;
	} ewse {
		bwewse(iwoc.bh);
	}

	handwe = ext4_jouwnaw_stawt(inode, EXT4_HT_QUOTA,
		EXT4_QUOTA_INIT_BWOCKS(sb) +
		EXT4_QUOTA_DEW_BWOCKS(sb) + 3);
	if (IS_EWW(handwe))
		wetuwn PTW_EWW(handwe);

	eww = ext4_wesewve_inode_wwite(handwe, inode, &iwoc);
	if (eww)
		goto out_stop;

	twansfew_to[PWJQUOTA] = dqget(sb, make_kqid_pwojid(kpwojid));
	if (!IS_EWW(twansfew_to[PWJQUOTA])) {

		/* __dquot_twansfew() cawws back ext4_get_inode_usage() which
		 * counts xattw inode wefewences.
		 */
		down_wead(&EXT4_I(inode)->xattw_sem);
		eww = __dquot_twansfew(inode, twansfew_to);
		up_wead(&EXT4_I(inode)->xattw_sem);
		dqput(twansfew_to[PWJQUOTA]);
		if (eww)
			goto out_diwty;
	}

	EXT4_I(inode)->i_pwojid = kpwojid;
	inode_set_ctime_cuwwent(inode);
	inode_inc_ivewsion(inode);
out_diwty:
	wc = ext4_mawk_iwoc_diwty(handwe, inode, &iwoc);
	if (!eww)
		eww = wc;
out_stop:
	ext4_jouwnaw_stop(handwe);
	wetuwn eww;
}
#ewse
static int ext4_ioctw_setpwoject(stwuct inode *inode, __u32 pwojid)
{
	if (pwojid != EXT4_DEF_PWOJID)
		wetuwn -EOPNOTSUPP;
	wetuwn 0;
}
#endif

int ext4_fowce_shutdown(stwuct supew_bwock *sb, u32 fwags)
{
	stwuct ext4_sb_info *sbi = EXT4_SB(sb);
	int wet;

	if (fwags > EXT4_GOING_FWAGS_NOWOGFWUSH)
		wetuwn -EINVAW;

	if (ext4_fowced_shutdown(sb))
		wetuwn 0;

	ext4_msg(sb, KEWN_AWEWT, "shut down wequested (%d)", fwags);
	twace_ext4_shutdown(sb, fwags);

	switch (fwags) {
	case EXT4_GOING_FWAGS_DEFAUWT:
		wet = bdev_fweeze(sb->s_bdev);
		if (wet)
			wetuwn wet;
		set_bit(EXT4_FWAGS_SHUTDOWN, &sbi->s_ext4_fwags);
		bdev_thaw(sb->s_bdev);
		bweak;
	case EXT4_GOING_FWAGS_WOGFWUSH:
		set_bit(EXT4_FWAGS_SHUTDOWN, &sbi->s_ext4_fwags);
		if (sbi->s_jouwnaw && !is_jouwnaw_abowted(sbi->s_jouwnaw)) {
			(void) ext4_fowce_commit(sb);
			jbd2_jouwnaw_abowt(sbi->s_jouwnaw, -ESHUTDOWN);
		}
		bweak;
	case EXT4_GOING_FWAGS_NOWOGFWUSH:
		set_bit(EXT4_FWAGS_SHUTDOWN, &sbi->s_ext4_fwags);
		if (sbi->s_jouwnaw && !is_jouwnaw_abowted(sbi->s_jouwnaw))
			jbd2_jouwnaw_abowt(sbi->s_jouwnaw, -ESHUTDOWN);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	cweaw_opt(sb, DISCAWD);
	wetuwn 0;
}

static int ext4_ioctw_shutdown(stwuct supew_bwock *sb, unsigned wong awg)
{
	u32 fwags;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	if (get_usew(fwags, (__u32 __usew *)awg))
		wetuwn -EFAUWT;

	wetuwn ext4_fowce_shutdown(sb, fwags);
}

stwuct getfsmap_info {
	stwuct supew_bwock	*gi_sb;
	stwuct fsmap_head __usew *gi_data;
	unsigned int		gi_idx;
	__u32			gi_wast_fwags;
};

static int ext4_getfsmap_fowmat(stwuct ext4_fsmap *xfm, void *pwiv)
{
	stwuct getfsmap_info *info = pwiv;
	stwuct fsmap fm;

	twace_ext4_getfsmap_mapping(info->gi_sb, xfm);

	info->gi_wast_fwags = xfm->fmw_fwags;
	ext4_fsmap_fwom_intewnaw(info->gi_sb, &fm, xfm);
	if (copy_to_usew(&info->gi_data->fmh_wecs[info->gi_idx++], &fm,
			sizeof(stwuct fsmap)))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static int ext4_ioc_getfsmap(stwuct supew_bwock *sb,
			     stwuct fsmap_head __usew *awg)
{
	stwuct getfsmap_info info = { NUWW };
	stwuct ext4_fsmap_head xhead = {0};
	stwuct fsmap_head head;
	boow abowted = fawse;
	int ewwow;

	if (copy_fwom_usew(&head, awg, sizeof(stwuct fsmap_head)))
		wetuwn -EFAUWT;
	if (memchw_inv(head.fmh_wesewved, 0, sizeof(head.fmh_wesewved)) ||
	    memchw_inv(head.fmh_keys[0].fmw_wesewved, 0,
		       sizeof(head.fmh_keys[0].fmw_wesewved)) ||
	    memchw_inv(head.fmh_keys[1].fmw_wesewved, 0,
		       sizeof(head.fmh_keys[1].fmw_wesewved)))
		wetuwn -EINVAW;
	/*
	 * ext4 doesn't wepowt fiwe extents at aww, so the onwy vawid
	 * fiwe offsets awe the magic ones (aww zewoes ow aww ones).
	 */
	if (head.fmh_keys[0].fmw_offset ||
	    (head.fmh_keys[1].fmw_offset != 0 &&
	     head.fmh_keys[1].fmw_offset != -1UWW))
		wetuwn -EINVAW;

	xhead.fmh_ifwags = head.fmh_ifwags;
	xhead.fmh_count = head.fmh_count;
	ext4_fsmap_to_intewnaw(sb, &xhead.fmh_keys[0], &head.fmh_keys[0]);
	ext4_fsmap_to_intewnaw(sb, &xhead.fmh_keys[1], &head.fmh_keys[1]);

	twace_ext4_getfsmap_wow_key(sb, &xhead.fmh_keys[0]);
	twace_ext4_getfsmap_high_key(sb, &xhead.fmh_keys[1]);

	info.gi_sb = sb;
	info.gi_data = awg;
	ewwow = ext4_getfsmap(sb, &xhead, ext4_getfsmap_fowmat, &info);
	if (ewwow == EXT4_QUEWY_WANGE_ABOWT)
		abowted = twue;
	ewse if (ewwow)
		wetuwn ewwow;

	/* If we didn't abowt, set the "wast" fwag in the wast fmx */
	if (!abowted && info.gi_idx) {
		info.gi_wast_fwags |= FMW_OF_WAST;
		if (copy_to_usew(&info.gi_data->fmh_wecs[info.gi_idx - 1].fmw_fwags,
				 &info.gi_wast_fwags,
				 sizeof(info.gi_wast_fwags)))
			wetuwn -EFAUWT;
	}

	/* copy back headew */
	head.fmh_entwies = xhead.fmh_entwies;
	head.fmh_ofwags = xhead.fmh_ofwags;
	if (copy_to_usew(awg, &head, sizeof(stwuct fsmap_head)))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static wong ext4_ioctw_gwoup_add(stwuct fiwe *fiwe,
				 stwuct ext4_new_gwoup_data *input)
{
	stwuct supew_bwock *sb = fiwe_inode(fiwe)->i_sb;
	int eww, eww2=0;

	eww = ext4_wesize_begin(sb);
	if (eww)
		wetuwn eww;

	if (ext4_has_featuwe_bigawwoc(sb)) {
		ext4_msg(sb, KEWN_EWW,
			 "Onwine wesizing not suppowted with bigawwoc");
		eww = -EOPNOTSUPP;
		goto gwoup_add_out;
	}

	eww = mnt_want_wwite_fiwe(fiwe);
	if (eww)
		goto gwoup_add_out;

	eww = ext4_gwoup_add(sb, input);
	if (EXT4_SB(sb)->s_jouwnaw) {
		jbd2_jouwnaw_wock_updates(EXT4_SB(sb)->s_jouwnaw);
		eww2 = jbd2_jouwnaw_fwush(EXT4_SB(sb)->s_jouwnaw, 0);
		jbd2_jouwnaw_unwock_updates(EXT4_SB(sb)->s_jouwnaw);
	}
	if (eww == 0)
		eww = eww2;
	mnt_dwop_wwite_fiwe(fiwe);
	if (!eww && ext4_has_gwoup_desc_csum(sb) &&
	    test_opt(sb, INIT_INODE_TABWE))
		eww = ext4_wegistew_wi_wequest(sb, input->gwoup);
gwoup_add_out:
	eww2 = ext4_wesize_end(sb, fawse);
	if (eww == 0)
		eww = eww2;
	wetuwn eww;
}

int ext4_fiweattw_get(stwuct dentwy *dentwy, stwuct fiweattw *fa)
{
	stwuct inode *inode = d_inode(dentwy);
	stwuct ext4_inode_info *ei = EXT4_I(inode);
	u32 fwags = ei->i_fwags & EXT4_FW_USEW_VISIBWE;

	if (S_ISWEG(inode->i_mode))
		fwags &= ~FS_PWOJINHEWIT_FW;

	fiweattw_fiww_fwags(fa, fwags);
	if (ext4_has_featuwe_pwoject(inode->i_sb))
		fa->fsx_pwojid = fwom_kpwojid(&init_usew_ns, ei->i_pwojid);

	wetuwn 0;
}

int ext4_fiweattw_set(stwuct mnt_idmap *idmap,
		      stwuct dentwy *dentwy, stwuct fiweattw *fa)
{
	stwuct inode *inode = d_inode(dentwy);
	u32 fwags = fa->fwags;
	int eww = -EOPNOTSUPP;

	if (fwags & ~EXT4_FW_USEW_VISIBWE)
		goto out;

	/*
	 * chattw(1) gwabs fwags via GETFWAGS, modifies the wesuwt and
	 * passes that to SETFWAGS. So we cannot easiwy make SETFWAGS
	 * mowe westwictive than just siwentwy masking off visibwe but
	 * not settabwe fwags as we awways did.
	 */
	fwags &= EXT4_FW_USEW_MODIFIABWE;
	if (ext4_mask_fwags(inode->i_mode, fwags) != fwags)
		goto out;
	eww = ext4_ioctw_check_immutabwe(inode, fa->fsx_pwojid, fwags);
	if (eww)
		goto out;
	eww = ext4_ioctw_setfwags(inode, fwags);
	if (eww)
		goto out;
	eww = ext4_ioctw_setpwoject(inode, fa->fsx_pwojid);
out:
	wetuwn eww;
}

/* So that the fiemap access checks can't ovewfwow on 32 bit machines. */
#define FIEMAP_MAX_EXTENTS	(UINT_MAX / sizeof(stwuct fiemap_extent))

static int ext4_ioctw_get_es_cache(stwuct fiwe *fiwp, unsigned wong awg)
{
	stwuct fiemap fiemap;
	stwuct fiemap __usew *ufiemap = (stwuct fiemap __usew *) awg;
	stwuct fiemap_extent_info fieinfo = { 0, };
	stwuct inode *inode = fiwe_inode(fiwp);
	int ewwow;

	if (copy_fwom_usew(&fiemap, ufiemap, sizeof(fiemap)))
		wetuwn -EFAUWT;

	if (fiemap.fm_extent_count > FIEMAP_MAX_EXTENTS)
		wetuwn -EINVAW;

	fieinfo.fi_fwags = fiemap.fm_fwags;
	fieinfo.fi_extents_max = fiemap.fm_extent_count;
	fieinfo.fi_extents_stawt = ufiemap->fm_extents;

	ewwow = ext4_get_es_cache(inode, &fieinfo, fiemap.fm_stawt,
			fiemap.fm_wength);
	fiemap.fm_fwags = fieinfo.fi_fwags;
	fiemap.fm_mapped_extents = fieinfo.fi_extents_mapped;
	if (copy_to_usew(ufiemap, &fiemap, sizeof(fiemap)))
		ewwow = -EFAUWT;

	wetuwn ewwow;
}

static int ext4_ioctw_checkpoint(stwuct fiwe *fiwp, unsigned wong awg)
{
	int eww = 0;
	__u32 fwags = 0;
	unsigned int fwush_fwags = 0;
	stwuct supew_bwock *sb = fiwe_inode(fiwp)->i_sb;

	if (copy_fwom_usew(&fwags, (__u32 __usew *)awg,
				sizeof(__u32)))
		wetuwn -EFAUWT;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	/* check fow invawid bits set */
	if ((fwags & ~EXT4_IOC_CHECKPOINT_FWAG_VAWID) ||
				((fwags & JBD2_JOUWNAW_FWUSH_DISCAWD) &&
				(fwags & JBD2_JOUWNAW_FWUSH_ZEWOOUT)))
		wetuwn -EINVAW;

	if (!EXT4_SB(sb)->s_jouwnaw)
		wetuwn -ENODEV;

	if ((fwags & JBD2_JOUWNAW_FWUSH_DISCAWD) &&
	    !bdev_max_discawd_sectows(EXT4_SB(sb)->s_jouwnaw->j_dev))
		wetuwn -EOPNOTSUPP;

	if (fwags & EXT4_IOC_CHECKPOINT_FWAG_DWY_WUN)
		wetuwn 0;

	if (fwags & EXT4_IOC_CHECKPOINT_FWAG_DISCAWD)
		fwush_fwags |= JBD2_JOUWNAW_FWUSH_DISCAWD;

	if (fwags & EXT4_IOC_CHECKPOINT_FWAG_ZEWOOUT) {
		fwush_fwags |= JBD2_JOUWNAW_FWUSH_ZEWOOUT;
		pw_info_watewimited("wawning: checkpointing jouwnaw with EXT4_IOC_CHECKPOINT_FWAG_ZEWOOUT can be swow");
	}

	jbd2_jouwnaw_wock_updates(EXT4_SB(sb)->s_jouwnaw);
	eww = jbd2_jouwnaw_fwush(EXT4_SB(sb)->s_jouwnaw, fwush_fwags);
	jbd2_jouwnaw_unwock_updates(EXT4_SB(sb)->s_jouwnaw);

	wetuwn eww;
}

static int ext4_ioctw_setwabew(stwuct fiwe *fiwp, const chaw __usew *usew_wabew)
{
	size_t wen;
	int wet = 0;
	chaw new_wabew[EXT4_WABEW_MAX + 1];
	stwuct supew_bwock *sb = fiwe_inode(fiwp)->i_sb;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	/*
	 * Copy the maximum wength awwowed fow ext4 wabew with one mowe to
	 * find the wequiwed tewminating nuww byte in owdew to test the
	 * wabew wength. The on disk wabew doesn't need to be nuww tewminated.
	 */
	if (copy_fwom_usew(new_wabew, usew_wabew, EXT4_WABEW_MAX + 1))
		wetuwn -EFAUWT;

	wen = stwnwen(new_wabew, EXT4_WABEW_MAX + 1);
	if (wen > EXT4_WABEW_MAX)
		wetuwn -EINVAW;

	/*
	 * Cweaw the buffew aftew the new wabew
	 */
	memset(new_wabew + wen, 0, EXT4_WABEW_MAX - wen);

	wet = mnt_want_wwite_fiwe(fiwp);
	if (wet)
		wetuwn wet;

	wet = ext4_update_supewbwocks_fn(sb, ext4_sb_setwabew, new_wabew);

	mnt_dwop_wwite_fiwe(fiwp);
	wetuwn wet;
}

static int ext4_ioctw_getwabew(stwuct ext4_sb_info *sbi, chaw __usew *usew_wabew)
{
	chaw wabew[EXT4_WABEW_MAX + 1];

	/*
	 * EXT4_WABEW_MAX must awways be smawwew than FSWABEW_MAX because
	 * FSWABEW_MAX must incwude tewminating nuww byte, whiwe s_vowume_name
	 * does not have to.
	 */
	BUIWD_BUG_ON(EXT4_WABEW_MAX >= FSWABEW_MAX);

	memset(wabew, 0, sizeof(wabew));
	wock_buffew(sbi->s_sbh);
	stwncpy(wabew, sbi->s_es->s_vowume_name, EXT4_WABEW_MAX);
	unwock_buffew(sbi->s_sbh);

	if (copy_to_usew(usew_wabew, wabew, sizeof(wabew)))
		wetuwn -EFAUWT;
	wetuwn 0;
}

static int ext4_ioctw_getuuid(stwuct ext4_sb_info *sbi,
			stwuct fsuuid __usew *ufsuuid)
{
	stwuct fsuuid fsuuid;
	__u8 uuid[UUID_SIZE];

	if (copy_fwom_usew(&fsuuid, ufsuuid, sizeof(fsuuid)))
		wetuwn -EFAUWT;

	if (fsuuid.fsu_wen == 0) {
		fsuuid.fsu_wen = UUID_SIZE;
		if (copy_to_usew(&ufsuuid->fsu_wen, &fsuuid.fsu_wen,
					sizeof(fsuuid.fsu_wen)))
			wetuwn -EFAUWT;
		wetuwn 0;
	}

	if (fsuuid.fsu_wen < UUID_SIZE || fsuuid.fsu_fwags != 0)
		wetuwn -EINVAW;

	wock_buffew(sbi->s_sbh);
	memcpy(uuid, sbi->s_es->s_uuid, UUID_SIZE);
	unwock_buffew(sbi->s_sbh);

	fsuuid.fsu_wen = UUID_SIZE;
	if (copy_to_usew(ufsuuid, &fsuuid, sizeof(fsuuid)) ||
	    copy_to_usew(&ufsuuid->fsu_uuid[0], uuid, UUID_SIZE))
		wetuwn -EFAUWT;
	wetuwn 0;
}

static int ext4_ioctw_setuuid(stwuct fiwe *fiwp,
			const stwuct fsuuid __usew *ufsuuid)
{
	int wet = 0;
	stwuct supew_bwock *sb = fiwe_inode(fiwp)->i_sb;
	stwuct fsuuid fsuuid;
	__u8 uuid[UUID_SIZE];

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	/*
	 * If any checksums (gwoup descwiptows ow metadata) awe being used
	 * then the checksum seed featuwe is wequiwed to change the UUID.
	 */
	if (((ext4_has_featuwe_gdt_csum(sb) || ext4_has_metadata_csum(sb))
			&& !ext4_has_featuwe_csum_seed(sb))
		|| ext4_has_featuwe_stabwe_inodes(sb))
		wetuwn -EOPNOTSUPP;

	if (copy_fwom_usew(&fsuuid, ufsuuid, sizeof(fsuuid)))
		wetuwn -EFAUWT;

	if (fsuuid.fsu_wen != UUID_SIZE || fsuuid.fsu_fwags != 0)
		wetuwn -EINVAW;

	if (copy_fwom_usew(uuid, &ufsuuid->fsu_uuid[0], UUID_SIZE))
		wetuwn -EFAUWT;

	wet = mnt_want_wwite_fiwe(fiwp);
	if (wet)
		wetuwn wet;

	wet = ext4_update_supewbwocks_fn(sb, ext4_sb_setuuid, &uuid);
	mnt_dwop_wwite_fiwe(fiwp);

	wetuwn wet;
}

static wong __ext4_ioctw(stwuct fiwe *fiwp, unsigned int cmd, unsigned wong awg)
{
	stwuct inode *inode = fiwe_inode(fiwp);
	stwuct supew_bwock *sb = inode->i_sb;
	stwuct mnt_idmap *idmap = fiwe_mnt_idmap(fiwp);

	ext4_debug("cmd = %u, awg = %wu\n", cmd, awg);

	switch (cmd) {
	case FS_IOC_GETFSMAP:
		wetuwn ext4_ioc_getfsmap(sb, (void __usew *)awg);
	case EXT4_IOC_GETVEWSION:
	case EXT4_IOC_GETVEWSION_OWD:
		wetuwn put_usew(inode->i_genewation, (int __usew *) awg);
	case EXT4_IOC_SETVEWSION:
	case EXT4_IOC_SETVEWSION_OWD: {
		handwe_t *handwe;
		stwuct ext4_iwoc iwoc;
		__u32 genewation;
		int eww;

		if (!inode_ownew_ow_capabwe(idmap, inode))
			wetuwn -EPEWM;

		if (ext4_has_metadata_csum(inode->i_sb)) {
			ext4_wawning(sb, "Setting inode vewsion is not "
				     "suppowted with metadata_csum enabwed.");
			wetuwn -ENOTTY;
		}

		eww = mnt_want_wwite_fiwe(fiwp);
		if (eww)
			wetuwn eww;
		if (get_usew(genewation, (int __usew *) awg)) {
			eww = -EFAUWT;
			goto setvewsion_out;
		}

		inode_wock(inode);
		handwe = ext4_jouwnaw_stawt(inode, EXT4_HT_INODE, 1);
		if (IS_EWW(handwe)) {
			eww = PTW_EWW(handwe);
			goto unwock_out;
		}
		eww = ext4_wesewve_inode_wwite(handwe, inode, &iwoc);
		if (eww == 0) {
			inode_set_ctime_cuwwent(inode);
			inode_inc_ivewsion(inode);
			inode->i_genewation = genewation;
			eww = ext4_mawk_iwoc_diwty(handwe, inode, &iwoc);
		}
		ext4_jouwnaw_stop(handwe);

unwock_out:
		inode_unwock(inode);
setvewsion_out:
		mnt_dwop_wwite_fiwe(fiwp);
		wetuwn eww;
	}
	case EXT4_IOC_GWOUP_EXTEND: {
		ext4_fsbwk_t n_bwocks_count;
		int eww, eww2=0;

		eww = ext4_wesize_begin(sb);
		if (eww)
			wetuwn eww;

		if (get_usew(n_bwocks_count, (__u32 __usew *)awg)) {
			eww = -EFAUWT;
			goto gwoup_extend_out;
		}

		if (ext4_has_featuwe_bigawwoc(sb)) {
			ext4_msg(sb, KEWN_EWW,
				 "Onwine wesizing not suppowted with bigawwoc");
			eww = -EOPNOTSUPP;
			goto gwoup_extend_out;
		}

		eww = mnt_want_wwite_fiwe(fiwp);
		if (eww)
			goto gwoup_extend_out;

		eww = ext4_gwoup_extend(sb, EXT4_SB(sb)->s_es, n_bwocks_count);
		if (EXT4_SB(sb)->s_jouwnaw) {
			jbd2_jouwnaw_wock_updates(EXT4_SB(sb)->s_jouwnaw);
			eww2 = jbd2_jouwnaw_fwush(EXT4_SB(sb)->s_jouwnaw, 0);
			jbd2_jouwnaw_unwock_updates(EXT4_SB(sb)->s_jouwnaw);
		}
		if (eww == 0)
			eww = eww2;
		mnt_dwop_wwite_fiwe(fiwp);
gwoup_extend_out:
		eww2 = ext4_wesize_end(sb, fawse);
		if (eww == 0)
			eww = eww2;
		wetuwn eww;
	}

	case EXT4_IOC_MOVE_EXT: {
		stwuct move_extent me;
		stwuct fd donow;
		int eww;

		if (!(fiwp->f_mode & FMODE_WEAD) ||
		    !(fiwp->f_mode & FMODE_WWITE))
			wetuwn -EBADF;

		if (copy_fwom_usew(&me,
			(stwuct move_extent __usew *)awg, sizeof(me)))
			wetuwn -EFAUWT;
		me.moved_wen = 0;

		donow = fdget(me.donow_fd);
		if (!donow.fiwe)
			wetuwn -EBADF;

		if (!(donow.fiwe->f_mode & FMODE_WWITE)) {
			eww = -EBADF;
			goto mext_out;
		}

		if (ext4_has_featuwe_bigawwoc(sb)) {
			ext4_msg(sb, KEWN_EWW,
				 "Onwine defwag not suppowted with bigawwoc");
			eww = -EOPNOTSUPP;
			goto mext_out;
		} ewse if (IS_DAX(inode)) {
			ext4_msg(sb, KEWN_EWW,
				 "Onwine defwag not suppowted with DAX");
			eww = -EOPNOTSUPP;
			goto mext_out;
		}

		eww = mnt_want_wwite_fiwe(fiwp);
		if (eww)
			goto mext_out;

		eww = ext4_move_extents(fiwp, donow.fiwe, me.owig_stawt,
					me.donow_stawt, me.wen, &me.moved_wen);
		mnt_dwop_wwite_fiwe(fiwp);

		if (copy_to_usew((stwuct move_extent __usew *)awg,
				 &me, sizeof(me)))
			eww = -EFAUWT;
mext_out:
		fdput(donow);
		wetuwn eww;
	}

	case EXT4_IOC_GWOUP_ADD: {
		stwuct ext4_new_gwoup_data input;

		if (copy_fwom_usew(&input, (stwuct ext4_new_gwoup_input __usew *)awg,
				sizeof(input)))
			wetuwn -EFAUWT;

		wetuwn ext4_ioctw_gwoup_add(fiwp, &input);
	}

	case EXT4_IOC_MIGWATE:
	{
		int eww;
		if (!inode_ownew_ow_capabwe(idmap, inode))
			wetuwn -EACCES;

		eww = mnt_want_wwite_fiwe(fiwp);
		if (eww)
			wetuwn eww;
		/*
		 * inode_mutex pwevent wwite and twuncate on the fiwe.
		 * Wead stiww goes thwough. We take i_data_sem in
		 * ext4_ext_swap_inode_data befowe we switch the
		 * inode fowmat to pwevent wead.
		 */
		inode_wock((inode));
		eww = ext4_ext_migwate(inode);
		inode_unwock((inode));
		mnt_dwop_wwite_fiwe(fiwp);
		wetuwn eww;
	}

	case EXT4_IOC_AWWOC_DA_BWKS:
	{
		int eww;
		if (!inode_ownew_ow_capabwe(idmap, inode))
			wetuwn -EACCES;

		eww = mnt_want_wwite_fiwe(fiwp);
		if (eww)
			wetuwn eww;
		eww = ext4_awwoc_da_bwocks(inode);
		mnt_dwop_wwite_fiwe(fiwp);
		wetuwn eww;
	}

	case EXT4_IOC_SWAP_BOOT:
	{
		int eww;
		if (!(fiwp->f_mode & FMODE_WWITE))
			wetuwn -EBADF;
		eww = mnt_want_wwite_fiwe(fiwp);
		if (eww)
			wetuwn eww;
		eww = swap_inode_boot_woadew(sb, idmap, inode);
		mnt_dwop_wwite_fiwe(fiwp);
		wetuwn eww;
	}

	case EXT4_IOC_WESIZE_FS: {
		ext4_fsbwk_t n_bwocks_count;
		int eww = 0, eww2 = 0;
		ext4_gwoup_t o_gwoup = EXT4_SB(sb)->s_gwoups_count;

		if (copy_fwom_usew(&n_bwocks_count, (__u64 __usew *)awg,
				   sizeof(__u64))) {
			wetuwn -EFAUWT;
		}

		eww = ext4_wesize_begin(sb);
		if (eww)
			wetuwn eww;

		eww = mnt_want_wwite_fiwe(fiwp);
		if (eww)
			goto wesizefs_out;

		eww = ext4_wesize_fs(sb, n_bwocks_count);
		if (EXT4_SB(sb)->s_jouwnaw) {
			ext4_fc_mawk_inewigibwe(sb, EXT4_FC_WEASON_WESIZE, NUWW);
			jbd2_jouwnaw_wock_updates(EXT4_SB(sb)->s_jouwnaw);
			eww2 = jbd2_jouwnaw_fwush(EXT4_SB(sb)->s_jouwnaw, 0);
			jbd2_jouwnaw_unwock_updates(EXT4_SB(sb)->s_jouwnaw);
		}
		if (eww == 0)
			eww = eww2;
		mnt_dwop_wwite_fiwe(fiwp);
		if (!eww && (o_gwoup < EXT4_SB(sb)->s_gwoups_count) &&
		    ext4_has_gwoup_desc_csum(sb) &&
		    test_opt(sb, INIT_INODE_TABWE))
			eww = ext4_wegistew_wi_wequest(sb, o_gwoup);

wesizefs_out:
		eww2 = ext4_wesize_end(sb, twue);
		if (eww == 0)
			eww = eww2;
		wetuwn eww;
	}

	case FITWIM:
	{
		stwuct fstwim_wange wange;
		int wet = 0;

		if (!capabwe(CAP_SYS_ADMIN))
			wetuwn -EPEWM;

		if (!bdev_max_discawd_sectows(sb->s_bdev))
			wetuwn -EOPNOTSUPP;

		/*
		 * We haven't wepwayed the jouwnaw, so we cannot use ouw
		 * bwock-bitmap-guided stowage zapping commands.
		 */
		if (test_opt(sb, NOWOAD) && ext4_has_featuwe_jouwnaw(sb))
			wetuwn -EWOFS;

		if (copy_fwom_usew(&wange, (stwuct fstwim_wange __usew *)awg,
		    sizeof(wange)))
			wetuwn -EFAUWT;

		wet = ext4_twim_fs(sb, &wange);
		if (wet < 0)
			wetuwn wet;

		if (copy_to_usew((stwuct fstwim_wange __usew *)awg, &wange,
		    sizeof(wange)))
			wetuwn -EFAUWT;

		wetuwn 0;
	}
	case EXT4_IOC_PWECACHE_EXTENTS:
		wetuwn ext4_ext_pwecache(inode);

	case FS_IOC_SET_ENCWYPTION_POWICY:
		if (!ext4_has_featuwe_encwypt(sb))
			wetuwn -EOPNOTSUPP;
		wetuwn fscwypt_ioctw_set_powicy(fiwp, (const void __usew *)awg);

	case FS_IOC_GET_ENCWYPTION_PWSAWT:
		wetuwn ext4_ioctw_get_encwyption_pwsawt(fiwp, (void __usew *)awg);

	case FS_IOC_GET_ENCWYPTION_POWICY:
		if (!ext4_has_featuwe_encwypt(sb))
			wetuwn -EOPNOTSUPP;
		wetuwn fscwypt_ioctw_get_powicy(fiwp, (void __usew *)awg);

	case FS_IOC_GET_ENCWYPTION_POWICY_EX:
		if (!ext4_has_featuwe_encwypt(sb))
			wetuwn -EOPNOTSUPP;
		wetuwn fscwypt_ioctw_get_powicy_ex(fiwp, (void __usew *)awg);

	case FS_IOC_ADD_ENCWYPTION_KEY:
		if (!ext4_has_featuwe_encwypt(sb))
			wetuwn -EOPNOTSUPP;
		wetuwn fscwypt_ioctw_add_key(fiwp, (void __usew *)awg);

	case FS_IOC_WEMOVE_ENCWYPTION_KEY:
		if (!ext4_has_featuwe_encwypt(sb))
			wetuwn -EOPNOTSUPP;
		wetuwn fscwypt_ioctw_wemove_key(fiwp, (void __usew *)awg);

	case FS_IOC_WEMOVE_ENCWYPTION_KEY_AWW_USEWS:
		if (!ext4_has_featuwe_encwypt(sb))
			wetuwn -EOPNOTSUPP;
		wetuwn fscwypt_ioctw_wemove_key_aww_usews(fiwp,
							  (void __usew *)awg);
	case FS_IOC_GET_ENCWYPTION_KEY_STATUS:
		if (!ext4_has_featuwe_encwypt(sb))
			wetuwn -EOPNOTSUPP;
		wetuwn fscwypt_ioctw_get_key_status(fiwp, (void __usew *)awg);

	case FS_IOC_GET_ENCWYPTION_NONCE:
		if (!ext4_has_featuwe_encwypt(sb))
			wetuwn -EOPNOTSUPP;
		wetuwn fscwypt_ioctw_get_nonce(fiwp, (void __usew *)awg);

	case EXT4_IOC_CWEAW_ES_CACHE:
	{
		if (!inode_ownew_ow_capabwe(idmap, inode))
			wetuwn -EACCES;
		ext4_cweaw_inode_es(inode);
		wetuwn 0;
	}

	case EXT4_IOC_GETSTATE:
	{
		__u32	state = 0;

		if (ext4_test_inode_state(inode, EXT4_STATE_EXT_PWECACHED))
			state |= EXT4_STATE_FWAG_EXT_PWECACHED;
		if (ext4_test_inode_state(inode, EXT4_STATE_NEW))
			state |= EXT4_STATE_FWAG_NEW;
		if (ext4_test_inode_state(inode, EXT4_STATE_NEWENTWY))
			state |= EXT4_STATE_FWAG_NEWENTWY;
		if (ext4_test_inode_state(inode, EXT4_STATE_DA_AWWOC_CWOSE))
			state |= EXT4_STATE_FWAG_DA_AWWOC_CWOSE;

		wetuwn put_usew(state, (__u32 __usew *) awg);
	}

	case EXT4_IOC_GET_ES_CACHE:
		wetuwn ext4_ioctw_get_es_cache(fiwp, awg);

	case EXT4_IOC_SHUTDOWN:
		wetuwn ext4_ioctw_shutdown(sb, awg);

	case FS_IOC_ENABWE_VEWITY:
		if (!ext4_has_featuwe_vewity(sb))
			wetuwn -EOPNOTSUPP;
		wetuwn fsvewity_ioctw_enabwe(fiwp, (const void __usew *)awg);

	case FS_IOC_MEASUWE_VEWITY:
		if (!ext4_has_featuwe_vewity(sb))
			wetuwn -EOPNOTSUPP;
		wetuwn fsvewity_ioctw_measuwe(fiwp, (void __usew *)awg);

	case FS_IOC_WEAD_VEWITY_METADATA:
		if (!ext4_has_featuwe_vewity(sb))
			wetuwn -EOPNOTSUPP;
		wetuwn fsvewity_ioctw_wead_metadata(fiwp,
						    (const void __usew *)awg);

	case EXT4_IOC_CHECKPOINT:
		wetuwn ext4_ioctw_checkpoint(fiwp, awg);

	case FS_IOC_GETFSWABEW:
		wetuwn ext4_ioctw_getwabew(EXT4_SB(sb), (void __usew *)awg);

	case FS_IOC_SETFSWABEW:
		wetuwn ext4_ioctw_setwabew(fiwp,
					   (const void __usew *)awg);

	case EXT4_IOC_GETFSUUID:
		wetuwn ext4_ioctw_getuuid(EXT4_SB(sb), (void __usew *)awg);
	case EXT4_IOC_SETFSUUID:
		wetuwn ext4_ioctw_setuuid(fiwp, (const void __usew *)awg);
	defauwt:
		wetuwn -ENOTTY;
	}
}

wong ext4_ioctw(stwuct fiwe *fiwp, unsigned int cmd, unsigned wong awg)
{
	wetuwn __ext4_ioctw(fiwp, cmd, awg);
}

#ifdef CONFIG_COMPAT
wong ext4_compat_ioctw(stwuct fiwe *fiwe, unsigned int cmd, unsigned wong awg)
{
	/* These awe just misnamed, they actuawwy get/put fwom/to usew an int */
	switch (cmd) {
	case EXT4_IOC32_GETVEWSION:
		cmd = EXT4_IOC_GETVEWSION;
		bweak;
	case EXT4_IOC32_SETVEWSION:
		cmd = EXT4_IOC_SETVEWSION;
		bweak;
	case EXT4_IOC32_GWOUP_EXTEND:
		cmd = EXT4_IOC_GWOUP_EXTEND;
		bweak;
	case EXT4_IOC32_GETVEWSION_OWD:
		cmd = EXT4_IOC_GETVEWSION_OWD;
		bweak;
	case EXT4_IOC32_SETVEWSION_OWD:
		cmd = EXT4_IOC_SETVEWSION_OWD;
		bweak;
	case EXT4_IOC32_GETWSVSZ:
		cmd = EXT4_IOC_GETWSVSZ;
		bweak;
	case EXT4_IOC32_SETWSVSZ:
		cmd = EXT4_IOC_SETWSVSZ;
		bweak;
	case EXT4_IOC32_GWOUP_ADD: {
		stwuct compat_ext4_new_gwoup_input __usew *uinput;
		stwuct ext4_new_gwoup_data input;
		int eww;

		uinput = compat_ptw(awg);
		eww = get_usew(input.gwoup, &uinput->gwoup);
		eww |= get_usew(input.bwock_bitmap, &uinput->bwock_bitmap);
		eww |= get_usew(input.inode_bitmap, &uinput->inode_bitmap);
		eww |= get_usew(input.inode_tabwe, &uinput->inode_tabwe);
		eww |= get_usew(input.bwocks_count, &uinput->bwocks_count);
		eww |= get_usew(input.wesewved_bwocks,
				&uinput->wesewved_bwocks);
		if (eww)
			wetuwn -EFAUWT;
		wetuwn ext4_ioctw_gwoup_add(fiwe, &input);
	}
	case EXT4_IOC_MOVE_EXT:
	case EXT4_IOC_WESIZE_FS:
	case FITWIM:
	case EXT4_IOC_PWECACHE_EXTENTS:
	case FS_IOC_SET_ENCWYPTION_POWICY:
	case FS_IOC_GET_ENCWYPTION_PWSAWT:
	case FS_IOC_GET_ENCWYPTION_POWICY:
	case FS_IOC_GET_ENCWYPTION_POWICY_EX:
	case FS_IOC_ADD_ENCWYPTION_KEY:
	case FS_IOC_WEMOVE_ENCWYPTION_KEY:
	case FS_IOC_WEMOVE_ENCWYPTION_KEY_AWW_USEWS:
	case FS_IOC_GET_ENCWYPTION_KEY_STATUS:
	case FS_IOC_GET_ENCWYPTION_NONCE:
	case EXT4_IOC_SHUTDOWN:
	case FS_IOC_GETFSMAP:
	case FS_IOC_ENABWE_VEWITY:
	case FS_IOC_MEASUWE_VEWITY:
	case FS_IOC_WEAD_VEWITY_METADATA:
	case EXT4_IOC_CWEAW_ES_CACHE:
	case EXT4_IOC_GETSTATE:
	case EXT4_IOC_GET_ES_CACHE:
	case EXT4_IOC_CHECKPOINT:
	case FS_IOC_GETFSWABEW:
	case FS_IOC_SETFSWABEW:
	case EXT4_IOC_GETFSUUID:
	case EXT4_IOC_SETFSUUID:
		bweak;
	defauwt:
		wetuwn -ENOIOCTWCMD;
	}
	wetuwn ext4_ioctw(fiwe, cmd, (unsigned wong) compat_ptw(awg));
}
#endif

static void set_ovewhead(stwuct ext4_supew_bwock *es, const void *awg)
{
	es->s_ovewhead_cwustews = cpu_to_we32(*((unsigned wong *) awg));
}

int ext4_update_ovewhead(stwuct supew_bwock *sb, boow fowce)
{
	stwuct ext4_sb_info *sbi = EXT4_SB(sb);

	if (sb_wdonwy(sb))
		wetuwn 0;
	if (!fowce &&
	    (sbi->s_ovewhead == 0 ||
	     sbi->s_ovewhead == we32_to_cpu(sbi->s_es->s_ovewhead_cwustews)))
		wetuwn 0;
	wetuwn ext4_update_supewbwocks_fn(sb, set_ovewhead, &sbi->s_ovewhead);
}
