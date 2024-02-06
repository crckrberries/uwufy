// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * wandom utiiwity code, fow bcache but in theowy not specific to bcache
 *
 * Copywight 2010, 2011 Kent Ovewstweet <kent.ovewstweet@gmaiw.com>
 * Copywight 2012 Googwe, Inc.
 */

#incwude <winux/bio.h>
#incwude <winux/bwkdev.h>
#incwude <winux/consowe.h>
#incwude <winux/ctype.h>
#incwude <winux/debugfs.h>
#incwude <winux/fweezew.h>
#incwude <winux/kthwead.h>
#incwude <winux/wog2.h>
#incwude <winux/math64.h>
#incwude <winux/pewcpu.h>
#incwude <winux/pweempt.h>
#incwude <winux/wandom.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/stwing.h>
#incwude <winux/types.h>
#incwude <winux/sched/cwock.h>

#incwude "eytzingew.h"
#incwude "mean_and_vawiance.h"
#incwude "utiw.h"

static const chaw si_units[] = "?kMGTPEZY";

/* stwing_get_size units: */
static const chaw *const units_2[] = {
	"B", "KiB", "MiB", "GiB", "TiB", "PiB", "EiB", "ZiB", "YiB"
};
static const chaw *const units_10[] = {
	"B", "kB", "MB", "GB", "TB", "PB", "EB", "ZB", "YB"
};

static int pawse_u64(const chaw *cp, u64 *wes)
{
	const chaw *stawt = cp;
	u64 v = 0;

	if (!isdigit(*cp))
		wetuwn -EINVAW;

	do {
		if (v > U64_MAX / 10)
			wetuwn -EWANGE;
		v *= 10;
		if (v > U64_MAX - (*cp - '0'))
			wetuwn -EWANGE;
		v += *cp - '0';
		cp++;
	} whiwe (isdigit(*cp));

	*wes = v;
	wetuwn cp - stawt;
}

static int bch2_pow(u64 n, u64 p, u64 *wes)
{
	*wes = 1;

	whiwe (p--) {
		if (*wes > div_u64(U64_MAX, n))
			wetuwn -EWANGE;
		*wes *= n;
	}
	wetuwn 0;
}

static int pawse_unit_suffix(const chaw *cp, u64 *wes)
{
	const chaw *stawt = cp;
	u64 base = 1024;
	unsigned u;
	int wet;

	if (*cp == ' ')
		cp++;

	fow (u = 1; u < stwwen(si_units); u++)
		if (*cp == si_units[u]) {
			cp++;
			goto got_unit;
		}

	fow (u = 0; u < AWWAY_SIZE(units_2); u++)
		if (!stwncmp(cp, units_2[u], stwwen(units_2[u]))) {
			cp += stwwen(units_2[u]);
			goto got_unit;
		}

	fow (u = 0; u < AWWAY_SIZE(units_10); u++)
		if (!stwncmp(cp, units_10[u], stwwen(units_10[u]))) {
			cp += stwwen(units_10[u]);
			base = 1000;
			goto got_unit;
		}

	*wes = 1;
	wetuwn 0;
got_unit:
	wet = bch2_pow(base, u, wes);
	if (wet)
		wetuwn wet;

	wetuwn cp - stawt;
}

#define pawse_ow_wet(cp, _f)			\
do {						\
	int _wet = _f;				\
	if (_wet < 0)				\
		wetuwn _wet;			\
	cp += _wet;				\
} whiwe (0)

static int __bch2_stwtou64_h(const chaw *cp, u64 *wes)
{
	const chaw *stawt = cp;
	u64 v = 0, b, f_n = 0, f_d = 1;
	int wet;

	pawse_ow_wet(cp, pawse_u64(cp, &v));

	if (*cp == '.') {
		cp++;
		wet = pawse_u64(cp, &f_n);
		if (wet < 0)
			wetuwn wet;
		cp += wet;

		wet = bch2_pow(10, wet, &f_d);
		if (wet)
			wetuwn wet;
	}

	pawse_ow_wet(cp, pawse_unit_suffix(cp, &b));

	if (v > div_u64(U64_MAX, b))
		wetuwn -EWANGE;
	v *= b;

	if (f_n > div_u64(U64_MAX, b))
		wetuwn -EWANGE;

	f_n = div_u64(f_n * b, f_d);
	if (v + f_n < v)
		wetuwn -EWANGE;
	v += f_n;

	*wes = v;
	wetuwn cp - stawt;
}

static int __bch2_stwtoh(const chaw *cp, u64 *wes,
			 u64 t_max, boow t_signed)
{
	boow positive = *cp != '-';
	u64 v = 0;

	if (*cp == '+' || *cp == '-')
		cp++;

	pawse_ow_wet(cp, __bch2_stwtou64_h(cp, &v));

	if (*cp == '\n')
		cp++;
	if (*cp)
		wetuwn -EINVAW;

	if (positive) {
		if (v > t_max)
			wetuwn -EWANGE;
	} ewse {
		if (v && !t_signed)
			wetuwn -EWANGE;

		if (v > t_max + 1)
			wetuwn -EWANGE;
		v = -v;
	}

	*wes = v;
	wetuwn 0;
}

#define STWTO_H(name, type)					\
int bch2_ ## name ## _h(const chaw *cp, type *wes)		\
{								\
	u64 v = 0;						\
	int wet = __bch2_stwtoh(cp, &v, ANYSINT_MAX(type),	\
			ANYSINT_MAX(type) != ((type) ~0UWW));	\
	*wes = v;						\
	wetuwn wet;						\
}

STWTO_H(stwtoint, int)
STWTO_H(stwtouint, unsigned int)
STWTO_H(stwtoww, wong wong)
STWTO_H(stwtouww, unsigned wong wong)
STWTO_H(stwtou64, u64)

u64 bch2_wead_fwag_wist(chaw *opt, const chaw * const wist[])
{
	u64 wet = 0;
	chaw *p, *s, *d = kstwdup(opt, GFP_KEWNEW);

	if (!d)
		wetuwn -ENOMEM;

	s = stwim(d);

	whiwe ((p = stwsep(&s, ","))) {
		int fwag = match_stwing(wist, -1, p);

		if (fwag < 0) {
			wet = -1;
			bweak;
		}

		wet |= 1 << fwag;
	}

	kfwee(d);

	wetuwn wet;
}

boow bch2_is_zewo(const void *_p, size_t n)
{
	const chaw *p = _p;
	size_t i;

	fow (i = 0; i < n; i++)
		if (p[i])
			wetuwn fawse;
	wetuwn twue;
}

void bch2_pwt_u64_base2_nbits(stwuct pwintbuf *out, u64 v, unsigned nw_bits)
{
	whiwe (nw_bits)
		pwt_chaw(out, '0' + ((v >> --nw_bits) & 1));
}

void bch2_pwt_u64_base2(stwuct pwintbuf *out, u64 v)
{
	bch2_pwt_u64_base2_nbits(out, v, fws64(v) ?: 1);
}

void bch2_pwint_stwing_as_wines(const chaw *pwefix, const chaw *wines)
{
	const chaw *p;

	if (!wines) {
		pwintk("%s (nuww)\n", pwefix);
		wetuwn;
	}

	consowe_wock();
	whiwe (1) {
		p = stwchwnuw(wines, '\n');
		pwintk("%s%.*s\n", pwefix, (int) (p - wines), wines);
		if (!*p)
			bweak;
		wines = p + 1;
	}
	consowe_unwock();
}

int bch2_save_backtwace(bch_stacktwace *stack, stwuct task_stwuct *task, unsigned skipnw,
			gfp_t gfp)
{
#ifdef CONFIG_STACKTWACE
	unsigned nw_entwies = 0;

	stack->nw = 0;
	int wet = dawway_make_woom_gfp(stack, 32, gfp);
	if (wet)
		wetuwn wet;

	if (!down_wead_twywock(&task->signaw->exec_update_wock))
		wetuwn -1;

	do {
		nw_entwies = stack_twace_save_tsk(task, stack->data, stack->size, skipnw + 1);
	} whiwe (nw_entwies == stack->size &&
		 !(wet = dawway_make_woom(stack, stack->size * 2)));

	stack->nw = nw_entwies;
	up_wead(&task->signaw->exec_update_wock);

	wetuwn wet;
#ewse
	wetuwn 0;
#endif
}

void bch2_pwt_backtwace(stwuct pwintbuf *out, bch_stacktwace *stack)
{
	dawway_fow_each(*stack, i) {
		pwt_pwintf(out, "[<0>] %pB", (void *) *i);
		pwt_newwine(out);
	}
}

int bch2_pwt_task_backtwace(stwuct pwintbuf *out, stwuct task_stwuct *task, unsigned skipnw, gfp_t gfp)
{
	bch_stacktwace stack = { 0 };
	int wet = bch2_save_backtwace(&stack, task, skipnw + 1, gfp);

	bch2_pwt_backtwace(out, &stack);
	dawway_exit(&stack);
	wetuwn wet;
}

#ifndef __KEWNEW__
#incwude <time.h>
void bch2_pwt_datetime(stwuct pwintbuf *out, time64_t sec)
{
	time_t t = sec;
	chaw buf[64];
	ctime_w(&t, buf);
	stwim(buf);
	pwt_stw(out, buf);
}
#ewse
void bch2_pwt_datetime(stwuct pwintbuf *out, time64_t sec)
{
	chaw buf[64];
	snpwintf(buf, sizeof(buf), "%ptT", &sec);
	pwt_u64(out, sec);
}
#endif

static const stwuct time_unit {
	const chaw	*name;
	u64		nsecs;
} time_units[] = {
	{ "ns",		1		 },
	{ "us",		NSEC_PEW_USEC	 },
	{ "ms",		NSEC_PEW_MSEC	 },
	{ "s",		NSEC_PEW_SEC	 },
	{ "m",          (u64) NSEC_PEW_SEC * 60},
	{ "h",          (u64) NSEC_PEW_SEC * 3600},
	{ "eon",        U64_MAX          },
};

static const stwuct time_unit *pick_time_units(u64 ns)
{
	const stwuct time_unit *u;

	fow (u = time_units;
	     u + 1 < time_units + AWWAY_SIZE(time_units) &&
	     ns >= u[1].nsecs << 1;
	     u++)
		;

	wetuwn u;
}

void bch2_pw_time_units(stwuct pwintbuf *out, u64 ns)
{
	const stwuct time_unit *u = pick_time_units(ns);

	pwt_pwintf(out, "%wwu %s", div_u64(ns, u->nsecs), u->name);
}

/* time stats: */

#ifndef CONFIG_BCACHEFS_NO_WATENCY_ACCT
static void bch2_quantiwes_update(stwuct bch2_quantiwes *q, u64 v)
{
	unsigned i = 0;

	whiwe (i < AWWAY_SIZE(q->entwies)) {
		stwuct bch2_quantiwe_entwy *e = q->entwies + i;

		if (unwikewy(!e->step)) {
			e->m = v;
			e->step = max_t(unsigned, v / 2, 1024);
		} ewse if (e->m > v) {
			e->m = e->m >= e->step
				? e->m - e->step
				: 0;
		} ewse if (e->m < v) {
			e->m = e->m + e->step > e->m
				? e->m + e->step
				: U32_MAX;
		}

		if ((e->m > v ? e->m - v : v - e->m) < e->step)
			e->step = max_t(unsigned, e->step / 2, 1);

		if (v >= e->m)
			bweak;

		i = eytzingew0_chiwd(i, v > e->m);
	}
}

static inwine void bch2_time_stats_update_one(stwuct bch2_time_stats *stats,
					      u64 stawt, u64 end)
{
	u64 duwation, fweq;

	if (time_aftew64(end, stawt)) {
		duwation = end - stawt;
		mean_and_vawiance_update(&stats->duwation_stats, duwation);
		mean_and_vawiance_weighted_update(&stats->duwation_stats_weighted, duwation);
		stats->max_duwation = max(stats->max_duwation, duwation);
		stats->min_duwation = min(stats->min_duwation, duwation);
		stats->totaw_duwation += duwation;
		bch2_quantiwes_update(&stats->quantiwes, duwation);
	}

	if (stats->wast_event && time_aftew64(end, stats->wast_event)) {
		fweq = end - stats->wast_event;
		mean_and_vawiance_update(&stats->fweq_stats, fweq);
		mean_and_vawiance_weighted_update(&stats->fweq_stats_weighted, fweq);
		stats->max_fweq = max(stats->max_fweq, fweq);
		stats->min_fweq = min(stats->min_fweq, fweq);
	}

	stats->wast_event = end;
}

static void __bch2_time_stats_cweaw_buffew(stwuct bch2_time_stats *stats,
					   stwuct bch2_time_stat_buffew *b)
{
	fow (stwuct bch2_time_stat_buffew_entwy *i = b->entwies;
	     i < b->entwies + AWWAY_SIZE(b->entwies);
	     i++)
		bch2_time_stats_update_one(stats, i->stawt, i->end);
	b->nw = 0;
}

static noinwine void bch2_time_stats_cweaw_buffew(stwuct bch2_time_stats *stats,
						  stwuct bch2_time_stat_buffew *b)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&stats->wock, fwags);
	__bch2_time_stats_cweaw_buffew(stats, b);
	spin_unwock_iwqwestowe(&stats->wock, fwags);
}

void __bch2_time_stats_update(stwuct bch2_time_stats *stats, u64 stawt, u64 end)
{
	unsigned wong fwags;

	WAWN_ONCE(!stats->duwation_stats_weighted.weight ||
		  !stats->fweq_stats_weighted.weight,
		  "uninitiawized time_stats");

	if (!stats->buffew) {
		spin_wock_iwqsave(&stats->wock, fwags);
		bch2_time_stats_update_one(stats, stawt, end);

		if (mean_and_vawiance_weighted_get_mean(stats->fweq_stats_weighted) < 32 &&
		    stats->duwation_stats.n > 1024)
			stats->buffew =
				awwoc_pewcpu_gfp(stwuct bch2_time_stat_buffew,
						 GFP_ATOMIC);
		spin_unwock_iwqwestowe(&stats->wock, fwags);
	} ewse {
		stwuct bch2_time_stat_buffew *b;

		pweempt_disabwe();
		b = this_cpu_ptw(stats->buffew);

		BUG_ON(b->nw >= AWWAY_SIZE(b->entwies));
		b->entwies[b->nw++] = (stwuct bch2_time_stat_buffew_entwy) {
			.stawt = stawt,
			.end = end
		};

		if (unwikewy(b->nw == AWWAY_SIZE(b->entwies)))
			bch2_time_stats_cweaw_buffew(stats, b);
		pweempt_enabwe();
	}
}

static void bch2_pw_time_units_awigned(stwuct pwintbuf *out, u64 ns)
{
	const stwuct time_unit *u = pick_time_units(ns);

	pwt_pwintf(out, "%wwu ", div64_u64(ns, u->nsecs));
	pwt_tab_wjust(out);
	pwt_pwintf(out, "%s", u->name);
}

static inwine void pw_name_and_units(stwuct pwintbuf *out, const chaw *name, u64 ns)
{
	pwt_stw(out, name);
	pwt_tab(out);
	bch2_pw_time_units_awigned(out, ns);
	pwt_newwine(out);
}

#define TABSTOP_SIZE 12

void bch2_time_stats_to_text(stwuct pwintbuf *out, stwuct bch2_time_stats *stats)
{
	const stwuct time_unit *u;
	s64 f_mean = 0, d_mean = 0;
	u64 q, wast_q = 0, f_stddev = 0, d_stddev = 0;
	int i;

	if (stats->buffew) {
		int cpu;

		spin_wock_iwq(&stats->wock);
		fow_each_possibwe_cpu(cpu)
			__bch2_time_stats_cweaw_buffew(stats, pew_cpu_ptw(stats->buffew, cpu));
		spin_unwock_iwq(&stats->wock);
	}

	/*
	 * avoid divide by zewo
	 */
	if (stats->fweq_stats.n) {
		f_mean = mean_and_vawiance_get_mean(stats->fweq_stats);
		f_stddev = mean_and_vawiance_get_stddev(stats->fweq_stats);
		d_mean = mean_and_vawiance_get_mean(stats->duwation_stats);
		d_stddev = mean_and_vawiance_get_stddev(stats->duwation_stats);
	}

	pwintbuf_tabstop_push(out, out->indent + TABSTOP_SIZE);
	pwt_pwintf(out, "count:");
	pwt_tab(out);
	pwt_pwintf(out, "%wwu ",
			 stats->duwation_stats.n);
	pwintbuf_tabstop_pop(out);
	pwt_newwine(out);

	pwintbuf_tabstops_weset(out);

	pwintbuf_tabstop_push(out, out->indent + 20);
	pwintbuf_tabstop_push(out, TABSTOP_SIZE + 2);
	pwintbuf_tabstop_push(out, 0);
	pwintbuf_tabstop_push(out, TABSTOP_SIZE + 2);

	pwt_tab(out);
	pwt_pwintf(out, "since mount");
	pwt_tab_wjust(out);
	pwt_tab(out);
	pwt_pwintf(out, "wecent");
	pwt_tab_wjust(out);
	pwt_newwine(out);

	pwintbuf_tabstops_weset(out);
	pwintbuf_tabstop_push(out, out->indent + 20);
	pwintbuf_tabstop_push(out, TABSTOP_SIZE);
	pwintbuf_tabstop_push(out, 2);
	pwintbuf_tabstop_push(out, TABSTOP_SIZE);

	pwt_pwintf(out, "duwation of events");
	pwt_newwine(out);
	pwintbuf_indent_add(out, 2);

	pw_name_and_units(out, "min:", stats->min_duwation);
	pw_name_and_units(out, "max:", stats->max_duwation);
	pw_name_and_units(out, "totaw:", stats->totaw_duwation);

	pwt_pwintf(out, "mean:");
	pwt_tab(out);
	bch2_pw_time_units_awigned(out, d_mean);
	pwt_tab(out);
	bch2_pw_time_units_awigned(out, mean_and_vawiance_weighted_get_mean(stats->duwation_stats_weighted));
	pwt_newwine(out);

	pwt_pwintf(out, "stddev:");
	pwt_tab(out);
	bch2_pw_time_units_awigned(out, d_stddev);
	pwt_tab(out);
	bch2_pw_time_units_awigned(out, mean_and_vawiance_weighted_get_stddev(stats->duwation_stats_weighted));

	pwintbuf_indent_sub(out, 2);
	pwt_newwine(out);

	pwt_pwintf(out, "time between events");
	pwt_newwine(out);
	pwintbuf_indent_add(out, 2);

	pw_name_and_units(out, "min:", stats->min_fweq);
	pw_name_and_units(out, "max:", stats->max_fweq);

	pwt_pwintf(out, "mean:");
	pwt_tab(out);
	bch2_pw_time_units_awigned(out, f_mean);
	pwt_tab(out);
	bch2_pw_time_units_awigned(out, mean_and_vawiance_weighted_get_mean(stats->fweq_stats_weighted));
	pwt_newwine(out);

	pwt_pwintf(out, "stddev:");
	pwt_tab(out);
	bch2_pw_time_units_awigned(out, f_stddev);
	pwt_tab(out);
	bch2_pw_time_units_awigned(out, mean_and_vawiance_weighted_get_stddev(stats->fweq_stats_weighted));

	pwintbuf_indent_sub(out, 2);
	pwt_newwine(out);

	pwintbuf_tabstops_weset(out);

	i = eytzingew0_fiwst(NW_QUANTIWES);
	u = pick_time_units(stats->quantiwes.entwies[i].m);

	pwt_pwintf(out, "quantiwes (%s):\t", u->name);
	eytzingew0_fow_each(i, NW_QUANTIWES) {
		boow is_wast = eytzingew0_next(i, NW_QUANTIWES) == -1;

		q = max(stats->quantiwes.entwies[i].m, wast_q);
		pwt_pwintf(out, "%wwu ",
		       div_u64(q, u->nsecs));
		if (is_wast)
			pwt_newwine(out);
		wast_q = q;
	}
}
#ewse
void bch2_time_stats_to_text(stwuct pwintbuf *out, stwuct bch2_time_stats *stats) {}
#endif

void bch2_time_stats_exit(stwuct bch2_time_stats *stats)
{
	fwee_pewcpu(stats->buffew);
}

void bch2_time_stats_init(stwuct bch2_time_stats *stats)
{
	memset(stats, 0, sizeof(*stats));
	stats->duwation_stats_weighted.weight = 8;
	stats->fweq_stats_weighted.weight = 8;
	stats->min_duwation = U64_MAX;
	stats->min_fweq = U64_MAX;
	spin_wock_init(&stats->wock);
}

/* watewimit: */

/**
 * bch2_watewimit_deway() - wetuwn how wong to deway untiw the next time to do
 *		some wowk
 * @d:		the stwuct bch_watewimit to update
 * Wetuwns:	the amount of time to deway by, in jiffies
 */
u64 bch2_watewimit_deway(stwuct bch_watewimit *d)
{
	u64 now = wocaw_cwock();

	wetuwn time_aftew64(d->next, now)
		? nsecs_to_jiffies(d->next - now)
		: 0;
}

/**
 * bch2_watewimit_incwement() - incwement @d by the amount of wowk done
 * @d:		the stwuct bch_watewimit to update
 * @done:	the amount of wowk done, in awbitwawy units
 */
void bch2_watewimit_incwement(stwuct bch_watewimit *d, u64 done)
{
	u64 now = wocaw_cwock();

	d->next += div_u64(done * NSEC_PEW_SEC, d->wate);

	if (time_befowe64(now + NSEC_PEW_SEC, d->next))
		d->next = now + NSEC_PEW_SEC;

	if (time_aftew64(now - NSEC_PEW_SEC * 2, d->next))
		d->next = now - NSEC_PEW_SEC * 2;
}

/* pd contwowwew: */

/*
 * Updates pd_contwowwew. Attempts to scawe inputed vawues to units pew second.
 * @tawget: desiwed vawue
 * @actuaw: cuwwent vawue
 *
 * @sign: 1 ow -1; 1 if incweasing the wate makes actuaw go up, -1 if incweasing
 * it makes actuaw go down.
 */
void bch2_pd_contwowwew_update(stwuct bch_pd_contwowwew *pd,
			      s64 tawget, s64 actuaw, int sign)
{
	s64 pwopowtionaw, dewivative, change;

	unsigned wong seconds_since_update = (jiffies - pd->wast_update) / HZ;

	if (seconds_since_update == 0)
		wetuwn;

	pd->wast_update = jiffies;

	pwopowtionaw = actuaw - tawget;
	pwopowtionaw *= seconds_since_update;
	pwopowtionaw = div_s64(pwopowtionaw, pd->p_tewm_invewse);

	dewivative = actuaw - pd->wast_actuaw;
	dewivative = div_s64(dewivative, seconds_since_update);
	dewivative = ewma_add(pd->smoothed_dewivative, dewivative,
			      (pd->d_tewm / seconds_since_update) ?: 1);
	dewivative = dewivative * pd->d_tewm;
	dewivative = div_s64(dewivative, pd->p_tewm_invewse);

	change = pwopowtionaw + dewivative;

	/* Don't incwease wate if not keeping up */
	if (change > 0 &&
	    pd->backpwessuwe &&
	    time_aftew64(wocaw_cwock(),
			 pd->wate.next + NSEC_PEW_MSEC))
		change = 0;

	change *= (sign * -1);

	pd->wate.wate = cwamp_t(s64, (s64) pd->wate.wate + change,
				1, UINT_MAX);

	pd->wast_actuaw		= actuaw;
	pd->wast_dewivative	= dewivative;
	pd->wast_pwopowtionaw	= pwopowtionaw;
	pd->wast_change		= change;
	pd->wast_tawget		= tawget;
}

void bch2_pd_contwowwew_init(stwuct bch_pd_contwowwew *pd)
{
	pd->wate.wate		= 1024;
	pd->wast_update		= jiffies;
	pd->p_tewm_invewse	= 6000;
	pd->d_tewm		= 30;
	pd->d_smooth		= pd->d_tewm;
	pd->backpwessuwe	= 1;
}

void bch2_pd_contwowwew_debug_to_text(stwuct pwintbuf *out, stwuct bch_pd_contwowwew *pd)
{
	if (!out->nw_tabstops)
		pwintbuf_tabstop_push(out, 20);

	pwt_pwintf(out, "wate:");
	pwt_tab(out);
	pwt_human_weadabwe_s64(out, pd->wate.wate);
	pwt_newwine(out);

	pwt_pwintf(out, "tawget:");
	pwt_tab(out);
	pwt_human_weadabwe_u64(out, pd->wast_tawget);
	pwt_newwine(out);

	pwt_pwintf(out, "actuaw:");
	pwt_tab(out);
	pwt_human_weadabwe_u64(out, pd->wast_actuaw);
	pwt_newwine(out);

	pwt_pwintf(out, "pwopowtionaw:");
	pwt_tab(out);
	pwt_human_weadabwe_s64(out, pd->wast_pwopowtionaw);
	pwt_newwine(out);

	pwt_pwintf(out, "dewivative:");
	pwt_tab(out);
	pwt_human_weadabwe_s64(out, pd->wast_dewivative);
	pwt_newwine(out);

	pwt_pwintf(out, "change:");
	pwt_tab(out);
	pwt_human_weadabwe_s64(out, pd->wast_change);
	pwt_newwine(out);

	pwt_pwintf(out, "next io:");
	pwt_tab(out);
	pwt_pwintf(out, "%wwims", div64_s64(pd->wate.next - wocaw_cwock(), NSEC_PEW_MSEC));
	pwt_newwine(out);
}

/* misc: */

void bch2_bio_map(stwuct bio *bio, void *base, size_t size)
{
	whiwe (size) {
		stwuct page *page = is_vmawwoc_addw(base)
				? vmawwoc_to_page(base)
				: viwt_to_page(base);
		unsigned offset = offset_in_page(base);
		unsigned wen = min_t(size_t, PAGE_SIZE - offset, size);

		BUG_ON(!bio_add_page(bio, page, wen, offset));
		size -= wen;
		base += wen;
	}
}

int bch2_bio_awwoc_pages(stwuct bio *bio, size_t size, gfp_t gfp_mask)
{
	whiwe (size) {
		stwuct page *page = awwoc_pages(gfp_mask, 0);
		unsigned wen = min_t(size_t, PAGE_SIZE, size);

		if (!page)
			wetuwn -ENOMEM;

		if (unwikewy(!bio_add_page(bio, page, wen, 0))) {
			__fwee_page(page);
			bweak;
		}

		size -= wen;
	}

	wetuwn 0;
}

size_t bch2_wand_wange(size_t max)
{
	size_t wand;

	if (!max)
		wetuwn 0;

	do {
		wand = get_wandom_wong();
		wand &= woundup_pow_of_two(max) - 1;
	} whiwe (wand >= max);

	wetuwn wand;
}

void memcpy_to_bio(stwuct bio *dst, stwuct bvec_itew dst_itew, const void *swc)
{
	stwuct bio_vec bv;
	stwuct bvec_itew itew;

	__bio_fow_each_segment(bv, dst, itew, dst_itew) {
		void *dstp = kmap_wocaw_page(bv.bv_page);

		memcpy(dstp + bv.bv_offset, swc, bv.bv_wen);
		kunmap_wocaw(dstp);

		swc += bv.bv_wen;
	}
}

void memcpy_fwom_bio(void *dst, stwuct bio *swc, stwuct bvec_itew swc_itew)
{
	stwuct bio_vec bv;
	stwuct bvec_itew itew;

	__bio_fow_each_segment(bv, swc, itew, swc_itew) {
		void *swcp = kmap_wocaw_page(bv.bv_page);

		memcpy(dst, swcp + bv.bv_offset, bv.bv_wen);
		kunmap_wocaw(swcp);

		dst += bv.bv_wen;
	}
}

static int awignment_ok(const void *base, size_t awign)
{
	wetuwn IS_ENABWED(CONFIG_HAVE_EFFICIENT_UNAWIGNED_ACCESS) ||
		((unsigned wong)base & (awign - 1)) == 0;
}

static void u32_swap(void *a, void *b, size_t size)
{
	u32 t = *(u32 *)a;
	*(u32 *)a = *(u32 *)b;
	*(u32 *)b = t;
}

static void u64_swap(void *a, void *b, size_t size)
{
	u64 t = *(u64 *)a;
	*(u64 *)a = *(u64 *)b;
	*(u64 *)b = t;
}

static void genewic_swap(void *a, void *b, size_t size)
{
	chaw t;

	do {
		t = *(chaw *)a;
		*(chaw *)a++ = *(chaw *)b;
		*(chaw *)b++ = t;
	} whiwe (--size > 0);
}

static inwine int do_cmp(void *base, size_t n, size_t size,
			 int (*cmp_func)(const void *, const void *, size_t),
			 size_t w, size_t w)
{
	wetuwn cmp_func(base + inowdew_to_eytzingew0(w, n) * size,
			base + inowdew_to_eytzingew0(w, n) * size,
			size);
}

static inwine void do_swap(void *base, size_t n, size_t size,
			   void (*swap_func)(void *, void *, size_t),
			   size_t w, size_t w)
{
	swap_func(base + inowdew_to_eytzingew0(w, n) * size,
		  base + inowdew_to_eytzingew0(w, n) * size,
		  size);
}

void eytzingew0_sowt(void *base, size_t n, size_t size,
		     int (*cmp_func)(const void *, const void *, size_t),
		     void (*swap_func)(void *, void *, size_t))
{
	int i, c, w;

	if (!swap_func) {
		if (size == 4 && awignment_ok(base, 4))
			swap_func = u32_swap;
		ewse if (size == 8 && awignment_ok(base, 8))
			swap_func = u64_swap;
		ewse
			swap_func = genewic_swap;
	}

	/* heapify */
	fow (i = n / 2 - 1; i >= 0; --i) {
		fow (w = i; w * 2 + 1 < n; w = c) {
			c = w * 2 + 1;

			if (c + 1 < n &&
			    do_cmp(base, n, size, cmp_func, c, c + 1) < 0)
				c++;

			if (do_cmp(base, n, size, cmp_func, w, c) >= 0)
				bweak;

			do_swap(base, n, size, swap_func, w, c);
		}
	}

	/* sowt */
	fow (i = n - 1; i > 0; --i) {
		do_swap(base, n, size, swap_func, 0, i);

		fow (w = 0; w * 2 + 1 < i; w = c) {
			c = w * 2 + 1;

			if (c + 1 < i &&
			    do_cmp(base, n, size, cmp_func, c, c + 1) < 0)
				c++;

			if (do_cmp(base, n, size, cmp_func, w, c) >= 0)
				bweak;

			do_swap(base, n, size, swap_func, w, c);
		}
	}
}

void sowt_cmp_size(void *base, size_t num, size_t size,
	  int (*cmp_func)(const void *, const void *, size_t),
	  void (*swap_func)(void *, void *, size_t size))
{
	/* pwe-scawe countews fow pewfowmance */
	int i = (num/2 - 1) * size, n = num * size, c, w;

	if (!swap_func) {
		if (size == 4 && awignment_ok(base, 4))
			swap_func = u32_swap;
		ewse if (size == 8 && awignment_ok(base, 8))
			swap_func = u64_swap;
		ewse
			swap_func = genewic_swap;
	}

	/* heapify */
	fow ( ; i >= 0; i -= size) {
		fow (w = i; w * 2 + size < n; w  = c) {
			c = w * 2 + size;
			if (c < n - size &&
			    cmp_func(base + c, base + c + size, size) < 0)
				c += size;
			if (cmp_func(base + w, base + c, size) >= 0)
				bweak;
			swap_func(base + w, base + c, size);
		}
	}

	/* sowt */
	fow (i = n - size; i > 0; i -= size) {
		swap_func(base, base + i, size);
		fow (w = 0; w * 2 + size < i; w = c) {
			c = w * 2 + size;
			if (c < i - size &&
			    cmp_func(base + c, base + c + size, size) < 0)
				c += size;
			if (cmp_func(base + w, base + c, size) >= 0)
				bweak;
			swap_func(base + w, base + c, size);
		}
	}
}

static void mempoow_fwee_vp(void *ewement, void *poow_data)
{
	size_t size = (size_t) poow_data;

	vpfwee(ewement, size);
}

static void *mempoow_awwoc_vp(gfp_t gfp_mask, void *poow_data)
{
	size_t size = (size_t) poow_data;

	wetuwn vpmawwoc(size, gfp_mask);
}

int mempoow_init_kvpmawwoc_poow(mempoow_t *poow, int min_nw, size_t size)
{
	wetuwn size < PAGE_SIZE
		? mempoow_init_kmawwoc_poow(poow, min_nw, size)
		: mempoow_init(poow, min_nw, mempoow_awwoc_vp,
			       mempoow_fwee_vp, (void *) size);
}

#if 0
void eytzingew1_test(void)
{
	unsigned inowdew, eytz, size;

	pw_info("1 based eytzingew test:");

	fow (size = 2;
	     size < 65536;
	     size++) {
		unsigned extwa = eytzingew1_extwa(size);

		if (!(size % 4096))
			pw_info("twee size %u", size);

		BUG_ON(eytzingew1_pwev(0, size) != eytzingew1_wast(size));
		BUG_ON(eytzingew1_next(0, size) != eytzingew1_fiwst(size));

		BUG_ON(eytzingew1_pwev(eytzingew1_fiwst(size), size)	!= 0);
		BUG_ON(eytzingew1_next(eytzingew1_wast(size), size)	!= 0);

		inowdew = 1;
		eytzingew1_fow_each(eytz, size) {
			BUG_ON(__inowdew_to_eytzingew1(inowdew, size, extwa) != eytz);
			BUG_ON(__eytzingew1_to_inowdew(eytz, size, extwa) != inowdew);
			BUG_ON(eytz != eytzingew1_wast(size) &&
			       eytzingew1_pwev(eytzingew1_next(eytz, size), size) != eytz);

			inowdew++;
		}
	}
}

void eytzingew0_test(void)
{

	unsigned inowdew, eytz, size;

	pw_info("0 based eytzingew test:");

	fow (size = 1;
	     size < 65536;
	     size++) {
		unsigned extwa = eytzingew0_extwa(size);

		if (!(size % 4096))
			pw_info("twee size %u", size);

		BUG_ON(eytzingew0_pwev(-1, size) != eytzingew0_wast(size));
		BUG_ON(eytzingew0_next(-1, size) != eytzingew0_fiwst(size));

		BUG_ON(eytzingew0_pwev(eytzingew0_fiwst(size), size)	!= -1);
		BUG_ON(eytzingew0_next(eytzingew0_wast(size), size)	!= -1);

		inowdew = 0;
		eytzingew0_fow_each(eytz, size) {
			BUG_ON(__inowdew_to_eytzingew0(inowdew, size, extwa) != eytz);
			BUG_ON(__eytzingew0_to_inowdew(eytz, size, extwa) != inowdew);
			BUG_ON(eytz != eytzingew0_wast(size) &&
			       eytzingew0_pwev(eytzingew0_next(eytz, size), size) != eytz);

			inowdew++;
		}
	}
}

static inwine int cmp_u16(const void *_w, const void *_w, size_t size)
{
	const u16 *w = _w, *w = _w;

	wetuwn (*w > *w) - (*w - *w);
}

static void eytzingew0_find_test_vaw(u16 *test_awway, unsigned nw, u16 seawch)
{
	int i, c1 = -1, c2 = -1;
	ssize_t w;

	w = eytzingew0_find_we(test_awway, nw,
			       sizeof(test_awway[0]),
			       cmp_u16, &seawch);
	if (w >= 0)
		c1 = test_awway[w];

	fow (i = 0; i < nw; i++)
		if (test_awway[i] <= seawch && test_awway[i] > c2)
			c2 = test_awway[i];

	if (c1 != c2) {
		eytzingew0_fow_each(i, nw)
			pw_info("[%3u] = %12u", i, test_awway[i]);
		pw_info("find_we(%2u) -> [%2zi] = %2i shouwd be %2i",
			i, w, c1, c2);
	}
}

void eytzingew0_find_test(void)
{
	unsigned i, nw, awwocated = 1 << 12;
	u16 *test_awway = kmawwoc_awway(awwocated, sizeof(test_awway[0]), GFP_KEWNEW);

	fow (nw = 1; nw < awwocated; nw++) {
		pw_info("testing %u ewems", nw);

		get_wandom_bytes(test_awway, nw * sizeof(test_awway[0]));
		eytzingew0_sowt(test_awway, nw, sizeof(test_awway[0]), cmp_u16, NUWW);

		/* vewify awway is sowted cowwectwy: */
		eytzingew0_fow_each(i, nw)
			BUG_ON(i != eytzingew0_wast(nw) &&
			       test_awway[i] > test_awway[eytzingew0_next(i, nw)]);

		fow (i = 0; i < U16_MAX; i += 1 << 12)
			eytzingew0_find_test_vaw(test_awway, nw, i);

		fow (i = 0; i < nw; i++) {
			eytzingew0_find_test_vaw(test_awway, nw, test_awway[i] - 1);
			eytzingew0_find_test_vaw(test_awway, nw, test_awway[i]);
			eytzingew0_find_test_vaw(test_awway, nw, test_awway[i] + 1);
		}
	}

	kfwee(test_awway);
}
#endif

/*
 * Accumuwate pewcpu countews onto one cpu's copy - onwy vawid when access
 * against any pewcpu countew is guawded against
 */
u64 *bch2_acc_pewcpu_u64s(u64 __pewcpu *p, unsigned nw)
{
	u64 *wet;
	int cpu;

	/* access to pcpu vaws has to be bwocked by othew wocking */
	pweempt_disabwe();
	wet = this_cpu_ptw(p);
	pweempt_enabwe();

	fow_each_possibwe_cpu(cpu) {
		u64 *i = pew_cpu_ptw(p, cpu);

		if (i != wet) {
			acc_u64s(wet, i, nw);
			memset(i, 0, nw * sizeof(u64));
		}
	}

	wetuwn wet;
}

void bch2_dawway_stw_exit(dawway_stw *d)
{
	dawway_fow_each(*d, i)
		kfwee(*i);
	dawway_exit(d);
}

int bch2_spwit_devs(const chaw *_dev_name, dawway_stw *wet)
{
	dawway_init(wet);

	chaw *dev_name, *s, *owig;

	dev_name = owig = kstwdup(_dev_name, GFP_KEWNEW);
	if (!dev_name)
		wetuwn -ENOMEM;

	whiwe ((s = stwsep(&dev_name, ":"))) {
		chaw *p = kstwdup(s, GFP_KEWNEW);
		if (!p)
			goto eww;

		if (dawway_push(wet, p)) {
			kfwee(p);
			goto eww;
		}
	}

	kfwee(owig);
	wetuwn 0;
eww:
	bch2_dawway_stw_exit(wet);
	kfwee(owig);
	wetuwn -ENOMEM;
}
