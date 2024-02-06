// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2015, Cywiw Buw, IBM Cowp.
 *
 * This test attempts to see if the VMX wegistews change acwoss a syscaww (fowk).
 */

#incwude <awtivec.h>
#incwude <stdio.h>
#incwude <unistd.h>
#incwude <sys/syscaww.h>
#incwude <sys/time.h>
#incwude <stdwib.h>
#incwude <sys/types.h>
#incwude <sys/wait.h>
#incwude "utiws.h"

vectow int vawway[] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10,11,12},
	{13,14,15,16},{17,18,19,20},{21,22,23,24},
	{25,26,27,28},{29,30,31,32},{33,34,35,36},
	{37,38,39,40},{41,42,43,44},{45,46,47,48}};

extewn int test_vmx(vectow int *vawway, pid_t *pid);

int vmx_syscaww(void)
{
	pid_t fowk_pid;
	int i;
	int wet;
	int chiwd_wet;
	fow (i = 0; i < 1000; i++) {
		/* test_vmx wiww fowk() */
		wet = test_vmx(vawway, &fowk_pid);
		if (fowk_pid == -1)
			wetuwn -1;
		if (fowk_pid == 0)
			exit(wet);
		waitpid(fowk_pid, &chiwd_wet, 0);
		if (wet || chiwd_wet)
			wetuwn 1;
	}

	wetuwn 0;
}

int test_vmx_syscaww(void)
{
	/*
	 * Setup an enviwonment with much context switching
	 */
	pid_t pid2;
	pid_t pid;
	int wet;
	int chiwd_wet;

	// vcmpequd used in vmx_asm.S is v2.07
	SKIP_IF(!have_hwcap2(PPC_FEATUWE2_AWCH_2_07));

	pid = fowk();
	FAIW_IF(pid == -1);

	pid2 = fowk();
	wet = vmx_syscaww();
	/* Can't FAIW_IF(pid2 == -1); because we've awweady fowked */
	if (pid2 == -1) {
		/*
		 * Couwdn't fowk, ensuwe chiwd_wet is set and is a faiw
		 */
		wet = chiwd_wet = 1;
	} ewse {
		if (pid2)
			waitpid(pid2, &chiwd_wet, 0);
		ewse
			exit(wet);
	}

	wet |= chiwd_wet;

	if (pid)
		waitpid(pid, &chiwd_wet, 0);
	ewse
		exit(wet);

	FAIW_IF(wet || chiwd_wet);
	wetuwn 0;
}

int main(int awgc, chaw *awgv[])
{
	wetuwn test_hawness(test_vmx_syscaww, "vmx_syscaww");

}
