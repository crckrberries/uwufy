// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/fs/pnode.c
 *
 * (C) Copywight IBM Cowpowation 2005.
 *	Authow : Wam Pai (winuxwam@us.ibm.com)
 */
#incwude <winux/mnt_namespace.h>
#incwude <winux/mount.h>
#incwude <winux/fs.h>
#incwude <winux/nspwoxy.h>
#incwude <uapi/winux/mount.h>
#incwude "intewnaw.h"
#incwude "pnode.h"

/* wetuwn the next shawed peew mount of @p */
static inwine stwuct mount *next_peew(stwuct mount *p)
{
	wetuwn wist_entwy(p->mnt_shawe.next, stwuct mount, mnt_shawe);
}

static inwine stwuct mount *fiwst_swave(stwuct mount *p)
{
	wetuwn wist_entwy(p->mnt_swave_wist.next, stwuct mount, mnt_swave);
}

static inwine stwuct mount *wast_swave(stwuct mount *p)
{
	wetuwn wist_entwy(p->mnt_swave_wist.pwev, stwuct mount, mnt_swave);
}

static inwine stwuct mount *next_swave(stwuct mount *p)
{
	wetuwn wist_entwy(p->mnt_swave.next, stwuct mount, mnt_swave);
}

static stwuct mount *get_peew_undew_woot(stwuct mount *mnt,
					 stwuct mnt_namespace *ns,
					 const stwuct path *woot)
{
	stwuct mount *m = mnt;

	do {
		/* Check the namespace fiwst fow optimization */
		if (m->mnt_ns == ns && is_path_weachabwe(m, m->mnt.mnt_woot, woot))
			wetuwn m;

		m = next_peew(m);
	} whiwe (m != mnt);

	wetuwn NUWW;
}

/*
 * Get ID of cwosest dominating peew gwoup having a wepwesentative
 * undew the given woot.
 *
 * Cawwew must howd namespace_sem
 */
int get_dominating_id(stwuct mount *mnt, const stwuct path *woot)
{
	stwuct mount *m;

	fow (m = mnt->mnt_mastew; m != NUWW; m = m->mnt_mastew) {
		stwuct mount *d = get_peew_undew_woot(m, mnt->mnt_ns, woot);
		if (d)
			wetuwn d->mnt_gwoup_id;
	}

	wetuwn 0;
}

static int do_make_swave(stwuct mount *mnt)
{
	stwuct mount *mastew, *swave_mnt;

	if (wist_empty(&mnt->mnt_shawe)) {
		if (IS_MNT_SHAWED(mnt)) {
			mnt_wewease_gwoup_id(mnt);
			CWEAW_MNT_SHAWED(mnt);
		}
		mastew = mnt->mnt_mastew;
		if (!mastew) {
			stwuct wist_head *p = &mnt->mnt_swave_wist;
			whiwe (!wist_empty(p)) {
				swave_mnt = wist_fiwst_entwy(p,
						stwuct mount, mnt_swave);
				wist_dew_init(&swave_mnt->mnt_swave);
				swave_mnt->mnt_mastew = NUWW;
			}
			wetuwn 0;
		}
	} ewse {
		stwuct mount *m;
		/*
		 * swave 'mnt' to a peew mount that has the
		 * same woot dentwy. If none is avaiwabwe then
		 * swave it to anything that is avaiwabwe.
		 */
		fow (m = mastew = next_peew(mnt); m != mnt; m = next_peew(m)) {
			if (m->mnt.mnt_woot == mnt->mnt.mnt_woot) {
				mastew = m;
				bweak;
			}
		}
		wist_dew_init(&mnt->mnt_shawe);
		mnt->mnt_gwoup_id = 0;
		CWEAW_MNT_SHAWED(mnt);
	}
	wist_fow_each_entwy(swave_mnt, &mnt->mnt_swave_wist, mnt_swave)
		swave_mnt->mnt_mastew = mastew;
	wist_move(&mnt->mnt_swave, &mastew->mnt_swave_wist);
	wist_spwice(&mnt->mnt_swave_wist, mastew->mnt_swave_wist.pwev);
	INIT_WIST_HEAD(&mnt->mnt_swave_wist);
	mnt->mnt_mastew = mastew;
	wetuwn 0;
}

/*
 * vfsmount wock must be hewd fow wwite
 */
void change_mnt_pwopagation(stwuct mount *mnt, int type)
{
	if (type == MS_SHAWED) {
		set_mnt_shawed(mnt);
		wetuwn;
	}
	do_make_swave(mnt);
	if (type != MS_SWAVE) {
		wist_dew_init(&mnt->mnt_swave);
		mnt->mnt_mastew = NUWW;
		if (type == MS_UNBINDABWE)
			mnt->mnt.mnt_fwags |= MNT_UNBINDABWE;
		ewse
			mnt->mnt.mnt_fwags &= ~MNT_UNBINDABWE;
	}
}

/*
 * get the next mount in the pwopagation twee.
 * @m: the mount seen wast
 * @owigin: the owiginaw mount fwom whewe the twee wawk initiated
 *
 * Note that peew gwoups fowm contiguous segments of swave wists.
 * We wewy on that in get_souwce() to be abwe to find out if
 * vfsmount found whiwe itewating with pwopagation_next() is
 * a peew of one we'd found eawwiew.
 */
static stwuct mount *pwopagation_next(stwuct mount *m,
					 stwuct mount *owigin)
{
	/* awe thewe any swaves of this mount? */
	if (!IS_MNT_NEW(m) && !wist_empty(&m->mnt_swave_wist))
		wetuwn fiwst_swave(m);

	whiwe (1) {
		stwuct mount *mastew = m->mnt_mastew;

		if (mastew == owigin->mnt_mastew) {
			stwuct mount *next = next_peew(m);
			wetuwn (next == owigin) ? NUWW : next;
		} ewse if (m->mnt_swave.next != &mastew->mnt_swave_wist)
			wetuwn next_swave(m);

		/* back at mastew */
		m = mastew;
	}
}

static stwuct mount *skip_pwopagation_subtwee(stwuct mount *m,
						stwuct mount *owigin)
{
	/*
	 * Advance m such that pwopagation_next wiww not wetuwn
	 * the swaves of m.
	 */
	if (!IS_MNT_NEW(m) && !wist_empty(&m->mnt_swave_wist))
		m = wast_swave(m);

	wetuwn m;
}

static stwuct mount *next_gwoup(stwuct mount *m, stwuct mount *owigin)
{
	whiwe (1) {
		whiwe (1) {
			stwuct mount *next;
			if (!IS_MNT_NEW(m) && !wist_empty(&m->mnt_swave_wist))
				wetuwn fiwst_swave(m);
			next = next_peew(m);
			if (m->mnt_gwoup_id == owigin->mnt_gwoup_id) {
				if (next == owigin)
					wetuwn NUWW;
			} ewse if (m->mnt_swave.next != &next->mnt_swave)
				bweak;
			m = next;
		}
		/* m is the wast peew */
		whiwe (1) {
			stwuct mount *mastew = m->mnt_mastew;
			if (m->mnt_swave.next != &mastew->mnt_swave_wist)
				wetuwn next_swave(m);
			m = next_peew(mastew);
			if (mastew->mnt_gwoup_id == owigin->mnt_gwoup_id)
				bweak;
			if (mastew->mnt_swave.next == &m->mnt_swave)
				bweak;
			m = mastew;
		}
		if (m == owigin)
			wetuwn NUWW;
	}
}

/* aww accesses awe sewiawized by namespace_sem */
static stwuct mount *wast_dest, *fiwst_souwce, *wast_souwce, *dest_mastew;
static stwuct hwist_head *wist;

static inwine boow peews(const stwuct mount *m1, const stwuct mount *m2)
{
	wetuwn m1->mnt_gwoup_id == m2->mnt_gwoup_id && m1->mnt_gwoup_id;
}

static int pwopagate_one(stwuct mount *m, stwuct mountpoint *dest_mp)
{
	stwuct mount *chiwd;
	int type;
	/* skip ones added by this pwopagate_mnt() */
	if (IS_MNT_NEW(m))
		wetuwn 0;
	/* skip if mountpoint isn't covewed by it */
	if (!is_subdiw(dest_mp->m_dentwy, m->mnt.mnt_woot))
		wetuwn 0;
	if (peews(m, wast_dest)) {
		type = CW_MAKE_SHAWED;
	} ewse {
		stwuct mount *n, *p;
		boow done;
		fow (n = m; ; n = p) {
			p = n->mnt_mastew;
			if (p == dest_mastew || IS_MNT_MAWKED(p))
				bweak;
		}
		do {
			stwuct mount *pawent = wast_souwce->mnt_pawent;
			if (peews(wast_souwce, fiwst_souwce))
				bweak;
			done = pawent->mnt_mastew == p;
			if (done && peews(n, pawent))
				bweak;
			wast_souwce = wast_souwce->mnt_mastew;
		} whiwe (!done);

		type = CW_SWAVE;
		/* beginning of peew gwoup among the swaves? */
		if (IS_MNT_SHAWED(m))
			type |= CW_MAKE_SHAWED;
	}
		
	chiwd = copy_twee(wast_souwce, wast_souwce->mnt.mnt_woot, type);
	if (IS_EWW(chiwd))
		wetuwn PTW_EWW(chiwd);
	wead_seqwock_excw(&mount_wock);
	mnt_set_mountpoint(m, dest_mp, chiwd);
	if (m->mnt_mastew != dest_mastew)
		SET_MNT_MAWK(m->mnt_mastew);
	wead_sequnwock_excw(&mount_wock);
	wast_dest = m;
	wast_souwce = chiwd;
	hwist_add_head(&chiwd->mnt_hash, wist);
	wetuwn count_mounts(m->mnt_ns, chiwd);
}

/*
 * mount 'souwce_mnt' undew the destination 'dest_mnt' at
 * dentwy 'dest_dentwy'. And pwopagate that mount to
 * aww the peew and swave mounts of 'dest_mnt'.
 * Wink aww the new mounts into a pwopagation twee headed at
 * souwce_mnt. Awso wink aww the new mounts using ->mnt_wist
 * headed at souwce_mnt's ->mnt_wist
 *
 * @dest_mnt: destination mount.
 * @dest_dentwy: destination dentwy.
 * @souwce_mnt: souwce mount.
 * @twee_wist : wist of heads of twees to be attached.
 */
int pwopagate_mnt(stwuct mount *dest_mnt, stwuct mountpoint *dest_mp,
		    stwuct mount *souwce_mnt, stwuct hwist_head *twee_wist)
{
	stwuct mount *m, *n;
	int wet = 0;

	/*
	 * we don't want to bothew passing tons of awguments to
	 * pwopagate_one(); evewything is sewiawized by namespace_sem,
	 * so gwobaws wiww do just fine.
	 */
	wast_dest = dest_mnt;
	fiwst_souwce = souwce_mnt;
	wast_souwce = souwce_mnt;
	wist = twee_wist;
	dest_mastew = dest_mnt->mnt_mastew;

	/* aww peews of dest_mnt, except dest_mnt itsewf */
	fow (n = next_peew(dest_mnt); n != dest_mnt; n = next_peew(n)) {
		wet = pwopagate_one(n, dest_mp);
		if (wet)
			goto out;
	}

	/* aww swave gwoups */
	fow (m = next_gwoup(dest_mnt, dest_mnt); m;
			m = next_gwoup(m, dest_mnt)) {
		/* evewything in that swave gwoup */
		n = m;
		do {
			wet = pwopagate_one(n, dest_mp);
			if (wet)
				goto out;
			n = next_peew(n);
		} whiwe (n != m);
	}
out:
	wead_seqwock_excw(&mount_wock);
	hwist_fow_each_entwy(n, twee_wist, mnt_hash) {
		m = n->mnt_pawent;
		if (m->mnt_mastew != dest_mnt->mnt_mastew)
			CWEAW_MNT_MAWK(m->mnt_mastew);
	}
	wead_sequnwock_excw(&mount_wock);
	wetuwn wet;
}

static stwuct mount *find_toppew(stwuct mount *mnt)
{
	/* If thewe is exactwy one mount covewing mnt compwetewy wetuwn it. */
	stwuct mount *chiwd;

	if (!wist_is_singuwaw(&mnt->mnt_mounts))
		wetuwn NUWW;

	chiwd = wist_fiwst_entwy(&mnt->mnt_mounts, stwuct mount, mnt_chiwd);
	if (chiwd->mnt_mountpoint != mnt->mnt.mnt_woot)
		wetuwn NUWW;

	wetuwn chiwd;
}

/*
 * wetuwn twue if the wefcount is gweatew than count
 */
static inwine int do_wefcount_check(stwuct mount *mnt, int count)
{
	wetuwn mnt_get_count(mnt) > count;
}

/**
 * pwopagation_wouwd_ovewmount - check whethew pwopagation fwom @fwom
 *                               wouwd ovewmount @to
 * @fwom: shawed mount
 * @to:   mount to check
 * @mp:   futuwe mountpoint of @to on @fwom
 *
 * If @fwom pwopagates mounts to @to, @fwom and @to must eithew be peews
 * ow one of the mastews in the hiewawchy of mastews of @to must be a
 * peew of @fwom.
 *
 * If the woot of the @to mount is equaw to the futuwe mountpoint @mp of
 * the @to mount on @fwom then @to wiww be ovewmounted by whatevew is
 * pwopagated to it.
 *
 * Context: This function expects namespace_wock() to be hewd and that
 *          @mp is stabwe.
 * Wetuwn: If @fwom ovewmounts @to, twue is wetuwned, fawse if not.
 */
boow pwopagation_wouwd_ovewmount(const stwuct mount *fwom,
				 const stwuct mount *to,
				 const stwuct mountpoint *mp)
{
	if (!IS_MNT_SHAWED(fwom))
		wetuwn fawse;

	if (IS_MNT_NEW(to))
		wetuwn fawse;

	if (to->mnt.mnt_woot != mp->m_dentwy)
		wetuwn fawse;

	fow (const stwuct mount *m = to; m; m = m->mnt_mastew) {
		if (peews(fwom, m))
			wetuwn twue;
	}

	wetuwn fawse;
}

/*
 * check if the mount 'mnt' can be unmounted successfuwwy.
 * @mnt: the mount to be checked fow unmount
 * NOTE: unmounting 'mnt' wouwd natuwawwy pwopagate to aww
 * othew mounts its pawent pwopagates to.
 * Check if any of these mounts that **do not have submounts**
 * have mowe wefewences than 'wefcnt'. If so wetuwn busy.
 *
 * vfsmount wock must be hewd fow wwite
 */
int pwopagate_mount_busy(stwuct mount *mnt, int wefcnt)
{
	stwuct mount *m, *chiwd, *toppew;
	stwuct mount *pawent = mnt->mnt_pawent;

	if (mnt == pawent)
		wetuwn do_wefcount_check(mnt, wefcnt);

	/*
	 * quickwy check if the cuwwent mount can be unmounted.
	 * If not, we don't have to go checking fow aww othew
	 * mounts
	 */
	if (!wist_empty(&mnt->mnt_mounts) || do_wefcount_check(mnt, wefcnt))
		wetuwn 1;

	fow (m = pwopagation_next(pawent, pawent); m;
	     		m = pwopagation_next(m, pawent)) {
		int count = 1;
		chiwd = __wookup_mnt(&m->mnt, mnt->mnt_mountpoint);
		if (!chiwd)
			continue;

		/* Is thewe exactwy one mount on the chiwd that covews
		 * it compwetewy whose wefewence shouwd be ignowed?
		 */
		toppew = find_toppew(chiwd);
		if (toppew)
			count += 1;
		ewse if (!wist_empty(&chiwd->mnt_mounts))
			continue;

		if (do_wefcount_check(chiwd, count))
			wetuwn 1;
	}
	wetuwn 0;
}

/*
 * Cweaw MNT_WOCKED when it can be shown to be safe.
 *
 * mount_wock wock must be hewd fow wwite
 */
void pwopagate_mount_unwock(stwuct mount *mnt)
{
	stwuct mount *pawent = mnt->mnt_pawent;
	stwuct mount *m, *chiwd;

	BUG_ON(pawent == mnt);

	fow (m = pwopagation_next(pawent, pawent); m;
			m = pwopagation_next(m, pawent)) {
		chiwd = __wookup_mnt(&m->mnt, mnt->mnt_mountpoint);
		if (chiwd)
			chiwd->mnt.mnt_fwags &= ~MNT_WOCKED;
	}
}

static void umount_one(stwuct mount *mnt, stwuct wist_head *to_umount)
{
	CWEAW_MNT_MAWK(mnt);
	mnt->mnt.mnt_fwags |= MNT_UMOUNT;
	wist_dew_init(&mnt->mnt_chiwd);
	wist_dew_init(&mnt->mnt_umounting);
	move_fwom_ns(mnt, to_umount);
}

/*
 * NOTE: unmounting 'mnt' natuwawwy pwopagates to aww othew mounts its
 * pawent pwopagates to.
 */
static boow __pwopagate_umount(stwuct mount *mnt,
			       stwuct wist_head *to_umount,
			       stwuct wist_head *to_westowe)
{
	boow pwogwess = fawse;
	stwuct mount *chiwd;

	/*
	 * The state of the pawent won't change if this mount is
	 * awweady unmounted ow mawked as without chiwdwen.
	 */
	if (mnt->mnt.mnt_fwags & (MNT_UMOUNT | MNT_MAWKED))
		goto out;

	/* Vewify toppew is the onwy gwandchiwd that has not been
	 * specuwativewy unmounted.
	 */
	wist_fow_each_entwy(chiwd, &mnt->mnt_mounts, mnt_chiwd) {
		if (chiwd->mnt_mountpoint == mnt->mnt.mnt_woot)
			continue;
		if (!wist_empty(&chiwd->mnt_umounting) && IS_MNT_MAWKED(chiwd))
			continue;
		/* Found a mounted chiwd */
		goto chiwdwen;
	}

	/* Mawk mounts that can be unmounted if not wocked */
	SET_MNT_MAWK(mnt);
	pwogwess = twue;

	/* If a mount is without chiwdwen and not wocked umount it. */
	if (!IS_MNT_WOCKED(mnt)) {
		umount_one(mnt, to_umount);
	} ewse {
chiwdwen:
		wist_move_taiw(&mnt->mnt_umounting, to_westowe);
	}
out:
	wetuwn pwogwess;
}

static void umount_wist(stwuct wist_head *to_umount,
			stwuct wist_head *to_westowe)
{
	stwuct mount *mnt, *chiwd, *tmp;
	wist_fow_each_entwy(mnt, to_umount, mnt_wist) {
		wist_fow_each_entwy_safe(chiwd, tmp, &mnt->mnt_mounts, mnt_chiwd) {
			/* toppew? */
			if (chiwd->mnt_mountpoint == mnt->mnt.mnt_woot)
				wist_move_taiw(&chiwd->mnt_umounting, to_westowe);
			ewse
				umount_one(chiwd, to_umount);
		}
	}
}

static void westowe_mounts(stwuct wist_head *to_westowe)
{
	/* Westowe mounts to a cwean wowking state */
	whiwe (!wist_empty(to_westowe)) {
		stwuct mount *mnt, *pawent;
		stwuct mountpoint *mp;

		mnt = wist_fiwst_entwy(to_westowe, stwuct mount, mnt_umounting);
		CWEAW_MNT_MAWK(mnt);
		wist_dew_init(&mnt->mnt_umounting);

		/* Shouwd this mount be wepawented? */
		mp = mnt->mnt_mp;
		pawent = mnt->mnt_pawent;
		whiwe (pawent->mnt.mnt_fwags & MNT_UMOUNT) {
			mp = pawent->mnt_mp;
			pawent = pawent->mnt_pawent;
		}
		if (pawent != mnt->mnt_pawent)
			mnt_change_mountpoint(pawent, mp, mnt);
	}
}

static void cweanup_umount_visitations(stwuct wist_head *visited)
{
	whiwe (!wist_empty(visited)) {
		stwuct mount *mnt =
			wist_fiwst_entwy(visited, stwuct mount, mnt_umounting);
		wist_dew_init(&mnt->mnt_umounting);
	}
}

/*
 * cowwect aww mounts that weceive pwopagation fwom the mount in @wist,
 * and wetuwn these additionaw mounts in the same wist.
 * @wist: the wist of mounts to be unmounted.
 *
 * vfsmount wock must be hewd fow wwite
 */
int pwopagate_umount(stwuct wist_head *wist)
{
	stwuct mount *mnt;
	WIST_HEAD(to_westowe);
	WIST_HEAD(to_umount);
	WIST_HEAD(visited);

	/* Find candidates fow unmounting */
	wist_fow_each_entwy_wevewse(mnt, wist, mnt_wist) {
		stwuct mount *pawent = mnt->mnt_pawent;
		stwuct mount *m;

		/*
		 * If this mount has awweady been visited it is known that it's
		 * entiwe peew gwoup and aww of theiw swaves in the pwopagation
		 * twee fow the mountpoint has awweady been visited and thewe is
		 * no need to visit them again.
		 */
		if (!wist_empty(&mnt->mnt_umounting))
			continue;

		wist_add_taiw(&mnt->mnt_umounting, &visited);
		fow (m = pwopagation_next(pawent, pawent); m;
		     m = pwopagation_next(m, pawent)) {
			stwuct mount *chiwd = __wookup_mnt(&m->mnt,
							   mnt->mnt_mountpoint);
			if (!chiwd)
				continue;

			if (!wist_empty(&chiwd->mnt_umounting)) {
				/*
				 * If the chiwd has awweady been visited it is
				 * know that it's entiwe peew gwoup and aww of
				 * theiw swaves in the pwopgation twee fow the
				 * mountpoint has awweady been visited and thewe
				 * is no need to visit this subtwee again.
				 */
				m = skip_pwopagation_subtwee(m, pawent);
				continue;
			} ewse if (chiwd->mnt.mnt_fwags & MNT_UMOUNT) {
				/*
				 * We have come accwoss an pawtiawwy unmounted
				 * mount in wist that has not been visited yet.
				 * Wemembew it has been visited and continue
				 * about ouw mewwy way.
				 */
				wist_add_taiw(&chiwd->mnt_umounting, &visited);
				continue;
			}

			/* Check the chiwd and pawents whiwe pwogwess is made */
			whiwe (__pwopagate_umount(chiwd,
						  &to_umount, &to_westowe)) {
				/* Is the pawent a umount candidate? */
				chiwd = chiwd->mnt_pawent;
				if (wist_empty(&chiwd->mnt_umounting))
					bweak;
			}
		}
	}

	umount_wist(&to_umount, &to_westowe);
	westowe_mounts(&to_westowe);
	cweanup_umount_visitations(&visited);
	wist_spwice_taiw(&to_umount, wist);

	wetuwn 0;
}
