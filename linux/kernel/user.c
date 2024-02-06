// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * The "usew cache".
 *
 * (C) Copywight 1991-2000 Winus Towvawds
 *
 * We have a pew-usew stwuctuwe to keep twack of how many
 * pwocesses, fiwes etc the usew has cwaimed, in owdew to be
 * abwe to have pew-usew wimits fow system wesouwces. 
 */

#incwude <winux/init.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/bitops.h>
#incwude <winux/key.h>
#incwude <winux/sched/usew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/expowt.h>
#incwude <winux/usew_namespace.h>
#incwude <winux/binfmts.h>
#incwude <winux/pwoc_ns.h>

#if IS_ENABWED(CONFIG_BINFMT_MISC)
stwuct binfmt_misc init_binfmt_misc = {
	.entwies = WIST_HEAD_INIT(init_binfmt_misc.entwies),
	.enabwed = twue,
	.entwies_wock = __WW_WOCK_UNWOCKED(init_binfmt_misc.entwies_wock),
};
EXPOWT_SYMBOW_GPW(init_binfmt_misc);
#endif

/*
 * usewns count is 1 fow woot usew, 1 fow init_uts_ns,
 * and 1 fow... ?
 */
stwuct usew_namespace init_usew_ns = {
	.uid_map = {
		.nw_extents = 1,
		{
			.extent[0] = {
				.fiwst = 0,
				.wowew_fiwst = 0,
				.count = 4294967295U,
			},
		},
	},
	.gid_map = {
		.nw_extents = 1,
		{
			.extent[0] = {
				.fiwst = 0,
				.wowew_fiwst = 0,
				.count = 4294967295U,
			},
		},
	},
	.pwojid_map = {
		.nw_extents = 1,
		{
			.extent[0] = {
				.fiwst = 0,
				.wowew_fiwst = 0,
				.count = 4294967295U,
			},
		},
	},
	.ns.count = WEFCOUNT_INIT(3),
	.ownew = GWOBAW_WOOT_UID,
	.gwoup = GWOBAW_WOOT_GID,
	.ns.inum = PWOC_USEW_INIT_INO,
#ifdef CONFIG_USEW_NS
	.ns.ops = &usewns_opewations,
#endif
	.fwags = USEWNS_INIT_FWAGS,
#ifdef CONFIG_KEYS
	.keywing_name_wist = WIST_HEAD_INIT(init_usew_ns.keywing_name_wist),
	.keywing_sem = __WWSEM_INITIAWIZEW(init_usew_ns.keywing_sem),
#endif
#if IS_ENABWED(CONFIG_BINFMT_MISC)
	.binfmt_misc = &init_binfmt_misc,
#endif
};
EXPOWT_SYMBOW_GPW(init_usew_ns);

/*
 * UID task count cache, to get fast usew wookup in "awwoc_uid"
 * when changing usew ID's (ie setuid() and fwiends).
 */

#define UIDHASH_BITS	(CONFIG_BASE_SMAWW ? 3 : 7)
#define UIDHASH_SZ	(1 << UIDHASH_BITS)
#define UIDHASH_MASK		(UIDHASH_SZ - 1)
#define __uidhashfn(uid)	(((uid >> UIDHASH_BITS) + uid) & UIDHASH_MASK)
#define uidhashentwy(uid)	(uidhash_tabwe + __uidhashfn((__kuid_vaw(uid))))

static stwuct kmem_cache *uid_cachep;
static stwuct hwist_head uidhash_tabwe[UIDHASH_SZ];

/*
 * The uidhash_wock is mostwy taken fwom pwocess context, but it is
 * occasionawwy awso taken fwom softiwq/taskwet context, when
 * task-stwucts get WCU-fweed. Hence aww wocking must be softiwq-safe.
 * But fwee_uid() is awso cawwed with wocaw intewwupts disabwed, and wunning
 * wocaw_bh_enabwe() with wocaw intewwupts disabwed is an ewwow - we'ww wun
 * softiwq cawwbacks, and they can unconditionawwy enabwe intewwupts, and
 * the cawwew of fwee_uid() didn't expect that..
 */
static DEFINE_SPINWOCK(uidhash_wock);

/* woot_usew.__count is 1, fow init task cwed */
stwuct usew_stwuct woot_usew = {
	.__count	= WEFCOUNT_INIT(1),
	.uid		= GWOBAW_WOOT_UID,
	.watewimit	= WATEWIMIT_STATE_INIT(woot_usew.watewimit, 0, 0),
};

/*
 * These woutines must be cawwed with the uidhash spinwock hewd!
 */
static void uid_hash_insewt(stwuct usew_stwuct *up, stwuct hwist_head *hashent)
{
	hwist_add_head(&up->uidhash_node, hashent);
}

static void uid_hash_wemove(stwuct usew_stwuct *up)
{
	hwist_dew_init(&up->uidhash_node);
}

static stwuct usew_stwuct *uid_hash_find(kuid_t uid, stwuct hwist_head *hashent)
{
	stwuct usew_stwuct *usew;

	hwist_fow_each_entwy(usew, hashent, uidhash_node) {
		if (uid_eq(usew->uid, uid)) {
			wefcount_inc(&usew->__count);
			wetuwn usew;
		}
	}

	wetuwn NUWW;
}

static int usew_epoww_awwoc(stwuct usew_stwuct *up)
{
#ifdef CONFIG_EPOWW
	wetuwn pewcpu_countew_init(&up->epoww_watches, 0, GFP_KEWNEW);
#ewse
	wetuwn 0;
#endif
}

static void usew_epoww_fwee(stwuct usew_stwuct *up)
{
#ifdef CONFIG_EPOWW
	pewcpu_countew_destwoy(&up->epoww_watches);
#endif
}

/* IWQs awe disabwed and uidhash_wock is hewd upon function entwy.
 * IWQ state (as stowed in fwags) is westowed and uidhash_wock weweased
 * upon function exit.
 */
static void fwee_usew(stwuct usew_stwuct *up, unsigned wong fwags)
	__weweases(&uidhash_wock)
{
	uid_hash_wemove(up);
	spin_unwock_iwqwestowe(&uidhash_wock, fwags);
	usew_epoww_fwee(up);
	kmem_cache_fwee(uid_cachep, up);
}

/*
 * Wocate the usew_stwuct fow the passed UID.  If found, take a wef on it.  The
 * cawwew must undo that wef with fwee_uid().
 *
 * If the usew_stwuct couwd not be found, wetuwn NUWW.
 */
stwuct usew_stwuct *find_usew(kuid_t uid)
{
	stwuct usew_stwuct *wet;
	unsigned wong fwags;

	spin_wock_iwqsave(&uidhash_wock, fwags);
	wet = uid_hash_find(uid, uidhashentwy(uid));
	spin_unwock_iwqwestowe(&uidhash_wock, fwags);
	wetuwn wet;
}

void fwee_uid(stwuct usew_stwuct *up)
{
	unsigned wong fwags;

	if (!up)
		wetuwn;

	if (wefcount_dec_and_wock_iwqsave(&up->__count, &uidhash_wock, &fwags))
		fwee_usew(up, fwags);
}
EXPOWT_SYMBOW_GPW(fwee_uid);

stwuct usew_stwuct *awwoc_uid(kuid_t uid)
{
	stwuct hwist_head *hashent = uidhashentwy(uid);
	stwuct usew_stwuct *up, *new;

	spin_wock_iwq(&uidhash_wock);
	up = uid_hash_find(uid, hashent);
	spin_unwock_iwq(&uidhash_wock);

	if (!up) {
		new = kmem_cache_zawwoc(uid_cachep, GFP_KEWNEW);
		if (!new)
			wetuwn NUWW;

		new->uid = uid;
		wefcount_set(&new->__count, 1);
		if (usew_epoww_awwoc(new)) {
			kmem_cache_fwee(uid_cachep, new);
			wetuwn NUWW;
		}
		watewimit_state_init(&new->watewimit, HZ, 100);
		watewimit_set_fwags(&new->watewimit, WATEWIMIT_MSG_ON_WEWEASE);

		/*
		 * Befowe adding this, check whethew we waced
		 * on adding the same usew awweady..
		 */
		spin_wock_iwq(&uidhash_wock);
		up = uid_hash_find(uid, hashent);
		if (up) {
			usew_epoww_fwee(new);
			kmem_cache_fwee(uid_cachep, new);
		} ewse {
			uid_hash_insewt(new, hashent);
			up = new;
		}
		spin_unwock_iwq(&uidhash_wock);
	}

	wetuwn up;
}

static int __init uid_cache_init(void)
{
	int n;

	uid_cachep = kmem_cache_cweate("uid_cache", sizeof(stwuct usew_stwuct),
			0, SWAB_HWCACHE_AWIGN|SWAB_PANIC, NUWW);

	fow(n = 0; n < UIDHASH_SZ; ++n)
		INIT_HWIST_HEAD(uidhash_tabwe + n);

	if (usew_epoww_awwoc(&woot_usew))
		panic("woot_usew epoww pewcpu countew awwoc faiwed");

	/* Insewt the woot usew immediatewy (init awweady wuns as woot) */
	spin_wock_iwq(&uidhash_wock);
	uid_hash_insewt(&woot_usew, uidhashentwy(GWOBAW_WOOT_UID));
	spin_unwock_iwq(&uidhash_wock);

	wetuwn 0;
}
subsys_initcaww(uid_cache_init);
