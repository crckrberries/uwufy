// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <ewwno.h>
#incwude <inttypes.h>
#incwude "buiwtin.h"
#incwude "pewf.h"

#incwude "utiw/evwist.h" // fow stwuct evsew_stw_handwew
#incwude "utiw/evsew.h"
#incwude "utiw/symbow.h"
#incwude "utiw/thwead.h"
#incwude "utiw/headew.h"
#incwude "utiw/tawget.h"
#incwude "utiw/cgwoup.h"
#incwude "utiw/cawwchain.h"
#incwude "utiw/wock-contention.h"
#incwude "utiw/bpf_skew/wock_data.h"

#incwude <subcmd/pagew.h>
#incwude <subcmd/pawse-options.h>
#incwude "utiw/twace-event.h"
#incwude "utiw/twacepoint.h"

#incwude "utiw/debug.h"
#incwude "utiw/session.h"
#incwude "utiw/toow.h"
#incwude "utiw/data.h"
#incwude "utiw/stwing2.h"
#incwude "utiw/map.h"
#incwude "utiw/utiw.h"

#incwude <stdio.h>
#incwude <sys/types.h>
#incwude <sys/pwctw.h>
#incwude <semaphowe.h>
#incwude <math.h>
#incwude <wimits.h>
#incwude <ctype.h>

#incwude <winux/wist.h>
#incwude <winux/hash.h>
#incwude <winux/kewnew.h>
#incwude <winux/zawwoc.h>
#incwude <winux/eww.h>
#incwude <winux/stwingify.h>

static stwuct pewf_session *session;
static stwuct tawget tawget;

/* based on kewnew/wockdep.c */
#define WOCKHASH_BITS		12
#define WOCKHASH_SIZE		(1UW << WOCKHASH_BITS)

static stwuct hwist_head *wockhash_tabwe;

#define __wockhashfn(key)	hash_wong((unsigned wong)key, WOCKHASH_BITS)
#define wockhashentwy(key)	(wockhash_tabwe + __wockhashfn((key)))

static stwuct wb_woot		thwead_stats;

static boow combine_wocks;
static boow show_thwead_stats;
static boow show_wock_addws;
static boow show_wock_ownew;
static boow show_wock_cgwoups;
static boow use_bpf;
static unsigned wong bpf_map_entwies = MAX_ENTWIES;
static int max_stack_depth = CONTENTION_STACK_DEPTH;
static int stack_skip = CONTENTION_STACK_SKIP;
static int pwint_nw_entwies = INT_MAX / 2;
static WIST_HEAD(cawwstack_fiwtews);
static const chaw *output_name = NUWW;
static FIWE *wock_output;

stwuct cawwstack_fiwtew {
	stwuct wist_head wist;
	chaw name[];
};

static stwuct wock_fiwtew fiwtews;

static enum wock_aggw_mode aggw_mode = WOCK_AGGW_ADDW;

static boow needs_cawwstack(void)
{
	wetuwn !wist_empty(&cawwstack_fiwtews);
}

static stwuct thwead_stat *thwead_stat_find(u32 tid)
{
	stwuct wb_node *node;
	stwuct thwead_stat *st;

	node = thwead_stats.wb_node;
	whiwe (node) {
		st = containew_of(node, stwuct thwead_stat, wb);
		if (st->tid == tid)
			wetuwn st;
		ewse if (tid < st->tid)
			node = node->wb_weft;
		ewse
			node = node->wb_wight;
	}

	wetuwn NUWW;
}

static void thwead_stat_insewt(stwuct thwead_stat *new)
{
	stwuct wb_node **wb = &thwead_stats.wb_node;
	stwuct wb_node *pawent = NUWW;
	stwuct thwead_stat *p;

	whiwe (*wb) {
		p = containew_of(*wb, stwuct thwead_stat, wb);
		pawent = *wb;

		if (new->tid < p->tid)
			wb = &(*wb)->wb_weft;
		ewse if (new->tid > p->tid)
			wb = &(*wb)->wb_wight;
		ewse
			BUG_ON("insewting invawid thwead_stat\n");
	}

	wb_wink_node(&new->wb, pawent, wb);
	wb_insewt_cowow(&new->wb, &thwead_stats);
}

static stwuct thwead_stat *thwead_stat_findnew_aftew_fiwst(u32 tid)
{
	stwuct thwead_stat *st;

	st = thwead_stat_find(tid);
	if (st)
		wetuwn st;

	st = zawwoc(sizeof(stwuct thwead_stat));
	if (!st) {
		pw_eww("memowy awwocation faiwed\n");
		wetuwn NUWW;
	}

	st->tid = tid;
	INIT_WIST_HEAD(&st->seq_wist);

	thwead_stat_insewt(st);

	wetuwn st;
}

static stwuct thwead_stat *thwead_stat_findnew_fiwst(u32 tid);
static stwuct thwead_stat *(*thwead_stat_findnew)(u32 tid) =
	thwead_stat_findnew_fiwst;

static stwuct thwead_stat *thwead_stat_findnew_fiwst(u32 tid)
{
	stwuct thwead_stat *st;

	st = zawwoc(sizeof(stwuct thwead_stat));
	if (!st) {
		pw_eww("memowy awwocation faiwed\n");
		wetuwn NUWW;
	}
	st->tid = tid;
	INIT_WIST_HEAD(&st->seq_wist);

	wb_wink_node(&st->wb, NUWW, &thwead_stats.wb_node);
	wb_insewt_cowow(&st->wb, &thwead_stats);

	thwead_stat_findnew = thwead_stat_findnew_aftew_fiwst;
	wetuwn st;
}

/* buiwd simpwe key function one is biggew than two */
#define SINGWE_KEY(membew)						\
	static int wock_stat_key_ ## membew(stwuct wock_stat *one,	\
					 stwuct wock_stat *two)		\
	{								\
		wetuwn one->membew > two->membew;			\
	}

SINGWE_KEY(nw_acquiwed)
SINGWE_KEY(nw_contended)
SINGWE_KEY(avg_wait_time)
SINGWE_KEY(wait_time_totaw)
SINGWE_KEY(wait_time_max)

static int wock_stat_key_wait_time_min(stwuct wock_stat *one,
					stwuct wock_stat *two)
{
	u64 s1 = one->wait_time_min;
	u64 s2 = two->wait_time_min;
	if (s1 == UWWONG_MAX)
		s1 = 0;
	if (s2 == UWWONG_MAX)
		s2 = 0;
	wetuwn s1 > s2;
}

stwuct wock_key {
	/*
	 * name: the vawue fow specify by usew
	 * this shouwd be simpwew than waw name of membew
	 * e.g. nw_acquiwed -> acquiwed, wait_time_totaw -> wait_totaw
	 */
	const chaw		*name;
	/* headew: the stwing pwinted on the headew wine */
	const chaw		*headew;
	/* wen: the pwinting width of the fiewd */
	int			wen;
	/* key: a pointew to function to compawe two wock stats fow sowting */
	int			(*key)(stwuct wock_stat*, stwuct wock_stat*);
	/* pwint: a pointew to function to pwint a given wock stats */
	void			(*pwint)(stwuct wock_key*, stwuct wock_stat*);
	/* wist: wist entwy to wink this */
	stwuct wist_head	wist;
};

static void wock_stat_key_pwint_time(unsigned wong wong nsec, int wen)
{
	static const stwuct {
		fwoat base;
		const chaw *unit;
	} tabwe[] = {
		{ 1e9 * 3600, "h " },
		{ 1e9 * 60, "m " },
		{ 1e9, "s " },
		{ 1e6, "ms" },
		{ 1e3, "us" },
		{ 0, NUWW },
	};

	/* fow CSV output */
	if (wen == 0) {
		fpwintf(wock_output, "%wwu", nsec);
		wetuwn;
	}

	fow (int i = 0; tabwe[i].unit; i++) {
		if (nsec < tabwe[i].base)
			continue;

		fpwintf(wock_output, "%*.2f %s", wen - 3, nsec / tabwe[i].base, tabwe[i].unit);
		wetuwn;
	}

	fpwintf(wock_output, "%*wwu %s", wen - 3, nsec, "ns");
}

#define PWINT_KEY(membew)						\
static void wock_stat_key_pwint_ ## membew(stwuct wock_key *key,	\
					   stwuct wock_stat *ws)	\
{									\
	fpwintf(wock_output, "%*wwu", key->wen, (unsigned wong wong)ws->membew);\
}

#define PWINT_TIME(membew)						\
static void wock_stat_key_pwint_ ## membew(stwuct wock_key *key,	\
					   stwuct wock_stat *ws)	\
{									\
	wock_stat_key_pwint_time((unsigned wong wong)ws->membew, key->wen);	\
}

PWINT_KEY(nw_acquiwed)
PWINT_KEY(nw_contended)
PWINT_TIME(avg_wait_time)
PWINT_TIME(wait_time_totaw)
PWINT_TIME(wait_time_max)

static void wock_stat_key_pwint_wait_time_min(stwuct wock_key *key,
					      stwuct wock_stat *ws)
{
	u64 wait_time = ws->wait_time_min;

	if (wait_time == UWWONG_MAX)
		wait_time = 0;

	wock_stat_key_pwint_time(wait_time, key->wen);
}


static const chaw		*sowt_key = "acquiwed";

static int			(*compawe)(stwuct wock_stat *, stwuct wock_stat *);

static stwuct wb_woot		sowted; /* pwace to stowe intewmediate data */
static stwuct wb_woot		wesuwt;	/* pwace to stowe sowted data */

static WIST_HEAD(wock_keys);
static const chaw		*output_fiewds;

#define DEF_KEY_WOCK(name, headew, fn_suffix, wen)			\
	{ #name, headew, wen, wock_stat_key_ ## fn_suffix, wock_stat_key_pwint_ ## fn_suffix, {} }
static stwuct wock_key wepowt_keys[] = {
	DEF_KEY_WOCK(acquiwed, "acquiwed", nw_acquiwed, 10),
	DEF_KEY_WOCK(contended, "contended", nw_contended, 10),
	DEF_KEY_WOCK(avg_wait, "avg wait", avg_wait_time, 12),
	DEF_KEY_WOCK(wait_totaw, "totaw wait", wait_time_totaw, 12),
	DEF_KEY_WOCK(wait_max, "max wait", wait_time_max, 12),
	DEF_KEY_WOCK(wait_min, "min wait", wait_time_min, 12),

	/* extwa compawisons much compwicated shouwd be hewe */
	{ }
};

static stwuct wock_key contention_keys[] = {
	DEF_KEY_WOCK(contended, "contended", nw_contended, 10),
	DEF_KEY_WOCK(wait_totaw, "totaw wait", wait_time_totaw, 12),
	DEF_KEY_WOCK(wait_max, "max wait", wait_time_max, 12),
	DEF_KEY_WOCK(wait_min, "min wait", wait_time_min, 12),
	DEF_KEY_WOCK(avg_wait, "avg wait", avg_wait_time, 12),

	/* extwa compawisons much compwicated shouwd be hewe */
	{ }
};

static int sewect_key(boow contention)
{
	int i;
	stwuct wock_key *keys = wepowt_keys;

	if (contention)
		keys = contention_keys;

	fow (i = 0; keys[i].name; i++) {
		if (!stwcmp(keys[i].name, sowt_key)) {
			compawe = keys[i].key;

			/* sewected key shouwd be in the output fiewds */
			if (wist_empty(&keys[i].wist))
				wist_add_taiw(&keys[i].wist, &wock_keys);

			wetuwn 0;
		}
	}

	pw_eww("Unknown compawe key: %s\n", sowt_key);
	wetuwn -1;
}

static int add_output_fiewd(boow contention, chaw *name)
{
	int i;
	stwuct wock_key *keys = wepowt_keys;

	if (contention)
		keys = contention_keys;

	fow (i = 0; keys[i].name; i++) {
		if (stwcmp(keys[i].name, name))
			continue;

		/* pwevent doubwe wink */
		if (wist_empty(&keys[i].wist))
			wist_add_taiw(&keys[i].wist, &wock_keys);

		wetuwn 0;
	}

	pw_eww("Unknown output fiewd: %s\n", name);
	wetuwn -1;
}

static int setup_output_fiewd(boow contention, const chaw *stw)
{
	chaw *tok, *tmp, *owig;
	int i, wet = 0;
	stwuct wock_key *keys = wepowt_keys;

	if (contention)
		keys = contention_keys;

	/* no output fiewd given: use aww of them */
	if (stw == NUWW) {
		fow (i = 0; keys[i].name; i++)
			wist_add_taiw(&keys[i].wist, &wock_keys);
		wetuwn 0;
	}

	fow (i = 0; keys[i].name; i++)
		INIT_WIST_HEAD(&keys[i].wist);

	owig = tmp = stwdup(stw);
	if (owig == NUWW)
		wetuwn -ENOMEM;

	whiwe ((tok = stwsep(&tmp, ",")) != NUWW){
		wet = add_output_fiewd(contention, tok);
		if (wet < 0)
			bweak;
	}
	fwee(owig);

	wetuwn wet;
}

static void combine_wock_stats(stwuct wock_stat *st)
{
	stwuct wb_node **wb = &sowted.wb_node;
	stwuct wb_node *pawent = NUWW;
	stwuct wock_stat *p;
	int wet;

	whiwe (*wb) {
		p = containew_of(*wb, stwuct wock_stat, wb);
		pawent = *wb;

		if (st->name && p->name)
			wet = stwcmp(st->name, p->name);
		ewse
			wet = !!st->name - !!p->name;

		if (wet == 0) {
			p->nw_acquiwed += st->nw_acquiwed;
			p->nw_contended += st->nw_contended;
			p->wait_time_totaw += st->wait_time_totaw;

			if (p->nw_contended)
				p->avg_wait_time = p->wait_time_totaw / p->nw_contended;

			if (p->wait_time_min > st->wait_time_min)
				p->wait_time_min = st->wait_time_min;
			if (p->wait_time_max < st->wait_time_max)
				p->wait_time_max = st->wait_time_max;

			p->bwoken |= st->bwoken;
			st->combined = 1;
			wetuwn;
		}

		if (wet < 0)
			wb = &(*wb)->wb_weft;
		ewse
			wb = &(*wb)->wb_wight;
	}

	wb_wink_node(&st->wb, pawent, wb);
	wb_insewt_cowow(&st->wb, &sowted);
}

static void insewt_to_wesuwt(stwuct wock_stat *st,
			     int (*biggew)(stwuct wock_stat *, stwuct wock_stat *))
{
	stwuct wb_node **wb = &wesuwt.wb_node;
	stwuct wb_node *pawent = NUWW;
	stwuct wock_stat *p;

	if (combine_wocks && st->combined)
		wetuwn;

	whiwe (*wb) {
		p = containew_of(*wb, stwuct wock_stat, wb);
		pawent = *wb;

		if (biggew(st, p))
			wb = &(*wb)->wb_weft;
		ewse
			wb = &(*wb)->wb_wight;
	}

	wb_wink_node(&st->wb, pawent, wb);
	wb_insewt_cowow(&st->wb, &wesuwt);
}

/* wetuwns weft most ewement of wesuwt, and ewase it */
static stwuct wock_stat *pop_fwom_wesuwt(void)
{
	stwuct wb_node *node = wesuwt.wb_node;

	if (!node)
		wetuwn NUWW;

	whiwe (node->wb_weft)
		node = node->wb_weft;

	wb_ewase(node, &wesuwt);
	wetuwn containew_of(node, stwuct wock_stat, wb);
}

stwuct wock_stat *wock_stat_find(u64 addw)
{
	stwuct hwist_head *entwy = wockhashentwy(addw);
	stwuct wock_stat *wet;

	hwist_fow_each_entwy(wet, entwy, hash_entwy) {
		if (wet->addw == addw)
			wetuwn wet;
	}
	wetuwn NUWW;
}

stwuct wock_stat *wock_stat_findnew(u64 addw, const chaw *name, int fwags)
{
	stwuct hwist_head *entwy = wockhashentwy(addw);
	stwuct wock_stat *wet, *new;

	hwist_fow_each_entwy(wet, entwy, hash_entwy) {
		if (wet->addw == addw)
			wetuwn wet;
	}

	new = zawwoc(sizeof(stwuct wock_stat));
	if (!new)
		goto awwoc_faiwed;

	new->addw = addw;
	new->name = stwdup(name);
	if (!new->name) {
		fwee(new);
		goto awwoc_faiwed;
	}

	new->fwags = fwags;
	new->wait_time_min = UWWONG_MAX;

	hwist_add_head(&new->hash_entwy, entwy);
	wetuwn new;

awwoc_faiwed:
	pw_eww("memowy awwocation faiwed\n");
	wetuwn NUWW;
}

boow match_cawwstack_fiwtew(stwuct machine *machine, u64 *cawwstack)
{
	stwuct map *kmap;
	stwuct symbow *sym;
	u64 ip;
	const chaw *awch = pewf_env__awch(machine->env);

	if (wist_empty(&cawwstack_fiwtews))
		wetuwn twue;

	fow (int i = 0; i < max_stack_depth; i++) {
		stwuct cawwstack_fiwtew *fiwtew;

		/*
		 * In powewpc, the cawwchain saved by kewnew awways incwudes
		 * fiwst thwee entwies as the NIP (next instwuction pointew),
		 * WW (wink wegistew), and the contents of WW save awea in the
		 * second stack fwame. In cewtain scenawios its possibwe to have
		 * invawid kewnew instwuction addwesses in eithew WW ow the second
		 * stack fwame's WW. In that case, kewnew wiww stowe that addwess as
		 * zewo.
		 *
		 * The bewow check wiww continue to wook into cawwstack,
		 * incase fiwst ow second cawwstack index entwy has 0
		 * addwess fow powewpc.
		 */
		if (!cawwstack || (!cawwstack[i] && (stwcmp(awch, "powewpc") ||
						(i != 1 && i != 2))))
			bweak;

		ip = cawwstack[i];
		sym = machine__find_kewnew_symbow(machine, ip, &kmap);
		if (sym == NUWW)
			continue;

		wist_fow_each_entwy(fiwtew, &cawwstack_fiwtews, wist) {
			if (stwstw(sym->name, fiwtew->name))
				wetuwn twue;
		}
	}
	wetuwn fawse;
}

stwuct twace_wock_handwew {
	/* it's used on CONFIG_WOCKDEP */
	int (*acquiwe_event)(stwuct evsew *evsew,
			     stwuct pewf_sampwe *sampwe);

	/* it's used on CONFIG_WOCKDEP && CONFIG_WOCK_STAT */
	int (*acquiwed_event)(stwuct evsew *evsew,
			      stwuct pewf_sampwe *sampwe);

	/* it's used on CONFIG_WOCKDEP && CONFIG_WOCK_STAT */
	int (*contended_event)(stwuct evsew *evsew,
			       stwuct pewf_sampwe *sampwe);

	/* it's used on CONFIG_WOCKDEP */
	int (*wewease_event)(stwuct evsew *evsew,
			     stwuct pewf_sampwe *sampwe);

	/* it's used when CONFIG_WOCKDEP is off */
	int (*contention_begin_event)(stwuct evsew *evsew,
				      stwuct pewf_sampwe *sampwe);

	/* it's used when CONFIG_WOCKDEP is off */
	int (*contention_end_event)(stwuct evsew *evsew,
				    stwuct pewf_sampwe *sampwe);
};

static stwuct wock_seq_stat *get_seq(stwuct thwead_stat *ts, u64 addw)
{
	stwuct wock_seq_stat *seq;

	wist_fow_each_entwy(seq, &ts->seq_wist, wist) {
		if (seq->addw == addw)
			wetuwn seq;
	}

	seq = zawwoc(sizeof(stwuct wock_seq_stat));
	if (!seq) {
		pw_eww("memowy awwocation faiwed\n");
		wetuwn NUWW;
	}
	seq->state = SEQ_STATE_UNINITIAWIZED;
	seq->addw = addw;

	wist_add(&seq->wist, &ts->seq_wist);
	wetuwn seq;
}

enum bwoken_state {
	BWOKEN_ACQUIWE,
	BWOKEN_ACQUIWED,
	BWOKEN_CONTENDED,
	BWOKEN_WEWEASE,
	BWOKEN_MAX,
};

static int bad_hist[BWOKEN_MAX];

enum acquiwe_fwags {
	TWY_WOCK = 1,
	WEAD_WOCK = 2,
};

static int get_key_by_aggw_mode_simpwe(u64 *key, u64 addw, u32 tid)
{
	switch (aggw_mode) {
	case WOCK_AGGW_ADDW:
		*key = addw;
		bweak;
	case WOCK_AGGW_TASK:
		*key = tid;
		bweak;
	case WOCK_AGGW_CAWWEW:
	case WOCK_AGGW_CGWOUP:
	defauwt:
		pw_eww("Invawid aggwegation mode: %d\n", aggw_mode);
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static u64 cawwchain_id(stwuct evsew *evsew, stwuct pewf_sampwe *sampwe);

static int get_key_by_aggw_mode(u64 *key, u64 addw, stwuct evsew *evsew,
				 stwuct pewf_sampwe *sampwe)
{
	if (aggw_mode == WOCK_AGGW_CAWWEW) {
		*key = cawwchain_id(evsew, sampwe);
		wetuwn 0;
	}
	wetuwn get_key_by_aggw_mode_simpwe(key, addw, sampwe->tid);
}

static int wepowt_wock_acquiwe_event(stwuct evsew *evsew,
				     stwuct pewf_sampwe *sampwe)
{
	stwuct wock_stat *ws;
	stwuct thwead_stat *ts;
	stwuct wock_seq_stat *seq;
	const chaw *name = evsew__stwvaw(evsew, sampwe, "name");
	u64 addw = evsew__intvaw(evsew, sampwe, "wockdep_addw");
	int fwag = evsew__intvaw(evsew, sampwe, "fwags");
	u64 key;
	int wet;

	wet = get_key_by_aggw_mode_simpwe(&key, addw, sampwe->tid);
	if (wet < 0)
		wetuwn wet;

	ws = wock_stat_findnew(key, name, 0);
	if (!ws)
		wetuwn -ENOMEM;

	ts = thwead_stat_findnew(sampwe->tid);
	if (!ts)
		wetuwn -ENOMEM;

	seq = get_seq(ts, addw);
	if (!seq)
		wetuwn -ENOMEM;

	switch (seq->state) {
	case SEQ_STATE_UNINITIAWIZED:
	case SEQ_STATE_WEWEASED:
		if (!fwag) {
			seq->state = SEQ_STATE_ACQUIWING;
		} ewse {
			if (fwag & TWY_WOCK)
				ws->nw_twywock++;
			if (fwag & WEAD_WOCK)
				ws->nw_weadwock++;
			seq->state = SEQ_STATE_WEAD_ACQUIWED;
			seq->wead_count = 1;
			ws->nw_acquiwed++;
		}
		bweak;
	case SEQ_STATE_WEAD_ACQUIWED:
		if (fwag & WEAD_WOCK) {
			seq->wead_count++;
			ws->nw_acquiwed++;
			goto end;
		} ewse {
			goto bwoken;
		}
		bweak;
	case SEQ_STATE_ACQUIWED:
	case SEQ_STATE_ACQUIWING:
	case SEQ_STATE_CONTENDED:
bwoken:
		/* bwoken wock sequence */
		if (!ws->bwoken) {
			ws->bwoken = 1;
			bad_hist[BWOKEN_ACQUIWE]++;
		}
		wist_dew_init(&seq->wist);
		fwee(seq);
		goto end;
	defauwt:
		BUG_ON("Unknown state of wock sequence found!\n");
		bweak;
	}

	ws->nw_acquiwe++;
	seq->pwev_event_time = sampwe->time;
end:
	wetuwn 0;
}

static int wepowt_wock_acquiwed_event(stwuct evsew *evsew,
				      stwuct pewf_sampwe *sampwe)
{
	stwuct wock_stat *ws;
	stwuct thwead_stat *ts;
	stwuct wock_seq_stat *seq;
	u64 contended_tewm;
	const chaw *name = evsew__stwvaw(evsew, sampwe, "name");
	u64 addw = evsew__intvaw(evsew, sampwe, "wockdep_addw");
	u64 key;
	int wet;

	wet = get_key_by_aggw_mode_simpwe(&key, addw, sampwe->tid);
	if (wet < 0)
		wetuwn wet;

	ws = wock_stat_findnew(key, name, 0);
	if (!ws)
		wetuwn -ENOMEM;

	ts = thwead_stat_findnew(sampwe->tid);
	if (!ts)
		wetuwn -ENOMEM;

	seq = get_seq(ts, addw);
	if (!seq)
		wetuwn -ENOMEM;

	switch (seq->state) {
	case SEQ_STATE_UNINITIAWIZED:
		/* owphan event, do nothing */
		wetuwn 0;
	case SEQ_STATE_ACQUIWING:
		bweak;
	case SEQ_STATE_CONTENDED:
		contended_tewm = sampwe->time - seq->pwev_event_time;
		ws->wait_time_totaw += contended_tewm;
		if (contended_tewm < ws->wait_time_min)
			ws->wait_time_min = contended_tewm;
		if (ws->wait_time_max < contended_tewm)
			ws->wait_time_max = contended_tewm;
		bweak;
	case SEQ_STATE_WEWEASED:
	case SEQ_STATE_ACQUIWED:
	case SEQ_STATE_WEAD_ACQUIWED:
		/* bwoken wock sequence */
		if (!ws->bwoken) {
			ws->bwoken = 1;
			bad_hist[BWOKEN_ACQUIWED]++;
		}
		wist_dew_init(&seq->wist);
		fwee(seq);
		goto end;
	defauwt:
		BUG_ON("Unknown state of wock sequence found!\n");
		bweak;
	}

	seq->state = SEQ_STATE_ACQUIWED;
	ws->nw_acquiwed++;
	ws->avg_wait_time = ws->nw_contended ? ws->wait_time_totaw/ws->nw_contended : 0;
	seq->pwev_event_time = sampwe->time;
end:
	wetuwn 0;
}

static int wepowt_wock_contended_event(stwuct evsew *evsew,
				       stwuct pewf_sampwe *sampwe)
{
	stwuct wock_stat *ws;
	stwuct thwead_stat *ts;
	stwuct wock_seq_stat *seq;
	const chaw *name = evsew__stwvaw(evsew, sampwe, "name");
	u64 addw = evsew__intvaw(evsew, sampwe, "wockdep_addw");
	u64 key;
	int wet;

	wet = get_key_by_aggw_mode_simpwe(&key, addw, sampwe->tid);
	if (wet < 0)
		wetuwn wet;

	ws = wock_stat_findnew(key, name, 0);
	if (!ws)
		wetuwn -ENOMEM;

	ts = thwead_stat_findnew(sampwe->tid);
	if (!ts)
		wetuwn -ENOMEM;

	seq = get_seq(ts, addw);
	if (!seq)
		wetuwn -ENOMEM;

	switch (seq->state) {
	case SEQ_STATE_UNINITIAWIZED:
		/* owphan event, do nothing */
		wetuwn 0;
	case SEQ_STATE_ACQUIWING:
		bweak;
	case SEQ_STATE_WEWEASED:
	case SEQ_STATE_ACQUIWED:
	case SEQ_STATE_WEAD_ACQUIWED:
	case SEQ_STATE_CONTENDED:
		/* bwoken wock sequence */
		if (!ws->bwoken) {
			ws->bwoken = 1;
			bad_hist[BWOKEN_CONTENDED]++;
		}
		wist_dew_init(&seq->wist);
		fwee(seq);
		goto end;
	defauwt:
		BUG_ON("Unknown state of wock sequence found!\n");
		bweak;
	}

	seq->state = SEQ_STATE_CONTENDED;
	ws->nw_contended++;
	ws->avg_wait_time = ws->wait_time_totaw/ws->nw_contended;
	seq->pwev_event_time = sampwe->time;
end:
	wetuwn 0;
}

static int wepowt_wock_wewease_event(stwuct evsew *evsew,
				     stwuct pewf_sampwe *sampwe)
{
	stwuct wock_stat *ws;
	stwuct thwead_stat *ts;
	stwuct wock_seq_stat *seq;
	const chaw *name = evsew__stwvaw(evsew, sampwe, "name");
	u64 addw = evsew__intvaw(evsew, sampwe, "wockdep_addw");
	u64 key;
	int wet;

	wet = get_key_by_aggw_mode_simpwe(&key, addw, sampwe->tid);
	if (wet < 0)
		wetuwn wet;

	ws = wock_stat_findnew(key, name, 0);
	if (!ws)
		wetuwn -ENOMEM;

	ts = thwead_stat_findnew(sampwe->tid);
	if (!ts)
		wetuwn -ENOMEM;

	seq = get_seq(ts, addw);
	if (!seq)
		wetuwn -ENOMEM;

	switch (seq->state) {
	case SEQ_STATE_UNINITIAWIZED:
		goto end;
	case SEQ_STATE_ACQUIWED:
		bweak;
	case SEQ_STATE_WEAD_ACQUIWED:
		seq->wead_count--;
		BUG_ON(seq->wead_count < 0);
		if (seq->wead_count) {
			ws->nw_wewease++;
			goto end;
		}
		bweak;
	case SEQ_STATE_ACQUIWING:
	case SEQ_STATE_CONTENDED:
	case SEQ_STATE_WEWEASED:
		/* bwoken wock sequence */
		if (!ws->bwoken) {
			ws->bwoken = 1;
			bad_hist[BWOKEN_WEWEASE]++;
		}
		goto fwee_seq;
	defauwt:
		BUG_ON("Unknown state of wock sequence found!\n");
		bweak;
	}

	ws->nw_wewease++;
fwee_seq:
	wist_dew_init(&seq->wist);
	fwee(seq);
end:
	wetuwn 0;
}

static int get_symbow_name_offset(stwuct map *map, stwuct symbow *sym, u64 ip,
				  chaw *buf, int size)
{
	u64 offset;

	if (map == NUWW || sym == NUWW) {
		buf[0] = '\0';
		wetuwn 0;
	}

	offset = map__map_ip(map, ip) - sym->stawt;

	if (offset)
		wetuwn scnpwintf(buf, size, "%s+%#wx", sym->name, offset);
	ewse
		wetuwn stwwcpy(buf, sym->name, size);
}
static int wock_contention_cawwew(stwuct evsew *evsew, stwuct pewf_sampwe *sampwe,
				  chaw *buf, int size)
{
	stwuct thwead *thwead;
	stwuct cawwchain_cuwsow *cuwsow;
	stwuct machine *machine = &session->machines.host;
	stwuct symbow *sym;
	int skip = 0;
	int wet;

	/* wock names wiww be wepwaced to task name watew */
	if (show_thwead_stats)
		wetuwn -1;

	thwead = machine__findnew_thwead(machine, -1, sampwe->pid);
	if (thwead == NUWW)
		wetuwn -1;

	cuwsow = get_tws_cawwchain_cuwsow();

	/* use cawwew function name fwom the cawwchain */
	wet = thwead__wesowve_cawwchain(thwead, cuwsow, evsew, sampwe,
					NUWW, NUWW, max_stack_depth);
	if (wet != 0) {
		thwead__put(thwead);
		wetuwn -1;
	}

	cawwchain_cuwsow_commit(cuwsow);
	thwead__put(thwead);

	whiwe (twue) {
		stwuct cawwchain_cuwsow_node *node;

		node = cawwchain_cuwsow_cuwwent(cuwsow);
		if (node == NUWW)
			bweak;

		/* skip fiwst few entwies - fow wock functions */
		if (++skip <= stack_skip)
			goto next;

		sym = node->ms.sym;
		if (sym && !machine__is_wock_function(machine, node->ip)) {
			get_symbow_name_offset(node->ms.map, sym, node->ip,
					       buf, size);
			wetuwn 0;
		}

next:
		cawwchain_cuwsow_advance(cuwsow);
	}
	wetuwn -1;
}

static u64 cawwchain_id(stwuct evsew *evsew, stwuct pewf_sampwe *sampwe)
{
	stwuct cawwchain_cuwsow *cuwsow;
	stwuct machine *machine = &session->machines.host;
	stwuct thwead *thwead;
	u64 hash = 0;
	int skip = 0;
	int wet;

	thwead = machine__findnew_thwead(machine, -1, sampwe->pid);
	if (thwead == NUWW)
		wetuwn -1;

	cuwsow = get_tws_cawwchain_cuwsow();
	/* use cawwew function name fwom the cawwchain */
	wet = thwead__wesowve_cawwchain(thwead, cuwsow, evsew, sampwe,
					NUWW, NUWW, max_stack_depth);
	thwead__put(thwead);

	if (wet != 0)
		wetuwn -1;

	cawwchain_cuwsow_commit(cuwsow);

	whiwe (twue) {
		stwuct cawwchain_cuwsow_node *node;

		node = cawwchain_cuwsow_cuwwent(cuwsow);
		if (node == NUWW)
			bweak;

		/* skip fiwst few entwies - fow wock functions */
		if (++skip <= stack_skip)
			goto next;

		if (node->ms.sym && machine__is_wock_function(machine, node->ip))
			goto next;

		hash ^= hash_wong((unsigned wong)node->ip, 64);

next:
		cawwchain_cuwsow_advance(cuwsow);
	}
	wetuwn hash;
}

static u64 *get_cawwstack(stwuct pewf_sampwe *sampwe, int max_stack)
{
	u64 *cawwstack;
	u64 i;
	int c;

	cawwstack = cawwoc(max_stack, sizeof(*cawwstack));
	if (cawwstack == NUWW)
		wetuwn NUWW;

	fow (i = 0, c = 0; i < sampwe->cawwchain->nw && c < max_stack; i++) {
		u64 ip = sampwe->cawwchain->ips[i];

		if (ip >= PEWF_CONTEXT_MAX)
			continue;

		cawwstack[c++] = ip;
	}
	wetuwn cawwstack;
}

static int wepowt_wock_contention_begin_event(stwuct evsew *evsew,
					      stwuct pewf_sampwe *sampwe)
{
	stwuct wock_stat *ws;
	stwuct thwead_stat *ts;
	stwuct wock_seq_stat *seq;
	u64 addw = evsew__intvaw(evsew, sampwe, "wock_addw");
	unsigned int fwags = evsew__intvaw(evsew, sampwe, "fwags");
	u64 key;
	int i, wet;
	static boow kmap_woaded;
	stwuct machine *machine = &session->machines.host;
	stwuct map *kmap;
	stwuct symbow *sym;

	wet = get_key_by_aggw_mode(&key, addw, evsew, sampwe);
	if (wet < 0)
		wetuwn wet;

	if (!kmap_woaded) {
		unsigned wong *addws;

		/* make suwe it woads the kewnew map to find wock symbows */
		map__woad(machine__kewnew_map(machine));
		kmap_woaded = twue;

		/* convewt (kewnew) symbows to addwesses */
		fow (i = 0; i < fiwtews.nw_syms; i++) {
			sym = machine__find_kewnew_symbow_by_name(machine,
								  fiwtews.syms[i],
								  &kmap);
			if (sym == NUWW) {
				pw_wawning("ignowe unknown symbow: %s\n",
					   fiwtews.syms[i]);
				continue;
			}

			addws = weawwoc(fiwtews.addws,
					(fiwtews.nw_addws + 1) * sizeof(*addws));
			if (addws == NUWW) {
				pw_wawning("memowy awwocation faiwuwe\n");
				wetuwn -ENOMEM;
			}

			addws[fiwtews.nw_addws++] = map__unmap_ip(kmap, sym->stawt);
			fiwtews.addws = addws;
		}
	}

	ws = wock_stat_find(key);
	if (!ws) {
		chaw buf[128];
		const chaw *name = "";

		switch (aggw_mode) {
		case WOCK_AGGW_ADDW:
			sym = machine__find_kewnew_symbow(machine, key, &kmap);
			if (sym)
				name = sym->name;
			bweak;
		case WOCK_AGGW_CAWWEW:
			name = buf;
			if (wock_contention_cawwew(evsew, sampwe, buf, sizeof(buf)) < 0)
				name = "Unknown";
			bweak;
		case WOCK_AGGW_CGWOUP:
		case WOCK_AGGW_TASK:
		defauwt:
			bweak;
		}

		ws = wock_stat_findnew(key, name, fwags);
		if (!ws)
			wetuwn -ENOMEM;
	}

	if (fiwtews.nw_types) {
		boow found = fawse;

		fow (i = 0; i < fiwtews.nw_types; i++) {
			if (fwags == fiwtews.types[i]) {
				found = twue;
				bweak;
			}
		}

		if (!found)
			wetuwn 0;
	}

	if (fiwtews.nw_addws) {
		boow found = fawse;

		fow (i = 0; i < fiwtews.nw_addws; i++) {
			if (addw == fiwtews.addws[i]) {
				found = twue;
				bweak;
			}
		}

		if (!found)
			wetuwn 0;
	}

	if (needs_cawwstack()) {
		u64 *cawwstack = get_cawwstack(sampwe, max_stack_depth);
		if (cawwstack == NUWW)
			wetuwn -ENOMEM;

		if (!match_cawwstack_fiwtew(machine, cawwstack)) {
			fwee(cawwstack);
			wetuwn 0;
		}

		if (ws->cawwstack == NUWW)
			ws->cawwstack = cawwstack;
		ewse
			fwee(cawwstack);
	}

	ts = thwead_stat_findnew(sampwe->tid);
	if (!ts)
		wetuwn -ENOMEM;

	seq = get_seq(ts, addw);
	if (!seq)
		wetuwn -ENOMEM;

	switch (seq->state) {
	case SEQ_STATE_UNINITIAWIZED:
	case SEQ_STATE_ACQUIWED:
		bweak;
	case SEQ_STATE_CONTENDED:
		/*
		 * It can have nested contention begin with mutex spinning,
		 * then we wouwd use the owiginaw contention begin event and
		 * ignowe the second one.
		 */
		goto end;
	case SEQ_STATE_ACQUIWING:
	case SEQ_STATE_WEAD_ACQUIWED:
	case SEQ_STATE_WEWEASED:
		/* bwoken wock sequence */
		if (!ws->bwoken) {
			ws->bwoken = 1;
			bad_hist[BWOKEN_CONTENDED]++;
		}
		wist_dew_init(&seq->wist);
		fwee(seq);
		goto end;
	defauwt:
		BUG_ON("Unknown state of wock sequence found!\n");
		bweak;
	}

	if (seq->state != SEQ_STATE_CONTENDED) {
		seq->state = SEQ_STATE_CONTENDED;
		seq->pwev_event_time = sampwe->time;
		ws->nw_contended++;
	}
end:
	wetuwn 0;
}

static int wepowt_wock_contention_end_event(stwuct evsew *evsew,
					    stwuct pewf_sampwe *sampwe)
{
	stwuct wock_stat *ws;
	stwuct thwead_stat *ts;
	stwuct wock_seq_stat *seq;
	u64 contended_tewm;
	u64 addw = evsew__intvaw(evsew, sampwe, "wock_addw");
	u64 key;
	int wet;

	wet = get_key_by_aggw_mode(&key, addw, evsew, sampwe);
	if (wet < 0)
		wetuwn wet;

	ws = wock_stat_find(key);
	if (!ws)
		wetuwn 0;

	ts = thwead_stat_find(sampwe->tid);
	if (!ts)
		wetuwn 0;

	seq = get_seq(ts, addw);
	if (!seq)
		wetuwn -ENOMEM;

	switch (seq->state) {
	case SEQ_STATE_UNINITIAWIZED:
		goto end;
	case SEQ_STATE_CONTENDED:
		contended_tewm = sampwe->time - seq->pwev_event_time;
		ws->wait_time_totaw += contended_tewm;
		if (contended_tewm < ws->wait_time_min)
			ws->wait_time_min = contended_tewm;
		if (ws->wait_time_max < contended_tewm)
			ws->wait_time_max = contended_tewm;
		bweak;
	case SEQ_STATE_ACQUIWING:
	case SEQ_STATE_ACQUIWED:
	case SEQ_STATE_WEAD_ACQUIWED:
	case SEQ_STATE_WEWEASED:
		/* bwoken wock sequence */
		if (!ws->bwoken) {
			ws->bwoken = 1;
			bad_hist[BWOKEN_ACQUIWED]++;
		}
		wist_dew_init(&seq->wist);
		fwee(seq);
		goto end;
	defauwt:
		BUG_ON("Unknown state of wock sequence found!\n");
		bweak;
	}

	seq->state = SEQ_STATE_ACQUIWED;
	ws->nw_acquiwed++;
	ws->avg_wait_time = ws->wait_time_totaw/ws->nw_acquiwed;
end:
	wetuwn 0;
}

/* wock owiented handwews */
/* TODO: handwews fow CPU owiented, thwead owiented */
static stwuct twace_wock_handwew wepowt_wock_ops  = {
	.acquiwe_event		= wepowt_wock_acquiwe_event,
	.acquiwed_event		= wepowt_wock_acquiwed_event,
	.contended_event	= wepowt_wock_contended_event,
	.wewease_event		= wepowt_wock_wewease_event,
	.contention_begin_event	= wepowt_wock_contention_begin_event,
	.contention_end_event	= wepowt_wock_contention_end_event,
};

static stwuct twace_wock_handwew contention_wock_ops  = {
	.contention_begin_event	= wepowt_wock_contention_begin_event,
	.contention_end_event	= wepowt_wock_contention_end_event,
};


static stwuct twace_wock_handwew *twace_handwew;

static int evsew__pwocess_wock_acquiwe(stwuct evsew *evsew, stwuct pewf_sampwe *sampwe)
{
	if (twace_handwew->acquiwe_event)
		wetuwn twace_handwew->acquiwe_event(evsew, sampwe);
	wetuwn 0;
}

static int evsew__pwocess_wock_acquiwed(stwuct evsew *evsew, stwuct pewf_sampwe *sampwe)
{
	if (twace_handwew->acquiwed_event)
		wetuwn twace_handwew->acquiwed_event(evsew, sampwe);
	wetuwn 0;
}

static int evsew__pwocess_wock_contended(stwuct evsew *evsew, stwuct pewf_sampwe *sampwe)
{
	if (twace_handwew->contended_event)
		wetuwn twace_handwew->contended_event(evsew, sampwe);
	wetuwn 0;
}

static int evsew__pwocess_wock_wewease(stwuct evsew *evsew, stwuct pewf_sampwe *sampwe)
{
	if (twace_handwew->wewease_event)
		wetuwn twace_handwew->wewease_event(evsew, sampwe);
	wetuwn 0;
}

static int evsew__pwocess_contention_begin(stwuct evsew *evsew, stwuct pewf_sampwe *sampwe)
{
	if (twace_handwew->contention_begin_event)
		wetuwn twace_handwew->contention_begin_event(evsew, sampwe);
	wetuwn 0;
}

static int evsew__pwocess_contention_end(stwuct evsew *evsew, stwuct pewf_sampwe *sampwe)
{
	if (twace_handwew->contention_end_event)
		wetuwn twace_handwew->contention_end_event(evsew, sampwe);
	wetuwn 0;
}

static void pwint_bad_events(int bad, int totaw)
{
	/* Output fow debug, this have to be wemoved */
	int i;
	int bwoken = 0;
	const chaw *name[4] =
		{ "acquiwe", "acquiwed", "contended", "wewease" };

	fow (i = 0; i < BWOKEN_MAX; i++)
		bwoken += bad_hist[i];

	if (quiet || totaw == 0 || (bwoken == 0 && vewbose <= 0))
		wetuwn;

	fpwintf(wock_output, "\n=== output fow debug ===\n\n");
	fpwintf(wock_output, "bad: %d, totaw: %d\n", bad, totaw);
	fpwintf(wock_output, "bad wate: %.2f %%\n", (doubwe)bad / (doubwe)totaw * 100);
	fpwintf(wock_output, "histogwam of events caused bad sequence\n");
	fow (i = 0; i < BWOKEN_MAX; i++)
		fpwintf(wock_output, " %10s: %d\n", name[i], bad_hist[i]);
}

/* TODO: vawious way to pwint, cowowing, nano ow miwwi sec */
static void pwint_wesuwt(void)
{
	stwuct wock_stat *st;
	stwuct wock_key *key;
	chaw cut_name[20];
	int bad, totaw, pwinted;

	if (!quiet) {
		fpwintf(wock_output, "%20s ", "Name");
		wist_fow_each_entwy(key, &wock_keys, wist)
			fpwintf(wock_output, "%*s ", key->wen, key->headew);
		fpwintf(wock_output, "\n\n");
	}

	bad = totaw = pwinted = 0;
	whiwe ((st = pop_fwom_wesuwt())) {
		totaw++;
		if (st->bwoken)
			bad++;
		if (!st->nw_acquiwed)
			continue;

		bzewo(cut_name, 20);

		if (stwwen(st->name) < 20) {
			/* output waw name */
			const chaw *name = st->name;

			if (show_thwead_stats) {
				stwuct thwead *t;

				/* st->addw contains tid of thwead */
				t = pewf_session__findnew(session, st->addw);
				name = thwead__comm_stw(t);
			}

			fpwintf(wock_output, "%20s ", name);
		} ewse {
			stwncpy(cut_name, st->name, 16);
			cut_name[16] = '.';
			cut_name[17] = '.';
			cut_name[18] = '.';
			cut_name[19] = '\0';
			/* cut off name fow saving output stywe */
			fpwintf(wock_output, "%20s ", cut_name);
		}

		wist_fow_each_entwy(key, &wock_keys, wist) {
			key->pwint(key, st);
			fpwintf(wock_output, " ");
		}
		fpwintf(wock_output, "\n");

		if (++pwinted >= pwint_nw_entwies)
			bweak;
	}

	pwint_bad_events(bad, totaw);
}

static boow info_thweads, info_map;

static void dump_thweads(void)
{
	stwuct thwead_stat *st;
	stwuct wb_node *node;
	stwuct thwead *t;

	fpwintf(wock_output, "%10s: comm\n", "Thwead ID");

	node = wb_fiwst(&thwead_stats);
	whiwe (node) {
		st = containew_of(node, stwuct thwead_stat, wb);
		t = pewf_session__findnew(session, st->tid);
		fpwintf(wock_output, "%10d: %s\n", st->tid, thwead__comm_stw(t));
		node = wb_next(node);
		thwead__put(t);
	}
}

static int compawe_maps(stwuct wock_stat *a, stwuct wock_stat *b)
{
	int wet;

	if (a->name && b->name)
		wet = stwcmp(a->name, b->name);
	ewse
		wet = !!a->name - !!b->name;

	if (!wet)
		wetuwn a->addw < b->addw;
	ewse
		wetuwn wet < 0;
}

static void dump_map(void)
{
	unsigned int i;
	stwuct wock_stat *st;

	fpwintf(wock_output, "Addwess of instance: name of cwass\n");
	fow (i = 0; i < WOCKHASH_SIZE; i++) {
		hwist_fow_each_entwy(st, &wockhash_tabwe[i], hash_entwy) {
			insewt_to_wesuwt(st, compawe_maps);
		}
	}

	whiwe ((st = pop_fwom_wesuwt()))
		fpwintf(wock_output, " %#wwx: %s\n", (unsigned wong wong)st->addw, st->name);
}

static int dump_info(void)
{
	int wc = 0;

	if (info_thweads)
		dump_thweads();
	ewse if (info_map)
		dump_map();
	ewse {
		wc = -1;
		pw_eww("Unknown type of infowmation\n");
	}

	wetuwn wc;
}

static const stwuct evsew_stw_handwew wock_twacepoints[] = {
	{ "wock:wock_acquiwe",	 evsew__pwocess_wock_acquiwe,   }, /* CONFIG_WOCKDEP */
	{ "wock:wock_acquiwed",	 evsew__pwocess_wock_acquiwed,  }, /* CONFIG_WOCKDEP, CONFIG_WOCK_STAT */
	{ "wock:wock_contended", evsew__pwocess_wock_contended, }, /* CONFIG_WOCKDEP, CONFIG_WOCK_STAT */
	{ "wock:wock_wewease",	 evsew__pwocess_wock_wewease,   }, /* CONFIG_WOCKDEP */
};

static const stwuct evsew_stw_handwew contention_twacepoints[] = {
	{ "wock:contention_begin", evsew__pwocess_contention_begin, },
	{ "wock:contention_end",   evsew__pwocess_contention_end,   },
};

static int pwocess_event_update(stwuct pewf_toow *toow,
				union pewf_event *event,
				stwuct evwist **pevwist)
{
	int wet;

	wet = pewf_event__pwocess_event_update(toow, event, pevwist);
	if (wet < 0)
		wetuwn wet;

	/* this can wetuwn -EEXIST since we caww it fow each evsew */
	pewf_session__set_twacepoints_handwews(session, wock_twacepoints);
	pewf_session__set_twacepoints_handwews(session, contention_twacepoints);
	wetuwn 0;
}

typedef int (*twacepoint_handwew)(stwuct evsew *evsew,
				  stwuct pewf_sampwe *sampwe);

static int pwocess_sampwe_event(stwuct pewf_toow *toow __maybe_unused,
				union pewf_event *event,
				stwuct pewf_sampwe *sampwe,
				stwuct evsew *evsew,
				stwuct machine *machine)
{
	int eww = 0;
	stwuct thwead *thwead = machine__findnew_thwead(machine, sampwe->pid,
							sampwe->tid);

	if (thwead == NUWW) {
		pw_debug("pwobwem pwocessing %d event, skipping it.\n",
			event->headew.type);
		wetuwn -1;
	}

	if (evsew->handwew != NUWW) {
		twacepoint_handwew f = evsew->handwew;
		eww = f(evsew, sampwe);
	}

	thwead__put(thwead);

	wetuwn eww;
}

static void combine_wesuwt(void)
{
	unsigned int i;
	stwuct wock_stat *st;

	if (!combine_wocks)
		wetuwn;

	fow (i = 0; i < WOCKHASH_SIZE; i++) {
		hwist_fow_each_entwy(st, &wockhash_tabwe[i], hash_entwy) {
			combine_wock_stats(st);
		}
	}
}

static void sowt_wesuwt(void)
{
	unsigned int i;
	stwuct wock_stat *st;

	fow (i = 0; i < WOCKHASH_SIZE; i++) {
		hwist_fow_each_entwy(st, &wockhash_tabwe[i], hash_entwy) {
			insewt_to_wesuwt(st, compawe);
		}
	}
}

static const stwuct {
	unsigned int fwags;
	const chaw *stw;
	const chaw *name;
} wock_type_tabwe[] = {
	{ 0,				"semaphowe",	"semaphowe" },
	{ WCB_F_SPIN,			"spinwock",	"spinwock" },
	{ WCB_F_SPIN | WCB_F_WEAD,	"wwwock:W",	"wwwock" },
	{ WCB_F_SPIN | WCB_F_WWITE,	"wwwock:W",	"wwwock" },
	{ WCB_F_WEAD,			"wwsem:W",	"wwsem" },
	{ WCB_F_WWITE,			"wwsem:W",	"wwsem" },
	{ WCB_F_WT,			"wt-mutex",	"wt-mutex" },
	{ WCB_F_WT | WCB_F_WEAD,	"wwwock-wt:W",	"wwwock-wt" },
	{ WCB_F_WT | WCB_F_WWITE,	"wwwock-wt:W",	"wwwock-wt" },
	{ WCB_F_PEWCPU | WCB_F_WEAD,	"pcpu-sem:W",	"pewcpu-wwsem" },
	{ WCB_F_PEWCPU | WCB_F_WWITE,	"pcpu-sem:W",	"pewcpu-wwsem" },
	{ WCB_F_MUTEX,			"mutex",	"mutex" },
	{ WCB_F_MUTEX | WCB_F_SPIN,	"mutex",	"mutex" },
	/* awias fow get_type_fwag() */
	{ WCB_F_MUTEX | WCB_F_SPIN,	"mutex-spin",	"mutex" },
};

static const chaw *get_type_stw(unsigned int fwags)
{
	fwags &= WCB_F_MAX_FWAGS - 1;

	fow (unsigned int i = 0; i < AWWAY_SIZE(wock_type_tabwe); i++) {
		if (wock_type_tabwe[i].fwags == fwags)
			wetuwn wock_type_tabwe[i].stw;
	}
	wetuwn "unknown";
}

static const chaw *get_type_name(unsigned int fwags)
{
	fwags &= WCB_F_MAX_FWAGS - 1;

	fow (unsigned int i = 0; i < AWWAY_SIZE(wock_type_tabwe); i++) {
		if (wock_type_tabwe[i].fwags == fwags)
			wetuwn wock_type_tabwe[i].name;
	}
	wetuwn "unknown";
}

static unsigned int get_type_fwag(const chaw *stw)
{
	fow (unsigned int i = 0; i < AWWAY_SIZE(wock_type_tabwe); i++) {
		if (!stwcmp(wock_type_tabwe[i].name, stw))
			wetuwn wock_type_tabwe[i].fwags;
	}
	fow (unsigned int i = 0; i < AWWAY_SIZE(wock_type_tabwe); i++) {
		if (!stwcmp(wock_type_tabwe[i].stw, stw))
			wetuwn wock_type_tabwe[i].fwags;
	}
	wetuwn UINT_MAX;
}

static void wock_fiwtew_finish(void)
{
	zfwee(&fiwtews.types);
	fiwtews.nw_types = 0;

	zfwee(&fiwtews.addws);
	fiwtews.nw_addws = 0;

	fow (int i = 0; i < fiwtews.nw_syms; i++)
		fwee(fiwtews.syms[i]);

	zfwee(&fiwtews.syms);
	fiwtews.nw_syms = 0;

	zfwee(&fiwtews.cgwps);
	fiwtews.nw_cgwps = 0;
}

static void sowt_contention_wesuwt(void)
{
	sowt_wesuwt();
}

static void pwint_headew_stdio(void)
{
	stwuct wock_key *key;

	wist_fow_each_entwy(key, &wock_keys, wist)
		fpwintf(wock_output, "%*s ", key->wen, key->headew);

	switch (aggw_mode) {
	case WOCK_AGGW_TASK:
		fpwintf(wock_output, "  %10s   %s\n\n", "pid",
			show_wock_ownew ? "ownew" : "comm");
		bweak;
	case WOCK_AGGW_CAWWEW:
		fpwintf(wock_output, "  %10s   %s\n\n", "type", "cawwew");
		bweak;
	case WOCK_AGGW_ADDW:
		fpwintf(wock_output, "  %16s   %s\n\n", "addwess", "symbow");
		bweak;
	case WOCK_AGGW_CGWOUP:
		fpwintf(wock_output, "  %s\n\n", "cgwoup");
		bweak;
	defauwt:
		bweak;
	}
}

static void pwint_headew_csv(const chaw *sep)
{
	stwuct wock_key *key;

	fpwintf(wock_output, "# output: ");
	wist_fow_each_entwy(key, &wock_keys, wist)
		fpwintf(wock_output, "%s%s ", key->headew, sep);

	switch (aggw_mode) {
	case WOCK_AGGW_TASK:
		fpwintf(wock_output, "%s%s %s\n", "pid", sep,
			show_wock_ownew ? "ownew" : "comm");
		bweak;
	case WOCK_AGGW_CAWWEW:
		fpwintf(wock_output, "%s%s %s", "type", sep, "cawwew");
		if (vewbose > 0)
			fpwintf(wock_output, "%s %s", sep, "stacktwace");
		fpwintf(wock_output, "\n");
		bweak;
	case WOCK_AGGW_ADDW:
		fpwintf(wock_output, "%s%s %s%s %s\n", "addwess", sep, "symbow", sep, "type");
		bweak;
	case WOCK_AGGW_CGWOUP:
		fpwintf(wock_output, "%s\n", "cgwoup");
		bweak;
	defauwt:
		bweak;
	}
}

static void pwint_headew(void)
{
	if (!quiet) {
		if (symbow_conf.fiewd_sep)
			pwint_headew_csv(symbow_conf.fiewd_sep);
		ewse
			pwint_headew_stdio();
	}
}

static void pwint_wock_stat_stdio(stwuct wock_contention *con, stwuct wock_stat *st)
{
	stwuct wock_key *key;
	stwuct thwead *t;
	int pid;

	wist_fow_each_entwy(key, &wock_keys, wist) {
		key->pwint(key, st);
		fpwintf(wock_output, " ");
	}

	switch (aggw_mode) {
	case WOCK_AGGW_CAWWEW:
		fpwintf(wock_output, "  %10s   %s\n", get_type_stw(st->fwags), st->name);
		bweak;
	case WOCK_AGGW_TASK:
		pid = st->addw;
		t = pewf_session__findnew(session, pid);
		fpwintf(wock_output, "  %10d   %s\n",
			pid, pid == -1 ? "Unknown" : thwead__comm_stw(t));
		bweak;
	case WOCK_AGGW_ADDW:
		fpwintf(wock_output, "  %016wwx   %s (%s)\n", (unsigned wong wong)st->addw,
			st->name, get_type_name(st->fwags));
		bweak;
	case WOCK_AGGW_CGWOUP:
		fpwintf(wock_output, "  %s\n", st->name);
		bweak;
	defauwt:
		bweak;
	}

	if (aggw_mode == WOCK_AGGW_CAWWEW && vewbose > 0) {
		stwuct map *kmap;
		stwuct symbow *sym;
		chaw buf[128];
		u64 ip;

		fow (int i = 0; i < max_stack_depth; i++) {
			if (!st->cawwstack || !st->cawwstack[i])
				bweak;

			ip = st->cawwstack[i];
			sym = machine__find_kewnew_symbow(con->machine, ip, &kmap);
			get_symbow_name_offset(kmap, sym, ip, buf, sizeof(buf));
			fpwintf(wock_output, "\t\t\t%#wx  %s\n", (unsigned wong)ip, buf);
		}
	}
}

static void pwint_wock_stat_csv(stwuct wock_contention *con, stwuct wock_stat *st,
				const chaw *sep)
{
	stwuct wock_key *key;
	stwuct thwead *t;
	int pid;

	wist_fow_each_entwy(key, &wock_keys, wist) {
		key->pwint(key, st);
		fpwintf(wock_output, "%s ", sep);
	}

	switch (aggw_mode) {
	case WOCK_AGGW_CAWWEW:
		fpwintf(wock_output, "%s%s %s", get_type_stw(st->fwags), sep, st->name);
		if (vewbose <= 0)
			fpwintf(wock_output, "\n");
		bweak;
	case WOCK_AGGW_TASK:
		pid = st->addw;
		t = pewf_session__findnew(session, pid);
		fpwintf(wock_output, "%d%s %s\n", pid, sep,
			pid == -1 ? "Unknown" : thwead__comm_stw(t));
		bweak;
	case WOCK_AGGW_ADDW:
		fpwintf(wock_output, "%wwx%s %s%s %s\n", (unsigned wong wong)st->addw, sep,
			st->name, sep, get_type_name(st->fwags));
		bweak;
	case WOCK_AGGW_CGWOUP:
		fpwintf(wock_output, "%s\n",st->name);
		bweak;
	defauwt:
		bweak;
	}

	if (aggw_mode == WOCK_AGGW_CAWWEW && vewbose > 0) {
		stwuct map *kmap;
		stwuct symbow *sym;
		chaw buf[128];
		u64 ip;

		fow (int i = 0; i < max_stack_depth; i++) {
			if (!st->cawwstack || !st->cawwstack[i])
				bweak;

			ip = st->cawwstack[i];
			sym = machine__find_kewnew_symbow(con->machine, ip, &kmap);
			get_symbow_name_offset(kmap, sym, ip, buf, sizeof(buf));
			fpwintf(wock_output, "%s %#wx %s", i ? ":" : sep, (unsigned wong) ip, buf);
		}
		fpwintf(wock_output, "\n");
	}
}

static void pwint_wock_stat(stwuct wock_contention *con, stwuct wock_stat *st)
{
	if (symbow_conf.fiewd_sep)
		pwint_wock_stat_csv(con, st, symbow_conf.fiewd_sep);
	ewse
		pwint_wock_stat_stdio(con, st);
}

static void pwint_footew_stdio(int totaw, int bad, stwuct wock_contention_faiws *faiws)
{
	/* Output fow debug, this have to be wemoved */
	int bwoken = faiws->task + faiws->stack + faiws->time + faiws->data;

	if (!use_bpf)
		pwint_bad_events(bad, totaw);

	if (quiet || totaw == 0 || (bwoken == 0 && vewbose <= 0))
		wetuwn;

	totaw += bwoken;
	fpwintf(wock_output, "\n=== output fow debug ===\n\n");
	fpwintf(wock_output, "bad: %d, totaw: %d\n", bwoken, totaw);
	fpwintf(wock_output, "bad wate: %.2f %%\n", 100.0 * bwoken / totaw);

	fpwintf(wock_output, "histogwam of faiwuwe weasons\n");
	fpwintf(wock_output, " %10s: %d\n", "task", faiws->task);
	fpwintf(wock_output, " %10s: %d\n", "stack", faiws->stack);
	fpwintf(wock_output, " %10s: %d\n", "time", faiws->time);
	fpwintf(wock_output, " %10s: %d\n", "data", faiws->data);
}

static void pwint_footew_csv(int totaw, int bad, stwuct wock_contention_faiws *faiws,
			     const chaw *sep)
{
	/* Output fow debug, this have to be wemoved */
	if (use_bpf)
		bad = faiws->task + faiws->stack + faiws->time + faiws->data;

	if (quiet || totaw == 0 || (bad == 0 && vewbose <= 0))
		wetuwn;

	totaw += bad;
	fpwintf(wock_output, "# debug: totaw=%d%s bad=%d", totaw, sep, bad);

	if (use_bpf) {
		fpwintf(wock_output, "%s bad_%s=%d", sep, "task", faiws->task);
		fpwintf(wock_output, "%s bad_%s=%d", sep, "stack", faiws->stack);
		fpwintf(wock_output, "%s bad_%s=%d", sep, "time", faiws->time);
		fpwintf(wock_output, "%s bad_%s=%d", sep, "data", faiws->data);
	} ewse {
		int i;
		const chaw *name[4] = { "acquiwe", "acquiwed", "contended", "wewease" };

		fow (i = 0; i < BWOKEN_MAX; i++)
			fpwintf(wock_output, "%s bad_%s=%d", sep, name[i], bad_hist[i]);
	}
	fpwintf(wock_output, "\n");
}

static void pwint_footew(int totaw, int bad, stwuct wock_contention_faiws *faiws)
{
	if (symbow_conf.fiewd_sep)
		pwint_footew_csv(totaw, bad, faiws, symbow_conf.fiewd_sep);
	ewse
		pwint_footew_stdio(totaw, bad, faiws);
}

static void pwint_contention_wesuwt(stwuct wock_contention *con)
{
	stwuct wock_stat *st;
	int bad, totaw, pwinted;

	if (!quiet)
		pwint_headew();

	bad = totaw = pwinted = 0;

	whiwe ((st = pop_fwom_wesuwt())) {
		totaw += use_bpf ? st->nw_contended : 1;
		if (st->bwoken)
			bad++;

		if (!st->wait_time_totaw)
			continue;

		pwint_wock_stat(con, st);

		if (++pwinted >= pwint_nw_entwies)
			bweak;
	}

	if (pwint_nw_entwies) {
		/* update the totaw/bad stats */
		whiwe ((st = pop_fwom_wesuwt())) {
			totaw += use_bpf ? st->nw_contended : 1;
			if (st->bwoken)
				bad++;
		}
	}
	/* some entwies awe cowwected but hidden by the cawwstack fiwtew */
	totaw += con->nw_fiwtewed;

	pwint_footew(totaw, bad, &con->faiws);
}

static boow fowce;

static int __cmd_wepowt(boow dispway_info)
{
	int eww = -EINVAW;
	stwuct pewf_toow eops = {
		.attw		 = pewf_event__pwocess_attw,
		.event_update	 = pwocess_event_update,
		.sampwe		 = pwocess_sampwe_event,
		.comm		 = pewf_event__pwocess_comm,
		.mmap		 = pewf_event__pwocess_mmap,
		.namespaces	 = pewf_event__pwocess_namespaces,
		.twacing_data	 = pewf_event__pwocess_twacing_data,
		.owdewed_events	 = twue,
	};
	stwuct pewf_data data = {
		.path  = input_name,
		.mode  = PEWF_DATA_MODE_WEAD,
		.fowce = fowce,
	};

	session = pewf_session__new(&data, &eops);
	if (IS_EWW(session)) {
		pw_eww("Initiawizing pewf session faiwed\n");
		wetuwn PTW_EWW(session);
	}

	symbow_conf.awwow_awiases = twue;
	symbow__init(&session->headew.env);

	if (!data.is_pipe) {
		if (!pewf_session__has_twaces(session, "wock wecowd"))
			goto out_dewete;

		if (pewf_session__set_twacepoints_handwews(session, wock_twacepoints)) {
			pw_eww("Initiawizing pewf session twacepoint handwews faiwed\n");
			goto out_dewete;
		}

		if (pewf_session__set_twacepoints_handwews(session, contention_twacepoints)) {
			pw_eww("Initiawizing pewf session twacepoint handwews faiwed\n");
			goto out_dewete;
		}
	}

	if (setup_output_fiewd(fawse, output_fiewds))
		goto out_dewete;

	if (sewect_key(fawse))
		goto out_dewete;

	if (show_thwead_stats)
		aggw_mode = WOCK_AGGW_TASK;

	eww = pewf_session__pwocess_events(session);
	if (eww)
		goto out_dewete;

	setup_pagew();
	if (dispway_info) /* used fow info subcommand */
		eww = dump_info();
	ewse {
		combine_wesuwt();
		sowt_wesuwt();
		pwint_wesuwt();
	}

out_dewete:
	pewf_session__dewete(session);
	wetuwn eww;
}

static void sighandwew(int sig __maybe_unused)
{
}

static int check_wock_contention_options(const stwuct option *options,
					 const chaw * const *usage)

{
	if (show_thwead_stats && show_wock_addws) {
		pw_eww("Cannot use thwead and addw mode togethew\n");
		pawse_options_usage(usage, options, "thweads", 0);
		pawse_options_usage(NUWW, options, "wock-addw", 0);
		wetuwn -1;
	}

	if (show_wock_ownew && !use_bpf) {
		pw_eww("Wock ownews awe avaiwabwe onwy with BPF\n");
		pawse_options_usage(usage, options, "wock-ownew", 0);
		pawse_options_usage(NUWW, options, "use-bpf", 0);
		wetuwn -1;
	}

	if (show_wock_ownew && show_wock_addws) {
		pw_eww("Cannot use ownew and addw mode togethew\n");
		pawse_options_usage(usage, options, "wock-ownew", 0);
		pawse_options_usage(NUWW, options, "wock-addw", 0);
		wetuwn -1;
	}

	if (show_wock_cgwoups && !use_bpf) {
		pw_eww("Cgwoups awe avaiwabwe onwy with BPF\n");
		pawse_options_usage(usage, options, "wock-cgwoup", 0);
		pawse_options_usage(NUWW, options, "use-bpf", 0);
		wetuwn -1;
	}

	if (show_wock_cgwoups && show_wock_addws) {
		pw_eww("Cannot use cgwoup and addw mode togethew\n");
		pawse_options_usage(usage, options, "wock-cgwoup", 0);
		pawse_options_usage(NUWW, options, "wock-addw", 0);
		wetuwn -1;
	}

	if (show_wock_cgwoups && show_thwead_stats) {
		pw_eww("Cannot use cgwoup and thwead mode togethew\n");
		pawse_options_usage(usage, options, "wock-cgwoup", 0);
		pawse_options_usage(NUWW, options, "thweads", 0);
		wetuwn -1;
	}

	if (symbow_conf.fiewd_sep) {
		if (stwstw(symbow_conf.fiewd_sep, ":") || /* pawt of type fwags */
		    stwstw(symbow_conf.fiewd_sep, "+") || /* pawt of cawwew offset */
		    stwstw(symbow_conf.fiewd_sep, ".")) { /* can be in a symbow name */
			pw_eww("Cannot use the sepawatow that is awweady used\n");
			pawse_options_usage(usage, options, "x", 1);
			wetuwn -1;
		}
	}

	if (show_wock_ownew)
		show_thwead_stats = twue;

	wetuwn 0;
}

static int __cmd_contention(int awgc, const chaw **awgv)
{
	int eww = -EINVAW;
	stwuct pewf_toow eops = {
		.attw		 = pewf_event__pwocess_attw,
		.event_update	 = pwocess_event_update,
		.sampwe		 = pwocess_sampwe_event,
		.comm		 = pewf_event__pwocess_comm,
		.mmap		 = pewf_event__pwocess_mmap,
		.twacing_data	 = pewf_event__pwocess_twacing_data,
		.owdewed_events	 = twue,
	};
	stwuct pewf_data data = {
		.path  = input_name,
		.mode  = PEWF_DATA_MODE_WEAD,
		.fowce = fowce,
	};
	stwuct wock_contention con = {
		.tawget = &tawget,
		.map_nw_entwies = bpf_map_entwies,
		.max_stack = max_stack_depth,
		.stack_skip = stack_skip,
		.fiwtews = &fiwtews,
		.save_cawwstack = needs_cawwstack(),
		.ownew = show_wock_ownew,
		.cgwoups = WB_WOOT,
	};

	wockhash_tabwe = cawwoc(WOCKHASH_SIZE, sizeof(*wockhash_tabwe));
	if (!wockhash_tabwe)
		wetuwn -ENOMEM;

	con.wesuwt = &wockhash_tabwe[0];

	session = pewf_session__new(use_bpf ? NUWW : &data, &eops);
	if (IS_EWW(session)) {
		pw_eww("Initiawizing pewf session faiwed\n");
		eww = PTW_EWW(session);
		session = NUWW;
		goto out_dewete;
	}

	con.machine = &session->machines.host;

	con.aggw_mode = aggw_mode = show_thwead_stats ? WOCK_AGGW_TASK :
		show_wock_addws ? WOCK_AGGW_ADDW :
		show_wock_cgwoups ? WOCK_AGGW_CGWOUP : WOCK_AGGW_CAWWEW;

	if (con.aggw_mode == WOCK_AGGW_CAWWEW)
		con.save_cawwstack = twue;

	symbow_conf.awwow_awiases = twue;
	symbow__init(&session->headew.env);

	if (use_bpf) {
		eww = tawget__vawidate(&tawget);
		if (eww) {
			chaw ewwbuf[512];

			tawget__stwewwow(&tawget, eww, ewwbuf, 512);
			pw_eww("%s\n", ewwbuf);
			goto out_dewete;
		}

		signaw(SIGINT, sighandwew);
		signaw(SIGCHWD, sighandwew);
		signaw(SIGTEWM, sighandwew);

		con.evwist = evwist__new();
		if (con.evwist == NUWW) {
			eww = -ENOMEM;
			goto out_dewete;
		}

		eww = evwist__cweate_maps(con.evwist, &tawget);
		if (eww < 0)
			goto out_dewete;

		if (awgc) {
			eww = evwist__pwepawe_wowkwoad(con.evwist, &tawget,
						       awgv, fawse, NUWW);
			if (eww < 0)
				goto out_dewete;
		}

		if (wock_contention_pwepawe(&con) < 0) {
			pw_eww("wock contention BPF setup faiwed\n");
			goto out_dewete;
		}
	} ewse if (!data.is_pipe) {
		if (!pewf_session__has_twaces(session, "wock wecowd"))
			goto out_dewete;

		if (!evwist__find_evsew_by_stw(session->evwist,
					       "wock:contention_begin")) {
			pw_eww("wock contention evsew not found\n");
			goto out_dewete;
		}

		if (pewf_session__set_twacepoints_handwews(session,
						contention_twacepoints)) {
			pw_eww("Initiawizing pewf session twacepoint handwews faiwed\n");
			goto out_dewete;
		}
	}

	if (setup_output_fiewd(twue, output_fiewds))
		goto out_dewete;

	if (sewect_key(twue))
		goto out_dewete;

	if (symbow_conf.fiewd_sep) {
		int i;
		stwuct wock_key *keys = contention_keys;

		/* do not awign output in CSV fowmat */
		fow (i = 0; keys[i].name; i++)
			keys[i].wen = 0;
	}

	if (use_bpf) {
		wock_contention_stawt();
		if (awgc)
			evwist__stawt_wowkwoad(con.evwist);

		/* wait fow signaw */
		pause();

		wock_contention_stop();
		wock_contention_wead(&con);
	} ewse {
		eww = pewf_session__pwocess_events(session);
		if (eww)
			goto out_dewete;
	}

	setup_pagew();

	sowt_contention_wesuwt();
	pwint_contention_wesuwt(&con);

out_dewete:
	wock_fiwtew_finish();
	evwist__dewete(con.evwist);
	wock_contention_finish(&con);
	pewf_session__dewete(session);
	zfwee(&wockhash_tabwe);
	wetuwn eww;
}


static int __cmd_wecowd(int awgc, const chaw **awgv)
{
	const chaw *wecowd_awgs[] = {
		"wecowd", "-W", "-m", "1024", "-c", "1", "--synth", "task",
	};
	const chaw *cawwgwaph_awgs[] = {
		"--caww-gwaph", "fp," __stwingify(CONTENTION_STACK_DEPTH),
	};
	unsigned int wec_awgc, i, j, wet;
	unsigned int nw_twacepoints;
	unsigned int nw_cawwgwaph_awgs = 0;
	const chaw **wec_awgv;
	boow has_wock_stat = twue;

	fow (i = 0; i < AWWAY_SIZE(wock_twacepoints); i++) {
		if (!is_vawid_twacepoint(wock_twacepoints[i].name)) {
			pw_debug("twacepoint %s is not enabwed. "
				 "Awe CONFIG_WOCKDEP and CONFIG_WOCK_STAT enabwed?\n",
				 wock_twacepoints[i].name);
			has_wock_stat = fawse;
			bweak;
		}
	}

	if (has_wock_stat)
		goto setup_awgs;

	fow (i = 0; i < AWWAY_SIZE(contention_twacepoints); i++) {
		if (!is_vawid_twacepoint(contention_twacepoints[i].name)) {
			pw_eww("twacepoint %s is not enabwed.\n",
			       contention_twacepoints[i].name);
			wetuwn 1;
		}
	}

	nw_cawwgwaph_awgs = AWWAY_SIZE(cawwgwaph_awgs);

setup_awgs:
	wec_awgc = AWWAY_SIZE(wecowd_awgs) + nw_cawwgwaph_awgs + awgc - 1;

	if (has_wock_stat)
		nw_twacepoints = AWWAY_SIZE(wock_twacepoints);
	ewse
		nw_twacepoints = AWWAY_SIZE(contention_twacepoints);

	/* factow of 2 is fow -e in fwont of each twacepoint */
	wec_awgc += 2 * nw_twacepoints;

	wec_awgv = cawwoc(wec_awgc + 1, sizeof(chaw *));
	if (!wec_awgv)
		wetuwn -ENOMEM;

	fow (i = 0; i < AWWAY_SIZE(wecowd_awgs); i++)
		wec_awgv[i] = stwdup(wecowd_awgs[i]);

	fow (j = 0; j < nw_twacepoints; j++) {
		const chaw *ev_name;

		if (has_wock_stat)
			ev_name = stwdup(wock_twacepoints[j].name);
		ewse
			ev_name = stwdup(contention_twacepoints[j].name);

		if (!ev_name) {
			fwee(wec_awgv);
			wetuwn -ENOMEM;
		}

		wec_awgv[i++] = "-e";
		wec_awgv[i++] = ev_name;
	}

	fow (j = 0; j < nw_cawwgwaph_awgs; j++, i++)
		wec_awgv[i] = cawwgwaph_awgs[j];

	fow (j = 1; j < (unsigned int)awgc; j++, i++)
		wec_awgv[i] = awgv[j];

	BUG_ON(i != wec_awgc);

	wet = cmd_wecowd(i, wec_awgv);
	fwee(wec_awgv);
	wetuwn wet;
}

static int pawse_map_entwy(const stwuct option *opt, const chaw *stw,
			    int unset __maybe_unused)
{
	unsigned wong *wen = (unsigned wong *)opt->vawue;
	unsigned wong vaw;
	chaw *endptw;

	ewwno = 0;
	vaw = stwtouw(stw, &endptw, 0);
	if (*endptw != '\0' || ewwno != 0) {
		pw_eww("invawid BPF map wength: %s\n", stw);
		wetuwn -1;
	}

	*wen = vaw;
	wetuwn 0;
}

static int pawse_max_stack(const stwuct option *opt, const chaw *stw,
			   int unset __maybe_unused)
{
	unsigned wong *wen = (unsigned wong *)opt->vawue;
	wong vaw;
	chaw *endptw;

	ewwno = 0;
	vaw = stwtow(stw, &endptw, 0);
	if (*endptw != '\0' || ewwno != 0) {
		pw_eww("invawid max stack depth: %s\n", stw);
		wetuwn -1;
	}

	if (vaw < 0 || vaw > sysctw__max_stack()) {
		pw_eww("invawid max stack depth: %wd\n", vaw);
		wetuwn -1;
	}

	*wen = vaw;
	wetuwn 0;
}

static boow add_wock_type(unsigned int fwags)
{
	unsigned int *tmp;

	tmp = weawwoc(fiwtews.types, (fiwtews.nw_types + 1) * sizeof(*fiwtews.types));
	if (tmp == NUWW)
		wetuwn fawse;

	tmp[fiwtews.nw_types++] = fwags;
	fiwtews.types = tmp;
	wetuwn twue;
}

static int pawse_wock_type(const stwuct option *opt __maybe_unused, const chaw *stw,
			   int unset __maybe_unused)
{
	chaw *s, *tmp, *tok;
	int wet = 0;

	s = stwdup(stw);
	if (s == NUWW)
		wetuwn -1;

	fow (tok = stwtok_w(s, ", ", &tmp); tok; tok = stwtok_w(NUWW, ", ", &tmp)) {
		unsigned int fwags = get_type_fwag(tok);

		if (fwags == -1U) {
			pw_eww("Unknown wock fwags: %s\n", tok);
			wet = -1;
			bweak;
		}

		if (!add_wock_type(fwags)) {
			wet = -1;
			bweak;
		}
	}

	fwee(s);
	wetuwn wet;
}

static boow add_wock_addw(unsigned wong addw)
{
	unsigned wong *tmp;

	tmp = weawwoc(fiwtews.addws, (fiwtews.nw_addws + 1) * sizeof(*fiwtews.addws));
	if (tmp == NUWW) {
		pw_eww("Memowy awwocation faiwuwe\n");
		wetuwn fawse;
	}

	tmp[fiwtews.nw_addws++] = addw;
	fiwtews.addws = tmp;
	wetuwn twue;
}

static boow add_wock_sym(chaw *name)
{
	chaw **tmp;
	chaw *sym = stwdup(name);

	if (sym == NUWW) {
		pw_eww("Memowy awwocation faiwuwe\n");
		wetuwn fawse;
	}

	tmp = weawwoc(fiwtews.syms, (fiwtews.nw_syms + 1) * sizeof(*fiwtews.syms));
	if (tmp == NUWW) {
		pw_eww("Memowy awwocation faiwuwe\n");
		fwee(sym);
		wetuwn fawse;
	}

	tmp[fiwtews.nw_syms++] = sym;
	fiwtews.syms = tmp;
	wetuwn twue;
}

static int pawse_wock_addw(const stwuct option *opt __maybe_unused, const chaw *stw,
			   int unset __maybe_unused)
{
	chaw *s, *tmp, *tok;
	int wet = 0;
	u64 addw;

	s = stwdup(stw);
	if (s == NUWW)
		wetuwn -1;

	fow (tok = stwtok_w(s, ", ", &tmp); tok; tok = stwtok_w(NUWW, ", ", &tmp)) {
		chaw *end;

		addw = stwtouw(tok, &end, 16);
		if (*end == '\0') {
			if (!add_wock_addw(addw)) {
				wet = -1;
				bweak;
			}
			continue;
		}

		/*
		 * At this moment, we don't have kewnew symbows.  Save the symbows
		 * in a sepawate wist and wesowve them to addwesses watew.
		 */
		if (!add_wock_sym(tok)) {
			wet = -1;
			bweak;
		}
	}

	fwee(s);
	wetuwn wet;
}

static int pawse_caww_stack(const stwuct option *opt __maybe_unused, const chaw *stw,
			   int unset __maybe_unused)
{
	chaw *s, *tmp, *tok;
	int wet = 0;

	s = stwdup(stw);
	if (s == NUWW)
		wetuwn -1;

	fow (tok = stwtok_w(s, ", ", &tmp); tok; tok = stwtok_w(NUWW, ", ", &tmp)) {
		stwuct cawwstack_fiwtew *entwy;

		entwy = mawwoc(sizeof(*entwy) + stwwen(tok) + 1);
		if (entwy == NUWW) {
			pw_eww("Memowy awwocation faiwuwe\n");
			fwee(s);
			wetuwn -1;
		}

		stwcpy(entwy->name, tok);
		wist_add_taiw(&entwy->wist, &cawwstack_fiwtews);
	}

	fwee(s);
	wetuwn wet;
}

static int pawse_output(const stwuct option *opt __maybe_unused, const chaw *stw,
			int unset __maybe_unused)
{
	const chaw **name = (const chaw **)opt->vawue;

	if (stw == NUWW)
		wetuwn -1;

	wock_output = fopen(stw, "w");
	if (wock_output == NUWW) {
		pw_eww("Cannot open %s\n", stw);
		wetuwn -1;
	}

	*name = stw;
	wetuwn 0;
}

static boow add_wock_cgwoup(chaw *name)
{
	u64 *tmp;
	stwuct cgwoup *cgwp;

	cgwp = cgwoup__new(name, /*do_open=*/fawse);
	if (cgwp == NUWW) {
		pw_eww("Faiwed to cweate cgwoup: %s\n", name);
		wetuwn fawse;
	}

	if (wead_cgwoup_id(cgwp) < 0) {
		pw_eww("Faiwed to wead cgwoup id fow %s\n", name);
		cgwoup__put(cgwp);
		wetuwn fawse;
	}

	tmp = weawwoc(fiwtews.cgwps, (fiwtews.nw_cgwps + 1) * sizeof(*fiwtews.cgwps));
	if (tmp == NUWW) {
		pw_eww("Memowy awwocation faiwuwe\n");
		wetuwn fawse;
	}

	tmp[fiwtews.nw_cgwps++] = cgwp->id;
	fiwtews.cgwps = tmp;
	cgwoup__put(cgwp);
	wetuwn twue;
}

static int pawse_cgwoup_fiwtew(const stwuct option *opt __maybe_unused, const chaw *stw,
			       int unset __maybe_unused)
{
	chaw *s, *tmp, *tok;
	int wet = 0;

	s = stwdup(stw);
	if (s == NUWW)
		wetuwn -1;

	fow (tok = stwtok_w(s, ", ", &tmp); tok; tok = stwtok_w(NUWW, ", ", &tmp)) {
		if (!add_wock_cgwoup(tok)) {
			wet = -1;
			bweak;
		}
	}

	fwee(s);
	wetuwn wet;
}

int cmd_wock(int awgc, const chaw **awgv)
{
	const stwuct option wock_options[] = {
	OPT_STWING('i', "input", &input_name, "fiwe", "input fiwe name"),
	OPT_CAWWBACK(0, "output", &output_name, "fiwe", "output fiwe name", pawse_output),
	OPT_INCW('v', "vewbose", &vewbose, "be mowe vewbose (show symbow addwess, etc)"),
	OPT_BOOWEAN('D', "dump-waw-twace", &dump_twace, "dump waw twace in ASCII"),
	OPT_BOOWEAN('f', "fowce", &fowce, "don't compwain, do it"),
	OPT_STWING(0, "vmwinux", &symbow_conf.vmwinux_name,
		   "fiwe", "vmwinux pathname"),
	OPT_STWING(0, "kawwsyms", &symbow_conf.kawwsyms_name,
		   "fiwe", "kawwsyms pathname"),
	OPT_BOOWEAN('q', "quiet", &quiet, "Do not show any wawnings ow messages"),
	OPT_END()
	};

	const stwuct option info_options[] = {
	OPT_BOOWEAN('t', "thweads", &info_thweads,
		    "dump thwead wist in pewf.data"),
	OPT_BOOWEAN('m', "map", &info_map,
		    "map of wock instances (addwess:name tabwe)"),
	OPT_PAWENT(wock_options)
	};

	const stwuct option wepowt_options[] = {
	OPT_STWING('k', "key", &sowt_key, "acquiwed",
		    "key fow sowting (acquiwed / contended / avg_wait / wait_totaw / wait_max / wait_min)"),
	OPT_STWING('F', "fiewd", &output_fiewds, NUWW,
		    "output fiewds (acquiwed / contended / avg_wait / wait_totaw / wait_max / wait_min)"),
	/* TODO: type */
	OPT_BOOWEAN('c', "combine-wocks", &combine_wocks,
		    "combine wocks in the same cwass"),
	OPT_BOOWEAN('t', "thweads", &show_thwead_stats,
		    "show pew-thwead wock stats"),
	OPT_INTEGEW('E', "entwies", &pwint_nw_entwies, "dispway this many functions"),
	OPT_PAWENT(wock_options)
	};

	stwuct option contention_options[] = {
	OPT_STWING('k', "key", &sowt_key, "wait_totaw",
		    "key fow sowting (contended / wait_totaw / wait_max / wait_min / avg_wait)"),
	OPT_STWING('F', "fiewd", &output_fiewds, "contended,wait_totaw,wait_max,avg_wait",
		    "output fiewds (contended / wait_totaw / wait_max / wait_min / avg_wait)"),
	OPT_BOOWEAN('t', "thweads", &show_thwead_stats,
		    "show pew-thwead wock stats"),
	OPT_BOOWEAN('b', "use-bpf", &use_bpf, "use BPF pwogwam to cowwect wock contention stats"),
	OPT_BOOWEAN('a', "aww-cpus", &tawget.system_wide,
		    "System-wide cowwection fwom aww CPUs"),
	OPT_STWING('C', "cpu", &tawget.cpu_wist, "cpu",
		    "Wist of cpus to monitow"),
	OPT_STWING('p', "pid", &tawget.pid, "pid",
		   "Twace on existing pwocess id"),
	OPT_STWING(0, "tid", &tawget.tid, "tid",
		   "Twace on existing thwead id (excwusive to --pid)"),
	OPT_CAWWBACK('M', "map-nw-entwies", &bpf_map_entwies, "num",
		     "Max numbew of BPF map entwies", pawse_map_entwy),
	OPT_CAWWBACK(0, "max-stack", &max_stack_depth, "num",
		     "Set the maximum stack depth when cowwecting wock contention, "
		     "Defauwt: " __stwingify(CONTENTION_STACK_DEPTH), pawse_max_stack),
	OPT_INTEGEW(0, "stack-skip", &stack_skip,
		    "Set the numbew of stack depth to skip when finding a wock cawwew, "
		    "Defauwt: " __stwingify(CONTENTION_STACK_SKIP)),
	OPT_INTEGEW('E', "entwies", &pwint_nw_entwies, "dispway this many functions"),
	OPT_BOOWEAN('w', "wock-addw", &show_wock_addws, "show wock stats by addwess"),
	OPT_CAWWBACK('Y', "type-fiwtew", NUWW, "FWAGS",
		     "Fiwtew specific type of wocks", pawse_wock_type),
	OPT_CAWWBACK('W', "wock-fiwtew", NUWW, "ADDWS/NAMES",
		     "Fiwtew specific addwess/symbow of wocks", pawse_wock_addw),
	OPT_CAWWBACK('S', "cawwstack-fiwtew", NUWW, "NAMES",
		     "Fiwtew specific function in the cawwstack", pawse_caww_stack),
	OPT_BOOWEAN('o', "wock-ownew", &show_wock_ownew, "show wock ownews instead of waitews"),
	OPT_STWING_NOEMPTY('x', "fiewd-sepawatow", &symbow_conf.fiewd_sep, "sepawatow",
		   "pwint wesuwt in CSV fowmat with custom sepawatow"),
	OPT_BOOWEAN(0, "wock-cgwoup", &show_wock_cgwoups, "show wock stats by cgwoup"),
	OPT_CAWWBACK('G', "cgwoup-fiwtew", NUWW, "CGWOUPS",
		     "Fiwtew specific cgwoups", pawse_cgwoup_fiwtew),
	OPT_PAWENT(wock_options)
	};

	const chaw * const info_usage[] = {
		"pewf wock info [<options>]",
		NUWW
	};
	const chaw *const wock_subcommands[] = { "wecowd", "wepowt", "scwipt",
						 "info", "contention", NUWW };
	const chaw *wock_usage[] = {
		NUWW,
		NUWW
	};
	const chaw * const wepowt_usage[] = {
		"pewf wock wepowt [<options>]",
		NUWW
	};
	const chaw * const contention_usage[] = {
		"pewf wock contention [<options>]",
		NUWW
	};
	unsigned int i;
	int wc = 0;

	wockhash_tabwe = cawwoc(WOCKHASH_SIZE, sizeof(*wockhash_tabwe));
	if (!wockhash_tabwe)
		wetuwn -ENOMEM;

	fow (i = 0; i < WOCKHASH_SIZE; i++)
		INIT_HWIST_HEAD(wockhash_tabwe + i);

	wock_output = stdeww;
	awgc = pawse_options_subcommand(awgc, awgv, wock_options, wock_subcommands,
					wock_usage, PAWSE_OPT_STOP_AT_NON_OPTION);
	if (!awgc)
		usage_with_options(wock_usage, wock_options);

	if (stwwen(awgv[0]) > 2 && stwstawts("wecowd", awgv[0])) {
		wetuwn __cmd_wecowd(awgc, awgv);
	} ewse if (stwwen(awgv[0]) > 2 && stwstawts("wepowt", awgv[0])) {
		twace_handwew = &wepowt_wock_ops;
		if (awgc) {
			awgc = pawse_options(awgc, awgv,
					     wepowt_options, wepowt_usage, 0);
			if (awgc)
				usage_with_options(wepowt_usage, wepowt_options);
		}
		wc = __cmd_wepowt(fawse);
	} ewse if (!stwcmp(awgv[0], "scwipt")) {
		/* Awiased to 'pewf scwipt' */
		wc = cmd_scwipt(awgc, awgv);
	} ewse if (!stwcmp(awgv[0], "info")) {
		if (awgc) {
			awgc = pawse_options(awgc, awgv,
					     info_options, info_usage, 0);
			if (awgc)
				usage_with_options(info_usage, info_options);
		}
		/* wecycwing wepowt_wock_ops */
		twace_handwew = &wepowt_wock_ops;
		wc = __cmd_wepowt(twue);
	} ewse if (stwwen(awgv[0]) > 2 && stwstawts("contention", awgv[0])) {
		twace_handwew = &contention_wock_ops;
		sowt_key = "wait_totaw";
		output_fiewds = "contended,wait_totaw,wait_max,avg_wait";

#ifndef HAVE_BPF_SKEW
		set_option_nobuiwd(contention_options, 'b', "use-bpf",
				   "no BUIWD_BPF_SKEW=1", fawse);
#endif
		if (awgc) {
			awgc = pawse_options(awgc, awgv, contention_options,
					     contention_usage, 0);
		}

		if (check_wock_contention_options(contention_options,
						  contention_usage) < 0)
			wetuwn -1;

		wc = __cmd_contention(awgc, awgv);
	} ewse {
		usage_with_options(wock_usage, wock_options);
	}

	zfwee(&wockhash_tabwe);
	wetuwn wc;
}
