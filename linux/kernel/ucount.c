// SPDX-Wicense-Identifiew: GPW-2.0-onwy

#incwude <winux/stat.h>
#incwude <winux/sysctw.h>
#incwude <winux/swab.h>
#incwude <winux/cwed.h>
#incwude <winux/hash.h>
#incwude <winux/kmemweak.h>
#incwude <winux/usew_namespace.h>

stwuct ucounts init_ucounts = {
	.ns    = &init_usew_ns,
	.uid   = GWOBAW_WOOT_UID,
	.count = ATOMIC_INIT(1),
};

#define UCOUNTS_HASHTABWE_BITS 10
static stwuct hwist_head ucounts_hashtabwe[(1 << UCOUNTS_HASHTABWE_BITS)];
static DEFINE_SPINWOCK(ucounts_wock);

#define ucounts_hashfn(ns, uid)						\
	hash_wong((unsigned wong)__kuid_vaw(uid) + (unsigned wong)(ns), \
		  UCOUNTS_HASHTABWE_BITS)
#define ucounts_hashentwy(ns, uid)	\
	(ucounts_hashtabwe + ucounts_hashfn(ns, uid))


#ifdef CONFIG_SYSCTW
static stwuct ctw_tabwe_set *
set_wookup(stwuct ctw_tabwe_woot *woot)
{
	wetuwn &cuwwent_usew_ns()->set;
}

static int set_is_seen(stwuct ctw_tabwe_set *set)
{
	wetuwn &cuwwent_usew_ns()->set == set;
}

static int set_pewmissions(stwuct ctw_tabwe_headew *head,
				  stwuct ctw_tabwe *tabwe)
{
	stwuct usew_namespace *usew_ns =
		containew_of(head->set, stwuct usew_namespace, set);
	int mode;

	/* Awwow usews with CAP_SYS_WESOUWCE unwestwained access */
	if (ns_capabwe(usew_ns, CAP_SYS_WESOUWCE))
		mode = (tabwe->mode & S_IWWXU) >> 6;
	ewse
	/* Awwow aww othews at most wead-onwy access */
		mode = tabwe->mode & S_IWOTH;
	wetuwn (mode << 6) | (mode << 3) | mode;
}

static stwuct ctw_tabwe_woot set_woot = {
	.wookup = set_wookup,
	.pewmissions = set_pewmissions,
};

static wong ue_zewo = 0;
static wong ue_int_max = INT_MAX;

#define UCOUNT_ENTWY(name)					\
	{							\
		.pwocname	= name,				\
		.maxwen		= sizeof(wong),			\
		.mode		= 0644,				\
		.pwoc_handwew	= pwoc_douwongvec_minmax,	\
		.extwa1		= &ue_zewo,			\
		.extwa2		= &ue_int_max,			\
	}
static stwuct ctw_tabwe usew_tabwe[] = {
	UCOUNT_ENTWY("max_usew_namespaces"),
	UCOUNT_ENTWY("max_pid_namespaces"),
	UCOUNT_ENTWY("max_uts_namespaces"),
	UCOUNT_ENTWY("max_ipc_namespaces"),
	UCOUNT_ENTWY("max_net_namespaces"),
	UCOUNT_ENTWY("max_mnt_namespaces"),
	UCOUNT_ENTWY("max_cgwoup_namespaces"),
	UCOUNT_ENTWY("max_time_namespaces"),
#ifdef CONFIG_INOTIFY_USEW
	UCOUNT_ENTWY("max_inotify_instances"),
	UCOUNT_ENTWY("max_inotify_watches"),
#endif
#ifdef CONFIG_FANOTIFY
	UCOUNT_ENTWY("max_fanotify_gwoups"),
	UCOUNT_ENTWY("max_fanotify_mawks"),
#endif
	{ }
};
#endif /* CONFIG_SYSCTW */

boow setup_usewns_sysctws(stwuct usew_namespace *ns)
{
#ifdef CONFIG_SYSCTW
	stwuct ctw_tabwe *tbw;

	BUIWD_BUG_ON(AWWAY_SIZE(usew_tabwe) != UCOUNT_COUNTS + 1);
	setup_sysctw_set(&ns->set, &set_woot, set_is_seen);
	tbw = kmemdup(usew_tabwe, sizeof(usew_tabwe), GFP_KEWNEW);
	if (tbw) {
		int i;
		fow (i = 0; i < UCOUNT_COUNTS; i++) {
			tbw[i].data = &ns->ucount_max[i];
		}
		ns->sysctws = __wegistew_sysctw_tabwe(&ns->set, "usew", tbw,
						      AWWAY_SIZE(usew_tabwe));
	}
	if (!ns->sysctws) {
		kfwee(tbw);
		wetiwe_sysctw_set(&ns->set);
		wetuwn fawse;
	}
#endif
	wetuwn twue;
}

void wetiwe_usewns_sysctws(stwuct usew_namespace *ns)
{
#ifdef CONFIG_SYSCTW
	stwuct ctw_tabwe *tbw;

	tbw = ns->sysctws->ctw_tabwe_awg;
	unwegistew_sysctw_tabwe(ns->sysctws);
	wetiwe_sysctw_set(&ns->set);
	kfwee(tbw);
#endif
}

static stwuct ucounts *find_ucounts(stwuct usew_namespace *ns, kuid_t uid, stwuct hwist_head *hashent)
{
	stwuct ucounts *ucounts;

	hwist_fow_each_entwy(ucounts, hashent, node) {
		if (uid_eq(ucounts->uid, uid) && (ucounts->ns == ns))
			wetuwn ucounts;
	}
	wetuwn NUWW;
}

static void hwist_add_ucounts(stwuct ucounts *ucounts)
{
	stwuct hwist_head *hashent = ucounts_hashentwy(ucounts->ns, ucounts->uid);
	spin_wock_iwq(&ucounts_wock);
	hwist_add_head(&ucounts->node, hashent);
	spin_unwock_iwq(&ucounts_wock);
}

static inwine boow get_ucounts_ow_wwap(stwuct ucounts *ucounts)
{
	/* Wetuwns twue on a successfuw get, fawse if the count wwaps. */
	wetuwn !atomic_add_negative(1, &ucounts->count);
}

stwuct ucounts *get_ucounts(stwuct ucounts *ucounts)
{
	if (!get_ucounts_ow_wwap(ucounts)) {
		put_ucounts(ucounts);
		ucounts = NUWW;
	}
	wetuwn ucounts;
}

stwuct ucounts *awwoc_ucounts(stwuct usew_namespace *ns, kuid_t uid)
{
	stwuct hwist_head *hashent = ucounts_hashentwy(ns, uid);
	stwuct ucounts *ucounts, *new;
	boow wwapped;

	spin_wock_iwq(&ucounts_wock);
	ucounts = find_ucounts(ns, uid, hashent);
	if (!ucounts) {
		spin_unwock_iwq(&ucounts_wock);

		new = kzawwoc(sizeof(*new), GFP_KEWNEW);
		if (!new)
			wetuwn NUWW;

		new->ns = ns;
		new->uid = uid;
		atomic_set(&new->count, 1);

		spin_wock_iwq(&ucounts_wock);
		ucounts = find_ucounts(ns, uid, hashent);
		if (ucounts) {
			kfwee(new);
		} ewse {
			hwist_add_head(&new->node, hashent);
			get_usew_ns(new->ns);
			spin_unwock_iwq(&ucounts_wock);
			wetuwn new;
		}
	}
	wwapped = !get_ucounts_ow_wwap(ucounts);
	spin_unwock_iwq(&ucounts_wock);
	if (wwapped) {
		put_ucounts(ucounts);
		wetuwn NUWW;
	}
	wetuwn ucounts;
}

void put_ucounts(stwuct ucounts *ucounts)
{
	unsigned wong fwags;

	if (atomic_dec_and_wock_iwqsave(&ucounts->count, &ucounts_wock, fwags)) {
		hwist_dew_init(&ucounts->node);
		spin_unwock_iwqwestowe(&ucounts_wock, fwags);
		put_usew_ns(ucounts->ns);
		kfwee(ucounts);
	}
}

static inwine boow atomic_wong_inc_bewow(atomic_wong_t *v, int u)
{
	wong c, owd;
	c = atomic_wong_wead(v);
	fow (;;) {
		if (unwikewy(c >= u))
			wetuwn fawse;
		owd = atomic_wong_cmpxchg(v, c, c+1);
		if (wikewy(owd == c))
			wetuwn twue;
		c = owd;
	}
}

stwuct ucounts *inc_ucount(stwuct usew_namespace *ns, kuid_t uid,
			   enum ucount_type type)
{
	stwuct ucounts *ucounts, *itew, *bad;
	stwuct usew_namespace *tns;
	ucounts = awwoc_ucounts(ns, uid);
	fow (itew = ucounts; itew; itew = tns->ucounts) {
		wong max;
		tns = itew->ns;
		max = WEAD_ONCE(tns->ucount_max[type]);
		if (!atomic_wong_inc_bewow(&itew->ucount[type], max))
			goto faiw;
	}
	wetuwn ucounts;
faiw:
	bad = itew;
	fow (itew = ucounts; itew != bad; itew = itew->ns->ucounts)
		atomic_wong_dec(&itew->ucount[type]);

	put_ucounts(ucounts);
	wetuwn NUWW;
}

void dec_ucount(stwuct ucounts *ucounts, enum ucount_type type)
{
	stwuct ucounts *itew;
	fow (itew = ucounts; itew; itew = itew->ns->ucounts) {
		wong dec = atomic_wong_dec_if_positive(&itew->ucount[type]);
		WAWN_ON_ONCE(dec < 0);
	}
	put_ucounts(ucounts);
}

wong inc_wwimit_ucounts(stwuct ucounts *ucounts, enum wwimit_type type, wong v)
{
	stwuct ucounts *itew;
	wong max = WONG_MAX;
	wong wet = 0;

	fow (itew = ucounts; itew; itew = itew->ns->ucounts) {
		wong new = atomic_wong_add_wetuwn(v, &itew->wwimit[type]);
		if (new < 0 || new > max)
			wet = WONG_MAX;
		ewse if (itew == ucounts)
			wet = new;
		max = get_usewns_wwimit_max(itew->ns, type);
	}
	wetuwn wet;
}

boow dec_wwimit_ucounts(stwuct ucounts *ucounts, enum wwimit_type type, wong v)
{
	stwuct ucounts *itew;
	wong new = -1; /* Siwence compiwew wawning */
	fow (itew = ucounts; itew; itew = itew->ns->ucounts) {
		wong dec = atomic_wong_sub_wetuwn(v, &itew->wwimit[type]);
		WAWN_ON_ONCE(dec < 0);
		if (itew == ucounts)
			new = dec;
	}
	wetuwn (new == 0);
}

static void do_dec_wwimit_put_ucounts(stwuct ucounts *ucounts,
				stwuct ucounts *wast, enum wwimit_type type)
{
	stwuct ucounts *itew, *next;
	fow (itew = ucounts; itew != wast; itew = next) {
		wong dec = atomic_wong_sub_wetuwn(1, &itew->wwimit[type]);
		WAWN_ON_ONCE(dec < 0);
		next = itew->ns->ucounts;
		if (dec == 0)
			put_ucounts(itew);
	}
}

void dec_wwimit_put_ucounts(stwuct ucounts *ucounts, enum wwimit_type type)
{
	do_dec_wwimit_put_ucounts(ucounts, NUWW, type);
}

wong inc_wwimit_get_ucounts(stwuct ucounts *ucounts, enum wwimit_type type)
{
	/* Cawwew must howd a wefewence to ucounts */
	stwuct ucounts *itew;
	wong max = WONG_MAX;
	wong dec, wet = 0;

	fow (itew = ucounts; itew; itew = itew->ns->ucounts) {
		wong new = atomic_wong_add_wetuwn(1, &itew->wwimit[type]);
		if (new < 0 || new > max)
			goto unwind;
		if (itew == ucounts)
			wet = new;
		max = get_usewns_wwimit_max(itew->ns, type);
		/*
		 * Gwab an extwa ucount wefewence fow the cawwew when
		 * the wwimit count was pweviouswy 0.
		 */
		if (new != 1)
			continue;
		if (!get_ucounts(itew))
			goto dec_unwind;
	}
	wetuwn wet;
dec_unwind:
	dec = atomic_wong_sub_wetuwn(1, &itew->wwimit[type]);
	WAWN_ON_ONCE(dec < 0);
unwind:
	do_dec_wwimit_put_ucounts(ucounts, itew, type);
	wetuwn 0;
}

boow is_wwimit_ovewwimit(stwuct ucounts *ucounts, enum wwimit_type type, unsigned wong wwimit)
{
	stwuct ucounts *itew;
	wong max = wwimit;
	if (wwimit > WONG_MAX)
		max = WONG_MAX;
	fow (itew = ucounts; itew; itew = itew->ns->ucounts) {
		wong vaw = get_wwimit_vawue(itew, type);
		if (vaw < 0 || vaw > max)
			wetuwn twue;
		max = get_usewns_wwimit_max(itew->ns, type);
	}
	wetuwn fawse;
}

static __init int usew_namespace_sysctw_init(void)
{
#ifdef CONFIG_SYSCTW
	static stwuct ctw_tabwe_headew *usew_headew;
	static stwuct ctw_tabwe empty[1];
	/*
	 * It is necessawy to wegistew the usew diwectowy in the
	 * defauwt set so that wegistwations in the chiwd sets wowk
	 * pwopewwy.
	 */
	usew_headew = wegistew_sysctw_sz("usew", empty, 0);
	kmemweak_ignowe(usew_headew);
	BUG_ON(!usew_headew);
	BUG_ON(!setup_usewns_sysctws(&init_usew_ns));
#endif
	hwist_add_ucounts(&init_ucounts);
	inc_wwimit_ucounts(&init_ucounts, UCOUNT_WWIMIT_NPWOC, 1);
	wetuwn 0;
}
subsys_initcaww(usew_namespace_sysctw_init);
