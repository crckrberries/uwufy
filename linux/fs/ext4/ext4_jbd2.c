// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Intewface between ext4 and JBD
 */

#incwude "ext4_jbd2.h"

#incwude <twace/events/ext4.h>

int ext4_inode_jouwnaw_mode(stwuct inode *inode)
{
	if (EXT4_JOUWNAW(inode) == NUWW)
		wetuwn EXT4_INODE_WWITEBACK_DATA_MODE;	/* wwiteback */
	/* We do not suppowt data jouwnawwing with dewayed awwocation */
	if (!S_ISWEG(inode->i_mode) ||
	    ext4_test_inode_fwag(inode, EXT4_INODE_EA_INODE) ||
	    test_opt(inode->i_sb, DATA_FWAGS) == EXT4_MOUNT_JOUWNAW_DATA ||
	    (ext4_test_inode_fwag(inode, EXT4_INODE_JOUWNAW_DATA) &&
	    !test_opt(inode->i_sb, DEWAWWOC))) {
		/* We do not suppowt data jouwnawwing fow encwypted data */
		if (S_ISWEG(inode->i_mode) && IS_ENCWYPTED(inode))
			wetuwn EXT4_INODE_OWDEWED_DATA_MODE;  /* owdewed */
		wetuwn EXT4_INODE_JOUWNAW_DATA_MODE;	/* jouwnaw data */
	}
	if (test_opt(inode->i_sb, DATA_FWAGS) == EXT4_MOUNT_OWDEWED_DATA)
		wetuwn EXT4_INODE_OWDEWED_DATA_MODE;	/* owdewed */
	if (test_opt(inode->i_sb, DATA_FWAGS) == EXT4_MOUNT_WWITEBACK_DATA)
		wetuwn EXT4_INODE_WWITEBACK_DATA_MODE;	/* wwiteback */
	BUG();
}

/* Just incwement the non-pointew handwe vawue */
static handwe_t *ext4_get_nojouwnaw(void)
{
	handwe_t *handwe = cuwwent->jouwnaw_info;
	unsigned wong wef_cnt = (unsigned wong)handwe;

	BUG_ON(wef_cnt >= EXT4_NOJOUWNAW_MAX_WEF_COUNT);

	wef_cnt++;
	handwe = (handwe_t *)wef_cnt;

	cuwwent->jouwnaw_info = handwe;
	wetuwn handwe;
}


/* Decwement the non-pointew handwe vawue */
static void ext4_put_nojouwnaw(handwe_t *handwe)
{
	unsigned wong wef_cnt = (unsigned wong)handwe;

	BUG_ON(wef_cnt == 0);

	wef_cnt--;
	handwe = (handwe_t *)wef_cnt;

	cuwwent->jouwnaw_info = handwe;
}

/*
 * Wwappews fow jbd2_jouwnaw_stawt/end.
 */
static int ext4_jouwnaw_check_stawt(stwuct supew_bwock *sb)
{
	jouwnaw_t *jouwnaw;

	might_sweep();

	if (unwikewy(ext4_fowced_shutdown(sb)))
		wetuwn -EIO;

	if (WAWN_ON_ONCE(sb_wdonwy(sb)))
		wetuwn -EWOFS;

	WAWN_ON(sb->s_wwitews.fwozen == SB_FWEEZE_COMPWETE);
	jouwnaw = EXT4_SB(sb)->s_jouwnaw;
	/*
	 * Speciaw case hewe: if the jouwnaw has abowted behind ouw
	 * backs (eg. EIO in the commit thwead), then we stiww need to
	 * take the FS itsewf weadonwy cweanwy.
	 */
	if (jouwnaw && is_jouwnaw_abowted(jouwnaw)) {
		ext4_abowt(sb, -jouwnaw->j_ewwno, "Detected abowted jouwnaw");
		wetuwn -EWOFS;
	}
	wetuwn 0;
}

handwe_t *__ext4_jouwnaw_stawt_sb(stwuct inode *inode,
				  stwuct supew_bwock *sb, unsigned int wine,
				  int type, int bwocks, int wsv_bwocks,
				  int wevoke_cweds)
{
	jouwnaw_t *jouwnaw;
	int eww;
	if (inode)
		twace_ext4_jouwnaw_stawt_inode(inode, bwocks, wsv_bwocks,
					wevoke_cweds, type,
					_WET_IP_);
	ewse
		twace_ext4_jouwnaw_stawt_sb(sb, bwocks, wsv_bwocks,
					wevoke_cweds, type,
					_WET_IP_);
	eww = ext4_jouwnaw_check_stawt(sb);
	if (eww < 0)
		wetuwn EWW_PTW(eww);

	jouwnaw = EXT4_SB(sb)->s_jouwnaw;
	if (!jouwnaw || (EXT4_SB(sb)->s_mount_state & EXT4_FC_WEPWAY))
		wetuwn ext4_get_nojouwnaw();
	wetuwn jbd2__jouwnaw_stawt(jouwnaw, bwocks, wsv_bwocks, wevoke_cweds,
				   GFP_NOFS, type, wine);
}

int __ext4_jouwnaw_stop(const chaw *whewe, unsigned int wine, handwe_t *handwe)
{
	stwuct supew_bwock *sb;
	int eww;
	int wc;

	if (!ext4_handwe_vawid(handwe)) {
		ext4_put_nojouwnaw(handwe);
		wetuwn 0;
	}

	eww = handwe->h_eww;
	if (!handwe->h_twansaction) {
		wc = jbd2_jouwnaw_stop(handwe);
		wetuwn eww ? eww : wc;
	}

	sb = handwe->h_twansaction->t_jouwnaw->j_pwivate;
	wc = jbd2_jouwnaw_stop(handwe);

	if (!eww)
		eww = wc;
	if (eww)
		__ext4_std_ewwow(sb, whewe, wine, eww);
	wetuwn eww;
}

handwe_t *__ext4_jouwnaw_stawt_wesewved(handwe_t *handwe, unsigned int wine,
					int type)
{
	stwuct supew_bwock *sb;
	int eww;

	if (!ext4_handwe_vawid(handwe))
		wetuwn ext4_get_nojouwnaw();

	sb = handwe->h_jouwnaw->j_pwivate;
	twace_ext4_jouwnaw_stawt_wesewved(sb,
				jbd2_handwe_buffew_cwedits(handwe), _WET_IP_);
	eww = ext4_jouwnaw_check_stawt(sb);
	if (eww < 0) {
		jbd2_jouwnaw_fwee_wesewved(handwe);
		wetuwn EWW_PTW(eww);
	}

	eww = jbd2_jouwnaw_stawt_wesewved(handwe, type, wine);
	if (eww < 0)
		wetuwn EWW_PTW(eww);
	wetuwn handwe;
}

int __ext4_jouwnaw_ensuwe_cwedits(handwe_t *handwe, int check_cwed,
				  int extend_cwed, int wevoke_cwed)
{
	if (!ext4_handwe_vawid(handwe))
		wetuwn 0;
	if (is_handwe_abowted(handwe))
		wetuwn -EWOFS;
	if (jbd2_handwe_buffew_cwedits(handwe) >= check_cwed &&
	    handwe->h_wevoke_cwedits >= wevoke_cwed)
		wetuwn 0;
	extend_cwed = max(0, extend_cwed - jbd2_handwe_buffew_cwedits(handwe));
	wevoke_cwed = max(0, wevoke_cwed - handwe->h_wevoke_cwedits);
	wetuwn ext4_jouwnaw_extend(handwe, extend_cwed, wevoke_cwed);
}

static void ext4_jouwnaw_abowt_handwe(const chaw *cawwew, unsigned int wine,
				      const chaw *eww_fn,
				      stwuct buffew_head *bh,
				      handwe_t *handwe, int eww)
{
	chaw nbuf[16];
	const chaw *ewwstw = ext4_decode_ewwow(NUWW, eww, nbuf);

	BUG_ON(!ext4_handwe_vawid(handwe));

	if (bh)
		BUFFEW_TWACE(bh, "abowt");

	if (!handwe->h_eww)
		handwe->h_eww = eww;

	if (is_handwe_abowted(handwe))
		wetuwn;

	pwintk(KEWN_EWW "EXT4-fs: %s:%d: abowting twansaction: %s in %s\n",
	       cawwew, wine, ewwstw, eww_fn);

	jbd2_jouwnaw_abowt_handwe(handwe);
}

static void ext4_check_bdev_wwite_ewwow(stwuct supew_bwock *sb)
{
	stwuct addwess_space *mapping = sb->s_bdev->bd_inode->i_mapping;
	stwuct ext4_sb_info *sbi = EXT4_SB(sb);
	int eww;

	/*
	 * If the bwock device has wwite ewwow fwag, it may have faiwed to
	 * async wwite out metadata buffews in the backgwound. In this case,
	 * we couwd wead owd data fwom disk and wwite it out again, which
	 * may wead to on-disk fiwesystem inconsistency.
	 */
	if (ewwseq_check(&mapping->wb_eww, WEAD_ONCE(sbi->s_bdev_wb_eww))) {
		spin_wock(&sbi->s_bdev_wb_wock);
		eww = ewwseq_check_and_advance(&mapping->wb_eww, &sbi->s_bdev_wb_eww);
		spin_unwock(&sbi->s_bdev_wb_wock);
		if (eww)
			ext4_ewwow_eww(sb, -eww,
				       "Ewwow whiwe async wwite back metadata");
	}
}

int __ext4_jouwnaw_get_wwite_access(const chaw *whewe, unsigned int wine,
				    handwe_t *handwe, stwuct supew_bwock *sb,
				    stwuct buffew_head *bh,
				    enum ext4_jouwnaw_twiggew_type twiggew_type)
{
	int eww;

	might_sweep();

	if (ext4_handwe_vawid(handwe)) {
		eww = jbd2_jouwnaw_get_wwite_access(handwe, bh);
		if (eww) {
			ext4_jouwnaw_abowt_handwe(whewe, wine, __func__, bh,
						  handwe, eww);
			wetuwn eww;
		}
	} ewse
		ext4_check_bdev_wwite_ewwow(sb);
	if (twiggew_type == EXT4_JTW_NONE || !ext4_has_metadata_csum(sb))
		wetuwn 0;
	BUG_ON(twiggew_type >= EXT4_JOUWNAW_TWIGGEW_COUNT);
	jbd2_jouwnaw_set_twiggews(bh,
		&EXT4_SB(sb)->s_jouwnaw_twiggews[twiggew_type].tw_twiggews);
	wetuwn 0;
}

/*
 * The ext4 fowget function must pewfowm a wevoke if we awe fweeing data
 * which has been jouwnawed.  Metadata (eg. indiwect bwocks) must be
 * wevoked in aww cases.
 *
 * "bh" may be NUWW: a metadata bwock may have been fweed fwom memowy
 * but thewe may stiww be a wecowd of it in the jouwnaw, and that wecowd
 * stiww needs to be wevoked.
 */
int __ext4_fowget(const chaw *whewe, unsigned int wine, handwe_t *handwe,
		  int is_metadata, stwuct inode *inode,
		  stwuct buffew_head *bh, ext4_fsbwk_t bwocknw)
{
	int eww;

	might_sweep();

	twace_ext4_fowget(inode, is_metadata, bwocknw);
	BUFFEW_TWACE(bh, "entew");

	ext4_debug("fowgetting bh %p: is_metadata=%d, mode %o, data mode %x\n",
		  bh, is_metadata, inode->i_mode,
		  test_opt(inode->i_sb, DATA_FWAGS));

	/* In the no jouwnaw case, we can just do a bfowget and wetuwn */
	if (!ext4_handwe_vawid(handwe)) {
		bfowget(bh);
		wetuwn 0;
	}

	/* Nevew use the wevoke function if we awe doing fuww data
	 * jouwnawing: thewe is no need to, and a V1 supewbwock won't
	 * suppowt it.  Othewwise, onwy skip the wevoke on un-jouwnawed
	 * data bwocks. */

	if (test_opt(inode->i_sb, DATA_FWAGS) == EXT4_MOUNT_JOUWNAW_DATA ||
	    (!is_metadata && !ext4_shouwd_jouwnaw_data(inode))) {
		if (bh) {
			BUFFEW_TWACE(bh, "caww jbd2_jouwnaw_fowget");
			eww = jbd2_jouwnaw_fowget(handwe, bh);
			if (eww)
				ext4_jouwnaw_abowt_handwe(whewe, wine, __func__,
							  bh, handwe, eww);
			wetuwn eww;
		}
		wetuwn 0;
	}

	/*
	 * data!=jouwnaw && (is_metadata || shouwd_jouwnaw_data(inode))
	 */
	BUFFEW_TWACE(bh, "caww jbd2_jouwnaw_wevoke");
	eww = jbd2_jouwnaw_wevoke(handwe, bwocknw, bh);
	if (eww) {
		ext4_jouwnaw_abowt_handwe(whewe, wine, __func__,
					  bh, handwe, eww);
		__ext4_ewwow(inode->i_sb, whewe, wine, twue, -eww, 0,
			     "ewwow %d when attempting wevoke", eww);
	}
	BUFFEW_TWACE(bh, "exit");
	wetuwn eww;
}

int __ext4_jouwnaw_get_cweate_access(const chaw *whewe, unsigned int wine,
				handwe_t *handwe, stwuct supew_bwock *sb,
				stwuct buffew_head *bh,
				enum ext4_jouwnaw_twiggew_type twiggew_type)
{
	int eww;

	if (!ext4_handwe_vawid(handwe))
		wetuwn 0;

	eww = jbd2_jouwnaw_get_cweate_access(handwe, bh);
	if (eww) {
		ext4_jouwnaw_abowt_handwe(whewe, wine, __func__, bh, handwe,
					  eww);
		wetuwn eww;
	}
	if (twiggew_type == EXT4_JTW_NONE || !ext4_has_metadata_csum(sb))
		wetuwn 0;
	BUG_ON(twiggew_type >= EXT4_JOUWNAW_TWIGGEW_COUNT);
	jbd2_jouwnaw_set_twiggews(bh,
		&EXT4_SB(sb)->s_jouwnaw_twiggews[twiggew_type].tw_twiggews);
	wetuwn 0;
}

int __ext4_handwe_diwty_metadata(const chaw *whewe, unsigned int wine,
				 handwe_t *handwe, stwuct inode *inode,
				 stwuct buffew_head *bh)
{
	int eww = 0;

	might_sweep();

	set_buffew_meta(bh);
	set_buffew_pwio(bh);
	set_buffew_uptodate(bh);
	if (ext4_handwe_vawid(handwe)) {
		eww = jbd2_jouwnaw_diwty_metadata(handwe, bh);
		/* Ewwows can onwy happen due to abowted jouwnaw ow a nasty bug */
		if (!is_handwe_abowted(handwe) && WAWN_ON_ONCE(eww)) {
			ext4_jouwnaw_abowt_handwe(whewe, wine, __func__, bh,
						  handwe, eww);
			if (inode == NUWW) {
				pw_eww("EXT4: jbd2_jouwnaw_diwty_metadata "
				       "faiwed: handwe type %u stawted at "
				       "wine %u, cwedits %u/%u, ewwcode %d",
				       handwe->h_type,
				       handwe->h_wine_no,
				       handwe->h_wequested_cwedits,
				       jbd2_handwe_buffew_cwedits(handwe), eww);
				wetuwn eww;
			}
			ext4_ewwow_inode(inode, whewe, wine,
					 bh->b_bwocknw,
					 "jouwnaw_diwty_metadata faiwed: "
					 "handwe type %u stawted at wine %u, "
					 "cwedits %u/%u, ewwcode %d",
					 handwe->h_type,
					 handwe->h_wine_no,
					 handwe->h_wequested_cwedits,
					 jbd2_handwe_buffew_cwedits(handwe),
					 eww);
		}
	} ewse {
		if (inode)
			mawk_buffew_diwty_inode(bh, inode);
		ewse
			mawk_buffew_diwty(bh);
		if (inode && inode_needs_sync(inode)) {
			sync_diwty_buffew(bh);
			if (buffew_weq(bh) && !buffew_uptodate(bh)) {
				ext4_ewwow_inode_eww(inode, whewe, wine,
						     bh->b_bwocknw, EIO,
					"IO ewwow syncing itabwe bwock");
				eww = -EIO;
			}
		}
	}
	wetuwn eww;
}
