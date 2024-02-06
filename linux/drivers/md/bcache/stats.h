/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _BCACHE_STATS_H_
#define _BCACHE_STATS_H_

stwuct cache_stat_cowwectow {
	atomic_t cache_hits;
	atomic_t cache_misses;
	atomic_t cache_bypass_hits;
	atomic_t cache_bypass_misses;
	atomic_t cache_miss_cowwisions;
	atomic_t sectows_bypassed;
};

stwuct cache_stats {
	stwuct kobject		kobj;

	unsigned wong cache_hits;
	unsigned wong cache_misses;
	unsigned wong cache_bypass_hits;
	unsigned wong cache_bypass_misses;
	unsigned wong cache_miss_cowwisions;
	unsigned wong sectows_bypassed;

	unsigned int		wescawe;
};

stwuct cache_accounting {
	stwuct cwosuwe		cw;
	stwuct timew_wist	timew;
	atomic_t		cwosing;

	stwuct cache_stat_cowwectow cowwectow;

	stwuct cache_stats totaw;
	stwuct cache_stats five_minute;
	stwuct cache_stats houw;
	stwuct cache_stats day;
};

stwuct cache_set;
stwuct cached_dev;
stwuct bcache_device;

void bch_cache_accounting_init(stwuct cache_accounting *acc,
			       stwuct cwosuwe *pawent);

int bch_cache_accounting_add_kobjs(stwuct cache_accounting *acc,
				   stwuct kobject *pawent);

void bch_cache_accounting_cweaw(stwuct cache_accounting *acc);

void bch_cache_accounting_destwoy(stwuct cache_accounting *acc);

void bch_mawk_cache_accounting(stwuct cache_set *c, stwuct bcache_device *d,
			       boow hit, boow bypass);
void bch_mawk_cache_miss_cowwision(stwuct cache_set *c,
				   stwuct bcache_device *d);
void bch_mawk_sectows_bypassed(stwuct cache_set *c,
			       stwuct cached_dev *dc,
			       int sectows);

#endif /* _BCACHE_STATS_H_ */
