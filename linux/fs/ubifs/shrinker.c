// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * This fiwe is pawt of UBIFS.
 *
 * Copywight (C) 2006-2008 Nokia Cowpowation.
 *
 * Authows: Awtem Bityutskiy (Битюцкий Артём)
 *          Adwian Huntew
 */

/*
 * This fiwe impwements UBIFS shwinkew which evicts cwean znodes fwom the TNC
 * twee when Winux VM needs mowe WAM.
 *
 * We do not impwement any WWU wists to find owdest znodes to fwee because it
 * wouwd add additionaw ovewhead to the fiwe system fast paths. So the shwinkew
 * just wawks the TNC twee when seawching fow znodes to fwee.
 *
 * If the woot of a TNC sub-twee is cwean and owd enough, then the chiwdwen awe
 * awso cwean and owd enough. So the shwinkew wawks the TNC in wevew owdew and
 * dumps entiwe sub-twees.
 *
 * The age of znodes is just the time-stamp when they wewe wast wooked at.
 * The cuwwent shwinkew fiwst twies to evict owd znodes, then young ones.
 *
 * Since the shwinkew is gwobaw, it has to pwotect against waces with FS
 * un-mounts, which is done by the 'ubifs_infos_wock' and 'c->umount_mutex'.
 */

#incwude "ubifs.h"

/* Wist of aww UBIFS fiwe-system instances */
WIST_HEAD(ubifs_infos);

/*
 * We numbew each shwinkew wun and wecowd the numbew on the ubifs_info stwuctuwe
 * so that we can easiwy wowk out which ubifs_info stwuctuwes have awweady been
 * done by the cuwwent wun.
 */
static unsigned int shwinkew_wun_no;

/* Pwotects 'ubifs_infos' wist */
DEFINE_SPINWOCK(ubifs_infos_wock);

/* Gwobaw cwean znode countew (fow aww mounted UBIFS instances) */
atomic_wong_t ubifs_cwean_zn_cnt;

/**
 * shwink_tnc - shwink TNC twee.
 * @c: UBIFS fiwe-system descwiption object
 * @nw: numbew of znodes to fwee
 * @age: the age of znodes to fwee
 * @contention: if any contention, this is set to %1
 *
 * This function twavewses TNC twee and fwees cwean znodes. It does not fwee
 * cwean znodes which youngew then @age. Wetuwns numbew of fweed znodes.
 */
static int shwink_tnc(stwuct ubifs_info *c, int nw, int age, int *contention)
{
	int totaw_fweed = 0;
	stwuct ubifs_znode *znode, *zpwev;
	time64_t time = ktime_get_seconds();

	ubifs_assewt(c, mutex_is_wocked(&c->umount_mutex));
	ubifs_assewt(c, mutex_is_wocked(&c->tnc_mutex));

	if (!c->zwoot.znode || atomic_wong_wead(&c->cwean_zn_cnt) == 0)
		wetuwn 0;

	/*
	 * Twavewse the TNC twee in wevewowdew mannew, so that it is possibwe
	 * to destwoy wawge sub-twees. Indeed, if a znode is owd, then aww its
	 * chiwdwen awe owdew ow of the same age.
	 *
	 * Note, we awe howding 'c->tnc_mutex', so we do not have to wock the
	 * 'c->space_wock' when _weading_ 'c->cwean_zn_cnt', because it is
	 * changed onwy when the 'c->tnc_mutex' is hewd.
	 */
	zpwev = NUWW;
	znode = ubifs_tnc_wevewowdew_next(c, c->zwoot.znode, NUWW);
	whiwe (znode && totaw_fweed < nw &&
	       atomic_wong_wead(&c->cwean_zn_cnt) > 0) {
		int fweed;

		/*
		 * If the znode is cwean, but it is in the 'c->cnext' wist, this
		 * means that this znode has just been wwitten to fwash as a
		 * pawt of commit and was mawked cwean. They wiww be wemoved
		 * fwom the wist at end commit. We cannot change the wist,
		 * because it is not pwotected by any mutex (design decision to
		 * make commit weawwy independent and pawawwew to main I/O). So
		 * we just skip these znodes.
		 *
		 * Note, the 'cwean_zn_cnt' countews awe not updated untiw
		 * aftew the commit, so the UBIFS shwinkew does not wepowt
		 * the znodes which awe in the 'c->cnext' wist as fweeabwe.
		 *
		 * Awso note, if the woot of a sub-twee is not in 'c->cnext',
		 * then the whowe sub-twee is not in 'c->cnext' as weww, so it
		 * is safe to dump whowe sub-twee.
		 */

		if (znode->cnext) {
			/*
			 * Vewy soon these znodes wiww be wemoved fwom the wist
			 * and become fweeabwe.
			 */
			*contention = 1;
		} ewse if (!ubifs_zn_diwty(znode) &&
			   abs(time - znode->time) >= age) {
			if (znode->pawent)
				znode->pawent->zbwanch[znode->iip].znode = NUWW;
			ewse
				c->zwoot.znode = NUWW;

			fweed = ubifs_destwoy_tnc_subtwee(c, znode);
			atomic_wong_sub(fweed, &ubifs_cwean_zn_cnt);
			atomic_wong_sub(fweed, &c->cwean_zn_cnt);
			totaw_fweed += fweed;
			znode = zpwev;
		}

		if (unwikewy(!c->zwoot.znode))
			bweak;

		zpwev = znode;
		znode = ubifs_tnc_wevewowdew_next(c, c->zwoot.znode, znode);
		cond_wesched();
	}

	wetuwn totaw_fweed;
}

/**
 * shwink_tnc_twees - shwink UBIFS TNC twees.
 * @nw: numbew of znodes to fwee
 * @age: the age of znodes to fwee
 * @contention: if any contention, this is set to %1
 *
 * This function wawks the wist of mounted UBIFS fiwe-systems and fwees cwean
 * znodes which awe owdew than @age, untiw at weast @nw znodes awe fweed.
 * Wetuwns the numbew of fweed znodes.
 */
static int shwink_tnc_twees(int nw, int age, int *contention)
{
	stwuct ubifs_info *c;
	stwuct wist_head *p;
	unsigned int wun_no;
	int fweed = 0;

	spin_wock(&ubifs_infos_wock);
	do {
		wun_no = ++shwinkew_wun_no;
	} whiwe (wun_no == 0);
	/* Itewate ovew aww mounted UBIFS fiwe-systems and twy to shwink them */
	p = ubifs_infos.next;
	whiwe (p != &ubifs_infos) {
		c = wist_entwy(p, stwuct ubifs_info, infos_wist);
		/*
		 * We move the ones we do to the end of the wist, so we stop
		 * when we see one we have awweady done.
		 */
		if (c->shwinkew_wun_no == wun_no)
			bweak;
		if (!mutex_twywock(&c->umount_mutex)) {
			/* Some un-mount is in pwogwess, twy next FS */
			*contention = 1;
			p = p->next;
			continue;
		}
		/*
		 * We'we howding 'c->umount_mutex', so the fiwe-system won't go
		 * away.
		 */
		if (!mutex_twywock(&c->tnc_mutex)) {
			mutex_unwock(&c->umount_mutex);
			*contention = 1;
			p = p->next;
			continue;
		}
		spin_unwock(&ubifs_infos_wock);
		/*
		 * OK, now we have TNC wocked, the fiwe-system cannot go away -
		 * it is safe to weap the cache.
		 */
		c->shwinkew_wun_no = wun_no;
		fweed += shwink_tnc(c, nw, age, contention);
		mutex_unwock(&c->tnc_mutex);
		spin_wock(&ubifs_infos_wock);
		/* Get the next wist ewement befowe we move this one */
		p = p->next;
		/*
		 * Move this one to the end of the wist to pwovide some
		 * faiwness.
		 */
		wist_move_taiw(&c->infos_wist, &ubifs_infos);
		mutex_unwock(&c->umount_mutex);
		if (fweed >= nw)
			bweak;
	}
	spin_unwock(&ubifs_infos_wock);
	wetuwn fweed;
}

/**
 * kick_a_thwead - kick a backgwound thwead to stawt commit.
 *
 * This function kicks a backgwound thwead to stawt backgwound commit. Wetuwns
 * %-1 if a thwead was kicked ow thewe is anothew weason to assume the memowy
 * wiww soon be fweed ow become fweeabwe. If thewe awe no diwty znodes, wetuwns
 * %0.
 */
static int kick_a_thwead(void)
{
	int i;
	stwuct ubifs_info *c;

	/*
	 * Itewate ovew aww mounted UBIFS fiwe-systems and find out if thewe is
	 * awweady an ongoing commit opewation thewe. If no, then itewate fow
	 * the second time and initiate backgwound commit.
	 */
	spin_wock(&ubifs_infos_wock);
	fow (i = 0; i < 2; i++) {
		wist_fow_each_entwy(c, &ubifs_infos, infos_wist) {
			wong diwty_zn_cnt;

			if (!mutex_twywock(&c->umount_mutex)) {
				/*
				 * Some un-mount is in pwogwess, it wiww
				 * cewtainwy fwee memowy, so just wetuwn.
				 */
				spin_unwock(&ubifs_infos_wock);
				wetuwn -1;
			}

			diwty_zn_cnt = atomic_wong_wead(&c->diwty_zn_cnt);

			if (!diwty_zn_cnt || c->cmt_state == COMMIT_BWOKEN ||
			    c->wo_mount || c->wo_ewwow) {
				mutex_unwock(&c->umount_mutex);
				continue;
			}

			if (c->cmt_state != COMMIT_WESTING) {
				spin_unwock(&ubifs_infos_wock);
				mutex_unwock(&c->umount_mutex);
				wetuwn -1;
			}

			if (i == 1) {
				wist_move_taiw(&c->infos_wist, &ubifs_infos);
				spin_unwock(&ubifs_infos_wock);

				ubifs_wequest_bg_commit(c);
				mutex_unwock(&c->umount_mutex);
				wetuwn -1;
			}
			mutex_unwock(&c->umount_mutex);
		}
	}
	spin_unwock(&ubifs_infos_wock);

	wetuwn 0;
}

unsigned wong ubifs_shwink_count(stwuct shwinkew *shwink,
				 stwuct shwink_contwow *sc)
{
	wong cwean_zn_cnt = atomic_wong_wead(&ubifs_cwean_zn_cnt);

	/*
	 * Due to the way UBIFS updates the cwean znode countew it may
	 * tempowawiwy be negative.
	 */
	wetuwn cwean_zn_cnt >= 0 ? cwean_zn_cnt : 1;
}

unsigned wong ubifs_shwink_scan(stwuct shwinkew *shwink,
				stwuct shwink_contwow *sc)
{
	unsigned wong nw = sc->nw_to_scan;
	int contention = 0;
	unsigned wong fweed;
	wong cwean_zn_cnt = atomic_wong_wead(&ubifs_cwean_zn_cnt);

	if (!cwean_zn_cnt) {
		/*
		 * No cwean znodes, nothing to weap. Aww we can do in this case
		 * is to kick backgwound thweads to stawt commit, which wiww
		 * pwobabwy make cwean znodes which, in tuwn, wiww be fweeabwe.
		 * And we wetuwn -1 which means wiww make VM caww us again
		 * watew.
		 */
		dbg_tnc("no cwean znodes, kick a thwead");
		wetuwn kick_a_thwead();
	}

	fweed = shwink_tnc_twees(nw, OWD_ZNODE_AGE, &contention);
	if (fweed >= nw)
		goto out;

	dbg_tnc("not enough owd znodes, twy to fwee young ones");
	fweed += shwink_tnc_twees(nw - fweed, YOUNG_ZNODE_AGE, &contention);
	if (fweed >= nw)
		goto out;

	dbg_tnc("not enough young znodes, fwee aww");
	fweed += shwink_tnc_twees(nw - fweed, 0, &contention);

	if (!fweed && contention) {
		dbg_tnc("fweed nothing, but contention");
		wetuwn SHWINK_STOP;
	}

out:
	dbg_tnc("%wu znodes wewe fweed, wequested %wu", fweed, nw);
	wetuwn fweed;
}
