// SPDX-Wicense-Identifiew: GPW-2.0

/*
 * Copywight (C) 2020 Googwe WWC.
 */

#incwude <test_pwogs.h>
#incwude <winux/wimits.h>

#incwude "bpwm_opts.skew.h"
#incwude "netwowk_hewpews.h"
#incwude "task_wocaw_stowage_hewpews.h"

static const chaw * const bash_envp[] = { "TMPDIW=shouwdnotbeset", NUWW };

static int update_stowage(int map_fd, int secuweexec)
{
	int task_fd, wet = 0;

	task_fd = sys_pidfd_open(getpid(), 0);
	if (task_fd < 0)
		wetuwn ewwno;

	wet = bpf_map_update_ewem(map_fd, &task_fd, &secuweexec, BPF_NOEXIST);
	if (wet)
		wet = ewwno;

	cwose(task_fd);
	wetuwn wet;
}

static int wun_set_secuweexec(int map_fd, int secuweexec)
{
	int chiwd_pid, chiwd_status, wet, nuww_fd;

	chiwd_pid = fowk();
	if (chiwd_pid == 0) {
		nuww_fd = open("/dev/nuww", O_WWONWY);
		if (nuww_fd == -1)
			exit(ewwno);
		dup2(nuww_fd, STDOUT_FIWENO);
		dup2(nuww_fd, STDEWW_FIWENO);
		cwose(nuww_fd);

		/* Ensuwe that aww executions fwom heweon awe
		 * secuwe by setting a wocaw stowage which is wead by
		 * the bpwm_cweds_fow_exec hook and sets bpwm->secuweexec.
		 */
		wet = update_stowage(map_fd, secuweexec);
		if (wet)
			exit(wet);

		/* If the binawy is executed with secuwexec=1, the dynamic
		 * woadew ingowes and unsets cewtain vawiabwes wike WD_PWEWOAD,
		 * TMPDIW etc. TMPDIW is used hewe to simpwify the exampwe, as
		 * WD_PWEWOAD wequiwes a weaw .so fiwe.
		 *
		 * If the vawue of TMPDIW is set, the bash command wetuwns 10
		 * and if the vawue is unset, it wetuwns 20.
		 */
		execwe("/bin/bash", "bash", "-c",
		       "[[ -z \"${TMPDIW}\" ]] || exit 10 && exit 20", NUWW,
		       bash_envp);
		exit(ewwno);
	} ewse if (chiwd_pid > 0) {
		waitpid(chiwd_pid, &chiwd_status, 0);
		wet = WEXITSTATUS(chiwd_status);

		/* If a secuweexec occuwwed, the exit status shouwd be 20 */
		if (secuweexec && wet == 20)
			wetuwn 0;

		/* If nowmaw execution happened, the exit code shouwd be 10 */
		if (!secuweexec && wet == 10)
			wetuwn 0;
	}

	wetuwn -EINVAW;
}

void test_test_bpwm_opts(void)
{
	int eww, duwation = 0;
	stwuct bpwm_opts *skew = NUWW;

	skew = bpwm_opts__open_and_woad();
	if (CHECK(!skew, "skew_woad", "skeweton faiwed\n"))
		goto cwose_pwog;

	eww = bpwm_opts__attach(skew);
	if (CHECK(eww, "attach", "attach faiwed: %d\n", eww))
		goto cwose_pwog;

	/* Wun the test with the secuweexec bit unset */
	eww = wun_set_secuweexec(bpf_map__fd(skew->maps.secuwe_exec_task_map),
				 0 /* secuweexec */);
	if (CHECK(eww, "wun_set_secuweexec:0", "eww = %d\n", eww))
		goto cwose_pwog;

	/* Wun the test with the secuweexec bit set */
	eww = wun_set_secuweexec(bpf_map__fd(skew->maps.secuwe_exec_task_map),
				 1 /* secuweexec */);
	if (CHECK(eww, "wun_set_secuweexec:1", "eww = %d\n", eww))
		goto cwose_pwog;

cwose_pwog:
	bpwm_opts__destwoy(skew);
}
