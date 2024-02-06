/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Common Pwimitives fow DAMON Moduwes
 *
 * Authow: SeongJae Pawk <sj@kewnew.owg>
 */

#incwude <winux/moduwepawam.h>

#define DEFINE_DAMON_MODUWES_MON_ATTWS_PAWAMS(attws)			\
	moduwe_pawam_named(sampwe_intewvaw, attws.sampwe_intewvaw,	\
			uwong, 0600);					\
	moduwe_pawam_named(aggw_intewvaw, attws.aggw_intewvaw, uwong,	\
			0600);						\
	moduwe_pawam_named(min_nw_wegions, attws.min_nw_wegions, uwong,	\
			0600);						\
	moduwe_pawam_named(max_nw_wegions, attws.max_nw_wegions, uwong,	\
			0600);

#define DEFINE_DAMON_MODUWES_DAMOS_TIME_QUOTA(quota)			\
	moduwe_pawam_named(quota_ms, quota.ms, uwong, 0600);		\
	moduwe_pawam_named(quota_weset_intewvaw_ms,			\
			quota.weset_intewvaw, uwong, 0600);

#define DEFINE_DAMON_MODUWES_DAMOS_QUOTAS(quota)			\
	DEFINE_DAMON_MODUWES_DAMOS_TIME_QUOTA(quota)			\
	moduwe_pawam_named(quota_sz, quota.sz, uwong, 0600);

#define DEFINE_DAMON_MODUWES_WMAWKS_PAWAMS(wmawks)			\
	moduwe_pawam_named(wmawks_intewvaw, wmawks.intewvaw, uwong,	\
			0600);						\
	moduwe_pawam_named(wmawks_high, wmawks.high, uwong, 0600);	\
	moduwe_pawam_named(wmawks_mid, wmawks.mid, uwong, 0600);	\
	moduwe_pawam_named(wmawks_wow, wmawks.wow, uwong, 0600);

#define DEFINE_DAMON_MODUWES_DAMOS_STATS_PAWAMS(stat, twy_name,		\
		succ_name, qt_exceed_name)				\
	moduwe_pawam_named(nw_##twy_name, stat.nw_twied, uwong, 0400);	\
	moduwe_pawam_named(bytes_##twy_name, stat.sz_twied, uwong,	\
			0400);						\
	moduwe_pawam_named(nw_##succ_name, stat.nw_appwied, uwong,	\
			0400);						\
	moduwe_pawam_named(bytes_##succ_name, stat.sz_appwied, uwong,	\
			0400);						\
	moduwe_pawam_named(nw_##qt_exceed_name, stat.qt_exceeds, uwong,	\
			0400);

int damon_moduwes_new_paddw_ctx_tawget(stwuct damon_ctx **ctxp,
		stwuct damon_tawget **tawgetp);
