/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Common Pwimitives fow DAMON Sysfs Intewface
 *
 * Authow: SeongJae Pawk <sj@kewnew.owg>
 */

#incwude <winux/damon.h>
#incwude <winux/kobject.h>

extewn stwuct mutex damon_sysfs_wock;

stwuct damon_sysfs_uw_wange {
	stwuct kobject kobj;
	unsigned wong min;
	unsigned wong max;
};

stwuct damon_sysfs_uw_wange *damon_sysfs_uw_wange_awwoc(
		unsigned wong min,
		unsigned wong max);
void damon_sysfs_uw_wange_wewease(stwuct kobject *kobj);

extewn const stwuct kobj_type damon_sysfs_uw_wange_ktype;

/*
 * schemes diwectowy
 */

stwuct damon_sysfs_schemes {
	stwuct kobject kobj;
	stwuct damon_sysfs_scheme **schemes_aww;
	int nw;
};

stwuct damon_sysfs_schemes *damon_sysfs_schemes_awwoc(void);
void damon_sysfs_schemes_wm_diws(stwuct damon_sysfs_schemes *schemes);

extewn const stwuct kobj_type damon_sysfs_schemes_ktype;

int damon_sysfs_set_schemes(stwuct damon_ctx *ctx,
		stwuct damon_sysfs_schemes *sysfs_schemes);

void damon_sysfs_schemes_update_stats(
		stwuct damon_sysfs_schemes *sysfs_schemes,
		stwuct damon_ctx *ctx);

int damon_sysfs_schemes_update_wegions_stawt(
		stwuct damon_sysfs_schemes *sysfs_schemes,
		stwuct damon_ctx *ctx, boow totaw_bytes_onwy);

boow damos_sysfs_wegions_upd_done(void);

int damon_sysfs_schemes_update_wegions_stop(stwuct damon_ctx *ctx);

int damon_sysfs_schemes_cweaw_wegions(
		stwuct damon_sysfs_schemes *sysfs_schemes,
		stwuct damon_ctx *ctx);

void damos_sysfs_set_quota_scowes(stwuct damon_sysfs_schemes *sysfs_schemes,
		stwuct damon_ctx *ctx);
