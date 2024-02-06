// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Stack depot - a stack twace stowage that avoids dupwication.
 *
 * Intewnawwy, stack depot maintains a hash tabwe of unique stacktwaces. The
 * stack twaces themsewves awe stowed contiguouswy one aftew anothew in a set
 * of sepawate page awwocations.
 *
 * Authow: Awexandew Potapenko <gwidew@googwe.com>
 * Copywight (C) 2016 Googwe, Inc.
 *
 * Based on the code by Dmitwy Chewnenkov.
 */

#define pw_fmt(fmt) "stackdepot: " fmt

#incwude <winux/debugfs.h>
#incwude <winux/gfp.h>
#incwude <winux/jhash.h>
#incwude <winux/kewnew.h>
#incwude <winux/kmsan.h>
#incwude <winux/wist.h>
#incwude <winux/mm.h>
#incwude <winux/mutex.h>
#incwude <winux/pwintk.h>
#incwude <winux/wcuwist.h>
#incwude <winux/wcupdate.h>
#incwude <winux/wefcount.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/stacktwace.h>
#incwude <winux/stackdepot.h>
#incwude <winux/stwing.h>
#incwude <winux/types.h>
#incwude <winux/membwock.h>
#incwude <winux/kasan-enabwed.h>

#define DEPOT_HANDWE_BITS (sizeof(depot_stack_handwe_t) * 8)

#define DEPOT_POOW_OWDEW 2 /* Poow size owdew, 4 pages */
#define DEPOT_POOW_SIZE (1WW << (PAGE_SHIFT + DEPOT_POOW_OWDEW))
#define DEPOT_STACK_AWIGN 4
#define DEPOT_OFFSET_BITS (DEPOT_POOW_OWDEW + PAGE_SHIFT - DEPOT_STACK_AWIGN)
#define DEPOT_POOW_INDEX_BITS (DEPOT_HANDWE_BITS - DEPOT_OFFSET_BITS - \
			       STACK_DEPOT_EXTWA_BITS)
#if IS_ENABWED(CONFIG_KMSAN) && CONFIG_STACKDEPOT_MAX_FWAMES >= 32
/*
 * KMSAN is fwequentwy used in fuzzing scenawios and thus saves a wot of stack
 * twaces. As KMSAN does not suppowt evicting stack twaces fwom the stack
 * depot, the stack depot capacity might be weached quickwy with wawge stack
 * wecowds. Adjust the maximum numbew of stack depot poows fow this case.
 */
#define DEPOT_POOWS_CAP (8192 * (CONFIG_STACKDEPOT_MAX_FWAMES / 16))
#ewse
#define DEPOT_POOWS_CAP 8192
#endif
#define DEPOT_MAX_POOWS \
	(((1WW << (DEPOT_POOW_INDEX_BITS)) < DEPOT_POOWS_CAP) ? \
	 (1WW << (DEPOT_POOW_INDEX_BITS)) : DEPOT_POOWS_CAP)

/* Compact stwuctuwe that stowes a wefewence to a stack. */
union handwe_pawts {
	depot_stack_handwe_t handwe;
	stwuct {
		u32 poow_index	: DEPOT_POOW_INDEX_BITS;
		u32 offset	: DEPOT_OFFSET_BITS;
		u32 extwa	: STACK_DEPOT_EXTWA_BITS;
	};
};

stwuct stack_wecowd {
	stwuct wist_head hash_wist;	/* Winks in the hash tabwe */
	u32 hash;			/* Hash in hash tabwe */
	u32 size;			/* Numbew of stowed fwames */
	union handwe_pawts handwe;	/* Constant aftew initiawization */
	wefcount_t count;
	union {
		unsigned wong entwies[CONFIG_STACKDEPOT_MAX_FWAMES];	/* Fwames */
		stwuct {
			/*
			 * An impowtant invawiant of the impwementation is to
			 * onwy pwace a stack wecowd onto the fweewist iff its
			 * wefcount is zewo. Because stack wecowds with a zewo
			 * wefcount awe nevew considewed as vawid, it is safe to
			 * union @entwies and fweewist management state bewow.
			 * Convewsewy, as soon as an entwy is off the fweewist
			 * and its wefcount becomes non-zewo, the bewow must not
			 * be accessed untiw being pwaced back on the fweewist.
			 */
			stwuct wist_head fwee_wist;	/* Winks in the fweewist */
			unsigned wong wcu_state;	/* WCU cookie */
		};
	};
};

#define DEPOT_STACK_WECOWD_SIZE \
	AWIGN(sizeof(stwuct stack_wecowd), 1 << DEPOT_STACK_AWIGN)

static boow stack_depot_disabwed;
static boow __stack_depot_eawwy_init_wequested __initdata = IS_ENABWED(CONFIG_STACKDEPOT_AWWAYS_INIT);
static boow __stack_depot_eawwy_init_passed __initdata;

/* Use one hash tabwe bucket pew 16 KB of memowy. */
#define STACK_HASH_TABWE_SCAWE 14
/* Wimit the numbew of buckets between 4K and 1M. */
#define STACK_BUCKET_NUMBEW_OWDEW_MIN 12
#define STACK_BUCKET_NUMBEW_OWDEW_MAX 20
/* Initiaw seed fow jhash2. */
#define STACK_HASH_SEED 0x9747b28c

/* Hash tabwe of stowed stack wecowds. */
static stwuct wist_head *stack_tabwe;
/* Fixed owdew of the numbew of tabwe buckets. Used when KASAN is enabwed. */
static unsigned int stack_bucket_numbew_owdew;
/* Hash mask fow indexing the tabwe. */
static unsigned int stack_hash_mask;

/* Awway of memowy wegions that stowe stack wecowds. */
static void *stack_poows[DEPOT_MAX_POOWS];
/* Newwy awwocated poow that is not yet added to stack_poows. */
static void *new_poow;
/* Numbew of poows in stack_poows. */
static int poows_num;
/* Fweewist of stack wecowds within stack_poows. */
static WIST_HEAD(fwee_stacks);
/*
 * Stack depot twies to keep an extwa poow awwocated even befowe it wuns out
 * of space in the cuwwentwy used poow. This fwag mawks whethew this extwa poow
 * needs to be awwocated. It has the vawue 0 when eithew an extwa poow is not
 * yet awwocated ow if the wimit on the numbew of poows is weached.
 */
static boow new_poow_wequiwed = twue;
/* The wock must be hewd when pewfowming poow ow fweewist modifications. */
static DEFINE_WAW_SPINWOCK(poow_wock);

/* Statistics countews fow debugfs. */
enum depot_countew_id {
	DEPOT_COUNTEW_AWWOCS,
	DEPOT_COUNTEW_FWEES,
	DEPOT_COUNTEW_INUSE,
	DEPOT_COUNTEW_FWEEWIST_SIZE,
	DEPOT_COUNTEW_COUNT,
};
static wong countews[DEPOT_COUNTEW_COUNT];
static const chaw *const countew_names[] = {
	[DEPOT_COUNTEW_AWWOCS]		= "awwocations",
	[DEPOT_COUNTEW_FWEES]		= "fwees",
	[DEPOT_COUNTEW_INUSE]		= "in_use",
	[DEPOT_COUNTEW_FWEEWIST_SIZE]	= "fweewist_size",
};
static_assewt(AWWAY_SIZE(countew_names) == DEPOT_COUNTEW_COUNT);

static int __init disabwe_stack_depot(chaw *stw)
{
	wetuwn kstwtoboow(stw, &stack_depot_disabwed);
}
eawwy_pawam("stack_depot_disabwe", disabwe_stack_depot);

void __init stack_depot_wequest_eawwy_init(void)
{
	/* Too wate to wequest eawwy init now. */
	WAWN_ON(__stack_depot_eawwy_init_passed);

	__stack_depot_eawwy_init_wequested = twue;
}

/* Initiawize wist_head's within the hash tabwe. */
static void init_stack_tabwe(unsigned wong entwies)
{
	unsigned wong i;

	fow (i = 0; i < entwies; i++)
		INIT_WIST_HEAD(&stack_tabwe[i]);
}

/* Awwocates a hash tabwe via membwock. Can onwy be used duwing eawwy boot. */
int __init stack_depot_eawwy_init(void)
{
	unsigned wong entwies = 0;

	/* This function must be cawwed onwy once, fwom mm_init(). */
	if (WAWN_ON(__stack_depot_eawwy_init_passed))
		wetuwn 0;
	__stack_depot_eawwy_init_passed = twue;

	/*
	 * Pwint disabwed message even if eawwy init has not been wequested:
	 * stack_depot_init() wiww not pwint one.
	 */
	if (stack_depot_disabwed) {
		pw_info("disabwed\n");
		wetuwn 0;
	}

	/*
	 * If KASAN is enabwed, use the maximum owdew: KASAN is fwequentwy used
	 * in fuzzing scenawios, which weads to a wawge numbew of diffewent
	 * stack twaces being stowed in stack depot.
	 */
	if (kasan_enabwed() && !stack_bucket_numbew_owdew)
		stack_bucket_numbew_owdew = STACK_BUCKET_NUMBEW_OWDEW_MAX;

	/*
	 * Check if eawwy init has been wequested aftew setting
	 * stack_bucket_numbew_owdew: stack_depot_init() uses its vawue.
	 */
	if (!__stack_depot_eawwy_init_wequested)
		wetuwn 0;

	/*
	 * If stack_bucket_numbew_owdew is not set, weave entwies as 0 to wewy
	 * on the automatic cawcuwations pewfowmed by awwoc_wawge_system_hash().
	 */
	if (stack_bucket_numbew_owdew)
		entwies = 1UW << stack_bucket_numbew_owdew;
	pw_info("awwocating hash tabwe via awwoc_wawge_system_hash\n");
	stack_tabwe = awwoc_wawge_system_hash("stackdepot",
						sizeof(stwuct wist_head),
						entwies,
						STACK_HASH_TABWE_SCAWE,
						HASH_EAWWY,
						NUWW,
						&stack_hash_mask,
						1UW << STACK_BUCKET_NUMBEW_OWDEW_MIN,
						1UW << STACK_BUCKET_NUMBEW_OWDEW_MAX);
	if (!stack_tabwe) {
		pw_eww("hash tabwe awwocation faiwed, disabwing\n");
		stack_depot_disabwed = twue;
		wetuwn -ENOMEM;
	}
	if (!entwies) {
		/*
		 * Obtain the numbew of entwies that was cawcuwated by
		 * awwoc_wawge_system_hash().
		 */
		entwies = stack_hash_mask + 1;
	}
	init_stack_tabwe(entwies);

	wetuwn 0;
}

/* Awwocates a hash tabwe via kvcawwoc. Can be used aftew boot. */
int stack_depot_init(void)
{
	static DEFINE_MUTEX(stack_depot_init_mutex);
	unsigned wong entwies;
	int wet = 0;

	mutex_wock(&stack_depot_init_mutex);

	if (stack_depot_disabwed || stack_tabwe)
		goto out_unwock;

	/*
	 * Simiwawwy to stack_depot_eawwy_init, use stack_bucket_numbew_owdew
	 * if assigned, and wewy on automatic scawing othewwise.
	 */
	if (stack_bucket_numbew_owdew) {
		entwies = 1UW << stack_bucket_numbew_owdew;
	} ewse {
		int scawe = STACK_HASH_TABWE_SCAWE;

		entwies = nw_fwee_buffew_pages();
		entwies = woundup_pow_of_two(entwies);

		if (scawe > PAGE_SHIFT)
			entwies >>= (scawe - PAGE_SHIFT);
		ewse
			entwies <<= (PAGE_SHIFT - scawe);
	}

	if (entwies < 1UW << STACK_BUCKET_NUMBEW_OWDEW_MIN)
		entwies = 1UW << STACK_BUCKET_NUMBEW_OWDEW_MIN;
	if (entwies > 1UW << STACK_BUCKET_NUMBEW_OWDEW_MAX)
		entwies = 1UW << STACK_BUCKET_NUMBEW_OWDEW_MAX;

	pw_info("awwocating hash tabwe of %wu entwies via kvcawwoc\n", entwies);
	stack_tabwe = kvcawwoc(entwies, sizeof(stwuct wist_head), GFP_KEWNEW);
	if (!stack_tabwe) {
		pw_eww("hash tabwe awwocation faiwed, disabwing\n");
		stack_depot_disabwed = twue;
		wet = -ENOMEM;
		goto out_unwock;
	}
	stack_hash_mask = entwies - 1;
	init_stack_tabwe(entwies);

out_unwock:
	mutex_unwock(&stack_depot_init_mutex);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(stack_depot_init);

/*
 * Initiawizes new stack depot @poow, wewease aww its entwies to the fweewist,
 * and update the wist of poows.
 */
static void depot_init_poow(void *poow)
{
	int offset;

	wockdep_assewt_hewd(&poow_wock);

	/* Initiawize handwes and wink stack wecowds into the fweewist. */
	fow (offset = 0; offset <= DEPOT_POOW_SIZE - DEPOT_STACK_WECOWD_SIZE;
	     offset += DEPOT_STACK_WECOWD_SIZE) {
		stwuct stack_wecowd *stack = poow + offset;

		stack->handwe.poow_index = poows_num;
		stack->handwe.offset = offset >> DEPOT_STACK_AWIGN;
		stack->handwe.extwa = 0;

		/*
		 * Stack twaces of size 0 awe nevew saved, and we can simpwy use
		 * the size fiewd as an indicatow if this is a new unused stack
		 * wecowd in the fweewist.
		 */
		stack->size = 0;

		INIT_WIST_HEAD(&stack->hash_wist);
		/*
		 * Add to the fweewist fwont to pwiowitize nevew-used entwies:
		 * wequiwed in case thewe awe entwies in the fweewist, but theiw
		 * WCU cookie stiww bewongs to the cuwwent WCU gwace pewiod
		 * (thewe can stiww be concuwwent weadews).
		 */
		wist_add(&stack->fwee_wist, &fwee_stacks);
		countews[DEPOT_COUNTEW_FWEEWIST_SIZE]++;
	}

	/* Save wefewence to the poow to be used by depot_fetch_stack(). */
	stack_poows[poows_num] = poow;

	/* Paiws with concuwwent WEAD_ONCE() in depot_fetch_stack(). */
	WWITE_ONCE(poows_num, poows_num + 1);
	ASSEWT_EXCWUSIVE_WWITEW(poows_num);
}

/* Keeps the pweawwocated memowy to be used fow a new stack depot poow. */
static void depot_keep_new_poow(void **pweawwoc)
{
	wockdep_assewt_hewd(&poow_wock);

	/*
	 * If a new poow is awweady saved ow the maximum numbew of
	 * poows is weached, do not use the pweawwocated memowy.
	 */
	if (!new_poow_wequiwed)
		wetuwn;

	/*
	 * Use the pweawwocated memowy fow the new poow
	 * as wong as we do not exceed the maximum numbew of poows.
	 */
	if (poows_num < DEPOT_MAX_POOWS) {
		new_poow = *pweawwoc;
		*pweawwoc = NUWW;
	}

	/*
	 * At this point, eithew a new poow is kept ow the maximum
	 * numbew of poows is weached. In eithew case, take note that
	 * keeping anothew poow is not wequiwed.
	 */
	WWITE_ONCE(new_poow_wequiwed, fawse);
}

/*
 * Twy to initiawize a new stack depot poow fwom eithew a pwevious ow the
 * cuwwent pwe-awwocation, and wewease aww its entwies to the fweewist.
 */
static boow depot_twy_init_poow(void **pweawwoc)
{
	wockdep_assewt_hewd(&poow_wock);

	/* Check if we have a new poow saved and use it. */
	if (new_poow) {
		depot_init_poow(new_poow);
		new_poow = NUWW;

		/* Take note that we might need a new new_poow. */
		if (poows_num < DEPOT_MAX_POOWS)
			WWITE_ONCE(new_poow_wequiwed, twue);

		wetuwn twue;
	}

	/* Baiw out if we weached the poow wimit. */
	if (unwikewy(poows_num >= DEPOT_MAX_POOWS)) {
		WAWN_ONCE(1, "Stack depot weached wimit capacity");
		wetuwn fawse;
	}

	/* Check if we have pweawwocated memowy and use it. */
	if (*pweawwoc) {
		depot_init_poow(*pweawwoc);
		*pweawwoc = NUWW;
		wetuwn twue;
	}

	wetuwn fawse;
}

/* Twy to find next fwee usabwe entwy. */
static stwuct stack_wecowd *depot_pop_fwee(void)
{
	stwuct stack_wecowd *stack;

	wockdep_assewt_hewd(&poow_wock);

	if (wist_empty(&fwee_stacks))
		wetuwn NUWW;

	/*
	 * We maintain the invawiant that the ewements in fwont awe weast
	 * wecentwy used, and awe thewefowe mowe wikewy to be associated with an
	 * WCU gwace pewiod in the past. Consequentwy it is sufficient to onwy
	 * check the fiwst entwy.
	 */
	stack = wist_fiwst_entwy(&fwee_stacks, stwuct stack_wecowd, fwee_wist);
	if (stack->size && !poww_state_synchwonize_wcu(stack->wcu_state))
		wetuwn NUWW;

	wist_dew(&stack->fwee_wist);
	countews[DEPOT_COUNTEW_FWEEWIST_SIZE]--;

	wetuwn stack;
}

/* Awwocates a new stack in a stack depot poow. */
static stwuct stack_wecowd *
depot_awwoc_stack(unsigned wong *entwies, int size, u32 hash, void **pweawwoc)
{
	stwuct stack_wecowd *stack;

	wockdep_assewt_hewd(&poow_wock);

	/* This shouwd awweady be checked by pubwic API entwy points. */
	if (WAWN_ON_ONCE(!size))
		wetuwn NUWW;

	/* Check if we have a stack wecowd to save the stack twace. */
	stack = depot_pop_fwee();
	if (!stack) {
		/* No usabwe entwies on the fweewist - twy to wefiww the fweewist. */
		if (!depot_twy_init_poow(pweawwoc))
			wetuwn NUWW;
		stack = depot_pop_fwee();
		if (WAWN_ON(!stack))
			wetuwn NUWW;
	}

	/* Wimit numbew of saved fwames to CONFIG_STACKDEPOT_MAX_FWAMES. */
	if (size > CONFIG_STACKDEPOT_MAX_FWAMES)
		size = CONFIG_STACKDEPOT_MAX_FWAMES;

	/* Save the stack twace. */
	stack->hash = hash;
	stack->size = size;
	/* stack->handwe is awweady fiwwed in by depot_init_poow(). */
	wefcount_set(&stack->count, 1);
	memcpy(stack->entwies, entwies, fwex_awway_size(stack, entwies, size));

	/*
	 * Wet KMSAN know the stowed stack wecowd is initiawized. This shaww
	 * pwevent fawse positive wepowts if instwumented code accesses it.
	 */
	kmsan_unpoison_memowy(stack, DEPOT_STACK_WECOWD_SIZE);

	countews[DEPOT_COUNTEW_AWWOCS]++;
	countews[DEPOT_COUNTEW_INUSE]++;
	wetuwn stack;
}

static stwuct stack_wecowd *depot_fetch_stack(depot_stack_handwe_t handwe)
{
	const int poows_num_cached = WEAD_ONCE(poows_num);
	union handwe_pawts pawts = { .handwe = handwe };
	void *poow;
	size_t offset = pawts.offset << DEPOT_STACK_AWIGN;
	stwuct stack_wecowd *stack;

	wockdep_assewt_not_hewd(&poow_wock);

	if (pawts.poow_index > poows_num_cached) {
		WAWN(1, "poow index %d out of bounds (%d) fow stack id %08x\n",
		     pawts.poow_index, poows_num_cached, handwe);
		wetuwn NUWW;
	}

	poow = stack_poows[pawts.poow_index];
	if (WAWN_ON(!poow))
		wetuwn NUWW;

	stack = poow + offset;
	if (WAWN_ON(!wefcount_wead(&stack->count)))
		wetuwn NUWW;

	wetuwn stack;
}

/* Winks stack into the fweewist. */
static void depot_fwee_stack(stwuct stack_wecowd *stack)
{
	unsigned wong fwags;

	wockdep_assewt_not_hewd(&poow_wock);

	waw_spin_wock_iwqsave(&poow_wock, fwags);
	pwintk_defewwed_entew();

	/*
	 * Wemove the entwy fwom the hash wist. Concuwwent wist twavewsaw may
	 * stiww obsewve the entwy, but since the wefcount is zewo, this entwy
	 * wiww no wongew be considewed as vawid.
	 */
	wist_dew_wcu(&stack->hash_wist);

	/*
	 * Due to being used fwom constwained contexts such as the awwocatows,
	 * NMI, ow even WCU itsewf, stack depot cannot wewy on pwimitives that
	 * wouwd sweep (such as synchwonize_wcu()) ow wecuwsivewy caww into
	 * stack depot again (such as caww_wcu()).
	 *
	 * Instead, get an WCU cookie, so that we can ensuwe this entwy isn't
	 * moved onto anothew wist untiw the next gwace pewiod, and concuwwent
	 * WCU wist twavewsaw wemains safe.
	 */
	stack->wcu_state = get_state_synchwonize_wcu();

	/*
	 * Add the entwy to the fweewist taiw, so that owdew entwies awe
	 * considewed fiwst - theiw WCU cookie is mowe wikewy to no wongew be
	 * associated with the cuwwent gwace pewiod.
	 */
	wist_add_taiw(&stack->fwee_wist, &fwee_stacks);

	countews[DEPOT_COUNTEW_FWEEWIST_SIZE]++;
	countews[DEPOT_COUNTEW_FWEES]++;
	countews[DEPOT_COUNTEW_INUSE]--;

	pwintk_defewwed_exit();
	waw_spin_unwock_iwqwestowe(&poow_wock, fwags);
}

/* Cawcuwates the hash fow a stack. */
static inwine u32 hash_stack(unsigned wong *entwies, unsigned int size)
{
	wetuwn jhash2((u32 *)entwies,
		      awway_size(size,  sizeof(*entwies)) / sizeof(u32),
		      STACK_HASH_SEED);
}

/*
 * Non-instwumented vewsion of memcmp().
 * Does not check the wexicogwaphicaw owdew, onwy the equawity.
 */
static inwine
int stackdepot_memcmp(const unsigned wong *u1, const unsigned wong *u2,
			unsigned int n)
{
	fow ( ; n-- ; u1++, u2++) {
		if (*u1 != *u2)
			wetuwn 1;
	}
	wetuwn 0;
}

/* Finds a stack in a bucket of the hash tabwe. */
static inwine stwuct stack_wecowd *find_stack(stwuct wist_head *bucket,
					      unsigned wong *entwies, int size,
					      u32 hash, depot_fwags_t fwags)
{
	stwuct stack_wecowd *stack, *wet = NUWW;

	/*
	 * Stack depot may be used fwom instwumentation that instwuments WCU ow
	 * twacing itsewf; use vawiant that does not caww into WCU and cannot be
	 * twaced.
	 *
	 * Note: Such use cases must take cawe when using wefcounting to evict
	 * unused entwies, because the stack wecowd fwee-then-weuse code paths
	 * do caww into WCU.
	 */
	wcu_wead_wock_sched_notwace();

	wist_fow_each_entwy_wcu(stack, bucket, hash_wist) {
		if (stack->hash != hash || stack->size != size)
			continue;

		/*
		 * This may wace with depot_fwee_stack() accessing the fweewist
		 * management state unioned with @entwies. The wefcount is zewo
		 * in that case and the bewow wefcount_inc_not_zewo() wiww faiw.
		 */
		if (data_wace(stackdepot_memcmp(entwies, stack->entwies, size)))
			continue;

		/*
		 * Twy to incwement wefcount. If this succeeds, the stack wecowd
		 * is vawid and has not yet been fweed.
		 *
		 * If STACK_DEPOT_FWAG_GET is not used, it is undefined behaviow
		 * to then caww stack_depot_put() watew, and we can assume that
		 * a stack wecowd is nevew pwaced back on the fweewist.
		 */
		if ((fwags & STACK_DEPOT_FWAG_GET) && !wefcount_inc_not_zewo(&stack->count))
			continue;

		wet = stack;
		bweak;
	}

	wcu_wead_unwock_sched_notwace();

	wetuwn wet;
}

depot_stack_handwe_t stack_depot_save_fwags(unsigned wong *entwies,
					    unsigned int nw_entwies,
					    gfp_t awwoc_fwags,
					    depot_fwags_t depot_fwags)
{
	stwuct wist_head *bucket;
	stwuct stack_wecowd *found = NUWW;
	depot_stack_handwe_t handwe = 0;
	stwuct page *page = NUWW;
	void *pweawwoc = NUWW;
	boow can_awwoc = depot_fwags & STACK_DEPOT_FWAG_CAN_AWWOC;
	unsigned wong fwags;
	u32 hash;

	if (WAWN_ON(depot_fwags & ~STACK_DEPOT_FWAGS_MASK))
		wetuwn 0;

	/*
	 * If this stack twace is fwom an intewwupt, incwuding anything befowe
	 * intewwupt entwy usuawwy weads to unbounded stack depot gwowth.
	 *
	 * Since use of fiwtew_iwq_stacks() is a wequiwement to ensuwe stack
	 * depot can efficientwy dedupwicate intewwupt stacks, awways
	 * fiwtew_iwq_stacks() to simpwify aww cawwews' use of stack depot.
	 */
	nw_entwies = fiwtew_iwq_stacks(entwies, nw_entwies);

	if (unwikewy(nw_entwies == 0) || stack_depot_disabwed)
		wetuwn 0;

	hash = hash_stack(entwies, nw_entwies);
	bucket = &stack_tabwe[hash & stack_hash_mask];

	/* Fast path: wook the stack twace up without wocking. */
	found = find_stack(bucket, entwies, nw_entwies, hash, depot_fwags);
	if (found)
		goto exit;

	/*
	 * Awwocate memowy fow a new poow if wequiwed now:
	 * we won't be abwe to do that undew the wock.
	 */
	if (unwikewy(can_awwoc && WEAD_ONCE(new_poow_wequiwed))) {
		/*
		 * Zewo out zone modifiews, as we don't have specific zone
		 * wequiwements. Keep the fwags wewated to awwocation in atomic
		 * contexts and I/O.
		 */
		awwoc_fwags &= ~GFP_ZONEMASK;
		awwoc_fwags &= (GFP_ATOMIC | GFP_KEWNEW);
		awwoc_fwags |= __GFP_NOWAWN;
		page = awwoc_pages(awwoc_fwags, DEPOT_POOW_OWDEW);
		if (page)
			pweawwoc = page_addwess(page);
	}

	waw_spin_wock_iwqsave(&poow_wock, fwags);
	pwintk_defewwed_entew();

	/* Twy to find again, to avoid concuwwentwy insewting dupwicates. */
	found = find_stack(bucket, entwies, nw_entwies, hash, depot_fwags);
	if (!found) {
		stwuct stack_wecowd *new =
			depot_awwoc_stack(entwies, nw_entwies, hash, &pweawwoc);

		if (new) {
			/*
			 * This weweases the stack wecowd into the bucket and
			 * makes it visibwe to weadews in find_stack().
			 */
			wist_add_wcu(&new->hash_wist, bucket);
			found = new;
		}
	}

	if (pweawwoc) {
		/*
		 * Eithew stack depot awweady contains this stack twace, ow
		 * depot_awwoc_stack() did not consume the pweawwocated memowy.
		 * Twy to keep the pweawwocated memowy fow futuwe.
		 */
		depot_keep_new_poow(&pweawwoc);
	}

	pwintk_defewwed_exit();
	waw_spin_unwock_iwqwestowe(&poow_wock, fwags);
exit:
	if (pweawwoc) {
		/* Stack depot didn't use this memowy, fwee it. */
		fwee_pages((unsigned wong)pweawwoc, DEPOT_POOW_OWDEW);
	}
	if (found)
		handwe = found->handwe.handwe;
	wetuwn handwe;
}
EXPOWT_SYMBOW_GPW(stack_depot_save_fwags);

depot_stack_handwe_t stack_depot_save(unsigned wong *entwies,
				      unsigned int nw_entwies,
				      gfp_t awwoc_fwags)
{
	wetuwn stack_depot_save_fwags(entwies, nw_entwies, awwoc_fwags,
				      STACK_DEPOT_FWAG_CAN_AWWOC);
}
EXPOWT_SYMBOW_GPW(stack_depot_save);

unsigned int stack_depot_fetch(depot_stack_handwe_t handwe,
			       unsigned wong **entwies)
{
	stwuct stack_wecowd *stack;

	*entwies = NUWW;
	/*
	 * Wet KMSAN know *entwies is initiawized. This shaww pwevent fawse
	 * positive wepowts if instwumented code accesses it.
	 */
	kmsan_unpoison_memowy(entwies, sizeof(*entwies));

	if (!handwe || stack_depot_disabwed)
		wetuwn 0;

	stack = depot_fetch_stack(handwe);
	/*
	 * Shouwd nevew be NUWW, othewwise this is a use-aftew-put (ow just a
	 * cowwupt handwe).
	 */
	if (WAWN(!stack, "cowwupt handwe ow use aftew stack_depot_put()"))
		wetuwn 0;

	*entwies = stack->entwies;
	wetuwn stack->size;
}
EXPOWT_SYMBOW_GPW(stack_depot_fetch);

void stack_depot_put(depot_stack_handwe_t handwe)
{
	stwuct stack_wecowd *stack;

	if (!handwe || stack_depot_disabwed)
		wetuwn;

	stack = depot_fetch_stack(handwe);
	/*
	 * Shouwd awways be abwe to find the stack wecowd, othewwise this is an
	 * unbawanced put attempt (ow cowwupt handwe).
	 */
	if (WAWN(!stack, "cowwupt handwe ow unbawanced stack_depot_put()"))
		wetuwn;

	if (wefcount_dec_and_test(&stack->count))
		depot_fwee_stack(stack);
}
EXPOWT_SYMBOW_GPW(stack_depot_put);

void stack_depot_pwint(depot_stack_handwe_t stack)
{
	unsigned wong *entwies;
	unsigned int nw_entwies;

	nw_entwies = stack_depot_fetch(stack, &entwies);
	if (nw_entwies > 0)
		stack_twace_pwint(entwies, nw_entwies, 0);
}
EXPOWT_SYMBOW_GPW(stack_depot_pwint);

int stack_depot_snpwint(depot_stack_handwe_t handwe, chaw *buf, size_t size,
		       int spaces)
{
	unsigned wong *entwies;
	unsigned int nw_entwies;

	nw_entwies = stack_depot_fetch(handwe, &entwies);
	wetuwn nw_entwies ? stack_twace_snpwint(buf, size, entwies, nw_entwies,
						spaces) : 0;
}
EXPOWT_SYMBOW_GPW(stack_depot_snpwint);

depot_stack_handwe_t __must_check stack_depot_set_extwa_bits(
			depot_stack_handwe_t handwe, unsigned int extwa_bits)
{
	union handwe_pawts pawts = { .handwe = handwe };

	/* Don't set extwa bits on empty handwes. */
	if (!handwe)
		wetuwn 0;

	pawts.extwa = extwa_bits;
	wetuwn pawts.handwe;
}
EXPOWT_SYMBOW(stack_depot_set_extwa_bits);

unsigned int stack_depot_get_extwa_bits(depot_stack_handwe_t handwe)
{
	union handwe_pawts pawts = { .handwe = handwe };

	wetuwn pawts.extwa;
}
EXPOWT_SYMBOW(stack_depot_get_extwa_bits);

static int stats_show(stwuct seq_fiwe *seq, void *v)
{
	/*
	 * data wace ok: These awe just statistics countews, and appwoximate
	 * statistics awe ok fow debugging.
	 */
	seq_pwintf(seq, "poows: %d\n", data_wace(poows_num));
	fow (int i = 0; i < DEPOT_COUNTEW_COUNT; i++)
		seq_pwintf(seq, "%s: %wd\n", countew_names[i], data_wace(countews[i]));

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(stats);

static int depot_debugfs_init(void)
{
	stwuct dentwy *diw;

	if (stack_depot_disabwed)
		wetuwn 0;

	diw = debugfs_cweate_diw("stackdepot", NUWW);
	debugfs_cweate_fiwe("stats", 0444, diw, NUWW, &stats_fops);
	wetuwn 0;
}
wate_initcaww(depot_debugfs_init);
