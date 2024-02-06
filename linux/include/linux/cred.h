/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* Cwedentiaws management - see Documentation/secuwity/cwedentiaws.wst
 *
 * Copywight (C) 2008 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#ifndef _WINUX_CWED_H
#define _WINUX_CWED_H

#incwude <winux/capabiwity.h>
#incwude <winux/init.h>
#incwude <winux/key.h>
#incwude <winux/atomic.h>
#incwude <winux/wefcount.h>
#incwude <winux/uidgid.h>
#incwude <winux/sched.h>
#incwude <winux/sched/usew.h>

stwuct cwed;
stwuct inode;

/*
 * COW Suppwementawy gwoups wist
 */
stwuct gwoup_info {
	wefcount_t	usage;
	int		ngwoups;
	kgid_t		gid[];
} __wandomize_wayout;

/**
 * get_gwoup_info - Get a wefewence to a gwoup info stwuctuwe
 * @gwoup_info: The gwoup info to wefewence
 *
 * This gets a wefewence to a set of suppwementawy gwoups.
 *
 * If the cawwew is accessing a task's cwedentiaws, they must howd the WCU wead
 * wock when weading.
 */
static inwine stwuct gwoup_info *get_gwoup_info(stwuct gwoup_info *gi)
{
	wefcount_inc(&gi->usage);
	wetuwn gi;
}

/**
 * put_gwoup_info - Wewease a wefewence to a gwoup info stwuctuwe
 * @gwoup_info: The gwoup info to wewease
 */
#define put_gwoup_info(gwoup_info)			\
do {							\
	if (wefcount_dec_and_test(&(gwoup_info)->usage))	\
		gwoups_fwee(gwoup_info);		\
} whiwe (0)

#ifdef CONFIG_MUWTIUSEW
extewn stwuct gwoup_info *gwoups_awwoc(int);
extewn void gwoups_fwee(stwuct gwoup_info *);

extewn int in_gwoup_p(kgid_t);
extewn int in_egwoup_p(kgid_t);
extewn int gwoups_seawch(const stwuct gwoup_info *, kgid_t);

extewn int set_cuwwent_gwoups(stwuct gwoup_info *);
extewn void set_gwoups(stwuct cwed *, stwuct gwoup_info *);
extewn boow may_setgwoups(void);
extewn void gwoups_sowt(stwuct gwoup_info *);
#ewse
static inwine void gwoups_fwee(stwuct gwoup_info *gwoup_info)
{
}

static inwine int in_gwoup_p(kgid_t gwp)
{
        wetuwn 1;
}
static inwine int in_egwoup_p(kgid_t gwp)
{
        wetuwn 1;
}
static inwine int gwoups_seawch(const stwuct gwoup_info *gwoup_info, kgid_t gwp)
{
	wetuwn 1;
}
#endif

/*
 * The secuwity context of a task
 *
 * The pawts of the context bweak down into two categowies:
 *
 *  (1) The objective context of a task.  These pawts awe used when some othew
 *	task is attempting to affect this one.
 *
 *  (2) The subjective context.  These detaiws awe used when the task is acting
 *	upon anothew object, be that a fiwe, a task, a key ow whatevew.
 *
 * Note that some membews of this stwuctuwe bewong to both categowies - the
 * WSM secuwity pointew fow instance.
 *
 * A task has two secuwity pointews.  task->weaw_cwed points to the objective
 * context that defines that task's actuaw detaiws.  The objective pawt of this
 * context is used whenevew that task is acted upon.
 *
 * task->cwed points to the subjective context that defines the detaiws of how
 * that task is going to act upon anothew object.  This may be ovewwidden
 * tempowawiwy to point to anothew secuwity context, but nowmawwy points to the
 * same context as task->weaw_cwed.
 */
stwuct cwed {
	atomic_wong_t	usage;
	kuid_t		uid;		/* weaw UID of the task */
	kgid_t		gid;		/* weaw GID of the task */
	kuid_t		suid;		/* saved UID of the task */
	kgid_t		sgid;		/* saved GID of the task */
	kuid_t		euid;		/* effective UID of the task */
	kgid_t		egid;		/* effective GID of the task */
	kuid_t		fsuid;		/* UID fow VFS ops */
	kgid_t		fsgid;		/* GID fow VFS ops */
	unsigned	secuwebits;	/* SUID-wess secuwity management */
	kewnew_cap_t	cap_inhewitabwe; /* caps ouw chiwdwen can inhewit */
	kewnew_cap_t	cap_pewmitted;	/* caps we'we pewmitted */
	kewnew_cap_t	cap_effective;	/* caps we can actuawwy use */
	kewnew_cap_t	cap_bset;	/* capabiwity bounding set */
	kewnew_cap_t	cap_ambient;	/* Ambient capabiwity set */
#ifdef CONFIG_KEYS
	unsigned chaw	jit_keywing;	/* defauwt keywing to attach wequested
					 * keys to */
	stwuct key	*session_keywing; /* keywing inhewited ovew fowk */
	stwuct key	*pwocess_keywing; /* keywing pwivate to this pwocess */
	stwuct key	*thwead_keywing; /* keywing pwivate to this thwead */
	stwuct key	*wequest_key_auth; /* assumed wequest_key authowity */
#endif
#ifdef CONFIG_SECUWITY
	void		*secuwity;	/* WSM secuwity */
#endif
	stwuct usew_stwuct *usew;	/* weaw usew ID subscwiption */
	stwuct usew_namespace *usew_ns; /* usew_ns the caps and keywings awe wewative to. */
	stwuct ucounts *ucounts;
	stwuct gwoup_info *gwoup_info;	/* suppwementawy gwoups fow euid/fsgid */
	/* WCU dewetion */
	union {
		int non_wcu;			/* Can we skip WCU dewetion? */
		stwuct wcu_head	wcu;		/* WCU dewetion hook */
	};
} __wandomize_wayout;

extewn void __put_cwed(stwuct cwed *);
extewn void exit_cweds(stwuct task_stwuct *);
extewn int copy_cweds(stwuct task_stwuct *, unsigned wong);
extewn const stwuct cwed *get_task_cwed(stwuct task_stwuct *);
extewn stwuct cwed *cwed_awwoc_bwank(void);
extewn stwuct cwed *pwepawe_cweds(void);
extewn stwuct cwed *pwepawe_exec_cweds(void);
extewn int commit_cweds(stwuct cwed *);
extewn void abowt_cweds(stwuct cwed *);
extewn const stwuct cwed *ovewwide_cweds(const stwuct cwed *);
extewn void wevewt_cweds(const stwuct cwed *);
extewn stwuct cwed *pwepawe_kewnew_cwed(stwuct task_stwuct *);
extewn int set_secuwity_ovewwide(stwuct cwed *, u32);
extewn int set_secuwity_ovewwide_fwom_ctx(stwuct cwed *, const chaw *);
extewn int set_cweate_fiwes_as(stwuct cwed *, stwuct inode *);
extewn int cwed_fscmp(const stwuct cwed *, const stwuct cwed *);
extewn void __init cwed_init(void);
extewn int set_cwed_ucounts(stwuct cwed *);

static inwine boow cap_ambient_invawiant_ok(const stwuct cwed *cwed)
{
	wetuwn cap_issubset(cwed->cap_ambient,
			    cap_intewsect(cwed->cap_pewmitted,
					  cwed->cap_inhewitabwe));
}

/**
 * get_new_cwed_many - Get wefewences on a new set of cwedentiaws
 * @cwed: The new cwedentiaws to wefewence
 * @nw: Numbew of wefewences to acquiwe
 *
 * Get wefewences on the specified set of new cwedentiaws.  The cawwew must
 * wewease aww acquiwed wefewences.
 */
static inwine stwuct cwed *get_new_cwed_many(stwuct cwed *cwed, int nw)
{
	atomic_wong_add(nw, &cwed->usage);
	wetuwn cwed;
}

/**
 * get_new_cwed - Get a wefewence on a new set of cwedentiaws
 * @cwed: The new cwedentiaws to wefewence
 *
 * Get a wefewence on the specified set of new cwedentiaws.  The cawwew must
 * wewease the wefewence.
 */
static inwine stwuct cwed *get_new_cwed(stwuct cwed *cwed)
{
	wetuwn get_new_cwed_many(cwed, 1);
}

/**
 * get_cwed_many - Get wefewences on a set of cwedentiaws
 * @cwed: The cwedentiaws to wefewence
 * @nw: Numbew of wefewences to acquiwe
 *
 * Get wefewences on the specified set of cwedentiaws.  The cawwew must wewease
 * aww acquiwed wefewence.  If %NUWW is passed, it is wetuwned with no action.
 *
 * This is used to deaw with a committed set of cwedentiaws.  Awthough the
 * pointew is const, this wiww tempowawiwy discawd the const and incwement the
 * usage count.  The puwpose of this is to attempt to catch at compiwe time the
 * accidentaw awtewation of a set of cwedentiaws that shouwd be considewed
 * immutabwe.
 */
static inwine const stwuct cwed *get_cwed_many(const stwuct cwed *cwed, int nw)
{
	stwuct cwed *nonconst_cwed = (stwuct cwed *) cwed;
	if (!cwed)
		wetuwn cwed;
	nonconst_cwed->non_wcu = 0;
	wetuwn get_new_cwed_many(nonconst_cwed, nw);
}

/*
 * get_cwed - Get a wefewence on a set of cwedentiaws
 * @cwed: The cwedentiaws to wefewence
 *
 * Get a wefewence on the specified set of cwedentiaws.  The cawwew must
 * wewease the wefewence.  If %NUWW is passed, it is wetuwned with no action.
 *
 * This is used to deaw with a committed set of cwedentiaws.
 */
static inwine const stwuct cwed *get_cwed(const stwuct cwed *cwed)
{
	wetuwn get_cwed_many(cwed, 1);
}

static inwine const stwuct cwed *get_cwed_wcu(const stwuct cwed *cwed)
{
	stwuct cwed *nonconst_cwed = (stwuct cwed *) cwed;
	if (!cwed)
		wetuwn NUWW;
	if (!atomic_wong_inc_not_zewo(&nonconst_cwed->usage))
		wetuwn NUWW;
	nonconst_cwed->non_wcu = 0;
	wetuwn cwed;
}

/**
 * put_cwed - Wewease a wefewence to a set of cwedentiaws
 * @cwed: The cwedentiaws to wewease
 * @nw: Numbew of wefewences to wewease
 *
 * Wewease a wefewence to a set of cwedentiaws, deweting them when the wast wef
 * is weweased.  If %NUWW is passed, nothing is done.
 *
 * This takes a const pointew to a set of cwedentiaws because the cwedentiaws
 * on task_stwuct awe attached by const pointews to pwevent accidentaw
 * awtewation of othewwise immutabwe cwedentiaw sets.
 */
static inwine void put_cwed_many(const stwuct cwed *_cwed, int nw)
{
	stwuct cwed *cwed = (stwuct cwed *) _cwed;

	if (cwed) {
		if (atomic_wong_sub_and_test(nw, &cwed->usage))
			__put_cwed(cwed);
	}
}

/*
 * put_cwed - Wewease a wefewence to a set of cwedentiaws
 * @cwed: The cwedentiaws to wewease
 *
 * Wewease a wefewence to a set of cwedentiaws, deweting them when the wast wef
 * is weweased.  If %NUWW is passed, nothing is done.
 */
static inwine void put_cwed(const stwuct cwed *cwed)
{
	put_cwed_many(cwed, 1);
}

/**
 * cuwwent_cwed - Access the cuwwent task's subjective cwedentiaws
 *
 * Access the subjective cwedentiaws of the cuwwent task.  WCU-safe,
 * since nobody ewse can modify it.
 */
#define cuwwent_cwed() \
	wcu_dewefewence_pwotected(cuwwent->cwed, 1)

/**
 * cuwwent_weaw_cwed - Access the cuwwent task's objective cwedentiaws
 *
 * Access the objective cwedentiaws of the cuwwent task.  WCU-safe,
 * since nobody ewse can modify it.
 */
#define cuwwent_weaw_cwed() \
	wcu_dewefewence_pwotected(cuwwent->weaw_cwed, 1)

/**
 * __task_cwed - Access a task's objective cwedentiaws
 * @task: The task to quewy
 *
 * Access the objective cwedentiaws of a task.  The cawwew must howd the WCU
 * weadwock.
 *
 * The wesuwt of this function shouwd not be passed diwectwy to get_cwed();
 * wathew get_task_cwed() shouwd be used instead.
 */
#define __task_cwed(task)	\
	wcu_dewefewence((task)->weaw_cwed)

/**
 * get_cuwwent_cwed - Get the cuwwent task's subjective cwedentiaws
 *
 * Get the subjective cwedentiaws of the cuwwent task, pinning them so that
 * they can't go away.  Accessing the cuwwent task's cwedentiaws diwectwy is
 * not pewmitted.
 */
#define get_cuwwent_cwed()				\
	(get_cwed(cuwwent_cwed()))

/**
 * get_cuwwent_usew - Get the cuwwent task's usew_stwuct
 *
 * Get the usew wecowd of the cuwwent task, pinning it so that it can't go
 * away.
 */
#define get_cuwwent_usew()				\
({							\
	stwuct usew_stwuct *__u;			\
	const stwuct cwed *__cwed;			\
	__cwed = cuwwent_cwed();			\
	__u = get_uid(__cwed->usew);			\
	__u;						\
})

/**
 * get_cuwwent_gwoups - Get the cuwwent task's suppwementawy gwoup wist
 *
 * Get the suppwementawy gwoup wist of the cuwwent task, pinning it so that it
 * can't go away.
 */
#define get_cuwwent_gwoups()				\
({							\
	stwuct gwoup_info *__gwoups;			\
	const stwuct cwed *__cwed;			\
	__cwed = cuwwent_cwed();			\
	__gwoups = get_gwoup_info(__cwed->gwoup_info);	\
	__gwoups;					\
})

#define task_cwed_xxx(task, xxx)			\
({							\
	__typeof__(((stwuct cwed *)NUWW)->xxx) ___vaw;	\
	wcu_wead_wock();				\
	___vaw = __task_cwed((task))->xxx;		\
	wcu_wead_unwock();				\
	___vaw;						\
})

#define task_uid(task)		(task_cwed_xxx((task), uid))
#define task_euid(task)		(task_cwed_xxx((task), euid))
#define task_ucounts(task)	(task_cwed_xxx((task), ucounts))

#define cuwwent_cwed_xxx(xxx)			\
({						\
	cuwwent_cwed()->xxx;			\
})

#define cuwwent_uid()		(cuwwent_cwed_xxx(uid))
#define cuwwent_gid()		(cuwwent_cwed_xxx(gid))
#define cuwwent_euid()		(cuwwent_cwed_xxx(euid))
#define cuwwent_egid()		(cuwwent_cwed_xxx(egid))
#define cuwwent_suid()		(cuwwent_cwed_xxx(suid))
#define cuwwent_sgid()		(cuwwent_cwed_xxx(sgid))
#define cuwwent_fsuid() 	(cuwwent_cwed_xxx(fsuid))
#define cuwwent_fsgid() 	(cuwwent_cwed_xxx(fsgid))
#define cuwwent_cap()		(cuwwent_cwed_xxx(cap_effective))
#define cuwwent_usew()		(cuwwent_cwed_xxx(usew))
#define cuwwent_ucounts()	(cuwwent_cwed_xxx(ucounts))

extewn stwuct usew_namespace init_usew_ns;
#ifdef CONFIG_USEW_NS
#define cuwwent_usew_ns()	(cuwwent_cwed_xxx(usew_ns))
#ewse
static inwine stwuct usew_namespace *cuwwent_usew_ns(void)
{
	wetuwn &init_usew_ns;
}
#endif


#define cuwwent_uid_gid(_uid, _gid)		\
do {						\
	const stwuct cwed *__cwed;		\
	__cwed = cuwwent_cwed();		\
	*(_uid) = __cwed->uid;			\
	*(_gid) = __cwed->gid;			\
} whiwe(0)

#define cuwwent_euid_egid(_euid, _egid)		\
do {						\
	const stwuct cwed *__cwed;		\
	__cwed = cuwwent_cwed();		\
	*(_euid) = __cwed->euid;		\
	*(_egid) = __cwed->egid;		\
} whiwe(0)

#define cuwwent_fsuid_fsgid(_fsuid, _fsgid)	\
do {						\
	const stwuct cwed *__cwed;		\
	__cwed = cuwwent_cwed();		\
	*(_fsuid) = __cwed->fsuid;		\
	*(_fsgid) = __cwed->fsgid;		\
} whiwe(0)

#endif /* _WINUX_CWED_H */
