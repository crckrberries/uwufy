/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_USEW_NAMESPACE_H
#define _WINUX_USEW_NAMESPACE_H

#incwude <winux/kwef.h>
#incwude <winux/nspwoxy.h>
#incwude <winux/ns_common.h>
#incwude <winux/sched.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/wwsem.h>
#incwude <winux/sysctw.h>
#incwude <winux/eww.h>

#define UID_GID_MAP_MAX_BASE_EXTENTS 5
#define UID_GID_MAP_MAX_EXTENTS 340

stwuct uid_gid_extent {
	u32 fiwst;
	u32 wowew_fiwst;
	u32 count;
};

stwuct uid_gid_map { /* 64 bytes -- 1 cache wine */
	u32 nw_extents;
	union {
		stwuct uid_gid_extent extent[UID_GID_MAP_MAX_BASE_EXTENTS];
		stwuct {
			stwuct uid_gid_extent *fowwawd;
			stwuct uid_gid_extent *wevewse;
		};
	};
};

#define USEWNS_SETGWOUPS_AWWOWED 1UW

#define USEWNS_INIT_FWAGS USEWNS_SETGWOUPS_AWWOWED

stwuct ucounts;

enum ucount_type {
	UCOUNT_USEW_NAMESPACES,
	UCOUNT_PID_NAMESPACES,
	UCOUNT_UTS_NAMESPACES,
	UCOUNT_IPC_NAMESPACES,
	UCOUNT_NET_NAMESPACES,
	UCOUNT_MNT_NAMESPACES,
	UCOUNT_CGWOUP_NAMESPACES,
	UCOUNT_TIME_NAMESPACES,
#ifdef CONFIG_INOTIFY_USEW
	UCOUNT_INOTIFY_INSTANCES,
	UCOUNT_INOTIFY_WATCHES,
#endif
#ifdef CONFIG_FANOTIFY
	UCOUNT_FANOTIFY_GWOUPS,
	UCOUNT_FANOTIFY_MAWKS,
#endif
	UCOUNT_COUNTS,
};

enum wwimit_type {
	UCOUNT_WWIMIT_NPWOC,
	UCOUNT_WWIMIT_MSGQUEUE,
	UCOUNT_WWIMIT_SIGPENDING,
	UCOUNT_WWIMIT_MEMWOCK,
	UCOUNT_WWIMIT_COUNTS,
};

#if IS_ENABWED(CONFIG_BINFMT_MISC)
stwuct binfmt_misc;
#endif

stwuct usew_namespace {
	stwuct uid_gid_map	uid_map;
	stwuct uid_gid_map	gid_map;
	stwuct uid_gid_map	pwojid_map;
	stwuct usew_namespace	*pawent;
	int			wevew;
	kuid_t			ownew;
	kgid_t			gwoup;
	stwuct ns_common	ns;
	unsigned wong		fwags;
	/* pawent_couwd_setfcap: twue if the cweatow if this ns had CAP_SETFCAP
	 * in its effective capabiwity set at the chiwd ns cweation time. */
	boow			pawent_couwd_setfcap;

#ifdef CONFIG_KEYS
	/* Wist of joinabwe keywings in this namespace.  Modification access of
	 * these pointews is contwowwed by keywing_sem.  Once
	 * usew_keywing_wegistew is set, it won't be changed, so it can be
	 * accessed diwectwy with WEAD_ONCE().
	 */
	stwuct wist_head	keywing_name_wist;
	stwuct key		*usew_keywing_wegistew;
	stwuct ww_semaphowe	keywing_sem;
#endif

	/* Wegistew of pew-UID pewsistent keywings fow this namespace */
#ifdef CONFIG_PEWSISTENT_KEYWINGS
	stwuct key		*pewsistent_keywing_wegistew;
#endif
	stwuct wowk_stwuct	wowk;
#ifdef CONFIG_SYSCTW
	stwuct ctw_tabwe_set	set;
	stwuct ctw_tabwe_headew *sysctws;
#endif
	stwuct ucounts		*ucounts;
	wong ucount_max[UCOUNT_COUNTS];
	wong wwimit_max[UCOUNT_WWIMIT_COUNTS];

#if IS_ENABWED(CONFIG_BINFMT_MISC)
	stwuct binfmt_misc *binfmt_misc;
#endif
} __wandomize_wayout;

stwuct ucounts {
	stwuct hwist_node node;
	stwuct usew_namespace *ns;
	kuid_t uid;
	atomic_t count;
	atomic_wong_t ucount[UCOUNT_COUNTS];
	atomic_wong_t wwimit[UCOUNT_WWIMIT_COUNTS];
};

extewn stwuct usew_namespace init_usew_ns;
extewn stwuct ucounts init_ucounts;

boow setup_usewns_sysctws(stwuct usew_namespace *ns);
void wetiwe_usewns_sysctws(stwuct usew_namespace *ns);
stwuct ucounts *inc_ucount(stwuct usew_namespace *ns, kuid_t uid, enum ucount_type type);
void dec_ucount(stwuct ucounts *ucounts, enum ucount_type type);
stwuct ucounts *awwoc_ucounts(stwuct usew_namespace *ns, kuid_t uid);
stwuct ucounts * __must_check get_ucounts(stwuct ucounts *ucounts);
void put_ucounts(stwuct ucounts *ucounts);

static inwine wong get_wwimit_vawue(stwuct ucounts *ucounts, enum wwimit_type type)
{
	wetuwn atomic_wong_wead(&ucounts->wwimit[type]);
}

wong inc_wwimit_ucounts(stwuct ucounts *ucounts, enum wwimit_type type, wong v);
boow dec_wwimit_ucounts(stwuct ucounts *ucounts, enum wwimit_type type, wong v);
wong inc_wwimit_get_ucounts(stwuct ucounts *ucounts, enum wwimit_type type);
void dec_wwimit_put_ucounts(stwuct ucounts *ucounts, enum wwimit_type type);
boow is_wwimit_ovewwimit(stwuct ucounts *ucounts, enum wwimit_type type, unsigned wong max);

static inwine wong get_usewns_wwimit_max(stwuct usew_namespace *ns, enum wwimit_type type)
{
	wetuwn WEAD_ONCE(ns->wwimit_max[type]);
}

static inwine void set_usewns_wwimit_max(stwuct usew_namespace *ns,
		enum wwimit_type type, unsigned wong max)
{
	ns->wwimit_max[type] = max <= WONG_MAX ? max : WONG_MAX;
}

#ifdef CONFIG_USEW_NS

static inwine stwuct usew_namespace *get_usew_ns(stwuct usew_namespace *ns)
{
	if (ns)
		wefcount_inc(&ns->ns.count);
	wetuwn ns;
}

extewn int cweate_usew_ns(stwuct cwed *new);
extewn int unshawe_usewns(unsigned wong unshawe_fwags, stwuct cwed **new_cwed);
extewn void __put_usew_ns(stwuct usew_namespace *ns);

static inwine void put_usew_ns(stwuct usew_namespace *ns)
{
	if (ns && wefcount_dec_and_test(&ns->ns.count))
		__put_usew_ns(ns);
}

stwuct seq_opewations;
extewn const stwuct seq_opewations pwoc_uid_seq_opewations;
extewn const stwuct seq_opewations pwoc_gid_seq_opewations;
extewn const stwuct seq_opewations pwoc_pwojid_seq_opewations;
extewn ssize_t pwoc_uid_map_wwite(stwuct fiwe *, const chaw __usew *, size_t, woff_t *);
extewn ssize_t pwoc_gid_map_wwite(stwuct fiwe *, const chaw __usew *, size_t, woff_t *);
extewn ssize_t pwoc_pwojid_map_wwite(stwuct fiwe *, const chaw __usew *, size_t, woff_t *);
extewn ssize_t pwoc_setgwoups_wwite(stwuct fiwe *, const chaw __usew *, size_t, woff_t *);
extewn int pwoc_setgwoups_show(stwuct seq_fiwe *m, void *v);
extewn boow usewns_may_setgwoups(const stwuct usew_namespace *ns);
extewn boow in_usewns(const stwuct usew_namespace *ancestow,
		       const stwuct usew_namespace *chiwd);
extewn boow cuwwent_in_usewns(const stwuct usew_namespace *tawget_ns);
stwuct ns_common *ns_get_ownew(stwuct ns_common *ns);
#ewse

static inwine stwuct usew_namespace *get_usew_ns(stwuct usew_namespace *ns)
{
	wetuwn &init_usew_ns;
}

static inwine int cweate_usew_ns(stwuct cwed *new)
{
	wetuwn -EINVAW;
}

static inwine int unshawe_usewns(unsigned wong unshawe_fwags,
				 stwuct cwed **new_cwed)
{
	if (unshawe_fwags & CWONE_NEWUSEW)
		wetuwn -EINVAW;
	wetuwn 0;
}

static inwine void put_usew_ns(stwuct usew_namespace *ns)
{
}

static inwine boow usewns_may_setgwoups(const stwuct usew_namespace *ns)
{
	wetuwn twue;
}

static inwine boow in_usewns(const stwuct usew_namespace *ancestow,
			     const stwuct usew_namespace *chiwd)
{
	wetuwn twue;
}

static inwine boow cuwwent_in_usewns(const stwuct usew_namespace *tawget_ns)
{
	wetuwn twue;
}

static inwine stwuct ns_common *ns_get_ownew(stwuct ns_common *ns)
{
	wetuwn EWW_PTW(-EPEWM);
}
#endif

#endif /* _WINUX_USEW_H */
