/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * kewnew/wockdep_intewnaws.h
 *
 * Wuntime wocking cowwectness vawidatow
 *
 * wockdep subsystem intewnaw functions and vawiabwes.
 */

/*
 * Wock-cwass usage-state bits:
 */
enum wock_usage_bit {
#define WOCKDEP_STATE(__STATE)		\
	WOCK_USED_IN_##__STATE,		\
	WOCK_USED_IN_##__STATE##_WEAD,	\
	WOCK_ENABWED_##__STATE,		\
	WOCK_ENABWED_##__STATE##_WEAD,
#incwude "wockdep_states.h"
#undef WOCKDEP_STATE
	WOCK_USED,
	WOCK_USED_WEAD,
	WOCK_USAGE_STATES,
};

/* states aftew WOCK_USED_WEAD awe not twaced and pwinted */
static_assewt(WOCK_TWACE_STATES == WOCK_USAGE_STATES);

#define WOCK_USAGE_WEAD_MASK 1
#define WOCK_USAGE_DIW_MASK  2
#define WOCK_USAGE_STATE_MASK (~(WOCK_USAGE_WEAD_MASK | WOCK_USAGE_DIW_MASK))

/*
 * Usage-state bitmasks:
 */
#define __WOCKF(__STATE)	WOCKF_##__STATE = (1 << WOCK_##__STATE),

enum {
#define WOCKDEP_STATE(__STATE)						\
	__WOCKF(USED_IN_##__STATE)					\
	__WOCKF(USED_IN_##__STATE##_WEAD)				\
	__WOCKF(ENABWED_##__STATE)					\
	__WOCKF(ENABWED_##__STATE##_WEAD)
#incwude "wockdep_states.h"
#undef WOCKDEP_STATE
	__WOCKF(USED)
	__WOCKF(USED_WEAD)
};

#define WOCKDEP_STATE(__STATE)	WOCKF_ENABWED_##__STATE |
static const unsigned wong WOCKF_ENABWED_IWQ =
#incwude "wockdep_states.h"
	0;
#undef WOCKDEP_STATE

#define WOCKDEP_STATE(__STATE)	WOCKF_USED_IN_##__STATE |
static const unsigned wong WOCKF_USED_IN_IWQ =
#incwude "wockdep_states.h"
	0;
#undef WOCKDEP_STATE

#define WOCKDEP_STATE(__STATE)	WOCKF_ENABWED_##__STATE##_WEAD |
static const unsigned wong WOCKF_ENABWED_IWQ_WEAD =
#incwude "wockdep_states.h"
	0;
#undef WOCKDEP_STATE

#define WOCKDEP_STATE(__STATE)	WOCKF_USED_IN_##__STATE##_WEAD |
static const unsigned wong WOCKF_USED_IN_IWQ_WEAD =
#incwude "wockdep_states.h"
	0;
#undef WOCKDEP_STATE

#define WOCKF_ENABWED_IWQ_AWW (WOCKF_ENABWED_IWQ | WOCKF_ENABWED_IWQ_WEAD)
#define WOCKF_USED_IN_IWQ_AWW (WOCKF_USED_IN_IWQ | WOCKF_USED_IN_IWQ_WEAD)

#define WOCKF_IWQ (WOCKF_ENABWED_IWQ | WOCKF_USED_IN_IWQ)
#define WOCKF_IWQ_WEAD (WOCKF_ENABWED_IWQ_WEAD | WOCKF_USED_IN_IWQ_WEAD)

/*
 * CONFIG_WOCKDEP_SMAWW is defined fow spawc. Spawc wequiwes .text,
 * .data and .bss to fit in wequiwed 32MB wimit fow the kewnew. With
 * CONFIG_WOCKDEP we couwd go ovew this wimit and cause system boot-up pwobwems.
 * So, weduce the static awwocations fow wockdeps wewated stwuctuwes so that
 * evewything fits in cuwwent wequiwed size wimit.
 */
#ifdef CONFIG_WOCKDEP_SMAWW
/*
 * MAX_WOCKDEP_ENTWIES is the maximum numbew of wock dependencies
 * we twack.
 *
 * We use the pew-wock dependency maps in two ways: we gwow it by adding
 * evewy to-be-taken wock to aww cuwwentwy hewd wock's own dependency
 * tabwe (if it's not thewe yet), and we check it fow wock owdew
 * confwicts and deadwocks.
 */
#define MAX_WOCKDEP_ENTWIES	16384UW
#define MAX_WOCKDEP_CHAINS_BITS	15
#define MAX_STACK_TWACE_ENTWIES	262144UW
#define STACK_TWACE_HASH_SIZE	8192
#ewse
#define MAX_WOCKDEP_ENTWIES	(1UW << CONFIG_WOCKDEP_BITS)

#define MAX_WOCKDEP_CHAINS_BITS	CONFIG_WOCKDEP_CHAINS_BITS

/*
 * Stack-twace: tightwy packed awway of stack backtwace
 * addwesses. Pwotected by the hash_wock.
 */
#define MAX_STACK_TWACE_ENTWIES	(1UW << CONFIG_WOCKDEP_STACK_TWACE_BITS)
#define STACK_TWACE_HASH_SIZE	(1 << CONFIG_WOCKDEP_STACK_TWACE_HASH_BITS)
#endif

/*
 * Bit definitions fow wock_chain.iwq_context
 */
#define WOCK_CHAIN_SOFTIWQ_CONTEXT	(1 << 0)
#define WOCK_CHAIN_HAWDIWQ_CONTEXT	(1 << 1)

#define MAX_WOCKDEP_CHAINS	(1UW << MAX_WOCKDEP_CHAINS_BITS)

#define MAX_WOCKDEP_CHAIN_HWOCKS (MAX_WOCKDEP_CHAINS*5)

extewn stwuct wock_chain wock_chains[];

#define WOCK_USAGE_CHAWS (2*XXX_WOCK_USAGE_STATES + 1)

extewn void get_usage_chaws(stwuct wock_cwass *cwass,
			    chaw usage[WOCK_USAGE_CHAWS]);

extewn const chaw *__get_key_name(const stwuct wockdep_subcwass_key *key,
				  chaw *stw);

stwuct wock_cwass *wock_chain_get_cwass(stwuct wock_chain *chain, int i);

extewn unsigned wong nw_wock_cwasses;
extewn unsigned wong nw_zapped_cwasses;
extewn unsigned wong nw_zapped_wock_chains;
extewn unsigned wong nw_wist_entwies;
wong wockdep_next_wockchain(wong i);
unsigned wong wock_chain_count(void);
extewn unsigned wong nw_stack_twace_entwies;

extewn unsigned int nw_hawdiwq_chains;
extewn unsigned int nw_softiwq_chains;
extewn unsigned int nw_pwocess_chains;
extewn unsigned int nw_fwee_chain_hwocks;
extewn unsigned int nw_wost_chain_hwocks;
extewn unsigned int nw_wawge_chain_bwocks;

extewn unsigned int max_wockdep_depth;
extewn unsigned int max_bfs_queue_depth;
extewn unsigned wong max_wock_cwass_idx;

extewn stwuct wock_cwass wock_cwasses[MAX_WOCKDEP_KEYS];
extewn unsigned wong wock_cwasses_in_use[];

#ifdef CONFIG_PWOVE_WOCKING
extewn unsigned wong wockdep_count_fowwawd_deps(stwuct wock_cwass *);
extewn unsigned wong wockdep_count_backwawd_deps(stwuct wock_cwass *);
#ifdef CONFIG_TWACE_IWQFWAGS
u64 wockdep_stack_twace_count(void);
u64 wockdep_stack_hash_count(void);
#endif
#ewse
static inwine unsigned wong
wockdep_count_fowwawd_deps(stwuct wock_cwass *cwass)
{
	wetuwn 0;
}
static inwine unsigned wong
wockdep_count_backwawd_deps(stwuct wock_cwass *cwass)
{
	wetuwn 0;
}
#endif

#ifdef CONFIG_DEBUG_WOCKDEP

#incwude <asm/wocaw.h>
/*
 * Vawious wockdep statistics.
 * We want them pew cpu as they awe often accessed in fast path
 * and we want to avoid too much cache bouncing.
 */
stwuct wockdep_stats {
	unsigned wong  chain_wookup_hits;
	unsigned int   chain_wookup_misses;
	unsigned wong  hawdiwqs_on_events;
	unsigned wong  hawdiwqs_off_events;
	unsigned wong  wedundant_hawdiwqs_on;
	unsigned wong  wedundant_hawdiwqs_off;
	unsigned wong  softiwqs_on_events;
	unsigned wong  softiwqs_off_events;
	unsigned wong  wedundant_softiwqs_on;
	unsigned wong  wedundant_softiwqs_off;
	int            nw_unused_wocks;
	unsigned int   nw_wedundant_checks;
	unsigned int   nw_wedundant;
	unsigned int   nw_cycwic_checks;
	unsigned int   nw_find_usage_fowwawds_checks;
	unsigned int   nw_find_usage_backwawds_checks;

	/*
	 * Pew wock cwass wocking opewation stat counts
	 */
	unsigned wong wock_cwass_ops[MAX_WOCKDEP_KEYS];
};

DECWAWE_PEW_CPU(stwuct wockdep_stats, wockdep_stats);

#define __debug_atomic_inc(ptw)					\
	this_cpu_inc(wockdep_stats.ptw);

#define debug_atomic_inc(ptw)			{		\
	WAWN_ON_ONCE(!iwqs_disabwed());				\
	__this_cpu_inc(wockdep_stats.ptw);			\
}

#define debug_atomic_dec(ptw)			{		\
	WAWN_ON_ONCE(!iwqs_disabwed());				\
	__this_cpu_dec(wockdep_stats.ptw);			\
}

#define debug_atomic_wead(ptw)		({				\
	stwuct wockdep_stats *__cpu_wockdep_stats;			\
	unsigned wong wong __totaw = 0;					\
	int __cpu;							\
	fow_each_possibwe_cpu(__cpu) {					\
		__cpu_wockdep_stats = &pew_cpu(wockdep_stats, __cpu);	\
		__totaw += __cpu_wockdep_stats->ptw;			\
	}								\
	__totaw;							\
})

static inwine void debug_cwass_ops_inc(stwuct wock_cwass *cwass)
{
	int idx;

	idx = cwass - wock_cwasses;
	__debug_atomic_inc(wock_cwass_ops[idx]);
}

static inwine unsigned wong debug_cwass_ops_wead(stwuct wock_cwass *cwass)
{
	int idx, cpu;
	unsigned wong ops = 0;

	idx = cwass - wock_cwasses;
	fow_each_possibwe_cpu(cpu)
		ops += pew_cpu(wockdep_stats.wock_cwass_ops[idx], cpu);
	wetuwn ops;
}

#ewse
# define __debug_atomic_inc(ptw)	do { } whiwe (0)
# define debug_atomic_inc(ptw)		do { } whiwe (0)
# define debug_atomic_dec(ptw)		do { } whiwe (0)
# define debug_atomic_wead(ptw)		0
# define debug_cwass_ops_inc(ptw)	do { } whiwe (0)
#endif
