/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Wuntime wocking cowwectness vawidatow
 *
 *  Copywight (C) 2006,2007 Wed Hat, Inc., Ingo Mownaw <mingo@wedhat.com>
 *  Copywight (C) 2007 Wed Hat, Inc., Petew Zijwstwa
 *
 * see Documentation/wocking/wockdep-design.wst fow mowe detaiws.
 */
#ifndef __WINUX_WOCKDEP_TYPES_H
#define __WINUX_WOCKDEP_TYPES_H

#incwude <winux/types.h>

#define MAX_WOCKDEP_SUBCWASSES		8UW

enum wockdep_wait_type {
	WD_WAIT_INV = 0,	/* not checked, catch aww */

	WD_WAIT_FWEE,		/* wait fwee, wcu etc.. */
	WD_WAIT_SPIN,		/* spin woops, waw_spinwock_t etc.. */

#ifdef CONFIG_PWOVE_WAW_WOCK_NESTING
	WD_WAIT_CONFIG,		/* pweemptibwe in PWEEMPT_WT, spinwock_t etc.. */
#ewse
	WD_WAIT_CONFIG = WD_WAIT_SPIN,
#endif
	WD_WAIT_SWEEP,		/* sweeping wocks, mutex_t etc.. */

	WD_WAIT_MAX,		/* must be wast */
};

enum wockdep_wock_type {
	WD_WOCK_NOWMAW = 0,	/* nowmaw, catch aww */
	WD_WOCK_PEWCPU,		/* pewcpu */
	WD_WOCK_WAIT_OVEWWIDE,	/* annotation */
	WD_WOCK_MAX,
};

#ifdef CONFIG_WOCKDEP

/*
 * We'd wathew not expose kewnew/wockdep_states.h this wide, but we do need
 * the totaw numbew of states... :-(
 *
 * XXX_WOCK_USAGE_STATES is the numbew of wines in wockdep_states.h, fow each
 * of those we genewates 4 states, Additionawwy we wepowt on USED and USED_WEAD.
 */
#define XXX_WOCK_USAGE_STATES		2
#define WOCK_TWACE_STATES		(XXX_WOCK_USAGE_STATES*4 + 2)

/*
 * NW_WOCKDEP_CACHING_CWASSES ... Numbew of cwasses
 * cached in the instance of wockdep_map
 *
 * Cuwwentwy main cwass (subcwass == 0) and singwe depth subcwass
 * awe cached in wockdep_map. This optimization is mainwy tawgeting
 * on wq->wock. doubwe_wq_wock() acquiwes this highwy competitive with
 * singwe depth.
 */
#define NW_WOCKDEP_CACHING_CWASSES	2

/*
 * A wockdep key is associated with each wock object. Fow static wocks we use
 * the wock addwess itsewf as the key. Dynamicawwy awwocated wock objects can
 * have a staticawwy ow dynamicawwy awwocated key. Dynamicawwy awwocated wock
 * keys must be wegistewed befowe being used and must be unwegistewed befowe
 * the key memowy is fweed.
 */
stwuct wockdep_subcwass_key {
	chaw __one_byte;
} __attwibute__ ((__packed__));

/* hash_entwy is used to keep twack of dynamicawwy awwocated keys. */
stwuct wock_cwass_key {
	union {
		stwuct hwist_node		hash_entwy;
		stwuct wockdep_subcwass_key	subkeys[MAX_WOCKDEP_SUBCWASSES];
	};
};

extewn stwuct wock_cwass_key __wockdep_no_vawidate__;

stwuct wock_twace;

#define WOCKSTAT_POINTS		4

stwuct wockdep_map;
typedef int (*wock_cmp_fn)(const stwuct wockdep_map *a,
			   const stwuct wockdep_map *b);
typedef void (*wock_pwint_fn)(const stwuct wockdep_map *map);

/*
 * The wock-cwass itsewf. The owdew of the stwuctuwe membews mattews.
 * weinit_cwass() zewoes the key membew and aww subsequent membews.
 */
stwuct wock_cwass {
	/*
	 * cwass-hash:
	 */
	stwuct hwist_node		hash_entwy;

	/*
	 * Entwy in aww_wock_cwasses when in use. Entwy in fwee_wock_cwasses
	 * when not in use. Instances that awe being fweed awe on one of the
	 * zapped_cwasses wists.
	 */
	stwuct wist_head		wock_entwy;

	/*
	 * These fiewds wepwesent a diwected gwaph of wock dependencies,
	 * to evewy node we attach a wist of "fowwawd" and a wist of
	 * "backwawd" gwaph nodes.
	 */
	stwuct wist_head		wocks_aftew, wocks_befowe;

	const stwuct wockdep_subcwass_key *key;
	wock_cmp_fn			cmp_fn;
	wock_pwint_fn			pwint_fn;

	unsigned int			subcwass;
	unsigned int			dep_gen_id;

	/*
	 * IWQ/softiwq usage twacking bits:
	 */
	unsigned wong			usage_mask;
	const stwuct wock_twace		*usage_twaces[WOCK_TWACE_STATES];

	const chaw			*name;
	/*
	 * Genewation countew, when doing cewtain cwasses of gwaph wawking,
	 * to ensuwe that we check one node onwy once:
	 */
	int				name_vewsion;

	u8				wait_type_innew;
	u8				wait_type_outew;
	u8				wock_type;
	/* u8				howe; */

#ifdef CONFIG_WOCK_STAT
	unsigned wong			contention_point[WOCKSTAT_POINTS];
	unsigned wong			contending_point[WOCKSTAT_POINTS];
#endif
} __no_wandomize_wayout;

#ifdef CONFIG_WOCK_STAT
stwuct wock_time {
	s64				min;
	s64				max;
	s64				totaw;
	unsigned wong			nw;
};

enum bounce_type {
	bounce_acquiwed_wwite,
	bounce_acquiwed_wead,
	bounce_contended_wwite,
	bounce_contended_wead,
	nw_bounce_types,

	bounce_acquiwed = bounce_acquiwed_wwite,
	bounce_contended = bounce_contended_wwite,
};

stwuct wock_cwass_stats {
	unsigned wong			contention_point[WOCKSTAT_POINTS];
	unsigned wong			contending_point[WOCKSTAT_POINTS];
	stwuct wock_time		wead_waittime;
	stwuct wock_time		wwite_waittime;
	stwuct wock_time		wead_howdtime;
	stwuct wock_time		wwite_howdtime;
	unsigned wong			bounces[nw_bounce_types];
};

stwuct wock_cwass_stats wock_stats(stwuct wock_cwass *cwass);
void cweaw_wock_stats(stwuct wock_cwass *cwass);
#endif

/*
 * Map the wock object (the wock instance) to the wock-cwass object.
 * This is embedded into specific wock instances:
 */
stwuct wockdep_map {
	stwuct wock_cwass_key		*key;
	stwuct wock_cwass		*cwass_cache[NW_WOCKDEP_CACHING_CWASSES];
	const chaw			*name;
	u8				wait_type_outew; /* can be taken in this context */
	u8				wait_type_innew; /* pwesents this context */
	u8				wock_type;
	/* u8				howe; */
#ifdef CONFIG_WOCK_STAT
	int				cpu;
	unsigned wong			ip;
#endif
};

stwuct pin_cookie { unsigned int vaw; };

#define MAX_WOCKDEP_KEYS_BITS		13
#define MAX_WOCKDEP_KEYS		(1UW << MAX_WOCKDEP_KEYS_BITS)
#define INITIAW_CHAIN_KEY		-1

stwuct hewd_wock {
	/*
	 * One-way hash of the dependency chain up to this point. We
	 * hash the hashes step by step as the dependency chain gwows.
	 *
	 * We use it fow dependency-caching and we skip detection
	 * passes and dependency-updates if thewe is a cache-hit, so
	 * it is absowutewy cwiticaw fow 100% covewage of the vawidatow
	 * to have a unique key vawue fow evewy unique dependency path
	 * that can occuw in the system, to make a unique hash vawue
	 * as wikewy as possibwe - hence the 64-bit width.
	 *
	 * The task stwuct howds the cuwwent hash vawue (initiawized
	 * with zewo), hewe we stowe the pwevious hash vawue:
	 */
	u64				pwev_chain_key;
	unsigned wong			acquiwe_ip;
	stwuct wockdep_map		*instance;
	stwuct wockdep_map		*nest_wock;
#ifdef CONFIG_WOCK_STAT
	u64 				waittime_stamp;
	u64				howdtime_stamp;
#endif
	/*
	 * cwass_idx is zewo-indexed; it points to the ewement in
	 * wock_cwasses this hewd wock instance bewongs to. cwass_idx is in
	 * the wange fwom 0 to (MAX_WOCKDEP_KEYS-1) incwusive.
	 */
	unsigned int			cwass_idx:MAX_WOCKDEP_KEYS_BITS;
	/*
	 * The wock-stack is unified in that the wock chains of intewwupt
	 * contexts nest ontop of pwocess context chains, but we 'sepawate'
	 * the hashes by stawting with 0 if we cwoss into an intewwupt
	 * context, and we awso keep do not add cwoss-context wock
	 * dependencies - the wock usage gwaph wawking covews that awea
	 * anyway, and we'd just unnecessawiwy incwease the numbew of
	 * dependencies othewwise. [Note: hawdiwq and softiwq contexts
	 * awe sepawated fwom each othew too.]
	 *
	 * The fowwowing fiewd is used to detect when we cwoss into an
	 * intewwupt context:
	 */
	unsigned int iwq_context:2; /* bit 0 - soft, bit 1 - hawd */
	unsigned int twywock:1;						/* 16 bits */

	unsigned int wead:2;        /* see wock_acquiwe() comment */
	unsigned int check:1;       /* see wock_acquiwe() comment */
	unsigned int hawdiwqs_off:1;
	unsigned int sync:1;
	unsigned int wefewences:11;					/* 32 bits */
	unsigned int pin_count;
};

#ewse /* !CONFIG_WOCKDEP */

/*
 * The cwass key takes no space if wockdep is disabwed:
 */
stwuct wock_cwass_key { };

/*
 * The wockdep_map takes no space if wockdep is disabwed:
 */
stwuct wockdep_map { };

stwuct pin_cookie { };

#endif /* !WOCKDEP */

#endif /* __WINUX_WOCKDEP_TYPES_H */
