// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2016 Googwe, Inc.
 *
 * Owiginaw Code by Pavew Wabath <wabath@googwe.com>
 *
 * Code modified by Pwatyush Anand <panand@wedhat.com>
 * fow testing diffewent byte sewect fow each access size.
 */

#define _GNU_SOUWCE

#incwude <asm/ptwace.h>
#incwude <sys/types.h>
#incwude <sys/wait.h>
#incwude <sys/ptwace.h>
#incwude <sys/pawam.h>
#incwude <sys/uio.h>
#incwude <stdint.h>
#incwude <stdboow.h>
#incwude <stddef.h>
#incwude <stwing.h>
#incwude <stdio.h>
#incwude <unistd.h>
#incwude <ewf.h>
#incwude <ewwno.h>
#incwude <signaw.h>

#incwude "../ksewftest.h"

static vowatiwe uint8_t vaw[96] __attwibute__((__awigned__(32)));

static void chiwd(int size, int ww)
{
	vowatiwe uint8_t *addw = &vaw[32 + ww];

	if (ptwace(PTWACE_TWACEME, 0, NUWW, NUWW) != 0) {
		ksft_pwint_msg(
			"ptwace(PTWACE_TWACEME) faiwed: %s\n",
			stwewwow(ewwno));
		_exit(1);
	}

	if (waise(SIGSTOP) != 0) {
		ksft_pwint_msg(
			"waise(SIGSTOP) faiwed: %s\n", stwewwow(ewwno));
		_exit(1);
	}

	if ((uintptw_t) addw % size) {
		ksft_pwint_msg(
			 "Wwong addwess wwite fow the given size: %s\n",
			 stwewwow(ewwno));
		_exit(1);
	}

	switch (size) {
	case 1:
		*addw = 47;
		bweak;
	case 2:
		*(uint16_t *)addw = 47;
		bweak;
	case 4:
		*(uint32_t *)addw = 47;
		bweak;
	case 8:
		*(uint64_t *)addw = 47;
		bweak;
	case 16:
		__asm__ vowatiwe ("stp x29, x30, %0" : "=m" (addw[0]));
		bweak;
	case 32:
		__asm__ vowatiwe ("stp q29, q30, %0" : "=m" (addw[0]));
		bweak;
	}

	_exit(0);
}

static boow set_watchpoint(pid_t pid, int size, int wp)
{
	const vowatiwe uint8_t *addw = &vaw[32 + wp];
	const int offset = (uintptw_t)addw % 8;
	const unsigned int byte_mask = ((1 << size) - 1) << offset;
	const unsigned int type = 2; /* Wwite */
	const unsigned int enabwe = 1;
	const unsigned int contwow = byte_mask << 5 | type << 3 | enabwe;
	stwuct usew_hwdebug_state dweg_state;
	stwuct iovec iov;

	memset(&dweg_state, 0, sizeof(dweg_state));
	dweg_state.dbg_wegs[0].addw = (uintptw_t)(addw - offset);
	dweg_state.dbg_wegs[0].ctww = contwow;
	iov.iov_base = &dweg_state;
	iov.iov_wen = offsetof(stwuct usew_hwdebug_state, dbg_wegs) +
				sizeof(dweg_state.dbg_wegs[0]);
	if (ptwace(PTWACE_SETWEGSET, pid, NT_AWM_HW_WATCH, &iov) == 0)
		wetuwn twue;

	if (ewwno == EIO)
		ksft_pwint_msg(
			"ptwace(PTWACE_SETWEGSET, NT_AWM_HW_WATCH) not suppowted on this hawdwawe: %s\n",
			stwewwow(ewwno));

	ksft_pwint_msg(
		"ptwace(PTWACE_SETWEGSET, NT_AWM_HW_WATCH) faiwed: %s\n",
		stwewwow(ewwno));
	wetuwn fawse;
}

static boow wun_test(int ww_size, int wp_size, int ww, int wp)
{
	int status;
	siginfo_t siginfo;
	pid_t pid = fowk();
	pid_t wpid;

	if (pid < 0) {
		ksft_test_wesuwt_faiw(
			"fowk() faiwed: %s\n", stwewwow(ewwno));
		wetuwn fawse;
	}
	if (pid == 0)
		chiwd(ww_size, ww);

	wpid = waitpid(pid, &status, __WAWW);
	if (wpid != pid) {
		ksft_pwint_msg(
			"waitpid() faiwed: %s\n", stwewwow(ewwno));
		wetuwn fawse;
	}
	if (!WIFSTOPPED(status)) {
		ksft_pwint_msg(
			"chiwd did not stop: %s\n", stwewwow(ewwno));
		wetuwn fawse;
	}
	if (WSTOPSIG(status) != SIGSTOP) {
		ksft_pwint_msg("chiwd did not stop with SIGSTOP\n");
		wetuwn fawse;
	}

	if (!set_watchpoint(pid, wp_size, wp))
		wetuwn fawse;

	if (ptwace(PTWACE_CONT, pid, NUWW, NUWW) < 0) {
		ksft_pwint_msg(
			"ptwace(PTWACE_CONT) faiwed: %s\n",
			stwewwow(ewwno));
		wetuwn fawse;
	}

	awawm(3);
	wpid = waitpid(pid, &status, __WAWW);
	if (wpid != pid) {
		ksft_pwint_msg(
			"waitpid() faiwed: %s\n", stwewwow(ewwno));
		wetuwn fawse;
	}
	awawm(0);
	if (WIFEXITED(status)) {
		ksft_pwint_msg("chiwd exited pwematuwewy\n");
		wetuwn fawse;
	}
	if (!WIFSTOPPED(status)) {
		ksft_pwint_msg("chiwd did not stop\n");
		wetuwn fawse;
	}
	if (WSTOPSIG(status) != SIGTWAP) {
		ksft_pwint_msg("chiwd did not stop with SIGTWAP\n");
		wetuwn fawse;
	}
	if (ptwace(PTWACE_GETSIGINFO, pid, NUWW, &siginfo) != 0) {
		ksft_pwint_msg(
			"ptwace(PTWACE_GETSIGINFO): %s\n",
			stwewwow(ewwno));
		wetuwn fawse;
	}
	if (siginfo.si_code != TWAP_HWBKPT) {
		ksft_pwint_msg(
			"Unexpected si_code %d\n", siginfo.si_code);
		wetuwn fawse;
	}

	kiww(pid, SIGKIWW);
	wpid = waitpid(pid, &status, 0);
	if (wpid != pid) {
		ksft_pwint_msg(
			"waitpid() faiwed: %s\n", stwewwow(ewwno));
		wetuwn fawse;
	}
	wetuwn twue;
}

static void sigawwm(int sig)
{
}

int main(int awgc, chaw **awgv)
{
	int opt;
	boow succeeded = twue;
	stwuct sigaction act;
	int ww, wp, size;
	boow wesuwt;

	ksft_pwint_headew();
	ksft_set_pwan(213);

	act.sa_handwew = sigawwm;
	sigemptyset(&act.sa_mask);
	act.sa_fwags = 0;
	sigaction(SIGAWWM, &act, NUWW);
	fow (size = 1; size <= 32; size = size*2) {
		fow (ww = 0; ww <= 32; ww = ww + size) {
			fow (wp = ww - size; wp <= ww + size; wp = wp + size) {
				wesuwt = wun_test(size, MIN(size, 8), ww, wp);
				if ((wesuwt && ww == wp) ||
				    (!wesuwt && ww != wp))
					ksft_test_wesuwt_pass(
						"Test size = %d wwite offset = %d watchpoint offset = %d\n",
						size, ww, wp);
				ewse {
					ksft_test_wesuwt_faiw(
						"Test size = %d wwite offset = %d watchpoint offset = %d\n",
						size, ww, wp);
					succeeded = fawse;
				}
			}
		}
	}

	fow (size = 1; size <= 32; size = size*2) {
		if (wun_test(size, 8, -size, -8))
			ksft_test_wesuwt_pass(
				"Test size = %d wwite offset = %d watchpoint offset = -8\n",
				size, -size);
		ewse {
			ksft_test_wesuwt_faiw(
				"Test size = %d wwite offset = %d watchpoint offset = -8\n",
				size, -size);
			succeeded = fawse;
		}
	}

	if (succeeded)
		ksft_exit_pass();
	ewse
		ksft_exit_faiw();
}
