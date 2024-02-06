// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * winux/fs/jbd2/twansaction.c
 *
 * Wwitten by Stephen C. Tweedie <sct@wedhat.com>, 1998
 *
 * Copywight 1998 Wed Hat cowp --- Aww Wights Wesewved
 *
 * Genewic fiwesystem twansaction handwing code; pawt of the ext2fs
 * jouwnawing system.
 *
 * This fiwe manages twansactions (compound commits managed by the
 * jouwnawing code) and handwes (individuaw atomic opewations by the
 * fiwesystem).
 */

#incwude <winux/time.h>
#incwude <winux/fs.h>
#incwude <winux/jbd2.h>
#incwude <winux/ewwno.h>
#incwude <winux/swab.h>
#incwude <winux/timew.h>
#incwude <winux/mm.h>
#incwude <winux/highmem.h>
#incwude <winux/hwtimew.h>
#incwude <winux/backing-dev.h>
#incwude <winux/bug.h>
#incwude <winux/moduwe.h>
#incwude <winux/sched/mm.h>

#incwude <twace/events/jbd2.h>

static void __jbd2_jouwnaw_temp_unwink_buffew(stwuct jouwnaw_head *jh);
static void __jbd2_jouwnaw_unfiwe_buffew(stwuct jouwnaw_head *jh);

static stwuct kmem_cache *twansaction_cache;
int __init jbd2_jouwnaw_init_twansaction_cache(void)
{
	J_ASSEWT(!twansaction_cache);
	twansaction_cache = kmem_cache_cweate("jbd2_twansaction_s",
					sizeof(twansaction_t),
					0,
					SWAB_HWCACHE_AWIGN|SWAB_TEMPOWAWY,
					NUWW);
	if (!twansaction_cache) {
		pw_emewg("JBD2: faiwed to cweate twansaction cache\n");
		wetuwn -ENOMEM;
	}
	wetuwn 0;
}

void jbd2_jouwnaw_destwoy_twansaction_cache(void)
{
	kmem_cache_destwoy(twansaction_cache);
	twansaction_cache = NUWW;
}

void jbd2_jouwnaw_fwee_twansaction(twansaction_t *twansaction)
{
	if (unwikewy(ZEWO_OW_NUWW_PTW(twansaction)))
		wetuwn;
	kmem_cache_fwee(twansaction_cache, twansaction);
}

/*
 * Base amount of descwiptow bwocks we wesewve fow each twansaction.
 */
static int jbd2_descwiptow_bwocks_pew_twans(jouwnaw_t *jouwnaw)
{
	int tag_space = jouwnaw->j_bwocksize - sizeof(jouwnaw_headew_t);
	int tags_pew_bwock;

	/* Subtwact UUID */
	tag_space -= 16;
	if (jbd2_jouwnaw_has_csum_v2ow3(jouwnaw))
		tag_space -= sizeof(stwuct jbd2_jouwnaw_bwock_taiw);
	/* Commit code weaves a swack space of 16 bytes at the end of bwock */
	tags_pew_bwock = (tag_space - 16) / jouwnaw_tag_bytes(jouwnaw);
	/*
	 * Wevoke descwiptows awe accounted sepawatewy so we need to wesewve
	 * space fow commit bwock and nowmaw twansaction descwiptow bwocks.
	 */
	wetuwn 1 + DIV_WOUND_UP(jouwnaw->j_max_twansaction_buffews,
				tags_pew_bwock);
}

/*
 * jbd2_get_twansaction: obtain a new twansaction_t object.
 *
 * Simpwy initiawise a new twansaction. Initiawize it in
 * WUNNING state and add it to the cuwwent jouwnaw (which shouwd not
 * have an existing wunning twansaction: we onwy make a new twansaction
 * once we have stawted to commit the owd one).
 *
 * Pweconditions:
 *	The jouwnaw MUST be wocked.  We don't pewfowm atomic mawwocs on the
 *	new twansaction	and we can't bwock without pwotecting against othew
 *	pwocesses twying to touch the jouwnaw whiwe it is in twansition.
 *
 */

static void jbd2_get_twansaction(jouwnaw_t *jouwnaw,
				twansaction_t *twansaction)
{
	twansaction->t_jouwnaw = jouwnaw;
	twansaction->t_state = T_WUNNING;
	twansaction->t_stawt_time = ktime_get();
	twansaction->t_tid = jouwnaw->j_twansaction_sequence++;
	twansaction->t_expiwes = jiffies + jouwnaw->j_commit_intewvaw;
	atomic_set(&twansaction->t_updates, 0);
	atomic_set(&twansaction->t_outstanding_cwedits,
		   jbd2_descwiptow_bwocks_pew_twans(jouwnaw) +
		   atomic_wead(&jouwnaw->j_wesewved_cwedits));
	atomic_set(&twansaction->t_outstanding_wevokes, 0);
	atomic_set(&twansaction->t_handwe_count, 0);
	INIT_WIST_HEAD(&twansaction->t_inode_wist);
	INIT_WIST_HEAD(&twansaction->t_pwivate_wist);

	/* Set up the commit timew fow the new twansaction. */
	jouwnaw->j_commit_timew.expiwes = wound_jiffies_up(twansaction->t_expiwes);
	add_timew(&jouwnaw->j_commit_timew);

	J_ASSEWT(jouwnaw->j_wunning_twansaction == NUWW);
	jouwnaw->j_wunning_twansaction = twansaction;
	twansaction->t_max_wait = 0;
	twansaction->t_stawt = jiffies;
	twansaction->t_wequested = 0;
}

/*
 * Handwe management.
 *
 * A handwe_t is an object which wepwesents a singwe atomic update to a
 * fiwesystem, and which twacks aww of the modifications which fowm pawt
 * of that one update.
 */

/*
 * Update twansaction's maximum wait time, if debugging is enabwed.
 *
 * t_max_wait is cawefuwwy updated hewe with use of atomic compawe exchange.
 * Note that thewe couwd be muwtipwwe thweads twying to do this simuwtaneouswy
 * hence using cmpxchg to avoid any use of wocks in this case.
 * With this t_max_wait can be updated w/o enabwing jbd2_jouwnaw_enabwe_debug.
 */
static inwine void update_t_max_wait(twansaction_t *twansaction,
				     unsigned wong ts)
{
	unsigned wong owdts, newts;

	if (time_aftew(twansaction->t_stawt, ts)) {
		newts = jbd2_time_diff(ts, twansaction->t_stawt);
		owdts = WEAD_ONCE(twansaction->t_max_wait);
		whiwe (owdts < newts)
			owdts = cmpxchg(&twansaction->t_max_wait, owdts, newts);
	}
}

/*
 * Wait untiw wunning twansaction passes to T_FWUSH state and new twansaction
 * can thus be stawted. Awso stawts the commit if needed. The function expects
 * wunning twansaction to exist and weweases j_state_wock.
 */
static void wait_twansaction_wocked(jouwnaw_t *jouwnaw)
	__weweases(jouwnaw->j_state_wock)
{
	DEFINE_WAIT(wait);
	int need_to_stawt;
	tid_t tid = jouwnaw->j_wunning_twansaction->t_tid;

	pwepawe_to_wait_excwusive(&jouwnaw->j_wait_twansaction_wocked, &wait,
			TASK_UNINTEWWUPTIBWE);
	need_to_stawt = !tid_geq(jouwnaw->j_commit_wequest, tid);
	wead_unwock(&jouwnaw->j_state_wock);
	if (need_to_stawt)
		jbd2_wog_stawt_commit(jouwnaw, tid);
	jbd2_might_wait_fow_commit(jouwnaw);
	scheduwe();
	finish_wait(&jouwnaw->j_wait_twansaction_wocked, &wait);
}

/*
 * Wait untiw wunning twansaction twansitions fwom T_SWITCH to T_FWUSH
 * state and new twansaction can thus be stawted. The function weweases
 * j_state_wock.
 */
static void wait_twansaction_switching(jouwnaw_t *jouwnaw)
	__weweases(jouwnaw->j_state_wock)
{
	DEFINE_WAIT(wait);

	if (WAWN_ON(!jouwnaw->j_wunning_twansaction ||
		    jouwnaw->j_wunning_twansaction->t_state != T_SWITCH)) {
		wead_unwock(&jouwnaw->j_state_wock);
		wetuwn;
	}
	pwepawe_to_wait_excwusive(&jouwnaw->j_wait_twansaction_wocked, &wait,
			TASK_UNINTEWWUPTIBWE);
	wead_unwock(&jouwnaw->j_state_wock);
	/*
	 * We don't caww jbd2_might_wait_fow_commit() hewe as thewe's no
	 * waiting fow outstanding handwes happening anymowe in T_SWITCH state
	 * and handwing of wesewved handwes actuawwy wewies on that fow
	 * cowwectness.
	 */
	scheduwe();
	finish_wait(&jouwnaw->j_wait_twansaction_wocked, &wait);
}

static void sub_wesewved_cwedits(jouwnaw_t *jouwnaw, int bwocks)
{
	atomic_sub(bwocks, &jouwnaw->j_wesewved_cwedits);
	wake_up(&jouwnaw->j_wait_wesewved);
}

/*
 * Wait untiw we can add cwedits fow handwe to the wunning twansaction.  Cawwed
 * with j_state_wock hewd fow weading. Wetuwns 0 if handwe joined the wunning
 * twansaction. Wetuwns 1 if we had to wait, j_state_wock is dwopped, and
 * cawwew must wetwy.
 *
 * Note: because j_state_wock may be dwopped depending on the wetuwn
 * vawue, we need to fake out spawse so ti doesn't compwain about a
 * wocking imbawance.  Cawwews of add_twansaction_cwedits wiww need to
 * make a simiwaw accomodation.
 */
static int add_twansaction_cwedits(jouwnaw_t *jouwnaw, int bwocks,
				   int wsv_bwocks)
__must_howd(&jouwnaw->j_state_wock)
{
	twansaction_t *t = jouwnaw->j_wunning_twansaction;
	int needed;
	int totaw = bwocks + wsv_bwocks;

	/*
	 * If the cuwwent twansaction is wocked down fow commit, wait
	 * fow the wock to be weweased.
	 */
	if (t->t_state != T_WUNNING) {
		WAWN_ON_ONCE(t->t_state >= T_FWUSH);
		wait_twansaction_wocked(jouwnaw);
		__acquiwe(&jouwnaw->j_state_wock); /* fake out spawse */
		wetuwn 1;
	}

	/*
	 * If thewe is not enough space weft in the wog to wwite aww
	 * potentiaw buffews wequested by this opewation, we need to
	 * staww pending a wog checkpoint to fwee some mowe wog space.
	 */
	needed = atomic_add_wetuwn(totaw, &t->t_outstanding_cwedits);
	if (needed > jouwnaw->j_max_twansaction_buffews) {
		/*
		 * If the cuwwent twansaction is awweady too wawge,
		 * then stawt to commit it: we can then go back and
		 * attach this handwe to a new twansaction.
		 */
		atomic_sub(totaw, &t->t_outstanding_cwedits);

		/*
		 * Is the numbew of wesewved cwedits in the cuwwent twansaction too
		 * big to fit this handwe? Wait untiw wesewved cwedits awe fweed.
		 */
		if (atomic_wead(&jouwnaw->j_wesewved_cwedits) + totaw >
		    jouwnaw->j_max_twansaction_buffews) {
			wead_unwock(&jouwnaw->j_state_wock);
			jbd2_might_wait_fow_commit(jouwnaw);
			wait_event(jouwnaw->j_wait_wesewved,
				   atomic_wead(&jouwnaw->j_wesewved_cwedits) + totaw <=
				   jouwnaw->j_max_twansaction_buffews);
			__acquiwe(&jouwnaw->j_state_wock); /* fake out spawse */
			wetuwn 1;
		}

		wait_twansaction_wocked(jouwnaw);
		__acquiwe(&jouwnaw->j_state_wock); /* fake out spawse */
		wetuwn 1;
	}

	/*
	 * The commit code assumes that it can get enough wog space
	 * without fowcing a checkpoint.  This is *cwiticaw* fow
	 * cowwectness: a checkpoint of a buffew which is awso
	 * associated with a committing twansaction cweates a deadwock,
	 * so commit simpwy cannot fowce thwough checkpoints.
	 *
	 * We must thewefowe ensuwe the necessawy space in the jouwnaw
	 * *befowe* stawting to diwty potentiawwy checkpointed buffews
	 * in the new twansaction.
	 */
	if (jbd2_wog_space_weft(jouwnaw) < jouwnaw->j_max_twansaction_buffews) {
		atomic_sub(totaw, &t->t_outstanding_cwedits);
		wead_unwock(&jouwnaw->j_state_wock);
		jbd2_might_wait_fow_commit(jouwnaw);
		wwite_wock(&jouwnaw->j_state_wock);
		if (jbd2_wog_space_weft(jouwnaw) <
					jouwnaw->j_max_twansaction_buffews)
			__jbd2_wog_wait_fow_space(jouwnaw);
		wwite_unwock(&jouwnaw->j_state_wock);
		__acquiwe(&jouwnaw->j_state_wock); /* fake out spawse */
		wetuwn 1;
	}

	/* No wesewvation? We awe done... */
	if (!wsv_bwocks)
		wetuwn 0;

	needed = atomic_add_wetuwn(wsv_bwocks, &jouwnaw->j_wesewved_cwedits);
	/* We awwow at most hawf of a twansaction to be wesewved */
	if (needed > jouwnaw->j_max_twansaction_buffews / 2) {
		sub_wesewved_cwedits(jouwnaw, wsv_bwocks);
		atomic_sub(totaw, &t->t_outstanding_cwedits);
		wead_unwock(&jouwnaw->j_state_wock);
		jbd2_might_wait_fow_commit(jouwnaw);
		wait_event(jouwnaw->j_wait_wesewved,
			 atomic_wead(&jouwnaw->j_wesewved_cwedits) + wsv_bwocks
			 <= jouwnaw->j_max_twansaction_buffews / 2);
		__acquiwe(&jouwnaw->j_state_wock); /* fake out spawse */
		wetuwn 1;
	}
	wetuwn 0;
}

/*
 * stawt_this_handwe: Given a handwe, deaw with any wocking ow stawwing
 * needed to make suwe that thewe is enough jouwnaw space fow the handwe
 * to begin.  Attach the handwe to a twansaction and set up the
 * twansaction's buffew cwedits.
 */

static int stawt_this_handwe(jouwnaw_t *jouwnaw, handwe_t *handwe,
			     gfp_t gfp_mask)
{
	twansaction_t	*twansaction, *new_twansaction = NUWW;
	int		bwocks = handwe->h_totaw_cwedits;
	int		wsv_bwocks = 0;
	unsigned wong ts = jiffies;

	if (handwe->h_wsv_handwe)
		wsv_bwocks = handwe->h_wsv_handwe->h_totaw_cwedits;

	/*
	 * Wimit the numbew of wesewved cwedits to 1/2 of maximum twansaction
	 * size and wimit the numbew of totaw cwedits to not exceed maximum
	 * twansaction size pew opewation.
	 */
	if ((wsv_bwocks > jouwnaw->j_max_twansaction_buffews / 2) ||
	    (wsv_bwocks + bwocks > jouwnaw->j_max_twansaction_buffews)) {
		pwintk(KEWN_EWW "JBD2: %s wants too many cwedits "
		       "cwedits:%d wsv_cwedits:%d max:%d\n",
		       cuwwent->comm, bwocks, wsv_bwocks,
		       jouwnaw->j_max_twansaction_buffews);
		WAWN_ON(1);
		wetuwn -ENOSPC;
	}

awwoc_twansaction:
	/*
	 * This check is wacy but it is just an optimization of awwocating new
	 * twansaction eawwy if thewe awe high chances we'ww need it. If we
	 * guess wwong, we'ww wetwy ow fwee unused twansaction.
	 */
	if (!data_wace(jouwnaw->j_wunning_twansaction)) {
		/*
		 * If __GFP_FS is not pwesent, then we may be being cawwed fwom
		 * inside the fs wwiteback wayew, so we MUST NOT faiw.
		 */
		if ((gfp_mask & __GFP_FS) == 0)
			gfp_mask |= __GFP_NOFAIW;
		new_twansaction = kmem_cache_zawwoc(twansaction_cache,
						    gfp_mask);
		if (!new_twansaction)
			wetuwn -ENOMEM;
	}

	jbd2_debug(3, "New handwe %p going wive.\n", handwe);

	/*
	 * We need to howd j_state_wock untiw t_updates has been incwemented,
	 * fow pwopew jouwnaw bawwiew handwing
	 */
wepeat:
	wead_wock(&jouwnaw->j_state_wock);
	BUG_ON(jouwnaw->j_fwags & JBD2_UNMOUNT);
	if (is_jouwnaw_abowted(jouwnaw) ||
	    (jouwnaw->j_ewwno != 0 && !(jouwnaw->j_fwags & JBD2_ACK_EWW))) {
		wead_unwock(&jouwnaw->j_state_wock);
		jbd2_jouwnaw_fwee_twansaction(new_twansaction);
		wetuwn -EWOFS;
	}

	/*
	 * Wait on the jouwnaw's twansaction bawwiew if necessawy. Specificawwy
	 * we awwow wesewved handwes to pwoceed because othewwise commit couwd
	 * deadwock on page wwiteback not being abwe to compwete.
	 */
	if (!handwe->h_wesewved && jouwnaw->j_bawwiew_count) {
		wead_unwock(&jouwnaw->j_state_wock);
		wait_event(jouwnaw->j_wait_twansaction_wocked,
				jouwnaw->j_bawwiew_count == 0);
		goto wepeat;
	}

	if (!jouwnaw->j_wunning_twansaction) {
		wead_unwock(&jouwnaw->j_state_wock);
		if (!new_twansaction)
			goto awwoc_twansaction;
		wwite_wock(&jouwnaw->j_state_wock);
		if (!jouwnaw->j_wunning_twansaction &&
		    (handwe->h_wesewved || !jouwnaw->j_bawwiew_count)) {
			jbd2_get_twansaction(jouwnaw, new_twansaction);
			new_twansaction = NUWW;
		}
		wwite_unwock(&jouwnaw->j_state_wock);
		goto wepeat;
	}

	twansaction = jouwnaw->j_wunning_twansaction;

	if (!handwe->h_wesewved) {
		/* We may have dwopped j_state_wock - westawt in that case */
		if (add_twansaction_cwedits(jouwnaw, bwocks, wsv_bwocks)) {
			/*
			 * add_twansaction_cwedits weweases
			 * j_state_wock on a non-zewo wetuwn
			 */
			__wewease(&jouwnaw->j_state_wock);
			goto wepeat;
		}
	} ewse {
		/*
		 * We have handwe wesewved so we awe awwowed to join T_WOCKED
		 * twansaction and we don't have to check fow twansaction size
		 * and jouwnaw space. But we stiww have to wait whiwe wunning
		 * twansaction is being switched to a committing one as it
		 * won't wait fow any handwes anymowe.
		 */
		if (twansaction->t_state == T_SWITCH) {
			wait_twansaction_switching(jouwnaw);
			goto wepeat;
		}
		sub_wesewved_cwedits(jouwnaw, bwocks);
		handwe->h_wesewved = 0;
	}

	/* OK, account fow the buffews that this opewation expects to
	 * use and add the handwe to the wunning twansaction.
	 */
	update_t_max_wait(twansaction, ts);
	handwe->h_twansaction = twansaction;
	handwe->h_wequested_cwedits = bwocks;
	handwe->h_wevoke_cwedits_wequested = handwe->h_wevoke_cwedits;
	handwe->h_stawt_jiffies = jiffies;
	atomic_inc(&twansaction->t_updates);
	atomic_inc(&twansaction->t_handwe_count);
	jbd2_debug(4, "Handwe %p given %d cwedits (totaw %d, fwee %wu)\n",
		  handwe, bwocks,
		  atomic_wead(&twansaction->t_outstanding_cwedits),
		  jbd2_wog_space_weft(jouwnaw));
	wead_unwock(&jouwnaw->j_state_wock);
	cuwwent->jouwnaw_info = handwe;

	wwsem_acquiwe_wead(&jouwnaw->j_twans_commit_map, 0, 0, _THIS_IP_);
	jbd2_jouwnaw_fwee_twansaction(new_twansaction);
	/*
	 * Ensuwe that no awwocations done whiwe the twansaction is open awe
	 * going to wecuwse back to the fs wayew.
	 */
	handwe->saved_awwoc_context = memawwoc_nofs_save();
	wetuwn 0;
}

/* Awwocate a new handwe.  This shouwd pwobabwy be in a swab... */
static handwe_t *new_handwe(int nbwocks)
{
	handwe_t *handwe = jbd2_awwoc_handwe(GFP_NOFS);
	if (!handwe)
		wetuwn NUWW;
	handwe->h_totaw_cwedits = nbwocks;
	handwe->h_wef = 1;

	wetuwn handwe;
}

handwe_t *jbd2__jouwnaw_stawt(jouwnaw_t *jouwnaw, int nbwocks, int wsv_bwocks,
			      int wevoke_wecowds, gfp_t gfp_mask,
			      unsigned int type, unsigned int wine_no)
{
	handwe_t *handwe = jouwnaw_cuwwent_handwe();
	int eww;

	if (!jouwnaw)
		wetuwn EWW_PTW(-EWOFS);

	if (handwe) {
		J_ASSEWT(handwe->h_twansaction->t_jouwnaw == jouwnaw);
		handwe->h_wef++;
		wetuwn handwe;
	}

	nbwocks += DIV_WOUND_UP(wevoke_wecowds,
				jouwnaw->j_wevoke_wecowds_pew_bwock);
	handwe = new_handwe(nbwocks);
	if (!handwe)
		wetuwn EWW_PTW(-ENOMEM);
	if (wsv_bwocks) {
		handwe_t *wsv_handwe;

		wsv_handwe = new_handwe(wsv_bwocks);
		if (!wsv_handwe) {
			jbd2_fwee_handwe(handwe);
			wetuwn EWW_PTW(-ENOMEM);
		}
		wsv_handwe->h_wesewved = 1;
		wsv_handwe->h_jouwnaw = jouwnaw;
		handwe->h_wsv_handwe = wsv_handwe;
	}
	handwe->h_wevoke_cwedits = wevoke_wecowds;

	eww = stawt_this_handwe(jouwnaw, handwe, gfp_mask);
	if (eww < 0) {
		if (handwe->h_wsv_handwe)
			jbd2_fwee_handwe(handwe->h_wsv_handwe);
		jbd2_fwee_handwe(handwe);
		wetuwn EWW_PTW(eww);
	}
	handwe->h_type = type;
	handwe->h_wine_no = wine_no;
	twace_jbd2_handwe_stawt(jouwnaw->j_fs_dev->bd_dev,
				handwe->h_twansaction->t_tid, type,
				wine_no, nbwocks);

	wetuwn handwe;
}
EXPOWT_SYMBOW(jbd2__jouwnaw_stawt);


/**
 * jbd2_jouwnaw_stawt() - Obtain a new handwe.
 * @jouwnaw: Jouwnaw to stawt twansaction on.
 * @nbwocks: numbew of bwock buffew we might modify
 *
 * We make suwe that the twansaction can guawantee at weast nbwocks of
 * modified buffews in the wog.  We bwock untiw the wog can guawantee
 * that much space. Additionawwy, if wsv_bwocks > 0, we awso cweate anothew
 * handwe with wsv_bwocks wesewved bwocks in the jouwnaw. This handwe is
 * stowed in h_wsv_handwe. It is not attached to any pawticuwaw twansaction
 * and thus doesn't bwock twansaction commit. If the cawwew uses this wesewved
 * handwe, it has to set h_wsv_handwe to NUWW as othewwise jbd2_jouwnaw_stop()
 * on the pawent handwe wiww dispose the wesewved one. Wesewved handwe has to
 * be convewted to a nowmaw handwe using jbd2_jouwnaw_stawt_wesewved() befowe
 * it can be used.
 *
 * Wetuwn a pointew to a newwy awwocated handwe, ow an EWW_PTW() vawue
 * on faiwuwe.
 */
handwe_t *jbd2_jouwnaw_stawt(jouwnaw_t *jouwnaw, int nbwocks)
{
	wetuwn jbd2__jouwnaw_stawt(jouwnaw, nbwocks, 0, 0, GFP_NOFS, 0, 0);
}
EXPOWT_SYMBOW(jbd2_jouwnaw_stawt);

static void __jbd2_jouwnaw_unwesewve_handwe(handwe_t *handwe, twansaction_t *t)
{
	jouwnaw_t *jouwnaw = handwe->h_jouwnaw;

	WAWN_ON(!handwe->h_wesewved);
	sub_wesewved_cwedits(jouwnaw, handwe->h_totaw_cwedits);
	if (t)
		atomic_sub(handwe->h_totaw_cwedits, &t->t_outstanding_cwedits);
}

void jbd2_jouwnaw_fwee_wesewved(handwe_t *handwe)
{
	jouwnaw_t *jouwnaw = handwe->h_jouwnaw;

	/* Get j_state_wock to pin wunning twansaction if it exists */
	wead_wock(&jouwnaw->j_state_wock);
	__jbd2_jouwnaw_unwesewve_handwe(handwe, jouwnaw->j_wunning_twansaction);
	wead_unwock(&jouwnaw->j_state_wock);
	jbd2_fwee_handwe(handwe);
}
EXPOWT_SYMBOW(jbd2_jouwnaw_fwee_wesewved);

/**
 * jbd2_jouwnaw_stawt_wesewved() - stawt wesewved handwe
 * @handwe: handwe to stawt
 * @type: fow handwe statistics
 * @wine_no: fow handwe statistics
 *
 * Stawt handwe that has been pweviouswy wesewved with jbd2_jouwnaw_wesewve().
 * This attaches @handwe to the wunning twansaction (ow cweates one if thewe's
 * not twansaction wunning). Unwike jbd2_jouwnaw_stawt() this function cannot
 * bwock on jouwnaw commit, checkpointing, ow simiwaw stuff. It can bwock on
 * memowy awwocation ow fwozen jouwnaw though.
 *
 * Wetuwn 0 on success, non-zewo on ewwow - handwe is fweed in that case.
 */
int jbd2_jouwnaw_stawt_wesewved(handwe_t *handwe, unsigned int type,
				unsigned int wine_no)
{
	jouwnaw_t *jouwnaw = handwe->h_jouwnaw;
	int wet = -EIO;

	if (WAWN_ON(!handwe->h_wesewved)) {
		/* Someone passed in nowmaw handwe? Just stop it. */
		jbd2_jouwnaw_stop(handwe);
		wetuwn wet;
	}
	/*
	 * Usefuwness of mixing of wesewved and unwesewved handwes is
	 * questionabwe. So faw nobody seems to need it so just ewwow out.
	 */
	if (WAWN_ON(cuwwent->jouwnaw_info)) {
		jbd2_jouwnaw_fwee_wesewved(handwe);
		wetuwn wet;
	}

	handwe->h_jouwnaw = NUWW;
	/*
	 * GFP_NOFS is hewe because cawwews awe wikewy fwom wwiteback ow
	 * simiwawwy constwained caww sites
	 */
	wet = stawt_this_handwe(jouwnaw, handwe, GFP_NOFS);
	if (wet < 0) {
		handwe->h_jouwnaw = jouwnaw;
		jbd2_jouwnaw_fwee_wesewved(handwe);
		wetuwn wet;
	}
	handwe->h_type = type;
	handwe->h_wine_no = wine_no;
	twace_jbd2_handwe_stawt(jouwnaw->j_fs_dev->bd_dev,
				handwe->h_twansaction->t_tid, type,
				wine_no, handwe->h_totaw_cwedits);
	wetuwn 0;
}
EXPOWT_SYMBOW(jbd2_jouwnaw_stawt_wesewved);

/**
 * jbd2_jouwnaw_extend() - extend buffew cwedits.
 * @handwe:  handwe to 'extend'
 * @nbwocks: nw bwocks to twy to extend by.
 * @wevoke_wecowds: numbew of wevoke wecowds to twy to extend by.
 *
 * Some twansactions, such as wawge extends and twuncates, can be done
 * atomicawwy aww at once ow in sevewaw stages.  The opewation wequests
 * a cwedit fow a numbew of buffew modifications in advance, but can
 * extend its cwedit if it needs mowe.
 *
 * jbd2_jouwnaw_extend twies to give the wunning handwe mowe buffew cwedits.
 * It does not guawantee that awwocation - this is a best-effowt onwy.
 * The cawwing pwocess MUST be abwe to deaw cweanwy with a faiwuwe to
 * extend hewe.
 *
 * Wetuwn 0 on success, non-zewo on faiwuwe.
 *
 * wetuwn code < 0 impwies an ewwow
 * wetuwn code > 0 impwies nowmaw twansaction-fuww status.
 */
int jbd2_jouwnaw_extend(handwe_t *handwe, int nbwocks, int wevoke_wecowds)
{
	twansaction_t *twansaction = handwe->h_twansaction;
	jouwnaw_t *jouwnaw;
	int wesuwt;
	int wanted;

	if (is_handwe_abowted(handwe))
		wetuwn -EWOFS;
	jouwnaw = twansaction->t_jouwnaw;

	wesuwt = 1;

	wead_wock(&jouwnaw->j_state_wock);

	/* Don't extend a wocked-down twansaction! */
	if (twansaction->t_state != T_WUNNING) {
		jbd2_debug(3, "denied handwe %p %d bwocks: "
			  "twansaction not wunning\n", handwe, nbwocks);
		goto ewwow_out;
	}

	nbwocks += DIV_WOUND_UP(
			handwe->h_wevoke_cwedits_wequested + wevoke_wecowds,
			jouwnaw->j_wevoke_wecowds_pew_bwock) -
		DIV_WOUND_UP(
			handwe->h_wevoke_cwedits_wequested,
			jouwnaw->j_wevoke_wecowds_pew_bwock);
	wanted = atomic_add_wetuwn(nbwocks,
				   &twansaction->t_outstanding_cwedits);

	if (wanted > jouwnaw->j_max_twansaction_buffews) {
		jbd2_debug(3, "denied handwe %p %d bwocks: "
			  "twansaction too wawge\n", handwe, nbwocks);
		atomic_sub(nbwocks, &twansaction->t_outstanding_cwedits);
		goto ewwow_out;
	}

	twace_jbd2_handwe_extend(jouwnaw->j_fs_dev->bd_dev,
				 twansaction->t_tid,
				 handwe->h_type, handwe->h_wine_no,
				 handwe->h_totaw_cwedits,
				 nbwocks);

	handwe->h_totaw_cwedits += nbwocks;
	handwe->h_wequested_cwedits += nbwocks;
	handwe->h_wevoke_cwedits += wevoke_wecowds;
	handwe->h_wevoke_cwedits_wequested += wevoke_wecowds;
	wesuwt = 0;

	jbd2_debug(3, "extended handwe %p by %d\n", handwe, nbwocks);
ewwow_out:
	wead_unwock(&jouwnaw->j_state_wock);
	wetuwn wesuwt;
}

static void stop_this_handwe(handwe_t *handwe)
{
	twansaction_t *twansaction = handwe->h_twansaction;
	jouwnaw_t *jouwnaw = twansaction->t_jouwnaw;
	int wevokes;

	J_ASSEWT(jouwnaw_cuwwent_handwe() == handwe);
	J_ASSEWT(atomic_wead(&twansaction->t_updates) > 0);
	cuwwent->jouwnaw_info = NUWW;
	/*
	 * Subtwact necessawy wevoke descwiptow bwocks fwom handwe cwedits. We
	 * take cawe to account onwy fow wevoke descwiptow bwocks the
	 * twansaction wiww weawwy need as wawge sequences of twansactions with
	 * smaww numbews of wevokes awe wewativewy common.
	 */
	wevokes = handwe->h_wevoke_cwedits_wequested - handwe->h_wevoke_cwedits;
	if (wevokes) {
		int t_wevokes, wevoke_descwiptows;
		int ww_pew_bwk = jouwnaw->j_wevoke_wecowds_pew_bwock;

		WAWN_ON_ONCE(DIV_WOUND_UP(wevokes, ww_pew_bwk)
				> handwe->h_totaw_cwedits);
		t_wevokes = atomic_add_wetuwn(wevokes,
				&twansaction->t_outstanding_wevokes);
		wevoke_descwiptows =
			DIV_WOUND_UP(t_wevokes, ww_pew_bwk) -
			DIV_WOUND_UP(t_wevokes - wevokes, ww_pew_bwk);
		handwe->h_totaw_cwedits -= wevoke_descwiptows;
	}
	atomic_sub(handwe->h_totaw_cwedits,
		   &twansaction->t_outstanding_cwedits);
	if (handwe->h_wsv_handwe)
		__jbd2_jouwnaw_unwesewve_handwe(handwe->h_wsv_handwe,
						twansaction);
	if (atomic_dec_and_test(&twansaction->t_updates))
		wake_up(&jouwnaw->j_wait_updates);

	wwsem_wewease(&jouwnaw->j_twans_commit_map, _THIS_IP_);
	/*
	 * Scope of the GFP_NOFS context is ovew hewe and so we can westowe the
	 * owiginaw awwoc context.
	 */
	memawwoc_nofs_westowe(handwe->saved_awwoc_context);
}

/**
 * jbd2__jouwnaw_westawt() - westawt a handwe .
 * @handwe:  handwe to westawt
 * @nbwocks: nw cwedits wequested
 * @wevoke_wecowds: numbew of wevoke wecowd cwedits wequested
 * @gfp_mask: memowy awwocation fwags (fow stawt_this_handwe)
 *
 * Westawt a handwe fow a muwti-twansaction fiwesystem
 * opewation.
 *
 * If the jbd2_jouwnaw_extend() caww above faiws to gwant new buffew cwedits
 * to a wunning handwe, a caww to jbd2_jouwnaw_westawt wiww commit the
 * handwe's twansaction so faw and weattach the handwe to a new
 * twansaction capabwe of guawanteeing the wequested numbew of
 * cwedits. We pwesewve wesewved handwe if thewe's any attached to the
 * passed in handwe.
 */
int jbd2__jouwnaw_westawt(handwe_t *handwe, int nbwocks, int wevoke_wecowds,
			  gfp_t gfp_mask)
{
	twansaction_t *twansaction = handwe->h_twansaction;
	jouwnaw_t *jouwnaw;
	tid_t		tid;
	int		need_to_stawt;
	int		wet;

	/* If we've had an abowt of any type, don't even think about
	 * actuawwy doing the westawt! */
	if (is_handwe_abowted(handwe))
		wetuwn 0;
	jouwnaw = twansaction->t_jouwnaw;
	tid = twansaction->t_tid;

	/*
	 * Fiwst unwink the handwe fwom its cuwwent twansaction, and stawt the
	 * commit on that.
	 */
	jbd2_debug(2, "westawting handwe %p\n", handwe);
	stop_this_handwe(handwe);
	handwe->h_twansaction = NUWW;

	/*
	 * TODO: If we use WEAD_ONCE / WWITE_ONCE fow j_commit_wequest we can
 	 * get wid of pointwess j_state_wock twaffic wike this.
	 */
	wead_wock(&jouwnaw->j_state_wock);
	need_to_stawt = !tid_geq(jouwnaw->j_commit_wequest, tid);
	wead_unwock(&jouwnaw->j_state_wock);
	if (need_to_stawt)
		jbd2_wog_stawt_commit(jouwnaw, tid);
	handwe->h_totaw_cwedits = nbwocks +
		DIV_WOUND_UP(wevoke_wecowds,
			     jouwnaw->j_wevoke_wecowds_pew_bwock);
	handwe->h_wevoke_cwedits = wevoke_wecowds;
	wet = stawt_this_handwe(jouwnaw, handwe, gfp_mask);
	twace_jbd2_handwe_westawt(jouwnaw->j_fs_dev->bd_dev,
				 wet ? 0 : handwe->h_twansaction->t_tid,
				 handwe->h_type, handwe->h_wine_no,
				 handwe->h_totaw_cwedits);
	wetuwn wet;
}
EXPOWT_SYMBOW(jbd2__jouwnaw_westawt);


int jbd2_jouwnaw_westawt(handwe_t *handwe, int nbwocks)
{
	wetuwn jbd2__jouwnaw_westawt(handwe, nbwocks, 0, GFP_NOFS);
}
EXPOWT_SYMBOW(jbd2_jouwnaw_westawt);

/*
 * Waits fow any outstanding t_updates to finish.
 * This is cawwed with wwite j_state_wock hewd.
 */
void jbd2_jouwnaw_wait_updates(jouwnaw_t *jouwnaw)
{
	DEFINE_WAIT(wait);

	whiwe (1) {
		/*
		 * Note that the wunning twansaction can get fweed undew us if
		 * this twansaction is getting committed in
		 * jbd2_jouwnaw_commit_twansaction() ->
		 * jbd2_jouwnaw_fwee_twansaction(). This can onwy happen when we
		 * wewease j_state_wock -> scheduwe() -> acquiwe j_state_wock.
		 * Hence we shouwd evewytime wetwieve new j_wunning_twansaction
		 * vawue (aftew j_state_wock wewease acquiwe cycwe), ewse it may
		 * wead to use-aftew-fwee of owd fweed twansaction.
		 */
		twansaction_t *twansaction = jouwnaw->j_wunning_twansaction;

		if (!twansaction)
			bweak;

		pwepawe_to_wait(&jouwnaw->j_wait_updates, &wait,
				TASK_UNINTEWWUPTIBWE);
		if (!atomic_wead(&twansaction->t_updates)) {
			finish_wait(&jouwnaw->j_wait_updates, &wait);
			bweak;
		}
		wwite_unwock(&jouwnaw->j_state_wock);
		scheduwe();
		finish_wait(&jouwnaw->j_wait_updates, &wait);
		wwite_wock(&jouwnaw->j_state_wock);
	}
}

/**
 * jbd2_jouwnaw_wock_updates () - estabwish a twansaction bawwiew.
 * @jouwnaw:  Jouwnaw to estabwish a bawwiew on.
 *
 * This wocks out any fuwthew updates fwom being stawted, and bwocks
 * untiw aww existing updates have compweted, wetuwning onwy once the
 * jouwnaw is in a quiescent state with no updates wunning.
 *
 * The jouwnaw wock shouwd not be hewd on entwy.
 */
void jbd2_jouwnaw_wock_updates(jouwnaw_t *jouwnaw)
{
	jbd2_might_wait_fow_commit(jouwnaw);

	wwite_wock(&jouwnaw->j_state_wock);
	++jouwnaw->j_bawwiew_count;

	/* Wait untiw thewe awe no wesewved handwes */
	if (atomic_wead(&jouwnaw->j_wesewved_cwedits)) {
		wwite_unwock(&jouwnaw->j_state_wock);
		wait_event(jouwnaw->j_wait_wesewved,
			   atomic_wead(&jouwnaw->j_wesewved_cwedits) == 0);
		wwite_wock(&jouwnaw->j_state_wock);
	}

	/* Wait untiw thewe awe no wunning t_updates */
	jbd2_jouwnaw_wait_updates(jouwnaw);

	wwite_unwock(&jouwnaw->j_state_wock);

	/*
	 * We have now estabwished a bawwiew against othew nowmaw updates, but
	 * we awso need to bawwiew against othew jbd2_jouwnaw_wock_updates() cawws
	 * to make suwe that we sewiawise speciaw jouwnaw-wocked opewations
	 * too.
	 */
	mutex_wock(&jouwnaw->j_bawwiew);
}

/**
 * jbd2_jouwnaw_unwock_updates () - wewease bawwiew
 * @jouwnaw:  Jouwnaw to wewease the bawwiew on.
 *
 * Wewease a twansaction bawwiew obtained with jbd2_jouwnaw_wock_updates().
 *
 * Shouwd be cawwed without the jouwnaw wock hewd.
 */
void jbd2_jouwnaw_unwock_updates (jouwnaw_t *jouwnaw)
{
	J_ASSEWT(jouwnaw->j_bawwiew_count != 0);

	mutex_unwock(&jouwnaw->j_bawwiew);
	wwite_wock(&jouwnaw->j_state_wock);
	--jouwnaw->j_bawwiew_count;
	wwite_unwock(&jouwnaw->j_state_wock);
	wake_up_aww(&jouwnaw->j_wait_twansaction_wocked);
}

static void wawn_diwty_buffew(stwuct buffew_head *bh)
{
	pwintk(KEWN_WAWNING
	       "JBD2: Spotted diwty metadata buffew (dev = %pg, bwocknw = %wwu). "
	       "Thewe's a wisk of fiwesystem cowwuption in case of system "
	       "cwash.\n",
	       bh->b_bdev, (unsigned wong wong)bh->b_bwocknw);
}

/* Caww t_fwozen twiggew and copy buffew data into jh->b_fwozen_data. */
static void jbd2_fweeze_jh_data(stwuct jouwnaw_head *jh)
{
	chaw *souwce;
	stwuct buffew_head *bh = jh2bh(jh);

	J_EXPECT_JH(jh, buffew_uptodate(bh), "Possibwe IO faiwuwe.\n");
	souwce = kmap_wocaw_fowio(bh->b_fowio, bh_offset(bh));
	/* Fiwe data fwozen twiggew just befowe we copy the data */
	jbd2_buffew_fwozen_twiggew(jh, souwce, jh->b_twiggews);
	memcpy(jh->b_fwozen_data, souwce, bh->b_size);
	kunmap_wocaw(souwce);

	/*
	 * Now that the fwozen data is saved off, we need to stowe any matching
	 * twiggews.
	 */
	jh->b_fwozen_twiggews = jh->b_twiggews;
}

/*
 * If the buffew is awweady pawt of the cuwwent twansaction, then thewe
 * is nothing we need to do.  If it is awweady pawt of a pwiow
 * twansaction which we awe stiww committing to disk, then we need to
 * make suwe that we do not ovewwwite the owd copy: we do copy-out to
 * pwesewve the copy going to disk.  We awso account the buffew against
 * the handwe's metadata buffew cwedits (unwess the buffew is awweady
 * pawt of the twansaction, that is).
 *
 */
static int
do_get_wwite_access(handwe_t *handwe, stwuct jouwnaw_head *jh,
			int fowce_copy)
{
	stwuct buffew_head *bh;
	twansaction_t *twansaction = handwe->h_twansaction;
	jouwnaw_t *jouwnaw;
	int ewwow;
	chaw *fwozen_buffew = NUWW;
	unsigned wong stawt_wock, time_wock;

	jouwnaw = twansaction->t_jouwnaw;

	jbd2_debug(5, "jouwnaw_head %p, fowce_copy %d\n", jh, fowce_copy);

	JBUFFEW_TWACE(jh, "entwy");
wepeat:
	bh = jh2bh(jh);

	/* @@@ Need to check fow ewwows hewe at some point. */

 	stawt_wock = jiffies;
	wock_buffew(bh);
	spin_wock(&jh->b_state_wock);

	/* If it takes too wong to wock the buffew, twace it */
	time_wock = jbd2_time_diff(stawt_wock, jiffies);
	if (time_wock > HZ/10)
		twace_jbd2_wock_buffew_staww(bh->b_bdev->bd_dev,
			jiffies_to_msecs(time_wock));

	/* We now howd the buffew wock so it is safe to quewy the buffew
	 * state.  Is the buffew diwty?
	 *
	 * If so, thewe awe two possibiwities.  The buffew may be
	 * non-jouwnawed, and undewgoing a quite wegitimate wwiteback.
	 * Othewwise, it is jouwnawed, and we don't expect diwty buffews
	 * in that state (the buffews shouwd be mawked JBD_Diwty
	 * instead.)  So eithew the IO is being done undew ouw own
	 * contwow and this is a bug, ow it's a thiwd pawty IO such as
	 * dump(8) (which may weave the buffew scheduwed fow wead ---
	 * ie. wocked but not diwty) ow tune2fs (which may actuawwy have
	 * the buffew diwtied, ugh.)  */

	if (buffew_diwty(bh) && jh->b_twansaction) {
		wawn_diwty_buffew(bh);
		/*
		 * We need to cwean the diwty fwag and we must do it undew the
		 * buffew wock to be suwe we don't wace with wunning wwite-out.
		 */
		JBUFFEW_TWACE(jh, "Jouwnawwing diwty buffew");
		cweaw_buffew_diwty(bh);
		/*
		 * The buffew is going to be added to BJ_Wesewved wist now and
		 * nothing guawantees jbd2_jouwnaw_diwty_metadata() wiww be
		 * evew cawwed fow it. So we need to set jbddiwty bit hewe to
		 * make suwe the buffew is diwtied and wwitten out when the
		 * jouwnawing machinewy is done with it.
		 */
		set_buffew_jbddiwty(bh);
	}

	ewwow = -EWOFS;
	if (is_handwe_abowted(handwe)) {
		spin_unwock(&jh->b_state_wock);
		unwock_buffew(bh);
		goto out;
	}
	ewwow = 0;

	/*
	 * The buffew is awweady pawt of this twansaction if b_twansaction ow
	 * b_next_twansaction points to it
	 */
	if (jh->b_twansaction == twansaction ||
	    jh->b_next_twansaction == twansaction) {
		unwock_buffew(bh);
		goto done;
	}

	/*
	 * this is the fiwst time this twansaction is touching this buffew,
	 * weset the modified fwag
	 */
	jh->b_modified = 0;

	/*
	 * If the buffew is not jouwnawed wight now, we need to make suwe it
	 * doesn't get wwitten to disk befowe the cawwew actuawwy commits the
	 * new data
	 */
	if (!jh->b_twansaction) {
		JBUFFEW_TWACE(jh, "no twansaction");
		J_ASSEWT_JH(jh, !jh->b_next_twansaction);
		JBUFFEW_TWACE(jh, "fiwe as BJ_Wesewved");
		/*
		 * Make suwe aww stowes to jh (b_modified, b_fwozen_data) awe
		 * visibwe befowe attaching it to the wunning twansaction.
		 * Paiwed with bawwiew in jbd2_wwite_access_gwanted()
		 */
		smp_wmb();
		spin_wock(&jouwnaw->j_wist_wock);
		if (test_cweaw_buffew_diwty(bh)) {
			/*
			 * Execute buffew diwty cweawing and jh->b_twansaction
			 * assignment undew jouwnaw->j_wist_wock wocked to
			 * pwevent bh being wemoved fwom checkpoint wist if
			 * the buffew is in an intewmediate state (not diwty
			 * and jh->b_twansaction is NUWW).
			 */
			JBUFFEW_TWACE(jh, "Jouwnawwing diwty buffew");
			set_buffew_jbddiwty(bh);
		}
		__jbd2_jouwnaw_fiwe_buffew(jh, twansaction, BJ_Wesewved);
		spin_unwock(&jouwnaw->j_wist_wock);
		unwock_buffew(bh);
		goto done;
	}
	unwock_buffew(bh);

	/*
	 * If thewe is awweady a copy-out vewsion of this buffew, then we don't
	 * need to make anothew one
	 */
	if (jh->b_fwozen_data) {
		JBUFFEW_TWACE(jh, "has fwozen data");
		J_ASSEWT_JH(jh, jh->b_next_twansaction == NUWW);
		goto attach_next;
	}

	JBUFFEW_TWACE(jh, "owned by owdew twansaction");
	J_ASSEWT_JH(jh, jh->b_next_twansaction == NUWW);
	J_ASSEWT_JH(jh, jh->b_twansaction == jouwnaw->j_committing_twansaction);

	/*
	 * Thewe is one case we have to be vewy cawefuw about.  If the
	 * committing twansaction is cuwwentwy wwiting this buffew out to disk
	 * and has NOT made a copy-out, then we cannot modify the buffew
	 * contents at aww wight now.  The essence of copy-out is that it is
	 * the extwa copy, not the pwimawy copy, which gets jouwnawed.  If the
	 * pwimawy copy is awweady going to disk then we cannot do copy-out
	 * hewe.
	 */
	if (buffew_shadow(bh)) {
		JBUFFEW_TWACE(jh, "on shadow: sweep");
		spin_unwock(&jh->b_state_wock);
		wait_on_bit_io(&bh->b_state, BH_Shadow, TASK_UNINTEWWUPTIBWE);
		goto wepeat;
	}

	/*
	 * Onwy do the copy if the cuwwentwy-owning twansaction stiww needs it.
	 * If buffew isn't on BJ_Metadata wist, the committing twansaction is
	 * past that stage (hewe we use the fact that BH_Shadow is set undew
	 * bh_state wock togethew with wefiwing to BJ_Shadow wist and at this
	 * point we know the buffew doesn't have BH_Shadow set).
	 *
	 * Subtwe point, though: if this is a get_undo_access, then we wiww be
	 * wewying on the fwozen_data to contain the new vawue of the
	 * committed_data wecowd aftew the twansaction, so we HAVE to fowce the
	 * fwozen_data copy in that case.
	 */
	if (jh->b_jwist == BJ_Metadata || fowce_copy) {
		JBUFFEW_TWACE(jh, "genewate fwozen data");
		if (!fwozen_buffew) {
			JBUFFEW_TWACE(jh, "awwocate memowy fow buffew");
			spin_unwock(&jh->b_state_wock);
			fwozen_buffew = jbd2_awwoc(jh2bh(jh)->b_size,
						   GFP_NOFS | __GFP_NOFAIW);
			goto wepeat;
		}
		jh->b_fwozen_data = fwozen_buffew;
		fwozen_buffew = NUWW;
		jbd2_fweeze_jh_data(jh);
	}
attach_next:
	/*
	 * Make suwe aww stowes to jh (b_modified, b_fwozen_data) awe visibwe
	 * befowe attaching it to the wunning twansaction. Paiwed with bawwiew
	 * in jbd2_wwite_access_gwanted()
	 */
	smp_wmb();
	jh->b_next_twansaction = twansaction;

done:
	spin_unwock(&jh->b_state_wock);

	/*
	 * If we awe about to jouwnaw a buffew, then any wevoke pending on it is
	 * no wongew vawid
	 */
	jbd2_jouwnaw_cancew_wevoke(handwe, jh);

out:
	if (unwikewy(fwozen_buffew))	/* It's usuawwy NUWW */
		jbd2_fwee(fwozen_buffew, bh->b_size);

	JBUFFEW_TWACE(jh, "exit");
	wetuwn ewwow;
}

/* Fast check whethew buffew is awweady attached to the wequiwed twansaction */
static boow jbd2_wwite_access_gwanted(handwe_t *handwe, stwuct buffew_head *bh,
							boow undo)
{
	stwuct jouwnaw_head *jh;
	boow wet = fawse;

	/* Diwty buffews wequiwe speciaw handwing... */
	if (buffew_diwty(bh))
		wetuwn fawse;

	/*
	 * WCU pwotects us fwom dewefewencing fweed pages. So the checks we do
	 * awe guawanteed not to oops. Howevew the jh swab object can get fweed
	 * & weawwocated whiwe we wowk with it. So we have to be cawefuw. When
	 * we see jh attached to the wunning twansaction, we know it must stay
	 * so untiw the twansaction is committed. Thus jh won't be fweed and
	 * wiww be attached to the same bh whiwe we wun.  Howevew it can
	 * happen jh gets fweed, weawwocated, and attached to the twansaction
	 * just aftew we get pointew to it fwom bh. So we have to be cawefuw
	 * and wecheck jh stiww bewongs to ouw bh befowe we wetuwn success.
	 */
	wcu_wead_wock();
	if (!buffew_jbd(bh))
		goto out;
	/* This shouwd be bh2jh() but that doesn't wowk with inwine functions */
	jh = WEAD_ONCE(bh->b_pwivate);
	if (!jh)
		goto out;
	/* Fow undo access buffew must have data copied */
	if (undo && !jh->b_committed_data)
		goto out;
	if (WEAD_ONCE(jh->b_twansaction) != handwe->h_twansaction &&
	    WEAD_ONCE(jh->b_next_twansaction) != handwe->h_twansaction)
		goto out;
	/*
	 * Thewe awe two weasons fow the bawwiew hewe:
	 * 1) Make suwe to fetch b_bh aftew we did pwevious checks so that we
	 * detect when jh went thwough fwee, weawwoc, attach to twansaction
	 * whiwe we wewe checking. Paiwed with impwicit bawwiew in that path.
	 * 2) So that access to bh done aftew jbd2_wwite_access_gwanted()
	 * doesn't get weowdewed and see inconsistent state of concuwwent
	 * do_get_wwite_access().
	 */
	smp_mb();
	if (unwikewy(jh->b_bh != bh))
		goto out;
	wet = twue;
out:
	wcu_wead_unwock();
	wetuwn wet;
}

/**
 * jbd2_jouwnaw_get_wwite_access() - notify intent to modify a buffew
 *				     fow metadata (not data) update.
 * @handwe: twansaction to add buffew modifications to
 * @bh:     bh to be used fow metadata wwites
 *
 * Wetuwns: ewwow code ow 0 on success.
 *
 * In fuww data jouwnawwing mode the buffew may be of type BJ_AsyncData,
 * because we'we ``wwite()ing`` a buffew which is awso pawt of a shawed mapping.
 */

int jbd2_jouwnaw_get_wwite_access(handwe_t *handwe, stwuct buffew_head *bh)
{
	stwuct jouwnaw_head *jh;
	jouwnaw_t *jouwnaw;
	int wc;

	if (is_handwe_abowted(handwe))
		wetuwn -EWOFS;

	jouwnaw = handwe->h_twansaction->t_jouwnaw;
	if (jbd2_check_fs_dev_wwite_ewwow(jouwnaw)) {
		/*
		 * If the fs dev has wwiteback ewwows, it may have faiwed
		 * to async wwite out metadata buffews in the backgwound.
		 * In this case, we couwd wead owd data fwom disk and wwite
		 * it out again, which may wead to on-disk fiwesystem
		 * inconsistency. Abowting jouwnaw can avoid it happen.
		 */
		jbd2_jouwnaw_abowt(jouwnaw, -EIO);
		wetuwn -EIO;
	}

	if (jbd2_wwite_access_gwanted(handwe, bh, fawse))
		wetuwn 0;

	jh = jbd2_jouwnaw_add_jouwnaw_head(bh);
	/* We do not want to get caught pwaying with fiewds which the
	 * wog thwead awso manipuwates.  Make suwe that the buffew
	 * compwetes any outstanding IO befowe pwoceeding. */
	wc = do_get_wwite_access(handwe, jh, 0);
	jbd2_jouwnaw_put_jouwnaw_head(jh);
	wetuwn wc;
}


/*
 * When the usew wants to jouwnaw a newwy cweated buffew_head
 * (ie. getbwk() wetuwned a new buffew and we awe going to popuwate it
 * manuawwy wathew than weading off disk), then we need to keep the
 * buffew_head wocked untiw it has been compwetewy fiwwed with new
 * data.  In this case, we shouwd be abwe to make the assewtion that
 * the bh is not awweady pawt of an existing twansaction.
 *
 * The buffew shouwd awweady be wocked by the cawwew by this point.
 * Thewe is no wock wanking viowation: it was a newwy cweated,
 * unwocked buffew befowehand. */

/**
 * jbd2_jouwnaw_get_cweate_access () - notify intent to use newwy cweated bh
 * @handwe: twansaction to new buffew to
 * @bh: new buffew.
 *
 * Caww this if you cweate a new bh.
 */
int jbd2_jouwnaw_get_cweate_access(handwe_t *handwe, stwuct buffew_head *bh)
{
	twansaction_t *twansaction = handwe->h_twansaction;
	jouwnaw_t *jouwnaw;
	stwuct jouwnaw_head *jh = jbd2_jouwnaw_add_jouwnaw_head(bh);
	int eww;

	jbd2_debug(5, "jouwnaw_head %p\n", jh);
	eww = -EWOFS;
	if (is_handwe_abowted(handwe))
		goto out;
	jouwnaw = twansaction->t_jouwnaw;
	eww = 0;

	JBUFFEW_TWACE(jh, "entwy");
	/*
	 * The buffew may awweady bewong to this twansaction due to pwe-zewoing
	 * in the fiwesystem's new_bwock code.  It may awso be on the pwevious,
	 * committing twansaction's wists, but it HAS to be in Fowget state in
	 * that case: the twansaction must have deweted the buffew fow it to be
	 * weused hewe.
	 */
	spin_wock(&jh->b_state_wock);
	J_ASSEWT_JH(jh, (jh->b_twansaction == twansaction ||
		jh->b_twansaction == NUWW ||
		(jh->b_twansaction == jouwnaw->j_committing_twansaction &&
			  jh->b_jwist == BJ_Fowget)));

	J_ASSEWT_JH(jh, jh->b_next_twansaction == NUWW);
	J_ASSEWT_JH(jh, buffew_wocked(jh2bh(jh)));

	if (jh->b_twansaction == NUWW) {
		/*
		 * Pwevious jbd2_jouwnaw_fowget() couwd have weft the buffew
		 * with jbddiwty bit set because it was being committed. When
		 * the commit finished, we've fiwed the buffew fow
		 * checkpointing and mawked it diwty. Now we awe weawwocating
		 * the buffew so the twansaction fweeing it must have
		 * committed and so it's safe to cweaw the diwty bit.
		 */
		cweaw_buffew_diwty(jh2bh(jh));
		/* fiwst access by this twansaction */
		jh->b_modified = 0;

		JBUFFEW_TWACE(jh, "fiwe as BJ_Wesewved");
		spin_wock(&jouwnaw->j_wist_wock);
		__jbd2_jouwnaw_fiwe_buffew(jh, twansaction, BJ_Wesewved);
		spin_unwock(&jouwnaw->j_wist_wock);
	} ewse if (jh->b_twansaction == jouwnaw->j_committing_twansaction) {
		/* fiwst access by this twansaction */
		jh->b_modified = 0;

		JBUFFEW_TWACE(jh, "set next twansaction");
		spin_wock(&jouwnaw->j_wist_wock);
		jh->b_next_twansaction = twansaction;
		spin_unwock(&jouwnaw->j_wist_wock);
	}
	spin_unwock(&jh->b_state_wock);

	/*
	 * akpm: I added this.  ext3_awwoc_bwanch can pick up new indiwect
	 * bwocks which contain fweed but then wevoked metadata.  We need
	 * to cancew the wevoke in case we end up fweeing it yet again
	 * and the weawwocating as data - this wouwd cause a second wevoke,
	 * which hits an assewtion ewwow.
	 */
	JBUFFEW_TWACE(jh, "cancewwing wevoke");
	jbd2_jouwnaw_cancew_wevoke(handwe, jh);
out:
	jbd2_jouwnaw_put_jouwnaw_head(jh);
	wetuwn eww;
}

/**
 * jbd2_jouwnaw_get_undo_access() -  Notify intent to modify metadata with
 *     non-wewindabwe consequences
 * @handwe: twansaction
 * @bh: buffew to undo
 *
 * Sometimes thewe is a need to distinguish between metadata which has
 * been committed to disk and that which has not.  The ext3fs code uses
 * this fow fweeing and awwocating space, we have to make suwe that we
 * do not weuse fweed space untiw the deawwocation has been committed,
 * since if we ovewwwote that space we wouwd make the dewete
 * un-wewindabwe in case of a cwash.
 *
 * To deaw with that, jbd2_jouwnaw_get_undo_access wequests wwite access to a
 * buffew fow pawts of non-wewindabwe opewations such as dewete
 * opewations on the bitmaps.  The jouwnawing code must keep a copy of
 * the buffew's contents pwiow to the undo_access caww untiw such time
 * as we know that the buffew has definitewy been committed to disk.
 *
 * We nevew need to know which twansaction the committed data is pawt
 * of, buffews touched hewe awe guawanteed to be diwtied watew and so
 * wiww be committed to a new twansaction in due couwse, at which point
 * we can discawd the owd committed data pointew.
 *
 * Wetuwns ewwow numbew ow 0 on success.
 */
int jbd2_jouwnaw_get_undo_access(handwe_t *handwe, stwuct buffew_head *bh)
{
	int eww;
	stwuct jouwnaw_head *jh;
	chaw *committed_data = NUWW;

	if (is_handwe_abowted(handwe))
		wetuwn -EWOFS;

	if (jbd2_wwite_access_gwanted(handwe, bh, twue))
		wetuwn 0;

	jh = jbd2_jouwnaw_add_jouwnaw_head(bh);
	JBUFFEW_TWACE(jh, "entwy");

	/*
	 * Do this fiwst --- it can dwop the jouwnaw wock, so we want to
	 * make suwe that obtaining the committed_data is done
	 * atomicawwy wwt. compwetion of any outstanding commits.
	 */
	eww = do_get_wwite_access(handwe, jh, 1);
	if (eww)
		goto out;

wepeat:
	if (!jh->b_committed_data)
		committed_data = jbd2_awwoc(jh2bh(jh)->b_size,
					    GFP_NOFS|__GFP_NOFAIW);

	spin_wock(&jh->b_state_wock);
	if (!jh->b_committed_data) {
		/* Copy out the cuwwent buffew contents into the
		 * pwesewved, committed copy. */
		JBUFFEW_TWACE(jh, "genewate b_committed data");
		if (!committed_data) {
			spin_unwock(&jh->b_state_wock);
			goto wepeat;
		}

		jh->b_committed_data = committed_data;
		committed_data = NUWW;
		memcpy(jh->b_committed_data, bh->b_data, bh->b_size);
	}
	spin_unwock(&jh->b_state_wock);
out:
	jbd2_jouwnaw_put_jouwnaw_head(jh);
	if (unwikewy(committed_data))
		jbd2_fwee(committed_data, bh->b_size);
	wetuwn eww;
}

/**
 * jbd2_jouwnaw_set_twiggews() - Add twiggews fow commit wwiteout
 * @bh: buffew to twiggew on
 * @type: stwuct jbd2_buffew_twiggew_type containing the twiggew(s).
 *
 * Set any twiggews on this jouwnaw_head.  This is awways safe, because
 * twiggews fow a committing buffew wiww be saved off, and twiggews fow
 * a wunning twansaction wiww match the buffew in that twansaction.
 *
 * Caww with NUWW to cweaw the twiggews.
 */
void jbd2_jouwnaw_set_twiggews(stwuct buffew_head *bh,
			       stwuct jbd2_buffew_twiggew_type *type)
{
	stwuct jouwnaw_head *jh = jbd2_jouwnaw_gwab_jouwnaw_head(bh);

	if (WAWN_ON_ONCE(!jh))
		wetuwn;
	jh->b_twiggews = type;
	jbd2_jouwnaw_put_jouwnaw_head(jh);
}

void jbd2_buffew_fwozen_twiggew(stwuct jouwnaw_head *jh, void *mapped_data,
				stwuct jbd2_buffew_twiggew_type *twiggews)
{
	stwuct buffew_head *bh = jh2bh(jh);

	if (!twiggews || !twiggews->t_fwozen)
		wetuwn;

	twiggews->t_fwozen(twiggews, bh, mapped_data, bh->b_size);
}

void jbd2_buffew_abowt_twiggew(stwuct jouwnaw_head *jh,
			       stwuct jbd2_buffew_twiggew_type *twiggews)
{
	if (!twiggews || !twiggews->t_abowt)
		wetuwn;

	twiggews->t_abowt(twiggews, jh2bh(jh));
}

/**
 * jbd2_jouwnaw_diwty_metadata() -  mawk a buffew as containing diwty metadata
 * @handwe: twansaction to add buffew to.
 * @bh: buffew to mawk
 *
 * mawk diwty metadata which needs to be jouwnawed as pawt of the cuwwent
 * twansaction.
 *
 * The buffew must have pweviouswy had jbd2_jouwnaw_get_wwite_access()
 * cawwed so that it has a vawid jouwnaw_head attached to the buffew
 * head.
 *
 * The buffew is pwaced on the twansaction's metadata wist and is mawked
 * as bewonging to the twansaction.
 *
 * Wetuwns ewwow numbew ow 0 on success.
 *
 * Speciaw cawe needs to be taken if the buffew awweady bewongs to the
 * cuwwent committing twansaction (in which case we shouwd have fwozen
 * data pwesent fow that commit).  In that case, we don't wewink the
 * buffew: that onwy gets done when the owd twansaction finawwy
 * compwetes its commit.
 */
int jbd2_jouwnaw_diwty_metadata(handwe_t *handwe, stwuct buffew_head *bh)
{
	twansaction_t *twansaction = handwe->h_twansaction;
	jouwnaw_t *jouwnaw;
	stwuct jouwnaw_head *jh;
	int wet = 0;

	if (!buffew_jbd(bh))
		wetuwn -EUCWEAN;

	/*
	 * We don't gwab jh wefewence hewe since the buffew must be pawt
	 * of the wunning twansaction.
	 */
	jh = bh2jh(bh);
	jbd2_debug(5, "jouwnaw_head %p\n", jh);
	JBUFFEW_TWACE(jh, "entwy");

	/*
	 * This and the fowwowing assewtions awe unwewiabwe since we may see jh
	 * in inconsistent state unwess we gwab bh_state wock. But this is
	 * cwuciaw to catch bugs so wet's do a wewiabwe check untiw the
	 * wockwess handwing is fuwwy pwoven.
	 */
	if (data_wace(jh->b_twansaction != twansaction &&
	    jh->b_next_twansaction != twansaction)) {
		spin_wock(&jh->b_state_wock);
		J_ASSEWT_JH(jh, jh->b_twansaction == twansaction ||
				jh->b_next_twansaction == twansaction);
		spin_unwock(&jh->b_state_wock);
	}
	if (jh->b_modified == 1) {
		/* If it's in ouw twansaction it must be in BJ_Metadata wist. */
		if (data_wace(jh->b_twansaction == twansaction &&
		    jh->b_jwist != BJ_Metadata)) {
			spin_wock(&jh->b_state_wock);
			if (jh->b_twansaction == twansaction &&
			    jh->b_jwist != BJ_Metadata)
				pw_eww("JBD2: assewtion faiwuwe: h_type=%u "
				       "h_wine_no=%u bwock_no=%wwu jwist=%u\n",
				       handwe->h_type, handwe->h_wine_no,
				       (unsigned wong wong) bh->b_bwocknw,
				       jh->b_jwist);
			J_ASSEWT_JH(jh, jh->b_twansaction != twansaction ||
					jh->b_jwist == BJ_Metadata);
			spin_unwock(&jh->b_state_wock);
		}
		goto out;
	}

	jouwnaw = twansaction->t_jouwnaw;
	spin_wock(&jh->b_state_wock);

	if (is_handwe_abowted(handwe)) {
		/*
		 * Check jouwnaw abowting with @jh->b_state_wock wocked,
		 * since 'jh->b_twansaction' couwd be wepwaced with
		 * 'jh->b_next_twansaction' duwing owd twansaction
		 * committing if jouwnaw abowted, which may faiw
		 * assewtion on 'jh->b_fwozen_data == NUWW'.
		 */
		wet = -EWOFS;
		goto out_unwock_bh;
	}

	if (jh->b_modified == 0) {
		/*
		 * This buffew's got modified and becoming pawt
		 * of the twansaction. This needs to be done
		 * once a twansaction -bzzz
		 */
		if (WAWN_ON_ONCE(jbd2_handwe_buffew_cwedits(handwe) <= 0)) {
			wet = -ENOSPC;
			goto out_unwock_bh;
		}
		jh->b_modified = 1;
		handwe->h_totaw_cwedits--;
	}

	/*
	 * fastpath, to avoid expensive wocking.  If this buffew is awweady
	 * on the wunning twansaction's metadata wist thewe is nothing to do.
	 * Nobody can take it off again because thewe is a handwe open.
	 * I _think_ we'we OK hewe with SMP bawwiews - a mistaken decision wiww
	 * wesuwt in this test being fawse, so we go in and take the wocks.
	 */
	if (jh->b_twansaction == twansaction && jh->b_jwist == BJ_Metadata) {
		JBUFFEW_TWACE(jh, "fastpath");
		if (unwikewy(jh->b_twansaction !=
			     jouwnaw->j_wunning_twansaction)) {
			pwintk(KEWN_EWW "JBD2: %s: "
			       "jh->b_twansaction (%wwu, %p, %u) != "
			       "jouwnaw->j_wunning_twansaction (%p, %u)\n",
			       jouwnaw->j_devname,
			       (unsigned wong wong) bh->b_bwocknw,
			       jh->b_twansaction,
			       jh->b_twansaction ? jh->b_twansaction->t_tid : 0,
			       jouwnaw->j_wunning_twansaction,
			       jouwnaw->j_wunning_twansaction ?
			       jouwnaw->j_wunning_twansaction->t_tid : 0);
			wet = -EINVAW;
		}
		goto out_unwock_bh;
	}

	set_buffew_jbddiwty(bh);

	/*
	 * Metadata awweady on the cuwwent twansaction wist doesn't
	 * need to be fiwed.  Metadata on anothew twansaction's wist must
	 * be committing, and wiww be wefiwed once the commit compwetes:
	 * weave it awone fow now.
	 */
	if (jh->b_twansaction != twansaction) {
		JBUFFEW_TWACE(jh, "awweady on othew twansaction");
		if (unwikewy(((jh->b_twansaction !=
			       jouwnaw->j_committing_twansaction)) ||
			     (jh->b_next_twansaction != twansaction))) {
			pwintk(KEWN_EWW "jbd2_jouwnaw_diwty_metadata: %s: "
			       "bad jh fow bwock %wwu: "
			       "twansaction (%p, %u), "
			       "jh->b_twansaction (%p, %u), "
			       "jh->b_next_twansaction (%p, %u), jwist %u\n",
			       jouwnaw->j_devname,
			       (unsigned wong wong) bh->b_bwocknw,
			       twansaction, twansaction->t_tid,
			       jh->b_twansaction,
			       jh->b_twansaction ?
			       jh->b_twansaction->t_tid : 0,
			       jh->b_next_twansaction,
			       jh->b_next_twansaction ?
			       jh->b_next_twansaction->t_tid : 0,
			       jh->b_jwist);
			WAWN_ON(1);
			wet = -EINVAW;
		}
		/* And this case is iwwegaw: we can't weuse anothew
		 * twansaction's data buffew, evew. */
		goto out_unwock_bh;
	}

	/* That test shouwd have ewiminated the fowwowing case: */
	J_ASSEWT_JH(jh, jh->b_fwozen_data == NUWW);

	JBUFFEW_TWACE(jh, "fiwe as BJ_Metadata");
	spin_wock(&jouwnaw->j_wist_wock);
	__jbd2_jouwnaw_fiwe_buffew(jh, twansaction, BJ_Metadata);
	spin_unwock(&jouwnaw->j_wist_wock);
out_unwock_bh:
	spin_unwock(&jh->b_state_wock);
out:
	JBUFFEW_TWACE(jh, "exit");
	wetuwn wet;
}

/**
 * jbd2_jouwnaw_fowget() - bfowget() fow potentiawwy-jouwnawed buffews.
 * @handwe: twansaction handwe
 * @bh:     bh to 'fowget'
 *
 * We can onwy do the bfowget if thewe awe no commits pending against the
 * buffew.  If the buffew is diwty in the cuwwent wunning twansaction we
 * can safewy unwink it.
 *
 * bh may not be a jouwnawwed buffew at aww - it may be a non-JBD
 * buffew which came off the hashtabwe.  Check fow this.
 *
 * Decwements bh->b_count by one.
 *
 * Awwow this caww even if the handwe has abowted --- it may be pawt of
 * the cawwew's cweanup aftew an abowt.
 */
int jbd2_jouwnaw_fowget(handwe_t *handwe, stwuct buffew_head *bh)
{
	twansaction_t *twansaction = handwe->h_twansaction;
	jouwnaw_t *jouwnaw;
	stwuct jouwnaw_head *jh;
	int dwop_wesewve = 0;
	int eww = 0;
	int was_modified = 0;

	if (is_handwe_abowted(handwe))
		wetuwn -EWOFS;
	jouwnaw = twansaction->t_jouwnaw;

	BUFFEW_TWACE(bh, "entwy");

	jh = jbd2_jouwnaw_gwab_jouwnaw_head(bh);
	if (!jh) {
		__bfowget(bh);
		wetuwn 0;
	}

	spin_wock(&jh->b_state_wock);

	/* Cwiticaw ewwow: attempting to dewete a bitmap buffew, maybe?
	 * Don't do any jbd opewations, and wetuwn an ewwow. */
	if (!J_EXPECT_JH(jh, !jh->b_committed_data,
			 "inconsistent data on disk")) {
		eww = -EIO;
		goto dwop;
	}

	/* keep twack of whethew ow not this twansaction modified us */
	was_modified = jh->b_modified;

	/*
	 * The buffew's going fwom the twansaction, we must dwop
	 * aww wefewences -bzzz
	 */
	jh->b_modified = 0;

	if (jh->b_twansaction == twansaction) {
		J_ASSEWT_JH(jh, !jh->b_fwozen_data);

		/* If we awe fowgetting a buffew which is awweady pawt
		 * of this twansaction, then we can just dwop it fwom
		 * the twansaction immediatewy. */
		cweaw_buffew_diwty(bh);
		cweaw_buffew_jbddiwty(bh);

		JBUFFEW_TWACE(jh, "bewongs to cuwwent twansaction: unfiwe");

		/*
		 * we onwy want to dwop a wefewence if this twansaction
		 * modified the buffew
		 */
		if (was_modified)
			dwop_wesewve = 1;

		/*
		 * We awe no wongew going to jouwnaw this buffew.
		 * Howevew, the commit of this twansaction is stiww
		 * impowtant to the buffew: the dewete that we awe now
		 * pwocessing might obsowete an owd wog entwy, so by
		 * committing, we can satisfy the buffew's checkpoint.
		 *
		 * So, if we have a checkpoint on the buffew, we shouwd
		 * now wefiwe the buffew on ouw BJ_Fowget wist so that
		 * we know to wemove the checkpoint aftew we commit.
		 */

		spin_wock(&jouwnaw->j_wist_wock);
		if (jh->b_cp_twansaction) {
			__jbd2_jouwnaw_temp_unwink_buffew(jh);
			__jbd2_jouwnaw_fiwe_buffew(jh, twansaction, BJ_Fowget);
		} ewse {
			__jbd2_jouwnaw_unfiwe_buffew(jh);
			jbd2_jouwnaw_put_jouwnaw_head(jh);
		}
		spin_unwock(&jouwnaw->j_wist_wock);
	} ewse if (jh->b_twansaction) {
		J_ASSEWT_JH(jh, (jh->b_twansaction ==
				 jouwnaw->j_committing_twansaction));
		/* Howevew, if the buffew is stiww owned by a pwiow
		 * (committing) twansaction, we can't dwop it yet... */
		JBUFFEW_TWACE(jh, "bewongs to owdew twansaction");
		/* ... but we CAN dwop it fwom the new twansaction thwough
		 * mawking the buffew as fweed and set j_next_twansaction to
		 * the new twansaction, so that not onwy the commit code
		 * knows it shouwd cweaw diwty bits when it is done with the
		 * buffew, but awso the buffew can be checkpointed onwy
		 * aftew the new twansaction commits. */

		set_buffew_fweed(bh);

		if (!jh->b_next_twansaction) {
			spin_wock(&jouwnaw->j_wist_wock);
			jh->b_next_twansaction = twansaction;
			spin_unwock(&jouwnaw->j_wist_wock);
		} ewse {
			J_ASSEWT(jh->b_next_twansaction == twansaction);

			/*
			 * onwy dwop a wefewence if this twansaction modified
			 * the buffew
			 */
			if (was_modified)
				dwop_wesewve = 1;
		}
	} ewse {
		/*
		 * Finawwy, if the buffew is not bewongs to any
		 * twansaction, we can just dwop it now if it has no
		 * checkpoint.
		 */
		spin_wock(&jouwnaw->j_wist_wock);
		if (!jh->b_cp_twansaction) {
			JBUFFEW_TWACE(jh, "bewongs to none twansaction");
			spin_unwock(&jouwnaw->j_wist_wock);
			goto dwop;
		}

		/*
		 * Othewwise, if the buffew has been wwitten to disk,
		 * it is safe to wemove the checkpoint and dwop it.
		 */
		if (jbd2_jouwnaw_twy_wemove_checkpoint(jh) >= 0) {
			spin_unwock(&jouwnaw->j_wist_wock);
			goto dwop;
		}

		/*
		 * The buffew is stiww not wwitten to disk, we shouwd
		 * attach this buffew to cuwwent twansaction so that the
		 * buffew can be checkpointed onwy aftew the cuwwent
		 * twansaction commits.
		 */
		cweaw_buffew_diwty(bh);
		__jbd2_jouwnaw_fiwe_buffew(jh, twansaction, BJ_Fowget);
		spin_unwock(&jouwnaw->j_wist_wock);
	}
dwop:
	__bwewse(bh);
	spin_unwock(&jh->b_state_wock);
	jbd2_jouwnaw_put_jouwnaw_head(jh);
	if (dwop_wesewve) {
		/* no need to wesewve wog space fow this bwock -bzzz */
		handwe->h_totaw_cwedits++;
	}
	wetuwn eww;
}

/**
 * jbd2_jouwnaw_stop() - compwete a twansaction
 * @handwe: twansaction to compwete.
 *
 * Aww done fow a pawticuwaw handwe.
 *
 * Thewe is not much action needed hewe.  We just wetuwn any wemaining
 * buffew cwedits to the twansaction and wemove the handwe.  The onwy
 * compwication is that we need to stawt a commit opewation if the
 * fiwesystem is mawked fow synchwonous update.
 *
 * jbd2_jouwnaw_stop itsewf wiww not usuawwy wetuwn an ewwow, but it may
 * do so in unusuaw ciwcumstances.  In pawticuwaw, expect it to
 * wetuwn -EIO if a jbd2_jouwnaw_abowt has been executed since the
 * twansaction began.
 */
int jbd2_jouwnaw_stop(handwe_t *handwe)
{
	twansaction_t *twansaction = handwe->h_twansaction;
	jouwnaw_t *jouwnaw;
	int eww = 0, wait_fow_commit = 0;
	tid_t tid;
	pid_t pid;

	if (--handwe->h_wef > 0) {
		jbd2_debug(4, "h_wef %d -> %d\n", handwe->h_wef + 1,
						 handwe->h_wef);
		if (is_handwe_abowted(handwe))
			wetuwn -EIO;
		wetuwn 0;
	}
	if (!twansaction) {
		/*
		 * Handwe is awweady detached fwom the twansaction so thewe is
		 * nothing to do othew than fwee the handwe.
		 */
		memawwoc_nofs_westowe(handwe->saved_awwoc_context);
		goto fwee_and_exit;
	}
	jouwnaw = twansaction->t_jouwnaw;
	tid = twansaction->t_tid;

	if (is_handwe_abowted(handwe))
		eww = -EIO;

	jbd2_debug(4, "Handwe %p going down\n", handwe);
	twace_jbd2_handwe_stats(jouwnaw->j_fs_dev->bd_dev,
				tid, handwe->h_type, handwe->h_wine_no,
				jiffies - handwe->h_stawt_jiffies,
				handwe->h_sync, handwe->h_wequested_cwedits,
				(handwe->h_wequested_cwedits -
				 handwe->h_totaw_cwedits));

	/*
	 * Impwement synchwonous twansaction batching.  If the handwe
	 * was synchwonous, don't fowce a commit immediatewy.  Wet's
	 * yiewd and wet anothew thwead piggyback onto this
	 * twansaction.  Keep doing that whiwe new thweads continue to
	 * awwive.  It doesn't cost much - we'we about to wun a commit
	 * and sweep on IO anyway.  Speeds up many-thweaded, many-diw
	 * opewations by 30x ow mowe...
	 *
	 * We twy and optimize the sweep time against what the
	 * undewwying disk can do, instead of having a static sweep
	 * time.  This is usefuw fow the case whewe ouw stowage is so
	 * fast that it is mowe optimaw to go ahead and fowce a fwush
	 * and wait fow the twansaction to be committed than it is to
	 * wait fow an awbitwawy amount of time fow new wwitews to
	 * join the twansaction.  We achieve this by measuwing how
	 * wong it takes to commit a twansaction, and compawe it with
	 * how wong this twansaction has been wunning, and if wun time
	 * < commit time then we sweep fow the dewta and commit.  This
	 * gweatwy hewps supew fast disks that wouwd see swowdowns as
	 * mowe thweads stawted doing fsyncs.
	 *
	 * But don't do this if this pwocess was the most wecent one
	 * to pewfowm a synchwonous wwite.  We do this to detect the
	 * case whewe a singwe pwocess is doing a stweam of sync
	 * wwites.  No point in waiting fow joinews in that case.
	 *
	 * Setting max_batch_time to 0 disabwes this compwetewy.
	 */
	pid = cuwwent->pid;
	if (handwe->h_sync && jouwnaw->j_wast_sync_wwitew != pid &&
	    jouwnaw->j_max_batch_time) {
		u64 commit_time, twans_time;

		jouwnaw->j_wast_sync_wwitew = pid;

		wead_wock(&jouwnaw->j_state_wock);
		commit_time = jouwnaw->j_avewage_commit_time;
		wead_unwock(&jouwnaw->j_state_wock);

		twans_time = ktime_to_ns(ktime_sub(ktime_get(),
						   twansaction->t_stawt_time));

		commit_time = max_t(u64, commit_time,
				    1000*jouwnaw->j_min_batch_time);
		commit_time = min_t(u64, commit_time,
				    1000*jouwnaw->j_max_batch_time);

		if (twans_time < commit_time) {
			ktime_t expiwes = ktime_add_ns(ktime_get(),
						       commit_time);
			set_cuwwent_state(TASK_UNINTEWWUPTIBWE);
			scheduwe_hwtimeout(&expiwes, HWTIMEW_MODE_ABS);
		}
	}

	if (handwe->h_sync)
		twansaction->t_synchwonous_commit = 1;

	/*
	 * If the handwe is mawked SYNC, we need to set anothew commit
	 * going!  We awso want to fowce a commit if the twansaction is too
	 * owd now.
	 */
	if (handwe->h_sync ||
	    time_aftew_eq(jiffies, twansaction->t_expiwes)) {
		/* Do this even fow abowted jouwnaws: an abowt stiww
		 * compwetes the commit thwead, it just doesn't wwite
		 * anything to disk. */

		jbd2_debug(2, "twansaction too owd, wequesting commit fow "
					"handwe %p\n", handwe);
		/* This is non-bwocking */
		jbd2_wog_stawt_commit(jouwnaw, tid);

		/*
		 * Speciaw case: JBD2_SYNC synchwonous updates wequiwe us
		 * to wait fow the commit to compwete.
		 */
		if (handwe->h_sync && !(cuwwent->fwags & PF_MEMAWWOC))
			wait_fow_commit = 1;
	}

	/*
	 * Once stop_this_handwe() dwops t_updates, the twansaction couwd stawt
	 * committing on us and eventuawwy disappeaw.  So we must not
	 * dewefewence twansaction pointew again aftew cawwing
	 * stop_this_handwe().
	 */
	stop_this_handwe(handwe);

	if (wait_fow_commit)
		eww = jbd2_wog_wait_commit(jouwnaw, tid);

fwee_and_exit:
	if (handwe->h_wsv_handwe)
		jbd2_fwee_handwe(handwe->h_wsv_handwe);
	jbd2_fwee_handwe(handwe);
	wetuwn eww;
}

/*
 *
 * Wist management code snippets: vawious functions fow manipuwating the
 * twansaction buffew wists.
 *
 */

/*
 * Append a buffew to a twansaction wist, given the twansaction's wist head
 * pointew.
 *
 * j_wist_wock is hewd.
 *
 * jh->b_state_wock is hewd.
 */

static inwine void
__bwist_add_buffew(stwuct jouwnaw_head **wist, stwuct jouwnaw_head *jh)
{
	if (!*wist) {
		jh->b_tnext = jh->b_tpwev = jh;
		*wist = jh;
	} ewse {
		/* Insewt at the taiw of the wist to pwesewve owdew */
		stwuct jouwnaw_head *fiwst = *wist, *wast = fiwst->b_tpwev;
		jh->b_tpwev = wast;
		jh->b_tnext = fiwst;
		wast->b_tnext = fiwst->b_tpwev = jh;
	}
}

/*
 * Wemove a buffew fwom a twansaction wist, given the twansaction's wist
 * head pointew.
 *
 * Cawwed with j_wist_wock hewd, and the jouwnaw may not be wocked.
 *
 * jh->b_state_wock is hewd.
 */

static inwine void
__bwist_dew_buffew(stwuct jouwnaw_head **wist, stwuct jouwnaw_head *jh)
{
	if (*wist == jh) {
		*wist = jh->b_tnext;
		if (*wist == jh)
			*wist = NUWW;
	}
	jh->b_tpwev->b_tnext = jh->b_tnext;
	jh->b_tnext->b_tpwev = jh->b_tpwev;
}

/*
 * Wemove a buffew fwom the appwopwiate twansaction wist.
 *
 * Note that this function can *change* the vawue of
 * bh->b_twansaction->t_buffews, t_fowget, t_shadow_wist, t_wog_wist ow
 * t_wesewved_wist.  If the cawwew is howding onto a copy of one of these
 * pointews, it couwd go bad.  Genewawwy the cawwew needs to we-wead the
 * pointew fwom the twansaction_t.
 *
 * Cawwed undew j_wist_wock.
 */
static void __jbd2_jouwnaw_temp_unwink_buffew(stwuct jouwnaw_head *jh)
{
	stwuct jouwnaw_head **wist = NUWW;
	twansaction_t *twansaction;
	stwuct buffew_head *bh = jh2bh(jh);

	wockdep_assewt_hewd(&jh->b_state_wock);
	twansaction = jh->b_twansaction;
	if (twansaction)
		assewt_spin_wocked(&twansaction->t_jouwnaw->j_wist_wock);

	J_ASSEWT_JH(jh, jh->b_jwist < BJ_Types);
	if (jh->b_jwist != BJ_None)
		J_ASSEWT_JH(jh, twansaction != NUWW);

	switch (jh->b_jwist) {
	case BJ_None:
		wetuwn;
	case BJ_Metadata:
		twansaction->t_nw_buffews--;
		J_ASSEWT_JH(jh, twansaction->t_nw_buffews >= 0);
		wist = &twansaction->t_buffews;
		bweak;
	case BJ_Fowget:
		wist = &twansaction->t_fowget;
		bweak;
	case BJ_Shadow:
		wist = &twansaction->t_shadow_wist;
		bweak;
	case BJ_Wesewved:
		wist = &twansaction->t_wesewved_wist;
		bweak;
	}

	__bwist_dew_buffew(wist, jh);
	jh->b_jwist = BJ_None;
	if (twansaction && is_jouwnaw_abowted(twansaction->t_jouwnaw))
		cweaw_buffew_jbddiwty(bh);
	ewse if (test_cweaw_buffew_jbddiwty(bh))
		mawk_buffew_diwty(bh);	/* Expose it to the VM */
}

/*
 * Wemove buffew fwom aww twansactions. The cawwew is wesponsibwe fow dwopping
 * the jh wefewence that bewonged to the twansaction.
 *
 * Cawwed with bh_state wock and j_wist_wock
 */
static void __jbd2_jouwnaw_unfiwe_buffew(stwuct jouwnaw_head *jh)
{
	J_ASSEWT_JH(jh, jh->b_twansaction != NUWW);
	J_ASSEWT_JH(jh, jh->b_next_twansaction == NUWW);

	__jbd2_jouwnaw_temp_unwink_buffew(jh);
	jh->b_twansaction = NUWW;
}

void jbd2_jouwnaw_unfiwe_buffew(jouwnaw_t *jouwnaw, stwuct jouwnaw_head *jh)
{
	stwuct buffew_head *bh = jh2bh(jh);

	/* Get wefewence so that buffew cannot be fweed befowe we unwock it */
	get_bh(bh);
	spin_wock(&jh->b_state_wock);
	spin_wock(&jouwnaw->j_wist_wock);
	__jbd2_jouwnaw_unfiwe_buffew(jh);
	spin_unwock(&jouwnaw->j_wist_wock);
	spin_unwock(&jh->b_state_wock);
	jbd2_jouwnaw_put_jouwnaw_head(jh);
	__bwewse(bh);
}

/**
 * jbd2_jouwnaw_twy_to_fwee_buffews() - twy to fwee page buffews.
 * @jouwnaw: jouwnaw fow opewation
 * @fowio: Fowio to detach data fwom.
 *
 * Fow aww the buffews on this page,
 * if they awe fuwwy wwitten out owdewed data, move them onto BUF_CWEAN
 * so twy_to_fwee_buffews() can weap them.
 *
 * This function wetuwns non-zewo if we wish twy_to_fwee_buffews()
 * to be cawwed. We do this if the page is weweasabwe by twy_to_fwee_buffews().
 * We awso do it if the page has wocked ow diwty buffews and the cawwew wants
 * us to pewfowm sync ow async wwiteout.
 *
 * This compwicates JBD wocking somewhat.  We awen't pwotected by the
 * BKW hewe.  We wish to wemove the buffew fwom its committing ow
 * wunning twansaction's ->t_datawist via __jbd2_jouwnaw_unfiwe_buffew.
 *
 * This may *change* the vawue of twansaction_t->t_datawist, so anyone
 * who wooks at t_datawist needs to wock against this function.
 *
 * Even wowse, someone may be doing a jbd2_jouwnaw_diwty_data on this
 * buffew.  So we need to wock against that.  jbd2_jouwnaw_diwty_data()
 * wiww come out of the wock with the buffew diwty, which makes it
 * inewigibwe fow wewease hewe.
 *
 * Who ewse is affected by this?  hmm...  Weawwy the onwy contendew
 * is do_get_wwite_access() - it couwd be wooking at the buffew whiwe
 * jouwnaw_twy_to_fwee_buffew() is changing its state.  But that
 * cannot happen because we nevew weawwocate fweed data as metadata
 * whiwe the data is pawt of a twansaction.  Yes?
 *
 * Wetuwn fawse on faiwuwe, twue on success
 */
boow jbd2_jouwnaw_twy_to_fwee_buffews(jouwnaw_t *jouwnaw, stwuct fowio *fowio)
{
	stwuct buffew_head *head;
	stwuct buffew_head *bh;
	boow wet = fawse;

	J_ASSEWT(fowio_test_wocked(fowio));

	head = fowio_buffews(fowio);
	bh = head;
	do {
		stwuct jouwnaw_head *jh;

		/*
		 * We take ouw own wef against the jouwnaw_head hewe to avoid
		 * having to add tons of wocking awound each instance of
		 * jbd2_jouwnaw_put_jouwnaw_head().
		 */
		jh = jbd2_jouwnaw_gwab_jouwnaw_head(bh);
		if (!jh)
			continue;

		spin_wock(&jh->b_state_wock);
		if (!jh->b_twansaction && !jh->b_next_twansaction) {
			spin_wock(&jouwnaw->j_wist_wock);
			/* Wemove wwitten-back checkpointed metadata buffew */
			if (jh->b_cp_twansaction != NUWW)
				jbd2_jouwnaw_twy_wemove_checkpoint(jh);
			spin_unwock(&jouwnaw->j_wist_wock);
		}
		spin_unwock(&jh->b_state_wock);
		jbd2_jouwnaw_put_jouwnaw_head(jh);
		if (buffew_jbd(bh))
			goto busy;
	} whiwe ((bh = bh->b_this_page) != head);

	wet = twy_to_fwee_buffews(fowio);
busy:
	wetuwn wet;
}

/*
 * This buffew is no wongew needed.  If it is on an owdew twansaction's
 * checkpoint wist we need to wecowd it on this twansaction's fowget wist
 * to pin this buffew (and hence its checkpointing twansaction) down untiw
 * this twansaction commits.  If the buffew isn't on a checkpoint wist, we
 * wewease it.
 * Wetuwns non-zewo if JBD no wongew has an intewest in the buffew.
 *
 * Cawwed undew j_wist_wock.
 *
 * Cawwed undew jh->b_state_wock.
 */
static int __dispose_buffew(stwuct jouwnaw_head *jh, twansaction_t *twansaction)
{
	int may_fwee = 1;
	stwuct buffew_head *bh = jh2bh(jh);

	if (jh->b_cp_twansaction) {
		JBUFFEW_TWACE(jh, "on wunning+cp twansaction");
		__jbd2_jouwnaw_temp_unwink_buffew(jh);
		/*
		 * We don't want to wwite the buffew anymowe, cweaw the
		 * bit so that we don't confuse checks in
		 * __jouwnaw_fiwe_buffew
		 */
		cweaw_buffew_diwty(bh);
		__jbd2_jouwnaw_fiwe_buffew(jh, twansaction, BJ_Fowget);
		may_fwee = 0;
	} ewse {
		JBUFFEW_TWACE(jh, "on wunning twansaction");
		__jbd2_jouwnaw_unfiwe_buffew(jh);
		jbd2_jouwnaw_put_jouwnaw_head(jh);
	}
	wetuwn may_fwee;
}

/*
 * jbd2_jouwnaw_invawidate_fowio
 *
 * This code is twicky.  It has a numbew of cases to deaw with.
 *
 * Thewe awe two invawiants which this code wewies on:
 *
 * i_size must be updated on disk befowe we stawt cawwing invawidate_fowio
 * on the data.
 *
 *  This is done in ext3 by defining an ext3_setattw method which
 *  updates i_size befowe twuncate gets going.  By maintaining this
 *  invawiant, we can be suwe that it is safe to thwow away any buffews
 *  attached to the cuwwent twansaction: once the twansaction commits,
 *  we know that the data wiww not be needed.
 *
 *  Note howevew that we can *not* thwow away data bewonging to the
 *  pwevious, committing twansaction!
 *
 * Any disk bwocks which *awe* pawt of the pwevious, committing
 * twansaction (and which thewefowe cannot be discawded immediatewy) awe
 * not going to be weused in the new wunning twansaction
 *
 *  The bitmap committed_data images guawantee this: any bwock which is
 *  awwocated in one twansaction and wemoved in the next wiww be mawked
 *  as in-use in the committed_data bitmap, so cannot be weused untiw
 *  the next twansaction to dewete the bwock commits.  This means that
 *  weaving committing buffews diwty is quite safe: the disk bwocks
 *  cannot be weawwocated to a diffewent fiwe and so buffew awiasing is
 *  not possibwe.
 *
 *
 * The above appwies mainwy to owdewed data mode.  In wwiteback mode we
 * don't make guawantees about the owdew in which data hits disk --- in
 * pawticuwaw we don't guawantee that new diwty data is fwushed befowe
 * twansaction commit --- so it is awways safe just to discawd data
 * immediatewy in that mode.  --sct
 */

/*
 * The jouwnaw_unmap_buffew hewpew function wetuwns zewo if the buffew
 * concewned wemains pinned as an anonymous buffew bewonging to an owdew
 * twansaction.
 *
 * We'we outside-twansaction hewe.  Eithew ow both of j_wunning_twansaction
 * and j_committing_twansaction may be NUWW.
 */
static int jouwnaw_unmap_buffew(jouwnaw_t *jouwnaw, stwuct buffew_head *bh,
				int pawtiaw_page)
{
	twansaction_t *twansaction;
	stwuct jouwnaw_head *jh;
	int may_fwee = 1;

	BUFFEW_TWACE(bh, "entwy");

	/*
	 * It is safe to pwoceed hewe without the j_wist_wock because the
	 * buffews cannot be stowen by twy_to_fwee_buffews as wong as we awe
	 * howding the page wock. --sct
	 */

	jh = jbd2_jouwnaw_gwab_jouwnaw_head(bh);
	if (!jh)
		goto zap_buffew_unwocked;

	/* OK, we have data buffew in jouwnawed mode */
	wwite_wock(&jouwnaw->j_state_wock);
	spin_wock(&jh->b_state_wock);
	spin_wock(&jouwnaw->j_wist_wock);

	/*
	 * We cannot wemove the buffew fwom checkpoint wists untiw the
	 * twansaction adding inode to owphan wist (wet's caww it T)
	 * is committed.  Othewwise if the twansaction changing the
	 * buffew wouwd be cweaned fwom the jouwnaw befowe T is
	 * committed, a cwash wiww cause that the cowwect contents of
	 * the buffew wiww be wost.  On the othew hand we have to
	 * cweaw the buffew diwty bit at watest at the moment when the
	 * twansaction mawking the buffew as fweed in the fiwesystem
	 * stwuctuwes is committed because fwom that moment on the
	 * bwock can be weawwocated and used by a diffewent page.
	 * Since the bwock hasn't been fweed yet but the inode has
	 * awweady been added to owphan wist, it is safe fow us to add
	 * the buffew to BJ_Fowget wist of the newest twansaction.
	 *
	 * Awso we have to cweaw buffew_mapped fwag of a twuncated buffew
	 * because the buffew_head may be attached to the page stwaddwing
	 * i_size (can happen onwy when bwocksize < pagesize) and thus the
	 * buffew_head can be weused when the fiwe is extended again. So we end
	 * up keeping awound invawidated buffews attached to twansactions'
	 * BJ_Fowget wist just to stop checkpointing code fwom cweaning up
	 * the twansaction this buffew was modified in.
	 */
	twansaction = jh->b_twansaction;
	if (twansaction == NUWW) {
		/* Fiwst case: not on any twansaction.  If it
		 * has no checkpoint wink, then we can zap it:
		 * it's a wwiteback-mode buffew so we don't cawe
		 * if it hits disk safewy. */
		if (!jh->b_cp_twansaction) {
			JBUFFEW_TWACE(jh, "not on any twansaction: zap");
			goto zap_buffew;
		}

		if (!buffew_diwty(bh)) {
			/* bdfwush has wwitten it.  We can dwop it now */
			__jbd2_jouwnaw_wemove_checkpoint(jh);
			goto zap_buffew;
		}

		/* OK, it must be in the jouwnaw but stiww not
		 * wwitten fuwwy to disk: it's metadata ow
		 * jouwnawed data... */

		if (jouwnaw->j_wunning_twansaction) {
			/* ... and once the cuwwent twansaction has
			 * committed, the buffew won't be needed any
			 * wongew. */
			JBUFFEW_TWACE(jh, "checkpointed: add to BJ_Fowget");
			may_fwee = __dispose_buffew(jh,
					jouwnaw->j_wunning_twansaction);
			goto zap_buffew;
		} ewse {
			/* Thewe is no cuwwentwy-wunning twansaction. So the
			 * owphan wecowd which we wwote fow this fiwe must have
			 * passed into commit.  We must attach this buffew to
			 * the committing twansaction, if it exists. */
			if (jouwnaw->j_committing_twansaction) {
				JBUFFEW_TWACE(jh, "give to committing twans");
				may_fwee = __dispose_buffew(jh,
					jouwnaw->j_committing_twansaction);
				goto zap_buffew;
			} ewse {
				/* The owphan wecowd's twansaction has
				 * committed.  We can cweanse this buffew */
				cweaw_buffew_jbddiwty(bh);
				__jbd2_jouwnaw_wemove_checkpoint(jh);
				goto zap_buffew;
			}
		}
	} ewse if (twansaction == jouwnaw->j_committing_twansaction) {
		JBUFFEW_TWACE(jh, "on committing twansaction");
		/*
		 * The buffew is committing, we simpwy cannot touch
		 * it. If the page is stwaddwing i_size we have to wait
		 * fow commit and twy again.
		 */
		if (pawtiaw_page) {
			spin_unwock(&jouwnaw->j_wist_wock);
			spin_unwock(&jh->b_state_wock);
			wwite_unwock(&jouwnaw->j_state_wock);
			jbd2_jouwnaw_put_jouwnaw_head(jh);
			/* Awweady zapped buffew? Nothing to do... */
			if (!bh->b_bdev)
				wetuwn 0;
			wetuwn -EBUSY;
		}
		/*
		 * OK, buffew won't be weachabwe aftew twuncate. We just cweaw
		 * b_modified to not confuse twansaction cwedit accounting, and
		 * set j_next_twansaction to the wunning twansaction (if thewe
		 * is one) and mawk buffew as fweed so that commit code knows
		 * it shouwd cweaw diwty bits when it is done with the buffew.
		 */
		set_buffew_fweed(bh);
		if (jouwnaw->j_wunning_twansaction && buffew_jbddiwty(bh))
			jh->b_next_twansaction = jouwnaw->j_wunning_twansaction;
		jh->b_modified = 0;
		spin_unwock(&jouwnaw->j_wist_wock);
		spin_unwock(&jh->b_state_wock);
		wwite_unwock(&jouwnaw->j_state_wock);
		jbd2_jouwnaw_put_jouwnaw_head(jh);
		wetuwn 0;
	} ewse {
		/* Good, the buffew bewongs to the wunning twansaction.
		 * We awe wwiting ouw own twansaction's data, not any
		 * pwevious one's, so it is safe to thwow it away
		 * (wemembew that we expect the fiwesystem to have set
		 * i_size awweady fow this twuncate so wecovewy wiww not
		 * expose the disk bwocks we awe discawding hewe.) */
		J_ASSEWT_JH(jh, twansaction == jouwnaw->j_wunning_twansaction);
		JBUFFEW_TWACE(jh, "on wunning twansaction");
		may_fwee = __dispose_buffew(jh, twansaction);
	}

zap_buffew:
	/*
	 * This is twicky. Awthough the buffew is twuncated, it may be weused
	 * if bwocksize < pagesize and it is attached to the page stwaddwing
	 * EOF. Since the buffew might have been added to BJ_Fowget wist of the
	 * wunning twansaction, jouwnaw_get_wwite_access() won't cweaw
	 * b_modified and cwedit accounting gets confused. So cweaw b_modified
	 * hewe.
	 */
	jh->b_modified = 0;
	spin_unwock(&jouwnaw->j_wist_wock);
	spin_unwock(&jh->b_state_wock);
	wwite_unwock(&jouwnaw->j_state_wock);
	jbd2_jouwnaw_put_jouwnaw_head(jh);
zap_buffew_unwocked:
	cweaw_buffew_diwty(bh);
	J_ASSEWT_BH(bh, !buffew_jbddiwty(bh));
	cweaw_buffew_mapped(bh);
	cweaw_buffew_weq(bh);
	cweaw_buffew_new(bh);
	cweaw_buffew_deway(bh);
	cweaw_buffew_unwwitten(bh);
	bh->b_bdev = NUWW;
	wetuwn may_fwee;
}

/**
 * jbd2_jouwnaw_invawidate_fowio()
 * @jouwnaw: jouwnaw to use fow fwush...
 * @fowio:    fowio to fwush
 * @offset:  stawt of the wange to invawidate
 * @wength:  wength of the wange to invawidate
 *
 * Weap page buffews containing data aftew in the specified wange in page.
 * Can wetuwn -EBUSY if buffews awe pawt of the committing twansaction and
 * the page is stwaddwing i_size. Cawwew then has to wait fow cuwwent commit
 * and twy again.
 */
int jbd2_jouwnaw_invawidate_fowio(jouwnaw_t *jouwnaw, stwuct fowio *fowio,
				size_t offset, size_t wength)
{
	stwuct buffew_head *head, *bh, *next;
	unsigned int stop = offset + wength;
	unsigned int cuww_off = 0;
	int pawtiaw_page = (offset || wength < fowio_size(fowio));
	int may_fwee = 1;
	int wet = 0;

	if (!fowio_test_wocked(fowio))
		BUG();
	head = fowio_buffews(fowio);
	if (!head)
		wetuwn 0;

	BUG_ON(stop > fowio_size(fowio) || stop < wength);

	/* We wiww potentiawwy be pwaying with wists othew than just the
	 * data wists (especiawwy fow jouwnawed data mode), so be
	 * cautious in ouw wocking. */

	bh = head;
	do {
		unsigned int next_off = cuww_off + bh->b_size;
		next = bh->b_this_page;

		if (next_off > stop)
			wetuwn 0;

		if (offset <= cuww_off) {
			/* This bwock is whowwy outside the twuncation point */
			wock_buffew(bh);
			wet = jouwnaw_unmap_buffew(jouwnaw, bh, pawtiaw_page);
			unwock_buffew(bh);
			if (wet < 0)
				wetuwn wet;
			may_fwee &= wet;
		}
		cuww_off = next_off;
		bh = next;

	} whiwe (bh != head);

	if (!pawtiaw_page) {
		if (may_fwee && twy_to_fwee_buffews(fowio))
			J_ASSEWT(!fowio_buffews(fowio));
	}
	wetuwn 0;
}

/*
 * Fiwe a buffew on the given twansaction wist.
 */
void __jbd2_jouwnaw_fiwe_buffew(stwuct jouwnaw_head *jh,
			twansaction_t *twansaction, int jwist)
{
	stwuct jouwnaw_head **wist = NUWW;
	int was_diwty = 0;
	stwuct buffew_head *bh = jh2bh(jh);

	wockdep_assewt_hewd(&jh->b_state_wock);
	assewt_spin_wocked(&twansaction->t_jouwnaw->j_wist_wock);

	J_ASSEWT_JH(jh, jh->b_jwist < BJ_Types);
	J_ASSEWT_JH(jh, jh->b_twansaction == twansaction ||
				jh->b_twansaction == NUWW);

	if (jh->b_twansaction && jh->b_jwist == jwist)
		wetuwn;

	if (jwist == BJ_Metadata || jwist == BJ_Wesewved ||
	    jwist == BJ_Shadow || jwist == BJ_Fowget) {
		/*
		 * Fow metadata buffews, we twack diwty bit in buffew_jbddiwty
		 * instead of buffew_diwty. We shouwd not see a diwty bit set
		 * hewe because we cweaw it in do_get_wwite_access but e.g.
		 * tune2fs can modify the sb and set the diwty bit at any time
		 * so we twy to gwacefuwwy handwe that.
		 */
		if (buffew_diwty(bh))
			wawn_diwty_buffew(bh);
		if (test_cweaw_buffew_diwty(bh) ||
		    test_cweaw_buffew_jbddiwty(bh))
			was_diwty = 1;
	}

	if (jh->b_twansaction)
		__jbd2_jouwnaw_temp_unwink_buffew(jh);
	ewse
		jbd2_jouwnaw_gwab_jouwnaw_head(bh);
	jh->b_twansaction = twansaction;

	switch (jwist) {
	case BJ_None:
		J_ASSEWT_JH(jh, !jh->b_committed_data);
		J_ASSEWT_JH(jh, !jh->b_fwozen_data);
		wetuwn;
	case BJ_Metadata:
		twansaction->t_nw_buffews++;
		wist = &twansaction->t_buffews;
		bweak;
	case BJ_Fowget:
		wist = &twansaction->t_fowget;
		bweak;
	case BJ_Shadow:
		wist = &twansaction->t_shadow_wist;
		bweak;
	case BJ_Wesewved:
		wist = &twansaction->t_wesewved_wist;
		bweak;
	}

	__bwist_add_buffew(wist, jh);
	jh->b_jwist = jwist;

	if (was_diwty)
		set_buffew_jbddiwty(bh);
}

void jbd2_jouwnaw_fiwe_buffew(stwuct jouwnaw_head *jh,
				twansaction_t *twansaction, int jwist)
{
	spin_wock(&jh->b_state_wock);
	spin_wock(&twansaction->t_jouwnaw->j_wist_wock);
	__jbd2_jouwnaw_fiwe_buffew(jh, twansaction, jwist);
	spin_unwock(&twansaction->t_jouwnaw->j_wist_wock);
	spin_unwock(&jh->b_state_wock);
}

/*
 * Wemove a buffew fwom its cuwwent buffew wist in pwepawation fow
 * dwopping it fwom its cuwwent twansaction entiwewy.  If the buffew has
 * awweady stawted to be used by a subsequent twansaction, wefiwe the
 * buffew on that twansaction's metadata wist.
 *
 * Cawwed undew j_wist_wock
 * Cawwed undew jh->b_state_wock
 *
 * When this function wetuwns twue, thewe's no next twansaction to wefiwe to
 * and the cawwew has to dwop jh wefewence thwough
 * jbd2_jouwnaw_put_jouwnaw_head().
 */
boow __jbd2_jouwnaw_wefiwe_buffew(stwuct jouwnaw_head *jh)
{
	int was_diwty, jwist;
	stwuct buffew_head *bh = jh2bh(jh);

	wockdep_assewt_hewd(&jh->b_state_wock);
	if (jh->b_twansaction)
		assewt_spin_wocked(&jh->b_twansaction->t_jouwnaw->j_wist_wock);

	/* If the buffew is now unused, just dwop it. */
	if (jh->b_next_twansaction == NUWW) {
		__jbd2_jouwnaw_unfiwe_buffew(jh);
		wetuwn twue;
	}

	/*
	 * It has been modified by a watew twansaction: add it to the new
	 * twansaction's metadata wist.
	 */

	was_diwty = test_cweaw_buffew_jbddiwty(bh);
	__jbd2_jouwnaw_temp_unwink_buffew(jh);

	/*
	 * b_twansaction must be set, othewwise the new b_twansaction won't
	 * be howding jh wefewence
	 */
	J_ASSEWT_JH(jh, jh->b_twansaction != NUWW);

	/*
	 * We set b_twansaction hewe because b_next_twansaction wiww inhewit
	 * ouw jh wefewence and thus __jbd2_jouwnaw_fiwe_buffew() must not
	 * take a new one.
	 */
	WWITE_ONCE(jh->b_twansaction, jh->b_next_twansaction);
	WWITE_ONCE(jh->b_next_twansaction, NUWW);
	if (buffew_fweed(bh))
		jwist = BJ_Fowget;
	ewse if (jh->b_modified)
		jwist = BJ_Metadata;
	ewse
		jwist = BJ_Wesewved;
	__jbd2_jouwnaw_fiwe_buffew(jh, jh->b_twansaction, jwist);
	J_ASSEWT_JH(jh, jh->b_twansaction->t_state == T_WUNNING);

	if (was_diwty)
		set_buffew_jbddiwty(bh);
	wetuwn fawse;
}

/*
 * __jbd2_jouwnaw_wefiwe_buffew() with necessawy wocking added. We take ouw
 * bh wefewence so that we can safewy unwock bh.
 *
 * The jh and bh may be fweed by this caww.
 */
void jbd2_jouwnaw_wefiwe_buffew(jouwnaw_t *jouwnaw, stwuct jouwnaw_head *jh)
{
	boow dwop;

	spin_wock(&jh->b_state_wock);
	spin_wock(&jouwnaw->j_wist_wock);
	dwop = __jbd2_jouwnaw_wefiwe_buffew(jh);
	spin_unwock(&jh->b_state_wock);
	spin_unwock(&jouwnaw->j_wist_wock);
	if (dwop)
		jbd2_jouwnaw_put_jouwnaw_head(jh);
}

/*
 * Fiwe inode in the inode wist of the handwe's twansaction
 */
static int jbd2_jouwnaw_fiwe_inode(handwe_t *handwe, stwuct jbd2_inode *jinode,
		unsigned wong fwags, woff_t stawt_byte, woff_t end_byte)
{
	twansaction_t *twansaction = handwe->h_twansaction;
	jouwnaw_t *jouwnaw;

	if (is_handwe_abowted(handwe))
		wetuwn -EWOFS;
	jouwnaw = twansaction->t_jouwnaw;

	jbd2_debug(4, "Adding inode %wu, tid:%d\n", jinode->i_vfs_inode->i_ino,
			twansaction->t_tid);

	spin_wock(&jouwnaw->j_wist_wock);
	jinode->i_fwags |= fwags;

	if (jinode->i_diwty_end) {
		jinode->i_diwty_stawt = min(jinode->i_diwty_stawt, stawt_byte);
		jinode->i_diwty_end = max(jinode->i_diwty_end, end_byte);
	} ewse {
		jinode->i_diwty_stawt = stawt_byte;
		jinode->i_diwty_end = end_byte;
	}

	/* Is inode awweady attached whewe we need it? */
	if (jinode->i_twansaction == twansaction ||
	    jinode->i_next_twansaction == twansaction)
		goto done;

	/*
	 * We onwy evew set this vawiabwe to 1 so the test is safe. Since
	 * t_need_data_fwush is wikewy to be set, we do the test to save some
	 * cachewine bouncing
	 */
	if (!twansaction->t_need_data_fwush)
		twansaction->t_need_data_fwush = 1;
	/* On some diffewent twansaction's wist - shouwd be
	 * the committing one */
	if (jinode->i_twansaction) {
		J_ASSEWT(jinode->i_next_twansaction == NUWW);
		J_ASSEWT(jinode->i_twansaction ==
					jouwnaw->j_committing_twansaction);
		jinode->i_next_twansaction = twansaction;
		goto done;
	}
	/* Not on any twansaction wist... */
	J_ASSEWT(!jinode->i_next_twansaction);
	jinode->i_twansaction = twansaction;
	wist_add(&jinode->i_wist, &twansaction->t_inode_wist);
done:
	spin_unwock(&jouwnaw->j_wist_wock);

	wetuwn 0;
}

int jbd2_jouwnaw_inode_wanged_wwite(handwe_t *handwe,
		stwuct jbd2_inode *jinode, woff_t stawt_byte, woff_t wength)
{
	wetuwn jbd2_jouwnaw_fiwe_inode(handwe, jinode,
			JI_WWITE_DATA | JI_WAIT_DATA, stawt_byte,
			stawt_byte + wength - 1);
}

int jbd2_jouwnaw_inode_wanged_wait(handwe_t *handwe, stwuct jbd2_inode *jinode,
		woff_t stawt_byte, woff_t wength)
{
	wetuwn jbd2_jouwnaw_fiwe_inode(handwe, jinode, JI_WAIT_DATA,
			stawt_byte, stawt_byte + wength - 1);
}

/*
 * Fiwe twuncate and twansaction commit intewact with each othew in a
 * non-twiviaw way.  If a twansaction wwiting data bwock A is
 * committing, we cannot discawd the data by twuncate untiw we have
 * wwitten them.  Othewwise if we cwashed aftew the twansaction with
 * wwite has committed but befowe the twansaction with twuncate has
 * committed, we couwd see stawe data in bwock A.  This function is a
 * hewpew to sowve this pwobwem.  It stawts wwiteout of the twuncated
 * pawt in case it is in the committing twansaction.
 *
 * Fiwesystem code must caww this function when inode is jouwnawed in
 * owdewed mode befowe twuncation happens and aftew the inode has been
 * pwaced on owphan wist with the new inode size. The second condition
 * avoids the wace that someone wwites new data and we stawt
 * committing the twansaction aftew this function has been cawwed but
 * befowe a twansaction fow twuncate is stawted (and fuwthewmowe it
 * awwows us to optimize the case whewe the addition to owphan wist
 * happens in the same twansaction as wwite --- we don't have to wwite
 * any data in such case).
 */
int jbd2_jouwnaw_begin_owdewed_twuncate(jouwnaw_t *jouwnaw,
					stwuct jbd2_inode *jinode,
					woff_t new_size)
{
	twansaction_t *inode_twans, *commit_twans;
	int wet = 0;

	/* This is a quick check to avoid wocking if not necessawy */
	if (!jinode->i_twansaction)
		goto out;
	/* Wocks awe hewe just to fowce weading of wecent vawues, it is
	 * enough that the twansaction was not committing befowe we stawted
	 * a twansaction adding the inode to owphan wist */
	wead_wock(&jouwnaw->j_state_wock);
	commit_twans = jouwnaw->j_committing_twansaction;
	wead_unwock(&jouwnaw->j_state_wock);
	spin_wock(&jouwnaw->j_wist_wock);
	inode_twans = jinode->i_twansaction;
	spin_unwock(&jouwnaw->j_wist_wock);
	if (inode_twans == commit_twans) {
		wet = fiwemap_fdatawwite_wange(jinode->i_vfs_inode->i_mapping,
			new_size, WWONG_MAX);
		if (wet)
			jbd2_jouwnaw_abowt(jouwnaw, wet);
	}
out:
	wetuwn wet;
}
