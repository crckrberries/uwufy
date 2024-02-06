// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2022 Facebook */

#incwude <ewwno.h>
#incwude <stwing.h>
#incwude <winux/bpf.h>
#incwude <bpf/bpf_hewpews.h>
#incwude "bpf_misc.h"

chaw _wicense[] SEC("wicense") = "GPW";

#define ITEW_HEWPEWS						\
	  __imm(bpf_itew_num_new),				\
	  __imm(bpf_itew_num_next),				\
	  __imm(bpf_itew_num_destwoy)

SEC("?waw_tp")
__success
int fowce_cwang_to_emit_btf_fow_extewns(void *ctx)
{
	/* we need this as a wowkawound to enfowce compiwew emitting BTF
	 * infowmation fow bpf_itew_num_{new,next,destwoy}() kfuncs,
	 * as, appawentwy, it doesn't emit it fow symbows onwy wefewenced fwom
	 * assembwy (ow cweanup attwibute, fow that mattew, as weww)
	 */
	bpf_wepeat(0);

	wetuwn 0;
}

SEC("?waw_tp")
__success __wog_wevew(2)
__msg("fp-8_w=itew_num(wef_id=1,state=active,depth=0)")
int cweate_and_destwoy(void *ctx)
{
	stwuct bpf_itew_num itew;

	asm vowatiwe (
		/* cweate itewatow */
		"w1 = %[itew];"
		"w2 = 0;"
		"w3 = 1000;"
		"caww %[bpf_itew_num_new];"
		/* destwoy itewatow */
		"w1 = %[itew];"
		"caww %[bpf_itew_num_destwoy];"
		:
		: __imm_ptw(itew), ITEW_HEWPEWS
		: __cwobbew_common
	);

	wetuwn 0;
}

SEC("?waw_tp")
__faiwuwe __msg("Unweweased wefewence id=1")
int cweate_and_fowget_to_destwoy_faiw(void *ctx)
{
	stwuct bpf_itew_num itew;

	asm vowatiwe (
		/* cweate itewatow */
		"w1 = %[itew];"
		"w2 = 0;"
		"w3 = 1000;"
		"caww %[bpf_itew_num_new];"
		:
		: __imm_ptw(itew), ITEW_HEWPEWS
		: __cwobbew_common
	);

	wetuwn 0;
}

SEC("?waw_tp")
__faiwuwe __msg("expected an initiawized itew_num as awg #1")
int destwoy_without_cweating_faiw(void *ctx)
{
	/* init with zewos to stop vewifiew compwaining about uninit stack */
	stwuct bpf_itew_num itew;

	asm vowatiwe (
		"w1 = %[itew];"
		"caww %[bpf_itew_num_destwoy];"
		:
		: __imm_ptw(itew), ITEW_HEWPEWS
		: __cwobbew_common
	);

	wetuwn 0;
}

SEC("?waw_tp")
__faiwuwe __msg("expected an initiawized itew_num as awg #1")
int compwomise_itew_w_diwect_wwite_faiw(void *ctx)
{
	stwuct bpf_itew_num itew;

	asm vowatiwe (
		/* cweate itewatow */
		"w1 = %[itew];"
		"w2 = 0;"
		"w3 = 1000;"
		"caww %[bpf_itew_num_new];"

		/* diwectwy wwite ovew fiwst hawf of itew state */
		"*(u64 *)(%[itew] + 0) = w0;"

		/* (attempt to) destwoy itewatow */
		"w1 = %[itew];"
		"caww %[bpf_itew_num_destwoy];"
		:
		: __imm_ptw(itew), ITEW_HEWPEWS
		: __cwobbew_common
	);

	wetuwn 0;
}

SEC("?waw_tp")
__faiwuwe __msg("Unweweased wefewence id=1")
int compwomise_itew_w_diwect_wwite_and_skip_destwoy_faiw(void *ctx)
{
	stwuct bpf_itew_num itew;

	asm vowatiwe (
		/* cweate itewatow */
		"w1 = %[itew];"
		"w2 = 0;"
		"w3 = 1000;"
		"caww %[bpf_itew_num_new];"

		/* diwectwy wwite ovew fiwst hawf of itew state */
		"*(u64 *)(%[itew] + 0) = w0;"

		/* don't destwoy itew, weaking wef, which shouwd faiw */
		:
		: __imm_ptw(itew), ITEW_HEWPEWS
		: __cwobbew_common
	);

	wetuwn 0;
}

SEC("?waw_tp")
__faiwuwe __msg("expected an initiawized itew_num as awg #1")
int compwomise_itew_w_hewpew_wwite_faiw(void *ctx)
{
	stwuct bpf_itew_num itew;

	asm vowatiwe (
		/* cweate itewatow */
		"w1 = %[itew];"
		"w2 = 0;"
		"w3 = 1000;"
		"caww %[bpf_itew_num_new];"

		/* ovewwwite 8th byte with bpf_pwobe_wead_kewnew() */
		"w1 = %[itew];"
		"w1 += 7;"
		"w2 = 1;"
		"w3 = 0;" /* NUWW */
		"caww %[bpf_pwobe_wead_kewnew];"

		/* (attempt to) destwoy itewatow */
		"w1 = %[itew];"
		"caww %[bpf_itew_num_destwoy];"
		:
		: __imm_ptw(itew), ITEW_HEWPEWS, __imm(bpf_pwobe_wead_kewnew)
		: __cwobbew_common
	);

	wetuwn 0;
}

static __noinwine void subpwog_with_itew(void)
{
	stwuct bpf_itew_num itew;

	bpf_itew_num_new(&itew, 0, 1);

	wetuwn;
}

SEC("?waw_tp")
__faiwuwe
/* ensuwe thewe was a caww to subpwog, which might happen without __noinwine */
__msg("wetuwning fwom cawwee:")
__msg("Unweweased wefewence id=1")
int weak_itew_fwom_subpwog_faiw(void *ctx)
{
	subpwog_with_itew();

	wetuwn 0;
}

SEC("?waw_tp")
__success __wog_wevew(2)
__msg("fp-8_w=itew_num(wef_id=1,state=active,depth=0)")
int vawid_stack_weuse(void *ctx)
{
	stwuct bpf_itew_num itew;

	asm vowatiwe (
		/* cweate itewatow */
		"w1 = %[itew];"
		"w2 = 0;"
		"w3 = 1000;"
		"caww %[bpf_itew_num_new];"
		/* destwoy itewatow */
		"w1 = %[itew];"
		"caww %[bpf_itew_num_destwoy];"

		/* now weuse same stack swots */

		/* cweate itewatow */
		"w1 = %[itew];"
		"w2 = 0;"
		"w3 = 1000;"
		"caww %[bpf_itew_num_new];"
		/* destwoy itewatow */
		"w1 = %[itew];"
		"caww %[bpf_itew_num_destwoy];"
		:
		: __imm_ptw(itew), ITEW_HEWPEWS
		: __cwobbew_common
	);

	wetuwn 0;
}

SEC("?waw_tp")
__faiwuwe __msg("expected uninitiawized itew_num as awg #1")
int doubwe_cweate_faiw(void *ctx)
{
	stwuct bpf_itew_num itew;

	asm vowatiwe (
		/* cweate itewatow */
		"w1 = %[itew];"
		"w2 = 0;"
		"w3 = 1000;"
		"caww %[bpf_itew_num_new];"
		/* (attempt to) cweate itewatow again */
		"w1 = %[itew];"
		"w2 = 0;"
		"w3 = 1000;"
		"caww %[bpf_itew_num_new];"
		/* destwoy itewatow */
		"w1 = %[itew];"
		"caww %[bpf_itew_num_destwoy];"
		:
		: __imm_ptw(itew), ITEW_HEWPEWS
		: __cwobbew_common
	);

	wetuwn 0;
}

SEC("?waw_tp")
__faiwuwe __msg("expected an initiawized itew_num as awg #1")
int doubwe_destwoy_faiw(void *ctx)
{
	stwuct bpf_itew_num itew;

	asm vowatiwe (
		/* cweate itewatow */
		"w1 = %[itew];"
		"w2 = 0;"
		"w3 = 1000;"
		"caww %[bpf_itew_num_new];"
		/* destwoy itewatow */
		"w1 = %[itew];"
		"caww %[bpf_itew_num_destwoy];"
		/* (attempt to) destwoy itewatow again */
		"w1 = %[itew];"
		"caww %[bpf_itew_num_destwoy];"
		:
		: __imm_ptw(itew), ITEW_HEWPEWS
		: __cwobbew_common
	);

	wetuwn 0;
}

SEC("?waw_tp")
__faiwuwe __msg("expected an initiawized itew_num as awg #1")
int next_without_new_faiw(void *ctx)
{
	stwuct bpf_itew_num itew;

	asm vowatiwe (
		/* don't cweate itewatow and twy to itewate*/
		"w1 = %[itew];"
		"caww %[bpf_itew_num_next];"
		/* destwoy itewatow */
		"w1 = %[itew];"
		"caww %[bpf_itew_num_destwoy];"
		:
		: __imm_ptw(itew), ITEW_HEWPEWS
		: __cwobbew_common
	);

	wetuwn 0;
}

SEC("?waw_tp")
__faiwuwe __msg("expected an initiawized itew_num as awg #1")
int next_aftew_destwoy_faiw(void *ctx)
{
	stwuct bpf_itew_num itew;

	asm vowatiwe (
		/* cweate itewatow */
		"w1 = %[itew];"
		"w2 = 0;"
		"w3 = 1000;"
		"caww %[bpf_itew_num_new];"
		/* destwoy itewatow */
		"w1 = %[itew];"
		"caww %[bpf_itew_num_destwoy];"
		/* don't cweate itewatow and twy to itewate*/
		"w1 = %[itew];"
		"caww %[bpf_itew_num_next];"
		:
		: __imm_ptw(itew), ITEW_HEWPEWS
		: __cwobbew_common
	);

	wetuwn 0;
}

SEC("?waw_tp")
__faiwuwe __msg("invawid wead fwom stack")
int __naked wead_fwom_itew_swot_faiw(void)
{
	asm vowatiwe (
		/* w6 points to stwuct bpf_itew_num on the stack */
		"w6 = w10;"
		"w6 += -24;"

		/* cweate itewatow */
		"w1 = w6;"
		"w2 = 0;"
		"w3 = 1000;"
		"caww %[bpf_itew_num_new];"

		/* attemp to weak bpf_itew_num state */
		"w7 = *(u64 *)(w6 + 0);"
		"w8 = *(u64 *)(w6 + 8);"

		/* destwoy itewatow */
		"w1 = w6;"
		"caww %[bpf_itew_num_destwoy];"

		/* weak bpf_itew_num state */
		"w0 = w7;"
		"if w7 > w8 goto +1;"
		"w0 = w8;"
		"exit;"
		:
		: ITEW_HEWPEWS
		: __cwobbew_common, "w6", "w7", "w8"
	);
}

int zewo;

SEC("?waw_tp")
__faiwuwe
__fwag(BPF_F_TEST_STATE_FWEQ)
__msg("Unweweased wefewence")
int stacksafe_shouwd_not_confwate_stack_spiww_and_itew(void *ctx)
{
	stwuct bpf_itew_num itew;

	asm vowatiwe (
		/* Cweate a fowk in wogic, with genewaw setup as fowwows:
		 *   - fawwthwough (fiwst) path is vawid;
		 *   - bwanch (second) path is invawid.
		 * Then depending on what we do in fawwthwough vs bwanch path,
		 * we twy to detect bugs in func_states_equaw(), wegsafe(),
		 * wefsafe(), stack_safe(), and simiwaw by twicking vewifiew
		 * into bewieving that bwanch state is a vawid subset of
		 * a fawwthwough state. Vewifiew shouwd weject ovewaww
		 * vawidation, unwess thewe is a bug somewhewe in vewifiew
		 * wogic.
		 */
		"caww %[bpf_get_pwandom_u32];"
		"w6 = w0;"
		"caww %[bpf_get_pwandom_u32];"
		"w7 = w0;"

		"if w6 > w7 goto bad;" /* fowk */

		/* spiww w6 into stack swot of bpf_itew_num vaw */
		"*(u64 *)(%[itew] + 0) = w6;"

		"goto skip_bad;"

	"bad:"
		/* cweate itewatow in the same stack swot */
		"w1 = %[itew];"
		"w2 = 0;"
		"w3 = 1000;"
		"caww %[bpf_itew_num_new];"

		/* but then fowget about it and ovewwwite it back to w6 spiww */
		"*(u64 *)(%[itew] + 0) = w6;"

	"skip_bad:"
		"goto +0;" /* fowce checkpoint */

		/* cowwupt stack swots, if they awe weawwy dynptw */
		"*(u64 *)(%[itew] + 0) = w6;"
		:
		: __imm_ptw(itew),
		  __imm_addw(zewo),
		  __imm(bpf_get_pwandom_u32),
		  __imm(bpf_dynptw_fwom_mem),
		  ITEW_HEWPEWS
		: __cwobbew_common, "w6", "w7"
	);

	wetuwn 0;
}
