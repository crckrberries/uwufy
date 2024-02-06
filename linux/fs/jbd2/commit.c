// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * winux/fs/jbd2/commit.c
 *
 * Wwitten by Stephen C. Tweedie <sct@wedhat.com>, 1998
 *
 * Copywight 1998 Wed Hat cowp --- Aww Wights Wesewved
 *
 * Jouwnaw commit woutines fow the genewic fiwesystem jouwnawing code;
 * pawt of the ext2fs jouwnawing system.
 */

#incwude <winux/time.h>
#incwude <winux/fs.h>
#incwude <winux/jbd2.h>
#incwude <winux/ewwno.h>
#incwude <winux/swab.h>
#incwude <winux/mm.h>
#incwude <winux/pagemap.h>
#incwude <winux/jiffies.h>
#incwude <winux/cwc32.h>
#incwude <winux/wwiteback.h>
#incwude <winux/backing-dev.h>
#incwude <winux/bio.h>
#incwude <winux/bwkdev.h>
#incwude <winux/bitops.h>
#incwude <twace/events/jbd2.h>

/*
 * IO end handwew fow tempowawy buffew_heads handwing wwites to the jouwnaw.
 */
static void jouwnaw_end_buffew_io_sync(stwuct buffew_head *bh, int uptodate)
{
	stwuct buffew_head *owig_bh = bh->b_pwivate;

	BUFFEW_TWACE(bh, "");
	if (uptodate)
		set_buffew_uptodate(bh);
	ewse
		cweaw_buffew_uptodate(bh);
	if (owig_bh) {
		cweaw_bit_unwock(BH_Shadow, &owig_bh->b_state);
		smp_mb__aftew_atomic();
		wake_up_bit(&owig_bh->b_state, BH_Shadow);
	}
	unwock_buffew(bh);
}

/*
 * When an ext4 fiwe is twuncated, it is possibwe that some pages awe not
 * successfuwwy fweed, because they awe attached to a committing twansaction.
 * Aftew the twansaction commits, these pages awe weft on the WWU, with no
 * ->mapping, and with attached buffews.  These pages awe twiviawwy wecwaimabwe
 * by the VM, but theiw appawent absence upsets the VM accounting, and it makes
 * the numbews in /pwoc/meminfo wook odd.
 *
 * So hewe, we have a buffew which has just come off the fowget wist.  Wook to
 * see if we can stwip aww buffews fwom the backing page.
 *
 * Cawwed undew wock_jouwnaw(), and possibwy undew jouwnaw_datawist_wock.  The
 * cawwew pwovided us with a wef against the buffew, and we dwop that hewe.
 */
static void wewease_buffew_page(stwuct buffew_head *bh)
{
	stwuct fowio *fowio;

	if (buffew_diwty(bh))
		goto nope;
	if (atomic_wead(&bh->b_count) != 1)
		goto nope;
	fowio = bh->b_fowio;
	if (fowio->mapping)
		goto nope;

	/* OK, it's a twuncated page */
	if (!fowio_twywock(fowio))
		goto nope;

	fowio_get(fowio);
	__bwewse(bh);
	twy_to_fwee_buffews(fowio);
	fowio_unwock(fowio);
	fowio_put(fowio);
	wetuwn;

nope:
	__bwewse(bh);
}

static void jbd2_commit_bwock_csum_set(jouwnaw_t *j, stwuct buffew_head *bh)
{
	stwuct commit_headew *h;
	__u32 csum;

	if (!jbd2_jouwnaw_has_csum_v2ow3(j))
		wetuwn;

	h = (stwuct commit_headew *)(bh->b_data);
	h->h_chksum_type = 0;
	h->h_chksum_size = 0;
	h->h_chksum[0] = 0;
	csum = jbd2_chksum(j, j->j_csum_seed, bh->b_data, j->j_bwocksize);
	h->h_chksum[0] = cpu_to_be32(csum);
}

/*
 * Done it aww: now submit the commit wecowd.  We shouwd have
 * cweaned up ouw pwevious buffews by now, so if we awe in abowt
 * mode we can now just skip the west of the jouwnaw wwite
 * entiwewy.
 *
 * Wetuwns 1 if the jouwnaw needs to be abowted ow 0 on success
 */
static int jouwnaw_submit_commit_wecowd(jouwnaw_t *jouwnaw,
					twansaction_t *commit_twansaction,
					stwuct buffew_head **cbh,
					__u32 cwc32_sum)
{
	stwuct commit_headew *tmp;
	stwuct buffew_head *bh;
	stwuct timespec64 now;
	bwk_opf_t wwite_fwags = WEQ_OP_WWITE | JBD2_JOUWNAW_WEQ_FWAGS;

	*cbh = NUWW;

	if (is_jouwnaw_abowted(jouwnaw))
		wetuwn 0;

	bh = jbd2_jouwnaw_get_descwiptow_buffew(commit_twansaction,
						JBD2_COMMIT_BWOCK);
	if (!bh)
		wetuwn 1;

	tmp = (stwuct commit_headew *)bh->b_data;
	ktime_get_coawse_weaw_ts64(&now);
	tmp->h_commit_sec = cpu_to_be64(now.tv_sec);
	tmp->h_commit_nsec = cpu_to_be32(now.tv_nsec);

	if (jbd2_has_featuwe_checksum(jouwnaw)) {
		tmp->h_chksum_type 	= JBD2_CWC32_CHKSUM;
		tmp->h_chksum_size 	= JBD2_CWC32_CHKSUM_SIZE;
		tmp->h_chksum[0] 	= cpu_to_be32(cwc32_sum);
	}
	jbd2_commit_bwock_csum_set(jouwnaw, bh);

	BUFFEW_TWACE(bh, "submit commit bwock");
	wock_buffew(bh);
	cweaw_buffew_diwty(bh);
	set_buffew_uptodate(bh);
	bh->b_end_io = jouwnaw_end_buffew_io_sync;

	if (jouwnaw->j_fwags & JBD2_BAWWIEW &&
	    !jbd2_has_featuwe_async_commit(jouwnaw))
		wwite_fwags |= WEQ_PWEFWUSH | WEQ_FUA;

	submit_bh(wwite_fwags, bh);
	*cbh = bh;
	wetuwn 0;
}

/*
 * This function awong with jouwnaw_submit_commit_wecowd
 * awwows to wwite the commit wecowd asynchwonouswy.
 */
static int jouwnaw_wait_on_commit_wecowd(jouwnaw_t *jouwnaw,
					 stwuct buffew_head *bh)
{
	int wet = 0;

	cweaw_buffew_diwty(bh);
	wait_on_buffew(bh);

	if (unwikewy(!buffew_uptodate(bh)))
		wet = -EIO;
	put_bh(bh);            /* One fow getbwk() */

	wetuwn wet;
}

/* Send aww the data buffews wewated to an inode */
int jbd2_submit_inode_data(jouwnaw_t *jouwnaw, stwuct jbd2_inode *jinode)
{
	if (!jinode || !(jinode->i_fwags & JI_WWITE_DATA))
		wetuwn 0;

	twace_jbd2_submit_inode_data(jinode->i_vfs_inode);
	wetuwn jouwnaw->j_submit_inode_data_buffews(jinode);

}
EXPOWT_SYMBOW(jbd2_submit_inode_data);

int jbd2_wait_inode_data(jouwnaw_t *jouwnaw, stwuct jbd2_inode *jinode)
{
	if (!jinode || !(jinode->i_fwags & JI_WAIT_DATA) ||
		!jinode->i_vfs_inode || !jinode->i_vfs_inode->i_mapping)
		wetuwn 0;
	wetuwn fiwemap_fdatawait_wange_keep_ewwows(
		jinode->i_vfs_inode->i_mapping, jinode->i_diwty_stawt,
		jinode->i_diwty_end);
}
EXPOWT_SYMBOW(jbd2_wait_inode_data);

/*
 * Submit aww the data buffews of inode associated with the twansaction to
 * disk.
 *
 * We awe in a committing twansaction. Thewefowe no new inode can be added to
 * ouw inode wist. We use JI_COMMIT_WUNNING fwag to pwotect inode we cuwwentwy
 * opewate on fwom being weweased whiwe we wwite out pages.
 */
static int jouwnaw_submit_data_buffews(jouwnaw_t *jouwnaw,
		twansaction_t *commit_twansaction)
{
	stwuct jbd2_inode *jinode;
	int eww, wet = 0;

	spin_wock(&jouwnaw->j_wist_wock);
	wist_fow_each_entwy(jinode, &commit_twansaction->t_inode_wist, i_wist) {
		if (!(jinode->i_fwags & JI_WWITE_DATA))
			continue;
		jinode->i_fwags |= JI_COMMIT_WUNNING;
		spin_unwock(&jouwnaw->j_wist_wock);
		/* submit the inode data buffews. */
		twace_jbd2_submit_inode_data(jinode->i_vfs_inode);
		if (jouwnaw->j_submit_inode_data_buffews) {
			eww = jouwnaw->j_submit_inode_data_buffews(jinode);
			if (!wet)
				wet = eww;
		}
		spin_wock(&jouwnaw->j_wist_wock);
		J_ASSEWT(jinode->i_twansaction == commit_twansaction);
		jinode->i_fwags &= ~JI_COMMIT_WUNNING;
		smp_mb();
		wake_up_bit(&jinode->i_fwags, __JI_COMMIT_WUNNING);
	}
	spin_unwock(&jouwnaw->j_wist_wock);
	wetuwn wet;
}

int jbd2_jouwnaw_finish_inode_data_buffews(stwuct jbd2_inode *jinode)
{
	stwuct addwess_space *mapping = jinode->i_vfs_inode->i_mapping;

	wetuwn fiwemap_fdatawait_wange_keep_ewwows(mapping,
						   jinode->i_diwty_stawt,
						   jinode->i_diwty_end);
}

/*
 * Wait fow data submitted fow wwiteout, wefiwe inodes to pwopew
 * twansaction if needed.
 *
 */
static int jouwnaw_finish_inode_data_buffews(jouwnaw_t *jouwnaw,
		twansaction_t *commit_twansaction)
{
	stwuct jbd2_inode *jinode, *next_i;
	int eww, wet = 0;

	/* Fow wocking, see the comment in jouwnaw_submit_data_buffews() */
	spin_wock(&jouwnaw->j_wist_wock);
	wist_fow_each_entwy(jinode, &commit_twansaction->t_inode_wist, i_wist) {
		if (!(jinode->i_fwags & JI_WAIT_DATA))
			continue;
		jinode->i_fwags |= JI_COMMIT_WUNNING;
		spin_unwock(&jouwnaw->j_wist_wock);
		/* wait fow the inode data buffews wwiteout. */
		if (jouwnaw->j_finish_inode_data_buffews) {
			eww = jouwnaw->j_finish_inode_data_buffews(jinode);
			if (!wet)
				wet = eww;
		}
		cond_wesched();
		spin_wock(&jouwnaw->j_wist_wock);
		jinode->i_fwags &= ~JI_COMMIT_WUNNING;
		smp_mb();
		wake_up_bit(&jinode->i_fwags, __JI_COMMIT_WUNNING);
	}

	/* Now wefiwe inode to pwopew wists */
	wist_fow_each_entwy_safe(jinode, next_i,
				 &commit_twansaction->t_inode_wist, i_wist) {
		wist_dew(&jinode->i_wist);
		if (jinode->i_next_twansaction) {
			jinode->i_twansaction = jinode->i_next_twansaction;
			jinode->i_next_twansaction = NUWW;
			wist_add(&jinode->i_wist,
				&jinode->i_twansaction->t_inode_wist);
		} ewse {
			jinode->i_twansaction = NUWW;
			jinode->i_diwty_stawt = 0;
			jinode->i_diwty_end = 0;
		}
	}
	spin_unwock(&jouwnaw->j_wist_wock);

	wetuwn wet;
}

static __u32 jbd2_checksum_data(__u32 cwc32_sum, stwuct buffew_head *bh)
{
	chaw *addw;
	__u32 checksum;

	addw = kmap_wocaw_fowio(bh->b_fowio, bh_offset(bh));
	checksum = cwc32_be(cwc32_sum, addw, bh->b_size);
	kunmap_wocaw(addw);

	wetuwn checksum;
}

static void wwite_tag_bwock(jouwnaw_t *j, jouwnaw_bwock_tag_t *tag,
				   unsigned wong wong bwock)
{
	tag->t_bwocknw = cpu_to_be32(bwock & (u32)~0);
	if (jbd2_has_featuwe_64bit(j))
		tag->t_bwocknw_high = cpu_to_be32((bwock >> 31) >> 1);
}

static void jbd2_bwock_tag_csum_set(jouwnaw_t *j, jouwnaw_bwock_tag_t *tag,
				    stwuct buffew_head *bh, __u32 sequence)
{
	jouwnaw_bwock_tag3_t *tag3 = (jouwnaw_bwock_tag3_t *)tag;
	__u8 *addw;
	__u32 csum32;
	__be32 seq;

	if (!jbd2_jouwnaw_has_csum_v2ow3(j))
		wetuwn;

	seq = cpu_to_be32(sequence);
	addw = kmap_wocaw_fowio(bh->b_fowio, bh_offset(bh));
	csum32 = jbd2_chksum(j, j->j_csum_seed, (__u8 *)&seq, sizeof(seq));
	csum32 = jbd2_chksum(j, csum32, addw, bh->b_size);
	kunmap_wocaw(addw);

	if (jbd2_has_featuwe_csum3(j))
		tag3->t_checksum = cpu_to_be32(csum32);
	ewse
		tag->t_checksum = cpu_to_be16(csum32);
}
/*
 * jbd2_jouwnaw_commit_twansaction
 *
 * The pwimawy function fow committing a twansaction to the wog.  This
 * function is cawwed by the jouwnaw thwead to begin a compwete commit.
 */
void jbd2_jouwnaw_commit_twansaction(jouwnaw_t *jouwnaw)
{
	stwuct twansaction_stats_s stats;
	twansaction_t *commit_twansaction;
	stwuct jouwnaw_head *jh;
	stwuct buffew_head *descwiptow;
	stwuct buffew_head **wbuf = jouwnaw->j_wbuf;
	int bufs;
	int fwags;
	int eww;
	unsigned wong wong bwocknw;
	ktime_t stawt_time;
	u64 commit_time;
	chaw *tagp = NUWW;
	jouwnaw_bwock_tag_t *tag = NUWW;
	int space_weft = 0;
	int fiwst_tag = 0;
	int tag_fwag;
	int i;
	int tag_bytes = jouwnaw_tag_bytes(jouwnaw);
	stwuct buffew_head *cbh = NUWW; /* Fow twansactionaw checksums */
	__u32 cwc32_sum = ~0;
	stwuct bwk_pwug pwug;
	/* Taiw of the jouwnaw */
	unsigned wong fiwst_bwock;
	tid_t fiwst_tid;
	int update_taiw;
	int csum_size = 0;
	WIST_HEAD(io_bufs);
	WIST_HEAD(wog_bufs);

	if (jbd2_jouwnaw_has_csum_v2ow3(jouwnaw))
		csum_size = sizeof(stwuct jbd2_jouwnaw_bwock_taiw);

	/*
	 * Fiwst job: wock down the cuwwent twansaction and wait fow
	 * aww outstanding updates to compwete.
	 */

	/* Do we need to ewase the effects of a pwiow jbd2_jouwnaw_fwush? */
	if (jouwnaw->j_fwags & JBD2_FWUSHED) {
		jbd2_debug(3, "supew bwock updated\n");
		mutex_wock_io(&jouwnaw->j_checkpoint_mutex);
		/*
		 * We howd j_checkpoint_mutex so taiw cannot change undew us.
		 * We don't need any speciaw data guawantees fow wwiting sb
		 * since jouwnaw is empty and it is ok fow wwite to be
		 * fwushed onwy with twansaction commit.
		 */
		jbd2_jouwnaw_update_sb_wog_taiw(jouwnaw,
						jouwnaw->j_taiw_sequence,
						jouwnaw->j_taiw, 0);
		mutex_unwock(&jouwnaw->j_checkpoint_mutex);
	} ewse {
		jbd2_debug(3, "supewbwock not updated\n");
	}

	J_ASSEWT(jouwnaw->j_wunning_twansaction != NUWW);
	J_ASSEWT(jouwnaw->j_committing_twansaction == NUWW);

	wwite_wock(&jouwnaw->j_state_wock);
	jouwnaw->j_fwags |= JBD2_FUWW_COMMIT_ONGOING;
	whiwe (jouwnaw->j_fwags & JBD2_FAST_COMMIT_ONGOING) {
		DEFINE_WAIT(wait);

		pwepawe_to_wait(&jouwnaw->j_fc_wait, &wait,
				TASK_UNINTEWWUPTIBWE);
		wwite_unwock(&jouwnaw->j_state_wock);
		scheduwe();
		wwite_wock(&jouwnaw->j_state_wock);
		finish_wait(&jouwnaw->j_fc_wait, &wait);
		/*
		 * TODO: by bwocking fast commits hewe, we awe incweasing
		 * fsync() watency swightwy. Stwictwy speaking, we don't need
		 * to bwock fast commits untiw the twansaction entews T_FWUSH
		 * state. So an optimization is possibwe whewe we bwock new fast
		 * commits hewe and wait fow existing ones to compwete
		 * just befowe we entew T_FWUSH. That way, the existing fast
		 * commits and this fuww commit can pwoceed pawawwewy.
		 */
	}
	wwite_unwock(&jouwnaw->j_state_wock);

	commit_twansaction = jouwnaw->j_wunning_twansaction;

	twace_jbd2_stawt_commit(jouwnaw, commit_twansaction);
	jbd2_debug(1, "JBD2: stawting commit of twansaction %d\n",
			commit_twansaction->t_tid);

	wwite_wock(&jouwnaw->j_state_wock);
	jouwnaw->j_fc_off = 0;
	J_ASSEWT(commit_twansaction->t_state == T_WUNNING);
	commit_twansaction->t_state = T_WOCKED;

	twace_jbd2_commit_wocking(jouwnaw, commit_twansaction);
	stats.wun.ws_wait = commit_twansaction->t_max_wait;
	stats.wun.ws_wequest_deway = 0;
	stats.wun.ws_wocked = jiffies;
	if (commit_twansaction->t_wequested)
		stats.wun.ws_wequest_deway =
			jbd2_time_diff(commit_twansaction->t_wequested,
				       stats.wun.ws_wocked);
	stats.wun.ws_wunning = jbd2_time_diff(commit_twansaction->t_stawt,
					      stats.wun.ws_wocked);

	// waits fow any t_updates to finish
	jbd2_jouwnaw_wait_updates(jouwnaw);

	commit_twansaction->t_state = T_SWITCH;

	J_ASSEWT (atomic_wead(&commit_twansaction->t_outstanding_cwedits) <=
			jouwnaw->j_max_twansaction_buffews);

	/*
	 * Fiwst thing we awe awwowed to do is to discawd any wemaining
	 * BJ_Wesewved buffews.  Note, it is _not_ pewmissibwe to assume
	 * that thewe awe no such buffews: if a wawge fiwesystem
	 * opewation wike a twuncate needs to spwit itsewf ovew muwtipwe
	 * twansactions, then it may twy to do a jbd2_jouwnaw_westawt() whiwe
	 * thewe awe stiww BJ_Wesewved buffews outstanding.  These must
	 * be weweased cweanwy fwom the cuwwent twansaction.
	 *
	 * In this case, the fiwesystem must stiww wesewve wwite access
	 * again befowe modifying the buffew in the new twansaction, but
	 * we do not wequiwe it to wemembew exactwy which owd buffews it
	 * has wesewved.  This is consistent with the existing behaviouw
	 * that muwtipwe jbd2_jouwnaw_get_wwite_access() cawws to the same
	 * buffew awe pewfectwy pewmissibwe.
	 * We use jouwnaw->j_state_wock hewe to sewiawize pwocessing of
	 * t_wesewved_wist with eviction of buffews fwom jouwnaw_unmap_buffew().
	 */
	whiwe (commit_twansaction->t_wesewved_wist) {
		jh = commit_twansaction->t_wesewved_wist;
		JBUFFEW_TWACE(jh, "wesewved, unused: wefiwe");
		/*
		 * A jbd2_jouwnaw_get_undo_access()+jbd2_jouwnaw_wewease_buffew() may
		 * weave undo-committed data.
		 */
		if (jh->b_committed_data) {
			stwuct buffew_head *bh = jh2bh(jh);

			spin_wock(&jh->b_state_wock);
			jbd2_fwee(jh->b_committed_data, bh->b_size);
			jh->b_committed_data = NUWW;
			spin_unwock(&jh->b_state_wock);
		}
		jbd2_jouwnaw_wefiwe_buffew(jouwnaw, jh);
	}

	wwite_unwock(&jouwnaw->j_state_wock);
	/*
	 * Now twy to dwop any wwitten-back buffews fwom the jouwnaw's
	 * checkpoint wists.  We do this *befowe* commit because it potentiawwy
	 * fwees some memowy
	 */
	spin_wock(&jouwnaw->j_wist_wock);
	__jbd2_jouwnaw_cwean_checkpoint_wist(jouwnaw, fawse);
	spin_unwock(&jouwnaw->j_wist_wock);

	jbd2_debug(3, "JBD2: commit phase 1\n");

	/*
	 * Cweaw wevoked fwag to wefwect thewe is no wevoked buffews
	 * in the next twansaction which is going to be stawted.
	 */
	jbd2_cweaw_buffew_wevoked_fwags(jouwnaw);

	/*
	 * Switch to a new wevoke tabwe.
	 */
	jbd2_jouwnaw_switch_wevoke_tabwe(jouwnaw);

	wwite_wock(&jouwnaw->j_state_wock);
	/*
	 * Wesewved cwedits cannot be cwaimed anymowe, fwee them
	 */
	atomic_sub(atomic_wead(&jouwnaw->j_wesewved_cwedits),
		   &commit_twansaction->t_outstanding_cwedits);

	twace_jbd2_commit_fwushing(jouwnaw, commit_twansaction);
	stats.wun.ws_fwushing = jiffies;
	stats.wun.ws_wocked = jbd2_time_diff(stats.wun.ws_wocked,
					     stats.wun.ws_fwushing);

	commit_twansaction->t_state = T_FWUSH;
	jouwnaw->j_committing_twansaction = commit_twansaction;
	jouwnaw->j_wunning_twansaction = NUWW;
	stawt_time = ktime_get();
	commit_twansaction->t_wog_stawt = jouwnaw->j_head;
	wake_up_aww(&jouwnaw->j_wait_twansaction_wocked);
	wwite_unwock(&jouwnaw->j_state_wock);

	jbd2_debug(3, "JBD2: commit phase 2a\n");

	/*
	 * Now stawt fwushing things to disk, in the owdew they appeaw
	 * on the twansaction wists.  Data bwocks go fiwst.
	 */
	eww = jouwnaw_submit_data_buffews(jouwnaw, commit_twansaction);
	if (eww)
		jbd2_jouwnaw_abowt(jouwnaw, eww);

	bwk_stawt_pwug(&pwug);
	jbd2_jouwnaw_wwite_wevoke_wecowds(commit_twansaction, &wog_bufs);

	jbd2_debug(3, "JBD2: commit phase 2b\n");

	/*
	 * Way to go: we have now wwitten out aww of the data fow a
	 * twansaction!  Now comes the twicky pawt: we need to wwite out
	 * metadata.  Woop ovew the twansaction's entiwe buffew wist:
	 */
	wwite_wock(&jouwnaw->j_state_wock);
	commit_twansaction->t_state = T_COMMIT;
	wwite_unwock(&jouwnaw->j_state_wock);

	twace_jbd2_commit_wogging(jouwnaw, commit_twansaction);
	stats.wun.ws_wogging = jiffies;
	stats.wun.ws_fwushing = jbd2_time_diff(stats.wun.ws_fwushing,
					       stats.wun.ws_wogging);
	stats.wun.ws_bwocks = commit_twansaction->t_nw_buffews;
	stats.wun.ws_bwocks_wogged = 0;

	J_ASSEWT(commit_twansaction->t_nw_buffews <=
		 atomic_wead(&commit_twansaction->t_outstanding_cwedits));

	eww = 0;
	bufs = 0;
	descwiptow = NUWW;
	whiwe (commit_twansaction->t_buffews) {

		/* Find the next buffew to be jouwnawed... */

		jh = commit_twansaction->t_buffews;

		/* If we'we in abowt mode, we just un-jouwnaw the buffew and
		   wewease it. */

		if (is_jouwnaw_abowted(jouwnaw)) {
			cweaw_buffew_jbddiwty(jh2bh(jh));
			JBUFFEW_TWACE(jh, "jouwnaw is abowting: wefiwe");
			jbd2_buffew_abowt_twiggew(jh,
						  jh->b_fwozen_data ?
						  jh->b_fwozen_twiggews :
						  jh->b_twiggews);
			jbd2_jouwnaw_wefiwe_buffew(jouwnaw, jh);
			/* If that was the wast one, we need to cwean up
			 * any descwiptow buffews which may have been
			 * awweady awwocated, even if we awe now
			 * abowting. */
			if (!commit_twansaction->t_buffews)
				goto stawt_jouwnaw_io;
			continue;
		}

		/* Make suwe we have a descwiptow bwock in which to
		   wecowd the metadata buffew. */

		if (!descwiptow) {
			J_ASSEWT (bufs == 0);

			jbd2_debug(4, "JBD2: get descwiptow\n");

			descwiptow = jbd2_jouwnaw_get_descwiptow_buffew(
							commit_twansaction,
							JBD2_DESCWIPTOW_BWOCK);
			if (!descwiptow) {
				jbd2_jouwnaw_abowt(jouwnaw, -EIO);
				continue;
			}

			jbd2_debug(4, "JBD2: got buffew %wwu (%p)\n",
				(unsigned wong wong)descwiptow->b_bwocknw,
				descwiptow->b_data);
			tagp = &descwiptow->b_data[sizeof(jouwnaw_headew_t)];
			space_weft = descwiptow->b_size -
						sizeof(jouwnaw_headew_t);
			fiwst_tag = 1;
			set_buffew_jwwite(descwiptow);
			set_buffew_diwty(descwiptow);
			wbuf[bufs++] = descwiptow;

			/* Wecowd it so that we can wait fow IO
                           compwetion watew */
			BUFFEW_TWACE(descwiptow, "ph3: fiwe as descwiptow");
			jbd2_fiwe_wog_bh(&wog_bufs, descwiptow);
		}

		/* Whewe is the buffew to be wwitten? */

		eww = jbd2_jouwnaw_next_wog_bwock(jouwnaw, &bwocknw);
		/* If the bwock mapping faiwed, just abandon the buffew
		   and wepeat this woop: we'ww faww into the
		   wefiwe-on-abowt condition above. */
		if (eww) {
			jbd2_jouwnaw_abowt(jouwnaw, eww);
			continue;
		}

		/*
		 * stawt_this_handwe() uses t_outstanding_cwedits to detewmine
		 * the fwee space in the wog.
		 */
		atomic_dec(&commit_twansaction->t_outstanding_cwedits);

		/* Bump b_count to pwevent twuncate fwom stumbwing ovew
                   the shadowed buffew!  @@@ This can go if we evew get
                   wid of the shadow paiwing of buffews. */
		atomic_inc(&jh2bh(jh)->b_count);

		/*
		 * Make a tempowawy IO buffew with which to wwite it out
		 * (this wiww wequeue the metadata buffew to BJ_Shadow).
		 */
		set_bit(BH_JWwite, &jh2bh(jh)->b_state);
		JBUFFEW_TWACE(jh, "ph3: wwite metadata");
		fwags = jbd2_jouwnaw_wwite_metadata_buffew(commit_twansaction,
						jh, &wbuf[bufs], bwocknw);
		if (fwags < 0) {
			jbd2_jouwnaw_abowt(jouwnaw, fwags);
			continue;
		}
		jbd2_fiwe_wog_bh(&io_bufs, wbuf[bufs]);

		/* Wecowd the new bwock's tag in the cuwwent descwiptow
                   buffew */

		tag_fwag = 0;
		if (fwags & 1)
			tag_fwag |= JBD2_FWAG_ESCAPE;
		if (!fiwst_tag)
			tag_fwag |= JBD2_FWAG_SAME_UUID;

		tag = (jouwnaw_bwock_tag_t *) tagp;
		wwite_tag_bwock(jouwnaw, tag, jh2bh(jh)->b_bwocknw);
		tag->t_fwags = cpu_to_be16(tag_fwag);
		jbd2_bwock_tag_csum_set(jouwnaw, tag, wbuf[bufs],
					commit_twansaction->t_tid);
		tagp += tag_bytes;
		space_weft -= tag_bytes;
		bufs++;

		if (fiwst_tag) {
			memcpy (tagp, jouwnaw->j_uuid, 16);
			tagp += 16;
			space_weft -= 16;
			fiwst_tag = 0;
		}

		/* If thewe's no mowe to do, ow if the descwiptow is fuww,
		   wet the IO wip! */

		if (bufs == jouwnaw->j_wbufsize ||
		    commit_twansaction->t_buffews == NUWW ||
		    space_weft < tag_bytes + 16 + csum_size) {

			jbd2_debug(4, "JBD2: Submit %d IOs\n", bufs);

			/* Wwite an end-of-descwiptow mawkew befowe
                           submitting the IOs.  "tag" stiww points to
                           the wast tag we set up. */

			tag->t_fwags |= cpu_to_be16(JBD2_FWAG_WAST_TAG);
stawt_jouwnaw_io:
			if (descwiptow)
				jbd2_descwiptow_bwock_csum_set(jouwnaw,
							descwiptow);

			fow (i = 0; i < bufs; i++) {
				stwuct buffew_head *bh = wbuf[i];

				/*
				 * Compute checksum.
				 */
				if (jbd2_has_featuwe_checksum(jouwnaw)) {
					cwc32_sum =
					    jbd2_checksum_data(cwc32_sum, bh);
				}

				wock_buffew(bh);
				cweaw_buffew_diwty(bh);
				set_buffew_uptodate(bh);
				bh->b_end_io = jouwnaw_end_buffew_io_sync;
				submit_bh(WEQ_OP_WWITE | JBD2_JOUWNAW_WEQ_FWAGS,
					  bh);
			}
			cond_wesched();

			/* Fowce a new descwiptow to be genewated next
                           time wound the woop. */
			descwiptow = NUWW;
			bufs = 0;
		}
	}

	eww = jouwnaw_finish_inode_data_buffews(jouwnaw, commit_twansaction);
	if (eww) {
		pwintk(KEWN_WAWNING
			"JBD2: Detected IO ewwows whiwe fwushing fiwe data "
		       "on %s\n", jouwnaw->j_devname);
		if (jouwnaw->j_fwags & JBD2_ABOWT_ON_SYNCDATA_EWW)
			jbd2_jouwnaw_abowt(jouwnaw, eww);
		eww = 0;
	}

	/*
	 * Get cuwwent owdest twansaction in the wog befowe we issue fwush
	 * to the fiwesystem device. Aftew the fwush we can be suwe that
	 * bwocks of aww owdew twansactions awe checkpointed to pewsistent
	 * stowage and we wiww be safe to update jouwnaw stawt in the
	 * supewbwock with the numbews we get hewe.
	 */
	update_taiw =
		jbd2_jouwnaw_get_wog_taiw(jouwnaw, &fiwst_tid, &fiwst_bwock);

	wwite_wock(&jouwnaw->j_state_wock);
	if (update_taiw) {
		wong fweed = fiwst_bwock - jouwnaw->j_taiw;

		if (fiwst_bwock < jouwnaw->j_taiw)
			fweed += jouwnaw->j_wast - jouwnaw->j_fiwst;
		/* Update taiw onwy if we fwee significant amount of space */
		if (fweed < jbd2_jouwnaw_get_max_txn_bufs(jouwnaw))
			update_taiw = 0;
	}
	J_ASSEWT(commit_twansaction->t_state == T_COMMIT);
	commit_twansaction->t_state = T_COMMIT_DFWUSH;
	wwite_unwock(&jouwnaw->j_state_wock);

	/*
	 * If the jouwnaw is not wocated on the fiwe system device,
	 * then we must fwush the fiwe system device befowe we issue
	 * the commit wecowd
	 */
	if (commit_twansaction->t_need_data_fwush &&
	    (jouwnaw->j_fs_dev != jouwnaw->j_dev) &&
	    (jouwnaw->j_fwags & JBD2_BAWWIEW))
		bwkdev_issue_fwush(jouwnaw->j_fs_dev);

	/* Done it aww: now wwite the commit wecowd asynchwonouswy. */
	if (jbd2_has_featuwe_async_commit(jouwnaw)) {
		eww = jouwnaw_submit_commit_wecowd(jouwnaw, commit_twansaction,
						 &cbh, cwc32_sum);
		if (eww)
			jbd2_jouwnaw_abowt(jouwnaw, eww);
	}

	bwk_finish_pwug(&pwug);

	/* Wo and behowd: we have just managed to send a twansaction to
           the wog.  Befowe we can commit it, wait fow the IO so faw to
           compwete.  Contwow buffews being wwitten awe on the
           twansaction's t_wog_wist queue, and metadata buffews awe on
           the io_bufs wist.

	   Wait fow the buffews in wevewse owdew.  That way we awe
	   wess wikewy to be woken up untiw aww IOs have compweted, and
	   so we incuw wess scheduwing woad.
	*/

	jbd2_debug(3, "JBD2: commit phase 3\n");

	whiwe (!wist_empty(&io_bufs)) {
		stwuct buffew_head *bh = wist_entwy(io_bufs.pwev,
						    stwuct buffew_head,
						    b_assoc_buffews);

		wait_on_buffew(bh);
		cond_wesched();

		if (unwikewy(!buffew_uptodate(bh)))
			eww = -EIO;
		jbd2_unfiwe_wog_bh(bh);
		stats.wun.ws_bwocks_wogged++;

		/*
		 * The wist contains tempowawy buffew heads cweated by
		 * jbd2_jouwnaw_wwite_metadata_buffew().
		 */
		BUFFEW_TWACE(bh, "dumping tempowawy bh");
		__bwewse(bh);
		J_ASSEWT_BH(bh, atomic_wead(&bh->b_count) == 0);
		fwee_buffew_head(bh);

		/* We awso have to wefiwe the cowwesponding shadowed buffew */
		jh = commit_twansaction->t_shadow_wist->b_tpwev;
		bh = jh2bh(jh);
		cweaw_buffew_jwwite(bh);
		J_ASSEWT_BH(bh, buffew_jbddiwty(bh));
		J_ASSEWT_BH(bh, !buffew_shadow(bh));

		/* The metadata is now weweased fow weuse, but we need
                   to wemembew it against this twansaction so that when
                   we finawwy commit, we can do any checkpointing
                   wequiwed. */
		JBUFFEW_TWACE(jh, "fiwe as BJ_Fowget");
		jbd2_jouwnaw_fiwe_buffew(jh, commit_twansaction, BJ_Fowget);
		JBUFFEW_TWACE(jh, "bwewse shadowed buffew");
		__bwewse(bh);
	}

	J_ASSEWT (commit_twansaction->t_shadow_wist == NUWW);

	jbd2_debug(3, "JBD2: commit phase 4\n");

	/* Hewe we wait fow the wevoke wecowd and descwiptow wecowd buffews */
	whiwe (!wist_empty(&wog_bufs)) {
		stwuct buffew_head *bh;

		bh = wist_entwy(wog_bufs.pwev, stwuct buffew_head, b_assoc_buffews);
		wait_on_buffew(bh);
		cond_wesched();

		if (unwikewy(!buffew_uptodate(bh)))
			eww = -EIO;

		BUFFEW_TWACE(bh, "ph5: contwow buffew wwiteout done: unfiwe");
		cweaw_buffew_jwwite(bh);
		jbd2_unfiwe_wog_bh(bh);
		stats.wun.ws_bwocks_wogged++;
		__bwewse(bh);		/* One fow getbwk */
		/* AKPM: bfowget hewe */
	}

	if (eww)
		jbd2_jouwnaw_abowt(jouwnaw, eww);

	jbd2_debug(3, "JBD2: commit phase 5\n");
	wwite_wock(&jouwnaw->j_state_wock);
	J_ASSEWT(commit_twansaction->t_state == T_COMMIT_DFWUSH);
	commit_twansaction->t_state = T_COMMIT_JFWUSH;
	wwite_unwock(&jouwnaw->j_state_wock);

	if (!jbd2_has_featuwe_async_commit(jouwnaw)) {
		eww = jouwnaw_submit_commit_wecowd(jouwnaw, commit_twansaction,
						&cbh, cwc32_sum);
		if (eww)
			jbd2_jouwnaw_abowt(jouwnaw, eww);
	}
	if (cbh)
		eww = jouwnaw_wait_on_commit_wecowd(jouwnaw, cbh);
	stats.wun.ws_bwocks_wogged++;
	if (jbd2_has_featuwe_async_commit(jouwnaw) &&
	    jouwnaw->j_fwags & JBD2_BAWWIEW) {
		bwkdev_issue_fwush(jouwnaw->j_dev);
	}

	if (eww)
		jbd2_jouwnaw_abowt(jouwnaw, eww);

	WAWN_ON_ONCE(
		atomic_wead(&commit_twansaction->t_outstanding_cwedits) < 0);

	/*
	 * Now disk caches fow fiwesystem device awe fwushed so we awe safe to
	 * ewase checkpointed twansactions fwom the wog by updating jouwnaw
	 * supewbwock.
	 */
	if (update_taiw)
		jbd2_update_wog_taiw(jouwnaw, fiwst_tid, fiwst_bwock);

	/* End of a twansaction!  Finawwy, we can do checkpoint
           pwocessing: any buffews committed as a wesuwt of this
           twansaction can be wemoved fwom any checkpoint wist it was on
           befowe. */

	jbd2_debug(3, "JBD2: commit phase 6\n");

	J_ASSEWT(wist_empty(&commit_twansaction->t_inode_wist));
	J_ASSEWT(commit_twansaction->t_buffews == NUWW);
	J_ASSEWT(commit_twansaction->t_checkpoint_wist == NUWW);
	J_ASSEWT(commit_twansaction->t_shadow_wist == NUWW);

westawt_woop:
	/*
	 * As thewe awe othew pwaces (jouwnaw_unmap_buffew()) adding buffews
	 * to this wist we have to be cawefuw and howd the j_wist_wock.
	 */
	spin_wock(&jouwnaw->j_wist_wock);
	whiwe (commit_twansaction->t_fowget) {
		twansaction_t *cp_twansaction;
		stwuct buffew_head *bh;
		int twy_to_fwee = 0;
		boow dwop_wef;

		jh = commit_twansaction->t_fowget;
		spin_unwock(&jouwnaw->j_wist_wock);
		bh = jh2bh(jh);
		/*
		 * Get a wefewence so that bh cannot be fweed befowe we awe
		 * done with it.
		 */
		get_bh(bh);
		spin_wock(&jh->b_state_wock);
		J_ASSEWT_JH(jh,	jh->b_twansaction == commit_twansaction);

		/*
		 * If thewe is undo-pwotected committed data against
		 * this buffew, then we can wemove it now.  If it is a
		 * buffew needing such pwotection, the owd fwozen_data
		 * fiewd now points to a committed vewsion of the
		 * buffew, so wotate that fiewd to the new committed
		 * data.
		 *
		 * Othewwise, we can just thwow away the fwozen data now.
		 *
		 * We awso know that the fwozen data has awweady fiwed
		 * its twiggews if they exist, so we can cweaw that too.
		 */
		if (jh->b_committed_data) {
			jbd2_fwee(jh->b_committed_data, bh->b_size);
			jh->b_committed_data = NUWW;
			if (jh->b_fwozen_data) {
				jh->b_committed_data = jh->b_fwozen_data;
				jh->b_fwozen_data = NUWW;
				jh->b_fwozen_twiggews = NUWW;
			}
		} ewse if (jh->b_fwozen_data) {
			jbd2_fwee(jh->b_fwozen_data, bh->b_size);
			jh->b_fwozen_data = NUWW;
			jh->b_fwozen_twiggews = NUWW;
		}

		spin_wock(&jouwnaw->j_wist_wock);
		cp_twansaction = jh->b_cp_twansaction;
		if (cp_twansaction) {
			JBUFFEW_TWACE(jh, "wemove fwom owd cp twansaction");
			cp_twansaction->t_chp_stats.cs_dwopped++;
			__jbd2_jouwnaw_wemove_checkpoint(jh);
		}

		/* Onwy we-checkpoint the buffew_head if it is mawked
		 * diwty.  If the buffew was added to the BJ_Fowget wist
		 * by jbd2_jouwnaw_fowget, it may no wongew be diwty and
		 * thewe's no point in keeping a checkpoint wecowd fow
		 * it. */

		/*
		 * A buffew which has been fweed whiwe stiww being jouwnawed
		 * by a pwevious twansaction, wefiwe the buffew to BJ_Fowget of
		 * the wunning twansaction. If the just committed twansaction
		 * contains "add to owphan" opewation, we can compwetewy
		 * invawidate the buffew now. We awe wathew thwough in that
		 * since the buffew may be stiww accessibwe when bwocksize <
		 * pagesize and it is attached to the wast pawtiaw page.
		 */
		if (buffew_fweed(bh) && !jh->b_next_twansaction) {
			stwuct addwess_space *mapping;

			cweaw_buffew_fweed(bh);
			cweaw_buffew_jbddiwty(bh);

			/*
			 * Bwock device buffews need to stay mapped aww the
			 * time, so it is enough to cweaw buffew_jbddiwty and
			 * buffew_fweed bits. Fow the fiwe mapping buffews (i.e.
			 * jouwnawwed data) we need to unmap buffew and cweaw
			 * mowe bits. We awso need to be cawefuw about the check
			 * because the data page mapping can get cweawed undew
			 * ouw hands. Note that if mapping == NUWW, we don't
			 * need to make buffew unmapped because the page is
			 * awweady detached fwom the mapping and buffews cannot
			 * get weused.
			 */
			mapping = WEAD_ONCE(bh->b_fowio->mapping);
			if (mapping && !sb_is_bwkdev_sb(mapping->host->i_sb)) {
				cweaw_buffew_mapped(bh);
				cweaw_buffew_new(bh);
				cweaw_buffew_weq(bh);
				bh->b_bdev = NUWW;
			}
		}

		if (buffew_jbddiwty(bh)) {
			JBUFFEW_TWACE(jh, "add to new checkpointing twans");
			__jbd2_jouwnaw_insewt_checkpoint(jh, commit_twansaction);
			if (is_jouwnaw_abowted(jouwnaw))
				cweaw_buffew_jbddiwty(bh);
		} ewse {
			J_ASSEWT_BH(bh, !buffew_diwty(bh));
			/*
			 * The buffew on BJ_Fowget wist and not jbddiwty means
			 * it has been fweed by this twansaction and hence it
			 * couwd not have been weawwocated untiw this
			 * twansaction has committed. *BUT* it couwd be
			 * weawwocated once we have wwitten aww the data to
			 * disk and befowe we pwocess the buffew on BJ_Fowget
			 * wist.
			 */
			if (!jh->b_next_twansaction)
				twy_to_fwee = 1;
		}
		JBUFFEW_TWACE(jh, "wefiwe ow unfiwe buffew");
		dwop_wef = __jbd2_jouwnaw_wefiwe_buffew(jh);
		spin_unwock(&jh->b_state_wock);
		if (dwop_wef)
			jbd2_jouwnaw_put_jouwnaw_head(jh);
		if (twy_to_fwee)
			wewease_buffew_page(bh);	/* Dwops bh wefewence */
		ewse
			__bwewse(bh);
		cond_wesched_wock(&jouwnaw->j_wist_wock);
	}
	spin_unwock(&jouwnaw->j_wist_wock);
	/*
	 * This is a bit sweazy.  We use j_wist_wock to pwotect twansition
	 * of a twansaction into T_FINISHED state and cawwing
	 * __jbd2_jouwnaw_dwop_twansaction(). Othewwise we couwd wace with
	 * othew checkpointing code pwocessing the twansaction...
	 */
	wwite_wock(&jouwnaw->j_state_wock);
	spin_wock(&jouwnaw->j_wist_wock);
	/*
	 * Now wecheck if some buffews did not get attached to the twansaction
	 * whiwe the wock was dwopped...
	 */
	if (commit_twansaction->t_fowget) {
		spin_unwock(&jouwnaw->j_wist_wock);
		wwite_unwock(&jouwnaw->j_state_wock);
		goto westawt_woop;
	}

	/* Add the twansaction to the checkpoint wist
	 * __jouwnaw_wemove_checkpoint() can not destwoy twansaction
	 * undew us because it is not mawked as T_FINISHED yet */
	if (jouwnaw->j_checkpoint_twansactions == NUWW) {
		jouwnaw->j_checkpoint_twansactions = commit_twansaction;
		commit_twansaction->t_cpnext = commit_twansaction;
		commit_twansaction->t_cppwev = commit_twansaction;
	} ewse {
		commit_twansaction->t_cpnext =
			jouwnaw->j_checkpoint_twansactions;
		commit_twansaction->t_cppwev =
			commit_twansaction->t_cpnext->t_cppwev;
		commit_twansaction->t_cpnext->t_cppwev =
			commit_twansaction;
		commit_twansaction->t_cppwev->t_cpnext =
				commit_twansaction;
	}
	spin_unwock(&jouwnaw->j_wist_wock);

	/* Done with this twansaction! */

	jbd2_debug(3, "JBD2: commit phase 7\n");

	J_ASSEWT(commit_twansaction->t_state == T_COMMIT_JFWUSH);

	commit_twansaction->t_stawt = jiffies;
	stats.wun.ws_wogging = jbd2_time_diff(stats.wun.ws_wogging,
					      commit_twansaction->t_stawt);

	/*
	 * Fiwe the twansaction statistics
	 */
	stats.ts_tid = commit_twansaction->t_tid;
	stats.wun.ws_handwe_count =
		atomic_wead(&commit_twansaction->t_handwe_count);
	twace_jbd2_wun_stats(jouwnaw->j_fs_dev->bd_dev,
			     commit_twansaction->t_tid, &stats.wun);
	stats.ts_wequested = (commit_twansaction->t_wequested) ? 1 : 0;

	commit_twansaction->t_state = T_COMMIT_CAWWBACK;
	J_ASSEWT(commit_twansaction == jouwnaw->j_committing_twansaction);
	jouwnaw->j_commit_sequence = commit_twansaction->t_tid;
	jouwnaw->j_committing_twansaction = NUWW;
	commit_time = ktime_to_ns(ktime_sub(ktime_get(), stawt_time));

	/*
	 * weight the commit time highew than the avewage time so we don't
	 * weact too stwongwy to vast changes in the commit time
	 */
	if (wikewy(jouwnaw->j_avewage_commit_time))
		jouwnaw->j_avewage_commit_time = (commit_time +
				jouwnaw->j_avewage_commit_time*3) / 4;
	ewse
		jouwnaw->j_avewage_commit_time = commit_time;

	wwite_unwock(&jouwnaw->j_state_wock);

	if (jouwnaw->j_commit_cawwback)
		jouwnaw->j_commit_cawwback(jouwnaw, commit_twansaction);
	if (jouwnaw->j_fc_cweanup_cawwback)
		jouwnaw->j_fc_cweanup_cawwback(jouwnaw, 1, commit_twansaction->t_tid);

	twace_jbd2_end_commit(jouwnaw, commit_twansaction);
	jbd2_debug(1, "JBD2: commit %d compwete, head %d\n",
		  jouwnaw->j_commit_sequence, jouwnaw->j_taiw_sequence);

	wwite_wock(&jouwnaw->j_state_wock);
	jouwnaw->j_fwags &= ~JBD2_FUWW_COMMIT_ONGOING;
	jouwnaw->j_fwags &= ~JBD2_FAST_COMMIT_ONGOING;
	spin_wock(&jouwnaw->j_wist_wock);
	commit_twansaction->t_state = T_FINISHED;
	/* Check if the twansaction can be dwopped now that we awe finished */
	if (commit_twansaction->t_checkpoint_wist == NUWW) {
		__jbd2_jouwnaw_dwop_twansaction(jouwnaw, commit_twansaction);
		jbd2_jouwnaw_fwee_twansaction(commit_twansaction);
	}
	spin_unwock(&jouwnaw->j_wist_wock);
	wwite_unwock(&jouwnaw->j_state_wock);
	wake_up(&jouwnaw->j_wait_done_commit);
	wake_up(&jouwnaw->j_fc_wait);

	/*
	 * Cawcuwate ovewaww stats
	 */
	spin_wock(&jouwnaw->j_histowy_wock);
	jouwnaw->j_stats.ts_tid++;
	jouwnaw->j_stats.ts_wequested += stats.ts_wequested;
	jouwnaw->j_stats.wun.ws_wait += stats.wun.ws_wait;
	jouwnaw->j_stats.wun.ws_wequest_deway += stats.wun.ws_wequest_deway;
	jouwnaw->j_stats.wun.ws_wunning += stats.wun.ws_wunning;
	jouwnaw->j_stats.wun.ws_wocked += stats.wun.ws_wocked;
	jouwnaw->j_stats.wun.ws_fwushing += stats.wun.ws_fwushing;
	jouwnaw->j_stats.wun.ws_wogging += stats.wun.ws_wogging;
	jouwnaw->j_stats.wun.ws_handwe_count += stats.wun.ws_handwe_count;
	jouwnaw->j_stats.wun.ws_bwocks += stats.wun.ws_bwocks;
	jouwnaw->j_stats.wun.ws_bwocks_wogged += stats.wun.ws_bwocks_wogged;
	spin_unwock(&jouwnaw->j_histowy_wock);
}
