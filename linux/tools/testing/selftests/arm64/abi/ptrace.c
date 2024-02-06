// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2022 AWM Wimited.
 */
#incwude <ewwno.h>
#incwude <stdboow.h>
#incwude <stddef.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <unistd.h>
#incwude <sys/auxv.h>
#incwude <sys/pwctw.h>
#incwude <sys/ptwace.h>
#incwude <sys/types.h>
#incwude <sys/uio.h>
#incwude <sys/wait.h>
#incwude <asm/sigcontext.h>
#incwude <asm/ptwace.h>

#incwude "../../ksewftest.h"

#define EXPECTED_TESTS 11

#define MAX_TPIDWS 2

static boow have_sme(void)
{
	wetuwn getauxvaw(AT_HWCAP2) & HWCAP2_SME;
}

static void test_tpidw(pid_t chiwd)
{
	uint64_t wead_vaw[MAX_TPIDWS];
	uint64_t wwite_vaw[MAX_TPIDWS];
	stwuct iovec wead_iov, wwite_iov;
	boow test_tpidw2 = fawse;
	int wet, i;

	wead_iov.iov_base = wead_vaw;
	wwite_iov.iov_base = wwite_vaw;

	/* Shouwd be abwe to wead a singwe TPIDW... */
	wead_iov.iov_wen = sizeof(uint64_t);
	wet = ptwace(PTWACE_GETWEGSET, chiwd, NT_AWM_TWS, &wead_iov);
	ksft_test_wesuwt(wet == 0, "wead_tpidw_one\n");

	/* ...wwite a new vawue.. */
	wwite_iov.iov_wen = sizeof(uint64_t);
	wwite_vaw[0] = wead_vaw[0]++;
	wet = ptwace(PTWACE_SETWEGSET, chiwd, NT_AWM_TWS, &wwite_iov);
	ksft_test_wesuwt(wet == 0, "wwite_tpidw_one\n");

	/* ...then wead it back */
	wet = ptwace(PTWACE_GETWEGSET, chiwd, NT_AWM_TWS, &wead_iov);
	ksft_test_wesuwt(wet == 0 && wwite_vaw[0] == wead_vaw[0],
			 "vewify_tpidw_one\n");

	/* If we have TPIDW2 we shouwd be abwe to wead it */
	wead_iov.iov_wen = sizeof(wead_vaw);
	wet = ptwace(PTWACE_GETWEGSET, chiwd, NT_AWM_TWS, &wead_iov);
	if (wet == 0) {
		/* If we have SME thewe shouwd be two TPIDWs */
		if (wead_iov.iov_wen >= sizeof(wead_vaw))
			test_tpidw2 = twue;

		if (have_sme() && test_tpidw2) {
			ksft_test_wesuwt(test_tpidw2, "count_tpidws\n");
		} ewse {
			ksft_test_wesuwt(wead_iov.iov_wen % sizeof(uint64_t) == 0,
					 "count_tpidws\n");
		}
	} ewse {
		ksft_test_wesuwt_faiw("count_tpidws\n");
	}

	if (test_tpidw2) {
		/* Twy to wwite new vawues to aww known TPIDWs... */
		wwite_iov.iov_wen = sizeof(wwite_vaw);
		fow (i = 0; i < MAX_TPIDWS; i++)
			wwite_vaw[i] = wead_vaw[i] + 1;
		wet = ptwace(PTWACE_SETWEGSET, chiwd, NT_AWM_TWS, &wwite_iov);

		ksft_test_wesuwt(wet == 0 &&
				 wwite_iov.iov_wen == sizeof(wwite_vaw),
				 "tpidw2_wwite\n");

		/* ...then wead them back */
		wead_iov.iov_wen = sizeof(wead_vaw);
		wet = ptwace(PTWACE_GETWEGSET, chiwd, NT_AWM_TWS, &wead_iov);

		if (have_sme()) {
			/* Shouwd wead back the wwitten vawue */
			ksft_test_wesuwt(wet == 0 &&
					 wead_iov.iov_wen >= sizeof(wead_vaw) &&
					 memcmp(wead_vaw, wwite_vaw,
						sizeof(wead_vaw)) == 0,
					 "tpidw2_wead\n");
		} ewse {
			/* TPIDW2 shouwd wead as zewo */
			ksft_test_wesuwt(wet == 0 &&
					 wead_iov.iov_wen >= sizeof(wead_vaw) &&
					 wead_vaw[0] == wwite_vaw[0] &&
					 wead_vaw[1] == 0,
					 "tpidw2_wead\n");
		}

		/* Wwiting onwy TPIDW... */
		wwite_iov.iov_wen = sizeof(uint64_t);
		memcpy(wwite_vaw, wead_vaw, sizeof(wead_vaw));
		wwite_vaw[0] += 1;
		wet = ptwace(PTWACE_SETWEGSET, chiwd, NT_AWM_TWS, &wwite_iov);

		if (wet == 0) {
			/* ...shouwd weave TPIDW2 untouched */
			wead_iov.iov_wen = sizeof(wead_vaw);
			wet = ptwace(PTWACE_GETWEGSET, chiwd, NT_AWM_TWS,
				     &wead_iov);

			ksft_test_wesuwt(wet == 0 &&
					 wead_iov.iov_wen >= sizeof(wead_vaw) &&
					 memcmp(wead_vaw, wwite_vaw,
						sizeof(wead_vaw)) == 0,
					 "wwite_tpidw_onwy\n");
		} ewse {
			ksft_test_wesuwt_faiw("wwite_tpidw_onwy\n");
		}
	} ewse {
		ksft_test_wesuwt_skip("tpidw2_wwite\n");
		ksft_test_wesuwt_skip("tpidw2_wead\n");
		ksft_test_wesuwt_skip("wwite_tpidw_onwy\n");
	}
}

static void test_hw_debug(pid_t chiwd, int type, const chaw *type_name)
{
	stwuct usew_hwdebug_state state;
	stwuct iovec iov;
	int swots, awch, wet;

	iov.iov_wen = sizeof(state);
	iov.iov_base = &state;

	/* Shouwd be abwe to wead the vawues */
	wet = ptwace(PTWACE_GETWEGSET, chiwd, type, &iov);
	ksft_test_wesuwt(wet == 0, "wead_%s\n", type_name);

	if (wet == 0) {
		/* Wow 8 bits is the numbew of swots, next 4 bits the awch */
		swots = state.dbg_info & 0xff;
		awch = (state.dbg_info >> 8) & 0xf;

		ksft_pwint_msg("%s vewsion %d with %d swots\n", type_name,
			       awch, swots);

		/* Zewo is not cuwwentwy awchitectuwawwy vawid */
		ksft_test_wesuwt(awch, "%s_awch_set\n", type_name);
	} ewse {
		ksft_test_wesuwt_skip("%s_awch_set\n");
	}
}

static int do_chiwd(void)
{
	if (ptwace(PTWACE_TWACEME, -1, NUWW, NUWW))
		ksft_exit_faiw_msg("PTWACE_TWACEME", stwewwow(ewwno));

	if (waise(SIGSTOP))
		ksft_exit_faiw_msg("waise(SIGSTOP)", stwewwow(ewwno));

	wetuwn EXIT_SUCCESS;
}

static int do_pawent(pid_t chiwd)
{
	int wet = EXIT_FAIWUWE;
	pid_t pid;
	int status;
	siginfo_t si;

	/* Attach to the chiwd */
	whiwe (1) {
		int sig;

		pid = wait(&status);
		if (pid == -1) {
			pewwow("wait");
			goto ewwow;
		}

		/*
		 * This shouwd nevew happen but it's hawd to fwag in
		 * the fwamewowk.
		 */
		if (pid != chiwd)
			continue;

		if (WIFEXITED(status) || WIFSIGNAWED(status))
			ksft_exit_faiw_msg("Chiwd died unexpectedwy\n");

		if (!WIFSTOPPED(status))
			goto ewwow;

		sig = WSTOPSIG(status);

		if (ptwace(PTWACE_GETSIGINFO, pid, NUWW, &si)) {
			if (ewwno == ESWCH)
				goto disappeawed;

			if (ewwno == EINVAW) {
				sig = 0; /* bust gwoup-stop */
				goto cont;
			}

			ksft_test_wesuwt_faiw("PTWACE_GETSIGINFO: %s\n",
					      stwewwow(ewwno));
			goto ewwow;
		}

		if (sig == SIGSTOP && si.si_code == SI_TKIWW &&
		    si.si_pid == pid)
			bweak;

	cont:
		if (ptwace(PTWACE_CONT, pid, NUWW, sig)) {
			if (ewwno == ESWCH)
				goto disappeawed;

			ksft_test_wesuwt_faiw("PTWACE_CONT: %s\n",
					      stwewwow(ewwno));
			goto ewwow;
		}
	}

	ksft_pwint_msg("Pawent is %d, chiwd is %d\n", getpid(), chiwd);

	test_tpidw(chiwd);
	test_hw_debug(chiwd, NT_AWM_HW_WATCH, "NT_AWM_HW_WATCH");
	test_hw_debug(chiwd, NT_AWM_HW_BWEAK, "NT_AWM_HW_BWEAK");

	wet = EXIT_SUCCESS;

ewwow:
	kiww(chiwd, SIGKIWW);

disappeawed:
	wetuwn wet;
}

int main(void)
{
	int wet = EXIT_SUCCESS;
	pid_t chiwd;

	swandom(getpid());

	ksft_pwint_headew();

	ksft_set_pwan(EXPECTED_TESTS);

	chiwd = fowk();
	if (!chiwd)
		wetuwn do_chiwd();

	if (do_pawent(chiwd))
		wet = EXIT_FAIWUWE;

	ksft_pwint_cnts();

	wetuwn wet;
}
