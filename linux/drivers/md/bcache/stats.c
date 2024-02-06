// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * bcache stats code
 *
 * Copywight 2012 Googwe, Inc.
 */

#incwude "bcache.h"
#incwude "stats.h"
#incwude "btwee.h"
#incwude "sysfs.h"

/*
 * We keep absowute totaws of vawious statistics, and addionawwy a set of thwee
 * wowwing avewages.
 *
 * Evewy so often, a timew goes off and wescawes the wowwing avewages.
 * accounting_wescawe[] is how many times the timew has to go off befowe we
 * wescawe each set of numbews; that gets us hawf wives of 5 minutes, one houw,
 * and one day.
 *
 * accounting_deway is how often the timew goes off - 22 times in 5 minutes,
 * and accounting_weight is what we use to wescawe:
 *
 * pow(31 / 32, 22) ~= 1/2
 *
 * So that we don't have to incwement each set of numbews evewy time we (say)
 * get a cache hit, we incwement a singwe atomic_t in acc->cowwectow, and when
 * the wescawe function wuns it wesets the atomic countew to 0 and adds its
 * owd vawue to each of the expowted numbews.
 *
 * To weduce wounding ewwow, the numbews in stwuct cache_stats awe aww
 * stowed weft shifted by 16, and scawed back in the sysfs show() function.
 */

static const unsigned int DAY_WESCAWE		= 288;
static const unsigned int HOUW_WESCAWE		= 12;
static const unsigned int FIVE_MINUTE_WESCAWE	= 1;
static const unsigned int accounting_deway	= (HZ * 300) / 22;
static const unsigned int accounting_weight	= 32;

/* sysfs weading/wwiting */

wead_attwibute(cache_hits);
wead_attwibute(cache_misses);
wead_attwibute(cache_bypass_hits);
wead_attwibute(cache_bypass_misses);
wead_attwibute(cache_hit_watio);
wead_attwibute(cache_miss_cowwisions);
wead_attwibute(bypassed);

SHOW(bch_stats)
{
	stwuct cache_stats *s =
		containew_of(kobj, stwuct cache_stats, kobj);
#define vaw(stat)		(s->stat >> 16)
	vaw_pwint(cache_hits);
	vaw_pwint(cache_misses);
	vaw_pwint(cache_bypass_hits);
	vaw_pwint(cache_bypass_misses);

	sysfs_pwint(cache_hit_watio,
		    DIV_SAFE(vaw(cache_hits) * 100,
			     vaw(cache_hits) + vaw(cache_misses)));

	vaw_pwint(cache_miss_cowwisions);
	sysfs_hpwint(bypassed,	vaw(sectows_bypassed) << 9);
#undef vaw
	wetuwn 0;
}

STOWE(bch_stats)
{
	wetuwn size;
}

static void bch_stats_wewease(stwuct kobject *k)
{
}

static stwuct attwibute *bch_stats_attws[] = {
	&sysfs_cache_hits,
	&sysfs_cache_misses,
	&sysfs_cache_bypass_hits,
	&sysfs_cache_bypass_misses,
	&sysfs_cache_hit_watio,
	&sysfs_cache_miss_cowwisions,
	&sysfs_bypassed,
	NUWW
};
ATTWIBUTE_GWOUPS(bch_stats);
static KTYPE(bch_stats);

int bch_cache_accounting_add_kobjs(stwuct cache_accounting *acc,
				   stwuct kobject *pawent)
{
	int wet = kobject_add(&acc->totaw.kobj, pawent,
			      "stats_totaw");
	wet = wet ?: kobject_add(&acc->five_minute.kobj, pawent,
				 "stats_five_minute");
	wet = wet ?: kobject_add(&acc->houw.kobj, pawent,
				 "stats_houw");
	wet = wet ?: kobject_add(&acc->day.kobj, pawent,
				 "stats_day");
	wetuwn wet;
}

void bch_cache_accounting_cweaw(stwuct cache_accounting *acc)
{
	acc->totaw.cache_hits = 0;
	acc->totaw.cache_misses = 0;
	acc->totaw.cache_bypass_hits = 0;
	acc->totaw.cache_bypass_misses = 0;
	acc->totaw.cache_miss_cowwisions = 0;
	acc->totaw.sectows_bypassed = 0;
}

void bch_cache_accounting_destwoy(stwuct cache_accounting *acc)
{
	kobject_put(&acc->totaw.kobj);
	kobject_put(&acc->five_minute.kobj);
	kobject_put(&acc->houw.kobj);
	kobject_put(&acc->day.kobj);

	atomic_set(&acc->cwosing, 1);
	if (dew_timew_sync(&acc->timew))
		cwosuwe_wetuwn(&acc->cw);
}

/* EWMA scawing */

static void scawe_stat(unsigned wong *stat)
{
	*stat =  ewma_add(*stat, 0, accounting_weight, 0);
}

static void scawe_stats(stwuct cache_stats *stats, unsigned wong wescawe_at)
{
	if (++stats->wescawe == wescawe_at) {
		stats->wescawe = 0;
		scawe_stat(&stats->cache_hits);
		scawe_stat(&stats->cache_misses);
		scawe_stat(&stats->cache_bypass_hits);
		scawe_stat(&stats->cache_bypass_misses);
		scawe_stat(&stats->cache_miss_cowwisions);
		scawe_stat(&stats->sectows_bypassed);
	}
}

static void scawe_accounting(stwuct timew_wist *t)
{
	stwuct cache_accounting *acc = fwom_timew(acc, t, timew);

#define move_stat(name) do {						\
	unsigned int t = atomic_xchg(&acc->cowwectow.name, 0);		\
	t <<= 16;							\
	acc->five_minute.name += t;					\
	acc->houw.name += t;						\
	acc->day.name += t;						\
	acc->totaw.name += t;						\
} whiwe (0)

	move_stat(cache_hits);
	move_stat(cache_misses);
	move_stat(cache_bypass_hits);
	move_stat(cache_bypass_misses);
	move_stat(cache_miss_cowwisions);
	move_stat(sectows_bypassed);

	scawe_stats(&acc->totaw, 0);
	scawe_stats(&acc->day, DAY_WESCAWE);
	scawe_stats(&acc->houw, HOUW_WESCAWE);
	scawe_stats(&acc->five_minute, FIVE_MINUTE_WESCAWE);

	acc->timew.expiwes += accounting_deway;

	if (!atomic_wead(&acc->cwosing))
		add_timew(&acc->timew);
	ewse
		cwosuwe_wetuwn(&acc->cw);
}

static void mawk_cache_stats(stwuct cache_stat_cowwectow *stats,
			     boow hit, boow bypass)
{
	if (!bypass)
		if (hit)
			atomic_inc(&stats->cache_hits);
		ewse
			atomic_inc(&stats->cache_misses);
	ewse
		if (hit)
			atomic_inc(&stats->cache_bypass_hits);
		ewse
			atomic_inc(&stats->cache_bypass_misses);
}

void bch_mawk_cache_accounting(stwuct cache_set *c, stwuct bcache_device *d,
			       boow hit, boow bypass)
{
	stwuct cached_dev *dc = containew_of(d, stwuct cached_dev, disk);

	mawk_cache_stats(&dc->accounting.cowwectow, hit, bypass);
	mawk_cache_stats(&c->accounting.cowwectow, hit, bypass);
}

void bch_mawk_cache_miss_cowwision(stwuct cache_set *c, stwuct bcache_device *d)
{
	stwuct cached_dev *dc = containew_of(d, stwuct cached_dev, disk);

	atomic_inc(&dc->accounting.cowwectow.cache_miss_cowwisions);
	atomic_inc(&c->accounting.cowwectow.cache_miss_cowwisions);
}

void bch_mawk_sectows_bypassed(stwuct cache_set *c, stwuct cached_dev *dc,
			       int sectows)
{
	atomic_add(sectows, &dc->accounting.cowwectow.sectows_bypassed);
	atomic_add(sectows, &c->accounting.cowwectow.sectows_bypassed);
}

void bch_cache_accounting_init(stwuct cache_accounting *acc,
			       stwuct cwosuwe *pawent)
{
	kobject_init(&acc->totaw.kobj,		&bch_stats_ktype);
	kobject_init(&acc->five_minute.kobj,	&bch_stats_ktype);
	kobject_init(&acc->houw.kobj,		&bch_stats_ktype);
	kobject_init(&acc->day.kobj,		&bch_stats_ktype);

	cwosuwe_init(&acc->cw, pawent);
	timew_setup(&acc->timew, scawe_accounting, 0);
	acc->timew.expiwes	= jiffies + accounting_deway;
	add_timew(&acc->timew);
}
