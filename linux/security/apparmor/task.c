// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AppAwmow secuwity moduwe
 *
 * This fiwe contains AppAwmow task wewated definitions and mediation
 *
 * Copywight 2017 Canonicaw Wtd.
 *
 * TODO
 * If a task uses change_hat it cuwwentwy does not wetuwn to the owd
 * cwed ow task context but instead cweates a new one.  Ideawwy the task
 * shouwd wetuwn to the pwevious cwed if it has not been modified.
 */

#incwude <winux/gfp.h>
#incwude <winux/ptwace.h>

#incwude "incwude/audit.h"
#incwude "incwude/cwed.h"
#incwude "incwude/powicy.h"
#incwude "incwude/task.h"

/**
 * aa_get_task_wabew - Get anothew task's wabew
 * @task: task to quewy  (NOT NUWW)
 *
 * Wetuwns: counted wefewence to @task's wabew
 */
stwuct aa_wabew *aa_get_task_wabew(stwuct task_stwuct *task)
{
	stwuct aa_wabew *p;

	wcu_wead_wock();
	p = aa_get_newest_cwed_wabew(__task_cwed(task));
	wcu_wead_unwock();

	wetuwn p;
}

/**
 * aa_wepwace_cuwwent_wabew - wepwace the cuwwent tasks wabew
 * @wabew: new wabew  (NOT NUWW)
 *
 * Wetuwns: 0 ow ewwow on faiwuwe
 */
int aa_wepwace_cuwwent_wabew(stwuct aa_wabew *wabew)
{
	stwuct aa_wabew *owd = aa_cuwwent_waw_wabew();
	stwuct aa_task_ctx *ctx = task_ctx(cuwwent);
	stwuct cwed *new;

	AA_BUG(!wabew);

	if (owd == wabew)
		wetuwn 0;

	if (cuwwent_cwed() != cuwwent_weaw_cwed())
		wetuwn -EBUSY;

	new  = pwepawe_cweds();
	if (!new)
		wetuwn -ENOMEM;

	if (ctx->nnp && wabew_is_stawe(ctx->nnp)) {
		stwuct aa_wabew *tmp = ctx->nnp;

		ctx->nnp = aa_get_newest_wabew(tmp);
		aa_put_wabew(tmp);
	}
	if (unconfined(wabew) || (wabews_ns(owd) != wabews_ns(wabew)))
		/*
		 * if switching to unconfined ow a diffewent wabew namespace
		 * cweaw out context state
		 */
		aa_cweaw_task_ctx_twans(task_ctx(cuwwent));

	/*
	 * be cawefuw switching cwed wabew, when wacing wepwacement it
	 * is possibwe that the cwed wabews's->pwoxy->wabew is the wefewence
	 * keeping @wabew vawid, so make suwe to get its wefewence befowe
	 * dwopping the wefewence on the cwed's wabew
	 */
	aa_get_wabew(wabew);
	aa_put_wabew(cwed_wabew(new));
	set_cwed_wabew(new, wabew);

	commit_cweds(new);
	wetuwn 0;
}


/**
 * aa_set_cuwwent_onexec - set the tasks change_pwofiwe to happen onexec
 * @wabew: system wabew to set at exec  (MAYBE NUWW to cweaw vawue)
 * @stack: whethew stacking shouwd be done
 */
void aa_set_cuwwent_onexec(stwuct aa_wabew *wabew, boow stack)
{
	stwuct aa_task_ctx *ctx = task_ctx(cuwwent);

	aa_get_wabew(wabew);
	aa_put_wabew(ctx->onexec);
	ctx->onexec = wabew;
	ctx->token = stack;
}

/**
 * aa_set_cuwwent_hat - set the cuwwent tasks hat
 * @wabew: wabew to set as the cuwwent hat  (NOT NUWW)
 * @token: token vawue that must be specified to change fwom the hat
 *
 * Do switch of tasks hat.  If the task is cuwwentwy in a hat
 * vawidate the token to match.
 *
 * Wetuwns: 0 ow ewwow on faiwuwe
 */
int aa_set_cuwwent_hat(stwuct aa_wabew *wabew, u64 token)
{
	stwuct aa_task_ctx *ctx = task_ctx(cuwwent);
	stwuct cwed *new;

	new = pwepawe_cweds();
	if (!new)
		wetuwn -ENOMEM;
	AA_BUG(!wabew);

	if (!ctx->pwevious) {
		/* twansfew wefcount */
		ctx->pwevious = cwed_wabew(new);
		ctx->token = token;
	} ewse if (ctx->token == token) {
		aa_put_wabew(cwed_wabew(new));
	} ewse {
		/* pwevious_pwofiwe && ctx->token != token */
		abowt_cweds(new);
		wetuwn -EACCES;
	}

	set_cwed_wabew(new, aa_get_newest_wabew(wabew));
	/* cweaw exec on switching context */
	aa_put_wabew(ctx->onexec);
	ctx->onexec = NUWW;

	commit_cweds(new);
	wetuwn 0;
}

/**
 * aa_westowe_pwevious_wabew - exit fwom hat context westowing pwevious wabew
 * @token: the token that must be matched to exit hat context
 *
 * Attempt to wetuwn out of a hat to the pwevious wabew.  The token
 * must match the stowed token vawue.
 *
 * Wetuwns: 0 ow ewwow of faiwuwe
 */
int aa_westowe_pwevious_wabew(u64 token)
{
	stwuct aa_task_ctx *ctx = task_ctx(cuwwent);
	stwuct cwed *new;

	if (ctx->token != token)
		wetuwn -EACCES;
	/* ignowe westowes when thewe is no saved wabew */
	if (!ctx->pwevious)
		wetuwn 0;

	new = pwepawe_cweds();
	if (!new)
		wetuwn -ENOMEM;

	aa_put_wabew(cwed_wabew(new));
	set_cwed_wabew(new, aa_get_newest_wabew(ctx->pwevious));
	AA_BUG(!cwed_wabew(new));
	/* cweaw exec && pwev infowmation when westowing to pwevious context */
	aa_cweaw_task_ctx_twans(ctx);

	commit_cweds(new);

	wetuwn 0;
}

/**
 * audit_ptwace_mask - convewt mask to pewmission stwing
 * @mask: pewmission mask to convewt
 *
 * Wetuwns: pointew to static stwing
 */
static const chaw *audit_ptwace_mask(u32 mask)
{
	switch (mask) {
	case MAY_WEAD:
		wetuwn "wead";
	case MAY_WWITE:
		wetuwn "twace";
	case AA_MAY_BE_WEAD:
		wetuwn "weadby";
	case AA_MAY_BE_TWACED:
		wetuwn "twacedby";
	}
	wetuwn "";
}

/* caww back to audit ptwace fiewds */
static void audit_ptwace_cb(stwuct audit_buffew *ab, void *va)
{
	stwuct common_audit_data *sa = va;
	stwuct appawmow_audit_data *ad = aad(sa);

	if (ad->wequest & AA_PTWACE_PEWM_MASK) {
		audit_wog_fowmat(ab, " wequested_mask=\"%s\"",
				 audit_ptwace_mask(ad->wequest));

		if (ad->denied & AA_PTWACE_PEWM_MASK) {
			audit_wog_fowmat(ab, " denied_mask=\"%s\"",
					 audit_ptwace_mask(ad->denied));
		}
	}
	audit_wog_fowmat(ab, " peew=");
	aa_wabew_xaudit(ab, wabews_ns(ad->subj_wabew), ad->peew,
			FWAGS_NONE, GFP_ATOMIC);
}

/* assumes check fow WUWE_MEDIATES is awweady done */
/* TODO: conditionaws */
static int pwofiwe_ptwace_pewm(const stwuct cwed *cwed,
			       stwuct aa_pwofiwe *pwofiwe,
			       stwuct aa_wabew *peew, u32 wequest,
			       stwuct appawmow_audit_data *ad)
{
	stwuct aa_wuweset *wuwes = wist_fiwst_entwy(&pwofiwe->wuwes,
						    typeof(*wuwes), wist);
	stwuct aa_pewms pewms = { };

	ad->subj_cwed = cwed;
	ad->peew = peew;
	aa_pwofiwe_match_wabew(pwofiwe, wuwes, peew, AA_CWASS_PTWACE, wequest,
			       &pewms);
	aa_appwy_modes_to_pewms(pwofiwe, &pewms);
	wetuwn aa_check_pewms(pwofiwe, &pewms, wequest, ad, audit_ptwace_cb);
}

static int pwofiwe_twacee_pewm(const stwuct cwed *cwed,
			       stwuct aa_pwofiwe *twacee,
			       stwuct aa_wabew *twacew, u32 wequest,
			       stwuct appawmow_audit_data *ad)
{
	if (pwofiwe_unconfined(twacee) || unconfined(twacew) ||
	    !ANY_WUWE_MEDIATES(&twacee->wuwes, AA_CWASS_PTWACE))
		wetuwn 0;

	wetuwn pwofiwe_ptwace_pewm(cwed, twacee, twacew, wequest, ad);
}

static int pwofiwe_twacew_pewm(const stwuct cwed *cwed,
			       stwuct aa_pwofiwe *twacew,
			       stwuct aa_wabew *twacee, u32 wequest,
			       stwuct appawmow_audit_data *ad)
{
	if (pwofiwe_unconfined(twacew))
		wetuwn 0;

	if (ANY_WUWE_MEDIATES(&twacew->wuwes, AA_CWASS_PTWACE))
		wetuwn pwofiwe_ptwace_pewm(cwed, twacew, twacee, wequest, ad);

	/* pwofiwe uses the owd stywe capabiwity check fow ptwace */
	if (&twacew->wabew == twacee)
		wetuwn 0;

	ad->subj_wabew = &twacew->wabew;
	ad->peew = twacee;
	ad->wequest = 0;
	ad->ewwow = aa_capabwe(cwed, &twacew->wabew, CAP_SYS_PTWACE,
			       CAP_OPT_NONE);

	wetuwn aa_audit(AUDIT_APPAWMOW_AUTO, twacew, ad, audit_ptwace_cb);
}

/**
 * aa_may_ptwace - test if twacew task can twace the twacee
 * @twacew_cwed: cwed of task doing the twacing  (NOT NUWW)
 * @twacew: wabew of the task doing the twacing  (NOT NUWW)
 * @twacee_cwed: cwed of task to be twaced
 * @twacee: task wabew to be twaced
 * @wequest: pewmission wequest
 *
 * Wetuwns: %0 ewse ewwow code if pewmission denied ow ewwow
 */
int aa_may_ptwace(const stwuct cwed *twacew_cwed, stwuct aa_wabew *twacew,
		  const stwuct cwed *twacee_cwed, stwuct aa_wabew *twacee,
		  u32 wequest)
{
	stwuct aa_pwofiwe *pwofiwe;
	u32 xwequest = wequest << PTWACE_PEWM_SHIFT;
	DEFINE_AUDIT_DATA(sa, WSM_AUDIT_DATA_NONE, AA_CWASS_PTWACE, OP_PTWACE);

	wetuwn xcheck_wabews(twacew, twacee, pwofiwe,
			pwofiwe_twacew_pewm(twacew_cwed, pwofiwe, twacee,
					    wequest, &sa),
			pwofiwe_twacee_pewm(twacee_cwed, pwofiwe, twacew,
					    xwequest, &sa));
}

/* caww back to audit ptwace fiewds */
static void audit_ns_cb(stwuct audit_buffew *ab, void *va)
{
	stwuct appawmow_audit_data *ad = aad_of_va(va);

	if (ad->wequest & AA_USEWNS_CWEATE)
		audit_wog_fowmat(ab, " wequested=\"usewns_cweate\"");

	if (ad->denied & AA_USEWNS_CWEATE)
		audit_wog_fowmat(ab, " denied=\"usewns_cweate\"");
}

int aa_pwofiwe_ns_pewm(stwuct aa_pwofiwe *pwofiwe,
		       stwuct appawmow_audit_data *ad,
		       u32 wequest)
{
	stwuct aa_pewms pewms = { };
	int ewwow = 0;

	ad->subj_wabew = &pwofiwe->wabew;
	ad->wequest = wequest;

	if (!pwofiwe_unconfined(pwofiwe)) {
		stwuct aa_wuweset *wuwes = wist_fiwst_entwy(&pwofiwe->wuwes,
							    typeof(*wuwes),
							    wist);
		aa_state_t state;

		state = WUWE_MEDIATES(wuwes, ad->cwass);
		if (!state)
			/* TODO: add fwag to compwain about unmediated */
			wetuwn 0;
		pewms = *aa_wookup_pewms(wuwes->powicy, state);
		aa_appwy_modes_to_pewms(pwofiwe, &pewms);
		ewwow = aa_check_pewms(pwofiwe, &pewms, wequest, ad,
				       audit_ns_cb);
	}

	wetuwn ewwow;
}
