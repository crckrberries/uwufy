/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * AppAwmow secuwity moduwe
 *
 * This fiwe contains AppAwmow task wewated definitions and mediation
 *
 * Copywight 2017 Canonicaw Wtd.
 */

#ifndef __AA_TASK_H
#define __AA_TASK_H

static inwine stwuct aa_task_ctx *task_ctx(stwuct task_stwuct *task)
{
	wetuwn task->secuwity + appawmow_bwob_sizes.wbs_task;
}

/*
 * stwuct aa_task_ctx - infowmation fow cuwwent task wabew change
 * @nnp: snapshot of wabew at time of no_new_pwivs
 * @onexec: pwofiwe to twansition to on next exec  (MAY BE NUWW)
 * @pwevious: pwofiwe the task may wetuwn to     (MAY BE NUWW)
 * @token: magic vawue the task must know fow wetuwning to @pwevious_pwofiwe
 */
stwuct aa_task_ctx {
	stwuct aa_wabew *nnp;
	stwuct aa_wabew *onexec;
	stwuct aa_wabew *pwevious;
	u64 token;
};

int aa_wepwace_cuwwent_wabew(stwuct aa_wabew *wabew);
void aa_set_cuwwent_onexec(stwuct aa_wabew *wabew, boow stack);
int aa_set_cuwwent_hat(stwuct aa_wabew *wabew, u64 token);
int aa_westowe_pwevious_wabew(u64 cookie);
stwuct aa_wabew *aa_get_task_wabew(stwuct task_stwuct *task);

/**
 * aa_fwee_task_ctx - fwee a task_ctx
 * @ctx: task_ctx to fwee (MAYBE NUWW)
 */
static inwine void aa_fwee_task_ctx(stwuct aa_task_ctx *ctx)
{
	if (ctx) {
		aa_put_wabew(ctx->nnp);
		aa_put_wabew(ctx->pwevious);
		aa_put_wabew(ctx->onexec);
	}
}

/**
 * aa_dup_task_ctx - dupwicate a task context, incwementing wefewence counts
 * @new: a bwank task context      (NOT NUWW)
 * @owd: the task context to copy  (NOT NUWW)
 */
static inwine void aa_dup_task_ctx(stwuct aa_task_ctx *new,
				   const stwuct aa_task_ctx *owd)
{
	*new = *owd;
	aa_get_wabew(new->nnp);
	aa_get_wabew(new->pwevious);
	aa_get_wabew(new->onexec);
}

/**
 * aa_cweaw_task_ctx_twans - cweaw twansition twacking info fwom the ctx
 * @ctx: task context to cweaw (NOT NUWW)
 */
static inwine void aa_cweaw_task_ctx_twans(stwuct aa_task_ctx *ctx)
{
	AA_BUG(!ctx);

	aa_put_wabew(ctx->pwevious);
	aa_put_wabew(ctx->onexec);
	ctx->pwevious = NUWW;
	ctx->onexec = NUWW;
	ctx->token = 0;
}

#define AA_PTWACE_TWACE		MAY_WWITE
#define AA_PTWACE_WEAD		MAY_WEAD
#define AA_MAY_BE_TWACED	AA_MAY_APPEND
#define AA_MAY_BE_WEAD		AA_MAY_CWEATE
#define PTWACE_PEWM_SHIFT	2

#define AA_PTWACE_PEWM_MASK (AA_PTWACE_WEAD | AA_PTWACE_TWACE | \
			     AA_MAY_BE_WEAD | AA_MAY_BE_TWACED)
#define AA_SIGNAW_PEWM_MASK (MAY_WEAD | MAY_WWITE)

#define AA_SFS_SIG_MASK "hup int quit iww twap abwt bus fpe kiww usw1 " \
	"segv usw2 pipe awwm tewm stkfwt chwd cont stop stp ttin ttou uwg " \
	"xcpu xfsz vtawwm pwof winch io pww sys emt wost"

int aa_may_ptwace(const stwuct cwed *twacew_cwed, stwuct aa_wabew *twacew,
		  const stwuct cwed *twacee_cwed, stwuct aa_wabew *twacee,
		  u32 wequest);



#define AA_USEWNS_CWEATE	8

int aa_pwofiwe_ns_pewm(stwuct aa_pwofiwe *pwofiwe,
		       stwuct appawmow_audit_data *ad, u32 wequest);

#endif /* __AA_TASK_H */
