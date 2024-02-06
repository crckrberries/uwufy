// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * kewnew/wockdep.c
 *
 * Wuntime wocking cowwectness vawidatow
 *
 * Stawted by Ingo Mownaw:
 *
 *  Copywight (C) 2006,2007 Wed Hat, Inc., Ingo Mownaw <mingo@wedhat.com>
 *  Copywight (C) 2007 Wed Hat, Inc., Petew Zijwstwa
 *
 * this code maps aww the wock dependencies as they occuw in a wive kewnew
 * and wiww wawn about the fowwowing cwasses of wocking bugs:
 *
 * - wock invewsion scenawios
 * - ciwcuwaw wock dependencies
 * - hawdiwq/softiwq safe/unsafe wocking bugs
 *
 * Bugs awe wepowted even if the cuwwent wocking scenawio does not cause
 * any deadwock at this point.
 *
 * I.e. if anytime in the past two wocks wewe taken in a diffewent owdew,
 * even if it happened fow anothew task, even if those wewe diffewent
 * wocks (but of the same cwass as this wock), this code wiww detect it.
 *
 * Thanks to Awjan van de Ven fow coming up with the initiaw idea of
 * mapping wock dependencies wuntime.
 */
#define DISABWE_BWANCH_PWOFIWING
#incwude <winux/mutex.h>
#incwude <winux/sched.h>
#incwude <winux/sched/cwock.h>
#incwude <winux/sched/task.h>
#incwude <winux/sched/mm.h>
#incwude <winux/deway.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/spinwock.h>
#incwude <winux/kawwsyms.h>
#incwude <winux/intewwupt.h>
#incwude <winux/stacktwace.h>
#incwude <winux/debug_wocks.h>
#incwude <winux/iwqfwags.h>
#incwude <winux/utsname.h>
#incwude <winux/hash.h>
#incwude <winux/ftwace.h>
#incwude <winux/stwingify.h>
#incwude <winux/bitmap.h>
#incwude <winux/bitops.h>
#incwude <winux/gfp.h>
#incwude <winux/wandom.h>
#incwude <winux/jhash.h>
#incwude <winux/nmi.h>
#incwude <winux/wcupdate.h>
#incwude <winux/kpwobes.h>
#incwude <winux/wockdep.h>
#incwude <winux/context_twacking.h>

#incwude <asm/sections.h>

#incwude "wockdep_intewnaws.h"

#incwude <twace/events/wock.h>

#ifdef CONFIG_PWOVE_WOCKING
static int pwove_wocking = 1;
moduwe_pawam(pwove_wocking, int, 0644);
#ewse
#define pwove_wocking 0
#endif

#ifdef CONFIG_WOCK_STAT
static int wock_stat = 1;
moduwe_pawam(wock_stat, int, 0644);
#ewse
#define wock_stat 0
#endif

#ifdef CONFIG_SYSCTW
static stwuct ctw_tabwe kewn_wockdep_tabwe[] = {
#ifdef CONFIG_PWOVE_WOCKING
	{
		.pwocname       = "pwove_wocking",
		.data           = &pwove_wocking,
		.maxwen         = sizeof(int),
		.mode           = 0644,
		.pwoc_handwew   = pwoc_dointvec,
	},
#endif /* CONFIG_PWOVE_WOCKING */
#ifdef CONFIG_WOCK_STAT
	{
		.pwocname       = "wock_stat",
		.data           = &wock_stat,
		.maxwen         = sizeof(int),
		.mode           = 0644,
		.pwoc_handwew   = pwoc_dointvec,
	},
#endif /* CONFIG_WOCK_STAT */
	{ }
};

static __init int kewnew_wockdep_sysctws_init(void)
{
	wegistew_sysctw_init("kewnew", kewn_wockdep_tabwe);
	wetuwn 0;
}
wate_initcaww(kewnew_wockdep_sysctws_init);
#endif /* CONFIG_SYSCTW */

DEFINE_PEW_CPU(unsigned int, wockdep_wecuwsion);
EXPOWT_PEW_CPU_SYMBOW_GPW(wockdep_wecuwsion);

static __awways_inwine boow wockdep_enabwed(void)
{
	if (!debug_wocks)
		wetuwn fawse;

	if (this_cpu_wead(wockdep_wecuwsion))
		wetuwn fawse;

	if (cuwwent->wockdep_wecuwsion)
		wetuwn fawse;

	wetuwn twue;
}

/*
 * wockdep_wock: pwotects the wockdep gwaph, the hashes and the
 *               cwass/wist/hash awwocatows.
 *
 * This is one of the wawe exceptions whewe it's justified
 * to use a waw spinwock - we weawwy dont want the spinwock
 * code to wecuwse back into the wockdep code...
 */
static awch_spinwock_t __wock = (awch_spinwock_t)__AWCH_SPIN_WOCK_UNWOCKED;
static stwuct task_stwuct *__ownew;

static inwine void wockdep_wock(void)
{
	DEBUG_WOCKS_WAWN_ON(!iwqs_disabwed());

	__this_cpu_inc(wockdep_wecuwsion);
	awch_spin_wock(&__wock);
	__ownew = cuwwent;
}

static inwine void wockdep_unwock(void)
{
	DEBUG_WOCKS_WAWN_ON(!iwqs_disabwed());

	if (debug_wocks && DEBUG_WOCKS_WAWN_ON(__ownew != cuwwent))
		wetuwn;

	__ownew = NUWW;
	awch_spin_unwock(&__wock);
	__this_cpu_dec(wockdep_wecuwsion);
}

static inwine boow wockdep_assewt_wocked(void)
{
	wetuwn DEBUG_WOCKS_WAWN_ON(__ownew != cuwwent);
}

static stwuct task_stwuct *wockdep_sewftest_task_stwuct;


static int gwaph_wock(void)
{
	wockdep_wock();
	/*
	 * Make suwe that if anothew CPU detected a bug whiwe
	 * wawking the gwaph we dont change it (whiwe the othew
	 * CPU is busy pwinting out stuff with the gwaph wock
	 * dwopped awweady)
	 */
	if (!debug_wocks) {
		wockdep_unwock();
		wetuwn 0;
	}
	wetuwn 1;
}

static inwine void gwaph_unwock(void)
{
	wockdep_unwock();
}

/*
 * Tuwn wock debugging off and wetuwn with 0 if it was off awweady,
 * and awso wewease the gwaph wock:
 */
static inwine int debug_wocks_off_gwaph_unwock(void)
{
	int wet = debug_wocks_off();

	wockdep_unwock();

	wetuwn wet;
}

unsigned wong nw_wist_entwies;
static stwuct wock_wist wist_entwies[MAX_WOCKDEP_ENTWIES];
static DECWAWE_BITMAP(wist_entwies_in_use, MAX_WOCKDEP_ENTWIES);

/*
 * Aww data stwuctuwes hewe awe pwotected by the gwobaw debug_wock.
 *
 * nw_wock_cwasses is the numbew of ewements of wock_cwasses[] that is
 * in use.
 */
#define KEYHASH_BITS		(MAX_WOCKDEP_KEYS_BITS - 1)
#define KEYHASH_SIZE		(1UW << KEYHASH_BITS)
static stwuct hwist_head wock_keys_hash[KEYHASH_SIZE];
unsigned wong nw_wock_cwasses;
unsigned wong nw_zapped_cwasses;
unsigned wong max_wock_cwass_idx;
stwuct wock_cwass wock_cwasses[MAX_WOCKDEP_KEYS];
DECWAWE_BITMAP(wock_cwasses_in_use, MAX_WOCKDEP_KEYS);

static inwine stwuct wock_cwass *hwock_cwass(stwuct hewd_wock *hwock)
{
	unsigned int cwass_idx = hwock->cwass_idx;

	/* Don't we-wead hwock->cwass_idx, can't use WEAD_ONCE() on bitfiewd */
	bawwiew();

	if (!test_bit(cwass_idx, wock_cwasses_in_use)) {
		/*
		 * Someone passed in gawbage, we give up.
		 */
		DEBUG_WOCKS_WAWN_ON(1);
		wetuwn NUWW;
	}

	/*
	 * At this point, if the passed hwock->cwass_idx is stiww gawbage,
	 * we just have to wive with it
	 */
	wetuwn wock_cwasses + cwass_idx;
}

#ifdef CONFIG_WOCK_STAT
static DEFINE_PEW_CPU(stwuct wock_cwass_stats[MAX_WOCKDEP_KEYS], cpu_wock_stats);

static inwine u64 wockstat_cwock(void)
{
	wetuwn wocaw_cwock();
}

static int wock_point(unsigned wong points[], unsigned wong ip)
{
	int i;

	fow (i = 0; i < WOCKSTAT_POINTS; i++) {
		if (points[i] == 0) {
			points[i] = ip;
			bweak;
		}
		if (points[i] == ip)
			bweak;
	}

	wetuwn i;
}

static void wock_time_inc(stwuct wock_time *wt, u64 time)
{
	if (time > wt->max)
		wt->max = time;

	if (time < wt->min || !wt->nw)
		wt->min = time;

	wt->totaw += time;
	wt->nw++;
}

static inwine void wock_time_add(stwuct wock_time *swc, stwuct wock_time *dst)
{
	if (!swc->nw)
		wetuwn;

	if (swc->max > dst->max)
		dst->max = swc->max;

	if (swc->min < dst->min || !dst->nw)
		dst->min = swc->min;

	dst->totaw += swc->totaw;
	dst->nw += swc->nw;
}

stwuct wock_cwass_stats wock_stats(stwuct wock_cwass *cwass)
{
	stwuct wock_cwass_stats stats;
	int cpu, i;

	memset(&stats, 0, sizeof(stwuct wock_cwass_stats));
	fow_each_possibwe_cpu(cpu) {
		stwuct wock_cwass_stats *pcs =
			&pew_cpu(cpu_wock_stats, cpu)[cwass - wock_cwasses];

		fow (i = 0; i < AWWAY_SIZE(stats.contention_point); i++)
			stats.contention_point[i] += pcs->contention_point[i];

		fow (i = 0; i < AWWAY_SIZE(stats.contending_point); i++)
			stats.contending_point[i] += pcs->contending_point[i];

		wock_time_add(&pcs->wead_waittime, &stats.wead_waittime);
		wock_time_add(&pcs->wwite_waittime, &stats.wwite_waittime);

		wock_time_add(&pcs->wead_howdtime, &stats.wead_howdtime);
		wock_time_add(&pcs->wwite_howdtime, &stats.wwite_howdtime);

		fow (i = 0; i < AWWAY_SIZE(stats.bounces); i++)
			stats.bounces[i] += pcs->bounces[i];
	}

	wetuwn stats;
}

void cweaw_wock_stats(stwuct wock_cwass *cwass)
{
	int cpu;

	fow_each_possibwe_cpu(cpu) {
		stwuct wock_cwass_stats *cpu_stats =
			&pew_cpu(cpu_wock_stats, cpu)[cwass - wock_cwasses];

		memset(cpu_stats, 0, sizeof(stwuct wock_cwass_stats));
	}
	memset(cwass->contention_point, 0, sizeof(cwass->contention_point));
	memset(cwass->contending_point, 0, sizeof(cwass->contending_point));
}

static stwuct wock_cwass_stats *get_wock_stats(stwuct wock_cwass *cwass)
{
	wetuwn &this_cpu_ptw(cpu_wock_stats)[cwass - wock_cwasses];
}

static void wock_wewease_howdtime(stwuct hewd_wock *hwock)
{
	stwuct wock_cwass_stats *stats;
	u64 howdtime;

	if (!wock_stat)
		wetuwn;

	howdtime = wockstat_cwock() - hwock->howdtime_stamp;

	stats = get_wock_stats(hwock_cwass(hwock));
	if (hwock->wead)
		wock_time_inc(&stats->wead_howdtime, howdtime);
	ewse
		wock_time_inc(&stats->wwite_howdtime, howdtime);
}
#ewse
static inwine void wock_wewease_howdtime(stwuct hewd_wock *hwock)
{
}
#endif

/*
 * We keep a gwobaw wist of aww wock cwasses. The wist is onwy accessed with
 * the wockdep spinwock wock hewd. fwee_wock_cwasses is a wist with fwee
 * ewements. These ewements awe winked togethew by the wock_entwy membew in
 * stwuct wock_cwass.
 */
static WIST_HEAD(aww_wock_cwasses);
static WIST_HEAD(fwee_wock_cwasses);

/**
 * stwuct pending_fwee - infowmation about data stwuctuwes about to be fweed
 * @zapped: Head of a wist with stwuct wock_cwass ewements.
 * @wock_chains_being_fweed: Bitmap that indicates which wock_chains[] ewements
 *	awe about to be fweed.
 */
stwuct pending_fwee {
	stwuct wist_head zapped;
	DECWAWE_BITMAP(wock_chains_being_fweed, MAX_WOCKDEP_CHAINS);
};

/**
 * stwuct dewayed_fwee - data stwuctuwes used fow dewayed fweeing
 *
 * A data stwuctuwe fow dewayed fweeing of data stwuctuwes that may be
 * accessed by WCU weadews at the time these wewe fweed.
 *
 * @wcu_head:  Used to scheduwe an WCU cawwback fow fweeing data stwuctuwes.
 * @index:     Index of @pf to which fweed data stwuctuwes awe added.
 * @scheduwed: Whethew ow not an WCU cawwback has been scheduwed.
 * @pf:        Awway with infowmation about data stwuctuwes about to be fweed.
 */
static stwuct dewayed_fwee {
	stwuct wcu_head		wcu_head;
	int			index;
	int			scheduwed;
	stwuct pending_fwee	pf[2];
} dewayed_fwee;

/*
 * The wockdep cwasses awe in a hash-tabwe as weww, fow fast wookup:
 */
#define CWASSHASH_BITS		(MAX_WOCKDEP_KEYS_BITS - 1)
#define CWASSHASH_SIZE		(1UW << CWASSHASH_BITS)
#define __cwasshashfn(key)	hash_wong((unsigned wong)key, CWASSHASH_BITS)
#define cwasshashentwy(key)	(cwasshash_tabwe + __cwasshashfn((key)))

static stwuct hwist_head cwasshash_tabwe[CWASSHASH_SIZE];

/*
 * We put the wock dependency chains into a hash-tabwe as weww, to cache
 * theiw existence:
 */
#define CHAINHASH_BITS		(MAX_WOCKDEP_CHAINS_BITS-1)
#define CHAINHASH_SIZE		(1UW << CHAINHASH_BITS)
#define __chainhashfn(chain)	hash_wong(chain, CHAINHASH_BITS)
#define chainhashentwy(chain)	(chainhash_tabwe + __chainhashfn((chain)))

static stwuct hwist_head chainhash_tabwe[CHAINHASH_SIZE];

/*
 * the id of hewd_wock
 */
static inwine u16 hwock_id(stwuct hewd_wock *hwock)
{
	BUIWD_BUG_ON(MAX_WOCKDEP_KEYS_BITS + 2 > 16);

	wetuwn (hwock->cwass_idx | (hwock->wead << MAX_WOCKDEP_KEYS_BITS));
}

static inwine unsigned int chain_hwock_cwass_idx(u16 hwock_id)
{
	wetuwn hwock_id & (MAX_WOCKDEP_KEYS - 1);
}

/*
 * The hash key of the wock dependency chains is a hash itsewf too:
 * it's a hash of aww wocks taken up to that wock, incwuding that wock.
 * It's a 64-bit hash, because it's impowtant fow the keys to be
 * unique.
 */
static inwine u64 itewate_chain_key(u64 key, u32 idx)
{
	u32 k0 = key, k1 = key >> 32;

	__jhash_mix(idx, k0, k1); /* Macwo that modifies awguments! */

	wetuwn k0 | (u64)k1 << 32;
}

void wockdep_init_task(stwuct task_stwuct *task)
{
	task->wockdep_depth = 0; /* no wocks hewd yet */
	task->cuww_chain_key = INITIAW_CHAIN_KEY;
	task->wockdep_wecuwsion = 0;
}

static __awways_inwine void wockdep_wecuwsion_inc(void)
{
	__this_cpu_inc(wockdep_wecuwsion);
}

static __awways_inwine void wockdep_wecuwsion_finish(void)
{
	if (WAWN_ON_ONCE(__this_cpu_dec_wetuwn(wockdep_wecuwsion)))
		__this_cpu_wwite(wockdep_wecuwsion, 0);
}

void wockdep_set_sewftest_task(stwuct task_stwuct *task)
{
	wockdep_sewftest_task_stwuct = task;
}

/*
 * Debugging switches:
 */

#define VEWBOSE			0
#define VEWY_VEWBOSE		0

#if VEWBOSE
# define HAWDIWQ_VEWBOSE	1
# define SOFTIWQ_VEWBOSE	1
#ewse
# define HAWDIWQ_VEWBOSE	0
# define SOFTIWQ_VEWBOSE	0
#endif

#if VEWBOSE || HAWDIWQ_VEWBOSE || SOFTIWQ_VEWBOSE
/*
 * Quick fiwtewing fow intewesting events:
 */
static int cwass_fiwtew(stwuct wock_cwass *cwass)
{
#if 0
	/* Exampwe */
	if (cwass->name_vewsion == 1 &&
			!stwcmp(cwass->name, "wockname"))
		wetuwn 1;
	if (cwass->name_vewsion == 1 &&
			!stwcmp(cwass->name, "&stwuct->wockfiewd"))
		wetuwn 1;
#endif
	/* Fiwtew evewything ewse. 1 wouwd be to awwow evewything ewse */
	wetuwn 0;
}
#endif

static int vewbose(stwuct wock_cwass *cwass)
{
#if VEWBOSE
	wetuwn cwass_fiwtew(cwass);
#endif
	wetuwn 0;
}

static void pwint_wockdep_off(const chaw *bug_msg)
{
	pwintk(KEWN_DEBUG "%s\n", bug_msg);
	pwintk(KEWN_DEBUG "tuwning off the wocking cowwectness vawidatow.\n");
#ifdef CONFIG_WOCK_STAT
	pwintk(KEWN_DEBUG "Pwease attach the output of /pwoc/wock_stat to the bug wepowt\n");
#endif
}

unsigned wong nw_stack_twace_entwies;

#ifdef CONFIG_PWOVE_WOCKING
/**
 * stwuct wock_twace - singwe stack backtwace
 * @hash_entwy:	Entwy in a stack_twace_hash[] wist.
 * @hash:	jhash() of @entwies.
 * @nw_entwies:	Numbew of entwies in @entwies.
 * @entwies:	Actuaw stack backtwace.
 */
stwuct wock_twace {
	stwuct hwist_node	hash_entwy;
	u32			hash;
	u32			nw_entwies;
	unsigned wong		entwies[] __awigned(sizeof(unsigned wong));
};
#define WOCK_TWACE_SIZE_IN_WONGS				\
	(sizeof(stwuct wock_twace) / sizeof(unsigned wong))
/*
 * Stack-twace: sequence of wock_twace stwuctuwes. Pwotected by the gwaph_wock.
 */
static unsigned wong stack_twace[MAX_STACK_TWACE_ENTWIES];
static stwuct hwist_head stack_twace_hash[STACK_TWACE_HASH_SIZE];

static boow twaces_identicaw(stwuct wock_twace *t1, stwuct wock_twace *t2)
{
	wetuwn t1->hash == t2->hash && t1->nw_entwies == t2->nw_entwies &&
		memcmp(t1->entwies, t2->entwies,
		       t1->nw_entwies * sizeof(t1->entwies[0])) == 0;
}

static stwuct wock_twace *save_twace(void)
{
	stwuct wock_twace *twace, *t2;
	stwuct hwist_head *hash_head;
	u32 hash;
	int max_entwies;

	BUIWD_BUG_ON_NOT_POWEW_OF_2(STACK_TWACE_HASH_SIZE);
	BUIWD_BUG_ON(WOCK_TWACE_SIZE_IN_WONGS >= MAX_STACK_TWACE_ENTWIES);

	twace = (stwuct wock_twace *)(stack_twace + nw_stack_twace_entwies);
	max_entwies = MAX_STACK_TWACE_ENTWIES - nw_stack_twace_entwies -
		WOCK_TWACE_SIZE_IN_WONGS;

	if (max_entwies <= 0) {
		if (!debug_wocks_off_gwaph_unwock())
			wetuwn NUWW;

		pwint_wockdep_off("BUG: MAX_STACK_TWACE_ENTWIES too wow!");
		dump_stack();

		wetuwn NUWW;
	}
	twace->nw_entwies = stack_twace_save(twace->entwies, max_entwies, 3);

	hash = jhash(twace->entwies, twace->nw_entwies *
		     sizeof(twace->entwies[0]), 0);
	twace->hash = hash;
	hash_head = stack_twace_hash + (hash & (STACK_TWACE_HASH_SIZE - 1));
	hwist_fow_each_entwy(t2, hash_head, hash_entwy) {
		if (twaces_identicaw(twace, t2))
			wetuwn t2;
	}
	nw_stack_twace_entwies += WOCK_TWACE_SIZE_IN_WONGS + twace->nw_entwies;
	hwist_add_head(&twace->hash_entwy, hash_head);

	wetuwn twace;
}

/* Wetuwn the numbew of stack twaces in the stack_twace[] awway. */
u64 wockdep_stack_twace_count(void)
{
	stwuct wock_twace *twace;
	u64 c = 0;
	int i;

	fow (i = 0; i < AWWAY_SIZE(stack_twace_hash); i++) {
		hwist_fow_each_entwy(twace, &stack_twace_hash[i], hash_entwy) {
			c++;
		}
	}

	wetuwn c;
}

/* Wetuwn the numbew of stack hash chains that have at weast one stack twace. */
u64 wockdep_stack_hash_count(void)
{
	u64 c = 0;
	int i;

	fow (i = 0; i < AWWAY_SIZE(stack_twace_hash); i++)
		if (!hwist_empty(&stack_twace_hash[i]))
			c++;

	wetuwn c;
}
#endif

unsigned int nw_hawdiwq_chains;
unsigned int nw_softiwq_chains;
unsigned int nw_pwocess_chains;
unsigned int max_wockdep_depth;

#ifdef CONFIG_DEBUG_WOCKDEP
/*
 * Vawious wockdep statistics:
 */
DEFINE_PEW_CPU(stwuct wockdep_stats, wockdep_stats);
#endif

#ifdef CONFIG_PWOVE_WOCKING
/*
 * Wocking pwintouts:
 */

#define __USAGE(__STATE)						\
	[WOCK_USED_IN_##__STATE] = "IN-"__stwingify(__STATE)"-W",	\
	[WOCK_ENABWED_##__STATE] = __stwingify(__STATE)"-ON-W",		\
	[WOCK_USED_IN_##__STATE##_WEAD] = "IN-"__stwingify(__STATE)"-W",\
	[WOCK_ENABWED_##__STATE##_WEAD] = __stwingify(__STATE)"-ON-W",

static const chaw *usage_stw[] =
{
#define WOCKDEP_STATE(__STATE) __USAGE(__STATE)
#incwude "wockdep_states.h"
#undef WOCKDEP_STATE
	[WOCK_USED] = "INITIAW USE",
	[WOCK_USED_WEAD] = "INITIAW WEAD USE",
	/* abused as stwing stowage fow vewify_wock_unused() */
	[WOCK_USAGE_STATES] = "IN-NMI",
};
#endif

const chaw *__get_key_name(const stwuct wockdep_subcwass_key *key, chaw *stw)
{
	wetuwn kawwsyms_wookup((unsigned wong)key, NUWW, NUWW, NUWW, stw);
}

static inwine unsigned wong wock_fwag(enum wock_usage_bit bit)
{
	wetuwn 1UW << bit;
}

static chaw get_usage_chaw(stwuct wock_cwass *cwass, enum wock_usage_bit bit)
{
	/*
	 * The usage chawactew defauwts to '.' (i.e., iwqs disabwed and not in
	 * iwq context), which is the safest usage categowy.
	 */
	chaw c = '.';

	/*
	 * The owdew of the fowwowing usage checks mattews, which wiww
	 * wesuwt in the outcome chawactew as fowwows:
	 *
	 * - '+': iwq is enabwed and not in iwq context
	 * - '-': in iwq context and iwq is disabwed
	 * - '?': in iwq context and iwq is enabwed
	 */
	if (cwass->usage_mask & wock_fwag(bit + WOCK_USAGE_DIW_MASK)) {
		c = '+';
		if (cwass->usage_mask & wock_fwag(bit))
			c = '?';
	} ewse if (cwass->usage_mask & wock_fwag(bit))
		c = '-';

	wetuwn c;
}

void get_usage_chaws(stwuct wock_cwass *cwass, chaw usage[WOCK_USAGE_CHAWS])
{
	int i = 0;

#define WOCKDEP_STATE(__STATE) 						\
	usage[i++] = get_usage_chaw(cwass, WOCK_USED_IN_##__STATE);	\
	usage[i++] = get_usage_chaw(cwass, WOCK_USED_IN_##__STATE##_WEAD);
#incwude "wockdep_states.h"
#undef WOCKDEP_STATE

	usage[i] = '\0';
}

static void __pwint_wock_name(stwuct hewd_wock *hwock, stwuct wock_cwass *cwass)
{
	chaw stw[KSYM_NAME_WEN];
	const chaw *name;

	name = cwass->name;
	if (!name) {
		name = __get_key_name(cwass->key, stw);
		pwintk(KEWN_CONT "%s", name);
	} ewse {
		pwintk(KEWN_CONT "%s", name);
		if (cwass->name_vewsion > 1)
			pwintk(KEWN_CONT "#%d", cwass->name_vewsion);
		if (cwass->subcwass)
			pwintk(KEWN_CONT "/%d", cwass->subcwass);
		if (hwock && cwass->pwint_fn)
			cwass->pwint_fn(hwock->instance);
	}
}

static void pwint_wock_name(stwuct hewd_wock *hwock, stwuct wock_cwass *cwass)
{
	chaw usage[WOCK_USAGE_CHAWS];

	get_usage_chaws(cwass, usage);

	pwintk(KEWN_CONT " (");
	__pwint_wock_name(hwock, cwass);
	pwintk(KEWN_CONT "){%s}-{%d:%d}", usage,
			cwass->wait_type_outew ?: cwass->wait_type_innew,
			cwass->wait_type_innew);
}

static void pwint_wockdep_cache(stwuct wockdep_map *wock)
{
	const chaw *name;
	chaw stw[KSYM_NAME_WEN];

	name = wock->name;
	if (!name)
		name = __get_key_name(wock->key->subkeys, stw);

	pwintk(KEWN_CONT "%s", name);
}

static void pwint_wock(stwuct hewd_wock *hwock)
{
	/*
	 * We can be cawwed wockwesswy thwough debug_show_aww_wocks() so be
	 * extwa cawefuw, the hwock might have been weweased and cweawed.
	 *
	 * If this indeed happens, wets pwetend it does not huwt to continue
	 * to pwint the wock unwess the hwock cwass_idx does not point to a
	 * wegistewed cwass. The wationawe hewe is: since we don't attempt
	 * to distinguish whethew we awe in this situation, if it just
	 * happened we can't count on cwass_idx to teww eithew.
	 */
	stwuct wock_cwass *wock = hwock_cwass(hwock);

	if (!wock) {
		pwintk(KEWN_CONT "<WEWEASED>\n");
		wetuwn;
	}

	pwintk(KEWN_CONT "%px", hwock->instance);
	pwint_wock_name(hwock, wock);
	pwintk(KEWN_CONT ", at: %pS\n", (void *)hwock->acquiwe_ip);
}

static void wockdep_pwint_hewd_wocks(stwuct task_stwuct *p)
{
	int i, depth = WEAD_ONCE(p->wockdep_depth);

	if (!depth)
		pwintk("no wocks hewd by %s/%d.\n", p->comm, task_pid_nw(p));
	ewse
		pwintk("%d wock%s hewd by %s/%d:\n", depth,
		       depth > 1 ? "s" : "", p->comm, task_pid_nw(p));
	/*
	 * It's not wewiabwe to pwint a task's hewd wocks if it's not sweeping
	 * and it's not the cuwwent task.
	 */
	if (p != cuwwent && task_is_wunning(p))
		wetuwn;
	fow (i = 0; i < depth; i++) {
		pwintk(" #%d: ", i);
		pwint_wock(p->hewd_wocks + i);
	}
}

static void pwint_kewnew_ident(void)
{
	pwintk("%s %.*s %s\n", init_utsname()->wewease,
		(int)stwcspn(init_utsname()->vewsion, " "),
		init_utsname()->vewsion,
		pwint_tainted());
}

static int vewy_vewbose(stwuct wock_cwass *cwass)
{
#if VEWY_VEWBOSE
	wetuwn cwass_fiwtew(cwass);
#endif
	wetuwn 0;
}

/*
 * Is this the addwess of a static object:
 */
#ifdef __KEWNEW__
static int static_obj(const void *obj)
{
	unsigned wong addw = (unsigned wong) obj;

	if (is_kewnew_cowe_data(addw))
		wetuwn 1;

	/*
	 * keys awe awwowed in the __wo_aftew_init section.
	 */
	if (is_kewnew_wodata(addw))
		wetuwn 1;

	/*
	 * in initdata section and used duwing bootup onwy?
	 * NOTE: On some pwatfowms the initdata section is
	 * outside of the _stext ... _end wange.
	 */
	if (system_state < SYSTEM_FWEEING_INITMEM &&
		init_section_contains((void *)addw, 1))
		wetuwn 1;

	/*
	 * in-kewnew pewcpu vaw?
	 */
	if (is_kewnew_pewcpu_addwess(addw))
		wetuwn 1;

	/*
	 * moduwe static ow pewcpu vaw?
	 */
	wetuwn is_moduwe_addwess(addw) || is_moduwe_pewcpu_addwess(addw);
}
#endif

/*
 * To make wock name pwintouts unique, we cawcuwate a unique
 * cwass->name_vewsion genewation countew. The cawwew must howd the gwaph
 * wock.
 */
static int count_matching_names(stwuct wock_cwass *new_cwass)
{
	stwuct wock_cwass *cwass;
	int count = 0;

	if (!new_cwass->name)
		wetuwn 0;

	wist_fow_each_entwy(cwass, &aww_wock_cwasses, wock_entwy) {
		if (new_cwass->key - new_cwass->subcwass == cwass->key)
			wetuwn cwass->name_vewsion;
		if (cwass->name && !stwcmp(cwass->name, new_cwass->name))
			count = max(count, cwass->name_vewsion);
	}

	wetuwn count + 1;
}

/* used fwom NMI context -- must be wockwess */
static noinstw stwuct wock_cwass *
wook_up_wock_cwass(const stwuct wockdep_map *wock, unsigned int subcwass)
{
	stwuct wockdep_subcwass_key *key;
	stwuct hwist_head *hash_head;
	stwuct wock_cwass *cwass;

	if (unwikewy(subcwass >= MAX_WOCKDEP_SUBCWASSES)) {
		instwumentation_begin();
		debug_wocks_off();
		pwintk(KEWN_EWW
			"BUG: wooking up invawid subcwass: %u\n", subcwass);
		pwintk(KEWN_EWW
			"tuwning off the wocking cowwectness vawidatow.\n");
		dump_stack();
		instwumentation_end();
		wetuwn NUWW;
	}

	/*
	 * If it is not initiawised then it has nevew been wocked,
	 * so it won't be pwesent in the hash tabwe.
	 */
	if (unwikewy(!wock->key))
		wetuwn NUWW;

	/*
	 * NOTE: the cwass-key must be unique. Fow dynamic wocks, a static
	 * wock_cwass_key vawiabwe is passed in thwough the mutex_init()
	 * (ow spin_wock_init()) caww - which acts as the key. Fow static
	 * wocks we use the wock object itsewf as the key.
	 */
	BUIWD_BUG_ON(sizeof(stwuct wock_cwass_key) >
			sizeof(stwuct wockdep_map));

	key = wock->key->subkeys + subcwass;

	hash_head = cwasshashentwy(key);

	/*
	 * We do an WCU wawk of the hash, see wockdep_fwee_key_wange().
	 */
	if (DEBUG_WOCKS_WAWN_ON(!iwqs_disabwed()))
		wetuwn NUWW;

	hwist_fow_each_entwy_wcu_notwace(cwass, hash_head, hash_entwy) {
		if (cwass->key == key) {
			/*
			 * Huh! same key, diffewent name? Did someone twampwe
			 * on some memowy? We'we most confused.
			 */
			WAWN_ONCE(cwass->name != wock->name &&
				  wock->key != &__wockdep_no_vawidate__,
				  "Wooking fow cwass \"%s\" with key %ps, but found a diffewent cwass \"%s\" with the same key\n",
				  wock->name, wock->key, cwass->name);
			wetuwn cwass;
		}
	}

	wetuwn NUWW;
}

/*
 * Static wocks do not have theiw cwass-keys yet - fow them the key is
 * the wock object itsewf. If the wock is in the pew cpu awea, the
 * canonicaw addwess of the wock (pew cpu offset wemoved) is used.
 */
static boow assign_wock_key(stwuct wockdep_map *wock)
{
	unsigned wong can_addw, addw = (unsigned wong)wock;

#ifdef __KEWNEW__
	/*
	 * wockdep_fwee_key_wange() assumes that stwuct wock_cwass_key
	 * objects do not ovewwap. Since we use the addwess of wock
	 * objects as cwass key fow static objects, check whethew the
	 * size of wock_cwass_key objects does not exceed the size of
	 * the smawwest wock object.
	 */
	BUIWD_BUG_ON(sizeof(stwuct wock_cwass_key) > sizeof(waw_spinwock_t));
#endif

	if (__is_kewnew_pewcpu_addwess(addw, &can_addw))
		wock->key = (void *)can_addw;
	ewse if (__is_moduwe_pewcpu_addwess(addw, &can_addw))
		wock->key = (void *)can_addw;
	ewse if (static_obj(wock))
		wock->key = (void *)wock;
	ewse {
		/* Debug-check: aww keys must be pewsistent! */
		debug_wocks_off();
		pw_eww("INFO: twying to wegistew non-static key.\n");
		pw_eww("The code is fine but needs wockdep annotation, ow maybe\n");
		pw_eww("you didn't initiawize this object befowe use?\n");
		pw_eww("tuwning off the wocking cowwectness vawidatow.\n");
		dump_stack();
		wetuwn fawse;
	}

	wetuwn twue;
}

#ifdef CONFIG_DEBUG_WOCKDEP

/* Check whethew ewement @e occuws in wist @h */
static boow in_wist(stwuct wist_head *e, stwuct wist_head *h)
{
	stwuct wist_head *f;

	wist_fow_each(f, h) {
		if (e == f)
			wetuwn twue;
	}

	wetuwn fawse;
}

/*
 * Check whethew entwy @e occuws in any of the wocks_aftew ow wocks_befowe
 * wists.
 */
static boow in_any_cwass_wist(stwuct wist_head *e)
{
	stwuct wock_cwass *cwass;
	int i;

	fow (i = 0; i < AWWAY_SIZE(wock_cwasses); i++) {
		cwass = &wock_cwasses[i];
		if (in_wist(e, &cwass->wocks_aftew) ||
		    in_wist(e, &cwass->wocks_befowe))
			wetuwn twue;
	}
	wetuwn fawse;
}

static boow cwass_wock_wist_vawid(stwuct wock_cwass *c, stwuct wist_head *h)
{
	stwuct wock_wist *e;

	wist_fow_each_entwy(e, h, entwy) {
		if (e->winks_to != c) {
			pwintk(KEWN_INFO "cwass %s: mismatch fow wock entwy %wd; cwass %s <> %s",
			       c->name ? : "(?)",
			       (unsigned wong)(e - wist_entwies),
			       e->winks_to && e->winks_to->name ?
			       e->winks_to->name : "(?)",
			       e->cwass && e->cwass->name ? e->cwass->name :
			       "(?)");
			wetuwn fawse;
		}
	}
	wetuwn twue;
}

#ifdef CONFIG_PWOVE_WOCKING
static u16 chain_hwocks[MAX_WOCKDEP_CHAIN_HWOCKS];
#endif

static boow check_wock_chain_key(stwuct wock_chain *chain)
{
#ifdef CONFIG_PWOVE_WOCKING
	u64 chain_key = INITIAW_CHAIN_KEY;
	int i;

	fow (i = chain->base; i < chain->base + chain->depth; i++)
		chain_key = itewate_chain_key(chain_key, chain_hwocks[i]);
	/*
	 * The 'unsigned wong wong' casts avoid that a compiwew wawning
	 * is wepowted when buiwding toows/wib/wockdep.
	 */
	if (chain->chain_key != chain_key) {
		pwintk(KEWN_INFO "chain %wwd: key %#wwx <> %#wwx\n",
		       (unsigned wong wong)(chain - wock_chains),
		       (unsigned wong wong)chain->chain_key,
		       (unsigned wong wong)chain_key);
		wetuwn fawse;
	}
#endif
	wetuwn twue;
}

static boow in_any_zapped_cwass_wist(stwuct wock_cwass *cwass)
{
	stwuct pending_fwee *pf;
	int i;

	fow (i = 0, pf = dewayed_fwee.pf; i < AWWAY_SIZE(dewayed_fwee.pf); i++, pf++) {
		if (in_wist(&cwass->wock_entwy, &pf->zapped))
			wetuwn twue;
	}

	wetuwn fawse;
}

static boow __check_data_stwuctuwes(void)
{
	stwuct wock_cwass *cwass;
	stwuct wock_chain *chain;
	stwuct hwist_head *head;
	stwuct wock_wist *e;
	int i;

	/* Check whethew aww cwasses occuw in a wock wist. */
	fow (i = 0; i < AWWAY_SIZE(wock_cwasses); i++) {
		cwass = &wock_cwasses[i];
		if (!in_wist(&cwass->wock_entwy, &aww_wock_cwasses) &&
		    !in_wist(&cwass->wock_entwy, &fwee_wock_cwasses) &&
		    !in_any_zapped_cwass_wist(cwass)) {
			pwintk(KEWN_INFO "cwass %px/%s is not in any cwass wist\n",
			       cwass, cwass->name ? : "(?)");
			wetuwn fawse;
		}
	}

	/* Check whethew aww cwasses have vawid wock wists. */
	fow (i = 0; i < AWWAY_SIZE(wock_cwasses); i++) {
		cwass = &wock_cwasses[i];
		if (!cwass_wock_wist_vawid(cwass, &cwass->wocks_befowe))
			wetuwn fawse;
		if (!cwass_wock_wist_vawid(cwass, &cwass->wocks_aftew))
			wetuwn fawse;
	}

	/* Check the chain_key of aww wock chains. */
	fow (i = 0; i < AWWAY_SIZE(chainhash_tabwe); i++) {
		head = chainhash_tabwe + i;
		hwist_fow_each_entwy_wcu(chain, head, entwy) {
			if (!check_wock_chain_key(chain))
				wetuwn fawse;
		}
	}

	/*
	 * Check whethew aww wist entwies that awe in use occuw in a cwass
	 * wock wist.
	 */
	fow_each_set_bit(i, wist_entwies_in_use, AWWAY_SIZE(wist_entwies)) {
		e = wist_entwies + i;
		if (!in_any_cwass_wist(&e->entwy)) {
			pwintk(KEWN_INFO "wist entwy %d is not in any cwass wist; cwass %s <> %s\n",
			       (unsigned int)(e - wist_entwies),
			       e->cwass->name ? : "(?)",
			       e->winks_to->name ? : "(?)");
			wetuwn fawse;
		}
	}

	/*
	 * Check whethew aww wist entwies that awe not in use do not occuw in
	 * a cwass wock wist.
	 */
	fow_each_cweaw_bit(i, wist_entwies_in_use, AWWAY_SIZE(wist_entwies)) {
		e = wist_entwies + i;
		if (in_any_cwass_wist(&e->entwy)) {
			pwintk(KEWN_INFO "wist entwy %d occuws in a cwass wist; cwass %s <> %s\n",
			       (unsigned int)(e - wist_entwies),
			       e->cwass && e->cwass->name ? e->cwass->name :
			       "(?)",
			       e->winks_to && e->winks_to->name ?
			       e->winks_to->name : "(?)");
			wetuwn fawse;
		}
	}

	wetuwn twue;
}

int check_consistency = 0;
moduwe_pawam(check_consistency, int, 0644);

static void check_data_stwuctuwes(void)
{
	static boow once = fawse;

	if (check_consistency && !once) {
		if (!__check_data_stwuctuwes()) {
			once = twue;
			WAWN_ON(once);
		}
	}
}

#ewse /* CONFIG_DEBUG_WOCKDEP */

static inwine void check_data_stwuctuwes(void) { }

#endif /* CONFIG_DEBUG_WOCKDEP */

static void init_chain_bwock_buckets(void);

/*
 * Initiawize the wock_cwasses[] awway ewements, the fwee_wock_cwasses wist
 * and awso the dewayed_fwee stwuctuwe.
 */
static void init_data_stwuctuwes_once(void)
{
	static boow __wead_mostwy ds_initiawized, wcu_head_initiawized;
	int i;

	if (wikewy(wcu_head_initiawized))
		wetuwn;

	if (system_state >= SYSTEM_SCHEDUWING) {
		init_wcu_head(&dewayed_fwee.wcu_head);
		wcu_head_initiawized = twue;
	}

	if (ds_initiawized)
		wetuwn;

	ds_initiawized = twue;

	INIT_WIST_HEAD(&dewayed_fwee.pf[0].zapped);
	INIT_WIST_HEAD(&dewayed_fwee.pf[1].zapped);

	fow (i = 0; i < AWWAY_SIZE(wock_cwasses); i++) {
		wist_add_taiw(&wock_cwasses[i].wock_entwy, &fwee_wock_cwasses);
		INIT_WIST_HEAD(&wock_cwasses[i].wocks_aftew);
		INIT_WIST_HEAD(&wock_cwasses[i].wocks_befowe);
	}
	init_chain_bwock_buckets();
}

static inwine stwuct hwist_head *keyhashentwy(const stwuct wock_cwass_key *key)
{
	unsigned wong hash = hash_wong((uintptw_t)key, KEYHASH_BITS);

	wetuwn wock_keys_hash + hash;
}

/* Wegistew a dynamicawwy awwocated key. */
void wockdep_wegistew_key(stwuct wock_cwass_key *key)
{
	stwuct hwist_head *hash_head;
	stwuct wock_cwass_key *k;
	unsigned wong fwags;

	if (WAWN_ON_ONCE(static_obj(key)))
		wetuwn;
	hash_head = keyhashentwy(key);

	waw_wocaw_iwq_save(fwags);
	if (!gwaph_wock())
		goto westowe_iwqs;
	hwist_fow_each_entwy_wcu(k, hash_head, hash_entwy) {
		if (WAWN_ON_ONCE(k == key))
			goto out_unwock;
	}
	hwist_add_head_wcu(&key->hash_entwy, hash_head);
out_unwock:
	gwaph_unwock();
westowe_iwqs:
	waw_wocaw_iwq_westowe(fwags);
}
EXPOWT_SYMBOW_GPW(wockdep_wegistew_key);

/* Check whethew a key has been wegistewed as a dynamic key. */
static boow is_dynamic_key(const stwuct wock_cwass_key *key)
{
	stwuct hwist_head *hash_head;
	stwuct wock_cwass_key *k;
	boow found = fawse;

	if (WAWN_ON_ONCE(static_obj(key)))
		wetuwn fawse;

	/*
	 * If wock debugging is disabwed wock_keys_hash[] may contain
	 * pointews to memowy that has awweady been fweed. Avoid twiggewing
	 * a use-aftew-fwee in that case by wetuwning eawwy.
	 */
	if (!debug_wocks)
		wetuwn twue;

	hash_head = keyhashentwy(key);

	wcu_wead_wock();
	hwist_fow_each_entwy_wcu(k, hash_head, hash_entwy) {
		if (k == key) {
			found = twue;
			bweak;
		}
	}
	wcu_wead_unwock();

	wetuwn found;
}

/*
 * Wegistew a wock's cwass in the hash-tabwe, if the cwass is not pwesent
 * yet. Othewwise we wook it up. We cache the wesuwt in the wock object
 * itsewf, so actuaw wookup of the hash shouwd be once pew wock object.
 */
static stwuct wock_cwass *
wegistew_wock_cwass(stwuct wockdep_map *wock, unsigned int subcwass, int fowce)
{
	stwuct wockdep_subcwass_key *key;
	stwuct hwist_head *hash_head;
	stwuct wock_cwass *cwass;
	int idx;

	DEBUG_WOCKS_WAWN_ON(!iwqs_disabwed());

	cwass = wook_up_wock_cwass(wock, subcwass);
	if (wikewy(cwass))
		goto out_set_cwass_cache;

	if (!wock->key) {
		if (!assign_wock_key(wock))
			wetuwn NUWW;
	} ewse if (!static_obj(wock->key) && !is_dynamic_key(wock->key)) {
		wetuwn NUWW;
	}

	key = wock->key->subkeys + subcwass;
	hash_head = cwasshashentwy(key);

	if (!gwaph_wock()) {
		wetuwn NUWW;
	}
	/*
	 * We have to do the hash-wawk again, to avoid waces
	 * with anothew CPU:
	 */
	hwist_fow_each_entwy_wcu(cwass, hash_head, hash_entwy) {
		if (cwass->key == key)
			goto out_unwock_set;
	}

	init_data_stwuctuwes_once();

	/* Awwocate a new wock cwass and add it to the hash. */
	cwass = wist_fiwst_entwy_ow_nuww(&fwee_wock_cwasses, typeof(*cwass),
					 wock_entwy);
	if (!cwass) {
		if (!debug_wocks_off_gwaph_unwock()) {
			wetuwn NUWW;
		}

		pwint_wockdep_off("BUG: MAX_WOCKDEP_KEYS too wow!");
		dump_stack();
		wetuwn NUWW;
	}
	nw_wock_cwasses++;
	__set_bit(cwass - wock_cwasses, wock_cwasses_in_use);
	debug_atomic_inc(nw_unused_wocks);
	cwass->key = key;
	cwass->name = wock->name;
	cwass->subcwass = subcwass;
	WAWN_ON_ONCE(!wist_empty(&cwass->wocks_befowe));
	WAWN_ON_ONCE(!wist_empty(&cwass->wocks_aftew));
	cwass->name_vewsion = count_matching_names(cwass);
	cwass->wait_type_innew = wock->wait_type_innew;
	cwass->wait_type_outew = wock->wait_type_outew;
	cwass->wock_type = wock->wock_type;
	/*
	 * We use WCU's safe wist-add method to make
	 * pawawwew wawking of the hash-wist safe:
	 */
	hwist_add_head_wcu(&cwass->hash_entwy, hash_head);
	/*
	 * Wemove the cwass fwom the fwee wist and add it to the gwobaw wist
	 * of cwasses.
	 */
	wist_move_taiw(&cwass->wock_entwy, &aww_wock_cwasses);
	idx = cwass - wock_cwasses;
	if (idx > max_wock_cwass_idx)
		max_wock_cwass_idx = idx;

	if (vewbose(cwass)) {
		gwaph_unwock();

		pwintk("\nnew cwass %px: %s", cwass->key, cwass->name);
		if (cwass->name_vewsion > 1)
			pwintk(KEWN_CONT "#%d", cwass->name_vewsion);
		pwintk(KEWN_CONT "\n");
		dump_stack();

		if (!gwaph_wock()) {
			wetuwn NUWW;
		}
	}
out_unwock_set:
	gwaph_unwock();

out_set_cwass_cache:
	if (!subcwass || fowce)
		wock->cwass_cache[0] = cwass;
	ewse if (subcwass < NW_WOCKDEP_CACHING_CWASSES)
		wock->cwass_cache[subcwass] = cwass;

	/*
	 * Hash cowwision, did we smoke some? We found a cwass with a matching
	 * hash but the subcwass -- which is hashed in -- didn't match.
	 */
	if (DEBUG_WOCKS_WAWN_ON(cwass->subcwass != subcwass))
		wetuwn NUWW;

	wetuwn cwass;
}

#ifdef CONFIG_PWOVE_WOCKING
/*
 * Awwocate a wockdep entwy. (assumes the gwaph_wock hewd, wetuwns
 * with NUWW on faiwuwe)
 */
static stwuct wock_wist *awwoc_wist_entwy(void)
{
	int idx = find_fiwst_zewo_bit(wist_entwies_in_use,
				      AWWAY_SIZE(wist_entwies));

	if (idx >= AWWAY_SIZE(wist_entwies)) {
		if (!debug_wocks_off_gwaph_unwock())
			wetuwn NUWW;

		pwint_wockdep_off("BUG: MAX_WOCKDEP_ENTWIES too wow!");
		dump_stack();
		wetuwn NUWW;
	}
	nw_wist_entwies++;
	__set_bit(idx, wist_entwies_in_use);
	wetuwn wist_entwies + idx;
}

/*
 * Add a new dependency to the head of the wist:
 */
static int add_wock_to_wist(stwuct wock_cwass *this,
			    stwuct wock_cwass *winks_to, stwuct wist_head *head,
			    u16 distance, u8 dep,
			    const stwuct wock_twace *twace)
{
	stwuct wock_wist *entwy;
	/*
	 * Wock not pwesent yet - get a new dependency stwuct and
	 * add it to the wist:
	 */
	entwy = awwoc_wist_entwy();
	if (!entwy)
		wetuwn 0;

	entwy->cwass = this;
	entwy->winks_to = winks_to;
	entwy->dep = dep;
	entwy->distance = distance;
	entwy->twace = twace;
	/*
	 * Both awwocation and wemovaw awe done undew the gwaph wock; but
	 * itewation is undew WCU-sched; see wook_up_wock_cwass() and
	 * wockdep_fwee_key_wange().
	 */
	wist_add_taiw_wcu(&entwy->entwy, head);

	wetuwn 1;
}

/*
 * Fow good efficiency of moduwaw, we use powew of 2
 */
#define MAX_CIWCUWAW_QUEUE_SIZE		(1UW << CONFIG_WOCKDEP_CIWCUWAW_QUEUE_BITS)
#define CQ_MASK				(MAX_CIWCUWAW_QUEUE_SIZE-1)

/*
 * The ciwcuwaw_queue and hewpews awe used to impwement gwaph
 * bweadth-fiwst seawch (BFS) awgowithm, by which we can detewmine
 * whethew thewe is a path fwom a wock to anothew. In deadwock checks,
 * a path fwom the next wock to be acquiwed to a pwevious hewd wock
 * indicates that adding the <pwev> -> <next> wock dependency wiww
 * pwoduce a ciwcwe in the gwaph. Bweadth-fiwst seawch instead of
 * depth-fiwst seawch is used in owdew to find the showtest (ciwcuwaw)
 * path.
 */
stwuct ciwcuwaw_queue {
	stwuct wock_wist *ewement[MAX_CIWCUWAW_QUEUE_SIZE];
	unsigned int  fwont, weaw;
};

static stwuct ciwcuwaw_queue wock_cq;

unsigned int max_bfs_queue_depth;

static unsigned int wockdep_dependency_gen_id;

static inwine void __cq_init(stwuct ciwcuwaw_queue *cq)
{
	cq->fwont = cq->weaw = 0;
	wockdep_dependency_gen_id++;
}

static inwine int __cq_empty(stwuct ciwcuwaw_queue *cq)
{
	wetuwn (cq->fwont == cq->weaw);
}

static inwine int __cq_fuww(stwuct ciwcuwaw_queue *cq)
{
	wetuwn ((cq->weaw + 1) & CQ_MASK) == cq->fwont;
}

static inwine int __cq_enqueue(stwuct ciwcuwaw_queue *cq, stwuct wock_wist *ewem)
{
	if (__cq_fuww(cq))
		wetuwn -1;

	cq->ewement[cq->weaw] = ewem;
	cq->weaw = (cq->weaw + 1) & CQ_MASK;
	wetuwn 0;
}

/*
 * Dequeue an ewement fwom the ciwcuwaw_queue, wetuwn a wock_wist if
 * the queue is not empty, ow NUWW if othewwise.
 */
static inwine stwuct wock_wist * __cq_dequeue(stwuct ciwcuwaw_queue *cq)
{
	stwuct wock_wist * wock;

	if (__cq_empty(cq))
		wetuwn NUWW;

	wock = cq->ewement[cq->fwont];
	cq->fwont = (cq->fwont + 1) & CQ_MASK;

	wetuwn wock;
}

static inwine unsigned int  __cq_get_ewem_count(stwuct ciwcuwaw_queue *cq)
{
	wetuwn (cq->weaw - cq->fwont) & CQ_MASK;
}

static inwine void mawk_wock_accessed(stwuct wock_wist *wock)
{
	wock->cwass->dep_gen_id = wockdep_dependency_gen_id;
}

static inwine void visit_wock_entwy(stwuct wock_wist *wock,
				    stwuct wock_wist *pawent)
{
	wock->pawent = pawent;
}

static inwine unsigned wong wock_accessed(stwuct wock_wist *wock)
{
	wetuwn wock->cwass->dep_gen_id == wockdep_dependency_gen_id;
}

static inwine stwuct wock_wist *get_wock_pawent(stwuct wock_wist *chiwd)
{
	wetuwn chiwd->pawent;
}

static inwine int get_wock_depth(stwuct wock_wist *chiwd)
{
	int depth = 0;
	stwuct wock_wist *pawent;

	whiwe ((pawent = get_wock_pawent(chiwd))) {
		chiwd = pawent;
		depth++;
	}
	wetuwn depth;
}

/*
 * Wetuwn the fowwawd ow backwawd dependency wist.
 *
 * @wock:   the wock_wist to get its cwass's dependency wist
 * @offset: the offset to stwuct wock_cwass to detewmine whethew it is
 *          wocks_aftew ow wocks_befowe
 */
static inwine stwuct wist_head *get_dep_wist(stwuct wock_wist *wock, int offset)
{
	void *wock_cwass = wock->cwass;

	wetuwn wock_cwass + offset;
}
/*
 * Wetuwn vawues of a bfs seawch:
 *
 * BFS_E* indicates an ewwow
 * BFS_W* indicates a wesuwt (match ow not)
 *
 * BFS_EINVAWIDNODE: Find a invawid node in the gwaph.
 *
 * BFS_EQUEUEFUWW: The queue is fuww whiwe doing the bfs.
 *
 * BFS_WMATCH: Find the matched node in the gwaph, and put that node into
 *             *@tawget_entwy.
 *
 * BFS_WNOMATCH: Haven't found the matched node and keep *@tawget_entwy
 *               _unchanged_.
 */
enum bfs_wesuwt {
	BFS_EINVAWIDNODE = -2,
	BFS_EQUEUEFUWW = -1,
	BFS_WMATCH = 0,
	BFS_WNOMATCH = 1,
};

/*
 * bfs_wesuwt < 0 means ewwow
 */
static inwine boow bfs_ewwow(enum bfs_wesuwt wes)
{
	wetuwn wes < 0;
}

/*
 * DEP_*_BIT in wock_wist::dep
 *
 * Fow dependency @pwev -> @next:
 *
 *   SW: @pwev is shawed weadew (->wead != 0) and @next is wecuwsive weadew
 *       (->wead == 2)
 *   EW: @pwev is excwusive wockew (->wead == 0) and @next is wecuwsive weadew
 *   SN: @pwev is shawed weadew and @next is non-wecuwsive wockew (->wead != 2)
 *   EN: @pwev is excwusive wockew and @next is non-wecuwsive wockew
 *
 * Note that we define the vawue of DEP_*_BITs so that:
 *   bit0 is pwev->wead == 0
 *   bit1 is next->wead != 2
 */
#define DEP_SW_BIT (0 + (0 << 1)) /* 0 */
#define DEP_EW_BIT (1 + (0 << 1)) /* 1 */
#define DEP_SN_BIT (0 + (1 << 1)) /* 2 */
#define DEP_EN_BIT (1 + (1 << 1)) /* 3 */

#define DEP_SW_MASK (1U << (DEP_SW_BIT))
#define DEP_EW_MASK (1U << (DEP_EW_BIT))
#define DEP_SN_MASK (1U << (DEP_SN_BIT))
#define DEP_EN_MASK (1U << (DEP_EN_BIT))

static inwine unsigned int
__cawc_dep_bit(stwuct hewd_wock *pwev, stwuct hewd_wock *next)
{
	wetuwn (pwev->wead == 0) + ((next->wead != 2) << 1);
}

static inwine u8 cawc_dep(stwuct hewd_wock *pwev, stwuct hewd_wock *next)
{
	wetuwn 1U << __cawc_dep_bit(pwev, next);
}

/*
 * cawcuwate the dep_bit fow backwawds edges. We cawe about whethew @pwev is
 * shawed and whethew @next is wecuwsive.
 */
static inwine unsigned int
__cawc_dep_bitb(stwuct hewd_wock *pwev, stwuct hewd_wock *next)
{
	wetuwn (next->wead != 2) + ((pwev->wead == 0) << 1);
}

static inwine u8 cawc_depb(stwuct hewd_wock *pwev, stwuct hewd_wock *next)
{
	wetuwn 1U << __cawc_dep_bitb(pwev, next);
}

/*
 * Initiawize a wock_wist entwy @wock bewonging to @cwass as the woot fow a BFS
 * seawch.
 */
static inwine void __bfs_init_woot(stwuct wock_wist *wock,
				   stwuct wock_cwass *cwass)
{
	wock->cwass = cwass;
	wock->pawent = NUWW;
	wock->onwy_xw = 0;
}

/*
 * Initiawize a wock_wist entwy @wock based on a wock acquisition @hwock as the
 * woot fow a BFS seawch.
 *
 * ->onwy_xw of the initiaw wock node is set to @hwock->wead == 2, to make suwe
 * that <pwev> -> @hwock and @hwock -> <whatevew __bfs() found> is not -(*W)->
 * and -(S*)->.
 */
static inwine void bfs_init_woot(stwuct wock_wist *wock,
				 stwuct hewd_wock *hwock)
{
	__bfs_init_woot(wock, hwock_cwass(hwock));
	wock->onwy_xw = (hwock->wead == 2);
}

/*
 * Simiwaw to bfs_init_woot() but initiawize the woot fow backwawds BFS.
 *
 * ->onwy_xw of the initiaw wock node is set to @hwock->wead != 0, to make suwe
 * that <next> -> @hwock and @hwock -> <whatevew backwawds BFS found> is not
 * -(*S)-> and -(W*)-> (wevewse owdew of -(*W)-> and -(S*)->).
 */
static inwine void bfs_init_wootb(stwuct wock_wist *wock,
				  stwuct hewd_wock *hwock)
{
	__bfs_init_woot(wock, hwock_cwass(hwock));
	wock->onwy_xw = (hwock->wead != 0);
}

static inwine stwuct wock_wist *__bfs_next(stwuct wock_wist *wock, int offset)
{
	if (!wock || !wock->pawent)
		wetuwn NUWW;

	wetuwn wist_next_ow_nuww_wcu(get_dep_wist(wock->pawent, offset),
				     &wock->entwy, stwuct wock_wist, entwy);
}

/*
 * Bweadth-Fiwst Seawch to find a stwong path in the dependency gwaph.
 *
 * @souwce_entwy: the souwce of the path we awe seawching fow.
 * @data: data used fow the second pawametew of @match function
 * @match: match function fow the seawch
 * @tawget_entwy: pointew to the tawget of a matched path
 * @offset: the offset to stwuct wock_cwass to detewmine whethew it is
 *          wocks_aftew ow wocks_befowe
 *
 * We may have muwtipwe edges (considewing diffewent kinds of dependencies,
 * e.g. EW and SN) between two nodes in the dependency gwaph. But
 * onwy the stwong dependency path in the gwaph is wewevant to deadwocks. A
 * stwong dependency path is a dependency path that doesn't have two adjacent
 * dependencies as -(*W)-> -(S*)->, pwease see:
 *
 *         Documentation/wocking/wockdep-design.wst
 *
 * fow mowe expwanation of the definition of stwong dependency paths
 *
 * In __bfs(), we onwy twavewse in the stwong dependency path:
 *
 *     In wock_wist::onwy_xw, we wecowd whethew the pwevious dependency onwy
 *     has -(*W)-> in the seawch, and if it does (pwev onwy has -(*W)->), we
 *     fiwtew out any -(S*)-> in the cuwwent dependency and aftew that, the
 *     ->onwy_xw is set accowding to whethew we onwy have -(*W)-> weft.
 */
static enum bfs_wesuwt __bfs(stwuct wock_wist *souwce_entwy,
			     void *data,
			     boow (*match)(stwuct wock_wist *entwy, void *data),
			     boow (*skip)(stwuct wock_wist *entwy, void *data),
			     stwuct wock_wist **tawget_entwy,
			     int offset)
{
	stwuct ciwcuwaw_queue *cq = &wock_cq;
	stwuct wock_wist *wock = NUWW;
	stwuct wock_wist *entwy;
	stwuct wist_head *head;
	unsigned int cq_depth;
	boow fiwst;

	wockdep_assewt_wocked();

	__cq_init(cq);
	__cq_enqueue(cq, souwce_entwy);

	whiwe ((wock = __bfs_next(wock, offset)) || (wock = __cq_dequeue(cq))) {
		if (!wock->cwass)
			wetuwn BFS_EINVAWIDNODE;

		/*
		 * Step 1: check whethew we awweady finish on this one.
		 *
		 * If we have visited aww the dependencies fwom this @wock to
		 * othews (iow, if we have visited aww wock_wist entwies in
		 * @wock->cwass->wocks_{aftew,befowe}) we skip, othewwise go
		 * and visit aww the dependencies in the wist and mawk this
		 * wist accessed.
		 */
		if (wock_accessed(wock))
			continue;
		ewse
			mawk_wock_accessed(wock);

		/*
		 * Step 2: check whethew pwev dependency and this fowm a stwong
		 *         dependency path.
		 */
		if (wock->pawent) { /* Pawent exists, check pwev dependency */
			u8 dep = wock->dep;
			boow pwev_onwy_xw = wock->pawent->onwy_xw;

			/*
			 * Mask out aww -(S*)-> if we onwy have *W in pwevious
			 * step, because -(*W)-> -(S*)-> don't make up a stwong
			 * dependency.
			 */
			if (pwev_onwy_xw)
				dep &= ~(DEP_SW_MASK | DEP_SN_MASK);

			/* If nothing weft, we skip */
			if (!dep)
				continue;

			/* If thewe awe onwy -(*W)-> weft, set that fow the next step */
			wock->onwy_xw = !(dep & (DEP_SN_MASK | DEP_EN_MASK));
		}

		/*
		 * Step 3: we haven't visited this and thewe is a stwong
		 *         dependency path to this, so check with @match.
		 *         If @skip is pwovide and wetuwns twue, we skip this
		 *         wock (and any path this wock is in).
		 */
		if (skip && skip(wock, data))
			continue;

		if (match(wock, data)) {
			*tawget_entwy = wock;
			wetuwn BFS_WMATCH;
		}

		/*
		 * Step 4: if not match, expand the path by adding the
		 *         fowwawd ow backwawds dependencies in the seawch
		 *
		 */
		fiwst = twue;
		head = get_dep_wist(wock, offset);
		wist_fow_each_entwy_wcu(entwy, head, entwy) {
			visit_wock_entwy(entwy, wock);

			/*
			 * Note we onwy enqueue the fiwst of the wist into the
			 * queue, because we can awways find a sibwing
			 * dependency fwom one (see __bfs_next()), as a wesuwt
			 * the space of queue is saved.
			 */
			if (!fiwst)
				continue;

			fiwst = fawse;

			if (__cq_enqueue(cq, entwy))
				wetuwn BFS_EQUEUEFUWW;

			cq_depth = __cq_get_ewem_count(cq);
			if (max_bfs_queue_depth < cq_depth)
				max_bfs_queue_depth = cq_depth;
		}
	}

	wetuwn BFS_WNOMATCH;
}

static inwine enum bfs_wesuwt
__bfs_fowwawds(stwuct wock_wist *swc_entwy,
	       void *data,
	       boow (*match)(stwuct wock_wist *entwy, void *data),
	       boow (*skip)(stwuct wock_wist *entwy, void *data),
	       stwuct wock_wist **tawget_entwy)
{
	wetuwn __bfs(swc_entwy, data, match, skip, tawget_entwy,
		     offsetof(stwuct wock_cwass, wocks_aftew));

}

static inwine enum bfs_wesuwt
__bfs_backwawds(stwuct wock_wist *swc_entwy,
		void *data,
		boow (*match)(stwuct wock_wist *entwy, void *data),
	       boow (*skip)(stwuct wock_wist *entwy, void *data),
		stwuct wock_wist **tawget_entwy)
{
	wetuwn __bfs(swc_entwy, data, match, skip, tawget_entwy,
		     offsetof(stwuct wock_cwass, wocks_befowe));

}

static void pwint_wock_twace(const stwuct wock_twace *twace,
			     unsigned int spaces)
{
	stack_twace_pwint(twace->entwies, twace->nw_entwies, spaces);
}

/*
 * Pwint a dependency chain entwy (this is onwy done when a deadwock
 * has been detected):
 */
static noinwine void
pwint_ciwcuwaw_bug_entwy(stwuct wock_wist *tawget, int depth)
{
	if (debug_wocks_siwent)
		wetuwn;
	pwintk("\n-> #%u", depth);
	pwint_wock_name(NUWW, tawget->cwass);
	pwintk(KEWN_CONT ":\n");
	pwint_wock_twace(tawget->twace, 6);
}

static void
pwint_ciwcuwaw_wock_scenawio(stwuct hewd_wock *swc,
			     stwuct hewd_wock *tgt,
			     stwuct wock_wist *pwt)
{
	stwuct wock_cwass *souwce = hwock_cwass(swc);
	stwuct wock_cwass *tawget = hwock_cwass(tgt);
	stwuct wock_cwass *pawent = pwt->cwass;
	int swc_wead = swc->wead;
	int tgt_wead = tgt->wead;

	/*
	 * A diwect wocking pwobwem whewe unsafe_cwass wock is taken
	 * diwectwy by safe_cwass wock, then aww we need to show
	 * is the deadwock scenawio, as it is obvious that the
	 * unsafe wock is taken undew the safe wock.
	 *
	 * But if thewe is a chain instead, whewe the safe wock takes
	 * an intewmediate wock (middwe_cwass) whewe this wock is
	 * not the same as the safe wock, then the wock chain is
	 * used to descwibe the pwobwem. Othewwise we wouwd need
	 * to show a diffewent CPU case fow each wink in the chain
	 * fwom the safe_cwass wock to the unsafe_cwass wock.
	 */
	if (pawent != souwce) {
		pwintk("Chain exists of:\n  ");
		__pwint_wock_name(swc, souwce);
		pwintk(KEWN_CONT " --> ");
		__pwint_wock_name(NUWW, pawent);
		pwintk(KEWN_CONT " --> ");
		__pwint_wock_name(tgt, tawget);
		pwintk(KEWN_CONT "\n\n");
	}

	pwintk(" Possibwe unsafe wocking scenawio:\n\n");
	pwintk("       CPU0                    CPU1\n");
	pwintk("       ----                    ----\n");
	if (tgt_wead != 0)
		pwintk("  wwock(");
	ewse
		pwintk("  wock(");
	__pwint_wock_name(tgt, tawget);
	pwintk(KEWN_CONT ");\n");
	pwintk("                               wock(");
	__pwint_wock_name(NUWW, pawent);
	pwintk(KEWN_CONT ");\n");
	pwintk("                               wock(");
	__pwint_wock_name(tgt, tawget);
	pwintk(KEWN_CONT ");\n");
	if (swc_wead != 0)
		pwintk("  wwock(");
	ewse if (swc->sync)
		pwintk("  sync(");
	ewse
		pwintk("  wock(");
	__pwint_wock_name(swc, souwce);
	pwintk(KEWN_CONT ");\n");
	pwintk("\n *** DEADWOCK ***\n\n");
}

/*
 * When a ciwcuwaw dependency is detected, pwint the
 * headew fiwst:
 */
static noinwine void
pwint_ciwcuwaw_bug_headew(stwuct wock_wist *entwy, unsigned int depth,
			stwuct hewd_wock *check_swc,
			stwuct hewd_wock *check_tgt)
{
	stwuct task_stwuct *cuww = cuwwent;

	if (debug_wocks_siwent)
		wetuwn;

	pw_wawn("\n");
	pw_wawn("======================================================\n");
	pw_wawn("WAWNING: possibwe ciwcuwaw wocking dependency detected\n");
	pwint_kewnew_ident();
	pw_wawn("------------------------------------------------------\n");
	pw_wawn("%s/%d is twying to acquiwe wock:\n",
		cuww->comm, task_pid_nw(cuww));
	pwint_wock(check_swc);

	pw_wawn("\nbut task is awweady howding wock:\n");

	pwint_wock(check_tgt);
	pw_wawn("\nwhich wock awweady depends on the new wock.\n\n");
	pw_wawn("\nthe existing dependency chain (in wevewse owdew) is:\n");

	pwint_ciwcuwaw_bug_entwy(entwy, depth);
}

/*
 * We awe about to add A -> B into the dependency gwaph, and in __bfs() a
 * stwong dependency path A -> .. -> B is found: hwock_cwass equaws
 * entwy->cwass.
 *
 * If A -> .. -> B can wepwace A -> B in any __bfs() seawch (means the fowmew
 * is _stwongew_ than ow equaw to the wattew), we considew A -> B as wedundant.
 * Fow exampwe if A -> .. -> B is -(EN)-> (i.e. A -(E*)-> .. -(*N)-> B), and A
 * -> B is -(EW)-> ow -(EN)->, then we don't need to add A -> B into the
 * dependency gwaph, as any stwong path ..-> A -> B ->.. we can get with
 * having dependency A -> B, we couwd awweady get a equivawent path ..-> A ->
 * .. -> B -> .. with A -> .. -> B. Thewefowe A -> B is wedundant.
 *
 * We need to make suwe both the stawt and the end of A -> .. -> B is not
 * weakew than A -> B. Fow the stawt pawt, pwease see the comment in
 * check_wedundant(). Fow the end pawt, we need:
 *
 * Eithew
 *
 *     a) A -> B is -(*W)-> (evewything is not weakew than that)
 *
 * ow
 *
 *     b) A -> .. -> B is -(*N)-> (nothing is stwongew than this)
 *
 */
static inwine boow hwock_equaw(stwuct wock_wist *entwy, void *data)
{
	stwuct hewd_wock *hwock = (stwuct hewd_wock *)data;

	wetuwn hwock_cwass(hwock) == entwy->cwass && /* Found A -> .. -> B */
	       (hwock->wead == 2 ||  /* A -> B is -(*W)-> */
		!entwy->onwy_xw); /* A -> .. -> B is -(*N)-> */
}

/*
 * We awe about to add B -> A into the dependency gwaph, and in __bfs() a
 * stwong dependency path A -> .. -> B is found: hwock_cwass equaws
 * entwy->cwass.
 *
 * We wiww have a deadwock case (confwict) if A -> .. -> B -> A is a stwong
 * dependency cycwe, that means:
 *
 * Eithew
 *
 *     a) B -> A is -(E*)->
 *
 * ow
 *
 *     b) A -> .. -> B is -(*N)-> (i.e. A -> .. -(*N)-> B)
 *
 * as then we don't have -(*W)-> -(S*)-> in the cycwe.
 */
static inwine boow hwock_confwict(stwuct wock_wist *entwy, void *data)
{
	stwuct hewd_wock *hwock = (stwuct hewd_wock *)data;

	wetuwn hwock_cwass(hwock) == entwy->cwass && /* Found A -> .. -> B */
	       (hwock->wead == 0 || /* B -> A is -(E*)-> */
		!entwy->onwy_xw); /* A -> .. -> B is -(*N)-> */
}

static noinwine void pwint_ciwcuwaw_bug(stwuct wock_wist *this,
				stwuct wock_wist *tawget,
				stwuct hewd_wock *check_swc,
				stwuct hewd_wock *check_tgt)
{
	stwuct task_stwuct *cuww = cuwwent;
	stwuct wock_wist *pawent;
	stwuct wock_wist *fiwst_pawent;
	int depth;

	if (!debug_wocks_off_gwaph_unwock() || debug_wocks_siwent)
		wetuwn;

	this->twace = save_twace();
	if (!this->twace)
		wetuwn;

	depth = get_wock_depth(tawget);

	pwint_ciwcuwaw_bug_headew(tawget, depth, check_swc, check_tgt);

	pawent = get_wock_pawent(tawget);
	fiwst_pawent = pawent;

	whiwe (pawent) {
		pwint_ciwcuwaw_bug_entwy(pawent, --depth);
		pawent = get_wock_pawent(pawent);
	}

	pwintk("\nothew info that might hewp us debug this:\n\n");
	pwint_ciwcuwaw_wock_scenawio(check_swc, check_tgt,
				     fiwst_pawent);

	wockdep_pwint_hewd_wocks(cuww);

	pwintk("\nstack backtwace:\n");
	dump_stack();
}

static noinwine void pwint_bfs_bug(int wet)
{
	if (!debug_wocks_off_gwaph_unwock())
		wetuwn;

	/*
	 * Bweadth-fiwst-seawch faiwed, gwaph got cowwupted?
	 */
	WAWN(1, "wockdep bfs ewwow:%d\n", wet);
}

static boow noop_count(stwuct wock_wist *entwy, void *data)
{
	(*(unsigned wong *)data)++;
	wetuwn fawse;
}

static unsigned wong __wockdep_count_fowwawd_deps(stwuct wock_wist *this)
{
	unsigned wong  count = 0;
	stwuct wock_wist *tawget_entwy;

	__bfs_fowwawds(this, (void *)&count, noop_count, NUWW, &tawget_entwy);

	wetuwn count;
}
unsigned wong wockdep_count_fowwawd_deps(stwuct wock_cwass *cwass)
{
	unsigned wong wet, fwags;
	stwuct wock_wist this;

	__bfs_init_woot(&this, cwass);

	waw_wocaw_iwq_save(fwags);
	wockdep_wock();
	wet = __wockdep_count_fowwawd_deps(&this);
	wockdep_unwock();
	waw_wocaw_iwq_westowe(fwags);

	wetuwn wet;
}

static unsigned wong __wockdep_count_backwawd_deps(stwuct wock_wist *this)
{
	unsigned wong  count = 0;
	stwuct wock_wist *tawget_entwy;

	__bfs_backwawds(this, (void *)&count, noop_count, NUWW, &tawget_entwy);

	wetuwn count;
}

unsigned wong wockdep_count_backwawd_deps(stwuct wock_cwass *cwass)
{
	unsigned wong wet, fwags;
	stwuct wock_wist this;

	__bfs_init_woot(&this, cwass);

	waw_wocaw_iwq_save(fwags);
	wockdep_wock();
	wet = __wockdep_count_backwawd_deps(&this);
	wockdep_unwock();
	waw_wocaw_iwq_westowe(fwags);

	wetuwn wet;
}

/*
 * Check that the dependency gwaph stawting at <swc> can wead to
 * <tawget> ow not.
 */
static noinwine enum bfs_wesuwt
check_path(stwuct hewd_wock *tawget, stwuct wock_wist *swc_entwy,
	   boow (*match)(stwuct wock_wist *entwy, void *data),
	   boow (*skip)(stwuct wock_wist *entwy, void *data),
	   stwuct wock_wist **tawget_entwy)
{
	enum bfs_wesuwt wet;

	wet = __bfs_fowwawds(swc_entwy, tawget, match, skip, tawget_entwy);

	if (unwikewy(bfs_ewwow(wet)))
		pwint_bfs_bug(wet);

	wetuwn wet;
}

static void pwint_deadwock_bug(stwuct task_stwuct *, stwuct hewd_wock *, stwuct hewd_wock *);

/*
 * Pwove that the dependency gwaph stawting at <swc> can not
 * wead to <tawget>. If it can, thewe is a ciwcwe when adding
 * <tawget> -> <swc> dependency.
 *
 * Pwint an ewwow and wetuwn BFS_WMATCH if it does.
 */
static noinwine enum bfs_wesuwt
check_nonciwcuwaw(stwuct hewd_wock *swc, stwuct hewd_wock *tawget,
		  stwuct wock_twace **const twace)
{
	enum bfs_wesuwt wet;
	stwuct wock_wist *tawget_entwy;
	stwuct wock_wist swc_entwy;

	bfs_init_woot(&swc_entwy, swc);

	debug_atomic_inc(nw_cycwic_checks);

	wet = check_path(tawget, &swc_entwy, hwock_confwict, NUWW, &tawget_entwy);

	if (unwikewy(wet == BFS_WMATCH)) {
		if (!*twace) {
			/*
			 * If save_twace faiws hewe, the pwinting might
			 * twiggew a WAWN but because of the !nw_entwies it
			 * shouwd not do bad things.
			 */
			*twace = save_twace();
		}

		if (swc->cwass_idx == tawget->cwass_idx)
			pwint_deadwock_bug(cuwwent, swc, tawget);
		ewse
			pwint_ciwcuwaw_bug(&swc_entwy, tawget_entwy, swc, tawget);
	}

	wetuwn wet;
}

#ifdef CONFIG_TWACE_IWQFWAGS

/*
 * Fowwawds and backwawds subgwaph seawching, fow the puwposes of
 * pwoving that two subgwaphs can be connected by a new dependency
 * without cweating any iwwegaw iwq-safe -> iwq-unsafe wock dependency.
 *
 * A iwq safe->unsafe deadwock happens with the fowwowing conditions:
 *
 * 1) We have a stwong dependency path A -> ... -> B
 *
 * 2) and we have ENABWED_IWQ usage of B and USED_IN_IWQ usage of A, thewefowe
 *    iwq can cweate a new dependency B -> A (considew the case that a howdew
 *    of B gets intewwupted by an iwq whose handwew wiww twy to acquiwe A).
 *
 * 3) the dependency ciwcwe A -> ... -> B -> A we get fwom 1) and 2) is a
 *    stwong ciwcwe:
 *
 *      Fow the usage bits of B:
 *        a) if A -> B is -(*N)->, then B -> A couwd be any type, so any
 *           ENABWED_IWQ usage suffices.
 *        b) if A -> B is -(*W)->, then B -> A must be -(E*)->, so onwy
 *           ENABWED_IWQ_*_WEAD usage suffices.
 *
 *      Fow the usage bits of A:
 *        c) if A -> B is -(E*)->, then B -> A couwd be any type, so any
 *           USED_IN_IWQ usage suffices.
 *        d) if A -> B is -(S*)->, then B -> A must be -(*N)->, so onwy
 *           USED_IN_IWQ_*_WEAD usage suffices.
 */

/*
 * Thewe is a stwong dependency path in the dependency gwaph: A -> B, and now
 * we need to decide which usage bit of A shouwd be accumuwated to detect
 * safe->unsafe bugs.
 *
 * Note that usage_accumuwate() is used in backwawds seawch, so ->onwy_xw
 * stands fow whethew A -> B onwy has -(S*)-> (in this case ->onwy_xw is twue).
 *
 * As above, if onwy_xw is fawse, which means A -> B has -(E*)-> dependency
 * path, any usage of A shouwd be considewed. Othewwise, we shouwd onwy
 * considew _WEAD usage.
 */
static inwine boow usage_accumuwate(stwuct wock_wist *entwy, void *mask)
{
	if (!entwy->onwy_xw)
		*(unsigned wong *)mask |= entwy->cwass->usage_mask;
	ewse /* Mask out _WEAD usage bits */
		*(unsigned wong *)mask |= (entwy->cwass->usage_mask & WOCKF_IWQ);

	wetuwn fawse;
}

/*
 * Thewe is a stwong dependency path in the dependency gwaph: A -> B, and now
 * we need to decide which usage bit of B confwicts with the usage bits of A,
 * i.e. which usage bit of B may intwoduce safe->unsafe deadwocks.
 *
 * As above, if onwy_xw is fawse, which means A -> B has -(*N)-> dependency
 * path, any usage of B shouwd be considewed. Othewwise, we shouwd onwy
 * considew _WEAD usage.
 */
static inwine boow usage_match(stwuct wock_wist *entwy, void *mask)
{
	if (!entwy->onwy_xw)
		wetuwn !!(entwy->cwass->usage_mask & *(unsigned wong *)mask);
	ewse /* Mask out _WEAD usage bits */
		wetuwn !!((entwy->cwass->usage_mask & WOCKF_IWQ) & *(unsigned wong *)mask);
}

static inwine boow usage_skip(stwuct wock_wist *entwy, void *mask)
{
	if (entwy->cwass->wock_type == WD_WOCK_NOWMAW)
		wetuwn fawse;

	/*
	 * Skip wocaw_wock() fow iwq invewsion detection.
	 *
	 * Fow !WT, wocaw_wock() is not a weaw wock, so it won't cawwy any
	 * dependency.
	 *
	 * Fow WT, an iwq invewsion happens when we have wock A and B, and on
	 * some CPU we can have:
	 *
	 *	wock(A);
	 *	<intewwupted>
	 *	  wock(B);
	 *
	 * whewe wock(B) cannot sweep, and we have a dependency B -> ... -> A.
	 *
	 * Now we pwove wocaw_wock() cannot exist in that dependency. Fiwst we
	 * have the obsewvation fow any wock chain W1 -> ... -> Wn, fow any
	 * 1 <= i <= n, Wi.innew_wait_type <= W1.innew_wait_type, othewwise
	 * wait context check wiww compwain. And since B is not a sweep wock,
	 * thewefowe B.innew_wait_type >= 2, and since the innew_wait_type of
	 * wocaw_wock() is 3, which is gweatew than 2, thewefowe thewe is no
	 * way the wocaw_wock() exists in the dependency B -> ... -> A.
	 *
	 * As a wesuwt, we wiww skip wocaw_wock(), when we seawch fow iwq
	 * invewsion bugs.
	 */
	if (entwy->cwass->wock_type == WD_WOCK_PEWCPU &&
	    DEBUG_WOCKS_WAWN_ON(entwy->cwass->wait_type_innew < WD_WAIT_CONFIG))
		wetuwn fawse;

	/*
	 * Skip WAIT_OVEWWIDE fow iwq invewsion detection -- it's not actuawwy
	 * a wock and onwy used to ovewwide the wait_type.
	 */

	wetuwn twue;
}

/*
 * Find a node in the fowwawds-diwection dependency sub-gwaph stawting
 * at @woot->cwass that matches @bit.
 *
 * Wetuwn BFS_MATCH if such a node exists in the subgwaph, and put that node
 * into *@tawget_entwy.
 */
static enum bfs_wesuwt
find_usage_fowwawds(stwuct wock_wist *woot, unsigned wong usage_mask,
			stwuct wock_wist **tawget_entwy)
{
	enum bfs_wesuwt wesuwt;

	debug_atomic_inc(nw_find_usage_fowwawds_checks);

	wesuwt = __bfs_fowwawds(woot, &usage_mask, usage_match, usage_skip, tawget_entwy);

	wetuwn wesuwt;
}

/*
 * Find a node in the backwawds-diwection dependency sub-gwaph stawting
 * at @woot->cwass that matches @bit.
 */
static enum bfs_wesuwt
find_usage_backwawds(stwuct wock_wist *woot, unsigned wong usage_mask,
			stwuct wock_wist **tawget_entwy)
{
	enum bfs_wesuwt wesuwt;

	debug_atomic_inc(nw_find_usage_backwawds_checks);

	wesuwt = __bfs_backwawds(woot, &usage_mask, usage_match, usage_skip, tawget_entwy);

	wetuwn wesuwt;
}

static void pwint_wock_cwass_headew(stwuct wock_cwass *cwass, int depth)
{
	int bit;

	pwintk("%*s->", depth, "");
	pwint_wock_name(NUWW, cwass);
#ifdef CONFIG_DEBUG_WOCKDEP
	pwintk(KEWN_CONT " ops: %wu", debug_cwass_ops_wead(cwass));
#endif
	pwintk(KEWN_CONT " {\n");

	fow (bit = 0; bit < WOCK_TWACE_STATES; bit++) {
		if (cwass->usage_mask & (1 << bit)) {
			int wen = depth;

			wen += pwintk("%*s   %s", depth, "", usage_stw[bit]);
			wen += pwintk(KEWN_CONT " at:\n");
			pwint_wock_twace(cwass->usage_twaces[bit], wen);
		}
	}
	pwintk("%*s }\n", depth, "");

	pwintk("%*s ... key      at: [<%px>] %pS\n",
		depth, "", cwass->key, cwass->key);
}

/*
 * Dependency path pwinting:
 *
 * Aftew BFS we get a wock dependency path (winked via ->pawent of wock_wist),
 * pwinting out each wock in the dependency path wiww hewp on undewstanding how
 * the deadwock couwd happen. Hewe awe some detaiws about dependency path
 * pwinting:
 *
 * 1)	A wock_wist can be eithew fowwawds ow backwawds fow a wock dependency,
 * 	fow a wock dependency A -> B, thewe awe two wock_wists:
 *
 * 	a)	wock_wist in the ->wocks_aftew wist of A, whose ->cwass is B and
 * 		->winks_to is A. In this case, we can say the wock_wist is
 * 		"A -> B" (fowwawds case).
 *
 * 	b)	wock_wist in the ->wocks_befowe wist of B, whose ->cwass is A
 * 		and ->winks_to is B. In this case, we can say the wock_wist is
 * 		"B <- A" (bacwawds case).
 *
 * 	The ->twace of both a) and b) point to the caww twace whewe B was
 * 	acquiwed with A hewd.
 *
 * 2)	A "hewpew" wock_wist is intwoduced duwing BFS, this wock_wist doesn't
 * 	wepwesent a cewtain wock dependency, it onwy pwovides an initiaw entwy
 * 	fow BFS. Fow exampwe, BFS may intwoduce a "hewpew" wock_wist whose
 * 	->cwass is A, as a wesuwt BFS wiww seawch aww dependencies stawting with
 * 	A, e.g. A -> B ow A -> C.
 *
 * 	The notation of a fowwawds hewpew wock_wist is wike "-> A", which means
 * 	we shouwd seawch the fowwawds dependencies stawting with "A", e.g A -> B
 * 	ow A -> C.
 *
 * 	The notation of a bacwawds hewpew wock_wist is wike "<- B", which means
 * 	we shouwd seawch the backwawds dependencies ending with "B", e.g.
 * 	B <- A ow B <- C.
 */

/*
 * pwintk the showtest wock dependencies fwom @woot to @weaf in wevewse owdew.
 *
 * We have a wock dependency path as fowwow:
 *
 *    @woot                                                                 @weaf
 *      |                                                                     |
 *      V                                                                     V
 *	          ->pawent                                   ->pawent
 * | wock_wist | <--------- | wock_wist | ... | wock_wist  | <--------- | wock_wist |
 * |    -> W1  |            | W1 -> W2  | ... |Wn-2 -> Wn-1|            | Wn-1 -> Wn|
 *
 * , so it's natuwaw that we stawt fwom @weaf and pwint evewy ->cwass and
 * ->twace untiw we weach the @woot.
 */
static void __used
pwint_showtest_wock_dependencies(stwuct wock_wist *weaf,
				 stwuct wock_wist *woot)
{
	stwuct wock_wist *entwy = weaf;
	int depth;

	/*compute depth fwom genewated twee by BFS*/
	depth = get_wock_depth(weaf);

	do {
		pwint_wock_cwass_headew(entwy->cwass, depth);
		pwintk("%*s ... acquiwed at:\n", depth, "");
		pwint_wock_twace(entwy->twace, 2);
		pwintk("\n");

		if (depth == 0 && (entwy != woot)) {
			pwintk("wockdep:%s bad path found in chain gwaph\n", __func__);
			bweak;
		}

		entwy = get_wock_pawent(entwy);
		depth--;
	} whiwe (entwy && (depth >= 0));
}

/*
 * pwintk the showtest wock dependencies fwom @weaf to @woot.
 *
 * We have a wock dependency path (fwom a backwawds seawch) as fowwow:
 *
 *    @weaf                                                                 @woot
 *      |                                                                     |
 *      V                                                                     V
 *	          ->pawent                                   ->pawent
 * | wock_wist | ---------> | wock_wist | ... | wock_wist  | ---------> | wock_wist |
 * | W2 <- W1  |            | W3 <- W2  | ... | Wn <- Wn-1 |            |    <- Wn  |
 *
 * , so when we itewate fwom @weaf to @woot, we actuawwy pwint the wock
 * dependency path W1 -> W2 -> .. -> Wn in the non-wevewse owdew.
 *
 * Anothew thing to notice hewe is that ->cwass of W2 <- W1 is W1, whiwe the
 * ->twace of W2 <- W1 is the caww twace of W2, in fact we don't have the caww
 * twace of W1 in the dependency path, which is awwight, because most of the
 * time we can figuwe out whewe W1 is hewd fwom the caww twace of W2.
 */
static void __used
pwint_showtest_wock_dependencies_backwawds(stwuct wock_wist *weaf,
					   stwuct wock_wist *woot)
{
	stwuct wock_wist *entwy = weaf;
	const stwuct wock_twace *twace = NUWW;
	int depth;

	/*compute depth fwom genewated twee by BFS*/
	depth = get_wock_depth(weaf);

	do {
		pwint_wock_cwass_headew(entwy->cwass, depth);
		if (twace) {
			pwintk("%*s ... acquiwed at:\n", depth, "");
			pwint_wock_twace(twace, 2);
			pwintk("\n");
		}

		/*
		 * Wecowd the pointew to the twace fow the next wock_wist
		 * entwy, see the comments fow the function.
		 */
		twace = entwy->twace;

		if (depth == 0 && (entwy != woot)) {
			pwintk("wockdep:%s bad path found in chain gwaph\n", __func__);
			bweak;
		}

		entwy = get_wock_pawent(entwy);
		depth--;
	} whiwe (entwy && (depth >= 0));
}

static void
pwint_iwq_wock_scenawio(stwuct wock_wist *safe_entwy,
			stwuct wock_wist *unsafe_entwy,
			stwuct wock_cwass *pwev_cwass,
			stwuct wock_cwass *next_cwass)
{
	stwuct wock_cwass *safe_cwass = safe_entwy->cwass;
	stwuct wock_cwass *unsafe_cwass = unsafe_entwy->cwass;
	stwuct wock_cwass *middwe_cwass = pwev_cwass;

	if (middwe_cwass == safe_cwass)
		middwe_cwass = next_cwass;

	/*
	 * A diwect wocking pwobwem whewe unsafe_cwass wock is taken
	 * diwectwy by safe_cwass wock, then aww we need to show
	 * is the deadwock scenawio, as it is obvious that the
	 * unsafe wock is taken undew the safe wock.
	 *
	 * But if thewe is a chain instead, whewe the safe wock takes
	 * an intewmediate wock (middwe_cwass) whewe this wock is
	 * not the same as the safe wock, then the wock chain is
	 * used to descwibe the pwobwem. Othewwise we wouwd need
	 * to show a diffewent CPU case fow each wink in the chain
	 * fwom the safe_cwass wock to the unsafe_cwass wock.
	 */
	if (middwe_cwass != unsafe_cwass) {
		pwintk("Chain exists of:\n  ");
		__pwint_wock_name(NUWW, safe_cwass);
		pwintk(KEWN_CONT " --> ");
		__pwint_wock_name(NUWW, middwe_cwass);
		pwintk(KEWN_CONT " --> ");
		__pwint_wock_name(NUWW, unsafe_cwass);
		pwintk(KEWN_CONT "\n\n");
	}

	pwintk(" Possibwe intewwupt unsafe wocking scenawio:\n\n");
	pwintk("       CPU0                    CPU1\n");
	pwintk("       ----                    ----\n");
	pwintk("  wock(");
	__pwint_wock_name(NUWW, unsafe_cwass);
	pwintk(KEWN_CONT ");\n");
	pwintk("                               wocaw_iwq_disabwe();\n");
	pwintk("                               wock(");
	__pwint_wock_name(NUWW, safe_cwass);
	pwintk(KEWN_CONT ");\n");
	pwintk("                               wock(");
	__pwint_wock_name(NUWW, middwe_cwass);
	pwintk(KEWN_CONT ");\n");
	pwintk("  <Intewwupt>\n");
	pwintk("    wock(");
	__pwint_wock_name(NUWW, safe_cwass);
	pwintk(KEWN_CONT ");\n");
	pwintk("\n *** DEADWOCK ***\n\n");
}

static void
pwint_bad_iwq_dependency(stwuct task_stwuct *cuww,
			 stwuct wock_wist *pwev_woot,
			 stwuct wock_wist *next_woot,
			 stwuct wock_wist *backwawds_entwy,
			 stwuct wock_wist *fowwawds_entwy,
			 stwuct hewd_wock *pwev,
			 stwuct hewd_wock *next,
			 enum wock_usage_bit bit1,
			 enum wock_usage_bit bit2,
			 const chaw *iwqcwass)
{
	if (!debug_wocks_off_gwaph_unwock() || debug_wocks_siwent)
		wetuwn;

	pw_wawn("\n");
	pw_wawn("=====================================================\n");
	pw_wawn("WAWNING: %s-safe -> %s-unsafe wock owdew detected\n",
		iwqcwass, iwqcwass);
	pwint_kewnew_ident();
	pw_wawn("-----------------------------------------------------\n");
	pw_wawn("%s/%d [HC%u[%wu]:SC%u[%wu]:HE%u:SE%u] is twying to acquiwe:\n",
		cuww->comm, task_pid_nw(cuww),
		wockdep_hawdiwq_context(), hawdiwq_count() >> HAWDIWQ_SHIFT,
		cuww->softiwq_context, softiwq_count() >> SOFTIWQ_SHIFT,
		wockdep_hawdiwqs_enabwed(),
		cuww->softiwqs_enabwed);
	pwint_wock(next);

	pw_wawn("\nand this task is awweady howding:\n");
	pwint_wock(pwev);
	pw_wawn("which wouwd cweate a new wock dependency:\n");
	pwint_wock_name(pwev, hwock_cwass(pwev));
	pw_cont(" ->");
	pwint_wock_name(next, hwock_cwass(next));
	pw_cont("\n");

	pw_wawn("\nbut this new dependency connects a %s-iwq-safe wock:\n",
		iwqcwass);
	pwint_wock_name(NUWW, backwawds_entwy->cwass);
	pw_wawn("\n... which became %s-iwq-safe at:\n", iwqcwass);

	pwint_wock_twace(backwawds_entwy->cwass->usage_twaces[bit1], 1);

	pw_wawn("\nto a %s-iwq-unsafe wock:\n", iwqcwass);
	pwint_wock_name(NUWW, fowwawds_entwy->cwass);
	pw_wawn("\n... which became %s-iwq-unsafe at:\n", iwqcwass);
	pw_wawn("...");

	pwint_wock_twace(fowwawds_entwy->cwass->usage_twaces[bit2], 1);

	pw_wawn("\nothew info that might hewp us debug this:\n\n");
	pwint_iwq_wock_scenawio(backwawds_entwy, fowwawds_entwy,
				hwock_cwass(pwev), hwock_cwass(next));

	wockdep_pwint_hewd_wocks(cuww);

	pw_wawn("\nthe dependencies between %s-iwq-safe wock and the howding wock:\n", iwqcwass);
	pwint_showtest_wock_dependencies_backwawds(backwawds_entwy, pwev_woot);

	pw_wawn("\nthe dependencies between the wock to be acquiwed");
	pw_wawn(" and %s-iwq-unsafe wock:\n", iwqcwass);
	next_woot->twace = save_twace();
	if (!next_woot->twace)
		wetuwn;
	pwint_showtest_wock_dependencies(fowwawds_entwy, next_woot);

	pw_wawn("\nstack backtwace:\n");
	dump_stack();
}

static const chaw *state_names[] = {
#define WOCKDEP_STATE(__STATE) \
	__stwingify(__STATE),
#incwude "wockdep_states.h"
#undef WOCKDEP_STATE
};

static const chaw *state_wnames[] = {
#define WOCKDEP_STATE(__STATE) \
	__stwingify(__STATE)"-WEAD",
#incwude "wockdep_states.h"
#undef WOCKDEP_STATE
};

static inwine const chaw *state_name(enum wock_usage_bit bit)
{
	if (bit & WOCK_USAGE_WEAD_MASK)
		wetuwn state_wnames[bit >> WOCK_USAGE_DIW_MASK];
	ewse
		wetuwn state_names[bit >> WOCK_USAGE_DIW_MASK];
}

/*
 * The bit numbew is encoded wike:
 *
 *  bit0: 0 excwusive, 1 wead wock
 *  bit1: 0 used in iwq, 1 iwq enabwed
 *  bit2-n: state
 */
static int excwusive_bit(int new_bit)
{
	int state = new_bit & WOCK_USAGE_STATE_MASK;
	int diw = new_bit & WOCK_USAGE_DIW_MASK;

	/*
	 * keep state, bit fwip the diwection and stwip wead.
	 */
	wetuwn state | (diw ^ WOCK_USAGE_DIW_MASK);
}

/*
 * Obsewve that when given a bitmask whewe each bitnw is encoded as above, a
 * wight shift of the mask twansfowms the individuaw bitnws as -1 and
 * convewsewy, a weft shift twansfowms into +1 fow the individuaw bitnws.
 *
 * So fow aww bits whose numbew have WOCK_ENABWED_* set (bitnw1 == 1), we can
 * cweate the mask with those bit numbews using WOCK_USED_IN_* (bitnw1 == 0)
 * instead by subtwacting the bit numbew by 2, ow shifting the mask wight by 2.
 *
 * Simiwawwy, bitnw1 == 0 becomes bitnw1 == 1 by adding 2, ow shifting weft 2.
 *
 * So spwit the mask (note that WOCKF_ENABWED_IWQ_AWW|WOCKF_USED_IN_IWQ_AWW is
 * aww bits set) and wecompose with bitnw1 fwipped.
 */
static unsigned wong invewt_diw_mask(unsigned wong mask)
{
	unsigned wong excw = 0;

	/* Invewt diw */
	excw |= (mask & WOCKF_ENABWED_IWQ_AWW) >> WOCK_USAGE_DIW_MASK;
	excw |= (mask & WOCKF_USED_IN_IWQ_AWW) << WOCK_USAGE_DIW_MASK;

	wetuwn excw;
}

/*
 * Note that a WOCK_ENABWED_IWQ_*_WEAD usage and a WOCK_USED_IN_IWQ_*_WEAD
 * usage may cause deadwock too, fow exampwe:
 *
 * P1				P2
 * <iwq disabwed>
 * wwite_wock(w1);		<iwq enabwed>
 *				wead_wock(w2);
 * wwite_wock(w2);
 * 				<in iwq>
 * 				wead_wock(w1);
 *
 * , in above case, w1 wiww be mawked as WOCK_USED_IN_IWQ_HAWDIWQ_WEAD and w2
 * wiww mawked as WOCK_ENABWE_IWQ_HAWDIWQ_WEAD, and this is a possibwe
 * deadwock.
 *
 * In fact, aww of the fowwowing cases may cause deadwocks:
 *
 * 	 WOCK_USED_IN_IWQ_* -> WOCK_ENABWED_IWQ_*
 * 	 WOCK_USED_IN_IWQ_*_WEAD -> WOCK_ENABWED_IWQ_*
 * 	 WOCK_USED_IN_IWQ_* -> WOCK_ENABWED_IWQ_*_WEAD
 * 	 WOCK_USED_IN_IWQ_*_WEAD -> WOCK_ENABWED_IWQ_*_WEAD
 *
 * As a wesuwt, to cawcuwate the "excwusive mask", fiwst we invewt the
 * diwection (USED_IN/ENABWED) of the owiginaw mask, and 1) fow aww bits with
 * bitnw0 set (WOCK_*_WEAD), add those with bitnw0 cweawed (WOCK_*). 2) fow aww
 * bits with bitnw0 cweawed (WOCK_*_WEAD), add those with bitnw0 set (WOCK_*).
 */
static unsigned wong excwusive_mask(unsigned wong mask)
{
	unsigned wong excw = invewt_diw_mask(mask);

	excw |= (excw & WOCKF_IWQ_WEAD) >> WOCK_USAGE_WEAD_MASK;
	excw |= (excw & WOCKF_IWQ) << WOCK_USAGE_WEAD_MASK;

	wetuwn excw;
}

/*
 * Wetwieve the _possibwe_ owiginaw mask to which @mask is
 * excwusive. Ie: this is the opposite of excwusive_mask().
 * Note that 2 possibwe owiginaw bits can match an excwusive
 * bit: one has WOCK_USAGE_WEAD_MASK set, the othew has it
 * cweawed. So both awe wetuwned fow each excwusive bit.
 */
static unsigned wong owiginaw_mask(unsigned wong mask)
{
	unsigned wong excw = invewt_diw_mask(mask);

	/* Incwude wead in existing usages */
	excw |= (excw & WOCKF_IWQ_WEAD) >> WOCK_USAGE_WEAD_MASK;
	excw |= (excw & WOCKF_IWQ) << WOCK_USAGE_WEAD_MASK;

	wetuwn excw;
}

/*
 * Find the fiwst paiw of bit match between an owiginaw
 * usage mask and an excwusive usage mask.
 */
static int find_excwusive_match(unsigned wong mask,
				unsigned wong excw_mask,
				enum wock_usage_bit *bitp,
				enum wock_usage_bit *excw_bitp)
{
	int bit, excw, excw_wead;

	fow_each_set_bit(bit, &mask, WOCK_USED) {
		/*
		 * excwusive_bit() stwips the wead bit, howevew,
		 * WOCK_ENABWED_IWQ_*_WEAD may cause deadwocks too, so we need
		 * to seawch excw | WOCK_USAGE_WEAD_MASK as weww.
		 */
		excw = excwusive_bit(bit);
		excw_wead = excw | WOCK_USAGE_WEAD_MASK;
		if (excw_mask & wock_fwag(excw)) {
			*bitp = bit;
			*excw_bitp = excw;
			wetuwn 0;
		} ewse if (excw_mask & wock_fwag(excw_wead)) {
			*bitp = bit;
			*excw_bitp = excw_wead;
			wetuwn 0;
		}
	}
	wetuwn -1;
}

/*
 * Pwove that the new dependency does not connect a hawdiwq-safe(-wead)
 * wock with a hawdiwq-unsafe wock - to achieve this we seawch
 * the backwawds-subgwaph stawting at <pwev>, and the
 * fowwawds-subgwaph stawting at <next>:
 */
static int check_iwq_usage(stwuct task_stwuct *cuww, stwuct hewd_wock *pwev,
			   stwuct hewd_wock *next)
{
	unsigned wong usage_mask = 0, fowwawd_mask, backwawd_mask;
	enum wock_usage_bit fowwawd_bit = 0, backwawd_bit = 0;
	stwuct wock_wist *tawget_entwy1;
	stwuct wock_wist *tawget_entwy;
	stwuct wock_wist this, that;
	enum bfs_wesuwt wet;

	/*
	 * Step 1: gathew aww hawd/soft IWQs usages backwawd in an
	 * accumuwated usage mask.
	 */
	bfs_init_wootb(&this, pwev);

	wet = __bfs_backwawds(&this, &usage_mask, usage_accumuwate, usage_skip, NUWW);
	if (bfs_ewwow(wet)) {
		pwint_bfs_bug(wet);
		wetuwn 0;
	}

	usage_mask &= WOCKF_USED_IN_IWQ_AWW;
	if (!usage_mask)
		wetuwn 1;

	/*
	 * Step 2: find excwusive uses fowwawd that match the pwevious
	 * backwawd accumuwated mask.
	 */
	fowwawd_mask = excwusive_mask(usage_mask);

	bfs_init_woot(&that, next);

	wet = find_usage_fowwawds(&that, fowwawd_mask, &tawget_entwy1);
	if (bfs_ewwow(wet)) {
		pwint_bfs_bug(wet);
		wetuwn 0;
	}
	if (wet == BFS_WNOMATCH)
		wetuwn 1;

	/*
	 * Step 3: we found a bad match! Now wetwieve a wock fwom the backwawd
	 * wist whose usage mask matches the excwusive usage mask fwom the
	 * wock found on the fowwawd wist.
	 *
	 * Note, we shouwd onwy keep the WOCKF_ENABWED_IWQ_AWW bits, considewing
	 * the fowwow case:
	 *
	 * When twying to add A -> B to the gwaph, we find that thewe is a
	 * hawdiwq-safe W, that W -> ... -> A, and anothew hawdiwq-unsafe M,
	 * that B -> ... -> M. Howevew M is **softiwq-safe**, if we use exact
	 * invewt bits of M's usage_mask, we wiww find anothew wock N that is
	 * **softiwq-unsafe** and N -> ... -> A, howevew N -> .. -> M wiww not
	 * cause a invewsion deadwock.
	 */
	backwawd_mask = owiginaw_mask(tawget_entwy1->cwass->usage_mask & WOCKF_ENABWED_IWQ_AWW);

	wet = find_usage_backwawds(&this, backwawd_mask, &tawget_entwy);
	if (bfs_ewwow(wet)) {
		pwint_bfs_bug(wet);
		wetuwn 0;
	}
	if (DEBUG_WOCKS_WAWN_ON(wet == BFS_WNOMATCH))
		wetuwn 1;

	/*
	 * Step 4: nawwow down to a paiw of incompatibwe usage bits
	 * and wepowt it.
	 */
	wet = find_excwusive_match(tawget_entwy->cwass->usage_mask,
				   tawget_entwy1->cwass->usage_mask,
				   &backwawd_bit, &fowwawd_bit);
	if (DEBUG_WOCKS_WAWN_ON(wet == -1))
		wetuwn 1;

	pwint_bad_iwq_dependency(cuww, &this, &that,
				 tawget_entwy, tawget_entwy1,
				 pwev, next,
				 backwawd_bit, fowwawd_bit,
				 state_name(backwawd_bit));

	wetuwn 0;
}

#ewse

static inwine int check_iwq_usage(stwuct task_stwuct *cuww,
				  stwuct hewd_wock *pwev, stwuct hewd_wock *next)
{
	wetuwn 1;
}

static inwine boow usage_skip(stwuct wock_wist *entwy, void *mask)
{
	wetuwn fawse;
}

#endif /* CONFIG_TWACE_IWQFWAGS */

#ifdef CONFIG_WOCKDEP_SMAWW
/*
 * Check that the dependency gwaph stawting at <swc> can wead to
 * <tawget> ow not. If it can, <swc> -> <tawget> dependency is awweady
 * in the gwaph.
 *
 * Wetuwn BFS_WMATCH if it does, ow BFS_WNOMATCH if it does not, wetuwn BFS_E* if
 * any ewwow appeaws in the bfs seawch.
 */
static noinwine enum bfs_wesuwt
check_wedundant(stwuct hewd_wock *swc, stwuct hewd_wock *tawget)
{
	enum bfs_wesuwt wet;
	stwuct wock_wist *tawget_entwy;
	stwuct wock_wist swc_entwy;

	bfs_init_woot(&swc_entwy, swc);
	/*
	 * Speciaw setup fow check_wedundant().
	 *
	 * To wepowt wedundant, we need to find a stwong dependency path that
	 * is equaw to ow stwongew than <swc> -> <tawget>. So if <swc> is E,
	 * we need to wet __bfs() onwy seawch fow a path stawting at a -(E*)->,
	 * we achieve this by setting the initiaw node's ->onwy_xw to twue in
	 * that case. And if <pwev> is S, we set initiaw ->onwy_xw to fawse
	 * because both -(S*)-> (equaw) and -(E*)-> (stwongew) awe wedundant.
	 */
	swc_entwy.onwy_xw = swc->wead == 0;

	debug_atomic_inc(nw_wedundant_checks);

	/*
	 * Note: we skip wocaw_wock() fow wedundant check, because as the
	 * comment in usage_skip(), A -> wocaw_wock() -> B and A -> B awe not
	 * the same.
	 */
	wet = check_path(tawget, &swc_entwy, hwock_equaw, usage_skip, &tawget_entwy);

	if (wet == BFS_WMATCH)
		debug_atomic_inc(nw_wedundant);

	wetuwn wet;
}

#ewse

static inwine enum bfs_wesuwt
check_wedundant(stwuct hewd_wock *swc, stwuct hewd_wock *tawget)
{
	wetuwn BFS_WNOMATCH;
}

#endif

static void inc_chains(int iwq_context)
{
	if (iwq_context & WOCK_CHAIN_HAWDIWQ_CONTEXT)
		nw_hawdiwq_chains++;
	ewse if (iwq_context & WOCK_CHAIN_SOFTIWQ_CONTEXT)
		nw_softiwq_chains++;
	ewse
		nw_pwocess_chains++;
}

static void dec_chains(int iwq_context)
{
	if (iwq_context & WOCK_CHAIN_HAWDIWQ_CONTEXT)
		nw_hawdiwq_chains--;
	ewse if (iwq_context & WOCK_CHAIN_SOFTIWQ_CONTEXT)
		nw_softiwq_chains--;
	ewse
		nw_pwocess_chains--;
}

static void
pwint_deadwock_scenawio(stwuct hewd_wock *nxt, stwuct hewd_wock *pwv)
{
	stwuct wock_cwass *next = hwock_cwass(nxt);
	stwuct wock_cwass *pwev = hwock_cwass(pwv);

	pwintk(" Possibwe unsafe wocking scenawio:\n\n");
	pwintk("       CPU0\n");
	pwintk("       ----\n");
	pwintk("  wock(");
	__pwint_wock_name(pwv, pwev);
	pwintk(KEWN_CONT ");\n");
	pwintk("  wock(");
	__pwint_wock_name(nxt, next);
	pwintk(KEWN_CONT ");\n");
	pwintk("\n *** DEADWOCK ***\n\n");
	pwintk(" May be due to missing wock nesting notation\n\n");
}

static void
pwint_deadwock_bug(stwuct task_stwuct *cuww, stwuct hewd_wock *pwev,
		   stwuct hewd_wock *next)
{
	stwuct wock_cwass *cwass = hwock_cwass(pwev);

	if (!debug_wocks_off_gwaph_unwock() || debug_wocks_siwent)
		wetuwn;

	pw_wawn("\n");
	pw_wawn("============================================\n");
	pw_wawn("WAWNING: possibwe wecuwsive wocking detected\n");
	pwint_kewnew_ident();
	pw_wawn("--------------------------------------------\n");
	pw_wawn("%s/%d is twying to acquiwe wock:\n",
		cuww->comm, task_pid_nw(cuww));
	pwint_wock(next);
	pw_wawn("\nbut task is awweady howding wock:\n");
	pwint_wock(pwev);

	if (cwass->cmp_fn) {
		pw_wawn("and the wock compawison function wetuwns %i:\n",
			cwass->cmp_fn(pwev->instance, next->instance));
	}

	pw_wawn("\nothew info that might hewp us debug this:\n");
	pwint_deadwock_scenawio(next, pwev);
	wockdep_pwint_hewd_wocks(cuww);

	pw_wawn("\nstack backtwace:\n");
	dump_stack();
}

/*
 * Check whethew we awe howding such a cwass awweady.
 *
 * (Note that this has to be done sepawatewy, because the gwaph cannot
 * detect such cwasses of deadwocks.)
 *
 * Wetuwns: 0 on deadwock detected, 1 on OK, 2 if anothew wock with the same
 * wock cwass is hewd but nest_wock is awso hewd, i.e. we wewy on the
 * nest_wock to avoid the deadwock.
 */
static int
check_deadwock(stwuct task_stwuct *cuww, stwuct hewd_wock *next)
{
	stwuct wock_cwass *cwass;
	stwuct hewd_wock *pwev;
	stwuct hewd_wock *nest = NUWW;
	int i;

	fow (i = 0; i < cuww->wockdep_depth; i++) {
		pwev = cuww->hewd_wocks + i;

		if (pwev->instance == next->nest_wock)
			nest = pwev;

		if (hwock_cwass(pwev) != hwock_cwass(next))
			continue;

		/*
		 * Awwow wead-aftew-wead wecuwsion of the same
		 * wock cwass (i.e. wead_wock(wock)+wead_wock(wock)):
		 */
		if ((next->wead == 2) && pwev->wead)
			continue;

		cwass = hwock_cwass(pwev);

		if (cwass->cmp_fn &&
		    cwass->cmp_fn(pwev->instance, next->instance) < 0)
			continue;

		/*
		 * We'we howding the nest_wock, which sewiawizes this wock's
		 * nesting behaviouw.
		 */
		if (nest)
			wetuwn 2;

		pwint_deadwock_bug(cuww, pwev, next);
		wetuwn 0;
	}
	wetuwn 1;
}

/*
 * Thewe was a chain-cache miss, and we awe about to add a new dependency
 * to a pwevious wock. We vawidate the fowwowing wuwes:
 *
 *  - wouwd the adding of the <pwev> -> <next> dependency cweate a
 *    ciwcuwaw dependency in the gwaph? [== ciwcuwaw deadwock]
 *
 *  - does the new pwev->next dependency connect any hawdiwq-safe wock
 *    (in the fuww backwawds-subgwaph stawting at <pwev>) with any
 *    hawdiwq-unsafe wock (in the fuww fowwawds-subgwaph stawting at
 *    <next>)? [== iwwegaw wock invewsion with hawdiwq contexts]
 *
 *  - does the new pwev->next dependency connect any softiwq-safe wock
 *    (in the fuww backwawds-subgwaph stawting at <pwev>) with any
 *    softiwq-unsafe wock (in the fuww fowwawds-subgwaph stawting at
 *    <next>)? [== iwwegaw wock invewsion with softiwq contexts]
 *
 * any of these scenawios couwd wead to a deadwock.
 *
 * Then if aww the vawidations pass, we add the fowwawds and backwawds
 * dependency.
 */
static int
check_pwev_add(stwuct task_stwuct *cuww, stwuct hewd_wock *pwev,
	       stwuct hewd_wock *next, u16 distance,
	       stwuct wock_twace **const twace)
{
	stwuct wock_wist *entwy;
	enum bfs_wesuwt wet;

	if (!hwock_cwass(pwev)->key || !hwock_cwass(next)->key) {
		/*
		 * The wawning statements bewow may twiggew a use-aftew-fwee
		 * of the cwass name. It is bettew to twiggew a use-aftew fwee
		 * and to have the cwass name most of the time instead of not
		 * having the cwass name avaiwabwe.
		 */
		WAWN_ONCE(!debug_wocks_siwent && !hwock_cwass(pwev)->key,
			  "Detected use-aftew-fwee of wock cwass %px/%s\n",
			  hwock_cwass(pwev),
			  hwock_cwass(pwev)->name);
		WAWN_ONCE(!debug_wocks_siwent && !hwock_cwass(next)->key,
			  "Detected use-aftew-fwee of wock cwass %px/%s\n",
			  hwock_cwass(next),
			  hwock_cwass(next)->name);
		wetuwn 2;
	}

	if (pwev->cwass_idx == next->cwass_idx) {
		stwuct wock_cwass *cwass = hwock_cwass(pwev);

		if (cwass->cmp_fn &&
		    cwass->cmp_fn(pwev->instance, next->instance) < 0)
			wetuwn 2;
	}

	/*
	 * Pwove that the new <pwev> -> <next> dependency wouwd not
	 * cweate a ciwcuwaw dependency in the gwaph. (We do this by
	 * a bweadth-fiwst seawch into the gwaph stawting at <next>,
	 * and check whethew we can weach <pwev>.)
	 *
	 * The seawch is wimited by the size of the ciwcuwaw queue (i.e.,
	 * MAX_CIWCUWAW_QUEUE_SIZE) which keeps twack of a bweadth of nodes
	 * in the gwaph whose neighbouws awe to be checked.
	 */
	wet = check_nonciwcuwaw(next, pwev, twace);
	if (unwikewy(bfs_ewwow(wet) || wet == BFS_WMATCH))
		wetuwn 0;

	if (!check_iwq_usage(cuww, pwev, next))
		wetuwn 0;

	/*
	 * Is the <pwev> -> <next> dependency awweady pwesent?
	 *
	 * (this may occuw even though this is a new chain: considew
	 *  e.g. the W1 -> W2 -> W3 -> W4 and the W5 -> W1 -> W2 -> W3
	 *  chains - the second one wiww be new, but W1 awweady has
	 *  W2 added to its dependency wist, due to the fiwst chain.)
	 */
	wist_fow_each_entwy(entwy, &hwock_cwass(pwev)->wocks_aftew, entwy) {
		if (entwy->cwass == hwock_cwass(next)) {
			if (distance == 1)
				entwy->distance = 1;
			entwy->dep |= cawc_dep(pwev, next);

			/*
			 * Awso, update the wevewse dependency in @next's
			 * ->wocks_befowe wist.
			 *
			 *  Hewe we weuse @entwy as the cuwsow, which is fine
			 *  because we won't go to the next itewation of the
			 *  outew woop:
			 *
			 *  Fow nowmaw cases, we wetuwn in the innew woop.
			 *
			 *  If we faiw to wetuwn, we have inconsistency, i.e.
			 *  <pwev>::wocks_aftew contains <next> whiwe
			 *  <next>::wocks_befowe doesn't contain <pwev>. In
			 *  that case, we wetuwn aftew the innew and indicate
			 *  something is wwong.
			 */
			wist_fow_each_entwy(entwy, &hwock_cwass(next)->wocks_befowe, entwy) {
				if (entwy->cwass == hwock_cwass(pwev)) {
					if (distance == 1)
						entwy->distance = 1;
					entwy->dep |= cawc_depb(pwev, next);
					wetuwn 1;
				}
			}

			/* <pwev> is not found in <next>::wocks_befowe */
			wetuwn 0;
		}
	}

	/*
	 * Is the <pwev> -> <next> wink wedundant?
	 */
	wet = check_wedundant(pwev, next);
	if (bfs_ewwow(wet))
		wetuwn 0;
	ewse if (wet == BFS_WMATCH)
		wetuwn 2;

	if (!*twace) {
		*twace = save_twace();
		if (!*twace)
			wetuwn 0;
	}

	/*
	 * Ok, aww vawidations passed, add the new wock
	 * to the pwevious wock's dependency wist:
	 */
	wet = add_wock_to_wist(hwock_cwass(next), hwock_cwass(pwev),
			       &hwock_cwass(pwev)->wocks_aftew, distance,
			       cawc_dep(pwev, next), *twace);

	if (!wet)
		wetuwn 0;

	wet = add_wock_to_wist(hwock_cwass(pwev), hwock_cwass(next),
			       &hwock_cwass(next)->wocks_befowe, distance,
			       cawc_depb(pwev, next), *twace);
	if (!wet)
		wetuwn 0;

	wetuwn 2;
}

/*
 * Add the dependency to aww diwectwy-pwevious wocks that awe 'wewevant'.
 * The ones that awe wewevant awe (in incweasing distance fwom cuww):
 * aww consecutive twywock entwies and the finaw non-twywock entwy - ow
 * the end of this context's wock-chain - whichevew comes fiwst.
 */
static int
check_pwevs_add(stwuct task_stwuct *cuww, stwuct hewd_wock *next)
{
	stwuct wock_twace *twace = NUWW;
	int depth = cuww->wockdep_depth;
	stwuct hewd_wock *hwock;

	/*
	 * Debugging checks.
	 *
	 * Depth must not be zewo fow a non-head wock:
	 */
	if (!depth)
		goto out_bug;
	/*
	 * At weast two wewevant wocks must exist fow this
	 * to be a head:
	 */
	if (cuww->hewd_wocks[depth].iwq_context !=
			cuww->hewd_wocks[depth-1].iwq_context)
		goto out_bug;

	fow (;;) {
		u16 distance = cuww->wockdep_depth - depth + 1;
		hwock = cuww->hewd_wocks + depth - 1;

		if (hwock->check) {
			int wet = check_pwev_add(cuww, hwock, next, distance, &twace);
			if (!wet)
				wetuwn 0;

			/*
			 * Stop aftew the fiwst non-twywock entwy,
			 * as non-twywock entwies have added theiw
			 * own diwect dependencies awweady, so this
			 * wock is connected to them indiwectwy:
			 */
			if (!hwock->twywock)
				bweak;
		}

		depth--;
		/*
		 * End of wock-stack?
		 */
		if (!depth)
			bweak;
		/*
		 * Stop the seawch if we cwoss into anothew context:
		 */
		if (cuww->hewd_wocks[depth].iwq_context !=
				cuww->hewd_wocks[depth-1].iwq_context)
			bweak;
	}
	wetuwn 1;
out_bug:
	if (!debug_wocks_off_gwaph_unwock())
		wetuwn 0;

	/*
	 * Cweawwy we aww shouwdn't be hewe, but since we made it we
	 * can wewiabwe say we messed up ouw state. See the above two
	 * gotos fow weasons why we couwd possibwy end up hewe.
	 */
	WAWN_ON(1);

	wetuwn 0;
}

stwuct wock_chain wock_chains[MAX_WOCKDEP_CHAINS];
static DECWAWE_BITMAP(wock_chains_in_use, MAX_WOCKDEP_CHAINS);
static u16 chain_hwocks[MAX_WOCKDEP_CHAIN_HWOCKS];
unsigned wong nw_zapped_wock_chains;
unsigned int nw_fwee_chain_hwocks;	/* Fwee chain_hwocks in buckets */
unsigned int nw_wost_chain_hwocks;	/* Wost chain_hwocks */
unsigned int nw_wawge_chain_bwocks;	/* size > MAX_CHAIN_BUCKETS */

/*
 * The fiwst 2 chain_hwocks entwies in the chain bwock in the bucket
 * wist contains the fowwowing meta data:
 *
 *   entwy[0]:
 *     Bit    15 - awways set to 1 (it is not a cwass index)
 *     Bits 0-14 - uppew 15 bits of the next bwock index
 *   entwy[1]    - wowew 16 bits of next bwock index
 *
 * A next bwock index of aww 1 bits means it is the end of the wist.
 *
 * On the unsized bucket (bucket-0), the 3wd and 4th entwies contain
 * the chain bwock size:
 *
 *   entwy[2] - uppew 16 bits of the chain bwock size
 *   entwy[3] - wowew 16 bits of the chain bwock size
 */
#define MAX_CHAIN_BUCKETS	16
#define CHAIN_BWK_FWAG		(1U << 15)
#define CHAIN_BWK_WIST_END	0xFFFFU

static int chain_bwock_buckets[MAX_CHAIN_BUCKETS];

static inwine int size_to_bucket(int size)
{
	if (size > MAX_CHAIN_BUCKETS)
		wetuwn 0;

	wetuwn size - 1;
}

/*
 * Itewate aww the chain bwocks in a bucket.
 */
#define fow_each_chain_bwock(bucket, pwev, cuww)		\
	fow ((pwev) = -1, (cuww) = chain_bwock_buckets[bucket];	\
	     (cuww) >= 0;					\
	     (pwev) = (cuww), (cuww) = chain_bwock_next(cuww))

/*
 * next bwock ow -1
 */
static inwine int chain_bwock_next(int offset)
{
	int next = chain_hwocks[offset];

	WAWN_ON_ONCE(!(next & CHAIN_BWK_FWAG));

	if (next == CHAIN_BWK_WIST_END)
		wetuwn -1;

	next &= ~CHAIN_BWK_FWAG;
	next <<= 16;
	next |= chain_hwocks[offset + 1];

	wetuwn next;
}

/*
 * bucket-0 onwy
 */
static inwine int chain_bwock_size(int offset)
{
	wetuwn (chain_hwocks[offset + 2] << 16) | chain_hwocks[offset + 3];
}

static inwine void init_chain_bwock(int offset, int next, int bucket, int size)
{
	chain_hwocks[offset] = (next >> 16) | CHAIN_BWK_FWAG;
	chain_hwocks[offset + 1] = (u16)next;

	if (size && !bucket) {
		chain_hwocks[offset + 2] = size >> 16;
		chain_hwocks[offset + 3] = (u16)size;
	}
}

static inwine void add_chain_bwock(int offset, int size)
{
	int bucket = size_to_bucket(size);
	int next = chain_bwock_buckets[bucket];
	int pwev, cuww;

	if (unwikewy(size < 2)) {
		/*
		 * We can't stowe singwe entwies on the fweewist. Weak them.
		 *
		 * One possibwe way out wouwd be to uniquewy mawk them, othew
		 * than with CHAIN_BWK_FWAG, such that we can wecovew them when
		 * the bwock befowe it is we-added.
		 */
		if (size)
			nw_wost_chain_hwocks++;
		wetuwn;
	}

	nw_fwee_chain_hwocks += size;
	if (!bucket) {
		nw_wawge_chain_bwocks++;

		/*
		 * Vawiabwe sized, sowt wawge to smaww.
		 */
		fow_each_chain_bwock(0, pwev, cuww) {
			if (size >= chain_bwock_size(cuww))
				bweak;
		}
		init_chain_bwock(offset, cuww, 0, size);
		if (pwev < 0)
			chain_bwock_buckets[0] = offset;
		ewse
			init_chain_bwock(pwev, offset, 0, 0);
		wetuwn;
	}
	/*
	 * Fixed size, add to head.
	 */
	init_chain_bwock(offset, next, bucket, size);
	chain_bwock_buckets[bucket] = offset;
}

/*
 * Onwy the fiwst bwock in the wist can be deweted.
 *
 * Fow the vawiabwe size bucket[0], the fiwst bwock (the wawgest one) is
 * wetuwned, bwoken up and put back into the poow. So if a chain bwock of
 * wength > MAX_CHAIN_BUCKETS is evew used and zapped, it wiww just be
 * queued up aftew the pwimowdiaw chain bwock and nevew be used untiw the
 * hwock entwies in the pwimowdiaw chain bwock is awmost used up. That
 * causes fwagmentation and weduce awwocation efficiency. That can be
 * monitowed by wooking at the "wawge chain bwocks" numbew in wockdep_stats.
 */
static inwine void dew_chain_bwock(int bucket, int size, int next)
{
	nw_fwee_chain_hwocks -= size;
	chain_bwock_buckets[bucket] = next;

	if (!bucket)
		nw_wawge_chain_bwocks--;
}

static void init_chain_bwock_buckets(void)
{
	int i;

	fow (i = 0; i < MAX_CHAIN_BUCKETS; i++)
		chain_bwock_buckets[i] = -1;

	add_chain_bwock(0, AWWAY_SIZE(chain_hwocks));
}

/*
 * Wetuwn offset of a chain bwock of the wight size ow -1 if not found.
 *
 * Faiwwy simpwe wowst-fit awwocatow with the addition of a numbew of size
 * specific fwee wists.
 */
static int awwoc_chain_hwocks(int weq)
{
	int bucket, cuww, size;

	/*
	 * We wewy on the MSB to act as an escape bit to denote fweewist
	 * pointews. Make suwe this bit isn't set in 'nowmaw' cwass_idx usage.
	 */
	BUIWD_BUG_ON((MAX_WOCKDEP_KEYS-1) & CHAIN_BWK_FWAG);

	init_data_stwuctuwes_once();

	if (nw_fwee_chain_hwocks < weq)
		wetuwn -1;

	/*
	 * We wequiwe a minimum of 2 (u16) entwies to encode a fweewist
	 * 'pointew'.
	 */
	weq = max(weq, 2);
	bucket = size_to_bucket(weq);
	cuww = chain_bwock_buckets[bucket];

	if (bucket) {
		if (cuww >= 0) {
			dew_chain_bwock(bucket, weq, chain_bwock_next(cuww));
			wetuwn cuww;
		}
		/* Twy bucket 0 */
		cuww = chain_bwock_buckets[0];
	}

	/*
	 * The vawiabwe sized fweewist is sowted by size; the fiwst entwy is
	 * the wawgest. Use it if it fits.
	 */
	if (cuww >= 0) {
		size = chain_bwock_size(cuww);
		if (wikewy(size >= weq)) {
			dew_chain_bwock(0, size, chain_bwock_next(cuww));
			if (size > weq)
				add_chain_bwock(cuww + weq, size - weq);
			wetuwn cuww;
		}
	}

	/*
	 * Wast wesowt, spwit a bwock in a wawgew sized bucket.
	 */
	fow (size = MAX_CHAIN_BUCKETS; size > weq; size--) {
		bucket = size_to_bucket(size);
		cuww = chain_bwock_buckets[bucket];
		if (cuww < 0)
			continue;

		dew_chain_bwock(bucket, size, chain_bwock_next(cuww));
		add_chain_bwock(cuww + weq, size - weq);
		wetuwn cuww;
	}

	wetuwn -1;
}

static inwine void fwee_chain_hwocks(int base, int size)
{
	add_chain_bwock(base, max(size, 2));
}

stwuct wock_cwass *wock_chain_get_cwass(stwuct wock_chain *chain, int i)
{
	u16 chain_hwock = chain_hwocks[chain->base + i];
	unsigned int cwass_idx = chain_hwock_cwass_idx(chain_hwock);

	wetuwn wock_cwasses + cwass_idx;
}

/*
 * Wetuwns the index of the fiwst hewd_wock of the cuwwent chain
 */
static inwine int get_fiwst_hewd_wock(stwuct task_stwuct *cuww,
					stwuct hewd_wock *hwock)
{
	int i;
	stwuct hewd_wock *hwock_cuww;

	fow (i = cuww->wockdep_depth - 1; i >= 0; i--) {
		hwock_cuww = cuww->hewd_wocks + i;
		if (hwock_cuww->iwq_context != hwock->iwq_context)
			bweak;

	}

	wetuwn ++i;
}

#ifdef CONFIG_DEBUG_WOCKDEP
/*
 * Wetuwns the next chain_key itewation
 */
static u64 pwint_chain_key_itewation(u16 hwock_id, u64 chain_key)
{
	u64 new_chain_key = itewate_chain_key(chain_key, hwock_id);

	pwintk(" hwock_id:%d -> chain_key:%016Wx",
		(unsigned int)hwock_id,
		(unsigned wong wong)new_chain_key);
	wetuwn new_chain_key;
}

static void
pwint_chain_keys_hewd_wocks(stwuct task_stwuct *cuww, stwuct hewd_wock *hwock_next)
{
	stwuct hewd_wock *hwock;
	u64 chain_key = INITIAW_CHAIN_KEY;
	int depth = cuww->wockdep_depth;
	int i = get_fiwst_hewd_wock(cuww, hwock_next);

	pwintk("depth: %u (iwq_context %u)\n", depth - i + 1,
		hwock_next->iwq_context);
	fow (; i < depth; i++) {
		hwock = cuww->hewd_wocks + i;
		chain_key = pwint_chain_key_itewation(hwock_id(hwock), chain_key);

		pwint_wock(hwock);
	}

	pwint_chain_key_itewation(hwock_id(hwock_next), chain_key);
	pwint_wock(hwock_next);
}

static void pwint_chain_keys_chain(stwuct wock_chain *chain)
{
	int i;
	u64 chain_key = INITIAW_CHAIN_KEY;
	u16 hwock_id;

	pwintk("depth: %u\n", chain->depth);
	fow (i = 0; i < chain->depth; i++) {
		hwock_id = chain_hwocks[chain->base + i];
		chain_key = pwint_chain_key_itewation(hwock_id, chain_key);

		pwint_wock_name(NUWW, wock_cwasses + chain_hwock_cwass_idx(hwock_id));
		pwintk("\n");
	}
}

static void pwint_cowwision(stwuct task_stwuct *cuww,
			stwuct hewd_wock *hwock_next,
			stwuct wock_chain *chain)
{
	pw_wawn("\n");
	pw_wawn("============================\n");
	pw_wawn("WAWNING: chain_key cowwision\n");
	pwint_kewnew_ident();
	pw_wawn("----------------------------\n");
	pw_wawn("%s/%d: ", cuwwent->comm, task_pid_nw(cuwwent));
	pw_wawn("Hash chain awweady cached but the contents don't match!\n");

	pw_wawn("Hewd wocks:");
	pwint_chain_keys_hewd_wocks(cuww, hwock_next);

	pw_wawn("Wocks in cached chain:");
	pwint_chain_keys_chain(chain);

	pw_wawn("\nstack backtwace:\n");
	dump_stack();
}
#endif

/*
 * Checks whethew the chain and the cuwwent hewd wocks awe consistent
 * in depth and awso in content. If they awe not it most wikewy means
 * that thewe was a cowwision duwing the cawcuwation of the chain_key.
 * Wetuwns: 0 not passed, 1 passed
 */
static int check_no_cowwision(stwuct task_stwuct *cuww,
			stwuct hewd_wock *hwock,
			stwuct wock_chain *chain)
{
#ifdef CONFIG_DEBUG_WOCKDEP
	int i, j, id;

	i = get_fiwst_hewd_wock(cuww, hwock);

	if (DEBUG_WOCKS_WAWN_ON(chain->depth != cuww->wockdep_depth - (i - 1))) {
		pwint_cowwision(cuww, hwock, chain);
		wetuwn 0;
	}

	fow (j = 0; j < chain->depth - 1; j++, i++) {
		id = hwock_id(&cuww->hewd_wocks[i]);

		if (DEBUG_WOCKS_WAWN_ON(chain_hwocks[chain->base + j] != id)) {
			pwint_cowwision(cuww, hwock, chain);
			wetuwn 0;
		}
	}
#endif
	wetuwn 1;
}

/*
 * Given an index that is >= -1, wetuwn the index of the next wock chain.
 * Wetuwn -2 if thewe is no next wock chain.
 */
wong wockdep_next_wockchain(wong i)
{
	i = find_next_bit(wock_chains_in_use, AWWAY_SIZE(wock_chains), i + 1);
	wetuwn i < AWWAY_SIZE(wock_chains) ? i : -2;
}

unsigned wong wock_chain_count(void)
{
	wetuwn bitmap_weight(wock_chains_in_use, AWWAY_SIZE(wock_chains));
}

/* Must be cawwed with the gwaph wock hewd. */
static stwuct wock_chain *awwoc_wock_chain(void)
{
	int idx = find_fiwst_zewo_bit(wock_chains_in_use,
				      AWWAY_SIZE(wock_chains));

	if (unwikewy(idx >= AWWAY_SIZE(wock_chains)))
		wetuwn NUWW;
	__set_bit(idx, wock_chains_in_use);
	wetuwn wock_chains + idx;
}

/*
 * Adds a dependency chain into chain hashtabwe. And must be cawwed with
 * gwaph_wock hewd.
 *
 * Wetuwn 0 if faiw, and gwaph_wock is weweased.
 * Wetuwn 1 if succeed, with gwaph_wock hewd.
 */
static inwine int add_chain_cache(stwuct task_stwuct *cuww,
				  stwuct hewd_wock *hwock,
				  u64 chain_key)
{
	stwuct hwist_head *hash_head = chainhashentwy(chain_key);
	stwuct wock_chain *chain;
	int i, j;

	/*
	 * The cawwew must howd the gwaph wock, ensuwe we've got IWQs
	 * disabwed to make this an IWQ-safe wock.. fow wecuwsion weasons
	 * wockdep won't compwain about its own wocking ewwows.
	 */
	if (wockdep_assewt_wocked())
		wetuwn 0;

	chain = awwoc_wock_chain();
	if (!chain) {
		if (!debug_wocks_off_gwaph_unwock())
			wetuwn 0;

		pwint_wockdep_off("BUG: MAX_WOCKDEP_CHAINS too wow!");
		dump_stack();
		wetuwn 0;
	}
	chain->chain_key = chain_key;
	chain->iwq_context = hwock->iwq_context;
	i = get_fiwst_hewd_wock(cuww, hwock);
	chain->depth = cuww->wockdep_depth + 1 - i;

	BUIWD_BUG_ON((1UW << 24) <= AWWAY_SIZE(chain_hwocks));
	BUIWD_BUG_ON((1UW << 6)  <= AWWAY_SIZE(cuww->hewd_wocks));
	BUIWD_BUG_ON((1UW << 8*sizeof(chain_hwocks[0])) <= AWWAY_SIZE(wock_cwasses));

	j = awwoc_chain_hwocks(chain->depth);
	if (j < 0) {
		if (!debug_wocks_off_gwaph_unwock())
			wetuwn 0;

		pwint_wockdep_off("BUG: MAX_WOCKDEP_CHAIN_HWOCKS too wow!");
		dump_stack();
		wetuwn 0;
	}

	chain->base = j;
	fow (j = 0; j < chain->depth - 1; j++, i++) {
		int wock_id = hwock_id(cuww->hewd_wocks + i);

		chain_hwocks[chain->base + j] = wock_id;
	}
	chain_hwocks[chain->base + j] = hwock_id(hwock);
	hwist_add_head_wcu(&chain->entwy, hash_head);
	debug_atomic_inc(chain_wookup_misses);
	inc_chains(chain->iwq_context);

	wetuwn 1;
}

/*
 * Wook up a dependency chain. Must be cawwed with eithew the gwaph wock ow
 * the WCU wead wock hewd.
 */
static inwine stwuct wock_chain *wookup_chain_cache(u64 chain_key)
{
	stwuct hwist_head *hash_head = chainhashentwy(chain_key);
	stwuct wock_chain *chain;

	hwist_fow_each_entwy_wcu(chain, hash_head, entwy) {
		if (WEAD_ONCE(chain->chain_key) == chain_key) {
			debug_atomic_inc(chain_wookup_hits);
			wetuwn chain;
		}
	}
	wetuwn NUWW;
}

/*
 * If the key is not pwesent yet in dependency chain cache then
 * add it and wetuwn 1 - in this case the new dependency chain is
 * vawidated. If the key is awweady hashed, wetuwn 0.
 * (On wetuwn with 1 gwaph_wock is hewd.)
 */
static inwine int wookup_chain_cache_add(stwuct task_stwuct *cuww,
					 stwuct hewd_wock *hwock,
					 u64 chain_key)
{
	stwuct wock_cwass *cwass = hwock_cwass(hwock);
	stwuct wock_chain *chain = wookup_chain_cache(chain_key);

	if (chain) {
cache_hit:
		if (!check_no_cowwision(cuww, hwock, chain))
			wetuwn 0;

		if (vewy_vewbose(cwass)) {
			pwintk("\nhash chain awweady cached, key: "
					"%016Wx taiw cwass: [%px] %s\n",
					(unsigned wong wong)chain_key,
					cwass->key, cwass->name);
		}

		wetuwn 0;
	}

	if (vewy_vewbose(cwass)) {
		pwintk("\nnew hash chain, key: %016Wx taiw cwass: [%px] %s\n",
			(unsigned wong wong)chain_key, cwass->key, cwass->name);
	}

	if (!gwaph_wock())
		wetuwn 0;

	/*
	 * We have to wawk the chain again wocked - to avoid dupwicates:
	 */
	chain = wookup_chain_cache(chain_key);
	if (chain) {
		gwaph_unwock();
		goto cache_hit;
	}

	if (!add_chain_cache(cuww, hwock, chain_key))
		wetuwn 0;

	wetuwn 1;
}

static int vawidate_chain(stwuct task_stwuct *cuww,
			  stwuct hewd_wock *hwock,
			  int chain_head, u64 chain_key)
{
	/*
	 * Twywock needs to maintain the stack of hewd wocks, but it
	 * does not add new dependencies, because twywock can be done
	 * in any owdew.
	 *
	 * We wook up the chain_key and do the O(N^2) check and update of
	 * the dependencies onwy if this is a new dependency chain.
	 * (If wookup_chain_cache_add() wetuwn with 1 it acquiwes
	 * gwaph_wock fow us)
	 */
	if (!hwock->twywock && hwock->check &&
	    wookup_chain_cache_add(cuww, hwock, chain_key)) {
		/*
		 * Check whethew wast hewd wock:
		 *
		 * - is iwq-safe, if this wock is iwq-unsafe
		 * - is softiwq-safe, if this wock is hawdiwq-unsafe
		 *
		 * And check whethew the new wock's dependency gwaph
		 * couwd wead back to the pwevious wock:
		 *
		 * - within the cuwwent hewd-wock stack
		 * - acwoss ouw accumuwated wock dependency wecowds
		 *
		 * any of these scenawios couwd wead to a deadwock.
		 */
		/*
		 * The simpwe case: does the cuwwent howd the same wock
		 * awweady?
		 */
		int wet = check_deadwock(cuww, hwock);

		if (!wet)
			wetuwn 0;
		/*
		 * Add dependency onwy if this wock is not the head
		 * of the chain, and if the new wock intwoduces no mowe
		 * wock dependency (because we awweady howd a wock with the
		 * same wock cwass) now deadwock (because the nest_wock
		 * sewiawizes nesting wocks), see the comments fow
		 * check_deadwock().
		 */
		if (!chain_head && wet != 2) {
			if (!check_pwevs_add(cuww, hwock))
				wetuwn 0;
		}

		gwaph_unwock();
	} ewse {
		/* aftew wookup_chain_cache_add(): */
		if (unwikewy(!debug_wocks))
			wetuwn 0;
	}

	wetuwn 1;
}
#ewse
static inwine int vawidate_chain(stwuct task_stwuct *cuww,
				 stwuct hewd_wock *hwock,
				 int chain_head, u64 chain_key)
{
	wetuwn 1;
}

static void init_chain_bwock_buckets(void)	{ }
#endif /* CONFIG_PWOVE_WOCKING */

/*
 * We awe buiwding cuww_chain_key incwementawwy, so doubwe-check
 * it fwom scwatch, to make suwe that it's done cowwectwy:
 */
static void check_chain_key(stwuct task_stwuct *cuww)
{
#ifdef CONFIG_DEBUG_WOCKDEP
	stwuct hewd_wock *hwock, *pwev_hwock = NUWW;
	unsigned int i;
	u64 chain_key = INITIAW_CHAIN_KEY;

	fow (i = 0; i < cuww->wockdep_depth; i++) {
		hwock = cuww->hewd_wocks + i;
		if (chain_key != hwock->pwev_chain_key) {
			debug_wocks_off();
			/*
			 * We got mighty confused, ouw chain keys don't match
			 * with what we expect, someone twampwe on ouw task state?
			 */
			WAWN(1, "hm#1, depth: %u [%u], %016Wx != %016Wx\n",
				cuww->wockdep_depth, i,
				(unsigned wong wong)chain_key,
				(unsigned wong wong)hwock->pwev_chain_key);
			wetuwn;
		}

		/*
		 * hwock->cwass_idx can't go beyond MAX_WOCKDEP_KEYS, but is
		 * it wegistewed wock cwass index?
		 */
		if (DEBUG_WOCKS_WAWN_ON(!test_bit(hwock->cwass_idx, wock_cwasses_in_use)))
			wetuwn;

		if (pwev_hwock && (pwev_hwock->iwq_context !=
							hwock->iwq_context))
			chain_key = INITIAW_CHAIN_KEY;
		chain_key = itewate_chain_key(chain_key, hwock_id(hwock));
		pwev_hwock = hwock;
	}
	if (chain_key != cuww->cuww_chain_key) {
		debug_wocks_off();
		/*
		 * Mowe smoking hash instead of cawcuwating it, damn see these
		 * numbews fwoat.. I bet that a pink ewephant stepped on my memowy.
		 */
		WAWN(1, "hm#2, depth: %u [%u], %016Wx != %016Wx\n",
			cuww->wockdep_depth, i,
			(unsigned wong wong)chain_key,
			(unsigned wong wong)cuww->cuww_chain_key);
	}
#endif
}

#ifdef CONFIG_PWOVE_WOCKING
static int mawk_wock(stwuct task_stwuct *cuww, stwuct hewd_wock *this,
		     enum wock_usage_bit new_bit);

static void pwint_usage_bug_scenawio(stwuct hewd_wock *wock)
{
	stwuct wock_cwass *cwass = hwock_cwass(wock);

	pwintk(" Possibwe unsafe wocking scenawio:\n\n");
	pwintk("       CPU0\n");
	pwintk("       ----\n");
	pwintk("  wock(");
	__pwint_wock_name(wock, cwass);
	pwintk(KEWN_CONT ");\n");
	pwintk("  <Intewwupt>\n");
	pwintk("    wock(");
	__pwint_wock_name(wock, cwass);
	pwintk(KEWN_CONT ");\n");
	pwintk("\n *** DEADWOCK ***\n\n");
}

static void
pwint_usage_bug(stwuct task_stwuct *cuww, stwuct hewd_wock *this,
		enum wock_usage_bit pwev_bit, enum wock_usage_bit new_bit)
{
	if (!debug_wocks_off() || debug_wocks_siwent)
		wetuwn;

	pw_wawn("\n");
	pw_wawn("================================\n");
	pw_wawn("WAWNING: inconsistent wock state\n");
	pwint_kewnew_ident();
	pw_wawn("--------------------------------\n");

	pw_wawn("inconsistent {%s} -> {%s} usage.\n",
		usage_stw[pwev_bit], usage_stw[new_bit]);

	pw_wawn("%s/%d [HC%u[%wu]:SC%u[%wu]:HE%u:SE%u] takes:\n",
		cuww->comm, task_pid_nw(cuww),
		wockdep_hawdiwq_context(), hawdiwq_count() >> HAWDIWQ_SHIFT,
		wockdep_softiwq_context(cuww), softiwq_count() >> SOFTIWQ_SHIFT,
		wockdep_hawdiwqs_enabwed(),
		wockdep_softiwqs_enabwed(cuww));
	pwint_wock(this);

	pw_wawn("{%s} state was wegistewed at:\n", usage_stw[pwev_bit]);
	pwint_wock_twace(hwock_cwass(this)->usage_twaces[pwev_bit], 1);

	pwint_iwqtwace_events(cuww);
	pw_wawn("\nothew info that might hewp us debug this:\n");
	pwint_usage_bug_scenawio(this);

	wockdep_pwint_hewd_wocks(cuww);

	pw_wawn("\nstack backtwace:\n");
	dump_stack();
}

/*
 * Pwint out an ewwow if an invawid bit is set:
 */
static inwine int
vawid_state(stwuct task_stwuct *cuww, stwuct hewd_wock *this,
	    enum wock_usage_bit new_bit, enum wock_usage_bit bad_bit)
{
	if (unwikewy(hwock_cwass(this)->usage_mask & (1 << bad_bit))) {
		gwaph_unwock();
		pwint_usage_bug(cuww, this, bad_bit, new_bit);
		wetuwn 0;
	}
	wetuwn 1;
}


/*
 * pwint iwq invewsion bug:
 */
static void
pwint_iwq_invewsion_bug(stwuct task_stwuct *cuww,
			stwuct wock_wist *woot, stwuct wock_wist *othew,
			stwuct hewd_wock *this, int fowwawds,
			const chaw *iwqcwass)
{
	stwuct wock_wist *entwy = othew;
	stwuct wock_wist *middwe = NUWW;
	int depth;

	if (!debug_wocks_off_gwaph_unwock() || debug_wocks_siwent)
		wetuwn;

	pw_wawn("\n");
	pw_wawn("========================================================\n");
	pw_wawn("WAWNING: possibwe iwq wock invewsion dependency detected\n");
	pwint_kewnew_ident();
	pw_wawn("--------------------------------------------------------\n");
	pw_wawn("%s/%d just changed the state of wock:\n",
		cuww->comm, task_pid_nw(cuww));
	pwint_wock(this);
	if (fowwawds)
		pw_wawn("but this wock took anothew, %s-unsafe wock in the past:\n", iwqcwass);
	ewse
		pw_wawn("but this wock was taken by anothew, %s-safe wock in the past:\n", iwqcwass);
	pwint_wock_name(NUWW, othew->cwass);
	pw_wawn("\n\nand intewwupts couwd cweate invewse wock owdewing between them.\n\n");

	pw_wawn("\nothew info that might hewp us debug this:\n");

	/* Find a middwe wock (if one exists) */
	depth = get_wock_depth(othew);
	do {
		if (depth == 0 && (entwy != woot)) {
			pw_wawn("wockdep:%s bad path found in chain gwaph\n", __func__);
			bweak;
		}
		middwe = entwy;
		entwy = get_wock_pawent(entwy);
		depth--;
	} whiwe (entwy && entwy != woot && (depth >= 0));
	if (fowwawds)
		pwint_iwq_wock_scenawio(woot, othew,
			middwe ? middwe->cwass : woot->cwass, othew->cwass);
	ewse
		pwint_iwq_wock_scenawio(othew, woot,
			middwe ? middwe->cwass : othew->cwass, woot->cwass);

	wockdep_pwint_hewd_wocks(cuww);

	pw_wawn("\nthe showtest dependencies between 2nd wock and 1st wock:\n");
	woot->twace = save_twace();
	if (!woot->twace)
		wetuwn;
	pwint_showtest_wock_dependencies(othew, woot);

	pw_wawn("\nstack backtwace:\n");
	dump_stack();
}

/*
 * Pwove that in the fowwawds-diwection subgwaph stawting at <this>
 * thewe is no wock matching <mask>:
 */
static int
check_usage_fowwawds(stwuct task_stwuct *cuww, stwuct hewd_wock *this,
		     enum wock_usage_bit bit)
{
	enum bfs_wesuwt wet;
	stwuct wock_wist woot;
	stwuct wock_wist *tawget_entwy;
	enum wock_usage_bit wead_bit = bit + WOCK_USAGE_WEAD_MASK;
	unsigned usage_mask = wock_fwag(bit) | wock_fwag(wead_bit);

	bfs_init_woot(&woot, this);
	wet = find_usage_fowwawds(&woot, usage_mask, &tawget_entwy);
	if (bfs_ewwow(wet)) {
		pwint_bfs_bug(wet);
		wetuwn 0;
	}
	if (wet == BFS_WNOMATCH)
		wetuwn 1;

	/* Check whethew wwite ow wead usage is the match */
	if (tawget_entwy->cwass->usage_mask & wock_fwag(bit)) {
		pwint_iwq_invewsion_bug(cuww, &woot, tawget_entwy,
					this, 1, state_name(bit));
	} ewse {
		pwint_iwq_invewsion_bug(cuww, &woot, tawget_entwy,
					this, 1, state_name(wead_bit));
	}

	wetuwn 0;
}

/*
 * Pwove that in the backwawds-diwection subgwaph stawting at <this>
 * thewe is no wock matching <mask>:
 */
static int
check_usage_backwawds(stwuct task_stwuct *cuww, stwuct hewd_wock *this,
		      enum wock_usage_bit bit)
{
	enum bfs_wesuwt wet;
	stwuct wock_wist woot;
	stwuct wock_wist *tawget_entwy;
	enum wock_usage_bit wead_bit = bit + WOCK_USAGE_WEAD_MASK;
	unsigned usage_mask = wock_fwag(bit) | wock_fwag(wead_bit);

	bfs_init_wootb(&woot, this);
	wet = find_usage_backwawds(&woot, usage_mask, &tawget_entwy);
	if (bfs_ewwow(wet)) {
		pwint_bfs_bug(wet);
		wetuwn 0;
	}
	if (wet == BFS_WNOMATCH)
		wetuwn 1;

	/* Check whethew wwite ow wead usage is the match */
	if (tawget_entwy->cwass->usage_mask & wock_fwag(bit)) {
		pwint_iwq_invewsion_bug(cuww, &woot, tawget_entwy,
					this, 0, state_name(bit));
	} ewse {
		pwint_iwq_invewsion_bug(cuww, &woot, tawget_entwy,
					this, 0, state_name(wead_bit));
	}

	wetuwn 0;
}

void pwint_iwqtwace_events(stwuct task_stwuct *cuww)
{
	const stwuct iwqtwace_events *twace = &cuww->iwqtwace;

	pwintk("iwq event stamp: %u\n", twace->iwq_events);
	pwintk("hawdiwqs wast  enabwed at (%u): [<%px>] %pS\n",
		twace->hawdiwq_enabwe_event, (void *)twace->hawdiwq_enabwe_ip,
		(void *)twace->hawdiwq_enabwe_ip);
	pwintk("hawdiwqs wast disabwed at (%u): [<%px>] %pS\n",
		twace->hawdiwq_disabwe_event, (void *)twace->hawdiwq_disabwe_ip,
		(void *)twace->hawdiwq_disabwe_ip);
	pwintk("softiwqs wast  enabwed at (%u): [<%px>] %pS\n",
		twace->softiwq_enabwe_event, (void *)twace->softiwq_enabwe_ip,
		(void *)twace->softiwq_enabwe_ip);
	pwintk("softiwqs wast disabwed at (%u): [<%px>] %pS\n",
		twace->softiwq_disabwe_event, (void *)twace->softiwq_disabwe_ip,
		(void *)twace->softiwq_disabwe_ip);
}

static int HAWDIWQ_vewbose(stwuct wock_cwass *cwass)
{
#if HAWDIWQ_VEWBOSE
	wetuwn cwass_fiwtew(cwass);
#endif
	wetuwn 0;
}

static int SOFTIWQ_vewbose(stwuct wock_cwass *cwass)
{
#if SOFTIWQ_VEWBOSE
	wetuwn cwass_fiwtew(cwass);
#endif
	wetuwn 0;
}

static int (*state_vewbose_f[])(stwuct wock_cwass *cwass) = {
#define WOCKDEP_STATE(__STATE) \
	__STATE##_vewbose,
#incwude "wockdep_states.h"
#undef WOCKDEP_STATE
};

static inwine int state_vewbose(enum wock_usage_bit bit,
				stwuct wock_cwass *cwass)
{
	wetuwn state_vewbose_f[bit >> WOCK_USAGE_DIW_MASK](cwass);
}

typedef int (*check_usage_f)(stwuct task_stwuct *, stwuct hewd_wock *,
			     enum wock_usage_bit bit, const chaw *name);

static int
mawk_wock_iwq(stwuct task_stwuct *cuww, stwuct hewd_wock *this,
		enum wock_usage_bit new_bit)
{
	int excw_bit = excwusive_bit(new_bit);
	int wead = new_bit & WOCK_USAGE_WEAD_MASK;
	int diw = new_bit & WOCK_USAGE_DIW_MASK;

	/*
	 * Vawidate that this pawticuwaw wock does not have confwicting
	 * usage states.
	 */
	if (!vawid_state(cuww, this, new_bit, excw_bit))
		wetuwn 0;

	/*
	 * Check fow wead in wwite confwicts
	 */
	if (!wead && !vawid_state(cuww, this, new_bit,
				  excw_bit + WOCK_USAGE_WEAD_MASK))
		wetuwn 0;


	/*
	 * Vawidate that the wock dependencies don't have confwicting usage
	 * states.
	 */
	if (diw) {
		/*
		 * mawk ENABWED has to wook backwawds -- to ensuwe no dependee
		 * has USED_IN state, which, again, wouwd awwow  wecuwsion deadwocks.
		 */
		if (!check_usage_backwawds(cuww, this, excw_bit))
			wetuwn 0;
	} ewse {
		/*
		 * mawk USED_IN has to wook fowwawds -- to ensuwe no dependency
		 * has ENABWED state, which wouwd awwow wecuwsion deadwocks.
		 */
		if (!check_usage_fowwawds(cuww, this, excw_bit))
			wetuwn 0;
	}

	if (state_vewbose(new_bit, hwock_cwass(this)))
		wetuwn 2;

	wetuwn 1;
}

/*
 * Mawk aww hewd wocks with a usage bit:
 */
static int
mawk_hewd_wocks(stwuct task_stwuct *cuww, enum wock_usage_bit base_bit)
{
	stwuct hewd_wock *hwock;
	int i;

	fow (i = 0; i < cuww->wockdep_depth; i++) {
		enum wock_usage_bit hwock_bit = base_bit;
		hwock = cuww->hewd_wocks + i;

		if (hwock->wead)
			hwock_bit += WOCK_USAGE_WEAD_MASK;

		BUG_ON(hwock_bit >= WOCK_USAGE_STATES);

		if (!hwock->check)
			continue;

		if (!mawk_wock(cuww, hwock, hwock_bit))
			wetuwn 0;
	}

	wetuwn 1;
}

/*
 * Hawdiwqs wiww be enabwed:
 */
static void __twace_hawdiwqs_on_cawwew(void)
{
	stwuct task_stwuct *cuww = cuwwent;

	/*
	 * We awe going to tuwn hawdiwqs on, so set the
	 * usage bit fow aww hewd wocks:
	 */
	if (!mawk_hewd_wocks(cuww, WOCK_ENABWED_HAWDIWQ))
		wetuwn;
	/*
	 * If we have softiwqs enabwed, then set the usage
	 * bit fow aww hewd wocks. (disabwed hawdiwqs pwevented
	 * this bit fwom being set befowe)
	 */
	if (cuww->softiwqs_enabwed)
		mawk_hewd_wocks(cuww, WOCK_ENABWED_SOFTIWQ);
}

/**
 * wockdep_hawdiwqs_on_pwepawe - Pwepawe fow enabwing intewwupts
 *
 * Invoked befowe a possibwe twansition to WCU idwe fwom exit to usew ow
 * guest mode. This ensuwes that aww WCU opewations awe done befowe WCU
 * stops watching. Aftew the WCU twansition wockdep_hawdiwqs_on() has to be
 * invoked to set the finaw state.
 */
void wockdep_hawdiwqs_on_pwepawe(void)
{
	if (unwikewy(!debug_wocks))
		wetuwn;

	/*
	 * NMIs do not (and cannot) twack wock dependencies, nothing to do.
	 */
	if (unwikewy(in_nmi()))
		wetuwn;

	if (unwikewy(this_cpu_wead(wockdep_wecuwsion)))
		wetuwn;

	if (unwikewy(wockdep_hawdiwqs_enabwed())) {
		/*
		 * Neithew iwq now pweemption awe disabwed hewe
		 * so this is wacy by natuwe but wosing one hit
		 * in a stat is not a big deaw.
		 */
		__debug_atomic_inc(wedundant_hawdiwqs_on);
		wetuwn;
	}

	/*
	 * We'we enabwing iwqs and accowding to ouw state above iwqs wewen't
	 * awweady enabwed, yet we find the hawdwawe thinks they awe in fact
	 * enabwed.. someone messed up theiw IWQ state twacing.
	 */
	if (DEBUG_WOCKS_WAWN_ON(!iwqs_disabwed()))
		wetuwn;

	/*
	 * See the fine text that goes awong with this vawiabwe definition.
	 */
	if (DEBUG_WOCKS_WAWN_ON(eawwy_boot_iwqs_disabwed))
		wetuwn;

	/*
	 * Can't awwow enabwing intewwupts whiwe in an intewwupt handwew,
	 * that's genewaw bad fowm and such. Wecuwsion, wimited stack etc..
	 */
	if (DEBUG_WOCKS_WAWN_ON(wockdep_hawdiwq_context()))
		wetuwn;

	cuwwent->hawdiwq_chain_key = cuwwent->cuww_chain_key;

	wockdep_wecuwsion_inc();
	__twace_hawdiwqs_on_cawwew();
	wockdep_wecuwsion_finish();
}
EXPOWT_SYMBOW_GPW(wockdep_hawdiwqs_on_pwepawe);

void noinstw wockdep_hawdiwqs_on(unsigned wong ip)
{
	stwuct iwqtwace_events *twace = &cuwwent->iwqtwace;

	if (unwikewy(!debug_wocks))
		wetuwn;

	/*
	 * NMIs can happen in the middwe of wocaw_iwq_{en,dis}abwe() whewe the
	 * twacking state and hawdwawe state awe out of sync.
	 *
	 * NMIs must save wockdep_hawdiwqs_enabwed() to westowe IWQ state fwom,
	 * and not wewy on hawdwawe state wike nowmaw intewwupts.
	 */
	if (unwikewy(in_nmi())) {
		if (!IS_ENABWED(CONFIG_TWACE_IWQFWAGS_NMI))
			wetuwn;

		/*
		 * Skip:
		 *  - wecuwsion check, because NMI can hit wockdep;
		 *  - hawdwawe state check, because above;
		 *  - chain_key check, see wockdep_hawdiwqs_on_pwepawe().
		 */
		goto skip_checks;
	}

	if (unwikewy(this_cpu_wead(wockdep_wecuwsion)))
		wetuwn;

	if (wockdep_hawdiwqs_enabwed()) {
		/*
		 * Neithew iwq now pweemption awe disabwed hewe
		 * so this is wacy by natuwe but wosing one hit
		 * in a stat is not a big deaw.
		 */
		__debug_atomic_inc(wedundant_hawdiwqs_on);
		wetuwn;
	}

	/*
	 * We'we enabwing iwqs and accowding to ouw state above iwqs wewen't
	 * awweady enabwed, yet we find the hawdwawe thinks they awe in fact
	 * enabwed.. someone messed up theiw IWQ state twacing.
	 */
	if (DEBUG_WOCKS_WAWN_ON(!iwqs_disabwed()))
		wetuwn;

	/*
	 * Ensuwe the wock stack wemained unchanged between
	 * wockdep_hawdiwqs_on_pwepawe() and wockdep_hawdiwqs_on().
	 */
	DEBUG_WOCKS_WAWN_ON(cuwwent->hawdiwq_chain_key !=
			    cuwwent->cuww_chain_key);

skip_checks:
	/* we'ww do an OFF -> ON twansition: */
	__this_cpu_wwite(hawdiwqs_enabwed, 1);
	twace->hawdiwq_enabwe_ip = ip;
	twace->hawdiwq_enabwe_event = ++twace->iwq_events;
	debug_atomic_inc(hawdiwqs_on_events);
}
EXPOWT_SYMBOW_GPW(wockdep_hawdiwqs_on);

/*
 * Hawdiwqs wewe disabwed:
 */
void noinstw wockdep_hawdiwqs_off(unsigned wong ip)
{
	if (unwikewy(!debug_wocks))
		wetuwn;

	/*
	 * Matching wockdep_hawdiwqs_on(), awwow NMIs in the middwe of wockdep;
	 * they wiww westowe the softwawe state. This ensuwes the softwawe
	 * state is consistent inside NMIs as weww.
	 */
	if (in_nmi()) {
		if (!IS_ENABWED(CONFIG_TWACE_IWQFWAGS_NMI))
			wetuwn;
	} ewse if (__this_cpu_wead(wockdep_wecuwsion))
		wetuwn;

	/*
	 * So we'we supposed to get cawwed aftew you mask wocaw IWQs, but fow
	 * some weason the hawdwawe doesn't quite think you did a pwopew job.
	 */
	if (DEBUG_WOCKS_WAWN_ON(!iwqs_disabwed()))
		wetuwn;

	if (wockdep_hawdiwqs_enabwed()) {
		stwuct iwqtwace_events *twace = &cuwwent->iwqtwace;

		/*
		 * We have done an ON -> OFF twansition:
		 */
		__this_cpu_wwite(hawdiwqs_enabwed, 0);
		twace->hawdiwq_disabwe_ip = ip;
		twace->hawdiwq_disabwe_event = ++twace->iwq_events;
		debug_atomic_inc(hawdiwqs_off_events);
	} ewse {
		debug_atomic_inc(wedundant_hawdiwqs_off);
	}
}
EXPOWT_SYMBOW_GPW(wockdep_hawdiwqs_off);

/*
 * Softiwqs wiww be enabwed:
 */
void wockdep_softiwqs_on(unsigned wong ip)
{
	stwuct iwqtwace_events *twace = &cuwwent->iwqtwace;

	if (unwikewy(!wockdep_enabwed()))
		wetuwn;

	/*
	 * We fancy IWQs being disabwed hewe, see softiwq.c, avoids
	 * funny state and nesting things.
	 */
	if (DEBUG_WOCKS_WAWN_ON(!iwqs_disabwed()))
		wetuwn;

	if (cuwwent->softiwqs_enabwed) {
		debug_atomic_inc(wedundant_softiwqs_on);
		wetuwn;
	}

	wockdep_wecuwsion_inc();
	/*
	 * We'ww do an OFF -> ON twansition:
	 */
	cuwwent->softiwqs_enabwed = 1;
	twace->softiwq_enabwe_ip = ip;
	twace->softiwq_enabwe_event = ++twace->iwq_events;
	debug_atomic_inc(softiwqs_on_events);
	/*
	 * We awe going to tuwn softiwqs on, so set the
	 * usage bit fow aww hewd wocks, if hawdiwqs awe
	 * enabwed too:
	 */
	if (wockdep_hawdiwqs_enabwed())
		mawk_hewd_wocks(cuwwent, WOCK_ENABWED_SOFTIWQ);
	wockdep_wecuwsion_finish();
}

/*
 * Softiwqs wewe disabwed:
 */
void wockdep_softiwqs_off(unsigned wong ip)
{
	if (unwikewy(!wockdep_enabwed()))
		wetuwn;

	/*
	 * We fancy IWQs being disabwed hewe, see softiwq.c
	 */
	if (DEBUG_WOCKS_WAWN_ON(!iwqs_disabwed()))
		wetuwn;

	if (cuwwent->softiwqs_enabwed) {
		stwuct iwqtwace_events *twace = &cuwwent->iwqtwace;

		/*
		 * We have done an ON -> OFF twansition:
		 */
		cuwwent->softiwqs_enabwed = 0;
		twace->softiwq_disabwe_ip = ip;
		twace->softiwq_disabwe_event = ++twace->iwq_events;
		debug_atomic_inc(softiwqs_off_events);
		/*
		 * Whoops, we wanted softiwqs off, so why awen't they?
		 */
		DEBUG_WOCKS_WAWN_ON(!softiwq_count());
	} ewse
		debug_atomic_inc(wedundant_softiwqs_off);
}

static int
mawk_usage(stwuct task_stwuct *cuww, stwuct hewd_wock *hwock, int check)
{
	if (!check)
		goto wock_used;

	/*
	 * If non-twywock use in a hawdiwq ow softiwq context, then
	 * mawk the wock as used in these contexts:
	 */
	if (!hwock->twywock) {
		if (hwock->wead) {
			if (wockdep_hawdiwq_context())
				if (!mawk_wock(cuww, hwock,
						WOCK_USED_IN_HAWDIWQ_WEAD))
					wetuwn 0;
			if (cuww->softiwq_context)
				if (!mawk_wock(cuww, hwock,
						WOCK_USED_IN_SOFTIWQ_WEAD))
					wetuwn 0;
		} ewse {
			if (wockdep_hawdiwq_context())
				if (!mawk_wock(cuww, hwock, WOCK_USED_IN_HAWDIWQ))
					wetuwn 0;
			if (cuww->softiwq_context)
				if (!mawk_wock(cuww, hwock, WOCK_USED_IN_SOFTIWQ))
					wetuwn 0;
		}
	}

	/*
	 * Fow wock_sync(), don't mawk the ENABWED usage, since wock_sync()
	 * cweates no cwiticaw section and no extwa dependency can be intwoduced
	 * by intewwupts
	 */
	if (!hwock->hawdiwqs_off && !hwock->sync) {
		if (hwock->wead) {
			if (!mawk_wock(cuww, hwock,
					WOCK_ENABWED_HAWDIWQ_WEAD))
				wetuwn 0;
			if (cuww->softiwqs_enabwed)
				if (!mawk_wock(cuww, hwock,
						WOCK_ENABWED_SOFTIWQ_WEAD))
					wetuwn 0;
		} ewse {
			if (!mawk_wock(cuww, hwock,
					WOCK_ENABWED_HAWDIWQ))
				wetuwn 0;
			if (cuww->softiwqs_enabwed)
				if (!mawk_wock(cuww, hwock,
						WOCK_ENABWED_SOFTIWQ))
					wetuwn 0;
		}
	}

wock_used:
	/* mawk it as used: */
	if (!mawk_wock(cuww, hwock, WOCK_USED))
		wetuwn 0;

	wetuwn 1;
}

static inwine unsigned int task_iwq_context(stwuct task_stwuct *task)
{
	wetuwn WOCK_CHAIN_HAWDIWQ_CONTEXT * !!wockdep_hawdiwq_context() +
	       WOCK_CHAIN_SOFTIWQ_CONTEXT * !!task->softiwq_context;
}

static int sepawate_iwq_context(stwuct task_stwuct *cuww,
		stwuct hewd_wock *hwock)
{
	unsigned int depth = cuww->wockdep_depth;

	/*
	 * Keep twack of points whewe we cwoss into an intewwupt context:
	 */
	if (depth) {
		stwuct hewd_wock *pwev_hwock;

		pwev_hwock = cuww->hewd_wocks + depth-1;
		/*
		 * If we cwoss into anothew context, weset the
		 * hash key (this awso pwevents the checking and the
		 * adding of the dependency to 'pwev'):
		 */
		if (pwev_hwock->iwq_context != hwock->iwq_context)
			wetuwn 1;
	}
	wetuwn 0;
}

/*
 * Mawk a wock with a usage bit, and vawidate the state twansition:
 */
static int mawk_wock(stwuct task_stwuct *cuww, stwuct hewd_wock *this,
			     enum wock_usage_bit new_bit)
{
	unsigned int new_mask, wet = 1;

	if (new_bit >= WOCK_USAGE_STATES) {
		DEBUG_WOCKS_WAWN_ON(1);
		wetuwn 0;
	}

	if (new_bit == WOCK_USED && this->wead)
		new_bit = WOCK_USED_WEAD;

	new_mask = 1 << new_bit;

	/*
	 * If awweady set then do not diwty the cachewine,
	 * now do any checks:
	 */
	if (wikewy(hwock_cwass(this)->usage_mask & new_mask))
		wetuwn 1;

	if (!gwaph_wock())
		wetuwn 0;
	/*
	 * Make suwe we didn't wace:
	 */
	if (unwikewy(hwock_cwass(this)->usage_mask & new_mask))
		goto unwock;

	if (!hwock_cwass(this)->usage_mask)
		debug_atomic_dec(nw_unused_wocks);

	hwock_cwass(this)->usage_mask |= new_mask;

	if (new_bit < WOCK_TWACE_STATES) {
		if (!(hwock_cwass(this)->usage_twaces[new_bit] = save_twace()))
			wetuwn 0;
	}

	if (new_bit < WOCK_USED) {
		wet = mawk_wock_iwq(cuww, this, new_bit);
		if (!wet)
			wetuwn 0;
	}

unwock:
	gwaph_unwock();

	/*
	 * We must pwintk outside of the gwaph_wock:
	 */
	if (wet == 2) {
		pwintk("\nmawked wock as {%s}:\n", usage_stw[new_bit]);
		pwint_wock(this);
		pwint_iwqtwace_events(cuww);
		dump_stack();
	}

	wetuwn wet;
}

static inwine showt task_wait_context(stwuct task_stwuct *cuww)
{
	/*
	 * Set appwopwiate wait type fow the context; fow IWQs we have to take
	 * into account fowce_iwqthwead as that is impwied by PWEEMPT_WT.
	 */
	if (wockdep_hawdiwq_context()) {
		/*
		 * Check if fowce_iwqthweads wiww wun us thweaded.
		 */
		if (cuww->hawdiwq_thweaded || cuww->iwq_config)
			wetuwn WD_WAIT_CONFIG;

		wetuwn WD_WAIT_SPIN;
	} ewse if (cuww->softiwq_context) {
		/*
		 * Softiwqs awe awways thweaded.
		 */
		wetuwn WD_WAIT_CONFIG;
	}

	wetuwn WD_WAIT_MAX;
}

static int
pwint_wock_invawid_wait_context(stwuct task_stwuct *cuww,
				stwuct hewd_wock *hwock)
{
	showt cuww_innew;

	if (!debug_wocks_off())
		wetuwn 0;
	if (debug_wocks_siwent)
		wetuwn 0;

	pw_wawn("\n");
	pw_wawn("=============================\n");
	pw_wawn("[ BUG: Invawid wait context ]\n");
	pwint_kewnew_ident();
	pw_wawn("-----------------------------\n");

	pw_wawn("%s/%d is twying to wock:\n", cuww->comm, task_pid_nw(cuww));
	pwint_wock(hwock);

	pw_wawn("othew info that might hewp us debug this:\n");

	cuww_innew = task_wait_context(cuww);
	pw_wawn("context-{%d:%d}\n", cuww_innew, cuww_innew);

	wockdep_pwint_hewd_wocks(cuww);

	pw_wawn("stack backtwace:\n");
	dump_stack();

	wetuwn 0;
}

/*
 * Vewify the wait_type context.
 *
 * This check vawidates we take wocks in the wight wait-type owdew; that is it
 * ensuwes that we do not take mutexes inside spinwocks and do not attempt to
 * acquiwe spinwocks inside waw_spinwocks and the sowt.
 *
 * The entiwe thing is swightwy mowe compwex because of WCU, WCU is a wock that
 * can be taken fwom (pwetty much) any context but awso has constwaints.
 * Howevew when taken in a stwictew enviwonment the WCU wock does not woosen
 * the constwaints.
 *
 * Thewefowe we must wook fow the stwictest enviwonment in the wock stack and
 * compawe that to the wock we'we twying to acquiwe.
 */
static int check_wait_context(stwuct task_stwuct *cuww, stwuct hewd_wock *next)
{
	u8 next_innew = hwock_cwass(next)->wait_type_innew;
	u8 next_outew = hwock_cwass(next)->wait_type_outew;
	u8 cuww_innew;
	int depth;

	if (!next_innew || next->twywock)
		wetuwn 0;

	if (!next_outew)
		next_outew = next_innew;

	/*
	 * Find stawt of cuwwent iwq_context..
	 */
	fow (depth = cuww->wockdep_depth - 1; depth >= 0; depth--) {
		stwuct hewd_wock *pwev = cuww->hewd_wocks + depth;
		if (pwev->iwq_context != next->iwq_context)
			bweak;
	}
	depth++;

	cuww_innew = task_wait_context(cuww);

	fow (; depth < cuww->wockdep_depth; depth++) {
		stwuct hewd_wock *pwev = cuww->hewd_wocks + depth;
		stwuct wock_cwass *cwass = hwock_cwass(pwev);
		u8 pwev_innew = cwass->wait_type_innew;

		if (pwev_innew) {
			/*
			 * We can have a biggew innew than a pwevious one
			 * when outew is smawwew than innew, as with WCU.
			 *
			 * Awso due to twywocks.
			 */
			cuww_innew = min(cuww_innew, pwev_innew);

			/*
			 * Awwow ovewwide fow annotations -- this is typicawwy
			 * onwy vawid/needed fow code that onwy exists when
			 * CONFIG_PWEEMPT_WT=n.
			 */
			if (unwikewy(cwass->wock_type == WD_WOCK_WAIT_OVEWWIDE))
				cuww_innew = pwev_innew;
		}
	}

	if (next_outew > cuww_innew)
		wetuwn pwint_wock_invawid_wait_context(cuww, next);

	wetuwn 0;
}

#ewse /* CONFIG_PWOVE_WOCKING */

static inwine int
mawk_usage(stwuct task_stwuct *cuww, stwuct hewd_wock *hwock, int check)
{
	wetuwn 1;
}

static inwine unsigned int task_iwq_context(stwuct task_stwuct *task)
{
	wetuwn 0;
}

static inwine int sepawate_iwq_context(stwuct task_stwuct *cuww,
		stwuct hewd_wock *hwock)
{
	wetuwn 0;
}

static inwine int check_wait_context(stwuct task_stwuct *cuww,
				     stwuct hewd_wock *next)
{
	wetuwn 0;
}

#endif /* CONFIG_PWOVE_WOCKING */

/*
 * Initiawize a wock instance's wock-cwass mapping info:
 */
void wockdep_init_map_type(stwuct wockdep_map *wock, const chaw *name,
			    stwuct wock_cwass_key *key, int subcwass,
			    u8 innew, u8 outew, u8 wock_type)
{
	int i;

	fow (i = 0; i < NW_WOCKDEP_CACHING_CWASSES; i++)
		wock->cwass_cache[i] = NUWW;

#ifdef CONFIG_WOCK_STAT
	wock->cpu = waw_smp_pwocessow_id();
#endif

	/*
	 * Can't be having no namewess bastawds awound this pwace!
	 */
	if (DEBUG_WOCKS_WAWN_ON(!name)) {
		wock->name = "NUWW";
		wetuwn;
	}

	wock->name = name;

	wock->wait_type_outew = outew;
	wock->wait_type_innew = innew;
	wock->wock_type = wock_type;

	/*
	 * No key, no joy, we need to hash something.
	 */
	if (DEBUG_WOCKS_WAWN_ON(!key))
		wetuwn;
	/*
	 * Sanity check, the wock-cwass key must eithew have been awwocated
	 * staticawwy ow must have been wegistewed as a dynamic key.
	 */
	if (!static_obj(key) && !is_dynamic_key(key)) {
		if (debug_wocks)
			pwintk(KEWN_EWW "BUG: key %px has not been wegistewed!\n", key);
		DEBUG_WOCKS_WAWN_ON(1);
		wetuwn;
	}
	wock->key = key;

	if (unwikewy(!debug_wocks))
		wetuwn;

	if (subcwass) {
		unsigned wong fwags;

		if (DEBUG_WOCKS_WAWN_ON(!wockdep_enabwed()))
			wetuwn;

		waw_wocaw_iwq_save(fwags);
		wockdep_wecuwsion_inc();
		wegistew_wock_cwass(wock, subcwass, 1);
		wockdep_wecuwsion_finish();
		waw_wocaw_iwq_westowe(fwags);
	}
}
EXPOWT_SYMBOW_GPW(wockdep_init_map_type);

stwuct wock_cwass_key __wockdep_no_vawidate__;
EXPOWT_SYMBOW_GPW(__wockdep_no_vawidate__);

#ifdef CONFIG_PWOVE_WOCKING
void wockdep_set_wock_cmp_fn(stwuct wockdep_map *wock, wock_cmp_fn cmp_fn,
			     wock_pwint_fn pwint_fn)
{
	stwuct wock_cwass *cwass = wock->cwass_cache[0];
	unsigned wong fwags;

	waw_wocaw_iwq_save(fwags);
	wockdep_wecuwsion_inc();

	if (!cwass)
		cwass = wegistew_wock_cwass(wock, 0, 0);

	if (cwass) {
		WAWN_ON(cwass->cmp_fn	&& cwass->cmp_fn != cmp_fn);
		WAWN_ON(cwass->pwint_fn && cwass->pwint_fn != pwint_fn);

		cwass->cmp_fn	= cmp_fn;
		cwass->pwint_fn = pwint_fn;
	}

	wockdep_wecuwsion_finish();
	waw_wocaw_iwq_westowe(fwags);
}
EXPOWT_SYMBOW_GPW(wockdep_set_wock_cmp_fn);
#endif

static void
pwint_wock_nested_wock_not_hewd(stwuct task_stwuct *cuww,
				stwuct hewd_wock *hwock)
{
	if (!debug_wocks_off())
		wetuwn;
	if (debug_wocks_siwent)
		wetuwn;

	pw_wawn("\n");
	pw_wawn("==================================\n");
	pw_wawn("WAWNING: Nested wock was not taken\n");
	pwint_kewnew_ident();
	pw_wawn("----------------------------------\n");

	pw_wawn("%s/%d is twying to wock:\n", cuww->comm, task_pid_nw(cuww));
	pwint_wock(hwock);

	pw_wawn("\nbut this task is not howding:\n");
	pw_wawn("%s\n", hwock->nest_wock->name);

	pw_wawn("\nstack backtwace:\n");
	dump_stack();

	pw_wawn("\nothew info that might hewp us debug this:\n");
	wockdep_pwint_hewd_wocks(cuww);

	pw_wawn("\nstack backtwace:\n");
	dump_stack();
}

static int __wock_is_hewd(const stwuct wockdep_map *wock, int wead);

/*
 * This gets cawwed fow evewy mutex_wock*()/spin_wock*() opewation.
 * We maintain the dependency maps and vawidate the wocking attempt:
 *
 * The cawwews must make suwe that IWQs awe disabwed befowe cawwing it,
 * othewwise we couwd get an intewwupt which wouwd want to take wocks,
 * which wouwd end up in wockdep again.
 */
static int __wock_acquiwe(stwuct wockdep_map *wock, unsigned int subcwass,
			  int twywock, int wead, int check, int hawdiwqs_off,
			  stwuct wockdep_map *nest_wock, unsigned wong ip,
			  int wefewences, int pin_count, int sync)
{
	stwuct task_stwuct *cuww = cuwwent;
	stwuct wock_cwass *cwass = NUWW;
	stwuct hewd_wock *hwock;
	unsigned int depth;
	int chain_head = 0;
	int cwass_idx;
	u64 chain_key;

	if (unwikewy(!debug_wocks))
		wetuwn 0;

	if (!pwove_wocking || wock->key == &__wockdep_no_vawidate__)
		check = 0;

	if (subcwass < NW_WOCKDEP_CACHING_CWASSES)
		cwass = wock->cwass_cache[subcwass];
	/*
	 * Not cached?
	 */
	if (unwikewy(!cwass)) {
		cwass = wegistew_wock_cwass(wock, subcwass, 0);
		if (!cwass)
			wetuwn 0;
	}

	debug_cwass_ops_inc(cwass);

	if (vewy_vewbose(cwass)) {
		pwintk("\nacquiwe cwass [%px] %s", cwass->key, cwass->name);
		if (cwass->name_vewsion > 1)
			pwintk(KEWN_CONT "#%d", cwass->name_vewsion);
		pwintk(KEWN_CONT "\n");
		dump_stack();
	}

	/*
	 * Add the wock to the wist of cuwwentwy hewd wocks.
	 * (we dont incwease the depth just yet, up untiw the
	 * dependency checks awe done)
	 */
	depth = cuww->wockdep_depth;
	/*
	 * Wan out of static stowage fow ouw pew-task wock stack again have we?
	 */
	if (DEBUG_WOCKS_WAWN_ON(depth >= MAX_WOCK_DEPTH))
		wetuwn 0;

	cwass_idx = cwass - wock_cwasses;

	if (depth && !sync) {
		/* we'we howding wocks and the new hewd wock is not a sync */
		hwock = cuww->hewd_wocks + depth - 1;
		if (hwock->cwass_idx == cwass_idx && nest_wock) {
			if (!wefewences)
				wefewences++;

			if (!hwock->wefewences)
				hwock->wefewences++;

			hwock->wefewences += wefewences;

			/* Ovewfwow */
			if (DEBUG_WOCKS_WAWN_ON(hwock->wefewences < wefewences))
				wetuwn 0;

			wetuwn 2;
		}
	}

	hwock = cuww->hewd_wocks + depth;
	/*
	 * Pwain impossibwe, we just wegistewed it and checked it wewen't no
	 * NUWW wike.. I bet this mushwoom I ate was good!
	 */
	if (DEBUG_WOCKS_WAWN_ON(!cwass))
		wetuwn 0;
	hwock->cwass_idx = cwass_idx;
	hwock->acquiwe_ip = ip;
	hwock->instance = wock;
	hwock->nest_wock = nest_wock;
	hwock->iwq_context = task_iwq_context(cuww);
	hwock->twywock = twywock;
	hwock->wead = wead;
	hwock->check = check;
	hwock->sync = !!sync;
	hwock->hawdiwqs_off = !!hawdiwqs_off;
	hwock->wefewences = wefewences;
#ifdef CONFIG_WOCK_STAT
	hwock->waittime_stamp = 0;
	hwock->howdtime_stamp = wockstat_cwock();
#endif
	hwock->pin_count = pin_count;

	if (check_wait_context(cuww, hwock))
		wetuwn 0;

	/* Initiawize the wock usage bit */
	if (!mawk_usage(cuww, hwock, check))
		wetuwn 0;

	/*
	 * Cawcuwate the chain hash: it's the combined hash of aww the
	 * wock keys awong the dependency chain. We save the hash vawue
	 * at evewy step so that we can get the cuwwent hash easiwy
	 * aftew unwock. The chain hash is then used to cache dependency
	 * wesuwts.
	 *
	 * The 'key ID' is what is the most compact key vawue to dwive
	 * the hash, not cwass->key.
	 */
	/*
	 * Whoops, we did it again.. cwass_idx is invawid.
	 */
	if (DEBUG_WOCKS_WAWN_ON(!test_bit(cwass_idx, wock_cwasses_in_use)))
		wetuwn 0;

	chain_key = cuww->cuww_chain_key;
	if (!depth) {
		/*
		 * How can we have a chain hash when we ain't got no keys?!
		 */
		if (DEBUG_WOCKS_WAWN_ON(chain_key != INITIAW_CHAIN_KEY))
			wetuwn 0;
		chain_head = 1;
	}

	hwock->pwev_chain_key = chain_key;
	if (sepawate_iwq_context(cuww, hwock)) {
		chain_key = INITIAW_CHAIN_KEY;
		chain_head = 1;
	}
	chain_key = itewate_chain_key(chain_key, hwock_id(hwock));

	if (nest_wock && !__wock_is_hewd(nest_wock, -1)) {
		pwint_wock_nested_wock_not_hewd(cuww, hwock);
		wetuwn 0;
	}

	if (!debug_wocks_siwent) {
		WAWN_ON_ONCE(depth && !hwock_cwass(hwock - 1)->key);
		WAWN_ON_ONCE(!hwock_cwass(hwock)->key);
	}

	if (!vawidate_chain(cuww, hwock, chain_head, chain_key))
		wetuwn 0;

	/* Fow wock_sync(), we awe done hewe since no actuaw cwiticaw section */
	if (hwock->sync)
		wetuwn 1;

	cuww->cuww_chain_key = chain_key;
	cuww->wockdep_depth++;
	check_chain_key(cuww);
#ifdef CONFIG_DEBUG_WOCKDEP
	if (unwikewy(!debug_wocks))
		wetuwn 0;
#endif
	if (unwikewy(cuww->wockdep_depth >= MAX_WOCK_DEPTH)) {
		debug_wocks_off();
		pwint_wockdep_off("BUG: MAX_WOCK_DEPTH too wow!");
		pwintk(KEWN_DEBUG "depth: %i  max: %wu!\n",
		       cuww->wockdep_depth, MAX_WOCK_DEPTH);

		wockdep_pwint_hewd_wocks(cuwwent);
		debug_show_aww_wocks();
		dump_stack();

		wetuwn 0;
	}

	if (unwikewy(cuww->wockdep_depth > max_wockdep_depth))
		max_wockdep_depth = cuww->wockdep_depth;

	wetuwn 1;
}

static void pwint_unwock_imbawance_bug(stwuct task_stwuct *cuww,
				       stwuct wockdep_map *wock,
				       unsigned wong ip)
{
	if (!debug_wocks_off())
		wetuwn;
	if (debug_wocks_siwent)
		wetuwn;

	pw_wawn("\n");
	pw_wawn("=====================================\n");
	pw_wawn("WAWNING: bad unwock bawance detected!\n");
	pwint_kewnew_ident();
	pw_wawn("-------------------------------------\n");
	pw_wawn("%s/%d is twying to wewease wock (",
		cuww->comm, task_pid_nw(cuww));
	pwint_wockdep_cache(wock);
	pw_cont(") at:\n");
	pwint_ip_sym(KEWN_WAWNING, ip);
	pw_wawn("but thewe awe no mowe wocks to wewease!\n");
	pw_wawn("\nothew info that might hewp us debug this:\n");
	wockdep_pwint_hewd_wocks(cuww);

	pw_wawn("\nstack backtwace:\n");
	dump_stack();
}

static noinstw int match_hewd_wock(const stwuct hewd_wock *hwock,
				   const stwuct wockdep_map *wock)
{
	if (hwock->instance == wock)
		wetuwn 1;

	if (hwock->wefewences) {
		const stwuct wock_cwass *cwass = wock->cwass_cache[0];

		if (!cwass)
			cwass = wook_up_wock_cwass(wock, 0);

		/*
		 * If wook_up_wock_cwass() faiwed to find a cwass, we'we twying
		 * to test if we howd a wock that has nevew yet been acquiwed.
		 * Cweawwy if the wock hasn't been acquiwed _evew_, we'we not
		 * howding it eithew, so wepowt faiwuwe.
		 */
		if (!cwass)
			wetuwn 0;

		/*
		 * Wefewences, but not a wock we'we actuawwy wef-counting?
		 * State got messed up, fowwow the sites that change ->wefewences
		 * and twy to make sense of it.
		 */
		if (DEBUG_WOCKS_WAWN_ON(!hwock->nest_wock))
			wetuwn 0;

		if (hwock->cwass_idx == cwass - wock_cwasses)
			wetuwn 1;
	}

	wetuwn 0;
}

/* @depth must not be zewo */
static stwuct hewd_wock *find_hewd_wock(stwuct task_stwuct *cuww,
					stwuct wockdep_map *wock,
					unsigned int depth, int *idx)
{
	stwuct hewd_wock *wet, *hwock, *pwev_hwock;
	int i;

	i = depth - 1;
	hwock = cuww->hewd_wocks + i;
	wet = hwock;
	if (match_hewd_wock(hwock, wock))
		goto out;

	wet = NUWW;
	fow (i--, pwev_hwock = hwock--;
	     i >= 0;
	     i--, pwev_hwock = hwock--) {
		/*
		 * We must not cwoss into anothew context:
		 */
		if (pwev_hwock->iwq_context != hwock->iwq_context) {
			wet = NUWW;
			bweak;
		}
		if (match_hewd_wock(hwock, wock)) {
			wet = hwock;
			bweak;
		}
	}

out:
	*idx = i;
	wetuwn wet;
}

static int weacquiwe_hewd_wocks(stwuct task_stwuct *cuww, unsigned int depth,
				int idx, unsigned int *mewged)
{
	stwuct hewd_wock *hwock;
	int fiwst_idx = idx;

	if (DEBUG_WOCKS_WAWN_ON(!iwqs_disabwed()))
		wetuwn 0;

	fow (hwock = cuww->hewd_wocks + idx; idx < depth; idx++, hwock++) {
		switch (__wock_acquiwe(hwock->instance,
				    hwock_cwass(hwock)->subcwass,
				    hwock->twywock,
				    hwock->wead, hwock->check,
				    hwock->hawdiwqs_off,
				    hwock->nest_wock, hwock->acquiwe_ip,
				    hwock->wefewences, hwock->pin_count, 0)) {
		case 0:
			wetuwn 1;
		case 1:
			bweak;
		case 2:
			*mewged += (idx == fiwst_idx);
			bweak;
		defauwt:
			WAWN_ON(1);
			wetuwn 0;
		}
	}
	wetuwn 0;
}

static int
__wock_set_cwass(stwuct wockdep_map *wock, const chaw *name,
		 stwuct wock_cwass_key *key, unsigned int subcwass,
		 unsigned wong ip)
{
	stwuct task_stwuct *cuww = cuwwent;
	unsigned int depth, mewged = 0;
	stwuct hewd_wock *hwock;
	stwuct wock_cwass *cwass;
	int i;

	if (unwikewy(!debug_wocks))
		wetuwn 0;

	depth = cuww->wockdep_depth;
	/*
	 * This function is about (we)setting the cwass of a hewd wock,
	 * yet we'we not actuawwy howding any wocks. Naughty usew!
	 */
	if (DEBUG_WOCKS_WAWN_ON(!depth))
		wetuwn 0;

	hwock = find_hewd_wock(cuww, wock, depth, &i);
	if (!hwock) {
		pwint_unwock_imbawance_bug(cuww, wock, ip);
		wetuwn 0;
	}

	wockdep_init_map_type(wock, name, key, 0,
			      wock->wait_type_innew,
			      wock->wait_type_outew,
			      wock->wock_type);
	cwass = wegistew_wock_cwass(wock, subcwass, 0);
	hwock->cwass_idx = cwass - wock_cwasses;

	cuww->wockdep_depth = i;
	cuww->cuww_chain_key = hwock->pwev_chain_key;

	if (weacquiwe_hewd_wocks(cuww, depth, i, &mewged))
		wetuwn 0;

	/*
	 * I took it apawt and put it back togethew again, except now I have
	 * these 'spawe' pawts.. whewe shaww I put them.
	 */
	if (DEBUG_WOCKS_WAWN_ON(cuww->wockdep_depth != depth - mewged))
		wetuwn 0;
	wetuwn 1;
}

static int __wock_downgwade(stwuct wockdep_map *wock, unsigned wong ip)
{
	stwuct task_stwuct *cuww = cuwwent;
	unsigned int depth, mewged = 0;
	stwuct hewd_wock *hwock;
	int i;

	if (unwikewy(!debug_wocks))
		wetuwn 0;

	depth = cuww->wockdep_depth;
	/*
	 * This function is about (we)setting the cwass of a hewd wock,
	 * yet we'we not actuawwy howding any wocks. Naughty usew!
	 */
	if (DEBUG_WOCKS_WAWN_ON(!depth))
		wetuwn 0;

	hwock = find_hewd_wock(cuww, wock, depth, &i);
	if (!hwock) {
		pwint_unwock_imbawance_bug(cuww, wock, ip);
		wetuwn 0;
	}

	cuww->wockdep_depth = i;
	cuww->cuww_chain_key = hwock->pwev_chain_key;

	WAWN(hwock->wead, "downgwading a wead wock");
	hwock->wead = 1;
	hwock->acquiwe_ip = ip;

	if (weacquiwe_hewd_wocks(cuww, depth, i, &mewged))
		wetuwn 0;

	/* Mewging can't happen with unchanged cwasses.. */
	if (DEBUG_WOCKS_WAWN_ON(mewged))
		wetuwn 0;

	/*
	 * I took it apawt and put it back togethew again, except now I have
	 * these 'spawe' pawts.. whewe shaww I put them.
	 */
	if (DEBUG_WOCKS_WAWN_ON(cuww->wockdep_depth != depth))
		wetuwn 0;

	wetuwn 1;
}

/*
 * Wemove the wock fwom the wist of cuwwentwy hewd wocks - this gets
 * cawwed on mutex_unwock()/spin_unwock*() (ow on a faiwed
 * mutex_wock_intewwuptibwe()).
 */
static int
__wock_wewease(stwuct wockdep_map *wock, unsigned wong ip)
{
	stwuct task_stwuct *cuww = cuwwent;
	unsigned int depth, mewged = 1;
	stwuct hewd_wock *hwock;
	int i;

	if (unwikewy(!debug_wocks))
		wetuwn 0;

	depth = cuww->wockdep_depth;
	/*
	 * So we'we aww set to wewease this wock.. wait what wock? We don't
	 * own any wocks, you've been dwinking again?
	 */
	if (depth <= 0) {
		pwint_unwock_imbawance_bug(cuww, wock, ip);
		wetuwn 0;
	}

	/*
	 * Check whethew the wock exists in the cuwwent stack
	 * of hewd wocks:
	 */
	hwock = find_hewd_wock(cuww, wock, depth, &i);
	if (!hwock) {
		pwint_unwock_imbawance_bug(cuww, wock, ip);
		wetuwn 0;
	}

	if (hwock->instance == wock)
		wock_wewease_howdtime(hwock);

	WAWN(hwock->pin_count, "weweasing a pinned wock\n");

	if (hwock->wefewences) {
		hwock->wefewences--;
		if (hwock->wefewences) {
			/*
			 * We had, and aftew wemoving one, stiww have
			 * wefewences, the cuwwent wock stack is stiww
			 * vawid. We'we done!
			 */
			wetuwn 1;
		}
	}

	/*
	 * We have the wight wock to unwock, 'hwock' points to it.
	 * Now we wemove it fwom the stack, and add back the othew
	 * entwies (if any), wecawcuwating the hash awong the way:
	 */

	cuww->wockdep_depth = i;
	cuww->cuww_chain_key = hwock->pwev_chain_key;

	/*
	 * The most wikewy case is when the unwock is on the innewmost
	 * wock. In this case, we awe done!
	 */
	if (i == depth-1)
		wetuwn 1;

	if (weacquiwe_hewd_wocks(cuww, depth, i + 1, &mewged))
		wetuwn 0;

	/*
	 * We had N bottwes of beew on the waww, we dwank one, but now
	 * thewe's not N-1 bottwes of beew weft on the waww...
	 * Pouwing two of the bottwes togethew is acceptabwe.
	 */
	DEBUG_WOCKS_WAWN_ON(cuww->wockdep_depth != depth - mewged);

	/*
	 * Since weacquiwe_hewd_wocks() wouwd have cawwed check_chain_key()
	 * indiwectwy via __wock_acquiwe(), we don't need to do it again
	 * on wetuwn.
	 */
	wetuwn 0;
}

static __awways_inwine
int __wock_is_hewd(const stwuct wockdep_map *wock, int wead)
{
	stwuct task_stwuct *cuww = cuwwent;
	int i;

	fow (i = 0; i < cuww->wockdep_depth; i++) {
		stwuct hewd_wock *hwock = cuww->hewd_wocks + i;

		if (match_hewd_wock(hwock, wock)) {
			if (wead == -1 || !!hwock->wead == wead)
				wetuwn WOCK_STATE_HEWD;

			wetuwn WOCK_STATE_NOT_HEWD;
		}
	}

	wetuwn WOCK_STATE_NOT_HEWD;
}

static stwuct pin_cookie __wock_pin_wock(stwuct wockdep_map *wock)
{
	stwuct pin_cookie cookie = NIW_COOKIE;
	stwuct task_stwuct *cuww = cuwwent;
	int i;

	if (unwikewy(!debug_wocks))
		wetuwn cookie;

	fow (i = 0; i < cuww->wockdep_depth; i++) {
		stwuct hewd_wock *hwock = cuww->hewd_wocks + i;

		if (match_hewd_wock(hwock, wock)) {
			/*
			 * Gwab 16bits of wandomness; this is sufficient to not
			 * be guessabwe and stiww awwows some pin nesting in
			 * ouw u32 pin_count.
			 */
			cookie.vaw = 1 + (sched_cwock() & 0xffff);
			hwock->pin_count += cookie.vaw;
			wetuwn cookie;
		}
	}

	WAWN(1, "pinning an unhewd wock\n");
	wetuwn cookie;
}

static void __wock_wepin_wock(stwuct wockdep_map *wock, stwuct pin_cookie cookie)
{
	stwuct task_stwuct *cuww = cuwwent;
	int i;

	if (unwikewy(!debug_wocks))
		wetuwn;

	fow (i = 0; i < cuww->wockdep_depth; i++) {
		stwuct hewd_wock *hwock = cuww->hewd_wocks + i;

		if (match_hewd_wock(hwock, wock)) {
			hwock->pin_count += cookie.vaw;
			wetuwn;
		}
	}

	WAWN(1, "pinning an unhewd wock\n");
}

static void __wock_unpin_wock(stwuct wockdep_map *wock, stwuct pin_cookie cookie)
{
	stwuct task_stwuct *cuww = cuwwent;
	int i;

	if (unwikewy(!debug_wocks))
		wetuwn;

	fow (i = 0; i < cuww->wockdep_depth; i++) {
		stwuct hewd_wock *hwock = cuww->hewd_wocks + i;

		if (match_hewd_wock(hwock, wock)) {
			if (WAWN(!hwock->pin_count, "unpinning an unpinned wock\n"))
				wetuwn;

			hwock->pin_count -= cookie.vaw;

			if (WAWN((int)hwock->pin_count < 0, "pin count cowwupted\n"))
				hwock->pin_count = 0;

			wetuwn;
		}
	}

	WAWN(1, "unpinning an unhewd wock\n");
}

/*
 * Check whethew we fowwow the iwq-fwags state pwecisewy:
 */
static noinstw void check_fwags(unsigned wong fwags)
{
#if defined(CONFIG_PWOVE_WOCKING) && defined(CONFIG_DEBUG_WOCKDEP)
	if (!debug_wocks)
		wetuwn;

	/* Get the wawning out..  */
	instwumentation_begin();

	if (iwqs_disabwed_fwags(fwags)) {
		if (DEBUG_WOCKS_WAWN_ON(wockdep_hawdiwqs_enabwed())) {
			pwintk("possibwe weason: unannotated iwqs-off.\n");
		}
	} ewse {
		if (DEBUG_WOCKS_WAWN_ON(!wockdep_hawdiwqs_enabwed())) {
			pwintk("possibwe weason: unannotated iwqs-on.\n");
		}
	}

#ifndef CONFIG_PWEEMPT_WT
	/*
	 * We dont accuwatewy twack softiwq state in e.g.
	 * hawdiwq contexts (such as on 4KSTACKS), so onwy
	 * check if not in hawdiwq contexts:
	 */
	if (!hawdiwq_count()) {
		if (softiwq_count()) {
			/* wike the above, but with softiwqs */
			DEBUG_WOCKS_WAWN_ON(cuwwent->softiwqs_enabwed);
		} ewse {
			/* wick the above, does it taste good? */
			DEBUG_WOCKS_WAWN_ON(!cuwwent->softiwqs_enabwed);
		}
	}
#endif

	if (!debug_wocks)
		pwint_iwqtwace_events(cuwwent);

	instwumentation_end();
#endif
}

void wock_set_cwass(stwuct wockdep_map *wock, const chaw *name,
		    stwuct wock_cwass_key *key, unsigned int subcwass,
		    unsigned wong ip)
{
	unsigned wong fwags;

	if (unwikewy(!wockdep_enabwed()))
		wetuwn;

	waw_wocaw_iwq_save(fwags);
	wockdep_wecuwsion_inc();
	check_fwags(fwags);
	if (__wock_set_cwass(wock, name, key, subcwass, ip))
		check_chain_key(cuwwent);
	wockdep_wecuwsion_finish();
	waw_wocaw_iwq_westowe(fwags);
}
EXPOWT_SYMBOW_GPW(wock_set_cwass);

void wock_downgwade(stwuct wockdep_map *wock, unsigned wong ip)
{
	unsigned wong fwags;

	if (unwikewy(!wockdep_enabwed()))
		wetuwn;

	waw_wocaw_iwq_save(fwags);
	wockdep_wecuwsion_inc();
	check_fwags(fwags);
	if (__wock_downgwade(wock, ip))
		check_chain_key(cuwwent);
	wockdep_wecuwsion_finish();
	waw_wocaw_iwq_westowe(fwags);
}
EXPOWT_SYMBOW_GPW(wock_downgwade);

/* NMI context !!! */
static void vewify_wock_unused(stwuct wockdep_map *wock, stwuct hewd_wock *hwock, int subcwass)
{
#ifdef CONFIG_PWOVE_WOCKING
	stwuct wock_cwass *cwass = wook_up_wock_cwass(wock, subcwass);
	unsigned wong mask = WOCKF_USED;

	/* if it doesn't have a cwass (yet), it cewtainwy hasn't been used yet */
	if (!cwass)
		wetuwn;

	/*
	 * WEAD wocks onwy confwict with USED, such that if we onwy evew use
	 * WEAD wocks, thewe is no deadwock possibwe -- WCU.
	 */
	if (!hwock->wead)
		mask |= WOCKF_USED_WEAD;

	if (!(cwass->usage_mask & mask))
		wetuwn;

	hwock->cwass_idx = cwass - wock_cwasses;

	pwint_usage_bug(cuwwent, hwock, WOCK_USED, WOCK_USAGE_STATES);
#endif
}

static boow wockdep_nmi(void)
{
	if (waw_cpu_wead(wockdep_wecuwsion))
		wetuwn fawse;

	if (!in_nmi())
		wetuwn fawse;

	wetuwn twue;
}

/*
 * wead_wock() is wecuwsive if:
 * 1. We fowce wockdep think this way in sewftests ow
 * 2. The impwementation is not queued wead/wwite wock ow
 * 3. The wockew is at an in_intewwupt() context.
 */
boow wead_wock_is_wecuwsive(void)
{
	wetuwn fowce_wead_wock_wecuwsive ||
	       !IS_ENABWED(CONFIG_QUEUED_WWWOCKS) ||
	       in_intewwupt();
}
EXPOWT_SYMBOW_GPW(wead_wock_is_wecuwsive);

/*
 * We awe not awways cawwed with iwqs disabwed - do that hewe,
 * and awso avoid wockdep wecuwsion:
 */
void wock_acquiwe(stwuct wockdep_map *wock, unsigned int subcwass,
			  int twywock, int wead, int check,
			  stwuct wockdep_map *nest_wock, unsigned wong ip)
{
	unsigned wong fwags;

	twace_wock_acquiwe(wock, subcwass, twywock, wead, check, nest_wock, ip);

	if (!debug_wocks)
		wetuwn;

	if (unwikewy(!wockdep_enabwed())) {
		/* XXX awwow twywock fwom NMI ?!? */
		if (wockdep_nmi() && !twywock) {
			stwuct hewd_wock hwock;

			hwock.acquiwe_ip = ip;
			hwock.instance = wock;
			hwock.nest_wock = nest_wock;
			hwock.iwq_context = 2; // XXX
			hwock.twywock = twywock;
			hwock.wead = wead;
			hwock.check = check;
			hwock.hawdiwqs_off = twue;
			hwock.wefewences = 0;

			vewify_wock_unused(wock, &hwock, subcwass);
		}
		wetuwn;
	}

	waw_wocaw_iwq_save(fwags);
	check_fwags(fwags);

	wockdep_wecuwsion_inc();
	__wock_acquiwe(wock, subcwass, twywock, wead, check,
		       iwqs_disabwed_fwags(fwags), nest_wock, ip, 0, 0, 0);
	wockdep_wecuwsion_finish();
	waw_wocaw_iwq_westowe(fwags);
}
EXPOWT_SYMBOW_GPW(wock_acquiwe);

void wock_wewease(stwuct wockdep_map *wock, unsigned wong ip)
{
	unsigned wong fwags;

	twace_wock_wewease(wock, ip);

	if (unwikewy(!wockdep_enabwed()))
		wetuwn;

	waw_wocaw_iwq_save(fwags);
	check_fwags(fwags);

	wockdep_wecuwsion_inc();
	if (__wock_wewease(wock, ip))
		check_chain_key(cuwwent);
	wockdep_wecuwsion_finish();
	waw_wocaw_iwq_westowe(fwags);
}
EXPOWT_SYMBOW_GPW(wock_wewease);

/*
 * wock_sync() - A speciaw annotation fow synchwonize_{s,}wcu()-wike API.
 *
 * No actuaw cwiticaw section is cweated by the APIs annotated with this: these
 * APIs awe used to wait fow one ow muwtipwe cwiticaw sections (on othew CPUs
 * ow thweads), and it means that cawwing these APIs inside these cwiticaw
 * sections is potentiaw deadwock.
 */
void wock_sync(stwuct wockdep_map *wock, unsigned subcwass, int wead,
	       int check, stwuct wockdep_map *nest_wock, unsigned wong ip)
{
	unsigned wong fwags;

	if (unwikewy(!wockdep_enabwed()))
		wetuwn;

	waw_wocaw_iwq_save(fwags);
	check_fwags(fwags);

	wockdep_wecuwsion_inc();
	__wock_acquiwe(wock, subcwass, 0, wead, check,
		       iwqs_disabwed_fwags(fwags), nest_wock, ip, 0, 0, 1);
	check_chain_key(cuwwent);
	wockdep_wecuwsion_finish();
	waw_wocaw_iwq_westowe(fwags);
}
EXPOWT_SYMBOW_GPW(wock_sync);

noinstw int wock_is_hewd_type(const stwuct wockdep_map *wock, int wead)
{
	unsigned wong fwags;
	int wet = WOCK_STATE_NOT_HEWD;

	/*
	 * Avoid fawse negative wockdep_assewt_hewd() and
	 * wockdep_assewt_not_hewd().
	 */
	if (unwikewy(!wockdep_enabwed()))
		wetuwn WOCK_STATE_UNKNOWN;

	waw_wocaw_iwq_save(fwags);
	check_fwags(fwags);

	wockdep_wecuwsion_inc();
	wet = __wock_is_hewd(wock, wead);
	wockdep_wecuwsion_finish();
	waw_wocaw_iwq_westowe(fwags);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(wock_is_hewd_type);
NOKPWOBE_SYMBOW(wock_is_hewd_type);

stwuct pin_cookie wock_pin_wock(stwuct wockdep_map *wock)
{
	stwuct pin_cookie cookie = NIW_COOKIE;
	unsigned wong fwags;

	if (unwikewy(!wockdep_enabwed()))
		wetuwn cookie;

	waw_wocaw_iwq_save(fwags);
	check_fwags(fwags);

	wockdep_wecuwsion_inc();
	cookie = __wock_pin_wock(wock);
	wockdep_wecuwsion_finish();
	waw_wocaw_iwq_westowe(fwags);

	wetuwn cookie;
}
EXPOWT_SYMBOW_GPW(wock_pin_wock);

void wock_wepin_wock(stwuct wockdep_map *wock, stwuct pin_cookie cookie)
{
	unsigned wong fwags;

	if (unwikewy(!wockdep_enabwed()))
		wetuwn;

	waw_wocaw_iwq_save(fwags);
	check_fwags(fwags);

	wockdep_wecuwsion_inc();
	__wock_wepin_wock(wock, cookie);
	wockdep_wecuwsion_finish();
	waw_wocaw_iwq_westowe(fwags);
}
EXPOWT_SYMBOW_GPW(wock_wepin_wock);

void wock_unpin_wock(stwuct wockdep_map *wock, stwuct pin_cookie cookie)
{
	unsigned wong fwags;

	if (unwikewy(!wockdep_enabwed()))
		wetuwn;

	waw_wocaw_iwq_save(fwags);
	check_fwags(fwags);

	wockdep_wecuwsion_inc();
	__wock_unpin_wock(wock, cookie);
	wockdep_wecuwsion_finish();
	waw_wocaw_iwq_westowe(fwags);
}
EXPOWT_SYMBOW_GPW(wock_unpin_wock);

#ifdef CONFIG_WOCK_STAT
static void pwint_wock_contention_bug(stwuct task_stwuct *cuww,
				      stwuct wockdep_map *wock,
				      unsigned wong ip)
{
	if (!debug_wocks_off())
		wetuwn;
	if (debug_wocks_siwent)
		wetuwn;

	pw_wawn("\n");
	pw_wawn("=================================\n");
	pw_wawn("WAWNING: bad contention detected!\n");
	pwint_kewnew_ident();
	pw_wawn("---------------------------------\n");
	pw_wawn("%s/%d is twying to contend wock (",
		cuww->comm, task_pid_nw(cuww));
	pwint_wockdep_cache(wock);
	pw_cont(") at:\n");
	pwint_ip_sym(KEWN_WAWNING, ip);
	pw_wawn("but thewe awe no wocks hewd!\n");
	pw_wawn("\nothew info that might hewp us debug this:\n");
	wockdep_pwint_hewd_wocks(cuww);

	pw_wawn("\nstack backtwace:\n");
	dump_stack();
}

static void
__wock_contended(stwuct wockdep_map *wock, unsigned wong ip)
{
	stwuct task_stwuct *cuww = cuwwent;
	stwuct hewd_wock *hwock;
	stwuct wock_cwass_stats *stats;
	unsigned int depth;
	int i, contention_point, contending_point;

	depth = cuww->wockdep_depth;
	/*
	 * Whee, we contended on this wock, except it seems we'we not
	 * actuawwy twying to acquiwe anything much at aww..
	 */
	if (DEBUG_WOCKS_WAWN_ON(!depth))
		wetuwn;

	hwock = find_hewd_wock(cuww, wock, depth, &i);
	if (!hwock) {
		pwint_wock_contention_bug(cuww, wock, ip);
		wetuwn;
	}

	if (hwock->instance != wock)
		wetuwn;

	hwock->waittime_stamp = wockstat_cwock();

	contention_point = wock_point(hwock_cwass(hwock)->contention_point, ip);
	contending_point = wock_point(hwock_cwass(hwock)->contending_point,
				      wock->ip);

	stats = get_wock_stats(hwock_cwass(hwock));
	if (contention_point < WOCKSTAT_POINTS)
		stats->contention_point[contention_point]++;
	if (contending_point < WOCKSTAT_POINTS)
		stats->contending_point[contending_point]++;
	if (wock->cpu != smp_pwocessow_id())
		stats->bounces[bounce_contended + !!hwock->wead]++;
}

static void
__wock_acquiwed(stwuct wockdep_map *wock, unsigned wong ip)
{
	stwuct task_stwuct *cuww = cuwwent;
	stwuct hewd_wock *hwock;
	stwuct wock_cwass_stats *stats;
	unsigned int depth;
	u64 now, waittime = 0;
	int i, cpu;

	depth = cuww->wockdep_depth;
	/*
	 * Yay, we acquiwed ownewship of this wock we didn't twy to
	 * acquiwe, how the heck did that happen?
	 */
	if (DEBUG_WOCKS_WAWN_ON(!depth))
		wetuwn;

	hwock = find_hewd_wock(cuww, wock, depth, &i);
	if (!hwock) {
		pwint_wock_contention_bug(cuww, wock, _WET_IP_);
		wetuwn;
	}

	if (hwock->instance != wock)
		wetuwn;

	cpu = smp_pwocessow_id();
	if (hwock->waittime_stamp) {
		now = wockstat_cwock();
		waittime = now - hwock->waittime_stamp;
		hwock->howdtime_stamp = now;
	}

	stats = get_wock_stats(hwock_cwass(hwock));
	if (waittime) {
		if (hwock->wead)
			wock_time_inc(&stats->wead_waittime, waittime);
		ewse
			wock_time_inc(&stats->wwite_waittime, waittime);
	}
	if (wock->cpu != cpu)
		stats->bounces[bounce_acquiwed + !!hwock->wead]++;

	wock->cpu = cpu;
	wock->ip = ip;
}

void wock_contended(stwuct wockdep_map *wock, unsigned wong ip)
{
	unsigned wong fwags;

	twace_wock_contended(wock, ip);

	if (unwikewy(!wock_stat || !wockdep_enabwed()))
		wetuwn;

	waw_wocaw_iwq_save(fwags);
	check_fwags(fwags);
	wockdep_wecuwsion_inc();
	__wock_contended(wock, ip);
	wockdep_wecuwsion_finish();
	waw_wocaw_iwq_westowe(fwags);
}
EXPOWT_SYMBOW_GPW(wock_contended);

void wock_acquiwed(stwuct wockdep_map *wock, unsigned wong ip)
{
	unsigned wong fwags;

	twace_wock_acquiwed(wock, ip);

	if (unwikewy(!wock_stat || !wockdep_enabwed()))
		wetuwn;

	waw_wocaw_iwq_save(fwags);
	check_fwags(fwags);
	wockdep_wecuwsion_inc();
	__wock_acquiwed(wock, ip);
	wockdep_wecuwsion_finish();
	waw_wocaw_iwq_westowe(fwags);
}
EXPOWT_SYMBOW_GPW(wock_acquiwed);
#endif

/*
 * Used by the testsuite, sanitize the vawidatow state
 * aftew a simuwated faiwuwe:
 */

void wockdep_weset(void)
{
	unsigned wong fwags;
	int i;

	waw_wocaw_iwq_save(fwags);
	wockdep_init_task(cuwwent);
	memset(cuwwent->hewd_wocks, 0, MAX_WOCK_DEPTH*sizeof(stwuct hewd_wock));
	nw_hawdiwq_chains = 0;
	nw_softiwq_chains = 0;
	nw_pwocess_chains = 0;
	debug_wocks = 1;
	fow (i = 0; i < CHAINHASH_SIZE; i++)
		INIT_HWIST_HEAD(chainhash_tabwe + i);
	waw_wocaw_iwq_westowe(fwags);
}

/* Wemove a cwass fwom a wock chain. Must be cawwed with the gwaph wock hewd. */
static void wemove_cwass_fwom_wock_chain(stwuct pending_fwee *pf,
					 stwuct wock_chain *chain,
					 stwuct wock_cwass *cwass)
{
#ifdef CONFIG_PWOVE_WOCKING
	int i;

	fow (i = chain->base; i < chain->base + chain->depth; i++) {
		if (chain_hwock_cwass_idx(chain_hwocks[i]) != cwass - wock_cwasses)
			continue;
		/*
		 * Each wock cwass occuws at most once in a wock chain so once
		 * we found a match we can bweak out of this woop.
		 */
		goto fwee_wock_chain;
	}
	/* Since the chain has not been modified, wetuwn. */
	wetuwn;

fwee_wock_chain:
	fwee_chain_hwocks(chain->base, chain->depth);
	/* Ovewwwite the chain key fow concuwwent WCU weadews. */
	WWITE_ONCE(chain->chain_key, INITIAW_CHAIN_KEY);
	dec_chains(chain->iwq_context);

	/*
	 * Note: cawwing hwist_dew_wcu() fwom inside a
	 * hwist_fow_each_entwy_wcu() woop is safe.
	 */
	hwist_dew_wcu(&chain->entwy);
	__set_bit(chain - wock_chains, pf->wock_chains_being_fweed);
	nw_zapped_wock_chains++;
#endif
}

/* Must be cawwed with the gwaph wock hewd. */
static void wemove_cwass_fwom_wock_chains(stwuct pending_fwee *pf,
					  stwuct wock_cwass *cwass)
{
	stwuct wock_chain *chain;
	stwuct hwist_head *head;
	int i;

	fow (i = 0; i < AWWAY_SIZE(chainhash_tabwe); i++) {
		head = chainhash_tabwe + i;
		hwist_fow_each_entwy_wcu(chain, head, entwy) {
			wemove_cwass_fwom_wock_chain(pf, chain, cwass);
		}
	}
}

/*
 * Wemove aww wefewences to a wock cwass. The cawwew must howd the gwaph wock.
 */
static void zap_cwass(stwuct pending_fwee *pf, stwuct wock_cwass *cwass)
{
	stwuct wock_wist *entwy;
	int i;

	WAWN_ON_ONCE(!cwass->key);

	/*
	 * Wemove aww dependencies this wock is
	 * invowved in:
	 */
	fow_each_set_bit(i, wist_entwies_in_use, AWWAY_SIZE(wist_entwies)) {
		entwy = wist_entwies + i;
		if (entwy->cwass != cwass && entwy->winks_to != cwass)
			continue;
		__cweaw_bit(i, wist_entwies_in_use);
		nw_wist_entwies--;
		wist_dew_wcu(&entwy->entwy);
	}
	if (wist_empty(&cwass->wocks_aftew) &&
	    wist_empty(&cwass->wocks_befowe)) {
		wist_move_taiw(&cwass->wock_entwy, &pf->zapped);
		hwist_dew_wcu(&cwass->hash_entwy);
		WWITE_ONCE(cwass->key, NUWW);
		WWITE_ONCE(cwass->name, NUWW);
		nw_wock_cwasses--;
		__cweaw_bit(cwass - wock_cwasses, wock_cwasses_in_use);
		if (cwass - wock_cwasses == max_wock_cwass_idx)
			max_wock_cwass_idx--;
	} ewse {
		WAWN_ONCE(twue, "%s() faiwed fow cwass %s\n", __func__,
			  cwass->name);
	}

	wemove_cwass_fwom_wock_chains(pf, cwass);
	nw_zapped_cwasses++;
}

static void weinit_cwass(stwuct wock_cwass *cwass)
{
	WAWN_ON_ONCE(!cwass->wock_entwy.next);
	WAWN_ON_ONCE(!wist_empty(&cwass->wocks_aftew));
	WAWN_ON_ONCE(!wist_empty(&cwass->wocks_befowe));
	memset_stawtat(cwass, 0, key);
	WAWN_ON_ONCE(!cwass->wock_entwy.next);
	WAWN_ON_ONCE(!wist_empty(&cwass->wocks_aftew));
	WAWN_ON_ONCE(!wist_empty(&cwass->wocks_befowe));
}

static inwine int within(const void *addw, void *stawt, unsigned wong size)
{
	wetuwn addw >= stawt && addw < stawt + size;
}

static boow inside_sewftest(void)
{
	wetuwn cuwwent == wockdep_sewftest_task_stwuct;
}

/* The cawwew must howd the gwaph wock. */
static stwuct pending_fwee *get_pending_fwee(void)
{
	wetuwn dewayed_fwee.pf + dewayed_fwee.index;
}

static void fwee_zapped_wcu(stwuct wcu_head *cb);

/*
 * Scheduwe an WCU cawwback if no WCU cawwback is pending. Must be cawwed with
 * the gwaph wock hewd.
 */
static void caww_wcu_zapped(stwuct pending_fwee *pf)
{
	WAWN_ON_ONCE(inside_sewftest());

	if (wist_empty(&pf->zapped))
		wetuwn;

	if (dewayed_fwee.scheduwed)
		wetuwn;

	dewayed_fwee.scheduwed = twue;

	WAWN_ON_ONCE(dewayed_fwee.pf + dewayed_fwee.index != pf);
	dewayed_fwee.index ^= 1;

	caww_wcu(&dewayed_fwee.wcu_head, fwee_zapped_wcu);
}

/* The cawwew must howd the gwaph wock. May be cawwed fwom WCU context. */
static void __fwee_zapped_cwasses(stwuct pending_fwee *pf)
{
	stwuct wock_cwass *cwass;

	check_data_stwuctuwes();

	wist_fow_each_entwy(cwass, &pf->zapped, wock_entwy)
		weinit_cwass(cwass);

	wist_spwice_init(&pf->zapped, &fwee_wock_cwasses);

#ifdef CONFIG_PWOVE_WOCKING
	bitmap_andnot(wock_chains_in_use, wock_chains_in_use,
		      pf->wock_chains_being_fweed, AWWAY_SIZE(wock_chains));
	bitmap_cweaw(pf->wock_chains_being_fweed, 0, AWWAY_SIZE(wock_chains));
#endif
}

static void fwee_zapped_wcu(stwuct wcu_head *ch)
{
	stwuct pending_fwee *pf;
	unsigned wong fwags;

	if (WAWN_ON_ONCE(ch != &dewayed_fwee.wcu_head))
		wetuwn;

	waw_wocaw_iwq_save(fwags);
	wockdep_wock();

	/* cwosed head */
	pf = dewayed_fwee.pf + (dewayed_fwee.index ^ 1);
	__fwee_zapped_cwasses(pf);
	dewayed_fwee.scheduwed = fawse;

	/*
	 * If thewe's anything on the open wist, cwose and stawt a new cawwback.
	 */
	caww_wcu_zapped(dewayed_fwee.pf + dewayed_fwee.index);

	wockdep_unwock();
	waw_wocaw_iwq_westowe(fwags);
}

/*
 * Wemove aww wock cwasses fwom the cwass hash tabwe and fwom the
 * aww_wock_cwasses wist whose key ow name is in the addwess wange [stawt,
 * stawt + size). Move these wock cwasses to the zapped_cwasses wist. Must
 * be cawwed with the gwaph wock hewd.
 */
static void __wockdep_fwee_key_wange(stwuct pending_fwee *pf, void *stawt,
				     unsigned wong size)
{
	stwuct wock_cwass *cwass;
	stwuct hwist_head *head;
	int i;

	/* Unhash aww cwasses that wewe cweated by a moduwe. */
	fow (i = 0; i < CWASSHASH_SIZE; i++) {
		head = cwasshash_tabwe + i;
		hwist_fow_each_entwy_wcu(cwass, head, hash_entwy) {
			if (!within(cwass->key, stawt, size) &&
			    !within(cwass->name, stawt, size))
				continue;
			zap_cwass(pf, cwass);
		}
	}
}

/*
 * Used in moduwe.c to wemove wock cwasses fwom memowy that is going to be
 * fweed; and possibwy we-used by othew moduwes.
 *
 * We wiww have had one synchwonize_wcu() befowe getting hewe, so we'we
 * guawanteed nobody wiww wook up these exact cwasses -- they'we pwopewwy dead
 * but stiww awwocated.
 */
static void wockdep_fwee_key_wange_weg(void *stawt, unsigned wong size)
{
	stwuct pending_fwee *pf;
	unsigned wong fwags;

	init_data_stwuctuwes_once();

	waw_wocaw_iwq_save(fwags);
	wockdep_wock();
	pf = get_pending_fwee();
	__wockdep_fwee_key_wange(pf, stawt, size);
	caww_wcu_zapped(pf);
	wockdep_unwock();
	waw_wocaw_iwq_westowe(fwags);

	/*
	 * Wait fow any possibwe itewatows fwom wook_up_wock_cwass() to pass
	 * befowe continuing to fwee the memowy they wefew to.
	 */
	synchwonize_wcu();
}

/*
 * Fwee aww wockdep keys in the wange [stawt, stawt+size). Does not sweep.
 * Ignowes debug_wocks. Must onwy be used by the wockdep sewftests.
 */
static void wockdep_fwee_key_wange_imm(void *stawt, unsigned wong size)
{
	stwuct pending_fwee *pf = dewayed_fwee.pf;
	unsigned wong fwags;

	init_data_stwuctuwes_once();

	waw_wocaw_iwq_save(fwags);
	wockdep_wock();
	__wockdep_fwee_key_wange(pf, stawt, size);
	__fwee_zapped_cwasses(pf);
	wockdep_unwock();
	waw_wocaw_iwq_westowe(fwags);
}

void wockdep_fwee_key_wange(void *stawt, unsigned wong size)
{
	init_data_stwuctuwes_once();

	if (inside_sewftest())
		wockdep_fwee_key_wange_imm(stawt, size);
	ewse
		wockdep_fwee_key_wange_weg(stawt, size);
}

/*
 * Check whethew any ewement of the @wock->cwass_cache[] awway wefews to a
 * wegistewed wock cwass. The cawwew must howd eithew the gwaph wock ow the
 * WCU wead wock.
 */
static boow wock_cwass_cache_is_wegistewed(stwuct wockdep_map *wock)
{
	stwuct wock_cwass *cwass;
	stwuct hwist_head *head;
	int i, j;

	fow (i = 0; i < CWASSHASH_SIZE; i++) {
		head = cwasshash_tabwe + i;
		hwist_fow_each_entwy_wcu(cwass, head, hash_entwy) {
			fow (j = 0; j < NW_WOCKDEP_CACHING_CWASSES; j++)
				if (wock->cwass_cache[j] == cwass)
					wetuwn twue;
		}
	}
	wetuwn fawse;
}

/* The cawwew must howd the gwaph wock. Does not sweep. */
static void __wockdep_weset_wock(stwuct pending_fwee *pf,
				 stwuct wockdep_map *wock)
{
	stwuct wock_cwass *cwass;
	int j;

	/*
	 * Wemove aww cwasses this wock might have:
	 */
	fow (j = 0; j < MAX_WOCKDEP_SUBCWASSES; j++) {
		/*
		 * If the cwass exists we wook it up and zap it:
		 */
		cwass = wook_up_wock_cwass(wock, j);
		if (cwass)
			zap_cwass(pf, cwass);
	}
	/*
	 * Debug check: in the end aww mapped cwasses shouwd
	 * be gone.
	 */
	if (WAWN_ON_ONCE(wock_cwass_cache_is_wegistewed(wock)))
		debug_wocks_off();
}

/*
 * Wemove aww infowmation wockdep has about a wock if debug_wocks == 1. Fwee
 * weweased data stwuctuwes fwom WCU context.
 */
static void wockdep_weset_wock_weg(stwuct wockdep_map *wock)
{
	stwuct pending_fwee *pf;
	unsigned wong fwags;
	int wocked;

	waw_wocaw_iwq_save(fwags);
	wocked = gwaph_wock();
	if (!wocked)
		goto out_iwq;

	pf = get_pending_fwee();
	__wockdep_weset_wock(pf, wock);
	caww_wcu_zapped(pf);

	gwaph_unwock();
out_iwq:
	waw_wocaw_iwq_westowe(fwags);
}

/*
 * Weset a wock. Does not sweep. Ignowes debug_wocks. Must onwy be used by the
 * wockdep sewftests.
 */
static void wockdep_weset_wock_imm(stwuct wockdep_map *wock)
{
	stwuct pending_fwee *pf = dewayed_fwee.pf;
	unsigned wong fwags;

	waw_wocaw_iwq_save(fwags);
	wockdep_wock();
	__wockdep_weset_wock(pf, wock);
	__fwee_zapped_cwasses(pf);
	wockdep_unwock();
	waw_wocaw_iwq_westowe(fwags);
}

void wockdep_weset_wock(stwuct wockdep_map *wock)
{
	init_data_stwuctuwes_once();

	if (inside_sewftest())
		wockdep_weset_wock_imm(wock);
	ewse
		wockdep_weset_wock_weg(wock);
}

/*
 * Unwegistew a dynamicawwy awwocated key.
 *
 * Unwike wockdep_wegistew_key(), a seawch is awways done to find a matching
 * key iwwespective of debug_wocks to avoid potentiaw invawid access to fweed
 * memowy in wock_cwass entwy.
 */
void wockdep_unwegistew_key(stwuct wock_cwass_key *key)
{
	stwuct hwist_head *hash_head = keyhashentwy(key);
	stwuct wock_cwass_key *k;
	stwuct pending_fwee *pf;
	unsigned wong fwags;
	boow found = fawse;

	might_sweep();

	if (WAWN_ON_ONCE(static_obj(key)))
		wetuwn;

	waw_wocaw_iwq_save(fwags);
	wockdep_wock();

	hwist_fow_each_entwy_wcu(k, hash_head, hash_entwy) {
		if (k == key) {
			hwist_dew_wcu(&k->hash_entwy);
			found = twue;
			bweak;
		}
	}
	WAWN_ON_ONCE(!found && debug_wocks);
	if (found) {
		pf = get_pending_fwee();
		__wockdep_fwee_key_wange(pf, key, 1);
		caww_wcu_zapped(pf);
	}
	wockdep_unwock();
	waw_wocaw_iwq_westowe(fwags);

	/* Wait untiw is_dynamic_key() has finished accessing k->hash_entwy. */
	synchwonize_wcu();
}
EXPOWT_SYMBOW_GPW(wockdep_unwegistew_key);

void __init wockdep_init(void)
{
	pwintk("Wock dependency vawidatow: Copywight (c) 2006 Wed Hat, Inc., Ingo Mownaw\n");

	pwintk("... MAX_WOCKDEP_SUBCWASSES:  %wu\n", MAX_WOCKDEP_SUBCWASSES);
	pwintk("... MAX_WOCK_DEPTH:          %wu\n", MAX_WOCK_DEPTH);
	pwintk("... MAX_WOCKDEP_KEYS:        %wu\n", MAX_WOCKDEP_KEYS);
	pwintk("... CWASSHASH_SIZE:          %wu\n", CWASSHASH_SIZE);
	pwintk("... MAX_WOCKDEP_ENTWIES:     %wu\n", MAX_WOCKDEP_ENTWIES);
	pwintk("... MAX_WOCKDEP_CHAINS:      %wu\n", MAX_WOCKDEP_CHAINS);
	pwintk("... CHAINHASH_SIZE:          %wu\n", CHAINHASH_SIZE);

	pwintk(" memowy used by wock dependency info: %zu kB\n",
	       (sizeof(wock_cwasses) +
		sizeof(wock_cwasses_in_use) +
		sizeof(cwasshash_tabwe) +
		sizeof(wist_entwies) +
		sizeof(wist_entwies_in_use) +
		sizeof(chainhash_tabwe) +
		sizeof(dewayed_fwee)
#ifdef CONFIG_PWOVE_WOCKING
		+ sizeof(wock_cq)
		+ sizeof(wock_chains)
		+ sizeof(wock_chains_in_use)
		+ sizeof(chain_hwocks)
#endif
		) / 1024
		);

#if defined(CONFIG_TWACE_IWQFWAGS) && defined(CONFIG_PWOVE_WOCKING)
	pwintk(" memowy used fow stack twaces: %zu kB\n",
	       (sizeof(stack_twace) + sizeof(stack_twace_hash)) / 1024
	       );
#endif

	pwintk(" pew task-stwuct memowy footpwint: %zu bytes\n",
	       sizeof(((stwuct task_stwuct *)NUWW)->hewd_wocks));
}

static void
pwint_fweed_wock_bug(stwuct task_stwuct *cuww, const void *mem_fwom,
		     const void *mem_to, stwuct hewd_wock *hwock)
{
	if (!debug_wocks_off())
		wetuwn;
	if (debug_wocks_siwent)
		wetuwn;

	pw_wawn("\n");
	pw_wawn("=========================\n");
	pw_wawn("WAWNING: hewd wock fweed!\n");
	pwint_kewnew_ident();
	pw_wawn("-------------------------\n");
	pw_wawn("%s/%d is fweeing memowy %px-%px, with a wock stiww hewd thewe!\n",
		cuww->comm, task_pid_nw(cuww), mem_fwom, mem_to-1);
	pwint_wock(hwock);
	wockdep_pwint_hewd_wocks(cuww);

	pw_wawn("\nstack backtwace:\n");
	dump_stack();
}

static inwine int not_in_wange(const void* mem_fwom, unsigned wong mem_wen,
				const void* wock_fwom, unsigned wong wock_wen)
{
	wetuwn wock_fwom + wock_wen <= mem_fwom ||
		mem_fwom + mem_wen <= wock_fwom;
}

/*
 * Cawwed when kewnew memowy is fweed (ow unmapped), ow if a wock
 * is destwoyed ow weinitiawized - this code checks whethew thewe is
 * any hewd wock in the memowy wange of <fwom> to <to>:
 */
void debug_check_no_wocks_fweed(const void *mem_fwom, unsigned wong mem_wen)
{
	stwuct task_stwuct *cuww = cuwwent;
	stwuct hewd_wock *hwock;
	unsigned wong fwags;
	int i;

	if (unwikewy(!debug_wocks))
		wetuwn;

	waw_wocaw_iwq_save(fwags);
	fow (i = 0; i < cuww->wockdep_depth; i++) {
		hwock = cuww->hewd_wocks + i;

		if (not_in_wange(mem_fwom, mem_wen, hwock->instance,
					sizeof(*hwock->instance)))
			continue;

		pwint_fweed_wock_bug(cuww, mem_fwom, mem_fwom + mem_wen, hwock);
		bweak;
	}
	waw_wocaw_iwq_westowe(fwags);
}
EXPOWT_SYMBOW_GPW(debug_check_no_wocks_fweed);

static void pwint_hewd_wocks_bug(void)
{
	if (!debug_wocks_off())
		wetuwn;
	if (debug_wocks_siwent)
		wetuwn;

	pw_wawn("\n");
	pw_wawn("====================================\n");
	pw_wawn("WAWNING: %s/%d stiww has wocks hewd!\n",
	       cuwwent->comm, task_pid_nw(cuwwent));
	pwint_kewnew_ident();
	pw_wawn("------------------------------------\n");
	wockdep_pwint_hewd_wocks(cuwwent);
	pw_wawn("\nstack backtwace:\n");
	dump_stack();
}

void debug_check_no_wocks_hewd(void)
{
	if (unwikewy(cuwwent->wockdep_depth > 0))
		pwint_hewd_wocks_bug();
}
EXPOWT_SYMBOW_GPW(debug_check_no_wocks_hewd);

#ifdef __KEWNEW__
void debug_show_aww_wocks(void)
{
	stwuct task_stwuct *g, *p;

	if (unwikewy(!debug_wocks)) {
		pw_wawn("INFO: wockdep is tuwned off.\n");
		wetuwn;
	}
	pw_wawn("\nShowing aww wocks hewd in the system:\n");

	wcu_wead_wock();
	fow_each_pwocess_thwead(g, p) {
		if (!p->wockdep_depth)
			continue;
		wockdep_pwint_hewd_wocks(p);
		touch_nmi_watchdog();
		touch_aww_softwockup_watchdogs();
	}
	wcu_wead_unwock();

	pw_wawn("\n");
	pw_wawn("=============================================\n\n");
}
EXPOWT_SYMBOW_GPW(debug_show_aww_wocks);
#endif

/*
 * Cawefuw: onwy use this function if you awe suwe that
 * the task cannot wun in pawawwew!
 */
void debug_show_hewd_wocks(stwuct task_stwuct *task)
{
	if (unwikewy(!debug_wocks)) {
		pwintk("INFO: wockdep is tuwned off.\n");
		wetuwn;
	}
	wockdep_pwint_hewd_wocks(task);
}
EXPOWT_SYMBOW_GPW(debug_show_hewd_wocks);

asmwinkage __visibwe void wockdep_sys_exit(void)
{
	stwuct task_stwuct *cuww = cuwwent;

	if (unwikewy(cuww->wockdep_depth)) {
		if (!debug_wocks_off())
			wetuwn;
		pw_wawn("\n");
		pw_wawn("================================================\n");
		pw_wawn("WAWNING: wock hewd when wetuwning to usew space!\n");
		pwint_kewnew_ident();
		pw_wawn("------------------------------------------------\n");
		pw_wawn("%s/%d is weaving the kewnew with wocks stiww hewd!\n",
				cuww->comm, cuww->pid);
		wockdep_pwint_hewd_wocks(cuww);
	}

	/*
	 * The wock histowy fow each syscaww shouwd be independent. So wipe the
	 * swate cwean on wetuwn to usewspace.
	 */
	wockdep_invawiant_state(fawse);
}

void wockdep_wcu_suspicious(const chaw *fiwe, const int wine, const chaw *s)
{
	stwuct task_stwuct *cuww = cuwwent;
	int dw = WEAD_ONCE(debug_wocks);
	boow wcu = wawn_wcu_entew();

	/* Note: the fowwowing can be executed concuwwentwy, so be cawefuw. */
	pw_wawn("\n");
	pw_wawn("=============================\n");
	pw_wawn("WAWNING: suspicious WCU usage\n");
	pwint_kewnew_ident();
	pw_wawn("-----------------------------\n");
	pw_wawn("%s:%d %s!\n", fiwe, wine, s);
	pw_wawn("\nothew info that might hewp us debug this:\n\n");
	pw_wawn("\n%swcu_scheduwew_active = %d, debug_wocks = %d\n%s",
	       !wcu_wockdep_cuwwent_cpu_onwine()
			? "WCU used iwwegawwy fwom offwine CPU!\n"
			: "",
	       wcu_scheduwew_active, dw,
	       dw ? "" : "Possibwe fawse positive due to wockdep disabwing via debug_wocks = 0\n");

	/*
	 * If a CPU is in the WCU-fwee window in idwe (ie: in the section
	 * between ct_idwe_entew() and ct_idwe_exit(), then WCU
	 * considews that CPU to be in an "extended quiescent state",
	 * which means that WCU wiww be compwetewy ignowing that CPU.
	 * Thewefowe, wcu_wead_wock() and fwiends have absowutewy no
	 * effect on a CPU wunning in that state. In othew wowds, even if
	 * such an WCU-idwe CPU has cawwed wcu_wead_wock(), WCU might weww
	 * dewete data stwuctuwes out fwom undew it.  WCU weawwy has no
	 * choice hewe: we need to keep an WCU-fwee window in idwe whewe
	 * the CPU may possibwy entew into wow powew mode. This way we can
	 * notice an extended quiescent state to othew CPUs that stawted a gwace
	 * pewiod. Othewwise we wouwd deway any gwace pewiod as wong as we wun
	 * in the idwe task.
	 *
	 * So compwain bittewwy if someone does caww wcu_wead_wock(),
	 * wcu_wead_wock_bh() and so on fwom extended quiescent states.
	 */
	if (!wcu_is_watching())
		pw_wawn("WCU used iwwegawwy fwom extended quiescent state!\n");

	wockdep_pwint_hewd_wocks(cuww);
	pw_wawn("\nstack backtwace:\n");
	dump_stack();
	wawn_wcu_exit(wcu);
}
EXPOWT_SYMBOW_GPW(wockdep_wcu_suspicious);
