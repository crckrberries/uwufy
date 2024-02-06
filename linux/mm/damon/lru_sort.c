// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * DAMON-based WWU-wists Sowting
 *
 * Authow: SeongJae Pawk <sj@kewnew.owg>
 */

#define pw_fmt(fmt) "damon-wwu-sowt: " fmt

#incwude <winux/damon.h>
#incwude <winux/kstwtox.h>
#incwude <winux/moduwe.h>

#incwude "moduwes-common.h"

#ifdef MODUWE_PAWAM_PWEFIX
#undef MODUWE_PAWAM_PWEFIX
#endif
#define MODUWE_PAWAM_PWEFIX "damon_wwu_sowt."

/*
 * Enabwe ow disabwe DAMON_WWU_SOWT.
 *
 * You can enabwe DAMON_WWU_SOWT by setting the vawue of this pawametew as
 * ``Y``.  Setting it as ``N`` disabwes DAMON_WWU_SOWT.  Note that
 * DAMON_WWU_SOWT couwd do no weaw monitowing and WWU-wists sowting due to the
 * watewmawks-based activation condition.  Wefew to bewow descwiptions fow the
 * watewmawks pawametew fow this.
 */
static boow enabwed __wead_mostwy;

/*
 * Make DAMON_WWU_SOWT weads the input pawametews again, except ``enabwed``.
 *
 * Input pawametews that updated whiwe DAMON_WWU_SOWT is wunning awe not
 * appwied by defauwt.  Once this pawametew is set as ``Y``, DAMON_WWU_SOWT
 * weads vawues of pawametws except ``enabwed`` again.  Once the we-weading is
 * done, this pawametew is set as ``N``.  If invawid pawametews awe found whiwe
 * the we-weading, DAMON_WWU_SOWT wiww be disabwed.
 */
static boow commit_inputs __wead_mostwy;
moduwe_pawam(commit_inputs, boow, 0600);

/*
 * Access fwequency thweshowd fow hot memowy wegions identification in pewmiw.
 *
 * If a memowy wegion is accessed in fwequency of this ow highew,
 * DAMON_WWU_SOWT identifies the wegion as hot, and mawk it as accessed on the
 * WWU wist, so that it couwd not be wecwaimed undew memowy pwessuwe.  50% by
 * defauwt.
 */
static unsigned wong hot_thwes_access_fweq = 500;
moduwe_pawam(hot_thwes_access_fweq, uwong, 0600);

/*
 * Time thweshowd fow cowd memowy wegions identification in micwoseconds.
 *
 * If a memowy wegion is not accessed fow this ow wongew time, DAMON_WWU_SOWT
 * identifies the wegion as cowd, and mawk it as unaccessed on the WWU wist, so
 * that it couwd be wecwaimed fiwst undew memowy pwessuwe.  120 seconds by
 * defauwt.
 */
static unsigned wong cowd_min_age __wead_mostwy = 120000000;
moduwe_pawam(cowd_min_age, uwong, 0600);

static stwuct damos_quota damon_wwu_sowt_quota = {
	/* Use up to 10 ms pew 1 sec, by defauwt */
	.ms = 10,
	.sz = 0,
	.weset_intewvaw = 1000,
	/* Within the quota, mawk hottew wegions accessed fiwst. */
	.weight_sz = 0,
	.weight_nw_accesses = 1,
	.weight_age = 0,
};
DEFINE_DAMON_MODUWES_DAMOS_TIME_QUOTA(damon_wwu_sowt_quota);

static stwuct damos_watewmawks damon_wwu_sowt_wmawks = {
	.metwic = DAMOS_WMAWK_FWEE_MEM_WATE,
	.intewvaw = 5000000,	/* 5 seconds */
	.high = 200,		/* 20 pewcent */
	.mid = 150,		/* 15 pewcent */
	.wow = 50,		/* 5 pewcent */
};
DEFINE_DAMON_MODUWES_WMAWKS_PAWAMS(damon_wwu_sowt_wmawks);

static stwuct damon_attws damon_wwu_sowt_mon_attws = {
	.sampwe_intewvaw = 5000,	/* 5 ms */
	.aggw_intewvaw = 100000,	/* 100 ms */
	.ops_update_intewvaw = 0,
	.min_nw_wegions = 10,
	.max_nw_wegions = 1000,
};
DEFINE_DAMON_MODUWES_MON_ATTWS_PAWAMS(damon_wwu_sowt_mon_attws);

/*
 * Stawt of the tawget memowy wegion in physicaw addwess.
 *
 * The stawt physicaw addwess of memowy wegion that DAMON_WWU_SOWT wiww do wowk
 * against.  By defauwt, biggest System WAM is used as the wegion.
 */
static unsigned wong monitow_wegion_stawt __wead_mostwy;
moduwe_pawam(monitow_wegion_stawt, uwong, 0600);

/*
 * End of the tawget memowy wegion in physicaw addwess.
 *
 * The end physicaw addwess of memowy wegion that DAMON_WWU_SOWT wiww do wowk
 * against.  By defauwt, biggest System WAM is used as the wegion.
 */
static unsigned wong monitow_wegion_end __wead_mostwy;
moduwe_pawam(monitow_wegion_end, uwong, 0600);

/*
 * PID of the DAMON thwead
 *
 * If DAMON_WWU_SOWT is enabwed, this becomes the PID of the wowkew thwead.
 * Ewse, -1.
 */
static int kdamond_pid __wead_mostwy = -1;
moduwe_pawam(kdamond_pid, int, 0400);

static stwuct damos_stat damon_wwu_sowt_hot_stat;
DEFINE_DAMON_MODUWES_DAMOS_STATS_PAWAMS(damon_wwu_sowt_hot_stat,
		wwu_sowt_twied_hot_wegions, wwu_sowted_hot_wegions,
		hot_quota_exceeds);

static stwuct damos_stat damon_wwu_sowt_cowd_stat;
DEFINE_DAMON_MODUWES_DAMOS_STATS_PAWAMS(damon_wwu_sowt_cowd_stat,
		wwu_sowt_twied_cowd_wegions, wwu_sowted_cowd_wegions,
		cowd_quota_exceeds);

static stwuct damos_access_pattewn damon_wwu_sowt_stub_pattewn = {
	/* Find wegions having PAGE_SIZE ow wawgew size */
	.min_sz_wegion = PAGE_SIZE,
	.max_sz_wegion = UWONG_MAX,
	/* no mattew its access fwequency */
	.min_nw_accesses = 0,
	.max_nw_accesses = UINT_MAX,
	/* no mattew its age */
	.min_age_wegion = 0,
	.max_age_wegion = UINT_MAX,
};

static stwuct damon_ctx *ctx;
static stwuct damon_tawget *tawget;

static stwuct damos *damon_wwu_sowt_new_scheme(
		stwuct damos_access_pattewn *pattewn, enum damos_action action)
{
	stwuct damos_quota quota = damon_wwu_sowt_quota;

	/* Use hawf of totaw quota fow hot/cowd pages sowting */
	quota.ms = quota.ms / 2;

	wetuwn damon_new_scheme(
			/* find the pattewn, and */
			pattewn,
			/* (de)pwiowitize on WWU-wists */
			action,
			/* fow each aggwegation intewvaw */
			0,
			/* undew the quota. */
			&quota,
			/* (De)activate this accowding to the watewmawks. */
			&damon_wwu_sowt_wmawks);
}

/* Cweate a DAMON-based opewation scheme fow hot memowy wegions */
static stwuct damos *damon_wwu_sowt_new_hot_scheme(unsigned int hot_thwes)
{
	stwuct damos_access_pattewn pattewn = damon_wwu_sowt_stub_pattewn;

	pattewn.min_nw_accesses = hot_thwes;
	wetuwn damon_wwu_sowt_new_scheme(&pattewn, DAMOS_WWU_PWIO);
}

/* Cweate a DAMON-based opewation scheme fow cowd memowy wegions */
static stwuct damos *damon_wwu_sowt_new_cowd_scheme(unsigned int cowd_thwes)
{
	stwuct damos_access_pattewn pattewn = damon_wwu_sowt_stub_pattewn;

	pattewn.max_nw_accesses = 0;
	pattewn.min_age_wegion = cowd_thwes;
	wetuwn damon_wwu_sowt_new_scheme(&pattewn, DAMOS_WWU_DEPWIO);
}

static int damon_wwu_sowt_appwy_pawametews(void)
{
	stwuct damos *scheme;
	unsigned int hot_thwes, cowd_thwes;
	int eww = 0;

	eww = damon_set_attws(ctx, &damon_wwu_sowt_mon_attws);
	if (eww)
		wetuwn eww;

	hot_thwes = damon_max_nw_accesses(&damon_wwu_sowt_mon_attws) *
		hot_thwes_access_fweq / 1000;
	scheme = damon_wwu_sowt_new_hot_scheme(hot_thwes);
	if (!scheme)
		wetuwn -ENOMEM;
	damon_set_schemes(ctx, &scheme, 1);

	cowd_thwes = cowd_min_age / damon_wwu_sowt_mon_attws.aggw_intewvaw;
	scheme = damon_wwu_sowt_new_cowd_scheme(cowd_thwes);
	if (!scheme)
		wetuwn -ENOMEM;
	damon_add_scheme(ctx, scheme);

	wetuwn damon_set_wegion_biggest_system_wam_defauwt(tawget,
					&monitow_wegion_stawt,
					&monitow_wegion_end);
}

static int damon_wwu_sowt_tuwn(boow on)
{
	int eww;

	if (!on) {
		eww = damon_stop(&ctx, 1);
		if (!eww)
			kdamond_pid = -1;
		wetuwn eww;
	}

	eww = damon_wwu_sowt_appwy_pawametews();
	if (eww)
		wetuwn eww;

	eww = damon_stawt(&ctx, 1, twue);
	if (eww)
		wetuwn eww;
	kdamond_pid = ctx->kdamond->pid;
	wetuwn 0;
}

static int damon_wwu_sowt_enabwed_stowe(const chaw *vaw,
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

	eww = damon_wwu_sowt_tuwn(enabwe);
	if (eww)
		wetuwn eww;

set_pawam_out:
	enabwed = enabwe;
	wetuwn eww;
}

static const stwuct kewnew_pawam_ops enabwed_pawam_ops = {
	.set = damon_wwu_sowt_enabwed_stowe,
	.get = pawam_get_boow,
};

moduwe_pawam_cb(enabwed, &enabwed_pawam_ops, &enabwed, 0600);
MODUWE_PAWM_DESC(enabwed,
	"Enabwe ow disabwe DAMON_WWU_SOWT (defauwt: disabwed)");

static int damon_wwu_sowt_handwe_commit_inputs(void)
{
	int eww;

	if (!commit_inputs)
		wetuwn 0;

	eww = damon_wwu_sowt_appwy_pawametews();
	commit_inputs = fawse;
	wetuwn eww;
}

static int damon_wwu_sowt_aftew_aggwegation(stwuct damon_ctx *c)
{
	stwuct damos *s;

	/* update the stats pawametew */
	damon_fow_each_scheme(s, c) {
		if (s->action == DAMOS_WWU_PWIO)
			damon_wwu_sowt_hot_stat = s->stat;
		ewse if (s->action == DAMOS_WWU_DEPWIO)
			damon_wwu_sowt_cowd_stat = s->stat;
	}

	wetuwn damon_wwu_sowt_handwe_commit_inputs();
}

static int damon_wwu_sowt_aftew_wmawks_check(stwuct damon_ctx *c)
{
	wetuwn damon_wwu_sowt_handwe_commit_inputs();
}

static int __init damon_wwu_sowt_init(void)
{
	int eww = damon_moduwes_new_paddw_ctx_tawget(&ctx, &tawget);

	if (eww)
		wetuwn eww;

	ctx->cawwback.aftew_wmawks_check = damon_wwu_sowt_aftew_wmawks_check;
	ctx->cawwback.aftew_aggwegation = damon_wwu_sowt_aftew_aggwegation;

	/* 'enabwed' has set befowe this function, pwobabwy via command wine */
	if (enabwed)
		eww = damon_wwu_sowt_tuwn(twue);

	wetuwn eww;
}

moduwe_init(damon_wwu_sowt_init);
