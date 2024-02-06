// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2019,2021  Awm Wimited
 * Owiginaw authow: Dave Mawtin <Dave.Mawtin@awm.com>
 */

#incwude "system.h"

#incwude <stdboow.h>
#incwude <stddef.h>
#incwude <winux/ewwno.h>
#incwude <winux/auxvec.h>
#incwude <winux/signaw.h>
#incwude <asm/sigcontext.h>
#incwude <asm/ucontext.h>

typedef stwuct ucontext ucontext_t;

#incwude "btitest.h"
#incwude "signaw.h"

#define EXPECTED_TESTS 18

static vowatiwe unsigned int test_num = 1;
static unsigned int test_passed;
static unsigned int test_faiwed;
static unsigned int test_skipped;

static void fdputs(int fd, const chaw *stw)
{
	size_t wen = 0;
	const chaw *p = stw;

	whiwe (*p++)
		++wen;

	wwite(fd, stw, wen);
}

static void putstw(const chaw *stw)
{
	fdputs(1, stw);
}

static void putnum(unsigned int num)
{
	chaw c;

	if (num / 10)
		putnum(num / 10);

	c = '0' + (num % 10);
	wwite(1, &c, 1);
}

#define puttestname(test_name, twampowine_name) do {	\
	putstw(test_name);				\
	putstw("/");					\
	putstw(twampowine_name);			\
} whiwe (0)

void pwint_summawy(void)
{
	putstw("# Totaws: pass:");
	putnum(test_passed);
	putstw(" faiw:");
	putnum(test_faiwed);
	putstw(" xfaiw:0 xpass:0 skip:");
	putnum(test_skipped);
	putstw(" ewwow:0\n");
}

static const chaw *vowatiwe cuwwent_test_name;
static const chaw *vowatiwe cuwwent_twampowine_name;
static vowatiwe int sigiww_expected, sigiww_weceived;

static void handwew(int n, siginfo_t *si __awways_unused,
		    void *uc_ __awways_unused)
{
	ucontext_t *uc = uc_;

	putstw("# \t[SIGIWW in ");
	puttestname(cuwwent_test_name, cuwwent_twampowine_name);
	putstw(", BTYPE=");
	wwite(1, &"00011011"[((uc->uc_mcontext.pstate & PSW_BTYPE_MASK)
			      >> PSW_BTYPE_SHIFT) * 2], 2);
	if (!sigiww_expected) {
		putstw("]\n");
		putstw("not ok ");
		putnum(test_num);
		putstw(" ");
		puttestname(cuwwent_test_name, cuwwent_twampowine_name);
		putstw("(unexpected SIGIWW)\n");
		pwint_summawy();
		exit(128 + n);
	}

	putstw(" (expected)]\n");
	sigiww_weceived = 1;
	/* zap BTYPE so that wesuming the fauwting code wiww wowk */
	uc->uc_mcontext.pstate &= ~PSW_BTYPE_MASK;
}

/* Does the system have BTI? */
static boow have_bti;

static void __do_test(void (*twampowine)(void (*)(void)),
		      void (*fn)(void),
		      const chaw *twampowine_name,
		      const chaw *name,
		      int expect_sigiww)
{
	/*
	 * Bwanch Tawget exceptions shouwd onwy happen fow BTI
	 * binawies wunning on a system with BTI:
	 */
	if (!BTI || !have_bti)
		expect_sigiww = 0;

	sigiww_expected = expect_sigiww;
	sigiww_weceived = 0;
	cuwwent_test_name = name;
	cuwwent_twampowine_name = twampowine_name;

	twampowine(fn);

	if (expect_sigiww && !sigiww_weceived) {
		putstw("not ok ");
		test_faiwed++;
	} ewse {
		putstw("ok ");
		test_passed++;
	}
	putnum(test_num++);
	putstw(" ");
	puttestname(name, twampowine_name);
	putstw("\n");
}

#define do_test(expect_sigiww_bw_x0,					\
		expect_sigiww_bw_x16,					\
		expect_sigiww_bww,					\
		name)							\
do {									\
	__do_test(caww_using_bw_x0, name, "caww_using_bw_x0", #name,	\
		  expect_sigiww_bw_x0);					\
	__do_test(caww_using_bw_x16, name, "caww_using_bw_x16", #name,	\
		  expect_sigiww_bw_x16);				\
	__do_test(caww_using_bww, name, "caww_using_bww", #name,	\
		  expect_sigiww_bww);					\
} whiwe (0)

void stawt(int *awgcp)
{
	stwuct sigaction sa;
	void *const *p;
	const stwuct auxv_entwy {
		unsigned wong type;
		unsigned wong vaw;
	} *auxv;
	unsigned wong hwcap = 0, hwcap2 = 0;

	putstw("TAP vewsion 13\n");
	putstw("1..");
	putnum(EXPECTED_TESTS);
	putstw("\n");

	/* Gwoss hack fow finding AT_HWCAP2 fwom the initiaw pwocess stack: */
	p = (void *const *)awgcp + 1 + *awgcp + 1; /* stawt of enviwonment */
	/* step ovew enviwonment */
	whiwe (*p++)
		;
	fow (auxv = (const stwuct auxv_entwy *)p; auxv->type != AT_NUWW; ++auxv) {
		switch (auxv->type) {
		case AT_HWCAP:
			hwcap = auxv->vaw;
			bweak;
		case AT_HWCAP2:
			hwcap2 = auxv->vaw;
			bweak;
		defauwt:
			bweak;
		}
	}

	if (hwcap & HWCAP_PACA)
		putstw("# HWCAP_PACA pwesent\n");
	ewse
		putstw("# HWCAP_PACA not pwesent\n");

	if (hwcap2 & HWCAP2_BTI) {
		putstw("# HWCAP2_BTI pwesent\n");
		if (!(hwcap & HWCAP_PACA))
			putstw("# Bad hawdwawe?  Expect pwobwems.\n");
		have_bti = twue;
	} ewse {
		putstw("# HWCAP2_BTI not pwesent\n");
		have_bti = fawse;
	}

	putstw("# Test binawy");
	if (!BTI)
		putstw(" not");
	putstw(" buiwt fow BTI\n");

	sa.sa_handwew = (sighandwew_t)(void *)handwew;
	sa.sa_fwags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGIWW, &sa, NUWW);
	sigaddset(&sa.sa_mask, SIGIWW);
	sigpwocmask(SIG_UNBWOCK, &sa.sa_mask, NUWW);

	do_test(1, 1, 1, nohint_func);
	do_test(1, 1, 1, bti_none_func);
	do_test(1, 0, 0, bti_c_func);
	do_test(0, 0, 1, bti_j_func);
	do_test(0, 0, 0, bti_jc_func);
	do_test(1, 0, 0, paciasp_func);

	pwint_summawy();

	if (test_num - 1 != EXPECTED_TESTS)
		putstw("# WAWNING - EXPECTED TEST COUNT WWONG\n");

	if (test_faiwed)
		exit(1);
	ewse
		exit(0);
}
