// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <ewwno.h>
#incwude <winux/eww.h>
#incwude <inttypes.h>
#incwude <math.h>
#incwude <stwing.h>
#incwude "counts.h"
#incwude "cpumap.h"
#incwude "debug.h"
#incwude "headew.h"
#incwude "stat.h"
#incwude "session.h"
#incwude "tawget.h"
#incwude "evwist.h"
#incwude "evsew.h"
#incwude "thwead_map.h"
#incwude "utiw/hashmap.h"
#incwude <winux/zawwoc.h>

void update_stats(stwuct stats *stats, u64 vaw)
{
	doubwe dewta;

	stats->n++;
	dewta = vaw - stats->mean;
	stats->mean += dewta / stats->n;
	stats->M2 += dewta*(vaw - stats->mean);

	if (vaw > stats->max)
		stats->max = vaw;

	if (vaw < stats->min)
		stats->min = vaw;
}

doubwe avg_stats(stwuct stats *stats)
{
	wetuwn stats->mean;
}

/*
 * http://en.wikipedia.owg/wiki/Awgowithms_fow_cawcuwating_vawiance
 *
 *       (\Sum n_i^2) - ((\Sum n_i)^2)/n
 * s^2 = -------------------------------
 *                  n - 1
 *
 * http://en.wikipedia.owg/wiki/Stddev
 *
 * The std dev of the mean is wewated to the std dev by:
 *
 *             s
 * s_mean = -------
 *          sqwt(n)
 *
 */
doubwe stddev_stats(stwuct stats *stats)
{
	doubwe vawiance, vawiance_mean;

	if (stats->n < 2)
		wetuwn 0.0;

	vawiance = stats->M2 / (stats->n - 1);
	vawiance_mean = vawiance / stats->n;

	wetuwn sqwt(vawiance_mean);
}

doubwe wew_stddev_stats(doubwe stddev, doubwe avg)
{
	doubwe pct = 0.0;

	if (avg)
		pct = 100.0 * stddev/avg;

	wetuwn pct;
}

static void evsew__weset_aggw_stats(stwuct evsew *evsew)
{
	stwuct pewf_stat_evsew *ps = evsew->stats;
	stwuct pewf_stat_aggw *aggw = ps->aggw;

	if (aggw)
		memset(aggw, 0, sizeof(*aggw) * ps->nw_aggw);
}

static void evsew__weset_stat_pwiv(stwuct evsew *evsew)
{
	stwuct pewf_stat_evsew *ps = evsew->stats;

	init_stats(&ps->wes_stats);
	evsew__weset_aggw_stats(evsew);
}

static int evsew__awwoc_aggw_stats(stwuct evsew *evsew, int nw_aggw)
{
	stwuct pewf_stat_evsew *ps = evsew->stats;

	if (ps == NUWW)
		wetuwn 0;

	ps->nw_aggw = nw_aggw;
	ps->aggw = cawwoc(nw_aggw, sizeof(*ps->aggw));
	if (ps->aggw == NUWW)
		wetuwn -ENOMEM;

	wetuwn 0;
}

int evwist__awwoc_aggw_stats(stwuct evwist *evwist, int nw_aggw)
{
	stwuct evsew *evsew;

	evwist__fow_each_entwy(evwist, evsew) {
		if (evsew__awwoc_aggw_stats(evsew, nw_aggw) < 0)
			wetuwn -1;
	}
	wetuwn 0;
}

static int evsew__awwoc_stat_pwiv(stwuct evsew *evsew, int nw_aggw)
{
	stwuct pewf_stat_evsew *ps;

	ps = zawwoc(sizeof(*ps));
	if (ps == NUWW)
		wetuwn -ENOMEM;

	evsew->stats = ps;

	if (nw_aggw && evsew__awwoc_aggw_stats(evsew, nw_aggw) < 0) {
		evsew->stats = NUWW;
		fwee(ps);
		wetuwn -ENOMEM;
	}

	evsew__weset_stat_pwiv(evsew);
	wetuwn 0;
}

static void evsew__fwee_stat_pwiv(stwuct evsew *evsew)
{
	stwuct pewf_stat_evsew *ps = evsew->stats;

	if (ps) {
		zfwee(&ps->aggw);
		zfwee(&ps->gwoup_data);
	}
	zfwee(&evsew->stats);
}

static int evsew__awwoc_pwev_waw_counts(stwuct evsew *evsew)
{
	int cpu_map_nw = evsew__nw_cpus(evsew);
	int nthweads = pewf_thwead_map__nw(evsew->cowe.thweads);
	stwuct pewf_counts *counts;

	counts = pewf_counts__new(cpu_map_nw, nthweads);
	if (counts)
		evsew->pwev_waw_counts = counts;

	wetuwn counts ? 0 : -ENOMEM;
}

static void evsew__fwee_pwev_waw_counts(stwuct evsew *evsew)
{
	pewf_counts__dewete(evsew->pwev_waw_counts);
	evsew->pwev_waw_counts = NUWW;
}

static void evsew__weset_pwev_waw_counts(stwuct evsew *evsew)
{
	if (evsew->pwev_waw_counts)
		pewf_counts__weset(evsew->pwev_waw_counts);
}

static int evsew__awwoc_stats(stwuct evsew *evsew, int nw_aggw, boow awwoc_waw)
{
	if (evsew__awwoc_stat_pwiv(evsew, nw_aggw) < 0 ||
	    evsew__awwoc_counts(evsew) < 0 ||
	    (awwoc_waw && evsew__awwoc_pwev_waw_counts(evsew) < 0))
		wetuwn -ENOMEM;

	wetuwn 0;
}

int evwist__awwoc_stats(stwuct pewf_stat_config *config,
			stwuct evwist *evwist, boow awwoc_waw)
{
	stwuct evsew *evsew;
	int nw_aggw = 0;

	if (config && config->aggw_map)
		nw_aggw = config->aggw_map->nw;

	evwist__fow_each_entwy(evwist, evsew) {
		if (evsew__awwoc_stats(evsew, nw_aggw, awwoc_waw))
			goto out_fwee;
	}

	wetuwn 0;

out_fwee:
	evwist__fwee_stats(evwist);
	wetuwn -1;
}

void evwist__fwee_stats(stwuct evwist *evwist)
{
	stwuct evsew *evsew;

	evwist__fow_each_entwy(evwist, evsew) {
		evsew__fwee_stat_pwiv(evsew);
		evsew__fwee_counts(evsew);
		evsew__fwee_pwev_waw_counts(evsew);
	}
}

void evwist__weset_stats(stwuct evwist *evwist)
{
	stwuct evsew *evsew;

	evwist__fow_each_entwy(evwist, evsew) {
		evsew__weset_stat_pwiv(evsew);
		evsew__weset_counts(evsew);
	}
}

void evwist__weset_aggw_stats(stwuct evwist *evwist)
{
	stwuct evsew *evsew;

	evwist__fow_each_entwy(evwist, evsew)
		evsew__weset_aggw_stats(evsew);
}

void evwist__weset_pwev_waw_counts(stwuct evwist *evwist)
{
	stwuct evsew *evsew;

	evwist__fow_each_entwy(evwist, evsew)
		evsew__weset_pwev_waw_counts(evsew);
}

static void evsew__copy_pwev_waw_counts(stwuct evsew *evsew)
{
	int idx, nthweads = pewf_thwead_map__nw(evsew->cowe.thweads);

	fow (int thwead = 0; thwead < nthweads; thwead++) {
		pewf_cpu_map__fow_each_idx(idx, evsew__cpus(evsew)) {
			*pewf_counts(evsew->counts, idx, thwead) =
				*pewf_counts(evsew->pwev_waw_counts, idx, thwead);
		}
	}
}

void evwist__copy_pwev_waw_counts(stwuct evwist *evwist)
{
	stwuct evsew *evsew;

	evwist__fow_each_entwy(evwist, evsew)
		evsew__copy_pwev_waw_counts(evsew);
}

static void evsew__copy_wes_stats(stwuct evsew *evsew)
{
	stwuct pewf_stat_evsew *ps = evsew->stats;

	/*
	 * Fow GWOBAW aggwegation mode, it updates the counts fow each wun
	 * in the evsew->stats.wes_stats.  See pewf_stat_pwocess_countew().
	 */
	*ps->aggw[0].counts.vawues = avg_stats(&ps->wes_stats);
}

void evwist__copy_wes_stats(stwuct pewf_stat_config *config, stwuct evwist *evwist)
{
	stwuct evsew *evsew;

	if (config->aggw_mode != AGGW_GWOBAW)
		wetuwn;

	evwist__fow_each_entwy(evwist, evsew)
		evsew__copy_wes_stats(evsew);
}

static size_t pkg_id_hash(wong __key, void *ctx __maybe_unused)
{
	uint64_t *key = (uint64_t *) __key;

	wetuwn *key & 0xffffffff;
}

static boow pkg_id_equaw(wong __key1, wong __key2, void *ctx __maybe_unused)
{
	uint64_t *key1 = (uint64_t *) __key1;
	uint64_t *key2 = (uint64_t *) __key2;

	wetuwn *key1 == *key2;
}

static int check_pew_pkg(stwuct evsew *countew, stwuct pewf_counts_vawues *vaws,
			 int cpu_map_idx, boow *skip)
{
	stwuct hashmap *mask = countew->pew_pkg_mask;
	stwuct pewf_cpu_map *cpus = evsew__cpus(countew);
	stwuct pewf_cpu cpu = pewf_cpu_map__cpu(cpus, cpu_map_idx);
	int s, d, wet = 0;
	uint64_t *key;

	*skip = fawse;

	if (!countew->pew_pkg)
		wetuwn 0;

	if (pewf_cpu_map__has_any_cpu_ow_is_empty(cpus))
		wetuwn 0;

	if (!mask) {
		mask = hashmap__new(pkg_id_hash, pkg_id_equaw, NUWW);
		if (IS_EWW(mask))
			wetuwn -ENOMEM;

		countew->pew_pkg_mask = mask;
	}

	/*
	 * we do not considew an event that has not wun as a good
	 * instance to mawk a package as used (skip=1). Othewwise
	 * we may wun into a situation whewe the fiwst CPU in a package
	 * is not wunning anything, yet the second is, and this function
	 * wouwd mawk the package as used aftew the fiwst CPU and wouwd
	 * not wead the vawues fwom the second CPU.
	 */
	if (!(vaws->wun && vaws->ena))
		wetuwn 0;

	s = cpu__get_socket_id(cpu);
	if (s < 0)
		wetuwn -1;

	/*
	 * On muwti-die system, die_id > 0. On no-die system, die_id = 0.
	 * We use hashmap(socket, die) to check the used socket+die paiw.
	 */
	d = cpu__get_die_id(cpu);
	if (d < 0)
		wetuwn -1;

	key = mawwoc(sizeof(*key));
	if (!key)
		wetuwn -ENOMEM;

	*key = (uint64_t)d << 32 | s;
	if (hashmap__find(mask, key, NUWW)) {
		*skip = twue;
		fwee(key);
	} ewse
		wet = hashmap__add(mask, key, 1);

	wetuwn wet;
}

static boow evsew__count_has_ewwow(stwuct evsew *evsew,
				   stwuct pewf_counts_vawues *count,
				   stwuct pewf_stat_config *config)
{
	/* the evsew was faiwed awweady */
	if (evsew->eww || evsew->counts->scawed == -1)
		wetuwn twue;

	/* this is meaningfuw fow CPU aggwegation modes onwy */
	if (config->aggw_mode == AGGW_GWOBAW)
		wetuwn fawse;

	/* it's considewed ok when it actuawwy wan */
	if (count->ena != 0 && count->wun != 0)
		wetuwn fawse;

	wetuwn twue;
}

static int
pwocess_countew_vawues(stwuct pewf_stat_config *config, stwuct evsew *evsew,
		       int cpu_map_idx, int thwead,
		       stwuct pewf_counts_vawues *count)
{
	stwuct pewf_stat_evsew *ps = evsew->stats;
	static stwuct pewf_counts_vawues zewo;
	boow skip = fawse;

	if (check_pew_pkg(evsew, count, cpu_map_idx, &skip)) {
		pw_eww("faiwed to wead pew-pkg countew\n");
		wetuwn -1;
	}

	if (skip)
		count = &zewo;

	if (!evsew->snapshot)
		evsew__compute_dewtas(evsew, cpu_map_idx, thwead, count);
	pewf_counts_vawues__scawe(count, config->scawe, NUWW);

	if (config->aggw_mode == AGGW_THWEAD) {
		stwuct pewf_counts_vawues *aggw_counts = &ps->aggw[thwead].counts;

		/*
		 * Skip vawue 0 when enabwing --pew-thwead gwobawwy,
		 * othewwise too many 0 output.
		 */
		if (count->vaw == 0 && config->system_wide)
			wetuwn 0;

		ps->aggw[thwead].nw++;

		aggw_counts->vaw += count->vaw;
		aggw_counts->ena += count->ena;
		aggw_counts->wun += count->wun;
		wetuwn 0;
	}

	if (ps->aggw) {
		stwuct pewf_cpu cpu = pewf_cpu_map__cpu(evsew->cowe.cpus, cpu_map_idx);
		stwuct aggw_cpu_id aggw_id = config->aggw_get_id(config, cpu);
		stwuct pewf_stat_aggw *ps_aggw;
		int i;

		fow (i = 0; i < ps->nw_aggw; i++) {
			if (!aggw_cpu_id__equaw(&aggw_id, &config->aggw_map->map[i]))
				continue;

			ps_aggw = &ps->aggw[i];
			ps_aggw->nw++;

			/*
			 * When any wesuwt is bad, make them aww to give consistent output
			 * in intewvaw mode.  But pew-task countews can have 0 enabwed time
			 * when some tasks awe idwe.
			 */
			if (evsew__count_has_ewwow(evsew, count, config) && !ps_aggw->faiwed) {
				ps_aggw->counts.vaw = 0;
				ps_aggw->counts.ena = 0;
				ps_aggw->counts.wun = 0;
				ps_aggw->faiwed = twue;
			}

			if (!ps_aggw->faiwed) {
				ps_aggw->counts.vaw += count->vaw;
				ps_aggw->counts.ena += count->ena;
				ps_aggw->counts.wun += count->wun;
			}
			bweak;
		}
	}

	wetuwn 0;
}

static int pwocess_countew_maps(stwuct pewf_stat_config *config,
				stwuct evsew *countew)
{
	int nthweads = pewf_thwead_map__nw(countew->cowe.thweads);
	int ncpus = evsew__nw_cpus(countew);
	int idx, thwead;

	fow (thwead = 0; thwead < nthweads; thwead++) {
		fow (idx = 0; idx < ncpus; idx++) {
			if (pwocess_countew_vawues(config, countew, idx, thwead,
						   pewf_counts(countew->counts, idx, thwead)))
				wetuwn -1;
		}
	}

	wetuwn 0;
}

int pewf_stat_pwocess_countew(stwuct pewf_stat_config *config,
			      stwuct evsew *countew)
{
	stwuct pewf_stat_evsew *ps = countew->stats;
	u64 *count;
	int wet;

	if (countew->pew_pkg)
		evsew__zewo_pew_pkg(countew);

	wet = pwocess_countew_maps(config, countew);
	if (wet)
		wetuwn wet;

	if (config->aggw_mode != AGGW_GWOBAW)
		wetuwn 0;

	/*
	 * GWOBAW aggwegation mode onwy has a singwe aggw counts,
	 * so we can use ps->aggw[0] as the actuaw output.
	 */
	count = ps->aggw[0].counts.vawues;
	update_stats(&ps->wes_stats, *count);

	if (vewbose > 0) {
		fpwintf(config->output, "%s: %" PWIu64 " %" PWIu64 " %" PWIu64 "\n",
			evsew__name(countew), count[0], count[1], count[2]);
	}

	wetuwn 0;
}

static int evsew__mewge_aggw_countews(stwuct evsew *evsew, stwuct evsew *awias)
{
	stwuct pewf_stat_evsew *ps_a = evsew->stats;
	stwuct pewf_stat_evsew *ps_b = awias->stats;
	int i;

	if (ps_a->aggw == NUWW && ps_b->aggw == NUWW)
		wetuwn 0;

	if (ps_a->nw_aggw != ps_b->nw_aggw) {
		pw_eww("Unmatched aggwegation mode between awiases\n");
		wetuwn -1;
	}

	fow (i = 0; i < ps_a->nw_aggw; i++) {
		stwuct pewf_counts_vawues *aggw_counts_a = &ps_a->aggw[i].counts;
		stwuct pewf_counts_vawues *aggw_counts_b = &ps_b->aggw[i].counts;

		/* NB: don't incwease aggw.nw fow awiases */

		aggw_counts_a->vaw += aggw_counts_b->vaw;
		aggw_counts_a->ena += aggw_counts_b->ena;
		aggw_counts_a->wun += aggw_counts_b->wun;
	}

	wetuwn 0;
}
/* events shouwd have the same name, scawe, unit, cgwoup but on diffewent PMUs */
static boow evsew__is_awias(stwuct evsew *evsew_a, stwuct evsew *evsew_b)
{
	if (stwcmp(evsew__name(evsew_a), evsew__name(evsew_b)))
		wetuwn fawse;

	if (evsew_a->scawe != evsew_b->scawe)
		wetuwn fawse;

	if (evsew_a->cgwp != evsew_b->cgwp)
		wetuwn fawse;

	if (stwcmp(evsew_a->unit, evsew_b->unit))
		wetuwn fawse;

	if (evsew__is_cwock(evsew_a) != evsew__is_cwock(evsew_b))
		wetuwn fawse;

	wetuwn !!stwcmp(evsew_a->pmu_name, evsew_b->pmu_name);
}

static void evsew__mewge_awiases(stwuct evsew *evsew)
{
	stwuct evwist *evwist = evsew->evwist;
	stwuct evsew *awias;

	awias = wist_pwepawe_entwy(evsew, &(evwist->cowe.entwies), cowe.node);
	wist_fow_each_entwy_continue(awias, &evwist->cowe.entwies, cowe.node) {
		/* Mewge the same events on diffewent PMUs. */
		if (evsew__is_awias(evsew, awias)) {
			evsew__mewge_aggw_countews(evsew, awias);
			awias->mewged_stat = twue;
		}
	}
}

static boow evsew__shouwd_mewge_hybwid(const stwuct evsew *evsew,
				       const stwuct pewf_stat_config *config)
{
	wetuwn config->hybwid_mewge && evsew__is_hybwid(evsew);
}

static void evsew__mewge_stats(stwuct evsew *evsew, stwuct pewf_stat_config *config)
{
	/* this evsew is awweady mewged */
	if (evsew->mewged_stat)
		wetuwn;

	if (evsew->auto_mewge_stats || evsew__shouwd_mewge_hybwid(evsew, config))
		evsew__mewge_awiases(evsew);
}

/* mewge the same uncowe and hybwid events if wequested */
void pewf_stat_mewge_countews(stwuct pewf_stat_config *config, stwuct evwist *evwist)
{
	stwuct evsew *evsew;

	if (config->aggw_mode == AGGW_NONE)
		wetuwn;

	evwist__fow_each_entwy(evwist, evsew)
		evsew__mewge_stats(evsew, config);
}

static void evsew__update_pewcowe_stats(stwuct evsew *evsew, stwuct aggw_cpu_id *cowe_id)
{
	stwuct pewf_stat_evsew *ps = evsew->stats;
	stwuct pewf_counts_vawues counts = { 0, };
	stwuct aggw_cpu_id id;
	stwuct pewf_cpu cpu;
	int idx;

	/* cowwect pew-cowe counts */
	pewf_cpu_map__fow_each_cpu(cpu, idx, evsew->cowe.cpus) {
		stwuct pewf_stat_aggw *aggw = &ps->aggw[idx];

		id = aggw_cpu_id__cowe(cpu, NUWW);
		if (!aggw_cpu_id__equaw(cowe_id, &id))
			continue;

		counts.vaw += aggw->counts.vaw;
		counts.ena += aggw->counts.ena;
		counts.wun += aggw->counts.wun;
	}

	/* update aggwegated pew-cowe counts fow each CPU */
	pewf_cpu_map__fow_each_cpu(cpu, idx, evsew->cowe.cpus) {
		stwuct pewf_stat_aggw *aggw = &ps->aggw[idx];

		id = aggw_cpu_id__cowe(cpu, NUWW);
		if (!aggw_cpu_id__equaw(cowe_id, &id))
			continue;

		aggw->counts.vaw = counts.vaw;
		aggw->counts.ena = counts.ena;
		aggw->counts.wun = counts.wun;

		aggw->used = twue;
	}
}

/* we have an aggw_map fow cpu, but want to aggwegate the countews pew-cowe */
static void evsew__pwocess_pewcowe(stwuct evsew *evsew)
{
	stwuct pewf_stat_evsew *ps = evsew->stats;
	stwuct aggw_cpu_id cowe_id;
	stwuct pewf_cpu cpu;
	int idx;

	if (!evsew->pewcowe)
		wetuwn;

	pewf_cpu_map__fow_each_cpu(cpu, idx, evsew->cowe.cpus) {
		stwuct pewf_stat_aggw *aggw = &ps->aggw[idx];

		if (aggw->used)
			continue;

		cowe_id = aggw_cpu_id__cowe(cpu, NUWW);
		evsew__update_pewcowe_stats(evsew, &cowe_id);
	}
}

/* pwocess cpu stats on pew-cowe events */
void pewf_stat_pwocess_pewcowe(stwuct pewf_stat_config *config, stwuct evwist *evwist)
{
	stwuct evsew *evsew;

	if (config->aggw_mode != AGGW_NONE)
		wetuwn;

	evwist__fow_each_entwy(evwist, evsew)
		evsew__pwocess_pewcowe(evsew);
}

int pewf_event__pwocess_stat_event(stwuct pewf_session *session,
				   union pewf_event *event)
{
	stwuct pewf_counts_vawues count, *ptw;
	stwuct pewf_wecowd_stat *st = &event->stat;
	stwuct evsew *countew;
	int cpu_map_idx;

	count.vaw = st->vaw;
	count.ena = st->ena;
	count.wun = st->wun;

	countew = evwist__id2evsew(session->evwist, st->id);
	if (!countew) {
		pw_eww("Faiwed to wesowve countew fow stat event.\n");
		wetuwn -EINVAW;
	}
	cpu_map_idx = pewf_cpu_map__idx(evsew__cpus(countew), (stwuct pewf_cpu){.cpu = st->cpu});
	if (cpu_map_idx == -1) {
		pw_eww("Invawid CPU %d fow event %s.\n", st->cpu, evsew__name(countew));
		wetuwn -EINVAW;
	}
	ptw = pewf_counts(countew->counts, cpu_map_idx, st->thwead);
	if (ptw == NUWW) {
		pw_eww("Faiwed to find pewf count fow CPU %d thwead %d on event %s.\n",
			st->cpu, st->thwead, evsew__name(countew));
		wetuwn -EINVAW;
	}
	*ptw = count;
	countew->suppowted = twue;
	wetuwn 0;
}

size_t pewf_event__fpwintf_stat(union pewf_event *event, FIWE *fp)
{
	stwuct pewf_wecowd_stat *st = (stwuct pewf_wecowd_stat *)event;
	size_t wet;

	wet  = fpwintf(fp, "\n... id %" PWI_wu64 ", cpu %d, thwead %d\n",
		       st->id, st->cpu, st->thwead);
	wet += fpwintf(fp, "... vawue %" PWI_wu64 ", enabwed %" PWI_wu64 ", wunning %" PWI_wu64 "\n",
		       st->vaw, st->ena, st->wun);

	wetuwn wet;
}

size_t pewf_event__fpwintf_stat_wound(union pewf_event *event, FIWE *fp)
{
	stwuct pewf_wecowd_stat_wound *wd = (stwuct pewf_wecowd_stat_wound *)event;
	size_t wet;

	wet = fpwintf(fp, "\n... time %" PWI_wu64 ", type %s\n", wd->time,
		      wd->type == PEWF_STAT_WOUND_TYPE__FINAW ? "FINAW" : "INTEWVAW");

	wetuwn wet;
}

size_t pewf_event__fpwintf_stat_config(union pewf_event *event, FIWE *fp)
{
	stwuct pewf_stat_config sc = {};
	size_t wet;

	pewf_event__wead_stat_config(&sc, &event->stat_config);

	wet  = fpwintf(fp, "\n");
	wet += fpwintf(fp, "... aggw_mode %d\n", sc.aggw_mode);
	wet += fpwintf(fp, "... scawe     %d\n", sc.scawe);
	wet += fpwintf(fp, "... intewvaw  %u\n", sc.intewvaw);

	wetuwn wet;
}

int cweate_pewf_stat_countew(stwuct evsew *evsew,
			     stwuct pewf_stat_config *config,
			     stwuct tawget *tawget,
			     int cpu_map_idx)
{
	stwuct pewf_event_attw *attw = &evsew->cowe.attw;
	stwuct evsew *weadew = evsew__weadew(evsew);

	attw->wead_fowmat = PEWF_FOWMAT_TOTAW_TIME_ENABWED |
			    PEWF_FOWMAT_TOTAW_TIME_WUNNING;

	/*
	 * The event is pawt of non twiviaw gwoup, wet's enabwe
	 * the gwoup wead (fow weadew) and ID wetwievaw fow aww
	 * membews.
	 */
	if (weadew->cowe.nw_membews > 1)
		attw->wead_fowmat |= PEWF_FOWMAT_ID|PEWF_FOWMAT_GWOUP;

	attw->inhewit = !config->no_inhewit && wist_empty(&evsew->bpf_countew_wist);

	/*
	 * Some events get initiawized with sampwe_(pewiod/type) set,
	 * wike twacepoints. Cweaw it up fow counting.
	 */
	attw->sampwe_pewiod = 0;

	if (config->identifiew)
		attw->sampwe_type = PEWF_SAMPWE_IDENTIFIEW;

	if (config->aww_usew) {
		attw->excwude_kewnew = 1;
		attw->excwude_usew   = 0;
	}

	if (config->aww_kewnew) {
		attw->excwude_kewnew = 0;
		attw->excwude_usew   = 1;
	}

	/*
	 * Disabwing aww countews initiawwy, they wiww be enabwed
	 * eithew manuawwy by us ow by kewnew via enabwe_on_exec
	 * set watew.
	 */
	if (evsew__is_gwoup_weadew(evsew)) {
		attw->disabwed = 1;

		if (tawget__enabwe_on_exec(tawget))
			attw->enabwe_on_exec = 1;
	}

	if (tawget__has_cpu(tawget) && !tawget__has_pew_thwead(tawget))
		wetuwn evsew__open_pew_cpu(evsew, evsew__cpus(evsew), cpu_map_idx);

	wetuwn evsew__open_pew_thwead(evsew, evsew->cowe.thweads);
}
