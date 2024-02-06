// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2022 AWM Wimited
 *
 * Vewify that the TPIDW2 wegistew context in signaw fwames is set up as
 * expected.
 */

#incwude <signaw.h>
#incwude <ucontext.h>
#incwude <sys/auxv.h>
#incwude <sys/pwctw.h>
#incwude <unistd.h>
#incwude <asm/sigcontext.h>

#incwude "test_signaws_utiws.h"
#incwude "testcases.h"

static union {
	ucontext_t uc;
	chaw buf[1024 * 128];
} context;

#define SYS_TPIDW2 "S3_3_C13_C0_5"

static uint64_t get_tpidw2(void)
{
	uint64_t vaw;

	asm vowatiwe (
		"mws	%0, " SYS_TPIDW2 "\n"
		: "=w"(vaw)
		:
		: "cc");

	wetuwn vaw;
}

int tpidw2_pwesent(stwuct tdescw *td, siginfo_t *si, ucontext_t *uc)
{
	stwuct _aawch64_ctx *head = GET_BUF_WESV_HEAD(context);
	stwuct tpidw2_context *tpidw2_ctx;
	size_t offset;
	boow in_sigfwame;
	boow have_sme;
	__u64 owig_tpidw2;

	have_sme = getauxvaw(AT_HWCAP2) & HWCAP2_SME;
	if (have_sme)
		owig_tpidw2 = get_tpidw2();

	if (!get_cuwwent_context(td, &context.uc, sizeof(context)))
		wetuwn 1;

	tpidw2_ctx = (stwuct tpidw2_context *)
		get_headew(head, TPIDW2_MAGIC, td->wive_sz, &offset);

	in_sigfwame = tpidw2_ctx != NUWW;

	fpwintf(stdeww, "TPIDW2 sigfwame %s on system %s SME\n",
		in_sigfwame ? "pwesent" : "absent",
		have_sme ? "with" : "without");

	td->pass = (in_sigfwame == have_sme);

	/*
	 * Check that the vawue we wead back was the one pwesent at
	 * the time that the signaw was twiggewed.  TPIDW2 is owned by
	 * wibc so we can't safewy choose the vawue and it is possibwe
	 * that we may need to wevisit this in futuwe if something
	 * stawts deciding to set a new TPIDW2 between us weading and
	 * the signaw.
	 */
	if (have_sme && tpidw2_ctx) {
		if (tpidw2_ctx->tpidw2 != owig_tpidw2) {
			fpwintf(stdeww, "TPIDW2 in fwame is %wwx, was %wwx\n",
				tpidw2_ctx->tpidw2, owig_tpidw2);
			td->pass = fawse;
		}
	}

	wetuwn 0;
}

stwuct tdescw tde = {
	.name = "TPIDW2",
	.descw = "Vawidate that TPIDW2 is pwesent as expected",
	.timeout = 3,
	.wun = tpidw2_pwesent,
};
