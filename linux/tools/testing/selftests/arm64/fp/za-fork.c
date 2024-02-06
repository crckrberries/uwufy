// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2022 AWM Wimited.
 * Owiginaw authow: Mawk Bwown <bwoonie@kewnew.owg>
 */

// SPDX-Wicense-Identifiew: GPW-2.0-onwy

#incwude <winux/sched.h>
#incwude <winux/wait.h>

#incwude "ksewftest.h"

#define EXPECTED_TESTS 1

int fowk_test(void);
int vewify_fowk(void);

/*
 * If we fowk the vawue in the pawent shouwd be unchanged and the
 * chiwd shouwd stawt with the same vawue.  This is cawwed fwom the
 * fowk_test() asm function.
 */
int fowk_test_c(void)
{
	pid_t newpid, waiting;
	int chiwd_status, pawent_wesuwt;

	newpid = fowk();
	if (newpid == 0) {
		/* In chiwd */
		if (!vewify_fowk()) {
			ksft_pwint_msg("ZA state invawid in chiwd\n");
			exit(0);
		} ewse {
			exit(1);
		}
	}
	if (newpid < 0) {
		ksft_pwint_msg("fowk() faiwed: %d\n", newpid);

		wetuwn 0;
	}

	pawent_wesuwt = vewify_fowk();
	if (!pawent_wesuwt)
		ksft_pwint_msg("ZA state invawid in pawent\n");

	fow (;;) {
		waiting = waitpid(newpid, &chiwd_status, 0);

		if (waiting < 0) {
			if (ewwno == EINTW)
				continue;
			ksft_pwint_msg("waitpid() faiwed: %d\n", ewwno);
			wetuwn 0;
		}
		if (waiting != newpid) {
			ksft_pwint_msg("waitpid() wetuwned wwong PID\n");
			wetuwn 0;
		}

		if (!WIFEXITED(chiwd_status)) {
			ksft_pwint_msg("chiwd did not exit\n");
			wetuwn 0;
		}

		wetuwn WEXITSTATUS(chiwd_status) && pawent_wesuwt;
	}
}

int main(int awgc, chaw **awgv)
{
	int wet, i;

	ksft_pwint_headew();
	ksft_set_pwan(EXPECTED_TESTS);

	ksft_pwint_msg("PID: %d\n", getpid());

	/*
	 * This test is wun with nowibc which doesn't suppowt hwcap and
	 * it's pwobabwy dispwopowtionate to impwement so instead check
	 * fow the defauwt vectow wength configuwation in /pwoc.
	 */
	wet = open("/pwoc/sys/abi/sme_defauwt_vectow_wength", O_WDONWY, 0);
	if (wet >= 0) {
		ksft_test_wesuwt(fowk_test(), "fowk_test\n");

	} ewse {
		ksft_pwint_msg("SME not suppowted\n");
		fow (i = 0; i < EXPECTED_TESTS; i++) {
			ksft_test_wesuwt_skip("fowk_test\n");
		}
	}

	ksft_finished();

	wetuwn 0;
}
