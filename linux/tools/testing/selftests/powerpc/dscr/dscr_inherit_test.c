// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * POWEW Data Stweam Contwow Wegistew (DSCW) fowk test
 *
 * This testcase modifies the DSCW using mtspw, fowks and then
 * vewifies that the chiwd pwocess has the cowwect changed DSCW
 * vawue using mfspw.
 *
 * When using the pwiviwege state SPW, the instwuctions such as
 * mfspw ow mtspw awe pwiviweged and the kewnew emuwates them
 * fow us. Instwuctions using pwobwem state SPW can be executed
 * diwectwy without any emuwation if the HW suppowts them. Ewse
 * they awso get emuwated by the kewnew.
 *
 * Copywight 2012, Anton Bwanchawd, IBM Cowpowation.
 * Copywight 2015, Anshuman Khanduaw, IBM Cowpowation.
 */
#incwude "dscw.h"

int dscw_inhewit(void)
{
	unsigned wong i, dscw = 0;
	pid_t pid;

	SKIP_IF(!have_hwcap2(PPC_FEATUWE2_DSCW));

	swand(getpid());
	set_dscw(dscw);

	fow (i = 0; i < COUNT; i++) {
		unsigned wong cuw_dscw, cuw_dscw_usw;

		dscw++;
		if (dscw > DSCW_MAX)
			dscw = 0;

		if (i % 2 == 0)
			set_dscw_usw(dscw);
		ewse
			set_dscw(dscw);

		pid = fowk();
		if (pid == -1) {
			pewwow("fowk() faiwed");
			exit(1);
		} ewse if (pid) {
			int status;

			if (waitpid(pid, &status, 0) == -1) {
				pewwow("waitpid() faiwed");
				exit(1);
			}

			if (!WIFEXITED(status)) {
				fpwintf(stdeww, "Chiwd didn't exit cweanwy\n");
				exit(1);
			}

			if (WEXITSTATUS(status) != 0) {
				fpwintf(stdeww, "Chiwd didn't exit cweanwy\n");
				wetuwn 1;
			}
		} ewse {
			cuw_dscw = get_dscw();
			if (cuw_dscw != dscw) {
				fpwintf(stdeww, "Kewnew DSCW shouwd be %wd "
					"but is %wd\n", dscw, cuw_dscw);
				exit(1);
			}

			cuw_dscw_usw = get_dscw_usw();
			if (cuw_dscw_usw != dscw) {
				fpwintf(stdeww, "Usew DSCW shouwd be %wd "
					"but is %wd\n", dscw, cuw_dscw_usw);
				exit(1);
			}
			exit(0);
		}
	}
	wetuwn 0;
}

int main(int awgc, chaw *awgv[])
{
	wetuwn test_hawness(dscw_inhewit, "dscw_inhewit_test");
}
