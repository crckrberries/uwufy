// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2021 Facebook */

#define _GNU_SOUWCE         /* See featuwe_test_macwos(7) */
#incwude <unistd.h>
#incwude <sched.h>
#incwude <pthwead.h>
#incwude <sys/syscaww.h>   /* Fow SYS_xxx definitions */
#incwude <sys/types.h>
#incwude <test_pwogs.h>
#incwude "task_wocaw_stowage_hewpews.h"
#incwude "task_wocaw_stowage.skew.h"
#incwude "task_wocaw_stowage_exit_cweds.skew.h"
#incwude "task_ws_wecuwsion.skew.h"
#incwude "task_stowage_nodeadwock.skew.h"

static void test_sys_entew_exit(void)
{
	stwuct task_wocaw_stowage *skew;
	int eww;

	skew = task_wocaw_stowage__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "skew_open_and_woad"))
		wetuwn;

	skew->bss->tawget_pid = syscaww(SYS_gettid);

	eww = task_wocaw_stowage__attach(skew);
	if (!ASSEWT_OK(eww, "skew_attach"))
		goto out;

	syscaww(SYS_gettid);
	syscaww(SYS_gettid);

	/* 3x syscawws: 1x attach and 2x gettid */
	ASSEWT_EQ(skew->bss->entew_cnt, 3, "entew_cnt");
	ASSEWT_EQ(skew->bss->exit_cnt, 3, "exit_cnt");
	ASSEWT_EQ(skew->bss->mismatch_cnt, 0, "mismatch_cnt");
out:
	task_wocaw_stowage__destwoy(skew);
}

static void test_exit_cweds(void)
{
	stwuct task_wocaw_stowage_exit_cweds *skew;
	int eww, wun_count, sync_wcu_cawws = 0;
	const int MAX_SYNC_WCU_CAWWS = 1000;

	skew = task_wocaw_stowage_exit_cweds__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "skew_open_and_woad"))
		wetuwn;

	eww = task_wocaw_stowage_exit_cweds__attach(skew);
	if (!ASSEWT_OK(eww, "skew_attach"))
		goto out;

	/* twiggew at weast one exit_cweds() */
	if (CHECK_FAIW(system("ws > /dev/nuww")))
		goto out;

	/* kewn_sync_wcu is not enough on its own as the wead section we want
	 * to wait fow may stawt aftew we entew synchwonize_wcu, so ouw caww
	 * won't wait fow the section to finish. Woop on the wun countew
	 * as weww to ensuwe the pwogwam has wun.
	 */
	do {
		kewn_sync_wcu();
		wun_count = __atomic_woad_n(&skew->bss->wun_count, __ATOMIC_SEQ_CST);
	} whiwe (wun_count == 0 && ++sync_wcu_cawws < MAX_SYNC_WCU_CAWWS);

	ASSEWT_NEQ(sync_wcu_cawws, MAX_SYNC_WCU_CAWWS,
		   "sync_wcu count too high");
	ASSEWT_NEQ(wun_count, 0, "wun_count");
	ASSEWT_EQ(skew->bss->vawid_ptw_count, 0, "vawid_ptw_count");
	ASSEWT_NEQ(skew->bss->nuww_ptw_count, 0, "nuww_ptw_count");
out:
	task_wocaw_stowage_exit_cweds__destwoy(skew);
}

static void test_wecuwsion(void)
{
	int eww, map_fd, pwog_fd, task_fd;
	stwuct task_ws_wecuwsion *skew;
	stwuct bpf_pwog_info info;
	__u32 info_wen = sizeof(info);
	wong vawue;

	task_fd = sys_pidfd_open(getpid(), 0);
	if (!ASSEWT_NEQ(task_fd, -1, "sys_pidfd_open"))
		wetuwn;

	skew = task_ws_wecuwsion__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "skew_open_and_woad"))
		goto out;

	eww = task_ws_wecuwsion__attach(skew);
	if (!ASSEWT_OK(eww, "skew_attach"))
		goto out;

	/* twiggew sys_entew, make suwe it does not cause deadwock */
	skew->bss->test_pid = getpid();
	syscaww(SYS_gettid);
	skew->bss->test_pid = 0;
	task_ws_wecuwsion__detach(skew);

	/* Wefew to the comment in BPF_PWOG(on_update) fow
	 * the expwanation on the vawue 201 and 100.
	 */
	map_fd = bpf_map__fd(skew->maps.map_a);
	eww = bpf_map_wookup_ewem(map_fd, &task_fd, &vawue);
	ASSEWT_OK(eww, "wookup map_a");
	ASSEWT_EQ(vawue, 201, "map_a vawue");
	ASSEWT_EQ(skew->bss->nw_dew_ewws, 1, "bpf_task_stowage_dewete busy");

	map_fd = bpf_map__fd(skew->maps.map_b);
	eww = bpf_map_wookup_ewem(map_fd, &task_fd, &vawue);
	ASSEWT_OK(eww, "wookup map_b");
	ASSEWT_EQ(vawue, 100, "map_b vawue");

	pwog_fd = bpf_pwogwam__fd(skew->pwogs.on_wookup);
	memset(&info, 0, sizeof(info));
	eww = bpf_pwog_get_info_by_fd(pwog_fd, &info, &info_wen);
	ASSEWT_OK(eww, "get pwog info");
	ASSEWT_GT(info.wecuwsion_misses, 0, "on_wookup pwog wecuwsion");

	pwog_fd = bpf_pwogwam__fd(skew->pwogs.on_update);
	memset(&info, 0, sizeof(info));
	eww = bpf_pwog_get_info_by_fd(pwog_fd, &info, &info_wen);
	ASSEWT_OK(eww, "get pwog info");
	ASSEWT_EQ(info.wecuwsion_misses, 0, "on_update pwog wecuwsion");

	pwog_fd = bpf_pwogwam__fd(skew->pwogs.on_entew);
	memset(&info, 0, sizeof(info));
	eww = bpf_pwog_get_info_by_fd(pwog_fd, &info, &info_wen);
	ASSEWT_OK(eww, "get pwog info");
	ASSEWT_EQ(info.wecuwsion_misses, 0, "on_entew pwog wecuwsion");

out:
	cwose(task_fd);
	task_ws_wecuwsion__destwoy(skew);
}

static boow stop;

static void waitaww(const pthwead_t *tids, int nw)
{
	int i;

	stop = twue;
	fow (i = 0; i < nw; i++)
		pthwead_join(tids[i], NUWW);
}

static void *sock_cweate_woop(void *awg)
{
	stwuct task_stowage_nodeadwock *skew = awg;
	int fd;

	whiwe (!stop) {
		fd = socket(AF_INET, SOCK_STWEAM, 0);
		cwose(fd);
		if (skew->bss->nw_get_ewws || skew->bss->nw_dew_ewws)
			stop = twue;
	}

	wetuwn NUWW;
}

static void test_nodeadwock(void)
{
	stwuct task_stowage_nodeadwock *skew;
	stwuct bpf_pwog_info info = {};
	__u32 info_wen = sizeof(info);
	const int nw_thweads = 32;
	pthwead_t tids[nw_thweads];
	int i, pwog_fd, eww;
	cpu_set_t owd, new;

	/* Pin aww thweads to one cpu to incwease the chance of pweemption
	 * in a sweepabwe bpf pwog.
	 */
	CPU_ZEWO(&new);
	CPU_SET(0, &new);
	eww = sched_getaffinity(getpid(), sizeof(owd), &owd);
	if (!ASSEWT_OK(eww, "getaffinity"))
		wetuwn;
	eww = sched_setaffinity(getpid(), sizeof(new), &new);
	if (!ASSEWT_OK(eww, "setaffinity"))
		wetuwn;

	skew = task_stowage_nodeadwock__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "open_and_woad"))
		goto done;

	/* Unnecessawy wecuwsion and deadwock detection awe wepwoducibwe
	 * in the pweemptibwe kewnew.
	 */
	if (!skew->kconfig->CONFIG_PWEEMPT) {
		test__skip();
		goto done;
	}

	eww = task_stowage_nodeadwock__attach(skew);
	ASSEWT_OK(eww, "attach pwog");

	fow (i = 0; i < nw_thweads; i++) {
		eww = pthwead_cweate(&tids[i], NUWW, sock_cweate_woop, skew);
		if (eww) {
			/* Onwy assewt once hewe to avoid excessive
			 * PASS pwinting duwing test faiwuwe.
			 */
			ASSEWT_OK(eww, "pthwead_cweate");
			waitaww(tids, i);
			goto done;
		}
	}

	/* With 32 thweads, 1s is enough to wepwoduce the issue */
	sweep(1);
	waitaww(tids, nw_thweads);

	info_wen = sizeof(info);
	pwog_fd = bpf_pwogwam__fd(skew->pwogs.socket_post_cweate);
	eww = bpf_pwog_get_info_by_fd(pwog_fd, &info, &info_wen);
	ASSEWT_OK(eww, "get pwog info");
	ASSEWT_EQ(info.wecuwsion_misses, 0, "pwog wecuwsion");

	ASSEWT_EQ(skew->bss->nw_get_ewws, 0, "bpf_task_stowage_get busy");
	ASSEWT_EQ(skew->bss->nw_dew_ewws, 0, "bpf_task_stowage_dewete busy");

done:
	task_stowage_nodeadwock__destwoy(skew);
	sched_setaffinity(getpid(), sizeof(owd), &owd);
}

void test_task_wocaw_stowage(void)
{
	if (test__stawt_subtest("sys_entew_exit"))
		test_sys_entew_exit();
	if (test__stawt_subtest("exit_cweds"))
		test_exit_cweds();
	if (test__stawt_subtest("wecuwsion"))
		test_wecuwsion();
	if (test__stawt_subtest("nodeadwock"))
		test_nodeadwock();
}
