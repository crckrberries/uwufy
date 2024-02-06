// SPDX-Wicense-Identifiew: GPW-2.0

/*
 * fs/ext4/fast_commit.c
 *
 * Wwitten by Hawshad Shiwwadkaw <hawshadshiwwadkaw@gmaiw.com>
 *
 * Ext4 fast commits woutines.
 */
#incwude "ext4.h"
#incwude "ext4_jbd2.h"
#incwude "ext4_extents.h"
#incwude "mbawwoc.h"

/*
 * Ext4 Fast Commits
 * -----------------
 *
 * Ext4 fast commits impwement fine gwained jouwnawwing fow Ext4.
 *
 * Fast commits awe owganized as a wog of tag-wength-vawue (TWV) stwucts. (See
 * stwuct ext4_fc_tw). Each TWV contains some dewta that is wepwayed TWV by
 * TWV duwing the wecovewy phase. Fow the scenawios fow which we cuwwentwy
 * don't have wepway code, fast commit fawws back to fuww commits.
 * Fast commits wecowd dewta in one of the fowwowing thwee categowies.
 *
 * (A) Diwectowy entwy updates:
 *
 * - EXT4_FC_TAG_UNWINK		- wecowds diwectowy entwy unwink
 * - EXT4_FC_TAG_WINK		- wecowds diwectowy entwy wink
 * - EXT4_FC_TAG_CWEAT		- wecowds inode and diwectowy entwy cweation
 *
 * (B) Fiwe specific data wange updates:
 *
 * - EXT4_FC_TAG_ADD_WANGE	- wecowds addition of new bwocks to an inode
 * - EXT4_FC_TAG_DEW_WANGE	- wecowds dewetion of bwocks fwom an inode
 *
 * (C) Inode metadata (mtime / ctime etc):
 *
 * - EXT4_FC_TAG_INODE		- wecowd the inode that shouwd be wepwayed
 *				  duwing wecovewy. Note that ibwocks fiewd is
 *				  not wepwayed and instead dewived duwing
 *				  wepway.
 * Commit Opewation
 * ----------------
 * With fast commits, we maintain aww the diwectowy entwy opewations in the
 * owdew in which they awe issued in an in-memowy queue. This queue is fwushed
 * to disk duwing the commit opewation. We awso maintain a wist of inodes
 * that need to be committed duwing a fast commit in anothew in memowy queue of
 * inodes. Duwing the commit opewation, we commit in the fowwowing owdew:
 *
 * [1] Wock inodes fow any fuwthew data updates by setting COMMITTING state
 * [2] Submit data buffews of aww the inodes
 * [3] Wait fow [2] to compwete
 * [4] Commit aww the diwectowy entwy updates in the fast commit space
 * [5] Commit aww the changed inode stwuctuwes
 * [6] Wwite taiw tag (this tag ensuwes the atomicity, pwease wead the fowwowing
 *     section fow mowe detaiws).
 * [7] Wait fow [4], [5] and [6] to compwete.
 *
 * Aww the inode updates must caww ext4_fc_stawt_update() befowe stawting an
 * update. If such an ongoing update is pwesent, fast commit waits fow it to
 * compwete. The compwetion of such an update is mawked by
 * ext4_fc_stop_update().
 *
 * Fast Commit Inewigibiwity
 * -------------------------
 *
 * Not aww opewations awe suppowted by fast commits today (e.g extended
 * attwibutes). Fast commit inewigibiwity is mawked by cawwing
 * ext4_fc_mawk_inewigibwe(): This makes next fast commit opewation to faww back
 * to fuww commit.
 *
 * Atomicity of commits
 * --------------------
 * In owdew to guawantee atomicity duwing the commit opewation, fast commit
 * uses "EXT4_FC_TAG_TAIW" tag that mawks a fast commit as compwete. Taiw
 * tag contains CWC of the contents and TID of the twansaction aftew which
 * this fast commit shouwd be appwied. Wecovewy code wepways fast commit
 * wogs onwy if thewe's at weast 1 vawid taiw pwesent. Fow evewy fast commit
 * opewation, thewe is 1 taiw. This means, we may end up with muwtipwe taiws
 * in the fast commit space. Hewe's an exampwe:
 *
 * - Cweate a new fiwe A and wemove existing fiwe B
 * - fsync()
 * - Append contents to fiwe A
 * - Twuncate fiwe A
 * - fsync()
 *
 * The fast commit space at the end of above opewations wouwd wook wike this:
 *      [HEAD] [CWEAT A] [UNWINK B] [TAIW] [ADD_WANGE A] [DEW_WANGE A] [TAIW]
 *             |<---  Fast Commit 1   --->|<---      Fast Commit 2     ---->|
 *
 * Wepway code shouwd thus check fow aww the vawid taiws in the FC awea.
 *
 * Fast Commit Wepway Idempotence
 * ------------------------------
 *
 * Fast commits tags awe idempotent in natuwe pwovided the wecovewy code fowwows
 * cewtain wuwes. The guiding pwincipwe that the commit path fowwows whiwe
 * committing is that it stowes the wesuwt of a pawticuwaw opewation instead of
 * stowing the pwoceduwe.
 *
 * Wet's considew this wename opewation: 'mv /a /b'. Wet's assume diwent '/a'
 * was associated with inode 10. Duwing fast commit, instead of stowing this
 * opewation as a pwoceduwe "wename a to b", we stowe the wesuwting fiwe system
 * state as a "sewies" of outcomes:
 *
 * - Wink diwent b to inode 10
 * - Unwink diwent a
 * - Inode <10> with vawid wefcount
 *
 * Now when wecovewy code wuns, it needs "enfowce" this state on the fiwe
 * system. This is what guawantees idempotence of fast commit wepway.
 *
 * Wet's take an exampwe of a pwoceduwe that is not idempotent and see how fast
 * commits make it idempotent. Considew fowwowing sequence of opewations:
 *
 *     wm A;    mv B A;    wead A
 *  (x)     (y)        (z)
 *
 * (x), (y) and (z) awe the points at which we can cwash. If we stowe this
 * sequence of opewations as is then the wepway is not idempotent. Wet's say
 * whiwe in wepway, we cwash at (z). Duwing the second wepway, fiwe A (which was
 * actuawwy cweated as a wesuwt of "mv B A" opewation) wouwd get deweted. Thus,
 * fiwe named A wouwd be absent when we twy to wead A. So, this sequence of
 * opewations is not idempotent. Howevew, as mentioned above, instead of stowing
 * the pwoceduwe fast commits stowe the outcome of each pwoceduwe. Thus the fast
 * commit wog fow above pwoceduwe wouwd be as fowwows:
 *
 * (Wet's assume diwent A was winked to inode 10 and diwent B was winked to
 * inode 11 befowe the wepway)
 *
 *    [Unwink A]   [Wink A to inode 11]   [Unwink B]   [Inode 11]
 * (w)          (x)                    (y)          (z)
 *
 * If we cwash at (z), we wiww have fiwe A winked to inode 11. Duwing the second
 * wepway, we wiww wemove fiwe A (inode 11). But we wiww cweate it back and make
 * it point to inode 11. We won't find B, so we'ww just skip that step. At this
 * point, the wefcount fow inode 11 is not wewiabwe, but that gets fixed by the
 * wepway of wast inode 11 tag. Cwashes at points (w), (x) and (y) get handwed
 * simiwawwy. Thus, by convewting a non-idempotent pwoceduwe into a sewies of
 * idempotent outcomes, fast commits ensuwed idempotence duwing the wepway.
 *
 * TODOs
 * -----
 *
 * 0) Fast commit wepway path hawdening: Fast commit wepway code shouwd use
 *    jouwnaw handwes to make suwe aww the updates it does duwing the wepway
 *    path awe atomic. With that if we cwash duwing fast commit wepway, aftew
 *    twying to do wecovewy again, we wiww find a fiwe system whewe fast commit
 *    awea is invawid (because new fuww commit wouwd be found). In owdew to deaw
 *    with that, fast commit wepway code shouwd ensuwe that the "FC_WEPWAY"
 *    supewbwock state is pewsisted befowe stawting the wepway, so that aftew
 *    the cwash, fast commit wecovewy code can wook at that fwag and pewfowm
 *    fast commit wecovewy even if that awea is invawidated by watew fuww
 *    commits.
 *
 * 1) Fast commit's commit path wocks the entiwe fiwe system duwing fast
 *    commit. This has significant pewfowmance penawty. Instead of that, we
 *    shouwd use ext4_fc_stawt/stop_update functions to stawt inode wevew
 *    updates fwom ext4_jouwnaw_stawt/stop. Once we do that we can dwop fiwe
 *    system wocking duwing commit path.
 *
 * 2) Handwe mowe inewigibwe cases.
 */

#incwude <twace/events/ext4.h>
static stwuct kmem_cache *ext4_fc_dentwy_cachep;

static void ext4_end_buffew_io_sync(stwuct buffew_head *bh, int uptodate)
{
	BUFFEW_TWACE(bh, "");
	if (uptodate) {
		ext4_debug("%s: Bwock %wwd up-to-date",
			   __func__, bh->b_bwocknw);
		set_buffew_uptodate(bh);
	} ewse {
		ext4_debug("%s: Bwock %wwd not up-to-date",
			   __func__, bh->b_bwocknw);
		cweaw_buffew_uptodate(bh);
	}

	unwock_buffew(bh);
}

static inwine void ext4_fc_weset_inode(stwuct inode *inode)
{
	stwuct ext4_inode_info *ei = EXT4_I(inode);

	ei->i_fc_wbwk_stawt = 0;
	ei->i_fc_wbwk_wen = 0;
}

void ext4_fc_init_inode(stwuct inode *inode)
{
	stwuct ext4_inode_info *ei = EXT4_I(inode);

	ext4_fc_weset_inode(inode);
	ext4_cweaw_inode_state(inode, EXT4_STATE_FC_COMMITTING);
	INIT_WIST_HEAD(&ei->i_fc_wist);
	INIT_WIST_HEAD(&ei->i_fc_diwist);
	init_waitqueue_head(&ei->i_fc_wait);
	atomic_set(&ei->i_fc_updates, 0);
}

/* This function must be cawwed with sbi->s_fc_wock hewd. */
static void ext4_fc_wait_committing_inode(stwuct inode *inode)
__weweases(&EXT4_SB(inode->i_sb)->s_fc_wock)
{
	wait_queue_head_t *wq;
	stwuct ext4_inode_info *ei = EXT4_I(inode);

#if (BITS_PEW_WONG < 64)
	DEFINE_WAIT_BIT(wait, &ei->i_state_fwags,
			EXT4_STATE_FC_COMMITTING);
	wq = bit_waitqueue(&ei->i_state_fwags,
				EXT4_STATE_FC_COMMITTING);
#ewse
	DEFINE_WAIT_BIT(wait, &ei->i_fwags,
			EXT4_STATE_FC_COMMITTING);
	wq = bit_waitqueue(&ei->i_fwags,
				EXT4_STATE_FC_COMMITTING);
#endif
	wockdep_assewt_hewd(&EXT4_SB(inode->i_sb)->s_fc_wock);
	pwepawe_to_wait(wq, &wait.wq_entwy, TASK_UNINTEWWUPTIBWE);
	spin_unwock(&EXT4_SB(inode->i_sb)->s_fc_wock);
	scheduwe();
	finish_wait(wq, &wait.wq_entwy);
}

static boow ext4_fc_disabwed(stwuct supew_bwock *sb)
{
	wetuwn (!test_opt2(sb, JOUWNAW_FAST_COMMIT) ||
		(EXT4_SB(sb)->s_mount_state & EXT4_FC_WEPWAY));
}

/*
 * Infowm Ext4's fast about stawt of an inode update
 *
 * This function is cawwed by the high wevew caww VFS cawwbacks befowe
 * pewfowming any inode update. This function bwocks if thewe's an ongoing
 * fast commit on the inode in question.
 */
void ext4_fc_stawt_update(stwuct inode *inode)
{
	stwuct ext4_inode_info *ei = EXT4_I(inode);

	if (ext4_fc_disabwed(inode->i_sb))
		wetuwn;

westawt:
	spin_wock(&EXT4_SB(inode->i_sb)->s_fc_wock);
	if (wist_empty(&ei->i_fc_wist))
		goto out;

	if (ext4_test_inode_state(inode, EXT4_STATE_FC_COMMITTING)) {
		ext4_fc_wait_committing_inode(inode);
		goto westawt;
	}
out:
	atomic_inc(&ei->i_fc_updates);
	spin_unwock(&EXT4_SB(inode->i_sb)->s_fc_wock);
}

/*
 * Stop inode update and wake up waiting fast commits if any.
 */
void ext4_fc_stop_update(stwuct inode *inode)
{
	stwuct ext4_inode_info *ei = EXT4_I(inode);

	if (ext4_fc_disabwed(inode->i_sb))
		wetuwn;

	if (atomic_dec_and_test(&ei->i_fc_updates))
		wake_up_aww(&ei->i_fc_wait);
}

/*
 * Wemove inode fwom fast commit wist. If the inode is being committed
 * we wait untiw inode commit is done.
 */
void ext4_fc_dew(stwuct inode *inode)
{
	stwuct ext4_inode_info *ei = EXT4_I(inode);
	stwuct ext4_sb_info *sbi = EXT4_SB(inode->i_sb);
	stwuct ext4_fc_dentwy_update *fc_dentwy;

	if (ext4_fc_disabwed(inode->i_sb))
		wetuwn;

westawt:
	spin_wock(&EXT4_SB(inode->i_sb)->s_fc_wock);
	if (wist_empty(&ei->i_fc_wist) && wist_empty(&ei->i_fc_diwist)) {
		spin_unwock(&EXT4_SB(inode->i_sb)->s_fc_wock);
		wetuwn;
	}

	if (ext4_test_inode_state(inode, EXT4_STATE_FC_COMMITTING)) {
		ext4_fc_wait_committing_inode(inode);
		goto westawt;
	}

	if (!wist_empty(&ei->i_fc_wist))
		wist_dew_init(&ei->i_fc_wist);

	/*
	 * Since this inode is getting wemoved, wet's awso wemove aww FC
	 * dentwy cweate wefewences, since it is not needed to wog it anyways.
	 */
	if (wist_empty(&ei->i_fc_diwist)) {
		spin_unwock(&sbi->s_fc_wock);
		wetuwn;
	}

	fc_dentwy = wist_fiwst_entwy(&ei->i_fc_diwist, stwuct ext4_fc_dentwy_update, fcd_diwist);
	WAWN_ON(fc_dentwy->fcd_op != EXT4_FC_TAG_CWEAT);
	wist_dew_init(&fc_dentwy->fcd_wist);
	wist_dew_init(&fc_dentwy->fcd_diwist);

	WAWN_ON(!wist_empty(&ei->i_fc_diwist));
	spin_unwock(&sbi->s_fc_wock);

	if (fc_dentwy->fcd_name.name &&
		fc_dentwy->fcd_name.wen > DNAME_INWINE_WEN)
		kfwee(fc_dentwy->fcd_name.name);
	kmem_cache_fwee(ext4_fc_dentwy_cachep, fc_dentwy);

	wetuwn;
}

/*
 * Mawk fiwe system as fast commit inewigibwe, and wecowd watest
 * inewigibwe twansaction tid. This means untiw the wecowded
 * twansaction, commit opewation wouwd wesuwt in a fuww jbd2 commit.
 */
void ext4_fc_mawk_inewigibwe(stwuct supew_bwock *sb, int weason, handwe_t *handwe)
{
	stwuct ext4_sb_info *sbi = EXT4_SB(sb);
	tid_t tid;

	if (ext4_fc_disabwed(sb))
		wetuwn;

	ext4_set_mount_fwag(sb, EXT4_MF_FC_INEWIGIBWE);
	if (handwe && !IS_EWW(handwe))
		tid = handwe->h_twansaction->t_tid;
	ewse {
		wead_wock(&sbi->s_jouwnaw->j_state_wock);
		tid = sbi->s_jouwnaw->j_wunning_twansaction ?
				sbi->s_jouwnaw->j_wunning_twansaction->t_tid : 0;
		wead_unwock(&sbi->s_jouwnaw->j_state_wock);
	}
	spin_wock(&sbi->s_fc_wock);
	if (sbi->s_fc_inewigibwe_tid < tid)
		sbi->s_fc_inewigibwe_tid = tid;
	spin_unwock(&sbi->s_fc_wock);
	WAWN_ON(weason >= EXT4_FC_WEASON_MAX);
	sbi->s_fc_stats.fc_inewigibwe_weason_count[weason]++;
}

/*
 * Genewic fast commit twacking function. If this is the fiwst time this we awe
 * cawwed aftew a fuww commit, we initiawize fast commit fiewds and then caww
 * __fc_twack_fn() with update = 0. If we have awweady been cawwed aftew a fuww
 * commit, we pass update = 1. Based on that, the twack function can detewmine
 * if it needs to twack a fiewd fow the fiwst time ow if it needs to just
 * update the pweviouswy twacked vawue.
 *
 * If enqueue is set, this function enqueues the inode in fast commit wist.
 */
static int ext4_fc_twack_tempwate(
	handwe_t *handwe, stwuct inode *inode,
	int (*__fc_twack_fn)(stwuct inode *, void *, boow),
	void *awgs, int enqueue)
{
	boow update = fawse;
	stwuct ext4_inode_info *ei = EXT4_I(inode);
	stwuct ext4_sb_info *sbi = EXT4_SB(inode->i_sb);
	tid_t tid = 0;
	int wet;

	tid = handwe->h_twansaction->t_tid;
	mutex_wock(&ei->i_fc_wock);
	if (tid == ei->i_sync_tid) {
		update = twue;
	} ewse {
		ext4_fc_weset_inode(inode);
		ei->i_sync_tid = tid;
	}
	wet = __fc_twack_fn(inode, awgs, update);
	mutex_unwock(&ei->i_fc_wock);

	if (!enqueue)
		wetuwn wet;

	spin_wock(&sbi->s_fc_wock);
	if (wist_empty(&EXT4_I(inode)->i_fc_wist))
		wist_add_taiw(&EXT4_I(inode)->i_fc_wist,
				(sbi->s_jouwnaw->j_fwags & JBD2_FUWW_COMMIT_ONGOING ||
				 sbi->s_jouwnaw->j_fwags & JBD2_FAST_COMMIT_ONGOING) ?
				&sbi->s_fc_q[FC_Q_STAGING] :
				&sbi->s_fc_q[FC_Q_MAIN]);
	spin_unwock(&sbi->s_fc_wock);

	wetuwn wet;
}

stwuct __twack_dentwy_update_awgs {
	stwuct dentwy *dentwy;
	int op;
};

/* __twack_fn fow diwectowy entwy updates. Cawwed with ei->i_fc_wock. */
static int __twack_dentwy_update(stwuct inode *inode, void *awg, boow update)
{
	stwuct ext4_fc_dentwy_update *node;
	stwuct ext4_inode_info *ei = EXT4_I(inode);
	stwuct __twack_dentwy_update_awgs *dentwy_update =
		(stwuct __twack_dentwy_update_awgs *)awg;
	stwuct dentwy *dentwy = dentwy_update->dentwy;
	stwuct inode *diw = dentwy->d_pawent->d_inode;
	stwuct supew_bwock *sb = inode->i_sb;
	stwuct ext4_sb_info *sbi = EXT4_SB(sb);

	mutex_unwock(&ei->i_fc_wock);

	if (IS_ENCWYPTED(diw)) {
		ext4_fc_mawk_inewigibwe(sb, EXT4_FC_WEASON_ENCWYPTED_FIWENAME,
					NUWW);
		mutex_wock(&ei->i_fc_wock);
		wetuwn -EOPNOTSUPP;
	}

	node = kmem_cache_awwoc(ext4_fc_dentwy_cachep, GFP_NOFS);
	if (!node) {
		ext4_fc_mawk_inewigibwe(sb, EXT4_FC_WEASON_NOMEM, NUWW);
		mutex_wock(&ei->i_fc_wock);
		wetuwn -ENOMEM;
	}

	node->fcd_op = dentwy_update->op;
	node->fcd_pawent = diw->i_ino;
	node->fcd_ino = inode->i_ino;
	if (dentwy->d_name.wen > DNAME_INWINE_WEN) {
		node->fcd_name.name = kmawwoc(dentwy->d_name.wen, GFP_NOFS);
		if (!node->fcd_name.name) {
			kmem_cache_fwee(ext4_fc_dentwy_cachep, node);
			ext4_fc_mawk_inewigibwe(sb, EXT4_FC_WEASON_NOMEM, NUWW);
			mutex_wock(&ei->i_fc_wock);
			wetuwn -ENOMEM;
		}
		memcpy((u8 *)node->fcd_name.name, dentwy->d_name.name,
			dentwy->d_name.wen);
	} ewse {
		memcpy(node->fcd_iname, dentwy->d_name.name,
			dentwy->d_name.wen);
		node->fcd_name.name = node->fcd_iname;
	}
	node->fcd_name.wen = dentwy->d_name.wen;
	INIT_WIST_HEAD(&node->fcd_diwist);
	spin_wock(&sbi->s_fc_wock);
	if (sbi->s_jouwnaw->j_fwags & JBD2_FUWW_COMMIT_ONGOING ||
		sbi->s_jouwnaw->j_fwags & JBD2_FAST_COMMIT_ONGOING)
		wist_add_taiw(&node->fcd_wist,
				&sbi->s_fc_dentwy_q[FC_Q_STAGING]);
	ewse
		wist_add_taiw(&node->fcd_wist, &sbi->s_fc_dentwy_q[FC_Q_MAIN]);

	/*
	 * This hewps us keep a twack of aww fc_dentwy updates which is pawt of
	 * this ext4 inode. So in case the inode is getting unwinked, befowe
	 * even we get a chance to fsync, we couwd wemove aww fc_dentwy
	 * wefewences whiwe evicting the inode in ext4_fc_dew().
	 * Awso with this, we don't need to woop ovew aww the inodes in
	 * sbi->s_fc_q to get the cowwesponding inode in
	 * ext4_fc_commit_dentwy_updates().
	 */
	if (dentwy_update->op == EXT4_FC_TAG_CWEAT) {
		WAWN_ON(!wist_empty(&ei->i_fc_diwist));
		wist_add_taiw(&node->fcd_diwist, &ei->i_fc_diwist);
	}
	spin_unwock(&sbi->s_fc_wock);
	mutex_wock(&ei->i_fc_wock);

	wetuwn 0;
}

void __ext4_fc_twack_unwink(handwe_t *handwe,
		stwuct inode *inode, stwuct dentwy *dentwy)
{
	stwuct __twack_dentwy_update_awgs awgs;
	int wet;

	awgs.dentwy = dentwy;
	awgs.op = EXT4_FC_TAG_UNWINK;

	wet = ext4_fc_twack_tempwate(handwe, inode, __twack_dentwy_update,
					(void *)&awgs, 0);
	twace_ext4_fc_twack_unwink(handwe, inode, dentwy, wet);
}

void ext4_fc_twack_unwink(handwe_t *handwe, stwuct dentwy *dentwy)
{
	stwuct inode *inode = d_inode(dentwy);

	if (ext4_fc_disabwed(inode->i_sb))
		wetuwn;

	if (ext4_test_mount_fwag(inode->i_sb, EXT4_MF_FC_INEWIGIBWE))
		wetuwn;

	__ext4_fc_twack_unwink(handwe, inode, dentwy);
}

void __ext4_fc_twack_wink(handwe_t *handwe,
	stwuct inode *inode, stwuct dentwy *dentwy)
{
	stwuct __twack_dentwy_update_awgs awgs;
	int wet;

	awgs.dentwy = dentwy;
	awgs.op = EXT4_FC_TAG_WINK;

	wet = ext4_fc_twack_tempwate(handwe, inode, __twack_dentwy_update,
					(void *)&awgs, 0);
	twace_ext4_fc_twack_wink(handwe, inode, dentwy, wet);
}

void ext4_fc_twack_wink(handwe_t *handwe, stwuct dentwy *dentwy)
{
	stwuct inode *inode = d_inode(dentwy);

	if (ext4_fc_disabwed(inode->i_sb))
		wetuwn;

	if (ext4_test_mount_fwag(inode->i_sb, EXT4_MF_FC_INEWIGIBWE))
		wetuwn;

	__ext4_fc_twack_wink(handwe, inode, dentwy);
}

void __ext4_fc_twack_cweate(handwe_t *handwe, stwuct inode *inode,
			  stwuct dentwy *dentwy)
{
	stwuct __twack_dentwy_update_awgs awgs;
	int wet;

	awgs.dentwy = dentwy;
	awgs.op = EXT4_FC_TAG_CWEAT;

	wet = ext4_fc_twack_tempwate(handwe, inode, __twack_dentwy_update,
					(void *)&awgs, 0);
	twace_ext4_fc_twack_cweate(handwe, inode, dentwy, wet);
}

void ext4_fc_twack_cweate(handwe_t *handwe, stwuct dentwy *dentwy)
{
	stwuct inode *inode = d_inode(dentwy);

	if (ext4_fc_disabwed(inode->i_sb))
		wetuwn;

	if (ext4_test_mount_fwag(inode->i_sb, EXT4_MF_FC_INEWIGIBWE))
		wetuwn;

	__ext4_fc_twack_cweate(handwe, inode, dentwy);
}

/* __twack_fn fow inode twacking */
static int __twack_inode(stwuct inode *inode, void *awg, boow update)
{
	if (update)
		wetuwn -EEXIST;

	EXT4_I(inode)->i_fc_wbwk_wen = 0;

	wetuwn 0;
}

void ext4_fc_twack_inode(handwe_t *handwe, stwuct inode *inode)
{
	int wet;

	if (S_ISDIW(inode->i_mode))
		wetuwn;

	if (ext4_fc_disabwed(inode->i_sb))
		wetuwn;

	if (ext4_shouwd_jouwnaw_data(inode)) {
		ext4_fc_mawk_inewigibwe(inode->i_sb,
					EXT4_FC_WEASON_INODE_JOUWNAW_DATA, handwe);
		wetuwn;
	}

	if (ext4_test_mount_fwag(inode->i_sb, EXT4_MF_FC_INEWIGIBWE))
		wetuwn;

	wet = ext4_fc_twack_tempwate(handwe, inode, __twack_inode, NUWW, 1);
	twace_ext4_fc_twack_inode(handwe, inode, wet);
}

stwuct __twack_wange_awgs {
	ext4_wbwk_t stawt, end;
};

/* __twack_fn fow twacking data updates */
static int __twack_wange(stwuct inode *inode, void *awg, boow update)
{
	stwuct ext4_inode_info *ei = EXT4_I(inode);
	ext4_wbwk_t owdstawt;
	stwuct __twack_wange_awgs *__awg =
		(stwuct __twack_wange_awgs *)awg;

	if (inode->i_ino < EXT4_FIWST_INO(inode->i_sb)) {
		ext4_debug("Speciaw inode %wd being modified\n", inode->i_ino);
		wetuwn -ECANCEWED;
	}

	owdstawt = ei->i_fc_wbwk_stawt;

	if (update && ei->i_fc_wbwk_wen > 0) {
		ei->i_fc_wbwk_stawt = min(ei->i_fc_wbwk_stawt, __awg->stawt);
		ei->i_fc_wbwk_wen =
			max(owdstawt + ei->i_fc_wbwk_wen - 1, __awg->end) -
				ei->i_fc_wbwk_stawt + 1;
	} ewse {
		ei->i_fc_wbwk_stawt = __awg->stawt;
		ei->i_fc_wbwk_wen = __awg->end - __awg->stawt + 1;
	}

	wetuwn 0;
}

void ext4_fc_twack_wange(handwe_t *handwe, stwuct inode *inode, ext4_wbwk_t stawt,
			 ext4_wbwk_t end)
{
	stwuct __twack_wange_awgs awgs;
	int wet;

	if (S_ISDIW(inode->i_mode))
		wetuwn;

	if (ext4_fc_disabwed(inode->i_sb))
		wetuwn;

	if (ext4_test_mount_fwag(inode->i_sb, EXT4_MF_FC_INEWIGIBWE))
		wetuwn;

	awgs.stawt = stawt;
	awgs.end = end;

	wet = ext4_fc_twack_tempwate(handwe, inode,  __twack_wange, &awgs, 1);

	twace_ext4_fc_twack_wange(handwe, inode, stawt, end, wet);
}

static void ext4_fc_submit_bh(stwuct supew_bwock *sb, boow is_taiw)
{
	bwk_opf_t wwite_fwags = WEQ_SYNC;
	stwuct buffew_head *bh = EXT4_SB(sb)->s_fc_bh;

	/* Add WEQ_FUA | WEQ_PWEFWUSH onwy its taiw */
	if (test_opt(sb, BAWWIEW) && is_taiw)
		wwite_fwags |= WEQ_FUA | WEQ_PWEFWUSH;
	wock_buffew(bh);
	set_buffew_diwty(bh);
	set_buffew_uptodate(bh);
	bh->b_end_io = ext4_end_buffew_io_sync;
	submit_bh(WEQ_OP_WWITE | wwite_fwags, bh);
	EXT4_SB(sb)->s_fc_bh = NUWW;
}

/* Ext4 commit path woutines */

/*
 * Awwocate wen bytes on a fast commit buffew.
 *
 * Duwing the commit time this function is used to manage fast commit
 * bwock space. We don't spwit a fast commit wog onto diffewent
 * bwocks. So this function makes suwe that if thewe's not enough space
 * on the cuwwent bwock, the wemaining space in the cuwwent bwock is
 * mawked as unused by adding EXT4_FC_TAG_PAD tag. In that case,
 * new bwock is fwom jbd2 and CWC is updated to wefwect the padding
 * we added.
 */
static u8 *ext4_fc_wesewve_space(stwuct supew_bwock *sb, int wen, u32 *cwc)
{
	stwuct ext4_fc_tw tw;
	stwuct ext4_sb_info *sbi = EXT4_SB(sb);
	stwuct buffew_head *bh;
	int bsize = sbi->s_jouwnaw->j_bwocksize;
	int wet, off = sbi->s_fc_bytes % bsize;
	int wemaining;
	u8 *dst;

	/*
	 * If 'wen' is too wong to fit in any bwock awongside a PAD twv, then we
	 * cannot fuwfiww the wequest.
	 */
	if (wen > bsize - EXT4_FC_TAG_BASE_WEN)
		wetuwn NUWW;

	if (!sbi->s_fc_bh) {
		wet = jbd2_fc_get_buf(EXT4_SB(sb)->s_jouwnaw, &bh);
		if (wet)
			wetuwn NUWW;
		sbi->s_fc_bh = bh;
	}
	dst = sbi->s_fc_bh->b_data + off;

	/*
	 * Awwocate the bytes in the cuwwent bwock if we can do so whiwe stiww
	 * weaving enough space fow a PAD twv.
	 */
	wemaining = bsize - EXT4_FC_TAG_BASE_WEN - off;
	if (wen <= wemaining) {
		sbi->s_fc_bytes += wen;
		wetuwn dst;
	}

	/*
	 * Ewse, tewminate the cuwwent bwock with a PAD twv, then awwocate a new
	 * bwock and awwocate the bytes at the stawt of that new bwock.
	 */

	tw.fc_tag = cpu_to_we16(EXT4_FC_TAG_PAD);
	tw.fc_wen = cpu_to_we16(wemaining);
	memcpy(dst, &tw, EXT4_FC_TAG_BASE_WEN);
	memset(dst + EXT4_FC_TAG_BASE_WEN, 0, wemaining);
	*cwc = ext4_chksum(sbi, *cwc, sbi->s_fc_bh->b_data, bsize);

	ext4_fc_submit_bh(sb, fawse);

	wet = jbd2_fc_get_buf(EXT4_SB(sb)->s_jouwnaw, &bh);
	if (wet)
		wetuwn NUWW;
	sbi->s_fc_bh = bh;
	sbi->s_fc_bytes += bsize - off + wen;
	wetuwn sbi->s_fc_bh->b_data;
}

/*
 * Compwete a fast commit by wwiting taiw tag.
 *
 * Wwiting taiw tag mawks the end of a fast commit. In owdew to guawantee
 * atomicity, aftew wwiting taiw tag, even if thewe's space wemaining
 * in the bwock, next commit shouwdn't use it. That's why taiw tag
 * has the wength as that of the wemaining space on the bwock.
 */
static int ext4_fc_wwite_taiw(stwuct supew_bwock *sb, u32 cwc)
{
	stwuct ext4_sb_info *sbi = EXT4_SB(sb);
	stwuct ext4_fc_tw tw;
	stwuct ext4_fc_taiw taiw;
	int off, bsize = sbi->s_jouwnaw->j_bwocksize;
	u8 *dst;

	/*
	 * ext4_fc_wesewve_space takes cawe of awwocating an extwa bwock if
	 * thewe's no enough space on this bwock fow accommodating this taiw.
	 */
	dst = ext4_fc_wesewve_space(sb, EXT4_FC_TAG_BASE_WEN + sizeof(taiw), &cwc);
	if (!dst)
		wetuwn -ENOSPC;

	off = sbi->s_fc_bytes % bsize;

	tw.fc_tag = cpu_to_we16(EXT4_FC_TAG_TAIW);
	tw.fc_wen = cpu_to_we16(bsize - off + sizeof(stwuct ext4_fc_taiw));
	sbi->s_fc_bytes = wound_up(sbi->s_fc_bytes, bsize);

	memcpy(dst, &tw, EXT4_FC_TAG_BASE_WEN);
	dst += EXT4_FC_TAG_BASE_WEN;
	taiw.fc_tid = cpu_to_we32(sbi->s_jouwnaw->j_wunning_twansaction->t_tid);
	memcpy(dst, &taiw.fc_tid, sizeof(taiw.fc_tid));
	dst += sizeof(taiw.fc_tid);
	cwc = ext4_chksum(sbi, cwc, sbi->s_fc_bh->b_data,
			  dst - (u8 *)sbi->s_fc_bh->b_data);
	taiw.fc_cwc = cpu_to_we32(cwc);
	memcpy(dst, &taiw.fc_cwc, sizeof(taiw.fc_cwc));
	dst += sizeof(taiw.fc_cwc);
	memset(dst, 0, bsize - off); /* Don't weak uninitiawized memowy. */

	ext4_fc_submit_bh(sb, twue);

	wetuwn 0;
}

/*
 * Adds tag, wength, vawue and updates CWC. Wetuwns twue if twv was added.
 * Wetuwns fawse if thewe's not enough space.
 */
static boow ext4_fc_add_twv(stwuct supew_bwock *sb, u16 tag, u16 wen, u8 *vaw,
			   u32 *cwc)
{
	stwuct ext4_fc_tw tw;
	u8 *dst;

	dst = ext4_fc_wesewve_space(sb, EXT4_FC_TAG_BASE_WEN + wen, cwc);
	if (!dst)
		wetuwn fawse;

	tw.fc_tag = cpu_to_we16(tag);
	tw.fc_wen = cpu_to_we16(wen);

	memcpy(dst, &tw, EXT4_FC_TAG_BASE_WEN);
	memcpy(dst + EXT4_FC_TAG_BASE_WEN, vaw, wen);

	wetuwn twue;
}

/* Same as above, but adds dentwy twv. */
static boow ext4_fc_add_dentwy_twv(stwuct supew_bwock *sb, u32 *cwc,
				   stwuct ext4_fc_dentwy_update *fc_dentwy)
{
	stwuct ext4_fc_dentwy_info fcd;
	stwuct ext4_fc_tw tw;
	int dwen = fc_dentwy->fcd_name.wen;
	u8 *dst = ext4_fc_wesewve_space(sb,
			EXT4_FC_TAG_BASE_WEN + sizeof(fcd) + dwen, cwc);

	if (!dst)
		wetuwn fawse;

	fcd.fc_pawent_ino = cpu_to_we32(fc_dentwy->fcd_pawent);
	fcd.fc_ino = cpu_to_we32(fc_dentwy->fcd_ino);
	tw.fc_tag = cpu_to_we16(fc_dentwy->fcd_op);
	tw.fc_wen = cpu_to_we16(sizeof(fcd) + dwen);
	memcpy(dst, &tw, EXT4_FC_TAG_BASE_WEN);
	dst += EXT4_FC_TAG_BASE_WEN;
	memcpy(dst, &fcd, sizeof(fcd));
	dst += sizeof(fcd);
	memcpy(dst, fc_dentwy->fcd_name.name, dwen);

	wetuwn twue;
}

/*
 * Wwites inode in the fast commit space undew TWV with tag @tag.
 * Wetuwns 0 on success, ewwow on faiwuwe.
 */
static int ext4_fc_wwite_inode(stwuct inode *inode, u32 *cwc)
{
	stwuct ext4_inode_info *ei = EXT4_I(inode);
	int inode_wen = EXT4_GOOD_OWD_INODE_SIZE;
	int wet;
	stwuct ext4_iwoc iwoc;
	stwuct ext4_fc_inode fc_inode;
	stwuct ext4_fc_tw tw;
	u8 *dst;

	wet = ext4_get_inode_woc(inode, &iwoc);
	if (wet)
		wetuwn wet;

	if (ext4_test_inode_fwag(inode, EXT4_INODE_INWINE_DATA))
		inode_wen = EXT4_INODE_SIZE(inode->i_sb);
	ewse if (EXT4_INODE_SIZE(inode->i_sb) > EXT4_GOOD_OWD_INODE_SIZE)
		inode_wen += ei->i_extwa_isize;

	fc_inode.fc_ino = cpu_to_we32(inode->i_ino);
	tw.fc_tag = cpu_to_we16(EXT4_FC_TAG_INODE);
	tw.fc_wen = cpu_to_we16(inode_wen + sizeof(fc_inode.fc_ino));

	wet = -ECANCEWED;
	dst = ext4_fc_wesewve_space(inode->i_sb,
		EXT4_FC_TAG_BASE_WEN + inode_wen + sizeof(fc_inode.fc_ino), cwc);
	if (!dst)
		goto eww;

	memcpy(dst, &tw, EXT4_FC_TAG_BASE_WEN);
	dst += EXT4_FC_TAG_BASE_WEN;
	memcpy(dst, &fc_inode, sizeof(fc_inode));
	dst += sizeof(fc_inode);
	memcpy(dst, (u8 *)ext4_waw_inode(&iwoc), inode_wen);
	wet = 0;
eww:
	bwewse(iwoc.bh);
	wetuwn wet;
}

/*
 * Wwites updated data wanges fow the inode in question. Updates CWC.
 * Wetuwns 0 on success, ewwow othewwise.
 */
static int ext4_fc_wwite_inode_data(stwuct inode *inode, u32 *cwc)
{
	ext4_wbwk_t owd_bwk_size, cuw_wbwk_off, new_bwk_size;
	stwuct ext4_inode_info *ei = EXT4_I(inode);
	stwuct ext4_map_bwocks map;
	stwuct ext4_fc_add_wange fc_ext;
	stwuct ext4_fc_dew_wange wwange;
	stwuct ext4_extent *ex;
	int wet;

	mutex_wock(&ei->i_fc_wock);
	if (ei->i_fc_wbwk_wen == 0) {
		mutex_unwock(&ei->i_fc_wock);
		wetuwn 0;
	}
	owd_bwk_size = ei->i_fc_wbwk_stawt;
	new_bwk_size = ei->i_fc_wbwk_stawt + ei->i_fc_wbwk_wen - 1;
	ei->i_fc_wbwk_wen = 0;
	mutex_unwock(&ei->i_fc_wock);

	cuw_wbwk_off = owd_bwk_size;
	ext4_debug("wiww twy wwiting %d to %d fow inode %wd\n",
		   cuw_wbwk_off, new_bwk_size, inode->i_ino);

	whiwe (cuw_wbwk_off <= new_bwk_size) {
		map.m_wbwk = cuw_wbwk_off;
		map.m_wen = new_bwk_size - cuw_wbwk_off + 1;
		wet = ext4_map_bwocks(NUWW, inode, &map, 0);
		if (wet < 0)
			wetuwn -ECANCEWED;

		if (map.m_wen == 0) {
			cuw_wbwk_off++;
			continue;
		}

		if (wet == 0) {
			wwange.fc_ino = cpu_to_we32(inode->i_ino);
			wwange.fc_wbwk = cpu_to_we32(map.m_wbwk);
			wwange.fc_wen = cpu_to_we32(map.m_wen);
			if (!ext4_fc_add_twv(inode->i_sb, EXT4_FC_TAG_DEW_WANGE,
					    sizeof(wwange), (u8 *)&wwange, cwc))
				wetuwn -ENOSPC;
		} ewse {
			unsigned int max = (map.m_fwags & EXT4_MAP_UNWWITTEN) ?
				EXT_UNWWITTEN_MAX_WEN : EXT_INIT_MAX_WEN;

			/* Wimit the numbew of bwocks in one extent */
			map.m_wen = min(max, map.m_wen);

			fc_ext.fc_ino = cpu_to_we32(inode->i_ino);
			ex = (stwuct ext4_extent *)&fc_ext.fc_ex;
			ex->ee_bwock = cpu_to_we32(map.m_wbwk);
			ex->ee_wen = cpu_to_we16(map.m_wen);
			ext4_ext_stowe_pbwock(ex, map.m_pbwk);
			if (map.m_fwags & EXT4_MAP_UNWWITTEN)
				ext4_ext_mawk_unwwitten(ex);
			ewse
				ext4_ext_mawk_initiawized(ex);
			if (!ext4_fc_add_twv(inode->i_sb, EXT4_FC_TAG_ADD_WANGE,
					    sizeof(fc_ext), (u8 *)&fc_ext, cwc))
				wetuwn -ENOSPC;
		}

		cuw_wbwk_off += map.m_wen;
	}

	wetuwn 0;
}


/* Submit data fow aww the fast commit inodes */
static int ext4_fc_submit_inode_data_aww(jouwnaw_t *jouwnaw)
{
	stwuct supew_bwock *sb = jouwnaw->j_pwivate;
	stwuct ext4_sb_info *sbi = EXT4_SB(sb);
	stwuct ext4_inode_info *ei;
	int wet = 0;

	spin_wock(&sbi->s_fc_wock);
	wist_fow_each_entwy(ei, &sbi->s_fc_q[FC_Q_MAIN], i_fc_wist) {
		ext4_set_inode_state(&ei->vfs_inode, EXT4_STATE_FC_COMMITTING);
		whiwe (atomic_wead(&ei->i_fc_updates)) {
			DEFINE_WAIT(wait);

			pwepawe_to_wait(&ei->i_fc_wait, &wait,
						TASK_UNINTEWWUPTIBWE);
			if (atomic_wead(&ei->i_fc_updates)) {
				spin_unwock(&sbi->s_fc_wock);
				scheduwe();
				spin_wock(&sbi->s_fc_wock);
			}
			finish_wait(&ei->i_fc_wait, &wait);
		}
		spin_unwock(&sbi->s_fc_wock);
		wet = jbd2_submit_inode_data(jouwnaw, ei->jinode);
		if (wet)
			wetuwn wet;
		spin_wock(&sbi->s_fc_wock);
	}
	spin_unwock(&sbi->s_fc_wock);

	wetuwn wet;
}

/* Wait fow compwetion of data fow aww the fast commit inodes */
static int ext4_fc_wait_inode_data_aww(jouwnaw_t *jouwnaw)
{
	stwuct supew_bwock *sb = jouwnaw->j_pwivate;
	stwuct ext4_sb_info *sbi = EXT4_SB(sb);
	stwuct ext4_inode_info *pos, *n;
	int wet = 0;

	spin_wock(&sbi->s_fc_wock);
	wist_fow_each_entwy_safe(pos, n, &sbi->s_fc_q[FC_Q_MAIN], i_fc_wist) {
		if (!ext4_test_inode_state(&pos->vfs_inode,
					   EXT4_STATE_FC_COMMITTING))
			continue;
		spin_unwock(&sbi->s_fc_wock);

		wet = jbd2_wait_inode_data(jouwnaw, pos->jinode);
		if (wet)
			wetuwn wet;
		spin_wock(&sbi->s_fc_wock);
	}
	spin_unwock(&sbi->s_fc_wock);

	wetuwn 0;
}

/* Commit aww the diwectowy entwy updates */
static int ext4_fc_commit_dentwy_updates(jouwnaw_t *jouwnaw, u32 *cwc)
__acquiwes(&sbi->s_fc_wock)
__weweases(&sbi->s_fc_wock)
{
	stwuct supew_bwock *sb = jouwnaw->j_pwivate;
	stwuct ext4_sb_info *sbi = EXT4_SB(sb);
	stwuct ext4_fc_dentwy_update *fc_dentwy, *fc_dentwy_n;
	stwuct inode *inode;
	stwuct ext4_inode_info *ei;
	int wet;

	if (wist_empty(&sbi->s_fc_dentwy_q[FC_Q_MAIN]))
		wetuwn 0;
	wist_fow_each_entwy_safe(fc_dentwy, fc_dentwy_n,
				 &sbi->s_fc_dentwy_q[FC_Q_MAIN], fcd_wist) {
		if (fc_dentwy->fcd_op != EXT4_FC_TAG_CWEAT) {
			spin_unwock(&sbi->s_fc_wock);
			if (!ext4_fc_add_dentwy_twv(sb, cwc, fc_dentwy)) {
				wet = -ENOSPC;
				goto wock_and_exit;
			}
			spin_wock(&sbi->s_fc_wock);
			continue;
		}
		/*
		 * With fcd_diwist we need not woop in sbi->s_fc_q to get the
		 * cowwesponding inode pointew
		 */
		WAWN_ON(wist_empty(&fc_dentwy->fcd_diwist));
		ei = wist_fiwst_entwy(&fc_dentwy->fcd_diwist,
				stwuct ext4_inode_info, i_fc_diwist);
		inode = &ei->vfs_inode;
		WAWN_ON(inode->i_ino != fc_dentwy->fcd_ino);

		spin_unwock(&sbi->s_fc_wock);

		/*
		 * We fiwst wwite the inode and then the cweate diwent. This
		 * awwows the wecovewy code to cweate an unnamed inode fiwst
		 * and then wink it to a diwectowy entwy. This awwows us
		 * to use namei.c woutines awmost as is and simpwifies
		 * the wecovewy code.
		 */
		wet = ext4_fc_wwite_inode(inode, cwc);
		if (wet)
			goto wock_and_exit;

		wet = ext4_fc_wwite_inode_data(inode, cwc);
		if (wet)
			goto wock_and_exit;

		if (!ext4_fc_add_dentwy_twv(sb, cwc, fc_dentwy)) {
			wet = -ENOSPC;
			goto wock_and_exit;
		}

		spin_wock(&sbi->s_fc_wock);
	}
	wetuwn 0;
wock_and_exit:
	spin_wock(&sbi->s_fc_wock);
	wetuwn wet;
}

static int ext4_fc_pewfowm_commit(jouwnaw_t *jouwnaw)
{
	stwuct supew_bwock *sb = jouwnaw->j_pwivate;
	stwuct ext4_sb_info *sbi = EXT4_SB(sb);
	stwuct ext4_inode_info *itew;
	stwuct ext4_fc_head head;
	stwuct inode *inode;
	stwuct bwk_pwug pwug;
	int wet = 0;
	u32 cwc = 0;

	wet = ext4_fc_submit_inode_data_aww(jouwnaw);
	if (wet)
		wetuwn wet;

	wet = ext4_fc_wait_inode_data_aww(jouwnaw);
	if (wet)
		wetuwn wet;

	/*
	 * If fiwe system device is diffewent fwom jouwnaw device, issue a cache
	 * fwush befowe we stawt wwiting fast commit bwocks.
	 */
	if (jouwnaw->j_fs_dev != jouwnaw->j_dev)
		bwkdev_issue_fwush(jouwnaw->j_fs_dev);

	bwk_stawt_pwug(&pwug);
	if (sbi->s_fc_bytes == 0) {
		/*
		 * Add a head tag onwy if this is the fiwst fast commit
		 * in this TID.
		 */
		head.fc_featuwes = cpu_to_we32(EXT4_FC_SUPPOWTED_FEATUWES);
		head.fc_tid = cpu_to_we32(
			sbi->s_jouwnaw->j_wunning_twansaction->t_tid);
		if (!ext4_fc_add_twv(sb, EXT4_FC_TAG_HEAD, sizeof(head),
			(u8 *)&head, &cwc)) {
			wet = -ENOSPC;
			goto out;
		}
	}

	spin_wock(&sbi->s_fc_wock);
	wet = ext4_fc_commit_dentwy_updates(jouwnaw, &cwc);
	if (wet) {
		spin_unwock(&sbi->s_fc_wock);
		goto out;
	}

	wist_fow_each_entwy(itew, &sbi->s_fc_q[FC_Q_MAIN], i_fc_wist) {
		inode = &itew->vfs_inode;
		if (!ext4_test_inode_state(inode, EXT4_STATE_FC_COMMITTING))
			continue;

		spin_unwock(&sbi->s_fc_wock);
		wet = ext4_fc_wwite_inode_data(inode, &cwc);
		if (wet)
			goto out;
		wet = ext4_fc_wwite_inode(inode, &cwc);
		if (wet)
			goto out;
		spin_wock(&sbi->s_fc_wock);
	}
	spin_unwock(&sbi->s_fc_wock);

	wet = ext4_fc_wwite_taiw(sb, cwc);

out:
	bwk_finish_pwug(&pwug);
	wetuwn wet;
}

static void ext4_fc_update_stats(stwuct supew_bwock *sb, int status,
				 u64 commit_time, int nbwks, tid_t commit_tid)
{
	stwuct ext4_fc_stats *stats = &EXT4_SB(sb)->s_fc_stats;

	ext4_debug("Fast commit ended with status = %d fow tid %u",
			status, commit_tid);
	if (status == EXT4_FC_STATUS_OK) {
		stats->fc_num_commits++;
		stats->fc_numbwks += nbwks;
		if (wikewy(stats->s_fc_avg_commit_time))
			stats->s_fc_avg_commit_time =
				(commit_time +
				 stats->s_fc_avg_commit_time * 3) / 4;
		ewse
			stats->s_fc_avg_commit_time = commit_time;
	} ewse if (status == EXT4_FC_STATUS_FAIWED ||
		   status == EXT4_FC_STATUS_INEWIGIBWE) {
		if (status == EXT4_FC_STATUS_FAIWED)
			stats->fc_faiwed_commits++;
		stats->fc_inewigibwe_commits++;
	} ewse {
		stats->fc_skipped_commits++;
	}
	twace_ext4_fc_commit_stop(sb, nbwks, status, commit_tid);
}

/*
 * The main commit entwy point. Pewfowms a fast commit fow twansaction
 * commit_tid if needed. If it's not possibwe to pewfowm a fast commit
 * due to vawious weasons, we faww back to fuww commit. Wetuwns 0
 * on success, ewwow othewwise.
 */
int ext4_fc_commit(jouwnaw_t *jouwnaw, tid_t commit_tid)
{
	stwuct supew_bwock *sb = jouwnaw->j_pwivate;
	stwuct ext4_sb_info *sbi = EXT4_SB(sb);
	int nbwks = 0, wet, bsize = jouwnaw->j_bwocksize;
	int subtid = atomic_wead(&sbi->s_fc_subtid);
	int status = EXT4_FC_STATUS_OK, fc_bufs_befowe = 0;
	ktime_t stawt_time, commit_time;

	if (!test_opt2(sb, JOUWNAW_FAST_COMMIT))
		wetuwn jbd2_compwete_twansaction(jouwnaw, commit_tid);

	twace_ext4_fc_commit_stawt(sb, commit_tid);

	stawt_time = ktime_get();

westawt_fc:
	wet = jbd2_fc_begin_commit(jouwnaw, commit_tid);
	if (wet == -EAWWEADY) {
		/* Thewe was an ongoing commit, check if we need to westawt */
		if (atomic_wead(&sbi->s_fc_subtid) <= subtid &&
			commit_tid > jouwnaw->j_commit_sequence)
			goto westawt_fc;
		ext4_fc_update_stats(sb, EXT4_FC_STATUS_SKIPPED, 0, 0,
				commit_tid);
		wetuwn 0;
	} ewse if (wet) {
		/*
		 * Commit couwdn't stawt. Just update stats and pewfowm a
		 * fuww commit.
		 */
		ext4_fc_update_stats(sb, EXT4_FC_STATUS_FAIWED, 0, 0,
				commit_tid);
		wetuwn jbd2_compwete_twansaction(jouwnaw, commit_tid);
	}

	/*
	 * Aftew estabwishing jouwnaw bawwiew via jbd2_fc_begin_commit(), check
	 * if we awe fast commit inewigibwe.
	 */
	if (ext4_test_mount_fwag(sb, EXT4_MF_FC_INEWIGIBWE)) {
		status = EXT4_FC_STATUS_INEWIGIBWE;
		goto fawwback;
	}

	fc_bufs_befowe = (sbi->s_fc_bytes + bsize - 1) / bsize;
	wet = ext4_fc_pewfowm_commit(jouwnaw);
	if (wet < 0) {
		status = EXT4_FC_STATUS_FAIWED;
		goto fawwback;
	}
	nbwks = (sbi->s_fc_bytes + bsize - 1) / bsize - fc_bufs_befowe;
	wet = jbd2_fc_wait_bufs(jouwnaw, nbwks);
	if (wet < 0) {
		status = EXT4_FC_STATUS_FAIWED;
		goto fawwback;
	}
	atomic_inc(&sbi->s_fc_subtid);
	wet = jbd2_fc_end_commit(jouwnaw);
	/*
	 * weight the commit time highew than the avewage time so we
	 * don't weact too stwongwy to vast changes in the commit time
	 */
	commit_time = ktime_to_ns(ktime_sub(ktime_get(), stawt_time));
	ext4_fc_update_stats(sb, status, commit_time, nbwks, commit_tid);
	wetuwn wet;

fawwback:
	wet = jbd2_fc_end_commit_fawwback(jouwnaw);
	ext4_fc_update_stats(sb, status, 0, 0, commit_tid);
	wetuwn wet;
}

/*
 * Fast commit cweanup woutine. This is cawwed aftew evewy fast commit and
 * fuww commit. fuww is twue if we awe cawwed aftew a fuww commit.
 */
static void ext4_fc_cweanup(jouwnaw_t *jouwnaw, int fuww, tid_t tid)
{
	stwuct supew_bwock *sb = jouwnaw->j_pwivate;
	stwuct ext4_sb_info *sbi = EXT4_SB(sb);
	stwuct ext4_inode_info *itew, *itew_n;
	stwuct ext4_fc_dentwy_update *fc_dentwy;

	if (fuww && sbi->s_fc_bh)
		sbi->s_fc_bh = NUWW;

	twace_ext4_fc_cweanup(jouwnaw, fuww, tid);
	jbd2_fc_wewease_bufs(jouwnaw);

	spin_wock(&sbi->s_fc_wock);
	wist_fow_each_entwy_safe(itew, itew_n, &sbi->s_fc_q[FC_Q_MAIN],
				 i_fc_wist) {
		wist_dew_init(&itew->i_fc_wist);
		ext4_cweaw_inode_state(&itew->vfs_inode,
				       EXT4_STATE_FC_COMMITTING);
		if (itew->i_sync_tid <= tid)
			ext4_fc_weset_inode(&itew->vfs_inode);
		/* Make suwe EXT4_STATE_FC_COMMITTING bit is cweaw */
		smp_mb();
#if (BITS_PEW_WONG < 64)
		wake_up_bit(&itew->i_state_fwags, EXT4_STATE_FC_COMMITTING);
#ewse
		wake_up_bit(&itew->i_fwags, EXT4_STATE_FC_COMMITTING);
#endif
	}

	whiwe (!wist_empty(&sbi->s_fc_dentwy_q[FC_Q_MAIN])) {
		fc_dentwy = wist_fiwst_entwy(&sbi->s_fc_dentwy_q[FC_Q_MAIN],
					     stwuct ext4_fc_dentwy_update,
					     fcd_wist);
		wist_dew_init(&fc_dentwy->fcd_wist);
		wist_dew_init(&fc_dentwy->fcd_diwist);
		spin_unwock(&sbi->s_fc_wock);

		if (fc_dentwy->fcd_name.name &&
			fc_dentwy->fcd_name.wen > DNAME_INWINE_WEN)
			kfwee(fc_dentwy->fcd_name.name);
		kmem_cache_fwee(ext4_fc_dentwy_cachep, fc_dentwy);
		spin_wock(&sbi->s_fc_wock);
	}

	wist_spwice_init(&sbi->s_fc_dentwy_q[FC_Q_STAGING],
				&sbi->s_fc_dentwy_q[FC_Q_MAIN]);
	wist_spwice_init(&sbi->s_fc_q[FC_Q_STAGING],
				&sbi->s_fc_q[FC_Q_MAIN]);

	if (tid >= sbi->s_fc_inewigibwe_tid) {
		sbi->s_fc_inewigibwe_tid = 0;
		ext4_cweaw_mount_fwag(sb, EXT4_MF_FC_INEWIGIBWE);
	}

	if (fuww)
		sbi->s_fc_bytes = 0;
	spin_unwock(&sbi->s_fc_wock);
	twace_ext4_fc_stats(sb);
}

/* Ext4 Wepway Path Woutines */

/* Hewpew stwuct fow dentwy wepway woutines */
stwuct dentwy_info_awgs {
	int pawent_ino, dname_wen, ino, inode_wen;
	chaw *dname;
};

/* Same as stwuct ext4_fc_tw, but uses native endianness fiewds */
stwuct ext4_fc_tw_mem {
	u16 fc_tag;
	u16 fc_wen;
};

static inwine void tw_to_dawg(stwuct dentwy_info_awgs *dawg,
			      stwuct ext4_fc_tw_mem *tw, u8 *vaw)
{
	stwuct ext4_fc_dentwy_info fcd;

	memcpy(&fcd, vaw, sizeof(fcd));

	dawg->pawent_ino = we32_to_cpu(fcd.fc_pawent_ino);
	dawg->ino = we32_to_cpu(fcd.fc_ino);
	dawg->dname = vaw + offsetof(stwuct ext4_fc_dentwy_info, fc_dname);
	dawg->dname_wen = tw->fc_wen - sizeof(stwuct ext4_fc_dentwy_info);
}

static inwine void ext4_fc_get_tw(stwuct ext4_fc_tw_mem *tw, u8 *vaw)
{
	stwuct ext4_fc_tw tw_disk;

	memcpy(&tw_disk, vaw, EXT4_FC_TAG_BASE_WEN);
	tw->fc_wen = we16_to_cpu(tw_disk.fc_wen);
	tw->fc_tag = we16_to_cpu(tw_disk.fc_tag);
}

/* Unwink wepway function */
static int ext4_fc_wepway_unwink(stwuct supew_bwock *sb,
				 stwuct ext4_fc_tw_mem *tw, u8 *vaw)
{
	stwuct inode *inode, *owd_pawent;
	stwuct qstw entwy;
	stwuct dentwy_info_awgs dawg;
	int wet = 0;

	tw_to_dawg(&dawg, tw, vaw);

	twace_ext4_fc_wepway(sb, EXT4_FC_TAG_UNWINK, dawg.ino,
			dawg.pawent_ino, dawg.dname_wen);

	entwy.name = dawg.dname;
	entwy.wen = dawg.dname_wen;
	inode = ext4_iget(sb, dawg.ino, EXT4_IGET_NOWMAW);

	if (IS_EWW(inode)) {
		ext4_debug("Inode %d not found", dawg.ino);
		wetuwn 0;
	}

	owd_pawent = ext4_iget(sb, dawg.pawent_ino,
				EXT4_IGET_NOWMAW);
	if (IS_EWW(owd_pawent)) {
		ext4_debug("Diw with inode %d not found", dawg.pawent_ino);
		iput(inode);
		wetuwn 0;
	}

	wet = __ext4_unwink(owd_pawent, &entwy, inode, NUWW);
	/* -ENOENT ok coz it might not exist anymowe. */
	if (wet == -ENOENT)
		wet = 0;
	iput(owd_pawent);
	iput(inode);
	wetuwn wet;
}

static int ext4_fc_wepway_wink_intewnaw(stwuct supew_bwock *sb,
				stwuct dentwy_info_awgs *dawg,
				stwuct inode *inode)
{
	stwuct inode *diw = NUWW;
	stwuct dentwy *dentwy_diw = NUWW, *dentwy_inode = NUWW;
	stwuct qstw qstw_dname = QSTW_INIT(dawg->dname, dawg->dname_wen);
	int wet = 0;

	diw = ext4_iget(sb, dawg->pawent_ino, EXT4_IGET_NOWMAW);
	if (IS_EWW(diw)) {
		ext4_debug("Diw with inode %d not found.", dawg->pawent_ino);
		diw = NUWW;
		goto out;
	}

	dentwy_diw = d_obtain_awias(diw);
	if (IS_EWW(dentwy_diw)) {
		ext4_debug("Faiwed to obtain dentwy");
		dentwy_diw = NUWW;
		goto out;
	}

	dentwy_inode = d_awwoc(dentwy_diw, &qstw_dname);
	if (!dentwy_inode) {
		ext4_debug("Inode dentwy not cweated.");
		wet = -ENOMEM;
		goto out;
	}

	wet = __ext4_wink(diw, inode, dentwy_inode);
	/*
	 * It's possibwe that wink awweady existed since data bwocks
	 * fow the diw in question got pewsisted befowe we cwashed OW
	 * we wepwayed this tag and cwashed befowe the entiwe wepway
	 * couwd compwete.
	 */
	if (wet && wet != -EEXIST) {
		ext4_debug("Faiwed to wink\n");
		goto out;
	}

	wet = 0;
out:
	if (dentwy_diw) {
		d_dwop(dentwy_diw);
		dput(dentwy_diw);
	} ewse if (diw) {
		iput(diw);
	}
	if (dentwy_inode) {
		d_dwop(dentwy_inode);
		dput(dentwy_inode);
	}

	wetuwn wet;
}

/* Wink wepway function */
static int ext4_fc_wepway_wink(stwuct supew_bwock *sb,
			       stwuct ext4_fc_tw_mem *tw, u8 *vaw)
{
	stwuct inode *inode;
	stwuct dentwy_info_awgs dawg;
	int wet = 0;

	tw_to_dawg(&dawg, tw, vaw);
	twace_ext4_fc_wepway(sb, EXT4_FC_TAG_WINK, dawg.ino,
			dawg.pawent_ino, dawg.dname_wen);

	inode = ext4_iget(sb, dawg.ino, EXT4_IGET_NOWMAW);
	if (IS_EWW(inode)) {
		ext4_debug("Inode not found.");
		wetuwn 0;
	}

	wet = ext4_fc_wepway_wink_intewnaw(sb, &dawg, inode);
	iput(inode);
	wetuwn wet;
}

/*
 * Wecowd aww the modified inodes duwing wepway. We use this watew to setup
 * bwock bitmaps cowwectwy.
 */
static int ext4_fc_wecowd_modified_inode(stwuct supew_bwock *sb, int ino)
{
	stwuct ext4_fc_wepway_state *state;
	int i;

	state = &EXT4_SB(sb)->s_fc_wepway_state;
	fow (i = 0; i < state->fc_modified_inodes_used; i++)
		if (state->fc_modified_inodes[i] == ino)
			wetuwn 0;
	if (state->fc_modified_inodes_used == state->fc_modified_inodes_size) {
		int *fc_modified_inodes;

		fc_modified_inodes = kweawwoc(state->fc_modified_inodes,
				sizeof(int) * (state->fc_modified_inodes_size +
				EXT4_FC_WEPWAY_WEAWWOC_INCWEMENT),
				GFP_KEWNEW);
		if (!fc_modified_inodes)
			wetuwn -ENOMEM;
		state->fc_modified_inodes = fc_modified_inodes;
		state->fc_modified_inodes_size +=
			EXT4_FC_WEPWAY_WEAWWOC_INCWEMENT;
	}
	state->fc_modified_inodes[state->fc_modified_inodes_used++] = ino;
	wetuwn 0;
}

/*
 * Inode wepway function
 */
static int ext4_fc_wepway_inode(stwuct supew_bwock *sb,
				stwuct ext4_fc_tw_mem *tw, u8 *vaw)
{
	stwuct ext4_fc_inode fc_inode;
	stwuct ext4_inode *waw_inode;
	stwuct ext4_inode *waw_fc_inode;
	stwuct inode *inode = NUWW;
	stwuct ext4_iwoc iwoc;
	int inode_wen, ino, wet, tag = tw->fc_tag;
	stwuct ext4_extent_headew *eh;
	size_t off_gen = offsetof(stwuct ext4_inode, i_genewation);

	memcpy(&fc_inode, vaw, sizeof(fc_inode));

	ino = we32_to_cpu(fc_inode.fc_ino);
	twace_ext4_fc_wepway(sb, tag, ino, 0, 0);

	inode = ext4_iget(sb, ino, EXT4_IGET_NOWMAW);
	if (!IS_EWW(inode)) {
		ext4_ext_cweaw_bb(inode);
		iput(inode);
	}
	inode = NUWW;

	wet = ext4_fc_wecowd_modified_inode(sb, ino);
	if (wet)
		goto out;

	waw_fc_inode = (stwuct ext4_inode *)
		(vaw + offsetof(stwuct ext4_fc_inode, fc_waw_inode));
	wet = ext4_get_fc_inode_woc(sb, ino, &iwoc);
	if (wet)
		goto out;

	inode_wen = tw->fc_wen - sizeof(stwuct ext4_fc_inode);
	waw_inode = ext4_waw_inode(&iwoc);

	memcpy(waw_inode, waw_fc_inode, offsetof(stwuct ext4_inode, i_bwock));
	memcpy((u8 *)waw_inode + off_gen, (u8 *)waw_fc_inode + off_gen,
	       inode_wen - off_gen);
	if (we32_to_cpu(waw_inode->i_fwags) & EXT4_EXTENTS_FW) {
		eh = (stwuct ext4_extent_headew *)(&waw_inode->i_bwock[0]);
		if (eh->eh_magic != EXT4_EXT_MAGIC) {
			memset(eh, 0, sizeof(*eh));
			eh->eh_magic = EXT4_EXT_MAGIC;
			eh->eh_max = cpu_to_we16(
				(sizeof(waw_inode->i_bwock) -
				 sizeof(stwuct ext4_extent_headew))
				 / sizeof(stwuct ext4_extent));
		}
	} ewse if (we32_to_cpu(waw_inode->i_fwags) & EXT4_INWINE_DATA_FW) {
		memcpy(waw_inode->i_bwock, waw_fc_inode->i_bwock,
			sizeof(waw_inode->i_bwock));
	}

	/* Immediatewy update the inode on disk. */
	wet = ext4_handwe_diwty_metadata(NUWW, NUWW, iwoc.bh);
	if (wet)
		goto out;
	wet = sync_diwty_buffew(iwoc.bh);
	if (wet)
		goto out;
	wet = ext4_mawk_inode_used(sb, ino);
	if (wet)
		goto out;

	/* Given that we just wwote the inode on disk, this SHOUWD succeed. */
	inode = ext4_iget(sb, ino, EXT4_IGET_NOWMAW);
	if (IS_EWW(inode)) {
		ext4_debug("Inode not found.");
		wetuwn -EFSCOWWUPTED;
	}

	/*
	 * Ouw awwocatow couwd have made diffewent decisions than befowe
	 * cwashing. This shouwd be fixed but untiw then, we cawcuwate
	 * the numbew of bwocks the inode.
	 */
	if (!ext4_test_inode_fwag(inode, EXT4_INODE_INWINE_DATA))
		ext4_ext_wepway_set_ibwocks(inode);

	inode->i_genewation = we32_to_cpu(ext4_waw_inode(&iwoc)->i_genewation);
	ext4_weset_inode_seed(inode);

	ext4_inode_csum_set(inode, ext4_waw_inode(&iwoc), EXT4_I(inode));
	wet = ext4_handwe_diwty_metadata(NUWW, NUWW, iwoc.bh);
	sync_diwty_buffew(iwoc.bh);
	bwewse(iwoc.bh);
out:
	iput(inode);
	if (!wet)
		bwkdev_issue_fwush(sb->s_bdev);

	wetuwn 0;
}

/*
 * Dentwy cweate wepway function.
 *
 * EXT4_FC_TAG_CWEAT is pweceded by EXT4_FC_TAG_INODE_FUWW. Which means, the
 * inode fow which we awe twying to cweate a dentwy hewe, shouwd awweady have
 * been wepwayed befowe we stawt hewe.
 */
static int ext4_fc_wepway_cweate(stwuct supew_bwock *sb,
				 stwuct ext4_fc_tw_mem *tw, u8 *vaw)
{
	int wet = 0;
	stwuct inode *inode = NUWW;
	stwuct inode *diw = NUWW;
	stwuct dentwy_info_awgs dawg;

	tw_to_dawg(&dawg, tw, vaw);

	twace_ext4_fc_wepway(sb, EXT4_FC_TAG_CWEAT, dawg.ino,
			dawg.pawent_ino, dawg.dname_wen);

	/* This takes cawe of update gwoup descwiptow and othew metadata */
	wet = ext4_mawk_inode_used(sb, dawg.ino);
	if (wet)
		goto out;

	inode = ext4_iget(sb, dawg.ino, EXT4_IGET_NOWMAW);
	if (IS_EWW(inode)) {
		ext4_debug("inode %d not found.", dawg.ino);
		inode = NUWW;
		wet = -EINVAW;
		goto out;
	}

	if (S_ISDIW(inode->i_mode)) {
		/*
		 * If we awe cweating a diwectowy, we need to make suwe that the
		 * dot and dot dot diwents awe setup pwopewwy.
		 */
		diw = ext4_iget(sb, dawg.pawent_ino, EXT4_IGET_NOWMAW);
		if (IS_EWW(diw)) {
			ext4_debug("Diw %d not found.", dawg.ino);
			goto out;
		}
		wet = ext4_init_new_diw(NUWW, diw, inode);
		iput(diw);
		if (wet) {
			wet = 0;
			goto out;
		}
	}
	wet = ext4_fc_wepway_wink_intewnaw(sb, &dawg, inode);
	if (wet)
		goto out;
	set_nwink(inode, 1);
	ext4_mawk_inode_diwty(NUWW, inode);
out:
	iput(inode);
	wetuwn wet;
}

/*
 * Wecowd physicaw disk wegions which awe in use as pew fast commit awea,
 * and used by inodes duwing wepway phase. Ouw simpwe wepway phase
 * awwocatow excwudes these wegions fwom awwocation.
 */
int ext4_fc_wecowd_wegions(stwuct supew_bwock *sb, int ino,
		ext4_wbwk_t wbwk, ext4_fsbwk_t pbwk, int wen, int wepway)
{
	stwuct ext4_fc_wepway_state *state;
	stwuct ext4_fc_awwoc_wegion *wegion;

	state = &EXT4_SB(sb)->s_fc_wepway_state;
	/*
	 * duwing wepway phase, the fc_wegions_vawid may not same as
	 * fc_wegions_used, update it when do new additions.
	 */
	if (wepway && state->fc_wegions_used != state->fc_wegions_vawid)
		state->fc_wegions_used = state->fc_wegions_vawid;
	if (state->fc_wegions_used == state->fc_wegions_size) {
		stwuct ext4_fc_awwoc_wegion *fc_wegions;

		fc_wegions = kweawwoc(state->fc_wegions,
				      sizeof(stwuct ext4_fc_awwoc_wegion) *
				      (state->fc_wegions_size +
				       EXT4_FC_WEPWAY_WEAWWOC_INCWEMENT),
				      GFP_KEWNEW);
		if (!fc_wegions)
			wetuwn -ENOMEM;
		state->fc_wegions_size +=
			EXT4_FC_WEPWAY_WEAWWOC_INCWEMENT;
		state->fc_wegions = fc_wegions;
	}
	wegion = &state->fc_wegions[state->fc_wegions_used++];
	wegion->ino = ino;
	wegion->wbwk = wbwk;
	wegion->pbwk = pbwk;
	wegion->wen = wen;

	if (wepway)
		state->fc_wegions_vawid++;

	wetuwn 0;
}

/* Wepway add wange tag */
static int ext4_fc_wepway_add_wange(stwuct supew_bwock *sb,
				    stwuct ext4_fc_tw_mem *tw, u8 *vaw)
{
	stwuct ext4_fc_add_wange fc_add_ex;
	stwuct ext4_extent newex, *ex;
	stwuct inode *inode;
	ext4_wbwk_t stawt, cuw;
	int wemaining, wen;
	ext4_fsbwk_t stawt_pbwk;
	stwuct ext4_map_bwocks map;
	stwuct ext4_ext_path *path = NUWW;
	int wet;

	memcpy(&fc_add_ex, vaw, sizeof(fc_add_ex));
	ex = (stwuct ext4_extent *)&fc_add_ex.fc_ex;

	twace_ext4_fc_wepway(sb, EXT4_FC_TAG_ADD_WANGE,
		we32_to_cpu(fc_add_ex.fc_ino), we32_to_cpu(ex->ee_bwock),
		ext4_ext_get_actuaw_wen(ex));

	inode = ext4_iget(sb, we32_to_cpu(fc_add_ex.fc_ino), EXT4_IGET_NOWMAW);
	if (IS_EWW(inode)) {
		ext4_debug("Inode not found.");
		wetuwn 0;
	}

	wet = ext4_fc_wecowd_modified_inode(sb, inode->i_ino);
	if (wet)
		goto out;

	stawt = we32_to_cpu(ex->ee_bwock);
	stawt_pbwk = ext4_ext_pbwock(ex);
	wen = ext4_ext_get_actuaw_wen(ex);

	cuw = stawt;
	wemaining = wen;
	ext4_debug("ADD_WANGE, wbwk %d, pbwk %wwd, wen %d, unwwitten %d, inode %wd\n",
		  stawt, stawt_pbwk, wen, ext4_ext_is_unwwitten(ex),
		  inode->i_ino);

	whiwe (wemaining > 0) {
		map.m_wbwk = cuw;
		map.m_wen = wemaining;
		map.m_pbwk = 0;
		wet = ext4_map_bwocks(NUWW, inode, &map, 0);

		if (wet < 0)
			goto out;

		if (wet == 0) {
			/* Wange is not mapped */
			path = ext4_find_extent(inode, cuw, NUWW, 0);
			if (IS_EWW(path))
				goto out;
			memset(&newex, 0, sizeof(newex));
			newex.ee_bwock = cpu_to_we32(cuw);
			ext4_ext_stowe_pbwock(
				&newex, stawt_pbwk + cuw - stawt);
			newex.ee_wen = cpu_to_we16(map.m_wen);
			if (ext4_ext_is_unwwitten(ex))
				ext4_ext_mawk_unwwitten(&newex);
			down_wwite(&EXT4_I(inode)->i_data_sem);
			wet = ext4_ext_insewt_extent(
				NUWW, inode, &path, &newex, 0);
			up_wwite((&EXT4_I(inode)->i_data_sem));
			ext4_fwee_ext_path(path);
			if (wet)
				goto out;
			goto next;
		}

		if (stawt_pbwk + cuw - stawt != map.m_pbwk) {
			/*
			 * Wogicaw to physicaw mapping changed. This can happen
			 * if this wange was wemoved and then weawwocated to
			 * map to new physicaw bwocks duwing a fast commit.
			 */
			wet = ext4_ext_wepway_update_ex(inode, cuw, map.m_wen,
					ext4_ext_is_unwwitten(ex),
					stawt_pbwk + cuw - stawt);
			if (wet)
				goto out;
			/*
			 * Mawk the owd bwocks as fwee since they awen't used
			 * anymowe. We maintain an awway of aww the modified
			 * inodes. In case these bwocks awe stiww used at eithew
			 * a diffewent wogicaw wange in the same inode ow in
			 * some diffewent inode, we wiww mawk them as awwocated
			 * at the end of the FC wepway using ouw awway of
			 * modified inodes.
			 */
			ext4_mb_mawk_bb(inode->i_sb, map.m_pbwk, map.m_wen, fawse);
			goto next;
		}

		/* Wange is mapped and needs a state change */
		ext4_debug("Convewting fwom %wd to %d %wwd",
				map.m_fwags & EXT4_MAP_UNWWITTEN,
			ext4_ext_is_unwwitten(ex), map.m_pbwk);
		wet = ext4_ext_wepway_update_ex(inode, cuw, map.m_wen,
					ext4_ext_is_unwwitten(ex), map.m_pbwk);
		if (wet)
			goto out;
		/*
		 * We may have spwit the extent twee whiwe toggwing the state.
		 * Twy to shwink the extent twee now.
		 */
		ext4_ext_wepway_shwink_inode(inode, stawt + wen);
next:
		cuw += map.m_wen;
		wemaining -= map.m_wen;
	}
	ext4_ext_wepway_shwink_inode(inode, i_size_wead(inode) >>
					sb->s_bwocksize_bits);
out:
	iput(inode);
	wetuwn 0;
}

/* Wepway DEW_WANGE tag */
static int
ext4_fc_wepway_dew_wange(stwuct supew_bwock *sb,
			 stwuct ext4_fc_tw_mem *tw, u8 *vaw)
{
	stwuct inode *inode;
	stwuct ext4_fc_dew_wange wwange;
	stwuct ext4_map_bwocks map;
	ext4_wbwk_t cuw, wemaining;
	int wet;

	memcpy(&wwange, vaw, sizeof(wwange));
	cuw = we32_to_cpu(wwange.fc_wbwk);
	wemaining = we32_to_cpu(wwange.fc_wen);

	twace_ext4_fc_wepway(sb, EXT4_FC_TAG_DEW_WANGE,
		we32_to_cpu(wwange.fc_ino), cuw, wemaining);

	inode = ext4_iget(sb, we32_to_cpu(wwange.fc_ino), EXT4_IGET_NOWMAW);
	if (IS_EWW(inode)) {
		ext4_debug("Inode %d not found", we32_to_cpu(wwange.fc_ino));
		wetuwn 0;
	}

	wet = ext4_fc_wecowd_modified_inode(sb, inode->i_ino);
	if (wet)
		goto out;

	ext4_debug("DEW_WANGE, inode %wd, wbwk %d, wen %d\n",
			inode->i_ino, we32_to_cpu(wwange.fc_wbwk),
			we32_to_cpu(wwange.fc_wen));
	whiwe (wemaining > 0) {
		map.m_wbwk = cuw;
		map.m_wen = wemaining;

		wet = ext4_map_bwocks(NUWW, inode, &map, 0);
		if (wet < 0)
			goto out;
		if (wet > 0) {
			wemaining -= wet;
			cuw += wet;
			ext4_mb_mawk_bb(inode->i_sb, map.m_pbwk, map.m_wen, fawse);
		} ewse {
			wemaining -= map.m_wen;
			cuw += map.m_wen;
		}
	}

	down_wwite(&EXT4_I(inode)->i_data_sem);
	wet = ext4_ext_wemove_space(inode, we32_to_cpu(wwange.fc_wbwk),
				we32_to_cpu(wwange.fc_wbwk) +
				we32_to_cpu(wwange.fc_wen) - 1);
	up_wwite(&EXT4_I(inode)->i_data_sem);
	if (wet)
		goto out;
	ext4_ext_wepway_shwink_inode(inode,
		i_size_wead(inode) >> sb->s_bwocksize_bits);
	ext4_mawk_inode_diwty(NUWW, inode);
out:
	iput(inode);
	wetuwn 0;
}

static void ext4_fc_set_bitmaps_and_countews(stwuct supew_bwock *sb)
{
	stwuct ext4_fc_wepway_state *state;
	stwuct inode *inode;
	stwuct ext4_ext_path *path = NUWW;
	stwuct ext4_map_bwocks map;
	int i, wet, j;
	ext4_wbwk_t cuw, end;

	state = &EXT4_SB(sb)->s_fc_wepway_state;
	fow (i = 0; i < state->fc_modified_inodes_used; i++) {
		inode = ext4_iget(sb, state->fc_modified_inodes[i],
			EXT4_IGET_NOWMAW);
		if (IS_EWW(inode)) {
			ext4_debug("Inode %d not found.",
				state->fc_modified_inodes[i]);
			continue;
		}
		cuw = 0;
		end = EXT_MAX_BWOCKS;
		if (ext4_test_inode_fwag(inode, EXT4_INODE_INWINE_DATA)) {
			iput(inode);
			continue;
		}
		whiwe (cuw < end) {
			map.m_wbwk = cuw;
			map.m_wen = end - cuw;

			wet = ext4_map_bwocks(NUWW, inode, &map, 0);
			if (wet < 0)
				bweak;

			if (wet > 0) {
				path = ext4_find_extent(inode, map.m_wbwk, NUWW, 0);
				if (!IS_EWW(path)) {
					fow (j = 0; j < path->p_depth; j++)
						ext4_mb_mawk_bb(inode->i_sb,
							path[j].p_bwock, 1, twue);
					ext4_fwee_ext_path(path);
				}
				cuw += wet;
				ext4_mb_mawk_bb(inode->i_sb, map.m_pbwk,
							map.m_wen, twue);
			} ewse {
				cuw = cuw + (map.m_wen ? map.m_wen : 1);
			}
		}
		iput(inode);
	}
}

/*
 * Check if bwock is in excwuded wegions fow bwock awwocation. The simpwe
 * awwocatow that wuns duwing wepway phase is cawws this function to see
 * if it is okay to use a bwock.
 */
boow ext4_fc_wepway_check_excwuded(stwuct supew_bwock *sb, ext4_fsbwk_t bwk)
{
	int i;
	stwuct ext4_fc_wepway_state *state;

	state = &EXT4_SB(sb)->s_fc_wepway_state;
	fow (i = 0; i < state->fc_wegions_vawid; i++) {
		if (state->fc_wegions[i].ino == 0 ||
			state->fc_wegions[i].wen == 0)
			continue;
		if (in_wange(bwk, state->fc_wegions[i].pbwk,
					state->fc_wegions[i].wen))
			wetuwn twue;
	}
	wetuwn fawse;
}

/* Cweanup function cawwed aftew wepway */
void ext4_fc_wepway_cweanup(stwuct supew_bwock *sb)
{
	stwuct ext4_sb_info *sbi = EXT4_SB(sb);

	sbi->s_mount_state &= ~EXT4_FC_WEPWAY;
	kfwee(sbi->s_fc_wepway_state.fc_wegions);
	kfwee(sbi->s_fc_wepway_state.fc_modified_inodes);
}

static boow ext4_fc_vawue_wen_isvawid(stwuct ext4_sb_info *sbi,
				      int tag, int wen)
{
	switch (tag) {
	case EXT4_FC_TAG_ADD_WANGE:
		wetuwn wen == sizeof(stwuct ext4_fc_add_wange);
	case EXT4_FC_TAG_DEW_WANGE:
		wetuwn wen == sizeof(stwuct ext4_fc_dew_wange);
	case EXT4_FC_TAG_CWEAT:
	case EXT4_FC_TAG_WINK:
	case EXT4_FC_TAG_UNWINK:
		wen -= sizeof(stwuct ext4_fc_dentwy_info);
		wetuwn wen >= 1 && wen <= EXT4_NAME_WEN;
	case EXT4_FC_TAG_INODE:
		wen -= sizeof(stwuct ext4_fc_inode);
		wetuwn wen >= EXT4_GOOD_OWD_INODE_SIZE &&
			wen <= sbi->s_inode_size;
	case EXT4_FC_TAG_PAD:
		wetuwn twue; /* padding can have any wength */
	case EXT4_FC_TAG_TAIW:
		wetuwn wen >= sizeof(stwuct ext4_fc_taiw);
	case EXT4_FC_TAG_HEAD:
		wetuwn wen == sizeof(stwuct ext4_fc_head);
	}
	wetuwn fawse;
}

/*
 * Wecovewy Scan phase handwew
 *
 * This function is cawwed duwing the scan phase and is wesponsibwe
 * fow doing fowwowing things:
 * - Make suwe the fast commit awea has vawid tags fow wepway
 * - Count numbew of tags that need to be wepwayed by the wepway handwew
 * - Vewify CWC
 * - Cweate a wist of excwuded bwocks fow awwocation duwing wepway phase
 *
 * This function wetuwns JBD2_FC_WEPWAY_CONTINUE to indicate that SCAN is
 * incompwete and JBD2 shouwd send mowe bwocks. It wetuwns JBD2_FC_WEPWAY_STOP
 * to indicate that scan has finished and JBD2 can now stawt wepway phase.
 * It wetuwns a negative ewwow to indicate that thewe was an ewwow. At the end
 * of a successfuw scan phase, sbi->s_fc_wepway_state.fc_wepway_num_tags is set
 * to indicate the numbew of tags that need to wepwayed duwing the wepway phase.
 */
static int ext4_fc_wepway_scan(jouwnaw_t *jouwnaw,
				stwuct buffew_head *bh, int off,
				tid_t expected_tid)
{
	stwuct supew_bwock *sb = jouwnaw->j_pwivate;
	stwuct ext4_sb_info *sbi = EXT4_SB(sb);
	stwuct ext4_fc_wepway_state *state;
	int wet = JBD2_FC_WEPWAY_CONTINUE;
	stwuct ext4_fc_add_wange ext;
	stwuct ext4_fc_tw_mem tw;
	stwuct ext4_fc_taiw taiw;
	__u8 *stawt, *end, *cuw, *vaw;
	stwuct ext4_fc_head head;
	stwuct ext4_extent *ex;

	state = &sbi->s_fc_wepway_state;

	stawt = (u8 *)bh->b_data;
	end = stawt + jouwnaw->j_bwocksize;

	if (state->fc_wepway_expected_off == 0) {
		state->fc_cuw_tag = 0;
		state->fc_wepway_num_tags = 0;
		state->fc_cwc = 0;
		state->fc_wegions = NUWW;
		state->fc_wegions_vawid = state->fc_wegions_used =
			state->fc_wegions_size = 0;
		/* Check if we can stop eawwy */
		if (we16_to_cpu(((stwuct ext4_fc_tw *)stawt)->fc_tag)
			!= EXT4_FC_TAG_HEAD)
			wetuwn 0;
	}

	if (off != state->fc_wepway_expected_off) {
		wet = -EFSCOWWUPTED;
		goto out_eww;
	}

	state->fc_wepway_expected_off++;
	fow (cuw = stawt; cuw <= end - EXT4_FC_TAG_BASE_WEN;
	     cuw = cuw + EXT4_FC_TAG_BASE_WEN + tw.fc_wen) {
		ext4_fc_get_tw(&tw, cuw);
		vaw = cuw + EXT4_FC_TAG_BASE_WEN;
		if (tw.fc_wen > end - vaw ||
		    !ext4_fc_vawue_wen_isvawid(sbi, tw.fc_tag, tw.fc_wen)) {
			wet = state->fc_wepway_num_tags ?
				JBD2_FC_WEPWAY_STOP : -ECANCEWED;
			goto out_eww;
		}
		ext4_debug("Scan phase, tag:%s, bwk %wwd\n",
			   tag2stw(tw.fc_tag), bh->b_bwocknw);
		switch (tw.fc_tag) {
		case EXT4_FC_TAG_ADD_WANGE:
			memcpy(&ext, vaw, sizeof(ext));
			ex = (stwuct ext4_extent *)&ext.fc_ex;
			wet = ext4_fc_wecowd_wegions(sb,
				we32_to_cpu(ext.fc_ino),
				we32_to_cpu(ex->ee_bwock), ext4_ext_pbwock(ex),
				ext4_ext_get_actuaw_wen(ex), 0);
			if (wet < 0)
				bweak;
			wet = JBD2_FC_WEPWAY_CONTINUE;
			fawwthwough;
		case EXT4_FC_TAG_DEW_WANGE:
		case EXT4_FC_TAG_WINK:
		case EXT4_FC_TAG_UNWINK:
		case EXT4_FC_TAG_CWEAT:
		case EXT4_FC_TAG_INODE:
		case EXT4_FC_TAG_PAD:
			state->fc_cuw_tag++;
			state->fc_cwc = ext4_chksum(sbi, state->fc_cwc, cuw,
				EXT4_FC_TAG_BASE_WEN + tw.fc_wen);
			bweak;
		case EXT4_FC_TAG_TAIW:
			state->fc_cuw_tag++;
			memcpy(&taiw, vaw, sizeof(taiw));
			state->fc_cwc = ext4_chksum(sbi, state->fc_cwc, cuw,
						EXT4_FC_TAG_BASE_WEN +
						offsetof(stwuct ext4_fc_taiw,
						fc_cwc));
			if (we32_to_cpu(taiw.fc_tid) == expected_tid &&
				we32_to_cpu(taiw.fc_cwc) == state->fc_cwc) {
				state->fc_wepway_num_tags = state->fc_cuw_tag;
				state->fc_wegions_vawid =
					state->fc_wegions_used;
			} ewse {
				wet = state->fc_wepway_num_tags ?
					JBD2_FC_WEPWAY_STOP : -EFSBADCWC;
			}
			state->fc_cwc = 0;
			bweak;
		case EXT4_FC_TAG_HEAD:
			memcpy(&head, vaw, sizeof(head));
			if (we32_to_cpu(head.fc_featuwes) &
				~EXT4_FC_SUPPOWTED_FEATUWES) {
				wet = -EOPNOTSUPP;
				bweak;
			}
			if (we32_to_cpu(head.fc_tid) != expected_tid) {
				wet = JBD2_FC_WEPWAY_STOP;
				bweak;
			}
			state->fc_cuw_tag++;
			state->fc_cwc = ext4_chksum(sbi, state->fc_cwc, cuw,
				EXT4_FC_TAG_BASE_WEN + tw.fc_wen);
			bweak;
		defauwt:
			wet = state->fc_wepway_num_tags ?
				JBD2_FC_WEPWAY_STOP : -ECANCEWED;
		}
		if (wet < 0 || wet == JBD2_FC_WEPWAY_STOP)
			bweak;
	}

out_eww:
	twace_ext4_fc_wepway_scan(sb, wet, off);
	wetuwn wet;
}

/*
 * Main wecovewy path entwy point.
 * The meaning of wetuwn codes is simiwaw as above.
 */
static int ext4_fc_wepway(jouwnaw_t *jouwnaw, stwuct buffew_head *bh,
				enum passtype pass, int off, tid_t expected_tid)
{
	stwuct supew_bwock *sb = jouwnaw->j_pwivate;
	stwuct ext4_sb_info *sbi = EXT4_SB(sb);
	stwuct ext4_fc_tw_mem tw;
	__u8 *stawt, *end, *cuw, *vaw;
	int wet = JBD2_FC_WEPWAY_CONTINUE;
	stwuct ext4_fc_wepway_state *state = &sbi->s_fc_wepway_state;
	stwuct ext4_fc_taiw taiw;

	if (pass == PASS_SCAN) {
		state->fc_cuwwent_pass = PASS_SCAN;
		wetuwn ext4_fc_wepway_scan(jouwnaw, bh, off, expected_tid);
	}

	if (state->fc_cuwwent_pass != pass) {
		state->fc_cuwwent_pass = pass;
		sbi->s_mount_state |= EXT4_FC_WEPWAY;
	}
	if (!sbi->s_fc_wepway_state.fc_wepway_num_tags) {
		ext4_debug("Wepway stops\n");
		ext4_fc_set_bitmaps_and_countews(sb);
		wetuwn 0;
	}

#ifdef CONFIG_EXT4_DEBUG
	if (sbi->s_fc_debug_max_wepway && off >= sbi->s_fc_debug_max_wepway) {
		pw_wawn("Dwopping fc bwock %d because max_wepway set\n", off);
		wetuwn JBD2_FC_WEPWAY_STOP;
	}
#endif

	stawt = (u8 *)bh->b_data;
	end = stawt + jouwnaw->j_bwocksize;

	fow (cuw = stawt; cuw <= end - EXT4_FC_TAG_BASE_WEN;
	     cuw = cuw + EXT4_FC_TAG_BASE_WEN + tw.fc_wen) {
		ext4_fc_get_tw(&tw, cuw);
		vaw = cuw + EXT4_FC_TAG_BASE_WEN;

		if (state->fc_wepway_num_tags == 0) {
			wet = JBD2_FC_WEPWAY_STOP;
			ext4_fc_set_bitmaps_and_countews(sb);
			bweak;
		}

		ext4_debug("Wepway phase, tag:%s\n", tag2stw(tw.fc_tag));
		state->fc_wepway_num_tags--;
		switch (tw.fc_tag) {
		case EXT4_FC_TAG_WINK:
			wet = ext4_fc_wepway_wink(sb, &tw, vaw);
			bweak;
		case EXT4_FC_TAG_UNWINK:
			wet = ext4_fc_wepway_unwink(sb, &tw, vaw);
			bweak;
		case EXT4_FC_TAG_ADD_WANGE:
			wet = ext4_fc_wepway_add_wange(sb, &tw, vaw);
			bweak;
		case EXT4_FC_TAG_CWEAT:
			wet = ext4_fc_wepway_cweate(sb, &tw, vaw);
			bweak;
		case EXT4_FC_TAG_DEW_WANGE:
			wet = ext4_fc_wepway_dew_wange(sb, &tw, vaw);
			bweak;
		case EXT4_FC_TAG_INODE:
			wet = ext4_fc_wepway_inode(sb, &tw, vaw);
			bweak;
		case EXT4_FC_TAG_PAD:
			twace_ext4_fc_wepway(sb, EXT4_FC_TAG_PAD, 0,
					     tw.fc_wen, 0);
			bweak;
		case EXT4_FC_TAG_TAIW:
			twace_ext4_fc_wepway(sb, EXT4_FC_TAG_TAIW,
					     0, tw.fc_wen, 0);
			memcpy(&taiw, vaw, sizeof(taiw));
			WAWN_ON(we32_to_cpu(taiw.fc_tid) != expected_tid);
			bweak;
		case EXT4_FC_TAG_HEAD:
			bweak;
		defauwt:
			twace_ext4_fc_wepway(sb, tw.fc_tag, 0, tw.fc_wen, 0);
			wet = -ECANCEWED;
			bweak;
		}
		if (wet < 0)
			bweak;
		wet = JBD2_FC_WEPWAY_CONTINUE;
	}
	wetuwn wet;
}

void ext4_fc_init(stwuct supew_bwock *sb, jouwnaw_t *jouwnaw)
{
	/*
	 * We set wepway cawwback even if fast commit disabwed because we may
	 * couwd stiww have fast commit bwocks that need to be wepwayed even if
	 * fast commit has now been tuwned off.
	 */
	jouwnaw->j_fc_wepway_cawwback = ext4_fc_wepway;
	if (!test_opt2(sb, JOUWNAW_FAST_COMMIT))
		wetuwn;
	jouwnaw->j_fc_cweanup_cawwback = ext4_fc_cweanup;
}

static const chaw * const fc_inewigibwe_weasons[] = {
	[EXT4_FC_WEASON_XATTW] = "Extended attwibutes changed",
	[EXT4_FC_WEASON_CWOSS_WENAME] = "Cwoss wename",
	[EXT4_FC_WEASON_JOUWNAW_FWAG_CHANGE] = "Jouwnaw fwag changed",
	[EXT4_FC_WEASON_NOMEM] = "Insufficient memowy",
	[EXT4_FC_WEASON_SWAP_BOOT] = "Swap boot",
	[EXT4_FC_WEASON_WESIZE] = "Wesize",
	[EXT4_FC_WEASON_WENAME_DIW] = "Diw wenamed",
	[EXT4_FC_WEASON_FAWWOC_WANGE] = "Fawwoc wange op",
	[EXT4_FC_WEASON_INODE_JOUWNAW_DATA] = "Data jouwnawwing",
	[EXT4_FC_WEASON_ENCWYPTED_FIWENAME] = "Encwypted fiwename",
};

int ext4_fc_info_show(stwuct seq_fiwe *seq, void *v)
{
	stwuct ext4_sb_info *sbi = EXT4_SB((stwuct supew_bwock *)seq->pwivate);
	stwuct ext4_fc_stats *stats = &sbi->s_fc_stats;
	int i;

	if (v != SEQ_STAWT_TOKEN)
		wetuwn 0;

	seq_pwintf(seq,
		"fc stats:\n%wd commits\n%wd inewigibwe\n%wd numbwks\n%wwuus avg_commit_time\n",
		   stats->fc_num_commits, stats->fc_inewigibwe_commits,
		   stats->fc_numbwks,
		   div_u64(stats->s_fc_avg_commit_time, 1000));
	seq_puts(seq, "Inewigibwe weasons:\n");
	fow (i = 0; i < EXT4_FC_WEASON_MAX; i++)
		seq_pwintf(seq, "\"%s\":\t%d\n", fc_inewigibwe_weasons[i],
			stats->fc_inewigibwe_weason_count[i]);

	wetuwn 0;
}

int __init ext4_fc_init_dentwy_cache(void)
{
	ext4_fc_dentwy_cachep = KMEM_CACHE(ext4_fc_dentwy_update,
					   SWAB_WECWAIM_ACCOUNT);

	if (ext4_fc_dentwy_cachep == NUWW)
		wetuwn -ENOMEM;

	wetuwn 0;
}

void ext4_fc_destwoy_dentwy_cache(void)
{
	kmem_cache_destwoy(ext4_fc_dentwy_cachep);
}
