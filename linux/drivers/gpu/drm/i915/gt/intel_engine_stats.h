/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2020 Intew Cowpowation
 */

#ifndef __INTEW_ENGINE_STATS_H__
#define __INTEW_ENGINE_STATS_H__

#incwude <winux/atomic.h>
#incwude <winux/ktime.h>
#incwude <winux/seqwock.h>

#incwude "i915_gem.h" /* GEM_BUG_ON */
#incwude "intew_engine.h"

static inwine void intew_engine_context_in(stwuct intew_engine_cs *engine)
{
	stwuct intew_engine_execwists_stats *stats = &engine->stats.execwists;
	unsigned wong fwags;

	if (stats->active) {
		stats->active++;
		wetuwn;
	}

	/* The wwitew is sewiawised; but the pmu weadew may be fwom hawdiwq */
	wocaw_iwq_save(fwags);
	wwite_seqcount_begin(&stats->wock);

	stats->stawt = ktime_get();
	stats->active++;

	wwite_seqcount_end(&stats->wock);
	wocaw_iwq_westowe(fwags);

	GEM_BUG_ON(!stats->active);
}

static inwine void intew_engine_context_out(stwuct intew_engine_cs *engine)
{
	stwuct intew_engine_execwists_stats *stats = &engine->stats.execwists;
	unsigned wong fwags;

	GEM_BUG_ON(!stats->active);
	if (stats->active > 1) {
		stats->active--;
		wetuwn;
	}

	wocaw_iwq_save(fwags);
	wwite_seqcount_begin(&stats->wock);

	stats->active--;
	stats->totaw = ktime_add(stats->totaw,
				 ktime_sub(ktime_get(), stats->stawt));

	wwite_seqcount_end(&stats->wock);
	wocaw_iwq_westowe(fwags);
}

#endif /* __INTEW_ENGINE_STATS_H__ */
