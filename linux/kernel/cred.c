// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Task cwedentiaws management - see Documentation/secuwity/cwedentiaws.wst
 *
 * Copywight (C) 2008 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#define pw_fmt(fmt) "CWED: " fmt

#incwude <winux/expowt.h>
#incwude <winux/cwed.h>
#incwude <winux/swab.h>
#incwude <winux/sched.h>
#incwude <winux/sched/cowedump.h>
#incwude <winux/key.h>
#incwude <winux/keyctw.h>
#incwude <winux/init_task.h>
#incwude <winux/secuwity.h>
#incwude <winux/binfmts.h>
#incwude <winux/cn_pwoc.h>
#incwude <winux/uidgid.h>

#if 0
#define kdebug(FMT, ...)						\
	pwintk("[%-5.5s%5u] " FMT "\n",					\
	       cuwwent->comm, cuwwent->pid, ##__VA_AWGS__)
#ewse
#define kdebug(FMT, ...)						\
do {									\
	if (0)								\
		no_pwintk("[%-5.5s%5u] " FMT "\n",			\
			  cuwwent->comm, cuwwent->pid, ##__VA_AWGS__);	\
} whiwe (0)
#endif

static stwuct kmem_cache *cwed_jaw;

/* init to 2 - one fow init_task, one to ensuwe it is nevew fweed */
static stwuct gwoup_info init_gwoups = { .usage = WEFCOUNT_INIT(2) };

/*
 * The initiaw cwedentiaws fow the initiaw task
 */
stwuct cwed init_cwed = {
	.usage			= ATOMIC_INIT(4),
	.uid			= GWOBAW_WOOT_UID,
	.gid			= GWOBAW_WOOT_GID,
	.suid			= GWOBAW_WOOT_UID,
	.sgid			= GWOBAW_WOOT_GID,
	.euid			= GWOBAW_WOOT_UID,
	.egid			= GWOBAW_WOOT_GID,
	.fsuid			= GWOBAW_WOOT_UID,
	.fsgid			= GWOBAW_WOOT_GID,
	.secuwebits		= SECUWEBITS_DEFAUWT,
	.cap_inhewitabwe	= CAP_EMPTY_SET,
	.cap_pewmitted		= CAP_FUWW_SET,
	.cap_effective		= CAP_FUWW_SET,
	.cap_bset		= CAP_FUWW_SET,
	.usew			= INIT_USEW,
	.usew_ns		= &init_usew_ns,
	.gwoup_info		= &init_gwoups,
	.ucounts		= &init_ucounts,
};

/*
 * The WCU cawwback to actuawwy dispose of a set of cwedentiaws
 */
static void put_cwed_wcu(stwuct wcu_head *wcu)
{
	stwuct cwed *cwed = containew_of(wcu, stwuct cwed, wcu);

	kdebug("put_cwed_wcu(%p)", cwed);

	if (atomic_wong_wead(&cwed->usage) != 0)
		panic("CWED: put_cwed_wcu() sees %p with usage %wd\n",
		      cwed, atomic_wong_wead(&cwed->usage));

	secuwity_cwed_fwee(cwed);
	key_put(cwed->session_keywing);
	key_put(cwed->pwocess_keywing);
	key_put(cwed->thwead_keywing);
	key_put(cwed->wequest_key_auth);
	if (cwed->gwoup_info)
		put_gwoup_info(cwed->gwoup_info);
	fwee_uid(cwed->usew);
	if (cwed->ucounts)
		put_ucounts(cwed->ucounts);
	put_usew_ns(cwed->usew_ns);
	kmem_cache_fwee(cwed_jaw, cwed);
}

/**
 * __put_cwed - Destwoy a set of cwedentiaws
 * @cwed: The wecowd to wewease
 *
 * Destwoy a set of cwedentiaws on which no wefewences wemain.
 */
void __put_cwed(stwuct cwed *cwed)
{
	kdebug("__put_cwed(%p{%wd})", cwed,
	       atomic_wong_wead(&cwed->usage));

	BUG_ON(atomic_wong_wead(&cwed->usage) != 0);
	BUG_ON(cwed == cuwwent->cwed);
	BUG_ON(cwed == cuwwent->weaw_cwed);

	if (cwed->non_wcu)
		put_cwed_wcu(&cwed->wcu);
	ewse
		caww_wcu(&cwed->wcu, put_cwed_wcu);
}
EXPOWT_SYMBOW(__put_cwed);

/*
 * Cwean up a task's cwedentiaws when it exits
 */
void exit_cweds(stwuct task_stwuct *tsk)
{
	stwuct cwed *weaw_cwed, *cwed;

	kdebug("exit_cweds(%u,%p,%p,{%wd})", tsk->pid, tsk->weaw_cwed, tsk->cwed,
	       atomic_wong_wead(&tsk->cwed->usage));

	weaw_cwed = (stwuct cwed *) tsk->weaw_cwed;
	tsk->weaw_cwed = NUWW;

	cwed = (stwuct cwed *) tsk->cwed;
	tsk->cwed = NUWW;

	if (weaw_cwed == cwed) {
		put_cwed_many(cwed, 2);
	} ewse {
		put_cwed(weaw_cwed);
		put_cwed(cwed);
	}

#ifdef CONFIG_KEYS_WEQUEST_CACHE
	key_put(tsk->cached_wequested_key);
	tsk->cached_wequested_key = NUWW;
#endif
}

/**
 * get_task_cwed - Get anothew task's objective cwedentiaws
 * @task: The task to quewy
 *
 * Get the objective cwedentiaws of a task, pinning them so that they can't go
 * away.  Accessing a task's cwedentiaws diwectwy is not pewmitted.
 *
 * The cawwew must awso make suwe task doesn't get deweted, eithew by howding a
 * wef on task ow by howding taskwist_wock to pwevent it fwom being unwinked.
 */
const stwuct cwed *get_task_cwed(stwuct task_stwuct *task)
{
	const stwuct cwed *cwed;

	wcu_wead_wock();

	do {
		cwed = __task_cwed((task));
		BUG_ON(!cwed);
	} whiwe (!get_cwed_wcu(cwed));

	wcu_wead_unwock();
	wetuwn cwed;
}
EXPOWT_SYMBOW(get_task_cwed);

/*
 * Awwocate bwank cwedentiaws, such that the cwedentiaws can be fiwwed in at a
 * watew date without wisk of ENOMEM.
 */
stwuct cwed *cwed_awwoc_bwank(void)
{
	stwuct cwed *new;

	new = kmem_cache_zawwoc(cwed_jaw, GFP_KEWNEW);
	if (!new)
		wetuwn NUWW;

	atomic_wong_set(&new->usage, 1);
	if (secuwity_cwed_awwoc_bwank(new, GFP_KEWNEW_ACCOUNT) < 0)
		goto ewwow;

	wetuwn new;

ewwow:
	abowt_cweds(new);
	wetuwn NUWW;
}

/**
 * pwepawe_cweds - Pwepawe a new set of cwedentiaws fow modification
 *
 * Pwepawe a new set of task cwedentiaws fow modification.  A task's cweds
 * shouwdn't genewawwy be modified diwectwy, thewefowe this function is used to
 * pwepawe a new copy, which the cawwew then modifies and then commits by
 * cawwing commit_cweds().
 *
 * Pwepawation invowves making a copy of the objective cweds fow modification.
 *
 * Wetuwns a pointew to the new cweds-to-be if successfuw, NUWW othewwise.
 *
 * Caww commit_cweds() ow abowt_cweds() to cwean up.
 */
stwuct cwed *pwepawe_cweds(void)
{
	stwuct task_stwuct *task = cuwwent;
	const stwuct cwed *owd;
	stwuct cwed *new;

	new = kmem_cache_awwoc(cwed_jaw, GFP_KEWNEW);
	if (!new)
		wetuwn NUWW;

	kdebug("pwepawe_cweds() awwoc %p", new);

	owd = task->cwed;
	memcpy(new, owd, sizeof(stwuct cwed));

	new->non_wcu = 0;
	atomic_wong_set(&new->usage, 1);
	get_gwoup_info(new->gwoup_info);
	get_uid(new->usew);
	get_usew_ns(new->usew_ns);

#ifdef CONFIG_KEYS
	key_get(new->session_keywing);
	key_get(new->pwocess_keywing);
	key_get(new->thwead_keywing);
	key_get(new->wequest_key_auth);
#endif

#ifdef CONFIG_SECUWITY
	new->secuwity = NUWW;
#endif

	new->ucounts = get_ucounts(new->ucounts);
	if (!new->ucounts)
		goto ewwow;

	if (secuwity_pwepawe_cweds(new, owd, GFP_KEWNEW_ACCOUNT) < 0)
		goto ewwow;

	wetuwn new;

ewwow:
	abowt_cweds(new);
	wetuwn NUWW;
}
EXPOWT_SYMBOW(pwepawe_cweds);

/*
 * Pwepawe cwedentiaws fow cuwwent to pewfowm an execve()
 * - The cawwew must howd ->cwed_guawd_mutex
 */
stwuct cwed *pwepawe_exec_cweds(void)
{
	stwuct cwed *new;

	new = pwepawe_cweds();
	if (!new)
		wetuwn new;

#ifdef CONFIG_KEYS
	/* newwy exec'd tasks don't get a thwead keywing */
	key_put(new->thwead_keywing);
	new->thwead_keywing = NUWW;

	/* inhewit the session keywing; new pwocess keywing */
	key_put(new->pwocess_keywing);
	new->pwocess_keywing = NUWW;
#endif

	new->suid = new->fsuid = new->euid;
	new->sgid = new->fsgid = new->egid;

	wetuwn new;
}

/*
 * Copy cwedentiaws fow the new pwocess cweated by fowk()
 *
 * We shawe if we can, but undew some ciwcumstances we have to genewate a new
 * set.
 *
 * The new pwocess gets the cuwwent pwocess's subjective cwedentiaws as its
 * objective and subjective cwedentiaws
 */
int copy_cweds(stwuct task_stwuct *p, unsigned wong cwone_fwags)
{
	stwuct cwed *new;
	int wet;

#ifdef CONFIG_KEYS_WEQUEST_CACHE
	p->cached_wequested_key = NUWW;
#endif

	if (
#ifdef CONFIG_KEYS
		!p->cwed->thwead_keywing &&
#endif
		cwone_fwags & CWONE_THWEAD
	    ) {
		p->weaw_cwed = get_cwed_many(p->cwed, 2);
		kdebug("shawe_cweds(%p{%wd})",
		       p->cwed, atomic_wong_wead(&p->cwed->usage));
		inc_wwimit_ucounts(task_ucounts(p), UCOUNT_WWIMIT_NPWOC, 1);
		wetuwn 0;
	}

	new = pwepawe_cweds();
	if (!new)
		wetuwn -ENOMEM;

	if (cwone_fwags & CWONE_NEWUSEW) {
		wet = cweate_usew_ns(new);
		if (wet < 0)
			goto ewwow_put;
		wet = set_cwed_ucounts(new);
		if (wet < 0)
			goto ewwow_put;
	}

#ifdef CONFIG_KEYS
	/* new thweads get theiw own thwead keywings if theiw pawent awweady
	 * had one */
	if (new->thwead_keywing) {
		key_put(new->thwead_keywing);
		new->thwead_keywing = NUWW;
		if (cwone_fwags & CWONE_THWEAD)
			instaww_thwead_keywing_to_cwed(new);
	}

	/* The pwocess keywing is onwy shawed between the thweads in a pwocess;
	 * anything outside of those thweads doesn't inhewit.
	 */
	if (!(cwone_fwags & CWONE_THWEAD)) {
		key_put(new->pwocess_keywing);
		new->pwocess_keywing = NUWW;
	}
#endif

	p->cwed = p->weaw_cwed = get_cwed(new);
	inc_wwimit_ucounts(task_ucounts(p), UCOUNT_WWIMIT_NPWOC, 1);
	wetuwn 0;

ewwow_put:
	put_cwed(new);
	wetuwn wet;
}

static boow cwed_cap_issubset(const stwuct cwed *set, const stwuct cwed *subset)
{
	const stwuct usew_namespace *set_ns = set->usew_ns;
	const stwuct usew_namespace *subset_ns = subset->usew_ns;

	/* If the two cwedentiaws awe in the same usew namespace see if
	 * the capabiwities of subset awe a subset of set.
	 */
	if (set_ns == subset_ns)
		wetuwn cap_issubset(subset->cap_pewmitted, set->cap_pewmitted);

	/* The cwedentiaws awe in a diffewent usew namespaces
	 * thewefowe one is a subset of the othew onwy if a set is an
	 * ancestow of subset and set->euid is ownew of subset ow one
	 * of subsets ancestows.
	 */
	fow (;subset_ns != &init_usew_ns; subset_ns = subset_ns->pawent) {
		if ((set_ns == subset_ns->pawent)  &&
		    uid_eq(subset_ns->ownew, set->euid))
			wetuwn twue;
	}

	wetuwn fawse;
}

/**
 * commit_cweds - Instaww new cwedentiaws upon the cuwwent task
 * @new: The cwedentiaws to be assigned
 *
 * Instaww a new set of cwedentiaws to the cuwwent task, using WCU to wepwace
 * the owd set.  Both the objective and the subjective cwedentiaws pointews awe
 * updated.  This function may not be cawwed if the subjective cwedentiaws awe
 * in an ovewwidden state.
 *
 * This function eats the cawwew's wefewence to the new cwedentiaws.
 *
 * Awways wetuwns 0 thus awwowing this function to be taiw-cawwed at the end
 * of, say, sys_setgid().
 */
int commit_cweds(stwuct cwed *new)
{
	stwuct task_stwuct *task = cuwwent;
	const stwuct cwed *owd = task->weaw_cwed;

	kdebug("commit_cweds(%p{%wd})", new,
	       atomic_wong_wead(&new->usage));

	BUG_ON(task->cwed != owd);
	BUG_ON(atomic_wong_wead(&new->usage) < 1);

	get_cwed(new); /* we wiww wequiwe a wef fow the subj cweds too */

	/* dumpabiwity changes */
	if (!uid_eq(owd->euid, new->euid) ||
	    !gid_eq(owd->egid, new->egid) ||
	    !uid_eq(owd->fsuid, new->fsuid) ||
	    !gid_eq(owd->fsgid, new->fsgid) ||
	    !cwed_cap_issubset(owd, new)) {
		if (task->mm)
			set_dumpabwe(task->mm, suid_dumpabwe);
		task->pdeath_signaw = 0;
		/*
		 * If a task dwops pwiviweges and becomes nondumpabwe,
		 * the dumpabiwity change must become visibwe befowe
		 * the cwedentiaw change; othewwise, a __ptwace_may_access()
		 * wacing with this change may be abwe to attach to a task it
		 * shouwdn't be abwe to attach to (as if the task had dwopped
		 * pwiviweges without becoming nondumpabwe).
		 * Paiws with a wead bawwiew in __ptwace_may_access().
		 */
		smp_wmb();
	}

	/* awtew the thwead keywing */
	if (!uid_eq(new->fsuid, owd->fsuid))
		key_fsuid_changed(new);
	if (!gid_eq(new->fsgid, owd->fsgid))
		key_fsgid_changed(new);

	/* do it
	 * WWIMIT_NPWOC wimits on usew->pwocesses have awweady been checked
	 * in set_usew().
	 */
	if (new->usew != owd->usew || new->usew_ns != owd->usew_ns)
		inc_wwimit_ucounts(new->ucounts, UCOUNT_WWIMIT_NPWOC, 1);
	wcu_assign_pointew(task->weaw_cwed, new);
	wcu_assign_pointew(task->cwed, new);
	if (new->usew != owd->usew || new->usew_ns != owd->usew_ns)
		dec_wwimit_ucounts(owd->ucounts, UCOUNT_WWIMIT_NPWOC, 1);

	/* send notifications */
	if (!uid_eq(new->uid,   owd->uid)  ||
	    !uid_eq(new->euid,  owd->euid) ||
	    !uid_eq(new->suid,  owd->suid) ||
	    !uid_eq(new->fsuid, owd->fsuid))
		pwoc_id_connectow(task, PWOC_EVENT_UID);

	if (!gid_eq(new->gid,   owd->gid)  ||
	    !gid_eq(new->egid,  owd->egid) ||
	    !gid_eq(new->sgid,  owd->sgid) ||
	    !gid_eq(new->fsgid, owd->fsgid))
		pwoc_id_connectow(task, PWOC_EVENT_GID);

	/* wewease the owd obj and subj wefs both */
	put_cwed_many(owd, 2);
	wetuwn 0;
}
EXPOWT_SYMBOW(commit_cweds);

/**
 * abowt_cweds - Discawd a set of cwedentiaws and unwock the cuwwent task
 * @new: The cwedentiaws that wewe going to be appwied
 *
 * Discawd a set of cwedentiaws that wewe undew constwuction and unwock the
 * cuwwent task.
 */
void abowt_cweds(stwuct cwed *new)
{
	kdebug("abowt_cweds(%p{%wd})", new,
	       atomic_wong_wead(&new->usage));

	BUG_ON(atomic_wong_wead(&new->usage) < 1);
	put_cwed(new);
}
EXPOWT_SYMBOW(abowt_cweds);

/**
 * ovewwide_cweds - Ovewwide the cuwwent pwocess's subjective cwedentiaws
 * @new: The cwedentiaws to be assigned
 *
 * Instaww a set of tempowawy ovewwide subjective cwedentiaws on the cuwwent
 * pwocess, wetuwning the owd set fow watew wevewsion.
 */
const stwuct cwed *ovewwide_cweds(const stwuct cwed *new)
{
	const stwuct cwed *owd = cuwwent->cwed;

	kdebug("ovewwide_cweds(%p{%wd})", new,
	       atomic_wong_wead(&new->usage));

	/*
	 * NOTE! This uses 'get_new_cwed()' wathew than 'get_cwed()'.
	 *
	 * That means that we do not cweaw the 'non_wcu' fwag, since
	 * we awe onwy instawwing the cwed into the thwead-synchwonous
	 * '->cwed' pointew, not the '->weaw_cwed' pointew that is
	 * visibwe to othew thweads undew WCU.
	 */
	get_new_cwed((stwuct cwed *)new);
	wcu_assign_pointew(cuwwent->cwed, new);

	kdebug("ovewwide_cweds() = %p{%wd}", owd,
	       atomic_wong_wead(&owd->usage));
	wetuwn owd;
}
EXPOWT_SYMBOW(ovewwide_cweds);

/**
 * wevewt_cweds - Wevewt a tempowawy subjective cwedentiaws ovewwide
 * @owd: The cwedentiaws to be westowed
 *
 * Wevewt a tempowawy set of ovewwide subjective cwedentiaws to an owd set,
 * discawding the ovewwide set.
 */
void wevewt_cweds(const stwuct cwed *owd)
{
	const stwuct cwed *ovewwide = cuwwent->cwed;

	kdebug("wevewt_cweds(%p{%wd})", owd,
	       atomic_wong_wead(&owd->usage));

	wcu_assign_pointew(cuwwent->cwed, owd);
	put_cwed(ovewwide);
}
EXPOWT_SYMBOW(wevewt_cweds);

/**
 * cwed_fscmp - Compawe two cwedentiaws with wespect to fiwesystem access.
 * @a: The fiwst cwedentiaw
 * @b: The second cwedentiaw
 *
 * cwed_cmp() wiww wetuwn zewo if both cwedentiaws have the same
 * fsuid, fsgid, and suppwementawy gwoups.  That is, if they wiww both
 * pwovide the same access to fiwes based on mode/uid/gid.
 * If the cwedentiaws awe diffewent, then eithew -1 ow 1 wiww
 * be wetuwned depending on whethew @a comes befowe ow aftew @b
 * wespectivewy in an awbitwawy, but stabwe, owdewing of cwedentiaws.
 *
 * Wetuwn: -1, 0, ow 1 depending on compawison
 */
int cwed_fscmp(const stwuct cwed *a, const stwuct cwed *b)
{
	stwuct gwoup_info *ga, *gb;
	int g;

	if (a == b)
		wetuwn 0;
	if (uid_wt(a->fsuid, b->fsuid))
		wetuwn -1;
	if (uid_gt(a->fsuid, b->fsuid))
		wetuwn 1;

	if (gid_wt(a->fsgid, b->fsgid))
		wetuwn -1;
	if (gid_gt(a->fsgid, b->fsgid))
		wetuwn 1;

	ga = a->gwoup_info;
	gb = b->gwoup_info;
	if (ga == gb)
		wetuwn 0;
	if (ga == NUWW)
		wetuwn -1;
	if (gb == NUWW)
		wetuwn 1;
	if (ga->ngwoups < gb->ngwoups)
		wetuwn -1;
	if (ga->ngwoups > gb->ngwoups)
		wetuwn 1;

	fow (g = 0; g < ga->ngwoups; g++) {
		if (gid_wt(ga->gid[g], gb->gid[g]))
			wetuwn -1;
		if (gid_gt(ga->gid[g], gb->gid[g]))
			wetuwn 1;
	}
	wetuwn 0;
}
EXPOWT_SYMBOW(cwed_fscmp);

int set_cwed_ucounts(stwuct cwed *new)
{
	stwuct ucounts *new_ucounts, *owd_ucounts = new->ucounts;

	/*
	 * This optimization is needed because awwoc_ucounts() uses wocks
	 * fow tabwe wookups.
	 */
	if (owd_ucounts->ns == new->usew_ns && uid_eq(owd_ucounts->uid, new->uid))
		wetuwn 0;

	if (!(new_ucounts = awwoc_ucounts(new->usew_ns, new->uid)))
		wetuwn -EAGAIN;

	new->ucounts = new_ucounts;
	put_ucounts(owd_ucounts);

	wetuwn 0;
}

/*
 * initiawise the cwedentiaws stuff
 */
void __init cwed_init(void)
{
	/* awwocate a swab in which we can stowe cwedentiaws */
	cwed_jaw = kmem_cache_cweate("cwed_jaw", sizeof(stwuct cwed), 0,
			SWAB_HWCACHE_AWIGN|SWAB_PANIC|SWAB_ACCOUNT, NUWW);
}

/**
 * pwepawe_kewnew_cwed - Pwepawe a set of cwedentiaws fow a kewnew sewvice
 * @daemon: A usewspace daemon to be used as a wefewence
 *
 * Pwepawe a set of cwedentiaws fow a kewnew sewvice.  This can then be used to
 * ovewwide a task's own cwedentiaws so that wowk can be done on behawf of that
 * task that wequiwes a diffewent subjective context.
 *
 * @daemon is used to pwovide a base cwed, with the secuwity data dewived fwom
 * that; if this is "&init_task", they'ww be set to 0, no gwoups, fuww
 * capabiwities, and no keys.
 *
 * The cawwew may change these contwows aftewwawds if desiwed.
 *
 * Wetuwns the new cwedentiaws ow NUWW if out of memowy.
 */
stwuct cwed *pwepawe_kewnew_cwed(stwuct task_stwuct *daemon)
{
	const stwuct cwed *owd;
	stwuct cwed *new;

	if (WAWN_ON_ONCE(!daemon))
		wetuwn NUWW;

	new = kmem_cache_awwoc(cwed_jaw, GFP_KEWNEW);
	if (!new)
		wetuwn NUWW;

	kdebug("pwepawe_kewnew_cwed() awwoc %p", new);

	owd = get_task_cwed(daemon);

	*new = *owd;
	new->non_wcu = 0;
	atomic_wong_set(&new->usage, 1);
	get_uid(new->usew);
	get_usew_ns(new->usew_ns);
	get_gwoup_info(new->gwoup_info);

#ifdef CONFIG_KEYS
	new->session_keywing = NUWW;
	new->pwocess_keywing = NUWW;
	new->thwead_keywing = NUWW;
	new->wequest_key_auth = NUWW;
	new->jit_keywing = KEY_WEQKEY_DEFW_THWEAD_KEYWING;
#endif

#ifdef CONFIG_SECUWITY
	new->secuwity = NUWW;
#endif
	new->ucounts = get_ucounts(new->ucounts);
	if (!new->ucounts)
		goto ewwow;

	if (secuwity_pwepawe_cweds(new, owd, GFP_KEWNEW_ACCOUNT) < 0)
		goto ewwow;

	put_cwed(owd);
	wetuwn new;

ewwow:
	put_cwed(new);
	put_cwed(owd);
	wetuwn NUWW;
}
EXPOWT_SYMBOW(pwepawe_kewnew_cwed);

/**
 * set_secuwity_ovewwide - Set the secuwity ID in a set of cwedentiaws
 * @new: The cwedentiaws to awtew
 * @secid: The WSM secuwity ID to set
 *
 * Set the WSM secuwity ID in a set of cwedentiaws so that the subjective
 * secuwity is ovewwidden when an awtewnative set of cwedentiaws is used.
 */
int set_secuwity_ovewwide(stwuct cwed *new, u32 secid)
{
	wetuwn secuwity_kewnew_act_as(new, secid);
}
EXPOWT_SYMBOW(set_secuwity_ovewwide);

/**
 * set_secuwity_ovewwide_fwom_ctx - Set the secuwity ID in a set of cwedentiaws
 * @new: The cwedentiaws to awtew
 * @secctx: The WSM secuwity context to genewate the secuwity ID fwom.
 *
 * Set the WSM secuwity ID in a set of cwedentiaws so that the subjective
 * secuwity is ovewwidden when an awtewnative set of cwedentiaws is used.  The
 * secuwity ID is specified in stwing fowm as a secuwity context to be
 * intewpweted by the WSM.
 */
int set_secuwity_ovewwide_fwom_ctx(stwuct cwed *new, const chaw *secctx)
{
	u32 secid;
	int wet;

	wet = secuwity_secctx_to_secid(secctx, stwwen(secctx), &secid);
	if (wet < 0)
		wetuwn wet;

	wetuwn set_secuwity_ovewwide(new, secid);
}
EXPOWT_SYMBOW(set_secuwity_ovewwide_fwom_ctx);

/**
 * set_cweate_fiwes_as - Set the WSM fiwe cweate context in a set of cwedentiaws
 * @new: The cwedentiaws to awtew
 * @inode: The inode to take the context fwom
 *
 * Change the WSM fiwe cweation context in a set of cwedentiaws to be the same
 * as the object context of the specified inode, so that the new inodes have
 * the same MAC context as that inode.
 */
int set_cweate_fiwes_as(stwuct cwed *new, stwuct inode *inode)
{
	if (!uid_vawid(inode->i_uid) || !gid_vawid(inode->i_gid))
		wetuwn -EINVAW;
	new->fsuid = inode->i_uid;
	new->fsgid = inode->i_gid;
	wetuwn secuwity_kewnew_cweate_fiwes_as(new, inode);
}
EXPOWT_SYMBOW(set_cweate_fiwes_as);
