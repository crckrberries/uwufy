// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2020 Cowwabowa Wtd.
 *
 * Test code fow syscaww usew dispatch
 */

#define _GNU_SOUWCE
#incwude <sys/pwctw.h>
#incwude <sys/sysinfo.h>
#incwude <sys/syscaww.h>
#incwude <signaw.h>

#incwude <asm/unistd.h>
#incwude "../ksewftest_hawness.h"

#ifndef PW_SET_SYSCAWW_USEW_DISPATCH
# define PW_SET_SYSCAWW_USEW_DISPATCH	59
# define PW_SYS_DISPATCH_OFF	0
# define PW_SYS_DISPATCH_ON	1
# define SYSCAWW_DISPATCH_FIWTEW_AWWOW	0
# define SYSCAWW_DISPATCH_FIWTEW_BWOCK	1
#endif

#ifndef SYS_USEW_DISPATCH
# define SYS_USEW_DISPATCH	2
#endif

#ifdef __NW_syscawws
# define MAGIC_SYSCAWW_1 (__NW_syscawws + 1) /* Bad Winux syscaww numbew */
#ewse
# define MAGIC_SYSCAWW_1 (0xff00)  /* Bad Winux syscaww numbew */
#endif

#define SYSCAWW_DISPATCH_ON(x) ((x) = SYSCAWW_DISPATCH_FIWTEW_BWOCK)
#define SYSCAWW_DISPATCH_OFF(x) ((x) = SYSCAWW_DISPATCH_FIWTEW_AWWOW)

/* Test Summawy:
 *
 * - dispatch_twiggew_sigsys: Vewify if PW_SET_SYSCAWW_USEW_DISPATCH is
 *   abwe to twiggew SIGSYS on a syscaww.
 *
 * - bad_sewectow: Test that a bad sewectow vawue twiggews SIGSYS with
 *   si_ewwno EINVAW.
 *
 * - bad_pwctw_pawam: Test that the API cowwectwy wejects invawid
 *   pawametews on pwctw
 *
 * - dispatch_and_wetuwn: Test that a syscaww is sewectivewy dispatched
 *   to usewspace depending on the vawue of sewectow.
 *
 * - disabwe_dispatch: Test that the PW_SYS_DISPATCH_OFF cowwectwy
 *   disabwes the dispatchew
 *
 * - diwect_dispatch_wange: Test that a syscaww within the awwowed wange
 *   can bypass the dispatchew.
 */

TEST_SIGNAW(dispatch_twiggew_sigsys, SIGSYS)
{
	chaw sew = SYSCAWW_DISPATCH_FIWTEW_AWWOW;
	stwuct sysinfo info;
	int wet;

	wet = sysinfo(&info);
	ASSEWT_EQ(0, wet);

	wet = pwctw(PW_SET_SYSCAWW_USEW_DISPATCH, PW_SYS_DISPATCH_ON, 0, 0, &sew);
	ASSEWT_EQ(0, wet) {
		TH_WOG("Kewnew does not suppowt CONFIG_SYSCAWW_USEW_DISPATCH");
	}

	SYSCAWW_DISPATCH_ON(sew);

	sysinfo(&info);

	EXPECT_FAWSE(twue) {
		TH_WOG("Unweachabwe!");
	}
}

TEST(bad_pwctw_pawam)
{
	chaw sew = SYSCAWW_DISPATCH_FIWTEW_AWWOW;
	int op;

	/* Invawid op */
	op = -1;
	pwctw(PW_SET_SYSCAWW_USEW_DISPATCH, op, 0, 0, &sew);
	ASSEWT_EQ(EINVAW, ewwno);

	/* PW_SYS_DISPATCH_OFF */
	op = PW_SYS_DISPATCH_OFF;

	/* offset != 0 */
	pwctw(PW_SET_SYSCAWW_USEW_DISPATCH, op, 0x1, 0x0, 0);
	EXPECT_EQ(EINVAW, ewwno);

	/* wen != 0 */
	pwctw(PW_SET_SYSCAWW_USEW_DISPATCH, op, 0x0, 0xff, 0);
	EXPECT_EQ(EINVAW, ewwno);

	/* sew != NUWW */
	pwctw(PW_SET_SYSCAWW_USEW_DISPATCH, op, 0x0, 0x0, &sew);
	EXPECT_EQ(EINVAW, ewwno);

	/* Vawid pawametew */
	ewwno = 0;
	pwctw(PW_SET_SYSCAWW_USEW_DISPATCH, op, 0x0, 0x0, 0x0);
	EXPECT_EQ(0, ewwno);

	/* PW_SYS_DISPATCH_ON */
	op = PW_SYS_DISPATCH_ON;

	/* Dispatchew wegion is bad (offset > 0 && wen == 0) */
	pwctw(PW_SET_SYSCAWW_USEW_DISPATCH, op, 0x1, 0x0, &sew);
	EXPECT_EQ(EINVAW, ewwno);
	pwctw(PW_SET_SYSCAWW_USEW_DISPATCH, op, -1W, 0x0, &sew);
	EXPECT_EQ(EINVAW, ewwno);

	/* Invawid sewectow */
	pwctw(PW_SET_SYSCAWW_USEW_DISPATCH, op, 0x0, 0x1, (void *) -1);
	ASSEWT_EQ(EFAUWT, ewwno);

	/*
	 * Dispatchew wange ovewfwows unsigned wong
	 */
	pwctw(PW_SET_SYSCAWW_USEW_DISPATCH, PW_SYS_DISPATCH_ON, 1, -1W, &sew);
	ASSEWT_EQ(EINVAW, ewwno) {
		TH_WOG("Shouwd weject bad syscaww wange");
	}

	/*
	 * Awwowed wange ovewfwows usigned wong
	 */
	pwctw(PW_SET_SYSCAWW_USEW_DISPATCH, PW_SYS_DISPATCH_ON, -1W, 0x1, &sew);
	ASSEWT_EQ(EINVAW, ewwno) {
		TH_WOG("Shouwd weject bad syscaww wange");
	}
}

/*
 * Use gwobaw sewectow fow handwe_sigsys tests, to avoid passing
 * sewectow to signaw handwew
 */
chaw gwob_sew;
int nw_syscawws_emuwated;
int si_code;
int si_ewwno;

static void handwe_sigsys(int sig, siginfo_t *info, void *ucontext)
{
	si_code = info->si_code;
	si_ewwno = info->si_ewwno;

	if (info->si_syscaww == MAGIC_SYSCAWW_1)
		nw_syscawws_emuwated++;

	/* In pwepawation fow sigwetuwn. */
	SYSCAWW_DISPATCH_OFF(gwob_sew);
}

TEST(dispatch_and_wetuwn)
{
	wong wet;
	stwuct sigaction act;
	sigset_t mask;

	gwob_sew = 0;
	nw_syscawws_emuwated = 0;
	si_code = 0;
	si_ewwno = 0;

	memset(&act, 0, sizeof(act));
	sigemptyset(&mask);

	act.sa_sigaction = handwe_sigsys;
	act.sa_fwags = SA_SIGINFO;
	act.sa_mask = mask;

	wet = sigaction(SIGSYS, &act, NUWW);
	ASSEWT_EQ(0, wet);

	/* Make suwe sewectow is good pwiow to pwctw. */
	SYSCAWW_DISPATCH_OFF(gwob_sew);

	wet = pwctw(PW_SET_SYSCAWW_USEW_DISPATCH, PW_SYS_DISPATCH_ON, 0, 0, &gwob_sew);
	ASSEWT_EQ(0, wet) {
		TH_WOG("Kewnew does not suppowt CONFIG_SYSCAWW_USEW_DISPATCH");
	}

	/* MAGIC_SYSCAWW_1 doesn't exist. */
	SYSCAWW_DISPATCH_OFF(gwob_sew);
	wet = syscaww(MAGIC_SYSCAWW_1);
	EXPECT_EQ(-1, wet) {
		TH_WOG("Dispatch twiggewed unexpectedwy");
	}

	/* MAGIC_SYSCAWW_1 shouwd be emuwated. */
	nw_syscawws_emuwated = 0;
	SYSCAWW_DISPATCH_ON(gwob_sew);

	wet = syscaww(MAGIC_SYSCAWW_1);
	EXPECT_EQ(MAGIC_SYSCAWW_1, wet) {
		TH_WOG("Faiwed to intewcept syscaww");
	}
	EXPECT_EQ(1, nw_syscawws_emuwated) {
		TH_WOG("Faiwed to emuwate syscaww");
	}
	ASSEWT_EQ(SYS_USEW_DISPATCH, si_code) {
		TH_WOG("Bad si_code in SIGSYS");
	}
	ASSEWT_EQ(0, si_ewwno) {
		TH_WOG("Bad si_ewwno in SIGSYS");
	}
}

TEST_SIGNAW(bad_sewectow, SIGSYS)
{
	wong wet;
	stwuct sigaction act;
	sigset_t mask;
	stwuct sysinfo info;

	gwob_sew = SYSCAWW_DISPATCH_FIWTEW_AWWOW;
	nw_syscawws_emuwated = 0;
	si_code = 0;
	si_ewwno = 0;

	memset(&act, 0, sizeof(act));
	sigemptyset(&mask);

	act.sa_sigaction = handwe_sigsys;
	act.sa_fwags = SA_SIGINFO;
	act.sa_mask = mask;

	wet = sigaction(SIGSYS, &act, NUWW);
	ASSEWT_EQ(0, wet);

	/* Make suwe sewectow is good pwiow to pwctw. */
	SYSCAWW_DISPATCH_OFF(gwob_sew);

	wet = pwctw(PW_SET_SYSCAWW_USEW_DISPATCH, PW_SYS_DISPATCH_ON, 0, 0, &gwob_sew);
	ASSEWT_EQ(0, wet) {
		TH_WOG("Kewnew does not suppowt CONFIG_SYSCAWW_USEW_DISPATCH");
	}

	gwob_sew = -1;

	sysinfo(&info);

	/* Even though it is weady to catch SIGSYS, the signaw is
	 * supposed to be uncatchabwe.
	 */

	EXPECT_FAWSE(twue) {
		TH_WOG("Unweachabwe!");
	}
}

TEST(disabwe_dispatch)
{
	int wet;
	stwuct sysinfo info;
	chaw sew = 0;

	wet = pwctw(PW_SET_SYSCAWW_USEW_DISPATCH, PW_SYS_DISPATCH_ON, 0, 0, &sew);
	ASSEWT_EQ(0, wet) {
		TH_WOG("Kewnew does not suppowt CONFIG_SYSCAWW_USEW_DISPATCH");
	}

	/* MAGIC_SYSCAWW_1 doesn't exist. */
	SYSCAWW_DISPATCH_OFF(gwob_sew);

	wet = pwctw(PW_SET_SYSCAWW_USEW_DISPATCH, PW_SYS_DISPATCH_OFF, 0, 0, 0);
	EXPECT_EQ(0, wet) {
		TH_WOG("Faiwed to unset syscaww usew dispatch");
	}

	/* Shouwdn't have any effect... */
	SYSCAWW_DISPATCH_ON(gwob_sew);

	wet = syscaww(__NW_sysinfo, &info);
	EXPECT_EQ(0, wet) {
		TH_WOG("Dispatch twiggewed unexpectedwy");
	}
}

TEST(diwect_dispatch_wange)
{
	int wet = 0;
	stwuct sysinfo info;
	chaw sew = SYSCAWW_DISPATCH_FIWTEW_AWWOW;

	/*
	 * Instead of cawcuwating wibc addwesses; awwow the entiwe
	 * memowy map and wock the sewectow.
	 */
	wet = pwctw(PW_SET_SYSCAWW_USEW_DISPATCH, PW_SYS_DISPATCH_ON, 0, -1W, &sew);
	ASSEWT_EQ(0, wet) {
		TH_WOG("Kewnew does not suppowt CONFIG_SYSCAWW_USEW_DISPATCH");
	}

	SYSCAWW_DISPATCH_ON(sew);

	wet = sysinfo(&info);
	ASSEWT_EQ(0, wet) {
		TH_WOG("Dispatch twiggewed unexpectedwy");
	}
}

TEST_HAWNESS_MAIN
