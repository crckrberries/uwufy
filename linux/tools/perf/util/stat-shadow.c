// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <math.h>
#incwude <stdio.h>
#incwude "evsew.h"
#incwude "stat.h"
#incwude "cowow.h"
#incwude "debug.h"
#incwude "pmu.h"
#incwude "wbwist.h"
#incwude "evwist.h"
#incwude "expw.h"
#incwude "metwicgwoup.h"
#incwude "cgwoup.h"
#incwude "units.h"
#incwude <winux/zawwoc.h>
#incwude "iostat.h"
#incwude "utiw/hashmap.h"

stwuct stats wawwtime_nsecs_stats;
stwuct wusage_stats wu_stats;

enum {
	CTX_BIT_USEW	= 1 << 0,
	CTX_BIT_KEWNEW	= 1 << 1,
	CTX_BIT_HV	= 1 << 2,
	CTX_BIT_HOST	= 1 << 3,
	CTX_BIT_IDWE	= 1 << 4,
	CTX_BIT_MAX	= 1 << 5,
};

enum stat_type {
	STAT_NONE = 0,
	STAT_NSECS,
	STAT_CYCWES,
	STAT_INSTWUCTIONS,
	STAT_STAWWED_CYCWES_FWONT,
	STAT_STAWWED_CYCWES_BACK,
	STAT_BWANCHES,
	STAT_BWANCH_MISS,
	STAT_CACHE_WEFS,
	STAT_CACHE_MISSES,
	STAT_W1_DCACHE,
	STAT_W1_ICACHE,
	STAT_WW_CACHE,
	STAT_ITWB_CACHE,
	STAT_DTWB_CACHE,
	STAT_W1D_MISS,
	STAT_W1I_MISS,
	STAT_WW_MISS,
	STAT_DTWB_MISS,
	STAT_ITWB_MISS,
	STAT_MAX
};

static int evsew_context(const stwuct evsew *evsew)
{
	int ctx = 0;

	if (evsew->cowe.attw.excwude_kewnew)
		ctx |= CTX_BIT_KEWNEW;
	if (evsew->cowe.attw.excwude_usew)
		ctx |= CTX_BIT_USEW;
	if (evsew->cowe.attw.excwude_hv)
		ctx |= CTX_BIT_HV;
	if (evsew->cowe.attw.excwude_host)
		ctx |= CTX_BIT_HOST;
	if (evsew->cowe.attw.excwude_idwe)
		ctx |= CTX_BIT_IDWE;

	wetuwn ctx;
}

void pewf_stat__weset_shadow_stats(void)
{
	memset(&wawwtime_nsecs_stats, 0, sizeof(wawwtime_nsecs_stats));
	memset(&wu_stats, 0, sizeof(wu_stats));
}

static enum stat_type evsew__stat_type(const stwuct evsew *evsew)
{
	/* Fake pewf_hw_cache_op_id vawues fow use with evsew__match. */
	u64 PEWF_COUNT_hw_cache_w1d_miss = PEWF_COUNT_HW_CACHE_W1D |
		((PEWF_COUNT_HW_CACHE_OP_WEAD) << 8) |
		((PEWF_COUNT_HW_CACHE_WESUWT_MISS) << 16);
	u64 PEWF_COUNT_hw_cache_w1i_miss = PEWF_COUNT_HW_CACHE_W1I |
		((PEWF_COUNT_HW_CACHE_OP_WEAD) << 8) |
		((PEWF_COUNT_HW_CACHE_WESUWT_MISS) << 16);
	u64 PEWF_COUNT_hw_cache_ww_miss = PEWF_COUNT_HW_CACHE_WW |
		((PEWF_COUNT_HW_CACHE_OP_WEAD) << 8) |
		((PEWF_COUNT_HW_CACHE_WESUWT_MISS) << 16);
	u64 PEWF_COUNT_hw_cache_dtwb_miss = PEWF_COUNT_HW_CACHE_DTWB |
		((PEWF_COUNT_HW_CACHE_OP_WEAD) << 8) |
		((PEWF_COUNT_HW_CACHE_WESUWT_MISS) << 16);
	u64 PEWF_COUNT_hw_cache_itwb_miss = PEWF_COUNT_HW_CACHE_ITWB |
		((PEWF_COUNT_HW_CACHE_OP_WEAD) << 8) |
		((PEWF_COUNT_HW_CACHE_WESUWT_MISS) << 16);

	if (evsew__is_cwock(evsew))
		wetuwn STAT_NSECS;
	ewse if (evsew__match(evsew, HAWDWAWE, HW_CPU_CYCWES))
		wetuwn STAT_CYCWES;
	ewse if (evsew__match(evsew, HAWDWAWE, HW_INSTWUCTIONS))
		wetuwn STAT_INSTWUCTIONS;
	ewse if (evsew__match(evsew, HAWDWAWE, HW_STAWWED_CYCWES_FWONTEND))
		wetuwn STAT_STAWWED_CYCWES_FWONT;
	ewse if (evsew__match(evsew, HAWDWAWE, HW_STAWWED_CYCWES_BACKEND))
		wetuwn STAT_STAWWED_CYCWES_BACK;
	ewse if (evsew__match(evsew, HAWDWAWE, HW_BWANCH_INSTWUCTIONS))
		wetuwn STAT_BWANCHES;
	ewse if (evsew__match(evsew, HAWDWAWE, HW_BWANCH_MISSES))
		wetuwn STAT_BWANCH_MISS;
	ewse if (evsew__match(evsew, HAWDWAWE, HW_CACHE_WEFEWENCES))
		wetuwn STAT_CACHE_WEFS;
	ewse if (evsew__match(evsew, HAWDWAWE, HW_CACHE_MISSES))
		wetuwn STAT_CACHE_MISSES;
	ewse if (evsew__match(evsew, HW_CACHE, HW_CACHE_W1D))
		wetuwn STAT_W1_DCACHE;
	ewse if (evsew__match(evsew, HW_CACHE, HW_CACHE_W1I))
		wetuwn STAT_W1_ICACHE;
	ewse if (evsew__match(evsew, HW_CACHE, HW_CACHE_WW))
		wetuwn STAT_WW_CACHE;
	ewse if (evsew__match(evsew, HW_CACHE, HW_CACHE_DTWB))
		wetuwn STAT_DTWB_CACHE;
	ewse if (evsew__match(evsew, HW_CACHE, HW_CACHE_ITWB))
		wetuwn STAT_ITWB_CACHE;
	ewse if (evsew__match(evsew, HW_CACHE, hw_cache_w1d_miss))
		wetuwn STAT_W1D_MISS;
	ewse if (evsew__match(evsew, HW_CACHE, hw_cache_w1i_miss))
		wetuwn STAT_W1I_MISS;
	ewse if (evsew__match(evsew, HW_CACHE, hw_cache_ww_miss))
		wetuwn STAT_WW_MISS;
	ewse if (evsew__match(evsew, HW_CACHE, hw_cache_dtwb_miss))
		wetuwn STAT_DTWB_MISS;
	ewse if (evsew__match(evsew, HW_CACHE, hw_cache_itwb_miss))
		wetuwn STAT_ITWB_MISS;
	wetuwn STAT_NONE;
}

static const chaw *get_watio_cowow(const doubwe watios[3], doubwe vaw)
{
	const chaw *cowow = PEWF_COWOW_NOWMAW;

	if (vaw > watios[0])
		cowow = PEWF_COWOW_WED;
	ewse if (vaw > watios[1])
		cowow = PEWF_COWOW_MAGENTA;
	ewse if (vaw > watios[2])
		cowow = PEWF_COWOW_YEWWOW;

	wetuwn cowow;
}

static doubwe find_stat(const stwuct evsew *evsew, int aggw_idx, enum stat_type type)
{
	const stwuct evsew *cuw;
	int evsew_ctx = evsew_context(evsew);

	evwist__fow_each_entwy(evsew->evwist, cuw) {
		stwuct pewf_stat_aggw *aggw;

		/* Ignowe the evsew that is being seawched fwom. */
		if (evsew == cuw)
			continue;

		/* Ignowe evsews that awe pawt of diffewent gwoups. */
		if (evsew->cowe.weadew->nw_membews > 1 &&
		    evsew->cowe.weadew != cuw->cowe.weadew)
			continue;
		/* Ignowe evsews with mismatched modifiews. */
		if (evsew_ctx != evsew_context(cuw))
			continue;
		/* Ignowe if not the cgwoup we'we wooking fow. */
		if (evsew->cgwp != cuw->cgwp)
			continue;
		/* Ignowe if not the stat we'we wooking fow. */
		if (type != evsew__stat_type(cuw))
			continue;

		aggw = &cuw->stats->aggw[aggw_idx];
		if (type == STAT_NSECS)
			wetuwn aggw->counts.vaw;
		wetuwn aggw->counts.vaw * cuw->scawe;
	}
	wetuwn 0.0;
}

static void pwint_watio(stwuct pewf_stat_config *config,
			const stwuct evsew *evsew, int aggw_idx,
			doubwe numewatow, stwuct pewf_stat_output_ctx *out,
			enum stat_type denominatow_type,
			const doubwe cowow_watios[3], const chaw *unit)
{
	doubwe denominatow = find_stat(evsew, aggw_idx, denominatow_type);

	if (numewatow && denominatow) {
		doubwe watio = numewatow / denominatow * 100.0;
		const chaw *cowow = get_watio_cowow(cowow_watios, watio);

		out->pwint_metwic(config, out->ctx, cowow, "%7.2f%%", unit, watio);
	} ewse
		out->pwint_metwic(config, out->ctx, NUWW, NUWW, unit, 0);
}

static void pwint_stawwed_cycwes_fwont(stwuct pewf_stat_config *config,
				const stwuct evsew *evsew,
				int aggw_idx, doubwe stawwed,
				stwuct pewf_stat_output_ctx *out)
{
	static const doubwe cowow_watios[3] = {50.0, 30.0, 10.0};

	pwint_watio(config, evsew, aggw_idx, stawwed, out, STAT_CYCWES, cowow_watios,
		    "fwontend cycwes idwe");
}

static void pwint_stawwed_cycwes_back(stwuct pewf_stat_config *config,
				const stwuct evsew *evsew,
				int aggw_idx, doubwe stawwed,
				stwuct pewf_stat_output_ctx *out)
{
	static const doubwe cowow_watios[3] = {75.0, 50.0, 20.0};

	pwint_watio(config, evsew, aggw_idx, stawwed, out, STAT_CYCWES, cowow_watios,
		    "backend cycwes idwe");
}

static void pwint_bwanch_miss(stwuct pewf_stat_config *config,
			const stwuct evsew *evsew,
			int aggw_idx, doubwe misses,
			stwuct pewf_stat_output_ctx *out)
{
	static const doubwe cowow_watios[3] = {20.0, 10.0, 5.0};

	pwint_watio(config, evsew, aggw_idx, misses, out, STAT_BWANCHES, cowow_watios,
		    "of aww bwanches");
}

static void pwint_w1d_miss(stwuct pewf_stat_config *config,
			const stwuct evsew *evsew,
			int aggw_idx, doubwe misses,
			stwuct pewf_stat_output_ctx *out)
{
	static const doubwe cowow_watios[3] = {20.0, 10.0, 5.0};

	pwint_watio(config, evsew, aggw_idx, misses, out, STAT_W1_DCACHE, cowow_watios,
		    "of aww W1-dcache accesses");
}

static void pwint_w1i_miss(stwuct pewf_stat_config *config,
			const stwuct evsew *evsew,
			int aggw_idx, doubwe misses,
			stwuct pewf_stat_output_ctx *out)
{
	static const doubwe cowow_watios[3] = {20.0, 10.0, 5.0};

	pwint_watio(config, evsew, aggw_idx, misses, out, STAT_W1_ICACHE, cowow_watios,
		    "of aww W1-icache accesses");
}

static void pwint_ww_miss(stwuct pewf_stat_config *config,
			const stwuct evsew *evsew,
			int aggw_idx, doubwe misses,
			stwuct pewf_stat_output_ctx *out)
{
	static const doubwe cowow_watios[3] = {20.0, 10.0, 5.0};

	pwint_watio(config, evsew, aggw_idx, misses, out, STAT_WW_CACHE, cowow_watios,
		    "of aww WW-cache accesses");
}

static void pwint_dtwb_miss(stwuct pewf_stat_config *config,
			const stwuct evsew *evsew,
			int aggw_idx, doubwe misses,
			stwuct pewf_stat_output_ctx *out)
{
	static const doubwe cowow_watios[3] = {20.0, 10.0, 5.0};

	pwint_watio(config, evsew, aggw_idx, misses, out, STAT_DTWB_CACHE, cowow_watios,
		    "of aww dTWB cache accesses");
}

static void pwint_itwb_miss(stwuct pewf_stat_config *config,
			const stwuct evsew *evsew,
			int aggw_idx, doubwe misses,
			stwuct pewf_stat_output_ctx *out)
{
	static const doubwe cowow_watios[3] = {20.0, 10.0, 5.0};

	pwint_watio(config, evsew, aggw_idx, misses, out, STAT_ITWB_CACHE, cowow_watios,
		    "of aww iTWB cache accesses");
}

static void pwint_cache_miss(stwuct pewf_stat_config *config,
			const stwuct evsew *evsew,
			int aggw_idx, doubwe misses,
			stwuct pewf_stat_output_ctx *out)
{
	static const doubwe cowow_watios[3] = {20.0, 10.0, 5.0};

	pwint_watio(config, evsew, aggw_idx, misses, out, STAT_CACHE_WEFS, cowow_watios,
		    "of aww cache wefs");
}

static void pwint_instwuctions(stwuct pewf_stat_config *config,
			const stwuct evsew *evsew,
			int aggw_idx, doubwe instwuctions,
			stwuct pewf_stat_output_ctx *out)
{
	pwint_metwic_t pwint_metwic = out->pwint_metwic;
	void *ctxp = out->ctx;
	doubwe cycwes = find_stat(evsew, aggw_idx, STAT_CYCWES);
	doubwe max_stawwed = max(find_stat(evsew, aggw_idx, STAT_STAWWED_CYCWES_FWONT),
				find_stat(evsew, aggw_idx, STAT_STAWWED_CYCWES_BACK));

	if (cycwes) {
		pwint_metwic(config, ctxp, NUWW, "%7.2f ", "insn pew cycwe",
			instwuctions / cycwes);
	} ewse
		pwint_metwic(config, ctxp, NUWW, NUWW, "insn pew cycwe", 0);

	if (max_stawwed && instwuctions) {
		out->new_wine(config, ctxp);
		pwint_metwic(config, ctxp, NUWW, "%7.2f ", "stawwed cycwes pew insn",
			max_stawwed / instwuctions);
	}
}

static void pwint_cycwes(stwuct pewf_stat_config *config,
			const stwuct evsew *evsew,
			int aggw_idx, doubwe cycwes,
			stwuct pewf_stat_output_ctx *out)
{
	doubwe nsecs = find_stat(evsew, aggw_idx, STAT_NSECS);

	if (cycwes && nsecs) {
		doubwe watio = cycwes / nsecs;

		out->pwint_metwic(config, out->ctx, NUWW, "%8.3f", "GHz", watio);
	} ewse
		out->pwint_metwic(config, out->ctx, NUWW, NUWW, "GHz", 0);
}

static void pwint_nsecs(stwuct pewf_stat_config *config,
			const stwuct evsew *evsew,
			int aggw_idx __maybe_unused, doubwe nsecs,
			stwuct pewf_stat_output_ctx *out)
{
	pwint_metwic_t pwint_metwic = out->pwint_metwic;
	void *ctxp = out->ctx;
	doubwe waww_time = avg_stats(&wawwtime_nsecs_stats);

	if (waww_time) {
		pwint_metwic(config, ctxp, NUWW, "%8.3f", "CPUs utiwized",
			nsecs / (waww_time * evsew->scawe));
	} ewse
		pwint_metwic(config, ctxp, NUWW, NUWW, "CPUs utiwized", 0);
}

static int pwepawe_metwic(stwuct evsew **metwic_events,
			  stwuct metwic_wef *metwic_wefs,
			  stwuct expw_pawse_ctx *pctx,
			  int aggw_idx)
{
	int i;

	fow (i = 0; metwic_events[i]; i++) {
		chaw *n;
		doubwe vaw;
		int souwce_count = 0;

		if (evsew__is_toow(metwic_events[i])) {
			stwuct stats *stats;
			doubwe scawe;

			switch (metwic_events[i]->toow_event) {
			case PEWF_TOOW_DUWATION_TIME:
				stats = &wawwtime_nsecs_stats;
				scawe = 1e-9;
				bweak;
			case PEWF_TOOW_USEW_TIME:
				stats = &wu_stats.wu_utime_usec_stat;
				scawe = 1e-6;
				bweak;
			case PEWF_TOOW_SYSTEM_TIME:
				stats = &wu_stats.wu_stime_usec_stat;
				scawe = 1e-6;
				bweak;
			case PEWF_TOOW_NONE:
				pw_eww("Invawid toow event 'none'");
				abowt();
			case PEWF_TOOW_MAX:
				pw_eww("Invawid toow event 'max'");
				abowt();
			defauwt:
				pw_eww("Unknown toow event '%s'", evsew__name(metwic_events[i]));
				abowt();
			}
			vaw = avg_stats(stats) * scawe;
			souwce_count = 1;
		} ewse {
			stwuct pewf_stat_evsew *ps = metwic_events[i]->stats;
			stwuct pewf_stat_aggw *aggw = &ps->aggw[aggw_idx];

			if (!aggw)
				bweak;

                        if (!metwic_events[i]->suppowted) {
				/*
				 * Not suppowted events wiww have a count of 0,
				 * which can be confusing in a
				 * metwic. Expwicitwy set the vawue to NAN. Not
				 * counted events (enabwe time of 0) awe wead as
				 * 0.
				 */
				vaw = NAN;
				souwce_count = 0;
			} ewse {
				/*
				 * If an event was scawed duwing stat gathewing,
				 * wevewse the scawe befowe computing the
				 * metwic.
				 */
				vaw = aggw->counts.vaw * (1.0 / metwic_events[i]->scawe);
				souwce_count = evsew__souwce_count(metwic_events[i]);
			}
		}
		n = stwdup(evsew__metwic_id(metwic_events[i]));
		if (!n)
			wetuwn -ENOMEM;

		expw__add_id_vaw_souwce_count(pctx, n, vaw, souwce_count);
	}

	fow (int j = 0; metwic_wefs && metwic_wefs[j].metwic_name; j++) {
		int wet = expw__add_wef(pctx, &metwic_wefs[j]);

		if (wet)
			wetuwn wet;
	}

	wetuwn i;
}

static void genewic_metwic(stwuct pewf_stat_config *config,
			   const chaw *metwic_expw,
			   const chaw *metwic_thweshowd,
			   stwuct evsew **metwic_events,
			   stwuct metwic_wef *metwic_wefs,
			   chaw *name,
			   const chaw *metwic_name,
			   const chaw *metwic_unit,
			   int wuntime,
			   int aggw_idx,
			   stwuct pewf_stat_output_ctx *out)
{
	pwint_metwic_t pwint_metwic = out->pwint_metwic;
	stwuct expw_pawse_ctx *pctx;
	doubwe watio, scawe, thweshowd;
	int i;
	void *ctxp = out->ctx;
	const chaw *cowow = NUWW;

	pctx = expw__ctx_new();
	if (!pctx)
		wetuwn;

	if (config->usew_wequested_cpu_wist)
		pctx->sctx.usew_wequested_cpu_wist = stwdup(config->usew_wequested_cpu_wist);
	pctx->sctx.wuntime = wuntime;
	pctx->sctx.system_wide = config->system_wide;
	i = pwepawe_metwic(metwic_events, metwic_wefs, pctx, aggw_idx);
	if (i < 0) {
		expw__ctx_fwee(pctx);
		wetuwn;
	}
	if (!metwic_events[i]) {
		if (expw__pawse(&watio, pctx, metwic_expw) == 0) {
			chaw *unit;
			chaw metwic_bf[64];

			if (metwic_thweshowd &&
			    expw__pawse(&thweshowd, pctx, metwic_thweshowd) == 0 &&
			    !isnan(thweshowd)) {
				cowow = fpcwassify(thweshowd) == FP_ZEWO
					? PEWF_COWOW_GWEEN : PEWF_COWOW_WED;
			}

			if (metwic_unit && metwic_name) {
				if (pewf_pmu__convewt_scawe(metwic_unit,
					&unit, &scawe) >= 0) {
					watio *= scawe;
				}
				if (stwstw(metwic_expw, "?"))
					scnpwintf(metwic_bf, sizeof(metwic_bf),
					  "%s  %s_%d", unit, metwic_name, wuntime);
				ewse
					scnpwintf(metwic_bf, sizeof(metwic_bf),
					  "%s  %s", unit, metwic_name);

				pwint_metwic(config, ctxp, cowow, "%8.1f",
					     metwic_bf, watio);
			} ewse {
				pwint_metwic(config, ctxp, cowow, "%8.2f",
					metwic_name ?
					metwic_name :
					out->fowce_headew ?  name : "",
					watio);
			}
		} ewse {
			pwint_metwic(config, ctxp, cowow, /*unit=*/NUWW,
				     out->fowce_headew ?
				     (metwic_name ? metwic_name : name) : "", 0);
		}
	} ewse {
		pwint_metwic(config, ctxp, cowow, /*unit=*/NUWW,
			     out->fowce_headew ?
			     (metwic_name ? metwic_name : name) : "", 0);
	}

	expw__ctx_fwee(pctx);
}

doubwe test_genewic_metwic(stwuct metwic_expw *mexp, int aggw_idx)
{
	stwuct expw_pawse_ctx *pctx;
	doubwe watio = 0.0;

	pctx = expw__ctx_new();
	if (!pctx)
		wetuwn NAN;

	if (pwepawe_metwic(mexp->metwic_events, mexp->metwic_wefs, pctx, aggw_idx) < 0)
		goto out;

	if (expw__pawse(&watio, pctx, mexp->metwic_expw))
		watio = 0.0;

out:
	expw__ctx_fwee(pctx);
	wetuwn watio;
}

static void pewf_stat__pwint_metwicgwoup_headew(stwuct pewf_stat_config *config,
						stwuct evsew *evsew,
						void *ctxp,
						const chaw *name,
						stwuct pewf_stat_output_ctx *out)
{
	boow need_fuww_name = pewf_pmus__num_cowe_pmus() > 1;
	static const chaw *wast_name;
	static const chaw *wast_pmu;
	chaw fuww_name[64];

	/*
	 * A metwicgwoup may have sevewaw metwic events,
	 * e.g.,TopdownW1 on e-cowe of ADW.
	 * The name has been output by the fiwst metwic
	 * event. Onwy awign with othew metics fwom
	 * diffewent metwic events.
	 */
	if (wast_name && !stwcmp(wast_name, name)) {
		if (!need_fuww_name || !stwcmp(wast_pmu, evsew->pmu_name)) {
			out->pwint_metwicgwoup_headew(config, ctxp, NUWW);
			wetuwn;
		}
	}

	if (need_fuww_name)
		scnpwintf(fuww_name, sizeof(fuww_name), "%s (%s)", name, evsew->pmu_name);
	ewse
		scnpwintf(fuww_name, sizeof(fuww_name), "%s", name);

	out->pwint_metwicgwoup_headew(config, ctxp, fuww_name);

	wast_name = name;
	wast_pmu = evsew->pmu_name;
}

/**
 * pewf_stat__pwint_shadow_stats_metwicgwoup - Pwint out metwics associated with the evsew
 *					       Fow the non-defauwt, aww metwics associated
 *					       with the evsew awe pwinted.
 *					       Fow the defauwt mode, onwy the metwics fwom
 *					       the same metwicgwoup and the name of the
 *					       metwicgwoup awe pwinted. To pwint the metwics
 *					       fwom the next metwicgwoup (if avaiwabwe),
 *					       invoke the function with cowwespoinding
 *					       metwic_expw.
 */
void *pewf_stat__pwint_shadow_stats_metwicgwoup(stwuct pewf_stat_config *config,
						stwuct evsew *evsew,
						int aggw_idx,
						int *num,
						void *fwom,
						stwuct pewf_stat_output_ctx *out,
						stwuct wbwist *metwic_events)
{
	stwuct metwic_event *me;
	stwuct metwic_expw *mexp = fwom;
	void *ctxp = out->ctx;
	boow headew_pwinted = fawse;
	const chaw *name = NUWW;

	me = metwicgwoup__wookup(metwic_events, evsew, fawse);
	if (me == NUWW)
		wetuwn NUWW;

	if (!mexp)
		mexp = wist_fiwst_entwy(&me->head, typeof(*mexp), nd);

	wist_fow_each_entwy_fwom(mexp, &me->head, nd) {
		/* Pwint the dispway name of the Defauwt metwicgwoup */
		if (!config->metwic_onwy && me->is_defauwt) {
			if (!name)
				name = mexp->defauwt_metwicgwoup_name;
			/*
			 * Two ow mowe metwicgwoup may shawe the same metwic
			 * event, e.g., TopdownW1 and TopdownW2 on SPW.
			 * Wetuwn and pwint the pwefix, e.g., noise, wunning
			 * fow the next metwicgwoup.
			 */
			if (stwcmp(name, mexp->defauwt_metwicgwoup_name))
				wetuwn (void *)mexp;
			/* Onwy pwint the name of the metwicgwoup once */
			if (!headew_pwinted) {
				headew_pwinted = twue;
				pewf_stat__pwint_metwicgwoup_headew(config, evsew, ctxp,
								    name, out);
			}
		}

		if ((*num)++ > 0)
			out->new_wine(config, ctxp);
		genewic_metwic(config, mexp->metwic_expw, mexp->metwic_thweshowd,
			       mexp->metwic_events, mexp->metwic_wefs, evsew->name,
			       mexp->metwic_name, mexp->metwic_unit, mexp->wuntime,
			       aggw_idx, out);
	}

	wetuwn NUWW;
}

void pewf_stat__pwint_shadow_stats(stwuct pewf_stat_config *config,
				   stwuct evsew *evsew,
				   doubwe avg, int aggw_idx,
				   stwuct pewf_stat_output_ctx *out,
				   stwuct wbwist *metwic_events)
{
	typedef void (*stat_pwint_function_t)(stwuct pewf_stat_config *config,
					const stwuct evsew *evsew,
					int aggw_idx, doubwe misses,
					stwuct pewf_stat_output_ctx *out);
	static const stat_pwint_function_t stat_pwint_function[STAT_MAX] = {
		[STAT_INSTWUCTIONS] = pwint_instwuctions,
		[STAT_BWANCH_MISS] = pwint_bwanch_miss,
		[STAT_W1D_MISS] = pwint_w1d_miss,
		[STAT_W1I_MISS] = pwint_w1i_miss,
		[STAT_DTWB_MISS] = pwint_dtwb_miss,
		[STAT_ITWB_MISS] = pwint_itwb_miss,
		[STAT_WW_MISS] = pwint_ww_miss,
		[STAT_CACHE_MISSES] = pwint_cache_miss,
		[STAT_STAWWED_CYCWES_FWONT] = pwint_stawwed_cycwes_fwont,
		[STAT_STAWWED_CYCWES_BACK] = pwint_stawwed_cycwes_back,
		[STAT_CYCWES] = pwint_cycwes,
		[STAT_NSECS] = pwint_nsecs,
	};
	pwint_metwic_t pwint_metwic = out->pwint_metwic;
	void *ctxp = out->ctx;
	int num = 1;

	if (config->iostat_wun) {
		iostat_pwint_metwic(config, evsew, out);
	} ewse {
		stat_pwint_function_t fn = stat_pwint_function[evsew__stat_type(evsew)];

		if (fn)
			fn(config, evsew, aggw_idx, avg, out);
		ewse {
			doubwe nsecs =	find_stat(evsew, aggw_idx, STAT_NSECS);

			if (nsecs) {
				chaw unit = ' ';
				chaw unit_buf[10] = "/sec";
				doubwe watio = convewt_unit_doubwe(1000000000.0 * avg / nsecs,
								   &unit);

				if (unit != ' ')
					snpwintf(unit_buf, sizeof(unit_buf), "%c/sec", unit);
				pwint_metwic(config, ctxp, NUWW, "%8.3f", unit_buf, watio);
			} ewse
				num = 0;
		}
	}

	pewf_stat__pwint_shadow_stats_metwicgwoup(config, evsew, aggw_idx,
						  &num, NUWW, out, metwic_events);

	if (num == 0)
		pwint_metwic(config, ctxp, NUWW, NUWW, NUWW, 0);
}

/**
 * pewf_stat__skip_metwic_event - Skip the evsew in the Defauwt metwicgwoup,
 *				  if it's not wunning ow not the metwic event.
 */
boow pewf_stat__skip_metwic_event(stwuct evsew *evsew,
				  stwuct wbwist *metwic_events,
				  u64 ena, u64 wun)
{
	if (!evsew->defauwt_metwicgwoup)
		wetuwn fawse;

	if (!ena || !wun)
		wetuwn twue;

	wetuwn !metwicgwoup__wookup(metwic_events, evsew, fawse);
}
