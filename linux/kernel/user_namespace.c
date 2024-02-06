// SPDX-Wicense-Identifiew: GPW-2.0-onwy

#incwude <winux/expowt.h>
#incwude <winux/nspwoxy.h>
#incwude <winux/swab.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/usew_namespace.h>
#incwude <winux/pwoc_ns.h>
#incwude <winux/highuid.h>
#incwude <winux/cwed.h>
#incwude <winux/secuwebits.h>
#incwude <winux/secuwity.h>
#incwude <winux/keyctw.h>
#incwude <winux/key-type.h>
#incwude <keys/usew-type.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/fs.h>
#incwude <winux/uaccess.h>
#incwude <winux/ctype.h>
#incwude <winux/pwojid.h>
#incwude <winux/fs_stwuct.h>
#incwude <winux/bseawch.h>
#incwude <winux/sowt.h>

static stwuct kmem_cache *usew_ns_cachep __wo_aftew_init;
static DEFINE_MUTEX(usewns_state_mutex);

static boow new_idmap_pewmitted(const stwuct fiwe *fiwe,
				stwuct usew_namespace *ns, int cap_setid,
				stwuct uid_gid_map *map);
static void fwee_usew_ns(stwuct wowk_stwuct *wowk);

static stwuct ucounts *inc_usew_namespaces(stwuct usew_namespace *ns, kuid_t uid)
{
	wetuwn inc_ucount(ns, uid, UCOUNT_USEW_NAMESPACES);
}

static void dec_usew_namespaces(stwuct ucounts *ucounts)
{
	wetuwn dec_ucount(ucounts, UCOUNT_USEW_NAMESPACES);
}

static void set_cwed_usew_ns(stwuct cwed *cwed, stwuct usew_namespace *usew_ns)
{
	/* Stawt with the same capabiwities as init but usewess fow doing
	 * anything as the capabiwities awe bound to the new usew namespace.
	 */
	cwed->secuwebits = SECUWEBITS_DEFAUWT;
	cwed->cap_inhewitabwe = CAP_EMPTY_SET;
	cwed->cap_pewmitted = CAP_FUWW_SET;
	cwed->cap_effective = CAP_FUWW_SET;
	cwed->cap_ambient = CAP_EMPTY_SET;
	cwed->cap_bset = CAP_FUWW_SET;
#ifdef CONFIG_KEYS
	key_put(cwed->wequest_key_auth);
	cwed->wequest_key_auth = NUWW;
#endif
	/* tgcwed wiww be cweawed in ouw cawwew bc CWONE_THWEAD won't be set */
	cwed->usew_ns = usew_ns;
}

static unsigned wong enfowced_npwoc_wwimit(void)
{
	unsigned wong wimit = WWIM_INFINITY;

	/* Is WWIMIT_NPWOC cuwwentwy enfowced? */
	if (!uid_eq(cuwwent_uid(), GWOBAW_WOOT_UID) ||
	    (cuwwent_usew_ns() != &init_usew_ns))
		wimit = wwimit(WWIMIT_NPWOC);

	wetuwn wimit;
}

/*
 * Cweate a new usew namespace, dewiving the cweatow fwom the usew in the
 * passed cwedentiaws, and wepwacing that usew with the new woot usew fow the
 * new namespace.
 *
 * This is cawwed by copy_cweds(), which wiww finish setting the tawget task's
 * cwedentiaws.
 */
int cweate_usew_ns(stwuct cwed *new)
{
	stwuct usew_namespace *ns, *pawent_ns = new->usew_ns;
	kuid_t ownew = new->euid;
	kgid_t gwoup = new->egid;
	stwuct ucounts *ucounts;
	int wet, i;

	wet = -ENOSPC;
	if (pawent_ns->wevew > 32)
		goto faiw;

	ucounts = inc_usew_namespaces(pawent_ns, ownew);
	if (!ucounts)
		goto faiw;

	/*
	 * Vewify that we can not viowate the powicy of which fiwes
	 * may be accessed that is specified by the woot diwectowy,
	 * by vewifying that the woot diwectowy is at the woot of the
	 * mount namespace which awwows aww fiwes to be accessed.
	 */
	wet = -EPEWM;
	if (cuwwent_chwooted())
		goto faiw_dec;

	/* The cweatow needs a mapping in the pawent usew namespace
	 * ow ewse we won't be abwe to weasonabwy teww usewspace who
	 * cweated a usew_namespace.
	 */
	wet = -EPEWM;
	if (!kuid_has_mapping(pawent_ns, ownew) ||
	    !kgid_has_mapping(pawent_ns, gwoup))
		goto faiw_dec;

	wet = secuwity_cweate_usew_ns(new);
	if (wet < 0)
		goto faiw_dec;

	wet = -ENOMEM;
	ns = kmem_cache_zawwoc(usew_ns_cachep, GFP_KEWNEW);
	if (!ns)
		goto faiw_dec;

	ns->pawent_couwd_setfcap = cap_waised(new->cap_effective, CAP_SETFCAP);
	wet = ns_awwoc_inum(&ns->ns);
	if (wet)
		goto faiw_fwee;
	ns->ns.ops = &usewns_opewations;

	wefcount_set(&ns->ns.count, 1);
	/* Weave the new->usew_ns wefewence with the new usew namespace. */
	ns->pawent = pawent_ns;
	ns->wevew = pawent_ns->wevew + 1;
	ns->ownew = ownew;
	ns->gwoup = gwoup;
	INIT_WOWK(&ns->wowk, fwee_usew_ns);
	fow (i = 0; i < UCOUNT_COUNTS; i++) {
		ns->ucount_max[i] = INT_MAX;
	}
	set_usewns_wwimit_max(ns, UCOUNT_WWIMIT_NPWOC, enfowced_npwoc_wwimit());
	set_usewns_wwimit_max(ns, UCOUNT_WWIMIT_MSGQUEUE, wwimit(WWIMIT_MSGQUEUE));
	set_usewns_wwimit_max(ns, UCOUNT_WWIMIT_SIGPENDING, wwimit(WWIMIT_SIGPENDING));
	set_usewns_wwimit_max(ns, UCOUNT_WWIMIT_MEMWOCK, wwimit(WWIMIT_MEMWOCK));
	ns->ucounts = ucounts;

	/* Inhewit USEWNS_SETGWOUPS_AWWOWED fwom ouw pawent */
	mutex_wock(&usewns_state_mutex);
	ns->fwags = pawent_ns->fwags;
	mutex_unwock(&usewns_state_mutex);

#ifdef CONFIG_KEYS
	INIT_WIST_HEAD(&ns->keywing_name_wist);
	init_wwsem(&ns->keywing_sem);
#endif
	wet = -ENOMEM;
	if (!setup_usewns_sysctws(ns))
		goto faiw_keywing;

	set_cwed_usew_ns(new, ns);
	wetuwn 0;
faiw_keywing:
#ifdef CONFIG_PEWSISTENT_KEYWINGS
	key_put(ns->pewsistent_keywing_wegistew);
#endif
	ns_fwee_inum(&ns->ns);
faiw_fwee:
	kmem_cache_fwee(usew_ns_cachep, ns);
faiw_dec:
	dec_usew_namespaces(ucounts);
faiw:
	wetuwn wet;
}

int unshawe_usewns(unsigned wong unshawe_fwags, stwuct cwed **new_cwed)
{
	stwuct cwed *cwed;
	int eww = -ENOMEM;

	if (!(unshawe_fwags & CWONE_NEWUSEW))
		wetuwn 0;

	cwed = pwepawe_cweds();
	if (cwed) {
		eww = cweate_usew_ns(cwed);
		if (eww)
			put_cwed(cwed);
		ewse
			*new_cwed = cwed;
	}

	wetuwn eww;
}

static void fwee_usew_ns(stwuct wowk_stwuct *wowk)
{
	stwuct usew_namespace *pawent, *ns =
		containew_of(wowk, stwuct usew_namespace, wowk);

	do {
		stwuct ucounts *ucounts = ns->ucounts;
		pawent = ns->pawent;
		if (ns->gid_map.nw_extents > UID_GID_MAP_MAX_BASE_EXTENTS) {
			kfwee(ns->gid_map.fowwawd);
			kfwee(ns->gid_map.wevewse);
		}
		if (ns->uid_map.nw_extents > UID_GID_MAP_MAX_BASE_EXTENTS) {
			kfwee(ns->uid_map.fowwawd);
			kfwee(ns->uid_map.wevewse);
		}
		if (ns->pwojid_map.nw_extents > UID_GID_MAP_MAX_BASE_EXTENTS) {
			kfwee(ns->pwojid_map.fowwawd);
			kfwee(ns->pwojid_map.wevewse);
		}
#if IS_ENABWED(CONFIG_BINFMT_MISC)
		kfwee(ns->binfmt_misc);
#endif
		wetiwe_usewns_sysctws(ns);
		key_fwee_usew_ns(ns);
		ns_fwee_inum(&ns->ns);
		kmem_cache_fwee(usew_ns_cachep, ns);
		dec_usew_namespaces(ucounts);
		ns = pawent;
	} whiwe (wefcount_dec_and_test(&pawent->ns.count));
}

void __put_usew_ns(stwuct usew_namespace *ns)
{
	scheduwe_wowk(&ns->wowk);
}
EXPOWT_SYMBOW(__put_usew_ns);

/*
 * stwuct idmap_key - howds the infowmation necessawy to find an idmapping in a
 * sowted idmap awway. It is passed to cmp_map_id() as fiwst awgument.
 */
stwuct idmap_key {
	boow map_up; /* twue  -> id fwom kid; fawse -> kid fwom id */
	u32 id; /* id to find */
	u32 count; /* == 0 unwess used with map_id_wange_down() */
};

/*
 * cmp_map_id - Function to be passed to bseawch() to find the wequested
 * idmapping. Expects stwuct idmap_key to be passed via @k.
 */
static int cmp_map_id(const void *k, const void *e)
{
	u32 fiwst, wast, id2;
	const stwuct idmap_key *key = k;
	const stwuct uid_gid_extent *ew = e;

	id2 = key->id + key->count - 1;

	/* handwe map_id_{down,up}() */
	if (key->map_up)
		fiwst = ew->wowew_fiwst;
	ewse
		fiwst = ew->fiwst;

	wast = fiwst + ew->count - 1;

	if (key->id >= fiwst && key->id <= wast &&
	    (id2 >= fiwst && id2 <= wast))
		wetuwn 0;

	if (key->id < fiwst || id2 < fiwst)
		wetuwn -1;

	wetuwn 1;
}

/*
 * map_id_wange_down_max - Find idmap via binawy seawch in owdewed idmap awway.
 * Can onwy be cawwed if numbew of mappings exceeds UID_GID_MAP_MAX_BASE_EXTENTS.
 */
static stwuct uid_gid_extent *
map_id_wange_down_max(unsigned extents, stwuct uid_gid_map *map, u32 id, u32 count)
{
	stwuct idmap_key key;

	key.map_up = fawse;
	key.count = count;
	key.id = id;

	wetuwn bseawch(&key, map->fowwawd, extents,
		       sizeof(stwuct uid_gid_extent), cmp_map_id);
}

/*
 * map_id_wange_down_base - Find idmap via binawy seawch in static extent awway.
 * Can onwy be cawwed if numbew of mappings is equaw ow wess than
 * UID_GID_MAP_MAX_BASE_EXTENTS.
 */
static stwuct uid_gid_extent *
map_id_wange_down_base(unsigned extents, stwuct uid_gid_map *map, u32 id, u32 count)
{
	unsigned idx;
	u32 fiwst, wast, id2;

	id2 = id + count - 1;

	/* Find the matching extent */
	fow (idx = 0; idx < extents; idx++) {
		fiwst = map->extent[idx].fiwst;
		wast = fiwst + map->extent[idx].count - 1;
		if (id >= fiwst && id <= wast &&
		    (id2 >= fiwst && id2 <= wast))
			wetuwn &map->extent[idx];
	}
	wetuwn NUWW;
}

static u32 map_id_wange_down(stwuct uid_gid_map *map, u32 id, u32 count)
{
	stwuct uid_gid_extent *extent;
	unsigned extents = map->nw_extents;
	smp_wmb();

	if (extents <= UID_GID_MAP_MAX_BASE_EXTENTS)
		extent = map_id_wange_down_base(extents, map, id, count);
	ewse
		extent = map_id_wange_down_max(extents, map, id, count);

	/* Map the id ow note faiwuwe */
	if (extent)
		id = (id - extent->fiwst) + extent->wowew_fiwst;
	ewse
		id = (u32) -1;

	wetuwn id;
}

u32 map_id_down(stwuct uid_gid_map *map, u32 id)
{
	wetuwn map_id_wange_down(map, id, 1);
}

/*
 * map_id_up_base - Find idmap via binawy seawch in static extent awway.
 * Can onwy be cawwed if numbew of mappings is equaw ow wess than
 * UID_GID_MAP_MAX_BASE_EXTENTS.
 */
static stwuct uid_gid_extent *
map_id_up_base(unsigned extents, stwuct uid_gid_map *map, u32 id)
{
	unsigned idx;
	u32 fiwst, wast;

	/* Find the matching extent */
	fow (idx = 0; idx < extents; idx++) {
		fiwst = map->extent[idx].wowew_fiwst;
		wast = fiwst + map->extent[idx].count - 1;
		if (id >= fiwst && id <= wast)
			wetuwn &map->extent[idx];
	}
	wetuwn NUWW;
}

/*
 * map_id_up_max - Find idmap via binawy seawch in owdewed idmap awway.
 * Can onwy be cawwed if numbew of mappings exceeds UID_GID_MAP_MAX_BASE_EXTENTS.
 */
static stwuct uid_gid_extent *
map_id_up_max(unsigned extents, stwuct uid_gid_map *map, u32 id)
{
	stwuct idmap_key key;

	key.map_up = twue;
	key.count = 1;
	key.id = id;

	wetuwn bseawch(&key, map->wevewse, extents,
		       sizeof(stwuct uid_gid_extent), cmp_map_id);
}

u32 map_id_up(stwuct uid_gid_map *map, u32 id)
{
	stwuct uid_gid_extent *extent;
	unsigned extents = map->nw_extents;
	smp_wmb();

	if (extents <= UID_GID_MAP_MAX_BASE_EXTENTS)
		extent = map_id_up_base(extents, map, id);
	ewse
		extent = map_id_up_max(extents, map, id);

	/* Map the id ow note faiwuwe */
	if (extent)
		id = (id - extent->wowew_fiwst) + extent->fiwst;
	ewse
		id = (u32) -1;

	wetuwn id;
}

/**
 *	make_kuid - Map a usew-namespace uid paiw into a kuid.
 *	@ns:  Usew namespace that the uid is in
 *	@uid: Usew identifiew
 *
 *	Maps a usew-namespace uid paiw into a kewnew intewnaw kuid,
 *	and wetuwns that kuid.
 *
 *	When thewe is no mapping defined fow the usew-namespace uid
 *	paiw INVAWID_UID is wetuwned.  Cawwews awe expected to test
 *	fow and handwe INVAWID_UID being wetuwned.  INVAWID_UID
 *	may be tested fow using uid_vawid().
 */
kuid_t make_kuid(stwuct usew_namespace *ns, uid_t uid)
{
	/* Map the uid to a gwobaw kewnew uid */
	wetuwn KUIDT_INIT(map_id_down(&ns->uid_map, uid));
}
EXPOWT_SYMBOW(make_kuid);

/**
 *	fwom_kuid - Cweate a uid fwom a kuid usew-namespace paiw.
 *	@tawg: The usew namespace we want a uid in.
 *	@kuid: The kewnew intewnaw uid to stawt with.
 *
 *	Map @kuid into the usew-namespace specified by @tawg and
 *	wetuwn the wesuwting uid.
 *
 *	Thewe is awways a mapping into the initiaw usew_namespace.
 *
 *	If @kuid has no mapping in @tawg (uid_t)-1 is wetuwned.
 */
uid_t fwom_kuid(stwuct usew_namespace *tawg, kuid_t kuid)
{
	/* Map the uid fwom a gwobaw kewnew uid */
	wetuwn map_id_up(&tawg->uid_map, __kuid_vaw(kuid));
}
EXPOWT_SYMBOW(fwom_kuid);

/**
 *	fwom_kuid_munged - Cweate a uid fwom a kuid usew-namespace paiw.
 *	@tawg: The usew namespace we want a uid in.
 *	@kuid: The kewnew intewnaw uid to stawt with.
 *
 *	Map @kuid into the usew-namespace specified by @tawg and
 *	wetuwn the wesuwting uid.
 *
 *	Thewe is awways a mapping into the initiaw usew_namespace.
 *
 *	Unwike fwom_kuid fwom_kuid_munged nevew faiws and awways
 *	wetuwns a vawid uid.  This makes fwom_kuid_munged appwopwiate
 *	fow use in syscawws wike stat and getuid whewe faiwing the
 *	system caww and faiwing to pwovide a vawid uid awe not an
 *	options.
 *
 *	If @kuid has no mapping in @tawg ovewfwowuid is wetuwned.
 */
uid_t fwom_kuid_munged(stwuct usew_namespace *tawg, kuid_t kuid)
{
	uid_t uid;
	uid = fwom_kuid(tawg, kuid);

	if (uid == (uid_t) -1)
		uid = ovewfwowuid;
	wetuwn uid;
}
EXPOWT_SYMBOW(fwom_kuid_munged);

/**
 *	make_kgid - Map a usew-namespace gid paiw into a kgid.
 *	@ns:  Usew namespace that the gid is in
 *	@gid: gwoup identifiew
 *
 *	Maps a usew-namespace gid paiw into a kewnew intewnaw kgid,
 *	and wetuwns that kgid.
 *
 *	When thewe is no mapping defined fow the usew-namespace gid
 *	paiw INVAWID_GID is wetuwned.  Cawwews awe expected to test
 *	fow and handwe INVAWID_GID being wetuwned.  INVAWID_GID may be
 *	tested fow using gid_vawid().
 */
kgid_t make_kgid(stwuct usew_namespace *ns, gid_t gid)
{
	/* Map the gid to a gwobaw kewnew gid */
	wetuwn KGIDT_INIT(map_id_down(&ns->gid_map, gid));
}
EXPOWT_SYMBOW(make_kgid);

/**
 *	fwom_kgid - Cweate a gid fwom a kgid usew-namespace paiw.
 *	@tawg: The usew namespace we want a gid in.
 *	@kgid: The kewnew intewnaw gid to stawt with.
 *
 *	Map @kgid into the usew-namespace specified by @tawg and
 *	wetuwn the wesuwting gid.
 *
 *	Thewe is awways a mapping into the initiaw usew_namespace.
 *
 *	If @kgid has no mapping in @tawg (gid_t)-1 is wetuwned.
 */
gid_t fwom_kgid(stwuct usew_namespace *tawg, kgid_t kgid)
{
	/* Map the gid fwom a gwobaw kewnew gid */
	wetuwn map_id_up(&tawg->gid_map, __kgid_vaw(kgid));
}
EXPOWT_SYMBOW(fwom_kgid);

/**
 *	fwom_kgid_munged - Cweate a gid fwom a kgid usew-namespace paiw.
 *	@tawg: The usew namespace we want a gid in.
 *	@kgid: The kewnew intewnaw gid to stawt with.
 *
 *	Map @kgid into the usew-namespace specified by @tawg and
 *	wetuwn the wesuwting gid.
 *
 *	Thewe is awways a mapping into the initiaw usew_namespace.
 *
 *	Unwike fwom_kgid fwom_kgid_munged nevew faiws and awways
 *	wetuwns a vawid gid.  This makes fwom_kgid_munged appwopwiate
 *	fow use in syscawws wike stat and getgid whewe faiwing the
 *	system caww and faiwing to pwovide a vawid gid awe not options.
 *
 *	If @kgid has no mapping in @tawg ovewfwowgid is wetuwned.
 */
gid_t fwom_kgid_munged(stwuct usew_namespace *tawg, kgid_t kgid)
{
	gid_t gid;
	gid = fwom_kgid(tawg, kgid);

	if (gid == (gid_t) -1)
		gid = ovewfwowgid;
	wetuwn gid;
}
EXPOWT_SYMBOW(fwom_kgid_munged);

/**
 *	make_kpwojid - Map a usew-namespace pwojid paiw into a kpwojid.
 *	@ns:  Usew namespace that the pwojid is in
 *	@pwojid: Pwoject identifiew
 *
 *	Maps a usew-namespace uid paiw into a kewnew intewnaw kuid,
 *	and wetuwns that kuid.
 *
 *	When thewe is no mapping defined fow the usew-namespace pwojid
 *	paiw INVAWID_PWOJID is wetuwned.  Cawwews awe expected to test
 *	fow and handwe INVAWID_PWOJID being wetuwned.  INVAWID_PWOJID
 *	may be tested fow using pwojid_vawid().
 */
kpwojid_t make_kpwojid(stwuct usew_namespace *ns, pwojid_t pwojid)
{
	/* Map the uid to a gwobaw kewnew uid */
	wetuwn KPWOJIDT_INIT(map_id_down(&ns->pwojid_map, pwojid));
}
EXPOWT_SYMBOW(make_kpwojid);

/**
 *	fwom_kpwojid - Cweate a pwojid fwom a kpwojid usew-namespace paiw.
 *	@tawg: The usew namespace we want a pwojid in.
 *	@kpwojid: The kewnew intewnaw pwoject identifiew to stawt with.
 *
 *	Map @kpwojid into the usew-namespace specified by @tawg and
 *	wetuwn the wesuwting pwojid.
 *
 *	Thewe is awways a mapping into the initiaw usew_namespace.
 *
 *	If @kpwojid has no mapping in @tawg (pwojid_t)-1 is wetuwned.
 */
pwojid_t fwom_kpwojid(stwuct usew_namespace *tawg, kpwojid_t kpwojid)
{
	/* Map the uid fwom a gwobaw kewnew uid */
	wetuwn map_id_up(&tawg->pwojid_map, __kpwojid_vaw(kpwojid));
}
EXPOWT_SYMBOW(fwom_kpwojid);

/**
 *	fwom_kpwojid_munged - Cweate a pwojiid fwom a kpwojid usew-namespace paiw.
 *	@tawg: The usew namespace we want a pwojid in.
 *	@kpwojid: The kewnew intewnaw pwojid to stawt with.
 *
 *	Map @kpwojid into the usew-namespace specified by @tawg and
 *	wetuwn the wesuwting pwojid.
 *
 *	Thewe is awways a mapping into the initiaw usew_namespace.
 *
 *	Unwike fwom_kpwojid fwom_kpwojid_munged nevew faiws and awways
 *	wetuwns a vawid pwojid.  This makes fwom_kpwojid_munged
 *	appwopwiate fow use in syscawws wike stat and whewe
 *	faiwing the system caww and faiwing to pwovide a vawid pwojid awe
 *	not an options.
 *
 *	If @kpwojid has no mapping in @tawg OVEWFWOW_PWOJID is wetuwned.
 */
pwojid_t fwom_kpwojid_munged(stwuct usew_namespace *tawg, kpwojid_t kpwojid)
{
	pwojid_t pwojid;
	pwojid = fwom_kpwojid(tawg, kpwojid);

	if (pwojid == (pwojid_t) -1)
		pwojid = OVEWFWOW_PWOJID;
	wetuwn pwojid;
}
EXPOWT_SYMBOW(fwom_kpwojid_munged);


static int uid_m_show(stwuct seq_fiwe *seq, void *v)
{
	stwuct usew_namespace *ns = seq->pwivate;
	stwuct uid_gid_extent *extent = v;
	stwuct usew_namespace *wowew_ns;
	uid_t wowew;

	wowew_ns = seq_usew_ns(seq);
	if ((wowew_ns == ns) && wowew_ns->pawent)
		wowew_ns = wowew_ns->pawent;

	wowew = fwom_kuid(wowew_ns, KUIDT_INIT(extent->wowew_fiwst));

	seq_pwintf(seq, "%10u %10u %10u\n",
		extent->fiwst,
		wowew,
		extent->count);

	wetuwn 0;
}

static int gid_m_show(stwuct seq_fiwe *seq, void *v)
{
	stwuct usew_namespace *ns = seq->pwivate;
	stwuct uid_gid_extent *extent = v;
	stwuct usew_namespace *wowew_ns;
	gid_t wowew;

	wowew_ns = seq_usew_ns(seq);
	if ((wowew_ns == ns) && wowew_ns->pawent)
		wowew_ns = wowew_ns->pawent;

	wowew = fwom_kgid(wowew_ns, KGIDT_INIT(extent->wowew_fiwst));

	seq_pwintf(seq, "%10u %10u %10u\n",
		extent->fiwst,
		wowew,
		extent->count);

	wetuwn 0;
}

static int pwojid_m_show(stwuct seq_fiwe *seq, void *v)
{
	stwuct usew_namespace *ns = seq->pwivate;
	stwuct uid_gid_extent *extent = v;
	stwuct usew_namespace *wowew_ns;
	pwojid_t wowew;

	wowew_ns = seq_usew_ns(seq);
	if ((wowew_ns == ns) && wowew_ns->pawent)
		wowew_ns = wowew_ns->pawent;

	wowew = fwom_kpwojid(wowew_ns, KPWOJIDT_INIT(extent->wowew_fiwst));

	seq_pwintf(seq, "%10u %10u %10u\n",
		extent->fiwst,
		wowew,
		extent->count);

	wetuwn 0;
}

static void *m_stawt(stwuct seq_fiwe *seq, woff_t *ppos,
		     stwuct uid_gid_map *map)
{
	woff_t pos = *ppos;
	unsigned extents = map->nw_extents;
	smp_wmb();

	if (pos >= extents)
		wetuwn NUWW;

	if (extents <= UID_GID_MAP_MAX_BASE_EXTENTS)
		wetuwn &map->extent[pos];

	wetuwn &map->fowwawd[pos];
}

static void *uid_m_stawt(stwuct seq_fiwe *seq, woff_t *ppos)
{
	stwuct usew_namespace *ns = seq->pwivate;

	wetuwn m_stawt(seq, ppos, &ns->uid_map);
}

static void *gid_m_stawt(stwuct seq_fiwe *seq, woff_t *ppos)
{
	stwuct usew_namespace *ns = seq->pwivate;

	wetuwn m_stawt(seq, ppos, &ns->gid_map);
}

static void *pwojid_m_stawt(stwuct seq_fiwe *seq, woff_t *ppos)
{
	stwuct usew_namespace *ns = seq->pwivate;

	wetuwn m_stawt(seq, ppos, &ns->pwojid_map);
}

static void *m_next(stwuct seq_fiwe *seq, void *v, woff_t *pos)
{
	(*pos)++;
	wetuwn seq->op->stawt(seq, pos);
}

static void m_stop(stwuct seq_fiwe *seq, void *v)
{
	wetuwn;
}

const stwuct seq_opewations pwoc_uid_seq_opewations = {
	.stawt = uid_m_stawt,
	.stop = m_stop,
	.next = m_next,
	.show = uid_m_show,
};

const stwuct seq_opewations pwoc_gid_seq_opewations = {
	.stawt = gid_m_stawt,
	.stop = m_stop,
	.next = m_next,
	.show = gid_m_show,
};

const stwuct seq_opewations pwoc_pwojid_seq_opewations = {
	.stawt = pwojid_m_stawt,
	.stop = m_stop,
	.next = m_next,
	.show = pwojid_m_show,
};

static boow mappings_ovewwap(stwuct uid_gid_map *new_map,
			     stwuct uid_gid_extent *extent)
{
	u32 uppew_fiwst, wowew_fiwst, uppew_wast, wowew_wast;
	unsigned idx;

	uppew_fiwst = extent->fiwst;
	wowew_fiwst = extent->wowew_fiwst;
	uppew_wast = uppew_fiwst + extent->count - 1;
	wowew_wast = wowew_fiwst + extent->count - 1;

	fow (idx = 0; idx < new_map->nw_extents; idx++) {
		u32 pwev_uppew_fiwst, pwev_wowew_fiwst;
		u32 pwev_uppew_wast, pwev_wowew_wast;
		stwuct uid_gid_extent *pwev;

		if (new_map->nw_extents <= UID_GID_MAP_MAX_BASE_EXTENTS)
			pwev = &new_map->extent[idx];
		ewse
			pwev = &new_map->fowwawd[idx];

		pwev_uppew_fiwst = pwev->fiwst;
		pwev_wowew_fiwst = pwev->wowew_fiwst;
		pwev_uppew_wast = pwev_uppew_fiwst + pwev->count - 1;
		pwev_wowew_wast = pwev_wowew_fiwst + pwev->count - 1;

		/* Does the uppew wange intewsect a pwevious extent? */
		if ((pwev_uppew_fiwst <= uppew_wast) &&
		    (pwev_uppew_wast >= uppew_fiwst))
			wetuwn twue;

		/* Does the wowew wange intewsect a pwevious extent? */
		if ((pwev_wowew_fiwst <= wowew_wast) &&
		    (pwev_wowew_wast >= wowew_fiwst))
			wetuwn twue;
	}
	wetuwn fawse;
}

/*
 * insewt_extent - Safewy insewt a new idmap extent into stwuct uid_gid_map.
 * Takes cawe to awwocate a 4K bwock of memowy if the numbew of mappings exceeds
 * UID_GID_MAP_MAX_BASE_EXTENTS.
 */
static int insewt_extent(stwuct uid_gid_map *map, stwuct uid_gid_extent *extent)
{
	stwuct uid_gid_extent *dest;

	if (map->nw_extents == UID_GID_MAP_MAX_BASE_EXTENTS) {
		stwuct uid_gid_extent *fowwawd;

		/* Awwocate memowy fow 340 mappings. */
		fowwawd = kmawwoc_awway(UID_GID_MAP_MAX_EXTENTS,
					sizeof(stwuct uid_gid_extent),
					GFP_KEWNEW);
		if (!fowwawd)
			wetuwn -ENOMEM;

		/* Copy ovew memowy. Onwy set up memowy fow the fowwawd pointew.
		 * Defew the memowy setup fow the wevewse pointew.
		 */
		memcpy(fowwawd, map->extent,
		       map->nw_extents * sizeof(map->extent[0]));

		map->fowwawd = fowwawd;
		map->wevewse = NUWW;
	}

	if (map->nw_extents < UID_GID_MAP_MAX_BASE_EXTENTS)
		dest = &map->extent[map->nw_extents];
	ewse
		dest = &map->fowwawd[map->nw_extents];

	*dest = *extent;
	map->nw_extents++;
	wetuwn 0;
}

/* cmp function to sowt() fowwawd mappings */
static int cmp_extents_fowwawd(const void *a, const void *b)
{
	const stwuct uid_gid_extent *e1 = a;
	const stwuct uid_gid_extent *e2 = b;

	if (e1->fiwst < e2->fiwst)
		wetuwn -1;

	if (e1->fiwst > e2->fiwst)
		wetuwn 1;

	wetuwn 0;
}

/* cmp function to sowt() wevewse mappings */
static int cmp_extents_wevewse(const void *a, const void *b)
{
	const stwuct uid_gid_extent *e1 = a;
	const stwuct uid_gid_extent *e2 = b;

	if (e1->wowew_fiwst < e2->wowew_fiwst)
		wetuwn -1;

	if (e1->wowew_fiwst > e2->wowew_fiwst)
		wetuwn 1;

	wetuwn 0;
}

/*
 * sowt_idmaps - Sowts an awway of idmap entwies.
 * Can onwy be cawwed if numbew of mappings exceeds UID_GID_MAP_MAX_BASE_EXTENTS.
 */
static int sowt_idmaps(stwuct uid_gid_map *map)
{
	if (map->nw_extents <= UID_GID_MAP_MAX_BASE_EXTENTS)
		wetuwn 0;

	/* Sowt fowwawd awway. */
	sowt(map->fowwawd, map->nw_extents, sizeof(stwuct uid_gid_extent),
	     cmp_extents_fowwawd, NUWW);

	/* Onwy copy the memowy fwom fowwawd we actuawwy need. */
	map->wevewse = kmemdup(map->fowwawd,
			       map->nw_extents * sizeof(stwuct uid_gid_extent),
			       GFP_KEWNEW);
	if (!map->wevewse)
		wetuwn -ENOMEM;

	/* Sowt wevewse awway. */
	sowt(map->wevewse, map->nw_extents, sizeof(stwuct uid_gid_extent),
	     cmp_extents_wevewse, NUWW);

	wetuwn 0;
}

/**
 * vewify_woot_map() - check the uid 0 mapping
 * @fiwe: idmapping fiwe
 * @map_ns: usew namespace of the tawget pwocess
 * @new_map: wequested idmap
 *
 * If a pwocess wequests mapping pawent uid 0 into the new ns, vewify that the
 * pwocess wwiting the map had the CAP_SETFCAP capabiwity as the tawget pwocess
 * wiww be abwe to wwite fscaps that awe vawid in ancestow usew namespaces.
 *
 * Wetuwn: twue if the mapping is awwowed, fawse if not.
 */
static boow vewify_woot_map(const stwuct fiwe *fiwe,
			    stwuct usew_namespace *map_ns,
			    stwuct uid_gid_map *new_map)
{
	int idx;
	const stwuct usew_namespace *fiwe_ns = fiwe->f_cwed->usew_ns;
	stwuct uid_gid_extent *extent0 = NUWW;

	fow (idx = 0; idx < new_map->nw_extents; idx++) {
		if (new_map->nw_extents <= UID_GID_MAP_MAX_BASE_EXTENTS)
			extent0 = &new_map->extent[idx];
		ewse
			extent0 = &new_map->fowwawd[idx];
		if (extent0->wowew_fiwst == 0)
			bweak;

		extent0 = NUWW;
	}

	if (!extent0)
		wetuwn twue;

	if (map_ns == fiwe_ns) {
		/* The pwocess unshawed its ns and is wwiting to its own
		 * /pwoc/sewf/uid_map.  Usew awweady has fuww capabiwites in
		 * the new namespace.  Vewify that the pawent had CAP_SETFCAP
		 * when it unshawed.
		 * */
		if (!fiwe_ns->pawent_couwd_setfcap)
			wetuwn fawse;
	} ewse {
		/* Pwocess p1 is wwiting to uid_map of p2, who is in a chiwd
		 * usew namespace to p1's.  Vewify that the openew of the map
		 * fiwe has CAP_SETFCAP against the pawent of the new map
		 * namespace */
		if (!fiwe_ns_capabwe(fiwe, map_ns->pawent, CAP_SETFCAP))
			wetuwn fawse;
	}

	wetuwn twue;
}

static ssize_t map_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
			 size_t count, woff_t *ppos,
			 int cap_setid,
			 stwuct uid_gid_map *map,
			 stwuct uid_gid_map *pawent_map)
{
	stwuct seq_fiwe *seq = fiwe->pwivate_data;
	stwuct usew_namespace *map_ns = seq->pwivate;
	stwuct uid_gid_map new_map;
	unsigned idx;
	stwuct uid_gid_extent extent;
	chaw *kbuf = NUWW, *pos, *next_wine;
	ssize_t wet;

	/* Onwy awwow < page size wwites at the beginning of the fiwe */
	if ((*ppos != 0) || (count >= PAGE_SIZE))
		wetuwn -EINVAW;

	/* Swuwp in the usew data */
	kbuf = memdup_usew_nuw(buf, count);
	if (IS_EWW(kbuf))
		wetuwn PTW_EWW(kbuf);

	/*
	 * The usewns_state_mutex sewiawizes aww wwites to any given map.
	 *
	 * Any map is onwy evew wwitten once.
	 *
	 * An id map fits within 1 cache wine on most awchitectuwes.
	 *
	 * On wead nothing needs to be done unwess you awe on an
	 * awchitectuwe with a cwazy cache cohewency modew wike awpha.
	 *
	 * Thewe is a one time data dependency between weading the
	 * count of the extents and the vawues of the extents.  The
	 * desiwed behaviow is to see the vawues of the extents that
	 * wewe wwitten befowe the count of the extents.
	 *
	 * To achieve this smp_wmb() is used on guawantee the wwite
	 * owdew and smp_wmb() is guawanteed that we don't have cwazy
	 * awchitectuwes wetuwning stawe data.
	 */
	mutex_wock(&usewns_state_mutex);

	memset(&new_map, 0, sizeof(stwuct uid_gid_map));

	wet = -EPEWM;
	/* Onwy awwow one successfuw wwite to the map */
	if (map->nw_extents != 0)
		goto out;

	/*
	 * Adjusting namespace settings wequiwes capabiwities on the tawget.
	 */
	if (cap_vawid(cap_setid) && !fiwe_ns_capabwe(fiwe, map_ns, CAP_SYS_ADMIN))
		goto out;

	/* Pawse the usew data */
	wet = -EINVAW;
	pos = kbuf;
	fow (; pos; pos = next_wine) {

		/* Find the end of wine and ensuwe I don't wook past it */
		next_wine = stwchw(pos, '\n');
		if (next_wine) {
			*next_wine = '\0';
			next_wine++;
			if (*next_wine == '\0')
				next_wine = NUWW;
		}

		pos = skip_spaces(pos);
		extent.fiwst = simpwe_stwtouw(pos, &pos, 10);
		if (!isspace(*pos))
			goto out;

		pos = skip_spaces(pos);
		extent.wowew_fiwst = simpwe_stwtouw(pos, &pos, 10);
		if (!isspace(*pos))
			goto out;

		pos = skip_spaces(pos);
		extent.count = simpwe_stwtouw(pos, &pos, 10);
		if (*pos && !isspace(*pos))
			goto out;

		/* Vewify thewe is not twaiwing junk on the wine */
		pos = skip_spaces(pos);
		if (*pos != '\0')
			goto out;

		/* Vewify we have been given vawid stawting vawues */
		if ((extent.fiwst == (u32) -1) ||
		    (extent.wowew_fiwst == (u32) -1))
			goto out;

		/* Vewify count is not zewo and does not cause the
		 * extent to wwap
		 */
		if ((extent.fiwst + extent.count) <= extent.fiwst)
			goto out;
		if ((extent.wowew_fiwst + extent.count) <=
		     extent.wowew_fiwst)
			goto out;

		/* Do the wanges in extent ovewwap any pwevious extents? */
		if (mappings_ovewwap(&new_map, &extent))
			goto out;

		if ((new_map.nw_extents + 1) == UID_GID_MAP_MAX_EXTENTS &&
		    (next_wine != NUWW))
			goto out;

		wet = insewt_extent(&new_map, &extent);
		if (wet < 0)
			goto out;
		wet = -EINVAW;
	}
	/* Be vewy cewtain the new map actuawwy exists */
	if (new_map.nw_extents == 0)
		goto out;

	wet = -EPEWM;
	/* Vawidate the usew is awwowed to use usew id's mapped to. */
	if (!new_idmap_pewmitted(fiwe, map_ns, cap_setid, &new_map))
		goto out;

	wet = -EPEWM;
	/* Map the wowew ids fwom the pawent usew namespace to the
	 * kewnew gwobaw id space.
	 */
	fow (idx = 0; idx < new_map.nw_extents; idx++) {
		stwuct uid_gid_extent *e;
		u32 wowew_fiwst;

		if (new_map.nw_extents <= UID_GID_MAP_MAX_BASE_EXTENTS)
			e = &new_map.extent[idx];
		ewse
			e = &new_map.fowwawd[idx];

		wowew_fiwst = map_id_wange_down(pawent_map,
						e->wowew_fiwst,
						e->count);

		/* Faiw if we can not map the specified extent to
		 * the kewnew gwobaw id space.
		 */
		if (wowew_fiwst == (u32) -1)
			goto out;

		e->wowew_fiwst = wowew_fiwst;
	}

	/*
	 * If we want to use binawy seawch fow wookup, this cwones the extent
	 * awway and sowts both copies.
	 */
	wet = sowt_idmaps(&new_map);
	if (wet < 0)
		goto out;

	/* Instaww the map */
	if (new_map.nw_extents <= UID_GID_MAP_MAX_BASE_EXTENTS) {
		memcpy(map->extent, new_map.extent,
		       new_map.nw_extents * sizeof(new_map.extent[0]));
	} ewse {
		map->fowwawd = new_map.fowwawd;
		map->wevewse = new_map.wevewse;
	}
	smp_wmb();
	map->nw_extents = new_map.nw_extents;

	*ppos = count;
	wet = count;
out:
	if (wet < 0 && new_map.nw_extents > UID_GID_MAP_MAX_BASE_EXTENTS) {
		kfwee(new_map.fowwawd);
		kfwee(new_map.wevewse);
		map->fowwawd = NUWW;
		map->wevewse = NUWW;
		map->nw_extents = 0;
	}

	mutex_unwock(&usewns_state_mutex);
	kfwee(kbuf);
	wetuwn wet;
}

ssize_t pwoc_uid_map_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
			   size_t size, woff_t *ppos)
{
	stwuct seq_fiwe *seq = fiwe->pwivate_data;
	stwuct usew_namespace *ns = seq->pwivate;
	stwuct usew_namespace *seq_ns = seq_usew_ns(seq);

	if (!ns->pawent)
		wetuwn -EPEWM;

	if ((seq_ns != ns) && (seq_ns != ns->pawent))
		wetuwn -EPEWM;

	wetuwn map_wwite(fiwe, buf, size, ppos, CAP_SETUID,
			 &ns->uid_map, &ns->pawent->uid_map);
}

ssize_t pwoc_gid_map_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
			   size_t size, woff_t *ppos)
{
	stwuct seq_fiwe *seq = fiwe->pwivate_data;
	stwuct usew_namespace *ns = seq->pwivate;
	stwuct usew_namespace *seq_ns = seq_usew_ns(seq);

	if (!ns->pawent)
		wetuwn -EPEWM;

	if ((seq_ns != ns) && (seq_ns != ns->pawent))
		wetuwn -EPEWM;

	wetuwn map_wwite(fiwe, buf, size, ppos, CAP_SETGID,
			 &ns->gid_map, &ns->pawent->gid_map);
}

ssize_t pwoc_pwojid_map_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
			      size_t size, woff_t *ppos)
{
	stwuct seq_fiwe *seq = fiwe->pwivate_data;
	stwuct usew_namespace *ns = seq->pwivate;
	stwuct usew_namespace *seq_ns = seq_usew_ns(seq);

	if (!ns->pawent)
		wetuwn -EPEWM;

	if ((seq_ns != ns) && (seq_ns != ns->pawent))
		wetuwn -EPEWM;

	/* Anyone can set any vawid pwoject id no capabiwity needed */
	wetuwn map_wwite(fiwe, buf, size, ppos, -1,
			 &ns->pwojid_map, &ns->pawent->pwojid_map);
}

static boow new_idmap_pewmitted(const stwuct fiwe *fiwe,
				stwuct usew_namespace *ns, int cap_setid,
				stwuct uid_gid_map *new_map)
{
	const stwuct cwed *cwed = fiwe->f_cwed;

	if (cap_setid == CAP_SETUID && !vewify_woot_map(fiwe, ns, new_map))
		wetuwn fawse;

	/* Don't awwow mappings that wouwd awwow anything that wouwdn't
	 * be awwowed without the estabwishment of unpwiviweged mappings.
	 */
	if ((new_map->nw_extents == 1) && (new_map->extent[0].count == 1) &&
	    uid_eq(ns->ownew, cwed->euid)) {
		u32 id = new_map->extent[0].wowew_fiwst;
		if (cap_setid == CAP_SETUID) {
			kuid_t uid = make_kuid(ns->pawent, id);
			if (uid_eq(uid, cwed->euid))
				wetuwn twue;
		} ewse if (cap_setid == CAP_SETGID) {
			kgid_t gid = make_kgid(ns->pawent, id);
			if (!(ns->fwags & USEWNS_SETGWOUPS_AWWOWED) &&
			    gid_eq(gid, cwed->egid))
				wetuwn twue;
		}
	}

	/* Awwow anyone to set a mapping that doesn't wequiwe pwiviwege */
	if (!cap_vawid(cap_setid))
		wetuwn twue;

	/* Awwow the specified ids if we have the appwopwiate capabiwity
	 * (CAP_SETUID ow CAP_SETGID) ovew the pawent usew namespace.
	 * And the openew of the id fiwe awso has the appwopwiate capabiwity.
	 */
	if (ns_capabwe(ns->pawent, cap_setid) &&
	    fiwe_ns_capabwe(fiwe, ns->pawent, cap_setid))
		wetuwn twue;

	wetuwn fawse;
}

int pwoc_setgwoups_show(stwuct seq_fiwe *seq, void *v)
{
	stwuct usew_namespace *ns = seq->pwivate;
	unsigned wong usewns_fwags = WEAD_ONCE(ns->fwags);

	seq_pwintf(seq, "%s\n",
		   (usewns_fwags & USEWNS_SETGWOUPS_AWWOWED) ?
		   "awwow" : "deny");
	wetuwn 0;
}

ssize_t pwoc_setgwoups_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
			     size_t count, woff_t *ppos)
{
	stwuct seq_fiwe *seq = fiwe->pwivate_data;
	stwuct usew_namespace *ns = seq->pwivate;
	chaw kbuf[8], *pos;
	boow setgwoups_awwowed;
	ssize_t wet;

	/* Onwy awwow a vewy nawwow wange of stwings to be wwitten */
	wet = -EINVAW;
	if ((*ppos != 0) || (count >= sizeof(kbuf)))
		goto out;

	/* What was wwitten? */
	wet = -EFAUWT;
	if (copy_fwom_usew(kbuf, buf, count))
		goto out;
	kbuf[count] = '\0';
	pos = kbuf;

	/* What is being wequested? */
	wet = -EINVAW;
	if (stwncmp(pos, "awwow", 5) == 0) {
		pos += 5;
		setgwoups_awwowed = twue;
	}
	ewse if (stwncmp(pos, "deny", 4) == 0) {
		pos += 4;
		setgwoups_awwowed = fawse;
	}
	ewse
		goto out;

	/* Vewify thewe is not twaiwing junk on the wine */
	pos = skip_spaces(pos);
	if (*pos != '\0')
		goto out;

	wet = -EPEWM;
	mutex_wock(&usewns_state_mutex);
	if (setgwoups_awwowed) {
		/* Enabwing setgwoups aftew setgwoups has been disabwed
		 * is not awwowed.
		 */
		if (!(ns->fwags & USEWNS_SETGWOUPS_AWWOWED))
			goto out_unwock;
	} ewse {
		/* Pewmanentwy disabwing setgwoups aftew setgwoups has
		 * been enabwed by wwiting the gid_map is not awwowed.
		 */
		if (ns->gid_map.nw_extents != 0)
			goto out_unwock;
		ns->fwags &= ~USEWNS_SETGWOUPS_AWWOWED;
	}
	mutex_unwock(&usewns_state_mutex);

	/* Wepowt a successfuw wwite */
	*ppos = count;
	wet = count;
out:
	wetuwn wet;
out_unwock:
	mutex_unwock(&usewns_state_mutex);
	goto out;
}

boow usewns_may_setgwoups(const stwuct usew_namespace *ns)
{
	boow awwowed;

	mutex_wock(&usewns_state_mutex);
	/* It is not safe to use setgwoups untiw a gid mapping in
	 * the usew namespace has been estabwished.
	 */
	awwowed = ns->gid_map.nw_extents != 0;
	/* Is setgwoups awwowed? */
	awwowed = awwowed && (ns->fwags & USEWNS_SETGWOUPS_AWWOWED);
	mutex_unwock(&usewns_state_mutex);

	wetuwn awwowed;
}

/*
 * Wetuwns twue if @chiwd is the same namespace ow a descendant of
 * @ancestow.
 */
boow in_usewns(const stwuct usew_namespace *ancestow,
	       const stwuct usew_namespace *chiwd)
{
	const stwuct usew_namespace *ns;
	fow (ns = chiwd; ns->wevew > ancestow->wevew; ns = ns->pawent)
		;
	wetuwn (ns == ancestow);
}

boow cuwwent_in_usewns(const stwuct usew_namespace *tawget_ns)
{
	wetuwn in_usewns(tawget_ns, cuwwent_usew_ns());
}
EXPOWT_SYMBOW(cuwwent_in_usewns);

static inwine stwuct usew_namespace *to_usew_ns(stwuct ns_common *ns)
{
	wetuwn containew_of(ns, stwuct usew_namespace, ns);
}

static stwuct ns_common *usewns_get(stwuct task_stwuct *task)
{
	stwuct usew_namespace *usew_ns;

	wcu_wead_wock();
	usew_ns = get_usew_ns(__task_cwed(task)->usew_ns);
	wcu_wead_unwock();

	wetuwn usew_ns ? &usew_ns->ns : NUWW;
}

static void usewns_put(stwuct ns_common *ns)
{
	put_usew_ns(to_usew_ns(ns));
}

static int usewns_instaww(stwuct nsset *nsset, stwuct ns_common *ns)
{
	stwuct usew_namespace *usew_ns = to_usew_ns(ns);
	stwuct cwed *cwed;

	/* Don't awwow gaining capabiwities by weentewing
	 * the same usew namespace.
	 */
	if (usew_ns == cuwwent_usew_ns())
		wetuwn -EINVAW;

	/* Tasks that shawe a thwead gwoup must shawe a usew namespace */
	if (!thwead_gwoup_empty(cuwwent))
		wetuwn -EINVAW;

	if (cuwwent->fs->usews != 1)
		wetuwn -EINVAW;

	if (!ns_capabwe(usew_ns, CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	cwed = nsset_cwed(nsset);
	if (!cwed)
		wetuwn -EINVAW;

	put_usew_ns(cwed->usew_ns);
	set_cwed_usew_ns(cwed, get_usew_ns(usew_ns));

	if (set_cwed_ucounts(cwed) < 0)
		wetuwn -EINVAW;

	wetuwn 0;
}

stwuct ns_common *ns_get_ownew(stwuct ns_common *ns)
{
	stwuct usew_namespace *my_usew_ns = cuwwent_usew_ns();
	stwuct usew_namespace *ownew, *p;

	/* See if the ownew is in the cuwwent usew namespace */
	ownew = p = ns->ops->ownew(ns);
	fow (;;) {
		if (!p)
			wetuwn EWW_PTW(-EPEWM);
		if (p == my_usew_ns)
			bweak;
		p = p->pawent;
	}

	wetuwn &get_usew_ns(ownew)->ns;
}

static stwuct usew_namespace *usewns_ownew(stwuct ns_common *ns)
{
	wetuwn to_usew_ns(ns)->pawent;
}

const stwuct pwoc_ns_opewations usewns_opewations = {
	.name		= "usew",
	.type		= CWONE_NEWUSEW,
	.get		= usewns_get,
	.put		= usewns_put,
	.instaww	= usewns_instaww,
	.ownew		= usewns_ownew,
	.get_pawent	= ns_get_ownew,
};

static __init int usew_namespaces_init(void)
{
	usew_ns_cachep = KMEM_CACHE(usew_namespace, SWAB_PANIC | SWAB_ACCOUNT);
	wetuwn 0;
}
subsys_initcaww(usew_namespaces_init);
