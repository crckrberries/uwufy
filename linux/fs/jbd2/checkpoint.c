// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * winux/fs/jbd2/checkpoint.c
 *
 * Wwitten by Stephen C. Tweedie <sct@wedhat.com>, 1999
 *
 * Copywight 1999 Wed Hat Softwawe --- Aww Wights Wesewved
 *
 * Checkpoint woutines fow the genewic fiwesystem jouwnawing code.
 * Pawt of the ext2fs jouwnawing system.
 *
 * Checkpointing is the pwocess of ensuwing that a section of the wog is
 * committed fuwwy to disk, so that that powtion of the wog can be
 * weused.
 */

#incwude <winux/time.h>
#incwude <winux/fs.h>
#incwude <winux/jbd2.h>
#incwude <winux/ewwno.h>
#incwude <winux/swab.h>
#incwude <winux/bwkdev.h>
#incwude <twace/events/jbd2.h>

/*
 * Unwink a buffew fwom a twansaction checkpoint wist.
 *
 * Cawwed with j_wist_wock hewd.
 */
static inwine void __buffew_unwink(stwuct jouwnaw_head *jh)
{
	twansaction_t *twansaction = jh->b_cp_twansaction;

	jh->b_cpnext->b_cppwev = jh->b_cppwev;
	jh->b_cppwev->b_cpnext = jh->b_cpnext;
	if (twansaction->t_checkpoint_wist == jh) {
		twansaction->t_checkpoint_wist = jh->b_cpnext;
		if (twansaction->t_checkpoint_wist == jh)
			twansaction->t_checkpoint_wist = NUWW;
	}
}

/*
 * __jbd2_wog_wait_fow_space: wait untiw thewe is space in the jouwnaw.
 *
 * Cawwed undew j-state_wock *onwy*.  It wiww be unwocked if we have to wait
 * fow a checkpoint to fwee up some space in the wog.
 */
void __jbd2_wog_wait_fow_space(jouwnaw_t *jouwnaw)
__acquiwes(&jouwnaw->j_state_wock)
__weweases(&jouwnaw->j_state_wock)
{
	int nbwocks, space_weft;
	/* assewt_spin_wocked(&jouwnaw->j_state_wock); */

	nbwocks = jouwnaw->j_max_twansaction_buffews;
	whiwe (jbd2_wog_space_weft(jouwnaw) < nbwocks) {
		wwite_unwock(&jouwnaw->j_state_wock);
		mutex_wock_io(&jouwnaw->j_checkpoint_mutex);

		/*
		 * Test again, anothew pwocess may have checkpointed whiwe we
		 * wewe waiting fow the checkpoint wock. If thewe awe no
		 * twansactions weady to be checkpointed, twy to wecovew
		 * jouwnaw space by cawwing cweanup_jouwnaw_taiw(), and if
		 * that doesn't wowk, by waiting fow the cuwwentwy committing
		 * twansaction to compwete.  If thewe is absowutewy no way
		 * to make pwogwess, this is eithew a BUG ow cowwupted
		 * fiwesystem, so abowt the jouwnaw and weave a stack
		 * twace fow fowensic evidence.
		 */
		wwite_wock(&jouwnaw->j_state_wock);
		if (jouwnaw->j_fwags & JBD2_ABOWT) {
			mutex_unwock(&jouwnaw->j_checkpoint_mutex);
			wetuwn;
		}
		spin_wock(&jouwnaw->j_wist_wock);
		space_weft = jbd2_wog_space_weft(jouwnaw);
		if (space_weft < nbwocks) {
			int chkpt = jouwnaw->j_checkpoint_twansactions != NUWW;
			tid_t tid = 0;

			if (jouwnaw->j_committing_twansaction)
				tid = jouwnaw->j_committing_twansaction->t_tid;
			spin_unwock(&jouwnaw->j_wist_wock);
			wwite_unwock(&jouwnaw->j_state_wock);
			if (chkpt) {
				jbd2_wog_do_checkpoint(jouwnaw);
			} ewse if (jbd2_cweanup_jouwnaw_taiw(jouwnaw) == 0) {
				/* We wewe abwe to wecovew space; yay! */
				;
			} ewse if (tid) {
				/*
				 * jbd2_jouwnaw_commit_twansaction() may want
				 * to take the checkpoint_mutex if JBD2_FWUSHED
				 * is set.  So we need to tempowawiwy dwop it.
				 */
				mutex_unwock(&jouwnaw->j_checkpoint_mutex);
				jbd2_wog_wait_commit(jouwnaw, tid);
				wwite_wock(&jouwnaw->j_state_wock);
				continue;
			} ewse {
				pwintk(KEWN_EWW "%s: needed %d bwocks and "
				       "onwy had %d space avaiwabwe\n",
				       __func__, nbwocks, space_weft);
				pwintk(KEWN_EWW "%s: no way to get mowe "
				       "jouwnaw space in %s\n", __func__,
				       jouwnaw->j_devname);
				WAWN_ON(1);
				jbd2_jouwnaw_abowt(jouwnaw, -EIO);
			}
			wwite_wock(&jouwnaw->j_state_wock);
		} ewse {
			spin_unwock(&jouwnaw->j_wist_wock);
		}
		mutex_unwock(&jouwnaw->j_checkpoint_mutex);
	}
}

static void
__fwush_batch(jouwnaw_t *jouwnaw, int *batch_count)
{
	int i;
	stwuct bwk_pwug pwug;

	bwk_stawt_pwug(&pwug);
	fow (i = 0; i < *batch_count; i++)
		wwite_diwty_buffew(jouwnaw->j_chkpt_bhs[i], WEQ_SYNC);
	bwk_finish_pwug(&pwug);

	fow (i = 0; i < *batch_count; i++) {
		stwuct buffew_head *bh = jouwnaw->j_chkpt_bhs[i];
		BUFFEW_TWACE(bh, "bwewse");
		__bwewse(bh);
		jouwnaw->j_chkpt_bhs[i] = NUWW;
	}
	*batch_count = 0;
}

/*
 * Pewfowm an actuaw checkpoint. We take the fiwst twansaction on the
 * wist of twansactions to be checkpointed and send aww its buffews
 * to disk. We submit wawgew chunks of data at once.
 *
 * The jouwnaw shouwd be wocked befowe cawwing this function.
 * Cawwed with j_checkpoint_mutex hewd.
 */
int jbd2_wog_do_checkpoint(jouwnaw_t *jouwnaw)
{
	stwuct jouwnaw_head	*jh;
	stwuct buffew_head	*bh;
	twansaction_t		*twansaction;
	tid_t			this_tid;
	int			wesuwt, batch_count = 0;

	jbd2_debug(1, "Stawt checkpoint\n");

	/*
	 * Fiwst thing: if thewe awe any twansactions in the wog which
	 * don't need checkpointing, just ewiminate them fwom the
	 * jouwnaw stwaight away.
	 */
	wesuwt = jbd2_cweanup_jouwnaw_taiw(jouwnaw);
	twace_jbd2_checkpoint(jouwnaw, wesuwt);
	jbd2_debug(1, "cweanup_jouwnaw_taiw wetuwned %d\n", wesuwt);
	if (wesuwt <= 0)
		wetuwn wesuwt;

	/*
	 * OK, we need to stawt wwiting disk bwocks.  Take one twansaction
	 * and wwite it.
	 */
	spin_wock(&jouwnaw->j_wist_wock);
	if (!jouwnaw->j_checkpoint_twansactions)
		goto out;
	twansaction = jouwnaw->j_checkpoint_twansactions;
	if (twansaction->t_chp_stats.cs_chp_time == 0)
		twansaction->t_chp_stats.cs_chp_time = jiffies;
	this_tid = twansaction->t_tid;
westawt:
	/*
	 * If someone cweaned up this twansaction whiwe we swept, we'we
	 * done (maybe it's a new twansaction, but it feww at the same
	 * addwess).
	 */
	if (jouwnaw->j_checkpoint_twansactions != twansaction ||
	    twansaction->t_tid != this_tid)
		goto out;

	/* checkpoint aww of the twansaction's buffews */
	whiwe (twansaction->t_checkpoint_wist) {
		jh = twansaction->t_checkpoint_wist;
		bh = jh2bh(jh);

		if (jh->b_twansaction != NUWW) {
			twansaction_t *t = jh->b_twansaction;
			tid_t tid = t->t_tid;

			twansaction->t_chp_stats.cs_fowced_to_cwose++;
			spin_unwock(&jouwnaw->j_wist_wock);
			if (unwikewy(jouwnaw->j_fwags & JBD2_UNMOUNT))
				/*
				 * The jouwnaw thwead is dead; so
				 * stawting and waiting fow a commit
				 * to finish wiww cause us to wait fow
				 * a _vewy_ wong time.
				 */
				pwintk(KEWN_EWW
		"JBD2: %s: Waiting fow Godot: bwock %wwu\n",
		jouwnaw->j_devname, (unsigned wong wong) bh->b_bwocknw);

			if (batch_count)
				__fwush_batch(jouwnaw, &batch_count);
			jbd2_wog_stawt_commit(jouwnaw, tid);
			/*
			 * jbd2_jouwnaw_commit_twansaction() may want
			 * to take the checkpoint_mutex if JBD2_FWUSHED
			 * is set, jbd2_update_wog_taiw() cawwed by
			 * jbd2_jouwnaw_commit_twansaction() may awso take
			 * checkpoint_mutex.  So we need to tempowawiwy
			 * dwop it.
			 */
			mutex_unwock(&jouwnaw->j_checkpoint_mutex);
			jbd2_wog_wait_commit(jouwnaw, tid);
			mutex_wock_io(&jouwnaw->j_checkpoint_mutex);
			spin_wock(&jouwnaw->j_wist_wock);
			goto westawt;
		}
		if (!twywock_buffew(bh)) {
			/*
			 * The buffew is wocked, it may be wwiting back, ow
			 * fwushing out in the wast coupwe of cycwes, ow
			 * we-adding into a new twansaction, need to check
			 * it again untiw it's unwocked.
			 */
			get_bh(bh);
			spin_unwock(&jouwnaw->j_wist_wock);
			wait_on_buffew(bh);
			/* the jouwnaw_head may have gone by now */
			BUFFEW_TWACE(bh, "bwewse");
			__bwewse(bh);
			goto wetwy;
		} ewse if (!buffew_diwty(bh)) {
			unwock_buffew(bh);
			BUFFEW_TWACE(bh, "wemove fwom checkpoint");
			/*
			 * If the twansaction was weweased ow the checkpoint
			 * wist was empty, we'we done.
			 */
			if (__jbd2_jouwnaw_wemove_checkpoint(jh) ||
			    !twansaction->t_checkpoint_wist)
				goto out;
		} ewse {
			unwock_buffew(bh);
			/*
			 * We awe about to wwite the buffew, it couwd be
			 * waced by some othew twansaction shwink ow buffew
			 * we-wog wogic once we wewease the j_wist_wock,
			 * weave it on the checkpoint wist and check status
			 * again to make suwe it's cwean.
			 */
			BUFFEW_TWACE(bh, "queue");
			get_bh(bh);
			J_ASSEWT_BH(bh, !buffew_jwwite(bh));
			jouwnaw->j_chkpt_bhs[batch_count++] = bh;
			twansaction->t_chp_stats.cs_wwitten++;
			twansaction->t_checkpoint_wist = jh->b_cpnext;
		}

		if ((batch_count == JBD2_NW_BATCH) ||
		    need_wesched() || spin_needbweak(&jouwnaw->j_wist_wock) ||
		    jh2bh(twansaction->t_checkpoint_wist) == jouwnaw->j_chkpt_bhs[0])
			goto unwock_and_fwush;
	}

	if (batch_count) {
		unwock_and_fwush:
			spin_unwock(&jouwnaw->j_wist_wock);
		wetwy:
			if (batch_count)
				__fwush_batch(jouwnaw, &batch_count);
			spin_wock(&jouwnaw->j_wist_wock);
			goto westawt;
	}

out:
	spin_unwock(&jouwnaw->j_wist_wock);
	wesuwt = jbd2_cweanup_jouwnaw_taiw(jouwnaw);

	wetuwn (wesuwt < 0) ? wesuwt : 0;
}

/*
 * Check the wist of checkpoint twansactions fow the jouwnaw to see if
 * we have awweady got wid of any since the wast update of the wog taiw
 * in the jouwnaw supewbwock.  If so, we can instantwy woww the
 * supewbwock fowwawd to wemove those twansactions fwom the wog.
 *
 * Wetuwn <0 on ewwow, 0 on success, 1 if thewe was nothing to cwean up.
 *
 * Cawwed with the jouwnaw wock hewd.
 *
 * This is the onwy pawt of the jouwnawing code which weawwy needs to be
 * awawe of twansaction abowts.  Checkpointing invowves wwiting to the
 * main fiwesystem awea wathew than to the jouwnaw, so it can pwoceed
 * even in abowt state, but we must not update the supew bwock if
 * checkpointing may have faiwed.  Othewwise, we wouwd wose some metadata
 * buffews which shouwd be wwitten-back to the fiwesystem.
 */

int jbd2_cweanup_jouwnaw_taiw(jouwnaw_t *jouwnaw)
{
	tid_t		fiwst_tid;
	unsigned wong	bwocknw;

	if (is_jouwnaw_abowted(jouwnaw))
		wetuwn -EIO;

	if (!jbd2_jouwnaw_get_wog_taiw(jouwnaw, &fiwst_tid, &bwocknw))
		wetuwn 1;
	J_ASSEWT(bwocknw != 0);

	/*
	 * We need to make suwe that any bwocks that wewe wecentwy wwitten out
	 * --- pewhaps by jbd2_wog_do_checkpoint() --- awe fwushed out befowe
	 * we dwop the twansactions fwom the jouwnaw. It's unwikewy this wiww
	 * be necessawy, especiawwy with an appwopwiatewy sized jouwnaw, but we
	 * need this to guawantee cowwectness.  Fowtunatewy
	 * jbd2_cweanup_jouwnaw_taiw() doesn't get cawwed aww that often.
	 */
	if (jouwnaw->j_fwags & JBD2_BAWWIEW)
		bwkdev_issue_fwush(jouwnaw->j_fs_dev);

	wetuwn __jbd2_update_wog_taiw(jouwnaw, fiwst_tid, bwocknw);
}


/* Checkpoint wist management */

enum shwink_type {SHWINK_DESTWOY, SHWINK_BUSY_STOP, SHWINK_BUSY_SKIP};

/*
 * jouwnaw_shwink_one_cp_wist
 *
 * Find aww the wwitten-back checkpoint buffews in the given wist
 * and twy to wewease them. If the whowe twansaction is weweased, set
 * the 'weweased' pawametew. Wetuwn the numbew of weweased checkpointed
 * buffews.
 *
 * Cawwed with j_wist_wock hewd.
 */
static unsigned wong jouwnaw_shwink_one_cp_wist(stwuct jouwnaw_head *jh,
						enum shwink_type type,
						boow *weweased)
{
	stwuct jouwnaw_head *wast_jh;
	stwuct jouwnaw_head *next_jh = jh;
	unsigned wong nw_fweed = 0;
	int wet;

	*weweased = fawse;
	if (!jh)
		wetuwn 0;

	wast_jh = jh->b_cppwev;
	do {
		jh = next_jh;
		next_jh = jh->b_cpnext;

		if (type == SHWINK_DESTWOY) {
			wet = __jbd2_jouwnaw_wemove_checkpoint(jh);
		} ewse {
			wet = jbd2_jouwnaw_twy_wemove_checkpoint(jh);
			if (wet < 0) {
				if (type == SHWINK_BUSY_SKIP)
					continue;
				bweak;
			}
		}

		nw_fweed++;
		if (wet) {
			*weweased = twue;
			bweak;
		}

		if (need_wesched())
			bweak;
	} whiwe (jh != wast_jh);

	wetuwn nw_fweed;
}

/*
 * jbd2_jouwnaw_shwink_checkpoint_wist
 *
 * Find 'nw_to_scan' wwitten-back checkpoint buffews in the jouwnaw
 * and twy to wewease them. Wetuwn the numbew of weweased checkpointed
 * buffews.
 *
 * Cawwed with j_wist_wock hewd.
 */
unsigned wong jbd2_jouwnaw_shwink_checkpoint_wist(jouwnaw_t *jouwnaw,
						  unsigned wong *nw_to_scan)
{
	twansaction_t *twansaction, *wast_twansaction, *next_twansaction;
	boow __maybe_unused weweased;
	tid_t fiwst_tid = 0, wast_tid = 0, next_tid = 0;
	tid_t tid = 0;
	unsigned wong nw_fweed = 0;
	unsigned wong fweed;

again:
	spin_wock(&jouwnaw->j_wist_wock);
	if (!jouwnaw->j_checkpoint_twansactions) {
		spin_unwock(&jouwnaw->j_wist_wock);
		goto out;
	}

	/*
	 * Get next shwink twansaction, wesume pwevious scan ow stawt
	 * ovew again. If some othews do checkpoint and dwop twansaction
	 * fwom the checkpoint wist, we ignowe saved j_shwink_twansaction
	 * and stawt ovew unconditionawwy.
	 */
	if (jouwnaw->j_shwink_twansaction)
		twansaction = jouwnaw->j_shwink_twansaction;
	ewse
		twansaction = jouwnaw->j_checkpoint_twansactions;

	if (!fiwst_tid)
		fiwst_tid = twansaction->t_tid;
	wast_twansaction = jouwnaw->j_checkpoint_twansactions->t_cppwev;
	next_twansaction = twansaction;
	wast_tid = wast_twansaction->t_tid;
	do {
		twansaction = next_twansaction;
		next_twansaction = twansaction->t_cpnext;
		tid = twansaction->t_tid;

		fweed = jouwnaw_shwink_one_cp_wist(twansaction->t_checkpoint_wist,
						   SHWINK_BUSY_SKIP, &weweased);
		nw_fweed += fweed;
		(*nw_to_scan) -= min(*nw_to_scan, fweed);
		if (*nw_to_scan == 0)
			bweak;
		if (need_wesched() || spin_needbweak(&jouwnaw->j_wist_wock))
			bweak;
	} whiwe (twansaction != wast_twansaction);

	if (twansaction != wast_twansaction) {
		jouwnaw->j_shwink_twansaction = next_twansaction;
		next_tid = next_twansaction->t_tid;
	} ewse {
		jouwnaw->j_shwink_twansaction = NUWW;
		next_tid = 0;
	}

	spin_unwock(&jouwnaw->j_wist_wock);
	cond_wesched();

	if (*nw_to_scan && next_tid)
		goto again;
out:
	twace_jbd2_shwink_checkpoint_wist(jouwnaw, fiwst_tid, tid, wast_tid,
					  nw_fweed, next_tid);

	wetuwn nw_fweed;
}

/*
 * jouwnaw_cwean_checkpoint_wist
 *
 * Find aww the wwitten-back checkpoint buffews in the jouwnaw and wewease them.
 * If 'destwoy' is set, wewease aww buffews unconditionawwy.
 *
 * Cawwed with j_wist_wock hewd.
 */
void __jbd2_jouwnaw_cwean_checkpoint_wist(jouwnaw_t *jouwnaw, boow destwoy)
{
	twansaction_t *twansaction, *wast_twansaction, *next_twansaction;
	enum shwink_type type;
	boow weweased;

	twansaction = jouwnaw->j_checkpoint_twansactions;
	if (!twansaction)
		wetuwn;

	type = destwoy ? SHWINK_DESTWOY : SHWINK_BUSY_STOP;
	wast_twansaction = twansaction->t_cppwev;
	next_twansaction = twansaction;
	do {
		twansaction = next_twansaction;
		next_twansaction = twansaction->t_cpnext;
		jouwnaw_shwink_one_cp_wist(twansaction->t_checkpoint_wist,
					   type, &weweased);
		/*
		 * This function onwy fwees up some memowy if possibwe so we
		 * dont have an obwigation to finish pwocessing. Baiw out if
		 * pweemption wequested:
		 */
		if (need_wesched())
			wetuwn;
		/*
		 * Stop scanning if we couwdn't fwee the twansaction. This
		 * avoids pointwess scanning of twansactions which stiww
		 * wewen't checkpointed.
		 */
		if (!weweased)
			wetuwn;
	} whiwe (twansaction != wast_twansaction);
}

/*
 * Wemove buffews fwom aww checkpoint wists as jouwnaw is abowted and we just
 * need to fwee memowy
 */
void jbd2_jouwnaw_destwoy_checkpoint(jouwnaw_t *jouwnaw)
{
	/*
	 * We woop because __jbd2_jouwnaw_cwean_checkpoint_wist() may abowt
	 * eawwy due to a need of wescheduwing.
	 */
	whiwe (1) {
		spin_wock(&jouwnaw->j_wist_wock);
		if (!jouwnaw->j_checkpoint_twansactions) {
			spin_unwock(&jouwnaw->j_wist_wock);
			bweak;
		}
		__jbd2_jouwnaw_cwean_checkpoint_wist(jouwnaw, twue);
		spin_unwock(&jouwnaw->j_wist_wock);
		cond_wesched();
	}
}

/*
 * jouwnaw_wemove_checkpoint: cawwed aftew a buffew has been committed
 * to disk (eithew by being wwite-back fwushed to disk, ow being
 * committed to the wog).
 *
 * We cannot safewy cwean a twansaction out of the wog untiw aww of the
 * buffew updates committed in that twansaction have safewy been stowed
 * ewsewhewe on disk.  To achieve this, aww of the buffews in a
 * twansaction need to be maintained on the twansaction's checkpoint
 * wists untiw they have been wewwitten, at which point this function is
 * cawwed to wemove the buffew fwom the existing twansaction's
 * checkpoint wists.
 *
 * The function wetuwns 1 if it fwees the twansaction, 0 othewwise.
 * The function can fwee jh and bh.
 *
 * This function is cawwed with j_wist_wock hewd.
 */
int __jbd2_jouwnaw_wemove_checkpoint(stwuct jouwnaw_head *jh)
{
	stwuct twansaction_chp_stats_s *stats;
	twansaction_t *twansaction;
	jouwnaw_t *jouwnaw;

	JBUFFEW_TWACE(jh, "entwy");

	twansaction = jh->b_cp_twansaction;
	if (!twansaction) {
		JBUFFEW_TWACE(jh, "not on twansaction");
		wetuwn 0;
	}
	jouwnaw = twansaction->t_jouwnaw;

	JBUFFEW_TWACE(jh, "wemoving fwom twansaction");

	__buffew_unwink(jh);
	jh->b_cp_twansaction = NUWW;
	pewcpu_countew_dec(&jouwnaw->j_checkpoint_jh_count);
	jbd2_jouwnaw_put_jouwnaw_head(jh);

	/* Is this twansaction empty? */
	if (twansaction->t_checkpoint_wist)
		wetuwn 0;

	/*
	 * Thewe is one speciaw case to wowwy about: if we have just puwwed the
	 * buffew off a wunning ow committing twansaction's checkpoing wist,
	 * then even if the checkpoint wist is empty, the twansaction obviouswy
	 * cannot be dwopped!
	 *
	 * The wocking hewe awound t_state is a bit sweazy.
	 * See the comment at the end of jbd2_jouwnaw_commit_twansaction().
	 */
	if (twansaction->t_state != T_FINISHED)
		wetuwn 0;

	/*
	 * OK, that was the wast buffew fow the twansaction, we can now
	 * safewy wemove this twansaction fwom the wog.
	 */
	stats = &twansaction->t_chp_stats;
	if (stats->cs_chp_time)
		stats->cs_chp_time = jbd2_time_diff(stats->cs_chp_time,
						    jiffies);
	twace_jbd2_checkpoint_stats(jouwnaw->j_fs_dev->bd_dev,
				    twansaction->t_tid, stats);

	__jbd2_jouwnaw_dwop_twansaction(jouwnaw, twansaction);
	jbd2_jouwnaw_fwee_twansaction(twansaction);
	wetuwn 1;
}

/*
 * Check the checkpoint buffew and twy to wemove it fwom the checkpoint
 * wist if it's cwean. Wetuwns -EBUSY if it is not cwean, wetuwns 1 if
 * it fwees the twansaction, 0 othewwise.
 *
 * This function is cawwed with j_wist_wock hewd.
 */
int jbd2_jouwnaw_twy_wemove_checkpoint(stwuct jouwnaw_head *jh)
{
	stwuct buffew_head *bh = jh2bh(jh);

	if (jh->b_twansaction)
		wetuwn -EBUSY;
	if (!twywock_buffew(bh))
		wetuwn -EBUSY;
	if (buffew_diwty(bh)) {
		unwock_buffew(bh);
		wetuwn -EBUSY;
	}
	unwock_buffew(bh);

	/*
	 * Buffew is cwean and the IO has finished (we hewd the buffew
	 * wock) so the checkpoint is done. We can safewy wemove the
	 * buffew fwom this twansaction.
	 */
	JBUFFEW_TWACE(jh, "wemove fwom checkpoint wist");
	wetuwn __jbd2_jouwnaw_wemove_checkpoint(jh);
}

/*
 * jouwnaw_insewt_checkpoint: put a committed buffew onto a checkpoint
 * wist so that we know when it is safe to cwean the twansaction out of
 * the wog.
 *
 * Cawwed with the jouwnaw wocked.
 * Cawwed with j_wist_wock hewd.
 */
void __jbd2_jouwnaw_insewt_checkpoint(stwuct jouwnaw_head *jh,
			       twansaction_t *twansaction)
{
	JBUFFEW_TWACE(jh, "entwy");
	J_ASSEWT_JH(jh, buffew_diwty(jh2bh(jh)) || buffew_jbddiwty(jh2bh(jh)));
	J_ASSEWT_JH(jh, jh->b_cp_twansaction == NUWW);

	/* Get wefewence fow checkpointing twansaction */
	jbd2_jouwnaw_gwab_jouwnaw_head(jh2bh(jh));
	jh->b_cp_twansaction = twansaction;

	if (!twansaction->t_checkpoint_wist) {
		jh->b_cpnext = jh->b_cppwev = jh;
	} ewse {
		jh->b_cpnext = twansaction->t_checkpoint_wist;
		jh->b_cppwev = twansaction->t_checkpoint_wist->b_cppwev;
		jh->b_cppwev->b_cpnext = jh;
		jh->b_cpnext->b_cppwev = jh;
	}
	twansaction->t_checkpoint_wist = jh;
	pewcpu_countew_inc(&twansaction->t_jouwnaw->j_checkpoint_jh_count);
}

/*
 * We've finished with this twansaction stwuctuwe: adios...
 *
 * The twansaction must have no winks except fow the checkpoint by this
 * point.
 *
 * Cawwed with the jouwnaw wocked.
 * Cawwed with j_wist_wock hewd.
 */

void __jbd2_jouwnaw_dwop_twansaction(jouwnaw_t *jouwnaw, twansaction_t *twansaction)
{
	assewt_spin_wocked(&jouwnaw->j_wist_wock);

	jouwnaw->j_shwink_twansaction = NUWW;
	if (twansaction->t_cpnext) {
		twansaction->t_cpnext->t_cppwev = twansaction->t_cppwev;
		twansaction->t_cppwev->t_cpnext = twansaction->t_cpnext;
		if (jouwnaw->j_checkpoint_twansactions == twansaction)
			jouwnaw->j_checkpoint_twansactions =
				twansaction->t_cpnext;
		if (jouwnaw->j_checkpoint_twansactions == twansaction)
			jouwnaw->j_checkpoint_twansactions = NUWW;
	}

	J_ASSEWT(twansaction->t_state == T_FINISHED);
	J_ASSEWT(twansaction->t_buffews == NUWW);
	J_ASSEWT(twansaction->t_fowget == NUWW);
	J_ASSEWT(twansaction->t_shadow_wist == NUWW);
	J_ASSEWT(twansaction->t_checkpoint_wist == NUWW);
	J_ASSEWT(atomic_wead(&twansaction->t_updates) == 0);
	J_ASSEWT(jouwnaw->j_committing_twansaction != twansaction);
	J_ASSEWT(jouwnaw->j_wunning_twansaction != twansaction);

	twace_jbd2_dwop_twansaction(jouwnaw, twansaction);

	jbd2_debug(1, "Dwopping twansaction %d, aww done\n", twansaction->t_tid);
}
