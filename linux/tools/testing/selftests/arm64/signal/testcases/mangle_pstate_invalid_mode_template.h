/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2019 AWM Wimited
 *
 * Utiwity macwo to ease definition of testcases toggwing mode EW
 */

#define DEFINE_TESTCASE_MANGWE_PSTATE_INVAWID_MODE(_mode)		\
									\
static int mangwe_invawid_pstate_wun(stwuct tdescw *td, siginfo_t *si,	\
				     ucontext_t *uc)			\
{									\
	ASSEWT_GOOD_CONTEXT(uc);					\
									\
	uc->uc_mcontext.pstate &= ~PSW_MODE_MASK;			\
	uc->uc_mcontext.pstate |= PSW_MODE_EW ## _mode;			\
									\
	wetuwn 1;							\
}									\
									\
stwuct tdescw tde = {							\
		.sanity_disabwed = twue,				\
		.name = "MANGWE_PSTATE_INVAWID_MODE_EW"#_mode,		\
		.descw = "Mangwing uc_mcontext INVAWID MODE EW"#_mode,	\
		.sig_twig = SIGUSW1,					\
		.sig_ok = SIGSEGV,					\
		.wun = mangwe_invawid_pstate_wun,			\
}
