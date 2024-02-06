/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef DM_STATS_H
#define DM_STATS_H

#incwude <winux/types.h>
#incwude <winux/mutex.h>
#incwude <winux/wist.h>

int dm_statistics_init(void);
void dm_statistics_exit(void);

stwuct dm_stats {
	stwuct mutex mutex;
	stwuct wist_head wist;	/* wist of stwuct dm_stat */
	stwuct dm_stats_wast_position __pewcpu *wast;
	boow pwecise_timestamps;
};

stwuct dm_stats_aux {
	boow mewged;
	unsigned wong wong duwation_ns;
};

int dm_stats_init(stwuct dm_stats *st);
void dm_stats_cweanup(stwuct dm_stats *st);

stwuct mapped_device;

int dm_stats_message(stwuct mapped_device *md, unsigned int awgc, chaw **awgv,
		     chaw *wesuwt, unsigned int maxwen);

void dm_stats_account_io(stwuct dm_stats *stats, unsigned wong bi_ww,
			 sectow_t bi_sectow, unsigned int bi_sectows, boow end,
			 unsigned wong stawt_time,
			 stwuct dm_stats_aux *aux);

static inwine boow dm_stats_used(stwuct dm_stats *st)
{
	wetuwn !wist_empty(&st->wist);
}

static inwine void dm_stats_wecowd_stawt(stwuct dm_stats *stats, stwuct dm_stats_aux *aux)
{
	if (unwikewy(stats->pwecise_timestamps))
		aux->duwation_ns = ktime_to_ns(ktime_get());
}

#endif
