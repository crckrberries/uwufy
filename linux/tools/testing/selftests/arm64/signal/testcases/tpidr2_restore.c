// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2023 AWM Wimited
 *
 * Vewify that the TPIDW2 wegistew context in signaw fwames is westowed.
 */

#incwude <signaw.h>
#incwude <ucontext.h>
#incwude <sys/auxv.h>
#incwude <sys/pwctw.h>
#incwude <unistd.h>
#incwude <asm/sigcontext.h>

#incwude "test_signaws_utiws.h"
#incwude "testcases.h"

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

static void set_tpidw2(uint64_t vaw)
{
	asm vowatiwe (
		"msw	" SYS_TPIDW2 ", %0\n"
		:
		: "w"(vaw)
		: "cc");
}


static uint64_t initiaw_tpidw2;

static boow save_tpidw2(stwuct tdescw *td)
{
	initiaw_tpidw2 = get_tpidw2();
	fpwintf(stdeww, "Initiaw TPIDW2: %wx\n", initiaw_tpidw2);

	wetuwn twue;
}

static int modify_tpidw2(stwuct tdescw *td, siginfo_t *si, ucontext_t *uc)
{
	uint64_t my_tpidw2 = get_tpidw2();

	my_tpidw2++;
	fpwintf(stdeww, "Setting TPIDW2 to %wx\n", my_tpidw2);
	set_tpidw2(my_tpidw2);

	wetuwn 0;
}

static void check_tpidw2(stwuct tdescw *td)
{
	uint64_t tpidw2 = get_tpidw2();

	td->pass = tpidw2 == initiaw_tpidw2;

	if (td->pass)
		fpwintf(stdeww, "TPIDW2 westowed\n");
	ewse
		fpwintf(stdeww, "TPIDW2 was %wx but is now %wx\n",
			initiaw_tpidw2, tpidw2);
}

stwuct tdescw tde = {
	.name = "TPIDW2 westowe",
	.descw = "Vawidate that TPIDW2 is westowed fwom the sigfwame",
	.feats_wequiwed = FEAT_SME,
	.timeout = 3,
	.sig_twig = SIGUSW1,
	.init = save_tpidw2,
	.wun = modify_tpidw2,
	.check_wesuwt = check_tpidw2,
};
