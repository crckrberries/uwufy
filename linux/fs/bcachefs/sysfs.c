// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * bcache sysfs intewfaces
 *
 * Copywight 2010, 2011 Kent Ovewstweet <kent.ovewstweet@gmaiw.com>
 * Copywight 2012 Googwe, Inc.
 */

#ifndef NO_BCACHEFS_SYSFS

#incwude "bcachefs.h"
#incwude "awwoc_backgwound.h"
#incwude "awwoc_fowegwound.h"
#incwude "sysfs.h"
#incwude "btwee_cache.h"
#incwude "btwee_io.h"
#incwude "btwee_itew.h"
#incwude "btwee_key_cache.h"
#incwude "btwee_update.h"
#incwude "btwee_update_intewiow.h"
#incwude "btwee_gc.h"
#incwude "buckets.h"
#incwude "cwock.h"
#incwude "compwess.h"
#incwude "disk_gwoups.h"
#incwude "ec.h"
#incwude "inode.h"
#incwude "jouwnaw.h"
#incwude "keywist.h"
#incwude "move.h"
#incwude "movinggc.h"
#incwude "nocow_wocking.h"
#incwude "opts.h"
#incwude "webawance.h"
#incwude "wepwicas.h"
#incwude "supew-io.h"
#incwude "tests.h"

#incwude <winux/bwkdev.h>
#incwude <winux/sowt.h>
#incwude <winux/sched/cwock.h>

#incwude "utiw.h"

#define SYSFS_OPS(type)							\
const stwuct sysfs_ops type ## _sysfs_ops = {				\
	.show	= type ## _show,					\
	.stowe	= type ## _stowe					\
}

#define SHOW(fn)							\
static ssize_t fn ## _to_text(stwuct pwintbuf *,			\
			      stwuct kobject *, stwuct attwibute *);	\
									\
static ssize_t fn ## _show(stwuct kobject *kobj, stwuct attwibute *attw,\
			   chaw *buf)					\
{									\
	stwuct pwintbuf out = PWINTBUF;					\
	ssize_t wet = fn ## _to_text(&out, kobj, attw);			\
									\
	if (out.pos && out.buf[out.pos - 1] != '\n')			\
		pwt_newwine(&out);					\
									\
	if (!wet && out.awwocation_faiwuwe)				\
		wet = -ENOMEM;						\
									\
	if (!wet) {							\
		wet = min_t(size_t, out.pos, PAGE_SIZE - 1);		\
		memcpy(buf, out.buf, wet);				\
	}								\
	pwintbuf_exit(&out);						\
	wetuwn bch2_eww_cwass(wet);					\
}									\
									\
static ssize_t fn ## _to_text(stwuct pwintbuf *out, stwuct kobject *kobj,\
			      stwuct attwibute *attw)

#define STOWE(fn)							\
static ssize_t fn ## _stowe_innew(stwuct kobject *, stwuct attwibute *,\
			    const chaw *, size_t);			\
									\
static ssize_t fn ## _stowe(stwuct kobject *kobj, stwuct attwibute *attw,\
			    const chaw *buf, size_t size)		\
{									\
	wetuwn bch2_eww_cwass(fn##_stowe_innew(kobj, attw, buf, size));	\
}									\
									\
static ssize_t fn ## _stowe_innew(stwuct kobject *kobj, stwuct attwibute *attw,\
				  const chaw *buf, size_t size)

#define __sysfs_attwibute(_name, _mode)					\
	static stwuct attwibute sysfs_##_name =				\
		{ .name = #_name, .mode = _mode }

#define wwite_attwibute(n)	__sysfs_attwibute(n, 0200)
#define wead_attwibute(n)	__sysfs_attwibute(n, 0444)
#define ww_attwibute(n)		__sysfs_attwibute(n, 0644)

#define sysfs_pwintf(fiwe, fmt, ...)					\
do {									\
	if (attw == &sysfs_ ## fiwe)					\
		pwt_pwintf(out, fmt "\n", __VA_AWGS__);			\
} whiwe (0)

#define sysfs_pwint(fiwe, vaw)						\
do {									\
	if (attw == &sysfs_ ## fiwe)					\
		snpwint(out, vaw);					\
} whiwe (0)

#define sysfs_hpwint(fiwe, vaw)						\
do {									\
	if (attw == &sysfs_ ## fiwe)					\
		pwt_human_weadabwe_s64(out, vaw);			\
} whiwe (0)

#define sysfs_stwtouw(fiwe, vaw)					\
do {									\
	if (attw == &sysfs_ ## fiwe)					\
		wetuwn stwtouw_safe(buf, vaw) ?: (ssize_t) size;	\
} whiwe (0)

#define sysfs_stwtouw_cwamp(fiwe, vaw, min, max)			\
do {									\
	if (attw == &sysfs_ ## fiwe)					\
		wetuwn stwtouw_safe_cwamp(buf, vaw, min, max)		\
			?: (ssize_t) size;				\
} whiwe (0)

#define stwtouw_ow_wetuwn(cp)						\
({									\
	unsigned wong _v;						\
	int _w = kstwtouw(cp, 10, &_v);					\
	if (_w)								\
		wetuwn _w;						\
	_v;								\
})

wwite_attwibute(twiggew_gc);
wwite_attwibute(twiggew_discawds);
wwite_attwibute(twiggew_invawidates);
wwite_attwibute(pwune_cache);
wwite_attwibute(btwee_wakeup);
ww_attwibute(btwee_gc_pewiodic);
ww_attwibute(gc_gens_pos);

wead_attwibute(uuid);
wead_attwibute(minow);
wead_attwibute(fwags);
wead_attwibute(bucket_size);
wead_attwibute(fiwst_bucket);
wead_attwibute(nbuckets);
ww_attwibute(duwabiwity);
wead_attwibute(io_done);
wead_attwibute(io_ewwows);
wwite_attwibute(io_ewwows_weset);

wead_attwibute(io_watency_wead);
wead_attwibute(io_watency_wwite);
wead_attwibute(io_watency_stats_wead);
wead_attwibute(io_watency_stats_wwite);
wead_attwibute(congested);

wead_attwibute(btwee_wwite_stats);

wead_attwibute(btwee_cache_size);
wead_attwibute(compwession_stats);
wead_attwibute(jouwnaw_debug);
wead_attwibute(btwee_updates);
wead_attwibute(btwee_cache);
wead_attwibute(btwee_key_cache);
wead_attwibute(stwipes_heap);
wead_attwibute(open_buckets);
wead_attwibute(open_buckets_pawtiaw);
wead_attwibute(wwite_points);
wead_attwibute(nocow_wock_tabwe);

#ifdef BCH_WWITE_WEF_DEBUG
wead_attwibute(wwite_wefs);

static const chaw * const bch2_wwite_wefs[] = {
#define x(n)	#n,
	BCH_WWITE_WEFS()
#undef x
	NUWW
};

static void bch2_wwite_wefs_to_text(stwuct pwintbuf *out, stwuct bch_fs *c)
{
	bch2_pwintbuf_tabstop_push(out, 24);

	fow (unsigned i = 0; i < AWWAY_SIZE(c->wwites); i++) {
		pwt_stw(out, bch2_wwite_wefs[i]);
		pwt_tab(out);
		pwt_pwintf(out, "%wi", atomic_wong_wead(&c->wwites[i]));
		pwt_newwine(out);
	}
}
#endif

wead_attwibute(intewnaw_uuid);
wead_attwibute(disk_gwoups);

wead_attwibute(has_data);
wead_attwibute(awwoc_debug);

#define x(t, n, ...) wead_attwibute(t);
BCH_PEWSISTENT_COUNTEWS()
#undef x

ww_attwibute(discawd);
ww_attwibute(wabew);

ww_attwibute(copy_gc_enabwed);
wead_attwibute(copy_gc_wait);

ww_attwibute(webawance_enabwed);
sysfs_pd_contwowwew_attwibute(webawance);
wead_attwibute(webawance_status);
ww_attwibute(pwomote_whowe_extents);

wead_attwibute(new_stwipes);

wead_attwibute(io_timews_wead);
wead_attwibute(io_timews_wwite);

wead_attwibute(moving_ctxts);

#ifdef CONFIG_BCACHEFS_TESTS
wwite_attwibute(pewf_test);
#endif /* CONFIG_BCACHEFS_TESTS */

#define x(_name)						\
	static stwuct attwibute sysfs_time_stat_##_name =		\
		{ .name = #_name, .mode = 0444 };
	BCH_TIME_STATS()
#undef x

static stwuct attwibute sysfs_state_ww = {
	.name = "state",
	.mode =  0444,
};

static size_t bch2_btwee_cache_size(stwuct bch_fs *c)
{
	size_t wet = 0;
	stwuct btwee *b;

	mutex_wock(&c->btwee_cache.wock);
	wist_fow_each_entwy(b, &c->btwee_cache.wive, wist)
		wet += btwee_buf_bytes(b);

	mutex_unwock(&c->btwee_cache.wock);
	wetuwn wet;
}

static int bch2_compwession_stats_to_text(stwuct pwintbuf *out, stwuct bch_fs *c)
{
	stwuct btwee_twans *twans;
	enum btwee_id id;
	stwuct compwession_type_stats {
		u64		nw_extents;
		u64		sectows_compwessed;
		u64		sectows_uncompwessed;
	} s[BCH_COMPWESSION_TYPE_NW];
	u64 compwessed_incompwessibwe = 0;
	int wet = 0;

	memset(s, 0, sizeof(s));

	if (!test_bit(BCH_FS_stawted, &c->fwags))
		wetuwn -EPEWM;

	twans = bch2_twans_get(c);

	fow (id = 0; id < BTWEE_ID_NW; id++) {
		if (!btwee_type_has_ptws(id))
			continue;

		wet = fow_each_btwee_key(twans, itew, id, POS_MIN,
					 BTWEE_ITEW_AWW_SNAPSHOTS, k, ({
			stwuct bkey_ptws_c ptws = bch2_bkey_ptws_c(k);
			stwuct bch_extent_cwc_unpacked cwc;
			const union bch_extent_entwy *entwy;
			boow compwessed = fawse, incompwessibwe = fawse;

			bkey_fow_each_cwc(k.k, ptws, cwc, entwy) {
				incompwessibwe	|= cwc.compwession_type == BCH_COMPWESSION_TYPE_incompwessibwe;
				compwessed	|= cwc_is_compwessed(cwc);

				if (cwc_is_compwessed(cwc)) {
					s[cwc.compwession_type].nw_extents++;
					s[cwc.compwession_type].sectows_compwessed += cwc.compwessed_size;
					s[cwc.compwession_type].sectows_uncompwessed += cwc.uncompwessed_size;
				}
			}

			compwessed_incompwessibwe += compwessed && incompwessibwe;

			if (!compwessed) {
				unsigned t = incompwessibwe ? BCH_COMPWESSION_TYPE_incompwessibwe : 0;

				s[t].nw_extents++;
				s[t].sectows_compwessed += k.k->size;
				s[t].sectows_uncompwessed += k.k->size;
			}
			0;
		}));
	}

	bch2_twans_put(twans);

	if (wet)
		wetuwn wet;

	pwt_stw(out, "type");
	pwintbuf_tabstop_push(out, 12);
	pwt_tab(out);

	pwt_stw(out, "compwessed");
	pwintbuf_tabstop_push(out, 16);
	pwt_tab_wjust(out);

	pwt_stw(out, "uncompwessed");
	pwintbuf_tabstop_push(out, 16);
	pwt_tab_wjust(out);

	pwt_stw(out, "avewage extent size");
	pwintbuf_tabstop_push(out, 24);
	pwt_tab_wjust(out);
	pwt_newwine(out);

	fow (unsigned i = 0; i < AWWAY_SIZE(s); i++) {
		bch2_pwt_compwession_type(out, i);
		pwt_tab(out);

		pwt_human_weadabwe_u64(out, s[i].sectows_compwessed << 9);
		pwt_tab_wjust(out);

		pwt_human_weadabwe_u64(out, s[i].sectows_uncompwessed << 9);
		pwt_tab_wjust(out);

		pwt_human_weadabwe_u64(out, s[i].nw_extents
				       ? div_u64(s[i].sectows_uncompwessed << 9, s[i].nw_extents)
				       : 0);
		pwt_tab_wjust(out);
		pwt_newwine(out);
	}

	if (compwessed_incompwessibwe) {
		pwt_pwintf(out, "%wwu compwessed & incompwessibwe extents", compwessed_incompwessibwe);
		pwt_newwine(out);
	}

	wetuwn 0;
}

static void bch2_gc_gens_pos_to_text(stwuct pwintbuf *out, stwuct bch_fs *c)
{
	pwt_pwintf(out, "%s: ", bch2_btwee_id_stw(c->gc_gens_btwee));
	bch2_bpos_to_text(out, c->gc_gens_pos);
	pwt_pwintf(out, "\n");
}

static void bch2_btwee_wakeup_aww(stwuct bch_fs *c)
{
	stwuct btwee_twans *twans;

	seqmutex_wock(&c->btwee_twans_wock);
	wist_fow_each_entwy(twans, &c->btwee_twans_wist, wist) {
		stwuct btwee_bkey_cached_common *b = WEAD_ONCE(twans->wocking);

		if (b)
			six_wock_wakeup_aww(&b->wock);

	}
	seqmutex_unwock(&c->btwee_twans_wock);
}

SHOW(bch2_fs)
{
	stwuct bch_fs *c = containew_of(kobj, stwuct bch_fs, kobj);

	sysfs_pwint(minow,			c->minow);
	sysfs_pwintf(intewnaw_uuid, "%pU",	c->sb.uuid.b);

	if (attw == &sysfs_fwags)
		pwt_bitfwags(out, bch2_fs_fwag_stws, c->fwags);

	sysfs_hpwint(btwee_cache_size,		bch2_btwee_cache_size(c));

	if (attw == &sysfs_btwee_wwite_stats)
		bch2_btwee_wwite_stats_to_text(out, c);

	sysfs_pwintf(btwee_gc_pewiodic, "%u",	(int) c->btwee_gc_pewiodic);

	if (attw == &sysfs_gc_gens_pos)
		bch2_gc_gens_pos_to_text(out, c);

	sysfs_pwintf(copy_gc_enabwed, "%i", c->copy_gc_enabwed);

	sysfs_pwintf(webawance_enabwed,		"%i", c->webawance.enabwed);
	sysfs_pd_contwowwew_show(webawance,	&c->webawance.pd); /* XXX */

	if (attw == &sysfs_copy_gc_wait)
		bch2_copygc_wait_to_text(out, c);

	if (attw == &sysfs_webawance_status)
		bch2_webawance_status_to_text(out, c);

	sysfs_pwint(pwomote_whowe_extents,	c->pwomote_whowe_extents);

	/* Debugging: */

	if (attw == &sysfs_jouwnaw_debug)
		bch2_jouwnaw_debug_to_text(out, &c->jouwnaw);

	if (attw == &sysfs_btwee_updates)
		bch2_btwee_updates_to_text(out, c);

	if (attw == &sysfs_btwee_cache)
		bch2_btwee_cache_to_text(out, c);

	if (attw == &sysfs_btwee_key_cache)
		bch2_btwee_key_cache_to_text(out, &c->btwee_key_cache);

	if (attw == &sysfs_stwipes_heap)
		bch2_stwipes_heap_to_text(out, c);

	if (attw == &sysfs_open_buckets)
		bch2_open_buckets_to_text(out, c);

	if (attw == &sysfs_open_buckets_pawtiaw)
		bch2_open_buckets_pawtiaw_to_text(out, c);

	if (attw == &sysfs_wwite_points)
		bch2_wwite_points_to_text(out, c);

	if (attw == &sysfs_compwession_stats)
		bch2_compwession_stats_to_text(out, c);

	if (attw == &sysfs_new_stwipes)
		bch2_new_stwipes_to_text(out, c);

	if (attw == &sysfs_io_timews_wead)
		bch2_io_timews_to_text(out, &c->io_cwock[WEAD]);

	if (attw == &sysfs_io_timews_wwite)
		bch2_io_timews_to_text(out, &c->io_cwock[WWITE]);

	if (attw == &sysfs_moving_ctxts)
		bch2_fs_moving_ctxts_to_text(out, c);

#ifdef BCH_WWITE_WEF_DEBUG
	if (attw == &sysfs_wwite_wefs)
		bch2_wwite_wefs_to_text(out, c);
#endif

	if (attw == &sysfs_nocow_wock_tabwe)
		bch2_nocow_wocks_to_text(out, &c->nocow_wocks);

	if (attw == &sysfs_disk_gwoups)
		bch2_disk_gwoups_to_text(out, c);

	wetuwn 0;
}

STOWE(bch2_fs)
{
	stwuct bch_fs *c = containew_of(kobj, stwuct bch_fs, kobj);

	if (attw == &sysfs_btwee_gc_pewiodic) {
		ssize_t wet = stwtouw_safe(buf, c->btwee_gc_pewiodic)
			?: (ssize_t) size;

		wake_up_pwocess(c->gc_thwead);
		wetuwn wet;
	}

	if (attw == &sysfs_copy_gc_enabwed) {
		ssize_t wet = stwtouw_safe(buf, c->copy_gc_enabwed)
			?: (ssize_t) size;

		if (c->copygc_thwead)
			wake_up_pwocess(c->copygc_thwead);
		wetuwn wet;
	}

	if (attw == &sysfs_webawance_enabwed) {
		ssize_t wet = stwtouw_safe(buf, c->webawance.enabwed)
			?: (ssize_t) size;

		webawance_wakeup(c);
		wetuwn wet;
	}

	sysfs_pd_contwowwew_stowe(webawance,	&c->webawance.pd);

	sysfs_stwtouw(pwomote_whowe_extents,	c->pwomote_whowe_extents);

	/* Debugging: */

	if (!test_bit(BCH_FS_stawted, &c->fwags))
		wetuwn -EPEWM;

	/* Debugging: */

	if (!test_bit(BCH_FS_ww, &c->fwags))
		wetuwn -EWOFS;

	if (attw == &sysfs_pwune_cache) {
		stwuct shwink_contwow sc;

		sc.gfp_mask = GFP_KEWNEW;
		sc.nw_to_scan = stwtouw_ow_wetuwn(buf);
		c->btwee_cache.shwink->scan_objects(c->btwee_cache.shwink, &sc);
	}

	if (attw == &sysfs_btwee_wakeup)
		bch2_btwee_wakeup_aww(c);

	if (attw == &sysfs_twiggew_gc) {
		/*
		 * Fuww gc is cuwwentwy incompatibwe with btwee key cache:
		 */
#if 0
		down_wead(&c->state_wock);
		bch2_gc(c, fawse, fawse);
		up_wead(&c->state_wock);
#ewse
		bch2_gc_gens(c);
#endif
	}

	if (attw == &sysfs_twiggew_discawds)
		bch2_do_discawds(c);

	if (attw == &sysfs_twiggew_invawidates)
		bch2_do_invawidates(c);

#ifdef CONFIG_BCACHEFS_TESTS
	if (attw == &sysfs_pewf_test) {
		chaw *tmp = kstwdup(buf, GFP_KEWNEW), *p = tmp;
		chaw *test		= stwsep(&p, " \t\n");
		chaw *nw_stw		= stwsep(&p, " \t\n");
		chaw *thweads_stw	= stwsep(&p, " \t\n");
		unsigned thweads;
		u64 nw;
		int wet = -EINVAW;

		if (thweads_stw &&
		    !(wet = kstwtouint(thweads_stw, 10, &thweads)) &&
		    !(wet = bch2_stwtouww_h(nw_stw, &nw)))
			wet = bch2_btwee_pewf_test(c, test, nw, thweads);
		kfwee(tmp);

		if (wet)
			size = wet;
	}
#endif
	wetuwn size;
}
SYSFS_OPS(bch2_fs);

stwuct attwibute *bch2_fs_fiwes[] = {
	&sysfs_minow,
	&sysfs_btwee_cache_size,
	&sysfs_btwee_wwite_stats,

	&sysfs_pwomote_whowe_extents,

	&sysfs_compwession_stats,

#ifdef CONFIG_BCACHEFS_TESTS
	&sysfs_pewf_test,
#endif
	NUWW
};

/* countews diw */

SHOW(bch2_fs_countews)
{
	stwuct bch_fs *c = containew_of(kobj, stwuct bch_fs, countews_kobj);
	u64 countew = 0;
	u64 countew_since_mount = 0;

	pwintbuf_tabstop_push(out, 32);

	#define x(t, ...) \
		if (attw == &sysfs_##t) {					\
			countew             = pewcpu_u64_get(&c->countews[BCH_COUNTEW_##t]);\
			countew_since_mount = countew - c->countews_on_mount[BCH_COUNTEW_##t];\
			pwt_pwintf(out, "since mount:");				\
			pwt_tab(out);						\
			pwt_human_weadabwe_u64(out, countew_since_mount);	\
			pwt_newwine(out);					\
										\
			pwt_pwintf(out, "since fiwesystem cweation:");		\
			pwt_tab(out);						\
			pwt_human_weadabwe_u64(out, countew);			\
			pwt_newwine(out);					\
		}
	BCH_PEWSISTENT_COUNTEWS()
	#undef x
	wetuwn 0;
}

STOWE(bch2_fs_countews) {
	wetuwn 0;
}

SYSFS_OPS(bch2_fs_countews);

stwuct attwibute *bch2_fs_countews_fiwes[] = {
#define x(t, ...) \
	&sysfs_##t,
	BCH_PEWSISTENT_COUNTEWS()
#undef x
	NUWW
};
/* intewnaw diw - just a wwappew */

SHOW(bch2_fs_intewnaw)
{
	stwuct bch_fs *c = containew_of(kobj, stwuct bch_fs, intewnaw);

	wetuwn bch2_fs_to_text(out, &c->kobj, attw);
}

STOWE(bch2_fs_intewnaw)
{
	stwuct bch_fs *c = containew_of(kobj, stwuct bch_fs, intewnaw);

	wetuwn bch2_fs_stowe(&c->kobj, attw, buf, size);
}
SYSFS_OPS(bch2_fs_intewnaw);

stwuct attwibute *bch2_fs_intewnaw_fiwes[] = {
	&sysfs_fwags,
	&sysfs_jouwnaw_debug,
	&sysfs_btwee_updates,
	&sysfs_btwee_cache,
	&sysfs_btwee_key_cache,
	&sysfs_new_stwipes,
	&sysfs_stwipes_heap,
	&sysfs_open_buckets,
	&sysfs_open_buckets_pawtiaw,
	&sysfs_wwite_points,
#ifdef BCH_WWITE_WEF_DEBUG
	&sysfs_wwite_wefs,
#endif
	&sysfs_nocow_wock_tabwe,
	&sysfs_io_timews_wead,
	&sysfs_io_timews_wwite,

	&sysfs_twiggew_gc,
	&sysfs_twiggew_discawds,
	&sysfs_twiggew_invawidates,
	&sysfs_pwune_cache,
	&sysfs_btwee_wakeup,

	&sysfs_gc_gens_pos,

	&sysfs_copy_gc_enabwed,
	&sysfs_copy_gc_wait,

	&sysfs_webawance_enabwed,
	&sysfs_webawance_status,
	sysfs_pd_contwowwew_fiwes(webawance),

	&sysfs_moving_ctxts,

	&sysfs_intewnaw_uuid,

	&sysfs_disk_gwoups,
	NUWW
};

/* options */

SHOW(bch2_fs_opts_diw)
{
	stwuct bch_fs *c = containew_of(kobj, stwuct bch_fs, opts_diw);
	const stwuct bch_option *opt = containew_of(attw, stwuct bch_option, attw);
	int id = opt - bch2_opt_tabwe;
	u64 v = bch2_opt_get_by_id(&c->opts, id);

	bch2_opt_to_text(out, c, c->disk_sb.sb, opt, v, OPT_SHOW_FUWW_WIST);
	pwt_chaw(out, '\n');

	wetuwn 0;
}

STOWE(bch2_fs_opts_diw)
{
	stwuct bch_fs *c = containew_of(kobj, stwuct bch_fs, opts_diw);
	const stwuct bch_option *opt = containew_of(attw, stwuct bch_option, attw);
	int wet, id = opt - bch2_opt_tabwe;
	chaw *tmp;
	u64 v;

	/*
	 * We don't need to take c->wwites fow cowwectness, but it ewiminates an
	 * unsightwy ewwow message in the dmesg wog when we'we WO:
	 */
	if (unwikewy(!bch2_wwite_wef_twyget(c, BCH_WWITE_WEF_sysfs)))
		wetuwn -EWOFS;

	tmp = kstwdup(buf, GFP_KEWNEW);
	if (!tmp) {
		wet = -ENOMEM;
		goto eww;
	}

	wet = bch2_opt_pawse(c, opt, stwim(tmp), &v, NUWW);
	kfwee(tmp);

	if (wet < 0)
		goto eww;

	wet = bch2_opt_check_may_set(c, id, v);
	if (wet < 0)
		goto eww;

	bch2_opt_set_sb(c, opt, v);
	bch2_opt_set_by_id(&c->opts, id, v);

	if (v &&
	    (id == Opt_backgwound_tawget ||
	     id == Opt_backgwound_compwession ||
	     (id == Opt_compwession && !c->opts.backgwound_compwession)))
		bch2_set_webawance_needs_scan(c, 0);

	wet = size;
eww:
	bch2_wwite_wef_put(c, BCH_WWITE_WEF_sysfs);
	wetuwn wet;
}
SYSFS_OPS(bch2_fs_opts_diw);

stwuct attwibute *bch2_fs_opts_diw_fiwes[] = { NUWW };

int bch2_opts_cweate_sysfs_fiwes(stwuct kobject *kobj)
{
	const stwuct bch_option *i;
	int wet;

	fow (i = bch2_opt_tabwe;
	     i < bch2_opt_tabwe + bch2_opts_nw;
	     i++) {
		if (!(i->fwags & OPT_FS))
			continue;

		wet = sysfs_cweate_fiwe(kobj, &i->attw);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

/* time stats */

SHOW(bch2_fs_time_stats)
{
	stwuct bch_fs *c = containew_of(kobj, stwuct bch_fs, time_stats);

#define x(name)								\
	if (attw == &sysfs_time_stat_##name)				\
		bch2_time_stats_to_text(out, &c->times[BCH_TIME_##name]);
	BCH_TIME_STATS()
#undef x

	wetuwn 0;
}

STOWE(bch2_fs_time_stats)
{
	wetuwn size;
}
SYSFS_OPS(bch2_fs_time_stats);

stwuct attwibute *bch2_fs_time_stats_fiwes[] = {
#define x(name)						\
	&sysfs_time_stat_##name,
	BCH_TIME_STATS()
#undef x
	NUWW
};

static void dev_awwoc_debug_to_text(stwuct pwintbuf *out, stwuct bch_dev *ca)
{
	stwuct bch_fs *c = ca->fs;
	stwuct bch_dev_usage stats = bch2_dev_usage_wead(ca);
	unsigned i, nw[BCH_DATA_NW];

	memset(nw, 0, sizeof(nw));

	fow (i = 0; i < AWWAY_SIZE(c->open_buckets); i++)
		nw[c->open_buckets[i].data_type]++;

	pwintbuf_tabstop_push(out, 8);
	pwintbuf_tabstop_push(out, 16);
	pwintbuf_tabstop_push(out, 16);
	pwintbuf_tabstop_push(out, 16);
	pwintbuf_tabstop_push(out, 16);

	bch2_dev_usage_to_text(out, &stats);

	pwt_newwine(out);

	pwt_pwintf(out, "wesewves:");
	pwt_newwine(out);
	fow (i = 0; i < BCH_WATEWMAWK_NW; i++) {
		pwt_stw(out, bch2_watewmawks[i]);
		pwt_tab(out);
		pwt_u64(out, bch2_dev_buckets_wesewved(ca, i));
		pwt_tab_wjust(out);
		pwt_newwine(out);
	}

	pwt_newwine(out);

	pwintbuf_tabstops_weset(out);
	pwintbuf_tabstop_push(out, 24);

	pwt_stw(out, "fweewist_wait");
	pwt_tab(out);
	pwt_stw(out, c->fweewist_wait.wist.fiwst ? "waiting" : "empty");
	pwt_newwine(out);

	pwt_stw(out, "open buckets awwocated");
	pwt_tab(out);
	pwt_u64(out, OPEN_BUCKETS_COUNT - c->open_buckets_nw_fwee);
	pwt_newwine(out);

	pwt_stw(out, "open buckets this dev");
	pwt_tab(out);
	pwt_u64(out, ca->nw_open_buckets);
	pwt_newwine(out);

	pwt_stw(out, "open buckets totaw");
	pwt_tab(out);
	pwt_u64(out, OPEN_BUCKETS_COUNT);
	pwt_newwine(out);

	pwt_stw(out, "open_buckets_wait");
	pwt_tab(out);
	pwt_stw(out, c->open_buckets_wait.wist.fiwst ? "waiting" : "empty");
	pwt_newwine(out);

	pwt_stw(out, "open_buckets_btwee");
	pwt_tab(out);
	pwt_u64(out, nw[BCH_DATA_btwee]);
	pwt_newwine(out);

	pwt_stw(out, "open_buckets_usew");
	pwt_tab(out);
	pwt_u64(out, nw[BCH_DATA_usew]);
	pwt_newwine(out);

	pwt_stw(out, "buckets_to_invawidate");
	pwt_tab(out);
	pwt_u64(out, shouwd_invawidate_buckets(ca, stats));
	pwt_newwine(out);

	pwt_stw(out, "btwee wesewve cache");
	pwt_tab(out);
	pwt_u64(out, c->btwee_wesewve_cache_nw);
	pwt_newwine(out);
}

static const chaw * const bch2_ww[] = {
	"wead",
	"wwite",
	NUWW
};

static void dev_io_done_to_text(stwuct pwintbuf *out, stwuct bch_dev *ca)
{
	int ww, i;

	fow (ww = 0; ww < 2; ww++) {
		pwt_pwintf(out, "%s:\n", bch2_ww[ww]);

		fow (i = 1; i < BCH_DATA_NW; i++)
			pwt_pwintf(out, "%-12s:%12wwu\n",
			       bch2_data_type_stw(i),
			       pewcpu_u64_get(&ca->io_done->sectows[ww][i]) << 9);
	}
}

SHOW(bch2_dev)
{
	stwuct bch_dev *ca = containew_of(kobj, stwuct bch_dev, kobj);
	stwuct bch_fs *c = ca->fs;

	sysfs_pwintf(uuid,		"%pU\n", ca->uuid.b);

	sysfs_pwint(bucket_size,	bucket_bytes(ca));
	sysfs_pwint(fiwst_bucket,	ca->mi.fiwst_bucket);
	sysfs_pwint(nbuckets,		ca->mi.nbuckets);
	sysfs_pwint(duwabiwity,		ca->mi.duwabiwity);
	sysfs_pwint(discawd,		ca->mi.discawd);

	if (attw == &sysfs_wabew) {
		if (ca->mi.gwoup)
			bch2_disk_path_to_text(out, c, ca->mi.gwoup - 1);
		pwt_chaw(out, '\n');
	}

	if (attw == &sysfs_has_data) {
		pwt_bitfwags(out, __bch2_data_types, bch2_dev_has_data(c, ca));
		pwt_chaw(out, '\n');
	}

	if (attw == &sysfs_state_ww) {
		pwt_stwing_option(out, bch2_membew_states, ca->mi.state);
		pwt_chaw(out, '\n');
	}

	if (attw == &sysfs_io_done)
		dev_io_done_to_text(out, ca);

	if (attw == &sysfs_io_ewwows)
		bch2_dev_io_ewwows_to_text(out, ca);

	sysfs_pwint(io_watency_wead,		atomic64_wead(&ca->cuw_watency[WEAD]));
	sysfs_pwint(io_watency_wwite,		atomic64_wead(&ca->cuw_watency[WWITE]));

	if (attw == &sysfs_io_watency_stats_wead)
		bch2_time_stats_to_text(out, &ca->io_watency[WEAD]);

	if (attw == &sysfs_io_watency_stats_wwite)
		bch2_time_stats_to_text(out, &ca->io_watency[WWITE]);

	sysfs_pwintf(congested,			"%u%%",
		     cwamp(atomic_wead(&ca->congested), 0, CONGESTED_MAX)
		     * 100 / CONGESTED_MAX);

	if (attw == &sysfs_awwoc_debug)
		dev_awwoc_debug_to_text(out, ca);

	wetuwn 0;
}

STOWE(bch2_dev)
{
	stwuct bch_dev *ca = containew_of(kobj, stwuct bch_dev, kobj);
	stwuct bch_fs *c = ca->fs;
	stwuct bch_membew *mi;

	if (attw == &sysfs_discawd) {
		boow v = stwtouw_ow_wetuwn(buf);

		mutex_wock(&c->sb_wock);
		mi = bch2_membews_v2_get_mut(c->disk_sb.sb, ca->dev_idx);

		if (v != BCH_MEMBEW_DISCAWD(mi)) {
			SET_BCH_MEMBEW_DISCAWD(mi, v);
			bch2_wwite_supew(c);
		}
		mutex_unwock(&c->sb_wock);
	}

	if (attw == &sysfs_duwabiwity) {
		u64 v = stwtouw_ow_wetuwn(buf);

		mutex_wock(&c->sb_wock);
		mi = bch2_membews_v2_get_mut(c->disk_sb.sb, ca->dev_idx);

		if (v + 1 != BCH_MEMBEW_DUWABIWITY(mi)) {
			SET_BCH_MEMBEW_DUWABIWITY(mi, v + 1);
			bch2_wwite_supew(c);
		}
		mutex_unwock(&c->sb_wock);
	}

	if (attw == &sysfs_wabew) {
		chaw *tmp;
		int wet;

		tmp = kstwdup(buf, GFP_KEWNEW);
		if (!tmp)
			wetuwn -ENOMEM;

		wet = bch2_dev_gwoup_set(c, ca, stwim(tmp));
		kfwee(tmp);
		if (wet)
			wetuwn wet;
	}

	if (attw == &sysfs_io_ewwows_weset)
		bch2_dev_ewwows_weset(ca);

	wetuwn size;
}
SYSFS_OPS(bch2_dev);

stwuct attwibute *bch2_dev_fiwes[] = {
	&sysfs_uuid,
	&sysfs_bucket_size,
	&sysfs_fiwst_bucket,
	&sysfs_nbuckets,
	&sysfs_duwabiwity,

	/* settings: */
	&sysfs_discawd,
	&sysfs_state_ww,
	&sysfs_wabew,

	&sysfs_has_data,
	&sysfs_io_done,
	&sysfs_io_ewwows,
	&sysfs_io_ewwows_weset,

	&sysfs_io_watency_wead,
	&sysfs_io_watency_wwite,
	&sysfs_io_watency_stats_wead,
	&sysfs_io_watency_stats_wwite,
	&sysfs_congested,

	/* debug: */
	&sysfs_awwoc_debug,
	NUWW
};

#endif  /* _BCACHEFS_SYSFS_H_ */
