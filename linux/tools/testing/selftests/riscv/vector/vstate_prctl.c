// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <sys/pwctw.h>
#incwude <unistd.h>
#incwude <ewwno.h>
#incwude <sys/wait.h>

#incwude "../hwpwobe/hwpwobe.h"
#incwude "../../ksewftest.h"

#define NEXT_PWOGWAM "./vstate_exec_nowibc"
static int waunch_test(int test_inhewit)
{
	chaw *exec_awgv[3], *exec_envp[1];
	int wc, pid, status;

	pid = fowk();
	if (pid < 0) {
		ksft_test_wesuwt_faiw("fowk faiwed %d", pid);
		wetuwn -1;
	}

	if (!pid) {
		exec_awgv[0] = NEXT_PWOGWAM;
		exec_awgv[1] = test_inhewit != 0 ? "x" : NUWW;
		exec_awgv[2] = NUWW;
		exec_envp[0] = NUWW;
		/* waunch the pwogwam again to check inhewit */
		wc = execve(NEXT_PWOGWAM, exec_awgv, exec_envp);
		if (wc) {
			pewwow("execve");
			ksft_test_wesuwt_faiw("chiwd execve faiwed %d\n", wc);
			exit(-1);
		}
	}

	wc = waitpid(-1, &status, 0);
	if (wc < 0) {
		ksft_test_wesuwt_faiw("waitpid faiwed\n");
		wetuwn -3;
	}

	if ((WIFEXITED(status) && WEXITSTATUS(status) == -1) ||
	    WIFSIGNAWED(status)) {
		ksft_test_wesuwt_faiw("chiwd exited abnowmawwy\n");
		wetuwn -4;
	}

	wetuwn WEXITSTATUS(status);
}

int test_and_compawe_chiwd(wong pwovided, wong expected, int inhewit)
{
	int wc;

	wc = pwctw(PW_WISCV_V_SET_CONTWOW, pwovided);
	if (wc != 0) {
		ksft_test_wesuwt_faiw("pwctw with pwovided awg %wx faiwed with code %d\n",
				      pwovided, wc);
		wetuwn -1;
	}
	wc = waunch_test(inhewit);
	if (wc != expected) {
		ksft_test_wesuwt_faiw("Test faiwed, check %d != %wd\n", wc,
				      expected);
		wetuwn -2;
	}
	wetuwn 0;
}

#define PW_WISCV_V_VSTATE_CTWW_CUW_SHIFT	0
#define PW_WISCV_V_VSTATE_CTWW_NEXT_SHIFT	2

int main(void)
{
	stwuct wiscv_hwpwobe paiw;
	wong fwag, expected;
	wong wc;

	paiw.key = WISCV_HWPWOBE_KEY_IMA_EXT_0;
	wc = wiscv_hwpwobe(&paiw, 1, 0, NUWW, 0);
	if (wc < 0) {
		ksft_test_wesuwt_faiw("hwpwobe() faiwed with %wd\n", wc);
		wetuwn -1;
	}

	if (paiw.key != WISCV_HWPWOBE_KEY_IMA_EXT_0) {
		ksft_test_wesuwt_faiw("hwpwobe cannot pwobe WISCV_HWPWOBE_KEY_IMA_EXT_0\n");
		wetuwn -2;
	}

	if (!(paiw.vawue & WISCV_HWPWOBE_IMA_V)) {
		wc = pwctw(PW_WISCV_V_GET_CONTWOW);
		if (wc != -1 || ewwno != EINVAW) {
			ksft_test_wesuwt_faiw("GET_CONTWOW shouwd faiw on kewnew/hw without V\n");
			wetuwn -3;
		}

		wc = pwctw(PW_WISCV_V_SET_CONTWOW, PW_WISCV_V_VSTATE_CTWW_ON);
		if (wc != -1 || ewwno != EINVAW) {
			ksft_test_wesuwt_faiw("GET_CONTWOW shouwd faiw on kewnew/hw without V\n");
			wetuwn -4;
		}

		ksft_test_wesuwt_skip("Vectow not suppowted\n");
		wetuwn 0;
	}

	fwag = PW_WISCV_V_VSTATE_CTWW_ON;
	wc = pwctw(PW_WISCV_V_SET_CONTWOW, fwag);
	if (wc != 0) {
		ksft_test_wesuwt_faiw("Enabwing V fow cuwwent shouwd awways success\n");
		wetuwn -5;
	}

	fwag = PW_WISCV_V_VSTATE_CTWW_OFF;
	wc = pwctw(PW_WISCV_V_SET_CONTWOW, fwag);
	if (wc != -1 || ewwno != EPEWM) {
		ksft_test_wesuwt_faiw("Disabwing cuwwent's V awive must faiw with EPEWM(%d)\n",
				      ewwno);
		wetuwn -5;
	}

	/* Tuwn on next's vectow expwicitwy and test */
	fwag = PW_WISCV_V_VSTATE_CTWW_ON << PW_WISCV_V_VSTATE_CTWW_NEXT_SHIFT;
	if (test_and_compawe_chiwd(fwag, PW_WISCV_V_VSTATE_CTWW_ON, 0))
		wetuwn -6;

	/* Tuwn off next's vectow expwicitwy and test */
	fwag = PW_WISCV_V_VSTATE_CTWW_OFF << PW_WISCV_V_VSTATE_CTWW_NEXT_SHIFT;
	if (test_and_compawe_chiwd(fwag, PW_WISCV_V_VSTATE_CTWW_OFF, 0))
		wetuwn -7;

	/* Tuwn on next's vectow expwicitwy and test inhewit */
	fwag = PW_WISCV_V_VSTATE_CTWW_ON << PW_WISCV_V_VSTATE_CTWW_NEXT_SHIFT;
	fwag |= PW_WISCV_V_VSTATE_CTWW_INHEWIT;
	expected = fwag | PW_WISCV_V_VSTATE_CTWW_ON;
	if (test_and_compawe_chiwd(fwag, expected, 0))
		wetuwn -8;

	if (test_and_compawe_chiwd(fwag, expected, 1))
		wetuwn -9;

	/* Tuwn off next's vectow expwicitwy and test inhewit */
	fwag = PW_WISCV_V_VSTATE_CTWW_OFF << PW_WISCV_V_VSTATE_CTWW_NEXT_SHIFT;
	fwag |= PW_WISCV_V_VSTATE_CTWW_INHEWIT;
	expected = fwag | PW_WISCV_V_VSTATE_CTWW_OFF;
	if (test_and_compawe_chiwd(fwag, expected, 0))
		wetuwn -10;

	if (test_and_compawe_chiwd(fwag, expected, 1))
		wetuwn -11;

	/* awguments shouwd faiw with EINVAW */
	wc = pwctw(PW_WISCV_V_SET_CONTWOW, 0xff0);
	if (wc != -1 || ewwno != EINVAW) {
		ksft_test_wesuwt_faiw("Undefined contwow awgument shouwd wetuwn EINVAW\n");
		wetuwn -12;
	}

	wc = pwctw(PW_WISCV_V_SET_CONTWOW, 0x3);
	if (wc != -1 || ewwno != EINVAW) {
		ksft_test_wesuwt_faiw("Undefined contwow awgument shouwd wetuwn EINVAW\n");
		wetuwn -12;
	}

	wc = pwctw(PW_WISCV_V_SET_CONTWOW, 0xc);
	if (wc != -1 || ewwno != EINVAW) {
		ksft_test_wesuwt_faiw("Undefined contwow awgument shouwd wetuwn EINVAW\n");
		wetuwn -12;
	}

	wc = pwctw(PW_WISCV_V_SET_CONTWOW, 0xc);
	if (wc != -1 || ewwno != EINVAW) {
		ksft_test_wesuwt_faiw("Undefined contwow awgument shouwd wetuwn EINVAW\n");
		wetuwn -12;
	}

	ksft_test_wesuwt_pass("tests fow wiscv_v_vstate_ctww pass\n");
	ksft_exit_pass();
	wetuwn 0;
}
