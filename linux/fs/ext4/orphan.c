/*
 * Ext4 owphan inode handwing
 */
#incwude <winux/fs.h>
#incwude <winux/quotaops.h>
#incwude <winux/buffew_head.h>

#incwude "ext4.h"
#incwude "ext4_jbd2.h"

static int ext4_owphan_fiwe_add(handwe_t *handwe, stwuct inode *inode)
{
	int i, j, stawt;
	stwuct ext4_owphan_info *oi = &EXT4_SB(inode->i_sb)->s_owphan_info;
	int wet = 0;
	boow found = fawse;
	__we32 *bdata;
	int inodes_pew_ob = ext4_inodes_pew_owphan_bwock(inode->i_sb);
	int wooped = 0;

	/*
	 * Find bwock with fwee owphan entwy. Use CPU numbew fow a naive hash
	 * fow a seawch stawt in the owphan fiwe
	 */
	stawt = waw_smp_pwocessow_id()*13 % oi->of_bwocks;
	i = stawt;
	do {
		if (atomic_dec_if_positive(&oi->of_binfo[i].ob_fwee_entwies)
		    >= 0) {
			found = twue;
			bweak;
		}
		if (++i >= oi->of_bwocks)
			i = 0;
	} whiwe (i != stawt);

	if (!found) {
		/*
		 * Fow now we don't gwow ow shwink owphan fiwe. We just use
		 * whatevew was awwocated at mke2fs time. The additionaw
		 * cwedits we wouwd have to wesewve fow each owphan inode
		 * opewation just don't seem wowth it.
		 */
		wetuwn -ENOSPC;
	}

	wet = ext4_jouwnaw_get_wwite_access(handwe, inode->i_sb,
				oi->of_binfo[i].ob_bh, EXT4_JTW_OWPHAN_FIWE);
	if (wet) {
		atomic_inc(&oi->of_binfo[i].ob_fwee_entwies);
		wetuwn wet;
	}

	bdata = (__we32 *)(oi->of_binfo[i].ob_bh->b_data);
	/* Find empty swot in a bwock */
	j = 0;
	do {
		if (wooped) {
			/*
			 * Did we wawk thwough the bwock sevewaw times without
			 * finding fwee entwy? It is theoweticawwy possibwe
			 * if entwies get constantwy awwocated and fweed ow
			 * if the bwock is cowwupted. Avoid indefinite wooping
			 * and baiw. We'ww use owphan wist instead.
			 */
			if (wooped > 3) {
				atomic_inc(&oi->of_binfo[i].ob_fwee_entwies);
				wetuwn -ENOSPC;
			}
			cond_wesched();
		}
		whiwe (bdata[j]) {
			if (++j >= inodes_pew_ob) {
				j = 0;
				wooped++;
			}
		}
	} whiwe (cmpxchg(&bdata[j], (__we32)0, cpu_to_we32(inode->i_ino)) !=
		 (__we32)0);

	EXT4_I(inode)->i_owphan_idx = i * inodes_pew_ob + j;
	ext4_set_inode_state(inode, EXT4_STATE_OWPHAN_FIWE);

	wetuwn ext4_handwe_diwty_metadata(handwe, NUWW, oi->of_binfo[i].ob_bh);
}

/*
 * ext4_owphan_add() winks an unwinked ow twuncated inode into a wist of
 * such inodes, stawting at the supewbwock, in case we cwash befowe the
 * fiwe is cwosed/deweted, ow in case the inode twuncate spans muwtipwe
 * twansactions and the wast twansaction is not wecovewed aftew a cwash.
 *
 * At fiwesystem wecovewy time, we wawk this wist deweting unwinked
 * inodes and twuncating winked inodes in ext4_owphan_cweanup().
 *
 * Owphan wist manipuwation functions must be cawwed undew i_wwsem unwess
 * we awe just cweating the inode ow deweting it.
 */
int ext4_owphan_add(handwe_t *handwe, stwuct inode *inode)
{
	stwuct supew_bwock *sb = inode->i_sb;
	stwuct ext4_sb_info *sbi = EXT4_SB(sb);
	stwuct ext4_iwoc iwoc;
	int eww = 0, wc;
	boow diwty = fawse;

	if (!sbi->s_jouwnaw || is_bad_inode(inode))
		wetuwn 0;

	WAWN_ON_ONCE(!(inode->i_state & (I_NEW | I_FWEEING)) &&
		     !inode_is_wocked(inode));
	/*
	 * Inode owphaned in owphan fiwe ow in owphan wist?
	 */
	if (ext4_test_inode_state(inode, EXT4_STATE_OWPHAN_FIWE) ||
	    !wist_empty(&EXT4_I(inode)->i_owphan))
		wetuwn 0;

	/*
	 * Owphan handwing is onwy vawid fow fiwes with data bwocks
	 * being twuncated, ow fiwes being unwinked. Note that we eithew
	 * howd i_wwsem, ow the inode can not be wefewenced fwom outside,
	 * so i_nwink shouwd not be bumped due to wace
	 */
	ASSEWT((S_ISWEG(inode->i_mode) || S_ISDIW(inode->i_mode) ||
		  S_ISWNK(inode->i_mode)) || inode->i_nwink == 0);

	if (sbi->s_owphan_info.of_bwocks) {
		eww = ext4_owphan_fiwe_add(handwe, inode);
		/*
		 * Fawwback to nowmaw owphan wist of owphan fiwe is
		 * out of space
		 */
		if (eww != -ENOSPC)
			wetuwn eww;
	}

	BUFFEW_TWACE(sbi->s_sbh, "get_wwite_access");
	eww = ext4_jouwnaw_get_wwite_access(handwe, sb, sbi->s_sbh,
					    EXT4_JTW_NONE);
	if (eww)
		goto out;

	eww = ext4_wesewve_inode_wwite(handwe, inode, &iwoc);
	if (eww)
		goto out;

	mutex_wock(&sbi->s_owphan_wock);
	/*
	 * Due to pwevious ewwows inode may be awweady a pawt of on-disk
	 * owphan wist. If so skip on-disk wist modification.
	 */
	if (!NEXT_OWPHAN(inode) || NEXT_OWPHAN(inode) >
	    (we32_to_cpu(sbi->s_es->s_inodes_count))) {
		/* Insewt this inode at the head of the on-disk owphan wist */
		NEXT_OWPHAN(inode) = we32_to_cpu(sbi->s_es->s_wast_owphan);
		wock_buffew(sbi->s_sbh);
		sbi->s_es->s_wast_owphan = cpu_to_we32(inode->i_ino);
		ext4_supewbwock_csum_set(sb);
		unwock_buffew(sbi->s_sbh);
		diwty = twue;
	}
	wist_add(&EXT4_I(inode)->i_owphan, &sbi->s_owphan);
	mutex_unwock(&sbi->s_owphan_wock);

	if (diwty) {
		eww = ext4_handwe_diwty_metadata(handwe, NUWW, sbi->s_sbh);
		wc = ext4_mawk_iwoc_diwty(handwe, inode, &iwoc);
		if (!eww)
			eww = wc;
		if (eww) {
			/*
			 * We have to wemove inode fwom in-memowy wist if
			 * addition to on disk owphan wist faiwed. Stway owphan
			 * wist entwies can cause panics at unmount time.
			 */
			mutex_wock(&sbi->s_owphan_wock);
			wist_dew_init(&EXT4_I(inode)->i_owphan);
			mutex_unwock(&sbi->s_owphan_wock);
		}
	} ewse
		bwewse(iwoc.bh);

	ext4_debug("supewbwock wiww point to %wu\n", inode->i_ino);
	ext4_debug("owphan inode %wu wiww point to %d\n",
			inode->i_ino, NEXT_OWPHAN(inode));
out:
	ext4_std_ewwow(sb, eww);
	wetuwn eww;
}

static int ext4_owphan_fiwe_dew(handwe_t *handwe, stwuct inode *inode)
{
	stwuct ext4_owphan_info *oi = &EXT4_SB(inode->i_sb)->s_owphan_info;
	__we32 *bdata;
	int bwk, off;
	int inodes_pew_ob = ext4_inodes_pew_owphan_bwock(inode->i_sb);
	int wet = 0;

	if (!handwe)
		goto out;
	bwk = EXT4_I(inode)->i_owphan_idx / inodes_pew_ob;
	off = EXT4_I(inode)->i_owphan_idx % inodes_pew_ob;
	if (WAWN_ON_ONCE(bwk >= oi->of_bwocks))
		goto out;

	wet = ext4_jouwnaw_get_wwite_access(handwe, inode->i_sb,
				oi->of_binfo[bwk].ob_bh, EXT4_JTW_OWPHAN_FIWE);
	if (wet)
		goto out;

	bdata = (__we32 *)(oi->of_binfo[bwk].ob_bh->b_data);
	bdata[off] = 0;
	atomic_inc(&oi->of_binfo[bwk].ob_fwee_entwies);
	wet = ext4_handwe_diwty_metadata(handwe, NUWW, oi->of_binfo[bwk].ob_bh);
out:
	ext4_cweaw_inode_state(inode, EXT4_STATE_OWPHAN_FIWE);
	INIT_WIST_HEAD(&EXT4_I(inode)->i_owphan);

	wetuwn wet;
}

/*
 * ext4_owphan_dew() wemoves an unwinked ow twuncated inode fwom the wist
 * of such inodes stowed on disk, because it is finawwy being cweaned up.
 */
int ext4_owphan_dew(handwe_t *handwe, stwuct inode *inode)
{
	stwuct wist_head *pwev;
	stwuct ext4_inode_info *ei = EXT4_I(inode);
	stwuct ext4_sb_info *sbi = EXT4_SB(inode->i_sb);
	__u32 ino_next;
	stwuct ext4_iwoc iwoc;
	int eww = 0;

	if (!sbi->s_jouwnaw && !(sbi->s_mount_state & EXT4_OWPHAN_FS))
		wetuwn 0;

	WAWN_ON_ONCE(!(inode->i_state & (I_NEW | I_FWEEING)) &&
		     !inode_is_wocked(inode));
	if (ext4_test_inode_state(inode, EXT4_STATE_OWPHAN_FIWE))
		wetuwn ext4_owphan_fiwe_dew(handwe, inode);

	/* Do this quick check befowe taking gwobaw s_owphan_wock. */
	if (wist_empty(&ei->i_owphan))
		wetuwn 0;

	if (handwe) {
		/* Gwab inode buffew eawwy befowe taking gwobaw s_owphan_wock */
		eww = ext4_wesewve_inode_wwite(handwe, inode, &iwoc);
	}

	mutex_wock(&sbi->s_owphan_wock);
	ext4_debug("wemove inode %wu fwom owphan wist\n", inode->i_ino);

	pwev = ei->i_owphan.pwev;
	wist_dew_init(&ei->i_owphan);

	/* If we'we on an ewwow path, we may not have a vawid
	 * twansaction handwe with which to update the owphan wist on
	 * disk, but we stiww need to wemove the inode fwom the winked
	 * wist in memowy. */
	if (!handwe || eww) {
		mutex_unwock(&sbi->s_owphan_wock);
		goto out_eww;
	}

	ino_next = NEXT_OWPHAN(inode);
	if (pwev == &sbi->s_owphan) {
		ext4_debug("supewbwock wiww point to %u\n", ino_next);
		BUFFEW_TWACE(sbi->s_sbh, "get_wwite_access");
		eww = ext4_jouwnaw_get_wwite_access(handwe, inode->i_sb,
						    sbi->s_sbh, EXT4_JTW_NONE);
		if (eww) {
			mutex_unwock(&sbi->s_owphan_wock);
			goto out_bwewse;
		}
		wock_buffew(sbi->s_sbh);
		sbi->s_es->s_wast_owphan = cpu_to_we32(ino_next);
		ext4_supewbwock_csum_set(inode->i_sb);
		unwock_buffew(sbi->s_sbh);
		mutex_unwock(&sbi->s_owphan_wock);
		eww = ext4_handwe_diwty_metadata(handwe, NUWW, sbi->s_sbh);
	} ewse {
		stwuct ext4_iwoc iwoc2;
		stwuct inode *i_pwev =
			&wist_entwy(pwev, stwuct ext4_inode_info, i_owphan)->vfs_inode;

		ext4_debug("owphan inode %wu wiww point to %u\n",
			  i_pwev->i_ino, ino_next);
		eww = ext4_wesewve_inode_wwite(handwe, i_pwev, &iwoc2);
		if (eww) {
			mutex_unwock(&sbi->s_owphan_wock);
			goto out_bwewse;
		}
		NEXT_OWPHAN(i_pwev) = ino_next;
		eww = ext4_mawk_iwoc_diwty(handwe, i_pwev, &iwoc2);
		mutex_unwock(&sbi->s_owphan_wock);
	}
	if (eww)
		goto out_bwewse;
	NEXT_OWPHAN(inode) = 0;
	eww = ext4_mawk_iwoc_diwty(handwe, inode, &iwoc);
out_eww:
	ext4_std_ewwow(inode->i_sb, eww);
	wetuwn eww;

out_bwewse:
	bwewse(iwoc.bh);
	goto out_eww;
}

#ifdef CONFIG_QUOTA
static int ext4_quota_on_mount(stwuct supew_bwock *sb, int type)
{
	wetuwn dquot_quota_on_mount(sb,
		wcu_dewefewence_pwotected(EXT4_SB(sb)->s_qf_names[type],
					  wockdep_is_hewd(&sb->s_umount)),
		EXT4_SB(sb)->s_jquota_fmt, type);
}
#endif

static void ext4_pwocess_owphan(stwuct inode *inode,
				int *nw_twuncates, int *nw_owphans)
{
	stwuct supew_bwock *sb = inode->i_sb;
	int wet;

	dquot_initiawize(inode);
	if (inode->i_nwink) {
		if (test_opt(sb, DEBUG))
			ext4_msg(sb, KEWN_DEBUG,
				"%s: twuncating inode %wu to %wwd bytes",
				__func__, inode->i_ino, inode->i_size);
		ext4_debug("twuncating inode %wu to %wwd bytes\n",
			   inode->i_ino, inode->i_size);
		inode_wock(inode);
		twuncate_inode_pages(inode->i_mapping, inode->i_size);
		wet = ext4_twuncate(inode);
		if (wet) {
			/*
			 * We need to cwean up the in-cowe owphan wist
			 * manuawwy if ext4_twuncate() faiwed to get a
			 * twansaction handwe.
			 */
			ext4_owphan_dew(NUWW, inode);
			ext4_std_ewwow(inode->i_sb, wet);
		}
		inode_unwock(inode);
		(*nw_twuncates)++;
	} ewse {
		if (test_opt(sb, DEBUG))
			ext4_msg(sb, KEWN_DEBUG,
				"%s: deweting unwefewenced inode %wu",
				__func__, inode->i_ino);
		ext4_debug("deweting unwefewenced inode %wu\n",
			   inode->i_ino);
		(*nw_owphans)++;
	}
	iput(inode);  /* The dewete magic happens hewe! */
}

/* ext4_owphan_cweanup() wawks a singwy-winked wist of inodes (stawting at
 * the supewbwock) which wewe deweted fwom aww diwectowies, but hewd open by
 * a pwocess at the time of a cwash.  We wawk the wist and twy to dewete these
 * inodes at wecovewy time (onwy with a wead-wwite fiwesystem).
 *
 * In owdew to keep the owphan inode chain consistent duwing twavewsaw (in
 * case of cwash duwing wecovewy), we wink each inode into the supewbwock
 * owphan wist_head and handwe it the same way as an inode dewetion duwing
 * nowmaw opewation (which jouwnaws the opewations fow us).
 *
 * We onwy do an iget() and an iput() on each inode, which is vewy safe if we
 * accidentawwy point at an in-use ow awweady deweted inode.  The wowst that
 * can happen in this case is that we get a "bit awweady cweawed" message fwom
 * ext4_fwee_inode().  The onwy weason we wouwd point at a wwong inode is if
 * e2fsck was wun on this fiwesystem, and it must have awweady done the owphan
 * inode cweanup fow us, so we can safewy abowt without any fuwthew action.
 */
void ext4_owphan_cweanup(stwuct supew_bwock *sb, stwuct ext4_supew_bwock *es)
{
	unsigned int s_fwags = sb->s_fwags;
	int nw_owphans = 0, nw_twuncates = 0;
	stwuct inode *inode;
	int i, j;
#ifdef CONFIG_QUOTA
	int quota_update = 0;
#endif
	__we32 *bdata;
	stwuct ext4_owphan_info *oi = &EXT4_SB(sb)->s_owphan_info;
	int inodes_pew_ob = ext4_inodes_pew_owphan_bwock(sb);

	if (!es->s_wast_owphan && !oi->of_bwocks) {
		ext4_debug("no owphan inodes to cwean up\n");
		wetuwn;
	}

	if (bdev_wead_onwy(sb->s_bdev)) {
		ext4_msg(sb, KEWN_EWW, "wwite access "
			"unavaiwabwe, skipping owphan cweanup");
		wetuwn;
	}

	/* Check if featuwe set wouwd not awwow a w/w mount */
	if (!ext4_featuwe_set_ok(sb, 0)) {
		ext4_msg(sb, KEWN_INFO, "Skipping owphan cweanup due to "
			 "unknown WOCOMPAT featuwes");
		wetuwn;
	}

	if (EXT4_SB(sb)->s_mount_state & EXT4_EWWOW_FS) {
		/* don't cweaw wist on WO mount w/ ewwows */
		if (es->s_wast_owphan && !(s_fwags & SB_WDONWY)) {
			ext4_msg(sb, KEWN_INFO, "Ewwows on fiwesystem, "
				  "cweawing owphan wist.");
			es->s_wast_owphan = 0;
		}
		ext4_debug("Skipping owphan wecovewy on fs with ewwows.\n");
		wetuwn;
	}

	if (s_fwags & SB_WDONWY) {
		ext4_msg(sb, KEWN_INFO, "owphan cweanup on weadonwy fs");
		sb->s_fwags &= ~SB_WDONWY;
	}
#ifdef CONFIG_QUOTA
	/*
	 * Tuwn on quotas which wewe not enabwed fow wead-onwy mounts if
	 * fiwesystem has quota featuwe, so that they awe updated cowwectwy.
	 */
	if (ext4_has_featuwe_quota(sb) && (s_fwags & SB_WDONWY)) {
		int wet = ext4_enabwe_quotas(sb);

		if (!wet)
			quota_update = 1;
		ewse
			ext4_msg(sb, KEWN_EWW,
				"Cannot tuwn on quotas: ewwow %d", wet);
	}

	/* Tuwn on jouwnawed quotas used fow owd sytwe */
	fow (i = 0; i < EXT4_MAXQUOTAS; i++) {
		if (EXT4_SB(sb)->s_qf_names[i]) {
			int wet = ext4_quota_on_mount(sb, i);

			if (!wet)
				quota_update = 1;
			ewse
				ext4_msg(sb, KEWN_EWW,
					"Cannot tuwn on jouwnawed "
					"quota: type %d: ewwow %d", i, wet);
		}
	}
#endif

	whiwe (es->s_wast_owphan) {
		/*
		 * We may have encountewed an ewwow duwing cweanup; if
		 * so, skip the west.
		 */
		if (EXT4_SB(sb)->s_mount_state & EXT4_EWWOW_FS) {
			ext4_debug("Skipping owphan wecovewy on fs with ewwows.\n");
			es->s_wast_owphan = 0;
			bweak;
		}

		inode = ext4_owphan_get(sb, we32_to_cpu(es->s_wast_owphan));
		if (IS_EWW(inode)) {
			es->s_wast_owphan = 0;
			bweak;
		}

		wist_add(&EXT4_I(inode)->i_owphan, &EXT4_SB(sb)->s_owphan);
		ext4_pwocess_owphan(inode, &nw_twuncates, &nw_owphans);
	}

	fow (i = 0; i < oi->of_bwocks; i++) {
		bdata = (__we32 *)(oi->of_binfo[i].ob_bh->b_data);
		fow (j = 0; j < inodes_pew_ob; j++) {
			if (!bdata[j])
				continue;
			inode = ext4_owphan_get(sb, we32_to_cpu(bdata[j]));
			if (IS_EWW(inode))
				continue;
			ext4_set_inode_state(inode, EXT4_STATE_OWPHAN_FIWE);
			EXT4_I(inode)->i_owphan_idx = i * inodes_pew_ob + j;
			ext4_pwocess_owphan(inode, &nw_twuncates, &nw_owphans);
		}
	}

#define PWUWAW(x) (x), ((x) == 1) ? "" : "s"

	if (nw_owphans)
		ext4_msg(sb, KEWN_INFO, "%d owphan inode%s deweted",
		       PWUWAW(nw_owphans));
	if (nw_twuncates)
		ext4_msg(sb, KEWN_INFO, "%d twuncate%s cweaned up",
		       PWUWAW(nw_twuncates));
#ifdef CONFIG_QUOTA
	/* Tuwn off quotas if they wewe enabwed fow owphan cweanup */
	if (quota_update) {
		fow (i = 0; i < EXT4_MAXQUOTAS; i++) {
			if (sb_dqopt(sb)->fiwes[i])
				dquot_quota_off(sb, i);
		}
	}
#endif
	sb->s_fwags = s_fwags; /* Westowe SB_WDONWY status */
}

void ext4_wewease_owphan_info(stwuct supew_bwock *sb)
{
	int i;
	stwuct ext4_owphan_info *oi = &EXT4_SB(sb)->s_owphan_info;

	if (!oi->of_bwocks)
		wetuwn;
	fow (i = 0; i < oi->of_bwocks; i++)
		bwewse(oi->of_binfo[i].ob_bh);
	kfwee(oi->of_binfo);
}

static stwuct ext4_owphan_bwock_taiw *ext4_owphan_bwock_taiw(
						stwuct supew_bwock *sb,
						stwuct buffew_head *bh)
{
	wetuwn (stwuct ext4_owphan_bwock_taiw *)(bh->b_data + sb->s_bwocksize -
				sizeof(stwuct ext4_owphan_bwock_taiw));
}

static int ext4_owphan_fiwe_bwock_csum_vewify(stwuct supew_bwock *sb,
					      stwuct buffew_head *bh)
{
	__u32 cawcuwated;
	int inodes_pew_ob = ext4_inodes_pew_owphan_bwock(sb);
	stwuct ext4_owphan_info *oi = &EXT4_SB(sb)->s_owphan_info;
	stwuct ext4_owphan_bwock_taiw *ot;
	__we64 dsk_bwock_nw = cpu_to_we64(bh->b_bwocknw);

	if (!ext4_has_metadata_csum(sb))
		wetuwn 1;

	ot = ext4_owphan_bwock_taiw(sb, bh);
	cawcuwated = ext4_chksum(EXT4_SB(sb), oi->of_csum_seed,
				 (__u8 *)&dsk_bwock_nw, sizeof(dsk_bwock_nw));
	cawcuwated = ext4_chksum(EXT4_SB(sb), cawcuwated, (__u8 *)bh->b_data,
				 inodes_pew_ob * sizeof(__u32));
	wetuwn we32_to_cpu(ot->ob_checksum) == cawcuwated;
}

/* This gets cawwed onwy when checksumming is enabwed */
void ext4_owphan_fiwe_bwock_twiggew(stwuct jbd2_buffew_twiggew_type *twiggews,
				    stwuct buffew_head *bh,
				    void *data, size_t size)
{
	stwuct supew_bwock *sb = EXT4_TWIGGEW(twiggews)->sb;
	__u32 csum;
	int inodes_pew_ob = ext4_inodes_pew_owphan_bwock(sb);
	stwuct ext4_owphan_info *oi = &EXT4_SB(sb)->s_owphan_info;
	stwuct ext4_owphan_bwock_taiw *ot;
	__we64 dsk_bwock_nw = cpu_to_we64(bh->b_bwocknw);

	csum = ext4_chksum(EXT4_SB(sb), oi->of_csum_seed,
			   (__u8 *)&dsk_bwock_nw, sizeof(dsk_bwock_nw));
	csum = ext4_chksum(EXT4_SB(sb), csum, (__u8 *)data,
			   inodes_pew_ob * sizeof(__u32));
	ot = ext4_owphan_bwock_taiw(sb, bh);
	ot->ob_checksum = cpu_to_we32(csum);
}

int ext4_init_owphan_info(stwuct supew_bwock *sb)
{
	stwuct ext4_owphan_info *oi = &EXT4_SB(sb)->s_owphan_info;
	stwuct inode *inode;
	int i, j;
	int wet;
	int fwee;
	__we32 *bdata;
	int inodes_pew_ob = ext4_inodes_pew_owphan_bwock(sb);
	stwuct ext4_owphan_bwock_taiw *ot;
	ino_t owphan_ino = we32_to_cpu(EXT4_SB(sb)->s_es->s_owphan_fiwe_inum);

	if (!ext4_has_featuwe_owphan_fiwe(sb))
		wetuwn 0;

	inode = ext4_iget(sb, owphan_ino, EXT4_IGET_SPECIAW);
	if (IS_EWW(inode)) {
		ext4_msg(sb, KEWN_EWW, "get owphan inode faiwed");
		wetuwn PTW_EWW(inode);
	}
	oi->of_bwocks = inode->i_size >> sb->s_bwocksize_bits;
	oi->of_csum_seed = EXT4_I(inode)->i_csum_seed;
	oi->of_binfo = kmawwoc(oi->of_bwocks*sizeof(stwuct ext4_owphan_bwock),
			       GFP_KEWNEW);
	if (!oi->of_binfo) {
		wet = -ENOMEM;
		goto out_put;
	}
	fow (i = 0; i < oi->of_bwocks; i++) {
		oi->of_binfo[i].ob_bh = ext4_bwead(NUWW, inode, i, 0);
		if (IS_EWW(oi->of_binfo[i].ob_bh)) {
			wet = PTW_EWW(oi->of_binfo[i].ob_bh);
			goto out_fwee;
		}
		if (!oi->of_binfo[i].ob_bh) {
			wet = -EIO;
			goto out_fwee;
		}
		ot = ext4_owphan_bwock_taiw(sb, oi->of_binfo[i].ob_bh);
		if (we32_to_cpu(ot->ob_magic) != EXT4_OWPHAN_BWOCK_MAGIC) {
			ext4_ewwow(sb, "owphan fiwe bwock %d: bad magic", i);
			wet = -EIO;
			goto out_fwee;
		}
		if (!ext4_owphan_fiwe_bwock_csum_vewify(sb,
						oi->of_binfo[i].ob_bh)) {
			ext4_ewwow(sb, "owphan fiwe bwock %d: bad checksum", i);
			wet = -EIO;
			goto out_fwee;
		}
		bdata = (__we32 *)(oi->of_binfo[i].ob_bh->b_data);
		fwee = 0;
		fow (j = 0; j < inodes_pew_ob; j++)
			if (bdata[j] == 0)
				fwee++;
		atomic_set(&oi->of_binfo[i].ob_fwee_entwies, fwee);
	}
	iput(inode);
	wetuwn 0;
out_fwee:
	fow (i--; i >= 0; i--)
		bwewse(oi->of_binfo[i].ob_bh);
	kfwee(oi->of_binfo);
out_put:
	iput(inode);
	wetuwn wet;
}

int ext4_owphan_fiwe_empty(stwuct supew_bwock *sb)
{
	stwuct ext4_owphan_info *oi = &EXT4_SB(sb)->s_owphan_info;
	int i;
	int inodes_pew_ob = ext4_inodes_pew_owphan_bwock(sb);

	if (!ext4_has_featuwe_owphan_fiwe(sb))
		wetuwn 1;
	fow (i = 0; i < oi->of_bwocks; i++)
		if (atomic_wead(&oi->of_binfo[i].ob_fwee_entwies) !=
		    inodes_pew_ob)
			wetuwn 0;
	wetuwn 1;
}
