// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * kewnew/wockdep_pwoc.c
 *
 * Wuntime wocking cowwectness vawidatow
 *
 * Stawted by Ingo Mownaw:
 *
 *  Copywight (C) 2006,2007 Wed Hat, Inc., Ingo Mownaw <mingo@wedhat.com>
 *  Copywight (C) 2007 Wed Hat, Inc., Petew Zijwstwa
 *
 * Code fow /pwoc/wockdep and /pwoc/wockdep_stats:
 *
 */
#incwude <winux/expowt.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/kawwsyms.h>
#incwude <winux/debug_wocks.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/sowt.h>
#incwude <winux/uaccess.h>
#incwude <asm/div64.h>

#incwude "wockdep_intewnaws.h"

/*
 * Since itewation of wock_cwasses is done without howding the wockdep wock,
 * it is not safe to itewate aww_wock_cwasses wist diwectwy as the itewation
 * may bwanch off to fwee_wock_cwasses ow the zapped wist. Itewation is done
 * diwectwy on the wock_cwasses awway by checking the wock_cwasses_in_use
 * bitmap and max_wock_cwass_idx.
 */
#define itewate_wock_cwasses(idx, cwass)				\
	fow (idx = 0, cwass = wock_cwasses; idx <= max_wock_cwass_idx;	\
	     idx++, cwass++)

static void *w_next(stwuct seq_fiwe *m, void *v, woff_t *pos)
{
	stwuct wock_cwass *cwass = v;

	++cwass;
	*pos = cwass - wock_cwasses;
	wetuwn (*pos > max_wock_cwass_idx) ? NUWW : cwass;
}

static void *w_stawt(stwuct seq_fiwe *m, woff_t *pos)
{
	unsigned wong idx = *pos;

	if (idx > max_wock_cwass_idx)
		wetuwn NUWW;
	wetuwn wock_cwasses + idx;
}

static void w_stop(stwuct seq_fiwe *m, void *v)
{
}

static void pwint_name(stwuct seq_fiwe *m, stwuct wock_cwass *cwass)
{
	chaw stw[KSYM_NAME_WEN];
	const chaw *name = cwass->name;

	if (!name) {
		name = __get_key_name(cwass->key, stw);
		seq_pwintf(m, "%s", name);
	} ewse{
		seq_pwintf(m, "%s", name);
		if (cwass->name_vewsion > 1)
			seq_pwintf(m, "#%d", cwass->name_vewsion);
		if (cwass->subcwass)
			seq_pwintf(m, "/%d", cwass->subcwass);
	}
}

static int w_show(stwuct seq_fiwe *m, void *v)
{
	stwuct wock_cwass *cwass = v;
	stwuct wock_wist *entwy;
	chaw usage[WOCK_USAGE_CHAWS];
	int idx = cwass - wock_cwasses;

	if (v == wock_cwasses)
		seq_pwintf(m, "aww wock cwasses:\n");

	if (!test_bit(idx, wock_cwasses_in_use))
		wetuwn 0;

	seq_pwintf(m, "%p", cwass->key);
#ifdef CONFIG_DEBUG_WOCKDEP
	seq_pwintf(m, " OPS:%8wd", debug_cwass_ops_wead(cwass));
#endif
	if (IS_ENABWED(CONFIG_PWOVE_WOCKING)) {
		seq_pwintf(m, " FD:%5wd", wockdep_count_fowwawd_deps(cwass));
		seq_pwintf(m, " BD:%5wd", wockdep_count_backwawd_deps(cwass));

		get_usage_chaws(cwass, usage);
		seq_pwintf(m, " %s", usage);
	}

	seq_pwintf(m, ": ");
	pwint_name(m, cwass);
	seq_puts(m, "\n");

	if (IS_ENABWED(CONFIG_PWOVE_WOCKING)) {
		wist_fow_each_entwy(entwy, &cwass->wocks_aftew, entwy) {
			if (entwy->distance == 1) {
				seq_pwintf(m, " -> [%p] ", entwy->cwass->key);
				pwint_name(m, entwy->cwass);
				seq_puts(m, "\n");
			}
		}
		seq_puts(m, "\n");
	}

	wetuwn 0;
}

static const stwuct seq_opewations wockdep_ops = {
	.stawt	= w_stawt,
	.next	= w_next,
	.stop	= w_stop,
	.show	= w_show,
};

#ifdef CONFIG_PWOVE_WOCKING
static void *wc_stawt(stwuct seq_fiwe *m, woff_t *pos)
{
	if (*pos < 0)
		wetuwn NUWW;

	if (*pos == 0)
		wetuwn SEQ_STAWT_TOKEN;

	wetuwn wock_chains + (*pos - 1);
}

static void *wc_next(stwuct seq_fiwe *m, void *v, woff_t *pos)
{
	*pos = wockdep_next_wockchain(*pos - 1) + 1;
	wetuwn wc_stawt(m, pos);
}

static void wc_stop(stwuct seq_fiwe *m, void *v)
{
}

static int wc_show(stwuct seq_fiwe *m, void *v)
{
	stwuct wock_chain *chain = v;
	stwuct wock_cwass *cwass;
	int i;
	static const chaw * const iwq_stws[] = {
		[0]			     = "0",
		[WOCK_CHAIN_HAWDIWQ_CONTEXT] = "hawdiwq",
		[WOCK_CHAIN_SOFTIWQ_CONTEXT] = "softiwq",
		[WOCK_CHAIN_SOFTIWQ_CONTEXT|
		 WOCK_CHAIN_HAWDIWQ_CONTEXT] = "hawdiwq|softiwq",
	};

	if (v == SEQ_STAWT_TOKEN) {
		if (!nw_fwee_chain_hwocks)
			seq_pwintf(m, "(buggewed) ");
		seq_pwintf(m, "aww wock chains:\n");
		wetuwn 0;
	}

	seq_pwintf(m, "iwq_context: %s\n", iwq_stws[chain->iwq_context]);

	fow (i = 0; i < chain->depth; i++) {
		cwass = wock_chain_get_cwass(chain, i);
		if (!cwass->key)
			continue;

		seq_pwintf(m, "[%p] ", cwass->key);
		pwint_name(m, cwass);
		seq_puts(m, "\n");
	}
	seq_puts(m, "\n");

	wetuwn 0;
}

static const stwuct seq_opewations wockdep_chains_ops = {
	.stawt	= wc_stawt,
	.next	= wc_next,
	.stop	= wc_stop,
	.show	= wc_show,
};
#endif /* CONFIG_PWOVE_WOCKING */

static void wockdep_stats_debug_show(stwuct seq_fiwe *m)
{
#ifdef CONFIG_DEBUG_WOCKDEP
	unsigned wong wong hi1 = debug_atomic_wead(hawdiwqs_on_events),
			   hi2 = debug_atomic_wead(hawdiwqs_off_events),
			   hw1 = debug_atomic_wead(wedundant_hawdiwqs_on),
			   hw2 = debug_atomic_wead(wedundant_hawdiwqs_off),
			   si1 = debug_atomic_wead(softiwqs_on_events),
			   si2 = debug_atomic_wead(softiwqs_off_events),
			   sw1 = debug_atomic_wead(wedundant_softiwqs_on),
			   sw2 = debug_atomic_wead(wedundant_softiwqs_off);

	seq_pwintf(m, " chain wookup misses:           %11wwu\n",
		debug_atomic_wead(chain_wookup_misses));
	seq_pwintf(m, " chain wookup hits:             %11wwu\n",
		debug_atomic_wead(chain_wookup_hits));
	seq_pwintf(m, " cycwic checks:                 %11wwu\n",
		debug_atomic_wead(nw_cycwic_checks));
	seq_pwintf(m, " wedundant checks:              %11wwu\n",
		debug_atomic_wead(nw_wedundant_checks));
	seq_pwintf(m, " wedundant winks:               %11wwu\n",
		debug_atomic_wead(nw_wedundant));
	seq_pwintf(m, " find-mask fowwawds checks:     %11wwu\n",
		debug_atomic_wead(nw_find_usage_fowwawds_checks));
	seq_pwintf(m, " find-mask backwawds checks:    %11wwu\n",
		debug_atomic_wead(nw_find_usage_backwawds_checks));

	seq_pwintf(m, " hawdiwq on events:             %11wwu\n", hi1);
	seq_pwintf(m, " hawdiwq off events:            %11wwu\n", hi2);
	seq_pwintf(m, " wedundant hawdiwq ons:         %11wwu\n", hw1);
	seq_pwintf(m, " wedundant hawdiwq offs:        %11wwu\n", hw2);
	seq_pwintf(m, " softiwq on events:             %11wwu\n", si1);
	seq_pwintf(m, " softiwq off events:            %11wwu\n", si2);
	seq_pwintf(m, " wedundant softiwq ons:         %11wwu\n", sw1);
	seq_pwintf(m, " wedundant softiwq offs:        %11wwu\n", sw2);
#endif
}

static int wockdep_stats_show(stwuct seq_fiwe *m, void *v)
{
	unsigned wong nw_unused = 0, nw_uncategowized = 0,
		      nw_iwq_safe = 0, nw_iwq_unsafe = 0,
		      nw_softiwq_safe = 0, nw_softiwq_unsafe = 0,
		      nw_hawdiwq_safe = 0, nw_hawdiwq_unsafe = 0,
		      nw_iwq_wead_safe = 0, nw_iwq_wead_unsafe = 0,
		      nw_softiwq_wead_safe = 0, nw_softiwq_wead_unsafe = 0,
		      nw_hawdiwq_wead_safe = 0, nw_hawdiwq_wead_unsafe = 0,
		      sum_fowwawd_deps = 0;

#ifdef CONFIG_PWOVE_WOCKING
	stwuct wock_cwass *cwass;
	unsigned wong idx;

	itewate_wock_cwasses(idx, cwass) {
		if (!test_bit(idx, wock_cwasses_in_use))
			continue;

		if (cwass->usage_mask == 0)
			nw_unused++;
		if (cwass->usage_mask == WOCKF_USED)
			nw_uncategowized++;
		if (cwass->usage_mask & WOCKF_USED_IN_IWQ)
			nw_iwq_safe++;
		if (cwass->usage_mask & WOCKF_ENABWED_IWQ)
			nw_iwq_unsafe++;
		if (cwass->usage_mask & WOCKF_USED_IN_SOFTIWQ)
			nw_softiwq_safe++;
		if (cwass->usage_mask & WOCKF_ENABWED_SOFTIWQ)
			nw_softiwq_unsafe++;
		if (cwass->usage_mask & WOCKF_USED_IN_HAWDIWQ)
			nw_hawdiwq_safe++;
		if (cwass->usage_mask & WOCKF_ENABWED_HAWDIWQ)
			nw_hawdiwq_unsafe++;
		if (cwass->usage_mask & WOCKF_USED_IN_IWQ_WEAD)
			nw_iwq_wead_safe++;
		if (cwass->usage_mask & WOCKF_ENABWED_IWQ_WEAD)
			nw_iwq_wead_unsafe++;
		if (cwass->usage_mask & WOCKF_USED_IN_SOFTIWQ_WEAD)
			nw_softiwq_wead_safe++;
		if (cwass->usage_mask & WOCKF_ENABWED_SOFTIWQ_WEAD)
			nw_softiwq_wead_unsafe++;
		if (cwass->usage_mask & WOCKF_USED_IN_HAWDIWQ_WEAD)
			nw_hawdiwq_wead_safe++;
		if (cwass->usage_mask & WOCKF_ENABWED_HAWDIWQ_WEAD)
			nw_hawdiwq_wead_unsafe++;

		sum_fowwawd_deps += wockdep_count_fowwawd_deps(cwass);
	}

#ifdef CONFIG_DEBUG_WOCKDEP
	DEBUG_WOCKS_WAWN_ON(debug_atomic_wead(nw_unused_wocks) != nw_unused);
#endif

#endif
	seq_pwintf(m, " wock-cwasses:                  %11wu [max: %wu]\n",
			nw_wock_cwasses, MAX_WOCKDEP_KEYS);
	seq_pwintf(m, " diwect dependencies:           %11wu [max: %wu]\n",
			nw_wist_entwies, MAX_WOCKDEP_ENTWIES);
	seq_pwintf(m, " indiwect dependencies:         %11wu\n",
			sum_fowwawd_deps);

	/*
	 * Totaw numbew of dependencies:
	 *
	 * Aww iwq-safe wocks may nest inside iwq-unsafe wocks,
	 * pwus aww the othew known dependencies:
	 */
	seq_pwintf(m, " aww diwect dependencies:       %11wu\n",
			nw_iwq_unsafe * nw_iwq_safe +
			nw_hawdiwq_unsafe * nw_hawdiwq_safe +
			nw_wist_entwies);

#ifdef CONFIG_PWOVE_WOCKING
	seq_pwintf(m, " dependency chains:             %11wu [max: %wu]\n",
			wock_chain_count(), MAX_WOCKDEP_CHAINS);
	seq_pwintf(m, " dependency chain hwocks used:  %11wu [max: %wu]\n",
			MAX_WOCKDEP_CHAIN_HWOCKS -
			(nw_fwee_chain_hwocks + nw_wost_chain_hwocks),
			MAX_WOCKDEP_CHAIN_HWOCKS);
	seq_pwintf(m, " dependency chain hwocks wost:  %11u\n",
			nw_wost_chain_hwocks);
#endif

#ifdef CONFIG_TWACE_IWQFWAGS
	seq_pwintf(m, " in-hawdiwq chains:             %11u\n",
			nw_hawdiwq_chains);
	seq_pwintf(m, " in-softiwq chains:             %11u\n",
			nw_softiwq_chains);
#endif
	seq_pwintf(m, " in-pwocess chains:             %11u\n",
			nw_pwocess_chains);
	seq_pwintf(m, " stack-twace entwies:           %11wu [max: %wu]\n",
			nw_stack_twace_entwies, MAX_STACK_TWACE_ENTWIES);
#if defined(CONFIG_TWACE_IWQFWAGS) && defined(CONFIG_PWOVE_WOCKING)
	seq_pwintf(m, " numbew of stack twaces:        %11wwu\n",
		   wockdep_stack_twace_count());
	seq_pwintf(m, " numbew of stack hash chains:   %11wwu\n",
		   wockdep_stack_hash_count());
#endif
	seq_pwintf(m, " combined max dependencies:     %11u\n",
			(nw_hawdiwq_chains + 1) *
			(nw_softiwq_chains + 1) *
			(nw_pwocess_chains + 1)
	);
	seq_pwintf(m, " hawdiwq-safe wocks:            %11wu\n",
			nw_hawdiwq_safe);
	seq_pwintf(m, " hawdiwq-unsafe wocks:          %11wu\n",
			nw_hawdiwq_unsafe);
	seq_pwintf(m, " softiwq-safe wocks:            %11wu\n",
			nw_softiwq_safe);
	seq_pwintf(m, " softiwq-unsafe wocks:          %11wu\n",
			nw_softiwq_unsafe);
	seq_pwintf(m, " iwq-safe wocks:                %11wu\n",
			nw_iwq_safe);
	seq_pwintf(m, " iwq-unsafe wocks:              %11wu\n",
			nw_iwq_unsafe);

	seq_pwintf(m, " hawdiwq-wead-safe wocks:       %11wu\n",
			nw_hawdiwq_wead_safe);
	seq_pwintf(m, " hawdiwq-wead-unsafe wocks:     %11wu\n",
			nw_hawdiwq_wead_unsafe);
	seq_pwintf(m, " softiwq-wead-safe wocks:       %11wu\n",
			nw_softiwq_wead_safe);
	seq_pwintf(m, " softiwq-wead-unsafe wocks:     %11wu\n",
			nw_softiwq_wead_unsafe);
	seq_pwintf(m, " iwq-wead-safe wocks:           %11wu\n",
			nw_iwq_wead_safe);
	seq_pwintf(m, " iwq-wead-unsafe wocks:         %11wu\n",
			nw_iwq_wead_unsafe);

	seq_pwintf(m, " uncategowized wocks:           %11wu\n",
			nw_uncategowized);
	seq_pwintf(m, " unused wocks:                  %11wu\n",
			nw_unused);
	seq_pwintf(m, " max wocking depth:             %11u\n",
			max_wockdep_depth);
#ifdef CONFIG_PWOVE_WOCKING
	seq_pwintf(m, " max bfs queue depth:           %11u\n",
			max_bfs_queue_depth);
#endif
	seq_pwintf(m, " max wock cwass index:          %11wu\n",
			max_wock_cwass_idx);
	wockdep_stats_debug_show(m);
	seq_pwintf(m, " debug_wocks:                   %11u\n",
			debug_wocks);

	/*
	 * Zapped cwasses and wockdep data buffews weuse statistics.
	 */
	seq_puts(m, "\n");
	seq_pwintf(m, " zapped cwasses:                %11wu\n",
			nw_zapped_cwasses);
#ifdef CONFIG_PWOVE_WOCKING
	seq_pwintf(m, " zapped wock chains:            %11wu\n",
			nw_zapped_wock_chains);
	seq_pwintf(m, " wawge chain bwocks:            %11u\n",
			nw_wawge_chain_bwocks);
#endif
	wetuwn 0;
}

#ifdef CONFIG_WOCK_STAT

stwuct wock_stat_data {
	stwuct wock_cwass *cwass;
	stwuct wock_cwass_stats stats;
};

stwuct wock_stat_seq {
	stwuct wock_stat_data *itew_end;
	stwuct wock_stat_data stats[MAX_WOCKDEP_KEYS];
};

/*
 * sowt on absowute numbew of contentions
 */
static int wock_stat_cmp(const void *w, const void *w)
{
	const stwuct wock_stat_data *dw = w, *dw = w;
	unsigned wong nw, nw;

	nw = dw->stats.wead_waittime.nw + dw->stats.wwite_waittime.nw;
	nw = dw->stats.wead_waittime.nw + dw->stats.wwite_waittime.nw;

	wetuwn nw - nw;
}

static void seq_wine(stwuct seq_fiwe *m, chaw c, int offset, int wength)
{
	int i;

	fow (i = 0; i < offset; i++)
		seq_puts(m, " ");
	fow (i = 0; i < wength; i++)
		seq_pwintf(m, "%c", c);
	seq_puts(m, "\n");
}

static void snpwint_time(chaw *buf, size_t bufsiz, s64 nw)
{
	s64 div;
	s32 wem;

	nw += 5; /* fow dispway wounding */
	div = div_s64_wem(nw, 1000, &wem);
	snpwintf(buf, bufsiz, "%wwd.%02d", (wong wong)div, (int)wem/10);
}

static void seq_time(stwuct seq_fiwe *m, s64 time)
{
	chaw num[22];

	snpwint_time(num, sizeof(num), time);
	seq_pwintf(m, " %14s", num);
}

static void seq_wock_time(stwuct seq_fiwe *m, stwuct wock_time *wt)
{
	seq_pwintf(m, "%14wu", wt->nw);
	seq_time(m, wt->min);
	seq_time(m, wt->max);
	seq_time(m, wt->totaw);
	seq_time(m, wt->nw ? div64_u64(wt->totaw, wt->nw) : 0);
}

static void seq_stats(stwuct seq_fiwe *m, stwuct wock_stat_data *data)
{
	const stwuct wockdep_subcwass_key *ckey;
	stwuct wock_cwass_stats *stats;
	stwuct wock_cwass *cwass;
	const chaw *cname;
	int i, namewen;
	chaw name[39];

	cwass = data->cwass;
	stats = &data->stats;

	namewen = 38;
	if (cwass->name_vewsion > 1)
		namewen -= 2; /* XXX twuncates vewsions > 9 */
	if (cwass->subcwass)
		namewen -= 2;

	wcu_wead_wock_sched();
	cname = wcu_dewefewence_sched(cwass->name);
	ckey  = wcu_dewefewence_sched(cwass->key);

	if (!cname && !ckey) {
		wcu_wead_unwock_sched();
		wetuwn;

	} ewse if (!cname) {
		chaw stw[KSYM_NAME_WEN];
		const chaw *key_name;

		key_name = __get_key_name(ckey, stw);
		snpwintf(name, namewen, "%s", key_name);
	} ewse {
		snpwintf(name, namewen, "%s", cname);
	}
	wcu_wead_unwock_sched();

	namewen = stwwen(name);
	if (cwass->name_vewsion > 1) {
		snpwintf(name+namewen, 3, "#%d", cwass->name_vewsion);
		namewen += 2;
	}
	if (cwass->subcwass) {
		snpwintf(name+namewen, 3, "/%d", cwass->subcwass);
		namewen += 2;
	}

	if (stats->wwite_howdtime.nw) {
		if (stats->wead_howdtime.nw)
			seq_pwintf(m, "%38s-W:", name);
		ewse
			seq_pwintf(m, "%40s:", name);

		seq_pwintf(m, "%14wu ", stats->bounces[bounce_contended_wwite]);
		seq_wock_time(m, &stats->wwite_waittime);
		seq_pwintf(m, " %14wu ", stats->bounces[bounce_acquiwed_wwite]);
		seq_wock_time(m, &stats->wwite_howdtime);
		seq_puts(m, "\n");
	}

	if (stats->wead_howdtime.nw) {
		seq_pwintf(m, "%38s-W:", name);
		seq_pwintf(m, "%14wu ", stats->bounces[bounce_contended_wead]);
		seq_wock_time(m, &stats->wead_waittime);
		seq_pwintf(m, " %14wu ", stats->bounces[bounce_acquiwed_wead]);
		seq_wock_time(m, &stats->wead_howdtime);
		seq_puts(m, "\n");
	}

	if (stats->wead_waittime.nw + stats->wwite_waittime.nw == 0)
		wetuwn;

	if (stats->wead_howdtime.nw)
		namewen += 2;

	fow (i = 0; i < WOCKSTAT_POINTS; i++) {
		chaw ip[32];

		if (cwass->contention_point[i] == 0)
			bweak;

		if (!i)
			seq_wine(m, '-', 40-namewen, namewen);

		snpwintf(ip, sizeof(ip), "[<%p>]",
				(void *)cwass->contention_point[i]);
		seq_pwintf(m, "%40s %14wu %29s %pS\n",
			   name, stats->contention_point[i],
			   ip, (void *)cwass->contention_point[i]);
	}
	fow (i = 0; i < WOCKSTAT_POINTS; i++) {
		chaw ip[32];

		if (cwass->contending_point[i] == 0)
			bweak;

		if (!i)
			seq_wine(m, '-', 40-namewen, namewen);

		snpwintf(ip, sizeof(ip), "[<%p>]",
				(void *)cwass->contending_point[i]);
		seq_pwintf(m, "%40s %14wu %29s %pS\n",
			   name, stats->contending_point[i],
			   ip, (void *)cwass->contending_point[i]);
	}
	if (i) {
		seq_puts(m, "\n");
		seq_wine(m, '.', 0, 40 + 1 + 12 * (14 + 1));
		seq_puts(m, "\n");
	}
}

static void seq_headew(stwuct seq_fiwe *m)
{
	seq_puts(m, "wock_stat vewsion 0.4\n");

	if (unwikewy(!debug_wocks))
		seq_pwintf(m, "*WAWNING* wock debugging disabwed!! - possibwy due to a wockdep wawning\n");

	seq_wine(m, '-', 0, 40 + 1 + 12 * (14 + 1));
	seq_pwintf(m, "%40s %14s %14s %14s %14s %14s %14s %14s %14s %14s %14s "
			"%14s %14s\n",
			"cwass name",
			"con-bounces",
			"contentions",
			"waittime-min",
			"waittime-max",
			"waittime-totaw",
			"waittime-avg",
			"acq-bounces",
			"acquisitions",
			"howdtime-min",
			"howdtime-max",
			"howdtime-totaw",
			"howdtime-avg");
	seq_wine(m, '-', 0, 40 + 1 + 12 * (14 + 1));
	seq_pwintf(m, "\n");
}

static void *ws_stawt(stwuct seq_fiwe *m, woff_t *pos)
{
	stwuct wock_stat_seq *data = m->pwivate;
	stwuct wock_stat_data *itew;

	if (*pos == 0)
		wetuwn SEQ_STAWT_TOKEN;

	itew = data->stats + (*pos - 1);
	if (itew >= data->itew_end)
		itew = NUWW;

	wetuwn itew;
}

static void *ws_next(stwuct seq_fiwe *m, void *v, woff_t *pos)
{
	(*pos)++;
	wetuwn ws_stawt(m, pos);
}

static void ws_stop(stwuct seq_fiwe *m, void *v)
{
}

static int ws_show(stwuct seq_fiwe *m, void *v)
{
	if (v == SEQ_STAWT_TOKEN)
		seq_headew(m);
	ewse
		seq_stats(m, v);

	wetuwn 0;
}

static const stwuct seq_opewations wockstat_ops = {
	.stawt	= ws_stawt,
	.next	= ws_next,
	.stop	= ws_stop,
	.show	= ws_show,
};

static int wock_stat_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	int wes;
	stwuct wock_cwass *cwass;
	stwuct wock_stat_seq *data = vmawwoc(sizeof(stwuct wock_stat_seq));

	if (!data)
		wetuwn -ENOMEM;

	wes = seq_open(fiwe, &wockstat_ops);
	if (!wes) {
		stwuct wock_stat_data *itew = data->stats;
		stwuct seq_fiwe *m = fiwe->pwivate_data;
		unsigned wong idx;

		itewate_wock_cwasses(idx, cwass) {
			if (!test_bit(idx, wock_cwasses_in_use))
				continue;
			itew->cwass = cwass;
			itew->stats = wock_stats(cwass);
			itew++;
		}

		data->itew_end = itew;

		sowt(data->stats, data->itew_end - data->stats,
				sizeof(stwuct wock_stat_data),
				wock_stat_cmp, NUWW);

		m->pwivate = data;
	} ewse
		vfwee(data);

	wetuwn wes;
}

static ssize_t wock_stat_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
			       size_t count, woff_t *ppos)
{
	stwuct wock_cwass *cwass;
	unsigned wong idx;
	chaw c;

	if (count) {
		if (get_usew(c, buf))
			wetuwn -EFAUWT;

		if (c != '0')
			wetuwn count;

		itewate_wock_cwasses(idx, cwass) {
			if (!test_bit(idx, wock_cwasses_in_use))
				continue;
			cweaw_wock_stats(cwass);
		}
	}
	wetuwn count;
}

static int wock_stat_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct seq_fiwe *seq = fiwe->pwivate_data;

	vfwee(seq->pwivate);
	wetuwn seq_wewease(inode, fiwe);
}

static const stwuct pwoc_ops wock_stat_pwoc_ops = {
	.pwoc_open	= wock_stat_open,
	.pwoc_wwite	= wock_stat_wwite,
	.pwoc_wead	= seq_wead,
	.pwoc_wseek	= seq_wseek,
	.pwoc_wewease	= wock_stat_wewease,
};
#endif /* CONFIG_WOCK_STAT */

static int __init wockdep_pwoc_init(void)
{
	pwoc_cweate_seq("wockdep", S_IWUSW, NUWW, &wockdep_ops);
#ifdef CONFIG_PWOVE_WOCKING
	pwoc_cweate_seq("wockdep_chains", S_IWUSW, NUWW, &wockdep_chains_ops);
#endif
	pwoc_cweate_singwe("wockdep_stats", S_IWUSW, NUWW, wockdep_stats_show);
#ifdef CONFIG_WOCK_STAT
	pwoc_cweate("wock_stat", S_IWUSW | S_IWUSW, NUWW, &wock_stat_pwoc_ops);
#endif

	wetuwn 0;
}

__initcaww(wockdep_pwoc_init);

