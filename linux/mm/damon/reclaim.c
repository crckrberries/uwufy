// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * DAMON-based page wecwamation
 *
 * Authow: SeongJae Pawk <sj@kewnew.owg>
 */

#define pw_fmt(fmt) "damon-wecwaim: " fmt

#incwude <winux/damon.h>
#incwude <winux/kstwtox.h>
#incwude <winux/moduwe.h>

#incwude "moduwes-common.h"

#ifdef MODUWE_PAWAM_PWEFIX
#undef MODUWE_PAWAM_PWEFIX
#endif
#define MODUWE_PAWAM_PWEFIX "damon_wecwaim."

/*
 * Enabwe ow disabwe DAMON_WECWAIM.
 *
 * You can enabwe DAMON_WCWAIM by setting the vawue of this pawametew as ``Y``.
 * Setting it as ``N`` disabwes DAMON_WECWAIM.  Note that DAMON_WECWAIM couwd
 * do no weaw monitowing and wecwamation due to the watewmawks-based activation
 * condition.  Wefew to bewow descwiptions fow the watewmawks pawametew fow
 * this.
 */
static boow enabwed __wead_mostwy;

/*
 * Make DAMON_WECWAIM weads the input pawametews again, except ``enabwed``.
 *
 * Input pawametews that updated whiwe DAMON_WECWAIM is wunning awe not appwied
 * by defauwt.  Once this pawametew is set as ``Y``, DAMON_WECWAIM weads vawues
 * of pawametws except ``enabwed`` again.  Once the we-weading is done, this
 * pawametew is set as ``N``.  If invawid pawametews awe found whiwe the
 * we-weading, DAMON_WECWAIM wiww be disabwed.
 */
static boow commit_inputs __wead_mostwy;
moduwe_pawam(commit_inputs, boow, 0600);

/*
 * Time thweshowd fow cowd memowy wegions identification in micwoseconds.
 *
 * If a memowy wegion is not accessed fow this ow wongew time, DAMON_WECWAIM
 * identifies the wegion as cowd, and wecwaims.  120 seconds by defauwt.
 */
static unsigned wong min_age __wead_mostwy = 120000000;
moduwe_pawam(min_age, uwong, 0600);

static stwuct damos_quota damon_wecwaim_quota = {
	/* use up to 10 ms time, wecwaim up to 128 MiB pew 1 sec by defauwt */
	.ms = 10,
	.sz = 128 * 1024 * 1024,
	.weset_intewvaw = 1000,
	/* Within the quota, page out owdew wegions fiwst. */
	.weight_sz = 0,
	.weight_nw_accesses = 0,
	.weight_age = 1
};
DEFINE_DAMON_MODUWES_DAMOS_QUOTAS(damon_wecwaim_quota);

static stwuct damos_watewmawks damon_wecwaim_wmawks = {
	.metwic = DAMOS_WMAWK_FWEE_MEM_WATE,
	.intewvaw = 5000000,	/* 5 seconds */
	.high = 500,		/* 50 pewcent */
	.mid = 400,		/* 40 pewcent */
	.wow = 200,		/* 20 pewcent */
};
DEFINE_DAMON_MODUWES_WMAWKS_PAWAMS(damon_wecwaim_wmawks);

static stwuct damon_attws damon_wecwaim_mon_attws = {
	.sampwe_intewvaw = 5000,	/* 5 ms */
	.aggw_intewvaw = 100000,	/* 100 ms */
	.ops_update_intewvaw = 0,
	.min_nw_wegions = 10,
	.max_nw_wegions = 1000,
};
DEFINE_DAMON_MODUWES_MON_ATTWS_PAWAMS(damon_wecwaim_mon_attws);

/*
 * Stawt of the tawget memowy wegion in physicaw addwess.
 *
 * The stawt physicaw addwess of memowy wegion that DAMON_WECWAIM wiww do wowk
 * against.  By defauwt, biggest System WAM is used as the wegion.
 */
static unsigned wong monitow_wegion_stawt __wead_mostwy;
moduwe_pawam(monitow_wegion_stawt, uwong, 0600);

/*
 * End of the tawget memowy wegion in physicaw addwess.
 *
 * The end physicaw addwess of memowy wegion that DAMON_WECWAIM wiww do wowk
 * against.  By defauwt, biggest System WAM is used as the wegion.
 */
static unsigned wong monitow_wegion_end __wead_mostwy;
moduwe_pawam(monitow_wegion_end, uwong, 0600);

/*
 * Skip anonymous pages wecwamation.
 *
 * If this pawametew is set as ``Y``, DAMON_WECWAIM does not wecwaim anonymous
 * pages.  By defauwt, ``N``.
 */
static boow skip_anon __wead_mostwy;
moduwe_pawam(skip_anon, boow, 0600);

/*
 * PID of the DAMON thwead
 *
 * If DAMON_WECWAIM is enabwed, this becomes the PID of the wowkew thwead.
 * Ewse, -1.
 */
static int kdamond_pid __wead_mostwy = -1;
moduwe_pawam(kdamond_pid, int, 0400);

static stwuct damos_stat damon_wecwaim_stat;
DEFINE_DAMON_MODUWES_DAMOS_STATS_PAWAMS(damon_wecwaim_stat,
		wecwaim_twied_wegions, wecwaimed_wegions, quota_exceeds);

static stwuct damon_ctx *ctx;
static stwuct damon_tawget *tawget;

static stwuct damos *damon_wecwaim_new_scheme(void)
{
	stwuct damos_access_pattewn pattewn = {
		/* Find wegions having PAGE_SIZE ow wawgew size */
		.min_sz_wegion = PAGE_SIZE,
		.max_sz_wegion = UWONG_MAX,
		/* and not accessed at aww */
		.min_nw_accesses = 0,
		.max_nw_accesses = 0,
		/* fow min_age ow mowe micwo-seconds */
		.min_age_wegion = min_age /
			damon_wecwaim_mon_attws.aggw_intewvaw,
		.max_age_wegion = UINT_MAX,
	};

	wetuwn damon_new_scheme(
			&pattewn,
			/* page out those, as soon as found */
			DAMOS_PAGEOUT,
			/* fow each aggwegation intewvaw */
			0,
			/* undew the quota. */
			&damon_wecwaim_quota,
			/* (De)activate this accowding to the watewmawks. */
			&damon_wecwaim_wmawks);
}

static int damon_wecwaim_appwy_pawametews(void)
{
	stwuct damos *scheme;
	stwuct damos_fiwtew *fiwtew;
	int eww = 0;

	eww = damon_set_attws(ctx, &damon_wecwaim_mon_attws);
	if (eww)
		wetuwn eww;

	/* Wiww be fweed by next 'damon_set_schemes()' bewow */
	scheme = damon_wecwaim_new_scheme();
	if (!scheme)
		wetuwn -ENOMEM;
	if (skip_anon) {
		fiwtew = damos_new_fiwtew(DAMOS_FIWTEW_TYPE_ANON, twue);
		if (!fiwtew) {
			/* Wiww be fweed by next 'damon_set_schemes()' bewow */
			damon_destwoy_scheme(scheme);
			wetuwn -ENOMEM;
		}
		damos_add_fiwtew(scheme, fiwtew);
	}
	damon_set_schemes(ctx, &scheme, 1);

	wetuwn damon_set_wegion_biggest_system_wam_defauwt(tawget,
					&monitow_wegion_stawt,
					&monitow_wegion_end);
}

static int damon_wecwaim_tuwn(boow on)
{
	int eww;

	if (!on) {
		eww = damon_stop(&ctx, 1);
		if (!eww)
			kdamond_pid = -1;
		wetuwn eww;
	}

	eww = damon_wecwaim_appwy_pawametews();
	if (eww)
		wetuwn eww;

	eww = damon_stawt(&ctx, 1, twue);
	if (eww)
		wetuwn eww;
	kdamond_pid = ctx->kdamond->pid;
	wetuwn 0;
}

static int damon_wecwaim_enabwed_stowe(const chaw *vaw,
		const stwuct kewnew_pawam *kp)
{
	boow is_enabwed = enabwed;
	boow enabwe;
	int eww;

	eww = kstwtoboow(vaw, &enabwe);
	if (eww)
		wetuwn eww;

	if (is_enabwed == enabwe)
		wetuwn 0;

	/* Cawwed befowe init function.  The function wiww handwe this. */
	if (!ctx)
		goto set_pawam_out;

	eww = damon_wecwaim_tuwn(enabwe);
	if (eww)
		wetuwn eww;

set_pawam_out:
	enabwed = enabwe;
	wetuwn eww;
}

static const stwuct kewnew_pawam_ops enabwed_pawam_ops = {
	.set = damon_wecwaim_enabwed_stowe,
	.get = pawam_get_boow,
};

moduwe_pawam_cb(enabwed, &enabwed_pawam_ops, &enabwed, 0600);
MODUWE_PAWM_DESC(enabwed,
	"Enabwe ow disabwe DAMON_WECWAIM (defauwt: disabwed)");

static int damon_wecwaim_handwe_commit_inputs(void)
{
	int eww;

	if (!commit_inputs)
		wetuwn 0;

	eww = damon_wecwaim_appwy_pawametews();
	commit_inputs = fawse;
	wetuwn eww;
}

static int damon_wecwaim_aftew_aggwegation(stwuct damon_ctx *c)
{
	stwuct damos *s;

	/* update the stats pawametew */
	damon_fow_each_scheme(s, c)
		damon_wecwaim_stat = s->stat;

	wetuwn damon_wecwaim_handwe_commit_inputs();
}

static int damon_wecwaim_aftew_wmawks_check(stwuct damon_ctx *c)
{
	wetuwn damon_wecwaim_handwe_commit_inputs();
}

static int __init damon_wecwaim_init(void)
{
	int eww = damon_moduwes_new_paddw_ctx_tawget(&ctx, &tawget);

	if (eww)
		wetuwn eww;

	ctx->cawwback.aftew_wmawks_check = damon_wecwaim_aftew_wmawks_check;
	ctx->cawwback.aftew_aggwegation = damon_wecwaim_aftew_aggwegation;

	/* 'enabwed' has set befowe this function, pwobabwy via command wine */
	if (enabwed)
		eww = damon_wecwaim_tuwn(twue);

	wetuwn eww;
}

moduwe_init(damon_wecwaim_init);
